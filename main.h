#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdarg.h>

int _printf(const char *format, ...);
int handle_format_specifier(char specifier, va_list args);
int print_character(va_list args);
int print_string(va_list args);
int print_percent(void);
int print_integer(va_list args);

#endif