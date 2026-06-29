project(api)
set(CMAKE_CXX_STANDARD 20)

add_library(api SHARED
        src/sm.cpp
        src/hook.cpp
        include/memory.h
        src/memory.cpp
        src/modmanager.cpp
        include/modmanager.h
)

set_target_properties(api PROPERTIES
        PREFIX ""
        OUTPUT_NAME "sm_legacy_api"
)

target_link_options(api PRIVATE
        "-static-libgcc"
        "-static-libstdc++"
        "-Wl,-Bstatic,--whole-archive"
        "-lwinpthread"
        "-Wl,-Bdynamic,--no-whole-archive"
)

target_link_libraries(api PRIVATE minhook)
target_compile_definitions(api PRIVATE WIN32_LEAN_AND_MEAN SM_API_EXPORTS)
