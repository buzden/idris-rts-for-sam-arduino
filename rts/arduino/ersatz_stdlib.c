#include <stdlib.h>

#include "Arduino.h"
#include "idris_rts.h"
#include "cpp_wrappers.h"

//////////////////////
/// System exiting ///
//////////////////////

#define BUILTIN_LED 13

#define MAX_SHOWN_EXITCODE ERR_THE_LAST

static void blinkBuiltin(int t) {
  digitalWrite(BUILTIN_LED, HIGH);
  delay(t);
  digitalWrite(BUILTIN_LED, LOW);
  delay(t);
}

void exit(int exit_code) {
  pinMode(BUILTIN_LED, OUTPUT);

  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
  blinkBuiltin(100);
  delay(1000);

  // Constantly blink the "exit pattern" and the exit code
  for (;;) {
    // Pattern "exit"
    for (unsigned i = 0, d = 3; i < 15; ++i, d += max(1, min(d / 5, 35))) {
      blinkBuiltin(d);
    }
    for (unsigned i = 0, d = 180; i < 20; ++i, d -= min(d / 4, 35)) {
      blinkBuiltin(d);
    }
    delay(2000);

    unsigned shown_exit_code = min((unsigned) exit_code, MAX_SHOWN_EXITCODE);

    if (shown_exit_code >= 10) {
      // Blink tens of the error code
      for (unsigned i = 0; i < shown_exit_code / 10; ++i) {
        blinkBuiltin(1000);
      }
      delay(350);
    }
    // Blink lower digit of the error code
    for (unsigned i = 0; i < shown_exit_code % 10; ++i) {
      blinkBuiltin(200);
    }

    delay(2000);
  }
}

//////////////////////////////
/// Simple string printing ///
//////////////////////////////

int puts(const char *str) {
  return serial_print_str_unready(str);
}

int fputs(const char *str, FILE *stream) {
  return puts(str);
}

////////////////////////////////////////
/// `printf`-like formatted printing ///
////////////////////////////////////////

#define MAX_LINE_SIZE 50

int vprintf(const char *format_str, va_list args) {
  char str[MAX_LINE_SIZE];
  vsnprintf(str, MAX_LINE_SIZE, format_str, args);
  return puts(str);
}

int printf(const char *format_str, ...) {
  int res;
  va_list args; va_start(args, format_str); {
    res = vprintf(format_str, args);
  } va_end(args);
  return res;
}

int fprintf(FILE *stream, const char *format_str, ...) {
  int res;
  va_list args; va_start(args, format_str); {
    res = vprintf(format_str, args);
  } va_end(args);
  return res;
}
