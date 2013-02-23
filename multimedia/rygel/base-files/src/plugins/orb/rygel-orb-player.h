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

        /* Signals */
        void (* playing)            (RygelOrbPlayer *player);
        void (* paused)             (RygelOrbPlayer *player);
        void (* eos)                (RygelOrbPlayer *player);
        void (* error)              (RygelOrbPlayer *player,
                                     GError         *error);
        
        /* Future padding */
        void (* _reserved1) (void);
        void (* _reserved2) (void);
        void (* _reserved3) (void);
        void (* _reserved4) (void);
} RygelOrbPlayerClass;

GType
rygel_orb_player_get_type           (void) G_GNUC_CONST;

RygelOrbPlayer *
rygel_orb_player_new                (void);

RygelOrbPlayer *
rygel_orb_player_get_default 		  (void);

const char *
rygel_orb_player_get_uri            (RygelOrbPlayer *player);

void
rygel_orb_player_set_protocol_info  (RygelOrbPlayer *player,
                                     const char     *protocol_info);

const char *
rygel_orb_player_get_protocol_info  (RygelOrbPlayer *player);

void
rygel_orb_player_play               (RygelOrbPlayer *player,
                                     const char     *uri);

void
rygel_orb_player_pause              (RygelOrbPlayer *player);

void
rygel_orb_player_resume             (RygelOrbPlayer *player);

void
rygel_orb_player_stop               (RygelOrbPlayer *player);

static gchar* 
rygel_orb_player_get_state (RygelOrbPlayer *player);

void
rygel_orb_player_set_position       (RygelOrbPlayer *player,
                                     int             time_in_seconds);

int
rygel_orb_player_get_position       (RygelOrbPlayer *player);

static gdouble rygel_orb_player_get_volume (RygelOrbPlayer *player);
static void rygel_orb_player_set_volume (RygelOrbPlayer *player, gdouble volume);

void
rygel_orb_player_set_mute           (RygelOrbPlayer *player,
                                     gboolean                mute);
gboolean
rygel_orb_player_get_mute           (RygelOrbPlayer *player);

gboolean
rygel_orb_player_get_can_seek       (RygelOrbPlayer *player);

int
rygel_orb_player_get_duration       (RygelOrbPlayer *player);

G_END_DECLS

#endif /* __ORB_PLAYER_H__ */
