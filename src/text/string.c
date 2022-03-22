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
    while (str[len])
    {
        len++;
    }

    return len;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char* s)
{
    int i;

    i = 0;
    do
    {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) >= 1);
    if (i == 1)
        s[i++] = '0';
    s[i] = '\0';
    reverse(s);
}

