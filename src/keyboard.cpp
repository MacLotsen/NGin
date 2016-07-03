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

#include <ngin/ngin.h>
#include <ngin/io.h>
#include "init.h"
#include "registry.h"
#include <GL/freeglut.h>

using namespace NGin::IO;

bool keyboard_state[256];
std::map<int, bool> special_keyboard_state;
std::map<KeyEvent*, output_f> Registry::key_registry;

void keyEvent(unsigned char key, int, int) {
    keyboard_state[key] = !keyboard_state[key];
}

void specialKeyEvent(int i, int, int) {
    special_keyboard_state[i] = !special_keyboard_state[i];
}

void initKeyboard() {
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyEvent);
    glutKeyboardUpFunc(keyEvent);
    glutSpecialFunc(specialKeyEvent);
    glutSpecialUpFunc(specialKeyEvent);
}
