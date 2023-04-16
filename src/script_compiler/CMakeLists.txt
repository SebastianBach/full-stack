add_executable(script_compiler)

target_sources(script_compiler PRIVATE compiler.cpp)

target_link_libraries(script_compiler PRIVATE script_lib)
target_include_directories(script_compiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(script_compiler PROPERTIES OUTPUT_NAME "compiler") 

install(TARGETS script_compiler RUNTIME DESTINATION product/script)

set_target_properties(script_compiler PROPERTIES FOLDER "script")


set(OUTPUT_FILE ${CMAKE_INSTALL_PREFIX}/script_compiler/bytecode.code)

set(SOURCE_FILE_BAD ${PROJECT_SOURCE_DIR}/src/script_resources/bad.txt)
add_test(NAME script_compiler_bad COMMAND script_compiler ${SOURCE_FILE_BAD} ${OUTPUT_FILE})
set_tests_properties(script_compiler_bad PROPERTIES WILL_FAIL TRUE)

set(SOURCE_FILE ${PROJECT_SOURCE_DIR}/src/script_resources/script.txt)
add_test(NAME script_compiler COMMAND script_compiler ${SOURCE_FILE} ${OUTPUT_FILE})

add_test(NAME script_compiler_no_args COMMAND script_compiler)
set_tests_properties(script_compiler_no_args PROPERTIES WILL_FAIL TRUE)

