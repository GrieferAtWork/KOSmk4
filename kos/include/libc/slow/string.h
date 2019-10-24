/* HASH CRC-32:0x58fafe2b */
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
#ifndef _LIBC_SLOW_STRING_H
#define _LIBC_SLOW_STRING_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_slow_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_slow_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#if defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_slow_memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* LIBC: memmove */
#include <local/string/memmove.h>
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_slow_memmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmove))
#endif /* memmove... */
#if defined(__CRT_HAVE_memset)
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __libc_slow_memset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))
#endif /* memset... */
#if defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcmp */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __libc_slow_memcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))
#endif /* memcmp... */
#if defined(__CRT_HAVE_memchr)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* LIBC: memchr */
#include <local/string/memchr.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))
#endif /* memchr... */
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_slow_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL __libc_slow_strchr)(char const *__restrict __haystack, int __needle) { return __builtin_strchr(__haystack, __needle); }
#elif defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__libc_slow_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#else /* LIBC: strchr */
#include <local/string/strchr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_strchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))
#endif /* strchr... */
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL __libc_slow_strcmp)(char const *__s1, char const *__s2) { return __builtin_strcmp(__s1, __s2); }
#elif defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__libc_slow_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* LIBC: strcmp */
#include <local/string/strcmp.h>
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_slow_strcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcmp))
#endif /* strcmp... */
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__FORCELOCAL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __libc_slow_strnlen)(char const *__restrict __string, __SIZE_TYPE__ __maxlen) { return __builtin_strnlen(__string, __maxlen); }
#elif defined(__CRT_HAVE_strnlen)
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,(__string,__maxlen))
#else /* LIBC: strnlen */
#include <local/string/strnlen.h>
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_slow_strnlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnlen))
#endif /* strnlen... */
#if defined(__CRT_HAVE_memrchr)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
#else /* LIBC: memrchr */
#include <local/string/memrchr.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchr))
#endif /* memrchr... */
#if defined(__CRT_HAVE_memmem)
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 3)),void *,__NOTHROW_NCX,__libc_slow_memmem,(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen),memmem,(__haystack,__haystacklen,__needle,__needlelen))
#else /* LIBC: memmem */
#include <local/string/memmem.h>
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally. */
#define __libc_slow_memmem (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmem))
#endif /* memmem... */
#if defined(__CRT_HAVE_mempcpy)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_slow_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_slow_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* LIBC: mempcpy */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
#define __libc_slow_mempcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))
#endif /* mempcpy... */
#if defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#else /* LIBC: memcpyw */
#include <local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
#define __libc_slow_memcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))
#endif /* memcpyw... */
#if defined(__CRT_HAVE_mempcpyw)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),mempcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#else /* LIBC: mempcpyw */
#include <local/string/mempcpyw.h>
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
#define __libc_slow_mempcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))
#endif /* mempcpyw... */
#if defined(__CRT_HAVE_memcpyl)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),memcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#else /* LIBC: memcpyl */
#include <local/string/memcpyl.h>
/* Copy memory between non-overlapping memory blocks. */
#define __libc_slow_memcpyl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))
#endif /* memcpyl... */
#if defined(__CRT_HAVE_mempcpyl)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmempcpy,(__dst,__src,__n_dwords))
#else /* LIBC: mempcpyl */
#include <local/string/mempcpyl.h>
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_slow_mempcpyl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))
#endif /* mempcpyl... */
#if defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 2)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#else /* LIBC: memmovew */
#include <local/string/memmovew.h>
/* Move memory between potentially overlapping memory blocks. */
#define __libc_slow_memmovew (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))
#endif /* memmovew... */
#if defined(__CRT_HAVE_mempmovew)
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempmovew,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#else /* LIBC: mempmovew */
#include <local/string/mempmovew.h>
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
#define __libc_slow_mempmovew (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))
#endif /* mempmovew... */
#if defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && (__SIZEOF_WCHAR_T__ == 4)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#else /* LIBC: memmovel */
#include <local/string/memmovel.h>
/* Move memory between potentially overlapping memory blocks. */
#define __libc_slow_memmovel (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))
#endif /* memmovel... */
#if defined(__CRT_HAVE_mempmovel)
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempmovel,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#else /* LIBC: mempmovel */
#include <local/string/mempmovel.h>
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_slow_mempmovel (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))
#endif /* mempmovel... */
#if defined(__CRT_HAVE_memsetw)
/* Fill memory with a given word */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#else /* LIBC: memsetw */
#include <local/string/memsetw.h>
/* Fill memory with a given word */
#define __libc_slow_memsetw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))
#endif /* memsetw... */
#if defined(__CRT_HAVE_mempsetw)
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),mempsetw,(__dst,__word,__n_words))
#else /* LIBC: mempsetw */
#include <local/string/mempsetw.h>
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
#define __libc_slow_mempsetw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))
#endif /* mempsetw... */
#if defined(__CRT_HAVE_memsetl)
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memsetl,(__dst,__dword,__n_dwords))
#else /* LIBC: memsetl */
#include <local/string/memsetl.h>
/* Fill memory with a given dword */
#define __libc_slow_memsetl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))
#endif /* memsetl... */
#if defined(__CRT_HAVE_mempsetl)
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#else /* LIBC: mempsetl */
#include <local/string/mempsetl.h>
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_slow_mempsetl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))
#endif /* mempsetl... */
#if defined(__CRT_HAVE_memcmpw)
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,__libc_slow_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Compare memory buffers and return the difference of the first non-matching word */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT16_TYPE__,__NOTHROW_NCX,__libc_slow_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),wmemcmp,(__s1,__s2,__n_words))
#else /* LIBC: memcmpw */
#include <local/string/memcmpw.h>
/* Compare memory buffers and return the difference of the first non-matching word */
#define __libc_slow_memcmpw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))
#endif /* memcmpw... */
#if defined(__CRT_HAVE_memcmpl)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,__libc_slow_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_wmemcmp) && (__SIZEOF_WCHAR_T__ == 4)
/* Compare memory buffers and return the difference of the first non-matching dword */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT32_TYPE__,__NOTHROW_NCX,__libc_slow_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),wmemcmp,(__s1,__s2,__n_dwords))
#else /* LIBC: memcmpl */
#include <local/string/memcmpl.h>
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __libc_slow_memcmpl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))
#endif /* memcmpl... */
#if defined(__CRT_HAVE_memchrw)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memchrw,(__haystack,__word,__n_words))
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 2)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemchr,(__haystack,__word,__n_words))
#else /* LIBC: memchrw */
#include <local/string/memchrw.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memchrw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))
#endif /* memchrw... */
#if defined(__CRT_HAVE_memchrl)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memchrl,(__haystack,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemchr) && (__SIZEOF_WCHAR_T__ == 4)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemchr,(__haystack,__dword,__n_dwords))
#else /* LIBC: memchrl */
#include <local/string/memchrl.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memchrl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))
#endif /* memchrl... */
#if defined(__CRT_HAVE_memrchrw)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memrchrw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrchrw,(__haystack,__word,__n_words))
#else /* LIBC: memrchrw */
#include <local/string/memrchrw.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrchrw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrw))
#endif /* memrchrw... */
#if defined(__CRT_HAVE_memrchrl)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memrchrl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrchrl,(__haystack,__dword,__n_dwords))
#else /* LIBC: memrchrl */
#include <local/string/memrchrl.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrchrl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrl))
#endif /* memrchrl... */
#if defined(__CRT_HAVE_memendw)
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),memendw,(__haystack,__word,__n_bytes))
#else /* LIBC: memendw */
#include <local/string/memendw.h>
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memendw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))
#endif /* memendw... */
#if defined(__CRT_HAVE_memendl)
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_bytes),memendl,(__haystack,__dword,__n_bytes))
#else /* LIBC: memendl */
#include <local/string/memendl.h>
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memendl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendl))
#endif /* memendl... */
#if defined(__CRT_HAVE_memrendw)
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__libc_slow_memrendw,(void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__word,__n_words))
#else /* LIBC: memrendw */
#include <local/string/memrendw.h>
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrendw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))
#endif /* memrendw... */
#if defined(__CRT_HAVE_memrendl)
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__libc_slow_memrendl,(void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__dword,__n_dwords))
#else /* LIBC: memrendl */
#include <local/string/memrendl.h>
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrendl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))
#endif /* memrendl... */
#if defined(__CRT_HAVE_memcpyq)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_memcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),memcpyq,(__dst,__src,__n_qwords))
#else /* LIBC: memcpyq */
#include <local/string/memcpyq.h>
/* Copy memory between non-overlapping memory blocks. */
#define __libc_slow_memcpyq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyq))
#endif /* memcpyq... */
#if defined(__CRT_HAVE_mempcpyq)
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempcpyq,(__dst,__src,__n_qwords))
#else /* LIBC: mempcpyq */
#include <local/string/mempcpyq.h>
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_slow_mempcpyq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyq))
#endif /* mempcpyq... */
#if defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_memmoveq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: memmoveq */
#include <local/string/memmoveq.h>
/* Move memory between potentially overlapping memory blocks. */
#define __libc_slow_memmoveq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmoveq))
#endif /* memmoveq... */
#if defined(__CRT_HAVE_mempmoveq)
/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempmoveq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* LIBC: mempmoveq */
#include <local/string/mempmoveq.h>
/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_slow_mempmoveq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmoveq))
#endif /* mempmoveq... */
#if defined(__CRT_HAVE_memsetq)
/* Fill memory with a given qword */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_memsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memsetq,(__dst,__qword,__n_qwords))
#else /* LIBC: memsetq */
#include <local/string/memsetq.h>
/* Fill memory with a given qword */
#define __libc_slow_memsetq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetq))
#endif /* memsetq... */
#if defined(__CRT_HAVE_mempsetq)
/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_mempsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),mempsetq,(__dst,__qword,__n_qwords))
#else /* LIBC: mempsetq */
#include <local/string/mempsetq.h>
/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_slow_mempsetq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetq))
#endif /* mempsetq... */
#if defined(__CRT_HAVE_memcmpq)
/* Compare memory buffers and return the difference of the first non-matching qword */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),__INT64_TYPE__,__NOTHROW_NCX,__libc_slow_memcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpq,(__s1,__s2,__n_dwords))
#else /* LIBC: memcmpq */
#include <local/string/memcmpq.h>
/* Compare memory buffers and return the difference of the first non-matching qword */
#define __libc_slow_memcmpq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpq))
#endif /* memcmpq... */
#if defined(__CRT_HAVE_memchrq)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_memchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memchrq,(__haystack,__qword,__n_qwords))
#else /* LIBC: memchrq */
#include <local/string/memchrq.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memchrq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrq))
#endif /* memchrq... */
#if defined(__CRT_HAVE_memrchrq)
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_memrchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrchrq,(__haystack,__qword,__n_qwords))
#else /* LIBC: memrchrq */
#include <local/string/memrchrq.h>
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrchrq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrchrq))
#endif /* memrchrq... */
#if defined(__CRT_HAVE_memendq)
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__qword,__n_bytes))
#else /* LIBC: memendq */
#include <local/string/memendq.h>
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memendq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))
#endif /* memendq... */
#if defined(__CRT_HAVE_memrendq)
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__libc_slow_memrendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrendq,(__haystack,__qword,__n_qwords))
#else /* LIBC: memrendq */
#include <local/string/memrendq.h>
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrendq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendq))
#endif /* memrendq... */
#if defined(__CRT_HAVE_memlenq)
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_memlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memlenq,(__haystack,__qword,__n_qwords))
#else /* LIBC: memlenq */
#include <local/string/memlenq.h>
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_slow_memlenq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlenq))
#endif /* memlenq... */
#if defined(__CRT_HAVE_memrlenq)
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_memrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memrlenq,(__haystack,__qword,__n_qwords))
#else /* LIBC: memrlenq */
#include <local/string/memrlenq.h>
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_slow_memrlenq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlenq))
#endif /* memrlenq... */
#if defined(__CRT_HAVE_rawmemlenq)
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_rawmemlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemlenq,(__haystack,__qword))
#else /* LIBC: rawmemlenq */
#include <local/string/rawmemlenq.h>
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_slow_rawmemlenq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemlenq))
#endif /* rawmemlenq... */
#if defined(__CRT_HAVE_rawmemrlenq)
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_rawmemrlenq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemrlenq,(__haystack,__qword))
#else /* LIBC: rawmemrlenq */
#include <local/string/rawmemrlenq.h>
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_slow_rawmemrlenq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemrlenq))
#endif /* rawmemrlenq... */
#if defined(__CRT_HAVE_strend)
/* Same as `STR+strlen(STR)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__libc_slow_strend,(char const *__restrict __string),strend,(__string))
#else /* LIBC: strend */
#include <local/string/strend.h>
/* Same as `STR+strlen(STR)' */
#define __libc_slow_strend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strend))
#endif /* strend... */
#if defined(__CRT_HAVE_strnend)
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__libc_slow_strnend,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnend,(__string,__maxlen))
#else /* LIBC: strnend */
#include <local/string/strnend.h>
/* Same as `STR+strnlen(STR, MAX_CHARS)' */
#define __libc_slow_strnend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnend))
#endif /* strnend... */
#if defined(__CRT_HAVE_mempset)
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* LIBC: mempset */
#include <local/string/mempset.h>
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
#define __libc_slow_mempset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))
#endif /* mempset... */
#if defined(__CRT_HAVE_mempmove)
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__libc_slow_mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* LIBC: mempmove */
#include <local/string/mempmove.h>
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
#define __libc_slow_mempmove (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmove))
#endif /* mempmove... */
#if defined(__CRT_HAVE_memend)
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_memend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memend,(__haystack,__needle,__n_bytes))
#else /* LIBC: memend */
#include <local/string/memend.h>
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memend))
#endif /* memend... */
#if defined(__CRT_HAVE_memrend)
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
#else /* LIBC: memrend */
#include <local/string/memrend.h>
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_slow_memrend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))
#endif /* memrend... */
#if defined(__CRT_HAVE_memlen)
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_memlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memlen,(__haystack,__needle,__n_bytes))
#else /* LIBC: memlen */
#include <local/string/memlen.h>
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_slow_memlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memlen))
#endif /* memlen... */
#if defined(__CRT_HAVE_memrlen)
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__libc_slow_memrlen,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrlen,(__haystack,__needle,__n_bytes))
#else /* LIBC: memrlen */
#include <local/string/memrlen.h>
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_slow_memrlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrlen))
#endif /* memrlen... */
#if defined(__CRT_HAVE_mempatw)
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_mempatw,(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),mempatw,(__dst,__pattern,__n_bytes))
#else /* LIBC: mempatw */
#include <local/string/mempatw.h>
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
#define __libc_slow_mempatw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatw))
#endif /* mempatw... */
#if defined(__CRT_HAVE_mempatl)
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_mempatl,(void *__restrict __dst, __UINT32_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),mempatl,(__dst,__pattern,__n_bytes))
#else /* LIBC: mempatl */
#include <local/string/mempatl.h>
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
#define __libc_slow_mempatl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatl))
#endif /* mempatl... */
#if defined(__CRT_HAVE_mempatq)
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__libc_slow_mempatq,(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes),mempatq,(__dst,__pattern,__n_bytes))
#else /* LIBC: mempatq */
#include <local/string/mempatq.h>
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
#define __libc_slow_mempatq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempatq))
#endif /* mempatq... */

__SYSDECL_END

#endif /* !_LIBC_SLOW_STRING_H */
