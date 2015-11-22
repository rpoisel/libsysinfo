cmake_minimum_required (VERSION 2.6)
project (libsysinfo C)

include_directories(
    .
    )

add_custom_command(OUTPUT lexer.c
    COMMAND re2c -i -o lexer.c ${CMAKE_SOURCE_DIR}/lexer.re
    MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/lexer.re
    )

add_library(system_info STATIC
    lexer.c
    system_info.c
    )

add_executable(libsysinfo_test
    libsysinfo_test.c
    )

target_link_libraries(libsysinfo_test
    system_info
    )
