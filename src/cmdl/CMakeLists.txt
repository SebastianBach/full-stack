add_executable(cmdl)

target_sources(cmdl PRIVATE cmdl.cpp)
set_target_properties(cmdl PROPERTIES OUTPUT_NAME "title_case") 
target_link_libraries(cmdl PRIVATE text_conversion_header_lib)
target_include_directories(cmdl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME cmdl COMMAND cmdl "this is the headline")

install(TARGETS cmdl RUNTIME DESTINATION product/tools)

set_target_properties(cmdl PROPERTIES FOLDER "tools")
