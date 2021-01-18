#include <stdbool.h>

#include <mgos_config.h>

#include <mgos_arduino_dallas_temp.h>

DallasTemperature *mgos_ds18x = NULL;

bool mgos_arduino_dallas_temperature_init(void) {
  if (!mgos_sys_config_get_ds18x_enable()) return true;
  mgos_ds18x = mgos_arduino_dt_create(
      mgos_arduino_onewire_create(mgos_sys_config_get_ds18x_pin()));
  mgos_arduino_dt_begin(mgos_ds18x);
  return true;
}
