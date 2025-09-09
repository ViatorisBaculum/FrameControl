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
    FLOW_GLOBAL_VARIABLE_BRIGHTNESS_LED3 = 8
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


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/