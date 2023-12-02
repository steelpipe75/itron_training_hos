# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# project情報
project(tlsf
    DESCRIPTION "tlsf"
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
    set(WORKSPACE_ROOT_DIR "${CMAKE_SOURCE_DIR}/../..")
endif()

#################################################################################

set(TLSF_DIR ${WORKSPACE_ROOT_DIR}/lib/third_party/tlsf)

add_library(tlsf STATIC
    ${TLSF_DIR}/tlsf.c
)

target_include_directories(tlsf PUBLIC
    ${TLSF_DIR}
)

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_utility/compile_option/compile_opion_helper.cmake)
target_compile_options_helper(tlsf) 

