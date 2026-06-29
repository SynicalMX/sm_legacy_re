project(examplemod)

set(CMAKE_CXX_STANDARD 20)

add_library(examplemod SHARED
        src/modmain.cpp
)

set_target_properties(examplemod PROPERTIES
        PREFIX ""
        OUTPUT_NAME "examplemod"
)

target_link_libraries(examplemod PRIVATE api)
target_compile_definitions(examplemod PRIVATE WIN32_LEAN_AND_MEAN)
