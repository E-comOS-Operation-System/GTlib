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
#ifdef ECLIB_UTILS_H
#define ECLIB_UTILS_H
#include <stddef.h>
#include <stdint.h>
// --------------------------
// String 
// --------------------------
size_t eclib_strlen(const char* str);
char* eclib_strncpy(char* dest, const char* src, size_t max_len);
int eclib_strcmp(const char* str1, const char* str2);
const char* eclib_strstr(const char* str, const char* substr);
// --------------------------
// Mentory
// --------------------------
void* eclib_memcpy(void* dest, const void* src, size_t len);
void* eclib_memmove(void* dest, const void* src, size_t len);void* eclib_memset(void* ptr, int value, size_t len);
// --------------------------
// Char
// --------------------------
int eclib_isdigit(int c);
int eclib_isalpha(int c);
int eclib_tolower(int c);
int eclib_toupper(int c);
#endif