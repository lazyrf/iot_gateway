#ifndef __DRV_RTC_H
#define __DRV_RTC_H

#include <stdint.h>
#include "igw_errno.h"

#define IS_RTC_ALARM_NUM(idx)       ((idx) < BOARD_RTC_ALARM_NUM)

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t date;
    uint8_t weekday;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} drv_rtc_datetime_t;

typedef struct {
    drv_rtc_datetime_t datetime;
    union {
        uint8_t value;
        struct {
            uint8_t year: 1;
            uint8_t month: 1;
            uint8_t date: 1;
            uint8_t hour: 1;
            uint8_t min: 1;
            uint8_t sec: 1;
            uint8_t padding: 2;
        } field;
    } mask;
    uint8_t wdsel;
} drv_rtc_alarm_t;

void drv_rtc_alarm_disable(int alarm_idx);
void drc_rtc_alarm_enable(int alarm_idx);
void drc_rtc_alarm_set(int alarm_idx, drv_rtc_alarm_t alarm);
void drv_rtc_datetime_get(int *year, int *month, int *date, int *weekday, int *hour, int *min, int *sec);
igw_err_t drv_rtc_datetime_set(int year, int month, int date, int weekday, int hour, int min, int sec);
void drv_rtc_init(void);

#endif /* __DRV_RTC_H */
