file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxcli STATIC ${SOURCES})

target_include_directories(nxcli
    PUBLIC
        include
)