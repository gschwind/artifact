/*
 * glmap.cc
 *
 *  Created on: Mar 3, 2010
 *      Author: gschwind
 */

#include <gtk/gtk.h>
#include <string>
#include <IL/ilut.h>
#include "gl_utils.h"
#include "glmap.h"

glmap::glmap(config &conf, uint32_t width, uint32_t height, uint8_t fill,
		std::string palette_name, GtkWidget * drawing_area) :
	map(width, height, fill, palette_name) {
	this->drawing_area = drawing_area;
	palette_name_ = conf.get_config("datadir", "");
	palette_name_ += "/";
	palette_name_ += palette_name;

	for (int l = 0; l < 8; l++)
		show_layer_[l] = FALSE;

	x = 0;
	y = 0;

}

glmap::~glmap() {

}

GdkPixbuf *
glmap::get_pixbuf() {
	return pixbuf_;
}

//GtkWidget * gtk_map::get_pixmap() {
//      return pixmap_;
//}

GtkWidget *
glmap::get_image() {
	return image_;
}

void glmap::set(uint32_t x, uint32_t y, uint32_t layer, uint8_t value) {
	map::set(x, y, layer, value);
	uint8_t sprite = value;
	int sprite_x = sprite & 0x0f;
	int sprite_y = (sprite >> 4) & 0x0f;
}

void glmap::set_pxl(uint32_t x, uint32_t y, uint32_t layer, uint8_t value) {
	int select_x, select_y;
	select_x = ((int) x + this->x) / 16;
	select_y = ((int) y + this->y) / 16;
	if (select_x >= 0 && select_x < height_ && select_y >= 0 && select_y
			< width_)
		map::set(select_x, select_y, layer, value);
}

void glmap::redraw() {
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

void glmap::redraw_pxl(uint32_t i, uint32_t j) {
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

void glmap::show_layer(uint32_t layer) {
	show_layer_[layer] = TRUE;
}

void glmap::hide_layer(uint32_t layer) {
	show_layer_[layer] = FALSE;
}

void glmap::gl_render() {
	printf("glmap::render\n");
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int x_offset, y_offset;
	x_offset = -1 * (x % 16);
	y_offset = -1 * (y % 16);
	glTranslatef(x_offset, y_offset, 0.0);
	int x_i = x / 16;
	int y_i = y / 16;

	if (x_i < 0) {
		glTranslatef(-1 * x_i * 16.0, 0.0, 0.0);
		x_i = 0;
	}

	if (y_i < 0) {
		glTranslatef(0.0, -1 * y_i * 16.0, 0.0);
		y_i = 0;
	}

	int x_length = x_i + drawing_area->allocation.width / 16 + 2;
	int y_length = y_i + drawing_area->allocation.height / 16 + 2;

	if (x_length > height_) {
		x_length = height_;
	}

	if (y_length > width_) {
		y_length = width_;
	}

	for (int l = 0; l < 8; l++) {
		if (show_layer_[l]) {
			glPushMatrix();
			for (int j = y_i; j < y_length; j++) {
				glPushMatrix();
				for (int i = x_i; i < x_length; i++) {
					uint8_t sprite = get(i, j, l);
					glCallList(palette_list_ + sprite);
				}
				glPopMatrix();
				glTranslatef(0.0, 16.0, 0.0);
			}
			glPopMatrix();
		}
		glTranslatef(0.0, 0.0, 1.0 / 16.0);
	}
	glPopMatrix();
}

void glmap::gl_init() {
	texture_id_ = gl_utils::load_texture(palette_name_.c_str());
	palette_list_ = glGenLists(256);
	for (int i = 0; i < 256; i++) {
		int sprite_x = i & 0x0f;
		int sprite_y = (i >> 4) & 0x0f;
		glNewList(palette_list_ + i, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(sprite_x / 16.0, sprite_y / 16.0);
		glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(sprite_x / 16.0, (sprite_y + 1) / 16.0);
		glVertex3f(0.0, 16.0, 0.0);
		glTexCoord2f((sprite_x + 1) / 16.0, (sprite_y + 1) / 16.0);
		glVertex3f(16.0, 16.0, 0.0);
		glTexCoord2f((sprite_x + 1) / 16.0, sprite_y / 16.0);
		glVertex3f(16.0, 0.0, 0.0);
		glEnd();
		glTranslatef(16.0, 0.0, 0.0);
		glEndList();
	}
}

void glmap::set_size(int height, int width) {
	h = height;
	w = width;
}

void glmap::move_view_pos(int x, int y) {
	this->x += x;
	this->y += y;
	g_print("glmap::move_view_pos %d %d\n", this->x, this->y);
}

void glmap::gl_release() {
	return;
}

