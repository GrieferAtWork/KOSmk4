/* HASH CRC-32:0xea200b6f */
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
#ifndef GUARD_LIBC_AUTO_STRING_C
#define GUARD_LIBC_AUTO_STRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/string.h"
#include "../user/ctype.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"

DECL_BEGIN

#ifndef LIBC_ARCH_HAVE_MEMCPY
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memcpy)(void *__restrict dst,
                                  void const *__restrict src,
                                  size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPY */
#ifndef LIBC_ARCH_HAVE_MEMMOVE
/* Move memory between potentially overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memmove)(void *dst,
                                   void const *src,
                                   size_t n_bytes) {
	byte_t *pdst, *psrc;
	if (dst <= src) {
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
#endif /* !LIBC_ARCH_HAVE_MEMMOVE */
#ifndef LIBC_ARCH_HAVE_MEMSET
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
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
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_memcmp)(void const *s1,
                                  void const *s2,
                                  size_t n_bytes) {
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes-- && ((v1 = *p1++) == (v2 = *p2++)))
		;
	return (int)v1 - (int)v2;
}
#endif /* !LIBC_ARCH_HAVE_MEMCMP */
#ifndef LIBC_ARCH_HAVE_MEMCHR
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
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
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strlen)(char const *__restrict string) {
	return (size_t)(libc_strend(string) - string);
}
#endif /* !LIBC_ARCH_HAVE_STRLEN */
#ifndef LIBC_ARCH_HAVE_STRCHR
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strchr)(char const *__restrict haystack,
                                  int needle) {
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char)needle)
			return (char *)haystack;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_STRCHR */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STRRCHR
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strrchr)(char const *__restrict haystack,
                                   int needle) {
	char const *result = NULL;
	for (; *haystack; ++haystack) {
		if unlikely(*haystack == (char)needle)
			result = haystack;
	}
	return (char *)result;
}
#endif /* !LIBC_ARCH_HAVE_STRRCHR */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRCMP
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
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
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STRNCMP
/* Same as `strcmp', but compare at most `MAXLEN' characters from either string */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
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
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strcpy)(char *__restrict buf,
                                  char const *__restrict src) {
	return (char *)libc_memcpy(buf, src, (libc_strlen(src) + 1) * sizeof(char));
}
#endif /* !LIBC_ARCH_HAVE_STRCPY */
#ifndef LIBC_ARCH_HAVE_STRNCPY
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_strnlen(src, buflen);
	libc_memcpy(buf, src, srclen * sizeof(char));
	libc_memset(buf + srclen, '\0', (buflen - srclen) * sizeof(char));
	return buf;
}
#endif /* !LIBC_ARCH_HAVE_STRNCPY */
#ifndef LIBC_ARCH_HAVE_STRCAT
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strcat)(char *__restrict buf,
                                  char const *__restrict src) {
	libc_memcpy(libc_strend(buf), src, (libc_strlen(src) + 1) * sizeof(char));
	return buf;
}
#endif /* !LIBC_ARCH_HAVE_STRCAT */
#ifndef LIBC_ARCH_HAVE_STRNCAT
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strncat)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_strnlen(src, buflen);
	char *dst = libc_strend(buf);
	libc_memcpy(dst, src, srclen * sizeof(char));
	dst[srclen] = '\0';
	return buf;
}
#endif /* !LIBC_ARCH_HAVE_STRNCAT */
#ifndef LIBC_ARCH_HAVE_STRCSPN
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc_strcspn)(char const *haystack,
                                   char const *reject) {
	char const *iter = haystack;
	while (*iter && !libc_strchr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRCSPN */
#ifndef LIBC_ARCH_HAVE_STRSPN
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc_strspn)(char const *haystack,
                                  char const *accept) {
	char const *iter = haystack;
	while (libc_strchr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRSPN */
#ifndef LIBC_ARCH_HAVE_STRPBRK
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
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
INTERN ATTR_SECTION(".text.crt.string.memory") NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_strtok)(char *string,
                                  char const *delim) {
	static char *save_ptr = NULL;
	return libc_strtok_r(string, delim, &save_ptr);
}
#ifndef LIBC_ARCH_HAVE_STRCOLL
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strcoll)(char const *s1,
                                   char const *s2) {
	return libc_strcmp(s1, s2);
}
#endif /* !LIBC_ARCH_HAVE_STRCOLL */
#ifndef LIBC_ARCH_HAVE_STRXFRM
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBCCALL libc_strxfrm)(char *dst,
                                   char const *__restrict src,
                                   size_t maxlen) {
	/* XXX: Implement me */
	size_t n = libc_strnlen(src, maxlen);
	libc_memcpy(dst, src, n * sizeof(char));
	return n;
}
#endif /* !LIBC_ARCH_HAVE_STRXFRM */
#ifndef __local_strerror_buf_defined
#define __local_strerror_buf_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(strerror_buf) char strerror_buf[64] = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_strerror_buf_defined */
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_strerror)(int errnum) {
	char *result = __NAMESPACE_LOCAL_SYM strerror_buf;
	char const *string;
	string = libc_strerror_s(errnum);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf) - 1] = '\0';
		libc_strncpy(result, string, COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf) - 1);
	} else {
		libc_sprintf(result, "Unknown error %d", errnum);
	}
	return result;
}
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRNLEN
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strnlen)(char const *__restrict string,
                                   size_t maxlen) {
	return (size_t)(libc_strnend(string, maxlen) - string);
}
#endif /* !LIBC_ARCH_HAVE_STRNLEN */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STPCPY
/* Same as `mempcpy(DST, SRC, (strlen(SRC) + 1) * sizeof(char)) - 1´ */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_stpcpy)(char *__restrict buf,
                                  char const *__restrict src) {
	return (char *)libc_mempcpy(buf, src, (libc_strlen(src) + 1) * sizeof(char)) - 1;
}
#endif /* !LIBC_ARCH_HAVE_STPCPY */
#ifndef LIBC_ARCH_HAVE_STPNCPY
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_stpncpy)(char *__restrict buf,
                                   char const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_strnlen(src, buflen);
	libc_memcpy(buf, src, srclen * sizeof(char));
	libc_memset(buf + srclen, '\0', (size_t)(buflen - srclen) * sizeof(char));
	return buf + srclen;
}
#endif /* !LIBC_ARCH_HAVE_STPNCPY */
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strcoll_l)(char const *s1,
                                     char const *s2,
                                     locale_t locale) {
	(void)locale;
	return libc_strcoll(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBCCALL libc_strxfrm_l)(char *dst,
                                     char const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
	(void)locale;
	return libc_strxfrm(dst, src, maxlen);
}
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_strerror_l)(int errnum,
                                      locale_t locale) {
	(void)locale;
	return libc_strerror(errnum);
}
INTERN ATTR_SECTION(".text.crt.string.memory.strsignal") ATTR_COLD ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_strsignal)(int signo) {
	static char strsignal_buf[64] = { 0 };
	char *result = strsignal_buf;
	char const *string;
	string = libc_strsignal_s(signo);
	if (string) {
		/* Copy the descriptor text. */
		result[COMPILER_LENOF(strsignal_buf) - 1] = '\0';
		libc_strncpy(result, string, COMPILER_LENOF(strsignal_buf) - 1);
	} else {
		libc_sprintf(result, "Unknown signal %d", signo);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strndup)(char const *__restrict string,
                                   size_t max_chars) {
	size_t resultsize = libc_strnlen(string, max_chars) * sizeof(char);
	char *result = (char *)libc_malloc(resultsize + sizeof(char));
	if likely(result) {
		*(char *)libc_mempcpy(result, string, resultsize) = '\0';
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strdup)(char const *__restrict string) {
	size_t resultsize = (libc_strlen(string) + 1) * sizeof(char);
	char *result = (char *)libc_malloc(resultsize);
	if likely(result)
		libc_memcpy(result, string, resultsize);
	return result;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF NONNULL((2, 3)) char *
NOTHROW_NCX(LIBCCALL libc_strtok_r)(char *string,
                                    char const *delim,
                                    char **__restrict save_ptr) {
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
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMRCHR
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_BYTES'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
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
#ifndef LIBC_ARCH_HAVE_RAWMEMCHR
/* Same as `memchr' with a search limit of `(size_t)-1' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
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
#ifndef LIBC_ARCH_HAVE_STRCHRNUL
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strchrnul)(char const *__restrict haystack,
                                     int needle) {
	for (; *haystack; ++haystack) {
		if (*haystack == (char)needle)
			break;
	}
	return (char *)haystack;
}
#endif /* !LIBC_ARCH_HAVE_STRCHRNUL */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_basename)(char const *filename) {
	char ch, *iter = (char *)filename, *result = NULL;
	if (!filename || !*filename)
		return (char *)filename;
	do {
		ch = *iter++;
#ifdef _WIN32
		if (ch == '/' || ch == '\\')
			result = iter;
#else /* _WIN32 */
		if (ch == '/')
			result = iter;
#endif /* !_WIN32 */
	} while (ch);
	if unlikely(!result)
		return (char *)filename; /* Path doesn't contain '/'. */
	if (*result)
		return result; /* Last character isn't a '/'. */
	iter = result;
#ifdef _WIN32
	while (iter != filename && (iter[-1] == '/' || iter[-1] == '\\'))
		--iter;
#else /* _WIN32 */
	while (iter != filename && iter[-1] == '/')
		--iter;
#endif /* !_WIN32 */
	if (iter == filename)
		return result-1; /* Only `'/'"-characters. */
	//*iter = '\0'; /* Trim all ending `'/'"-characters. */
#ifdef _WIN32
	while (iter != filename && (iter[-1] != '/' || iter[-1] != '\\'))
		--iter; /* Scan until the previous '/'. */
#else /* _WIN32 */
	while (iter != filename && iter[-1] != '/')
		--iter; /* Scan until the previous '/'. */
#endif /* !_WIN32 */
	return iter; /* Returns string after previous '/'. */
}
/* Same as `strstr', but ignore casing */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strcasestr)(char const *haystack,
                                      char const *needle) {
	for (; *haystack; ++haystack) {
		if (libc_strcasecmp(haystack, needle) == 0)
			return (char *)haystack;
	}
	return NULL;
}
#ifndef LIBC_ARCH_HAVE_MEMMEM
#include <features.h>
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
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
			return (int)vala - (int)valb;
		}
		++s1, ++s2;
	} while (c1);
	return 0;
}
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMPCPY
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempcpy)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_bytes) {
	byte_t *pdst = (byte_t *)dst;
	byte_t *psrc = (byte_t *)src;
	while (n_bytes--)
		*pdst++ = *psrc++;
	return pdst;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPY */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strfry)(char *__restrict string) {
	size_t i, count = libc_strlen(string);
	for (i = 0; i < count; ++i) {
		char temp;
		size_t j = libc_rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
	return string;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memfrob)(void *buf,
                                   size_t num_bytes) {
	byte_t *iter = (byte_t *)buf;
	while (num_bytes--)
		*iter++ ^= 42; /* -_-   yeah... */
	return buf;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strcasecmp_l)(char const *s1,
                                        char const *s2,
                                        locale_t locale) {
	(void)locale;
	return libc_strcasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncasecmp_l)(char const *s1,
                                         char const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libc_strncasecmp(s1, s2, maxlen);
}
#include <hybrid/__assert.h>
#ifndef __local_strerror_buf_defined
#define __local_strerror_buf_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(strerror_buf) char strerror_buf[64] = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_strerror_buf_defined */
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD ATTR_RETNONNULL NONNULL((2)) char *
NOTHROW_NCX(LIBCCALL libc_strerror_r)(int errnum,
                                      char *buf,
                                      size_t buflen) {
	char const *string;
	string = libc_strerror_s(errnum);
	if (!buf || !buflen) {
		buf    = __NAMESPACE_LOCAL_SYM strerror_buf;
		buflen = COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf);
	}
	if (string) {
		/* Copy the descriptor text. */
		size_t msg_len = libc_strlen(string) + 1;
		if (msg_len > buflen) {
			buf    = __NAMESPACE_LOCAL_SYM strerror_buf;
			buflen = COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf);
			if unlikely(msg_len > buflen) {
				msg_len      = buflen - 1;
				buf[msg_len] = '\0';
			}
		}
		libc_memcpyc(buf, string, msg_len, sizeof(char));
	} else {
again_unknown:
		if (libc_snprintf(buf, buflen, "Unknown error %d", errnum) >= buflen) {
			__hybrid_assert(buf != __NAMESPACE_LOCAL_SYM strerror_buf);
			buf    = __NAMESPACE_LOCAL_SYM strerror_buf;
			buflen = COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf);
			goto again_unknown;
		}
	}
	return buf;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.errno") ATTR_COLD NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc___xpg_strerror_r)(int errnum,
                                            char *buf,
                                            size_t buflen) {
	size_t msg_len;
	char const *string;
	string = libc_strerror_s(errnum);
	if (!buf)
		buflen = 0;
	if (!string) {
#ifdef EINVAL
		return EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	/* Copy the descriptor text. */
	msg_len = libc_strlen(string) + 1;
	if (msg_len > buflen) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	libc_memcpyc(buf, string, msg_len, sizeof(char));
	return EOK;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strsep)(char **__restrict stringp,
                                  char const *__restrict delim) {
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
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strcasecmp)(char const *s1,
                                      char const *s2) {
	char c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = libc_tolower(c1)) != (c2 = libc_tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncasecmp)(char const *s1,
                                       char const *s2,
                                       size_t maxlen) {
	char c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = libc_tolower(c1)) != (c2 = libc_tolower(c2))))
			return (int)((unsigned char)c1 - (unsigned char)c2);
	} while (c1);
	return 0;
}
#ifndef LIBC_ARCH_HAVE_FFS
#include <hybrid/__bit.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_ffs)(int i) {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((unsigned int)i);
}
#endif /* !LIBC_ARCH_HAVE_FFS */
#ifndef LIBC_ARCH_HAVE_FFSL
#include <hybrid/__bit.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_ffsl)(long i) {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((unsigned long)i);
}
#endif /* !LIBC_ARCH_HAVE_FFSL */
#ifndef LIBC_ARCH_HAVE_FFSLL
#include <hybrid/__bit.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_ffsll)(__LONGLONG i) {
	return (__STDC_INT_AS_SIZE_T)__hybrid_ffs((__ULONGLONG)i);
}
#endif /* !LIBC_ARCH_HAVE_FFSLL */
#ifndef LIBC_ARCH_HAVE_STRLCAT
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF NONNULL((1, 2)) size_t
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc_strlcpy)(char *__restrict dst,
                                   char const *__restrict src,
                                   size_t bufsize) {
	size_t result = libc_strlen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(dst, src, copy_size*sizeof(char));
	dst[copy_size] = '\0';
	return result;
}
#endif /* !LIBC_ARCH_HAVE_STRLCPY */
#ifndef LIBC_ARCH_HAVE_MEMCCPY
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF NONNULL((1, 2)) void *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memcpyw)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_words) {
	u16 *pdst = (u16 *)dst;
	u16 *psrc = (u16 *)src;
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPYW */
#ifndef LIBC_ARCH_HAVE_MEMPCPYW
/* Same as `memcpyw', but return `DST + N_WORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyw)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_words) {
	return (u16 *)libc_memcpyw(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPYW */
#ifndef LIBC_ARCH_HAVE_MEMCPYL
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memcpyl)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_dwords) {
	u32 *pdst = (u32 *)dst;
	u32 *psrc = (u32 *)src;
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPYL */
#ifndef LIBC_ARCH_HAVE_MEMPCPYL
/* Same as `memcpyl', but return `DST + N_DWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyl)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_dwords) {
	return (u32 *)libc_memcpyl(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPYL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEW
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memmovew)(void *dst,
                                    void const *src,
                                    size_t n_words) {
	u16 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u16 *)dst;
		psrc = (u16 *)src;
		while (n_words--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u16 *)dst + n_words;
		psrc = (u16 *)src + n_words;
		while (n_words--)
			*--pdst = *--psrc;
	}
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEW
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempmovew)(void *dst,
                                     void const *src,
                                     size_t n_words) {
	return (u16 *)libc_memmovew(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEL
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memmovel)(void *dst,
                                    void const *src,
                                    size_t n_dwords) {
	u32 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 *)src;
		while (n_dwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u32 *)dst + n_dwords;
		psrc = (u32 *)src + n_dwords;
		while (n_dwords--)
			*--pdst = *--psrc;
	}
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEL
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempmovel)(void *dst,
                                     void const *src,
                                     size_t n_dwords) {
	return (u32 *)libc_memmovel(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPW
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memmoveupw)(void *dst,
                                      void const *src,
                                      size_t n_words) {
	u16 *pdst, *psrc;
	pdst = (u16 *)dst + n_words;
	psrc = (u16 *)src + n_words;
	__hybrid_assertf(pdst >= psrc || !n_words, "%p < %p (count:%Iu)", dst, src, n_words);
	while (n_words--)
		*--pdst = *--psrc;
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNW
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memmovedownw)(void *dst,
                                        void const *src,
                                        size_t n_words) {
	u16 *pdst, *psrc;
	pdst = (u16 *)dst;
	psrc = (u16 *)src;
	__hybrid_assertf(pdst <= psrc || !n_words, "%p > %p (count:%Iu)", dst, src, n_words);
	while (n_words--)
		*pdst++ = *psrc++;
	return (u16 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPW
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST >= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveupw)(void *dst,
                                       void const *src,
                                       size_t n_words) {
	return (u16 *)libc_memmoveupw(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPW */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNW
/* Same as `memmovew', but return `DST + N_WORDS', rather than `DST' (assumes that `DST <= SRC || !N_WORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempmovedownw)(void *dst,
                                         void const *src,
                                         size_t n_words) {
	return (u16 *)libc_memmovedownw(dst, src, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNW */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPL
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memmoveupl)(void *dst,
                                      void const *src,
                                      size_t n_dwords) {
	u32 *pdst, *psrc;
	pdst = (u32 *)dst + n_dwords;
	psrc = (u32 *)src + n_dwords;
	__hybrid_assertf(pdst >= psrc || !n_dwords, "%p < %p (count:%Iu)", dst, src, n_dwords);
	while (n_dwords--)
		*--pdst = *--psrc;
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNL
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memmovedownl)(void *dst,
                                        void const *src,
                                        size_t n_dwords) {
	u32 *pdst, *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 *)src;
	__hybrid_assertf(pdst <= psrc || !n_dwords, "%p > %p (count:%Iu)", dst, src, n_dwords);
	while (n_dwords--)
		*pdst++ = *psrc++;
	return (u32 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPL
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST >= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveupl)(void *dst,
                                       void const *src,
                                       size_t n_dwords) {
	return (u32 *)libc_memmoveupl(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPL */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNL
/* Same as `memmovew', but return `DST + N_DWORDS', rather than `DST' (assumes that `DST <= SRC || !N_DWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempmovedownl)(void *dst,
                                         void const *src,
                                         size_t n_dwords) {
	return (u32 *)libc_memmovedownl(dst, src, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNL */
#ifndef LIBC_ARCH_HAVE_MEMSETW
/* Fill memory with a given word */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
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
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_mempsetw)(void *__restrict dst,
                                    uint16_t word,
                                    size_t n_words) {
	return (u16 *)libc_memsetw(dst, word, n_words) + n_words;
}
#endif /* !LIBC_ARCH_HAVE_MEMPSETW */
#ifndef LIBC_ARCH_HAVE_MEMSETL
/* Fill memory with a given dword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
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
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_mempsetl)(void *__restrict dst,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return (u32 *)libc_memsetl(dst, dword, n_dwords) + n_dwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPSETL */
#ifndef LIBC_ARCH_HAVE_MEMCMPW
/* Compare memory buffers and return the difference of the first non-matching word */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int16_t
NOTHROW_NCX(LIBCCALL libc_memcmpw)(void const *s1,
                                   void const *s2,
                                   size_t n_words) {
	s16 *p1 = (s16 *)s1;
	s16 *p2 = (s16 *)s2;
	s16 v1, v2;
	v1 = v2 = 0;
	while (n_words-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}
#endif /* !LIBC_ARCH_HAVE_MEMCMPW */
#ifndef LIBC_ARCH_HAVE_MEMCMPL
/* Compare memory buffers and return the difference of the first non-matching dword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int32_t
NOTHROW_NCX(LIBCCALL libc_memcmpl)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
	s32 *p1 = (s32 *)s1;
	s32 *p2 = (s32 *)s2;
	s32 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}
#endif /* !LIBC_ARCH_HAVE_MEMCMPL */
#ifndef LIBC_ARCH_HAVE_MEMCHRW
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memchrw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_words) {
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter == word)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCHRW */
#ifndef LIBC_ARCH_HAVE_MEMCHRL
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memchrl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_dwords) {
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter == dword)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCHRL */
#ifndef LIBC_ARCH_HAVE_MEMRCHRW
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_WORDS * 2'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrchrw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter == word)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRCHRW */
#ifndef LIBC_ARCH_HAVE_MEMRCHRL
/* Descendingly search for `NEEDLE', starting at `HAYSTACK + N_DWORDS * 4'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrchrl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter == dword)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRW
/* Same as `memchrw' with a search limit of `(size_t)-1 / 2' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrw)(void const *__restrict haystack,
                                      uint16_t word) {
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == word)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRL
/* Same as `memchrl' with a search limit of `(size_t)-1 / 4' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrl)(void const *__restrict haystack,
                                      uint32_t dword) {
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == dword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRW
/* Same as `memrchrw' without a search limit, starting at `(byte_t *)HAYSTACK - 2' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrw)(void const *__restrict haystack,
                                       uint16_t word) {
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter == word)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRL
/* Same as `memrchrl' without a search limit, starting at `(byte_t *)HAYSTACK - 4' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrl)(void const *__restrict haystack,
                                       uint32_t dword) {
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter == dword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRL */
#ifndef LIBC_ARCH_HAVE_MEMENDW
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memendw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_bytes) {
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == word)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMENDW */
#ifndef LIBC_ARCH_HAVE_MEMENDL
/* Same as `memchrl', but return `HAYSTACK + N_DWORDS * 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memendl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_bytes) {
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == dword)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMENDL */
#ifndef LIBC_ARCH_HAVE_MEMRENDW
/* Same as `memrchrw', but return `HAYSTACK - 2', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrendw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	u16 *result = (u16 *)haystack + n_words;
	for (;;) {
		--result;
		if unlikely(!n_words)
			break;
		if unlikely(*result == word)
			break;
		--n_words;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRENDW */
#ifndef LIBC_ARCH_HAVE_MEMRENDL
/* Same as `memrchrl', but return `HAYSTACK - 4', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrendl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	u32 *result = (u32 *)haystack + n_dwords;
	for (;;) {
		--result;
		if unlikely(!n_dwords)
			break;
		if unlikely(*result == dword)
			break;
		--n_dwords;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRENDL */
#ifndef LIBC_ARCH_HAVE_MEMLENW
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memlenw)(void const *__restrict haystack,
                                   uint16_t word,
                                   size_t n_words) {
	return (size_t)(libc_memendw(haystack, word, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLENW */
#ifndef LIBC_ARCH_HAVE_MEMLENL
/* Same as `memendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 4' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memlenl)(void const *__restrict haystack,
                                   uint32_t dword,
                                   size_t n_dwords) {
	return (size_t)(libc_memendl(haystack, dword, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLENL */
#ifndef LIBC_ARCH_HAVE_MEMRLENW
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 2' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrlenw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	return (size_t)(libc_memrendw(haystack, word, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLENW */
#ifndef LIBC_ARCH_HAVE_MEMRLENL
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 4' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrlenl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return (size_t)(libc_memrendl(haystack, dword, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENW
/* Same as `rawmemchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenw)(void const *__restrict haystack,
                                      uint16_t word) {
	return (size_t)(libc_rawmemchrw(haystack, word) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENL
/* Same as `rawmemchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenl)(void const *__restrict haystack,
                                      uint32_t dword) {
	return (size_t)(libc_rawmemchrl(haystack, dword) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENW
/* Same as `rawmemrchrw', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenw)(void const *__restrict haystack,
                                       uint16_t word) {
	return (size_t)(libc_rawmemrchrw(haystack, word) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENL
/* Same as `rawmemrchrl', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenl)(void const *__restrict haystack,
                                       uint32_t dword) {
	return (size_t)(libc_rawmemrchrl(haystack, dword) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENL */
#ifndef LIBC_ARCH_HAVE_MEMCPYQ
/* Copy memory between non-overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memcpyq)(void *__restrict dst,
                                   void const *__restrict src,
                                   size_t n_qwords) {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst = (u64 *)dst;
	u64 *psrc = (u64 *)src;
	while (n_qwords--)
		*pdst++ = *psrc++;
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst = (u32 *)dst;
	u32 *psrc = (u32 *)src;
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMPCPYQ
/* Same as `memcpyq', but return `DST + N_QWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempcpyq)(void *__restrict dst,
                                    void const *__restrict src,
                                    size_t n_qwords) {
	return (u64 *)libc_memcpyq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPCPYQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEQ
/* Move memory between potentially overlapping memory blocks. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memmoveq)(void *dst,
                                    void const *src,
                                    size_t n_qwords) {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u64 *)dst;
		psrc = (u64 *)src;
		while (n_qwords--)
			*pdst++ = *psrc++;
	} else {
		pdst = (u64 *)dst + n_qwords;
		psrc = (u64 *)src + n_qwords;
		while (n_qwords--)
			*--pdst = *--psrc;
	}
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst, *psrc;
	if (dst <= src) {
		pdst = (u32 *)dst;
		psrc = (u32 *)src;
		while (n_qwords--) {
			*pdst++ = *psrc++;
			*pdst++ = *psrc++;
		}
	} else {
		pdst = (u32 *)dst + (n_qwords * 2);
		psrc = (u32 *)src + (n_qwords * 2);
		while (n_qwords--) {
			*--pdst = *--psrc;
			*--pdst = *--psrc;
		}
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEQ
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveq)(void *__restrict dst,
                                     void const *__restrict src,
                                     size_t n_qwords) {
	return (u64 *)libc_memmoveq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUPQ
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST >= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memmoveupq)(void *dst,
                                      void const *src,
                                      size_t n_qwords) {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	pdst = (u64 *)dst + n_qwords;
	psrc = (u64 *)src + n_qwords;
	__hybrid_assertf(pdst >= psrc || !n_qwords, "%p < %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--)
		*--pdst = *--psrc;
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst, *psrc;
	pdst = (u32 *)dst + (n_qwords * 2);
	psrc = (u32 *)src + (n_qwords * 2);
	__hybrid_assertf(pdst >= psrc || !n_qwords, "%p < %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--) {
		*--pdst = *--psrc;
		*--pdst = *--psrc;
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWNQ
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memmovedownq)(void *dst,
                                        void const *src,
                                        size_t n_qwords) {
#if __SIZEOF_POINTER__ >= 8
	u64 *pdst, *psrc;
	pdst = (u64 *)dst;
	psrc = (u64 *)src;
	__hybrid_assertf(pdst <= psrc || !n_qwords, "%p > %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--)
		*pdst++ = *psrc++;
#else /* __SIZEOF_POINTER__ >= 8 */
	u32 *pdst, *psrc;
	pdst = (u32 *)dst;
	psrc = (u32 *)src;
	__hybrid_assertf(pdst <= psrc || !n_qwords, "%p > %p (count:%Iu)", dst, src, n_qwords);
	while (n_qwords--) {
		*pdst++ = *psrc++;
		*pdst++ = *psrc++;
	}
#endif /* __SIZEOF_POINTER__ < 8 */
	return (u64 *)dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUPQ
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST >= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempmoveupq)(void *__restrict dst,
                                       void const *__restrict src,
                                       size_t n_qwords) {
	return (u64 *)libc_memmoveupq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUPQ */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWNQ
/* Same as `memmovew', but return `DST + N_QWORDS', rather than `DST' (assumes that `DST <= SRC || !N_QWORDS') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempmovedownq)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_qwords) {
	return (u64 *)libc_memmovedownq(dst, src, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWNQ */
#ifndef LIBC_ARCH_HAVE_MEMSETQ
/* Fill memory with a given qword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
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
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_mempsetq)(void *__restrict dst,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return (u64 *)libc_memsetq(dst, qword, n_qwords) + n_qwords;
}
#endif /* !LIBC_ARCH_HAVE_MEMPSETQ */
#ifndef LIBC_ARCH_HAVE_MEMCMPQ
/* Compare memory buffers and return the difference of the first non-matching qword */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int64_t
NOTHROW_NCX(LIBCCALL libc_memcmpq)(void const *s1,
                                   void const *s2,
                                   size_t n_dwords) {
	s64 *p1 = (s64 *)s1;
	s64 *p2 = (s64 *)s2;
	s64 v1, v2;
	v1 = v2 = 0;
	while (n_dwords-- && ((v1 = *p1++) == (v2 = *p2++)));
	return v1 - v2;
}
#endif /* !LIBC_ARCH_HAVE_MEMCMPQ */
#ifndef LIBC_ARCH_HAVE_MEMCHRQ
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memchrq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_qwords) {
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter == (u64)qword)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMRCHRQ
/* Descendingly search for `NEEDLE', starting at `HAYSTACK+N_QWORDS'. - Return `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrchrq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter == qword)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHRQ
/* Same as `memchrq' with a search limit of `(size_t)-1 / 8' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemchrq)(void const *__restrict haystack,
                                      uint64_t qword) {
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter == qword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHRQ
/* Same as `memrchrq' without a search limit, starting at `(byte_t *)HAYSTACK - 8' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrchrq)(void const *__restrict haystack,
                                       uint64_t qword) {
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter == qword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMENDQ
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memendq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_bytes) {
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result == qword)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMENDQ */
#ifndef LIBC_ARCH_HAVE_MEMRENDQ
/* Same as `memrchrq', but return `HAYSTACK - 8', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrendq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	u64 *result = (u64 *)haystack + n_qwords;
	for (;;) {
		--result;
		if unlikely(!n_qwords)
			break;
		if unlikely(*result == qword)
			break;
		--n_qwords;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRENDQ */
#ifndef LIBC_ARCH_HAVE_MEMLENQ
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `N_QWORDS' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memlenq)(void const *__restrict haystack,
                                   uint64_t qword,
                                   size_t n_qwords) {
	return (size_t)(libc_memendq(haystack, qword, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLENQ */
#ifndef LIBC_ARCH_HAVE_MEMRLENQ
/* Same as `memrendq', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1 / 8' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrlenq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return (size_t)(libc_memrendq(haystack, qword, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMLENQ
/* Same as `rawmemchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlenq)(void const *__restrict haystack,
                                      uint64_t qword) {
	return (size_t)(libc_rawmemchrq(haystack, qword) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLENQ
/* Same as `rawmemrchrq', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlenq)(void const *__restrict haystack,
                                       uint64_t qword) {
	return (size_t)(libc_rawmemrchrq(haystack, qword) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLENQ */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_MEMXCHR
/* Same as `memchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) void *
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
/* Same as `rawmemchr', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_memrxend)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	byte_t *result = (byte_t *)haystack + n_bytes;
	while (n_bytes--) {
		if unlikely(*--result != (byte_t)needle)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXEND */
#ifndef LIBC_ARCH_HAVE_MEMXLEN
/* Same as `memlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memxlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return (size_t)((byte_t *)libc_memxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLEN */
#ifndef LIBC_ARCH_HAVE_MEMRXLEN
/* Same as `memrlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlen)(void const *__restrict haystack,
                                    int needle,
                                    size_t n_bytes) {
	return (size_t)((byte_t *)libc_memrxend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLEN
/* Same as `rawmemlen', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memxchrw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	u16 *hay_iter = (u16 *)haystack;
	for (; n_words--; ++hay_iter) {
		if unlikely(*hay_iter != word)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMXCHRW */
#ifndef LIBC_ARCH_HAVE_MEMXCHRL
/* Same as `memchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memxchrl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	u32 *hay_iter = (u32 *)haystack;
	for (; n_dwords--; ++hay_iter) {
		if unlikely(*hay_iter != dword)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMXCHRL */
#ifndef LIBC_ARCH_HAVE_MEMRXCHRW
/* Same as `memrchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
	u16 *iter = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--iter != word)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXCHRW */
#ifndef LIBC_ARCH_HAVE_MEMRXCHRL
/* Same as `memrchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
	u32 *iter = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--iter != dword)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMXCHRW
/* Same as `rawmemchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrw)(void const *__restrict haystack,
                                       uint16_t word) {
	u16 *iter = (u16 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != word)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMXCHRL
/* Same as `rawmemchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrl)(void const *__restrict haystack,
                                       uint32_t dword) {
	u32 *iter = (u32 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != dword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXCHRL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXCHRW
/* Same as `rawmemrchrw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrw)(void const *__restrict haystack,
                                        uint16_t word) {
	u16 *iter = (u16 *)haystack;
	for (;;) {
		if unlikely(*--iter != word)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXCHRW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXCHRL
/* Same as `rawmemrchrl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrl)(void const *__restrict haystack,
                                        uint32_t dword) {
	u32 *iter = (u32 *)haystack;
	for (;;) {
		if unlikely(*--iter != dword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXCHRL */
#ifndef LIBC_ARCH_HAVE_MEMXENDW
/* Same as `memendw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memxendw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_bytes) {
	u16 *result = (u16 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != word)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMXENDW */
#ifndef LIBC_ARCH_HAVE_MEMXENDL
/* Same as `memendl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memxendl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_bytes) {
	u32 *result = (u32 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != dword)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMXENDL */
#ifndef LIBC_ARCH_HAVE_MEMRXENDW
/* Same as `memrendw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc_memrxendw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
	u16 *result = (u16 *)haystack + n_words;
	while (n_words--) {
		if unlikely(*--result != word)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXENDW */
#ifndef LIBC_ARCH_HAVE_MEMRXENDL
/* Same as `memrendl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc_memrxendl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
	u32 *result = (u32 *)haystack + n_dwords;
	while (n_dwords--) {
		if unlikely(*--result != dword)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXENDL */
#ifndef LIBC_ARCH_HAVE_MEMXLENW
/* Same as `memlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memxlenw)(void const *__restrict haystack,
                                    uint16_t word,
                                    size_t n_words) {
	return (size_t)(libc_memxendw(haystack, word, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLENW */
#ifndef LIBC_ARCH_HAVE_MEMXLENL
/* Same as `memlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memxlenl)(void const *__restrict haystack,
                                    uint32_t dword,
                                    size_t n_dwords) {
	return (size_t)(libc_memxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLENL */
#ifndef LIBC_ARCH_HAVE_MEMRXLENW
/* Same as `memrlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenw)(void const *__restrict haystack,
                                     uint16_t word,
                                     size_t n_words) {
	return (size_t)(libc_memrxendw(haystack, word, n_words) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLENW */
#ifndef LIBC_ARCH_HAVE_MEMRXLENL
/* Same as `memrlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenl)(void const *__restrict haystack,
                                     uint32_t dword,
                                     size_t n_dwords) {
	return (size_t)(libc_memrxendl(haystack, dword, n_dwords) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLENW
/* Same as `rawmemlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenw)(void const *__restrict haystack,
                                       uint16_t word) {
	return (size_t)(libc_rawmemxchrw(haystack, word) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLENL
/* Same as `rawmemlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenl)(void const *__restrict haystack,
                                       uint32_t dword) {
	return (size_t)(libc_rawmemxchrl(haystack, dword) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXLENL */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXLENW
/* Same as `rawmemrlenw', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenw)(void const *__restrict haystack,
                                        uint16_t word) {
	return (size_t)(libc_rawmemrxchrw(haystack, word) - (u16 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXLENW */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXLENL
/* Same as `rawmemrlenl', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenl)(void const *__restrict haystack,
                                        uint32_t dword) {
	return (size_t)(libc_rawmemrxchrl(haystack, dword) - (u32 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXLENL */
#ifndef LIBC_ARCH_HAVE_MEMXCHRQ
/* Same as `memchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memxchrq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	u64 *hay_iter = (u64 *)haystack;
	for (; n_qwords--; ++hay_iter) {
		if unlikely(*hay_iter != (u64)qword)
			return hay_iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMXCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMRXCHRQ
/* Same as `memrchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrxchrq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
	u64 *iter = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--iter != qword)
			return iter;
	}
	return NULL;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMXCHRQ
/* Same as `rawmemchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemxchrq)(void const *__restrict haystack,
                                       uint64_t qword) {
	u64 *iter = (u64 *)haystack;
	for (;; ++iter) {
		if unlikely(*iter != qword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXCHRQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXCHRQ
/* Same as `rawmemrchrq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_rawmemrxchrq)(void const *__restrict haystack,
                                        uint64_t qword) {
	u64 *iter = (u64 *)haystack;
	for (;;) {
		if unlikely(*--iter != qword)
			break;
	}
	return iter;
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXCHRQ */
#ifndef LIBC_ARCH_HAVE_MEMXENDQ
/* Same as `memendq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memxendq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_bytes) {
	u64 *result = (u64 *)haystack;
	for (; n_bytes--; ++result) {
		if unlikely(*result != qword)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMXENDQ */
#ifndef LIBC_ARCH_HAVE_MEMRXENDQ
/* Same as `memrendq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc_memrxendq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
	u64 *result = (u64 *)haystack + n_qwords;
	while (n_qwords--) {
		if unlikely(*--result != qword)
			break;
	}
	return result;
}
#endif /* !LIBC_ARCH_HAVE_MEMRXENDQ */
#ifndef LIBC_ARCH_HAVE_MEMXLENQ
/* Same as `memlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memxlenq)(void const *__restrict haystack,
                                    uint64_t qword,
                                    size_t n_qwords) {
	return (size_t)(libc_memxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMXLENQ */
#ifndef LIBC_ARCH_HAVE_MEMRXLENQ
/* Same as `memrlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrxlenq)(void const *__restrict haystack,
                                     uint64_t qword,
                                     size_t n_qwords) {
	return (size_t)(libc_memrxendq(haystack, qword, n_qwords) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRXLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMXLENQ
/* Same as `rawmemlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemxlenq)(void const *__restrict haystack,
                                       uint64_t qword) {
	return (size_t)(libc_rawmemxchrq(haystack, qword) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMXLENQ */
#ifndef LIBC_ARCH_HAVE_RAWMEMRXLENQ
/* Same as `rawmemrlenq', but search for non-matching locations. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrxlenq)(void const *__restrict haystack,
                                        uint64_t qword) {
	return (size_t)(libc_rawmemrxchrq(haystack, qword) - (u64 *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRXLENQ */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMMOVEUP
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memmoveup)(void *dst,
                                     void const *src,
                                     size_t n_bytes) {
	byte_t *pdst, *psrc;
	pdst = (byte_t *)dst + n_bytes;
	psrc = (byte_t *)src + n_bytes;
	__hybrid_assertf(pdst >= psrc || !n_bytes, "%p < %p (count:%Iu)", dst, src, n_bytes);
	while (n_bytes--)
		*--pdst = *--psrc;
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMMOVEDOWN
#include <hybrid/__assert.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_memmovedown)(void *dst,
                                       void const *src,
                                       size_t n_bytes) {
	byte_t *pdst, *psrc;
	pdst = (byte_t *)dst;
	psrc = (byte_t *)src;
	__hybrid_assertf(pdst <= psrc || !n_bytes, "%p > %p (count:%Iu)", dst, src, n_bytes);
	while (n_bytes--)
		*pdst++ = *psrc++;
	return dst;
}
#endif /* !LIBC_ARCH_HAVE_MEMMOVEDOWN */
#ifndef __KERNEL__
#include <hybrid/host.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
#include <hybrid/host.h>
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
#include <hybrid/host.h>
/* Move memory between potentially overlapping memory blocks
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
#include <hybrid/host.h>
/* Same as `memmovec', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
#include <hybrid/host.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
#include <hybrid/host.h>
/* Same as `memmoveupc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST >= SRC || !ELEM_COUNT || !ELEM_SIZE') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
#include <hybrid/host.h>
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
#include <hybrid/host.h>
/* Same as `memmovedownc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
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
/* Same as `STR + strlen(STR)' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strend)(char const *__restrict string) {
	while (*string)
		++string;
	return (char *)string;
}
#endif /* !LIBC_ARCH_HAVE_STREND */
#ifndef LIBC_ARCH_HAVE_STRNEND
/* Same as `STR + strnlen(STR, MAX_CHARS)' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnend)(char const *__restrict string,
                                   size_t maxlen) {
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char *)string;
}
#endif /* !LIBC_ARCH_HAVE_STRNEND */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_STRNCHR
/* Same as `strchr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
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
/* Same as `strrchr', but don't exceed `MAX_CHARS' characters. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char *
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
/* Same as `strrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
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
/* Same as `strnchr', but return `strnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnchrnul)(char const *__restrict haystack,
                                      int needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (unsigned char)*haystack != (unsigned char)needle; ++haystack)
		;
	return (char *)haystack;
}
#endif /* !LIBC_ARCH_HAVE_STRNCHRNUL */
#ifndef LIBC_ARCH_HAVE_STRNRCHRNUL
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char *
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
/* Same as `strchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_stroff)(char const *__restrict haystack,
                                  int needle) {
	return (size_t)(libc_strchrnul(haystack, needle) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STROFF */
#ifndef LIBC_ARCH_HAVE_STRROFF
/* Same as `strrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strroff)(char const *__restrict haystack,
                                   int needle) {
	return (size_t)(libc_strrchrnul(haystack, needle) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRROFF */
#ifndef LIBC_ARCH_HAVE_STRNOFF
/* Same as `strnchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strnoff)(char const *__restrict haystack,
                                   int needle,
                                   size_t maxlen) {
	return (size_t)(libc_strnchrnul(haystack, needle, maxlen) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRNOFF */
#ifndef LIBC_ARCH_HAVE_STRNROFF
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_strnroff)(char const *__restrict haystack,
                                    int needle,
                                    size_t maxlen) {
	return (size_t)(libc_strnrchrnul(haystack, needle, maxlen) - haystack);
}
#endif /* !LIBC_ARCH_HAVE_STRNROFF */
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMPSET
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_mempset)(void *__restrict dst,
                                   int byte,
                                   size_t n_bytes) {
	return (void *)((byte_t *)libc_memset(dst, byte, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPSET */
#ifndef LIBC_ARCH_HAVE_MEMPMOVE
/* Same as `memmove', but return `DST + N_BYTES', rather than `DST' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempmove)(void *dst,
                                    void const *src,
                                    size_t n_bytes) {
	return (void *)((byte_t *)libc_memmove(dst, src, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVE */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEUP
/* Same as `memmoveup', but return `DST + N_BYTES', rather than `DST' (assumes that `DST >= SRC || !N_BYTES') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempmoveup)(void *dst,
                                      void const *src,
                                      size_t n_bytes) {
	return (void *)((byte_t *)libc_memmoveup(dst, src, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEUP */
#ifndef LIBC_ARCH_HAVE_MEMPMOVEDOWN
/* Same as `memmovedown', but return `DST + N_BYTES', rather than `DST' (assumes that `DST <= SRC || !N_BYTES') */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc_mempmovedown)(void *dst,
                                        void const *src,
                                        size_t n_bytes) {
	return (void *)((byte_t *)libc_memmovedown(dst, src, n_bytes) + n_bytes);
}
#endif /* !LIBC_ARCH_HAVE_MEMPMOVEDOWN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRCHR
/* Same as `memrchr' without a search limit, starting at `HAYSTACK - 1' */
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
/* Same as `memchr', but return `HAYSTACK + N_BYTES', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
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
/* Same as `memrchr', but return `HAYSTACK - 1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
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
/* Same as `memend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `n_bytes' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memlen)(void const *__restrict haystack,
                                  int needle,
                                  size_t n_bytes) {
	return (size_t)((byte_t *)libc_memend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMLEN */
#ifndef LIBC_ARCH_HAVE_MEMRLEN
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `(size_t)-1' if the given `NEEDLE' wasn't found */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_memrlen)(void const *__restrict haystack,
                                   int needle,
                                   size_t n_bytes) {
	return (size_t)((byte_t *)libc_memrend(haystack, needle, n_bytes) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_MEMRLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMLEN
/* Same as `rawmemchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemlen)(void const *__restrict haystack,
                                     int needle) {
	return (size_t)((byte_t *)libc_rawmemchr(haystack, needle) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMLEN */
#ifndef LIBC_ARCH_HAVE_RAWMEMRLEN
/* Same as `rawmemrchr', but return the offset from `HAYSTACK', rather than the actual address. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc_rawmemrlen)(void const *__restrict haystack,
                                      int needle) {
	return (size_t)((byte_t *)libc_rawmemrchr(haystack, needle) - (byte_t *)haystack);
}
#endif /* !LIBC_ARCH_HAVE_RAWMEMRLEN */
#ifndef __KERNEL__
#ifndef LIBC_ARCH_HAVE_MEMRMEM
#include <features.h>
/* Return the last address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
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
	marker = *(uint8_t *)needle;
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
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
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
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
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
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
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
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_memcasecmp)(void const *s1,
                                      void const *s2,
                                      size_t n_bytes) {
	byte_t *p1 = (byte_t *)s1;
	byte_t *p2 = (byte_t *)s2;
	byte_t v1, v2;
	v1 = v2 = 0;
	while (n_bytes-- &&
	    (((v1 = *p1++) == (v2 = *p2++)) ||
	     ((v1 = libc_tolower(v1)) == (v2 = libc_tolower(v2)))));
	return (int)v1 - (int)v2;
}
#include <features.h>
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
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
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_memcasecmp_l)(void const *s1,
                                        void const *s2,
                                        size_t n_bytes,
                                        locale_t locale) {
	(void)locale;
	return libc_memcasecmp(s1, s2, n_bytes);
}
#include <features.h>
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored using the given `locale' (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) void *
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
	marker       = libc_tolower_l(*(byte_t *)needle, locale);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || libc_tolower_l(b, locale) == marker)
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
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_strcasestr_l)(char const *haystack,
                                        char const *needle,
                                        locale_t locale) {
	for (; *haystack; ++haystack) {
		if (libc_strcasecmp_l(haystack, needle, locale) == 0)
			return (char *)haystack;
	}
	return NULL;
}
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *
NOTHROW_NCX(LIBCCALL libc_vstrdupf)(char const *__restrict format,
                                    va_list args) {
	char *result;
	return libc_vasprintf(&result, format, args) >= 0 ? result : 0;
}
/* Print the given `FORMAT' into a newly allocated, heap-allocated string */
INTERN ATTR_SECTION(".text.crt.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_LIBC_PRINTF(1, 0) char *
NOTHROW_NCX(VLIBCCALL libc_strdupf)(char const *__restrict format,
                                    ...) {
	char * result;
	va_list args;
	va_start(args, format);
	result = libc_vstrdupf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_wildstrcmp)(char const *pattern,
                                      char const *string) {
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
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp)(char const *pattern,
                                          char const *string) {
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcmp)(char const *s1,
                                        char const *s2) {
	return libc_fuzzy_memcmp(s1, libc_strlen(s1), s2, libc_strlen(s2));
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncmp)(char const *s1,
                                         size_t s1_maxlen,
                                         char const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmp(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen));
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp)(char const *s1,
                                            char const *s2) {
	return libc_fuzzy_memcasecmp(s1, libc_strlen(s1), s2, libc_strlen(s2));
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp)(char const *s1,
                                             size_t s1_maxlen,
                                             char const *s2,
                                             size_t s2_maxlen) {
	return libc_fuzzy_memcasecmp(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen));
}
#include <parts/malloca.h>
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
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
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
#include <parts/malloca.h>
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
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
			cost  = c1 != c2 && libc_tolower(c1) != libc_tolower(c2);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strcasecmp_l)(char const *s1,
                                              char const *s2,
                                              locale_t locale) {
	return libc_fuzzy_memcasecmp_l(s1, libc_strlen(s1), s2, libc_strlen(s2), locale);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_strncasecmp_l)(char const *s1,
                                               size_t s1_maxlen,
                                               char const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libc_fuzzy_memcasecmp_l(s1, libc_strnlen(s1, s1_maxlen), s2, libc_strnlen(s2, s2_maxlen), locale);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_wildstrcasecmp_l)(char const *pattern,
                                            char const *string,
                                            locale_t locale) {
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
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
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
			cost  = c1 != c2 && libc_tolower_l(c1, locale) != libc_tolower_l(c2, locale);
			cost += v0[j];
			temp  = v1[j] + 1;
			if (cost > temp)
				cost = temp;
			temp  = v0[j + 1] + 1;
			if (cost > temp)
				cost = temp;
			v1[j + 1] = cost;
		}
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_bytes, sizeof(size_t));
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
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
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_words, sizeof(size_t));
	}
	temp = v1[s2_words];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
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
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_dwords, sizeof(size_t));
	}
	temp = v1[s2_dwords];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
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
		libc_memcpyc((u8 *)v0, (u8 *)v1, s2_qwords, sizeof(size_t));
	}
	temp = v1[s2_qwords];
	__freea(v1);
	__freea(v0);
	return temp;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncoll)(char const *s1,
                                    char const *s2,
                                    size_t maxlen) {
	return libc_strncmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strcasecoll)(char const *s1,
                                       char const *s2) {
	return libc_strcasecmp(s1, s2);
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncasecoll)(char const *s1,
                                        char const *s2,
                                        size_t maxlen) {
	return libc_strncasecmp(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnrev)(char *__restrict str,
                                   size_t maxlen) {
	return (char *)libc_memrev(str, libc_strnlen(str, maxlen));
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnlwr)(char *__restrict str,
                                   size_t maxlen) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnupr)(char *__restrict str,
                                   size_t maxlen) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncoll_l)(char const *s1,
                                      char const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	(void)locale;
	return libc_strncoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strcasecoll_l)(char const *s1,
                                         char const *s2,
                                         locale_t locale) {
	return libc_strcasecmp_l(s1, s2, locale);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_strncasecoll_l)(char const *s1,
                                          char const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	(void)locale;
	return libc_strncasecoll(s1, s2, maxlen);
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strlwr_l)(char *__restrict str,
                                    locale_t locale) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strupr_l)(char *__restrict str,
                                    locale_t locale) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnlwr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnupr_l)(char *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper_l(ch, locale);
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
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
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strlwr)(char *__restrict str) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strupr)(char *__restrict str) {
	char *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper(ch);
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strset)(char *__restrict str,
                                  int ch) {
	char *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strnset)(char *__restrict str,
                                   int ch,
                                   size_t maxlen) {
	char *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char)ch;
	return str;
}
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_strrev)(char *__restrict str) {
	return (char *)libc_memrev(str, libc_strlen(str));
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__strset_s)(char *dst,
                                     size_t dstsize,
                                     int ch) {
	char *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __EINVAL;
	}
	__libc_memsetc(p, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_memcpy_s)(void *dst,
                                    rsize_t dstlength,
                                    void const *src,
                                    rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, __SIZEOF_CHAR__);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	__libc_memcpyc(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_memmove_s)(void *dst,
                                     rsize_t dstlength,
                                     void const *src,
                                     rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	__libc_memmovec(dst, src, srclength, __SIZEOF_CHAR__);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBCCALL libc_strcpy_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
	char *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBCCALL libc_strcat_s)(char *dst,
                                    size_t dstsize,
                                    char const *src) {
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
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBCCALL libc_strncat_s)(char *dst,
                                     rsize_t dstsize,
                                     const char *src,
                                     rsize_t maxlen) {
	char *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
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
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
#include <parts/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBCCALL libc_strncpy_s)(char *dst,
                                     size_t dstsize,
                                     char const *src,
                                     size_t maxlen) {
	char *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
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
		__libc_memsetc(dst, 0, dstsize, __SIZEOF_CHAR__);
		return __ERANGE;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
#ifndef __local_strerror_buf_defined
#define __local_strerror_buf_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(strerror_buf) char strerror_buf[64] = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_strerror_buf_defined */
INTERN ATTR_SECTION(".text.crt.dos.errno") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc__strerror)(char const *message) {
	libc__strerror_s(__NAMESPACE_LOCAL_SYM strerror_buf,
	            COMPILER_LENOF(__NAMESPACE_LOCAL_SYM strerror_buf),
	            message);
	return __NAMESPACE_LOCAL_SYM strerror_buf;
}
#include <bits/types.h>
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.errno") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc__strerror_s)(char *__restrict buf,
                                       size_t buflen,
                                       char const *message) {
	char const *string;
	size_t reqlen;
	errno_t eno = __libc_geterrno();
	string = libc_strerror_s(eno);
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
	if (reqlen > buflen) {
#ifdef ERANGE
		return ERANGE;
#else /* ERANGE */
		return 1;
#endif /* !ERANGE */
	}
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") errno_t
NOTHROW_NCX(LIBCCALL libc__strlwr_s)(char *buf,
                                     size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower(ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.static.memory") errno_t
NOTHROW_NCX(LIBCCALL libc__strupr_s)(char *buf,
                                     size_t buflen) {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = libc_toupper(ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBCCALL libc__strlwr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_strnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = libc_tolower_l(ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.unicode.locale.memory") errno_t
NOTHROW_NCX(LIBCCALL libc__strupr_s_l)(char *buf,
                                       size_t buflen,
                                       locale_t locale) {
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
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.string.memory") errno_t
NOTHROW_NCX(LIBCCALL libc__strnset_s)(char *__restrict buf,
                                      size_t buflen,
                                      int ch,
                                      size_t maxlen) {
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
		*iter++ = (wchar_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, __SIZEOF_CHAR__);
		return __EINVAL;
	}
	__libc_memsetc(iter, 0, remaining, __SIZEOF_CHAR__);
	return 0;
}
/* Search for `needle...+=strlen(needle)' within `haystack...+=strnlen(haystack, haystack_maxlen)'
 * If found, return a pointer to its location within `str', else return `NULL'
 * This function originates from BSD, but is also provided as a KOS extension */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char *
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
#include <asm/stat.h>
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
INTERN ATTR_SECTION(".text.crt.bsd.strstat") NONNULL((2)) void
NOTHROW_NCX(LIBCCALL libc_strmode)(mode_t mode,
                                   char p[12]) {
	char ch;
	/* First character: File type */
	ch = '?';
#ifdef S_IFMT
	switch (mode & S_IFMT) {
#ifdef S_IFDIR
	case S_IFDIR:  ch = 'd'; break;
#endif /* S_IFDIR */
#ifdef S_IFCHR
	case S_IFCHR:  ch = 'c'; break;
#endif /* S_IFCHR */
#ifdef S_IFBLK
	case S_IFBLK:  ch = 'b'; break;
#endif /* S_IFBLK */
#ifdef S_IFREG
	case S_IFREG:  ch = '-'; break;
#endif /* S_IFREG */
#ifdef S_IFLNK
	case S_IFLNK:  ch = 'l'; break;
#endif /* S_IFLNK */
#ifdef S_IFSOCK
	case S_IFSOCK: ch = 's'; break;
#endif /* S_IFSOCK */
#ifdef S_IFIFO
	case S_IFIFO:  ch = 'p'; break; /* p=pipe */
#endif /* S_IFIFO */
	default: break;
	}
#endif /* S_IFMT */
	*p++ = ch;

#ifdef S_IRUSR
	*p++ = mode & S_IRUSR ? 'r' : '-';
#else /* S_IRUSR */
	*p++ = '-';
#endif /* !S_IRUSR */

#ifdef S_IWUSR
	*p++ = mode & S_IWUSR ? 'w' : '-';
#else /* S_IWUSR */
	*p++ = '-';
#endif /* !S_IWUSR */

#if defined(S_IXUSR) && defined(S_ISUID)
	switch (mode & (S_IXUSR | S_ISUID)) {
	case 0:                 ch = '-'; break;
	case S_IXUSR:           ch = 'x'; break;
	case S_ISUID:           ch = 'S'; break;
	case S_IXUSR | S_ISUID: ch = 's'; break;
	default: __builtin_unreachable();
	}
#elif defined(S_IXUSR)
	ch = mode & S_IXUSR ? 'x' : '-';
#elif defined(S_ISUID)
	ch = mode & S_ISUID ? 'S' : '-';
#else /* S_IWUSR */
	ch = '-';
#endif /* !S_IWUSR */
	*p++ = ch;

#ifdef S_IRGRP
	*p++ = mode & S_IRGRP ? 'r' : '-';
#else /* S_IRGRP */
	*p++ = '-';
#endif /* !S_IRGRP */

#ifdef S_IWGRP
	*p++ = mode & S_IWGRP ? 'w' : '-';
#else /* S_IWGRP */
	*p++ = '-';
#endif /* !S_IWGRP */

#if defined(S_IXGRP) && defined(S_ISGID)
	switch (mode & (S_IXGRP | S_ISGID)) {
	case 0:                 ch = '-'; break;
	case S_IXGRP:           ch = 'x'; break;
	case S_ISGID:           ch = 'S'; break;
	case S_IXGRP | S_ISGID: ch = 's'; break;
	default: __builtin_unreachable();
	}
#elif defined(S_IXGRP)
	ch = mode & S_IXGRP ? 'x' : '-';
#elif defined(S_ISGID)
	ch = mode & S_ISGID ? 'S' : '-';
#else /* S_IWUSR */
	ch = '-';
#endif /* !S_IWUSR */
	*p++ = ch;

#ifdef S_IROTH
	*p++ = mode & S_IROTH ? 'r' : '-';
#else /* S_IROTH */
	*p++ = '-';
#endif /* !S_IROTH */

#ifdef S_IWOTH
	*p++ = mode & S_IWOTH ? 'w' : '-';
#else /* S_IWOTH */
	*p++ = '-';
#endif /* !S_IWOTH */

#if defined(S_IXOTH) && defined(S_ISVTX)
	switch (mode & (S_IXOTH | S_ISVTX)) {
	case 0:                 ch = '-'; break;
	case S_IXOTH:           ch = 'x'; break;
	case S_ISVTX:           ch = 'T'; break;
	case S_IXOTH | S_ISVTX: ch = 't'; break;
	default: __builtin_unreachable();
	}
#elif defined(S_IXOTH)
	ch = mode & S_IXOTH ? 'x' : '-';
#elif defined(S_ISVTX)
	ch = mode & S_ISVTX ? 'T' : '-';
#else /* S_IWUSR */
	ch = '-';
#endif /* !S_IWUSR */
	*p++ = ch;

	/* Always space in this implementation */
	*p++ = ' ';

	/* NUL-terminate */
	*p = '\0';
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
DEFINE_PUBLIC_ALIAS(bcmp, libc_memcmp);
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
DEFINE_PUBLIC_ALIAS(strchr, libc_strchr);
#endif /* !LIBC_ARCH_HAVE_STRCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRRCHR)
DEFINE_PUBLIC_ALIAS(strrchr, libc_strrchr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRRCHR */
#ifndef LIBC_ARCH_HAVE_STRCMP
DEFINE_PUBLIC_ALIAS(strcmp, libc_strcmp);
#endif /* !LIBC_ARCH_HAVE_STRCMP */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCMP)
DEFINE_PUBLIC_ALIAS(strncmp, libc_strncmp);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCMP */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRSTR)
DEFINE_PUBLIC_ALIAS(strstr, libc_strstr);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRSTR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCPY)
DEFINE_PUBLIC_ALIAS(strcpy, libc_strcpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRNCPY)
DEFINE_PUBLIC_ALIAS(strncpy, libc_strncpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRNCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCAT)
DEFINE_PUBLIC_ALIAS(strcat, libc_strcat);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCAT */
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
DEFINE_PUBLIC_ALIAS(strerror, libc_strerror);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_STRNLEN
DEFINE_PUBLIC_ALIAS(strnlen, libc_strnlen);
#endif /* !LIBC_ARCH_HAVE_STRNLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STPCPY)
DEFINE_PUBLIC_ALIAS(__stpcpy, libc_stpcpy);
DEFINE_PUBLIC_ALIAS(stpcpy, libc_stpcpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STPCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STPNCPY)
DEFINE_PUBLIC_ALIAS(__stpncpy, libc_stpncpy);
DEFINE_PUBLIC_ALIAS(stpncpy, libc_stpncpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STPNCPY */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_strcoll_l, libc_strcoll_l);
DEFINE_PUBLIC_ALIAS(__strcoll_l, libc_strcoll_l);
DEFINE_PUBLIC_ALIAS(strcoll_l, libc_strcoll_l);
DEFINE_PUBLIC_ALIAS(_strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_ALIAS(__strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_ALIAS(strxfrm_l, libc_strxfrm_l);
DEFINE_PUBLIC_ALIAS(strerror_l, libc_strerror_l);
DEFINE_PUBLIC_ALIAS(strsignal, libc_strsignal);
DEFINE_PUBLIC_ALIAS(__strndup, libc_strndup);
DEFINE_PUBLIC_ALIAS(strndup, libc_strndup);
DEFINE_PUBLIC_ALIAS(_strdup, libc_strdup);
DEFINE_PUBLIC_ALIAS(__strdup, libc_strdup);
DEFINE_PUBLIC_ALIAS(strdup, libc_strdup);
DEFINE_PUBLIC_ALIAS(strtok_s, libc_strtok_r);
DEFINE_PUBLIC_ALIAS(__strtok_r, libc_strtok_r);
DEFINE_PUBLIC_ALIAS(strtok_r, libc_strtok_r);
#endif /* !__KERNEL__ */
#ifndef LIBC_ARCH_HAVE_MEMRCHR
DEFINE_PUBLIC_ALIAS(memrchr, libc_memrchr);
#endif /* !LIBC_ARCH_HAVE_MEMRCHR */
#ifndef LIBC_ARCH_HAVE_RAWMEMCHR
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__rawmemchr, libc_rawmemchr);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(rawmemchr, libc_rawmemchr);
#endif /* !LIBC_ARCH_HAVE_RAWMEMCHR */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRCHRNUL)
DEFINE_PUBLIC_ALIAS(strchrnul, libc_strchrnul);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRCHRNUL */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(basename, libc_basename);
DEFINE_PUBLIC_ALIAS(__strcasestr, libc_strcasestr);
DEFINE_PUBLIC_ALIAS(strcasestr, libc_strcasestr);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMMEM)
DEFINE_PUBLIC_ALIAS(memmem, libc_memmem);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_MEMMEM */
#ifndef __KERNEL__
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
DEFINE_PUBLIC_ALIAS(_stricmp_l, libc_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(__strcasecmp_l, libc_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(strcasecmp_l, libc_strcasecmp_l);
DEFINE_PUBLIC_ALIAS(_strnicmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(_strncmpi_l, libc_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(__strncasecmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(strncasecmp_l, libc_strncasecmp_l);
DEFINE_PUBLIC_ALIAS(__strerror_r, libc_strerror_r);
DEFINE_PUBLIC_ALIAS(strerror_r, libc_strerror_r);
DEFINE_PUBLIC_ALIAS(__xpg_strerror_r, libc___xpg_strerror_r);
DEFINE_PUBLIC_ALIAS(strsep, libc_strsep);
DEFINE_PUBLIC_ALIAS(_stricmp, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(_strcmpi, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(stricmp, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(strcmpi, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(__strcasecmp, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(strcasecmp, libc_strcasecmp);
DEFINE_PUBLIC_ALIAS(_strnicmp, libc_strncasecmp);
DEFINE_PUBLIC_ALIAS(strnicmp, libc_strncasecmp);
DEFINE_PUBLIC_ALIAS(_strncmpi, libc_strncasecmp);
DEFINE_PUBLIC_ALIAS(strncmpi, libc_strncasecmp);
DEFINE_PUBLIC_ALIAS(strncasecmp, libc_strncasecmp);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_FFS)
DEFINE_PUBLIC_ALIAS(__ffs, libc_ffs);
DEFINE_PUBLIC_ALIAS(ffs, libc_ffs);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_FFS */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_FFSL)
DEFINE_PUBLIC_ALIAS(ffsl, libc_ffsl);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_FFSL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_FFSLL)
DEFINE_PUBLIC_ALIAS(ffsll, libc_ffsll);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_FFSLL */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRLCAT)
DEFINE_PUBLIC_ALIAS(strlcat, libc_strlcat);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRLCAT */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_STRLCPY)
DEFINE_PUBLIC_ALIAS(strlcpy, libc_strlcpy);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_STRLCPY */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_MEMCCPY)
DEFINE_PUBLIC_ALIAS(_memccpy, libc_memccpy);
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
DEFINE_PUBLIC_ALIAS(_memicmp, libc_memcasecmp);
DEFINE_PUBLIC_ALIAS(memcasecmp, libc_memcasecmp);
DEFINE_PUBLIC_ALIAS(memcasemem, libc_memcasemem);
DEFINE_PUBLIC_ALIAS(_memicmp_l, libc_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(memcasecmp_l, libc_memcasecmp_l);
DEFINE_PUBLIC_ALIAS(memcasemem_l, libc_memcasemem_l);
DEFINE_PUBLIC_ALIAS(strcasestr_l, libc_strcasestr_l);
DEFINE_PUBLIC_ALIAS(vstrdupf, libc_vstrdupf);
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
DEFINE_PUBLIC_ALIAS(_strncoll, libc_strncoll);
DEFINE_PUBLIC_ALIAS(strncoll, libc_strncoll);
DEFINE_PUBLIC_ALIAS(_stricoll, libc_strcasecoll);
DEFINE_PUBLIC_ALIAS(strcasecoll, libc_strcasecoll);
DEFINE_PUBLIC_ALIAS(_strnicoll, libc_strncasecoll);
DEFINE_PUBLIC_ALIAS(strncasecoll, libc_strncasecoll);
DEFINE_PUBLIC_ALIAS(strnrev, libc_strnrev);
DEFINE_PUBLIC_ALIAS(strnlwr, libc_strnlwr);
DEFINE_PUBLIC_ALIAS(strnupr, libc_strnupr);
DEFINE_PUBLIC_ALIAS(_strncoll_l, libc_strncoll_l);
DEFINE_PUBLIC_ALIAS(strncoll_l, libc_strncoll_l);
DEFINE_PUBLIC_ALIAS(_stricoll_l, libc_strcasecoll_l);
DEFINE_PUBLIC_ALIAS(strcasecoll_l, libc_strcasecoll_l);
DEFINE_PUBLIC_ALIAS(_strnicoll_l, libc_strncasecoll_l);
DEFINE_PUBLIC_ALIAS(strncasecoll_l, libc_strncasecoll_l);
DEFINE_PUBLIC_ALIAS(_strlwr_l, libc_strlwr_l);
DEFINE_PUBLIC_ALIAS(strlwr_l, libc_strlwr_l);
DEFINE_PUBLIC_ALIAS(_strupr_l, libc_strupr_l);
DEFINE_PUBLIC_ALIAS(strupr_l, libc_strupr_l);
DEFINE_PUBLIC_ALIAS(strnlwr_l, libc_strnlwr_l);
DEFINE_PUBLIC_ALIAS(strnupr_l, libc_strnupr_l);
DEFINE_PUBLIC_ALIAS(memrev, libc_memrev);
DEFINE_PUBLIC_ALIAS(memrevw, libc_memrevw);
DEFINE_PUBLIC_ALIAS(memrevl, libc_memrevl);
DEFINE_PUBLIC_ALIAS(memrevq, libc_memrevq);
DEFINE_PUBLIC_ALIAS(_strlwr, libc_strlwr);
DEFINE_PUBLIC_ALIAS(strlwr, libc_strlwr);
DEFINE_PUBLIC_ALIAS(_strupr, libc_strupr);
DEFINE_PUBLIC_ALIAS(strupr, libc_strupr);
DEFINE_PUBLIC_ALIAS(_strset, libc_strset);
DEFINE_PUBLIC_ALIAS(strset, libc_strset);
DEFINE_PUBLIC_ALIAS(_strnset, libc_strnset);
DEFINE_PUBLIC_ALIAS(strnset, libc_strnset);
DEFINE_PUBLIC_ALIAS(_strrev, libc_strrev);
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
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_STRING_C */
