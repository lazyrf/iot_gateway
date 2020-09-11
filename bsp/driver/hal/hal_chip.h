#ifndef __HAL_CHIP_H
#define __HAL_CHIP_H

#include "stm32f4xx.h"

/* Unique ID register address location */
#define HAL_CHIP_UNIQUE_ID_ADDRESS          0x1FFF7A10

/* Flash size register address */
#define HAL_CHIP_FLASH_SIZE_ADDRESS         0x1FFF7A22

/* Gets device id */
#define HAL_CHIP_GET_DEVICE_ID()            (DBGMCU->IDCODE & 0x00000FFF)

/* Gets device revision */
#define HAL_CHIP_GET_REVISION_ID()          ((DBGMCU->IDCODE >> 16) & 0x0000FFFF)

/* Get device flash size in kilo bytes */
#define HAL_CHIP_GET_FLASH_SIZE()           (*(__IO uint16_t *) (HAL_CHIP_FLASH_SIZE_ADDRESS))

/* Gets unique ID number in 8-bit format */
#define HAL_CHIP_GET_UNIQUE_ID8(x)          ((x >= 0 && x < 12) ? (*(__IO uint8_t *) (HAL_CHIP_UNIQUE_ID_ADDRESS + (x))) : 0)

/* Gets unique ID number in 16-bit format */
#define HAL_CHIP_GET_UNIQUE_ID16(x)         ((x >= 0 && x < 6) ? (*(__IO uint16_t *) (HAL_CHIP_UNIQUE_ID_ADDRESS + 2 * (x))) : 0)

/* Gets unique ID number in 32-bit format */
#define HAL_CHIP_GET_UNIQUE_ID32(x)         ((x >= 0 && x < 3) ? (*(__IO uint32_t *) (HAL_CHIP_UNIQUE_ID_ADDRESS + 4 * (x))) : 0)

#endif /* __HAL_CHIP_H */
