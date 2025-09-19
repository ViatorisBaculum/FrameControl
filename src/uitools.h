// Only declare brightness helpers here; battery and LED state
// accessors are declared in ui/vars.h and implemented in uitools.c.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void set_var_brightness_led1(float value);
void set_var_brightness_led2(float value);
void set_var_brightness_led3(float value);

float get_var_brightness_led1();
float get_var_brightness_led2();
float get_var_brightness_led3();

void set_var_operating_hours1(uint32_t value);
void set_var_operating_hours2(uint32_t value);
void set_var_operating_hours3(uint32_t value);

void uitools_style_main_tabview(void);

#ifdef __cplusplus
}
#endif
