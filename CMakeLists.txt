cmake_minimum_required(VERSION 3.6.0)

# Set project name and version
project(Pyng VERSION 0.0.0.1 LANGUAGES CXX)

# Activating C++17
set(CMAKE_CXX_STANDARD 17)

# Specify this flag to use Microsoft AMP for parallel calculations
if (USE_CPP_AMP)
    add_definitions(-D__CPP_AMP_ACCELERATION)
else()
# Try to find and use OpenMP to for parallel calculations
find_package(OpenMP)
    if (OPENMP_FOUND)
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
endif()

set(HEADERS Matrix3d.h Vector3d.h Matrix.h MatrixView.h property.h)
set(SOURCES main.cpp)

add_executable(Pyng ${HEADERS} ${SOURCES})
