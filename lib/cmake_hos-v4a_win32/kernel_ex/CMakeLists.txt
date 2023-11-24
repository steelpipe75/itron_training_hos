# 動作確認できたCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# project情報
project(hosv4a_kernel
    DESCRIPTION "HOS-V4a kernel ex"
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

option(HOSV4A_KERNEL_EX_NOUSE_MESSAGEBOX "no use messagebox" OFF)

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

add_subdirectory(${WORKSPACE_ROOT_DIR}/lib/set_thread_name set_thread_name)

#################################################################################

set(KERNEL_DIR          "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a/kernel")
set(KERNEL_SRC_DIR      "${KERNEL_DIR}/source")
set(KERNEL_INC_DIR      "${KERNEL_DIR}/include")
set(KERNEL_CORE_DIR     "${KERNEL_SRC_DIR}/core")
set(KERNEL_OBJ_DIR      "${KERNEL_SRC_DIR}/object")
set(KERNEL_INC_PROC_DIR "${KERNEL_INC_DIR}/arch/proc/${ARCH_PROC}")
set(KERNEL_INC_IRC_DIR  "${KERNEL_INC_DIR}/arch/irc/${ARCH_IRC}")
set(KERNEL_SRC_PROC_DIR "${KERNEL_SRC_DIR}/arch/proc/${ARCH_PROC}")

set(KERNEL_EXT_DIR      "${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a_modify/extension/kernel")
set(KERNEL_EXT_SRC_DIR  "${KERNEL_EXT_DIR}/source")
set(KERNEL_EXT_INC_DIR  "${KERNEL_EXT_DIR}/include")

#################################################################################

# Dispatcher
set(DSP_DIR ${KERNEL_CORE_DIR}/dsp)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${DSP_DIR}/ent_tsk.c
    ${DSP_DIR}/idl_lop.c
    ${DSP_DIR}/dsp_tsk.c
    ${DSP_DIR}/dsp_sta.c
    ${DSP_DIR}/dsp_ext.c
    ${DSP_DIR}/dsp_ter.c
    ${DSP_DIR}/dsp_wai.c
    ${DSP_DIR}/dsp_wup.c
    ${DSP_DIR}/dsp_sus.c
    ${DSP_DIR}/dsp_rsm.c
)

# Task-queue
set(QUE_DIR ${KERNEL_CORE_DIR}/que)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${QUE_DIR}/add_que.c
    ${QUE_DIR}/adf_que.c
    ${QUE_DIR}/adp_que.c
    ${QUE_DIR}/rmv_que.c
    ${QUE_DIR}/rmh_que.c
    ${QUE_DIR}/trm_que.c
    ${QUE_DIR}/nxt_que.c
    ${QUE_DIR}/rot_que.c
)

# Ready-queue
set(RDQ_DIR ${KERNEL_CORE_DIR}/rdq)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${RDQ_DIR}/cre_rdq.c
    ${RDQ_DIR}/del_rdq.c
    ${RDQ_DIR}/add_rdq.c
    ${RDQ_DIR}/rmv_rdq.c
    ${RDQ_DIR}/rmh_rdq.c
    ${RDQ_DIR}/ref_rdq.c
)

# Time management
set(TIM_DIR ${KERNEL_CORE_DIR}/tim)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${TIM_DIR}/sig_tim.c
)

# Timeout-queue
set(TOQ_DIR ${KERNEL_CORE_DIR}/toq)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${TOQ_DIR}/sig_toq.c
    ${TOQ_DIR}/add_toq.c
    ${TOQ_DIR}/rmv_toq.c
)

# Timer-queue
set(TMQ_DIR ${KERNEL_CORE_DIR}/tmq)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${TMQ_DIR}/sig_tmq.c
    ${TMQ_DIR}/add_tmq.c
    ${TMQ_DIR}/rmv_tmq.c
)

# Memory-heap
set(HEP_DIR ${KERNEL_CORE_DIR}/hep)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${HEP_DIR}/cre_hep.c
    ${HEP_DIR}/alc_hep.c
    ${HEP_DIR}/fre_hep.c
)

# Deferrable procedure call
set(DPC_DIR ${KERNEL_CORE_DIR}/dpc)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${DPC_DIR}/ini_dpc.c
    ${DPC_DIR}/req_dpc.c
    ${DPC_DIR}/exe_dpc.c
)

# Asyncronous data-queue
set(ADTQ_DIR ${KERNEL_CORE_DIR}/adtq)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${ADTQ_DIR}/frcv_adq.c
    ${ADTQ_DIR}/fsnd_adq.c
    ${ADTQ_DIR}/rcv_adq.c
    ${ADTQ_DIR}/reff_adq.c
    ${ADTQ_DIR}/refs_adq.c
    ${ADTQ_DIR}/snd_adq.c
)

# System
set(SYSOBJ_DIR ${KERNEL_OBJ_DIR}/sys)
set(KERNEL_SRCS ${KERNEL_SRCS}
    # ${SYSOBJ_DIR}/sta_knl.c
    ${KERNEL_EXT_SRC_DIR}/object/sys/sta_knl.c
    ${SYSOBJ_DIR}/get_tid.c
    ${SYSOBJ_DIR}/loc_cpu.c
    ${SYSOBJ_DIR}/unl_cpu.c
    ${SYSOBJ_DIR}/sns_loc.c
    ${SYSOBJ_DIR}/ena_dsp.c
    ${SYSOBJ_DIR}/dis_dsp.c
    ${SYSOBJ_DIR}/sns_dsp.c
    ${SYSOBJ_DIR}/sns_ctx.c
    ${KERNEL_EXT_SRC_DIR}/object/sys/ter_knl.c
)

# Tasks
set(TSKOBJ_DIR ${KERNEL_OBJ_DIR}/tsk)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${TSKOBJ_DIR}/cre_tsk.c
    ${TSKOBJ_DIR}/acre_tsk.c
    # ${TSKOBJ_DIR}/kcre_tsk.c
    ${KERNEL_EXT_SRC_DIR}/object/tsk/kcre_tsk.c
    ${TSKOBJ_DIR}/del_tsk.c
    # ${TSKOBJ_DIR}/act_tsk.c
    ${KERNEL_EXT_SRC_DIR}/object/tsk/act_tsk.c
    # ${TSKOBJ_DIR}/iact_tsk.c
    ${KERNEL_EXT_SRC_DIR}/object/tsk/iact_tsk.c
    ${TSKOBJ_DIR}/can_act.c
    ${TSKOBJ_DIR}/ext_tsk.c
    # ${TSKOBJ_DIR}/exd_tsk.c
    ${KERNEL_EXT_SRC_DIR}/object/tsk/exd_tsk.c
    ${TSKOBJ_DIR}/ter_tsk.c
    ${TSKOBJ_DIR}/chg_pri.c
    ${TSKOBJ_DIR}/kchg_pri.c
    ${TSKOBJ_DIR}/get_pri.c
    ${TSKOBJ_DIR}/ref_tsk.c
    ${TSKOBJ_DIR}/ref_tst.c
    ${TSKOBJ_DIR}/slp_tsk.c
    ${TSKOBJ_DIR}/wup_tsk.c
    ${TSKOBJ_DIR}/iwup_tsk.c
    ${TSKOBJ_DIR}/can_wup.c
    ${TSKOBJ_DIR}/rel_wai.c
    ${TSKOBJ_DIR}/irel_wai.c
    ${TSKOBJ_DIR}/sus_tsk.c
    ${TSKOBJ_DIR}/rsm_tsk.c
    ${TSKOBJ_DIR}/frsm_tsk.c
    ${TSKOBJ_DIR}/dly_tsk.c
    ${TSKOBJ_DIR}/def_tex.c
    ${TSKOBJ_DIR}/ras_tex.c
    ${TSKOBJ_DIR}/ena_tex.c
    ${TSKOBJ_DIR}/kexe_tex.c
    ${TSKOBJ_DIR}/tcb2id.c
)

# Semaphores
set(SEMOBJ_DIR ${KERNEL_OBJ_DIR}/sem)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${SEMOBJ_DIR}/cre_sem.c
    ${SEMOBJ_DIR}/acre_sem.c
    ${SEMOBJ_DIR}/kcre_sem.c
    ${SEMOBJ_DIR}/del_sem.c
    ${SEMOBJ_DIR}/sig_sem.c
    ${SEMOBJ_DIR}/isig_sem.c
    ${SEMOBJ_DIR}/wai_sem.c
    ${SEMOBJ_DIR}/pol_sem.c
    ${SEMOBJ_DIR}/twai_sem.c
    ${SEMOBJ_DIR}/ref_sem.c
)

# Event-flags
set(FLGOBJ_DIR ${KERNEL_OBJ_DIR}/flg)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${FLGOBJ_DIR}/cre_flg.c
    ${FLGOBJ_DIR}/acre_flg.c
    ${FLGOBJ_DIR}/kcre_flg.c
    ${FLGOBJ_DIR}/del_flg.c
    ${FLGOBJ_DIR}/set_flg.c
    ${FLGOBJ_DIR}/iset_flg.c
    ${FLGOBJ_DIR}/clr_flg.c
    ${FLGOBJ_DIR}/wai_flg.c
    ${FLGOBJ_DIR}/pol_flg.c
    ${FLGOBJ_DIR}/twai_flg.c
    ${FLGOBJ_DIR}/kchk_flg.c
    ${FLGOBJ_DIR}/ref_flg.c
)

# Data queues
set(DTQOBJ_DIR ${KERNEL_OBJ_DIR}/dtq)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${DTQOBJ_DIR}/cre_dtq.c
    ${DTQOBJ_DIR}/acre_dtq.c
    ${DTQOBJ_DIR}/kcre_dtq.c
    ${DTQOBJ_DIR}/del_dtq.c
    ${DTQOBJ_DIR}/snd_dtq.c
    ${DTQOBJ_DIR}/fsnd_dtq.c
    ${DTQOBJ_DIR}/rcv_dtq.c
    ${DTQOBJ_DIR}/prcv_dtq.c
    ${DTQOBJ_DIR}/trcv_dtq.c
)

# Mailboxes
set(MBXOBJ_DIR ${KERNEL_OBJ_DIR}/mbx)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${MBXOBJ_DIR}/acre_mbx.c
    ${MBXOBJ_DIR}/kcre_mbx.c
    ${MBXOBJ_DIR}/snd_mbx.c
    ${MBXOBJ_DIR}/rcv_mbx.c
    ${MBXOBJ_DIR}/kadf_msg.c
    ${MBXOBJ_DIR}/kadp_msg.c
    ${MBXOBJ_DIR}/kadd_msq.c
    ${MBXOBJ_DIR}/krmf_msg.c
    ${MBXOBJ_DIR}/krmp_msg.c
    ${MBXOBJ_DIR}/krmv_msq.c
)

# Mutexes
set(MTXOBJ_DIR ${KERNEL_OBJ_DIR}/mtx)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${MTXOBJ_DIR}/cre_mtx.c
    ${MTXOBJ_DIR}/acre_mtx.c
    ${MTXOBJ_DIR}/kcre_mtx.c
    ${MTXOBJ_DIR}/del_mtx.c
    ${MTXOBJ_DIR}/loc_mtx.c
    ${MTXOBJ_DIR}/ploc_mtx.c
    ${MTXOBJ_DIR}/tloc_mtx.c
    ${MTXOBJ_DIR}/unl_mtx.c
    ${MTXOBJ_DIR}/kadd_mtx.c
    ${MTXOBJ_DIR}/krmv_mtx.c
)

# Fixed-sized Memory Pools
set(MPFOBJ_DIR ${KERNEL_OBJ_DIR}/mpf)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${MPFOBJ_DIR}/acre_mpf.c
    ${MPFOBJ_DIR}/kcre_mpf.c
    # ${MPFOBJ_DIR}/get_mpf.c
    ${KERNEL_EXT_SRC_DIR}/object/mpf/get_mpf.c
    # ${MPFOBJ_DIR}/pget_mpf.c
    ${KERNEL_EXT_SRC_DIR}/object/mpf/pget_mpf.c
    # ${MPFOBJ_DIR}/tget_mpf.c
    ${KERNEL_EXT_SRC_DIR}/object/mpf/tget_mpf.c
    ${MPFOBJ_DIR}/rel_mpf.c
)

# System Time Management
set(TIMOBJ_DIR ${KERNEL_OBJ_DIR}/tim)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${TIMOBJ_DIR}/set_tim.c
    ${TIMOBJ_DIR}/get_tim.c
    ${TIMOBJ_DIR}/isig_tim.c
)

# Cyclic Handlers
set(CYCOBJ_DIR ${KERNEL_OBJ_DIR}/cyc)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${CYCOBJ_DIR}/cre_cyc.c
    ${CYCOBJ_DIR}/acre_cyc.c
    ${CYCOBJ_DIR}/kcre_cyc.c
    ${CYCOBJ_DIR}/del_cyc.c
    ${CYCOBJ_DIR}/sta_cyc.c
    ${CYCOBJ_DIR}/stp_cyc.c
    ${CYCOBJ_DIR}/ref_cyc.c
    ${CYCOBJ_DIR}/kcyc_hdr.c
)

# Interrupt handlers
set(INHOBJ_DIR ${KERNEL_OBJ_DIR}/inh)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${INHOBJ_DIR}/def_inh.c
    ${INHOBJ_DIR}/sta_inh.c
    ${INHOBJ_DIR}/exe_inh.c
    ${INHOBJ_DIR}/end_inh.c
)

# Interrupt Service Routines
set(ISROBJ_DIR ${KERNEL_OBJ_DIR}/isr)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${ISROBJ_DIR}/acre_isr.c
    ${ISROBJ_DIR}/kcre_isr.c
    ${ISROBJ_DIR}/del_isr.c
    ${ISROBJ_DIR}/exe_isr.c
)

# CPU exception handlers
set(EXCOBJ_DIR ${KERNEL_OBJ_DIR}/exc)
set(KERNEL_SRCS ${KERNEL_SRCS}
    ${EXCOBJ_DIR}/def_exc.c
    ${EXCOBJ_DIR}/exe_exc.c
)

#################################################################################

add_library(hosv4a_ex STATIC
    ${KERNEL_SRCS}
    # ${KERNEL_SRC_PROC_DIR}/kcre_ctx.c
    ${WORKSPACE_ROOT_DIR}/lib/third_party/hos-v4a_modify/extension/kernel/source/arch/proc/win/win32/kcre_ctx.c
    ${KERNEL_SRC_PROC_DIR}/kdis_int.c
    ${KERNEL_SRC_PROC_DIR}/kena_int.c
    # ${KERNEL_SRC_PROC_DIR}/kini_prc.c
    ${KERNEL_EXT_SRC_DIR}/arch/proc/win/win32/kini_prc.c
    ${KERNEL_SRC_PROC_DIR}/krst_ctx.c
    # ${KERNEL_SRC_PROC_DIR}/ksta_ctx.c
    ${KERNEL_EXT_SRC_DIR}/arch/proc/win/win32/ksta_ctx.c
    ${KERNEL_SRC_PROC_DIR}/kswi_ctx.c
    ${KERNEL_SRC_PROC_DIR}/kwai_int.c
    ${KERNEL_SRC_PROC_DIR}/val_int.c
    ${KERNEL_SRC_PROC_DIR}/vsig_int.c
    ${KERNEL_EXT_SRC_DIR}/arch/proc/win/win32/kter_ctx.c
)

if(HOSV4A_KERNEL_EX_NOUSE_MESSAGEBOX)
    target_compile_definitions(hosv4a_ex PRIVATE
        HOSV4A_KERNEL_EX_NOUSE_MESSAGEBOX
    )
endif()

target_include_directories(hosv4a_ex PUBLIC
    ${KERNEL_EXT_INC_DIR}/arch/proc/win/win32
    ${KERNEL_EXT_INC_DIR}
    ${KERNEL_INC_DIR}
    ${KERNEL_INC_PROC_DIR}
    ${KERNEL_INC_IRC_DIR}
)

target_link_libraries(hosv4a_ex PUBLIC set_thread_name)

#################################################################################

include(${WORKSPACE_ROOT_DIR}/lib/cmake_utility/compile_option/compile_opion_helper.cmake)
target_compile_options_helper(hosv4a_ex) 

