include $(TOPDIR)/rules.mk

PKG_NAME:=jquery-contextmenu
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git@github.qualcomm.com:streamboost/jquery-contextmenu.git
PKG_BRANCH:=master
PKG_RELEASE:=1

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_REV:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
  PKG_VERSION:=1.01-g$(PKG_REV)
endif
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_MIRROR:=none

include $(INCLUDE_DIR)/package-version-override.mk
include $(INCLUDE_DIR)/package.mk

define Package/jquery-contextmenu
  SECTION:=language-javascript
  CATEGORY:=Languages
  SUBMENU:=JavaScript
  TITLE:=jQuery context menu
  URL:=http://abeautifulsite.net/2008/09/jquery-context-menu-plugin/
  DEPENDS:=+jquery
endef

define Package/jquery-contextmenu/description
	A jquery context menu plugin
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/jquery-contextmenu/install
	$(INSTALL_DIR) $(1)/www/js/
	$(INSTALL_DIR) $(1)/www/css/
	cp $(PKG_BUILD_DIR)/js/jquery.contextMenu.js $(1)/www/js/
	cp $(PKG_BUILD_DIR)/css/jquery.contextMenu.css $(1)/www/css/
endef

$(eval $(call BuildPackage,jquery-contextmenu))
