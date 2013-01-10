#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=vala
PKG_VERSION:=0.7.9
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://ftp.gnome.org/pub/GNOME/sources/vala/0.7/
PKG_MD5SUM:=f2f8b2914361db599fd6392ec27f7042

PKG_BUILD_DEPENDS:=glib2 vala/host
HOST_BUILD_DEPENDS:=glib2/host

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

TARGET_LDFLAGS+=\
	-Wl,-rpath-link=$(STAGING_DIR)/usr/lib

define Package/vala
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=C-sharp like language for the GObject system
  DEPENDS:=+glib2
  URL:=http://live.gnome.org/Vala
endef

define Package/vala/description
Vala is a C-sharp like language for the GObject system. This package contains
the Vala-to-C compiler.
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		all install
endef

define Build/InstallDev
	$(INSTALL_DIR) \
		$(1)/usr/share/vala/vapi \
		$(1)/usr/lib \
		$(1)/usr/lib/pkgconfig \
		$(1)/usr/bin

	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/share/vala/vapi/* \
		$(1)/usr/share/vala/vapi

	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/libvala.{so*,la} \
		$(1)/usr/lib

	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/bin/valac \
		$(1)/usr/bin

	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc \
		$(1)/usr/lib/pkgconfig
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,vala))
