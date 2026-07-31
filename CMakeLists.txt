# FieldSense-Z Zephyr application
#
# Checkpoint: first ESP32 board bring-up.
# No sensor code is included in this checkpoint.

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(fieldsense_z)

target_sources(app PRIVATE src/main.c)