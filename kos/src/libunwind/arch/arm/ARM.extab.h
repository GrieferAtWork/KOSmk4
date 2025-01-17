/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBUNWIND_ARCH_ARM_ARM_EXTAB_H
#define GUARD_LIBUNWIND_ARCH_ARM_ARM_EXTAB_H 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libunwind/ARM.extab.h>

DECL_BEGIN

/* Locate the entry corresponding to a given `absolute_pc' within a given `.ARM.exidx' section.
 * @return: * :   Address of `.ARM.exidx' entry corresponding to `absolute_pc'
 * @return: NULL: No unwind entry associated with `absolute_pc' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) struct ARM_exidx_entry const *
NOTHROW_NCX(CC libuw_unwind_ARM_exidx_locate)(byte_t const *ARM_exidx_start,
                                              byte_t const *ARM_exidx_end,
                                              void const *absolute_pc);


/* ABI runtime support unwind functions.
 *
 * Specs require programs that index these functions in `ARM_extab_entry::aete_perso_prel31'
 * to produce `R_ARM_NONE' relocations against them (even though these relocations don't end
 * up  being acted upon by the RTLD). However, since they're referenced, they have to appear
 * as publicly visible, and must therefor be apart of the public interface.
 *
 * For the sake of simplicity, these functions are implemented by libunwind, however  libc
 * also exports them via IFUNC aliases which in turn will lazily load and link against our
 * library ("libunwind.so"). */
INTDEF NONNULL((2, 3)) _Unwind_Reason_Code
NOTHROW_NCX(__LIBKCALL libuw___aeabi_unwind_cpp_pr0)(_Unwind_State state, _Unwind_Control_Block *ucbp,
                                                     _Unwind_Context *context);
INTDEF NONNULL((2, 3)) _Unwind_Reason_Code
NOTHROW_NCX(__LIBKCALL libuw___aeabi_unwind_cpp_pr1)(_Unwind_State state, _Unwind_Control_Block *ucbp,
                                                     _Unwind_Context *context);
INTDEF NONNULL((2, 3)) _Unwind_Reason_Code
NOTHROW_NCX(__LIBKCALL libuw___aeabi_unwind_cpp_pr2)(_Unwind_State state, _Unwind_Control_Block *ucbp,
                                                     _Unwind_Context *context);
INTDEF NONNULL((2, 3)) _Unwind_Reason_Code
NOTHROW_NCX(__LIBKCALL libuw___aeabi_unwind_cpp_prN)(_Unwind_State state, _Unwind_Control_Block *ucbp,
                                                     _Unwind_Context *context, unsigned int n);


DECL_END

#endif /* !GUARD_LIBUNWIND_ARCH_ARM_ARM_EXTAB_H */
