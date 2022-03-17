#include "string.h"

bool is_digit(char c)
{
    return c >= 48 && c <= 57;
}

int to_number(char c)
{
    return c - 48;
}

size_t strlen(const char *str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }

    return len;
}