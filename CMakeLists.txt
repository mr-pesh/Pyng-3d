cmake_minimum_required(VERSION 3.6.0)

project(Pyng VERSION 0.0.0.1 LANGUAGES CXX)
# Activating C++17
set(CMAKE_CXX_STANDARD 17)

set(HEADERS matrix3d.h vector3d.h matrix_base.h vector_base.h property.h)
set(SOURCES main.cpp)

add_executable(Pyng ${HEADERS} ${SOURCES})
