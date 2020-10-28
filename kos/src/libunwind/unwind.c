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
#ifndef GUARD_LIBUNWIND_UNWIND_C
#define GUARD_LIBUNWIND_UNWIND_C 1
#define _KOS_SOURCE 1

#include "unwind.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stdbool.h>

#include <libdebuginfo/api.h> /* LIBDEBUGINFO_CC_IS_LIBUNWIND_CC */
#include <libunwind/unwind.h>

#include "eh_frame.h"

#ifndef __KERNEL__
#include <dlfcn.h>
#else /* !__KERNEL__ */
#include <kernel/vm/usermod.h> /* CONFIG_HAVE_USERMOD */
#endif /* __KERNEL__ */

DECL_BEGIN


/* NOTE: In kernel-space, `libuw_unwind_fde_find()' is
 *       implemented in `/kos/src/kernel/core/fs/driver.c' */
#ifndef __KERNEL__

PRIVATE NONNULL((2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_find_new)(void const *absolute_pc,
                                          unwind_fde_t *__restrict result) {
	void *module;
	unsigned int error;
	struct dl_section *eh_frame_sect;
	/* Lookup the module associated with the given program counter position. */
	module = dlgethandle(absolute_pc, DLGETHANDLE_FNORMAL);
	if unlikely(!module)
		ERROR(err);
	/* Lock the module's .eh_frame section into memory. */
	eh_frame_sect = dllocksection(module,
	                              ".eh_frame",
	                              DLLOCKSECTION_FNORMAL);
	if unlikely(!eh_frame_sect)
		ERROR(err);
	/* Scan the .eh_frame section of the associated module. */
	error = libuw_unwind_fde_scan((byte_t const *)eh_frame_sect->ds_data,
	                              (byte_t const *)eh_frame_sect->ds_data + eh_frame_sect->ds_size,
	                              absolute_pc,
	                              result,
	                              sizeof(void *));
	dlunlocksection(eh_frame_sect);
	return error;
err:
	return UNWIND_NO_FRAME;
}

/* Lookup FDE information associated with a given program counter position.
 * Using integration with KOS's DL extension APIs, this function automatically
 * accesses the `.eh_frame' sections of the module associated with the given
 * address, as well as keep track of a lazily allocated address-tree of FDE
 * caches for quick (O(1)) repeated access to an FDE located within a known
 * function. */
INTERN NONNULL((2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_find)(void const *absolute_pc,
                                      unwind_fde_t *__restrict result) {
	unsigned int error;
	/* TODO: Search the FDE-cache */
	error = libuw_unwind_fde_find_new(absolute_pc,
	                                  result);
	if (error == UNWIND_SUCCESS) {
		/* TODO: Cache the results */
	}
	return error;
}
DEFINE_PUBLIC_ALIAS(unwind_fde_find, libuw_unwind_fde_find);
#endif /* !__KERNEL__ */



/* Top-level function for unwinding the specific register state, automatically
 * locating the associated FDE entry, before using it to unwind the specified
 * register state.
 * NOTE: The given `ABSOLUTE_PC' should point _to_ or _into_ the instruction that
 *       should be unwound; Not after it. - i.e. range checking is done as:
 *       `absolute_pc >= start && absolute_pc < end'
 * @return: * : One of `UNWIND_*' (UNWIND_SUCCESS on success, other values on failure) */
INTERN NONNULL((2, 4)) unsigned int CC
linuw_unwind(void const *absolute_pc,
             unwind_getreg_t reg_getter, void const *reg_getter_arg,
             unwind_setreg_t reg_setter, void *reg_setter_arg) {
	unsigned int result;
	unwind_fde_t fde;
	result = libuw_unwind_fde_find(absolute_pc, &fde);
	if unlikely(result != UNWIND_SUCCESS)
		goto done;
#ifndef __OPTIMIZE_SIZE__
	/* Optimization for unwinding through signal frames! */
	if (fde.f_sigframe) {
		unwind_cfa_sigframe_state_t cfa;
		result = libuw_unwind_fde_sigframe_exec(&fde, &cfa, absolute_pc);
		if unlikely(result != UNWIND_SUCCESS)
			goto done;
		result = libuw_unwind_cfa_sigframe_apply(&cfa, &fde, absolute_pc,
		                                         reg_getter, reg_getter_arg,
		                                         reg_setter, reg_setter_arg);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		unwind_cfa_state_t cfa;
		result = libuw_unwind_fde_exec(&fde, &cfa, absolute_pc);
		if unlikely(result != UNWIND_SUCCESS)
			goto done;
		result = libuw_unwind_cfa_apply(&cfa, &fde, absolute_pc,
		                                reg_getter, reg_getter_arg,
		                                reg_setter, reg_setter_arg);
	}
done:
	return result;
}



DEFINE_PUBLIC_ALIAS(unwind, linuw_unwind);

/* In certain configurations, the kernel's `unwind_for_debug(3)'
 * is identical to its regular, old `unwind(3)' function. */
#ifdef __KERNEL__
#if !defined(CONFIG_HAVE_USERMOD) && defined(LIBDEBUGINFO_CC_IS_LIBUNWIND_CC)
DEFINE_PUBLIC_ALIAS(unwind_for_debug, linuw_unwind);
#endif /* !CONFIG_HAVE_USERMOD && LIBDEBUGINFO_CC_IS_LIBUNWIND_CC */
#endif /* __KERNEL__ */


DECL_END

#endif /* !GUARD_LIBUNWIND_UNWIND_C */
