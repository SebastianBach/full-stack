add_library(c_wrapper STATIC)

target_sources(c_wrapper PRIVATE c_wrapper.cpp)
target_include_directories(c_wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(c_wrapper PRIVATE text_conversion_header_lib)

if(WIN32)
    set_target_properties(c_wrapper PROPERTIES OUTPUT_NAME "rustwrapper")
elseif(UNIX AND NOT APPLE)
    set_target_properties(c_wrapper PROPERTIES OUTPUT_NAME "librustwrapper")
endif()

set_target_properties(c_wrapper PROPERTIES FOLDER "rust")

install(TARGETS c_wrapper DESTINATION product/rust)

