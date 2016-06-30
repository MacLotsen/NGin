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

    extern Register<NGin::Model::Mesh>       meshes;
    extern Register<NGin::Model::Object3D>   objects;

    extern std::map<NGin::IO::KeyEvent*, NGin::IO::output_f> key_registry;
    extern std::map<NGin::IO::KeyEvent*, std::pair<NGin::IO::MouseEvent, NGin::IO::output_f>> mouse_registry;

}

#endif //NGIN_REGISTRY_H
