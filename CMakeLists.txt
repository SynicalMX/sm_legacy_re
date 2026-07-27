cmake_minimum_required(VERSION 3.5)
project(sm_legacy_re)

add_subdirectory(vendor/minhook)
add_subdirectory(proxy)
add_subdirectory(loader)
add_subdirectory(api)

add_subdirectory(researchmod)

set(SM_PATH "C:/Program Files (x86)/Steam/steamapps/common/Scrap Mechanic")
set(SM_RELEASE "${SM_PATH}/Release")
set(SM_LEGACY "${SM_RELEASE}/sm_legacy")

add_custom_target(install_and_run
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:proxy>   "${SM_RELEASE}/version.dll"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:api>     "${SM_LEGACY}/sm_legacy_api.dll"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:loader>  "${SM_LEGACY}/sm_legacy_loader.dll"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:researchmod> "${SM_PATH}/EngineMods/researchmod.dll"
        COMMAND "C:/Program Files (x86)/Steam/steam.exe" "steam://rungameid/387990"
        DEPENDS proxy api loader researchmod
        COMMENT "Installing DLLs and launching Scrap Mechanic"
)
