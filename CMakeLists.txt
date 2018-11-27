cmake_minimum_required(VERSION 3.1.3)

# Set project name and version
project(Pyng VERSION 0.0.0.1 LANGUAGES CXX)

# Disable RTTI
if(MSVC)
    set(DISABLE_RTTI_FLAG "/GR-")
else()
    set(DISABLE_RTTI_FLAG "-fno-rtti")
endif()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${DISABLE_RTTI_FLAG}")


# Check if DirectX backend selected to be used for graphics acceleration
if(WIN32)
    option(USE_DX_MATH "Use DirectX backend for hardware acceleration (Recommended)" OFF)

    if (USE_DX_MATH)
        add_definitions(-D__DX_MATH_LIBRARY)
    endif()
    # Available only for DirectX implementations
    option(USE_CPP_AMP "Use Microsoft's C++ Accelerated Massive Parallelism library for Pyng utilities components" OFF)

    if(USE_CPP_AMP)
        add_definitions(-D__CPP_AMP_ACCELERATION)
    endif()

endif()


# Check if OpenGL backend selected to be used for graphics acceleration
option(USE_GL_MATH "Use OpenGL backend for hardware acceleration (Recommended)" ON)

if(USE_GL_MATH)
    find_package(GLM)
        if(GLM_FOUND)
            add_definitions(-D__GL_MATH_LIBRARY)
            include_directories(${GLM_INCLUDE_DIRS})
	 endif()
endif()


# Try to find and use OpenMP to for parallel calculations
find_package(OpenMP)
    if(OPENMP_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()


# Check if building unit tests required
option(BUILD_TESTS "Include unit tests to build scenario" ON)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(testing)
endif()
