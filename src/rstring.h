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

#ifndef RSTRING_HPP_
#define RSTRING_HPP_

#include <string>
#include "render.h"
#include "font.h"

class rstring: public vrender {
	public:
	std::string s;
	int x, y;
	font * f;
	rstring(char * string, font *, int x, int y);
	virtual ~rstring();
	void render();
};

#endif /* RSTRING_H_ */