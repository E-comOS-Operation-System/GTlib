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

void gt_set_cursor_position(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
    fflush(stdout);
}

void gt_set_cursor_visibility(bool visible) {
    printf(visible ? "\033[?25h" : "\033[?25l");
    fflush(stdout);
}
