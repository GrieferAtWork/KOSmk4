/* HASH CRC-32:0x37c08716 */
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
/* (#) Portability: libc4/5 (/include/bsd/signal.h) */
/*!always_includes <signal.h>*/
#ifndef _BSD_SIGNAL_H
#define _BSD_SIGNAL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <signal.h>
#include <features.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sig_t_defined
#define __sig_t_defined
typedef __sighandler_t sig_t;
#endif /* !__sig_t_defined */

#ifdef __CRT_HAVE_bsd_signal
/* >> bsd_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> sigemptyset(&act.sa_mask);
 *     >> sigaddset(&act.sa_mask, signo);
 *     >> act.sa_flags = sigismember(&[SIGNALS_WITH_SIGINTERRUPT], signo) ? 0 : SA_RESTART;
 *     >> SET_SIGRESTORE(act);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 *     Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for  which
 *     `siginterrupt(3)' had last been called with a non-zero `interrupt'
 *     argument
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__bsd_signal,(__signo_t __signo, __sighandler_t __handler),bsd_signal,(__signo,__handler))
#elif defined(__CRT_HAVE___bsd_signal)
/* >> bsd_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> sigemptyset(&act.sa_mask);
 *     >> sigaddset(&act.sa_mask, signo);
 *     >> act.sa_flags = sigismember(&[SIGNALS_WITH_SIGINTERRUPT], signo) ? 0 : SA_RESTART;
 *     >> SET_SIGRESTORE(act);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 *     Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for  which
 *     `siginterrupt(3)' had last been called with a non-zero `interrupt'
 *     argument
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,__bsd_signal,(__signo_t __signo, __sighandler_t __handler),(__signo,__handler))
#endif /* ... */
#if defined(__CRT_HAVE_bsd_signal) || defined(__CRT_HAVE___bsd_signal)
#undef signal
#define signal __bsd_signal
#endif /* __CRT_HAVE_bsd_signal || __CRT_HAVE___bsd_signal */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_SIGNAL_H */
