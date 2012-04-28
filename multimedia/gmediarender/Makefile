# 
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gmediarender
PKG_VERSION:=0.0.6
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://savannah.nongnu.org/download/gmrender
PKG_MD5SUM:=4fc1d5ce6ef2c27fae01d3e3fdc46240

PKG_BUILD_PARALLEL:=0

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/gmediarender
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=UPnP A/V & DLNA Media Render
  URL:=http://gmrender.nongnu.org
  DEPENDS:= +gstreamer +gst-mod-playbin +libupnp +libxml2 +zlib
endef

define Package/gmediarender/description
  GMediaRender is a UPnP™ media renderer for POSIX®-compliant systems.
  It implements the server component that provides UPnP controllers a means to render media content (audio, video and images) from a UPnP media server.
endef

EXTRA_LDFLAGS+=-lixml -lthreadutil -lz

CONFIGURE_ARGS+= \
	--with-libupnp=$(STAGING_DIR)/usr \
	ac_cv_lib_upnp_UpnpInit=yes

define Package/gmediarender/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/gmediarender $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/share/gmediarender
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/data/grender-64x64.png $(1)/usr/share/gmediarender
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/data/grender-128x128.png $(1)/usr/share/gmediarender
	$(INSTALL_BIN) ./files/gmediarender.init $(1)/etc/init.d/gmediarender
	$(INSTALL_CONF) files/$(PKG_NAME).config $(1)/etc/config/$(PKG_NAME)
endef

$(eval $(call BuildPackage,gmediarender))
