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
#ifndef _I386_KOS_BITS_OS_KOS_SIGACTION64_H
#define _I386_KOS_BITS_OS_KOS_SIGACTION64_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigaction64.h>
 *
 * Definitions:
 *    - struct __sigactionx64 { ... };
 *    - typedef ... __sigactionx64_sa_handler_t;
 * #ifdef __x86_64__
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/os/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>

#ifdef __x86_64__
/* Portable system feature spec macros */
#define __ARCH_HAVE_SIGACTION_SA_RESTORER
#define __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
#define __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION

/* Portable names */
#define __OFFSET_SIGACTION_HANDLER         __OFFSET_SIGACTIONX64_HANDLER
#define __OFFSET_SIGACTION_SIGACTION       __OFFSET_SIGACTIONX64_SIGACTION
#define __OFFSET_SIGACTION_FLAGS           __OFFSET_SIGACTIONX64_FLAGS
#define __OFFSET_SIGACTION_RESTORER        __OFFSET_SIGACTIONX64_RESTORER
#define __OFFSET_SIGACTION_MASK            __OFFSET_SIGACTIONX64_MASK
#define __SIZEOF_SIGACTION                 __SIZEOF_SIGACTIONX64
#define __ALIGNOF_SIGACTION                __ALIGNOF_SIGACTIONX64
#define __OFFSET_KERNEL_SIGACTION_HANDLER  __OFFSET_KERNEL_SIGACTIONX64_HANDLER
#define __OFFSET_KERNEL_SIGACTION_FLAGS    __OFFSET_KERNEL_SIGACTIONX64_FLAGS
#define __OFFSET_KERNEL_SIGACTION_RESTORER __OFFSET_KERNEL_SIGACTIONX64_RESTORER
#define __OFFSET_KERNEL_SIGACTION_MASK     __OFFSET_KERNEL_SIGACTIONX64_MASK
#define __ALIGNOF_KERNEL_SIGACTION         __ALIGNOF_KERNEL_SIGACTIONX64
#define __sigaction_sa_handler_t           __sigactionx64_sa_handler_t
#define __sigaction_sa_restorer_t          __sigactionx64_sa_restorer_t
#define __sigaction_sa_sigaction_t         __sigactionx64_sa_sigaction_t
#define __sigactionx64                     sigaction
#define __kernel_sigaction                 sigaction /* Binary compatible! */
#if defined(__KERNEL__) || defined(__USE_KOS_KERNEL)
#define kernel_sigaction sigaction /* Binary compatible! */
#endif /* __KERNEL__ || __USE_KOS_KERNEL */
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
#define __sigactionx64_sa_handler_t __sighandler_t
#endif /* !____sighandler_t_defined */
#endif /* __x86_64__ */


#define __OFFSET_SIGACTIONX64_HANDLER   0
#define __OFFSET_SIGACTIONX64_SIGACTION 0
#define __OFFSET_SIGACTIONX64_FLAGS     8
#define __OFFSET_SIGACTIONX64_RESTORER  16
#define __OFFSET_SIGACTIONX64_MASK      24
#define __SIZEOF_SIGACTIONX64           (24 + __SIZEOF_SIGSET_T__)
#define __ALIGNOF_SIGACTIONX64          8

#define __OFFSET_KERNEL_SIGACTIONX64_HANDLER   __OFFSET_SIGACTIONX64_HANDLER
#define __OFFSET_KERNEL_SIGACTIONX64_FLAGS     __OFFSET_SIGACTIONX64_FLAGS
#define __OFFSET_KERNEL_SIGACTIONX64_RESTORER  __OFFSET_SIGACTIONX64_RESTORER
#define __OFFSET_KERNEL_SIGACTIONX64_MASK      __OFFSET_SIGACTIONX64_MASK
#define __ALIGNOF_KERNEL_SIGACTIONX64          __ALIGNOF_SIGACTIONX64
/* No sizeof, because actual size is flexible. */

#ifdef __CC__
__DECL_BEGIN

#ifdef __x86_64__
typedef void (__ATTR_SYSVABI *__sigactionx64_sa_handler_t)(int __signo);
typedef void (__ATTR_SYSVABI *__sigactionx64_sa_restorer_t)(void);
struct __siginfo_struct;
#ifdef __USE_KOS_ALTERATIONS
struct ucontext;
typedef void (__ATTR_SYSVABI *__sigactionx64_sa_sigaction_t)(int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx);
#else /* __USE_KOS_ALTERATIONS */
typedef void (__ATTR_SYSVABI *__sigactionx64_sa_sigaction_t)(int __signo, struct __siginfo_struct *__info, void *__ctx);
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __x86_64__ */
struct __siginfox64_struct;
typedef __HYBRID_FUNCPTR64(void, , __sigactionx64_sa_handler_t, (int __signo));
typedef __HYBRID_FUNCPTR64(void, , __sigactionx64_sa_restorer_t, (void));
#ifdef __USE_KOS_ALTERATIONS
struct __ucontextx64;
typedef __HYBRID_FUNCPTR64(void, , __sigactionx64_sa_sigaction_t, (int __signo, struct __siginfox64_struct *__info, struct __ucontextx64 *__ctx));
#else /* __USE_KOS_ALTERATIONS */
typedef __HYBRID_FUNCPTR64(void, , __sigactionx64_sa_sigaction_t, (int __signo, struct __siginfox64_struct *__info, void *__ctx));
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__x86_64__ */



/* Structure describing the action to be taken when a signal arrives. */
struct __ATTR_ALIGNED(__ALIGNOF_SIGACTIONX64) __sigactionx64 /*[NAME(sigactionx64)][PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		__sigactionx64_sa_handler_t   sa_handler;   /* [valid_if(!(sa_flags & SA_SIGINFO))] */
		__sigactionx64_sa_sigaction_t sa_sigaction; /* [valid_if(sa_flags & SA_SIGINFO)] */
	};
#else /* __USE_POSIX199309 */
	__sigactionx64_sa_handler_t  sa_handler;  /* Signal handler */
#endif /* !__USE_POSIX199309 */
	__uint64_t                   sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
	__sigactionx64_sa_restorer_t sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
	struct __sigset_struct       sa_mask;     /* Additional set of signals to be blocked. */
};



/* Because of `__ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION', the kernel's `struct sigaction' matches libc's! */
#define __kernel_sigactionx64 __sigactionx64
#define __ARCH_HAVE_KERNEL_SIGACTIONX64_IS_LIBC_SIGACTIONX64

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_KOS_SIGACTION64_H */
