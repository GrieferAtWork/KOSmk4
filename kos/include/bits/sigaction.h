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
#ifndef _BITS_SIGACTION_H
#define _BITS_SIGACTION_H 1

#include <__stdinc.h>

#include <bits/sigaction-struct.h>
#include <bits/siginfo.h>
#include <bits/sigset.h>

/* Bits in `sa_flags'. */
#ifndef SA_NOCLDSTOP
#define SA_NOCLDSTOP  1 /* Don't send SIGCHLD when children stop. */
#endif /* !SA_NOCLDSTOP */
#ifndef SA_NOCLDWAIT
#define SA_NOCLDWAIT  2 /* Don't create zombie on child death. */
#endif /* !SA_NOCLDWAIT */
#ifndef SA_SIGINFO
#define SA_SIGINFO    4 /* Invoke signal-catching function with three arguments instead of one. */
#endif /* !SA_SIGINFO */
#ifdef __USE_KOS_KERNEL
#ifndef SA_RESTORER
#define SA_RESTORER   0x04000000 /* A custom signal restore function (`sa_restorer') was given.
                                  * This flag is set by libc, after having filled in the `sa_restorer' field.
                                  * NOTE: On x86, the kernel assumes that this points to a function:
                                  * >> sa_restorer:
                                  * >>     movl   $SYS_sigreturn, %eax
                                  * >>     int    $0x80
                                  */
#endif /* !SA_RESTORER */
#endif /* __USE_KOS_KERNEL */
#if defined(__USE_UNIX98) || defined(__USE_MISC)
#ifndef SA_ONSTACK
#ifdef __CRT_CYG_PRIMARY
#define SA_ONSTACK    0x20000000 /* Execute the handler on sigaltstack. */
#else /* __CRT_CYG_PRIMARY */
#define SA_ONSTACK    0x08000000 /* Execute the handler on sigaltstack. */
#endif /* !__CRT_CYG_PRIMARY */
#endif /* !SA_ONSTACK */
#endif /* __USE_UNIX98 || __USE_MISC */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef SA_RESTART
#define SA_RESTART    0x10000000 /* Restart restartable syscall on signal return. */
#endif /* !SA_RESTART */
#ifndef SA_NODEFER
#define SA_NODEFER    0x40000000 /* Don't automatically block the signal when its handler is being executed. */
#endif /* !SA_NODEFER */
#ifndef SA_RESETHAND
#define SA_RESETHAND  0x80000000 /* Reset to SIG_DFL on entry to handler. */
#endif /* !SA_RESETHAND */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */
#ifdef __USE_MISC
#ifndef SA_INTERRUPT
#define SA_INTERRUPT  0x20000000 /* Historical no-op. */
#endif /* !SA_INTERRUPT */
/* Some aliases for the SA_ constants. */
#ifndef SA_NOMASK
#define SA_NOMASK     SA_NODEFER
#endif /* !SA_NOMASK */
#ifndef SA_ONESHOT
#define SA_ONESHOT    SA_RESETHAND
#endif /* !SA_ONESHOT */
#ifndef SA_STACK
#define SA_STACK      SA_ONSTACK
#endif /* !SA_STACK */
#endif /* __USE_MISC */

/* Values for the HOW argument to `sigprocmask'. */
#ifndef SIG_BLOCK
#define SIG_BLOCK     0 /* Block signals. */
#endif /* !SIG_BLOCK */
#ifndef SIG_UNBLOCK
#define SIG_UNBLOCK   1 /* Unblock signals. */
#endif /* !SIG_UNBLOCK */
#ifndef SIG_SETMASK
#define SIG_SETMASK   2 /* Set the set of blocked signals. */
#endif /* !SIG_SETMASK */

#endif /* !_BITS_SIGACTION_H */
