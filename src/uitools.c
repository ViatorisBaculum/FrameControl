// Central place for UI-related helpers and variable storage

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <lvgl.h>

#include "uitools.h"
#include "ui/fonts.h"
#include "ui/vars.h"
#include "ui/screens.h"
#include "ui/actions.h"

extern lv_obj_t *tick_value_change_obj;

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
static uint32_t led_on_time1;
static uint32_t led_on_time2;
static uint32_t led_on_time3;
static uint32_t last_charged1;
static uint32_t last_charged2;
static uint32_t last_charged3;

typedef struct
{
    bool active;
    uint8_t phase;
    uint8_t progress;
    uint32_t lastTick;
    float targetBattery;
    float targetBrightness;
} PendingAnim;

static PendingAnim pendingAnim[3];
static const uint32_t kPendingAnimStepMs = 2;
static const uint8_t kPendingAnimStep = 2;

static float get_desired_brightness(int idx)
{
    switch (idx)
    {
    case 0:
        return brightness_led1;
    case 1:
        return brightness_led2;
    case 2:
        return brightness_led3;
    default:
        return 0.0f;
    }
}

static void update_brightness_visuals(int idx, float value)
{
    if (value < 0.0f) value = 0.0f;
    if (value > 100.0f) value = 100.0f;

    int pct = (int)(value + 0.5f);
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;

    lv_obj_t *label = NULL;

    switch (idx)
    {
    case 0:
        label = objects.label_brightness_1;
        break;
    case 1:
        label = objects.label_brightness_2;
        break;
    case 2:
        label = objects.label_brightness_3;
        break;
    default:
        break;
    }

    if (label != NULL)
    {
        lv_label_set_text_fmt(label, "%d%%", pct);
    }
}

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

void set_var_brightness_led1(float value) {
    brightness_led1 = value;
    update_brightness_visuals(0, value);
}

float get_var_brightness_led1() { return brightness_led1; }

void set_var_brightness_led2(float value) {
    brightness_led2 = value;
    update_brightness_visuals(1, value);
}

float get_var_brightness_led2() { return brightness_led2; }

void set_var_brightness_led3(float value) {
    brightness_led3 = value;
    update_brightness_visuals(2, value);
}

float get_var_brightness_led3() { return brightness_led3; }

void set_var_led_on_time1(int32_t value) {
    led_on_time1 = value;
    if (objects.label_operating_hours_1 != NULL) {
        if (value >= 60 * 60 * 24) {
            int32_t days = value / (60 * 60 * 24);
            lv_label_set_text_fmt(objects.label_operating_hours_1, "%ld d", (long)days);
            return;
        } else if (value >= 60 * 60) {
            int32_t hours = value / (60 * 60);
            lv_label_set_text_fmt(objects.label_operating_hours_1, "%ld h", (long)hours);
            return;
        } else if (value >= 60) {
            int32_t minutes = value / 60;
            lv_label_set_text_fmt(objects.label_operating_hours_1, "%ld m", (long)minutes);
            return;
        } else {
            lv_label_set_text_fmt(objects.label_operating_hours_1, "%ld s", (long)value);
        }
    }
}

int32_t get_var_led_on_time1() { return led_on_time1; }    

void set_var_led_on_time2(int32_t value) {
    led_on_time2 = value;
    if (objects.label_operating_hours_2 != NULL) {
        if (value >= 60 * 60 * 24) {
            int32_t days = value / (60 * 60 * 24);
            lv_label_set_text_fmt(objects.label_operating_hours_2, "%ld d", (long)days);
            return;
        } else if (value >= 60 * 60) {
            int32_t hours = value / (60 * 60);
            lv_label_set_text_fmt(objects.label_operating_hours_2, "%ld h", (long)hours);
            return;
        } else if (value >= 60) {
            int32_t minutes = value / 60;
            lv_label_set_text_fmt(objects.label_operating_hours_2, "%ld m", (long)minutes);
            return;
        } else {
            lv_label_set_text_fmt(objects.label_operating_hours_2, "%ld s", (long)value);
        }
    }
}

int32_t get_var_led_on_time2() { return led_on_time2; }

void set_var_led_on_time3(int32_t value) {
    led_on_time3 = value;
    if (objects.label_operating_hours_3 != NULL) {
        if (value >= 60 * 60 * 24) {
            int32_t days = value / (60 * 60 * 24);
            lv_label_set_text_fmt(objects.label_operating_hours_3, "%ld d", (long)days);
            return;
        } else if (value >= 60 * 60) {
            int32_t hours = value / (60 * 60);
            lv_label_set_text_fmt(objects.label_operating_hours_3, "%ld h", (long)hours);
            return;
        } else if (value >= 60) {
            int32_t minutes = value / 60;
            lv_label_set_text_fmt(objects.label_operating_hours_3, "%ld m", (long)minutes);
            return;
        } else {
            lv_label_set_text_fmt(objects.label_operating_hours_3, "%ld s", (long)value);
        }
    }
}

int32_t get_var_led_on_time3() { return led_on_time3; }

int32_t get_var_last_charged1() { return last_charged1; }
void set_var_last_charged1(int32_t value) {
    last_charged1 = value;
    if (objects.label_charging_date_1 != NULL) {
        if (value >= 60 * 60 * 24) {
            int32_t days = value / (60 * 60 * 24);
            lv_label_set_text_fmt(objects.label_charging_date_1, "%ld d", (long)days);
            return;
        } else if (value >= 60 * 60) {
            int32_t hours = value / (60 * 60);
            lv_label_set_text_fmt(objects.label_charging_date_1, "%ld h", (long)hours);
            return;
        } else if (value >= 60) {
            int32_t minutes = value / 60;
            lv_label_set_text_fmt(objects.label_charging_date_1, "%ld m", (long)minutes);
            return;
        } else {
            lv_label_set_text_fmt(objects.label_charging_date_1, "%ld s", (long)value);
        }
    }
}

int32_t get_var_last_charged2() { return last_charged2; }
void set_var_last_charged2(int32_t value) {
    last_charged2 = value;
    if (objects.label_charging_date_2 != NULL) {
        if (value >= 60 * 60 * 24) {
            int32_t days = value / (60 * 60 * 24);
            lv_label_set_text_fmt(objects.label_charging_date_2, "%ld d", (long)days);
            return;
        } else if (value >= 60 * 60) {
            int32_t hours = value / (60 * 60);
            lv_label_set_text_fmt(objects.label_charging_date_2, "%ld h", (long)hours);
            return;
        } else if (value >= 60) {
            int32_t minutes = value / 60;
            lv_label_set_text_fmt(objects.label_charging_date_2, "%ld m", (long)minutes);
            return;
        } else {
            lv_label_set_text_fmt(objects.label_charging_date_2, "%ld s", (long)value);
        }
    }
}

int32_t get_var_last_charged3() { return last_charged3; }
void set_var_last_charged3(int32_t value) {
    last_charged3 = value;
    if (objects.label_charging_date_3 != NULL) {
        if (value >= 60 * 60 * 24) {
            int32_t days = value / (60 * 60 * 24);
            lv_label_set_text_fmt(objects.label_charging_date_3, "%ld d", (long)days);
            return;
        } else if (value >= 60 * 60) {
            int32_t hours = value / (60 * 60);
            lv_label_set_text_fmt(objects.label_charging_date_3, "%ld h", (long)hours);
            return;
        } else if (value >= 60) {
            int32_t minutes = value / 60;
            lv_label_set_text_fmt(objects.label_charging_date_3, "%ld m", (long)minutes);
            return;
        } else {
            lv_label_set_text_fmt(objects.label_charging_date_3, "%ld s", (long)value);
        }
    }
}

static void set_battery_display(int idx, float value)
{
    if (value < 0.0f) value = 0.0f;
    if (value > 100.0f) value = 100.0f;

    switch (idx)
    {
    case 0:
        set_var_battery_percentage1(value);
        break;
    case 1:
        set_var_battery_percentage2(value);
        break;
    case 2:
        set_var_battery_percentage3(value);
        break;
    default:
        break;
    }
}

static void set_brightness_display(int idx, float value)
{
    update_brightness_visuals(idx, value);
}

static void apply_target_display(int idx)
{
    set_battery_display(idx, pendingAnim[idx].targetBattery);
    set_brightness_display(idx, pendingAnim[idx].targetBrightness);
}

void uitools_update_channel_feedback(int idx, float battery_pct, float brightness_pct, bool pending)
{
    if (idx < 0 || idx >= 3)
    {
        return;
    }

    PendingAnim *anim = &pendingAnim[idx];
    anim->targetBattery = battery_pct;
    anim->targetBrightness = brightness_pct;

    float displayBrightness = pending ? get_desired_brightness(idx) : brightness_pct;
    update_brightness_visuals(idx, displayBrightness);

    if (!pending)
    {
        anim->active = false;
        anim->phase = 0;
        anim->progress = 0;
        anim->lastTick = 0;
        apply_target_display(idx);
        return;
    }

    if (!anim->active)
    {
        anim->active = true;
        anim->phase = 0;
        anim->progress = 0;
        anim->lastTick = 0;
    }
}

void uitools_tick_pending(void)
{
    uint32_t now = lv_tick_get();
    for (int idx = 0; idx < 3; ++idx)
    {
        PendingAnim *anim = &pendingAnim[idx];
        if (!anim->active)
        {
            continue;
        }

        if (anim->lastTick != 0 && (now - anim->lastTick) < kPendingAnimStepMs)
        {
            continue;
        }

        anim->lastTick = now;
        float battery = 0.0f;
        switch (anim->phase)
        {
        case 0:
            battery = (float)anim->progress;
            break;
        case 1:
            battery = 100.0f;
            break;
        case 2:
            battery = 100.0f - (float)anim->progress;
            break;
        default:
            battery = 0.0f;
            break;
        }

        set_battery_display(idx, battery);
        update_brightness_visuals(idx, get_desired_brightness(idx));

        anim->progress = (uint8_t)(anim->progress + kPendingAnimStep);
        if (anim->progress > 100)
        {
            anim->progress = 0;
            anim->phase = (uint8_t)((anim->phase + 1) & 0x03);
        }
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
        if (value && get_var_brightness_led1() <= 0.0f)
        {
            set_var_brightness_led1(100.0f);
        }
        set_var_state_led1(value);
        break;
    case 1:
        if (value && get_var_brightness_led2() <= 0.0f)
        {
            set_var_brightness_led2(100.0f);
        }
        set_var_state_led2(value);
        break;
    case 2:
        if (value && get_var_brightness_led3() <= 0.0f)
        {
            set_var_brightness_led3(100.0f);
        }
        set_var_state_led3(value);
        break;
    default:
        return;
    }
    
    setLEDState_c();
}

void uitools_style_main_tabview(void)
{
    lv_obj_t *tab_page = objects.tab_home;
    if (tab_page == NULL) {
        return;
    }

    lv_obj_t *content = lv_obj_get_parent(tab_page);
    if (content == NULL) {
        return;
    }

    lv_obj_t *tabview = lv_obj_get_parent(content);
    if (tabview == NULL) {
        tabview = content;
    }

    lv_obj_t *tab_bar = lv_tabview_get_tab_bar(tabview);
    if (tab_bar == NULL) {
        return;
    }

    lv_obj_set_style_bg_color(tab_bar, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tab_bar, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(tab_bar, lv_color_hex(0xff000000), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tab_bar, LV_OPA_COVER, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tab_bar, lv_color_hex(0xffffffff), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(tab_bar, &lv_font_montserrat_14, LV_PART_ITEMS | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(tab_bar, lv_color_hex(0xff000000), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(tab_bar, LV_OPA_COVER, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(tab_bar, lv_color_hex(0xffffffff), LV_PART_ITEMS | LV_STATE_CHECKED);

    lv_obj_set_style_border_opa(tab_bar, LV_OPA_0, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(tab_bar, LV_OPA_0, LV_PART_ITEMS | LV_STATE_CHECKED);
}

