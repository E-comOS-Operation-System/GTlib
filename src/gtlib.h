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
#ifndef GTLIB_H
#define GTLIB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../include/ecomos-gtlib.h"

typedef enum { // Color
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
typedef enum { // Text attributes
    GT_ATTR_NORMAL = 0,
    GT_ATTR_BOLD = 1 << 0,
    GT_ATTR_UNDERLINE = 1 << 1,
    GT_ATTR_REVERSE = 1 << 2,
    GT_ATTR_BLINK = 1 << 3,
    GT_ATTR_DIM = 1 << 4,
    GT_ATTR_INVISIBLE = 1 << 5
} gt_attr_t;
typedef enum {//Keyborad button def
     GT_KEY_UNKNOWN = 0,
    GT_KEY_ENTER = 13,
    GT_KEY_ESC = 27,
    GT_KEY_TAB = 9,
    GT_KEY_BACKSPACE = 8,
    GT_KEY_DELETE = 127,
    // UP/DOWN/LEFT/RIGHT
     GT_KEY_UP = 256,
    GT_KEY_DOWN,
    GT_KEY_LEFT,
    GT_KEY_RIGHT,
    // F1-F12
    GT_KEY_F1, GT_KEY_F2, GT_KEY_F3, GT_KEY_F4,
    GT_KEY_F5, GT_KEY_F6, GT_KEY_F7, GT_KEY_F8,
    GT_KEY_F9, GT_KEY_F10, GT_KEY_F11, GT_KEY_F12
} gt_key_t;
// Mouse event types
typedef enum {
    GT_MOUSE_LEFT_CLICK,
    GT_MOUSE_RIGHT_CLICK,
    GT_MOUSE_MIDDLE_CLICK,
    GT_MOUSE_MOVE
} gt_mouse_event_type_t;
// Mouse event structure
typedef struct {
    gt_mouse_event_type_t type;
    int x;
    int y;
    int button;
} gt_mouse_event_t;
// Event types
typedef enum {
    GT_EVENT_KEY_PRESS,
    GT_EVENT_MOUSE,
    GT_EVENT_TIMER,
    GT_EVENT_WINDOW_RESIZE
} gt_event_type_t;
// Event structure
typedef struct {
    gt_event_type_t type;
    union {
        gt_key_t key;
        gt_mouse_event_t mouse;
        uint32_t timer_id;
        struct { int width; int height; } resize;
    } data;
} gt_event_t;
// Control Type
typedef enum {
    GT_WIDGET_BUTTON,
    GT_WIDGET_LABEL,
    GT_WIDGET_TEXTBOX
} gt_widget_type_t;

typedef struct gt_window gt_window_t;
typedef struct gt_widget gt_widget_t;

/* Windows Manager */
// Initialize GTlib library
int gt_init(void);
// Cleanup GTlib library resources
void gt_cleanup(void);
// Created window
gt_window_t *gt_create_window(int x, int y, int width, int height, const char *title);
// Destroy a window
void gt_destroy_window(gt_window_t *window);
// Show a window
void gt_show_window(gt_window_t *window);
// Hide a window
void gt_hide_window(gt_window_t *window);
// Setup a window tittle
void gt_set_window_title(gt_window_t *window, const char *title);
// Get window tittle
void gt_get_window_title(gt_window_t *window, char *title, size_t max_length);
// Move a window
void gt_move_window(gt_window_t *window, int x, int y);
// Resize a window
void gt_resize_window(gt_window_t *window, int width, int height);
// Obtain window geometry information
void gt_get_window_geometry(gt_window_t *window, int *x, int *y, int *width, int *height);

/* Draw a window */

// Clear window content
void gt_clear_window(gt_window_t *window);
// Draw a character in window
void gt_draw_char(gt_window_t *window, int x, int y, char ch,
                  gt_color_t fg, gt_color_t bg, gt_attr_t attr);
// Draw a string in window
void gt_draw_string(gt_window_t *window, int x, int y, const char *str,
                    gt_color_t fg, gt_color_t bg, gt_attr_t attr);
// Draw borders for windows
void gt_draw_border(gt_window_t *window, gt_color_t fg, gt_color_t bg, gt_attr_t attr);
// Refresh window display
void gt_refresh_window(gt_window_t *window);
// Refresh all windows
void gt_refresh_all(void);
// Set cursor position
void gt_set_cursor_position(int x, int y);
// Show or hide cursor
void gt_set_cursor_visibility(bool visible);

/* Control */

// Button callback function type
typedef void (*gt_button_callback_t)(gt_widget_t *widget, void *user_data);
// Create a button
gt_widget_t *gt_create_button(gt_window_t *window, int x, int y, int width, int height,
                              const char *text, gt_button_callback_t callback, void *user_data);
// Create a label
gt_widget_t *gt_create_label(gt_window_t *window, int x, int y, const char *text,
                             gt_color_t fg, gt_color_t bg, gt_attr_t attr);
// Create a text box
gt_widget_t *gt_create_textbox(gt_window_t *window, int x, int y, int width, int height,
                               const char *text, int max_length);
// Set control text
void gt_set_widget_text(gt_widget_t *widget, const char *text);
// Get control text
const char *gt_get_widget_text(gt_widget_t *widget);
// Set widget visible
void gt_set_widget_visible(gt_widget_t *widget, bool visible);
// Destroy control
void gt_destroy_widget(gt_widget_t *widget);
// Set focus to a widget
void gt_set_widget_focus(gt_widget_t *widget);

/* Event handling */

// Waiting for an event 
int gt_wait_event(gt_event_t *event, int timeout);
// Init mouse event support
int gt_init_mouse(void);
// Enbale/Disable mouse event support
void gt_enable_mouse(bool enable);
// Set timer
uint32_t gt_set_timer(int interval);
// Cancel timer
void gt_cancel_timer(uint32_t timer_id);
// Get version for GTLib
const char *gt_get_version(void);

/* Internal implementation considerations */

// Window structure definition 
struct gt_window {
    int x, y, width, height;
    char *title;
    bool visible;
    struct gt_widget *widgets;
};

// Widget structure definition
struct gt_widget {
    gt_widget_type_t type;
    int x, y, width, height;
    char *text;
    gt_color_t fg, bg;
    gt_attr_t attr;
    bool visible;
    gt_button_callback_t callback;
    void *user_data;
    struct gt_widget *next;
};

/* IPC Messages */

// IPC message types
typedef enum {
    GT_IPC_CREATE_WINDOW,
    GT_IPC_DESTROY_WINDOW,
    GT_IPC_DRAW_CHAR,
    GT_IPC_DRAW_STRING,
    GT_IPC_DRAW_BORDER,
    GT_IPC_CLEAR_WINDOW,
    GT_IPC_REFRESH_WINDOW,
    GT_IPC_EVENT_KEY,
    GT_IPC_EVENT_MOUSE
} gt_ipc_msg_type_t;

// IPC message structure
typedef struct {
    gt_ipc_msg_type_t type;
    uint32_t window_id;
    uint32_t data_len;
    uint8_t data[];
} gt_ipc_msg_t;
#endif