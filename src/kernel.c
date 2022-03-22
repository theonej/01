#include <stdint.h>
#include "text/console.h"
#include "dependency.h"

static uart_config _uart_config;
static uart_methods _uart_methods;

void init()
{
    _uart_config = init_uart_config();
    _uart_methods = get_uart_methods();

    _uart_methods.configure(&_uart_config);

    init_console(_uart_methods);
}

int main()
{
    init();

    const char *message = "initializing 01\n";
    write_to_console(message);

    message = "Please input 4096 bit encryption key\n";
    write_to_console(message);
    
    char buffer[4096];
    uart_status status = read_from_console(buffer);
    if (status == UART_OK)
    {
        write_to_console("encryption key read from console:\n");
        write_to_console(buffer);
    }

    while (1)
    {
    }

    return 0;
}