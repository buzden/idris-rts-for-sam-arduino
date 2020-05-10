#include <stdlib.h>

#include "Arduino.h"

//////////////////////
/// System exiting ///
//////////////////////

#define BUILTIN_LED 13

#define MAX_SHOWN_EXITCODE 32

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
