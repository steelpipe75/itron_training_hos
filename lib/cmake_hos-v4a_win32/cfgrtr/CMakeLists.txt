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
    set(WORKSPACE_ROOT_DIR "../../..")
endif()

if(NOT ARCH_PROC)
    set(ARCH_PROC "win/win32")
endif()

if(NOT ARCH_IRC)
    set(ARCH_IRC "simple")
endif()

#################################################################################

include(h4acfg-win32.cmake)

#################################################################################

if(MSVC)
    # Visual Studio環境は ${CMAKE_BINARY_DIR}フォルダ 直下にビルド成果物のexeファイルを出力しない
    # Ninja環境/MinGW Makefiles環境などは ${CMAKE_BINARY_DIR}フォルダ 直下にビルド成果物のexeファイルを出力する
    # exe呼び出し処理の使い勝手が変わるのが嫌だったので、Visual Studio環境のビルド成果物のexeファイルを
    # ほかの環境に合わせた位置にコピーする処理を追加する
    #  ※ Visual Studio環境だと Debug / Release それぞれのビルドconfigで ビルド成果物のexeファイル出力フォルダが変わる。
    #     $<TARGET_FILE:h4acfg-win32>でconfigの変更に追従させる
    add_custom_command(
        TARGET h4acfg-win32 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:h4acfg-win32> ${CMAKE_BINARY_DIR}/$<TARGET_FILE_NAME:h4acfg-win32>
    )
endif()

set(LAUNCH_JSON_EXE_FILE h4acfg-win32.exe)

# Visual Studio Code用 設定ファイル
configure_file(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/configure_file/tasks.json.in  ${WORKSPACE_ROOT_DIR}/../.vscode/tasks.json)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    configure_file(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/configure_file/launch.json.in ${WORKSPACE_ROOT_DIR}/../.vscode/launch.json)
endif()
