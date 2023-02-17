add_executable(cmdl_file)

target_sources(cmdl_file PRIVATE cmdl_file.cpp)
target_link_libraries(cmdl_file PRIVATE my_func)
target_include_directories(cmdl_file PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

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

# etc

install(TARGETS cmdl_file RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product/tools)

set_target_properties(cmdl_file PROPERTIES FOLDER "tools")
