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
#ifndef _BITS_SIGACTION_STRUCT_H
#define _BITS_SIGACTION_STRUCT_H 1

/* File:
 *    <bits/sigaction-struct.h>
 * 
 * Definitions:
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 */

#include <__stdinc.h>
#include <features.h>

#include <bits/os/sigset.h> /* struct __sigset_struct */
#include <bits/types.h>

#define __OFFSET_SIGACTION_HANDLER   0
#define __OFFSET_SIGACTION_SIGACTION 0
#define __OFFSET_SIGACTION_MASK      __SIZEOF_POINTER__
#define __OFFSET_SIGACTION_FLAGS     (__SIZEOF_POINTER__ + __SIZEOF_SIGSET_T__)
#define __OFFSET_SIGACTION_RESTORER  ((__SIZEOF_POINTER__ * 2) + __SIZEOF_SIGSET_T__)
#define __SIZEOF_SIGACTION           ((__SIZEOF_POINTER__ * 3) + __SIZEOF_SIGSET_T__)
#define __ALIGNOF_SIGACTION          __SIZEOF_POINTER__

#ifdef __CC__
__DECL_BEGIN

#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined 1
typedef void (__LIBKCALL *__sighandler_t)(int __signo);
#endif /* !____sighandler_t_defined */

#ifdef __USE_POSIX199309
#ifdef __USE_KOS_ALTERATIONS
struct ucontext;
#endif /* __USE_KOS_ALTERATIONS */
#endif /* __USE_POSIX199309 */

/* Structure describing the action to be taken when a signal arrives. */
struct __siginfo_struct;
struct sigaction /*[PREFIX(sa_)]*/ {
	/* Signal handler. */
#ifdef __USE_POSIX199309
	union {
		__sighandler_t sa_handler; /* Used if SA_SIGINFO is not set. */
#ifdef __USE_KOS_ALTERATIONS
		void (__LIBKCALL *sa_sigaction)(int __signo, struct __siginfo_struct *__info, struct ucontext *__ctx); /* Used if SA_SIGINFO is set. */
#else /* __USE_KOS_ALTERATIONS */
		void (__LIBKCALL *sa_sigaction)(int __signo, struct __siginfo_struct *__info, void *__ctx); /* Used if SA_SIGINFO is set. */
#endif /* !__USE_KOS_ALTERATIONS */
	};
#else /* __USE_POSIX199309 */
	__sighandler_t sa_handler;
#endif /* !__USE_POSIX199309 */
	struct __sigset_struct sa_mask;  /* Additional set of signals to be blocked. */
	int                    sa_flags; /* Special flags. */
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	__byte_t             __sa_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__]; /* ... */
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
	void      (__LIBKCALL *sa_restorer)(void); /* Restore handler. */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_SIGACTION_STRUCT_H */
