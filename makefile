# Target specific macros
TARGET = test
TARGET_SOURCES := \
	./main.c
TOPPERS_OSEK_OIL_SOURCE := ./main.oil

O_PATH ?= build

include ~/nxtOSEK/ecrobot/ecrobot.mak
