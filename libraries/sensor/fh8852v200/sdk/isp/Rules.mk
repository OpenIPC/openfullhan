-include ../personal.make

export ARCH ?= arm
export RTT_ROOT ?= /home/duobao/fh6x_rtt/fh86xx-sdk/rt-thread
export DSP_ROOT ?= $(FHBUILD_TOPDIR)/dsp
export ISP_ROOT ?= $(FHBUILD_TOPDIR)/isp
export BSP_ROOT ?= $(FHBUILD_TOPDIR)/ipcsdk/bsp
export TOP_DRIVER_DIR := $(ISP_ROOT)/drivers
export INSTALL_DIR ?= /home/nfs/opt/test
export LINUX_ROOT ?= $(FHBUILD_TOPDIR)/kernel
export CROSS_COMPILE ?= arm-fullhanv2-linux-uclibcgnueabi-
export VBUSKO_PATH ?= drivers/vbus

export RTT_ROOT ?= $(FHBUILD_TOPDIR)/fh6x_rtt/fh86xx-sdk/rt-thread
export ARC_RTT_ROOT ?= $(RTT_ROOT)
export RTT_CROSS_COMPILE ?= arm-fullhanv2-eabi-
export RTT_ARC_CROSS_COMPILE ?=arc-fullhan-elf32-
export RTT_INSTALL_DIR ?= $(INSTALL_DIR)
export RTT_ARC_INSTALL_DIR ?= $(INSTALL_DIR)

export RTT ?= 0
export VFP ?= 0
export STATIC ?= 1
export DEBUG ?= 0
export CHIP_ID ?= ZY
export BUILD_MODE ?= 0
export FPGA_ENV ?= 0
export MEDIA_TRACE ?= 2
export CB ?= 0
export EMU ?= 0
export AUTOTEST ?= 0
export RTOSV3 ?= 1

ifeq ($(CB),1)
EXTRA_CFLAGS+=-DISP_COLORBAR
endif

ifeq ($(RTT),1)
export BUILD_MODE=1
endif

ifeq ($(EMU),1)
EXTRA_CFLAGS+=-DEMU
endif

ifeq ($(AUTOTEST),1)
EXTRA_CFLAGS+=-DAUTOTEST
endif

ifeq ($(FPGA_ENV),1)
EXTRA_CFLAGS+=-DFPGA_ENV
endif

ifeq ($(MEDIA_TRACE),0)
EXTRA_CFLAGS+=-DFH_TRACE_MINI
else ifeq ($(MEDIA_TRACE),2)
EXTRA_CFLAGS+=-DFH_TRACE_DEBUG
endif
ifeq ($(RTOSV3),1)
EXTRA_CFLAGS+=-DRTOSV3
endif

EXT_COPY += $(TARGET_BIN)

-include $(ISP_ROOT)/Rules_linux.mk
-include $(ISP_ROOT)/Rules_rtt.mk

install:
ifneq ($(EXT_COPY),)
	$(Q)echo copy $(notdir $(EXT_COPY)) to $(EXT_INSTALL_DIR)
	cp -f $(EXT_COPY) $(EXT_INSTALL_DIR)/
endif

clean:
	$(Q)-rm -rf $(BUILD_FOLDER)
	$(Q)-rm -f $(OBJFILES)
	$(Q)find . -name "*.cmd" | xargs rm -f
	$(Q)-rm -f *.ko *.o *.a *.so src/*.o
	$(Q)-rm -f *.cmd .*.cmd .*.mod.c *.mod.o
	$(Q)-rm -f *.mod.c modules.order Module.symvers
	$(Q)-rm -rf .tmp_versions