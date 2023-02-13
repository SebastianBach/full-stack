add_library(func_lib STATIC)

target_sources(func_lib PRIVATE lib.cpp info.cpp)
target_include_directories(func_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(func_lib PRIVATE my_func)


install(TARGETS func_lib  DESTINATION ${CMAKE_BINARY_DIR}/product/lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib.h DESTINATION ${CMAKE_BINARY_DIR}/product/lib)

set_target_properties(func_lib PROPERTIES FOLDER "lib")
