/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
 *    - typedef ... __sighandlerx64_t;
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
#define __OFFSET_SIGACTION_HANDLER   __OFFSET_SIGACTIONX64_HANDLER
#define __OFFSET_SIGACTION_SIGACTION __OFFSET_SIGACTIONX64_SIGACTION
#define __OFFSET_SIGACTION_MASK      __OFFSET_SIGACTIONX64_MASK
#define __OFFSET_SIGACTION_FLAGS     __OFFSET_SIGACTIONX64_FLAGS
#define __OFFSET_SIGACTION_RESTORER  __OFFSET_SIGACTIONX64_RESTORER
#define __SIZEOF_SIGACTION           __SIZEOF_SIGACTIONX64
#define __ALIGNOF_SIGACTION          __ALIGNOF_SIGACTIONX64
#define __sigactionx64 sigaction
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined 1
#define __sighandlerx64_t __sighandler_t
#endif /* !____sighandler_t_defined */
#endif /* __x86_64__ */


__SYSDECL_BEGIN


#ifdef __CC__
typedef __HYBRID_FUNCPTR64(void,__ATTR_SYSVABI,__sighandlerx64_t,(int __signo));

#ifdef __USE_POSIX199309
#ifdef __x86_64__
struct __siginfo_struct;
#else /* __x86_64__ */
struct __siginfo64_struct;
#endif /* !__x86_64__ */
#ifdef __USE_KOS_ALTERATIONS
#ifdef __x86_64__
struct ucontext;
#else /* __x86_64__ */
struct ucontext64;
#endif /* !__x86_64__ */
#endif /* __USE_KOS_ALTERATIONS */
#endif /* __USE_POSIX199309 */
#endif /* __CC__ */


#define __OFFSET_SIGACTIONX64_HANDLER   0
#define __OFFSET_SIGACTIONX64_SIGACTION 0
#define __OFFSET_SIGACTIONX64_MASK      8
#define __OFFSET_SIGACTIONX64_FLAGS     136
#define __OFFSET_SIGACTIONX64_RESTORER  144
#define __SIZEOF_SIGACTIONX64           152
#define __ALIGNOF_SIGACTIONX64          8
#ifdef __CC__
/* Structure describing the action to be taken when a signal arrives. */
struct __ATTR_ALIGNED(__ALIGNOF_SIGACTIONX64) __sigactionx64 /*[NAME(sigactionx64)][PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		/* Used if SA_SIGINFO is not set. */
		__sighandlerx64_t sa_handler;
		/* Used if SA_SIGINFO is set. */
#ifdef __USE_KOS_ALTERATIONS
#ifdef __x86_64__
		__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, sa_sigaction, (int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx));
#else /* __x86_64__ */
		__HYBRID_FUNCPTR64(void, , sa_sigaction, (int __signo, struct __siginfo64_struct *__info, struct ucontext64 *__ctx));
#endif /* !__x86_64__ */
#else /* __USE_KOS_ALTERATIONS */
#ifdef __x86_64__
		__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, sa_sigaction, (int __signo, struct __siginfo_struct *__info, void *__ctx));
#else /* __x86_64__ */
		__HYBRID_FUNCPTR64(void, , sa_sigaction, (int __signo, struct __siginfo64_struct *__info, void *__ctx));
#endif /* !__x86_64__ */
#endif /* !__USE_KOS_ALTERATIONS */
	};
#else /* __USE_POSIX199309 */
	__sighandlerx64_t sa_handler;
#endif /* !__USE_POSIX199309 */
	struct __sigset_struct sa_mask;  /* Additional set of signals to be blocked. */
	__uint32_t             sa_flags; /* Special flags (set of `SA_*' from <signal.h>) */
	__uint32_t           __sa_pad;   /* ... */
#ifdef __x86_64__
	__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, sa_restorer, (void)); /* Restore handler. */
#else /* __x86_64__ */
	__HYBRID_FUNCPTR64(void, , sa_restorer, (void)); /* Restore handler. */
#endif /* !__x86_64__ */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_OS_KOS_SIGACTION64_H */
