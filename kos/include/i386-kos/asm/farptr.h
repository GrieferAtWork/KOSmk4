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
#ifndef _I386_KOS_ASM_FARPTR_H
#define _I386_KOS_ASM_FARPTR_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

/* T &loadfarptr(T &x);
 * Return  a pointer to a far-off symbol,  regardless of the used memory model.
 * On x86_64, this is required for addressing symbols outside the -2GiB...+2Gib
 * range from within program text. */
#ifdef __x86_64__
#include <hybrid/typecore.h>

#define loadfarptr(symbol)                        \
	__XBLOCK({                                    \
		__register __UINT64_TYPE__ __fadr;        \
		__asm__("movabs %1, %0"                   \
		        : "=r" (__fadr)                   \
		        : "i" (&(symbol)));               \
		__XRETURN *(__typeof__(&(symbol)))__fadr; \
	})
#else /* __x86_64__ */
#define loadfarptr(symbol) \
	(symbol)
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_ASM_FARPTR_H */
