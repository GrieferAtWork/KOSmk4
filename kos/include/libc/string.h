/* HASH CRC-32:0xa2f11084 */
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
#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include "core/string.h"

#ifdef __fast_memcpy_defined
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#else /* __fast_memcpy_defined */
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memcpy __libc_core_memcpy
#endif /* !__fast_memcpy_defined */
#ifdef __fast_memmove_defined
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmove))
#else /* __fast_memmove_defined */
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memmove __libc_core_memmove
#endif /* !__fast_memmove_defined */
#ifdef __fast_memset_defined
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __libc_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#else /* __fast_memset_defined */
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __libc_memset __libc_core_memset
#endif /* !__fast_memset_defined */
#ifdef __fast_memcmp_defined
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __libc_memcmp (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))
#else /* __fast_memcmp_defined */
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __libc_memcmp __libc_core_memcmp
#endif /* !__fast_memcmp_defined */
#ifdef __fast_memchr_defined
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
#define __libc_memchr (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))
#else /* __fast_memchr_defined */
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
#define __libc_memchr __libc_core_memchr
#endif /* !__fast_memchr_defined */
#if defined(__LIBC_BIND_OPTIMIZATIONS) && !defined(__NO_builtin_constant_p) && (__has_builtin(__builtin_strlen) && defined(__CRT_HAVE_strlen))
#define __libc_strlen(str) (__builtin_constant_p(str) ? __builtin_strlen(str) : __libc_core_strlen(str))
#else /* __LIBC_BIND_OPTIMIZATIONS && !__NO_builtin_constant_p && __builtin_strlen && __CRT_HAVE_strlen */
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __libc_strlen __libc_core_strlen
#endif /* !__LIBC_BIND_OPTIMIZATIONS || __NO_builtin_constant_p || !__builtin_strlen || !__CRT_HAVE_strlen */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
#define __libc_strchr __libc_core_strchr
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __libc_strcmp __libc_core_strcmp
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
#define __libc_strcpy __libc_core_strcpy
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __libc_strnlen __libc_core_strnlen
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
#define __libc_memrchr __libc_core_memrchr
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __libc_memmem __libc_core_memmem
#ifdef __fast_mempcpy_defined
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
#define __libc_mempcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))
#else /* __fast_mempcpy_defined */
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
#define __libc_mempcpy __libc_core_mempcpy
#endif /* !__fast_mempcpy_defined */
#ifdef __fast_bzero_defined
#define __libc_bzero (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzero))
#else /* __fast_bzero_defined */
#define __libc_bzero __libc_core_bzero
#endif /* !__fast_bzero_defined */
#ifdef __fast_bzerow_defined
#define __libc_bzerow (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerow))
#else /* __fast_bzerow_defined */
#define __libc_bzerow __libc_core_bzerow
#endif /* !__fast_bzerow_defined */
#ifdef __fast_bzerol_defined
#define __libc_bzerol (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzerol))
#else /* __fast_bzerol_defined */
#define __libc_bzerol __libc_core_bzerol
#endif /* !__fast_bzerol_defined */
#ifdef __fast_bzeroq_defined
#define __libc_bzeroq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroq))
#else /* __fast_bzeroq_defined */
#define __libc_bzeroq __libc_core_bzeroq
#endif /* !__fast_bzeroq_defined */
#ifdef __fast_bzeroc_defined
#define __libc_bzeroc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bzeroc))
#else /* __fast_bzeroc_defined */
#define __libc_bzeroc __libc_core_bzeroc
#endif /* !__fast_bzeroc_defined */
#ifdef __fast_bcmp_defined
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
#define __libc_bcmp (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(bcmp))
#else /* __fast_bcmp_defined */
/* >> bcmp(3)
 * Similar to `memcmp(3)', except that no ordering is done,
 * such  that compare is  only correct for equal/non-equal.
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return: != 0: `s1...+=n_bytes' != `s2...+=n_bytes' */
#define __libc_bcmp __libc_core_bcmp
#endif /* !__fast_bcmp_defined */
#ifdef __fast_memcpyw_defined
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))
#else /* __fast_memcpyw_defined */
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyw __libc_core_memcpyw
#endif /* !__fast_memcpyw_defined */
#ifdef __fast_mempcpyw_defined
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
#define __libc_mempcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyw))
#else /* __fast_mempcpyw_defined */
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
#define __libc_mempcpyw __libc_core_mempcpyw
#endif /* !__fast_mempcpyw_defined */
#ifdef __fast_memcpyl_defined
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))
#else /* __fast_memcpyl_defined */
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyl __libc_core_memcpyl
#endif /* !__fast_memcpyl_defined */
#ifdef __fast_mempcpyl_defined
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_mempcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyl))
#else /* __fast_mempcpyl_defined */
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_mempcpyl __libc_core_mempcpyl
#endif /* !__fast_mempcpyl_defined */
#ifdef __fast_memmovew_defined
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovew))
#else /* __fast_memmovew_defined */
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovew __libc_core_memmovew
#endif /* !__fast_memmovew_defined */
#ifdef __fast_mempmovew_defined
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
#define __libc_mempmovew (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovew))
#else /* __fast_mempmovew_defined */
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
#define __libc_mempmovew __libc_core_mempmovew
#endif /* !__fast_mempmovew_defined */
#ifdef __fast_memmovel_defined
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovel (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovel))
#else /* __fast_memmovel_defined */
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmovel __libc_core_memmovel
#endif /* !__fast_memmovel_defined */
#ifdef __fast_mempmovel_defined
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_mempmovel (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovel))
#else /* __fast_mempmovel_defined */
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_mempmovel __libc_core_mempmovel
#endif /* !__fast_mempmovel_defined */
#ifdef __fast_memmoveupw_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
#define __libc_memmoveupw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupw))
#else /* __fast_memmoveupw_defined */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
#define __libc_memmoveupw __libc_core_memmoveupw
#endif /* !__fast_memmoveupw_defined */
#ifdef __fast_memmovedownw_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
#define __libc_memmovedownw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownw))
#else /* __fast_memmovedownw_defined */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
#define __libc_memmovedownw __libc_core_memmovedownw
#endif /* !__fast_memmovedownw_defined */
#ifdef __fast_mempmoveupw_defined
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
#define __libc_mempmoveupw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupw))
#else /* __fast_mempmoveupw_defined */
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
#define __libc_mempmoveupw __libc_core_mempmoveupw
#endif /* !__fast_mempmoveupw_defined */
#ifdef __fast_mempmovedownw_defined
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
#define __libc_mempmovedownw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownw))
#else /* __fast_mempmovedownw_defined */
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
#define __libc_mempmovedownw __libc_core_mempmovedownw
#endif /* !__fast_mempmovedownw_defined */
#ifdef __fast_memmoveupl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
#define __libc_memmoveupl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupl))
#else /* __fast_memmoveupl_defined */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
#define __libc_memmoveupl __libc_core_memmoveupl
#endif /* !__fast_memmoveupl_defined */
#ifdef __fast_memmovedownl_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
#define __libc_memmovedownl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownl))
#else /* __fast_memmovedownl_defined */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
#define __libc_memmovedownl __libc_core_memmovedownl
#endif /* !__fast_memmovedownl_defined */
#ifdef __fast_mempmoveupl_defined
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
#define __libc_mempmoveupl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupl))
#else /* __fast_mempmoveupl_defined */
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
#define __libc_mempmoveupl __libc_core_mempmoveupl
#endif /* !__fast_mempmoveupl_defined */
#ifdef __fast_mempmovedownl_defined
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
#define __libc_mempmovedownl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownl))
#else /* __fast_mempmovedownl_defined */
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
#define __libc_mempmovedownl __libc_core_mempmovedownl
#endif /* !__fast_mempmovedownl_defined */
#ifdef __fast_memsetw_defined
/* Fill memory with a given word */
#define __libc_memsetw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))
#else /* __fast_memsetw_defined */
/* Fill memory with a given word */
#define __libc_memsetw __libc_core_memsetw
#endif /* !__fast_memsetw_defined */
#ifdef __fast_mempsetw_defined
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
#define __libc_mempsetw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))
#else /* __fast_mempsetw_defined */
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
#define __libc_mempsetw __libc_core_mempsetw
#endif /* !__fast_mempsetw_defined */
#ifdef __fast_memsetl_defined
/* Fill memory with a given dword */
#define __libc_memsetl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))
#else /* __fast_memsetl_defined */
/* Fill memory with a given dword */
#define __libc_memsetl __libc_core_memsetl
#endif /* !__fast_memsetl_defined */
#ifdef __fast_mempsetl_defined
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_mempsetl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))
#else /* __fast_mempsetl_defined */
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
#define __libc_mempsetl __libc_core_mempsetl
#endif /* !__fast_mempsetl_defined */
#ifdef __fast_memcmpw_defined
/* Compare memory buffers and return the difference of the first non-matching word */
#define __libc_memcmpw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpw))
#else /* __fast_memcmpw_defined */
/* Compare memory buffers and return the difference of the first non-matching word */
#define __libc_memcmpw __libc_core_memcmpw
#endif /* !__fast_memcmpw_defined */
#ifdef __fast_memcmpl_defined
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __libc_memcmpl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpl))
#else /* __fast_memcmpl_defined */
/* Compare memory buffers and return the difference of the first non-matching dword */
#define __libc_memcmpl __libc_core_memcmpl
#endif /* !__fast_memcmpl_defined */
#ifdef __fast_memchrw_defined
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memchrw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrw))
#else /* __fast_memchrw_defined */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memchrw __libc_core_memchrw
#endif /* !__fast_memchrw_defined */
#ifdef __fast_memchrl_defined
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memchrl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrl))
#else /* __fast_memchrl_defined */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memchrl __libc_core_memchrl
#endif /* !__fast_memchrl_defined */
#ifdef __fast_memrchrw_defined
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memrchrw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrw))
#else /* __fast_memrchrw_defined */
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memrchrw __libc_core_memrchrw
#endif /* !__fast_memrchrw_defined */
#ifdef __fast_memrchrl_defined
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memrchrl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrl))
#else /* __fast_memrchrl_defined */
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memrchrl __libc_core_memrchrl
#endif /* !__fast_memrchrl_defined */
#ifdef __fast_memendw_defined
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
#define __libc_memendw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))
#else /* __fast_memendw_defined */
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
#define __libc_memendw __libc_core_memendw
#endif /* !__fast_memendw_defined */
#ifdef __fast_memendl_defined
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
#define __libc_memendl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendl))
#else /* __fast_memendl_defined */
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
#define __libc_memendl __libc_core_memendl
#endif /* !__fast_memendl_defined */
#ifdef __fast_memrendw_defined
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrendw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))
#else /* __fast_memrendw_defined */
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrendw __libc_core_memrendw
#endif /* !__fast_memrendw_defined */
#ifdef __fast_memrendl_defined
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrendl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))
#else /* __fast_memrendl_defined */
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrendl __libc_core_memrendl
#endif /* !__fast_memrendl_defined */
#ifdef __fast_memcpyq_defined
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))
#else /* __fast_memcpyq_defined */
/* Copy memory between non-overlapping memory blocks. */
#define __libc_memcpyq __libc_core_memcpyq
#endif /* !__fast_memcpyq_defined */
#ifdef __fast_mempcpyq_defined
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
#define __libc_mempcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyq))
#else /* __fast_mempcpyq_defined */
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
#define __libc_mempcpyq __libc_core_mempcpyq
#endif /* !__fast_mempcpyq_defined */
#ifdef __fast_memmoveq_defined
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmoveq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveq))
#else /* __fast_memmoveq_defined */
/* Move memory between potentially overlapping memory blocks. */
#define __libc_memmoveq __libc_core_memmoveq
#endif /* !__fast_memmoveq_defined */
#ifdef __fast_mempmoveq_defined
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
#define __libc_mempmoveq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveq))
#else /* __fast_mempmoveq_defined */
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
#define __libc_mempmoveq __libc_core_mempmoveq
#endif /* !__fast_mempmoveq_defined */
#ifdef __fast_memmoveupq_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
#define __libc_memmoveupq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupq))
#else /* __fast_memmoveupq_defined */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
#define __libc_memmoveupq __libc_core_memmoveupq
#endif /* !__fast_memmoveupq_defined */
#ifdef __fast_memmovedownq_defined
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
#define __libc_memmovedownq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownq))
#else /* __fast_memmovedownq_defined */
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
#define __libc_memmovedownq __libc_core_memmovedownq
#endif /* !__fast_memmovedownq_defined */
#ifdef __fast_mempmoveupq_defined
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
#define __libc_mempmoveupq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupq))
#else /* __fast_mempmoveupq_defined */
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
#define __libc_mempmoveupq __libc_core_mempmoveupq
#endif /* !__fast_mempmoveupq_defined */
#ifdef __fast_mempmovedownq_defined
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
#define __libc_mempmovedownq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownq))
#else /* __fast_mempmovedownq_defined */
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
#define __libc_mempmovedownq __libc_core_mempmovedownq
#endif /* !__fast_mempmovedownq_defined */
#ifdef __fast_memsetq_defined
/* Fill memory with a given qword */
#define __libc_memsetq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))
#else /* __fast_memsetq_defined */
/* Fill memory with a given qword */
#define __libc_memsetq __libc_core_memsetq
#endif /* !__fast_memsetq_defined */
#ifdef __fast_mempsetq_defined
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
#define __libc_mempsetq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))
#else /* __fast_mempsetq_defined */
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
#define __libc_mempsetq __libc_core_mempsetq
#endif /* !__fast_mempsetq_defined */
#ifdef __fast_memcmpq_defined
/* Compare memory buffers and return the difference of the first non-matching qword */
#define __libc_memcmpq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpq))
#else /* __fast_memcmpq_defined */
/* Compare memory buffers and return the difference of the first non-matching qword */
#define __libc_memcmpq __libc_core_memcmpq
#endif /* !__fast_memcmpq_defined */
#ifdef __fast_memchrq_defined
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memchrq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchrq))
#else /* __fast_memchrq_defined */
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memchrq __libc_core_memchrq
#endif /* !__fast_memchrq_defined */
#ifdef __fast_memrchrq_defined
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memrchrq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrchrq))
#else /* __fast_memrchrq_defined */
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
#define __libc_memrchrq __libc_core_memrchrq
#endif /* !__fast_memrchrq_defined */
#ifdef __fast_memendq_defined
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
#define __libc_memendq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))
#else /* __fast_memendq_defined */
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
#define __libc_memendq __libc_core_memendq
#endif /* !__fast_memendq_defined */
#ifdef __fast_memrendq_defined
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrendq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendq))
#else /* __fast_memrendq_defined */
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrendq __libc_core_memrendq
#endif /* !__fast_memrendq_defined */
#ifdef __fast_memlenq_defined
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
#define __libc_memlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlenq))
#else /* __fast_memlenq_defined */
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
#define __libc_memlenq __libc_core_memlenq
#endif /* !__fast_memlenq_defined */
#ifdef __fast_memrlenq_defined
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
#define __libc_memrlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlenq))
#else /* __fast_memrlenq_defined */
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
#define __libc_memrlenq __libc_core_memrlenq
#endif /* !__fast_memrlenq_defined */
#ifdef __fast_rawmemlenq_defined
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
#define __libc_rawmemlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemlenq))
#else /* __fast_rawmemlenq_defined */
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
#define __libc_rawmemlenq __libc_core_rawmemlenq
#endif /* !__fast_rawmemlenq_defined */
#ifdef __fast_rawmemrlenq_defined
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
#define __libc_rawmemrlenq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(rawmemrlenq))
#else /* __fast_rawmemrlenq_defined */
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
#define __libc_rawmemrlenq __libc_core_rawmemrlenq
#endif /* !__fast_rawmemrlenq_defined */
#ifdef __fast_memmoveup_defined
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
#define __libc_memmoveup (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveup))
#else /* __fast_memmoveup_defined */
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
#define __libc_memmoveup __libc_core_memmoveup
#endif /* !__fast_memmoveup_defined */
#ifdef __fast_memmovedown_defined
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
#define __libc_memmovedown (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedown))
#else /* __fast_memmovedown_defined */
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
#define __libc_memmovedown __libc_core_memmovedown
#endif /* !__fast_memmovedown_defined */
#ifdef __fast_memcmpc_defined
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
#define __libc_memcmpc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmpc))
#else /* __fast_memcmpc_defined */
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
#define __libc_memcmpc __libc_core_memcmpc
#endif /* !__fast_memcmpc_defined */
#ifdef __fast_memcpyc_defined
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memcpyc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))
#else /* __fast_memcpyc_defined */
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __libc_memcpyc __libc_core_memcpyc
#endif /* !__fast_memcpyc_defined */
#ifdef __fast_mempcpyc_defined
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
#define __libc_mempcpyc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpyc))
#else /* __fast_mempcpyc_defined */
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
#define __libc_mempcpyc __libc_core_mempcpyc
#endif /* !__fast_mempcpyc_defined */
#ifdef __fast_memmovec_defined
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
#define __libc_memmovec (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovec))
#else /* __fast_memmovec_defined */
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
#define __libc_memmovec __libc_core_memmovec
#endif /* !__fast_memmovec_defined */
#ifdef __fast_mempmovec_defined
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
#define __libc_mempmovec (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovec))
#else /* __fast_mempmovec_defined */
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
#define __libc_mempmovec __libc_core_mempmovec
#endif /* !__fast_mempmovec_defined */
#ifdef __fast_memmoveupc_defined
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __libc_memmoveupc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmoveupc))
#else /* __fast_memmoveupc_defined */
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __libc_memmoveupc __libc_core_memmoveupc
#endif /* !__fast_memmoveupc_defined */
#ifdef __fast_mempmoveupc_defined
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
#define __libc_mempmoveupc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveupc))
#else /* __fast_mempmoveupc_defined */
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
#define __libc_mempmoveupc __libc_core_mempmoveupc
#endif /* !__fast_mempmoveupc_defined */
#ifdef __fast_memmovedownc_defined
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __libc_memmovedownc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memmovedownc))
#else /* __fast_memmovedownc_defined */
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
#define __libc_memmovedownc __libc_core_memmovedownc
#endif /* !__fast_memmovedownc_defined */
#ifdef __fast_mempmovedownc_defined
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
#define __libc_mempmovedownc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedownc))
#else /* __fast_mempmovedownc_defined */
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
#define __libc_mempmovedownc __libc_core_mempmovedownc
#endif /* !__fast_mempmovedownc_defined */
/* >> strend(3)
 * Same as `str + strlen(str)' */
#define __libc_strend __libc_core_strend
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
#define __libc_strnend __libc_core_strnend
#ifdef __fast_mempset_defined
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
#define __libc_mempset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))
#else /* __fast_mempset_defined */
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
#define __libc_mempset __libc_core_mempset
#endif /* !__fast_mempset_defined */
#ifdef __fast_mempmove_defined
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
#define __libc_mempmove (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmove))
#else /* __fast_mempmove_defined */
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
#define __libc_mempmove __libc_core_mempmove
#endif /* !__fast_mempmove_defined */
#ifdef __fast_mempmoveup_defined
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
#define __libc_mempmoveup (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmoveup))
#else /* __fast_mempmoveup_defined */
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
#define __libc_mempmoveup __libc_core_mempmoveup
#endif /* !__fast_mempmoveup_defined */
#ifdef __fast_mempmovedown_defined
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
#define __libc_mempmovedown (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempmovedown))
#else /* __fast_mempmovedown_defined */
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
#define __libc_mempmovedown __libc_core_mempmovedown
#endif /* !__fast_mempmovedown_defined */
#ifdef __fast_memend_defined
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
#define __libc_memend (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memend))
#else /* __fast_memend_defined */
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
#define __libc_memend __libc_core_memend
#endif /* !__fast_memend_defined */
#ifdef __fast_memrend_defined
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrend (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))
#else /* __fast_memrend_defined */
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
#define __libc_memrend __libc_core_memrend
#endif /* !__fast_memrend_defined */
#ifdef __fast_memlen_defined
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
#define __libc_memlen (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memlen))
#else /* __fast_memlen_defined */
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
#define __libc_memlen __libc_core_memlen
#endif /* !__fast_memlen_defined */
#ifdef __fast_memrlen_defined
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
#define __libc_memrlen (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrlen))
#else /* __fast_memrlen_defined */
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
#define __libc_memrlen __libc_core_memrlen
#endif /* !__fast_memrlen_defined */
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
#define __libc_memrmem __libc_core_memrmem
#ifdef __fast_mempatw_defined
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
#define __libc_mempatw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatw))
#else /* __fast_mempatw_defined */
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
#define __libc_mempatw __libc_core_mempatw
#endif /* !__fast_mempatw_defined */
#ifdef __fast_mempatl_defined
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
#define __libc_mempatl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatl))
#else /* __fast_mempatl_defined */
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
#define __libc_mempatl __libc_core_mempatl
#endif /* !__fast_mempatl_defined */
#ifdef __fast_mempatq_defined
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
#define __libc_mempatq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempatq))
#else /* __fast_mempatq_defined */
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
#define __libc_mempatq __libc_core_mempatq
#endif /* !__fast_mempatq_defined */
#define __libc_PRIVATE_memset1 __libc_memset
#define __libc_PRIVATE_memset2 __libc_memsetw
#define __libc_PRIVATE_memset4 __libc_memsetl
#define __libc_PRIVATE_memset8 __libc_memsetq
#define __libc_PRIVATE_memset(dst, word, elem_count, elem_size) \
	__libc_PRIVATE_memset##elem_size(dst, word, elem_count)
#define __libc_memsetc(dst, word, elem_count, elem_size) \
	__libc_PRIVATE_memset(dst, word, elem_count, elem_size)

#endif /* __CC__ */

#endif /* !_LIBC_STRING_H */
