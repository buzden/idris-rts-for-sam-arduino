#ifndef _CPP_WRAPPERS_H
#define _CPP_WRAPPERS_H

#include <stdlib.h>

#ifndef SERIAL_CONFIGURATION // allowing redefenition externally
#define SERIAL_CONFIGURATION 9600
#endif

#if defined (__cplusplus)
extern "C" {
#endif

size_t serial_print_str(const char *str);
size_t serial_print_str_unready(const char *str);
size_t serial_println_str(const char *str);
size_t serial_println_str_unready(const char *str);

size_t serial_println(void);
size_t serial_println_unready(void);

void serial_flush();

#if defined (__cplusplus)
} // from `extern "C"`
#endif

#endif // _CPP_WRAPPERS_H
