#include <stdint.h>

#include "hal_flash.h"
#include "stm32f4xx_flash.h"

/**
 * @brief Get the sector of a given address
 * @param None
 * @re    The sector of a given address
 */
static uint32_t _get_sector(uint32_t address)
{
    uint32_t sector = 0;

    if ((address < HAL_FLASH_SECTOR_1_ADDR) && (address >= HAL_FLASH_SECTOR_0_ADDR)) {
        sector = FLASH_Sector_0;
    } else if ((address < HAL_FLASH_SECTOR_2_ADDR) && (address >= HAL_FLASH_SECTOR_1_ADDR)) {
        sector = FLASH_Sector_1;
    } else if ((address < HAL_FLASH_SECTOR_3_ADDR) && (address >= HAL_FLASH_SECTOR_2_ADDR)) {
        sector = FLASH_Sector_2;
    } else if ((address < HAL_FLASH_SECTOR_4_ADDR) && (address >= HAL_FLASH_SECTOR_3_ADDR)) {
        sector = FLASH_Sector_3;
    } else if ((address < HAL_FLASH_SECTOR_5_ADDR) && (address >= HAL_FLASH_SECTOR_4_ADDR)) {
        sector = FLASH_Sector_4;
    } else if ((address < HAL_FLASH_SECTOR_6_ADDR) && (address >= HAL_FLASH_SECTOR_5_ADDR)) {
        sector = FLASH_Sector_5;
    } else if ((address < HAL_FLASH_SECTOR_7_ADDR) && (address >= HAL_FLASH_SECTOR_6_ADDR)) {
        sector = FLASH_Sector_6;
    } else if ((address < HAL_FLASH_SECTOR_8_ADDR) && (address >= HAL_FLASH_SECTOR_7_ADDR)) {
        sector = FLASH_Sector_7;
    } else if((address < HAL_FLASH_SECTOR_9_ADDR) && (address >= HAL_FLASH_SECTOR_8_ADDR)) {
        sector = FLASH_Sector_8;
    } else if ((address < HAL_FLASH_SECTOR_10_ADDR) && (address >= HAL_FLASH_SECTOR_9_ADDR)) {
        sector = FLASH_Sector_9;
    } else if ((address < HAL_FLASH_SECTOR_11_ADDR) && (address >= HAL_FLASH_SECTOR_10_ADDR)) {
        sector = FLASH_Sector_10;
    } else {
        sector = FLASH_Sector_11;
    }

    return sector;
}

/**
 * @brief   Locks flash for write access
 * @param   None
 * @rv      None
 */
void hal_flash_lock(void)
{
    FLASH_Lock();
}

/**
 * @brief   Unlocks flash for write access
 * @param   None
 * @rv      None
 */
void hal_flash_unlock(void)
{
    FLASH_Unlock();
}

igw_err_t hal_flash_program_word(uint32_t addr, uint32_t data)
{
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will be done by word */
    return (FLASH_ProgramWord(addr, data) == FLASH_COMPLETE) ? IGW_ERR_OK : IGW_ERR_HAL_FLASH_PROGRAM;
}

igw_err_t hal_flash_program_byte(uint8_t  addr, uint8_t data)
{
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will be done by word */
    return (FLASH_ProgramByte(addr, data) == FLASH_COMPLETE) ? IGW_ERR_OK : IGW_ERR_HAL_FLASH_PROGRAM;
}

igw_err_t hal_flash_erase(uint32_t start_addr, uint32_t end_addr)
{
    uint32_t start_sector;
    uint32_t end_sector;
    uint32_t sector_idx;

    /* Clear pending flags (if any) */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
        FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

    /* Get the number of the start and end sectors */
    start_sector =_get_sector(start_addr);
    end_sector = _get_sector(end_addr);

    /* Start the erase operation */
    sector_idx = start_sector;
    while (sector_idx <= end_sector) {
        /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
        be done by word */
        if (FLASH_EraseSector(sector_idx, VoltageRange_3) != FLASH_COMPLETE) {
            /* Error occurred while sector erase.
            User can add here some code to deal with this error  */
            return IGW_ERR_HAL_FLASH_ERASE;
        }
        sector_idx += 8;
    }

    return IGW_ERR_OK;
}
