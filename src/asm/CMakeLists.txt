
add_custom_target(asm_program ALL 

        COMMAND bash -c "echo 'build ASM program'; \
                        ./build_and_run.sh '$<TARGET_FILE:lib_c>' release" 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        VERBATIM)

add_dependencies(asm_program lib_c)

add_test(asm_test "${CMAKE_CURRENT_SOURCE_DIR}/temp/program")

install(CODE " file(INSTALL \"${CMAKE_CURRENT_SOURCE_DIR}/temp/program\" DESTINATION \"${CMAKE_INSTALL_PREFIX}/product/asm\")" )
