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

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <ctime>
#include <list>

#include "gl_renderable.h"
#include "gl_ship.h"
#include "gl_main_ship.h"
#include "ui_toolbar.h"
#include "ui_player_status.h"
#include "ui_target_status.h"

struct global_t {
	std::list<gl::renderable_i *> world;
	std::list<gl::ship_t *> enemy;
	timespec last_frame;
	timespec cur_frame;
	gl::toolbar * toolbar;
	gl::status_player * left_status_player;
	gl::status_target * right_status_target;
	gl::main_ship_t ship;
	gl::freetype_t * f;

	global_t() {

	}

};

extern global_t global;

#endif /* GLOBAL_H_ */
