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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_NOPF_H
#define GUARD_LIBC_HYBRID_ARCH_I386_NOPF_H 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __CC__
DECL_BEGIN

/* Must declare these symbols as ELF.HIDDEN (INTDEF) in order to prevent
 * a relocation being generated during linking as the result of except.c
 * otherwise not knowing that these symbols are defined by libc itself. */
INTDEF __BYTE_TYPE__ const libc_x86_nopf_begin[];   /* Start address for NOPF memory access PC values */
INTDEF __BYTE_TYPE__ const libc_x86_nopf_end_clc[]; /* End of NOPF handlers that should return to `libc_x86_nopf_ret_stc' */
INTDEF __BYTE_TYPE__ const libc_x86_nopf_end[];     /* End address for NOPF memory access PC values */
INTDEF __BYTE_TYPE__ const libc_x86_nopf_ret_stc[]; /* Set the carry bit and return to the caller */
INTDEF __BYTE_TYPE__ const libc_x86_nopf_ret[];     /* Return PC for #PF with `libc_nopf_checkpc(pc) == true' */

/* Return the #PF-execution-resume address for a #PF that happened at `pc', where pc is
 * apart of a libc_x86_nopf_* function, as indicated by `libc_nopf_checkpc(pc) == true' */
#define libc_nopf_retof(pc)                              \
	((__BYTE_TYPE__ const *)(pc) < libc_x86_nopf_end_clc \
	 ? (__BYTE_TYPE__ const *)libc_x86_nopf_ret_stc      \
	 : (__BYTE_TYPE__ const *)libc_x86_nopf_ret)

#define libc_nopf_checkpc(pc)                              \
	((__BYTE_TYPE__ const *)(pc) >= libc_x86_nopf_begin && \
	 (__BYTE_TYPE__ const *)(pc) < libc_x86_nopf_end)

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_NOPF_H */
