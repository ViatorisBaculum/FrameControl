#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *button_power_1;
    lv_obj_t *button_power_2;
    lv_obj_t *button_power_3;
    lv_obj_t *obj0;
    lv_obj_t *tab_home;
    lv_obj_t *battery_percentage_1;
    lv_obj_t *brightness_percentage_1;
    lv_obj_t *image_button_power_1;
    lv_obj_t *battery_percentage_2;
    lv_obj_t *brightness_percentage_2;
    lv_obj_t *image_button_power_2;
    lv_obj_t *battery_percentage_3;
    lv_obj_t *brightness_percentage_3;
    lv_obj_t *image_button_power_3;
    lv_obj_t *tab_settings;
    lv_obj_t *image_object_frame_1;
    lv_obj_t *image_battery_percentage_1;
    lv_obj_t *label_battery_percentage_1;
    lv_obj_t *image_charging_date_1;
    lv_obj_t *label_charging_date_1;
    lv_obj_t *image_operating_hours_1;
    lv_obj_t *label_operating_hours_1;
    lv_obj_t *image_brightness_1;
    lv_obj_t *button_brightness_down_1;
    lv_obj_t *label_button_brightness_down_1;
    lv_obj_t *label_brightness_1;
    lv_obj_t *button_brightness_up_1;
    lv_obj_t *label_button_brightness_up_1;
    lv_obj_t *slider_brightness_1;
    lv_obj_t *line_settings_1;
    lv_obj_t *image_object_frame_2;
    lv_obj_t *image_battery_percentage_2;
    lv_obj_t *label_battery_percentage_2;
    lv_obj_t *image_charging_date_2;
    lv_obj_t *label_charging_date_2;
    lv_obj_t *image_operating_hours_2;
    lv_obj_t *label_operating_hours_2;
    lv_obj_t *image_brightness_2;
    lv_obj_t *button_brightness_down_2;
    lv_obj_t *label_button_brightness_down_2;
    lv_obj_t *label_brightness_2;
    lv_obj_t *button_brightness_up_2;
    lv_obj_t *label_button_brightness_up_2;
    lv_obj_t *slider_brightness_2;
    lv_obj_t *line_settings_2;
    lv_obj_t *image_object_frame_3;
    lv_obj_t *image_battery_percentage_3;
    lv_obj_t *label_battery_percentage_3;
    lv_obj_t *image_charging_date_3;
    lv_obj_t *label_charging_date_3;
    lv_obj_t *image_operating_hours_3;
    lv_obj_t *label_operating_hours_3;
    lv_obj_t *image_brightness_3;
    lv_obj_t *button_brightness_down_3;
    lv_obj_t *label_button_brightness_down_3;
    lv_obj_t *label_brightness_3;
    lv_obj_t *button_brightness_up_3;
    lv_obj_t *label_button_brightness_up_3;
    lv_obj_t *slider_brightness_3;
    lv_obj_t *line_settings_3;
    lv_obj_t *image_automatic_mode;
    lv_obj_t *obj1;
    lv_obj_t *image_absence_control;
    lv_obj_t *obj2;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/