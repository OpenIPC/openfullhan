-include ../personal.make

export FHBUILD_TOPDIR ?= /home/duobao/work

export RTT_ROOT ?= /home/duobao/fh6x_rtt/fh86xx-sdk/rt-thread
export DSP_ROOT ?= $(FHBUILD_TOPDIR)/dsp
export ISP_ROOT ?= $(FHBUILD_TOPDIR)/isp
export LINUX_ROOT ?= $(FHBUILD_TOPDIR)/kernel
export LINUX_INSTALL_DIR ?= $(FHBUILD_TOPDIR)/fh81_release/target/isp
export LINUXKERNEL_INSTALL_DIR ?= $(LINUX_ROOT)
export CROSS_COMPILE ?= arm-fullhan-linux-uclibcgnueabi-
export CC_PREFIX := $(CROSS_COMPILE)
export TOP_DRIVER_DIR := $(ISP_ROOT)/drivers
export LINUX_CROSS_COMPILE ?= $(CROSS_COMPILE)

export RTT_MASTER ?= $(FHBUILD_TOPDIR)/RT-Thread-fh-master/fh-master
export RTT_CROSS_COMPILE ?= arm-none-eabi-
export RTT_ROOT?=/home/duobao/fh6x_rtt/fh86xx-sdk/rt-thread
export RTT_INSTALL_DIR ?=~/fh6x_rtt/fh86xx-sdk/extlib
export RTT ?= 0
export STATIC ?= 1
export DEBUG ?= 0
export CHIP_ID ?= ZY


OBJFILES := $(patsubst %.c,%.o,$(CSRC))


#############for RTT############################################
ifeq ($(RTT),1)
CC = $(RTT_CROSS_COMPILE)gcc
AR = $(RTT_CROSS_COMPILE)ar
EXTRA_CFLAGS+=$(RTT_EXTRA_CFLAGS)
EXTRA_CFLAGS+=-DOS_RTT
EXTRA_CFLAGS+=-D${CHIP_ID}

ifeq ($(ARCH),arm)
CFLAGS+=-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=soft -mno-unaligned-access
else # ($(ARCH),arc)
CFLAGS+= -mno-sdata -mmac-24 -mA6
endif

ifeq ($(DEBUG),1)
CFLAGS += -O0 -gdwarf-2 -DRT_USING_NEWLIB
else
CFLAGS += -O2
endif

CFLAGS+=$(EXTRA_CFLAGS)

CFLAGS += -I$(RTT_ROOT)/

CFLAGS += -I$(RTT_ROOT)/include
CFLAGS += -I$(RTT_ROOT)/libcpu/arm/armv6
CFLAGS += -I$(RTT_ROOT)/libcpu/arm/common
CFLAGS += -I$(RTT_ROOT)/components/dfs
CFLAGS += -I$(RTT_ROOT)/components/dfs/include
CFLAGS += -I$(RTT_ROOT)/components/dfs/filesystems/devfs
CFLAGS += -I$(RTT_ROOT)/components/drivers/include
CFLAGS += -I$(RTT_ROOT)/components/drivers/spi
CFLAGS += -I$(RTT_ROOT)/components/finsh
CFLAGS += -I$(RTT_ROOT)/components/libc/newlib
CFLAGS += -I$(RTT_ROOT)/components/libdl
CFLAGS += -I$(RTT_ROOT)/components/libc/pthreads
CFLAGS += -I$(RTT_ROOT)/../


$(RTT_TARGET): $(OBJFILES)
	$(AR) -rcsD $@ $^

else
#############for LINUX############################################
CC = $(LINUX_CROSS_COMPILE)gcc
AR = $(LINUX_CROSS_COMPILE)ar
EXTRA_CFLAGS+=$(LINUX_EXTRA_CFLAGS)
EXTRA_CFLAGS+=-DOS_LINUX
CFLAGS += -fPIC
EXTRA_CFLAGS+=-D${CHIP_ID}
CFLAGS += -fPIC
ifeq ($(DEBUG),1)
EXTRA_CFLAGS+=-g
else
EXTRA_CFLAGS+=-O2
endif

ifeq ($(suffix $(LINUX_TARGET)), .ko) #####build .ko
$(LINUX_TARGET):
	make -C $(LINUX_ROOT) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" M=`pwd` modules
else

CFLAGS += $(EXTRA_CFLAGS)

ifneq (, $(filter %.so %.a, $(LINUX_TARGET)))
ifeq ($(STATIC), 1)
$(LINUX_TARGET): $(OBJFILES)
	$(AR) -rcsD $(basename $(LINUX_TARGET)).a $^
else
CFLAGS+=-fPIC
$(LINUX_TARGET): $(OBJFILES)
	$(CC) -shared -fPIC -o $(basename $(LINUX_TARGET)).so $^ $(LDFLAGS) $(EXTRA_LDFLAGS)
endif
else
$(LINUX_TARGET): $(OBJFILES)
	$(CC) $(LDFLAGS) $(EXTRA_LDFLAGS) $^ -o $@
endif  ##end .so | .a
endif  ##end .ko
endif  ##end RTT
#############the END ############################################


clean:
	-rm -f $(OBJFILES)
	-rm -f $(RTT_TARGET)
	find $(PWD) -name "*.o" | xargs rm -f
ifeq (, $(filter %.so %.a, $(LINUX_TARGET)))
	-rm -f $(LINUX_TARGET)
else
	-rm -f $(basename $(LINUX_TARGET)).a
	-rm -f $(basename $(LINUX_TARGET)).so
endif
