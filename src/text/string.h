#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdbool.h>

bool is_digit(char c);
int to_number(char c);
size_t strlen(const char *str);

#endif