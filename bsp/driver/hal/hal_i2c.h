#ifndef __HAL_I2C_H
#define __HAL_I2C_H

#include "stm32f4xx_i2c.h"
#include "hal_gpio.h"
#include "igw_errno.h"

typedef struct {
    I2C_TypeDef *i2c;
    void *clk_cmd;
    uint32_t clk;
    hal_gpio_cfg_t scl;
    hal_gpio_cfg_t sda;
    uint16_t af;
    uint16_t addr;
    uint32_t speed;
} hal_i2c_cfg_t;

igw_err_t hal_i2c_byte_write(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t len, uint8_t const *data);
igw_err_t hal_i2c_byte_read(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t len, uint8_t *data);
igw_err_t hal_i2c_u16_write(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint16_t reg_addr, uint8_t len, uint8_t const *data);
igw_err_t hal_i2c_u16_read(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint16_t reg_addr, uint8_t len, uint8_t *data);
void hal_i2c_init(hal_i2c_cfg_t i2c);

#endif /* __HAL_I2C_H */
