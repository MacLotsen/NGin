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
                if (state == PARSING_VALUE) {
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
                        section = "global";
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
