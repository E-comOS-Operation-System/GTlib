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
#ifndef ECLIB_SERVICE_H
#define ECLIB_SERVICE_H
#include "error.h"
#include "ipc_message.h"
#include <stdint.h>
#include <stddef.h>
// ---------------------
// The connted code with service registry
// ---------------------
#define SERVICE_CMD_LOOKUP    0x5001  // FOUND SERVICE
#define SERVICE_CMD_REGISTER  0x5002  // REGISTER SERVICE 
#define SERVICE_CMD_UNREGISTER 0x5003 // LOG OUT SERVICE
#define SERVICE_CMD_RESP      0x5004  
// ---------------------
// Communication structure (request/response format)
// ---------------------

typedef struct {
    char service_name[64]; // Service name
}service_lookup_req_t;

typedef struct {
    uint32_t service_pid; // Service PID (0 if not found)
    eclib_err_t err;      // Error code
}service_lookup_resp_t;

typedef struct {
    char service_name[64];  
    uint32_t pid;           
} service_register_req_t;

typedef struct {
    eclib_err_t err;        // ERROR CODE
} service_register_resp_t;

typedef struct {
    char service_name[64];
} service_unregister_req_t;

typedef struct {
    eclib_err_t err;        // ERROR CODE
} service_unregister_resp_t;
// ---------------------
// External Interface
// ---------------------
/*
* Found service's PID
* Parameter:
*    service_name: The name of the service to look up
* Return Value:
*    On success: service PID (non-zero)
*    On failure: 0 (and sets the last error code)
*/
uint32_t eclib_service_lookup(const char* service_name);

/*
* Register a service
* Parameter:
*    service_name: The name of the service to register
* Return Value:
*    On success: ECLIB_ERR_OK
*    On failure: The error code
*/
eclib_err_t eclib_service_register(const char* service_name);

/*
* Unregister a service
* Parameter:
*    service_name: The name of the service to unregister
* Return Value:
*    On success: ECLIB_ERR_OK
*    On failure: The error code
*/
eclib_err_t eclib_service_unregister(const char* service_name);
/*
* Get now service PID
* Return:Now service PID
*/
uint32_t eclib_getpid(void);
#endif // ECLIB_SERVICE_H