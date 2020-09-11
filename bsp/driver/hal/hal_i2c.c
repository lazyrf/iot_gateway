#include "hal_i2c.h"

#define HAL_I2C_FLAG_TIMEOUT_MS                     (1000UL)
#define HAL_I2C_WAIT_EVENT(timeout, err_code)       do { \
        uint32_t wait_time = (timeout); \
        if ((wait_time--) == 0) hal_i2c_err_cb((err_code)); \
    } while (0);

void hal_i2c_err_cb(ig_err_e err)
{
}

ig_err_e hal_i2c_byte_write(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t len, uint8_t const *data)
{
    uint8_t i;

    /* Send START */
    I2C_GenerateSTART(i2c.i2c, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_MODE_SELECT)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_START);
    }

    /* Send slave address for write */
    I2C_Send7bitAddress(i2c.i2c, (slave_addr << 1), I2C_Direction_Transmitter);
    /* Test on EV6 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_SLAVE_ADDR);
    }

    /* Send the slave's internal address to write */
    I2C_SendData(i2c.i2c, reg_addr);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
    }

    for (i = 0; i < len; i++) {
        /* Prepare the register value to be sent */
        I2C_SendData(i2c.i2c, data[i]);
        /* Test on EV8 and clear it */
        while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
            HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
        }
    }

    /* Send STOP condition */
    I2C_GenerateSTOP(i2c.i2c, ENABLE);

    return IG_ERR_OK;
}

ig_err_e hal_i2c_byte_read(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t len, uint8_t *data)
{
    while (I2C_GetFlagStatus(i2c.i2c, I2C_FLAG_BUSY)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_BUSY);
    }

    /* Send START */
    I2C_GenerateSTART(i2c.i2c, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_MODE_SELECT)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_START);
    }

    /* Send slave address for write */
    I2C_Send7bitAddress(i2c.i2c, (slave_addr << 1), I2C_Direction_Transmitter);
    /* Test on Ev6 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_SLAVE_ADDR);
    }

    /* Clear EV6 by setting agian the PE bit */
    I2C_Cmd(i2c.i2c, ENABLE);

    /* Send the slave's internal address to write */
    I2C_SendData(i2c.i2c, reg_addr);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
    }


    /* Send START condition a second time */
    I2C_GenerateSTART(i2c.i2c, ENABLE);
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_MODE_SELECT)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_START);
    }

    /* Send slave address for read */
    I2C_Send7bitAddress(i2c.i2c, (slave_addr << 1), I2C_Direction_Receiver);
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_SLAVE_ADDR);
    }

    /* While there is data to be read */
    while (len) {
        if (len == 1) {
            /* Disable Acknowledgment */
            I2C_AcknowledgeConfig(i2c.i2c, DISABLE);
            /* Send STOP condition */
            I2C_GenerateSTOP(i2c.i2c, ENABLE);
        }

        /* Test on EV7 and clear it */
        if (I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
            /* Read a byte form the slave */
            *data = I2C_ReceiveData(i2c.i2c);

            /* Point to the next locaion where the byte read will be saved */
            data++;

            /* Decrement the read bytes counter */
            len--;
        }
    }

    /* Enable Acknowledgment to be ready for another reception */
    I2C_AcknowledgeConfig(i2c.i2c, ENABLE);

    return IG_ERR_OK;
}

ig_err_e hal_i2c_u16_write(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint16_t reg_addr, uint8_t len, uint8_t const *data)
{
    uint8_t i;

    /* Send START */
    I2C_GenerateSTART(i2c.i2c, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_MODE_SELECT)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_START);
    }

    /* Send slave address for write */
    I2C_Send7bitAddress(i2c.i2c, (slave_addr << 1), I2C_Direction_Transmitter);
    /* Test on EV6 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_SLAVE_ADDR);
    }

    /* Send the slave's internal address to write */
    I2C_SendData(i2c.i2c, (reg_addr >> 8) & 0x00FF);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
    }

    /* Send the slave's internal address to write */
    I2C_SendData(i2c.i2c, reg_addr & 0x00FF);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
    }

    for (i = 0; i < len; i++) {
        /* Prepare the register value to be sent */
        I2C_SendData(i2c.i2c, data[i]);
        /* Test on EV8 and clear it */
        while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
            HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
        }
    }

    /* Send STOP condition */
    I2C_GenerateSTOP(i2c.i2c, ENABLE);

    return IG_ERR_OK;
}

ig_err_e hal_i2c_u16_read(hal_i2c_cfg_t i2c, uint8_t slave_addr, uint16_t reg_addr, uint8_t len, uint8_t *data)
{
    while (I2C_GetFlagStatus(i2c.i2c, I2C_FLAG_BUSY)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_BUSY);
    }

    /* Send START */
    I2C_GenerateSTART(i2c.i2c, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_MODE_SELECT)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_START);
    }

    /* Send slave address for write */
    I2C_Send7bitAddress(i2c.i2c, (slave_addr << 1), I2C_Direction_Transmitter);
    /* Test on Ev6 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_SLAVE_ADDR);
    }

    /* Clear EV6 by setting agian the PE bit */
    I2C_Cmd(i2c.i2c, ENABLE);

    /* Send the slave's internal address to write */
    I2C_SendData(i2c.i2c, (reg_addr >> 8) & 0x00FF);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
    }

    /* Send the slave's internal address to write */
    I2C_SendData(i2c.i2c, reg_addr & 0x00FF);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_DATA);
    }

    /* Send START condition a second time */
    I2C_GenerateSTART(i2c.i2c, ENABLE);
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_MODE_SELECT)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_START);
    }

    /* Send slave address for read */
    I2C_Send7bitAddress(i2c.i2c, (slave_addr << 1), I2C_Direction_Receiver);
    while (!I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
        HAL_I2C_WAIT_EVENT(HAL_I2C_FLAG_TIMEOUT_MS, IG_ERR_HAL_I2C_SEND_SLAVE_ADDR);
    }

    /* While there is data to be read */
    while (len) {
        if (len == 1) {
            /* Disable Acknowledgment */
            I2C_AcknowledgeConfig(i2c.i2c, DISABLE);
            /* Send STOP condition */
            I2C_GenerateSTOP(i2c.i2c, ENABLE);
        }

        /* Test on EV7 and clear it */
        if (I2C_CheckEvent(i2c.i2c, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
            /* Read a byte form the slave */
            *data = I2C_ReceiveData(i2c.i2c);

            /* Point to the next locaion where the byte read will be saved */
            data++;

            /* Decrement the read bytes counter */
            len--;
        }
    }

    /* Enable Acknowledgment to be ready for another reception */
    I2C_AcknowledgeConfig(i2c.i2c, ENABLE);

    return IG_ERR_OK;
}

void hal_i2c_init(hal_i2c_cfg_t i2c)
{
    I2C_InitTypeDef i2c_cfg;
    void (*rcc_clk_cmd)(uint32_t, FunctionalState);

    /* Enable clock */
    rcc_clk_cmd = i2c.clk_cmd;
    rcc_clk_cmd(i2c.clk, ENABLE);

    hal_gpio_cfg_af_od(i2c.scl, i2c.af);
    hal_gpio_cfg_af_od(i2c.sda, i2c.af);

    i2c_cfg.I2C_Mode = I2C_Mode_I2C;
    i2c_cfg.I2C_DutyCycle = I2C_DutyCycle_2;
    i2c_cfg.I2C_OwnAddress1 = i2c.addr;
    i2c_cfg.I2C_Ack = I2C_Ack_Enable;
    i2c_cfg.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    i2c_cfg.I2C_ClockSpeed = i2c.speed;
    I2C_Init(i2c.i2c, &i2c_cfg);
    I2C_Cmd(i2c.i2c, ENABLE);
}
