# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# project情報
project(hosv4a_sample
    DESCRIPTION "HOS-V4a sample win32 (cli)"
    LANGUAGES C CXX
)

# コンパイル情報をJSON形式で出力
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# in-source ビルドガード
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

#################################################################################

set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release")
endif()

#################################################################################

if(NOT WORKSPACE_ROOT_DIR)
    set(WORKSPACE_ROOT_DIR "${CMAKE_SOURCE_DIR}/../../..")
endif()

if(NOT ARCH_PROC)
    set(ARCH_PROC "win/win32")
endif()

if(NOT ARCH_IRC)
    set(ARCH_IRC "simple")
endif()

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/kernel/libhosv4a.cmake)
include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/cfgrtr/h4acfg-win32.cmake)

#################################################################################

set(WIN32_SAMPLE_DIR    "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/sample/win/win32")

find_file(SYSTEM_CONFIG_FILE system.cfg
    PATH ${WIN32_SAMPLE_DIR}/
)

if(MSVC)
    add_custom_command(
        OUTPUT  ${CMAKE_BINARY_DIR}/system.i
        DEPENDS ${SYSTEM_CONFIG_FILE}
        COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ARG1} /P ${SYSTEM_CONFIG_FILE}
    )
else()
    add_custom_command(
        OUTPUT  ${CMAKE_BINARY_DIR}/system.i
        DEPENDS ${SYSTEM_CONFIG_FILE}
        COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ARG1} -E -x c -o system.i ${SYSTEM_CONFIG_FILE}
    )
endif()


add_custom_command(
    OUTPUT  ${CMAKE_BINARY_DIR}/kernel_cfg.c ${CMAKE_BINARY_DIR}/kernel_id.h
    DEPENDS ${CMAKE_BINARY_DIR}/system.i
    DEPENDS h4acfg-win32
    COMMAND h4acfg-win32 ${CMAKE_BINARY_DIR}/system.i -c ${CMAKE_BINARY_DIR}/kernel_cfg.c -i ${CMAKE_BINARY_DIR}/kernel_id.h
)

add_executable(sample

    ${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a_modify/kernel/ksta_ctx.c

    ${CMAKE_BINARY_DIR}/kernel_cfg.c

    ${WIN32_SAMPLE_DIR}/main.c
    ${WIN32_SAMPLE_DIR}/sample.c
    ${WIN32_SAMPLE_DIR}/ostimer.c
    ${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a_modify/sample/wintimer.c
)

target_link_libraries(sample hosv4a winmm)

target_include_directories(sample PRIVATE
    ${H4ACFG_INC_DIR}
    ${KERNEL_INC_DIR}
    ${KERNEL_PROC_DIR}
    ${KERNEL_IRC_DIR}
    ${CMAKE_BINARY_DIR}
    ${WIN32_SAMPLE_DIR}
)

target_compile_options(sample
  PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX- /utf-8>
  PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-g -O0>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:-O3 -DNDEBUG>
  PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Debug>>:-g -O0>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-O3 -DNDEBUG>
)

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/configure_file/vs_vscode.cmake)
vs_and_vscode_helper(sample)

