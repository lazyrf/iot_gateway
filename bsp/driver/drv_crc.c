#include "drv_crc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_crc.h"

uint32_t drv_crc_calc(uint32_t *data, uint32_t len)
{
    CRC_ResetDR();

    return CRC_CalcBlockCRC(data, len);
}

void drv_crc_init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
}
