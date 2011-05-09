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

#ifndef SON_VALUE_HPP_
#define SON_VALUE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace son {

enum type {
	INT, DOUBLE, BINARY, STRING
};

class value {
	type t;
public:
	class bad_type {
	};

	value() {
	}
	value(char const * s) { };
	virtual ~value() {
	}

	virtual std::string serialize() = 0;

	virtual operator int() const = 0;
	virtual operator double() const = 0;
	virtual operator std::string() const = 0;
	virtual operator std::vector<char>() const = 0;
};

class v_int: public value {
	int value_;
public:
	v_int(int i) {
		value_ = i;
	}
	v_int(char const * s) {
		std::istringstream iss(s);
		iss >> this->value_;
	};

	virtual std::string serialize() {
		std::ostringstream out;
		out << value_;
		return out.str();
	}

	virtual operator int() const {
		std::cout << "call int conversion" << std::endl;
		return value_;
	}
	virtual operator double() const {
		throw value::bad_type();
	}
	virtual operator std::string() const {
		throw std::exception();
	}
	virtual operator std::vector<char>() const {
		throw value::bad_type();
	}
};

class v_double: public value {
	double value_;
public:
	v_double(double i) {
		value_ = i;
	}

	v_double(char const * s) {
		std::istringstream iss(s);
		iss >> this->value_;
	};

	virtual std::string serialize() {
		std::ostringstream out;
		out << value_;
		return out.str();
	}
	virtual operator int() const {
		throw value::bad_type();
	}
	virtual operator double() const {
		std::cout << "call double conversion" << std::endl;
		return value_;
	}
	virtual operator std::string() const {
		throw value::bad_type();
	}
	virtual operator std::vector<char>() const {
		throw value::bad_type();
	}
};

class v_string: public value, public std::string {
public:
	v_string(std::string const & s) :
		std::string(s) {
	}

	v_string(char const * s) {
		std::string ss(s);
		this->assign(ss, 1, ss.length() - 2);
	};

	virtual std::string serialize() {
		// TODO: filter string
		std::string s(*this);
		std::ostringstream out;
		out << "\"" << s << "\"";
		return out.str();
	}
	virtual operator int() const {
		throw value::bad_type();
	}
	virtual operator double() const {
		throw value::bad_type();
	}
	virtual operator std::string() const {
		std::cout << "call string conversion" << std::endl;
		return *this;
	}
	virtual operator std::vector<char>() const {
		throw value::bad_type();
	}
};

static const char HEX_TABLE[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F' };

class v_binary: public value, public std::vector<char> {
public:
	v_binary(int i) :
		std::vector<char>(i) {
	}
	v_binary(char const * s) {
		std::string ss(s);
		std::string::iterator iter = ss.begin();
		iter += 2;
		this->clear();
		while(iter != ss.end()) {
			char c;
			char c_out = 0;
			c = *iter;
			switch (c) {
				case '0':
					c_out += 0x00;
					break;
				case '1':
					c_out += 0x10;
					break;
				case '2':
					c_out += 0x20;
					break;
				case '3':
					c_out += 0x30;
					break;
				case '4':
					c_out += 0x40;
					break;
				case '5':
					c_out += 0x50;
					break;
				case '6':
					c_out += 0x60;
					break;
				case '7':
					c_out += 0x70;
					break;
				case '8':
					c_out += 0x80;
					break;
				case '9':
					c_out += 0x90;
					break;
				case 'A':
				case 'a':
					c_out += 0xA0;
					break;
				case 'B':
				case 'b':
					c_out += 0xB0;
					break;
				case 'C':
				case 'c':
					c_out += 0xC0;
					break;
				case 'D':
				case 'd':
					c_out += 0xD0;
					break;
				case 'E':
				case 'e':
					c_out += 0xE0;
					break;
				case 'F':
				case 'f':
					c_out += 0xF0;
					break;
				default:
					throw bad_type();
					break;
			}

			iter++;
			c = *iter;
			switch (c) {
				case '0':
					c_out += 0x00;
					break;
				case '1':
					c_out += 0x01;
					break;
				case '2':
					c_out += 0x02;
					break;
				case '3':
					c_out += 0x03;
					break;
				case '4':
					c_out += 0x04;
					break;
				case '5':
					c_out += 0x05;
					break;
				case '6':
					c_out += 0x06;
					break;
				case '7':
					c_out += 0x07;
					break;
				case '8':
					c_out += 0x08;
					break;
				case '9':
					c_out += 0x09;
					break;
				case 'A':
				case 'a':
					c_out += 0x0A;
					break;
				case 'B':
				case 'b':
					c_out += 0x0B;
					break;
				case 'C':
				case 'c':
					c_out += 0x0C;
					break;
				case 'D':
				case 'd':
					c_out += 0x0D;
					break;
				case 'E':
				case 'e':
					c_out += 0x0E;
					break;
				case 'F':
				case 'f':
					c_out += 0x0F;
					break;
				default:
					throw bad_type();
					break;
			}
			iter++;
			this->push_back(c_out);
		}
	}

	virtual std::string serialize() {
		std::ostringstream out;
		out << "0x";
		std::vector<char>::iterator iter = this->begin();
		while(iter != this->end()) {
			char c = *iter;
			int a = (c >> 4) & 0x0F;
			int b = (c) & 0x0F;
			out << HEX_TABLE[a] << HEX_TABLE[b];
			iter++;
		}
		return out.str();
	}
	virtual operator int() const {
		throw value::bad_type();
	}
	virtual operator double() const {
		throw value::bad_type();
	}
	virtual operator std::string() const {
		throw value::bad_type();
	}
	virtual operator std::vector<char>() const {
		std::cout << "call vector conversion" << std::endl;
		return *this;
	}
};

}
#endif /* SON_VALUE_HPP_ */
