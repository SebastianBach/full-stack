
# function lib
add_library(win_utility_lib STATIC)

target_sources(win_utility_lib PRIVATE  clipboard.cpp
                                        clipboard.h)

target_include_directories(win_utility_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(win_utility_lib text_conversion_header_lib)
set_target_properties(win_utility_lib PROPERTIES FOLDER "win_utilities")


# tests
add_executable(win_utility_test clipboard_test.cpp)
target_link_libraries(win_utility_test win_utility_lib user32 shell32)
set_target_properties(win_utility_test PROPERTIES FOLDER "win_utilities")

add_test(NAME win_utility_test COMMAND win_utility_test)


# tool
add_executable(win_tray WIN32   tray.cpp 
                                resources.h 
                                resources.rc)

target_link_libraries(win_tray win_utility_lib user32 shell32)
set_target_properties(win_tray PROPERTIES FOLDER "win_utilities")

install(TARGETS win_tray RUNTIME DESTINATION product/win)
