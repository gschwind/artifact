/*
 * Copyright 2012 Benoit Gschwind <gschwind@gnu-log.net>
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

#ifndef GL_SHIP_H_
#define GL_SHIP_H_

#include <string>
#include "freetype_font.h"
#include "gl_renderable.h"

namespace gl {

struct ship_t : public renderable_i {
	static gl::freetype_t * font;
	double x;
	double y;
	double orientation;
	GLuint texture;

	double max_shield;
	double max_armor;
	double max_hull;

	double shield;
	double armor;
	double hull;
	std::string name;
	bool is_selected;

	ship_t(double x, double y, double orientation, std::string & name);
	void render(double elapsed_time);
	void render_ui();
	bool need_destroy();

};

}

#endif /* GL_SHIP_H_ */
