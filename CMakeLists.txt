cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(full_stack CXX)
enable_testing()


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("build with GCC")
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_IMPORT_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_MODULE_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wpedantic -Wconversion -Werror)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/lib)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/header)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/documentation)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/lib/example)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/tools)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/app)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/python)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/script)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/dynamic_lib)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/product/rust)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/wasm)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/temp)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib_example_build)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/script_compiler)

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

endif()

add_subdirectory(src)
