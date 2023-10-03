# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# project情報
project(hosv4a_kernel
    DESCRIPTION "HOS-V4a kernel"
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

if (MSVC)
    set(CMAKE_C_FLAGS   "/W4 /WX-")
    set(CMAKE_CXX_FLAGS "/W4 /WX-")
else()
    set(CMAKE_C_FLAGS           "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS         "-Wall -Wextra")
    set(CMAKE_C_FLAGS_DEBUG     "-g -O0")
    set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0")
    set(CMAKE_C_FLAGS_RELEASE   "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

#################################################################################

if(NOT WORKSPACE_ROOT_DIR)
    set(WORKSPACE_ROOT_DIR "../../..")
endif()

if(NOT ARCH_PROC)
    set(ARCH_PROC "win/win32")
endif()

if(NOT ARCH_IRC)
    set(ARCH_IRC "simple")
endif()

#################################################################################

include(../kernel/libhosv4a.cmake)

#################################################################################

find_program(KERNEL_CFGRTR h4acfg-win32.exe
    HINTS ${WORKSPACE_ROOT_DIR}lib/cmake_hos-v4a_win32/cfgrtr/build
)

set(KERNEL_DIR          "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/kernel")

set(WIN32_SAMPLE_DIR    "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/sample/win/win32")

find_file(SYSTEM_CONFIG_FILE system.cfg
    PATH ${WIN32_SAMPLE_DIR}/
)

add_custom_command(
    OUTPUT  ${CMAKE_BINARY_DIR}/system.i
    DEPENDS ${SYSTEM_CONFIG_FILE}
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ARG1} -E -x c -o system.i ${SYSTEM_CONFIG_FILE}
)

add_custom_command(
    OUTPUT  ${CMAKE_BINARY_DIR}/kernel_cfg.c ${CMAKE_BINARY_DIR}/kernel_id.h
    DEPENDS ${CMAKE_BINARY_DIR}/system.i
    COMMAND ${KERNEL_CFGRTR} ${CMAKE_BINARY_DIR}/system.i -c ${CMAKE_BINARY_DIR}/kernel_cfg.c -i ${CMAKE_BINARY_DIR}/kernel_id.h
)

include_directories(
    ${H4ACFG_INC_DIR}
    ${KERNEL_INC_DIR}
    ${KERNEL_PROC_DIR}
    ${KERNEL_IRC_DIR}
    ${CMAKE_BINARY_DIR}
    ${WIN32_SAMPLE_DIR}
)

add_executable(sample
    ${CMAKE_BINARY_DIR}/kernel_cfg.c

    ${WIN32_SAMPLE_DIR}/main.c
    ${WIN32_SAMPLE_DIR}/sample.c
    ${WIN32_SAMPLE_DIR}/ostimer.c
    ${WIN32_SAMPLE_DIR}/wintimer.c
)

target_link_libraries(sample hosv4a winmm)

