#ifndef CONSOLE_H
#define CONSOLE_H

#include "../hardware/uart/uart.h"

void init_console(uart_methods methods);
void write_to_console(const char *str);
uart_status read_from_console(char *buffer);

#endif