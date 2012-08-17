# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gssdp
PKG_VERSION:=0.7.2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://ftp.gnome.org/pub/GNOME/sources/gssdp/0.7/
PKG_MD5SUM:=7280956344e9c53c9afff0d08bf8cecf

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/gssdp
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=GSSDP framework
  URL:=http://www.gupnp.org/
  DEPENDS+= +glib2 +libpthread +libsoup
endef


define Package/gssdp/description
	GSSDP implements resource discovery and announcement over SSDP.
endef

EXTRA_LDFLAGS+= \
        -Wl,-rpath-link=$(STAGING_DIR)/usr/lib \
        -L$(ICONV_PREFIX)/lib -L$(INTL_PREFIX)/lib

CONFIGURE_ARGS+= \
	--disable-maintainer-mode \
	--enable-shared \
	--enable-static \
	--disable-fast-install \
	--disable-dependency-tracking \
	--disable-libtool-lock \
	--enable-debug \
	--disable-gtk-doc \
	--without-gtk \
	--with-pic \
	--with-gnu-ld \
	--without-html-dir

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/gssdp-1.0/libgssdp \
		$(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
                $(PKG_INSTALL_DIR)/usr/lib/*.{so*,a,la} \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc \
		$(1)/usr/lib/pkgconfig
endef

define Package/gssdp/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgssdp-1.0.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,gssdp))
