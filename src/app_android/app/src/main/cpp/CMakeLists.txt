cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("titlecase")

add_library(${CMAKE_PROJECT_NAME} SHARED native-lib.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ../../../../../header)

target_link_libraries(${CMAKE_PROJECT_NAME} android log)
