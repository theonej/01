#include "console.h"
#include "config.h"
#include <stdint.h>
#include <stdbool.h>
#include "hardware/uart/uart.h"
#include "text/string.h"

static uart_methods _methods;

void init_console(uart_methods methods)
{
    _methods = methods;
}

void write_to_console(const char *str)
{
    _methods.write(str);
}

uart_status read_from_console(char *buffer)
{
    uart_status status;

    bool do_continue = true;
    int buffer_index = 0;
    while (do_continue)
    {
        char c;

        status = _methods.read(&c);
        if (status != UART_OK && status != UART_NO_DATA)
        {
            write_to_console("There was an error reading from the console.  The error is: \n");
         
            char err[64];
            itoa(status, err);
            write_to_console(err);
            write_to_console("\n");

            do_continue = false;
        }
        else
        {
            if (status == UART_OK)
            {
                buffer[buffer_index++] = c;
        
                 write_to_console(&c);
                if (c == '\r')
                {
                    buffer[buffer_index] = '\0';
                    do_continue = false;
                }
            }
        }
    }

    return status;
}