/*
 * orb-audio-player.c
 *   A GObject based wrapper for vlc media player
 *
 * (C) Copyright 2010, Ubicom, Inc.
 *
 * This file is part of the Ubicom32 Rygel.
 *
 * This program is free software: you can redistribute
 * it and/or modify it under the terms of the GNU Lesser General Public
 * License (LGPL) as published by the Free Software Foundation, either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 * the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not,
 * see <http://www.gnu.org/licenses/>.
 *
 * Ubicom32 implementation derived from (with many thanks):
 *   OpenedHand's orb-audio-player.c file by Jorn Baayen <jorn@openedhand.com>
 */


#include "rygel-orb-player.h"
#include <liborbplay.h>
#include <dlfcn.h>
#include <rygel.h>


struct _RygelOrbPlayerPrivate {
	orbplay_ctx_t * pVLCInstance;

	char *uri;
	char *protocol_info;

	int duration;
	gboolean can_seek;
	gchar* _playback_state;
	int _playback_state_int;
};

enum {
        PLAYING,
        PAUSED,
        EOS,
        ERROR,
        LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

static const gchar* RYGEL_ORB_PLAYER_protocols[1] = {"http-get"};
static const gchar* RYGEL_ORB_PLAYER_mime_types[30] = {"audio/mpeg", "application/ogg", "audio/x-vorbis", "audio/x-vorbis+ogg", "audio/x-ms-wma", "audio/x-ms-asf", "audio/x-flac", "audio/x-mod", "audio/x-wav", "audio/x-ac3", "audio/x-m4a", "audio/mp4", "image/jpeg", "image/png", "video/x-theora", "video/x-dirac", "video/x-wmv", "video/x-wma", "video/x-msvideo", "video/x-3ivx", "video/x-3ivx", "video/x-matroska", "video/x-mkv", "video/mpeg", "video/mp4", "video/x-ms-asf", "video/x-xvid", "video/x-ms-wmv", "audio/L16;rate=44100;channels=2", "audio/L16;rate=44100;channels=1"};

#define TICK_TIMEOUT 0.5

/* TODO: Possibly retrieve these through introspection. The problem is that we
 * need them in class_init already. */
#define VLC_VOL_DEFAULT 50.0
#define VLC_VOL_MAX     200.0
#define VLC_VOL_MUTE_DEFAULT FALSE

enum  {
	RYGEL_ORB_PLAYER_DUMMY_PROPERTY,
	RYGEL_ORB_PLAYER_PLAYBACK_STATE,
	RYGEL_ORB_PLAYER_URI,
	RYGEL_ORB_PLAYER_VOLUME,
	RYGEL_ORB_PLAYER_DURATION,
	RYGEL_ORB_PLAYER_POSITION
};

static RygelOrbPlayer *gPlayer;
static RygelOrbPlayer *gPlayer = NULL;
static gpointer rygel_orb_player_parent_class = NULL;
#define RYGEL_ORB_PLAYER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_ORB_TYPE_PLAYER, RygelOrbPlayerPrivate))

static void rygel_orb_player_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void rygel_orb_player_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void rygel_orb_player_finalize (GObject *object);
static gchar** rygel_orb_player_get_protocols (RygelMediaPlayer* base, int* result_length1);
static gchar** rygel_orb_player_get_mime_types (RygelMediaPlayer* base, int* result_length1);
static RygelMediaPlayerIface* rygel_orb_player_rygel_media_player_parent_iface = NULL;
const char *rygel_orb_player_get_protocol_info (RygelOrbPlayer *player);
const char *rygel_orb_player_get_uri (RygelOrbPlayer *player);
void rygel_orb_player_pause (RygelOrbPlayer *player);
static gchar* rygel_orb_player_get_state (RygelOrbPlayer *player);
static gdouble rygel_orb_player_get_volume (RygelOrbPlayer *player);
static void rygel_orb_player_set_volume (RygelOrbPlayer *player, gdouble volume);
int rygel_orb_player_get_position (RygelOrbPlayer *player);
static void rygel_orb_player_set_uri (RygelOrbPlayer* player, const gchar* value);
static void rygel_orb_player_set_playback_state (RygelOrbPlayer* base, const gchar* value);
static gboolean rygel_orb_player_real_seek (RygelMediaPlayer* base, GstClockTime time);
static gboolean rygel_orb_player_seek (RygelMediaPlayer* base, GstClockTime time);
int rygel_orb_player_get_duration (RygelOrbPlayer *player);
static void rygel_orb_player_init (RygelOrbPlayer *player);


static void rygel_orb_player_class_init (RygelOrbPlayerClass * klass) {
	rygel_orb_player_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelOrbPlayerPrivate));
	G_OBJECT_CLASS (klass)->get_property = rygel_orb_player_get_property;
	G_OBJECT_CLASS (klass)->set_property = rygel_orb_player_set_property;
	G_OBJECT_CLASS (klass)->finalize = rygel_orb_player_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_ORB_PLAYER_PLAYBACK_STATE, g_param_spec_string ("playback-state", "playback-state", "playback-state", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_ORB_PLAYER_URI, g_param_spec_string ("uri", "uri", "uri", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_ORB_PLAYER_VOLUME, g_param_spec_double ("volume", "volume", "volume", -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_ORB_PLAYER_DURATION, g_param_spec_int64 ("duration", "duration", "duration", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), RYGEL_ORB_PLAYER_POSITION, g_param_spec_int64 ("position", "position", "position", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void rygel_orb_player_rygel_media_player_interface_init (RygelMediaPlayerIface * iface) {
	rygel_orb_player_rygel_media_player_parent_iface = g_type_interface_peek_parent (iface);
	iface->seek = (gboolean (*)(RygelMediaPlayer*, GstClockTime)) rygel_orb_player_seek;
	iface->get_protocols = (gchar** (*)(RygelMediaPlayer*, int*)) rygel_orb_player_get_protocols;
	iface->get_mime_types = (gchar** (*)(RygelMediaPlayer*, int*)) rygel_orb_player_get_mime_types;
	iface->get_playback_state = rygel_orb_player_get_state;
	iface->set_playback_state = rygel_orb_player_set_playback_state;
	iface->get_uri = rygel_orb_player_get_uri;
	iface->set_uri = rygel_orb_player_set_uri;
	iface->get_volume = rygel_orb_player_get_volume;
	iface->set_volume = rygel_orb_player_set_volume;
	iface->get_duration = rygel_orb_player_get_duration;
	iface->get_position = rygel_orb_player_get_position;
}


static void rygel_orb_player_instance_init (RygelOrbPlayer * self) {
	gchar* _tmp0_;
	self->priv = RYGEL_ORB_PLAYER_GET_PRIVATE (self);
	_tmp0_ = g_strdup ("STOPPED");
	self->priv->_playback_state = _tmp0_;
	rygel_orb_player_init (self);

}

GType rygel_orb_player_get_type (void) {
	static volatile gsize rygel_orb_player_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_orb_player_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelOrbPlayerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_orb_player_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelOrbPlayer), 0, (GInstanceInitFunc) rygel_orb_player_instance_init, NULL };
		static const GInterfaceInfo rygel_media_player_info = { (GInterfaceInitFunc) rygel_orb_player_rygel_media_player_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		GType rygel_orb_player_type_id;
		rygel_orb_player_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelOrbPlayer", &g_define_type_info, 0);
		g_type_add_interface_static (rygel_orb_player_type_id, RYGEL_TYPE_MEDIA_PLAYER, &rygel_media_player_info);
		g_once_init_leave (&rygel_orb_player_type_id__volatile, rygel_orb_player_type_id);
	}
	return rygel_orb_player_type_id__volatile;
}


static gchar** _vala_array_dup1 (gchar** self, int length) {
	gchar** result;
	int i;
	result = g_new0 (gchar*, length + 1);
	for (i = 0; i < length; i++) {
		gchar* _tmp0_;
		_tmp0_ = g_strdup (self[i]);
		result[i] = _tmp0_;
	}
	return result;
}


static gchar** rygel_orb_player_get_protocols (RygelMediaPlayer* base, int* result_length1) {
	RygelOrbPlayer * self;
	gchar** result = NULL;
	gchar** _tmp0_;
	gint _tmp0__length1;
	gchar** _tmp1_;
	gint _tmp1__length1;
	self = (RygelOrbPlayer*) base;
	_tmp0_ = (RYGEL_ORB_PLAYER_protocols != NULL) ? _vala_array_dup1 (RYGEL_ORB_PLAYER_protocols, G_N_ELEMENTS (RYGEL_ORB_PLAYER_protocols)) : ((gpointer) RYGEL_ORB_PLAYER_protocols);
	_tmp0__length1 = G_N_ELEMENTS (RYGEL_ORB_PLAYER_protocols);
	_tmp1_ = _tmp0_;
	_tmp1__length1 = _tmp0__length1;
	if (result_length1) {
		*result_length1 = _tmp1__length1;
	}
	result = _tmp1_;
	return result;
}


static gchar** _vala_array_dup2 (gchar** self, int length) {
	gchar** result;
	int i;
	result = g_new0 (gchar*, length + 1);
	for (i = 0; i < length; i++) {
		gchar* _tmp0_;
		_tmp0_ = g_strdup (self[i]);
		result[i] = _tmp0_;
	}
	return result;
}


static gchar** rygel_orb_player_get_mime_types (RygelMediaPlayer* base, int* result_length1) {
	RygelOrbPlayer * self;
	gchar** result = NULL;
	gchar** _tmp0_;
	gint _tmp0__length1;
	gchar** _tmp1_;
	gint _tmp1__length1;
	self = (RygelOrbPlayer*) base;
	_tmp0_ = (RYGEL_ORB_PLAYER_mime_types != NULL) ? _vala_array_dup2 (RYGEL_ORB_PLAYER_mime_types, G_N_ELEMENTS (RYGEL_ORB_PLAYER_mime_types)) : ((gpointer) RYGEL_ORB_PLAYER_mime_types);
	_tmp0__length1 = G_N_ELEMENTS (RYGEL_ORB_PLAYER_mime_types);
	_tmp1_ = _tmp0_;
	_tmp1__length1 = _tmp0__length1;
	if (result_length1) {
		*result_length1 = _tmp1__length1;
	}
	result = _tmp1_;
	return result;
}

static gboolean rygel_orb_player_seek (RygelMediaPlayer* base, GstClockTime time) {
	return FALSE;

}

/**
 * Player playing media.
 **/
static void
orb_media_player_playing_cb( orbplay_ctx_t *orbctx, const orbplay_event_t *event, void *app_data )
{
	RygelOrbPlayer *player = app_data;
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));
// 	rygel_media_player_set_playback_state ((RygelMediaPlayer*) player, "PLAYING");
	g_object_notify ((GObject *) player, "playback-state");
}

/**
 * Player paused playing media.
 **/
static void
orb_media_player_paused_cb( orbplay_ctx_t *orbctx, const orbplay_event_t *event, void *app_data )
{
	RygelOrbPlayer *player = app_data;
	printf("Orb orb_media_player_paused_cb\n");
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));
// 		rygel_media_player_set_playback_state ((RygelMediaPlayer*) player, "PAUSED");
	g_object_notify ((GObject *) player, "playback-state");
}

/**
 * End of stream reached.
 **/
typedef void (*orbplay_cb_t) (orbplay_ctx_t *orbctx, orbplay_event_t event,
			      void *);
static void
orb_eos_cb( orbplay_ctx_t *orbctx, const orbplay_event_t *event, void *app_data )
{
	RygelOrbPlayer *player = app_data;
	printf("Orb orb_eos_cb\n");
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));
	g_object_notify ((GObject *) player, "playback-state");
// 	rygel_media_player_set_playback_state ((RygelMediaPlayer*) player, "STOPPED");
}

/**
 * Error occured.
 **/
static void
orb_error_cb( orbplay_ctx_t *orbctx, const orbplay_event_t *event, void *app_data )
{
	RygelOrbPlayer *player = app_data;
	printf("Orb orb_error_cb\n");
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));

	g_object_notify ((GObject *) player, "playback-state");
// 	rygel_media_player_set_playback_state ((RygelMediaPlayer*) player, "STOPPED");
}

// static void
// rygel_orb_player_get_player ()
// {
// 	printf("Orb rygel_orb_player_get_player\n");
//
// }

static void
rygel_orb_player_init (RygelOrbPlayer *player)
{
        /**
         * Create pointer to private data.
         **/
        player->priv =
                G_TYPE_INSTANCE_GET_PRIVATE (player,
                                             RYGEL_ORB_TYPE_PLAYER,
                                             RygelOrbPlayerPrivate);


	player->priv->_playback_state = strdup("STOPPED");
	player->priv->_playback_state_int = ORBPLAY_STATE_STOPPED;
	player->priv->uri = NULL;
	orbplay_ctx_t * pVLCInstance = NULL;

	// init orb modules, should be done only once
	pVLCInstance = liborbplay_new ();

	liborbplay_events_attach(pVLCInstance,
	                    ORBPLAY_EVENT_EOS_REACHED,
	                    orb_eos_cb,
	                    player);
	liborbplay_events_attach(pVLCInstance,
	                    ORBPLAY_EVENT_ERROR,
	                    orb_error_cb,
	                    player);
	liborbplay_events_attach(pVLCInstance,
	                    ORBPLAY_EVENT_PAUSED,
	                    orb_media_player_paused_cb,
	                    player);
	liborbplay_events_attach(pVLCInstance,
	                    ORBPLAY_EVENT_PLAYING,
	                    orb_media_player_playing_cb,
	                    player);

	player->priv->pVLCInstance = pVLCInstance;
}

static void
rygel_orb_player_set_property (GObject      *object,
                               guint         property_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
        RygelOrbPlayer *player;

        player = RYGEL_ORB_PLAYER (object);
		printf("Orb rygel_orb_player_set_property: %x  - %s\n", property_id,g_value_get_string (value));

        switch (property_id) {
			case RYGEL_ORB_PLAYER_PLAYBACK_STATE:
			rygel_media_player_set_playback_state ((RygelMediaPlayer*) player, g_value_get_string (value));
			break;
			case RYGEL_ORB_PLAYER_URI:
			rygel_media_player_set_uri ((RygelMediaPlayer*) player, g_value_get_string (value));
			break;
			case RYGEL_ORB_PLAYER_VOLUME:
			rygel_media_player_set_volume ((RygelMediaPlayer*) player, g_value_get_double (value));
			break;
			default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
        }
}

static void
rygel_orb_player_get_property (GObject    *object,
                               guint       property_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
	RygelOrbPlayer *player;

	printf("Orb rygel_orb_player_get_property: %x\n", property_id);
	player = RYGEL_ORB_PLAYER (object);

	switch (property_id) {
		case RYGEL_ORB_PLAYER_PLAYBACK_STATE:
		g_value_take_string (value, rygel_media_player_get_playback_state ((RygelMediaPlayer*) player));
		break;
		case RYGEL_ORB_PLAYER_URI:
		g_value_take_string (value, rygel_media_player_get_uri ((RygelMediaPlayer*) player));
		break;
		case RYGEL_ORB_PLAYER_VOLUME:
		g_value_set_double (value, rygel_media_player_get_volume ((RygelMediaPlayer*) player));
		break;
		case RYGEL_ORB_PLAYER_DURATION:
		g_value_set_int64 (value, rygel_media_player_get_duration ((RygelMediaPlayer*) player));
		break;
		case RYGEL_ORB_PLAYER_POSITION:
		g_value_set_int64 (value, rygel_media_player_get_position ((RygelMediaPlayer*) player));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}

static void
rygel_orb_player_dispose (GObject *object)
{
	RygelOrbPlayer *player;
	GObjectClass *object_class;

	player = RYGEL_ORB_PLAYER (object);


	if (player->priv->pVLCInstance) {
		liborbplay_free (player->priv->pVLCInstance);
	        player->priv->pVLCInstance = NULL;
	}


	object_class = G_OBJECT_CLASS (rygel_orb_player_parent_class);
	object_class->dispose (object);
}

static void
rygel_orb_player_finalize (GObject *object)
{
	RygelOrbPlayer *player;
	GObjectClass *object_class;

	player = RYGEL_ORB_PLAYER (object);

	g_free (player->priv->uri);
	g_free (player->priv->protocol_info);

	object_class = G_OBJECT_CLASS (rygel_orb_player_parent_class);
	object_class->finalize (object);
}

// static void
// rygel_orb_player_class_init (RygelOrbPlayerClass *klass)
// {
// 	GObjectClass *object_class;
//
// 	object_class = G_OBJECT_CLASS (klass);
//
// 	object_class->set_property = rygel_orb_player_set_property;
// 	object_class->get_property = rygel_orb_player_get_property;
// 	object_class->dispose      = rygel_orb_player_dispose;
// 	object_class->finalize     = rygel_orb_player_finalize;
//
// 	g_type_class_add_private (klass, sizeof (RygelOrbPlayerPrivate));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_URI,
// 	         g_param_spec_string
// 	                 ("uri",
// 	                  "URI",
// 	                  "The loaded URI.",
// 	                  NULL,
// 	                  G_PARAM_READWRITE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_PROTOCOL_INFO,
// 	         g_param_spec_string
// 	                 ("protocol-info",
// 	                  "PROTOCOL_INFO",
// 	                  "The DLNA protocolInfo.",
// 	                  NULL,
// 	                  G_PARAM_READWRITE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_STATE,
// 	         g_param_spec_boolean
// 	                 ("state",
// 	                  "Playing State",
// 	                  "Returns playing state.",
// 	                  FALSE,
// 	                  G_PARAM_READWRITE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_POSITION,
// 	         g_param_spec_int
// 	                 ("position",
// 	                  "Position",
// 	                  "The position in the current stream in seconds.",
// 	                  0, G_MAXINT, 0,
// 	                  G_PARAM_READWRITE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_VOLUME,
// 	         g_param_spec_uint
// 	                 ("volume",
// 	                  "Volume",
// 	                  "The audio volume.",
// 	                  0, VLC_VOL_MAX, VLC_VOL_DEFAULT,
// 	                  G_PARAM_READWRITE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_MUTE,
// 	         g_param_spec_uint
// 	                 ("mute",
// 	                  "Mute",
// 	                  "The audio mute.",
// 	                  0, 1, VLC_VOL_MUTE_DEFAULT,
// 	                  G_PARAM_READWRITE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_CAN_SEEK,
// 	         g_param_spec_boolean
// 	                 ("can-seek",
// 	                  "Can seek",
// 	                  "TRUE if the current stream is seekable.",
// 	                  FALSE,
// 	                  G_PARAM_READABLE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	g_object_class_install_property
// 	        (object_class,
// 	         PROP_DURATION,
// 	         g_param_spec_int
// 	                 ("duration",
// 	                  "Duration",
// 	                  "The duration of the current stream in seconds.",
// 	                  0, G_MAXINT, 0,
// 	                  G_PARAM_READABLE |
// 	                  G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK |
// 	                  G_PARAM_STATIC_BLURB));
//
// 	signals[PLAYING] =
// 	        g_signal_new ("playing",
// 	                      RYGEL_ORB_TYPE_PLAYER,
// 	                      G_SIGNAL_RUN_LAST,
// 	                      G_STRUCT_OFFSET (RygelOrbPlayerClass,
// 	                                       playing),
// 	                      NULL, NULL,
// 	                      g_cclosure_marshal_VOID__VOID,
// 	                      G_TYPE_NONE, 0);
//
// 	signals[PAUSED] =
// 	        g_signal_new ("paused",
// 	                      RYGEL_ORB_TYPE_PLAYER,
// 	                      G_SIGNAL_RUN_LAST,
// 	                      G_STRUCT_OFFSET (RygelOrbPlayerClass,
// 	                                       paused),
// 	                      NULL, NULL,
// 	                      g_cclosure_marshal_VOID__VOID,
// 	                      G_TYPE_NONE, 0);
//
// 	signals[EOS] =
// 	        g_signal_new ("eos",
// 	                      RYGEL_ORB_TYPE_PLAYER,
// 	                      G_SIGNAL_RUN_LAST,
// 	                      G_STRUCT_OFFSET (RygelOrbPlayerClass,
// 	                                       eos),
// 	                      NULL, NULL,
// 	                      g_cclosure_marshal_VOID__VOID,
// 	                      G_TYPE_NONE, 0);
//
// 	signals[ERROR] =
// 	        g_signal_new ("error",
// 	                      RYGEL_ORB_TYPE_PLAYER,
// 	                      G_SIGNAL_RUN_LAST,
// 	                      G_STRUCT_OFFSET (RygelOrbPlayerClass,
// 	                                       error),
// 	                      NULL, NULL,
// 	                      g_cclosure_marshal_VOID__POINTER,
// 	                      G_TYPE_NONE, 1, G_TYPE_POINTER);
// }

/**
 * rygel_orb_player_construct
 *
 * Return value: A new #RygelOrbPlayer.
 **/
RygelOrbPlayer *
rygel_orb_player_construct (GType object_type)
{
	return g_object_new (RYGEL_ORB_TYPE_PLAYER, NULL);
}

/**
 * rygel_orb_player_new
 *
 * Return value: A new #RygelOrbPlayer.
 **/
RygelOrbPlayer *
rygel_orb_player_new (void)
{
	return rygel_orb_player_construct (RYGEL_ORB_TYPE_PLAYER);
}

RygelOrbPlayer *
rygel_orb_player_get_default (void)
{
	if(!gPlayer)
		gPlayer = rygel_orb_player_new();

	return gPlayer;
}

/**
 * rygel_orb_player_set_protocol_info
 * @player: A #RygelOrbPlayer
 * @protocol_info: A PROTOCOL_INFO
 *
 * Loads @protocol_info.
 **/
void
rygel_orb_player_set_protocol_info (RygelOrbPlayer *player,
                                    const char     *protocol_info)
{
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));


	if (protocol_info && player->priv->protocol_info && !strcmp(protocol_info, player->priv->protocol_info)) {
		return;
	}

	g_free (player->priv->protocol_info);

	if (protocol_info) {
	        player->priv->protocol_info = g_strdup (protocol_info);
	} else {
	        player->priv->protocol_info = NULL;
	}
}

/**
 * rygel_orb_player_get_protocol_info
 * @player: A #RygelOrbPlayer
 *
 * Return value: The DLNA protocolInfo, or NULL if none set.
 **/
const char *
rygel_orb_player_get_protocol_info (RygelOrbPlayer *player)
{
	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), NULL);

	return player->priv->protocol_info;
}

/**
 * rygel_orb_player_get_uri
 * @player: A #RygelOrbPlayer
 *
 * Return value: The loaded URI, or NULL if none set.
 **/
const char *
rygel_orb_player_get_uri (RygelOrbPlayer *player)
{
	gchar *uri;
	printf("Orb rygel_orb_player_get_uri\n");
	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), NULL);
	if(player->priv->uri)
		uri = strdup(player->priv->uri);
	else
		uri = NULL;

	return uri;
}



static void rygel_orb_player_set_uri (RygelOrbPlayer* player, const gchar* value) {
	printf("Orb rygel_orb_player_set_uri %s\n",value);

	if(player->priv->uri)
		free(player->priv->uri);
    player->priv->uri = strdup (value);
	rygel_orb_player_play(player, value);
	g_object_notify ((GObject *) player, "uri");
}

static void rygel_orb_player_set_playback_state (RygelOrbPlayer* player, const gchar* value) {

	printf("Orb rygel_orb_player_set_playback_state - %s\n",value);

	if(!strncmp(value,"STOPPED",7))
	{
		player->priv->_playback_state_int = ORBPLAY_STATE_STOPPED;
		if (liborbplay_get_state(player->priv->pVLCInstance) != ORBPLAY_STATE_STOPPED)
		{
			rygel_orb_player_stop(player);
		}
	}
	else if(!strncmp(value,"PAUSED_PLAYBACK",15))
	{
		player->priv->_playback_state_int = ORBPLAY_STATE_PAUSED;
		rygel_orb_player_pause(player);
	}
	else if(!strncmp(value,"PLAYING",7))
	{
		player->priv->_playback_state_int = ORBPLAY_STATE_PLAYING;
		if (liborbplay_get_state(player->priv->pVLCInstance) != ORBPLAY_STATE_PAUSED) {
			rygel_orb_player_play(player, player->priv->uri);
		}
		else
		{
			liborbplay_playback_resume(player->priv->pVLCInstance);
		}
	}
	if(player->priv->_playback_state)
		free(player->priv->_playback_state);
	player->priv->_playback_state = strdup(value);
	g_object_notify ((GObject *) player, "playback-state");
}

/**
 * rygel_orb_player_pause
 * @player: A #RygelOrbPlayer
 *
 * Pauses playing media.
 **/
void
rygel_orb_player_pause (RygelOrbPlayer *player)
{
	printf("Orb rygel_orb_player_pause\n");
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));

	if (liborbplay_get_state(player->priv->pVLCInstance) != ORBPLAY_STATE_PLAYING) {
		return;
	}

	liborbplay_playback_pause(player->priv->pVLCInstance);
}

/**
 * rygel_orb_player_resume
 * @player: A #RygelOrbPlayer
 *
 * Resumes paused media.
 **/
void
rygel_orb_player_resume (RygelOrbPlayer *player)
{
	printf("Orb rygel_orb_player_resume\n");
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));

	if (!player->priv->pVLCInstance)
	        return;

	if (liborbplay_get_state(player->priv->pVLCInstance) != ORBPLAY_STATE_PAUSED) {
		return;
	}

	liborbplay_playback_pause(player->priv->pVLCInstance);
}

/**
 * rygel_orb_player_stop
 * @player: A #RygelOrbPlayer
 *
 * Stops playing media.
 **/
void
rygel_orb_player_stop (RygelOrbPlayer *player)
{
	printf("Orb rygel_orb_player_stop\n");
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));

	if (!player->priv->pVLCInstance)
	        return;

	liborbplay_playback_stop(player->priv->pVLCInstance);
}

/**
 * rygel_orb_player_play
 * @player: A #RygelOrbPlayer
 * @uri: A URI
 *
 * Plays the media at @uri.
 **/
void
rygel_orb_player_play (RygelOrbPlayer *player,
                       const char *uri)
{
	printf("Orb rygel_orb_player_play\n");
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));

	if (!player->priv->pVLCInstance)
	        return;

	if (!uri) {
		return;
	}


	/**
	 * Play media
	 **/
	liborbplay_playback_start(player->priv->pVLCInstance, uri);

	/**
	 * Reset properties.
	 **/
	player->priv->can_seek = 0;
	player->priv->duration = 0;
}

/**
 * rygel_orb_player_get_state
 * @player: A #RygelOrbPlayer
 *
 * Return value: Playing state of @player.
 **/
static gchar*
rygel_orb_player_get_state (RygelOrbPlayer *player)
{
	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), FALSE);

	if (!player->priv->pVLCInstance)
	        return FALSE;


	orbplay_state_t state = liborbplay_get_state(player->priv->pVLCInstance);
	printf("Orb Get_state:  %x\n", state);
	gchar *retString;
// 	ORBPLAY_STATE_ERROR,
// 	ORBPLAY_STATE_STARTING,
// 	ORBPLAY_STATE_BUFFERING,
// 	ORBPLAY_STATE_PLAYING,
// 	ORBPLAY_STATE_STOPPED,
// 	ORBPLAY_STATE_PAUSED,

	switch (state) {
	case ORBPLAY_STATE_BUFFERING:
	case ORBPLAY_STATE_STARTING:
// 		retString = strdup ("TRANSITIONING");
// 		break;
	case ORBPLAY_STATE_PLAYING:
		if(player->priv->_playback_state_int == ORBPLAY_STATE_PAUSED)
			retString = strdup ("PAUSED_PLAYBACK");
		else
			retString = strdup ("PLAYING");
		break;
	case ORBPLAY_STATE_STOPPED:
	case ORBPLAY_STATE_ERROR:
		retString = strdup ("STOPPED");
		break;
	case ORBPLAY_STATE_PAUSED:
		if(player->priv->_playback_state_int == ORBPLAY_STATE_PLAYING)
			retString = strdup ("PLAYING");
		else
			retString = strdup ("PAUSED_PLAYBACK");
		break;
	}
	printf("Orb Get_state:  %s\n", retString);
	return retString;
}

/**
 * rygel_orb_player_set_position
 * @player: A #RygelOrbPlayer
 * @time_in_seconds: The position in the current stream in seconds.
 *
 * Sets the position in the current stream to @time_in_seconds.
 **/
void
rygel_orb_player_set_position (RygelOrbPlayer *player,
                               int time_in_seconds)
{
	// printf("Orb rygel_orb_player_set_position:  %d\n", time_in_seconds);
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));

	if (!player->priv->pVLCInstance)
		return;

	if (time_in_seconds < 0) {
		return;
	}

	int time_in_mseconds = time_in_seconds * 1000;
	liborbplay_set_position(player->priv->pVLCInstance, time_in_mseconds);
	g_debug("%p: New time is %lld", player, time_in_mseconds);
}

/**
 * rygel_orb_player_get_position
 * @player: A #RygelOrbPlayer
 *
 * Return value: The position in the current file in seconds.
 **/
int
rygel_orb_player_get_position (RygelOrbPlayer *player)
{
	// printf("Orb rygel_orb_player_get_position\n");
	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), -1);

	if (!player->priv->pVLCInstance)
	        return -1;

	int time_in_mseconds = liborbplay_get_position(player->priv->pVLCInstance);

	// printf("Orb rygel_orb_player_get_position %d\n", time_in_mseconds);
	return time_in_mseconds / 1000;
}

/**
 * rygel_orb_player_set_volume
 * @player: A #RygelOrbPlayer
 * @volume: The audio volume to set, in the range 0.0 - 4.0.
 *
 * Sets the current audio volume to @volume.
 **/
static void
rygel_orb_player_set_volume (RygelOrbPlayer *player,
                             gdouble          volume)
{
	gdouble orbVolumeDbl;
	int		orbVol;

	printf("Orb rygel_orb_player_set_volume %lld\n",volume);
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));
	g_return_if_fail (volume >= -G_MAXDOUBLE && volume <= G_MAXDOUBLE);

	if (!player->priv->pVLCInstance)
	        return;

	orbVolumeDbl = volume * 100;
	orbVol = orbVolumeDbl;


	liborbplay_set_volume(player->priv->pVLCInstance, orbVol);
	g_object_notify ((GObject *) player, "volume");
}

/**
 * rygel_orb_player_get_volume
 * @player: A #RygelOrbPlayer
 *
 * Return value: The current audio volume, in the range 0.0 - 4.0.
 **/
static gdouble
rygel_orb_player_get_volume (RygelOrbPlayer *player)
{
	unsigned int volume;
	gdouble dblVol;
	printf("Orb rygel_orb_player_get_volume\n");

	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), 0);

	if (!player->priv->pVLCInstance)
	        return 0.0;

	volume = liborbplay_get_volume(player->priv->pVLCInstance	);
	dblVol = volume * 100;
	return dblVol;
}

/**
 * rygel_orb_player_set_mute
 * @player: A #RygelOrbPlayer
 * @mute: TRUE if volume should be muted, FALSE otherwise
 *
 * Sets the current audio mute to @mute.
 **/
void
rygel_orb_player_set_mute (RygelOrbPlayer *player,
                           gboolean                mute)
{
	g_return_if_fail (RYGEL_ORB_IS_PLAYER (player));

	if (!player->priv->pVLCInstance)
	        return;

	liborbplay_set_mute(player->priv->pVLCInstance, mute);
}

/**
 * rygel_orb_player_get_mute
 * @player: A #RygelOrbPlayer
 *
 * Return value: TRUE if the current volume is muted.
 **/
gboolean
rygel_orb_player_get_mute (RygelOrbPlayer *player)
{
	gboolean mute;

	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), 0);

	if (!player->priv->pVLCInstance)
	        return FALSE;

	mute = liborbplay_get_mute(player->priv->pVLCInstance);

	return mute;
}

/**
 * rygel_orb_player_get_can_seek
 * @player: A #RygelOrbPlayer
 *
 * Return value: TRUE if the current stream is seekable.
 **/
gboolean
rygel_orb_player_get_can_seek (RygelOrbPlayer *player)
{
	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), FALSE);

// 	int is_seekable = libvlc_media_player_is_seekable(player->priv->pVLCInstance);
	return FALSE;
}

/**
 * rygel_orb_player_get_duration
 * @player: A #RygelOrbPlayer
 *
 * Return value: The duration of the current stream in seconds.
 **/
int
rygel_orb_player_get_duration (RygelOrbPlayer *player)
{
	g_return_val_if_fail (RYGEL_ORB_IS_PLAYER (player), -1);

// 	printf("Orb rygel_orb_player_get_duration - %d\n",player->priv->duration);
	return player->priv->duration;
}
