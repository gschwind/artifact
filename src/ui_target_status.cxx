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

#include "ui_target_status.h"

namespace gl {

GLuint status_target::texture = 0;
GLuint status_target::notarget = 0;
gl::freetype_t * status_target::font = 0;

status_target::status_target() {
	target = 0;
	texture = gl_utils::load_texture("data/UI_player_status.png");
	notarget = gl_utils::load_texture("data/notarget.png");
	font = gl_utils::load_font("data/DejaVuSans.ttf", 11);
}

void status_target::render() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3d(1., 1., 1.);
	glTexCoord2d(1., 1.);
	glVertex3d(0.0, 0.0, 0.);
	glTexCoord2d(0., 1.);
	glVertex3d(width, 0.0, 0.);
	glTexCoord2d(0., 0.);
	glVertex3d(width, height, 0.);
	glTexCoord2d(1., 0.);
	glVertex3d(0.0, height, 0.);
	glEnd();

	if (target) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		glBegin(GL_QUADS);
		glColor3d(0.0, 0.0, 1.0);
		glVertex3d(width - 62.0, height - 19.0, 0.0);
		glVertex3d(
				width - ((target->shield / target->max_shield) * 99.0 + 62.0),
				height - 19.0, 0.0);
		glVertex3d(
				width - ((target->shield / target->max_shield) * 99.0 + 62.0),
				height - 26.0, 0.0);
		glVertex3d(width - 62.0, height - 26.0, 0.0);
		glColor3d(0.0, 1.0, 0.0);
		glVertex3d(width - 62.0, height - 29.0, 0.0);
		glVertex3d(width - ((target->armor / target->max_armor) * 99.0 + 62.0),
				height - 29.0, 0.0);
		glVertex3d(width - ((target->armor / target->max_armor) * 99.0 + 62.0),
				height - 37.0, 0.0);
		glVertex3d(width - 62.0, height - 37.0, 0.0);
		glColor3d(1.0, 1.0, 0.0);
		glVertex3d(width - 62.0, height - 40.0, 0.0);
		glVertex3d(width - ((target->hull / target->max_hull) * 99.0 + 62.0),
				height - 40.0, 0.0);
		glVertex3d(width - ((target->hull / target->max_hull) * 99.0 + 62.0),
				height - 48.0, 0.0);
		glVertex3d(width - 62.0, height - 48.0, 0.0);
		glEnd();

		glPushMatrix();
		glTranslated(width - 30.0, height - 30.0, 0.0);
		target->render_ui();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, -10.0, 0.0);
		font->print2(target->name.c_str());
		glPopMatrix();

	} else {
		glPushMatrix();
		glTranslated(width - 30.0, height - 30.0, 0.0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, notarget);
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
		glPopMatrix();
	}

}

}
