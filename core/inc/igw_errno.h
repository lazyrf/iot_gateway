#ifndef __ERRNO_H
#define __ERRNO_H

typedef enum {
    IGW_ERR_OK,

    /* HAL error */
    IGW_ERR_HAL_I2C_BUSY,
    IGW_ERR_HAL_I2C_SEND_START,
    IGW_ERR_HAL_I2C_SEND_SLAVE_ADDR,
    IGW_ERR_HAL_I2C_SEND_DATA,
} igw_err_t;

#endif /* __ERRNO_H */
