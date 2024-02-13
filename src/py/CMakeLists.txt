cmake_minimum_required(VERSION 3.12)

option(ADD_PYTHON_MODULE "Include the Python Module" OFF)

if(ADD_PYTHON_MODULE)

    message(STATUS "Building Python module.")

    find_package(Python3 COMPONENTS Development)


    add_library(python_module SHARED module.cpp functions.cpp functions.h)

    set_target_properties(python_module PROPERTIES OUTPUT_NAME "text_conversion") 
    set_target_properties(python_module PROPERTIES FOLDER "python")

    target_link_libraries(python_module PRIVATE text_conversion_header_lib)
    target_link_libraries(python_module PRIVATE Python3::Python)

    target_include_directories(python_module PRIVATE ${Python3_INCLUDE_DIRS})
    target_include_directories(python_module PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    
    if(WIN32)
        set_target_properties(python_module PROPERTIES SUFFIX ".pyd")
        install(TARGETS python_module RUNTIME DESTINATION product/python)
    elseif(UNIX AND NOT APPLE)
        install(TARGETS python_module LIBRARY DESTINATION product/python)
    endif()

endif()
