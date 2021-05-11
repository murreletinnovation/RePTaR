#ifndef __SD_H
#define __SD_H

#include "reptar_main.h"

error_code_t sd_mount (void);
error_code_t sd_unmount (void);
error_code_t sd_get_free (uint32_t *totalSpace, uint32_t *freeSpace);
error_code_t sd_open_file (char *fn, uint8_t mode);
error_code_t sd_close_file (void);
error_code_t sd_puts (char* input);
void sd_test_print (void);

#endif /* __SD_H */
