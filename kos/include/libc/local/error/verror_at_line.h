/* HASH CRC-32:0x29b66e48 */
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
#ifndef __local_verror_at_line_defined
#define __local_verror_at_line_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#include <libc/template/program_invocation_name.h>
#include <features.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_program_invocation_short_name)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_exit_defined
#define __local___localdep_exit_defined
#if __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIREDIRECT(__ATTR_NORETURN,void,,__localdep_exit,(int __status),exit,{ __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE_xexit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_exit,(int __status),xexit,(__status))
#else /* ... */
#undef __local___localdep_exit_defined
#endif /* !... */
#endif /* !__local___localdep_exit_defined */
#ifndef __local___localdep_fflush_defined
#define __local___localdep_fflush_defined
#if defined(__CRT_HAVE_fflush_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream))
#elif defined(__CRT_HAVE_fflush)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush,(__FILE *__stream),fflush,(__stream))
#elif defined(__CRT_HAVE__IO_fflush)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush,(__FILE *__stream),_IO_fflush,(__stream))
#elif defined(__CRT_HAVE_fflush_unlocked)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush,(__FILE *__stream),fflush_unlocked,(__stream))
#elif defined(__CRT_HAVE__fflush_nolock)
__CREDIRECT(,int,__NOTHROW_CB_NCX,__localdep_fflush,(__FILE *__stream),_fflush_nolock,(__stream))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fflush.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fflush __LIBC_LOCAL_NAME(fflush)
#endif /* !... */
#endif /* !__local___localdep_fflush_defined */
#ifndef __local___localdep_fprintf_defined
#define __local___localdep_fprintf_defined
#if defined(__USE_STDIO_UNLOCKED) && __has_builtin(__builtin_fprintf_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf_unlocked) && __has_builtin(__builtin_va_arg_pack)
__CEIREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_fprintf,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf_unlocked,{ return __builtin_fprintf_unlocked(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf_unlocked");
#elif __has_builtin(__builtin_fprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fprintf) && __has_builtin(__builtin_va_arg_pack)
__CEIREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_fprintf,(__FILE *__restrict __stream, char const *__restrict __format, ...),fprintf,{ return __builtin_fprintf(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fprintf)
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf");
#elif defined(__CRT_HAVE__IO_fprintf)
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("_IO_fprintf");
#elif defined(__CRT_HAVE_fprintf_s)
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf_s");
#elif defined(__CRT_HAVE_fprintf_unlocked)
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_CB_NCX(__VLIBCCALL __localdep_fprintf)(__FILE *__restrict __stream, char const *__restrict __format, ...) __CASMNAME("fprintf_unlocked");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fprintf __LIBC_LOCAL_NAME(fprintf)
#endif /* !... */
#endif /* !__local___localdep_fprintf_defined */
#ifndef __local___localdep_fputc_defined
#define __local___localdep_fputc_defined
#if defined(__USE_STDIO_UNLOCKED) && __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
__CEIREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
__CEIREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,{ return __builtin_fputc(__ch, __stream); })
#elif defined(__CRT_HAVE_putc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__putc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_putc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE__fputc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_CB_NCX,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_fputc_nolock,(__ch,__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fputc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fputc __LIBC_LOCAL_NAME(fputc)
#else /* ... */
#undef __local___localdep_fputc_defined
#endif /* !... */
#endif /* !__local___localdep_fputc_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
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
#if defined(__CRT_HAVE_vfprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif __has_builtin(__builtin_vfprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vfprintf)
__CEIREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,{ return __builtin_vfprintf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfprintf)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE__IO_vfprintf)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),_IO_vfprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_s)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_s,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfprintf_unlocked)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_CB_NCX,__localdep_vfprintf,(__FILE *__restrict __stream, char const *__restrict __format, __builtin_va_list __args),vfprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vfprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vfprintf __LIBC_LOCAL_NAME(vfprintf)
#else /* ... */
#undef __local___localdep_vfprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vfprintf_defined */
__NAMESPACE_LOCAL_END
#ifndef __LOCAL_error_print_progname
#ifdef error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#elif defined(__CRT_HAVE_error_print_progname)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,void (__LIBKCALL *__LOCAL_error_print_progname)(void),__LOCAL_error_print_progname,error_print_progname)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE2(,void (__LIBKCALL *error_print_progname)(void),error_print_progname)
#define error_print_progname       error_print_progname
#define __LOCAL_error_print_progname error_print_progname
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_print_progname */
#ifndef __LOCAL_error_one_per_line
#ifdef error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#elif defined(__CRT_HAVE_error_one_per_line)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,__LOCAL_error_one_per_line,error_one_per_line)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,error_one_per_line)
#define error_one_per_line       error_one_per_line
#define __LOCAL_error_one_per_line error_one_per_line
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_one_per_line */
#ifndef __LOCAL_error_message_count
#ifdef error_message_count
#define __LOCAL_error_message_count error_message_count
#elif defined(__CRT_HAVE_error_message_count)
#ifdef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,unsigned int,__LOCAL_error_message_count,error_message_count)
#else /* __NO_COMPILER_SREDIRECT */
__CSDECLARE(,unsigned int,error_message_count)
#define error_message_count       error_message_count
#define __LOCAL_error_message_count error_message_count
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL_error_message_count */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(verror_at_line) __ATTR_LIBC_PRINTF(5, 0) void
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(verror_at_line))(int __status, __errno_t __errnum, char const *__filename, unsigned int __line, char const *__format, __builtin_va_list __args) {
#ifdef __LOCAL_error_one_per_line
	static char const *__last_filename = __NULLPTR;
	static unsigned int __last_line = 0;
	if (__LOCAL_error_one_per_line != 0 &&
	    __line == __last_line && __filename && __last_filename &&
	    (__filename == __last_filename || (__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__filename, __last_filename) == 0)) {
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
#ifdef __LOCAL_stdout
			(__NAMESPACE_LOCAL_SYM __localdep_fflush)(__LOCAL_stdout);
#endif /* __LOCAL_stdout */
			(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s:", __LOCAL_program_invocation_short_name);
		}
		(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s:%u: ", __filename, __line);
		if (__format)
			(__NAMESPACE_LOCAL_SYM __localdep_vfprintf)(__LOCAL_stderr, __format, __args);
#ifdef __LOCAL_error_message_count
		++__LOCAL_error_message_count;
#endif /* __LOCAL_error_message_count */
		if (__errnum != 0)
			(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, ": %s", (__NAMESPACE_LOCAL_SYM __localdep_strerror)(__errnum));
		(__NAMESPACE_LOCAL_SYM __localdep_fputc)('\n', __LOCAL_stderr);
		if (__status != 0)
			(__NAMESPACE_LOCAL_SYM __localdep_exit)(__status);
	}
	if (__status != 0)
		(__NAMESPACE_LOCAL_SYM __localdep_exit)(__status);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_verror_at_line_defined
#define __local___localdep_verror_at_line_defined
#define __localdep_verror_at_line __LIBC_LOCAL_NAME(verror_at_line)
#endif /* !__local___localdep_verror_at_line_defined */
#else /* __LOCAL_stderr && (__CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit) && (__CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_program_invocation_short_name */
#undef __local_verror_at_line_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit && !__CRT_HAVE_xexit) || (!__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) || !__LOCAL_program_invocation_short_name */
#endif /* !__local_verror_at_line_defined */
