# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# project情報
project(hosv4a_sample
    DESCRIPTION "HOS-V4a aplfw sample win32"
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

set(LINK_WINSOCK YES)

include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/aplfw/libhosaplfw.cmake)
include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/cfgrtr/h4acfg-win32.cmake)

#################################################################################

set(APLFW_WIN32_SAMPLE_DIR  "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/aplfw/sample/win/win32")

find_file(SYSTEM_CONFIG_FILE system.cfg
    PATH ${APLFW_WIN32_SAMPLE_DIR}/
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

    ${CMAKE_BINARY_DIR}/kernel_cfg.c

    ${APLFW_WIN32_SAMPLE_DIR}/main.c
    ${APLFW_WIN32_SAMPLE_DIR}/boot.c
    ${APLFW_WIN32_SAMPLE_DIR}/ostimer.c
    ${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a_modify/aplfw/wintimer.c
)

target_link_libraries(sample hosv4a hosaplfw ws2_32 winmm)

target_include_directories(sample PRIVATE
    ${H4ACFG_INC_DIR}
    ${KERNEL_INC_DIR}
    ${KERNEL_PROC_DIR}
    ${KERNEL_IRC_DIR}
    ${CMAKE_BINARY_DIR}
    ${HOSAPLFW_INC_DIR}
    ${APLFW_WIN32_SAMPLE_DIR}
)

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/compile_option/compile_opion_helper.cmake)
target_compile_options_helper(sample) 

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/configure_file/vs_vscode.cmake)
vs_and_vscode_helper(sample)

