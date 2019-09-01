/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_SIGACTION_STRUCT64_H
#define _I386_KOS_BITS_SIGACTION_STRUCT64_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>
#include <bits/sigset.h>
#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#if defined(__x86_64__) && !defined(__CRT_CYG_PRIMARY)
#define __OFFSET_SIGACTION_HANDLER   __OFFSET_SIGACTION64_HANDLER
#define __OFFSET_SIGACTION_SIGACTION __OFFSET_SIGACTION64_SIGACTION
#define __OFFSET_SIGACTION_MASK      __OFFSET_SIGACTION64_MASK
#define __OFFSET_SIGACTION_FLAGS     __OFFSET_SIGACTION64_FLAGS
#define __OFFSET_SIGACTION_RESTORER  __OFFSET_SIGACTION64_RESTORER
#define __SIZEOF_SIGACTION           __SIZEOF_SIGACTION64
#define __ALIGNOF_SIGACTION          __ALIGNOF_SIGACTION64
#define sigaction64       sigaction
#define __sighandler64_t  __sighandler_t
#endif /* __x86_64__ && !__CRT_CYG_PRIMARY */


__SYSDECL_BEGIN


#ifdef __CC__
#ifdef __x86_64__
typedef __HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, __sighandler64_t, (int __signo));
#else /* __x86_64__ */
typedef __HYBRID_FUNCPTR64(void, , __sighandler64_t, (int __signo));
#endif /* !__x86_64__ */

#ifdef __USE_POSIX199309
#ifdef __x86_64__
struct __siginfo_struct;
#else /* __x86_64__ */
struct __siginfo64_struct;
#endif /* !__x86_64__ */
#ifdef __USE_KOS
#ifdef __x86_64__
struct ucontext;
#else /* __x86_64__ */
struct ucontext64;
#endif /* !__x86_64__ */
#endif /* __USE_KOS */
#endif /* __USE_POSIX199309 */
#endif /* __CC__ */


#define __OFFSET_SIGACTION64_HANDLER   0
#define __OFFSET_SIGACTION64_SIGACTION 0
#define __OFFSET_SIGACTION64_MASK      8
#define __OFFSET_SIGACTION64_FLAGS     136
#define __OFFSET_SIGACTION64_RESTORER  144
#define __SIZEOF_SIGACTION64           152
#define __ALIGNOF_SIGACTION64          8
#ifdef __CC__
/* Structure describing the action to be taken when a signal arrives. */
struct __ATTR_ALIGNED(__ALIGNOF_SIGACTION64) sigaction64 /*[PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		/* Used if SA_SIGINFO is not set. */
		__sighandler64_t sa_handler;
		/* Used if SA_SIGINFO is set. */
#ifdef __USE_KOS
#ifdef __x86_64__
		__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, sa_sigaction, (int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx));
#else /* __x86_64__ */
		__HYBRID_FUNCPTR64(void, , sa_sigaction, (int __signo, struct __siginfo64_struct *__info, struct ucontext64 *__ctx));
#endif /* !__x86_64__ */
#else /* __USE_KOS */
#ifdef __x86_64__
		__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, sa_sigaction, (int __signo, struct __siginfo_struct *__info, void *__ctx));
#else /* __x86_64__ */
		__HYBRID_FUNCPTR64(void, , sa_sigaction, (int __signo, struct __siginfo64_struct *__info, void *__ctx));
#endif /* !__x86_64__ */
#endif /* !__USE_KOS */
	};
#else /* __USE_POSIX199309 */
	__sighandler64_t sa_handler;
#endif /* !__USE_POSIX199309 */
	__sigset_t sa_mask;  /* Additional set of signals to be blocked. */
	__uint32_t sa_flags; /* Special flags. */
	__uint32_t __sa_pad; /* ... */
#ifdef __x86_64__
	__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, sa_restorer, (void)); /* Restore handler. */
#else /* __x86_64__ */
	__HYBRID_FUNCPTR64(void, , sa_restorer, (void)); /* Restore handler. */
#endif /* !__x86_64__ */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_SIGACTION_STRUCT32_H */
