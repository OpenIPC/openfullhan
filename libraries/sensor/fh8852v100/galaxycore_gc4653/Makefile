# SPDX-License-Identifier: GPL-3.0-only
#
# lib$(SENSOR).so for the FH885x V100 ISP. CC comes from the caller (the
# OpenIPC toolchain); the headers are the SDK's, in libraries/include.

SENSOR  := gc4653_mipi
FAMILY  := fh8852v100
INC     := ../../../include/$(FAMILY)
COMMON  := ../common

CFLAGS  += -O2 -fPIC -Wall -Werror -DISP -DARMLIB -DOS_LINUX \
	   -I$(INC) -I$(INC)/isp -I$(INC)/isp_ext -I$(INC)/mipi -I$(COMMON)
LDFLAGS += -shared -Wl,-soname,lib$(SENSOR).so

SRCS    := gc4653_mipi.c gc4653_mipi_param.c \
	   $(COMMON)/sensor_ops.c $(COMMON)/sensor_api.c $(COMMON)/clock_ops.c

all: lib$(SENSOR).so

lib$(SENSOR).so: $(SRCS) gc4653_mipi.h
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $@

clean:
	rm -f lib$(SENSOR).so

.PHONY: all clean
