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

	status_player();
	void render();

};

}

#endif /* UI_PLAYER_STATUS_H_ */
