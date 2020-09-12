#ifndef __HAL_RTC_H
#define __HAL_RTC_H

#include <stdint.h>
#include "stm32f4xx_rtc.h"

#define IS_RTC_CLK_SRC(clk)         (((clk) == HAL_RTC_CLK_SRC_LSI) || ((clk) == HAL_RTC_CLK_SRC_LSE) || ((clk) == HAL_RTC_CLK_SRC_HSE))
#define IS_RTC_ALRAM(alarm)         (((alarm) == HAL_RTC_ALARM_A) || ((alarm) == HAL_RTC_ALARM_B))

typedef enum {
    HAL_RTC_CLK_SRC_LSI,
    HAL_RTC_CLK_SRC_LSE,
    HAL_RTC_CLK_SRC_HSE
} hal_rtc_clk_src_t;

typedef enum {
    HAL_RTC_ALARM_A = RTC_Alarm_A,
    HAL_RTC_ALARM_B = RTC_Alarm_B
} hal_rtc_alarm_t;

typedef enum {
    HAL_RTC_ALARM_DAY_IN_WEEK,
    HAL_RTC_ALARM_DAY_IN_MONTH
} hal_rtc_alarm_wdsel_t;

typedef enum {
    HAL_RTC_ALARM_MASK_NONE = RTC_AlarmMask_None,
    HAL_RTC_ALARM_MASK_DATE = RTC_AlarmMask_DateWeekDay,
    HAL_RTC_ALARM_MASK_HOUR = RTC_AlarmMask_Hours,
    HAL_RTC_ALARM_MASK_MIN = RTC_AlarmMask_Minutes,
    HAL_RTC_ALARM_MASK_SEC = RTC_AlarmMask_Seconds,
    HAL_RTC_ALARM_MASK_ALL = RTC_AlarmMask_All
} hal_rtc_alarm_mask_t;

typedef struct {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint16_t subsec;
} hal_rtc_time_t;

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t date;
    uint8_t weekday;
} hal_rtc_date_t;

typedef struct {
    hal_rtc_date_t date;
    hal_rtc_time_t time;
} hal_rtc_datetime_t;

typedef struct {
    hal_rtc_alarm_wdsel_t wdsel;
    uint8_t date;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    hal_rtc_alarm_mask_t mask;
} hal_rtc_alarm_cfg_t;

void hal_rtc_alarm_disable(hal_rtc_alarm_t alarm);
void hal_rtc_alarm_enable(hal_rtc_alarm_t alarm);
void hal_rtc_alarm_set(hal_rtc_alarm_t alarm, hal_rtc_alarm_cfg_t alarm_cfg);
void hal_rtc_time_get(hal_rtc_time_t *time);
void hal_rtc_time_set(hal_rtc_time_t time);
void hal_rtc_date_get(hal_rtc_date_t *date);
void hal_rtc_date_set(hal_rtc_date_t date);
void hal_rtc_datetime_get(hal_rtc_datetime_t *datetime);
void hal_rtc_datetime_set(hal_rtc_datetime_t datetime);
void hal_rtc_init(hal_rtc_clk_src_t clk_src);

#endif /* __HAL_RTC_H */
