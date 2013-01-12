# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=vlc
PKG_VERSION:=2.0.5
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=http://download.videolan.org/pub/videolan/vlc/$(PKG_VERSION)
PKG_MD5SUM:=4f959c0766ada8cea5a72c65fce94ebe

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/vlc
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=Audio player
  URL:=http://www.videolan.org/vlc/
  DEPENDS+= +glib2 +libpthread +libmad +libfaad2 +librt +alsa-lib +libid3tag \
	+libstdcpp +libflac +libmpeg2 +libogg +libffmpeg +libvorbisidec
endef


define Package/vlc/description
  VLC is the multimedia player backend designed to render the mediaformats it
  receives through the DLNA software stack.
endef

EXTRA_LDFLAGS+= \
        -Wl,-rpath-link=$(STAGING_DIR)/usr/lib \
        -L$(ICONV_PREFIX)/lib -L$(INTL_PREFIX)/lib

TARGET_CFLAGS +=-std=gnu99

CONFIGURE_ARGS+= \
	--disable-static \
	--enable-shared \
	--disable-maintainer-mode \
	--disable-dependency-tracking \
	--disable-dependency-tracking \
	--disable-macosx \
	--without-macosx-sdk \
	--disable-macosx-audio \
	--disable-libtool-lock \
	--disable-nls \
	--disable-rpath \
	--disable-dbus \
	--disable-dbus-control \
	--disable-telepathy \
	--disable-debug \
	--disable-gprof \
	--disable-cprof \
	--disable-mmx \
	--disable-sse \
	--disable-altivec \
	--disable-optimize-memory \
	--disable-optimizations \
	--disable-run-as-root \
	--disable-coverage \
	--disable-sout \
	--disable-switcher \
	--disable-shout \
	--disable-lua \
	--disable-httpd \
	--disable-libproxy \
	--disable-vlm \
	--disable-growl \
	--disable-notify \
	--disable-taglib \
	--disable-live555 \
	--disable-dc1394 \
	--disable-dv \
	--disable-dvdread \
	--disable-dvdnav \
	--disable-dshow \
	--disable-opencv \
	--disable-smb \
	--disable-dvbpsi \
	--disable-v4l2 \
	--disable-pvr \
	--disable-gnomevfs \
	--disable-libcddb \
	--disable-vcdx \
	--disable-vcd \
	--disable-screen \
	--enable-ogg \
	--disable-mkv \
	--disable-mod \
	--disable-mpc \
	--disable-gme \
	--enable-mad \
	--enable-avcodec \
	--enable-avformat \
	--disable-swscale \
	--disable-postproc \
	--enable-faad \
	--disable-twolame \
	--disable-quicktime \
	--disable-real \
	--disable-realrtsp \
	--disable-libtar \
	--disable-a52 \
	--disable-dca \
	--enable-flac \
	--enable-libmpeg2 \
	--disable-vorbis \
	--enable-tremor \
	--disable-speex \
	--disable-theora \
	--disable-dirac \
	--disable-schroedinger \
	--disable-png \
	--disable-x264 \
	--disable-fluidsynth \
	--disable-zvbi \
	--disable-telx \
	--disable-libass \
	--disable-kate \
	--disable-xvideo \
	--disable-glx \
	--disable-sdl \
	--disable-sdl-image \
	--disable-freetype \
	--disable-fribidi \
	--disable-fontconfig \
	--disable-libxml2 \
	--disable-svg \
	--disable-directx \
	--disable-directfb \
	--disable-aa \
	--disable-caca \
	--disable-wingdi \
	--disable-oss \
	--disable-pulse \
	--disable-portaudio \
	--enable-alsa \
	--disable-waveout \
	--disable-macosx-audio \
	--disable-jack \
	--disable-upnp \
	--disable-skins2 \
	--disable-qt4 \
	--disable-macosx \
	--disable-ncurses \
	--disable-xosd \
	--disable-fbosd \
	--disable-visual \
	--disable-goom \
	--disable-atmo \
	--disable-bonjour \
	--disable-lirc \
	--disable-libgcrypt \
	--disable-gnutls \
	--disable-update-check \
	--disable-loader \
	--enable-vlc \
	--with-pic \
	--with-gnu-ld \
	--without-libintl-prefix \
	--without-x \
	--enable-run-as-root \
	--disable-xcb

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/vlc/ \
		$(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/*.{so*,la} \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/vlc/ \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc \
		$(1)/usr/lib/pkgconfig
endef

define Package/vlc/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/vlc $(1)/usr/bin/
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/cvlc $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/usr/lib
	( cd $(PKG_INSTALL_DIR); $(CP) \
				./usr/lib/libvlccore.so* \
				./usr/lib/libvlc.so* \
				$(1)/usr/lib/ \
	)

	$(INSTALL_DIR) $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/access $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/audio_filter $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/audio_mixer $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/audio_output $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/codec $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/control $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/demux $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/gui $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/meta_engine $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/misc $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/packetizer $(1)/usr/lib/vlc/plugins
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/plugins/services_discovery $(1)/usr/lib/vlc/plugins
endef

$(eval $(call BuildPackage,vlc))
