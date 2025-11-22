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
#include "gtlib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

// Internal structures are now defined in the header file

static bool gt_initialized = false;
static struct termios orig_termios;
static int term_width = 80;
static int term_height = 24;

int gt_init(void) {
    if (gt_initialized) return 0;
    
    // Save original terminal settings
    tcgetattr(STDIN_FILENO, &orig_termios);
    
    // Set raw mode
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    
    // Get terminal size
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        term_width = ws.ws_col;
        term_height = ws.ws_row;
    }
    
    // Clear screen and hide cursor
    printf("\033[2J\033[H\033[?25l");
    fflush(stdout);
    
    gt_initialized = true;
    return 0;
}

void gt_cleanup(void) {
    if (!gt_initialized) return;
    
    // Restore terminal settings
    printf("\033[2J\033[H\033[?25h");
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    
    gt_initialized = false;
}

gt_window_t *gt_create_window(int x, int y, int width, int height, const char *title) {
    gt_window_t *window = malloc(sizeof(gt_window_t));
    if (!window) return NULL;
    
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;
    if (title) {
        size_t len = strlen(title) + 1;
        window->title = malloc(len);
        if (window->title) strncpy(window->title, title, len);
    } else {
        window->title = NULL;
    }
    window->visible = false;
    window->widgets = NULL;
    
    return window;
}

void gt_destroy_window(gt_window_t *window) {
    if (!window) return;
    
    // Free all widgets
    gt_widget_t *widget = window->widgets;
    while (widget) {
        gt_widget_t *next = widget->next;
        gt_destroy_widget(widget);
        widget = next;
    }
    
    if (window->title) free(window->title);
    free(window);
}

void gt_show_window(gt_window_t *window) {
    if (window) window->visible = true;
}

void gt_hide_window(gt_window_t *window) {
    if (window) window->visible = false;
}

void gt_set_window_title(gt_window_t *window, const char *title) {
    if (!window) return;
    if (window->title) free(window->title);
    if (title) {
        size_t len = strlen(title) + 1;
        window->title = malloc(len);
        if (window->title) strncpy(window->title, title, len);
    } else {
        window->title = NULL;
    }
}

void gt_get_window_title(gt_window_t *window, char *title, size_t max_length) {
    if (!window || !title || max_length == 0) return;
    if (window->title) {
        strncpy(title, window->title, max_length - 1);
        title[max_length - 1] = '\0';
    } else {
        title[0] = '\0';
    }
}

void gt_move_window(gt_window_t *window, int x, int y) {
    if (!window) return;
    window->x = x;
    window->y = y;
}

void gt_resize_window(gt_window_t *window, int width, int height) {
    if (!window) return;
    window->width = width;
    window->height = height;
}

void gt_get_window_geometry(gt_window_t *window, int *x, int *y, int *width, int *height) {
    if (!window) return;
    if (x) *x = window->x;
    if (y) *y = window->y;
    if (width) *width = window->width;
    if (height) *height = window->height;
}

void gt_clear_window(gt_window_t *window) {
    if (!window || !window->visible) return;
    
    for (int y = window->y; y < window->y + window->height && y < term_height; y++) {
        printf("\033[%d;%dH", y + 1, window->x + 1);
        for (int x = 0; x < window->width && window->x + x < term_width; x++) {
            printf(" ");
        }
    }
    fflush(stdout);
}

void gt_draw_char(gt_window_t *window, int x, int y, char ch, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    if (!window || !window->visible) return;
    
    int abs_x = window->x + x;
    int abs_y = window->y + y;
    
    if (abs_x < 0 || abs_x >= term_width || abs_y < 0 || abs_y >= term_height) return;
    
    printf("\033[%d;%dH", abs_y + 1, abs_x + 1);
    
    // Set colors and attributes
    if (attr & GT_ATTR_BOLD) printf("\033[1m");
    if (attr & GT_ATTR_UNDERLINE) printf("\033[4m");
    if (attr & GT_ATTR_REVERSE) printf("\033[7m");
    
    if (fg != GT_COLOR_DEFAULT) printf("\033[3%dm", fg);
    if (bg != GT_COLOR_DEFAULT) printf("\033[4%dm", bg);
    
    printf("%c", ch);
    printf("\033[0m"); // Reset attributes
    fflush(stdout);
}

void gt_draw_string(gt_window_t *window, int x, int y, const char *str, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    if (!window || !window->visible || !str) return;
    
    int pos_x = x;
    for (const char *p = str; *p && pos_x < window->width; p++, pos_x++) {
        gt_draw_char(window, pos_x, y, *p, fg, bg, attr);
    }
}

void gt_draw_border(gt_window_t *window, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    if (!window || !window->visible) return;
    
    // Top and bottom borders
    for (int x = 0; x < window->width; x++) {
        gt_draw_char(window, x, 0, '-', fg, bg, attr);
        gt_draw_char(window, x, window->height - 1, '-', fg, bg, attr);
    }
    
    // Left and right borders
    for (int y = 0; y < window->height; y++) {
        gt_draw_char(window, 0, y, '|', fg, bg, attr);
        gt_draw_char(window, window->width - 1, y, '|', fg, bg, attr);
    }
    
    // Corners
    gt_draw_char(window, 0, 0, '+', fg, bg, attr);
    gt_draw_char(window, window->width - 1, 0, '+', fg, bg, attr);
    gt_draw_char(window, 0, window->height - 1, '+', fg, bg, attr);
    gt_draw_char(window, window->width - 1, window->height - 1, '+', fg, bg, attr);
}

static void gt_draw_widget(gt_window_t *window, gt_widget_t *widget) {
    if (!widget || !widget->visible) return;
    
    switch (widget->type) {
        case GT_WIDGET_LABEL:
            if (widget->text) {
                gt_draw_string(window, widget->x, widget->y, widget->text, 
                             widget->fg, widget->bg, widget->attr);
            }
            break;
            
        case GT_WIDGET_BUTTON: {
            // Draw button border
            for (int x = 0; x < widget->width; x++) {
                gt_draw_char(window, widget->x + x, widget->y, '-', 
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
                gt_draw_char(window, widget->x + x, widget->y + widget->height - 1, '-',
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
            }
            for (int y = 1; y < widget->height - 1; y++) {
                gt_draw_char(window, widget->x, widget->y + y, '|',
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
                gt_draw_char(window, widget->x + widget->width - 1, widget->y + y, '|',
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
            }
            // Draw button text centered
            if (widget->text) {
                int text_len = strlen(widget->text);
                int text_x = widget->x + (widget->width - text_len) / 2;
                int text_y = widget->y + widget->height / 2;
                gt_draw_string(window, text_x, text_y, widget->text,
                             GT_COLOR_CYAN, GT_COLOR_DEFAULT, GT_ATTR_BOLD);
            }
            break;
        }
        
        case GT_WIDGET_TEXTBOX: {
            // Draw textbox border
            for (int x = 0; x < widget->width; x++) {
                gt_draw_char(window, widget->x + x, widget->y, '-',
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
                gt_draw_char(window, widget->x + x, widget->y + widget->height - 1, '-',
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
            }
            for (int y = 1; y < widget->height - 1; y++) {
                gt_draw_char(window, widget->x, widget->y + y, '|',
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
                gt_draw_char(window, widget->x + widget->width - 1, widget->y + y, '|',
                           GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
            }
            // Draw textbox content
            if (widget->text) {
                gt_draw_string(window, widget->x + 1, widget->y + 1, widget->text,
                             GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
            }
            break;
        }
    }
}

void gt_refresh_window(gt_window_t *window) {
    if (!window || !window->visible) return;
    
    // Draw all widgets
    gt_widget_t *widget = window->widgets;
    while (widget) {
        gt_draw_widget(window, widget);
        widget = widget->next;
    }
    fflush(stdout);
}

void gt_refresh_all(void) {
    fflush(stdout);
}

gt_widget_t *gt_create_button(gt_window_t *window, int x, int y, int width, int height, const char *text, gt_button_callback_t callback, void *user_data) {
    if (!window) return NULL;
    
    gt_widget_t *widget = malloc(sizeof(gt_widget_t));
    if (!widget) return NULL;
    
    widget->type = GT_WIDGET_BUTTON;
    widget->x = x;
    widget->y = y;
    widget->width = width;
    widget->height = height;
    if (text) {
        size_t len = strlen(text) + 1;
        widget->text = malloc(len);
        if (widget->text) strncpy(widget->text, text, len);
    } else {
        widget->text = NULL;
    }
    widget->visible = true;
    widget->callback = callback;
    widget->user_data = user_data;
    widget->next = window->widgets;
    window->widgets = widget;
    
    return widget;
}

gt_widget_t *gt_create_label(gt_window_t *window, int x, int y, const char *text, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    if (!window) return NULL;
    
    gt_widget_t *widget = malloc(sizeof(gt_widget_t));
    if (!widget) return NULL;
    
    widget->type = GT_WIDGET_LABEL;
    widget->x = x;
    widget->y = y;
    if (text) {
        size_t len = strlen(text) + 1;
        widget->text = malloc(len);
        if (widget->text) strncpy(widget->text, text, len);
    } else {
        widget->text = NULL;
    }
    widget->fg = fg;
    widget->bg = bg;
    widget->attr = attr;
    widget->visible = true;
    widget->next = window->widgets;
    window->widgets = widget;
    
    return widget;
}

gt_widget_t *gt_create_textbox(gt_window_t *window, int x, int y, int width, int height, const char *text, int max_length) {
    if (!window) return NULL;
    
    gt_widget_t *widget = malloc(sizeof(gt_widget_t));
    if (!widget) return NULL;
    
    widget->type = GT_WIDGET_TEXTBOX;
    widget->x = x;
    widget->y = y;
    widget->width = width;
    widget->height = height;
    if (text) {
        size_t len = strlen(text) + 1;
        widget->text = malloc(len);
        if (widget->text) strncpy(widget->text, text, len);
    } else {
        widget->text = NULL;
    }
    widget->visible = true;
    widget->next = window->widgets;
    window->widgets = widget;
    
    return widget;
}

void gt_set_widget_text(gt_widget_t *widget, const char *text) {
    if (!widget) return;
    if (widget->text) free(widget->text);
    if (text) {
        size_t len = strlen(text) + 1;
        widget->text = malloc(len);
        if (widget->text) strncpy(widget->text, text, len);
    } else {
        widget->text = NULL;
    }
}

const char *gt_get_widget_text(gt_widget_t *widget) {
    return widget ? widget->text : NULL;
}

void gt_set_widget_visible(gt_widget_t *widget, bool visible) {
    if (widget) widget->visible = visible;
}

void gt_destroy_widget(gt_widget_t *widget) {
    if (!widget) return;
    if (widget->text) free(widget->text);
    free(widget);
}

void gt_set_widget_focus(gt_widget_t *widget) {
    (void)widget;
}

void gt_set_cursor_position(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
    fflush(stdout);
}

void gt_set_cursor_visibility(bool visible) {
    if (visible) {
        printf("\033[?25h");
    } else {
        printf("\033[?25l");
    }
    fflush(stdout);
}

int gt_wait_event(gt_event_t *event, int timeout) {
    (void)event; (void)timeout;
    return 1;
}

int gt_init_mouse(void) {
    return 0;
}

void gt_enable_mouse(bool enable) {
    (void)enable;
}

uint32_t gt_set_timer(int interval) {
    (void)interval;
    return 0;
}

void gt_cancel_timer(uint32_t timer_id) {
    (void)timer_id;
}

const char *gt_get_version(void) {
    return GTLIB_VERSION;
}