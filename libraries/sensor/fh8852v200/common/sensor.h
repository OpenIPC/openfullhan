#ifndef __SENSOR_H__
#define __SENSOR_H__

typedef struct
{
    FH_UINT32 sns_fmt;  // 该配置的制式
    FH_UINT32 conf_size;  // 该配置的大小
    const FH_UINT16 *conf_addr; // 配置指向的初始化数组
    FH_UINT8 mipi_clk_rate;  // 该配置的mipi时钟频率
    FH_UINT8 mipi_lane_num;  // 该配置的mipilane数
    ISP_VI_ATTR_S *sns_attr;  // 该配置的幅面相关的配置
}SensorConfig;

typedef struct
{
    SensorConfig *conf;
    FH_UINT8 conf_size;
}SensorConfigPtr;

struct sns_cfg_s {
    FH_BOOL inited;        // sensor初始化
    FH_UINT32 maxLaneNum;  // sensor的mipi配置不能超过最大支持的lane数目
    FH_UINT32 sensor_fmt;  // sensor输出制式
    FH_UINT32 v_cycle;     // sensor框架高
    FH_UINT32 wdr_flag;    // sensor是否是wdr输出
    FH_UINT32 curr_sensor_gain;        // 当前sensor增益
    FH_UINT32 curr_sensor_intt;        // 当前sensor长曝光时间
    FH_UINT32 curr_sensor_short_intt;  // 当前sensor短曝光时间
    FH_UINT32 curr_exposure_ratio;     // 当前sensor曝光比

    FH_UINT32 curr_hsf;    // 当前sensor行频
    FH_UINT32 max_intt;    // sensor最大曝光时间(非降帧时)
    FH_UINT32 minAGain;    // 最小曝光增益,U.6精度
    FH_UINT32 fullLineStd; // sensor框架高度(非降帧时)
    FH_UINT32 MinRstLine;  // 计算最大曝光时间时的最小复位行数
    FH_SINT8 sns_conf_num;  // 当前使用的sensor配置的序号
};

#endif // __SENSOR_H__
