#include <stdint.h>

#include "drv_flash.h"
#include "hal_flash.h"
#include "board.h"

igw_err_t drv_flash_erase(uint32_t start_addr, uint32_t end_addr)
{
    igw_err_t rv;

    hal_flash_unlock();

    rv = hal_flash_erase(start_addr, end_addr);

    hal_flash_lock();

    return rv;
}

igw_err_t drv_flash_write_word(__IO uint32_t address, uint32_t *data, uint32_t len)
{
    uint32_t i;
    igw_err_t rv = IGW_ERR_OK;

    hal_flash_unlock();

    for (i = 0; (i < len) && (address <= (BOARD_FLASH_END_ADDRESS - 4)); i++) {
        rv = hal_flash_program_word(address, *(uint32_t *) (data + i));
        if (rv == IGW_ERR_OK) {
            /* Check the written value */
            if (*((uint32_t *) address) != *(uint32_t *) (data + i)) {
                /* Flash content doesn't match RAM content */
                rv = IGW_ERR_DRV_FLASH_WRITE;
                break;
            } else {
                /* Increment FLASH destination address */
                address += 4;
            }
        } else {
            /* Error occured while writing data in Flash memory */
            break;
        }
    }

    hal_flash_lock();

    return rv;
}

igw_err_t drv_flash_write_byte(__IO uint32_t address, uint8_t *data, uint32_t len)
{
    uint32_t i;
    igw_err_t rv = IGW_ERR_OK;

    hal_flash_unlock();

    for (i = 0; (i < len) && (address <= (BOARD_FLASH_END_ADDRESS - 1)); i++) {
        rv = hal_flash_program_byte(address, *(uint8_t *) (data + i));
        if (rv == IGW_ERR_OK) {
            /* Check the written value */
            if (*((uint8_t *) address) != *(uint8_t *) (data + i)) {
                /* Flash content doesn't match RAM content */
                rv = IGW_ERR_DRV_FLASH_WRITE;
            } else {
                /* Increment FLASH destination address */
                address += 1;
            }
        } else {
            /* Error occured while writing data in Flash memory */
            break;
        }
    }

    hal_flash_lock();

    return rv;
}
