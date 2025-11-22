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

gt_widget_t *gt_create_button(gt_window_t *window, int x, int y, int width, int height, const char *text, gt_button_callback_t callback, void *user_data) {
    if (!window) return NULL;
    
    gt_widget_t *widget = malloc(sizeof(gt_widget_t));
    if (!widget) return NULL;
    
    widget->type = GT_WIDGET_BUTTON;
    widget->x = x;
    widget->y = y;
    widget->width = width;
    widget->height = height;
    widget->text = text ? strdup(text) : NULL;
    widget->visible = true;
    widget->focused = false;
    widget->callback = callback;
    widget->user_data = user_data;
    widget->next = window->widgets;
    window->widgets = widget;
    
    // 如果这是第一个可交互控件，设为焦点
    if (!window->focused_widget && widget->type == GT_WIDGET_BUTTON) {
        window->focused_widget = widget;
        widget->focused = true;
    }
    
    return widget;
}

gt_widget_t *gt_create_label(gt_window_t *window, int x, int y, const char *text, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    if (!window) return NULL;
    
    gt_widget_t *widget = malloc(sizeof(gt_widget_t));
    if (!widget) return NULL;
    
    widget->type = GT_WIDGET_LABEL;
    widget->x = x;
    widget->y = y;
    widget->text = text ? strdup(text) : NULL;
    widget->fg = fg;
    widget->bg = bg;
    widget->attr = attr;
    widget->visible = true;
    widget->focused = false;
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
    widget->text = text ? strdup(text) : NULL;
    widget->visible = true;
    widget->focused = false;
    widget->next = window->widgets;
    window->widgets = widget;
    
    // 如果这是第一个可交互控件且没有其他焦点控件，设为焦点
    if (!window->focused_widget && widget->type == GT_WIDGET_TEXTBOX) {
        window->focused_widget = widget;
        widget->focused = true;
    }
    
    (void)max_length;
    return widget;
}

void gt_set_widget_text(gt_widget_t *widget, const char *text) {
    if (!widget) return;
    if (widget->text) free(widget->text);
    widget->text = text ? strdup(text) : NULL;
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
