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
#ifndef _I386_KOS_BITS_OS_KOS_SIGACTION32_H
#define _I386_KOS_BITS_OS_KOS_SIGACTION32_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigaction32.h>
 *
 * Definitions:
 *    - struct __sigactionx32 { ... };
 *    - typedef ... __sigactionx32_sa_handler_t;
 * #if !defined(__x86_64__) && defined(__i386__)
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/sigset.h>
#include <bits/types.h>

#if !defined(__x86_64__) && defined(__i386__)
/* Portable system feature spec macros */
#define __ARCH_HAVE_SIGACTION_SA_RESTORER
#define __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
#undef __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION

/* Portable names */
#define __OFFSET_SIGACTION_HANDLER         __OFFSET_SIGACTIONX32_HANDLER
#define __OFFSET_SIGACTION_SIGACTION       __OFFSET_SIGACTIONX32_SIGACTION
#define __OFFSET_SIGACTION_MASK            __OFFSET_SIGACTIONX32_MASK
#define __OFFSET_SIGACTION_FLAGS           __OFFSET_SIGACTIONX32_FLAGS
#define __OFFSET_SIGACTION_RESTORER        __OFFSET_SIGACTIONX32_RESTORER
#define __SIZEOF_SIGACTION                 __SIZEOF_SIGACTIONX32
#define __ALIGNOF_SIGACTION                __ALIGNOF_SIGACTIONX32
#define __OFFSET_KERNEL_SIGACTION_HANDLER  __OFFSET_KERNEL_SIGACTIONX32_HANDLER
#define __OFFSET_KERNEL_SIGACTION_FLAGS    __OFFSET_KERNEL_SIGACTIONX32_FLAGS
#define __OFFSET_KERNEL_SIGACTION_MASK     __OFFSET_KERNEL_SIGACTIONX32_MASK
#define __OFFSET_KERNEL_SIGACTION_RESTORER __OFFSET_KERNEL_SIGACTIONX32_RESTORER
#define __ALIGNOF_KERNEL_SIGACTION         __ALIGNOF_KERNEL_SIGACTIONX32
#define __sigaction_sa_handler_t           __sigactionx32_sa_handler_t
#define __sigaction_sa_restorer_t          __sigactionx32_sa_restorer_t
#define __sigaction_sa_sigaction_t         __sigactionx32_sa_sigaction_t
#define __sigactionx32                     sigaction
#if defined(__KERNEL__) || defined(__USE_KOS_KERNEL)
#define __kernel_sigaction    kernel_sigaction
#define __kernel_sigactionx32 kernel_sigaction
#else /* __KERNEL__ || __USE_KOS_KERNEL */
#define __kernel_sigactionx32 __kernel_sigaction
#endif /* !__KERNEL__ && !__USE_KOS_KERNEL */
#ifdef __USE_KOS_KERNEL
#define __OFFSET_OLD_KERNEL_SIGACTION_HANDLER   __OFFSET_OLD_KERNEL_SIGACTIONX32_HANDLER
#define __OFFSET_OLD_KERNEL_SIGACTION_MASK      __OFFSET_OLD_KERNEL_SIGACTIONX32_MASK
#define __OFFSET_OLD_KERNEL_SIGACTION_FLAGS     __OFFSET_OLD_KERNEL_SIGACTIONX32_FLAGS
#define __OFFSET_OLD_KERNEL_SIGACTION_RESTORER  __OFFSET_OLD_KERNEL_SIGACTIONX32_RESTORER
#define __SIZEOF_OLD_KERNEL_SIGACTION           __SIZEOF_OLD_KERNEL_SIGACTIONX32
#define __ALIGNOF_OLD_KERNEL_SIGACTION          __ALIGNOF_OLD_KERNEL_SIGACTIONX32
#define __old_kernel_sigactionx32               __old_kernel_sigaction
#endif /* __USE_KOS_KERNEL */
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
#define __sigactionx32_sa_handler_t __sighandler_t
#endif /* !____sighandler_t_defined */
#endif /* !__x86_64__ && __i386__ */

#define __OFFSET_SIGACTIONX32_HANDLER   0
#define __OFFSET_SIGACTIONX32_SIGACTION 0
#define __OFFSET_SIGACTIONX32_MASK      4
#define __OFFSET_SIGACTIONX32_FLAGS     (__SIZEOF_SIGSET_T__ + 4)
#define __OFFSET_SIGACTIONX32_RESTORER  (__SIZEOF_SIGSET_T__ + 8)
#define __SIZEOF_SIGACTIONX32           (__SIZEOF_SIGSET_T__ + 12)
#define __ALIGNOF_SIGACTIONX32          4

#define __OFFSET_KERNEL_SIGACTIONX32_HANDLER   0
#define __OFFSET_KERNEL_SIGACTIONX32_FLAGS     4
#define __OFFSET_KERNEL_SIGACTIONX32_RESTORER  8
#define __OFFSET_KERNEL_SIGACTIONX32_MASK      12
#define __ALIGNOF_KERNEL_SIGACTIONX32          4
/* No sizeof, because actual size is flexible. */

#ifdef __USE_KOS_KERNEL
#define __OFFSET_OLD_KERNEL_SIGACTIONX32_HANDLER   0
#define __OFFSET_OLD_KERNEL_SIGACTIONX32_MASK      4
#define __OFFSET_OLD_KERNEL_SIGACTIONX32_FLAGS     8
#define __OFFSET_OLD_KERNEL_SIGACTIONX32_RESTORER  12
#define __SIZEOF_OLD_KERNEL_SIGACTIONX32           16
#define __ALIGNOF_OLD_KERNEL_SIGACTIONX32          4
#endif /* __USE_KOS_KERNEL */


#ifdef __CC__
__DECL_BEGIN

#if defined(__i386__) && !defined(__x86_64__)
typedef void (__ATTR_CDECL *__sigactionx32_sa_handler_t)(int __signo);
typedef void (__ATTR_CDECL *__sigactionx32_sa_restorer_t)(void);
struct __siginfo_struct;
#ifdef __USE_KOS_ALTERATIONS
struct ucontext;
typedef void (__ATTR_CDECL *__sigactionx32_sa_sigaction_t)(int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx);
#else /* __USE_KOS_ALTERATIONS */
typedef void (__ATTR_CDECL *__sigactionx32_sa_sigaction_t)(int __signo, struct __siginfo_struct *__info, void *__ctx);
#endif /* !__USE_KOS_ALTERATIONS */
#else /* __i386__ && !__x86_64__ */
struct __siginfox32_struct;
typedef __HYBRID_FUNCPTR32(void, , __sigactionx32_sa_handler_t, (int __signo));
typedef __HYBRID_FUNCPTR32(void, , __sigactionx32_sa_restorer_t, (void));
#ifdef __USE_KOS_ALTERATIONS
struct __ucontextx32;
typedef __HYBRID_FUNCPTR32(void, , __sigactionx32_sa_sigaction_t, (int __signo, struct __siginfox32_struct *__info, struct __ucontextx32 *__ctx));
#else /* __USE_KOS_ALTERATIONS */
typedef __HYBRID_FUNCPTR32(void, , __sigactionx32_sa_sigaction_t, (int __signo, struct __siginfox32_struct *__info, void *__ctx));
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__i386__ || __x86_64__ */

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

/* Structure describing the action to be taken when a signal arrives.
 * WARNING: on i386, the kernel system call `sys_rt_sigaction()' uses  a
 *          binary incompatible structure `struct __kernel_sigactionx32'
 *          instead of this one! */
struct __ATTR_ALIGNED(__ALIGNOF_SIGACTIONX32) __sigactionx32 /*[NAME(sigactionx32)][PREFIX(sa_)]*/ {
#ifdef __USE_POSIX199309
	union {
		__sigactionx32_sa_handler_t   sa_handler;   /* [valid_if(!(sa_flags & SA_SIGINFO))] */
		__sigactionx32_sa_sigaction_t sa_sigaction; /* [valid_if(sa_flags & SA_SIGINFO)] */
	};
#else /* __USE_POSIX199309 */
	__sigactionx32_sa_handler_t  sa_handler;  /* Signal handler */
#endif /* !__USE_POSIX199309 */
	struct __sigset_structx32    sa_mask;     /* Additional set of signals to be blocked. */
	__ULONG32_TYPE__             sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
	__sigactionx32_sa_restorer_t sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
};



/* Because of `#undef __ARCH_HAVE_KERNEL_SIGACTION_IS_LIBC_SIGACTION', we also define the kernel's `struct sigaction' */
struct __ATTR_ALIGNED(__ALIGNOF_KERNEL_SIGACTIONX32) __kernel_sigactionx32 /*[NAME(kernel_sigactionx32)][PREFIX(sa_)]*/ {
	__sigactionx32_sa_handler_t  sa_handler;  /* Signal handler */
	__ULONG32_TYPE__             sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
	__sigactionx32_sa_restorer_t sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
	struct __sigset_structx32    sa_mask;     /* Additional set of signals to be blocked. */
};



/* This is the struct accepted by `sys_sigaction()' */
#ifdef __USE_KOS_KERNEL
struct __old_kernel_sigactionx32 /*[NAME(old_kernel_sigactionx32)][PREFIX(sa_)]*/ {
	__sigactionx32_sa_handler_t  sa_handler;  /* Signal handler. */
	struct __old_sigset_struct   sa_mask;     /* Additional set of signals to be blocked. */
	__ULONG32_TYPE__             sa_flags;    /* Special flags (set of `SA_*' from <signal.h>) */
	__sigactionx32_sa_restorer_t sa_restorer; /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
};
#endif /* __USE_KOS_KERNEL */


__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_KOS_SIGACTION32_H */
