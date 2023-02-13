
find_package(Python3 COMPONENTS Development)


add_library(python_module SHARED python.cpp)

set_property(TARGET python_module PROPERTY OUTPUT_NAME "func") 
set_target_properties(python_module PROPERTIES SUFFIX ".pyd")

target_link_libraries(python_module PRIVATE my_func)
target_link_libraries(python_module PRIVATE Python3::Python)

target_include_directories(python_module PRIVATE ${Python3_INCLUDE_DIRS})


set_target_properties(python_module PROPERTIES FOLDER "python")

install(TARGETS python_module RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/product)



