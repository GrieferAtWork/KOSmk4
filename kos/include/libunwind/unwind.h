/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _LIBUNWIND_UNWIND_H
#define _LIBUNWIND_UNWIND_H 1

#include "api.h"

#include <features.h>

#include <bits/types.h>

#include <libunwind/arch-register.h>

#include "cfi.h"
#include "eh_frame.h"

/* High-level API functions for (optionally cached) queries
 * on FDE descriptors associated with arbitrary addresses.
 * NOTE: The internally kept FDE cache is cleared by `dlclearcaches()'
 */

#ifdef __CC__
__DECL_BEGIN

/* Register accessor callbacks for a variety of known cpu context structures. */
#ifndef __KERNEL__
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_UCONTEXT)(/*struct ucontext*/ void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_UCONTEXT)(/*struct ucontext*/ void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_GETREG_MCONTEXT)(/*struct mcontext*/ void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
typedef __ATTR_NONNULL((1, 3)) __BOOL (LIBUNWIND_CC *PUNWIND_SETREG_MCONTEXT)(/*struct mcontext*/ void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_ucontext)(/*struct ucontext*/ void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_ucontext)(/*struct ucontext*/ void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_getreg_mcontext)(/*struct mcontext*/ void const *arg, __UINTPTR_HALF_TYPE__ regno, void *__restrict dst);
LIBUNWIND_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBUNWIND_CC unwind_setreg_mcontext)(/*struct mcontext*/ void *arg, __UINTPTR_HALF_TYPE__ regno, void const *__restrict src);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

#ifndef LIBUNWIND_HAVE_ERROR_REGISTER_STATE_ACCESSORS
#define LIBUNWIND_HAVE_ERROR_REGISTER_STATE_ACCESSORS 1
typedef PUNWIND_GETREG_MCONTEXT PUNWIND_GETREG_ERROR_REGISTER_STATE;
typedef PUNWIND_SETREG_MCONTEXT PUNWIND_SETREG_ERROR_REGISTER_STATE;
#define UNWIND_GETREG_ERROR_REGISTER_STATE_NAME "unwind_getreg_mcontext"
#define UNWIND_SETREG_ERROR_REGISTER_STATE_NAME "unwind_setreg_mcontext"
#ifdef LIBUNWIND_WANT_PROTOTYPES
#define unwind_getreg_error_register_state       unwind_getreg_mcontext
#define unwind_setreg_error_register_state       unwind_setreg_mcontext
#endif /* LIBUNWIND_WANT_PROTOTYPES */
#endif /* !LIBUNWIND_HAVE_ERROR_REGISTER_STATE_ACCESSORS */
#endif /* !__KERNEL__ */



/* Lookup FDE information associated with a given program counter position.
 * Using integration with KOS's DL extension APIs, this function automatically
 * accesses the `.eh_frame' sections of the module associated with the given
 * address, as well as keep track of a lazily allocated address-tree of FDE
 * caches for quick (O(1)) repeated access to an FDE located within a known
 * function. */
typedef __ATTR_NONNULL((2)) unsigned int
(LIBUNWIND_CC *PUNWIND_FDE_FIND)(void *absolute_pc,
                                 unwind_fde_t *__restrict result);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((2)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind_fde_find)(void *absolute_pc,
                                            unwind_fde_t *__restrict result);
#endif /* LIBUNWIND_WANT_PROTOTYPES */


/* Top-level function for unwinding the specific register state, automatically
 * locating the associated FDE entry, before using it to unwind the specified
 * register state.
 * NOTE: The given `absolute_pc' should point _to_ the instruction that should
 *       be unwound; Not after it. - i.e. range checking is done as:
 *       `absolute_pc >= start && absolute_pc < end'
 * @return: * : One of `UNWIND_*' (UNWIND_SUCCESS on success, other values on failure) */
typedef __ATTR_NONNULL((2, 4)) unsigned int
(LIBUNWIND_CC *PUNWIND)(void *absolute_pc,
                        unwind_getreg_t reg_getter, void const *reg_getter_arg,
                        unwind_setreg_t reg_setter, void *reg_setter_arg);
#ifdef LIBUNWIND_WANT_PROTOTYPES
LIBUNWIND_DECL __ATTR_NONNULL((2, 4)) unsigned int
__NOTHROW_NCX(LIBUNWIND_CC unwind)(void *absolute_pc,
                                   unwind_getreg_t reg_getter, void const *reg_getter_arg,
                                   unwind_setreg_t reg_setter, void *reg_setter_arg);
#endif /* LIBUNWIND_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */


#endif /* !_LIBUNWIND_UNWIND_H */
