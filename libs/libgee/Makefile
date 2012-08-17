# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libgee
PKG_VERSION:=0.5.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://ftp.gnome.org/pub/GNOME/sources/libgee/0.5/
PKG_MD5SUM:=fc5a36eb5f61154a1456cbb8b1798e41

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

define Package/libgee
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE+=library
  DEPENDS:=+glib2 +libpthread
endef


define Package/libgee/description
  Libgee is a collection library providing GObject-based interfaces and classes
  for commonly used data structures.
endef

EXTRA_LDFLAGS+= \
        -Wl,-rpath-link=$(STAGING_DIR)/usr/lib \
        -L$(ICONV_PREFIX)/lib -L$(INTL_PREFIX)/lib

CONFIGURE_ARGS+= \
	--disable-fast-install \
	--disable-dependency-tracking \
	--disable-libtool-lock \
	--with-pic \
	--with-gnu-ld

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/gee-1.0/*.h \
		$(1)/usr/include

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
               	$(PKG_INSTALL_DIR)/usr/lib/*.{so*,la} \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc \
		$(1)/usr/lib/pkgconfig
endef

define Package/libgee/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgee.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libgee))
