/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBUNWIND_EH_FRAME_H
#define GUARD_LIBUNWIND_EH_FRAME_H 1

#include "api.h"
#include <hybrid/compiler.h>
#include <libunwind/eh_frame.h>
#include <kos/types.h>
#include <stdbool.h>

DECL_BEGIN


/* Load the next eh_frame function descriptor from `*peh_frame_reader', which
 * must either be a pointer to the start of the `.eh_frame' section, to be the
 * value written back to `*peh_frame_reader' after a previous call to `unwind_fde_load()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTDEF NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_load)(byte_t **__restrict peh_frame_reader,
                                      byte_t *__restrict eh_frame_end,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address);

/* Same as `unwind_fde_load()', but quickly search for and return the
 * FDE descriptor containing the given `absolute_pc' text address.
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `ABSOLUTE_PC'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTDEF NONNULL((1, 2, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_scan)(byte_t *__restrict eh_frame_start,
                                      byte_t *__restrict eh_frame_end,
                                      void *absolute_pc,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address);


/* Execute CFA state instruction until `absolute_pc' has been reached,
 * or the entirety of the FDE instruction code has been executed.
 * This function is used to fill in CFA state information at a given address,
 * which can then be used to unwind a register state for the purpose of
 * implementing language-level, zero-effort exception support, as well
 * as for generating tracebacks when combined with `libdebuginfo.so'
 * NOTE: Usually, the caller will have already ensured that:
 *      `self->f_pcstart <= absolute_pc && self->f_pcend >= absolute_pc'
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec)(unwind_fde_t const *__restrict self,
                                      unwind_cfa_state_t *__restrict result,
                                      void *absolute_pc);

/* Behaves identical to `unwind_fde_exec()', and doesn't actually ever have to be
 * used, but performes better than `unwind_fde_exec()' when unwinding SIGNAL_FRAME
 * FDE descriptors (though again: use of this is entirely optional; the regular
 * `unwind_fde_exec()' is just as capable of unwinding signal frame descriptors.
 * This function is merely optimized to better restore registers commonly used
 * within signal frames)
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_sigframe_exec)(unwind_fde_t const *__restrict self,
                                               unwind_cfa_sigframe_state_t *__restrict result,
                                               void *absolute_pc);

/* Similar to `unwind_fde_exec()', but used to calculate the
 * unwind rule for `dw_regno' at the given text location.
 * This is used to implement unwinding for uncommon registers,
 * since `unwind_fde_exec()' will not already calculate these
 * during the first pass (thus keeping down the memory requirements
 * imposed on the one responsible for allocating `unwind_cfa_state_t')
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_rule)(unwind_fde_t const *__restrict self,
                                      unwind_cfa_register_t *__restrict result,
                                      __UINTPTR_HALF_TYPE__ dw_regno,
                                      void *absolute_pc);

/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa)(unwind_fde_t const *__restrict self,
                                          unwind_cfa_value_t *__restrict result,
                                          void *absolute_pc);


/* Similar to `unwind_fde_exec()', but only decode `DW_CFA_GNU_args_size' instructions
 * in order to calculate the proper exception_handler landing-pad-stack-adjustment that
 * is required to re-align the stack before jumping to a local exception handler.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_exec_landing_pad_adjustment)(unwind_fde_t const *__restrict self,
                                                             uintptr_t *__restrict psp_adjustment,
                                                             void *absolute_pc);


/* Apply a given CFA unwind state in order to apply register information from from reg_getter to reg_setter.
 * Note however that only registers with a rule other than `DW_CFA_register_rule_undefined'
 * will be applied, meaning that `*reg_setter' will not get invoked for these registers.
 * WARNING: This function will modify `self' in such a manner that repeated calls
 *          require that `self' must be restored to its state prior to a call to
 *          this function before a repeated call can be made!
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTDEF NONNULL((1, 2, 4, 6)) unsigned int CC
libuw_unwind_cfa_apply(unwind_cfa_state_t *__restrict self,
                       unwind_fde_t const *__restrict fde, void *absolute_pc,
                       unwind_getreg_t reg_getter, void const *reg_getter_arg,
                       unwind_setreg_t reg_setter, void *reg_setter_arg);

/* For use with `unwind_fde_sigframe_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTDEF NONNULL((1, 2, 4, 6)) unsigned int CC
libuw_unwind_cfa_sigframe_apply(unwind_cfa_sigframe_state_t *__restrict self,
                                unwind_fde_t const *__restrict fde, void *absolute_pc,
                                unwind_getreg_t reg_getter, void const *reg_getter_arg,
                                unwind_setreg_t reg_setter, void *reg_setter_arg);

/* Calculate the CFA (CanonicalFrameAddress) of the given CFA restore descriptor.
 * @param: self: The CFA state to-be used to calculate the CFA
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTDEF NONNULL((1, 2, 4)) unsigned int CC
libuw_unwind_cfa_calculate_cfa(unwind_cfa_value_t const *__restrict self,
                               unwind_getreg_t reg_getter,
                               void const *reg_callback_arg,
                               uintptr_t *__restrict presult);


DECL_END

#endif /* !GUARD_LIBUNWIND_EH_FRAME_H */
