#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=xrelayd
PKG_VERSION:=0.2.1pre2
PKG_RELEASE:=4

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://znerol.ch/files/xrelayd-0.2.1pre2.tar.gz
PKG_MD5SUM:=05f242295fa864bb3b0b7f0712b4dfa3

include $(INCLUDE_DIR)/package.mk

define Package/xrelayd
  SECTION:=net
  CATEGORY:=Network
  TITLE:=xrelayd
  URL:=http://vmlinux.org/jocke/xrelay.shtml
  DEPENDS:=+qca-libath +libpolarssl_bsd
endef

define Package/xrelayd/description
	A simple SSL tunnel for UN*X and Linux system.
endef
define Package/xrelayd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/xrelay $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,xrelayd))
