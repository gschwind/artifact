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

#include "GL/gl.h"
#include <cmath>
#include "gl_utils.h"
#include "gl_ship.h"

namespace gl {

gl::freetype_t * ship_t::font = 0;

ship_t::ship_t(double x, double y, double orientation, std::string & name) :
		x(x), y(y), orientation(orientation) {
	font = gl_utils::load_font("data/DejaVuSans.ttf", 11);
	is_selected = false;
	this->name = name;

	max_shield = 100.0;
	max_armor = 100.0;
	max_hull = 100.0;

	shield = 100.0;
	armor = 100.0;
	hull = 100.0;
}

void ship_t::render(double elapsed_time) {
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glPushMatrix();
	glTranslated(0.0, 10.0, 0.0);
//		glRotated(ship.orientation, 0.0, 0.0, 1.0);
	font->print2(name.c_str());
	glPopMatrix();

	glRotated(orientation, 0.0, 0.0, 1.0);

	if (is_selected) {
		glDisable(GL_TEXTURE_2D);

		double const r = 16.0;
		glBegin(GL_LINES);
		glColor3d(1.0, 0.0, 0.0);
		int i;
		for (i = 0; i < 16; ++i) {
			glVertex3d(cos(i * M_PI_4 / 2.0) * r, sin(i * M_PI_4 / 2.0) * r,
					0.0);
			glVertex3d(cos((i + 1) * M_PI_4 / 2.0) * r,
					sin((i + 1) * M_PI_4 / 2.0) * r, 0.0);
		}
		glEnd();

	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
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

void ship_t::render_ui() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2d(1., 1.);
	glColor3d(1., 1., 1.);
	glVertex3d(-16.0, -16., 0.);
	glTexCoord2d(0., 1.);
	glVertex3d(16.0, -16.0, 0.);
	glTexCoord2d(0., 0.);
	glVertex3d(16.0, 16.0, 0.);
	glTexCoord2d(1., 0.);
	glVertex3d(-16.0, 16.0, 0.);
	glEnd();
}

bool ship_t::need_destroy() {
	return false;
}

}


