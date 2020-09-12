#include "drv_rtc.h"
#include "hal_rtc.h"
#include "board.h"
#include "assert.h"
#include "igw_errno.h"

void drv_rtc_alarm_disable(int alarm_idx)
{
    hal_rtc_alarm_disable(rtc_alarm_list[alarm_idx]);
}

void drc_rtc_alarm_enable(int alarm_idx)
{
    hal_rtc_alarm_enable(rtc_alarm_list[alarm_idx]);
}

void drc_rtc_alarm_set(int alarm_idx, drv_rtc_alarm_t alarm)
{
    hal_rtc_alarm_cfg_t alrm_cfg;
    hal_rtc_alarm_t alrm;

    assert(IS_RTC_ALARM_NUM(alarm_idx));

    alrm = rtc_alarm_list[alarm_idx];
    alrm_cfg.date = alarm.datetime.date;
    alrm_cfg.hour = alarm.datetime.hour;
    alrm_cfg.min = alarm.datetime.min;
    alrm_cfg.sec = alarm.datetime.sec;
    alrm_cfg.wdsel = alarm.wdsel;

    if (alarm.mask.value == 0) {
        alrm_cfg.mask = HAL_RTC_ALARM_MASK_NONE;
    } else {
        if (alarm.mask.field.date) {
            alrm_cfg.mask |= HAL_RTC_ALARM_MASK_DATE;
        }

        if (alarm.mask.field.hour) {
            alrm_cfg.mask |= HAL_RTC_ALARM_MASK_HOUR;
        }

        if (alarm.mask.field.min) {
            alrm_cfg.mask |= HAL_RTC_ALARM_MASK_MIN;
        }
        if (alarm.mask.field.sec) {
            alrm_cfg.mask |= HAL_RTC_ALARM_MASK_SEC;
        }
        if (alarm.mask.field.hour) {
            alrm_cfg.mask |= HAL_RTC_ALARM_MASK_HOUR;
        }
    }

    hal_rtc_alarm_set(alrm, alrm_cfg);
}

void drv_rtc_datetime_get(int *year, int *month, int *date, int *weekday,
        int *hour, int *min, int *sec)
{
    hal_rtc_datetime_t datetime;

    hal_rtc_datetime_get(&datetime);

    *year = datetime.date.year;
    *month = datetime.date.month;
    *date = datetime.date.date;
    *weekday = datetime.date.weekday;
    *hour = datetime.time.hour;
    *min = datetime.time.min;
    *sec = datetime.time.sec;
}

igw_err_t drv_rtc_datetime_set(int year, int month, int date, int weekday,
        int hour, int min, int sec)
{
    hal_rtc_datetime_t datetime;

    if (year > 99 || month == 0 || month > 12 || date == 0 ||
            hour > 23 || min > 59 || sec > 59) {
        return IGW_ERR_DRV_RTC_DATETIME_SET;
    }

    datetime.date.year = year;
    datetime.date.month = month;
    datetime.date.date = date;
    datetime.date.weekday = weekday;

    datetime.time.hour = hour;
    datetime.time.min = min;
    datetime.time.sec = sec;

    hal_rtc_datetime_set(datetime);

    return IGW_ERR_OK;
}

void drv_rtc_init(void)
{
    hal_rtc_init(BOARD_RTC_CLK_SRC);
}
