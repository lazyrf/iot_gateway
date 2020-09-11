#ifndef __ERRNO_H
#define __ERRNO_H

typedef enum {
    IG_ERR_OK,

    /* HAL error */
    IG_ERR_HAL_I2C_BUSY,
    IG_ERR_HAL_I2C_SEND_START,
    IG_ERR_HAL_I2C_SEND_SLAVE_ADDR,
    IG_ERR_HAL_I2C_SEND_DATA,
} ig_err_e;

#endif /* __ERRNO_H */
