add_library(text_conversion_lib STATIC)

target_sources(text_conversion_lib PRIVATE conversion.cpp info.cpp text_conversion.h)
target_include_directories(text_conversion_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(text_conversion_lib PRIVATE text_conversion_header_lib)

if(WIN32)
    set_target_properties(text_conversion_lib PROPERTIES OUTPUT_NAME "text_conversion")
elseif(UNIX AND NOT APPLE)
    set_target_properties(text_conversion_lib PROPERTIES OUTPUT_NAME "libtext_conversion")
endif()

install(TARGETS text_conversion_lib DESTINATION product/lib/lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/text_conversion.h DESTINATION product/lib/header)

set_target_properties(text_conversion_lib PROPERTIES FOLDER "static_libs")
