/* Copyright (c) 2019-2021 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBSERVICE_ARCH_I386_WRAPPER_H
#define GUARD_LIBSERVICE_ARCH_I386_WRAPPER_H 1
#define _KOS_SOURCE 1

#include "../../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <kos/types.h>

#include "../../com.h"

DECL_BEGIN

/*
 * Function arguments are serialized (and potentially deserialized) as follows:
 *   - SERVICE_TYPE_386_R32:      putl(VALUE);
 *   - SERVICE_TYPE_386_R64:      putl(VALUE & 0xffffffff); putl((VALUE >> 32) & 0xffffffff);
 *   - SERVICE_TYPE_X86_64_R64:   putq(VALUE);
 *   - SERVICE_TYPE_STR_IN:       putP(MAP_BUFFER_DATA(VALUE, (strlen(VALUE) + 1) * sizeof(char)).offset_in_shm);
 *   - SERVICE_TYPE_ARGBUF_IN:    putP(MAP_BUFFER_DATA(VALUE, (size_t)PARAMS[sizearg_index]).offset_in_shm);
 *   - SERVICE_TYPE_ARGBUF_OUT:   putP(ALLOC_BUFFER_DATA((size_t)PARAMS[sizearg_index]).offset_in_shm);
 *   - SERVICE_TYPE_ARGBUF_INOUT: putP(MAP_BUFFER_DATA(VALUE, (size_t)PARAMS[sizearg_index]).offset_in_shm);
 *   - SERVICE_TYPE_FIXBUF_IN:    putP(MAP_BUFFER_DATA(VALUE, BUFFER_SIZE).offset_in_shm);
 *   - SERVICE_TYPE_FIXBUF_OUT:   putP(ALLOC_BUFFER_DATA(BUFFER_SIZE).offset_in_shm);
 *   - SERVICE_TYPE_FIXBUF_INOUT: putP(MAP_BUFFER_DATA(VALUE, BUFFER_SIZE).offset_in_shm);
 *
 * Deserialization only does anything for out and in/out buffer arguments, where it will
 * copy back data from the SHM buffer to the user's buffer (unless the user's buffer was
 * located within SHM (s.a. `service_buffer_malloc()')).
 *
 * Serialized data is stored as a tightly packed datastream
 * in `service_com::sc_generic::g_data'. Because all values
 * written to this  stream are 4  bytes long, alignment  is
 * always guarantied  as `struct service_com'  also has  an
 * alignment at least  that large (and  the `g_data'  field
 * is at an offset that is a multiple of `4') */
STATIC_ASSERT(IS_ALIGNED(offsetof(struct service_com, sc_generic.g_data), 4));


/* Fixed-length buffers with a size <= this value are stored inline with the com descriptor.
 * As such, fixed-length buffers no greater than  this value don't profit from being  stored
 * in SHM memory, as they are always copied before/after a com call. */
#ifdef __x86_64__
#define COM_FIXBUF_INLINE_THRESHOLD 64
#else /* __x86_64__ */
#define COM_FIXBUF_INLINE_THRESHOLD 32
#endif /* !__x86_64__ */


/* ================================================================================================
 * Buffer   argument   indices   are    calculated   as   follows   (s.a.    LOC_bufparam_handles):
 *   - All fixed-length buffers with a fixed data size <= COM_FIXBUF_INLINE_THRESHOLD
 *     are moved into a separate buffer list `INLINE_BUFFERS'
 *   - Take the list of all parameters that operate on buffers
 *   - Sort such such that buffers are ordered as in,inout,out
 *   - All  out/inout  buffers that  have `SERVICE_OUT_SIZEARG_RETURN_MINVAL',
 *     are moved to the back of their respective sub-list of buffers elements.
 *   - Positions within the resulting list are used as buffer indices within
 *     generated code.
 *   - INLINE_BUFFERS_COUNT:  # of buffer arguments in `INLINE_BUFFERS'
 *   - BUF_PARAM_COUNT:       # of buffer arguments
 *   - IN_BUF_ARGUMENT_COUNT: # of in buffers (== index of first inout buffer)
 *   - INOUT_BUF_PARAM_COUNT: # of inout buffers
 *   - OUT_BUF_PARAM_COUNT:   # of out buffers
 * ================================================================================================
 *
 *
 *
 * ================================================================================================
 * The stack-frame of a wrapper function looks like this:
 *
 * ------------------------------------------------------------------------------------------------
 *      {SP-RELATIVE OFFSET}               {CONTENS}
 * ------------------------------------------------------------------------------------------------
 *      CFA-cg_locvar_offset               [<start of locals>]
 *      CFA-cg_locvar_offset+0*P           sigset_t *LOC_oldset;         # [1..1] Old signal maks pointer
 *      CFA-cg_locvar_offset+1*P           struct userprocmask *LOC_upm; # [1..1] Return value of `getuserprocmask()'
 *
 * #if BUF_PARAM_COUNT != 0
 *                                         # [0..1] Non-shm buffer temporary storage
 *      CFA-cg_locvar_offset+2*P           void *LOC_bufpar_ptr;
 *
 *                                         # [1..1][valid_if(LOC_bufpar_ptr)] SHM for `LOC_bufpar_ptr'
 *      CFA-cg_locvar_offset+3*P           REF struct service_shm_handle *LOC_bufpar_shm;
 *
 *                                         # [0..1][*] SHM handles for user buffers (NULL for buffers that need to be copied)
 *      CFA-cg_locvar_offset+4*P           struct service_shm_handle *LOC_bufparam_handles[BUF_PARAM_COUNT];
 *
 *                                         # [0..1][*] SHM handles for user buffers (NULL for buffers that need to be copied)
 * #if IN_BUF_PARAM_COUNT != 0 && (INOUT_BUF_PARAM_COUNT != 0 || OUT_BUF_PARAM_COUNT != 0)
 *      CFA-cg_locvar_offset+...           byte_t *LOC_outbuffers_start; # [1..1] Base address for output buffers (see below)
 * #endif // IN_BUF_PARAM_COUNT != 0 && (INOUT_BUF_PARAM_COUNT != 0 || OUT_BUF_PARAM_COUNT != 0)
 * #endif // BUF_PARAM_COUNT != 0
 *
 *      CFA-cg_locvar_offset+cg_locvar_size [<end of locals>]
 *
 * #ifdef __x86_64__
 *  /   CFA-10*P                           REGPAR: %rdi        # Only if PARAM_COUNT >= 1  (NOT RESTORED!)
 *  |   CFA-9*P                            REGPAR: %rsi        # Only if PARAM_COUNT >= 2  (NOT RESTORED!)
 *  |   CFA-8*P                            REGPAR: %rdx        # Only if PARAM_COUNT >= 3  (NOT RESTORED!)
 *  |   CFA-7*P                            REGPAR: %rcx        # Only if PARAM_COUNT >= 4  (NOT RESTORED!)
 *  |   CFA-6*P                            REGPAR: %r8         # Only if PARAM_COUNT >= 5  (NOT RESTORED!)
 *  \   CFA-5*P                            REGPAR: %r9         # Only if PARAM_COUNT >= 6  (NOT RESTORED!)
 *  -   CFA-4*P                            SAVED: %r12         # Only if `COM_GENERATOR_FEATURE_USES_R12' (restored on exit)
 * #else // __x86_64__
 *  /   CFA-5*P                            SAVED: %Pdi         # Only if `COM_GENERATOR_FEATURE_USES_EDI' (restored on exit)
 *  \   CFA-4*P                            SAVED: %Psi         # Only if `COM_GENERATOR_FEATURE_USES_ESI' (restored on exit)
 * #endif // !__x86_64__
 *  /   CFA-3*P                            SAVED: %Pbx         # %Pbx is used for `struct service_com            *R_service_com'
 *  \   CFA-2*P                            SAVED: %Pbp         # %Pbp is used for `REF struct service_shm_handle *R_service_shm_handle'
 *  -   CFA-1*P                            RETURN_PC
 *  /   CFA                                [STACK_ARG[0]]
 *  |   CFA+1*P                            [STACK_ARG[1]]
 *  |                                       ...
 *  \   CFA+n*P                            [STACK_ARG[n]]
 * ------------------------------------------------------------------------------------------------
 * Where CFA == %Psp + cfa_offset   (and `cfa_offset' is adjusted as %Psp is altered)
 * Where P   == sizeof(void *)
 * ================================================================================================
 *
 *
 *
 * ================================================================================================
 * ALLOC_SIZE is calculated as:
 *      offsetof(struct service_com, sc_generic.g_data)
 *    + PARAM_COUNT * sizeof(uintptr_t)                           # Every parameter has (at least) 1 serial word
 * #ifndef __x86_64__
 *    + PARAM_COUNT_OF(SERVICE_TYPE_386_R64) * sizeof(uintptr_t)  # On i386, 64-bit arguments take 2 serial words
 * #endif // !__x86_64__
 *    + SUM(INLINE_BUFFERS_COUNT.each.buffer_size)                # Inline buffers are allocated alongside com
 * Afterwards, apply the size requirements detailed in `libservice_shmbuf_alloc_nopr()'
 * to   the   calculated   size   to   generate   the   effective   allocation    size.
 *
 * INLINE_BUFFERS_OFFSET is calculated as:
 *      offsetof(struct service_com, sc_generic.g_data)
 *    + PARAM_COUNT * sizeof(uintptr_t)
 * #ifndef __x86_64__
 *    + PARAM_COUNT_OF(SERVICE_TYPE_386_R64) * sizeof(uintptr_t)
 * #endif // !__x86_64__
 * ================================================================================================
 *
 *
 *
 * ================================================================================================
 * Code features flags:
 * Note that regardless of which features are enabled/disabled, code always works correctly!
 *   - COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_LODS  # Use `lodsP' to load non-buffer arguments
 *   - COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_STOS  # Use `stosP' to write non-buffer arguments
 *   - COM_GENERATOR_FEATURE_USES_R12                       # x86_64-only: Set when %r12 is used by the implementation
 *   - COM_GENERATOR_FEATURE_USES_EDI                       # i386-only:   Set when %edi is used by the implementation
 *   - COM_GENERATOR_FEATURE_USES_ESI                       # i386-only:   Set when %esi is used by the implementation
 * ================================================================================================
 *
 *
 *
 * ================================================================================================
 * Wrapper functions are implemented as follows:
 *
 * >>
 * >> #ifdef __x86_64__
 * >> #define SET_ERROR_RETURN_VALUE() \
 * >>     movq $<info->dl_error_return.scr_rax>, service_com::sc_retval::scr_rax(%R_service_com)
 * >> #else // __x86_64__
 * >> #define SET_ERROR_RETURN_VALUE()                                                           \
 * >>     movq $<info->dl_error_return.scr_eax>, service_com::sc_retval::scr_eax(%R_service_com) \
 * >>     movq $<info->dl_error_return.scr_edx>, service_com::sc_retval::scr_edx(%R_service_com)
 * >> #endif // !__x86_64__
 * >>
 * >>
 * >> ENTRY:
 * >>     .cfi_startproc
 * >>     .cfi_def_cfa_offset 0
 * >>
 * >> // Save registers & allocate stack space
 * >>     pushP_cfi_r %Pbp        # %Pbp is used for `REF struct service_shm_handle *R_service_shm_handle'
 * >>     pushP_cfi_r %Pbx        # %Pbx is used for `struct service_com            *R_service_com'
 * >> #ifdef __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_R12
 * >>     pushP_cfi_r %r12        # Only if used anywhere below (restored on exit)
 * >> #endif // COM_GENERATOR_FEATURE_USES_R12
 * >> #if PARAM_COUNT >= 6
 * >>     pushP_cfi_r %r9
 * >> #endif // PARAM_COUNT >= 6
 * >>     pushP_cfi_r %r8         # Only if PARAM_COUNT >= 5  (NOT RESTORED!)
 * >>     pushP_cfi_r %rcx        # Only if PARAM_COUNT >= 4  (NOT RESTORED!)
 * >>     pushP_cfi_r %rdx        # Only if PARAM_COUNT >= 3  (NOT RESTORED!)
 * >>     pushP_cfi_r %rsi        # Only if PARAM_COUNT >= 2  (NOT RESTORED!)
 * >>     pushP_cfi_r %rdi        # Only if PARAM_COUNT >= 1  (NOT RESTORED!)
 * >> #else // __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_ESI
 * >>     pushP_cfi_r %Psi        # Only if used anywhere below (restored on exit)
 * >> #endif // COM_GENERATOR_FEATURE_USES_ESI
 * >> #if COM_GENERATOR_FEATURE_USES_EDI
 * >>     pushP_cfi_r %Pdi        # Only if used anywhere below (restored on exit)
 * >> #endif // COM_GENERATOR_FEATURE_USES_EDI
 * >> #endif // !__x86_64__
 * >>
 * >>     subP   $<cg_locvar_size>, %Psp
 * >>     .cfi_adjust_cfa_offset <cg_locvar_size>
 * >>
 * >> // Disable preemption
 * >>     call   getuserprocmask
 * >>     pushP_cfi %Pax                                                     # LOC_upm
 * >>     pushP_cfi userprocmask::pm_sigmask(%Pax)        # LOC_oldset
 * >>     movP   $ss_full, userprocmask::pm_sigmask(%Pax) # Disable preemption
 * >>     .cfi_remember_state
 * >> .Leh_preemption_pop_begin:
 * >>
 * >>
 * >> // Allocate the com buffer
 * >>     movP   $<struct service *self>, %R_fcall0P   # Input constant (hard-coded)
 * >>     movP   $<ALLOC_SIZE>,           %R_fcall1P   # Input constant (hard-coded)
 * >> #if !EXCEPT_ENABLED
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_pop_preemption
 * >> #else // !EXCEPT_ENABLED
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // EXCEPT_ENABLED
 * >>     movP   %Pax, %R_service_shm_handle   # %R_service_shm_handle == %Pbp
 * >>     movP   %Pdx, %R_service_com          # %R_service_com        == %Pbx
 * >>
 * >>
 * >>
 * >> // Initialize the command descriptor
 * >> .Leh_free_service_com_begin:
 * >>
 * >>
 * >>
 * >> // Serialize buffer arguments (if they exist)
 * >> #if BUF_PARAM_COUNT == 0
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pax  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pax, userprocmask::pm_sigmask(%Pdx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_com_buffer_alloc
 * >> .Ltest_pending_signals_after_com_buffer_alloc_return:
 * >> #elif BUF_PARAM_COUNT == 1
 * >>     movP   $0, LOC_bufpar_ptr(%Psp)
 * >>     movP   $<struct service *self>,                                                         %R_fcall0P
 * >>     movP   SP_OFFSET_OF_PARAM(BUFFER_INDEX_TO_PARAM_INDEX(BUFFER_ARGUMENT(0).INDEX))(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[BUFFER_ARGUMENT(0).INDEX](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jnz    .Lsingle_buffers_is_in_band
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >> #if BUFFER_ARGUMENT(0).HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<BUFFER_ARGUMENT(0).FIXED_BUFFER_SIZE_WITH_ADJUSTMENT>, %R_fcall1P
 * >> #else !BUFFER_ARGUMENT(0).HAS_FIXED_BUFFER_SIZE
 * >>     movP   ..., %R_fcall1P  # Buffer size requirements of BUFFER_ARGUMENT(0)
 * >> #if BUFFER_ARGUMENT(0).IS_IN_OR_INOUT_BUFFER
 * >>     movP   %R_fcall1P, %Psi    # Used by the out-of-band copy-in loop below!
 * >> #endif // BUFFER_ARGUMENT(0).IS_IN_OR_INOUT_BUFFER
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %R_fcall1P, %Pax   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #endif // !BUFFER_ARGUMENT(0).HAS_FIXED_BUFFER_SIZE
 * >> #if !EXCEPT_ENABLED
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !EXCEPT_ENABLED
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // EXCEPT_ENABLED
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy an out-of-band in/inout buffer into SHM memory
 * >> #if BUFFER_ARGUMENT(0).IS_IN_OR_INOUT_BUFFER
 * >>     movP   %Pax, %Pdi # Unconditionally use %Pdi for copying!
 * >> #endif // BUFFER_ARGUMENT(0).IS_IN_OR_INOUT_BUFFER
 * >>     subP   service_shm_handle::ssh_shm(%Pdx), %Pax
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx)
 * >>     movP   %Pax, BUFFER_ARGUMENT(0).SERIAL_OFFSET(%Psp)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_single_buffer_alloc
 * >> .Ltest_pending_signals_after_single_buffer_alloc_return:
 * >> #if BUFFER_ARGUMENT(0).IS_IN_OR_INOUT_BUFFER
 * >> #if BUFFER_ARGUMENT(0).HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<BUFFER_ARGUMENT(0).FIXED_BUFFER_SIZE>, %Pcx
 * >> #else // BUFFER_ARGUMENT(0).HAS_FIXED_BUFFER_SIZE
 * >>     movP   %Psi,                                  %Pcx # This one was preserved above!
 * >> #endif // !BUFFER_ARGUMENT(0).HAS_FIXED_BUFFER_SIZE
 * >>     movP   BUFFER_ARGUMENT(0).PARAM_OFFSET(%Psp), %Psi # Unconditionally use %Psi for copying!
 * >>     rep    movsb
 * >> #endif // BUFFER_ARGUMENT(0).IS_IN_OR_INOUT_BUFFER
 * >>     jmp    .Lsingle_buffers_done
 * >>
 * >> .Lsingle_buffers_is_in_band:
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_single_buffers_is_in_band
 * >> .Ltest_pending_signals_after_single_buffers_is_in_band_return:
 * >>     # %Pax == libservice_shm_handle_ataddr_nopr(<self>, SP_OFFSET_OF_PARAM(BUFFER_INDEX_TO_PARAM_INDEX(0))(%Psp))
 * >>     movP   SP_OFFSET_OF_PARAM(BUFFER_INDEX_TO_PARAM_INDEX(0))(%Psp), %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, BUFFER_ARGUMENT(0).SERIAL_OFFSET(%Psp)
 * >> .Lsingle_buffers_done:
 * >>
 * >> #else // #elif BUF_PARAM_COUNT >= 2
 * >>     # >> %R_temp_exbuf_size is %edi on i386 and %r12 on x86_64
 * >>     # NOTE: On x86_64, compilation getting here imples `COM_GENERATOR_FEATURE_USES_R12'!
 * >>     xorP   %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     movP   %R_temp_exbuf_size, LOC_bufpar_ptr(%Psp)
 * >> {foreach[BUFFER_ARGUMENT: <INDEX>, <PARAM_OFFSET>, <SERIAL_OFFSET>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles'
 * >>     movP   $<struct service *self>,                                      %R_fcall0P
 * >>     movP   SP_OFFSET_OF_PARAM(BUFFER_INDEX_TO_PARAM_INDEX(INDEX))(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[INDEX](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jz     1f
 * >>     movP   SP_OFFSET_OF_PARAM(BUFFER_INDEX_TO_PARAM_INDEX(INDEX))(%Psp), %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, SERIAL_OFFSET(%Psp)
 * >>     jmp    2f
 * >> 1:  # NOTE: When only 1 buffer argument exists, %R_temp_exbuf_size isn't
 * >>     #       used and the allocated+initialization is done inline.
 * >>     addP   ..., %R_temp_exbuf_size  # Account for required buffer size (depending on buffer type)
 * >> 2:
 * >> }}
 * >>     testP  %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     jz     .Lall_buffers_are_in_band
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >>     movP   %R_temp_exbuf_size,      %R_fcall1P
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %R_fcall1P, %Pax   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #if !EXCEPT_ENABLED
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !EXCEPT_ENABLED
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // EXCEPT_ENABLED
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy out-of-band in/inout buffers into SHM memory
 * >> #if IN_BUF_ARGUMENT_COUNT != 0 || INOUT_BUF_PARAM_COUNT != 0
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdi  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pcx  # `struct userprocmask *upm'
 * >>     movP   %Pdi, userprocmask::pm_sigmask(%Pcx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pcx)
 * >>     jnz    .Ltest_pending_signals_after_xbuf_alloc
 * >> .Ltest_pending_signals_after_xbuf_alloc_return:
 * >>     movP   %Pax, %Pdi                               # Unconditionally use %Pdi for copying!
 * >>     movP   service_shm_handle::ssh_shm(%Pdx), %Pdx  # %Pdx is the base address of the out-of-band buffer SHM mapping
 * >> {foreach[IN_INOUT_BUFFER_ARGUMENT: <INDEX>, <PARAM_OFFSET>, <SERIAL_OFFSET>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles'
 * >>     cmpP   $0, LOC_bufparam_handles[INDEX](%Psp)
 * >>     jne    1f
 * >> #if IN_BUF_PARAM_COUNT != 0 && INOUT_BUF_PARAM_COUNT != 0 && OUT_BUF_PARAM_COUNT != 0
 * >> #if IS_FIRST_INOUT_BUFFER(INDEX)
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif
 * >> #endif // IN_BUF_PARAM_COUNT != 0 && INOUT_BUF_PARAM_COUNT != 0 && OUT_BUF_PARAM_COUNT != 0
 * >>
 * >>     # Set: %Pax = SHM_ADDR - SHM_BASE  (offset in SHM to input buffer)
 * >>     # NOTE: We don't have to about output buffers, since those appear after in/inout buffers
 * >>     movP   %Pdi, %Pax
 * >>     subP   %Pdx, %Pax
 * >>     movP   %Pax, SERIAL_OFFSET(%Psp)                # Store SHM offset in serial data
 * >>
 * >>     movP   PARAM_OFFSET(%Psp), %Psi                 # Unconditionally use %Psi for copying!
 * >>     movP   ...,                %Pcx                 # required buffer size (depending on buffer type)
 * >>     rep    movsb                                    # Copy input buffers into SHM
 * >> 1:
 * >> }}
 * >> #if IN_BUF_PARAM_COUNT != 0 && INOUT_BUF_PARAM_COUNT == 0 && OUT_BUF_PARAM_COUNT != 0
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif // IN_BUF_PARAM_COUNT != 0 && INOUT_BUF_PARAM_COUNT == 0 && OUT_BUF_PARAM_COUNT != 0
 * >>     jmp    .Lall_buffers_are_in_band_preemption_reenabled
 * >> #endif // IN_BUF_ARGUMENT_COUNT != 0 || INOUT_BUF_PARAM_COUNT != 0
 * >> .Lall_buffers_are_in_band:
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pax  # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    .Ltest_pending_signals_after_all_buffers_are_in_band
 * >> .Lall_buffers_are_in_band_preemption_reenabled:
 * >> #endif // #endif BUF_PARAM_COUNT >= 2
 * >>
 * >>
 * >>
 * >> // Serialize non-buffer arguments (if they exist)
 * >> #if NON_BUFFER_ARGUMENT_COUNT != 0
 * >> #if COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_LODS
 * >> #set _GENERATOR_VAR_Psi_offset = FIRST_NON_BUFFER_ARGUMENT.PARAM_OFFSET   # Stack-offset of first argument
 * >>     leaP   FIRST_NON_BUFFER_ARGUMENT.PARAM_OFFSET(%Psp), %Psi
 * >> #endif // COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_LODS
 * >>
 * >> #if COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_STOS
 * >> #set _GENERATOR_VAR_Pdi_offset = FIRST_NON_BUFFER_ARGUMENT.SERIAL_OFFSET  # Serial-offset of first argument
 * >>     leaP   FIRST_NON_BUFFER_ARGUMENT.PARAM_OFFSET(%Psp), %Pdi
 * >> #endif // COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_STOS
 * >>
 * >> {foreach[NON_BUFFER_ARGUMENT: <PARAM_OFFSET>, <SERIAL_OFFSET>]: {
 * >>     # NOTE: PARAM_OFFSET is the offset to the input parameter (from %Psp)
 * >>     # NOTE: SERIAL_OFFSET is the offset in the serial stream (from %R_service_com)
 * >>     # NOTE: For parameters with PARAM_TYPE == SERVICE_TYPE_386_R64,
 * >>     #       on i386, the below code block is repeated twice with
 * >>     #       PARAM_OFFSET and SERIAL_OFFSET adjusted the second time
 * >>     #       around as:
 * >>     #       >> PARAM_OFFSET  += 4;
 * >>     #       >> SERIAL_OFFSET += 4;
 * >>
 * >>     # Load the argument value from the parameter-save or stack-argument area
 * >> #if COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_LODS
 * >> #if _GENERATOR_VAR_Psi_offset != PARAM_OFFSET
 * >> #static_assert(PARAM_OFFSET > _GENERATOR_VAR_Psi_offset)
 * >>     addP   $(PARAM_OFFSET - _GENERATOR_VAR_Psi_offset), %Psi
 * >> #endif
 * >>     lodsP
 * >> #set _GENERATOR_VAR_Psi_offset += sizeof(void *)
 * >> #else // COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_LODS
 * >>     movP   PARAM_OFFSET(%Psp), %Pax
 * >> #endif // !COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_LODS
 * >>
 * >>     # Write the argument value to serial com data area
 * >> #if COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_STOS
 * >> #if _GENERATOR_VAR_Pdi_offset != SERIAL_OFFSET
 * >> #static_assert(SERIAL_OFFSET > _GENERATOR_VAR_Pdi_offset)
 * >>     addP   $(SERIAL_OFFSET - _GENERATOR_VAR_Pdi_offset), %Pdi
 * >> #endif
 * >>     stosP
 * >> #set _GENERATOR_VAR_Pdi_offset += sizeof(void *)
 * >> #else // COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_STOS
 * >>     movP   %Pax, SERIAL_OFFSET(%R_service_com)
 * >> #endif // !COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_STOS
 * >> }}
 * >> #endif // NON_BUFFER_ARGUMENT_COUNT != 0
 * >>
 * >>
 * >>
 * >> // Set the function code within the com descriptor
 * >>     movP   $<info->dl_comid>, sc_code(%R_service_com)
 * >>
 * >>
 * >>
 * >> // Calculate the SHM-relative address of `service_com'
 * >>     movP   %R_service_com,                                     %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%R_service_shm_handle), %Pdx
 * >>
 * >>
 * >>
 * >> // Serialize fixed-length inline buffers
 * >> #if INLINE_BUFFERS_COUNT != 0
 * >> {foreach[INLINE_BUFFER_ARGUMENT: <INLINE_BUFFERS_OFFSET>, <INLINE_BUFFER_SIZE>, <PARAM_OFFSET>, <SERIAL_OFFSET>]: {
 * >>     # NOTE: `INLINE_BUFFERS_OFFSET' (>= `INLINE_BUFFERS_OFFSET') is the
 * >>     #       offsets from service_com to where inline buffer data is stored.
 * >>     leaP   INLINE_BUFFERS_OFFSET(%Pdx), %Pax    # SHM-relative address of the inline buffer
 * >>     movP   %Pax, SERIAL_OFFSET(%R_service_com)  # Store relative address in serial stream
 * >> #if ARGUMENT_IS_IN_OR_INOUT_BUFFER # (Referring to the argument being enumerated)
 * >>     # Whether or not movs is used is determined on a per-argument basis
 * >> #if ARGUMENT_USES_MOVS_FOR_COPY
 * >>     leaP   INLINE_BUFFERS_OFFSET(%R_service_com), %Pdi # This instruction is skipped if `Pdi' already has the
 * >>                                                        # correct value, which may be the case if a preceding
 * >>                                                        # inline buffer already set it up correctly.
 * >>     movP   PARAM_OFFSET(%Psp),                    %Psi
 * >>     movP   $INLINE_BUFFER_SIZE,                   %Pcx
 * >>     rep    movsb
 * >> #else // ARGUMENT_USES_MOVS_FOR_COPY
 * >>     movP   PARAM_OFFSET(%Psp), %Pcx
 * >>     {INLINE_MEMCPY(_OFF, _BWLQ, INLINE_BUFFER_SIZE) {
 * >>         mov{_BWLQ} _OFF(%Pcx), %{_BWLQ}ax
 * >>         mov{_BWLQ} %{_BWLQ}ax, INLINE_BUFFERS_OFFSET+_OFF(%R_service_com)
 * >>     }}
 * >> #endif // !ARGUMENT_USES_MOVS_FOR_COPY
 * >> #endif // ARGUMENT_IS_IN_OR_INOUT_BUFFER
 * >> }}
 * >> #endif // INLINE_BUFFERS_COUNT != 0
 * >>
 * >>
 * >>
 * >> // Insert the command into the server's pending list
 * >>     # Atomically insert the new command into the list
 * >>     # HINT: At this point, %Pdx == (%R_service_com - service_shm_handle::ssh_shm(%R_service_shm_handle))
 * >>     movP   service_shm_handle::ssh_shm(%R_service_shm_handle), %Pcx
 * >> 1:  movP   service_shm::s_commands(%Pcx), %Pax
 * >>     movP   %Pax, service_com::sc_link(%R_service_com)
 * >>     lock   cmpxchgP %Pdx, service_shm::s_commands(%Pcx)
 * >>     jne    1b
 * >>
 * >>
 * >>
 * >> .Leh_com_waitfor_begin:
 * >>
 * >>
 * >>
 * >> // Tell the server that a new command has become available
 * >>     #     futex_wake(&shm->s_commands, 1)
 * >>     # <=> syscall(SYS_lfutex, &shm->s_commands, LFUTEX_WAKE, 1)
 * >>     movP   $SYS_lfutex, %Pax
 * >> #ifdef __x86_64__
 * >>     leaq   service_shm::s_commands(%Pcx), %rdi   # NOTE: %Pcx was already initialized above!
 * >>     movq   $LFUTEX_WAKE,                  %rsi
 * >>     movq   $1,                            %rdx
 * >> #if EXCEPT_ENABLED
 * >>     std
 * >>     .cfi_escape 56,22,49,7,146,49,0,11,255,251,26  # Disable EFLAGS.DF during unwind & landing
 * >>     syscall
 * >>     cld
 * >>     .cfi_escape 57
 * >> #else // EXCEPT_ENABLED
 * >>     syscall
 * >> #endif // !EXCEPT_ENABLED
 * >> #else // __x86_64__
 * >>     pushl_cfi %ebx
 * >>     .cfi_escape DW_CFA_GNU_args_size, 4
 * >>     leal   service_shm::s_commands(%Pcx), %ebx   # NOTE: %Pcx was already initialized above!
 * >>     movl   $LFUTEX_WAKE,                  %ecx
 * >>     movl   $1,                            %edx
 * >> #if EXCEPT_ENABLED
 * >>     call   __i386_Xsyscall
 * >> #else // EXCEPT_ENABLED
 * >>     call   __i386_syscall
 * >> #endif // !EXCEPT_ENABLED
 * >>     popl_cfi %ebx
 * >>     .cfi_escape DW_CFA_GNU_args_size, 0
 * >> #endif // !__x86_64__
 * >>     # No need to check for errors here: There
 * >>     # should be no reason for the above to fail!
 * >>
 * >>
 * >>
 * >> // Wait for the command to complete
 * >>     #     futex_waitwhile(&com->sc_code, <info->dl_comid>)
 * >>     # <=> syscall(SYS_lfutx, &com->sc_code, LFUTEX_WAIT_WHILE, <info->dl_comid>)
 * >> .Lwaitfor_completion:
 * >>     movP   $SYS_lfutex, %Pax
 * >> #ifdef __x86_64__
 * >>     leaq   service_com::sc_code(%R_service_com), %rdi
 * >>     movq   $LFUTEX_WAIT_WHILE,                   %rsi
 * >>     movq   $<info->dl_comid>,                    %rdx
 * >> #if EXCEPT_ENABLED
 * >>     std
 * >>     .cfi_escape 56,22,49,7,146,49,0,11,255,251,26  # Disable EFLAGS.DF during unwind & landing
 * >>     syscall
 * >>     cld
 * >>     .cfi_escape 57
 * >> #else // EXCEPT_ENABLED
 * >>     syscall
 * >> #endif // !EXCEPT_ENABLED
 * >> #else // __x86_64__
 * >>     pushl_cfi %ebx
 * >>     .cfi_escape DW_CFA_GNU_args_size, 4
 * >>     leaq   service_com::sc_code(%R_service_com), %ebx
 * >>     movl   $LFUTEX_WAIT_WHILE,                   %ecx
 * >>     movl   $<info->dl_comid>,                    %edx
 * >> #if EXCEPT_ENABLED
 * >>     call   __i386_Xsyscall
 * >> #else // EXCEPT_ENABLED
 * >>     call   __i386_syscall
 * >> #endif // !EXCEPT_ENABLED
 * >>     popl_cfi %ebx
 * >>     .cfi_escape DW_CFA_GNU_args_size, 0
 * >> #endif // !__x86_64__
 * >> #if !EXCEPT_ENABLED
 * >>     cmpP   $(-ELIMIT), %Pax
 * >>     ja     .Lerr_com_abort_errno
 * >> #endif // !EXCEPT_ENABLED
 * >>     # Check if the operation has completed
 * >>     cmpP   $<info->dl_comid>, service_com::sc_code(%R_service_com)
 * >>     je     .Lwaitfor_completion
 * >>
 * >>
 * >>
 * >> .Leh_com_waitfor_end:
 * >>
 * >>
 * >>
 * >> // Deserialize fixed-length inline buffers
 * >> {foreach[INLINE_INOUT_OUT_BUFFER_ARGUMENT: <INLINE_BUFFERS_OFFSET>, <INLINE_BUFFER_SIZE>, <PARAM_OFFSET>]: {
 * >> #if ARGUMENT_USES_MOVS_FOR_COPY
 * >>     leaP   INLINE_BUFFERS_OFFSET(%R_service_com), %Psi # This instruction is skipped if `Psi' already has the
 * >>                                                        # correct value, which may be the case if a preceding
 * >>                                                        # inline buffer already set it up correctly.
 * >>     movP   PARAM_OFFSET(%Psp),                    %Pdi
 * >>     movP   $INLINE_BUFFER_SIZE,                   %Pcx
 * >>     rep    movsb
 * >> #else // ARGUMENT_USES_MOVS_FOR_COPY
 * >>     movP   PARAM_OFFSET(%Psp), %Pcx
 * >>     {INLINE_MEMCPY(_OFF, _BWLQ, INLINE_BUFFER_SIZE) {
 * >>         mov{_BWLQ} INLINE_BUFFERS_OFFSET+_OFF(%R_service_com), %{_BWLQ}ax
 * >>         mov{_BWLQ} %{_BWLQ}ax,                                 _OFF(%Pcx)
 * >>     }}
 * >> #endif // !ARGUMENT_USES_MOVS_FOR_COPY
 * >> }}
 * >>
 * >>
 * >>
 * >> // Copy out-of-band inout/out buffers into user-provided storage
 * >> #if INOUT_BUF_PARAM_COUNT != 0 || OUT_BUF_PARAM_COUNT != 0
 * >>     # Load %Psi with the SHM address of the first out-of-band inout/out buffer
 * >>     # NOTE: We unconditionally use %Psi for copying!
 * >> #if IN_BUF_PARAM_COUNT != 0
 * >>     movP   LOC_outbuffers_start(%Psp), %Psi
 * >> #else // IN_BUF_PARAM_COUNT != 0
 * >>     movP   LOC_bufpar_ptr(%Psp), %Psi
 * >> #endif // IN_BUF_PARAM_COUNT == 0
 * >>
 * >>     # Copy out-of-band SHM buffers for inout/out arguments back to user-memory
 * >> {foreach[INOUT_OUT_BUFFER_ARGUMENT: <INDEX>, <PARAM_OFFSET>, <SERIAL_OFFSET>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles'
 * >>     cmpP   $0, LOC_bufparam_handles[INDEX](%Psp)
 * >>     jne    1f
 * >>     movP   PARAM_OFFSET(%Psp), %Pdi                 # Unconditionally use %Psi for copying!
 * >>     movP   ...,                %Pcx                 # required buffer size (depending on buffer type)
 * >>     rep    movsb
 * >> #if ...
 * >>     addP   $..., %Psi  # When this isn't the last inout/out buffer that needs to be copied,
 * >>                        # but the copy size loaded into %Pcx above is less than what was
 * >>                        # allocated for the buffer prior to the call (iow: the buffer has the
 * >>                        # `SERVICE_OUT_SIZEARG_RETURN_MINVAL' flag set), then adjust the source
 * >>                        # pointer to load data from the correct location at the start of the
 * >>                        # next buffer.
 * >> #endif
 * >> 1:
 * >> }}
 * >> #endif // INOUT_BUF_PARAM_COUNT != 0 || OUT_BUF_PARAM_COUNT != 0
 * >>
 * >>
 * >>
 * >> #if BUF_PARAM_COUNT != 0
 * >> // Free the xbuf buffer
 * >> .Leh_free_xbuf_end:
 * >>     movP   LOC_bufpar_ptr(%Psp), %Pdx
 * >>     testP  %Pdx, %Pdx
 * >>     jz     1f
 * >>     subP   $<sizeof(size_t)>, %Pdx
 * >> #ifdef __x86_64__
 * >>     movP   0(%Pdx), %Pcx
 * >> #else // __x86_64__
 * >>     pushP_cfi 0(%Pdx)
 * >>     pushP_cfi %Pdx
 * >> #endif // !__x86_64__
 * >>     movP   LOC_bufpar_shm(%Psp),    %R_fcall1P
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >>     movP   LOC_upm(%Psp), %Pax
 * >>     movP   $ss_full, userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >>     call   libservice_shmbuf_freeat_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__
 * >> 1:
 * >> #endif // BUF_PARAM_COUNT != 0
 * >>
 * >>
 * >>
 * >> // Free the com buffer
 * >> .Leh_free_service_com_end:
 * >>     subP   $<sizeof(size_t)>, %R_service_com
 * >> #ifdef __x86_64__
 * >>     movq   0(%R_service_com), %rcx
 * >>     movq   %R_service_com,    %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi 0(%R_service_com)
 * >>     pushl_cfi %R_service_com
 * >> #endif // !__x86_64__
 * >>     movP   %R_service_shm_handle, %R_fcall1P
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >> #ifdef __x86_64__
 * >>     movq   service_com::sc_retval::scr_rax+<sizeof(size_t)>(%R_service_com), %rbp # Load return values
 * >> #else // __x86_64__
 * >>     movl   service_com::sc_retval::scr_eax+<sizeof(size_t)>(%R_service_com), %ebp # Load return values
 * >>     movl   service_com::sc_retval::scr_edx+<sizeof(size_t)>(%R_service_com), %ebx # *ditto*
 * >> #endif // !__x86_64__
 * >> #if BUF_PARAM_COUNT == 0
 * >>     movP   LOC_upm(%Psp), %Pax
 * >>     movP   $ss_full, userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >> #endif // BUF_PARAM_COUNT == 0
 * >>     call   libservice_shmbuf_freeat_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__
 * >>
 * >>
 * >>
 * >> // Restore preemption
 * >> .Leh_preemption_pop_end:
 * >>     popP_cfi %Pdx              # `sigset_t *oldset'
 * >>     popP_cfi %Pax              # `struct userprocmask *upm'
 * >>     .cfi_remember_state
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    .Lcheck_signals_before_return
 * >> .Lafter_check_signals_before_return:
 * >> #ifdef __x86_64__
 * >>     # local variables + register argument storage After this, %Psp
 * >>     # points at the first registers which needs to be restored.
 * >>     addP   $<cg_locvar_size + (MIN(PARAM_COUNT, 6) * 8)>, %Psp
 * >>     .cfi_adjust_cfa_offset -<cg_locvar_size + (MIN(PARAM_COUNT, 6) * 8)>
 * >> #else // __x86_64__
 * >>     addP   $<cg_locvar_size>, %Psp        # local variables
 * >>     .cfi_adjust_cfa_offset -<cg_locvar_size>
 * >> #endif // !__x86_64__
 * >> #ifdef __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_R12
 * >>     popP_cfi_r %r12        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_R12
 * >> #else // __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_EDI
 * >>     popP_cfi_r %Pdi        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_EDI
 * >> #if COM_GENERATOR_FEATURE_USES_ESI
 * >>     popP_cfi_r %Psi        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_ESI
 * >> #endif // !__x86_64__
 * >>
 * >>
 * >>
 * >> // Set return values
 * >> #ifdef __x86_64__
 * >>     movq   %rbp, %rax
 * >> #else // __x86_64__
 * >>     movl   %ebp, %eax
 * >>     movl   %ebx, %edx
 * >> #endif // !__x86_64__
 * >>
 * >>
 * >>
 * >> // Normal return
 * >>     popP_cfi_r %Pbx
 * >>     popP_cfi_r %Pbp
 * >>     ret
 * >>
 * >>
 * >>
 * >>     .cfi_restore_state
 * >> .Lcheck_signals_before_return:
 * >>     call   chkuserprocmask
 * >>     jmp    .Lafter_check_signals_before_return
 * >>     .cfi_restore_state
 * >>
 * >>
 * >>
 * >>
 * >>
 * >> #if BUF_PARAM_COUNT == 0
 * >> .Ltest_pending_signals_after_com_buffer_alloc:
 * >>     call   chkuserprocmask
 * >>     jmp    .Ltest_pending_signals_after_com_buffer_alloc_return
 * >> #elif BUF_PARAM_COUNT == 1
 * >> .Ltest_pending_signals_after_single_buffer_alloc:
 * >>     call   chkuserprocmask
 * >>     jmp    .Ltest_pending_signals_after_single_buffer_alloc_return
 * >> .Ltest_pending_signals_after_single_buffers_is_in_band:
 * >>     pushP_cfi_r %Pax
 * >>     call   chkuserprocmask
 * >>     popP_cfi_r %Pax
 * >>     jmp .Ltest_pending_signals_after_single_buffers_is_in_band_return
 * >> #else // #elif BUF_PARAM_COUNT >= 2
 * >> #if IN_BUF_ARGUMENT_COUNT != 0 || INOUT_BUF_PARAM_COUNT != 0
 * >> .Ltest_pending_signals_after_xbuf_alloc:
 * >>     pushP_cfi_r %Pax
 * >>     pushP_cfi_r %Pdx
 * >>     call   chkuserprocmask
 * >>     popP_cfi_r %Pdx
 * >>     popP_cfi_r %Pax
 * >>     jmp .Ltest_pending_signals_after_xbuf_alloc_return
 * >> #endif // IN_BUF_ARGUMENT_COUNT != 0 || INOUT_BUF_PARAM_COUNT != 0
 * >> .Ltest_pending_signals_after_all_buffers_are_in_band:
 * >>     call   chkuserprocmask
 * >>     jmp    .Lall_buffers_are_in_band_preemption_reenabled:
 * >> #endif // #endif BUF_PARAM_COUNT >= 2
 * >>
 * >>
 * >>
 * >>
 * >>
 * >> #if !EXCEPT_ENABLED
 * >> .Lerr_com_abort_errno:
 * >>     negP   %Pax
 * >>     movP   %Pax, %R_fcall0P
 * >>     call   __set_errno_f
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >>     movP   %R_service_com,          %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movP   $<info->dl_comid>, %rdx
 * >> #else // __x86_64__
 * >>     pushP_cfi $<info->dl_comid>
 * >> #endif // !__x86_64__
 * >>     call   libservice_aux_com_abort
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -4
 * >> #endif // !__x86_64__
 * >>     testb  %al, %al                   # Check if command completed before it could be aborted
 * >>     jz     .Leh_free_service_com_end  # if (COMPLETED_BEFORE_ABORT) goto .Leh_free_service_com_end;
 * >>     SET_ERROR_RETURN_VALUE()
 * >>     jmp    .Leh_free_service_com_end
 * >>
 * >> //NEVER_USED:#if BUF_PARAM_COUNT != 0
 * >> //NEVER_USED:.Lerr_free_xbuf:
 * >> //NEVER_USED:    SET_ERROR_RETURN_VALUE()
 * >> //NEVER_USED:    jmp   .Leh_free_xbuf_end
 * >> //NEVER_USED:#endif // BUF_PARAM_COUNT != 0
 * >>
 * >> .Lerr_free_service_com:
 * >>     SET_ERROR_RETURN_VALUE()
 * >>     jmp   .Leh_free_service_com_end
 * >>
 * >> .Lerr_pop_preemption:
 * >>     SET_ERROR_RETURN_VALUE()
 * >>     jmp   .Leh_preemption_pop_end
 * >> #endif // !EXCEPT_ENABLED
 * >>
 * >>
 * >>
 * >>
 * >> // Remove command from wait queue on interrupt
 * >> .Leh_com_waitfor_entry:
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >>     movP   %R_service_com,          %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movP   $<info->dl_comid>, %rdx
 * >> #else // __x86_64__
 * >>     pushP_cfi $<info->dl_comid>
 * >> #endif // !__x86_64__
 * >>     call   libservice_aux_com_abort
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -4
 * >> #endif // !__x86_64__
 * >>     testb  %al, %al   # Check if command completed before it could be aborted
 * >>     jnz    1f         # if (ABORTED) goto 1f;
 * >>     call   libservice_aux_com_discard_nonrt_exception # Try to clear non-RT exceptions
 * >>     testb  %al, %al
 * >>     jnz    .Leh_com_waitfor_end
 * >>1:   // fallthru...
 * >>
 * >>
 * >>
 * >> // Except handler to free xbuf
 * >> .Leh_free_xbuf_entry:
 * >>     movP   LOC_bufpar_ptr(%Psp), %Pdx
 * >>     testP  %Pdx, %Pdx
 * >>     jz     1f
 * >>     subP   $<sizeof(size_t)>, %Pdx
 * >> #ifdef __x86_64__
 * >>     movP   0(%Pdx), %Pcx
 * >> #else // __x86_64__
 * >>     pushP_cfi 0(%Pdx)
 * >>     pushP_cfi %Pdx
 * >> #endif // !__x86_64__
 * >>     movP   LOC_bufpar_shm(%Psp),    %R_fcall1P
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >>     call   libservice_shmbuf_freeat_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__
 * >> 1:  // fallthru...
 * >>
 * >>
 * >>
 * >> // Except handler to free the service com
 * >> .Leh_free_service_com_entry:
 * >>     subP   $<sizeof(size_t)>, %R_service_com
 * >> #ifdef __x86_64__
 * >>     movq   0(%R_service_com), %rcx
 * >>     movq   %R_service_com,    %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi 0(%R_service_com)
 * >>     pushl_cfi %R_service_com
 * >> #endif // !__x86_64__
 * >>     movP   %R_service_shm_handle, %R_fcall1P
 * >>     movP   $<struct service *self>, %R_fcall0P
 * >>     call   libservice_shmbuf_freeat_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__
 * >>     // fallthru...
 * >>
 * >>
 * >>
 * >> // Except handler to restore preemption
 * >> .Leh_preemption_pop_entry:
 * >>     popP_cfi %Pdx              # `sigset_t *oldset'
 * >>     popP_cfi %Pax              # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     call   chkuserprocmask
 * >> #ifdef __x86_64__
 * >>     xorq   %rdi, %rdi
 * >> #else // __x86_64__
 * >>     pushl_cfi $0
 * >> #endif // !__x86_64__
 * >>     call   _Unwind_Resume
 * >>     .cfi_endproc
 * ================================================================================================
 *
 */


/* Flags for `com_inline_buffer_param::cibp_flags' */
#define COM_INLINE_BUFFER_PARAM_FIN    0x01 /* FLAG: In buffer */
#define COM_INLINE_BUFFER_PARAM_FOUT   0x02 /* FLAG: Out buffer */
#define COM_INLINE_BUFFER_PARAM_FMOVS  0x04 /* FLAG: Use `movs' for copying buffer contents */
struct com_inline_buffer_param {
	byte_t   cibp_param_index;   /* [const] Parameter index in `:cg_info.dl_params' */
	byte_t   cibp_flags;         /* [const] Parameter flags (set of `COM_INLINE_BUFFER_PARAM_F*') */
	int16_t  cibp_param_offset;  /* [const] Offset from CFA to where this parameter is stored in memory */
	uint16_t cibp_serial_offset; /* [const] Offset from `struct service_com' to where the address of this buffer is saved */
	uint16_t cibp_sizeof;        /* [const][== (:cg_info.dl_params[cibp_param_index] & _SERVICE_TYPE_PARAMMASK)]
	                              * Fixed sizeof this buffer parameter */
};


/* Flags for `com_buffer_param::cbp_flags' */
#define COM_BUFFER_PARAM_FIN    0x01 /* FLAG: In buffer */
#define COM_BUFFER_PARAM_FOUT   0x02 /* FLAG: Out buffer */

struct com_buffer_param {
	byte_t   cbp_param_index;   /* [const] Parameter index in `:cg_info.dl_params' */
	byte_t   cbp_flags;         /* [const] Parameter flags (set of `COM_BUFFER_PARAM_F*') */
	int16_t  cbp_param_offset;  /* [const] Offset from CFA to where this parameter is stored in memory:
	                             * >> value = *(void **)(%Psp + cg_cfa_offset + cbp_param_offset); */
	uint16_t cbp_serial_offset; /* [const] Offset from `struct service_com' to where the address of this buffer is saved */
};

/* Flags for `struct com_generator::cg_features' */
#define COM_GENERATOR_FEATURE_FNORMAL                       0x00 /* Normal flags. */
#define COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_LODS 0x01 /* Use `lodsP' to load non-buffer arguments */
#define COM_GENERATOR_FEATURE_NONBUFFER_ARGUMENTS_USES_STOS 0x02 /* Use `stosP' to write non-buffer arguments */
#ifdef __x86_64__
#define COM_GENERATOR_FEATURE_USES_R12 0x80 /* %r12 is used and must be saved/restored */
#else /* __x86_64__ */
#define COM_GENERATOR_FEATURE_USES_EDI 0x40 /* %edi is used and must be saved/restored */
#define COM_GENERATOR_FEATURE_USES_ESI 0x80 /* %esi is used and must be saved/restored */
#endif /* !__x86_64__ */


struct com_generator {
	byte_t                     *cg_txptr;                /* [1..1][<= cg_txend] .text writer pointer */
	byte_t                     *cg_ehptr;                /* [1..1][<= cg_ehend] .eh_frame writer pointer */
	byte_t                     *cg_txend;                /* [1..1][const] .text buffer end pointer */
	byte_t                     *cg_ehend;                /* [1..1][const] .eh_frame buffer end pointer */
	struct service_com_funinfo  cg_info;                 /* [const] Function information. */
	intptr_t                    cg_cfa_offset;           /* Current offset to-be applied to %Psp to find CFA
	                                                      * All stack-offset variables are actually relative
	                                                      * to CFA, and  cg_cfa_offset itself always  points
	                                                      * just after the return-PC:
	                                                      * >> RETURN_PC == ((void **)(%Psp + cg_cfa_offset))[-1]; */
	intptr_t                    cg_locvar_offset;        /* [const] Offset from CFA to the start of local variables */
	size_t                      cg_locvar_size;          /* [const] Total size of the local variables area */
	struct com_inline_buffer_param cg_inline_buffer_paramv[SERVICE_ARGC_MAX];
	                                                     /* [cg_inline_buffer_paramc] Fixed-length inline buffers */
	struct com_buffer_param     cg_buffer_paramv[SERVICE_ARGC_MAX];
	                                                     /* [cg_buffer_paramc] Buffer parameters. Sorted by
	                                                      * buffer type in  order of `in, inout, out'.  Out
	                                                      * buffers with  SERVICE_OUT_SIZEARG_RETURN_MINVAL
	                                                      * come after those without. */
	byte_t                      cg_inline_buffer_paramc; /* [const] # of inline buffer parameters */
	byte_t                      cg_buffer_paramc;        /* [const] # of buffer parameters */
	byte_t                      cg_inbuf_paramc;         /* [const] # of in-buffer parameters     (cg_buffer_paramv[0..cg_inbuf_paramc-1]) */
	byte_t                      cg_inoutbuf_paramc;      /* [const] # of inout-buffer parameters  (cg_buffer_paramv[cg_inbuf_paramc..cg_inoutbuf_paramc+cg_inbuf_paramc-1]) */
	byte_t                      cg_outbuf_paramc;        /* [const] # of out-buffer parameters    (cg_buffer_paramv[cg_inoutbuf_paramc+cg_inbuf_paramc..cg_inoutbuf_paramc+cg_inbuf_paramc+cg_outbuf_paramc-1]) */
	byte_t                      cg_features;             /* [const] Code features (set of `COM_GENERATOR_FEATURE_F*') */
};

/* Helper macros for generating offsets */
#define com_generator_spoffsetof_LOCALS(self)     ((self)->cg_cfa_offset + (self)->cg_locvar_offset)
#define com_generator_spoffsetof_LOC_oldset(self) (com_generator_spoffsetof_LOCALS(self) + 0)                  /* sigset_t *LOC_oldset; */
#define com_generator_spoffsetof_LOC_upm(self)    (com_generator_spoffsetof_LOCALS(self) + __SIZEOF_POINTER__) /* struct userprocmask *LOC_upm; */


// #if BUF_PARAM_COUNT != 0
//                                         # [0..1] Non-shm buffer temporary storage
//      CFA-cg_locvar_offset+2*P           void *LOC_bufpar_ptr;
//
//                                         # [1..1][valid_if(LOC_bufpar_ptr)] SHM for `LOC_bufpar_ptr'
//      CFA-cg_locvar_offset+3*P           REF struct service_shm_handle *LOC_bufpar_shm;
//
//                                         # [0..1][*] SHM handles for user buffers (NULL for buffers that need to be copied)
//      CFA-cg_locvar_offset+4*P           struct service_shm_handle *LOC_bufparam_handles[BUF_PARAM_COUNT];
//
//                                         # [0..1][*] SHM handles for user buffers (NULL for buffers that need to be copied)
// #if IN_BUF_PARAM_COUNT != 0 && (INOUT_BUF_PARAM_COUNT != 0 || OUT_BUF_PARAM_COUNT != 0)
//      CFA-cg_locvar_offset+...           byte_t *LOC_outbuffers_start; # [1..1] Base address for output buffers (see below)
// #endif // IN_BUF_PARAM_COUNT != 0 && (INOUT_BUF_PARAM_COUNT != 0 || OUT_BUF_PARAM_COUNT != 0)
// #endif // BUF_PARAM_COUNT != 0






/* When the currently set exception is RT-level, return `false'.
 * Otherwise,   clear   the   exception   and   return   `true'. */
INTDEF bool NOTHROW(FCALL libservice_aux_com_discard_nonrt_exception)(void);




DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_H */
