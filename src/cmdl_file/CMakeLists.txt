add_executable(cmdl_file)

target_sources(cmdl_file PRIVATE cmdl_file.cpp)
set_target_properties(cmdl_file PROPERTIES OUTPUT_NAME "title_case_files") 
target_link_libraries(cmdl_file PRIVATE text_conversion_header_lib)
target_include_directories(cmdl_file PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# testing

set(SOURCE_FILE ${PROJECT_SOURCE_DIR}/src/test_cmdl_file/source.txt)
set(OUTPUT_FILE ${PROJECT_SOURCE_DIR}/src/test_cmdl_file/dst.txt)
set(REFERENCE_FILE ${PROJECT_SOURCE_DIR}/src/test_cmdl_file/ref.txt)

add_test(NAME cmdl_file COMMAND cmdl_file ${SOURCE_FILE} ${OUTPUT_FILE})

add_test(NAME test_file_compare COMMAND ${CMAKE_COMMAND}
    -DOUTPUT_FILE=${OUTPUT_FILE}
    -DREFERENCE_FILE=${REFERENCE_FILE}
    -P ${PROJECT_SOURCE_DIR}/src/test_cmdl_file/compare.cmake
)


add_test(NAME cmdl_file_no_args COMMAND cmdl_file)
set_tests_properties(cmdl_file_no_args PROPERTIES WILL_FAIL TRUE)

add_test(NAME cmdl_file_invalid_arg COMMAND cmdl_file "__invalid_file.txt")
set_tests_properties(cmdl_file_invalid_arg PROPERTIES WILL_FAIL TRUE)

# etc

install(TARGETS cmdl_file RUNTIME DESTINATION product/tools)

set_target_properties(cmdl_file PROPERTIES FOLDER "tools")
