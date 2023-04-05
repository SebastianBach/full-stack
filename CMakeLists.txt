cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(full_stack CXX)
enable_testing()


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("build with GCC")
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wpedantic -Wconversion -Werror)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/lib)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/lib/lib)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/lib/header)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/tools)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/app)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/python)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/script)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/dynamic_lib)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/firefox)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/wasm)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/script_compiler)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

add_subdirectory(src)
