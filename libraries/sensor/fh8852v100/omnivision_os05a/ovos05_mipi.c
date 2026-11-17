/* BUILD VERSION: FH8856_IPC_V1.2.0_20200324 @ aee6fa1 */
/*
 * ovos05_mipi.c
 *
 */

#include "ovos05_mipi.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fh_defs.h"
#include "isp_func_def.h"
#include "clock_ops.h"

#include "isp_sensor_if.h"
#include "sensor_ops.h"

#include "isp_enum.h"
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

static FH_BOOL inited = 0;
static FH_UINT32 sensor_fmt;
static FH_UINT32 wdr_flag;
static FH_UINT32 curr_sensor_gain;
static FH_UINT32 long_exposure_intt;
static FH_UINT32 curr_exposure_ratio = 256;
static FH_BOOL chip_idx = 1;

int SetIspChipId(int chip_id) {
    if (chip_id == 0xc) {
        chip_idx = 0;
    }
    return 0;
}

static int GetSensorViAttr(ISP_VI_ATTR_S *vi_attr) {
    if (vi_attr == NULL)
        return FH_ERR_NULL_POINTER;
    if (chip_idx == 1) {
        if (wdr_flag == 1) {
            switch (sensor_fmt) {
            case FORMAT_500W12P5:  // 500w 12.5
                vi_attr->u16WndWidth = FRAM_W_WDR_500W12P5;
                vi_attr->u16WndHeight = FRAM_H_WDR_500W12P5;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_500W12P5;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_500W12P5;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_500W12P5;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_500W12P5;
                vi_attr->u16OffsetX = OFFSET_X_WDR_500W12P5;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_500W12P5;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_1536P25:
                vi_attr->u16WndWidth = FRAM_W_WDR_1536P25;
                vi_attr->u16WndHeight = FRAM_H_WDR_1536P25;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_1536P25;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_1536P25;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_1536P25;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_1536P25;
                vi_attr->u16OffsetX = OFFSET_X_WDR_1536P25;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_1536P25;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_1536P30:
                vi_attr->u16WndWidth = FRAM_W_WDR_1536P30;
                vi_attr->u16WndHeight = FRAM_H_WDR_1536P30;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_1536P30;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_1536P30;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_1536P30;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_1536P30;
                vi_attr->u16OffsetX = OFFSET_X_WDR_1536P30;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_1536P30;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_1536P40:
                vi_attr->u16WndWidth = FRAM_W_WDR_1536P40;
                vi_attr->u16WndHeight = FRAM_H_WDR_1536P40;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_1536P40;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_1536P40;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_1536P40;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_1536P40;
                vi_attr->u16OffsetX = OFFSET_X_WDR_1536P40;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_1536P40;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_400WP25:
                vi_attr->u16WndWidth = FRAM_W_WDR_400WP25;
                vi_attr->u16WndHeight = FRAM_H_WDR_400WP25;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_400WP25;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_400WP25;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_400WP25;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_400WP25;
                vi_attr->u16OffsetX = OFFSET_X_WDR_400WP25;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_400WP25;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_400WP30:
                vi_attr->u16WndWidth = FRAM_W_WDR_400WP30;
                vi_attr->u16WndHeight = FRAM_H_WDR_400WP30;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_400WP30;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_400WP30;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_400WP30;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_400WP30;
                vi_attr->u16OffsetX = OFFSET_X_WDR_400WP30;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_400WP30;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_500WP15:
                vi_attr->u16WndWidth = FRAM_W_WDR_500WP15;
                vi_attr->u16WndHeight = FRAM_H_WDR_500WP15;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_500WP15;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_500WP15;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_500WP15;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_500WP15;
                vi_attr->u16OffsetX = OFFSET_X_WDR_500WP15;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_500WP15;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_500WP20:
                vi_attr->u16WndWidth = FRAM_W_WDR_500WP20;
                vi_attr->u16WndHeight = FRAM_H_WDR_500WP20;
                vi_attr->u16InputWidth = ACTIVE_W_WDR_500WP20;
                vi_attr->u16InputHeight = ACTIVE_H_WDR_500WP20;
                vi_attr->u16PicWidth = PIC_IN_W_WDR_500WP20;
                vi_attr->u16PicHeight = PIC_IN_H_WDR_500WP20;
                vi_attr->u16OffsetX = OFFSET_X_WDR_500WP20;
                vi_attr->u16OffsetY = OFFSET_Y_WDR_500WP20;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            default:
		        return FH_ERR_ISP_NO_SUPPORT_FORMAT;
            }
        } else {
            switch (sensor_fmt) {
            case FORMAT_400WP25:  // 400w 25
                vi_attr->u16WndWidth = FRAM_W_400WP25;
                vi_attr->u16WndHeight = FRAM_H_400WP25;
                vi_attr->u16InputWidth = ACTIVE_W_400WP25;
                vi_attr->u16InputHeight = ACTIVE_H_400WP25;
                vi_attr->u16PicWidth = PIC_IN_W_400WP25;
                vi_attr->u16PicHeight = PIC_IN_H_400WP25;
                vi_attr->u16OffsetX = OFFSET_X_400WP25;
                vi_attr->u16OffsetY = OFFSET_Y_400WP25;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_400WP30:  // 400w 30
                vi_attr->u16WndWidth = FRAM_W_400WP30;
                vi_attr->u16WndHeight = FRAM_H_400WP30;
                vi_attr->u16InputWidth = ACTIVE_W_400WP30;
                vi_attr->u16InputHeight = ACTIVE_H_400WP30;
                vi_attr->u16PicWidth = PIC_IN_W_400WP30;
                vi_attr->u16PicHeight = PIC_IN_H_400WP30;
                vi_attr->u16OffsetX = OFFSET_X_400WP30;
                vi_attr->u16OffsetY = OFFSET_Y_400WP30;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_500WP15:  // 500w 15
                vi_attr->u16WndWidth = FRAM_W_500WP15;
                vi_attr->u16WndHeight = FRAM_H_500WP15;
                vi_attr->u16InputWidth = ACTIVE_W_500WP15;
                vi_attr->u16InputHeight = ACTIVE_H_500WP15;
                vi_attr->u16PicWidth = PIC_IN_W_500WP15;
                vi_attr->u16PicHeight = PIC_IN_H_500WP15;
                vi_attr->u16OffsetX = OFFSET_X_500WP15;
                vi_attr->u16OffsetY = OFFSET_Y_500WP15;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            case FORMAT_500WP20:  // 500w 20
                vi_attr->u16WndWidth = FRAM_W_500WP20;
                vi_attr->u16WndHeight = FRAM_H_500WP20;
                vi_attr->u16InputWidth = ACTIVE_W_500WP20;
                vi_attr->u16InputHeight = ACTIVE_H_500WP20;
                vi_attr->u16PicWidth = PIC_IN_W_500WP20;
                vi_attr->u16PicHeight = PIC_IN_H_500WP20;
                vi_attr->u16OffsetX = OFFSET_X_500WP20;
                vi_attr->u16OffsetY = OFFSET_Y_500WP20;
                vi_attr->enBayerType = BAYER_BGGR;
                break;
            default:
		        return FH_ERR_ISP_NO_SUPPORT_FORMAT;
            }
        }
    } else {
        switch (sensor_fmt) {
        case FORMAT_400WP20:  // 400w 20
            vi_attr->u16WndWidth = FRAM_W_400WP20;
            vi_attr->u16WndHeight = FRAM_H_400WP20;
            vi_attr->u16InputWidth = ACTIVE_W_400WP20;
            vi_attr->u16InputHeight = ACTIVE_H_400WP20;
            vi_attr->u16PicWidth = PIC_IN_W_400WP20;
            vi_attr->u16PicHeight = PIC_IN_H_400WP20;
            vi_attr->u16OffsetX = OFFSET_X_400WP20;
            vi_attr->u16OffsetY = OFFSET_Y_400WP20;
            vi_attr->enBayerType = BAYER_BGGR;
            break;
        case FORMAT_500W12P5:  // 500w 12
            vi_attr->u16WndWidth = FRAM_W_500W12P5;
            vi_attr->u16WndHeight = FRAM_H_500W12P5;
            vi_attr->u16InputWidth = ACTIVE_W_500W12P5;
            vi_attr->u16InputHeight = ACTIVE_H_500W12P5;
            vi_attr->u16PicWidth = PIC_IN_W_500W12P5;
            vi_attr->u16PicHeight = PIC_IN_H_500W12P5;
            vi_attr->u16OffsetX = OFFSET_X_500W12P5;
            vi_attr->u16OffsetY = OFFSET_Y_500W12P5;
            vi_attr->enBayerType = BAYER_BGGR;
            break;
        default:
		    return FH_ERR_ISP_NO_SUPPORT_FORMAT;
        }
    }

    return 0;
}

static void SensorReset(void) {
    return;
}

static int GetSensorGain(FH_UINT32 *u32Gain) {  // gain U10.6
    *u32Gain = curr_sensor_gain;
    return 0;
}

static int SetSensorGain(FH_UINT32 gain) {  // gain U10.6
    curr_sensor_gain = gain;
    FH_UINT8  Reg3508, Reg3509, Reg350a, Reg350b;
    FH_UINT32  d_gain;

    gain = gain << 1;  // U.6 -> U.7
    if (gain <= 0x80) {  // 1x
        Reg3508 = 0x00;
        Reg3509 = 0x80;
        Reg350a = 0x04;
        Reg350b = 0x00;
    } else if (gain <= 0x7ff) {  // 1X~16X a_gain
        Reg3508 = (gain >> 8) & 0xff;
        Reg3509 = gain & 0xff;
        Reg350a = 0x04;
        Reg350b = 0x00;
    } else if (gain > 0x7ff) {
        Reg3508 = 0x07;
        Reg3509 = 0xff;
        d_gain = (gain << 10) / 0x7ff;  // U.7~U.10
        if (d_gain > 0x3fff) {
            d_gain = 0x3fff;
        }
        Reg350a = (d_gain >> 8) & 0xff;
        Reg350b = d_gain & 0xff;
    }
    Sensor_Write(0x3508, Reg3508);
    Sensor_Write(0x3509, Reg3509);
    Sensor_Write(0x350a, Reg350a);
    Sensor_Write(0x350b, Reg350b);

    return 0;
}

static int GetSensorIntt(FH_UINT32 *intt) {
    *intt = long_exposure_intt;
    return 0;
}

static int SetSensorIntt(FH_UINT32 intt) {
    /****** Set Intt_LEF ******/
    FH_UINT32 Reg3501, Reg3502;
    // intt>>=4;
    Reg3501 = (intt >> 8) & 0xff;
    Reg3502 = intt & 0xff;
    Sensor_Write(0x3501, Reg3501);
    Sensor_Write(0x3502, Reg3502);

    long_exposure_intt = intt;

    return 0;
}

int Set_r_shtpos_intt(FH_UINT32 intt)
{
    FH_UINT32 intt_h, intt_l;

    // intt = MAX(1, intt);

    intt_h = (intt >> 8) & 0xff;
    intt_l = intt & 0xff;

    Sensor_Write(0x3511, intt_h);
    Sensor_Write(0x3512, intt_l);

    return 0;
}

static int SetExposureRatio(FH_UINT32 exposure_ratio)
{
    FH_UINT32 r_shtpos_intt;
    FH_UINT32 cur_r_coarse_intt;

    cur_r_coarse_intt = long_exposure_intt;

    r_shtpos_intt = ((cur_r_coarse_intt<<4) + (exposure_ratio>>1)) / exposure_ratio;
    r_shtpos_intt = MAX(1, r_shtpos_intt);

    Set_r_shtpos_intt(r_shtpos_intt);
    // curr_exposure_ratio=exposure_ratio;
	curr_exposure_ratio = (long_exposure_intt<<4)/r_shtpos_intt;

	return 0;
}

static int GetExposureRatio(FH_UINT32 *exposure_ratio)
{
    *exposure_ratio=curr_exposure_ratio;
    return 0;
}


static int SetSensorFrameHeight(FH_UINT32 multiple) {
    return 0;
}

static int Sensor_Init(void) {
    SensorDevice_Init((0x6c>>1), 2);
    SensorReset();
    return 0;
}

static int Sensor_DeInit(void) {
    SensorReset();

    return SensorDevice_Close();
}

static void SetSensorMipiCfg(void)
{
    struct mipi_conf config;
    config.raw_type = RAW10;
    config.sensor_mode = NOT_SONY_WDR_USE_WDR;

    if (wdr_flag) {
        config.lf_vc_id = 0;
        config.sf_vc_id = 1;
        config.lane_num = 4;
        config.frq_range = R_900_949;

        switch (sensor_fmt) {
        case FORMAT_1536P40:
            config.frq_range = R_950_999;
            break;
        default:
            break;
        }

    } else {
        config.lf_vc_id = 0;
        config.sf_vc_id = 0;
        if (chip_idx == 1) {
            config.lane_num = 4;
            config.frq_range = R_500_549;
        } else {
            config.lane_num = 2;
            config.frq_range = R_900_949;
        }
        switch (sensor_fmt) {
        case FORMAT_500WP15:
        case FORMAT_500WP20:
            config.frq_range = R_950_999;
            break;
        default:
            break;
        }
    }

    mipi_init(&config);
    return;
}

static int SetSensorFmt(int format) {
    SensorDevice_Close();

    sensor_fmt = format&0xffff;
    wdr_flag   = (format>>16)&1;

    SetSensorMipiCfg();
    SensorDevice_Init((0x6c>>1), 2);
    SensorReset();

    curr_sensor_gain = 0x40;

    long_exposure_intt = 0x6f;

    inited = 1;
    //Sensor_Write(0x0100,0x00);
    //usleep(100000);

    if (inited) {
        int i;
        if (chip_idx == 1) {
            if (wdr_flag == 1) {
                switch(sensor_fmt)
                {
                case FORMAT_500W12P5:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_500W12P5)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_500W12P5[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_500W12P5[2*i+1]);
                    }
                    break;
                case FORMAT_1536P25:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_1536P25)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_1536P25[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_1536P25[2*i+1]);
                    }
                    break;
                case FORMAT_1536P30:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_1536P30)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_1536P30[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_1536P30[2*i+1]);
                    }
                    break;
                case FORMAT_1536P40:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_1536P40)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_1536P40[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_1536P40[2*i+1]);
                    }
                    break;
                    case FORMAT_400WP25:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_400WP25)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_400WP25[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_400WP25[2*i+1]);
                        usleep(200);
                    }
                    break;
                case FORMAT_400WP30:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_400WP30)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_400WP30[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_400WP30[2*i+1]);
                    }
                    break;
                case FORMAT_500WP15:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_500WP15)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_500WP15[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_500WP15[2*i+1]);
                    }
                    break;
                case FORMAT_500WP20:
                    for(i=0; i<sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_500WP20)/4; i++)
                    {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_WDR_500WP20[2*i], Sensor_Cfg_OVOS05_MIPI_WDR_500WP20[2*i+1]);
                    }
                    break;
                default:
                    return -1;
                }
            } else {
                switch (sensor_fmt) {
                case FORMAT_400WP25:
                    for (i = 0; i < sizeof(Sensor_Cfg_OVOS05_MIPI_400WP25)/4; i++) {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_400WP25[2*i], Sensor_Cfg_OVOS05_MIPI_400WP25[2*i+1]);
                        usleep(200);
                    }
                    break;
                case FORMAT_400WP30:
                    for (i = 0; i < sizeof(Sensor_Cfg_OVOS05_MIPI_400WP30)/4; i++) {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_400WP30[2*i], Sensor_Cfg_OVOS05_MIPI_400WP30[2*i+1]);
                    }
                    break;
                case FORMAT_500WP15:
                    for (i = 0; i < sizeof(Sensor_Cfg_OVOS05_MIPI_500WP15)/4; i++) {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_500WP15[2*i], Sensor_Cfg_OVOS05_MIPI_500WP15[2*i+1]);
                    }
                    break;
                case FORMAT_500WP20:
                    for (i = 0; i < sizeof(Sensor_Cfg_OVOS05_MIPI_500WP20)/4; i++) {
                        Sensor_Write(Sensor_Cfg_OVOS05_MIPI_500WP20[2*i], Sensor_Cfg_OVOS05_MIPI_500WP20[2*i+1]);
                    }
                    break;
                default:
                    return -1;
                }
            }
        } else {
            switch (sensor_fmt) {
            case FORMAT_400WP20:
                for (i = 0; i < sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP20)/4; i++) {
                    Sensor_Write(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP20[2*i], Sensor_Cfg_OVOS05_MIPI_2LANE_400WP20[2*i+1]);
                }
                break;
            case FORMAT_500W12P5:
                for (i = 0; i < sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_500W12P5)/4; i++) {
                    Sensor_Write(Sensor_Cfg_OVOS05_MIPI_2LANE_500W12P5[2*i], Sensor_Cfg_OVOS05_MIPI_2LANE_500W12P5[2*i+1]);
                }
                break;
            default:
                return -1;
            }
        }
        usleep(100000);
        Sensor_Write(0x0100,0x01);
        //usleep(100000);
    }

    return 0;
}

static int GetSensorAttribute(char * name, FH_UINT32 *value)
{
    if (strcmp(name, "WDR") == 0) {
        *value = wdr_flag;
        return 0;
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
    FH_UINT8 tmp1, tmp2;
    FH_UINT8 flip, mirror;

    flip = sensor_en_stat & 0x1;
    mirror = !(((sensor_en_stat >> 1)) & 0x1);

    tmp1 = Sensor_Read(0x3820);
    tmp2 = Sensor_Read(0x3821);

    tmp1 = (tmp1&0xfb) | (flip << 2);
    tmp2 = (tmp2&0xfb) | (mirror << 2);

    Sensor_Write(0x3820, tmp1);
    Sensor_Write(0x3821, tmp2);

    return 0;
}
static int GetSensorFlipMirror(FH_UINT32 *sensor_en_stat)
{
    FH_UINT8 mirror, flip;

    flip = (Sensor_Read(0x3820))>>2 & 0x1;
    mirror = !((Sensor_Read(0x3821))>>2 & 0x1);
    *sensor_en_stat = (mirror << 1) | flip;

    return 0;
}

FH_UINT32* NAME(GetDefaultParam)() {
    if (wdr_flag)
        return NAME(ImageParamWdr);
    else
        return NAME(ImageParam);
}

FH_UINT32* NAME(GetContrast)() {
    if (wdr_flag)
        return NAME(contrastWdr);
    else
        return NAME(contrast);
}

FH_UINT32* NAME(GetSaturation)() {
    if (wdr_flag)
        return NAME(saturationWdr);
    else
        return NAME(saturation);
}

FH_UINT32* NAME(GetSharpness)() {
    if (wdr_flag)
        return NAME(sharpnessWdr);
    else
        return NAME(sharpness);
}


FH_UINT32 NAME(*GetMirrorFlipBayerFormat)() {
    if (wdr_flag)
        return NAME(MirrorFlipBayerFormatWdr);
    else
        return NAME(MirrorFlipBayerFormat);
}

FH_UINT32* NAME(GetSensorAwbGain)(int idx) {
    if (wdr_flag)
        return NAME(AwbGainWdr)[idx];
    else
        return NAME(AwbGain)[idx];

}

FH_UINT32* NAME(GetSensorLtmCurve)(int idx) {
    if (!wdr_flag) {
        switch (idx) {
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
        }
        return NAME(LtmMapping00);
    }
    return 0;
}

#if MULTI_SENSOR
static int Sensor_Isconnect(void)
{
    unsigned int sensor_chip_id;
    SensorDevice_Init((0x6c>>1), 2);

    sensor_chip_id = Sensor_Read(0x300c);
    sensor_chip_id |= Sensor_Read(0x300b) << 8;
    sensor_chip_id |= Sensor_Read(0x300a) << 16;

    SensorDevice_Close();

    if (sensor_chip_id == 0x530541)
        return 1;
    else
    {
        return 0;
    }
}
#endif

#define SENSOR_OVOS05_MIPI    "ovos05_mipi"
struct isp_sensor_if ovos05_mipi;

struct isp_sensor_if* NAME(Sensor_Create)() {
#if MULTI_SENSOR
    if (!Sensor_Isconnect())
        return 0;
#endif
    memset(&ovos05_mipi, 0, sizeof(struct isp_sensor_if));
    ovos05_mipi.name = SENSOR_OVOS05_MIPI;
    ovos05_mipi.init = Sensor_Init;
    ovos05_mipi.get_vi_attr = GetSensorViAttr;
    ovos05_mipi.set_sns_fmt = SetSensorFmt;
    ovos05_mipi.set_gain = SetSensorGain;
    ovos05_mipi.get_gain = GetSensorGain;
    ovos05_mipi.reset    = SensorReset;
    ovos05_mipi.get_intt = GetSensorIntt;
    ovos05_mipi.set_intt = SetSensorIntt;
    ovos05_mipi.set_sns_reg = SetSensorReg;
    ovos05_mipi.set_frame_height = SetSensorFrameHeight;
    ovos05_mipi.set_flipmirror = SetSensorFlipMirror;
    ovos05_mipi.get_flipmirror = GetSensorFlipMirror;
    ovos05_mipi.deinit   = Sensor_DeInit;
    ovos05_mipi.set_exposure_ratio = SetExposureRatio;
    ovos05_mipi.get_exposure_ratio = GetExposureRatio;
    ovos05_mipi.set_chip_id = SetIspChipId;
    ovos05_mipi.get_sensor_attribute = GetSensorAttribute;
    ovos05_mipi.get_sns_reg = GetSensorReg;

    return &ovos05_mipi;
}

void NAME(Sensor_Destory)(struct isp_sensor_if* s_if) {
    ovos05_mipi.name = 0;
    ovos05_mipi.init = 0;
    ovos05_mipi.get_vi_attr = 0;
    ovos05_mipi.set_sns_fmt = 0;
    ovos05_mipi.set_gain = 0;
    ovos05_mipi.get_gain = 0;
    ovos05_mipi.reset    = 0;
    ovos05_mipi.get_intt = 0;
    ovos05_mipi.set_intt = 0;
    ovos05_mipi.set_sns_reg = 0;
    ovos05_mipi.set_frame_height = 0;
    ovos05_mipi.set_flipmirror = 0;
    ovos05_mipi.get_flipmirror = 0;
    ovos05_mipi.deinit   = 0;
    ovos05_mipi.set_exposure_ratio = 0;
    ovos05_mipi.get_exposure_ratio = 0;
    ovos05_mipi.set_chip_id = 0;
    ovos05_mipi.get_sensor_attribute = 0;
    ovos05_mipi.get_sns_reg = 0;

}
