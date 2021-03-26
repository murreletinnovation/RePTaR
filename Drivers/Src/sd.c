#include "sd.h"
#include "fatfs.h"


static FATFS FatFs;

error_code_t sd_mount (void)
{
	FRESULT fres;
	uint8_t retval = E_OK;

	fres = f_mount(&FatFs, "", 1); //1=mount now
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

	fres = f_mount(NULL, "", 0);

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

