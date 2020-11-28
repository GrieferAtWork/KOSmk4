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
#ifndef GUARD_LIBCFIENTRY_ENTRY_VALUE_C
#define GUARD_LIBCFIENTRY_ENTRY_VALUE_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <assert.h>
#include <string.h>

#include <libunwind/cfi.h>

#include "entry_value.h"

DECL_BEGIN

/* Initialize/finalize a CFI-entry controller.
 * NOTE: Before calling `cfientry_init()', the caller must fill in:
 *       - self->ce_regget     (as [1..1])
 *       - self->ce_regget_arg (if needed)
 * @return: UNWIND_SUCCESS: Success
 * @return: * :             Error */
INTERN WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(CC libcfientry_init)(struct cfientry *__restrict self) {
	assert(self->ce_regget);
	COMPILER_IMPURE();
	(void)self; /* TODO */
	return UNWIND_SUCCESS;
}

INTERN NONNULL((1)) void
NOTHROW_NCX(CC libcfientry_fini)(struct cfientry *__restrict self) {
	COMPILER_IMPURE();
	(void)self; /* TODO */
#ifndef NDEBUG
	memset(self, 0xcc, sizeof(*self));
#endif /* !NDEBUG */
}

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
INTERN NONNULL((1, 3)) bool
NOTHROW_NCX(CC libcfientry_getreg)(/*struct cfientry **/ void const *arg,
                                   unwind_regno_t dw_regno,
                                   void *__restrict dst) {
	struct cfientry *self;
	self = (struct cfientry *)arg;
	(void)self;     /* TODO */
	(void)dw_regno; /* TODO */
	(void)dst;      /* TODO */
	COMPILER_IMPURE();
	return false;
}


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
INTERN NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libcfientry_run_unwind_emulator)(unwind_emulator_t *__restrict self,
                                                byte_t const *cfi_start_pc,
                                                byte_t const *cfi_end_pc) {
	unsigned int result;
	struct cfientry ce;
	byte_t const *saved_pc;
	byte_t const *saved_pc_start;
	byte_t const *saved_pc_end;
	unwind_setreg_t saved_regset;
	void *saved_objaddr;
	uint8_t saved_piecewrite;
	byte_t *saved_piecebuf;
	size_t saved_piecesiz, saved_piecebits;

	/* Initialize the cfientry controller. */
	ce.ce_regget     = self->ue_regget;
	ce.ce_regget_arg = self->ue_regget_arg;
	result           = libcfientry_init(&ce);
	if unlikely(result != UNWIND_SUCCESS)
		goto done;

	/* Preserve the old emulator state. */
	saved_pc         = self->ue_pc;
	saved_pc_start   = self->ue_pc_start;
	saved_pc_end     = self->ue_pc_end;
	saved_regset     = self->ue_regset;
	saved_objaddr    = self->ue_objaddr;
	saved_piecewrite = self->ue_piecewrite;
	saved_piecebuf   = self->ue_piecebuf;
	saved_piecesiz   = self->ue_piecesiz;
	saved_piecebits  = self->ue_piecebits;

	/* Set-up the emulator to do our bidding. */
	self->ue_pc         = cfi_start_pc;
	self->ue_pc_start   = cfi_start_pc;
	self->ue_pc_end     = cfi_end_pc;
	self->ue_regget     = &libcfientry_getreg;
	self->ue_regget_arg = &ce;
	self->ue_regset     = NULL;
	self->ue_objaddr    = NULL;
	self->ue_piecewrite = 0;
	self->ue_piecebuf   = NULL;
	self->ue_piecesiz   = 0;
	self->ue_piecebits  = 0;

	/* And invoke the emulator proper, which is now re-directed
	 * to dispatch register accesses using `libcfientry_getreg'
	 * from above. */
	result = unwind_emulator_exec(self);

	/* Restore the old emulator state. */
	self->ue_pc         = saved_pc;
	self->ue_pc_start   = saved_pc_start;
	self->ue_pc_end     = saved_pc_end;
	self->ue_regget     = ce.ce_regget;
	self->ue_regget_arg = ce.ce_regget_arg;
	self->ue_regset     = saved_regset;
	self->ue_objaddr    = saved_objaddr;
	self->ue_piecewrite = saved_piecewrite;
	self->ue_piecebuf   = saved_piecebuf;
	self->ue_piecesiz   = saved_piecesiz;
	self->ue_piecebits  = saved_piecebits;

	/* TODO: Convert all newly pushed register values into r-values! */

	/* Finalize the cfientry controller. */
	libcfientry_fini(&ce);

done:
	return result;
}


/* Library exports */
DEFINE_PUBLIC_ALIAS(cfientry_init, libcfientry_init);
DEFINE_PUBLIC_ALIAS(cfientry_fini, libcfientry_fini);
DEFINE_PUBLIC_ALIAS(cfientry_getreg, libcfientry_getreg);
DEFINE_PUBLIC_ALIAS(cfientry_run_unwind_emulator, libcfientry_run_unwind_emulator);

DECL_END

#endif /* !GUARD_LIBCFIENTRY_ENTRY_VALUE_C */
