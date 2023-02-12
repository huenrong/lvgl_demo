/**
 * @file      : app.c
 * @brief     : 应用层接口源文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-02-12 18:16:08
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-02-12 huenrong        创建文件
 *
 */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "./app.h"
#include "lvgl/lvgl.h"
#include "../../lvgl_inc/lv_drv_conf.h"

#if USE_FBDEV
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#elif USE_SDL
#include "../../lv_drivers/sdl/sdl.h"
#endif
#include "lvgl/examples/lv_examples.h"

#define LOG_TAG "app"
#include "elog.h"

#ifndef SDL_HOR_RES
#define SDL_HOR_RES 320
#endif
#ifndef SDL_VER_RES
#define SDL_VER_RES 240
#endif

#define DISP_BUF_SIZE (SDL_HOR_RES * SDL_VER_RES)

/**
 * @brief  初始化LVGL硬件抽象层
 */
static void lvgl_hal_init(void)
{
#if USE_FBDEV
    /*Linux frame buffer device init*/
    fbdev_init();
#elif USE_SDL
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    sdl_init();
#endif

    /*Create a display buffer*/
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf[DISP_BUF_SIZE];
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Create a display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;
#if USE_FBDEV
    disp_drv.flush_cb = fbdev_flush;
#elif USE_SDL
    disp_drv.flush_cb = sdl_display_flush;
#endif
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

#if USE_EVDEV
    /* Linux input device init */
    evdev_init();
#endif

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
#if USE_EVDEV
    indev_drv.read_cb = evdev_read;
#elif USE_SDL
    indev_drv.read_cb = sdl_mouse_read;
#endif
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);

#if 0
    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon);                  /*Declare the image file.*/
    lv_obj_t *cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);     /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);       /*Connect the image  object to the driver*/
#endif
}

/**
 * @brief  初始化easy_logger
 */
void easy_logger_init(void)
{
    /* close printf buffer */
    setbuf(stdout, NULL);
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, (ELOG_FMT_ALL & ~(ELOG_FMT_P_INFO | ELOG_FMT_T_INFO)));
    elog_set_fmt(ELOG_LVL_WARN, (ELOG_FMT_ALL & ~(ELOG_FMT_P_INFO | ELOG_FMT_T_INFO)));
    elog_set_fmt(ELOG_LVL_INFO, (ELOG_FMT_ALL & ~(ELOG_FMT_P_INFO | ELOG_FMT_T_INFO)));
    elog_set_fmt(ELOG_LVL_DEBUG, (ELOG_FMT_ALL & ~(ELOG_FMT_P_INFO | ELOG_FMT_T_INFO)));
    elog_set_fmt(ELOG_LVL_VERBOSE, (ELOG_FMT_ALL & ~(ELOG_FMT_P_INFO | ELOG_FMT_T_INFO)));
#ifdef ELOG_COLOR_ENABLE
    elog_set_text_color_enabled(true);
#endif
    /* start EasyLogger */
    elog_start();
}

/**
 * @brief  初始化LVGL
 */
void lvgl_init(void)
{
    // 初始化LVGL库
    lv_init();

    // 初始化LVGL硬件抽象层
    lvgl_hal_init();
}

/**
 * @brief  初始化应用程序
 */
void application_init(void)
{
    lv_example_btn_1();
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if (start_ms == 0)
    {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
