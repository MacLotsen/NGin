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

#include "default_values.h"

using namespace NGin;
using namespace std;

ShaderProgram* shader_program;

Camera camera = defaults::camera;

Mesh cone, cube, star, plane, pyramid;
glm::vec3 lightPosition(0, 1, -4);

void construct_shader();
void construct_meshes();

void update(int delta) {
    updateCamera(camera);

    glutPostRedisplay();
    glutTimerFunc(20, update, delta+1);
};

void resize (int w, int h) {
    camera.viewWidth = w;
    camera.viewHeight = h;
    glm::mat4 projection = getProjectionMatrix(camera);
    glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void draw () {
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    //glClearBufferfv(GL_COLOR, 0, value_ptr(defaults::color_black));
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program->program);

    glm::mat4 view = getViewMatrix(camera);
    glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 trans;

    if (length2(camera.dist) > 1.0f) {
        trans = translate(camera.pos);
        glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
        setMaterial(defaults::solidRed, shader_program->program);
        render(pyramid);
    }

    trans = glm::translate(glm::vec3(-4.0f,0,4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
    setMaterial(defaults::solidRed, shader_program->program);
    render(cube);

    trans = glm::translate(glm::vec3(4.0f,0,4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "model"), 1, GL_FALSE, value_ptr(trans));
    setMaterial(defaults::softBlue, shader_program->program);
    render(pyramid);

    trans = glm::translate(glm::vec3(-4.0f,0,-4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "model"), 1, GL_FALSE, value_ptr(trans));
    setMaterial(defaults::solidGreen, shader_program->program);
    render(pyramid);

    trans = glm::translate(glm::vec3(4.0f,0,-4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "model"), 1, GL_FALSE, value_ptr(trans));
    setMaterial(defaults::softOrange, shader_program->program);
    render(cube);

    glutSwapBuffers();
}

void keyPress(unsigned char key, int, int) {
    keyPress(key);
}

void mouseMove(int x, int y) {
    mouseMove(x, y, camera);
    glutPostRedisplay();
}

void special_key(int i, int x, int y) {
    switch(i) {
    }
}

int main (int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Some program...");

    glutReshapeFunc(resize);
    glutDisplayFunc(draw);
    glutIgnoreKeyRepeat(1);
    glutTimerFunc(200, update, 0);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyPress);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutSpecialFunc(special_key);

    glewInit();

    construct_shader();
    construct_meshes();
    glm::mat4 projection = getProjectionMatrix(camera);
    glUseProgram(shader_program->program);
    glUniformMatrix4fv(glGetUniformLocation(shader_program->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(glGetUniformLocation(shader_program->program, "light"), 1, value_ptr(lightPosition));

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

void construct_shader() {
    shader_program = setupShaderProgram("shaders/shader.vert", "shaders/shader.frag");
}

void construct_meshes() {
    //TODO make it pointer values
    cone = *meshFromFile("objects/cone.obj", shader_program->program);
    cube = *meshFromFile("objects/cube.obj", shader_program->program);
    star = *meshFromFile("objects/star.obj", shader_program->program);
    plane = *meshFromFile("objects/plane.obj", shader_program->program);
    pyramid = *meshFromFile("objects/pyramid.obj", shader_program->program);
}
