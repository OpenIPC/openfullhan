# OpenFullhan

Sensor libraries for Fullhan IP camera SoCs, built from source, laid out like
[OpenHisilicon](https://github.com/OpenIPC/openhisilicon). Used by
[OpenIPC](https://openipc.org/) firmware, which otherwise ships the SDK's
prebuilt `lib<sensor>_mipi.so` files.

## Supported hardware

| SoC family | Chips | Kernel | SDK the sources come from |
|------------|-------|--------|---------------------------|
| `fh8852v100` | FH8852, FH8856 (V100) | 3.0.8 | `FH8856_IPC_V1.2.0_20200324` |
| `fh8852v200` | FH8852V200/V210, FH8856V200/V210, FH8858V200/V210 | 4.9.129 | `FH885XV200_IPC_V1.1.0_20210716` + `FH885XV200_IPC_V1.1.0.FP13_20211202` |

The family names are OpenIPC's `OPENIPC_SOC_FAMILY`.

## Layout

```
libraries/
  include/<family>/        ISP, DSP and MIPI headers the drivers build against
  sensor/<family>/
    common/                the SDK's sensor_common (I2C, clock and register helpers)
    <vendor>_<sensor>/     one driver per directory
    sdk/                   the SDK's own sensor-build scripts, as shipped
```

## Provenance

The first commit is the sensor sources Fullhan ships in its SDKs'
`media_support/tools/sensor-build`, byte for byte; only their location
changed. Each source still carries its `BUILD VERSION: <SDK> @ <hash>` line.
The FH885xV200 base release ships the headers and build scripts, and its FP13
patch the `isp/libs/sensor` tree, so `fh8852v200` is the base with FP13 over
it, as the SDK intends.

| SDK path (under `media_support/tools/sensor-build/`) | Here (under `libraries/`) |
|---|---|
| `isp/include/*`, `dsp/include/*` | `include/<family>/` |
| `dsp/drivers/fh_std/include/*` (V200) | `include/fh8852v200/fh_std/` |
| `isp/drivers/include/version.h` | `include/<family>/version.h` |
| `isp/libs/mipi/mipi_ctrl.h` | `include/<family>/mipi/mipi_ctrl.h` |
| `isp/libs/sensor/{Makefile,Sensor.make,*.py}` | `sensor/<family>/` |
| `isp/libs/sensor/sensor_common/` | `sensor/<family>/common/` |
| `isp/libs/sensor/jxf22_mipi/` | `sensor/<family>/soi_jxf22/` |
| `isp/libs/sensor/ovos05_mipi/` | `sensor/<family>/omnivision_os05a/` |
| `README.txt`, `build.sh`, `setup_env.sh`, `isp/{Makefile,Rules.mk}` | `sensor/<family>/sdk/` |

The SDKs ship sensor sources for these two sensors only. Every other sensor
library in them is a prebuilt `.so`; drivers for other sensors are added here
as source.

## Sensors written here

| Family | Directory | Sensor | Sources of its register values |
|---|---|---|---|
| `fh8852v100` | `galaxycore_gc4653` | GalaxyCore GC4653, 2560x1440 at 15-30 fps, MIPI 2-lane RAW10 | GalaxyCore's datasheet (V1.0), and for the PLL/analog start-up and gain steps the datasheet omits, [sophgo/SensorSupportList](https://github.com/sophgo/SensorSupportList) (BSD-2-Clause, notice kept in `gc4653_mipi.h`) |

Its ISP defaults are the SDK's JX-F22 tables and its `.hex` tuning the SDK's
GC4633 files until the sensor is tuned on a camera, with one byte changed:
offset `0x6e` is `0x00`, not GC4633's `0x02`. Bit 1 there tells `libispcore`
that the sensor applies white balance itself, through the driver's
`get_awb_gain`. The GC4653 driver does not, so the ISP is left with zero
gains and the white-balance loop divides by one (SIGFPE in `SetWbGain`).
Every other 2560x1440 tuning in the SDK (GC4623, OS05A) has `0x00` there.

## Building

Each sensor directory has a self-contained `Makefile`; pass the toolchain:

```sh
make -C libraries/sensor/fh8852v100/galaxycore_gc4653 CC=arm-openipc-linux-musleabi-gcc
```

## Licence

GPL-3.0 (`LICENSE`) for the code written here. The SDK files keep their
origin (see Provenance); the GC4653 register tables carry Sophgo's BSD-2-Clause
notice.
