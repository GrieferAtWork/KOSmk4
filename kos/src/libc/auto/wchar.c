/* HASH CRC-32:0xadf5dedf */
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
#ifndef GUARD_LIBC_AUTO_WCHAR_C
#define GUARD_LIBC_AUTO_WCHAR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "wchar.h"
#include "string.h"
#include "wctype.h"
#include "stdlib.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.btowc") wint_t
NOTHROW_NCX(LIBCCALL libc_btowc)(int ch) {
#line 180 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return ch;
}

INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wctob") int
NOTHROW_NCX(LIBCCALL libc_wctob)(wint_t ch) {
#line 184 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return ch;
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbrtowc") size_t
NOTHROW_NCX(LIBCCALL libc_mbrtowc)(char32_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *ps) {
#line 191 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.mbrtowc") size_t
NOTHROW_NCX(LIBDCALL libd_mbrtowc)(char16_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *ps) {
#line 191 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcrtomb") size_t
NOTHROW_NCX(LIBCCALL libc_wcrtomb)(char *__restrict str,
                                   char32_t wc,
                                   mbstate_t *ps) {
#line 197 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcrtomb") size_t
NOTHROW_NCX(LIBDCALL libd_wcrtomb)(char *__restrict str,
                                   char16_t wc,
                                   mbstate_t *ps) {
#line 197 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}

INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbrlen") size_t
NOTHROW_NCX(LIBCCALL libc_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *ps) {
#line 203 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.mbrlen") size_t
NOTHROW_NCX(LIBDCALL libd_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *ps) {
#line 203 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbsrtowcs") size_t
NOTHROW_NCX(LIBCCALL libc_mbsrtowcs)(char32_t *dst,
                                     char const **__restrict psrc,
                                     size_t len,
                                     mbstate_t *ps) {
#line 210 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.mbsrtowcs") size_t
NOTHROW_NCX(LIBDCALL libd_mbsrtowcs)(char16_t *dst,
                                     char const **__restrict psrc,
                                     size_t len,
                                     mbstate_t *ps) {
#line 210 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcsrtombs") size_t
NOTHROW_NCX(LIBCCALL libc_wcsrtombs)(char *dst,
                                     char32_t const **__restrict psrc,
                                     size_t len,
                                     mbstate_t *ps) {
#line 217 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcsrtombs") size_t
NOTHROW_NCX(LIBDCALL libd_wcsrtombs)(char *dst,
                                     char16_t const **__restrict psrc,
                                     size_t len,
                                     mbstate_t *ps) {
#line 217 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcstod") double
NOTHROW_NCX(LIBCCALL libc_wcstod)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
#line 224 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcstod") double
NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
#line 224 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstol") long
NOTHROW_NCX(LIBCCALL libc_wcstol)(char32_t const *__restrict nptr,
                                  char32_t **endptr,
                                  int base) {
#line 708 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (long)libc_wcsto32(nptr, endptr, base);
#else
	return (long)libc_wcsto64(nptr, endptr, base);
#endif
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstol") long
NOTHROW_NCX(LIBDCALL libd_wcstol)(char16_t const *__restrict nptr,
                                  char16_t **endptr,
                                  int base) {
#line 708 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (long)libd_wcsto32(nptr, endptr, base);
#else
	return (long)libd_wcsto64(nptr, endptr, base);
#endif
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstoul") unsigned long
NOTHROW_NCX(LIBCCALL libc_wcstoul)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   int base) {
#line 695 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libc_wcstou32(nptr, endptr, base);
#else
	return (unsigned long)libc_wcstou64(nptr, endptr, base);
#endif
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstoul") unsigned long
NOTHROW_NCX(LIBDCALL libd_wcstoul)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   int base) {
#line 695 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libd_wcstou32(nptr, endptr, base);
#else
	return (unsigned long)libd_wcstou64(nptr, endptr, base);
#endif
}

INTERN WUNUSED ATTR_PURE
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbsinit") int
NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *ps) {
#line 248 "kos/src/libc/magic/wchar.c"
	return !ps || __MBSTATE_ISINIT(ps);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmemcmp") int
NOTHROW_NCX(LIBCCALL libc_wmemcmp)(char32_t const *s1,
                                   char32_t const *s2,
                                   size_t num_chars) {
#line 256 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return memcmpw(s1, s2, num_chars);
#elif 4 == 4
	return memcmpl(s1, s2, num_chars);
#else
	return memcmp(s1, s2, num_chars * sizeof(char32_t));
#endif
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemcmp") int
NOTHROW_NCX(LIBDCALL libd_wmemcmp)(char16_t const *s1,
                                   char16_t const *s2,
                                   size_t num_chars) {
#line 256 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return libc_memcmpw(s1, s2, num_chars);
#elif 2 == 4
	return libc_memcmpl(s1, s2, num_chars);
#else
	return libc_memcmp(s1, s2, num_chars * sizeof(char16_t));
#endif
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmemcpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wmemcpy)(char32_t *__restrict dst,
                                   char32_t const *__restrict src,
                                   size_t num_chars) {
#line 272 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)memcpyw(dst, src, num_chars);
#elif 4 == 4
	return (char32_t *)memcpyl(dst, src, num_chars);
#else
	return (char32_t *)memcpy(dst, src, num_chars * sizeof(char32_t));
#endif
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemcpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wmemcpy)(char16_t *__restrict dst,
                                   char16_t const *__restrict src,
                                   size_t num_chars) {
#line 272 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_memcpyw(dst, src, num_chars);
#elif 2 == 4
	return (char16_t *)libc_memcpyl(dst, src, num_chars);
#else
	return (char16_t *)libc_memcpy(dst, src, num_chars * sizeof(char16_t));
#endif
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmemmove") char32_t *
NOTHROW_NCX(LIBCCALL libc_wmemmove)(char32_t *dst,
                                    char32_t const *src,
                                    size_t num_chars) {
#line 288 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)memmovew(dst, src, num_chars);
#elif 4 == 4
	return (char32_t *)memmovel(dst, src, num_chars);
#else
	return (char32_t *)memmove(dst, src, num_chars * sizeof(char32_t));
#endif
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemmove") char16_t *
NOTHROW_NCX(LIBDCALL libd_wmemmove)(char16_t *dst,
                                    char16_t const *src,
                                    size_t num_chars) {
#line 288 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_memmovew(dst, src, num_chars);
#elif 2 == 4
	return (char16_t *)libc_memmovel(dst, src, num_chars);
#else
	return (char16_t *)libc_memmove(dst, src, num_chars * sizeof(char16_t));
#endif
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmemset") char32_t *
NOTHROW_NCX(LIBCCALL libc_wmemset)(char32_t *dst,
                                   char32_t filler,
                                   size_t num_chars) {
#line 302 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)memsetw(dst, (u16)filler, num_chars);
#elif 4 == 4
	return (char32_t *)memsetl(dst, (u32)filler, num_chars);
#else
	return (char32_t *)memset(dst, (int)filler, num_chars * sizeof(char32_t));
#endif
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemset") char16_t *
NOTHROW_NCX(LIBDCALL libd_wmemset)(char16_t *dst,
                                   char16_t filler,
                                   size_t num_chars) {
#line 302 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_memsetw(dst, (u16)filler, num_chars);
#elif 2 == 4
	return (char16_t *)libc_memsetl(dst, (u32)filler, num_chars);
#else
	return (char16_t *)libc_memset(dst, (int)filler, num_chars * sizeof(char16_t));
#endif
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcscpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcscpy)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
#line 314 "kos/src/libc/magic/wchar.c"
	return libc_wmemcpy(buf, src, libc_wcslen(src) + 1);
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
#line 314 "kos/src/libc/magic/wchar.c"
	return libd_wmemcpy(buf, src, libd_wcslen(src) + 1);
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcscat") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcscat)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
#line 320 "kos/src/libc/magic/wchar.c"
	libc_wmemcpy(libc_wcsend(buf), src, libc_wcslen(src) + 1);
	return buf;
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscat") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
#line 320 "kos/src/libc/magic/wchar.c"
	libd_wmemcpy(libd_wcsend(buf), src, libd_wcslen(src) + 1);
	return buf;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsncat") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsncat)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
#line 329 "kos/src/libc/magic/wchar.c"
	size_t srclen = libc_wcsnlen(src, buflen);
	char32_t *dst = libc_wcsend(buf);
	libc_wmemcpy(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsncat") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
#line 329 "kos/src/libc/magic/wchar.c"
	size_t srclen = libd_wcsnlen(src, buflen);
	char16_t *dst = libd_wcsend(buf);
	libd_wmemcpy(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsncpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
#line 341 "kos/src/libc/magic/wchar.c"
	size_t srclen = libc_wcsnlen(src, buflen);
	libc_wmemcpy(buf, src, srclen);
	libc_wmemset(buf+srclen, '\0', buflen - srclen);
	return buf;
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsncpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
#line 341 "kos/src/libc/magic/wchar.c"
	size_t srclen = libd_wcsnlen(src, buflen);
	libd_wmemcpy(buf, src, srclen);
	libd_wmemset(buf+srclen, '\0', buflen - srclen);
	return buf;
}

/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcscmp") int
NOTHROW_NCX(LIBCCALL libc_wcscmp)(char32_t const *s1,
                                  char32_t const *s2) {
#line 238 "kos/src/libc/magic/string.c"
	char32_t c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscmp") int
NOTHROW_NCX(LIBDCALL libd_wcscmp)(char16_t const *s1,
                                  char16_t const *s2) {
#line 238 "kos/src/libc/magic/string.c"
	char16_t c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}

/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsncmp") int
NOTHROW_NCX(LIBCCALL libc_wcsncmp)(char32_t const *s1,
                                   char32_t const *s2,
                                   size_t maxlen) {
#line 249 "kos/src/libc/magic/string.c"
	char32_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsncmp") int
NOTHROW_NCX(LIBDCALL libd_wcsncmp)(char16_t const *s1,
                                   char16_t const *s2,
                                   size_t maxlen) {
#line 249 "kos/src/libc/magic/string.c"
	char16_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcscoll") int
NOTHROW_NCX(LIBCCALL libc_wcscoll)(char32_t const *s1,
                                   char32_t const *s2) {
#line 354 "kos/src/libc/magic/string.c"
	return libc_wcscmp(s1, s2);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcscoll") int
NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1,
                                   char16_t const *s2) {
#line 354 "kos/src/libc/magic/string.c"
	return libd_wcscmp(s1, s2);
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcsxfrm") size_t
NOTHROW_NCX(LIBCCALL libc_wcsxfrm)(char32_t *dst,
                                   char32_t const *__restrict src,
                                   size_t maxlen) {
#line 359 "kos/src/libc/magic/string.c"
	/* XXX: Implement me */
	size_t n = libc_wcsnlen(src, maxlen);
	memcpy(dst, src, n * sizeof(char32_t));
	return n;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcsxfrm") size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst,
                                   char16_t const *__restrict src,
                                   size_t maxlen) {
#line 359 "kos/src/libc/magic/string.c"
	/* XXX: Implement me */
	size_t n = libd_wcsnlen(src, maxlen);
	libc_memcpy(dst, src, n * sizeof(char16_t));
	return n;
}

INTERN NONNULL((1, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.format.strftime.wcsftime") size_t
NOTHROW_NCX(LIBCCALL libc_wcsftime)(char32_t *__restrict buf,
                                    size_t buflen,
                                    char32_t const *__restrict format,
                                    struct tm const *__restrict tp) {
#line 466 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}
INTERN NONNULL((1, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.strftime.wcsftime") size_t
NOTHROW_NCX(LIBDCALL libd_wcsftime)(char16_t *__restrict buf,
                                    size_t buflen,
                                    char16_t const *__restrict format,
                                    struct tm const *__restrict tp) {
#line 466 "kos/src/libc/magic/wchar.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcstok") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcstok)(char32_t *string,
                                  char32_t const *__restrict delim,
                                  char32_t **__restrict save_ptr) {
#line 483 "kos/src/libc/magic/string.c"
	char32_t *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += libc_wcsspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + libc_wcscspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return string;
}
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcstok") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcstok)(char16_t *string,
                                  char16_t const *__restrict delim,
                                  char16_t **__restrict save_ptr) {
#line 483 "kos/src/libc/magic/string.c"
	char16_t *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += libd_wcsspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + libd_wcscspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return string;
}

/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcslen") size_t
NOTHROW_NCX(LIBCCALL libc_wcslen)(char32_t const *__restrict string) {
#line 206 "kos/src/libc/magic/string.c"
	return (size_t)(libc_wcsend(string) - string);
}
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcslen") size_t
NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict string) {
#line 206 "kos/src/libc/magic/string.c"
	return (size_t)(libd_wcsend(string) - string);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsspn") size_t
NOTHROW_NCX(LIBCCALL libc_wcsspn)(char32_t const *haystack,
                                  char32_t const *accept) {
#line 320 "kos/src/libc/magic/string.c"
	char32_t const *iter = haystack;
	while (libc_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsspn") size_t
NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack,
                                  char16_t const *accept) {
#line 320 "kos/src/libc/magic/string.c"
	char16_t const *iter = haystack;
	while (libd_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcscspn") size_t
NOTHROW_NCX(LIBCCALL libc_wcscspn)(char32_t const *haystack,
                                   char32_t const *reject) {
#line 312 "kos/src/libc/magic/string.c"
	char32_t const *iter = haystack;
	while (*iter && !libc_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscspn") size_t
NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack,
                                   char16_t const *reject) {
#line 312 "kos/src/libc/magic/string.c"
	char16_t const *iter = haystack;
	while (*iter && !libd_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}

/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcschr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcschr)(char32_t const *__restrict haystack,
                                  char32_t needle) {
#line 216 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack)
		if (*haystack == (char32_t)needle)
			return (char32_t *)haystack;
	return NULL;
}
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcschr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcschr)(char16_t const *__restrict haystack,
                                  char16_t needle) {
#line 216 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack)
		if (*haystack == (char16_t)needle)
			return (char16_t *)haystack;
	return NULL;
}

/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsrchr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsrchr)(char32_t const *__restrict haystack,
                                   char32_t needle) {
#line 228 "kos/src/libc/magic/string.c"
	char32_t const *result = NULL;
	for (; *haystack; ++haystack)
		if (*haystack == (char32_t)needle)
			result = haystack;
	return (char32_t *)result;
}
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsrchr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrchr)(char16_t const *__restrict haystack,
                                   char16_t needle) {
#line 228 "kos/src/libc/magic/string.c"
	char16_t const *result = NULL;
	for (; *haystack; ++haystack)
		if (*haystack == (char16_t)needle)
			result = haystack;
	return (char16_t *)result;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcspbrk") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcspbrk)(char32_t const *haystack,
                                   char32_t const *accept) {
#line 331 "kos/src/libc/magic/string.c"
	char32_t const *ned_iter;
	char32_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char32_t *)haystack - 1;
		}
	}
	return NULL;
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcspbrk") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack,
                                   char16_t const *accept) {
#line 331 "kos/src/libc/magic/string.c"
	char16_t const *ned_iter;
	char16_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char16_t *)haystack - 1;
		}
	}
	return NULL;
}

/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsstr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsstr)(char32_t const *haystack,
                                  char32_t const *needle) {
#line 266 "kos/src/libc/magic/string.c"
	char32_t const *hay2, *ned_iter;
	char32_t ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			hay2 = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char32_t *)haystack-1;
		}
miss:
		;
	}
	return NULL;
}
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsstr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsstr)(char16_t const *haystack,
                                  char16_t const *needle) {
#line 266 "kos/src/libc/magic/string.c"
	char16_t const *hay2, *ned_iter;
	char16_t ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			hay2 = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char16_t *)haystack-1;
		}
miss:
		;
	}
	return NULL;
}

INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmemchr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wmemchr)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t num_chars) {
#line 520 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)memchrw(haystack, needle, num_chars);
#elif 4 == 4
	return (char32_t *)memchrl(haystack, needle, num_chars);
#else
	return (char32_t *)memchr(haystack, (int)needle, num_chars * sizeof(char32_t));
#endif
}
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemchr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wmemchr)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t num_chars) {
#line 520 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_memchrw(haystack, needle, num_chars);
#elif 2 == 4
	return (char16_t *)libc_memchrl(haystack, needle, num_chars);
#else
	return (char16_t *)libc_memchr(haystack, (int)needle, num_chars * sizeof(char16_t));
#endif
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.utility.fwide") int
NOTHROW_NCX(LIBCCALL libc_fwide)(FILE *fp,
                                 int mode) {
#line 533 "kos/src/libc/magic/wchar.c"
	return 0;
}

INTERN ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf.swscanf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc_swscanf)(char32_t const *__restrict src,
                                    char32_t const *__restrict format,
                                    ...) {
#line 577 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswscanf(src, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf.swscanf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_swscanf)(char16_t const *__restrict src,
                                    char16_t const *__restrict format,
                                    ...) {
#line 577 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswscanf(src, format, args);
	va_end(args);
	return result;
}

INTERN ATTR_LIBC_WPRINTF(3, 0) NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf.vswprintf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_vswprintf)(char32_t *__restrict buf,
                                     size_t buflen,
                                     char32_t const *__restrict format,
                                     va_list args) {
#line 582 "kos/src/libc/magic/wchar.c"
	/* TODO: format_wprintf() */
	return 0;
}
INTERN ATTR_LIBC_WPRINTF(3, 0) NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf.vswprintf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vswprintf)(char16_t *__restrict buf,
                                     size_t buflen,
                                     char16_t const *__restrict format,
                                     va_list args) {
#line 582 "kos/src/libc/magic/wchar.c"
	/* TODO: format_wprintf() */
	return 0;
}

INTERN ATTR_LIBC_WPRINTF(3, 4) NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf.swprintf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBCCALL libc_swprintf)(char32_t *__restrict buf,
                                     size_t buflen,
                                     char32_t const *__restrict format,
                                     ...) {
#line 591 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
INTERN ATTR_LIBC_WPRINTF(3, 4) NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf.swprintf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_swprintf)(char16_t *__restrict buf,
                                     size_t buflen,
                                     char16_t const *__restrict format,
                                     ...) {
#line 591 "kos/src/libc/magic/wchar.c"
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}

INTERN ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstof") float
NOTHROW_NCX(LIBCCALL libc_wcstof)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
#line 758 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
INTERN ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstof") float
NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
#line 758 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstold") long double
NOTHROW_NCX(LIBCCALL libc_wcstold)(char32_t const *__restrict nptr,
                                   char32_t **endptr) {
#line 765 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
INTERN ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstold") long double
NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr,
                                   char16_t **endptr) {
#line 765 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstoll") __LONGLONG
NOTHROW_NCX(LIBCCALL libc_wcstoll)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   int base) {
#line 735 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_wcsto32(nptr, endptr, base);
#else
	return (__LONGLONG)libc_wcsto64(nptr, endptr, base);
#endif
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstoll") __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoll)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   int base) {
#line 735 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libd_wcsto32(nptr, endptr, base);
#else
	return (__LONGLONG)libd_wcsto64(nptr, endptr, base);
#endif
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstoull") __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_wcstoull)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    int base) {
#line 723 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libc_wcstou32(nptr, endptr, base);
#else
	return (__ULONGLONG)libc_wcstou64(nptr, endptr, base);
#endif
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstoull") __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoull)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    int base) {
#line 723 "kos/src/libc/magic/stdlib.c"
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libd_wcstou32(nptr, endptr, base);
#else
	return (__ULONGLONG)libd_wcstou64(nptr, endptr, base);
#endif
}

INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf.vswscanf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_vswscanf)(char32_t const *__restrict src,
                                    char32_t const *__restrict format,
                                    va_list args) {
#line 639 "kos/src/libc/magic/wchar.c"
	/* TODO: format_wscanf() */
	return 0;
}
INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf.vswscanf") __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vswscanf)(char16_t const *__restrict src,
                                    char16_t const *__restrict format,
                                    va_list args) {
#line 639 "kos/src/libc/magic/wchar.c"
	/* TODO: format_wscanf() */
	return 0;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcscasecmp") int
NOTHROW_NCX(LIBCCALL libc_wcscasecmp)(char32_t const *s1,
                                      char32_t const *s2) {
#line 756 "kos/src/libc/magic/string.c"
	char32_t c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char32_t)libc_towlower(c1)) != (c2 = (char32_t)libc_towlower(c2))))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcscasecmp") int
NOTHROW_NCX(LIBDCALL libd_wcscasecmp)(char16_t const *s1,
                                      char16_t const *s2) {
#line 756 "kos/src/libc/magic/string.c"
	char16_t c1, c2;
	do {
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char16_t)libc_towlower(c1)) != (c2 = (char16_t)libc_towlower(c2))))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcsncasecmp") int
NOTHROW_NCX(LIBCCALL libc_wcsncasecmp)(char32_t const *s1,
                                       char32_t const *s2,
                                       size_t maxlen) {
#line 766 "kos/src/libc/magic/string.c"
	char32_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char32_t)libc_towlower(c1)) != (c2 = (char32_t)libc_towlower(c2))))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcsncasecmp") int
NOTHROW_NCX(LIBDCALL libd_wcsncasecmp)(char16_t const *s1,
                                       char16_t const *s2,
                                       size_t maxlen) {
#line 766 "kos/src/libc/magic/string.c"
	char16_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++) && ((c1 = (char16_t)libc_towlower(c1)) != (c2 = (char16_t)libc_towlower(c2))))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcscasecmp_l") int
NOTHROW_NCX(LIBCCALL libc_wcscasecmp_l)(char32_t const *s1,
                                        char32_t const *s2,
                                        locale_t locale) {
#line 710 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_wcscasecmp(s1, s2);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcscasecmp_l") int
NOTHROW_NCX(LIBDCALL libd_wcscasecmp_l)(char16_t const *s1,
                                        char16_t const *s2,
                                        locale_t locale) {
#line 710 "kos/src/libc/magic/string.c"
	(void)locale;
	return libd_wcscasecmp(s1, s2);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcsncasecmp_l") int
NOTHROW_NCX(LIBCCALL libc_wcsncasecmp_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
#line 716 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_wcsncasecmp(s1, s2, maxlen);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcsncasecmp_l") int
NOTHROW_NCX(LIBDCALL libd_wcsncasecmp_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
#line 716 "kos/src/libc/magic/string.c"
	(void)locale;
	return libd_wcsncasecmp(s1, s2, maxlen);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcscoll_l") int
NOTHROW_NCX(LIBCCALL libc_wcscoll_l)(char32_t const *s1,
                                     char32_t const *s2,
                                     locale_t locale) {
#line 424 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_wcscoll(s1, s2);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcscoll_l") int
NOTHROW_NCX(LIBDCALL libd_wcscoll_l)(char16_t const *s1,
                                     char16_t const *s2,
                                     locale_t locale) {
#line 424 "kos/src/libc/magic/string.c"
	(void)locale;
	return libd_wcscoll(s1, s2);
}

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcsxfrm_l") size_t
NOTHROW_NCX(LIBCCALL libc_wcsxfrm_l)(char32_t *dst,
                                     char32_t const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
#line 432 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_wcsxfrm(dst, src, maxlen);
}
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcsxfrm_l") size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm_l)(char16_t *dst,
                                     char16_t const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
#line 432 "kos/src/libc/magic/string.c"
	(void)locale;
	return libd_wcsxfrm(dst, src, maxlen);
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcpcpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcpcpy)(char32_t *__restrict dst,
                                  char32_t const *__restrict src) {
#line 725 "kos/src/libc/magic/wchar.c"
	return libc_wmempcpy(dst, src, libc_wcslen(src) + 1);
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcpcpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpcpy)(char16_t *__restrict dst,
                                  char16_t const *__restrict src) {
#line 725 "kos/src/libc/magic/wchar.c"
	return libd_wmempcpy(dst, src, libd_wcslen(src) + 1);
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcpncpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcpncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
#line 731 "kos/src/libc/magic/wchar.c"
	size_t srclen = libc_wcsnlen(src, buflen);
	libc_wmemcpy(buf, src, srclen);
	libc_wmemset(buf + srclen, '\0', (size_t)(buflen - srclen));
	return buf + srclen;
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcpncpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
#line 731 "kos/src/libc/magic/wchar.c"
	size_t srclen = libd_wcsnlen(src, buflen);
	libd_wmemcpy(buf, src, srclen);
	libd_wmemset(buf + srclen, '\0', (size_t)(buflen - srclen));
	return buf + srclen;
}

/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnlen") size_t
NOTHROW_NCX(LIBCCALL libc_wcsnlen)(char32_t const *__restrict string,
                                   size_t maxlen) {
#line 398 "kos/src/libc/magic/string.c"
	return (size_t)(libc_wcsnend(string, maxlen) - string);
}
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnlen") size_t
NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict string,
                                   size_t maxlen) {
#line 398 "kos/src/libc/magic/string.c"
	return (size_t)(libd_wcsnend(string, maxlen) - string);
}

/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcschrnul") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcschrnul)(char32_t const *haystack,
                                     char32_t needle) {
#line 545 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack)
		if (*haystack == (char32_t)needle)
			break;
	return (char32_t *)haystack;
}
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcschrnul") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcschrnul)(char16_t const *haystack,
                                     char16_t needle) {
#line 545 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack)
		if (*haystack == (char16_t)needle)
			break;
	return (char16_t *)haystack;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmempcpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wmempcpy)(char32_t *__restrict dst,
                                    char32_t const *__restrict src,
                                    size_t num_chars) {
#line 811 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)mempcpyw(dst, src, num_chars);
#elif 4 == 4
	return (char32_t *)mempcpyl(dst, src, num_chars);
#else
	return (char32_t *)mempcpy(dst, src, num_chars * sizeof(char32_t));
#endif
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmempcpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wmempcpy)(char16_t *__restrict dst,
                                    char16_t const *__restrict src,
                                    size_t num_chars) {
#line 811 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_mempcpyw(dst, src, num_chars);
#elif 2 == 4
	return (char16_t *)libc_mempcpyl(dst, src, num_chars);
#else
	return (char16_t *)libc_mempcpy(dst, src, num_chars * sizeof(char16_t));
#endif
}

INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmempmove") char32_t *
NOTHROW_NCX(LIBCCALL libc_wmempmove)(char32_t *dst,
                                     char32_t const *src,
                                     size_t num_chars) {
#line 826 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)mempmovew(dst, src, num_chars);
#elif 4 == 4
	return (char32_t *)mempmovel(dst, src, num_chars);
#else
	return (char32_t *)mempmove(dst, src, num_chars * sizeof(char32_t));
#endif
}
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmempmove") char16_t *
NOTHROW_NCX(LIBDCALL libd_wmempmove)(char16_t *dst,
                                     char16_t const *src,
                                     size_t num_chars) {
#line 826 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_mempmovew(dst, src, num_chars);
#elif 2 == 4
	return (char16_t *)libc_mempmovel(dst, src, num_chars);
#else
	return (char16_t *)libc_mempmove(dst, src, num_chars * sizeof(char16_t));
#endif
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstol_l") long
NOTHROW_NCX(LIBCCALL libc_wcstol_l)(char32_t const *__restrict nptr,
                                    char32_t **__restrict endptr,
                                    int base,
                                    locale_t locale) {
#line 1386 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstol(nptr, endptr, base);
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstol_l") long
NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr,
                                    char16_t **__restrict endptr,
                                    int base,
                                    locale_t locale) {
#line 1386 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wcstol(nptr, endptr, base);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstoul_l") unsigned long
NOTHROW_NCX(LIBCCALL libc_wcstoul_l)(char32_t const *__restrict nptr,
                                     char32_t **__restrict endptr,
                                     int base,
                                     locale_t locale) {
#line 1395 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstoul(nptr, endptr, base);
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstoul_l") unsigned long
NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr,
                                     char16_t **__restrict endptr,
                                     int base,
                                     locale_t locale) {
#line 1395 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wcstoul(nptr, endptr, base);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstoll_l") __LONGLONG
NOTHROW_NCX(LIBCCALL libc_wcstoll_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     int base,
                                     locale_t locale) {
#line 1405 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstoll(nptr, endptr, base);
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstoll_l") __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     int base,
                                     locale_t locale) {
#line 1405 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wcstoll(nptr, endptr, base);
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstoull_l") __ULONGLONG
NOTHROW_NCX(LIBCCALL libc_wcstoull_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      int base,
                                      locale_t locale) {
#line 1414 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstoull(nptr, endptr, base);
}
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstoull_l") __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      int base,
                                      locale_t locale) {
#line 1414 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wcstoull(nptr, endptr, base);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstof_l") float
NOTHROW_NCX(LIBCCALL libc_wcstof_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
#line 1429 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstof(nptr, endptr);
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstof_l") float
NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
#line 1429 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wcstof(nptr, endptr);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstod_l") double
NOTHROW_NCX(LIBCCALL libc_wcstod_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
#line 1423 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstod(nptr, endptr);
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstod_l") double
NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
#line 1423 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wcstod(nptr, endptr);
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.convert.wcstold_l") long double
NOTHROW_NCX(LIBCCALL libc_wcstold_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     locale_t locale) {
#line 1436 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libc_wcstold(nptr, endptr);
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert.wcstold_l") long double
NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     locale_t locale) {
#line 1436 "kos/src/libc/magic/stdlib.c"
	(void)locale;
	return libd_wcstold(nptr, endptr);
}

INTERN NONNULL((1, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.format.strftime.wcsftime_l") size_t
NOTHROW_NCX(LIBCCALL libc_wcsftime_l)(char32_t *__restrict buf,
                                      size_t maxsize,
                                      char32_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
#line 982 "kos/src/libc/magic/wchar.c"
	(void)locale;
	return libc_wcsftime(buf, maxsize, format, tp);
}
INTERN NONNULL((1, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.strftime.wcsftime_l") size_t
NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf,
                                      size_t maxsize,
                                      char16_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
#line 982 "kos/src/libc/magic/wchar.c"
	(void)locale;
	return libd_wcsftime(buf, maxsize, format, tp);
}

/* Same as `STR+wcslen(STR)' */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsend") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsend)(char32_t const *__restrict string) {
#line 2066 "kos/src/libc/magic/string.c"
	while (*string)
		++string;
	return (char32_t *)string;
}
/* Same as `STR+wcslen(STR)' */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsend") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict string) {
#line 2066 "kos/src/libc/magic/string.c"
	while (*string)
		++string;
	return (char16_t *)string;
}

/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnend") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnend)(char32_t const *__restrict string,
                                   size_t maxlen) {
#line 2077 "kos/src/libc/magic/string.c"
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char32_t *)string;
}
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnend") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnend)(char16_t const *__restrict string,
                                   size_t maxlen) {
#line 2077 "kos/src/libc/magic/string.c"
	for (; maxlen && *string; ++string, --maxlen)
		;
	return (char16_t *)string;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstou32") uint32_t
NOTHROW_NCX(LIBCCALL libc_wcstou32)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    int base) {
#line 800 "kos/src/libc/magic/stdlib.c"
	u32 result, temp;
	if (!base) {
		if (*nptr == '0') {
			++nptr;
			if (*nptr == 'x' || *nptr == 'X') {
				++nptr;
				base = 16;
			} else if (*nptr == 'b' || *nptr == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char32_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch-'0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)(10+(ch-'a'));
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)(10+(ch-'A'));
		else {
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		result *= base;
		result += temp;
	}
	if (endptr)
		*endptr = (char32_t *)nptr;
	return result;
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstou32") uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    int base) {
#line 800 "kos/src/libc/magic/stdlib.c"
	u32 result, temp;
	if (!base) {
		if (*nptr == '0') {
			++nptr;
			if (*nptr == 'x' || *nptr == 'X') {
				++nptr;
				base = 16;
			} else if (*nptr == 'b' || *nptr == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char16_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch-'0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)(10+(ch-'a'));
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)(10+(ch-'A'));
		else {
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		result *= base;
		result += temp;
	}
	if (endptr)
		*endptr = (char16_t *)nptr;
	return result;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcsto32") int32_t
NOTHROW_NCX(LIBCCALL libc_wcsto32)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   int base) {
#line 845 "kos/src/libc/magic/stdlib.c"
	u32 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = libc_wcstou32(nptr, endptr, base);
	return neg ? -(s32)result : (s32)result;
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcsto32") int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   int base) {
#line 845 "kos/src/libc/magic/stdlib.c"
	u32 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = libd_wcstou32(nptr, endptr, base);
	return neg ? -(s32)result : (s32)result;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcstou64") uint64_t
NOTHROW_NCX(LIBCCALL libc_wcstou64)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    int base) {
#line 861 "kos/src/libc/magic/stdlib.c"
	u64 result, temp;
	if (!base) {
		if (*nptr == '0') {
			++nptr;
			if (*nptr == 'x' || *nptr == 'X') {
				++nptr;
				base = 16;
			} else if (*nptr == 'b' || *nptr == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char32_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch-'0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)(10+(ch-'a'));
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)(10+(ch-'A'));
		else {
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		result *= base;
		result += temp;
	}
	if (endptr)
		*endptr = (char32_t *)nptr;
	return result;
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcstou64") uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    int base) {
#line 861 "kos/src/libc/magic/stdlib.c"
	u64 result, temp;
	if (!base) {
		if (*nptr == '0') {
			++nptr;
			if (*nptr == 'x' || *nptr == 'X') {
				++nptr;
				base = 16;
			} else if (*nptr == 'b' || *nptr == 'B') {
				++nptr;
				base = 2;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	}
	result = 0;
	for (;;) {
		char16_t ch = *nptr;
		if (ch >= '0' && ch <= '9')
			temp = (u64)(ch-'0');
		else if (ch >= 'a' && ch <= 'z')
			temp = (u64)(10+(ch-'a'));
		else if (ch >= 'A' && ch <= 'Z')
			temp = (u64)(10+(ch-'A'));
		else {
			break;
		}
		if (temp >= (unsigned int)base)
			break;
		++nptr;
		result *= base;
		result += temp;
	}
	if (endptr)
		*endptr = (char16_t *)nptr;
	return result;
}

INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.convert.wcsto64") int64_t
NOTHROW_NCX(LIBCCALL libc_wcsto64)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   int base) {
#line 906 "kos/src/libc/magic/stdlib.c"
	u64 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = libc_wcstou64(nptr, endptr, base);
	return neg ? -(s64)result : (s64)result;
}
INTERN ATTR_PURE WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert.wcsto64") int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   int base) {
#line 906 "kos/src/libc/magic/stdlib.c"
	u64 result;
	bool neg = 0;
	while (*nptr == '-') {
		neg = !neg;
		++nptr;
	}
	result = libd_wcstou64(nptr, endptr, base);
	return neg ? -(s64)result : (s64)result;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcsncoll") int
NOTHROW_NCX(LIBCCALL libc_wcsncoll)(char32_t const *s1,
                                    char32_t const *s2,
                                    size_t maxlen) {
#line 3998 "kos/src/libc/magic/string.c"
	return libc_wcsncmp(s1, s2, maxlen);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcsncoll") int
NOTHROW_NCX(LIBDCALL libd_wcsncoll)(char16_t const *s1,
                                    char16_t const *s2,
                                    size_t maxlen) {
#line 3998 "kos/src/libc/magic/string.c"
	return libd_wcsncmp(s1, s2, maxlen);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcscasecoll") int
NOTHROW_NCX(LIBCCALL libc_wcscasecoll)(char32_t const *s1,
                                       char32_t const *s2) {
#line 4003 "kos/src/libc/magic/string.c"
	return libc_wcscasecmp(s1, s2);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcscasecoll") int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll)(char16_t const *s1,
                                       char16_t const *s2) {
#line 4003 "kos/src/libc/magic/string.c"
	return libd_wcscasecmp(s1, s2);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcsncasecoll") int
NOTHROW_NCX(LIBCCALL libc_wcsncasecoll)(char32_t const *s1,
                                        char32_t const *s2,
                                        size_t maxlen) {
#line 4008 "kos/src/libc/magic/string.c"
	return libc_wcsncasecmp(s1, s2, maxlen);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcsncasecoll") int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll)(char16_t const *s1,
                                        char16_t const *s2,
                                        size_t maxlen) {
#line 4008 "kos/src/libc/magic/string.c"
	return libd_wcsncasecmp(s1, s2, maxlen);
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnrev") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnrev)(char32_t *__restrict str,
                                   size_t maxlen) {
#line 1187 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)libc_memrevw(str, libc_wcsnlen(str, maxlen));
#elif 4 == 4
	return (char32_t *)libc_memrevl(str, libc_wcsnlen(str, maxlen));
#else
	return (char32_t *)libc_memrev(str, libc_wcsnlen(str, maxlen) * sizeof(char32_t));
#endif
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnrev") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str,
                                   size_t maxlen) {
#line 1187 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_memrevw(str, libd_wcsnlen(str, maxlen));
#elif 2 == 4
	return (char16_t *)libc_memrevl(str, libd_wcsnlen(str, maxlen));
#else
	return (char16_t *)libc_memrev(str, libd_wcsnlen(str, maxlen) * sizeof(char16_t));
#endif
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcsnlwr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnlwr)(char32_t *__restrict str,
                                   size_t maxlen) {
#line 4018 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower(ch);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcsnupr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnupr)(char32_t *__restrict str,
                                   size_t maxlen) {
#line 4026 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper(ch);
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcsnupr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str,
                                   size_t maxlen) {
#line 4026 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper(ch);
	return str;
}

/* Same as `wcsstr', but ignore casing */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wcscasestr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcscasestr)(char32_t const *haystack,
                                      char32_t const *needle) {
#line 602 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack) {
		if (libc_wcscasecmp(haystack, needle) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* Same as `wcsstr', but ignore casing */
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcscasestr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack,
                                      char16_t const *needle) {
#line 602 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack) {
		if (libd_wcscasecmp(haystack, needle) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}

/* Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcspcpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcspcpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src) {
#line 1215 "kos/src/libc/magic/wchar.c"
	return libc_wmempcpy(buf, src, libc_wcslen(src) + 1);
}
/* Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcspcpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src) {
#line 1215 "kos/src/libc/magic/wchar.c"
	return libd_wmempcpy(buf, src, libd_wcslen(src) + 1);
}

/* Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcspncpy") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcspncpy)(char32_t *__restrict buf,
                                    char32_t const *__restrict src,
                                    size_t buflen) {
#line 1221 "kos/src/libc/magic/wchar.c"
	size_t srclen = libc_wcsnlen(src, buflen);
	libc_wmemcpy(buf, src, srclen);
	return libc_wmempset(buf+srclen, '\0', buflen - srclen);
}
/* Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcspncpy") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf,
                                    char16_t const *__restrict src,
                                    size_t buflen) {
#line 1221 "kos/src/libc/magic/wchar.c"
	size_t srclen = libd_wcsnlen(src, buflen);
	libd_wmemcpy(buf, src, srclen);
	return libd_wmempset(buf+srclen, '\0', buflen - srclen);
}

/* Same as wmemset, but return a pointer after the last written character */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wmempset") char32_t *
NOTHROW_NCX(LIBCCALL libc_wmempset)(char32_t *dst,
                                    char32_t filler,
                                    size_t num_chars) {
#line 1231 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)mempsetw(dst, (u16)filler, num_chars);
#elif 4 == 4
	return (char32_t *)mempsetl(dst, (u32)filler, num_chars);
#else
	return (char32_t *)mempset(dst, (int)filler, num_chars * sizeof(char32_t));
#endif
}
/* Same as wmemset, but return a pointer after the last written character */
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmempset") char16_t *
NOTHROW_NCX(LIBDCALL libd_wmempset)(char16_t *dst,
                                    char16_t filler,
                                    size_t num_chars) {
#line 1231 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_mempsetw(dst, (u16)filler, num_chars);
#elif 2 == 4
	return (char16_t *)libc_mempsetl(dst, (u32)filler, num_chars);
#else
	return (char16_t *)libc_mempset(dst, (int)filler, num_chars * sizeof(char16_t));
#endif
}

/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnchr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnchr)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t maxlen) {
#line 2088 "kos/src/libc/magic/string.c"
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((char32_t)*haystack == (char32_t)needle)
			return (char32_t *)haystack;
	return NULL;
}
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnchr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnchr)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t maxlen) {
#line 2088 "kos/src/libc/magic/string.c"
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((char16_t)*haystack == (char16_t)needle)
			return (char16_t *)haystack;
	return NULL;
}

/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnrchr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnrchr)(char32_t const *__restrict haystack,
                                    char32_t needle,
                                    size_t maxlen) {
#line 2100 "kos/src/libc/magic/string.c"
	char32_t const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	return (char32_t *)result;
}
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnrchr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrchr)(char16_t const *__restrict haystack,
                                    char16_t needle,
                                    size_t maxlen) {
#line 2100 "kos/src/libc/magic/string.c"
	char16_t const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	return (char16_t *)result;
}

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcssep") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcssep)(char32_t **__restrict stringp,
                                  char32_t const *__restrict delim) {
#line 736 "kos/src/libc/magic/string.c"
	char32_t *result, *iter;
	if (!stringp || (result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libc_wcschr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcssep") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcssep)(char16_t **__restrict stringp,
                                  char16_t const *__restrict delim) {
#line 736 "kos/src/libc/magic/string.c"
	char16_t *result, *iter;
	if (!stringp || (result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libd_wcschr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsfry") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsfry)(char32_t *__restrict string) {
#line 685 "kos/src/libc/magic/string.c"
	char32_t temp;
	size_t i, count = libc_wcslen(string);
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
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsfry") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsfry)(char16_t *__restrict string) {
#line 685 "kos/src/libc/magic/string.c"
	char16_t temp;
	size_t i, count = libd_wcslen(string);
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

/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsrchrnul") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsrchrnul)(char32_t const *__restrict haystack,
                                      char32_t needle) {
#line 2113 "kos/src/libc/magic/string.c"
	char32_t const *result = haystack - 1;
	do {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	} while (*haystack++);
	return (char32_t *)result;
}
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsrchrnul") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrchrnul)(char16_t const *__restrict haystack,
                                      char16_t needle) {
#line 2113 "kos/src/libc/magic/string.c"
	char16_t const *result = haystack - 1;
	do {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	} while (*haystack++);
	return (char16_t *)result;
}

/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnchrnul") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnchrnul)(char32_t const *__restrict haystack,
                                      char32_t needle,
                                      size_t maxlen) {
#line 2127 "kos/src/libc/magic/string.c"
	for (; maxlen-- && *haystack && (char32_t)*haystack != (char32_t)needle; ++haystack);
	return (char32_t *)haystack;
}
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnchrnul") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack,
                                      char16_t needle,
                                      size_t maxlen) {
#line 2127 "kos/src/libc/magic/string.c"
	for (; maxlen-- && *haystack && (char16_t)*haystack != (char16_t)needle; ++haystack);
	return (char16_t *)haystack;
}

/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnrchrnul") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnrchrnul)(char32_t const *__restrict haystack,
                                       char32_t needle,
                                       size_t maxlen) {
#line 2137 "kos/src/libc/magic/string.c"
	char32_t const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	return (char32_t *)result;
}
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
INTERN WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnrchrnul") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrchrnul)(char16_t const *__restrict haystack,
                                       char16_t needle,
                                       size_t maxlen) {
#line 2137 "kos/src/libc/magic/string.c"
	char16_t const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack)
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	return (char16_t *)result;
}

/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsoff") size_t
NOTHROW_NCX(LIBCCALL libc_wcsoff)(char32_t const *__restrict haystack,
                                  char32_t needle) {
#line 2147 "kos/src/libc/magic/string.c"
	return (size_t)(libc_wcschrnul(haystack, needle) - haystack);
}
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsoff") size_t
NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack,
                                  char16_t needle) {
#line 2147 "kos/src/libc/magic/string.c"
	return (size_t)(libd_wcschrnul(haystack, needle) - haystack);
}

/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsroff") size_t
NOTHROW_NCX(LIBCCALL libc_wcsroff)(char32_t const *__restrict haystack,
                                   char32_t needle) {
#line 2153 "kos/src/libc/magic/string.c"
	return (size_t)(libc_wcsrchrnul(haystack, needle) - haystack);
}
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsroff") size_t
NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack,
                                   char16_t needle) {
#line 2153 "kos/src/libc/magic/string.c"
	return (size_t)(libd_wcsrchrnul(haystack, needle) - haystack);
}

/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnoff") size_t
NOTHROW_NCX(LIBCCALL libc_wcsnoff)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t maxlen) {
#line 2159 "kos/src/libc/magic/string.c"
	return (size_t)(libc_wcsnchrnul(haystack, needle, maxlen) - haystack);
}
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnoff") size_t
NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t maxlen) {
#line 2159 "kos/src/libc/magic/string.c"
	return (size_t)(libd_wcsnchrnul(haystack, needle, maxlen) - haystack);
}

/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsnroff") size_t
NOTHROW_NCX(LIBCCALL libc_wcsnroff)(char32_t const *__restrict haystack,
                                    char32_t needle,
                                    size_t maxlen) {
#line 2165 "kos/src/libc/magic/string.c"
	return (size_t)(libc_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
INTERN WUNUSED ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnroff") size_t
NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack,
                                    char16_t needle,
                                    size_t maxlen) {
#line 2165 "kos/src/libc/magic/string.c"
	return (size_t)(libd_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.fuzzy_wmemcmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wmemcmp)(char32_t const *s1,
                                         size_t s1_chars,
                                         char32_t const *s2,
                                         size_t s2_chars) {
#line 1322 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return libc_fuzzy_memcmpw(s1, s1_chars, s2, s2_chars);
#elif 4 == 4
	return libc_fuzzy_memcmpl(s1, s1_chars, s2, s2_chars);
#else
	return libc_fuzzy_memcmp(s1, s1_chars * sizeof(char32_t), s2, s2_chars * sizeof(char32_t));
#endif
}
#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.fuzzy_wmemcmp") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcmp)(char16_t const *s1,
                                         size_t s1_chars,
                                         char16_t const *s2,
                                         size_t s2_chars) {
#line 1322 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return libc_fuzzy_memcmpw(s1, s1_chars, s2, s2_chars);
#elif 2 == 4
	return libc_fuzzy_memcmpl(s1, s1_chars, s2, s2_chars);
#else
	return libc_fuzzy_memcmp(s1, s1_chars * sizeof(char16_t), s2, s2_chars * sizeof(char16_t));
#endif
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.fuzzy_wcscmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wcscmp)(char32_t const *s1,
                                        char32_t const *s2) {
#line 1336 "kos/src/libc/magic/wchar.c"
	return libc_fuzzy_wmemcmp(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.fuzzy_wcscmp") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscmp)(char16_t const *s1,
                                        char16_t const *s2) {
#line 1336 "kos/src/libc/magic/wchar.c"
	return libd_fuzzy_wmemcmp(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.fuzzy_wcsncmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wcsncmp)(char32_t const *s1,
                                         size_t s1_maxlen,
                                         char32_t const *s2,
                                         size_t s2_maxlen) {
#line 1344 "kos/src/libc/magic/wchar.c"
	return libc_fuzzy_wmemcmp(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.fuzzy_wcsncmp") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncmp)(char16_t const *s1,
                                         size_t s1_maxlen,
                                         char16_t const *s2,
                                         size_t s2_maxlen) {
#line 1344 "kos/src/libc/magic/wchar.c"
	return libd_fuzzy_wmemcmp(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.fuzzy_wmemcasecmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wmemcasecmp)(char32_t const *s1,
                                             size_t s1_bytes,
                                             char32_t const *s2,
                                             size_t s2_bytes) {
#line 3657 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ char32_t const *temp = s1; s1 = s2; s2 = temp; }
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
			cost  = c1 != c2 && (char32_t)libc_towlower(c1) != (char32_t)libc_towlower(c2);
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
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.fuzzy_wmemcasecmp") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp)(char16_t const *s1,
                                             size_t s1_bytes,
                                             char16_t const *s2,
                                             size_t s2_bytes) {
#line 3657 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ char16_t const *temp = s1; s1 = s2; s2 = temp; }
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
			cost  = c1 != c2 && (char16_t)libc_towlower(c1) != (char16_t)libc_towlower(c2);
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		libc_memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		libc_memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		libc_memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		libc_memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.fuzzy_wcscasecmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wcscasecmp)(char32_t const *s1,
                                            char32_t const *s2) {
#line 1360 "kos/src/libc/magic/wchar.c"
	return libc_fuzzy_wmemcasecmp(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.fuzzy_wcscasecmp") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp)(char16_t const *s1,
                                            char16_t const *s2) {
#line 1360 "kos/src/libc/magic/wchar.c"
	return libd_fuzzy_wmemcasecmp(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.fuzzy_wcsncasecmp") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wcsncasecmp)(char32_t const *s1,
                                             size_t s1_maxlen,
                                             char32_t const *s2,
                                             size_t s2_maxlen) {
#line 1369 "kos/src/libc/magic/wchar.c"
	return libc_fuzzy_wmemcasecmp(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.fuzzy_wcsncasecmp") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp)(char16_t const *s1,
                                             size_t s1_maxlen,
                                             char16_t const *s2,
                                             size_t s2_maxlen) {
#line 1369 "kos/src/libc/magic/wchar.c"
	return libd_fuzzy_wmemcasecmp(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wildwcscmp") int
NOTHROW_NCX(LIBCCALL libc_wildwcscmp)(char32_t const *pattern,
                                      char32_t const *string) {
#line 3482 "kos/src/libc/magic/string.c"
	char32_t card_post;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)(char32_t)*pattern;
		}
		if (!*pattern)
			return (int)(char32_t)*string; /* Pattern end doesn't match */
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
				char32_t ch = *string++;
				if (ch == card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildwcscmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char32_t)card_post; /* Wildcard suffix not found */
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
	return (int)((char32_t)*string - (char32_t)*pattern);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wildwcscmp") int
NOTHROW_NCX(LIBDCALL libd_wildwcscmp)(char16_t const *pattern,
                                      char16_t const *string) {
#line 3482 "kos/src/libc/magic/string.c"
	char16_t card_post;
	for (;;) {
		if (!*string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			return -(int)(char16_t)*pattern;
		}
		if (!*pattern)
			return (int)(char16_t)*string; /* Pattern end doesn't match */
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
				char16_t ch = *string++;
				if (ch == card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wildwcscmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
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
	return (int)((char16_t)*string - (char16_t)*pattern);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.memory.wildwcscasecmp") int
NOTHROW_NCX(LIBCCALL libc_wildwcscasecmp)(char32_t const *pattern,
                                          char32_t const *string) {
#line 3526 "kos/src/libc/magic/string.c"
	char32_t card_post, pattern_ch, wcsing_ch;
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
			card_post = (char32_t)libc_towlower(card_post);
			for (;;) {
				char32_t ch = *string++;
				if (card_post == ch || card_post == (char32_t)libc_towlower(ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildwcscasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char32_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char32_t)libc_towlower(pattern_ch),
		    wcsing_ch = (char32_t)libc_towlower(wcsing_ch),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char32_t)wcsing_ch - (char32_t)pattern_ch);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wildwcscasecmp") int
NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp)(char16_t const *pattern,
                                          char16_t const *string) {
#line 3526 "kos/src/libc/magic/string.c"
	char16_t card_post, pattern_ch, wcsing_ch;
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
			card_post = (char16_t)libc_towlower(card_post);
			for (;;) {
				char16_t ch = *string++;
				if (card_post == ch || card_post == (char16_t)libc_towlower(ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wildwcscasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char16_t)libc_towlower(pattern_ch),
		    wcsing_ch = (char16_t)libc_towlower(wcsing_ch),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char16_t)wcsing_ch - (char16_t)pattern_ch);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcsverscmp") int
NOTHROW_NCX(LIBCCALL libc_wcsverscmp)(char32_t const *s1,
                                      char32_t const *s2) {
#line 625 "kos/src/libc/magic/string.c"
	char32_t const *s1_start = s1;
	char32_t c1, c2;
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
				return (int)((char32_t)c1 - (char32_t)c2);
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
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsverscmp") int
NOTHROW_NCX(LIBDCALL libd_wcsverscmp)(char16_t const *s1,
                                      char16_t const *s2) {
#line 625 "kos/src/libc/magic/string.c"
	char16_t const *s1_start = s1;
	char16_t c1, c2;
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
				return (int)((char16_t)c1 - (char16_t)c2);
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

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcsncoll_l") int
NOTHROW_NCX(LIBCCALL libc_wcsncoll_l)(char32_t const *s1,
                                      char32_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
#line 4037 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_wcsncoll(s1, s2, maxlen);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcsncoll_l") int
NOTHROW_NCX(LIBDCALL libd_wcsncoll_l)(char16_t const *s1,
                                      char16_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
#line 4037 "kos/src/libc/magic/string.c"
	(void)locale;
	return libd_wcsncoll(s1, s2, maxlen);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcscasecoll_l") int
NOTHROW_NCX(LIBCCALL libc_wcscasecoll_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         locale_t locale) {
#line 4043 "kos/src/libc/magic/string.c"
	return libc_wcscasecmp_l(s1, s2, locale);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcscasecoll_l") int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         locale_t locale) {
#line 4043 "kos/src/libc/magic/string.c"
	return libd_wcscasecmp_l(s1, s2, locale);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcsncasecoll_l") int
NOTHROW_NCX(LIBCCALL libc_wcsncasecoll_l)(char32_t const *s1,
                                          char32_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
#line 4049 "kos/src/libc/magic/string.c"
	(void)locale;
	return libc_wcsncasecoll(s1, s2, maxlen);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcsncasecoll_l") int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll_l)(char16_t const *s1,
                                          char16_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
#line 4049 "kos/src/libc/magic/string.c"
	(void)locale;
	return libd_wcsncasecoll(s1, s2, maxlen);
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcslwr_l") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcslwr_l)(char32_t *__restrict str,
                                    locale_t locale) {
#line 4056 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l(ch, locale);
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcslwr_l") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr_l)(char16_t *__restrict str,
                                    locale_t locale) {
#line 4056 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower_l(ch, locale);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcsupr_l") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsupr_l)(char32_t *__restrict str,
                                    locale_t locale) {
#line 4064 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l(ch, locale);
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcsupr_l") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr_l)(char16_t *__restrict str,
                                    locale_t locale) {
#line 4064 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper_l(ch, locale);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcsnlwr_l") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnlwr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
#line 4072 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l(ch, locale);
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcsnlwr_l") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
#line 4072 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower_l(ch, locale);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcsnupr_l") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnupr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
#line 4080 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l(ch, locale);
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcsnupr_l") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
#line 4080 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper_l(ch, locale);
	return str;
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wcscasestr_l") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcscasestr_l)(char32_t const *haystack,
                                        char32_t const *needle,
                                        locale_t locale) {
#line 2380 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack) {
		if (libc_wcscasecmp_l(haystack, needle, locale) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wcscasestr_l") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack,
                                        char16_t const *needle,
                                        locale_t locale) {
#line 2380 "kos/src/libc/magic/string.c"
	for (; *haystack; ++haystack) {
		if (libd_wcscasecmp_l(haystack, needle, locale) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.fuzzy_wmemcasecmp_l") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wmemcasecmp_l)(char32_t const *s1,
                                               size_t s1_bytes,
                                               char32_t const *s2,
                                               size_t s2_bytes,
                                               locale_t locale) {
#line 3773 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ char32_t const *temp = s1; s1 = s2; s2 = temp; }
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
			cost  = c1 != c2 && (char32_t)libc_towlower_l(c1, locale) != (char32_t)libc_towlower_l(c2, locale);
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
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.fuzzy_wmemcasecmp_l") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp_l)(char16_t const *s1,
                                               size_t s1_bytes,
                                               char16_t const *s2,
                                               size_t s2_bytes,
                                               locale_t locale) {
#line 3773 "kos/src/libc/magic/string.c"
	size_t *v0, *v1, i, j, cost, temp;
	if unlikely(!s1_bytes)
		return s2_bytes;
	if unlikely(!s2_bytes)
		return s1_bytes;
	if (s2_bytes > s1_bytes) {
		{ char16_t const *temp = s1; s1 = s2; s2 = temp; }
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
			cost  = c1 != c2 && (char16_t)libc_towlower_l(c1, locale) != (char16_t)libc_towlower_l(c2, locale);
			cost += v0[j];
			temp  = v1[j]+1;
			if (cost > temp) cost = temp;
			temp  = v0[j+1]+1;
			if (cost > temp) cost = temp;
			v1[j+1] = cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		libc_memcpyq((u64 *)v0, (u64 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		libc_memcpyl((u32 *)v0, (u32 *)v1, s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		libc_memcpyw((u16 *)v0, (u16 *)v1, s2_bytes);
#else
		libc_memcpy((u8 *)v0, (u8 *)v1, s2_bytes*sizeof(size_t));
#endif
	}
	temp = v1[s2_bytes];
	__freea(v1);
	__freea(v0);
	return temp;
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.fuzzy_wcscasecmp_l") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1,
                                              char32_t const *s2,
                                              locale_t locale) {
#line 1445 "kos/src/libc/magic/wchar.c"
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcslen(s1), s2, libc_wcslen(s2), locale);
}
#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.fuzzy_wcscasecmp_l") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1,
                                              char16_t const *s2,
                                              locale_t locale) {
#line 1445 "kos/src/libc/magic/wchar.c"
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcslen(s1), s2, libd_wcslen(s2), locale);
}

#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.fuzzy_wcsncasecmp_l") size_t
NOTHROW_NCX(LIBCCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1,
                                               size_t s1_maxlen,
                                               char32_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
#line 1453 "kos/src/libc/magic/wchar.c"
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen), locale);
}
#include <parts/malloca.h>
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.fuzzy_wcsncasecmp_l") size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1,
                                               size_t s1_maxlen,
                                               char16_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
#line 1453 "kos/src/libc/magic/wchar.c"
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen), locale);
}

INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.locale.memory.wildwcscasecmp_l") int
NOTHROW_NCX(LIBCCALL libc_wildwcscasecmp_l)(char32_t const *pattern,
                                            char32_t const *string,
                                            locale_t locale) {
#line 3723 "kos/src/libc/magic/string.c"
	char32_t card_post, pattern_ch, wcsing_ch;
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
			card_post = (char32_t)libc_towlower_l(card_post, locale);
			for (;;) {
				char32_t ch = *string++;
				if (card_post == ch || card_post == (char32_t)libc_towlower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wcscasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(char32_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char32_t)libc_towlower_l(pattern_ch, locale),
		    wcsing_ch = (char32_t)libc_towlower_l(wcsing_ch, locale),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char32_t)wcsing_ch - (char32_t)pattern_ch);
}
INTERN WUNUSED ATTR_PURE NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory.wildwcscasecmp_l") int
NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp_l)(char16_t const *pattern,
                                            char16_t const *string,
                                            locale_t locale) {
#line 3723 "kos/src/libc/magic/string.c"
	char16_t card_post, pattern_ch, wcsing_ch;
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
			card_post = (char16_t)libc_towlower_l(card_post, locale);
			for (;;) {
				char16_t ch = *string++;
				if (card_post == ch || card_post == (char16_t)libc_towlower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wcscasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		   (pattern_ch = (char16_t)libc_towlower_l(pattern_ch, locale),
		    wcsing_ch = (char16_t)libc_towlower_l(wcsing_ch, locale),
		    pattern_ch == wcsing_ch)) {
next:
			++string;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((char16_t)wcsing_ch - (char16_t)pattern_ch);
}

#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscat_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wcscat_s)(char32_t *dst,
                                    size_t dstsize,
                                    char32_t const *src) {
#line 4275 "kos/src/libc/magic/string.c"
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
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscat_s") errno_t
NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst,
                                    size_t dstsize,
                                    char16_t const *src) {
#line 4275 "kos/src/libc/magic/string.c"
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
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscpy_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wcscpy_s)(char32_t *dst,
                                    rsize_t dstsize,
                                    char32_t const *src) {
#line 4254 "kos/src/libc/magic/string.c"


	char32_t *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		libc_wmemset(dst, 0, dstsize);
		return __ERANGE;
	}
	libc_wmemset(iter, 0, remaining);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcscpy_s") errno_t
NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst,
                                    rsize_t dstsize,
                                    char16_t const *src) {
#line 4254 "kos/src/libc/magic/string.c"


	char16_t *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return __EINVAL;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		libd_wmemset(dst, 0, dstsize);
		return __ERANGE;
	}
	libd_wmemset(iter, 0, remaining);
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsncat_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wcsncat_s)(char32_t *dst,
                                     rsize_t dstsize,
                                     char32_t const *src,
                                     rsize_t maxlen) {
#line 4299 "kos/src/libc/magic/string.c"


	char32_t *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		libc_wmemset(dst, 0, dstsize);
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
		libc_wmemset(dst, 0, dstsize);
		return __ERANGE;
	}
	libc_wmemset(iter, 0, remaining);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsncat_s") errno_t
NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst,
                                     rsize_t dstsize,
                                     char16_t const *src,
                                     rsize_t maxlen) {
#line 4299 "kos/src/libc/magic/string.c"


	char16_t *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		libd_wmemset(dst, 0, dstsize);
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
		libd_wmemset(dst, 0, dstsize);
		return __ERANGE;
	}
	libd_wmemset(iter, 0, remaining);
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsncpy_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wcsncpy_s)(char32_t *dst,
                                     rsize_t dstsize,
                                     char32_t const *src,
                                     rsize_t maxlen) {
#line 4339 "kos/src/libc/magic/string.c"


	char32_t *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	if (!maxlen) {
		libc_wmemset(dst, 0, dstsize);
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
		libc_wmemset(dst, 0, dstsize);
		return __ERANGE;
	}
	libc_wmemset(iter, 0, remaining);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsncpy_s") errno_t
NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst,
                                     rsize_t dstsize,
                                     char16_t const *src,
                                     rsize_t maxlen) {
#line 4339 "kos/src/libc/magic/string.c"


	char16_t *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return __EINVAL;
	if (!maxlen) {
		libd_wmemset(dst, 0, dstsize);
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
		libd_wmemset(dst, 0, dstsize);
		return __ERANGE;
	}
	libd_wmemset(iter, 0, remaining);
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory._wcsnset_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wcsnset_s)(char32_t *buf,
                                      size_t buflen,
                                      char32_t ch,
                                      size_t maxlen) {
#line 4451 "kos/src/libc/magic/string.c"


	char32_t *iter;
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
		libc_wmemset(buf, 0, buflen);
		return __EINVAL;
	}
	libc_wmemset(iter, 0, remaining);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory._wcsnset_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *buf,
                                      size_t buflen,
                                      char16_t ch,
                                      size_t maxlen) {
#line 4451 "kos/src/libc/magic/string.c"


	char16_t *iter;
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
		*iter++ = (char16_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		libd_wmemset(buf, 0, buflen);
		return __EINVAL;
	}
	libd_wmemset(iter, 0, remaining);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory._wcsset_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wcsset_s)(char32_t *dst,
                                     size_t dstsize,
                                     char32_t ch) {
#line 4193 "kos/src/libc/magic/string.c"


	char32_t *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char32_t)ch;
	if (remaining == 0) {
		libc_wmemset(dst, 1, dstsize);
		return __EINVAL;
	}
	libc_wmemset(p, 0, remaining);
	return 0;
}
#include <parts/errno.h>
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory._wcsset_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst,
                                     size_t dstsize,
                                     char16_t ch) {
#line 4193 "kos/src/libc/magic/string.c"


	char16_t *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return __EINVAL;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char16_t)ch;
	if (remaining == 0) {
		libd_wmemset(dst, 1, dstsize);
		return __EINVAL;
	}
	libd_wmemset(p, 0, remaining);
	return 0;
}

#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory._wcslwr_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wcslwr_s)(char32_t *buf,
                                     size_t buflen) {
#line 4400 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower(ch);
	return 0;
}
#include <parts/errno.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory._wcslwr_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf,
                                     size_t buflen) {
#line 4400 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower(ch);
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory._wcsupr_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wcsupr_s)(char32_t *buf,
                                     size_t buflen) {
#line 4412 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper(ch);
	return 0;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory._wcsupr_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf,
                                     size_t buflen) {
#line 4412 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper(ch);
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory._wcslwr_s_l") errno_t
NOTHROW_NCX(LIBCCALL libc__wcslwr_s_l)(char32_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
#line 4424 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l(ch, locale);
	return 0;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory._wcslwr_s_l") errno_t
NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
#line 4424 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower_l(ch, locale);
	return 0;
}

INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory._wcsupr_s_l") errno_t
NOTHROW_NCX(LIBCCALL libc__wcsupr_s_l)(char32_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
#line 4436 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l(ch, locale);
	return 0;
}
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory._wcsupr_s_l") errno_t
NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
#line 4436 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	if (buf == NULL)
		return __EINVAL;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return __EINVAL;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper_l(ch, locale);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemcpy_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wmemcpy_s)(char32_t *dst,
                                     rsize_t dstlength,
                                     char32_t const *src,
                                     rsize_t srclength) {
#line 4217 "kos/src/libc/magic/string.c"


	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		libc_wmemset(dst, 0, dstlength);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	libc_wmemcpy(dst, src, srclength);
	return 0;
}
#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemcpy_s") errno_t
NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(char16_t *dst,
                                     rsize_t dstlength,
                                     char16_t const *src,
                                     rsize_t srclength) {
#line 4217 "kos/src/libc/magic/string.c"


	if (!srclength)
		return 0;
	if (dst == NULL)
		return __EINVAL;
	if (!src || dstlength < srclength) {
		libd_wmemset(dst, 0, dstlength);
		if (!src)
			return __EINVAL;
		if (dstlength < srclength)
			return __ERANGE;
		return __EINVAL;
	}
	libd_wmemcpy(dst, src, srclength);
	return 0;
}

#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemmove_s") errno_t
NOTHROW_NCX(LIBCCALL libc_wmemmove_s)(char32_t *dst,
                                      rsize_t dstlength,
                                      char32_t const *src,
                                      rsize_t srclength) {
#line 4239 "kos/src/libc/magic/string.c"

	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	libc_wmemmove(dst, src, srclength);
	return 0;
}
#include <parts/errno.h>
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wmemmove_s") errno_t
NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(char16_t *dst,
                                      rsize_t dstlength,
                                      char16_t const *src,
                                      rsize_t srclength) {
#line 4239 "kos/src/libc/magic/string.c"

	if (!srclength)
		return 0;
	if (!dst || !src)
		return __EINVAL;
	if (dstlength < srclength)
		return __ERANGE;
	libd_wmemmove(dst, src, srclength);
	return 0;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnset") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsnset)(char32_t *__restrict str,
                                   char32_t ch,
                                   size_t maxlen) {
#line 4169 "kos/src/libc/magic/string.c"
	char32_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsnset") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnset)(char16_t *__restrict str,
                                   char16_t ch,
                                   size_t maxlen) {
#line 4169 "kos/src/libc/magic/string.c"
	char16_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsrev") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsrev)(char32_t *__restrict str) {
#line 1632 "kos/src/libc/magic/wchar.c"
#if 4 == 2
	return (char32_t *)libc_memrevw(str, libc_wcslen(str));
#elif 4 == 4
	return (char32_t *)libc_memrevl(str, libc_wcslen(str));
#else
	return (char32_t *)libc_memrev(str, libc_wcslen(str) * sizeof(char32_t));
#endif
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsrev") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrev)(char16_t *__restrict str) {
#line 1632 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (char16_t *)libc_memrevw(str, libd_wcslen(str));
#elif 2 == 4
	return (char16_t *)libc_memrevl(str, libd_wcslen(str));
#else
	return (char16_t *)libc_memrev(str, libd_wcslen(str) * sizeof(char16_t));
#endif
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsset") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsset)(char32_t *__restrict str,
                                  char32_t ch) {
#line 4162 "kos/src/libc/magic/string.c"
	char32_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcsset") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsset)(char16_t *__restrict str,
                                  char16_t ch) {
#line 4162 "kos/src/libc/magic/string.c"
	char16_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcslwr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcslwr)(char32_t *__restrict str) {
#line 4147 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower(ch);
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcslwr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr)(char16_t *__restrict str) {
#line 4147 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towlower(ch);
	return str;
}

INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcsupr") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsupr)(char32_t *__restrict str) {
#line 4155 "kos/src/libc/magic/string.c"
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper(ch);
	return str;
}
INTERN ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory.wcsupr") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr)(char16_t *__restrict str) {
#line 4155 "kos/src/libc/magic/string.c"
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libc_towupper(ch);
	return str;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#undef swscanf
#undef swprintf
DEFINE_PUBLIC_WEAK_ALIAS(btowc, libc_btowc);
DEFINE_PUBLIC_WEAK_ALIAS(wctob, libc_wctob);
DEFINE_PUBLIC_WEAK_ALIAS(mbrtowc, libc_mbrtowc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$mbrtowc, libd_mbrtowc);
DEFINE_PUBLIC_WEAK_ALIAS(wcrtomb, libc_wcrtomb);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcrtomb, libd_wcrtomb);
DEFINE_PUBLIC_WEAK_ALIAS(mbrlen, libc_mbrlen);
DEFINE_PUBLIC_WEAK_ALIAS(__mbrlen, libc_mbrlen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$mbrlen, libd_mbrlen);
DEFINE_PUBLIC_WEAK_ALIAS(mbsrtowcs, libc_mbsrtowcs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$mbsrtowcs, libd_mbsrtowcs);
DEFINE_PUBLIC_WEAK_ALIAS(wcsrtombs, libc_wcsrtombs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsrtombs, libd_wcsrtombs);
DEFINE_PUBLIC_WEAK_ALIAS(wcstod, libc_wcstod);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstod, libd_wcstod);
DEFINE_PUBLIC_WEAK_ALIAS(wcstol, libc_wcstol);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstol, libd_wcstol);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoul, libc_wcstoul);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoul, libd_wcstoul);
DEFINE_PUBLIC_WEAK_ALIAS(mbsinit, libc_mbsinit);
DEFINE_PUBLIC_WEAK_ALIAS(wmemcmp, libc_wmemcmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmemcmp, libd_wmemcmp);
DEFINE_PUBLIC_WEAK_ALIAS(wmemcpy, libc_wmemcpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmemcpy, libd_wmemcpy);
DEFINE_PUBLIC_WEAK_ALIAS(wmemmove, libc_wmemmove);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmemmove, libd_wmemmove);
DEFINE_PUBLIC_WEAK_ALIAS(wmemset, libc_wmemset);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmemset, libd_wmemset);
DEFINE_PUBLIC_WEAK_ALIAS(wcscpy, libc_wcscpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscpy, libd_wcscpy);
DEFINE_PUBLIC_WEAK_ALIAS(wcscat, libc_wcscat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscat, libd_wcscat);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncat, libc_wcsncat);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncat, libd_wcsncat);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncpy, libc_wcsncpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncpy, libd_wcsncpy);
DEFINE_PUBLIC_WEAK_ALIAS(wcscmp, libc_wcscmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscmp, libd_wcscmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncmp, libc_wcsncmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncmp, libd_wcsncmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcscoll, libc_wcscoll);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscoll, libd_wcscoll);
DEFINE_PUBLIC_WEAK_ALIAS(wcsxfrm, libc_wcsxfrm);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsxfrm, libd_wcsxfrm);
DEFINE_PUBLIC_WEAK_ALIAS(wcsftime, libc_wcsftime);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsftime, libd_wcsftime);
DEFINE_PUBLIC_WEAK_ALIAS(wcstok, libc_wcstok);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstok, libd_wcstok);
DEFINE_PUBLIC_WEAK_ALIAS(wcslen, libc_wcslen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcslen, libd_wcslen);
DEFINE_PUBLIC_WEAK_ALIAS(wcsspn, libc_wcsspn);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsspn, libd_wcsspn);
DEFINE_PUBLIC_WEAK_ALIAS(wcscspn, libc_wcscspn);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscspn, libd_wcscspn);
DEFINE_PUBLIC_WEAK_ALIAS(wcschr, libc_wcschr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcschr, libd_wcschr);
DEFINE_PUBLIC_WEAK_ALIAS(wcsrchr, libc_wcsrchr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsrchr, libd_wcsrchr);
DEFINE_PUBLIC_WEAK_ALIAS(wcspbrk, libc_wcspbrk);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcspbrk, libd_wcspbrk);
DEFINE_PUBLIC_WEAK_ALIAS(wcsstr, libc_wcsstr);
DEFINE_PUBLIC_WEAK_ALIAS(wcswcs, libc_wcsstr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsstr, libd_wcsstr);
DEFINE_PUBLIC_WEAK_ALIAS(wmemchr, libc_wmemchr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmemchr, libd_wmemchr);
DEFINE_PUBLIC_WEAK_ALIAS(fwide, libc_fwide);
DEFINE_PUBLIC_WEAK_ALIAS(swscanf, libc_swscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$swscanf, libd_swscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vswprintf, libc_vswprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vswprintf, libd_vswprintf);
DEFINE_PUBLIC_WEAK_ALIAS(swprintf, libc_swprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$swprintf, libd_swprintf);
DEFINE_PUBLIC_WEAK_ALIAS(wcstof, libc_wcstof);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstof, libd_wcstof);
DEFINE_PUBLIC_WEAK_ALIAS(wcstold, libc_wcstold);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstold, libd_wcstold);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoll, libc_wcstoll);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoq, libc_wcstoll);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoll, libd_wcstoll);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoull, libc_wcstoull);
DEFINE_PUBLIC_WEAK_ALIAS(wcstouq, libc_wcstoull);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoull, libd_wcstoull);
DEFINE_PUBLIC_WEAK_ALIAS(vswscanf, libc_vswscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vswscanf, libd_vswscanf);
DEFINE_PUBLIC_WEAK_ALIAS(wcscasecmp, libc_wcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsicmp, libc_wcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcsicmp, libc_wcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscasecmp, libd_wcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncasecmp, libc_wcsncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsnicmp, libc_wcsncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnicmp, libc_wcsncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncasecmp, libd_wcsncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcscasecmp_l, libc_wcscasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsicmp_l, libc_wcscasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscasecmp_l, libd_wcscasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncasecmp_l, libc_wcsncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsnicmp_l, libc_wcsncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncasecmp_l, libd_wcsncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcscoll_l, libc_wcscoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcscoll_l, libc_wcscoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscoll_l, libd_wcscoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsxfrm_l, libc_wcsxfrm_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsxfrm_l, libc_wcsxfrm_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsxfrm_l, libd_wcsxfrm_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcpcpy, libc_wcpcpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcpcpy, libd_wcpcpy);
DEFINE_PUBLIC_WEAK_ALIAS(wcpncpy, libc_wcpncpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcpncpy, libd_wcpncpy);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnlen, libc_wcsnlen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnlen, libd_wcsnlen);
DEFINE_PUBLIC_WEAK_ALIAS(wcschrnul, libc_wcschrnul);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcschrnul, libd_wcschrnul);
DEFINE_PUBLIC_WEAK_ALIAS(wmempcpy, libc_wmempcpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmempcpy, libd_wmempcpy);
DEFINE_PUBLIC_WEAK_ALIAS(wmempmove, libc_wmempmove);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmempmove, libd_wmempmove);
DEFINE_PUBLIC_WEAK_ALIAS(wcstol_l, libc_wcstol_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstol_l, libd_wcstol_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoul_l, libc_wcstoul_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoul_l, libd_wcstoul_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoll_l, libc_wcstoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoll_l, libd_wcstoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstoull_l, libc_wcstoull_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstoull_l, libd_wcstoull_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstof_l, libc_wcstof_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstof_l, libd_wcstof_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstod_l, libc_wcstod_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstod_l, libd_wcstod_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcstold_l, libc_wcstold_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstold_l, libd_wcstold_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsftime_l, libc_wcsftime_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsftime_l, libd_wcsftime_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsend, libc_wcsend);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsend, libd_wcsend);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnend, libc_wcsnend);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnend, libd_wcsnend);
DEFINE_PUBLIC_WEAK_ALIAS(wcstou32, libc_wcstou32);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstou32, libd_wcstou32);
DEFINE_PUBLIC_WEAK_ALIAS(wcsto32, libc_wcsto32);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsto32, libd_wcsto32);
DEFINE_PUBLIC_WEAK_ALIAS(wcstou64, libc_wcstou64);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstou64, libd_wcstou64);
DEFINE_PUBLIC_WEAK_ALIAS(wcsto64, libc_wcsto64);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsto64, libd_wcsto64);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncoll, libc_wcsncoll);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncoll, libd_wcsncoll);
DEFINE_PUBLIC_WEAK_ALIAS(wcscasecoll, libc_wcscasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsicoll, libc_wcscasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(wcsicoll, libc_wcscasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscasecoll, libd_wcscasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncasecoll, libc_wcsncasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsncoll, libc_wcsncasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsnicoll, libc_wcsncasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncasecoll, libd_wcsncasecoll);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnrev, libc_wcsnrev);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnrev, libd_wcsnrev);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnlwr, libc_wcsnlwr);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnupr, libc_wcsnupr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnupr, libd_wcsnupr);
DEFINE_PUBLIC_WEAK_ALIAS(wcscasestr, libc_wcscasestr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscasestr, libd_wcscasestr);
DEFINE_PUBLIC_WEAK_ALIAS(wcspcpy, libc_wcspcpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcspcpy, libd_wcspcpy);
DEFINE_PUBLIC_WEAK_ALIAS(wcspncpy, libc_wcspncpy);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcspncpy, libd_wcspncpy);
DEFINE_PUBLIC_WEAK_ALIAS(wmempset, libc_wmempset);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmempset, libd_wmempset);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnchr, libc_wcsnchr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnchr, libd_wcsnchr);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnrchr, libc_wcsnrchr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnrchr, libd_wcsnrchr);
DEFINE_PUBLIC_WEAK_ALIAS(wcssep, libc_wcssep);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcssep, libd_wcssep);
DEFINE_PUBLIC_WEAK_ALIAS(wcsfry, libc_wcsfry);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsfry, libd_wcsfry);
DEFINE_PUBLIC_WEAK_ALIAS(wcsrchrnul, libc_wcsrchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsrchrnul, libd_wcsrchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnchrnul, libc_wcsnchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnchrnul, libd_wcsnchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnrchrnul, libc_wcsnrchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnrchrnul, libd_wcsnrchrnul);
DEFINE_PUBLIC_WEAK_ALIAS(wcsoff, libc_wcsoff);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsoff, libd_wcsoff);
DEFINE_PUBLIC_WEAK_ALIAS(wcsroff, libc_wcsroff);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsroff, libd_wcsroff);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnoff, libc_wcsnoff);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnoff, libd_wcsnoff);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnroff, libc_wcsnroff);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnroff, libd_wcsnroff);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wmemcmp, libc_fuzzy_wmemcmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wmemcmp, libd_fuzzy_wmemcmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wcscmp, libc_fuzzy_wcscmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wcscmp, libd_fuzzy_wcscmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wcsncmp, libc_fuzzy_wcsncmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wcsncmp, libd_fuzzy_wcsncmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wmemcasecmp, libc_fuzzy_wmemcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wmemcasecmp, libd_fuzzy_wmemcasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wcscasecmp, libc_fuzzy_wcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wcscasecmp, libd_fuzzy_wcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wcsncasecmp, libc_fuzzy_wcsncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wcsncasecmp, libd_fuzzy_wcsncasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(wildwcscmp, libc_wildwcscmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wildwcscmp, libd_wildwcscmp);
DEFINE_PUBLIC_WEAK_ALIAS(wildwcscasecmp, libc_wildwcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wildwcscasecmp, libd_wildwcscasecmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcsverscmp, libc_wcsverscmp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsverscmp, libd_wcsverscmp);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncoll_l, libc_wcsncoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsncoll_l, libc_wcsncoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncoll_l, libd_wcsncoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcscasecoll_l, libc_wcscasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsicoll_l, libc_wcscasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscasecoll_l, libd_wcscasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncasecoll_l, libc_wcsncasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsnicoll_l, libc_wcsncasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncasecoll_l, libd_wcsncasecoll_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcslwr_l, libc_wcslwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcslwr_l, libc_wcslwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcslwr_l, libd_wcslwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsupr_l, libc_wcsupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsupr_l, libc_wcsupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsupr_l, libd_wcsupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnlwr_l, libc_wcsnlwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnlwr_l, libd_wcsnlwr_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnupr_l, libc_wcsnupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnupr_l, libd_wcsnupr_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcscasestr_l, libc_wcscasestr_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscasestr_l, libd_wcscasestr_l);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wmemcasecmp_l, libc_fuzzy_wmemcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wmemcasecmp_l, libd_fuzzy_wmemcasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wcscasecmp_l, libc_fuzzy_wcscasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wcscasecmp_l, libd_fuzzy_wcscasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(fuzzy_wcsncasecmp_l, libc_fuzzy_wcsncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fuzzy_wcsncasecmp_l, libd_fuzzy_wcsncasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(wildwcscasecmp_l, libc_wildwcscasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wildwcscasecmp_l, libd_wildwcscasecmp_l);
DEFINE_PUBLIC_WEAK_ALIAS(wcscat_s, libc_wcscat_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscat_s, libd_wcscat_s);
DEFINE_PUBLIC_WEAK_ALIAS(wcscpy_s, libc_wcscpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcscpy_s, libd_wcscpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncat_s, libc_wcsncat_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncat_s, libd_wcsncat_s);
DEFINE_PUBLIC_WEAK_ALIAS(wcsncpy_s, libc_wcsncpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsncpy_s, libd_wcsncpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsnset_s, libc__wcsnset_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcsnset_s, libd__wcsnset_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsset_s, libc__wcsset_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcsset_s, libd__wcsset_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wcslwr_s, libc__wcslwr_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcslwr_s, libd__wcslwr_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsupr_s, libc__wcsupr_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcsupr_s, libd__wcsupr_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wcslwr_s_l, libc__wcslwr_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcslwr_s_l, libd__wcslwr_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsupr_s_l, libc__wcsupr_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcsupr_s_l, libd__wcsupr_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(wmemcpy_s, libc_wmemcpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmemcpy_s, libd_wmemcpy_s);
DEFINE_PUBLIC_WEAK_ALIAS(wmemmove_s, libc_wmemmove_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wmemmove_s, libd_wmemmove_s);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnset, libc_wcsnset);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsnset, libc_wcsnset);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnset, libd_wcsnset);
DEFINE_PUBLIC_WEAK_ALIAS(wcsrev, libc_wcsrev);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsrev, libc_wcsrev);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsrev, libd_wcsrev);
DEFINE_PUBLIC_WEAK_ALIAS(wcsset, libc_wcsset);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsset, libc_wcsset);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsset, libd_wcsset);
DEFINE_PUBLIC_WEAK_ALIAS(wcslwr, libc_wcslwr);
DEFINE_PUBLIC_WEAK_ALIAS(_wcslwr, libc_wcslwr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcslwr, libd_wcslwr);
DEFINE_PUBLIC_WEAK_ALIAS(wcsupr, libc_wcsupr);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsupr, libc_wcsupr);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsupr, libd_wcsupr);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_WCHAR_C */
