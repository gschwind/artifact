/*
 * palette_window.h
 *
 *  Created on: Jan 24, 2010
 *      Author: gschwind
 */

#ifndef PALETTE_WINDOW_H_
#define PALETTE_WINDOW_H_

#include <string>
#include <gtk/gtk.h>
#include "map.h"
#include "config.h"

class palette_window {
	GtkWidget * window_;
	GtkWidget * eventbox_;
	GtkWidget * image_;
	GdkPixmap * pixmap_;
	GdkPixbuf * pixbuf_;
	GdkGC * gc_red_;
	GdkGC * gc_purple_;

	GtkWidget * fs;

	map * map_;

	std::string filename_;
	uint8_t selected_sprite_;
private:

	/* This is a callback function. The data arguments are ignored
	 * in this example. More on callbacks below. */
	static void press_event(GtkWidget * widget, GdkEventButton * event,
			palette_window * ths);

	static gboolean delete_event(GtkWidget *widget, GdkEvent *event,
			gpointer data);

	/* Another callback */
	static void destroy(GtkWidget *widget, gpointer data);

public:
	palette_window(config &conf, map * map);
	virtual ~palette_window();
	void show();
	uint8_t get_selected_sprite();
};

#endif /* PALETTE_WINDOW_H_ */
