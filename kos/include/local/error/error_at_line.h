/* HASH CRC-32:0x82c0d7f9 */
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
#ifndef __local_error_at_line_defined
#include <local/program_invocation_name.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked)) && defined(__LOCAL_program_invocation_short_name)
#define __local_error_at_line_defined 1
#include <kos/anno.h>
#include <bits/types.h>
#include <local/stdstreams.h>
/* Dependency: "strcmp" from "string" */
#ifndef ____localdep_strcmp_defined
#define ____localdep_strcmp_defined 1
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL __localdep_strcmp)(char const *__s1, char const *__s2) { return __builtin_strcmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* LIBC: strcmp */
#include <local/string/strcmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_strcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp))
#endif /* strcmp... */
#endif /* !____localdep_strcmp_defined */

/* Dependency: "fflush" from "stdio" */
#ifndef ____localdep_fflush_defined
#define ____localdep_fflush_defined 1
#if defined(__CRT_HAVE_fflush_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fflush_nolock) && (defined(__USE_STDIO_UNLOCKED))
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fflush)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),fflush,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_fflush)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),_IO_fflush,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fflush_unlocked)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fflush_nolock)
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
__CREDIRECT(,int,,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream)) __THROWS(...)
#else /* LIBC: fflush */
#include <local/stdio/fflush.h>
/* Flush any unwritten data from `STREAM' to the underlying filesystem/TTY */
#define __localdep_fflush (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fflush))
#endif /* fflush... */
#endif /* !____localdep_fflush_defined */

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

/* Dependency: "fputc" from "stdio" */
#ifndef ____localdep_fputc_defined
#define ____localdep_fputc_defined 1
#if __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__FORCELOCAL __ATTR_NONNULL((2)) int (__LIBCCALL __localdep_fputc)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return __builtin_fputc(__ch, __stream); }
#elif defined(__CRT_HAVE_fputc_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_putc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/fputc.h>
/* Write a single character `CH' to `STREAM' */
#define __localdep_fputc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc))
#else /* CUSTOM: fputc */
#undef ____localdep_fputc_defined
#endif /* fputc... */
#endif /* !____localdep_fputc_defined */

/* Dependency: "exit" */
#ifndef ____localdep_exit_defined
#define ____localdep_exit_defined 1
#ifdef __std___localdep_exit_defined
__NAMESPACE_STD_USING(__localdep_exit)
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__FORCELOCAL __ATTR_NORETURN void (__LIBCCALL __localdep_exit)(int __status) __THROWS(...) { __builtin_exit(__status); }
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),exit,(__status)) __THROWS(...)
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),quick_exit,(__status)) __THROWS(...)
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),_exit,(__status)) __THROWS(...)
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),_Exit,(__status)) __THROWS(...)
#else /* LIBC: exit */
#undef ____localdep_exit_defined
#endif /* exit... */
#endif /* !____localdep_exit_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_ASMNAME
__LIBC void (__LIBCCALL *__LOCAL_error_print_progname)(void) __ASMNAME("error_print_progname");
#else /* __NO_ASMNAME */
__LIBC void (__LIBCCALL *error_print_progname)(void);
#ifndef __cplusplus
#define error_print_progname         error_print_progname
#endif /* !__cplusplus */
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_ASMNAME */
#endif /* __CRT_HAVE_error_print_progname */
#endif /* !__LOCAL_error_print_progname */

#ifndef __LOCAL_error_one_per_line
#ifdef error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#elif defined(__CRT_HAVE_error_one_per_line)
#ifdef __NO_ASMNAME
__LIBC int __LOCAL_error_one_per_line __ASMNAME("error_one_per_line");
#else /* __NO_ASMNAME */
__LIBC int error_one_per_line;
#ifndef __cplusplus
#define error_one_per_line         error_one_per_line
#endif /* !__cplusplus */
#define __LOCAL_error_one_per_line error_one_per_line
#endif /* !__NO_ASMNAME */
#endif /* __CRT_HAVE_error_one_per_line */
#endif /* !__LOCAL_error_one_per_line */

#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_ASMNAME
__LIBC unsigned int __LOCAL_error_message_count __ASMNAME("error_message_count");
#else /* __NO_ASMNAME */
__LIBC unsigned int error_message_count;
#ifndef __cplusplus
#define error_message_count         error_message_count
#endif /* !__cplusplus */
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_ASMNAME */
#endif /* __CRT_HAVE_error_message_count */
#endif /* !__LOCAL_error_message_count */
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
 * pass the same values for `filename' and `line' will not produce the error message. */
__LOCAL_LIBC(error_at_line) __ATTR_LIBC_PRINTF(5, 6) void
(__VLIBCCALL __LIBC_LOCAL_NAME(error_at_line))(int __status,
                                               __errno_t __errnum,
                                               char const *__filename,
                                               unsigned int __line,
                                               char const *__format,
                                               ...) __THROWS(...) {
#line 147 "kos/src/libc/magic/error.c"
#ifdef __LOCAL_error_one_per_line
	static char const *__last_filename = __NULLPTR;
	static unsigned int __last_line = 0;
	if (__LOCAL_error_one_per_line != 0 &&
	    __line == __last_line &&
	    (__filename == __last_filename ||
	     __localdep_strcmp(__filename, __last_filename) == 0)) {
		/* Don't print the same error more than once */
	} else
#endif /* __LOCAL_error_one_per_line */
	{
#ifdef __LOCAL_error_one_per_line
		__filename = __last_filename;
		__line     = __last_line;
#endif /* __LOCAL_error_one_per_line */
#ifdef __LOCAL_error_print_progname
		if (__LOCAL_error_print_progname) {
			(*__LOCAL_error_print_progname)();
		} else
#endif /* __LOCAL_error_print_progname */
		{
			__localdep_fflush(__LOCAL_stdout);
			__localdep_fprintf(__LOCAL_stderr, "%s:", __LOCAL_program_invocation_short_name);
		}
		__localdep_fprintf(__LOCAL_stderr, "%s:%u: ", __filename, __line);
		if (__format) {
			__builtin_va_list __args;
			__builtin_va_start(__args, __format);
			__localdep_vfprintf(__LOCAL_stderr, __format, __args);
			__builtin_va_end(__args);
		}
#ifdef __LOCAL_error_message_count
		++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
		if (__errnum != 0)
			__localdep_fprintf(__LOCAL_stderr, ": %s", __localdep_strerror(__errnum));
		__localdep_fputc('\n', __LOCAL_stderr);
		if (__status != 0)
			__localdep_exit(__status);
	}
	if (__status != 0)
		__localdep_exit(__status);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked)) && ((defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked)) && defined(__LOCAL_program_invocation_short_name) */
#endif /* !__local_error_at_line_defined */
