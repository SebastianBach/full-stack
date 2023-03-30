add_executable(script_converter)

target_sources(script_converter PRIVATE converter.cpp)
target_link_libraries(script_converter PRIVATE script_lib)
set_target_properties(script_converter PROPERTIES OUTPUT_NAME "converter") 

install(TARGETS script_converter RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product/script)

set_target_properties(script_converter PROPERTIES FOLDER "script")
