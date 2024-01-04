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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_NOPF_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_NOPF_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

/* For reference as to what this file is for, see system headers:
 *  - <kos/nopf.h>
 *  - <kos/bits/nopf.h>
 *  - <i386-kos/kos/bits/nopf.h>
 */

#ifdef __CC__
DECL_BEGIN

DATDEF byte_t const x86_nopf_begin[];   /* Start address for NOPF memory access PC values */
DATDEF byte_t const x86_nopf_end_clc[]; /* End of NOPF handlers that should return to `x86_nopf_ret_stc' */
DATDEF byte_t const x86_nopf_end[];     /* End address for NOPF memory access PC values */
DATDEF byte_t const x86_nopf_ret_stc[]; /* Set the carry bit and return to the caller */
DATDEF byte_t const x86_nopf_ret[];     /* Return PC for #PF with `x86_nopf_check(pc) == true' */

/* Return  the #PF-execution-resume  address for a  #PF that happened  at `pc', where
 * pc is apart of a x86_nopf_* function, as indicated by `x86_nopf_check(pc) == true' */
#define x86_nopf_retof(pc)                   \
	((byte_t const *)(pc) < x86_nopf_end_clc \
	 ? (byte_t const *)x86_nopf_ret_stc      \
	 : (byte_t const *)x86_nopf_ret)

#define x86_nopf_check(pc)                     \
	((byte_t const *)(pc) >= x86_nopf_begin && \
	 (byte_t const *)(pc) < x86_nopf_end)

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_NOPF_H */
