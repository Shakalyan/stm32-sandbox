#include <common/log/log.h>
#include <addr_map.h>
#include <stdarg.h>
#include <stdio.h>


puart_t UART2_LOG = (puart_t)UART2_BASE;

void logger_init(void)
{
    uart_init(UART2_LOG, UART2);
}

void _pr(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            if (*fmt == '\n')
                uart_putc(UART2_LOG, '\r');
            uart_putc(UART2_LOG, *fmt);
            ++fmt;
            continue;
        }

        if (*(fmt+1) == 'u' || *(fmt+1) == 'd') {
            uint32_t val = va_arg(ap, uint32_t);
            uart_uint32(UART2_LOG, val);
            fmt += 2;
        }
        else if (*(fmt+1) == 'x') {
            uint32_t val = va_arg(ap, uint32_t);
            uart_puts(UART2_LOG, "0x");
            uart_hex(UART2_LOG, val);
            fmt += 2;
        }
        else if (*(fmt+1) == 's') {
            char *s = va_arg(ap, char*);
            uart_puts(UART2_LOG, s);
            fmt += 2;
        }
        else {
            uart_putc(UART2_LOG, '%');
            ++fmt;
        }

    }

    va_end(ap);

}
