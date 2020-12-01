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
#ifndef GUARD_LIBDEBUGINFO_CFI_ENTRY_C
#define GUARD_LIBDEBUGINFO_CFI_ENTRY_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>

#include <alloca.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/cfi_entry.h>
#include <libunwind/cfi.h>

#include "cfi_entry.h"
#include "unwind.h"

DECL_BEGIN

#ifndef __KERNEL__
PRIVATE void *libunwind = NULL;
INTERN WUNUSED void *CC dlopen_libunwind(void) {
	void *lu = ATOMIC_READ(libunwind);
	if (!lu) {
		void *real_lu;
		lu = dlopen(LIBUNWIND_LIBRARY_NAME, RTLD_LOCAL);
		if unlikely(!lu)
			goto done;
		real_lu = ATOMIC_CMPXCH_VAL(libunwind, NULL, lu);
		if unlikely(real_lu) {
			dlclose(lu);
			lu = real_lu;
		}
	}
done:
	return lu;
}

PRIVATE PUNWIND_EMULATOR_EXEC /*   */ pdyn_unwind_emulator_exec    = NULL;
PRIVATE PUNWIND_INSTRUCTION_SUCC /**/ pdyn_unwind_instruction_succ = NULL;
#define unwind_emulator_exec    (*pdyn_unwind_emulator_exec)
#define unwind_instruction_succ (*pdyn_unwind_instruction_succ)

PRIVATE bool CC load_libunwind(void) {
	void *lu;
	if (pdyn_unwind_emulator_exec)
		return true;
	COMPILER_BARRIER();
	lu = dlopen_libunwind();
	if unlikely(!lu)
		goto nope;
	COMPILER_BARRIER();
#define LOAD(ptr, name)                               \
	if ((*(void **)&(ptr) = dlsym(lu, name)) == NULL) \
		goto nope

	/* Lazily load functions from libunwind. */
	LOAD(pdyn_unwind_instruction_succ, "unwind_instruction_succ");
	COMPILER_BARRIER();
	LOAD(pdyn_unwind_emulator_exec, "unwind_emulator_exec");

	COMPILER_WRITE_BARRIER();
#undef LOAD
	return true;
nope:
	return false;
}

#endif /* !__KERNEL__ */

struct unwind_register {
	unwind_regno_t ur_regno;                             /* Register number. */
	byte_t         ur_data[CFI_UNWIND_REGISTER_MAXSIZE]; /* Unwind register data. */
};

struct cfientry {
	unwind_getreg_t ce_regget;     /* [1..1][const] Callback for reading out the value of a register.
	                                * This function is provided by the caller, and should return register
	                                * values as they'd appear at the position where the request is made
	                                * from. This function is then used internally to perform the initial
	                                * step of unwinding to the current function's call-site, at which
	                                * point libcfientry(3) will make an attempt to reverse-engineer the
	                                * values of requested registers. */
	union {
		void const *ce_regget_arg;  /* [?..?][const] Argument passed to `ce_regget'. */
		size_t     _ce_unwind_rega; /* # of allocated slots in `ce_unwind_regv' (used during start-up) */
	};
	/* Unwind register information: These descriptors override register values
	 * for the purpose of masking registers with new values as they'd appear at
	 * the respective call-sites following a call to `unwind(3)'
	 * As such, any arbitrary register from the call-site of the function containing
	 * an DW_OP_entry_value instruction is contained here-in, and is mainly intended
	 * to be used for evaluating expression of `DW_AT_GNU_call_site_value' and friends
	 * which are found from .debug_info of the module found at the PC-register (who's
	 * value should also be apart of this vector of overrides)
	 * As such, `DW_OP_entry_value' is evaluated by:
	 *   - unwind(3) with modified registers written to entries in `ce_unwind_regv'
	 *   - Execute code from the DW_OP_entry_value-block
	 *   - Register accesses first check if the requested register can be found
	 *     as part of the `ce_unwind_regv' vector. If it's inside, use that value.
	 *   - If the register cannot be found, scan .debug_info for call-site parameter
	 *     information on that register, and (if found) use that info.
	 *   - Memory accesses are always dispatched by searching for call-site paramter
	 *     information. */
	size_t                                          ce_unwind_regc;  /* # of register overrides found. */
	COMPILER_FLEXIBLE_ARRAY(struct unwind_register, ce_unwind_regv); /* [ce_unwind_regc] Vector of register overrides.
	                                                                  * Note that this vector is ascendingly sorted by
	                                                                  * an entry's `ur_regno', meaning you can use bsearch
	                                                                  * to find a specific entry within. */
};
#define cfientry_alloc(unwind_rega)                                        \
	((struct cfientry *)alloca(offsetof(struct cfientry, ce_unwind_regv) + \
	                           (unwind_rega) *                             \
	                           sizeof(struct unwind_register)))

/* Read the contents of a register after unwinding. When the value of `dw_regno'
 * wasn't specified by unwind information, then return its contents as they are
 * at the moment. iow: check `ce_unwind_regv', and if that doesn't mention `dw_regno',
 * simply forward the request to `arg->ce_regget'.
 * This function is used to facilitate register access inside of call-site parameter
 * expressions found in `DW_TAG_GNU_call_site_parameter:DW_AT_GNU_call_site_value'. */
PRIVATE NONNULL((1, 3)) bool
NOTHROW_NCX(LIBUNWIND_CC after_unwind_getreg)(/*struct cfientry **/ void const *arg,
                                              unwind_regno_t dw_regno,
                                              void *__restrict dst) {
	struct cfientry *self;
	size_t i;
	self = (struct cfientry *)arg;
	/* Check if the register can be found as part of unwind information. */
	BSEARCH(i, self->ce_unwind_regv, self->ce_unwind_regc, .ur_regno, dw_regno) {
		/* Found it! */
		memcpy(dst, self->ce_unwind_regv[i].ur_data,
		       CFI_REGISTER_SIZE(dw_regno));
		return true;
	}
	/* Forward the request to the underlying register accessor function. */
	return (*self->ce_regget)(self->ce_regget_arg, dw_regno, dst);
}


PRIVATE NONNULL((1, 3)) bool
NOTHROW_NCX(LIBUNWIND_CC cfi_getreg)(/*struct cfientry **/ void const *arg,
                                     unwind_regno_t dw_regno,
                                     void *__restrict dst) {
	struct cfientry *self;
	size_t i;
	self = (struct cfientry *)arg;

	/* First up: Check if the register can be found as part of unwind information.
	 *           It it can, then pretty much all of the hard work's already been
	 *           done and we can just read from there. */
	BSEARCH(i, self->ce_unwind_regv, self->ce_unwind_regc, .ur_regno, dw_regno) {
		/* Found it! */
		memcpy(dst, self->ce_unwind_regv[i].ur_data,
		       CFI_REGISTER_SIZE(dw_regno));
		return true;
	}

	/* Can't find register information from unwind data. As such, check
	 * if we can find information about the requested register as part
	 * of call-site parameter information. */

	/* TODO:
	 *  #1: Lazily load .debug_info (and related sections) for the module
	 *      currently loaded at `CFI_UNWIND_REGISTER_PC' (which be the
	 *      value of one of the entries of `ce_unwind_regv')
	 *  #2: Search for the DW_TAG_subprogram entry containing the call-site
	 *      program counter, and scan that component for `DW_TAG_GNU_call_site'
	 *      with a `DW_AT_location'-attribute that matches the register
	 *      expression currently being described by `dw_regno'.
	 *      Once found, load a different attribute `DW_AT_GNU_call_site_value'
	 *      from that same `DW_TAG_GNU_call_site'-component, which then contains
	 *      a CFI-expression that can be evaluated in order to calculate the
	 *      value that the requested register had at the time of the current
	 *      function being called.
	 *      NOTE: Register access from inside of this expression is performed
	 *            through use of `after_unwind_getreg()'. */
	(void)&after_unwind_getreg;

	return false;
}




/* Convert the given stack-entry into an R-value:
 *    - UNWIND_STE_REGISTER   -> UNWIND_STE_CONSTANT
 *    - UNWIND_STE_REGPOINTER -> UNWIND_STE_STACKVALUE */
PRIVATE NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC make_rvalue)(unwind_emulator_t *__restrict self,
                            unwind_ste_t *__restrict ste) {
	union {
		uintptr_t p;
		byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
	} regval;
	switch (ste->s_type) {

	case UNWIND_STE_REGISTER:
	case UNWIND_STE_REGPOINTER: {
		if unlikely(!cfi_getreg(self->ue_regget_arg, ste->s_register, regval.buf))
			goto err_invalid_register;
		/* Convert the stack-entry. */
		if (ste->s_type == UNWIND_STE_REGISTER) {
			ste->s_uconst = regval.p + ste->s_regoffset;
			ste->s_type   = UNWIND_STE_CONSTANT;
		} else {
			ste->s_uconst = regval.p;
			ste->s_type   = UNWIND_STE_STACKVALUE;
		}
	}	break;

	default:
		break;
	}
	return UNWIND_SUCCESS;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
}

PRIVATE NONNULL((1, 3)) bool LIBUNWIND_CC
cfi_entry_init_setreg(void *arg,
                      unwind_regno_t dw_regno,
                      void const *__restrict src) {
	struct cfientry *self;
	size_t index, lo, hi;
	self = (struct cfientry *)arg;
	lo   = 0;
	hi   = self->ce_unwind_regc;
	/* First up: Check if we've already seen this register. */
	for (;;) {
		index = (lo + hi) / 2;
		if (lo >= hi)
			break;
		if (dw_regno < self->ce_unwind_regv[index].ur_regno) {
			hi = index;
		} else if (dw_regno > self->ce_unwind_regv[index].ur_regno) {
			lo = index + 1;
		} else {
			/* Register had been set before. - Just override its old data-entry. */
			memcpy(self->ce_unwind_regv[index].ur_data,
			       src, CFI_REGISTER_SIZE(dw_regno));
			return true;
		}
	}
	/* Need another register override entry. */
	if (self->ce_unwind_regc < self->_ce_unwind_rega) {
		/* Must insert at `index' */
		memmoveup(&self->ce_unwind_regv[index + 1],
		          &self->ce_unwind_regv[index],
		          self->ce_unwind_regc - index,
		          sizeof(struct unwind_register));
		self->ce_unwind_regv[index].ur_regno = dw_regno;
		memcpy(self->ce_unwind_regv[index].ur_data,
		       src, CFI_REGISTER_SIZE(dw_regno));
	}
	/* Track the # of unwind registers. */
	++self->ce_unwind_regc;
	return true;
}


/* Initialize the given cfientry controller `self' by performing an `unwind_for_debug(3)'
 * from the point-of-view of the register state described by `regget' and `regget_arg'.
 * The caller must check if all registers overrides could be allocated, as this function
 * will simply set `self->ce_unwind_regc' to the exact # of overrides required, but will
 * only fill in the first `self->_ce_unwind_rega' of them! */
PRIVATE WUNUSED ATTR_NOINLINE NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC cfientry_init)(struct cfientry *__restrict self,
                              unwind_getreg_t regget,
                              void const *regget_arg) {
	unsigned int result;
	union {
		byte_t buf[CFI_REGISTER_SIZE(CFI_UNWIND_REGISTER_PC)];
		void *pc;
	} pc_buf;
	/* Lookup the origin PC (which we need for unwinding to the call-site) */
	if (!(*regget)(regget_arg, CFI_UNWIND_REGISTER_PC, pc_buf.buf)) {
		result = UNWIND_INVALID_REGISTER;
		goto done;
	}
	/* Use unwind_for_debug(3) because we can. */
	result = libdi_unwind_for_debug(pc_buf.pc, regget, regget_arg,
	                                &cfi_entry_init_setreg, self);
done:
	return result;
}

/* Special error-return value for `run_entry_value_emulator()' */
#define _UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS ((unsigned int)-10)

/* Worker-function for emulating instruction in entry-value context.
 * @param: unwind_rega:      The # of slots to allocate for unwind register overrides.
 * @param: preq_unwind_rega: When `_UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS' is
 *                           returned, write-back the # of required into this slot. */
PRIVATE WUNUSED ATTR_NOINLINE NONNULL((1)) unsigned int
NOTHROW_NCX(CC run_entry_value_emulator)(unwind_emulator_t *__restrict self,
                                         size_t unwind_rega,
                                         size_t *__restrict preq_unwind_rega) {
	unsigned int result;
	size_t old_stacksize;
	struct cfientry *ce;

	/* Allocate the CFI-entry controller. */
	ce = cfientry_alloc(unwind_rega);
	ce->_ce_unwind_rega = unwind_rega;
	ce->ce_unwind_regc  = 0;

	/* Initialize the CFI-entry controller. */
	result = cfientry_init(ce, self->ue_regget, self->ue_regget_arg);
	if (result != UNWIND_SUCCESS)
		goto done;

	/* Check if we need more space to hold all of the register overrides. */
	if (ce->ce_unwind_regc > ce->_ce_unwind_rega) {
		result            = _UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS;
		*preq_unwind_rega = ce->ce_unwind_regc;
		goto done;
	}

	/* Fill in the calle-register accessor callback of `ce' */
	ce->ce_regget     = self->ue_regget;
	ce->ce_regget_arg = self->ue_regget_arg;

	/* Re-configure `self' for executino. */
	old_stacksize       = self->ue_stacksz;
	self->ue_regget     = &cfi_getreg;
	self->ue_regget_arg = ce;

	/* Actually execution DW_OP_*-code. */
	result = unwind_emulator_exec(self);

	/* Convert all newly pushed register values into r-values! */
	if (result == UNWIND_SUCCESS && self->ue_stacksz > old_stacksize) {
		size_t i;
		for (i = old_stacksize; i < self->ue_stacksz; ++i) {
			unwind_ste_t *ste;
			ste    = &self->ue_stack[i];
			result = make_rvalue(self, ste);
			if unlikely(result != UNWIND_SUCCESS)
				break;
		}
	}

	/* Restore the old configuration of `self' */
	self->ue_regget     = ce->ce_regget;
	self->ue_regget_arg = ce->ce_regget_arg;
done:
	return result;
}


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
INTERN WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libdi_debuginfo_run_entry_value_emulator)(unwind_emulator_t *__restrict self,
                                                         byte_t const *cfi_start_pc,
                                                         byte_t const *cfi_end_pc) {
	unsigned int result;
	byte_t const *saved_pc;
	byte_t const *saved_pc_start;
	byte_t const *saved_pc_end;
	unwind_setreg_t saved_regset;
	void *saved_objaddr;
	uint8_t saved_piecewrite;
	byte_t *saved_piecebuf;
	size_t saved_piecesiz;
	size_t saved_piecebits;

#ifndef __KERNEL__
	/* Ensure that we've loaded the necessary symbols from libunwind.so */
	if unlikely(!load_libunwind())
		return UNWIND_EMULATOR_UNKNOWN_INSTRUCTION;
#endif /* !__KERNEL__ */

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
	self->ue_regset     = NULL;
	self->ue_objaddr    = NULL;
	self->ue_piecewrite = 0;
	self->ue_piecebuf   = NULL;
	self->ue_piecesiz   = 0;
	self->ue_piecebits  = 0;

	/* And invoke the emulator proper, which is now re-directed
	 * to dispatch register accesses using `libcfientry_getreg'
	 * from above. */
	{
		size_t req_unwind_rega = 8; /* XXX: Allow for an arch-specific hint for this value! */
		for (;;) {
			result = run_entry_value_emulator(self, req_unwind_rega, &req_unwind_rega);
			if (result != _UNWIND_TOO_FEW_UNWIND_REGISTER_OVERRIDE_SLOTS)
				break;
		}
	}

	/* Restore the old emulator state. */
	self->ue_pc         = saved_pc;
	self->ue_pc_start   = saved_pc_start;
	self->ue_pc_end     = saved_pc_end;
	self->ue_regset     = saved_regset;
	self->ue_objaddr    = saved_objaddr;
	self->ue_piecewrite = saved_piecewrite;
	self->ue_piecebuf   = saved_piecebuf;
	self->ue_piecesiz   = saved_piecesiz;
	self->ue_piecebits  = saved_piecebits;

	return result;
}


DEFINE_PUBLIC_ALIAS(debuginfo_run_entry_value_emulator, libdi_debuginfo_run_entry_value_emulator);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_CFI_ENTRY_C */
