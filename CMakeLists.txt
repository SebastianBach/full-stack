cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ADD_BASIC_TOOLS "Include basic commandline tools." OFF)
option(ADD_SDK "Include static library with documentation and examples." OFF)
option(ADD_C_LIB "Include a static library with C interface." OFF)
option(ADD_DYNAMIC_LIB "Include a dynamic library." OFF)
option(ADD_PYTHON_MODULE "Include the Python module." OFF)
option(ADD_PY_DOCS "Include Python module documentation." OFF)
option(ADD_RUST_APP "Include the Rust cmdl app. Requires the C library." OFF)
option(ADD_JAVA_APP "Include the Java command line app." OFF)
option(ADD_SDK_DOCS "Include C++ library documentation." OFF)
option(ADD_QT_APP "Include the Qt UI App. Requires the SDK." OFF)
option(ADD_SCRIPT_TOOLS "Include script tools." OFF)
option(ADD_ASSEMBLY_PROGRAM "Include ASM program. Requires the C library." OFF)

if(WIN32)
    option(ADD_WIN_TOOLS "Include Windows Utilities" OFF)
endif()

project(full_stack CXX)
enable_testing()


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "build with GCC")
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_IMPORT_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_MODULE_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wpedantic -Wconversion -Werror)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product)

if(ADD_SDK)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/lib)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/header)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/example)
endif()

if(ADD_DYNAMIC_LIB)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/dynamic_lib)
endif()

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/web)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/android)

if(ADD_BASIC_TOOLS)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/tools)
endif()

if(ADD_WIN_TOOLS)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/win)
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/wasm)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp/cppcheck)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp/coverage)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp/doxygen)


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib_example_build)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/script_compiler)

if(ADD_ASSEMBLY_PROGRAM AND ADD_C_LIB)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/asm)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp/asm)
endif()


if(ADD_SCRIPT_TOOLS)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/script)
endif()

if(ADD_QT_APP)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/app)
endif()

if(ADD_SDK_DOCS)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/documentation)
endif()

if(ADD_PYTHON_MODULE)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/python)
endif()

if(ADD_PY_DOCS)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/python/documentation)
endif()

if(ADD_RUST_APP)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/rust)
endif()

if(ADD_JAVA_APP)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/java)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp/java)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

if(CMAKE_COMPILER_IS_GNUCXX)

    option(BUILD_COVERAGE "Coverage Build" OFF)

    if(BUILD_COVERAGE)
        message(STATUS "Build coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    endif()

    option(BUILD_UBSAN "UndefinedBehaviorSanitizer Build" OFF)

    if(BUILD_UBSAN)
        message(STATUS "Build with UBSan")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fno-omit-frame-pointer -fno-sanitize-recover")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
    endif()

    option(BUILD_ASAN "AddressSanitizer Build" OFF)

    if(BUILD_ASAN)
        message(STATUS "Build with ASan")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    endif()

    option(BUILD_GPROF "gprof Build" OFF)

    if(BUILD_GPROF)
        message(STATUS "Build with gprof")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    endif()


    option(BUILD_VALGRIND "Valgrind Testing" OFF)

    if(BUILD_VALGRIND)
        message(STATUS "build for Valgrind testing")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
        set(MEMORYCHECK_COMMAND "/usr/bin/valgrind")
        set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=${PROJECT_SOURCE_DIR}/valgrind.supp")
        include(CTest)
    endif()

endif()

add_subdirectory(src)
