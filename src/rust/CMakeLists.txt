set(RUST_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/text_conversion")

set(RUST_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/text_conversion/target/release/text_conversion")

add_custom_command(
    OUTPUT ${RUST_EXECUTABLE}
    COMMAND cargo clean
    COMMAND cargo build --release
    COMMAND chmod +x "${RUST_EXECUTABLE}"
    WORKING_DIRECTORY ${RUST_PROJECT_DIR}
    COMMENT "Compiling Rust project: ${RUST_PROJECT_DIR}"
    VERBATIM
)

add_custom_target(
    rust_app ALL
    DEPENDS ${RUST_EXECUTABLE}
)

install(CODE " file(INSTALL \"${RUST_EXECUTABLE}\" DESTINATION \"${CMAKE_BINARY_DIR}/product/rust/\")" )

add_test(NAME test_rust_app COMMAND "${RUST_EXECUTABLE}" "this is a test")

add_test(NAME test_rust_app_no_args COMMAND "${RUST_EXECUTABLE}")
set_tests_properties(test_rust_app_no_args PROPERTIES WILL_FAIL TRUE)
