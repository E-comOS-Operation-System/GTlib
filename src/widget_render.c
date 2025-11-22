/*
    GTLib - Widget Rendering and Focus Management
*/
#include "gtlib.h"
#include <stdio.h>
#include <string.h>

// 渲染单个控件
void gt_render_widget(gt_window_t *window, gt_widget_t *widget) {
    if (!window || !widget || !widget->visible) return;
    
    switch (widget->type) {
        case GT_WIDGET_BUTTON: {
            // 绘制按钮边框
            gt_color_t fg = widget->focused ? GT_COLOR_YELLOW : GT_COLOR_WHITE;
            gt_color_t bg = widget->focused ? GT_COLOR_BLUE : GT_COLOR_DEFAULT;
            
            // 绘制按钮框架
            for (int y = 0; y < widget->height; y++) {
                for (int x = 0; x < widget->width; x++) {
                    char ch = ' ';
                    if (y == 0 || y == widget->height - 1) {
                        ch = (x == 0 || x == widget->width - 1) ? '+' : '-';
                    } else if (x == 0 || x == widget->width - 1) {
                        ch = '|';
                    }
                    gt_draw_char(window, widget->x + x, widget->y + y, ch, fg, bg, GT_ATTR_NORMAL);
                }
            }
            
            // 绘制按钮文本
            if (widget->text) {
                int text_len = strlen(widget->text);
                int start_x = (widget->width - text_len) / 2;
                int start_y = widget->height / 2;
                gt_draw_string(window, widget->x + start_x, widget->y + start_y, 
                              widget->text, fg, bg, widget->focused ? GT_ATTR_BOLD : GT_ATTR_NORMAL);
            }
            break;
        }
        
        case GT_WIDGET_LABEL: {
            if (widget->text) {
                gt_draw_string(window, widget->x, widget->y, widget->text, 
                              widget->fg, widget->bg, widget->attr);
            }
            break;
        }
        
        case GT_WIDGET_TEXTBOX: {
            gt_color_t fg = widget->focused ? GT_COLOR_BLACK : GT_COLOR_WHITE;
            gt_color_t bg = widget->focused ? GT_COLOR_WHITE : GT_COLOR_BLACK;
            
            // 绘制文本框背景
            for (int y = 0; y < widget->height; y++) {
                for (int x = 0; x < widget->width; x++) {
                    gt_draw_char(window, widget->x + x, widget->y + y, ' ', fg, bg, GT_ATTR_NORMAL);
                }
            }
            
            // 绘制文本框边框
            for (int x = 0; x < widget->width; x++) {
                gt_draw_char(window, widget->x + x, widget->y, '-', fg, bg, GT_ATTR_NORMAL);
                gt_draw_char(window, widget->x + x, widget->y + widget->height - 1, '-', fg, bg, GT_ATTR_NORMAL);
            }
            for (int y = 0; y < widget->height; y++) {
                gt_draw_char(window, widget->x, widget->y + y, '|', fg, bg, GT_ATTR_NORMAL);
                gt_draw_char(window, widget->x + widget->width - 1, widget->y + y, '|', fg, bg, GT_ATTR_NORMAL);
            }
            
            // 绘制文本内容
            if (widget->text) {
                gt_draw_string(window, widget->x + 1, widget->y + 1, widget->text, fg, bg, GT_ATTR_NORMAL);
            }
            break;
        }
    }
}

// 渲染所有控件
void gt_render_all_widgets(gt_window_t *window) {
    if (!window) return;
    
    gt_widget_t *widget = window->widgets;
    while (widget) {
        gt_render_widget(window, widget);
        widget = widget->next;
    }
}

// 切换到下一个可交互控件
void gt_focus_next_widget(gt_window_t *window) {
    if (!window || !window->widgets) return;
    
    gt_widget_t *current = window->focused_widget;
    gt_widget_t *next = NULL;
    
    // 如果当前有焦点控件，找下一个可交互控件
    if (current) {
        gt_widget_t *widget = current->next;
        while (widget) {
            if (widget->type == GT_WIDGET_BUTTON || widget->type == GT_WIDGET_TEXTBOX) {
                next = widget;
                break;
            }
            widget = widget->next;
        }
        
        // 如果没找到，从头开始找
        if (!next) {
            widget = window->widgets;
            while (widget && widget != current) {
                if (widget->type == GT_WIDGET_BUTTON || widget->type == GT_WIDGET_TEXTBOX) {
                    next = widget;
                    break;
                }
                widget = widget->next;
            }
        }
    } else {
        // 如果没有当前焦点，找第一个可交互控件
        gt_widget_t *widget = window->widgets;
        while (widget) {
            if (widget->type == GT_WIDGET_BUTTON || widget->type == GT_WIDGET_TEXTBOX) {
                next = widget;
                break;
            }
            widget = widget->next;
        }
    }
    
    // 更新焦点
    if (next) {
        if (current) current->focused = false;
        next->focused = true;
        window->focused_widget = next;
    }
}

// 切换到上一个可交互控件
void gt_focus_prev_widget(gt_window_t *window) {
    if (!window || !window->widgets) return;
    
    gt_widget_t *current = window->focused_widget;
    gt_widget_t *prev = NULL;
    
    // 如果当前有焦点控件，找上一个可交互控件
    if (current) {
        // 从头开始找到当前控件之前的最后一个可交互控件
        gt_widget_t *widget = window->widgets;
        while (widget && widget != current) {
            if (widget->type == GT_WIDGET_BUTTON || widget->type == GT_WIDGET_TEXTBOX) {
                prev = widget;
            }
            widget = widget->next;
        }
        
        // 如果没找到，找最后一个可交互控件
        if (!prev) {
            widget = window->widgets;
            while (widget) {
                if (widget->type == GT_WIDGET_BUTTON || widget->type == GT_WIDGET_TEXTBOX) {
                    prev = widget;
                }
                widget = widget->next;
            }
        }
    } else {
        // 如果没有当前焦点，找最后一个可交互控件
        gt_widget_t *widget = window->widgets;
        while (widget) {
            if (widget->type == GT_WIDGET_BUTTON || widget->type == GT_WIDGET_TEXTBOX) {
                prev = widget;
            }
            widget = widget->next;
        }
    }
    
    // 更新焦点
    if (prev && prev != current) {
        if (current) current->focused = false;
        prev->focused = true;
        window->focused_widget = prev;
    }
}

// 激活当前焦点控件
void gt_activate_focused_widget(gt_window_t *window) {
    if (!window || !window->focused_widget) return;
    
    gt_widget_t *widget = window->focused_widget;
    if (widget->type == GT_WIDGET_BUTTON && widget->callback) {
        widget->callback(widget, widget->user_data);
    }
}