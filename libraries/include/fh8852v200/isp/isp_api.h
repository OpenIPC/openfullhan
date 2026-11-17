#ifndef _ISP_API_H_
#define _ISP_API_H_


#include "isp_common.h"
#include "isp_sensor_if.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define lift_shift_bit_num(bit_num)			(1<<bit_num)
// #define DEBUG_API 1

#define CHECK_VALIDATION(x, a, b)                                                                                                  \
    do                                                                                                                             \
    {                                                                                                                              \
        int r;                                                                                                                     \
        if ((x < a) || (x > b))                                                                                                    \
        {                                                                                                                          \
            if (x < a)                                                                                                             \
                r = a;                                                                                                             \
            else                                                                                                                   \
                r = b;                                                                                                             \
            fh_printf("[WARNING]parameter out of range @%s %s= %d | range=[%d,%d] | auto clip to %d\n", __func__, #x, x, a, b, r); \
            x = r;                                                                                                                 \
        }                                                                                                                          \
    } while (0)

#define TRACE_API ispTrace_FunctionName(__func__)

#define FUNC_DEP __attribute__((deprecated))

enum ISP_HW_MODULE_LIST
{
    HW_MODUL_WBS           = lift_shift_bit_num(0),
    HW_MODUL_WBL           = lift_shift_bit_num(1),
    HW_MODUL_WDR           = lift_shift_bit_num(2),
    HW_MODUL_HMIRROR       = lift_shift_bit_num(3),
    HW_MODUL_LSC           = lift_shift_bit_num(4),

    HW_MODUL_DPC           = lift_shift_bit_num(5),
    HW_MODUL_GB            = lift_shift_bit_num(6),
    HW_MODUL_STAT_AF       = lift_shift_bit_num(7),
    HW_MODUL_GAIN          = lift_shift_bit_num(8),

    HW_MODUL_POST_GAIN     = lift_shift_bit_num(9),
    HW_MODUL_STAT_HIST     = lift_shift_bit_num(10),
    HW_MODUL_GLOBE_STAT    = lift_shift_bit_num(11),
    HW_MODUL_WB            = lift_shift_bit_num(12),
    HW_MODUL_FCCFA         = lift_shift_bit_num(13),
    HW_MODUL_HLR           = lift_shift_bit_num(14),
    HW_MODUL_RGBB          = lift_shift_bit_num(15),
    HW_MODUL_LTM           = lift_shift_bit_num(16),
    HW_MODUL_RGBB2         = lift_shift_bit_num(17),
    HW_MODUL_CGAMMA        = lift_shift_bit_num(18),
    HW_MODUL_YGAMMA        = lift_shift_bit_num(19),
    HW_MODUL_YNR           = lift_shift_bit_num(20),
    HW_MODUL_CNR           = lift_shift_bit_num(21),
    HW_MODUL_APC           = lift_shift_bit_num(22),
    HW_MODUL_PURPLE        = lift_shift_bit_num(23),
    HW_MODUL_CHROMA        = lift_shift_bit_num(24),
    HW_MODUL_LOCAL_CHROMA  = lift_shift_bit_num(25),
    HW_MODUL_YIE           = lift_shift_bit_num(26),
    HW_MODUL_CIE           = lift_shift_bit_num(27),
    HW_MODUL_DEHAZE        = lift_shift_bit_num(28),

    HW_MODUL_NR3D          = lift_shift_bit_num(29),
    HW_MODUL_LCE           = lift_shift_bit_num(30),
    HW_MODUL_NR2D          = lift_shift_bit_num(31),
    ISP_HW_MODULE_LIST_DUMMY=0xffffffff,
};

/**SYSTEM_CONTROL*/

/*
*   Name: API_ISP_GetBuffSize
*            获取ISP中分配的buffer大小
*
*   Parameters:
*
*       [IN] FH_UINT32 width
*            输入的幅面宽度
*
*       [IN]  FH_UINT32 height
*            输入的幅面高度
*
*   Return:
*            ISP中分配的buffer大小
*   Note:
*       只用于统计内存时调用,isp正常运行程序不能调用,否则会出异常
*/
FH_SINT32 API_ISP_GetBuffSize(FH_UINT32 width, FH_UINT32 height);
/*
*   Name: API_ISP_MemInit
*            ISP内部使用的memory分配与初始化
*
*   Parameters:
*
*       [IN]  FH_UINT32 width
*            ISP处理的幅面宽度
*
*       [IN]  FH_UINT32 height
*            ISP处理的幅面高度
*
*   Return:
*            0(正确)
*           -1(ISP设备驱动打开失败)
*   Note:
*       无
*/
FH_SINT32 API_ISP_MemInit( FH_UINT32 width, FH_UINT32 height );
/*
*   Name: API_ISP_GetBinAddr
*            获取ISP的param参数的地址和大小
*
*   Parameters:
*
*       [OUT] FH_UINT32 *u32BinAddr
*            param的地址
*
*       [OUT] FH_UINT32 *u32BinSize
*            param的size
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetBinAddr(FH_UINT32 *u32BinAddr,FH_UINT32 *u32BinSize);
/*
*   Name: API_ISP_SetViHwAttr
*            弃用
*
*   Parameters:
*
*       [IN] const ISP_VI_HW_ATTR *pstViHwAttr
*            输入vi相关的一些配置信息
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_SetViHwAttr(const ISP_VI_HW_ATTR *pstViHwAttr);
/*
*   Name: API_ISP_SetCisClk
*            配置供给sensor的时钟
*
*   Parameters:
*
*       [IN] FH_UINT32 cisClk
*            需要配置时钟频率值
*
*   Return:
*            正确则返回0,错误则返回ERROR_ISP_SET_CIS_CLK
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCisClk(FH_UINT32 cisClk);
/*
*   Name: API_ISP_CisClkEn
*            供给sensor的时钟使能配置
*
*   Parameters:
*
*       [IN] FH_BOOL bEn
*            1表示使能时钟，0表示关闭时钟。
*
*   Return:
*            0(正确)，错误(ERROR_ISP_SET_CIS_CLK)
*   Note:
*       无
*/
FH_SINT32 API_ISP_CisClkEn(FH_BOOL bEn);
/*
*   Name: API_ISP_SetViAttr
*            配置vi相关的一些幅面信息
*
*   Parameters:
*
*       [IN] const ISP_VI_ATTR_S *pstViAttr
*            结构体ISP_VI_ATTR_S的指针
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetViAttr(const ISP_VI_ATTR_S *pstViAttr);
/*
*   Name: API_ISP_GetViAttr
*            获取当前幅面相关信息
*
*   Parameters:
*
*       [OUT] ISP_VI_ATTR_S *pstViAttr
*            结构体ISP_VI_ATTR_S的指针
*
*   Return:
*            0(正确)，
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetViAttr(ISP_VI_ATTR_S *pstViAttr);
/*
*   Name: API_ISP_GetIspMode
*            弃用
*
*   Parameters:
*
*       [OUT] FH_UINT32 *mode
*            ISP当前运行模式(直通/非直通)
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_GetIspMode(FH_UINT32 *mode);
/*
*   Name: API_ISP_Init
*            初始化ISP硬件寄存器，并启动ISP
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确)
*        -1003(ISP初始化异常)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Init(FH_VOID);

FH_SINT32 FUNC_DEP API_ISP_SetIspParam(ISP_DEFAULT_PARAM *pstDefaultParam);
/*
*   Name: API_ISP_LoadIspParam
*            加载指定参数到DRV寄存器
*
*   Parameters:
*
*       [IN] char *isp_param_buff
*            指定参数的指针
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_LoadIspParam(char *isp_param_buff);
/*
*   Name: API_ISP_CLEAN_CIRCLUAR_BUFF
*            清空循环缓冲
*
*   Parameters:
*
*            None
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_CLEAN_CIRCLUAR_BUFF(FH_VOID);
/*
*   Name: API_ISP_Pause
*            暂停ISP对图像的处理与输出
*
*   Parameters:
*
*            None
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Pause(FH_VOID);
/*
*   Name: API_ISP_SoftReset
*            ISP软复位
*
*   Parameters:
*
*            None
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SoftReset(FH_VOID);
FH_SINT32 FUNC_DEP API_ISP_KickStart(FH_VOID);
/*
*   Name: API_ISP_Resume
*            恢复ISP对图像处理与输出
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Resume(FH_VOID);
/*
*   Name: API_ISP_DetectPicSize
*            检测幅面信息是否符合预期
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确)，错误(ERROR_ISP_DETECT_NO_INPUT, ERROR_ISP_UNEXPECTED_PIC_SIZE)
*   Note:
*       无
*/
FH_SINT32 API_ISP_DetectPicSize(FH_VOID);
/*
*   Name: API_ISP_Run
*            ISP策略处理
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确)，
*           -1(图像丢失)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Run(FH_VOID);
/*
*   Name: API_ISP_AE_AWB_Run
*            ISP AE&AWB策略处理
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确)
*            图像丢失(ERROR_ISP_WAIT_PICEND_FAILED)
*   Note:
*       无
*/
FH_SINT32 API_ISP_AE_AWB_Run(FH_VOID);
/*
*   Name: API_ISP_Exit
*            ISP线程退出，清理状态
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Exit(FH_VOID);
/*
*   Name: API_ISP_SensorRegCb
*            拷贝sensor的回调函数到目标地址。
*
*   Parameters:
*
*       [IN] FH_UINT32 u32SensorId
*            无用
*
*       [IN]  struct isp_sensor_if* pstSensorFunc
*            类型为isp_sensor_if的结构体指针，详细成员变量请查看isp_sensor_if结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorRegCb(FH_UINT32 u32SensorId, struct isp_sensor_if* pstSensorFunc);
/*
*   Name: API_ISP_SensorUnRegCb
*            注销ISP中注册的sensor的回调函数。
*
*   Parameters:
*
*       [IN] FH_UINT32 u32SensorId
*            无用
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorUnRegCb(FH_UINT32 u32SensorId);
/*
*   Name: API_ISP_Set_HWmodule_cfg
*            配置ISP模块硬件使能
*
*   Parameters:
*
*       [IN] const FH_UINT32 u32modulecfg
*            每1bit对应一个硬件使能位0表示关闭，1表示打开，详见枚举ISP_HW_MODULE_LIST。
*
*   Return:
*            0(正确)
*   Note:
*       当需要一次开关多个模块时,使用此函数,若只需控制一个模块,则可使用API_ISP_Set_Determined_HWmodule函数实现
*/
FH_SINT32 API_ISP_Set_HWmodule_cfg(const FH_UINT32 u32modulecfg);
/*
*   Name: API_ISP_Get_HWmodule_cfg
*            获取当前ISP模块硬件状态
*
*   Parameters:
*
*       [OUT] FH_UINT32 *u32modulecfg
*            每1bit对应一个硬件使能位0表示关闭，1表示打开，详见枚举ISP_HW_MODULE_LIST。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Get_HWmodule_cfg(FH_UINT32 *u32modulecfg);
/*
*   Name: API_ISP_Set_Determined_HWmodule
*            配置ISP某个模块硬件使能
*
*   Parameters:
*
*       [IN] const HW_MODULE_CFG *pstModuleCfg
*            传入要控制的某个模块枚举变量以及开关状态，详见HW_MODULE_CFG。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       一次只能传入一个模块,否则会出错
*/
FH_SINT32 API_ISP_Set_Determined_HWmodule(const HW_MODULE_CFG *pstModuleCfg);
/*
*   Name: API_ISP_Get_Determined_HWmodule
*           获取ISP某个模块硬件使能状态
*
*   Parameters:
*
*       [INOUT] HW_MODULE_CFG *pstModuleCfg
*            传入要控制的某个模块枚举变量,获取该模块开关状态，详见HW_MODULE_CFG。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       一次只能传入一个模块,否则会出错
*/
FH_SINT32 API_ISP_Get_Determined_HWmodule(HW_MODULE_CFG *pstModuleCfg);
/*
*   Name: API_ISP_GetAlgCtrl
*            获取软件控制开关寄存器状态
*
*   Parameters:
*
*       [OUT] FH_UINT32 *u32AlgCtrl
*            每1bit对应一个软件使能位0表示关闭，1表示打开
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAlgCtrl(FH_UINT32 *u32AlgCtrl);
/*
*   Name: API_ISP_SetAlgCtrl
*            设置软件控制开关寄存器状态
*
*   Parameters:
*
*       [IN] FH_UINT32 u32AlgCtrl
*            每1bit对应一个软件使能位0表示关闭，1表示打开
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAlgCtrl(FH_UINT32 u32AlgCtrl);
/*
*   Name: API_ISP_WaitVD
*            获取ispf中断
*
*   Parameters:
*
*       [IN] VOID
*
*   Return:
*            任意值(获取到中断信号时间)
*            0(没有获取到中断信号))
*   Note:
*       无
*/
FH_SINT32 API_ISP_WaitVD(FH_VOID);
FH_SINT32 FUNC_DEP API_ISP_GetVersion(ISP_VERSION *pstIspVersion);
FH_SINT32 FUNC_DEP API_ISP_SetIspReg(FH_UINT32 u32RegAddr,FH_UINT32 u32RegData);
FH_SINT32 FUNC_DEP API_ISP_GetIspReg(FH_UINT32 u32RegAddr,FH_UINT32 *u32RegData);
/*
*   Name: API_ISP_GetRawSize
*            获取raw数据的大小, 供应用层分配空间
*
*   Parameters:
*       [OUT]  FH_UINT32* raw_size
*            raw数据大小,单位byte
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       与API_ISP_GetRaw配合使用
*/
FH_SINT32 API_ISP_GetRawSize(FH_UINT32 *raw_size);
/*
*   Name: API_ISP_GetRaw
*            获取ISP　NR3D处的raw数据
*
*   Parameters:
*
*       [IN] FH_BOOL strategy_en
*            关闭硬件影响图像效果模块(0)，打开硬件影响图像效果模块(1)
*
*       [OUT]  FH_VOID* pRawBuff
*            存放raw数据的地址
*
*       [IN]  FH_UINT32 u32Size
*            存放raw数据buffer大小
*
*       [IN]  FH_UINT32 u32FrameCnt
*            需要导出的帧数，导出帧数不连续
*
*       [IN]  FRAME_TYPE type
*            帧类型
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetRaw(FH_BOOL strategy_en, FH_VOID* pRawBuff, FH_UINT32 u32Size, FH_UINT32 u32FrameCnt, FRAME_TYPE type);
/*
*   Name: API_ISP_SetRawBuf
*            连续导出多帧raw功能, 配置相关信息
*
*   Parameters:
*
*       [IN] FH_BOOL strategy_en
*            关闭硬件影响图像效果模块(0)，打开硬件影响图像效果模块(1)
*
*       [IN]  ISP_RAW_BUF *raw_buf
*            类型为ISP_RAW_BUF的结构体指针，详细成员变量请查看ISP_RAW_BUF结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       应用层需申请足够的vmm内存
*/
FH_SINT32 API_ISP_SetRawBuf(FH_BOOL strategy_en, ISP_RAW_BUF *raw_buf);
FH_SINT32 FUNC_DEP API_ISP_CheckStatReady(FH_BOOL *isReady);
/*
*   Name: API_ISP_SetViGenCfg
*            使用VI GEN灌输据方式出图
*
*   Parameters:
*
*       [IN] ISP_VIGEN_CFG *vi_gen
*            类型为ISP_VIGEN_CFG的结构体指针，详细成员变量请查看ISP_VIGEN_CFG结构体定义。
*
*   Return:
*            0(正确)
*        -3002(空指针异常)
*   Note:
*      无
*/
FH_SINT32 API_ISP_SetViGenCfg(ISP_VIGEN_CFG *vi_gen);
/**SENSOR_CONTROL*/

/*
*   Name: API_ISP_SensorInit
*            sensor预初始化，并未配置sensor寄存器
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorInit(FH_VOID);
/*
*   Name: API_ISP_SetSensorFmt
*            初始化sensor
*
*   Parameters:
*
*       [IN] FH_UINT32 format
*            传入的时枚举FORMAT中的枚举值，选择幅面
*
*   Return:
*            0(正确)
*        -3002(sensor初始化异常)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorFmt(FH_UINT32 format);

/*
*   Name: API_ISP_SensorKick
*            启动sensor输出，有的sensor需要用到
*
*   Parameters:
*
*            None
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorKick(FH_VOID);
/*
*   Name: API_ISP_SetSensorIntt
*            配置sensor的曝光值
*
*   Parameters:
*
*       [IN] FH_UINT32 intt
*            传入的曝光值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)。
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorIntt(FH_UINT32 intt);
/*
*   Name: API_ISP_SetSensorGain
*            配置sensor增益值
*
*   Parameters:
*
*       [IN] FH_UINT32 gain
*            增益值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorGain(FH_UINT32 gain);
/*
*   Name: API_ISP_MapInttGain
*            不同幅面切换时根据当前幅面曝光值和增益值转换成目标幅面曝光值和增益值
*
*   Parameters:
*
*       [IN] ISP_SENSOR_COMMON_CMD_DATA0 *pstMapInttGainCfg
*            类型为ISP_SENSOR_COMMON_CMD_DATA0的结构体指针，详细成员变量请查看ISP_SENSOR_COMMON_CMD_DATA0结构体定义。
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_MapInttGain(ISP_SENSOR_COMMON_CMD_DATA0 *pstMapInttGainCfg);
/*
*   Name: API_ISP_SetSensorReg
*            配置sensor寄存器
*
*   Parameters:
*
*       [IN] FH_UINT16 addr
*            sensor寄存器地址
*
*       [IN] FH_UINT16 data
*            配置的值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorReg(FH_UINT16 addr,FH_UINT16 data);
/*
*   Name: API_ISP_GetSensorReg
*            读取sensor寄存器
*
*   Parameters:
*
*       [IN] FH_UINT16 addr
*            sensor寄存器地址
*
*       [OUT]  FH_UINT16 *data
*            读取的值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetSensorReg(FH_UINT16 addr, FH_UINT16 *data);

/** AE **/
/*
*   Name: API_ISP_SetAeDefaultCfg
*            设置ae相关参数
*
*   Parameters:
*
*       [IN] AE_DEFAULT_CFG *pstAeDefaultCfg
*            类型为AE_DEFAULT_CFG的结构体指针，详细成员变量请查看AE_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAeDefaultCfg(AE_DEFAULT_CFG *pstAeDefaultCfg);
/*
*   Name: API_ISP_GetAeDefaultCfg
*            获取ae相关参数
*
*   Parameters:
*
*       [OUT] AE_DEFAULT_CFG *pstAeDefaultCfg
*            类型为AE_DEFAULT_CFG的结构体指针，详细成员变量请查看AE_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeDefaultCfg(AE_DEFAULT_CFG *pstAeDefaultCfg);
/*
*   Name: API_ISP_SetAeRouteCfg
*            设置ae路线模式相关参数
*
*   Parameters:
*
*       [IN] AE_ROUTE_CFG *pstAeRouteCfg
*            类型为AE_ROUTE_CFG的结构体指针，详细成员变量请查看AE_ROUTE_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAeRouteCfg(AE_ROUTE_CFG *pstAeRouteCfg);
/*
*   Name: API_ISP_GetAeRouteCfg
*            获取ae路线模式相关参数
*
*   Parameters:
*
*       [OUT] AE_ROUTE_CFG *pstAeRouteCfg
*            类型为AE_ROUTE_CFG的结构体指针，详细成员变量请查看AE_ROUTE_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeRouteCfg(AE_ROUTE_CFG *pstAeRouteCfg);
/*
*   Name: API_ISP_SetAeInfo
*            设置ae曝光时间及增益参数至sensor及硬件寄存器
*
*   Parameters:
*
*       [IN] const ISP_AE_INFO *pstAeInfo
*            类型为ISP_AE_INFO的结构体指针，详细成员变量请查看ISP_AE_INFO结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAeInfo(const ISP_AE_INFO *pstAeInfo);
/*
*   Name: API_ISP_GetAeInfo
*           从sensor及硬件寄存器获取ae曝光时间及增益参数
*
*   Parameters:
*
*       [OUT] ISP_AE_INFO *pstAeInfo
*            类型为ISP_AE_INFO的结构体指针，详细成员变量请查看ISP_AE_INFO结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeInfo(ISP_AE_INFO *pstAeInfo);
/*
*   Name: API_ISP_SetAeInfo2
*            设置ae曝光时间及增益参数至sensor及硬件寄存器
*
*   Parameters:
*
*       [IN] const ISP_AE_INFO_2 *pstAeInfo2
*            类型为ISP_AE_INFO_2的结构体指针，详细成员变量请查看ISP_AE_INFO_2结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       与API_ISP_SetAeInfo的区别在于isp gain分为pre和post两部分配置
*/
FH_SINT32 API_ISP_SetAeInfo2(const ISP_AE_INFO_2 *pstAeInfo2);
/*
*   Name: API_ISP_GetAeInfo2
*           从sensor及硬件寄存器获取ae曝光时间及增益参数
*
*   Parameters:
*
*       [OUT] ISP_AE_INFO_2 *pstAeInfo2
*            类型为ISP_AE_INFO_2的结构体指针，详细成员变量请查看ISP_AE_INFO_2结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       与API_ISPGetAeInfo的区别在于isp gain分为pre和post两部分获取
*/
FH_SINT32 API_ISP_GetAeInfo2(ISP_AE_INFO_2 *pstAeInfo2);
/*
*   Name: API_ISP_GetAeStatus
*            获取ae状态值
*
*   Parameters:
*
*       [OUT] ISP_AE_STATUS *pstAeStatus
*            类型为ISP_AE_STATUS的结构体指针，详细成员变量请查看ISP_AE_STATUS结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeStatus(ISP_AE_STATUS *pstAeStatus);
/*
*   Name: API_ISP_SetAeUserStatus
*            设置ae用户状态值
*
*   Parameters:
*
*       [IN] AE_USER_STATUS *pstAeUserStatus
*            类型为AE_USER_STATUS的结构体指针，详细成员变量请查看AE_USER_STATUS结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       若用户使用自定义ae策略,则需要调用该函数配置ae相关状态值,提供给isp的其他策略使用,否则其他策略可能运行会有异常
*/
FH_SINT32 API_ISP_SetAeUserStatus(AE_USER_STATUS *pstAeUserStatus);

/** AWB **/
/*
*   Name: API_ISP_SetAwbDefaultCfg
*            设置awb相关参数
*
*   Parameters:
*
*       [IN] AWB_DEFAULT_CFG *pstAwbDefaultCfg
*            类型为AWB_DEFAULT_CFG的结构体指针，详细成员变量请查看AWB_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAwbDefaultCfg(AWB_DEFAULT_CFG *pstAwbDefaultCfg);
/*
*   Name: API_ISP_GetAwbDefaultCfg
*            获取awb相关参数
*
*   Parameters:
*
*       [OUT] AWB_DEFAULT_CFG *pstAwbDefaultCfg
*            类型为AWB_DEFAULT_CFG的结构体指针，详细成员变量请查看AWB_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbDefaultCfg(AWB_DEFAULT_CFG *pstAwbDefaultCfg);
/*
*   Name: API_ISP_GetAwbStatus
*            获取awb状态值
*
*   Parameters:
*
*       [OUT] ISP_AWB_STATUS *pstAwbStatus
*            类型为ISP_AWB_STATUS的结构体指针，详细成员变量请查看ISP_AWB_STATUS结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbStatus(ISP_AWB_STATUS *pstAwbStatus);
/*
*   Name: API_ISP_SetAwbGain
*            设置awb增益至硬件寄存器
*
*   Parameters:
*
*       [IN] ISP_AWB_GAIN *pstAwbGain
*            类型为ISP_AWB_GAIN的结构体指针，详细成员变量请查看ISP_AWB_GAIN结构体定义。
*
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAwbGain(const ISP_AWB_GAIN *pstAwbGain);
/*
*   Name: API_ISP_GetAwbGain
*            从硬件寄存器获取awb增益值
*
*   Parameters:
*
*       [OUT] const ISP_AWB_GAIN *pstAwbGain
*            类型为ISP_AWB_GAIN的结构体指针，详细成员变量请查看ISP_AWB_GAIN结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)

*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbGain(ISP_AWB_GAIN *pstAwbGain);

/**  AF*/
FH_SINT32 FUNC_DEP API_ISP_AFlibRegCb(FH_VOID);
FH_SINT32 FUNC_DEP API_ISP_AFlibUnRegCb(FH_VOID);

/*
*   Name: API_ISP_AFAlgEn
*            设置获取af开关。
*
*   Parameters:
*
*       [IN] FH_BOOL bEn
*          使能(bEn=1)，关闭(bEn=0)
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_AFAlgEn(FH_BOOL bEn);

FH_SINT32 FUNC_DEP API_ISP_AFSendCmd(FH_UINT32 u32Dev,FH_UINT32 u32Cmd,FH_VOID *param);
/*
*   Name: API_ISP_SetAFFilter
*            设置滤波器参数。
*
*   Parameters:
*
*       [IN] ISP_AF_FILTER *pstAfFilter
*            类型为ISP_AF_FILTER的结构体指针，详细成员变量请查看ISP_AF_FILTER结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAFFilter(ISP_AF_FILTER *pstAfFilter);
/*
*   Name: API_ISP_GetAFFilter
*            获取滤波器参数。
*
*   Parameters:
*
*       [OUT] ISP_AF_FILTER *pstAfFilter
*            类型为ISP_AF_FILTER的结构体指针，详细成员变量请查看ISP_AF_FILTER结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAFFilter(ISP_AF_FILTER *pstAfFilter);
FH_SINT32 FUNC_DEP API_ISP_SetAFStatAddr(const ISP_AF_STAT_ADDR *pstAfStatAddr);
FH_SINT32 FUNC_DEP API_ISP_GetAFStatAddr(ISP_AF_STAT_ADDR *pstAfStatAddr);

/**LTM*/
/*
*   Name: API_ISP_SetLtmCfg
*            配置LTM的DRV寄存器值
*
*   Parameters:
*
*       [IN] ISP_LTM_CFG *pstLtmCfg
*            类型为ISP_LTM_CFG的结构体指针，详细成员变量请查看ISP_LTM_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLtmCfg(ISP_LTM_CFG *pstLtmCfg);
/*
*   Name: API_ISP_GetLtmCfg
*            获取当前DRV中的LTM配置
*
*   Parameters:
*
*       [OUT] ISP_LTM_CFG *pstLtmCfg
*            类型为ISP_LTM_CFG的结构体指针，详细成员变量请查看ISP_LTM_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetLtmCfg(ISP_LTM_CFG *pstLtmCfg);
/**BLC*/
/*
*   Name: API_ISP_SetBlcAttr
*            配置BLC的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_BLC_ATTR * pstBlcAttr
*            类型为ISP_BLC_ATTR的结构体指针，详细成员变量请查看ISP_BLC_ATTR结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetBlcAttr(ISP_BLC_ATTR * pstBlcAttr);
/*
*   Name: API_ISP_GetBlcAttr
*            获取当前配置的BLC的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_BLC_ATTR * pstBlcAttr
*            类型为ISP_BLC_ATTR的结构体指针，详细成员变量请查看ISP_BLC_ATTR结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetBlcAttr(ISP_BLC_ATTR * pstBlcAttr);

/** GB*/
/*
*   Name: API_ISP_SetGbCfg
*            配置GB的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_GB_CFG *pstGbCfg
*            类型为ISP_GB_CFG的结构体指针，详细成员变量请查看ISP_GB_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGbCfg(ISP_GB_CFG *pstGbCfg);
/*
*   Name: API_ISP_GetGbCfg
*            获取当前配置的GB的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_GB_CFG *pstGbCfg
*            类型为ISP_GB_CFG的结构体指针，详细成员变量请查看ISP_GB_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGbCfg(ISP_GB_CFG *pstGbCfg);
/** DPC*/

FH_SINT32 FUNC_DEP API_ISP_SetStaticDpc(STATIC_DPC_CFG *pstStaticDpc);
FH_SINT32 FUNC_DEP API_ISP_GetStaticDpc(STATIC_DPC_CFG *pstStaticDpc);
/*
*   Name: API_ISP_SetDynamicDpc
*            配置动态DPC的DRV寄存器
*
*   Parameters:
*
*       [IN] DYNAMIC_DPC_CFG *pstDynamicDpc
*            类型为DYNAMIC_DPC_CFG的结构体指针，详细成员变量请查看DYNAMIC_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDynamicDpc(DYNAMIC_DPC_CFG *pstDynamicDpc);
/*
*   Name: API_ISP_GetDynamicDpc
*            获取当前配置的动态DPC的DRV寄存器值
*
*   Parameters:
*
*       [OUT] DYNAMIC_DPC_CFG *pstDynamicDpc
*            类型为DYNAMIC_DPC_CFG的结构体指针，详细成员变量请查看DYNAMIC_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDynamicDpc(DYNAMIC_DPC_CFG *pstDynamicDpc);
/** LSC*/
/*
*   Name: API_ISP_SetLscCfg
*            配置lsc参数
*
*   Parameters:
*
*       [IN] ISP_LSC_CFG *pstLscCfg
*            类型为ISP_LSC_CFG的结构体指针，详细成员变量请查看ISP_LSC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLscCfg(ISP_LSC_CFG *pstLscCfg);
/** NR3D*/
/*
*   Name: API_ISP_SetNr3dCfg
*            配置NR3D的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_NR3D_CFG *pstNr3dCfg
*            类型为ISP_NR3D_CFG的结构体指针，详细成员变量请查看ISP_NR3D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetNr3dCfg(ISP_NR3D_CFG *pstNr3dCfg);
/*
*   Name: API_ISP_GetNR3DCfg
*            获取当前配置的NR3D的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_NR3D_CFG *pstNr3dCfg
*            类型为ISP_NR3D_CFG的结构体指针，详细成员变量请查看ISP_NR3D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetNr3dCfg(ISP_NR3D_CFG *pstNr3dCfg);
/*
*   Name: API_ISP_SetNR3DCoeffCfg
*            该函数可以配置NR3D的Coeff曲线，通过配置四对坐标可以配置Coeff曲线。
*
*   Parameters:
*
*       [IN] const ISP_NR3D_COEFF_CFG *pstNr3dCoeffCfg
*            类型为ISP_NR3D_COEFF_CFG的结构体指针，详细成员变量请查看ISP_NR3D_COEFF_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetNr3dCoeffCfg(ISP_NR3D_COEFF_CFG *pstNr3dCoeffCfg);
/** NR2D*/
/*
*   Name: API_ISP_SetNR2DCfg
*            配置NR2D的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_NR2D_CFG *pstNr2dCfg
*            类型为ISP_NR2D_CFG的结构体指针，详细成员变量请查看ISP_NR2D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetNR2DCfg(ISP_NR2D_CFG *pstNr2dCfg);
/*
*   Name: API_ISP_GetNR2DCfg
*            获取当前配置的NR2D的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_NR2D_CFG *pstNr2dCfg
*            类型为ISP_NR2D_CFG的结构体指针，详细成员变量请查看ISP_NR2D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetNR2DCfg(ISP_NR2D_CFG *pstNr2dCfg);

/**HLR*/
/*
*   Name: API_ISP_SetHlrCfg
*            配置HLR的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_HLR_CFG *pstHlrCfg
*            类型为ISP_HLR_CFG的结构体指针，详细成员变量请查看ISP_HLR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetHlrCfg(ISP_HLR_CFG *pstHlrCfg);
/*
*   Name: API_ISP_GetHlrCfg
*            获取当前配置的HLR的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_HLR_CFG *pstHlrCfg
*            类型为ISP_HLR_CFG的结构体指针，详细成员变量请查看ISP_HLR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetHlrCfg(ISP_HLR_CFG *pstHlrCfg);
/**IE*/
/*
*   Name: API_ISP_SetContrastCfg
*            配置对比度相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_CONTRAST_CFG *pstContrastCfg
*            类型为ISP_CONTRAST_CFG的结构体指针，详细成员变量请查看ISP_CONTRAST_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetContrastCfg(ISP_CONTRAST_CFG *pstContrastCfg);
/*
*   Name: API_ISP_GetContrastCfg
*            获取当前配置的对比度相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_CONTRAST_CFG *pstContrastCfg
*            类型为ISP_CONTRAST_CFG的结构体指针，详细成员变量请查看ISP_CONTRAST_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetContrastCfg(ISP_CONTRAST_CFG *pstContrastCfg);
/*
*   Name: API_ISP_SetBrightnessCfg
*            配置亮度相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_BRIGHTNESS_CFG *pstBrightnessCfg
*            类型为ISP_BRIGHTNESS_CFG的结构体指针，详细成员变量请查看ISP_BRIGHTNESS_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetBrightnessCfg(ISP_BRIGHTNESS_CFG *pstBrightnessCfg);
/*
*   Name: API_ISP_GetBrightnessCfg
*            获取当前配置的亮度相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_BRIGHTNESS_CFG *pstBrightnessCfg
*            类型为ISP_BRIGHTNESS_CFG的结构体指针，详细成员变量请查看ISP_BRIGHTNESS_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetBrightnessCfg(ISP_BRIGHTNESS_CFG *pstBrightnessCfg);
/**CE*/
/*
*   Name: API_ISP_SetSaturation
*            配置对比度相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_SAT_CFG *pstCeCfg
*            类型为ISP_SAT_CFG的结构体指针，详细成员变量请查看ISP_SAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSaturation(ISP_SAT_CFG *pstCeCfg);
/*
*   Name: API_ISP_GetSaturation
*            获取当前配置的对比度相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_SAT_CFG *pstCeCfg
*            类型为ISP_SAT_CFG的结构体指针，详细成员变量请查看ISP_SAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetSaturation(ISP_SAT_CFG *pstCeCfg);
/**APC*/
/*
*   Name: API_ISP_SetApcCfg
*            配置锐度相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_APC_CFG *pstApcCfg
*            类型为ISP_APC_CFG的结构体指针，详细成员变量请查看ISP_APC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetApcCfg(ISP_APC_CFG *pstApcCfg);
/*
*   Name: API_ISP_GetApcCfg
*            获取当前配置的锐度相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_APC_CFG *pstApcCfg
*            类型为ISP_APC_CFG的结构体指针，详细成员变量请查看ISP_APC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetApcCfg(ISP_APC_CFG *pstApcCfg);
/*
*   Name: API_ISP_SetApcMtCfg
*            配置apc与nr3d的联动参数
*
*   Parameters:
*
*       [IN] ISP_APC_MT_CFG *pstApcMtCfg
*            类型为ISP_APC_MT_CFG的结构体指针，详细成员变量请查看ISP_APC_MT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetApcMtCfg(ISP_APC_MT_CFG *pstApcMtCfg);
/*
*   Name: API_ISP_GetApcMtCfg
*            获取APC与nr3d的联动参数。
*
*   Parameters:
*
*       [OUT] ISP_APC_MT_CFG *pstApcMtCfg
*             类型为ISP_APC_MT_CFG的结构体指针，详细成员变量请查看ISP_APC_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetApcMtCfg(ISP_APC_MT_CFG *pstApcMtCfg);
/**GAMMA*/
/*
*   Name: API_ISP_SetGammaCfg
*            配置gamma相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_GAMMA_CFG *pstGammaCfg
*            类型为ISP_GAMMA_CFG的结构体指针，详细成员变量请查看ISP_GAMMA_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGammaCfg(ISP_GAMMA_CFG *pstGammaCfg);
/*
*   Name: API_ISP_GetGammaCfg
*            获取当前配置的gamma相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_GAMMA_CFG *pstGammaCfg
*            类型为ISP_GAMMA_CFG的结构体指针，详细成员变量请查看ISP_GAMMA_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGammaCfg(ISP_GAMMA_CFG *pstGammaCfg);

/**YCNR*/
/*
*   Name: API_ISP_SetYnrCfg
*            配置YNR相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_YNR_CFG *pstYnrCfg
*            类型为ISP_YNR_CFG的结构体指针，详细成员变量请查看ISP_YNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYnrCfg(ISP_YNR_CFG *pstYnrCfg);
/*
*   Name: API_ISP_GetYnrCfg
*            获取当前配置的YNR相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_YNR_CFG *pstYnrCfg
*            类型为ISP_YNR_CFG的结构体指针，详细成员变量请查看ISP_YNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetYnrCfg(ISP_YNR_CFG *pstYnrCfg);
/*
*   Name: API_ISP_SetYnrMtCfg
*            配置YNR与nr3d的联动参数。
*
*   Parameters:
*
*       [IN] ISP_YNR_MT_CFG *pstYnrMtCfg
*             类型为ISP_YNR_MT_CFG的结构体指针，详细成员变量请查看ISP_YNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYnrMtCfg(ISP_YNR_MT_CFG *pstYnrMtCfg);
/*
*   Name: API_ISP_GetYnrMtCfg
*           获取YNR与nr3d的联动参数。
*
*   Parameters:
*
*       [OUT] ISP_YNR_MT_CFG *pstYnrMtCfg
*             类型为ISP_YNR_MT_CFG的结构体指针，详细成员变量请查看ISP_YNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetYnrMtCfg(ISP_YNR_MT_CFG *pstYnrMtCfg);
/*
*   Name: API_ISP_SetCnrCfg
*            配置CNR相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_CNR_CFG *pstCnrCfg
*            类型为ISP_CNR_CFG的结构体指针，详细成员变量请查看ISP_CNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCnrCfg(ISP_CNR_CFG *pstCnrCfg);
/*
*   Name: API_ISP_GetCnrCfg
*            获取当前配置的CNR相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_CNR_CFG *pstCnrCfg
*            类型为ISP_CNR_CFG的结构体指针，详细成员变量请查看ISP_CNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCnrCfg(ISP_CNR_CFG *pstCnrCfg);
/*
*   Name: API_ISP_SetCnrMtCfg
*           设置CNR与nr3d的联动参数。
*
*   Parameters:
*
*       [IN] ISP_CNR_MT_CFG *pstCnrMtCfg
*             类型为ISP_CNR_MT_CFG的结构体指针，详细成员变量请查看ISP_CNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCnrMtCfg(ISP_CNR_MT_CFG *pstCnrMtCfg);
/*
*   Name: API_ISP_GetCnrMtCfg
*           获取CNR与nr3d的联动参数。
*
*   Parameters:
*
*       [OUT] ISP_CNR_MT_CFG *pstCnrMtCfg
*             类型为ISP_CNR_MT_CFG的结构体指针，详细成员变量请查看ISP_CNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCnrMtCfg(ISP_CNR_MT_CFG *pstCnrMtCfg);
/**PURPLE*/
/*
*   Name: API_ISP_SetAntiPurpleBoundary
*            配置去紫边相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_PURPLEFRI_CFG *pstPurplefriCfg
*            类型为ISP_PURPLEFRI_CFG的结构体指针，详细成员变量请查看ISP_PURPLEFRI_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAntiPurpleBoundary(ISP_PURPLEFRI_CFG *pstPurplefriCfg);
/*
*   Name: API_ISP_GetAntiPurpleBoundary
*            获取当前配置的去紫边的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_PURPLEFRI_CFG *pstPurplefriCfg
*            类型为ISP_PURPLEFRI_CFG的结构体指针，详细成员变量请查看ISP_PURPLEFRI_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAntiPurpleBoundary(ISP_PURPLEFRI_CFG *pstPurplefriCfg);

/**LC*/
/*
*   Name: API_ISP_SetLcCfg
*            配置Local Chroma相关的DRV寄存器
*
*   Parameters:
*
*       [IN] ISP_LC_CFG *pstLCCfg
*            类型为ISP_LC_CFG的结构体指针，详细成员变量请查看ISP_LC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLcCfg(ISP_LC_CFG *pstLCCfg);
/*
*   Name: API_ISP_GetLcCfg
*            获取当前配置的Local Chroma相关的DRV寄存器值
*
*   Parameters:
*
*       [OUT] ISP_LC_CFG *pstLCCfg
*            类型为ISP_LC_CFG的结构体指针，详细成员变量请查看ISP_LC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetLcCfg(ISP_LC_CFG *pstLCCfg);

/**Debug Interface**/
/*
*   Name: API_ISP_ReadMallocedMem
*            读取指定偏移的VMM分配的内存的值
*
*   Parameters:
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [OUT]  FH_UINT32 *pstData
*            存放读取到数据的地址。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_ReadMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
/*
*   Name: API_ISP_WriteMallocedMem
*            写指定偏移的VMM分配的内存的值
*
*   Parameters:
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [IN]  FH_UINT32 *pstData
*            目标值，将该值写入目标地址。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_WriteMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
/*
*   Name: API_ISP_ImportMallocedMem
*            导入指定大小的数据到指定偏移的VMM分配的内存
*
*   Parameters:
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [IN]  FH_UINT32 *pstSrc
*            导入数据的起始地址
*
*       [IN]  FH_UINT32 size
*            需要导入的数据大小
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_ImportMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstSrc, FH_UINT32 size);
/*
*   Name: API_ISP_ExportMallocedMem
*            从指定偏移的VMM分配的内存导出指定大小的数据
*
*   Parameters:
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [OUT]  FH_UINT32 *pstDst
*            存放导出数据的起始地址
*
*       [IN]  FH_UINT32 size
*            需要导出的数据大小
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_ExportMallocedMem(FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstDst, FH_UINT32 size);
/*
*   Name: API_ISP_GetVIState
*            获取当前ISP的一些运行状态信息
*
*   Parameters:
*
*       [OUT] ISP_VI_STAT_S *pstStat
*            类型为ISP_VI_STAT_S的结构体指针，详细成员变量请查看ISP_VI_STAT_S结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetVIState(ISP_VI_STAT_S *pstStat);
/*
*   Name: API_ISP_SetSensorFrameRate
*            配置SENSOR的垂直消隐至指定倍率
*
*   Parameters:
*
*       [IN] int m
*            垂直消隐的倍率,U.8,也即0x100表示一倍
*
*   Return:
*            0(正确)
*   Note:
*       当ae策略关闭时可使用该函数,策略打开时的帧消隐由策略参数控制,且只支持大于1倍的降帧
*/
FH_SINT32 API_ISP_SetSensorFrameRate(int m);
/*
*   Name: API_ISP_Dump_Param
*            拷贝所有DRV寄存器值到指定地址
*
*   Parameters:
*
*       [OUT] FH_UINT32 *addr
*            存放DRV参数的地址
*
*       [IN] FH_UINT32 *size
*            拷贝数据的大小
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Dump_Param(FH_UINT32 *addr,FH_UINT32 *size);
FH_SINT32 FUNC_DEP API_ISP_GetDebugInfo(ISP_DEBUG_INFO *pstIspDebug);
/**MIRROR*/
/*
*   Name: API_ISP_MirrorEnable
*            ISP的MIRROR模块，可以实现镜像,镜像后的pattern不需要配置,软件会自动转换。
*
*   Parameters:
*
*       [IN] MIRROR_CFG_S *pMirror
*            类型为MIRROR_CFG_S的结构体指针，详细成员变量请查看MIRROR_CFG_S结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_MirrorEnable(MIRROR_CFG_S *pMirror);
/*
*   Name: API_ISP_SetMirrorAndflip
*            配置SENSOR的镜像和水平翻转。
*
*   Parameters:
*
*       [IN] FH_BOOL mirror
*            镜像(mirror=1)，正常(mirror=0)
*
*       [IN]  FH_BOOL flip
*            水平翻转(flip=1)，正常(flip=0)
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetMirrorAndflip(FH_BOOL mirror, FH_BOOL flip);
/*
*   Name: API_ISP_SetMirrorAndflipEx
*            配置SENSOR的镜像和水平翻转，同时会更改ISP中相关bayer配置。
*
*   Parameters:
*
*       [IN] FH_BOOL mirror
*            镜像(mirror=1)，正常(mirror=0)
*
*       [IN]  FH_BOOL flip
*            水平翻转(flip=1)，正常(flip=0)
*
*       [IN] FH_UINT32 bayer
*            镜像和水平翻转影响之后的BAYER格式。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetMirrorAndflipEx(FH_BOOL mirror, FH_BOOL flip,FH_UINT32 bayer);
/*
*   Name: API_ISP_GetMirrorAndflip
*            获取当前SENSOR镜像和水平翻转的状态
*
*   Parameters:
*
*       [OUT] FH_BOOL *mirror
*            镜像(mirror=1)，正常(mirror=0)
*
*       [OUT]  FH_BOOL *flip
*            水平翻转(flip=1)，正常(flip=0)
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetMirrorAndflip(FH_BOOL *mirror, FH_BOOL *flip);

/**POST_GAIN*/
/*
*   Name: API_ISP_SetPostGain
*            设置postgain参数
*
*   Parameters:
*
*       [IN] const ISP_POST_GAIN_CFG *pstPostGainCfg
*            类型为ISP_POST_GAIN_CFG的结构体指针，详细成员变量请查看ISP_POST_GAIN_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       post_gain模块目前作为一部分数字增益使用,不建议随意配置增益,防止ae策略出现一些异常
*/
FH_SINT32 API_ISP_SetPostGain(const ISP_POST_GAIN_CFG *pstPostGainCfg);
/*
*   Name: API_ISP_GetPostGain
*           获取postgain参数
*
*   Parameters:
*
*       [OUT] ISP_POST_GAIN_CFG *pstPostGainCfg
*            类型为ISP_POST_GAIN_CFG的结构体指针，详细成员变量请查看ISP_POST_GAIN_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetPostGain(ISP_POST_GAIN_CFG *pstPostGainCfg);

/**RGBA*/
/*
*   Name: API_ISP_RgbaSendCmd
*            指令设置操作rgba相关参数
*
*   Parameters:
*
*       [] FH_UINT32 u32Cmd
*            指令号 可参考RGBA_CMD_KEY的枚举变量
*
*       []  FH_VOID *param
*            设置的参数值
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_RgbaSendCmd(FH_UINT32 u32Cmd, FH_VOID *param);
/*
*   Name: API_ISP_GetRgbaCfg
*            获得rgba参数配置
*
*   Parameters:
*
*       [] RGBA_DEFAULT_CFG *pstRgbaDefaultCfg
*            类型为RGBA_DEFAULT_CFG的结构体指针，详细成员变量请查看RGBA_DEFAULT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_GetRgbaCfg(RGBA_DEFAULT_CFG *pstRgbaDefaultCfg);
/*
*   Name: API_ISP_GetRgbaInfo
*            获取rgba当前状态
*
*   Parameters:
*
*       [] RGBA_CURR_INFO *pstRgbaInfo
*            类型为RGBA_CURR_INFO的结构体指针，详细成员变量请查看RGBA_CURR_INFO结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_GetRgbaInfo(RGBA_CURR_INFO *pstRgbaInfo);
/*
*   Name: API_ISP_GetRgbaStat
*            获得rgba统计信息
*
*   Parameters:
*
*       [] RGBA_STAT_INFO *pstRgbaStat
*            类型为RGBA_STAT_INFO的结构体指针，详细成员变量请查看RGBA_STAT_INFO结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_GetRgbaStat(RGBA_STAT_INFO *pstRgbaStat);
/*
*   Name: API_ISP_SetRgbaDpc
*            设置rgba dpc参数
*
*   Parameters:
*
*       [] RGBA_DPC_CFG *pstRgbaDpc
*            类型为RGBA_DPC_CFG的结构体指针，详细成员变量请查看RGBA_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_SetRgbaDpc(RGBA_DPC_CFG *pstRgbaDpc);
/*
*   Name: API_ISP_GetRgbaDpc
*            获得rgba dpc参数
*
*   Parameters:
*
*       [] RGBA_DPC_CFG *pstRgbaDpc
*            类型为RGBA_DPC_CFG的结构体指针，详细成员变量请查看RGBA_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 FUNC_DEP API_ISP_GetRgbaDpc(RGBA_DPC_CFG *pstRgbaDpc);

/**SMART IR**/
/*
*   Name: API_ISP_SetSmartIrCfg
*            设置智能切换日夜的参数
*
*   Parameters:
*
*       [IN] SMART_IR_CFG *pstSmartIrCfg
*            类型为SMART_IR_CFG的结构体指针，详细成员变量请查看SMART_IR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSmartIrCfg(SMART_IR_CFG *pstSmartIrCfg);
/*
*   Name: API_ISP_GetSmartIrCfg
*            获取智能切换日夜的参数
*
*   Parameters:
*
*       [OUT] SMART_IR_CFG *pstSmartIrCfg
*            类型为SMART_IR_CFG的结构体指针，详细成员变量请查看SMART_IR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetSmartIrCfg(SMART_IR_CFG *pstSmartIrCfg);
/**WDR**/
/*
*   Name: API_ISP_SetWdrShortFrameMergeCfg
*            该函数可以配置wdr下短帧的merge曲线，通过配置四对坐标可以配置短帧的merge曲线。
*
*   Parameters:
*
*       [IN] const ISP_WDR_MERGE_CFG *pstWdrMergeCfg
*            类型为ISP_WDR_MERGE_CFG的结构体指针，详细成员变量请查看ISP_WDR_MERGE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetWdrShortFrameMergeCfg(const ISP_WDR_MERGE_CFG *pstWdrMergeCfg);
/*
*   Name: API_ISP_SetWdrLongFrameMergeCfg
*            该函数可以配置wdr下长帧的merge曲线，通过配置四对坐标可以配置长帧的merge曲线。
*
*   Parameters:
*
*       [IN] const ISP_WDR_MERGE_CFG *pstWdrMergeCfg
*            类型为ISP_WDR_MERGE_CFG的结构体指针，详细成员变量请查看ISP_WDR_MERGE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetWdrLongFrameMergeCfg(const ISP_WDR_MERGE_CFG *pstWdrMergeCfg);
/*
*   Name: API_ISP_GetWdrCfg
*            用于获得wdr配置参数。
*
*   Parameters:
*
*       [OUT] ISP_WDR_CFG *pstWdrCfg
*            类型为ISP_WDR_CFG的结构体指针，详细成员变量请查看ISP_WDR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetWdrCfg(ISP_WDR_CFG *pstWdrCfg);
/*
*   Name: API_ISP_SetWdrCfg
*            用于设置wdr配置参数
*
*   Parameters:
*
*       [IN] ISP_WDR_CFG *pstWdrCfg
*            类型为ISP_WDR_CFG的结构体指针，详细成员变量请查看ISP_WDR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetWdrCfg(ISP_WDR_CFG *pstWdrCfg);
/**FC*/

/*
*   Name: API_ISP_SetFcCfg
*            配置去假色相关的寄存器
*
*   Parameters:
*
*       [IN] FC_CFG *pstFcCfg
*            类型为FC_CFG的结构体指针，详细成员变量请查看FC_CFG结构体定义。
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*      无
*/
FH_SINT32 API_ISP_SetFcCfg(FC_CFG *pstFcCfg);
/*
*   Name: API_ISP_GetFcCfg
*            获取当前去假色配置参数
*
*   Parameters:
*
*       [] FC_CFG *pstFcCfg
*            类型为FC_CFG的结构体指针，详细成员变量请查看FC_CFG结构体定义。
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*      无
*/
FH_SINT32 API_ISP_GetFcCfg(FC_CFG *pstFcCfg);
/**OTHERS*/
/*
*   Name: API_ISP_SetCropInfo
*            配置输入幅面的水平和垂直的处理偏移。
*
*   Parameters:
*
*       [IN] int offset_x
*            水平方向的偏移
*
*       [IN] int offset_y
*            垂直方向的偏移。
*
*   Return:
*            0(正确)
*        -3004(偏移值超过输入幅面或者为奇数)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCropInfo(int offset_x,int offset_y);
/*
*   Name: *FH_ISP_Version
*            获取、打印ISP版本号。
*
*   Parameters:
*
*       [IN] FH_UINT32 print_enable
*            打印ISP库版本号(1)，不打印ISP库版本号(0)
*
*   Return:
*            ISP库版本号的字符串。
*   Note:
*       无
*/
FH_CHAR *FH_ISP_Version(FH_UINT32 print_enable);
/*
*   Name: *FH_ISPCORE_Version
*            获取、打印ISP版本号。
*
*   Parameters:
*
*       [IN] FH_UINT32 print_enable
*            打印ISP_CORE库的版本号(1)，不打印ISP_CORE库的版本号(0)
*
*   Return:
*            ISP_CORE库的版本号的字符串。
*   Note:
*       无
*/
FH_CHAR *FH_ISPCORE_Version(FH_UINT32 print_enable);
/**FAST_BOOT**/
/*
*   Name: API_ISP_RegisterPicStartCallback
*            在ISP PicStartB的时候的回调函数，可以用在RTT下统计时间。
*
*   Parameters:
*
*       [IN] ispIntCallback cb
*            void型的函数指针，指向回调函数的位置。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_RegisterPicStartCallback(ispIntCallback cb);
/*
*   Name: API_ISP_RegisterPicEndCallback
*            在ISP PicEndP的时候的回调函数，可以用在RTT下统计时间。
*
*   Parameters:
*
*       [IN] ispIntCallback cb
*            void型的函数指针，指向回调函数的位置。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_RegisterPicEndCallback(ispIntCallback cb);
/*
*   Name: API_ISP_RegisterIspInitCfgCallback
*            ISP硬件初始化回调函数，其执行位置在API_ISP_Init之前，此时ISP未启动，流程中仅执行一次。
*
*   Parameters:
*
*       [IN] ispInitCfgCallback cb
*            void型的函数指针，指向回调函数的位置。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_RegisterIspInitCfgCallback(ispInitCfgCallback cb);
/*
*   Name: API_ISP_SetBlcInitCfg
*            初始化BLC所有通道的减DC值，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const BLC_INIT_CFG *pstBlcInitCfg
*            类型为BLC_INIT_CFG的结构体指针，详细成员变量请查看BLC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetBlcInitCfg(const BLC_INIT_CFG *pstBlcInitCfg);
/*
*   Name: API_ISP_SetWbInitCfg
*            初始化WB三个通道增益值，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const WB_INIT_CFG *pstWbInitCfg
*            类型为WB_INIT_CFG的结构体指针，详细成员变量请查看WB_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetWbInitCfg(const WB_INIT_CFG *pstWbInitCfg);
/*
*   Name: API_ISP_SetCcmInitCfg
*            初始化CCM矩阵硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] CCM_INIT_CFG *pstCcmInitCfg
*            类型为DPC_INIT_CFG的结构体指针，详细成员变量请查看DPC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcmInitCfg(const CCM_INIT_CFG *pstCcmInitCfg);
/*
*   Name: API_ISP_SetDpcInitCfg
*            初始化DPC硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const DPC_INIT_CFG *pstDpcInitCfg
*            类型为DPC_INIT_CFG的结构体指针，详细成员变量请查看DPC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDpcInitCfg(const DPC_INIT_CFG *pstDpcInitCfg);
/*
*   Name: API_ISP_SetApcInitCfg
*            初始化APC硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const APC_INIT_CFG *pstApcInitCfg
*            类型为APC_INIT_CFG的结构体指针，详细成员变量请查看APC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetApcInitCfg(const APC_INIT_CFG *pstApcInitCfg);
/*
*   Name: API_ISP_SetYnrInitCfg
*            初始化YNR硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const YNR_INIT_CFG *pstYnrInitCfg
*            类型为YNR_INIT_CFG的结构体指针，详细成员变量请查看YNR_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYnrInitCfg(const YNR_INIT_CFG *pstYnrInitCfg);
/*
*   Name: API_ISP_SetCtrInitCfg
*            配置对比度值到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const CTR_INIT_CFG *pstCtrInitCfg
*            类型为CTR_INIT_CFG的结构体指针，详细成员变量请查看CTR_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCtrInitCfg(const CTR_INIT_CFG *pstCtrInitCfg);
/*
*   Name: API_ISP_SetSatInitCfg
*            配置饱和度值到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const SAT_INIT_CFG *pstSatInitCfg
*            SAT_INIT_CFG的结构体指针，详细参数查看结构体SAT_INIT_CFG注释。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSatInitCfg(const SAT_INIT_CFG *pstSatInitCfg);
/*
*   Name: API_ISP_SetGammaModeInitCfg
*            根据传入的gamma mode值，配置相应硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const GAMMA_MODE_INIT_CFG *pstGammaModeInitCfg
*            目标配置的gamma mode。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGammaModeInitCfg(const GAMMA_MODE_INIT_CFG *pstGammaModeInitCfg);
/*
*   Name: API_ISP_SetCGammaInitCfg
*            配置cgamma table到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const GAMMA_INIT_CFG *pstCGammaInitCfg
*            结构体GAMMA_INIT_CFG的指针，目标配置cgamma表。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCGammaInitCfg(const GAMMA_INIT_CFG *pstCGammaInitCfg);
/*
*   Name: API_ISP_SetYGammaInitCfg
*            配置ygamma table到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const GAMMA_INIT_CFG *pstYGammaInitCfg
*            结构体GAMMA_INIT_CFG的指针，目标配置的ygamma表。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYGammaInitCfg(const GAMMA_INIT_CFG *pstYGammaInitCfg);
/*
*   Name: API_ISP_SetLtmInitCfg
*            配置Ltm table到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const LTM_INIT_CFG *pstLtmInitCfg
*            结构体LTM_INIT_CFG的指针，目标配置的Ltm表。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLtmInitCfg(const LTM_INIT_CFG *pstLtmInitCfg);
/*
*   Name: API_ISP_SetIspGainInitCfg
*            配置Isp Gain到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN] const ISP_GAIN_INIT_CFG *pstIspGainInitCfg
*            结构体ISP_GAIN_INIT_CFG的指针，目标配置的Isp Gain。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetIspGainInitCfg(const ISP_GAIN_INIT_CFG *pstIspGainInitCfg);
/*
*   Name: API_ISP_SetDehazeFltModeInitCfg
*            配置Dehaze Filter Config到硬件寄存器。
*
*   Parameters:
*
*       [IN] FH_UINT8 mode
*            Dehaze FIlter Config mode。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDehazeFiltModeInitCfg(FH_UINT8 mode);
/**CCM**/
/*
*   Name: API_ISP_SetCcmCfg
*            配置CCM。
*
*   Parameters:
*
*       [IN] CCM_TABLE *pstCcmCfg
*             类型为CCM_TABLE的结构体指针，详细成员变量请查看CCM_TABLE结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcmCfg(CCM_TABLE *pstCcmCfg);
/*
*   Name: API_ISP_GetCcmCfg
*           获取CCM。
*
*   Parameters:
*
*       [IN] CCM_TABLE *pstCcmCfg
*             类型为CCM_TABLE的结构体指针，详细成员变量请查看CCM_TABLE结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCcmCfg(CCM_TABLE *pstCcmCfg);
/*
*   Name: API_ISP_SetCcm2Cfg
*            配置CCM2。
*
*   Parameters:
*
*       [IN] ISP_CCM_CFG *pstCcmCfg
*             类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcm2Cfg(ISP_CCM_CFG *pstCcmCfg);
/*
*   Name: API_ISP_GetCcm2Cfg
*           获取CCM2。
*
*   Parameters:
*
*       [IN] ISP_CCM_CFG *pstCcmCfg
*             类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCcm2Cfg(ISP_CCM_CFG *pstCcmCfg);
/*
*   Name: API_ISP_SetCcmHwCfg
*            配置ccm参数至硬件寄存器
*
*   Parameters:
*
*       [IN] const ISP_CCM_CFG *pstCcmCfg
*             类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcmHwCfg(const ISP_CCM_CFG *pstCcmCfg);
/*
*   Name: API_ISP_GetCcmHwCfg
*            从硬件寄存器获取ccm参数
*
*   Parameters:
*
*       [OUT] ISP_CCM_CFG *pstCcmCfg
*            类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCcmHwCfg(ISP_CCM_CFG *pstCcmCfg);
/*
*   Name: API_ISP_SetCcm2HwCfg
*            配置ccm2参数至硬件寄存器
*
*   Parameters:
*
*       [IN] const ISP_CCM_CFG *pstCcmCfg
*             类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcm2HwCfg(const ISP_CCM_CFG *pstCcmCfg);
/*
*   Name: API_ISP_GetCcm2HwCfg
*            从硬件寄存器获取ccm2参数
*
*   Parameters:
*
*       [OUT] ISP_CCM_CFG *pstCcmCfg
*            类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCcm2HwCfg(ISP_CCM_CFG *pstCcmCfg);
/**DEHAZE**/
/*
*   Name: API_ISP_SetDehazeCfg
*           设置去雾参数。
*
*   Parameters:
*
*       [IN] ISP_DEHAZE_CFG *pstDehazeCfg
*             类型为ISP_DEHAZE_CFG的结构体指针，详细成员变量请查看ISP_DEHAZE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDehazeCfg(ISP_DEHAZE_CFG *pstDehazeCfg);
/*
*   Name: API_ISP_GetDehazeCfg
*           获得去雾参数。
*
*   Parameters:
*
*       [OUT] ISP_DEHAZE_CFG *pstDehazeCfg
*             类型为ISP_DEHAZE_CFG的结构体指针，详细成员变量请查看ISP_DEHAZE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDehazeCfg(ISP_DEHAZE_CFG *pstDehazeCfg);
/*
*   Name: API_ISP_SetDeCfg
*           设置暗部增强参数。
*
*   Parameters:
*
*       [IN] ISP_DE_CFG *pstDeCfg
*             类型为ISP_DE_CFG的结构体指针，详细成员变量请查看ISP_DE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDeCfg(ISP_DE_CFG *pstDeCfg);
/*
*   Name: API_ISP_GetDeCfg
*           获得暗部参数。
*
*   Parameters:
*
*       [OUT] ISP_DE_CFG *pstDeCfg
*             类型为ISP_DE_CFG的结构体指针，详细成员变量请查看ISP_DE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDeCfg(ISP_DE_CFG *pstDeCfg);
/**LCE**/
/*
*   Name: API_ISP_SetLceCfg
*           设置局部色度参数。
*
*   Parameters:
*
*       [IN] ISP_LCE_CFG *pstLceCfg
*             类型为ISP_LCE_CFG的结构体指针，详细成员变量请查看ISP_LCE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLceCfg(ISP_LCE_CFG *pstLceCfg);
/*
*   Name: API_ISP_GetLceCfg
*           获得局部色度参数。
*
*   Parameters:
*
*       [OUT] ISP_LCE_CFG *pstLceCfg
*             类型为ISP_LCE_CFG的结构体指针，详细成员变量请查看ISP_LCE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetLceCfg(ISP_LCE_CFG *pstLceCfg);

/** STATISTICS **/
/*
*   Name: API_ISP_GetAeStat
*            获取AE统计值
*
*   Parameters:
*
*       [OUT] ISP_AE_STAT * pstAeStat
*            类型为ISP_AE_STAT的结构体指针，详细成员变量请查看ISP_AE_STAT结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeStat(ISP_AE_STAT * pstAeStat);
/*
*   Name: API_ISP_SetAeStatCfg
*            设置ae统计配置相关参数
*
*   Parameters:
*
*       [IN] const ISP_AE_STAT_CFG *pstAeStatCfg
*            类型为ISP_AE_STAT_CFG的结构体指针，详细成员变量请查看ISP_AE_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAeStatCfg(const ISP_AE_STAT_CFG *pstAeStatCfg);
/*
*   Name: API_ISP_GetAeStatCfg
*            获取ae统计配置相关参数
*
*   Parameters:
*
*       [OUT] ISP_AE_STAT_CFG *pstAeStatCfg
*            类型为ISP_AE_STAT_CFG的结构体指针，详细成员变量请查看ISP_AE_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeStatCfg(ISP_AE_STAT_CFG *pstAeStatCfg);
/*
*   Name: API_ISP_GetAFStat
*           读取af统计结果信息。
*
*   Parameters:
*
*       [OUT] ISP_AF_STAT *pstAfStat
*            类型为ISP_AF_STAT的结构体指针，详细成员变量请查看ISP_AF_STAT结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAFStat(ISP_AF_STAT *pstAfStat);
/*
*   Name: API_ISP_SetAFStatCfg
*            设置af统计配置相关参数。
*
*   Parameters:
*
*       [IN] const ISP_AF_STAT_CFG *pstAfStatCfg
*            类型为ISP_AF_STAT_CFG的结构体指针，详细成员变量请查看ISP_AF_STAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       1. af的win0和win1两个窗口不能有交叠,否则统计数据可能会出错
*       2. 统计窗的大小参数输入范围为0-512，实际生效的统计窗的大小为2-512
*       3. 统计窗的大小和偏移都只支持偶数，输入非偶数时API会自动校正为偶数
*/
FH_SINT32 API_ISP_SetAFStatCfg(const ISP_AF_STAT_CFG *pstAfStatCfg);
/*
*   Name: API_ISP_GetAFStatCfg
*            获取af统计配置相关参数。
*
*   Parameters:
*
*       [OUT] const ISP_AF_STAT_CFG *pstAfStatCfg
*            类型为ISP_AF_STAT_CFG的结构体指针，详细成员变量请查看ISP_AF_STAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAFStatCfg(ISP_AF_STAT_CFG *pstAfStatCfg);
/*
*   Name: API_ISP_GetAwbStat
*            获取awb 3*3统计信息
*
*   Parameters:
*
*       [OUT] ISP_AWB_STAT * pstAwbStat
*            类型为ISP_AWB_STAT的结构体指针，详细成员变量请查看ISP_AWB_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbStat(ISP_AWB_STAT * pstAwbStat);
/*
*   Name: API_ISP_SetAwbStatCfg
*            设置awb 3*3统计配置相关参数
*
*   Parameters:
*
*       [IN] const ISP_AWB_STAT_CFG *pstAwbStatCfg
*            类型为ISP_AWB_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       传入的参数经过计算后可能由于对齐问题与获取的参数不完全一致
*/
FH_SINT32 API_ISP_SetAwbStatCfg(const ISP_AWB_STAT_CFG *pstAwbStatCfg);
/*
*   Name: API_ISP_GetAwbStatCfg
*            获取awb 3*3统计配置相关参数
*
*   Parameters:
*
*       [OUT] ISP_AWB_STAT_CFG *pstAwbStatCfg
*            类型为ISP_AWB_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbStatCfg(ISP_AWB_STAT_CFG *pstAwbStatCfg);

/*
*   Name: API_ISP_GetAwbAdvStat
*            获取awb高级统计信息
*
*   Parameters:
*
*       [OUT] ISP_AWB_ADV_STAT * pstAwbAdvStat
*            类型为ISP_AWB_ADV_STAT的结构体指针，详细成员变量请查看ISP_AWB_ADV_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       统计窗个数默认16*16,也可通过API_ISP_SetAwbAdvStatCfg进行重新配置,最大支持32*32
*       使用示例:
*              ISP_AWB_ADV_STAT awbAdvStat[256];  // 256是默认窗口配置,若改动的话通过API_ISP_GetAwbAdvStatCfg获取当前统计窗个数
*              API_ISP_GetAwbAdvStat(awbAdvStat);
*/
FH_SINT32 API_ISP_GetAwbAdvStat(ISP_AWB_ADV_STAT * pstAwbAdvStat);
/*
*   Name: API_ISP_SetAwbAdvStatCfg
*            设置awb高级统计配置相关参数
*
*   Parameters:
*
*       [IN] const ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg
*            类型为ISP_AWB_ADV_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_ADV_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAwbAdvStatCfg(const ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg);
/*
*   Name: API_ISP_GetAwbAdvStatCfg
*            获取awb高级统计配置相关参数
*
*   Parameters:
*
*       [OUT] ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg
*            类型为ISP_AWB_ADV_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_ADV_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbAdvStatCfg(ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg);

/*
*   Name: API_ISP_GetShortAwbStat
*            获取awb短帧8*8统计信息
*
*   Parameters:
*
*       [OUT] ISP_AWB_FRONT_STAT * pstAwbFrontStat
*            类型为ISP_AWB_FRONT_STAT的结构体指针，详细成员变量请查看ISP_AWB_FRONT_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetShortAwbStat(ISP_AWB_FRONT_STAT * pstAwbFrontStat);
/*
*   Name: API_ISP_SetShortAwbStatCfg
*            设置awb短帧8*8统计配置相关参数
*
*   Parameters:
*
*       [IN] const ISP_AWB_STAT_CFG * pstAwbFrontStatCfg
*            类型为ISP_AWB_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       传入的参数经过计算后可能由于对齐问题与获取的参数不完全一致
*/
FH_SINT32 API_ISP_SetShortAwbStatCfg(const ISP_AWB_STAT_CFG * pstAwbFrontStatCfg);
/*
*   Name: API_ISP_GetShortAwbStatCfg
*            获取awb短帧8*8统计配置相关参数
*
*   Parameters:
*
*       [OUT] ISP_AWB_STAT_CFG * pstAwbFrontStatCfg
*            类型为ISP_AWB_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetShortAwbStatCfg(ISP_AWB_STAT_CFG * pstAwbFrontStatCfg);
/*
*   Name: API_ISP_GetHistStat
*            获取hist统计结果
*
*   Parameters:
*
*       [OUT] ISP_HIST_STAT *psthistStat
*            类型为ISP_HIST_STAT的结构体指针，详细成员变量请查看ISP_HIST_STAT结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetHistStat(ISP_HIST_STAT *psthistStat);
/*
*   Name: API_ISP_SetHistStatCfg
*            设置hist统计配置相关参数
*
*   Parameters:
*
*       [IN] const ISP_HIST_STAT_CFG *pstHistStatCfg
*            类型为ISP_HIST_STAT_CFG的结构体指针，详细成员变量请查看ISP_HIST_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetHistStatCfg(const ISP_HIST_STAT_CFG *pstHistStatCfg);
/*
*   Name: API_ISP_GetHistStatCfg
*            获取hist统计配置相关参数
*
*   Parameters:
*
*       [OUT] ISP_HIST_STAT_CFG *pstHistStatCfg
*            类型为ISP_HIST_STAT_CFG的结构体指针，详细成员变量请查看ISP_HIST_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetHistStatCfg(ISP_HIST_STAT_CFG *pstHistStatCfg);
/**GLOBAL_STAT**/
/*
*   Name: API_ISP_GetGlobeStat
*            获取global统计信息
*
*   Parameters:
*
*       [OUT] GLOBE_STAT *pstGlobeStat
*            类型为GLOBE_STAT的结构体指针，详细成员变量请查看GLOBE_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       使用示例:
*               GLOBE_STAT glStat[256];  // 256是默认窗口配置,若改动的话通过API_ISP_GetGlobeStatCfg获取当前统计窗个数
*               API_ISP_GetGlobeStat(glStat);
*/
FH_SINT32 API_ISP_GetGlobeStat(GLOBE_STAT *pstGlobeStat);
/*
*   Name: API_ISP_SetGlobeStatCfg
*            设置global统计配置相关参数
*
*   Parameters:
*
*       [IN] const GLOBE_STAT_CFG *pstGlobeStatCfg
*            类型为GLOBE_STAT_CFG的结构体指针，详细成员变量请查看GLOBE_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGlobeStatCfg(const GLOBE_STAT_CFG *pstGlobeStatCfg);
/*
*   Name: API_ISP_GetGlobeStatCfg
*            获取global统计配置相关参数
*
*   Parameters:
*
*       [OUT] GLOBE_STAT_CFG *pstGlobeStatCfg
*            类型为GLOBE_STAT_CFG的结构体指针，详细成员变量请查看GLOBE_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGlobeStatCfg(GLOBE_STAT_CFG *pstGlobeStatCfg);
/*
*   Name: API_ISP_GetDehazeStat
*            获取Dehaze统计
*
*   Parameters:
*
*       [OUT] DEHAZE_STAT *pstDehazeStat
*            类型为DEHAZE_STAT的结构体指针，详细成员变量请查看DEHAZE_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDehazeStat(DEHAZE_STAT *pstDehazeStat);
/*
*   Name: API_ISP_GetFirstStageParam
*            获取第一阶段传给小图isp效果参数以及拉高gpio延时时间等
*
*   Parameters:
*
*       [OUT] ISP_SENSOR_COMMON_CMD_DATA0 *pstFirstStageParamCfg
*            类型为ISP_SENSOR_COMMON_CMD_DATA0的结构体指针，详细成员变量请查看ISP_SENSOR_COMMON_CMD_DATA0结构体定义。
*
*   Return:
*        0(正确返回)
*        -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetFirstStageParam(ISP_SENSOR_COMMON_CMD_DATA0 *pstFirstStageParamCfg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*_ISP_API_H_*/
