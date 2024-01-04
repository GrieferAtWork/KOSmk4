/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDEBUGINFO_UNWIND_H
#define GUARD_LIBDEBUGINFO_UNWIND_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libdebuginfo/unwind.h>
#include <libunwind/errno.h>

/* Figure out if unwind_for_debug() has already been defined externally somehow. */
#undef HAVE_UNWIND_FOR_DEBUG_EXTERNALLY
#ifdef __KERNEL__
#define HAVE_UNWIND_FOR_DEBUG_EXTERNALLY 1 /* Defined in `/kos/src/kernel/core/memory/mman/module.c' */
#endif /* __KERNEL__ */

DECL_BEGIN

#ifndef HAVE_UNWIND_FOR_DEBUG_EXTERNALLY
/* Same as the regular unwind(3) (from libunwind.so), however (if configured),
 * this  one also handles the case where `absolute_pc' points into user-space,
 * allowing user-space text locations to be correctly unwound.
 * NOTE: This function should only be used when printing tracebacks for
 *       debugging purposes, but _NEVER_  for the purpose of  something
 *       like exception unwinding!
 * To improve the success-rate of unwinding, this function does a number of things:
 *   - Try to make use of the regular, old `unwind(3)' from `libunwind.so'
 *   - Make use of DWARF `.debug_frame' debug information (if present)
 *   - Inspect/emulate  the underlying program  text to detect patterns
 *     that lead to known return instructions. Though this is only done
 *     if implemented and supported for the hosting architecture.
 * Also note that in kernel-space, once the kernel has been poisoned, no
 * additional user-space module information can be loaded, and unwinding
 * for user-space location for which the kernel doesn't already know how
 * to unwind them will fail with `UNWIND_NO_FRAME'.
 * @return: * : One of `UNWIND_*' (UNWIND_SUCCESS on success, other values on failure) */
INTDEF NONNULL((2, 4)) unwind_errno_t CC
libdi_unwind_for_debug(void const *absolute_pc,
                       unwind_getreg_t reg_getter, void const *reg_getter_arg,
                       unwind_setreg_t reg_setter, void *reg_setter_arg);
#endif /* !HAVE_UNWIND_FOR_DEBUG_EXTERNALLY */

#ifdef HAVE_UNWIND_FOR_DEBUG_EXTERNALLY
extern NONNULL((2, 4)) unwind_errno_t CC
libdi_unwind_for_debug(void const *absolute_pc,
                       unwind_getreg_t reg_getter, void const *reg_getter_arg,
                       unwind_setreg_t reg_setter, void *reg_setter_arg)
	ASMNAME("unwind_for_debug");
#endif /* HAVE_UNWIND_FOR_DEBUG_EXTERNALLY */

DECL_END


#endif /* !GUARD_LIBDEBUGINFO_UNWIND_H */
