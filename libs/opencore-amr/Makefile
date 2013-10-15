include $(TOPDIR)/rules.mk

PKG_NAME:=opencore-amr
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://git.code.sf.net/p/opencore-amr/code
PKG_REV:=v0.1.3
PKG_VERSION:=v0.1.3

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_MIRROR:=none
PKG_FIXUP:=autoreconf libtool

include $(INCLUDE_DIR)/uclibc++.mk
include $(INCLUDE_DIR)/package.mk

# use SPACES here instead of tabs
define Package/$(PKG_NAME)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:= Audio codecs extracted from Android Open Source Project
  DEPENDS:=$(CXX_DEPENDS)
  MAINTAINER:=Matthew McClintock <mmcclint@qca.qualcomm.com>
endef

define Package/$(PKG_NAME)/description
  Audio codecs extracted from Android Open Source Project
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		DESTDIR=$(PKG_INSTALL_DIR) \
	       	install
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(call Package/$(PKG_NAME)/install, $(1))
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
