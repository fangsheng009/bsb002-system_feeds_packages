# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rygel
PKG_VERSION:=0.4.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://ftp.acc.umu.se/pub/GNOME/sources/rygel/0.4/
PKG_MD5SUM:=79a33b9875eacdcb22d9d195aaf24028

PKG_BUILD_DEPENDS:=vala/host
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

define Package/rygel
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=UPnP A/V & DLNA Media Render
  URL:=http://live.gnome.org/Rygel
  DEPENDS+= +glib2 +libpthread +gupnp +gupnp-av +gssdp \
		+vlc +libgee +libsqlite3 +dbus +vala
endef


define Package/rygel/description
  Rygel is a home media solution that allows you to easily share audio, video
  and pictures, and control of media player on your home network.
  In technical terms it is both a UPnP AV MediaServer and MediaRenderer
  implemented through a plug-in mechanism.
  Interoperability with other devices in the market is achieved by conformance
  to very strict requirements of DLNA and on the fly conversion of media to
  format that client devices are capable of handling.
endef

EXTRA_LDFLAGS+= \
        -Wl,-rpath-link=$(STAGING_DIR)/usr/lib \
        -L$(ICONV_PREFIX)/lib -L$(INTL_PREFIX)/lib

CONFIGURE_ARGS+= \
	--enable-maintainer-mode \
	--enable-shared \
	--enable-static \
	--disable-fast-install \
	--disable-dependency-tracking \
	--disable-libtool-lock \
	--enable-debug \
	--with-pic \
	--with-gnu-ld \
	--enable-vala \
	--disable-media-export-plugin \
	--disable-mediathek-plugin \
	--disable-gstlaunch-plugin \
	--disable-tracker-plugin \
	--disable-external-plugin \
	--enable-gst-renderer-plugin

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/rygel-1.0/ \
		$(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/rygel-1.0/*.{so*,la} \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc \
		$(1)/usr/lib/pkgconfig
endef

define Package/rygel/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/rygel-1.0/ $(1)/lib/

	$(INSTALL_DIR) $(1)/share
	$(CP) $(PKG_INSTALL_DIR)/usr/share/* $(1)/share/

	$(INSTALL_DIR) $(1)/etc
	$(CP) $(PKG_INSTALL_DIR)/etc/* $(1)/etc/

	$(INSTALL_DIR) $(1)/root/.config

	$(INSTALL_DIR) $(1)/usr/share/mime
	$(CP) ./files/globs $(1)/usr/share/mime

	$(INSTALL_DIR) $(1)/etc/dbus-1/system.d
	$(CP) ./files/dlnas.conf $(1)/etc/dbus-1/system.d

	$(INSTALL_DATA) ./files/Skifta_icon_LRG.jpg $(1)/share/rygel/xml
	$(INSTALL_DATA) ./files/Skifta_icon_LRG.png $(1)/share/rygel/xml
	$(INSTALL_DATA) ./files/Skifta_icon_SM.jpg $(1)/share/rygel/xml
	$(INSTALL_DATA) ./files/Skifta_icon_SM.png $(1)/share/rygel/xml

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/rygel.init $(1)/etc/init.d/rygel

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/$(PKG_NAME).config $(1)/etc/config/$(PKG_NAME)
endef

$(eval $(call BuildPackage,rygel))
