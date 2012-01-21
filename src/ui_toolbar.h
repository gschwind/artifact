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

#ifndef UI_TOOLBAR_H_
#define UI_TOOLBAR_H_

#include "gl_utils.h"

namespace gl {

struct toolbar {
	static GLuint texture;
	static gl::freetype_t * font;
	static double const width = 410;
	static double const height = 40;
	toolbar() {
		texture = gl_utils::load_texture("data/bottom_toolbar.png");
		font = gl_utils::load_font("data/DejaVuSans.ttf", 11);
	}

	void render() {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2d(1., 1.);
		glColor3d(1., 1., 1.);
		glVertex3d(0.0, 0.0, 0.);
		glTexCoord2d(0., 1.);
		glVertex3d(width, 0.0, 0.);
		glTexCoord2d(0., 0.);
		glVertex3d(width, height, 0.);
		glTexCoord2d(1., 0.);
		glVertex3d(0.0, height, 0.);
		glEnd();

		glPushMatrix();
		glTranslated(10.0, 20.0, 0.0);
		for(int i = 1; i < 10; ++i) {
			char buf[40];
			snprintf(buf, 39, "%d", i);
			font->print2(buf);
			glTranslated(40.0, 0.0, 0.0);
		}

		glPopMatrix();
	}

};

GLuint toolbar::texture = 0;
gl::freetype_t * toolbar::font = 0;
}




#endif /* UI_TOOLBAR_H_ */
