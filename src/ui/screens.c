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

static void event_handler_cb_main_btn1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led1(value);
        }
    }
}

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led1(value);
        }
    }
}

static void event_handler_cb_main_btn2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led2(value);
        }
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led2(value);
        }
    }
}

static void event_handler_cb_main_btn2_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led3(value);
        }
    }
}

static void event_handler_cb_main_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_state_led3(value);
        }
    }
}

static void event_handler_cb_main_arc1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_battery_percentage1(value);
        }
    }
}

static void event_handler_cb_main_arc2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_battery_percentage2(value);
        }
    }
}

static void event_handler_cb_main_arc3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_battery_percentage3(value);
        }
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff15203d), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // btn1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn1 = obj;
            lv_obj_set_pos(obj, 13, 179);
            lv_obj_set_size(obj, 80, 50);
            lv_obj_add_event_cb(obj, action_switch_led, LV_EVENT_RELEASED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn1, LV_EVENT_ALL, 0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff18345d), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0050), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "LED 1");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, 0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffff0050), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                }
            }
        }
        {
            // btn2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn2 = obj;
            lv_obj_set_pos(obj, 118, 179);
            lv_obj_set_size(obj, 80, 50);
            lv_obj_add_event_cb(obj, action_switch_led, LV_EVENT_RELEASED, (void *)1);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn2, LV_EVENT_ALL, 0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff18345d), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0050), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "LED 2");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, 0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffff0050), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                }
            }
        }
        {
            // btn2_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn2_1 = obj;
            lv_obj_set_pos(obj, 223, 179);
            lv_obj_set_size(obj, 80, 50);
            lv_obj_add_event_cb(obj, action_switch_led, LV_EVENT_RELEASED, (void *)2);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn2_1, LV_EVENT_ALL, 0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff18345d), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0050), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "LED 3");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj2, LV_EVENT_ALL, 0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffff0050), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                }
            }
        }
        {
            // Arc1
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc1 = obj;
            lv_obj_set_pos(obj, 18, 85);
            lv_obj_set_size(obj, 70, 70);
            lv_obj_add_event_cb(obj, event_handler_cb_main_arc1, LV_EVENT_ALL, 0);
            add_style_battery_arc(obj);
        }
        {
            // Arc2
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc2 = obj;
            lv_obj_set_pos(obj, 126, 86);
            lv_obj_set_size(obj, 70, 70);
            lv_obj_add_event_cb(obj, event_handler_cb_main_arc2, LV_EVENT_ALL, 0);
            add_style_battery_arc(obj);
        }
        {
            // Arc3
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc3 = obj;
            lv_obj_set_pos(obj, 233, 85);
            lv_obj_set_size(obj, 70, 70);
            lv_obj_add_event_cb(obj, event_handler_cb_main_arc3, LV_EVENT_ALL, 0);
            add_style_battery_arc(obj);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        bool new_val = get_var_state_led1();
        bool cur_val = lv_obj_has_state(objects.btn1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.btn1;
            if (new_val) lv_obj_add_state(objects.btn1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.btn1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led1();
        bool cur_val = lv_obj_has_state(objects.obj0, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            if (new_val) lv_obj_add_state(objects.obj0, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj0, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led2();
        bool cur_val = lv_obj_has_state(objects.btn2, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.btn2;
            if (new_val) lv_obj_add_state(objects.btn2, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.btn2, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led2();
        bool cur_val = lv_obj_has_state(objects.obj1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            if (new_val) lv_obj_add_state(objects.obj1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led3();
        bool cur_val = lv_obj_has_state(objects.btn2_1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.btn2_1;
            if (new_val) lv_obj_add_state(objects.btn2_1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.btn2_1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_state_led3();
        bool cur_val = lv_obj_has_state(objects.obj2, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj2;
            if (new_val) lv_obj_add_state(objects.obj2, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj2, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_battery_percentage1();
        int32_t cur_val = lv_arc_get_value(objects.arc1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.arc1;
            lv_arc_set_value(objects.arc1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_battery_percentage2();
        int32_t cur_val = lv_arc_get_value(objects.arc2);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.arc2;
            lv_arc_set_value(objects.arc2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_battery_percentage3();
        int32_t cur_val = lv_arc_get_value(objects.arc3);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.arc3;
            lv_arc_set_value(objects.arc3, new_val);
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
