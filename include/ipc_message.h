/*
 * ECLib - E-comOS C Library
 * Copyright (C) 2025 E-comOS Kernel Mode Team & Saladin5101
 * 
 * This file is part of ECLib.
 * ECLib is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 */

#ifndef ECLIB_IPC_MESSAGE_H
#define ECLIB_IPC_MESSAGE_H

#include "error.h"  // Include error code definitions
#include <stdint.h>
#include <stddef.h>

// Define error type (consistent with error.h)
typedef int eclib_err_t;

// --------------------------
// Child process protection
// --------------------------
/*
 * Protect background child processes from being reclaimed by kernel when main process exits
 * Description: After calling, all child processes of current main process (including future ones) will be marked as "independent processes".
 *              Kernel will not trigger SIGTERM/SIGKILL to child processes when main process exits (manual management required).
 * Return:
 *   ECLIB_OK: Success
 *   ECLIB_IPC_SERVICE_UNAVAIL: IPC service not running
 *   ECLIB_IPC_PERMISSION_DENIED: Insufficient permissions
 *   ECLIB_IPC_TIMEOUT: IPC service timeout
 */
eclib_err_t ipc_do_not_kill_sub(void);

// --------------------------
// Message sending
// --------------------------
/*
 * Send a message to target process
 * Parameters:
 *   pid: Target process ID
 *   msg_id: Custom message type ID (e.g., 0x01 for file request)
 *   data: Pointer to message payload (will be copied to ipc_message_t.payload)
 *   data_len: Size of payload (must be <= max IPC payload size)
 *   need_feedback: 1 = send feedback if failed (via ECLIB_IPC_MSG_TYPE_SEND_FAILED), 0 = no feedback
 *   msg_seq: Output unique sequence number (for matching feedback, can be NULL)
 * Return:
 *   ECLIB_OK: Sent successfully
 *   ECLIB_IPC_SERVICE_UNAVAIL: IPC service not running
 *   ECLIB_IPC_PERMISSION_DENIED: No permission to send to target
 *   ECLIB_IPC_TIMEOUT: Timeout
 *   ECLIB_IPC_BUFFER_OVERFLOW: data_len exceeds max payload size
 */
eclib_err_t ipc_send_msg(uint32_t pid, uint16_t msg_id, const void* data, size_t data_len,
                         int need_feedback, uint64_t* msg_seq);

// --------------------------
// Message type and structure
// --------------------------
// Message type: Feedback for send failure (ipc_message_t.message_id will be this value)
#define ECLIB_IPC_MSG_TYPE_SEND_FAILED 0xFF00

/*
 * IPC message structure (used for both sending and receiving)
 * Note: To create a message with payload, allocate memory as:
 *       ipc_message_t* msg = malloc(sizeof(ipc_message_t) + payload_size);
 */
typedef struct {
    uint32_t message_id;      // Unique message ID (e.g., ECLIB_IPC_MSG_TYPE_SEND_FAILED for failure feedback)
    uint32_t sender_pid;      // PID of sender
    uint32_t receiver_pid;    // PID of receiver
    uint32_t payload_size;    // Size of payload (bytes)
    uint8_t payload[];        // Flexible array: actual message data
} ipc_message_t;

// --------------------------
// Message states
// --------------------------
/* When process want to get it sended messages states , call this
* Parameters:
*   msg_seq: Message sequence number (obtained from ipc_send_msg)
*   msg_state: Output message state
* Return:
*   ECLIB_OK: Success
*   ECLIB_IPC_SERVICE_UNAVAIL: IPC service not running
*   ECLIB_IPC_PERMISSION_DENIED: Insufficient permissions
*   ECLIB_IPC_TIMEOUT: IPC service timeout
*/
eclib_err_t ipc_get_msg_state(uint64_t msg_seq, uint8_t* msg_state);

#endif // ECLIB_IPC_MESSAGE_H