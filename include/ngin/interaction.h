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

#include "./model.h"

namespace NGin {

	namespace ObjectAction {

		void (*action_func) (Model::Object3D&, float);

		/* BASIC OBJECT FUNCTIONS */
		void pitch		(Model::Object3D&, float);
		void yaw			(Model::Object3D&, float);
		void roll			(Model::Object3D&, float);
		void forward	(Model::Object3D&, float);
		void backward	(Model::Object3D&, float);
		void left			(Model::Object3D&, float);
		void right		(Model::Object3D&, float);
		void up				(Model::Object3D&, float);
		void down			(Model::Object3D&, float);
	}

}
