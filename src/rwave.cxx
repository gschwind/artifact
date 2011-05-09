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
#include "rwave.h"
#include <math.h>

rwave::rwave(vrender * src, float speed, float max) {
	this->src = src;
	this->speed = speed;
	this->max = max;
	this->cur = 0.0;
}

rwave::~rwave() {
	// TODO Auto-generated destructor stub
}

void rwave::render() {
	glPushMatrix();
	glScalef(max * (cos(cur) + 1.0) / 2.0 + 1.0, max * (cos(cur) + 1.0) / 2.0 + 1.0, 0.0);
	src->render();
	glPopMatrix();

	cur += speed;
}
