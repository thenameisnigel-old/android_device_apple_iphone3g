#
# Copyright (C) 2011 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


# This variable is set first, so it can be overridden
# by BoardConfigVendor.mk
-include device/apple/iphone-common/BoardCommonConfig.mk

# Kernel Config
TARGET_KERNEL_SOURCE := kernel/apple/idevice
TARGET_KERNEL_CONFIG := needs to be set

#Camera 
USE_CAMERA_STUB := false    # Last time Im saying no fucking camera stub

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := need to create first

# Notification LED
BOARD_HAS_LED_NOTIF := false

# RIL
BOARD_MOBILEDATA_INTERFACE_NAME := "ppp0"

# Recovery
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../device/apple/iphone3g/recovery/recovery_keys.c
BOARD_USE_CUSTOM_RECOVERY_FONT := \"roboto_10x18.h\"

TARGET_SPECIFIC_HEADER_PATH := device/samsung/d710/include

# Use the non-open-source parts, if they're present
-include vendor/apple/iphone3g/BoardConfigVendor.mk


#WiFi Shit
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := 
#WPA_SUPPLICANT_VERSION      := VER_0_6_X
#BOARD_WLAN_DEVICE           := libertas_sdio
#WIFI_DRIVER_MODULE_PATH     := "/system/lib/modules/libertas_sdio.ko"
#WIFI_DRIVER_MODULE_ARG      := ""
#WIFI_DRIVER_MODULE_NAME     := "libertas_sdio"

