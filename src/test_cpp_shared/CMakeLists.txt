add_executable(cpp_shared_test)

target_sources(cpp_shared_test PRIVATE test.cpp)
target_link_libraries(cpp_shared_test PRIVATE cpp_shared)

add_test(NAME cpp_shared_test COMMAND cpp_shared_test)

set_target_properties(cpp_shared_test PROPERTIES FOLDER "cpp shared")
