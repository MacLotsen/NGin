cmake_minimum_required(VERSION 2.8)
project(NGin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

# export with UNIX dir structure
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GTest)

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

include_directories(${GTEST_INCLUDE_DIRS})

set(ENGINE_SRC
        src/engine.cpp
        src/shader.cpp
        src/controls.cpp
        src/mesh.cpp
        src/material.cpp
        src/object3d.cpp
        src/window.cpp
        src/camera.cpp
        src/keyboard.cpp src/ini_parser.cpp)

set(ENGINE_TESTS
        test/main.cpp
        test/ini_test.cpp)

include_directories(include)

add_library(ngin ${ENGINE_SRC})
add_executable(ngin_preview src/main.cpp)

target_link_libraries(ngin ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
target_link_libraries(ngin_preview ngin)

if (GTEST_FOUND)
    enable_testing()
    add_executable(tests ${ENGINE_TESTS})
    target_link_libraries(tests ${GTEST_LIBRARIES} ngin)
    add_test(NAME tests COMMAND bin/tests)
endif (GTEST_FOUND)

install(DIRECTORY include DESTINATION .)
install(DIRECTORY share DESTINATION .)
install(DIRECTORY games DESTINATION .)
install(TARGETS ngin ngin_preview
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
