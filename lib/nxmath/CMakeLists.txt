file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxmath STATIC ${SOURCES})

target_include_directories(nxmath
    PUBLIC
        include
)