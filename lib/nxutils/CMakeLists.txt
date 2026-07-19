file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxutils STATIC ${SOURCES})

target_include_directories(nxutils
    PUBLIC
        include
)