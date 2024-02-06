option(ADD_RUST_APP "Include the Rust cmdl app." OFF)

if(ADD_RUST_APP)

    set(RUST_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/text_conversion")

    set(RUST_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/text_conversion/target/release/text_conversion")

    add_custom_command(
        OUTPUT ${RUST_EXECUTABLE}
        # each COMMAND is its own shell instance; env variables are local to the shell instance; 
        # so put all into one command to tell build.rs where to find the lib...
        COMMAND bash -c "   echo 'start Rust build process...'; \
                            full_path='$<TARGET_FILE:lib_c>'; \
                            folder_path=\$(dirname \"\$full_path\"); \
                            export C_WRAPPER_LIB_LOCATION=\$folder_path; \
                            echo \"Stored folder path in environment variable: \$C_WRAPPER_LIB_LOCATION\"; \
                            echo \$C_WRAPPER_LIB_LOCATION; \
                            cargo clean; \
                            cargo build --release"
        COMMAND chmod +x "${RUST_EXECUTABLE}"
        WORKING_DIRECTORY ${RUST_PROJECT_DIR}
        COMMENT "Compiling Rust command line tool: ${RUST_PROJECT_DIR}"
        VERBATIM
    )

    add_custom_target(
        rust_app ALL
        DEPENDS ${RUST_EXECUTABLE}
    )

    add_dependencies(rust_app lib_c)


    install(CODE " file(INSTALL \"${RUST_EXECUTABLE}\" DESTINATION \"${CMAKE_BINARY_DIR}/product/rust/\")" )

    add_test(NAME test_rust_app COMMAND "${RUST_EXECUTABLE}" "this is a test")

    add_test(NAME test_rust_app_no_args COMMAND "${RUST_EXECUTABLE}")
    set_tests_properties(test_rust_app_no_args PROPERTIES WILL_FAIL TRUE)

endif()