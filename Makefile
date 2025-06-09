TARGET := timer_app
BUILD := build
OUTPUT := output
ROMFS := romfs

APP_TITLE := Timer App
APP_AUTHOR := Autore
APP_VERSION := 1.0

SOURCES := source/main.cpp

include $(DEVKITPRO)/libnx/switch_rules
