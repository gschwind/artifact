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

#include <iostream>
#include <string>
#include "data_value.h"
#include "data_file.h"
using namespace std;

int main() {

	char const sa[] = "100";
	char const sb[] = "-1.5e+100";
	char const sc[] = "\"toto\"";
	char const sd[] = "0xC0FE000000AF00000300";
	son::v_int a(sa);
	son::v_double b(sb);
	son::v_string c(sc);
	son::v_binary d(sd);
	son::value * t = &b;
	cout << static_cast<int>(a) << " serialied " << a.serialize() << endl;
	cout << static_cast<double>(b) << " serialied " << b.serialize() << endl;
	cout << static_cast<std::string>(c) << " serialied " << c.serialize() << endl;
	cout << static_cast<double>(*t) << " serialied " << t->serialize() << endl;
	cout << " serialied " << d.serialize() << endl;
	data_file f("/home/gschwind/test_lex/test.i");

	f.print(cout);
	return 0;
}
