# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=vlc
PKG_VERSION:=0.9.9
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://download.videolan.org/pub/videolan/vlc/0.9.9/
PKG_MD5SUM:=b7c2a75194ad5c73979c3d880aebbe38

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/vlc
  SECTION:=multimedia
  CATEGORY:=Multimedia
  TITLE:=Audio player
  URL:=http://www.videolan.org/vlc/
  DEPENDS+= +glib2 +libpthread +libmpg123 +libfaad2 +librt +alsa-lib +libid3tag \
	+libstdcpp +libflac +libmpeg2 +libogg +ffmpeg-old +libvorbisidec
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
	--disable-python-bindings \
	--disable-java-bindings \
	--disable-dependency-tracking \
	--disable-dependency-tracking \
	--disable-macosx \
	--without-macosx-sdk \
	--disable-macosx-audio \
	--disable-macosx-defaults \
	--disable-libtool-lock \
	--disable-nls \
	--disable-rpath \
	--disable-hal \
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
	--disable-release \
	--disable-sout \
	--enable-rawaud \
	--disable-switcher \
	--disable-shout \
	--disable-lua \
	--disable-httpd \
	--disable-libproxy \
	--disable-vlm \
	--disable-growl \
	--disable-notify \
	--disable-audioscrobbler \
	--disable-taglib \
	--disable-live555 \
	--disable-dc1394 \
	--disable-dv \
	--disable-dvdread \
	--disable-dvdnav \
	--disable-dshow \
	--disable-bda \
	--disable-opencv \
	--disable-smb \
	--disable-dvbpsi \
	--disable-v4l \
	--disable-v4l2 \
	--disable-libv4l2 \
	--disable-pvr \
	--disable-gnomevfs \
	--disable-libcdio \
	--disable-cddax \
	--disable-libcddb \
	--disable-vcdx \
	--disable-cdda \
	--disable-vcd \
	--disable-dvb \
	--disable-screen \
	--enable-ogg \
	--disable-mkv \
	--disable-mod \
	--disable-mpc \
	--disable-gme \
	--disable-mad \
	--enable-mpg123 \
	--enable-id3tag \
	--enable-avcodec \
	--disable-avformat \
	--disable-swscale \
	--disable-imgresample \
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
	--disable-tarkin \
	--disable-theora \
	--disable-dirac \
	--disable-schroedinger \
	--disable-png \
	--disable-x264 \
	--disable-fluidsynth \
	--disable-zvbi \
	--disable-telx \
	--disable-libass \
	--disable-asademux \
	--disable-cmml \
	--disable-kate \
	--disable-x11 \
	--disable-xvideo \
	--disable-glx \
	--disable-xvmc \
	--disable-xinerama \
	--disable-opengl \
	--disable-sdl \
	--disable-sdl-image \
	--disable-freetype \
	--disable-fribidi \
	--disable-fontconfig \
	--disable-libxml2 \
	--disable-svg \
	--disable-snapshot \
	--disable-qte \
	--disable-hd1000v \
	--disable-directx \
	--disable-fb \
	--disable-mga \
	--disable-svgalib \
	--disable-directfb \
	--disable-ggi \
	--disable-aa \
	--disable-caca \
	--disable-wingdi \
	--disable-oss \
	--disable-esd \
	--disable-pulse \
	--disable-portaudio \
	--disable-arts \
	--enable-alsa \
	--disable-waveout \
	--disable-macosx-audio \
	--disable-hd1000a \
	--disable-jack \
	--disable-cyberlink \
	--disable-upnp \
	--disable-skins2 \
	--disable-pda \
	--disable-qt4 \
	--disable-wince \
	--disable-opie \
	--disable-macosx \
	--disable-qnx \
	--disable-ncurses \
	--disable-xosd \
	--disable-fbosd \
	--disable-visual \
	--disable-galaktos \
	--disable-goom \
	--disable-atmo \
	--disable-bonjour \
	--disable-lirc \
	--disable-libgcrypt \
	--disable-gnutls \
	--disable-remoteosd \
	--disable-update-check \
	--disable-loader \
	--enable-vlc \
	--disable-activex \
	--disable-mozilla \
	--disable-testsuite \
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

	$(INSTALL_DIR) $(1)/usr/lib
	( cd $(PKG_INSTALL_DIR); $(CP) \
				./usr/lib/libvlccore.so* \
				./usr/lib/libvlc.so* \
				$(1)/usr/lib/ \
	)

	$(INSTALL_DIR) $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/access $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/access_filter $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/audio_filter $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/audio_mixer $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/audio_output $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/codec $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/control $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/demux $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/gui $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/meta_engine $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/misc $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/packetizer $(1)/usr/lib/vlc
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/vlc/services_discovery $(1)/usr/lib/vlc
endef

$(eval $(call BuildPackage,vlc))
