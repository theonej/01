#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    UART_OK = 0,
    UART_INVALID_ARGUMENT_BAUDRATE = 9001,
    UART_INVALID_ARGUMENT_WORDSIZE = 9002,
    UART_INVALID_ARGUMENT_STOP_BITS = 9003,
    UART_RECEIVE_ERROR = 9004,
    UART_NO_DATA = 9005
} uart_status;

typedef struct
{
    uint8_t data_bits;
    uint8_t stop_bits;
    bool parity;
    uint32_t baudrate;
} uart_config;

typedef uart_status (*configure_method)(uart_config *config);
typedef void (*write_method)(const char *);
typedef uart_status (*read_method)(char *buffer);

typedef struct
{
    configure_method configure;
    read_method read;
    write_method write;
} uart_methods;

#endif