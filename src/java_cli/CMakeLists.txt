
add_custom_target(java_cli ALL COMMAND bash -c  "javac -d ${CMAKE_BINARY_DIR}/temp/java ${CMAKE_CURRENT_SOURCE_DIR}/TextConversionTool.java; \
                                                cd '${CMAKE_BINARY_DIR}/temp/java'; \
                                                jar cmvf ${CMAKE_CURRENT_SOURCE_DIR}/META-INF/MANIFEST.MF text_conversion.jar TextConversionTool.class "

                                                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                                VERBATIM)

add_dependencies(java_cli java_shared_lib)

add_test(NAME test_java_cli COMMAND "java" "-Djava.library.path=$<TARGET_FILE_DIR:java_shared_lib>" "-jar" "${CMAKE_BINARY_DIR}/temp/java/text_conversion.jar" "this is a headline")

install(FILES ${CMAKE_BINARY_DIR}/temp/java/text_conversion.jar DESTINATION product/java)

