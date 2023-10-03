# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

#################################################################################

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
    DEPENDS h4acfg-win32
    COMMAND h4acfg-win32 ${CMAKE_BINARY_DIR}/system.i -c ${CMAKE_BINARY_DIR}/kernel_cfg.c -i ${CMAKE_BINARY_DIR}/kernel_id.h
)

add_executable(sample
    ${CMAKE_BINARY_DIR}/kernel_cfg.c

    ${WIN32_SAMPLE_DIR}/main.c
    ${WIN32_SAMPLE_DIR}/sample.c
    ${WIN32_SAMPLE_DIR}/ostimer.c
    ${WIN32_SAMPLE_DIR}/wintimer.c
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

target_compile_options(h4acfg-win32
  PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX- /utf-8>
  PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-g -O0>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:-O3 -DNDEBUG>
)
