cmake_minimum_required(VERSION 3.10.0)

# Set project name and version
project(Pyng VERSION 0.0.0.1 LANGUAGES CXX)

# Specify this flag to use OpenGL Mathematics SIMD-friendly types mapping
if (USE_GL_MATH)
    find_package(GLM)
        if(GLM_FOUND)
         # Set a preprocessor macro to use GLM implementation for mathematics
            add_definitions(-D__GL_MATH_LIBRARY)
            include_directories(${GLM_INCLUDE_DIRS})
	 endif()
endif()

# Specify this flag to use Microsoft AMP for parallel calculations
if(USE_CPP_AMP)
    add_definitions(-D__CPP_AMP_ACCELERATION)
endif()

# Try to find and use OpenMP to for parallel calculations
find_package(OpenMP)
    if(OPENMP_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()

find_package(GTest)

set(HEADERS ArrayView.h Matrix.h MatrixView.h Vector.h property.h)
set(SOURCES main.cpp)

add_executable(Pyng ${HEADERS} ${SOURCES})
set_property(TARGET Pyng PROPERTY CXX_STANDARD 17)
set_property(TARGET Pyng PROPERTY CXX_STANDART_REQUIRED ON)

add_executable(MatrixIterator MatrixIteratorUnitTest.cpp)
target_compile_features(MatrixIterator PRIVATE cxx_std_17)

add_executable(MatrixTest MatrixUnitTest.cpp)
target_compile_features(MatrixTest PRIVATE cxx_std_17)

gtest_add_tests(TARGET MatrixIterator)
gtest_add_tests(TARGET MatrixTest)
