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
#include <stdio.h>

/*@ 
  @ requires width > 0 && height > 0;
  @ ensures \result == NULL || (\result->width == width && \result->height == height);
  @ ensures \result == NULL || (\result->x == x && \result->y == y);
  @ ensures \result == NULL || \result->visible == false;
  @*/
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

/*@
  @ requires \valid(window) || window == NULL;
  @ ensures window == NULL || \freed(window);
  @*/
void gt_destroy_window(gt_window_t *window) {
    if (!window) return;
    if (window->title) free(window->title);
    free(window);
}

/*@
  @ requires \valid(window) || window == NULL;
  @ ensures window == NULL || window->visible == true;
  @*/
void gt_show_window(gt_window_t *window) {
    if (window) window->visible = true;
}

/*@
  @ requires \valid(window) || window == NULL;
  @ ensures window == NULL || window->visible == false;
  @*/
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

/*@
  @ requires \valid(window) || window == NULL;
  @ ensures window == NULL || (window->x == x && window->y == y);
  @*/
void gt_move_window(gt_window_t *window, int x, int y) {
    if (!window) return;
    window->x = x;
    window->y = y;
}

/*@
  @ requires \valid(window) || window == NULL;
  @ requires width > 0 && height > 0;
  @ ensures window == NULL || (window->width == width && window->height == height);
  @*/
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
