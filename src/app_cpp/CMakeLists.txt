
option(ADD_QT_APP "Include the Qt UI App." OFF)

if(ADD_QT_APP)

    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    if(NOT Qt5Widgets_FOUND)
        message(FATAL_ERROR "Qt5 needed but not found!")
    endif()

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)


    add_executable(title_case_app WIN32)
    target_sources(title_case_app PRIVATE app.cpp)
    target_link_libraries(title_case_app PRIVATE text_conversion_lib)
    target_link_libraries(title_case_app PRIVATE Qt5::Widgets)
    target_include_directories(title_case_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    set_target_properties(title_case_app PROPERTIES CXX_STANDARD 11)

    install(TARGETS title_case_app RUNTIME DESTINATION product/app)

    if(WIN32)
        set(WINDEPLOYQT_EXECUTABLE "${Qt5_DIR}/../../../bin/windeployqt${CMAKE_EXECUTABLE_SUFFIX}")
        set(EXE_PATH "${CMAKE_INSTALL_PREFIX}/product/app/title_case_app${CMAKE_EXECUTABLE_SUFFIX}")
        install(CODE "execute_process(COMMAND ${WINDEPLOYQT_EXECUTABLE} \"${EXE_PATH}\")")
    endif()

    set_target_properties(title_case_app PROPERTIES FOLDER "app")

endif()
