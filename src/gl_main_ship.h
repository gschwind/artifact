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

#ifndef GL_MAIN_SHIP_H_
#define GL_MAIN_SHIP_H_

#include "gl_ship.h"
#include "gl_cast_bar.h"

namespace gl {

struct main_ship_t {
	double x, y;
	double orientation;
	double xo;
	bool move_forward;
	bool move_backward;
	bool move_left;
	bool move_right;
	bool right_click;
	bool left_click;
	int xpos, ypos;

	double max_shield;
	double max_armor;
	double max_hull;

	double shield;
	double armor;
	double hull;

	double zoom;

	GLuint texture;

	main_ship_t() {
		x = 0.0;
		y = 0.0;
		orientation = 0.0;
		xo = 0.0;
		move_forward = false;
		move_backward = false;
		move_left = false;
		move_right = false;
		zoom = 10.0;
		max_shield = 100.0;
		shield = 100.0;
		right_click = false;
		left_click = false;
		texture = 0;
		casting = 0;
	}

	double foox, fooy;
	long long int foos;

	gl::ship_t * selected;

	gl::cast_bar * casting;

};

}

#endif /* GL_MAIN_SHIP_H_ */
