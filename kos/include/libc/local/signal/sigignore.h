/* HASH CRC-32:0x43f5df55 */
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
#ifndef __local_sigignore_defined
#define __local_sigignore_defined 1
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SIG_IGN) && defined(__SIG_ERR) && defined(__CRT_HAVE_bsd_signal)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: bsd_signal from signal */
#ifndef __local___localdep_bsd_signal_defined
#define __local___localdep_bsd_signal_defined 1
__NAMESPACE_LOCAL_END
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
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
 *     Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for which
 *     `siginterrupt(3)' had last been called with a non-zero `interrupt'
 *     argument
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__localdep_bsd_signal,(__signo_t __signo, __sighandler_t __handler),bsd_signal,(__signo,__handler))
#endif /* !__local___localdep_bsd_signal_defined */
/* >> sigignore(3)
 * Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__LOCAL_LIBC(sigignore) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigignore))(__signo_t __signo) {
	return __localdep_bsd_signal(__signo, (__sighandler_t)__SIG_IGN) == (__sighandler_t)__SIG_ERR ? -1 : 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigignore_defined
#define __local___localdep_sigignore_defined 1
#define __localdep_sigignore __LIBC_LOCAL_NAME(sigignore)
#endif /* !__local___localdep_sigignore_defined */
#else /* __SIG_IGN && __SIG_ERR && __CRT_HAVE_bsd_signal */
#undef __local_sigignore_defined
#endif /* !__SIG_IGN || !__SIG_ERR || !__CRT_HAVE_bsd_signal */
#endif /* !__local_sigignore_defined */
