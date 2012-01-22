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

#include <GL/gl.h>
#include "gl_utils.h"
#include "gl_cast_bar.h"
#include "global.h"
#include "gl_shoot_anim.h"


namespace gl {

GLuint cast_bar::texture = 0;

cast_bar::cast_bar(double cast_time, double x0, double y0, double x1, double y1, ship_t * target) {
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
	time_left = cast_time;
	this->cast_time = cast_time;
	texture = gl_utils::load_texture("data/cast_bar.png");
	this->target = target;
}

void cast_bar::render(double elapsed_time) {
	time_left -= elapsed_time;

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


	glBegin(GL_QUADS);
	glColor3d(1.0, 0.0, 1.0);
	glVertex3d(7.0, height - 5.0, 0.0);
	glVertex3d((time_left / cast_time) * 121.0 + 7.0, height - 5.0, 0.0);
	glVertex3d((time_left / cast_time) * 121.0 + 7.0, height - 12.0, 0.0);
	glVertex3d(7.0, height - 12.0, 0.0);
	glEnd();

	if(time_left <= 0.0) {
		if (target->shield > 0.0) {
			target->shield -= 10.0;
		} else if (target->armor > 0.0) {
			target->armor -= 10.0;
		} else if (target->hull > 0.0) {
			target->hull -= 10.0;
		}

		global.world.push_back(
				new shoot_anim_t(global.ship.x, global.ship.y,
						target->x, target->y));

		if (target->hull <= 0) {
			global.world.remove(target);
			global.enemy.remove(target);
			delete target;
			global.ship.selected = 0;
			global.right_status_target->target = 0;
		}
	}

}

bool cast_bar::need_destroy() {
	return time_left <= 0.0;
}

}



