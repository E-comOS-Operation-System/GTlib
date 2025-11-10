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
void* eclib_malloc(size_t size);

void eclib_free(void* addr);

void* eclib_calloc(size_t nmemb, size_t size);

void* eclib_realloc(void* ptr, size_t size);

#endif