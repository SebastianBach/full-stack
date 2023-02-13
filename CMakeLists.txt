cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


option(ADD_PYTHON_MODULE "Include the Python Module" OFF)

project(full_stack)
enable_testing()


if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("build for linux")
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wpedantic -Wconversion)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/product/lib)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

add_subdirectory(src)
