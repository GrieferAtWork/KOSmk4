/* HASH CRC-32:0xd31dd6e0 */
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
#ifndef GUARD_LIBC_AUTO_WCHAR_C
#define GUARD_LIBC_AUTO_WCHAR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/wchar.h"
#if !defined(LIBC_ARCH_HAVE_C16MEMCMP) && __SIZEOF_INT__ > 2
#include "../user/string.h"
#endif /* !LIBC_ARCH_HAVE_C16MEMCMP && __SIZEOF_INT__ > 2 */
#if !defined(LIBC_ARCH_HAVE_C32MEMCMP) && __SIZEOF_INT__ > 4
#include "../user/string.h"
#endif /* !LIBC_ARCH_HAVE_C32MEMCMP && __SIZEOF_INT__ > 4 */
#include "format-printer.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/unicode.h"
#include "wctype.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_btowc)(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint16_t)ch;
	return __WEOF16;
}
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc_btowc)(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint32_t)ch;
	return __WEOF32;
}
#include <asm/crt/stdio.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd_wctob)(wint16_t ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (int)ch;
	return EOF;
}
#include <asm/crt/stdio.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBKCALL libc_wctob)(wint32_t ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (int)ch;
	return EOF;
}
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_INTERN_ALIAS(libc_mbrtoc16, libd_mbrtowc);
DEFINE_INTERN_ALIAS(libc_c16rtomb, libd_wcrtomb);
#else /* __LIBCCALL_IS_LIBDCALL */
/* Because STDC mandates the uchar16 and uchar32 variants:
 *    mbrtowc:mbrtoc16:mbrtoc32
 *    wcrtomb:c16rtomb:c32rtomb
 * which are exposed in <uchar.h>, we need to be a little bit
 * more  careful when it comes to defining them on a platform
 * where the standard DOS calling convention differs from the
 * calling convention used by KOS (e.g. x86-64)
 *
 * In this scenario, magic will have already given the symbols:
 *   - LIBDCALL:DOS$mbrtowc:   size_t(wchar16_t *pwc, char const *str, size_t maxlen, mbstate_t *mbs);
 *     LIBDCALL:DOS$mbrtoc16:  ...
 *   - LIBKCALL:mbrtowc:       size_t(wchar32_t *pwc, char const *str, size_t maxlen, mbstate_t *mbs);
 *     LIBKCALL:mbrtoc32:      ...
 *     LIBDCALL:DOS$mbrtoc32:  ...  (msabi64-generator)
 *   - LIBDCALL:DOS$wcrtomb:   size_t(char *str, wchar16_t wc, mbstate_t *mbs);
 *     LIBDCALL:DOS$c16rtomb:  ...
 *   - LIBKCALL:wcrtomb:       size_t(char *str, wchar32_t wc, mbstate_t *mbs);
 *     LIBKCALL:c32rtomb:      ...
 *     LIBDCALL:DOS$c32rtomb:  ...  (msabi64-generator)
 *
 * However,  you can  see that this  system is still  lacking the LIBKCALL
 * variants of 2 functions that are only available as LIBDCALL (thus far):
 *     LIBKCALL:mbrtoc16:  ...
 *     LIBKCALL:c16rtomb:  ...
 *
 * And because the msabi64 generator doesn't include special handling for this case,
 * we  simply have to manually implement these  2 functions as LIBKCALL wrappers for
 * the associated LIBDCALL functions:
 *
 *     libc_mbrtoc16(...) { return libd_mbrtowc(...); }
 *     libc_c16rtomb(...) { return libd_wcrtomb(...); }
 */
DEFINE_PUBLIC_ALIAS(mbrtoc16, libc_mbrtoc16);
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_mbrtoc16)(char16_t *pwc,
                                    char const *__restrict str,
                                    size_t maxlen,
                                    mbstate_t *mbs) {
	return libd_mbrtowc(pwc, str, maxlen, mbs);
}

DEFINE_PUBLIC_ALIAS(c16rtomb, libc_c16rtomb);
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_c16rtomb)(char *__restrict str,
                                    char16_t wc,
                                    mbstate_t *mbs) {
	return libd_wcrtomb(str, wc, mbs);
}
#endif /* !__LIBCCALL_IS_LIBDCALL */
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <libc/errno.h>
/* >> mbrtowc(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBDCALL libd_mbrtowc)(char16_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *mbs) {
	size_t error;
	char16_t fallback_wc;
	if (mbs == NULL) {
		/* TODO: For whatever reason, libc4/5 exported this `mbrtowc_ps' as `_mb_shift' */
		static mbstate_t mbrtowc_ps = __MBSTATE_INIT;
		mbs = &mbrtowc_ps;
	}
	if (str == NULL) {
		mbstate_init(mbs);
		return 0;
	}
	if (maxlen == 0 || *str == '\0')
		return 0;
	if unlikely(pwc == NULL)
		pwc = &fallback_wc;

	error = libc_unicode_c8toc16((char16_t *)pwc, str, maxlen, mbs);




	if (error == (size_t)-1)
		(void)libc_seterrno(EILSEQ);

	return error;
}
#include <libc/errno.h>
/* >> mbrtowc(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_mbrtowc)(char32_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *mbs) {
	size_t error;
	char32_t fallback_wc;
	if (mbs == NULL) {
		/* TODO: For whatever reason, libc4/5 exported this `mbrtowc_ps' as `_mb_shift' */
		static mbstate_t mbrtowc_ps = __MBSTATE_INIT;
		mbs = &mbrtowc_ps;
	}
	if (str == NULL) {
		mbstate_init(mbs);
		return 0;
	}
	if (maxlen == 0 || *str == '\0')
		return 0;
	if unlikely(pwc == NULL)
		pwc = &fallback_wc;



	error = libc_unicode_c8toc32((char32_t *)pwc, str, maxlen, mbs);


	if (error == (size_t)-1)
		(void)libc_seterrno(EILSEQ);

	return error;
}
#include <libc/errno.h>
/* >> wcrtomb(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBDCALL libd_wcrtomb)(char *__restrict str,
                                   char16_t wc,
                                   mbstate_t *mbs) {
	char *endptr;
	size_t result;

	/* unicode_c16toc8() */
	if (!mbs) {
		static mbstate_t wcrtomb_ps = __MBSTATE_INIT;
		mbs = &wcrtomb_ps;
	}
	if (!str) {
		mbstate_init(mbs);
		return 1;
	}
	if ((mbs->__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		/* Complete surrogate */
		char32_t ch32;
		if unlikely(!((u16)wc >= 0xdc00 &&
		              (u16)wc <= 0xdfff)) {
			/* Expected low surrogate */

			(void)libc_seterrno(EILSEQ);

			return (size_t)-1;
		}
		ch32 = ((mbs->__mb_word & 0x000003ff) << 10) +
		       0x10000 + ((u16)wc - 0xdc00);
		mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
		endptr = libc_unicode_writeutf8(str, ch32);
	} else if ((u16)wc >= 0xd800 &&
	           (u16)wc <= 0xdbff) {
		mbs->__mb_word = __MBSTATE_TYPE_UTF16_LO | ((u16)wc - 0xd800);
		return 0;
	} else {
		endptr = libc_unicode_writeutf8(str, (char32_t)(u32)(u16)wc);
	}







	result = (size_t)(endptr - str);
	return result;
}
#include <libc/errno.h>
/* >> wcrtomb(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_wcrtomb)(char *__restrict str,
                                   char32_t wc,
                                   mbstate_t *mbs) {
	char *endptr;
	size_t result;

































	/* unicode_c32toc8() */
	(void)mbs;
	if (!str)
		return 1;
	endptr = libc_unicode_writeutf8(str, (char32_t)wc);

	result = (size_t)(endptr - str);
	return result;
}
/* >> mbrlen(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") WUNUSED size_t
NOTHROW_NCX(LIBDCALL libd_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *mbs) {
	char16_t wc;
	return libd_mbrtowc(&wc, str, maxlen, mbs);
}
/* >> mbrlen(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") WUNUSED size_t
NOTHROW_NCX(LIBKCALL libc_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *mbs) {
	char32_t wc;
	return libc_mbrtowc(&wc, str, maxlen, mbs);
}
/* >> mbsrtowcs(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_mbsrtowcs)(char16_t *__restrict dst,
                                     char const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libd_mbsnrtowcs(dst, psrc, (size_t)-1, dstlen, mbs);
}
/* >> mbsrtowcs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_mbsrtowcs)(char32_t *__restrict dst,
                                     char const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libc_mbsnrtowcs(dst, psrc, (size_t)-1, dstlen, mbs);
}
/* >> wcsrtombs(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsrtombs)(char *dst,
                                     char16_t const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libd_wcsnrtombs(dst, psrc, (size_t)-1, dstlen, mbs);
}
/* >> wcsrtombs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsrtombs)(char *dst,
                                     char32_t const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libc_wcsnrtombs(dst, psrc, (size_t)-1, dstlen, mbs);
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libd_wcstol, libd_wcsto32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libd_wcstol, libd_wcsto64);
#else /* ... */
/* >> wcstol(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_wcstol)(char16_t const *__restrict nptr,
                                  char16_t **endptr,
                                  __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (long)libd_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libd_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_wcstol, libc_wcsto32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_wcstol, libc_wcsto64);
#else /* ... */
/* >> wcstol(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) long
NOTHROW_NCX(LIBKCALL libc_wcstol)(char32_t const *__restrict nptr,
                                  char32_t **endptr,
                                  __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (long)libc_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (long)libc_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libd_wcstoul, libd_wcstou32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libd_wcstoul, libd_wcstou64);
#else /* ... */
/* >> wcstoul(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) unsigned long
NOTHROW_NCX(LIBDCALL libd_wcstoul)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libd_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)libd_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_wcstoul, libc_wcstou32);
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_wcstoul, libc_wcstou64);
#else /* ... */
/* >> wcstoul(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) unsigned long
NOTHROW_NCX(LIBKCALL libc_wcstoul)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG__ <= 4
	return (unsigned long)libc_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG__ <= 4 */
	return (unsigned long)libc_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG__ > 4 */
}
#endif /* !... */
/* >> mbsinit(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *mbs) {
	return !mbs || mbstate_isempty(mbs);
}
#if !defined(LIBC_ARCH_HAVE_C16MEMCMP) && __SIZEOF_INT__ > 2
/* >> wmemcmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wmemcmp)(char16_t const *s1,
                                   char16_t const *s2,
                                   size_t num_chars) {

	return (int)libc_memcmpw(s1, s2, num_chars);





}
#endif /* !LIBC_ARCH_HAVE_C16MEMCMP && __SIZEOF_INT__ > 2 */
#if !defined(LIBC_ARCH_HAVE_C32MEMCMP) && __SIZEOF_INT__ > 4
/* >> wmemcmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wmemcmp)(char32_t const *s1,
                                   char32_t const *s2,
                                   size_t num_chars) {



	return (int)libc_memcmpl(s1, s2, num_chars);



}
#endif /* !LIBC_ARCH_HAVE_C32MEMCMP && __SIZEOF_INT__ > 4 */
/* >> wcscpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
	return (char16_t *)libc_memcpyw(buf, src, libd_wcslen(src) + 1);
}
/* >> wcscpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscpy)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
	return (char32_t *)libc_memcpyl(buf, src, libc_wcslen(src) + 1);
}
/* >> wcscat(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
	(char16_t *)libc_memcpyw(libd_wcsend(buf), src, libd_wcslen(src) + 1);
	return buf;
}
/* >> wcscat(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscat)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
	(char32_t *)libc_memcpyl(libc_wcsend(buf), src, libc_wcslen(src) + 1);
	return buf;
}
/* >> wcsncat(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	char16_t *dst = libd_wcsend(buf);
	(char16_t *)libc_memcpyw(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}
/* >> wcsncat(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsncat)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	char32_t *dst = libc_wcsend(buf);
	(char32_t *)libc_memcpyl(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}
/* >> wcsncpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	(char16_t *)libc_memcpyw(buf, src, srclen);
	(char16_t *)libc_memsetw(buf+srclen, '\0', buflen - srclen);
	return buf;
}
/* >> wcsncpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	(char32_t *)libc_memcpyl(buf, src, srclen);
	(char32_t *)libc_memsetl(buf+srclen, '\0', buflen - srclen);
	return buf;
}
/* >> wcscmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscmp)(char16_t const *s1,
                                  char16_t const *s2) {
	char16_t c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}
/* >> wcscmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscmp)(char32_t const *s1,
                                  char32_t const *s2) {
	char32_t c1, c2;
	do {
		if unlikely((c1 = *s1++) != (c2 = *s2++))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
/* >> wcsncmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncmp)(char16_t const *s1,
                                   char16_t const *s2,
                                   size_t maxlen) {
	char16_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((char16_t)c1 - (char16_t)c2);
	} while (c1);
	return 0;
}
/* >> wcsncmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncmp)(char32_t const *s1,
                                   char32_t const *s2,
                                   size_t maxlen) {
	char32_t c1, c2;
	do {
		if (!maxlen--)
			break;
		if ((c1 = *s1++) != (c2 = *s2++))
			return (int)((char32_t)c1 - (char32_t)c2);
	} while (c1);
	return 0;
}
/* >> wcscoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1,
                                   char16_t const *s2) {
	/* XXX: Implement properly? */
	return libd_wcscmp(s1, s2);
}
/* >> wcscoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscoll)(char32_t const *s1,
                                   char32_t const *s2) {
	/* XXX: Implement properly? */
	return libc_wcscmp(s1, s2);
}
/* >> wcsxfrm(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst,
                                   char16_t const *__restrict src,
                                   size_t maxlen) {
	/* XXX: Implement properly? */
	size_t n = libd_wcsnlen(src, maxlen);
	libc_memcpy(dst, src, n * sizeof(char16_t));
	return n;
}
/* >> wcsxfrm(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsxfrm)(char32_t *dst,
                                   char32_t const *__restrict src,
                                   size_t maxlen) {
	/* XXX: Implement properly? */
	size_t n = libc_wcsnlen(src, maxlen);
	libc_memcpy(dst, src, n * sizeof(char32_t));
	return n;
}
#include <libc/template/stdstreams.h>
/* >> getwchar(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc") wint16_t
(LIBDCALL libd_getwchar)(void) THROWS(...) {
	return libd_fgetwc(stdin);
}
#include <libc/template/stdstreams.h>
/* >> getwchar(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc") wint32_t
(LIBKCALL libc_getwchar)(void) THROWS(...) {
	return libc_fgetwc(stdin);
}
#include <libc/template/stdstreams.h>
/* >> putwchar(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc") wint16_t
(LIBDCALL libd_putwchar)(char16_t wc) THROWS(...) {
	return libd_fputwc(wc, stdout);
}
#include <libc/template/stdstreams.h>
/* >> putwchar(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc") wint32_t
(LIBKCALL libc_putwchar)(char32_t wc) THROWS(...) {
	return libc_fputwc(wc, stdout);
}
#include <libc/errno.h>
#include <asm/crt/stdio.h>
/* >> fgetws(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") WUNUSED NONNULL((1, 3)) char16_t *
(LIBDCALL libd_fgetws)(char16_t *__restrict buf,
                       __STDC_INT_AS_SIZE_T bufsize,
                       FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */

		(void)libc_seterrno(ERANGE);

		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint16_t ch = libd_fgetwc(stream);
		if (ch == __WEOF16) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libd_fgetwc(stream);
			if (ch == __WEOF16) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libd_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
#include <libc/errno.h>
#include <asm/crt/stdio.h>
/* >> fgetws(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.read") WUNUSED NONNULL((1, 3)) char32_t *
(LIBKCALL libc_fgetws)(char32_t *__restrict buf,
                       __STDC_INT_AS_SIZE_T bufsize,
                       FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */

		(void)libc_seterrno(ERANGE);

		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint32_t ch = libc_fgetwc(stream);
		if (ch == __WEOF32) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetwc(stream);
			if (ch == __WEOF32) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/* >> fputws(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_fputws)(char16_t const *__restrict str,
                       FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter(stream, str, libd_wcslen(str));
	return result;
}
/* >> fputws(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_fputws)(char32_t const *__restrict str,
                       FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter(stream, str, libc_wcslen(str));
	return result;
}
/* >> wcsftime(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.strftime") ATTR_LIBC_C16FTIME(3, 0) NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsftime)(char16_t *__restrict buf,
                                    size_t buflen,
                                    char16_t const *__restrict format,
                                    struct tm const *__restrict tp) {
	if (buflen)
		*buf = 0;
	/* TODO */
	(void)format;
	(void)tp;
	return 0;
}
/* >> wcsftime(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.strftime") ATTR_LIBC_C32FTIME(3, 0) NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsftime)(char32_t *__restrict buf,
                                    size_t buflen,
                                    char32_t const *__restrict format,
                                    struct tm const *__restrict tp) {
	if (buflen)
		*buf = 0;
	/* TODO */
	(void)format;
	(void)tp;
	return 0;
}
/* >> wcstok(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((2, 3)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcstok)(char16_t *str,
                                  char16_t const *__restrict delim,
                                  char16_t **__restrict save_ptr) {
	char16_t *end;
	if (!str)
		str = *save_ptr;
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	str += libd_wcsspn(str, delim);
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	end = str + libd_wcscspn(str, delim);
	if (!*end) {
		*save_ptr = end;
		return str;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return str;
}
/* >> wcstok(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") NONNULL((2, 3)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcstok)(char32_t *str,
                                  char32_t const *__restrict delim,
                                  char32_t **__restrict save_ptr) {
	char32_t *end;
	if (!str)
		str = *save_ptr;
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	str += libc_wcsspn(str, delim);
	if (!*str) {
		*save_ptr = str;
		return NULL;
	}
	end = str + libc_wcscspn(str, delim);
	if (!*end) {
		*save_ptr = end;
		return str;
	}
	*end = '\0';
	*save_ptr = end + 1;
	return str;
}
#ifndef LIBC_ARCH_HAVE_C16SLEN
/* >> wcslen(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict str) {
	return (size_t)(libd_wcsend(str) - str);
}
#endif /* !LIBC_ARCH_HAVE_C16SLEN */
#ifndef LIBC_ARCH_HAVE_C32SLEN
/* >> wcslen(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcslen)(char32_t const *__restrict str) {
	return (size_t)(libc_wcsend(str) - str);
}
#endif /* !LIBC_ARCH_HAVE_C32SLEN */
/* >> wcsspn(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack,
                                  char16_t const *accept) {
	char16_t const *iter = haystack;
	while (*iter && libd_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
/* >> wcsspn(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsspn)(char32_t const *haystack,
                                  char32_t const *accept) {
	char32_t const *iter = haystack;
	while (*iter && libc_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#include <hybrid/typecore.h>
/* >> wcscspn(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack,
                                   char16_t const *reject) {
	char16_t const *iter = haystack;
	while (*iter && !libd_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
#include <hybrid/typecore.h>
/* >> wcscspn(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcscspn)(char32_t const *haystack,
                                   char32_t const *reject) {
	char32_t const *iter = haystack;
	while (*iter && !libc_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
/* >> wcschr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcschr)(char16_t const *__restrict haystack,
                                  char16_t needle) {
	for (;; ++haystack) {
		char16_t ch = *haystack;
		if unlikely((char16_t)ch == (char16_t)needle)
			return (char16_t *)haystack;
		if (!ch)
			break;
	}
	return NULL;
}
/* >> wcschr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcschr)(char32_t const *__restrict haystack,
                                  char32_t needle) {
	for (;; ++haystack) {
		char32_t ch = *haystack;
		if unlikely((char32_t)ch == (char32_t)needle)
			return (char32_t *)haystack;
		if (!ch)
			break;
	}
	return NULL;
}
/* >> wcsrchr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrchr)(char16_t const *__restrict haystack,
                                   char16_t needle) {
	char16_t const *result = NULL;
	for (;; ++haystack) {
		char16_t ch = *haystack;
		if unlikely((char16_t)ch == (char16_t)needle)
			result = haystack;
		if (!ch)
			break;
	}
	return (char16_t *)result;
}
/* >> wcsrchr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrchr)(char32_t const *__restrict haystack,
                                   char32_t needle) {
	char32_t const *result = NULL;
	for (;; ++haystack) {
		char32_t ch = *haystack;
		if unlikely((char32_t)ch == (char32_t)needle)
			result = haystack;
		if (!ch)
			break;
	}
	return (char32_t *)result;
}
/* >> wcspbrk(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack,
                                   char16_t const *accept) {
	char16_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		char16_t const *ned_iter;
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char16_t *)haystack - 1;
		}
	}
	return NULL;
}
/* >> wcspbrk(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspbrk)(char32_t const *haystack,
                                   char32_t const *accept) {
	char32_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		char32_t const *ned_iter;
		ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char32_t *)haystack - 1;
		}
	}
	return NULL;
}
/* >> wcsstr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsstr)(char16_t const *haystack,
                                  char16_t const *needle) {
	char16_t ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char16_t const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char16_t *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}
/* >> wcsstr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsstr)(char32_t const *haystack,
                                  char32_t const *needle) {
	char32_t ch, needle_start = *needle++;
	while ((ch = *haystack++) != '\0') {
		if (ch == needle_start) {
			char32_t const *hay2, *ned_iter;
			hay2     = haystack;
			ned_iter = needle;
			while ((ch = *ned_iter++) != '\0') {
				if (*hay2++ != ch)
					goto miss;
			}
			return (char32_t *)haystack - 1;
		}
miss:
		;
	}
	return NULL;
}
/* >> fwide(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.utility") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_fwide)(FILE *fp,
                                 int mode) {
	(void)fp;
	(void)mode;
	COMPILER_IMPURE();
	return 0;
}
/* >> fwprintf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_C16PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwprintf)(FILE *__restrict stream,
                          char16_t const *__restrict format,
                          ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwprintf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_C32PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwprintf)(FILE *__restrict stream,
                          char32_t const *__restrict format,
                          ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
/* >> vfwprintf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_C16PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwprintf)(FILE *__restrict stream,
                          char16_t const *__restrict format,
                          va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter, stream, format, args);
}
/* >> vfwprintf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_C32PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vfwprintf)(FILE *__restrict stream,
                          char32_t const *__restrict format,
                          va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter, stream, format, args);
}
/* >> wprintf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_C16PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wprintf)(char16_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf(format, args);
	va_end(args);
	return result;
}
/* >> wprintf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_C32PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wprintf)(char32_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf(format, args);
	va_end(args);
	return result;
}
#include <libc/template/stdstreams.h>
/* >> vwprintf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwprintf)(char16_t const *__restrict format,
                         va_list args) THROWS(...) {
	return libd_vfwprintf(stdout, format, args);
}
#include <libc/template/stdstreams.h>
/* >> vwprintf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwprintf)(char32_t const *__restrict format,
                         va_list args) THROWS(...) {
	return libc_vfwprintf(stdout, format, args);
}
/* >> fwscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwscanf)(FILE *__restrict stream,
                         char16_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwscanf)(FILE *__restrict stream,
                         char32_t const *__restrict format,
                         ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
/* >> wscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_LIBC_C16SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wscanf)(char16_t const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf(format, args);
	va_end(args);
	return result;
}
/* >> wscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") ATTR_LIBC_C32SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wscanf)(char32_t const *__restrict format,
                        ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwscanf(format, args);
	va_end(args);
	return result;
}
/* >> swscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf") ATTR_LIBC_C16SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_swscanf)(char16_t const *__restrict src,
                                    char16_t const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswscanf(src, format, args);
	va_end(args);
	return result;
}
/* >> swscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf") ATTR_LIBC_C32SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBKCALL libc_swscanf)(char32_t const *__restrict src,
                                    char32_t const *__restrict format,
                                    ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswscanf(src, format, args);
	va_end(args);
	return result;
}
#ifndef ____format_c16snprintf_data_defined
#define ____format_c16snprintf_data_defined
struct __format_c16snprintf_data {
	char16_t      *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_c16snprintf_data_defined */
/* >> vswprintf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vswprintf)(char16_t *__restrict buf,
                                     size_t buflen,
                                     char16_t const *__restrict format,
                                     va_list args) {
	struct __format_c16snprintf_data data;
	__STDC_INT_AS_SSIZE_T result;
	data.__sd_buffer = buf;
	data.__sd_bufsiz = buflen;
	result = (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_format_wsnprintf_printer,
	                                                (void *)&data, format, args);
	if (result >= 0) {
		if (data.__sd_bufsiz != 0) {
			*data.__sd_buffer = (char16_t)'\0';
		} else {
			if (buflen != 0)
				buf[buflen - 1] = (char16_t)'\0';
		}
	}
	return result;
}
#ifndef ____format_c32snprintf_data_defined
#define ____format_c32snprintf_data_defined
struct __format_c32snprintf_data {
	char32_t      *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_c32snprintf_data_defined */
/* >> vswprintf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 0) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBKCALL libc_vswprintf)(char32_t *__restrict buf,
                                     size_t buflen,
                                     char32_t const *__restrict format,
                                     va_list args) {
	struct __format_c32snprintf_data data;
	__STDC_INT_AS_SSIZE_T result;
	data.__sd_buffer = buf;
	data.__sd_bufsiz = buflen;
	result = (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_format_wsnprintf_printer,
	                                                (void *)&data, format, args);
	if (result >= 0) {
		if (data.__sd_bufsiz != 0) {
			*data.__sd_buffer = (char32_t)'\0';
		} else {
			if (buflen != 0)
				buf[buflen - 1] = (char32_t)'\0';
		}
	}
	return result;
}
/* >> swprintf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_LIBC_C16PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBDCALL libd_swprintf)(char16_t *__restrict buf,
                                     size_t buflen,
                                     char16_t const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vswprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
/* >> swprintf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf") ATTR_LIBC_C32PRINTF(3, 4) NONNULL((3)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(VLIBKCALL libc_swprintf)(char32_t *__restrict buf,
                                     size_t buflen,
                                     char32_t const *__restrict format,
                                     ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vswprintf(buf, buflen, format, args);
	va_end(args);
	return result;
}
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END


#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char32_t result = libc_unicode_readutf16(&reader);
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */




__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END
/* >> wcstod(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
	double result;
	char16_t const *text_pointer = nptr;






	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                  (void *)&text_pointer, "%lf", &result))
		result = 0.0;






	if (endptr)
		*endptr = (char16_t *)text_pointer;
	return result;
}
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END




__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END


#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */
/* >> wcstod(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc_wcstod)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
	double result;
	char32_t const *text_pointer = nptr;











	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                  (void *)&text_pointer, "%lf", &result))
		result = 0.0;

	if (endptr)
		*endptr = (char32_t *)text_pointer;
	return result;
}
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END


#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char32_t result = libc_unicode_readutf16(&reader);
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */




__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END
/* >> wcstof(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) float
NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
	float result;
	char16_t const *text_pointer = nptr;






	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                  (void *)&text_pointer, "%f", &result))
		result = 0.0f;






	if (endptr)
		*endptr = (char16_t *)text_pointer;
	return result;
}
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END




__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END


#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */
/* >> wcstof(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) float
NOTHROW_NCX(LIBKCALL libc_wcstof)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
	float result;
	char32_t const *text_pointer = nptr;











	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                  (void *)&text_pointer, "%f", &result))
		result = 0.0f;

	if (endptr)
		*endptr = (char32_t *)text_pointer;
	return result;
}
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END


#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) ssize_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char32_t result = libc_unicode_readutf16(&reader);
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	libc_unicode_readutf16_rev((char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */




__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END
/* >> wcstold(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr,
                                   char16_t **endptr) {
	__LONGDOUBLE result;
	char16_t const *text_pointer = nptr;






	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                  (void *)&text_pointer, "%Lf", &result))
		result = 0.0L;






	if (endptr)
		*endptr = (char16_t *)text_pointer;
	return result;
}
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END




__NAMESPACE_LOCAL_BEGIN














__NAMESPACE_LOCAL_END


#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) ssize_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, char32_t UNUSED(ch)) {
	--*(char32_t const **)arg;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */
/* >> wcstold(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBKCALL libc_wcstold)(char32_t const *__restrict nptr,
                                   char32_t **endptr) {
	__LONGDOUBLE result;
	char32_t const *text_pointer = nptr;











	if (!libc_format_scanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                  &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                  (void *)&text_pointer, "%Lf", &result))
		result = 0.0L;

	if (endptr)
		*endptr = (char32_t *)text_pointer;
	return result;
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libd_wcstoll, libd_wcsto64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libd_wcstoll, libd_wcsto32);
#else /* ... */
/* >> wcstoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoll)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libd_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libd_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_wcstoll, libc_wcsto64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_wcstoll, libc_wcsto32);
#else /* ... */
/* >> wcstoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoll)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__LONGLONG)libc_wcsto32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__LONGLONG)libc_wcsto64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libd_wcstoull, libd_wcstou64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libd_wcstoull, libd_wcstou32);
#else /* ... */
/* >> wcstoull(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoull)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libd_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)libd_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS(libc_wcstoull, libc_wcstou64);
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS(libc_wcstoull, libc_wcstou32);
#else /* ... */
/* >> wcstoull(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoull)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {
#if __SIZEOF_LONG_LONG__ <= 4
	return (__ULONGLONG)libc_wcstou32(nptr, endptr, base);
#else /* __SIZEOF_LONG_LONG__ <= 4 */
	return (__ULONGLONG)libc_wcstou64(nptr, endptr, base);
#endif /* __SIZEOF_LONG_LONG__ > 4 */
}
#endif /* !... */
#include <libc/template/stdstreams.h>
/* >> vwscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwscanf)(char16_t const *__restrict format,
                        va_list args) THROWS(...) {
	return libd_vfwscanf(stdin, format, args);
}
#include <libc/template/stdstreams.h>
/* >> vwscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwscanf)(char32_t const *__restrict format,
                        va_list args) THROWS(...) {
	return libc_vfwscanf(stdin, format, args);
}
/* >> vswscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vswscanf)(char16_t const *__restrict src,
                                    char16_t const *__restrict format,
                                    va_list args) {
	/* TODO: format_wscanf() */
	(void)src;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
/* >> vswscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBKCALL libc_vswscanf)(char32_t const *__restrict src,
                                    char32_t const *__restrict format,
                                    va_list args) {
	/* TODO: format_wscanf() */
	(void)src;
	(void)format;
	(void)args;
	COMPILER_IMPURE();
	return 0;
}
/* >> wcscasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecmp)(char16_t const *s1,
                                      char16_t const *s2) {
	char16_t c1, c2;
	do {
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char16_t)libd_towlower((char16_t)c1);
			c2 = (char16_t)libd_towlower((char16_t)c2);
			if (c1 != c2)
				return (int)((char16_t)c1 - (char16_t)c2);
		}
	} while (c1 != '\0');
	return 0;
}
/* >> wcscasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecmp)(char32_t const *s1,
                                      char32_t const *s2) {
	char32_t c1, c2;
	do {
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char32_t)libc_towlower((char32_t)c1);
			c2 = (char32_t)libc_towlower((char32_t)c2);
			if (c1 != c2)
				return (int)((char32_t)c1 - (char32_t)c2);
		}
	} while (c1 != '\0');
	return 0;
}
/* >> wcsncasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecmp)(char16_t const *s1,
                                       char16_t const *s2,
                                       size_t maxlen) {
	char16_t c1, c2;
	do {
		if (!maxlen--)
			break;
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char16_t)libd_towlower((char16_t)c1);
			c2 = (char16_t)libd_towlower((char16_t)c2);
			if (c1 != c2)
				return (int)((char16_t)c1 - (char16_t)c2);
		}
	} while (c1 != '\0');
	return 0;
}
/* >> wcsncasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecmp)(char32_t const *s1,
                                       char32_t const *s2,
                                       size_t maxlen) {
	char32_t c1, c2;
	do {
		if (!maxlen--)
			break;
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2) {
			c1 = (char32_t)libc_towlower((char32_t)c1);
			c2 = (char32_t)libc_towlower((char32_t)c2);
			if (c1 != c2)
				return (int)((char32_t)c1 - (char32_t)c2);
		}
	} while (c1 != '\0');
	return 0;
}
/* >> wcscasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecmp_l)(char16_t const *s1,
                                        char16_t const *s2,
                                        locale_t locale) {
	(void)locale;
	return libd_wcscasecmp(s1, s2);
}
/* >> wcscasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecmp_l)(char32_t const *s1,
                                        char32_t const *s2,
                                        locale_t locale) {
	(void)locale;
	return libc_wcscasecmp(s1, s2);
}
/* >> wcsncasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecmp_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libd_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcsncasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecmp_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libc_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcscoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscoll_l)(char16_t const *s1,
                                     char16_t const *s2,
                                     locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libd_wcscoll(s1, s2);
}
/* >> wcscoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscoll_l)(char32_t const *s1,
                                     char32_t const *s2,
                                     locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_wcscoll(s1, s2);
}
/* >> wcsxfrm_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm_l)(char16_t *dst,
                                     char16_t const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsxfrm(dst, src, maxlen);
}
/* >> wcsxfrm_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsxfrm_l)(char32_t *dst,
                                     char32_t const *__restrict src,
                                     size_t maxlen,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsxfrm(dst, src, maxlen);
}
/* >> wcpcpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpcpy)(char16_t *__restrict dst,
                                  char16_t const *__restrict src) {
	return (char16_t *)libc_mempcpyw(dst, src, libd_wcslen(src) + 1);
}
/* >> wcpcpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcpcpy)(char32_t *__restrict dst,
                                  char32_t const *__restrict src) {
	return (char32_t *)libc_mempcpyl(dst, src, libc_wcslen(src) + 1);
}
/* >> wcpncpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	(char16_t *)libc_memcpyw(buf, src, srclen);
	(char16_t *)libc_memsetw(buf + srclen, '\0', (size_t)(buflen - srclen));
	return buf + srclen;
}
/* >> wcpncpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcpncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	(char32_t *)libc_memcpyl(buf, src, srclen);
	(char32_t *)libc_memsetl(buf + srclen, '\0', (size_t)(buflen - srclen));
	return buf + srclen;
}
/* >> mbsnrtowcs(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_mbsnrtowcs)(char16_t *__restrict dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t dstlen,
                                      mbstate_t *mbs) {
	size_t result = 0;
	char const *src = *psrc;
	if (nmc) {
		while (dstlen) {
			size_t error;
			char16_t wc;
			if (nmc >= 7) {
				error = libd_mbrtowc(&wc, src, (size_t)-1, mbs);
			} else {
				char temp[7];
				libc_bzero(libc_mempcpy(temp, src, nmc), 7 - nmc);
				error = libd_mbrtowc(&wc, temp, (size_t)-1, mbs);
			}
			if (!error) {
				src = NULL; /* NUL-character reached */
				break;
			}
			if (error == (size_t)-1) {
				result = (size_t)-1; /* EILSEQ */
				break;
			}
			if (dst != NULL)
				*dst++ = wc;
			--dstlen;
			++result;
			if (error >= nmc) {
				src = NULL; /* (implicit) NUL-character reached */
				break;
			}
			src += error;
			nmc -= error;
		}
	} else {
		src = NULL; /* (implicit) NUL-character reached */
	}
	if (dst != NULL)
		*psrc = src; /* Only update source if destination was given */
	return result;
}
/* >> mbsnrtowcs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_mbsnrtowcs)(char32_t *__restrict dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t dstlen,
                                      mbstate_t *mbs) {
	size_t result = 0;
	char const *src = *psrc;
	if (nmc) {
		while (dstlen) {
			size_t error;
			char32_t wc;
			if (nmc >= 7) {
				error = libc_mbrtowc(&wc, src, (size_t)-1, mbs);
			} else {
				char temp[7];
				libc_bzero(libc_mempcpy(temp, src, nmc), 7 - nmc);
				error = libc_mbrtowc(&wc, temp, (size_t)-1, mbs);
			}
			if (!error) {
				src = NULL; /* NUL-character reached */
				break;
			}
			if (error == (size_t)-1) {
				result = (size_t)-1; /* EILSEQ */
				break;
			}
			if (dst != NULL)
				*dst++ = wc;
			--dstlen;
			++result;
			if (error >= nmc) {
				src = NULL; /* (implicit) NUL-character reached */
				break;
			}
			src += error;
			nmc -= error;
		}
	} else {
		src = NULL; /* (implicit) NUL-character reached */
	}
	if (dst != NULL)
		*psrc = src; /* Only update source if destination was given */
	return result;
}
/* >> wcsnrtombs(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnrtombs)(char *dst,
                                      char16_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t dstlen,
                                      mbstate_t *mbs) {
	size_t result = 0;
	char16_t const *src = *psrc;
	while (dstlen) {
		size_t error;
		char buf[7];
		char16_t ch;
		if (!nwc) {
			src = NULL; /* (implicit) NUL-character reached */
			break;
		}
		ch = *src;
		error = libd_wcrtomb(buf, ch, mbs);
		if (error == (size_t)-1) {
			result = (size_t)-1; /* EILSEQ */
			break;
		}
		if (error > dstlen)
			break;
		if (dst != NULL)
			dst = (char *)libc_mempcpy(dst, buf, error);
		result += error;
		dstlen -= error;
		++src;
		--nwc;
		if (ch == '\0') {
			src = NULL; /* NUL-character reached */
			break;
		}
	}
	if (dst != NULL)
		*psrc = src; /* Only update source if destination was given */
	return result;
}
/* >> wcsnrtombs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnrtombs)(char *dst,
                                      char32_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t dstlen,
                                      mbstate_t *mbs) {
	size_t result = 0;
	char32_t const *src = *psrc;
	while (dstlen) {
		size_t error;
		char buf[7];
		char32_t ch;
		if (!nwc) {
			src = NULL; /* (implicit) NUL-character reached */
			break;
		}
		ch = *src;
		error = libc_wcrtomb(buf, ch, mbs);
		if (error == (size_t)-1) {
			result = (size_t)-1; /* EILSEQ */
			break;
		}
		if (error > dstlen)
			break;
		if (dst != NULL)
			dst = (char *)libc_mempcpy(dst, buf, error);
		result += error;
		dstlen -= error;
		++src;
		--nwc;
		if (ch == '\0') {
			src = NULL; /* NUL-character reached */
			break;
		}
	}
	if (dst != NULL)
		*psrc = src; /* Only update source if destination was given */
	return result;
}
#ifndef LIBC_ARCH_HAVE_C16SNLEN
/* >> wcsnlen(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict str,
                                   size_t maxlen) {
	return (size_t)(libd_wcsnend(str, maxlen) - str);
}
#endif /* !LIBC_ARCH_HAVE_C16SNLEN */
#ifndef LIBC_ARCH_HAVE_C32SNLEN
/* >> wcsnlen(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnlen)(char32_t const *__restrict str,
                                   size_t maxlen) {
	return (size_t)(libc_wcsnend(str, maxlen) - str);
}
#endif /* !LIBC_ARCH_HAVE_C32SNLEN */
#include <hybrid/typecore.h>
/* >> wcsdup(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsdup)(char16_t const *__restrict string) {
	size_t resultsize = (libd_wcslen(string) + 1) * sizeof(char16_t);
	char16_t *result = (char16_t *)libc_malloc(resultsize);
	if likely(result)
		libc_memcpy(result, string, resultsize);
	return result;
}
#include <hybrid/typecore.h>
/* >> wcsdup(3) */
INTERN ATTR_SECTION(".text.crt.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsdup)(char32_t const *__restrict string) {
	size_t resultsize = (libc_wcslen(string) + 1) * sizeof(char32_t);
	char32_t *result = (char32_t *)libc_malloc(resultsize);
	if likely(result)
		libc_memcpy(result, string, resultsize);
	return result;
}
#include <libc/unicode.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd_wcwidth)(char16_t ch) {
	if (__libc_unicode_isprint(ch))
		return 1;
	if (ch == 0)
		return 0;
	return -1;
}
#include <libc/unicode.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBKCALL libc_wcwidth)(char32_t ch) {
	if (__libc_unicode_isprint(ch))
		return 1;
	if (ch == 0)
		return 0;
	return -1;
}
/* >> wcswidth(3)
 * Returns the number of columns needed to display `str...+=wcslen(str, num_chars)'
 * in a system terminal. If any of the contained characters cannot be printed, then
 * `-1' is returned. (s.a. `wcwidth(3)') */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) __STDC_INT32_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_wcswidth)(char16_t const *__restrict str,
                                    size_t num_chars) {
	int temp;
	__STDC_INT32_AS_SSIZE_T result = 0;
	for (; num_chars; ++str, --num_chars) {
		char16_t ch = *str;
		if (!ch)
			break;
		temp = libd_wcwidth(ch);
		if (temp < 0)
			return temp;
		result += temp;
	}
	return result;
}
/* >> wcswidth(3)
 * Returns the number of columns needed to display `str...+=wcslen(str, num_chars)'
 * in a system terminal. If any of the contained characters cannot be printed, then
 * `-1' is returned. (s.a. `wcwidth(3)') */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED NONNULL((1)) __STDC_INT32_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc_wcswidth)(char32_t const *__restrict str,
                                    size_t num_chars) {
	int temp;
	__STDC_INT32_AS_SSIZE_T result = 0;
	for (; num_chars; ++str, --num_chars) {
		char32_t ch = *str;
		if (!ch)
			break;
		temp = libc_wcwidth(ch);
		if (temp < 0)
			return temp;
		result += temp;
	}
	return result;
}
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcschrnul)(char16_t const *haystack,
                                     char16_t needle) {
	for (; *haystack; ++haystack) {
		if ((char16_t)*haystack == (char16_t)needle)
			break;
	}
	return (char16_t *)haystack;
}
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcschrnul)(char32_t const *haystack,
                                     char32_t needle) {
	for (; *haystack; ++haystack) {
		if ((char32_t)*haystack == (char32_t)needle)
			break;
	}
	return (char32_t *)haystack;
}
/* >> wcstol_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) long
NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstol(nptr, endptr, base);
}
/* >> wcstol_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) long
NOTHROW_NCX(LIBKCALL libc_wcstol_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstol(nptr, endptr, base);
}
/* >> wcstoul_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) unsigned long
NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstoul(nptr, endptr, base);
}
/* >> wcstoul_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) unsigned long
NOTHROW_NCX(LIBKCALL libc_wcstoul_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstoul(nptr, endptr, base);
}
/* >> wcstoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstoll(nptr, endptr, base);
}
/* >> wcstoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) __LONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoll_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstoll(nptr, endptr, base);
}
/* >> wcstoull_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstoull(nptr, endptr, base);
}
/* >> wcstoull_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) __ULONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoull_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstoull(nptr, endptr, base);
}
/* >> wcstof_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) float
NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstof(nptr, endptr);
}
/* >> wcstof_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) float
NOTHROW_NCX(LIBKCALL libc_wcstof_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstof(nptr, endptr);
}
/* >> wcstod_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) double
NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstod(nptr, endptr);
}
/* >> wcstod_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) double
NOTHROW_NCX(LIBKCALL libc_wcstod_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstod(nptr, endptr);
}
/* >> wcstold_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstold(nptr, endptr);
}
/* >> wcstold_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") NONNULL((1)) __LONGDOUBLE
NOTHROW_NCX(LIBKCALL libc_wcstold_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstold(nptr, endptr);
}
#include <libc/template/stdstreams.h>
/* >> getwchar_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc") wint16_t
(LIBDCALL libd_getwchar_unlocked)(void) THROWS(...) {
	return libd_fgetwc_unlocked(stdin);
}
#include <libc/template/stdstreams.h>
/* >> getwchar_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc") wint32_t
(LIBKCALL libc_getwchar_unlocked)(void) THROWS(...) {
	return libc_fgetwc_unlocked(stdin);
}
#include <libc/template/stdstreams.h>
/* >> putwchar_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc") wint16_t
(LIBDCALL libd_putwchar_unlocked)(char16_t wc) THROWS(...) {
	return libd_fputwc_unlocked(wc, stdout);
}
#include <libc/template/stdstreams.h>
/* >> putwchar_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc") wint32_t
(LIBKCALL libc_putwchar_unlocked)(char32_t wc) THROWS(...) {
	return libc_fputwc_unlocked(wc, stdout);
}
#include <asm/crt/stdio.h>
#include <libc/errno.h>
/* >> fgetws_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.read") NONNULL((1, 3)) char16_t *
(LIBDCALL libd_fgetws_unlocked)(char16_t *__restrict buf,
                                __STDC_INT_AS_SIZE_T bufsize,
                                FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */

		(void)libc_seterrno(ERANGE);

		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint16_t ch = libd_fgetwc_unlocked(stream);
		if (ch == __WEOF16) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libd_fgetwc_unlocked(stream);
			if (ch == __WEOF16) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libd_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
#include <asm/crt/stdio.h>
#include <libc/errno.h>
/* >> fgetws_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.read") NONNULL((1, 3)) char32_t *
(LIBKCALL libc_fgetws_unlocked)(char32_t *__restrict buf,
                                __STDC_INT_AS_SIZE_T bufsize,
                                FILE *__restrict stream) THROWS(...) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */

		(void)libc_seterrno(ERANGE);

		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint32_t ch = libc_fgetwc_unlocked(stream);
		if (ch == __WEOF32) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetwc_unlocked(stream);
			if (ch == __WEOF32) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/* >> fputws_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_fputws_unlocked)(char16_t const *__restrict str,
                                FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter_unlocked(stream, str, libd_wcslen(str));
	return result;
}
/* >> fputws_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write") NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_fputws_unlocked)(char32_t const *__restrict str,
                                FILE *__restrict stream) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter_unlocked(stream, str, libc_wcslen(str));
	return result;
}
/* >> wcsftime_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.strftime") ATTR_LIBC_C16FTIME(3, 0) NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf,
                                      size_t maxsize,
                                      char16_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libd_wcsftime(buf, maxsize, format, tp);
}
/* >> wcsftime_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.format.strftime") ATTR_LIBC_C32FTIME(3, 0) NONNULL((1, 3, 4)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsftime_l)(char32_t *__restrict buf,
                                      size_t maxsize,
                                      char32_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libc_wcsftime(buf, maxsize, format, tp);
}
/* >> vfwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C16PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwprintf_unlocked)(FILE *__restrict stream,
                                   char16_t const *__restrict format,
                                   va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter_unlocked,
	                                              stream, format, args);
}
/* >> vfwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C32PRINTF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vfwprintf_unlocked)(FILE *__restrict stream,
                                   char32_t const *__restrict format,
                                   va_list args) THROWS(...) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter_unlocked,
	                                              stream, format, args);
}
/* >> fwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C16PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwprintf_unlocked)(FILE *__restrict stream,
                                   char16_t const *__restrict format,
                                   ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C32PRINTF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwprintf_unlocked)(FILE *__restrict stream,
                                   char32_t const *__restrict format,
                                   ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> wprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C16PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wprintf_unlocked)(char16_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
/* >> wprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C32PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wprintf_unlocked)(char32_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
#include <libc/template/stdstreams.h>
/* >> vwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C16PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwprintf_unlocked)(char16_t const *__restrict format,
                                  va_list args) THROWS(...) {
	return libd_vfwprintf_unlocked(stdout, format, args);
}
#include <libc/template/stdstreams.h>
/* >> vwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_LIBC_C32PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwprintf_unlocked)(char32_t const *__restrict format,
                                  va_list args) THROWS(...) {
	return libc_vfwprintf_unlocked(stdout, format, args);
}
#include <libc/template/stdstreams.h>
/* >> vwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwscanf_unlocked)(char16_t const *__restrict format,
                                 va_list args) THROWS(...) {
	return libd_vfwscanf_unlocked(stdin, format, args);
}
#include <libc/template/stdstreams.h>
/* >> vwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vwscanf_unlocked)(char32_t const *__restrict format,
                                 va_list args) THROWS(...) {
	return libc_vfwscanf_unlocked(stdin, format, args);
}
/* >> fwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwscanf_unlocked)(FILE *__restrict stream,
                                  char16_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(2, 3) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_fwscanf_unlocked)(FILE *__restrict stream,
                                  char32_t const *__restrict format,
                                  ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> wscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_C16SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wscanf_unlocked)(char16_t const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf_unlocked(format, args);
	va_end(args);
	return result;
}
/* >> wscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_C32SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SIZE_T
(VLIBKCALL libc_wscanf_unlocked)(char32_t const *__restrict format,
                                 ...) THROWS(...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwscanf_unlocked(format, args);
	va_end(args);
	return result;
}
#ifndef LIBC_ARCH_HAVE_C16SEND
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict str) {
	while (*str)
		++str;
	return (char16_t *)str;
}
#endif /* !LIBC_ARCH_HAVE_C16SEND */
#ifndef LIBC_ARCH_HAVE_C32SEND
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsend)(char32_t const *__restrict str) {
	while (*str)
		++str;
	return (char32_t *)str;
}
#endif /* !LIBC_ARCH_HAVE_C32SEND */
#ifndef LIBC_ARCH_HAVE_C16SNEND
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnend)(char16_t const *__restrict str,
                                   size_t maxlen) {
	for (; maxlen && *str; ++str, --maxlen)
		;
	return (char16_t *)str;
}
#endif /* !LIBC_ARCH_HAVE_C16SNEND */
#ifndef LIBC_ARCH_HAVE_C32SNEND
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnend)(char32_t const *__restrict str,
                                   size_t maxlen) {
	for (; maxlen && *str; ++str, --maxlen)
		;
	return (char32_t *)str;
}
#endif /* !LIBC_ARCH_HAVE_C32SNEND */
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
#include <hybrid/limitcore.h>
/* >> wcsto32_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32_r)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {
	int32_t result;
	char16_t sign;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	while (libd_iswspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char16_t ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char16_t *)num_iter;
			}
			if (sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			while (libd_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char16_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char16_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char16_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libd_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
#include <hybrid/limitcore.h>
/* >> wcsto32_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBKCALL libc_wcsto32_r)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {
	int32_t result;
	char32_t sign;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	while (libc_iswspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char32_t ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char32_t *)num_iter;
			}
			if (sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			while (libc_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char32_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char32_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char32_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
/* >> wcstou32_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32_r)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {
	uint32_t result;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	while (libd_iswspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char16_t ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char16_t *)num_iter;
			}
			return (uint32_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			while (libd_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char16_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char16_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char16_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libd_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
/* >> wcstou32_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBKCALL libc_wcstou32_r)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {
	uint32_t result;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	while (libc_iswspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char32_t ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char32_t *)num_iter;
			}
			return (uint32_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			while (libc_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char32_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char32_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char32_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <libc/errno.h>
/* >> wcsto32(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {

	int32_t result;
	errno_t error;
	result = libd_wcsto32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
#include <libc/errno.h>
/* >> wcsto32(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBKCALL libc_wcsto32)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {

	int32_t result;
	errno_t error;
	result = libc_wcsto32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
#include <libc/errno.h>
/* >> wcstou32(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {

	uint32_t result;
	errno_t error;
	result = libd_wcstou32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
#include <libc/errno.h>
/* >> wcstou32(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBKCALL libc_wcstou32)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {

	uint32_t result;
	errno_t error;
	result = libc_wcstou32_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
#include <hybrid/limitcore.h>
/* >> wcsto64_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64_r)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {
	int64_t result;
	char16_t sign;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	while (libd_iswspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char16_t ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char16_t *)num_iter;
			}
			if (sign == '-')
				return __INT64_MIN__;
			return __INT64_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			while (libd_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char16_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char16_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char16_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libd_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
#include <hybrid/limitcore.h>
/* >> wcsto64_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBKCALL libc_wcsto64_r)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {
	int64_t result;
	char32_t sign;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	while (libc_iswspace(*num_start))
		++num_start;
	sign = *num_start;
	if (sign == '-' || sign == '+')
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char32_t ch;
		ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_sadd(result, digit, &result)) {
handle_overflow:
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char32_t *)num_iter;
			}
			if (sign == '-')
				return __INT64_MIN__;
			return __INT64_MAX__;
		}
	}
	if (sign == '-') {
		result = -result;
		if unlikely(result > 0)
			goto handle_overflow; /* Overflow... */
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			while (libc_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char32_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char32_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char32_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
/* >> wcstou64_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64_r)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {
	uint64_t result;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	while (libd_iswspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char16_t ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char16_t *)num_iter;
			}
			return (uint64_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			while (libd_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char16_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char16_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char16_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libd_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
/* >> wcstou64_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBKCALL libc_wcstou64_r)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {
	uint64_t result;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	while (libc_iswspace(*num_start))
		++num_start;
	if (base == 0) {
		/* Automatically deduce base. */
		if (*num_start == '0') {
			++num_start;
			if (*num_start == 'x' || *num_start == 'X') {
				base = 16;
				++num_start;
			} else if (*num_start == 'b' || *num_start == 'B') {
				base = 2;
				++num_start;
			} else {
				base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
				--num_start;
			}
		} else {
			base = 10;
		}
	}
	num_iter = num_start;
	result   = 0;
	for (;;) {
		uint8_t digit;
		char32_t ch = *num_iter;
		if (ch >= '0' && ch <= '9')
			digit = (uint8_t)(ch - '0');
		else if (ch >= 'a' && ch <= 'z')
			digit = (uint8_t)(10 + ch - 'a');
		else if (ch >= 'A' && ch <= 'Z')
			digit = (uint8_t)(10 + ch - 'A');
		else {
			break;
		}
		if (digit >= base)
			break;
		++num_iter;
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		            __hybrid_overflow_uadd(result, digit, &result)) {
			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (ch >= '0' && ch <= '9')
						digit = (uint8_t)(ch - '0');
					else if (ch >= 'a' && ch <= 'z')
						digit = (uint8_t)(10 + ch - 'a');
					else if (ch >= 'A' && ch <= 'Z')
						digit = (uint8_t)(10 + ch - 'A');
					else {
						break;
					}
					if (digit >= base)
						break;
					++num_iter;
				}
				*endptr = (char32_t *)num_iter;
			}
			return (uint64_t)-1;
		}
	}
	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			while (libc_iswspace(*nptr_ps))
				++nptr_ps;
			if (num_start > nptr_ps && *nptr_ps == '0') {
				if (endptr)
					*endptr = (char32_t *)nptr_ps + 1;
				if (error)
					*error = 0;
				return 0;
			}
		}

		/* Empty number... */
		if (error) {

			*error = ECANCELED;



		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (endptr)
			*endptr = (char32_t *)nptr;
	} else {
		if (endptr) {
			*endptr = (char32_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				while (libc_iswspace(*num_iter))
					++num_iter;
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <libc/errno.h>
/* >> wcstou64(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {

	uint64_t result;
	errno_t error;
	result = libd_wcstou64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
#include <libc/errno.h>
/* >> wcstou64(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBKCALL libc_wcstou64)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base) {

	uint64_t result;
	errno_t error;
	result = libc_wcstou64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
#include <libc/errno.h>
/* >> wcsto64(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64)(char16_t const *__restrict nptr,
                                   char16_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {

	int64_t result;
	errno_t error;
	result = libd_wcsto64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
#include <libc/errno.h>
/* >> wcsto64(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBKCALL libc_wcsto64)(char32_t const *__restrict nptr,
                                   char32_t **endptr,
                                   __STDC_INT_AS_UINT_T base) {

	int64_t result;
	errno_t error;
	result = libc_wcsto64_r(nptr, endptr, base, &error);
	if (error == ERANGE)
		(void)libc_seterrno(ERANGE);
	return result;



}
/* >> wcsto32_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsto32(nptr, endptr, base);
}
/* >> wcsto32_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int32_t
NOTHROW_NCX(LIBKCALL libc_wcsto32_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsto32(nptr, endptr, base);
}
/* >> wcstou32_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstou32(nptr, endptr, base);
}
/* >> wcstou32_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint32_t
NOTHROW_NCX(LIBKCALL libc_wcstou32_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstou32(nptr, endptr, base);
}
/* >> wcsto64_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsto64(nptr, endptr, base);
}
/* >> wcsto64_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) int64_t
NOTHROW_NCX(LIBKCALL libc_wcsto64_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsto64(nptr, endptr, base);
}
/* >> wcstou64_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstou64(nptr, endptr, base);
}
/* >> wcstou64_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF NONNULL((1)) uint64_t
NOTHROW_NCX(LIBKCALL libc_wcstou64_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstou64(nptr, endptr, base);
}
/* >> wcsncoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncoll)(char16_t const *s1,
                                    char16_t const *s2,
                                    size_t maxlen) {
	/* XXX: Implement properly? */
	return libd_wcsncmp(s1, s2, maxlen);
}
/* >> wcsncoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncoll)(char32_t const *s1,
                                    char32_t const *s2,
                                    size_t maxlen) {
	/* XXX: Implement properly? */
	return libc_wcsncmp(s1, s2, maxlen);
}
/* >> wcscasecoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll)(char16_t const *s1,
                                       char16_t const *s2) {
	/* XXX: Implement properly? */
	return libd_wcscasecmp(s1, s2);
}
/* >> wcscasecoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecoll)(char32_t const *s1,
                                       char32_t const *s2) {
	/* XXX: Implement properly? */
	return libc_wcscasecmp(s1, s2);
}
/* >> wcsncasecoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll)(char16_t const *s1,
                                        char16_t const *s2,
                                        size_t maxlen) {
	/* XXX: Implement properly? */
	return libd_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcsncasecoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecoll)(char32_t const *s1,
                                        char32_t const *s2,
                                        size_t maxlen) {
	/* XXX: Implement properly? */
	return libc_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcsnrev(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str,
                                   size_t maxlen) {

	return (char16_t *)libc_memrevw(str, libd_wcsnlen(str, maxlen));





}
/* >> wcsnrev(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnrev)(char32_t *__restrict str,
                                   size_t maxlen) {



	return (char32_t *)libc_memrevl(str, libc_wcsnlen(str, maxlen));



}
/* >> wcsnlwr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnlwr)(char16_t *__restrict str,
                                   size_t maxlen) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower((char16_t)ch);
	return str;
}
/* >> wcsnlwr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnlwr)(char32_t *__restrict str,
                                   size_t maxlen) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower((char32_t)ch);
	return str;
}
/* >> wcsnupr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str,
                                   size_t maxlen) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper((char16_t)ch);
	return str;
}
/* >> wcsnupr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnupr)(char32_t *__restrict str,
                                   size_t maxlen) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper((char32_t)ch);
	return str;
}
/* >> wcscasestr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack,
                                      char16_t const *needle) {
	for (; *haystack; ++haystack) {
		if (libd_wcscasecmp(haystack, needle) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}
/* >> wcscasestr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscasestr)(char32_t const *haystack,
                                      char32_t const *needle) {
	for (; *haystack; ++haystack) {
		if (libc_wcscasecmp(haystack, needle) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src) {
	return (char16_t *)libc_mempcpyw(buf, src, libd_wcslen(src) + 1);
}
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspcpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src) {
	return (char32_t *)libc_mempcpyl(buf, src, libc_wcslen(src) + 1);
}
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf,
                                    char16_t const *__restrict src,
                                    size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	(char16_t *)libc_memcpyw(buf, src, srclen);
	return (char16_t *)libc_mempsetw(buf + srclen, '\0', buflen - srclen);
}
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspncpy)(char32_t *__restrict buf,
                                    char32_t const *__restrict src,
                                    size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	(char32_t *)libc_memcpyl(buf, src, srclen);
	return (char32_t *)libc_mempsetl(buf + srclen, '\0', buflen - srclen);
}
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnchr)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t maxlen) {
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			return (char16_t *)haystack;
	}
	return NULL;
}
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnchr)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t maxlen) {
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrchr)(char16_t const *__restrict haystack,
                                    char16_t needle,
                                    size_t maxlen) {
	char16_t const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	}
	return (char16_t *)result;
}
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnrchr)(char32_t const *__restrict haystack,
                                    char32_t needle,
                                    size_t maxlen) {
	char32_t const *result = NULL;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	}
	return (char32_t *)result;
}
/* >> wcssep(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcssep)(char16_t **__restrict stringp,
                                  char16_t const *__restrict delim) {
	char16_t *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libd_wcschr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}
/* >> wcssep(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcssep)(char32_t **__restrict stringp,
                                  char32_t const *__restrict delim) {
	char32_t *result, *iter;
	if ((result = *stringp) == NULL || !*result)
		return NULL;
	for (iter = result; *iter && !libc_wcschr(delim, *iter); ++iter)
		;
	if (*iter)
		*iter++ = '\0';
	*stringp = iter;
	return result;
}
#include <hybrid/typecore.h>
/* >> wcsfry(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsfry)(char16_t *__restrict str) {
	size_t i, count = libd_wcslen(str);
	for (i = 0; i < count; ++i) {
		char16_t temp;
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
/* >> wcsfry(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsfry)(char32_t *__restrict str) {
	size_t i, count = libc_wcslen(str);
	for (i = 0; i < count; ++i) {
		char32_t temp;
		size_t j = libc_rand();
		j = i + (j % (count - i));
		/* Swap these 2 characters. */
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}
/* >> wcsndup(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsndup)(char16_t const *__restrict str,
                                   size_t max_chars) {
	size_t resultsize = libd_wcsnlen(str, max_chars) * sizeof(char16_t);
	char16_t *result = (char16_t *)libc_malloc(resultsize + sizeof(char16_t));
	if likely(result) {
		*(char16_t *)libc_mempcpy(result, str, resultsize) = '\0';
	}
	return result;
}
/* >> wcsndup(3) */
INTERN ATTR_SECTION(".text.crt.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsndup)(char32_t const *__restrict str,
                                   size_t max_chars) {
	size_t resultsize = libc_wcsnlen(str, max_chars) * sizeof(char32_t);
	char32_t *result = (char32_t *)libc_malloc(resultsize + sizeof(char32_t));
	if likely(result) {
		*(char32_t *)libc_mempcpy(result, str, resultsize) = '\0';
	}
	return result;
}
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrchrnul)(char16_t const *__restrict haystack,
                                      char16_t needle) {
	char16_t const *result = haystack - 1;
	do {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	} while (*haystack++);
	return (char16_t *)result;
}
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrchrnul)(char32_t const *__restrict haystack,
                                      char32_t needle) {
	char32_t const *result = haystack - 1;
	do {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	} while (*haystack++);
	return (char32_t *)result;
}
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack,
                                      char16_t needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (char16_t)*haystack != (char16_t)needle; ++haystack)
		;
	return (char16_t *)haystack;
}
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnchrnul)(char32_t const *__restrict haystack,
                                      char32_t needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (char32_t)*haystack != (char32_t)needle; ++haystack)
		;
	return (char32_t *)haystack;
}
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrchrnul)(char16_t const *__restrict haystack,
                                       char16_t needle,
                                       size_t maxlen) {
	char16_t const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char16_t)*haystack == (char16_t)needle)
			result = haystack;
	}
	return (char16_t *)result;
}
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnrchrnul)(char32_t const *__restrict haystack,
                                       char32_t needle,
                                       size_t maxlen) {
	char32_t const *result = haystack - 1;
	for (; maxlen-- && *haystack; ++haystack) {
		if unlikely((char32_t)*haystack == (char32_t)needle)
			result = haystack;
	}
	return (char32_t *)result;
}
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack,
                                  char16_t needle) {
	return (size_t)(libd_wcschrnul(haystack, needle) - haystack);
}
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsoff)(char32_t const *__restrict haystack,
                                  char32_t needle) {
	return (size_t)(libc_wcschrnul(haystack, needle) - haystack);
}
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack,
                                   char16_t needle) {
	return (size_t)(libd_wcsrchrnul(haystack, needle) - haystack);
}
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsroff)(char32_t const *__restrict haystack,
                                   char32_t needle) {
	return (size_t)(libc_wcsrchrnul(haystack, needle) - haystack);
}
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t maxlen) {
	return (size_t)(libd_wcsnchrnul(haystack, needle, maxlen) - haystack);
}
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnoff)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t maxlen) {
	return (size_t)(libc_wcsnchrnul(haystack, needle, maxlen) - haystack);
}
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack,
                                    char16_t needle,
                                    size_t maxlen) {
	return (size_t)(libd_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnroff)(char32_t const *__restrict haystack,
                                    char32_t needle,
                                    size_t maxlen) {
	return (size_t)(libc_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}
/* >> fuzzy_wcscmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscmp)(char16_t const *s1,
                                        char16_t const *s2) {
	return libc_fuzzy_memcmpw(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}
/* >> fuzzy_wcscmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscmp)(char32_t const *s1,
                                        char32_t const *s2) {
	return libc_fuzzy_memcmpl(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
/* >> fuzzy_wcsncmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncmp)(char16_t const *s1,
                                         size_t s1_maxlen,
                                         char16_t const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmpw(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}
/* >> fuzzy_wcsncmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncmp)(char32_t const *s1,
                                         size_t s1_maxlen,
                                         char32_t const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmpl(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
#include <parts/malloca.h>
/* >> fuzzy_wmemcasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp)(char16_t const *s1,
                                             size_t s1_bytes,
                                             char16_t const *s2,
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
			cost  = c1 != c2 && (libd_towlower((char16_t)c1) !=
			                     libd_towlower((char16_t)c2));
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
/* >> fuzzy_wmemcasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp)(char32_t const *s1,
                                             size_t s1_bytes,
                                             char32_t const *s2,
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
			cost  = c1 != c2 && (libc_towlower((char32_t)c1) !=
			                     libc_towlower((char32_t)c2));
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
/* >> fuzzy_wcscasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp)(char16_t const *s1,
                                            char16_t const *s2) {
	return libd_fuzzy_wmemcasecmp(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}
/* >> fuzzy_wcscasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp)(char32_t const *s1,
                                            char32_t const *s2) {
	return libc_fuzzy_wmemcasecmp(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
/* >> fuzzy_wcsncasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp)(char16_t const *s1,
                                             size_t s1_maxlen,
                                             char16_t const *s2,
                                             size_t s2_maxlen) {
	return libd_fuzzy_wmemcasecmp(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}
/* >> fuzzy_wcsncasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp)(char32_t const *s1,
                                             size_t s1_maxlen,
                                             char32_t const *s2,
                                             size_t s2_maxlen) {
	return libc_fuzzy_wmemcasecmp(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
/* >> wildwcscmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildwcscmp)(char16_t const *pattern,
                                      char16_t const *string) {
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
			char16_t card_post;
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
/* >> wildwcscmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wildwcscmp)(char32_t const *pattern,
                                      char32_t const *string) {
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
			char32_t card_post;
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
/* >> wildwcscasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp)(char16_t const *pattern,
                                          char16_t const *string) {
	char16_t pattern_ch, wcsing_ch;
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
			char16_t card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char16_t)libd_towlower((char16_t)card_post);
			for (;;) {
				char16_t ch = *string++;
				if (card_post == ch || card_post == (char16_t)libd_towlower((char16_t)ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wildwcscasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch  = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		    (pattern_ch = (char16_t)libd_towlower((char16_t)pattern_ch),
		     wcsing_ch  = (char16_t)libd_towlower((char16_t)wcsing_ch),
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
/* >> wildwcscasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp)(char32_t const *pattern,
                                          char32_t const *string) {
	char32_t pattern_ch, wcsing_ch;
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
			char32_t card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char32_t)libc_towlower((char32_t)card_post);
			for (;;) {
				char32_t ch = *string++;
				if (card_post == ch || card_post == (char32_t)libc_towlower((char32_t)ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libc_wildwcscasecmp(string, pattern))
						return 0;
				} else if (!ch) {
					return -(int)(char32_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch  = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		    (pattern_ch = (char32_t)libc_towlower((char32_t)pattern_ch),
		     wcsing_ch  = (char32_t)libc_towlower((char32_t)wcsing_ch),
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
/* >> wcsverscmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsverscmp)(char16_t const *s1,
                                      char16_t const *s2) {
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

			/* Return difference between digits. */
			return (int)vala - (int)valb;
		}
		++s1;
		++s2;
	} while (c1 != '\0');
	return 0;
}
/* >> wcsverscmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsverscmp)(char32_t const *s1,
                                      char32_t const *s2) {
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

			/* Return difference between digits. */
			return (int)vala - (int)valb;
		}
		++s1;
		++s2;
	} while (c1 != '\0');
	return 0;
}
/* >> wcsncoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncoll_l)(char16_t const *s1,
                                      char16_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libd_wcsncoll(s1, s2, maxlen);
}
/* >> wcsncoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncoll_l)(char32_t const *s1,
                                      char32_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_wcsncoll(s1, s2, maxlen);
}
/* >> wcscasecoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         locale_t locale) {
	/* XXX: Implement properly? */
	return libd_wcscasecmp_l(s1, s2, locale);
}
/* >> wcscasecoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcscasecoll_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         locale_t locale) {
	/* XXX: Implement properly? */
	return libc_wcscasecmp_l(s1, s2, locale);
}
/* >> wcsncasecoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll_l)(char16_t const *s1,
                                          char16_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libd_wcsncasecoll(s1, s2, maxlen);
}
/* >> wcsncasecoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecoll_l)(char32_t const *s1,
                                          char32_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_wcsncasecoll(s1, s2, maxlen);
}
/* >> wcslwr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr_l)(char16_t *__restrict str,
                                    locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower_l((char16_t)ch, locale);
	return str;
}
/* >> wcslwr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcslwr_l)(char32_t *__restrict str,
                                    locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l((char32_t)ch, locale);
	return str;
}
/* >> wcsupr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr_l)(char16_t *__restrict str,
                                    locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper_l((char16_t)ch, locale);
	return str;
}
/* >> wcsupr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsupr_l)(char32_t *__restrict str,
                                    locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l((char32_t)ch, locale);
	return str;
}
/* >> wcsnlwr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower_l((char16_t)ch, locale);
	return str;
}
/* >> wcsnlwr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnlwr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l((char32_t)ch, locale);
	return str;
}
/* >> wcsnupr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper_l((char16_t)ch, locale);
	return str;
}
/* >> wcsnupr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnupr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l((char32_t)ch, locale);
	return str;
}
/* >> wcscasestr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack,
                                        char16_t const *needle,
                                        locale_t locale) {
	for (; *haystack; ++haystack) {
		if (libd_wcscasecmp_l(haystack, needle, locale) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}
/* >> wcscasestr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscasestr_l)(char32_t const *haystack,
                                        char32_t const *needle,
                                        locale_t locale) {
	for (; *haystack; ++haystack) {
		if (libc_wcscasecmp_l(haystack, needle, locale) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* >> fuzzy_wmemcasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wmemcasecmp_l)(char16_t const *s1,
                                               size_t s1_bytes,
                                               char16_t const *s2,
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
			cost  = c1 != c2 && (libd_towlower_l((char16_t)c1, locale) !=
			                     libd_towlower_l((char16_t)c2, locale));
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
/* >> fuzzy_wmemcasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wmemcasecmp_l)(char32_t const *s1,
                                               size_t s1_bytes,
                                               char32_t const *s2,
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
			cost  = c1 != c2 && (libc_towlower_l((char32_t)c1, locale) !=
			                     libc_towlower_l((char32_t)c2, locale));
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
/* >> fuzzy_wcscasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1,
                                              char16_t const *s2,
                                              locale_t locale) {
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcslen(s1), s2, libd_wcslen(s2), locale);
}
/* >> fuzzy_wcscasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1,
                                              char32_t const *s2,
                                              locale_t locale) {
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcslen(s1), s2, libc_wcslen(s2), locale);
}
/* >> fuzzy_wcsncasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1,
                                               size_t s1_maxlen,
                                               char16_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen), locale);
}
/* >> fuzzy_wcsncasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1,
                                               size_t s1_maxlen,
                                               char32_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen), locale);
}
/* >> wildwcscasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wildwcscasecmp_l)(char16_t const *pattern,
                                            char16_t const *string,
                                            locale_t locale) {
	char16_t pattern_ch, wcsing_ch;
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
			char16_t card_post;
			/* Skip stars */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?')
				goto next; /* Match any --> already found */
			card_post = (char16_t)libd_towlower_l(card_post, locale);
			for (;;) {
				char16_t ch = *string++;
				if (card_post == ch || card_post == (char16_t)libd_towlower_l(ch, locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!libd_wcscasecmp_l(string, pattern, locale))
						return 0;
				} else if (!ch) {
					return -(int)(char16_t)card_post; /* Wildcard suffix not found */
				}
			}
		}
		pattern_ch = *pattern;
		wcsing_ch  = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		    (pattern_ch = (char16_t)libd_towlower_l((char16_t)pattern_ch, locale),
		     wcsing_ch  = (char16_t)libd_towlower_l((char16_t)wcsing_ch, locale),
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
/* >> wildwcscasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wildwcscasecmp_l)(char32_t const *pattern,
                                            char32_t const *string,
                                            locale_t locale) {
	char32_t pattern_ch, wcsing_ch;
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
			char32_t card_post;
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
		wcsing_ch  = *string;
		if (pattern_ch == wcsing_ch || pattern_ch == '?' ||
		    (pattern_ch = (char32_t)libc_towlower_l((char32_t)pattern_ch, locale),
		     wcsing_ch  = (char32_t)libc_towlower_l((char32_t)wcsing_ch, locale),
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
/* >> wcslcat(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcslcat)(char16_t *__restrict dst,
                                   char16_t const *__restrict src,
                                   size_t bufsize) {
	size_t result = libd_wcslen(src);
	char16_t *new_dst = dst + libd_wcsnlen(dst, bufsize);
	size_t copy_size;
	bufsize -= (new_dst - dst);
	copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(new_dst, src, copy_size*sizeof(char16_t));
	new_dst[copy_size] = '\0';
	return result + (new_dst - dst);
}
/* >> wcslcat(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcslcat)(char32_t *__restrict dst,
                                   char32_t const *__restrict src,
                                   size_t bufsize) {
	size_t result = libc_wcslen(src);
	char32_t *new_dst = dst + libc_wcsnlen(dst, bufsize);
	size_t copy_size;
	bufsize -= (new_dst - dst);
	copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(new_dst, src, copy_size*sizeof(char32_t));
	new_dst[copy_size] = '\0';
	return result + (new_dst - dst);
}
/* >> wcslcpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcslcpy)(char16_t *__restrict dst,
                                   char16_t const *__restrict src,
                                   size_t bufsize) {
	size_t result = libd_wcslen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(dst, src, copy_size*sizeof(char16_t));
	dst[copy_size] = '\0';
	return result;
}
/* >> wcslcpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcslcpy)(char32_t *__restrict dst,
                                   char32_t const *__restrict src,
                                   size_t bufsize) {
	size_t result = libc_wcslen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(dst, src, copy_size*sizeof(char32_t));
	dst[copy_size] = '\0';
	return result;
}
/* >> wcsnset(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnset)(char16_t *__restrict str,
                                   char16_t ch,
                                   size_t maxlen) {
	char16_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}
/* >> wcsnset(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnset)(char32_t *__restrict str,
                                   char32_t ch,
                                   size_t maxlen) {
	char32_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
/* >> wcsrev(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrev)(char16_t *__restrict str) {

	return (char16_t *)libc_memrevw(str, libd_wcslen(str));





}
/* >> wcsrev(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrev)(char32_t *__restrict str) {



	return (char32_t *)libc_memrevl(str, libc_wcslen(str));



}
/* >> wcsset(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsset)(char16_t *__restrict str,
                                  int ch) {
	char16_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}
/* >> wcsset(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsset)(char32_t *__restrict str,
                                  int ch) {
	char32_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
/* >> wcslwr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr)(char16_t *__restrict str) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower((char16_t)ch);
	return str;
}
/* >> wcslwr(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcslwr)(char32_t *__restrict str) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower((char32_t)ch);
	return str;
}
/* >> wcsupr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr)(char16_t *__restrict str) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper((char16_t)ch);
	return str;
}
/* >> wcsupr(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_RETNONNULL NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsupr)(char32_t *__restrict str) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper((char32_t)ch);
	return str;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$btowc, libd_btowc);
DEFINE_PUBLIC_ALIAS(btowc, libc_btowc);
DEFINE_PUBLIC_ALIAS(DOS$wctob, libd_wctob);
DEFINE_PUBLIC_ALIAS(wctob, libc_wctob);
DEFINE_PUBLIC_ALIAS(DOS$__mbrtowc, libd_mbrtowc);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(mbrtoc16, libd_mbrtowc);
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$mbrtoc16, libd_mbrtowc);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(DOS$mbrtowc, libd_mbrtowc);
DEFINE_PUBLIC_ALIAS(__mbrtowc, libc_mbrtowc);
DEFINE_PUBLIC_ALIAS(mbrtoc32, libc_mbrtowc);
DEFINE_PUBLIC_ALIAS(mbrtowc, libc_mbrtowc);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(c16rtomb, libd_wcrtomb);
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$c16rtomb, libd_wcrtomb);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(DOS$wcrtomb, libd_wcrtomb);
DEFINE_PUBLIC_ALIAS(c32rtomb, libc_wcrtomb);
DEFINE_PUBLIC_ALIAS(wcrtomb, libc_wcrtomb);
DEFINE_PUBLIC_ALIAS(DOS$__mbrlen, libd_mbrlen);
DEFINE_PUBLIC_ALIAS(DOS$mbrlen, libd_mbrlen);
DEFINE_PUBLIC_ALIAS(__mbrlen, libc_mbrlen);
DEFINE_PUBLIC_ALIAS(mbrlen, libc_mbrlen);
DEFINE_PUBLIC_ALIAS(DOS$mbsrtowcs, libd_mbsrtowcs);
DEFINE_PUBLIC_ALIAS(mbsrtowcs, libc_mbsrtowcs);
DEFINE_PUBLIC_ALIAS(DOS$wcsrtombs, libd_wcsrtombs);
DEFINE_PUBLIC_ALIAS(wcsrtombs, libc_wcsrtombs);
DEFINE_PUBLIC_ALIAS(DOS$wcstol, libd_wcstol);
DEFINE_PUBLIC_ALIAS(wcstol, libc_wcstol);
DEFINE_PUBLIC_ALIAS(DOS$wcstoul, libd_wcstoul);
DEFINE_PUBLIC_ALIAS(wcstoul, libc_wcstoul);
DEFINE_PUBLIC_ALIAS(mbsinit, libc_mbsinit);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16MEMCMP) && __SIZEOF_INT__ > 2
DEFINE_PUBLIC_ALIAS(DOS$wmemcmp, libd_wmemcmp);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16MEMCMP && __SIZEOF_INT__ > 2 */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32MEMCMP) && __SIZEOF_INT__ > 4
DEFINE_PUBLIC_ALIAS(wmemcmp, libc_wmemcmp);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32MEMCMP && __SIZEOF_INT__ > 4 */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$wcscpy, libd_wcscpy);
DEFINE_PUBLIC_ALIAS(wcscpy, libc_wcscpy);
DEFINE_PUBLIC_ALIAS(DOS$wcscat, libd_wcscat);
DEFINE_PUBLIC_ALIAS(wcscat, libc_wcscat);
DEFINE_PUBLIC_ALIAS(DOS$wcsncat, libd_wcsncat);
DEFINE_PUBLIC_ALIAS(wcsncat, libc_wcsncat);
DEFINE_PUBLIC_ALIAS(DOS$wcsncpy, libd_wcsncpy);
DEFINE_PUBLIC_ALIAS(wcsncpy, libc_wcsncpy);
DEFINE_PUBLIC_ALIAS(DOS$wcscmp, libd_wcscmp);
DEFINE_PUBLIC_ALIAS(wcscmp, libc_wcscmp);
DEFINE_PUBLIC_ALIAS(DOS$wcsncmp, libd_wcsncmp);
DEFINE_PUBLIC_ALIAS(wcsncmp, libc_wcsncmp);
DEFINE_PUBLIC_ALIAS(DOS$wcscoll, libd_wcscoll);
DEFINE_PUBLIC_ALIAS(wcscoll, libc_wcscoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsxfrm, libd_wcsxfrm);
DEFINE_PUBLIC_ALIAS(wcsxfrm, libc_wcsxfrm);
DEFINE_PUBLIC_ALIAS(DOS$_fgetwchar, libd_getwchar);
DEFINE_PUBLIC_ALIAS(DOS$getwchar, libd_getwchar);
DEFINE_PUBLIC_ALIAS(getwchar, libc_getwchar);
DEFINE_PUBLIC_ALIAS(DOS$_fputwchar, libd_putwchar);
DEFINE_PUBLIC_ALIAS(DOS$putwchar, libd_putwchar);
DEFINE_PUBLIC_ALIAS(putwchar, libc_putwchar);
DEFINE_PUBLIC_ALIAS(DOS$fgetws, libd_fgetws);
DEFINE_PUBLIC_ALIAS(fgetws, libc_fgetws);
DEFINE_PUBLIC_ALIAS(DOS$fputws, libd_fputws);
DEFINE_PUBLIC_ALIAS(fputws, libc_fputws);
DEFINE_PUBLIC_ALIAS(DOS$wcsftime, libd_wcsftime);
DEFINE_PUBLIC_ALIAS(wcsftime, libc_wcsftime);
DEFINE_PUBLIC_ALIAS(DOS$wcstok_s, libd_wcstok);
DEFINE_PUBLIC_ALIAS(wcstok, libc_wcstok);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SLEN)
DEFINE_PUBLIC_ALIAS(DOS$wcslen, libd_wcslen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SLEN)
DEFINE_PUBLIC_ALIAS(wcslen, libc_wcslen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SLEN */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$wcsspn, libd_wcsspn);
DEFINE_PUBLIC_ALIAS(wcsspn, libc_wcsspn);
DEFINE_PUBLIC_ALIAS(DOS$wcscspn, libd_wcscspn);
DEFINE_PUBLIC_ALIAS(wcscspn, libc_wcscspn);
DEFINE_PUBLIC_ALIAS(DOS$wcschr, libd_wcschr);
DEFINE_PUBLIC_ALIAS(wcschr, libc_wcschr);
DEFINE_PUBLIC_ALIAS(DOS$wcsrchr, libd_wcsrchr);
DEFINE_PUBLIC_ALIAS(wcsrchr, libc_wcsrchr);
DEFINE_PUBLIC_ALIAS(DOS$wcspbrk, libd_wcspbrk);
DEFINE_PUBLIC_ALIAS(wcspbrk, libc_wcspbrk);
DEFINE_PUBLIC_ALIAS(DOS$wcswcs, libd_wcsstr);
DEFINE_PUBLIC_ALIAS(DOS$wcsstr, libd_wcsstr);
DEFINE_PUBLIC_ALIAS(wcswcs, libc_wcsstr);
DEFINE_PUBLIC_ALIAS(wcsstr, libc_wcsstr);
DEFINE_PUBLIC_ALIAS(fwide, libc_fwide);
DEFINE_PUBLIC_ALIAS(DOS$_fwprintf_p, libd_fwprintf);
DEFINE_PUBLIC_ALIAS(DOS$fwprintf, libd_fwprintf);
DEFINE_PUBLIC_ALIAS(_fwprintf_p, libc_fwprintf);
DEFINE_PUBLIC_ALIAS(fwprintf, libc_fwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vfwprintf_p, libd_vfwprintf);
DEFINE_PUBLIC_ALIAS(DOS$vfwprintf, libd_vfwprintf);
DEFINE_PUBLIC_ALIAS(_vfwprintf_p, libc_vfwprintf);
DEFINE_PUBLIC_ALIAS(vfwprintf, libc_vfwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_wprintf_p, libd_wprintf);
DEFINE_PUBLIC_ALIAS(DOS$wprintf, libd_wprintf);
DEFINE_PUBLIC_ALIAS(_wprintf_p, libc_wprintf);
DEFINE_PUBLIC_ALIAS(wprintf, libc_wprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vwprintf_p, libd_vwprintf);
DEFINE_PUBLIC_ALIAS(DOS$vwprintf, libd_vwprintf);
DEFINE_PUBLIC_ALIAS(_vwprintf_p, libc_vwprintf);
DEFINE_PUBLIC_ALIAS(vwprintf, libc_vwprintf);
DEFINE_PUBLIC_ALIAS(DOS$fwscanf, libd_fwscanf);
DEFINE_PUBLIC_ALIAS(fwscanf, libc_fwscanf);
DEFINE_PUBLIC_ALIAS(DOS$wscanf, libd_wscanf);
DEFINE_PUBLIC_ALIAS(wscanf, libc_wscanf);
DEFINE_PUBLIC_ALIAS(DOS$swscanf, libd_swscanf);
DEFINE_PUBLIC_ALIAS(swscanf, libc_swscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vswprintf_p, libd_vswprintf);
DEFINE_PUBLIC_ALIAS(DOS$vswprintf, libd_vswprintf);
DEFINE_PUBLIC_ALIAS(_vswprintf_p, libc_vswprintf);
DEFINE_PUBLIC_ALIAS(vswprintf, libc_vswprintf);
DEFINE_PUBLIC_ALIAS(DOS$_swprintf_p, libd_swprintf);
DEFINE_PUBLIC_ALIAS(DOS$swprintf, libd_swprintf);
DEFINE_PUBLIC_ALIAS(_swprintf_p, libc_swprintf);
DEFINE_PUBLIC_ALIAS(swprintf, libc_swprintf);
DEFINE_PUBLIC_ALIAS(DOS$wcstod, libd_wcstod);
DEFINE_PUBLIC_ALIAS(wcstod, libc_wcstod);
DEFINE_PUBLIC_ALIAS(DOS$wcstof, libd_wcstof);
DEFINE_PUBLIC_ALIAS(wcstof, libc_wcstof);
DEFINE_PUBLIC_ALIAS(DOS$wcstold, libd_wcstold);
DEFINE_PUBLIC_ALIAS(wcstold, libc_wcstold);
DEFINE_PUBLIC_ALIAS(DOS$wcstoll, libd_wcstoll);
DEFINE_PUBLIC_ALIAS(DOS$wcstoq, libd_wcstoll);
DEFINE_PUBLIC_ALIAS(wcstoll, libc_wcstoll);
DEFINE_PUBLIC_ALIAS(wcstoq, libc_wcstoll);
DEFINE_PUBLIC_ALIAS(DOS$wcstoull, libd_wcstoull);
DEFINE_PUBLIC_ALIAS(DOS$wcstouq, libd_wcstoull);
DEFINE_PUBLIC_ALIAS(wcstoull, libc_wcstoull);
DEFINE_PUBLIC_ALIAS(wcstouq, libc_wcstoull);
DEFINE_PUBLIC_ALIAS(DOS$vwscanf, libd_vwscanf);
DEFINE_PUBLIC_ALIAS(vwscanf, libc_vwscanf);
DEFINE_PUBLIC_ALIAS(DOS$vswscanf, libd_vswscanf);
DEFINE_PUBLIC_ALIAS(vswscanf, libc_vswscanf);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicmp, libd_wcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecmp, libd_wcscasecmp);
DEFINE_PUBLIC_ALIAS(wcscasecmp, libc_wcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicmp, libd_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecmp, libd_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(wcsncasecmp, libc_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicmp_l, libd_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcscasecmp_l, libd_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecmp_l, libd_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(__wcscasecmp_l, libc_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(wcscasecmp_l, libc_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicmp_l, libd_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcsncasecmp_l, libd_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecmp_l, libd_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(__wcsncasecmp_l, libc_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(wcsncasecmp_l, libc_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcscoll_l, libd_wcscoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcscoll_l, libd_wcscoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscoll_l, libd_wcscoll_l);
DEFINE_PUBLIC_ALIAS(__wcscoll_l, libc_wcscoll_l);
DEFINE_PUBLIC_ALIAS(wcscoll_l, libc_wcscoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsxfrm_l, libd_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcsxfrm_l, libd_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsxfrm_l, libd_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(__wcsxfrm_l, libc_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(wcsxfrm_l, libc_wcsxfrm_l);
DEFINE_PUBLIC_ALIAS(DOS$wcpcpy, libd_wcpcpy);
DEFINE_PUBLIC_ALIAS(wcpcpy, libc_wcpcpy);
DEFINE_PUBLIC_ALIAS(DOS$wcpncpy, libd_wcpncpy);
DEFINE_PUBLIC_ALIAS(wcpncpy, libc_wcpncpy);
DEFINE_PUBLIC_ALIAS(DOS$mbsnrtowcs, libd_mbsnrtowcs);
DEFINE_PUBLIC_ALIAS(mbsnrtowcs, libc_mbsnrtowcs);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrtombs, libd_wcsnrtombs);
DEFINE_PUBLIC_ALIAS(wcsnrtombs, libc_wcsnrtombs);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SNLEN)
DEFINE_PUBLIC_ALIAS(DOS$__wcsncnt, libd_wcsnlen);
DEFINE_PUBLIC_ALIAS(DOS$wcsnlen, libd_wcsnlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SNLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SNLEN)
DEFINE_PUBLIC_ALIAS(wcsnlen, libc_wcsnlen);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SNLEN */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wcsdup, libd_wcsdup);
DEFINE_PUBLIC_ALIAS(DOS$wcsdup, libd_wcsdup);
DEFINE_PUBLIC_ALIAS(wcsdup, libc_wcsdup);
DEFINE_PUBLIC_ALIAS(DOS$wcwidth, libd_wcwidth);
DEFINE_PUBLIC_ALIAS(wcwidth, libc_wcwidth);
DEFINE_PUBLIC_ALIAS(DOS$wcswidth, libd_wcswidth);
DEFINE_PUBLIC_ALIAS(wcswidth, libc_wcswidth);
DEFINE_PUBLIC_ALIAS(DOS$wcschrnul, libd_wcschrnul);
DEFINE_PUBLIC_ALIAS(wcschrnul, libc_wcschrnul);
DEFINE_PUBLIC_ALIAS(DOS$_wcstol_l, libd_wcstol_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstol_l, libd_wcstol_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstol_l, libd_wcstol_l);
DEFINE_PUBLIC_ALIAS(__wcstol_l, libc_wcstol_l);
DEFINE_PUBLIC_ALIAS(wcstol_l, libc_wcstol_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoul_l, libd_wcstoul_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstoul_l, libd_wcstoul_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstoul_l, libd_wcstoul_l);
DEFINE_PUBLIC_ALIAS(__wcstoul_l, libc_wcstoul_l);
DEFINE_PUBLIC_ALIAS(wcstoul_l, libc_wcstoul_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoll_l, libd_wcstoll_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstoll_l, libd_wcstoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstoll_l, libd_wcstoll_l);
DEFINE_PUBLIC_ALIAS(__wcstoll_l, libc_wcstoll_l);
DEFINE_PUBLIC_ALIAS(wcstoll_l, libc_wcstoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoull_l, libd_wcstoull_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstoull_l, libd_wcstoull_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstoull_l, libd_wcstoull_l);
DEFINE_PUBLIC_ALIAS(__wcstoull_l, libc_wcstoull_l);
DEFINE_PUBLIC_ALIAS(wcstoull_l, libc_wcstoull_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstof_l, libd_wcstof_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstof_l, libd_wcstof_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstof_l, libd_wcstof_l);
DEFINE_PUBLIC_ALIAS(__wcstof_l, libc_wcstof_l);
DEFINE_PUBLIC_ALIAS(wcstof_l, libc_wcstof_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstod_l, libd_wcstod_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstod_l, libd_wcstod_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstod_l, libd_wcstod_l);
DEFINE_PUBLIC_ALIAS(__wcstod_l, libc_wcstod_l);
DEFINE_PUBLIC_ALIAS(wcstod_l, libc_wcstod_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstold_l, libd_wcstold_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcstold_l, libd_wcstold_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstold_l, libd_wcstold_l);
DEFINE_PUBLIC_ALIAS(__wcstold_l, libc_wcstold_l);
DEFINE_PUBLIC_ALIAS(wcstold_l, libc_wcstold_l);
DEFINE_PUBLIC_ALIAS(DOS$getwchar_unlocked, libd_getwchar_unlocked);
DEFINE_PUBLIC_ALIAS(getwchar_unlocked, libc_getwchar_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$putwchar_unlocked, libd_putwchar_unlocked);
DEFINE_PUBLIC_ALIAS(putwchar_unlocked, libc_putwchar_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fgetws_nolock, libd_fgetws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetws_unlocked, libd_fgetws_unlocked);
DEFINE_PUBLIC_ALIAS(fgetws_unlocked, libc_fgetws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fputws_nolock, libd_fputws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fputws_unlocked, libd_fputws_unlocked);
DEFINE_PUBLIC_ALIAS(fputws_unlocked, libc_fputws_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_wcsftime_l, libd_wcsftime_l);
DEFINE_PUBLIC_ALIAS(DOS$__wcsftime_l, libd_wcsftime_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsftime_l, libd_wcsftime_l);
DEFINE_PUBLIC_ALIAS(__wcsftime_l, libc_wcsftime_l);
DEFINE_PUBLIC_ALIAS(wcsftime_l, libc_wcsftime_l);
DEFINE_PUBLIC_ALIAS(DOS$vfwprintf_unlocked, libd_vfwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(vfwprintf_unlocked, libc_vfwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fwprintf_unlocked, libd_fwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(fwprintf_unlocked, libc_fwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$wprintf_unlocked, libd_wprintf_unlocked);
DEFINE_PUBLIC_ALIAS(wprintf_unlocked, libc_wprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vwprintf_unlocked, libd_vwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(vwprintf_unlocked, libc_vwprintf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vwscanf_unlocked, libd_vwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(vwscanf_unlocked, libc_vwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fwscanf_unlocked, libd_fwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(fwscanf_unlocked, libc_fwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$wscanf_unlocked, libd_wscanf_unlocked);
DEFINE_PUBLIC_ALIAS(wscanf_unlocked, libc_wscanf_unlocked);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SEND)
DEFINE_PUBLIC_ALIAS(DOS$wcsend, libd_wcsend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SEND)
DEFINE_PUBLIC_ALIAS(wcsend, libc_wcsend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SNEND)
DEFINE_PUBLIC_ALIAS(DOS$wcsnend, libd_wcsnend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SNEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SNEND)
DEFINE_PUBLIC_ALIAS(wcsnend, libc_wcsnend);
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SNEND */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$wcsto32_r, libd_wcsto32_r);
DEFINE_PUBLIC_ALIAS(wcsto32_r, libc_wcsto32_r);
DEFINE_PUBLIC_ALIAS(DOS$wcstou32_r, libd_wcstou32_r);
DEFINE_PUBLIC_ALIAS(wcstou32_r, libc_wcstou32_r);
DEFINE_PUBLIC_ALIAS(DOS$wcsto32, libd_wcsto32);
DEFINE_PUBLIC_ALIAS(wcsto32, libc_wcsto32);
DEFINE_PUBLIC_ALIAS(DOS$wcstou32, libd_wcstou32);
DEFINE_PUBLIC_ALIAS(wcstou32, libc_wcstou32);
DEFINE_PUBLIC_ALIAS(DOS$wcsto64_r, libd_wcsto64_r);
DEFINE_PUBLIC_ALIAS(wcsto64_r, libc_wcsto64_r);
DEFINE_PUBLIC_ALIAS(DOS$wcstou64_r, libd_wcstou64_r);
DEFINE_PUBLIC_ALIAS(wcstou64_r, libc_wcstou64_r);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoui64, libd_wcstou64);
DEFINE_PUBLIC_ALIAS(DOS$wcstou64, libd_wcstou64);
DEFINE_PUBLIC_ALIAS(wcstou64, libc_wcstou64);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoi64, libd_wcsto64);
DEFINE_PUBLIC_ALIAS(DOS$wcsto64, libd_wcsto64);
DEFINE_PUBLIC_ALIAS(wcsto64, libc_wcsto64);
DEFINE_PUBLIC_ALIAS(DOS$wcsto32_l, libd_wcsto32_l);
DEFINE_PUBLIC_ALIAS(wcsto32_l, libc_wcsto32_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstou32_l, libd_wcstou32_l);
DEFINE_PUBLIC_ALIAS(wcstou32_l, libc_wcstou32_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoi64_l, libd_wcsto64_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsto64_l, libd_wcsto64_l);
DEFINE_PUBLIC_ALIAS(wcsto64_l, libc_wcsto64_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcstoui64_l, libd_wcstou64_l);
DEFINE_PUBLIC_ALIAS(DOS$wcstou64_l, libd_wcstou64_l);
DEFINE_PUBLIC_ALIAS(wcstou64_l, libc_wcstou64_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsncoll, libd_wcsncoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsncoll, libd_wcsncoll);
DEFINE_PUBLIC_ALIAS(wcsncoll, libc_wcsncoll);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicoll, libd_wcscasecoll);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecoll, libd_wcscasecoll);
DEFINE_PUBLIC_ALIAS(wcscasecoll, libc_wcscasecoll);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicoll, libd_wcsncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecoll, libd_wcsncasecoll);
DEFINE_PUBLIC_ALIAS(wcsncasecoll, libc_wcsncasecoll);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrev, libd_wcsnrev);
DEFINE_PUBLIC_ALIAS(wcsnrev, libc_wcsnrev);
DEFINE_PUBLIC_ALIAS(DOS$wcsnlwr, libd_wcsnlwr);
DEFINE_PUBLIC_ALIAS(wcsnlwr, libc_wcsnlwr);
DEFINE_PUBLIC_ALIAS(DOS$wcsnupr, libd_wcsnupr);
DEFINE_PUBLIC_ALIAS(wcsnupr, libc_wcsnupr);
DEFINE_PUBLIC_ALIAS(DOS$wcscasestr, libd_wcscasestr);
DEFINE_PUBLIC_ALIAS(wcscasestr, libc_wcscasestr);
DEFINE_PUBLIC_ALIAS(DOS$wcspcpy, libd_wcspcpy);
DEFINE_PUBLIC_ALIAS(wcspcpy, libc_wcspcpy);
DEFINE_PUBLIC_ALIAS(DOS$wcspncpy, libd_wcspncpy);
DEFINE_PUBLIC_ALIAS(wcspncpy, libc_wcspncpy);
DEFINE_PUBLIC_ALIAS(DOS$wcsnchr, libd_wcsnchr);
DEFINE_PUBLIC_ALIAS(wcsnchr, libc_wcsnchr);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrchr, libd_wcsnrchr);
DEFINE_PUBLIC_ALIAS(wcsnrchr, libc_wcsnrchr);
DEFINE_PUBLIC_ALIAS(DOS$wcssep, libd_wcssep);
DEFINE_PUBLIC_ALIAS(wcssep, libc_wcssep);
DEFINE_PUBLIC_ALIAS(DOS$wcsfry, libd_wcsfry);
DEFINE_PUBLIC_ALIAS(wcsfry, libc_wcsfry);
DEFINE_PUBLIC_ALIAS(DOS$wcsndup, libd_wcsndup);
DEFINE_PUBLIC_ALIAS(wcsndup, libc_wcsndup);
DEFINE_PUBLIC_ALIAS(DOS$wcsrchrnul, libd_wcsrchrnul);
DEFINE_PUBLIC_ALIAS(wcsrchrnul, libc_wcsrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$wcsnchrnul, libd_wcsnchrnul);
DEFINE_PUBLIC_ALIAS(wcsnchrnul, libc_wcsnchrnul);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrchrnul, libd_wcsnrchrnul);
DEFINE_PUBLIC_ALIAS(wcsnrchrnul, libc_wcsnrchrnul);
DEFINE_PUBLIC_ALIAS(DOS$wcsoff, libd_wcsoff);
DEFINE_PUBLIC_ALIAS(wcsoff, libc_wcsoff);
DEFINE_PUBLIC_ALIAS(DOS$wcsroff, libd_wcsroff);
DEFINE_PUBLIC_ALIAS(wcsroff, libc_wcsroff);
DEFINE_PUBLIC_ALIAS(DOS$wcsnoff, libd_wcsnoff);
DEFINE_PUBLIC_ALIAS(wcsnoff, libc_wcsnoff);
DEFINE_PUBLIC_ALIAS(DOS$wcsnroff, libd_wcsnroff);
DEFINE_PUBLIC_ALIAS(wcsnroff, libc_wcsnroff);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcscmp, libd_fuzzy_wcscmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcscmp, libc_fuzzy_wcscmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcsncmp, libd_fuzzy_wcsncmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcsncmp, libc_fuzzy_wcsncmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcasecmp, libd_fuzzy_wmemcasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wmemcasecmp, libc_fuzzy_wmemcasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcscasecmp, libd_fuzzy_wcscasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcscasecmp, libc_fuzzy_wcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcsncasecmp, libd_fuzzy_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(fuzzy_wcsncasecmp, libc_fuzzy_wcsncasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wildwcscmp, libd_wildwcscmp);
DEFINE_PUBLIC_ALIAS(wildwcscmp, libc_wildwcscmp);
DEFINE_PUBLIC_ALIAS(DOS$wildwcscasecmp, libd_wildwcscasecmp);
DEFINE_PUBLIC_ALIAS(wildwcscasecmp, libc_wildwcscasecmp);
DEFINE_PUBLIC_ALIAS(DOS$wcsverscmp, libd_wcsverscmp);
DEFINE_PUBLIC_ALIAS(wcsverscmp, libc_wcsverscmp);
DEFINE_PUBLIC_ALIAS(DOS$_wcsncoll_l, libd_wcsncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsncoll_l, libd_wcsncoll_l);
DEFINE_PUBLIC_ALIAS(wcsncoll_l, libc_wcsncoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsicoll_l, libd_wcscasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscasecoll_l, libd_wcscasecoll_l);
DEFINE_PUBLIC_ALIAS(wcscasecoll_l, libc_wcscasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnicoll_l, libd_wcsncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsncasecoll_l, libd_wcsncasecoll_l);
DEFINE_PUBLIC_ALIAS(wcsncasecoll_l, libc_wcsncasecoll_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr_l, libd_wcslwr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcslwr_l, libd_wcslwr_l);
DEFINE_PUBLIC_ALIAS(wcslwr_l, libc_wcslwr_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr_l, libd_wcsupr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsupr_l, libd_wcsupr_l);
DEFINE_PUBLIC_ALIAS(wcsupr_l, libc_wcsupr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsnlwr_l, libd_wcsnlwr_l);
DEFINE_PUBLIC_ALIAS(wcsnlwr_l, libc_wcsnlwr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcsnupr_l, libd_wcsnupr_l);
DEFINE_PUBLIC_ALIAS(wcsnupr_l, libc_wcsnupr_l);
DEFINE_PUBLIC_ALIAS(DOS$wcscasestr_l, libd_wcscasestr_l);
DEFINE_PUBLIC_ALIAS(wcscasestr_l, libc_wcscasestr_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wmemcasecmp_l, libd_fuzzy_wmemcasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_wmemcasecmp_l, libc_fuzzy_wmemcasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcscasecmp_l, libd_fuzzy_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_wcscasecmp_l, libc_fuzzy_wcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$fuzzy_wcsncasecmp_l, libd_fuzzy_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(fuzzy_wcsncasecmp_l, libc_fuzzy_wcsncasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wildwcscasecmp_l, libd_wildwcscasecmp_l);
DEFINE_PUBLIC_ALIAS(wildwcscasecmp_l, libc_wildwcscasecmp_l);
DEFINE_PUBLIC_ALIAS(DOS$wcslcat, libd_wcslcat);
DEFINE_PUBLIC_ALIAS(wcslcat, libc_wcslcat);
DEFINE_PUBLIC_ALIAS(DOS$wcslcpy, libd_wcslcpy);
DEFINE_PUBLIC_ALIAS(wcslcpy, libc_wcslcpy);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnset, libd_wcsnset);
DEFINE_PUBLIC_ALIAS(DOS$wcsnset, libd_wcsnset);
DEFINE_PUBLIC_ALIAS(wcsnset, libc_wcsnset);
DEFINE_PUBLIC_ALIAS(DOS$_wcsrev, libd_wcsrev);
DEFINE_PUBLIC_ALIAS(DOS$wcsrev, libd_wcsrev);
DEFINE_PUBLIC_ALIAS(wcsrev, libc_wcsrev);
DEFINE_PUBLIC_ALIAS(DOS$_wcsset, libd_wcsset);
DEFINE_PUBLIC_ALIAS(DOS$wcsset, libd_wcsset);
DEFINE_PUBLIC_ALIAS(wcsset, libc_wcsset);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr, libd_wcslwr);
DEFINE_PUBLIC_ALIAS(DOS$wcslwr, libd_wcslwr);
DEFINE_PUBLIC_ALIAS(wcslwr, libc_wcslwr);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr, libd_wcsupr);
DEFINE_PUBLIC_ALIAS(DOS$wcsupr, libd_wcsupr);
DEFINE_PUBLIC_ALIAS(wcsupr, libc_wcsupr);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_WCHAR_C */
