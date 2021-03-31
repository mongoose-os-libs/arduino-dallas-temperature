#include <stdbool.h>

#include <mgos_config.h>
#include <mgos_system.h>

#include <mgos_arduino_dallas_temp.h>

static struct mgos_rlock_type *lock = NULL;
static DallasTemperature *s_global_mgos_ds18x = NULL;

DallasTemperature *mgos_ds18x_get_global() {
  return s_global_mgos_ds18x;
}

DallasTemperature *mgos_ds18x_get_global_locked() {
  if (s_global_mgos_ds18x) mgos_rlock(lock);
  return s_global_mgos_ds18x;
}

void mgos_ds18x_put_global_locked() {
  if (s_global_mgos_ds18x) mgos_runlock(lock);
}

bool mgos_arduino_dallas_temperature_init(void) {
  int pin = mgos_sys_config_get_ds18x_pin();
  if (pin < 0) return true;
  lock = mgos_rlock_create();
  s_global_mgos_ds18x = mgos_arduino_dt_create(mgos_arduino_onewire_create(pin));
  mgos_arduino_dt_begin(s_global_mgos_ds18x);
  return true;
}
