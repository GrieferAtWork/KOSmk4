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
#ifndef _I386_KOS_BITS_OS_KOS_UCONTEXT64_H
#define _I386_KOS_BITS_OS_KOS_UCONTEXT64_H 1

/* File:
 *    <i386-kos/bits/os/kos/ucontext64.h>
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

#include <bits/os/kos/mcontext64.h> /* struct __mcontextx64 */
#include <bits/os/kos/sigstack64.h> /* struct __sigaltstackx64 */
#include <bits/os/sigset.h>         /* struct __sigset_struct */

#ifdef __x86_64__
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXTX64_MCONTEXT
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXTX64_STACK
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXTX64_LINK
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXTX64_SIGMASK
#define __ALIGNOF_UCONTEXT         __ALIGNOF_UCONTEXTX64
#define __ucontextx64              ucontext
#endif /* __x86_64__ */


#define __OFFSET_UCONTEXTX64_MCONTEXT 0
#define __OFFSET_UCONTEXTX64_STACK    736
#define __OFFSET_UCONTEXTX64_LINK     760
#define __OFFSET_UCONTEXTX64_SIGMASK  768
#define __ALIGNOF_UCONTEXTX64         __ALIGNOF_MCONTEXTX64
#ifdef __CC__
__DECL_BEGIN

struct __ATTR_ALIGNED(__ALIGNOF_UCONTEXTX64) __ucontextx64 /*[NAME(ucontextx64)][PREFIX(uc_)]*/ {
	struct __mcontextx64                 uc_mcontext;    /* CPU context. */
	struct __sigaltstackx64              uc_stack;       /* Program stack (only used for <ucontext.h>; currently meaningless in signal handlers) */
	__HYBRID_PTR64(struct __ucontextx64) uc_link;        /* [0..1] Linked context (only used for <ucontext.h>; NULL in signal handlers) */
	struct __sigset_struct               uc_sigmask;     /* Signal mask to apply upon context load */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_OS_KOS_UCONTEXT64_H */
