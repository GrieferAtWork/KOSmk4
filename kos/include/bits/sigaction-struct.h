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
#ifndef _BITS_SIGACTION_STRUCT_H
#define _BITS_SIGACTION_STRUCT_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/sigset.h>

__SYSDECL_BEGIN

#define __OFFSET_SIGACTION_HANDLER   0
#define __OFFSET_SIGACTION_SIGACTION 0
#define __OFFSET_SIGACTION_MASK      __SIZEOF_POINTER__
#define __OFFSET_SIGACTION_FLAGS    (__SIZEOF_POINTER__ + __SIZEOF_SIGSET_T__)
#define __OFFSET_SIGACTION_RESTORER ((__SIZEOF_POINTER__ * 2) + __SIZEOF_SIGSET_T__)
#define __SIZEOF_SIGACTION          ((__SIZEOF_POINTER__ * 3) + __SIZEOF_SIGSET_T__)
#define __ALIGNOF_SIGACTION         __SIZEOF_POINTER__

#ifdef __CC__
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined 1
typedef void (__LIBCCALL *__sighandler_t)(int __signo);
#endif /* !____sighandler_t_defined */

#ifdef __USE_POSIX199309
#ifdef __USE_KOS
struct ucontext;
#endif /* __USE_KOS */
#endif /* __USE_POSIX199309 */

/* Structure describing the action to be taken when a signal arrives. */
struct __siginfo_struct;
struct sigaction /*[PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		__sighandler_t sa_handler; /* Used if SA_SIGINFO is not set. */
#ifdef __USE_KOS
		void (__LIBCCALL *sa_sigaction)(int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx); /* Used if SA_SIGINFO is set. */
#else /* __USE_KOS */
		void (__LIBCCALL *sa_sigaction)(int __signo, struct __siginfo_struct *__info, void *__ctx); /* Used if SA_SIGINFO is set. */
#endif /* !__USE_KOS */
	};
#else /* __USE_POSIX199309 */
	__sighandler_t sa_handler;
#endif /* !__USE_POSIX199309 */
	__sigset_t sa_mask;  /* Additional set of signals to be blocked. */
	int        sa_flags; /* Special flags. */
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	__byte_t __sa_bad[__SIZEOF_POINTER__ - __SIZEOF_INT__]; /* ... */
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	void (*sa_restorer)(void); /* Restore handler. */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_SIGACTION_STRUCT_H */
