#!/bin/bash


frama-c -wp -wp-rte src/window.c -cpp-extra-args="-Iinclude -Isrc"
# A other option
# frama-c -val src/window.c -cpp-extra-args="-Iinclude -Isrc"
