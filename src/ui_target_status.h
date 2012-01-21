/*
 * ui_player_status.h
 *
 *  Created on: Jan 21, 2012
 *      Author: gschwind
 */

#ifndef UI_TARGET_STATUS_H_
#define UI_TARGET_STATUS_H_

#include "gl_utils.h"

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

	status_target() {
		target = 0;
		texture = gl_utils::load_texture("data/UI_player_status.png");
		notarget = gl_utils::load_texture("data/notarget.png");
		font = gl_utils::load_font("data/DejaVuSans.ttf", 11);
	}

	void render() {

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
			glVertex3d(width - ((shield / max_shield) * 99.0 + 62.0),
					height - 19.0, 0.0);
			glVertex3d(width - ((shield / max_shield) * 99.0 + 62.0),
					height - 26.0, 0.0);
			glVertex3d(width - 62.0, height - 26.0, 0.0);
			glColor3d(0.0, 1.0, 0.0);
			glVertex3d(width - 62.0, height - 29.0, 0.0);
			glVertex3d(width - ((shield / max_shield) * 99.0 + 62.0),
					height - 29.0, 0.0);
			glVertex3d(width - ((shield / max_shield) * 99.0 + 62.0),
					height - 37.0, 0.0);
			glVertex3d(width - 62.0, height - 37.0, 0.0);
			glColor3d(1.0, 1.0, 0.0);
			glVertex3d(width - 62.0, height - 40.0, 0.0);
			glVertex3d(width - ((shield / max_shield) * 99.0 + 62.0),
					height - 40.0, 0.0);
			glVertex3d(width - ((shield / max_shield) * 99.0 + 62.0),
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

};

GLuint status_target::texture = 0;
GLuint status_target::notarget = 0;
gl::freetype_t * status_target::font = 0;
}

#endif /* UI_PLAYER_STATUS_H_ */
