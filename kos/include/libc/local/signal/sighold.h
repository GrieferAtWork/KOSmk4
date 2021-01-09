/* HASH CRC-32:0xb0a5ffd1 */
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
#ifndef __local_sighold_defined
#define __local_sighold_defined 1
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SIG_BLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: set_single_signal_action from signal */
#ifndef __local___localdep_set_single_signal_action_defined
#define __local___localdep_set_single_signal_action_defined 1
__NAMESPACE_LOCAL_END
#include <libc/local/signal/set_single_signal_action.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_set_single_signal_action __LIBC_LOCAL_NAME(set_single_signal_action)
#endif /* !__local___localdep_set_single_signal_action_defined */
/* >> sighold(3)
 * Mask a single signal `signo', which is the same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__LOCAL_LIBC(sighold) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sighold))(__signo_t __signo) {
	return __localdep_set_single_signal_action(__signo, __SIG_BLOCK);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sighold_defined
#define __local___localdep_sighold_defined 1
#define __localdep_sighold __LIBC_LOCAL_NAME(sighold)
#endif /* !__local___localdep_sighold_defined */
#else /* __SIG_BLOCK && (__CRT_HAVE_sigprocmask || __CRT_HAVE_pthread_sigmask) */
#undef __local_sighold_defined
#endif /* !__SIG_BLOCK || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE_pthread_sigmask) */
#endif /* !__local_sighold_defined */
