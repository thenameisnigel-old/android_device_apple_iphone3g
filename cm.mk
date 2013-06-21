#
# Copyright (C) 2013 Norris Enterprises
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

## Specify phone tech before including full_phone
$(call inherit-product, vendor/cm/config/gsm.mk)

# Release name
PRODUCT_RELEASE_NAME := iPhone3G

# Bootanimation
TARGET_SCREEN_HEIGHT := 800
TARGET_SCREEN_WIDTH := 480

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/apple/iphone3g/full_iphone3g.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := iPhone3G
PRODUCT_NAME := cm_iphone3g
PRODUCT_BRAND := Apple
PRODUCT_MODEL := A1241 

#Set build fingerprint
PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=iPhone3G TARGET_DEVICE=iPhone3G BUILD_FINGERPRINT=samsung/SPH-D710/SPH-D710:4.1.2/JZO54K/SPH-D710.GB27:user/release-keys PRIVATE_BUILD_DESC="SPH-D710-user 4.1.2 JZO54K SPH-D710.GB27 release-keys"
