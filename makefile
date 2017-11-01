# Target specific macros
TARGET = test
TARGET_SOURCES := \
	src/main.c \
	src/path.c
TOPPERS_OSEK_OIL_SOURCE := src/main.oil

O_PATH ?= build

include ~/nxtOSEK/ecrobot/ecrobot.mak
