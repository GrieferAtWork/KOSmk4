/* HASH CRC-32:0x16722000 */
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
#ifndef GUARD_LIBC_AUTO_STRING_C
#define GUARD_LIBC_AUTO_STRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

DECL_BEGIN

/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcpy") void *
NOTHROW_NCX(LIBCCALL libc_memcpy)(void *__restrict dst,
                                  void const *__restrict src,
                                  size_t n_bytes) {
#line 138 "kos/src/libc/magic/string.c"
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}

/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memmove") void *
NOTHROW_NCX(LIBCCALL libc_memmove)(void *dst,
                                   void const *src,
                                   size_t n_bytes) {
#line 148 "kos/src/libc/magic/string.c"
	byte_t *pdst, *psrc;
	if (dst < src) {
		pdst = (byte_t *)dst;
		psrc = (byte_t *)src;
		while (n_bytes--)
			*pdst++ = *psrc++;
	} else {
		pdst = (byte_t *)dst + n_bytes;
		psrc = (byte_t *)src + n_bytes;
		while (n_bytes--)
			*--pdst = *--psrc;
	}
	return dst;
}

/* Fill memory with a given byte */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memset") void *
NOTHROW_NCX(LIBCCALL libc_memset)(void *__restrict dst,
                                  int byte,
                                  size_t n_bytes) {
#line 166 "kos/src/libc/magic/string.c"
	byte_t *pdst = (byte_t *)dst;
	while (n_bytes--)
		*pdst++ = (byte_t)byte;
	return dst;
}

/* Compare memory buffers and return the difference of the first non-matching byte */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcmp") int
NOTHROW_NCX(LIBCCALL libc_memcmp)(void const *s1,
                                  void const *s2,
                                  size_t n_bytes) {
#line 176 "kos/src/libc/magic/string.c"
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes-- && ((v1 = *p1++) == (v2 = *p2++)));
	return (int)v1 - (int)v2;
}

/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memchr") void *
NOTHROW_NCX(LIBCCALL libc_memchr)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
#line 190 "kos/src/libc/magic/string.c"
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter == (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}

/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strlen") size_t
NOTHROW_NCX(LIBCCALL libc_strlen)(char const *__restrict string) {
#line 206 "kos/src/libc/magic/string.c"
	return (size_t)(libc_strend(string) - string);
}

/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strchr") char *
NOTHROW_NCX(LIBCCALL libc_strchr)(char const *__restrict haystack,
                                  int needle) {
#line 216 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack)
		if (*haystack == (char)needle)
			return (char *)haystack;
	return NULL;
}

/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strcmp") int
NOTHROW_NCX(LIBCCALL libc_strcmp)(char const *s1,
                                  char const *s2) {
#line 238 "kos/src/libc/magic/string.c"
	char c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnlen") size_t
NOTHROW_NCX(LIBCCALL libc_strnlen)(char const *__restrict string,
                                   size_t maxlen) {
#line 398 "kos/src/libc/magic/string.c"
	return (size_t)(libc_strnend(string, maxlen) - string);
}

/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrchr") void *
NOTHROW_NCX(LIBCCALL libc_memrchr)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
#line 516 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if (*--iter == (byte_t)needle)
			return iter;
	}
	return NULL;
}

/* Same as `memchr' with a search limit of `(size_t)-1' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemchr") void *
NOTHROW_NCX(LIBCCALL libc_rawmemchr)(void const *__restrict haystack,
                                     int needle) {
#line 531 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if (*iter == (byte_t)needle)
			break;
	}
	return iter;
}

/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally. */
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memmem") void *
NOTHROW_NCX(LIBCCALL libc_memmem)(void const *haystack,
                                  size_t haystacklen,
                                  void const *needle,
                                  size_t needlelen) {
#line 617 "kos/src/libc/magic/string.c"
	byte_t *candidate, marker;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = *(byte_t *)needle;
	while ((candidate = (byte_t *)memchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

/* Same as `memcpy', but return `DST+N_BYTES', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempcpy") void *
NOTHROW_NCX(LIBCCALL libc_mempcpy)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_bytes) {
#line 685 "kos/src/libc/magic/string.c"
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return pdst;
}

/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcpyw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memcpyw)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_words) {
#line 893 "kos/src/libc/magic/string.c"
	u16 *pdst = (u16 *)dst;
	u16 *psrc = (u16 *)src;
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}

/* Same as `memcpyw', but return `DST+N_WORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempcpyw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyw)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_words) {
#line 904 "kos/src/libc/magic/string.c"
	return (u16 *)memcpyw(dst, src, n_words) + n_words;
}

/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcpyl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memcpyl)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_dwords) {
#line 911 "kos/src/libc/magic/string.c"
	u32 *pdst = (u32 *)dst;
	u32 *psrc = (u32 *)src;
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}

/* Same as `memcpyl', but return `DST+N_DWORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempcpyl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyl)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_dwords) {
#line 922 "kos/src/libc/magic/string.c"
	return (u32 *)memcpyl(dst, src, n_dwords) + n_dwords;
}

/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memmovew") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memmovew)(void *dst,
                                    void const *src,
                                    size_t n_words) {
#line 938 "kos/src/libc/magic/string.c"
	u16 *pdst, *psrc;
	if (dst < src) {
		psrc = (u16 *)src;
		pdst = (u16 *)dst;
		while (n_words--)
			*pdst++ = *psrc++;
	} else {
		psrc = (u16 *)src + n_words;
		pdst = (u16 *)dst + n_words;
		while (n_words--)
			*--pdst = *--psrc;
	}
	return (u16 *)dst;
}

/* Same as `memmovew', but return `DST+N_WORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempmovew") uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempmovew)(void *__restrict dst,
                                     void const *__restrict src,
                                     size_t n_words) {
#line 956 "kos/src/libc/magic/string.c"
	return (u16 *)memmovew(dst, src, n_words) + n_words;
}

/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memmovel") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memmovel)(void *dst,
                                    void const *src,
                                    size_t n_dwords) {
#line 963 "kos/src/libc/magic/string.c"
	u32 *pdst, *psrc;
	if (dst < src) {
		psrc = (u32 *)src;
		pdst = (u32 *)dst;
		while (n_dwords--)
			*pdst++ = *psrc++;
	} else {
		psrc = (u32 *)src + n_dwords;
		pdst = (u32 *)dst + n_dwords;
		while (n_dwords--)
			*--pdst = *--psrc;
	}
	return (u32 *)dst;
}

/* Same as `memmovew', but return `DST+N_DWORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempmovel") uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempmovel)(void *__restrict dst,
                                     void const *__restrict src,
                                     size_t n_dwords) {
#line 981 "kos/src/libc/magic/string.c"
	return (u32 *)memmovel(dst, src, n_dwords) + n_dwords;
}

/* Fill memory with a given word */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memsetw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memsetw)(void *__restrict dst,
                                   uint16_t word,
                                   size_t n_words) {
#line 995 "kos/src/libc/magic/string.c"
	u16 *pdst = (u16 *)dst;
	while (n_words--)
		*pdst++ = word;
	return (u16 *)dst;
}

/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempsetw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempsetw)(void *__restrict dst,
                                    uint16_t word,
                                    size_t n_words) {
#line 1004 "kos/src/libc/magic/string.c"
	return (u16 *)memsetw(dst, word, n_words) + n_words;
}

/* Fill memory with a given dword */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memsetl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memsetl)(void *__restrict dst,
                                   uint32_t dword,
                                   size_t n_dwords) {
#line 1010 "kos/src/libc/magic/string.c"
	u32 *pdst = (u32 *)dst;
	while (n_dwords--)
		*pdst++ = dword;
	return (u32 *)dst;
}

/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempsetl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempsetl)(void *__restrict dst,
                                    uint32_t dword,
                                    size_t n_dwords) {
#line 1019 "kos/src/libc/magic/string.c"
	return (u32 *)memsetl(dst, dword, n_dwords) + n_dwords;
}

/* Compare memory buffers and return the difference of the first non-matching word */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcmpw") int16_t
NOTHROW_NCX(LIBCCALL libc_memcmpw)(void const *s1,
                                   void const *s2,
                                   size_t n_words) {
#line 1031 "kos/src/libc/magic/string.c"
	s16 *p1 = (s16 *)s1;
	s16 *p2 = (s16 *)s2;
	s16 v1, v2;
	v1 = v2 = 0;
	while (n_words-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

/* Compare memory buffers and return the difference of the first non-matching dword */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcmpl") int32_t
NOTHROW_NCX(LIBCCALL libc_memcmpl)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
#line 1043 "kos/src/libc/magic/string.c"
	s32 *p1 = (s32 *)s1;
	s32 *p2 = (s32 *)s2;
	s32 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memchrw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_words) {
#line 1065 "kos/src/libc/magic/string.c"
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter == word)
			return hay_iter;
	}
	return NULL;
}

/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memchrl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_dwords) {
#line 1080 "kos/src/libc/magic/string.c"
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter == dword)
			return hay_iter;
	}
	return NULL;
}

/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_WORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrchrw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
#line 1101 "kos/src/libc/magic/string.c"
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter == word)
			return iter;
	}
	return NULL;
}

/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_DWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrchrl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
#line 1115 "kos/src/libc/magic/string.c"
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter == dword)
			return iter;
	}
	return NULL;
}

/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrw)(void const *__restrict haystack,
                                      uint16_t word) {
#line 1136 "kos/src/libc/magic/string.c"
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == word)
			break;
	}
	return iter;
}

/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrl)(void const *__restrict haystack,
                                      uint32_t dword) {
#line 1150 "kos/src/libc/magic/string.c"
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == dword)
			break;
	}
	return iter;
}

/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK-2' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrw)(void const *__restrict haystack,
                                       uint16_t word) {
#line 1172 "kos/src/libc/magic/string.c"
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter == word)
			break;
	}
	return iter;
}

/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK-4' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrl)(void const *__restrict haystack,
                                       uint32_t dword) {
#line 1186 "kos/src/libc/magic/string.c"
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter == dword)
			break;
	}
	return iter;
}

/* Same as `memchrw', but return `HAYSTACK+N_WORDS', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memendw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memendw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_bytes) {
#line 1208 "kos/src/libc/magic/string.c"
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == word)
			break;
	}
	return result;
}

/* Same as `memchrl', but return `HAYSTACK+N_DWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memendl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memendl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_bytes) {
#line 1222 "kos/src/libc/magic/string.c"
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == dword)
			break;
	}
	return result;
}

/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrendw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrendw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
#line 1243 "kos/src/libc/magic/string.c"
	u16 *result = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--result == word)
			break;
	}
	return result;
}

/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrendl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrendl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
#line 1257 "kos/src/libc/magic/string.c"
	u32 *result = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--result == dword)
			break;
	}
	return result;
}

/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memlenw") size_t
NOTHROW_NCX(LIBCCALL libc_memlenw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_words) {
#line 1274 "kos/src/libc/magic/string.c"
	return (size_t)(memendw(haystack, word, n_words) - (u16 *)haystack);
}

/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memlenl") size_t
NOTHROW_NCX(LIBCCALL libc_memlenl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_dwords) {
#line 1280 "kos/src/libc/magic/string.c"
	return (size_t)(memendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrlenw") size_t
NOTHROW_NCX(LIBCCALL libc_memrlenw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
#line 1290 "kos/src/libc/magic/string.c"
	return (size_t)(memrendw(haystack, word, n_words) - (u16 *)haystack);
}

/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrlenl") size_t
NOTHROW_NCX(LIBCCALL libc_memrlenl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
#line 1296 "kos/src/libc/magic/string.c"
	return (size_t)(memrendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemlenw") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenw)(void const *__restrict haystack,
                                      uint16_t word) {
#line 1308 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemchrw(haystack, word) - (u16 *)haystack);
}

/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemlenl") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenl)(void const *__restrict haystack,
                                      uint32_t dword) {
#line 1314 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemchrl(haystack, dword) - (u32 *)haystack);
}

/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrlenw") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenw)(void const *__restrict haystack,
                                       uint16_t word) {
#line 1325 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemrchrw(haystack, word) - (u16 *)haystack);
}

/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrlenl") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenl)(void const *__restrict haystack,
                                       uint32_t dword) {
#line 1331 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemrchrl(haystack, dword) - (u32 *)haystack);
}

/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcpyq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memcpyq)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_qwords) {
#line 1340 "kos/src/libc/magic/string.c"
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst = (u64 *)dst;
	u64 *psrc = (u64 *)src;
	while (n_qwords--)
		*pdst++ = *psrc++;
#else
	u32 *pdst = (u32 *)dst;
	u32 *psrc = (u32 *)src;
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
#endif
	return (u64 *)dst;
}

/* Same as `memcpyq', but return `DST+N_QWORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempcpyq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyq)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_qwords) {
#line 1359 "kos/src/libc/magic/string.c"
	return (u64 *)memcpyq(dst, src, n_qwords) + n_qwords;
}

/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memmoveq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memmoveq)(void *dst,
                                    void const *src,
                                    size_t n_qwords) {
#line 1365 "kos/src/libc/magic/string.c"
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	if (dst < src) {
		psrc = (u64 *)src;
		pdst = (u64 *)dst;
		while (n_qwords--)
			*pdst++ = *psrc++;
	} else {
		psrc = (u64 *)src + n_qwords;
		pdst = (u64 *)dst + n_qwords;
		while (n_qwords--)
			*--pdst = *--psrc;
	}
#else
	u32 *pdst, *psrc;
	if (dst < src) {
		psrc = (u32 *)src;
		pdst = (u32 *)dst;
		while (n_qwords--) {
			*pdst++ = *psrc++;
			*pdst++ = *psrc++;
		}
	} else {
		psrc = (u32 *)src + (n_qwords * 2);
		pdst = (u32 *)dst + (n_qwords * 2);
		while (n_qwords--) {
			*--pdst = *--psrc;
			*--pdst = *--psrc;
		}
	}
#endif
	return (u64 *)dst;
}

/* Same as `memmovew', but return `DST+N_QWORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempmoveq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveq)(void *__restrict dst,
                                     void const *__restrict src,
                                     size_t n_qwords) {
#line 1402 "kos/src/libc/magic/string.c"
	return (u64 *)memmoveq(dst, src, n_qwords) + n_qwords;
}

/* Fill memory with a given qword */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memsetq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memsetq)(void *__restrict dst,
                                   uint64_t qword,
                                   size_t n_qwords) {
#line 1408 "kos/src/libc/magic/string.c"
	u64 *pdst = (u64 *)dst;
	while (n_qwords--)
		*pdst++ = qword;
	return (u64 *)dst;
}

/* Same as `memsetq', but return `DST+N_QWORDS', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempsetq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempsetq)(void *__restrict dst,
                                    uint64_t qword,
                                    size_t n_qwords) {
#line 1417 "kos/src/libc/magic/string.c"
	return (u64 *)memsetq(dst, qword, n_qwords) + n_qwords;
}

/* Compare memory buffers and return the difference of the first non-matching qword */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memcmpq") int64_t
NOTHROW_NCX(LIBCCALL libc_memcmpq)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
#line 1423 "kos/src/libc/magic/string.c"
	s64 *p1 = (s64 *)s1;
	s64 *p2 = (s64 *)s2;
	s64 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}

/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memchrq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_qwords) {
#line 1437 "kos/src/libc/magic/string.c"
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter == (u64)qword)
			return hay_iter;
	}
	return NULL;
}

/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrchrq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
#line 1451 "kos/src/libc/magic/string.c"
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter == qword)
			return iter;
	}
	return NULL;
}

/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrq)(void const *__restrict haystack,
                                      uint64_t qword) {
#line 1465 "kos/src/libc/magic/string.c"
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == qword)
			break;
	}
	return iter;
}

/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK-8' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrq)(void const *__restrict haystack,
                                       uint64_t qword) {
#line 1479 "kos/src/libc/magic/string.c"
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter == qword)
			break;
	}
	return iter;
}

/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memendq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memendq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_bytes) {
#line 1493 "kos/src/libc/magic/string.c"
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == qword)
			break;
	}
	return result;
}

/* Same as `memrchrq', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrendq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrendq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
#line 1507 "kos/src/libc/magic/string.c"
	u64 *result = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--result == qword)
			break;
	}
	return result;
}

/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memlenq") size_t
NOTHROW_NCX(LIBCCALL libc_memlenq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_qwords) {
#line 1518 "kos/src/libc/magic/string.c"
	return (size_t)(memendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrlenq") size_t
NOTHROW_NCX(LIBCCALL libc_memrlenq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
#line 1524 "kos/src/libc/magic/string.c"
	return (size_t)(memrendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemlenq") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenq)(void const *__restrict haystack,
                                      uint64_t qword) {
#line 1530 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemchrq(haystack, qword) - (u64 *)haystack);
}

/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrlenq") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenq)(void const *__restrict haystack,
                                       uint64_t qword) {
#line 1536 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemrchrq(haystack, qword) - (u64 *)haystack);
}

/* Same as `STR+strlen(STR)' */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strend") char *
NOTHROW_NCX(LIBCCALL libc_strend)(char const *__restrict string) {
#line 2075 "kos/src/libc/magic/string.c"
	while (*string)
		++string;
	return (char *)string;
}

/* Same as `STR+strnlen(STR, MAX_CHARS)' */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnend") char *
NOTHROW_NCX(LIBCCALL libc_strnend)(char const *__restrict string,
                                   size_t maxlen) {
#line 2086 "kos/src/libc/magic/string.c"
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char *)string;
}

/* Same as `memset', but return `DST+N_BYTES', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempset") void *
NOTHROW_NCX(LIBCCALL libc_mempset)(void *__restrict dst,
                                   int byte,
                                   size_t n_bytes) {
#line 2181 "kos/src/libc/magic/string.c"
	return (void *)((byte_t *)memset(dst, byte, n_bytes) + n_bytes);
}

/* Same as `memmove', but return `DST+N_BYTES', rather than `DST' */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempmove") void *
NOTHROW_NCX(LIBCCALL libc_mempmove)(void *dst,
                                    void const *src,
                                    size_t n_bytes) {
#line 2187 "kos/src/libc/magic/string.c"
	return (void *)((byte_t *)memmove(dst, src, n_bytes) + n_bytes);
}

/* Same as `memrchr' without a search limit, starting at `HAYSTACK-1' */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrchr") void *
NOTHROW_NCX(LIBCCALL libc_rawmemrchr)(void const *__restrict haystack,
                                      int needle) {
#line 2196 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter == (byte_t)needle)
			break;
	}
	return iter;
}

/* Same as `memchr', but return `HAYSTACK+N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memend") void *
NOTHROW_NCX(LIBCCALL libc_memend)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
#line 2239 "kos/src/libc/magic/string.c"
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == (byte_t)needle)
			break;
	}
	return result;
}

/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrend") void *
NOTHROW_NCX(LIBCCALL libc_memrend)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
#line 2253 "kos/src/libc/magic/string.c"
	byte_t *result = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--result == (byte_t)needle)
			break;
	}
	return result;
}

/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memlen") size_t
NOTHROW_NCX(LIBCCALL libc_memlen)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
#line 2264 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)memend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrlen") size_t
NOTHROW_NCX(LIBCCALL libc_memrlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
#line 2270 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)memrend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemlen") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlen)(void const *__restrict haystack,
                                     int needle) {
#line 2276 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)libc_rawmemchr(haystack, needle) - (byte_t *)haystack);
}

/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrlen") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlen)(void const *__restrict haystack,
                                      int needle) {
#line 2282 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)libc_rawmemrchr(haystack, needle) - (byte_t *)haystack);
}

#include <hybrid/__wordbits.h>
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempatw") void *
NOTHROW_NCX(LIBCCALL libc_mempatw)(void *__restrict dst,
                                   uint16_t pattern,
                                   size_t n_bytes) {
#line 2294 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)dst;
	if (n_bytes && (uintptr_t)iter & 1) {
		*iter = __INT16_BYTE(pattern, 1);
		++iter;
		--n_bytes;
	}
	iter = (byte_t *)mempsetw(iter, pattern, n_bytes / 2);
	if (n_bytes & 1)
		*iter = __INT16_BYTE(pattern, 0);
	return dst;
}

#include <hybrid/__wordbits.h>
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempatl") void *
NOTHROW_NCX(LIBCCALL libc_mempatl)(void *__restrict dst,
                                   uint32_t pattern,
                                   size_t n_bytes) {
#line 2311 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 3; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	iter = (byte_t *)mempsetl(iter, pattern, n_bytes / 4);
	for (n_bytes &= 3; n_bytes; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	return dst;
}

#include <hybrid/__wordbits.h>
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.mempatq") void *
NOTHROW_NCX(LIBCCALL libc_mempatq)(void *__restrict dst,
                                   uint64_t pattern,
                                   size_t n_bytes) {
#line 2325 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 7; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	iter = (byte_t *)mempsetq(iter, pattern, n_bytes / 8);
	for (n_bytes &= 7; n_bytes; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	return dst;
}

#ifndef __KERNEL__
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strrchr") char *
NOTHROW_NCX(LIBCCALL libc_strrchr)(char const *__restrict haystack,
                                   int needle) {
#line 228 "kos/src/libc/magic/string.c"
	char const *result = NULL;
	for (; *haystack; ++haystack)
		if (*haystack == (char)needle)
			result = haystack;
	return (char *)result;
}

/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strncmp") int
NOTHROW_NCX(LIBCCALL libc_strncmp)(char const *s1,
                                   char const *s2,
                                   size_t maxlen) {
#line 249 "kos/src/libc/magic/string.c"
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strstr") char *
NOTHROW_NCX(LIBCCALL libc_strstr)(char const *haystack,
                                  char const *needle) {
#line 266 "kos/src/libc/magic/string.c"
	char const *hay2, *ned_iter;
	char ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			hay2 = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char *)haystack-1;
		}
miss:
		;
	}
	return NULL;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strcpy") char *
NOTHROW_NCX(LIBCCALL libc_strcpy)(char *__restrict buf,
                                  char const *__restrict src) {
#line 287 "kos/src/libc/magic/string.c"
	return (char *)memcpy(buf, src, (libc_strlen(src) + 1) * sizeof(char));
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strncpy") char *
NOTHROW_NCX(LIBCCALL libc_strncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
#line 291 "kos/src/libc/magic/string.c"
	size_t srclen = libc_strnlen(src, buflen);
	memcpy(buf, src, srclen * sizeof(char));
	memset(buf+srclen, '\0', (buflen - srclen) * sizeof(char));
	return buf;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strcat") char *
NOTHROW_NCX(LIBCCALL libc_strcat)(char *__restrict buf,
                                  char const *__restrict src) {
#line 298 "kos/src/libc/magic/string.c"
	memcpy(libc_strend(buf), src, (libc_strlen(src) + 1) * sizeof(char));
	return buf;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strncat") char *
NOTHROW_NCX(LIBCCALL libc_strncat)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
#line 303 "kos/src/libc/magic/string.c"
	size_t srclen = libc_strnlen(src, buflen);
	char *dst = libc_strend(buf);
	memcpy(dst, src, srclen * sizeof(char));
	dst[srclen] = '\0';
	return buf;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strcspn") size_t
NOTHROW_NCX(LIBCCALL libc_strcspn)(char const *haystack,
                                   char const *reject) {
#line 312 "kos/src/libc/magic/string.c"
	char const *iter = haystack;
	while (*iter && !libc_strchr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strspn") size_t
NOTHROW_NCX(LIBCCALL libc_strspn)(char const *haystack,
                                  char const *accept) {
#line 320 "kos/src/libc/magic/string.c"
	char const *iter = haystack;
	while (libc_strchr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strpbrk") char *
NOTHROW_NCX(LIBCCALL libc_strpbrk)(char const *haystack,
                                   char const *accept) {
#line 331 "kos/src/libc/magic/string.c"
	char const *ned_iter;
	char haych, ch;
	while ((haych = *haystack++) != '\0') {
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char *)haystack - 1;
		}
	}
	return NULL;
}

__LOCAL_LIBC_DATA(save_ptr) char *save_ptr = NULL;
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strtok") char *
NOTHROW_NCX(LIBCCALL libc_strtok)(char *string,
                                  char const *delim) {
#line 348 "kos/src/libc/magic/string.c"
	return libc_strtok_r(string, delim, &save_ptr);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strcoll") int
NOTHROW_NCX(LIBCCALL libc_strcoll)(char const *s1,
                                   char const *s2) {
#line 354 "kos/src/libc/magic/string.c"
	return libc_strcmp(s1, s2);
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strxfrm") size_t
NOTHROW_NCX(LIBCCALL libc_strxfrm)(char *dst,
                                   char const *__restrict src,
                                   size_t maxlen) {
#line 359 "kos/src/libc/magic/string.c"
	/* XXX: Implement me */
	size_t n = libc_strnlen(src, maxlen);
	memcpy(dst, src, n * sizeof(char));
	return n;
}

/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.stpcpy") char *
NOTHROW_NCX(LIBCCALL libc_stpcpy)(char *__restrict buf,
                                  char const *__restrict src) {
#line 407 "kos/src/libc/magic/string.c"
	return (char *)mempcpy(buf, src, (libc_strlen(src) + 1) * sizeof(char)) - 1;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.stpncpy") char *
NOTHROW_NCX(LIBCCALL libc_stpncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
#line 411 "kos/src/libc/magic/string.c"
	size_t srclen = libc_strnlen(src, buflen);
	memcpy(buf, src, srclen * sizeof(char));
	memset(buf+srclen, '\0', (size_t)(buflen - srclen) * sizeof(char));
	return buf + srclen;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strcoll_l") int
NOTHROW_NCX(LIBCCALL libc_strcoll_l)(char const *s1,
                                     char const *s2,
                                     locale_t locale) {
#line 424 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_strcoll(s1, s2);
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strxfrm_l") size_t
NOTHROW_NCX(LIBCCALL libc_strxfrm_l)(char *dst,
                                     char const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
#line 432 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_strxfrm(dst, src, maxlen);
}

INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strtok_r") char *
NOTHROW_NCX(LIBCCALL libc_strtok_r)(char *string,
                                    char const *delim,
                                    char **__restrict save_ptr) {
#line 483 "kos/src/libc/magic/string.c"
	char *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += libc_strspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + libc_strcspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return string;
}

/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strchrnul") char *
NOTHROW_NCX(LIBCCALL libc_strchrnul)(char const *__restrict haystack,
                                     int needle) {
#line 545 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack)
		if (*haystack == (char)needle)
			break;
	return (char *)haystack;
}

INTERN WUNUSED ATTR_PURE
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.basename") char *
NOTHROW_NCX(LIBCCALL libc_basename)(char const *filename) {
#line 556 "kos/src/libc/magic/string.c"
	char ch, *iter = (char *)filename, *result = NULL;
	if (!filename || !*filename)
		return (char *)filename;
	do {
		ch = *iter++;
#ifdef _WIN32
		if (ch == '/' || ch == '\\')
			result = iter;
#else
		if (ch == '/')
			result = iter;
#endif
	} while (ch);
	if unlikely(!result)
		return (char *)filename; /* Path doesn't contain '/'. */
	if (*result)
		return result; /* Last character isn't a '/'. */
	iter = result;
#ifdef _WIN32
	while (iter != filename && (iter[-1] == '/' || iter[-1] == '\\'))
		--iter;
#else
	while (iter != filename && iter[-1] == '/')
		--iter;
#endif
	if (iter == filename)
		return result-1; /* Only `'/'"-characters. */
	//*iter = '\0'; /* Trim all ending `'/'"-characters. */
#ifdef _WIN32
	while (iter != filename && (iter[-1] != '/' || iter[-1] != '\\'))
		--iter; /* Scan until the previous '/'. */
#else
	while (iter != filename && iter[-1] != '/')
		--iter; /* Scan until the previous '/'. */
#endif
	return iter; /* Returns string after previous '/'. */
}

/* Same as `strstr', but ignore casing */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strcasestr") char *
NOTHROW_NCX(LIBCCALL libc_strcasestr)(char const *haystack,
                                      char const *needle) {
#line 602 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack) {
		if (libc_strcasecmp(haystack, needle) == 0)
			return (char *)haystack;
	}
	return NULL;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strverscmp") int
NOTHROW_NCX(LIBCCALL libc_strverscmp)(char const *s1,
                                      char const *s2) {
#line 634 "kos/src/libc/magic/string.c"
	char const *s1_start = s1;
	char c1, c2;
	do {
		if ((c1 = *s1) != (c2 = *s2)) {
			unsigned int vala, valb;
			/* Unwind common digits. */
			while (s1 != s1_start) {
				if (s1[-1] < '0' || s1[-1] > '9')
					break;
				c2 = c1 = *--s1, --s2;
			}
			/* Check if both strings have digit sequences in the same places. */
			if ((c1 < '0' || c1 > '9') &&
			    (c2 < '0' || c2 > '9'))
				return (int)((unsigned char)c1 - (unsigned char)c2);
			/* Deal with leading zeros. */
			if (c1 == '0')
				return -1;
			if (c2 == '0')
				return 1;
			/* Compare digits. */
			vala = c1 - '0';
			valb = c2 - '0';
			for (;;) {
				c1 = *s1++;
				if (c1 < '0' || c1 > '9')
					break;
				vala *= 10;
				vala += c1-'0';
			}
			for (;;) {
				c2 = *s2++;
				if (c2 < '0' || c2 > '9')
					break;
				valb *= 10;
				valb += c2-'0';
			}
			return (int)vala - (int)valb;
		}
		++s1, ++s2;
	} while (c1);
	return 0;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strfry") char *
NOTHROW_NCX(LIBCCALL libc_strfry)(char *__restrict string) {
#line 694 "kos/src/libc/magic/string.c"
	char temp;
	size_t i, count = libc_strlen(string);
	for (i = 0; i < count; ++i) {
		size_t j = libc_rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
	return string;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memfrob") void *
NOTHROW_NCX(LIBCCALL libc_memfrob)(void *buf,
                                   size_t num_bytes) {
#line 709 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)buf;
	while (num_bytes--)
		*iter++ ^= 42; /* -_-   yeah... */
	return buf;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strcasecmp_l") int
NOTHROW_NCX(LIBCCALL libc_strcasecmp_l)(char const *s1,
                                        char const *s2,
                                        locale_t locale) {
#line 719 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_strcasecmp(s1, s2);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strncasecmp_l") int
NOTHROW_NCX(LIBCCALL libc_strncasecmp_l)(char const *s1,
                                         char const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
#line 725 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_strncasecmp(s1, s2, maxlen);
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strsep") char *
NOTHROW_NCX(LIBCCALL libc_strsep)(char **__restrict stringp,
                                  char const *__restrict delim) {
#line 745 "kos/src/libc/magic/string.c"
	char *result, *iter;
	if (!stringp || (result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libc_strchr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strcasecmp") int
NOTHROW_NCX(LIBCCALL libc_strcasecmp)(char const *s1,
                                      char const *s2) {
#line 765 "kos/src/libc/magic/string.c"
	char c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = libc_tolower(c1)) != (c2 = libc_tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strncasecmp") int
NOTHROW_NCX(LIBCCALL libc_strncasecmp)(char const *s1,
                                       char const *s2,
                                       size_t maxlen) {
#line 775 "kos/src/libc/magic/string.c"
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = libc_tolower(c1)) != (c2 = libc_tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}

#include <hybrid/__bit.h>
INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.ffs") __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_ffs)(int i) {
#line 791 "kos/src/libc/magic/string.c"
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((unsigned int)i);
}

#include <hybrid/__bit.h>
INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.ffsl") __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_ffsl)(long i) {
#line 813 "kos/src/libc/magic/string.c"
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((unsigned long)i);
}

#include <hybrid/__bit.h>
INTERN WUNUSED ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.ffsll") __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_ffsll)(__LONGLONG i) {
#line 821 "kos/src/libc/magic/string.c"
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((__ULONGLONG)i);
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strlcat") size_t
NOTHROW_NCX(LIBCCALL libc_strlcat)(char *__restrict dst,
                                   char const *__restrict src,
                                   size_t bufsize) {
#line 827 "kos/src/libc/magic/string.c"
	size_t result = libc_strlen(src);
	char *new_dst = dst + libc_strnlen(dst, bufsize);
	size_t copy_size;
	bufsize -= (new_dst - dst);
	copy_size = result < bufsize ? result : bufsize - 1;
	memcpy(new_dst, src, copy_size*sizeof(char));
	new_dst[copy_size] = '\0';
	return result + (new_dst - dst);
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strlcpy") size_t
NOTHROW_NCX(LIBCCALL libc_strlcpy)(char *__restrict dst,
                                   char const *__restrict src,
                                   size_t bufsize) {
#line 838 "kos/src/libc/magic/string.c"
	size_t result = libc_strlen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	memcpy(dst, src, copy_size*sizeof(char));
	dst[copy_size] = '\0';
	return result;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memccpy") void *
NOTHROW_NCX(LIBCCALL libc_memccpy)(void *__restrict dst,
                                   void const *__restrict src,
                                   int needle,
                                   size_t num_bytes) {
#line 854 "kos/src/libc/magic/string.c"
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (num_bytes--) {
		if ((*pdst++ = *psrc++) == (byte_t)needle)
			return pdst; /* Yes, this returns +1 past the needle. */
	}
	return NULL;
}

/* Same as `memchr', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxchr") void *
NOTHROW_NCX(LIBCCALL libc_memxchr)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
#line 1554 "kos/src/libc/magic/string.c"
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter != (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}

/* Same as `memrchr', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxchr") void *
NOTHROW_NCX(LIBCCALL libc_memrxchr)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
#line 1568 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--iter != (byte_t)needle)
			return iter;
	}
	return NULL;
}

/* Same as `rawmemchr', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxchr") void *
NOTHROW_NCX(LIBCCALL libc_rawmemxchr)(void const *__restrict haystack,
                                      int needle) {
#line 1583 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != (byte_t)needle)
			break;
	}
	return iter;
}

/* Same as `rawmemrchr', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxchr") void *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchr)(void const *__restrict haystack,
                                       int needle) {
#line 1597 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter != (byte_t)needle)
			break;
	}
	return iter;
}

/* Same as `memend', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxend") void *
NOTHROW_NCX(LIBCCALL libc_memxend)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
#line 1611 "kos/src/libc/magic/string.c"
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != (byte_t)needle)
			break;
	}
	return result;
}

/* Same as `memrend', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxend") void *
NOTHROW_NCX(LIBCCALL libc_memrxend)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
#line 1625 "kos/src/libc/magic/string.c"
	byte_t *result = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--result != (byte_t)needle)
			break;
	}
	return result;
}

/* Same as `memlen', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxlen") size_t
NOTHROW_NCX(LIBCCALL libc_memxlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
#line 1636 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)libc_memxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

/* Same as `memrlen', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxlen") size_t
NOTHROW_NCX(LIBCCALL libc_memrxlen)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
#line 1642 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)libc_memrxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}

/* Same as `rawmemlen', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxlen") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlen)(void const *__restrict haystack,
                                      int needle) {
#line 1648 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)libc_rawmemxchr(haystack, needle) - (byte_t *)haystack);
}

/* Same as `rawmemrlen', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxlen") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlen)(void const *__restrict haystack,
                                       int needle) {
#line 1654 "kos/src/libc/magic/string.c"
	return (size_t)((byte_t *)libc_rawmemrxchr(haystack, needle) - (byte_t *)haystack);
}

/* Same as `memchrw', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memxchrw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
#line 1674 "kos/src/libc/magic/string.c"
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter != word)
			return hay_iter;
	}
	return NULL;
}

/* Same as `memchrl', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memxchrl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
#line 1688 "kos/src/libc/magic/string.c"
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter != dword)
			return hay_iter;
	}
	return NULL;
}

/* Same as `memrchrw', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
#line 1709 "kos/src/libc/magic/string.c"
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter != word)
			return iter;
	}
	return NULL;
}

/* Same as `memrchrl', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
#line 1723 "kos/src/libc/magic/string.c"
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter != dword)
			return iter;
	}
	return NULL;
}

/* Same as `rawmemchrw', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrw)(void const *__restrict haystack,
                                       uint16_t word) {
#line 1744 "kos/src/libc/magic/string.c"
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != word)
			break;
	}
	return iter;
}

/* Same as `rawmemchrl', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrl)(void const *__restrict haystack,
                                       uint32_t dword) {
#line 1758 "kos/src/libc/magic/string.c"
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != dword)
			break;
	}
	return iter;
}

/* Same as `rawmemrchrw', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxchrw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrw)(void const *__restrict haystack,
                                        uint16_t word) {
#line 1780 "kos/src/libc/magic/string.c"
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter != word)
			break;
	}
	return iter;
}

/* Same as `rawmemrchrl', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxchrl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrl)(void const *__restrict haystack,
                                        uint32_t dword) {
#line 1794 "kos/src/libc/magic/string.c"
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter != dword)
			break;
	}
	return iter;
}

/* Same as `memendw', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxendw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memxendw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_bytes) {
#line 1816 "kos/src/libc/magic/string.c"
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != word)
			break;
	}
	return result;
}

/* Same as `memendl', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxendl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memxendl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_bytes) {
#line 1830 "kos/src/libc/magic/string.c"
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != dword)
			break;
	}
	return result;
}

/* Same as `memrendw', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxendw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrxendw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
#line 1852 "kos/src/libc/magic/string.c"
	u16 *result = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--result != word)
			break;
	}
	return result;
}

/* Same as `memrendl', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxendl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrxendl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
#line 1866 "kos/src/libc/magic/string.c"
	u32 *result = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--result != dword)
			break;
	}
	return result;
}

/* Same as `memlenw', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxlenw") size_t
NOTHROW_NCX(LIBCCALL libc_memxlenw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
#line 1883 "kos/src/libc/magic/string.c"
	return (size_t)(libc_memxendw(haystack, word, n_words) - (u16 *)haystack);
}

/* Same as `memlenl', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxlenl") size_t
NOTHROW_NCX(LIBCCALL libc_memxlenl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
#line 1889 "kos/src/libc/magic/string.c"
	return (size_t)(libc_memxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

/* Same as `memrlenw', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxlenw") size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
#line 1899 "kos/src/libc/magic/string.c"
	return (size_t)(libc_memrxendw(haystack, word, n_words) - (u16 *)haystack);
}

/* Same as `memrlenl', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxlenl") size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
#line 1905 "kos/src/libc/magic/string.c"
	return (size_t)(libc_memrxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}

/* Same as `rawmemlenw', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxlenw") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenw)(void const *__restrict haystack,
                                       uint16_t word) {
#line 1917 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemxchrw(haystack, word) - (u16 *)haystack);
}

/* Same as `rawmemlenl', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxlenl") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenl)(void const *__restrict haystack,
                                       uint32_t dword) {
#line 1923 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemxchrl(haystack, dword) - (u32 *)haystack);
}

/* Same as `rawmemrlenw', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxlenw") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenw)(void const *__restrict haystack,
                                        uint16_t word) {
#line 1934 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemrxchrw(haystack, word) - (u16 *)haystack);
}

/* Same as `rawmemrlenl', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxlenl") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenl)(void const *__restrict haystack,
                                        uint32_t dword) {
#line 1940 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemrxchrl(haystack, dword) - (u32 *)haystack);
}

/* Same as `memchrq', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memxchrq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
#line 1953 "kos/src/libc/magic/string.c"
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter != (u64)qword)
			return hay_iter;
	}
	return NULL;
}

/* Same as `memrchrq', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
#line 1967 "kos/src/libc/magic/string.c"
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter != qword)
			return iter;
	}
	return NULL;
}

/* Same as `rawmemchrq', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrq)(void const *__restrict haystack,
                                       uint64_t qword) {
#line 1981 "kos/src/libc/magic/string.c"
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != qword)
			break;
	}
	return iter;
}

/* Same as `rawmemrchrq', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxchrq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrq)(void const *__restrict haystack,
                                        uint64_t qword) {
#line 1995 "kos/src/libc/magic/string.c"
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter != qword)
			break;
	}
	return iter;
}

/* Same as `memendq', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxendq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memxendq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_bytes) {
#line 2009 "kos/src/libc/magic/string.c"
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != qword)
			break;
	}
	return result;
}

/* Same as `memrendq', but search for non-matching locations. */
INTERN ATTR_RETNONNULL WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxendq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrxendq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
#line 2023 "kos/src/libc/magic/string.c"
	u64 *result = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--result != qword)
			break;
	}
	return result;
}

/* Same as `memlenq', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memxlenq") size_t
NOTHROW_NCX(LIBCCALL libc_memxlenq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
#line 2034 "kos/src/libc/magic/string.c"
	return (size_t)(libc_memxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

/* Same as `memrlenq', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrxlenq") size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
#line 2040 "kos/src/libc/magic/string.c"
	return (size_t)(libc_memrxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}

/* Same as `rawmemlenq', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemxlenq") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenq)(void const *__restrict haystack,
                                       uint64_t qword) {
#line 2046 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemxchrq(haystack, qword) - (u64 *)haystack);
}

/* Same as `rawmemrlenq', but search for non-matching locations. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.rawmemrxlenq") size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenq)(void const *__restrict haystack,
                                        uint64_t qword) {
#line 2052 "kos/src/libc/magic/string.c"
	return (size_t)(libc_rawmemrxchrq(haystack, qword) - (u64 *)haystack);
}

/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnchr") char *
NOTHROW_NCX(LIBCCALL libc_strnchr)(char const *__restrict haystack,
                                   int needle,
                                   size_t maxlen) {
#line 2097 "kos/src/libc/magic/string.c"
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			return (char *)haystack;
	return NULL;
}

/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnrchr") char *
NOTHROW_NCX(LIBCCALL libc_strnrchr)(char const *__restrict haystack,
                                    int needle,
                                    size_t maxlen) {
#line 2109 "kos/src/libc/magic/string.c"
	char const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	return (char *)result;
}

/* Same as `strrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strrchrnul") char *
NOTHROW_NCX(LIBCCALL libc_strrchrnul)(char const *__restrict haystack,
                                      int needle) {
#line 2122 "kos/src/libc/magic/string.c"
	char const *result = haystack - 1;
	do {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	} while (*haystack++);
	return (char *)result;
}

/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnchrnul") char *
NOTHROW_NCX(LIBCCALL libc_strnchrnul)(char const *__restrict haystack,
                                      int needle,
                                      size_t maxlen) {
#line 2136 "kos/src/libc/magic/string.c"
	for (; maxlen-- && *haystack && (unsigned char)*haystack != (unsigned char)needle; ++haystack);
	return (char *)haystack;
}

/* Same as `strnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnrchrnul") char *
NOTHROW_NCX(LIBCCALL libc_strnrchrnul)(char const *__restrict haystack,
                                       int needle,
                                       size_t maxlen) {
#line 2146 "kos/src/libc/magic/string.c"
	char const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	return (char *)result;
}

/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.stroff") size_t
NOTHROW_NCX(LIBCCALL libc_stroff)(char const *__restrict haystack,
                                  int needle) {
#line 2156 "kos/src/libc/magic/string.c"
	return (size_t)(libc_strchrnul(haystack, needle) - haystack);
}

/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strroff") size_t
NOTHROW_NCX(LIBCCALL libc_strroff)(char const *__restrict haystack,
                                   int needle) {
#line 2162 "kos/src/libc/magic/string.c"
	return (size_t)(libc_strrchrnul(haystack, needle) - haystack);
}

/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnoff") size_t
NOTHROW_NCX(LIBCCALL libc_strnoff)(char const *__restrict haystack,
                                   int needle,
                                   size_t maxlen) {
#line 2168 "kos/src/libc/magic/string.c"
	return (size_t)(libc_strnchrnul(haystack, needle, maxlen) - haystack);
}

/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnroff") size_t
NOTHROW_NCX(LIBCCALL libc_strnroff)(char const *__restrict haystack,
                                    int needle,
                                    size_t maxlen) {
#line 2174 "kos/src/libc/magic/string.c"
	return (size_t)(libc_strnrchrnul(haystack, needle, maxlen) - haystack);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.memcasecmp") int
NOTHROW_NCX(LIBCCALL libc_memcasecmp)(void const *s1,
                                      void const *s2,
                                      size_t n_bytes) {
#line 2338 "kos/src/libc/magic/string.c"
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes-- &&
	    (((v1 = *p1++) == (v2 = *p2++)) ||
	     ((v1 = libc_tolower(v1)) == (v2 = libc_tolower(v2)))));
	return (int)v1 - (int)v2;
}

/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally. */
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.memcasemem") void *
NOTHROW_NCX(LIBCCALL libc_memcasemem)(void const *haystack,
                                      size_t haystacklen,
                                      void const *needle,
                                      size_t needlelen) {
#line 2359 "kos/src/libc/magic/string.c"
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = libc_tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || libc_tolower(b) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (libc_memcasecmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.memcasecmp_l") int
NOTHROW_NCX(LIBCCALL libc_memcasecmp_l)(void const *s1,
                                        void const *s2,
                                        size_t n_bytes,
                                        locale_t locale) {
#line 2387 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_memcasecmp(s1, s2, n_bytes);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.memcasemem_l") void *
NOTHROW_NCX(LIBCCALL libc_memcasemem_l)(void const *haystack,
                                        size_t haystacklen,
                                        void const *needle,
                                        size_t needlelen,
                                        locale_t locale) {
#line 2396 "kos/src/libc/magic/string.c"
	byte_t *iter = (byte_t *)haystack;
	while (haystacklen >= needlelen) {
		if (libc_memcasecmp_l(iter, needle, needlelen, locale) == 0)
			return (void *)iter;
		++iter;
	}
	return NULL;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strcasestr_l") char *
NOTHROW_NCX(LIBCCALL libc_strcasestr_l)(char const *haystack,
                                        char const *needle,
                                        locale_t locale) {
#line 2410 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack) {
		if (libc_strcasecmp_l(haystack, needle, locale) == 0)
			return (char *)haystack;
	}
	return NULL;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.wildstrcmp") int
NOTHROW_NCX(LIBCCALL libc_wildstrcmp)(char const *pattern,
                                      char const *string) {
#line 3512 "kos/src/libc/magic/string.c"
	char card_post;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)(unsigned char)*pattern;
		}
		if (!*pattern)
			return (int)(unsigned char)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			for (;;) {
				char ch = *string++;
				if (ch == card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildstrcmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		if (*pattern == *string || *pattern == '?') {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)*string - (unsigned char)*pattern);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.wildstrcasecmp") int
NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp)(char const *pattern,
                                          char const *string) {
#line 3556 "kos/src/libc/magic/string.c"
	char card_post, pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = libc_tolower(card_post);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == libc_tolower(ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildstrcasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		   (pattern_ch = libc_tolower(pattern_ch),
		    string_ch = libc_tolower(string_ch),
		    pattern_ch == string_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)string_ch - (unsigned char)pattern_ch);
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.fuzzy_strcmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcmp)(char const *s1,
                                        char const *s2) {
#line 3606 "kos/src/libc/magic/string.c"
	return libc_fuzzy_memcmp(s1, libc_strlen(s1), s2, libc_strlen(s2));
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.fuzzy_strncmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncmp)(char const *s1,
                                         size_t s1_maxlen,
                                         char const *s2,
                                         size_t s2_maxlen) {
#line 3613 "kos/src/libc/magic/string.c"
	return libc_fuzzy_memcmp(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen));
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.fuzzy_strcasecmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp)(char const *s1,
                                            char const *s2) {
#line 3620 "kos/src/libc/magic/string.c"
	return libc_fuzzy_memcasecmp(s1, libc_strlen(s1), s2, libc_strlen(s2));
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.fuzzy_strncasecmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp)(char const *s1,
                                             size_t s1_maxlen,
                                             char const *s2,
                                             size_t s2_maxlen) {
#line 3627 "kos/src/libc/magic/string.c"
	return libc_fuzzy_memcasecmp(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen));
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.fuzzy_memcmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmp)(void const *s1,
                                        size_t s1_bytes,
                                        void const *s2,
                                        size_t s2_bytes) {
#line 3634 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_bytes; s1_bytes = s2_bytes; s2_bytes = temp; }
	}
	__malloca_tryhard(v0, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif
	__malloca_tryhard(v1, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif
	for (i = 0; i < s2_bytes; ++i) v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_bytes; j++) {
			cost  = ((byte_t *)s1)[i] != ((byte_t *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.fuzzy_memcasecmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp)(void const *s1,
                                            size_t s1_bytes,
                                            void const *s2,
                                            size_t s2_bytes) {
#line 3687 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_bytes; s1_bytes = s2_bytes; s2_bytes = temp; }
	}
	__malloca_tryhard(v0, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif
	__malloca_tryhard(v1, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif
	for (i = 0; i < s2_bytes; ++i) v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && libc_tolower(c1) != libc_tolower(c2);
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.fuzzy_strcasecmp_l") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp_l)(char const *s1,
                                              char const *s2,
                                              locale_t locale) {
#line 3741 "kos/src/libc/magic/string.c"
	return libc_fuzzy_memcasecmp_l(s1, libc_strlen(s1), s2, libc_strlen(s2), locale);
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.fuzzy_strncasecmp_l") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp_l)(char const *s1,
                                               size_t s1_maxlen,
                                               char const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
#line 3747 "kos/src/libc/magic/string.c"
	return libc_fuzzy_memcasecmp_l(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen), locale);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.wildstrcasecmp_l") int
NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp_l)(char const *pattern,
                                            char const *string,
                                            locale_t locale) {
#line 3753 "kos/src/libc/magic/string.c"
	char card_post, pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*') ++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = libc_tolower_l(card_post, locale);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == libc_tolower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_strcasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		   (pattern_ch = libc_tolower_l(pattern_ch, locale),
		    string_ch = libc_tolower_l(string_ch, locale),
		    pattern_ch == string_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)string_ch - (unsigned char)pattern_ch);
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.fuzzy_memcasecmp_l") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp_l)(void const *s1,
                                              size_t s1_bytes,
                                              void const *s2,
                                              size_t s2_bytes,
                                              locale_t locale) {
#line 3803 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_bytes; s1_bytes = s2_bytes; s2_bytes = temp; }
	}
	__malloca_tryhard(v0, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif
	__malloca_tryhard(v1, (s2_bytes+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif
	for (i = 0; i < s2_bytes; ++i) v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && libc_tolower_l(c1, locale) != libc_tolower_l(c2, locale);
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.fuzzy_memcmpw") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpw)(void const *s1,
                                         size_t s1_words,
                                         void const *s2,
                                         size_t s2_words) {
#line 3867 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_words)
		return s2_words;
	if unlikely(!s2_words)
		return s1_words;
	if (s2_words > s1_words) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_words; s1_words = s2_words; s2_words = temp; }
	}
	__malloca_tryhard(v0, (s2_words+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif
	__malloca_tryhard(v1, (s2_words+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif
	for (i = 0; i < s2_words; ++i) v0[i] = i;
	for (i = 0; i < s1_words; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_words; j++) {
			cost  = ((u16 *)s1)[i] != ((u16 *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_words);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_words);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_words);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_words*sizeof(size_t));
#endif
	}
	temp = v1[s2_words];
	__freea(v1);
	__freea(v0);
	return temp;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.fuzzy_memcmpl") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpl)(void const *s1,
                                         size_t s1_dwords,
                                         void const *s2,
                                         size_t s2_dwords) {
#line 3919 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_dwords)
		return s2_dwords;
	if unlikely(!s2_dwords)
		return s1_dwords;
	if (s2_dwords > s1_dwords) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_dwords; s1_dwords = s2_dwords; s2_dwords = temp; }
	}
	__malloca_tryhard(v0, (s2_dwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif
	__malloca_tryhard(v1, (s2_dwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif
	for (i = 0; i < s2_dwords; ++i) v0[i] = i;
	for (i = 0; i < s1_dwords; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_dwords; j++) {
			cost  = ((u32 *)s1)[i] != ((u32 *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_dwords);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_dwords);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_dwords);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_dwords*sizeof(size_t));
#endif
	}
	temp = v1[s2_dwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.fuzzy_memcmpq") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpq)(void const *s1,
                                         size_t s1_qwords,
                                         void const *s2,
                                         size_t s2_qwords) {
#line 3972 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_qwords)
		return s2_qwords;
	if unlikely(!s2_qwords)
		return s1_qwords;
	if (s2_qwords > s1_qwords) {
		{ void const *temp = s1; s1 = s2; s2 = temp; }
		{ size_t temp = s1_qwords; s1_qwords = s2_qwords; s2_qwords = temp; }
	}
	__malloca_tryhard(v0, (s2_qwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0) return (size_t)-1;
#endif
	__malloca_tryhard(v1, (s2_qwords+1)*sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif
	for (i = 0; i < s2_qwords; ++i) v0[i] = i;
	for (i = 0; i < s1_qwords; ++i) {
		v1[0] = i+1;
		for (j = 0; j < s2_qwords; j++) {
			cost  = ((u64 *)s1)[i] != ((u64 *)s2)[j];
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		memcpyq((u64 *)v0, (u64 *)v1, s2_qwords);
#elif __SIZEOF_SIZE_T__ == 4
		memcpyl((u32 *)v0, (u32 *)v1, s2_qwords);
#elif __SIZEOF_SIZE_T__ == 2
		memcpyw((u16 *)v0, (u16 *)v1, s2_qwords);
#else
		memcpy((u8 *)v0, (u8 *)v1, s2_qwords*sizeof(size_t));
#endif
	}
	temp = v1[s2_qwords];
	__freea(v1);
	__freea(v0);
	return temp;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strncoll") int
NOTHROW_NCX(LIBCCALL libc_strncoll)(char const *s1,
                                    char const *s2,
                                    size_t maxlen) {
#line 4028 "kos/src/libc/magic/string.c"
	return libc_strncmp(s1, s2, maxlen);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strcasecoll") int
NOTHROW_NCX(LIBCCALL libc_strcasecoll)(char const *s1,
                                       char const *s2) {
#line 4033 "kos/src/libc/magic/string.c"
	return libc_strcasecmp(s1, s2);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strncasecoll") int
NOTHROW_NCX(LIBCCALL libc_strncasecoll)(char const *s1,
                                        char const *s2,
                                        size_t maxlen) {
#line 4038 "kos/src/libc/magic/string.c"
	return libc_strncasecmp(s1, s2, maxlen);
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnrev") char *
NOTHROW_NCX(LIBCCALL libc_strnrev)(char *__restrict str,
                                   size_t maxlen) {
#line 4042 "kos/src/libc/magic/string.c"
	return (char *)libc_memrev(str, libc_strnlen(str, maxlen));
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strnlwr") char *
NOTHROW_NCX(LIBCCALL libc_strnlwr)(char *__restrict str,
                                   size_t maxlen) {
#line 4048 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower(ch);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strnupr") char *
NOTHROW_NCX(LIBCCALL libc_strnupr)(char *__restrict str,
                                   size_t maxlen) {
#line 4056 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper(ch);
	return str;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strncoll_l") int
NOTHROW_NCX(LIBCCALL libc_strncoll_l)(char const *s1,
                                      char const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
#line 4067 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_strncoll(s1, s2, maxlen);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strcasecoll_l") int
NOTHROW_NCX(LIBCCALL libc_strcasecoll_l)(char const *s1,
                                         char const *s2,
                                         locale_t locale) {
#line 4073 "kos/src/libc/magic/string.c"
	return libc_strcasecmp_l(s1, s2, locale);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strncasecoll_l") int
NOTHROW_NCX(LIBCCALL libc_strncasecoll_l)(char const *s1,
                                          char const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
#line 4079 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_strncasecoll(s1, s2, maxlen);
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strlwr_l") char *
NOTHROW_NCX(LIBCCALL libc_strlwr_l)(char *__restrict str,
                                    locale_t locale) {
#line 4086 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower_l(ch, locale);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strupr_l") char *
NOTHROW_NCX(LIBCCALL libc_strupr_l)(char *__restrict str,
                                    locale_t locale) {
#line 4094 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper_l(ch, locale);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strnlwr_l") char *
NOTHROW_NCX(LIBCCALL libc_strnlwr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
#line 4102 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower_l(ch, locale);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.strnupr_l") char *
NOTHROW_NCX(LIBCCALL libc_strnupr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
#line 4110 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper_l(ch, locale);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrev") void *
NOTHROW_NCX(LIBCCALL libc_memrev)(void *__restrict base,
                                  size_t n_bytes) {
#line 4117 "kos/src/libc/magic/string.c"
	byte_t *iter, *end;
	end = (iter = (byte_t *)base) + n_bytes;
	while (iter < end) {
		byte_t temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return base;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrevw") uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrevw)(void *__restrict base,
                                   size_t n_words) {
#line 4133 "kos/src/libc/magic/string.c"
	u16 *iter, *end;
	end = (iter = (u16 *)base) + n_words;
	while (iter < end) {
		u16 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u16 *)base;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrevl") uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrevl)(void *__restrict base,
                                   size_t n_dwords) {
#line 4144 "kos/src/libc/magic/string.c"
	u32 *iter, *end;
	end = (iter = (u32 *)base) + n_dwords;
	while (iter < end) {
		u32 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u32 *)base;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrevq") uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrevq)(void *__restrict base,
                                   size_t n_qwords) {
#line 4156 "kos/src/libc/magic/string.c"
	u64 *iter, *end;
	end = (iter = (u64 *)base) + n_qwords;
	while (iter < end) {
		u64 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u64 *)base;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strlwr") char *
NOTHROW_NCX(LIBCCALL libc_strlwr)(char *__restrict str) {
#line 4177 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower(ch);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.strupr") char *
NOTHROW_NCX(LIBCCALL libc_strupr)(char *__restrict str) {
#line 4185 "kos/src/libc/magic/string.c"
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper(ch);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strset") char *
NOTHROW_NCX(LIBCCALL libc_strset)(char *__restrict str,
                                  int ch) {
#line 4192 "kos/src/libc/magic/string.c"
	char *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char)ch;
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strnset") char *
NOTHROW_NCX(LIBCCALL libc_strnset)(char *__restrict str,
                                   int ch,
                                   size_t maxlen) {
#line 4199 "kos/src/libc/magic/string.c"
	char *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char)ch;
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.strrev") char *
NOTHROW_NCX(LIBCCALL libc_strrev)(char *__restrict str) {
#line 4206 "kos/src/libc/magic/string.c"
	return (char *)libc_memrev(str, libc_strlen(str));
}

#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory._strset_s") errno_t
NOTHROW_NCX(LIBCCALL libc__strset_s)(char *dst,
                                     size_t dstsize,
                                     int ch) {
#line 4223 "kos/src/libc/magic/string.c"


	char *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char)ch;
	if (remaining == 0) {
		memset(dst, 1, dstsize * sizeof(char));
		return __EINVAL;
	}
	memset(p, 0, remaining * sizeof(char));
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory.memcpy_s") errno_t
NOTHROW_NCX(LIBCCALL libc_memcpy_s)(void *dst,
                                    rsize_t dstlength,
                                    void const *src,
                                    rsize_t srclength) {
#line 4247 "kos/src/libc/magic/string.c"


	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		memset(dst, 0, dstlength);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	memcpy(dst, src, srclength);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory.memmove_s") errno_t
NOTHROW_NCX(LIBCCALL libc_memmove_s)(void *dst,
                                     rsize_t dstlength,
                                     void const *src,
                                     rsize_t srclength) {
#line 4269 "kos/src/libc/magic/string.c"

	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	memmove(dst, src, srclength);
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory.strcpy_s") errno_t
NOTHROW_NCX(LIBCCALL libc_strcpy_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
#line 4284 "kos/src/libc/magic/string.c"


	char *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		memset(dst, 0, dstsize * sizeof(char));
		return __ERANGE;
	}
	memset(iter, 0, remaining * sizeof(char));
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory.strcat_s") errno_t
NOTHROW_NCX(LIBCCALL libc_strcat_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
#line 4305 "kos/src/libc/magic/string.c"
	if (!dst || !src)
		return __EINVAL;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return __EINVAL;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return __ERANGE;
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory.strncat_s") errno_t
NOTHROW_NCX(LIBCCALL libc_strncat_s)(char *dst,
                                     rsize_t dstsize,
                                     const char *src,
                                     rsize_t maxlen) {
#line 4329 "kos/src/libc/magic/string.c"


	char *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		memset(dst, 0, dstsize * sizeof(char));
		return __EINVAL;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		memset(dst, 0, dstsize * sizeof(char));
		return __ERANGE;
	}
	memset(iter, 0, remaining * sizeof(char));
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory.strncpy_s") errno_t
NOTHROW_NCX(LIBCCALL libc_strncpy_s)(char *dst,
                                     size_t dstsize,
                                     char const *src,
                                     size_t maxlen) {
#line 4369 "kos/src/libc/magic/string.c"


	char *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	if (!maxlen) {
		memset(dst, 0, dstsize * sizeof(char));
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return __ERANGE;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return __STRUNCATE;
		}
		memset(dst, 0, dstsize * sizeof(char));
		return __ERANGE;
	}
	memset(iter, 0, remaining * sizeof(char));
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.memory._strlwr_s") errno_t
NOTHROW_NCX(LIBCCALL libc__strlwr_s)(char *buf,
                                     size_t buflen) {
#line 4430 "kos/src/libc/magic/string.c"
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower(ch);
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.static.memory._strupr_s") errno_t
NOTHROW_NCX(LIBCCALL libc__strupr_s)(char *buf,
                                     size_t buflen) {
#line 4442 "kos/src/libc/magic/string.c"
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper(ch);
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.memory._strlwr_s_l") errno_t
NOTHROW_NCX(LIBCCALL libc__strlwr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
#line 4454 "kos/src/libc/magic/string.c"
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower_l(ch, locale);
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.unicode.locale.memory._strupr_s_l") errno_t
NOTHROW_NCX(LIBCCALL libc__strupr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
#line 4466 "kos/src/libc/magic/string.c"
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper_l(ch, locale);
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.string.memory._strnset_s") errno_t
NOTHROW_NCX(LIBCCALL libc__strnset_s)(char *__restrict buf,
                                      size_t buflen,
                                      int ch,
                                      size_t maxlen) {
#line 4481 "kos/src/libc/magic/string.c"


	char *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return __EINVAL;
	if (maxlen >= buflen)
		return __ERANGE;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (char32_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		memset(buf, 0, buflen * sizeof(char));
		return __EINVAL;
	}
	memset(iter, 0, remaining * sizeof(char));
	return 0;
}

#endif /* !__KERNEL__ */
DEFINE_PUBLIC_WEAK_ALIAS(memcpy, libc_memcpy);
DEFINE_PUBLIC_WEAK_ALIAS(memmove, libc_memmove);
DEFINE_PUBLIC_WEAK_ALIAS(memset, libc_memset);
DEFINE_PUBLIC_WEAK_ALIAS(memcmp, libc_memcmp);
DEFINE_PUBLIC_WEAK_ALIAS(bcmp, libc_memcmp);
DEFINE_PUBLIC_WEAK_ALIAS(memchr, libc_memchr);
DEFINE_PUBLIC_WEAK_ALIAS(strlen, libc_strlen);
DEFINE_PUBLIC_WEAK_ALIAS(strchr, libc_strchr);
DEFINE_PUBLIC_WEAK_ALIAS(strcmp, libc_strcmp);
DEFINE_PUBLIC_WEAK_ALIAS(strnlen, libc_strnlen);
DEFINE_PUBLIC_WEAK_ALIAS(memrchr, libc_memrchr);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemchr, libc_rawmemchr);
DEFINE_PUBLIC_WEAK_ALIAS(__rawmemchr, libc_rawmemchr);
DEFINE_PUBLIC_WEAK_ALIAS(memmem, libc_memmem);
DEFINE_PUBLIC_WEAK_ALIAS(mempcpy, libc_mempcpy);
DEFINE_PUBLIC_WEAK_ALIAS(__mempcpy, libc_mempcpy);
DEFINE_PUBLIC_WEAK_ALIAS(memcpyw, libc_memcpyw);
DEFINE_PUBLIC_WEAK_ALIAS(mempcpyw, libc_mempcpyw);
DEFINE_PUBLIC_WEAK_ALIAS(memcpyl, libc_memcpyl);
DEFINE_PUBLIC_WEAK_ALIAS(mempcpyl, libc_mempcpyl);
DEFINE_PUBLIC_WEAK_ALIAS(memmovew, libc_memmovew);
DEFINE_PUBLIC_WEAK_ALIAS(mempmovew, libc_mempmovew);
DEFINE_PUBLIC_WEAK_ALIAS(memmovel, libc_memmovel);
DEFINE_PUBLIC_WEAK_ALIAS(mempmovel, libc_mempmovel);
DEFINE_PUBLIC_WEAK_ALIAS(memsetw, libc_memsetw);
DEFINE_PUBLIC_WEAK_ALIAS(mempsetw, libc_mempsetw);
DEFINE_PUBLIC_WEAK_ALIAS(memsetl, libc_memsetl);
DEFINE_PUBLIC_WEAK_ALIAS(mempsetl, libc_mempsetl);
DEFINE_PUBLIC_WEAK_ALIAS(memcmpw, libc_memcmpw);
DEFINE_PUBLIC_WEAK_ALIAS(memcmpl, libc_memcmpl);
DEFINE_PUBLIC_WEAK_ALIAS(memchrw, libc_memchrw);
DEFINE_PUBLIC_WEAK_ALIAS(memchrl, libc_memchrl);
DEFINE_PUBLIC_WEAK_ALIAS(memrchrw, libc_memrchrw);
DEFINE_PUBLIC_WEAK_ALIAS(memrchrl, libc_memrchrl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemchrw, libc_rawmemchrw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemchrl, libc_rawmemchrl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrchrw, libc_rawmemrchrw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrchrl, libc_rawmemrchrl);
DEFINE_PUBLIC_WEAK_ALIAS(memendw, libc_memendw);
DEFINE_PUBLIC_WEAK_ALIAS(memendl, libc_memendl);
DEFINE_PUBLIC_WEAK_ALIAS(memrendw, libc_memrendw);
DEFINE_PUBLIC_WEAK_ALIAS(memrendl, libc_memrendl);
DEFINE_PUBLIC_WEAK_ALIAS(memlenw, libc_memlenw);
DEFINE_PUBLIC_WEAK_ALIAS(memlenl, libc_memlenl);
DEFINE_PUBLIC_WEAK_ALIAS(memrlenw, libc_memrlenw);
DEFINE_PUBLIC_WEAK_ALIAS(memrlenl, libc_memrlenl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemlenw, libc_rawmemlenw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemlenl, libc_rawmemlenl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrlenw, libc_rawmemrlenw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrlenl, libc_rawmemrlenl);
DEFINE_PUBLIC_WEAK_ALIAS(memcpyq, libc_memcpyq);
DEFINE_PUBLIC_WEAK_ALIAS(mempcpyq, libc_mempcpyq);
DEFINE_PUBLIC_WEAK_ALIAS(memmoveq, libc_memmoveq);
DEFINE_PUBLIC_WEAK_ALIAS(mempmoveq, libc_mempmoveq);
DEFINE_PUBLIC_WEAK_ALIAS(memsetq, libc_memsetq);
DEFINE_PUBLIC_WEAK_ALIAS(mempsetq, libc_mempsetq);
DEFINE_PUBLIC_WEAK_ALIAS(memcmpq, libc_memcmpq);
DEFINE_PUBLIC_WEAK_ALIAS(memchrq, libc_memchrq);
DEFINE_PUBLIC_WEAK_ALIAS(memrchrq, libc_memrchrq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemchrq, libc_rawmemchrq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrchrq, libc_rawmemrchrq);
DEFINE_PUBLIC_WEAK_ALIAS(memendq, libc_memendq);
DEFINE_PUBLIC_WEAK_ALIAS(memrendq, libc_memrendq);
DEFINE_PUBLIC_WEAK_ALIAS(memlenq, libc_memlenq);
DEFINE_PUBLIC_WEAK_ALIAS(memrlenq, libc_memrlenq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemlenq, libc_rawmemlenq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrlenq, libc_rawmemrlenq);
DEFINE_PUBLIC_WEAK_ALIAS(strend, libc_strend);
DEFINE_PUBLIC_WEAK_ALIAS(strnend, libc_strnend);
DEFINE_PUBLIC_WEAK_ALIAS(mempset, libc_mempset);
DEFINE_PUBLIC_WEAK_ALIAS(mempmove, libc_mempmove);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrchr, libc_rawmemrchr);
DEFINE_PUBLIC_WEAK_ALIAS(memend, libc_memend);
DEFINE_PUBLIC_WEAK_ALIAS(memrend, libc_memrend);
DEFINE_PUBLIC_WEAK_ALIAS(memlen, libc_memlen);
DEFINE_PUBLIC_WEAK_ALIAS(memrlen, libc_memrlen);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemlen, libc_rawmemlen);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrlen, libc_rawmemrlen);
DEFINE_PUBLIC_WEAK_ALIAS(mempatw, libc_mempatw);
DEFINE_PUBLIC_WEAK_ALIAS(mempatl, libc_mempatl);
DEFINE_PUBLIC_WEAK_ALIAS(mempatq, libc_mempatq);
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(strrchr, libc_strrchr);
DEFINE_PUBLIC_WEAK_ALIAS(strncmp, libc_strncmp);
DEFINE_PUBLIC_WEAK_ALIAS(strstr, libc_strstr);
DEFINE_PUBLIC_WEAK_ALIAS(strcpy, libc_strcpy);
DEFINE_PUBLIC_WEAK_ALIAS(strncpy, libc_strncpy);
DEFINE_PUBLIC_WEAK_ALIAS(strcat, libc_strcat);
DEFINE_PUBLIC_WEAK_ALIAS(strncat, libc_strncat);
DEFINE_PUBLIC_WEAK_ALIAS(strcspn, libc_strcspn);
DEFINE_PUBLIC_WEAK_ALIAS(strspn, libc_strspn);
DEFINE_PUBLIC_WEAK_ALIAS(strpbrk, libc_strpbrk);
DEFINE_PUBLIC_WEAK_ALIAS(strtok, libc_strtok);
DEFINE_PUBLIC_WEAK_ALIAS(strcoll, libc_strcoll);
DEFINE_PUBLIC_WEAK_ALIAS(strxfrm, libc_strxfrm);
DEFINE_PUBLIC_WEAK_ALIAS(stpcpy, libc_stpcpy);
DEFINE_PUBLIC_WEAK_ALIAS(__stpcpy, libc_stpcpy);
DEFINE_PUBLIC_WEAK_ALIAS(stpncpy, libc_stpncpy);
DEFINE_PUBLIC_WEAK_ALIAS(__stpncpy, libc_stpncpy);
DEFINE_PUBLIC_WEAK_ALIAS(strcoll_l, libc_strcoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strcoll_l, libc_strcoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strcoll_l, libc_strcoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_WEAK_ALIAS(strtok_r, libc_strtok_r);
DEFINE_PUBLIC_WEAK_ALIAS(__strtok_r, libc_strtok_r);
DEFINE_PUBLIC_WEAK_ALIAS(strtok_s, libc_strtok_r);
DEFINE_PUBLIC_WEAK_ALIAS(strchrnul, libc_strchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(basename, libc_basename);
DEFINE_PUBLIC_WEAK_ALIAS(strcasestr, libc_strcasestr);
DEFINE_PUBLIC_WEAK_ALIAS(__strcasestr, libc_strcasestr);
DEFINE_PUBLIC_WEAK_ALIAS(strverscmp, libc_strverscmp);
DEFINE_PUBLIC_WEAK_ALIAS(__strverscmp, libc_strverscmp);
DEFINE_PUBLIC_WEAK_ALIAS(strfry, libc_strfry);
DEFINE_PUBLIC_WEAK_ALIAS(memfrob, libc_memfrob);
DEFINE_PUBLIC_WEAK_ALIAS(strcasecmp_l, libc_strcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strcasecmp_l, libc_strcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(_stricmp_l, libc_strcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(strncasecmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strncasecmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strnicmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strncmpi_l, libc_strncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(strsep, libc_strsep);
DEFINE_PUBLIC_WEAK_ALIAS(strcasecmp, libc_strcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(__strcasecmp, libc_strcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(_stricmp, libc_strcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(_strcmpi, libc_strcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(stricmp, libc_strcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(strcmpi, libc_strcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(strncasecmp, libc_strncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(_strnicmp, libc_strncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(strnicmp, libc_strncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(_strncmpi, libc_strncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(strncmpi, libc_strncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(ffs, libc_ffs);
DEFINE_PUBLIC_WEAK_ALIAS(__ffs, libc_ffs);
DEFINE_PUBLIC_WEAK_ALIAS(ffsl, libc_ffsl);
DEFINE_PUBLIC_WEAK_ALIAS(ffsll, libc_ffsll);
DEFINE_PUBLIC_WEAK_ALIAS(strlcat, libc_strlcat);
DEFINE_PUBLIC_WEAK_ALIAS(strlcpy, libc_strlcpy);
DEFINE_PUBLIC_WEAK_ALIAS(memccpy, libc_memccpy);
DEFINE_PUBLIC_WEAK_ALIAS(_memccpy, libc_memccpy);
DEFINE_PUBLIC_WEAK_ALIAS(memxchr, libc_memxchr);
DEFINE_PUBLIC_WEAK_ALIAS(memrxchr, libc_memrxchr);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxchr, libc_rawmemxchr);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxchr, libc_rawmemrxchr);
DEFINE_PUBLIC_WEAK_ALIAS(memxend, libc_memxend);
DEFINE_PUBLIC_WEAK_ALIAS(memrxend, libc_memrxend);
DEFINE_PUBLIC_WEAK_ALIAS(memxlen, libc_memxlen);
DEFINE_PUBLIC_WEAK_ALIAS(memrxlen, libc_memrxlen);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxlen, libc_rawmemxlen);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxlen, libc_rawmemrxlen);
DEFINE_PUBLIC_WEAK_ALIAS(memxchrw, libc_memxchrw);
DEFINE_PUBLIC_WEAK_ALIAS(memxchrl, libc_memxchrl);
DEFINE_PUBLIC_WEAK_ALIAS(memrxchrw, libc_memrxchrw);
DEFINE_PUBLIC_WEAK_ALIAS(memrxchrl, libc_memrxchrl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxchrw, libc_rawmemxchrw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxchrl, libc_rawmemxchrl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxchrw, libc_rawmemrxchrw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxchrl, libc_rawmemrxchrl);
DEFINE_PUBLIC_WEAK_ALIAS(memxendw, libc_memxendw);
DEFINE_PUBLIC_WEAK_ALIAS(memxendl, libc_memxendl);
DEFINE_PUBLIC_WEAK_ALIAS(memrxendw, libc_memrxendw);
DEFINE_PUBLIC_WEAK_ALIAS(memrxendl, libc_memrxendl);
DEFINE_PUBLIC_WEAK_ALIAS(memxlenw, libc_memxlenw);
DEFINE_PUBLIC_WEAK_ALIAS(memxlenl, libc_memxlenl);
DEFINE_PUBLIC_WEAK_ALIAS(memrxlenw, libc_memrxlenw);
DEFINE_PUBLIC_WEAK_ALIAS(memrxlenl, libc_memrxlenl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxlenw, libc_rawmemxlenw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxlenl, libc_rawmemxlenl);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxlenw, libc_rawmemrxlenw);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxlenl, libc_rawmemrxlenl);
DEFINE_PUBLIC_WEAK_ALIAS(memxchrq, libc_memxchrq);
DEFINE_PUBLIC_WEAK_ALIAS(memrxchrq, libc_memrxchrq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxchrq, libc_rawmemxchrq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxchrq, libc_rawmemrxchrq);
DEFINE_PUBLIC_WEAK_ALIAS(memxendq, libc_memxendq);
DEFINE_PUBLIC_WEAK_ALIAS(memrxendq, libc_memrxendq);
DEFINE_PUBLIC_WEAK_ALIAS(memxlenq, libc_memxlenq);
DEFINE_PUBLIC_WEAK_ALIAS(memrxlenq, libc_memrxlenq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemxlenq, libc_rawmemxlenq);
DEFINE_PUBLIC_WEAK_ALIAS(rawmemrxlenq, libc_rawmemrxlenq);
DEFINE_PUBLIC_WEAK_ALIAS(strnchr, libc_strnchr);
DEFINE_PUBLIC_WEAK_ALIAS(strnrchr, libc_strnrchr);
DEFINE_PUBLIC_WEAK_ALIAS(strrchrnul, libc_strrchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(strnchrnul, libc_strnchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(strnrchrnul, libc_strnrchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(stroff, libc_stroff);
DEFINE_PUBLIC_WEAK_ALIAS(strroff, libc_strroff);
DEFINE_PUBLIC_WEAK_ALIAS(strnoff, libc_strnoff);
DEFINE_PUBLIC_WEAK_ALIAS(strnroff, libc_strnroff);
DEFINE_PUBLIC_WEAK_ALIAS(memcasecmp, libc_memcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(_memicmp, libc_memcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(memicmp, libc_memcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(memcasemem, libc_memcasemem);
DEFINE_PUBLIC_WEAK_ALIAS(memcasecmp_l, libc_memcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(_memicmp_l, libc_memcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(memcasemem_l, libc_memcasemem_l);
DEFINE_PUBLIC_WEAK_ALIAS(strcasestr_l, libc_strcasestr_l);
DEFINE_PUBLIC_WEAK_ALIAS(wildstrcmp, libc_wildstrcmp);
DEFINE_PUBLIC_WEAK_ALIAS(wildstrcasecmp, libc_wildstrcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_strcmp, libc_fuzzy_strcmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_strncmp, libc_fuzzy_strncmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_strcasecmp, libc_fuzzy_strcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_strncasecmp, libc_fuzzy_strncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_memcmp, libc_fuzzy_memcmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_memcasecmp, libc_fuzzy_memcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_strcasecmp_l, libc_fuzzy_strcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_strncasecmp_l, libc_fuzzy_strncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(wildstrcasecmp_l, libc_wildstrcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_memcasecmp_l, libc_fuzzy_memcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_memcmpw, libc_fuzzy_memcmpw);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_memcmpl, libc_fuzzy_memcmpl);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_memcmpq, libc_fuzzy_memcmpq);
DEFINE_PUBLIC_WEAK_ALIAS(strncoll, libc_strncoll);
DEFINE_PUBLIC_WEAK_ALIAS(_strncoll, libc_strncoll);
DEFINE_PUBLIC_WEAK_ALIAS(strcasecoll, libc_strcasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(_stricoll, libc_strcasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(strncasecoll, libc_strncasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(_strnicoll, libc_strncasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(strnrev, libc_strnrev);
DEFINE_PUBLIC_WEAK_ALIAS(strnlwr, libc_strnlwr);
DEFINE_PUBLIC_WEAK_ALIAS(strnupr, libc_strnupr);
DEFINE_PUBLIC_WEAK_ALIAS(strncoll_l, libc_strncoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strncoll_l, libc_strncoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(strcasecoll_l, libc_strcasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_stricoll_l, libc_strcasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(strncasecoll_l, libc_strncasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strnicoll_l, libc_strncasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(strlwr_l, libc_strlwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strlwr_l, libc_strlwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(strupr_l, libc_strupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strupr_l, libc_strupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(strnlwr_l, libc_strnlwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(strnupr_l, libc_strnupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(memrev, libc_memrev);
DEFINE_PUBLIC_WEAK_ALIAS(memrevw, libc_memrevw);
DEFINE_PUBLIC_WEAK_ALIAS(memrevl, libc_memrevl);
DEFINE_PUBLIC_WEAK_ALIAS(memrevq, libc_memrevq);
DEFINE_PUBLIC_WEAK_ALIAS(strlwr, libc_strlwr);
DEFINE_PUBLIC_WEAK_ALIAS(_strlwr, libc_strlwr);
DEFINE_PUBLIC_WEAK_ALIAS(strupr, libc_strupr);
DEFINE_PUBLIC_WEAK_ALIAS(_strupr, libc_strupr);
DEFINE_PUBLIC_WEAK_ALIAS(strset, libc_strset);
DEFINE_PUBLIC_WEAK_ALIAS(_strset, libc_strset);
DEFINE_PUBLIC_WEAK_ALIAS(strnset, libc_strnset);
DEFINE_PUBLIC_WEAK_ALIAS(_strnset, libc_strnset);
DEFINE_PUBLIC_WEAK_ALIAS(strrev, libc_strrev);
DEFINE_PUBLIC_WEAK_ALIAS(_strrev, libc_strrev);
DEFINE_PUBLIC_WEAK_ALIAS(_strset_s, libc__strset_s);
DEFINE_PUBLIC_WEAK_ALIAS(memcpy_s, libc_memcpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(memmove_s, libc_memmove_s);
DEFINE_PUBLIC_WEAK_ALIAS(strcpy_s, libc_strcpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(strcat_s, libc_strcat_s);
DEFINE_PUBLIC_WEAK_ALIAS(strncat_s, libc_strncat_s);
DEFINE_PUBLIC_WEAK_ALIAS(strncpy_s, libc_strncpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(_strlwr_s, libc__strlwr_s);
DEFINE_PUBLIC_WEAK_ALIAS(_strupr_s, libc__strupr_s);
DEFINE_PUBLIC_WEAK_ALIAS(_strlwr_s_l, libc__strlwr_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strupr_s_l, libc__strupr_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_strnset_s, libc__strnset_s);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STRING_C */
