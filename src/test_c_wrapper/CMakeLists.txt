add_executable(c_wrapper_test)

target_sources(c_wrapper_test PRIVATE test.cpp)
target_link_libraries(c_wrapper_test PRIVATE c_wrapper)

add_test(NAME c_wrapper_test COMMAND c_wrapper_test)

set_target_properties(c_wrapper_test PROPERTIES FOLDER "rust")

if (WIN32)
    target_compile_options(c_wrapper_test PRIVATE "/Zc:__cplusplus")
endif()
