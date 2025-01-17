/* HASH CRC-32:0x6351b07b */
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
#ifndef __local_tmpfile_defined
#define __local_tmpfile_defined
#include <__crt.h>
#include <asm/os/mman.h>
#include <asm/os/signal.h>
#include <features.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)) && ((defined(__CRT_HAVE_memfd_create) && defined(__MFD_CLOEXEC)) || (((defined(__CRT_HAVE_mkstemp) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemp64) || (defined(__CRT_HAVE_mkstemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemps64) || (defined(__CRT_HAVE_mkostemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))) && defined(__SIG_SETMASK)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_fdopen_defined
#define __local___localdep_fdopen_defined
#ifdef __CRT_HAVE_fdopen
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__fdopen)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),_fdopen,(__fd,__modes))
#elif defined(__CRT_HAVE__IO_fdopen)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1) __ATTR_IN(2),__FILE *,__NOTHROW_NCX,__localdep_fdopen,(__fd_t __fd, char const *__restrict __modes),_IO_fdopen,(__fd,__modes))
#else /* ... */
#undef __local___localdep_fdopen_defined
#endif /* !... */
#endif /* !__local___localdep_fdopen_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#if !defined(__local___localdep_memfd_create_defined) && defined(__CRT_HAVE_memfd_create)
#define __local___localdep_memfd_create_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_memfd_create,(char const *__name, unsigned int __flags),memfd_create,(__name,__flags))
#endif /* !__local___localdep_memfd_create_defined && __CRT_HAVE_memfd_create */
#ifndef __local___localdep_mkstemp_defined
#define __local___localdep_mkstemp_defined
#if defined(__CRT_HAVE_mkstemp) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_RPC,__localdep_mkstemp,(char *__template_),mkstemp,(__template_))
#elif defined(__CRT_HAVE_mkstemp64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_RPC,__localdep_mkstemp,(char *__template_),mkstemp64,(__template_))
#elif (defined(__CRT_HAVE_mkstemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkstemps64) || (defined(__CRT_HAVE_mkostemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mkstemp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkstemp __LIBC_LOCAL_NAME(mkstemp)
#else /* ... */
#undef __local___localdep_mkstemp_defined
#endif /* !... */
#endif /* !__local___localdep_mkstemp_defined */
#ifndef __local___localdep_setsigmaskfullptr_defined
#define __local___localdep_setsigmaskfullptr_defined
#ifdef __CRT_HAVE_setsigmaskfullptr
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL,struct __sigset_struct *,__NOTHROW_NCX,__localdep_setsigmaskfullptr,(void),setsigmaskfullptr,())
#elif defined(__CRT_HAVE_setsigmaskptr)
__NAMESPACE_LOCAL_END
#include <libc/local/signal/setsigmaskfullptr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_setsigmaskfullptr __LIBC_LOCAL_NAME(setsigmaskfullptr)
#else /* ... */
#undef __local___localdep_setsigmaskfullptr_defined
#endif /* !... */
#endif /* !__local___localdep_setsigmaskfullptr_defined */
#if !defined(__local___localdep_setsigmaskptr_defined) && defined(__CRT_HAVE_setsigmaskptr)
#define __local___localdep_setsigmaskptr_defined
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),struct __sigset_struct *,__NOTHROW_NCX,__localdep_setsigmaskptr,(struct __sigset_struct *__sigmaskptr),setsigmaskptr,(__sigmaskptr))
#endif /* !__local___localdep_setsigmaskptr_defined && __CRT_HAVE_setsigmaskptr */
#ifndef __local___localdep_sigfillset_defined
#define __local___localdep_sigfillset_defined
#ifdef __CRT_HAVE_sigfillset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sigfillset,(struct __sigset_struct *__set),sigfillset,(__set))
#else /* __CRT_HAVE_sigfillset */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigfillset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigfillset __LIBC_LOCAL_NAME(sigfillset)
#endif /* !__CRT_HAVE_sigfillset */
#endif /* !__local___localdep_sigfillset_defined */
#ifndef __local___localdep_sigprocmask_defined
#define __local___localdep_sigprocmask_defined
#ifdef __CRT_HAVE_sigprocmask
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___libc_sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__libc_sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),pthread_sigmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_thr_sigsetmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),thr_sigsetmask,(__how,__set,__oset))
#else /* ... */
#undef __local___localdep_sigprocmask_defined
#endif /* !... */
#endif /* !__local___localdep_sigprocmask_defined */
#ifndef __local___localdep_unlink_defined
#define __local___localdep_unlink_defined
#ifdef __CRT_HAVE_unlink
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),unlink,(__file))
#elif defined(__CRT_HAVE__unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__libc_unlink,(__file))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/unlink.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unlink __LIBC_LOCAL_NAME(unlink)
#else /* ... */
#undef __local___localdep_unlink_defined
#endif /* !... */
#endif /* !__local___localdep_unlink_defined */
__NAMESPACE_LOCAL_END
#include <paths.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tmpfile) __ATTR_WUNUSED __FILE *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(tmpfile))(void) {
	__FILE *__result;
	__fd_t __tmpfd;
#if defined(__CRT_HAVE_memfd_create) && defined(__MFD_CLOEXEC)
	__tmpfd = (__NAMESPACE_LOCAL_SYM __localdep_memfd_create)(__NULLPTR, __MFD_CLOEXEC);
#else /* __CRT_HAVE_memfd_create && __MFD_CLOEXEC */
	/* OS doesn't have memory file -> create a temp file and delete it immediately. */
#ifndef _PATH_TMP
#define _PATH_TMP "/tmp/"
#endif /* !_PATH_TMP */
	char __tmpfd_name_buf[__COMPILER_STRLEN(_PATH_TMP "tmp.XXXXXX") + 1];
	(void)(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__tmpfd_name_buf, _PATH_TMP "tmp.XXXXXX", sizeof(__tmpfd_name_buf));
	{
#ifdef __CRT_HAVE_setsigmaskptr
		struct __sigset_struct *__oset;
		__oset  = (__NAMESPACE_LOCAL_SYM __localdep_setsigmaskfullptr)();
		__tmpfd = (__NAMESPACE_LOCAL_SYM __localdep_mkstemp)(__tmpfd_name_buf);
		if __likely(__tmpfd >= 0)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_unlink)(__tmpfd_name_buf);
		(void)(__NAMESPACE_LOCAL_SYM __localdep_setsigmaskptr)(__oset);
#else /* __CRT_HAVE_setsigmaskptr */
		struct __sigset_struct __nset, __oset;
		(void)(__NAMESPACE_LOCAL_SYM __localdep_sigfillset)(&__nset);
		(void)(__NAMESPACE_LOCAL_SYM __localdep_sigprocmask)(__SIG_SETMASK, &__nset, &__oset);
		__tmpfd = (__NAMESPACE_LOCAL_SYM __localdep_mkstemp)(__tmpfd_name_buf);
		if __likely(__tmpfd >= 0)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_unlink)(__tmpfd_name_buf);
		(void)(__NAMESPACE_LOCAL_SYM __localdep_sigprocmask)(__SIG_SETMASK, &__oset, __NULLPTR);
#endif /* !__CRT_HAVE_setsigmaskptr */
	}
#endif /* !__CRT_HAVE_memfd_create || !__MFD_CLOEXEC */
	if __unlikely(__tmpfd < 0)
		return __NULLPTR;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fdopen)(__tmpfd, "w+");
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	if __unlikely(!__result)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__tmpfd);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tmpfile_defined
#define __local___localdep_tmpfile_defined
#define __localdep_tmpfile __LIBC_LOCAL_NAME(tmpfile)
#endif /* !__local___localdep_tmpfile_defined */
#else /* (__CRT_HAVE_fdopen || __CRT_HAVE__fdopen || __CRT_HAVE__IO_fdopen) && ((__CRT_HAVE_memfd_create && __MFD_CLOEXEC) || (((__CRT_HAVE_mkstemp && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkstemp64 || (__CRT_HAVE_mkstemps && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkstemps64 || (__CRT_HAVE_mkostemps && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask) && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) && __SIG_SETMASK)) */
#undef __local_tmpfile_defined
#endif /* (!__CRT_HAVE_fdopen && !__CRT_HAVE__fdopen && !__CRT_HAVE__IO_fdopen) || ((!__CRT_HAVE_memfd_create || !__MFD_CLOEXEC) && (((!__CRT_HAVE_mkstemp || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkstemp64 && (!__CRT_HAVE_mkstemps || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkstemps64 && (!__CRT_HAVE_mkostemps || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE___sigprocmask && !__CRT_HAVE___libc_sigprocmask && !__CRT_HAVE_pthread_sigmask && !__CRT_HAVE_thr_sigsetmask) || (!__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat)) || !__SIG_SETMASK)) */
#endif /* !__local_tmpfile_defined */
