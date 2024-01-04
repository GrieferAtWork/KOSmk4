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
#ifndef _BITS_CRT_SETJMP_H
#define _BITS_CRT_SETJMP_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/os/sigset.h> /* struct __sigset_struct */

#ifdef __CC__
__DECL_BEGIN

/* Define like suggested here:
 * https://gcc.gnu.org/onlinedocs/gcc/Nonlocal-Gotos.html */
struct __jmp_buf {
	__INTPTR_TYPE__ __jb_regs[5];
};

#ifndef __KERNEL__
struct __sigjmp_buf {
	struct __jmp_buf       __sj_buf;
	/* Guess... */
	__UINTPTR_TYPE__       __sj_hassig;
	struct __sigset_struct __sj_sig;
};
#endif /* !__KERNEL__ */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_CRT_SETJMP_H */
