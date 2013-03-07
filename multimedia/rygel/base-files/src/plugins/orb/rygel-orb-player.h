/*
 * orb-audio-player.h
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
 *   OpenedHand's orb-audio-player.h file by Jorn Baayen <jorn@openedhand.com>
 */

#ifndef __ORB_PLAYER_H__
#define __ORB_PLAYER_H__

#include <glib-object.h>
#include <liborbplay.h>
#include <dlfcn.h>
#include <rygel.h>

G_BEGIN_DECLS


#define RYGEL_ORB_TYPE_PLAYER \
                (rygel_orb_player_get_type ())
#define RYGEL_ORB_PLAYER(obj) \
                (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                 RYGEL_ORB_TYPE_PLAYER, \
                 RygelOrbPlayer))
#define RYGEL_ORB_PLAYER_CLASS(klass) \
                (G_TYPE_CHECK_CLASS_CAST ((klass), \
                 RYGEL_ORB_TYPE_PLAYER, \
                 RygelOrbPlayerClass))
#define RYGEL_ORB_IS_PLAYER(obj) \
                (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                 RYGEL_ORB_TYPE_PLAYER))
#define RYGEL_ORB_IS_PLAYER_CLASS(klass) \
                (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                 RYGEL_ORB_TYPE_PLAYER))
#define RYGEL_ORB_PLAYER_GET_CLASS(obj) \
                (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                 RYGEL_ORB_TYPE_PLAYER, \
                 RygelOrbPlayerClass))

typedef enum _orb_playing_state{
        ORB_PLAYING_STATE_PLAYING,
        ORB_PLAYING_STATE_PAUSED_PLAYBACK,
        ORB_PLAYING_STATE_STOPPED,
	 ORB_PLAYING_STATE_TRANSITIONING
} orb_playing_state;

typedef struct _RygelOrbPlayerPrivate RygelOrbPlayerPrivate;

typedef struct {
        GObject parent;

        RygelOrbPlayerPrivate *priv;
} RygelOrbPlayer;

typedef struct {
        GObjectClass parent_class;

        
        /* Future padding */
        void (* _reserved1) (void);
        void (* _reserved2) (void);
        void (* _reserved3) (void);
        void (* _reserved4) (void);
} RygelOrbPlayerClass;


RygelOrbPlayer *
rygel_orb_player_construct (GType object_type);
RygelOrbPlayer *
rygel_orb_player_new (void);
static gboolean rygel_orb_player_seek (RygelMediaPlayer* base, GstClockTime time);
static void rygel_orb_player_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void rygel_orb_player_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
gint64 rygel_orb_player_get_duration (RygelOrbPlayer *player);
const char *rygel_orb_player_get_uri (RygelOrbPlayer *player);
static void rygel_orb_player_set_uri (RygelOrbPlayer* player, const gchar* value);
static gchar* rygel_orb_player_get_playback_state (RygelOrbPlayer *player);
static void rygel_orb_player_set_playback_state (RygelOrbPlayer* base, const gchar* value);
static gdouble rygel_orb_player_get_volume (RygelOrbPlayer *player);
static void rygel_orb_player_set_volume (RygelOrbPlayer *player, gdouble volume);
gint64 rygel_orb_player_get_position (RygelOrbPlayer *player);


GType
rygel_orb_player_get_type           (void) G_GNUC_CONST;

RygelOrbPlayer *
rygel_orb_player_new                (void);

RygelOrbPlayer *
rygel_orb_player_get_default 		  (void);

static gchar** rygel_orb_player_get_protocols (RygelMediaPlayer* base, int* result_length1);
static gchar** rygel_orb_player_get_mime_types (RygelMediaPlayer* base, int* result_length1);


G_END_DECLS

#endif /* __ORB_PLAYER_H__ */
