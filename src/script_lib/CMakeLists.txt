add_library(script_lib STATIC)

target_sources(script_lib PRIVATE script.cpp script.h)

target_include_directories(script_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(script_lib PRIVATE text_conversion_header_lib)

set_target_properties(script_lib PROPERTIES FOLDER "script")
