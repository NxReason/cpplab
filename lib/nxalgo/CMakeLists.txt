file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(nxalgo STATIC ${SOURCES})

target_include_directories(nxalgo
    PUBLIC
        include
)

target_link_libraries(nxalgo
    PRIVATE
        nxid
)