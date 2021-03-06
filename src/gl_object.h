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

#ifndef GL_OBJECT_HPP_
#define GL_OBJECT_HPP_

class gl_object {
public:
	gl_object();
	virtual ~gl_object();
	virtual void gl_init();
	virtual void gl_render();
	virtual void gl_release();
};

namespace gl {

class object {
public:
	object() { }
	virtual ~object() { };
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void release() = 0;
};


}

#endif /* GL_OBJECT_HPP_ */
