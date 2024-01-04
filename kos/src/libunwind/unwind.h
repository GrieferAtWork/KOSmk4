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
#ifndef GUARD_LIBUNWIND_UNWIND_H
#define GUARD_LIBUNWIND_UNWIND_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stdbool.h>

#include <libunwind/unwind.h>

DECL_BEGIN

/* Lookup FDE information  associated with a  given program counter  position.
 * Using integration with KOS's DL extension APIs, this function automatically
 * accesses the `.eh_frame' sections of  the module associated with the  given
 * address, as well as  keep track of a  lazily allocated address-tree of  FDE
 * caches for quick (O(log2)) repeated access to an FDE located within a known
 * function. */
INTDEF NONNULL((2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_find)(VIRT void const *absolute_pc,
                                      unwind_fde_t *__restrict result);


/* Top-level function for unwinding the specific register state, automatically
 * locating the associated FDE entry, before using it to unwind the  specified
 * register state.
 * NOTE: The given `absolute_pc' should point _to_ or _into_ the instruction that
 *       should be  unwound; Not  after it.  - i.e.  range checking  is done  as:
 *       `absolute_pc >= start && absolute_pc < end'
 * @return: * : One of `UNWIND_*' (UNWIND_SUCCESS on success, other values on failure) */
INTDEF NONNULL((2, 4)) unwind_errno_t CC
linuw_unwind(VIRT void const *absolute_pc,
             unwind_getreg_t reg_getter, void const *reg_getter_arg,
             unwind_setreg_t reg_setter, void *reg_setter_arg);


DECL_END

#endif /* !GUARD_LIBUNWIND_UNWIND_H */
