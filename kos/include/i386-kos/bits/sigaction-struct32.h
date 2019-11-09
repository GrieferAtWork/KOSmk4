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
#ifndef _I386_KOS_BITS_SIGACTION_STRUCT32_H
#define _I386_KOS_BITS_SIGACTION_STRUCT32_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/sigset.h>
#include <bits/types.h>

#if !defined(__x86_64__) && !defined(__CRT_CYG_PRIMARY)
#define __OFFSET_SIGACTION_HANDLER   __OFFSET_SIGACTION32_HANDLER
#define __OFFSET_SIGACTION_SIGACTION __OFFSET_SIGACTION32_SIGACTION
#define __OFFSET_SIGACTION_MASK      __OFFSET_SIGACTION32_MASK
#define __OFFSET_SIGACTION_FLAGS     __OFFSET_SIGACTION32_FLAGS
#define __OFFSET_SIGACTION_RESTORER  __OFFSET_SIGACTION32_RESTORER
#define __SIZEOF_SIGACTION           __SIZEOF_SIGACTION32
#define __ALIGNOF_SIGACTION          __ALIGNOF_SIGACTION32
#define sigaction32       sigaction
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined 1
#define __sighandler32_t  __sighandler_t
#endif /* !____sighandler_t_defined */
#endif /* !__x86_64__ && !__CRT_CYG_PRIMARY */


__SYSDECL_BEGIN


#ifdef __CC__
typedef __HYBRID_FUNCPTR32(void,__ATTR_CDECL,__sighandler32_t,(int __signo));

#ifdef __USE_POSIX199309
#ifdef __x86_64__
struct __siginfo32_struct;
#else /* __x86_64__ */
struct __siginfo_struct;
#endif /* !__x86_64__ */
#ifdef __USE_KOS
#ifdef __x86_64__
struct ucontext32;
#else /* __x86_64__ */
struct ucontext;
#endif /* !__x86_64__ */
#endif /* __USE_KOS */
#endif /* __USE_POSIX199309 */
#ifndef ____sigset32_t_defined
#define ____sigset32_t_defined 1
#ifdef __x86_64__
typedef struct __sigset_struct32 {
	__UINT32_TYPE__ __val[__SIZEOF_SIGSET_T__ / 4];
} __sigset32_t;
#else /* __x86_64__ */
#define __sigset_struct32 __sigset_struct
#define __sigset32_t      __sigset_t
#endif /* !__x86_64__ */
#endif /* !____sigset32_t_defined */
#endif /* __CC__ */


#define __OFFSET_SIGACTION32_HANDLER   0
#define __OFFSET_SIGACTION32_SIGACTION 0
#define __OFFSET_SIGACTION32_MASK      4
#define __OFFSET_SIGACTION32_FLAGS     132
#define __OFFSET_SIGACTION32_RESTORER  136
#define __SIZEOF_SIGACTION32           140
#define __ALIGNOF_SIGACTION32          4
#ifdef __CC__
/* Structure describing the action to be taken when a signal arrives. */
struct __ATTR_ALIGNED(__ALIGNOF_SIGACTION32) sigaction32 /*[PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		/* Used if SA_SIGINFO is not set. */
		__sighandler32_t sa_handler;
		/* Used if SA_SIGINFO is set. */
#ifdef __USE_KOS
#ifdef __x86_64__
		__HYBRID_FUNCPTR32(void, , sa_sigaction, (int __signo, struct __siginfo32_struct *__info, struct ucontext32 *__ctx));
#else /* __x86_64__ */
		__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_sigaction, (int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx));
#endif /* !__x86_64__ */
#else /* __USE_KOS */
#ifdef __x86_64__
		__HYBRID_FUNCPTR32(void, , sa_sigaction, (int __signo, struct __siginfo32_struct *__info, void *__ctx));
#else /* __x86_64__ */
		__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_sigaction, (int __signo, struct __siginfo_struct *__info, void *__ctx));
#endif /* !__x86_64__ */
#endif /* !__USE_KOS */
	};
#else /* __USE_POSIX199309 */
	__sighandler32_t sa_handler;
#endif /* !__USE_POSIX199309 */
	__sigset32_t sa_mask;  /* Additional set of signals to be blocked. */
	__uint32_t   sa_flags; /* Special flags. */
#ifdef __x86_64__
	__HYBRID_FUNCPTR32(void, , sa_restorer, (void)); /* Restore handler. */
#else /* __x86_64__ */
	__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_restorer, (void)); /* Restore handler. */
#endif /* !__x86_64__ */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_SIGACTION_STRUCT32_H */
