# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ffmpeg-old
PKG_VERSION:=0.5
PKG_RELEASE:=1

PKG_SOURCE:=ffmpeg-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://ffmpeg.org/releases/
PKG_MD5SUM:=

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

define Package/ffmpeg-old
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE+= program
  DEPENDS:=+glib2 +libpthread +libbz2
endef


define Package/ffmpeg-old/description
  FFmpeg is the leading multimedia framework, able to decode, encode, transcode,
  mux, demux, stream, filter and play pretty much anything that humans and
  machines have created.
endef

FFMPEG_CONFIGURE:= \
	CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS) $(FPIC)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	./configure \
	--enable-cross-compile \
    --cross-prefix="$(TARGET_CROSS)" \
    --arch="$(ARCH)" \
    --target-os=linux \
    --prefix="/usr" \
	--enable-shared \
	--enable-static \
	--enable-gpl \
	--enable-pthreads \
	--enable-swscale \
	--enable-postproc \
	--enable-avfilter \
	--disable-altivec \
	--disable-mmx \
	--disable-mmx2 \
	--disable-ssse3 \
	--disable-armv5te \
	--disable-armv6 \
	--disable-armvfp \
	--disable-iwmmxt \
	--disable-mmi \
	--disable-neon \
	--disable-vis \
	--disable-network \
	--disable-ipv6 \
	--disable-mpegaudio-hp \
	--enable-gray \
	--disable-ffmpeg \
	--disable-ffplay \
	--disable-ffserver \
	--enable-hardcoded-tables \
	--disable-bsfs \
	--disable-devices \
	--enable-extra-warnings

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
	wget http://ffmpeg.org/releases/$(PKG_SOURCE)
	tar -jxvf $(PKG_SOURCE)
	$(CP) ./ffmpeg-$(PKG_VERSION)/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
    ( cd $(PKG_BUILD_DIR); $(FFMPEG_CONFIGURE) )
endef

FFMPEG_LIBS= libavcodec libavdevice libavfilter libavformat libavutil \
	libpostproc libswscale

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(foreach lib,$(FFMPEG_LIBS), \
	  $(CP) $(PKG_INSTALL_DIR)/usr/include/$(lib) $(1)/usr/include/; )

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/*.so* \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc \
		$(1)/usr/lib/pkgconfig
endef

define Package/ffmpeg-old/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
	rm -rf ./ffmpeg*
endef

$(eval $(call BuildPackage,ffmpeg-old))
