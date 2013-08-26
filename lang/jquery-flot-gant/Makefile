include $(TOPDIR)/rules.mk

PKG_NAME:=jquery-flot-gant
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git@github.qualcomm.com:streamboost/jquery-flot-gant.git
PKG_BRANCH:=master
PKG_RELEASE:=1

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_REV:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
  PKG_VERSION:=0.1-g$(PKG_REV)
endif
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_MIRROR:=none

include $(INCLUDE_DIR)/package-version-override.mk
include $(INCLUDE_DIR)/package.mk

define Package/jquery-flot-gant
  SECTION:=language-javascript
  CATEGORY:=Languages
  SUBMENU:=JavaScript
  TITLE:=jQuery Flot Gant Chart Plugin
  URL:=http://jqueryui.com/
  DEPENDS:=+jquery-flot
endef

define Package/jquery-flot-gant/description
  Gant Chart plugin for jQuery flot
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/jquery-flot-gant/install
	$(INSTALL_DIR) $(1)/www/js/
	cp $(PKG_BUILD_DIR)/jquery.flot.gant.js $(1)/www/js/
endef

$(eval $(call BuildPackage,jquery-flot-gant))
