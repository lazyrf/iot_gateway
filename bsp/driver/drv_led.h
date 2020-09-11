#ifndef __DRV_LED_H
#define __DRV_LED_H

void drv_led_toggle(int idx);
void drv_led_off(int idx);
void drv_led_on(int idx);
void drv_led_all_toggle(void);
void drv_led_all_off(void);
void drv_led_all_on(void);
void drv_led_init(void);

#endif /* __DRV_LED_H */
