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
#ifndef _LIBCFIENTRY_ENTRY_VALUE_H
#define _LIBCFIENTRY_ENTRY_VALUE_H 1

#include "api.h"
/**/

#include <libunwind/cfi.h>

/* >> libcfientry(3)
 *
 * Support library for reverse emulation of native machine instruction
 * for the purpose of decoding registers states that were once present
 * when some function was called.
 *
 * This library is used to implement support for the `DW_OP_GNU_entry_value'
 * CFI instruction, which can be used to retrieve the value of a register
 * or memory location at the time a function was entered. Note that for this
 * purpose, only register locations can (possibly) be reverse engineered.
 *
 * The DWARF specs state that in order to calculate the values of registers
 * upon function-entry, one should record those values whenever a function
 * is entered. - That's total BS if you ask me: It's ABSOLUTELY, ENTIRELTY,
 * COMPLETELY UNFEASABLE to set a breakpoint at the start of _EVERY_ function
 * in existence, only to somehow keep track of register values, just so one
 * can deal with the slim chance that those values would be needed at some
 * later point in time.
 * And that isn't even to mention that doing something like this would require
 * one to also load debug information of every executable module, as that
 * module is loaded, which would add even more absurd overhead, and that isn't
 * even to mention the problem that the act of loading more stuff into memory
 * would most definitely require at least 1 function call, which in turn would
 * also have to have its registers recorded, immediately leading to a logic
 * loop.
 *
 * So no DWARF specs. - I won't set a breakpoint on every function. I'll go
 * a different route and do the only sane thing that one can do in order to
 * support this opcode:
 *
 * libcfientry(3) can be used to unwind an abstract register state (using the
 * normal unwind machinery from libunwind(3)), following which arch-specific
 * code will try to decompile the instruction immediately preceding the return
 * address acquired during unwinding.
 * From there on, libcfientry(3) will try to re-construct register values as
 * they were prior to the call, which can then be used to provide values to
 * `DW_OP_GNU_entry_value' as they are needed.
 *
 * This works best when function arguments loaded from constants, or loaded
 * from fixed offsets added to callee-preserve registers.
 *
 * NOTE: This library makes no effort to guaranty that any value it returns
 *       was actually what was passed to some function, simply because there
 *       is no way of re-constructing such a value without fail, because:
 *
 *         - The return address may have been custom-made, and the actual
 *           register value that libcfientry(3) was supposed to retrieve
 *           was filled in from somewhere completely different that where
 *           the return-pointer points at.
 *
 *         - Assembly at the call-site may look like this:
 *           >>    mov  $1234, %REG0
 *           >>    jX   .Lcall_function
 *           >>    mov  $4321, %REG0
 *           >> .Lcall_function:
 *           >>    call some_function
 *           If we're not supposed to re-construct the value of %REG0 at
 *           the time the call to `some_function' was made, you're out of
 *           luck, because libcfientry(3) would always just tell you that
 *           the register you were asking for had the value 4321.
 *           If this library was supposed to properly reconstruct control
 *           flow in its entirety, not only would this increase complexity
 *           by an insane factor, but it would only lead to the unavoidable
 *           consequence that a register may have had more than 1 value at
 *           the time that a call was made.
 *           And taking this thought even further, who's to say that some
 *           other piece of assembly in memory doesn't look like this:
 *           >>    mov  $1, %REG0
 *           >>    jmp  .Lcall_function
 *           >>    mov  $2, %REG0
 *           >>    jmp  .Lcall_function
 *           >>    ...
 *           >>    mov  $0xffffffff, %REG0
 *           >>    jmp  .Lcall_function
 *           The answer is: you'd never be find a definitive answer if you
 *           wanted to take arbitrary call-sites into account, so just keep
 *           it simple, and assume that a function call only ever loads
 *           arguments immediately prior to the actual call, and no other
 *           code could possibly jump into the middle of argument loading,
 *           or forge return addresses.
 */


#ifdef __CC__
__DECL_BEGIN

struct cfientry {
	unwind_getreg_t ce_regget;     /* [1..1][const] Callback for reading out the value of a register.
	                                * This function is provided by the caller, and should return register
	                                * values as they'd appear at the position where the request is made
	                                * from. This function is then used internally to perform the initial
	                                * step of unwinding to the current function's call-site, at which
	                                * point libcfientry(3) will make an attempt to reverse-engineer the
	                                * values of requested registers. */
	void const     *ce_regget_arg; /* [?..?][const] Argument passed to `ce_regget'. */
	/* TODO: Internal state (implementation-details managed by the below API-functions) */
};

/* Initialize/finalize a CFI-entry controller.
 * NOTE: Before calling `cfientry_init()', the caller must fill in:
 *       - self->ce_regget     (as [1..1])
 *       - self->ce_regget_arg (if needed)
 * @return: UNWIND_SUCCESS: Success
 * @return: * :             Error */
typedef __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned int
/*__NOTHROW_NCX*/ (LIBCFIENTRY_CC *PCFIENTRY_INIT)(struct cfientry *__restrict self);
typedef __ATTR_NONNULL((1)) void
/*__NOTHROW_NCX*/ (LIBCFIENTRY_CC *PCFIENTRY_FINI)(struct cfientry *__restrict self);
#ifdef LIBCFIENTRY_WANT_PROTOTYPES
LIBCFIENTRY_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned int
__NOTHROW_NCX(LIBCFIENTRY_CC cfientry_init)(struct cfientry *__restrict self);
LIBCFIENTRY_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBCFIENTRY_CC cfientry_fini)(struct cfientry *__restrict self);
#endif /* LIBCFIENTRY_WANT_PROTOTYPES */


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
typedef __ATTR_NONNULL((1, 3)) __BOOL
/*__NOTHROW_NCX*/ (LIBUNWIND_CC *PCFIENTRY_GETREG)(/*struct cfientry **/ void const *arg,
                                                   unwind_regno_t dw_regno,
                                                   void *__restrict dst);
#ifdef LIBCFIENTRY_WANT_PROTOTYPES
LIBCFIENTRY_DECL __ATTR_NONNULL((1, 3)) __BOOL
__NOTHROW_NCX(LIBUNWIND_CC cfientry_getreg)(/*struct cfientry **/ void const *arg,
                                            unwind_regno_t dw_regno,
                                            void *__restrict dst);
#endif /* LIBCFIENTRY_WANT_PROTOTYPES */



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
typedef __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) unsigned int
/*__NOTHROW_NCX*/ (LIBUNWIND_CC *PCFIENTRY_RUN_UNWIND_EMULATOR)(unwind_emulator_t *__restrict self,
                                                                __byte_t const *cfi_start_pc,
                                                                __byte_t const *cfi_end_pc);
#ifdef LIBCFIENTRY_WANT_PROTOTYPES
LIBCFIENTRY_DECL __ATTR_NONNULL((1, 2, 3)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC cfientry_run_unwind_emulator)(unwind_emulator_t *__restrict self,
                                                         __byte_t const *cfi_start_pc,
                                                         __byte_t const *cfi_end_pc);
#endif /* LIBCFIENTRY_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBCFIENTRY_ENTRY_VALUE_H */
