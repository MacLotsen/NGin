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
#include <ngin/model.h>
#include "init.h"
#include "registry.h"
#include "ini_parser.h"

using namespace NGin;
using namespace std;

Registry::Register<Model::Object3D> Registry::objects;

void initObjects() {
    //TODO specify which objects to load
    ini_map_t result = parse_ini("games/preview/objects.ini");
    for (auto kv : result) {
        map<string, string> properties = kv.second;
        Model::Object3D* obj = new Model::Object3D();
        //TODO load if unloaded
        obj->mesh = Registry::meshes.records[properties["mesh"]].value;
        obj->material = {
                parseVec(properties["ambient"]),
                parseVec(properties["diffuse"]),
                parseVec(properties["specular"]),
                stof(properties["power"])
        };
        obj->position = parseVec(properties["position"]);
        obj->scale = parseVec(properties["scale"]);
        obj->orientation = parseQuat(properties["orientation"]);
        Registry::Register<Model::Object3D>::Record r;
        r.value = obj;
        Registry::objects.records[kv.first] = r;
    }
}
