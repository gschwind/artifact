/*
 * Copyright 2010 Benoit Gschwind <gschwind@gnu-log.net>
 *
 * This file is part of artifact.
 *
 * artifact is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * artifact is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with artifact.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include "map.h"
#include "palette_window.h"

void palette_window::press_event(GtkWidget * widget, GdkEventButton * event,
		palette_window * ths) {
	uint8_t select_x, select_y;
	select_x = ((uint8_t) event->x) / 16;
	select_y = ((uint8_t) event->y) / 16;
	ths->selected_sprite_ = (select_y&0x0f)<< 4 | (select_x&0x0f);
	cairo_t * cr = gdk_cairo_create(GDK_DRAWABLE(ths->pixmap_));
	cairo_rectangle(cr, 0.0, 0.0, 256.0, 256.0);
	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	cairo_stroke(cr);
	cairo_destroy(cr);
	gtk_widget_queue_draw(GTK_WIDGET(ths->image_));
	g_print("X: %f Y: %f \n", event->x, event->y);
	g_print("Hello World\n");
}

palette_window::palette_window(config &conf, map * map) {
	std::string palette_filename = conf.get_config("datadir", "");
	palette_filename += "/";
	palette_filename += map->get_palette_name();
	map_ = map;
	selected_sprite_ = 0;
	/* create a new window */
	window_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window_), "helo");
	gtk_window_set_resizable(GTK_WINDOW(window_), FALSE);
	/* Sets the border width of the window. */
	gtk_container_set_border_width(GTK_CONTAINER(window_), 0);

	g_signal_connect (G_OBJECT(window_), "delete_event",
			G_CALLBACK (palette_window::delete_event), NULL);

	g_signal_connect (G_OBJECT(window_), "destroy",
			G_CALLBACK (palette_window::destroy), NULL);

	eventbox_ = gtk_event_box_new();
	pixmap_ = gdk_pixmap_new(NULL, 256, 256, 24);
	//gc_red_ = gdk_gc_new(pixmap_);
	//gc_purple_ = gdk_gc_new(pixmap_);
	GdkColor color = { 0, 0xffff, 0, 0 };
	//gdk_gc_set_rgb_bg_color(gc_red_, &color);
	//gdk_gc_set_rgb_fg_color(gc_red_, &color);
	color.blue =  0xffff;
	//gdk_gc_set_rgb_bg_color(gc_purple_, &color);
	//gdk_gc_set_rgb_fg_color(gc_purple_, &color);

	//gdk_draw_rectangle(pixmap_, gc_purple_, TRUE, 0, 0, 256, 256);
	pixbuf_ = gdk_pixbuf_new_from_file(palette_filename.c_str(), NULL);
	//gdk_draw_pixbuf(pixmap_, NULL, pixbuf_, 0, 0, 0, 0, 256, 256,
	//		GDK_RGB_DITHER_NONE, 0, 0);
	image_ = gtk_image_new_from_pixmap(pixmap_, NULL);

	/* When the button receives the "clicked" signal, it will call the
	 * function hello() passing it NULL as its argument.  The hello()
	 * function is defined above. */
	g_signal_connect (G_OBJECT (eventbox_), "button_press_event",
			G_CALLBACK (palette_window::press_event), this);

	/* This packs the button into the window (a gtk container). */
	gtk_container_add(GTK_CONTAINER(window_), eventbox_);
	gtk_container_add(GTK_CONTAINER(eventbox_), image_);

}

palette_window::~palette_window() {
	// TODO Auto-generated destructor stub
}

void palette_window::show() {
	/* The final step is to display this newly created widget. */
	gtk_widget_show(eventbox_);
	gtk_widget_show(image_);
	/* and the window */
	gtk_widget_show(window_);
}

gboolean palette_window::delete_event(GtkWidget *widget, GdkEvent *event,
		gpointer data) {
	/* Ne pas quite le progamme quand on click sur la croix */
	return TRUE;
}

/* Another callback */
void palette_window::destroy(GtkWidget *widget, gpointer data) {

}

uint8_t palette_window::get_selected_sprite() {
	return selected_sprite_;
}
