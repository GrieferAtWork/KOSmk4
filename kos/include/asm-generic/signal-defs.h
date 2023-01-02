/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/asm-generic/signal-defs.h) */
#ifndef _ASM_GENERIC_SIGNAL_DEFS_H
#define _ASM_GENERIC_SIGNAL_DEFS_H 1

#include <__stdinc.h>

#include <asm/os/signal.h>

/* Bits in `sa_flags'. */
#if !defined(SA_NOCLDSTOP) && defined(__SA_NOCLDSTOP)
#define SA_NOCLDSTOP __SA_NOCLDSTOP /* Don't send SIGCHLD when children stop (Ignored for anything other than SIGCLD). */
#endif /* !SA_NOCLDSTOP && __SA_NOCLDSTOP */
#if !defined(SA_NOCLDWAIT) && defined(__SA_NOCLDWAIT)
#define SA_NOCLDWAIT __SA_NOCLDWAIT /* Don't create zombie on child death (Ignored for anything other than SIGCLD). */
#endif /* !SA_NOCLDWAIT && __SA_NOCLDWAIT */
#if !defined(SA_SIGINFO) && defined(__SA_SIGINFO)
#define SA_SIGINFO __SA_SIGINFO /* Invoke signal-catching function with three arguments instead of one. */
#endif /* !SA_SIGINFO && __SA_SIGINFO */
#if !defined(SA_ONSTACK) && defined(__SA_ONSTACK)
#define SA_ONSTACK __SA_ONSTACK /* Execute the handler on sigaltstack. */
#endif /* !SA_ONSTACK && __SA_ONSTACK */
#if !defined(SA_RESTART) && defined(__SA_RESTART)
#define SA_RESTART __SA_RESTART /* Restart restartable syscall on signal return. */
#endif /* !SA_RESTART && __SA_RESTART */
#if !defined(SA_NODEFER) && defined(__SA_NODEFER)
#define SA_NODEFER __SA_NODEFER /* Don't automatically block the signal when its handler is being executed. */
#endif /* !SA_NODEFER && __SA_NODEFER */
#if !defined(SA_RESETHAND) && defined(__SA_RESETHAND)
#define SA_RESETHAND __SA_RESETHAND /* Reset to SIG_DFL on entry to handler. */
#endif /* !SA_RESETHAND && __SA_RESETHAND */
#if !defined(SA_NOMASK) && defined(__SA_NODEFER)
#define SA_NOMASK __SA_NODEFER
#endif /* !SA_NOMASK && __SA_NODEFER */
#if !defined(SA_ONESHOT) && defined(__SA_RESETHAND)
#define SA_ONESHOT __SA_RESETHAND
#endif /* !SA_ONESHOT && __SA_RESETHAND */
#if !defined(SA_UNSUPPORTED) && defined(__SA_UNSUPPORTED)
#define SA_UNSUPPORTED __SA_UNSUPPORTED /* ??? */
#endif /* !SA_UNSUPPORTED && __SA_UNSUPPORTED */
#if !defined(SA_EXPOSE_TAGBITS) && defined(__SA_EXPOSE_TAGBITS)
#define SA_EXPOSE_TAGBITS __SA_EXPOSE_TAGBITS /* ??? */
#endif /* !SA_EXPOSE_TAGBITS && __SA_EXPOSE_TAGBITS */

/* Values for the HOW argument to `sigprocmask'. */
#if !defined(SIG_BLOCK) && defined(__SIG_BLOCK)
#define SIG_BLOCK __SIG_BLOCK /* Block signals. */
#endif /* !SIG_BLOCK && __SIG_BLOCK */
#if !defined(SIG_UNBLOCK) && defined(__SIG_UNBLOCK)
#define SIG_UNBLOCK __SIG_UNBLOCK /* Unblock signals. */
#endif /* !SIG_UNBLOCK && __SIG_UNBLOCK */
#if !defined(SIG_SETMASK) && defined(__SIG_SETMASK)
#define SIG_SETMASK __SIG_SETMASK /* Set the set of blocked signals. */
#endif /* !SIG_SETMASK && __SIG_SETMASK */

#ifdef __CC__
#include <__crt.h>
__DECL_BEGIN

#ifndef ____signalfn_t_defined
#define ____signalfn_t_defined
typedef void (__LIBKCALL __signalfn_t)(int __signo);
#endif /* !____signalfn_t_defined */

#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined
typedef void (__LIBKCALL *__sighandler_t)(int __signo);
#endif /* !____sighandler_t_defined */

#ifndef ____restorefn_t_defined
#define ____restorefn_t_defined
typedef void (__LIBKCALL __restorefn_t)(void);
#endif /* !____restorefn_t_defined */

#ifndef ____sigrestore_t_defined
#define ____sigrestore_t_defined
typedef void (__LIBKCALL *__sigrestore_t)(void);
#endif /* !____sigrestore_t_defined */

__DECL_END
#endif /* __CC__ */

/* Fake signal functions. */
#if !defined(SIG_ERR) && defined(__SIG_ERR)
#define SIG_ERR (__CCAST(__sighandler_t)__SIG_ERR) /* Error return. */
#endif /* !SIG_ERR && __SIG_ERR */
#if !defined(SIG_DFL) && defined(__SIG_DFL)
#define SIG_DFL (__CCAST(__sighandler_t)__SIG_DFL) /* Default action. */
#endif /* !SIG_DFL && __SIG_DFL */
#if !defined(SIG_IGN) && defined(__SIG_IGN)
#define SIG_IGN (__CCAST(__sighandler_t)__SIG_IGN) /* Ignore signal. */
#endif /* !SIG_IGN && __SIG_IGN */


#endif /* !_ASM_GENERIC_SIGNAL_DEFS_H */
