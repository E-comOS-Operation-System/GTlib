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
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

static struct termios orig_termios;
static int term_width = 80;
static int term_height = 24;

int gt_init(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        term_width = ws.ws_col;
        term_height = ws.ws_row;
    }
    
    printf("\033[2J\033[H\033[?25l");
    fflush(stdout);
    
    return 0;
}

void gt_cleanup(void) {
    printf("\033[2J\033[H\033[?25h");
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void gt_clear_window(gt_window_t *window) {
    if (!window || !window->visible) return;
    
    for (int y = 0; y < window->height; y++) {
        printf("\033[%d;%dH", window->y + y + 1, window->x + 1);
        for (int x = 0; x < window->width; x++) {
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
    
    if (attr & GT_ATTR_BOLD) printf("\033[1m");
    if (attr & GT_ATTR_UNDERLINE) printf("\033[4m");
    if (attr & GT_ATTR_REVERSE) printf("\033[7m");
    
    if (fg != GT_COLOR_DEFAULT) printf("\033[3%dm", fg);
    if (bg != GT_COLOR_DEFAULT) printf("\033[4%dm", bg);
    
    printf("%c\033[0m", ch);
    fflush(stdout);
}

void gt_draw_string(gt_window_t *window, int x, int y, const char *str, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    if (!window || !window->visible || !str) return;
    
    for (int i = 0; str[i] && x + i < window->width; i++) {
        gt_draw_char(window, x + i, y, str[i], fg, bg, attr);
    }
}

void gt_draw_border(gt_window_t *window, gt_color_t fg, gt_color_t bg, gt_attr_t attr) {
    if (!window || !window->visible) return;
    
    for (int x = 0; x < window->width; x++) {
        gt_draw_char(window, x, 0, '-', fg, bg, attr);
        gt_draw_char(window, x, window->height - 1, '-', fg, bg, attr);
    }
    
    for (int y = 0; y < window->height; y++) {
        gt_draw_char(window, 0, y, '|', fg, bg, attr);
        gt_draw_char(window, window->width - 1, y, '|', fg, bg, attr);
    }
    
    gt_draw_char(window, 0, 0, '+', fg, bg, attr);
    gt_draw_char(window, window->width - 1, 0, '+', fg, bg, attr);
    gt_draw_char(window, 0, window->height - 1, '+', fg, bg, attr);
    gt_draw_char(window, window->width - 1, window->height - 1, '+', fg, bg, attr);
}

void gt_refresh_window(gt_window_t *window) {
    (void)window;
    fflush(stdout);
}

void gt_refresh_all(void) {
    fflush(stdout);
}

const char *gt_get_version(void) {
    return GTLIB_VERSION;
}
