add_executable(script_interpreter)

target_sources(script_interpreter PRIVATE interpreter.cpp)

target_link_libraries(script_interpreter PRIVATE script_lib)

install(TARGETS script_interpreter RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product/script)

set_target_properties(script_interpreter PROPERTIES FOLDER "script")

