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

#include <fstream>
#include "data_file.h"

data_file::data_file(std::string const &s) : objs() {
//	FlexLexer * lexer;
//	std::ifstream fin;
//	fin.open(s.c_str());
//	lexer = new yyFlexLexer(&fin, &std::cout);
//
//	std::list<son::value *> * l_tmp = new std::list<son::value *>;
//	son::value * v_tmp = 0;
//
//	int end = 0;
//
//	while(!end) {
//		switch(lexer->yylex()) {
//		case data::END:
//			end = 1;
//			break;
//		case data::BINARY:
//			std::cout << "Parse binary : " << lexer->YYText() << std::endl;
//			v_tmp = new son::v_binary(lexer->YYText());
//			break;
//		case data::FLOAT:
//			std::cout << "Parse float : " << lexer->YYText() << std::endl;
//			v_tmp = new son::v_double(lexer->YYText());
//			break;
//		case data::INTEGER:
//			std::cout << "Parse integer : " << lexer->YYText() << std::endl;
//			v_tmp = new son::v_int(lexer->YYText());
//			break;
//		case data::STRING:
//			std::cout << "Parse string : " << lexer->YYText() << std::endl;
//			v_tmp = new son::v_string(lexer->YYText());
//			break;
//		case data::NEXTITEM:
//			std::cout << "Goto next item" << std::endl;
//			l_tmp->push_back(v_tmp);
//			break;
//		case data::NEWOBJ:
//			std::cout << "Goto next obj" << std::endl;
//			l_tmp->push_back(v_tmp);
//			objs.push_back(l_tmp);
//			l_tmp = new std::list<son::value *>;
//			break;
//		default:
//			break;
//		}
//	}
//
//	delete lexer;
//	fin.close();
}

data_file::~data_file() {
	// TODO Auto-generated destructor stub
}

void data_file::print(std::ostream & out) {
	std::list<std::list<son::value *> *>::iterator iter = objs.begin();
	while(iter != objs.end()) {
		std::list<son::value *> * l = *iter;
		std::list<son::value *>::iterator jter = l->begin();
		for(;;) {
			out << (*jter)->serialize();
			jter++;
			if(jter == l->end())
				break;
			out << ",";
		}
		out << ";" << std::endl;
		iter++;
	}
}
