/* BUILD VERSION: FH8856_IPC_V1.2.0_20200324 @ cd1ec21 */
#ifndef _API_COMMON_H_
#define _API_COMMON_H_

#include <stdio.h>
#include <string.h>

#ifdef OS_RTT
#include <rtthread.h>
#include <rtdevice.h>
//#include <posix_types.h>
#include <pthread.h>
#include "bufCtrl_rtt.h"

#define fh_printf    rt_kprintf
#define fh_sprintf   rt_sprintf
#define fh_memcpy    rt_memcpy
#define fh_memset    rt_memset
#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

//device
#define SYS_NAME    "media"
#define VPU_NAME    "vpu"
#define PAE_NAME    "enc"
#define JPEG_NAME   "jpeg"
#define BGM_NAME    "bgm"
#define HEVC_NAME   "hevc"
#define AUDIO_NAME  "fh_audio"

typedef rt_device_t DEV_FD;
#define dev_exist(name)         (rt_device_find(name) != 0)
#define dev_ioctl(dev,cmd,data) \
({ \
	int _ret;\
	_ret = rt_device_control(dev,cmd,data);\
	if(_ret < 0)\
		rt_set_errno(_ret);\
	_ret;\
})
#define dev_open(name,p1,p2)\
({\
	int _ret;\
	DEV_FD _dev;\
	_dev = rt_device_find(name);\
	if(_dev != RT_NULL)\
	{\
		_ret = rt_device_open(_dev,RT_DEVICE_OFLAG_RDWR);\
		if(_ret != 0)\
			_dev = RT_NULL;\
	}\
	_dev;\
})
#define dev_close(dev)          rt_device_close(dev)
#define dev_islegal(dev)        (dev != RT_NULL)

#define ERRNO  ({int _errno=rt_get_errno(); _errno?_errno:errs;})

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* OS_RTT */

#ifdef OS_LINUX
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "bufCtrl.h"
#include "type_def.h"

#define fh_printf    printf
#define fh_sprintf   sprintf
#define fh_memcpy    memcpy
#define fh_memset    memset
#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define SYS_NAME    "/dev/media_process"
#define VPU_NAME    "/dev/vpu"
#define PAE_NAME    "/dev/pae"
#define JPEG_NAME   "/dev/jpeg"
#define BGM_NAME    "/dev/bgm"
#define HEVC_NAME   "/dev/hevc"
#define AUDIO_NAME  "/dev/fh_audio"

typedef FH_SINT32 DEV_FD;
#define dev_exist(name)         (access(name,F_OK) == 0)
#define dev_ioctl(dev,cmd,data) ioctl(dev,cmd,data)
#define dev_open(name,p1,p2)    open(name,p1,p2)
#define dev_close(dev)          close(dev)
#define dev_islegal(dev)        (dev >= 0)

#define ERRNO  ({int _errno=errno; _errno?_errno:errs;})

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* OS_LINUX */

#endif

