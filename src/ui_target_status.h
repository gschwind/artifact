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

#ifndef UI_TARGET_STATUS_H_
#define UI_TARGET_STATUS_H_

#include "gl_utils.h"
#include "gl_ship.h"

namespace gl {

struct status_target {
	double max_shield;
	double max_armor;
	double max_hull;

	double shield;
	double armor;
	double hull;

	gl::ship_t * target;

	static double const width = 167;
	static double const height = 63;

	static GLuint texture;
	static GLuint notarget;
	static gl::freetype_t * font;

	status_target();
	void render();

};

}

#endif /* UI_PLAYER_STATUS_H_ */
