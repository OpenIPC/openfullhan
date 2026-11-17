# sensor库编译环境

## 编译方法
1. export SDK_DIR=sdk的绝对路径
2. export PATH=编译器文件夹/bin:$PATH
   - cd $SDK_DIR/docs_tools/software/pc
   - tar xf 编译器压缩包
      - 可能是 gcc-arm-fullhan-eabi-6-2017-q2-update.tar.bz2 (V2.x.x 以后的版本)
      - 可能是 arm-2013.11-24-arm-none-eabi-i686-pc-linux-gnu.tar.bz2 (V1.3.1 及以前的版本)
   - export PATH=$(pwd)/上一步解压出的文件夹名/bin:$PATH

3. 运行 ./setup_env.sh 生成 personal.make
4. 运行 build.sh 进行编译:

        ./build.sh

5. 编译好的sensor库放在 _output 文件夹中

## 接入方法
当我们准备接入一个新的sensor时，首先需要一份sensor出图的寄存器配置，
我们需要知道这份配置的帧框架(frame W/H)，有效幅面(active W/H)，mclock，
如果是MIPI接口还需要知道当前配置是几lane

依据配置文件中的 frame/active 数据，定义好头文件中的FRAM_W、FRAM_H、ACTIVE_W、ACTIVE_H等值。
如有多个配置文件，请依据不同的输出定义不同的格式宏(参考isp\libs\sensor\jxf22\jxf22.h)

头文件配置好后实现接口函数，首先实现的几个接口函数: (参考isp\libs\sensor\jxf22\jxf22.c)
- 初始化(Sensor_Init)：打开i2c设备，MIPI接口需要配置好MIPI参数
- 格式设置(SetSensorFmt):根据不同的格式，配置不同的sensor寄存器参数，
- sensor接口(GetViMode): 1:DVP, 5:MIPI，告诉ISP当前的sensor接口类型
- 幅面信息(GetSensorViAttr):配置好每个幅面的信息

实现上面4个接口后，调用isp的接口，sensor就可以有图像出来了，后面再根据datasheet上面的描述，
实现增益、曝光、翻转等接口，用于ISP的策略控制，完成接口。

## 注意事项
1. DVP和MIPI接口VIMODE的值不同
  - DVP: 1
  - MIPI: 5
2. MULTI_SENSOR宏是用于多sensor，定义该宏，需要实现Sensor_Isconnect，用于多sensor的检测
3. 当图像颜色完全偏色的时候，注意bayer格式是否设置正确， 在GetSensorViAttr->enBayerType中设置
4. MIPI接口sensor在初始化时需要对MIPI做相关配置，参考MIPI的示例
5. gain设置是U10.6精度，曝光intt是U10.4精度
