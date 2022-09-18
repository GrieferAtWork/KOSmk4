/* HASH CRC-32:0xd097e450 */
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
#ifndef _LIBC_CORE_STRING_H
#define _LIBC_CORE_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CRT_HAVE_memcpy
#include <hybrid/typecore.h>
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
#include <libc/local/string/memcpy.h>
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_core_memcpy __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#ifdef __CRT_HAVE_memmove
#include <hybrid/typecore.h>
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memmove */
#include <libc/local/string/memmove.h>
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_core_memmove __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove)
#endif /* !__CRT_HAVE_memmove */
#ifdef __CRT_HAVE_memset
#include <hybrid/typecore.h>
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
#include <libc/local/string/memset.h>
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __libc_core_memset __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#ifdef __CRT_HAVE_memcmp
#include <hybrid/typecore.h>
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
#include <hybrid/typecore.h>
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),__gcc_bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __libc_core_memcmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#ifdef __CRT_HAVE_memchr
#include <hybrid/typecore.h>
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memchr */
#include <libc/local/string/memchr.h>
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
#define __libc_core_memchr __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr)
#endif /* !__CRT_HAVE_memchr */
#ifdef __CRT_HAVE_strlen
#include <hybrid/typecore.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
#include <libc/local/string/strlen.h>
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __libc_core_strlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__libc_core_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__libc_core_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__libc_core_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__libc_core_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
#include <libc/local/string/strchr.h>
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
#define __libc_core_strchr __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
#include <libc/local/string/strcmp.h>
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_core_strcmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#if __has_builtin(__builtin_strcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcpy)
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__libc_core_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,{ return __builtin_strcpy(__dst, __src); })
#elif defined(__CRT_HAVE_strcpy)
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__libc_core_strcpy,(char *__restrict __dst, char const *__restrict __src),strcpy,(__dst,__src))
#elif defined(__CRT_HAVE__mbscpy)
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__libc_core_strcpy,(char *__restrict __dst, char const *__restrict __src),_mbscpy,(__dst,__src))
#else /* ... */
#include <libc/local/string/strcpy.h>
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
#define __libc_core_strcpy __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcpy)
#endif /* !... */
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
#include <hybrid/typecore.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__str, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
#include <hybrid/typecore.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___strncnt)
#include <hybrid/typecore.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),__strncnt,(__str,__maxlen))
#else /* ... */
#include <libc/local/string/strnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __libc_core_strnlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#ifdef __CRT_HAVE_memrchr
#include <hybrid/typecore.h>
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrchr */
#include <libc/local/string/memrchr.h>
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
#define __libc_core_memrchr __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr)
#endif /* !__CRT_HAVE_memrchr */
#include <features.h>
#if defined(__CRT_HAVE_memmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#include <hybrid/typecore.h>
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__libc_core_memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem0,(__haystack,__haystacklen,__needle,__needlelen))
#elif defined(__CRT_HAVE_memmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#include <hybrid/typecore.h>
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__libc_core_memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
#else /* ... */
#include <libc/local/string/memmem.h>
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __libc_core_memmem __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem)
#endif /* !... */
#ifdef __CRT_HAVE_mempcpy
#include <hybrid/typecore.h>
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
#include <hybrid/typecore.h>
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempcpy.h>
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
#define __libc_core_mempcpy __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#ifdef __CRT_HAVE_bzero
#include <hybrid/typecore.h>
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__libc_core_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
#include <hybrid/typecore.h>
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__libc_core_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
#include <hybrid/typecore.h>
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__libc_core_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
#include <libc/local/string/bzero.h>
#define __libc_core_bzero __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#ifdef __CRT_HAVE_bzerow
#include <hybrid/typecore.h>
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,__libc_core_bzerow,(void *__restrict __dst, __SIZE_TYPE__ __num_words),bzerow,(__dst,__num_words))
#else /* __CRT_HAVE_bzerow */
#include <libc/local/string/bzerow.h>
#define __libc_core_bzerow __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerow)
#endif /* !__CRT_HAVE_bzerow */
#ifdef __CRT_HAVE_bzerol
#include <hybrid/typecore.h>
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,__libc_core_bzerol,(void *__restrict __dst, __SIZE_TYPE__ __num_dwords),bzerol,(__dst,__num_dwords))
#else /* __CRT_HAVE_bzerol */
#include <libc/local/string/bzerol.h>
#define __libc_core_bzerol __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzerol)
#endif /* !__CRT_HAVE_bzerol */
#ifdef __CRT_HAVE_bcmpw
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),bcmpw,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_memcmpw)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,(__s1,__s2,__n_words))
#else /* ... */
#include <libc/local/string/memcmpw.h>
#define __libc_core_bcmpw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw)
#endif /* !... */
#ifdef __CRT_HAVE_bcmpl
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),bcmpl,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_memcmpl)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,(__s1,__s2,__n_dwords))
#else /* ... */
#include <libc/local/string/memcmpl.h>
#define __libc_core_bcmpl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl)
#endif /* !... */
#ifdef __CRT_HAVE_bzeroq
#include <hybrid/typecore.h>
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,__libc_core_bzeroq,(void *__restrict __dst, __SIZE_TYPE__ __num_qwords),bzeroq,(__dst,__num_qwords))
#else /* __CRT_HAVE_bzeroq */
#include <libc/local/string/bzeroq.h>
#define __libc_core_bzeroq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroq)
#endif /* !__CRT_HAVE_bzeroq */
#ifdef __CRT_HAVE_bcmpq
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),bcmpq,(__s1,__s2,__n_qwords))
#elif defined(__CRT_HAVE_memcmpq)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_qwords),memcmpq,(__s1,__s2,__n_qwords))
#else /* ... */
#include <libc/local/string/memcmpq.h>
#define __libc_core_bcmpq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq)
#endif /* !... */
#ifdef __CRT_HAVE_bzeroc
#include <hybrid/typecore.h>
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,__libc_core_bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,(__dst,__elem_count,__elem_size))
#else /* __CRT_HAVE_bzeroc */
#include <libc/local/string/bzeroc.h>
#define __libc_core_bzeroc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(bzeroc)
#endif /* !__CRT_HAVE_bzeroc */
#ifdef __CRT_HAVE_bcmpc
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
#include <libc/local/string/memcmpc.h>
#define __libc_core_bcmpc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc)
#endif /* !... */
#ifdef __CRT_HAVE_bcmp
#include <hybrid/typecore.h>
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
#include <hybrid/typecore.h>
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_core_bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
#include <libc/local/string/memcmp.h>
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
#define __libc_core_bcmp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#ifdef __CRT_HAVE_memcpyw
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcpy) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
#define __libc_core_memcpyw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw)
#endif /* !... */
#ifdef __CRT_HAVE_mempcpyw
#include <hybrid/typecore.h>
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),mempcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempcpy) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmempcpy,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempcpyw.h>
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
#define __libc_core_mempcpyw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw)
#endif /* !... */
#ifdef __CRT_HAVE_memcpyl
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),memcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcpy) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmemcpy,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memcpyl.h>
/* Copy memory between non-overlapping memory blocks. */
#define __libc_core_memcpyl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl)
#endif /* !... */
#ifdef __CRT_HAVE_mempcpyl
#include <hybrid/typecore.h>
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempcpy) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmempcpy,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempcpyl.h>
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_core_mempcpyl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl)
#endif /* !... */
#ifdef __CRT_HAVE_memmovew
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memmovew.h>
/* Move memory between potentially overlapping memory blocks. */
#define __libc_core_memmovew __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew)
#endif /* !... */
#ifdef __CRT_HAVE_mempmovew
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempmovew.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
#define __libc_core_mempmovew __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew)
#endif /* !... */
#ifdef __CRT_HAVE_memmovel
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memmovel.h>
/* Move memory between potentially overlapping memory blocks. */
#define __libc_core_memmovel __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel)
#endif /* !... */
#ifdef __CRT_HAVE_mempmovel
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempmovel.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_core_mempmovel __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel)
#endif /* !... */
#ifdef __CRT_HAVE_memmoveupw
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmoveupw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memmoveupw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
#define __libc_core_memmoveupw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupw)
#endif /* !... */
#ifdef __CRT_HAVE_memmovedownw
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovedownw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/memmovedownw.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
#define __libc_core_memmovedownw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownw)
#endif /* !... */
#ifdef __CRT_HAVE_mempmoveupw
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmoveupw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempmoveupw.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
#define __libc_core_mempmoveupw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupw)
#endif /* !... */
#ifdef __CRT_HAVE_mempmovedownw
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovedownw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
#include <libc/local/string/mempmovedownw.h>
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
#define __libc_core_mempmovedownw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownw)
#endif /* !... */
#ifdef __CRT_HAVE_memmoveupl
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmoveupl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memmoveupl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
#define __libc_core_memmoveupl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupl)
#endif /* !... */
#ifdef __CRT_HAVE_memmovedownl
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovedownl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/memmovedownl.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
#define __libc_core_memmovedownl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownl)
#endif /* !... */
#ifdef __CRT_HAVE_mempmoveupl
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmoveupl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempmoveupl.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
#define __libc_core_mempmoveupl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupl)
#endif /* !... */
#ifdef __CRT_HAVE_mempmovedownl
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovedownl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
#include <libc/local/string/mempmovedownl.h>
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
#define __libc_core_mempmovedownl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownl)
#endif /* !... */
#ifdef __CRT_HAVE_memsetw
#include <hybrid/typecore.h>
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemset) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Fill memory with a given word */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemset,(__dst,__word,__n_words))
#else /* ... */
#include <libc/local/string/memsetw.h>
/* Fill memory with a given word */
#define __libc_core_memsetw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw)
#endif /* !... */
#ifdef __CRT_HAVE_mempsetw
#include <hybrid/typecore.h>
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),mempsetw,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmempset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempset) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmempset,(__dst,__word,__n_words))
#else /* ... */
#include <libc/local/string/mempsetw.h>
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
#define __libc_core_mempsetw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw)
#endif /* !... */
#ifdef __CRT_HAVE_memsetl
#include <hybrid/typecore.h>
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemset) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Fill memory with a given dword */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemset,(__dst,__dword,__n_dwords))
#else /* ... */
#include <libc/local/string/memsetl.h>
/* Fill memory with a given dword */
#define __libc_core_memsetl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl)
#endif /* !... */
#ifdef __CRT_HAVE_mempsetl
#include <hybrid/typecore.h>
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempset) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,(__dst,__dword,__n_dwords))
#else /* ... */
#include <libc/local/string/mempsetl.h>
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_core_mempsetl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl)
#endif /* !... */
#ifdef __CRT_HAVE_memcmpw
#include <hybrid/typecore.h>
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),wmemcmp,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Compare memory buffers and return the difference of the first non-matching word */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,__libc_core_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),DOS$wmemcmp,(__s1,__s2,__n_words))
#else /* ... */
#include <libc/local/string/memcmpw.h>
/* Compare memory buffers and return the difference of the first non-matching word */
#define __libc_core_memcmpw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw)
#endif /* !... */
#ifdef __CRT_HAVE_memcmpl
#include <hybrid/typecore.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),wmemcmp,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,__libc_core_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),KOS$wmemcmp,(__s1,__s2,__n_dwords))
#else /* ... */
#include <libc/local/string/memcmpl.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __libc_core_memcmpl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl)
#endif /* !... */
#ifdef __CRT_HAVE_memchrw
#include <hybrid/typecore.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memchrw,(__haystack,__needle,__n_words))
#elif defined(__CRT_HAVE_wmemchr) && __SIZEOF_WCHAR_T__ == 2
#include <hybrid/typecore.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__needle,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemchr) && defined(__LIBCCALL_IS_LIBDCALL)
#include <hybrid/typecore.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),DOS$wmemchr,(__haystack,__needle,__n_words))
#else /* ... */
#include <libc/local/string/memchrw.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_core_memchrw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw)
#endif /* !... */
#ifdef __CRT_HAVE_memchrl
#include <hybrid/typecore.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memchrl,(__haystack,__needle,__n_dwords))
#elif defined(__CRT_HAVE_wmemchr) && __SIZEOF_WCHAR_T__ == 4
#include <hybrid/typecore.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__needle,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemchr) && defined(__LIBCCALL_IS_LIBKCALL)
#include <hybrid/typecore.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__libc_core_memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),KOS$wmemchr,(__haystack,__needle,__n_dwords))
#else /* ... */
#include <libc/local/string/memchrl.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_core_memchrl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl)
#endif /* !... */
#ifdef __CRT_HAVE_memrchrw
#include <hybrid/typecore.h>
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrchrw,(__haystack,__needle,__n_words))
#else /* __CRT_HAVE_memrchrw */
#include <libc/local/string/memrchrw.h>
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
#define __libc_core_memrchrw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw)
#endif /* !__CRT_HAVE_memrchrw */
#ifdef __CRT_HAVE_memrchrl
#include <hybrid/typecore.h>
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrchrl,(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memrchrl */
#include <libc/local/string/memrchrl.h>
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
#define __libc_core_memrchrl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl)
#endif /* !__CRT_HAVE_memrchrl */
#ifdef __CRT_HAVE_memendw
#include <hybrid/typecore.h>
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendw,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memendw */
#include <libc/local/string/memendw.h>
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memendw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw)
#endif /* !__CRT_HAVE_memendw */
#ifdef __CRT_HAVE_memendl
#include <hybrid/typecore.h>
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memendl,(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memendl */
#include <libc/local/string/memendl.h>
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memendl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl)
#endif /* !__CRT_HAVE_memendl */
#ifdef __CRT_HAVE_memrendw
#include <hybrid/typecore.h>
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_core_memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__needle,__n_words))
#else /* __CRT_HAVE_memrendw */
#include <libc/local/string/memrendw.h>
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memrendw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw)
#endif /* !__CRT_HAVE_memrendw */
#ifdef __CRT_HAVE_memrendl
#include <hybrid/typecore.h>
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_core_memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __needle, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__needle,__n_dwords))
#else /* __CRT_HAVE_memrendl */
#include <libc/local/string/memrendl.h>
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memrendl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl)
#endif /* !__CRT_HAVE_memrendl */
#ifdef __CRT_HAVE_memcpyq
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),memcpyq,(__dst,__src,__n_qwords))
#else /* __CRT_HAVE_memcpyq */
#include <libc/local/string/memcpyq.h>
/* Copy memory between non-overlapping memory blocks. */
#define __libc_core_memcpyq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyq)
#endif /* !__CRT_HAVE_memcpyq */
#ifdef __CRT_HAVE_mempcpyq
#include <hybrid/typecore.h>
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_mempcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempcpyq,(__dst,__src,__n_qwords))
#else /* __CRT_HAVE_mempcpyq */
#include <libc/local/string/mempcpyq.h>
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
#define __libc_core_mempcpyq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyq)
#endif /* !__CRT_HAVE_mempcpyq */
#ifdef __CRT_HAVE_memmoveq
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* __CRT_HAVE_memmoveq */
#include <libc/local/string/memmoveq.h>
/* Move memory between potentially overlapping memory blocks. */
#define __libc_core_memmoveq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveq)
#endif /* !__CRT_HAVE_memmoveq */
#ifdef __CRT_HAVE_mempmoveq
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* __CRT_HAVE_mempmoveq */
#include <libc/local/string/mempmoveq.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
#define __libc_core_mempmoveq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveq)
#endif /* !__CRT_HAVE_mempmoveq */
#ifdef __CRT_HAVE_memmoveupq
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveupq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/memmoveupq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
#define __libc_core_memmoveupq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupq)
#endif /* !... */
#ifdef __CRT_HAVE_memmovedownq
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmovedownq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/memmovedownq.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
#define __libc_core_memmovedownq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownq)
#endif /* !... */
#ifdef __CRT_HAVE_mempmoveupq
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveupq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmoveupq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/mempmoveupq.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
#define __libc_core_mempmoveupq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupq)
#endif /* !... */
#ifdef __CRT_HAVE_mempmovedownq
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmovedownq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
#include <hybrid/typecore.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* ... */
#include <libc/local/string/mempmovedownq.h>
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
#define __libc_core_mempmovedownq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownq)
#endif /* !... */
#ifdef __CRT_HAVE_memsetq
#include <hybrid/typecore.h>
/* Fill memory with a given qword */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memsetq,(__dst,__qword,__n_qwords))
#else /* __CRT_HAVE_memsetq */
#include <libc/local/string/memsetq.h>
/* Fill memory with a given qword */
#define __libc_core_memsetq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetq)
#endif /* !__CRT_HAVE_memsetq */
#ifdef __CRT_HAVE_mempsetq
#include <hybrid/typecore.h>
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_mempsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),mempsetq,(__dst,__qword,__n_qwords))
#else /* __CRT_HAVE_mempsetq */
#include <libc/local/string/mempsetq.h>
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
#define __libc_core_mempsetq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetq)
#endif /* !__CRT_HAVE_mempsetq */
#ifdef __CRT_HAVE_memcmpq
#include <hybrid/typecore.h>
/* Compare memory buffers and return the difference of the first non-matching qword */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_memcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpq,(__s1,__s2,__n_dwords))
#else /* __CRT_HAVE_memcmpq */
#include <libc/local/string/memcmpq.h>
/* Compare memory buffers and return the difference of the first non-matching qword */
#define __libc_core_memcmpq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq)
#endif /* !__CRT_HAVE_memcmpq */
#ifdef __CRT_HAVE_memchrq
#include <hybrid/typecore.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memchrq,(__haystack,__needle,__n_qwords))
#else /* __CRT_HAVE_memchrq */
#include <libc/local/string/memchrq.h>
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_core_memchrq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq)
#endif /* !__CRT_HAVE_memchrq */
#ifdef __CRT_HAVE_memrchrq
#include <hybrid/typecore.h>
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrchrq,(__haystack,__needle,__n_qwords))
#else /* __CRT_HAVE_memrchrq */
#include <libc/local/string/memrchrq.h>
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
#define __libc_core_memrchrq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq)
#endif /* !__CRT_HAVE_memrchrq */
#ifdef __CRT_HAVE_memendq
#include <hybrid/typecore.h>
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memendq */
#include <libc/local/string/memendq.h>
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memendq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq)
#endif /* !__CRT_HAVE_memendq */
#ifdef __CRT_HAVE_memrendq
#include <hybrid/typecore.h>
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_core_memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrendq,(__haystack,__needle,__n_qwords))
#else /* __CRT_HAVE_memrendq */
#include <libc/local/string/memrendq.h>
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memrendq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq)
#endif /* !__CRT_HAVE_memrendq */
#ifdef __CRT_HAVE_memlenq
#include <hybrid/typecore.h>
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_memlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memlenq,(__haystack,__needle,__n_qwords))
#else /* __CRT_HAVE_memlenq */
#include <libc/local/string/memlenq.h>
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
#define __libc_core_memlenq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenq)
#endif /* !__CRT_HAVE_memlenq */
#ifdef __CRT_HAVE_memrlenq
#include <hybrid/typecore.h>
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_memrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle, __SIZE_TYPE__ __n_qwords),memrlenq,(__haystack,__needle,__n_qwords))
#else /* __CRT_HAVE_memrlenq */
#include <libc/local/string/memrlenq.h>
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
#define __libc_core_memrlenq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenq)
#endif /* !__CRT_HAVE_memrlenq */
#ifdef __CRT_HAVE_rawmemlenq
#include <hybrid/typecore.h>
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_rawmemlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemlenq,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemlenq */
#include <libc/local/string/rawmemlenq.h>
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
#define __libc_core_rawmemlenq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenq)
#endif /* !__CRT_HAVE_rawmemlenq */
#ifdef __CRT_HAVE_rawmemrlenq
#include <hybrid/typecore.h>
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_rawmemrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __needle),rawmemrlenq,(__haystack,__needle))
#else /* __CRT_HAVE_rawmemrlenq */
#include <libc/local/string/rawmemrlenq.h>
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
#define __libc_core_rawmemrlenq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenq)
#endif /* !__CRT_HAVE_rawmemrlenq */
#ifdef __CRT_HAVE_memmoveup
#include <hybrid/typecore.h>
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmoveup,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
#include <hybrid/typecore.h>
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memmoveup.h>
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
#define __libc_core_memmoveup __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveup)
#endif /* !... */
#ifdef __CRT_HAVE_memmovedown
#include <hybrid/typecore.h>
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
#include <hybrid/typecore.h>
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/memmovedown.h>
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
#define __libc_core_memmovedown __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedown)
#endif /* !... */
#ifdef __CRT_HAVE_memcmpc
#include <hybrid/typecore.h>
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__libc_core_memcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcmpc */
#include <libc/local/string/memcmpc.h>
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
#define __libc_core_memcmpc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpc)
#endif /* !__CRT_HAVE_memcmpc */
#ifdef __CRT_HAVE_memcpyc
#include <hybrid/typecore.h>
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
#include <libc/local/string/memcpyc.h>
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_core_memcpyc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#ifdef __CRT_HAVE_mempcpyc
#include <hybrid/typecore.h>
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
#include <libc/local/string/mempcpyc.h>
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
#define __libc_core_mempcpyc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__CRT_HAVE_mempcpyc */
#ifdef __CRT_HAVE_memmovec
#include <hybrid/typecore.h>
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_memmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovec,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovec */
#include <libc/local/string/memmovec.h>
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
#define __libc_core_memmovec __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovec)
#endif /* !__CRT_HAVE_memmovec */
#ifdef __CRT_HAVE_mempmovec
#include <hybrid/typecore.h>
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_mempmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovec,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempmovec */
#include <libc/local/string/mempmovec.h>
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
#define __libc_core_mempmovec __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovec)
#endif /* !__CRT_HAVE_mempmovec */
#ifdef __CRT_HAVE_memmoveupc
#include <hybrid/typecore.h>
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_memmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmoveupc */
#include <libc/local/string/memmoveupc.h>
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __libc_core_memmoveupc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveupc)
#endif /* !__CRT_HAVE_memmoveupc */
#ifdef __CRT_HAVE_mempmoveupc
#include <hybrid/typecore.h>
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_mempmoveupc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmoveupc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempmoveupc */
#include <libc/local/string/mempmoveupc.h>
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
#define __libc_core_mempmoveupc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveupc)
#endif /* !__CRT_HAVE_mempmoveupc */
#ifdef __CRT_HAVE_memmovedownc
#include <hybrid/typecore.h>
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
#include <libc/local/string/memmovedownc.h>
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __libc_core_memmovedownc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__CRT_HAVE_memmovedownc */
#ifdef __CRT_HAVE_mempmovedownc
#include <hybrid/typecore.h>
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__libc_core_mempmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempmovedownc */
#include <libc/local/string/mempmovedownc.h>
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
#define __libc_core_mempmovedownc __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedownc)
#endif /* !__CRT_HAVE_mempmovedownc */
#ifdef __CRT_HAVE_strend
/* >> strend(3)
 * Same as `str + strlen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__libc_core_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
#include <libc/local/string/strend.h>
/* >> strend(3)
 * Same as `str + strlen(str)' */
#define __libc_core_strend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#ifdef __CRT_HAVE_strnend
#include <hybrid/typecore.h>
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__libc_core_strnend,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnend,(__str,__maxlen))
#else /* __CRT_HAVE_strnend */
#include <libc/local/string/strnend.h>
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
#define __libc_core_strnend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend)
#endif /* !__CRT_HAVE_strnend */
#ifdef __CRT_HAVE_mempset
#include <hybrid/typecore.h>
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_mempset */
#include <libc/local/string/mempset.h>
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
#define __libc_core_mempset __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset)
#endif /* !__CRT_HAVE_mempset */
#ifdef __CRT_HAVE_mempmove
#include <hybrid/typecore.h>
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_mempmove */
#include <libc/local/string/mempmove.h>
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
#define __libc_core_mempmove __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove)
#endif /* !__CRT_HAVE_mempmove */
#ifdef __CRT_HAVE_mempmoveup
#include <hybrid/typecore.h>
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmoveup,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempmove)
#include <hybrid/typecore.h>
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_mempmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmoveup.h>
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
#define __libc_core_mempmoveup __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveup)
#endif /* !... */
#ifdef __CRT_HAVE_mempmovedown
#include <hybrid/typecore.h>
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempmove)
#include <hybrid/typecore.h>
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_core_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* ... */
#include <libc/local/string/mempmovedown.h>
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
#define __libc_core_mempmovedown __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovedown)
#endif /* !... */
#ifdef __CRT_HAVE_memend
#include <hybrid/typecore.h>
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memend */
#include <libc/local/string/memend.h>
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend)
#endif /* !__CRT_HAVE_memend */
#ifdef __CRT_HAVE_memrend
#include <hybrid/typecore.h>
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrend */
#include <libc/local/string/memrend.h>
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
#define __libc_core_memrend __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend)
#endif /* !__CRT_HAVE_memrend */
#ifdef __CRT_HAVE_memlen
#include <hybrid/typecore.h>
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_memlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memlen,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memlen */
#include <libc/local/string/memlen.h>
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
#define __libc_core_memlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen)
#endif /* !__CRT_HAVE_memlen */
#ifdef __CRT_HAVE_memrlen
#include <hybrid/typecore.h>
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_memrlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrlen,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrlen */
#include <libc/local/string/memrlen.h>
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
#define __libc_core_memrlen __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen)
#endif /* !__CRT_HAVE_memrlen */
#if defined(__CRT_HAVE_memrmem0) && defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#include <hybrid/typecore.h>
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__libc_core_memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem0,(__haystack,__haystacklen,__needle,__needlelen))
#elif defined(__CRT_HAVE_memrmem) && !defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL)
#include <hybrid/typecore.h>
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__libc_core_memrmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memrmem,(__haystack,__haystacklen,__needle,__needlelen))
#else /* ... */
#include <libc/local/string/memrmem.h>
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __libc_core_memrmem __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrmem)
#endif /* !... */
#ifdef __CRT_HAVE_mempatw
#include <hybrid/typecore.h>
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_mempatw,(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),mempatw,(__dst,__pattern,__n_bytes))
#else /* __CRT_HAVE_mempatw */
#include <libc/local/string/mempatw.h>
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
#define __libc_core_mempatw __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatw)
#endif /* !__CRT_HAVE_mempatw */
#ifdef __CRT_HAVE_mempatl
#include <hybrid/typecore.h>
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_mempatl,(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),mempatl,(__dst,__pattern,__n_bytes))
#else /* __CRT_HAVE_mempatl */
#include <libc/local/string/mempatl.h>
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
#define __libc_core_mempatl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatl)
#endif /* !__CRT_HAVE_mempatl */
#ifdef __CRT_HAVE_mempatq
#include <hybrid/typecore.h>
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_core_mempatq,(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),mempatq,(__dst,__pattern,__n_bytes))
#else /* __CRT_HAVE_mempatq */
#include <libc/local/string/mempatq.h>
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
#define __libc_core_mempatq __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatq)
#endif /* !__CRT_HAVE_mempatq */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_STRING_H */
