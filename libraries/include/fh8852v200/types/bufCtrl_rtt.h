#ifndef _BUFCTRL_H_
#define _BUFCTRL_H_
#include "dsp/fh_common.h"

typedef struct fhMEM_DESC_
{
	unsigned int base;
	void        *vbase;
	unsigned int size;
	unsigned int align;
}MEM_DESC;

#define   mem_desc   fhMEM_DESC_

typedef unsigned int cmm_handle;

/**alloc vmm useby harware*/
int bufferInit(unsigned char* pAddr, unsigned int bufSize);
int buffer_malloc(MEM_DESC *mem, int size, int align);
int buffer_malloc_withname(MEM_DESC *mem, int size, int align,  char* name);
int buffer_malloc_withname_cached(MEM_DESC *mem, int size, int align,const char* name);

/** alloc cached none buffered(CNB) memory management used by dma  */
cmm_handle cmm_init(unsigned char* pAddr, unsigned int bufSize);
int cmm_malloc(cmm_handle handle, MEM_DESC *mem, int size, int align,  char* name);
int cmm_free(cmm_handle handle);

/** RTT下功能未实现，临时define下*/
#define buffer_malloc_withname_cached buffer_malloc_withname
#endif
