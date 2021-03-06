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

#ifndef NGIN_WINDOW_H
#define NGIN_WINDOW_H

#include <string>
#include <tuple>

namespace NGin {

	namespace UI {

		struct Perspective {
			float angle;
			float near_plane;
			float far_plane;
		};

		struct Window {
			std::string title;
			std::pair<int, int> resolution;
			bool fullscreen;
		};
	}

}

#endif //NGIN_WINDOW_H
