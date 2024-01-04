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
#ifndef _I386_KOS_BITS_OS_LINUX_UCONTEXT64_H
#define _I386_KOS_BITS_OS_LINUX_UCONTEXT64_H 1

/* File:
 *    <i386-kos/bits/os/linux/ucontext64.h>
 *
 * Definitions:
 *    - struct __ucontext_linux64 { ... };
 * #if defined(__linux__) && defined(__x86_64__)
 *    - struct ucontext { ... };
 * #endif
 */

#include <__stdinc.h>

#include <hybrid/__pointer.h> /* __HYBRID_PTR64() */
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/kos/sigstack64.h>   /* struct __sigaltstackx64 */
#include <bits/os/linux/mcontext64.h> /* struct __mcontext_linux64 */
#include <bits/os/sigset.h>           /* struct __sigset_struct */


#if defined(__linux__) && defined(__x86_64__)
#define __ucontext_linux64         ucontext
#define __OFFSET_UCONTEXT_FLAGS    __OFFSET_UCONTEXT_LINUX64_FLAGS
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXT_LINUX64_LINK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXT_LINUX64_STACK
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXT_LINUX64_MCONTEXT
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXT_LINUX64_SIGMASK
#define __OFFSET_UCONTEXT_FPREGS   __OFFSET_UCONTEXT_LINUX64_FPREGS
#define __SIZEOF_UCONTEXT          __SIZEOF_UCONTEXT_LINUX64
#define __ALIGNOF_UCONTEXT         __ALIGNOF_UCONTEXT_LINUX64
#endif /* __linux__ && __x86_64__ */

#define __OFFSET_UCONTEXT_LINUX64_FLAGS    0
#define __OFFSET_UCONTEXT_LINUX64_LINK     8
#define __OFFSET_UCONTEXT_LINUX64_STACK    16
#define __OFFSET_UCONTEXT_LINUX64_MCONTEXT (16 + __SIZEOF_SIGALTSTACKX64)
#define __OFFSET_UCONTEXT_LINUX64_SIGMASK  (16 + __SIZEOF_SIGALTSTACKX64 + __SIZEOF_MCONTEXT_LINUX64)
#define __OFFSET_UCONTEXT_LINUX64_FPREGS   (16 + __SIZEOF_SIGALTSTACKX64 + __SIZEOF_MCONTEXT_LINUX64 + __SIZEOF_SIGSET_T__)
#define __SIZEOF_UCONTEXT_LINUX64          (16 + __SIZEOF_SIGALTSTACKX64 + __SIZEOF_MCONTEXT_LINUX64 + __SIZEOF_SIGSET_T__ + __SIZEOF_LIBC_LINUX64_FPSTATE)
#define __ALIGNOF_UCONTEXT_LINUX64         8

#ifdef __CC__
__DECL_BEGIN

struct __ucontext_linux64 {
	/* Userlevel context. */
	__ULONGPTR_TYPE__               uc_flags;
	__HYBRID_PTR64(struct ucontext) uc_link;
	struct __sigaltstackx64         uc_stack;
	struct __mcontext_linux64       uc_mcontext;
	struct __sigset_struct          uc_sigmask;
	struct __libc_linux64_fpstate __fpregs_mem;
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_LINUX_UCONTEXT64_H */
