/*
 * ui_player_status.h
 *
 *  Created on: Jan 21, 2012
 *      Author: gschwind
 */

#ifndef UI_PLAYER_STATUS_H_
#define UI_PLAYER_STATUS_H_

#include "gl_utils.h"

namespace gl {

struct status_player {
	double max_shield;
	double max_armor;
	double max_hull;

	double shield;
	double armor;
	double hull;

	std::string name;

	static double const width = 167;
	static double const height = 63;

	static GLuint texture;
	status_player() {
		texture = gl_utils::load_texture("data/UI_player_status.png");
	}

	void render() {

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glColor3d(1., 1., 1.);
		glTexCoord2d(0., 1.);
		glVertex3d(0.0, 0.0, 0.);
		glTexCoord2d(1., 1.);
		glVertex3d(width, 0.0, 0.);
		glTexCoord2d(1., 0.);
		glVertex3d(width, height, 0.);
		glTexCoord2d(0., 0.);
		glVertex3d(0.0, height, 0.);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		glBegin(GL_QUADS);

		glColor3d(0.0, 0.0, 1.0);
		glVertex3d(62.0, height - 19.0, 0.0);
		glVertex3d((shield / max_shield) * 99.0 + 62.0, height - 19.0, 0.0);
		glVertex3d((shield / max_shield) * 99.0 + 62.0, height - 26.0, 0.0);
		glVertex3d(62.0, height - 26.0, 0.0);
		glColor3d(0.0, 1.0, 0.0);
		glVertex3d(62.0, height - 29.0, 0.0);
		glVertex3d((shield / max_shield) * 99.0 + 62.0, height - 29.0, 0.0);
		glVertex3d((shield / max_shield) * 99.0 + 62.0, height - 37.0, 0.0);
		glVertex3d(62.0, height - 37.0, 0.0);
		glColor3d(1.0, 1.0, 0.0);
		glVertex3d(62.0, height - 40.0, 0.0);
		glVertex3d((shield / max_shield) * 99.0 + 62.0, height - 40.0, 0.0);
		glVertex3d((shield / max_shield) * 99.0 + 62.0, height - 48.0, 0.0);
		glVertex3d(62.0, height - 48.0, 0.0);
		glEnd();

	}

};

GLuint status_player::texture = 0;

}



#endif /* UI_PLAYER_STATUS_H_ */
