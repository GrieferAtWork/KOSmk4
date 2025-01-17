/* HASH CRC-32:0x1566a650 */
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
#ifndef __local_sysv_signal_defined
#define __local_sysv_signal_defined
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SA_RESETHAND) && defined(__SA_NODEFER) && defined(__SIG_ERR) && (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction))
#include <bits/types.h>
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#else /* ... */
#undef __local___localdep_sigaction_defined
#endif /* !... */
#endif /* !__local___localdep_sigaction_defined */
#ifndef __local___localdep_sigemptyset_defined
#define __local___localdep_sigemptyset_defined
#ifdef __CRT_HAVE_sigemptyset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigemptyset __LIBC_LOCAL_NAME(sigemptyset)
#endif /* !__CRT_HAVE_sigemptyset */
#endif /* !__local___localdep_sigemptyset_defined */
__LOCAL_LIBC(sysv_signal) __sighandler_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sysv_signal))(__signo_t __signo, __sighandler_t __handler) {
	struct sigaction __act, __oact
	__act.sa_handler = __handler;
	__act.sa_flags   = __SA_RESETHAND | __SA_NODEFER;
	(__NAMESPACE_LOCAL_SYM __localdep_sigemptyset)(&__act.sa_mask);
	if ((__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__signo, &__act, &__oact) != 0)
	    __oact.sa_handler = __SIG_ERR;
	return __oact.sa_handler;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sysv_signal_defined
#define __local___localdep_sysv_signal_defined
#define __localdep_sysv_signal __LIBC_LOCAL_NAME(sysv_signal)
#endif /* !__local___localdep_sysv_signal_defined */
#else /* __SA_RESETHAND && __SA_NODEFER && __SIG_ERR && (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) */
#undef __local_sysv_signal_defined
#endif /* !__SA_RESETHAND || !__SA_NODEFER || !__SIG_ERR || (!__CRT_HAVE_sigaction && !__CRT_HAVE___sigaction) */
#endif /* !__local_sysv_signal_defined */
