
string(TIMESTAMP CURRENT_DATE "%Y-%m-%d")
string(TIMESTAMP CURRENT_TIME "%H:%M:%S")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/BUILD.txt
                ${CMAKE_BINARY_DIR}/product/lib/BUILD.txt
                @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.txt DESTINATION ${CMAKE_BINARY_DIR}/product/lib)