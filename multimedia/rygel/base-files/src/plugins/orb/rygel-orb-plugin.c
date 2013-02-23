/* rygel-orb-plugin.c generated by valac 0.16.0, the Vala compiler
 * generated from rygel-orb-plugin.vala, do not modify */

/*
 * Copyright (C) 2008 Zeeshan Ali (Khattak) <zeeshanak@gnome.org>.
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Author: Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
 *                               <zeeshan.ali@nokia.com>
 *
 * This file is part of Rygel.
 *
 * Rygel is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Rygel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <glib.h>
#include <glib-object.h>
#include <rygel.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n-lib.h>
#include <rygel-orb-player.h>


#define RYGEL_ORB_PLAYER_TYPE_PLUGIN (rygel_orb_player_plugin_get_type ())
#define RYGEL_ORB_PLAYER_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_ORB_PLAYER_TYPE_PLUGIN, RygelOrbPlayerPlugin))
#define RYGEL_ORB_PLAYER_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_ORB_PLAYER_TYPE_PLUGIN, RygelOrbPlayerPluginClass))
#define RYGEL_ORB_PLAYER_IS_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_ORB_PLAYER_TYPE_PLUGIN))
#define RYGEL_ORB_PLAYER_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_ORB_PLAYER_TYPE_PLUGIN))
#define RYGEL_ORB_PLAYER_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_ORB_PLAYER_TYPE_PLUGIN, RygelOrbPlayerPluginClass))

typedef struct _RygelOrbPlayerPlugin RygelOrbPlayerPlugin;
typedef struct _RygelOrbPlayerPluginClass RygelOrbPlayerPluginClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
typedef struct _RygelOrbPlayerPluginPrivate RygelOrbPlayerPluginPrivate;

struct _RygelOrbPlayerPlugin {
	RygelMediaRendererPlugin parent_instance;
	RygelOrbPlayerPluginPrivate * priv;
};

struct _RygelOrbPlayerPluginClass {
	RygelMediaRendererPluginClass parent_class;
};


static gpointer rygel_orb_player_plugin_parent_class = NULL;

void module_init (RygelPluginLoader* loader);
#define RYGEL_ORB_PLAYER_PLUGIN_NAME "RygelOrbPlayer"
RygelOrbPlayerPlugin* rygel_orb_player_plugin_new (void);
RygelOrbPlayerPlugin* rygel_orb_player_plugin_construct (GType object_type);
GType rygel_orb_player_plugin_get_type (void) G_GNUC_CONST;
enum  {
	RYGEL_ORB_PLAYER_PLUGIN_DUMMY_PROPERTY
};
static RygelMediaPlayer* rygel_orb_player_plugin_real_get_player (RygelMediaRendererPlugin* base);


void module_init (RygelPluginLoader* loader) {
	RygelPluginLoader* _tmp0_;
	gboolean _tmp1_ = FALSE;
	RygelOrbPlayerPlugin* _tmp2_;
	RygelOrbPlayerPlugin* plugin;
	RygelPluginLoader* _tmp3_;
	RygelOrbPlayerPlugin* _tmp4_;
	g_return_if_fail (loader != NULL);
	_tmp0_ = loader;
	_tmp1_ = rygel_plugin_loader_plugin_disabled (_tmp0_, RYGEL_ORB_PLAYER_PLUGIN_NAME);
	if (_tmp1_) {
		g_message ("rygel-orb-plugin.vala:31: Plugin '%s' disabled by user, ignoring..", RYGEL_ORB_PLAYER_PLUGIN_NAME);
		return;
	}
	_tmp2_ = rygel_orb_player_plugin_new ();
	plugin = _tmp2_;
	_tmp3_ = loader;
	_tmp4_ = plugin;
	rygel_plugin_loader_add_plugin (_tmp3_, (RygelPlugin*) _tmp4_);
	_g_object_unref0 (plugin);
}


RygelOrbPlayerPlugin* rygel_orb_player_plugin_construct (GType object_type) {
	RygelOrbPlayerPlugin * self = NULL;
	const gchar* _tmp0_ = NULL;
	_tmp0_ = _ ("Orb Player");
	self = (RygelOrbPlayerPlugin*) rygel_media_renderer_plugin_construct (object_type, RYGEL_ORB_PLAYER_PLUGIN_NAME, _tmp0_, NULL);
	return self;
}


RygelOrbPlayerPlugin* rygel_orb_player_plugin_new (void) {
	return rygel_orb_player_plugin_construct (RYGEL_ORB_PLAYER_TYPE_PLUGIN);
}


static RygelMediaPlayer* rygel_orb_player_plugin_real_get_player (RygelMediaRendererPlugin* base) {
	RygelOrbPlayerPlugin * self;
	RygelMediaPlayer* result = NULL;
	RygelOrbPlayer* _tmp0_ = NULL;
	self = (RygelOrbPlayerPlugin*) base;
	_tmp0_ = rygel_orb_player_get_default ();
	result = (RygelMediaPlayer*) _tmp0_;
	return result;
}


static void rygel_orb_player_plugin_class_init (RygelOrbPlayerPluginClass * klass) {
	rygel_orb_player_plugin_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_RENDERER_PLUGIN_CLASS (klass)->get_player = rygel_orb_player_plugin_real_get_player;
}


static void rygel_orb_player_plugin_instance_init (RygelOrbPlayerPlugin * self) {
}


GType rygel_orb_player_plugin_get_type (void) {
	static volatile gsize rygel_orb_player_plugin_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_orb_player_plugin_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelOrbPlayerPluginClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_orb_player_plugin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelOrbPlayerPlugin), 0, (GInstanceInitFunc) rygel_orb_player_plugin_instance_init, NULL };
		GType rygel_orb_player_plugin_type_id;
		rygel_orb_player_plugin_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_RENDERER_PLUGIN, "RygelOrbPlayerPlugin", &g_define_type_info, 0);
		g_once_init_leave (&rygel_orb_player_plugin_type_id__volatile, rygel_orb_player_plugin_type_id);
	}
	return rygel_orb_player_plugin_type_id__volatile;
}



