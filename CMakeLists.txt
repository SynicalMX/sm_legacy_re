cmake_minimum_required(VERSION 3.5)
project(sm_legacy_re)

add_subdirectory(vendor/minhook)
add_subdirectory(proxy)
add_subdirectory(loader)
add_subdirectory(api)

add_subdirectory(examplemod)
