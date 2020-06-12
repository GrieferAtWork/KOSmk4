/* HASH CRC-32:0x15f53354 */
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

#ifndef LIBC_ARCH_HAVE_MEMCPY
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMCPY */
#ifndef LIBC_ARCH_HAVE_MEMMOVE
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmove)(void *dst, void const *src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMMOVE */
#ifndef LIBC_ARCH_HAVE_MEMSET
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memset)(void *__restrict dst, int byte, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMSET */
#ifndef LIBC_ARCH_HAVE_MEMCMP
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_memcmp)(void const *s1, void const *s2, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMCMP */
#ifndef LIBC_ARCH_HAVE_MEMCHR
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMCHR */
#ifndef LIBC_ARCH_HAVE_STRLEN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strlen)(char const *__restrict string);
#endif /* !LIBC_ARCH_HAVE_STRLEN */
#ifndef LIBC_ARCH_HAVE_STRCHR
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strchr)(char const *__restrict haystack, int needle);
#endif /* !LIBC_ARCH_HAVE_STRCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRRCHR)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strrchr)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRRCHR */
#ifndef LIBC_ARCH_HAVE_STRCMP
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcmp)(char const *s1, char const *s2);
#endif /* !LIBC_ARCH_HAVE_STRCMP */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCMP)
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncmp)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCMP */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRSTR)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strstr)(char const *haystack, char const *needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRSTR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCPY)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcpy)(char *__restrict buf, char const *__restrict src);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCPY)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCAT)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcat)(char *__restrict buf, char const *__restrict src);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCAT */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCAT)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strncat)(char *__restrict buf, char const *__restrict src, size_t buflen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCAT */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCSPN)
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strcspn)(char const *haystack, char const *reject);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCSPN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRSPN)
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strspn)(char const *haystack, char const *accept);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRSPN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRPBRK)
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strpbrk)(char const *haystack, char const *accept);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRPBRK */
#ifndef __KERNEL__
INTDEF NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_strtok)(char *string, char const *delim);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCOLL)
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcoll)(char const *s1, char const *s2);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCOLL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRXFRM)
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBCCALL libc_strxfrm)(char *dst, char const *__restrict src, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRXFRM */
#ifndef __KERNEL__
INTDEF ATTR_COLD ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strerror)(int errnum);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRNLEN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnlen)(char const *__restrict string, size_t maxlen);
#endif /* !LIBC_ARCH_HAVE_STRNLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STPCPY)
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_stpcpy)(char *__restrict buf, char const *__restrict src);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STPCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STPNCPY)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_stpncpy)(char *__restrict buf, char const *__restrict src, size_t buflen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STPNCPY */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcoll_l)(char const *s1, char const *s2, locale_t locale);
INTDEF NONNULL((2)) size_t NOTHROW_NCX(LIBCCALL libc_strxfrm_l)(char *dst, char const *__restrict src, size_t maxlen, locale_t locale);
INTDEF ATTR_COLD WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strerror_l)(int errnum, locale_t locale);
INTDEF ATTR_COLD ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_strsignal)(int signo);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strndup)(char const *__restrict string, size_t max_chars);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strdup)(char const *__restrict string);
INTDEF ATTR_LEAF NONNULL((2, 3)) char *NOTHROW_NCX(LIBCCALL libc_strtok_r)(char *string, char const *delim, char **__restrict save_ptr);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMRCHR
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMRCHR */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHR
/* Same as `memchr' with a search limit of `(size_t)-1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemchr)(void const *__restrict haystack, int needle);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCHRNUL)
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strchrnul)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCHRNUL */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED char *NOTHROW_NCX(LIBCCALL libc_basename)(char const *filename);
/* Same as `strstr', but ignore casing */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcasestr)(char const *haystack, char const *needle);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMMEM)
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMMEM */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strverscmp)(char const *s1, char const *s2);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMPCPY
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempcpy)(void *__restrict dst, void const *__restrict src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPCPY */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strfry)(char *__restrict string);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memfrob)(void *buf, size_t num_bytes);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcasecmp_l)(char const *s1, char const *s2, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecmp_l)(char const *s1, char const *s2, size_t maxlen, locale_t locale);
INTDEF ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *NOTHROW_NCX(LIBCCALL libc_strerror_r)(int errnum, char *buf, size_t buflen);
INTDEF ATTR_COLD NONNULL((2)) errno_t NOTHROW_NCX(LIBCCALL libc___xpg_strerror_r)(int errnum, char *buf, size_t buflen);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strsep)(char **__restrict stringp, char const *__restrict delim);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strcasecmp)(char const *s1, char const *s2);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_strncasecmp)(char const *s1, char const *s2, size_t maxlen);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_FFS)
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_ffs)(int i);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_FFS */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_FFSL)
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_ffsl)(long i);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_FFSL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_FFSLL)
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_ffsll)(__LONGLONG i);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_FFSLL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRLCAT)
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strlcat)(char *__restrict dst, char const *__restrict src, size_t bufsize);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRLCAT */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRLCPY)
INTDEF ATTR_LEAF NONNULL((1, 2)) size_t NOTHROW_NCX(LIBCCALL libc_strlcpy)(char *__restrict dst, char const *__restrict src, size_t bufsize);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRLCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMCCPY)
INTDEF ATTR_LEAF NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memccpy)(void *__restrict dst, void const *__restrict src, int needle, size_t num_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMCCPY */
#ifndef LIBC_ARCH_HAVE_MEMCPYW
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memcpyw)(void *__restrict dst, void const *__restrict src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMCPYW */
#ifndef LIBC_ARCH_HAVE_MEMPCPYW
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempcpyw)(void *__restrict dst, void const *__restrict src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMPCPYW */
#ifndef LIBC_ARCH_HAVE_MEMCPYL
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memcpyl)(void *__restrict dst, void const *__restrict src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMCPYL */
#ifndef LIBC_ARCH_HAVE_MEMPCPYL
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempcpyl)(void *__restrict dst, void const *__restrict src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMPCPYL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEW
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmovew)(void *dst, void const *src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEW
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmovew)(void *dst, void const *src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEL
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmovel)(void *dst, void const *src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEL
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmovel)(void *dst, void const *src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPW
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmoveupw)(void *dst, void const *src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNW
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memmovedownw)(void *dst, void const *src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPW
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupw)(void *dst, void const *src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNW
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownw)(void *dst, void const *src, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPL
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmoveupl)(void *dst, void const *src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNL
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memmovedownl)(void *dst, void const *src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPL
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupl)(void *dst, void const *src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNL
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownl)(void *dst, void const *src, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMSETW
/* Fill memory with a given word */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memsetw)(void *__restrict dst, uint16_t word, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMSETW */
#ifndef LIBC_ARCH_HAVE_MEMPSETW
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_mempsetw)(void *__restrict dst, uint16_t word, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMPSETW */
#ifndef LIBC_ARCH_HAVE_MEMSETL
/* Fill memory with a given dword */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memsetl)(void *__restrict dst, uint32_t dword, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMSETL */
#ifndef LIBC_ARCH_HAVE_MEMPSETL
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_mempsetl)(void *__restrict dst, uint32_t dword, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMPSETL */
#ifndef LIBC_ARCH_HAVE_MEMCMPW
/* Compare memory buffers and return the difference of the first non-matching word */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int16_t NOTHROW_NCX(LIBCCALL libc_memcmpw)(void const *s1, void const *s2, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMCMPW */
#ifndef LIBC_ARCH_HAVE_MEMCMPL
/* Compare memory buffers and return the difference of the first non-matching dword */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int32_t NOTHROW_NCX(LIBCCALL libc_memcmpl)(void const *s1, void const *s2, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMCMPL */
#ifndef LIBC_ARCH_HAVE_MEMCHRW
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memchrw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMCHRW */
#ifndef LIBC_ARCH_HAVE_MEMCHRL
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memchrl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMCHRL */
#ifndef LIBC_ARCH_HAVE_MEMRCHRW
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrchrw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMRCHRW */
#ifndef LIBC_ARCH_HAVE_MEMRCHRL
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrchrl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMRCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRW
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrw)(void const *__restrict haystack, uint16_t word);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRL
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrl)(void const *__restrict haystack, uint32_t dword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRW
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrw)(void const *__restrict haystack, uint16_t word);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRL
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrl)(void const *__restrict haystack, uint32_t dword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRL */
#ifndef LIBC_ARCH_HAVE_MEMENDW
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memendw)(void const *__restrict haystack, uint16_t word, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMENDW */
#ifndef LIBC_ARCH_HAVE_MEMENDL
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memendl)(void const *__restrict haystack, uint32_t dword, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMENDL */
#ifndef LIBC_ARCH_HAVE_MEMRENDW
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrendw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMRENDW */
#ifndef LIBC_ARCH_HAVE_MEMRENDL
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrendl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMRENDL */
#ifndef LIBC_ARCH_HAVE_MEMLENW
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlenw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMLENW */
#ifndef LIBC_ARCH_HAVE_MEMLENL
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 4' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlenl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMLENL */
#ifndef LIBC_ARCH_HAVE_MEMRLENW
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlenw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !LIBC_ARCH_HAVE_MEMRLENW */
#ifndef LIBC_ARCH_HAVE_MEMRLENL
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlenl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMRLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENW
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenw)(void const *__restrict haystack, uint16_t word);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENL
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenl)(void const *__restrict haystack, uint32_t dword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENW
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenw)(void const *__restrict haystack, uint16_t word);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENL
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenl)(void const *__restrict haystack, uint32_t dword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENL */
#ifndef LIBC_ARCH_HAVE_MEMCPYQ
/* Copy memory between non-overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memcpyq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMPCPYQ
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempcpyq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMPCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEQ
/* Move memory between potentially overlapping memory blocks. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmoveq)(void *dst, void const *src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEQ
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmoveq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPQ
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmoveupq)(void *dst, void const *src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNQ
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memmovedownq)(void *dst, void const *src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPQ
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmoveupq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNQ
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempmovedownq)(void *__restrict dst, void const *__restrict src, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMSETQ
/* Fill memory with a given qword */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memsetq)(void *__restrict dst, uint64_t qword, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMSETQ */
#ifndef LIBC_ARCH_HAVE_MEMPSETQ
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_mempsetq)(void *__restrict dst, uint64_t qword, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMPSETQ */
#ifndef LIBC_ARCH_HAVE_MEMCMPQ
/* Compare memory buffers and return the difference of the first non-matching qword */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) int64_t NOTHROW_NCX(LIBCCALL libc_memcmpq)(void const *s1, void const *s2, size_t n_dwords);
#endif /* !LIBC_ARCH_HAVE_MEMCMPQ */
#ifndef LIBC_ARCH_HAVE_MEMCHRQ
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memchrq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMRCHRQ
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrchrq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRQ
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemchrq)(void const *__restrict haystack, uint64_t qword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRQ
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemrchrq)(void const *__restrict haystack, uint64_t qword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMENDQ
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memendq)(void const *__restrict haystack, uint64_t qword, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMENDQ */
#ifndef LIBC_ARCH_HAVE_MEMRENDQ
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrendq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMRENDQ */
#ifndef LIBC_ARCH_HAVE_MEMLENQ
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `N_QWORDS' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlenq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMLENQ */
#ifndef LIBC_ARCH_HAVE_MEMRLENQ
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlenq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !LIBC_ARCH_HAVE_MEMRLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENQ
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlenq)(void const *__restrict haystack, uint64_t qword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENQ
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlenq)(void const *__restrict haystack, uint64_t qword);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHR)
/* Same as `memchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHR)
/* Same as `memrchr', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrxchr)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHR)
/* Same as `rawmemchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemxchr)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHR)
/* Same as `rawmemrchr', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemrxchr)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXEND)
/* Same as `memend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memxend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXEND)
/* Same as `memrend', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrxend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLEN)
/* Same as `memlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLEN)
/* Same as `memrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLEN)
/* Same as `rawmemlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlen)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLEN)
/* Same as `rawmemrlen', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlen)(void const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHRW)
/* Same as `memchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memxchrw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHRL)
/* Same as `memchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memxchrl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHRW)
/* Same as `memrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrxchrw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHRL)
/* Same as `memrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrxchrl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHRW)
/* Same as `rawmemchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrw)(void const *__restrict haystack, uint16_t word);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHRL)
/* Same as `rawmemchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrl)(void const *__restrict haystack, uint32_t dword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHRW)
/* Same as `rawmemrchrw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrw)(void const *__restrict haystack, uint16_t word);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHRL)
/* Same as `rawmemrchrl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrl)(void const *__restrict haystack, uint32_t dword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXENDW)
/* Same as `memendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memxendw)(void const *__restrict haystack, uint16_t word, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXENDW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXENDL)
/* Same as `memendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memxendl)(void const *__restrict haystack, uint32_t dword, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXENDL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXENDW)
/* Same as `memrendw', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc_memrxendw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXENDW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXENDL)
/* Same as `memrendl', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc_memrxendl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXENDL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLENW)
/* Same as `memlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlenw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLENL)
/* Same as `memlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlenl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLENW)
/* Same as `memrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenw)(void const *__restrict haystack, uint16_t word, size_t n_words);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLENL)
/* Same as `memrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenl)(void const *__restrict haystack, uint32_t dword, size_t n_dwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLENW)
/* Same as `rawmemlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenw)(void const *__restrict haystack, uint16_t word);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLENL)
/* Same as `rawmemlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenl)(void const *__restrict haystack, uint32_t dword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLENW)
/* Same as `rawmemrlenw', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenw)(void const *__restrict haystack, uint16_t word);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLENL)
/* Same as `rawmemrlenl', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenl)(void const *__restrict haystack, uint32_t dword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHRQ)
/* Same as `memchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memxchrq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHRQ)
/* Same as `memrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrxchrq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHRQ)
/* Same as `rawmemchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemxchrq)(void const *__restrict haystack, uint64_t qword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHRQ)
/* Same as `rawmemrchrq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_rawmemrxchrq)(void const *__restrict haystack, uint64_t qword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXENDQ)
/* Same as `memendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memxendq)(void const *__restrict haystack, uint64_t qword, size_t n_bytes);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXENDQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXENDQ)
/* Same as `memrendq', but search for non-matching locations. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc_memrxendq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXENDQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLENQ)
/* Same as `memlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memxlenq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLENQ)
/* Same as `memrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrxlenq)(void const *__restrict haystack, uint64_t qword, size_t n_qwords);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLENQ)
/* Same as `rawmemlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemxlenq)(void const *__restrict haystack, uint64_t qword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLENQ)
/* Same as `rawmemrlenq', but search for non-matching locations. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrxlenq)(void const *__restrict haystack, uint64_t qword);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLENQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUP
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmoveup)(void *dst, void const *src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWN
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_memmovedown)(void *dst, void const *src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWN */
#ifndef __KERNEL__
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
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STREND
/* Same as `STR + strlen(STR)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strend)(char const *__restrict string);
#endif /* !LIBC_ARCH_HAVE_STREND */
#ifndef LIBC_ARCH_HAVE_STRNEND
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnend)(char const *__restrict string, size_t maxlen);
#endif /* !LIBC_ARCH_HAVE_STRNEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCHR)
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnchr)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNRCHR)
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrchr)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNRCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRRCHRNUL)
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strrchrnul)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRRCHRNUL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCHRNUL)
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCHRNUL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNRCHRNUL)
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_strnrchrnul)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNRCHRNUL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STROFF)
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_stroff)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STROFF */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRROFF)
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strroff)(char const *__restrict haystack, int needle);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRROFF */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNOFF)
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnoff)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNOFF */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNROFF)
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_strnroff)(char const *__restrict haystack, int needle, size_t maxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNROFF */
#ifndef LIBC_ARCH_HAVE_MEMPSET
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempset)(void *__restrict dst, int byte, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPSET */
#ifndef LIBC_ARCH_HAVE_MEMPMOVE
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmove)(void *dst, void const *src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVE */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUP
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmoveup)(void *dst, void const *src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWN
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_mempmovedown)(void *dst, void const *src, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHR
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_rawmemrchr)(void const *__restrict haystack, int needle);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHR */
#ifndef LIBC_ARCH_HAVE_MEMEND
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMEND */
#ifndef LIBC_ARCH_HAVE_MEMREND
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_memrend)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMREND */
#ifndef LIBC_ARCH_HAVE_MEMLEN
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMLEN */
#ifndef LIBC_ARCH_HAVE_MEMRLEN
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_memrlen)(void const *__restrict haystack, int needle, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMRLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMLEN
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemlen)(void const *__restrict haystack, int needle);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLEN
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_rawmemrlen)(void const *__restrict haystack, int needle);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRMEM)
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memrmem)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRMEM */
#ifndef LIBC_ARCH_HAVE_MEMPATW
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatw)(void *__restrict dst, uint16_t pattern, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPATW */
#ifndef LIBC_ARCH_HAVE_MEMPATL
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatl)(void *__restrict dst, uint32_t pattern, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPATL */
#ifndef LIBC_ARCH_HAVE_MEMPATQ
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_mempatq)(void *__restrict dst, uint64_t pattern, size_t n_bytes);
#endif /* !LIBC_ARCH_HAVE_MEMPATQ */
#ifndef __KERNEL__
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
INTDEF ATTR_PURE WUNUSED NONNULL((1, 3)) void *NOTHROW_NCX(LIBCCALL libc_memcasemem_l)(void const *haystack, size_t haystacklen, void const *needle, size_t needlelen, locale_t locale);
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strcasestr_l)(char const *haystack, char const *needle, locale_t locale);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(LIBCCALL libc_vstrdupf)(char const *__restrict format, va_list args);
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *NOTHROW_NCX(VLIBCCALL libc_strdupf)(char const *__restrict format, ...);
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
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__strset_s)(char *dst, size_t dstsize, int ch);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_memcpy_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc_memmove_s)(void *dst, rsize_t dstlength, void const *src, rsize_t srclength);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strcpy_s)(char *dst, size_t dstsize, char const *src);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strcat_s)(char *dst, size_t dstsize, char const *src);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strncat_s)(char *dst, rsize_t dstsize, const char *src, rsize_t maxlen);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_strncpy_s)(char *dst, size_t dstsize, char const *src, size_t maxlen);
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc__strerror)(char const *message);
INTDEF NONNULL((1)) errno_t NOTHROW_RPC(LIBCCALL libc__strerror_s)(char *__restrict buf, size_t buflen, char const *message);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strlwr_s)(char *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strupr_s)(char *buf, size_t buflen);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strlwr_s_l)(char *buf, size_t buflen, locale_t locale);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strupr_s_l)(char *buf, size_t buflen, locale_t locale);
INTDEF ATTR_LEAF errno_t NOTHROW_NCX(LIBCCALL libc__strnset_s)(char *__restrict buf, size_t buflen, int ch, size_t maxlen);
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
INTDEF ATTR_PURE WUNUSED NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_strnstr)(char const *haystack, char const *needle, size_t haystack_maxlen);
/* Generate a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4]  = mode & S_IRGRP ? 'r' : '-';
 *    p[5]  = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7]  = mode & S_IROTH ? 'r' : '-';
 *    p[8]  = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
INTDEF NONNULL((2)) void NOTHROW_NCX(LIBCCALL libc_strmode)(mode_t mode, char p[12]);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STRING_H */
