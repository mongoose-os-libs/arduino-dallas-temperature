#include <stdbool.h>

#include <mgos_config.h>

#include <mgos_arduino_dallas_temp.h>

static DallasTemperature *s_global_mgos_ds18x = NULL;
DallasTemperature *mgos_ds18x_get_global() {
  return s_global_mgos_ds18x;
}

bool mgos_arduino_dallas_temperature_init(void) {
  int pin = mgos_sys_config_get_ds18x_pin();
  if (pin < 0) return true;
  s_global_mgos_ds18x = mgos_arduino_dt_create(mgos_arduino_onewire_create(pin));
  mgos_arduino_dt_begin(s_global_mgos_ds18x);
  return true;
}
