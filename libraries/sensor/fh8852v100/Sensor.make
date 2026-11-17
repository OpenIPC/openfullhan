INSTALL_DIR ?= /home/nfs/opt/test
DSP_ROOT ?= $(HOME)/work/dsp
ISP_ROOT ?= $(HOME)/work/isp
LIBPATH=./

SENSOR_NAME?=$(shell pwd | sed 's/^\(.*\)[/]//')

LINUX_TARGET = $(LIBPATH)/lib$(SENSOR_NAME).a
RTT_TARGET = $(LIBPATH)/lib$(SENSOR_NAME)_rtt.a
CSRC= $(wildcard *.c)
TEMSRC= $(wildcard *.hex)
TEMSRC := $(patsubst %.hex,%.c,$(TEMSRC))
CSRC+=../sensor_common/sensor_ops.c
CSRC+=../sensor_common/sensor_api.c
CSRC+=../sensor_common/clock_ops.c
EXTRA_CFLAGS += -Wall -Werror -DISP -DARMLIB
EXTRA_CFLAGS += -I$(ISP_ROOT)/include/isp \
		-I$(ISP_ROOT)/include/isp_ext \
		-I$(ISP_ROOT)/drivers/include \
		-I$(DSP_ROOT)/include \
		-I$(DSP_ROOT)/libs/vmm \
		-I$(ISP_ROOT)/libisp/include/isp_core \
		-I$(ISP_ROOT)/libs/sensor/sensor_common \
		-I$(ISP_ROOT)/libs/mipi/
RTT_EXTRA_CFLAGS += \
                -I$(RTT_ROOT)/include \
		-I$(ISP_ROOT) \
		-I$(RTT_ROOT)/components/drivers/include/ \
		-I$(RTT_ROOT)/components/pthreads \
		-I$(RTT_ROOT)/components/finsh/ \
		-I$(RTT_ROOT)/../platform/startup/gcc


#INC_DIR = -I$(ISP_ROOT)/include/isp  -I$(ISP_ROOT)/include/isp/isp_core

obj-m = $(patsubst %.ko,%.o,$(LINUX_TARGET))
#obj-m += ../sensor_common/sensor_ops.o
$(patsubst %.ko,%,$(LINUX_TARGET))-y = $(patsubst %.c,%.o,$(CSRC))
-include ../../../Rules.mk

ifeq ($(MS),1)
EXTRA_CFLAGS += -DMULTI_SENSOR=1
endif

ifeq ($(STATIC),0)
LINUX_TARGET_CP =$(basename $(LINUX_TARGET)).so
RTT_TARGET_CP = $(basename $(RTT_TARGET)).so
else
LINUX_TARGET_CP =$(basename $(LINUX_TARGET)).a
RTT_TARGET_CP = $(basename $(RTT_TARGET)).a
endif

ifeq ($(RTT),1)
install:
	@if [ ! -d "$(RTT_INSTALL_DIR)/sensors" ]; then mkdir $(RTT_INSTALL_DIR)/sensors; fi
ifeq ($(MS),1)
	@if [ ! -d "$(RTT_INSTALL_DIR)/sensors/multiple" ]; then mkdir $(RTT_INSTALL_DIR)/sensors/multiple; fi
	-cp -rf $(RTT_TARGET_CP) $(RTT_INSTALL_DIR)/sensors/multiple
else
	-cp -rf $(RTT_TARGET_CP) $(RTT_INSTALL_DIR)/sensors
endif
else
install:
	-cp -rf $(LINUX_TARGET_CP) $(INSTALL_DIR)/
endif



	
ifneq "$(MAKECMDGOALS)" "clean"
  -include $(DEPENDS)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

.PHONY: build-headfile

prebuild-paraFile:
	mkdir -p parameters
	python3 ../prebuildHeadFile.py $(SENSOR_NAME)
	mv sensorParam* parameters

build-paraFile: $(TEMSRC)
%.c: %.hex
	mkdir -p parameters
	python3 ../hex2headfile.py $^ $@
	mv sensorParam* parameters


.PHONY: delete-headfile

delete-paraFile:
	rm -rf parameters