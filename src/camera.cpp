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
#include <ngin/io.h>
#include <iostream>
#include "registry.h"

using namespace NGin::IO;

std::map<KeyEvent*, std::pair<MouseEvent, output_f>> Registry::mouse_registry;

void pitch() {

}

void yaw() {

}

void roll() {

}

//TODO move to keyboard

void forward() {
    std::cout << "FORWAAAARD!!" << std::endl;
}

void backward() {

}

void left() {

}

void right() {

}

void up() {

}

void down() {

}

void initCamera() {
    glutSetCursor(GLUT_CURSOR_NONE);
    KeyEvent* k = new KeyEvent;
    k->key = 'w';
    Registry::key_registry[k] = forward;
}
