#ifndef __REPTAR_MAIN_H
#define __REPTAR_MAIN_H

#include "stm32l4xx.h"
#include "main.h"

typedef enum
{
	E_OK = 0,
	E_NULL_POINTER,
	E_INVALID_ARG,
	E_HAL,
	E_FS
} error_code_t;

error_code_t reptar_init (void);
void reptar_printf(const char *fmt, ...);


#endif /* __REPTAR_MAIN_H */

