cmake_minimum_required(VERSION 3.15)
project(sorted_vector)

set(CMAKE_CXX_STANDARD 17)

###############################
## Unit tests
###############################

set(TEST_EXECUTABLE sorted_vector_unit_tests)
enable_testing()

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.gtest googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
        )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build"
        )

target_include_directories(gmock_main SYSTEM BEFORE INTERFACE
        "$<BUILD_INTERFACE:${gtest_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${gmock_SOURCE_DIR}/include>")

add_executable(${TEST_EXECUTABLE}
        src/sorted_vector.h
        tests/sorted_vector_int_test.cpp
        tests/sorted_vector_unit_tests.cpp
        tests/sorted_vector_int_pair_test.cpp
        tests/sorted_vector_int_str_pair_test.cpp)

target_link_libraries(${TEST_EXECUTABLE} gtest_main)
target_link_libraries(${TEST_EXECUTABLE} gmock_main)


