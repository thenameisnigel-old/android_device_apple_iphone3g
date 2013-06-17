LOCAL_PATH := $(call my-dir)
COMMON := $(dir $(LOCAL_PATH))common

BOARD_HAS_VIBRATOR := ../../vendor/apple/iPhone3G/vibrator/vibrator.c

include $(CLEAR_VARS)
LOCAL_SRC_FILES := gpio-keys.kcm
LOCAL_MODULE_TAGS := eng
include $(BUILD_KEY_CHAR_MAP)

SUBDIRS := \
	$(LOCAL_PATH)/../libril/pmb8878/Android.mk \
	$(LOCAL_PATH)/libsensors/Android.mk \
	$(COMMON)/AndroidBoardCommon.mk

include $(SUBDIRS)
