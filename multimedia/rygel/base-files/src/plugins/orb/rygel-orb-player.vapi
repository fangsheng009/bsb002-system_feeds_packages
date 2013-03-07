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

		public Player ();
		public static Player get_default ();
	    public string[] get_protocols ();
	    public string[] get_mime_types ();
	}
