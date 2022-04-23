/* HASH CRC-32:0xaee10f4b */
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
#ifndef __local_vwarnc_defined
#define __local_vwarnc_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if defined(__LOCAL_stderr) && defined(__LOCAL_program_invocation_short_name) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_flockfile_defined
#define __local___localdep_flockfile_defined
#ifdef __CRT_HAVE_flockfile
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),flockfile,(__stream))
#elif defined(__CRT_HAVE__lock_file)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_lock_file,(__stream))
#elif defined(__CRT_HAVE__IO_flockfile)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_RPC,__localdep_flockfile,(__FILE *__restrict __stream),_IO_flockfile,(__stream))
#else /* ... */
#undef __local___localdep_flockfile_defined
#endif /* !... */
#endif /* !__local___localdep_flockfile_defined */
#ifndef __local___localdep_fprintf_defined
#define __local___localdep_fprintf_defined
#if __has_builtin(__builtin_fprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf) && __has_builtin(__builtin_va_arg_pack)
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_fprintf,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf,{ return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#elif defined(__CRT_HAVE_fprintf)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("fprintf_unlocked");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fprintf __LIBC_LOCAL_NAME(fprintf)
#endif /* !... */
#endif /* !__local___localdep_fprintf_defined */
#ifndef __local___localdep_funlockfile_defined
#define __local___localdep_funlockfile_defined
#ifdef __CRT_HAVE_funlockfile
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),funlockfile,(__stream))
#elif defined(__CRT_HAVE__unlock_file)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_unlock_file,(__stream))
#elif defined(__CRT_HAVE__IO_funlockfile)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_funlockfile,(__FILE *__restrict __stream),_IO_funlockfile,(__stream))
#else /* ... */
#undef __local___localdep_funlockfile_defined
#endif /* !... */
#endif /* !__local___localdep_funlockfile_defined */
#ifndef __local___localdep_strerror_defined
#define __local___localdep_strerror_defined
#ifdef __CRT_HAVE_strerror
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(__errno_t __errnum),strerror,(__errnum))
#elif defined(__CRT_HAVE_xstrerror)
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(__errno_t __errnum),xstrerror,(__errnum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerror.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerror __LIBC_LOCAL_NAME(strerror)
#endif /* !... */
#endif /* !__local___localdep_strerror_defined */
#ifndef __local___localdep_vfprintf_defined
#define __local___localdep_vfprintf_defined
#if __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,{ return __builtin_vfprintf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_s)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfprintf)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_unlocked)
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vfprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfprintf __LIBC_LOCAL_NAME(vfprintf)
#else /* ... */
#undef __local___localdep_vfprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vfprintf_defined */
__LOCAL_LIBC(vwarnc) __ATTR_LIBC_PRINTF(2, 0) void
(__LIBCCALL __LIBC_LOCAL_NAME(vwarnc))(__errno_t __used_errno, char const *__format, __builtin_va_list __args) __THROWS(...) {
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_flockfile)(__LOCAL_stderr);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
	(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: ", __LOCAL_program_invocation_short_name);
	if (__format) {
		(__NAMESPACE_LOCAL_SYM __localdep_vfprintf)(__LOCAL_stderr, __format, __args);
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, ": %s\n", (__NAMESPACE_LOCAL_SYM __localdep_strerror)(__used_errno));
	} else {
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s\n", (__NAMESPACE_LOCAL_SYM __localdep_strerror)(__used_errno));
	}
#if (defined(__CRT_HAVE_flockfile) || defined(__CRT_HAVE__lock_file) || defined(__CRT_HAVE__IO_flockfile)) && (defined(__CRT_HAVE_funlockfile) || defined(__CRT_HAVE__unlock_file) || defined(__CRT_HAVE__IO_funlockfile))
	(__NAMESPACE_LOCAL_SYM __localdep_funlockfile)(__LOCAL_stderr);
#endif /* (__CRT_HAVE_flockfile || __CRT_HAVE__lock_file || __CRT_HAVE__IO_flockfile) && (__CRT_HAVE_funlockfile || __CRT_HAVE__unlock_file || __CRT_HAVE__IO_funlockfile) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vwarnc_defined
#define __local___localdep_vwarnc_defined
#define __localdep_vwarnc __LIBC_LOCAL_NAME(vwarnc)
#endif /* !__local___localdep_vwarnc_defined */
#else /* __LOCAL_stderr && __LOCAL_program_invocation_short_name && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __local_vwarnc_defined
#endif /* !__LOCAL_stderr || !__LOCAL_program_invocation_short_name || (!__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__local_vwarnc_defined */
