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

#include "../include/ecomos-gtlib.h"

/* Internal implementation */

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