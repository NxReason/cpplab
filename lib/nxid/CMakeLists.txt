file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxid STATIC ${SOURCES})

target_include_directories(nxid
    PUBLIC
        include
)