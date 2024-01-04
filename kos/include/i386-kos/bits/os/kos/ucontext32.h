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
#ifndef _I386_KOS_BITS_OS_KOS_UCONTEXT32_H
#define _I386_KOS_BITS_OS_KOS_UCONTEXT32_H 1

/* File:
 *    <i386-kos/bits/os/kos/ucontext32.h>
 *
 * Definitions:
 *    - struct __ucontextx32 { ... };
 * #if !defined(__x86_64__) && defined(__i386__)
 *    - struct ucontext { ... };
 * #endif
 */

#include <__stdinc.h>

#include <hybrid/__pointer.h> /* __HYBRID_PTR32 */
#include <hybrid/host.h>      /* __x86_64__, __i386__ */
#include <hybrid/typecore.h>

#include <bits/os/kos/mcontext32.h> /* struct __mcontextx32 */
#include <bits/os/kos/sigstack32.h> /* struct __sigaltstackx32 */
#include <bits/os/sigset.h>         /* struct __sigset_struct */

#if !defined(__x86_64__) && defined(__i386__)
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXTX32_MCONTEXT
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXTX32_STACK
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXTX32_LINK
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXTX32_SIGMASK
#define __ALIGNOF_UCONTEXT         __ALIGNOF_UCONTEXTX32
#define __ucontextx32              ucontext
#endif /* !__x86_64__ && __i386__ */


#define __OFFSET_UCONTEXTX32_MCONTEXT 0
#define __OFFSET_UCONTEXTX32_STACK    592
#define __OFFSET_UCONTEXTX32_LINK     604
#define __OFFSET_UCONTEXTX32_SIGMASK  608
#define __ALIGNOF_UCONTEXTX32         __ALIGNOF_MCONTEXTX32

#ifdef __CC__
__DECL_BEGIN

#ifndef ____sigsetx32_t_defined
#define ____sigsetx32_t_defined
#if __SIZEOF_POINTER__ == 4
#define __sigset_structx32 __sigset_struct
#else /* __SIZEOF_POINTER__ == 4 */
struct __sigset_structx32 {
	__UINT32_TYPE__ __val[__SIZEOF_SIGSET_T__ / 4];
};
#endif /* !__SIZEOF_POINTER__ != 4 */
#endif /* !____sigsetx32_t_defined */

/* Userlevel context. */
struct __ATTR_ALIGNED(__ALIGNOF_UCONTEXTX32) __ucontextx32 /*[NAME(ucontextx32)][PREFIX(uc_)]*/ {
	struct __mcontextx32                 uc_mcontext;    /* CPU context. */
	struct __sigaltstackx32              uc_stack;       /* Program stack (only used for <ucontext.h>; currently meaningless in signal handlers) */
	__HYBRID_PTR32(struct __ucontextx32) uc_link;        /* [0..1] Linked context (only used for <ucontext.h>; NULL in signal handlers) */
	struct __sigset_structx32            uc_sigmask;     /* Signal mask to apply upon context load */
};

__DECL_END
#endif /* __CC__ */



#endif /* !_I386_KOS_BITS_OS_KOS_UCONTEXT32_H */
