/* HASH CRC-32:0x8b22882a */
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
#ifndef __local_sigignore_defined
#define __local_sigignore_defined
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SIG_IGN) && defined(__SIG_ERR) && (defined(__CRT_HAVE_bsd_signal) || defined(__CRT_HAVE___bsd_signal))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bsd_signal_defined
#define __local___localdep_bsd_signal_defined
#ifdef __CRT_HAVE_bsd_signal
__NAMESPACE_LOCAL_END
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__localdep_bsd_signal,(__signo_t __signo, __sighandler_t __handler),bsd_signal,(__signo,__handler))
#elif defined(__CRT_HAVE___bsd_signal)
__NAMESPACE_LOCAL_END
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__localdep_bsd_signal,(__signo_t __signo, __sighandler_t __handler),__bsd_signal,(__signo,__handler))
#else /* ... */
#undef __local___localdep_bsd_signal_defined
#endif /* !... */
#endif /* !__local___localdep_bsd_signal_defined */
__LOCAL_LIBC(sigignore) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigignore))(__signo_t __signo) {
	return (__NAMESPACE_LOCAL_SYM __localdep_bsd_signal)(__signo, (__sighandler_t)__SIG_IGN) == (__sighandler_t)__SIG_ERR ? -1 : 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigignore_defined
#define __local___localdep_sigignore_defined
#define __localdep_sigignore __LIBC_LOCAL_NAME(sigignore)
#endif /* !__local___localdep_sigignore_defined */
#else /* __SIG_IGN && __SIG_ERR && (__CRT_HAVE_bsd_signal || __CRT_HAVE___bsd_signal) */
#undef __local_sigignore_defined
#endif /* !__SIG_IGN || !__SIG_ERR || (!__CRT_HAVE_bsd_signal && !__CRT_HAVE___bsd_signal) */
#endif /* !__local_sigignore_defined */
