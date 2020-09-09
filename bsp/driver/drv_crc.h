#ifndef __DRV_CRC_H
#define __DRV_CRC_H

#include <stdint.h>

void drv_crc_init(void);
uint32_t drv_crc_calc(uint32_t *data, uint32_t len);

#endif /* __DRV_CRC_H */
