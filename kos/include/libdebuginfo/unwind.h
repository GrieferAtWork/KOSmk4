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
#ifndef _LIBDEBUGINFO_UNWIND_H
#define _LIBDEBUGINFO_UNWIND_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <kos/anno.h>

#include <libunwind/cfi.h>   /* unwind_getreg_t, unwind_setreg_t */
#include <libunwind/errno.h> /* unwind_errno_t */

#ifdef __CC__
__DECL_BEGIN

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
typedef __ATTR_NONNULL_T((2, 4)) unwind_errno_t
(LIBDEBUGINFO_CC *PUNWIND_FOR_DEBUG)(__CHECKED void const *__absolute_pc,
                                     unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                     unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((2, 4)) unwind_errno_t
(LIBDEBUGINFO_CC unwind_for_debug)(__CHECKED void const *__absolute_pc,
                                   unwind_getreg_t __reg_getter, void const *__reg_getter_arg,
                                   unwind_setreg_t __reg_setter, void *__reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_UNWIND_H */
