cmake_minimum_required(VERSION 3.0)

enable_testing()

project(title_case)

set(CMAKE_CXX_STANDARD 11)

include_directories(../header)
link_directories(../lib)

add_executable(title_case example.cpp)
target_link_libraries(title_case text_conversion)

add_test(NAME title_case COMMAND title_case)
