## lvgl_demo

### 介绍
- 适用于Linux PC和ARM Linux的lvgl demo

### 使用说明

#### 用于Linux PC时的修改项

1. 修改Makefile

    - 修改GCC: 修改[Makefile](Makefile)文件中的`CC`为对应的GCC
    - 使能SDL: 在[Makefile](Makefile)文件的`LDFLAGS`中增加`SDL2`


2. 修改[lv_drv_conf.h](lvgl_inc/lv_drv_conf.h)文件

    使能如下宏定义

    ```c
    #define USE_SDL 1
    ```

    失能如下宏定义
    ```c
    #define USE_FBDEV 0
    #define USE_EVDEV 0
    ```

#### 用于ARM Linux时的修改项

1. 修改CMakeLists.txt

    - 修改GCC: 修改[Makefile](Makefile)文件中的`CC`为对应的GCC
    - 失能SDL: 在[Makefile](Makefile)文件的`LDFLAGS`中删除`SDL2`


2. 修改[lv_drv_conf.h](lvgl_inc/lv_drv_conf.h)文件

    使能如下宏定义

    ```c
    #define USE_FBDEV 1
    #define USE_EVDEV 1
    ```

    失能如下宏定义

    ```c
    #define USE_SDL 0
    ```

### 编译&清理

1. 编译: `make -j32`
2. 清理: `make clean`或者`make distclean`
