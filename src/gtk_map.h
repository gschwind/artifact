/*
 * gtk_map.h
 *
 *  Created on: Jan 24, 2010
 *      Author: gschwind
 */

#ifndef GTK_MAP_H_
#define GTK_MAP_H_

#include <gtk/gtk.h>
#include "map.h"
#include "config.h"

class gtk_map : public map {
	/* palette pixbuf */
	GdkPixbuf * pixbuf_;
	/* map image */
	GdkPixmap * pixmap_;
	GtkWidget * image_;

	gboolean show_layer_[8];

public:
	gtk_map(config &conf, uint32_t width, uint32_t height, uint8_t fill, std::string palette_name);
	~gtk_map();

	GdkPixbuf * get_pixbuf();
	GtkWidget * get_pixmap();
	GtkWidget * get_image();

	virtual void set(uint32_t x, uint32_t y, uint32_t layer, uint8_t value);

	void show_layer(uint32_t layer);
	void hide_layer(uint32_t layer);

	void redraw();
	void redraw_pxl(uint32_t x, uint32_t y);

};

#endif /* GTK_MAP_H_ */
