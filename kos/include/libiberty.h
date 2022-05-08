/* HASH CRC-32:0xe59cbdac */
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
/* (#) Portability: EMX kLIBC (/libc/include/libiberty.h) */
/* (#) Portability: libiberty (/include/libiberty.h) */
#ifndef _LIBIBERTY_H
#define _LIBIBERTY_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>
#include <stdio.h>
#include <libc/string.h>
#include <hybrid/__alloca.h>

#ifdef __USE_GLIBC
#include <stddef.h>
#include <stdarg.h>
#endif /* __USE_GLIBC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

#define ARRAY_SIZE __COMPILER_LENOF

#define MAX_ALLOCA_SIZE 4032

#ifdef __CRT_HAVE_C_alloca
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,C_alloca,(size_t __num_bytes),(__num_bytes))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/C_alloca.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(C_alloca, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL C_alloca)(size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(C_alloca))(__num_bytes); })
#endif /* ... */
#undef C_ALLOCA
#if defined(__hybrid_alloca) && !defined(__USE_C_ALLOCA)
#undef alloca
#define alloca(num_bytes) __hybrid_alloca(num_bytes)
#elif defined(__CRT_HAVE_C_alloca) || defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#undef alloca
#define alloca(x) C_alloca(x)
#undef USE_C_ALLOCA
#define USE_C_ALLOCA 1
#undef C_ALLOCA
#define C_ALLOCA 1
#endif /* ... */
#ifdef alloca
#ifdef __NO_XBLOCK
#ifdef __CRT_HAVE_libiberty_optr
__CSDECLARE(,char const *,libiberty_optr)
#define ASTRDUP(str) \
	(libiberty_optr = (str), __libc_strcpy((char *)__hybrid_alloca((__libc_strlen(libiberty_optr) + 1) * sizeof(char)), libiberty_optr))
#else /* __CRT_HAVE_libiberty_optr */
#define ASTRDUP(str) \
	(__libc_strcpy((char *)__hybrid_alloca((__libc_strlen(str) + 1) * sizeof(char)), str))
#endif /* !__CRT_HAVE_libiberty_optr */
#else /* __NO_XBLOCK */
#define ASTRDUP(str)                                                         \
	__XBLOCK({                                                               \
		char const *__orig_s = (str);                                        \
		__size_t __orig_len  = (__libc_strlen(__orig_s) + 1) * sizeof(char); \
		__XRETURN (char *)__libc_memcpy(__hybrid_alloca(__orig_len),         \
		                                __orig_s, __orig_len);               \
	})
#endif /* !__NO_XBLOCK */


#ifdef __NO_XBLOCK
#define ASTRDUP(str)                                     \
	(libiberty_optr = (str),                             \
	 libiberty_len  = __libc_strlen(libiberty_optr) + 1, \
	 libiberty_nptr = (char *)alloca(libiberty_len),     \
	 (char *)__libc_memcpy(libiberty_nptr, libiberty_optr, libiberty_len))
#else /* __NO_XBLOCK */
#define ASTRDUP(str)                                                                           \
	__XBLOCK({                                                                                 \
		char const *__astrdup_str = (str);                                                     \
		size_t __astrdup_siz      = (__libc_strlen(__astrdup_str) + 1) * sizeof(char);         \
		__XRETURN((char *)__libc_memcpy(alloca(__astrdup_siz), __astrdup_str, __astrdup_siz)); \
	})
#endif /* !__NO_XBLOCK */
#endif /* alloca */
#ifndef __asprintf_defined
#define __asprintf_defined
#ifdef __CRT_HAVE_asprintf
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME_SAME("asprintf");
#elif defined(__CRT_HAVE___asprintf)
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) __CASMNAME("__asprintf");
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <libc/local/stdio/asprintf.h>
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(asprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL asprintf)(char **__restrict __pstr, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))(__pstr, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define asprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ... */
#undef __asprintf_defined
#endif /* !... */
#endif /* !__asprintf_defined */
#ifndef __vasprintf_defined
#define __vasprintf_defined
#ifdef __CRT_HAVE_vasprintf
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__CDECLARE(__ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vasprintf,(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args),(__pstr,__format,__args))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
#include <libc/local/stdio/vasprintf.h>
/* >> asprintf(3), vasprintf(3)
 * Print the given `format' into a newly allocated, heap-allocated string which is then stored in `*pstr' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vasprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vasprintf)(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vasprintf))(__pstr, __format, __args); })
#else /* ... */
#undef __vasprintf_defined
#endif /* !... */
#endif /* !__vasprintf_defined */
#ifndef __snprintf_defined
#define __snprintf_defined
#ifdef __std_snprintf_defined
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__NAMESPACE_STD_USING(snprintf)
#elif __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CEIDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,snprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...),{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) __CASMNAME_SAME_GCCNCX("snprintf");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
#include <libc/local/stdio/snprintf.h>
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(snprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL snprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define snprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(snprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !... */
#endif /* !__snprintf_defined */
#ifndef __vsnprintf_defined
#define __vsnprintf_defined
#ifdef __std_vsnprintf_defined
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__NAMESPACE_STD_USING(vsnprintf)
#elif __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CEIDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CDECLARE_GCCNCX(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__CREDIRECT_GCCNCX(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vsnprintf,(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
#include <libc/local/stdio/vsnprintf.h>
/* >> snprintf(3), vsnprintf(3)
 * Print  a formatted string to a given in-member string buffer `buf'
 * Always return the REQUIRED buffer size (excluding a trailing  NUL-
 * character), and never write more than `buflen' characters to `buf' */
__NAMESPACE_LOCAL_USING_OR_IMPL(vsnprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vsnprintf)(char *__restrict __buf, size_t __buflen, char const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsnprintf))(__buf, __buflen, __format, __args); })
#endif /* !... */
#endif /* !__vsnprintf_defined */
#ifndef __strverscmp_defined
#define __strverscmp_defined
#ifdef __CRT_HAVE_strverscmp
/* >> strverscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strverscmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE___strverscmp)
/* >> strverscmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strverscmp,(char const *__s1, char const *__s2),__strverscmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strverscmp.h>
/* >> strverscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strverscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strverscmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strverscmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__strverscmp_defined */
#ifndef __basename_defined
#define __basename_defined
#ifdef __CRT_HAVE_basename
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,basename,(char *__filename),basename,(__filename))
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,basename,(char const *__filename),basename,(__filename))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,basename,(char const *__filename),(__filename))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE___basename)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,basename,(char *__filename),__basename,(__filename))
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,basename,(char const *__filename),__basename,(__filename))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,basename,(char const *__filename),__basename,(__filename))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_lbasename)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,basename,(char *__filename),lbasename,(__filename))
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,basename,(char const *__filename),lbasename,(__filename))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,basename,(char const *__filename),lbasename,(__filename))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/basename.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL basename)(char *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__NAMESPACE_LOCAL_USING_OR_IMPL(basename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL basename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__basename_defined */
#ifndef __ffs_defined
#define __ffs_defined
#if __has_builtin(__builtin_ffs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ffs)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),{ return __builtin_ffs(__i); })
#elif defined(__CRT_HAVE_ffs)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),(__i))
#elif defined(__CRT_HAVE_ffsl) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),ffsl,(__i))
#elif defined(__CRT_HAVE_ffsll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),ffsll,(__i))
#elif defined(__CRT_HAVE___ffs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_UINT_T,__NOTHROW,ffs,(int __i),__ffs,(__i))
#else /* ... */
#include <libc/local/string/ffs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ffs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_UINT_T __NOTHROW(__LIBCCALL ffs)(int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ffs))(__i); })
#endif /* !... */
#endif /* !__ffs_defined */
#ifndef __strtosigno_defined
#define __strtosigno_defined
#ifdef __CRT_HAVE_strtosigno
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g.: `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__signo_t,__NOTHROW_NCX,strtosigno,(const char *__name),(__name))
#else /* __CRT_HAVE_strtosigno */
#include <libc/local/string/strtosigno.h>
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g.: `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(strtosigno, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __signo_t __NOTHROW_NCX(__LIBCCALL strtosigno)(const char *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtosigno))(__name); })
#endif /* !__CRT_HAVE_strtosigno */
#endif /* !__strtosigno_defined */
#ifndef __strnlen_defined
#define __strnlen_defined
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),{ return __builtin_strnlen(__str, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#elif defined(__CRT_HAVE___strncnt)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),__strncnt,(__str,__maxlen))
#else /* ... */
#include <libc/local/string/strnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(strnlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL strnlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlen))(__str, __maxlen); })
#endif /* !... */
#endif /* !__strnlen_defined */
#ifndef __strtol_defined
#define __strtol_defined
#ifdef __std_strtol_defined
__NAMESPACE_STD_USING(strtol)
#elif defined(__CRT_HAVE_strtol)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,strtol,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#else /* ... */
#include <libc/local/stdlib/strtol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL strtol)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtol))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__strtol_defined */
#ifndef __strtoul_defined
#define __strtoul_defined
#ifdef __std_strtoul_defined
__NAMESPACE_STD_USING(strtoul)
#elif defined(__CRT_HAVE_strtoul)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,strtoul,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/stdlib/strtoul.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL strtoul)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoul))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__strtoul_defined */
#ifdef __LONGLONG
#ifndef __strtoll_defined
#define __strtoll_defined
#ifdef __std_strtoll_defined
__NAMESPACE_STD_USING(strtoll)
#elif defined(__CRT_HAVE_strtoll)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strto64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strto32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto32))(__nptr, __endptr, __base); }
#else /* ... */
#include <libc/local/stdlib/strtoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL strtoll)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__strtoll_defined */
#ifndef __strtoull_defined
#define __strtoull_defined
#ifdef __std_strtoull_defined
__NAMESPACE_STD_USING(strtoull)
#elif defined(__CRT_HAVE_strtoull)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 8
#include <libc/local/stdlib/strtou64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou64))(__nptr, __endptr, __base); }
#elif __SIZEOF_LONG__ == 4
#include <libc/local/stdlib/strtou32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtou32))(__nptr, __endptr, __base); }
#else /* ... */
#include <libc/local/stdlib/strtoull.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL strtoull)(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoull))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__strtoull_defined */
#endif /* __LONGLONG */
#ifndef __setproctitle_defined
#define __setproctitle_defined
#ifdef __CRT_HAVE_setproctitle
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
__LIBC __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) void __NOTHROW_NCX(__VLIBCCALL setproctitle)(char const *__format, ...) __CASMNAME_SAME("setproctitle");
#else /* __CRT_HAVE_setproctitle */
#include <linux/prctl.h>
#if ((defined(__CRT_HAVE_prctl) && defined(PR_SET_NAME)) || ((defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self)) && (defined(__CRT_HAVE_pthread_setname_np) || defined(__CRT_HAVE_pthread_set_name_np)))) && (defined(__TASK_COMM_LEN) || defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))))
#include <libc/local/stdlib/setproctitle.h>
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(setproctitle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) void __NOTHROW_NCX(__VLIBCCALL setproctitle)(char const *__format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setproctitle))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define setproctitle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setproctitle))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ((__CRT_HAVE_prctl && PR_SET_NAME) || ((__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self) && (__CRT_HAVE_pthread_setname_np || __CRT_HAVE_pthread_set_name_np))) && (__TASK_COMM_LEN || __CRT_HAVE_vstrdupf || __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free))) */
#undef __setproctitle_defined
#endif /* ((!__CRT_HAVE_prctl || !PR_SET_NAME) && ((!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self) || (!__CRT_HAVE_pthread_setname_np && !__CRT_HAVE_pthread_set_name_np))) || (!__TASK_COMM_LEN && !__CRT_HAVE_vstrdupf && !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free))) */
#endif /* !__CRT_HAVE_setproctitle */
#endif /* !__setproctitle_defined */
#ifdef __CRT_HAVE_strerror
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,xstrerror,(__errno_t __errnum),strerror,(__errnum))
#elif defined(__CRT_HAVE_xstrerror)
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,xstrerror,(__errno_t __errnum),(__errnum))
#else /* ... */
#include <libc/local/string/strerror.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL xstrerror)(__errno_t __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerror))(__errnum); }
#endif /* !... */
#ifdef __CRT_HAVE_strerrorname_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strerrno,(__errno_t __errnum),strerrorname_np,(__errnum))
#elif defined(__CRT_HAVE_strerrno)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strerrno,(__errno_t __errnum),(__errnum))
#else /* ... */
#include <libc/local/string/strerrorname_np.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL strerrno)(__errno_t __errnum) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strerrorname_np))(__errnum); }
#endif /* !... */
#ifdef __CRT_HAVE_sigabbrev_np
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signo' isn't  recognized, `NULL' is returned  instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strsigno,(__signo_t __signo),sigabbrev_np,(__signo))
#elif defined(__CRT_HAVE_signalname)
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signo' isn't  recognized, `NULL' is returned  instead. */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strsigno,(__signo_t __signo),signalname,(__signo))
#elif defined(__CRT_HAVE_strsigno)
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signo' isn't  recognized, `NULL' is returned  instead. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,strsigno,(__signo_t __signo),(__signo))
#else /* ... */
#include <libc/local/string/sigabbrev_np.h>
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signo' isn't  recognized, `NULL' is returned  instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(__LIBCCALL strsigno)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigabbrev_np))(__signo); }
#endif /* !... */
#ifdef __CRT_HAVE_atexit
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,xatexit,(void (__LIBCCALL *__func)(void)),atexit,(__func))
#elif defined(__CRT_HAVE__crt_atexit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,xatexit,(void (__LIBCCALL *__func)(void)),_crt_atexit,(__func))
#elif defined(__CRT_HAVE_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,xatexit,(void (__LIBCCALL *__func)(void)),at_quick_exit,(__func))
#elif defined(__CRT_HAVE__crt_at_quick_exit)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,xatexit,(void (__LIBCCALL *__func)(void)),_crt_at_quick_exit,(__func))
#elif defined(__CRT_HAVE_xatexit)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,xatexit,(void (__LIBCCALL *__func)(void)),(__func))
#endif /* ... */
#if __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,xexit,(int __status),exit,{ __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,xexit,(int __status),exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,xexit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,xexit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,xexit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE_xexit)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,xexit,(int __status),(__status))
#endif /* ... */
#ifdef __CRT_HAVE_basename
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,lbasename,(char const *__filename),basename,(__filename))
#elif defined(__CRT_HAVE___basename)
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,lbasename,(char const *__filename),__basename,(__filename))
#elif defined(__CRT_HAVE_lbasename)
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,lbasename,(char const *__filename),(__filename))
#else /* ... */
#include <libc/local/string/basename.h>
/* >> basename(3)
 * Alternate `basename(3)' function that doesn't modify its `filename' argument
 * For a version that is allowed to modify its argument, but is also allowed to
 * strip trailing slashes, include <libgen.h> instead, which will override this
 * GNU-specific  basename() function (you  can explicitly make  use of this GNU
 * version by doing  `#undef basename', or  writing `(basename)(filename)',  as
 * opposed to  `basename(filename)',  when  both  version  have  been  defined)
 * >> basename("/usr/include///"); // Returns ""
 * >> basename("/usr/include/");   // Returns ""
 * >> basename("/usr/include");    // Returns "include"
 * >> basename("/usr/");           // Returns ""
 * >> basename("/usr");            // Returns "usr"
 * >> basename("/");               // Returns ""
 * >> basename("///");             // Returns ""
 * >> basename("foo/bar/");        // Returns ""
 * >> basename("foo/bar");         // Returns "bar"
 * >> basename("foo/");            // Returns ""
 * >> basename("foo");             // Returns "foo"
 * >> basename(".");               // Returns "."
 * >> basename("..");              // Returns ".."
 * >> basename("");                // Returns ""
 * >> basename(NULL);              // <Undefined behavior> */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL lbasename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(basename))(__filename); }
#endif /* !... */
#ifdef __CRT_HAVE_stack_limit_increase
__CDECLARE_VOID(,__NOTHROW_NCX,stack_limit_increase,(__ULONGPTR_TYPE__ __newlim),(__newlim))
#else /* __CRT_HAVE_stack_limit_increase */
#include <libc/local/libiberty/stack_limit_increase.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(stack_limit_increase, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL stack_limit_increase)(__ULONGPTR_TYPE__ __newlim) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stack_limit_increase))(__newlim); })
#endif /* !__CRT_HAVE_stack_limit_increase */
#ifdef __CRT_HAVE_dos_lbasename
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,dos_lbasename,(char const *__filename),(__filename))
#elif defined(__CRT_HAVE_basename) && defined(_WIN32)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,dos_lbasename,(char const *__filename),basename,(__filename))
#elif defined(__CRT_HAVE___basename) && defined(_WIN32)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,dos_lbasename,(char const *__filename),__basename,(__filename))
#elif defined(__CRT_HAVE_lbasename) && defined(_WIN32)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,dos_lbasename,(char const *__filename),lbasename,(__filename))
#else /* ... */
#include <libc/local/libiberty/dos_lbasename.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dos_lbasename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL dos_lbasename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dos_lbasename))(__filename); })
#endif /* !... */
#ifdef __CRT_HAVE_unix_lbasename
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,unix_lbasename,(char const *__filename),(__filename))
#elif defined(__CRT_HAVE_basename) && !defined(_WIN32)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,unix_lbasename,(char const *__filename),basename,(__filename))
#elif defined(__CRT_HAVE___basename) && !defined(_WIN32)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,unix_lbasename,(char const *__filename),__basename,(__filename))
#elif defined(__CRT_HAVE_lbasename) && !defined(_WIN32)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,unix_lbasename,(char const *__filename),lbasename,(__filename))
#else /* ... */
#include <libc/local/libiberty/unix_lbasename.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(unix_lbasename, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL unix_lbasename)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unix_lbasename))(__filename); })
#endif /* !... */
#ifdef __CRT_HAVE_lrealpath
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,lrealpath,(char const *__path),(__path))
#elif defined(__CRT_HAVE_canonicalize_file_name) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
#include <libc/local/libiberty/lrealpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lrealpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL lrealpath)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrealpath))(__path); })
#endif /* ... */
#ifdef __CRT_HAVE_getpwd
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,getpwd,(void),())
#elif defined(__CRT_HAVE_get_current_dir_name) || defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <libc/local/libiberty/getpwd.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getpwd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL getpwd)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpwd))(); })
#endif /* ... */
#ifdef __CRT_HAVE_errno_max
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,errno_max,(void),())
#else /* __CRT_HAVE_errno_max */
#include <asm/os/errno.h>
#ifdef __ECOUNT
#include <libc/local/libiberty/errno_max.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(errno_max, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL errno_max)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(errno_max))(); })
#endif /* __ECOUNT */
#endif /* !__CRT_HAVE_errno_max */
#ifdef __CRT_HAVE_signo_max
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,signo_max,(void),())
#else /* __CRT_HAVE_signo_max */
#include <asm/os/signal.h>
#ifdef __NSIG
#include <libc/local/libiberty/signo_max.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(signo_max, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL signo_max)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(signo_max))(); })
#endif /* __NSIG */
#endif /* !__CRT_HAVE_signo_max */
#ifdef __CRT_HAVE_strtoerrno
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__errno_t,__NOTHROW_NCX,strtoerrno,(char const *__name),(__name))
#else /* __CRT_HAVE_strtoerrno */
#include <asm/os/errno.h>
#if defined(__CRT_HAVE_errno_max) || defined(__ECOUNT)
#include <libc/local/libiberty/strtoerrno.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strtoerrno, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __errno_t __NOTHROW_NCX(__LIBCCALL strtoerrno)(char const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoerrno))(__name); })
#endif /* __CRT_HAVE_errno_max || __ECOUNT */
#endif /* !__CRT_HAVE_strtoerrno */
#ifdef __CRT_HAVE_unlock_stream
__CDECLARE_VOID(,__NOTHROW_NCX,unlock_stream,(FILE *__fp),(__fp))
#else /* __CRT_HAVE_unlock_stream */
#include <libc/local/libiberty/unlock_stream.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(unlock_stream, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL unlock_stream)(FILE *__fp) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlock_stream))(__fp); })
#endif /* !__CRT_HAVE_unlock_stream */
#ifdef __CRT_HAVE_unlock_std_streams
__CDECLARE_VOID(,__NOTHROW_NCX,unlock_std_streams,(void),())
#else /* __CRT_HAVE_unlock_std_streams */
#include <libc/local/libiberty/unlock_std_streams.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(unlock_std_streams, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL unlock_std_streams)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlock_std_streams))(); })
#endif /* !__CRT_HAVE_unlock_std_streams */
#ifdef __CRT_HAVE_fopen_unlocked
__CDECLARE(,FILE *,__NOTHROW_NCX,fopen_unlocked,(char const *__filename, char const *__mode),(__filename,__mode))
#else /* __CRT_HAVE_fopen_unlocked */
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)
#include <libc/local/libiberty/fopen_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fopen_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL FILE *__NOTHROW_NCX(__LIBCCALL fopen_unlocked)(char const *__filename, char const *__mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fopen_unlocked))(__filename, __mode); })
#endif /* (__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64 */
#endif /* !__CRT_HAVE_fopen_unlocked */
#ifdef __CRT_HAVE_fdopen_unlocked
__CDECLARE(,FILE *,__NOTHROW_NCX,fdopen_unlocked,(__fd_t __fd, char const *__mode),(__fd,__mode))
#elif defined(__CRT_HAVE_fdopen) || defined(__CRT_HAVE__fdopen) || defined(__CRT_HAVE__IO_fdopen)
#include <libc/local/libiberty/fdopen_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fdopen_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL FILE *__NOTHROW_NCX(__LIBCCALL fdopen_unlocked)(__fd_t __fd, char const *__mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdopen_unlocked))(__fd, __mode); })
#endif /* ... */
#ifndef __freopen_unlocked_defined
#define __freopen_unlocked_defined
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_freopen_unlocked) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64_unlocked)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64_unlocked,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen,(__filename,__modes,__stream))
#elif defined(__CRT_HAVE_freopen64)
/* >> freopen(3), freopen64(3), freopen_unlocked(3), freopen64_unlocked(3)
 * Re-open the given  `stream' as a  file-stream for accessing  `filename' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__FILE *,__NOTHROW_RPC,freopen_unlocked,(char const *__restrict __filename, char const *__restrict __modes, __FILE *__restrict __stream),freopen64,(__filename,__modes,__stream))
#else /* ... */
#undef __freopen_unlocked_defined
#endif /* !... */
#endif /* !__freopen_unlocked_defined */
#ifdef __CRT_HAVE_spaces
__CDECLARE(__ATTR_WUNUSED,char const *,__NOTHROW_NCX,spaces,(__STDC_INT_AS_SIZE_T __count),(__count))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/libiberty/spaces.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spaces, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL spaces)(__STDC_INT_AS_SIZE_T __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spaces))(__count); })
#endif /* ... */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,xmalloc_set_program_name,(char const *__progname),(__progname))
__CDECLARE_VOID_OPT(__ATTR_NORETURN,__THROWING,xmalloc_failed,(size_t __num_bytes),(__num_bytes))
#ifdef __CRT_HAVE_xmalloc
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,xmalloc,(size_t __num_bytes),(__num_bytes))
#elif defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/xmalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(xmalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL xmalloc)(size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xmalloc))(__num_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_xrealloc
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,xrealloc,(void *__ptr, size_t __num_bytes),(__ptr,__num_bytes))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed)
#include <libc/local/libiberty/xrealloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(xrealloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL xrealloc)(void *__ptr, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xrealloc))(__ptr, __num_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_xcalloc
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,xcalloc,(size_t __elem_count, size_t __elem_size),(__elem_count,__elem_size))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/xcalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(xcalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL xcalloc)(size_t __elem_count, size_t __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xcalloc))(__elem_count, __elem_size); })
#endif /* ... */
#ifdef __CRT_HAVE_xstrdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,xstrdup,(char const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/xstrdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(xstrdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL xstrdup)(char const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xstrdup))(__string); })
#endif /* ... */
#ifdef __CRT_HAVE_xstrndup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,xstrndup,(char const *__string, size_t __max_chars),(__string,__max_chars))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/xstrndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(xstrndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL xstrndup)(char const *__string, size_t __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xstrndup))(__string, __max_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_xmemdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3)) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,xmemdup,(void const *__src, size_t __src_bytes, size_t __alloc_size),(__src,__src_bytes,__alloc_size))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/xmemdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(xmemdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3)) __ATTR_NONNULL((1)) void *__NOTHROW_NCX(__LIBCCALL xmemdup)(void const *__src, size_t __src_bytes, size_t __alloc_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xmemdup))(__src, __src_bytes, __alloc_size); })
#endif /* ... */
#ifdef __CRT_HAVE_xvasprintf
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,xvasprintf,(char const *__format, __builtin_va_list __args),(__format,__args))
#elif (defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))) && defined(__CRT_HAVE_xmalloc_failed)
#include <libc/local/libiberty/xvasprintf.h>
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
__NAMESPACE_LOCAL_USING_OR_IMPL(xvasprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 0) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL xvasprintf)(char const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xvasprintf))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_xasprintf
__LIBC __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__VLIBCCALL xasprintf)(char const *__restrict __format, ...) __CASMNAME_SAME("xasprintf");
#elif defined(__CRT_HAVE_xvasprintf) || ((defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/xasprintf.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(xasprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_LIBC_PRINTF(1, 2) __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__VLIBCCALL xasprintf)(char const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xasprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define xasprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xasprintf))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifndef __free_defined
#define __free_defined
#ifdef __std_free_defined
__NAMESPACE_STD_USING(free)
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIDECLARE_GCCNCX(,void,__NOTHROW_NCX,free,(void *__mallptr),{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CDECLARE_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __free_defined
#endif /* !... */
#endif /* !__free_defined */
#if defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#define XNEW(T)             ((T *)xmalloc(sizeof(T)))
#define XNEWVEC(T, n)       ((T *)xmalloc(sizeof(T) * (n)))
#define XNEWVAR(T, s)       ((T *)xmalloc(s))
#endif /* __CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed) */
#if defined(__CRT_HAVE_xcalloc) || defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#define XCNEW(T)            ((T *)xcalloc(1, sizeof(T)))
#define XCNEWVEC(T, n)      ((T *)xcalloc(n, sizeof(T)))
#define XCNEWVAR(T, s)      ((T *)xcalloc(1, s))
#endif /* __CRT_HAVE_xcalloc || __CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed) */
#if defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed))
#define XRESIZEVEC(T, p, n) ((T *)xrealloc((void *)(p), sizeof(T) * (n)))
#define XRESIZEVAR(T, p, s) ((T *)xrealloc(p, s))
#endif /* __CRT_HAVE_xrealloc || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_xmalloc_failed) */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#define XDELETE(p)          free((void *)(p))
#define XDELETEVEC(p)       free((void *)(p))
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#define XOBNEW(self, T)    ((T *)obstack_alloc(self, sizeof(T)))
#define XOBFINISH(self, T) ((T)obstack_finish(self))
#ifdef __CRT_HAVE_dupargv
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED,char **,__NOTHROW_NCX,dupargv,(char **___argv),(___argv))
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/dupargv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dupargv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBCCALL dupargv)(char **___argv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dupargv))(___argv); })
#endif /* ... */
#ifdef __CRT_HAVE_freeargv
__CDECLARE_VOID(,__NOTHROW_NCX,freeargv,(char **___argv),(___argv))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/libiberty/freeargv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(freeargv, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL freeargv)(char **___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(freeargv))(___argv); })
#endif /* ... */
#ifdef __CRT_HAVE_countargv
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,countargv,(char *const *___argv),(___argv))
#else /* __CRT_HAVE_countargv */
#include <libc/local/libiberty/countargv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(countargv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL countargv)(char *const *___argv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(countargv))(___argv); })
#endif /* !__CRT_HAVE_countargv */
#ifdef __CRT_HAVE_fdmatch
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,fdmatch,(__fd_t __fd1, __fd_t __fd2),(__fd1,__fd2))
#else /* __CRT_HAVE_fdmatch */
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__fstat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__fstat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_fstat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_fstat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
#include <libc/local/libiberty/fdmatch.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fdmatch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL fdmatch)(__fd_t __fd1, __fd_t __fd2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdmatch))(__fd1, __fd2); })
#endif /* (__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__fstat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__fstat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_fstat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_fstat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */
#endif /* !__CRT_HAVE_fdmatch */
#ifdef __CRT_HAVE_buildargv
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED,char **,__NOTHROW_NCX,buildargv,(char const *__cmdline),(__cmdline))
#elif defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/buildargv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(buildargv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED char **__NOTHROW_NCX(__LIBCCALL buildargv)(char const *__cmdline) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(buildargv))(__cmdline); })
#endif /* ... */
#ifdef __CRT_HAVE_expandargv
/* >> expandargv(3)
 * Expand special `@file' arguments passed on the commandline */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,expandargv,(int *__p_argc, char ***__p_argv),(__p_argc,__p_argv))
#else /* __CRT_HAVE_expandargv */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_mapfile) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_fmapfileat) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))))) || (defined(__O_RDONLY) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fmapfile) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))))) && (defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && defined(__CRT_HAVE_xmalloc_failed))) && (defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed)))
#include <libc/local/libiberty/expandargv.h>
/* >> expandargv(3)
 * Expand special `@file' arguments passed on the commandline */
__NAMESPACE_LOCAL_USING_OR_IMPL(expandargv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL expandargv)(int *__p_argc, char ***__p_argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expandargv))(__p_argc, __p_argv); })
#endif /* (__CRT_HAVE_mapfile || (__AT_FDCWD && (__CRT_HAVE_fmapfileat || (__O_RDONLY && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc)))))) || (__O_RDONLY && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fmapfile || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))))) && (__CRT_HAVE_xrealloc || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && __CRT_HAVE_xmalloc_failed)) && (__CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed)) */
#endif /* !__CRT_HAVE_expandargv */
#ifdef __CRT_HAVE_writeargv
/* @return: 0 : Success
 * @return: 1 : Error */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,writeargv,(char *const *___argv, FILE *__fp),(___argv,__fp))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <libc/local/libiberty/writeargv.h>
/* @return: 0 : Success
 * @return: 1 : Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(writeargv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL writeargv)(char *const *___argv, FILE *__fp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(writeargv))(___argv, __fp); })
#endif /* ... */
#ifdef __CRT_HAVE_concat
__LIBC __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_SENTINEL __ATTR_WUNUSED char *__NOTHROW_NCX(__VLIBCCALL concat)(char const *__first, ...) __CASMNAME_SAME("concat");
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/concat.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(concat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_SENTINEL __ATTR_WUNUSED char *__NOTHROW_NCX(__VLIBCCALL concat)(char const *__first, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(concat))(__first, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define concat(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(concat))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_reconcat
__LIBC __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_SENTINEL __ATTR_WUNUSED char *__NOTHROW_NCX(__VLIBCCALL reconcat)(char *__old_ptr, char const *__first, ...) __CASMNAME_SAME("reconcat");
#elif defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <libc/local/libiberty/reconcat.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(reconcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_SENTINEL __ATTR_WUNUSED char *__NOTHROW_NCX(__VLIBCCALL reconcat)(char *__old_ptr, char const *__first, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reconcat))(__old_ptr, __first, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define reconcat(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reconcat))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_concat_length
__LIBC __ULONGPTR_TYPE__ __NOTHROW_NCX(__VLIBCCALL concat_length)(char const *__first, ...) __CASMNAME_SAME("concat_length");
#else /* __CRT_HAVE_concat_length */
#include <libc/local/libiberty/concat_length.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(concat_length, __FORCELOCAL __ATTR_ARTIFICIAL __ULONGPTR_TYPE__ __NOTHROW_NCX(__VLIBCCALL concat_length)(char const *__first, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(concat_length))(__first, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define concat_length(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(concat_length))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE_concat_length */
#ifdef __CRT_HAVE_concat_copy
__LIBC __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__VLIBCCALL concat_copy)(char *__dst, char const *__first, ...) __CASMNAME_SAME("concat_copy");
#else /* __CRT_HAVE_concat_copy */
#include <libc/local/libiberty/concat_copy.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(concat_copy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__VLIBCCALL concat_copy)(char *__dst, char const *__first, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(concat_copy))(__dst, __first, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define concat_copy(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(concat_copy))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* !__CRT_HAVE_concat_copy */
#ifdef __CRT_HAVE_concat_copy2
__LIBC char *__NOTHROW_NCX(__VLIBCCALL concat_copy2)(char const *__first, ...) __CASMNAME_SAME("concat_copy2");
#endif /* __CRT_HAVE_concat_copy2 */
#ifndef libiberty_concat_ptr
#ifdef __CRT_HAVE_libiberty_concat_ptr
__CSDECLARE(,char *,libiberty_concat_ptr)
#define libiberty_concat_ptr libiberty_concat_ptr
#endif /* __CRT_HAVE_libiberty_concat_ptr */
#endif /* !libiberty_concat_ptr */

#if defined(__alloca) && defined(__libiberty_concat_ptr) && defined(__CRT_HAVE_concat_copy2)
#define ACONCAT(paren_args)                                               \
	(libiberty_concat_ptr = (char *)alloca(concat_length paren_args + 1), \
	 concat_copy2 paren_args)
#endif /* __alloca && __libiberty_concat_ptr && __CRT_HAVE_concat_copy2 */
__CDECLARE_OPT(,long,__NOTHROW_NCX,get_run_time,(void),())
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED,char *,__NOTHROW_NCX,make_relative_prefix,(char const *__a, char const *__b, char const *__c),(__a,__b,__c))
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED,char *,__NOTHROW_NCX,make_relative_prefix_ignore_links,(char const *__a, char const *__b, char const *__c),(__a,__b,__c))
#ifdef __CRT_HAVE_choose_temp_base
/* >> choose_temp_base(3)
 * Create a temporary filename in `choose_tmpdir(3)' by use of `mktemp(3)'
 * The returned string must always be freed, and if no filename could be
 * generated, an empty string is returned. */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED,char *,__NOTHROW_NCX,choose_temp_base,(void),())
#else /* __CRT_HAVE_choose_temp_base */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_choose_tmpdir) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && !defined(_WIN32) && defined(__X_OK) && defined(__W_OK) && defined(__R_OK))) && (defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))) && (defined(__CRT_HAVE_mktemp) || defined(__CRT_HAVE__mktemp) || defined(__CRT_HAVE___mktemp) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))))
#include <libc/local/libiberty/choose_temp_base.h>
/* >> choose_temp_base(3)
 * Create a temporary filename in `choose_tmpdir(3)' by use of `mktemp(3)'
 * The returned string must always be freed, and if no filename could be
 * generated, an empty string is returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(choose_temp_base, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL choose_temp_base)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(choose_temp_base))(); })
#endif /* (__CRT_HAVE_choose_tmpdir || ((__CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat)) && !_WIN32 && __X_OK && __W_OK && __R_OK)) && (__CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed)) && (__CRT_HAVE_mktemp || __CRT_HAVE__mktemp || __CRT_HAVE___mktemp || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64))) */
#endif /* !__CRT_HAVE_choose_temp_base */
#ifdef __CRT_HAVE_choose_tmpdir
/* >> choose_tmpdir(3)
 * Return the path to a suitable temp directory.
 * The returned path is guarantied to be non-NULL, and include a trailing slash. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW_NCX,choose_tmpdir,(void),())
#else /* __CRT_HAVE_choose_tmpdir */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && (defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))) && !defined(_WIN32) && defined(__X_OK) && defined(__W_OK) && defined(__R_OK)
#include <libc/local/libiberty/choose_tmpdir.h>
/* >> choose_tmpdir(3)
 * Return the path to a suitable temp directory.
 * The returned path is guarantied to be non-NULL, and include a trailing slash. */
__NAMESPACE_LOCAL_USING_OR_IMPL(choose_tmpdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL choose_tmpdir)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(choose_tmpdir))(); })
#endif /* (__CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat)) && (__CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed)) && !_WIN32 && __X_OK && __W_OK && __R_OK */
#endif /* !__CRT_HAVE_choose_tmpdir */
#ifdef __CRT_HAVE_make_temp_file_with_prefix
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,make_temp_file_with_prefix,(char const *__prefix, char const *__suffix),(__prefix,__suffix))
#else /* __CRT_HAVE_make_temp_file_with_prefix */
#include <libc/template/stdstreams.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_choose_tmpdir) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && !defined(_WIN32) && defined(__X_OK) && defined(__W_OK) && defined(__R_OK))) && (defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && (defined(__CRT_HAVE_abort) || defined(__CRT_HAVE__ZSt9terminatev) || defined(__CRT_HAVE_terminate) || defined(__CRT_HAVE___chk_fail) || defined(__CRT_HAVE_$Qterminate$A$AYAXXZ) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && defined(__LOCAL_stderr)
#include <libc/local/libiberty/make_temp_file_with_prefix.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(make_temp_file_with_prefix, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL make_temp_file_with_prefix)(char const *__prefix, char const *__suffix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(make_temp_file_with_prefix))(__prefix, __suffix); })
#endif /* (__CRT_HAVE_choose_tmpdir || ((__CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat)) && !_WIN32 && __X_OK && __W_OK && __R_OK)) && (__CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed)) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && (__CRT_HAVE_abort || __CRT_HAVE__ZSt9terminatev || __CRT_HAVE_terminate || __CRT_HAVE___chk_fail || __CRT_HAVE_$Qterminate$A$AYAXXZ || __CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && __LOCAL_stderr */
#endif /* !__CRT_HAVE_make_temp_file_with_prefix */
#ifdef __CRT_HAVE_make_temp_file
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,make_temp_file,(char const *__suffix),(__suffix))
#else /* __CRT_HAVE_make_temp_file */
#include <libc/template/stdstreams.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_make_temp_file_with_prefix) || ((defined(__CRT_HAVE_choose_tmpdir) || ((defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))) && !defined(_WIN32) && defined(__X_OK) && defined(__W_OK) && defined(__R_OK))) && (defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)) && (defined(__CRT_HAVE_abort) || defined(__CRT_HAVE__ZSt9terminatev) || defined(__CRT_HAVE_terminate) || defined(__CRT_HAVE___chk_fail) || defined(__CRT_HAVE_$Qterminate$A$AYAXXZ) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && defined(__LOCAL_stderr))
#include <libc/local/libiberty/make_temp_file.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(make_temp_file, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL make_temp_file)(char const *__suffix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(make_temp_file))(__suffix); })
#endif /* __CRT_HAVE_make_temp_file_with_prefix || ((__CRT_HAVE_choose_tmpdir || ((__CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat)) && !_WIN32 && __X_OK && __W_OK && __R_OK)) && (__CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed)) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) && (__CRT_HAVE_abort || __CRT_HAVE__ZSt9terminatev || __CRT_HAVE_terminate || __CRT_HAVE___chk_fail || __CRT_HAVE_$Qterminate$A$AYAXXZ || __CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && __LOCAL_stderr) */
#endif /* !__CRT_HAVE_make_temp_file */
#ifdef __CRT_HAVE_unlink_if_ordinary
/* >> unlink_if_ordinary(3)
 * Delete a file, but only if it's S_ISREG or S_ISLNK
 * @return:  0: File was deleted
 * @return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
 * @return: -1: Unlink failed (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,unlink_if_ordinary,(char const *__filename),(__filename))
#else /* __CRT_HAVE_unlink_if_ordinary */
#include <bits/os/stat.h>
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_lstat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_lstat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))) && (defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)))
#include <libc/local/libiberty/unlink_if_ordinary.h>
/* >> unlink_if_ordinary(3)
 * Delete a file, but only if it's S_ISREG or S_ISLNK
 * @return:  0: File was deleted
 * @return:  1: File doesn't exist, isn't accessible, or not a "regular" file.
 * @return: -1: Unlink failed (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink_if_ordinary, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL unlink_if_ordinary)(char const *__filename) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink_if_ordinary))(__filename); })
#endif /* ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_lstat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_lstat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64))) && (__CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat)) */
#endif /* !__CRT_HAVE_unlink_if_ordinary */
#ifdef __CRT_HAVE_physmem_total
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,physmem_total,(void),())
#else /* __CRT_HAVE_physmem_total */
#include <asm/crt/confname.h>
#include <asm/pagesize.h>
#if (defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE)) && (defined(__CRT_HAVE_sysconf) || defined(__CRT_HAVE___sysconf)) && defined(_SC_PHYS_PAGES)
#include <libc/local/libiberty/physmem_total.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(physmem_total, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL physmem_total)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(physmem_total))(); })
#endif /* (__CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE) && (__CRT_HAVE_sysconf || __CRT_HAVE___sysconf) && _SC_PHYS_PAGES */
#endif /* !__CRT_HAVE_physmem_total */
#ifdef __CRT_HAVE_physmem_available
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,double,__NOTHROW_NCX,physmem_available,(void),())
#else /* __CRT_HAVE_physmem_available */
#include <asm/crt/confname.h>
#include <asm/pagesize.h>
#if (defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE)) && (defined(__CRT_HAVE_sysconf) || defined(__CRT_HAVE___sysconf)) && defined(_SC_AVPHYS_PAGES)
#include <libc/local/libiberty/physmem_available.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(physmem_available, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED double __NOTHROW_NCX(__LIBCCALL physmem_available)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(physmem_available))(); })
#endif /* (__CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE) && (__CRT_HAVE_sysconf || __CRT_HAVE___sysconf) && _SC_AVPHYS_PAGES */
#endif /* !__CRT_HAVE_physmem_available */
#ifdef __CRT_HAVE_xcrc32
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,xcrc32,(__BYTE_TYPE__ const *__buf, __STDC_INT_AS_SIZE_T __len, __UINT32_TYPE__ __crc),(__buf,__len,__crc))
#else /* __CRT_HAVE_xcrc32 */
#include <libc/local/libiberty/xcrc32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(xcrc32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL xcrc32)(__BYTE_TYPE__ const *__buf, __STDC_INT_AS_SIZE_T __len, __UINT32_TYPE__ __crc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(xcrc32))(__buf, __len, __crc); })
#endif /* !__CRT_HAVE_xcrc32 */
#define _hex_array_size 256
#define _hex_bad        99
extern unsigned char const _hex_value[_hex_array_size];
#define hex_value(c) ((unsigned int)_hex_value[(unsigned char)(c)])
#define hex_p(c)     (hex_value(c) != _hex_bad)
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,hex_init,(void),())


#define PEX_RECORD_TIMES 0x1
#define PEX_USE_PIPES    0x2
#define PEX_SAVE_TEMPS   0x4

#define PEXECUTE_FIRST   1
#define PEXECUTE_LAST    2
#define PEXECUTE_ONE     3 /* (PEXECUTE_FIRST + PEXECUTE_LAST) */
#define PEXECUTE_SEARCH  4
#define PEXECUTE_VERBOSE 8

#define PEX_LAST             0x1
#define PEX_SEARCH           0x2
#define PEX_SUFFIX           0x4
#define PEX_STDERR_TO_STDOUT 0x8
#define PEX_BINARY_INPUT     0x10
#define PEX_BINARY_OUTPUT    0x20
#define PEX_STDERR_TO_PIPE   0x40
#define PEX_BINARY_ERROR     0x80
#define PEX_STDOUT_APPEND    0x100
#define PEX_STDERR_APPEND    0x200
struct pex_time {
	unsigned long user_seconds;
	unsigned long user_microseconds;
	unsigned long system_seconds;
	unsigned long system_microseconds;
};

__CDECLARE_OPT(,char const *,__NOTHROW_NCX,pex_run,(struct pex_obj *__obj, int __flags, char const *__executable, char *const *___argv, char const *__outname, char const *__errname, int *__err),(__obj,__flags,__executable,___argv,__outname,__errname,__err))
__CDECLARE_OPT(,char const *,__NOTHROW_NCX,pex_run_in_environment,(struct pex_obj *__obj, int __flags, char const *__executable, char *const *___argv, char *const *__env, char const *__outname, char const *__errname, int *__err),(__obj,__flags,__executable,___argv,__env,__outname,__errname,__err))
__CDECLARE_OPT(,FILE *,__NOTHROW_NCX,pex_input_file,(struct pex_obj *__obj, int __flags, char const *__in_name),(__obj,__flags,__in_name))
__CDECLARE_OPT(,FILE *,__NOTHROW_NCX,pex_input_pipe,(struct pex_obj *__obj, int __binary),(__obj,__binary))
__CDECLARE_OPT(,FILE *,__NOTHROW_NCX,pex_read_output,(struct pex_obj *__obj, int __binary),(__obj,__binary))
__CDECLARE_OPT(,FILE *,__NOTHROW_NCX,pex_read_err,(struct pex_obj *__obj, int __binary),(__obj,__binary))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pex_get_status,(struct pex_obj *__obj, int __count, int *__vector),(__obj,__count,__vector))
__CDECLARE_OPT(,struct pex_obj *,__NOTHROW_NCX,pex_init,(int __flags, char const *__pname, char const *__tempbase),(__flags,__pname,__tempbase))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pex_get_times,(struct pex_obj *__obj, int __count, struct pex_time *__vector),(__obj,__count,__vector))
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,pex_free,(struct pex_obj *__obj),(__obj))
__CDECLARE_OPT(,char const *,__NOTHROW_NCX,pex_one,(int __flags, char const *__executable, char *const *___argv, char const *__pname, char const *__outname, char const *__errname, int *__status, int *__err),(__flags,__executable,___argv,__pname,__outname,__errname,__status,__err))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pexecute,(char const *__a, char *const *__b, char const *__c, char const *__d, char **__e, char **__f, int __g),(__a,__b,__c,__d,__e,__f,__g))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pwait,(int __a, int *__b, int __c),(__a,__b,__c))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBIBERTY_H */
