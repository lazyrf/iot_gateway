#ifndef __DRV_FLASH_H
#define __DRV_FLASH_H

#include "stm32f4xx.h"
#include "igw_errno.h"

igw_err_t drv_flash_write_word(__IO uint32_t address, uint32_t *data, uint32_t len);
igw_err_t drv_flash_write_byte(__IO uint32_t address, uint8_t *data, uint32_t len);

#endif /* __DRV_FLASH_H */
