#include <stdio.h>

#include "hal_rtc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "assert.h"

void hal_rtc_alarm_disable(hal_rtc_alarm_t alarm)
{
    assert(IS_RTC_ALRAM(alarm));

    /* Disable alarm interrupt */
    if (alarm == HAL_RTC_ALARM_A) {
        RTC_ITConfig(RTC_IT_ALRA, DISABLE);
    } else {
        RTC_ITConfig(RTC_IT_ALRB, DISABLE);
    }
    RTC_AlarmCmd(alarm, DISABLE);
}

void hal_rtc_alarm_enable(hal_rtc_alarm_t alarm)
{
    EXTI_InitTypeDef exti_cfg;

    assert(IS_RTC_ALRAM(alarm));

    /* Enable alarm interrupt */
    if (alarm == HAL_RTC_ALARM_A) {
        RTC_ITConfig(RTC_IT_ALRA, ENABLE);
    } else {
        RTC_ITConfig(RTC_IT_ALRB, ENABLE);
    }
    RTC_AlarmCmd(alarm, ENABLE);

    // Clear Alarm interupt status
    if (alarm == HAL_RTC_ALARM_A) {
        RTC_ClearFlag(RTC_FLAG_ALRAF);
    } else {
        RTC_ClearFlag(RTC_FLAG_ALRBF);
    }

    exti_cfg.EXTI_Line = EXTI_Line17;
    exti_cfg.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_cfg.EXTI_Trigger = EXTI_Trigger_Rising;
    exti_cfg.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_cfg);

    NVIC_SetPriority(RTC_Alarm_IRQn, 9);
    NVIC_EnableIRQ(RTC_Alarm_IRQn);

    // Clear EXTI_Line17 pending bit
    EXTI_ClearITPendingBit(EXTI_Line17);
}

void hal_rtc_alarm_set(hal_rtc_alarm_t alarm, hal_rtc_alarm_cfg_t alarm_cfg)
{
    RTC_AlarmTypeDef rtc_alarm_cfg;

    assert(IS_RTC_ALRAM(alarm));

    /* According document page.804 (Programming the alarm section), 1. and 2. step must be done before set/update alarm */
    RTC_AlarmCmd(alarm, DISABLE);

    if (alarm_cfg.wdsel == HAL_RTC_ALARM_DAY_IN_WEEK) {
        rtc_alarm_cfg.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;
    } else {
        rtc_alarm_cfg.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    }
    rtc_alarm_cfg.RTC_AlarmMask = alarm_cfg.mask;
    rtc_alarm_cfg.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
    rtc_alarm_cfg.RTC_AlarmTime.RTC_Hours = alarm_cfg.hour;
    rtc_alarm_cfg.RTC_AlarmTime.RTC_Minutes = alarm_cfg.min;
    rtc_alarm_cfg.RTC_AlarmTime.RTC_Seconds = alarm_cfg.sec;
    rtc_alarm_cfg.RTC_AlarmDateWeekDay = alarm_cfg.date;
    RTC_SetAlarm(RTC_Format_BIN, alarm, &rtc_alarm_cfg);
}

void hal_rtc_time_get(hal_rtc_time_t *time)
{
    RTC_TimeTypeDef rtc_time;

    RTC_GetTime(RTC_Format_BIN, &rtc_time);

    time->hour = rtc_time.RTC_Hours;
    time->min = rtc_time.RTC_Minutes;
    time->sec = rtc_time.RTC_Seconds;
    time->hour = rtc_time.RTC_Hours;
}

void hal_rtc_time_set(hal_rtc_time_t time)
{
    RTC_TimeTypeDef rtc_time;

    rtc_time.RTC_Hours = time.hour;
    rtc_time.RTC_Minutes = time.min;
    rtc_time.RTC_Seconds = time.sec;

    RTC_SetTime(RTC_Format_BIN, &rtc_time);
}

void hal_rtc_date_get(hal_rtc_date_t *date)
{
    RTC_DateTypeDef rtc_date;

    RTC_GetDate(RTC_Format_BIN, &rtc_date);

    date->year = rtc_date.RTC_Year;
    date->month = rtc_date.RTC_Month;
    date->date = rtc_date.RTC_Date;
    date->weekday = rtc_date.RTC_WeekDay;
}

void hal_rtc_date_set(hal_rtc_date_t date)
{
    RTC_DateTypeDef rtc_date;

    rtc_date.RTC_Year = date.year;
    rtc_date.RTC_Month = date.month;
    rtc_date.RTC_Date = date.date;
    rtc_date.RTC_WeekDay = date.weekday;

    RTC_SetDate(RTC_Format_BIN, &rtc_date);
}

void hal_rtc_datetime_get(hal_rtc_datetime_t *datetime)
{
    hal_rtc_date_get(&datetime->date);
    hal_rtc_time_get(&datetime->time);
}

void hal_rtc_datetime_set(hal_rtc_datetime_t datetime)
{
    hal_rtc_date_set(datetime.date);
    hal_rtc_time_set(datetime.time);
}

static void _hal_rtc_config(hal_rtc_clk_src_t clk_src)
{
    RTC_InitTypeDef rtc_cfg;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC Backup register */
    PWR_BackupAccessCmd(ENABLE);

    if (clk_src == HAL_RTC_CLK_SRC_LSI) {
        /* Enable the LSI OSC */
        RCC_LSICmd(ENABLE);

        /* Wait till LSI is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

        /* Select the LSI as RTC clock source */
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    } else {
        /* Enable the LSE OSC */
        RCC_LSEConfig(RCC_LSE_ON);

        /* Wait till LSE is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

        /* Select the LSE as RTC clock source */
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    }

    /* Enable the RTC clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();

    rtc_cfg.RTC_AsynchPrediv = 0x7F;
    rtc_cfg.RTC_SynchPrediv = 0xFF;
    rtc_cfg.RTC_HourFormat = RTC_HourFormat_24;
    RTC_Init(&rtc_cfg);
}

void hal_rtc_init(hal_rtc_clk_src_t clk_src)
{
    assert(IS_RTC_CLK_SRC(clk_src));

    if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x32F2) {
        printf("RTC is not set, start to config...\r\n");

        /* Config RTC */
        _hal_rtc_config(clk_src);

        /* Indictor for the RTC configuration */
        RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    } else {
        printf("RTC is ready\r\n");

        /* Check if the Power ON Rest flag is set */
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET) {
            printf("Power On Reset\r\n");
        }
        /* Check if the Pin Reset flag is set */
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET) {
            printf("Pin Reset\r\n");
        }

        /* Enable the PWR clock */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

        /* Allow access to RTC */
        PWR_BackupAccessCmd(ENABLE);

        /* Wiat for RTC APB rgisters synchronisation */
        RTC_WaitForSynchro();
    }
}

