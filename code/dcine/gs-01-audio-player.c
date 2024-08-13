/*
* This program is part of Occam's Razor Number 7
* Copyright (C) 2024 Occam's Razor
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <gst/gst.h>
#include <stdio.h>
#include <string.h>

int
main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus     *bus;
  GstMessage *msg;
  char       cmd[2048];
 
  /* Inicializa GStreamer */
  gst_init (&argc, &argv);

  /* Construimos la pipeline */
  snprintf (cmd, 2048, "playbin uri=%s", argv[2]);  
  pipeline = gst_parse_launch (cmd, NULL);
  /* Reprodución */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Esperamos hasta error o EOS (End Of Stream) */
  bus = gst_element_get_bus (pipeline);
  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
				    GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) {
    g_error ("ERROR!. Inicializa la variable de entorno GST_DEBUG=*:WARN"
	     "para más detalles");
  }

  /* Liberamos memoria */
  gst_message_unref     (msg);
  gst_object_unref      (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref      (pipeline);
  return 0;
}


