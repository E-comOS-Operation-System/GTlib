/*
    GTLib - Terminal text GUI Library of E-comOS
    Copyright (C) 2025  Saladin5101

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

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

// Internal structures are now defined in the header file

static bool gt_initialized = false;

int gt_init(void) {
    if (gt_initialized) return 0;
    gt_initialized = true;
    return 0;
}

void gt_cleanup(void) {
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
    (void)window;
}

void gt_draw_char(gt_window_t *window, int x, int y, char ch, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    (void)window; (void)x; (void)y; (void)ch; (void)fg; (void)bg; (void)attr;
}

void gt_draw_string(gt_window_t *window, int x, int y, const char *str, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    (void)window; (void)x; (void)y; (void)str; (void)fg; (void)bg; (void)attr;
}

void gt_draw_border(gt_window_t *window, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    (void)window; (void)fg; (void)bg; (void)attr;
}

void gt_refresh_window(gt_window_t *window) {
    (void)window;
}

void gt_refresh_all(void) {
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