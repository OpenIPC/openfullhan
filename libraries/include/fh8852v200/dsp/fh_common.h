#ifndef __FH_COMMON_H__
#define __FH_COMMON_H__
#include "types/type_def.h"
/**|System Control|**/

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#pragma pack(4)

// #define API_PRT
#ifdef API_PRT
#define API_DEBUG(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#define API_NOTICE(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#else
#define API_DEBUG(...)
#define API_NOTICE(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#endif

/*此错误号无效，已经弃用*/
#define RETURN_NULL                         (0)
#define RETURN_OK                           (0)
#define NO_DEVICE                           (-1001)
#define OPEN_DEVICE_ERR                     (-1001)
#define CLOSE_DEVICE_ERR                    (-1002)
#define FIND_DEVICE_ERR                     (-1003)
#define PARAM_NULL                          (-1004)
#define PARAM_ERR                           (-1005)
#define ALIGN_ERR                           (-1006)
#define MODULE_ENABLE_ERR                   (-1007)
#define CHAN_ERR                            (-1008)
#define MEM_NULL                            (-1009)
#define GET_STREAM_EMPTY                    (-1010)
#define HAS_CREATED                         (-1011)
#define SDK_ERR                             (-1012)
#define NOT_SUPPORT                         (-1013)
#define NOT_READY                           (-1014)
#define NOT_INIT                            (-1015)

#define MAX_OSD_LINE                         (8)
#define MAX_INVERT_CNT                       (8)
#define MAX_MASK_AREA                        (8)
#define MAX_GBOX_AREA                        (16)
#define DEFALT_ALIGN                         (8)
#define MAX_VPU_CHANNO                       (4)
#define MAX_ENC_CHANNO                       (8)

#define MALLOCED_MEM_BASE_DSP                (1)
#define MALLOCED_MEM_VPUPKG                  (0)

/*芯片名称,0代表未知芯片*/
#define FH8632                               (0x863200A1)
#define FH8632v2                             (0x863200A2)
#define FH8620H                              (0x863200B1)
#define FH8856                               (0x885600A1)
#define FH8852                               (0x885600B1)
#define FH8626V100                           (0x8626A100)
#define FH8852V200                           (0x8852A200)
#define FH8856V200                           (0x8856A200)
#define FH8858V200                           (0x8858A200)
#define FH8652                               (0x8652A100)
#define FH8656                               (0x8656A100)
#define FH8658                               (0x8658A100)

typedef enum
{
	FH_RO_OPS_0     = 0,//旋转0度 | [ ]
	FH_RO_OPS_90    = 1,//旋转90度 | [ ]
	FH_RO_OPS_180   = 2,//旋转180度 | [ ]
	FH_RO_OPS_270   = 3,//旋转270度 | [ ]
	FH_ROTATE_OPS_DUMMY= 0xffffffff,
}FH_ROTATE_OPS;

typedef enum
{
	VPU_VOMODE_BLK          = 0, // 宏块格式 | [ ]
	VPU_VOMODE_SCAN         = 1, // 光栅格式(NV12) | [ ]
	VPU_VOMODE_TILE192      = 2, // Tile压缩192Byte | [ ]
	VPU_VOMODE_TILE224      = 3, // Tile压缩224Byte | [ ]
	VPU_VOMODE_TILE256      = 4, // Tile压缩256Byte | [ ]
	VPU_VOMODE_RGB888       = 5, // RGB888 | [ ]
	VPU_VOMODE_YUYV         = 6, // YUYV(YUV2) | [ ]
	VPU_VOMODE_BUTT            ,
	FH_VPU_VO_MODE_DUMMY    = 0xffffffff,
}FH_VPU_VO_MODE;

typedef struct fhVERSION_INFO_
{
	FH_UINT32           build_date;  // 编译时间  | [ ]
	FH_UINT32           sw_version;  // 软件版本号  | [ ]
	FH_UINT32           hw_version;  // 硬件驱动版本号  | [ ]
}FH_VERSION_INFO;

typedef struct fhPOINT_
{
	FH_UINT32           u32X;        // 水平坐标 | [ ]
	FH_UINT32           u32Y;        // 垂直坐标 | [ ]
}FH_POINT;

typedef struct fhSIZE_S
{
	FH_UINT32           u32Width;    // 宽度 | [ ]
	FH_UINT32           u32Height;   // 高度 | [ ]
} FH_SIZE;

typedef struct fhRECT_S
{
	FH_UINT32           u32X;        // 起始点水平坐标 | [ ]
	FH_UINT32           u32Y;        // 起始点垂直坐标 | [ ]
	FH_UINT32           u32Width;    // 区域宽度 | [ ]
	FH_UINT32           u32Height;   // 区域高度 | [ ]
}FH_AREA;

typedef struct
{
	FH_ADDR             addr;        // 虚拟地址 | [ ]
	FH_UINT32           size;        // 内存大小 | [ ]
}FH_ADDR_INFO;

typedef struct
{
	FH_UINT32           base;        // 物理地址 | [ ]
	FH_VOID *           vbase;       // 虚拟地址 | [ ]
	FH_UINT32           size;        // 内存大小 | [ ]
}FH_MEM_INFO;

typedef struct
{
	FH_UINT16           frame_count; // 帧数 | [ ]
	FH_UINT16           frame_time;  // 统计时间(s) | [ ]
} FH_FRAMERATE;

typedef struct
{
	FH_UINT32           y;           // 亮度 | [ ]
	FH_UINT32           cb;          // 蓝色浓度偏移量 | [ ]
	FH_UINT32           cr;          // 红色浓度偏移量 | [ ]
	FH_UINT32           alpha;       // 透明度 | [ ]
} FH_YC_COLOR;

typedef struct
{
	FH_UINT32 avgTime;
	FH_UINT32 maxTime;
	FH_UINT32 avgCycle;
	FH_UINT32 maxCycle;
	FH_UINT32 win_size;
	FH_UINT64 time_stamp;
}FH_HW_AVG_TIME;
#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _FH_COMMON_H_ */
