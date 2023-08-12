/* HASH CRC-32:0x5718acea */
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
#ifndef __local_tmpfile_s_defined
#define __local_tmpfile_s_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#include <features.h>
#include <asm/os/fcntl.h>
#include <asm/os/mman.h>
#include <asm/os/signal.h>
#if (defined(__CRT_HAVE_tmpfile) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_tmpfile64) || ((defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)) && ((defined(__CRT_HAVE_memfd_create) && defined(__MFD_CLOEXEC)) || ((defined(__CRT_HAVE_mkstemp) || defined(__CRT_HAVE_mkstemp64) || defined(__CRT_HAVE_mkstemps) || defined(__CRT_HAVE_mkstemps64) || defined(__CRT_HAVE_mkostemps) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && defined(__SIG_SETMASK) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)))) || ((defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)) && ((defined(__CRT_HAVE_mkstemp) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemp64) || (defined(__CRT_HAVE_mkstemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemps64) || (defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && defined(__SIG_SETMASK))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tmpfile64_defined
#define __local___localdep_tmpfile64_defined
#if defined(__CRT_HAVE_tmpfile) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,__localdep_tmpfile64,(void),tmpfile,())
#elif defined(__CRT_HAVE_tmpfile64)
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,__localdep_tmpfile64,(void),tmpfile64,())
#elif (defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)) && ((defined(__CRT_HAVE_memfd_create) && defined(__MFD_CLOEXEC)) || ((defined(__CRT_HAVE_mkstemp) || defined(__CRT_HAVE_mkstemp64) || defined(__CRT_HAVE_mkstemps) || defined(__CRT_HAVE_mkstemps64) || defined(__CRT_HAVE_mkostemps) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && defined(__SIG_SETMASK) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/tmpfile.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tmpfile64 __NAMESPACE_LOCAL_TYPEHAX(__FILE *(__LIBCCALL*)(),__FILE *(__LIBCCALL&)(),tmpfile)
#elif (defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)) && ((defined(__CRT_HAVE_mkstemp) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemp64) || (defined(__CRT_HAVE_mkstemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemps64) || (defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && defined(__SIG_SETMASK)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/tmpfile64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tmpfile64 __LIBC_LOCAL_NAME(tmpfile64)
#else /* ... */
#undef __local___localdep_tmpfile64_defined
#endif /* !... */
#endif /* !__local___localdep_tmpfile64_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tmpfile_s) __ATTR_OUT(1) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(tmpfile_s))(__FILE **__pstream) {
	if (!__pstream) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	*__pstream = (__NAMESPACE_LOCAL_SYM __localdep_tmpfile64)();
	if (!*__pstream) {
#ifdef __ENOMEM
		return __libc_geterrno_or(__ENOMEM);
#else /* __ENOMEM */
		return __libc_geterrno_or(1);
#endif /* !__ENOMEM */
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tmpfile_s_defined
#define __local___localdep_tmpfile_s_defined
#define __localdep_tmpfile_s __LIBC_LOCAL_NAME(tmpfile_s)
#endif /* !__local___localdep_tmpfile_s_defined */
#else /* (__CRT_HAVE_tmpfile && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_tmpfile64 || ((__CRT_HAVE_fdopen || __CRT_HAVE__fdopen || __CRT_HAVE__IO_fdopen) && ((__CRT_HAVE_memfd_create && __MFD_CLOEXEC) || ((__CRT_HAVE_mkstemp || __CRT_HAVE_mkstemp64 || __CRT_HAVE_mkstemps || __CRT_HAVE_mkstemps64 || __CRT_HAVE_mkostemps || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask) && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && __SIG_SETMASK && (!__O_LARGEFILE || !__O_LARGEFILE)))) || ((__CRT_HAVE_fdopen || __CRT_HAVE__fdopen || __CRT_HAVE__IO_fdopen) && ((__CRT_HAVE_mkstemp && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkstemp64 || (__CRT_HAVE_mkstemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkstemps64 || (__CRT_HAVE_mkostemps && (!__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask) && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && __SIG_SETMASK) */
#undef __local_tmpfile_s_defined
#endif /* (!__CRT_HAVE_tmpfile || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_tmpfile64 && ((!__CRT_HAVE_fdopen && !__CRT_HAVE__fdopen && !__CRT_HAVE__IO_fdopen) || ((!__CRT_HAVE_memfd_create || !__MFD_CLOEXEC) && ((!__CRT_HAVE_mkstemp && !__CRT_HAVE_mkstemp64 && !__CRT_HAVE_mkstemps && !__CRT_HAVE_mkstemps64 && !__CRT_HAVE_mkostemps && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE___sigprocmask && !__CRT_HAVE___libc_sigprocmask && !__CRT_HAVE_pthread_sigmask && !__CRT_HAVE_thr_sigsetmask) || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) || !__SIG_SETMASK || (__O_LARGEFILE && __O_LARGEFILE)))) && ((!__CRT_HAVE_fdopen && !__CRT_HAVE__fdopen && !__CRT_HAVE__IO_fdopen) || ((!__CRT_HAVE_mkstemp || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkstemp64 && (!__CRT_HAVE_mkstemps || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkstemps64 && (!__CRT_HAVE_mkostemps || (__O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE___sigprocmask && !__CRT_HAVE___libc_sigprocmask && !__CRT_HAVE_pthread_sigmask && !__CRT_HAVE_thr_sigsetmask) || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) || !__SIG_SETMASK) */
#endif /* !__local_tmpfile_s_defined */
