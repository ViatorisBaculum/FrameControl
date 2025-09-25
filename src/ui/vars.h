#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_BATTERY_PERCENTAGE1 = 0,
    FLOW_GLOBAL_VARIABLE_BATTERY_PERCENTAGE2 = 1,
    FLOW_GLOBAL_VARIABLE_BATTERY_PERCENTAGE3 = 2,
    FLOW_GLOBAL_VARIABLE_STATE_LED1 = 3,
    FLOW_GLOBAL_VARIABLE_STATE_LED2 = 4,
    FLOW_GLOBAL_VARIABLE_STATE_LED3 = 5,
    FLOW_GLOBAL_VARIABLE_BRIGHTNESS_LED1 = 6,
    FLOW_GLOBAL_VARIABLE_BRIGHTNESS_LED2 = 7,
    FLOW_GLOBAL_VARIABLE_BRIGHTNESS_LED3 = 8,
    FLOW_GLOBAL_VARIABLE_LAST_CHARGED1 = 9,
    FLOW_GLOBAL_VARIABLE_LAST_CHARGED2 = 10,
    FLOW_GLOBAL_VARIABLE_LAST_CHARGED3 = 11,
    FLOW_GLOBAL_VARIABLE_LED_ON_TIME1 = 12,
    FLOW_GLOBAL_VARIABLE_LED_ON_TIME2 = 13,
    FLOW_GLOBAL_VARIABLE_LED_ON_TIME3 = 14,
    FLOW_GLOBAL_VARIABLE_USE_PIR_SENSOR = 15,
    FLOW_GLOBAL_VARIABLE_USE_AUTOMATIC_MODE = 16
};

// Native global variables

extern float get_var_battery_percentage1();
extern void set_var_battery_percentage1(float value);
extern float get_var_battery_percentage2();
extern void set_var_battery_percentage2(float value);
extern float get_var_battery_percentage3();
extern void set_var_battery_percentage3(float value);
extern bool get_var_state_led1();
extern void set_var_state_led1(bool value);
extern bool get_var_state_led2();
extern void set_var_state_led2(bool value);
extern bool get_var_state_led3();
extern void set_var_state_led3(bool value);
extern float get_var_brightness_led1();
extern void set_var_brightness_led1(float value);
extern float get_var_brightness_led2();
extern void set_var_brightness_led2(float value);
extern float get_var_brightness_led3();
extern void set_var_brightness_led3(float value);
extern int32_t get_var_last_charged1();
extern void set_var_last_charged1(int32_t value);
extern int32_t get_var_last_charged2();
extern void set_var_last_charged2(int32_t value);
extern int32_t get_var_last_charged3();
extern void set_var_last_charged3(int32_t value);
extern int32_t get_var_led_on_time1();
extern void set_var_led_on_time1(int32_t value);
extern int32_t get_var_led_on_time2();
extern void set_var_led_on_time2(int32_t value);
extern int32_t get_var_led_on_time3();
extern void set_var_led_on_time3(int32_t value);
extern bool get_var_use_pir_sensor();
extern void set_var_use_pir_sensor(bool value);
extern bool get_var_use_automatic_mode();
extern void set_var_use_automatic_mode(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/