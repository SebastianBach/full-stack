add_executable(cmdl_interactive)

target_sources(cmdl_interactive PRIVATE cmdl_interactive.cpp)
set_target_properties(cmdl_interactive PROPERTIES OUTPUT_NAME "title_case_console") 
target_link_libraries(cmdl_interactive PRIVATE text_conversion_header_lib)
target_include_directories(cmdl_interactive PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS cmdl_interactive RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product/tools)

set_target_properties(cmdl_interactive PROPERTIES FOLDER "tools")
