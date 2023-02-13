add_executable(compile_tests)

target_sources(compile_tests PRIVATE tests.cpp test_utilities.h)

target_link_libraries(compile_tests PRIVATE my_func)
target_include_directories(compile_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(compile_tests PROPERTIES FOLDER "tests")
