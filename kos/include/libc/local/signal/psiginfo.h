/* HASH CRC-32:0xa5db1b88 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_psiginfo_defined
#define __local_psiginfo_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <features.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <bits/os/siginfo.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fprintf_defined
#define __local___localdep_fprintf_defined
#if defined(__USE_STDIO_UNLOCKED) && __has_builtin(__builtin_fprintf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf_unlocked) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fprintf,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf_unlocked,{ return __builtin_fprintf_unlocked(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif __has_builtin(__builtin_fprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fprintf,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf,{ return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fprintf __LIBC_LOCAL_NAME(fprintf)
#else /* ... */
#undef __local___localdep_fprintf_defined
#endif /* !... */
#endif /* !__local___localdep_fprintf_defined */
#ifndef __local___localdep_sigabbrev_np_defined
#define __local___localdep_sigabbrev_np_defined
#ifdef __CRT_HAVE_sigabbrev_np
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),sigabbrev_np,(__signum))
#elif defined(__CRT_HAVE_signalname)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),signalname,(__signum))
#elif defined(__CRT_HAVE_strsigno)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_sigabbrev_np,(__signo_t __signum),strsigno,(__signum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/sigabbrev_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigabbrev_np __LIBC_LOCAL_NAME(sigabbrev_np)
#endif /* !... */
#endif /* !__local___localdep_sigabbrev_np_defined */
#ifndef __local___localdep_strsigcode_s_defined
#define __local___localdep_strsigcode_s_defined
#ifdef __CRT_HAVE_strsigcode_s
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__localdep_strsigcode_s,(__signo_t __signo, int __code),strsigcode_s,(__signo,__code))
#else /* __CRT_HAVE_strsigcode_s */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/strsigcode_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strsigcode_s __LIBC_LOCAL_NAME(strsigcode_s)
#endif /* !__CRT_HAVE_strsigcode_s */
#endif /* !__local___localdep_strsigcode_s_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
#include <bits/crt/inttypes.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(psiginfo) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(psiginfo))(struct __siginfo_struct const *__pinfo, char const *__s) {
	char const *__text;
	__text = (__NAMESPACE_LOCAL_SYM __localdep_sigabbrev_np)(__pinfo->si_signo);
	if (__s && *__s)
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: ", __s);
	if (__text) {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "SIG%s (", __text);
#if defined(__SIGRTMIN) && defined(__SIGRTMAX)
	} else if (__pinfo->si_signo >= __SIGRTMIN &&
	           __pinfo->si_signo <= __SIGRTMAX) {
		unsigned int __offset;
		__offset = (unsigned int)(__pinfo->si_signo - __SIGRTMIN);
		if (__offset != 0) {
			(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "SIGRTMIN+%u (", __offset);
		} else {
			(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "SIGRTMIN (");
		}
#endif /* __SIGRTMIN && __SIGRTMAX */
	} else {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "Unknown signal %d (", __pinfo->si_signo);
	}
	__text = (__NAMESPACE_LOCAL_SYM __localdep_strsigcode_s)(__pinfo->si_signo, __pinfo->si_code);
	if (__text) {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s ", __text);
	} else {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%u ", (unsigned int)__pinfo->si_code);
	}
#if defined(__SIGILL) || defined(__SIGFPE) || defined(__SIGSEGV) || defined(__SIGBUS)
	if (0
#ifdef __SIGILL
	    || __pinfo->si_signo == __SIGILL
#endif /* __SIGILL */
#ifdef __SIGFPE
	    || __pinfo->si_signo == __SIGFPE
#endif /* __SIGFPE */
#ifdef __SIGSEGV
	    || __pinfo->si_signo == __SIGSEGV
#endif /* __SIGSEGV */
#ifdef __SIGBUS
	    || __pinfo->si_signo == __SIGBUS
#endif /* __SIGBUS */
	    ) {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "[%p])\n", __pinfo->si_addr);
	} else
#endif /* __SIGILL || __SIGFPE || __SIGSEGV || __SIGBUS */
#ifdef __SIGCHLD
	if (__pinfo->si_signo == __SIGCHLD) {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr,
		        "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d %d "
		        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		        (__pid_t)__pinfo->si_pid,
		        (int)__pinfo->si_status,
		        (__uid_t)__pinfo->si_uid);
	} else
#endif /* __SIGCHLD */
#ifdef __SIGPOLL
	if (__pinfo->si_signo == __SIGPOLL) {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%" __PRIN_PREFIX(__SIZEOF_POINTER__) "d)\n",
		        (__LONGPTR_TYPE__)__pinfo->si_band);
	} else
#endif /* __SIGPOLL */
	{
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr,
		        "%" __PRIN_PREFIX(__SIZEOF_PID_T__) "d "
		        "%" __PRIN_PREFIX(__SIZEOF_UID_T__) "d)\n",
		        (__pid_t)__pinfo->si_pid,
		        (__uid_t)__pinfo->si_uid);
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_psiginfo_defined
#define __local___localdep_psiginfo_defined
#define __localdep_psiginfo __LIBC_LOCAL_NAME(psiginfo)
#endif /* !__local___localdep_psiginfo_defined */
#else /* __LOCAL_stderr && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __local_psiginfo_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__local_psiginfo_defined */
