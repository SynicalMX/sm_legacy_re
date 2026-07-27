project(researchmod)

set(CMAKE_CXX_STANDARD 20)

add_library(researchmod SHARED
        src/modmain.cpp
)

set_target_properties(researchmod PROPERTIES
        PREFIX ""
        OUTPUT_NAME "researchmod"
)

target_link_libraries(researchmod PRIVATE api)
target_compile_definitions(researchmod PRIVATE WIN32_LEAN_AND_MEAN)
