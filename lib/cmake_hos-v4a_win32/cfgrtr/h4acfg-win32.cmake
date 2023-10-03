# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

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

target_include_directories(h4acfg-win32 PUBLIC
    ${H4ACFG_INC_DIR}
    ${KERNEL_INC_DIR}
    ${KERNEL_PROC_DIR}
    ${KERNEL_IRC_DIR}
)

target_compile_options(h4acfg-win32 PUBLIC
  PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX- /utf-8>
  PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-g -O0>
  PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:-O3 -DNDEBUG>
)
