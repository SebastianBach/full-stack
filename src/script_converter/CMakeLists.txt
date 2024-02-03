add_executable(script_converter)

target_sources(script_converter PRIVATE main.cpp 
                                        converter.cpp)

target_include_directories(script_converter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(script_converter PRIVATE script_lib)
set_target_properties(script_converter PROPERTIES OUTPUT_NAME "converter") 

install(TARGETS script_converter RUNTIME DESTINATION product/script)

set_target_properties(script_converter PROPERTIES FOLDER "script")


# tests

add_test(NAME script_converter_no_args COMMAND script_converter)
set_tests_properties(script_converter_no_args PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_converter_one_arg COMMAND script_converter something)
set_tests_properties(script_converter_one_arg PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_converter_two_args COMMAND script_converter something something)
set_tests_properties(script_converter_two_args PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_converter_invalid_target COMMAND script_converter something something abc)
set_tests_properties(script_converter_invalid_target PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_converter_invalid_source COMMAND script_converter no_source_file.txt result.py py)
set_tests_properties(script_converter_invalid_source PROPERTIES WILL_FAIL TRUE)


set(OUTPUT_FILE ${PROJECT_SOURCE_DIR}/build/result.cpp)

add_test(NAME script_converter_cpp COMMAND script_converter ${PROJECT_SOURCE_DIR}/src/script_resources/script_full.txt ${OUTPUT_FILE} cpp)

set(REFERENCE_FILE ${PROJECT_SOURCE_DIR}/src/script_resources/result.cpp)

add_test(NAME script_converter_cpp_compare COMMAND ${CMAKE_COMMAND}
    -DOUTPUT_FILE=${OUTPUT_FILE}
    -DREFERENCE_FILE=${REFERENCE_FILE}
    -P ${PROJECT_SOURCE_DIR}/src/cmake/compare.cmake
)


set(OUTPUT_FILE ${PROJECT_SOURCE_DIR}/build/result.py)

add_test(NAME script_converter_py COMMAND script_converter ${PROJECT_SOURCE_DIR}/src/script_resources/script_full.txt  ${OUTPUT_FILE} py)

set(REFERENCE_FILE ${PROJECT_SOURCE_DIR}/src/script_resources/result.py)

add_test(NAME script_converter_py_compare COMMAND ${CMAKE_COMMAND}
    -DOUTPUT_FILE=${OUTPUT_FILE}
    -DREFERENCE_FILE=${REFERENCE_FILE}
    -P ${PROJECT_SOURCE_DIR}/src/cmake/compare.cmake
)

