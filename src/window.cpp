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

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ngin/window.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include "init.h"
#include "registry.h"
#include "ini_parser.h"


using namespace std;
using namespace NGin;

UI::Window Registry::window;
UI::Perspective Registry::perspective;

void parse_config() {
	ini_map_t raw = parse_ini("games/preview/config.ini");

	Registry::window.title = raw["WINDOW"]["title"];

	bool passedX;
	string w, h;
	for (auto c : raw["WINDOW"]["resolution"]) {
		if (c == 'x') {
			passedX = true;
			continue;
		}
		if (passedX)
			h += c;
		else
			w += c;
	}

	Registry::window.resolution = pair<int, int>(stoi(w), stoi(h));
	Registry::window.fullscreen = raw["WINDOW"]["fullscreen"] != "0";

	Registry::perspective.angle = stof(raw["VIEW"]["angle"]);
	Registry::perspective.far_plane = stof(raw["VIEW"]["far_plane"]);
	Registry::perspective.near_plane = stof(raw["VIEW"]["near_plane"]);
}

const glm::mat4 create_projection() {
	return glm::perspectiveFov(
			Registry::perspective.angle,
			(float) Registry::window.resolution.first,
			(float) Registry::window.resolution.second,
			Registry::perspective.near_plane,
			Registry::perspective.far_plane
			);
}

void window_resize(int w, int h) {
	Registry::window.resolution = pair<int, int>(w, h);

	const glm::mat4 proj = create_projection();
	//TODO for each shader
	glUniformMatrix4fv(glGetUniformLocation(Util::getShader(NGIN_SHADER_OBJECT_SHADER).program, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	glViewport(0, 0, w, h);
}

void initWindow() {
	parse_config();
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Registry::window.resolution.first, Registry::window.resolution.second);
	glutCreateWindow(Registry::window.title.c_str());
	if (Registry::window.fullscreen) {
		glutFullScreen();
	}
	glutReshapeFunc(window_resize);
}
