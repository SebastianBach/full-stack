cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(full_stack)
enable_testing()

message(${CMAKE_SYSTEM_NAME})

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wpedantic -Wconversion)
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/lib)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

add_subdirectory(src)
