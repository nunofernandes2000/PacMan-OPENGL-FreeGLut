cmake_minimum_required(VERSION 3.30)
project(pacman C)

set(CMAKE_C_STANDARD 11)

#[[include_directories(.)]]

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(/opt/homebrew/include)

add_executable(pacman
    colorcube.c
    pm-maps.c
    pm-maps.h)

target_link_libraries(pacman OpenGL::GL GLUT::GLUT)
