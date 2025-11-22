/*
    GTLib - Terminal text GUI Library of E-comOS
    Copyright (C) 2025  Saladin5101

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef ECOMOS_GTLIB_H
#define ECOMOS_GTLIB_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define GTLIB_VERSION "1.0.0"

// 颜色定义
typedef enum {
    GT_COLOR_BLACK = 0,
    GT_COLOR_RED,
    GT_COLOR_GREEN,
    GT_COLOR_YELLOW,
    GT_COLOR_BLUE,
    GT_COLOR_MAGENTA,
    GT_COLOR_CYAN,
    GT_COLOR_WHITE,
    GT_COLOR_DEFAULT,
    GT_COLOR_MAX
} gt_color_t;

// 文本属性
typedef enum {
    GT_ATTR_NORMAL = 0,
    GT_ATTR_BOLD = 1 << 0,
    GT_ATTR_UNDERLINE = 1 << 1,
    GT_ATTR_REVERSE = 1 << 2,
    GT_ATTR_BLINK = 1 << 3,
    GT_ATTR_DIM = 1 << 4,
    GT_ATTR_INVISIBLE = 1 << 5
} gt_attr_t;

// 键盘按键定义
typedef enum {
    GT_KEY_UNKNOWN = 0,
    GT_KEY_ENTER = 13,
    GT_KEY_ESC = 27,
    GT_KEY_TAB = 9,
    GT_KEY_BACKSPACE = 8,
    GT_KEY_DELETE = 127,
    GT_KEY_UP = 256,
    GT_KEY_DOWN,
    GT_KEY_LEFT,
    GT_KEY_RIGHT,
    GT_KEY_F1, GT_KEY_F2, GT_KEY_F3, GT_KEY_F4,
    GT_KEY_F5, GT_KEY_F6, GT_KEY_F7, GT_KEY_F8,
    GT_KEY_F9, GT_KEY_F10, GT_KEY_F11, GT_KEY_F12
} gt_key_t;

// 鼠标事件类型
typedef enum {
    GT_MOUSE_LEFT_CLICK,
    GT_MOUSE_RIGHT_CLICK,
    GT_MOUSE_MIDDLE_CLICK,
    GT_MOUSE_MOVE
} gt_mouse_event_type_t;

// 鼠标事件结构
typedef struct {
    gt_mouse_event_type_t type;
    int x;
    int y;
    int button;
} gt_mouse_event_t;

// 事件类型
typedef enum {
    GT_EVENT_KEY_PRESS,
    GT_EVENT_MOUSE,
    GT_EVENT_TIMER,
    GT_EVENT_WINDOW_RESIZE
} gt_event_type_t;

// 事件结构
typedef struct {
    gt_event_type_t type;
    union {
        gt_key_t key;
        gt_mouse_event_t mouse;
        uint32_t timer_id;
        struct { int width; int height; } resize;
    } data;
} gt_event_t;

// 控件类型
typedef enum {
    GT_WIDGET_BUTTON,
    GT_WIDGET_LABEL,
    GT_WIDGET_TEXTBOX
} gt_widget_type_t;

typedef struct gt_window gt_window_t;
typedef struct gt_widget gt_widget_t;
typedef void (*gt_button_callback_t)(gt_widget_t *widget, void *user_data);

// 初始化和清理
int gt_init(void);
void gt_cleanup(void);

// 窗口管理
gt_window_t *gt_create_window(int x, int y, int width, int height, const char *title);
void gt_destroy_window(gt_window_t *window);
void gt_show_window(gt_window_t *window);
void gt_hide_window(gt_window_t *window);
void gt_set_window_title(gt_window_t *window, const char *title);
void gt_get_window_title(gt_window_t *window, char *title, size_t max_length);
void gt_move_window(gt_window_t *window, int x, int y);
void gt_resize_window(gt_window_t *window, int width, int height);
void gt_get_window_geometry(gt_window_t *window, int *x, int *y, int *width, int *height);

// 窗口绘制
void gt_clear_window(gt_window_t *window);
void gt_draw_char(gt_window_t *window, int x, int y, char ch, gt_color_t fg, gt_color_t bg, gt_attr_t attr);
void gt_draw_string(gt_window_t *window, int x, int y, const char *str, gt_color_t fg, gt_color_t bg, gt_attr_t attr);
void gt_draw_border(gt_window_t *window, gt_color_t fg, gt_color_t bg, gt_attr_t attr);
void gt_refresh_window(gt_window_t *window);
void gt_refresh_all(void);
void gt_set_cursor_position(int x, int y);
void gt_set_cursor_visibility(bool visible);

// 控件
gt_widget_t *gt_create_button(gt_window_t *window, int x, int y, int width, int height, const char *text, gt_button_callback_t callback, void *user_data);
gt_widget_t *gt_create_label(gt_window_t *window, int x, int y, const char *text, gt_color_t fg, gt_color_t bg, gt_attr_t attr);
gt_widget_t *gt_create_textbox(gt_window_t *window, int x, int y, int width, int height, const char *text, int max_length);
void gt_set_widget_text(gt_widget_t *widget, const char *text);
const char *gt_get_widget_text(gt_widget_t *widget);
void gt_set_widget_visible(gt_widget_t *widget, bool visible);
void gt_destroy_widget(gt_widget_t *widget);
void gt_set_widget_focus(gt_widget_t *widget);

// 事件处理
int gt_wait_event(gt_event_t *event, int timeout);
int gt_init_mouse(void);
void gt_enable_mouse(bool enable);
uint32_t gt_set_timer(int interval);
void gt_cancel_timer(uint32_t timer_id);
const char *gt_get_version(void);

#endif