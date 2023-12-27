
option(SW_OPT_no_unused_parameter OFF "if \"ON\" add compile option \"-Wno-unused-parameter\"")

macro(target_compile_options_helper ARG_TARGET_NAME)
    target_compile_options(${ARG_TARGET_NAME}
        PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX- /utf-8>
        PRIVATE $<$<C_COMPILER_ID:Clang>:-Wall -Wextra>
        PRIVATE $<$<AND:$<C_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-g -O0>
        PRIVATE $<$<AND:$<C_COMPILER_ID:Clang>,$<CONFIG:Release>>:-O3 -DNDEBUG>
        PRIVATE $<$<AND:$<C_COMPILER_ID:Clang>,$<CONFIG:Coverage>>:-g -O0 -fprofile-instr-generate -fcoverage-mapping>

        PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX- /utf-8>
        PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
        PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-g -O0>
        PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:-O3 -DNDEBUG>
        PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Coverage>>:-g -O0 -fprofile-instr-generate -fcoverage-mapping>
    )
    if(${SW_OPT_no_unused_parameter})
        target_compile_options(${ARG_TARGET_NAME}
            PRIVATE $<$<AND:$<C_COMPILER_ID:Clang>>:-Wno-unused-parameter>
            PRIVATE $<$<AND:$<CXX_COMPILER_ID:Clang>>:-Wno-unused-parameter>
        )
    endif()
endmacro()
