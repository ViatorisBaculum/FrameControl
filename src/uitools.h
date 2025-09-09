// Only declare brightness helpers here; battery and LED state
// accessors are declared in `ui/vars.h` and implemented in uitools.c.

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

#ifdef __cplusplus
}
#endif
