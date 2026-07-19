file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxrng STATIC ${SOURCES})

target_include_directories(nxrng
    PUBLIC
        include
)