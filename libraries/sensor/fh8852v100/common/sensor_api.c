/* BUILD VERSION: FH8856_IPC_V1.2.0_20200324 @ aee6fa1 */
#include "sensor_api.h"
extern char *get_sensor_version(unsigned int print_enable);
char *FH_SENSOR_Version(unsigned int print_enable)
{
	return get_sensor_version(print_enable);
}
