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
#ifndef _ASM_SIGNAL_H
#define _ASM_SIGNAL_H 1

#include <__stdinc.h>
#include <__crt.h>

#if defined(__KOS__) || defined(__linux__)
/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* Bits in `sa_flags'. */
#define __SA_NOCLDSTOP 0x00000001 /* Don't send SIGCHLD when children stop. */
#define __SA_NOCLDWAIT 0x00000002 /* Don't create zombie on child death. */
#define __SA_SIGINFO   0x00000004 /* Invoke signal-catching function with three arguments instead of one. */
#define __SA_RESTORER  0x04000000 /* A custom signal restore function (`sa_restorer') was given.
                                   * This flag is set by libc, after having filled in the `sa_restorer' field.
                                   * NOTE: On x86, the kernel assumes that this points to a function:
                                   * >> sa_restorer:
                                   * >>     movl   $SYS_sigreturn, %eax
                                   * >>     int    $0x80 */
#define __SA_ONSTACK   0x08000000 /* Execute the handler on sigaltstack. */
#define __SA_RESTART   0x10000000 /* Restart restartable syscall on signal return. */
#define __SA_NODEFER   0x40000000 /* Don't automatically block the signal when its handler is being executed. */
#define __SA_RESETHAND 0x80000000 /* Reset to SIG_DFL on entry to handler. */
#define __SA_INTERRUPT 0x20000000 /* Historical no-op. */

/* Values for the HOW argument to `sigprocmask'. */
#define __SIG_BLOCK   0 /* Block signals. */
#define __SIG_UNBLOCK 1 /* Unblock signals. */
#define __SIG_SETMASK 2 /* Set the set of blocked signals. */

#elif defined(__CRT_CYG_PRIMARY)
/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

/* Bits in `sa_flags'. */
#define __SA_NOCLDSTOP 0x00000001 /* Don't send SIGCHLD when children stop. */
#define __SA_NOCLDWAIT 0x00000002 /* Don't create zombie on child death. */
#define __SA_SIGINFO   0x00000004 /* Invoke signal-catching function with three arguments instead of one. */
#define __SA_RESTORER  0x04000000 /* A custom signal restore function (`sa_restorer') was given.
                                   * This flag is set by libc, after having filled in the `sa_restorer' field.
                                   * NOTE: On x86, the kernel assumes that this points to a function:
                                   * >> sa_restorer:
                                   * >>     movl   $SYS_sigreturn, %eax
                                   * >>     int    $0x80 */
#define __SA_ONSTACK   0x20000000 /* Execute the handler on sigaltstack. */
#define __SA_RESTART   0x10000000 /* Restart restartable syscall on signal return. */
#define __SA_NODEFER   0x40000000 /* Don't automatically block the signal when its handler is being executed. */
#define __SA_RESETHAND 0x80000000 /* Reset to SIG_DFL on entry to handler. */
#define __SA_INTERRUPT 0x20000000 /* Historical no-op. */

/* Values for the HOW argument to `sigprocmask'. */
#define __SIG_BLOCK   0 /* Block signals. */
#define __SIG_UNBLOCK 1 /* Unblock signals. */
#define __SIG_SETMASK 2 /* Set the set of blocked signals. */

#elif defined(__NetBSD__)
/************************************************************************/
/* NetBSD                                                               */
/************************************************************************/

#define __SA_ONSTACK    0x0001
#define __SA_RESTART    0x0002
#define __SA_RESETHAND  0x0004
#define __SA_NODEFER    0x0010
#define __SA_NOCLDSTOP  0x0008
#define __SA_NOCLDWAIT  0x0020
#define __SA_SIGINFO    0x0040
#define __SA_NOKERNINFO 0x0080

#define __SIG_BLOCK   1
#define __SIG_UNBLOCK 2
#define __SIG_SETMASK 3

#elif defined(__solaris__)
/************************************************************************/
/* SOLARIS                                                              */
/************************************************************************/

/* TODO */

#else /* ... */
/************************************************************************/
/* GENERIC                                                              */
/************************************************************************/


#endif /* !... */

#endif /* !_ASM_SIGNAL_H */
