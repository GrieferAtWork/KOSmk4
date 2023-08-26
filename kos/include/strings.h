/* HASH CRC-32:0x5c8cb731 */
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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/strings.h) */
/* (#) Portability: DJGPP         (/include/strings.h) */
/* (#) Portability: DragonFly BSD (/include/strings.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/strings.h) */
/* (#) Portability: FreeBSD       (/include/strings.h) */
/* (#) Portability: GNU C Library (/string/strings.h) */
/* (#) Portability: GNU Hurd      (/usr/include/strings.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/strings.h) */
/* (#) Portability: NetBSD        (/include/strings.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/strings.h) */
/* (#) Portability: OpenBSD       (/include/strings.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/strings.h) */
/* (#) Portability: diet libc     (/include/strings.h) */
/* (#) Portability: libc4/5       (/include/strings.h) */
/* (#) Portability: libc6         (/include/strings.h) */
/* (#) Portability: mintlib       (/include/strings.h) */
/* (#) Portability: musl libc     (/include/strings.h) */
/* (#) Portability: uClibc        (/include/strings.h) */
#ifndef _STRINGS_H
#define _STRINGS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus && __USE_STRING_OVERLOADS */
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __USE_NETBSD
#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */
#endif /* __USE_NETBSD */

#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)
#ifndef __bcopy_defined
#define __bcopy_defined
#if __has_builtin(__builtin_bcopy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_bcopy)
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__CEIDECLARE_GCCNCX(__ATTR_INS(1, 3) __ATTR_OUTS(2, 3),void,__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),{ __builtin_bcopy(__src, __dst, __num_bytes); })
#elif defined(__CRT_HAVE_bcopy)
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__CDECLARE_VOID_GCCNCX(__ATTR_INS(1, 3) __ATTR_OUTS(2, 3),__NOTHROW_NCX,bcopy,(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes),(__src,__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bcopy.h>
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
__NAMESPACE_LOCAL_USING_OR_IMPL(bcopy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 3) __ATTR_OUTS(2, 3) void __NOTHROW_NCX(__LIBCCALL bcopy)(void const *__src, void *__dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bcopy))(__src, __dst, __num_bytes); })
#endif /* !... */
#endif /* !__bcopy_defined */
#ifndef __index_defined
#define __index_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),{ return __builtin_index(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_index)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char *__restrict __haystack, int __needle),index,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,index,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/strchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL index)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL index)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__index_defined */
#ifndef __rindex_defined
#define __rindex_defined
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,{ return __builtin_strrchr(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif __has_builtin(__builtin_rindex) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,{ return __builtin_rindex(__haystack, __needle); })
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),{ return __builtin_rindex(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_strrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#elif defined(__CRT_HAVE_rindex)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char const *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),rindex,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,rindex,(char const *__restrict __haystack, int __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#else /* ... */
#include <libc/local/string/strrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_STRING_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL rindex)(char *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char const *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_STRING_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL rindex)(char const *__restrict __haystack, int __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_STRING_H_PROTO */
#endif /* !... */
#endif /* !__rindex_defined */

#ifndef __bcmp_defined
#define __bcmp_defined
#if defined(__fast_bcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_bcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); }
#elif defined(__fast_memcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_memcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_bcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_bcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__fast_memcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_memcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bcmpc)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/memcmpc.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#endif /* !__bcmp_defined */

#ifndef __bzero_defined
#define __bzero_defined
#if defined(__fast_bzero_defined) && defined(__CRT_HAVE_bzero)
__CEIDECLARE_GCCNCX(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE___bzero)
__CEIREDIRECT_GCCNCX(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE_explicit_bzero)
__CEIREDIRECT_GCCNCX(__ATTR_OUTS(1, 2),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined)
__FORCELOCAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CDECLARE_VOID_GCCNCX(__ATTR_OUTS(1, 2),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID_GCCNCX(__ATTR_OUTS(1, 2),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID_GCCNCX(__ATTR_OUTS(1, 2),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzero, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); })
#endif /* !... */
#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
extern "C++" {
#if defined(__fast_bzeroc_defined) && defined(__CRT_HAVE_bzeroc)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#elif defined(__fast_bzeroc_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bzeroc)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzero,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,(__dst,__elem_count,__elem_size))
#else /* ... */
} /* extern "C++" */
#include <libc/local/string/bzeroc.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzero)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#endif /* !... */
} /* extern "C++" */
#endif /* __cplusplus && __USE_STRING_OVERLOADS */
#endif /* !__bzero_defined */

#ifdef __USE_STRING_BWLQ
#ifndef __bcmpb_defined
#define __bcmpb_defined
#if defined(__fast_bcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_bcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))(__s1, __s2, __n_bytes); }
#elif defined(__fast_memcmp_defined) && defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); })
#elif defined(__fast_memcmp_defined)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))(__s1, __s2, __n_bytes); }
#elif defined(__CRT_HAVE_bcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,bcmpb,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL bcmpb)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))(__s1, __s2, __n_bytes); }
#endif /* !... */
#endif /* !__bcmpb_defined */
#ifndef __bcmpw_defined
#define __bcmpw_defined
#if defined(__fast_bcmpw_defined) && defined(__CRT_HAVE_bcmpw)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_memcmpw_defined) && defined(__CRT_HAVE_bcmpw)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_bcmpw_defined) && defined(__CRT_HAVE_memcmpw)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_memcmpw_defined) && defined(__CRT_HAVE_memcmpw)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); })
#elif defined(__fast_bcmpw_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpw))(__s1, __s2, __n_words); }
#elif defined(__fast_memcmpw_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))(__s1, __s2, __n_words); }
#elif defined(__CRT_HAVE_bcmpw)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_memcmpw)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,(__s1,__s2,__n_words))
#else /* ... */
#include <libc/local/string/memcmpw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpw)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))(__s1, __s2, __n_words); }
#endif /* !... */
#endif /* !__bcmpw_defined */
#ifndef __bcmpl_defined
#define __bcmpl_defined
#if defined(__fast_bcmpl_defined) && defined(__CRT_HAVE_bcmpl)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpl_defined) && defined(__CRT_HAVE_bcmpl)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_bcmpl_defined) && defined(__CRT_HAVE_memcmpl)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_memcmpl_defined) && defined(__CRT_HAVE_memcmpl)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); })
#elif defined(__fast_bcmpl_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpl))(__s1, __s2, __n_dwords); }
#elif defined(__fast_memcmpl_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))(__s1, __s2, __n_dwords); }
#elif defined(__CRT_HAVE_bcmpl)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_memcmpl)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,(__s1,__s2,__n_dwords))
#else /* ... */
#include <libc/local/string/memcmpl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpl)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))(__s1, __s2, __n_dwords); }
#endif /* !... */
#endif /* !__bcmpl_defined */
#ifndef __bzerob_defined
#define __bzerob_defined
#if defined(__fast_bzero_defined) && defined(__CRT_HAVE_bzero)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE___bzero)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined) && defined(__CRT_HAVE_explicit_bzero)
__CEIREDIRECT(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),void,__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); })
#elif defined(__fast_bzero_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerob)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))(__dst, __num_bytes); }
#elif defined(__CRT_HAVE_bzero)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)),__NOTHROW_NCX,bzerob,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bzero.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUTS(1, 2) __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL bzerob)(void *__restrict __dst, __SIZE_TYPE__ __num_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero))(__dst, __num_bytes); }
#endif /* !... */
#endif /* !__bzerob_defined */
#ifndef __bzerow_defined
#define __bzerow_defined
#if defined(__fast_bzerow_defined) && defined(__CRT_HAVE_bzerow)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))(__dst, __num_words); })
#elif defined(__fast_bzerow_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerow)(void *__restrict __dst, __SIZE_TYPE__ __num_words) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))(__dst, __num_words); }
#elif defined(__CRT_HAVE_bzerow)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),(__dst,__num_words))
#else /* ... */
#include <libc/local/string/bzerow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzerow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerow)(void *__restrict __dst, __SIZE_TYPE__ __num_words) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerow))(__dst, __num_words); })
#endif /* !... */
#endif /* !__bzerow_defined */
#ifndef __bzerol_defined
#define __bzerol_defined
#if defined(__fast_bzerol_defined) && defined(__CRT_HAVE_bzerol)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))(__dst, __num_dwords); })
#elif defined(__fast_bzerol_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerol)(void *__restrict __dst, __SIZE_TYPE__ __num_dwords) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))(__dst, __num_dwords); }
#elif defined(__CRT_HAVE_bzerol)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),(__dst,__num_dwords))
#else /* ... */
#include <libc/local/string/bzerol.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzerol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzerol)(void *__restrict __dst, __SIZE_TYPE__ __num_dwords) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerol))(__dst, __num_dwords); })
#endif /* !... */
#endif /* !__bzerol_defined */
#ifdef __UINT64_TYPE__
#ifndef __bcmpq_defined
#define __bcmpq_defined
#if defined(__fast_bcmpq_defined) && defined(__CRT_HAVE_bcmpq)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_memcmpq_defined) && defined(__CRT_HAVE_bcmpq)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_bcmpq_defined) && defined(__CRT_HAVE_memcmpq)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),memcmpq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_memcmpq_defined) && defined(__CRT_HAVE_memcmpq)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),memcmpq,{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_qwords); })
#elif defined(__fast_bcmpq_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpq))(__s1, __s2, __n_qwords); }
#elif defined(__fast_memcmpq_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))(__s1, __s2, __n_qwords); }
#elif defined(__CRT_HAVE_bcmpq)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),(__s1,__s2,__n_qwords))
#elif defined(__CRT_HAVE_memcmpq)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),memcmpq,(__s1,__s2,__n_qwords))
#else /* ... */
#include <libc/local/string/memcmpq.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpq)(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq))(__s1, __s2, __n_qwords); }
#endif /* !... */
#endif /* !__bcmpq_defined */
#ifndef __bzeroq_defined
#define __bzeroq_defined
#if defined(__fast_bzeroq_defined) && defined(__CRT_HAVE_bzeroq)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))(__dst, __num_qwords); })
#elif defined(__fast_bzeroq_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroq)(void *__restrict __dst, __SIZE_TYPE__ __num_qwords) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))(__dst, __num_qwords); }
#elif defined(__CRT_HAVE_bzeroq)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),(__dst,__num_qwords))
#else /* ... */
#include <libc/local/string/bzeroq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzeroq, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroq)(void *__restrict __dst, __SIZE_TYPE__ __num_qwords) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroq))(__dst, __num_qwords); })
#endif /* !... */
#endif /* !__bzeroq_defined */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_STRING_BWLQ */

#ifdef __USE_KOS
#ifndef __bcmpc_defined
#define __bcmpc_defined
#if defined(__fast_bcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_bcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__fast_memcmpc_defined) && defined(__CRT_HAVE_bcmpc)
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); })
#elif defined(__fast_memcmpc_defined)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bcmpc)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memcmpc.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL bcmpc)(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc))(__s1, __s2, __elem_count, __elem_size); }
#endif /* !... */
#endif /* !__bcmpc_defined */
#ifndef __bzeroc_defined
#define __bzeroc_defined
#if defined(__fast_bzeroc_defined) && defined(__CRT_HAVE_bzeroc)
__CEIDECLARE(__ATTR_LEAF __ATTR_OUT(1),void,__NOTHROW_NCX,bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),{ (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#elif defined(__fast_bzeroc_defined)
__FORCELOCAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroc)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))(__dst, __elem_count, __elem_size); }
#elif defined(__CRT_HAVE_bzeroc)
__CDECLARE_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__dst,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/bzeroc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(bzeroc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL bzeroc)(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroc))(__dst, __elem_count, __elem_size); })
#endif /* !... */
#endif /* !__bzeroc_defined */
#endif /* __USE_KOS */
#endif /* __USE_MISC || !__USE_XOPEN2K8 */

#ifndef __strcasecmp_defined
#define __strcasecmp_defined
#if __has_builtin(__builtin_strcasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcasecmp)
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),{ return __builtin_strcasecmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcasecmp)
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_stricmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE_strcmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),strcmpi,(__s1,__s2))
#elif defined(__CRT_HAVE___strcasecmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),__strcasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__stricmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_stricmp,(__s1,__s2))
#elif defined(__CRT_HAVE__strcmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp,(char const *__s1, char const *__s2),_strcmpi,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcasecmp)(char const *__s1, char const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__strcasecmp_defined */
#ifndef __strncasecmp_defined
#define __strncasecmp_defined
#if __has_builtin(__builtin_strncasecmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncasecmp)
__CEIDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),{ return __builtin_strncasecmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_strncasecmp)
__CDECLARE_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strnicmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_strncmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),strncmpi,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strnicmp)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__strncmpi)
__CREDIRECT_GCCNCX(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,strncasecmp,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen),_strncmpi,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/string/strncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL strncasecmp)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__strncasecmp_defined */

#ifdef __USE_XOPEN2K8
#ifndef __strcasecmp_l_defined
#define __strcasecmp_l_defined
#ifdef __CRT_HAVE_strcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___strcasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),__strcasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/string/strcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strcasecmp_l)(char const *__s1, char const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#endif /* !__strcasecmp_l_defined */
#ifndef __strncasecmp_l_defined
#define __strncasecmp_l_defined
#ifdef __CRT_HAVE_strncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__strncmpi_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_strncmpi_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___strncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,strncasecmp_l,(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__strncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/string/strncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL strncasecmp_l)(char const *__s1, char const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#endif /* !__strncasecmp_l_defined */
#endif /* __USE_XOPEN2K8 */


#if defined(__USE_KOS) || defined(__USE_GNU) || defined(__USE_BSD)
#ifndef __explicit_bzero_defined
#define __explicit_bzero_defined
#ifdef __CRT_HAVE_bzero
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,explicit_bzero,(void *__dst, size_t __n_bytes),bzero,(__dst,__n_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__CDECLARE_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,explicit_bzero,(void *__dst, size_t __n_bytes),(__dst,__n_bytes))
#elif defined(__CRT_HAVE___bzero)
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,explicit_bzero,(void *__dst, size_t __n_bytes),__bzero,(__dst,__n_bytes))
#else /* ... */
#include <libc/local/strings/explicit_bzero.h>
/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
__NAMESPACE_LOCAL_USING_OR_IMPL(explicit_bzero, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) void __NOTHROW_NCX(__LIBCCALL explicit_bzero)(void *__dst, size_t __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(explicit_bzero))(__dst, __n_bytes); })
#endif /* !... */
#endif /* !__explicit_bzero_defined */
#endif /* __USE_KOS || __USE_GNU || __USE_BSD */
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS) && defined(__HYBRID_PP_VA_OVERLOAD)
/* In C, we can use argument-count overload macros to implement these overloads! */
#ifdef __USE_MISC
#undef __PRIVATE_bcmp_3
#undef __PRIVATE_bcmp_4
#undef __PRIVATE_bzero_2
#undef __PRIVATE_bzero_3
#ifdef __USE_KOS
#define __PRIVATE_bcmp_4  bcmpc
#define __PRIVATE_bzero_3 bzeroc
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_bcmp_4  __libc_bcmpc
#define __PRIVATE_bzero_3 __libc_bzeroc
#endif /* !__USE_KOS */
#define __PRIVATE_bcmp_3  (bcmp)
#define __PRIVATE_bzero_2 (bzero)
#undef bcmp
#undef bzero
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define bcmp(...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bcmp_, (__VA_ARGS__))(__VA_ARGS__)
#define bzero(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define bcmp(args...)  __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bcmp_, (args))(args)
#define bzero(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (args))(args)
#endif /* ... */
#endif /* __USE_MISC */
#endif /* !__cplusplus && __USE_STRING_OVERLOADS && __HYBRID_PP_VA_OVERLOAD */

#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8) || defined(__USE_XOPEN2K8XSI)
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
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* shift_t FFS(INTEGER i):
 *     FindFirstSet
 *     Returns the index (starting at 1 for 0x01) of the first
 *     1-bit in given value, or ZERO(0) if the given value is ZERO(0).
 *     >> assert(!x ||  (x &  (1 << (ffs(x)-1))));    // FFS-bit is set
 *     >> assert(!x || !(x & ((1 << (ffs(x)-1))-1))); // Less significant bits are clear */
#define ffs(i) __hybrid_ffs(i)
#endif /* !__USE_KOS */
#endif /* __USE_MISC || !__USE_XOPEN2K8 || __USE_XOPEN2K8XSI */

#if defined(__USE_NETBSD)
#if __has_builtin(__builtin_popcount) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcount)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),{ return __builtin_popcount(__i); })
#elif defined(__CRT_HAVE_popcount)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),(__i))
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_INT__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcount32,(__i))
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_INT__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcount64,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcountl,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount,(unsigned int __i),popcountll,(__i))
#elif __SIZEOF_INT__ == 4
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount)(unsigned int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))((__UINT32_TYPE__)__i); }
#elif __SIZEOF_INT__ == 8
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount)(unsigned int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))((__UINT64_TYPE__)__i); }
#else /* ... */
#include <libc/local/strings/popcount.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcount, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount)(unsigned int __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount))(__i); })
#endif /* !... */
#if __has_builtin(__builtin_popcountl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcountl)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),{ return __builtin_popcountl(__i); })
#elif defined(__CRT_HAVE_popcountl)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),(__i))
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcount32,(__i))
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcount64,(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_LONG__ == __SIZEOF_INT__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountl,(unsigned long __i),popcountll,(__i))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountl)(unsigned long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))((__UINT32_TYPE__)__i); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountl)(unsigned long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))((__UINT64_TYPE__)__i); }
#else /* ... */
#include <libc/local/strings/popcountl.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcountl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountl)(unsigned long __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcountl))(__i); })
#endif /* !... */
#ifdef __LONGLONG
#if __has_builtin(__builtin_popcountll) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcountll)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),{ return __builtin_popcountll(__i); })
#elif defined(__CRT_HAVE_popcountll)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),(__i))
#elif defined(__CRT_HAVE_popcount32) && __SIZEOF_LONG_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcount32,(__i))
#elif defined(__CRT_HAVE_popcount64) && __SIZEOF_LONG_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcount64,(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcountll,(__ULONGLONG __i),popcountl,(__i))
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountll)(__ULONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))((__UINT32_TYPE__)__i); }
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountll)(__ULONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))((__UINT64_TYPE__)__i); }
#else /* ... */
#include <libc/local/strings/popcountll.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcountll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcountll)(__ULONGLONG __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcountll))(__i); })
#endif /* !... */
#endif /* __LONGLONG */
#if __has_builtin(__builtin_popcount32) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcount32)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),{ return __builtin_popcount32(__i); })
#elif defined(__CRT_HAVE_popcount32)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_INT__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),popcountl,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_LONG_LONG__ == 4
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount32,(__UINT32_TYPE__ __i),popcountll,(__i))
#else /* ... */
#include <libc/local/strings/popcount32.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcount32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount32)(__UINT32_TYPE__ __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount32))(__i); })
#endif /* !... */
#ifdef __UINT64_TYPE__
#if __has_builtin(__builtin_popcount64) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_popcount64)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),{ return __builtin_popcount64(__i); })
#elif defined(__CRT_HAVE_popcount64)
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),(__i))
#elif defined(__CRT_HAVE_popcount) && __SIZEOF_INT__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),popcount,(__i))
#elif defined(__CRT_HAVE_popcountl) && __SIZEOF_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),popcountl,(__i))
#elif defined(__CRT_HAVE_popcountll) && __SIZEOF_LONG_LONG__ == 8
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,unsigned int,__NOTHROW,popcount64,(__UINT64_TYPE__ __i),popcountll,(__i))
#else /* ... */
#include <libc/local/strings/popcount64.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
__NAMESPACE_LOCAL_USING_OR_IMPL(popcount64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED unsigned int __NOTHROW(__LIBCCALL popcount64)(__UINT64_TYPE__ __i) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(popcount64))(__i); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#ifdef __USE_KOS
#include <hybrid/__bit.h>
/* shift_t POPCOUNT(unsigned Integer i):
 *     POPulationCOUNT
 *     Return the number of 1-bits in `i' */
#define popcount(i) __hybrid_popcount(i)
#endif /* !__USE_KOS */
#endif /* __USE_NETBSD */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_STRINGS_H */
