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
#include <ngin/ngin.h>
#include <glm/ext.hpp>

#include "default_values.h"
#include "registry.h"
#include <iostream>

using namespace std;
using namespace NGin;

Camera camera = defaults::camera;

glm::vec3 lightPosition(0, 1, -6);

void update(int delta) {
	// TODO: reimplement controls
	updateCamera(camera);

	glutPostRedisplay();
	glutTimerFunc(20, update, delta + 1);
};

void resize(int w, int h) {
	const Util::ShaderProgram shader_program = Util::getShader(NGIN_SHADER_OBJECT_SHADER);
	camera.viewWidth = w;
	camera.viewHeight = h;
	glm::mat4 projection = getProjectionMatrix(camera);
	glUniformMatrix4fv(glGetUniformLocation(shader_program.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

void draw() {
	const Util::ShaderProgram& shader_program = Util::getShader(NGIN_SHADER_OBJECT_SHADER);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearBufferfv(GL_COLOR, 0, value_ptr(defaults::color_black));
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_program.program);

	glm::mat4 view = getViewMatrix(camera);
	glUniformMatrix4fv(glGetUniformLocation(shader_program.program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 trans;

	for (auto kv: Registry::objects.records) {
		Model::Object3D* object = kv.second.value;
		trans = translate(object->position);
		// TODO rotate and scale
		glUniformMatrix4fv(glGetUniformLocation(shader_program.program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
		setMaterial(object->material, shader_program.program);
		Model::render(*object->mesh);
	}

	glutSwapBuffers();
}

void keyPress(unsigned char key, int, int) {
	keyPress(key);
	for (auto record : Registry::key_registry) {
		if (record.first->key == key) {
			record.second();
		}
	}
}

void mouseMove(int x, int y) {
	mouseMove(x, y, camera);
	glutPostRedisplay();
}

void special_key(int i, int x, int y) {

}

int main(int argc, char** argv) {
	init(argc, argv, "preview");
	glutDisplayFunc(draw);
	glutTimerFunc(20, update, 0);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyPress);
	glutPassiveMotionFunc(mouseMove);
	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
	glutSpecialFunc(special_key);

	const Util::ShaderProgram& shader_program = Util::getShader(NGIN_SHADER_OBJECT_SHADER);

	glm::mat4 projection = getProjectionMatrix(camera);
	glUseProgram(shader_program.program);
	glUniformMatrix4fv(glGetUniformLocation(shader_program.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3fv(glGetUniformLocation(shader_program.program, "light"), 1, value_ptr(lightPosition));

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}
