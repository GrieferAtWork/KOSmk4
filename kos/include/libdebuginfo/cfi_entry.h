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
#ifndef _LIBDEBUGINFO_CFI_ENTRY_H
#define _LIBDEBUGINFO_CFI_ENTRY_H 1

#include "api.h"
/**/

#include "debug_info.h"

#ifdef __CC__
__DECL_BEGIN


struct unwind_emulator_struct;

/* Run a sequence of DW_OP_* instructions as though they were being
 * invoked at the start of the current function. After this, any
 * stack-value left on the internal stack of `self' that was pushed
 * by the given instruction stream, wasn't there before, and refers
 * to a register location, will be replaced with a stack-local R-value
 * copy of that location, thus ensuring that any register accessed is
 * loaded by-value
 *
 * NOTE: This function will preserve and restore the original values of:
 *        - ue_pc         (Altered to point to the given `cfi_start_pc...cfi_end_pc' range)
 *        - ue_pc_start   (*ditto*)
 *        - ue_pc_end     (*ditto*)
 *        - ue_regget     (Register access is dispatched to register states as they were on function entry)
 *        - ue_regget_arg (*ditto*)
 *        - ue_regset     (Temporarily set to NULL to prevent register writes)
 *       ... before returning, regardless of what ends up being returned.
 *
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ... (May also be returned if a register counter not be reversed)
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
typedef __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) unsigned int
/*__NOTHROW_NCX*/ (LIBDEBUGINFO_CC *PDEBUGINFO_RUN_ENTRY_VALUE_EMULATOR)(struct unwind_emulator_struct *__restrict self,
                                                                         __byte_t const *cfi_start_pc,
                                                                         __byte_t const *cfi_end_pc);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_run_entry_value_emulator)(struct unwind_emulator_struct *__restrict self,
                                                                  __byte_t const *cfi_start_pc,
                                                                  __byte_t const *cfi_end_pc);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_CFI_ENTRY_H */
