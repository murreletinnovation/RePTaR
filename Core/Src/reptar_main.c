#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include "reptar_main.h"
#include "low_power.h"
#include "sd.h"
#include "ff.h"

extern UART_HandleTypeDef 	DEBUG_UART_HANDLE;
extern RTC_HandleTypeDef  	RTC_HANDLE;
extern SPI_HandleTypeDef	SD_SPI_HANDLE;

void reptar_printf(const char *fmt, ...)
{
	static char buffer[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	int len = strlen(buffer);
	HAL_UART_Transmit(&DEBUG_UART_HANDLE, (uint8_t*) buffer, len, -1);
}


error_code_t reptar_init (void)
{
	error_code_t retval = E_OK;
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	uint32_t totalSpace, freeSpace;

	HAL_RTC_GetTime(&RTC_HANDLE, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&RTC_HANDLE, &gDate, RTC_FORMAT_BIN);

	reptar_printf("%02d:%02d:%02d\r\n", gTime.Hours, gTime.Minutes, gTime.Seconds);
	reptar_printf("%02d-%02d-%2d\r\n", gDate.Date, gDate.Month, 2000 + gDate.Year);
	reptar_printf("Welcome to the Reptar Project!\r\n");

    /* Wait for SD module reset */
    HAL_Delay(500);

    retval = sd_mount();
    retval = sd_open_file("file.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
    retval = sd_get_free(&totalSpace, &freeSpace);
    retval = sd_puts("STM32 SD Card I/O Example via SPI\r\n");
    retval = sd_puts("Save the world!!!\r\n");
    retval = sd_close_file();
    retval = sd_open_file("file.txt", FA_READ);
    sd_test_print();
    retval = sd_close_file();
    retval = sd_unmount();

    // Include this when you have an actual interrupt source
//    low_power_enter_stop();
//    retval = low_power_exit_stop();

	return retval;
}
