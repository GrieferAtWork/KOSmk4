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
#ifndef _I386_KOS_KOS_KERNEL_UCONTEXT32_H
#define _I386_KOS_KOS_KERNEL_UCONTEXT32_H 1

/* File:
 *    <i386-kos/bits/ucontext32.h>
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

#include <bits/mcontext32.h> /* struct __mcontextx32 */
#include <bits/sigset.h>     /* struct __sigset_struct */
#include <bits/sigstack32.h> /* struct __sigaltstackx32 */

#if !defined(__x86_64__) && defined(__i386__)
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXTX32_MCONTEXT
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXTX32_SIGMASK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXTX32_STACK
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXTX32_LINK
#define __SIZEOF_UCONTEXT          __SIZEOF_UCONTEXTX32
#define __ALIGNOF_UCONTEXT         __ALIGNOF_UCONTEXTX32
#define __ucontextx32              ucontext
#endif /* !__x86_64__ && __i386__ */


#define __OFFSET_UCONTEXTX32_MCONTEXT 0
#define __OFFSET_UCONTEXTX32_SIGMASK  592
#define __OFFSET_UCONTEXTX32_STACK    720
#define __OFFSET_UCONTEXTX32_LINK     732
#define __SIZEOF_UCONTEXTX32          736
#define __ALIGNOF_UCONTEXTX32         __ALIGNOF_MCONTEXTX32

#ifdef __CC__
__DECL_BEGIN

#ifndef ____sigsetx32_t_defined
#define ____sigsetx32_t_defined 1
#ifdef __x86_64__
struct __sigset_structx32 {
	__UINT32_TYPE__ __val[__SIZEOF_SIGSET_T__ / 4];
};
#else /* __x86_64__ */
#define __sigset_structx32 __sigset_struct
#endif /* !__x86_64__ */
#endif /* !____sigsetx32_t_defined */


struct __ATTR_ALIGNED(__ALIGNOF_UCONTEXTX32) __ucontextx32 /*[NAME(ucontextx32)][PREFIX(uc_)]*/ {
	/* Userlevel context. */
	struct __mcontextx32                 uc_mcontext;
	struct __sigset_structx32            uc_sigmask;
	struct __sigaltstackx32              uc_stack;
	__HYBRID_PTR32(struct __ucontextx32) uc_link;
};

__DECL_END
#endif /* __CC__ */



#endif /* !_I386_KOS_KOS_KERNEL_UCONTEXT32_H */
