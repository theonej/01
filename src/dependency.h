#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include "hardware/uart/uart.h"

uart_config init_uart_config();
uart_methods get_uart_methods();

#endif