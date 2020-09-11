#include "hal_iwdg.h"
#include "stm32f4xx_iwdg.h"

#define IWDG_PRV        IWDG_Prescaler_256
#define IWDG_RLV        3125

void hal_iwdg_feed(void)
{
    IWDG_ReloadCounter();
}

/*
 * @brief
 * Tout = prv /40 * rlv (s)
 * prv can be [4,8,16,32,64,128,256]
 * prv:
 *     @arg IWDG_Prescaler_4: IWDG prescaler set to 4
 *     @arg IWDG_Prescaler_8: IWDG prescaler set to 8
 *     @arg IWDG_Prescaler_16: IWDG prescaler set to 16
 *     @arg IWDG_Prescaler_32: IWDG prescaler set to 32
 *     @arg IWDG_Prescaler_64: IWDG prescaler set to 64
 *     @arg IWDG_Prescaler_128: IWDG prescaler set to 128
 *     @arg IWDG_Prescaler_256: IWDG prescaler set to 256
 * rlv: 12 bit
 * Ex. IWDG_Config(IWDG_Prescaler_64 ,625);
 * (64/40) * 625 = 1s
 * Freq = 40 / (4 * 2 ^ prv)
 * Period = (4 * 2 ^ prv) / 40
 * Tout = rlv * period = rlv * (4 * 2 ^ prv) / 40
 */
void hal_iwdg_init(void)
{
    /* Make Prv and ARR be writable */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* Set Prescaler */
    IWDG_SetPrescaler(IWDG_PRV);

    /* Set RLR value */
    IWDG_SetReload(IWDG_RLV);

    /* Load RLR value to CNT */
    IWDG_ReloadCounter();

    /* Enable IWDG */
    IWDG_Enable();
}
