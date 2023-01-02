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
#ifndef _I386_KOS_BITS_OS_CYGWIN_UCONTEXT32_H
#define _I386_KOS_BITS_OS_CYGWIN_UCONTEXT32_H 1

/* File:
 *    <i386-kos/bits/os/cygwin/ucontext32.h>
 *
 * Definitions:
 *    - struct __cygwin32_ucontext { ... };
 * #if defined(__CRT_CYG) && (!defined(__x86_64__) && defined(__i386__))
 *    - struct ucontext { ... };
 * #endif
 */

#include <__stdinc.h>

#include <hybrid/__pointer.h> /* __HYBRID_PTR32 */
#include <hybrid/host.h>      /* __x86_64__, __i386__ */
#include <hybrid/typecore.h>  /* __ULONG32_TYPE__ */

#include <bits/os/cygwin/mcontext32.h> /* struct __cygwin32_mcontext */
#include <bits/os/kos/sigstack32.h>    /* struct __sigaltstackx32 */
#include <bits/os/sigset.h>            /* struct __sigset_struct */

#if defined(__CRT_CYG) && (!defined(__x86_64__) && defined(__i386__))
#define __cygwin32_ucontext        ucontext
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_CYGWIN32_UCONTEXT_MCONTEXT
#define __OFFSET_UCONTEXT_LINK     __OFFSET_CYGWIN32_UCONTEXT_LINK
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_CYGWIN32_UCONTEXT_SIGMASK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_CYGWIN32_UCONTEXT_STACK
#define __OFFSET_UCONTEXT_FLAGS    __OFFSET_CYGWIN32_UCONTEXT_FLAGS
#define __SIZEOF_UCONTEXT          __SIZEOF_CYGWIN32_UCONTEXT
#define __ALIGNOF_UCONTEXT         __ALIGNOF_CYGWIN32_UCONTEXT
#endif /* __CRT_CYG && (!__x86_64__ && __i386__) */

#define __OFFSET_CYGWIN32_UCONTEXT_MCONTEXT 0
#define __OFFSET_CYGWIN32_UCONTEXT_LINK     724
#define __OFFSET_CYGWIN32_UCONTEXT_SIGMASK  728
#define __OFFSET_CYGWIN32_UCONTEXT_STACK    (728 + __SIZEOF_SIGSET_T__)
#define __OFFSET_CYGWIN32_UCONTEXT_FLAGS    (728 + __SIZEOF_SIGSET_T__ + __SIZEOF_SIGALTSTACKX32)
#define __SIZEOF_CYGWIN32_UCONTEXT          (732 + __SIZEOF_SIGSET_T__ + __SIZEOF_SIGALTSTACKX32)
#define __ALIGNOF_CYGWIN32_UCONTEXT         4

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

struct __cygwin32_ucontext /*[NAME(cygwin32_ucontext)][PREFIX(uc_)]*/ {
	/* Userlevel context. */
	struct __cygwin32_mcontext                 uc_mcontext;
	__HYBRID_PTR32(struct __cygwin32_ucontext) uc_link;
	struct __sigset_structx32                  uc_sigmask;
	struct __sigaltstackx32                    uc_stack;
	__ULONG32_TYPE__                           uc_flags;
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_CYGWIN_UCONTEXT32_H */
