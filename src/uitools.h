// Only declare brightness helpers here; battery and LED state
// accessors are declared in ui/vars.h and implemented in uitools.c.

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void set_var_brightness_led1(float value);
    void set_var_brightness_led2(float value);
    void set_var_brightness_led3(float value);

    float get_var_brightness_led1();
    float get_var_brightness_led2();
    float get_var_brightness_led3();

    int32_t get_var_last_charged1();
    int32_t get_var_last_charged2();
    int32_t get_var_last_charged3();

    int32_t get_var_led_on_time1();
    int32_t get_var_led_on_time2();
    int32_t get_var_led_on_time3();

    void set_var_operating_hours1(int32_t value);
    void set_var_operating_hours2(int32_t value);
    void set_var_operating_hours3(int32_t value);

    void set_var_last_charged1(int32_t value);
    void set_var_last_charged2(int32_t value);
    void set_var_last_charged3(int32_t value);

    void set_var_led_on_time1(int32_t value);
    void set_var_led_on_time2(int32_t value);
    void set_var_led_on_time3(int32_t value);

    void uitools_update_channel_feedback(int idx, float battery_pct, float brightness_pct, bool pending);
    void uitools_tick_pending(void);

    void uitools_style_main_tabview(void);

#ifdef __cplusplus
}
#endif
