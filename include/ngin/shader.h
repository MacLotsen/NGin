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

#ifndef NGIN_SHADER_H
#define NGIN_SHADER_H

#include <GL/glew.h>

#define NGIN_SHADER_OBJECT_SHADER 1

namespace NGin {

	/**
	 * Change type when using more than 8 shaders
	 */
	typedef unsigned char shader_flag_t;

	namespace Util {

		struct ShaderProgram {
			const shader_flag_t flag;
			GLuint program;
			GLuint vertex;
			GLuint fragment;

			ShaderProgram(shader_flag_t _flag) : flag(_flag) {}
		};

		const ShaderProgram& getShader(const shader_flag_t index);

	}

}

#endif //NGIN_SHADER_H
