/*
 * gtk_map.cc
 *
 *  Created on: Jan 24, 2010
 *      Author: gschwind
 */

#include <gtk/gtk.h>
#include <string>
#include "gtk_map.h"

gtk_map::gtk_map(config &conf, uint32_t width, uint32_t height, uint8_t fill,
		std::string palette_name) :
	map(width, height, fill, palette_name) {
	std::string palette_filename = conf.get_config("datadir", "");
	palette_filename += "/";
	palette_filename += palette_name;

	GdkColor color = { 0, 0, 0, 0 };

	for(int l = 0; l < 8; l++)
		show_layer_[l] = FALSE;
	//show_layer_[0] = TRUE;

	pixbuf_ = gdk_pixbuf_new_from_file(palette_filename.c_str(), NULL);
	pixmap_ = gdk_pixmap_new(NULL, 16 * width_, 16 * height_, 24);
	//gc_ = gdk_gc_new(pixmap_);
	//gdk_gc_set_rgb_bg_color(gc_, &color);
	//gdk_gc_set_rgb_fg_color(gc_, &color);
	redraw();
	image_ = gtk_image_new_from_pixmap(pixmap_, NULL);

}

gtk_map::~gtk_map() {

}

GdkPixbuf * gtk_map::get_pixbuf() {
	return pixbuf_;
}

//GtkWidget * gtk_map::get_pixmap() {
//	return pixmap_;
//}

GtkWidget * gtk_map::get_image() {
	return image_;
}

void gtk_map::set(uint32_t x, uint32_t y, uint32_t layer, uint8_t value) {
	map::set(x, y, layer, value);
	uint8_t sprite = value;
	int sprite_x = sprite & 0x0f;
	int sprite_y = (sprite >> 4) & 0x0f;

	redraw_pxl(x, y);
	gtk_widget_queue_draw(GTK_WIDGET(image_));
	//if (show_layer_[layer]) {
	//	gdk_draw_pixbuf(pixmap_, NULL, pixbuf_, sprite_x * 16, sprite_y * 16, x
	//			* 16, y * 16, 16, 16, GDK_RGB_DITHER_NONE, 0, 0);
	//	gtk_widget_queue_draw(GTK_WIDGET(image_));
	//}
}

void gtk_map::redraw() {
	//gdk_draw_rectangle(pixmap_, gc_, TRUE, 0, 0, width_ * 16, height_ * 16);
	for (int l = 0; l < 8; l++)
		if (show_layer_[l])
			for (int i = 0; i < width_; i++)
				for (int j = 0; j < height_; j++) {
					uint8_t sprite = get(i, j, l);
					int sprite_x = sprite & 0x0f;
					int sprite_y = (sprite >> 4) & 0x0f;
					//gdk_draw_pixbuf(pixmap_, NULL, pixbuf_, sprite_x * 16,
					//		sprite_y * 16, i * 16, j * 16, 16, 16,
					//		GDK_RGB_DITHER_NONE, 0, 0);

				}

}

void gtk_map::redraw_pxl(uint32_t i, uint32_t j) {
	//gdk_draw_rectangle(pixmap_, gc_, TRUE, i * 16, j * 16, 16, 16);
	for (int l = 0; l < 8; l++)
		if (show_layer_[l]) {
			uint8_t sprite = get(i, j, l);
			int sprite_x = sprite & 0x0f;
			int sprite_y = (sprite >> 4) & 0x0f;
			//gdk_draw_pixbuf(pixmap_, NULL, pixbuf_, sprite_x * 16, sprite_y
			//		* 16, i * 16, j * 16, 16, 16, GDK_RGB_DITHER_NONE, 0, 0);

		}

}


void gtk_map::show_layer(uint32_t layer) {
	show_layer_[layer] = TRUE;
}

void gtk_map::hide_layer(uint32_t layer) {
	show_layer_[layer] = FALSE;
}


