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

#ifndef GL_DOT_H_
#define GL_DOT_H_

#include <GL/glx.h>
#include "gl_object.h"


namespace gl {

class dot : public object {
	double _x, _y;

	dot(dot const &);
	dot & operator=(dot const &);
public:

	dot(double x, double y) : _x(x), _y(y) {

	}

	~dot() {

	}

	void init() {

	}

	void render() {
		glBegin(GL_POINT);
		glColor3d(1.0, 0.0, 0.0);
		glVertex3d(_x, _y, 0.0);
		glEnd();
	}

	void release() {

	}

};

}


#endif /* GL_DOT_H_ */
