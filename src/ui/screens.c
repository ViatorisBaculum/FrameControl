#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

static void event_handler_cb_main_battery_percentage_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_battery_percentage1(value);
        }
    }
}

static void event_handler_cb_main_brightness_percentage_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_brightness_led1(value);
        }
    }
}

static void event_handler_cb_main_button_power_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led1(value);
        }
    }
}

static void event_handler_cb_main_battery_percentage_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_battery_percentage2(value);
        }
    }
}

static void event_handler_cb_main_brightness_percentage_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_brightness_led2(value);
        }
    }
}

static void event_handler_cb_main_button_power_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led2(value);
        }
    }
}

static void event_handler_cb_main_battery_percentage_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_battery_percentage3(value);
        }
    }
}

static void event_handler_cb_main_brightness_percentage_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_brightness_led3(value);
        }
    }
}

static void event_handler_cb_main_button_power_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led3(value);
        }
    }
}

static void event_handler_cb_main_slider_brightness_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_brightness_led1(value);
        }
    }
}

static void event_handler_cb_main_slider_brightness_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_brightness_led2(value);
        }
    }
}

static void event_handler_cb_main_slider_brightness_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_brightness_led3(value);
        }
    }
}

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_use_pir_sensor(value);
        }
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_tabview_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_tabview_set_tab_bar_position(obj, LV_DIR_TOP);
            lv_tabview_set_tab_bar_size(obj, 32);
            add_style_tab_view(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // tab_home
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Start");
                    objects.tab_home = obj;
                    add_style_active_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // battery_percentage_1
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.battery_percentage_1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 100, 100);
                            lv_arc_set_bg_start_angle(obj, 100);
                            lv_arc_set_bg_end_angle(obj, 260);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_battery_percentage_1, LV_EVENT_ALL, 0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_battery_arc(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff0035ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // brightness_percentage_1
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.brightness_percentage_1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 100, 100);
                            lv_arc_set_bg_start_angle(obj, 280);
                            lv_arc_set_bg_end_angle(obj, 80);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_brightness_percentage_1, LV_EVENT_ALL, 0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_battery_arc(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // button_power_1
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_power_1 = obj;
                            lv_obj_set_pos(obj, 25, 25);
                            lv_obj_set_size(obj, 50, 50);
                            lv_obj_add_event_cb(obj, action_switch_led, LV_EVENT_VALUE_CHANGED, (void *)0);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_button_power_1, LV_EVENT_ALL, 0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_button_style(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_outline_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            // image_button_power_1
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_button_power_1 = obj;
                            lv_obj_set_pos(obj, 27, 27);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_coins);
                        }
                        {
                            // battery_percentage_2
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.battery_percentage_2 = obj;
                            lv_obj_set_pos(obj, 97, 82);
                            lv_obj_set_size(obj, 100, 100);
                            lv_arc_set_bg_start_angle(obj, 100);
                            lv_arc_set_bg_end_angle(obj, 260);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_battery_percentage_2, LV_EVENT_ALL, 0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_battery_arc(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff0035ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // brightness_percentage_2
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.brightness_percentage_2 = obj;
                            lv_obj_set_pos(obj, 97, 82);
                            lv_obj_set_size(obj, 100, 100);
                            lv_arc_set_bg_start_angle(obj, 280);
                            lv_arc_set_bg_end_angle(obj, 80);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_brightness_percentage_2, LV_EVENT_ALL, 0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_battery_arc(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // button_power_2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_power_2 = obj;
                            lv_obj_set_pos(obj, 122, 107);
                            lv_obj_set_size(obj, 50, 50);
                            lv_obj_add_event_cb(obj, action_switch_led, LV_EVENT_VALUE_CHANGED, (void *)1);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_button_power_2, LV_EVENT_ALL, 0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_button_style(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_outline_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            // image_button_power_2
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_button_power_2 = obj;
                            lv_obj_set_pos(obj, 124, 109);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_exodia);
                        }
                        {
                            // battery_percentage_3
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.battery_percentage_3 = obj;
                            lv_obj_set_pos(obj, 194, 0);
                            lv_obj_set_size(obj, 100, 100);
                            lv_arc_set_bg_start_angle(obj, 100);
                            lv_arc_set_bg_end_angle(obj, 260);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_battery_percentage_3, LV_EVENT_ALL, 0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_battery_arc(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff0035ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // brightness_percentage_3
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.brightness_percentage_3 = obj;
                            lv_obj_set_pos(obj, 194, 0);
                            lv_obj_set_size(obj, 100, 100);
                            lv_arc_set_bg_start_angle(obj, 280);
                            lv_arc_set_bg_end_angle(obj, 80);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_brightness_percentage_3, LV_EVENT_ALL, 0);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_battery_arc(obj);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_arc_width(obj, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            // button_power_3
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_power_3 = obj;
                            lv_obj_set_pos(obj, 219, 25);
                            lv_obj_set_size(obj, 50, 50);
                            lv_obj_add_event_cb(obj, action_switch_led, LV_EVENT_VALUE_CHANGED, (void *)2);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_button_power_3, LV_EVENT_ALL, 0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
                            add_style_button_style(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_outline_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            // image_button_power_3
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_button_power_3 = obj;
                            lv_obj_set_pos(obj, 221, 27);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_gods);
                        }
                    }
                }
                {
                    // tab_settings
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Einstellungen");
                    objects.tab_settings = obj;
                    add_style_active_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // image_object_frame_1
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_object_frame_1 = obj;
                            lv_obj_set_pos(obj, -3, -2);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_coins_inverted_small);
                        }
                        {
                            // Image_battery_percentage_1
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_battery_percentage_1 = obj;
                            lv_obj_set_pos(obj, 37, -6);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_ladezustand);
                        }
                        {
                            // Label_battery_percentage_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_battery_percentage_1 = obj;
                            lv_obj_set_pos(obj, 65, -8);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 %");
                        }
                        {
                            // Image_charging_date_1
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_charging_date_1 = obj;
                            lv_obj_set_pos(obj, 116, -6);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_ladedatum);
                        }
                        {
                            // Label_charging_date_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_charging_date_1 = obj;
                            lv_obj_set_pos(obj, 144, -8);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 s");
                        }
                        {
                            // Image_operating_hours_1
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_operating_hours_1 = obj;
                            lv_obj_set_pos(obj, 230, -6);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_betriebsstunden);
                        }
                        {
                            // Label_operating_hours_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_operating_hours_1 = obj;
                            lv_obj_set_pos(obj, 258, -8);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 s");
                        }
                        {
                            // Image_brightness_1
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_brightness_1 = obj;
                            lv_obj_set_pos(obj, 37, 19);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_helligkeit);
                        }
                        {
                            // button_brightness_down_1
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_brightness_down_1 = obj;
                            lv_obj_set_pos(obj, 66, 21);
                            lv_obj_set_size(obj, 22, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_PRESSED, (void *)10);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Label_button_brightness_down_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_button_brightness_down_1 = obj;
                                    lv_obj_set_pos(obj, 0, -2);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-");
                                }
                            }
                        }
                        {
                            // Label_brightness_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_brightness_1 = obj;
                            lv_obj_set_pos(obj, 91, 18);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 %");
                        }
                        {
                            // button_brightness_up_1
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_brightness_up_1 = obj;
                            lv_obj_set_pos(obj, 135, 21);
                            lv_obj_set_size(obj, 22, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_PRESSED, (void *)11);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Label_button_brightness_up_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_button_brightness_up_1 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "+");
                                }
                            }
                        }
                        {
                            // Slider_brightness_1
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.slider_brightness_1 = obj;
                            lv_obj_set_pos(obj, 171, 21);
                            lv_obj_set_size(obj, 112, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_VALUE_CHANGED, (void *)12);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_slider_brightness_1, LV_EVENT_ALL, 0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Line_settings_1
                            lv_obj_t *obj = lv_line_create(parent_obj);
                            objects.line_settings_1 = obj;
                            lv_obj_set_pos(obj, 0, 44);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            static lv_point_precise_t line_points[] = {
                                { 0, 0 },
                                { 294, 0 }
                            };
                            lv_line_set_points(obj, line_points, 2);
                            lv_obj_set_style_line_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // image_object_frame_2
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_object_frame_2 = obj;
                            lv_obj_set_pos(obj, -3, 55);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_exodia_inverted_small);
                        }
                        {
                            // Image_battery_percentage_2
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_battery_percentage_2 = obj;
                            lv_obj_set_pos(obj, 37, 51);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_ladezustand);
                        }
                        {
                            // Label_battery_percentage_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_battery_percentage_2 = obj;
                            lv_obj_set_pos(obj, 65, 49);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 %");
                        }
                        {
                            // Image_charging_date_2
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_charging_date_2 = obj;
                            lv_obj_set_pos(obj, 116, 51);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_ladedatum);
                        }
                        {
                            // Label_charging_date_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_charging_date_2 = obj;
                            lv_obj_set_pos(obj, 144, 49);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 s");
                        }
                        {
                            // Image_operating_hours_2
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_operating_hours_2 = obj;
                            lv_obj_set_pos(obj, 230, 51);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_betriebsstunden);
                        }
                        {
                            // Label_operating_hours_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_operating_hours_2 = obj;
                            lv_obj_set_pos(obj, 258, 49);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 s");
                        }
                        {
                            // Image_brightness_2
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_brightness_2 = obj;
                            lv_obj_set_pos(obj, 37, 76);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_helligkeit);
                        }
                        {
                            // button_brightness_down_2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_brightness_down_2 = obj;
                            lv_obj_set_pos(obj, 66, 78);
                            lv_obj_set_size(obj, 22, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_PRESSED, (void *)20);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Label_button_brightness_down_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_button_brightness_down_2 = obj;
                                    lv_obj_set_pos(obj, 0, -2);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-");
                                }
                            }
                        }
                        {
                            // Label_brightness_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_brightness_2 = obj;
                            lv_obj_set_pos(obj, 91, 75);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 %");
                        }
                        {
                            // button_brightness_up_2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_brightness_up_2 = obj;
                            lv_obj_set_pos(obj, 135, 78);
                            lv_obj_set_size(obj, 22, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_PRESSED, (void *)21);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Label_button_brightness_up_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_button_brightness_up_2 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "+");
                                }
                            }
                        }
                        {
                            // Slider_brightness_2
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.slider_brightness_2 = obj;
                            lv_obj_set_pos(obj, 171, 78);
                            lv_obj_set_size(obj, 112, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_VALUE_CHANGED, (void *)22);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_slider_brightness_2, LV_EVENT_ALL, 0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Line_settings_2
                            lv_obj_t *obj = lv_line_create(parent_obj);
                            objects.line_settings_2 = obj;
                            lv_obj_set_pos(obj, 0, 101);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            static lv_point_precise_t line_points[] = {
                                { 0, 0 },
                                { 294, 0 }
                            };
                            lv_line_set_points(obj, line_points, 2);
                            lv_obj_set_style_line_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // image_object_frame_3
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_object_frame_3 = obj;
                            lv_obj_set_pos(obj, -3, 111);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_gods_inverted_small);
                        }
                        {
                            // Image_battery_percentage_3
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_battery_percentage_3 = obj;
                            lv_obj_set_pos(obj, 37, 108);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_ladezustand);
                        }
                        {
                            // Label_battery_percentage_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_battery_percentage_3 = obj;
                            lv_obj_set_pos(obj, 65, 106);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 %");
                        }
                        {
                            // Image_charging_date_3
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_charging_date_3 = obj;
                            lv_obj_set_pos(obj, 116, 108);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_ladedatum);
                        }
                        {
                            // Label_charging_date_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_charging_date_3 = obj;
                            lv_obj_set_pos(obj, 144, 106);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 s");
                        }
                        {
                            // Image_operating_hours_3
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_operating_hours_3 = obj;
                            lv_obj_set_pos(obj, 230, 108);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_betriebsstunden);
                        }
                        {
                            // Label_operating_hours_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_operating_hours_3 = obj;
                            lv_obj_set_pos(obj, 258, 106);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 s");
                        }
                        {
                            // Image_brightness_3
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_brightness_3 = obj;
                            lv_obj_set_pos(obj, 37, 133);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_helligkeit);
                        }
                        {
                            // button_brightness_down_3
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_brightness_down_3 = obj;
                            lv_obj_set_pos(obj, 66, 135);
                            lv_obj_set_size(obj, 22, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_PRESSED, (void *)30);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Label_button_brightness_down_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_button_brightness_down_3 = obj;
                                    lv_obj_set_pos(obj, 0, -2);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-");
                                }
                            }
                        }
                        {
                            // Label_brightness_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_brightness_3 = obj;
                            lv_obj_set_pos(obj, 91, 132);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 %");
                        }
                        {
                            // button_brightness_up_3
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.button_brightness_up_3 = obj;
                            lv_obj_set_pos(obj, 135, 135);
                            lv_obj_set_size(obj, 22, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_PRESSED, (void *)31);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Label_button_brightness_up_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_button_brightness_up_3 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "+");
                                }
                            }
                        }
                        {
                            // Slider_brightness_3
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.slider_brightness_3 = obj;
                            lv_obj_set_pos(obj, 171, 135);
                            lv_obj_set_size(obj, 112, 12);
                            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_VALUE_CHANGED, (void *)32);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_slider_brightness_3, LV_EVENT_ALL, 0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Line_settings_3
                            lv_obj_t *obj = lv_line_create(parent_obj);
                            objects.line_settings_3 = obj;
                            lv_obj_set_pos(obj, 0, 158);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            static lv_point_precise_t line_points[] = {
                                { 0, 0 },
                                { 294, 0 }
                            };
                            lv_line_set_points(obj, line_points, 2);
                            lv_obj_set_style_line_color(obj, lv_color_hex(0xff0035ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Image_automatic_mode
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_automatic_mode = obj;
                            lv_obj_set_pos(obj, 54, 167);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_automatikmodus);
                        }
                        {
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.obj2 = obj;
                            lv_obj_set_pos(obj, 84, 165);
                            lv_obj_set_size(obj, 30, 16);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff303030), LV_PART_KNOB | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_CHECKED);
                        }
                        {
                            // Image_Absence_control
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            objects.image_absence_control = obj;
                            lv_obj_set_pos(obj, 180, 167);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_image_set_src(obj, &img_symbol_abwesenheitskontrolle);
                        }
                        {
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.obj0 = obj;
                            lv_obj_set_pos(obj, 210, 165);
                            lv_obj_set_size(obj, 30, 17);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, 0);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff303030), LV_PART_KNOB | LV_STATE_CHECKED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00d5ff), LV_PART_INDICATOR | LV_STATE_CHECKED);
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        int32_t new_val = get_var_battery_percentage1();
        int32_t cur_val = lv_arc_get_value(objects.battery_percentage_1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.battery_percentage_1;
            lv_arc_set_value(objects.battery_percentage_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_brightness_led1();
        int32_t cur_val = lv_arc_get_value(objects.brightness_percentage_1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.brightness_percentage_1;
            lv_arc_set_value(objects.brightness_percentage_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led1();
        bool cur_val = lv_obj_has_state(objects.button_power_1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.button_power_1;
            if (new_val) lv_obj_add_state(objects.button_power_1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.button_power_1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_battery_percentage2();
        int32_t cur_val = lv_arc_get_value(objects.battery_percentage_2);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.battery_percentage_2;
            lv_arc_set_value(objects.battery_percentage_2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_brightness_led2();
        int32_t cur_val = lv_arc_get_value(objects.brightness_percentage_2);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.brightness_percentage_2;
            lv_arc_set_value(objects.brightness_percentage_2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led2();
        bool cur_val = lv_obj_has_state(objects.button_power_2, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.button_power_2;
            if (new_val) lv_obj_add_state(objects.button_power_2, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.button_power_2, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_battery_percentage3();
        int32_t cur_val = lv_arc_get_value(objects.battery_percentage_3);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.battery_percentage_3;
            lv_arc_set_value(objects.battery_percentage_3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_brightness_led3();
        int32_t cur_val = lv_arc_get_value(objects.brightness_percentage_3);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.brightness_percentage_3;
            lv_arc_set_value(objects.brightness_percentage_3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led3();
        bool cur_val = lv_obj_has_state(objects.button_power_3, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.button_power_3;
            if (new_val) lv_obj_add_state(objects.button_power_3, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.button_power_3, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_brightness_led1();
        int32_t cur_val = lv_slider_get_value(objects.slider_brightness_1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.slider_brightness_1;
            lv_slider_set_value(objects.slider_brightness_1, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_brightness_led2();
        int32_t cur_val = lv_slider_get_value(objects.slider_brightness_2);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.slider_brightness_2;
            lv_slider_set_value(objects.slider_brightness_2, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_brightness_led3();
        int32_t cur_val = lv_slider_get_value(objects.slider_brightness_3);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.slider_brightness_3;
            lv_slider_set_value(objects.slider_brightness_3, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_use_pir_sensor();
        bool cur_val = lv_obj_has_state(objects.obj0, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            if (new_val) lv_obj_add_state(objects.obj0, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj0, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
