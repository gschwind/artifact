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

#ifndef GL_SHOOT_ANIM_H_
#define GL_SHOOT_ANIM_H_

#include "gl_renderable.h"

namespace gl {

struct shoot_anim_t: public renderable_i {
	double time_left;
	double x0, x1, y0, y1;
	shoot_anim_t(double x0, double y0, double x1, double y1);
	void render(double elapsed_time);
	bool need_destroy();
};

}

#endif /* GL_SHOOT_ANIM_H_ */
