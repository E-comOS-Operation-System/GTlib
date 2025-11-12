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
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

int gt_wait_event(gt_event_t *event, int timeout) {
    if (!event) return -1;
    
    fd_set readfds;
    struct timeval tv;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    if (timeout >= 0) {
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
    }
    
    int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, timeout >= 0 ? &tv : NULL);
    
    if (ret <= 0) return ret;
    
    char buf[3];
    int n = read(STDIN_FILENO, buf, sizeof(buf));
    
    if (n <= 0) return -1;
    
    event->type = GT_EVENT_KEY_PRESS;
    
    if (n == 1) {
        event->data.key = buf[0];
    } else if (n == 3 && buf[0] == 27 && buf[1] == '[') {
        switch (buf[2]) {
            case 'A': event->data.key = GT_KEY_UP; break;
            case 'B': event->data.key = GT_KEY_DOWN; break;
            case 'C': event->data.key = GT_KEY_RIGHT; break;
            case 'D': event->data.key = GT_KEY_LEFT; break;
            default: event->data.key = GT_KEY_UNKNOWN;
        }
    } else {
        event->data.key = GT_KEY_UNKNOWN;
    }
    
    return 0;
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
