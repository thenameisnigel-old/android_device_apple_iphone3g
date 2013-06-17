LOCAL_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
COMMON := $(subst iPhone3G,common,$(LOCAL_DIR))

ifeq ($(TARGET_BUILD_TYPE),debug)
$(call inherit-product, $(SRC_TARGET_DIR)/product/sdk.mk)
else
$(call inherit-product, $(COMMON)/iPhone.mk)
endif

$(call inherit-product, $(COMMON)/common.mk)

PRODUCT_NAME := iPhone3G
PRODUCT_DEVICE := iPhone3G

PRODUCT_PACKAGE_OVERLAYS += vendor/apple/overlay/mbxlite

PRODUCT_COPY_FILES += \
	$(LOCAL_DIR)gpio-keys.kl:system/usr/keylayout/gpio-keys.kl \
	$(LOCAL_DIR)asound.conf:system/etc/asound.conf \
	$(LOCAL_DIR)asound.state:system/etc/asound.state

