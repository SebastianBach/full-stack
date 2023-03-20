cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(text_conversion CONFIG REQUIRED)

add_executable(test test.cpp)
target_link_libraries(test text_conversion::text_conversion)

