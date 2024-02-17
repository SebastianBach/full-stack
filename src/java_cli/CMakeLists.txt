
# todo: replace with https://cmake.org/cmake/help/latest/module/UseJava.html add_jar()

# unit test

find_package(Java REQUIRED)
include(UseJava)

add_jar(java_unit_test
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/UnitTest.java
                ${CMAKE_CURRENT_SOURCE_DIR}/TextConversion.java
        OUTPUT_NAME unit_test
        OUTPUT_DIR ${CMAKE_BINARY_DIR}/temp/java
        MANIFEST ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/META-INF/MANIFEST.MF
)

add_dependencies(java_unit_test java_shared_lib)

add_test(NAME java_unit_test COMMAND "java" "-Djava.library.path=$<TARGET_FILE_DIR:java_shared_lib>/" "-jar" "${CMAKE_BINARY_DIR}/temp/java/unit_test.jar")


# CLI tool

add_jar(java_cli
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tool/TextConversionTool.java
                ${CMAKE_CURRENT_SOURCE_DIR}/TextConversion.java
        OUTPUT_NAME text_conversion
        OUTPUT_DIR ${CMAKE_BINARY_DIR}/temp/java
        MANIFEST ${CMAKE_CURRENT_SOURCE_DIR}/tool/META-INF/MANIFEST.MF
)

add_dependencies(java_cli java_shared_lib)

add_test(NAME test_java_cli COMMAND "java" "-Djava.library.path=$<TARGET_FILE_DIR:java_shared_lib>/" "-jar" "${CMAKE_BINARY_DIR}/temp/java/text_conversion.jar" "this is a headline")

install(FILES ${CMAKE_BINARY_DIR}/temp/java/text_conversion.jar DESTINATION product/java)

