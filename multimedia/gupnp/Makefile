# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gupnp
PKG_VERSION:=0.13.5
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://ftp.gnome.org/pub/GNOME/sources/gupnp/0.13/
PKG_MD5SUM:=b3c003ceeca44dc02215c545ef28bf8d

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/gupnp
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=GUPnP framework
  URL:=http://www.gupnp.org/
  DEPENDS+= +glib2 +libsoup +gssdp +libuuid +libdbus-glib +gssdp
endef


define Package/gupnp/description
  GUPnP implements the UPnP specification: resource announcement and discovery,
  description, control, event notification, and presentation
  (GUPnP includes basic web server functionality through libsoup).
endef

EXTRA_LDFLAGS+= \
        -Wl,-rpath-link=$(STAGING_DIR)/usr/lib \
        -L$(ICONV_PREFIX)/lib -L$(INTL_PREFIX)/lib

CONFIGURE_ARGS+= \
	--disable-introspection \
	--disable-maintainer-mode \
	--enable-shared \
	--disable-static \
	--disable-fast-install \
	--disable-dependency-tracking \
	--disable-libtool-lock \
	--disable-largefile \
	--enable-debug \
	--disable-gtk-doc \
	--with-pic \
	--with-gnu-ld \
	--without-html-dir \
	--with-context-manager=unix

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/gupnp-1.0/libgupnp \
		$(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/*.{so*,la} \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc \
		$(1)/usr/lib/pkgconfig
endef

define Package/gupnp/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libgupnp-1.0.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,gupnp))
