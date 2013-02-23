include ../../../common.am

plugin_LTLIBRARIES = librygel-orb.la

AM_CFLAGS += -DG_LOG_DOMAIN='"Orb"'

librygel_orb_la_SOURCES = \
	rygel-orb-player.c \
	rygel-orb-plugin.vala

librygel_orb_la_VALAFLAGS =  	--vapidir=$(srcdir) \
				--pkg rygel-orb-player \
				$(RYGEL_COMMON_PLUGIN_VALAFLAGS)

librygel_orb_la_LIBADD = $(RYGEL_COMMON_LDADD)	\
						-L/Users/mlarson/Sources/FebSkifta/skifta/staging_dir/target-mips_r2_uClibc-0.9.33.2/root-ar71xx/usr/lib/ \
						-lstdc++	\
						-lorbplay	\
						$(ORB_LIBS)

librygel_orb_la_LDFLAGS = $(RYGEL_PLUGIN_LINKER_FLAGS)	\
							-Wl --pic-executable	\
							-Wl -z,now	\
							-Wl -z,defs	\
							 --
