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
#ifndef _I386_KOS_BITS_OS_CYGWIN_UCONTEXT64_H
#define _I386_KOS_BITS_OS_CYGWIN_UCONTEXT64_H 1

/* File:
 *    <i386-kos/bits/os/cygwin/ucontext64.h>
 *
 * Definitions:
 *    - struct __cygwin64_ucontext { ... };
 * #if defined(__CRT_CYG) && defined(__x86_64__)
 *    - struct ucontext { ... };
 * #endif
 */

#include <__stdinc.h>

#include <hybrid/__pointer.h> /* __HYBRID_PTR64 */
#include <hybrid/host.h>      /* __x86_64__, __i386__ */
#include <hybrid/typecore.h>  /* __ULONG64_TYPE__ */

#include <bits/os/cygwin/mcontext64.h> /* struct __cygwin64_mcontext */
#include <bits/os/kos/sigstack64.h>    /* struct __sigaltstackx64 */
#include <bits/os/sigset.h>            /* struct __sigset_struct */

#if defined(__CRT_CYG) && defined(__x86_64__)
#define __cygwin64_ucontext        ucontext
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_CYGWIN64_UCONTEXT_MCONTEXT
#define __OFFSET_UCONTEXT_LINK     __OFFSET_CYGWIN64_UCONTEXT_LINK
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_CYGWIN64_UCONTEXT_SIGMASK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_CYGWIN64_UCONTEXT_STACK
#define __OFFSET_UCONTEXT_FLAGS    __OFFSET_CYGWIN64_UCONTEXT_FLAGS
#define __SIZEOF_UCONTEXT          __SIZEOF_CYGWIN64_UCONTEXT
#define __ALIGNOF_UCONTEXT         __ALIGNOF_CYGWIN64_UCONTEXT
#endif /* __CRT_CYG && __x86_64__ */

#define __OFFSET_CYGWIN64_UCONTEXT_MCONTEXT   0
#define __OFFSET_CYGWIN64_UCONTEXT_LINK       1248
#define __OFFSET_CYGWIN64_UCONTEXT_SIGMASK    1256
#define __OFFSET_CYGWIN64_UCONTEXT_STACK      (1256 + __SIZEOF_SIGSET_T__)
#define __OFFSET_CYGWIN64_UCONTEXT_FLAGS      (1256 + __SIZEOF_SIGSET_T__ + __SIZEOF_SIGALTSTACKX64)
#define __OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS (1264 + __SIZEOF_SIGSET_T__ + __SIZEOF_SIGALTSTACKX64)
#if (__OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS % 16) != 0
#define __SIZEOF_CYGWIN64_UCONTEXT ((__OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS + 15) & ~15)
#else /* (__OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS % 16) != 0 */
#define __SIZEOF_CYGWIN64_UCONTEXT __OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS
#endif /* (__OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS % 16) == 0 */
#define __ALIGNOF_CYGWIN64_UCONTEXT 16

#ifdef __CC__
__DECL_BEGIN

struct __ATTR_ALIGNED(__ALIGNOF_CYGWIN64_UCONTEXT) __cygwin64_ucontext /*[NAME(cygwin64_ucontext)][PREFIX(uc_)]*/ {
	/* Userlevel context. */
	struct __cygwin64_mcontext                 uc_mcontext;
	__HYBRID_PTR64(struct __cygwin64_ucontext) uc_link;
	struct __sigset_struct                     uc_sigmask;
	struct __sigaltstackx64                    uc_stack;
	__ULONG64_TYPE__                           uc_flags;
#if (__OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS % 16) != 0
	__BYTE_TYPE__ __uc_pad[__SIZEOF_CYGWIN64_UCONTEXT - __OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS];
#endif /* (__OFFSETAFTER_CYGWIN64_UCONTEXT_FLAGS % 16) != 0 */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_CYGWIN_UCONTEXT64_H */
