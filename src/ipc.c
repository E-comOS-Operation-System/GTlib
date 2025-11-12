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
#include <ipc_message.h>
#include <service.h>
#include <stdlib.h>
#include <string.h>

static uint32_t wm_service_pid = 0;

int gt_ipc_connect_wm(void) {
    wm_service_pid = eclib_service_lookup("window_manager");
    return wm_service_pid > 0 ? 0 : -1;
}

void gt_ipc_disconnect_wm(void) {
    wm_service_pid = 0;
}

int gt_ipc_send_msg(gt_ipc_msg_type_t type, uint32_t window_id, const void *data, uint32_t data_len) {
    if (wm_service_pid == 0) return -1;
    
    size_t total_size = sizeof(uint32_t) + sizeof(uint32_t) + data_len;
    uint8_t *payload = malloc(total_size);
    if (!payload) return -1;
    
    memcpy(payload, &type, sizeof(uint32_t));
    memcpy(payload + sizeof(uint32_t), &window_id, sizeof(uint32_t));
    if (data && data_len > 0) {
        memcpy(payload + sizeof(uint32_t) * 2, data, data_len);
    }
    
    eclib_err_t ret = ipc_send_msg(wm_service_pid, type, payload, total_size, 0, NULL);
    free(payload);
    
    return ret == ECLIB_OK ? 0 : -1;
}

int gt_ipc_recv_msg(gt_ipc_msg_t *msg, int timeout) {
    (void)msg;
    (void)timeout;
    return -1;
}
