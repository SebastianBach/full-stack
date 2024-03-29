add_executable(script_transcompiler)

target_sources(script_transcompiler PRIVATE main.cpp 
                                        transcompiler.cpp
                                        frontend.cpp
                                        optimization.cpp
                                        backend.cpp
                                        backend_linux_x86_64.cpp
                                        backend_python.cpp
                                        backend_cpp.cpp
                                        backend_intermediate.cpp)

target_include_directories(script_transcompiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(script_transcompiler PRIVATE script_lib)
set_target_properties(script_transcompiler PROPERTIES OUTPUT_NAME "transcompiler") 

install(TARGETS script_transcompiler RUNTIME DESTINATION product/script)

set_target_properties(script_transcompiler PROPERTIES FOLDER "script")


# basic invalid args tests

add_test(NAME script_transcompiler_no_args COMMAND script_transcompiler)
set_tests_properties(script_transcompiler_no_args PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_transcompiler_one_arg COMMAND script_transcompiler something)
set_tests_properties(script_transcompiler_one_arg PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_transcompiler_two_args COMMAND script_transcompiler something something)
set_tests_properties(script_transcompiler_two_args PROPERTIES WILL_FAIL TRUE)

add_test(NAME script_transcompiler_invalid_target COMMAND script_transcompiler something something abc)
set_tests_properties(script_transcompiler_invalid_target PROPERTIES WILL_FAIL TRUE)


# basic tests

set(COMPLEX_SOURCE_FILE ${PROJECT_SOURCE_DIR}/src/script_resources/script_test.txt)

add_test(NAME script_transcompiler_test_cpp COMMAND script_transcompiler ${COMPLEX_SOURCE_FILE} basic.cpp cpp)
add_test(NAME script_transcompiler_test_py COMMAND script_transcompiler ${COMPLEX_SOURCE_FILE} basic.py py)
add_test(NAME script_transcompiler_test_i COMMAND script_transcompiler ${COMPLEX_SOURCE_FILE} basic.txt i)
add_test(NAME script_transcompiler_test_linux_x86_64 COMMAND script_transcompiler ${COMPLEX_SOURCE_FILE} basic.s linux_x86_64)
