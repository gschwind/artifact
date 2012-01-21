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

#include <GL/gl.h>
#include "gl_shoot_anim.h"

namespace gl {

shoot_anim_t::shoot_anim_t(double x0, double y0, double x1, double y1) :
		x0(x0), x1(x1), y0(y0), y1(y1) {
	time_left = 1.0;
}

void shoot_anim_t::render(double elapsed_time) {
	time_left -= elapsed_time;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBegin(GL_LINES);
	glColor3d(0.0, time_left, 0.0);
	glVertex3d(x0, y0, 0.0);
	glVertex3d(x1, y1, 0.0);
	glEnd();
}

bool shoot_anim_t::need_destroy() {
	return (time_left < 0.0);
}

}

