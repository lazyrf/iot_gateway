#include "hal_crc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_crc.h"

uint32_t hal_crc_calc(uint32_t *data, uint32_t len)
{
    CRC_ResetDR();

    return CRC_CalcBlockCRC(data, len);
}

void hal_crc_init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
}
