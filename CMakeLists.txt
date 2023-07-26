cmake_minimum_required(VERSION 3.10)

project(jIMSRGpr VERSION 0.1.0 LANGUAGES CXX)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(JIMSRGPR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# External libraries
add_subdirectory(lib)

# jIMSRGprime library
add_subdirectory(jimsrgpr)

# Tests ...
include(CTest)
enable_testing()

# ... use Catch2 mostly ...
include(lib/Catch2/extras/Catch.cmake)

# # ... but sometimes GoogleTest ...
# include(GoogleTest)

# # Unit tests
# add_subdirectory(tests)
