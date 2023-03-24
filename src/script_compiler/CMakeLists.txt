add_executable(script_compiler)

target_sources(script_compiler PRIVATE compiler.cpp)

target_link_libraries(script_compiler PRIVATE script_lib)
target_include_directories(script_compiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS script_compiler RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product/script)

set_target_properties(script_compiler PROPERTIES FOLDER "script")
