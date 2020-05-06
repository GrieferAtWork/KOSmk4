/* HASH CRC-32:0x2a681638 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_STRING_H
#define GUARD_LIBC_AUTO_STRING_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <string.h>

DECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef size_t rsize_t;
#endif /* !__rsize_t_defined */

/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmove)(void *dst, void const *src, size_t n_bytes);
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memset)(void *__restrict dst, int byte, size_t n_bytes);
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_memcmp)(void const *s1, void const *s2, size_t n_bytes);
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memchr)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strlen)(char const *__restrict string);
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strchr)(char const *__restrict haystack, int needle);
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcmp)(char const *s1, char const *s2);
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnlen)(char const *__restrict string, size_t maxlen);
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrchr)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memchr' with a search limit of `(size_t)-1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemchr)(void const *__restrict haystack, int needle);
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memcpyw)(/*aligned(2)*/ void *__restrict dst, /*aligned(2)*/ void const *__restrict src, size_t n_words);
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempcpyw)(/*aligned(2)*/ void *__restrict dst, /*aligned(2)*/ void const *__restrict src, size_t n_words);
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memcpyl)(/*aligned(4)*/ void *__restrict dst, /*aligned(4)*/ void const *__restrict src, size_t n_dwords);
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempcpyl)(/*aligned(4)*/ void *__restrict dst, /*aligned(4)*/ void const *__restrict src, size_t n_dwords);
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmovew)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words);
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmovew)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words);
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmovel)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords);
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmovel)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords);
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmoveupw)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words);
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmovedownw)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words);
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupw)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words);
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownw)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words);
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmoveupl)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords);
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmovedownl)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords);
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupl)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords);
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownl)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords);
/* Fill memory with a given word */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memsetw)(/*aligned(2)*/ void *__restrict dst, uint16_t word, size_t n_words);
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempsetw)(/*aligned(2)*/ void *__restrict dst, uint16_t word, size_t n_words);
/* Fill memory with a given dword */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memsetl)(/*aligned(4)*/ void *__restrict dst, uint32_t dword, size_t n_dwords);
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempsetl)(/*aligned(4)*/ void *__restrict dst, uint32_t dword, size_t n_dwords);
/* Compare memory buffers and return the difference of the first non-matching word */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int16_t NOTHROW_NCX(LIBCCALL libc_memcmpw)(/*aligned(2)*/ void const *s1, /*aligned(2)*/ void const *s2, size_t n_words);
/* Compare memory buffers and return the difference of the first non-matching dword */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int32_t NOTHROW_NCX(LIBCCALL libc_memcmpl)(/*aligned(4)*/ void const *s1, /*aligned(4)*/ void const *s2, size_t n_dwords);
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memendw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_bytes);
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memendl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_bytes);
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrendw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrendl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 4' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memcpyq)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords);
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempcpyq)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords);
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmoveq)(/*aligned(8)*/ void *dst, /*aligned(8)*/ void const *src, size_t n_qwords);
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmoveq)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords);
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmoveupq)(/*aligned(8)*/ void *dst, /*aligned(8)*/ void const *src, size_t n_qwords);
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmovedownq)(/*aligned(8)*/ void *dst, /*aligned(8)*/ void const *src, size_t n_qwords);
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupq)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords);
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownq)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords);
/* Fill memory with a given qword */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memsetq)(/*aligned(8)*/ void *__restrict dst, uint64_t qword, size_t n_qwords);
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempsetq)(/*aligned(8)*/ void *__restrict dst, uint64_t qword, size_t n_qwords);
/* Compare memory buffers and return the difference of the first non-matching qword */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int64_t NOTHROW_NCX(LIBCCALL libc_memcmpq)(/*aligned(8)*/ void const *s1, /*aligned(8)*/ void const *s2, size_t n_dwords);
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memendq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_bytes);
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrendq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `N_QWORDS' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmoveup)(void *dst, void const *src, size_t n_bytes);
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmovedown)(void *dst, void const *src, size_t n_bytes);
/* Same as `STR + strlen(STR)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strend)(char const *__restrict string);
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnend)(char const *__restrict string, size_t maxlen);
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempset)(void *__restrict dst, int byte, size_t n_bytes);
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmove)(void *dst, void const *src, size_t n_bytes);
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmoveup)(void *dst, void const *src, size_t n_bytes);
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmovedown)(void *dst, void const *src, size_t n_bytes);
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemrchr)(void const *__restrict haystack, int needle);
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memend)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrend)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlen)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlen)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlen)(void const *__restrict haystack, int needle);
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlen)(void const *__restrict haystack, int needle);
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTDEF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatw)(void *__restrict dst, uint16_t pattern, size_t n_bytes);
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTDEF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatl)(void *__restrict dst, uint32_t pattern, size_t n_bytes);
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTDEF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatq)(void *__restrict dst, uint64_t pattern, size_t n_bytes);
#ifndef __KERNEL__
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strrchr)(char const *__restrict haystack, int needle);
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncmp)(char const *s1, char const *s2, size_t maxlen);
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strstr)(char const *haystack, char const *needle);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcpy)(char *__restrict buf, char const *__restrict src);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcat)(char *__restrict buf, char const *__restrict src);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strncat)(char *__restrict buf, char const *__restrict src, size_t buflen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strcspn)(char const *haystack, char const *reject);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strspn)(char const *haystack, char const *accept);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strpbrk)(char const *haystack, char const *accept);
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_strtok)(char *string, char const *delim);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcoll)(char const *s1, char const *s2);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBCCALL libc_strxfrm)(char *dst, char const *__restrict src, size_t maxlen);
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_stpcpy)(char *__restrict buf, char const *__restrict src);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_stpncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
#define libc___stpcpy libc_stpcpy
#define libc___stpncpy libc_stpncpy
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcoll_l)(char const *s1, char const *s2, locale_t locale);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBCCALL libc_strxfrm_l)(char *dst, char const *__restrict src, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_LEAF NONNULL((2, 3)) char *NOTHROW_NCX(LIBCCALL libc_strtok_r)(char *string, char const *delim, char **__restrict save_ptr);
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strchrnul)(char const *__restrict haystack, int needle);
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBCCALL libc_basename)(char const *filename);
/* Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcasestr)(char const *haystack, char const *needle);
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strverscmp)(char const *s1, char const *s2);
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
#define libc___mempcpy libc_mempcpy
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strfry)(char *__restrict string);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memfrob)(void *buf, size_t num_bytes);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcasecmp_l)(char const *s1, char const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecmp_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strsep)(char **__restrict stringp, char const *__restrict delim);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcasecmp)(char const *s1, char const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecmp)(char const *s1, char const *s2, size_t maxlen);
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_ffs)(int i);
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_ffsl)(long i);
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_ffsll)(__LONGLONG i);
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strlcat)(char *__restrict dst, char const *__restrict src, size_t bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strlcpy)(char *__restrict dst, char const *__restrict src, size_t bufsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memccpy)(void *__restrict dst, void const *__restrict src, int needle, size_t num_bytes);
#define libc___bzero libc_bzero
#define libc___strtok_r libc_strtok_r
/* Same as `memchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memrchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `rawmemchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemxchr)(void const *__restrict haystack, int needle);
/* Same as `rawmemrchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemrxchr)(void const *__restrict haystack, int needle);
/* Same as `memend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memxend)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memrend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrxend)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `memrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
/* Same as `rawmemlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlen)(void const *__restrict haystack, int needle);
/* Same as `rawmemrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlen)(void const *__restrict haystack, int needle);
/* Same as `memchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memxchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memxchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `memrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrxchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrxchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `rawmemchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `rawmemchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Same as `rawmemrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `rawmemrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Same as `memendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memxendw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_bytes);
/* Same as `memendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memxendl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_bytes);
/* Same as `memrendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrxendw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memrendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrxendl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `memlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `memrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word, size_t n_words);
/* Same as `memrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword, size_t n_dwords);
/* Same as `rawmemlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `rawmemlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Same as `rawmemrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenw)(/*aligned(2)*/ void const *__restrict haystack, uint16_t word);
/* Same as `rawmemrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenl)(/*aligned(4)*/ void const *__restrict haystack, uint32_t dword);
/* Same as `memchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memxchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `memrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrxchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `rawmemchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Same as `rawmemrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Same as `memendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memxendq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_bytes);
/* Same as `memrendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrxendq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `memlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `memrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword, size_t n_qwords);
/* Same as `rawmemlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Same as `rawmemrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenq)(/*aligned(8)*/ void const *__restrict haystack, uint64_t qword);
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memcpyc)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size);
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempcpyc)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size);
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmovec)(void *dst, void const *src, size_t elem_count, size_t elem_size);
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmovec)(void *dst, void const *src, size_t elem_count, size_t elem_size);
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmoveupc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmoveupc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmovedownc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmovedownc)(void *dst, void const *src, size_t elem_count, size_t elem_size);
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnchr)(char const *__restrict haystack, int needle, size_t maxlen);
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrchr)(char const *__restrict haystack, int needle, size_t maxlen);
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strrchrnul)(char const *__restrict haystack, int needle);
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_stroff)(char const *__restrict haystack, int needle);
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strroff)(char const *__restrict haystack, int needle);
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnoff)(char const *__restrict haystack, int needle, size_t maxlen);
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnroff)(char const *__restrict haystack, int needle, size_t maxlen);
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memrmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_memcasecmp)(void const *s1, void const *s2, size_t n_bytes);
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memcasemem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_memcasecmp_l)(void const *s1, void const *s2, size_t n_bytes, locale_t locale);
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE ATTR_PURE WUNUSED NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memcasemem_l)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcasestr_l)(char const *haystack, char const *needle, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wildstrcmp)(char const *pattern, char const *string);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp)(char const *pattern, char const *string);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strcmp)(char const *s1, char const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strncmp)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp)(char const *s1, char const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmp)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp_l)(char const *s1, char const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp_l)(char const *s1, size_t s1_maxlen, char const *s2, size_t s2_maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp_l)(char const *pattern, char const *string, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp_l)(void const *s1, size_t s1_bytes, void const *s2, size_t s2_bytes, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpw)(void const *s1, size_t s1_words, void const *s2, size_t s2_words);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpl)(void const *s1, size_t s1_dwords, void const *s2, size_t s2_dwords);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) size_t NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpq)(void const *s1, size_t s1_qwords, void const *s2, size_t s2_qwords);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncoll)(char const *s1, char const *s2, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcasecoll)(char const *s1, char const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecoll)(char const *s1, char const *s2, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrev)(char *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnlwr)(char *__restrict str, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnupr)(char *__restrict str, size_t maxlen);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncoll_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcasecoll_l)(char const *s1, char const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecoll_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strlwr_l)(char *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strupr_l)(char *__restrict str, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnlwr_l)(char *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnupr_l)(char *__restrict str, size_t maxlen, locale_t locale);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrev)(void *__restrict base, size_t n_bytes);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrevw)(void *__restrict base, size_t n_words);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrevl)(void *__restrict base, size_t n_dwords);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrevq)(void *__restrict base, size_t n_qwords);
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strlwr)(char *__restrict str);
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strupr)(char *__restrict str);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strset)(char *__restrict str, int ch);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnset)(char *__restrict str, int ch, size_t maxlen);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strrev)(char *__restrict str);
#define libc__memccpy libc_memccpy
#define libc__memicmp libc_memcasecmp
#define libc__memicmp_l libc_memcasecmp_l
#define libc_memicmp libc_memcasecmp
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__strset_s)(char *dst, size_t dstsize, int ch);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_memcpy_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_memmove_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strcpy_s)(char *dst, size_t dstsize, char const *src);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strcat_s)(char *dst, size_t dstsize, char const *src);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strncat_s)(char *dst, rsize_t dstsize, const char *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strncpy_s)(char *dst, size_t dstsize, char const *src, size_t maxlen);
#define libc_strtok_s libc_strtok_r
#define libc__stricmp libc_strcasecmp
#define libc__strcmpi libc_strcasecmp
#define libc__stricmp_l libc_strcasecmp_l
#define libc__strcoll_l libc_strcoll_l
#define libc__stricoll libc_strcasecoll
#define libc__stricoll_l libc_strcasecoll_l
#define libc__strncoll libc_strncoll
#define libc__strncoll_l libc_strncoll_l
#define libc__strnicoll libc_strncasecoll
#define libc__strnicoll_l libc_strncasecoll_l
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strlwr_s)(char *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strupr_s)(char *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strlwr_s_l)(char *buf, size_t buflen, locale_t locale);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strupr_s_l)(char *buf, size_t buflen, locale_t locale);
#define libc__strnicmp libc_strncasecmp
#define libc__strnicmp_l libc_strncasecmp_l
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strnset_s)(char *__restrict buf, size_t buflen, int ch, size_t maxlen);
#define libc__strrev libc_strrev
#define libc__strxfrm_l libc_strxfrm_l
#define libc_stricmp libc_strcasecmp
#define libc_strcmpi libc_strcasecmp
#define libc_strnicmp libc_strncasecmp
#define libc__strncmpi libc_strncasecmp
#define libc__strncmpi_l libc_strncasecmp_l
#define libc_strncmpi libc_strncasecmp
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strnstr)(char const *haystack, char const *needle, size_t haystack_maxlen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STRING_H */
