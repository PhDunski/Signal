cmake_minimum_required(VERSION 3.0)

project(cmake_test)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Catch2//single_include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
option(BUILD_TESTS "Should we build unit tests?" yes)
