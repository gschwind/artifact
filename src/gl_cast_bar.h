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


#ifndef GL_CAST_BAR_H_
#define GL_CAST_BAR_H_

#include "gl_renderable.h"
#include "gl_ship.h"

namespace gl {

struct cast_bar : public renderable_i {
	static unsigned int const height = 17;
	static unsigned int const width = 135;

	static GLuint texture;
	double time_left;
	double cast_time;
	double x0, x1, y0, y1;

	ship_t * target;

	cast_bar(double cast_time, double x0, double y0, double x1, double y1, ship_t * target);
	void render(double elapsed_time);
	bool need_destroy();

};

}


#endif /* GL_CAST_BAR_H_ */
