#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: BatteryArc
//

void init_style_battery_arc_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_color(style, lv_color_hex(0xffee0350));
    lv_style_set_arc_width(style, 6);
    lv_style_set_border_opa(style, 0);
};

lv_style_t *get_style_battery_arc_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_battery_arc_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_battery_arc_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_width(style, 6);
    lv_style_set_arc_color(style, lv_color_hex(0xff18345d));
};

lv_style_t *get_style_battery_arc_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_battery_arc_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_battery_arc_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_opa(style, 0);
};

lv_style_t *get_style_battery_arc_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_battery_arc_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_battery_arc(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_battery_arc_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_battery_arc_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_battery_arc_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_battery_arc(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_battery_arc_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_battery_arc_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_battery_arc_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
// Style: ButtonText
//

void init_style_button_text_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xffff0050));
    lv_style_set_text_letter_space(style, 2);
    lv_style_set_text_font(style, &lv_font_montserrat_14);
};

lv_style_t *get_style_button_text_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_text_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_text_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffffff));
};

lv_style_t *get_style_button_text_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_text_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_button_text(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_text_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_text_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_button_text(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_text_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_text_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: ButtonStyle
//

void init_style_button_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff18345d));
    lv_style_set_radius(style, 100);
};

lv_style_t *get_style_button_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_style_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_style_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0050));
};

lv_style_t *get_style_button_style_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_style_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_style_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_style_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: tabView
//

void init_style_tab_view_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
};

lv_style_t *get_style_tab_view_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_tab_view_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_tab_view(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_tab_view_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_tab_view(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_tab_view_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: ActiveTab
//

void init_style_active_tab_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_active_tab_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_active_tab_MAIN_CHECKED(style);
    }
    return style;
};

void init_style_active_tab_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
    lv_style_set_outline_color(style, lv_color_hex(0xff000000));
    lv_style_set_line_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_active_tab_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_active_tab_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_active_tab_MAIN_CHECKED_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_active_tab_MAIN_CHECKED_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_active_tab_MAIN_CHECKED_PRESSED(style);
    }
    return style;
};

void add_style_active_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_active_tab_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_active_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_active_tab_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

void remove_style_active_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_active_tab_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_active_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_active_tab_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_battery_arc,
        add_style_button_text,
        add_style_button_style,
        add_style_tab_view,
        add_style_active_tab,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_battery_arc,
        remove_style_button_text,
        remove_style_button_style,
        remove_style_tab_view,
        remove_style_active_tab,
    };
    remove_style_funcs[styleIndex](obj);
}

