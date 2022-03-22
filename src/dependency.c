#include "dependency.h"
#include "hardware/uart/PL011/PL011.h"

/*
    This file will be used to initialize concrete implementations of abstracted dependencies
*/

uart_config init_uart_config()
{
    uart_config config = 
    {
        .data_bits = 8,
        .stop_bits = 1,
        .parity = false,
        .baudrate = 9600
    };

    return config;
}

uart_methods get_uart_methods()
{
    uart_methods methods = 
    {
        .configure = PL001_configure,
        .read = PL011_read_data,
        .write = PL001_write_data
    };

    return methods;
}