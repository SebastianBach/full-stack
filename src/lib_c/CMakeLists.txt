add_library(lib_c STATIC)

target_sources(lib_c PRIVATE c_wrapper.cpp)
target_include_directories(lib_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lib_c PRIVATE text_conversion_header_lib)

if(WIN32)
    set_target_properties(lib_c PROPERTIES OUTPUT_NAME "libtext_conversion_c")
elseif(UNIX AND NOT APPLE)
    set_target_properties(lib_c PROPERTIES OUTPUT_NAME "libtext_conversion_c")
endif()

set_target_properties(lib_c PROPERTIES FOLDER "static_libs")

install(TARGETS lib_c DESTINATION product/rust)

