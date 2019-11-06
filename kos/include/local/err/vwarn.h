/* HASH CRC-32:0x97e34122 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vwarn_defined
#include <local/program_invocation_name.h>
#if !defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked))
#define __local_vwarn_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
#include <parts/errno.h>
/* Dependency: "flockfile" */
#ifndef ____localdep_flockfile_defined
#define ____localdep_flockfile_defined 1
#ifdef __CRT_HAVE_flockfile
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),flockfile,(__stream))
#elif defined(__CRT_HAVE__lock_file)
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_lock_file,(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
/* Acquire a lock to `STREAM' and block until doing so succeeds */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#else /* LIBC: flockfile */
#undef ____localdep_flockfile_defined
#endif /* flockfile... */
#endif /* !____localdep_flockfile_defined */

/* Dependency: "fprintf" from "stdio" */
#ifndef ____localdep_fprintf_defined
#define ____localdep_fprintf_defined 1
#if __has_builtin(__builtin_fprintf) && __has_builtin(__builtin_va_arg_pack) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) { return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); }
#elif defined(__CRT_HAVE_fprintf_unlocked) && (defined(__USE_STDIO_UNLOCKED)) && (!defined(__NO_ASMNAME))
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf) && (!defined(__NO_ASMNAME))
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf) && (!defined(__NO_ASMNAME))
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s) && (!defined(__NO_ASMNAME))
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked) && (!defined(__NO_ASMNAME))
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked)
#include <local/stdio/fprintf.h>
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
#define __localdep_fprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fprintf))
#else /* CUSTOM: fprintf */
#undef ____localdep_fprintf_defined
#endif /* fprintf... */
#endif /* !____localdep_fprintf_defined */

/* Dependency: "vfprintf" from "stdio" */
#ifndef ____localdep_vfprintf_defined
#define ____localdep_vfprintf_defined 1
#if __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__FORCELOCAL __ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T (__LIBCCALL __localdep_vfprintf)(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return __builtin_vfprintf(__stream, __format, __args); }
#elif defined(__CRT_HAVE_vfprintf_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf_s)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_vfprintf)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfprintf_unlocked)
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
__CREDIRECT(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked)
#include <local/stdio/vfprintf.h>
/* Print data to `STREAM', following `FORMAT'
 * Return the number of successfully printed bytes */
#define __localdep_vfprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfprintf))
#else /* CUSTOM: vfprintf */
#undef ____localdep_vfprintf_defined
#endif /* vfprintf... */
#endif /* !____localdep_vfprintf_defined */

/* Dependency: "strerror" from "string" */
#ifndef ____localdep_strerror_defined
#define ____localdep_strerror_defined 1
#ifdef __CRT_HAVE_strerror
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(int __errnum),strerror,(__errnum))
#else /* LIBC: strerror */
#include <local/string/strerror.h>
#define __localdep_strerror (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror))
#endif /* strerror... */
#endif /* !____localdep_strerror_defined */

/* Dependency: "funlockfile" */
#ifndef ____localdep_funlockfile_defined
#define ____localdep_funlockfile_defined 1
#ifdef __CRT_HAVE_funlockfile
/* Release a previously acquired lock from `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),funlockfile,(__stream))
#elif defined(__CRT_HAVE__unlock_file)
/* Release a previously acquired lock from `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_unlock_file,(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
/* Release a previously acquired lock from `STREAM' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#else /* LIBC: funlockfile */
#undef ____localdep_funlockfile_defined
#endif /* funlockfile... */
#endif /* !____localdep_funlockfile_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print to stderr: `<program_invocation_short_name>: <format...>: strerror(errno)\n' */
__LOCAL_LIBC(vwarn) __ATTR_LIBC_PRINTF(1, 0) void
(__LIBCCALL __LIBC_LOCAL_NAME(vwarn))(char const *__format,
                                      __builtin_va_list __args) __THROWS(...) {
#line 41 "kos/src/libc/magic/err.c"
	int __errval = __libc_geterrno_or(0);
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	__localdep_flockfile(__LOCAL_stderr);
#endif
	__localdep_fprintf(__LOCAL_stderr, "%s: ", __LOCAL_program_invocation_short_name);
	if (__format) {
		__localdep_vfprintf(__LOCAL_stderr, __format, __args);
		__localdep_fprintf(__LOCAL_stderr, ": %s\n", __localdep_strerror(__errval));
	} else {
		__localdep_fprintf(__LOCAL_stderr, "%s\n", __localdep_strerror(__errval));
	}
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	__localdep_funlockfile(__LOCAL_stderr);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && defined(__LOCAL_program_invocation_short_name) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked)) */
#endif /* !__local_vwarn_defined */
