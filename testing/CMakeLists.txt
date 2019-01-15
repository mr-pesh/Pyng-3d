enable_testing()

function(create_test TEST_DIR DEPENDENCIES)
    set(TEST_NAME "${TEST_DIR}Test")
    aux_source_directory(${TEST_DIR} TEST_SRC)

    add_executable(${TEST_NAME} ${TEST_SRC})

    if(NOT USE_GL_MATH)
        target_link_libraries(${TEST_NAME} ${DEPENDENCIES})
    else()
        target_link_libraries(${TEST_NAME} ${DEPENDENCIES} glm)
    endif()

    target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/source)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction(create_test)

# Build-in GoogleTest to the project
configure_file(include-googletest.cmake.in googletest/CMakeLists.txt)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Defines 'gtest' and 'gtest_main' targets
add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/googletest ${CMAKE_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)

list_subdirectories(TESTING_DIRECTORIES ${CMAKE_SOURCE_DIR}/testing)

set(COMMON_TEST_DEPENDENCIES gtest gtest_main)

foreach(TEST_DIR ${TESTING_DIRECTORIES})
    create_test(${TEST_DIR} ${COMMON_TEST_DEPENDENCIES})
endforeach()
