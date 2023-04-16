add_executable(script_interpreter)

target_sources(script_interpreter PRIVATE interpreter.cpp)
target_link_libraries(script_interpreter PRIVATE script_lib)
set_target_properties(script_interpreter PROPERTIES OUTPUT_NAME "interpreter") 

install(TARGETS script_interpreter RUNTIME DESTINATION product/script)

set_target_properties(script_interpreter PROPERTIES FOLDER "script")


set(SOURCE_FILE ${PROJECT_SOURCE_DIR}/src/script_resources/script.txt)
add_test(NAME script_interpreter COMMAND script_interpreter ${SOURCE_FILE})

set(SOURCE_FILE_BAD ${PROJECT_SOURCE_DIR}/src/script_resources/bad.txt)
add_test(NAME script_interpreter_bad COMMAND script_interpreter ${SOURCE_FILE_BAD})
set_tests_properties(script_interpreter_bad PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_interpreter_no_args COMMAND script_interpreter)
set_tests_properties(script_interpreter_no_args PROPERTIES WILL_FAIL TRUE)
