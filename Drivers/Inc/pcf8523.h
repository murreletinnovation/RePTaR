#ifndef __PCF8523_H
#define __PCF8523_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32l4xx.h"
#include "reptar_main.h"

#define PCF8523_ADDR						0xD0 //0x68

#define PCF8523_CONTROL_1					0x00
#define PCF8523_CONTROL_2					0x01
#define PCF8523_CONTROL_3					0x02
#define PCF8523_SECONDS						0x03
#define PCF8523_MINUTES						0x04
#define PCF8523_HOURS						0x05
#define PCF8523_DAYS						0x06
#define PCF8523_WEEKDAYS					0x07
#define PCF8523_MONTHS						0x08
#define PCF8523_YEARS						0x09
#define PCF8523_MINUTE_ALARM				0x0A
#define PCF8523_HOUR_ALARM					0x0B
#define PCF8523_DAY_ALARM					0x0C
#define PCF8523_WEEKDAY_ALARM				0x0D
#define PCF8523_OFFSET						0x0E
#define PCF8523_TMR_CLKOUT_CTRL				0x0F
#define PCF8523_TMR_A_FREQ_CTRL				0x10
#define PCF8523_TMR_A_REG					0x11
#define PCF8523_TMR_B_FREQ_CTRL				0x12
#define PCF8523_TMR_B_REG					0x13

error_code_t pcf8523_self_test(void);
error_code_t pcf8523_lost_power(bool *lost_power);
error_code_t pcf8523_is_running(bool *is_running);
error_code_t pcf8523_is_initialized(bool *is_initialized);
error_code_t pcf8523_init(void);

#endif /* __PCF8523_H */
