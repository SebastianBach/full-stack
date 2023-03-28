add_executable(script_test)

target_sources(script_test PRIVATE test.cpp)
target_link_libraries(script_test PRIVATE script_lib)

add_test(NAME script_test COMMAND script_test)

set_target_properties(script_test PROPERTIES FOLDER "script")
