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

#include <iterator>
#include <SDL/SDL.h>
#include "event_handler.h"

void event_handler::process_events(SDL_Event const &ev) {

	if (detect_release(ev, key_map[0]))
		main->joy_button0_release();
	if (detect_release(ev, key_map[1]))
		main->joy_button1_release();
	if (detect_release(ev, key_map[2]))
		main->joy_button2_release();
	if (detect_release(ev, key_map[3]))
		main->joy_button3_release();
	if (detect_release(ev, key_map[4]))
		main->joy_button4_release();
	if (detect_release(ev, key_map[5]))
		main->joy_button5_release();
	if (detect_release(ev, key_map[6]))
		main->joy_button6_release();
	if (detect_release(ev, key_map[7]))
		main->joy_button7_release();
	if (detect_release(ev, key_map[8]))
		main->joy_left_release();
	if (detect_release(ev, key_map[9]))
		main->joy_right_release();
	if (detect_release(ev, key_map[10]))
		main->joy_up_release();
	if (detect_release(ev, key_map[11]))
		main->joy_down_release();

	if (detect_press(ev, key_map[0]))
		main->joy_button0_press();
	if (detect_press(ev, key_map[1]))
		main->joy_button1_press();
	if (detect_press(ev, key_map[2]))
		main->joy_button2_press();
	if (detect_press(ev, key_map[3]))
		main->joy_button3_press();
	if (detect_press(ev, key_map[4]))
		main->joy_button4_press();
	if (detect_press(ev, key_map[5]))
		main->joy_button5_press();
	if (detect_press(ev, key_map[6]))
		main->joy_button6_press();
	if (detect_press(ev, key_map[7]))
		main->joy_button7_press();
	if (detect_press(ev, key_map[8]))
		main->joy_left_press();
	if (detect_press(ev, key_map[9]))
		main->joy_right_press();
	if (detect_press(ev, key_map[10]))
		main->joy_up_press();
	if (detect_press(ev, key_map[11]))
		main->joy_down_press();

	/* update key press status */
	if (SDL_JOYAXISMOTION == ev.type) {
		if (ev.jaxis.value < -16000)
			axis_negative_press |= 0x01 << ev.jaxis.axis;
		if (ev.jaxis.value > 16000)
			axis_positive_press |= 0x01 << ev.jaxis.axis;
		if (ev.jaxis.value > -16000)
			axis_negative_press &= ~(0x01 << ev.jaxis.axis);
		if (ev.jaxis.value < 16000)
			axis_positive_press &= ~(0x01 << ev.jaxis.axis);
	}

}

event_handler::event_handler(config &cfg, vcontrol * def) :
	event_listen() {
	this->main = def;
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	std::string type = cfg.get_config("joy::type", "j0");
	if (type[0] == 'j') {
		int j = atoi(type.c_str() + 1);
		SDL_Joystick * joy;
		if (SDL_NumJoysticks() > j) {
			// Open joystick
			joy = SDL_JoystickOpen(0);

			if (joy) {
				printf("Opened Joystick 0\n");
				printf("Name: %s\n", SDL_JoystickName(0));
				printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
				printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
				printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
			} else
				printf("Couldn't open Joystick 0\n");
		}

	}
	std::string b0 = cfg.get_config("joy::button0", "b0");
	parse_joy(b0, key_map[0]);
	std::string b1 = cfg.get_config("joy::button1", "b1");
	parse_joy(b1, key_map[1]);
	std::string b2 = cfg.get_config("joy::button2", "b2");
	parse_joy(b2, key_map[2]);
	std::string b3 = cfg.get_config("joy::button3", "b3");
	parse_joy(b3, key_map[3]);
	std::string b4 = cfg.get_config("joy::button4", "b4");
	parse_joy(b4, key_map[4]);
	std::string b5 = cfg.get_config("joy::button5", "b5");
	parse_joy(b5, key_map[5]);
	std::string b6 = cfg.get_config("joy::button6", "b6");
	parse_joy(b6, key_map[6]);
	std::string b7 = cfg.get_config("joy::button7", "b7");
	parse_joy(b7, key_map[7]);
	std::string left = cfg.get_config("joy::left", "a-4");
	parse_joy(left, key_map[8]);
	std::string right = cfg.get_config("joy::right", "a+4");
	parse_joy(right, key_map[9]);
	std::string up = cfg.get_config("joy::up", "a+5");
	parse_joy(up, key_map[10]);
	std::string down = cfg.get_config("joy::down", "a-5");
	parse_joy(down, key_map[11]);
}

void event_handler::parse_joy(std::string &s, key_map_entry &e) {
	switch (s[0]) {
	case 'b':
		e.type = 1;
		e.num = atoi(s.c_str() + 1);
		break;
	case 'a':
		e.type = 2;
		e.num = atoi(s.c_str() + 2);
		switch (s[1]) {
		case '+':
			e.dir = 1;
			break;
		case '-':
			e.dir = -1;
			break;
		}
		break;
	case 'k':
		e.type = 3;
		e.num = atoi(s.c_str() + 1);
		break;
	}
}

bool event_handler::detect_press(SDL_Event const &ev, key_map_entry &m) {
	switch (m.type) {
	case 1:
		if (SDL_JOYBUTTONDOWN == ev.type) {
			if (ev.button.button == m.num)
				return 1;
			else
				return 0;
		} else
			return 0;
		break;
	case 2:
		if (SDL_JOYAXISMOTION == ev.type) {
			if (ev.jaxis.axis == m.num) {
				if ((m.dir == 1 && ev.jaxis.value > 16000)) {
					if (!(axis_positive_press & (0x01 << m.num)))
						return 1;
					else
						return 0;
				} else if (m.dir == -1 && ev.jaxis.value < -16000) {
					if (!(axis_negative_press & (0x01 << m.num)))
						return 1;
					else
						return 0;
				} else
					return 0;
			} else
				return 0;
		} else
			return 0;
		break;
	case 3:
		if (SDL_KEYDOWN == ev.type) {
			if (m.num == ev.key.keysym.sym) {
				return 1;
			}
			return 0;
		}
		break;
	}
	return 0;
}

bool event_handler::detect_release(SDL_Event const &ev, key_map_entry &m) {
	switch (m.type) {
	case 1:
		if (SDL_JOYBUTTONUP == ev.type) {
			if (ev.button.button == m.num)
				return 1;
			else
				return 0;
		} else
			return 0;
		break;
	case 2:
		if (SDL_JOYAXISMOTION == ev.type) {
			if (ev.jaxis.axis == m.num) {
				if ((m.dir == 1 && ev.jaxis.value < 16000)) {
					if ((axis_positive_press & (0x01 << m.num)))
						return 1;
					else
						return 0;
				} else if (m.dir == -1 && ev.jaxis.value > -16000) {
					if ((axis_negative_press & (0x01 << m.num)))
						return 1;
					else
						return 0;
				} else
					return 0;
			} else
				return 0;
		} else
			return 0;
		break;
		break;
	case 3:
		if (SDL_KEYUP == ev.type) {
			if (m.num == ev.key.keysym.sym) {
				return 1;
			}
			return 0;
		}
		break;
	}
	return 0;

}
