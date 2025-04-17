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
/*!replace_with_include <bits/os/sigaction.h>*/
#ifndef _BITS_OS_CYGWIN_SIGACTION_H
#define _BITS_OS_CYGWIN_SIGACTION_H 1

/* File:
 *    <bits/os/cygwin/sigaction.h>
 *
 * Definitions:
 *    - struct __sigaction_cygwin { ... };
 *    - typedef ... __sighandler_cygwin_t;
 * #ifdef __CRT_CYG_PRIMARY
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 * #endif
 */

#include <__crt.h> /* __CRT_CYG_PRIMARY */
#include <__stdinc.h>
#include <features.h>

#include <bits/os/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>

#ifdef __CRT_CYG_PRIMARY
#define __OFFSET_SIGACTION_HANDLER   __OFFSET_SIGACTION_CYGWIN_HANDLER
#define __OFFSET_SIGACTION_SIGACTION __OFFSET_SIGACTION_CYGWIN_SIGACTION
#define __OFFSET_SIGACTION_MASK      __OFFSET_SIGACTION_CYGWIN_MASK
#define __OFFSET_SIGACTION_FLAGS     __OFFSET_SIGACTION_CYGWIN_FLAGS
#define __SIZEOF_SIGACTION           __SIZEOF_SIGACTION_CYGWIN
#define __ALIGNOF_SIGACTION          __ALIGNOF_SIGACTION_CYGWIN
#define __sigaction_cygwin           sigaction
#define __kernel_sigaction           sigaction
#if defined(__KERNEL__) || defined(__USE_KOS_KERNEL)
#define kernel_sigaction sigaction
#endif /* __KERNEL__ || __USE_KOS_KERNEL */
#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
#define __sighandler_cygwin_t __sighandler_t
#endif /* !____sighandler_t_defined */
#endif /* __CRT_CYG_PRIMARY */

__SYSDECL_BEGIN

#define __OFFSET_SIGACTION_CYGWIN_HANDLER   0
#define __OFFSET_SIGACTION_CYGWIN_SIGACTION 0
#define __OFFSET_SIGACTION_CYGWIN_MASK      __SIZEOF_POINTER__
#define __OFFSET_SIGACTION_CYGWIN_FLAGS     (__SIZEOF_POINTER__ + __SIZEOF_SIGSET_T__)
#if __SIZEOF_POINTER__ > 4
#define __SIZEOF_SIGACTION_CYGWIN           (__SIZEOF_POINTER__ + (__SIZEOF_SIGSET_T__ + 4 + __SIZEOF_POINTER__ - 1) & ~(__SIZEOF_POINTER__ - 1))
#else /* __SIZEOF_POINTER__ > 4 */
#define __SIZEOF_SIGACTION_CYGWIN           (__SIZEOF_POINTER__ + __SIZEOF_SIGSET_T__ + 4)
#endif /* !__SIZEOF_POINTER__ <= 4 */
#define __ALIGNOF_SIGACTION_CYGWIN          __SIZEOF_POINTER__

#ifdef __CC__
typedef void (*__sighandler_cygwin_t)(int __signo);

/* Structure describing the action to be taken when a signal arrives. */
struct __sigaction_cygwin /*[NAME(sigaction_cygwin)][PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		/* Used if SA_SIGINFO is not set. */
		__sighandler_cygwin_t sa_handler;
		/* Used if SA_SIGINFO is set. */
		void (*sa_sigaction)(int __signo, struct __siginfo_cygwin_struct *__info, void *__ctx);
	};
#else /* __USE_POSIX199309 */
	__sighandler_cygwin_t sa_handler;
#endif /* !__USE_POSIX199309 */
	/* XXX: Doesn't sigset_t have a different size in cygwin? */
	struct __sigset_struct sa_mask;  /* Additional set of signals to be blocked. */
	__uint32_t             sa_flags; /* Special flags (set of `SA_*' from <signal.h>) */
};

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_OS_CYGWIN_SIGACTION_H */
