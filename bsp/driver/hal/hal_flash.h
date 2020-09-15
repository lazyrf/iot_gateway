#ifndef __HAL_FLASH_H
#define __HAL_FLASH_H

#include <stdint.h>

#include "igw_errno.h"

/* Base address of the Flash sectors */
#define HAL_FLASH_SECTOR_0_ADDR     ((uint32_t)0x08000000) /* Base address of Sector 0, 16 Kbytes   */
#define HAL_FLASH_SECTOR_1_ADDR     ((uint32_t)0x08004000) /* Base address of Sector 1, 16 Kbytes   */
#define HAL_FLASH_SECTOR_2_ADDR     ((uint32_t)0x08008000) /* Base address of Sector 2, 16 Kbytes   */
#define HAL_FLASH_SECTOR_3_ADDR     ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 Kbytes   */
#define HAL_FLASH_SECTOR_4_ADDR     ((uint32_t)0x08010000) /* Base address of Sector 4, 64 Kbytes   */
#define HAL_FLASH_SECTOR_5_ADDR     ((uint32_t)0x08020000) /* Base address of Sector 5, 128 Kbytes  */
#define HAL_FLASH_SECTOR_6_ADDR     ((uint32_t)0x08040000) /* Base address of Sector 6, 128 Kbytes  */
#define HAL_FLASH_SECTOR_7_ADDR     ((uint32_t)0x08060000) /* Base address of Sector 7, 128 Kbytes  */

#define HAL_FLASH_SECTOR_8_ADDR     ((uint32_t)0x08080000) /* Base address of Sector 8, 128 Kbytes  */
#define HAL_FLASH_SECTOR_9_ADDR     ((uint32_t)0x080A0000) /* Base address of Sector 9, 128 Kbytes  */
#define HAL_FLASH_SECTOR_10_ADDR    ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 Kbytes */
#define HAL_FLASH_SECTOR_11_ADDR    ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 Kbytes */

void hal_flash_lock(void);
void hal_flash_unlock(void);
igw_err_t hal_flash_program_word(uint32_t addr, uint32_t data);
igw_err_t hal_flash_program_byte(uint8_t  addr, uint8_t data);
igw_err_t hal_flash_erase(uint32_t start_addr, uint32_t end_addr);

#endif /* __HAL_FLASH_H */
