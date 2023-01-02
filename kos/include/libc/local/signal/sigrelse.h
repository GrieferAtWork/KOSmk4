/* HASH CRC-32:0x19b3c255 */
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
#ifndef __local_sigrelse_defined
#define __local_sigrelse_defined
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SIG_UNBLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_set_single_signal_masked_defined
#define __local___localdep_set_single_signal_masked_defined
__NAMESPACE_LOCAL_END
#include <libc/local/signal/set_single_signal_masked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_set_single_signal_masked __LIBC_LOCAL_NAME(set_single_signal_masked)
#endif /* !__local___localdep_set_single_signal_masked_defined */
__LOCAL_LIBC(sigrelse) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigrelse))(__signo_t __signo) {
	return (__NAMESPACE_LOCAL_SYM __localdep_set_single_signal_masked)(__signo, __SIG_UNBLOCK);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigrelse_defined
#define __local___localdep_sigrelse_defined
#define __localdep_sigrelse __LIBC_LOCAL_NAME(sigrelse)
#endif /* !__local___localdep_sigrelse_defined */
#else /* __SIG_UNBLOCK && (__CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask) */
#undef __local_sigrelse_defined
#endif /* !__SIG_UNBLOCK || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE___sigprocmask && !__CRT_HAVE___libc_sigprocmask && !__CRT_HAVE_pthread_sigmask && !__CRT_HAVE_thr_sigsetmask) */
#endif /* !__local_sigrelse_defined */
