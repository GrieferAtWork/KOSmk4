/* HASH CRC-32:0xeabf6072 */
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
#ifndef GUARD_LIBC_AUTO_STRING_C
#define GUARD_LIBC_AUTO_STRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "string.h"
#include "../user/ctype.h"
#include "../user/kos.except.h"
#include "../user/signal.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"

DECL_BEGIN

#include "../user/stdio.h"
#ifndef __KERNEL__
#include "../libc/errno.h"


/* Variants for `__USE_MEMMEM_EMPTY_NEEDLE_NULL' */
DEFINE_PUBLIC_ALIAS(memcasemem0_l, libc_memcasemem0_l);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.unicode.locale.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memcasemem0_l)(void const *haystack, size_t haystacklen,
                                         void const *needle, size_t needlelen,
                                         locale_t locale) {
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = tolower_l(*(byte_t *)needle, locale);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || tolower_l(b, locale) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp_l(candidate, needle, needlelen, locale) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memcasemem0, libc_memcasemem0);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.unicode.static.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memcasemem0)(void const *haystack, size_t haystacklen,
                                       void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = (byte_t)tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || (byte_t)tolower(b) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memmem0, libc_memmem0);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memmem0)(void const *haystack, size_t haystacklen,
                                   void const *needle, size_t needlelen) {
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

DEFINE_PUBLIC_ALIAS(memrmem0, libc_memrmem0);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memrmem0)(void const *haystack, size_t haystacklen,
                                    void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= needlelen - 1;
	marker = *(uint8_t const *)needle;
	while ((candidate = (byte_t *)memrchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		haystacklen = (size_t)(candidate - (byte_t *)haystack);
	}
	return NULL;
}

#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMCPY
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memcpy)(void *__restrict dst,
                                  void const *__restrict src,
                                  size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPY */
#ifndef LIBC_ARCH_HAVE_MEMMOVE
/* >> memmove(3)
 * Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memmove)(void *dst,
                                   void const *src,
                                   size_t n_bytes) {
	byte_t *pdst;
	byte_t const *psrc;
	if (dst <= src) {
		pdst = (byte_t *)dst;
		psrc = (byte_t const *)src;
		while (n_bytes--)
			*pdst++ = *psrc++;
	} else {
		pdst = (byte_t *)dst + n_bytes;
		psrc = (byte_t const *)src + n_bytes;
		while (n_bytes--)
			*--pdst = *--psrc;
	}
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVE */
#ifndef LIBC_ARCH_HAVE_MEMSET
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memset)(void *__restrict dst,
                                  int byte,
                                  size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	while (n_bytes--)
		*pdst++ = (byte_t)byte;
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMSET */
#ifndef LIBC_ARCH_HAVE_MEMCMP
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_memcmp)(void const *s1,
                                  void const *s2,
                                  size_t n_bytes) {
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
#if __SIZEOF_INT__ >= 2
	while (n_bytes-- && ((v1 = *p1++) == (v2 = *p2++)))
		;
	return (int)v1 - (int)v2;
#else /* __SIZEOF_INT__ >= 2 */
	while (n_bytes--) {
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
#endif /* __SIZEOF_INT__ < 2 */
}
#endif /* !LIBC_ARCH_HAVE_MEMCMP */
#ifndef LIBC_ARCH_HAVE_MEMCHR
/* >> memchr(3)
 * Ascendingly search for `needle', starting at `haystack'.
 * Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memchr)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter == (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCHR */
#ifndef LIBC_ARCH_HAVE_STRLEN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_strlen)(char const *__restrict str) {
	return (size_t)(libc_strend(str) - str);
}
#endif /* !LIBC_ARCH_HAVE_STRLEN */
#ifndef LIBC_ARCH_HAVE_STRCHR
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strchr)(char const *__restrict haystack,
                                  int needle) {
	for (;; ++haystack) {
		char ch = *haystack;
		if unlikely((unsigned char)ch == (unsigned char)needle)
			return (char *)haystack;
		if (!ch)
			break;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_STRCHR */
#ifndef LIBC_ARCH_HAVE_STRRCHR
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strrchr)(char const *__restrict haystack,
                                   int needle) {
	char const *result = NULL;
	for (;; ++haystack) {
		char ch = *haystack;
		if unlikely((unsigned char)ch == (unsigned char)needle)
			result = haystack;
		if (!ch)
			break;
	}
	return (char *)result;
}
#endif /* !LIBC_ARCH_HAVE_STRRCHR */
#ifndef LIBC_ARCH_HAVE_STRCMP
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strcmp)(char const *s1,
                                  char const *s2) {
	char c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}
#endif /* !LIBC_ARCH_HAVE_STRCMP */
#ifndef LIBC_ARCH_HAVE_STRNCMP
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncmp)(char const *s1,
                                   char const *s2,
                                   size_t maxlen) {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}
#endif /* !LIBC_ARCH_HAVE_STRNCMP */
#ifndef LIBC_ARCH_HAVE_STRSTR
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *
NOTHROW_NCX(LIBCCALL libc_strstr)(char const *haystack,
                                  char const *needle) {
	char ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_STRSTR */
#ifndef LIBC_ARCH_HAVE_STRCPY
/* >> strcpy(3)
 * Copy a NUL-terminated string `str' to `dst', and re-return `dst'.
 * The exact # of characters copied is `strlen(src) + 1' (+1 because
 * the trailing NUL-character is also copied) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strcpy)(char *__restrict dst,
                                  char const *__restrict src) {
	return (char *)libc_memcpy(dst, src, (libc_strlen(src) + 1) * sizeof(char));
}
#endif /* !LIBC_ARCH_HAVE_STRCPY */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STRNCPY
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space  for doing so is available, up to the `strlen(src)' of
 * the first characters  are copied from  `src'. All  remaining
 * characters are always set  to '\0'. Always re-returns  `buf' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	libc_stpncpy(buf, src, buflen);
	return buf;
}
#endif /* !LIBC_ARCH_HAVE_STRNCPY */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRCAT
/* >> strcat(3)
 * Same as `strcpy(3)',  but rather  than copying `src'  ontop of  `dst',
 * append it at the end of `dst', or more precisely copy to `strend(dst)'
 * Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strcat)(char *__restrict dst,
                                  char const *__restrict src) {
	libc_memcpy(libc_strend(dst), src, (libc_strlen(src) + 1) * sizeof(char));
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_STRCAT */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STRNCAT
/* >> strncat(3)
 * Copy at most max_srclen (or rather: exactly `strnlen(src, max_srclen)')
 * characters   to    `strend(buf)',   and    always   re-return    `buf'. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUT(1) ATTR_INS(2, 3) NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_strncat)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t max_srclen) {
	size_t srclen = libc_strnlen(src, max_srclen);
	char *dst = libc_strend(buf);
	libc_memcpy(dst, src, srclen * sizeof(char));
	dst[srclen] = '\0';
	return buf;
}
#endif /* !LIBC_ARCH_HAVE_STRNCAT */
#ifndef LIBC_ARCH_HAVE_STRCSPN
/* >> strcspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(reject, ch) == NULL'. If no such character
 * exists, return `strlen(haystack)' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc_strcspn)(char const *haystack,
                                   char const *reject) {
	char const *iter = haystack;
	while (*iter && !libc_strchr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRCSPN */
#ifndef LIBC_ARCH_HAVE_STRSPN
/* >> strspn(3)
 * Return the  offset from  `haystack' to  the first  character
 * for which `strchr(accept, ch) != NULL'. If no such character
 * exists, return `strlen(haystack)' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc_strspn)(char const *haystack,
                                  char const *accept) {
	char const *iter = haystack;
	while (*iter && libc_strchr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRSPN */
#ifndef LIBC_ARCH_HAVE_STRPBRK
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *
NOTHROW_NCX(LIBCCALL libc_strpbrk)(char const *haystack,
                                   char const *accept) {
	char haych, ch;
	while ((haych = *haystack++) != '\0') {
		char const *ned_iter;
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char *)haystack - 1;
		}
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_STRPBRK */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_IN(2) ATTR_INOUT_OPT(1) char *
NOTHROW_NCX(LIBCCALL libc_strtok)(char *str,
                                  char const *delim) {
	static char *save_ptr = NULL;
	return libc_strtok_r(str, delim, &save_ptr);
}
#ifndef LIBC_ARCH_HAVE_STRCOLL
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strcoll)(char const *s1,
                                   char const *s2) {
	/* XXX: Implement properly? */
	return libc_strcmp(s1, s2);
}
#endif /* !LIBC_ARCH_HAVE_STRCOLL */
#ifndef LIBC_ARCH_HAVE_STRXFRM
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBCCALL libc_strxfrm)(char *dst,
                                   char const *__restrict src,
                                   size_t buflen) {
	/* XXX: Implement properly? */
	size_t n = libc_strnlen(src, buflen);
	libc_memcpy(dst, src, n * sizeof(char));
	return n;
}
#endif /* !LIBC_ARCH_HAVE_STRXFRM */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_strerror)(errno_t errnum) { return libc_strerror(libd_errno_dos2kos(errnum)); }
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_strerror)(errno_t errnum) {
	static char strerror_buf[64];
	char *result;
	char const *string;
	result = strerror_buf;
	string = libc_strerrordesc_np(errnum);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strerror_buf) - 1] = '\0';
		libc_strncpy(result, string, COMPILER_LENOF(strerror_buf) - 1);
	} else {

		libc_sprintf(result, "Unknown error %d", errnum);

















	}
	return result;
}
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRNLEN
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strnlen)(char const *__restrict str,
                                   size_t maxlen) {
	return (size_t)(libc_strnend(str, maxlen) - str);
}
#endif /* !LIBC_ARCH_HAVE_STRNLEN */
#ifndef LIBC_ARCH_HAVE_STPCPY
/* >> stpcpy(3)
 * Same as `mempcpy(dst, src, (strlen(src) + 1) * sizeof(char)) - 1´ */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) char *
NOTHROW_NCX(LIBCCALL libc_stpcpy)(char *__restrict buf,
                                  char const *__restrict src) {
	return (char *)libc_mempcpy(buf, src, (libc_strlen(src) + 1) * sizeof(char)) - 1;
}
#endif /* !LIBC_ARCH_HAVE_STPCPY */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STPNCPY
/* >> stpncpy(3) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_stpncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_strnlen(src, buflen);
	libc_memcpy(buf, src, srclen * sizeof(char));
	libc_bzero(buf + srclen, (size_t)(buflen - srclen) * sizeof(char));
	return buf + srclen;
}
#endif /* !LIBC_ARCH_HAVE_STPNCPY */
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strcoll_l)(char const *s1,
                                     char const *s2,
                                     locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_strcoll(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBCCALL libc_strxfrm_l)(char *dst,
                                     char const *__restrict src,
                                     size_t buflen,
                                     locale_t locale) {
	(void)locale;
	return libc_strxfrm(dst, src, buflen);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_strerror_l)(errno_t errnum,
                                      locale_t locale) {
	(void)locale;
	return libd_strerror(errnum);
}
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_strerror_l)(errno_t errnum,
                                      locale_t locale) {
	(void)locale;
	return libc_strerror(errnum);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.string.memory.strsignal") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_strsignal)(signo_t signo) { return libc_strerror(libd_signo_dos2kos(signo)); }
INTERN ATTR_SECTION(".text.crt.string.memory.strsignal") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_strsignal)(signo_t signo) {
	static char strsignal_buf[64];
	char *result = strsignal_buf;
	char const *string;
	string = libc_sigdescr_np(signo);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strsignal_buf) - 1] = '\0';
		libc_strncpy(result, string, COMPILER_LENOF(strsignal_buf) - 1);
	} else {
		libc_sprintf(result, "Unknown signal %d", signo);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INS(1, 2) char *
NOTHROW_NCX(LIBCCALL libc_strndup)(char const *__restrict str,
                                   size_t max_chars) {
	size_t resultsize = libc_strnlen(str, max_chars) * sizeof(char);
	char *result = (char *)libc_malloc(resultsize + sizeof(char));
	if likely(result) {
		*(char *)libc_mempcpy(result, str, resultsize) = '\0';
	}
	return result;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strdup)(char const *__restrict string) {
	size_t resultsize = (libc_strlen(string) + 1) * sizeof(char);
	char *result = (char *)libc_malloc(resultsize);
	if likely(result)
		libc_memcpy(result, string, resultsize);
	return result;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) char *
NOTHROW_NCX(LIBCCALL libc_strtok_r)(char *str,
                                    char const *delim,
                                    char **__restrict save_ptr) {
	char *end;
	if (!str)
		str = *save_ptr;
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	str += libc_strspn(str, delim);
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	end = str + libc_strcspn(str, delim);
	if (!*end) {
		*save_ptr = end;
		return str;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return str;
}
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMRCHR
/* >> memrchr(3)
 * Descendingly search for `needle', starting at `haystack + n_bytes'.
 * Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memrchr)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if (*--iter == (byte_t)needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRCHR */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_MEMMEM
#include <features.h>
/* >> memmem(3)
 * Return the first address of a sub-string `needle...+=needlelen'
 * stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memmem)(void const *haystack,
                                  size_t haystacklen,
                                  void const *needle,
                                  size_t needlelen) {
	byte_t *candidate, marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (void *)haystack;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = *(byte_t *)needle;
	while ((candidate = (byte_t *)libc_memchr(haystack, marker, haystacklen)) != NULL) {
		if (libc_memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMMEM */
#endif /* !__KERNEL__ */
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *
NOTHROW_NCX(LIBCCALL libc_strcasestr)(char const *haystack,
                                      char const *needle) {
	for (; *haystack; ++haystack) {
		if (libc_strcasecmp(haystack, needle) == 0)
			return (char *)haystack;
	}
	return NULL;
}
#ifndef LIBC_ARCH_HAVE_STRCHRNUL
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strchrnul)(char const *__restrict haystack,
                                     int needle) {
	for (; *haystack; ++haystack) {
		if ((unsigned char)*haystack == (unsigned char)needle)
			break;
	}
	return (char *)haystack;
}
#endif /* !LIBC_ARCH_HAVE_STRCHRNUL */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHR
#include <hybrid/typecore.h>
/* >> rawmemchr(3)
 * Same as `memchr' with a search limit of `(size_t)-1' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) void *
NOTHROW_NCX(LIBCCALL libc_rawmemchr)(void const *__restrict haystack,
                                     int needle) {
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if (*iter == (byte_t)needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHR */
#ifndef __KERNEL__
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_basename)(char const *filename) {
	/* >> char *slash = strrchr(filename, '/');
	 * >> return slash ? slash + 1 : (char *)filename; */
	char *result, *iter = (char *)filename;





	result = iter;
	for (;;) {
		char ch = *iter++;



		if (ch == '/')

		{
			result = iter;
		}
		if (!ch)
			break;
	}
	return result;
}
/* >> strverscmp(3) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strverscmp)(char const *s1,
                                      char const *s2) {
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

			/* Return difference between digits. */
			return (int)vala - (int)valb;
		}
		++s1;
		++s2;
	} while (c1 != '\0');
	return 0;
}
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMPCPY
/* >> mempcpy(3)
 * Same as `memcpy', but return `dst + n_bytes', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempcpy)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return pdst;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPY */
#ifndef __KERNEL__
#include <hybrid/typecore.h>
/* >> strfry(3) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strfry)(char *__restrict str) {
	size_t i, count = libc_strlen(str);
	for (i = 0; i < count; ++i) {
		char temp;
		size_t j = libc_rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}
#include <hybrid/typecore.h>
/* >> memfrob(3)
 * Xor every byte in `buf...+=num_bytes' with decimal `42' (yeah...)
 * Always re-return the given `buf' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memfrob)(void *buf,
                                   size_t num_bytes) {
	byte_t *iter = (byte_t *)buf;
	while (num_bytes--)
		*iter++ ^= 42; /* -_-   yeah... */
	return buf;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strcasecmp_l)(char const *s1,
                                        char const *s2,
                                        locale_t locale) {
	(void)locale;
	return libc_strcasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strncasecmp_l)(char const *s1,
                                         char const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libc_strncasecmp(s1, s2, maxlen);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_strerrordesc_np)(errno_t errnum) {
	char const *result;
	result = libd_strerrorname_np(errnum);
	if (result)
		result = libc_strend(result) + 1;
	return result;
}
#endif /* !__KERNEL__ */
#ifndef __BUILDING_LIBC
#ifndef ___local_sys_errlist_defined
#define ___local_sys_errlist_defined
#if defined(__CRT_HAVE__sys_errlist) && defined(__CRT_HAVE__sys_nerr)
#ifndef _sys_errlist
__CSDECLARE2(,char const *const _sys_errlist[],_sys_errlist)
#define _sys_errlist _sys_errlist
#endif /* !_sys_errlist */
#ifndef _sys_nerr
__CSDECLARE(,int,_sys_nerr)
#define _sys_nerr _sys_nerr
#endif /* !_sys_nerr */
#elif defined(__CRT_HAVE___sys_errlist) && defined(__CRT_HAVE___sys_nerr)
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,char const *const *,__sys_errlist,(void),())
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST,int *,__sys_nerr,(void),())
#else /* ... */
#undef ___local_sys_errlist_defined
#endif /* !... */
#endif /* !___local_sys_errlist_defined */
#endif /* !__BUILDING_LIBC */
#include <asm/os/errno.h>
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_strerrordesc_np)(errno_t errnum) {





	char const *result;
	result = libc_strerrorname_np(errnum);
	if (result)
		result = libc_strend(result) + 1;
	return result;





















































































































































































































































































































































































































































}
#ifndef __KERNEL__
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_strerrorname_np)(errno_t errnum) {
	/* Special handling for a hand full of errno
	 * values that don't  have KOS  equivalents. */
	switch (errnum) {
	case 80:
		return "STRUNCATE\0" "Truncated";
	case 131:
		return "EOTHER\0" "Other";
	default:
		break;
	}
	errnum = libd_errno_dos2kos(errnum);
	return libc_strerrorname_np(errnum);
}
#endif /* !__KERNEL__ */
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_strerrorname_np)(errno_t errnum) {
/*[[[deemon
import * from deemon;
@@Mapping for id -> (kosName, comment)
local kosErrnoMappings: {int: (string, string)} = Dict();
local inside = false;
with (local fp = File.open("../../../include/asm/os/kos/errno.h")) {
	for (local l: fp) {
		l = l.strip();
		if (l == "/" "*[[[begin]]]*" "/")
			inside = true;
		if (l == "/" "*[[[end]]]*" "/")
			inside = false;
		if (!inside)
			continue;
		local name, value, comment;
		try {
			name, value, comment = l.scanf(" # define __%[^ ] %[^/ ] /" "* %[^]")...;
		} catch (...) {
			continue;
		}
		comment = comment.partition("*" "/")[0].strip();
		while (comment.startswith("["))
			comment = comment.partition("]")[2].lstrip();
		value = int(value.strip());
		if (value in kosErrnoMappings)
			continue;
		kosErrnoMappings[value] = (name, comment);
	}
}
local emax = kosErrnoMappings.keys > ...;
print("#define HAVE_KOS_ERRNO_VALUES");
for (local ids: kosErrnoMappings.keys.sorted().segments(4)) {
	print("@@pp_if ", " || ".join(for (local id: ids)
		"!defined({0}) || {0} != {1}".format({ kosErrnoMappings[id].first, id })),
		"@@");
	print("#undef HAVE_KOS_ERRNO_VALUES");
	print("@@pp_endif@@");
}
kosErrnoMappings[0] = ("EOK", "Success");
print("@@pp_ifdef HAVE_KOS_ERRNO_VALUES@@");
print("	static char const errno_strtab[] =");
local strtab_offsets: {int: int} = Dict();
local currentOffset = 0;
for (local i: [:emax + 1]) {
	local name, comment = kosErrnoMappings.get(i)...;
	if (name is none)
		continue;
	name += "\0";
	if (i != emax)
		comment += "\0";
	print("\t", repr(name + comment));
	strtab_offsets[i] = currentOffset;
	currentOffset += #name;
	currentOffset += #comment;
}
print("	\"\";");
for (local i: [:emax + 1]) {
	if (kosErrnoMappings.get(i) is none)
		strtab_offsets[i] = currentOffset;
}
local sizeofStrTab = currentOffset;
local usedOffsetType = "uint8_t";
if (sizeofStrTab > 0xffff)
	usedOffsetType = "uint32_t";
else if (sizeofStrTab > 0xff)
	usedOffsetType = "uint16_t";
print("	static ", usedOffsetType, " const errno_offsets[", (emax + 1), "] = {");
for (local i: [:emax + 1].segments(16))
	print("\t\t", ", ".join(for (local x: i) strtab_offsets[x]), ",");
print("	};");
]]]*/
#define HAVE_KOS_ERRNO_VALUES
#if !defined(EPERM) || EPERM != 1 || !defined(ENOENT) || ENOENT != 2 || !defined(ESRCH) || ESRCH != 3 || !defined(EINTR) || EINTR != 4
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EPERM || EPERM != 1 || !ENOENT || ENOENT != 2 || !ESRCH || ESRCH != 3 || !EINTR || EINTR != 4 */
#if !defined(EIO) || EIO != 5 || !defined(ENXIO) || ENXIO != 6 || !defined(E2BIG) || E2BIG != 7 || !defined(ENOEXEC) || ENOEXEC != 8
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EIO || EIO != 5 || !ENXIO || ENXIO != 6 || !E2BIG || E2BIG != 7 || !ENOEXEC || ENOEXEC != 8 */
#if !defined(EBADF) || EBADF != 9 || !defined(ECHILD) || ECHILD != 10 || !defined(EAGAIN) || EAGAIN != 11 || !defined(ENOMEM) || ENOMEM != 12
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EBADF || EBADF != 9 || !ECHILD || ECHILD != 10 || !EAGAIN || EAGAIN != 11 || !ENOMEM || ENOMEM != 12 */
#if !defined(EACCES) || EACCES != 13 || !defined(EFAULT) || EFAULT != 14 || !defined(ENOTBLK) || ENOTBLK != 15 || !defined(EBUSY) || EBUSY != 16
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EACCES || EACCES != 13 || !EFAULT || EFAULT != 14 || !ENOTBLK || ENOTBLK != 15 || !EBUSY || EBUSY != 16 */
#if !defined(EEXIST) || EEXIST != 17 || !defined(EXDEV) || EXDEV != 18 || !defined(ENODEV) || ENODEV != 19 || !defined(ENOTDIR) || ENOTDIR != 20
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EEXIST || EEXIST != 17 || !EXDEV || EXDEV != 18 || !ENODEV || ENODEV != 19 || !ENOTDIR || ENOTDIR != 20 */
#if !defined(EISDIR) || EISDIR != 21 || !defined(EINVAL) || EINVAL != 22 || !defined(ENFILE) || ENFILE != 23 || !defined(EMFILE) || EMFILE != 24
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EISDIR || EISDIR != 21 || !EINVAL || EINVAL != 22 || !ENFILE || ENFILE != 23 || !EMFILE || EMFILE != 24 */
#if !defined(ENOTTY) || ENOTTY != 25 || !defined(ETXTBSY) || ETXTBSY != 26 || !defined(EFBIG) || EFBIG != 27 || !defined(ENOSPC) || ENOSPC != 28
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOTTY || ENOTTY != 25 || !ETXTBSY || ETXTBSY != 26 || !EFBIG || EFBIG != 27 || !ENOSPC || ENOSPC != 28 */
#if !defined(ESPIPE) || ESPIPE != 29 || !defined(EROFS) || EROFS != 30 || !defined(EMLINK) || EMLINK != 31 || !defined(EPIPE) || EPIPE != 32
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ESPIPE || ESPIPE != 29 || !EROFS || EROFS != 30 || !EMLINK || EMLINK != 31 || !EPIPE || EPIPE != 32 */
#if !defined(EDOM) || EDOM != 33 || !defined(ERANGE) || ERANGE != 34 || !defined(EDEADLK) || EDEADLK != 35 || !defined(ENAMETOOLONG) || ENAMETOOLONG != 36
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EDOM || EDOM != 33 || !ERANGE || ERANGE != 34 || !EDEADLK || EDEADLK != 35 || !ENAMETOOLONG || ENAMETOOLONG != 36 */
#if !defined(ENOLCK) || ENOLCK != 37 || !defined(ENOSYS) || ENOSYS != 38 || !defined(ENOTEMPTY) || ENOTEMPTY != 39 || !defined(ELOOP) || ELOOP != 40
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOLCK || ENOLCK != 37 || !ENOSYS || ENOSYS != 38 || !ENOTEMPTY || ENOTEMPTY != 39 || !ELOOP || ELOOP != 40 */
#if !defined(ENOMSG) || ENOMSG != 42 || !defined(EIDRM) || EIDRM != 43 || !defined(ECHRNG) || ECHRNG != 44 || !defined(EL2NSYNC) || EL2NSYNC != 45
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOMSG || ENOMSG != 42 || !EIDRM || EIDRM != 43 || !ECHRNG || ECHRNG != 44 || !EL2NSYNC || EL2NSYNC != 45 */
#if !defined(EL3HLT) || EL3HLT != 46 || !defined(EL3RST) || EL3RST != 47 || !defined(ELNRNG) || ELNRNG != 48 || !defined(EUNATCH) || EUNATCH != 49
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EL3HLT || EL3HLT != 46 || !EL3RST || EL3RST != 47 || !ELNRNG || ELNRNG != 48 || !EUNATCH || EUNATCH != 49 */
#if !defined(ENOCSI) || ENOCSI != 50 || !defined(EL2HLT) || EL2HLT != 51 || !defined(EBADE) || EBADE != 52 || !defined(EBADR) || EBADR != 53
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOCSI || ENOCSI != 50 || !EL2HLT || EL2HLT != 51 || !EBADE || EBADE != 52 || !EBADR || EBADR != 53 */
#if !defined(EXFULL) || EXFULL != 54 || !defined(ENOANO) || ENOANO != 55 || !defined(EBADRQC) || EBADRQC != 56 || !defined(EBADSLT) || EBADSLT != 57
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EXFULL || EXFULL != 54 || !ENOANO || ENOANO != 55 || !EBADRQC || EBADRQC != 56 || !EBADSLT || EBADSLT != 57 */
#if !defined(EBFONT) || EBFONT != 59 || !defined(ENOSTR) || ENOSTR != 60 || !defined(ENODATA) || ENODATA != 61 || !defined(ETIME) || ETIME != 62
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EBFONT || EBFONT != 59 || !ENOSTR || ENOSTR != 60 || !ENODATA || ENODATA != 61 || !ETIME || ETIME != 62 */
#if !defined(ENOSR) || ENOSR != 63 || !defined(ENONET) || ENONET != 64 || !defined(ENOPKG) || ENOPKG != 65 || !defined(EREMOTE) || EREMOTE != 66
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOSR || ENOSR != 63 || !ENONET || ENONET != 64 || !ENOPKG || ENOPKG != 65 || !EREMOTE || EREMOTE != 66 */
#if !defined(ENOLINK) || ENOLINK != 67 || !defined(EADV) || EADV != 68 || !defined(ESRMNT) || ESRMNT != 69 || !defined(ECOMM) || ECOMM != 70
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOLINK || ENOLINK != 67 || !EADV || EADV != 68 || !ESRMNT || ESRMNT != 69 || !ECOMM || ECOMM != 70 */
#if !defined(EPROTO) || EPROTO != 71 || !defined(EMULTIHOP) || EMULTIHOP != 72 || !defined(EDOTDOT) || EDOTDOT != 73 || !defined(EBADMSG) || EBADMSG != 74
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EPROTO || EPROTO != 71 || !EMULTIHOP || EMULTIHOP != 72 || !EDOTDOT || EDOTDOT != 73 || !EBADMSG || EBADMSG != 74 */
#if !defined(EOVERFLOW) || EOVERFLOW != 75 || !defined(ENOTUNIQ) || ENOTUNIQ != 76 || !defined(EBADFD) || EBADFD != 77 || !defined(EREMCHG) || EREMCHG != 78
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EOVERFLOW || EOVERFLOW != 75 || !ENOTUNIQ || ENOTUNIQ != 76 || !EBADFD || EBADFD != 77 || !EREMCHG || EREMCHG != 78 */
#if !defined(ELIBACC) || ELIBACC != 79 || !defined(ELIBBAD) || ELIBBAD != 80 || !defined(ELIBSCN) || ELIBSCN != 81 || !defined(ELIBMAX) || ELIBMAX != 82
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ELIBACC || ELIBACC != 79 || !ELIBBAD || ELIBBAD != 80 || !ELIBSCN || ELIBSCN != 81 || !ELIBMAX || ELIBMAX != 82 */
#if !defined(ELIBEXEC) || ELIBEXEC != 83 || !defined(EILSEQ) || EILSEQ != 84 || !defined(ERESTART) || ERESTART != 85 || !defined(ESTRPIPE) || ESTRPIPE != 86
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ELIBEXEC || ELIBEXEC != 83 || !EILSEQ || EILSEQ != 84 || !ERESTART || ERESTART != 85 || !ESTRPIPE || ESTRPIPE != 86 */
#if !defined(EUSERS) || EUSERS != 87 || !defined(ENOTSOCK) || ENOTSOCK != 88 || !defined(EDESTADDRREQ) || EDESTADDRREQ != 89 || !defined(EMSGSIZE) || EMSGSIZE != 90
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EUSERS || EUSERS != 87 || !ENOTSOCK || ENOTSOCK != 88 || !EDESTADDRREQ || EDESTADDRREQ != 89 || !EMSGSIZE || EMSGSIZE != 90 */
#if !defined(EPROTOTYPE) || EPROTOTYPE != 91 || !defined(ENOPROTOOPT) || ENOPROTOOPT != 92 || !defined(EPROTONOSUPPORT) || EPROTONOSUPPORT != 93 || !defined(ESOCKTNOSUPPORT) || ESOCKTNOSUPPORT != 94
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EPROTOTYPE || EPROTOTYPE != 91 || !ENOPROTOOPT || ENOPROTOOPT != 92 || !EPROTONOSUPPORT || EPROTONOSUPPORT != 93 || !ESOCKTNOSUPPORT || ESOCKTNOSUPPORT != 94 */
#if !defined(EOPNOTSUPP) || EOPNOTSUPP != 95 || !defined(EPFNOSUPPORT) || EPFNOSUPPORT != 96 || !defined(EAFNOSUPPORT) || EAFNOSUPPORT != 97 || !defined(EADDRINUSE) || EADDRINUSE != 98
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EOPNOTSUPP || EOPNOTSUPP != 95 || !EPFNOSUPPORT || EPFNOSUPPORT != 96 || !EAFNOSUPPORT || EAFNOSUPPORT != 97 || !EADDRINUSE || EADDRINUSE != 98 */
#if !defined(EADDRNOTAVAIL) || EADDRNOTAVAIL != 99 || !defined(ENETDOWN) || ENETDOWN != 100 || !defined(ENETUNREACH) || ENETUNREACH != 101 || !defined(ENETRESET) || ENETRESET != 102
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EADDRNOTAVAIL || EADDRNOTAVAIL != 99 || !ENETDOWN || ENETDOWN != 100 || !ENETUNREACH || ENETUNREACH != 101 || !ENETRESET || ENETRESET != 102 */
#if !defined(ECONNABORTED) || ECONNABORTED != 103 || !defined(ECONNRESET) || ECONNRESET != 104 || !defined(ENOBUFS) || ENOBUFS != 105 || !defined(EISCONN) || EISCONN != 106
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ECONNABORTED || ECONNABORTED != 103 || !ECONNRESET || ECONNRESET != 104 || !ENOBUFS || ENOBUFS != 105 || !EISCONN || EISCONN != 106 */
#if !defined(ENOTCONN) || ENOTCONN != 107 || !defined(ESHUTDOWN) || ESHUTDOWN != 108 || !defined(ETOOMANYREFS) || ETOOMANYREFS != 109 || !defined(ETIMEDOUT) || ETIMEDOUT != 110
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOTCONN || ENOTCONN != 107 || !ESHUTDOWN || ESHUTDOWN != 108 || !ETOOMANYREFS || ETOOMANYREFS != 109 || !ETIMEDOUT || ETIMEDOUT != 110 */
#if !defined(ECONNREFUSED) || ECONNREFUSED != 111 || !defined(EHOSTDOWN) || EHOSTDOWN != 112 || !defined(EHOSTUNREACH) || EHOSTUNREACH != 113 || !defined(EALREADY) || EALREADY != 114
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ECONNREFUSED || ECONNREFUSED != 111 || !EHOSTDOWN || EHOSTDOWN != 112 || !EHOSTUNREACH || EHOSTUNREACH != 113 || !EALREADY || EALREADY != 114 */
#if !defined(EINPROGRESS) || EINPROGRESS != 115 || !defined(ESTALE) || ESTALE != 116 || !defined(EUCLEAN) || EUCLEAN != 117 || !defined(ENOTNAM) || ENOTNAM != 118
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EINPROGRESS || EINPROGRESS != 115 || !ESTALE || ESTALE != 116 || !EUCLEAN || EUCLEAN != 117 || !ENOTNAM || ENOTNAM != 118 */
#if !defined(ENAVAIL) || ENAVAIL != 119 || !defined(EISNAM) || EISNAM != 120 || !defined(EREMOTEIO) || EREMOTEIO != 121 || !defined(EDQUOT) || EDQUOT != 122
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENAVAIL || ENAVAIL != 119 || !EISNAM || EISNAM != 120 || !EREMOTEIO || EREMOTEIO != 121 || !EDQUOT || EDQUOT != 122 */
#if !defined(ENOMEDIUM) || ENOMEDIUM != 123 || !defined(EMEDIUMTYPE) || EMEDIUMTYPE != 124 || !defined(ECANCELED) || ECANCELED != 125 || !defined(ENOKEY) || ENOKEY != 126
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOMEDIUM || ENOMEDIUM != 123 || !EMEDIUMTYPE || EMEDIUMTYPE != 124 || !ECANCELED || ECANCELED != 125 || !ENOKEY || ENOKEY != 126 */
#if !defined(EKEYEXPIRED) || EKEYEXPIRED != 127 || !defined(EKEYREVOKED) || EKEYREVOKED != 128 || !defined(EKEYREJECTED) || EKEYREJECTED != 129 || !defined(EOWNERDEAD) || EOWNERDEAD != 130
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !EKEYEXPIRED || EKEYEXPIRED != 127 || !EKEYREVOKED || EKEYREVOKED != 128 || !EKEYREJECTED || EKEYREJECTED != 129 || !EOWNERDEAD || EOWNERDEAD != 130 */
#if !defined(ENOTRECOVERABLE) || ENOTRECOVERABLE != 131 || !defined(ERFKILL) || ERFKILL != 132 || !defined(EHWPOISON) || EHWPOISON != 133
#undef HAVE_KOS_ERRNO_VALUES
#endif /* !ENOTRECOVERABLE || ENOTRECOVERABLE != 131 || !ERFKILL || ERFKILL != 132 || !EHWPOISON || EHWPOISON != 133 */
#ifdef HAVE_KOS_ERRNO_VALUES
	static char const errno_strtab[] =
	"EOK\0Success\0"
	"EPERM\0Operation not permitted\0"
	"ENOENT\0No such file or directory\0"
	"ESRCH\0No such process\0"
	"EINTR\0Interrupted system call\0"
	"EIO\0I/O error\0"
	"ENXIO\0No such device or address\0"
	"E2BIG\0Argument list too long\0"
	"ENOEXEC\0Exec format error\0"
	"EBADF\0Bad file number\0"
	"ECHILD\0No child processes\0"
	"EAGAIN\0Try again\0"
	"ENOMEM\0Out of memory\0"
	"EACCES\0Permission denied\0"
	"EFAULT\0Bad address\0"
	"ENOTBLK\0Block device required\0"
	"EBUSY\0Device or resource busy\0"
	"EEXIST\0File exists\0"
	"EXDEV\0Cross-device link\0"
	"ENODEV\0No such device\0"
	"ENOTDIR\0Not a directory\0"
	"EISDIR\0Is a directory\0"
	"EINVAL\0Invalid argument\0"
	"ENFILE\0File table overflow\0"
	"EMFILE\0Too many open files\0"
	"ENOTTY\0Not a typewriter\0"
	"ETXTBSY\0Text file busy\0"
	"EFBIG\0File too large\0"
	"ENOSPC\0No space left on device\0"
	"ESPIPE\0Illegal seek\0"
	"EROFS\0Read-only file system\0"
	"EMLINK\0Too many links\0"
	"EPIPE\0Broken pipe\0"
	"EDOM\0Math argument out of domain of func\0"
	"ERANGE\0Math result not representable\0"
	"EDEADLK\0Resource deadlock would occur\0"
	"ENAMETOOLONG\0File name too long\0"
	"ENOLCK\0No record locks available\0"
	"ENOSYS\0Function not implemented\0"
	"ENOTEMPTY\0Directory not empty\0"
	"ELOOP\0Too many symbolic links encountered\0"
	"ENOMSG\0No message of desired type\0"
	"EIDRM\0Identifier removed\0"
	"ECHRNG\0Channel number out of range\0"
	"EL2NSYNC\0Level 2 not synchronized\0"
	"EL3HLT\0Level 3 halted\0"
	"EL3RST\0Level 3 reset\0"
	"ELNRNG\0Link number out of range\0"
	"EUNATCH\0Protocol driver not attached\0"
	"ENOCSI\0No CSI structure available\0"
	"EL2HLT\0Level 2 halted\0"
	"EBADE\0Invalid exchange\0"
	"EBADR\0Invalid request descriptor\0"
	"EXFULL\0Exchange full\0"
	"ENOANO\0No anode\0"
	"EBADRQC\0Invalid request code\0"
	"EBADSLT\0Invalid slot\0"
	"EBFONT\0Bad font file format\0"
	"ENOSTR\0Device not a stream\0"
	"ENODATA\0No data available\0"
	"ETIME\0Timer expired\0"
	"ENOSR\0Out of streams resources\0"
	"ENONET\0Machine is not on the network\0"
	"ENOPKG\0Package not installed\0"
	"EREMOTE\0Object is remote\0"
	"ENOLINK\0Link has been severed\0"
	"EADV\0Advertise error\0"
	"ESRMNT\0Srmount error\0"
	"ECOMM\0Communication error on send\0"
	"EPROTO\0Protocol error\0"
	"EMULTIHOP\0Multihop attempted\0"
	"EDOTDOT\0RFS specific error\0"
	"EBADMSG\0Not a data message\0"
	"EOVERFLOW\0Value too large for defined data type\0"
	"ENOTUNIQ\0Name not unique on network\0"
	"EBADFD\0File descriptor in bad state\0"
	"EREMCHG\0Remote address changed\0"
	"ELIBACC\0Can not access a needed shared library\0"
	"ELIBBAD\0Accessing a corrupted shared library\0"
	"ELIBSCN\0.lib section in a.out corrupted\0"
	"ELIBMAX\0Attempting to link in too many shared libraries\0"
	"ELIBEXEC\0Cannot exec a shared library directly\0"
	"EILSEQ\0Illegal byte sequence\0"
	"ERESTART\0Interrupted system call should be restarted\0"
	"ESTRPIPE\0Streams pipe error\0"
	"EUSERS\0Too many users\0"
	"ENOTSOCK\0Socket operation on non-socket\0"
	"EDESTADDRREQ\0Destination address required\0"
	"EMSGSIZE\0Message too long\0"
	"EPROTOTYPE\0Protocol wrong type for socket\0"
	"ENOPROTOOPT\0Protocol not available\0"
	"EPROTONOSUPPORT\0Protocol not supported\0"
	"ESOCKTNOSUPPORT\0Socket type not supported\0"
	"EOPNOTSUPP\0Operation not supported on transport endpoint\0"
	"EPFNOSUPPORT\0Protocol family not supported\0"
	"EAFNOSUPPORT\0Address family not supported by protocol\0"
	"EADDRINUSE\0Address already in use\0"
	"EADDRNOTAVAIL\0Cannot assign requested address\0"
	"ENETDOWN\0Network is down\0"
	"ENETUNREACH\0Network is unreachable\0"
	"ENETRESET\0Network dropped connection because of reset\0"
	"ECONNABORTED\0Software caused connection abort\0"
	"ECONNRESET\0Connection reset by peer\0"
	"ENOBUFS\0No buffer space available\0"
	"EISCONN\0Transport endpoint is already connected\0"
	"ENOTCONN\0Transport endpoint is not connected\0"
	"ESHUTDOWN\0Cannot send after transport endpoint shutdown\0"
	"ETOOMANYREFS\0Too many references: cannot splice\0"
	"ETIMEDOUT\0Connection timed out\0"
	"ECONNREFUSED\0Connection refused\0"
	"EHOSTDOWN\0Host is down\0"
	"EHOSTUNREACH\0No route to host\0"
	"EALREADY\0Operation already in progress\0"
	"EINPROGRESS\0Operation now in progress\0"
	"ESTALE\0Stale file handle\0"
	"EUCLEAN\0Structure needs cleaning\0"
	"ENOTNAM\0Not a XENIX named type file\0"
	"ENAVAIL\0No XENIX semaphores available\0"
	"EISNAM\0Is a named type file\0"
	"EREMOTEIO\0Remote I/O error\0"
	"EDQUOT\0Quota exceeded\0"
	"ENOMEDIUM\0No medium found\0"
	"EMEDIUMTYPE\0Wrong medium type\0"
	"ECANCELED\0Operation canceled\0"
	"ENOKEY\0Required key not available\0"
	"EKEYEXPIRED\0Key has expired\0"
	"EKEYREVOKED\0Key has been revoked\0"
	"EKEYREJECTED\0Key was rejected by service\0"
	"EOWNERDEAD\0Owner died\0"
	"ENOTRECOVERABLE\0State not recoverable\0"
	"ERFKILL\0Operation not possible due to RF-kill\0"
	"EHWPOISON\0Memory page has hardware error"
	"";
	static uint16_t const errno_offsets[134] = {
		0, 12, 42, 75, 97, 127, 141, 173, 202, 228, 250, 276, 293, 314, 339, 358,
		388, 418, 437, 461, 483, 507, 529, 553, 580, 607, 631, 654, 675, 706, 726, 754,
		776, 794, 835, 872, 910, 942, 975, 1007, 1037, 4166, 1079, 1113, 1138, 1173, 1207, 1229,
		1250, 1282, 1319, 1353, 1375, 1398, 1431, 1452, 1468, 1497, 4166, 1518, 1546, 1573, 1599, 1619,
		1650, 1687, 1716, 1741, 1771, 1792, 1813, 1847, 1869, 1898, 1925, 1952, 2000, 2036, 2072, 2103,
		2150, 2195, 2235, 2291, 2338, 2367, 2420, 2448, 2470, 2510, 2552, 2578, 2620, 2655, 2694, 2736,
		2793, 2836, 2890, 2924, 2970, 2995, 3030, 3084, 3130, 3166, 3200, 3248, 3293, 3349, 3397, 3428,
		3460, 3483, 3513, 3552, 3590, 3615, 3648, 3684, 3722, 3750, 3777, 3799, 3825, 3855, 3884, 3918,
		3946, 3979, 4020, 4042, 4080, 4126,
	};
/*[[[end]]]*/
	char const *result;
	if ((unsigned int)errnum >= COMPILER_LENOF(errno_offsets))
		return NULL;
	result = &errno_strtab[errno_offsets[errnum]];
	if (!*result)
		result = NULL;
	return result;
#else /* HAVE_KOS_ERRNO_VALUES */
	char const *result;
	switch (errnum) {

#ifdef EPERM
	case EPERM:           result = "EPERM\0Operation not permitted"; break;
#endif /* EPERM */
#ifdef ENOENT
	case ENOENT:          result = "ENOENT\0No such file or directory"; break;
#endif /* ENOENT */
#ifdef ESRCH
	case ESRCH:           result = "ESRCH\0No such process"; break;
#endif /* ESRCH */
#ifdef EINTR
	case EINTR:           result = "EINTR\0Interrupted system call"; break;
#endif /* EINTR */
#ifdef EIO
	case EIO:             result = "EIO\0I/O error"; break;
#endif /* EIO */
#ifdef ENXIO
	case ENXIO:           result = "ENXIO\0No such device or address"; break;
#endif /* ENXIO */
#ifdef E2BIG
	case E2BIG:           result = "E2BIG\0Argument list too long"; break;
#endif /* E2BIG */
#ifdef ENOEXEC
	case ENOEXEC:         result = "ENOEXEC\0Exec format error"; break;
#endif /* ENOEXEC */
#ifdef EBADF
	case EBADF:           result = "EBADF\0Bad file number"; break;
#endif /* EBADF */
#ifdef ECHILD
	case ECHILD:          result = "ECHILD\0No child processes"; break;
#endif /* ECHILD */
#ifdef EAGAIN
	case EAGAIN:          result = "EAGAIN\0Try again"; break;
#endif /* EAGAIN */
#ifdef ENOMEM
	case ENOMEM:          result = "ENOMEM\0Out of memory"; break;
#endif /* ENOMEM */
#ifdef EACCES
	case EACCES:          result = "EACCES\0Permission denied"; break;
#endif /* EACCES */
#ifdef EFAULT
	case EFAULT:          result = "EFAULT\0Bad address"; break;
#endif /* EFAULT */
#ifdef EBUSY
	case EBUSY:           result = "EBUSY\0Device or resource busy"; break;
#endif /* EBUSY */
#ifdef EEXIST
	case EEXIST:          result = "EEXIST\0File exists"; break;
#endif /* EEXIST */
#ifdef EXDEV
	case EXDEV:           result = "EXDEV\0Cross-device link"; break;
#endif /* EXDEV */
#ifdef ENODEV
	case ENODEV:          result = "ENODEV\0No such device"; break;
#endif /* ENODEV */
#ifdef ENOTDIR
	case ENOTDIR:         result = "ENOTDIR\0Not a directory"; break;
#endif /* ENOTDIR */
#ifdef EISDIR
	case EISDIR:          result = "EISDIR\0Is a directory"; break;
#endif /* EISDIR */
#ifdef ENFILE
	case ENFILE:          result = "ENFILE\0File table overflow"; break;
#endif /* ENFILE */
#ifdef EMFILE
	case EMFILE:          result = "EMFILE\0Too many open files"; break;
#endif /* EMFILE */
#ifdef ENOTTY
	case ENOTTY:          result = "ENOTTY\0Not a typewriter"; break;
#endif /* ENOTTY */
#ifdef EFBIG
	case EFBIG:           result = "EFBIG\0File too large"; break;
#endif /* EFBIG */
#ifdef ENOSPC
	case ENOSPC:          result = "ENOSPC\0No space left on device"; break;
#endif /* ENOSPC */
#ifdef ESPIPE
	case ESPIPE:          result = "ESPIPE\0Illegal seek"; break;
#endif /* ESPIPE */
#ifdef EROFS
	case EROFS:           result = "EROFS\0Read-only file system"; break;
#endif /* EROFS */
#ifdef EMLINK
	case EMLINK:          result = "EMLINK\0Too many links"; break;
#endif /* EMLINK */
#ifdef EPIPE
	case EPIPE:           result = "EPIPE\0Broken pipe"; break;
#endif /* EPIPE */
#ifdef EDOM
	case EDOM:            result = "EDOM\0Math argument out of domain of func"; break;
#endif /* EDOM */
#ifdef ENAMETOOLONG
	case ENAMETOOLONG:    result = "ENAMETOOLONG\0File name too long"; break;
#endif /* ENAMETOOLONG */
#ifdef ENOLCK
	case ENOLCK:          result = "ENOLCK\0No record locks available"; break;
#endif /* ENOLCK */
#ifdef ENOSYS
	case ENOSYS:          result = "ENOSYS\0Function not implemented"; break;
#endif /* ENOSYS */
#ifdef ENOTEMPTY
	case ENOTEMPTY:       result = "ENOTEMPTY\0Directory not empty"; break;
#endif /* ENOTEMPTY */
#ifdef EINVAL
	case EINVAL:          result = "EINVAL\0Invalid argument"; break;
#endif /* EINVAL */
#ifdef ERANGE
	case ERANGE:          result = "ERANGE\0Math result not representable"; break;
#endif /* ERANGE */
#ifdef EILSEQ
	case EILSEQ:          result = "EILSEQ\0Illegal byte sequence"; break;
#endif /* EILSEQ */
#ifdef EDEADLOCK
	case EDEADLOCK:       result = "EDEADLOCK\0Resource deadlock would occur"; break;
#endif /* EDEADLOCK */
#ifdef EADDRINUSE
	case EADDRINUSE:      result = "EADDRINUSE\0Address already in use"; break;
#endif /* EADDRINUSE */
#ifdef EADDRNOTAVAIL
	case EADDRNOTAVAIL:   result = "EADDRNOTAVAIL\0Cannot assign requested address"; break;
#endif /* EADDRNOTAVAIL */
#ifdef EAFNOSUPPORT
	case EAFNOSUPPORT:    result = "EAFNOSUPPORT\0Address family not supported by protocol"; break;
#endif /* EAFNOSUPPORT */
#ifdef EALREADY
	case EALREADY:        result = "EALREADY\0Operation already in progress"; break;
#endif /* EALREADY */
#ifdef EBADMSG
	case EBADMSG:         result = "EBADMSG\0Not a data message"; break;
#endif /* EBADMSG */
#ifdef ECANCELED
	case ECANCELED:       result = "ECANCELED\0Operation Canceled"; break;
#endif /* ECANCELED */
#ifdef ECONNABORTED
	case ECONNABORTED:    result = "ECONNABORTED\0Software caused connection abort"; break;
#endif /* ECONNABORTED */
#ifdef ECONNREFUSED
	case ECONNREFUSED:    result = "ECONNREFUSED\0Connection refused"; break;
#endif /* ECONNREFUSED */
#ifdef ECONNRESET
	case ECONNRESET:      result = "ECONNRESET\0Connection reset by peer"; break;
#endif /* ECONNRESET */
#ifdef EDESTADDRREQ
	case EDESTADDRREQ:    result = "EDESTADDRREQ\0Destination address required"; break;
#endif /* EDESTADDRREQ */
#ifdef EHOSTUNREACH
	case EHOSTUNREACH:    result = "EHOSTUNREACH\0No route to host"; break;
#endif /* EHOSTUNREACH */
#ifdef EIDRM
	case EIDRM:           result = "EIDRM\0Identifier removed"; break;
#endif /* EIDRM */
#ifdef EINPROGRESS
	case EINPROGRESS:     result = "EINPROGRESS\0Operation now in progress"; break;
#endif /* EINPROGRESS */
#ifdef EISCONN
	case EISCONN:         result = "EISCONN\0Transport endpoint is already connected"; break;
#endif /* EISCONN */
#ifdef ELOOP
	case ELOOP:           result = "ELOOP\0Too many symbolic links encountered"; break;
#endif /* ELOOP */
#ifdef EMSGSIZE
	case EMSGSIZE:        result = "EMSGSIZE\0Message too long"; break;
#endif /* EMSGSIZE */
#ifdef ENETDOWN
	case ENETDOWN:        result = "ENETDOWN\0Network is down"; break;
#endif /* ENETDOWN */
#ifdef ENETRESET
	case ENETRESET:       result = "ENETRESET\0Network dropped connection because of reset"; break;
#endif /* ENETRESET */
#ifdef ENETUNREACH
	case ENETUNREACH:     result = "ENETUNREACH\0Network is unreachable"; break;
#endif /* ENETUNREACH */
#ifdef ENOBUFS
	case ENOBUFS:         result = "ENOBUFS\0No buffer space available"; break;
#endif /* ENOBUFS */
#ifdef ENODATA
	case ENODATA:         result = "ENODATA\0No data available"; break;
#endif /* ENODATA */
#ifdef ENOLINK
	case ENOLINK:         result = "ENOLINK\0Link has been severed"; break;
#endif /* ENOLINK */
#ifdef ENOMSG
	case ENOMSG:          result = "ENOMSG\0No message of desired type"; break;
#endif /* ENOMSG */
#ifdef ENOPROTOOPT
	case ENOPROTOOPT:     result = "ENOPROTOOPT\0Protocol not available"; break;
#endif /* ENOPROTOOPT */
#ifdef ENOSR
	case ENOSR:           result = "ENOSR\0Out of streams resources"; break;
#endif /* ENOSR */
#ifdef ENOSTR
	case ENOSTR:          result = "ENOSTR\0Device not a stream"; break;
#endif /* ENOSTR */
#ifdef ENOTCONN
	case ENOTCONN:        result = "ENOTCONN\0Transport endpoint is not connected"; break;
#endif /* ENOTCONN */
#ifdef ENOTRECOVERABLE
	case ENOTRECOVERABLE: result = "ENOTRECOVERABLE\0State not recoverable"; break;
#endif /* ENOTRECOVERABLE */
#ifdef ENOTSOCK
	case ENOTSOCK:        result = "ENOTSOCK\0Socket operation on non-socket"; break;
#endif /* ENOTSOCK */
#ifdef ENOTSUP
	case ENOTSUP:         result = "ENOTSUP\0Not supported"; break;
#endif /* ENOTSUP */
#ifdef EOPNOTSUPP
	case EOPNOTSUPP:      result = "EOPNOTSUPP\0Operation not supported on transport endpoint"; break;
#endif /* EOPNOTSUPP */
#ifdef EOTHER
	case EOTHER:          result = "EOTHER\0Other"; break;
#endif /* EOTHER */
#ifdef EOVERFLOW
	case EOVERFLOW:       result = "EOVERFLOW\0Value too large for defined data type"; break;
#endif /* EOVERFLOW */
#ifdef EOWNERDEAD
	case EOWNERDEAD:      result = "EOWNERDEAD\0Owner died"; break;
#endif /* EOWNERDEAD */
#ifdef EPROTO
	case EPROTO:          result = "EPROTO\0Protocol error"; break;
#endif /* EPROTO */
#ifdef EPROTONOSUPPORT
	case EPROTONOSUPPORT: result = "EPROTONOSUPPORT\0Protocol not supported"; break;
#endif /* EPROTONOSUPPORT */
#ifdef EPROTOTYPE
	case EPROTOTYPE:      result = "EPROTOTYPE\0Protocol wrong type for socket"; break;
#endif /* EPROTOTYPE */
#ifdef ETIME
	case ETIME:           result = "ETIME\0Timer expired"; break;
#endif /* ETIME */
#ifdef ETIMEDOUT
	case ETIMEDOUT:       result = "ETIMEDOUT\0Connection timed out"; break;
#endif /* ETIMEDOUT */
#ifdef ETXTBSY
	case ETXTBSY:         result = "ETXTBSY\0Text file busy"; break;
#endif /* ETXTBSY */
#ifdef EFTYPE
	case EFTYPE:          result = "EFTYPE\0Inappropriate file type or format"; break;
#endif /* EFTYPE */
#ifdef ENMFILE
	case ENMFILE:         result = "ENMFILE\0No more files"; break;
#endif /* ENMFILE */
#ifdef EPFNOSUPPORT
	case EPFNOSUPPORT:    result = "EPFNOSUPPORT\0Protocol family not supported"; break;
#endif /* EPFNOSUPPORT */
#ifdef EHOSTDOWN
	case EHOSTDOWN:       result = "EHOSTDOWN\0Host is down"; break;
#endif /* EHOSTDOWN */
#ifdef ETOOMANYREFS
	case ETOOMANYREFS:    result = "ETOOMANYREFS\0Too many references: cannot splice"; break;
#endif /* ETOOMANYREFS */
#ifdef EDQUOT
	case EDQUOT:          result = "EDQUOT\0Quota exceeded"; break;
#endif /* EDQUOT */
#ifdef ESTALE
	case ESTALE:          result = "ESTALE\0Stale file handle"; break;
#endif /* ESTALE */
#ifdef ENOSHARE
	case ENOSHARE:        result = "ENOSHARE\0No such host or network path"; break;
#endif /* ENOSHARE */
#ifdef ECASECLASH
	case ECASECLASH:      result = "ECASECLASH\0Filename exists with different case"; break;
#endif /* ECASECLASH */
#ifdef ENOTBLK
	case ENOTBLK:         result = "ENOTBLK\0Block device required"; break;
#endif /* ENOTBLK */
#ifdef ECHRNG
	case ECHRNG:          result = "ECHRNG\0Channel number out of range"; break;
#endif /* ECHRNG */
#ifdef EL2NSYNC
	case EL2NSYNC:        result = "EL2NSYNC\0Level 2 not synchronized"; break;
#endif /* EL2NSYNC */
#ifdef EL3HLT
	case EL3HLT:          result = "EL3HLT\0Level 3 halted"; break;
#endif /* EL3HLT */
#ifdef EL3RST
	case EL3RST:          result = "EL3RST\0Level 3 reset"; break;
#endif /* EL3RST */
#ifdef ELNRNG
	case ELNRNG:          result = "ELNRNG\0Link number out of range"; break;
#endif /* ELNRNG */
#ifdef EUNATCH
	case EUNATCH:         result = "EUNATCH\0Protocol driver not attached"; break;
#endif /* EUNATCH */
#ifdef ENOCSI
	case ENOCSI:          result = "ENOCSI\0No CSI structure available"; break;
#endif /* ENOCSI */
#ifdef EL2HLT
	case EL2HLT:          result = "EL2HLT\0Level 2 halted"; break;
#endif /* EL2HLT */
#ifdef EBADE
	case EBADE:           result = "EBADE\0Invalid exchange"; break;
#endif /* EBADE */
#ifdef EBADR
	case EBADR:           result = "EBADR\0Invalid request descriptor"; break;
#endif /* EBADR */
#ifdef EXFULL
	case EXFULL:          result = "EXFULL\0Exchange full"; break;
#endif /* EXFULL */
#ifdef ENOANO
	case ENOANO:          result = "ENOANO\0No anode"; break;
#endif /* ENOANO */
#ifdef EBADRQC
	case EBADRQC:         result = "EBADRQC\0Invalid request code"; break;
#endif /* EBADRQC */
#ifdef EBADSLT
	case EBADSLT:         result = "EBADSLT\0Invalid slot"; break;
#endif /* EBADSLT */
#ifdef EBFONT
	case EBFONT:          result = "EBFONT\0Bad font file fmt"; break;
#endif /* EBFONT */
#ifdef ENONET
	case ENONET:          result = "ENONET\0Machine is not on the network"; break;
#endif /* ENONET */
#ifdef ENOPKG
	case ENOPKG:          result = "ENOPKG\0Package not installed"; break;
#endif /* ENOPKG */
#ifdef EREMOTE
	case EREMOTE:         result = "EREMOTE\0The object is remote"; break;
#endif /* EREMOTE */
#ifdef EADV
	case EADV:            result = "EADV\0Advertise error"; break;
#endif /* EADV */
#ifdef ESRMNT
	case ESRMNT:          result = "ESRMNT\0Srmount error"; break;
#endif /* ESRMNT */
#ifdef ECOMM
	case ECOMM:           result = "ECOMM\0Communication error on send"; break;
#endif /* ECOMM */
#ifdef ELBIN
	case ELBIN:           result = "ELBIN\0Inode is remote (not really error)"; break;
#endif /* ELBIN */
#ifdef EDOTDOT
	case EDOTDOT:         result = "EDOTDOT\0Cross mount point (not really error)"; break;
#endif /* EDOTDOT */
#ifdef ENOTUNIQ
	case ENOTUNIQ:        result = "ENOTUNIQ\0Given log. name not unique"; break;
#endif /* ENOTUNIQ */
#ifdef EBADFD
	case EBADFD:          result = "EBADFD\0f.d. invalid for this operation"; break;
#endif /* EBADFD */
#ifdef EREMCHG
	case EREMCHG:         result = "EREMCHG\0Remote address changed"; break;
#endif /* EREMCHG */
#ifdef ELIBACC
	case ELIBACC:         result = "ELIBACC\0Can't access a needed shared lib"; break;
#endif /* ELIBACC */
#ifdef ELIBBAD
	case ELIBBAD:         result = "ELIBBAD\0Accessing a corrupted shared lib"; break;
#endif /* ELIBBAD */
#ifdef ELIBSCN
	case ELIBSCN:         result = "ELIBSCN\0.lib section in a.out corrupted"; break;
#endif /* ELIBSCN */
#ifdef ELIBMAX
	case ELIBMAX:         result = "ELIBMAX\0Attempting to link in too many libs"; break;
#endif /* ELIBMAX */
#ifdef ELIBEXEC
	case ELIBEXEC:        result = "ELIBEXEC\0Attempting to exec a shared library"; break;
#endif /* ELIBEXEC */
#ifdef ESHUTDOWN
	case ESHUTDOWN:       result = "ESHUTDOWN\0Can't send after socket shutdown"; break;
#endif /* ESHUTDOWN */
#ifdef ESOCKTNOSUPPORT
	case ESOCKTNOSUPPORT: result = "ESOCKTNOSUPPORT\0Socket type not supported"; break;
#endif /* ESOCKTNOSUPPORT */
#ifdef EPROCLIM
	case EPROCLIM:        result = "EPROCLIM\0Process limit reached"; break;
#endif /* EPROCLIM */
#ifdef EUSERS
	case EUSERS:          result = "EUSERS\0Too many users"; break;
#endif /* EUSERS */
#ifdef ENOMEDIUM
	case ENOMEDIUM:       result = "ENOMEDIUM\0No medium (in tape drive)"; break;
#endif /* ENOMEDIUM */
#ifdef ESTRPIPE
	case ESTRPIPE:        result = "ESTRPIPE\0Streams pipe error"; break;
#endif /* ESTRPIPE */
#ifdef EMULTIHOP
	case EMULTIHOP:       result = "EMULTIHOP\0Multihop attempted"; break;
#endif /* EMULTIHOP */
#ifdef ERESTART
	case ERESTART:        result = "ERESTART\0Interrupted system call should be restarted"; break;
#endif /* ERESTART */
#ifdef EUCLEAN
	case EUCLEAN:         result = "EUCLEAN\0Structure needs cleaning"; break;
#endif /* EUCLEAN */
#ifdef ENOTNAM
	case ENOTNAM:         result = "ENOTNAM\0Not a XENIX named type file"; break;
#endif /* ENOTNAM */
#ifdef ENAVAIL
	case ENAVAIL:         result = "ENAVAIL\0No XENIX semaphores available"; break;
#endif /* ENAVAIL */
#ifdef EISNAM
	case EISNAM:          result = "EISNAM\0Is a named type file"; break;
#endif /* EISNAM */
#ifdef EREMOTEIO
	case EREMOTEIO:       result = "EREMOTEIO\0Remote I/O error"; break;
#endif /* EREMOTEIO */
#ifdef EMEDIUMTYPE
	case EMEDIUMTYPE:     result = "EMEDIUMTYPE\0Wrong medium type"; break;
#endif /* EMEDIUMTYPE */
#ifdef ENOKEY
	case ENOKEY:          result = "ENOKEY\0Required key not available"; break;
#endif /* ENOKEY */
#ifdef EKEYEXPIRED
	case EKEYEXPIRED:     result = "EKEYEXPIRED\0Key has expired"; break;
#endif /* EKEYEXPIRED */
#ifdef EKEYREVOKED
	case EKEYREVOKED:     result = "EKEYREVOKED\0Key has been revoked"; break;
#endif /* EKEYREVOKED */
#ifdef EKEYREJECTED
	case EKEYREJECTED:    result = "EKEYREJECTED\0Key was rejected by service"; break;
#endif /* EKEYREJECTED */
#ifdef ERFKILL
	case ERFKILL:         result = "ERFKILL\0Operation not possible due to RF-kill"; break;
#endif /* ERFKILL */
#ifdef EHWPOISON
	case EHWPOISON:       result = "EHWPOISON\0Memory page has hardware error"; break;
#endif /* EHWPOISON */
#if defined(STRUNCATE) && (!defined(ERANGE) || STRUNCATE != ERANGE)
	case STRUNCATE:       result = "STRUNCATE\0Truncated"; break;
#endif /* STRUNCATE && (!ERANGE || STRUNCATE != ERANGE) */
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EWOULDBLOCK != EAGAIN)
	case EWOULDBLOCK:     result = "EWOULDBLOCK\0Operation would block"; break;
#endif /* EWOULDBLOCK && (!EAGAIN || EWOULDBLOCK != EAGAIN) */
#if defined(EDEADLK) && (!defined(EDEADLOCK) || EDEADLOCK != EDEADLK)
	case EDEADLK:         result = "EDEADLK\0Resource deadlock would occur"; break;
#endif /* EDEADLK && (!EDEADLOCK || EDEADLOCK != EDEADLK) */

	default:
		result = NULL;
		break;
	}
	return result;
#endif /* !HAVE_KOS_ERRNO_VALUES */
}
#ifndef __KERNEL__
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_sigabbrev_np)(signo_t signo) { return libc_sigabbrev_np(libd_signo_dos2kos(signo)); }
#endif /* !__KERNEL__ */
#include <asm/os/signal.h>
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given  `signo' isn't recognized,  `NULL' is returned  instead. */
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_sigabbrev_np)(signo_t signo) {
/*[[[deemon
import * from deemon;
@@Mapping for id -> (kosName, comment)
local kosSignoMappings: {int: (string, string)} = Dict();
local rtmin = none;
local rtmax = none;
with (local fp = File.open("../../../include/asm/os/kos/signal.h")) {
	for (local l: fp) {
		l = l.strip();
		local name, value, comment;
		try {
			name, value, comment = l.scanf(" # define __SIG%[^ ] %[^/ ] /" "*%[^]")...;
		} catch (...) {
			try {
				name, value = l.scanf(" # define __SIG%[^ ] %[^]")...;
			} catch (...) {
				continue;
			}
			comment = "";
		}
		if (name.startswith("_"))
			continue;
		value = value.strip();
		if (name == "RTMIN") {
			rtmin = int(value);
		} else if (name == "RTMAX") {
			rtmax = int(value);
		} else {
			comment = comment.partition("*" "/")[0].strip();
			while (comment.startswith("["))
				comment = comment.partition("]")[2].lstrip();
			comment = comment.rstrip(".").strip();
			if ("--" in comment) {
				comment = comment.partition("--")[0].strip();
			} else {
				while (comment.endswith(")"))
					comment = comment[:comment.rindex("(")].strip();
			}
			value = try int(value) catch (...) none;
			if (value is none)
				continue;
			if (value in kosSignoMappings)
				continue;
			kosSignoMappings[value] = (name, comment);
		}
	}
}
assert rtmin !is none;
assert rtmax !is none;
assert rtmin <= rtmax;

local sigmax = kosSignoMappings.keys > ...;
if (sigmax < rtmax)
	sigmax = rtmax;

print("#define HAVE_KOS_SIGNO_VALUES");
for (local ids: kosSignoMappings.keys.sorted().segments(4)) {
	print("@@pp_if ", " || ".join(for (local id: ids)
		"!defined(__SIG{0}) || __SIG{0} != {1}".format({ kosSignoMappings[id].first, id })),
		"@@");
	print("#undef HAVE_KOS_SIGNO_VALUES");
	print("@@pp_endif@@");
}
print("@@pp_if __SIGRTMIN != ", rtmin, " || __SIGRTMAX != ", rtmax, "@@");
print("#undef HAVE_KOS_SIGNO_VALUES");
print("@@pp_endif@@");

// Generate names+descriptors for real-time signals.
for (local id: [rtmin:rtmax]) {
	local desc = f"RTMIN+{id - rtmin}";
	kosSignoMappings[id] = (desc, desc.lower());
}
kosSignoMappings[rtmin] = ("RTMIN", "rtmin");
kosSignoMappings[rtmax] = ("RTMAX", "rtmax");


print("@@pp_ifdef HAVE_KOS_SIGNO_VALUES@@");
print("	static char const signo_strtab[] =");
local strtab_offsets: {int: int} = Dict();
local currentOffset = 0;
for (local i: [:sigmax + 1]) {
	local name, comment = kosSignoMappings.get(i)...;
	if (name is none)
		continue;
	name += "\0";
	if (i != sigmax)
		comment += "\0";
	print("\t", repr(name + comment));
	strtab_offsets[i] = currentOffset;
	currentOffset += #name;
	currentOffset += #comment;
}
print("	\"\";");
for (local i: [:sigmax + 1]) {
	if (kosSignoMappings.get(i) is none)
		strtab_offsets[i] = currentOffset;
}
local sizeofStrTab = currentOffset;
local usedOffsetType = "uint8_t";
if (sizeofStrTab > 0xffff)
	usedOffsetType = "uint32_t";
else if (sizeofStrTab > 0xff)
	usedOffsetType = "uint16_t";
print("	static ", usedOffsetType, " const signo_offsets[", (sigmax + 1), "] = {");
for (local i: [:sigmax + 1].segments(16))
	print("\t\t", ", ".join(for (local x: i) strtab_offsets[x]), ",");
print("	};");
]]]*/
#define HAVE_KOS_SIGNO_VALUES
#if !defined(__SIGHUP) || __SIGHUP != 1 || !defined(__SIGINT) || __SIGINT != 2 || !defined(__SIGQUIT) || __SIGQUIT != 3 || !defined(__SIGILL) || __SIGILL != 4
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGHUP || __SIGHUP != 1 || !__SIGINT || __SIGINT != 2 || !__SIGQUIT || __SIGQUIT != 3 || !__SIGILL || __SIGILL != 4 */
#if !defined(__SIGTRAP) || __SIGTRAP != 5 || !defined(__SIGABRT) || __SIGABRT != 6 || !defined(__SIGBUS) || __SIGBUS != 7 || !defined(__SIGFPE) || __SIGFPE != 8
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGTRAP || __SIGTRAP != 5 || !__SIGABRT || __SIGABRT != 6 || !__SIGBUS || __SIGBUS != 7 || !__SIGFPE || __SIGFPE != 8 */
#if !defined(__SIGKILL) || __SIGKILL != 9 || !defined(__SIGUSR1) || __SIGUSR1 != 10 || !defined(__SIGSEGV) || __SIGSEGV != 11 || !defined(__SIGUSR2) || __SIGUSR2 != 12
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGKILL || __SIGKILL != 9 || !__SIGUSR1 || __SIGUSR1 != 10 || !__SIGSEGV || __SIGSEGV != 11 || !__SIGUSR2 || __SIGUSR2 != 12 */
#if !defined(__SIGPIPE) || __SIGPIPE != 13 || !defined(__SIGALRM) || __SIGALRM != 14 || !defined(__SIGTERM) || __SIGTERM != 15 || !defined(__SIGSTKFLT) || __SIGSTKFLT != 16
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGPIPE || __SIGPIPE != 13 || !__SIGALRM || __SIGALRM != 14 || !__SIGTERM || __SIGTERM != 15 || !__SIGSTKFLT || __SIGSTKFLT != 16 */
#if !defined(__SIGCHLD) || __SIGCHLD != 17 || !defined(__SIGCONT) || __SIGCONT != 18 || !defined(__SIGSTOP) || __SIGSTOP != 19 || !defined(__SIGTSTP) || __SIGTSTP != 20
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGCHLD || __SIGCHLD != 17 || !__SIGCONT || __SIGCONT != 18 || !__SIGSTOP || __SIGSTOP != 19 || !__SIGTSTP || __SIGTSTP != 20 */
#if !defined(__SIGTTIN) || __SIGTTIN != 21 || !defined(__SIGTTOU) || __SIGTTOU != 22 || !defined(__SIGURG) || __SIGURG != 23 || !defined(__SIGXCPU) || __SIGXCPU != 24
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGTTIN || __SIGTTIN != 21 || !__SIGTTOU || __SIGTTOU != 22 || !__SIGURG || __SIGURG != 23 || !__SIGXCPU || __SIGXCPU != 24 */
#if !defined(__SIGXFSZ) || __SIGXFSZ != 25 || !defined(__SIGVTALRM) || __SIGVTALRM != 26 || !defined(__SIGPROF) || __SIGPROF != 27 || !defined(__SIGWINCH) || __SIGWINCH != 28
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGXFSZ || __SIGXFSZ != 25 || !__SIGVTALRM || __SIGVTALRM != 26 || !__SIGPROF || __SIGPROF != 27 || !__SIGWINCH || __SIGWINCH != 28 */
#if !defined(__SIGIO) || __SIGIO != 29 || !defined(__SIGPWR) || __SIGPWR != 30 || !defined(__SIGSYS) || __SIGSYS != 31
#undef HAVE_KOS_SIGNO_VALUES
#endif /* !__SIGIO || __SIGIO != 29 || !__SIGPWR || __SIGPWR != 30 || !__SIGSYS || __SIGSYS != 31 */
#if __SIGRTMIN != 32 || __SIGRTMAX != 64
#undef HAVE_KOS_SIGNO_VALUES
#endif /* __SIGRTMIN != 32 || __SIGRTMAX != 64 */
#ifdef HAVE_KOS_SIGNO_VALUES
	static char const signo_strtab[] =
	"HUP\0Hangup\0"
	"INT\0Interrupt\0"
	"QUIT\0Quit\0"
	"ILL\0Illegal instruction\0"
	"TRAP\0Trace/breakpoint trap\0"
	"ABRT\0Aborted\0"
	"BUS\0Bus error\0"
	"FPE\0Floating point exception\0"
	"KILL\0Killed\0"
	"USR1\0User defined signal 1\0"
	"SEGV\0Segmentation violation\0"
	"USR2\0User defined signal 2\0"
	"PIPE\0Broken pipe\0"
	"ALRM\0Alarm clock\0"
	"TERM\0Terminated\0"
	"STKFLT\0Stack fault\0"
	"CHLD\0Child exited\0"
	"CONT\0Continued\0"
	"STOP\0Stopped (signal)\0"
	"TSTP\0Stopped\0"
	"TTIN\0Stopped (tty input)\0"
	"TTOU\0Stopped (tty output)\0"
	"URG\0Urgent I/O condition\0"
	"XCPU\0CPU time limit exceeded\0"
	"XFSZ\0File size limit exceeded\0"
	"VTALRM\0Virtual timer expired\0"
	"PROF\0Profiling timer expired\0"
	"WINCH\0Window changed\0"
	"IO\0I/O possible\0"
	"PWR\0Power failure\0"
	"SYS\0Bad system call\0"
	"RTMIN\0rtmin\0"
	"RTMIN+1\0rtmin+1\0"
	"RTMIN+2\0rtmin+2\0"
	"RTMIN+3\0rtmin+3\0"
	"RTMIN+4\0rtmin+4\0"
	"RTMIN+5\0rtmin+5\0"
	"RTMIN+6\0rtmin+6\0"
	"RTMIN+7\0rtmin+7\0"
	"RTMIN+8\0rtmin+8\0"
	"RTMIN+9\0rtmin+9\0"
	"RTMIN+10\0rtmin+10\0"
	"RTMIN+11\0rtmin+11\0"
	"RTMIN+12\0rtmin+12\0"
	"RTMIN+13\0rtmin+13\0"
	"RTMIN+14\0rtmin+14\0"
	"RTMIN+15\0rtmin+15\0"
	"RTMIN+16\0rtmin+16\0"
	"RTMIN+17\0rtmin+17\0"
	"RTMIN+18\0rtmin+18\0"
	"RTMIN+19\0rtmin+19\0"
	"RTMIN+20\0rtmin+20\0"
	"RTMIN+21\0rtmin+21\0"
	"RTMIN+22\0rtmin+22\0"
	"RTMIN+23\0rtmin+23\0"
	"RTMIN+24\0rtmin+24\0"
	"RTMIN+25\0rtmin+25\0"
	"RTMIN+26\0rtmin+26\0"
	"RTMIN+27\0rtmin+27\0"
	"RTMIN+28\0rtmin+28\0"
	"RTMIN+29\0rtmin+29\0"
	"RTMIN+30\0rtmin+30\0"
	"RTMIN+31\0rtmin+31\0"
	"RTMAX\0rtmax"
	"";
	static uint16_t const signo_offsets[65] = {
		1204, 0, 11, 25, 35, 59, 86, 99, 113, 142, 154, 181, 209, 236, 253, 270,
		286, 305, 323, 338, 360, 373, 398, 424, 449, 478, 508, 537, 566, 587, 603, 621,
		641, 653, 669, 685, 701, 717, 733, 749, 765, 781, 797, 815, 833, 851, 869, 887,
		905, 923, 941, 959, 977, 995, 1013, 1031, 1049, 1067, 1085, 1103, 1121, 1139, 1157, 1175,
		1193,
	};
/*[[[end]]]*/
	char const *result;
	if ((unsigned int)signo >= COMPILER_LENOF(signo_offsets))
		return NULL;
	result = &signo_strtab[signo_offsets[signo]];
	if (!*result)
		result = NULL;
	return result;
#else /* HAVE_KOS_SIGNO_VALUES */
	char const *result;
	switch (signo) {

#ifdef SIGABRT_COMPAT
	case SIGABRT_COMPAT: result = "ABRT_COMPAT\0Aborted"; break;
#endif /* SIGABRT_COMPAT */
#ifdef SIGBREAK
	case SIGBREAK:       result = "BREAK\0Stopped (tty input)"; break;
#endif /* SIGBREAK */
#ifdef SIGHUP
	case SIGHUP:         result = "HUP\0Hangup"; break;
#endif /* SIGHUP */
#ifdef SIGINT
	case SIGINT:         result = "INT\0Interrupt"; break;
#endif /* SIGINT */
#ifdef SIGQUIT
	case SIGQUIT:        result = "QUIT\0Quit"; break;
#endif /* SIGQUIT */
#ifdef SIGILL
	case SIGILL:         result = "ILL\0Illegal instruction"; break;
#endif /* SIGILL */
#ifdef SIGTRAP
	case SIGTRAP:        result = "TRAP\0Trace/breakpoint trap"; break;
#endif /* SIGTRAP */
#ifdef SIGABRT
	case SIGABRT:        result = "ABRT\0Aborted"; break;
#endif /* SIGABRT */
#ifdef SIGBUS
	case SIGBUS:         result = "BUS\0Bus error"; break;
#endif /* SIGBUS */
#ifdef SIGFPE
	case SIGFPE:         result = "FPE\0Floating point exception"; break;
#endif /* SIGFPE */
#ifdef SIGKILL
	case SIGKILL:        result = "KILL\0Killed"; break;
#endif /* SIGKILL */
#ifdef SIGUSR1
	case SIGUSR1:        result = "USR1\0User defined signal 1"; break;
#endif /* SIGUSR1 */
#ifdef SIGSEGV
	case SIGSEGV:        result = "SEGV\0Segmentation violation"; break;
#endif /* SIGSEGV */
#ifdef SIGUSR2
	case SIGUSR2:        result = "USR2\0User defined signal 2"; break;
#endif /* SIGUSR2 */
#ifdef SIGPIPE
	case SIGPIPE:        result = "PIPE\0Broken pipe"; break;
#endif /* SIGPIPE */
#ifdef SIGALRM
	case SIGALRM:        result = "ALRM\0Alarm clock"; break;
#endif /* SIGALRM */
#ifdef SIGTERM
	case SIGTERM:        result = "TERM\0Terminated"; break;
#endif /* SIGTERM */
#ifdef SIGSTKFLT
	case SIGSTKFLT:      result = "STKFLT\0Stack fault"; break;
#endif /* SIGSTKFLT */
#ifdef SIGCHLD
	case SIGCHLD:        result = "CHLD\0Child exited"; break;
#endif /* SIGCHLD */
#ifdef SIGCONT
	case SIGCONT:        result = "CONT\0Continued"; break;
#endif /* SIGCONT */
#ifdef SIGSTOP
	case SIGSTOP:        result = "STOP\0Stopped (signal)"; break;
#endif /* SIGSTOP */
#ifdef SIGTSTP
	case SIGTSTP:        result = "TSTP\0Stopped"; break;
#endif /* SIGTSTP */
#ifdef SIGTTOU
	case SIGTTOU:        result = "TTOU\0Stopped (tty output)"; break;
#endif /* SIGTTOU */
#ifdef SIGURG
	case SIGURG:         result = "URG\0Urgent I/O condition"; break;
#endif /* SIGURG */
#ifdef SIGXCPU
	case SIGXCPU:        result = "XCPU\0CPU time limit exceeded"; break;
#endif /* SIGXCPU */
#ifdef SIGXFSZ
	case SIGXFSZ:        result = "XFSZ\0File size limit exceeded"; break;
#endif /* SIGXFSZ */
#ifdef SIGVTALRM
	case SIGVTALRM:      result = "VTALRM\0Virtual timer expired"; break;
#endif /* SIGVTALRM */
#ifdef SIGPROF
	case SIGPROF:        result = "PROF\0Profiling timer expired"; break;
#endif /* SIGPROF */
#ifdef SIGWINCH
	case SIGWINCH:       result = "WINCH\0Window changed"; break;
#endif /* SIGWINCH */
#ifdef SIGIO
	case SIGIO:          result = "IO\0I/O possible"; break;
#endif /* SIGIO */
#ifdef SIGSYS
	case SIGSYS:         result = "SYS\0Bad system call"; break;
#endif /* SIGSYS */
#ifdef SIGEMT
	case SIGEMT:         result = "EMT\0EMT instruction"; break;
#endif /* SIGEMT */
#ifdef SIGLOST
	case SIGLOST:        result = "LOST\0Resource lost"; break;
#endif /* SIGLOST */
#if defined(SIGTTIN) && (!defined(SIGBREAK) || SIGBREAK != SIGTTIN)
	case SIGTTIN:        result = "TTIN\0Stopped (tty input)"; break;
#endif /* SIGTTIN && (!SIGBREAK || SIGBREAK != SIGTTIN) */
#if defined(SIGCLD) && (!defined(SIGCHLD) || SIGCLD != SIGCHLD)
	case SIGCLD:         result = "CLD\0Child exited"; break;
#endif /* SIGCLD && (!SIGCHLD || SIGCLD != SIGCHLD) */
#if defined(SIGIOT) && (!defined(SIGABRT) || SIGIOT != SIGABRT)
	case SIGIOT:         result = "IOT\0IOT trap"; break;
#endif /* SIGIOT && (!SIGABRT || SIGIOT != SIGABRT) */
#if defined(SIGPOLL) && (!defined(SIGIO) || SIGPOLL != SIGIO)
	case SIGPOLL:        result = "POLL\0Pollable event occurred"; break;
#endif /* SIGPOLL && (!SIGIO || SIGPOLL != SIGIO) */
#if defined(SIGPWR) && (!defined(SIGLOST) || SIGPWR != SIGLOST)
	case SIGPWR:         result = "PWR\0Power failure"; break;
#endif /* SIGPWR && (!SIGLOST || SIGPWR != SIGLOST) */

	default:
		result = NULL;
		break;
	}
	return result;
#endif /* !HAVE_KOS_SIGNO_VALUES */
}
#ifndef __KERNEL__
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signo' isn't recognized, return `NULL' instead. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_sigdescr_np)(signo_t signo) { return libc_sigdescr_np(libd_signo_dos2kos(signo)); }
#endif /* !__KERNEL__ */
#ifndef __BUILDING_LIBC
#ifdef __CRT_HAVE__sys_siglist
#ifndef _sys_siglist
#ifdef __NSIG
__CSDECLARE2(,char const *const _sys_siglist[__NSIG],_sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const _sys_siglist[],_sys_siglist)
#endif /* !__NSIG */
#define _sys_siglist _sys_siglist
#endif /* !_sys_siglist */
#if !defined(_sys_nsig) && defined(__CRT_HAVE__sys_nsig)
__CSDECLARE(,int,_sys_nsig)
#define _sys_nsig _sys_nsig
#endif /* !_sys_nsig && __CRT_HAVE__sys_nsig */
#endif /* __CRT_HAVE__sys_siglist */
#endif /* !__BUILDING_LIBC */
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signo' isn't recognized, return `NULL' instead. */
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_sigdescr_np)(signo_t signo) {










	char const *result;
	result = libc_sigabbrev_np(signo);
	if (result)
		result = libc_strend(result) + 1;
	return result;





























































































































}
#ifndef __KERNEL__
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_strerror_r)(errno_t errnum,
                                      char *buf,
                                      size_t buflen) { return libc_strerror_r(libd_errno_dos2kos(errnum), buf, buflen); }
#include <hybrid/__assert.h>
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_strerror_r)(errno_t errnum,
                                      char *buf,
                                      size_t buflen) {
	char const *string;
	if (!buf)
		goto fallback;
	if (!buflen)
		goto fallback;
	string = libc_strerrordesc_np(errnum);
	if (string) {
		/* Copy the descriptor text. */
		size_t msg_len = libc_strlen(string) + 1;
		if (msg_len > buflen)
			goto fallback;
		libc_memcpyc(buf, string, msg_len, sizeof(char));
	} else {
		if ((size_t)libc_snprintf(buf, buflen, "Unknown error %d", errnum) >= buflen)
			goto fallback;
	}
	return buf;
fallback:
	return libc_strerror(errnum);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_COLD ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd___xpg_strerror_r)(errno_t errnum,
                                            char *buf,
                                            size_t buflen) { return libc___xpg_strerror_r(libd_errno_dos2kos(errnum), buf, buflen); }
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBCCALL libc___xpg_strerror_r)(errno_t errnum,
                                            char *buf,
                                            size_t buflen) {
	size_t msg_len;
	char const *string;
	string = libc_strerrordesc_np(errnum);
	if (!buf)
		buflen = 0;
	if (!string) {

		return EINVAL;



	}
	/* Copy the descriptor text. */
	msg_len = libc_strlen(string) + 1;
	if (msg_len > buflen) {

		return ERANGE;



	}
	libc_memcpyc(buf, string, msg_len, sizeof(char));
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strsep)(char **__restrict stringp,
                                  char const *__restrict delim) {
	char *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libc_strchr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}
/* Same as `memmove(dst, src, num_bytes)'
 * Note that bcopy is called with `dst' and `src' reversed */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_INS(1, 3) ATTR_OUTS(2, 3) void
NOTHROW_NCX(LIBCCALL libc_bcopy)(void const *src,
                                 void *dst,
                                 size_t num_bytes) {
	libc_memmove(dst, src, num_bytes);
}
#endif /* !__KERNEL__ */
/* Prevent bzero()'s call to memset() from being routed back to bzero itself! */
#ifndef LIBC_ARCH_HAVE_BZERO
#undef libc_memset
#endif /* !LIBC_ARCH_HAVE_BZERO */
#ifndef LIBC_ARCH_HAVE_BZEROW
#undef libc_memsetw
#endif /* !LIBC_ARCH_HAVE_BZEROW */
#ifndef LIBC_ARCH_HAVE_BZEROL
#undef libc_memsetl
#endif /* !LIBC_ARCH_HAVE_BZEROL */
#ifndef LIBC_ARCH_HAVE_BZEROQ
#undef libc_memsetq
#endif /* !LIBC_ARCH_HAVE_BZEROQ */
#ifndef LIBC_ARCH_HAVE_BZERO
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_OUTS(1, 2) void
NOTHROW_NCX(LIBCCALL libc_bzero)(void *__restrict dst,
                                 size_t num_bytes) {
	libc_memset(dst, 0, num_bytes);
}
#endif /* !LIBC_ARCH_HAVE_BZERO */
#ifndef LIBC_ARCH_HAVE_BZEROW
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_bzerow)(void *__restrict dst,
                                  size_t num_words) {
	libc_memsetw(dst, 0, num_words);
}
#endif /* !LIBC_ARCH_HAVE_BZEROW */
#ifndef LIBC_ARCH_HAVE_BZEROL
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_bzerol)(void *__restrict dst,
                                  size_t num_dwords) {
	libc_memsetl(dst, 0, num_dwords);
}
#endif /* !LIBC_ARCH_HAVE_BZEROL */
#ifndef LIBC_ARCH_HAVE_BCMPW
DEFINE_INTERN_ALIAS(libc_bcmpw, libc_memcmpw);
#endif /* !LIBC_ARCH_HAVE_BCMPW */
#ifndef LIBC_ARCH_HAVE_BCMPL
DEFINE_INTERN_ALIAS(libc_bcmpl, libc_memcmpl);
#endif /* !LIBC_ARCH_HAVE_BCMPL */
#ifndef LIBC_ARCH_HAVE_BZEROQ
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_bzeroq)(void *__restrict dst,
                                  size_t num_qwords) {
#if defined(__UINT64_TYPE__) && __SIZEOF_BUSINT__ >= 8
	libc_memsetq(dst, 0, num_qwords);
#else /* __UINT64_TYPE__ && __SIZEOF_BUSINT__ >= 8 */
	libc_bzerol(dst, num_qwords * 2);
#endif /* !__UINT64_TYPE__ || __SIZEOF_BUSINT__ < 8 */
}
#endif /* !LIBC_ARCH_HAVE_BZEROQ */
#ifndef LIBC_ARCH_HAVE_BCMPQ
DEFINE_INTERN_ALIAS(libc_bcmpq, libc_memcmpq);
#endif /* !LIBC_ARCH_HAVE_BCMPQ */
/* Restore optimized libc string functions */
#if !defined(LIBC_ARCH_HAVE_BZERO) && defined(__fast_memset_defined)
#define libc_memset(dst, byte, n_bytes) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))(dst, byte, n_bytes)
#endif /* !LIBC_ARCH_HAVE_BZERO && __fast_memset_defined */
#if !defined(LIBC_ARCH_HAVE_BZEROW) && defined(__fast_memsetw_defined)
#define libc_memsetw(dst, word, n_words) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))(dst, word, n_words)
#endif /* !LIBC_ARCH_HAVE_BZEROW && __fast_memsetw_defined */
#if !defined(LIBC_ARCH_HAVE_BZEROL) && defined(__fast_memsetl_defined)
#define libc_memsetl(dst, dword, n_dwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))(dst, dword, n_dwords)
#endif /* !LIBC_ARCH_HAVE_BZEROL && __fast_memsetl_defined */
#if !defined(LIBC_ARCH_HAVE_BZEROQ) && defined(__fast_memsetq_defined)
#define libc_memsetq(dst, qword, n_qwords) (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetq))(dst, qword, n_qwords)
#endif /* !LIBC_ARCH_HAVE_BZEROQ && __fast_memsetq_defined */
#include <hybrid/host.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_bzeroc)(void *__restrict dst,
                                  size_t elem_count,
                                  size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		libc_bzero(dst, elem_count);
		break;

	case 2:
		libc_bzerow(dst, elem_count);
		break;

	case 4:
		libc_bzerol(dst, elem_count);
		break;

#ifdef __UINT64_TYPE__
	case 8:
		libc_bzeroq(dst, elem_count);
		break;
#endif /* __UINT64_TYPE__ */

	default:
		libc_bzero(dst, elem_count * elem_size);
		break;
	}
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	libc_bzero(dst, elem_count * elem_size);
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
}
#ifndef LIBC_ARCH_HAVE_BCMPC
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_bcmpc)(void const *s1,
                                 void const *s2,
                                 size_t elem_count,
                                 size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_bcmp(s1, s2, elem_count);

	case 2:
		return libc_bcmpw(s1, s2, elem_count);

	case 4:
		return libc_bcmpl(s1, s2, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_bcmpq(s1, s2, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_bcmp(s1, s2, elem_count * elem_size);
}
#endif /* !LIBC_ARCH_HAVE_BCMPC */
#ifndef LIBC_ARCH_HAVE_BCMP
DEFINE_INTERN_ALIAS(libc_bcmp, libc_memcmp);
#endif /* !LIBC_ARCH_HAVE_BCMP */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strcasecmp)(char const *s1,
                                      char const *s2) {
	char c1, c2;
	do {
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char)libc_tolower((unsigned char)c1);
			c2 = (char)libc_tolower((unsigned char)c2);
			if (c1 != c2)
				return (int)((unsigned char)c1 - (unsigned char)c2);
		}
	} while (c1 != '\0');
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncasecmp)(char const *s1,
                                       char const *s2,
                                       size_t maxlen) {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char)libc_tolower((unsigned char)c1);
			c2 = (char)libc_tolower((unsigned char)c2);
			if (c1 != c2)
				return (int)((unsigned char)c1 - (unsigned char)c2);
		}
	} while (c1 != '\0');
	return 0;
}
#ifndef __KERNEL__
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == __SIZEOF_LONG__ && !defined(LIBC_ARCH_HAVE_FFSL)
DEFINE_INTERN_ALIAS(libc_ffs, libc_ffsl);
#elif __SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && !defined(LIBC_ARCH_HAVE_FFSLL)
DEFINE_INTERN_ALIAS(libc_ffs, libc_ffsll);
#elif !defined(LIBC_ARCH_HAVE_FFS)
#include <hybrid/__bit.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T
NOTHROW(LIBCCALL libc_ffs)(int i) {
	return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned int)i);
}
#endif /* ... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && !defined(LIBC_ARCH_HAVE_FFSLL)
DEFINE_INTERN_ALIAS(libc_ffsl, libc_ffsll);
#elif !defined(LIBC_ARCH_HAVE_FFSL)
#include <hybrid/__bit.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T
NOTHROW(LIBCCALL libc_ffsl)(long i) {
	return (__STDC_INT_AS_UINT_T)__hybrid_ffs((unsigned long)i);
}
#endif /* ... */
#ifndef LIBC_ARCH_HAVE_FFSLL
#include <hybrid/__bit.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_UINT_T
NOTHROW(LIBCCALL libc_ffsll)(__LONGLONG i) {
	return (__STDC_INT_AS_UINT_T)__hybrid_ffs((__ULONGLONG)i);
}
#endif /* !LIBC_ARCH_HAVE_FFSLL */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRLCAT
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUTS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strlcat)(char *__restrict dst,
                                   char const *__restrict src,
                                   size_t bufsize) {
	size_t result = libc_strlen(src);
	char *new_dst = dst + libc_strnlen(dst, bufsize);
	size_t copy_size;
	bufsize -= (new_dst - dst);
	copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(new_dst, src, copy_size*sizeof(char));
	new_dst[copy_size] = '\0';
	return result + (new_dst - dst);
}
#endif /* !LIBC_ARCH_HAVE_STRLCAT */
#ifndef LIBC_ARCH_HAVE_STRLCPY
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUTS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strlcpy)(char *__restrict dst,
                                   char const *__restrict src,
                                   size_t bufsize) {
	size_t result = libc_strlen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(dst, src, copy_size * sizeof(char));
	dst[copy_size] = '\0';
	return result;
}
#endif /* !LIBC_ARCH_HAVE_STRLCPY */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_MEMCCPY
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_INS(2, 4) ATTR_OUTS(1, 4) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memccpy)(void *__restrict dst,
                                   void const *__restrict src,
                                   int needle,
                                   size_t num_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t const *psrc = (byte_t const *)src;
	while (num_bytes--) {
		if ((*pdst++ = *psrc++) == (byte_t)needle)
			return pdst; /* Yes, this returns +1 past the needle. */
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCCPY */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMCPYW
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memcpyw)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_words) {
	u16 *pdst = (u16 *)dst;
	u16 const *psrc = (u16 const *)src;
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPYW */
#ifndef LIBC_ARCH_HAVE_MEMPCPYW
/* Same as `memcpyw', but return `dst + N_WORDS', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyw)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_words) {
	return (u16 *)libc_memcpyw(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPYW */
#ifndef LIBC_ARCH_HAVE_MEMCPYL
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memcpyl)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_dwords) {
	u32 *pdst = (u32 *)dst;
	u32 const *psrc = (u32 const *)src;
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPYL */
#ifndef LIBC_ARCH_HAVE_MEMPCPYL
/* Same as `memcpyl', but return `dst + N_DWORDS', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyl)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_dwords) {
	return (u32 *)libc_memcpyl(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPYL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEW
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memmovew)(void *dst,
                                    void const *src,
                                    size_t n_words) {
	u16 *pdst;
	u16 const *psrc;
	if (dst <= src) {
		pdst = (u16 *)dst;
		psrc = (u16 const *)src;
		while (n_words--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u16 *)dst + n_words;
		psrc = (u16 const *)src + n_words;
		while (n_words--)
			*--pdst = *--psrc;
	}
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEW
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempmovew)(void *dst,
                                     void const *src,
                                     size_t n_words) {
	return (u16 *)libc_memmovew(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEL
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memmovel)(void *dst,
                                    void const *src,
                                    size_t n_dwords) {
	u32 *pdst;
	u32 const *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 const *)src;
		while (n_dwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u32 *)dst + n_dwords;
		psrc = (u32 const *)src + n_dwords;
		while (n_dwords--)
			*--pdst = *--psrc;
	}
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEL
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempmovel)(void *dst,
                                     void const *src,
                                     size_t n_dwords) {
	return (u32 *)libc_memmovel(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPW
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memmoveupw)(void *dst,
                                      void const *src,
                                      size_t n_words) {
	u16 *pdst;
	u16 const *psrc;
	pdst = (u16 *)dst + n_words;
	psrc = (u16 const *)src + n_words;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst >= psrc || !n_words, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_words);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst >= psrc || !n_words, "%p < %p (count:%zu)", dst, src, n_words);
#endif /* !__PRIP_PREFIX */
	while (n_words--)
		*--pdst = *--psrc;
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNW
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memmovedownw)(void *dst,
                                        void const *src,
                                        size_t n_words) {
	u16 *pdst;
	u16 const *psrc;
	pdst = (u16 *)dst;
	psrc = (u16 const *)src;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst <= psrc || !n_words, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_words);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst <= psrc || !n_words, "%p > %p (count:%zu)", dst, src, n_words);
#endif /* !__PRIP_PREFIX */
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPW
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst >= src || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveupw)(void *dst,
                                       void const *src,
                                       size_t n_words) {
	return (u16 *)libc_memmoveupw(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNW
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' (assumes that `dst <= src || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempmovedownw)(void *dst,
                                         void const *src,
                                         size_t n_words) {
	return (u16 *)libc_memmovedownw(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPL
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memmoveupl)(void *dst,
                                      void const *src,
                                      size_t n_dwords) {
	u32 *pdst;
	u32 const  *psrc;
	pdst = (u32 *)dst + n_dwords;
	psrc = (u32 const *)src + n_dwords;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst >= psrc || !n_dwords, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_dwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst >= psrc || !n_dwords, "%p < %p (count:%zu)", dst, src, n_dwords);
#endif /* !__PRIP_PREFIX */
	while (n_dwords--)
		*--pdst = *--psrc;
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNL
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memmovedownl)(void *dst,
                                        void const *src,
                                        size_t n_dwords) {
	u32 *pdst;
	u32 const *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 const *)src;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst <= psrc || !n_dwords, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_dwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst <= psrc || !n_dwords, "%p > %p (count:%zu)", dst, src, n_dwords);
#endif /* !__PRIP_PREFIX */
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPL
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst >= src || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveupl)(void *dst,
                                       void const *src,
                                       size_t n_dwords) {
	return (u32 *)libc_memmoveupl(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNL
/* Same as `memmovew', but return `dst + N_DWORDS', rather than `dst' (assumes that `dst <= src || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempmovedownl)(void *dst,
                                         void const *src,
                                         size_t n_dwords) {
	return (u32 *)libc_memmovedownl(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMSETW
/* Fill memory with a given word */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memsetw)(void *__restrict dst,
                                   uint16_t word,
                                   size_t n_words) {
	u16 *pdst = (u16 *)dst;
	while (n_words--)
		*pdst++ = word;
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMSETW */
#ifndef LIBC_ARCH_HAVE_MEMPSETW
/* Same as `memsetw', but return `dst + N_WORDS', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempsetw)(void *__restrict dst,
                                    uint16_t word,
                                    size_t n_words) {
	return (u16 *)libc_memsetw(dst, word, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPSETW */
#ifndef LIBC_ARCH_HAVE_MEMSETL
/* Fill memory with a given dword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memsetl)(void *__restrict dst,
                                   uint32_t dword,
                                   size_t n_dwords) {
	u32 *pdst = (u32 *)dst;
	while (n_dwords--)
		*pdst++ = dword;
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMSETL */
#ifndef LIBC_ARCH_HAVE_MEMPSETL
/* Same as `memsetl', but return `dst + N_DWORDS', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempsetl)(void *__restrict dst,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return (u32 *)libc_memsetl(dst, dword, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPSETL */
#ifndef LIBC_ARCH_HAVE_MEMCMPW
/* Compare memory buffers and return the difference of the first non-matching word */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_memcmpw)(void const *s1,
                                   void const *s2,
                                   size_t n_words) {
	u16 const *p1 = (u16 const *)s1;
	u16 const *p2 = (u16 const *)s2;
	while (n_words--) {
		u16 v1, v2;
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
}
#endif /* !LIBC_ARCH_HAVE_MEMCMPW */
#ifndef LIBC_ARCH_HAVE_MEMCMPL
/* Compare memory buffers and return the difference of the first non-matching dword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_memcmpl)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
	u32 const *p1 = (u32 const *)s1;
	u32 const *p2 = (u32 const *)s2;
	while (n_dwords--) {
		u32 v1, v2;
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
}
#endif /* !LIBC_ARCH_HAVE_MEMCMPL */
#ifndef LIBC_ARCH_HAVE_MEMCHRW
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memchrw)(void const *__restrict haystack,
                                   uint16_t needle,
                                   size_t n_words) {
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter == needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCHRW */
#ifndef LIBC_ARCH_HAVE_MEMCHRL
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memchrl)(void const *__restrict haystack,
                                   uint32_t needle,
                                   size_t n_dwords) {
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter == needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCHRL */
#ifndef LIBC_ARCH_HAVE_MEMRCHRW
/* Descendingly search for `needle', starting at `haystack + N_WORDS * 2'. - Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrchrw)(void const *__restrict haystack,
                                    uint16_t needle,
                                    size_t n_words) {
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter == needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRCHRW */
#ifndef LIBC_ARCH_HAVE_MEMRCHRL
/* Descendingly search for `needle', starting at `haystack + N_DWORDS * 4'. - Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrchrl)(void const *__restrict haystack,
                                    uint32_t needle,
                                    size_t n_dwords) {
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter == needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRW
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrw)(void const *__restrict haystack,
                                      uint16_t needle) {
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRL
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrl)(void const *__restrict haystack,
                                      uint32_t needle) {
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRW
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)haystack - 2' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrw)(void const *__restrict haystack,
                                       uint16_t needle) {
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter == needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRL
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)haystack - 4' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrl)(void const *__restrict haystack,
                                       uint32_t needle) {
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter == needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRL */
#ifndef LIBC_ARCH_HAVE_MEMENDW
/* Same as `memchrw', but return `haystack + N_WORDS * 2', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memendw)(void const *__restrict haystack,
                                   uint16_t needle,
                                   size_t n_bytes) {
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMENDW */
#ifndef LIBC_ARCH_HAVE_MEMENDL
/* Same as `memchrl', but return `haystack + N_DWORDS * 4', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memendl)(void const *__restrict haystack,
                                   uint32_t needle,
                                   size_t n_dwords) {
	u32 *result = (u32 *)haystack;
	for (; n_dwords--; ++result) {
		if unlikely(*result == needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMENDL */
#ifndef LIBC_ARCH_HAVE_MEMRENDW
/* Same as `memrchrw', but return `haystack - 2', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrendw)(void const *__restrict haystack,
                                    uint16_t needle,
                                    size_t n_words) {
	u16 *result = (u16 *)haystack + n_words;
	for (;;) {
		--result;
		if unlikely(!n_words)
			break;
		if unlikely(*result == needle)
			break;
		--n_words;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRENDW */
#ifndef LIBC_ARCH_HAVE_MEMRENDL
/* Same as `memrchrl', but return `haystack - 4', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrendl)(void const *__restrict haystack,
                                    uint32_t needle,
                                    size_t n_dwords) {
	u32 *result = (u32 *)haystack + n_dwords;
	for (;;) {
		--result;
		if unlikely(!n_dwords)
			break;
		if unlikely(*result == needle)
			break;
		--n_dwords;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRENDL */
#ifndef LIBC_ARCH_HAVE_MEMLENW
/* Same as `memendw', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 2'    if    the    given    `needle'    wasn't    found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memlenw)(void const *__restrict haystack,
                                   uint16_t needle,
                                   size_t n_words) {
	return (size_t)(libc_memendw(haystack, needle, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLENW */
#ifndef LIBC_ARCH_HAVE_MEMLENL
/* Same as `memendl', but return the offset from `haystack', rather than the actual address.
 * Returns    `haystack + N_DWORDS * 4'    if    the    given    `needle'    wasn't    found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memlenl)(void const *__restrict haystack,
                                   uint32_t needle,
                                   size_t n_dwords) {
	return (size_t)(libc_memendl(haystack, needle, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLENL */
#ifndef LIBC_ARCH_HAVE_MEMRLENW
/* Same as `memrendw', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `needle' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memrlenw)(void const *__restrict haystack,
                                    uint16_t needle,
                                    size_t n_words) {
	return (size_t)(libc_memrendw(haystack, needle, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLENW */
#ifndef LIBC_ARCH_HAVE_MEMRLENL
/* Same as `memrendl', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `needle' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memrlenl)(void const *__restrict haystack,
                                    uint32_t needle,
                                    size_t n_dwords) {
	return (size_t)(libc_memrendl(haystack, needle, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENW
/* Same as `rawmemchrw', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenw)(void const *__restrict haystack,
                                      uint16_t needle) {
	return (size_t)(libc_rawmemchrw(haystack, needle) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENL
/* Same as `rawmemchrl', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenl)(void const *__restrict haystack,
                                      uint32_t needle) {
	return (size_t)(libc_rawmemchrl(haystack, needle) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENW
/* Same as `rawmemrchrw', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenw)(void const *__restrict haystack,
                                       uint16_t needle) {
	return (size_t)(libc_rawmemrchrw(haystack, needle) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENL
/* Same as `rawmemrchrl', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenl)(void const *__restrict haystack,
                                       uint32_t needle) {
	return (size_t)(libc_rawmemrchrl(haystack, needle) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENL */
#ifndef LIBC_ARCH_HAVE_MEMCPYQ
#include <hybrid/typecore.h>
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memcpyq)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_qwords) {
#if __SIZEOF_BUSINT__ >= 8
	u64 *pdst = (u64 *)dst;
	u64 const *psrc = (u64 const *)src;
	while (n_qwords--)
		*pdst++ = *psrc++;
#else /* __SIZEOF_BUSINT__ >= 8 */
	u32 *pdst = (u32 *)dst;
	u32 const *psrc = (u32 const *)src;
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
#endif /* __SIZEOF_BUSINT__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMPCPYQ
/* Same as `memcpyq', but return `dst + n_qwords', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyq)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_qwords) {
	return (u64 *)libc_memcpyq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEQ
#include <hybrid/typecore.h>
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memmoveq)(void *dst,
                                    void const *src,
                                    size_t n_qwords) {
#if __SIZEOF_BUSINT__ >= 8
	u64 *pdst;
	u64 const *psrc;
	if (dst <= src) {
		pdst = (u64 *)dst;
		psrc = (u64 const *)src;
		while (n_qwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u64 *)dst + n_qwords;
		psrc = (u64 const *)src + n_qwords;
		while (n_qwords--)
			*--pdst = *--psrc;
	}
#else /* __SIZEOF_BUSINT__ >= 8 */
	u32 *pdst;
	u32 const *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 const *)src;
		while (n_qwords--) {
			*pdst++ = *psrc++;
			*pdst++ = *psrc++;
		}
	} else {
		pdst = (u32 *)dst + (n_qwords * 2);
		psrc = (u32 const *)src + (n_qwords * 2);
		while (n_qwords--) {
			*--pdst = *--psrc;
			*--pdst = *--psrc;
		}
	}
#endif /* __SIZEOF_BUSINT__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEQ
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveq)(void *__restrict dst,
                                     void const *__restrict src,
                                     size_t n_qwords) {
	return (u64 *)libc_memmoveq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPQ
#include <hybrid/typecore.h>
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst >= src || !n_qwords') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memmoveupq)(void *dst,
                                      void const *src,
                                      size_t n_qwords) {
#if __SIZEOF_BUSINT__ >= 8
	u64 *pdst;
	u64 const *psrc;
	pdst = (u64 *)dst + n_qwords;
	psrc = (u64 const *)src + n_qwords;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst >= psrc || !n_qwords, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst >= psrc || !n_qwords, "%p < %p (count:%zu)", dst, src, n_qwords);
#endif /* !__PRIP_PREFIX */
	while (n_qwords--)
		*--pdst = *--psrc;
#else /* __SIZEOF_BUSINT__ >= 8 */
	u32 *pdst;
	u32 const *psrc;
	pdst = (u32 *)dst + (n_qwords * 2);
	psrc = (u32 const *)src + (n_qwords * 2);
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst >= psrc || !n_qwords, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst >= psrc || !n_qwords, "%p < %p (count:%zu)", dst, src, n_qwords);
#endif /* !__PRIP_PREFIX */
	while (n_qwords--) {
		*--pdst = *--psrc;
		*--pdst = *--psrc;
	}
#endif /* __SIZEOF_BUSINT__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNQ
#include <hybrid/typecore.h>
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `dst <= src || !n_qwords') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memmovedownq)(void *dst,
                                        void const *src,
                                        size_t n_qwords) {
#if __SIZEOF_BUSINT__ >= 8
	u64 *pdst;
	u64 const *psrc;
	pdst = (u64 *)dst;
	psrc = (u64 const *)src;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst <= psrc || !n_qwords, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst <= psrc || !n_qwords, "%p > %p (count:%zu)", dst, src, n_qwords);
#endif /* !__PRIP_PREFIX */
	while (n_qwords--)
		*pdst++ = *psrc++;
#else /* __SIZEOF_BUSINT__ >= 8 */
	u32 *pdst;
	u32 const *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 const *)src;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst <= psrc || !n_qwords, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_qwords);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst <= psrc || !n_qwords, "%p > %p (count:%zu)", dst, src, n_qwords);
#endif /* !__PRIP_PREFIX */
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
#endif /* __SIZEOF_BUSINT__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPQ
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst >= src || !n_qwords') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveupq)(void *__restrict dst,
                                       void const *__restrict src,
                                       size_t n_qwords) {
	return (u64 *)libc_memmoveupq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNQ
/* Same as `memmovew', but return `dst + n_qwords', rather than `dst' (assumes that `dst <= src || !n_qwords') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempmovedownq)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_qwords) {
	return (u64 *)libc_memmovedownq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMSETQ
/* Fill memory with a given qword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memsetq)(void *__restrict dst,
                                   uint64_t qword,
                                   size_t n_qwords) {
	u64 *pdst = (u64 *)dst;
	while (n_qwords--)
		*pdst++ = qword;
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMSETQ */
#ifndef LIBC_ARCH_HAVE_MEMPSETQ
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_OUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempsetq)(void *__restrict dst,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return (u64 *)libc_memsetq(dst, qword, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPSETQ */
#ifndef LIBC_ARCH_HAVE_MEMCMPQ
/* Compare memory buffers and return the difference of the first non-matching qword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_memcmpq)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
	u64 const *p1 = (u64 const *)s1;
	u64 const *p2 = (u64 const *)s2;
	while (n_dwords--) {
		u64 v1, v2;
		if ((v1 = *p1++) != (v2 = *p2++)) {
			return v1 < v2 ? -1 : 1;
		}
	}
	return 0;
}
#endif /* !LIBC_ARCH_HAVE_MEMCMPQ */
#ifndef LIBC_ARCH_HAVE_MEMCHRQ
/* Ascendingly search for `needle', starting at `haystack'. - Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memchrq)(void const *__restrict haystack,
                                   uint64_t needle,
                                   size_t n_qwords) {
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter == needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMRCHRQ
/* Descendingly search for `needle', starting at `haystack+n_qwords'. - Return `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrchrq)(void const *__restrict haystack,
                                    uint64_t needle,
                                    size_t n_qwords) {
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter == needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRQ
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrq)(void const *__restrict haystack,
                                      uint64_t needle) {
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRQ
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)haystack - 8' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrq)(void const *__restrict haystack,
                                       uint64_t needle) {
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter == needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMENDQ
/* Same as `memchrq', but return `haystack+n_qwords', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memendq)(void const *__restrict haystack,
                                   uint64_t needle,
                                   size_t n_bytes) {
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMENDQ */
#ifndef LIBC_ARCH_HAVE_MEMRENDQ
/* Same as `memrchrq', but return `haystack - 8', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrendq)(void const *__restrict haystack,
                                    uint64_t needle,
                                    size_t n_qwords) {
	u64 *result = (u64 *)haystack + n_qwords;
	for (;;) {
		--result;
		if unlikely(!n_qwords)
			break;
		if unlikely(*result == needle)
			break;
		--n_qwords;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRENDQ */
#ifndef LIBC_ARCH_HAVE_MEMLENQ
/* Same as `memendq', but return the offset from `haystack', rather than the actual address.
 * Returns `n_qwords' if the given `needle' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memlenq)(void const *__restrict haystack,
                                   uint64_t needle,
                                   size_t n_qwords) {
	return (size_t)(libc_memendq(haystack, needle, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLENQ */
#ifndef LIBC_ARCH_HAVE_MEMRLENQ
/* Same as `memrendq', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `needle' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memrlenq)(void const *__restrict haystack,
                                    uint64_t needle,
                                    size_t n_qwords) {
	return (size_t)(libc_memrendq(haystack, needle, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENQ
/* Same as `rawmemchrq', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenq)(void const *__restrict haystack,
                                      uint64_t needle) {
	return (size_t)(libc_rawmemchrq(haystack, needle) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENQ
/* Same as `rawmemrchrq', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenq)(void const *__restrict haystack,
                                       uint64_t needle) {
	return (size_t)(libc_rawmemrchrq(haystack, needle) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENQ */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_MEMXCHR
/* Same as `memchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memxchr)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	byte_t *hay_iter = (byte_t *)haystack;
	for (; n_bytes--; ++hay_iter) {
		if unlikely(*hay_iter != (byte_t)needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMXCHR */
#ifndef LIBC_ARCH_HAVE_MEMRXCHR
/* Same as `memrchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memrxchr)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	byte_t *iter = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--iter != (byte_t)needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXCHR */
#ifndef LIBC_ARCH_HAVE_RAWMEMXCHR
#include <hybrid/typecore.h>
/* Same as `rawmemchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) void *
NOTHROW_NCX(LIBCCALL libc_rawmemxchr)(void const *__restrict haystack,
                                      int needle) {
	byte_t *iter = (byte_t *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != (byte_t)needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXCHR */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXCHR
#include <hybrid/typecore.h>
/* Same as `rawmemrchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchr)(void const *__restrict haystack,
                                       int needle) {
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter != (byte_t)needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXCHR */
#ifndef LIBC_ARCH_HAVE_MEMXEND
/* Same as `memend', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memxend)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != (byte_t)needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMXEND */
#ifndef LIBC_ARCH_HAVE_MEMRXEND
/* Same as `memrend', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memrxend)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	byte_t *result = (byte_t *)haystack + n_bytes;
	for (;;) {
		--result;
		if unlikely(!n_bytes)
			break;
		if unlikely(*result != (byte_t)needle)
			break;
		--n_bytes;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXEND */
#ifndef LIBC_ARCH_HAVE_MEMXLEN
/* Same as `memlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memxlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return (size_t)((byte_t *)libc_memxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLEN */
#ifndef LIBC_ARCH_HAVE_MEMRXLEN
/* Same as `memrlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlen)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	return (size_t)((byte_t *)libc_memrxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLEN
/* Same as `rawmemlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlen)(void const *__restrict haystack,
                                      int needle) {
	return (size_t)((byte_t *)libc_rawmemxchr(haystack, needle) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXLEN
/* Same as `rawmemrlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlen)(void const *__restrict haystack,
                                       int needle) {
	return (size_t)((byte_t *)libc_rawmemrxchr(haystack, needle) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXLEN */
#ifndef LIBC_ARCH_HAVE_MEMXCHRW
/* Same as `memchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memxchrw)(void const *__restrict haystack,
                                    uint16_t needle,
                                    size_t n_words) {
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter != needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMXCHRW */
#ifndef LIBC_ARCH_HAVE_MEMXCHRL
/* Same as `memchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memxchrl)(void const *__restrict haystack,
                                    uint32_t needle,
                                    size_t n_dwords) {
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter != needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMXCHRL */
#ifndef LIBC_ARCH_HAVE_MEMRXCHRW
/* Same as `memrchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrw)(void const *__restrict haystack,
                                     uint16_t needle,
                                     size_t n_words) {
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter != needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXCHRW */
#ifndef LIBC_ARCH_HAVE_MEMRXCHRL
/* Same as `memrchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrl)(void const *__restrict haystack,
                                     uint32_t needle,
                                     size_t n_dwords) {
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter != needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMXCHRW
/* Same as `rawmemchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrw)(void const *__restrict haystack,
                                       uint16_t needle) {
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMXCHRL
/* Same as `rawmemchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrl)(void const *__restrict haystack,
                                       uint32_t needle) {
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXCHRW
/* Same as `rawmemrchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrw)(void const *__restrict haystack,
                                        uint16_t needle) {
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter != needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXCHRL
/* Same as `rawmemrchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrl)(void const *__restrict haystack,
                                        uint32_t needle) {
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter != needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXCHRL */
#ifndef LIBC_ARCH_HAVE_MEMXENDW
/* Same as `memendw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memxendw)(void const *__restrict haystack,
                                    uint16_t needle,
                                    size_t n_words) {
	u16 *result = (u16 *)haystack;
	for (; n_words--; ++result) {
		if unlikely(*result != needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMXENDW */
#ifndef LIBC_ARCH_HAVE_MEMXENDL
/* Same as `memendl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memxendl)(void const *__restrict haystack,
                                    uint32_t needle,
                                    size_t n_dwords) {
	u32 *result = (u32 *)haystack;
	for (; n_dwords--; ++result) {
		if unlikely(*result != needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMXENDL */
#ifndef LIBC_ARCH_HAVE_MEMRXENDW
/* Same as `memrendw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrxendw)(void const *__restrict haystack,
                                     uint16_t needle,
                                     size_t n_words) {
	u16 *result = (u16 *)haystack + n_words;
	for (;;) {
		--result;
		if unlikely(!n_words)
			break;
		if unlikely(*result != needle)
			break;
		--n_words;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXENDW */
#ifndef LIBC_ARCH_HAVE_MEMRXENDL
/* Same as `memrendl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrxendl)(void const *__restrict haystack,
                                     uint32_t needle,
                                     size_t n_dwords) {
	u32 *result = (u32 *)haystack + n_dwords;
	for (;;) {
		--result;
		if unlikely(!n_dwords)
			break;
		if unlikely(*result != needle)
			break;
		--n_dwords;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXENDL */
#ifndef LIBC_ARCH_HAVE_MEMXLENW
/* Same as `memlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memxlenw)(void const *__restrict haystack,
                                    uint16_t needle,
                                    size_t n_words) {
	return (size_t)(libc_memxendw(haystack, needle, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLENW */
#ifndef LIBC_ARCH_HAVE_MEMXLENL
/* Same as `memlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memxlenl)(void const *__restrict haystack,
                                    uint32_t needle,
                                    size_t n_dwords) {
	return (size_t)(libc_memxendl(haystack, needle, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLENL */
#ifndef LIBC_ARCH_HAVE_MEMRXLENW
/* Same as `memrlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenw)(void const *__restrict haystack,
                                     uint16_t needle,
                                     size_t n_words) {
	return (size_t)(libc_memrxendw(haystack, needle, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLENW */
#ifndef LIBC_ARCH_HAVE_MEMRXLENL
/* Same as `memrlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenl)(void const *__restrict haystack,
                                     uint32_t needle,
                                     size_t n_dwords) {
	return (size_t)(libc_memrxendl(haystack, needle, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLENW
/* Same as `rawmemlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenw)(void const *__restrict haystack,
                                       uint16_t needle) {
	return (size_t)(libc_rawmemxchrw(haystack, needle) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLENL
/* Same as `rawmemlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenl)(void const *__restrict haystack,
                                       uint32_t needle) {
	return (size_t)(libc_rawmemxchrl(haystack, needle) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXLENW
/* Same as `rawmemrlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenw)(void const *__restrict haystack,
                                        uint16_t needle) {
	return (size_t)(libc_rawmemrxchrw(haystack, needle) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXLENL
/* Same as `rawmemrlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenl)(void const *__restrict haystack,
                                        uint32_t needle) {
	return (size_t)(libc_rawmemrxchrl(haystack, needle) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXLENL */
#ifndef LIBC_ARCH_HAVE_MEMXCHRQ
/* Same as `memchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memxchrq)(void const *__restrict haystack,
                                    uint64_t needle,
                                    size_t n_qwords) {
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter != needle)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMXCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMRXCHRQ
/* Same as `memrchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrq)(void const *__restrict haystack,
                                     uint64_t needle,
                                     size_t n_qwords) {
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter != needle)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMXCHRQ
/* Same as `rawmemchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrq)(void const *__restrict haystack,
                                       uint64_t needle) {
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXCHRQ
/* Same as `rawmemrchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrq)(void const *__restrict haystack,
                                        uint64_t needle) {
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter != needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMXENDQ
/* Same as `memendq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memxendq)(void const *__restrict haystack,
                                    uint64_t needle,
                                    size_t n_bytes) {
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMXENDQ */
#ifndef LIBC_ARCH_HAVE_MEMRXENDQ
/* Same as `memrendq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrxendq)(void const *__restrict haystack,
                                     uint64_t needle,
                                     size_t n_qwords) {
	u64 *result = (u64 *)haystack + n_qwords;
	for (;;) {
		--result;
		if unlikely(!n_qwords)
			break;
		if unlikely(*result != needle)
			break;
		--n_qwords;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXENDQ */
#ifndef LIBC_ARCH_HAVE_MEMXLENQ
/* Same as `memlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memxlenq)(void const *__restrict haystack,
                                    uint64_t needle,
                                    size_t n_qwords) {
	return (size_t)(libc_memxendq(haystack, needle, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLENQ */
#ifndef LIBC_ARCH_HAVE_MEMRXLENQ
/* Same as `memrlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenq)(void const *__restrict haystack,
                                     uint64_t needle,
                                     size_t n_qwords) {
	return (size_t)(libc_memrxendq(haystack, needle, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLENQ
/* Same as `rawmemlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenq)(void const *__restrict haystack,
                                       uint64_t needle) {
	return (size_t)(libc_rawmemxchrq(haystack, needle) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXLENQ
/* Same as `rawmemrlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenq)(void const *__restrict haystack,
                                        uint64_t needle) {
	return (size_t)(libc_rawmemrxchrq(haystack, needle) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXLENQ */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUP
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* >> memmoveup(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst >= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memmoveup)(void *dst,
                                     void const *src,
                                     size_t n_bytes) {
	byte_t *pdst;
	byte_t const *psrc;
	pdst = (byte_t *)dst + n_bytes;
	psrc = (byte_t const *)src + n_bytes;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst >= psrc || !n_bytes, "%p < %p (count:%" __PRIP_PREFIX "u)", dst, src, n_bytes);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst >= psrc || !n_bytes, "%p < %p (count:%zu)", dst, src, n_bytes);
#endif /* !__PRIP_PREFIX */
	while (n_bytes--)
		*--pdst = *--psrc;
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWN
#include <hybrid/__assert.h>
#include <bits/crt/inttypes.h>
/* >> memmovedown(3)
 * Move memory between potentially overlapping memory blocks (assumes that `dst <= src || !n_bytes')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memmovedown)(void *dst,
                                       void const *src,
                                       size_t n_bytes) {
	byte_t *pdst;
	byte_t const *psrc;
	pdst = (byte_t *)dst;
	psrc = (byte_t const *)src;
#ifdef __PRIP_PREFIX
	__hybrid_assertf(pdst <= psrc || !n_bytes, "%p > %p (count:%" __PRIP_PREFIX "u)", dst, src, n_bytes);
#else /* __PRIP_PREFIX */
	__hybrid_assertf(pdst <= psrc || !n_bytes, "%p > %p (count:%zu)", dst, src, n_bytes);
#endif /* !__PRIP_PREFIX */
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWN */
#ifndef LIBC_ARCH_HAVE_MEMCMPC
#include <hybrid/byteorder.h>
/* >> memcmpc(3)
 * Compare up to `elem_count' `elem_size'-bytes-large unsigned integers
 * from  the 2 given  buffers. If all are  identical, return `0'. Else:
 *  - return `< 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] < (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]'
 *  - return `> 0' if `(UNSIGNED NBYTES(elem_size))s1[FIRST_MISSMATCH] > (UNSIGNED NBYTES(elem_size))s2[FIRST_MISSMATCH]' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_memcmpc)(void const *s1,
                                   void const *s2,
                                   size_t elem_count,
                                   size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_memcmp(s1, s2, elem_count);

	case 2:
		return libc_memcmpw(s1, s2, elem_count);

	case 4:
		return libc_memcmpl(s1, s2, elem_count);

	case 8:
		return libc_memcmpq(s1, s2, elem_count);

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return libc_memcmp(s1, s2, elem_count * elem_size);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	/* Complicated case: we must compare elem_size-large unsigned integers,
	 * but because host endian is LITTLE, we can't just compare bytes  from
	 * lowest address -> highest address (because the most significant byte
	 * comes last in a LITTLE-ENDIAN data-word) */
	while (elem_count--) {
		size_t i;
		byte_t const *s1_iter, *s2_iter;
		s1      = (byte_t const *)s1 + elem_size;
		s2      = (byte_t const *)s2 + elem_size;
		s1_iter = (byte_t const *)s1;
		s2_iter = (byte_t const *)s2;
		i = elem_size;
		while (i--) {
			byte_t v1, v2;
			v1 = *--s1_iter;
			v2 = *--s2_iter;
			if (v1 != v2) {
#if __SIZEOF_INT__ >= 2
				return (int)(unsigned int)v1 -
				       (int)(unsigned int)v2;
#else /* __SIZEOF_INT__ >= 2 */
				return v1 < v2 ? -1 : 1;
#endif /* __SIZEOF_INT__ < 2 */
			}
		}
	}
	return 0;
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
}
#endif /* !LIBC_ARCH_HAVE_MEMCMPC */
#ifndef __KERNEL__
/* >> memcpyc(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_memcpyc)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t elem_count,
                                   size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_memcpy(dst, src, elem_count);

	case 2:
		return libc_memcpyw(dst, src, elem_count);

	case 4:
		return libc_memcpyl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_memcpyq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_memcpy(dst, src, elem_count * elem_size);
}
/* >> mempcpyc(3)
 * Same as `memcpyc', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_mempcpyc)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t elem_count,
                                    size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_mempcpy(dst, src, elem_count);

	case 2:
		return libc_mempcpyw(dst, src, elem_count);

	case 4:
		return libc_mempcpyl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_mempcpyq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_mempcpy(dst, src, elem_count * elem_size);
}
/* >> memmovec(3)
 * Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_memmovec)(void *dst,
                                    void const *src,
                                    size_t elem_count,
                                    size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_memmove(dst, src, elem_count);

	case 2:
		return libc_memmovew(dst, src, elem_count);

	case 4:
		return libc_memmovel(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_memmoveq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_memmove(dst, src, elem_count * elem_size);
}
/* >> mempmovec(3)
 * Same as `memmovec', but return `dst + (ELEM_COUNT * ELEM_SIZE)', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_mempmovec)(void *dst,
                                     void const *src,
                                     size_t elem_count,
                                     size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_mempmove(dst, src, elem_count);

	case 2:
		return libc_mempmovew(dst, src, elem_count);

	case 4:
		return libc_mempmovel(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_mempmoveq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_mempmove(dst, src, elem_count * elem_size);
}
/* >> memmoveupc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_memmoveupc)(void *dst,
                                      void const *src,
                                      size_t elem_count,
                                      size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_memmoveup(dst, src, elem_count);

	case 2:
		return libc_memmoveupw(dst, src, elem_count);

	case 4:
		return libc_memmoveupl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_memmoveupq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_memmoveup(dst, src, elem_count * elem_size);
}
/* >> mempmoveupc(3)
 * Same   as   `memmoveupc',  but   return  `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst >= src || !ELEM_COUNT || !ELEM_SIZE') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_mempmoveupc)(void *dst,
                                       void const *src,
                                       size_t elem_count,
                                       size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_mempmoveup(dst, src, elem_count);

	case 2:
		return libc_mempmoveupw(dst, src, elem_count);

	case 4:
		return libc_mempmoveupl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_mempmoveupq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_mempmoveup(dst, src, elem_count * elem_size);
}
/* >> memmovedownc(3)
 * Move memory between potentially overlapping memory
 * blocks (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_memmovedownc)(void *dst,
                                        void const *src,
                                        size_t elem_count,
                                        size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_memmovedown(dst, src, elem_count);

	case 2:
		return libc_memmovedownw(dst, src, elem_count);

	case 4:
		return libc_memmovedownl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_memmovedownq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_memmovedown(dst, src, elem_count * elem_size);
}
/* >> mempmovedownc(3)
 * Same  as  `memmovedownc',  but  return   `dst + (ELEM_COUNT * ELEM_SIZE)',
 * rather than `dst' (assumes that `dst <= src || !ELEM_COUNT || !ELEM_SIZE') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUT(1) void *
NOTHROW_NCX(LIBCCALL libc_mempmovedownc)(void *dst,
                                         void const *src,
                                         size_t elem_count,
                                         size_t elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (elem_size) {

	case 1:
		return libc_mempmovedown(dst, src, elem_count);

	case 2:
		return libc_mempmovedownw(dst, src, elem_count);

	case 4:
		return libc_mempmovedownl(dst, src, elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return libc_mempmovedownq(dst, src, elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return libc_mempmovedown(dst, src, elem_count * elem_size);
}
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STREND
/* >> strend(3)
 * Same as `str + strlen(str)' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strend)(char const *__restrict str) {
	while (*str)
		++str;
	return (char *)str;
}
#endif /* !LIBC_ARCH_HAVE_STREND */
#ifndef LIBC_ARCH_HAVE_STRNEND
/* >> strnend(3)
 * Same as `str + strnlen(str, max_chars)' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnend)(char const *__restrict str,
                                   size_t maxlen) {
	for (; maxlen && *str; ++str, --maxlen)
		;
	return (char *)str;
}
#endif /* !LIBC_ARCH_HAVE_STRNEND */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STRNCHR
/* >> strnchr(3)
 * Same as `strchr', but don't exceed `max_chars' characters. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnchr)(char const *__restrict haystack,
                                   int needle,
                                   size_t maxlen) {
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			return (char *)haystack;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_STRNCHR */
#ifndef LIBC_ARCH_HAVE_STRNRCHR
/* >> strnrchr(3)
 * Same as `strrchr', but don't exceed `max_chars' characters. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnrchr)(char const *__restrict haystack,
                                    int needle,
                                    size_t maxlen) {
	char const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}
#endif /* !LIBC_ARCH_HAVE_STRNRCHR */
#ifndef LIBC_ARCH_HAVE_STRRCHRNUL
/* >> strrchrnul(3)
 * Same as `strrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strrchrnul)(char const *__restrict haystack,
                                      int needle) {
	char const *result = haystack - 1;
	do {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	} while (*haystack++);
	return (char *)result;
}
#endif /* !LIBC_ARCH_HAVE_STRRCHRNUL */
#ifndef LIBC_ARCH_HAVE_STRNCHRNUL
/* >> strnchrnul(3)
 * Same as `strnchr', but return `strnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnchrnul)(char const *__restrict haystack,
                                      int needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (unsigned char)*haystack != (unsigned char)needle; ++haystack)
		;
	return (char *)haystack;
}
#endif /* !LIBC_ARCH_HAVE_STRNCHRNUL */
#ifndef LIBC_ARCH_HAVE_STRNRCHRNUL
/* >> strnrchrnul(3)
 * Same as `strnrchr', but return `str - 1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnrchrnul)(char const *__restrict haystack,
                                       int needle,
                                       size_t maxlen) {
	char const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((unsigned char)*haystack == (unsigned char)needle)
			result = haystack;
	}
	return (char *)result;
}
#endif /* !LIBC_ARCH_HAVE_STRNRCHRNUL */
#ifndef LIBC_ARCH_HAVE_STROFF
/* >> stroff(3)
 * Same as `strchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_stroff)(char const *__restrict haystack,
                                  int needle) {
	return (size_t)(libc_strchrnul(haystack, needle) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STROFF */
#ifndef LIBC_ARCH_HAVE_STRROFF
/* >> strroff(3)
 * Same as `strrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_strroff)(char const *__restrict haystack,
                                   int needle) {
	return (size_t)(libc_strrchrnul(haystack, needle) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRROFF */
#ifndef LIBC_ARCH_HAVE_STRNOFF
/* >> strnoff(3)
 * Same as `strnchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strnoff)(char const *__restrict haystack,
                                   int needle,
                                   size_t maxlen) {
	return (size_t)(libc_strnchrnul(haystack, needle, maxlen) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRNOFF */
#ifndef LIBC_ARCH_HAVE_STRNROFF
/* >> strnroff(3)
 * Same as `strnrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strnroff)(char const *__restrict haystack,
                                    int needle,
                                    size_t maxlen) {
	return (size_t)(libc_strnrchrnul(haystack, needle, maxlen) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRNROFF */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMPSET
/* >> mempset(3)
 * Same as `memset', but return `dst + n_bytes', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_mempset)(void *__restrict dst,
                                   int byte,
                                   size_t n_bytes) {
	return (void *)((byte_t *)libc_memset(dst, byte, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPSET */
#ifndef LIBC_ARCH_HAVE_MEMPMOVE
/* >> mempmove(3)
 * Same as `memmove', but return `dst + n_bytes', rather than `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempmove)(void *dst,
                                    void const *src,
                                    size_t n_bytes) {
	return (void *)((byte_t *)libc_memmove(dst, src, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVE */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUP
/* >> mempmoveup(3)
 * Same as `memmoveup', but return `dst + n_bytes', rather than `dst' (assumes that `dst >= src || !n_bytes') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempmoveup)(void *dst,
                                      void const *src,
                                      size_t n_bytes) {
	return (void *)((byte_t *)libc_memmoveup(dst, src, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWN
/* >> mempmovedown(3)
 * Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempmovedown)(void *dst,
                                        void const *src,
                                        size_t n_bytes) {
	return (void *)((byte_t *)libc_memmovedown(dst, src, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHR
#include <hybrid/typecore.h>
/* >> rawmemrchr(3)
 * Same as `memrchr' without a search limit, starting at `haystack - 1' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_rawmemrchr)(void const *__restrict haystack,
                                      int needle) {
	byte_t *iter = (byte_t *)haystack;
	for (;;) {
		if unlikely(*--iter == (byte_t)needle)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHR */
#ifndef LIBC_ARCH_HAVE_MEMEND
/* >> memend(3)
 * Same as `memchr', but return `haystack + n_bytes', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memend)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
	byte_t *result = (byte_t *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == (byte_t)needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMEND */
#ifndef LIBC_ARCH_HAVE_MEMREND
/* >> memrend(3)
 * Same as `memrchr', but return `haystack - 1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memrend)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	byte_t *result = (byte_t *)haystack + n_bytes;
	for (;;) {
		--result;
		if unlikely(!n_bytes)
			break;
		if unlikely(*result == (byte_t)needle)
			break;
		--n_bytes;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMREND */
#ifndef LIBC_ARCH_HAVE_MEMLEN
/* >> memlen(3)
 * Same as `memend', but return the offset from `haystack', rather than the actual address.
 * Returns `n_bytes' if the given `needle' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memlen)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
	return (size_t)((byte_t *)libc_memend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLEN */
#ifndef LIBC_ARCH_HAVE_MEMRLEN
/* >> memrlen(3)
 * Same as `memrend', but return the offset from `haystack', rather than the actual address.
 * Returns `(size_t)-1' if the given `needle' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return (size_t)((byte_t *)libc_memrend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMLEN
/* >> rawmemlen(3)
 * Same as `rawmemchr', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlen)(void const *__restrict haystack,
                                     int needle) {
	return (size_t)((byte_t *)libc_rawmemchr(haystack, needle) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLEN
/* >> rawmemrlen(3)
 * Same as `rawmemrchr', but return the offset from `haystack', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlen)(void const *__restrict haystack,
                                      int needle) {
	return (size_t)((byte_t *)libc_rawmemrchr(haystack, needle) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLEN */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_MEMRMEM
#include <features.h>
/* >> memrmem(3)
 * Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memrmem)(void const *haystack,
                                   size_t haystacklen,
                                   void const *needle,
                                   size_t needlelen) {
	byte_t *candidate, marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= needlelen - 1;
	marker = *(uint8_t const *)needle;
	while ((candidate = (byte_t *)libc_memrchr(haystack, marker, haystacklen)) != NULL) {
		if (libc_memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		haystacklen = (size_t)(candidate - (byte_t *)haystack);
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRMEM */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMPATW
#include <hybrid/__wordbits.h>
/* >> mempatw(3)
 * Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_mempatw)(void *__restrict dst,
                                   uint16_t pattern,
                                   size_t n_bytes) {
	byte_t *iter = (byte_t *)dst;
	if (n_bytes && (uintptr_t)iter & 1) {
		*iter = __INT16_BYTE(pattern, 1);
		++iter;
		--n_bytes;
	}
	iter = (byte_t *)libc_mempsetw(iter, pattern, n_bytes / 2);
	if (n_bytes & 1)
		*iter = __INT16_BYTE(pattern, 0);
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMPATW */
#ifndef LIBC_ARCH_HAVE_MEMPATL
#include <hybrid/__wordbits.h>
/* >> mempatl(3)
 * Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_mempatl)(void *__restrict dst,
                                   uint32_t pattern,
                                   size_t n_bytes) {
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 3; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	iter = (byte_t *)libc_mempsetl(iter, pattern, n_bytes / 4);
	for (n_bytes &= 3; n_bytes; ++iter, --n_bytes)
		*iter = __INT32_BYTE(pattern, (uintptr_t)iter & 3);
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMPATL */
#ifndef LIBC_ARCH_HAVE_MEMPATQ
#include <hybrid/__wordbits.h>
/* >> mempatq(3)
 * Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_OUTS(1, 3) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_mempatq)(void *__restrict dst,
                                   uint64_t pattern,
                                   size_t n_bytes) {
	byte_t *iter = (byte_t *)dst;
	for (; n_bytes && (uintptr_t)iter & 7; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	iter = (byte_t *)libc_mempsetq(iter, pattern, n_bytes / 8);
	for (n_bytes &= 7; n_bytes; ++iter, --n_bytes)
		*iter = __INT64_BYTE(pattern, (uintptr_t)iter & 7);
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMPATQ */
/* >> memcasecmp(3), memcasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_memcasecmp)(void const *s1,
                                      void const *s2,
                                      size_t n_bytes) {
	byte_t const *p1 = (byte_t const *)s1;
	byte_t const *p2 = (byte_t const *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes--) {
		v1 = *p1++;
		v2 = *p2++;
		if (v1 != v2) {
			v1 = (byte_t)libc_tolower(v1);
			v2 = (byte_t)libc_tolower(v2);
			if (v1 != v2)
				break;
		}
	}
	return (int)v1 - (int)v2;
}
#ifndef __KERNEL__
#include <features.h>
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memcasemem)(void const *haystack,
                                      size_t haystacklen,
                                      void const *needle,
                                      size_t needlelen) {
	byte_t *candidate, marker;
	byte_t *hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = (byte_t)libc_tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || (byte_t)libc_tolower(b) == marker)
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
/* >> memcasecmp(3), memcasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_memcasecmp_l)(void const *s1,
                                        void const *s2,
                                        size_t n_bytes,
                                        locale_t locale) {
	(void)locale;
	return libc_memcasecmp(s1, s2, n_bytes);
}
#include <features.h>
/* >> memcasemem(3), memcasemem_l(3)
 * Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comparisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memcasemem_l)(void const *haystack,
                                        size_t haystacklen,
                                        void const *needle,
                                        size_t needlelen,
                                        locale_t locale) {
	byte_t *candidate, marker;
	byte_t *hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if unlikely(!needlelen)
		return (byte_t *)haystack + haystacklen;
	if unlikely(needlelen > haystacklen)
		return NULL;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	haystacklen -= (needlelen - 1);
	marker       = (byte_t)libc_tolower_l(*(byte_t *)needle, locale);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || (byte_t)libc_tolower_l(b, locale) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (libc_memcasecmp_l(candidate, needle, needlelen, locale) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}
/* >> strcasestr(3), strcasestr_l(3)
 * Same as `strstr', but ignore casing */
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *
NOTHROW_NCX(LIBCCALL libc_strcasestr_l)(char const *haystack,
                                        char const *needle,
                                        locale_t locale) {
	for (; *haystack; ++haystack) {
		if (libc_strcasecmp_l(haystack, needle, locale) == 0)
			return (char *)haystack;
	}
	return NULL;
}
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) char *
NOTHROW_NCX(LIBCCALL libc_vstrdupf)(char const *__restrict format,
                                    va_list args) {
	char *result;
	return libc_vasprintf(&result, format, args) >= 0 ? result : 0;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) char *
NOTHROW_NCX(VLIBDCALL libd_strdupf)(char const *__restrict format,
                                    ...) {
	char *result;
	va_list args;
	va_start(args, format);
	result = libc_vstrdupf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> strdupf(3), vstrdupf(3)
 * Print the given `format' into a newly allocated, heap-allocated string */
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) char *
NOTHROW_NCX(VLIBCCALL libc_strdupf)(char const *__restrict format,
                                    ...) {
	char *result;
	va_list args;
	va_start(args, format);
	result = libc_vstrdupf(format, args);
	va_end(args);
	return result;
}
/* >> wildstrcmp(3) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_wildstrcmp)(char const *pattern,
                                      char const *string) {
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
			char card_post;
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
/* >> wildstrcasecmp(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp)(char const *pattern,
                                          char const *string) {
	char pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			char card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char)libc_tolower((unsigned char)card_post);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == (char)libc_tolower((unsigned char)ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildstrcasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch  = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		    (pattern_ch = (char)libc_tolower((unsigned char)pattern_ch),
		     string_ch  = (char)libc_tolower((unsigned char)string_ch),
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
/* >> fuzzy_strcmp(3) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcmp)(char const *s1,
                                        char const *s2) {
	return libc_fuzzy_memcmp(s1, libc_strlen(s1), s2, libc_strlen(s2));
}
/* >> fuzzy_strncmp(3) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncmp)(char const *s1,
                                         size_t s1_maxlen,
                                         char const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmp(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen));
}
/* >> fuzzy_strcasecmp(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp)(char const *s1,
                                            char const *s2) {
	return libc_fuzzy_memcasecmp(s1, libc_strlen(s1), s2, libc_strlen(s2));
}
/* >> fuzzy_strncasecmp(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp)(char const *s1,
                                             size_t s1_maxlen,
                                             char const *s2,
                                             size_t s2_maxlen) {
	return libc_fuzzy_memcasecmp(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen));
}
#include <parts/malloca.h>
/* >> fuzzy_memcmp(3) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmp)(void const *s1,
                                        size_t s1_bytes,
                                        void const *s2,
                                        size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			cost  = ((byte_t *)s1)[i] != ((byte_t *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc(v0, v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
#include <parts/malloca.h>
/* >> fuzzy_memcasecmp(3) */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp)(void const *s1,
                                            size_t s1_bytes,
                                            void const *s2,
                                            size_t s2_bytes) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (libc_tolower((unsigned char)c1) !=
			                     libc_tolower((unsigned char)c2));
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc(v0, v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp_l)(char const *s1,
                                              char const *s2,
                                              locale_t locale) {
	return libc_fuzzy_memcasecmp_l(s1, libc_strlen(s1), s2, libc_strlen(s2), locale);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp_l)(char const *s1,
                                               size_t s1_maxlen,
                                               char const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libc_fuzzy_memcasecmp_l(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen), locale);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp_l)(char const *pattern,
                                            char const *string,
                                            locale_t locale) {
	char pattern_ch, string_ch;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)*pattern;
		}
		if (!*pattern)
			return (int)*string; /* Pattern end doesn't match */
		if (*pattern == '*') {
			char card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char)libc_tolower_l(card_post, locale);
			for (;;) {
				char ch = *string++;
				if (card_post == ch || card_post == (char)libc_tolower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_strcasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(unsigned char)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		string_ch  = *string;
		if (pattern_ch == string_ch || pattern_ch == '?' ||
		    (pattern_ch = (char)libc_tolower_l((unsigned char)pattern_ch, locale),
		     string_ch  = (char)libc_tolower_l((unsigned char)string_ch, locale),
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
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcasecmp_l)(void const *s1,
                                              size_t s1_bytes,
                                              void const *s2,
                                              size_t s2_bytes,
                                              locale_t locale) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{
			void const *temp;
			temp = (void const *)s1;
			s1   = s2;
			*(void const **)&s2 = temp;
		}
		{
			size_t temp;
			temp     = s1_bytes;
			s1_bytes = s2_bytes;
			s2_bytes = temp;
		}
	}
	__malloca_tryhard(v0, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_bytes + 1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_bytes; ++i)
		v0[i] = i;
	for (i = 0; i < s1_bytes; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_bytes; j++) {
			byte_t c1 = ((byte_t *)s1)[i];
			byte_t c2 = ((byte_t *)s2)[j];
			cost  = c1 != c2 && (libc_tolower_l((unsigned char)c1, locale) !=
			                     libc_tolower_l((unsigned char)c2, locale));
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc(v0, v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpw)(void const *s1,
                                         size_t s1_words,
                                         void const *s2,
                                         size_t s2_words) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_words)
		return s2_words;
	if unlikely(!s2_words)
		return s1_words;
	if (s2_words > s1_words) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp     = s1_words;
			s1_words = s2_words;
			s2_words = temp;
		}
	}
	__malloca_tryhard(v0, (s2_words+1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_words+1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_words; ++i)
		v0[i] = i;
	for (i = 0; i < s1_words; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_words; j++) {
			cost  = ((u16 *)s1)[i] != ((u16 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc(v0, v1, s2_words, sizeof(size_t));
	}
	temp = v1[s2_words];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpl)(void const *s1,
                                         size_t s1_dwords,
                                         void const *s2,
                                         size_t s2_dwords) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_dwords)
		return s2_dwords;
	if unlikely(!s2_dwords)
		return s1_dwords;
	if (s2_dwords > s1_dwords) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp      = s1_dwords;
			s1_dwords = s2_dwords;
			s2_dwords = temp;
		}
	}
	__malloca_tryhard(v0, (s2_dwords+1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_dwords+1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_dwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_dwords; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_dwords; j++) {
			cost  = ((u32 *)s1)[i] != ((u32 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc(v0, v1, s2_dwords, sizeof(size_t));
	}
	temp = v1[s2_dwords];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(3) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_memcmpq)(void const *s1,
                                         size_t s1_qwords,
                                         void const *s2,
                                         size_t s2_qwords) {
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_qwords)
		return s2_qwords;
	if unlikely(!s2_qwords)
		return s1_qwords;
	if (s2_qwords > s1_qwords) {
		{
			void const *temp;
			temp = s1;
			s1   = s2;
			s2   = temp;
		}
		{
			size_t temp;
			temp      = s1_qwords;
			s1_qwords = s2_qwords;
			s2_qwords = temp;
		}
	}
	__malloca_tryhard(v0, (s2_qwords+1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v0)
		return (size_t)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(v1, (s2_qwords+1) * sizeof(size_t));
#ifdef __malloca_tryhard_mayfail
	if unlikely(!v1) {
		__freea(v0);
		return (size_t)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (i = 0; i < s2_qwords; ++i)
		v0[i] = i;
	for (i = 0; i < s1_qwords; ++i) {
		v1[0] = i + 1;
		for (j = 0; j < s2_qwords; j++) {
			cost  = ((u64 *)s1)[i] != ((u64 *)s2)[j];
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc(v0, v1, s2_qwords, sizeof(size_t));
	}
	temp = v1[s2_qwords];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncoll)(char const *s1,
                                    char const *s2,
                                    size_t maxlen) {
	/* XXX: Implement properly? */
	return libc_strncmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strcasecoll)(char const *s1,
                                       char const *s2) {
	/* XXX: Implement properly? */
	return libc_strcasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncasecoll)(char const *s1,
                                        char const *s2,
                                        size_t maxlen) {
	/* XXX: Implement properly? */
	return libc_strncasecmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnrev)(char *__restrict str,
                                   size_t maxlen) {
	return (char *)libc_memrev(str, libc_strnlen(str, maxlen));
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnlwr)(char *__restrict str,
                                   size_t maxlen) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_tolower((unsigned char)ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnupr)(char *__restrict str,
                                   size_t maxlen) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_toupper((unsigned char)ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memrev)(void *__restrict base,
                                  size_t n_bytes) {
	byte_t *iter, *end;
	end = (iter = (byte_t *)base) + n_bytes;
	while (iter < end) {
		byte_t temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return base;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncoll_l)(char const *s1,
                                      char const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_strncoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strcasecoll_l)(char const *s1,
                                         char const *s2,
                                         locale_t locale) {
	/* XXX: Implement properly? */
	return libc_strcasecmp_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncasecoll_l)(char const *s1,
                                          char const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_strncasecoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strlwr_l)(char *__restrict str,
                                    locale_t locale) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_tolower_l((unsigned char)ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strupr_l)(char *__restrict str,
                                    locale_t locale) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_toupper_l((unsigned char)ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnlwr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_tolower_l((unsigned char)ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnupr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_toupper_l((unsigned char)ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_INOUT(1) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrevw)(void *__restrict base,
                                   size_t n_words) {
	u16 *iter, *end;
	end = (iter = (u16 *)base) + n_words;
	while (iter < end) {
		u16 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u16 *)base;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_INOUT(1) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrevl)(void *__restrict base,
                                   size_t n_dwords) {
	u32 *iter, *end;
	end = (iter = (u32 *)base) + n_dwords;
	while (iter < end) {
		u32 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u32 *)base;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_INOUT(1) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrevq)(void *__restrict base,
                                   size_t n_qwords) {
	u64 *iter, *end;
	end = (iter = (u64 *)base) + n_qwords;
	while (iter < end) {
		u64 temp = *iter;
		*iter++ = *--end;
		*end = temp;
	}
	return (u64 *)base;
}
#endif /* !__KERNEL__ */
/* >> strcmpz(3)
 * Similar to `strcmp(3)', but the given `rhs' string mustn't necessarily be NUL-terminated.
 * Instead, that string's length is  fixed at `rhs_len', and  the compare is equivalent  to:
 * > char *dup = (char *)malloc((rhs_len + 1) * sizeof(char));
 * > *(char *)mempcpy(dup, rhs, rhs_len, sizeof(char)) = '\0';
 * > return strcmp(lhs, dup); */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strcmpz)(char const *lhs,
                                   char const *rhs,
                                   size_t rhs_len) {
	char c1, c2;
	do {
		c1 = *lhs++;
		if (!rhs_len--) {
			/* Once  RHS  reaches  the end  of  the string,
			 * compare the last character of LHS with `NUL' */
			return (int)((unsigned char)c1 - '\0');
		}
		c2 = *rhs++;
		if unlikely(c1 != c2)
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}
/* >> strstartcmp(3)
 * Compare the first `strnlen(str, strlen(startswith_str))' characters
 * of `str' with  `startswith_str', returning the  usual >0, <0,  ==0. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_strstartcmp)(char const *str,
                                       char const *startswith) {
	char c1, c2;
	do {
		c2 = *startswith++;
		if (!c2) {
			/* When the end of the RHS-string is reached, then we
			 * know  that  `str'  has `startswith'  as  a leading
			 * prefix. */
			return 0;
		}
		c1 = *str++;
		if unlikely(c1 != c2)
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);

	/* The given `str' has a  length less than `strlen(startswith)',  meaning
	 * that we're expected to return the result of a compare `NUL - NON_NUL',
	 * which  means  we must  return  -1. Note  that  the NON_NUL  is kind-of
	 * assumed here,  since  `startswith'  may contain  only  NUL  characters
	 * from  here on out,  however that is both  unlikely, wouldn't even make
	 * much sense. */
	return -1;
}
/* >> strstartcmpz(3)
 * Compare the first `strnlen(str, startswith_len)' characters of
 * `str' with  `startswith', returning  the  usual >0,  <0,  ==0. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strstartcmpz)(char const *str,
                                        char const *startswith,
                                        size_t startswith_len) {
	char c1, c2;
	do {
		if (!startswith_len--) {
			/* When the end of the RHS-string is reached, then we
			 * know  that  `str'  has `startswith'  as  a leading
			 * prefix. */
			return 0;
		}
		c1 = *str++;
		c2 = *startswith++;
		if unlikely(c1 != c2)
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);

	/* The  given  `str' has  a  length less  than  `startswith_len', meaning
	 * that we're expected to return the result of a compare `NUL - NON_NUL',
	 * which  means  we must  return  -1. Note  that  the NON_NUL  is kind-of
	 * assumed here,  since  `startswith'  may contain  only  NUL  characters
	 * from  here on out,  however that is both  unlikely, wouldn't even make
	 * much sense. */
	return -1;
}
#include <hybrid/typecore.h>
/* >> bitcpy(3)
 * Copy exactly `num_bits' from `src_base+(src_bit_offset/NBBY)' to `dst_base+(dst_bit_offset/NBBY)',
 * doing a byte-wise copy  but leaving bits not  meant to be copied  untouched. Inside of  individual
 * bytes, individual bits are  indexed such that the  least significant bit is  at `0', and the  most
 * significant bit is at `NBBY-1':
 * >> byte_t src[] = { 0b00001001 };
 * >> byte_t dst[] = { 0b00000000 };
 * >> bitcpy(dst, 4, src, 0, 4);
 * >> assert(dst == 0b10010000); */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_IN(3) ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_bitcpy)(void *__restrict dst_base,
                                  size_t dst_bit_offset,
                                  void const *__restrict src_base,
                                  size_t src_bit_offset,
                                  size_t num_bits) {
	while (num_bits) {
		byte_t remaining, src_value, remaining_temp;
		src_base = (byte_t const *)src_base + (src_bit_offset / __CHAR_BIT__);
		src_bit_offset %= __CHAR_BIT__;
		remaining = (byte_t)(__CHAR_BIT__ - src_bit_offset);
		if ((size_t)remaining > num_bits)
			remaining = (byte_t)num_bits;
		src_value      = *(byte_t const *)src_base >> src_bit_offset;
		remaining_temp = remaining;
		while (remaining_temp) {
			byte_t avail, dst_value;
			dst_base = (byte_t *)dst_base + (dst_bit_offset / __CHAR_BIT__);
			dst_bit_offset %= __CHAR_BIT__;
			avail = (byte_t)(__CHAR_BIT__ - dst_bit_offset);
			if (avail > remaining_temp)
				avail = remaining_temp;
			dst_value = *(byte_t *)dst_base;
			dst_value &= ~(((1 << avail) - 1) << dst_bit_offset);
			dst_value |= (src_value & ((1 << avail) - 1)) << dst_bit_offset;
			*(byte_t *)dst_base = dst_value;
			dst_bit_offset += avail;
			remaining_temp -= avail;
			src_value >>= avail;
		}
		src_bit_offset += remaining;
		num_bits -= remaining;
	}
}
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STRRSTR
/* >> strrstr(3)
 * Find the last instance of `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char *
NOTHROW_NCX(LIBCCALL libc_strrstr)(char const *haystack,
                                   char const *needle) {
	char *result = NULL;
	char ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			result = (char *)haystack - 1;
		}
miss:
		;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_STRRSTR */
#endif /* !__KERNEL__ */
#include <libc/unicode.h>
/* >> strlstrip(3)
 * Skip all leading `isspace(3)'-characters of `str' to return a pointer
 * to  the first  non-space character (or  the trailing NUL  if `str' is
 * empty or contains only spaces).
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Pointer to the first non-space character in `str' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strlstrip)(char const *str) {
	/* NOTE: assert(!isspace('\0'));
	 * -> So we don't need special handling to stop on NUL! */
#ifdef __CRT_HAVE___unicode_descriptor
	/* Unicode support */
	for (;;) {
		unsigned char ch = (unsigned char)*str;
		if (libc_isspace(ch)) {
			/* Fast-pass: ASCII space characters. */
			++str;
		} else if (ch >= 0x80) {
			char const *new_str = str;
			char32_t uni = __libc_unicode_readutf8(&new_str);
			if (!__libc_unicode_isspace(uni))
				break;
			str = new_str;
		} else {
			break;
		}
	}
#else /* __CRT_HAVE___unicode_descriptor */







	while (libc_isspace((unsigned char)*str))
		++str;
#endif /* !__CRT_HAVE___unicode_descriptor */
	return (char *)str;
}
/* >> strrstrip(3)
 * Find the last trailing `isspace(3)'-character (i.e. the one closest
 * to the start and not followed by a non-`isspace(3)'-character), and
 * replace it with '\0', effectively deleting trailing space.
 * NOTE: If available, use `unicode_isspace(3)' instead of `isspace(3)'
 * @return: * : Always re-returns `str' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strrstrip)(char *str) {
	char *endp = libc_strend(str);
#ifdef __CRT_HAVE___unicode_descriptor
	/* Unicode support */
	for (;;) {
		unsigned char ch = (unsigned char)endp[-1];
		if (libc_isspace(ch)) {
			/* Fast-pass: ASCII space characters. */
			--endp;
		} else if (ch >= 0x80) {
			char const *new_endp = endp;
			char32_t uni;
			uni = __libc_unicode_readutf8_rev_n(&new_endp, str);
			if (!__libc_unicode_isspace(uni))
				break;
			endp = (char *)new_endp;
		} else {
			break;
		}
	}
#else /* __CRT_HAVE___unicode_descriptor */







	while (endp > str && libc_isspace((unsigned char)endp[-1]))
		--endp;
#endif /* !__CRT_HAVE___unicode_descriptor */
	*endp = '\0'; /* Delete trailing space. */
	return str;
}
/* >> strstrip(3)
 * The combination of `strlstrip(3)' and `strrstrip(3)'
 * @return: * : Same as `strrstrip(strlstrip(str))' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_strstrip)(char *str) {
	str = libc_strlstrip(str);
	str = libc_strrstrip(str);
	return str;
}
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strlwr)(char *__restrict str) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_tolower((unsigned char)ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strupr)(char *__restrict str) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_toupper((unsigned char)ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strset)(char *__restrict str,
                                  int ch) {
	char *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 3) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnset)(char *__restrict str,
                                   int ch,
                                   size_t maxlen) {
	char *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_strrev)(char *__restrict str) {
	return (char *)libc_memrev(str, libc_strlen(str));
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc__strset_s)(char *dst,
                                     size_t dstsize,
                                     int ch) {
	char *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return 22;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 22;
	}
	__libc_memsetc(p, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc_memcpy_s)(void *dst,
                                    rsize_t dstlength,
                                    void const *src,
                                    rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return 22;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, __SIZEOF_CHAR__);
		if (!src)
			return 22;
		if (dstlength < srclength)
			return 34;
		return 22;
	}
	__libc_memcpyc(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc_memmove_s)(void *dst,
                                     rsize_t dstlength,
                                     void const *src,
                                     rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return 22;
	if (dstlength < srclength)
		return 34;
	__libc_memmovec(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc_strcpy_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
	char *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return 22;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_strcat_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
	if (!dst || !src)
		return 22;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return 22;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return 34;
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_strncat_s)(char *dst,
                                     rsize_t dstsize,
                                     const char *src,
                                     rsize_t maxlen) {
	char *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return 22;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 22;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return 34;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return 80;
		}
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBCCALL libc_strncpy_s)(char *dst,
                                     size_t dstsize,
                                     char const *src,
                                     size_t maxlen) {
	char *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return 22;
	if (!maxlen) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return 34;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return 80;
		}
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.errno") WUNUSED ATTR_IN_OPT(1) char *
NOTHROW_RPC(LIBCCALL libc__strerror)(char const *message) {
	static char strerror_buf[64];
	if (libc__strerror_s(strerror_buf,
	                COMPILER_LENOF(strerror_buf),
	                message))
		return NULL;
	return strerror_buf;
}
#include <bits/types.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_RPC(LIBCCALL libc__strerror_s)(char *__restrict buf,
                                       size_t buflen,
                                       char const *message) {
	char const *string;
	size_t reqlen;
	errno_t eno = __libc_geterrno();
	string = libc_strerrordesc_np(eno);
	if (string) {
		if (message) {
			reqlen = libc_snprintf(buf, buflen, "%s: %s\n", message, string);
		} else {
			reqlen = libc_snprintf(buf, buflen, "%s\n", string);
		}
	} else if (message) {
		reqlen = libc_snprintf(buf, buflen, "%s: Unknown error %d\n", message, eno);
	} else {
		reqlen = libc_snprintf(buf, buflen, "Unknown error %d\n", eno);
	}
	if (reqlen > buflen)
		return 34;
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__strlwr_s)(char *buf,
                                     size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_strnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_tolower((unsigned char)ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__strupr_s)(char *buf,
                                     size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_strnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_toupper((unsigned char)ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__strlwr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_strnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_tolower_l((unsigned char)ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__strupr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_strnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char)libc_toupper_l((unsigned char)ch, locale);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_INOUTS(1, 4) errno_t
NOTHROW_NCX(LIBCCALL libc__strnset_s)(char *__restrict buf,
                                      size_t buflen,
                                      int ch,
                                      size_t maxlen) {
	char *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return 22;
	if (maxlen >= buflen)
		return 34;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (wchar_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, __SIZEOF_CHAR__);
		return 22;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
/* >> strnstr(3)
 * Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If   found,   return  a   pointer   to  its   location   within  `str',   else   return  `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(2) ATTR_INS(1, 3) NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnstr)(char const *haystack,
                                   char const *needle,
                                   size_t haystack_maxlen) {
	char ch, needle_start = *needle++;
	while (haystack_maxlen-- && (ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char const *hay2, *ned_iter;
			size_t maxlen2;
			hay2     = haystack;
			ned_iter = needle;
			maxlen2  = haystack_maxlen;
			while ((ch = *ned_iter++) != '\0') {
				if (!maxlen2-- || *hay2++ != ch)
					goto miss;
			}
			return (char *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}
#endif /* !__KERNEL__ */
#include <sys/stat.h>
#ifndef __KERNEL__
#include <asm/os/stat.h>
/* Generate  a file mode representation similar to what's printed by `ls -l'
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
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
INTERN ATTR_SECTION(".text.crt.bsd.strstat") ATTR_OUT(2) void
NOTHROW_NCX(LIBCCALL libc_strmode)(mode_t mode,
                                   char p[12]) {
	char ch;

#ifndef S_IRUSR
#define S_IRUSR 0400 /* Read by owner. */
#endif /* !S_IRUSR */
#ifndef S_IWUSR
#define S_IWUSR 0200 /* Write by owner. */
#endif /* !S_IWUSR */
#ifndef S_IXUSR
#define S_IXUSR 0100 /* Execute by owner. */
#endif /* !S_IXUSR */
#ifndef S_IRWXU
#define S_IRWXU 0700
#endif /* !S_IRWXU */
#ifndef S_IRGRP
#define S_IRGRP 0040 /* Read by group. */
#endif /* !S_IRGRP */
#ifndef S_IWGRP
#define S_IWGRP 0020 /* Write by group. */
#endif /* !S_IWGRP */
#ifndef S_IXGRP
#define S_IXGRP 0010 /* Execute by group. */
#endif /* !S_IXGRP */
#ifndef S_IRWXG
#define S_IRWXG 0070
#endif /* !S_IRWXG */
#ifndef S_IROTH
#define S_IROTH 0004 /* Read by others. */
#endif /* !S_IROTH */
#ifndef S_IWOTH
#define S_IWOTH 0002 /* Write by others. */
#endif /* !S_IWOTH */
#ifndef S_IXOTH
#define S_IXOTH 0001 /* Execute by others. */
#endif /* !S_IXOTH */
#ifndef S_IRWXO
#define S_IRWXO 0007
#endif /* !S_IRWXO */

	/* First character: File type */
	ch = '?';

	switch (mode & S_IFMT) {

	case S_IFDIR:  ch = 'd'; break;


	case S_IFCHR:  ch = 'c'; break;


	case S_IFBLK:  ch = 'b'; break;


	case S_IFREG:  ch = '-'; break;


	case S_IFLNK:  ch = 'l'; break;


	case S_IFSOCK: ch = 's'; break;


	case S_IFIFO:  ch = 'p'; break; /* p=pipe */

	default: break;
	}

	*p++ = ch;

	*p++ = mode & S_IRUSR ? 'r' : '-';
	*p++ = mode & S_IWUSR ? 'w' : '-';


	switch (mode & (S_IXUSR | S_ISUID)) {
	case 0:                 ch = '-'; break;
	case S_IXUSR:           ch = 'x'; break;
	case S_ISUID:           ch = 'S'; break;
	case S_IXUSR | S_ISUID: ch = 's'; break;
	default: __builtin_unreachable();
	}



	*p++ = ch;

	*p++ = mode & S_IRGRP ? 'r' : '-';
	*p++ = mode & S_IWGRP ? 'w' : '-';


	switch (mode & (S_IXGRP | S_ISGID)) {
	case 0:                 ch = '-'; break;
	case S_IXGRP:           ch = 'x'; break;
	case S_ISGID:           ch = 'S'; break;
	case S_IXGRP | S_ISGID: ch = 's'; break;
	default: __builtin_unreachable();
	}



	*p++ = ch;

	*p++ = mode & S_IROTH ? 'r' : '-';
	*p++ = mode & S_IWOTH ? 'w' : '-';


	switch (mode & (S_IXOTH | S_ISVTX)) {
	case 0:                 ch = '-'; break;
	case S_IXOTH:           ch = 'x'; break;
	case S_ISVTX:           ch = 'T'; break;
	case S_IXOTH | S_ISVTX: ch = 't'; break;
	default: __builtin_unreachable();
	}



	*p++ = ch;

	/* Always space in this implementation */
	*p++ = ' ';

	/* NUL-terminate */
	*p = '\0';
}
#include <asm/signed-shift.h>
/* >> timingsafe_memcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: <  0: Block `s1' should be considered less than `s2'
 * @return: == 0: Memory blocks are equal.
 * @return: >  0: Block `s1' should be considered greater than `s2' */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) int
NOTHROW_NCX(LIBCCALL libc_timingsafe_memcmp)(void const *s1,
                                             void const *s2,
                                             size_t n_bytes) {
	int result = 0, finished = 0;
	/* Suppress warnings about ATTR_PURE. Even though they're correct,
	 * don't mark  this function  as `pure'  to prevent  any  compiler
	 * optimizations which  may result  in  the `timingsafe'  part  of
	 * this function's purpose no longer being correct. */
	COMPILER_IMPURE();
	while (n_bytes) {
		int a_le_b, a_gr_b, diff;
		__SBYTE_TYPE__ a, b;
		a = *(__SBYTE_TYPE__ const *)s1;
		b = *(__SBYTE_TYPE__ const *)s2;

		/* a_le_b:
		 *    0  <=> a <= b <=> 0b0???????
		 *   -1  <=> a >  b <=> 0b1???????
		 *                        | >>= 7 (signed shift --> copy sign bit to all other positions)
		 *                        +-> 0bXXXXXXXX
		 * HINT: (signed)x >> 7 == (signed)x / 0x80 == 0xff * ((unsigned)x >> 7)
		 *
		 * >> a_le_b = a <= b ? 0 : -1; */
#ifdef __ARCH_SIGNED_SHIFT_IS_SDIV
		a_le_b = (int)((b - a) >> (__CHAR_BIT__ - 1));
#else /* __ARCH_SIGNED_SHIFT_IS_SDIV */
		a_le_b = (int)((b - a) / (1 << (__CHAR_BIT__ - 1)));
#endif /* !__ARCH_SIGNED_SHIFT_IS_SDIV */

		/* a_gr_b:
		 *    0  <=> a >= b <=> 0b0???????
		 *   -1  <=> a <  b <=> 0b1???????
		 *                        | >>= 7 (signed shift --> copy sign bit to all other positions)
		 *                        +-> 0bXXXXXXXX
		 * HINT: (signed)x >> 7 == (signed)x / 0x80 == 0xff * ((unsigned)x >> 7)
		 *
		 * >> a_gr_b = a >= b ? 0 : -1; */
#ifdef __ARCH_SIGNED_SHIFT_IS_SDIV
		a_gr_b = (int)((a - b) >> (__CHAR_BIT__ - 1));
#else /* __ARCH_SIGNED_SHIFT_IS_SDIV */
		a_gr_b = (int)((a - b) / (1 << (__CHAR_BIT__ - 1)));
#endif /* !__ARCH_SIGNED_SHIFT_IS_SDIV */

		/* a <  b  <=>  [a_le_b= 0,a_gr_b=-1]   -> diff=-1
		 * a == b  <=>  [a_le_b= 0,a_gr_b= 0]   -> diff= 0
		 * a >  b  <=>  [a_le_b=-1,a_gr_b= 0]   -> diff=+1 */
		diff = a_gr_b - a_le_b;

		/* (finished == 0) <=> (~finished != 0)
		 * (finished == 0) <=> {All preceding bytes were equal}
		 *
		 * >> if ({All preceding bytes were equal})
		 * >>     result = diff; */
		result |= diff & ~finished;

		/* ((a_gr_b | a_le_b) == -1)  <=>  {a != b}
		 *
		 * >> if (a != b)
		 * >>     finished = -1; */
		finished |= a_gr_b | a_le_b;

		s1 = (__SBYTE_TYPE__ const *)s1 + 1;
		s2 = (__SBYTE_TYPE__ const *)s2 + 1;
		--n_bytes;
	}
	return result;
}
/* >> strtosigno(3)
 * Return the signal number for a given name.
 * e.g.: `strtosigno("SIGINT") == SIGINT'
 * When `name' isn't recognized, return `0' instead. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) signo_t
NOTHROW_NCX(LIBCCALL libc_strtosigno)(const char *name) {
	size_t i;
	if (name[0] != 'S' || name[1] != 'I' || name[2] != 'G')
		return 0;
	name += 3;
	for (i = 0; name[i]; ++i) {
		if (!libc_isupper(name[i]))
			return 0;
	}
	return libc_signalnumber(name);
}
/* >> stresep(3)
 * Same as `strsep(3)', but allow the specification of an additional `escape'
 * character  that will cause  the following character  from `*stringp' to be
 * escaped, and not  be considered  as a separator,  even if  it is  included
 * within `delim'. Note that `escape'-characters (if present) are not removed
 * from  the input  string, meaning that  they will still  appear in returned
 * strings, should they have been present in the original input string. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char *
NOTHROW_NCX(LIBCCALL libc_stresep)(char **__restrict stringp,
                                   char const *__restrict delim,
                                   int escape) {
	char *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result;; ++iter) {
		char ch = *iter;
		if (!ch)
			break;
		if ((int)(unsigned int)(unsigned char)ch == escape) {
			/* Escape the next character. */
			ch = *++iter;
			if (!ch)
				break;
		}
		if (libc_strchr(delim, ch))
			break;
	}
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}
/* >> consttime_memequal(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are non-equal.
 * @return: != 0: Memory blocks are equal. */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) int
NOTHROW_NCX(LIBCCALL libc_consttime_memequal)(void const *s1,
                                              void const *s2,
                                              size_t n_bytes) {
	return libc_timingsafe_memcmp(s1, s2, n_bytes) == 0;
}
#include <kos/except.h>
#include <libc/errno.h>
/* >> uucopy(2)
 * Copy `num_bytes' from `src' to `dst'. The copy is done such that  any
 * faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: 0 : Success
 * @return: -1: [errno=EFAULT] Faulty memory access */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_INS(1, 3) ATTR_OUTS(2, 3) int
NOTHROW_NCX(LIBCCALL libc_uucopy)(void const *__restrict src,
                                  void *__restrict dst,
                                  size_t num_bytes) {
	NESTED_TRY {
		libc_memcpy(dst, src, num_bytes);
	} EXCEPT {

		return __libc_seterrno(libc_except_as_errno(libc_except_data()));





	}
	return 0;
}
#include <kos/except.h>
#include <libc/errno.h>
/* >> uucopystr(2)
 * Copy  a string `src' into `dst', but copy no more than `maxlen' characters (including trailing NUL).
 * The copy is done such that any faulty memory access is handled by returning `-1' with `errno=EFAULT'
 * @return: * : The number of copied characters (including trialing NUL; )
 * @return: -1: [errno=EFAULT]       Faulty memory access
 * @return: -1: [errno=ENAMETOOLONG] `strlen(src) >= maxlen' */
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_IN_OPT(1) ATTR_OUT_OPT(2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_uucopystr)(void const *__restrict src,
                                     void *__restrict dst,
                                     size_t maxlen) {
	size_t result = 0;
	NESTED_TRY {
		byte_t const *s_ptr = (byte_t const *)src;
		byte_t *d_ptr = (byte_t *)dst;
		for (;;) {
			char ch;
			if unlikely(maxlen == 0) {

				return __libc_seterrno(ENAMETOOLONG);



			}
			--maxlen;
			COMPILER_BARRIER();
			ch = *s_ptr++;
			*d_ptr++ = ch;
			COMPILER_BARRIER();
			++result;
			if (ch == '\0')
				break;
		}
	} EXCEPT {

		return __libc_seterrno(libc_except_as_errno(libc_except_data()));





	}
	return (__STDC_INT_AS_SSIZE_T)result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef LIBC_ARCH_HAVE_MEMCPY
DEFINE_PUBLIC_ALIAS(memcpy, libc_memcpy);
#endif /* !LIBC_ARCH_HAVE_MEMCPY */
#ifndef LIBC_ARCH_HAVE_MEMMOVE
DEFINE_PUBLIC_ALIAS(memmove, libc_memmove);
#endif /* !LIBC_ARCH_HAVE_MEMMOVE */
#ifndef LIBC_ARCH_HAVE_MEMSET
DEFINE_PUBLIC_ALIAS(memset, libc_memset);
#endif /* !LIBC_ARCH_HAVE_MEMSET */
#ifndef LIBC_ARCH_HAVE_MEMCMP
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__gcc_bcmp, libc_memcmp);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(memcmp, libc_memcmp);
#endif /* !LIBC_ARCH_HAVE_MEMCMP */
#ifndef LIBC_ARCH_HAVE_MEMCHR
DEFINE_PUBLIC_ALIAS(memchr, libc_memchr);
#endif /* !LIBC_ARCH_HAVE_MEMCHR */
#ifndef LIBC_ARCH_HAVE_STRLEN
DEFINE_PUBLIC_ALIAS(strlen, libc_strlen);
#endif /* !LIBC_ARCH_HAVE_STRLEN */
#ifndef LIBC_ARCH_HAVE_STRCHR
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(index, libc_strchr);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strchr, libc_strchr);
#endif /* !LIBC_ARCH_HAVE_STRCHR */
#ifndef LIBC_ARCH_HAVE_STRRCHR
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(rindex, libc_strrchr);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strrchr, libc_strrchr);
#endif /* !LIBC_ARCH_HAVE_STRRCHR */
#ifndef LIBC_ARCH_HAVE_STRCMP
DEFINE_PUBLIC_ALIAS(strcmp, libc_strcmp);
#endif /* !LIBC_ARCH_HAVE_STRCMP */
#ifndef LIBC_ARCH_HAVE_STRNCMP
DEFINE_PUBLIC_ALIAS(strncmp, libc_strncmp);
#endif /* !LIBC_ARCH_HAVE_STRNCMP */
#ifndef LIBC_ARCH_HAVE_STRSTR
DEFINE_PUBLIC_ALIAS(strstr, libc_strstr);
#endif /* !LIBC_ARCH_HAVE_STRSTR */
#ifndef LIBC_ARCH_HAVE_STRCPY
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mbscpy, libc_strcpy);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strcpy, libc_strcpy);
#endif /* !LIBC_ARCH_HAVE_STRCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCPY)
DEFINE_PUBLIC_ALIAS(strncpy, libc_strncpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCPY */
#ifndef LIBC_ARCH_HAVE_STRCAT
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_mbscat, libc_strcat);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strcat, libc_strcat);
#endif /* !LIBC_ARCH_HAVE_STRCAT */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCAT)
DEFINE_PUBLIC_ALIAS(strncat, libc_strncat);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCAT */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCSPN)
DEFINE_PUBLIC_ALIAS(strcspn, libc_strcspn);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCSPN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRSPN)
DEFINE_PUBLIC_ALIAS(strspn, libc_strspn);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRSPN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRPBRK)
DEFINE_PUBLIC_ALIAS(strpbrk, libc_strpbrk);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRPBRK */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(strtok, libc_strtok);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCOLL)
DEFINE_PUBLIC_ALIAS(strcoll, libc_strcoll);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCOLL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRXFRM)
DEFINE_PUBLIC_ALIAS(strxfrm, libc_strxfrm);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRXFRM */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$xstrerror, libd_strerror);
DEFINE_PUBLIC_ALIAS(DOS$strerror, libd_strerror);
DEFINE_PUBLIC_ALIAS(xstrerror, libc_strerror);
DEFINE_PUBLIC_ALIAS(strerror, libc_strerror);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRNLEN
#if defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(__strncnt, libc_strnlen);
#endif /* __LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strnlen, libc_strnlen);
#endif /* !LIBC_ARCH_HAVE_STRNLEN */
#ifndef LIBC_ARCH_HAVE_STPCPY
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__stpcpy, libc_stpcpy);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(stpcpy, libc_stpcpy);
#endif /* !LIBC_ARCH_HAVE_STPCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STPNCPY)
DEFINE_PUBLIC_ALIAS(__stpncpy, libc_stpncpy);
DEFINE_PUBLIC_ALIAS(stpncpy, libc_stpncpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STPNCPY */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strcoll_l, libc_strcoll_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strcoll_l, libc_strcoll_l);
DEFINE_PUBLIC_ALIAS(strcoll_l, libc_strcoll_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strxfrm_l, libc_strxfrm_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_ALIAS(strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$strerror_l, libd_strerror_l);
DEFINE_PUBLIC_ALIAS(strerror_l, libc_strerror_l);
DEFINE_PUBLIC_ALIAS(DOS$strsignal, libd_strsignal);
DEFINE_PUBLIC_ALIAS(strsignal, libc_strsignal);
DEFINE_PUBLIC_ALIAS(__strndup, libc_strndup);
DEFINE_PUBLIC_ALIAS(strndup, libc_strndup);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strdup, libc_strdup);
DEFINE_PUBLIC_ALIAS(_mbsdup, libc_strdup);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strdup, libc_strdup);
DEFINE_PUBLIC_ALIAS(strdup, libc_strdup);
DEFINE_PUBLIC_ALIAS(strtok_s, libc_strtok_r);
DEFINE_PUBLIC_ALIAS(__strtok_r, libc_strtok_r);
DEFINE_PUBLIC_ALIAS(strtok_r, libc_strtok_r);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMRCHR
DEFINE_PUBLIC_ALIAS(memrchr, libc_memrchr);
#endif /* !LIBC_ARCH_HAVE_MEMRCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMMEM)
DEFINE_PUBLIC_ALIAS(memmem, libc_memmem);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMMEM */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__strcasestr, libc_strcasestr);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strcasestr, libc_strcasestr);
#ifndef LIBC_ARCH_HAVE_STRCHRNUL
DEFINE_PUBLIC_ALIAS(strchrnul, libc_strchrnul);
#endif /* !LIBC_ARCH_HAVE_STRCHRNUL */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHR
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__rawmemchr, libc_rawmemchr);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(rawmemchr, libc_rawmemchr);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHR */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__basename, libc_basename);
DEFINE_PUBLIC_ALIAS(lbasename, libc_basename);
DEFINE_PUBLIC_ALIAS(unix_lbasename, libc_basename);
DEFINE_PUBLIC_ALIAS(basename, libc_basename);
DEFINE_PUBLIC_ALIAS(__strverscmp, libc_strverscmp);
DEFINE_PUBLIC_ALIAS(strverscmp, libc_strverscmp);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMPCPY
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__mempcpy, libc_mempcpy);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(mempcpy, libc_mempcpy);
#endif /* !LIBC_ARCH_HAVE_MEMPCPY */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(strfry, libc_strfry);
DEFINE_PUBLIC_ALIAS(memfrob, libc_memfrob);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_stricmp_l, libc_strcasecmp_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strcasecmp_l, libc_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(strcasecmp_l, libc_strcasecmp_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strnicmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(_strncmpi_l, libc_strncasecmp_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strncasecmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(strncasecmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$strerrordesc_np, libd_strerrordesc_np);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strerrordesc_np, libc_strerrordesc_np);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$strerrno, libd_strerrorname_np);
DEFINE_PUBLIC_ALIAS(DOS$strerrorname_np, libd_strerrorname_np);
DEFINE_PUBLIC_ALIAS(strerrno, libc_strerrorname_np);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strerrorname_np, libc_strerrorname_np);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$signalname, libd_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(DOS$strsigno, libd_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(DOS$sigabbrev_np, libd_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(signalname, libc_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(strsigno, libc_sigabbrev_np);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigabbrev_np, libc_sigabbrev_np);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$sigdescr_np, libd_sigdescr_np);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigdescr_np, libc_sigdescr_np);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$__strerror_r, libd_strerror_r);
DEFINE_PUBLIC_ALIAS(DOS$strerror_r, libd_strerror_r);
DEFINE_PUBLIC_ALIAS(__strerror_r, libc_strerror_r);
DEFINE_PUBLIC_ALIAS(strerror_r, libc_strerror_r);
DEFINE_PUBLIC_ALIAS(DOS$__xpg_strerror_r, libd___xpg_strerror_r);
DEFINE_PUBLIC_ALIAS(__xpg_strerror_r, libc___xpg_strerror_r);
DEFINE_PUBLIC_ALIAS(strsep, libc_strsep);
DEFINE_PUBLIC_ALIAS(bcopy, libc_bcopy);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_BZERO
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__bzero, libc_bzero);
DEFINE_PUBLIC_ALIAS(explicit_bzero, libc_bzero);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(bzero, libc_bzero);
#endif /* !LIBC_ARCH_HAVE_BZERO */
#ifndef LIBC_ARCH_HAVE_BZEROW
DEFINE_PUBLIC_ALIAS(bzerow, libc_bzerow);
#endif /* !LIBC_ARCH_HAVE_BZEROW */
#ifndef LIBC_ARCH_HAVE_BZEROL
DEFINE_PUBLIC_ALIAS(bzerol, libc_bzerol);
#endif /* !LIBC_ARCH_HAVE_BZEROL */
#ifndef LIBC_ARCH_HAVE_BCMPW
DEFINE_PUBLIC_ALIAS(bcmpw, libc_bcmpw);
#endif /* !LIBC_ARCH_HAVE_BCMPW */
#ifndef LIBC_ARCH_HAVE_BCMPL
DEFINE_PUBLIC_ALIAS(bcmpl, libc_bcmpl);
#endif /* !LIBC_ARCH_HAVE_BCMPL */
#ifndef LIBC_ARCH_HAVE_BZEROQ
DEFINE_PUBLIC_ALIAS(bzeroq, libc_bzeroq);
#endif /* !LIBC_ARCH_HAVE_BZEROQ */
#ifndef LIBC_ARCH_HAVE_BCMPQ
DEFINE_PUBLIC_ALIAS(bcmpq, libc_bcmpq);
#endif /* !LIBC_ARCH_HAVE_BCMPQ */
DEFINE_PUBLIC_ALIAS(bzeroc, libc_bzeroc);
#ifndef LIBC_ARCH_HAVE_BCMPC
DEFINE_PUBLIC_ALIAS(bcmpc, libc_bcmpc);
#endif /* !LIBC_ARCH_HAVE_BCMPC */
#ifndef LIBC_ARCH_HAVE_BCMP
DEFINE_PUBLIC_ALIAS(bcmp, libc_bcmp);
#endif /* !LIBC_ARCH_HAVE_BCMP */
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_stricmp, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(_strcmpi, libc_strcasecmp);
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(stricmp, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(strcmpi, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(__strcasecmp, libc_strcasecmp);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strcasecmp, libc_strcasecmp);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strnicmp, libc_strncasecmp);
DEFINE_PUBLIC_ALIAS(_strncmpi, libc_strncasecmp);
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(strnicmp, libc_strncasecmp);
DEFINE_PUBLIC_ALIAS(strncmpi, libc_strncasecmp);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strncasecmp, libc_strncasecmp);
#if !defined(__KERNEL__) && ((__SIZEOF_INT__ == __SIZEOF_LONG__ && !defined(LIBC_ARCH_HAVE_FFSL)) || (__SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && !defined(LIBC_ARCH_HAVE_FFSLL)) || !defined(LIBC_ARCH_HAVE_FFS))
DEFINE_PUBLIC_ALIAS(__ffs, libc_ffs);
DEFINE_PUBLIC_ALIAS(ffs, libc_ffs);
#endif /* !__KERNEL__ && ((__SIZEOF_INT__ == __SIZEOF_LONG__ && !LIBC_ARCH_HAVE_FFSL) || (__SIZEOF_INT__ == __SIZEOF_LONG_LONG__ && !LIBC_ARCH_HAVE_FFSLL) || !LIBC_ARCH_HAVE_FFS) */
#if !defined(__KERNEL__) && ((__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && !defined(LIBC_ARCH_HAVE_FFSLL)) || !defined(LIBC_ARCH_HAVE_FFSL))
DEFINE_PUBLIC_ALIAS(ffsl, libc_ffsl);
#endif /* !__KERNEL__ && ((__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && !LIBC_ARCH_HAVE_FFSLL) || !LIBC_ARCH_HAVE_FFSL) */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_FFSLL)
DEFINE_PUBLIC_ALIAS(ffsll, libc_ffsll);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_FFSLL */
#ifndef LIBC_ARCH_HAVE_STRLCAT
DEFINE_PUBLIC_ALIAS(strlcat, libc_strlcat);
#endif /* !LIBC_ARCH_HAVE_STRLCAT */
#ifndef LIBC_ARCH_HAVE_STRLCPY
DEFINE_PUBLIC_ALIAS(strlcpy, libc_strlcpy);
#endif /* !LIBC_ARCH_HAVE_STRLCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMCCPY)
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_memccpy, libc_memccpy);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__memccpy, libc_memccpy);
DEFINE_PUBLIC_ALIAS(memccpy, libc_memccpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMCCPY */
#ifndef LIBC_ARCH_HAVE_MEMCPYW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmemcpy, libc_memcpyw);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(memcpyw, libc_memcpyw);
#endif /* !LIBC_ARCH_HAVE_MEMCPYW */
#ifndef LIBC_ARCH_HAVE_MEMPCPYW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmempcpy, libc_mempcpyw);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(mempcpyw, libc_mempcpyw);
#endif /* !LIBC_ARCH_HAVE_MEMPCPYW */
#ifndef LIBC_ARCH_HAVE_MEMCPYL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmemcpy, libc_memcpyl);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(memcpyl, libc_memcpyl);
#endif /* !LIBC_ARCH_HAVE_MEMCPYL */
#ifndef LIBC_ARCH_HAVE_MEMPCPYL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmempcpy, libc_mempcpyl);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(mempcpyl, libc_mempcpyl);
#endif /* !LIBC_ARCH_HAVE_MEMPCPYL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmemmove, libc_memmovew);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(memmovew, libc_memmovew);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmempmove, libc_mempmovew);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(mempmovew, libc_mempmovew);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmemmove, libc_memmovel);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(memmovel, libc_memmovel);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmempmove, libc_mempmovel);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(mempmovel, libc_mempmovel);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPW
DEFINE_PUBLIC_ALIAS(memmoveupw, libc_memmoveupw);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNW
DEFINE_PUBLIC_ALIAS(memmovedownw, libc_memmovedownw);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPW
DEFINE_PUBLIC_ALIAS(mempmoveupw, libc_mempmoveupw);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNW
DEFINE_PUBLIC_ALIAS(mempmovedownw, libc_mempmovedownw);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPL
DEFINE_PUBLIC_ALIAS(memmoveupl, libc_memmoveupl);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNL
DEFINE_PUBLIC_ALIAS(memmovedownl, libc_memmovedownl);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPL
DEFINE_PUBLIC_ALIAS(mempmoveupl, libc_mempmoveupl);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNL
DEFINE_PUBLIC_ALIAS(mempmovedownl, libc_mempmovedownl);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMSETW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmemset, libc_memsetw);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(memsetw, libc_memsetw);
#endif /* !LIBC_ARCH_HAVE_MEMSETW */
#ifndef LIBC_ARCH_HAVE_MEMPSETW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmempset, libc_mempsetw);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(mempsetw, libc_mempsetw);
#endif /* !LIBC_ARCH_HAVE_MEMPSETW */
#ifndef LIBC_ARCH_HAVE_MEMSETL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmemset, libc_memsetl);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(memsetl, libc_memsetl);
#endif /* !LIBC_ARCH_HAVE_MEMSETL */
#ifndef LIBC_ARCH_HAVE_MEMPSETL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmempset, libc_mempsetl);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(mempsetl, libc_mempsetl);
#endif /* !LIBC_ARCH_HAVE_MEMPSETL */
#ifndef LIBC_ARCH_HAVE_MEMCMPW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmemcmp, libc_memcmpw);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(memcmpw, libc_memcmpw);
#endif /* !LIBC_ARCH_HAVE_MEMCMPW */
#ifndef LIBC_ARCH_HAVE_MEMCMPL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmemcmp, libc_memcmpl);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(memcmpl, libc_memcmpl);
#endif /* !LIBC_ARCH_HAVE_MEMCMPL */
#ifndef LIBC_ARCH_HAVE_MEMCHRW
#if !defined(__KERNEL__) && defined(__LIBCCALL_IS_LIBDCALL)
DEFINE_PUBLIC_ALIAS(DOS$wmemchr, libc_memchrw);
#endif /* !__KERNEL__ && __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(memchrw, libc_memchrw);
#endif /* !LIBC_ARCH_HAVE_MEMCHRW */
#ifndef LIBC_ARCH_HAVE_MEMCHRL
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(wmemchr, libc_memchrl);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(memchrl, libc_memchrl);
#endif /* !LIBC_ARCH_HAVE_MEMCHRL */
#ifndef LIBC_ARCH_HAVE_MEMRCHRW
DEFINE_PUBLIC_ALIAS(memrchrw, libc_memrchrw);
#endif /* !LIBC_ARCH_HAVE_MEMRCHRW */
#ifndef LIBC_ARCH_HAVE_MEMRCHRL
DEFINE_PUBLIC_ALIAS(memrchrl, libc_memrchrl);
#endif /* !LIBC_ARCH_HAVE_MEMRCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRW
DEFINE_PUBLIC_ALIAS(rawmemchrw, libc_rawmemchrw);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRL
DEFINE_PUBLIC_ALIAS(rawmemchrl, libc_rawmemchrl);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRW
DEFINE_PUBLIC_ALIAS(rawmemrchrw, libc_rawmemrchrw);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRL
DEFINE_PUBLIC_ALIAS(rawmemrchrl, libc_rawmemrchrl);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRL */
#ifndef LIBC_ARCH_HAVE_MEMENDW
DEFINE_PUBLIC_ALIAS(memendw, libc_memendw);
#endif /* !LIBC_ARCH_HAVE_MEMENDW */
#ifndef LIBC_ARCH_HAVE_MEMENDL
DEFINE_PUBLIC_ALIAS(memendl, libc_memendl);
#endif /* !LIBC_ARCH_HAVE_MEMENDL */
#ifndef LIBC_ARCH_HAVE_MEMRENDW
DEFINE_PUBLIC_ALIAS(memrendw, libc_memrendw);
#endif /* !LIBC_ARCH_HAVE_MEMRENDW */
#ifndef LIBC_ARCH_HAVE_MEMRENDL
DEFINE_PUBLIC_ALIAS(memrendl, libc_memrendl);
#endif /* !LIBC_ARCH_HAVE_MEMRENDL */
#ifndef LIBC_ARCH_HAVE_MEMLENW
DEFINE_PUBLIC_ALIAS(memlenw, libc_memlenw);
#endif /* !LIBC_ARCH_HAVE_MEMLENW */
#ifndef LIBC_ARCH_HAVE_MEMLENL
DEFINE_PUBLIC_ALIAS(memlenl, libc_memlenl);
#endif /* !LIBC_ARCH_HAVE_MEMLENL */
#ifndef LIBC_ARCH_HAVE_MEMRLENW
DEFINE_PUBLIC_ALIAS(memrlenw, libc_memrlenw);
#endif /* !LIBC_ARCH_HAVE_MEMRLENW */
#ifndef LIBC_ARCH_HAVE_MEMRLENL
DEFINE_PUBLIC_ALIAS(memrlenl, libc_memrlenl);
#endif /* !LIBC_ARCH_HAVE_MEMRLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENW
DEFINE_PUBLIC_ALIAS(rawmemlenw, libc_rawmemlenw);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENL
DEFINE_PUBLIC_ALIAS(rawmemlenl, libc_rawmemlenl);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENW
DEFINE_PUBLIC_ALIAS(rawmemrlenw, libc_rawmemrlenw);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENL
DEFINE_PUBLIC_ALIAS(rawmemrlenl, libc_rawmemrlenl);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENL */
#ifndef LIBC_ARCH_HAVE_MEMCPYQ
DEFINE_PUBLIC_ALIAS(memcpyq, libc_memcpyq);
#endif /* !LIBC_ARCH_HAVE_MEMCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMPCPYQ
DEFINE_PUBLIC_ALIAS(mempcpyq, libc_mempcpyq);
#endif /* !LIBC_ARCH_HAVE_MEMPCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEQ
DEFINE_PUBLIC_ALIAS(memmoveq, libc_memmoveq);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEQ
DEFINE_PUBLIC_ALIAS(mempmoveq, libc_mempmoveq);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPQ
DEFINE_PUBLIC_ALIAS(memmoveupq, libc_memmoveupq);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNQ
DEFINE_PUBLIC_ALIAS(memmovedownq, libc_memmovedownq);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPQ
DEFINE_PUBLIC_ALIAS(mempmoveupq, libc_mempmoveupq);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNQ
DEFINE_PUBLIC_ALIAS(mempmovedownq, libc_mempmovedownq);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMSETQ
DEFINE_PUBLIC_ALIAS(memsetq, libc_memsetq);
#endif /* !LIBC_ARCH_HAVE_MEMSETQ */
#ifndef LIBC_ARCH_HAVE_MEMPSETQ
DEFINE_PUBLIC_ALIAS(mempsetq, libc_mempsetq);
#endif /* !LIBC_ARCH_HAVE_MEMPSETQ */
#ifndef LIBC_ARCH_HAVE_MEMCMPQ
DEFINE_PUBLIC_ALIAS(memcmpq, libc_memcmpq);
#endif /* !LIBC_ARCH_HAVE_MEMCMPQ */
#ifndef LIBC_ARCH_HAVE_MEMCHRQ
DEFINE_PUBLIC_ALIAS(memchrq, libc_memchrq);
#endif /* !LIBC_ARCH_HAVE_MEMCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMRCHRQ
DEFINE_PUBLIC_ALIAS(memrchrq, libc_memrchrq);
#endif /* !LIBC_ARCH_HAVE_MEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRQ
DEFINE_PUBLIC_ALIAS(rawmemchrq, libc_rawmemchrq);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRQ
DEFINE_PUBLIC_ALIAS(rawmemrchrq, libc_rawmemrchrq);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMENDQ
DEFINE_PUBLIC_ALIAS(memendq, libc_memendq);
#endif /* !LIBC_ARCH_HAVE_MEMENDQ */
#ifndef LIBC_ARCH_HAVE_MEMRENDQ
DEFINE_PUBLIC_ALIAS(memrendq, libc_memrendq);
#endif /* !LIBC_ARCH_HAVE_MEMRENDQ */
#ifndef LIBC_ARCH_HAVE_MEMLENQ
DEFINE_PUBLIC_ALIAS(memlenq, libc_memlenq);
#endif /* !LIBC_ARCH_HAVE_MEMLENQ */
#ifndef LIBC_ARCH_HAVE_MEMRLENQ
DEFINE_PUBLIC_ALIAS(memrlenq, libc_memrlenq);
#endif /* !LIBC_ARCH_HAVE_MEMRLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENQ
DEFINE_PUBLIC_ALIAS(rawmemlenq, libc_rawmemlenq);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENQ
DEFINE_PUBLIC_ALIAS(rawmemrlenq, libc_rawmemrlenq);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHR)
DEFINE_PUBLIC_ALIAS(memxchr, libc_memxchr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHR)
DEFINE_PUBLIC_ALIAS(memrxchr, libc_memrxchr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHR)
DEFINE_PUBLIC_ALIAS(rawmemxchr, libc_rawmemxchr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHR)
DEFINE_PUBLIC_ALIAS(rawmemrxchr, libc_rawmemrxchr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXEND)
DEFINE_PUBLIC_ALIAS(memxend, libc_memxend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXEND)
DEFINE_PUBLIC_ALIAS(memrxend, libc_memrxend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLEN)
DEFINE_PUBLIC_ALIAS(memxlen, libc_memxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLEN)
DEFINE_PUBLIC_ALIAS(memrxlen, libc_memrxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLEN)
DEFINE_PUBLIC_ALIAS(rawmemxlen, libc_rawmemxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLEN)
DEFINE_PUBLIC_ALIAS(rawmemrxlen, libc_rawmemrxlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHRW)
DEFINE_PUBLIC_ALIAS(memxchrw, libc_memxchrw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHRL)
DEFINE_PUBLIC_ALIAS(memxchrl, libc_memxchrl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHRW)
DEFINE_PUBLIC_ALIAS(memrxchrw, libc_memrxchrw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHRL)
DEFINE_PUBLIC_ALIAS(memrxchrl, libc_memrxchrl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHRW)
DEFINE_PUBLIC_ALIAS(rawmemxchrw, libc_rawmemxchrw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHRL)
DEFINE_PUBLIC_ALIAS(rawmemxchrl, libc_rawmemxchrl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHRW)
DEFINE_PUBLIC_ALIAS(rawmemrxchrw, libc_rawmemrxchrw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHRW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHRL)
DEFINE_PUBLIC_ALIAS(rawmemrxchrl, libc_rawmemrxchrl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHRL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXENDW)
DEFINE_PUBLIC_ALIAS(memxendw, libc_memxendw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXENDW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXENDL)
DEFINE_PUBLIC_ALIAS(memxendl, libc_memxendl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXENDL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXENDW)
DEFINE_PUBLIC_ALIAS(memrxendw, libc_memrxendw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXENDW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXENDL)
DEFINE_PUBLIC_ALIAS(memrxendl, libc_memrxendl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXENDL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLENW)
DEFINE_PUBLIC_ALIAS(memxlenw, libc_memxlenw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLENL)
DEFINE_PUBLIC_ALIAS(memxlenl, libc_memxlenl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLENW)
DEFINE_PUBLIC_ALIAS(memrxlenw, libc_memrxlenw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLENL)
DEFINE_PUBLIC_ALIAS(memrxlenl, libc_memrxlenl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLENW)
DEFINE_PUBLIC_ALIAS(rawmemxlenw, libc_rawmemxlenw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLENL)
DEFINE_PUBLIC_ALIAS(rawmemxlenl, libc_rawmemxlenl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLENW)
DEFINE_PUBLIC_ALIAS(rawmemrxlenw, libc_rawmemrxlenw);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLENW */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLENL)
DEFINE_PUBLIC_ALIAS(rawmemrxlenl, libc_rawmemrxlenl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLENL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXCHRQ)
DEFINE_PUBLIC_ALIAS(memxchrq, libc_memxchrq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXCHRQ)
DEFINE_PUBLIC_ALIAS(memrxchrq, libc_memrxchrq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXCHRQ)
DEFINE_PUBLIC_ALIAS(rawmemxchrq, libc_rawmemxchrq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXCHRQ)
DEFINE_PUBLIC_ALIAS(rawmemrxchrq, libc_rawmemrxchrq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXCHRQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXENDQ)
DEFINE_PUBLIC_ALIAS(memxendq, libc_memxendq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXENDQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXENDQ)
DEFINE_PUBLIC_ALIAS(memrxendq, libc_memrxendq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXENDQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMXLENQ)
DEFINE_PUBLIC_ALIAS(memxlenq, libc_memxlenq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMXLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRXLENQ)
DEFINE_PUBLIC_ALIAS(memrxlenq, libc_memrxlenq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRXLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMXLENQ)
DEFINE_PUBLIC_ALIAS(rawmemxlenq, libc_rawmemxlenq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMXLENQ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_RAWMEMRXLENQ)
DEFINE_PUBLIC_ALIAS(rawmemrxlenq, libc_rawmemrxlenq);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_RAWMEMRXLENQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUP
DEFINE_PUBLIC_ALIAS(memmoveup, libc_memmoveup);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWN
DEFINE_PUBLIC_ALIAS(memmovedown, libc_memmovedown);
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWN */
#ifndef LIBC_ARCH_HAVE_MEMCMPC
DEFINE_PUBLIC_ALIAS(memcmpc, libc_memcmpc);
#endif /* !LIBC_ARCH_HAVE_MEMCMPC */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(memcpyc, libc_memcpyc);
DEFINE_PUBLIC_ALIAS(mempcpyc, libc_mempcpyc);
DEFINE_PUBLIC_ALIAS(memmovec, libc_memmovec);
DEFINE_PUBLIC_ALIAS(mempmovec, libc_mempmovec);
DEFINE_PUBLIC_ALIAS(memmoveupc, libc_memmoveupc);
DEFINE_PUBLIC_ALIAS(mempmoveupc, libc_mempmoveupc);
DEFINE_PUBLIC_ALIAS(memmovedownc, libc_memmovedownc);
DEFINE_PUBLIC_ALIAS(mempmovedownc, libc_mempmovedownc);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STREND
DEFINE_PUBLIC_ALIAS(strend, libc_strend);
#endif /* !LIBC_ARCH_HAVE_STREND */
#ifndef LIBC_ARCH_HAVE_STRNEND
DEFINE_PUBLIC_ALIAS(strnend, libc_strnend);
#endif /* !LIBC_ARCH_HAVE_STRNEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCHR)
DEFINE_PUBLIC_ALIAS(strnchr, libc_strnchr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNRCHR)
DEFINE_PUBLIC_ALIAS(strnrchr, libc_strnrchr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNRCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRRCHRNUL)
DEFINE_PUBLIC_ALIAS(strrchrnul, libc_strrchrnul);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRRCHRNUL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCHRNUL)
DEFINE_PUBLIC_ALIAS(strnchrnul, libc_strnchrnul);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCHRNUL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNRCHRNUL)
DEFINE_PUBLIC_ALIAS(strnrchrnul, libc_strnrchrnul);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNRCHRNUL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STROFF)
DEFINE_PUBLIC_ALIAS(stroff, libc_stroff);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STROFF */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRROFF)
DEFINE_PUBLIC_ALIAS(strroff, libc_strroff);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRROFF */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNOFF)
DEFINE_PUBLIC_ALIAS(strnoff, libc_strnoff);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNOFF */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNROFF)
DEFINE_PUBLIC_ALIAS(strnroff, libc_strnroff);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNROFF */
#ifndef LIBC_ARCH_HAVE_MEMPSET
DEFINE_PUBLIC_ALIAS(mempset, libc_mempset);
#endif /* !LIBC_ARCH_HAVE_MEMPSET */
#ifndef LIBC_ARCH_HAVE_MEMPMOVE
DEFINE_PUBLIC_ALIAS(mempmove, libc_mempmove);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVE */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUP
DEFINE_PUBLIC_ALIAS(mempmoveup, libc_mempmoveup);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWN
DEFINE_PUBLIC_ALIAS(mempmovedown, libc_mempmovedown);
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHR
DEFINE_PUBLIC_ALIAS(rawmemrchr, libc_rawmemrchr);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHR */
#ifndef LIBC_ARCH_HAVE_MEMEND
DEFINE_PUBLIC_ALIAS(memend, libc_memend);
#endif /* !LIBC_ARCH_HAVE_MEMEND */
#ifndef LIBC_ARCH_HAVE_MEMREND
DEFINE_PUBLIC_ALIAS(memrend, libc_memrend);
#endif /* !LIBC_ARCH_HAVE_MEMREND */
#ifndef LIBC_ARCH_HAVE_MEMLEN
DEFINE_PUBLIC_ALIAS(memlen, libc_memlen);
#endif /* !LIBC_ARCH_HAVE_MEMLEN */
#ifndef LIBC_ARCH_HAVE_MEMRLEN
DEFINE_PUBLIC_ALIAS(memrlen, libc_memrlen);
#endif /* !LIBC_ARCH_HAVE_MEMRLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMLEN
DEFINE_PUBLIC_ALIAS(rawmemlen, libc_rawmemlen);
#endif /* !LIBC_ARCH_HAVE_RAWMEMLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLEN
DEFINE_PUBLIC_ALIAS(rawmemrlen, libc_rawmemrlen);
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMRMEM)
DEFINE_PUBLIC_ALIAS(memrmem, libc_memrmem);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMRMEM */
#ifndef LIBC_ARCH_HAVE_MEMPATW
DEFINE_PUBLIC_ALIAS(mempatw, libc_mempatw);
#endif /* !LIBC_ARCH_HAVE_MEMPATW */
#ifndef LIBC_ARCH_HAVE_MEMPATL
DEFINE_PUBLIC_ALIAS(mempatl, libc_mempatl);
#endif /* !LIBC_ARCH_HAVE_MEMPATL */
#ifndef LIBC_ARCH_HAVE_MEMPATQ
DEFINE_PUBLIC_ALIAS(mempatq, libc_mempatq);
#endif /* !LIBC_ARCH_HAVE_MEMPATQ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(memicmp, libc_memcasecmp);
#endif /* !__KERNEL__ */
#if defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(_memicmp, libc_memcasecmp);
#endif /* __LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(memcasecmp, libc_memcasecmp);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(memcasemem, libc_memcasemem);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_memicmp_l, libc_memcasecmp_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(memcasecmp_l, libc_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(memcasemem_l, libc_memcasemem_l);
DEFINE_PUBLIC_ALIAS(strcasestr_l, libc_strcasestr_l);
DEFINE_PUBLIC_ALIAS(vstrdupf, libc_vstrdupf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$strdupf, libd_strdupf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(strdupf, libc_strdupf);
DEFINE_PUBLIC_ALIAS(wildstrcmp, libc_wildstrcmp);
DEFINE_PUBLIC_ALIAS(wildstrcasecmp, libc_wildstrcasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_strcmp, libc_fuzzy_strcmp);
DEFINE_PUBLIC_ALIAS(fuzzy_strncmp, libc_fuzzy_strncmp);
DEFINE_PUBLIC_ALIAS(fuzzy_strcasecmp, libc_fuzzy_strcasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_strncasecmp, libc_fuzzy_strncasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_memcmp, libc_fuzzy_memcmp);
DEFINE_PUBLIC_ALIAS(fuzzy_memcasecmp, libc_fuzzy_memcasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_strcasecmp_l, libc_fuzzy_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_strncasecmp_l, libc_fuzzy_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(wildstrcasecmp_l, libc_wildstrcasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_memcasecmp_l, libc_fuzzy_memcasecmp_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcmp, libc_fuzzy_memcmpw);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(fuzzy_memcmpw, libc_fuzzy_memcmpw);
DEFINE_PUBLIC_ALIAS(fuzzy_wmemcmp, libc_fuzzy_memcmpl);
DEFINE_PUBLIC_ALIAS(fuzzy_memcmpl, libc_fuzzy_memcmpl);
DEFINE_PUBLIC_ALIAS(fuzzy_memcmpq, libc_fuzzy_memcmpq);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strncoll, libc_strncoll);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strncoll, libc_strncoll);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_stricoll, libc_strcasecoll);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strcasecoll, libc_strcasecoll);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strnicoll, libc_strncasecoll);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strncasecoll, libc_strncasecoll);
DEFINE_PUBLIC_ALIAS(strnrev, libc_strnrev);
DEFINE_PUBLIC_ALIAS(strnlwr, libc_strnlwr);
DEFINE_PUBLIC_ALIAS(strnupr, libc_strnupr);
DEFINE_PUBLIC_ALIAS(memrev, libc_memrev);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strncoll_l, libc_strncoll_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strncoll_l, libc_strncoll_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_stricoll_l, libc_strcasecoll_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strcasecoll_l, libc_strcasecoll_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strnicoll_l, libc_strncasecoll_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strncasecoll_l, libc_strncasecoll_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strlwr_l, libc_strlwr_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strlwr_l, libc_strlwr_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strupr_l, libc_strupr_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strupr_l, libc_strupr_l);
DEFINE_PUBLIC_ALIAS(strnlwr_l, libc_strnlwr_l);
DEFINE_PUBLIC_ALIAS(strnupr_l, libc_strnupr_l);
DEFINE_PUBLIC_ALIAS(memrevw, libc_memrevw);
DEFINE_PUBLIC_ALIAS(memrevl, libc_memrevl);
DEFINE_PUBLIC_ALIAS(memrevq, libc_memrevq);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(strcmpz, libc_strcmpz);
DEFINE_PUBLIC_ALIAS(strstartcmp, libc_strstartcmp);
DEFINE_PUBLIC_ALIAS(strstartcmpz, libc_strstartcmpz);
DEFINE_PUBLIC_ALIAS(bitcpy, libc_bitcpy);
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRRSTR)
DEFINE_PUBLIC_ALIAS(strrstr, libc_strrstr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRRSTR */
DEFINE_PUBLIC_ALIAS(strlstrip, libc_strlstrip);
DEFINE_PUBLIC_ALIAS(strrstrip, libc_strrstrip);
DEFINE_PUBLIC_ALIAS(strstrip, libc_strstrip);
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strlwr, libc_strlwr);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strlwr, libc_strlwr);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strupr, libc_strupr);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strupr, libc_strupr);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strset, libc_strset);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strset, libc_strset);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strnset, libc_strnset);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strnset, libc_strnset);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_strrev, libc_strrev);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strrev, libc_strrev);
DEFINE_PUBLIC_ALIAS(_strset_s, libc__strset_s);
DEFINE_PUBLIC_ALIAS(memcpy_s, libc_memcpy_s);
DEFINE_PUBLIC_ALIAS(memmove_s, libc_memmove_s);
DEFINE_PUBLIC_ALIAS(strcpy_s, libc_strcpy_s);
DEFINE_PUBLIC_ALIAS(strcat_s, libc_strcat_s);
DEFINE_PUBLIC_ALIAS(strncat_s, libc_strncat_s);
DEFINE_PUBLIC_ALIAS(strncpy_s, libc_strncpy_s);
DEFINE_PUBLIC_ALIAS(_strerror, libc__strerror);
DEFINE_PUBLIC_ALIAS(_strerror_s, libc__strerror_s);
DEFINE_PUBLIC_ALIAS(_strlwr_s, libc__strlwr_s);
DEFINE_PUBLIC_ALIAS(_strupr_s, libc__strupr_s);
DEFINE_PUBLIC_ALIAS(_strlwr_s_l, libc__strlwr_s_l);
DEFINE_PUBLIC_ALIAS(_strupr_s_l, libc__strupr_s_l);
DEFINE_PUBLIC_ALIAS(_strnset_s, libc__strnset_s);
DEFINE_PUBLIC_ALIAS(strnstr, libc_strnstr);
DEFINE_PUBLIC_ALIAS(strmode, libc_strmode);
DEFINE_PUBLIC_ALIAS(timingsafe_bcmp, libc_timingsafe_memcmp);
DEFINE_PUBLIC_ALIAS(timingsafe_memcmp, libc_timingsafe_memcmp);
DEFINE_PUBLIC_ALIAS(strtosigno, libc_strtosigno);
DEFINE_PUBLIC_ALIAS(stresep, libc_stresep);
DEFINE_PUBLIC_ALIAS(consttime_memequal, libc_consttime_memequal);
DEFINE_PUBLIC_ALIAS(uucopy, libc_uucopy);
DEFINE_PUBLIC_ALIAS(uucopystr, libc_uucopystr);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STRING_C */
