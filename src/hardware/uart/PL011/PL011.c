#include "PL011.h"
#include "config.h"
#include <math.h>
#include "text/string.h"

static uart_registers *_uart0 = (uart_registers *)UART_ADDRESS;

const int MIN_DATA_BIT_SIZE = 5u;
const int MAX_DATA_BIT_SIZE = 8u;
const int VALID_STOP_BITS[2] = {1, 2};
const int MIN_BAUDRATE = 110u;
const int MAX_BAUDRATE = 460800u;
const int DIVISOR_MULTIPLIER = 16u;
const int FRACTIONAL_MULTIPLIER = 64u;

uart_status validate_config(uart_config *config)
{
    int returnValue = UART_OK;

    if (config->data_bits < MIN_DATA_BIT_SIZE || config->data_bits > MAX_DATA_BIT_SIZE)
    {
        returnValue = UART_INVALID_ARGUMENT_WORDSIZE;
        return returnValue;
    }

    if (config->stop_bits != VALID_STOP_BITS[0] && config->stop_bits != VALID_STOP_BITS[1])
    {
        returnValue = UART_INVALID_ARGUMENT_STOP_BITS;
        return returnValue;
    }

    if (config->baudrate < MIN_BAUDRATE || config->baudrate > MAX_BAUDRATE)
    {
        returnValue = UART_INVALID_ARGUMENT_BAUDRATE;
        return returnValue;
    }

    return returnValue;
}

void disable_uart()
{
    _uart0->CR &= ~CR_UARTEN;
}

void enable_uart()
{
    _uart0->CR |= CR_UARTEN;
}

void finish_transmission()
{
    while (_uart0->FR & FR_BUSY)
        ;
}

void flush_fifo()
{
    _uart0->LCRH &= ~LCRH_FEN;
}

void set_baudrate(uart_config *config)
{
    double int_part, fractional_part;
    double divisor = (double)REFCLOCK / (DIVISOR_MULTIPLIER * config->baudrate);
    fractional_part = modf(divisor, &int_part); // int part is set inside modf

    _uart0->IBRD = (uint16_t)int_part;
    _uart0->FBRD = (uint16_t)((fractional_part * FRACTIONAL_MULTIPLIER) + 0.5);
}

int set_data_bits(uart_config *config, int lcrh)
{
    // data_bits is guaranteed to be >=5 <= 8 by validate_config
    uint32_t bitSizes[4] = {LCRH_WLEN_5BITS, LCRH_WLEN_6BITS, LCRH_WLEN_7BITS, LCRH_WLEN_8BITS};
    lcrh |= bitSizes[config->data_bits - 5];

    return lcrh;
}

int set_parity_bits(uart_config *config, int lcrh)
{
    if (config->parity)
    {
        lcrh |= LCRH_PEN;
        lcrh |= LCRH_EPS;
        lcrh |= LCRH_SPS;
    }
    else
    {
        lcrh &= ~LCRH_PEN;
        lcrh &= ~LCRH_EPS;
        lcrh &= ~LCRH_SPS;
    }

    return lcrh;
}

int set_stop_bits(uart_config *config, int lcrh)
{
    if (config->stop_bits == VALID_STOP_BITS[0])
    {
        lcrh &= ~LCRH_STP2;
    }
    else
    {
        lcrh |= LCRH_STP2;
    }

    return lcrh;
}

int enable_fifo(int lcrh)
{
    lcrh |= LCRH_FEN;

    return lcrh;
}

void configure_line_control_register(uart_config *config)
{
    uint32_t lcrh = 0u;

    lcrh = set_data_bits(config, lcrh);
    lcrh = set_parity_bits(config, lcrh);
    lcrh = set_stop_bits(config, lcrh);
    lcrh = enable_fifo(lcrh);

    _uart0->LCRH = lcrh;
}

uart_status PL001_configure(uart_config *config)
{
    int status = validate_config(config);

    if (status == UART_OK)
    {
        disable_uart();

        finish_transmission();

        flush_fifo();

        set_baudrate(config);

        configure_line_control_register(config);

        enable_uart();
    }

    return status;
}

void uart_write_char(char c)
{
    while (_uart0->FR & FR_TXFF);

    if (c != '\0')
    {
        _uart0->DR = c;
    }
}

void PL001_write_data(const char *data)
{
    while (*data)
    {
        uart_write_char(*data++);
    }
}

uart_status PL011_read_data(char *buffer)
{
    uart_status status = UART_NO_DATA;

    if (!(_uart0->FR & FR_RXFE))
    {
        *buffer = _uart0->DR & DR_DATA_MASK;
        status = UART_OK;
        if (_uart0->RSRECR & RSRECR_ERR_MASK)
        {
            _uart0->RSRECR &= RSRECR_ERR_MASK;
            status = UART_RECEIVE_ERROR;
        }
    }

    return status;
}