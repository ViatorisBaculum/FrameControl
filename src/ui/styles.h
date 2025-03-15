#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: BatteryArc
lv_style_t *get_style_battery_arc_INDICATOR_DEFAULT();
lv_style_t *get_style_battery_arc_MAIN_DEFAULT();
lv_style_t *get_style_battery_arc_KNOB_DEFAULT();
void add_style_battery_arc(lv_obj_t *obj);
void remove_style_battery_arc(lv_obj_t *obj);

// Style: ButtonText
lv_style_t *get_style_button_text_MAIN_DEFAULT();
lv_style_t *get_style_button_text_MAIN_CHECKED();
void add_style_button_text(lv_obj_t *obj);
void remove_style_button_text(lv_obj_t *obj);

// Style: ButtonStyle
lv_style_t *get_style_button_style_MAIN_DEFAULT();
lv_style_t *get_style_button_style_MAIN_CHECKED();
void add_style_button_style(lv_obj_t *obj);
void remove_style_button_style(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/