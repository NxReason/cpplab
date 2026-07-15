file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(cli_output STATIC ${SOURCES})

target_include_directories(cli_output
    PUBLIC
        include
)