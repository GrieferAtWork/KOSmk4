/* HASH CRC-32:0x7e428489 */
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
#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include "slow/string.h"

#ifdef __fast_memcpy_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#else /* __fast_memcpy_defined */
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memcpy __libc_slow_memcpy
#endif /* !__fast_memcpy_defined */
#ifdef __fast_memmove_defined
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))
#else /* __fast_memmove_defined */
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memmove __libc_slow_memmove
#endif /* !__fast_memmove_defined */
#ifdef __fast_memset_defined
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __libc_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#else /* __fast_memset_defined */
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __libc_memset __libc_slow_memset
#endif /* !__fast_memset_defined */
#ifdef __fast_memcmp_defined
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __libc_memcmp (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))
#else /* __fast_memcmp_defined */
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __libc_memcmp __libc_slow_memcmp
#endif /* !__fast_memcmp_defined */
#ifdef __fast_memchr_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchr (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))
#else /* __fast_memchr_defined */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchr __libc_slow_memchr
#endif /* !__fast_memchr_defined */
#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p) && (__has_builtin(__builtin_strlen) && defined(__CRT_HAVE_strlen))
#define __libc_strlen(string) (__builtin_constant_p(string) ? __builtin_strlen(string) : __libc_slow_strlen(string))
#else /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p && __builtin_strlen && __CRT_HAVE_strlen */
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __libc_strlen __libc_slow_strlen
#endif /* !__LIBC_BIND_OPTIMIZATIONS || __NO_builtin_constant_p || !__builtin_strlen || !__CRT_HAVE_strlen */
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __libc_strchr __libc_slow_strchr
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_strcmp __libc_slow_strcmp
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __libc_strnlen __libc_slow_strnlen
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrchr __libc_slow_memrchr
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __libc_memmem __libc_slow_memmem
#ifdef __fast_mempcpy_defined
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
#define __libc_mempcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))
#else /* __fast_mempcpy_defined */
/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
#define __libc_mempcpy __libc_slow_mempcpy
#endif /* !__fast_mempcpy_defined */
#ifdef __fast_memcpyw_defined
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))
#else /* __fast_memcpyw_defined */
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyw __libc_slow_memcpyw
#endif /* !__fast_memcpyw_defined */
#ifdef __fast_mempcpyw_defined
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
#define __libc_mempcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))
#else /* __fast_mempcpyw_defined */
/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
#define __libc_mempcpyw __libc_slow_mempcpyw
#endif /* !__fast_mempcpyw_defined */
#ifdef __fast_memcpyl_defined
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))
#else /* __fast_memcpyl_defined */
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyl __libc_slow_memcpyl
#endif /* !__fast_memcpyl_defined */
#ifdef __fast_mempcpyl_defined
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_mempcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))
#else /* __fast_mempcpyl_defined */
/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_mempcpyl __libc_slow_mempcpyl
#endif /* !__fast_mempcpyl_defined */
#ifdef __fast_memmovew_defined
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))
#else /* __fast_memmovew_defined */
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovew __libc_slow_memmovew
#endif /* !__fast_memmovew_defined */
#ifdef __fast_mempmovew_defined
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
#define __libc_mempmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))
#else /* __fast_mempmovew_defined */
/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
#define __libc_mempmovew __libc_slow_mempmovew
#endif /* !__fast_mempmovew_defined */
#ifdef __fast_memmovel_defined
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovel (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))
#else /* __fast_memmovel_defined */
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovel __libc_slow_memmovel
#endif /* !__fast_memmovel_defined */
#ifdef __fast_mempmovel_defined
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_mempmovel (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))
#else /* __fast_mempmovel_defined */
/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_mempmovel __libc_slow_mempmovel
#endif /* !__fast_mempmovel_defined */
#ifdef __fast_memsetw_defined
/* Fill memory with a given word */
#define __libc_memsetw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))
#else /* __fast_memsetw_defined */
/* Fill memory with a given word */
#define __libc_memsetw __libc_slow_memsetw
#endif /* !__fast_memsetw_defined */
#ifdef __fast_mempsetw_defined
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
#define __libc_mempsetw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))
#else /* __fast_mempsetw_defined */
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
#define __libc_mempsetw __libc_slow_mempsetw
#endif /* !__fast_mempsetw_defined */
#ifdef __fast_memsetl_defined
/* Fill memory with a given dword */
#define __libc_memsetl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))
#else /* __fast_memsetl_defined */
/* Fill memory with a given dword */
#define __libc_memsetl __libc_slow_memsetl
#endif /* !__fast_memsetl_defined */
#ifdef __fast_mempsetl_defined
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_mempsetl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))
#else /* __fast_mempsetl_defined */
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
#define __libc_mempsetl __libc_slow_mempsetl
#endif /* !__fast_mempsetl_defined */
#ifdef __fast_memcmpw_defined
/* Compare memory buffers and return the difference of the first non-matching word */
#define __libc_memcmpw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))
#else /* __fast_memcmpw_defined */
/* Compare memory buffers and return the difference of the first non-matching word */
#define __libc_memcmpw __libc_slow_memcmpw
#endif /* !__fast_memcmpw_defined */
#ifdef __fast_memcmpl_defined
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __libc_memcmpl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))
#else /* __fast_memcmpl_defined */
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __libc_memcmpl __libc_slow_memcmpl
#endif /* !__fast_memcmpl_defined */
#ifdef __fast_memchrw_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchrw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))
#else /* __fast_memchrw_defined */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchrw __libc_slow_memchrw
#endif /* !__fast_memchrw_defined */
#ifdef __fast_memchrl_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchrl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))
#else /* __fast_memchrl_defined */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchrl __libc_slow_memchrl
#endif /* !__fast_memchrl_defined */
#ifdef __fast_memrchrw_defined
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrchrw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))
#else /* __fast_memrchrw_defined */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrchrw __libc_slow_memrchrw
#endif /* !__fast_memrchrw_defined */
#ifdef __fast_memrchrl_defined
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrchrl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))
#else /* __fast_memrchrl_defined */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrchrl __libc_slow_memrchrl
#endif /* !__fast_memrchrl_defined */
#ifdef __fast_memendw_defined
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memendw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))
#else /* __fast_memendw_defined */
/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memendw __libc_slow_memendw
#endif /* !__fast_memendw_defined */
#ifdef __fast_memendl_defined
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memendl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))
#else /* __fast_memendl_defined */
/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memendl __libc_slow_memendl
#endif /* !__fast_memendl_defined */
#ifdef __fast_memrendw_defined
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrendw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))
#else /* __fast_memrendw_defined */
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrendw __libc_slow_memrendw
#endif /* !__fast_memrendw_defined */
#ifdef __fast_memrendl_defined
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrendl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))
#else /* __fast_memrendl_defined */
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrendl __libc_slow_memrendl
#endif /* !__fast_memrendl_defined */
#ifdef __fast_memcpyq_defined
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))
#else /* __fast_memcpyq_defined */
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyq __libc_slow_memcpyq
#endif /* !__fast_memcpyq_defined */
#ifdef __fast_mempcpyq_defined
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_mempcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))
#else /* __fast_mempcpyq_defined */
/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_mempcpyq __libc_slow_mempcpyq
#endif /* !__fast_mempcpyq_defined */
#ifdef __fast_memmoveq_defined
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmoveq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))
#else /* __fast_memmoveq_defined */
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmoveq __libc_slow_memmoveq
#endif /* !__fast_memmoveq_defined */
#ifdef __fast_mempmoveq_defined
/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_mempmoveq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))
#else /* __fast_mempmoveq_defined */
/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_mempmoveq __libc_slow_mempmoveq
#endif /* !__fast_mempmoveq_defined */
#ifdef __fast_memsetq_defined
/* Fill memory with a given qword */
#define __libc_memsetq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))
#else /* __fast_memsetq_defined */
/* Fill memory with a given qword */
#define __libc_memsetq __libc_slow_memsetq
#endif /* !__fast_memsetq_defined */
#ifdef __fast_mempsetq_defined
/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_mempsetq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))
#else /* __fast_mempsetq_defined */
/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
#define __libc_mempsetq __libc_slow_mempsetq
#endif /* !__fast_mempsetq_defined */
#ifdef __fast_memcmpq_defined
/* Compare memory buffers and return the difference of the first non-matching qword */
#define __libc_memcmpq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))
#else /* __fast_memcmpq_defined */
/* Compare memory buffers and return the difference of the first non-matching qword */
#define __libc_memcmpq __libc_slow_memcmpq
#endif /* !__fast_memcmpq_defined */
#ifdef __fast_memchrq_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchrq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))
#else /* __fast_memchrq_defined */
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memchrq __libc_slow_memchrq
#endif /* !__fast_memchrq_defined */
#ifdef __fast_memrchrq_defined
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrchrq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))
#else /* __fast_memrchrq_defined */
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrchrq __libc_slow_memrchrq
#endif /* !__fast_memrchrq_defined */
#ifdef __fast_memendq_defined
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memendq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))
#else /* __fast_memendq_defined */
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memendq __libc_slow_memendq
#endif /* !__fast_memendq_defined */
#ifdef __fast_memrendq_defined
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrendq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))
#else /* __fast_memrendq_defined */
/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrendq __libc_slow_memrendq
#endif /* !__fast_memrendq_defined */
#ifdef __fast_memlenq_defined
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlenq))
#else /* __fast_memlenq_defined */
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memlenq __libc_slow_memlenq
#endif /* !__fast_memlenq_defined */
#ifdef __fast_memrlenq_defined
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memrlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlenq))
#else /* __fast_memrlenq_defined */
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memrlenq __libc_slow_memrlenq
#endif /* !__fast_memrlenq_defined */
#ifdef __fast_rawmemlenq_defined
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_rawmemlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemlenq))
#else /* __fast_rawmemlenq_defined */
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_rawmemlenq __libc_slow_rawmemlenq
#endif /* !__fast_rawmemlenq_defined */
#ifdef __fast_rawmemrlenq_defined
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_rawmemrlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemrlenq))
#else /* __fast_rawmemrlenq_defined */
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_rawmemrlenq __libc_slow_rawmemrlenq
#endif /* !__fast_rawmemrlenq_defined */
/* Same as `STR + strlen(STR)' */
#define __libc_strend __libc_slow_strend
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
#define __libc_strnend __libc_slow_strnend
#ifdef __fast_mempset_defined
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
#define __libc_mempset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))
#else /* __fast_mempset_defined */
/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
#define __libc_mempset __libc_slow_mempset
#endif /* !__fast_mempset_defined */
#ifdef __fast_mempmove_defined
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
#define __libc_mempmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))
#else /* __fast_mempmove_defined */
/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
#define __libc_mempmove __libc_slow_mempmove
#endif /* !__fast_mempmove_defined */
#ifdef __fast_memend_defined
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memend (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))
#else /* __fast_memend_defined */
/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memend __libc_slow_memend
#endif /* !__fast_memend_defined */
#ifdef __fast_memrend_defined
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrend (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))
#else /* __fast_memrend_defined */
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __libc_memrend __libc_slow_memrend
#endif /* !__fast_memrend_defined */
#ifdef __fast_memlen_defined
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memlen (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))
#else /* __fast_memlen_defined */
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memlen __libc_slow_memlen
#endif /* !__fast_memlen_defined */
#ifdef __fast_memrlen_defined
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memrlen (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))
#else /* __fast_memrlen_defined */
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
#define __libc_memrlen __libc_slow_memrlen
#endif /* !__fast_memrlen_defined */
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __libc_memrmem __libc_slow_memrmem
#ifdef __fast_mempatw_defined
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
#define __libc_mempatw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatw))
#else /* __fast_mempatw_defined */
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
#define __libc_mempatw __libc_slow_mempatw
#endif /* !__fast_mempatw_defined */
#ifdef __fast_mempatl_defined
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
#define __libc_mempatl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatl))
#else /* __fast_mempatl_defined */
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
#define __libc_mempatl __libc_slow_mempatl
#endif /* !__fast_mempatl_defined */
#ifdef __fast_mempatq_defined
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
#define __libc_mempatq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatq))
#else /* __fast_mempatq_defined */
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
#define __libc_mempatq __libc_slow_mempatq
#endif /* !__fast_mempatq_defined */

#endif /* __CC__ */

#endif /* !_LIBC_STRING_H */
