#!/bin/bash

CUR_DIR=$(pwd)

echo "export DSP_ROOT=$CUR_DIR/dsp
export ISP_ROOT=$CUR_DIR/isp
export INSTALL_DIR=$CUR_DIR/_output
export ARCH=arm
export CHIP_ID=ZY
export CROSS_COMPILE=arm-fullhanv2-linux-uclibcgnueabi-
" > personal.make

