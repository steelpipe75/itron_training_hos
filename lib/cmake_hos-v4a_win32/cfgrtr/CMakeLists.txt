# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# project情報
project(h4acfg
    DESCRIPTION "HOS-V4a configulator"
    LANGUAGES CXX
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

set(KERNEL_INC_DIR  "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/kernel/include")
set(KERNEL_PROC_DIR "${KERNEL_INC_DIR}/arch/proc/${ARCH_PROC}")
set(KERNEL_IRC_DIR  "${KERNEL_INC_DIR}/arch/irc/${ARCH_IRC}")

set(H4ACFG_INC_DIR "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/cfgrtr/include")
set(H4ACFG_SRC_DIR "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/cfgrtr/source")

#################################################################################

add_executable(h4acfg-win32
    ${H4ACFG_SRC_DIR}/h4acfg.cpp
    ${H4ACFG_SRC_DIR}/analyze.cpp
    ${H4ACFG_SRC_DIR}/parpack.cpp
    ${H4ACFG_SRC_DIR}/read.cpp
    ${H4ACFG_SRC_DIR}/defercd.cpp
    ${H4ACFG_SRC_DIR}/intstk.cpp
    ${H4ACFG_SRC_DIR}/dpcque.cpp
    ${H4ACFG_SRC_DIR}/idlstk.cpp
    ${H4ACFG_SRC_DIR}/knlheap.cpp
    ${H4ACFG_SRC_DIR}/maxtpri.cpp
    ${H4ACFG_SRC_DIR}/apidef.cpp
    ${H4ACFG_SRC_DIR}/apiinc.cpp
    ${H4ACFG_SRC_DIR}/cretsk.cpp
    ${H4ACFG_SRC_DIR}/deftex.cpp
    ${H4ACFG_SRC_DIR}/cresem.cpp
    ${H4ACFG_SRC_DIR}/creflg.cpp
    ${H4ACFG_SRC_DIR}/credtq.cpp
    ${H4ACFG_SRC_DIR}/crembx.cpp
    ${H4ACFG_SRC_DIR}/cremtx.cpp
    ${H4ACFG_SRC_DIR}/crempf.cpp
    ${H4ACFG_SRC_DIR}/crembf.cpp
    ${H4ACFG_SRC_DIR}/timtic.cpp
    ${H4ACFG_SRC_DIR}/crecyc.cpp
    ${H4ACFG_SRC_DIR}/crealm.cpp
    ${H4ACFG_SRC_DIR}/defexc.cpp
    ${H4ACFG_SRC_DIR}/attini.cpp
    ${H4ACFG_SRC_DIR}/definh.cpp
    ${H4ACFG_SRC_DIR}/attisr.cpp
)

target_include_directories(h4acfg-win32 PRIVATE
    ${H4ACFG_INC_DIR}
    ${KERNEL_INC_DIR}
    ${KERNEL_PROC_DIR}
    ${KERNEL_IRC_DIR}
)

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/compile_option/compile_opion_helper.cmake)
target_compile_options_helper(h4acfg-win32) 

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/configure_file/vs_vscode.cmake)
vs_and_vscode_helper(h4acfg-win32)

