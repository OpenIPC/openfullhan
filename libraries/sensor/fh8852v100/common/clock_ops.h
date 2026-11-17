/* BUILD VERSION: FH8856_IPC_V1.2.0_20200324 @ aee6fa1 */
#ifndef __CLOCK_OPS_H
#define __CLOCK_OPS_H

#ifdef OS_LINUX
#include <sys/ioctl.h>
#else
#ifndef USE_RTT3_0
#define _IOWR(io_magic, cmd_id, stru) (cmd_id)
#endif
#endif

#define CLK_IOCTL_MAGIC 		'c'
#define ENABLE_CLK	 		_IOWR(CLK_IOCTL_MAGIC, 0, unsigned int)
#define DISABLE_CLK		 	_IOWR(CLK_IOCTL_MAGIC, 1, unsigned int)
#define SET_CLK_RATE			_IOWR(CLK_IOCTL_MAGIC, 2, unsigned int)
#define GET_CLK_RATE			_IOWR(CLK_IOCTL_MAGIC, 3, unsigned int)
#define SET_PMU				_IOWR(CLK_IOCTL_MAGIC, 4, unsigned int)
#define GET_PMU				_IOWR(CLK_IOCTL_MAGIC, 5, unsigned int)

#define CLK_IOCTL_MAXNR 		8
struct clk_usr
{
	char			*name;
	unsigned long       	frequency;
};

int set_clk_rate(int clock_type,unsigned long rate);
int set_clk_enable(int clock_type, int enable);

enum CLK_TYPE
{
	isp_clk=0,
	cis_clk=1,
};

enum CLK_RATE
{
	CLK_12M = 12000000,
	CLK_18M = 18000000,
	CLK_20M = 20000000,
	CLK_22M5 = 22500000,
	CLK_27M = 27000000,
	CLK_30M = 30000000,
	CLK_36M = 36000000,
	CLK_45M = 45000000,
	CLK_96M = 96000000,
	CLK_120M =120000000,
	CLK_160M= 160000000,
};

#endif
