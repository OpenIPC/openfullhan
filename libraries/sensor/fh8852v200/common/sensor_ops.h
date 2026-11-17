/*
 * sensor_ops.h
 *
 *  Created on: Jun 2, 2015
 *      Author: duobao
 */

#ifndef SENSOR_OPS_H_
#define SENSOR_OPS_H_

#include "types/type_def.h"
#ifdef OS_LINUX
#include <stdio.h>
#define I2C_DEVICE		"/dev/i2c-0"
#define SPI_DEVICE		"/dev/spi1"
typedef int SEN_DEV_FD;
#define fh_printf printf
#define sensor_dev_ioctl ioctl
#define sensor_dev_open open
#else
#include <rtthread.h>
#define fh_printf rt_kprintf
typedef rt_device_t SEN_DEV_FD;
#define sensor_dev_ioctl(dev,cmd,data) \
({ \
	int _ret;\
	_ret = rt_device_control(dev,cmd,data);\
	if(_ret < 0)\
		rt_set_errno(_ret);\
	_ret;\
})
#define sensor_dev_open(name,p1,p2)\
({\
	int _ret;\
	SEN_DEV_FD _dev;\
	_dev = rt_device_find(name);\
	if(_dev != RT_NULL)\
	{\
		_ret = rt_device_open(_dev,RT_DEVICE_OFLAG_RDWR);\
		if(_ret != 0)\
			_dev = RT_NULL;\
	}\
	_dev;\
})
#endif
#ifdef RPC_RTT
#define _IOC(a,b,c,d) ( ((a)<<30) | ((b)<<8) | (c) | ((d)<<16) )
#define _IOC_NONE  0U
#define _IOC_WRITE 1U
#define _IOC_READ  2U
#define _IO(a,b)    _IOC(_IOC_NONE,(a),(b),0)
#define _IOW(a,b,c) _IOC(_IOC_WRITE,(a),(b),sizeof(c))
#define _IOR(a,b,c) _IOC(_IOC_READ,(a),(b),sizeof(c))
#define _IOWR(a,b,c) _IOC(_IOC_READ|_IOC_WRITE,(a),(b),sizeof(c))
#endif


#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define CLIP(x,min,max) MAX((min),MIN((x),(max)))
#define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct SensorDevice
{
	char *dev;
	int fd;
	FH_UINT8 mode;
	FH_UINT16 i2c_devid;
#ifndef OS_LINUX
	struct rt_i2c_bus_device *fh81_i2c;
#endif

}SensorDevice;
void fh_delay_200us();
void fh_delay_1ms();
int SensorDevice_Init(FH_UINT16 i2c_devid, FH_UINT8 mode);
FH_UINT16 Sensor_Read(FH_UINT16 addr);
void Sensor_Write(FH_UINT16 addr, FH_UINT16 data);
void Sensor_WriteEx(FH_UINT16 addr, FH_UINT16 data, int no_ack);
void Sensor_Write_Multi(FH_UINT16* addr, FH_UINT16* data,FH_UINT16 size);
int SensorDevice_Close(void);

#endif /* SENSOR_OPS_H_ */
