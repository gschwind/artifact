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

#ifndef FONT_HPP_
#define FONT_HPP_

#include <GL/gl.h>
#include "gl_utils.h"

class font {
    GLuint font_texture;
    int xs, ys;
public:
    font(char const * name, int nb_x, int nb_y) {
    	font_texture = gl_utils::load_texture(name);
    	xs = nb_x;
    	ys = nb_y;
    }

    void print(const char * text) {
    	glPushMatrix();
    	while (*text != 0) {
    		int y = (*text / xs);
    		float top = y / (float)ys;
    		float bot = (y + 1) / (float)ys;
    		int x = (*text % xs);
    		float lef = x / (float)xs;
    		float rig = (x + 1) / (float)xs;
    		glBindTexture(GL_TEXTURE_2D, font_texture);
    		glBegin(GL_QUADS);
    		glTexCoord2f(lef, top);
    		glVertex2f(0.0, 0.0);
    		glTexCoord2f(lef, bot);
    		glVertex2f(0.0, 16.0);
    		glTexCoord2f(rig, bot);
    		glVertex2f(8.0, 16.0);
    		glTexCoord2f(rig, top);
    		glVertex2f(8.0, 0.0);
    		glEnd();
    		glTranslatef(8.0, 0.0, 0.0);
    		text++;
    	}
    	glPopMatrix();
    }


};

#endif /* FONTS_HPP_ */
