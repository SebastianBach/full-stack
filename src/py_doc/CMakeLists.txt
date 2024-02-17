
message(STATUS "Building Python module documentation.")

add_custom_target(python_docs ALL COMMAND bash -c "sphinx-build -b html ${CMAKE_CURRENT_SOURCE_DIR}/source ${CMAKE_BINARY_DIR}/product/python/documentation")
add_dependencies(python_docs python_module)

