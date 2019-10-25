/* HASH CRC-32:0x2490935c */
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
#ifndef _STRINGS_H
#define _STRINGS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
#ifndef __bcopy_defined
#define __bcopy_defined 1
#if __has_builtin(__builtin_bcopy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bcopy)
__FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes) { return __builtin_bcopy(__src, __dst, __num_bytes); }
#elif defined(__CRT_HAVE_bcopy)
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),(__src,__dst,__num_bytes))
#else /* LIBC: bcopy */
#include <local/strings/bcopy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bcopy, __FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bcopy))(__src, __dst, __num_bytes); })
#endif /* bcopy... */
#endif /* !__bcopy_defined */
#ifndef __bzero_defined
#define __bzero_defined 1
#if __has_builtin(__builtin_bzero) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bzero)
__FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { return __builtin_bzero(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#else /* LIBC: bzero */
#include <local/strings/bzero.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzero, __FORCELOCAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); })
#endif /* bzero... */
#endif /* !__bzero_defined */
#ifndef __bcmp_defined
#define __bcmp_defined 1
#if defined(__fast_memcmp_defined)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __num_bytes); }
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_bytes),(__s1,__s2,__num_bytes))
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_bytes),memcmp,(__s1,__s2,__num_bytes))
#else /* LIBC: memcmp */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __num_bytes); }
#endif /* bcmp... */
#endif /* !__bcmp_defined */
#ifndef __index_defined
#define __index_defined 1
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
#if __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return __builtin_index(__haystack, __needle); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return __builtin_index(__haystack, __needle); }
}
#elif defined(__CRT_HAVE_index)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,(__haystack, __needle))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,(__haystack, __needle))
}
#else /* LIBC: index */
#include <local/strings/index.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); }
}
#endif /* index... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
#if __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return __builtin_index(__haystack, __needle); }
#elif defined(__CRT_HAVE_index)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: index */
#include <local/strings/index.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(index, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(index))(__haystack, __needle); })
#endif /* index... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#endif /* !__index_defined */
#ifndef __rindex_defined
#define __rindex_defined 1
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRINGS_H_PROTO)
#if __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return __builtin_rindex(__haystack, __needle); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return __builtin_rindex(__haystack, __needle); }
}
#elif defined(__CRT_HAVE_rindex)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,(__haystack, __needle))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,(__haystack, __needle))
}
#else /* LIBC: rindex */
#include <local/strings/rindex.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); }
}
#endif /* rindex... */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRINGS_H_PROTO */
#if __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return __builtin_rindex(__haystack, __needle); }
#elif defined(__CRT_HAVE_rindex)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#else /* LIBC: rindex */
#include <local/strings/rindex.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(rindex, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rindex))(__haystack, __needle); })
#endif /* rindex... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRINGS_H_PROTO */
#endif /* !__rindex_defined */
#endif /* __USE_MISC || !__USE_XOPEN2K8 */

#ifndef __strcasecmp_defined
#define __strcasecmp_defined 1
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return __builtin_strcasecmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#else /* LIBC: strcasecmp */
#include <local/string/strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); })
#endif /* strcasecmp... */
#endif /* !__strcasecmp_defined */
#ifndef __strncasecmp_defined
#define __strncasecmp_defined 1
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return __builtin_strncasecmp(__s1, __s2, __maxlen); }
#elif defined(__CRT_HAVE_strncasecmp)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#else /* LIBC: strncasecmp */
#include <local/string/strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); })
#endif /* strncasecmp... */
#endif /* !__strncasecmp_defined */

#ifdef __USE_XOPEN2K8
#ifndef __strcasecmp_l_defined
#define __strcasecmp_l_defined 1
#if defined(__CRT_HAVE_strcasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* LIBC: strcasecmp_l */
#include <local/string/strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); })
#endif /* strcasecmp_l... */
#endif /* !__strcasecmp_l_defined */
#ifndef __strncasecmp_l_defined
#define __strncasecmp_l_defined 1
#if defined(__CRT_HAVE_strncasecmp_l)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: strncasecmp_l */
#include <local/string/strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* strncasecmp_l... */
#endif /* !__strncasecmp_l_defined */
#endif /* __USE_XOPEN2K8 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_STRINGS_H */
