/*
 *  Modern OpenGL Game Engine C/C++
 *  Copyright (C) 2016  Erik Nijenhuis

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "ini_parser.h"

#define PARSING_GLOBAL  0
#define PARSING_SECTION 1
#define PARSING_KEY     2
#define PARSING_VALUE   3

using namespace std;

ini_map_t parse_ini(string path) {
	ini_map_t result;
	FILE* file = fopen(path.c_str(), "r");

	int character;

	char state = PARSING_GLOBAL;
	string section, key, value;
	map<string, string> key_values;

	while((character = fgetc(file)) != EOF) {
		switch((char) character) {
			case '[':
				if (state == PARSING_KEY) {
					result[section] = key_values;
					key_values = map<string, string>();
					section = "";
				}
				state = PARSING_SECTION;
				break;
			case ']':
				state = PARSING_KEY;
				break;
			case '=':
				state = PARSING_VALUE;
				break;
			case '\t':
				break;
			case ' ':
				if (state == PARSING_VALUE && value != "") {
					value += character;
				}
				break;
			case '\n':
				if (state == PARSING_VALUE) {
					key_values[key] = value;
					key = value = "";
					state = PARSING_KEY;
				}
				break;
			default:
				switch(state) {
					case PARSING_GLOBAL:
						section = "GLOBAL";
						key += character;
						break;
					case PARSING_SECTION:
						section += character;
						break;
					case PARSING_KEY:
						key += character;
						break;
					case PARSING_VALUE:
						value += character;
						break;
				}
				break;
		}
	}
	// append the last section (sections are added when a new section is found)
	if (key_values.size() > 0 && section != "") {
		result[section] = key_values;
	}
	return result;
}

glm::vec3 parseVec(std::string raw) {
	int i = 0;
	glm::vec3 result;
	std::string tmp;
	for (auto c : raw) {
		if (c == ' ') {
			result[i++] = stof(tmp);
			tmp = "";
		} else {
			tmp += c;
		}
	}
	// append the last element
	if (tmp != "") {
		result[i] = stof(tmp);
	}
	// if theres only one arg
	if (i == 0) {
		result = glm::vec3(stof(tmp));
	}
	return result;
}

glm::quat parseQuat(std::string raw) {
	int i = 0;
	glm::quat result;
	std::string tmp;
	for (auto c : raw) {
		if (c == ' ') {
			result[i++] = stof(tmp);
			tmp = "";
		} else {
			tmp += c;
		}
	}
	// append the last element
	if (tmp != "") {
		result[i] = stof(tmp);
	}
	return result;
}

ostream& operator<<(ostream& os, const ini_map_t& map) {
	for (auto kv : map) {
		os << "SECTION: " << kv.first << endl;
		for (auto kv2 : kv.second) {
			os << "KV: " << kv2.first << '=' << kv2.second << endl;
		}
		os << endl;
	}
	return os;
}
