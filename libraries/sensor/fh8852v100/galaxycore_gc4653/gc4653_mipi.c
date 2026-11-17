/* SPDX-License-Identifier: GPL-3.0-only */
/*
 * GalaxyCore GC4653 for the FH885x V100 ISP (FH8852, FH8856), on the
 * interface of the SDK's sensor-build drivers (../soi_jxf22). Register
 * sources are in gc4653_mipi.h.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fh_defs.h"
#include "isp_func_def.h"

#include "isp_sensor_if.h"
#include "sensor_ops.h"

#include "isp_enum.h"
#include "gc4653_mipi.h"
#include "mipi_ctrl.h"

extern unsigned int NAME(ImageParam)[4], NAME(contrast)[12],
	NAME(saturation)[12], NAME(sharpness)[12],
	NAME(MirrorFlipBayerFormat)[4], NAME(AwbGain)[4][3],
	NAME(LtmMapping00)[128], NAME(LtmMapping01)[128],
	NAME(LtmMapping02)[128], NAME(LtmMapping03)[128],
	NAME(LtmMapping04)[128], NAME(LtmMapping05)[128],
	NAME(LtmMapping06)[128], NAME(LtmMapping07)[128],
	NAME(LtmMapping08)[128], NAME(LtmMapping09)[128],
	NAME(LtmMapping10)[128];

/*
 * The MIPI receiver's band for the lane rate. The rate is set by the PLL
 * values in the start-up list, which no source states; the frame itself
 * needs 576 Mbit/s a lane (2560 x 10 bits / 2 lanes x 1500 lines x 30)
 * before packet overhead, so 600-649 is the first band that can hold it.
 * Unconfirmed on a camera.
 */
#define GC4653_MIPI_BAND	R_600_649

static FH_UINT32 sensor_fmt;
static FH_UINT32 frame_lines = FRAM_H_1440P30;
static FH_UINT32 m_gain = 0x40;		/* U10.6, as applied */
static FH_UINT32 m_intt;

static int fmt_fps(FH_UINT32 format)
{
	switch (format) {
	case FORMAT_400WP30:
		return 30;
	case FORMAT_400WP25:
		return 25;
	case FORMAT_400WP20:
		return 20;
	case FORMAT_400WP15:
		return 15;
	}
	return 0;
}

static int GetSensorViAttr(ISP_VI_ATTR_S *vi_attr)
{
	if (vi_attr == NULL)
		return FH_ERR_NULL_POINTER;
	if (!fmt_fps(sensor_fmt))
		return FH_ERR_ISP_NO_SUPPORT_FORMAT;

	vi_attr->u16WndWidth = FRAM_W_1440P30;
	vi_attr->u16WndHeight = frame_lines;
	vi_attr->u16InputWidth = ACTIVE_W_1440P30;
	vi_attr->u16InputHeight = ACTIVE_H_1440P30;
	vi_attr->u16PicWidth = ACTIVE_W_1440P30;
	vi_attr->u16PicHeight = ACTIVE_H_1440P30;
	vi_attr->u16OffsetX = 0;
	vi_attr->u16OffsetY = 0;
	vi_attr->enBayerType = BAYER_GRBG;
	return 0;
}

static void SensorReset(void)
{
}

static int GetSensorGain(FH_UINT32 *u32Gain)
{
	*u32Gain = m_gain;
	return 0;
}

/*
 * The ISP asks for gain in U10.6 (0x40 = 1x). The sensor takes the largest
 * analog step at or below it, and the rest as its digital pre-gain,
 * 0x020e[3:0] / 0x020f[7:2], 64 = 1x.
 */
static int SetSensorGain(FH_UINT32 gain)
{
	const int steps = sizeof(gc4653_again_x1024) / sizeof(gc4653_again_x1024[0]);
	FH_UINT32 want = gain << 4;		/* U10.6 -> x1024 */
	FH_UINT32 pre;
	int i;

	if (want < gc4653_again_x1024[0])
		want = gc4653_again_x1024[0];
	for (i = 1; i < steps; i++)
		if (want < gc4653_again_x1024[i])
			break;
	i--;

	pre = want * 64 / gc4653_again_x1024[i];
	if (pre > 0x3ff)
		pre = 0x3ff;

	Sensor_Write(0x031d, 0x2d);		/* hold, as Sophgo's update does */
	Sensor_Write(0x02b3, gc4653_again_regs[i][0]);
	Sensor_Write(0x02b4, gc4653_again_regs[i][1]);
	Sensor_Write(0x02b8, gc4653_again_regs[i][2]);
	Sensor_Write(0x02b9, gc4653_again_regs[i][3]);
	Sensor_Write(0x0515, gc4653_again_regs[i][4]);
	Sensor_Write(0x0519, gc4653_again_regs[i][5]);
	Sensor_Write(0x02d9, gc4653_again_regs[i][6]);
	Sensor_Write(0x031d, 0x28);
	Sensor_Write(0x020e, pre >> 6);
	Sensor_Write(0x020f, (pre & 0x3f) << 2);

	m_gain = (gc4653_again_x1024[i] * pre / 64) >> 4;
	return 0;
}

static int GetSensorIntt(FH_UINT32 *intt)
{
	*intt = m_intt;
	return 0;
}

/* Lines. Past frame length - 32 the sensor stretches the frame itself. */
static int SetSensorIntt(FH_UINT32 intt)
{
	if (intt < 1)
		intt = 1;
	if (intt > GC4653_SHUTTER_MAX)
		intt = GC4653_SHUTTER_MAX;

	Sensor_Write(0x0202, (intt >> 8) & 0x3f);
	Sensor_Write(0x0203, intt & 0xff);
	m_intt = intt;
	return 0;
}

static int SetExposureRatio(FH_UINT32 exposure_ratio)
{
	return 0;
}

static int GetExposureRatio(FH_UINT32 *exposure_ratio)
{
	*exposure_ratio = 16;
	return 0;
}

/* As the SDK's OS05A driver: the frame follows the shutter on its own. */
static int SetSensorFrameHeight(FH_UINT32 multiple)
{
	return 0;
}

static int Sensor_Init(void)
{
	SensorDevice_Init(GC4653_I2C_ADDR, 2);	/* 16-bit address, 8-bit data */
	SensorReset();
	return 0;
}

static int Sensor_DeInit(void)
{
	SensorReset();
	return SensorDevice_Close();
}

static void SetSensorMipiCfg(void)
{
	struct mipi_conf config;

	memset(&config, 0, sizeof(config));
	config.frq_range = GC4653_MIPI_BAND;
	config.sensor_mode = NOT_SONY_WDR_USE_WDR;
	config.raw_type = RAW10;
	config.lane_num = 2;
	config.sf_vc_id = 0;
	config.lf_vc_id = 0;
	mipi_init(&config);
}

static int SetSensorFmt(int format)
{
	const int n = sizeof(Sensor_Cfg_GC4653_MIPI_1440P30) /
		      sizeof(Sensor_Cfg_GC4653_MIPI_1440P30[0]) / 2;
	int fps = fmt_fps(format);
	int i;

	if (!fps)
		return FH_ERR_ISP_NO_SUPPORT_FORMAT;

	sensor_fmt = format;
	frame_lines = FRAM_H_1440P30 * 30 / fps;
	m_gain = 0x40;

	SetSensorMipiCfg();
	SensorReset();

	usleep(10000);
	for (i = 0; i < n; i++)
		Sensor_Write(Sensor_Cfg_GC4653_MIPI_1440P30[2 * i],
			     Sensor_Cfg_GC4653_MIPI_1440P30[2 * i + 1]);

	Sensor_Write(0x0340, (frame_lines >> 8) & 0x3f);
	Sensor_Write(0x0341, frame_lines & 0xff);
	SetSensorIntt(frame_lines - 32);
	SetSensorGain(0x40);
	usleep(10000);
	return 0;
}

/*
 * API_ISP_SensorKick() calls this and fails with -1 when it is unset, which
 * stops majestic's start-up after everything else has worked; neither of
 * the SDK's V100 sample drivers sets it. The start-up list has already
 * switched streaming on, so this only says so again, as the V200 SDK's
 * OS05A driver's kick does ("enable sensor output").
 */
static int Sensor_Kick(void)
{
	Sensor_Write(0x0100, 0x09);
	return 0;
}

static int GetSensorAttribute(char *name, FH_UINT32 *value)
{
	return -1;
}

static int SetSensorReg(unsigned short addr, unsigned short data)
{
	Sensor_Write(addr, data);
	return 0;
}

static int GetSensorReg(unsigned short addr, unsigned short *data)
{
	*data = Sensor_Read(addr);
	return 0;
}

/* sensor_en_stat: bit 1 mirror, bit 0 flip; 0x0101: bit 1 flip, bit 0 mirror. */
static int SetSensorFlipMirror(FH_UINT32 sensor_en_stat)
{
	FH_UINT32 mirror = (sensor_en_stat >> 1) & 1;
	FH_UINT32 flip = sensor_en_stat & 1;

	Sensor_Write(0x031d, 0x2d);
	Sensor_Write(0x0101, (flip << 1) | mirror);
	Sensor_Write(0x031d, 0x28);
	return 0;
}

static int GetSensorFlipMirror(FH_UINT32 *sensor_en_stat)
{
	FH_UINT32 v = Sensor_Read(0x0101);

	*sensor_en_stat = ((v & 1) << 1) | ((v >> 1) & 1);
	return 0;
}

int GetViMode(int *vi_mode)
{
	*vi_mode = 5;				/* MIPI */
	return 0;
}

FH_UINT32 *NAME(GetDefaultParam)()
{
	return NAME(ImageParam);
}

FH_UINT32 *NAME(GetContrast)()
{
	return NAME(contrast);
}

FH_UINT32 *NAME(GetSaturation)()
{
	return NAME(saturation);
}

FH_UINT32 *NAME(GetSharpness)()
{
	return NAME(sharpness);
}

FH_UINT32 NAME(*GetMirrorFlipBayerFormat)()
{
	return NAME(MirrorFlipBayerFormat);
}

FH_UINT32 *NAME(GetSensorAwbGain)(int idx)
{
	return NAME(AwbGain)[idx];
}

FH_UINT32 *NAME(GetSensorLtmCurve)(int idx)
{
	static unsigned int *const curves[] = {
		NAME(LtmMapping00), NAME(LtmMapping01), NAME(LtmMapping02),
		NAME(LtmMapping03), NAME(LtmMapping04), NAME(LtmMapping05),
		NAME(LtmMapping06), NAME(LtmMapping07), NAME(LtmMapping08),
		NAME(LtmMapping09), NAME(LtmMapping10),
	};

	if (idx < 0 || idx >= (int)(sizeof(curves) / sizeof(curves[0])))
		idx = 0;
	return curves[idx];
}

#if MULTI_SENSOR
static int Sensor_Isconnect(void)
{
	unsigned short id;

	SensorDevice_Init(GC4653_I2C_ADDR, 2);
	id = (Sensor_Read(0x03f0) << 8) | Sensor_Read(0x03f1);
	SensorDevice_Close();
	return id == GC4653_CHIP_ID;
}
#endif

#define SENSOR_GC4653_MIPI	"gc4653_mipi"
struct isp_sensor_if gc4653_mipi;

struct isp_sensor_if *NAME(Sensor_Create)()
{
#if MULTI_SENSOR
	if (!Sensor_Isconnect())
		return 0;
#endif
	memset(&gc4653_mipi, 0, sizeof(struct isp_sensor_if));
	gc4653_mipi.name = SENSOR_GC4653_MIPI;
	gc4653_mipi.init = Sensor_Init;
	gc4653_mipi.get_vi_attr = GetSensorViAttr;
	gc4653_mipi.set_sns_fmt = SetSensorFmt;
	gc4653_mipi.kick = Sensor_Kick;
	gc4653_mipi.get_vi_mode = GetViMode;
	gc4653_mipi.set_gain = SetSensorGain;
	gc4653_mipi.get_gain = GetSensorGain;
	gc4653_mipi.reset = SensorReset;
	gc4653_mipi.get_intt = GetSensorIntt;
	gc4653_mipi.set_intt = SetSensorIntt;
	gc4653_mipi.set_sns_reg = SetSensorReg;
	gc4653_mipi.set_frame_height = SetSensorFrameHeight;
	gc4653_mipi.set_flipmirror = SetSensorFlipMirror;
	gc4653_mipi.get_flipmirror = GetSensorFlipMirror;
	gc4653_mipi.set_exposure_ratio = SetExposureRatio;
	gc4653_mipi.get_exposure_ratio = GetExposureRatio;
	gc4653_mipi.get_sensor_attribute = GetSensorAttribute;
	gc4653_mipi.get_sns_reg = GetSensorReg;
	gc4653_mipi.deinit = Sensor_DeInit;
	return &gc4653_mipi;
}

/* "Destory" is the SDK's spelling of the symbol the ISP looks up. */
void NAME(Sensor_Destory)(struct isp_sensor_if *s_if)
{
	memset(&gc4653_mipi, 0, sizeof(struct isp_sensor_if));
}

/* The destructor under its corrected spelling as well as the SDK's. */
void NAME(Sensor_Destroy)(struct isp_sensor_if *s_if)
{
	NAME(Sensor_Destory)(s_if);
}
