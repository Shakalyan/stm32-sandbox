#ifndef _ERRORS_H_
#define _ERRORS_H_

typedef enum error {
    SUCCESS = 0,
    VOLTAGE_NOT_SUPPORTED = 1,
    SYSCLK_NOT_SUPPORTED,

} error_t;

#endif
