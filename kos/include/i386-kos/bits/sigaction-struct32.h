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
#ifndef _I386_KOS_BITS_SIGACTION_STRUCT32_H
#define _I386_KOS_BITS_SIGACTION_STRUCT32_H 1

/* File:
 *    <i386-kos/bits/sigaction-struct32.h>
 * 
 * Definitions:
 *    - struct __sigactionx32 { ... };
 *    - typedef ... __sighandlerx32_t;
 * #if !defined(__CRT_CYG_PRIMARY) && !defined(__x86_64__) && defined(__i386__)
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 * #endif
 */

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/sigset.h>
#include <bits/types.h>

#if !defined(__CRT_CYG_PRIMARY) && !defined(__x86_64__) && defined(__i386__)
#define __OFFSET_SIGACTION_HANDLER   __OFFSET_SIGACTIONX32_HANDLER
#define __OFFSET_SIGACTION_SIGACTION __OFFSET_SIGACTIONX32_SIGACTION
#define __OFFSET_SIGACTION_MASK      __OFFSET_SIGACTIONX32_MASK
#define __OFFSET_SIGACTION_FLAGS     __OFFSET_SIGACTIONX32_FLAGS
#define __OFFSET_SIGACTION_RESTORER  __OFFSET_SIGACTIONX32_RESTORER
#define __SIZEOF_SIGACTION           __SIZEOF_SIGACTIONX32
#define __ALIGNOF_SIGACTION          __ALIGNOF_SIGACTIONX32
#define __sigactionx32 sigaction
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined 1
#define __sighandlerx32_t  __sighandler_t
#endif /* !____sighandler_t_defined */
#endif /* !__CRT_CYG_PRIMARY && !__x86_64__ && __i386__ */


__SYSDECL_BEGIN


#ifdef __CC__
typedef __HYBRID_FUNCPTR32(void,__ATTR_CDECL,__sighandlerx32_t,(int __signo));

#ifdef __USE_POSIX199309
#if !defined(__CRT_CYG_PRIMARY) && !defined(__x86_64__) && defined(__i386__)
struct __siginfo_struct;
#else /* !__CRT_CYG_PRIMARY && !__x86_64__ && __i386__ */
struct __siginfox32_struct;
#endif /* __CRT_CYG_PRIMARY || __x86_64__ || !__i386__ */
#ifdef __USE_KOS
#ifdef __x86_64__
struct ucontext32;
#else /* __x86_64__ */
struct ucontext;
#endif /* !__x86_64__ */
#endif /* __USE_KOS */
#endif /* __USE_POSIX199309 */
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
		/* Used if SA_SIGINFO is not set. */
		__sighandlerx32_t sa_handler;
		/* Used if SA_SIGINFO is set. */
#ifdef __USE_KOS
#if !defined(__CRT_CYG_PRIMARY) && !defined(__x86_64__) && defined(__i386__)
		__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_sigaction, (int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx));
#else /* !__CRT_CYG_PRIMARY && !__x86_64__ && __i386__ */
		__HYBRID_FUNCPTR32(void, , sa_sigaction, (int __signo, struct __siginfox32_struct *__info, struct ucontext32 *__ctx));
#endif /* __CRT_CYG_PRIMARY || __x86_64__ || !__i386__ */
#else /* __USE_KOS */
#if !defined(__CRT_CYG_PRIMARY) && !defined(__x86_64__) && defined(__i386__)
		__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_sigaction, (int __signo, struct __siginfo_struct *__info, void *__ctx));
#else /* !__CRT_CYG_PRIMARY && !__x86_64__ && __i386__ */
		__HYBRID_FUNCPTR32(void, , sa_sigaction, (int __signo, struct __siginfox32_struct *__info, void *__ctx));
#endif /* __CRT_CYG_PRIMARY || __x86_64__ || !__i386__ */
#endif /* !__USE_KOS */
	};
#else /* __USE_POSIX199309 */
	__sighandlerx32_t sa_handler;
#endif /* !__USE_POSIX199309 */
	struct __sigset_structx32 sa_mask;  /* Additional set of signals to be blocked. */
	__uint32_t                sa_flags; /* Special flags. */
#ifdef __x86_64__
	__HYBRID_FUNCPTR32(void, , sa_restorer, (void)); /* Restore handler. */
#else /* __x86_64__ */
	__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sa_restorer, (void)); /* Restore handler. */
#endif /* !__x86_64__ */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_SIGACTION_STRUCT32_H */
