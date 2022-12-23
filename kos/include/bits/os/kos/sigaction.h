/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_SIGACTION_H
#define _BITS_OS_KOS_SIGACTION_H 1

/* File:
 *    <bits/os/kos/sigaction.h>
 *
 * Definitions:
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 */

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#include <bits/os/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>

/* Portable system feature spec macros */
#undef __ARCH_HAVE_SIGACTION_SA_RESTORER
#undef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
#if (defined(__arm__) || defined(__h8300__) || defined(__m68k__) ||     \
     defined(__powerpc__) || defined(__s390__) || defined(__sparc__) || \
     defined(__i386__) || defined(__x86_64__) || defined(__xtensa__))
#define __ARCH_HAVE_SIGACTION_SA_RESTORER
#define __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
#endif /* ... */
#undef __ARCH_HAVE_IRIX_KERNEL_SIGACTION
#ifdef __mips__
#define __ARCH_HAVE_IRIX_KERNEL_SIGACTION
#endif /* ... */
#undef __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION
#if !defined(__i386__) /* XXX: May be incomplete! */
#define __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION
#endif /* ... */

/* Offsets for `struct __kernel_sigaction' (no SIZEOF, because variable-sized due to sigmask) */
#ifdef __ARCH_HAVE_IRIX_KERNEL_SIGACTION
#define __OFFSET_KERNEL_SIGACTION_FLAGS   0
#define __OFFSET_KERNEL_SIGACTION_HANDLER __SIZEOF_POINTER__
#else /* __ARCH_HAVE_IRIX_KERNEL_SIGACTION */
#define __OFFSET_KERNEL_SIGACTION_HANDLER 0
#define __OFFSET_KERNEL_SIGACTION_FLAGS   __SIZEOF_POINTER__
#endif /* !__ARCH_HAVE_IRIX_KERNEL_SIGACTION */
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
#define __OFFSET_KERNEL_SIGACTION_RESTORER (__SIZEOF_POINTER__ * 2)
#define __OFFSET_KERNEL_SIGACTION_MASK     (__SIZEOF_POINTER__ * 3)
#else /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
#define __OFFSET_KERNEL_SIGACTION_MASK (__SIZEOF_POINTER__ * 2)
#endif /* !__ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
#define __ALIGNOF_KERNEL_SIGACTION __SIZEOF_POINTER__


/* `struct sigaction': Structure describing the action to be taken when a signal arrives. */
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION
#define __OFFSET_SIGACTION_HANDLER  __OFFSET_KERNEL_SIGACTION_HANDLER
#define __OFFSET_SIGACTION_FLAGS    __OFFSET_KERNEL_SIGACTION_FLAGS
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
#define __OFFSET_SIGACTION_RESTORER __OFFSET_KERNEL_SIGACTION_RESTORER
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
#define __OFFSET_SIGACTION_MASK     __OFFSET_KERNEL_SIGACTION_MASK
#define __SIZEOF_SIGACTION          (__OFFSET_SIGACTION_MASK + __SIZEOF_SIGSET_T__)
#define __ALIGNOF_SIGACTION         __ALIGNOF_KERNEL_SIGACTION
#elif defined(__i386__)
#define __OFFSET_SIGACTION_HANDLER  0
#define __OFFSET_SIGACTION_MASK     4
#define __OFFSET_SIGACTION_FLAGS    132
#define __OFFSET_SIGACTION_RESTORER 136
#define __SIZEOF_SIGACTION          140
#else /* __i386__ */
#define __OFFSET_SIGACTION_HANDLER  0
#define __OFFSET_SIGACTION_FLAGS    __SIZEOF_POINTER__
#define __OFFSET_SIGACTION_RESTORER (__SIZEOF_POINTER__ * 2)
#define __OFFSET_SIGACTION_MASK     (__SIZEOF_POINTER__ * 3)
#define __SIZEOF_SIGACTION          ((__SIZEOF_POINTER__ * 3) + __SIZEOF_SIGSET_T__)
#endif /* !__i386__ */
#define __OFFSET_SIGACTION_SIGACTION __OFFSET_SIGACTION_HANDLER
#ifndef __ALIGNOF_SIGACTION
#define __ALIGNOF_SIGACTION __SIZEOF_POINTER__
#endif /* !__ALIGNOF_SIGACTION */


#ifdef __CC__
__DECL_BEGIN

typedef void (__LIBKCALL *__sigaction_sa_handler_t)(int __signo);
struct __siginfo_struct;
#ifdef __USE_KOS_ALTERATIONS
struct ucontext;
typedef void (__LIBKCALL *__sigaction_sa_sigaction_t)(int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx);
#else /* __USE_KOS_ALTERATIONS */
typedef void (__LIBKCALL *__sigaction_sa_sigaction_t)(int __signo, struct __siginfo_struct *__info, void *__ctx);
#endif /* !__USE_KOS_ALTERATIONS */
#if defined(__ARCH_HAVE_SIGACTION_SA_RESTORER) || defined(__ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER)
typedef void (__LIBKCALL *__sigaction_sa_restorer_t)(void);
#endif /* __ARCH_HAVE_SIGACTION_SA_RESTORER || __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */

#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
typedef __sigaction_sa_handler_t __sighandler_t;
#endif /* !____sighandler_t_defined */

/* This is the struct accepted by `sigaction(3)' (iow: the one from libc; assuming Glibc compat) */
struct sigaction /*[PREFIX(sa_)]*/ {
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION
#ifdef __ARCH_HAVE_IRIX_KERNEL_SIGACTION
	__ULONGPTR_TYPE__         sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
#endif /* __ARCH_HAVE_IRIX_KERNEL_SIGACTION */
#ifdef __USE_POSIX199309
	union {
		__sigaction_sa_handler_t   sa_handler;   /* [valid_if(!(sa_flags & SA_SIGINFO))] */
		__sigaction_sa_sigaction_t sa_sigaction; /* [valid_if(sa_flags & SA_SIGINFO)] */
	};
#else /* __USE_POSIX199309 */
	__sighandler_t            sa_handler;  /* Signal handler. */
#endif /* !__USE_POSIX199309 */
#ifndef __ARCH_HAVE_IRIX_KERNEL_SIGACTION
	__ULONGPTR_TYPE__         sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
#endif /* __ARCH_HAVE_IRIX_KERNEL_SIGACTION */
#ifdef __ARCH_HAVE_SIGACTION_SA_RESTORER
	__sigaction_sa_restorer_t sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
#endif /* __ARCH_HAVE_SIGACTION_SA_RESTORER */
	struct __sigset_struct    sa_mask;     /* Additional set of signals to be blocked. */
#elif defined(__i386__)
#ifdef __USE_POSIX199309
	union {
		__sigaction_sa_handler_t   sa_handler;   /* [valid_if(!(sa_flags & SA_SIGINFO))] */
		__sigaction_sa_sigaction_t sa_sigaction; /* [valid_if(sa_flags & SA_SIGINFO)] */
	};
#else /* __USE_POSIX199309 */
	__sigaction_sa_handler_t  sa_handler;  /* Signal handler */
#endif /* !__USE_POSIX199309 */
	struct __sigset_struct    sa_mask;     /* Additional set of signals to be blocked. */
	__ULONG32_TYPE__          sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
	__sigaction_sa_restorer_t sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
#else /* ... */
#error "Unsupported architecture"
#endif /* !... */
};



/* This is the struct accepted by `sys_rt_sigaction(2)' */
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION
#define __kernel_sigaction sigaction
#if defined(__KERNEL__) || defined(__USE_KOS_KERNEL)
#define kernel_sigaction sigaction
#endif /* __KERNEL__ || __USE_KOS_KERNEL */
#else /* __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION */
#if defined(__KERNEL__) || defined(__USE_KOS_KERNEL)
#define __kernel_sigaction kernel_sigaction
#endif /* __KERNEL__ || __USE_KOS_KERNEL */
struct __kernel_sigaction /*[NAME(kernel_sigaction)][PREFIX(sa_)]*/ {
#ifdef __ARCH_HAVE_IRIX_KERNEL_SIGACTION
	__ULONGPTR_TYPE__         sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
	__sighandler_t            sa_handler;  /* Signal handler. */
#else /* __ARCH_HAVE_IRIX_KERNEL_SIGACTION */
	__sighandler_t            sa_handler;  /* Signal handler. */
	__ULONGPTR_TYPE__         sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
#endif /* !__ARCH_HAVE_IRIX_KERNEL_SIGACTION */
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
	__sigaction_sa_restorer_t sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
	struct __sigset_struct    sa_mask;     /* Additional set of signals to be blocked. */
};
#endif /* !__ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION */



/* This is the struct accepted by `sys_sigaction(2)' */
#ifdef __USE_KOS_KERNEL
struct __old_kernel_sigaction /*[NAME(old_kernel_sigaction)][PREFIX(sa_)]*/ {
	__sighandler_t             sa_handler;  /* Signal handler. */
	struct __old_sigset_struct sa_mask;     /* Additional set of signals to be blocked. */
	__ULONGPTR_TYPE__          sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
	__sigaction_sa_restorer_t  sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
};
#endif /* __USE_KOS_KERNEL */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_SIGACTION_H */
