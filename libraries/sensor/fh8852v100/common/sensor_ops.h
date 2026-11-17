/* BUILD VERSION: FH8856_IPC_V1.2.0_20200324 @ aee6fa1 */
/*
 * sensor_ops.h
 *
 *  Created on: Jun 2, 2015
 *      Author: duobao
 */

#ifndef SENSOR_OPS_H_
#define SENSOR_OPS_H_

#include "types/type_def.h"
#include "fh_defs.h"
#ifdef OS_LINUX
#define I2C_DEVICE		"/dev/i2c-0"
#define SPI_DEVICE		"/dev/spi1"
#endif


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
