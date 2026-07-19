file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxtest STATIC ${SOURCES})

target_include_directories(nxtest
    PUBLIC
        include
)