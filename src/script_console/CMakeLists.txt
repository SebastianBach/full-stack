add_executable(script_console)

target_sources(script_console PRIVATE console.cpp)

target_link_libraries(script_console PRIVATE script_lib)
target_include_directories(script_console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(script_console PROPERTIES OUTPUT_NAME "console") 

install(TARGETS script_console RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product/script)

set_target_properties(script_console PROPERTIES FOLDER "script")
