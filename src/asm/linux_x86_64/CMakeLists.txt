
message(STATUS "Add Linux x86_64 Assembly Tool")

add_custom_target(asm_program ALL 

        COMMAND bash -c "echo 'build Assembly tool'; \
                        ../build_and_run.sh 'tool.s' 'title_case' '$<TARGET_FILE:lib_c>' '${CMAKE_BUILD_TYPE}' '${CMAKE_BINARY_DIR}/temp/asm'" 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        VERBATIM)

add_dependencies(asm_program lib_c)


add_test(asm_test "${CMAKE_BINARY_DIR}/temp/asm/title_case" "this is some headline")

add_test(asm_test_failure_no_args "${CMAKE_BINARY_DIR}/temp/asm/title_case")
set_tests_properties(asm_test_failure_no_args PROPERTIES WILL_FAIL TRUE)

add_test(asm_test_failure_empty_arg "${CMAKE_BINARY_DIR}/temp/asm/title_case" "")
set_tests_properties(asm_test_failure_empty_arg PROPERTIES WILL_FAIL TRUE)

install(CODE " file(INSTALL \"${CMAKE_BINARY_DIR}/temp/asm/title_case\" DESTINATION \"${CMAKE_INSTALL_PREFIX}/product/asm\")" )
