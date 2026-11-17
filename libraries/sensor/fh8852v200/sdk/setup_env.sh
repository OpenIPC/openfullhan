#!/bin/bash

CUR_DIR=$(pwd)

echo "export DSP_ROOT=$CUR_DIR/dsp
export ISP_ROOT=$CUR_DIR/isp
export INSTALL_DIR=$CUR_DIR/_output
export ARCH=arm
export CHIP_ID=HL
export CROSS_COMPILE=arm-fullhanv3-linux-uclibcgnueabi-
" > personal.make

