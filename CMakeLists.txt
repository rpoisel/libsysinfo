cmake_minimum_required (VERSION 2.6)
project (Tutorial C)

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

add_executable(main
    main.c
    )

target_link_libraries(main
    system_info
    )
