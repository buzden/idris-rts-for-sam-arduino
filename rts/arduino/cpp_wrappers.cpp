#include "cpp_wrappers.h"

#include "Arduino.h"

#define define_serial_fun(return_type, name, params, call) \
  return_type name##_unready params { \
    Serial.begin(SERIAL_CONFIGURATION); \
    return_type res = name call; \
    Serial.end(); \
    return res; \
  } \
  return_type name params

extern "C" {

define_serial_fun(size_t, serial_print_str, (const char *str), (str)) {
  return Serial.print(str);
}

define_serial_fun(size_t, serial_println_str, (const char *str), (str)) {
  return Serial.println(str);
}

define_serial_fun(size_t, serial_println, (void), ()) {
  return Serial.println();
}

void serial_flush() {
  Serial.flush();
}

} // for `extern "C"`
