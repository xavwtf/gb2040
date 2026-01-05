# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Pico specific stuff
if(PICO_BUILD)
    if(WIN32)
        set(USERHOME $ENV{USERPROFILE})
    else()
        set(USERHOME $ENV{HOME})
    endif()
    set(sdkVersion 2.2.0)
    set(toolchainVersion 14_2_Rel1)
    set(picotoolVersion 2.2.0-a4)
    set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
    if (EXISTS ${picoVscode})
        include(${picoVscode})
    endif()

    set(PICO_BOARD pico CACHE STRING "Board type")

    # Pull in Raspberry Pi Pico SDK (must be before project)
    include(pico_sdk_import.cmake)
endif()
# ====================================================================================

file(GLOB_RECURSE CORE_SOURCES "src/core/*.cpp")

set(SHARED_SOURCES
    src/main.cpp
    ${CORE_SOURCES}
)

if(PICO_BUILD)
    # ========= pico target =========

    project(gb2040 C CXX ASM)
    pico_sdk_init()

    # add rp2040 executable
    add_executable(gb2040
        ${SHARED_SOURCES}
        src/platform/pico/platform.cpp
    )

    # set up include dirs for pico target
    target_include_directories(gb2040
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # pull in pico deps
    target_link_libraries(gb2040 pico_stdlib)

    pico_add_extra_outputs(gb2040)
else()
    # ========= desktop target =========

    project(gb2040_desktop C CXX ASM)

    # add desktop executable
    add_executable(gb2040_desktop
        ${SHARED_SOURCES}
        src/platform/desktop/platform.cpp
    )

    # do the same for desktop, include SDL
    target_include_directories(gb2040_desktop
        PUBLIC 
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3/include
    )

    # pull in desktop deps
    target_link_libraries(gb2040_desktop
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3/lib/x64/SDL3.lib
    )

    # copy SDL3.dll next to desktop executable
    add_custom_command(TARGET gb2040_desktop POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3/lib/x64/SDL3.dll
        $<TARGET_FILE_DIR:gb2040_desktop>
    )

endif()
# add url via pico_set_program_url
