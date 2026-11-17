#ifndef _MIPI_API_H_
#define _MIPI_API_H_


enum FRQ_RANGE
{
    R_80_89      = 0,
    R_90_99      = 16,
    R_100_109    = 32,
    R_110_129    = 1,
    R_130_139    = 17,
    R_140_149    = 33,
    R_150_169    = 2,
    R_170_179    = 18,
    R_180_199    = 34,
    R_200_219    = 3,
    R_220_239    = 19,
    R_240_249    = 35,
    R_250_269    = 4,
    R_270_299    = 20,
    R_300_329    = 5,
    R_330_359    = 21,
    R_360_399    = 37,
    R_400_449    = 6,
    R_450_499    = 22,
    R_500_549    = 7,
    R_550_599    = 23,
    R_600_649    = 8,
    R_650_699    = 24,
    R_700_749    = 9,
    R_750_799    = 25,
    R_800_849    = 41,
    R_850_899    = 57,
    R_900_949    = 10,
    R_950_999    = 26,
    R_1000_1049  = 42,
    R_1050_1099  = 58,
    R_1100_1149  = 11,
    R_1150_1199  = 27,
    R_1200_1249  = 43,
    R_1250_1299  = 59,
    R_1300_1349  = 12,
    R_1350_1399  = 28,
    R_1400_1449  = 44,
    R_1450_1500  = 60,

};

enum SENSOR_MODE
{
    NON_WDR=0,
    NOT_SONY_WDR_USE_WDR=1,
    SONY_WDR_NOT_USE_WDR=2,
    SONY_WDR_USE_WDR=3,
};

enum RAW_TYPE
{
    RAW10=0,
    RAW12=1,
};

struct mipi_conf
{
    int frq_range;
    int sensor_mode;
    int raw_type;
    int lf_vc_id;
    int sf_vc_id;
    int lane_num;

};

void mipi_init(struct mipi_conf *config);

/**
* FH_MIPI_Version
*@brief 按SDK的统一格式定义的版本信息
*@param [in] print_enable:是否打印版本信息
*@param [out] 无
*@return 是否成功
* - RETURN_OK(0):  成功
* - 其他：失败,错误详见错误号
*/
char *FH_MIPI_Version(unsigned int print_enable);
#endif