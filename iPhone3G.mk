# Copyright (C) 2013 Norris Enterprises / Project Open Cannibal / CyanogenMod Team
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

LOCAL_PATH := device/apple/iphone3g

$(call inherit-product, device/apple/iphone-common/common.mk

ifeq ($(TARGET_BUILD_TYPE),debug)
$(call inherit-product, $(SRC_TARGET_DIR)/product/sdk.mk)
else
$(call inherit-product, device/apple/iphone-common/iPhone.mk)
endif.mk)

PRODUCT_NAME := iPhone3G
PRODUCT_DEVICE := iPhone3G

PRODUCT_PACKAGE_OVERLAYS += vendor/apple/overlay/mbxlite


# Keylayout
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)gpio-keys.kl:system/usr/keylayout/gpio-keys.kl \
	$(LOCAL_PATH)asound.conf:system/etc/asound.conf \
	$(LOCAL_PATH)asound.state:system/etc/asound.state
	



