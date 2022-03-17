#include "console.h"
#include <stdint.h>

volatile uint8_t *uart0 = (uint8_t *)UART_ADDRESS;

void write_to_console(const char *str)
{
    while (*str)
    {
        *uart0 = *str++;
    }
}