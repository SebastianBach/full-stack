add_library(script_lib STATIC)

target_sources(script_lib PRIVATE   script.h 
                                    parser.cpp
                                    engine.cpp
                                    compiler.cpp
                                    runtime.cpp)

target_include_directories(script_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(script_lib PRIVATE text_conversion_header_lib)

set_target_properties(script_lib PROPERTIES FOLDER "script")
