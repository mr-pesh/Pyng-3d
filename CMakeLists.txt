cmake_minimum_required(VERSION 3.1.3)

# Set project name and version
project(Pyng VERSION 0.0.1 LANGUAGES CXX)

# Disable RTTI and exceptions
if(MSVC)
    string(REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

if(WIN32)
    # Check to select OpenGL backend for graphics acceleration
    option(USE_GL_MATH "Use OpenGL backend for hardware acceleration" OFF)
    # Check to select DirectX backend for graphics acceleration
    option(USE_DX_MATH "Use DirectX backend for hardware acceleration (Recommended)" ON)

    if(USE_DX_MATH)
        add_definitions(-D__DX_MATH_LIBRARY)
    endif()
    # Available only for DirectX implementations
    option(USE_CPP_AMP "Use Microsoft's C++ Accelerated Massive Parallelism library for Pyng utilities components" OFF)

    if(USE_CPP_AMP)
        add_definitions(-D__CPP_AMP_ACCELERATION)
    endif()
else()
    option(USE_GL_MATH "Use OpenGL backend for hardware acceleration (Recommended)" ON)
endif()

if(USE_GL_MATH)
    add_definitions(-D__GL_MATH_LIBRARY)
    # Enable GLM-GTX extensions
    add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
    # TODO: set this option to OFF by default
    option(GLM_FORCE_PURE "Disable the use of SIMD optimizations based on compiler intrinsics" ON)

    if (GLM_FORCE_PURE)
        add_definitions(-DGLM_FORCE_PURE)
    endif()
endif()

# Check to enable unit tests
option(BUILD_TESTS "Include unit tests to build scenario" ON)

include(cmake/FrameworkConfig.cmake)

add_subdirectory(source)

if(BUILD_TESTS)
    enable_testing()
    add_definitions(-DPYNG_ENABLE_TESTING)
    add_subdirectory(testing)
endif()
