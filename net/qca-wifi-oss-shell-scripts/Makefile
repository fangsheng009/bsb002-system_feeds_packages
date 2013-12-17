include $(TOPDIR)/rules.mk

PKG_NAME=qca-wifi-oss-shell-scripts
PKG_VERSION=1
PKG_RELEASE=1

include $(INCLUDE_DIR)/package.mk

define Package/qca-wifi-oss-shell-scripts
  SECTION:=net
  TITLE:=qca-wifi scripts
  MAINTAINER:=Matthew McClintock <mmcclint@qca.qualcomm.com>
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
	$(CP) -a ./files/* $(1)/
endef

$(eval $(call BuildPackage,qca-wifi-oss-shell-scripts))
