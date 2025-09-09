#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_symbol_ladezustand;
extern const lv_img_dsc_t img_symbol_ladedatum;
extern const lv_img_dsc_t img_symbol_betriebsstunden;
extern const lv_img_dsc_t img_symbol_helligkeit;
extern const lv_img_dsc_t img_symbol_exodia;
extern const lv_img_dsc_t img_symbol_gods;
extern const lv_img_dsc_t img_symbol_coins;
extern const lv_img_dsc_t img_symbol_coins_inverted_small;
extern const lv_img_dsc_t img_symbol_exodia_inverted_small;
extern const lv_img_dsc_t img_symbol_gods_inverted_small;
extern const lv_img_dsc_t img_symbol_automatikmodus;
extern const lv_img_dsc_t img_symbol_abwesenheitskontrolle;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[12];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/