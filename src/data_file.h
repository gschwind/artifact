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

#ifndef DATA_FILE_HPP_
#define DATA_FILE_HPP_

#include <list>
#include <FlexLexer.h>
#include <string>
#include <iostream>
#include "data_value.h"

class data_file {
	std::list<std::list<son::value *> * > objs;

public:
	data_file(std::string const &s);
	virtual ~data_file();
	void print(std::ostream & out);
};

#endif /* DATA_FILE_HPP_ */
