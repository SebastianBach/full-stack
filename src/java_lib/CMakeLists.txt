find_package(Java)

if(Java_FOUND)

    get_filename_component(JAVA_BIN "${Java_JAVA_EXECUTABLE}" DIRECTORY)
    get_filename_component(Java_HOME "${JAVA_BIN}" DIRECTORY)

    message(STATUS "Java found: ${Java_HOME}")

    add_library(java_shared_lib SHARED TextConversionTool.cpp)

    set_target_properties(java_shared_lib PROPERTIES OUTPUT_NAME "libjava_text_conversion")
    target_link_libraries(java_shared_lib PRIVATE text_conversion_header_lib)
    target_include_directories(java_shared_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(java_shared_lib PUBLIC  ${Java_HOME}/include ${Java_HOME}/include/linux)

    set_target_properties(java_shared_lib PROPERTIES FOLDER "java_lib")


    install(TARGETS java_shared_lib DESTINATION product/java)

endif()
