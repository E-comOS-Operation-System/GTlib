# ==============================================================================
# GTlib - Terminal text GUI Library of E-comOS
# Makefile for building GTlib library
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# ==============================================================================
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -Isrc
SRCDIR = src
OBJDIR = obj
LIBDIR = lib

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(LIBDIR)/libgtlib.a

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(LIBDIR)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -rf $(OBJDIR) $(LIBDIR)