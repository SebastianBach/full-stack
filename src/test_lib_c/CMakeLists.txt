add_executable(test_lib_c)

target_sources(test_lib_c PRIVATE test.cpp)
target_link_libraries(test_lib_c PRIVATE lib_c)

add_test(NAME test_lib_c_test COMMAND test_lib_c)

set_target_properties(test_lib_c PROPERTIES FOLDER "static_libs")

if (WIN32)
    target_compile_options(test_lib_c PRIVATE "/Zc:__cplusplus")
endif()
