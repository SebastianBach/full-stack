add_library(dynamic_lib SHARED lib.cpp)

set_target_properties(dynamic_lib PROPERTIES PUBLIC_HEADER lib.h)
set_target_properties(dynamic_lib PROPERTIES OUTPUT_NAME "text_conversion")
target_link_libraries(dynamic_lib PRIVATE text_conversion_header_lib)
target_include_directories(dynamic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS dynamic_lib DESTINATION ${CMAKE_BINARY_DIR}/product/dynamic_lib)

set_target_properties(dynamic_lib PROPERTIES FOLDER "dynamic_lib")

