/*
* ovos05_mipi.h
*
*  Created on: Jun 29, 2015
*      Author: duobao
*/

#ifndef OVOS05_MIPI_H_
#define OVOS05_MIPI_H_

#include "cfg/ovos05_mipi_2lane_400w20.h"
#include "cfg/ovos05_mipi_2lane_400w25.h"
#include "cfg/ovos05_mipi_2lane_400w30.h"
#include "cfg/ovos05_mipi_2lane_400w25_wdr.h"
#include "cfg/ovos05_mipi_2lane_400w30_wdr.h"
#include "cfg/ovos05_mipi_2lane_500w12p5.h"
#include "cfg/ovos05_mipi_2lane_500w25.h"
#include "cfg/ovos05_mipi_2lane_2304X1296P25.h"
#include "cfg/ovos05_mipi_2lane_2304X1296P25_wdr.h"
#include "cfg/ovos05_mipi_4lane_1080p20.h"
#include "cfg/ovos05_mipi_4lane_1080p25.h"
#include "cfg/ovos05_mipi_4lane_1536p25_wdr.h"
#include "cfg/ovos05_mipi_4lane_1536p30_wdr.h"
#include "cfg/ovos05_mipi_4lane_1536p40_wdr.h"
#include "cfg/ovos05_mipi_4lane_400w25.h"
#include "cfg/ovos05_mipi_4lane_400w25_wdr.h"
#include "cfg/ovos05_mipi_4lane_400w30.h"
#include "cfg/ovos05_mipi_4lane_400w30_wdr.h"
#include "cfg/ovos05_mipi_4lane_500w12p5_wdr.h"
#include "cfg/ovos05_mipi_4lane_500w15.h"
#include "cfg/ovos05_mipi_4lane_500w15_wdr.h"
#include "cfg/ovos05_mipi_4lane_500w20.h"
#include "cfg/ovos05_mipi_4lane_500w20_wdr.h"
#include "cfg/ovos05_mipi_4lane_500w25_wdr.h"
#define current_sns_conf sns_conf.conf[sns_cfg.sns_conf_num]
#define current_sns_attr sns_conf.conf[sns_cfg.sns_conf_num].sns_attr

static SensorConfigPtr sns_conf;
// 用于0x20的sensor的配置
static SensorConfig sns_conf0[] =
{

    {
        .sns_fmt        = FORMAT_WDR_500W12P5,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_500W12P5) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_500W12P5,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_500w12
    },

    {
        .sns_fmt        = FORMAT_WDR_1536P25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_1536P25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_1536P25,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_1536p25
    },

    {
        .sns_fmt        = FORMAT_WDR_1536P30,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_1536P30) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_1536P30,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_1536p30
    },

    {
        .sns_fmt        = FORMAT_WDR_1536P40,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_1536P40) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_1536P40,
        .mipi_clk_rate  = R_950_999,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_1536p40
    },

    {
        .sns_fmt        = FORMAT_WDR_400WP25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_400WP25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_400WP25,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_400wp25
    },

    {
        .sns_fmt        = FORMAT_WDR_400WP30,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_400WP30) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_400WP30,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_400wp30
    },

    {
        .sns_fmt        = FORMAT_WDR_500WP15,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_500WP15) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_500WP15,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_500wp15
    },

    {
        .sns_fmt        = FORMAT_WDR_500WP20,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_500WP20) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_500WP20,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_500wp20
    },

    {
        .sns_fmt        = FORMAT_WDR_500WP25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_WDR_500WP25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_WDR_500WP25,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_wdr_500wp25
    },

    {
        .sns_fmt        = FORMAT_400WP25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_400WP25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_400WP25,
        .mipi_clk_rate  = R_500_549,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_400wp25
    },

    {
        .sns_fmt        = FORMAT_1080P25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_400WP25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_400WP25,
        .mipi_clk_rate  = R_500_549,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_1080p25
    },

    {
        .sns_fmt        = FORMAT_400WP30,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_400WP30) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_400WP30,
        .mipi_clk_rate  = R_500_549,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_400wp30
    },

    {
        .sns_fmt        = FORMAT_500WP15,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_500WP15) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_500WP15,
        .mipi_clk_rate  = R_500_549,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_500wp15
    },

    {
        .sns_fmt        = FORMAT_500WP20,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_500WP20) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_500WP20,
        .mipi_clk_rate  = R_500_549,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_500wp20
    },

    {
        .sns_fmt        = FORMAT_1080P20,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_500WP20) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_500WP20,
        .mipi_clk_rate  = R_500_549,
        .mipi_lane_num  = 4,
        .sns_attr       = &attr_4l_1080p20
    },

    {
        .sns_fmt        = FORMAT_WDR_400WP30,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP30_WDR) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_400WP30_WDR,
        .mipi_clk_rate  = R_1450_1500,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_wdr_400wp25
    },

    {
        .sns_fmt        = FORMAT_WDR_400WP25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25_WDR) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25_WDR,
        .mipi_clk_rate  = R_1450_1500,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_wdr_400wp30
    },

    {
        .sns_fmt        = FORMAT_2304X1296P25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25,
        .mipi_clk_rate  = R_1450_1500,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_2304x1296p25
    },

    {
        .sns_fmt        = FORMAT_WDR_2304X1296P25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25_WDR) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25_WDR,
        .mipi_clk_rate  = R_1450_1500,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_wdr_2304x1296p25
    },

    {
        .sns_fmt        = FORMAT_400WP20,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP20) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_400WP20,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_400wp20
    },

    {
        .sns_fmt        = FORMAT_500W12P5,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_500W12P5) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_500W12P5,
        .mipi_clk_rate  = R_900_949,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_500wp12
    },

    {
        .sns_fmt        = FORMAT_500WP25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_500WP25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_500WP25,
        .mipi_clk_rate  = R_1150_1199,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_500wp25
    },

    {
        .sns_fmt        = FORMAT_400WP30,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP30) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_400WP30,
        .mipi_clk_rate  = R_1450_1500,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_400wp30
    },

    {
        .sns_fmt        = FORMAT_400WP25,
        .conf_size      = sizeof(Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25) / 4,
        .conf_addr      = Sensor_Cfg_OVOS05_MIPI_2LANE_400WP25,
        .mipi_clk_rate  = R_1450_1500,
        .mipi_lane_num  = 2,
        .sns_attr       = &attr_2l_400wp25
    },

};

#endif /* OVOS05_MIPI_H_ */
