/* BUILD VERSION: FH8856_IPC_V1.2.0_20200324 @ aee6fa1 */
/*
 * jxf22_mipi_mipi.c
 *
 *  Created on: Sep 14, 2015
 *      Author: duobao
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fh_defs.h"
#include "isp_func_def.h"

#include "isp_sensor_if.h"
#include "sensor_ops.h"

#include "isp_enum.h"
#include "jxf22_mipi.h"
#include "jxf22_mipi_wdr.h"
#include "mipi_ctrl.h"

extern unsigned int NAME(ImageParam)[4],NAME(contrast)[12],NAME(saturation)[12],NAME(sharpness)[12],NAME(MirrorFlipBayerFormat)[4],NAME(AwbGain)[4][3],
NAME(LtmMapping00)[128],NAME(LtmMapping01)[128],NAME(LtmMapping02)[128],NAME(LtmMapping03)[128],NAME(LtmMapping04)[128],NAME(LtmMapping05)[128],
NAME(LtmMapping06)[128],NAME(LtmMapping07)[128],NAME(LtmMapping08)[128],NAME(LtmMapping09)[128],NAME(LtmMapping10)[128];

extern unsigned int NAME(ImageParamWdr)[4];
extern unsigned int NAME(contrastWdr)[12];
extern unsigned int NAME(saturationWdr)[12];
extern unsigned int NAME(sharpnessWdr)[12];
extern unsigned int NAME(MirrorFlipBayerFormatWdr)[4];
extern unsigned int NAME(AwbGainWdr)[4][3];

static FH_BOOL inited=0;

static FH_UINT32 sensor_fmt;
static FH_UINT32 m_gain = 0;
static int wdr_flag;
static int curr_exposure_ratio = 96;
static FH_UINT32 l_intt;
static FH_UINT32 s_intt;

#define intt_step_max 0x10

static int GetSensorViAttr(ISP_VI_ATTR_S *vi_attr)
{

	if(vi_attr == NULL)
		return FH_ERR_NULL_POINTER;

	switch (sensor_fmt)
	{
	case FORMAT_1080P25:
		vi_attr->u16WndWidth = FRAM_W_1080P25;
		vi_attr->u16WndHeight = FRAM_H_1080P25;
		vi_attr->u16InputWidth = ACTIVE_W_1080P25;
		vi_attr->u16InputHeight = ACTIVE_H_1080P25;
		vi_attr->u16PicWidth = PIC_IN_W_1080P25;
		vi_attr->u16PicHeight = PIC_IN_H_1080P25;
		vi_attr->u16OffsetX = OFFSET_X_1080P25;
		vi_attr->u16OffsetY = OFFSET_Y_1080P25;
		vi_attr->enBayerType = BAYER_BGGR;
		break;
	case FORMAT_1080P30:
		vi_attr->u16WndWidth = FRAM_W_1080P30;
		vi_attr->u16WndHeight = FRAM_H_1080P30;
		vi_attr->u16InputWidth = ACTIVE_W_1080P30;
		vi_attr->u16InputHeight = ACTIVE_H_1080P30;
		vi_attr->u16PicWidth = PIC_IN_W_1080P30;
		vi_attr->u16PicHeight = PIC_IN_H_1080P30;
		vi_attr->u16OffsetX = OFFSET_X_1080P30;
		vi_attr->u16OffsetY = OFFSET_Y_1080P30;
		vi_attr->enBayerType = BAYER_BGGR;
		break;
	case FORMAT_WDR_1080P25:
		vi_attr->u16WndWidth = FRAM_W_1080P25_WDR;
		vi_attr->u16WndHeight = FRAM_H_1080P25_WDR;
		vi_attr->u16InputWidth = ACTIVE_W_1080P25_WDR;
		vi_attr->u16InputHeight = ACTIVE_H_1080P25_WDR;
		vi_attr->u16PicWidth = PIC_IN_W_1080P25_WDR;
		vi_attr->u16PicHeight = PIC_IN_H_1080P25_WDR;
		vi_attr->u16OffsetX = OFFSET_X_1080P25_WDR;
		vi_attr->u16OffsetY = OFFSET_Y_1080P25_WDR;
		vi_attr->enBayerType = BAYER_BGGR;
		break;
	case FORMAT_WDR_1080P30:
		vi_attr->u16WndWidth = FRAM_W_1080P30_WDR;
		vi_attr->u16WndHeight = FRAM_H_1080P30_WDR;
		vi_attr->u16InputWidth = ACTIVE_W_1080P30_WDR;
		vi_attr->u16InputHeight = ACTIVE_H_1080P30_WDR;
		vi_attr->u16PicWidth = PIC_IN_W_1080P30_WDR;
		vi_attr->u16PicHeight = PIC_IN_H_1080P30_WDR;
		vi_attr->u16OffsetX = OFFSET_X_1080P30_WDR;
		vi_attr->u16OffsetY = OFFSET_Y_1080P30_WDR;
		vi_attr->enBayerType = BAYER_BGGR;
		break;
	default:
		return FH_ERR_ISP_NO_SUPPORT_FORMAT;
		}
	return 0;
}

static void SensorReset(void)
{
	return;
}

static int GetSensorGain(FH_UINT32 *u32Gain)		//gain U10.6
{
    // if (0 == m_gain){

    //    /* Total gain = (2^PGA[6:4])*(1+PGA[3:0]/16) */
    //     FH_UINT32 gain = Sensor_Read( 0x00);
    //     FH_UINT8 int_gain = (gain >> 4)  &  0x7;

    //     m_gain = ((((gain & 0xf) + 0x10) << int_gain)
    //                  << 2);   /* U.4 ---> U.6 */

    // }

    *u32Gain = m_gain;
    return 0;

}

static int SetSensorGain(FH_UINT32 gain)		//gain U10.6
{
    FH_UINT32 real_gain = gain >> 2;      /* U.6-->U.4 */
    FH_UINT32 integer = real_gain >> 4;
    FH_UINT32 fine;
    FH_UINT8 i = 0;

    while(integer >>= 1){
        i++;
    }
    fine = (real_gain >> i) - 0x10;

    Sensor_Write( 0x00, ((i & 0x7) << 4) | fine);

    /* Applied gain */
    m_gain = (((fine + 0x10) << (i & 0x7) )
                    << 2);
	//m_gain = gain;

    return 0;
}

static int GetSensorIntt(FH_UINT32 *intt)
{
    // if (0 == m_intt)
    // {
    // 	FH_UINT32 inttL,inttH;
	// 	inttH = Sensor_Read(0x02);
	// 	inttL = Sensor_Read(0x01);

	// 	m_intt = (inttH<<8) |inttL;
	//  }
	*intt=l_intt;
	return 0;


}

static int SetSensorIntt(FH_UINT32 intt)
{
	if(intt > (intt_step_max + l_intt))
	{
		intt = l_intt + intt_step_max;
	}

	l_intt = MAX(intt, 0x4);

	Sensor_Write(0x02,(intt>>8)&0xff);
	Sensor_Write(0x01,intt&0xff);

   #if 0
    /*In case camera targeted the sun, elmilate sun spot */
    #define _sun_spot_recv_cache   4
    if (intt <= drvReg->ae_ctrl2.x.sensor_intt_min){
        if (0 == sun_spot){
            Sensor_Write(0x0c, 0x00);
            Sensor_Write(0x6a, 0x61);
            sun_spot = 1;
        }
    }else if (intt > (drvReg->ae_ctrl2.x.sensor_intt_min + _sun_spot_recv_cache)){
        if (1 == sun_spot){
            Sensor_Write(0x0c, 0x40);
            Sensor_Write(0x6a, 0x01);
            sun_spot = 0;
        }
    }
#endif
    return 0;
}

static int SetExposureRatio(FH_UINT32 exposure_ratio)
{
    s_intt = MAX((((l_intt<<4)+(exposure_ratio>>1)) / exposure_ratio), 4);
    if(s_intt%2==0)
    {
        s_intt -= 1;
    }
    Sensor_Write(0x5,(s_intt - 1)/2);
    curr_exposure_ratio=(l_intt<<4)/s_intt;

    return 0;
}

static int GetExposureRatio(FH_UINT32 *exposure_ratio)
{
    *exposure_ratio = curr_exposure_ratio;
    return 0;
}

static int SetSensorFrameHeight(FH_UINT32 multiple)
{
	FH_UINT32 frame_height;
	ISP_VI_ATTR_S vi_attr;

	GetSensorViAttr(&vi_attr);

	frame_height = vi_attr.u16WndHeight * multiple;

	Sensor_Write(0x300A, frame_height);

    return 0;
}

static int Sensor_Init(void)
{
	SensorDevice_Init((0x80>>1), 0);
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
    config.frq_range = R_400_449;
    config.sensor_mode = NOT_SONY_WDR_USE_WDR;
    config.raw_type = RAW10;
    config.lane_num = 2;

    if (wdr_flag) {
        config.sf_vc_id = 2;
        config.lf_vc_id = 1;
    }
    else
    {
        config.sf_vc_id = 0;
        config.lf_vc_id = 0;
    }

    mipi_init(&config);
    return;
}

static int SetSensorFmt(int format)
{
	sensor_fmt = format;
	wdr_flag = (format >> 16) & 0x1;
	l_intt = 0xca;
	s_intt = 0x16;
	m_gain = 0x40;
	inited = 1;

	SetSensorMipiCfg();
	SensorReset();

	if(inited)
	{
		int i;

		if (wdr_flag)
		{
			switch(sensor_fmt)
			{
				case FORMAT_WDR_1080P25:
					for(i=0; i<sizeof(Sensor_Cfg_JXF22_MIPI_WDR_1080P25)/4; i++)
					{
						Sensor_Write(Sensor_Cfg_JXF22_MIPI_WDR_1080P25[2*i], Sensor_Cfg_JXF22_MIPI_WDR_1080P25[2*i+1]);
					}
					break;
				case FORMAT_WDR_1080P30:
					for(i=0; i<sizeof(Sensor_Cfg_JXF22_MIPI_WDR_1080P30)/4; i++)
					{
						Sensor_Write(Sensor_Cfg_JXF22_MIPI_WDR_1080P30[2*i], Sensor_Cfg_JXF22_MIPI_WDR_1080P30[2*i+1]);
					}
					break;
			}
		}
		else
		{
			switch(sensor_fmt)
			{
			case FORMAT_1080P25:
				Sensor_Write(Sensor_Cfg_JXF22_MIPI_1080P25[0], Sensor_Cfg_JXF22_MIPI_1080P25[1]);
				usleep(10000);
				for(i=1; i<sizeof(Sensor_Cfg_JXF22_MIPI_1080P25)/4; i++)
				{
					Sensor_Write(Sensor_Cfg_JXF22_MIPI_1080P25[2*i], Sensor_Cfg_JXF22_MIPI_1080P25[2*i+1]);
				}
				break;
			case FORMAT_1080P30:
				Sensor_Write(Sensor_Cfg_JXF22_MIPI_1080P30[0], Sensor_Cfg_JXF22_MIPI_1080P30[1]);
				usleep(10000);
				for(i=1; i<sizeof(Sensor_Cfg_JXF22_MIPI_1080P30)/4; i++)
				{
					Sensor_Write(Sensor_Cfg_JXF22_MIPI_1080P30[2*i], Sensor_Cfg_JXF22_MIPI_1080P30[2*i+1]);
				}
				break;
			}
			usleep(5000);
			for(i=0; i<sizeof(Sensor_Cfg_JXF22_MIPI_AFTER)/4; i++)
			{
				Sensor_Write(Sensor_Cfg_JXF22_MIPI_AFTER[2*i], Sensor_Cfg_JXF22_MIPI_AFTER[2*i+1]);
				usleep(1000);

			}
		}
	}
	return 0;
}

static int GetSensorAttribute(char * name, FH_UINT32 *value)
{
    if (wdr_flag) {
        if (strcmp(name, "WDR") == 0) {
            *value = 1;
            return 0;
        }
    }

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

static int SetSensorFlipMirror(FH_UINT32 sensor_en_stat)
{
	FH_UINT32 tmp,mirror,flip;

	tmp = Sensor_Read(0x12);
	mirror = (sensor_en_stat >>1)&0x1;
	flip = sensor_en_stat & 0x1;
	Sensor_Write(0x12, (tmp & 0xffcf)|mirror<<5|flip<<4);
	if (wdr_flag)
	{
		if (mirror)
			Sensor_Write(0x27,0x53);
		else
			Sensor_Write(0x27,0x52);
		if (flip)
			Sensor_Write(0x39,0x91);
		else
			Sensor_Write(0x39,0x90);
	}
	else
	{
		if (mirror)
			Sensor_Write(0x27,0xd2);
		else
			Sensor_Write(0x27,0xc9);
		if (flip)
			Sensor_Write(0x39,0x91);
		else
			Sensor_Write(0x39,0x90);
	}
	return 0;
}
static int GetSensorFlipMirror(FH_UINT32 *sensor_en_stat)
{
	FH_UINT32 tmp;

	tmp = Sensor_Read(0x12);
	*sensor_en_stat = (tmp >> 4) & 0x3;
	return 0;
}

int GetViMode(int * vi_mode)
{
    * vi_mode=5;
    return 0;
}

FH_UINT32* NAME(GetDefaultParam)()
{
    if (wdr_flag)
        return NAME(ImageParamWdr);
    else
        return NAME(ImageParam);
}

FH_UINT32* NAME(GetContrast)()
{
    if (wdr_flag)
        return NAME(contrastWdr);
    else
        return NAME(contrast);
}

FH_UINT32* NAME(GetSaturation)()
{
    if (wdr_flag)
        return NAME(saturationWdr);
    else
        return NAME(saturation);
}
FH_UINT32* NAME(GetSharpness)()
{
    if (wdr_flag)
        return NAME(sharpnessWdr);
    else
        return NAME(sharpness);
}

FH_UINT32 NAME(*GetMirrorFlipBayerFormat)()
{
    if (wdr_flag)
        return NAME(MirrorFlipBayerFormatWdr);
    else
        return NAME(MirrorFlipBayerFormat);
}

FH_UINT32* NAME(GetSensorAwbGain)(int idx)
{
    if (wdr_flag)
        return NAME(AwbGainWdr)[idx];
    else
        return NAME(AwbGain)[idx];
}

FH_UINT32* NAME(GetSensorLtmCurve)(int idx)
{
    if (!wdr_flag)
    {
        switch (idx)
        {
        case 0:
            return NAME(LtmMapping00);
            break;
        case 1:
            return NAME(LtmMapping01);
            break;
        case 2:
            return NAME(LtmMapping02);
            break;
        case 3:
            return NAME(LtmMapping03);
            break;
        case 4:
            return NAME(LtmMapping04);
            break;
        case 5:
            return NAME(LtmMapping05);
            break;
        case 6:
            return NAME(LtmMapping06);
            break;
        case 7:
            return NAME(LtmMapping07);
            break;
        case 8:
            return NAME(LtmMapping08);
            break;
        case 9:
            return NAME(LtmMapping09);
            break;
        case 10:
            return NAME(LtmMapping10);
            break;
        }
        return NAME(LtmMapping00);
    }
    return 0;
}

#if MULTI_SENSOR
static int Sensor_Isconnect(void)
{
    unsigned short pid1, pid2;
    SensorDevice_Init((0x80>>1), 0);

    pid1 = Sensor_Read(0xa);
    pid2 = Sensor_Read(0xb);
    SensorDevice_Close();
    if (pid1 == 0xf && pid2 == 0x22) {
        return 1;
    } else {
        return 0;
    }
}
#endif

#define SENSOR_JXF22_MIPI	"jxf22_mipi"
struct isp_sensor_if jxf22_mipi;

struct isp_sensor_if* NAME(Sensor_Create)()
{
#if MULTI_SENSOR
	if (!Sensor_Isconnect())
		return 0;
#endif
	memset(&jxf22_mipi,0,sizeof(struct isp_sensor_if));
	jxf22_mipi.name = SENSOR_JXF22_MIPI;
	jxf22_mipi.init = Sensor_Init;
	jxf22_mipi.get_vi_attr = GetSensorViAttr;
	jxf22_mipi.set_sns_fmt = SetSensorFmt;
	jxf22_mipi.set_gain = SetSensorGain;
	jxf22_mipi.get_gain = GetSensorGain;
	jxf22_mipi.reset    = SensorReset;
	jxf22_mipi.get_intt = GetSensorIntt;
	jxf22_mipi.set_intt = SetSensorIntt;
	jxf22_mipi.set_sns_reg = SetSensorReg;
	jxf22_mipi.set_frame_height = SetSensorFrameHeight;
	jxf22_mipi.set_flipmirror = SetSensorFlipMirror;
	jxf22_mipi.get_flipmirror = GetSensorFlipMirror;
	jxf22_mipi.set_exposure_ratio =SetExposureRatio;
	jxf22_mipi.get_exposure_ratio =GetExposureRatio;
	jxf22_mipi.get_sensor_attribute = GetSensorAttribute;
	jxf22_mipi.get_sns_reg = GetSensorReg;
	jxf22_mipi.deinit   = Sensor_DeInit;
	return &jxf22_mipi;
}

void NAME(Sensor_Destory)(struct isp_sensor_if* s_if)
{
	jxf22_mipi.name = 0;
	jxf22_mipi.init = 0;
	jxf22_mipi.get_vi_attr = 0;
	jxf22_mipi.set_sns_fmt = 0;
	jxf22_mipi.set_gain = 0;
	jxf22_mipi.get_gain = 0;
	jxf22_mipi.reset    = 0;
	jxf22_mipi.get_intt = 0;
	jxf22_mipi.set_intt = 0;
	jxf22_mipi.set_sns_reg = 0;
	jxf22_mipi.set_frame_height = 0;
	jxf22_mipi.set_flipmirror = 0;
	jxf22_mipi.get_flipmirror = 0;
	jxf22_mipi.set_exposure_ratio =0;
	jxf22_mipi.get_exposure_ratio =0;
	jxf22_mipi.get_sensor_attribute = 0;
	jxf22_mipi.get_sns_reg = 0;
	jxf22_mipi.deinit   = 0;
}