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

#ifndef GL_RENDERABLE_H_
#define GL_RENDERABLE_H_

namespace gl {

struct renderable_i {
	virtual ~renderable_i() { }
	virtual void render(double elapsed_time) = 0;
	virtual bool need_destroy() = 0;

	static bool need_destroy(renderable_i * value) {
		return value->need_destroy();
	}
};

}

#endif /* GL_RENDERABLE_H_ */
