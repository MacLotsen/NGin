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

#ifndef NGIN_REGISTRY_H
#define NGIN_REGISTRY_H

#include <ngin/ngin.h>
#include <ngin/window.h>
#include <ngin/model.h>
#include <ngin/io.h>
#include <map>
#include <tuple>

namespace Registry {

	template<typename T>
		struct Register {

			typedef struct {
				std::string path;
				T* value = nullptr;
			} Record;
			std::map<std::string, Record> records;
		};

	extern NGin::UI::Window window;
	extern NGin::UI::Perspective perspective;

	extern Register<NGin::Model::Mesh>       meshes;
	extern Register<NGin::Model::Object3D>   objects;

	extern std::map<NGin::IO::KeyEvent*, NGin::IO::output_f> key_registry;
	extern std::map<NGin::IO::KeyEvent*, std::pair<NGin::IO::MouseEvent, NGin::IO::output_f>> mouse_registry;

}

#endif //NGIN_REGISTRY_H
