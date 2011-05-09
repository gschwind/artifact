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

#include <SDL/SDL.h>
#include "config.h"
#include <iterator>

config::config(std::string &s) {
	int eof = 0;
	SDL_RWops * f = SDL_RWFromFile(s.c_str(), "r");
	while (!eof) {
		std::string a = readline(f);
		printf("{%s}\n", a.c_str());
		int e = a.find("eof", 0);
		if (e == 0) {
			eof = 1;
		} else {
			int begin, end;
			begin = a.find("[", 0);
			end = a.find("]", begin + 1);
			std::string key = a.substr(0, begin);
			std::string value = a.substr(begin + 1, end - begin - 1);
			printf("key: <%s> value: <%s>\n", key.c_str(), value.c_str());
			cfg[key] = value;
		}
	}
}

config::~config() {
	// TODO Auto-generated destructor stub
}

std::string config::readline(SDL_RWops * f) {
	std::string r("");
	char a;
	int endl = 0;
	while (!endl) {
		int i = SDL_RWread(f, &a, 1, 1);
		if (a == '\n' || i == -1) {
			endl = 1;
		} else {
			r += a;
		}
	}
	return r;
}

std::string config::get_config(std::string key, std::string dflt) const {
	std::map<std::string, std::string>::const_iterator iter = cfg.find(key);
	if (iter == cfg.end()) {
		return dflt;
	}
	return iter->second;
}
