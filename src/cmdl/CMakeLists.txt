add_executable(cmdl)

target_sources(cmdl PRIVATE cmdl.cpp)

target_link_libraries(cmdl PRIVATE my_func)
target_include_directories(cmdl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME cmdl COMMAND cmdl "Basic Test")

install(TARGETS cmdl RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product)

set_target_properties(cmdl PROPERTIES FOLDER "tools")
