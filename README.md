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
