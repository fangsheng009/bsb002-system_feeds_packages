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

using Rygel;
using Gee;
using Orb;

public void module_init (PluginLoader loader) {
    if (loader.plugin_disabled (Orb.Plugin.NAME)) {
        message ("Plugin '%s' disabled by user, ignoring..",
                 Orb.Plugin.NAME);

        return;
    }

    var plugin = new Orb.Plugin ();

    loader.add_plugin (plugin);
}

public class Rygel.Orb.Plugin : Rygel.MediaRendererPlugin {
    public const string NAME = "Orb";

    public Plugin () {
        base (Plugin.NAME, _("Orb Player"));
    }

    public override MediaPlayer? get_player () {
        return Orb.Player.get_default ();
    }
}

