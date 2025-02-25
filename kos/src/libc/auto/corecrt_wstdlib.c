/* HASH CRC-32:0x6e08e689 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_WSTDLIB_C
#define GUARD_LIBC_AUTO_CORECRT_WSTDLIB_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "corecrt_wstdlib.h"
#include "../user/stdlib.h"
#include "string.h"
#include "uchar.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) double
NOTHROW_NCX(LIBDCALL libd__wtof)(char16_t const *nptr) {
	return libd_wcstod(nptr, NULL);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) double
NOTHROW_NCX(LIBKCALL libc__wtof)(char32_t const *nptr) {
	return libc_wcstod(nptr, NULL);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) double
NOTHROW_NCX(LIBDCALL libd__wtof_l)(char16_t const *nptr,
                                   locale_t locale) {
	return libd_wcstod_l(nptr, NULL, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) double
NOTHROW_NCX(LIBKCALL libc__wtof_l)(char32_t const *nptr,
                                   locale_t locale) {
	return libc_wcstod_l(nptr, NULL, locale);
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd__itow)(int val,
                                 char16_t *buf,
                                 int radix) {
	libd__itow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc__itow)(int val,
                                 char32_t *buf,
                                 int radix) {
	libc__itow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd__ltow)(long val,
                                 char16_t *buf,
                                 int radix) {
	libd__ltow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc__ltow)(long val,
                                 char32_t *buf,
                                 int radix) {
	libc__ltow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd__ultow)(unsigned long val,
                                  char16_t *buf,
                                  int radix) {
	libd__ultow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc__ultow)(unsigned long val,
                                  char32_t *buf,
                                  int radix) {
	libc__ultow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd__i64tow)(s64 val,
                                   char16_t *buf,
                                   int radix) {
	libd__i64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc__i64tow)(s64 val,
                                   char32_t *buf,
                                   int radix) {
	libc__i64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd__ui64tow)(u64 val,
                                    char16_t *buf,
                                    int radix) {
	libd__ui64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc__ui64tow)(u64 val,
                                    char32_t *buf,
                                    int radix) {
	libc__ui64tow_s(val, buf, (size_t)-1, radix);
	return buf;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__itow_s)(int val,
                                   char16_t *buf,
                                   size_t buflen,
                                   int radix) {

	char16_t *p;
	unsigned int temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return 34;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (unsigned int)val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return 34;



	}
	temp = (unsigned int)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBKCALL libc__itow_s)(int val,
                                   char32_t *buf,
                                   size_t buflen,
                                   int radix) {

	char32_t *p;
	unsigned int temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return ERANGE;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (unsigned int)val;
	do {
		++p;
	} while ((temp /= (unsigned int)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (unsigned int)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned int)radix];
	} while ((temp /= (unsigned int)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__ltow_s)(long val,
                                   char16_t *buf,
                                   size_t buflen,
                                   int radix) {

	char16_t *p;
	unsigned long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return 34;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (unsigned long)val;
	do {
		++p;
	} while ((temp /= (unsigned long)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return 34;



	}
	temp = (unsigned long)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned long)radix];
	} while ((temp /= (unsigned long)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBKCALL libc__ltow_s)(long val,
                                   char32_t *buf,
                                   size_t buflen,
                                   int radix) {

	char32_t *p;
	unsigned long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return ERANGE;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (unsigned long)val;
	do {
		++p;
	} while ((temp /= (unsigned long)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (unsigned long)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned long)radix];
	} while ((temp /= (unsigned long)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__ultow_s)(unsigned long val,
                                    char16_t *buf,
                                    size_t buflen,
                                    int radix) {

	char16_t *p;
	unsigned long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;













	temp = (unsigned long)val;
	do {
		++p;
	} while ((temp /= (unsigned long)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return 34;



	}
	temp = (unsigned long)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned long)radix];
	} while ((temp /= (unsigned long)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBKCALL libc__ultow_s)(unsigned long val,
                                    char32_t *buf,
                                    size_t buflen,
                                    int radix) {

	char32_t *p;
	unsigned long temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;













	temp = (unsigned long)val;
	do {
		++p;
	} while ((temp /= (unsigned long)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (unsigned long)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (unsigned long)radix];
	} while ((temp /= (unsigned long)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__i64tow_s)(s64 val,
                                     char16_t *buf,
                                     size_t buflen,
                                     int radix) {

	char16_t *p;
	__UINT64_TYPE__ temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return 34;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (__UINT64_TYPE__)val;
	do {
		++p;
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return 34;



	}
	temp = (__UINT64_TYPE__)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (__UINT64_TYPE__)radix];
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBKCALL libc__i64tow_s)(s64 val,
                                     char32_t *buf,
                                     size_t buflen,
                                     int radix) {

	char32_t *p;
	__UINT64_TYPE__ temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;

	if (val < 0) {
		if (!buflen--) {

			return ERANGE;



		}
		*p++ = '-';
		val = -val;
	}

	temp = (__UINT64_TYPE__)val;
	do {
		++p;
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (__UINT64_TYPE__)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (__UINT64_TYPE__)radix];
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBDCALL libd__ui64tow_s)(u64 val,
                                      char16_t *buf,
                                      size_t buflen,
                                      int radix) {

	char16_t *p;
	__UINT64_TYPE__ temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;













	temp = (__UINT64_TYPE__)val;
	do {
		++p;
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return 34;



	}
	temp = (__UINT64_TYPE__)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (__UINT64_TYPE__)radix];
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/template/itoa_digits.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBKCALL libc__ui64tow_s)(u64 val,
                                      char32_t *buf,
                                      size_t buflen,
                                      int radix) {

	char32_t *p;
	__UINT64_TYPE__ temp;
	if unlikely(radix < 2)
		radix = 2;
	if unlikely(radix > 36)
		radix = 36;
	p = buf;













	temp = (__UINT64_TYPE__)val;
	do {
		++p;
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	if (buflen <= (size_t)(p - buf)) {

		return ERANGE;



	}
	temp = (__UINT64_TYPE__)val;
	*p = '\0';
	do {
		*--p = _itoa_upper_digits[temp % (__UINT64_TYPE__)radix];
	} while ((temp /= (__UINT64_TYPE__)radix) != 0);
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) s64
NOTHROW_NCX(LIBDCALL libd__wtoi64)(char16_t const *__restrict nptr) {
	return libd_wcsto64(nptr, NULL, 10);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_PURE WUNUSED ATTR_IN(1) s64
NOTHROW_NCX(LIBKCALL libc__wtoi64)(char32_t const *__restrict nptr) {
	return libc_wcsto64(nptr, NULL, 10);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBDCALL libd__wtoi_l)(char16_t const *__restrict nptr,
                                   locale_t locale) {
	return (int)libd_wcstol_l(nptr, NULL, 10, locale);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) int
NOTHROW_NCX(LIBKCALL libc__wtoi_l)(char32_t const *__restrict nptr,
                                   locale_t locale) {
	return (int)libc_wcstol_l(nptr, NULL, 10, locale);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) long int
NOTHROW_NCX(LIBDCALL libd__wtol_l)(char16_t const *__restrict nptr,
                                   locale_t locale) {
	return libd_wcstol_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc__wtol_l,libc__wtoi_l,ATTR_PURE WUNUSED ATTR_IN(1),long int,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
#else /* __SIZEOF_LONG__ == __SIZEOF_INT__ */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) long int
NOTHROW_NCX(LIBKCALL libc__wtol_l)(char32_t const *__restrict nptr,
                                   locale_t locale) {
	return libc_wcstol_l(nptr, NULL, 10, locale);
}
#endif /* __SIZEOF_LONG__ != __SIZEOF_INT__ */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) s64
NOTHROW_NCX(LIBDCALL libd__wtoi64_l)(char16_t const *__restrict nptr,
                                     locale_t locale) {
	return libd_wcsto64_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_INT__ == 8
DEFINE_INTERN_ALIAS_P(libc__wtoi64_l,libc__wtoi_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__wtoi64_l,libc__wtol_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
#elif __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc__wtoi64_l,libc__wtoll_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) s64
NOTHROW_NCX(LIBKCALL libc__wtoi64_l)(char32_t const *__restrict nptr,
                                     locale_t locale) {
	return libc_wcsto64_l(nptr, NULL, 10, locale);
}
#endif /* !... */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) __LONGLONG
NOTHROW_NCX(LIBDCALL libd__wtoll_l)(char16_t const *__restrict nptr,
                                    locale_t locale) {
	return libd_wcstoll_l(nptr, NULL, 10, locale);
}
#if __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
DEFINE_INTERN_ALIAS_P(libc__wtoll_l,libc__wtoi_l,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
DEFINE_INTERN_ALIAS_P(libc__wtoll_l,libc__wtol_l,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
#else /* ... */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_PURE WUNUSED ATTR_IN(1) __LONGLONG
NOTHROW_NCX(LIBKCALL libc__wtoll_l)(char32_t const *__restrict nptr,
                                    locale_t locale) {
	return libc_wcstoll_l(nptr, NULL, 10, locale);
}
#endif /* !... */
#include <libc/errno.h>
#include <asm/os/fcntl.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_IN(2) ATTR_OUTS(1, 3) char16_t *
NOTHROW_NCX(LIBDCALL libd__wfullpath)(char16_t *buf,
                                      char16_t const *path,
                                      size_t buflen) {
	size_t reqlen;
	char *utf8_path, *utf8_realpath;
	char16_t *wcs_realpath;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return NULL;
	utf8_realpath = libd__fullpath(NULL, utf8_path, 0);

	libc_free(utf8_path);

	if unlikely(!utf8_realpath)
		return NULL;
	wcs_realpath = libd_convert_mbstowcs(utf8_realpath);

	libc_free(utf8_realpath);

	if unlikely(!wcs_realpath)
		return NULL;
	if (!buf)
		return wcs_realpath;
	reqlen = libd_wcslen(wcs_realpath) + 1;
	if (reqlen > buflen) {

		libc_free(wcs_realpath);


		(void)libc_seterrno(ERANGE);



		return NULL;
	}
	buf = (char16_t *)libc_memcpyw(buf, wcs_realpath, reqlen);

	libc_free(wcs_realpath);

	return buf;
}
#include <libc/errno.h>
#include <asm/os/fcntl.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_IN(2) ATTR_OUTS(1, 3) char32_t *
NOTHROW_NCX(LIBKCALL libc__wfullpath)(char32_t *buf,
                                      char32_t const *path,
                                      size_t buflen) {
	size_t reqlen;
	char *utf8_path, *utf8_realpath;
	char32_t *wcs_realpath;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		return NULL;
	utf8_realpath = libc__fullpath(NULL, utf8_path, 0);

	libc_free(utf8_path);

	if unlikely(!utf8_realpath)
		return NULL;
	wcs_realpath = libc_convert_mbstowcs(utf8_realpath);

	libc_free(utf8_realpath);

	if unlikely(!wcs_realpath)
		return NULL;
	if (!buf)
		return wcs_realpath;
	reqlen = libc_wcslen(wcs_realpath) + 1;
	if (reqlen > buflen) {

		libc_free(wcs_realpath);


		(void)libc_seterrno(ERANGE);



		return NULL;
	}
	buf = (char32_t *)libc_memcpyl(buf, wcs_realpath, reqlen);

	libc_free(wcs_realpath);

	return buf;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wmakepath_s)(char16_t *buf,
                                        size_t buflen,
                                        char16_t const *drive,
                                        char16_t const *dir,
                                        char16_t const *file,
                                        char16_t const *ext) {
#define path_putn(p, n)                                  \
	do {                                                 \
		if unlikely(buflen < n)                          \
			goto err_buflen;                             \
		buf = (char16_t *)libc_mempcpyc(buf, p, n, sizeof(char16_t)); \
	}	__WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	}	__WHILE0
	if (drive && *drive) {
		path_putc(*drive);
		path_putc(':');
	}
	if (dir && *dir) {
		size_t len = libd_wcslen(dir);
		path_putn(dir, len);
		if (dir[len - 1] != '/' && dir[len - 1] != '\\')
			path_putc('\\');
	}
	if (file && *file) {
		size_t len = libd_wcslen(file);
		path_putn(file, len);
	}
	if (ext && *ext) {
		size_t len = libd_wcslen(ext);
		if (*ext != '.')
			path_putc('.');
		path_putn(ext, len);
	}
	path_putc('\0');
	return 0;
err_buflen:

	return 22;



#undef path_putn
#undef path_putc
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wmakepath_s)(char32_t *buf,
                                        size_t buflen,
                                        char32_t const *drive,
                                        char32_t const *dir,
                                        char32_t const *file,
                                        char32_t const *ext) {
#define path_putn(p, n)                                  \
	do {                                                 \
		if unlikely(buflen < n)                          \
			goto err_buflen;                             \
		buf = (char32_t *)libc_mempcpyc(buf, p, n, sizeof(char32_t)); \
	}	__WHILE0
#define path_putc(ch)          \
	do {                       \
		if unlikely(!buflen--) \
			goto err_buflen;   \
		*buf++ = (ch);         \
	}	__WHILE0
	if (drive && *drive) {
		path_putc(*drive);
		path_putc(':');
	}
	if (dir && *dir) {
		size_t len = libc_wcslen(dir);
		path_putn(dir, len);
		if (dir[len - 1] != '/' && dir[len - 1] != '\\')
			path_putc('\\');
	}
	if (file && *file) {
		size_t len = libc_wcslen(file);
		path_putn(file, len);
	}
	if (ext && *ext) {
		size_t len = libc_wcslen(ext);
		if (*ext != '.')
			path_putc('.');
		path_putn(ext, len);
	}
	path_putc('\0');
	return 0;
err_buflen:

	return EINVAL;



#undef path_putn
#undef path_putc
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) void
NOTHROW_NCX(LIBDCALL libd__wmakepath)(char16_t *__restrict buf,
                                      char16_t const *drive,
                                      char16_t const *dir,
                                      char16_t const *file,
                                      char16_t const *ext) {
	libd__wmakepath_s(buf, (size_t)-1, drive, dir, file, ext);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) void
NOTHROW_NCX(LIBKCALL libc__wmakepath)(char32_t *__restrict buf,
                                      char32_t const *drive,
                                      char32_t const *dir,
                                      char32_t const *file,
                                      char32_t const *ext) {
	libc__wmakepath_s(buf, (size_t)-1, drive, dir, file, ext);
}
#include <hybrid/typecore.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) void
NOTHROW_RPC(LIBDCALL libd__wsearchenv)(char16_t const *file,
                                       char16_t const *envvar,
                                       char16_t *__restrict resultpath) {
	libd__wsearchenv_s(file, envvar, resultpath, (size_t)-1);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3) void
NOTHROW_RPC(LIBKCALL libc__wsearchenv)(char32_t const *file,
                                       char32_t const *envvar,
                                       char32_t *__restrict resultpath) {
	libc__wsearchenv_s(file, envvar, resultpath, (size_t)-1);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) ATTR_OUT_OPT(4) ATTR_OUT_OPT(5) void
NOTHROW_NCX(LIBDCALL libd__wsplitpath)(char16_t const *__restrict abspath,
                                       char16_t *drive,
                                       char16_t *dir,
                                       char16_t *file,
                                       char16_t *ext) {
	libd__wsplitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) ATTR_OUT_OPT(4) ATTR_OUT_OPT(5) void
NOTHROW_NCX(LIBKCALL libc__wsplitpath)(char32_t const *__restrict abspath,
                                       char32_t *drive,
                                       char32_t *dir,
                                       char32_t *file,
                                       char32_t *ext) {
	libc__wsplitpath_s(abspath,
	             drive, drive ? 3 : 0,
	             dir, dir ? 256 : 0,
	             file, file ? 256 : 0,
	             ext, ext ? 256 : 0);
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9) errno_t
NOTHROW_NCX(LIBDCALL libd__wsplitpath_s)(char16_t const *__restrict abspath,
                                         char16_t *drive,
                                         size_t drivelen,
                                         char16_t *dir,
                                         size_t dirlen,
                                         char16_t *file,
                                         size_t filelen,
                                         char16_t *ext,
                                         size_t extlen) {
	size_t len, last_slash, last_dot;
	if unlikely(!abspath)
		goto err_inval;
	if unlikely((drive != NULL) != (drivelen != 0))
		goto err_inval;
	if unlikely((dir != NULL) != (dirlen != 0))
		goto err_inval;
	if unlikely((file != NULL) != (filelen != 0))
		goto err_inval;
	if unlikely((ext != NULL) != (extlen != 0))
		goto err_inval;
	for (len = 0; len < 3; ++len) {
		if (abspath[len] == ':') {
			if (drive) {
				if unlikely(drivelen <= len)
					goto err_range;
				libc_memcpyc(drive, abspath, len, sizeof(char16_t));
				drive[len] = 0;
			}
			abspath += len + 1;
			goto got_drive;
		}
	}
	if (drive)
		*drive = 0;
got_drive:
	last_slash = 0;
	last_dot = (size_t)-1;
	for (len = 0;; ++len) {
		char16_t ch = abspath[len];
		if (!ch)
			break;
		if (ch == '/' || ch == '\\')
			last_slash = len + 1;
		if (ch == '.')
			last_dot = len;
	}
	if (last_slash) {
		if (dir) {
			if unlikely(dirlen <= last_slash)
				goto err_range;
			libc_memcpyc(dir, abspath, last_slash, sizeof(char16_t));
			dir[last_slash] = 0;
		}
	} else {
		if (dir)
			*dir = 0;
	}
	if (last_dot != (size_t)-1 && last_dot > last_slash) {
		if (ext) {
			size_t path_extlen = len - last_dot;
			if unlikely(extlen <= path_extlen)
				goto err_range;
			libc_memcpyc(ext, abspath + last_dot, path_extlen, sizeof(char16_t));
			ext[path_extlen] = 0;
		}
	} else {
		if (ext)
			*ext = 0;
		last_dot = len;
	}
	if (file) {
		len = last_dot - last_slash;
		if unlikely(filelen <= len)
			goto err_range;
		libc_memcpyc(file, abspath + last_slash, len, sizeof(char16_t));
		file[len] = 0;
	}
	return 0;
err_inval:

	return 22;



err_range:

	(void)libc_seterrno(ERANGE);
	return 34;



}
#include <hybrid/typecore.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.environ") ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9) errno_t
NOTHROW_NCX(LIBKCALL libc__wsplitpath_s)(char32_t const *__restrict abspath,
                                         char32_t *drive,
                                         size_t drivelen,
                                         char32_t *dir,
                                         size_t dirlen,
                                         char32_t *file,
                                         size_t filelen,
                                         char32_t *ext,
                                         size_t extlen) {
	size_t len, last_slash, last_dot;
	if unlikely(!abspath)
		goto err_inval;
	if unlikely((drive != NULL) != (drivelen != 0))
		goto err_inval;
	if unlikely((dir != NULL) != (dirlen != 0))
		goto err_inval;
	if unlikely((file != NULL) != (filelen != 0))
		goto err_inval;
	if unlikely((ext != NULL) != (extlen != 0))
		goto err_inval;
	for (len = 0; len < 3; ++len) {
		if (abspath[len] == ':') {
			if (drive) {
				if unlikely(drivelen <= len)
					goto err_range;
				libc_memcpyc(drive, abspath, len, sizeof(char32_t));
				drive[len] = 0;
			}
			abspath += len + 1;
			goto got_drive;
		}
	}
	if (drive)
		*drive = 0;
got_drive:
	last_slash = 0;
	last_dot = (size_t)-1;
	for (len = 0;; ++len) {
		char32_t ch = abspath[len];
		if (!ch)
			break;
		if (ch == '/' || ch == '\\')
			last_slash = len + 1;
		if (ch == '.')
			last_dot = len;
	}
	if (last_slash) {
		if (dir) {
			if unlikely(dirlen <= last_slash)
				goto err_range;
			libc_memcpyc(dir, abspath, last_slash, sizeof(char32_t));
			dir[last_slash] = 0;
		}
	} else {
		if (dir)
			*dir = 0;
	}
	if (last_dot != (size_t)-1 && last_dot > last_slash) {
		if (ext) {
			size_t path_extlen = len - last_dot;
			if unlikely(extlen <= path_extlen)
				goto err_range;
			libc_memcpyc(ext, abspath + last_dot, path_extlen, sizeof(char32_t));
			ext[path_extlen] = 0;
		}
	} else {
		if (ext)
			*ext = 0;
		last_dot = len;
	}
	if (file) {
		len = last_dot - last_slash;
		if unlikely(filelen <= len)
			goto err_range;
		libc_memcpyc(file, abspath + last_slash, len, sizeof(char32_t));
		file[len] = 0;
	}
	return 0;
err_inval:

	return EINVAL;



err_range:

	(void)libc_seterrno(ERANGE);
	return ERANGE;



}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$_wtof,libd__wtof,ATTR_PURE WUNUSED ATTR_IN(1),double,NOTHROW_NCX,LIBDCALL,(char16_t const *nptr),(nptr));
DEFINE_PUBLIC_ALIAS_P(_wtof,libc__wtof,ATTR_PURE WUNUSED ATTR_IN(1),double,NOTHROW_NCX,LIBKCALL,(char32_t const *nptr),(nptr));
DEFINE_PUBLIC_ALIAS_P(DOS$_wtof_l,libd__wtof_l,ATTR_PURE WUNUSED ATTR_IN(1),double,NOTHROW_NCX,LIBDCALL,(char16_t const *nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_wtof_l,libc__wtof_l,ATTR_PURE WUNUSED ATTR_IN(1),double,NOTHROW_NCX,LIBKCALL,(char32_t const *nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_itow,libd__itow,ATTR_OUT(2),char16_t *,NOTHROW_NCX,LIBDCALL,(int val, char16_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(_itow,libc__itow,ATTR_OUT(2),char32_t *,NOTHROW_NCX,LIBKCALL,(int val, char32_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ltow,libd__ltow,ATTR_OUT(2),char16_t *,NOTHROW_NCX,LIBDCALL,(long val, char16_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(_ltow,libc__ltow,ATTR_OUT(2),char32_t *,NOTHROW_NCX,LIBKCALL,(long val, char32_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ultow,libd__ultow,ATTR_OUT(2),char16_t *,NOTHROW_NCX,LIBDCALL,(unsigned long val, char16_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(_ultow,libc__ultow,ATTR_OUT(2),char32_t *,NOTHROW_NCX,LIBKCALL,(unsigned long val, char32_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_i64tow,libd__i64tow,ATTR_OUT(2),char16_t *,NOTHROW_NCX,LIBDCALL,(s64 val, char16_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(_i64tow,libc__i64tow,ATTR_OUT(2),char32_t *,NOTHROW_NCX,LIBKCALL,(s64 val, char32_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ui64tow,libd__ui64tow,ATTR_OUT(2),char16_t *,NOTHROW_NCX,LIBDCALL,(u64 val, char16_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(_ui64tow,libc__ui64tow,ATTR_OUT(2),char32_t *,NOTHROW_NCX,LIBKCALL,(u64 val, char32_t *buf, int radix),(val,buf,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_itow_s,libd__itow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(int val, char16_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_itow_s,libc__itow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBKCALL,(int val, char32_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ltow_s,libd__ltow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(long val, char16_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_ltow_s,libc__ltow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBKCALL,(long val, char32_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ultow_s,libd__ultow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(unsigned long val, char16_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_ultow_s,libc__ultow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBKCALL,(unsigned long val, char32_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_i64tow_s,libd__i64tow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(s64 val, char16_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_i64tow_s,libc__i64tow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBKCALL,(s64 val, char32_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_ui64tow_s,libd__ui64tow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBDCALL,(u64 val, char16_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(_ui64tow_s,libc__ui64tow_s,ATTR_OUTS(2, 3),errno_t,NOTHROW_NCX,LIBKCALL,(u64 val, char32_t *buf, size_t buflen, int radix),(val,buf,buflen,radix));
DEFINE_PUBLIC_ALIAS_P(DOS$_wtoi64,libd__wtoi64,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr),(nptr));
DEFINE_PUBLIC_ALIAS_P(_wtoi64,libc__wtoi64,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr),(nptr));
DEFINE_PUBLIC_ALIAS_P(DOS$_wtoi_l,libd__wtoi_l,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_wtoi_l,libc__wtoi_l,ATTR_PURE WUNUSED ATTR_IN(1),int,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wtol_l,libd__wtol_l,ATTR_PURE WUNUSED ATTR_IN(1),long int,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_wtol_l,libc__wtol_l,ATTR_PURE WUNUSED ATTR_IN(1),long int,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wtoi64_l,libd__wtoi64_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_wtoi64_l,libc__wtoi64_l,ATTR_PURE WUNUSED ATTR_IN(1),s64,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wtoll_l,libd__wtoll_l,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(_wtoll_l,libc__wtoll_l,ATTR_PURE WUNUSED ATTR_IN(1),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, locale_t locale),(nptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wfullpath,libd__wfullpath,ATTR_IN(2) ATTR_OUTS(1, 3),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *buf, char16_t const *path, size_t buflen),(buf,path,buflen));
DEFINE_PUBLIC_ALIAS_P(_wfullpath,libc__wfullpath,ATTR_IN(2) ATTR_OUTS(1, 3),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *buf, char32_t const *path, size_t buflen),(buf,path,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$_wmakepath_s,libd__wmakepath_s,ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBDCALL,(char16_t *buf, size_t buflen, char16_t const *drive, char16_t const *dir, char16_t const *file, char16_t const *ext),(buf,buflen,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P(_wmakepath_s,libc__wmakepath_s,ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_IN_OPT(6) ATTR_OUTS(1, 2),errno_t,NOTHROW_NCX,LIBKCALL,(char32_t *buf, size_t buflen, char32_t const *drive, char32_t const *dir, char32_t const *file, char32_t const *ext),(buf,buflen,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$_wmakepath,libd__wmakepath,ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1),NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *drive, char16_t const *dir, char16_t const *file, char16_t const *ext),(buf,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P_VOID(_wmakepath,libc__wmakepath,ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1),NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *drive, char32_t const *dir, char32_t const *file, char32_t const *ext),(buf,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$_wsearchenv,libd__wsearchenv,ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3),NOTHROW_RPC,LIBDCALL,(char16_t const *file, char16_t const *envvar, char16_t *__restrict resultpath),(file,envvar,resultpath));
DEFINE_PUBLIC_ALIAS_P_VOID(_wsearchenv,libc__wsearchenv,ATTR_IN(1) ATTR_IN(2) ATTR_OUT(3),NOTHROW_RPC,LIBKCALL,(char32_t const *file, char32_t const *envvar, char32_t *__restrict resultpath),(file,envvar,resultpath));
DEFINE_PUBLIC_ALIAS_P_VOID(DOS$_wsplitpath,libd__wsplitpath,ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) ATTR_OUT_OPT(4) ATTR_OUT_OPT(5),NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict abspath, char16_t *drive, char16_t *dir, char16_t *file, char16_t *ext),(abspath,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P_VOID(_wsplitpath,libc__wsplitpath,ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) ATTR_OUT_OPT(4) ATTR_OUT_OPT(5),NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict abspath, char32_t *drive, char32_t *dir, char32_t *file, char32_t *ext),(abspath,drive,dir,file,ext));
DEFINE_PUBLIC_ALIAS_P(DOS$_wsplitpath_s,libd__wsplitpath_s,ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9),errno_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict abspath, char16_t *drive, size_t drivelen, char16_t *dir, size_t dirlen, char16_t *file, size_t filelen, char16_t *ext, size_t extlen),(abspath,drive,drivelen,dir,dirlen,file,filelen,ext,extlen));
DEFINE_PUBLIC_ALIAS_P(_wsplitpath_s,libc__wsplitpath_s,ATTR_IN(1) ATTR_OUTS(2, 3) ATTR_OUTS(4, 5) ATTR_OUTS(6, 7) ATTR_OUTS(8, 9),errno_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict abspath, char32_t *drive, size_t drivelen, char32_t *dir, size_t dirlen, char32_t *file, size_t filelen, char32_t *ext, size_t extlen),(abspath,drive,drivelen,dir,dirlen,file,filelen,ext,extlen));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WSTDLIB_C */
