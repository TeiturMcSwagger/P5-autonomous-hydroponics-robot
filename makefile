# Target specific macros
TARGET = leetOSEK
TARGET_SOURCES := main.c path.c turn.c nxtMotorController.c
TOPPERS_OSEK_OIL_SOURCE := main.oil

O_PATH ?= build

include ~/nxtOSEK/ecrobot/ecrobot.mak
