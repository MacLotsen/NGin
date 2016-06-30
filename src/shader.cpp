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

#include <ngin/shader.h>
#include <map>
#include "init.h"

using namespace NGin;

char* _read_shader(const char* path) {
    // Open the file
    FILE* fp = fopen(path, "r");
    // Move the file pointer to the end of the file and determining the length
    fseek(fp, 0, SEEK_END);
    long file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* source_buffer = new char[file_length + 1];
    // zero out memory
    for (int i = 0; i < file_length + 1; i++) {
        source_buffer[i] = 0;
    }
    // Here's the actual read
    fread(source_buffer, 1, file_length, fp);
    // This is how you denote the end of a string in C
    source_buffer[file_length + 1] = '\0';
    fclose(fp);
    return source_buffer;
}

bool _compiles(GLuint shader) {
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled) {
        return true;
    } else {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char* msgBuffer = new char[logLength];
        glGetShaderInfoLog(shader, logLength, NULL, msgBuffer);
        printf("%s\n", msgBuffer);
        delete (msgBuffer);
        return false;
    }
}

GLuint _create_shader(std::string path, GLuint type) {
    char* source = _read_shader(path.c_str());
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, (const GLchar**)&source, NULL);
    glCompileShader(id);
    if (_compiles(id))
        return id;
    return GLuint(-1);
}

void _bind_program(Util::ShaderProgram* p) {
    glAttachShader(p->program, p->vertex);
    glAttachShader(p->program, p->fragment);
    glLinkProgram(p->program);
}

struct shader_pair_t {
    std::string vert;
    std::string frag;
};

std::map<const shader_flag_t, Util::ShaderProgram*> _shaders;

/*
 * don't forget to add a handle in shader.h
 */
const struct shader_pair_t _shader_paths[] = {
        {"share/ngin/shaders/shader.vert", "share/ngin/shaders/shader.frag"}
};

shader_flag_t _shader_flag_index = 0;
const shader_flag_t _begin = 1;

Util::ShaderProgram* _setupShaderProgram(std::string vert, std::string frag) {
    _shader_flag_index = _begin << _shader_flag_index;
    Util::ShaderProgram* prog = new Util::ShaderProgram(_shader_flag_index);
    _shaders[_shader_flag_index] = prog;

    prog->program = glCreateProgram();
    prog->vertex = _create_shader(vert, GL_VERTEX_SHADER);
    prog->fragment = _create_shader(frag, GL_FRAGMENT_SHADER);

    _bind_program(prog);

    return prog;
}

const Util::ShaderProgram& Util::getShader(const shader_flag_t index) {
    return *(_shaders[index]);
}

void initShaders() {
    for (auto paths : _shader_paths) {
        _setupShaderProgram(paths.vert, paths.frag);
    }
}
