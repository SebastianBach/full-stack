
message(STATUS "Add Linux x86_64 Assembly Tool")

enable_language(ASM)

add_executable(asm_program tool.s)
set_target_properties(asm_program PROPERTIES LINK_FLAGS "-nostartfiles")
set_target_properties(asm_program PROPERTIES OUTPUT_NAME "title_case") 
target_link_libraries(asm_program PRIVATE lib_c)


add_test(NAME asm_test COMMAND asm_program "this is the headline")

add_test(NAME asm_test_failure_no_args COMMAND asm_program)
set_tests_properties(asm_test_failure_no_args PROPERTIES WILL_FAIL TRUE)

add_test(NAME asm_test_failure_empty_arg COMMAND asm_program "")
set_tests_properties(asm_test_failure_empty_arg PROPERTIES WILL_FAIL TRUE)

install(TARGETS asm_program RUNTIME DESTINATION product/asm)
