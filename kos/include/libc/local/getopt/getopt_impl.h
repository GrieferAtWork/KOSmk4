/* HASH CRC-32:0x9e4410e2 */
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
#ifndef __local_getopt_impl_defined
#define __local_getopt_impl_defined
#include <__crt.h>
#include <libc/template/getopt.h>
#if defined(__LOCAL_optarg) && defined(__LOCAL_optind)
#include <bits/crt/getopt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
#ifndef __local___localdep_fprintf_defined
#define __local___localdep_fprintf_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
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
#elif defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fprintf __LIBC_LOCAL_NAME(fprintf)
#else /* ... */
#undef __local___localdep_fprintf_defined
#endif /* !... */
#endif /* !__local___localdep_fprintf_defined */
#ifndef __local___localdep_fputc_defined
#define __local___localdep_fputc_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#else /* __CRT_HAVE_getenv */
__NAMESPACE_LOCAL_END
#include <libc/template/environ.h>
__NAMESPACE_LOCAL_BEGIN
#ifdef __LOCAL_environ
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#else /* __LOCAL_environ */
#undef __local___localdep_getenv_defined
#endif /* !__LOCAL_environ */
#endif /* !__CRT_HAVE_getenv */
#endif /* !__local___localdep_getenv_defined */
#ifndef __local___localdep_memmovedownc_defined
#define __local___localdep_memmovedownc_defined
#ifdef __CRT_HAVE_memmovedownc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovedownc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovedownc __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__CRT_HAVE_memmovedownc */
#endif /* !__local___localdep_memmovedownc_defined */
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
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
#ifndef __local___localdep_strcmpz_defined
#define __local___localdep_strcmpz_defined
#ifdef __CRT_HAVE_strcmpz
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmpz,(char const *__lhs, char const *__rhs, __SIZE_TYPE__ __rhs_len),strcmpz,(__lhs,__rhs,__rhs_len))
#else /* __CRT_HAVE_strcmpz */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmpz.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmpz __LIBC_LOCAL_NAME(strcmpz)
#endif /* !__CRT_HAVE_strcmpz */
#endif /* !__local___localdep_strcmpz_defined */
#ifndef __local___localdep_strncmp_defined
#define __local___localdep_strncmp_defined
#if __has_builtin(__builtin_strncmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmp,{ return __builtin_strncmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strncmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmp,(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncmp __LIBC_LOCAL_NAME(strncmp)
#endif /* !... */
#endif /* !__local___localdep_strncmp_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libc/template/stdstreams.h>
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getopt_impl) __ATTR_WUNUSED __ATTR_NONNULL((2, 3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getopt_impl))(unsigned int ___argc, char const *___argv[], char const *__optstring, struct option const *__longopts, unsigned int *__longindex, unsigned int __flags) {

	/* True if getopt has been initialized. */



	static __BOOL __getopt_initialized = 0;

	/* 0: permute-argv       (permute non-options to the back of `argv')
	 * 1: optstring[0]=='-'  (yield non-options via `optarg' and `return == 1')
	 * 2: optstring[1]=='+'  (stop parsing on the first non-option argument) */



	static __UINT8_TYPE__ __getopt_parsemode = 0;

	/* Pointer to the  next character in  `argv[optind]' that hasn't  been
	 * parsed, yet (used for arguments containing multiple short-options).
	 *
	 * Points to an empty string if no further short options can be loaded. */



	static char const *__getopt_nextchar = __NULLPTR;

	/* Pointers-to-globals */
	unsigned int *__p_optind = (unsigned int *)&__LOCAL_optind;
	char const  **__p_optarg = (char const **)&__LOCAL_optarg;

	/* Current argument */
	char const *__arg;
	char const *__longopt_prefix;

	/*syslog(LOG_DEBUG, "getopt(%d, [", argc);
	for (unsigned int i = 0; i < argc; ++i)
		syslog(LOG_DEBUG, "%s%q", i ? ", " : "", argv[i]);
	syslog(LOG_DEBUG, "], %q, flags: %#x) [getopt_parsemode: %u, getopt_nextchar: %q, optind: %u]\n",
	       optstring, flags, (unsigned int)getopt_parsemode, getopt_nextchar, *p_optind);*/

	/* (re-)initialize getopt parser configuration on first use (or when `optind == 0'). */
	if (!__getopt_initialized || *__p_optind == 0
#ifdef __LOCAL_optreset
	    || __LOCAL_optreset
#endif /* __LOCAL_optreset */
		) {
#ifdef __LOCAL_optreset
		__LOCAL_optreset = 0;
#endif /* __LOCAL_optreset */
		if (*__p_optind == 0)
			*__p_optind = 1;
		__getopt_nextchar    = "";
		__getopt_initialized = 1;

		/* Figure out which parsing mode to use. */
		if (*__optstring == '-') {
			__getopt_parsemode = 1;
			++__optstring;
		} else if (*__optstring == '+') {
			__getopt_parsemode = 2;
			++__optstring;
		} else if ((__flags & 2)
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
		           || (__NAMESPACE_LOCAL_SYM __localdep_getenv)("POSIXLY_CORRECT") != __NULLPTR
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
		           ) {
			__getopt_parsemode = 2;
		} else {
			__getopt_parsemode = 0;
		}
	} else {
		if (*__optstring == '-' || *__optstring == '+')
			++__optstring;
	}

	/* Default: no argument (if appropriate, this gets overwritten later) */
	*__p_optarg = __NULLPTR;

	/* Check if a short-option-group is currently in progress. */
	if (*__getopt_nextchar != '\0') {
		/* Parse the next character from a multi-char short option. */
		char __optch;
		char const *__optspec_ptr;
__parse_short_option_from_getopt_nextchar:
		__optch = *__getopt_nextchar++;
		if __unlikely(__optch == ':' || __optch == ';') {
__err_bad_getopt_nextchar:
#if (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_stderr)
			if (__optstring[0] != ':'
#ifdef __LOCAL_opterr
			    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
			    ) {
				(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: invalid option -- '%c'\n", ___argv[0], __optch);
			}
#endif /* (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_stderr */
#ifdef __LOCAL_optopt
			__LOCAL_optopt = (unsigned char)__optch;
#endif /* __LOCAL_optopt */
			__getopt_nextchar = "";
			return '?';
		}
		__optspec_ptr = (__NAMESPACE_LOCAL_SYM __localdep_strchr)(__optstring, __optch);
		if __unlikely(__optspec_ptr == __NULLPTR)
			goto __err_bad_getopt_nextchar;
		if (__optch == 'W' && __optspec_ptr[1] == ';' && __longopts != __NULLPTR) {
			/* Special case: `-Wfoo' and `-W foo' behave like "--foo" */
			if (*__getopt_nextchar != '\0') {
				__arg = __getopt_nextchar;
				++(*__p_optind);
			} else {
				++(*__p_optind); /* consume option-argument */
				if __unlikely(*__p_optind >= ___argc)
					goto __err_optch_requires_argument;
				__arg = ___argv[(*__p_optind)++]; /* consume argument operand */
			}
			__longopt_prefix = "-W ";
			goto __do_arg_long_option;
		}

		/* Check if this option takes an argument. */
		if (__optspec_ptr[1] == ':') {
			if (__optspec_ptr[2] == ':') {
				/* Special case: optional short-argument (only allowed for something like "-ofile.txt") */
				if (*__getopt_nextchar != '\0') {
					*__p_optarg = __getopt_nextchar;
					++(*__p_optind);
				}
			} else {
				if (*__getopt_nextchar != '\0') {
					/* Option argument is next remainder of current argument */
					*__p_optarg = __getopt_nextchar;
					++(*__p_optind);
				} else {
					/* Option argument is next argv-argument */
					++(*__p_optind); /* consume option-argument */
					if __unlikely(*__p_optind >= ___argc)
						goto __err_optch_requires_argument;
					*__p_optarg = ___argv[(*__p_optind)++]; /* consume argument operand */
				}
			}
			/* Mark short-option-group as being empty now. */
			__getopt_nextchar = "";
		} else {
			if (*__getopt_nextchar == '\0')
				++(*__p_optind); /* End-of-options-group-argument */
		}
		return (unsigned char)__optch;

__err_optch_requires_argument:
#if (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_stderr)
		if (__optstring[0] != ':'
#ifdef __LOCAL_opterr
		    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
		    ) {
			(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: option requires an argument -- '%c'\n", ___argv[0], __optch);
		}
#endif /* (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_stderr */
#ifdef __LOCAL_optopt
		__LOCAL_optopt = (unsigned char)__optch;
#endif /* __LOCAL_optopt */
		goto __err_return_col_or_qmark;
	}

	/* No short-option-group in progress -- load the next argument from argv. */
	if (*__p_optind >= ___argc)
		return -1; /* No more options... */

__load_arg_from__ind__p_optind:
	__arg = ___argv[*__p_optind];
#define __GETOPT_IS_NONOPTION_ARGUMENT(__arg) ((__arg)[0] != '-' || (__arg)[1] == '\0')
	if (__GETOPT_IS_NONOPTION_ARGUMENT(__arg)) {
		unsigned int __i, __nonoption_start, __nonoption_end, __nonoption_insert;
		/* Non-option argument encountered. */
		if (__getopt_parsemode == 2)
			return -1; /* stop parsing on the first non-option argument */
		if (__getopt_parsemode == 1) {
			*__p_optarg = __arg;
			++(*__p_optind);
			return 1;
		}
		/* Check if there are only non-option arguments from on out. */
		for (__i = *__p_optind + 1; __i < ___argc; ++__i) {
			__arg = ___argv[__i];
			if (!__GETOPT_IS_NONOPTION_ARGUMENT(__arg))
				goto __not_already_permuted;
		}
		/* There are only non-option arguments remaining, so we're done! */
		return -1;
__not_already_permuted:
		/* Permutate `argv' to move all non-option arguments to the end,
		 * or immediately  after  the  "--" argument  (if  it's  there). */
		__nonoption_start  = *__p_optind;
		__nonoption_end    = __nonoption_start;
		__nonoption_insert = ___argc;
		while (__nonoption_end < ___argc) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(___argv[__nonoption_end], "--") == 0) {
				__nonoption_insert = __nonoption_end + 1;
				break;
			}
			++__nonoption_end;
		}

		/* Move shift all non-option arguments in `[nonoption_start,nonoption_end)'
		 * such  that they  all appear  at (what  is currently) `nonoption_insert'. */
		__i = __nonoption_end;
		while (__i > __nonoption_start) {
			--__i;
			__arg = ___argv[__i];
			if (__GETOPT_IS_NONOPTION_ARGUMENT(__arg)) {
				--__nonoption_insert;
				(__NAMESPACE_LOCAL_SYM __localdep_memmovedownc)(&___argv[__i],
				             &___argv[__i + 1],
				             __nonoption_insert - __i,
				             sizeof(char const *));
				___argv[__nonoption_insert] = __arg;
			}
		}
		goto __load_arg_from__ind__p_optind;
	}
#undef __GETOPT_IS_NONOPTION_ARGUMENT

	/* Got an option argument in `arg = argv[*p_optind]'. */
	++__arg; /* Skip leading '-' */

	if (__arg[0] == '-' && __arg[1] == '\0') {
		/* Special case: "--" */
		++(*__p_optind); /* Consume "--" */
		return -1; /* No more options... (rest of argv are just normal arguments) */
	}

	/* Check for long options. */
	if (__longopts) {
		struct option const *__longopt;
		__SIZE_TYPE__ __optname_len;
		if (*__arg == '-') {
			/* "--" always indicates a long option */
			++__arg;
			__longopt_prefix = "--";
		} else {
			/* When `getopt_long_only(3)' was used, we also accept "-" for long options. */
			if (!(__flags & 0x0001))
				goto __not_a_long_option;
			if (__arg[1] == '\0')
				goto __not_a_long_option;
			if (__arg[2] == '\0' && (__NAMESPACE_LOCAL_SYM __localdep_strchr)(__optstring, __arg[1]) != __NULLPTR)
				goto __not_a_long_option;
			__longopt_prefix = "-";
		}
__do_arg_long_option:

		/* Figure out the length of the long option name in `arg' */
		for (__optname_len = 0; __arg[__optname_len] != '\0' &&
		                      __arg[__optname_len] != '=';)
			++__optname_len;

		/* Check if there is a long option matching the given name. */
		for (__longopt = __longopts;; ++__longopt) {
			if (__longopt->name == __NULLPTR) {
				__BYTE_TYPE__ *__ambig_set;
				struct option const *__candidate;

				/* long options are special, in that (so-long as it's not ambiguous),
				 * you're allowed to  specify only  part of the  long option's  name:
				 * $ ls --almo
				 * Works, and behaves the same as:
				 * $ ls --almost-all */
				__ambig_set = __NULLPTR;
				__candidate = __NULLPTR;
				for (__longopt = __longopts; __longopt->name != __NULLPTR; ++__longopt) {
					if ((__NAMESPACE_LOCAL_SYM __localdep_strncmp)(__longopt->name, __arg, __optname_len) != 0) /* Check for starts-with */
						continue;
					if (__candidate == __NULLPTR) {
						__candidate = __longopt;
					} else {
						__SIZE_TYPE__ __longopt_id;
#ifdef __malloca_mayfail
						if (__ambig_set == (__BYTE_TYPE__ *)-1)
							continue; /* Failed to allocate set of candidates. */
#endif /* __malloca_mayfail */
						if (__ambig_set == __NULLPTR) {
							__SIZE_TYPE__ __num_options;
							__num_options = (__SIZE_TYPE__)(__longopt - __longopts) + 1;
							while (__longopts[__num_options].name != __NULLPTR)
								++__num_options;
							__num_options += (__CHAR_BIT__ - 1);
							__num_options /= __CHAR_BIT__;
							__ambig_set = (__BYTE_TYPE__ *)__malloca(__num_options);
#ifdef __malloca_mayfail
							if (__ambig_set == __NULLPTR) {
								/* Failed to allocate set of candidates. */
								__ambig_set = (__BYTE_TYPE__ *)-1;
								continue;
							}
#endif /* __malloca_mayfail */
							(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__ambig_set, __num_options);
							__longopt_id = (__SIZE_TYPE__)(__candidate - __longopts);
							__ambig_set[__longopt_id / __CHAR_BIT__] |= (__BYTE_TYPE__)1 << (__longopt_id % __CHAR_BIT__);
						}
						__longopt_id = (__SIZE_TYPE__)(__longopt - __longopts);
						__ambig_set[__longopt_id / __CHAR_BIT__] |= (__BYTE_TYPE__)1 << (__longopt_id % __CHAR_BIT__);
					}
				}
				if (__ambig_set != __NULLPTR) {
#ifdef __malloca_mayfail
					if (__ambig_set == (__BYTE_TYPE__ *)-1) {
						/* Error: ambiguous long option */
#if (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_stderr)
						if (__optstring[0] != ':'
#ifdef __LOCAL_opterr
						    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
						    ) {
							(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: option `%s%s' is ambiguous\n",
							        ___argv[0], __longopt_prefix, __arg);
						}
#endif /* (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_stderr */
					} else
#endif /* __malloca_mayfail */
					{
						/* Error: ambiguous long option */
#if (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_stderr)
						if (__optstring[0] != ':'
#ifdef __LOCAL_opterr
						    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
						    ) {
							__SIZE_TYPE__ __longopt_id;
							(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: option `%s%s' is ambiguous; possibilities:",
							        ___argv[0], __longopt_prefix, __arg);
							for (__longopt_id = 0; __longopts[__longopt_id].name; ++__longopt_id) {
								if (!(__ambig_set[__longopt_id / __CHAR_BIT__] & (__BYTE_TYPE__)1 << (__longopt_id % __CHAR_BIT__)))
									continue;
								(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, " `%s%s'", __longopt_prefix, __longopts[__longopt_id].name);
							}
#if defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
							(__NAMESPACE_LOCAL_SYM __localdep_fputc)('\n', __LOCAL_stderr);
#else /* __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
							(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "\n");
#endif /* !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock */
						}
#endif /* (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_stderr */
						__freea(__ambig_set);
					}
					goto __err_longopt_common;
				}
				if (__candidate != __NULLPTR) {
					/* Only a single candidate exists -> that's the one we want to use! */
					__longopt = __candidate;
					goto __do_use_longopt;
				}

				/* If we got here due to something like "-foo", then go to the normal handler instead. */
				if ((__flags & 0x0001) && __arg == &___argv[*__p_optind][1] && (__NAMESPACE_LOCAL_SYM __localdep_strchr)(__optstring, *__arg) != __NULLPTR)
					goto __not_a_long_option;

				/* Error: no such long option */
#if (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_stderr)
				if (__optstring[0] != ':'
#ifdef __LOCAL_opterr
				    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
				    ) {
					(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: unrecognized option `%s%s'\n", ___argv[0], __longopt_prefix, __arg);
				}
#endif /* (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_stderr */
__err_longopt_common:
				++(*__p_optind);
#ifdef __LOCAL_optopt
				__LOCAL_optopt = 0;
#endif /* __LOCAL_optopt */
				return '?';
			}

			/* Check for exact match. */
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmpz)(__longopt->name, __arg, __optname_len) == 0)
				break; /* Found it! */
		}
__do_use_longopt:

		/* We found the long-option, and its potential argument.
		 * Now to match the 2 against each other (and assert the
		 * presence or absence of an argument) */
		++(*__p_optind); /* Consume the argument containing the long-option itself. */
		__arg += __optname_len; /* Jump to the '\0' or '=<arg>' */
		if (*__arg == '=') {
			/* Long option has an argument in `argv' */
			++__arg;
			if (__longopt->has_arg != __no_argument) {
				*__p_optarg = __arg;
			} else {
#if (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_stderr)
				if (__optstring[0] != ':'
#ifdef __LOCAL_opterr
				    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
				    ) {
					(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: option `%s%s' doesn't allow an argument\n",
					        ___argv[0], __longopt_prefix, __longopt->name);
				}
#endif /* (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_stderr */
#ifdef __LOCAL_optopt
				__LOCAL_optopt = __longopt->val;
#endif /* __LOCAL_optopt */
				return '?';
			}
		} else if (__longopt->has_arg == __required_argument) {
			/* Must take the argument from `argv[*p_optind]' */
			if (*__p_optind >= ___argc) {
#if (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && defined(__LOCAL_stderr)
				if (__optstring[0] != ':'
#ifdef __LOCAL_opterr
				    && __LOCAL_opterr
#endif /* __LOCAL_opterr */
				    ) {
					(__NAMESPACE_LOCAL_SYM __localdep_fprintf)(__LOCAL_stderr, "%s: option `%s%s' requires an argument\n",
					        ___argv[0], __longopt_prefix, __longopt->name);
				}
#endif /* (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && __LOCAL_stderr */
#ifdef __LOCAL_optopt
				__LOCAL_optopt = __longopt->val;
#endif /* __LOCAL_optopt */
				goto __err_return_col_or_qmark;
			}
			*__p_optarg = ___argv[(*__p_optind)++];
		}
		if (__longindex != __NULLPTR)
			*__longindex = (unsigned int)(__SIZE_TYPE__)(__longopt - __longopts);
		if (__longopt->flag != __NULLPTR) {
			*__longopt->flag = __longopt->val;
			return 0;
		}
		return __longopt->val;
	}

	/* It's not a long option, so it _has_ to be a short option! */
__not_a_long_option:
	__getopt_nextchar = __arg;
	goto __parse_short_option_from_getopt_nextchar;
__err_return_col_or_qmark:
	return __optstring[0] == ':' ? ':' : '?';
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getopt_impl_defined
#define __local___localdep_getopt_impl_defined
#define __localdep_getopt_impl __LIBC_LOCAL_NAME(getopt_impl)
#endif /* !__local___localdep_getopt_impl_defined */
#else /* __LOCAL_optarg && __LOCAL_optind */
#undef __local_getopt_impl_defined
#endif /* !__LOCAL_optarg || !__LOCAL_optind */
#endif /* !__local_getopt_impl_defined */
