#ifndef _COMMON_H_
#define _COMMON_H_


#include <uart/uart.h>
#include <config.h>


#define LOG_LEVEL_FATAL ((1))
#define LOG_LEVEL_ERROR ((2))
#define LOG_LEVEL_WARN  ((3))
#define LOG_LEVEL_INFO  ((4))
#define LOG_LEVEL_DEBUG ((5))


#define pr(level, fmt, ...) {{      \
    if (level <= CONFIG_LOG_LEVEL)  \
        _pr(fmt, ##__VA_ARGS__);    \
}}


#define pr_fatal(fmt, ...) pr(LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__)
#define pr_error(fmt, ...) pr(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define pr_warn(fmt, ...)  pr(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define pr_info(fmt, ...)  pr(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define pr_debug(fmt, ...) pr(LOG_LEVEL_DEBUG, "%s: " fmt, __func__, ##__VA_ARGS__)


extern puart_t UART2_LOG;

void logger_init(void);

void _pr(char *fmt, ...);

#endif
