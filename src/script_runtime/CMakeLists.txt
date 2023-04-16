add_executable(script_runtime)

target_sources(script_runtime PRIVATE runtime.cpp)
target_link_libraries(script_runtime PRIVATE script_lib)
set_target_properties(script_runtime PROPERTIES OUTPUT_NAME "runtime") 

install(TARGETS script_runtime RUNTIME DESTINATION product/script)

set_target_properties(script_runtime PROPERTIES FOLDER "script")

set(SOURCE_FILE ${CMAKE_INSTALL_PREFIX}/script_compiler/bytecode.code)
add_test(NAME script_runtime COMMAND script_runtime ${SOURCE_FILE})


set(SOURCE_FILE_EMPTY ${PROJECT_SOURCE_DIR}/src/script_resources/empty.code)
add_test(NAME script_runtime_empty COMMAND script_runtime ${SOURCE_FILE_EMPTY})
set_tests_properties(script_runtime_empty PROPERTIES WILL_FAIL TRUE)

set(SOURCE_FILE_BAD ${PROJECT_SOURCE_DIR}/src/script_resources/bad.code)
add_test(NAME script_runtime_bad COMMAND script_runtime ${SOURCE_FILE_BAD})
set_tests_properties(script_runtime_bad PROPERTIES WILL_FAIL TRUE)
