
string(TIMESTAMP CURRENT_DATE "%Y-%m-%d")
string(TIMESTAMP CURRENT_TIME "%H:%M:%S")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/BUILD.txt
                ${CMAKE_INSTALL_PREFIX}/product/lib/BUILD.txt
                @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.txt DESTINATION product/lib)

install(DIRECTORY example_project/ DESTINATION product/lib/example FILES_MATCHING PATTERN "*")



# build and test doxygen code snippets source

add_executable(lib_doxygen_examples)

target_sources(lib_doxygen_examples PRIVATE doc_examples/examples.cpp)
target_link_libraries(lib_doxygen_examples PRIVATE text_conversion_lib)

add_test(NAME lib_doxygen_examples COMMAND lib_doxygen_examples)

set_target_properties(lib_doxygen_examples PROPERTIES FOLDER "static_libs")

if (WIN32)
    target_compile_options(lib_doxygen_examples PRIVATE "/Zc:__cplusplus")
endif()

# doxygen documentation

option(ADD_LIB_DOCS "Include C++ library documentation." OFF)

if(ADD_LIB_DOCS)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxyfile
    ${CMAKE_INSTALL_PREFIX}/temp/doxygen/doxyfile
    @ONLY)

    message(STATUS "Building C++ library documentation.")

    add_custom_target(lib_docs ALL COMMAND bash -c "doxygen ${CMAKE_INSTALL_PREFIX}/temp/doxygen/doxyfile")
    add_dependencies(lib_docs text_conversion_lib)
endif()
