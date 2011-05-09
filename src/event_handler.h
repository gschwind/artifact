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

#ifndef EVENT_HANDLER_HPP_
#define EVENT_HANDLER_HPP_

#include <stack>
#include <list>
#include <map>
#include <SDL/SDL.h>
#include "event_func.h"
#include "vcontrol.h"
#include "config.h"
#include <stdint.h>

typedef struct _key_map_entry {
	int8_t type;
	int8_t num;
	int8_t dir;
} key_map_entry;

class event_handler {
	vcontrol * main;
	std::list<vcontrol *> event_listen;
	uint32_t axis_positive_press;
	uint32_t axis_negative_press;

	key_map_entry key_map[12];

	bool detect_press(SDL_Event const &ev, key_map_entry &m);
	bool detect_release(SDL_Event const &ev, key_map_entry &m);
	void parse_joy(std::string &s, key_map_entry &e);
public:
	event_handler(config &cfg, vcontrol * def);
	~event_handler();
	void add_listener(vcontrol * vc);
	void remove_listener(vcontrol * vc);
	void process_events(SDL_Event const &event);
};

#endif /* EVENT_HANDLER_H_ */
