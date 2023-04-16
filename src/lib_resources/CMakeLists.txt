
string(TIMESTAMP CURRENT_DATE "%Y-%m-%d")
string(TIMESTAMP CURRENT_TIME "%H:%M:%S")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/BUILD.txt
                ${CMAKE_INSTALL_PREFIX}/product/lib/BUILD.txt
                @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.txt DESTINATION product/lib)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxyfile
                ${CMAKE_INSTALL_PREFIX}/doxyfile
                @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/frontpage.dox ${CMAKE_CURRENT_SOURCE_DIR}/examples.cpp DESTINATION temp)

install(DIRECTORY example_project/ DESTINATION product/lib/example FILES_MATCHING PATTERN "*")



# build and test doxygen examples source

add_executable(lib_doxygen_examples)

target_sources(lib_doxygen_examples PRIVATE examples.cpp)
target_link_libraries(lib_doxygen_examples PRIVATE text_conversion_lib)

add_test(NAME lib_doxygen_examples COMMAND lib_doxygen_examples)

set_target_properties(lib_doxygen_examples PROPERTIES FOLDER "static_lib")

if (WIN32)
    target_compile_options(lib_doxygen_examples PRIVATE "/Zc:__cplusplus")
endif()

