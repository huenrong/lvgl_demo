/**
 * @file      : main.c
 * @brief     : 程序入口文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-02-12 16:19:08
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-02-12 huenrong        创建文件
 *
 */

#include <stdio.h>
#include <unistd.h>

#include "./src/app/app.h"
#include "lvgl/lvgl.h"

/**
 * @brief  : 程序入口
 * @param  : argc: 输入参数, 参数个数
 * @param  : argv: 输入参数, 参数列表
 * @return : 成功: 0
 *           失败: 其它
 */
int main(int argc, char *argv[])
{
    easy_logger_init();

    lvgl_init();

    application_init();

    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5 * 1000);
    }

    return 0;
}
