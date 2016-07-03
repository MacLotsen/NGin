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

#include <gtest/gtest.h>
#include "../src/ini_parser.h"

TEST(IniParser, Sections) {
    ini_map_t result;
    ASSERT_NO_THROW(result = parse_ini("games/preview/config.ini"));
    std::cout << result << std::endl;
    ASSERT_TRUE(result["WINDOW"]["title"] != "");
}

TEST(IniParser, Global) {
    ini_map_t result;
    ASSERT_NO_THROW(result = parse_ini("games/preview/meshes.ini"));
    std::cout << result << std::endl;
    ASSERT_TRUE(result["GLOBAL"].size() > 0);
    ASSERT_TRUE(result["GLOBAL"]["cube"] != "");
}
