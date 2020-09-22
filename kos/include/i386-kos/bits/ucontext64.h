/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_UCONTEXT64_H
#define _I386_KOS_KOS_KERNEL_UCONTEXT64_H 1

/* File:
 *    <i386-kos/bits/ucontext64.h>
 * 
 * Definitions:
 *    - struct __ucontextx64 { ... };
 * #ifdef __x86_64__
 *    - struct ucontext { ... };
 * #endif
 */

#include <__stdinc.h>

#include <hybrid/__pointer.h> /* __HYBRID_PTR64 */
#include <hybrid/host.h>      /* __x86_64__ */

#include <bits/mcontext64.h>        /* struct __mcontextx64 */
#include <bits/os/kos/sigstack64.h> /* struct __sigaltstackx64 */
#include <bits/os/sigset.h>         /* struct __sigset_struct */

#ifdef __x86_64__
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXTX64_MCONTEXT
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXTX64_SIGMASK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXTX64_STACK
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXTX64_LINK
#define __SIZEOF_UCONTEXT          __SIZEOF_UCONTEXTX64
#define __ALIGNOF_UCONTEXT         __ALIGNOF_UCONTEXTX64
#define __ucontextx64              ucontext
#endif /* __x86_64__ */


#define __OFFSET_UCONTEXTX64_MCONTEXT 0
#define __OFFSET_UCONTEXTX64_SIGMASK  736
#define __OFFSET_UCONTEXTX64_STACK    864
#define __OFFSET_UCONTEXTX64_LINK     888
#define __SIZEOF_UCONTEXTX64          896
#define __ALIGNOF_UCONTEXTX64         __ALIGNOF_MCONTEXTX64
#ifdef __CC__
__DECL_BEGIN

struct __ATTR_ALIGNED(__ALIGNOF_UCONTEXTX64) __ucontextx64 /*[NAME(ucontextx64)][PREFIX(uc_)]*/ {
	/* Userlevel context. */
	struct __mcontextx64                 uc_mcontext;
	struct __sigset_struct               uc_sigmask;
	struct __sigaltstackx64              uc_stack;
	__HYBRID_PTR64(struct __ucontextx64) uc_link;
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_KERNEL_UCONTEXT64_H */
