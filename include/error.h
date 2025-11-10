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
#ifndef ECLIB_ERROR_REPOERT
#define ECLIB_ERROR_REPOERT

#define ECLIB_OK          0
// =========== UNKNOWN ERRORS MESSAGES ===========
// ERROR CODE FROM -100000000 TO -199999999
#define ECLIB_ERR_UNKNOWN               -100000000 // Pulic unknown error (I fuck this error)
#define ECLIB_IPC_MESSAGES_UNKNOWN      -100000001 // IPC unknown error (I hope our users never can find it in our logs)
#define ECLIB_RUI_UNKNOWN               -100000002 // RUI GUI unknown error (Well , who can tell me our users can saw logs?)
#define ECLIB_KERNEL_UNKNOWN            -100000003 // kernel unknown error (If users cannot see our logs , we deltel it , okay?)
#define ECLIB_ECLIB_UNKNOWN             -100000004 // ECLib unknown error (Not okay , cause ... if our users is developers ... I don't want to be a "fuckeder")
#define ECLIB_UNKNOWN_UNKNOWN           -100000005 // If ... One fuck developer didn't register a module and it need a error code
// =========== KERNEL ERRORS MESSAGES ===========
// ERROR CODE FROM 0x00 TO 0x10
#define ECLIB_KERNEL_TO_USER_MODE       0x00 // Cannot find user mode (I hope it isn't)
#define ECLIB_KERNEL_CAN_NOT_FOUND_SSD  0x01 // Cannot find disk (WHAT THE FUCK IS THIS)
#define ECLIB_KERNEL_CAN_NOT_FOUND_UEFI_OR_BIOS  0x02 //Cannot find UEFI/BIOS - Whaaat!?
#define ECLIB_KERNEL_CAN_NOT_FOUND_DOS25 0x03 // Cannot find DOS25 (How am I supposed to boot without DOS25!?)
#define ECLIB_KERNEL_MEMORY_SCHEDULING 0x04 // A critical process was killed during memory scheduling, and the kernel could no longer continue running.
#define ECLIB_KERNEL_FUCK_USER_WHY_YOU_EDIT_KERNEL 0x05 // Stupid user made a custom kernel and it conflicted with the original kernel.
#define ECLIB_KERNEL_IMAGE_BAD           0x06 // Corrupted image file (kernel)
#define ECLIB_KERNEL_CRITICAL_PROCESS_FAIL 0x07 // Critical user-mode service (e.g., memory manager) failed to start (Microkernel can't live without it!)
#define ECLIB_KERNEL_OUT_OF_MEMORY 0x08 // Kernel ran out of its own memory (How the hell did you even do this?)
#define ECLIB_KERNEL_INTERRUPT_CONTROLLER_FAIL 0x09 // Interrupt controller (APIC/IOAPIC) init failed (Hardware's ignoring us, great)
#define ECLIB_KERNEL_USER_SERVICE_REG_FAIL 0x0A // User-mode service failed to register with kernel (Service is shy? Or just broken?)
#define ECLIB_KERNEL_INVALID_PARAM 0x0B // Kernel got invalid boot parameters (Who passed "lol" as memory size?!)
#define ECLIB_KERNEL_CPU_UNSUPPORTED 0x0C // CPU doesn't support required instructions (This CPU is from 2001, stop using it!)
#define ECLIB_KERNEL_DEVICE_DRIVER_FAIL 0x0D // A critical device driver failed to load (No keyboard driver? Seriously?)
#define ECLIB_KERNEL_FILESYSTEM_FAIL 0x0E // Filesystem initialization failed (Disk is borked or missing?)
#define ECLIB_KERNEL_HARDWARE_INCOMPATIBLE 0x0F // Detected incompatible hardware (Did you try to run this on a toaster?)
// =========== IPC ERRORS MESSAGES ===========
// ERROR CODE FROM 0x10 TO 0x30 OR FROM -1000 TO -1
#define ECLIB_IPC_MSG_QUEUE_FULL        -1000 // Message queue is full (Too many messages, slow down!)
#define ECLIB_IPC_MSG_NOT_FOUND         -1001 // Message not found (Did you lose it?)
#define ECLIB_IPC_INVALID_MSG_FORMAT    -1002 // Invalid message format (Check your message structure!)
#define ECLIB_IPC_PERMISSION_DENIED     -1003 // Permission denied (You shall not pass!)
#define ECLIB_IPC_TIMEOUT               -1004 // Operation timed out (Patience is a virtue!)
#define ECLIB_IPC_CONNECTION_LOST        -1005 // Connection lost (Where did it go?)
#define ECLIB_IPC_INVALID_ENDPOINT      -1006 // Invalid endpoint (Are you sure this endpoint exists?)
#define ECLIB_IPC_BUFFER_OVERFLOW        -1007 // Buffer overflow (Whoa, that's too much data!)
#define ECLIB_IPC_SERVICE_UNAVAIL        -1008 // IPC service unavailable (Service not started or unreachable!)
#define ECLIB_IPC_CANNOT_FOUND_WHO_RECEIVE_MESSAGE 0x10 // Cannot find who receive the message (Are they hiding?)
#define ECLIB_IPC_CANNOT_FOUND_WHO_SEND_MESSAGE 0x11 // Cannot find who send the message (Did they ghost you?)
// =========== RUI ERRORS MESSAGES ===========
// ERROR CODE FROM -2000 TO -1001 OR FROM 0x30 TO 0x100
#define ECLIB_RUI_WINDOW_NOT_FOUND      -2000 // Window not found (Did you close it?)
#define ECLIB_RUI_INVALID_COLOR_CODE    -2001 // Invalid color code (Check your colors!)
#define ECLIB_RUI_FONT_NOT_AVAILABLE    -2002 // Font not available (Missing font file?)
#define ECLIB_RUI_RENDERING_ERROR       -2003 // Rendering error (Graphics card acting up?)
#define ECLIB_RUI_EVENT_QUEUE_FULL      -2004 // Event queue is full (Too many events, slow down!)
#define ECLIB_RUI_INVALID_EVENT_TYPE     -2005 // Invalid event type (What kind of event is that?)
#define ECLIB_RUI_CANNOT_LOAD_RESOURCE   -2006 // Cannot load resource (File missing or corrupted?)
#define ECLIB_RUI_UNSUPPORTED_OPERATION  -2007 // Unsupported operation (This feature isn't implemented yet!)
#define ECLIB_RUI_WIDGET_NOT_FOUND       0x30 // Widget not found (Did you delete it?)
#define ECLIB_RUI_INVALID_LAYOUT         0x31 // Invalid layout (Check your layout settings!)
#define ECLIB_RUI_THEME_NOT_AVAILABLE    0x32 // Theme not available (Missing theme files?)
#define ECLIB_RUI_ANIMATION_ERROR        0x33 // Animation error (Graphics card struggling?)
#define ECLIB_RUI_CANNOT_CREATE_WINDOW   0x34 // Cannot create window (Resource limits reached?)
#define ECLIB_RUI_INVALID_WIDGET_STATE   0x35 // Invalid widget state (Is the widget initialized?)
#define ECLIB_RUI_CANNOT_START           0x36 // Cannot start RUI system (Critical failure during initialization!)
#define ECLIB_RUI_CANNOT_FIND_FONT_FILE   0x37 // Cannot find font file (Font file missing from resources!)
#define ECLIB_RUI_CANNOT_FIND_CONTROLS   0x38 // Cannot find controls (Controls resource missing or corrupted!)
// =========== ECLIB ERRORS MESSAGES ===========
// ERROR CODE FROM -3000 TO -2001 OR FROM 0x100 TO 0x200
#define ECLIB_ECLIB_INIT_FAIL           -3000 // ECLib initialization failed (Critical failure during ECLib startup!)
#define ECLIB_ECLIB_INVALID_CONFIG     -3001 // Invalid ECLib configuration (Check your ECLib settings!)
#define ECLIB_ECLIB_MISSING_DEPENDENCY  -3002 // Missing ECLib dependency (Required library not found!)
#define ECLIB_ECLIB_VERSION_MISMATCH   -3003 // ECLib version mismatch (Incompatible ECLib version detected!)
#define ECLIB_ECLIB_RESOURCE_LIMIT     -3004 // ECLib resource limit
#define ECLIB_ECLIB_UNSUPPORTED_PLATFORM -3005 // Unsupported platform (ECLib not supported on this OS!)
#define ECLIB_ECLIB_CANNOT_ALLOCATE_MEMORY -3006 // Cannot allocate memory (Out of memory during ECLib operation!)
#define ECLIB_ECLIB_INVALID_OPERATION   -3007 // Invalid ECLib operation (Operation not allowed in current state!)
#define ECLIB_ECLIB_CANNOT_FIND_MODULE   0x100 // Cannot find
#define ECLIB_ECLIB_INVALID_MODULE_STATE 0x101 // Invalid module state (Is the module initialized?)
#define ECLIB_ECLIB_CANNOT_LOAD_LIBRARY  0x102 // Cannot load library (Shared library missing or corrupted!)
#define ECLIB_ECLIB_FUNCTION_NOT_FOUND   0x103 // Function not found
#define ECLIB_ECLIB_INVALID_PARAMETER   0x104 // Invalid parameter (Check function arguments!)
#define ECLIB_ECLIB_OPERATION_TIMEOUT    0x105 // Operation timeout (Operation
#define ECLIB_ECLIB_UNEXPECTED_ERROR    0x106 // Unexpected error (An unknown error occurred during ECLib operation!)
#define ECLIB_ECLIB_CANNOT_INITIALIZE_SUBSYSTEM 0x107 // Cannot initialize subsystem (Critical failure during subsystem startup!)
#define ECLIB_ECLIB_DEPENDENCY_VERSION_MISMATCH 0x108 // Dependency version mismatch (Incompatible version of a required dependency detected!)
#define ECLIB_ECLIB_CANNOT_FIND_RESOURCE 0x109 // Cannot find resource (Required resource file missing or corrupted!)
#define ECLIB_ECLIB_INSUFFICIENT_PERMISSIONS 0x10A // Insufficient permissions (Operation requires higher privileges!)
#endif
