project(loader)
set(CMAKE_CXX_STANDARD 20)

add_library(loader SHARED
        src/dllmain.cpp
        src/loader.cpp
        src/hooks/allocconsole.cpp
)

set_target_properties(loader PROPERTIES
        PREFIX ""
        OUTPUT_NAME "sm_legacy_loader"
)

target_link_libraries(loader PRIVATE api shlwapi)
target_compile_definitions(loader PRIVATE WIN32_LEAN_AND_MEAN)
