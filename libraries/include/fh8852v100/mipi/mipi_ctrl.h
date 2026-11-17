/* BUILD VERSION: FH8856_IPC_V1.2.0_20200324 @ aee6fa1 */
#ifndef _MIPI_CTRL_H
#define _MIPI_CTRL_H
#define SET_MIPI_REG(addr,value) (*(volatile unsigned int *)(addr)=(value))
#define GET_MIPI_REG(addr) (*((volatile unsigned int *)(addr)))

//mipi ctrl related reg list
#define PMU_REG_BASE  0xf0000000
#define MIPIC_WRAPPER_REG_BASE 0xf1000000
#define MIPIC_REG_BASE 0xf1100000


struct Reg_Pmu
{
    unsigned int             reserverd_1;         //0x0
    unsigned int             reserverd_2;         //0x4
    unsigned int             reserverd_3;         //0x8
    unsigned int             sys_ctrl;            //0x0c
    unsigned int             reserverd_5;         //0x10
    unsigned int             reserverd_6;         //0x14
    unsigned int             reserverd_7;         //0x18
    unsigned int             clk_gate;            //0x1c
    unsigned int             clk_sel;             //0x20
    unsigned int             reserverd_8;         //0x24
    unsigned int             reserverd_9;         //0x28
    unsigned int             clk_div2;            //0x2c

};

struct Reg_Mipic_Wrapper
{
    unsigned int             mipic_wrap_ctrl;         //0x0
    unsigned int             mipic_wrap_int_en;       //0x4
    unsigned int             mipic_wrap_int_status;   //0x8


};

struct Reg_Mipic
{
    unsigned int             mipic_version;                      //0x000
    unsigned int             mipic_n_lanes;                      //0x004
    unsigned int             mipic_csi2_resetn;                  //0x008
    unsigned int             mipic_int_st_main;                  //0x00c
    unsigned int             mipic_data_ids_1;                   //0x010
    unsigned int             mipic_data_ids_2;                   //0x014
    unsigned int             mipic_reserverd_1[10];              //0x018-0x3c
    unsigned int             mipic_phy_shutdownz;                //0x040
    unsigned int             mipic_dphy_rstz;                    //0x044
    unsigned int             mipic_phy_rx;                       //0x048
    unsigned int             mipic_phy_stopstate;                //0x04c
    unsigned int             mipic_phy_test_ctrl0;               //0x050
    unsigned int             mipic_phy_test_ctrl1;               //0x054
    unsigned int             mipic_phy2_test_ctrl0;              //0x058
    unsigned int             mipic_phy2_test_ctrl1;              //0x05c
    unsigned int             mipic_reserverd_2[8];               //0x060-0x7c
    unsigned int             mipic_ipi_mode;                     //0x080
    unsigned int             mipic_ipi_vcid;                     //0x084
    unsigned int             mipic_ipi_data_type;                //0x088
    unsigned int             mipic_ipi_mem_flush;                //0x08c
    unsigned int             mipic_ipi_hsa_time;                 //0x090
    unsigned int             mipic_ipi_hbp_time;                 //0x094
    unsigned int             mipic_ipi_hsd_time;                 //0x098
    unsigned int             mipic_ipi_hline_time;               //0x09c
    unsigned int             mipic_reserverd_3[4];               //0x0a0-0xaf
    unsigned int             mipic_ipi_vsa_lines;                //0x0b0
    unsigned int             mipic_ipi_vbp_lines;                //0x0b4
    unsigned int             mipic_ipi_vfp_lines;                //0x0b8
    unsigned int             mipic_ipi_vactive_lines;            //0x0bc
    unsigned int             mipic_reserverd_4[8];               //0x0c0-0xdc
    unsigned int             mipic_int_st_phy_fatal;             //0x0e0
    unsigned int             mipic_int_msk_phy_fatal;            //0x0e4
    unsigned int             mipic_int_force_phy_fatal;          //0x0e8
    unsigned int             mipic_reserverd_5;                  //0x0ec
    unsigned int             mipic_int_st_pkt_fatal;             //0x0f0
    unsigned int             mipic_int_msk_pkt_fatal;            //0x0f4
    unsigned int             mipic_int_force_pkt_fatal;          //0x0f8
    unsigned int             mipic_reserverd_6;                  //0x0fc
    unsigned int             mipic_int_st_frame_fatal;           //0x100
    unsigned int             mipic_int_msk_frame_fatal;          //0x104
    unsigned int             mipic_int_force_frame_fatal;        //0x108
    unsigned int             mipic_reserverd_7;                  //0x10c
    unsigned int             mipic_int_st_phy;                   //0x110
    unsigned int             mipic_int_msk_phy;                  //0x114
    unsigned int             mipic_int_force_phy;                //0x118
    unsigned int             mipic_reserverd_8;                  //0x11c
    unsigned int             mipic_int_st_pkt;                   //0x120
    unsigned int             mipic_int_msk_pkt;                  //0x124
    unsigned int             mipic_int_force_pkt;                //0x128
    unsigned int             mipic_reserverd_9;                  //0x12c
    unsigned int             mipic_int_st_line;                  //0x130
    unsigned int             mipic_int_msk_line;                 //0x134
    unsigned int             mipic_int_force_line;               //0x138
    unsigned int             mipic_reserverd_10;                 //0x13c
    unsigned int             mipic_int_st_ipi;                   //0x140
    unsigned int             mipic_msk_int_ipi;                  //0x144
    unsigned int             mipic_force_int_ipi;                //0x148

};

struct mipi_common
{
    volatile struct Reg_Pmu     *pmu_reg;
    volatile struct Reg_Mipic_Wrapper    *mipi_wrapper;
    volatile struct Reg_Mipic    *mipi_reg;

};

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
char *get_mipi_version(unsigned int print_enable);

#endif
