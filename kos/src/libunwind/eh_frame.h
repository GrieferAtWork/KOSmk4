/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBUNWIND_EH_FRAME_H
#define GUARD_LIBUNWIND_EH_FRAME_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stdbool.h>

#include <libunwind/eh_frame.h>

DECL_BEGIN


/* Load the next eh_frame function  descriptor from `*peh_frame_reader', which  must
 * either be a  pointer to the  start of the  `.eh_frame' section, or  be the  value
 * written back to `*peh_frame_reader' after a previous call to `unwind_fde_load()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTDEF NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_load)(CHECKED byte_t const **__restrict peh_frame_reader,
                                      CHECKED byte_t const *eh_frame_end,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address);

/* Same as `unwind_fde_load()', but quickly search for and return the
 * FDE descriptor containing  the given  `absolute_pc' text  address.
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `absolute_pc'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTDEF NONNULL((4)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_scan)(CHECKED byte_t const *eh_frame_start,
                                      CHECKED byte_t const *eh_frame_end,
                                      CHECKED void const *absolute_pc,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address);


/* Execute CFA state  instruction until `absolute_pc'  has been  reached,
 * or  the entirety of  the FDE instruction code  has been executed. This
 * function is used to fill in CFA state information at a given  address,
 * which can then be used to unwind  a register state for the purpose  of
 * implementing language-level, zero-effort exception support, as well as
 * for generating tracebacks when combined with `libdebuginfo.so'
 * NOTE: Usually, the caller will have already ensured that:
 *       `self->f_pcstart <= absolute_pc && self->f_pcend >= absolute_pc'
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_exec)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                      unwind_cfa_state_t *__restrict result,
                                      CHECKED void const *absolute_pc);

/* Behaves  identical to `unwind_fde_exec()', and doesn't actually ever have to be
 * used, but performes better than `unwind_fde_exec()' when unwinding SIGNAL_FRAME
 * FDE  descriptors (though again:  use of this is  entirely optional; the regular
 * `unwind_fde_exec()' is just as capable  of unwinding signal frame  descriptors.
 * This function is  merely optimized  to better restore  registers commonly  used
 * within signal frames)
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_sigframe_exec)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                               unwind_cfa_sigframe_state_t *__restrict result,
                                               CHECKED void const *absolute_pc);

/* Behaves similar to `unwind_fde_exec()', but must  be used to calculate the  CFA
 * for the purpose of jumping to a  custom `landingpad_pc' as part of handling  an
 * exceptions which  originates from  `absolute_pc' within  the current  cfi-proc.
 * This function calculates the relative CFI-capsule offset between `absolute_pc',
 * and `landingpad_pc', as well as the GNU-argsize adjustment. Once this is  done,
 * the caller must use `unwind_cfa_landing_apply()' to apply these transformations
 * onto some given register state, which may then be used to resume execution.
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: CFA state descriptor, to-be filled with restore information upon success.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_landing_exec)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                              unwind_cfa_landing_state_t *__restrict result,
                                              CHECKED void const *absolute_pc,
                                              CHECKED void const *landingpad_pc);

/* Similar to `unwind_fde_exec()', but used to calculate the unwind rule
 * for `dw_regno' at the given text location. This is used to  implement
 * unwinding  for uncommon registers, since `unwind_fde_exec()' will not
 * already  calculate these during the first pass (thus keeping down the
 * memory requirements  imposed on  the one  responsible for  allocating
 * `unwind_cfa_state_t')
 * @param: self:   The FDE to execute in search of `absolute_pc'
 * @param: result: The CFA register result controller to-be filled.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_rule)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                      unwind_cfa_register_t *__restrict result,
                                      unwind_regno_t dw_regno,
                                      CHECKED void const *absolute_pc);

/* Same as `unwind_fde_exec()', however only calculate the CFA restore descriptor.
 * @return: UNWIND_SUCCESS:                 ...
 * @return: UNWIND_INVALID_REGISTER:        ...
 * @return: UNWIND_CFA_UNKNOWN_INSTRUCTION: ...
 * @return: UNWIND_CFA_ILLEGAL_INSTRUCTION: ...
 * @return: UNWIND_BADALLOC:                ... */
INTDEF NONNULL((1, 2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_exec_cfa)(unwind_fde_t *__restrict self, /* Only non-const for lazy initialized fields! */
                                          unwind_cfa_value_t *__restrict result,
                                          CHECKED void const *absolute_pc);

/* Apply  a given CFA  unwind state in order  to apply register information
 * from `reg_getter'  to `reg_setter'.  Note  however that  only  registers
 * with a rule other than `DW_CFA_register_rule_undefined' will be applied,
 * meaning  that `*reg_setter'  will not  get invoked  for these registers.
 * WARNING: This function will modify `self' in such a manner that repeated calls
 *          require  that `self' must be restored to its state prior to a call to
 *          this function before a repeated call can be made!
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTDEF NONNULL((1, 2, 4, 6)) unwind_errno_t CC
libuw_unwind_cfa_apply(unwind_cfa_state_t *__restrict self,
                       unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                       CHECKED void const *absolute_pc,
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
INTDEF NONNULL((1, 2, 4, 6)) unwind_errno_t CC
libuw_unwind_cfa_sigframe_apply(unwind_cfa_sigframe_state_t *__restrict self,
                                unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                                CHECKED void const *absolute_pc,
                                unwind_getreg_t reg_getter, void const *reg_getter_arg,
                                unwind_setreg_t reg_setter, void *reg_setter_arg);

/* For use with `unwind_fde_landing_exec()': Apply register rules previously calculated.
 * @param: self:        The CFA state to-be used when applying registers
 * @param: absolute_pc: Same value as was previously used to calculate `fde' from `self'
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTDEF NONNULL((1, 2, 4, 6)) unwind_errno_t CC
libuw_unwind_cfa_landing_apply(unwind_cfa_landing_state_t *__restrict self,
                               unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                               CHECKED void const *absolute_pc,
                               unwind_getreg_t reg_getter, void const *reg_getter_arg,
                               unwind_setreg_t reg_setter, void *reg_setter_arg);

/* Calculate the CFA (CanonicalFrameAddress) of the given CFA restore descriptor.
 * @param: self: The CFA state to-be used to calculate the CFA
 * @return: UNWIND_SUCCESS:               ...
 * @return: UNWIND_INVALID_REGISTER:      ...
 * @return: UNWIND_SEGFAULT:              ...
 * @return: UNWIND_EMULATOR_*:            ...
 * @return: UNWIND_APPLY_NOADDR_REGISTER: ... */
INTDEF NONNULL((1, 2, 3, 5)) unwind_errno_t CC
libuw_unwind_fde_calculate_cfa(unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                               unwind_cfa_value_t const *__restrict self,
                               unwind_getreg_t reg_getter,
                               void const *reg_callback_arg,
                               uintptr_t *__restrict presult);


DECL_END

#endif /* !GUARD_LIBUNWIND_EH_FRAME_H */
