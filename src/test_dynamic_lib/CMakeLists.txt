
add_executable(test_dynamic_lib test.cpp)

target_link_libraries(test_dynamic_lib PRIVATE dynamic_lib)

target_include_directories(test_dynamic_lib PRIVATE $<TARGET_PROPERTY:dynamic_lib,INTERFACE_INCLUDE_DIRECTORIES>)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set_target_properties(test_dynamic_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")
  add_custom_command(TARGET test_dynamic_lib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:dynamic_lib> $<TARGET_FILE_DIR:test_dynamic_lib>)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set_target_properties(test_dynamic_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")
  add_custom_command(TARGET test_dynamic_lib POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:dynamic_lib> $<TARGET_FILE_DIR:test_dynamic_lib>)
  set_target_properties(test_dynamic_lib PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN'")
else()
  message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set_target_properties(test_dynamic_lib PROPERTIES FOLDER "dynamic_lib")

add_test(NAME test_dynamic_lib COMMAND test_dynamic_lib)

