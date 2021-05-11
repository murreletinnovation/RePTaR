#include <stdio.h>
#include "sd.h"
#include "fatfs.h"

static FATFS fs;
static FIL fil;

error_code_t sd_mount (void)
{
	FRESULT fres;
	uint8_t retval = E_OK;

	fres = f_mount(&fs, "", 0);
	if (fres != FR_OK)
	{
		reptar_printf("f_mount error (%i)\r\n", fres);
		retval = E_FS;
		goto out;
	}
	else
	{
		reptar_printf("Successfully mounted file system\r\n");
	}

out:
	return retval;
}

error_code_t sd_unmount (void)
{
	FRESULT fres;
	uint8_t retval = E_OK;

	fres = f_mount(NULL, "", 1);

	if (fres != FR_OK)
	{
		reptar_printf("f_mount error (%i)\r\n", fres);
		retval = E_FS;
		goto out;
	}
	else
	{
		reptar_printf("Successfully unmounted file system\r\n");
	}

out:
	return retval;
}

error_code_t sd_get_free (uint32_t *totalSpace, uint32_t *freeSpace)
{
    FRESULT fres;
    FATFS *pfs;
    DWORD fre_clust;
    uint8_t retval = E_OK;

    fres = f_getfree("", &fre_clust, &pfs);

    if (fres != FR_OK)
    {
        reptar_printf("f_getfree error (%i)\r\n", fres);
        retval = E_FS;
        goto out;
    }

    *totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    *freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);

    /* free space is less than 1kb */
    if(*freeSpace < 1)
    {
        reptar_printf("Not enough free space on SD card (%i)\r\n", fres);
        retval = E_FS;
        goto out;
    }

out:
    return retval;
}

error_code_t sd_open_file (char *fn, BYTE mode)
{
    FRESULT fres;
    uint8_t retval = E_OK;

    fres = f_open(&fil, fn, mode);

    if (fres != FR_OK)
    {
        reptar_printf("f_open error (%i)\r\n", fres);
        retval = E_FS;
        goto out;
    }
    else
    {
        reptar_printf("Successfully opened file system\r\n");
    }

out:
    return retval;
}

error_code_t sd_close_file (void)
{
    FRESULT fres;
    uint8_t retval = E_OK;

    fres = f_close(&fil);

    if (fres != FR_OK)
    {
        reptar_printf("f_close error (%i)\r\n", fres);
        retval = E_FS;
        goto out;
    }
    else
    {
        reptar_printf("Successfully closed file\r\n");
    }

out:
    return retval;
}

error_code_t sd_puts (char* input)
{
    uint8_t retval = E_OK;

    if (f_puts(input, &fil) < 1)
    {
        reptar_printf("f_puts error \r\n");
        retval = E_FS;
        goto out;
    }

out:
    return retval;
}

void sd_test_print (void)
{
    char buffer[100];

    while(f_gets(buffer, sizeof(buffer), &fil))
    {
        reptar_printf("%s", buffer);
        fflush(stdout);
    }
}

