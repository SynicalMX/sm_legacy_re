project(proxy)
set(CMAKE_CXX_STANDARD 20)

add_library(proxy SHARED
        src/dllmain.cpp
        src/proxy.cpp
        src/bootstrapper.cpp
)

target_link_options(proxy PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/version.def"
        "-static-libgcc"
        "-static-libstdc++"
        "-Wl,-Bstatic,--whole-archive"
        "-lwinpthread"
        "-Wl,-Bdynamic,--no-whole-archive"
)

set_target_properties(proxy PROPERTIES
        PREFIX ""
        OUTPUT_NAME "version"
)

target_compile_definitions(proxy PRIVATE WIN32_LEAN_AND_MEAN)
