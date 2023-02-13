add_executable(cmdl_interactive)

target_sources(cmdl_interactive PRIVATE cmdl_interactive.cpp)

target_link_libraries(cmdl_interactive PRIVATE my_func)
target_include_directories(cmdl_interactive PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS cmdl_interactive RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product)

set_target_properties(cmdl_interactive PROPERTIES FOLDER "tools")
