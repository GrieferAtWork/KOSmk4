/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#include <stdbool.h>
#include <stdint.h>

#include <libgen86/gen.h> /* GEN86_INSTRLEN_MAX */

#include "../../com.h"

DECL_BEGIN

#ifdef __x86_64__
/* Alter the call generator macro such that it will compile code as
 * >> movabs $addr, %rax
 * >> call   *%rax
 * ... when the delta between `*p_pc' and `addr' is too large. */
#undef gen86_call
#define gen86_call(p_pc, addr)                                 \
	do {                                                       \
		int64_t _c_delta = (int64_t)((uint64_t)(addr) -        \
		                             (uint64_t)(*(p_pc) + 5)); \
		if (_gen86_fitsl(_c_delta)) {                          \
			gen86_call_offset(p_pc, (int32_t)_c_delta);        \
		} else {                                               \
			gen86_movabs_imm_r(p_pc, addr, GEN86_R_RAX);       \
			gen86_callP_mod(p_pc, gen86_modrm_r, GEN86_R_RAX); \
		}                                                      \
	}	__WHILE0
#endif /* __x86_64__ */



/*
 * Function arguments are serialized (and deserialized) as follows:
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
 * Where:
 *   - putl writes a 32-bit word
 *   - putq writes a 64-bit word
 *   - putP writes a pointer-sized word
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


/* ================================================================================================
 * Buffer   argument   indices   are    calculated   as   follows   (s.a.    LOC_bufparam_handles):
 *   - All fixed-length buffers with a fixed data size <= COM_FIXBUF_INLINE_THRESHOLD
 *     are   moved   into    a   separate    buffer   list    `cg_inline_buf_paramv'.
 *   - Take the list of all parameters that operate on buffers
 *   - Sort such such that buffers are ordered as in,inout,out
 *   - All  out/inout  buffers that  have `SERVICE_OUT_SIZEARG_RETURN_MINVAL',
 *     are moved to the back of their respective sub-list of buffers elements.
 *   - Positions within the resulting list are used as buffer indices within
 *     generated code.
 *   - cg_inline_buf_paramc: # of buffer arguments in `cg_inline_buf_paramv'
 *   - cg_buf_paramc:        # of buffer arguments
 *   - cg_inbuf_paramc:      # of in buffers (== index of first inout buffer)
 *   - cg_inoutbuf_paramc:   # of inout buffers
 *   - cg_outbuf_paramc:     # of out buffers
 * ================================================================================================
 *
 *
 *
 * ================================================================================================
 * The stack-frame of a wrapper function looks like this:
 *
 * ------------------------------------------------------------------------------------------------
 *      {SP-RELATIVE OFFSET}               {CONTENTS}
 * ------------------------------------------------------------------------------------------------
 *      CFA-cg_locvar_offset               [<start of locals>]
 *      CFA-cg_locvar_offset+0*P           sigset_t *LOC_oldset;                   # [1..1] Old signal maks pointer
 *      CFA-cg_locvar_offset+1*P           struct userprocmask *LOC_upm;           # [1..1] Return value of `getuserprocmask()'
 *      CFA-cg_locvar_offset+2*P           REF struct service_shm_handle *LOC_shm; # [1..1] SHM for `R_service_com'
 *
 * #if cg_buf_paramc != 0
 *      CFA-cg_locvar_offset+3*P           void                          *LOC_bufpar_ptr;                        # [0..1] Non-shm buffer temporary storage
 *      CFA-cg_locvar_offset+4*P           REF struct service_shm_handle *LOC_bufpar_shm;                        # [1..1][valid_if(LOC_bufpar_ptr)] SHM for `LOC_bufpar_ptr'
 *      CFA-cg_locvar_offset+5*P           struct service_shm_handle     *LOC_bufparam_handles[cg_buf_paramc]; # [0..1][*] SHM handles for user buffers (NULL for buffers that need to be copied)
 * #if cg_inbuf_paramc != 0 && (cg_inoutbuf_paramc != 0 || cg_outbuf_paramc != 0) && !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 *      CFA-cg_locvar_offset+...           byte_t *LOC_outbuffers_start; # [1..1] Base address for inout/out buffers (see below)
 * #endif // cg_inbuf_paramc != 0 && (cg_inoutbuf_paramc != 0 || cg_outbuf_paramc != 0) && !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * #endif // cg_buf_paramc != 0
 *
 *      CFA-cg_locvar_offset+cg_locvar_size [<end of locals>]
 *
 * #ifdef __x86_64__
 *  /   CFA-9*P                            REGPAR: %rdi        # Only if cg_paramc >= 1  (NOT RESTORED!)
 *  |   CFA-8*P                            REGPAR: %rsi        # Only if cg_paramc >= 2  (NOT RESTORED!)
 *  |   CFA-7*P                            REGPAR: %rdx        # Only if cg_paramc >= 3  (NOT RESTORED!)
 *  |   CFA-6*P                            REGPAR: %rcx        # Only if cg_paramc >= 4  (NOT RESTORED!)
 *  |   CFA-5*P                            REGPAR: %r8         # Only if cg_paramc >= 5  (NOT RESTORED!)
 *  \   CFA-4*P                            REGPAR: %r9         # Only if cg_paramc >= 6  (NOT RESTORED!)
 *  -   CFA-3*P                            SAVED: %rbx         # Only if `COM_GENERATOR_FEATURE_USES_RBX' (restored on exit)
 * #else // __x86_64__
 *  /   CFA-5*P                            SAVED: %Pdi         # Only if `COM_GENERATOR_FEATURE_USES_EDI' (restored on exit)
 *  |   CFA-4*P                            SAVED: %Psi         # Only if `COM_GENERATOR_FEATURE_USES_ESI' (restored on exit)
 *  \   CFA-3*P                            SAVED: %Pbx         # %Pbx is needed for system calls
 * #endif // !__x86_64__
 *  \   CFA-2*P                            SAVED: %Pbp         # %Pbp is used for `struct service_comdesc *R_service_com'
 *  -   CFA-1*P                            RETURN_PC
 *  /   CFA                                [STACK_ARG[0]]
 *  |   CFA+1*P                            [STACK_ARG[1]]
 *  |                                       ...
 *  \   CFA+n*P                            [STACK_ARG[n]]
 * ------------------------------------------------------------------------------------------------
 * Where CFA == %Psp + cg_cfa_offset   (and `cg_cfa_offset' is adjusted as %Psp is altered)
 * Where P   == sizeof(void *)
 * ================================================================================================
 *
 *
 *
 * ================================================================================================
 * ALLOC_SIZE is calculated as:
 *      offsetof(struct service_comdesc, scd_com.sc_generic.g_data)
 *    + cg_paramc * sizeof(uintptr_t)                             # Every parameter has (at least) 1 serial word
 * #ifndef __x86_64__
 *    + PARAM_COUNT_OF(SERVICE_TYPE_386_R64) * sizeof(uintptr_t)  # On i386, 64-bit arguments take 2 serial words
 * #endif // !__x86_64__
 *    + SUM(cg_inline_buf_paramv.each.buffer_size.ceil_align(SERVICE_BUFFER_ALIGNMENT)) # Inline buffers are allocated within com
 * Afterwards, apply the size requirements detailed in `libservice_shmbuf_alloc_nopr()'
 * to the calculated size to generate the effective allocation size. The unadjusted
 * value is stored in `cg_sizeof_service_com'
 *
 * <cibp_buffer_offset> is calculated as:
 *      offsetof(struct service_comdesc, scd_com.sc_generic.g_data)
 *    + cg_paramc * sizeof(uintptr_t)
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
 *   - COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS  # Use `lodsP' to load integer parameters from the stack
 *   - COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS  # Use `stosP' to write integer parameters to SHM
 *   - COM_GENERATOR_FEATURE_USES_RBX             # x86_64-only: Set when %rbx is used by the implementation
 *   - COM_GENERATOR_FEATURE_USES_EDI             # i386-only:   Set when %edi is used by the implementation
 *   - COM_GENERATOR_FEATURE_USES_ESI             # i386-only:   Set when %esi is used by the implementation
 * ================================================================================================
 *
 *
 *
 * ================================================================================================
 * Wrapper functions are implemented as follows:
 * WARNING: The below documentation isn't an aproximation; it is the _real_ _thing_!
 *          Any modification made below _MUST_  be mirrored in the appropriate  code
 *          generation  sub-routines. If the two ever fall  out of sync too much, it
 *          might become impossible to navigate and update either!
 *
 * >>
 * >> #ifdef __x86_64__
 * >> #define SET_ERROR_RETURN_VALUE() \
 * >>     movq   $<cg_info.dl_error_return.scr_rax>, service_comdesc::scd_com::sc_retval::scr_rax(%R_service_com)
 * >> #else // __x86_64__
 * >> #define SET_ERROR_RETURN_VALUE()                                                                                \
 * >>     #if cg_info.dl_return == SERVICE_TYPE_386_R64                                                               \
 * >>         movl   $<cg_info.dl_error_return.scr_edx>, service_comdesc::scd_com::sc_retval::scr_edx(%R_service_com) \
 * >>     #endif // cg_info.dl_return == SERVICE_TYPE_386_R64                                                         \
 * >>     movl   $<cg_info.dl_error_return.scr_eax>, service_comdesc::scd_com::sc_retval::scr_eax(%R_service_com)
 * >> #endif // !__x86_64__
 * >>
 * >>
 * >> ENTRY:
 * >>     .cfi_startproc
 * >>     .cfi_def_cfa_offset 0
 * >>
 * >> // Save registers & allocate stack space
 * >>     pushP_cfi_r %Pbp        # %Pbp is used for `struct service_comdesc *R_service_com'
 * >> #ifdef __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_RBX
 * >>     pushP_cfi_r %rbx        # Only if used anywhere below (restored on exit)
 * >> #endif // COM_GENERATOR_FEATURE_USES_RBX
 * >> #if cg_paramc >= 6
 * >>     pushP_cfi %r9           # Only if cg_paramc >= 6  (NOT RESTORED!)
 * >> #endif // cg_paramc >= 6
 * >> #if cg_paramc >= 5
 * >>     pushP_cfi %r8           # Only if cg_paramc >= 5  (NOT RESTORED!)
 * >> #endif // cg_paramc >= 5
 * >> #if cg_paramc >= 4
 * >>     pushP_cfi %rcx          # Only if cg_paramc >= 4  (NOT RESTORED!)
 * >> #endif // cg_paramc >= 4
 * >> #if cg_paramc >= 3
 * >>     pushP_cfi %rdx          # Only if cg_paramc >= 3  (NOT RESTORED!)
 * >> #endif // cg_paramc >= 3
 * >> #if cg_paramc >= 2
 * >>     pushP_cfi %rsi          # Only if cg_paramc >= 2  (NOT RESTORED!)
 * >> #endif // cg_paramc >= 2
 * >> #if cg_paramc >= 1
 * >>     pushP_cfi %rdi          # Only if cg_paramc >= 1  (NOT RESTORED!)
 * >> #endif // cg_paramc >= 1
 * >> #else // __x86_64__
 * >>     pushP_cfi_r %Pbx        # %Pbx is needed for system calls
 * >> #if COM_GENERATOR_FEATURE_USES_ESI
 * >>     pushP_cfi_r %Psi        # Only if used anywhere below (restored on exit)
 * >> #endif // COM_GENERATOR_FEATURE_USES_ESI
 * >> #if COM_GENERATOR_FEATURE_USES_EDI
 * >>     pushP_cfi_r %Pdi        # Only if used anywhere below (restored on exit)
 * >> #endif // COM_GENERATOR_FEATURE_USES_EDI
 * >> #endif // !__x86_64__
 * >>
 * >>     subP   $<cg_locvar_size - 2 * sizeof(void*)>, %Psp
 * >>     .cfi_adjust_cfa_offset <cg_locvar_size - 2 * sizeof(void*)>
 * >>
 * >> // Disable preemption
 * >>     call   getuserprocmask
 * >>     pushP_cfi %Pax                                  # LOC_upm
 * >>     pushP_cfi userprocmask::pm_sigmask(%Pax)        # LOC_oldset
 * >>     .cfi_remember_state
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset, %Pcx
 * >>     movP   %Pcx,         userprocmask::pm_sigmask(%Pax) # Disable preemption
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $full_sigset, userprocmask::pm_sigmask(%Pax) # Disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >> .Leh_preemption_pop_begin:
 * >>
 * >>
 * >> // Allocate the com buffer
 * >>     movP   $<cg_service>, %R_fcall0P   # Input constant (hard-coded)
 * >>     movP   $<ALLOC_SIZE>, %R_fcall1P   # Input constant (hard-coded)
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_pop_preemption
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, %R_service_com       # %R_service_com == %Pbx
 * >>     movP   %Pdx, LOC_shm(%Psp)
 * >> .Leh_free_service_com_begin:
 * >>
 * >>
 * >>
 * >> // Serialize buffer arguments (if they exist)
 * >> #if cg_buf_paramc == 0
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pax  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pax, userprocmask::pm_sigmask(%Pdx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_com_buffer_alloc
 * >> .Ltest_pending_signals_after_com_buffer_alloc_return:
 * >> #elif cg_buf_paramc == 1
 * >>     movP   $0, LOC_bufpar_ptr(%Psp)
 * >>     movP   $<cg_service>,                             %R_fcall0P
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[0](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jnz    .Lsingle_buffers_is_in_band
 * >> #if cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE_WITH_ADJUSTMENT>, %R_fcall1P
 * >> #else // cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   ..., %R_fcall1P  # Buffer size requirements of cg_buf_paramv[0]
 * >>                             # Allowed to clobber: %Pax, %Pcx, %Pdi, %Psi
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     movP   %R_fcall1P, %Psi    # Used by the out-of-band copy-in loop below!
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %Pax, %R_fcall1P   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #endif // !cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy an out-of-band in/inout buffer into SHM memory
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     movP   %Pax, %Pdi # Unconditionally use %Pdi for copying!
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >>     subP   service_shm_handle::ssh_shm(%Pdx), %Pax
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pcx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pdx  # `struct userprocmask *upm'
 * >>     movP   %Pcx, userprocmask::pm_sigmask(%Pdx)
 * >>     movP   %Pax, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pdx)
 * >>     jnz    .Ltest_pending_signals_after_single_buffer_alloc
 * >> .Ltest_pending_signals_after_single_buffer_alloc_return:
 * >> #if cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
 * >> #if cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   $<cg_buf_paramv[0].FIXED_BUFFER_SIZE>, %Pcx
 * >> #else // cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   %Psi,                                      %Pcx # This one was preserved above!
 * >> #endif // !cg_buf_paramv[0].HAS_FIXED_BUFFER_SIZE
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Psi # Unconditionally use %Psi for copying!
 * >>     rep    movsb
 * >> #endif // cg_buf_paramv[0].IS_IN_OR_INOUT_BUFFER
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
 * >>     # %Pax == libservice_shm_handle_ataddr_nopr(<cg_service>, <cg_buf_paramv[0].cbp_param_offset>(%Psp))
 * >>     movP   <cg_buf_paramv[0].cbp_param_offset>(%Psp), %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, <cg_buf_paramv[0].cbp_serial_offset>(%R_service_com)
 * >> .Lsingle_buffers_done:
 * >>
 * >> #else // #elif cg_buf_paramc >= 2
 * >>     # >> %R_temp_exbuf_size is %esi on i386 and %rbx on x86_64
 * >>     # NOTE: On x86_64, compilation getting here imples `COM_GENERATOR_FEATURE_USES_RBX'!
 * >>     xorP   %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     movP   %R_temp_exbuf_size, LOC_bufpar_ptr(%Psp)
 * >> {foreach[BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     movP   $<cg_service>,            %R_fcall0P
 * >>     movP   <cbp_param_offset>(%Psp), %R_fcall1P
 * >>     call   libservice_shm_handle_ataddr_nopr
 * >>     movP   %Pax, LOC_bufparam_handles[INDEX](%Psp)
 * >>     testP  %Pax, %Pax
 * >>     jz     1f
 * >>     movP   <cbp_param_offset>(%Psp),          %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pax), %Pdx
 * >>     movP   %Pdx, <cbp_serial_offset>(%R_service_com)
 * >>     jmp    2f
 * >> 1:  # NOTE: When only 1 buffer argument exists, %R_temp_exbuf_size isn't
 * >>     #       used and the allocated+initialization is done inline.
 * >>     addP   ..., %R_temp_exbuf_size  # Account for required buffer size (depending on buffer type)
 * >>                                     # NOTE: The buffer size calculated here must be ceil-aligned by SERVICE_BUFFER_ALIGNMENT,
 * >>                                     #       unless INDEX == self->cg_buf_paramc - 1, in which case this alignment
 * >>                                     #       is optional.
 * >>                                     # Allowed to clobber: %Pax, %Pcx, %Pdx, %Pdi (on i386, %Psi must be preserved!)
 * >> 2:
 * >> }}
 * >>     testP  %R_temp_exbuf_size, %R_temp_exbuf_size
 * >>     jz     .Lall_buffers_are_in_band
 * >>     movP   $<cg_service>,      %R_fcall0P
 * >>     movP   %R_temp_exbuf_size, %R_fcall1P
 * >>     addP   $(SERVICE_SHM_ALLOC_EXTRA + SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     andP   $~(SERVICE_SHM_ALLOC_ALIGN - 1), %R_fcall1P
 * >>     movP   $SERVICE_SHM_ALLOC_MINSIZE, %Pax
 * >>     cmpP   %Pax, %R_fcall1P   # if (%R_fcall1P < SERVICE_SHM_ALLOC_MINSIZE)
 * >>     cmovbP %Pax, %R_fcall1P   #     %R_fcall1P = SERVICE_SHM_ALLOC_MINSIZE;
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr_nx
 * >>     testP  %Pax, %Pax
 * >>     jz     .Lerr_free_service_com
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_shmbuf_alloc_nopr
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     movP   %Pax, LOC_bufpar_ptr(%Psp)
 * >>     movP   %Pdx, LOC_bufpar_shm(%Psp)
 * >> .Leh_free_xbuf_begin:
 * >>
 * >> // Copy out-of-band in/inout buffers into SHM memory
 * >> #if cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdi  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pcx  # `struct userprocmask *upm'
 * >>     movP   %Pdi, userprocmask::pm_sigmask(%Pcx)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pcx)
 * >>     jnz    .Ltest_pending_signals_after_xbuf_alloc
 * >> .Ltest_pending_signals_after_xbuf_alloc_return:
 * >>     movP   %Pax, %Pdi                               # Unconditionally use %Pdi for copying!
 * >>     movP   service_shm_handle::ssh_shm(%Pdx), %Pdx  # %Pdx is the base address of the out-of-band buffer SHM mapping
 * >> {foreach[IN_INOUT_BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>, <cbp_serial_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     cmpP   $0, LOC_bufparam_handles[INDEX](%Psp)
 * >>     jne    1f
 * >> #if cg_inbuf_paramc != 0 && cg_inoutbuf_paramc != 0 && cg_outbuf_paramc != 0
 * >> #if IS_FIRST_INOUT_BUFFER(INDEX) && !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif // IS_FIRST_INOUT_BUFFER(INDEX) && !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >> #endif // cg_inbuf_paramc != 0 && cg_inoutbuf_paramc != 0 && cg_outbuf_paramc != 0
 * >>
 * >>     # Set: %Pax = SHM_ADDR - SHM_BASE  (offset in SHM to input buffer)
 * >>     # NOTE: We don't have to about output buffers, since those appear after in/inout buffers
 * >>     movP   %Pdi, %Pax
 * >>     subP   %Pdx, %Pax
 * >>     movP   %Pax, <cbp_serial_offset>(%R_service_com) # Store SHM offset in serial data
 * >>
 * >>     movP   ...,                      %Pcx            # required buffer size (depending on buffer type)
 * >>                                                      # Allowed to clobber: %Pax, %Pdx, %Pcx, %Psi
 * >>     movP   <cbp_param_offset>(%Psp), %Psi            # Unconditionally use %Psi for copying!
 * >>     rep    movsb                                     # Copy input buffers into SHM
 * >> #if INDEX != cg_paramc - 1                           # If %Pdi will still be used, it must be re-aligned
 * >> #if cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #if !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT - (cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE & (SERVICE_BUFFER_ALIGNMENT - 1))>, %Pdi
 * >> #endif // !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >> #else // cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT-1>,    %Pdi
 * >>     andP   $<~(SERVICE_BUFFER_ALIGNMENT-1)>, %Pdi
 * >> #endif // !cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #endif // INDEX != cg_paramc - 1
 * >> 1:
 * >> }}
 * >> #if cg_inbuf_paramc != 0 && cg_inoutbuf_paramc == 0 && cg_outbuf_paramc != 0
 * >> #if !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   %Pdi, LOC_outbuffers_start(%Psp)         # `LOC_outbuffers_start' contains the start of the first inout/out buffer
 * >> #endif // !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >> #endif // cg_inbuf_paramc != 0 && cg_inoutbuf_paramc == 0 && cg_outbuf_paramc != 0
 * >>     jmp    .Lall_buffers_are_in_band_preemption_reenabled
 * >> #endif // cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >> .Lall_buffers_are_in_band:
 * >>     # Re-enable preemption
 * >>     movP   LOC_oldset(%Psp), %Pdx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pax  # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    .Ltest_pending_signals_after_all_buffers_are_in_band
 * >> .Lall_buffers_are_in_band_preemption_reenabled:
 * >> #endif // #endif cg_buf_paramc >= 2
 * >>
 * >>
 * >>
 * >>
 * >> // Serialize integer arguments (if they exist)
 * >> #if cg_int_paramc != 0
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >> #set _GENERATOR_VAR_Psi_offset = FIRST_NON_BUFFER_ARGUMENT.cip_param_offset  # Stack-offset of first argument
 * >>     leaP   <FIRST_NON_BUFFER_ARGUMENT.cip_param_offset>(%Psp), %Psi
 * >> #endif // COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >>
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >> #set _GENERATOR_VAR_Pdi_offset = FIRST_NON_BUFFER_ARGUMENT.cip_serial_offset # Serial-offset of first argument
 * >>     leaP   <FIRST_NON_BUFFER_ARGUMENT.cip_param_offset>(%Psp), %Pdi
 * >> #endif // COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >>
 * >> {foreach[NON_BUFFER_ARGUMENT: <cip_param_offset>, <cip_serial_offset>]: {
 * >>     # NOTE: cip_param_offset is the offset to the input parameter (from %Psp)
 * >>     # NOTE: cip_serial_offset is the offset in the serial stream (from %R_service_com)
 * >>     # NOTE: When both lodsP and stosP are used together, movsP may be generated instead!
 * >>
 * >>     # Load the argument value from the parameter-save or stack-argument area
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >> #if _GENERATOR_VAR_Psi_offset != cip_param_offset
 * >>     addP   $(<cip_param_offset - _GENERATOR_VAR_Psi_offset>), %Psi # Or subP
 * >> #endif
 * >>     lodsP
 * >> #set _GENERATOR_VAR_Psi_offset += sizeof(void *)
 * >> #else // COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >>     movP   <cip_param_offset>(%Psp), %Pax
 * >> #endif // !COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS
 * >>
 * >>     # Write the argument value to serial com data area
 * >> #if COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >> #if _GENERATOR_VAR_Pdi_offset != cip_serial_offset
 * >>     addP   $(<cip_serial_offset - _GENERATOR_VAR_Pdi_offset>), %Pdi # Or subP
 * >> #endif
 * >>     stosP
 * >> #set _GENERATOR_VAR_Pdi_offset += sizeof(void *)
 * >> #else // COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >>     movP   %Pax, <cip_serial_offset>(%R_service_com)
 * >> #endif // !COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS
 * >> }}
 * >> #endif // cg_int_paramc != 0
 * >>
 * >>
 * >>
 * >> // Set the function code within the com descriptor
 * >>     movP   $<cg_info.dl_comid>, service_comdesc::scd_com::sc_code(%R_service_com)
 * >>
 * >>
 * >>
 * >> // Calculate the SHM-relative address of `service_comdesc::scd_com'
 * >>     # On i386, `%R_shmbase' is '%Pbx'. On x86_64, `%R_shmbase' is:
 * >>     # (cg_inline_buf_paramc && COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS) ? '%r8' : '%Pdi'
 * >>     leaP   service_comdesc::scd_com(%R_service_com), %Pdx
 * >>     movP   LOC_shm(%Psp),                            %R_shmbase
 * >>     movP   service_shm_handle::ssh_shm(%R_shmbase),  %R_shmbase
 * >>     subP   %R_shmbase,                               %Pdx
 * >>
 * >>
 * >>
 * >> // Serialize fixed-length inline buffers
 * >> #if cg_inline_buf_paramc != 0
 * >> {foreach[INLINE_BUFFER_ARGUMENT: <cibp_buffer_offset>, <cibp_sizeof>, <cibp_param_offset>, <cibp_serial_offset>]: {
 * >>     # NOTE: `<cibp_buffer_offset>' (>= `<cibp_buffer_offset>') is the
 * >>     #       offset from service_comdesc to where inline buffer data is stored.
 * >>     leaP   <cibp_buffer_offset - service_comdesc::scd_com>(%Pdx), %Pax # SHM-relative address of the inline buffer
 * >>     movP   %Pax, <cibp_serial_offset>(%R_service_com)                  # Store relative address in serial stream
 * >> #if ARGUMENT_IS_IN_OR_INOUT_BUFFER # (Referring to the argument being enumerated)
 * >>     # Whether or not movs is used is determined on a per-argument basis
 * >> #if COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     leaP   <cibp_buffer_offset>(%R_service_com), %Pdi # This instruction is skipped if `Pdi' already has the
 * >>                                                       # correct value, which may be the case if a preceding
 * >>                                                       # inline buffer already set it up correctly.
 * >>     movP   <cibp_param_offset>(%Psp), %Psi
 * >>     movP   $<cibp_sizeof>,            %Pcx            # Or an equivalent series of inline `[rep] movsX' instructions
 * >>     rep    movsb
 * >> #else // COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     movP   <cibp_param_offset>(%Psp), %Pcx
 * >>     {INLINE_MEMCPY(_OFF, _BWLQ, <cibp_sizeof>) {
 * >>         mov{_BWLQ} _OFF(%Pcx), %{_BWLQ}ax
 * >>         mov{_BWLQ} %{_BWLQ}ax, <cibp_buffer_offset>+_OFF(%R_service_com)
 * >>     }}
 * >> #endif // !COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >> #endif // ARGUMENT_IS_IN_OR_INOUT_BUFFER
 * >> }}
 * >> #endif // cg_inline_buf_paramc != 0
 * >>
 * >>
 * >>
 * >> // Add the service_comdesc to the list of active commands `cg_service->s_active_list'
 * >>     movP   <cg_service->s_active_list>, %Pax                      # movabs via %Pcx if necessary on x86_64
 * >> 1:  # TODO: Check for SERVICE_ACTIVE_LIST_SHUTDOWN
 * >>     movP   %Pax, service_comdesc::scd_active_link(%R_service_com)
 * >>     lock   cmpxchgP %Pdx, <cg_service->s_active_list>
 * >>     jne    1b
 * >>
 * >>
 * >>
 * >> // Insert the command into the server's pending list
 * >>     # Atomically insert the new command into the list
 * >>     # HINT: At this point, %Pdx == ((%R_service_com + service_comdesc::scd_com) - service_shm_handle::ssh_shm(%R_temp_shm_handle))
 * >>     movP   service_shm::s_commands(%R_shmbase), %Pax
 * >> 1:  movP   %Pax, service_comdesc::scd_com::sc_link(%R_service_com)
 * >>     lock   cmpxchgP %Pdx, service_shm::s_commands(%R_shmbase)
 * >>     jne    1b
 * >> .Leh_com_waitfor_begin:
 * >>
 * >>
 * >>
 * >> // Tell the server that a new command has become available
 * >>     #     futex_wake(&shm->s_commands, 1)
 * >>     # <=> syscall(SYS_lfutex, &shm->s_commands, LFUTEX_WAKE, 1)
 * >>     movP   $SYS_lfutex, %Pax
 * >> #ifdef __x86_64__
 * >>     leaq   service_shm::s_commands(%R_shmbase), %rdi # NOTE: %R_shmbase was already initialized above!
 * >>     movq   $LFUTEX_WAKE,                        %rsi
 * >>     movq   $1,                                  %rdx
 * >>     syscall
 * >> #else // __x86_64__
 * >> #if offsetof(service_shm, s_commands) != 0  # HINT: `%R_shmbase' is `%ebx' on i386!
 * >>     addl   $<service_shm::s_commands>, %ebx # NOTE: %R_shmbase was already initialized above!
 * >> #endif // offsetof(service_shm, s_commands) != 0
 * >>     movl   $LFUTEX_WAKE, %ecx
 * >>     movl   $1,           %edx
 * >>     call   __i386_syscall
 * >> #endif // !__x86_64__
 * >>     # No need to check for errors here: There
 * >>     # should be no reason for the above to fail!
 * >>
 * >>
 * >>
 * >> // Wait for the command to complete
 * >>     #     futex_waitwhile(&com->sc_code, <cg_info.dl_comid>)
 * >>     # <=> syscall(SYS_lfutx, &com->sc_code, LFUTEX_WAIT_WHILE, <cg_info.dl_comid>)
 * >> .Lwaitfor_completion:
 * >>     movP   $SYS_lfutex, %Pax
 * >> #ifdef __x86_64__
 * >>     leaq   service_comdesc::scd_com::sc_code(%R_service_com), %rdi
 * >>     movq   $LFUTEX_WAIT_WHILE,                                %rsi
 * >>     movq   $<cg_info.dl_comid>,                               %rdx
 * >> #if COM_GENERATOR_FEATURE_FEXCEPT
 * >>     std
 * >>     .cfi_escape 56,22,49,7,146,49,0,11,255,251,26  # Disable EFLAGS.DF during unwind & landing
 * >>     syscall
 * >>     cld
 * >>     .cfi_escape 57
 * >> #else // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     syscall
 * >> #endif // !COM_GENERATOR_FEATURE_FEXCEPT
 * >> #else // __x86_64__
 * >>     leaq   service_comdesc::scd_com::sc_code(%R_service_com), %ebx
 * >>     movl   $LFUTEX_WAIT_WHILE,                                %ecx
 * >>     movl   $<cg_info.dl_comid>,                               %edx
 * >> #if COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   __i386_Xsyscall
 * >> #else // COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   __i386_syscall
 * >> #endif // !COM_GENERATOR_FEATURE_FEXCEPT
 * >> #endif // !__x86_64__
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     cmpP   $(-ELIMIT), %Pax
 * >>     ja     .Lerr_com_abort_errno
 * >> #endif // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     # Check if the operation has completed
 * >>     movP   service_comdesc::scd_com::sc_code(%R_service_com), %R_fcall0P
 * >>     cmpP   $<cg_info.dl_comid>, %R_fcall0P
 * >>     je     .Lwaitfor_completion
 * >> .Leh_com_waitfor_end:
 * >>
 * >>
 * >>
 * >> // Remove the service_comdesc to the list of active commands `cg_service->s_active_list'
 * >>     leaP   service_comdesc::scd_com(%R_service_com), %Pax
 * >>     movP   LOC_shm(%Psp),                            %Pdx
 * >>     subP   service_shm_handle::ssh_shm(%Pdx),        %Pax # %Pax == shm_offsetof_elem_com
 * >>     movP   service_comdesc::scd_active_link(%R_service_com), %Pdx
 * >>     lock   cmpxchgP %Pdx, <cg_service->s_active_list>  # movabs via %Pcx if necessary on x86_64
 * >>     jne    .Lremove_service_com_tryhard
 * >> .Lremove_service_com_tryhard_return:
 * >>
 * >>
 * >>
 * >> // Check if the command completed with a special status code
 * >>     cmpP   $SERVICE_COM_ST_SUCCESS, %R_fcall0P
 * >>     jne    .Lcom_special_return
 * >> .Lcom_special_return_resume:
 * >>
 * >>
 * >> // Deserialize fixed-length inline buffers
 * >> {foreach[INLINE_INOUT_OUT_BUFFER_ARGUMENT: <cibp_buffer_offset>, <cibp_sizeof>, <cibp_param_offset>]: {
 * >> #if COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     leaP   <cibp_buffer_offset>(%R_service_com), %Psi # This instruction is skipped if `Psi' already has the
 * >>                                                       # correct value, which may be the case if a preceding
 * >>                                                       # inline buffer already set it up correctly.
 * >>                                                       # May also be encoded as `addP $..., %Psi' if appropriate
 * >>     movP   <cibp_param_offset>(%Psp),            %Pdi
 * >>     movP   $<cibp_sizeof>,                       %Pcx # Or an equivalent series of inline `[rep] movsX' instructions
 * >>     rep    movsb
 * >> #else // COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >>     movP   <cibp_param_offset>(%Psp), %Pcx
 * >>     {INLINE_MEMCPY(_OFF, _BWLQ, <cibp_sizeof>) {
 * >>         mov{_BWLQ} <cibp_buffer_offset>+_OFF(%R_service_com), %{_BWLQ}ax
 * >>         mov{_BWLQ} %{_BWLQ}ax,                                 _OFF(%Pcx)
 * >>     }}
 * >> #endif // !COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS
 * >> }}
 * >>
 * >>
 * >>
 * >> // Copy out-of-band inout/out buffers back into user-provided storage
 * >> #if cg_inoutbuf_paramc != 0 || cg_outbuf_paramc != 0
 * >>     # Load %Psi with the SHM address of the first out-of-band inout/out buffer
 * >>     # NOTE: We unconditionally use %Psi for copying!
 * >> #if cg_inbuf_paramc != 0
 * >> #if COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   LOC_bufpar_ptr(%Psp), %Psi
 * >>     addP   $<SUM(IN_BUFFERS.each.FIXED_BUFFER_SIZE.ceil_align(SERVICE_BUFFER_ALIGNMENT)>, %Psi
 * >> #else // COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >>     movP   LOC_outbuffers_start(%Psp), %Psi
 * >> #endif // !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN
 * >> #else // cg_inbuf_paramc != 0
 * >>     movP   LOC_bufpar_ptr(%Psp), %Psi
 * >> #endif // cg_inbuf_paramc == 0
 * >>
 * >>     # Copy out-of-band SHM buffers for inout/out arguments back to user-memory
 * >> {foreach[INOUT_OUT_BUFFER_ARGUMENT: <INDEX>, <cbp_param_offset>]: {
 * >>     # NOTE: INDEX is the index within `LOC_bufparam_handles' and `cg_buf_paramv'
 * >>     cmpP   $0, LOC_bufparam_handles[INDEX](%Psp)
 * >>     jne    1f
 * >>     movP   ...,                      %Pcx # required buffer size (depending on buffer type)
 * >>                                           # Allowed to clobber: %Pax, %Pdx, %Pdi
 * >>     movP   <cbp_param_offset>(%Psp), %Pdi # Unconditionally use %Psi for copying!
 * >>     rep    movsb
 * >> #if INDEX != cg_buf_paramc -1
 * >> #if cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #if !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT - (cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE & (SERVICE_BUFFER_ALIGNMENT - 1))>, %Psi   # Re-align by pointer size
 * >> #endif // !IS_ALIGNED(cg_buf_paramv[INDEX].FIXED_BUFFER_SIZE, SERVICE_BUFFER_ALIGNMENT)
 * >> #else // cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >>     ... # NOTE: In case of a `COM_BUFFER_PARAM_FRETMIN' param, also add the difference
 * >>         #       between `bufsize' and `return' to `%Psi' (when `return < bufsize')
 * >>     addP   $<SERVICE_BUFFER_ALIGNMENT-1>,    %Psi   # Re-align buffer pointer
 * >>     andP   $<~(SERVICE_BUFFER_ALIGNMENT-1)>, %Psi   # *ditto*
 * >> #endif // !cg_buf_paramv[INDEX].HAS_FIXED_BUFFER_SIZE
 * >> #endif // INDEX != cg_buf_paramc -1
 * >> 1:
 * >> }}
 * >> #endif // cg_inoutbuf_paramc != 0 || cg_outbuf_paramc != 0
 * >>
 * >>
 * >>
 * >> // Free the xbuf buffer
 * >> #if cg_buf_paramc != 0
 * >> .Leh_free_xbuf_end:
 * >>     movP   LOC_bufpar_ptr(%Psp), %Pdx
 * >>     testP  %Pdx, %Pdx
 * >>     jz     1f
 * >>     subP   $<sizeof(size_t)>, %Pdx
 * >> #ifdef __x86_64__
 * >>     movP   0(%Pdx), %Pcx
 * >> #else // __x86_64__
 * >>     pushl_cfi 0(%Pdx)
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 4  # Not needed because `libservice_shmbuf_freeat_fast_nopr()' is NOTHROW
 * >>     pushl_cfi %Pdx
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 8  # Not needed because `libservice_shmbuf_freeat_fast_nopr()' is NOTHROW
 * >> #endif // !__x86_64__
 * >>     movP   LOC_bufpar_shm(%Psp), %R_fcall1P
 * >>     movP   LOC_upm(%Psp), %Pax
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset,  %R_fcall0P
 * >>     movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $<cg_service>, %R_fcall0P
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >>     call   libservice_shmbuf_freeat_fast_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 0  # Not needed because `libservice_shmbuf_freeat_fast_nopr()' is NOTHROW
 * >> #endif // !__x86_64__
 * >> 1:
 * >> #endif // cg_buf_paramc != 0
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
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 4  # Not needed because `libservice_shmbuf_freeat_fast_nopr()' is NOTHROW
 * >>     pushl_cfi %R_service_com
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 8  # Not needed because `libservice_shmbuf_freeat_fast_nopr()' is NOTHROW
 * >> #endif // !__x86_64__
 * >>     movP   LOC_shm(%Psp), %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movq   service_comdesc::scd_com::sc_retval::scr_rax+<sizeof(size_t)>(%R_service_com), %rbp # Load return values
 * >> #else // __x86_64__
 * >> #if cg_info.dl_return == SERVICE_TYPE_386_R64
 * >>     movl   service_comdesc::scd_com::sc_retval::scr_edx+<sizeof(size_t)>(%R_service_com), %ebx # Load return values
 * >> #endif // cg_info.dl_return == SERVICE_TYPE_386_R64
 * >>     movl   service_comdesc::scd_com::sc_retval::scr_eax+<sizeof(size_t)>(%R_service_com), %ebp # Load return values
 * >> #endif // !__x86_64__
 * >> #if cg_buf_paramc == 0
 * >>     movP   LOC_upm(%Psp), %Pax
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset,  %R_fcall0P
 * >>     movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $<cg_service>, %R_fcall0P
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >> #else // cg_buf_paramc == 0
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #endif // cg_buf_paramc != 0
 * >>     call   libservice_shmbuf_freeat_fast_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 0  # Not needed because `libservice_shmbuf_freeat_fast_nopr()' is NOTHROW
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
 * >>
 * >>
 * >>
 * >> // Normal return
 * >> #ifdef __x86_64__
 * >>     # local variables + register argument storage After this, %Psp
 * >>     # points at the first registers which needs to be restored.
 * >>     addP   $<cg_locvar_size + (MIN(cg_paramc, 6) * 8) - 2 * 8>, %Psp
 * >>     .cfi_adjust_cfa_offset -<cg_locvar_size + (MIN(cg_paramc, 6) * 8) - 2 * 8>
 * >> #else // __x86_64__
 * >>     addP   $<cg_locvar_size - 2 * 4>, %Psp        # local variables
 * >>     .cfi_adjust_cfa_offset -<cg_locvar_size - 2 * 4>
 * >> #endif // !__x86_64__
 * >> #ifdef __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_RBX
 * >>     popP_cfi_r %rbx        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_RBX
 * >> #else // __x86_64__
 * >> #if COM_GENERATOR_FEATURE_USES_EDI
 * >>     popP_cfi_r %Pdi        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_EDI
 * >> #if COM_GENERATOR_FEATURE_USES_ESI
 * >>     popP_cfi_r %Psi        # Only if used anywhere above
 * >> #endif // COM_GENERATOR_FEATURE_USES_ESI
 * >> #endif // !__x86_64__
 * >>     // Set return values
 * >> #ifdef __x86_64__
 * >>     movq   %rbp, %rax
 * >> #else // __x86_64__
 * >>     movl   %ebp, %eax
 * >>     movl   %ebx, %edx
 * >> #endif // !__x86_64__
 * >>     // Restore preserved registers
 * >> #ifndef __x86_64__
 * >>     popP_cfi_r %Pbx
 * >> #endif // !__x86_64__
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
 * >> #if cg_buf_paramc == 0
 * >> .Ltest_pending_signals_after_com_buffer_alloc:
 * >>     call   chkuserprocmask
 * >>     jmp    .Ltest_pending_signals_after_com_buffer_alloc_return
 * >> #elif cg_buf_paramc == 1
 * >> .Ltest_pending_signals_after_single_buffer_alloc:
 * >>     call   chkuserprocmask
 * >>     jmp    .Ltest_pending_signals_after_single_buffer_alloc_return
 * >> .Ltest_pending_signals_after_single_buffers_is_in_band:
 * >>     pushP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, SIZEOF_POINTER   # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     call   chkuserprocmask
 * >>     popP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 0                # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     jmp .Ltest_pending_signals_after_single_buffers_is_in_band_return
 * >> #else // #elif cg_buf_paramc >= 2
 * >> #if cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >> .Ltest_pending_signals_after_xbuf_alloc:
 * >>     pushP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, SIZEOF_POINTER   # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     pushP_cfi %Pdx
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 2*SIZEOF_POINTER # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     call   chkuserprocmask
 * >>     popP_cfi %Pdx
 * >> //  .cfi_escape DW_CFA_GNU_args_size, SIZEOF_POINTER   # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     popP_cfi %Pax
 * >> //  .cfi_escape DW_CFA_GNU_args_size, 0                # Not needed because `chkuserprocmask()' is NOTHROW
 * >>     jmp .Ltest_pending_signals_after_xbuf_alloc_return
 * >> #endif // cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0
 * >> .Ltest_pending_signals_after_all_buffers_are_in_band:
 * >>     call   chkuserprocmask
 * >>     jmp    .Lall_buffers_are_in_band_preemption_reenabled:
 * >> #endif // #endif cg_buf_paramc >= 2
 * >>
 * >>
 * >>
 * >>
 * >>
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >> .Lerr_com_abort_errno:
 * >>     negP   %Pax
 * >>     movP   %Pax, %R_fcall0P
 * >>     call   __set_errno_f
 * >>     movP   $<cg_service>,  %R_fcall0P
 * >>     movP   %R_service_com, %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movq   $<cg_info.dl_comid>, %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi $<cg_info.dl_comid>
 * >> #endif // !__x86_64__
 * >>     call   libservice_aux_com_abort
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -4
 * >> #endif // !__x86_64__
 * >>     testb  %al, %al                   # Check if command completed before it could be aborted
 * >>     jz     .Leh_free_service_com_end  # if (COMPLETED_BEFORE_ABORT) goto .Leh_free_service_com_end;
 * >>     // fallthru...
 * >>
 * >> .Lerr_free_service_com:
 * >>     SET_ERROR_RETURN_VALUE()
 * >>     jmp   .Leh_free_service_com_end
 * >>
 * >> .Lerr_pop_preemption:
 * >>     SET_ERROR_RETURN_VALUE()
 * >>     jmp   .Leh_preemption_pop_end
 * >> #endif // !COM_GENERATOR_FEATURE_FEXCEPT
 * >>
 * >>
 * >>
 * >>
 * >> // Try-hard removal of commands from the active list
 * >> // s.a. the `REMOVE()' documentation in `service::s_active_list'
 * >> // NOTE: This sub-routine must preserve `%R_fcall0P', or restore its expected value by means of:
 * >> //       >> movP   service_comdesc::scd_com::sc_code(%R_service_com), %R_fcall0P
 * >> .Lremove_service_com_tryhard:
 * >>     leaP   service_comdesc::scd_com(%R_service_com), %Pdx
 * >>     movP   LOC_shm(%Psp),                            %Pax
 * >>     subP   service_shm_handle::ssh_shm(%Pax),        %Pdx # %Pdx = shm_offsetof_elem_com
 * >> // preemption_pushoff();
 * >>     movP   LOC_upm(%Psp), %Pax
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption (movabs via %Pdi on x86_64)
 * >> // atomic_lock_acquire(&s_shm_lock);
 * >> 1:  movl   $1, %eax
 * >>     xchgl  %eax, <cg_service->s_shm_lock.a_lock>         # (movabs via %Pdi on x86_64)
 * >>     testl  %eax, %eax
 * >>     jz     2f
 * >>     movP   $SYS_sched_yield, %Pax
 * >>     syscall                                              # Or `call __i386_syscall' on i386
 * >>     jmp    1b
 * >> 2:  movP   <cg_service->s_active_list>, %Pax                       # uintptr_t first = s_active_list;                     # (movabs via %Pdi on x86_64)
 * >> 3:  cmpP   %Pdx, %Pax                                              # 3: if (first == shm_offsetof_elem_com) {
 * >>     jne    4f                                                      #     ...
 * >>     movP   service_comdesc::scd_active_link(%R_service_com), %Pcx  #     %Pcx = next = elem->scd_active_link;
 * >>     lock   cmpxchgP %Pcx, <cg_service->s_active_list>              #     if (!atomic_cmpxch(&s_active_list, first, next))  # (movabs via %Pdi on x86_64)
 * >>     jz     3b                                                      #     { first = s_active_list; goto 3b; }
 * >>     jmp    6f                                                      # } else
 * >> 4:  testP  %Pax, %Pax                                              # if (first != 0) {
 * >>     jz     6f                                                      #     ...
 * >> 5:  movP   <cg_service->s_shm>, %Pcx                               # 5:  %Pcx = s_shm;                          # (movabs via %Pdi on x86_64)
 * >>     movP   service_shm_handle::ssh_base(%Pcx), %Pcx                #     %Pcx = s_shm->ssh_base;
 * >>     addP   %Pax, %Pcx                                              #     %Pcx = &COMDESC_FROM_COM_OFFSET(first)->scd_com
 * >>     movP   <service_comdesc::scd_active_link-                      #     ...
 * >>             service_comdesc::scd_com>(%Pcx), %Pax                  #     %Pax = first = container_of(%Pcx, struct service_comdesc, scd_com)->scd_active_link
 * >>     testP  %Pax, %Pax                                              #     if (first != 0) {
 * >>     jz     6f                                                      #         ...
 * >>     cmpP   %Pdx, %Pax                                              #         if (first != shm_offsetof_elem_com)
 * >>     jne    5b                                                      #             goto 5b;
 * >>     movP   service_comdesc::scd_active_link(%R_service_com), %Pax  #         %Pax = elem->scd_active_link;
 * >>     movP   %Pax, <service_comdesc::scd_active_link-                #         ...
 * >>                   service_comdesc::scd_com>(%Pcx)                  #         container_of(%Pcx, struct service_comdesc, scd_com)->scd_active_link = %Pax;
 * >>                                                                    #     }
 * >>                                                                    # }
 * >> 6:
 * >> // atomic_lock_release(&s_shm_lock);
 * >>     movl   $0, <cg_service->s_shm_lock.a_lock>           # (movabs via %Pdi on x86_64)
 * >> // PREEMPTION_POP();
 * >>     movP   LOC_oldset(%Psp), %Pdx  # `sigset_t *oldset'
 * >>     movP   LOC_upm(%Psp),    %Pax  # `struct userprocmask *upm'
 * >>     movP   %Pdx, userprocmask::pm_sigmask(%Pax)
 * >>     test   $USERPROCMASK_FLAG_HASPENDING, userprocmask::pm_flags(%Pax)
 * >>     jnz    8f
 * >> 7:  movP   service_comdesc::scd_com::sc_code(%R_service_com), %R_fcall0P   # Restore to expected value
 * >>     jmp    .Lremove_service_com_tryhard_return
 * >> 8:  call   chkuserprocmask
 * >>     jmp    7b
 * >>
 * >>
 * >>
 * >>
 * >> // Handling for custom completion status codes
 * >> .Lcom_special_return:
 * >>     cmpP   $SERVICE_COM_ST_ECHO, %R_fcall0P
 * >>     jbe    1f
 * >>     # Normal return with non-zero errno
 * >>     negP   %R_fcall0P
 * >>     call   __set_errno_f
 * >>     jmp    .Lcom_special_return_resume
 * >> 1:  movP   %R_service_com, %R_fcall1P
 * >> #if !COM_GENERATOR_FEATURE_FEXCEPT
 * >>     call   libservice_aux_load_except_as_errno
 * >> #if cg_buf_paramc != 0
 * >>     jmp    .Leh_free_xbuf_end
 * >> #else // cg_buf_paramc != 0
 * >>     jmp    .Leh_free_service_com_end
 * >> #endif // cg_buf_paramc == 0
 * >> #else // !COM_GENERATOR_FEATURE_FEXCEPT
 * >> #ifdef __x86_64__
 * >>     movP   <cg_cfa_offset-P>(%Psp), %R_sysvabi2P
 * >>     call   libservice_aux_load_except_as_error
 * >> #else // __x86_64__
 * >>     pushP_cfi <cg_cfa_offset-P>(%Psp)
 * >>     call   libservice_aux_load_except_as_error
 * >>     .cfi_adjust_cfa_offset -4
 * >> #endif // !__x86_64__
 * >> #if cg_buf_paramc != 0
 * >>     jmp    .Leh_free_xbuf_entry
 * >> #else // cg_buf_paramc != 0
 * >>     jmp    .Leh_free_service_com_entry
 * >> #endif // cg_buf_paramc == 0
 * >> #endif // COM_GENERATOR_FEATURE_FEXCEPT
 * >>
 * >>
 * >>
 * >>
 * >> // Remove command from active+wait queue on interrupt
 * >> .Leh_com_waitfor_entry:
 * >>     movP   $<cg_service>,  %R_fcall0P
 * >>     movP   %R_service_com, %R_fcall1P
 * >> #ifdef __x86_64__
 * >>     movq   $<cg_info.dl_comid>, %rdx
 * >> #else // __x86_64__
 * >>     pushl_cfi $<cg_info.dl_comid>
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
 * >> 1:  // fallthru...
 * >>
 * >>
 * >>
 * >> // Except handler to free xbuf
 * >> #if cg_buf_paramc != 0
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
 * >>     movP   LOC_bufpar_shm(%Psp), %R_fcall1P
 * >>     movP   LOC_upm(%Psp), %Pax
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset,  %R_fcall0P
 * >>     movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $<cg_service>, %R_fcall0P
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >>     call   libservice_shmbuf_freeat_fast_nopr
 * >> #ifndef __x86_64__
 * >>     .cfi_adjust_cfa_offset -8
 * >> #endif // !__x86_64__
 * >> 1:  // fallthru...
 * >> #endif // cg_buf_paramc != 0
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
 * >>     movP   LOC_shm(%Psp), %R_fcall1P
 * >>     movP   LOC_upm(%Psp), %Pax
 * >> #if defined(__x86_64__) && $full_sigset > 0xffffffff
 * >>     movabs $full_sigset,  %R_fcall0P
 * >>     movP   %R_fcall0P,    userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >>     movP   $<cg_service>, %R_fcall0P
 * >> #else // __x86_64__ && $full_sigset > 0xffffffff
 * >>     movP   $<cg_service>, %R_fcall0P
 * >>     movP   $full_sigset,  userprocmask::pm_sigmask(%Pax) # re-disable preemption
 * >> #endif // !__x86_64__ || $full_sigset <= 0xffffffff
 * >>     call   libservice_shmbuf_freeat_fast_nopr
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
 * >>     nop
 * >>     .cfi_endproc
 *
 * NOTES:
 *  - Every `call foo' instruction above can  either be encoded as itself,  or
 *    (if doing so would result in an integer overflow on x86_64), it can also
 *    be encoded as:
 *    >> movabs $foo, %rax
 *    >> call   *%rax
 *    Though obviously, normal `call' instructions are preferred!
 *
 * ================================================================================================
 */



/* Internal IDs for special locations with wrapper texts.
 * When wrappers are generated, it is possible to  define
 * relocations against any of these symbols */
enum {
	COM_SYM_Leh_preemption_pop_begin,                            /* `.Leh_preemption_pop_begin' */
	COM_SYM_Leh_free_service_com_begin,                          /* `.Leh_free_service_com_begin' */
	COM_SYM_Leh_free_xbuf_begin,                                 /* `.Leh_free_xbuf_begin'                                          [valid_if(cg_buf_paramc == 1)] */
	COM_SYM_Ltest_pending_signals_after_xbuf_alloc_return,       /* `.Ltest_pending_signals_after_xbuf_alloc_return'                [valid_if(cg_buf_paramc >= 2 && (cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0))] */
	COM_SYM_Lall_buffers_are_in_band_preemption_reenabled,       /* `.Lall_buffers_are_in_band_preemption_reenabled'                [valid_if(cg_buf_paramc >= 2)] */
	COM_SYM_Leh_com_waitfor_begin,                               /* `.Leh_com_waitfor_begin' */
	COM_SYM_Leh_com_waitfor_end,                                 /* `.Leh_com_waitfor_end' */
	COM_SYM_Lremove_service_com_tryhard,                         /* `.Lremove_service_com_tryhard' */
	COM_SYM_Lremove_service_com_tryhard_return,                  /* `.Lremove_service_com_tryhard_return' */
	COM_SYM_Lcom_special_return,                                 /* `.Lcom_special_return' */
	COM_SYM_Lcom_special_return_resume,                          /* `.Lcom_special_return_resume' */
	COM_SYM_Leh_free_xbuf_end,                                   /* `.Leh_free_xbuf_end'                                            [valid_if(cg_buf_paramc != 0)] */
	COM_SYM_Leh_free_service_com_end,                            /* `.Leh_free_service_com_end' */
	COM_SYM_Leh_preemption_pop_end,                              /* `.Leh_preemption_pop_end' */
	COM_SYM_Lafter_check_signals_before_return,                  /* `.Lafter_check_signals_before_return' */
	COM_SYM_Lcheck_signals_before_return,                        /* `.Lcheck_signals_before_return' */
	COM_SYM_Ltest_pending_signals_after_xbuf_alloc,              /* `.Ltest_pending_signals_after_xbuf_alloc'                       [valid_if(cg_buf_paramc >= 2 && (cg_inbuf_paramc != 0 || cg_inoutbuf_paramc != 0))] */
	COM_SYM_Ltest_pending_signals_after_all_buffers_are_in_band, /* `.Ltest_pending_signals_after_all_buffers_are_in_band'          [valid_if(cg_buf_paramc >= 2)] */
	COM_SYM_Lerr_com_abort_errno,                                /* `.Lerr_com_abort_errno'                                         [valid_if(!COM_GENERATOR_FEATURE_FEXCEPT)] */
	COM_SYM_Lerr_free_service_com,                               /* `.Lerr_free_service_com'                                        [valid_if(!COM_GENERATOR_FEATURE_FEXCEPT)] */
	COM_SYM_Lerr_pop_preemption,                                 /* `.Lerr_pop_preemption'                                          [valid_if(!COM_GENERATOR_FEATURE_FEXCEPT)] */
	COM_SYM_Leh_com_waitfor_entry,                               /* `.Leh_com_waitfor_entry' */
	COM_SYM_Leh_free_xbuf_entry,                                 /* `.Leh_free_xbuf_entry'                                          [valid_if(cg_buf_paramc != 0)] */
	COM_SYM_Leh_free_service_com_entry,                          /* `.Leh_free_service_com_entry' */
	COM_SYM_Leh_preemption_pop_entry,                            /* `.Leh_preemption_pop_entry' */
	COM_SYM_COUNT,                                               /* # of COM symbols */

	/* Reused symbol IDs. */
	COM_SYM_Ltest_pending_signals_after_com_buffer_alloc_return          = COM_SYM_Lall_buffers_are_in_band_preemption_reenabled,       /* `.Ltest_pending_signals_after_com_buffer_alloc_return'          [valid_if(cg_buf_paramc == 0)] */
	COM_SYM_Ltest_pending_signals_after_single_buffer_alloc_return       = COM_SYM_Ltest_pending_signals_after_xbuf_alloc_return,       /* `.Ltest_pending_signals_after_single_buffer_alloc_return'       [valid_if(cg_buf_paramc == 1)] */
	COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band_return = COM_SYM_Lall_buffers_are_in_band_preemption_reenabled,       /* `.Ltest_pending_signals_after_single_buffers_is_in_band_return' [valid_if(cg_buf_paramc == 1)] */
	COM_SYM_Ltest_pending_signals_after_com_buffer_alloc                 = COM_SYM_Ltest_pending_signals_after_xbuf_alloc,              /* `.Ltest_pending_signals_after_com_buffer_alloc'                 [valid_if(cg_buf_paramc == 0)] */
	COM_SYM_Ltest_pending_signals_after_single_buffer_alloc              = COM_SYM_Ltest_pending_signals_after_xbuf_alloc,              /* `.Ltest_pending_signals_after_single_buffer_alloc'              [valid_if(cg_buf_paramc == 1)] */
	COM_SYM_Ltest_pending_signals_after_single_buffers_is_in_band        = COM_SYM_Ltest_pending_signals_after_all_buffers_are_in_band, /* `.Ltest_pending_signals_after_single_buffers_is_in_band'        [valid_if(cg_buf_paramc == 1)] */
};


/* COM Relocation types */
#define COM_R_PCREL32 0 /* [*(s32 *)ADDR += (s32)(u32)(VALUE - (uintptr_t)ADDR)] PC-relative, 32-bit */
#define COM_R_PCREL8  1 /* [*(s8 *)ADDR += (s8)(u8)(VALUE - (uintptr_t)ADDR)] PC-relative, 8-bit */
#define COM_R_ABSPTR  2 /* [*(uintptr_t *)ADDR += VALUE] Absolute, pointer-sized */

/* Com relocation descriptor */
struct com_reloc {
	uint16_t cr_offset; /* .text offset where relocation should be applied */
	uint8_t  cr_type;   /* Relocation type (one of `COM_R_*') */
	uint8_t  cr_symbol; /* Symbol against which to relocate (one of `COM_SYM_*') */
};

/* Max number of relocations in com wrapper functions */
/*[[[deemon print("#define COM_RELOC_MAXCOUNT ", (File from deemon)
	.open("./wrapper.c", "r").read().decode("utf-8").count("comgen_reloc"));]]]*/
#define COM_RELOC_MAXCOUNT 10
/*[[[end]]]*/


#ifdef __x86_64__
#define SERVICE_INTPAR_MACOUNT SERVICE_ARGC_MAX
#else /* __x86_64__ */
/* This limit is reached when all parameters are 64-bit integers! */
#define SERVICE_INTPAR_MACOUNT (SERVICE_ARGC_MAX * 2)
#endif /* !__x86_64__ */

struct com_int_param {
	int16_t  cip_param_offset;  /* [const] Offset from CFA to where this parameter is stored in memory */
	uint16_t cip_serial_offset; /* [const] Offset from `struct service_comdesc' to where this parameter's value is stored */
};

/* Fixed-length buffers with a size <= this value are stored inline with the com descriptor.
 * As such, fixed-length buffers no greater than  this value don't profit from being  stored
 * in SHM memory, as they are always copied before/after a com call. */
#ifdef __x86_64__
#define COM_FIXBUF_INLINE_THRESHOLD 64
#else /* __x86_64__ */
#define COM_FIXBUF_INLINE_THRESHOLD 32
#endif /* !__x86_64__ */

/* Use `movs' for buffers with sizes >= this value. */
#ifdef __x86_64__
#define COM_USEMOVS_THRESHOLD 17
#else /* __x86_64__ */
#define COM_USEMOVS_THRESHOLD 9
#endif /* !__x86_64__ */

/* Try to use `rep movsX' when  at least this many  identical
 * consecutive movsX instructions would have to be generated. */
#define COM_USEREP_THRESHOLD 8


/* Flags for `com_inline_buffer_param::cibp_flags' */
#define COM_INLINE_BUFFER_PARAM_FIN    0x01 /* FLAG: In buffer */
#define COM_INLINE_BUFFER_PARAM_FOUT   0x02 /* FLAG: Out buffer */
struct com_inline_buffer_param {
	uint8_t  cibp_param_index;   /* [const] Parameter index in `:cg_info.dl_params' */
	uint8_t  cibp_flags;         /* [const] Parameter flags (set of `COM_INLINE_BUFFER_PARAM_F*') */
	int16_t  cibp_param_offset;  /* [const] Offset from CFA to where this parameter is stored in memory */
	uint16_t cibp_serial_offset; /* [const] Offset from `struct service_comdesc' to where the address of this buffer is saved */
	uint16_t cibp_buffer_offset; /* [const] Offset from `struct service_comdesc' to the buffer itself exists */
	uint16_t cibp_sizeof;        /* [const][== (:cg_info.dl_params[cibp_param_index] & _SERVICE_TYPE_PARAMMASK)]
	                              * Fixed sizeof this buffer parameter */
};


/* Flags for `com_buffer_param::cbp_flags' */
#define COM_BUFFER_PARAM_FIN     0x01 /* FLAG: In buffer */
#define COM_BUFFER_PARAM_FOUT    0x02 /* FLAG: Out buffer */
#define COM_BUFFER_PARAM_FRETMIN 0x04 /* FLAG: May only appear in conjunction with `COM_BUFFER_PARAM_FOUT'
                                       *       (output  size  is   limited  by   function  return   value) */
#define COM_BUFFER_PARAM_FFIXED  0x08 /* FLAG: Buffer size of this parameter is fixed. */

struct com_buffer_param {
	uint8_t  cbp_param_index;   /* [const] Parameter index in `:cg_info.dl_params' */
	uint8_t  cbp_flags;         /* [const] Parameter flags (set of `COM_BUFFER_PARAM_F*') */
	int16_t  cbp_param_offset;  /* [const] Offset from CFA to where this parameter is stored in memory:
	                             * >> value = *(void **)(%Psp + cg_cfa_offset + cbp_param_offset); */
	uint16_t cbp_serial_offset; /* [const] Offset from `struct service_comdesc' to where the address of this buffer is saved */
};

/* Flags for `struct com_generator::cg_features' */
#define COM_GENERATOR_FEATURE_FNORMAL             0x00 /* Normal flags. */
#define COM_GENERATOR_FEATURE_FEXCEPT             0x01 /* Wrapper function uses exceptions */
#define COM_GENERATOR_FEATURE_INT_PARAMS_USE_LODS 0x02 /* Use `lodsP' to load integer parameters from the stack */
#define COM_GENERATOR_FEATURE_INT_PARAMS_USE_STOS 0x04 /* Use `stosP' to write integer parameters to SHM */
#define COM_GENERATOR_FEATURE_INLINE_BUFFERS_MOVS 0x08 /* Use `movs' to copy inline buffers */
#define COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN   0x10 /* All in buffers have fixed lengths */
#ifdef __x86_64__
#define COM_GENERATOR_FEATURE_USES_RBX 0x80 /* %rbx is used and must be saved/restored */
#else /* __x86_64__ */
#define COM_GENERATOR_FEATURE_USES_EDI 0x40 /* %edi is used and must be saved/restored */
#define COM_GENERATOR_FEATURE_USES_ESI 0x80 /* %esi is used and must be saved/restored */
#endif /* !__x86_64__ */


struct com_generator {
	byte_t                     *cg_txbas;             /* [1..1][const] .text base pointer */
	byte_t                     *cg_ehbas;             /* [1..1][const] .eh_frame base pointer */
	byte_t                     *cg_txend;             /* [1..1][const] .text buffer end pointer */
	byte_t                     *cg_ehend;             /* [1..1][const] .eh_frame buffer end pointer */
	struct service             *cg_service;           /* [1..1][const] The service in question. */
	struct service_com_funinfo  cg_info;              /* [const] Function information. */
	int16_t                     cg_locvar_offset;     /* [const] Offset from CFA to the start of local variables */
	uint16_t                    cg_locvar_size;       /* [const] Total size of the local variables area */
	struct com_int_param        cg_intpar[SERVICE_INTPAR_MACOUNT]; /* [cg_int_paramc][const] Word-sized integer parameters */
	struct com_inline_buffer_param cg_inline_buf_paramv[SERVICE_ARGC_MAX];
	                                                  /* [cg_inline_buf_paramc][const] Fixed-length inline buffers (sorted as `in, inout, out') */
	struct com_buffer_param     cg_buf_paramv[SERVICE_ARGC_MAX];
	                                                  /* [cg_buf_paramc][const] Buffer parameters. Sorted
	                                                   * by buffer type in order of `in, inout, out'. Out
	                                                   * buffers  with  SERVICE_OUT_SIZEARG_RETURN_MINVAL
	                                                   * come after those without. */
	uint16_t                    cg_sizeof_service_com; /* [const] Total required sizeof for the service_comdesc object. (NOT ADJUSTED FOR ALLOCATION INTERNALS!) */
	uint8_t                     cg_inline_buf_paramc; /* [const] # of inline buffer parameters */
	uint8_t                     cg_buf_paramc;        /* [const] # of buffer parameters */
	uint8_t                     cg_inbuf_paramc;      /* [const] # of in-buffer parameters     (cg_buf_paramv[0..cg_inbuf_paramc-1]) */
	uint8_t                     cg_inoutbuf_paramc;   /* [const] # of inout-buffer parameters  (cg_buf_paramv[cg_inbuf_paramc..cg_inoutbuf_paramc+cg_inbuf_paramc-1]) */
	uint8_t                     cg_outbuf_paramc;     /* [const] # of out-buffer parameters    (cg_buf_paramv[cg_inoutbuf_paramc+cg_inbuf_paramc..cg_inoutbuf_paramc+cg_inbuf_paramc+cg_outbuf_paramc-1]) */
	uint8_t                     cg_int_paramc;        /* [const] # of integer parameters */
	uint8_t                     cg_paramc;            /* [const] # of parameters (index of first SERVICE_TYPE_VOID param, or SERVICE_ARGC_MAX when all params are used) */
	uint8_t                     cg_features;          /* [const] Code features (set of `COM_GENERATOR_FEATURE_F*') */
	/* Fields used internally  by `comgen_compile()'.  These don't  require
	 * any special initialization and are left undefined by `comgen_init()' */
	uint8_t                     cg_nrelocs;           /* [<= COM_RELOC_MAXCOUNT] # of relocations in use */
	int16_t                     cg_cfa_offset;        /* Current offset to-be applied to %Psp to find CFA
	                                                   * All stack-offset variables are actually relative
	                                                   * to CFA, and  cg_cfa_offset itself always  points
	                                                   * just after the return-PC:
	                                                   * >> RETURN_PC == ((void **)(%Psp + cg_cfa_offset))[-1]; */
	uint16_t                    cg_symbols[COM_SYM_COUNT]; /* Symbol definitions (relative to `cg_txbas') */
	struct com_reloc            cg_relocs[COM_RELOC_MAXCOUNT]; /* Relocations */
	byte_t                     *cg_txptr;             /* [1..1][>= cg_txbas && <= cg_txend] .text writer pointer */
	byte_t                     *cg_ehptr;             /* [1..1][>= cg_ehbas && <= cg_ehend] .eh_frame writer pointer */
	byte_t                     *cg_CFA_loc;           /* [1..1][>= cg_txbas && <= cg_txend] Last CFA instrumentation location. */
};


/* Initialize the given com generator. Prior to calling
 * this function, the  caller must already  initialize:
 *  - self->cg_info
 * NOTE: This  function will leave the following fields
 *       uninitialized (which must be set-up by a later
 *       call to `comgen_reset()'):
 *  - self->cg_txbas, self->cg_ehbas
 *  - self->cg_txend, self->cg_ehend */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _comgen_init)(struct com_generator *__restrict self);
#define comgen_init(self, svc, enable_except)               \
	((self)->cg_service  = (svc),                           \
	 (self)->cg_features = (enable_except)                  \
	                       ? COM_GENERATOR_FEATURE_FEXCEPT  \
	                       : COM_GENERATOR_FEATURE_FNORMAL, \
	 _comgen_init(self))


/* Compile  the  com generator  wrapper function.  Upon return,
 * the caller must check the status using `comgen_compile_st_*'
 * Only with both *_moretx and *_moreeh return `false' may  the
 * compile operation be  considered successful. Otherwise,  the
 * respective need-more-memory condition should be handled.
 *
 * @return: true:  Compilation succeed (you may assume `comgen_compile_isok(self) == true')
 * @return: false: Compilation failed due to lack of .text- or  .eh_frame-memory
 *                 Check which is the case with `comgen_compile_st_moretx()' and
 *                 `comgen_compile_st_moreeh()'
 *
 * NOTE: Upon  success, the  used EH  buffer size  will indicate 4
 *       bytes more than should actually be accounted as belonging
 *       to the associated function. These bytes may not be freed,
 *       but should be overwritten  (iow: passed as `cg_ehbas'  in
 *       some  future compilation operation),  as they represent a
 *       sentinel marker in unwind debug data.
 *       The implementation of  this function takes  care to  maintain
 *       the  sentinel until the  point in time when  eh data has been
 *       finalized, at which point other threads may immediately begin
 *       parsing generated debug data.
 *       Until  that point,  the sentinel  must be  kept to prevent
 *       other threads from accessing incomplete debug information! */
INTDEF NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL comgen_compile)(struct com_generator *__restrict self);
#define comgen_compile_st_moretx(self) (!comgen_txok1(self))
#define comgen_compile_st_moreeh(self) (!comgen_ehok1(self))
/* Number of .text/.eh_frame bytes used on success */
#define comgen_compile_txused(self) ((size_t)((self)->cg_txptr - (self)->cg_txbas))
#define comgen_compile_ehused(self) ((size_t)((self)->cg_ehptr - (self)->cg_ehbas))

/* Helper to check if compilation should continue */
#define comgen_compile_isok(self)       \
	(!comgen_compile_st_moretx(self) && \
	 !comgen_compile_st_moreeh(self))



/* Reset all  fields that  are not  [const] in  `self'
 * This must be called whenever code generation has to
 * be restarted as the result of insufficient .text or
 * .eh_frame space. */
#define comgen_reset(self, txbas, txend, ehbas, ehend)             \
	(void)((self)->cg_txbas = (txbas), (self)->cg_ehbas = (ehbas), \
	       (self)->cg_txend = (txend), (self)->cg_ehend = (ehend))


/* Helper macros for generating offsets to local variables (from %Psp) */
#define comgen_spoffsetof_LOCALS(self)                ((self)->cg_cfa_offset + (self)->cg_locvar_offset)
#define comgen_spoffsetof_LOC_oldset(self)            (comgen_spoffsetof_LOCALS(self) + 0)                              /* sigset_t                      *LOC_oldset; */
#define comgen_spoffsetof_LOC_upm(self)               (comgen_spoffsetof_LOCALS(self) + __SIZEOF_POINTER__)             /* struct userprocmask           *LOC_upm; */
#define comgen_spoffsetof_LOC_shm(self)               (comgen_spoffsetof_LOCALS(self) + 2 * __SIZEOF_POINTER__)         /* struct service_shm_handle     *LOC_shm; */
#define comgen_spoffsetof_LOC_bufpar_ptr(self)        (comgen_spoffsetof_LOCALS(self) + 3 * __SIZEOF_POINTER__)         /* void                          *LOC_bufpar_ptr;                      // [valid_if(cg_buf_paramc != 0)] */
#define comgen_spoffsetof_LOC_bufpar_shm(self)        (comgen_spoffsetof_LOCALS(self) + 4 * __SIZEOF_POINTER__)         /* REF struct service_shm_handle *LOC_bufpar_shm;                      // [valid_if(cg_buf_paramc != 0)] */
#define comgen_spoffsetof_LOC_bufpar_handles(self, i) (comgen_spoffsetof_LOCALS(self) + (5 + (i)) * __SIZEOF_POINTER__) /* struct service_shm_handle     *LOC_bufparam_handles[cg_buf_paramc]; // [valid_if(cg_buf_paramc != 0)] */
#define comgen_spoffsetof_LOC_outbuffers_start(self)  comgen_spoffsetof_LOC_bufpar_handles(self, (self)->cg_buf_paramc) /* byte_t                        *LOC_outbuffers_start;                // [valid_if(cg_inbuf_paramc != 0 && (cg_inoutbuf_paramc != 0 || cg_outbuf_paramc != 0) && !COM_GENERATOR_FEATURE_IN_BUFFERS_FIXLEN)] */

/* Returns the number of available .text or .eh_frame bytes. */
#define comgen_txavail(self) ((size_t)((self)->cg_txend - (self)->cg_txptr))
#define comgen_ehavail(self) ((size_t)((self)->cg_ehend - (self)->cg_ehptr))

/* Check if sufficient  text memory remains  available.
 * When  this  macro returns  `false', `comgen_instr()'
 * becomes a no-op, and the caller should allocate more
 * text memory. */
#define comgen_txok1(self) \
	((self)->cg_txptr + GEN86_INSTRLEN_MAX <= (self)->cg_txend)
#define comgen_txok(self, n_instr) \
	((self)->cg_txptr + ((n_instr) * GEN86_INSTRLEN_MAX) <= (self)->cg_txend)
#define comgen_txav(self, n_bytes) \
	((self)->cg_txptr + (n_bytes) <= (self)->cg_txend)

#ifdef GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C

 /* Helper macro to safely generate instructions:
 * >> comgen_instr(self, gen86_movb_r_r(&self->cg_txptr, GEN86_R_AL, GEN86_R_AH)); */
#define comgen_instr(self, ...)          \
	do {                                 \
		if unlikely(!comgen_txok1(self)) \
			return;                      \
		__VA_ARGS__;                     \
	}	__WHILE0

/* Return the current text location as a function-relative offset */
#define comgen_funcrel_offsetat(self, ptr) ((uint16_t)(uintptr_t)((ptr) - (self)->cg_txbas))
#define comgen_funcrel_offset(self)        comgen_funcrel_offsetat(self, (self)->cg_txptr)

/* Define the symbol `id' at the current text location. */
#define comgen_defsym(self, id) (void)((self)->cg_symbols[id] = comgen_funcrel_offset(self))

/* Return the  absolute address  of  the given  symbol  `id'.
 * The caller must ensure that `id' has already been defined. */
#define comgen_symaddr(self, id) ((self)->cg_txbas + (self)->cg_symbols[id])
#define comgen_symreladdr(self, id) (self)->cg_symbols[id]

#define comgen_reloc(self, addr, type, symbol)                                                    \
	(void)((self)->cg_relocs[(self)->cg_nrelocs].cr_offset = comgen_funcrel_offsetat(self, addr), \
	       (self)->cg_relocs[(self)->cg_nrelocs].cr_type   = (type),                              \
	       (self)->cg_relocs[(self)->cg_nrelocs].cr_symbol = (symbol),                            \
	       ++(self)->cg_nrelocs)
/* Same as `comgen_reloc()', but hidden from `COM_RELOC_MAXCOUNT' (Use with caution!) */
#define comgen_hidden_reloc comgen_reloc
#endif /* GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */



/* Structural representation of the .eh_frame
 * segment  generated  by the  com generator. */
struct ATTR_PACKED ATTR_ALIGNED(1) com_eh_frame {
	/* CIE */
	uint32_t  cef_cie_size;      /* [== offsetof(cef_fde_size)] CIE::cie_size */
	uint32_t  cef_cie_id;        /* [== 0]                      CIE::cie_id */
	uint8_t   cef_cie_version;   /* [== 1]                      CIE::cie_version */
	char      cef_cie_augstr[3]; /* [== {'z', 'L', 'P'}]        CIE::cie_augstr */
	uint8_t   cef_cie_codealign; /* [== 1]                      CIE::cie_codealign */
#ifdef __x86_64__
	uint8_t   cef_cie_dataalign; /* [== 0x78] (decodes to: -8)  CIE::cie_dataalign */
	uint8_t   cef_cie_retreg;    /* [== CFI_X86_64_UNWIND_REGISTER_RIP] CIE::cie_retreg */
	uint8_t   cef_cie_auglen;    /* [== 10]                     CIE::cie_auglen */
#else /* __x86_64__ */
	uint8_t   cef_cie_dataalign; /* [== 0x7c] (decodes to: -4)  CIE::cie_dataalign */
	uint8_t   cef_cie_retreg;    /* [== CFI_386_UNWIND_REGISTER_EIP] CIE::cie_retreg */
	uint8_t   cef_cie_auglen;    /* [== 6]                      CIE::cie_auglen */
#endif /* !__x86_64__ */
	uint8_t   cef_cie_lsdaenc;   /* [== DW_EH_PE_absptr]        CIE::cie_lsdaenc */
	uint8_t   cef_cie_persoenc;  /* [== DW_EH_PE_absptr]        CIE::cie_persoenc */
	uintptr_t cef_cie_persoptr;  /* <Flexible>                  CIE::cie_persoptr */
	/* CIE init text would go here... */

	/* FDE */
	uint32_t  cef_fde_size;      /* <Flexible>                     FDE::fde_size */
	uint32_t  cef_fde_cie_off;   /* [== offsetof(cef_fde_cie_off)] FDE::fde_cie_off */
	uintptr_t cef_fde_funbase;   /* <Flexible>                     FDE::fde_funbase */
	size_t    cef_fde_funsize;   /* <Flexible>                     FDE::fde_funsize */
	uint8_t   cef_fde_auglen;    /* [== sizeof(void *)]            FDE::fde_auglen */
	uintptr_t cef_fde_lsda;      /* <Flexible>                     FDE::fde_lsda */

	/* FDE unwind instrumentation text */
	COMPILER_FLEXIBLE_ARRAY(byte_t, cef_fde_text); /* FDE::fde_text */
};


/* Minimum buffer sizes which must be set in a call to `comgen_reset()'
 * Note that less than this  may end up being  used, but these are  the
 * minimum requirements imposed on input buffer sizes. */
#define COM_GENERATOR_INITIAL_TX_BUFSIZ (512)
#define COM_GENERATOR_INITIAL_EH_BUFSIZ (offsetof(struct com_eh_frame, cef_fde_text) + 64)



/* Helper macros for generating .eh_frame instrumentation */
#define COMGEN_EH_FRAME_INSTRLEN_MAX (1 + __SIZEOF_POINTER__ + ((__SIZEOF_POINTER__ + 7) / 8)) /* # of bytes which must remain available in .eh_frame */

#define comgen_ehav(self, n) likely((self)->cg_ehptr + (n) <= (self)->cg_ehend)
#define comgen_ehok1(self)   comgen_ehav(self, COMGEN_EH_FRAME_INSTRLEN_MAX)

/* Generate various CFA instructions. */
#ifdef GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C
#define comgen_eh_putb(self, b) (void)(*(self)->cg_ehptr++ = (__UINT8_TYPE__)(b))
#define comgen_eh_putw(self, w) (void)(__hybrid_unaligned_set16((self)->cg_ehptr, (__UINT16_TYPE__)(w)), (self)->cg_ehptr += 2)
#define comgen_eh_putl(self, l) (void)(__hybrid_unaligned_set32((self)->cg_ehptr, (__UINT32_TYPE__)(l)), (self)->cg_ehptr += 4)
#define comgen_eh_putq(self, q) (void)(__hybrid_unaligned_set64((self)->cg_ehptr, (__UINT64_TYPE__)(q)), (self)->cg_ehptr += 8)
#define comgen_eh_putsleb128(self, value) (void)((self)->cg_ehptr = _eh_putsleb128((self)->cg_ehptr, value))
#define comgen_eh_putuleb128(self, value) (void)((self)->cg_ehptr = _eh_putuleb128((self)->cg_ehptr, value))
PRIVATE WUNUSED NONNULL((1)) byte_t *NOTHROW(FCALL _eh_putsleb128)(byte_t *__restrict writer, intptr_t value);
PRIVATE WUNUSED NONNULL((1)) byte_t *NOTHROW(FCALL _eh_putuleb128)(byte_t *__restrict writer, uintptr_t value);

#define comgen_eh_DW_CFA_advance_loc(self, pc_offset)                \
	(void)(!comgen_ehav(self, 5) ||                                  \
	       ((pc_offset) <= 0x3f                                      \
	        ? comgen_eh_putb(self, DW_CFA_advance_loc | (pc_offset)) \
	        : (pc_offset) <= 0xff                                    \
	          ? (comgen_eh_putb(self, DW_CFA_advance_loc1),          \
	             comgen_eh_putb(self, pc_offset))                    \
	          : (pc_offset) <= 0xffff                                \
	            ? (comgen_eh_putb(self, DW_CFA_advance_loc2),        \
	               comgen_eh_putw(self, pc_offset))                  \
	            : (comgen_eh_putb(self, DW_CFA_advance_loc4),        \
	               comgen_eh_putl(self, pc_offset)),                 \
	        0))
/* Generate instrumentation to move the CFA PC to the current position.
 * The  .cfi_* macros in  GNU AS automatically do  this whenever any of
 * them are used, and will  also move the CFA  PC such that it  equates
 * the current PC.
 * >> if (self->cg_CFA_loc < self->cg_txptr) {
 * >>     uint32_t delta;
 * >>     delta = (uint32_t)(uintptr_t)(self->cg_txptr - self->cg_CFA_loc);
 * >>     comgen_eh_DW_CFA_advance_loc(self, delta);
 * >>     self->cg_CFA_loc = self->cg_txptr;
 * >> }
 * NOTE: For all of the below macros, this function must be called _explicitly_! */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_movehere)(struct com_generator *__restrict self);


/* .cfi_offset <regno>, <offset> */
#define comgen_eh_DW_CFA_offset(self, regno, offset)                         \
	(void)(!comgen_ehok1(self) ||                                            \
	       (assert((offset) < 0 && ((-(offset)) % __SIZEOF_POINTER__) == 0), \
	        (regno) <= 0x3f                                                  \
	        ? (comgen_eh_putb(self, DW_CFA_offset | (regno)))                \
	        : (comgen_eh_putb(self, DW_CFA_offset_extended),                 \
	           comgen_eh_putuleb128(self, regno)),                           \
	        comgen_eh_putuleb128(self, (-(offset)) / __SIZEOF_POINTER__),    \
	        0))

/* .cfi_rel_offset <regno>, <offset> */
#define comgen_eh_DW_CFA_rel_offset(self, regno, rel_offset) \
	comgen_eh_DW_CFA_offset(self, regno, (rel_offset) - (self)->cg_cfa_offset)

/* .cfi_restore <regno> */
#define comgen_eh_DW_CFA_restore(self, regno)                  \
	(void)(!comgen_ehok1(self) ||                              \
	       ((regno) <= 0x3f                                    \
	        ? (comgen_eh_putb(self, DW_CFA_restore | (regno))) \
	        : (comgen_eh_putb(self, DW_CFA_restore_extended),  \
	           comgen_eh_putuleb128(self, regno)),             \
	        0))

/* .cfi_remember_state */
#define comgen_eh_DW_CFA_remember_state(self) \
	(void)(!comgen_ehav(self, 1) || (comgen_eh_putb(self, DW_CFA_remember_state), 0))

/* .cfi_restore_state */
#define comgen_eh_DW_CFA_restore_state(self) \
	(void)(!comgen_ehav(self, 1) || (comgen_eh_putb(self, DW_CFA_restore_state), 0))

/* .cfi_def_cfa <regno>, <offset> */
#define comgen_eh_DW_CFA_def_cfa(self, regno, offset)                     \
	(void)(assert(((offset) % __SIZEOF_POINTER__) == 0),                  \
	       !comgen_ehok1(self) ||                                         \
	       (comgen_eh_putb(self, DW_CFA_def_cfa_sf),                      \
	        comgen_eh_putuleb128(self, regno),                            \
	        comgen_eh_putsleb128(self, -((offset) / __SIZEOF_POINTER__)), \
	        0),                                                           \
	       (self)->cg_cfa_offset = (offset))

/* .cfi_def_cfa_offset <offset> */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL comgen_eh_DW_CFA_def_cfa_offset)(struct com_generator *__restrict self,
                                               int16_t offset);

/* .cfi_adjust_cfa_offset <delta> */
#define comgen_eh_DW_CFA_adjust_cfa_offset(self, delta) \
	comgen_eh_DW_CFA_def_cfa_offset(self, (self)->cg_cfa_offset + (delta))


/* Portable register names */
#ifdef __x86_64__
#define CFI_X86_UNWIND_REGISTER_PAX    CFI_X86_64_UNWIND_REGISTER_RAX
#define CFI_X86_UNWIND_REGISTER_PCX    CFI_X86_64_UNWIND_REGISTER_RCX
#define CFI_X86_UNWIND_REGISTER_PDX    CFI_X86_64_UNWIND_REGISTER_RDX
#define CFI_X86_UNWIND_REGISTER_PBX    CFI_X86_64_UNWIND_REGISTER_RBX
#define CFI_X86_UNWIND_REGISTER_PSP    CFI_X86_64_UNWIND_REGISTER_RSP
#define CFI_X86_UNWIND_REGISTER_PBP    CFI_X86_64_UNWIND_REGISTER_RBP
#define CFI_X86_UNWIND_REGISTER_PSI    CFI_X86_64_UNWIND_REGISTER_RSI
#define CFI_X86_UNWIND_REGISTER_PDI    CFI_X86_64_UNWIND_REGISTER_RDI
#define CFI_X86_UNWIND_REGISTER_PIP    CFI_X86_64_UNWIND_REGISTER_RIP
#define CFI_X86_UNWIND_REGISTER_PFLAGS CFI_X86_64_UNWIND_REGISTER_RFLAGS
#else /* __x86_64__ */
#define CFI_X86_UNWIND_REGISTER_PAX    CFI_386_UNWIND_REGISTER_EAX
#define CFI_X86_UNWIND_REGISTER_PCX    CFI_386_UNWIND_REGISTER_ECX
#define CFI_X86_UNWIND_REGISTER_PDX    CFI_386_UNWIND_REGISTER_EDX
#define CFI_X86_UNWIND_REGISTER_PBX    CFI_386_UNWIND_REGISTER_EBX
#define CFI_X86_UNWIND_REGISTER_PSP    CFI_386_UNWIND_REGISTER_ESP
#define CFI_X86_UNWIND_REGISTER_PBP    CFI_386_UNWIND_REGISTER_EBP
#define CFI_X86_UNWIND_REGISTER_PSI    CFI_386_UNWIND_REGISTER_ESI
#define CFI_X86_UNWIND_REGISTER_PDI    CFI_386_UNWIND_REGISTER_EDI
#define CFI_X86_UNWIND_REGISTER_PIP    CFI_386_UNWIND_REGISTER_EIP
#define CFI_X86_UNWIND_REGISTER_PFLAGS CFI_386_UNWIND_REGISTER_EFLAGS
#endif /* !__x86_64__ */
#endif /* GUARD_LIBSERVICE_ARCH_I386_WRAPPER_C */





/* When  the currently set  exception is RT-level, return
 * false. Otherwise, clear the exception and return true. */
INTDEF bool NOTHROW(FCALL libservice_aux_com_discard_nonrt_exception)(void);


/* Set `errno' to the error code associated with `info' */
INTDEF NOBLOCK NONNULL((2)) void
NOTHROW(FCALL libservice_aux_load_except_as_errno)(uintptr_t status,
                                                   struct service_comdesc *__restrict info);

/* Populate `except_data()' with the given information. */
INTDEF NOBLOCK NONNULL((2, 3)) void
NOTHROW(FCALL libservice_aux_load_except_as_error)(uintptr_t status,
                                                   struct service_comdesc *__restrict info,
                                                   void const *faultpc);


DECL_END

#endif /* !GUARD_LIBSERVICE_ARCH_I386_WRAPPER_H */
