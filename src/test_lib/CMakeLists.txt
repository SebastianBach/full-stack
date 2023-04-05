add_executable(lib_test)

target_sources(lib_test PRIVATE tests.cpp)
target_link_libraries(lib_test PRIVATE text_conversion_lib)

add_test(NAME lib_test COMMAND lib_test)

set_target_properties(lib_test PROPERTIES FOLDER "static_lib")

if (WIN32)
    target_compile_options(lib_test PRIVATE "/Zc:__cplusplus")
endif()
