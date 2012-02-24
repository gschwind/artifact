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
#include "gl_shoot_anim_bullet1.h"
#include "gl_utils.h"

namespace gl {

GLint shoot_anim_bullet1_t::texture = 0;

shoot_anim_bullet1_t::shoot_anim_bullet1_t(double x0, double y0, double x1,
		double y1) :
		x0(x0), x1(x1), y0(y0), y1(y1) {
	texture = gl_utils::load_texture("data/bullet1.png");

	time_left = 1.0;
}

void shoot_anim_bullet1_t::render(double elapsed_time) {
	time_left -= elapsed_time;

	double ax = x0 - x1;
	double ay = y0 - y1;

	double x = ax * time_left + x1;
	double y = ay * time_left + y1;

	glPushMatrix();
	glTranslated(x, y, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glTexCoord2d(1., 1.);
	glColor3f(1., 1., 1.);
	glVertex3f(-8.0, -8., 0.);
	glTexCoord2d(0., 1.);
	glVertex3f(8.0, -8.0, 0.);
	glTexCoord2d(0., 0.);
	glVertex3f(8.0, 8.0, 0.);
	glTexCoord2d(1., 0.);
	glVertex3f(-8.0, 8.0, 0.);
	glEnd();
	glPopMatrix();
}

bool shoot_anim_bullet1_t::need_destroy() {
	return (time_left < 0.0);
}

}

