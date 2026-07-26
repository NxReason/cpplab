file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(patterns STATIC ${SOURCES})

target_include_directories(patterns
    PUBLIC
        include
)