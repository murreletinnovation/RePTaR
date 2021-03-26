#include "pcf8523.h"

extern I2C_HandleTypeDef RTC_I2C_HANDLE;

error_code_t _pcf8523_reg_read(uint8_t reg, uint8_t *val, uint8_t val_size)
{
	error_code_t retval = E_OK;
	uint8_t status;

	if (val == NULL)
	{
		retval = E_NULL_POINTER;
		goto out;
	}

	if (val_size == 0)
	{
		retval = E_INVALID_ARG;
		goto out;
	}

	if (reg > 0x13)
	{
		retval = E_INVALID_ARG;
		goto out;
	}

	status = HAL_I2C_Master_Transmit(&RTC_I2C_HANDLE, PCF8523_ADDR, &reg, 1, HAL_MAX_DELAY);

	if (status != HAL_OK)
	{
		retval = E_HAL;
		goto out;
	}

	status = HAL_I2C_Master_Receive(&RTC_I2C_HANDLE, PCF8523_ADDR, val, val_size, HAL_MAX_DELAY);

	if (status != HAL_OK)
	{
		retval = E_HAL;
		goto out;
	}

out:
	return retval;
}

error_code_t _pcf8523_reg_write(uint8_t reg, uint8_t val)
{
	error_code_t retval = E_OK;
	uint8_t status;
	uint8_t buf[2];

	if (reg > 0x13)
	{
		retval = E_INVALID_ARG;
		goto out;
	}

	buf[0] = reg;
	buf[1] = val;
	status = HAL_I2C_Master_Transmit(&RTC_I2C_HANDLE, PCF8523_ADDR, buf, 2, HAL_MAX_DELAY);

	if (status != HAL_OK)
	{
		retval = E_HAL;
		goto out;
	}

out:
	return retval;
}

error_code_t pcf8523_self_test(void)
{
	uint8_t buf;
	error_code_t retval = E_OK;

	retval = _pcf8523_reg_write(PCF8523_CONTROL_1, 0x02);

	if (retval != E_OK)
	{
		goto out;
	}

	retval = _pcf8523_reg_read(PCF8523_CONTROL_1, &buf, 1);

	if (retval != E_OK)
	{
		goto out;
	}

	if ( buf != 0x02)
	{
		while(1);
	}

	retval = _pcf8523_reg_write(PCF8523_CONTROL_1, 0x00);

	if (retval != E_OK)
	{
		goto out;
	}

out:
	return retval;
}

error_code_t pcf8523_lost_power(bool *lost_power)
{
	uint8_t buf;
	error_code_t retval = E_OK;

	retval = _pcf8523_reg_read(PCF8523_SECONDS, &buf, 1);

	if (retval != E_OK)
	{
		goto out;
	}

	if ( buf & 0x80)
	{
		*lost_power = true;
	}
	else
	{
		*lost_power = false;
	}

out:
	return retval;
}

error_code_t pcf8523_is_running(bool *is_running)
{
	uint8_t buf;
	error_code_t retval = E_OK;

	retval = _pcf8523_reg_read(PCF8523_CONTROL_1, &buf, 1);

	if (retval != E_OK)
	{
		goto out;
	}

	if ( buf & 0x20)
	{
		*is_running = false;
	}
	else
	{
		*is_running = true;
	}

out:
	return retval;
}

error_code_t pcf8523_is_initialized(bool *is_initialized)
{
	uint8_t buf;
	error_code_t retval = E_OK;

	retval = _pcf8523_reg_read(PCF8523_CONTROL_3, &buf, 1);

	if (retval != E_OK)
	{
		goto out;
	}

	if ( buf & 0xE0)
	{
		*is_initialized = false;
	}
	else
	{
		*is_initialized = true;
	}

out:
	return retval;
}

error_code_t pcf8523_init(void)
{
	error_code_t retval = E_OK;
	bool lost_power;

	retval = pcf8523_lost_power(&lost_power);

	if (retval != E_OK)
	{
		goto out;
	}


out:
	return retval;
}
