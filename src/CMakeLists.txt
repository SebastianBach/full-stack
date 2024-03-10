add_subdirectory(header)
add_subdirectory(test_header)

add_subdirectory(cmdl)
add_subdirectory(cmdl_interactive)
add_subdirectory(cmdl_file)

add_subdirectory(app_py_cmdl)

add_subdirectory(lib)
add_subdirectory(lib_resources)
add_subdirectory(test_lib)
add_subdirectory(lib_c)
add_subdirectory(test_lib_c)

if(ADD_ASSEMBLY_PROGRAM)
    add_subdirectory(asm)
endif()

if(ADD_PYTHON_MODULE)
    add_subdirectory(py)
    add_subdirectory(app_py)
    add_subdirectory(py_ipynb)
endif()

if(ADD_PY_DOCS)
    add_subdirectory(py_doc)
endif()

if(ADD_QT_APP)
    add_subdirectory(app_cpp)
endif()

add_subdirectory(dynamic_lib)
add_subdirectory(dynamic_lib_app_py)
add_subdirectory(test_dynamic_lib)

if(ADD_SCRIPT_TOOLS)
    add_subdirectory(script_lib)
    add_subdirectory(test_script)
    add_subdirectory(script_console)
    add_subdirectory(script_interpreter)
    add_subdirectory(script_compiler)
    add_subdirectory(script_runtime)
    add_subdirectory(script_converter)
    add_subdirectory(script_ide)
endif()

if(ADD_RUST_APP)
    add_subdirectory(rust_cmdl)
endif()

if(ADD_JAVA_APP)
    add_subdirectory(java_lib)
    add_subdirectory(java_cli)
endif()

add_subdirectory(web)
