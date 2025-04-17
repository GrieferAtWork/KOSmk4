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
/*!included_by <bits/os/ucontext.h>*/
#ifndef _I386_KOS_BITS_OS_LINUX_UCONTEXT32_H
#define _I386_KOS_BITS_OS_LINUX_UCONTEXT32_H 1

/* File:
 *    <i386-kos/bits/os/linux/ucontext32.h>
 *
 * Definitions:
 *    - struct __ucontext_linux32 { ... };
 * #if defined(__linux__) && (!defined(__x86_64__) && defined(__i386__))
 *    - struct ucontext { ... };
 * #endif
 */

#include <__stdinc.h>

#include <hybrid/__pointer.h> /* __HYBRID_PTR32 */
#include <hybrid/host.h>      /* __x86_64__, __i386__ */
#include <hybrid/typecore.h>  /* __ULONG32_TYPE__ */

#include <bits/os/kos/sigstack32.h>   /* struct __sigaltstackx32 */
#include <bits/os/linux/mcontext32.h> /* struct __mcontext_linux32 */
#include <bits/os/sigset.h>           /* struct __sigset_struct */

#if ((defined(__linux__) || (defined(__KOS__) && __KOS_VERSION__ < 300)) && \
     (!defined(__x86_64__) && defined(__i386__)))
#define __ucontext_linux32         ucontext
#define __OFFSET_UCONTEXT_FLAGS    __OFFSET_UCONTEXT_LINUX32_FLAGS
#define __OFFSET_UCONTEXT_LINK     __OFFSET_UCONTEXT_LINUX32_LINK
#define __OFFSET_UCONTEXT_STACK    __OFFSET_UCONTEXT_LINUX32_STACK
#define __OFFSET_UCONTEXT_MCONTEXT __OFFSET_UCONTEXT_LINUX32_MCONTEXT
#define __OFFSET_UCONTEXT_SIGMASK  __OFFSET_UCONTEXT_LINUX32_SIGMASK
#define __OFFSET_UCONTEXT_FPREGS   __OFFSET_UCONTEXT_LINUX32_FPREGS
#define __SIZEOF_UCONTEXT          __SIZEOF_UCONTEXT_LINUX32
#define __ALIGNOF_UCONTEXT         __ALIGNOF_UCONTEXT_LINUX32
#endif /* (__linux__ || (__KOS__ && __KOS_VERSION__ < 300)) && (!__x86_64__ && __i386__) */

#define __OFFSET_UCONTEXT_LINUX32_FLAGS    0
#define __OFFSET_UCONTEXT_LINUX32_LINK     4
#define __OFFSET_UCONTEXT_LINUX32_STACK    8
#define __OFFSET_UCONTEXT_LINUX32_MCONTEXT (8 + __SIZEOF_SIGALTSTACKX32)
#define __OFFSET_UCONTEXT_LINUX32_SIGMASK  (8 + __SIZEOF_SIGALTSTACKX32 + __SIZEOF_MCONTEXT_LINUX32)
#define __OFFSET_UCONTEXT_LINUX32_FPREGS   (8 + __SIZEOF_SIGALTSTACKX32 + __SIZEOF_MCONTEXT_LINUX32 + __SIZEOF_SIGSET_T__) /* [FIELD(__fpregs_mem)] */
#define __SIZEOF_UCONTEXT_LINUX32          (8 + __SIZEOF_SIGALTSTACKX32 + __SIZEOF_MCONTEXT_LINUX32 + __SIZEOF_SIGSET_T__ + __SIZEOF_LIBC_LINUX32_FPSTATE)
#define __ALIGNOF_UCONTEXT_LINUX32         4

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
struct __ucontext_linux32 /*[NAME(ucontext_linux32)][PREFIX(uc_)]*/ {
	__ULONG32_TYPE__                          uc_flags;
	__HYBRID_PTR32(struct __ucontext_linux32) uc_link;
	struct __sigaltstackx32                   uc_stack;
	struct __mcontext_linux32                 uc_mcontext;
	struct __sigset_structx32                 uc_sigmask;
	struct __libc_linux32_fpstate           __fpregs_mem;
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_LINUX_UCONTEXT32_H */
