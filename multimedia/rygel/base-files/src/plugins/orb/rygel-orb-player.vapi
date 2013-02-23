/*
 * orb-audio-player.vapi
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
 *   OpenedHand's orb-audio-player.vapi file by Jorn Baayen <jorn@openedhand.com>
 */
using Gst;
using Rygel;

	[CCode (cname = "orb_playing_state", has_type_id = false)]
	public enum PlayingState {
		PLAYING,
		PAUSED_PLAYBACK,
		STOPPED,
		TRANSITIONING
	}

	[CCode (cheader_filename = "rygel-orb-player.h")]
	public class Rygel.Orb.Player : GLib.Object, Rygel.MediaPlayer {
    private const string[] protocols;
    private const string[] mime_types;

		public bool seek (Gst.ClockTime time);
		public int64 duration { get; }
		public string duration_as_str { owned get; }
		public string playback_state { owned get; set; }
		public int64 position { get; }
		public string position_as_str { owned get; }
		public string? uri { owned get; set; }
		public double volume { get; set; }

		public bool get_can_seek ();
		public int get_duration ();
		public bool get_mute ();
		public PlayingState get_state ();
		public int get_position ();
		public unowned string get_uri ();
		public unowned string get_protocol_info ();
		public uint get_volume ();
		public Player ();
		public static Player get_default ();
		public void set_mute (bool mute);
		public void play (string uri);
		public void pause ();
		public void resume ();
		public void stop ();
		public void set_position (int time_in_seconds);
		public void set_protocol_info (string protocol_info);
		public void set_volume (uint volume);
		public bool can_seek { get; }
		public bool mute { get; set; }
		public PlayingState state { get; }
		public string protocol_info { get; set; }
		public virtual signal void playing ();
		public virtual signal void paused ();
		public virtual signal void eos ();
		public virtual signal void error (GLib.Error error);
	    public string[] get_protocols ();
	    public string[] get_mime_types ();
	}
