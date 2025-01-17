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
#ifndef _I386_KOS_BITS_CRT_SETJMP_H
#define _I386_KOS_BITS_CRT_SETJMP_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/sigset.h> /* struct __sigset_struct */

__DECL_BEGIN

#ifdef __CRT_DOS_PRIMARY
#if defined(__x86_64__)
#define __JMP_BUF_ALIGN 16
#define __JMP_BUF_SIZE  256
#elif defined(__i386__)
#define __JMP_BUF_SIZE  64
#elif defined(__arm__)
#define __JMP_BUF_SIZE  112
#endif /* ... */

#ifdef __CC__
#ifdef __JMP_BUF_ALIGN
__ATTR_ALIGNED(__JMP_BUF_ALIGN)
#else /* __JMP_BUF_ALIGN */
__ATTR_ALIGNED(__SIZEOF_POINTER__)
#endif /* !__JMP_BUF_ALIGN */
struct __jmp_buf {
	__BYTE_TYPE__ __data[__JMP_BUF_SIZE];
};
#endif /* __CC__ */

#elif defined(__x86_64__)

/************************************************************************/
/* 64-bit                                                               */
/************************************************************************/
#ifdef __CC__
struct __jmp_buf {
	__UINTPTR_TYPE__ __rbx, __rbp, __r12, __r13;
	__UINTPTR_TYPE__ __r14, __r15, __rsp, __rip;
};
#endif /* __CC__ */

#else /* ... */

/************************************************************************/
/* 32-bit                                                               */
/************************************************************************/
#ifdef __CC__
struct __jmp_buf {
	__UINTPTR_TYPE__ __ebx, __esp, __ebp;
	__UINTPTR_TYPE__ __esi, __edi, __eip;
	__UINTPTR_TYPE__ __padding[2];
};
#endif /* __CC__ */

#endif /* !... */


#ifdef __CC__
#ifndef __KERNEL__
struct __sigjmp_buf {
	struct __jmp_buf       __sj_buf;    /* regular jump buffer (NOTE:  `__padding[0] != 0'
	                                     * is used to indicate the validity of `__sj_sig') */
#ifdef __x86_64__
	__UINTPTR_TYPE__       __sj_hassig; /* non-zero if a signal set is present. */
#endif /* __x86_64__ */
	struct __sigset_struct __sj_sig;    /* Signal set to be restored before jumping (if given). */
};
#endif /* !__KERNEL__ */
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_BITS_CRT_SETJMP_H */
