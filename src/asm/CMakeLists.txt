
if(UNIX AND NOT APPLE)
    if(CMAKE_COMPILER_IS_GNUCXX)
        add_subdirectory(linux_x86_64)
    endif()
endif()
