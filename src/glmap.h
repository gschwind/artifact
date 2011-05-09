/*
 * glmap.h
 *
 *  Created on: Mar 3, 2010
 *      Author: gschwind
 */

#ifndef GLMAP_H_
#define GLMAP_H_

#include <GL/gl.h>
#include <string>
#include "config.h"
#include "map.h"
#include "render.h"
#include "gl_object.h"

class glmap: public map, public gl_object {
	/* palette pixbuf */
	GdkPixbuf * pixbuf_;
	/* map image */
	GdkPixmap * pixmap_;
	GtkWidget * image_;

	GtkWidget * drawing_area;

	gboolean show_layer_[8];

	GLuint texture_id_;
	std::string palette_name_;

	GLuint palette_list_;

	int x, y;
	int h, w;

public:
	glmap(config &conf, uint32_t width, uint32_t height, uint8_t fill,
			std::string palette_name, GtkWidget * drawing_area);
	~glmap();

	GdkPixbuf * get_pixbuf();
	GtkWidget * get_pixmap();
	GtkWidget * get_image();

	virtual void set(uint32_t x, uint32_t y, uint32_t layer, uint8_t value);
	virtual void set_pxl(uint32_t x, uint32_t y, uint32_t layer, uint8_t value);

	void show_layer(uint32_t layer);
	void hide_layer(uint32_t layer);

	void redraw();
	void redraw_pxl(uint32_t x, uint32_t y);

	void set_size(int height, int witdh);
	void move_view_pos(int x, int y);

	void gl_init();
	void gl_render();
	void gl_release();

};

#endif /* GLMAP_H_ */
