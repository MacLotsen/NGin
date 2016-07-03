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

#ifndef NGIN_INI_PARSER_H
#define NGIN_INI_PARSER_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <string>
#include <map>

typedef std::map<std::string, std::map<std::string, std::string>> ini_map_t;

ini_map_t parse_ini(std::string);

glm::vec3 parseVec(std::string);
glm::quat parseQuat(std::string);

std::ostream& operator << (std::ostream& os, const ini_map_t& map);

#endif //NGIN_INI_PARSER_H
