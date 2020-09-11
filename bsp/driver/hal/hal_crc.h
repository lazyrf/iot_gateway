#ifndef __HAL_CRC_H
#define __HAL_CRC_H

#include <stdint.h>

void hal_crc_init(void);
uint32_t hal_crc_calc(uint32_t *data, uint32_t len);

#endif /* __HAL_CRC_H */
