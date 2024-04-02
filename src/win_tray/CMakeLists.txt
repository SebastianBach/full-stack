
add_executable(win_tray WIN32   tray.cpp 
                                resources.h 
                                resources.rc)

target_link_libraries(win_tray user32 shell32)
target_link_libraries(win_tray text_conversion_header_lib)
set_target_properties(win_tray PROPERTIES FOLDER "win_utilities")

install(TARGETS win_tray RUNTIME DESTINATION product/win)
