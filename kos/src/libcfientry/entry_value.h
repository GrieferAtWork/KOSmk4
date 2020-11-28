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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBCFIENTRY_ENTRY_VALUE_H
#define GUARD_LIBCFIENTRY_ENTRY_VALUE_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <stdbool.h>

#include <libcfientry/entry_value.h>

DECL_BEGIN

/* Initialize/finalize a CFI-entry controller.
 * NOTE: Before calling `cfientry_init()', the caller must fill in:
 *       - self->ce_regget     (as [1..1])
 *       - self->ce_regget_arg (if needed)
 * @return: UNWIND_SUCCESS: Success
 * @return: * :             Error */
INTDEF WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(CC libcfientry_init)(struct cfientry *__restrict self);
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libcfientry_fini)(struct cfientry *__restrict self);

/* High-level register getter for register values as they were upon function entry.
 * This function can be used as a drop-in replacement anywhere that a `unwind_getreg_t'
 * function is required, and the given `arg' must be (writable) `struct cfientry'.
 *
 * The pre-defined prototype for this function requires that the first argument
 * be a pointer to a constant, however this isn't actually the case as far as the
 * internal implementation of this function goes. - `*arg' must be writable, and
 * may be altered by this function!
 *
 * @return: true:  Successfully reverse-engineered the value of `dw_regno'.
 * @return: false: Failed to reverse-engineered the value of `dw_regno'.
 * @return: false: The given `dw_regno' is an invalid register number for
 *                 the target intrinsically described by the host machine. */
INTDEF NONNULL((1, 3)) bool
NOTHROW_NCX(CC libcfientry_getreg)(/*struct cfientry **/ void const *arg,
                                   unwind_regno_t dw_regno,
                                   void *__restrict dst);


/* Run a sequence of DW_OP_* instructions where any register access is
 * dispatched through `cfientry_getreg'. After this, any stack-value
 * left on the internal stack of `self' that was pushed by the given
 * instruction stream, wasn't there before, and refers to a register
 * location, will be replaced with a stack-local R-value copy of that
 * location, thus ensuring that any register accessed is loaded by-value
 *
 * This function is implemented using the above functions, and is directly
 * called in order to implement the `DW_OP_GNU_entry_value' instruction,
 * as it may be encountered by `unwind_emulator_exec()'
 *
 * NOTE: This function will preserve and restore the original values of:
 *        - ue_pc         (Altered to point to the given `cfi_start_pc...cfi_end_pc' range)
 *        - ue_pc_start   (*ditto*)
 *        - ue_pc_end     (*ditto*)
 *        - ue_regget     (Temporarily set to &cfientry_getreg to dispatch register access via CFI-entry)
 *        - ue_regget_arg (*ditto*)
 *        - ue_regset     (Temporarily set to NULL to prevent register writes)
 *        - ue_objaddr    (Temporarily set to NULL; the specs even state that `DW_OP_push_object_address'
 *                         isn't allowed inside of entry-value expressions)
 *        - ue_piecewrite (Set to `0' to indicate that data is only to be read)
 *        - ue_piecebuf   (*ditto*)
 *        - ue_piecesiz   (*ditto*)
 *        - ue_piecebits  (*ditto*)
 *       ... before returning, regardless of what ends up being returned.
 *
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ... (May also be returned if a register counter not be reversed)
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
INTDEF WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libcfientry_run_unwind_emulator)(unwind_emulator_t *__restrict self,
                                                byte_t const *cfi_start_pc,
                                                byte_t const *cfi_end_pc);


DECL_END

#endif /* !GUARD_LIBCFIENTRY_ENTRY_VALUE_H */
