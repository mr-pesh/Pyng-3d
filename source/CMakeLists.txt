# Try to find and use OpenMP to for parallel calculations
find_package(OpenMP)

if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

if(USE_GL_MATH)
    # Embed glm into the project
    configure_file(include-glm.cmake.in glm/CMakeLists.txt)
    # Defines 'glm' target
    add_subdirectory(${CMAKE_SOURCE_DIR}/glm ${CMAKE_BINARY_DIR}/glm EXCLUDE_FROM_ALL)
endif()
