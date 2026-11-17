/*
 * ovos05_mipi.c
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "isp_func_def.h"
#include "clock_ops.h"

#include "isp_sensor_if.h"
#include "sensor_ops.h"

#include "isp_enum.h"
#include "mipi_api.h"
#include "ovos05_mipi_param.h"
#include "ovos05_mipi_wdr_param.h"
#include "sensor.h"
#include "ovos05_mipi.h"

static struct sns_cfg_s sns_cfg = {
    .inited = 0,
    .curr_exposure_ratio = 256,  // 默认初始化为16倍
    .MinRstLine = 5,
    .minAGain = 0x40,
};


static int SetIntt(FH_UINT32 intt, FH_UINT8 fNo);
static int GetIntt();
static int SetGain(FH_UINT32 again, FH_UINT8 fNo);
static int GetGain();
static int SetExposureRatio(FH_UINT32 exposure_ratio);
static int GetExposureRatio(FH_UINT32 *exposure_ratio);
/********************sensor flow related start****************************/
static void SensorReset(void)
{
    return;
}

static int Sensor_Init(void)
{
    SensorDevice_Init((0x6c >> 1), 2);
    SensorReset();
    sns_cfg.inited = 1;
    return 0;
}

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

static int Sensor_DeInit(void)
{
    SensorReset();

    return SensorDevice_Close();
}

static void SetSensorMipiCfg(void)
{
    struct mipi_conf config;
    config.frq_range = current_sns_conf.mipi_clk_rate;
    config.sensor_mode = NOT_SONY_WDR_USE_WDR;
    config.raw_type = RAW10;
    config.lane_num = current_sns_conf.mipi_lane_num;

    if (sns_cfg.wdr_flag == 1)
    {
        config.lf_vc_id = 0;
        config.sf_vc_id = 1;
    }
    else
    {
        config.lf_vc_id = 0;
        config.sf_vc_id = 0;
    }

    mipi_init(&config);
    return;
}

static int SetLaneNumMax(FH_UINT32 lane_num)
{
#ifdef FPGA_ENV
    sns_cfg.maxLaneNum = 4;
#else
    sns_cfg.maxLaneNum = lane_num;
#endif
    return 0;
}

static int getSensorConfType(void)
{
    sns_conf.conf = sns_conf0;
    sns_conf.conf_size = sizeof(sns_conf0) / sizeof(SensorConfig);

    return 0;
}

static int getSensorConf(void)
{
    int i;

    getSensorConfType();

    for (i = 0; i < sns_conf.conf_size; i++)
    {
        if (sns_cfg.sensor_fmt == sns_conf.conf[i].sns_fmt)
        {
            if (sns_cfg.maxLaneNum >= sns_conf.conf[i].mipi_lane_num)
            {
                return i;
            }
        }
    }

    return -1;
}


static int GetSensorViAttr(ISP_VI_ATTR_S *vi_attr)
{
    if (vi_attr == NULL)
        return FH_ERR_NULL_POINTER;

    if (current_sns_attr == NULL)
        sns_cfg.sns_conf_num = getSensorConf();

    vi_attr->u16WndWidth = current_sns_attr->u16WndWidth;
    vi_attr->u16WndHeight = current_sns_attr->u16WndHeight;
    vi_attr->u16InputWidth = current_sns_attr->u16InputWidth;
    vi_attr->u16InputHeight = current_sns_attr->u16InputHeight;
    vi_attr->u16PicWidth = current_sns_attr->u16PicWidth;
    vi_attr->u16PicHeight = current_sns_attr->u16PicHeight;
    vi_attr->u16OffsetX = current_sns_attr->u16OffsetX;
    vi_attr->u16OffsetY = current_sns_attr->u16OffsetY;
    vi_attr->enBayerType = current_sns_attr->enBayerType;

    if (current_sns_attr->u16FrameRate == 12)
        sns_cfg.curr_hsf = 25 * vi_attr->u16WndHeight / 2;
    else
        sns_cfg.curr_hsf = current_sns_attr->u16FrameRate * vi_attr->u16WndHeight;

    return 0;
}

//可根据sns_cfg.max_lane_num确定当前使用2lane配置还是4lane配置
static int SetSensorFmt(int format)
{
    SensorDevice_Close();
    sns_cfg.sensor_fmt = format;
    sns_cfg.wdr_flag = (format >> 16) & 1;

    SensorDevice_Init((0x6c>>1), 2);
    SensorReset();

    if (sns_cfg.inited)
    {
        int i;

        sns_cfg.sns_conf_num = getSensorConf();

        if (sns_cfg.sns_conf_num < 0)
            return FH_ERR_ISP_NO_SUPPORT_FORMAT;

        SetSensorMipiCfg();

        for (i = 0; i < current_sns_conf.conf_size; i++)
        {
            Sensor_Write(current_sns_conf.conf_addr[2 * i], current_sns_conf.conf_addr[2 * i + 1]);
        }

        Sensor_Write(0x0100,0x01);
    }
    else
        return -1;

    sns_cfg.v_cycle = (Sensor_Read(0x380e) << 8) | (Sensor_Read(0x380f));
    sns_cfg.fullLineStd = sns_cfg.v_cycle;

    if (sns_cfg.wdr_flag == 0)
    {
        sns_cfg.MinRstLine = 5;
    }
    else
    {
        sns_cfg.MinRstLine = sns_cfg.v_cycle / 7 + 5;
    }
    sns_cfg.max_intt = sns_cfg.v_cycle - sns_cfg.MinRstLine;
    SetIntt(sns_cfg.max_intt, 0);
    SetExposureRatio(sns_cfg.curr_exposure_ratio);
    SetGain(sns_cfg.minAGain, 0);
    sns_cfg.curr_sensor_gain = sns_cfg.minAGain;

    return 0;
}
/********************sensor flow related end*************************************/

/************************AE&WDR Related start************************************/
static int GetAEInfo(Sensor_AE_INFO_S *sensAEInfo)
{
    sensAEInfo->currIntt = GetIntt();
    sensAEInfo->currAGain = GetGain();
    sensAEInfo->currHsf = sns_cfg.curr_hsf;
    sensAEInfo->currFrameH = sns_cfg.v_cycle;
    return 0;
}

static int GetAEDefault(Sensor_AE_Default_S *sensAEDefault)
{
    sensAEDefault->minIntt = 1;
    sensAEDefault->maxIntt = sns_cfg.max_intt;
    sensAEDefault->minAGain = sns_cfg.minAGain;
    sensAEDefault->maxAGain = 0x3ff7;
    sensAEDefault->fullLineStd = sns_cfg.fullLineStd;
    sensAEDefault->MinRstLine = sns_cfg.MinRstLine;

    return 0;
}

// GetGain仅在ae refresh时会重新获取,所以尽量直接从sensor端获取,保证intt的正确性
static int GetGain()
{
    int gain, again, dgain, Reg3508, Reg3509, Reg350a, Reg350b;
    Reg3508 = Sensor_Read(0x3508) & 0xff;
    Reg3509 = Sensor_Read(0x3509) & 0xff;
    Reg350a = Sensor_Read(0x350a) & 0xff;
    Reg350b = Sensor_Read(0x350b) & 0xff;

    dgain = ((Reg350a << 8) | Reg350b);  // U.10
    again = ((Reg3508 << 8) | Reg3509);  // U.7

    gain = (dgain * again) >> 11;  // U.17->U.6

    return gain;
}

static int CalcSnsValidGain(FH_UINT32 *u32Gain)
{
    return 0;
}


static int SetGain(FH_UINT32 again, FH_UINT8 fNo) {
    FH_UINT8  Reg3508, Reg3509, Reg350a, Reg350b;
    FH_UINT32  d_gain;

    again = again << 1;  // U.6 -> U.7
    if (again <= 0x80) {  // 1x
        Reg3508 = 0x00;
        Reg3509 = 0x80;
        Reg350a = 0x04;
        Reg350b = 0x00;
    } else if (again <= 0x7ff) {  // 1X~16X a_gain
        Reg3508 = (again >> 8) & 0xff;
        Reg3509 = again & 0xff;
        Reg350a = 0x04;
        Reg350b = 0x00;
    } else if (again > 0x7ff) {
        Reg3508 = 0x07;
        Reg3509 = 0xff;
        d_gain = (again << 10) / 0x7ff;  // U.7~U.10
        if (d_gain > 0x3fff) {
            d_gain = 0x3fff;
        }
        Reg350a = (d_gain >> 8) & 0xff;
        Reg350b = d_gain & 0xff;
    }

    if (fNo == 0) {
        Sensor_Write(0x3508, Reg3508);
        Sensor_Write(0x3509, Reg3509);
        Sensor_Write(0x350a, Reg350a);
        Sensor_Write(0x350b, Reg350b);
        if (sns_cfg.wdr_flag ) {
            Sensor_Write(0x350c, Reg3508);
            Sensor_Write(0x350d, Reg3509);
            Sensor_Write(0x350e, Reg350a);
            Sensor_Write(0x350f, Reg350b);
        }
    }

    return 0;
}

// GetIntt仅在ae refresh时会重新获取,所以尽量直接从sensor端获取,保证intt的正确性
static int GetIntt()
{
    int intt, Reg3501, Reg3502;
    Reg3501 = Sensor_Read(0x3501) & 0xff;
    Reg3502 = Sensor_Read(0x3502) & 0xff;
    intt = (Reg3501<<8)|Reg3502;
    return intt;
}

static int CalcSnsValidIntt(FH_UINT32 *u32Intt)
{
    return 0;
}

static int Set_short_exp_intt(FH_UINT32 intt)
{
    FH_UINT32 intt_h, intt_l;

    intt_h = (intt >> 8) & 0xff;
    intt_l = intt & 0xff;

    Sensor_Write(0x3511, intt_h);
    Sensor_Write(0x3512, intt_l);
    sns_cfg.curr_sensor_short_intt = intt;
    return 0;
}

static int SetIntt(FH_UINT32 intt, FH_UINT8 fNo)
{
    if (fNo == 0) {  // first frame
        FH_UINT32 intt_h, intt_l;

        intt_h = (intt >> 8) & 0xff;
        intt_l = intt & 0xff;
        Sensor_Write(0x3501, intt_h);
        Sensor_Write(0x3502, intt_l);
        sns_cfg.curr_sensor_intt = intt;
        if(sns_cfg.wdr_flag)
        {
            FH_UINT32 short_exp_intt;
            short_exp_intt = MAX(1, ((MIN(intt, sns_cfg.max_intt) << 4) + (sns_cfg.curr_exposure_ratio >> 1)) / sns_cfg.curr_exposure_ratio);
            Set_short_exp_intt(short_exp_intt);
        }
    }
    return 0;
}

static int SetSnsFrameH(FH_UINT32 frameH) {
    Sensor_Write(0x380e, frameH>>8);
    Sensor_Write(0x380f, frameH&0xff);
    sns_cfg.v_cycle = frameH;

    return 0;
}

static int SetExposureRatio(FH_UINT32 exposure_ratio)
{
    sns_cfg.curr_exposure_ratio = exposure_ratio;
    return 0;
}

static int GetExposureRatio(FH_UINT32 *exposure_ratio)
{
    *exposure_ratio = (sns_cfg.curr_sensor_intt  << 4) / MAX(1, sns_cfg.curr_sensor_short_intt);
    return 0;
}
/************************AE&WDR Related End************************************/

/************************sensor attr related start*****************************/
static int GetSensorAttribute(char * name, FH_UINT32 *value)
{
    if (strcmp(name, "WDR") == 0) {
        *value = sns_cfg.wdr_flag;
        return 0;
    }

    return -1;
}
/************************sensor attr related end*******************************/

/***********************fastboot related start*********************************/
static int Sensor_Kick()
{
    if (sns_cfg.inited)
    {
        // enable sensor output
    }
    return 0;
}
/***********************fastboot related end**********************************/

/************************sensor func related start****************************/
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

static int SensorCommonIf(FH_UINT32 cmd, ISP_SENSOR_COMMON_CMD_DATA0* data0, ISP_SENSOR_COMMON_CMD_DATA1* data1)
{
    int ret = -1;
    return ret;
}
/***********************sensor func related end**********************************/

/***********************adv api related start************************************/
static FH_UINT32* GetMirrorFlipBayerFormat(void){return 0;}
static FH_UINT32* GetUserSensorAwbGain(FH_UINT32 idx)
{
    if(sns_cfg.wdr_flag)
        return (AwbGainWdr)[idx];
    else
        return (AwbGain)[idx];
}
static FH_UINT32* GetSensorLtmCurve(FH_UINT32 idx)
{
    if (!sns_cfg.wdr_flag)
    {
        switch (idx)
        {
        case 0:
            return (LtmMapping00);
            break;
        case 1:
            return (LtmMapping01);
            break;
        case 2:
            return (LtmMapping02);
            break;
        case 3:
            return (LtmMapping03);
            break;
        case 4:
            return (LtmMapping04);
            break;
        case 5:
            return (LtmMapping05);
            break;
        case 6:
            return (LtmMapping06);
            break;
        case 7:
            return (LtmMapping07);
            break;
        case 8:
            return (LtmMapping08);
            break;
        case 9:
            return (LtmMapping09);
            break;
        case 10:
            return (LtmMapping10);
        }
        return (LtmMapping00);
    }
    return 0;
}
/***********************adv api related end*************************************/

/***********************not used for now start**********************************/
static int SetSensorAwbGain(FH_UINT32 *awb_gain){return 0;}
static int GetSensorAwbGain(FH_UINT32 *awb_gain){return 0;}
static int SetSensorIris(FH_UINT32 iris){return 0;}
/***********************not used for now end************************************/

#define SENSOR_OVOS05_MIPI    "ovos05_mipi"
#ifdef OS_RTT
struct isp_sensor_if ovos05_mipi_sensor_if __attribute__((section(".sensor_drv"))) = {
#else
struct isp_sensor_if ovos05_mipi_sensor_if = {
#endif
    .name = SENSOR_OVOS05_MIPI,
    .get_vi_attr = GetSensorViAttr,
    .set_flipmirror = SetSensorFlipMirror,
    .get_flipmirror = GetSensorFlipMirror,
    .set_iris = SetSensorIris,
    .init = Sensor_Init,
    .reset = SensorReset,
    .deinit = Sensor_DeInit,
    .set_sns_fmt = SetSensorFmt,
    .kick = Sensor_Kick,
    .set_sns_reg = SetSensorReg,
    .set_exposure_ratio = SetExposureRatio,
    .get_exposure_ratio = GetExposureRatio,
    .get_sensor_attribute = GetSensorAttribute,
    .set_lane_num_max = SetLaneNumMax,
    .get_sns_reg = GetSensorReg,
    .get_awb_gain = GetSensorAwbGain,
    .set_awb_gain = SetSensorAwbGain,
    .data = 0,
    .common_if = SensorCommonIf,
    .get_sns_ae_default = GetAEDefault,
    .get_sns_ae_info = GetAEInfo,
    .set_sns_intt  = SetIntt,
    .calc_sns_valid_intt = CalcSnsValidIntt,
    .set_sns_gain = SetGain,
    .calc_sns_valid_gain = CalcSnsValidGain,
    .set_sns_frame_height = SetSnsFrameH,
    .get_sensor_mirror_flip_bayer_format = GetMirrorFlipBayerFormat,
    .get_user_awb_gain = GetUserSensorAwbGain,
    .get_user_ltm_curve = GetSensorLtmCurve,
    .is_sensor_connect = Sensor_Isconnect,
};

#ifdef OS_RTT
#else
struct isp_sensor_if* (Sensor_Create)() {
    return &ovos05_mipi_sensor_if;
}

void (Sensor_Destroy)(struct isp_sensor_if* s_if) {
    memset(&ovos05_mipi_sensor_if, 0, sizeof(struct isp_sensor_if));
}
#endif
