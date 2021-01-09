/* HASH CRC-32:0x1d382ce0 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ssignal_defined
#define __local_ssignal_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_bsd_signal
#include <bits/types.h>
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: bsd_signal from signal */
#ifndef __local___localdep_bsd_signal_defined
#define __local___localdep_bsd_signal_defined 1
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
/* >> ssignal(3)
 * Establish a software-signal-handler. This handler may or may not
 * be distinct from normal signal handlers, and should be triggered
 * by `gsignal(3)', rather than `raise(3)'.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
__LOCAL_LIBC(ssignal) __sighandler_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ssignal))(__signo_t __signo, __sighandler_t __handler) {
	return __localdep_bsd_signal(__signo, __handler);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ssignal_defined
#define __local___localdep_ssignal_defined 1
#define __localdep_ssignal __LIBC_LOCAL_NAME(ssignal)
#endif /* !__local___localdep_ssignal_defined */
#else /* __CRT_HAVE_bsd_signal */
#undef __local_ssignal_defined
#endif /* !__CRT_HAVE_bsd_signal */
#endif /* !__local_ssignal_defined */
