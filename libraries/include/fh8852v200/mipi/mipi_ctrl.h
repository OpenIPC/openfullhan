#ifndef _MIPI_CTRL_H
#define _MIPI_CTRL_H
#define SET_MIPI_REG(addr,value) (*(volatile unsigned int *)(addr)=(value))
#define GET_MIPI_REG(addr) (*((volatile unsigned int *)(addr)))

//mipi ctrl related reg list
// #define PMU_REG_BASE  0xf0000000
#define MIPIC_WRAPPER_REG_BASE 0xf1000000
#define MIPIC_REG_BASE 0xf1100000


// struct Reg_Pmu
// {
//     unsigned int             reserverd_1[5];      //0x00
//     unsigned int             sys_ctrl;            //0x14
//     unsigned int             reserverd_2[122];    //0x10
//     unsigned int             clk_gate;            //0x200
//     unsigned int             reserverd_3[3];      //0x204
//     unsigned int             clk_sel;             //0x210
// };

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
    // volatile struct Reg_Pmu     *pmu_reg;
    volatile struct Reg_Mipic_Wrapper    *mipi_wrapper;
    volatile struct Reg_Mipic    *mipi_reg;

};

char *get_mipi_version(unsigned int print_enable);

#endif
