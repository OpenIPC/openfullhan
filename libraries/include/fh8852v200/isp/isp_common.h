#ifndef _ISP_COMMON_H_
#define _ISP_COMMON_H_

#include "types/type_def.h"
#include "types/bufCtrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
#pragma pack(4)

#define MALLOCED_MEM_BASE_ISP (0)

#define MALLOCED_MEM_ISPPPKG (0)
#define MALLOCED_MEM_ISPFPKG (1)
#define MALLOCED_MEM_ISPFPKG_L (2)
#define MALLOCED_MEM_ISPFPKG_L2 (4)
#define MALLOCED_MEM_ISPFPKG_L3 (5)

#define MALLOCED_MEM_DRV (3)

#define GAIN_NODES 12


typedef int (*ispInitCfgCallback)(void);
typedef int (*ispIntCallback)(void);
void ispTrace_FunctionName(const char* func);

/**|SYSTEM CONTROL|**/
typedef enum _ISP_BAYER_TYPE_S_ {
    BAYER_RGGB = 0x0, // 色彩模式RGGB
    BAYER_GRBG = 0x1, // 色彩模式GRBG
    BAYER_BGGR = 0x2, // 色彩模式BGGR
    BAYER_GBRG = 0x3, // 色彩模式GBRG
    ISP_BAYER_TYPE_DUMMY=0xffffffff,
} ISP_BAYER_TYPE;

typedef enum _TAB_COLOR_CODE {
    CC_R  = 0,
    CC_GR = 1,
    CC_B  = 2,
    CC_GB = 3,
    TAB_COLOR_CODE_DUMMY =0xffffffff,
} TAB_COLOR_CODE;

typedef enum _CURVE_TYPE_ {
    CURVE_BUILTIN     = 0x1, // 选用内定曲线
    CURVE_USER_DEFINE = 0x2, // 选用用户自定义曲线
    CURVE_TYPE_DUMMY  =0xffffffff,
} CURVE_TYPE;

typedef enum _FRAME_TYPE_ {
    FRAME_LINEAR = 0x0,
    FRAME_WDR_SHORT = 0x1,
    FRAME_WDR_LONG  = 0x2,
    FRAME_WDR_MERGED = 0x3,
} FRAME_TYPE;

typedef struct _HW_MODULE_CFG_S{
    FH_UINT32 moduleCfg;  // 需要配置的模块 | [ISP_HW_MODULE_LIST]
    FH_BOOL enable;  // 使能开关,0表示关闭,1表示打开 | [0~1]
} HW_MODULE_CFG;

typedef struct _ISP_VERSION_S_
{
    FH_UINT32 u32SdkVer;        // sdk版本号 | [0~0xffffffff]
    FH_UINT32 FH_UINT32ChipVer; // 芯片版本号 | [0~0xffffffff]
    FH_UINT8  u08SdkSubVer;     // sdk sub版本号 | [0~0xff]
    FH_UINT8  u08BuildTime[21]; // sdk构建时间 | [0~0xff]
} ISP_VERSION;

typedef struct _ISP_VI_ATTR_
{
    FH_UINT16      u16WndHeight;   ///<sensor幅面高度 | [0~0xffff]
    FH_UINT16      u16WndWidth;    /// <sensor幅面宽度 | [0~0xffff]
    FH_UINT16      u16InputHeight; ///<sensor输入图像高度 | [0~0x1fff]
    FH_UINT16      u16InputWidth;  ///<sensor输入图像宽度 | [0~0x1fff]
    FH_UINT16      u16OffsetX;     ///<裁剪水平偏移 | [0~0xfff]
    FH_UINT16      u16OffsetY;     ///<裁剪垂直偏移 | [0~0xfff]
    FH_UINT16      u16PicHeight;   ///<处理的图像高度 | [0~0x1fff]
    FH_UINT16      u16PicWidth;    ///<处理的图像宽度 | [0~0x1fff]
    FH_UINT16      u16FrameRate;   ///<帧率 | [0~0xffff]
    ISP_BAYER_TYPE enBayerType;    ///bayer数据格式 | [0~0x3]
} ISP_VI_ATTR_S;

typedef struct _ISP_VI_STAT_S
{
    FH_UINT32 u32IPBIntCnt;   // IPB中断计数 | [0~0xffffffff]
    FH_UINT32 u32IPFIntCnt;   // IPF中断计数 | [0~0xffffffff]
    FH_UINT32 u32FrmRate;     // 当前帧率 | [0~0xffffffff]
    FH_UINT32 u32PicWidth;    // 当前处理图像宽度 | [0~0xffffffff]
    FH_UINT32 u32PicHeight;   // 当前处理图像高度 | [0~0xffffffff]
    FH_UINT32 u32IpfOverFlow; // ISP Vi溢出中断计数 | [0~0xffffffff]
    FH_UINT32 u32IspErrorSt;  // 出错标志，Vi溢出终端计数大于阈值会被值1 | [0~1]
} ISP_VI_STAT_S;

typedef struct _ISP_VIGEN_CFG_S
{
    FH_BOOL   bViGenEn;     // VIGEN使能 0：关闭 1：打开。| [0~1]
    FH_UINT32 u32ViAddr;    //线性图像（或者wdr合成后的图像）导入到ddr空间的起始地址,大小计算方式：1.非合成的短（长）帧为长×宽×1.5;2合成后的为长x宽×2| [0~0xffffffff]
    FH_UINT32 u32LfViAddr;  //长帧图像导入到ddr空间的起始地址，大小计算方式：长帧为长×宽×1.5| [0~0xffffffff]
    FH_UINT32 u32PicWidth;  // 图像宽度 | [0~0xffffffff]
    FH_UINT32 u32PicHeight; // 图像高度 | [0~0xffffffff]
    FH_UINT32 u32FrameWidth;// 框架宽度 | [0~0xffffffff]
    FH_UINT32 u32FrameHeight;// 框架高度 | [0~0xffffffff]
    ISP_BAYER_TYPE  enBayerType;// bayer数据格式 | [0~0x3]
    FH_UINT8  u08InputMode; // 模式选择 0.线性（短帧）模式 1.长短两帧帧输入模式 2.wdr合成后数据输入模式 | [0~2]
    FH_UINT8  u08FrameCnt;  // 多张图模式的帧数（需要输入大于1,否则为单图）| [0~0xff]
} ISP_VIGEN_CFG;

typedef struct _ISP_RAW_BUF_S
{
    struct mem_desc raw_mem;
    FH_UINT32 frameCnt;
    FRAME_TYPE raw_type;
} ISP_RAW_BUF;

/**|MIRROR|**/
typedef struct mirror_cfg_s
{
    FH_BOOL             bEN;  // 镜像使能开关 | [0~1]
    ISP_BAYER_TYPE      normal_bayer;  // 无效成员变量 | [0~3]
    ISP_BAYER_TYPE      mirror_bayer;  //　无效成员变量 | [0~3]
}MIRROR_CFG_S;

/**|AE|**/
typedef struct _AE_ENABLE_CFG_S_
{
    FH_BOOL bAecEn;          // 自动曝光策略总开关     0：关闭AE策略   1：打开AE策略 | [0x0-0x1]
    FH_UINT8 u08AeMode;      // 自动曝光模式选择： （更新时需置位refresh位）       0：自动 1：半自动(允许固定曝光时间或增益中的一个，另一个走自动模式)     2：手动 | [0x0-0x2]
    FH_BOOL bAscEn;          // 自动快门使能   (aeMode为0时生效，更新时需置位refresh位)         0：关闭自动曝光时间，曝光时间维持上一帧的数值  1：使能自动曝光时间 | [0x0-0x1]
    FH_BOOL bMscEn;          // 手动快门使能   (aeMode为1时生效，更新时需置位refresh位)        0：关闭手动曝光时间，则曝光时间自动走   1：使能手动曝光时间，则曝光时间由mIntt决定 | [0x0-0x1]
    FH_BOOL bAgcEn;          // 自动增益使能   (aeMode为0时生效，更新时需置位refresh位)        0：关闭自动增益，增益维持上一帧的数值   1：使能自动增益 | [0x0-0x1]
    FH_BOOL bMgcEn;          // 手动增益使能(aeMode为1时生效，更新时需置位refresh位)   0：关闭手动增益，则增益自动走   1：使能手动增益，则增益由mAgain,mDgain决定 | [0x0-0x1]
    FH_BOOL bSensUpEn;       // 慢快门使能(更新时需置位refresh位)   0：禁止降低帧率 1：允许降低帧率，增加快门时间 | [0x0-0x1]
    FH_BOOL bIrisEn;         // 自动光圈使能(暂不支持)        0：关闭自动光圈 1：打开自动光圈 | [0x0-0x1]
    FH_BOOL bInttFineEn;     // 精细快门使能      0：只能调整整数行曝光时间       1：允许调整小数行曝光时间(采用数字增益内插) | [0x0-0x1]
    FH_BOOL bGainFineEn;     // 精细增益使能      0：增益精度跟随sensor   1：允许1/256增益精度(采用数字增益内插) | [0x0-0x1]
    FH_BOOL bAspeedEn;       // 自动速度控制使能    0：关闭自动速度，速度由initSpeed，speed及UExpSpeedBias决定      1：打开自动速度 | [0x0-0x1]
    FH_BOOL bAntiFlickerEn;  // 自动抗闪使能   0：关闭抗闪模式 1：打开抗闪模式 | [0x0-0x1]
    FH_BOOL bAdaptiveEn;     // 自适应参考亮度    0：关闭自适应参考亮度，亮度只由lumaRef决定      1：打开自适应参考亮度，亮度跟随环境光线变化 | [0x0-0x1]
    FH_BOOL bARouteEn;       // 自动曝光路线使能（更新时需置位refresh位）   0：使用默认曝光路线     1：使用手动曝光路线 | [0x0-0x1]
    FH_BOOL bInttUnitSel;    // 曝光时间单位选择：       0: 曝光时间单位使用us   1: 曝光时间单位使用行 | [0x0-0x1]
} AE_ENABLE_CFG;

typedef struct _AE_INIT_CFG_S_
{
    FH_UINT8 u08InitSpeed;     // 初始化曝光速度 | [0x0-0xff]
    FH_UINT32 u32InitExpTime;  // 初始化曝光时间，单位由inttUnitSel决定，暂不支持 | [0x0-0xfffff]
    FH_UINT16 u16InitAgain;    // 初始化sensor增益，U.6，暂不支持 | [0x40-0xffff]
    FH_UINT16 u16InitDgain;    // 初始化isp增益，U.6，暂不支持 | [0x40-0x3ff]
} AE_INIT_CFG;

typedef struct _AE_SPEED_CFG_S_
{
    FH_UINT8 u08GreatChangeZone;  // 较大亮度变化区间 | [0x0-0xff]
    FH_UINT8 u08Tolerance;        // 一般不超过lumaRef的1%,U.4精度 | [0x0-0xff]
    FH_UINT8 u08LightChangeZone;  // 较小亮度变化区间 | [0x0-0xff]
    FH_UINT8 u08OverExpLDlyFrm;   // 过曝较小调整时延时调整的帧数 | [0x0-0xff]
    FH_UINT8 u08UnderExpGDlyFrm;  // 欠曝较大调整时延时调整的帧数 | [0x0-0xff]
    FH_UINT8 u08UnderExpLDlyFrm;  // 欠曝较小调整时延时调整的帧数 | [0x0-0xff]
    FH_UINT8 u08OverExpGDlyFrm;   // 过曝较大调整时延时调整的帧数 | [0x0-0xff]
    FH_UINT8 u08UExpSpeedBias;    // 欠曝调整时速度偏移量 | [0x0-0xff]
    FH_UINT8 u08RunInterval;      // AE策略运行间隔，值为0时表示每帧运行，值为1时表示隔1帧运行一次，依次类推，一般配成0 | [0x0-0xf]
    FH_UINT8 u08Speed;            // 曝光速度，值越小速率越快，0是最快速率 | [0x0-0xff]
} AE_SPEED_CFG;

typedef struct _AE_METERING_CFG_S_
{
    FH_UINT8 u08StatSel;         // 统计模式：  0：3*3分块统计  1：16*16分块统计    2：hist统计 | [0x0-0x2]
    FH_UINT8 u08LightMode;       // 亮度测光模式(statSel=1或2时生效)：  0：正常模式 1：高光优先	2：低光优先 | [0x0-0x2]
    FH_UINT8 u08BlockMode;       // 分块测光模式(statSel=0或1时生效)：  0：全局测光 1：前光补偿(仅3*3统计生效)	2：背光补偿(仅3*3统计生效)	3：用户自定义 | [0x0-0x3]
    FH_UINT8 u08MeteringBlock;   // 当blockMode = 1/2时生效，表示   0：最强，8最弱 | [0x0-0x8]
    FH_UINT8 u08LumaBoundary;    // 高光或低光亮度截断值(仅在lightMode下有效) | [0x0-0xff]
    FH_UINT8 u08RoiWeight;       // 高光或低光区域对平均亮度影响程度，值越大，对平均亮度影响越大，值为0时不影响(仅在lightMode下有效) | [0x0-0xff]
    FH_UINT16 u16Sensitivity;    // 亮度敏感度，值越大，对高光或低光区域越敏感, U.7(仅在lightMode下有效) | [0x0-0xffff]
    FH_UINT8 u08WeightBlk[256];  // 最大支持256个窗口权值配置（仅meteringMode=5或7，更新时需置位refresh位） | [0x0-0xf]
} AE_METERING_CFG;

typedef struct _AE_TIMING_CFG_S_
{
    FH_UINT8 u08Intt0Delay;   // 配置T1 intt时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08Intt1Delay;   // 当至少两帧合成时配置T2 intt时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08Intt2Delay;   // 当至少三帧合成时配置T3 intt时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08Intt3Delay;   // 当至少四帧合成时配置T4 intt时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08Again0Delay;  // 配置T1 sensor gain时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08Again1Delay;  // 当至少两帧合成时配置T2 again时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08Again2Delay;  // 当至少三帧合成时配置T3 again时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08Again3Delay;  // 当至少四帧合成时配置T4 again时，延迟的帧数，更新时需置位refresh位 | [0x0-0x3]
    FH_UINT8 u08DgainDelay;   // 配置isp gain时，延迟的帧数，更新时需置位refresh位 | [0x0-0xf]
    FH_UINT8 u08SensUpDelay;  // 配置帧结构时，延迟的帧数，更新时需置位refresh位 | [0x0-0xf]
} AE_TIMING_CFG;

typedef struct _AE_MANUAL_CFG_S_
{
    FH_UINT32 u32MIntt;   // 手动模式下的intt值，单位由inttUnitSel决定 | [0x0-0x3ffff]
    FH_UINT16 u16MAgain;  // 手动模式下的again值，U.6 | [0x40-0xffff]
    FH_UINT16 u16MDgain;  // 手动模式下的Dgain值，U.6 | [0x40-0x3ff]
} AE_MANUAL_CFG;

typedef struct _AE_ANTIFLICKER_CFG_S_
{
    FH_BOOL bAntiFlickerMode;  // 抗闪模式选择：    1:强抗闪模式，完全根据频闪周期配置曝光时间  0:弱抗闪模式，当环境光较亮时通过限制亮度并取消抗闪来避免过曝严重 | [0x0-0x1]
    FH_UINT16 u16Frequency;    // 抗闪频率值 | [0x0-0xfff]
    FH_UINT8 u08StabZone;      // 抗闪最大亮度差异设置，当stabZone+targetLuma<CurrLuma时取消抗闪设置 | [0x0-0xff]
} AE_ANTIFLICKER_CFG;

typedef struct _AE_LUMA_CFG_S_
{
    FH_UINT8 u08LumaRefHigh;  // 高光状态下的参考亮度，仅当adaptiveEn为1且aRouteEn为0时生效，归一化至0~255 | [0x0-0xff]
    FH_UINT8 u08LumaRefLow;   // 低光状态下的参考亮度，仅当adaptiveEn为1且aRouteEn为0时生效，归一化至0~255 | [0x0-0xff]
    FH_UINT8 u08LumaRef;      // 参考亮度，归一化至0~255 | [0x0-0xff]
    FH_UINT16 u16EvLow;       // 低光状态环境光强，用于aRouteEn为0时的参考亮度内插 | [0x0-0xffff]
    FH_UINT16 u16EvNormL;     // 正常光线状态环境光强下阈值，用于aRouteEn为0时的参考亮度内插 | [0x0-0xffff]
    FH_UINT16 u16EvNormH;     // 正常光线状态环境光强上阈值，用于aRouteEn为0时的参考亮度内插 | [0x0-0xffff]
    FH_UINT16 u16EvHigh;      // 高光状态环境光强，用于aRouteEn为0时的参考亮度内插 | [0x0-0xffff]
} AE_LUMA_CFG;

typedef struct _AE_RANGE_CFG_S_
{
    FH_UINT16 u16InttMin;   // 最小曝光时间，单位由inttUnitSel决定，更新时需置位refresh位 | [0x0-0xffff]
    FH_UINT32 u32InttMax;   // 最大曝光时间，单位由inttUnitSel决定，更新时需置位refresh位 | [0x0-0xfffff]
    FH_UINT16 u16AgainMin;  // sensor增益最小值，U.6，更新时需置位refresh位 | [0x40-0xffff]
    FH_UINT16 u16AgainMax;  // sensor增益最大值，U.6，更新时需置位refresh位 | [0x40-0xffff]
    FH_UINT16 u16DgainMin;  // isp增益最小值，U.6，更新时需置位refresh位 | [0x40-0x3ff]
    FH_UINT16 u16DgainMax;  // isp增益最大值，U.6，更新时需置位refresh位 | [0x40-0x3ff]
} AE_RANGE_CFG;

typedef struct _AE_DEFAULT_CFG_S_ {
    AE_ENABLE_CFG stAeEnableCfg;            // ae使能配置 | [AE_ENABLE_CFG]
    AE_INIT_CFG stAeInitCfg;                // ae初始化配置 | [AE_INIT_CFG]
    AE_SPEED_CFG stAeSpeedCfg;              // ae速率配置 | [AE_SPEED_CFG]
    AE_METERING_CFG stAeMeteringCfg;        // ae测光配置 | [AE_METERING_CFG]
    AE_TIMING_CFG stAeTimingCfg;            // ae时序配置 | [AE_TIMING_CFG]
    AE_MANUAL_CFG stAeManualCfg;            // ae手动值配置 | [AE_MANUAL_CFG]
    AE_ANTIFLICKER_CFG stAeAntiflickerCfg;  // ae抗闪配置 | [AE_ANTIFLICKER_CFG]
    AE_LUMA_CFG stAeLumaCfg;                // ae亮度配置 | [AE_LUMA_CFG]
    AE_RANGE_CFG stAeRangeCfg;              // 最小最大范围配置,更新时需置位refresh位 | [AE_RANGE_CFG]
    FH_BOOL bNodeChMode;                    // ae节点变化模式选择：     0:跨节点变化模式; 1:节点连续变化模式 | [0x0-0x1]
    FH_BOOL bSensUpMode;                    // 慢快门模式选择：     0:无极连续降帧; 1:非连续直接降帧 | [0x0-0x1]
    FH_UINT8 u08SensUpPrec;                 // 慢快门非连续降帧精度，值越大降帧分段越多越精确 | [0x0-0xf]
    FH_UINT16 u16SensUpEnableAgain;         // 降帧启动增益，U.6 (aRouteEn为0时生效，更新时需置位refresh位） | [0x40-0xffff]
    FH_UINT8 u08InttPrec;                   // 曝光精度，固定以行为单位 | [0x0-0xff]
    FH_UINT8 u08InttOffset;                 // 当sensor intt与again存在偏移关系时需要配置曝光时间的偏移，固定以μs为单位 | [0x0-0xff]
} AE_DEFAULT_CFG;

typedef struct _AE_ROUTE_CFG_S_ {
    FH_UINT16 u16Piris[16];   // 节点对应光圈参数，更新时需置位refresh位 | [0x0-0xfff]
    FH_UINT32 u32Intt[16];    // 节点对应曝光时间参数，单位由inttUnitSel决定，更新时需置位refresh位 | [0x0-0xfffff]
    FH_UINT16 u16AGain[16];   // 节点对应模拟增益，U.6，更新时需置位refresh位 | [0x40-0xffff]
    FH_UINT16 u16DGain[16];   // 节点对应数字增益，U.6，更新时需置位refresh位 | [0x40-0x3ff]
    FH_UINT8 u08LumaRef[16];  // 节点对应的参考亮度，更新时需置位refresh位 | [0x0-0xff]
} AE_ROUTE_CFG;

typedef struct _ISP_AE_INFO_S_
{
    FH_UINT32   u32Intt;          // sensor曝光行数 | [0~0xffffffff]
    FH_UINT32   u32IspGain;       // isp增益值U4.8, 0x100表示一倍 | [0~0xfff]
    FH_UINT32   u32SensorGain;    // sensor增益值U.6, 0x40表示一倍 |[0~0xffffffff]
    FH_UINT32   u32TotalGain;     // 总增益U.6 , 0x40表示一倍 | [0~0xffffffff]
} ISP_AE_INFO;

typedef struct _ISP_AE_INFO_2_S_
{
    FH_UINT32   u32Intt;          // sensor曝光行数 | [0~0xffffffff]
    FH_UINT32   u32PreGain;       // 前置isp增益值U4.8, 0x100表示一倍 | [0~0xfff]
    FH_UINT32   u32PostGain;      // 后置isp增益值U4.8, 0x100表示一倍 | [0~0xfff]
    FH_UINT32   u32SensorGain;    // sensor增益值U.6, 0x40表示一倍 |[0~0xffffffff]
    FH_UINT32   u32TotalGain;     // 总增益U.6 , 0x40表示一倍 | [0~0xffffffff]
} ISP_AE_INFO_2;

typedef struct _ISP_AE_STATUS_S_
{
    FH_UINT8 u08TarLuma;           // 目标亮度 | [0x0-0xff]
    FH_UINT8 u08CurrLuma;          // 当前亮度 | [0x0-0xff]
    FH_UINT16 u16ErrorLuma;        // 当前帧亮度与目标值差异，S.4，tar-curr | [0x0-0x1fff]
    FH_UINT32 u32CurrIntt;         // 当前曝光时间，单位固定是μs | [0x0-0xfffff]
    FH_UINT16 u16CurrPiris;        // 当前光圈值 | [0x0-0xfff]
    FH_UINT16 u16CurrDgain;        // 当前isp增益，U.6 | [0x0-0xffff]
    FH_UINT16 u16CurrAgain;        // 当前sensor增益，U.6 | [0x0-0xffff]
    FH_UINT32 u32CurrTotalGain;    // 当前总增益，U.6 | [0x0-0xffffffff]
    FH_UINT16 u16CurrInttLine;     // 当前曝光时间，单位固定为行 | [0x0-0xffff]
    FH_UINT16 u16CurrFrameHeight;  // 当前帧高度 | [0x0-0xffff]
    FH_UINT16 u16Ev;               // 当前环境光强 | [0x0-0xffff]
    FH_UINT8 u08CurrNodeId;        // 当前节点ID(仅aRouteEn为1时有效) | [0x0-0xf]
    FH_BOOL bOpStatus;             // Ae当前运行状态    0：停止 1：运行 | [0x0-0x1]
    FH_UINT32 u32ExpParam;         // 当前总曝光参数，曝光时间以行数计算，增益均以.6精度 | [0x0-0xffffffff]
    FH_UINT16 u16Piris[16];        // 该节点对应光圈参数 | [0x0-0xfff]
    FH_UINT32 u32Intt[16];         // 该节点对应曝光时间参数，单位由inttUnitSel决定 | [0x0-0xfffff]
    FH_UINT16 u16DGain[16];        // 该节点对应数字增益，U.6 | [0x0-0xffff]
    FH_UINT16 u16AGain[16];        // 该节点对应模拟增益，U.6 | [0x0-0xffff]
    FH_UINT16 u16ActInttMax;       // 策略运行生效的inttmax，以行为单位 | [0x0-0xffff]
    FH_UINT16 u16ActAgainMax;      // 策略运行生效的againmax，U.6 | [0x0-0xffff]
    FH_UINT16 u16ActDgainMax;      // 策略运行生效的dgainmax，U.6 | [0x0-0xffff]
    FH_UINT16 u16SensorInttMax;    // Sensor支持的inttmax，以行为单位，从sensor库获取 | [0x0-0xffff]
    FH_UINT16 u16SensorInttMin;    // Sensor支持的inttMin，以行为单位，从sensor库获取 | [0x0-0xffff]
    FH_UINT16 u16SensorAgainMax;   // Sensor支持的againMax，U.6，从sensor库获取 | [0x0-0xffff]
    FH_UINT16 u16SensorAgainMin;   // Sensor支持的againMin，U.6，从sensor库获取 | [0x0-0xffff]
    FH_UINT16 u16DgainMax;         // ISP支持的DgainMax，U.6，由硬件位宽决定 | [0x0-0xffff]
    FH_UINT16 u16DgainMin;         // ISP支持的DgainMin，U.6，由硬件位宽决定 | [0x0-0xffff]
} ISP_AE_STATUS;

typedef struct _AE_USER_STATUS_S_
{
    FH_UINT8 u08TarLuma;         // 当前目标亮度 | [0x0-0xff]
    FH_UINT32 u32CurrTotalGain;  // 当前总增益，U.6 | [0x0-0xffffffff]
    FH_BOOL bOpStatus;           // Ae当前运行状态  0：停止 1：运行 | [0x0-0x1]
    FH_UINT32 u32CurrIntt;       // 当前曝光时间，单位固定是μs | [0x0-0xfffff]
    FH_UINT16 u16CurrInttLine;   // 当前曝光时间，单位固定为行 | [0x0-0xffff]
    FH_UINT16 u16ActInttMax;     // 策略运行生效的inttmax，以行为单位,非慢快门下不大于u16SensorInttMax | [0x0-0xffff]
    FH_UINT16 u16SensorInttMax;  // Sensor支持的inttmax，以行为单位，不考虑慢快门情况,表示的是一帧之内的最大曝光值 | [0x0-0xffff]
} AE_USER_STATUS;

/**|AWB|**/
typedef struct _AWB_ENABLE_CFG_S_
{
    FH_BOOL bAwbEn;          // Awb总使能 | [0x0-0x1]
    FH_BOOL bMwbEn;          // 手动wb使能，当为1时配置手动R,G,B增益值，当为0时根据统计实时调整 | [0x0-0x1]
    FH_BOOL bPureColorEn;    // 单色物体判断使能 | [0x0-0x1]
    FH_BOOL bCompEn;         // 增益补偿使能 | [0x0-0x1]
    FH_BOOL bInOutEn;        // 室内外场景判断使能 | [0x0-0x1]
    FH_BOOL bLightWeightEn;  // 亮度是否影响权重使能 | [0x0-0x1]
    FH_BOOL bMultiCTEn;      // 混合色温使能 | [0x0-0x1]
    FH_BOOL bAddWPEn;        // 附加色温点使能 | [0x0-0x1]
    FH_BOOL bMinMaxSel;      // 0：增益计算采用最小值   1：增益计算采用最大值 | [0x0-0x1]
    FH_BOOL bMinNormEn;      // 增益计算采用最小值时，是否做亮度归一化的使能 | [0x0-0x1]
    FH_UINT8 u08AwbAlgType;  // 0：Gray World   1：Global Alg 2:Advanced Alg| [0x0-0x2]
    FH_BOOL bRefresh;        // 刷新位：更新AWB控制参数，初始化AWB流程 0：不刷新;   1：刷新 | [0x0-0x01]
} AWB_ENABLE_CFG;

typedef struct _AWB_WHITE_POINT_S_
{
    FH_UINT16 u16BOverG;  // 标定白点的B/G分量 | [0-0xffff]
    FH_UINT16 u16ROverG;  // 标定白点的R/G分量 | [0-0xffff]
} AWB_WHITE_POINT;

typedef struct _STAT_WHITE_POINT_S_
{
    FH_UINT16 u16Coordinate_w;  // awb白框横坐标U3.7 | [0-0x3ff]
    FH_UINT16 u16Coordinate_h;  // awb白框纵坐标U3.7 | [0-0x3ff]
} STAT_WHITE_POINT;

typedef struct _AWB_CT_CFG_S_
{
    FH_UINT8 u08ColorTempNum;         // 色温框的个数，范围4~12 | [0x4-0xc]
    FH_UINT8 u08CtWidthThl;           // 每个色温框斜向宽度下阈值，U.7，斜向指垂直于标定色温连线方向,值越大被判定为白点的可能性越高，当前增益小于config21中的ctWidthGainThl时，ctWidth采用ctWidthThl | [0x0-0xff]
    FH_UINT8 u08CtWidthThh;           // 每个色温框斜向宽度上阈值，U.7，斜向指垂直于标定色温连线方向,值越大被判定为白点的可能性越高，当前增益大于config21中的ctWidthGainThh时，ctWidth采用ctWidthThh,当前增益在两个值中间时，线性内插出ctWidth | [0x0-0xff]
    FH_UINT16 u16CtWidthGainThh;      // 色温框斜向宽度的增益上阈值(U12.4) | [0x0-0xffff]
    FH_UINT16 u16CtWidthGainThl;      // 色温框斜向宽度的增益下阈值(U12.4) | [0x0-0xffff]
    AWB_WHITE_POINT stWhitePoint[4];  // 标定白点的结构体 | [AWB_WHITE_POINT]
    STAT_WHITE_POINT stPoint[6];      //  awb白框点,A，B，C，D，E，F六个点，Ax=Bx By=Cy Dy=Ey Ex=Fx | [STAT_WHITE_POINT]
} AWB_CT_CFG;

typedef struct _AWB_LIGHT_CFG_S_
{
    FH_BOOL bLightWeightThMode;    // 0：内置门限值表   1：用户自定义门限值 | [0x0-0x1]
    FH_UINT8 u08LightWeightTh[6];  // 亮度阈值, 单调递增 | [0x0-0xff]
    FH_UINT8 u08LightWeight[6];    // 对应亮度阈值的亮度权重 | [0x0-0xff]
} AWB_LIGHT_CFG;

typedef struct _AWB_SCENE_CFG_S_
{
    FH_UINT8 u08SingleCTRatioThl;   // 单色温比例门限下阈值，原来处于单色温状态时，比例小于该值认为是混合色温。单位是百分比，0~100% | [0x0-0x64]
    FH_UINT8 u08SingleCTRatioThh;   // 单色温比例门限上阈值，原来处于混合色温状态时，比例大于该值认为是单色温。单位是百分比，0~100% | [0x0-0x64]
    FH_UINT8 u08MultiSatScaler;     // 混合色温下饱和度调整比例，增益系数计算为multiSatScaler/0xff,值越小，混合色温下饱和度越低。（暂不支持） | [0x0-0xff]
    FH_UINT8 u08MultiCTWeight[12];  // 混合色温下各色温点的权重 | [0x0-0xff]
    FH_UINT8 u08LumaDiffRatioTh;    // 单色亮度差异比例门限值，差异值与平均值的比例小于此值则亮度符合纯色判断，反之则不符合 | [0x0-0x64]
    FH_UINT8 u08ChromaDiffRatioTh;  // 单色色度差异比例门限值，差异值与平均值的比例小于此值则色度符合纯色判断，反之则不符合 | [0x0-0x64]
    FH_BOOL bInOutType;             // 室内外判断类型： 0：自动 1：手动 | [0x0-0x1]
    FH_BOOL bManualType;            // 手动模式下室内外类型：   0：室内 1：室外 | [0x0-0x1]
    FH_UINT16 u16InDoorThresh;      // 室内场景判断曝光时间的阈值，单位是us，大于该曝光时间认为是室内的概率是100% | [0x0-0xffff]
    FH_UINT16 u16OutDoorThresh;     // 室外场景判断曝光时间的阈值，单位是us，不大于该曝光时间认为是室外的概率是100% | [0x0-0xffff]
    FH_UINT8 u08OutWeight[12];      // 室外各色温点的权重 | [0x0-0xff]
} AWB_SCENE_CFG;

typedef struct _AWB_ADD_WHITE_AREA_S_
{
    FH_BOOL bAddWPEn;     // 新增白点使能 | [0x0-0x1]
    FH_UINT8 u08ByWidth;  // 新增白点的色温框B-Y的宽度，U.7 | [0x0-0xff]
    FH_UINT8 u08RyWidth;  // 新增白点的色温框R-Y的宽度，U.7 | [0x0-0xff]
} AWB_ADD_WHITE_AREA;

typedef struct _AWB_ADD_CT_CFG_S_
{
    AWB_ADD_WHITE_AREA stAddWhiteArea[4];  // 新增白点使能及色温框配置 | [AWB_ADD_WHITE_AREA]
    AWB_WHITE_POINT stAddWhitePoint[4];    // 标定新增白点的结构体 | [AWB_WHITE_POINT]
} AWB_ADD_CT_CFG;

typedef struct _ISP_AWB_GAIN_S_ {
    FH_UINT16 u16Rgain;  // 手动R通道增益，U.9 | [0x0-0x1fff]
    FH_UINT16 u16Ggain;  // 手动G通道增益，U.9 | [0x0-0x1fff]
    FH_UINT16 u16Bgain;  // 手动B通道增益，U.9 | [0x0-0x1fff]
} ISP_AWB_GAIN;

typedef struct _AWB_MANUAL_CFG_S_
{
    ISP_AWB_GAIN stAwbGain;  // wb手动增益值 | [ISP_AWB_GAIN]
} AWB_MANUAL_CFG;

typedef struct _AWB_COMP_CFG_S_
{
    FH_UINT8 u08REnhance;  // R通道增益补偿，U.6 | [0x0-0xff]
    FH_UINT8 u08BEnhance;  // B通道增益补偿，U.6 | [0x0-0xff]
    FH_UINT8 u08GEnhance;  // G通道增益补偿，U.6 | [0x0-0xff]
} AWB_COMP_CFG;

typedef struct _AWB_DEFAULT_CFG_S_
{
    AWB_ENABLE_CFG stAwbEnableCfg;  // awb使能配置 | [AWB_ENABLE_CFG]
    FH_UINT16 u16Speed;             // 值越大，调整速度越快 | [0x0-0xfff]
    FH_UINT8 u08StatThh;            // 统计像素亮度阈值上限，亮度按255归一化 | [0x0-0xff]
    FH_UINT8 u08StatThl;            // 统计像素亮度阈值下限，亮度按255归一化 | [0x0-0xff]
    AWB_CT_CFG stAwbCtCfg;          // awb色温相关参数配置 | [AWB_CT_CFG]
    AWB_LIGHT_CFG stAwbLightCfg;    // awb亮度阈值及权重配置 | [AWB_LIGHT_CFG]
    AWB_SCENE_CFG stAwbSceneCfg;    // awb场景判断参数配置 | [AWB_SCENE_CFG]
    AWB_ADD_CT_CFG stAwbAddCtCfg;   // awb新增色温参数配置 | [AWB_ADD_CT_CFG]
    AWB_MANUAL_CFG stAwbManualCfg;  // awb手动增益配置 | [AWB_MANUAL_CFG]
    AWB_COMP_CFG stAwbCompCfg;      // awb补偿增益配置 | [AWB_COMP_CFG]
} AWB_DEFAULT_CFG;

typedef struct _ISP_AWB_STATUS_S_
{
    FH_UINT16 u16RGain;            // 红色增益（U4.6） | [0x0-0x3ff]
    FH_UINT16 u16GGain;            // 绿色增益（U4.6） | [0x0-0x3ff]
    FH_UINT16 u16BGain;            // 蓝色增益（U4.6） | [0x0-0x3ff]
    FH_UINT16 u16CurrBOverG;       // 当前B/G(水平坐标，U4.12) | [0x0-0xffff]
    FH_UINT16 u16CurrROverG;       // 当前R/G(垂直坐标，U4.12) | [0x0-0xffff]
    FH_UINT16 u16RAvg;             // 当前统计红色平均值（U10） | [0x0-0x3ff]
    FH_UINT16 u16GAvg;             // 当前统计绿色平均值（U10） | [0x0-0x3ff]
    FH_UINT16 u16BAvg;             // 当前统计蓝色平均值（U10） | [0x0-0x3ff]
    FH_UINT8 u08Pos;               // 当前色温位置   0：最靠近左侧统计点 255：最靠近右侧统计点 | [0x0-0xff]
    FH_UINT8 u08CurrLeft;          // 当前色温左侧统计点index | [0x0-0xf]
    FH_UINT8 u08CurrRight;         // 当前色温右侧统计点index | [0x0-0xf]
    FH_UINT8 u08UnknownProb;       // 当前为不确定场景的概率，单位为百分比 | [0x0-0x64]
    FH_UINT8 u08PureColorProb;     // 当前为纯色场景的概率，单位为百分比 | [0x0-0x64]
    FH_UINT8 u08OutdoorProb;       // 当前为室外场景的概率，单位为百分比 | [0x0-0x64]
    FH_UINT8 u08IndoorSingleProb;  // 当前为室内单色温场景的概率，单位为百分比 | [0x0-0x64]
    FH_UINT8 u08IndoorMultiProb;   // 当前为室内混合色温场景的概率，单位为百分比 | [0x0-0x64]
    FH_UINT8 u08CtNum[12];         // 各色温的blk数量 | [0x0-0xff]
    FH_UINT8 u08CtAddNum[4];       // 新增白点的blk数量 | [0x0-0xff]
} ISP_AWB_STATUS;

/**|CCM|**/
typedef struct _CCM_TABLE_S_
{
    FH_SINT16 s16CcmTable[4][12];  // ccm矩阵表 | [-4096~0xfff]
} CCM_TABLE;

typedef struct _ISP_CCM_CFG_S_ {
    FH_SINT16 s16CcmTable[12];  // ccm矩阵表 | [-4096~0xfff]
} ISP_CCM_CFG;

/**|GAMMA|**/
typedef enum IPB_GAMMA_MODE_S_ {
    GAMMA_OFF       = 0, // 关闭GAMMA
    GAMMA_MODE_YC   = 1, // GAMMA采用YC模式
    GAMMA_MODE_RGB  = 2, // GAMMA采用RGB模式
    GAMMA_MODE_RGBY = 3, // GAMMA采用RGBY模式
    IPB_GAMMA_MODE_DUMMY =0xffffffff,
} IPB_GAMMA_MODE;

typedef enum _GAMMA_BUILTIN_IDX_ {
    GAMMA_CURVE_10 = 0, // GAMMA曲线1.0
    GAMMA_CURVE_12 = 1, // GAMMA曲线1.2
    GAMMA_CURVE_14 = 2, // GAMMA曲线1.4
    GAMMA_CURVE_16 = 3, // GAMMA曲线1.6
    GAMMA_CURVE_18 = 4, // GAMMA曲线1.8
    GAMMA_CURVE_20 = 5, // GAMMA曲线2.0
    GAMMA_CURVE_22 = 6, // GAMMA曲线2.2
    GAMMA_CURVE_24 = 7, // GAMMA曲线2.4
    GAMMA_CURVE_26 = 8, // GAMMA曲线2.6
    GAMMA_CURVE_28 = 9, // GAMMA曲线2.8
    GAMMA_BUILTIN_IDX_DUMMY =0xffffffff,
} GAMMA_BUILTIN_IDX;

typedef struct _ISP_GAMMA_CFG_S_
{
    FH_BOOL        bGammaEn;    // gamma控制使能 | [0~1]
    IPB_GAMMA_MODE u8GammaMode; // GAMMA模块输入选择	0: gamma off	1: YC mode	2: RGB mode	3: RGBY mode |[0-0x3]
    CURVE_TYPE        eCCurveType;       // c gamma控制模式:0 内置gamma表;1 用户自定义gamma表 | [0~1]
    GAMMA_BUILTIN_IDX eCGammaBuiltInIdx; // c gamma控制模式等于0时有效，内置cgamma表索引 | [0~0xf]
    FH_UINT16         u16CGamma[160];    // 用户自定义cgamma表 | [0~0x3ff]
    CURVE_TYPE        eYCurveType;       // y gamma控制模式:0 内置gamma表;1 用户自定义gamma表 | [0~1]
    GAMMA_BUILTIN_IDX eYGammaBuiltInIdx; // y gamma控制模式等于0时有效，内置ygamma表索引 | [0~0xf]
    FH_UINT16         u16YGamma[160];    // 用户自定义ygamma表 | [0~0x3ff]
} ISP_GAMMA_CFG;
/**|BLC|**/
typedef struct _ISP_BLC_ATTR_S_
{
    FH_BOOL   bGainmappingEn; // 0: 手动	1: 增益映射模式 | [0-0x1]
    FH_BOOL   bBlcDeltaModeEn;// 0:分通道Blc Delta Mode关闭	1: 分通道Blc Delta Mode打开 | [0-0x1]
    FH_UINT16 u16Blclv;       //手动黑电平值 | [0-0xffff]
    FH_UINT16 u16ChannelMode; // 0:全通道设置blc	1: 分通道设置blc | [0-0x1]
    FH_UINT16 u16BlcChannel0; //通道0 blc值 | [0-0xffff]
    FH_UINT16 u16BlcChannel1; //通道1 blc值 | [0-0xffff]
    FH_UINT16 u16BlcChannel2; //通道2 blc值 | [0-0xffff]
    FH_UINT16 u16BlcChannel3; //通道3 blc值 | [0-0xffff]
    FH_UINT16 u16Blc[GAIN_NODES];//不同增益下 blc值 | [0-0xffff]
    FH_SINT8  s08BlcDeltaValR;//手动 blc R delta值 | [-128~127]
    FH_SINT8  s08BlcDeltaValG;//手动 blc G delta值 | [-128~127]
    FH_SINT8  s08BlcDeltaValB;//手动 blc B delta值 | [-128~127]
    FH_SINT8  s08BlcDeltaR[GAIN_NODES];//不同增益下 blc R delta值 | [-128~127]
    FH_SINT8  s08BlcDeltaG[GAIN_NODES];//不同增益下 blc G delta值 | [-128~127]
    FH_SINT8  s08BlcDeltaB[GAIN_NODES];//不同增益下 blc B delta值 | [-128~127]
} ISP_BLC_ATTR;
/**|GB|**/
typedef struct _ISP_GB_CFG_S_
{
    FH_BOOL   bGBEn;        // 绿平衡控制使能 | [0~1]
    FH_BOOL   bGBNewModeEn; //绿平衡新模式使能：0关闭;1开启 | [0~1]
    FH_UINT16 u16Th;        //上阈值 | [0-0xffff]
    FH_UINT16 u16Tl;        //下阈值 | [0-0xffff]
    FH_SINT16 s16GrRatio;   //Gr通道比例 | [-512~511]
    FH_SINT16 s16GbRatio;   //Gb通道比例 | [-512~511]
} ISP_GB_CFG;
/**|DPC|**/
typedef struct _DYNAMIC_DPC_CFG_S_
{
    FH_BOOL  bDpcEn;  // 坏点消除控制使能 | [0~1]
    FH_BOOL  bGainMappingEn; // 0：手动	1：增益映射 | [0~1]
    FH_UINT8 ctrl_mode;      //去坏点控制模式：0~3，值越大越强 | [0~3]
    FH_UINT8 u08Str;         // 去坏点强度,U1.3 | [0-0xf]
    FH_UINT8 u08DpcMode; // 0:关闭去坏点;1:打开去白点功能;2.打开去黑点功能;3.同时打开去白点黑点功能| [0~3]
    FH_UINT8 u08Strenght[GAIN_NODES]; //不同增益下DPC强度| [0-0xf]
    FH_UINT8 u08WhiteThr[GAIN_NODES]; //不同增益下白点门限DC值 | [0-0xff]
    FH_UINT8 u08BlackThr[GAIN_NODES]; //不同增益下黑点门限值 | [0-0xff]
    FH_UINT8 u08wdc;                  //手动白点门限值 | [0-0xff]
    FH_UINT8 u08bdc;                  //手动黑点门限值 | [0-0xff]
} DYNAMIC_DPC_CFG;
/**|LSC|**/
typedef struct _ISP_LSC_CFG_S_
{
    FH_BOOL   bLscEn;       // 镜头阴影矫正控制使能 | [0~1]
    FH_UINT32 u32Coff[299]; // 补偿系数 | [0~0xffffffff]
} ISP_LSC_CFG;
/**|NR3D|**/
typedef struct _ISP_NR3D_CFG_S_
{
    FH_BOOL   bNR3DEn;                       // 3d降噪控制使能 | [0~1]
    FH_BOOL   bGainMappingEn;                // 0：手动	1：增益映射 | [0~1]
    FH_BOOL   bPresetMap;                    // 0: 采用内置coeff映射表（由coeff_map_idx决定）	1：采用自定义coeff映射表 | [0-0x1]
    FH_BOOL   bMtParam1Mode;                 // 0: 采用内置mtparam1映射表（由mt_param1决定）	1：采用自定义mt_param1映射表 | [0-0x1]
    FH_UINT8  u08CoeffMapIdx;                // Coeff映射线（建议白天配置0或1）：	0~7：过渡越来越平滑，但同时强度变弱 | [0-0x7]
    FH_UINT8  u08GlutIdx;                    // sensor预矫正曲线index | [0-0xf]
    FH_UINT8  u08RefCoeffRatio;              // 参考帧coeff的比例因子，值越小收敛越快，但过小也会引起拖影。 | [0x0-0xf]
    FH_BOOL   bCoeffParam;                   // Coeff控制参数：	0：作用范围小；	1：作用范围大；  | [0x0-0x1]
    FH_BOOL   bCoeffMode;                    // Coef处理方式 | [0-1]
    FH_UINT8  u08Dc;                         // dc值,U8 | [0-0xff]
    FH_UINT8  u08CoeffOffset;                // coeff的偏移,U8 | [0-0xff]
    FH_UINT8  u08MtParam0;                   // NR3D滤波参数0，值越小去低频噪声能力越强，但运动拖影明显；值越大去低频噪声能力越弱，运动拖影轻微。 | [0x0-0xff]
    FH_UINT8  u08MtParam1;                   // Nr3d滤波参数1，强度等级范围是0~4，值越小去噪能力越弱，残留噪声越大；值越大去噪能力越强，残留噪声越大。建议亮的环境配成0、1，低照环境配成2、3或4。 | [0x0-0x7]
    FH_UINT8  u08MtStr;                      // 运动估计等级，U8 | [0-0xff]
    FH_UINT8  u08Nr3dCoeffOffsetMap[GAIN_NODES]; // coeff的偏移等级，U8| [0~0xff]
    FH_UINT8  u08CoefIdxMap[GAIN_NODES];     // 不同增益下 coef idx选择 | [0-0xf]
    FH_UINT8  u08MtStrMap[GAIN_NODES];       // NR3D运动估计等级 | [0~0xff]
    FH_UINT8  u08MtParam0StrMap[GAIN_NODES];  // NR3D 运动估计参数param0等级 | [0~0xff]
    FH_UINT8  u08MtParam1StrMap[GAIN_NODES];  // NR3D 运动估计参数param1等级 | [0~0x7]
    FH_UINT8  u08MtParam1GUserX0Map[GAIN_NODES];  // NR3D 自定义mt_param1 G通道X0点 | [0~0x3f]
    FH_UINT8  u08MtParam1GUserY0Map[GAIN_NODES];  // NR3D 自定义mt_param1 G通道Y0点 | [0~0x3f]
    FH_UINT8  u08MtParam1GUserX1Map[GAIN_NODES];  // NR3D 自定义mt_param1 G通道X1点 | [0~0x3f]
    FH_UINT8  u08MtParam1GUserY1Map[GAIN_NODES];  // NR3D 自定义mt_param1 G通道Y1点 | [0~0x3f]
    FH_UINT8  u08MtParam1UserRRatioMap[GAIN_NODES];  // NR3D 自定义mt_param1 R通道占G通道比例因子 | [0~0xff]
    FH_UINT8  u08MtParam1UserBRatioMap[GAIN_NODES];  // NR3D 自定义mt_param1 B通道占G通道比例因子 | [0~0xff]
} ISP_NR3D_CFG;

typedef struct _ISP_NR3D_COEFF_CFG_
{
    FH_UINT8 u08CoeffX0; // NR3D Coeff映射线的第一个折点横坐标。X0<X1<X2<X3 | [1~0xff]
    FH_UINT8 u08CoeffX1; // NR3D Coeff映射线的第二个折点横坐标。 | [1~0xff]
    FH_UINT8 u08CoeffX2; // NR3D Coeff映射线的第三个折点横坐标。 | [1~0xff]
    FH_UINT8 u08CoeffX3; // NR3D Coeff映射线的第四个折点横坐标。 | [1~0xff]
    FH_UINT16 u16CoeffY0; // NR3D Coeff映射线的第一个折点纵坐标。Y0<=Y1<=Y2<=Y3 | [0~0xffff]
    FH_UINT16 u16CoeffY1; // NR3D Coeff映射线的第二个折点纵坐标。 | [0~0xffff]
    FH_UINT16 u16CoeffY2; // NR3D Coeff映射线的第三个折点纵坐标。 | [0~0xffff]
    FH_UINT16 u16CoeffY3; // NR3D Coeff映射线的第四个折点纵坐标。 | [0~0xffff]
} ISP_NR3D_COEFF_CFG;

/**|LTM|**/
typedef struct _ISP_LTM_CFG_S_
{
    FH_BOOL    bLtmEn;               // 线性增益模式:0 手动,1 gainMapping | [0~1]
    CURVE_TYPE eCurveType;           //曲线预设类型 | [1~2]
    FH_UINT32  u32TonemapCurve[128]; // ltm曲线设置表格 | [1~0xffffffff]
    FH_UINT32  u32LtmIdx;            //当mode为normal模式时：	0~14: 内部表系数	15:用户定义 | [0-0xf]
    FH_BOOL bMode;                   // 0：宽动态模式	1：非宽动态模式 | [0~1]
    FH_BOOL  bLtmHwEn;               // Ltm硬件模块开关 | [0-0x1]
    FH_BOOL  bYPreScalerEn;          //高亮时正常亮度和高光处比例系数设置使能 | [0-0x1]
    FH_UINT8 u08HlYScaler;           //高光处的亮度比例系数，值越大越亮，U.5 | [0-0x3f]
    FH_UINT8 u08NlYScaler;           //正常亮度处的亮度比例系数，值越大越亮，U.5， | [0-0x3f]
    FH_UINT8 u08YMaxRatio;           //统计得到的像素最大值的补偿比例因子，U.6 | [0-0xff]
    FH_UINT8 u08YMeanRatio;          //统计得到的像素平均值的补偿比例因子，U.6 | [0-0xff]
    FH_UINT8 u08YMinRatio;           //统计得到的像素最小值的补偿比例因子，U.6 | [0-0xff]
    FH_UINT8 u08NlCtr;   //正常亮度处的局部对比度，值越大对比度越大，但噪声也越大 | [0-0xff]
    FH_UINT8 u08Weight1; //正常亮度处新旧LTM融合比例，值越小，新LTM越多 | [0-0xff]
    FH_UINT8 u08Weight3; //高亮处新旧LTM融合比例，值越小，新LTM越多 | [0-0xff]
    FH_UINT8 u08Weight0; //低亮处新旧LTM融合比例，值越小，新LTM越多 | [0-0xff]
    FH_UINT8 u08Weight2; //较亮处新旧LTM融合比例，值越小，新LTM越多 | [0-0xff]
    FH_UINT8 u08NlYScalerMap[GAIN_NODES]; //正常亮度比例系数 | [0-0xff]
    FH_UINT8 u08HlYScalerMap[GAIN_NODES]; //高光处比例系数 | [0-0xff]
    FH_UINT8 u08NlCtrMap[GAIN_NODES];     //局部对比度 | [0-0xff]
    FH_UINT8 u08LtmWinIdxMap[GAIN_NODES]; //window idx选择 | [0-0xf]
    FH_UINT8 u08EpsWdr;                   //宽动态场景下滤波器参数值 | [0-0xf]
    FH_UINT8 u08EpsLinear;                //普通场景下滤波器参数值 | [0-0xf]
    FH_UINT8 u08NlYPreScaler[4];             //(1/16|1/8|1/4|1/2 inttMax)时正常亮度处的亮度比例系数，值越大越亮，U.5， | [0-0x3f]
    FH_UINT8 u08HlYPreScaler[4];             //(1/16|1/8|1/4|1/2 inttMax)时高亮处的亮度比例系数，值越大越亮，U.5， | [0-0x3f]
} ISP_LTM_CFG;
/**|NR2D|**/
typedef struct _ISP_NR2D_CFG_S_
{
    FH_BOOL   bNR2DEn;        // 2D降噪控制使能 | [0~1]
    FH_BOOL   bGainMappingEn; // 0：手动	1：增益映射 | [0~1]
    FH_UINT8  u8BlendingVal;  // nr2d所占比例 | [0-0xff]
    FH_UINT8  u8Nr2dSft;      // nr2d噪声估计移位因子,U4 | [0-0xf]
    FH_UINT8  u8CoeffOffset;  // nr2d coeff的偏移 | [0-0xf]
    FH_UINT8  u08Str;         // nr2d去噪强度,U4.4 | [0-0xff]
    FH_UINT16 u16K1;          //斜率K的斜率,U2.6 | [0-0xff]
    FH_UINT16 u16K2;          //斜率K的偏移,U8 | [0-0xff]
	FH_UINT16 u16O1;          //偏移O的斜率,U8 | [0-0x1ff]
	FH_UINT16 u16O2;          //偏移O的偏移,U8 | [0-0x1ff]
    FH_UINT8  u08StrMap[GAIN_NODES]; // nr2d等级 | [0~0xff]
} ISP_NR2D_CFG;

/**|HLR|**/
typedef struct _ISP_HLR_CFG_S_
{
    FH_BOOL  bHlrEn;   // 高光恢复控制使能 | [0-1]
    FH_SINT8 s08Level; // Hlr补偿因子 S1.7	hlr_val = hlr_val*(128+comp_level)>>7 |  [-128-127]
} ISP_HLR_CFG;
/**|IE|**/
typedef struct _ISP_CONTRAST_CFG_S_
{
    FH_BOOL  bYcEn;                 // 亮度控制使能 | [0~1]
    FH_BOOL  bGainMappingEn;        // 0：手动	1：增益映射 | [0-1]
    FH_UINT8 u08Crt;                // 手动模式下对比度 U2.6 | [0-0xff]
    FH_UINT8 u08Mid;                // 手动模式下对比度矫正的中心亮度,暂不支持 | [0-0xff]
    FH_UINT8 u08CrtMap[GAIN_NODES]; // 不同噪声强度下对比度值U2.6 | [0~0xff]
} ISP_CONTRAST_CFG;
typedef struct _ISP_BRIGHTNESS_CFG_S_
{
    FH_BOOL  bYcEn;          // 亮度控制使能 | [0~1]
    FH_BOOL  bGainMappingEn; // 0：手动	1：增益映射 | [0~1]
    FH_SINT8 s08Brt;         // 手动模式下亮度S8(-128到127) | [-128~127]
    FH_SINT8 s08BrtMap[GAIN_NODES]; // 不同噪声强度下亮度S8 | [-128~127]
} ISP_BRIGHTNESS_CFG;
/**|CE|**/
typedef struct _ISP_SAT_CFG_S_
{
    FH_BOOL  bGainMappingEn;        // 0：手动	1：增益映射 | [0~1]
    FH_SINT8 s08RollAngle;          // 色度旋转因子 | [-64,63]
    FH_UINT8 u08Sat;                //饱和度调整因子 U3.5 | [0-0xff]
    FH_UINT8 u08BlueSup;           //饱和度蓝色分量 U2.6 | [0-0xff]
    FH_UINT8 u08RedSup;            //饱和度红色分量 U2.6 | [0-0xff]
    FH_BOOL bPresetLut;            //预设亮度增益抑制LUT 0:采用内置lut映射表；1：采用自定义lut映射表|[0~1]
    FH_BOOL bGlutEn;               //亮度增益抑制使能：0: 关闭 1: 开启|[0~1]
    FH_UINT8 u08ThhSup;            //抑制阈值:值越小抑制作用越强|[0~0xff]
    FH_BOOL bThhMode;              //抑制阈值控制模式:0:手动; 1:映射|[0~1]
    FH_BOOL bThreshEn;             //阈值抑制使能：0: 关闭 1: 开启 |[0~1]
    FH_UINT8 u08SatParaR1;         //白色门限制，饱和度小于该值的会被置0 | [0-0xff]
    FH_UINT8 u08CeGainWeight;      //亮度增益抑制LUT融合权重 | [0-0xff]
    FH_UINT8 u08Gain[32][4];       //亮度增益抑制映射表：128项| [0-0xf]
    FH_UINT8 u08SatMap[GAIN_NODES]; // 不同噪声强度下亮度值U3.5 | [0~0xff]
    FH_UINT8 u08ThhMap[GAIN_NODES]; // 不同噪声强度下抑制阈值|[0~0xff]
    FH_UINT8 u08GainWeightMap[GAIN_NODES]; // 不同噪声强度下亮度增益抑制LUT融合权重|[0~0xff]
} ISP_SAT_CFG;
/**|APC|**/
typedef struct _ISP_APC_CFG_S_
{
    FH_BOOL bApcEn;    //锐度控制使能 | [0-0x1]
    FH_BOOL bPreWeightEn;// 高亮时细节与边界权重使能 | [0x0-0x1]
    FH_BOOL bLightStrEn;// 锐化强度跟随亮度变化使能 | [0x0-0x1]
    FH_BOOL bLutMode;  // LUT 系数选择模式：	0：系数表选择模式	1：手动配置系数 | [0~1]
    FH_UINT8  u08DetailLutNum;  //细节增强LUT系数选择 | [0-0x7]
    FH_UINT8  u08EdgeLutNum;    //边界锐化LUT系数选择 | [0-0x7]
    FH_BOOL   bFilterMode;      //滤波器选择模式：	0：系数表选择模式	1：手动配置系数 | [0~1]
    FH_BOOL   bLightDeStrEn;    //细节锐化强度跟随亮度变化使能 | [0x0-0x1]
    FH_BOOL   bLightEdgeStrEn;  //边界锐化强度跟随亮度变化使能 | [0x0-0x1]
    FH_UINT8  u08DetailFNum;    //细节滤波器选择 | [0-0x3]
    FH_UINT8  u08EdgeFNum;      //边界滤波器选择 | [0-0x3]
    FH_BOOL   bGainMappingEn;   // 0：手动	1：增益映射 | [0~1]
    FH_UINT8  u08Pgain;         //总体APC 正向增益 | [0-0xff]
    FH_UINT8  u08Ngain;         //总体APC 负向增益 | [0-0xff]
    FH_UINT8  u08NoiseTh;       //噪声阈值，值越大，噪声越不容易锐出来，过大会影响细节和边界|[0-0xff]
    FH_UINT8  u08DetailWeight;  // 细节锐化融合权重U4 | [0x0-0xf]
    FH_UINT8  u08EdgeWeight;    // 边界锐化融合权重U4 | [0x0-0xf]
    FH_UINT8  u08NoiseWeight;   // 去噪融合权重U4 | [0x0-0xf]
    FH_UINT8  u08Overshoot;     // 白边抑制，值越小抑制越明显 | [0x0-0xff]
    FH_UINT8  u08Undershoot;    // 黑边抑制，值越小抑制越明显 | [0x0-0xff]
    FH_UINT8 u08DetailPreWeight0;// detail pre_weight0值（1/16 inttMax 时） | [0x0-0xf]
    FH_UINT8 u08DetailPreWeight1;// detail pre_weight1值（1/8 inttMax 时） | [0x0-0xf]
    FH_UINT8 u08DetailPreWeight2;// detail pre_weight2值（1/4 inttMax 时） | [0x0-0xf]
    FH_UINT8 u08DetailPreWeight3;// detail pre_weight3值（1/2 inttMax 时） | [0x0-0xf]
    FH_UINT8 u08EdgePreWeight0;// edge pre_weight0值（1/16 inttMax 时） | [0x0-0xf]
    FH_UINT8 u08EdgePreWeight1;// edge pre_weight1值（1/8 inttMax 时） | [0x0-0xf]
    FH_UINT8 u08EdgePreWeight2;// edge pre_weight2值（1/4 inttMax 时） | [0x0-0xf]
    FH_UINT8 u08EdgePreWeight3;// edge pre_weight3值（1/2 inttMax 时） | [0x0-0xf]
    FH_UINT16 u16LightGainThl;// 锐化强度跟随亮度变化增益下阈值，单位为倍数 | [0x0-0xfff]
    FH_UINT16 u16LightGainThh;// 锐化强度跟随亮度变化增益上阈值，单位为倍数 | [0x0-0xfff]
    FH_UINT8 u08Light0PstrThl;// 亮度等级0在增益不大于gain_thl时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light1PstrThl;// 亮度等级1在增益不大于gain_thl时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light2PstrThl;// 亮度等级2在增益不大于gain_thl时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light3PstrThl;// 亮度等级3在增益不大于gain_thl时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light0PstrThh;// 亮度等级0在增益大于gain_thh时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light1PstrThh;// 亮度等级1在增益大于gain_thh时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light2PstrThh;// 亮度等级2在增益大于gain_thh时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light3PstrThh;// 亮度等级3在增益大于gain_thh时正向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light0NstrThl;// 亮度等级0在增益不大于gain_thl时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light1NstrThl;// 亮度等级1在增益不大于gain_thl时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light2NstrThl;// 亮度等级2在增益不大于gain_thl时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light3NstrThl;// 亮度等级3在增益不大于gain_thl时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light0NstrThh;// 亮度等级0在增益大于gain_thh时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light1NstrThh;// 亮度等级1在增益大于gain_thh时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light2NstrThh;// 亮度等级2在增益大于gain_thh时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8 u08Light3NstrThh;// 亮度等级3在增益大于gain_thh时负向强度，U4.4 | [0x0-0xff]
    FH_UINT8  u08NoiseThMap[GAIN_NODES];     // 不同噪声强度下噪声阈值| [0~0xff]
    FH_UINT8  u08PgainMap[GAIN_NODES];       // 不同噪声强度下白边界强度值U2.6 | [0~0xff]
    FH_UINT8  u08NgainMap[GAIN_NODES];       // 不同噪声强度下黑边界强度值U2.6 | [0~0xff]
    FH_UINT8  u08DetailWeightMap[GAIN_NODES];// 不同噪声强度下细节滤波系数值 | [0~0xf]
    FH_UINT8  u08EdgeWeightMap[GAIN_NODES];  // 不同噪声强度下边界LUT系数值 | [0~0xf]
    FH_UINT8  u08NoiseWeightMap[GAIN_NODES]; // 不同噪声强度下细节滤波系数值 | [0~0xf]
    FH_UINT8  u08DetailLutNumMap[GAIN_NODES];// 不同噪声强度下边界滤波系数值 | [0~0x7]
    FH_UINT8  u08EdgeLutNumMap[GAIN_NODES];  // 不同噪声强度下Lut系数选择| [0~0x7]
    FH_UINT8  u08DetailFNumMap[GAIN_NODES];  // 不同噪声强度下细节filter系数选择| [0~0x3]
    FH_UINT8  u08EdgeFNumMap[GAIN_NODES];    // 不同噪声强度下边界filter系数选择| [0~0x3]
    FH_UINT16 u16LightDeGainThl;// 细节锐化强度跟随亮度变化增益下阈值，单位为倍数 | [0x0-0xfff]
    FH_UINT16 u16LightDeGainThh;// 细节锐化强度跟随亮度变化增益上阈值，单位为倍数 | [0x0-0xfff]
    FH_UINT8  u8DeLightPstrThl[6];// 亮度等级1~6在增益不大于gain_thl时正向强度偏移，值越大强度越小 | [0x0-0xff]
    FH_UINT8  u8DeLightPstrThh[6];// 亮度等级1~6在增益大于gain_thh时正向强度偏移，值越大强度越小 | [0x0-0xff]
    FH_UINT8  u8DeLightNstrThl[6];// 亮度等级1~6在增益不大于gain_thl时负向强度偏移，值越大强度越小 | [0x0-0xff]
    FH_UINT8  u8DeLightNstrThh[6];// 亮度等级1~6在增益大于gain_thh时负向强度偏移，值越大强度越小 | [0x0-0xff]
    FH_UINT16 u16LightEdgeGainThl;// 边界锐化强度跟随亮度变化增益下阈值，单位为倍数 | [0x0-0xfff]
    FH_UINT16 u16LightEdgeGainThh;// 边界锐化强度跟随亮度变化增益上阈值，单位为倍数 | [0x0-0xfff]
    FH_UINT8  u8EdgeLightPstrThl[6];// 亮度等级1~6在增益不大于gain_thl时正向强度偏移，值越大强度越小 | [0x0-0xff]
    FH_UINT8  u8EdgeLightPstrThh[6];// 亮度等级1~6在增益大于gain_thh时正向强度偏移，值越大强度越小 | [0x0-0xff]
    FH_UINT8  u8EdgeLightNstrThl[6];// 亮度等级1~6在增益不大于gain_thl时负向强度偏移，值越大强度越小 | [0x0-0xff]
    FH_UINT8  u8EdgeLightNstrThh[6];// 亮度等级1~6在增益大于gain_thh时负向强度偏移，值越大强度越小 | [0x0-0xff]
} ISP_APC_CFG;

typedef struct _ISP_APC_MT_CFG_S_ {
    FH_BOOL bApcMtEn;     // apc联动使能：0: Off 1: On|[0-0x1]
    FH_BOOL bApcMtMode;   // apc联动模式：0: manual 1: gain mapping|[0-0x1]
    FH_UINT8 u08MtStr;    // 联动强度，越大运动区域越模糊|[0~0xff]
    FH_SINT16 s16MtOffset;// 联动偏移，越大运动区域越模糊|[-256~255]
    FH_UINT8 u08MtStrMap[GAIN_NODES];// 联动强度|[0~0xff]
} ISP_APC_MT_CFG;

/**|YCNR|**/
typedef struct _ISP_YNR_CFG_S_ {
    FH_BOOL bYnrEn;  // ynr控制使能 | [0~1]
    FH_BOOL bGainMappingEn;  // ynr gainMapping control mode: 0:gain mapping OFF 1:gainMapping ON | [0~1]
    FH_BOOL bCtrlMode;  // ynr模式: 0:弱模式　1:强模式| [0~1]
    FH_UINT8 u08YnrThSlope0; //高频映射斜率  | [0~0xff]
    FH_UINT8 u08YnrThSlope2; //中频映射斜率  | [0~0xff]
    FH_UINT8 u08YnrThSlope1; //低频映射斜率  | [0~0xff]
    FH_UINT8 u08MergeWeight;  //融合权重 （去噪结果与原始输入融合，weight权重越大，原始输入权重越大，去噪越弱）| [0~0xff]
    FH_UINT8 u08YnrThStr0; //YNR高频降噪去噪等级　| [0~0xff]
    FH_UINT8 u08YnrThStr1; //YNR中频降噪去噪等级　| [0~0xff]
    FH_UINT8 u08YnrThStr2; //YNR低频降噪去噪等级　| [0~0xff]
    FH_UINT16 u08Thl0[16];  //YNR亮度阈值（高频分量） | [0~0xff]
    FH_UINT16 u08Thl1[16];  //YNR亮度阈值（中频分量） | [0~0xff]
    FH_UINT16 u08Thl2[16];  //YNR亮度阈值（低频分量） | [0~0xff]
    FH_UINT8 u08YnrMergeWeightMap[GAIN_NODES];  //不同噪声强度下融合权重值　| [0~0xff]
    FH_UINT8 u08YnrThSlope0Map[GAIN_NODES]; //不同噪声强度下映射斜率（高频）  | [0~0xff]
    FH_UINT8 u08YnrThSlope1Map[GAIN_NODES]; //不同噪声强度下映射斜率（中频）  | [0~0xff]
    FH_UINT8 u08YnrThSlope2Map[GAIN_NODES]; //不同噪声强度下映射斜率（低频）  | [0~0xff]
    FH_UINT16 u08YnrThStr0Map[GAIN_NODES];  //不同噪声强度下亮度去噪强度（高频）　| [0~0xff]
    FH_UINT16 u08YnrThStr1Map[GAIN_NODES];  //不同噪声强度下亮度去噪强度（中频）　| [0~0xff]
    FH_UINT16 u08YnrThStr2Map[GAIN_NODES];  //不同噪声强度下亮度去噪强度（低频）　| [0~0xff]
} ISP_YNR_CFG;

typedef struct _ISP_YNR_MT_CFG_S_ {
    FH_BOOL bCoefEn; //YNR与NR3D联动使能 0：关 1：开
    FH_BOOL bCoefGainMappingEn;// ynr mt gainMapping control mode: 0:gain mapping OFF 1:gainMapping ON | [0~1]
    FH_UINT8 u08MtCoeff0;  //YNR与NR3D联动去噪第一个coeff分界点，小运动 | [0~0xff]
    FH_UINT8 u08MtCoeff1;  //YNR与NR3D联动去噪第二个coeff分界点，大运动 | [0~0xff]
    FH_UINT8 u08YnrMtStrM0;  //YNR与NR3D联动去噪第一级强度，小运动 | [0~0xff]
    FH_UINT8 u08YnrMtStrM1;  //YNR与NR3D联动去噪第二级强度，大运动 | [0~0xff]
    FH_UINT8 u08YnrMtStr0Map[GAIN_NODES];  //运动去噪等级（小运动） | [0~0xff]
    FH_UINT8 u08YnrMtStr1Map[GAIN_NODES];  //运动去噪等级（大运动） | [0~0xff]
} ISP_YNR_MT_CFG;

typedef struct _ISP_CNR_CFG_S_
{
    FH_BOOL  bCnrEn;           //色度降噪控制使能 | [0-0x1]
    FH_UINT8 u08CnrStr;        //色度去噪强度 | [0-0xff]
	FH_UINT8 u08ColThh;        //饱和度阈值上限。满足约束：SatThH>SatThL。值越大，饱和度保护越好，同时去噪效果越弱|[0~0xff]
	FH_UINT8 u08ColThl;        //饱和度阈值下限。值越小，饱和度保护越好，同时去噪效果越弱。|[0-0xff]
    FH_BOOL  bGainMappingEn;   // 0：手动	1：增益映射 | [0~1]
    FH_UINT8 u08StrMap[GAIN_NODES]; // 不同增益下的色度噪声等级,gainMapping模式用 | [0~0xff]
    FH_UINT8 u08ColThlMap[GAIN_NODES];//饱和度阈值下限|[0~0xff]
    FH_UINT8 u08ColThhMap[GAIN_NODES];//饱和度阈值上限|[0~0xff]
} ISP_CNR_CFG;

typedef struct _ISP_CNR_MT_CFG_S_
{
	FH_BOOL bCnrMtEn;        //CNR联动使能0: 关;   1:开|[0-0x1]
	FH_BOOL bCnrMtStrMode;   //CNR联动强度模式 0: manual;   1:gain mapping|[0-0x1]
	FH_UINT8 u08CnrMtColStr; //cnr联动饱和度保护强度|[0~0xf]
	FH_UINT8 u08CnrMtStr;    //cnr联动强度，越大运动区域色度降噪越强| [0-0xff]
	FH_SINT16 s16CnrMtOffset;//cnr联动偏移，越大整体色度去噪越强|[-254 - 255]
    FH_UINT8 u08MtStrMap[GAIN_NODES]; //cnr联动强度等级| [0-0xff]
} ISP_CNR_MT_CFG;

/**|DEHAZE|**/
typedef struct _ISP_DEHAZE_CFG_S_
{
	FH_BOOL bDehazeHwEn;                    //去雾功能硬件开关|[0-0x1]
	FH_UINT8 u08DehazeStr;                  //手动模式下总的去雾强度, 值越大去雾力度越强|[0-0xff]
	FH_BOOL bPresetLut;                     //0：采用内置lut映射表 1：采用自定义lut映射表|[0-0x1]
	FH_BOOL bGainMappingEn;                 //控制模式0: manual 1: gain mapping|[0-0x1]
	FH_UINT8 u08DehazeStrMap[GAIN_NODES];   //去雾强度等级|[0-0xff]
	FH_UINT16 u16DehazeLutData[33][2];      //根据不同亮度配置去雾强度映射表，共66项，一般情况下，暗处去雾强度弱，亮处去雾强度强。最大65/66项0x00000fff不用配|[0-0xfff]
} ISP_DEHAZE_CFG;

typedef struct _ISP_DE_CFG_S_
{
	FH_BOOL bDarkEnhanceEn;                 //暗部增强功能开关，与去雾功能互斥|[0-0x1]
	FH_UINT8 u08DeStr;                      //暗部增强强度, 值越大暗部增强力度越强|[0-0xff]
	FH_UINT8 u08GainThl;                    //暗部增强作用时增益下限，最小为1倍增益|[0x1-0xff]
	FH_UINT8 u08GainThh;                    //暗部增强作用时增益上限，必须满足u08GainThh > u08GainThl|[0x2-0xff]
} ISP_DE_CFG;

/**|PURPLE|**/
typedef struct _ISP_PURPLEFRI_CFG_S_
{
    FH_BOOL bPurpleEn; //去紫边控制使能 | [0-0x1]
    FH_SINT8 s08Shiftbits; //校正力度调整单元，通过移位增大或减小饱和度（当为正数时表示左移，当为负数时表示右移），范围为[-8,3]。| [-8,3]
    FH_BOOL   bSatcorrenable; //饱和度校正使能 | [0~1]
    FH_UINT16 u16Rollangle;   //旋转因子，单位为度° | [0-0x1ff]
    FH_UINT16 u16Adjangle;    //调整区域因子，单位为度° | [0-0x1ff]
    FH_UINT16 u16Ygapth; // 7x7窗亮度分量最大值和最小值之差的最小阈值，YMax-YMin>=YGapTh | [0-0x3ff]
    FH_UINT16 u16Yth;    // 7x7窗亮度分量最大值的最小阈值，YMax >= YTh | [0-0x3ff]
    FH_UINT16 u16Expoth; //亮度分量的最大阈值，Y<ExpoTh | [0-0x3ff]
    FH_SINT16 s16Ulth;   //旋转后色度分量U’最小阈值，U’>ULth | [-512-511]
    FH_SINT16 s16Uhth;   //旋转后色度分量U’最大阈值，U’<UHth | [-512-511]
    FH_UINT16 u16Satthh; //饱和度最大阈值，	Sat(YMax)< SatThH | [0-0x3ff]
    FH_UINT16 u16Satthl; //饱和度最小阈值，Sat> SatThL | [0-0x3ff]
} ISP_PURPLEFRI_CFG;

/**|LC|**/
typedef struct _ISP_LC_CFG_S_
{
    FH_BOOL   bLc0En;   //第一个色度调整使能 | [0x0-0x1]
    FH_UINT8  u08Gain0; //中心增益：0.6-3.98(0x27-0xff，小于0x27的按0x27处理)U2.6 | [0x0-0xff]
    FH_UINT8  u08Alpha0; //调整范围角度阿尔法：15-89(0x0f-0x59,小于0x0f的按0x0f处理，大于0x59的按0x59处理) | [0x0-0xff]
    FH_UINT16 u16Theta0; //中心线角度西塔：0-359(0x0-0x167，大于0x167的按0x167处理) | [0x0-0x1ff]
    FH_BOOL   bLc1En;    //第二个色度调整使能 | [0x0-0x1]
    FH_UINT8  u08Gain1;  //中心增益：0.6-3.98(0x27-0xff，小于0x27的按0x27处理)U2.6 | [0x0-0xff]
    FH_UINT8  u08Alpha1; //调整范围角度阿尔法：15-89(0x0f-0x59,小于0x0f的按0x0f处理，大于0x59的按0x59处理) | [0x0-0xff]
    FH_UINT16 u16Theta1; //中心线角度西塔：0-359(0x0-0x167，大于0x167的按0x167处理) | [0x0-0x1ff]
    FH_BOOL   bLc2En;    //第三个色度调整使能 | [0x0-0x1]
    FH_UINT8  u08Gain2;  //中心增益：0.6-3.98(0x27-0xff，小于0x27的按0x27处理)U2.6 | [0x0-0xff]
    FH_UINT8  u08Alpha2; //调整范围角度阿尔法：15-89(0x0f-0x59,小于0x0f的按0x0f处理，大于0x59的按0x59处理) | [0x0-0xff]
    FH_UINT16 u16Theta2; //中心线角度西塔：0-359(0x0-0x167，大于0x167的按0x167处理) | [0x0-0x1ff]
} ISP_LC_CFG;

/**|AF|**/
//----------------AF-------------------
typedef struct _ISP_AF_FILTER_S
{
    FH_UINT8  afStatChannel;       // 统计对象选择，0~3分别对应C0/C1/C2/C3，例如如果当前bayer为RGGB则C0/C1/C2/C3分别对应R/G/G/B | [0~3]
    FH_UINT8  afStatHFilterMode;   // 水平滤波模式选择 | [0~0x1]
    FH_UINT16 afGMapX[2];          // gMap三段式折点拐点横坐标 | [0~0xffff]
    FH_UINT16 afGmapS[3];          // gMap三段式折线直线斜率 | [0~0x3ff]
    FH_UINT16 afLumTl;            // 亮度统计亮度門限下阈值 | [0~0xfff]
    FH_UINT16 afLumTh;            // 亮度统计亮度門限上阈值 | [0~0xfff]
    FH_SINT8  afPreFilterCoe[7];   // 预滤波滤波器系数 | [0~0xf]
    FH_UINT16 afPreFilterMul;      // 预滤波滤波器乘系数 | [0-0x3ff]
    FH_UINT16 afPreFilterShift;    // 预滤波滤波器移位因子 | [0~0xf]
    FH_SINT8  afVfilter0[25];      // 垂直滤波器0系数 | [0~0xf]
    FH_UINT16 afVFilter0Shift;     // 垂直滤波器0移位因子 | [0~0xf]
    FH_UINT16 afVFilter0T;         // 垂直滤波器0門限阈值 | [0~0xfff]
    FH_SINT8  afVfilter1[25];      // 垂直滤波器1系数 | [0~0xf]
    FH_UINT16 afVFilter1Shift;     // 垂直滤波器1移位因子 | [0~0xf]
    FH_UINT16 afVFilter1T;         // 垂直滤波器1門限阈值 | [0~0xfff]
    FH_BOOL   afHfilter0En[3];     // 水平滤波器0第1/2/3级滤波器使能 | [0~1]
    FH_UINT8  afHfilter0Gain;      // 水平滤波器0增益 | [0~0xff]
    FH_UINT16 afHFilter0T;         // 水平滤波器0門限阈值 | [0~0xfff]
    FH_SINT16 afHFilter0Offset;    // 水平滤波器0输出偏移 | [0~0x1fff]
    FH_UINT8  afHFilter0Shift[7];  // 水平滤波器0移位因子 | [0~0xf]
    FH_UINT16 afHFilter0C[6];      // 水平滤波器0滤波器系数C | [0~0x7ff]
    FH_UINT16 afHFilter0D[6];      // 水平滤波器0滤波器系数D | [0~0x7ff]
    FH_BOOL   afHfilter1En[3];     // 水平滤波器1第1/2/3级滤波器使能 | [0~1]
    FH_UINT8  afHfilter1Gain;      // 水平滤波器1增益 | [0~0xff]
    FH_UINT16 afHFilter1T;         // 水平滤波器1門限阈值 | [0~0xfff]
    FH_SINT16 afHFilter1Offset;    // 水平滤波器1输出偏移 | [0~0x1fff]
    FH_UINT8  afHFilter1Shift[7];  // 水平滤波器1移位因子 | [0~0xf]
    FH_UINT16 afHFilter1C[6];      // 水平滤波器1滤波器系数C | [0~0x7ff]
    FH_UINT16 afHFilter1D[6];      // 水平滤波器1滤波器系数D | [0~0x7ff]

} ISP_AF_FILTER;

typedef struct _ISP_AF_STAT_ADDR_S
{
    FH_UINT32 startAddr;      // AF统计信息存放地址| [0~0xffffffff]
} ISP_AF_STAT_ADDR;

/**|GME|**/
typedef struct _ISP_GME_PARAM_S_
{
    FH_SINT32 s32x; // x vector | [0~0xffffffff]
    FH_SINT32 s32y; // y vector | [0~0xffffffff]
} ISP_GME_PARAM;

/**|WDR|**/

typedef struct _ISP_WDR_MERGE_CFG_
{
    FH_UINT16 u16MergeX0; // Merge曲线的第一个折点横坐标。 | [0~0xffff]
    FH_UINT16 u16MergeX1; // Merge曲线的第二个折点横坐标。 | [0~0xffff]
    FH_UINT16 u16MergeX2; // Merge曲线的第三个折点横坐标。 | [0~0xffff]
    FH_UINT16 u16MergeX3; // Merge曲线的第四个折点横坐标。 | [0~0xffff]
    FH_UINT16 u16MergeY0; // Merge曲线的第一个折点纵坐标。 | [0~0xffff]
    FH_UINT16 u16MergeY1; // Merge曲线的第二个折点纵坐标。 | [0~0xffff]
    FH_UINT16 u16MergeY2; // Merge曲线的第三个折点纵坐标。 | [0~0xffff]
    FH_UINT16 u16MergeY3; // Merge曲线的第四个折点纵坐标。 | [0~0xffff]
} ISP_WDR_MERGE_CFG;

typedef struct _ISP_WDR_CFG_S_
{
    FH_BOOL bWdrEn;             //宽动态控制使能 | [0-0x1]
    FH_BOOL bShowHist;          //打印hist统计使能	0：关闭	1：使能 | [0~1]
    FH_BOOL bMode;              // 0：宽动态模式	1：非宽动态模式 | [0~1]
    FH_BOOL  bAutoAdjustEn;     //自动曝光比例调整使能 | [0~1]
    FH_UINT8 u08SframeCorrMode; //短帧亮度校正模式选择	0：自动模式，自动配置短帧亮度校正曲线 1：自定义模式，用户通过api设置短帧亮度校正曲线 | [0~1]
    FH_UINT8 u08MergeCurveMode; //长短帧merge曲线模式选择	0：采用内置merge曲线，根据pre_curve_idx确定 1：自定义模式，用户通过api设置长短帧merge曲线 | [0~1]
    FH_UINT16 u16SensorOutputMax;  // Sensor最大输出，用于数据通路归一化 | [0-0xfff]
    FH_UINT16 u16SframeCorrTiming; //短帧亮度校正与短帧intt的生效时机控制：	0：同一帧生效 其他：短帧亮度校正推迟1/2/3帧生效 | [0-0x3]
    FH_UINT8  u08ExposureRatio;    // auto_adjust_en为0时，长短帧曝光比例：(6~64倍)  | [0-0xff]
    FH_UINT8  u08ExposureRatioMin; // auto_adjust_en为1时，长短帧曝光比例最小值值，不能小于6 | [0-0xff]
    FH_UINT8  u08ExposureRatioMax; // auto_adjust_en为1时，长短帧曝光比例最大值，不能大于64 | [0-0xff]
    FH_UINT16 u16WdrDc;            // WDR DC值配置 | [0-0xfff]
    FH_UINT8  u08WdrMergeCfg;      // WDR merge曲线配置	0:两帧合成输出	1:只出长帧	2:只出短帧 | [0-0x3]
    FH_UINT8  u08PreCurveIdx;      // Merge预设曲线 | [0-0x3]
    FH_UINT16 u16LfOverexpRatioThh; //长帧过曝比例(百分数)上阈值U6.6 | [0-0xfff]
    FH_UINT16 u16LfOverexpRatioThl; //长帧过曝比例(百分数)下阈值U6.6 | [0-0xfff]
    FH_UINT16 u16SfOverexpRatioTh;  //短帧过曝比例(百分数)阈值U2.10 | [0-0xfff]
    FH_UINT16 u16GainTh;            //增益门限值 | [0-0xfff]
} ISP_WDR_CFG;

/**|POST_GAIN|**/
typedef struct _ISP_POST_GAIN_CFG_S
{
    FH_UINT16 rGain;        //R分量增益 | [0-0xfff]
    FH_UINT16 gGain;        //G分量增益 | [0-0xfff]
    FH_UINT16 bGain;        //B分量增益 | [0-0xfff]
    FH_UINT16 rOffset;      //R分量黑度补偿 | [0-0xfff]
    FH_UINT16 gOffset;      //G分量黑度补偿 | [0-0xfff]
    FH_UINT16 bOffset;      //B分量黑度补偿 | [0-0xfff]
} ISP_POST_GAIN_CFG;
/**|RGBA|**/
typedef struct _RGBA_ABAL_CFG_S_
{
    FH_UINT8 abalSpeed;          // Abal的调整速度 | [0~0xf]
    FH_UINT8 abalThl;            // Abal不调整的阈值 | [0~0xf]
    FH_UINT8 abalThh;            // Abal开始调整的阈值 | [0~0xf]
    FH_UINT8 abalStabTime;       // Abal的稳定时间 | [0~0xff]
    FH_UINT8 abalStep;           // ABal调整的步长 | [0~0xf]
    FH_UINT8 abalTargetStabTime; // AbalTarget的稳定时间 | [0~0xff]
    FH_UINT8 abalTargetThr;      // AbalTarget的调整阈值 | [0~0xf]
} RGBA_ABAL_CFG;

typedef struct _RGBA_WEIGHT_CFG_S_
{
    FH_UINT8  W2Speed;    // W2的调整速度 | [0~0xf]
    FH_UINT8  W2Thl;      // W2的不调整阈值 | [0~0xf]
    FH_UINT8  W2Thh;      // W2开始调整的阈值 | [0~0xf]
    FH_UINT8  W2StabTime; // W2的稳定时间 | [0~0xf]
    FH_UINT8  W2Step;     // W2的调整步长 | [0~0xf]
    FH_UINT8  W2AThl;     // W2计算时增益的上阈值 | [0~0x7f]
    FH_UINT8  W2AThh;     // W2计算时增益的下阈值 | [0~0x7f]
    FH_UINT16 W2GThl;     // W2计算时红外的下阈值 | [0~0x7f]
    FH_UINT16 W2GThh;     // W2计算时红外的上阈值 | [0~0x7f]
} RGBA_WEIGHT_CFG;

typedef struct _RGBA_CCM_TABLE_S_
{
    FH_UINT16 RgbaCcmTable[2][16]; // rgba ccm矩阵系数 | [-4096~4095]
} RGBA_CCM_TABLE;

typedef struct _RGBA_CONVERT_TH_S_
{
    FH_UINT16 convThl; // 格式转换模块LUT上阈值 | [0~0xffff]
    FH_UINT16 convThh; // 格式转换模块LUT下阈值 | [0~0xffff]
} RGBA_CONVERT_TH;

typedef struct _RGBA_ENHANCE_TH_S_
{
    FH_UINT16 enhThl; // 亮度/锐度增强模块亮度下阈值 | [0~0xffff]
    FH_UINT16 enhThh; // 亮度/锐度增强模块亮度上阈值 | [0~0xffff]
} RGBA_ENHANCE_TH;

typedef struct _RGBA_ETH_S_
{
    FH_UINT16 eThl; // 边界强度下限 | [0~0xffff]
    FH_UINT16 eThh; // 边界强度上限 | [0~0xffff]
} RGBA_ETH;

typedef struct _RGBA_EGAIN_CFG_S_
{
    FH_UINT8 egainR; // 亮度/锐度增强模块R通道增强增益 | [0~0xff]
    FH_UINT8 egainG; // 亮度/锐度增强模块G通道增强增益 | [0~0xff]
    FH_UINT8 egainB; // 亮度/锐度增强模块B通道增强增益 | [0~0xff]
} RGBA_EGAIN_CFG;

typedef struct _RGBA_DEFAULT_CFG_S_
{
    FH_BOOL         bRgbaEn;     // RGBA控制使能 | [0~1]
    FH_BOOL         bIrmode;     // Abal是否使能 | [0~1]
    FH_BOOL         bFirFrm;     // 是否是第一帧标志 | [0~1]
    RGBA_ABAL_CFG   abalParam;   // Abal参数结构体 | [RGBA_ABAL_CFG]
    RGBA_WEIGHT_CFG weightParam; // W2参数结构体 | [RGBA_WEIGHT_CFG]
    RGBA_CCM_TABLE  ccmTab;      // ccm矩阵表 | [RGBA_CCM_TABLE]
    RGBA_CONVERT_TH convTh;      // 格式转换LUT阈值参数结构体 | [RGBA_CONVERT_TH]
    RGBA_ENHANCE_TH enhTh;       // 亮度/锐度阈值参数结构体 | [RGBA_ENHANCE_TH]
    RGBA_ETH        eTh;         // 边界强度参数结构体 | [RGBA_ETH]
    RGBA_EGAIN_CFG  egain;       // 分通道亮度/锐度增强模块增益参数结构体 | [RGBA_EGAIN_CFG]
} RGBA_DEFAULT_CFG;

typedef struct _RGBA_CURR_INFO_S_
{
    FH_UINT16 u08RBalGainPre;   // 上一帧RBalGain | [0~0xffff]
    FH_UINT8  u08RBalCnt;       // 当前RBal稳定时间计数 | [0~0xff]
    FH_UINT8  u08RBalTargetCnt; // 当前RBal目标值的稳定时间计数 | [0~0xff]
    FH_UINT16 u16W2Pre;         // 上一帧CCM2权重 | [0~0x7fff]
    FH_UINT16 u16W2Cnt;         // W2的稳定时间计数 | [0~0xff]
} RGBA_CURR_INFO;

typedef enum _RGBA_CMD_KEY_S_ {
    SET_RGBA_DEFAULT   = 0x0, // 配置RGBA　DRV寄存器
    SET_RGBA_EN        = 0x1, // RGBA策略使能开关
    SET_RGBA_FIRFRM    = 0x2, // 配置RGBA处理第一帧标志
    SET_RGBA_IRMODE    = 0x3, // Abal使能
    SET_ABAL_PARA      = 0x4, // 配置Abal相关DRV参数
    SET_WEIGHT_PARA    = 0x5, // 配置W2相关DRV参数
    SET_RGBA_CCM_TABLE = 0x6, // 配置RGBA的CCM矩阵
    SET_CONVERT_TH     = 0x7, // 格式转换LUT上下阈值配置
    SET_ENHANCE_TH     = 0x8, //  亮度/锐度上下阈值设置
    SET_ETH            = 0x9, // 边界强度上下阈值设置
    SET_EGAIN          = 0xa, // RGB通道亮度/锐度增强模块增益设置
    RGBA_CMD_KEY_DUMMY =0xffffffff,
} RGBA_CMD_KEY;

typedef struct _RGBA_STAT_INFO_S_
{
    struct rgba_blk_info
    {
        FH_UINT32 R_sum;  // RGBA统计值R sum | [0~0xffffffff]
        FH_UINT32 G_sum;  // RGBA统计值G sum | [0~0xffffffff]
        FH_UINT32 B_sum;  // RGBA统计值B sum | [0~0xffffffff]
        FH_UINT32 A_sum;  // RGBA统计值A sum | [0~0xffffffff]
        FH_UINT32 IR_sum; // RGBA统计值IR sum | [0~0xffffffff]
        FH_UINT32 cnt;    // RGBA统计值CNT | [0~0xffffffff]
    } blk_rgba[32];
} RGBA_STAT_INFO;

typedef struct _RGBA_DPC_CFG_S
{
    FH_BOOL   bRGBADpcEn;              // RGBA模式下的dpc控制使能 | [0~1]
    FH_BOOL   bGainMappingEn;          // 0：手动	1：增益映射 | [0~1]
    FH_UINT8  u08DpcMode;              // 0:all close;1:white pixel correct open;2.black pixel correct open;3.all open.
    FH_UINT8  u08ModeIdx;              // 去坏点强度 | [0~2]
    FH_UINT8  u08Str;                  // nr2d去噪强度,U1.3 | [0-0xf]
    FH_UINT8  u08wdc;                  //手动白点门限值 | [0-0xff]
    FH_UINT8  u08bdc;                  //手动黑点门限值 | [0-0xff]
    FH_UINT8  u08ThhIR;                // IR通道比值上阈值 | [0~0x3f]
    FH_UINT8  u08ThlIR;                // IR通道比值下阈值 | [0~0xf]
    FH_UINT8  u08ThhG;                 // G通道比值上阈值 | [0~0x3f]
    FH_UINT8  u08ThlG;                 // G通道比值下阈值 | [0~0xf]
    FH_UINT16 u16DiffMin;              // 变化程度的最小值 | [0~0x3ff]
    FH_UINT8  u08DiffShift;            // 变化程度的移位值 | [0~0xf]
    FH_UINT8  u08Strenght[GAIN_NODES]; // 包括:mode,w_s,b_s
    FH_UINT8  u08WhiteThr[GAIN_NODES]; //白点门限DC值
    FH_UINT8  u08BlackThr[GAIN_NODES]; //黑点门限值
} RGBA_DPC_CFG;

/**|SMART IR|**/
typedef struct _SMART_IR_CFG_S
{
    FH_UINT16 u16gainDay2Night; // 白天切换到夜晚的增益門限，bayer sensor | [0~0xffff]
    FH_UINT16 u16gainNight2Day; // 夜晚切换到白天的增益門限，bayer sensor | [0~0xffff]
    FH_UINT16 u16lumaDay2Night; // 白天切换到夜晚的增益門限，rgbir sensor | [0~0xfff]
    FH_UINT16 u16lumaNight2Day; // 夜晚切换到白天的增益門限，rgbir sensor | [0~0xfff]
} SMART_IR_CFG;

/**|FC|**/

typedef struct _FC_CFG_S
{
    FH_UINT8 str; // 去假色强度 | [0~0xff]
    FH_UINT16 u16OffsetT; // 纹理信息偏移量 | [0~0xffff]
    FH_UINT16 u16OffsetY; // 亮度信息偏移量 | [0~0xffff]
} FC_CFG;

/**|LCE|**/
typedef struct _ISP_LCE_CFG_S_ {
	FH_BOOL bMergecurvemode;  // 0：内置MERGE表 1：用户自定义MERGE表|| [0~1]
	FH_UINT8 u08Mergecurvenum;// 仅内置模式下有0-3 共四条曲线|| [0~3]
	FH_BOOL bGainMappingEn;   // lce控制模式|| [0~1]
	FH_BOOL bLceHwEn;         //硬件开关|| [0~1]
	FH_BOOL bMergesel;        // 结果是否与原始输入融合：0：不融合 1：融合|| [0~1]
	FH_UINT8 u08Kneex1;       //权重LUT的第二个点横坐标, 第一个点固定为0|| [0~0xf]
	FH_UINT8 u08Kneex2;       //权重LUT的第三个点横坐标|[0~0xf]
	FH_UINT8 u08Kneex3;       //权重LUT的第四个点横坐标|[0~0xf]
	FH_UINT8 u08Kneex4;       //权重LUT的第五个点横坐标，第六个点固定为1023|[0~0xf]
	FH_UINT8 u08Kneey0;       //权重LUT的第一个点纵坐标|[0~0xf]
	FH_UINT8 u08Kneey1;       //权重LUT的第二个点纵坐标|[0~0xf]
	FH_UINT8 u08Kneey2;       //权重LUT的第三个点纵坐标|[0~0xf]
	FH_UINT8 u08Kneey3;       //权重LUT的第四个点纵坐标|[0~0xf]
	FH_UINT8 u08Kneey4;       //权重LUT的第五个点纵坐标|[0~0xf]
	FH_UINT8 u08Kneey5;       //权重LUT的第六个点纵坐标|[0~0xf]
	FH_UINT8 u08LceStr;       //局部对比度强度|[0~0xf]
	FH_UINT8 u08Cgain;        //色度补偿因子，值越大，饱和度提升越大，U.6|[0~0xf]
	FH_UINT8 u08Coffset;      //色度偏移因子，主要针对暗处，值越大，暗处色度补偿越小，对色噪友好|[0~0xf]
    FH_UINT8 u08StrMap[GAIN_NODES];//局部对比度强度|[0~0xf]
    FH_UINT8 u08CgainMap[GAIN_NODES];//色度补偿因子|[0~0xf]
    FH_UINT8 u08CoffsetMap[GAIN_NODES];//色度偏移因子|[0~0xf]
} ISP_LCE_CFG;


/**|STATISTICS|**/
typedef struct _ISP_STAT_WIN_S_
{
    FH_UINT16 winHOffset;  // 统计窗口水平偏移 | [0~PicW]
    FH_UINT16 winVOffset;  // 统计窗口垂直偏移 | [0~PicH]
    FH_UINT16 winHSize;    // 统计窗口宽度 | [0~(PicW-winHOffset)]
    FH_UINT16 winVSize;    // 统计窗口高度 | [0~(PicH-winVOffset)]
} ISP_STAT_WIN;

typedef struct _ISP_STAT_WIN1_S_
{
    FH_UINT16 winHOffset;  // 统计窗水平方向偏移 | [0~0xfff]
    FH_UINT16 winVOffset;  // 统计窗垂直方向偏移 | [0~0xfff]
    FH_UINT16 winHSize;    // 统计窗总宽度 winHOffset+winHSize<=picW | [0~0xfff]
    FH_UINT16 winVSize;    // 统计窗总高度 winHOffset+winHSize<=picH| [0~0xfff]
    FH_UINT8 winHCnt;      // 全局统计水平方向窗口个数 | [1~32]
    FH_UINT8 winVCnt;      // 全局统计垂直方向窗口个数 | [1~32]
} ISP_STAT_WIN1;

typedef struct _ISP_AE_STAT_CFG_S_
{
    ISP_STAT_WIN stStatWin;  // 统计窗口配置 | [ISP_STAT_WIN]
} ISP_AE_STAT_CFG;


typedef struct _ISP_AE_STAT_S_
{
    FH_UINT32 u32SumLuma[9];  // ae统计sum值 | [0~0xffffffff]
    FH_UINT32 u32Cnt[9];      // ae统计cnt值 | [0~0xffffffff]
} ISP_AE_STAT;

typedef struct _ISP_AF_WIN_INFO_S
{
    ISP_STAT_WIN stStatWin;    // 统计窗口0配置,需注意统计窗口0和1不能有交叠 | [ISP_STAT_WIN]
    ISP_STAT_WIN1 stStatWin1;  // 统计窗口1配置,统计窗口1的水平和垂直个数均不大于4，统计窗的宽高均不能大于0x1ff| [ISP_STAT_WIN1]
} ISP_AF_STAT_CFG;

typedef struct _ISP_AF_STAT_PIXEL_S
{
    FH_UINT32 line_e;    // 偶数行统计结果 | [0~0x3fffffff]
    FH_UINT32 line_o;    // 奇数行统计结果 | [0~0x3fffffff]
    FH_UINT32 column_e;  // 偶数列统计结果 | [0~0x3fffffff]
    FH_UINT32 column_o;  // 奇数列统计结果 | [0~0x3fffffff]
    FH_UINT32 cnt;  // 窗口中大于设定阈值的个数 | [0~0x3ffff]
    FH_UINT32 sum;  // 窗口中大于设定阈值的累加和 | [0~0x3fffffff]
} ISP_AF_STAT_DATA;

typedef struct _ISP_AF_STAT_S
{
    ISP_AF_STAT_DATA stat_win1[16];  // AF窗口1统计信息 | [ISP_AF_STAT_DATA]
    ISP_AF_STAT_DATA stat_win0;      // AF窗口0统计信息 | [ISP_AF_STAT_DATA]
} ISP_AF_STAT;

typedef struct _AWB_BLOCK_STAT_S_
{
    FH_UINT32 u32AwbBlockR;    // AWB R分量sum统计值 | [0~0xffffffff]
    FH_UINT32 u32AwbBlockG;    // AWB G分量sum统计值 | [0~0xffffffff]
    FH_UINT32 u32AwbBlockB;    // AWB B分量sum统计值 | [0~0xffffffff]
    FH_UINT32 u32AwbBlockCnt;  // AWB 统计值cnt值 | [0~0xffffffff]
} AWB_BLOCK_STAT;

typedef struct _ISP_AWB_STAT1_S_
{
    AWB_BLOCK_STAT stBlkStat[9];  // AWB 3*3统计 | [AWB_BLOCK_STAT]
} ISP_AWB_STAT;

typedef struct _ISP_AWB_STAT_CFG_S_
{
    ISP_STAT_WIN stStatWin;       // 统计窗口配置 | [ISP_STAT_WIN]
    FH_UINT16 u16YHighThreshold;  // awb统计上門限值 | [0~0xfff]
    FH_UINT16 u16YLowThreshold;   // awb统计低門限值 | [0~0xfff]
    STAT_WHITE_POINT stPoint[6];  // awb白框点，A，B，C，D，E，F六个点，Ax=Bx By=Cy Dy=Ey Ex=Fx | [STAT_WHITE_POINT]
} ISP_AWB_STAT_CFG;

typedef struct _ISP_AWB_STAT2_S_
{
    AWB_BLOCK_STAT stBlkStat;  // AWB统计,最大支持32*32,位置可选择在长帧上或合成后,具体可看框图 | [AWB_BLOCK_STAT]
} ISP_AWB_ADV_STAT;



typedef struct _ISP_AWB_ADV_STAT_CFG_S_
{
    FH_UINT8 u08StatPosSel;       // 统计位置选择,0:合成前长帧位置,1:合成后,默认linear选1,wdr下选0 | [0~1]
    ISP_STAT_WIN1 stStatWin;      // 统计窗口配置 | [ISP_STAT_WIN1]
    FH_UINT16 u16YHighThreshold;  // awb统计上門限值 | [0~0xfff]
    FH_UINT16 u16YLowThreshold;   // awb统计低門限值 | [0~0xfff]
    STAT_WHITE_POINT stPoint[6];  // awb白框点，A，B，C，D，E，F六个点，Ax=Bx By=Cy Dy=Ey Ex=Fx | [STAT_WHITE_POINT]
} ISP_AWB_ADV_STAT_CFG;

typedef struct _ISP_AWB_FRONT_STAT_S_
{
    AWB_BLOCK_STAT stBlkStat[64];  // AWB 8*8统计,位于短帧上 | [AWB_BLOCK_STAT]
} ISP_AWB_FRONT_STAT;

typedef struct _ISP_HIST_STAT_S_
{
    struct _hist_bin
    {
        FH_UINT32 cnt;  // 每个bin的cnt | [0~0x7fffff]
        FH_UINT64 sum;  // 每个bin的sum | [0~0x3ffffffff]
    } bin[33];          // hist统计值，该统计值包含33个bin
} ISP_HIST_STAT;

typedef struct _ISP_HIST_STAT_CFG_S_
{
    ISP_STAT_WIN stStatWin;        // 统计窗口配置 | [ISP_STAT_WIN]
    FH_UINT16 u16HistStatThr[32];  // hist统计阈值配置 | [0x0~0xfff]
} ISP_HIST_STAT_CFG;
/**|GLOBAL_STAT|**/
typedef struct _GLOBE_STAT_S
{
    struct _Block_gstat
    {
        FH_UINT32 sum;  // 全局统计sum值 | [0~0xffffffff]
        FH_UINT32 cnt;  // 全局统计cnt值 | [0~0xffffffff]
        FH_UINT32 max;  // 统计块内出现的亮度最大值 | [0~0xffffffff]
        FH_UINT32 min;  // 统计块内出现的亮度最小值 | [0~0xffffffff]
    } r, gr, gb, b;
} GLOBE_STAT;

typedef struct _GLOBE_STAT_CFG_S
{
    ISP_STAT_WIN1 stStatWin;  // 统计窗口配置,对于global统计,winHSize和winVSize需小于512,窗口个数较小时需注意 | [ISP_STAT_WIN1]
    FH_UINT16 u16ChnThH;      // 统计像素上阈值,默认0xfff | [0x0~0xfff]
    FH_UINT16 u16ChnThL;      // 统计像素下阈值,默认0 | [0x0~0xfff]
} GLOBE_STAT_CFG;

typedef struct _DEHAZE_STAT_S
{
    FH_UINT32 u32DehazeRGB[2048];  // Dehaze 32*64分区窗共2048个RGB三个通道大气光统计值：B(bit20~29)|G(bit10~19)|R(bit0~9) | [0~0x3fffffff]
    FH_UINT16 u16DehazeIdx;        // 统计最小值中极大值所在窗Index | [0~0x7ff]
} DEHAZE_STAT;

/**|FAST_BOOT|**/
/******************************************************************/
/******************isp init cfg structure**************************/
/******************************************************************/
/******************************************************************/
typedef struct _BLC_INIT_CFG_S
{
    FH_UINT16 blc_level; //黑电平值  | [0~0xffff]
} BLC_INIT_CFG;

typedef struct _WB_INIT_CFG_S
{
    FH_UINT16 wbGain[3];  // 白平衡三通道增益值rgain, ggain, bgain; | [0~0x1fff]
} WB_INIT_CFG;

typedef struct _CCM_INIT_CFG_S
{
    FH_UINT8  ccmIdx;     // 选择使用ccm的序号 | [0~1]
    FH_SINT16 ccmCfg[9];  // 颜色矫正矩阵 | [-4096~4095]
} CCM_INIT_CFG;

typedef struct _DPC_INIT_CFG_S
{
    FH_UINT8 ctrlMode;  // 去坏点模式 | [0~3]
    FH_UINT8 str;  // 去坏点比例門限值 | [0~7]
} DPC_INIT_CFG;

typedef struct _APC_INIT_CFG_S
{
    FH_UINT8 edgeStr;  // 边界锐化增益，对应drv apc_edge_weight, 低4bits无效 U8| [0x0~0xff]
    FH_UINT8 detailStr;  // 细节增强增益, 对应drv apc_detail_weight, 低4bits无效 U8| [0x0~0xff]
    FH_UINT8 positiveStr;  // 总体正向增益, U8 | [0~0xff]
    FH_UINT8 negativeStr;  // 总体负向增益, U8 | [0~0xff]
} APC_INIT_CFG;

typedef struct _YNR_INIT_CFG_S
{
    FH_UINT8 th_str[3];  // th_str[0] 高频亮度阈值, th_str[1] 中频亮度阈值, th_str[2] 低频亮度阈值，U4.4 | [0~0xff]
} YNR_INIT_CFG;

typedef struct _CTR_INIT_CFG_S
{
    FH_UINT16 ctr;  // 对比度增强因子,U2.6 | [0~255]
} CTR_INIT_CFG;

typedef struct _SAT_INIT_CFG_S
{
    FH_UINT16 sat;  // 饱和度调整因子,U3.5 | [0~0xff]
    FH_UINT16 blue_sup;  // 饱和度蓝色分量,U2.6 | [0~200]
    FH_UINT16 red_sup;  // 饱和度红色分量,U2.6 | [0~200]
} SAT_INIT_CFG;

typedef struct _GAMMA_MODE_INIT_CFG_S
{
    FH_UINT16 gamma_mode;  // 当前gamma运行模式 | [0~3]
} GAMMA_MODE_INIT_CFG;

typedef struct _GAMMA_INIT_CFG_S
{
    FH_UINT32 gamma[80];  // gamma表对应的值 | [0~0xffffffff]
} GAMMA_INIT_CFG;

typedef struct _LTM_INIT_CFG_S
{
    FH_UINT32 ltm[128]; // ltm表对应值| [0~0xffffffff]
} LTM_INIT_CFG;

typedef struct _ISP_GAIN_INIT_CFG_S
{
    FH_UINT32 u32IspGain; // isp增益值 [0~0xffffffff]
} ISP_GAIN_INIT_CFG;
/******************************************************************/
/******************end of isp init cfg structure*******************/
/******************************************************************/
/******************************************************************/

/******************isp sensor common_if interface******************/
typedef struct _MAP_INTT_GAIN_CFG_S
{
    FH_SINT32 currFormat;  //当前的sensor format | [0~0xffffffff]
    FH_SINT32 desFormat;   //目标的sensor format | [0~0xffffffff]
    FH_UINT32 currIntt;    //当前的曝光时间，单位为行 | [0~0xffffffff]
    FH_UINT32 currTotalGain; //当前的曝光增益，u.6精度 | [0~0xffffffff]
    FH_UINT32 desIntt;     //计算返回的曝光时间，单位为行 | [0~0xffffffff]
    FH_UINT32 desTotalGain; //计算返回的曝光增益，u.6精度 | [0~0xffffffff]
} MAP_INTT_GAIN_CFG;

typedef struct _GPIO_PARAM_CFG_S
{
    FH_BOOL gpio_enable;  //第二阶段是否需要拉高拉低GPIO | [0-0x1]
    FH_UINT32 gpio_time;  //第二阶段拉高拉低需要配置的延时　| [0-0xffffffff]
} GPIO_PARAM_CFG;

typedef struct _BLC_PARAM_CFG_S
{
    FH_UINT32 blc_value;  //配置的第一阶段blc值 | [0~0xffff]
} BLC_PARAM_CFG;

typedef union
{
    BLC_PARAM_CFG blc_param_cfg;
    GPIO_PARAM_CFG gpio_param_cfg;
    MAP_INTT_GAIN_CFG mapInttGainCfg;
    unsigned int dw[128];
} ISP_SENSOR_COMMON_CMD_DATA0;

typedef union
{
    unsigned int dw[128];
} ISP_SENSOR_COMMON_CMD_DATA1;
/*******************************************************************/

/**|RUBBISH|**/
typedef enum _SNS_CLK_S_ {
    SNS_CLK_24_POINT_0   = 0x1,
    SNS_CLK_27_POINT_0   = 0x2,
    SNS_CLK_37_POINT_125 = 0x3,
    SNS_CLK_DUMMY =0xffffffff,
} SNS_CLK;

typedef enum _SNS_DATA_BIT_S_ {
    LINER_DATA_8_BITS  = 0x1,
    LINER_DATA_12_BITS = 0x2,
    LINER_DATA_14_BITS = 0x3,
    WDR_DATA_16_BITS   = 0x4,
    SNS_DATA_BITS_DUMMY =0xffffffff,
} SNS_DATA_BITS;

typedef enum _SIGNAL_POLARITY_S_ {
    ACTIVE_HIGH = 0x0,
    ACTIVE_LOW = 0x1,
    SIGNAL_POLARITY_DUMMY =0xffffffff,
} SIGNAL_POLARITY;

typedef struct _ISP_VI_HW_ATTR_S_
{
    SNS_CLK         eSnsClock;         // 配置的cis时钟 | [SNS_CLK]
    SNS_DATA_BITS   eSnsDataBits;      // 配置的sensor数据位宽 | [SNS_DATA_BITS]
    SIGNAL_POLARITY eHorizontalSignal; // 时钟水平极性 | [0~1]
    SIGNAL_POLARITY eVerticalSignal;   // 时钟垂直极性 | [0~1]
    FH_BOOL         u08Mode16;         //  | [ ]
    FH_UINT32       u32DataMaskHigh;   //  | [ ]
    FH_UINT32       u32DataMaskLow;    //  | [ ]
} ISP_VI_HW_ATTR;

typedef struct _ISP_ALGORITHM_S_
{
    FH_UINT8 u08Name[16];    //  | [ ]
    FH_UINT8 u08AlgorithmId; //  | [ ]
    FH_VOID (*run)(FH_VOID); //  | [ ]
} ISP_ALGORITHM;

typedef struct _STATIC_DPC_CFG_S_
{
    FH_BOOL   bStaticDccEn;
    FH_BOOL   bStaticDpcEn;
    FH_UINT32 u32DpcTable[1024];
    FH_UINT16 u16DpcCol[32];
} STATIC_DPC_CFG;

typedef struct _ISP_DEBUG_INFO_S_
{
    FH_UINT32 envLuma;
    FH_UINT32 sqrtenvLuma;
    FH_UINT32 sensor_gain;
    FH_UINT32 isp_gain;
} ISP_DEBUG_INFO;

typedef struct _ISP_DEFAULT_PARAM_
{
    ISP_BLC_ATTR       stBlcCfg;     //　 | [ ]
    ISP_LTM_CFG        stLtmCfg;     //  | [ ]
    ISP_GAMMA_CFG      stGamma;      //  | [ ]
    ISP_SAT_CFG        stSaturation; //  | [ ]
    ISP_APC_CFG        stApc;        //  | [ ]
    ISP_CONTRAST_CFG   stContrast;   //  | [ ]
    ISP_BRIGHTNESS_CFG stBrt;        //  | [ ]
    ISP_NR3D_CFG       stNr3d;       //  | [ ]
    ISP_NR2D_CFG       stNr2d;       //  | [ ]
    ISP_YNR_CFG        stYnr;        //  | [ ]
    ISP_CNR_CFG        stCnr;        //  | [ ]
    DYNAMIC_DPC_CFG    stDpc;        //  | [ ]
    ISP_LSC_CFG        stLscCfg;     //  | [ ]
} ISP_DEFAULT_PARAM;

#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*_ISP_COMMON_H_*/
