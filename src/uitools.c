// Central place for UI-related helpers and variable storage

#include <stdio.h>
#include <stdbool.h>
#include <lvgl.h>

#include "uitools.h"
#include "ui/vars.h"
#include "ui/screens.h"
#include "ui/actions.h"

// Backing storage for variables exposed via ui/vars.h and uitools.h
static float battery_percentage1;
static float battery_percentage2;
static float battery_percentage3;
static float brightness_led1;
static float brightness_led2;
static float brightness_led3;
static bool state_led1;
static bool state_led2;
static bool state_led3;

// Implementations for ui/vars.h (battery + LED states)
float get_var_battery_percentage1() { return battery_percentage1; }
void set_var_battery_percentage1(float value) { 
    battery_percentage1 = value; 
    if (objects.label_battery_percentage_1 != NULL) {
        int pct = (int)(battery_percentage1 + 0.5f);
        lv_label_set_text_fmt(objects.label_battery_percentage_1, "%d%%", pct);
    }
}

float get_var_battery_percentage2() { return battery_percentage2; }
void set_var_battery_percentage2(float value) { 
    battery_percentage2 = value; 
    if (objects.label_battery_percentage_2 != NULL) {
        int pct = (int)(battery_percentage2 + 0.5f);
        lv_label_set_text_fmt(objects.label_battery_percentage_2, "%d%%", pct);
    }
}

float get_var_battery_percentage3() { return battery_percentage3; }
void set_var_battery_percentage3(float value) { 
    battery_percentage3 = value; 
    if (objects.label_battery_percentage_3 != NULL) {
        int pct = (int)(battery_percentage3 + 0.5f);
        lv_label_set_text_fmt(objects.label_battery_percentage_3, "%d%%", pct);
    }
}

bool get_var_state_led1() { return state_led1; }
void set_var_state_led1(bool value) { state_led1 = value; }

bool get_var_state_led2() { return state_led2; }
void set_var_state_led2(bool value) { state_led2 = value; }

bool get_var_state_led3() { return state_led3; }
void set_var_state_led3(bool value) { state_led3 = value; }

// Brightness helpers exposed via uitools.h
void set_var_brightness_led1(float value) { brightness_led1 = value; }
void set_var_brightness_led2(float value) { brightness_led2 = value; }
void set_var_brightness_led3(float value) { brightness_led3 = value; }

float get_var_brightness_led1() { return brightness_led1; }
float get_var_brightness_led2() { return brightness_led2; }
float get_var_brightness_led3() { return brightness_led3; }

void set_var_operating_hours1(uint32_t value) {
    if (objects.label_operating_hours_1 != NULL) {
        lv_label_set_text_fmt(objects.label_operating_hours_1, "%u h", value);
    }
}

void set_var_operating_hours2(uint32_t value) {
    if (objects.label_operating_hours_2 != NULL) {
        lv_label_set_text_fmt(objects.label_operating_hours_2, "%u h", value);
    }
}

void set_var_operating_hours3(uint32_t value) {
    if (objects.label_operating_hours_3 != NULL) {
        lv_label_set_text_fmt(objects.label_operating_hours_3, "%u h", value);
    }
}

// UI event: refresh brightness from slider and +/- buttons
void action_change_brightness(lv_event_t *e)
{
    lv_obj_t *target = (lv_obj_t *)lv_event_get_target(e);

    int channel = -1; // 0..2
    enum Kind { Kind_Slider, Kind_Down, Kind_Up } kind;

    if (target == objects.slider_brightness_1) {
        channel = 0; kind = Kind_Slider;
    } else if (target == objects.slider_brightness_2) {
        channel = 1; kind = Kind_Slider;
    } else if (target == objects.slider_brightness_3) {
        channel = 2; kind = Kind_Slider;
    } else if (target == objects.button_brightness_down_1) {
        channel = 0; kind = Kind_Down;
    } else if (target == objects.button_brightness_down_2) {
        channel = 1; kind = Kind_Down;
    } else if (target == objects.button_brightness_down_3) {
        channel = 2; kind = Kind_Down;
    } else if (target == objects.button_brightness_up_1) {
        channel = 0; kind = Kind_Up;
    } else if (target == objects.button_brightness_up_2) {
        channel = 1; kind = Kind_Up;
    } else if (target == objects.button_brightness_up_3) {
        channel = 2; kind = Kind_Up;
    } else {
        return;
    }

    lv_obj_t *slider = NULL;
    lv_obj_t *label = NULL;
    switch (channel) {
    case 0:
        slider = objects.slider_brightness_1;
        label  = objects.label_brightness_1;
        break;
    case 1:
        slider = objects.slider_brightness_2;
        label  = objects.label_brightness_2;
        break;
    case 2:
        slider = objects.slider_brightness_3;
        label  = objects.label_brightness_3;
        break;
    default:
        return;
    }

    int value = lv_slider_get_value(slider);
    // Round to nearest 5 for consistent step increments
    value = ((value + 2) / 5) * 5;
    if (kind == Kind_Down) {
        value -= 5;
    } else if (kind == Kind_Up) {
        value += 5;
    } else { // slider moved
        value = lv_slider_get_value(target);
    }

    if (value < 0) value = 0;
    if (value > 100) value = 100;

    if (target != slider) {
        lv_slider_set_value(slider, value, LV_ANIM_OFF);
    }

    char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", value);
    lv_label_set_text(label, buf);

    switch (channel) {
    case 0: set_var_brightness_led1(value); break;
    case 1: set_var_brightness_led2(value); break;
    case 2: set_var_brightness_led3(value); break;
    }
}

// Persist helper from main.cpp (C-linkage wrapper)
extern void setLEDState_c(void);

// UI event: mirror button state to variable and persist
void action_switch_led(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED && code != LV_EVENT_RELEASED) return;

    int userData = (int)lv_event_get_user_data(e); // 0,1,2
    lv_obj_t *ta = lv_event_get_target(e);
    bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);

    switch (userData)
    {
    case 0:
        set_var_state_led1(value);
        break;
    case 1:
        set_var_state_led2(value);
        break;
    case 2:
        set_var_state_led3(value);
        break;
    default:
        return;
    }
    setLEDState_c();
}
