/**
 * @file      : app.h
 * @brief     : 应用层接口头文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-02-12 18:16:23
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-02-12 huenrong        创建文件
 *
 */

#ifndef __APP_H
#define __APP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  初始化LVGL
 */
void lvgl_init(void);

/**
 * @brief  初始化应用程序
 */
void application_init(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_H
