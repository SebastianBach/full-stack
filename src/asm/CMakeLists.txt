
add_custom_target(asm_program ALL 

        COMMAND bash -c "echo 'build ASM program'; \
                        ./build_and_run.sh '$<TARGET_FILE:lib_c>' '${CMAKE_BUILD_TYPE}' '${CMAKE_BINARY_DIR}/temp/asm'" 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        VERBATIM)

add_dependencies(asm_program lib_c)

add_test(asm_test "${CMAKE_BINARY_DIR}/temp/asm/program")

install(CODE " file(INSTALL \"${CMAKE_BINARY_DIR}/temp/asm/program\" DESTINATION \"${CMAKE_INSTALL_PREFIX}/product/asm\")" )
