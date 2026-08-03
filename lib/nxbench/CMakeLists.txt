file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxbench STATIC ${SOURCES})

target_include_directories(nxbench
    PUBLIC
        include
)