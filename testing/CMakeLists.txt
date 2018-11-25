enable_testing()

macro(list_subdirectories result_list current_dir)
    file(GLOB children RELATIVE ${current_dir} ${current_dir}/*)
    set(dir_list "")
    foreach(child ${children})
        if(IS_DIRECTORY ${current_dir}/${child})
            list(APPEND dir_list ${child})
        endif()
    endforeach()
    set(${result_list} ${dir_list})
endmacro()

function(create_test TEST_DIR)
    set(TEST_NAME "${TEST_DIR}Test")
    aux_source_directory(${TEST_DIR} TEST_SRC)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} gtest gtest_main)
    target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction(create_test)

# Build-in GoogleTest to the project
configure_file(CMakeLists.txt.in googletest/CMakeLists.txt)

execute_process(
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest"
)

if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest"
)

if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL
)

include_directories("${CMAKE_SOURCE_DIR}/source")

list_subdirectories(TESTING_DIRECTORIES "${CMAKE_SOURCE_DIR}/testing")

foreach(TEST_DIR ${TESTING_DIRECTORIES})
    create_test(${TEST_DIR})
endforeach()
