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

option(TEST_MODE "Enable test" ON)

if(${TEST_MODE})
    enable_testing()
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
    set(WORKSPACE_ROOT_DIR "${CMAKE_SOURCE_DIR}/../..")
endif()

if(NOT ARCH_PROC)
    set(ARCH_PROC "win/win32")
endif()

if(NOT ARCH_IRC)
    set(ARCH_IRC "simple")
endif()

#################################################################################

add_subdirectory(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/cfgrtr_ex cfgrtr_ex)

#################################################################################

set(HOSV4A_KERNEL_EX_NOUSE_MESSAGEBOX ON CACHE BOOL "no use messagebox" FORCE)
add_subdirectory(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/kernel_ex kernel_ex)

#################################################################################

set(GTest_DIR ${WORKSPACE_ROOT_DIR}/lib/third_party/googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${GTest_DIR} lib/third_party/googletest)
include(GoogleTest)

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
    DEPENDS h4acfg_ex-win32
    COMMAND h4acfg_ex-win32 ${CMAKE_BINARY_DIR}/system.i -c ${CMAKE_BINARY_DIR}/kernel_cfg.c -i ${CMAKE_BINARY_DIR}/kernel_id.h
)

add_executable(sample

    ${CMAKE_BINARY_DIR}/kernel_cfg.c

    mock_my_rand.cpp
    gmock_hos_main.cpp
    sample_test.cpp
    ${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a_modify/sample/sample_for_unittest.c
    ${WIN32_SAMPLE_DIR}/ostimer.c
    ${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a_modify/sample/wintimer.c
)

target_link_libraries(sample hosv4a_ex winmm gmock)

target_include_directories(sample PRIVATE
    .
    ${H4ACFG_INC_DIR}
    ${KERNEL_EXT_INC_DIR}
    ${KERNEL_INC_DIR}
    ${KERNEL_PROC_DIR}
    ${KERNEL_IRC_DIR}
    ${CMAKE_BINARY_DIR}
    ${WIN32_SAMPLE_DIR}
)

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_utility/compile_option/compile_opion_helper.cmake)
target_compile_options_helper(sample) 

#################################################################################

if(${TEST_MODE})
    gtest_discover_tests(sample)
endif()

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_utility/configure_file/vs_vscode.cmake)
vs_and_vscode_helper(sample)

