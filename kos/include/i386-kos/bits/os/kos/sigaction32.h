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
#ifndef _I386_KOS_BITS_OS_KOS_SIGACTION32_H
#define _I386_KOS_BITS_OS_KOS_SIGACTION32_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigaction32.h>
 *
 * Definitions:
 *    - struct __sigactionx32 { ... };
 *    - typedef ... __sighandlerx32_t;
 * #if !defined(__x86_64__) && defined(__i386__)
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/os/sigset.h>
#include <bits/types.h>

#if !defined(__x86_64__) && defined(__i386__)
#define __OFFSET_SIGACTION_HANDLER   __OFFSET_SIGACTIONX32_HANDLER
#define __OFFSET_SIGACTION_SIGACTION __OFFSET_SIGACTIONX32_SIGACTION
#define __OFFSET_SIGACTION_MASK      __OFFSET_SIGACTIONX32_MASK
#define __OFFSET_SIGACTION_FLAGS     __OFFSET_SIGACTIONX32_FLAGS
#define __OFFSET_SIGACTION_RESTORER  __OFFSET_SIGACTIONX32_RESTORER
#define __SIZEOF_SIGACTION           __SIZEOF_SIGACTIONX32
#define __ALIGNOF_SIGACTION          __ALIGNOF_SIGACTIONX32
#define __sigactionx32 sigaction
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
#define __sighandlerx32_t __sighandler_t
#endif /* !____sighandler_t_defined */
#endif /* !__x86_64__ && __i386__ */

#ifdef __CC__
__DECL_BEGIN

typedef __HYBRID_FUNCPTR32(void,__ATTR_CDECL,__sighandlerx32_t,(int __signo));

#ifdef __USE_POSIX199309
#if !defined(__x86_64__) && defined(__i386__)
struct __siginfo_struct;
#else /* !__x86_64__ && __i386__ */
struct __siginfox32_struct;
#endif /* __x86_64__ || !__i386__ */
#ifdef __USE_KOS_ALTERATIONS
#if ((defined(__linux__) || (defined(__KOS__) && __KOS_VERSION__ < 300)) && \
     (!defined(__x86_64__) && defined(__i386__)))
struct ucontext;
#else /* ... */
struct __ucontextx32;
#endif /* !... */
#endif /* __USE_KOS_ALTERATIONS */
#endif /* __USE_POSIX199309 */
#ifndef ____sigsetx32_t_defined
#define ____sigsetx32_t_defined
#ifdef __x86_64__
struct __sigset_structx32 {
	__UINT32_TYPE__ __val[__SIZEOF_SIGSET_T__ / 4];
};
#else /* __x86_64__ */
#define __sigset_structx32 __sigset_struct
#endif /* !__x86_64__ */
#endif /* !____sigsetx32_t_defined */
#endif /* __CC__ */


#define __OFFSET_SIGACTIONX32_HANDLER   0
#define __OFFSET_SIGACTIONX32_SIGACTION 0
#define __OFFSET_SIGACTIONX32_MASK      4
#define __OFFSET_SIGACTIONX32_FLAGS     132
#define __OFFSET_SIGACTIONX32_RESTORER  136
#define __SIZEOF_SIGACTIONX32           140
#define __ALIGNOF_SIGACTIONX32          4
#ifdef __CC__
/* Structure describing the action to be taken when a signal arrives. */
struct __ATTR_ALIGNED(__ALIGNOF_SIGACTIONX32) __sigactionx32 /*[NAME(sigactionx32)][PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		/* [valid_if(!(sa_flags & SA_SIGINFO))] */
		__sighandlerx32_t sa_handler;

		/* [valid_if(sa_flags & SA_SIGINFO)] */
#ifdef __USE_KOS_ALTERATIONS
#if ((defined(__linux__) || (defined(__KOS__) && __KOS_VERSION__ < 300)) && \
     (!defined(__x86_64__) && defined(__i386__)))
#if !defined(__x86_64__) && defined(__i386__)
		__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_sigaction, (int __signo, struct __siginfox32_struct *__info, struct __ucontextx32 *__ctx));
#else /* !__x86_64__ && __i386__ */
		__HYBRID_FUNCPTR32(void, , sa_sigaction, (int __signo, struct __siginfox32_struct *__info, struct __ucontextx32 *__ctx));
#endif /* __x86_64__ || !__i386__ */
#else /* ... */
#if !defined(__x86_64__) && defined(__i386__)
		__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_sigaction, (int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx));
#else /* !__x86_64__ && __i386__ */
		__HYBRID_FUNCPTR32(void, , sa_sigaction, (int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx));
#endif /* __x86_64__ || !__i386__ */
#endif /* !... */
#else /* __USE_KOS_ALTERATIONS */
#if !defined(__x86_64__) && defined(__i386__)
		__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_sigaction, (int __signo, struct __siginfo_struct *__info, void *__ctx));
#else /* !__x86_64__ && __i386__ */
		__HYBRID_FUNCPTR32(void, , sa_sigaction, (int __signo, struct __siginfox32_struct *__info, void *__ctx));
#endif /* __x86_64__ || !__i386__ */
#endif /* !__USE_KOS_ALTERATIONS */
	};
#else /* __USE_POSIX199309 */
	__sighandlerx32_t sa_handler;
#endif /* !__USE_POSIX199309 */
	struct __sigset_structx32 sa_mask;  /* Additional set of signals to be blocked. */
	__uint32_t                sa_flags; /* Special flags (set of `SA_*' from <signal.h>) */
#ifdef __x86_64__
	__HYBRID_FUNCPTR32(void, , sa_restorer, (void)); /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
#else /* __x86_64__ */
	__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_restorer, (void)); /* [valid_if(sa_flags & SA_RESTORER)] Restore handler. */
#endif /* !__x86_64__ */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_KOS_SIGACTION32_H */
