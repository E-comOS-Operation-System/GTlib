/*
 * ECLib - E-comOS C Library
 * Copyright (C) 2025 E-comOS Kernel Mode Team & Saladin5101
 * 
 * This file is part of ECLib.
 * ECLib is free library; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 */
#include "error.h"
#include "ipc_message.h"
#include <stdint.h>
#include <stddef.h>

#ifndef ECLIB_FILE_H
#define ECLIB_FILE_H

typedef long ssize_t;
// ---------------------------
// Basic type definition
// ---------------------------
// File handle definition
typedef uint32_t eclib_file_t;
// Invalid file handle (indicating that the open/operation failed)
#define ECLIB_FILE_INVALID (-1)
// ---------------------------
// File open mode
// ---------------------------
// File open mode definition
#define ECLIB_FILE_MODE_READ  0x01 // Only read
#define ECLIB_FILE_MODE_WRITE 0x02 // Only write
#define ECLIB_FILE_MODE_READ_WRITE 0x03 // Read and write
#define ECLIB_FILE_MODE_CREATE 0x04 // Create file if not exists

// ---------------------------
// Chat with file service 
// ---------------------------
#define ECLIB_FILE_CMD_OPEN    0x1001 //Open file
#define ECLIB_FILE_CMD_READ    0x1002 //Read file
#define ECLIB_FILE_CMD_WRITE   0x1003 //Write file
#define ECLIB_FILE_CMD_CLOSE   0x1004 //Close file
#define ECLIB_FILE_CMD_GET_LEN 0x1005 //Get file length
// file_control return codes
#define ECLIB_FILE_CMD_RESP    0x1006 

// ---------------------------
// IPC messages POST and SENT
// ---------------------------
typedef struct {
    char filename[256];
    uint8_t mode;
} eclib_file_open_req_t;

typedef struct {
    eclib_file_t file;
    eclib_err_t err;
} eclib_file_open_resp_t;

typedef struct {
    eclib_file_t file;
    size_t max_len;  
} eclib_file_read_req_t;

typedef struct {
    uint8_t* data;       // Read data buffer pointer (allocated by caller, size = max_len)
    size_t actual_len;   // Read bytes length
    eclib_err_t err;     // Error code
} eclib_file_read_resp_t;

typedef struct {
    eclib_file_t file;
    const uint8_t* data; // Data buffer pointer
    size_t data_len;     // Data length to write
} eclib_file_write_req_t;

typedef struct {
    size_t actual_len;   // Actual written bytes length
    eclib_err_t err;     // Error code
} eclib_file_write_resp_t;

typedef struct {
    eclib_file_t file;
    char filename[256];
} eclib_file_close_req_t;

typedef struct {
    eclib_err_t err;     // Error code
} eclib_file_close_resp_t;

typedef struct {
    eclib_file_t file;
    char filename[256];
} eclib_file_get_len_req_t;

typedef struct {
    size_t len;          // File total length
    eclib_err_t err;     // Error code
} eclib_file_get_len_resp_t;
// ---------------------------
// The file operation functions provided externally (directly called by users, internally communicating with file_control via IPC)
// ---------------------------
/* HELP AND USEAGE
* Parameters:
*   filename: File path (e.g., "/ssd/data/log.txt")
*   mode: Open mode (ECLIB_FILE_MODE_XXX combination)
* Return value:
*   Success: Valid eclib_file_t handle
*   Failure: ECLIB_FILE_INVALID (the specific error code can be obtained via eclib_get_last_err())
*/
eclib_file_t eclib_file_open(const char* filename, uint8_t mode);
/*
* Read data from a file
* Parameters:
*   file: Handle to the opened file
*   buf: User buffer (used to store the read data)
*   max_len: Maximum buffer capacity (maximum number of bytes to read)
* Return value:
*   Success: The number of bytes actually read (0 indicates the end of the file)
*   Failure: -1 (error code obtained via eclib_get_last_err())
*/
ssize_t eclib_file_read(eclib_file_t file, void* buf, size_t max_len);
/*
* Write data to a file
* Parameters:
*   file: Handle to the opened file
*   buf: User buffer (contains the data to be written)
*   len: Number of bytes to write
* Return value:
*   Success: The number of bytes actually written
*   Failure: -1 (error code obtained via eclib_get_last_err())
*/
ssize_t eclib_file_write(eclib_file_t file, const void* buf, size_t len);
/*
* Close an opened file
* Parameters:
*   file: Handle to the opened file
* Return value:
*   ECLIB_OK: Success
*   Other: Failure (error code obtained via eclib_get_last_err())
*/
eclib_err_t eclib_file_close(eclib_file_t file);
/*
* Get the total length of the file (in bytes)
* Parameters:
* file: Handle to the opened file (can be ECLIB_FILE_INVALID)
* filename: If file is invalid, use this filename to search (e.g., "/ssd/config.ini")
* Return:
* Success: File length (in bytes)
* Failure: -1 (error code obtained via eclib_get_last_err())
*/
ssize_t eclib_file_get_length(eclib_file_t file, const char* filename);
#endif // ECLIB_FILE_H
