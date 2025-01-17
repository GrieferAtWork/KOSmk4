/* HASH CRC-32:0xd852e5e9 */
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
#ifndef GUARD_LIBC_AUTO_WCHAR_C
#define GUARD_LIBC_AUTO_WCHAR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/wchar.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/unicode.h"
#include "wctype.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <asm/crt/stdio.h>
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint16_t
NOTHROW(LIBDCALL libd_btowc)(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint16_t)ch;
	return __WEOF16;
}
#include <asm/crt/stdio.h>
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED wint32_t
NOTHROW(LIBKCALL libc_btowc)(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint32_t)ch;
	return __WEOF32;
}
#include <asm/crt/stdio.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_wctob)(wint16_t ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (int)ch;
	return EOF;
}
#include <asm/crt/stdio.h>
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_wctob)(wint32_t ch) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBDCALL libd_mbrtowc)(char16_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *mbs) {
	size_t error;
	char16_t fallback_wc;
	if (mbs == NULL) {

		mbs = &_mb_shift;





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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBKCALL libc_mbrtowc)(char32_t *pwc,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *mbs) {
	size_t error;
	char32_t fallback_wc;
	if (mbs == NULL) {

		mbs = &_mb_shift;





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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBDCALL libd_wcrtomb)(char *__restrict str,
                                   char16_t wc,
                                   mbstate_t *mbs) {
	char *endptr;
	size_t result;

	/* unicode_c16toc8() */
	if (!mbs) {

		mbs = &_mb_shift;





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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1) size_t
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") WUNUSED ATTR_INOUT_OPT(3) ATTR_IN_OPT(1) size_t
NOTHROW_NCX(LIBDCALL libd_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *mbs) {
	char16_t wc;
	return libd_mbrtowc(&wc, str, maxlen, mbs);
}
/* >> mbrlen(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") WUNUSED ATTR_INOUT_OPT(3) ATTR_IN_OPT(1) size_t
NOTHROW_NCX(LIBKCALL libc_mbrlen)(char const *__restrict str,
                                  size_t maxlen,
                                  mbstate_t *mbs) {
	char32_t wc;
	return libc_mbrtowc(&wc, str, maxlen, mbs);
}
/* >> mbsrtowcs(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBDCALL libd_mbsrtowcs)(char16_t *__restrict dst,
                                     char const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libd_mbsnrtowcs(dst, psrc, (size_t)-1, dstlen, mbs);
}
/* >> mbsrtowcs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBKCALL libc_mbsrtowcs)(char32_t *__restrict dst,
                                     char const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libc_mbsnrtowcs(dst, psrc, (size_t)-1, dstlen, mbs);
}
/* >> wcsrtombs(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBDCALL libd_wcsrtombs)(char *dst,
                                     char16_t const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libd_wcsnrtombs(dst, psrc, (size_t)-1, dstlen, mbs);
}
/* >> wcsrtombs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBKCALL libc_wcsrtombs)(char *dst,
                                     char32_t const **__restrict psrc,
                                     size_t dstlen,
                                     mbstate_t *mbs) {
	return libc_wcsnrtombs(dst, psrc, (size_t)-1, dstlen, mbs);
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libd_wcstol,libd_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libd_wcstol,libd_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstol(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) long
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
DEFINE_INTERN_ALIAS_P(libc_wcstol,libc_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_wcstol,libc_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstol(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) long
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
DEFINE_INTERN_ALIAS_P(libd_wcstoul,libd_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libd_wcstoul,libd_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstoul(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) unsigned long
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
DEFINE_INTERN_ALIAS_P(libc_wcstoul,libc_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libc_wcstoul,libc_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstoul(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) unsigned long
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_IN_OPT(1) int
NOTHROW_NCX(LIBCCALL libc_mbsinit)(mbstate_t const *mbs) {
	return !mbs || mbstate_isempty(mbs);
}
/* >> wcscpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscpy)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
	return (char16_t *)libc_memcpyw(buf, src, libd_wcslen(src) + 1);
}
/* >> wcscpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscpy)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
	return (char32_t *)libc_memcpyl(buf, src, libc_wcslen(src) + 1);
}
/* >> wcscat(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscat)(char16_t *__restrict buf,
                                  char16_t const *__restrict src) {
	(void)(char16_t *)libc_memcpyw(libd_wcsend(buf), src, libd_wcslen(src) + 1);
	return buf;
}
/* >> wcscat(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscat)(char32_t *__restrict buf,
                                  char32_t const *__restrict src) {
	(void)(char32_t *)libc_memcpyl(libc_wcsend(buf), src, libc_wcslen(src) + 1);
	return buf;
}
/* >> wcsncat(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_INOUTS(1, 3) ATTR_INS(2, 3) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncat)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	char16_t *dst = libd_wcsend(buf);
	*(char16_t *)libc_mempcpyw(dst, src, srclen) = (char16_t)'\0';
	return buf;
}
/* >> wcsncat(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL ATTR_INOUTS(1, 3) ATTR_INS(2, 3) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsncat)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	char32_t *dst = libc_wcsend(buf);
	*(char32_t *)libc_mempcpyl(dst, src, srclen) = (char32_t)'\0';
	return buf;
}
/* >> wcsncpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	char16_t *ptr;
	size_t srclen = libd_wcsnlen(src, buflen);
	ptr = (char16_t *)libc_mempcpyw(buf, src, srclen);
	(void)(char16_t *)libc_memsetw(ptr, (char16_t)'\0', buflen - srclen);
	return buf;
}
/* >> wcsncpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	char32_t *ptr;
	size_t srclen = libc_wcsnlen(src, buflen);
	ptr = (char32_t *)libc_mempcpyl(buf, src, srclen);
	(void)(char32_t *)libc_memsetl(ptr, (char32_t)'\0', buflen - srclen);
	return buf;
}
/* >> wcscmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBDCALL libd_wcscoll)(char16_t const *s1,
                                   char16_t const *s2) {
	/* XXX: Implement properly? */
	return libd_wcscmp(s1, s2);
}
/* >> wcscoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBKCALL libc_wcscoll)(char32_t const *s1,
                                   char32_t const *s2) {
	/* XXX: Implement properly? */
	return libc_wcscmp(s1, s2);
}
#include <hybrid/typecore.h>
/* >> wcsxfrm(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm)(char16_t *dst,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	/* XXX: Implement properly? */
	size_t n = libd_wcsnlen(src, buflen);
	libc_memcpy(dst, src, n * sizeof(char16_t));
	return n;
}
#include <hybrid/typecore.h>
/* >> wcsxfrm(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBKCALL libc_wcsxfrm)(char32_t *dst,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	/* XXX: Implement properly? */
	size_t n = libc_wcsnlen(src, buflen);
	libc_memcpy(dst, src, n * sizeof(char32_t));
	return n;
}
#include <libc/template/stdstreams.h>
/* >> getwchar(3), getwchar_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc") wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_getwchar)(void) {
	return libd_fgetwc(stdin);
}
#include <libc/template/stdstreams.h>
/* >> getwchar(3), getwchar_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc") wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_getwchar)(void) {
	return libc_fgetwc(stdin);
}
#include <libc/template/stdstreams.h>
/* >> putwchar(3), putwchar_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc") wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_putwchar)(char16_t wc) {
	return libd_fputwc(wc, stdout);
}
#include <libc/template/stdstreams.h>
/* >> putwchar(3), putwchar_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc") wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_putwchar)(char32_t wc) {
	return libc_fputwc(wc, stdout);
}
#include <libc/errno.h>
#include <asm/crt/stdio.h>
/* >> fgetws(3), fgetws_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read") WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2) char16_t *
NOTHROW_CB_NCX(LIBDCALL libd_fgetws)(char16_t *__restrict buf,
                                     __STDC_INT_AS_SIZE_T bufsize,
                                     FILE *__restrict stream) {
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
		if (ch == (char16_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = (char16_t)'\n';
			ch = libd_fgetwc(stream);
			if (ch == __WEOF16) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == (char16_t)'\r')
				continue;
			libd_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == (char16_t)'\n')
			break;
	}
	buf[n] = (char16_t)'\0';
	return buf;
}
#include <libc/errno.h>
#include <asm/crt/stdio.h>
/* >> fgetws(3), fgetws_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.read") WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2) char32_t *
NOTHROW_CB_NCX(LIBKCALL libc_fgetws)(char32_t *__restrict buf,
                                     __STDC_INT_AS_SIZE_T bufsize,
                                     FILE *__restrict stream) {
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
		if (ch == (char32_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = (char32_t)'\n';
			ch = libc_fgetwc(stream);
			if (ch == __WEOF32) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == (char32_t)'\r')
				continue;
			libc_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == (char32_t)'\n')
			break;
	}
	buf[n] = (char32_t)'\0';
	return buf;
}
/* >> fputws(3), fputws_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") ATTR_IN(1) ATTR_INOUT(2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_fputws)(char16_t const *__restrict str,
                                     FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter(stream, str, libd_wcslen(str));
	return result;
}
/* >> fputws(3), fputws_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write") ATTR_IN(1) ATTR_INOUT(2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_fputws)(char32_t const *__restrict str,
                                     FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter(stream, str, libc_wcslen(str));
	return result;
}
/* >> wcsftime(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.strftime") ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C16FTIME(3, 0) ATTR_OUTS(1, 2) size_t
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.strftime") ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C32FTIME(3, 0) ATTR_OUTS(1, 2) size_t
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1) char32_t *
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
#include <hybrid/typecore.h>
/* >> wcslen(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBDCALL libd_wcslen)(char16_t const *__restrict str) {
	return (size_t)(libd_wcsend(str) - str);
}
#endif /* !LIBC_ARCH_HAVE_C16SLEN */
#ifndef LIBC_ARCH_HAVE_C32SLEN
#include <hybrid/typecore.h>
/* >> wcslen(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBKCALL libc_wcslen)(char32_t const *__restrict str) {
	return (size_t)(libc_wcsend(str) - str);
}
#endif /* !LIBC_ARCH_HAVE_C32SLEN */
/* >> wcsspn(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBDCALL libd_wcsspn)(char16_t const *haystack,
                                  char16_t const *accept) {
	char16_t const *iter = haystack;
	while (*iter && libd_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
/* >> wcsspn(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBKCALL libc_wcsspn)(char32_t const *haystack,
                                  char32_t const *accept) {
	char32_t const *iter = haystack;
	while (*iter && libc_wcschr(accept, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
/* >> wcscspn(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBDCALL libd_wcscspn)(char16_t const *haystack,
                                   char16_t const *reject) {
	char16_t const *iter = haystack;
	while (*iter && !libd_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
/* >> wcscspn(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBKCALL libc_wcscspn)(char32_t const *haystack,
                                   char32_t const *reject) {
	char32_t const *iter = haystack;
	while (*iter && !libc_wcschr(reject, *iter))
		++iter;
	return (size_t)(iter - haystack);
}
/* >> wcschr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspbrk)(char16_t const *haystack,
                                   char16_t const *accept) {
	char16_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		char16_t const *ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char16_t *)haystack - 1;
		}
	}
	return NULL;
}
/* >> wcspbrk(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspbrk)(char32_t const *haystack,
                                   char32_t const *accept) {
	char32_t haych, ch;
	while ((haych = *haystack++) != '\0') {
		char32_t const *ned_iter = accept;
		while ((ch = *ned_iter++) != '\0') {
			if (haych == ch)
				return (char32_t *)haystack - 1;
		}
	}
	return NULL;
}
/* >> wcsstr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char32_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.utility") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_fwide)(FILE *fp,
                                 int mode) {
	(void)fp;
	(void)mode;
	COMPILER_IMPURE();
	return 0;
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fwprintf)(FILE *__restrict stream,
                                        char16_t const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_fwprintf)(FILE *__restrict stream,
                                        char32_t const *__restrict format,
                                        ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vfwprintf)(FILE *__restrict stream,
                                        char16_t const *__restrict format,
                                        va_list args) {
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter, stream, format, args);
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vfwprintf)(FILE *__restrict stream,
                                        char32_t const *__restrict format,
                                        va_list args) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter, stream, format, args);
}
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_wprintf)(char16_t const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf(format, args);
	va_end(args);
	return result;
}
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_wprintf)(char32_t const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf(format, args);
	va_end(args);
	return result;
}
#include <libc/template/stdstreams.h>
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf") ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vwprintf)(char16_t const *__restrict format,
                                       va_list args) {
	return libd_vfwprintf(stdout, format, args);
}
#include <libc/template/stdstreams.h>
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf") ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vwprintf)(char32_t const *__restrict format,
                                       va_list args) {
	return libc_vfwprintf(stdout, format, args);
}
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fwscanf)(FILE *__restrict stream,
                                       char16_t const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_fwscanf)(FILE *__restrict stream,
                                       char32_t const *__restrict format,
                                       ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_wscanf)(char16_t const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf(format, args);
	va_end(args);
	return result;
}
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_wscanf)(char32_t const *__restrict format,
                                      ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwscanf(format, args);
	va_end(args);
	return result;
}
/* >> swscanf(3), vswscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf") ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 3) __STDC_INT_AS_SIZE_T
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
/* >> swscanf(3), vswscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf") ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 3) __STDC_INT_AS_SIZE_T
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.printf") ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 4) ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
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
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstod(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) double
NOTHROW_NCX(LIBDCALL libd_wcstod)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
	char16_t sign, ch = *nptr;
	double float_extension_mult;
	double fltval = 0.0;
	uint8_t numsys, digit;
	while (libd_iswspace((char16_t)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libd_iswdigit((char16_t)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libd_iswalnum((char16_t)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char16_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0(inf)
			                   : +__LIBM_MATHFUN0(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libd_iswalnum((char16_t)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char16_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1I(nan, NULL)
			                   : +__LIBM_MATHFUN1I(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0)
			goto done;
		float_extension_mult = (double)numsys;
		ch = *++nptr;
		goto next;

	default: {













		char16_t const *new_nptr;
		char32_t uni;
		new_nptr = (char16_t const *)nptr;
		uni = __libc_unicode_readutf16(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else





		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0) {
		fltval += (double)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char16_t float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char16_t *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstod(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) double
NOTHROW_NCX(LIBKCALL libc_wcstod)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
	char32_t sign, ch = *nptr;
	double float_extension_mult;
	double fltval = 0.0;
	uint8_t numsys, digit;
	while (libc_iswspace((char32_t)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libc_iswdigit((char32_t)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libc_iswalnum((char32_t)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char32_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0(inf)
			                   : +__LIBM_MATHFUN0(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libc_iswalnum((char32_t)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char32_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1I(nan, NULL)
			                   : +__LIBM_MATHFUN1I(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0)
			goto done;
		float_extension_mult = (double)numsys;
		ch = *++nptr;
		goto next;

	default: {





















		if (__libc_unicode_asdigit(ch, numsys, &digit)) {
			++nptr;
		} else

		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0) {
		fltval += (double)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char32_t float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char32_t *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstof(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) float
NOTHROW_NCX(LIBDCALL libd_wcstof)(char16_t const *__restrict nptr,
                                  char16_t **endptr) {
	char16_t sign, ch = *nptr;
	float float_extension_mult;
	float fltval = 0.0f;
	uint8_t numsys, digit;
	while (libd_iswspace((char16_t)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libd_iswdigit((char16_t)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libd_iswalnum((char16_t)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char16_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0F(inf)
			                   : +__LIBM_MATHFUN0F(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libd_iswalnum((char16_t)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char16_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1IF(nan, NULL)
			                   : +__LIBM_MATHFUN1IF(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0f;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0f)
			goto done;
		float_extension_mult = (float)numsys;
		ch = *++nptr;
		goto next;

	default: {













		char16_t const *new_nptr;
		char32_t uni;
		new_nptr = (char16_t const *)nptr;
		uni = __libc_unicode_readutf16(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else





		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0f) {
		fltval += (float)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char16_t float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0f;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0f;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0f;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char16_t *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstof(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) float
NOTHROW_NCX(LIBKCALL libc_wcstof)(char32_t const *__restrict nptr,
                                  char32_t **endptr) {
	char32_t sign, ch = *nptr;
	float float_extension_mult;
	float fltval = 0.0f;
	uint8_t numsys, digit;
	while (libc_iswspace((char32_t)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libc_iswdigit((char32_t)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libc_iswalnum((char32_t)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char32_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0F(inf)
			                   : +__LIBM_MATHFUN0F(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libc_iswalnum((char32_t)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char32_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1IF(nan, NULL)
			                   : +__LIBM_MATHFUN1IF(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0f;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0f)
			goto done;
		float_extension_mult = (float)numsys;
		ch = *++nptr;
		goto next;

	default: {





















		if (__libc_unicode_asdigit(ch, numsys, &digit)) {
			++nptr;
		} else

		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0f) {
		fltval += (float)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char32_t float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0f;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0f;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0f;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char32_t *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstold(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_wcstold)(char16_t const *__restrict nptr,
                                   char16_t **endptr) {
	char16_t sign, ch = *nptr;
	__LONGDOUBLE float_extension_mult;
	__LONGDOUBLE fltval = 0.0L;
	uint8_t numsys, digit;
	while (libd_iswspace((char16_t)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libd_iswdigit((char16_t)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libd_iswalnum((char16_t)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char16_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0L(inf)
			                   : +__LIBM_MATHFUN0L(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libd_iswalnum((char16_t)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char16_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1IL(nan, NULL)
			                   : +__LIBM_MATHFUN1IL(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0L;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0L)
			goto done;
		float_extension_mult = (__LONGDOUBLE)numsys;
		ch = *++nptr;
		goto next;

	default: {













		char16_t const *new_nptr;
		char32_t uni;
		new_nptr = (char16_t const *)nptr;
		uni = __libc_unicode_readutf16(&new_nptr);
		if (__libc_unicode_asdigit(uni, numsys, &digit)) {
			nptr = new_nptr;
		} else





		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0L) {
		fltval += (__LONGDOUBLE)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char16_t float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0L;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0L;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0L;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char16_t *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <ieee754.h>
#include <libm/inf.h>
#include <libm/nan.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstold(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __LONGDOUBLE
NOTHROW_NCX(LIBKCALL libc_wcstold)(char32_t const *__restrict nptr,
                                   char32_t **endptr) {
	char32_t sign, ch = *nptr;
	__LONGDOUBLE float_extension_mult;
	__LONGDOUBLE fltval = 0.0L;
	uint8_t numsys, digit;
	while (libc_iswspace((char32_t)ch))
		ch = *++nptr;
	sign = ch;
	if (sign == '+' || sign == '-')
		ch = *++nptr;
	if (ch == '0') {
		ch = *++nptr;
		if (ch == 'x' || ch == 'X') {
			ch = *++nptr;
			numsys = 16;
		} else if (ch == 'b' || ch == 'B') {
			ch = *++nptr;
			numsys = 2;
		} else if (ch == '.') {
			numsys = 10;
		} else if (!libc_iswdigit((char32_t)ch)) {
			goto done;
		} else {
			/*numsys = 8;*/ /* Would be non-conforming */
			numsys = 10;
		}
	} else {

		if ((ch == 'i' || ch == 'I') &&
		    (nptr[1] == 'n' || nptr[1] == 'N') &&
		    (nptr[2] == 'f' || nptr[2] == 'F') &&
		    !libc_iswalnum((char32_t)nptr[3])) {
			nptr += 3;
			if (endptr)
				*endptr = (char32_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN0L(inf)
			                   : +__LIBM_MATHFUN0L(inf);
		}
		if ((ch == 'n' || ch == 'N') &&
		    (nptr[1] == 'a' || nptr[1] == 'A') &&
		    (nptr[2] == 'n' || nptr[2] == 'N') &&
		    !libc_iswalnum((char32_t)nptr[3])) {
			nptr += 3;
			if (*nptr == '(') {
				++nptr;
				while (*nptr != ')')
					++nptr;
				++nptr;
				/* XXX: Custom nan-tag? */
			}
			if (endptr)
				*endptr = (char32_t *)nptr;
			return sign == '-' ? -__LIBM_MATHFUN1IL(nan, NULL)
			                   : +__LIBM_MATHFUN1IL(nan, NULL);
		}

		numsys = 10;
	}

	float_extension_mult = 0.0L;
next:
	switch (ch) {
	case 'p':
	case 'P':
		if (numsys == 10)
			goto done;
		goto flt_exp;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		digit = ch - '0';
		break;

	case 'e':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
		digit = 10 + ch - 'a';
		break;

	case 'E':
		if (numsys == 10)
			goto flt_exp;
		ATTR_FALLTHROUGH
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
		digit = 10 + ch - 'A';
		break;

	case '.':
		if (float_extension_mult != 0.0L)
			goto done;
		float_extension_mult = (__LONGDOUBLE)numsys;
		ch = *++nptr;
		goto next;

	default: {





















		if (__libc_unicode_asdigit(ch, numsys, &digit)) {
			++nptr;
		} else

		{
			goto done;
		}
	}	break;

	}
	if unlikely(digit >= numsys)
		goto done;
	ch = *++nptr;
	if (float_extension_mult != 0.0L) {
		fltval += (__LONGDOUBLE)digit / float_extension_mult;
		float_extension_mult *= numsys;
	} else {
		fltval = fltval * numsys + digit;
	}
	goto next;
	{
#define float_extension_pos digit
		unsigned int float_extension_off;
		char32_t float_exp_mode;
flt_exp:
		float_exp_mode = ch;
		float_extension_pos = 1;
		float_extension_off = 0;
		ch = *++nptr;
		if (ch == '-' || ch == '+') {
			float_extension_pos = (ch == '+');
			ch = *++nptr;
		}
		while (ch >= '0' && ch <= '9') {
			float_extension_off *= 10;
			float_extension_off += ch - '0';
			ch = *++nptr;
		}
		float_extension_mult = 1.0L;
		if (float_exp_mode == 'e' || float_exp_mode == 'E') {
			while (float_extension_off != 0) {
				float_extension_mult *= 10.0L;
				--float_extension_off;
			}
		} else {
			while (float_extension_off != 0) {
				float_extension_mult *= 2.0L;
				--float_extension_off;
			}
		}
		if (float_extension_pos) {
			fltval *= float_extension_mult;
		} else {
			fltval /= float_extension_mult;
		}
#undef float_extension_pos
		/* FALLTHRU to "done" */
	}
done:
	if (endptr)
		*endptr = (char32_t *)nptr;
	if (sign == '-')
		fltval = -fltval;
	return fltval;
}
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 8
DEFINE_INTERN_ALIAS_P(libd_wcstoll,libd_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libd_wcstoll,libd_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __LONGLONG
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
DEFINE_INTERN_ALIAS_P(libc_wcstoll,libc_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_wcstoll,libc_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __LONGLONG
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
DEFINE_INTERN_ALIAS_P(libd_wcstoull,libd_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libd_wcstoull,libd_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstoull(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __ULONGLONG
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
DEFINE_INTERN_ALIAS_P(libc_wcstoull,libc_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#elif __SIZEOF_LONG_LONG__ == 4
DEFINE_INTERN_ALIAS_P(libc_wcstoull,libc_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#else /* ... */
/* >> wcstoull(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) __ULONGLONG
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
#include <hybrid/typecore.h>
#ifndef ____vfc16scanf_getc_defined
#define ____vfc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBDCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 2
__LOCAL_LIBC(vfc16scanf_getc) __format_word_t
(__FORMATPRINTER_CC vfc16scanf_getc)(void *arg) {
	return (__format_word_t)libd_fgetwc((FILE *)arg);
}
#endif /* !__LIBDCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 2 */
__LOCAL_LIBC(vfc16scanf_ungetc) ssize_t
(__FORMATPRINTER_CC vfc16scanf_ungetc)(void *arg, __format_word_t word) {
	return libd_ungetwc((wint16_t)word, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfc16scanf_getc_defined */
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vfwscanf)(FILE *__restrict stream,
                                       char16_t const *__restrict format,
                                       va_list args) {
#if defined(__LIBDCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == 2
	return libd_format_vwscanf((pformatgetc)(void *)&libd_fgetwc,
	                      &__NAMESPACE_LOCAL_SYM vfc16scanf_ungetc,
	                      (void *)stream,
	                      format, args);
#else /* __LIBDCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == 2 */
	return libd_format_vwscanf(&__NAMESPACE_LOCAL_SYM vfc16scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM vfc16scanf_ungetc,
	                      (void *)stream,
	                      format, args);
#endif /* !__LIBDCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 2 */
}
#include <hybrid/typecore.h>
#ifndef ____vfc32scanf_getc_defined
#define ____vfc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBKCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 4
__LOCAL_LIBC(vfc32scanf_getc) __format_word_t
(__FORMATPRINTER_CC vfc32scanf_getc)(void *arg) {
	return (__format_word_t)libc_fgetwc((FILE *)arg);
}
#endif /* !__LIBKCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 4 */
__LOCAL_LIBC(vfc32scanf_ungetc) ssize_t
(__FORMATPRINTER_CC vfc32scanf_ungetc)(void *arg, __format_word_t word) {
	return libc_ungetwc((wint32_t)word, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfc32scanf_getc_defined */
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vfwscanf)(FILE *__restrict stream,
                                       char32_t const *__restrict format,
                                       va_list args) {
#if defined(__LIBKCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == 4
	return libc_format_vwscanf((pformatgetc)(void *)&libc_fgetwc,
	                      &__NAMESPACE_LOCAL_SYM vfc32scanf_ungetc,
	                      (void *)stream,
	                      format, args);
#else /* __LIBKCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == 4 */
	return libc_format_vwscanf(&__NAMESPACE_LOCAL_SYM vfc32scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM vfc32scanf_ungetc,
	                      (void *)stream,
	                      format, args);
#endif /* !__LIBKCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 4 */
}
#include <libc/template/stdstreams.h>
/* >> vwscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vwscanf)(char16_t const *__restrict format,
                                      va_list args) {
	return libd_vfwscanf(stdin, format, args);
}
#include <libc/template/stdstreams.h>
/* >> vwscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vwscanf)(char32_t const *__restrict format,
                                      va_list args) {
	return libc_vfwscanf(stdin, format, args);
}
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#include <asm/crt/stdio.h>
#ifndef ____vsc16scanf_getc_defined
#define ____vsc16scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc16scanf_getc) __format_word_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char16_t result        = *reader++;
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return (__format_word_t)result;
}
__LOCAL_LIBC(vsc16scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, __format_word_t UNUSED(word)) {
	--(*(char16_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc16scanf_getc_defined */
/* >> swscanf(3), vswscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.format.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBDCALL libd_vswscanf)(char16_t const *__restrict input,
                                    char16_t const *__restrict format,
                                    va_list args) {
	return libd_format_vwscanf(&__NAMESPACE_LOCAL_SYM vsc16scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM vsc16scanf_ungetc,
	                      (void *)&input, format, args);
}
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#include <asm/crt/stdio.h>
#ifndef ____vsc32scanf_getc_defined
#define ____vsc32scanf_getc_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vsc32scanf_getc) __format_word_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result        = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return (__format_word_t)result;
}
__LOCAL_LIBC(vsc32scanf_ungetc) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, __format_word_t UNUSED(word)) {
	--(*(char32_t const **)arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !____vsc32scanf_getc_defined */
/* >> swscanf(3), vswscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.format.scanf") WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBKCALL libc_vswscanf)(char32_t const *__restrict input,
                                    char32_t const *__restrict format,
                                    va_list args) {
	return libc_format_vwscanf(&__NAMESPACE_LOCAL_SYM vsc32scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM vsc32scanf_ungetc,
	                      (void *)&input, format, args);
}
/* >> wcscasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBDCALL libd_wcscasecmp_l)(char16_t const *s1,
                                        char16_t const *s2,
                                        locale_t locale) {
	(void)locale;
	return libd_wcscasecmp(s1, s2);
}
/* >> wcscasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBKCALL libc_wcscasecmp_l)(char32_t const *s1,
                                        char32_t const *s2,
                                        locale_t locale) {
	(void)locale;
	return libc_wcscasecmp(s1, s2);
}
/* >> wcsncasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecmp_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libd_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcsncasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecmp_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         size_t maxlen,
                                         locale_t locale) {
	(void)locale;
	return libc_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcscoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBDCALL libd_wcscoll_l)(char16_t const *s1,
                                     char16_t const *s2,
                                     locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libd_wcscoll(s1, s2);
}
/* >> wcscoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBKCALL libc_wcscoll_l)(char32_t const *s1,
                                     char32_t const *s2,
                                     locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_wcscoll(s1, s2);
}
/* >> wcsxfrm_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBDCALL libd_wcsxfrm_l)(char16_t *dst,
                                     char16_t const *__restrict src,
                                     size_t buflen,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsxfrm(dst, src, buflen);
}
/* >> wcsxfrm_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_INS(2, 3) ATTR_OUTS(1, 3) size_t
NOTHROW_NCX(LIBKCALL libc_wcsxfrm_l)(char32_t *dst,
                                     char32_t const *__restrict src,
                                     size_t buflen,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsxfrm(dst, src, buflen);
}
/* >> wcpcpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpcpy)(char16_t *__restrict dst,
                                  char16_t const *__restrict src) {
	return (char16_t *)libc_mempcpyw(dst, src, libd_wcslen(src) + 1);
}
/* >> wcpcpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcpcpy)(char32_t *__restrict dst,
                                  char32_t const *__restrict src) {
	return (char32_t *)libc_mempcpyl(dst, src, libc_wcslen(src) + 1);
}
/* >> wcpncpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcpncpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	buf = (char16_t *)libc_mempcpyw(buf, src, srclen);
	buf = (char16_t *)libc_memsetw(buf, (char16_t)'\0', (size_t)(buflen - srclen));
	return buf;
}
/* >> wcpncpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcpncpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src,
                                   size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	buf = (char32_t *)libc_mempcpyl(buf, src, srclen);
	buf = (char32_t *)libc_memsetl(buf, (char32_t)'\0', (size_t)(buflen - srclen));
	return buf;
}
/* >> mbsnrtowcs(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1) size_t
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1) size_t
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1) size_t
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
		if (ch == (char16_t)'\0') {
			src = NULL; /* NUL-character reached */
			break;
		}
	}
	if (dst != NULL)
		*psrc = src; /* Only update source if destination was given */
	return result;
}
/* >> wcsnrtombs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1) size_t
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
		if (ch == (char32_t)'\0') {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnlen)(char16_t const *__restrict str,
                                   size_t maxlen) {
	return (size_t)(libd_wcsnend(str, maxlen) - str);
}
#endif /* !LIBC_ARCH_HAVE_C16SNLEN */
#ifndef LIBC_ARCH_HAVE_C32SNLEN
/* >> wcsnlen(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnlen)(char32_t const *__restrict str,
                                   size_t maxlen) {
	return (size_t)(libc_wcsnend(str, maxlen) - str);
}
#endif /* !LIBC_ARCH_HAVE_C32SNLEN */
#include <hybrid/typecore.h>
/* >> wcsdup(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsdup)(char16_t const *__restrict string) {
	size_t resultsize = (libd_wcslen(string) + 1) * sizeof(char16_t);
	char16_t *result = (char16_t *)libc_malloc(resultsize);
	if likely(result)
		result = (char16_t *)libc_memcpy(result, string, resultsize);
	return result;
}
#include <hybrid/typecore.h>
/* >> wcsdup(3) */
INTERN ATTR_SECTION(".text.crt.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsdup)(char32_t const *__restrict string) {
	size_t resultsize = (libc_wcslen(string) + 1) * sizeof(char32_t);
	char32_t *result = (char32_t *)libc_malloc(resultsize);
	if likely(result)
		result = (char32_t *)libc_memcpy(result, string, resultsize);
	return result;
}
#include <libc/unicode.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_wcwidth)(char16_t ch) {
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
NOTHROW(LIBKCALL libc_wcwidth)(char32_t ch) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) __STDC_INT32_AS_SSIZE_T
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)) __STDC_INT32_AS_SSIZE_T
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcschrnul)(char32_t const *haystack,
                                     char32_t needle) {
	for (; *haystack; ++haystack) {
		if ((char32_t)*haystack == (char32_t)needle)
			break;
	}
	return (char32_t *)haystack;
}
/* >> wcstol_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) long
NOTHROW_NCX(LIBDCALL libd_wcstol_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstol(nptr, endptr, base);
}
/* >> wcstol_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) long
NOTHROW_NCX(LIBKCALL libc_wcstol_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    __STDC_INT_AS_UINT_T base,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstol(nptr, endptr, base);
}
/* >> wcstoul_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) unsigned long
NOTHROW_NCX(LIBDCALL libd_wcstoul_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstoul(nptr, endptr, base);
}
/* >> wcstoul_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) unsigned long
NOTHROW_NCX(LIBKCALL libc_wcstoul_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstoul(nptr, endptr, base);
}
/* >> wcstoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __LONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoll_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstoll(nptr, endptr, base);
}
/* >> wcstoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __LONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoll_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstoll(nptr, endptr, base);
}
/* >> wcstoull_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __ULONGLONG
NOTHROW_NCX(LIBDCALL libd_wcstoull_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstoull(nptr, endptr, base);
}
/* >> wcstoull_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __ULONGLONG
NOTHROW_NCX(LIBKCALL libc_wcstoull_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstoull(nptr, endptr, base);
}
/* >> wcstof_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) float
NOTHROW_NCX(LIBDCALL libd_wcstof_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstof(nptr, endptr);
}
/* >> wcstof_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) float
NOTHROW_NCX(LIBKCALL libc_wcstof_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstof(nptr, endptr);
}
/* >> wcstod_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) double
NOTHROW_NCX(LIBDCALL libd_wcstod_l)(char16_t const *__restrict nptr,
                                    char16_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libd_wcstod(nptr, endptr);
}
/* >> wcstod_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) double
NOTHROW_NCX(LIBKCALL libc_wcstod_l)(char32_t const *__restrict nptr,
                                    char32_t **endptr,
                                    locale_t locale) {
	(void)locale;
	return libc_wcstod(nptr, endptr);
}
/* >> wcstold_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __LONGDOUBLE
NOTHROW_NCX(LIBDCALL libd_wcstold_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     locale_t locale) {
	(void)locale;
	return libd_wcstold(nptr, endptr);
}
/* >> wcstold_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_IN(1) ATTR_OUT_OPT(2) __LONGDOUBLE
NOTHROW_NCX(LIBKCALL libc_wcstold_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     locale_t locale) {
	(void)locale;
	return libc_wcstold(nptr, endptr);
}
#include <libc/template/stdstreams.h>
/* >> getwchar(3), getwchar_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc") wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_getwchar_unlocked)(void) {
	return libd_fgetwc_unlocked(stdin);
}
#include <libc/template/stdstreams.h>
/* >> getwchar(3), getwchar_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc") wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_getwchar_unlocked)(void) {
	return libc_fgetwc_unlocked(stdin);
}
#include <libc/template/stdstreams.h>
/* >> putwchar(3), putwchar_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc") wint16_t
NOTHROW_CB_NCX(LIBDCALL libd_putwchar_unlocked)(char16_t wc) {
	return libd_fputwc_unlocked(wc, stdout);
}
#include <libc/template/stdstreams.h>
/* >> putwchar(3), putwchar_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc") wint32_t
NOTHROW_CB_NCX(LIBKCALL libc_putwchar_unlocked)(char32_t wc) {
	return libc_fputwc_unlocked(wc, stdout);
}
#include <asm/crt/stdio.h>
#include <libc/errno.h>
/* >> fgetws(3), fgetws_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.read") ATTR_INOUT(3) ATTR_OUTS(1, 2) char16_t *
NOTHROW_CB_NCX(LIBDCALL libd_fgetws_unlocked)(char16_t *__restrict buf,
                                              __STDC_INT_AS_SIZE_T bufsize,
                                              FILE *__restrict stream) {
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
		if (ch == (char16_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = (char16_t)'\n';
			ch = libd_fgetwc_unlocked(stream);
			if (ch == __WEOF16) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == (char16_t)'\r')
				continue;
			libd_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == (char16_t)'\n')
			break;
	}
	buf[n] = (char16_t)'\0';
	return buf;
}
#include <asm/crt/stdio.h>
#include <libc/errno.h>
/* >> fgetws(3), fgetws_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.read") ATTR_INOUT(3) ATTR_OUTS(1, 2) char32_t *
NOTHROW_CB_NCX(LIBKCALL libc_fgetws_unlocked)(char32_t *__restrict buf,
                                              __STDC_INT_AS_SIZE_T bufsize,
                                              FILE *__restrict stream) {
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
		if (ch == (char32_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = (char32_t)'\n';
			ch = libc_fgetwc_unlocked(stream);
			if (ch == __WEOF32) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == (char32_t)'\r')
				continue;
			libc_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == (char32_t)'\n')
			break;
	}
	buf[n] = (char32_t)'\0';
	return buf;
}
/* >> fputws(3), fputws_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.write") ATTR_IN(1) ATTR_INOUT(2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_fputws_unlocked)(char16_t const *__restrict str,
                                              FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter_unlocked(stream, str, libd_wcslen(str));
	return result;
}
/* >> fputws(3), fputws_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write") ATTR_IN(1) ATTR_INOUT(2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_fputws_unlocked)(char32_t const *__restrict str,
                                              FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter_unlocked(stream, str, libc_wcslen(str));
	return result;
}
/* >> wcsftime_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.format.strftime") ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C16FTIME(3, 0) ATTR_OUTS(1, 2) size_t
NOTHROW_NCX(LIBDCALL libd_wcsftime_l)(char16_t *__restrict buf,
                                      size_t maxsize,
                                      char16_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libd_wcsftime(buf, maxsize, format, tp);
}
/* >> wcsftime_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.format.strftime") ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C32FTIME(3, 0) ATTR_OUTS(1, 2) size_t
NOTHROW_NCX(LIBKCALL libc_wcsftime_l)(char32_t *__restrict buf,
                                      size_t maxsize,
                                      char32_t const *__restrict format,
                                      struct tm const *__restrict tp,
                                      locale_t locale) {
	(void)locale;
	return libc_wcsftime(buf, maxsize, format, tp);
}
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
#ifndef ____free_and_return_zero_defined
#define ____free_and_return_zero_defined
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(free_and_return_zero) int
(__LIBKCALL __free_and_return_zero)(void *arg) {
	libc_free(arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#endif /* !____free_and_return_zero_defined */
#ifndef ____fopen_wprinter_flush_defined
#define ____fopen_wprinter_flush_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fopen_wprinter_flush) int
(__LIBKCALL __fopen_wprinter_flush)(void *arg) {
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *me = (struct __local_format_8tow_data *)arg;

	/* Verify that the mbstate is in an empty state. */
	if (__mbstate_isempty(&me->fd_incomplete))
		return 0;

	/* If it isn't then we must indicate an illegal-sequence error. */
#ifdef EILSEQ
	return libc_seterrno(EILSEQ);
#else /* EILSEQ */
	return libc_seterrno(1);
#endif /* !EILSEQ */
}
__NAMESPACE_LOCAL_END
#endif /* !____fopen_wprinter_flush_defined */
/* >> fopen_wprinter(3)
 * Create and return a new write-only file-stream that will write to the given printer.
 * Note  that by default, the buffering is enabled for the file-stream, meaning you may
 * have to call `fflush(return)' before printed data is committed to the given printer.
 * - Buffering can be disabled with `setvbuf(return, NULL, _IONBF, 0)'
 * - When `printer' returns a negative value, `ferror(return)' becomes set
 * - When calling `fflush(return)', with the current unicode sequence is incomplete,
 *   that function will return with `-1' and `errno == EILSEQ'
 * @return: * :   A file-stream that emits its data to `printer'
 * @return: NULL: Insufficient memory. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1)) FILE *
NOTHROW_NCX(LIBDCALL libd_fopen_wprinter)(__pc16formatprinter printer,
                                          void *arg) {
	FILE *result;
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		pc16formatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *cookie;
	cookie = (struct __local_format_8tow_data *)libc_malloc(sizeof(struct __local_format_8tow_data));
	if unlikely(!cookie)
		return NULL;
	cookie->fd_printer = printer;
	cookie->fd_arg     = arg;
	__mbstate_init(&cookie->fd_incomplete);

	/* KOS's pformatprinter is ABI-compatible with the `writefn' of `funopen2(3)' / `funopen2_64(3)'
	 * -> As such, this function can super-easily be implemented with the help of that one! */


	result = libc_funopen2_64(cookie, NULL, (ssize_t (LIBKCALL *)(void *, void const *, size_t))&libd_format_8tow, NULL,
	                     &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush,
	                     &__NAMESPACE_LOCAL_SYM __free_and_return_zero);















	/* Cleanup on error. */

	if unlikely(!result)
		libc_free(cookie);

	return result;
}
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
#include <bits/crt/mbstate.h>
#include <libc/errno.h>
#ifndef ____free_and_return_zero_defined
#define ____free_and_return_zero_defined
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(free_and_return_zero) int
(__LIBKCALL __free_and_return_zero)(void *arg) {
	libc_free(arg);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
#endif /* !____free_and_return_zero_defined */
#ifndef ____fopen_wprinter_flush_defined
#define ____fopen_wprinter_flush_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fopen_wprinter_flush) int
(__LIBKCALL __fopen_wprinter_flush)(void *arg) {
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *me = (struct __local_format_8tow_data *)arg;

	/* Verify that the mbstate is in an empty state. */
	if (__mbstate_isempty(&me->fd_incomplete))
		return 0;

	/* If it isn't then we must indicate an illegal-sequence error. */
#ifdef EILSEQ
	return libc_seterrno(EILSEQ);
#else /* EILSEQ */
	return libc_seterrno(1);
#endif /* !EILSEQ */
}
__NAMESPACE_LOCAL_END
#endif /* !____fopen_wprinter_flush_defined */
/* >> fopen_wprinter(3)
 * Create and return a new write-only file-stream that will write to the given printer.
 * Note  that by default, the buffering is enabled for the file-stream, meaning you may
 * have to call `fflush(return)' before printed data is committed to the given printer.
 * - Buffering can be disabled with `setvbuf(return, NULL, _IONBF, 0)'
 * - When `printer' returns a negative value, `ferror(return)' becomes set
 * - When calling `fflush(return)', with the current unicode sequence is incomplete,
 *   that function will return with `-1' and `errno == EILSEQ'
 * @return: * :   A file-stream that emits its data to `printer'
 * @return: NULL: Insufficient memory. */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") WUNUSED NONNULL((1)) FILE *
NOTHROW_NCX(LIBKCALL libc_fopen_wprinter)(__pc32formatprinter printer,
                                          void *arg) {
	FILE *result;
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		pc32formatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *cookie;
	cookie = (struct __local_format_8tow_data *)libc_malloc(sizeof(struct __local_format_8tow_data));
	if unlikely(!cookie)
		return NULL;
	cookie->fd_printer = printer;
	cookie->fd_arg     = arg;
	__mbstate_init(&cookie->fd_incomplete);

	/* KOS's pformatprinter is ABI-compatible with the `writefn' of `funopen2(3)' / `funopen2_64(3)'
	 * -> As such, this function can super-easily be implemented with the help of that one! */


	result = libc_funopen2_64(cookie, NULL, (ssize_t (LIBKCALL *)(void *, void const *, size_t))&libc_format_8tow, NULL,
	                     &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush,
	                     &__NAMESPACE_LOCAL_SYM __free_and_return_zero);















	/* Cleanup on error. */

	if unlikely(!result)
		libc_free(cookie);

	return result;
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vfwprintf_unlocked)(FILE *__restrict stream,
                                                 char16_t const *__restrict format,
                                                 va_list args) {
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter_unlocked,
	                                              stream, format, args);
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vfwprintf_unlocked)(FILE *__restrict stream,
                                                 char32_t const *__restrict format,
                                                 va_list args) {
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter_unlocked,
	                                              stream, format, args);
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fwprintf_unlocked)(FILE *__restrict stream,
                                                 char16_t const *__restrict format,
                                                 ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_fwprintf_unlocked)(FILE *__restrict stream,
                                                 char32_t const *__restrict format,
                                                 ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_wprintf_unlocked)(char16_t const *__restrict format,
                                                ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_wprintf_unlocked)(char32_t const *__restrict format,
                                                ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
#include <libc/template/stdstreams.h>
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf") ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vwprintf_unlocked)(char16_t const *__restrict format,
                                                va_list args) {
	return libd_vfwprintf_unlocked(stdout, format, args);
}
#include <libc/template/stdstreams.h>
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf") ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vwprintf_unlocked)(char32_t const *__restrict format,
                                                va_list args) {
	return libc_vfwprintf_unlocked(stdout, format, args);
}
#include <hybrid/typecore.h>
#ifndef ____vfc16scanf_unlocked_getc_defined
#define ____vfc16scanf_unlocked_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBDCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 2
__LOCAL_LIBC(vfc16scanf_unlocked_getc) __format_word_t
(__FORMATPRINTER_CC vfc16scanf_unlocked_getc)(void *arg) {
	return (__format_word_t)libd_fgetwc_unlocked((FILE *)arg);
}
#endif /* !__LIBDCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 2 */
__LOCAL_LIBC(vfc16scanf_unlocked_ungetc) ssize_t
(__FORMATPRINTER_CC vfc16scanf_unlocked_ungetc)(void *arg, __format_word_t word) {
	return libd_ungetwc_unlocked((wint16_t)word, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfc16scanf_unlocked_getc_defined */
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vfwscanf_unlocked)(FILE *__restrict stream,
                                                char16_t const *__restrict format,
                                                va_list args) {
#if defined(__LIBDCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == 2
	return libd_format_vwscanf((pformatgetc)(void *)&libd_fgetwc_unlocked,
	                      &__NAMESPACE_LOCAL_SYM vfc16scanf_unlocked_ungetc,
	                      (void *)stream,
	                      format, args);
#else /* __LIBDCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == 2 */
	return libd_format_vwscanf(&__NAMESPACE_LOCAL_SYM vfc16scanf_unlocked_getc,
	                      &__NAMESPACE_LOCAL_SYM vfc16scanf_unlocked_ungetc,
	                      (void *)stream,
	                      format, args);
#endif /* !__LIBDCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 2 */
}
#include <hybrid/typecore.h>
#ifndef ____vfc32scanf_unlocked_getc_defined
#define ____vfc32scanf_unlocked_getc_defined
__NAMESPACE_LOCAL_BEGIN
#if !defined(__LIBKCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 4
__LOCAL_LIBC(vfc32scanf_unlocked_getc) __format_word_t
(__FORMATPRINTER_CC vfc32scanf_unlocked_getc)(void *arg) {
	return (__format_word_t)libc_fgetwc_unlocked((FILE *)arg);
}
#endif /* !__LIBKCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 4 */
__LOCAL_LIBC(vfc32scanf_unlocked_ungetc) ssize_t
(__FORMATPRINTER_CC vfc32scanf_unlocked_ungetc)(void *arg, __format_word_t word) {
	return libc_ungetwc_unlocked((wint32_t)word, (FILE *)arg);
}
__NAMESPACE_LOCAL_END
#endif /* !____vfc32scanf_unlocked_getc_defined */
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vfwscanf_unlocked)(FILE *__restrict stream,
                                                char32_t const *__restrict format,
                                                va_list args) {
#if defined(__LIBKCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == 4
	return libc_format_vwscanf((pformatgetc)(void *)&libc_fgetwc_unlocked,
	                      &__NAMESPACE_LOCAL_SYM vfc32scanf_unlocked_ungetc,
	                      (void *)stream,
	                      format, args);
#else /* __LIBKCALL_IS_FORMATPRINTER_CC && __SIZEOF_FORMAT_WORD_T__ == 4 */
	return libc_format_vwscanf(&__NAMESPACE_LOCAL_SYM vfc32scanf_unlocked_getc,
	                      &__NAMESPACE_LOCAL_SYM vfc32scanf_unlocked_ungetc,
	                      (void *)stream,
	                      format, args);
#endif /* !__LIBKCALL_IS_FORMATPRINTER_CC || __SIZEOF_FORMAT_WORD_T__ != 4 */
}
#include <libc/template/stdstreams.h>
/* >> vwscanf(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBDCALL libd_vwscanf_unlocked)(char16_t const *__restrict format,
                                               va_list args) {
	return libd_vfwscanf_unlocked(stdin, format, args);
}
#include <libc/template/stdstreams.h>
/* >> vwscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(LIBKCALL libc_vwscanf_unlocked)(char32_t const *__restrict format,
                                               va_list args) {
	return libc_vfwscanf_unlocked(stdin, format, args);
}
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_fwscanf_unlocked)(FILE *__restrict stream,
                                                char16_t const *__restrict format,
                                                ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 3) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_fwscanf_unlocked)(FILE *__restrict stream,
                                                char32_t const *__restrict format,
                                                ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBDCALL libd_wscanf_unlocked)(char16_t const *__restrict format,
                                               ...) {
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf_unlocked(format, args);
	va_end(args);
	return result;
}
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_CB_NCX(VLIBKCALL libc_wscanf_unlocked)(char32_t const *__restrict format,
                                               ...) {
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsend)(char16_t const *__restrict str) {
	while (*str)
		++str;
	return (char16_t *)str;
}
#endif /* !LIBC_ARCH_HAVE_C16SEND */
#ifndef LIBC_ARCH_HAVE_C32SEND
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsend)(char32_t const *__restrict str) {
	while (*str)
		++str;
	return (char32_t *)str;
}
#endif /* !LIBC_ARCH_HAVE_C32SEND */
#ifndef LIBC_ARCH_HAVE_C16SNEND
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) NONNULL((1)) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnend)(char32_t const *__restrict str,
                                   size_t maxlen) {
	for (; maxlen && *str; ++str, --maxlen)
		;
	return (char32_t *)str;
}
#endif /* !LIBC_ARCH_HAVE_C32SNEND */
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcsto32_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32_r)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {





	char16_t sign;

	int32_t result;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	num_start = libd_wcslstrip(num_start);

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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */













			char16_t const *new_num_iter;
			char32_t uni;
			new_num_iter = (char16_t const *)num_iter;
			uni = __libc_unicode_readutf16(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else






			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_sadd(result, digit, &result)) {

			/* Check for special case: `strtoi(itos(T.MIN))' */
			if ((__UINT32_TYPE__)result == ((__UINT32_TYPE__)0 - (__UINT32_TYPE__)__INT32_MIN__) &&
			    sign == '-') {
				/* Must ensure that we're at the end of the input string. */
				ch = *num_iter;
				if (!__libc_hex2int(ch, &digit)) {

					/* Unicode decimal support */















					char16_t const *new_num_iter;
					char32_t uni;
					new_num_iter = (char16_t const *)num_iter;
					uni = __libc_unicode_readutf16(&new_num_iter);
					if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
						goto handle_overflow;
					} else






					{
						/* Not a digit valid for `radix' --> allowed */
					}
				} else {
					if (digit < base)
						goto handle_overflow;
				}
				/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */



				result = __INT32_MIN__;
				goto return_not_an_overflow;
			}
handle_overflow:

			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */













						char16_t const *new_num_iter;
						char32_t uni;
						new_num_iter = (char16_t const *)num_iter;
						uni = __libc_unicode_readutf16(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else






						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char16_t *)num_iter;
			}

			if (sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;



		}
	}

	if (sign == '-') {
		if (__hybrid_overflow_sneg_p2n(result, &result)) /* NOLINT */
			goto handle_overflow; /* Overflow... */
	}


	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			nptr_ps = libd_wcslstrip(nptr_ps);
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

return_not_an_overflow:

		if (endptr) {
			*endptr = (char16_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				num_iter = libd_wcslstrip(num_iter);
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
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcsto32_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) int32_t
NOTHROW_NCX(LIBKCALL libc_wcsto32_r)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {





	char32_t sign;

	int32_t result;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	num_start = libc_wcslstrip(num_start);

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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */





















			if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
				++num_iter;
			} else


			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_sadd(result, digit, &result)) {

			/* Check for special case: `strtoi(itos(T.MIN))' */
			if ((__UINT32_TYPE__)result == ((__UINT32_TYPE__)0 - (__UINT32_TYPE__)__INT32_MIN__) &&
			    sign == '-') {
				/* Must ensure that we're at the end of the input string. */
				ch = *num_iter;
				if (!__libc_hex2int(ch, &digit)) {

					/* Unicode decimal support */























					if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
						goto handle_overflow;
					} else


					{
						/* Not a digit valid for `radix' --> allowed */
					}
				} else {
					if (digit < base)
						goto handle_overflow;
				}
				/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */



				result = __INT32_MIN__;
				goto return_not_an_overflow;
			}
handle_overflow:

			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */





















						if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
							++num_iter;
						} else


						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char32_t *)num_iter;
			}

			if (sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;



		}
	}

	if (sign == '-') {
		if (__hybrid_overflow_sneg_p2n(result, &result)) /* NOLINT */
			goto handle_overflow; /* Overflow... */
	}


	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			nptr_ps = libc_wcslstrip(nptr_ps);
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

return_not_an_overflow:

		if (endptr) {
			*endptr = (char32_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				num_iter = libc_wcslstrip(num_iter);
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
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstou32_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32_r)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {







	uint32_t result;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	num_start = libd_wcslstrip(num_start);





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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */













			char16_t const *new_num_iter;
			char32_t uni;
			new_num_iter = (char16_t const *)num_iter;
			uni = __libc_unicode_readutf16(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else






			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_uadd(result, digit, &result)) {





















































			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */













						char16_t const *new_num_iter;
						char32_t uni;
						new_num_iter = (char16_t const *)num_iter;
						uni = __libc_unicode_readutf16(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else






						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char16_t *)num_iter;
			}





			return __UINT32_MAX__;

		}
	}







	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			nptr_ps = libd_wcslstrip(nptr_ps);
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
				num_iter = libd_wcslstrip(num_iter);
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
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstou32_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) uint32_t
NOTHROW_NCX(LIBKCALL libc_wcstou32_r)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {







	uint32_t result;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	num_start = libc_wcslstrip(num_start);





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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */





















			if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
				++num_iter;
			} else


			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_uadd(result, digit, &result)) {





















































			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */





















						if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
							++num_iter;
						} else


						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char32_t *)num_iter;
			}





			return __UINT32_MAX__;

		}
	}







	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			nptr_ps = libc_wcslstrip(nptr_ps);
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
				num_iter = libc_wcslstrip(num_iter);
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int32_t
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int32_t
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint32_t
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint32_t
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
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcsto64_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64_r)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {





	char16_t sign;

	int64_t result;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	num_start = libd_wcslstrip(num_start);

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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */













			char16_t const *new_num_iter;
			char32_t uni;
			new_num_iter = (char16_t const *)num_iter;
			uni = __libc_unicode_readutf16(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else






			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_sadd(result, digit, &result)) {

			/* Check for special case: `strtoi(itos(T.MIN))' */
			if ((__UINT64_TYPE__)result == ((__UINT64_TYPE__)0 - (__UINT64_TYPE__)__INT64_MIN__) &&
			    sign == '-') {
				/* Must ensure that we're at the end of the input string. */
				ch = *num_iter;
				if (!__libc_hex2int(ch, &digit)) {

					/* Unicode decimal support */















					char16_t const *new_num_iter;
					char32_t uni;
					new_num_iter = (char16_t const *)num_iter;
					uni = __libc_unicode_readutf16(&new_num_iter);
					if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
						goto handle_overflow;
					} else






					{
						/* Not a digit valid for `radix' --> allowed */
					}
				} else {
					if (digit < base)
						goto handle_overflow;
				}
				/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */



				result = __INT64_MIN__;
				goto return_not_an_overflow;
			}
handle_overflow:

			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */













						char16_t const *new_num_iter;
						char32_t uni;
						new_num_iter = (char16_t const *)num_iter;
						uni = __libc_unicode_readutf16(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else






						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char16_t *)num_iter;
			}

			if (sign == '-')
				return __INT64_MIN__;
			return __INT64_MAX__;



		}
	}

	if (sign == '-') {
		if (__hybrid_overflow_sneg_p2n(result, &result)) /* NOLINT */
			goto handle_overflow; /* Overflow... */
	}


	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			nptr_ps = libd_wcslstrip(nptr_ps);
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

return_not_an_overflow:

		if (endptr) {
			*endptr = (char16_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				num_iter = libd_wcslstrip(num_iter);
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
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcsto64_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) int64_t
NOTHROW_NCX(LIBKCALL libc_wcsto64_r)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     errno_t *error) {





	char32_t sign;

	int64_t result;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	num_start = libc_wcslstrip(num_start);

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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */





















			if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
				++num_iter;
			} else


			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_smul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_sadd(result, digit, &result)) {

			/* Check for special case: `strtoi(itos(T.MIN))' */
			if ((__UINT64_TYPE__)result == ((__UINT64_TYPE__)0 - (__UINT64_TYPE__)__INT64_MIN__) &&
			    sign == '-') {
				/* Must ensure that we're at the end of the input string. */
				ch = *num_iter;
				if (!__libc_hex2int(ch, &digit)) {

					/* Unicode decimal support */























					if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
						goto handle_overflow;
					} else


					{
						/* Not a digit valid for `radix' --> allowed */
					}
				} else {
					if (digit < base)
						goto handle_overflow;
				}
				/* Not actually an overflow --> result is supposed to be `INTxx_MIN'! */



				result = __INT64_MIN__;
				goto return_not_an_overflow;
			}
handle_overflow:

			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */





















						if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
							++num_iter;
						} else


						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char32_t *)num_iter;
			}

			if (sign == '-')
				return __INT64_MIN__;
			return __INT64_MAX__;



		}
	}

	if (sign == '-') {
		if (__hybrid_overflow_sneg_p2n(result, &result)) /* NOLINT */
			goto handle_overflow; /* Overflow... */
	}


	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			nptr_ps = libc_wcslstrip(nptr_ps);
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

return_not_an_overflow:

		if (endptr) {
			*endptr = (char32_t *)num_iter;
			if (error)
				*error = 0;
		} else if (error) {
			*error = 0;
			/* Check for `EINVAL' */
			if unlikely(*num_iter) {
				num_iter = libc_wcslstrip(num_iter);
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
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstou64_r(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64_r)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {







	uint64_t result;
	char16_t const *num_start = nptr;
	char16_t const *num_iter;
	num_start = libd_wcslstrip(num_start);





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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */













			char16_t const *new_num_iter;
			char32_t uni;
			new_num_iter = (char16_t const *)num_iter;
			uni = __libc_unicode_readutf16(&new_num_iter);
			if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
				num_iter = new_num_iter;
			} else






			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_uadd(result, digit, &result)) {





















































			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */













						char16_t const *new_num_iter;
						char32_t uni;
						new_num_iter = (char16_t const *)num_iter;
						uni = __libc_unicode_readutf16(&new_num_iter);
						if (__libc_unicode_asdigit(uni, (uint8_t)base, &digit)) {
							num_iter = new_num_iter;
						} else






						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char16_t *)num_iter;
			}





			return __UINT64_MAX__;

		}
	}







	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char16_t const *nptr_ps = nptr;
			nptr_ps = libd_wcslstrip(nptr_ps);
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
				num_iter = libd_wcslstrip(num_iter);
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
#include <libc/template/hex.h>
#include <hybrid/limitcore.h>
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcstou64_r(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4) uint64_t
NOTHROW_NCX(LIBKCALL libc_wcstou64_r)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      errno_t *error) {







	uint64_t result;
	char32_t const *num_start = nptr;
	char32_t const *num_iter;
	num_start = libc_wcslstrip(num_start);





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
		if (!__libc_hex2int(ch, &digit)) {

			/* Unicode decimal support */





















			if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
				++num_iter;
			} else


			{
				break;
			}
		} else {
			if (digit >= base)
				break;
			++num_iter;
		}
		if unlikely(__hybrid_overflow_umul(result, (unsigned int)base, &result) ||
		/*       */ __hybrid_overflow_uadd(result, digit, &result)) {





















































			/* Integer overflow. */
			if (error) {

				*error = ERANGE;



			}
			if (endptr) {
				for (;;) {
					ch = *num_iter;
					if (!__libc_hex2int(ch, &digit)) {

						/* Unicode decimal support */





















						if (__libc_unicode_asdigit(ch, (uint8_t)base, &digit)) {
							++num_iter;
						} else


						{
							break;
						}
					} else {
						if (digit >= base)
							break;
						++num_iter;
					}
				}
				*endptr = (char32_t *)num_iter;
			}





			return __UINT64_MAX__;

		}
	}







	if unlikely(num_iter == num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((base == 16 || base == 2) && num_start > nptr) {
			char32_t const *nptr_ps = nptr;
			nptr_ps = libc_wcslstrip(nptr_ps);
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
				num_iter = libc_wcslstrip(num_iter);
				if (*num_iter) {

					*error = EINVAL;



				}
			}
		}
	}
	return result;
}
#include <libc/errno.h>
/* >> wcsto64(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int64_t
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int64_t
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
#include <libc/errno.h>
/* >> wcstou64(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint64_t
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint64_t
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
/* >> wcsto32_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int32_t
NOTHROW_NCX(LIBDCALL libd_wcsto32_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsto32(nptr, endptr, base);
}
/* >> wcsto32_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int32_t
NOTHROW_NCX(LIBKCALL libc_wcsto32_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsto32(nptr, endptr, base);
}
/* >> wcstou32_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint32_t
NOTHROW_NCX(LIBDCALL libd_wcstou32_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstou32(nptr, endptr, base);
}
/* >> wcstou32_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint32_t
NOTHROW_NCX(LIBKCALL libc_wcstou32_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstou32(nptr, endptr, base);
}
/* >> wcsto64_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int64_t
NOTHROW_NCX(LIBDCALL libd_wcsto64_l)(char16_t const *__restrict nptr,
                                     char16_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libd_wcsto64(nptr, endptr, base);
}
/* >> wcsto64_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) int64_t
NOTHROW_NCX(LIBKCALL libc_wcsto64_l)(char32_t const *__restrict nptr,
                                     char32_t **endptr,
                                     __STDC_INT_AS_UINT_T base,
                                     locale_t locale) {
	(void)locale;
	return libc_wcsto64(nptr, endptr, base);
}
/* >> wcstou64_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint64_t
NOTHROW_NCX(LIBDCALL libd_wcstou64_l)(char16_t const *__restrict nptr,
                                      char16_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libd_wcstou64(nptr, endptr, base);
}
/* >> wcstou64_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.convert") ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) uint64_t
NOTHROW_NCX(LIBKCALL libc_wcstou64_l)(char32_t const *__restrict nptr,
                                      char32_t **endptr,
                                      __STDC_INT_AS_UINT_T base,
                                      locale_t locale) {
	(void)locale;
	return libc_wcstou64(nptr, endptr, base);
}
/* >> wcsncoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncoll)(char16_t const *s1,
                                    char16_t const *s2,
                                    size_t maxlen) {
	/* XXX: Implement properly? */
	return libd_wcsncmp(s1, s2, maxlen);
}
/* >> wcsncoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncoll)(char32_t const *s1,
                                    char32_t const *s2,
                                    size_t maxlen) {
	/* XXX: Implement properly? */
	return libc_wcsncmp(s1, s2, maxlen);
}
/* >> wcscasecoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll)(char16_t const *s1,
                                       char16_t const *s2) {
	/* XXX: Implement properly? */
	return libd_wcscasecmp(s1, s2);
}
/* >> wcscasecoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBKCALL libc_wcscasecoll)(char32_t const *s1,
                                       char32_t const *s2) {
	/* XXX: Implement properly? */
	return libc_wcscasecmp(s1, s2);
}
/* >> wcsncasecoll(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll)(char16_t const *s1,
                                        char16_t const *s2,
                                        size_t maxlen) {
	/* XXX: Implement properly? */
	return libd_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcsncasecoll(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecoll)(char32_t const *s1,
                                        char32_t const *s2,
                                        size_t maxlen) {
	/* XXX: Implement properly? */
	return libc_wcsncasecmp(s1, s2, maxlen);
}
/* >> wcsnrev(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnrev)(char16_t *__restrict str,
                                   size_t maxlen) {

	return (char16_t *)libc_memrevw(str, libd_wcsnlen(str, maxlen));





}
/* >> wcsnrev(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnrev)(char32_t *__restrict str,
                                   size_t maxlen) {



	return (char32_t *)libc_memrevl(str, libc_wcsnlen(str, maxlen));



}
/* >> wcsnlwr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnlwr)(char16_t *__restrict str,
                                   size_t maxlen) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower((char16_t)ch);
	return str;
}
/* >> wcsnlwr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnlwr)(char32_t *__restrict str,
                                   size_t maxlen) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower((char32_t)ch);
	return str;
}
/* >> wcsnupr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr)(char16_t *__restrict str,
                                   size_t maxlen) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper((char16_t)ch);
	return str;
}
/* >> wcsnupr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnupr)(char32_t *__restrict str,
                                   size_t maxlen) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper((char32_t)ch);
	return str;
}
#include <hybrid/typecore.h>
/* >> wcscasestr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr)(char16_t const *haystack,
                                      char16_t const *needle) {
	size_t needle_len = libd_wcslen(needle);
	for (; *haystack; ++haystack) {
		if (libd_wmemcasecmp(haystack, needle, needle_len * sizeof(char16_t)) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}
#include <hybrid/typecore.h>
/* >> wcscasestr(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscasestr)(char32_t const *haystack,
                                      char32_t const *needle) {
	size_t needle_len = libc_wcslen(needle);
	for (; *haystack; ++haystack) {
		if (libc_wmemcasecmp(haystack, needle, needle_len * sizeof(char32_t)) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspcpy)(char16_t *__restrict buf,
                                   char16_t const *__restrict src) {
	return (char16_t *)libc_mempcpyw(buf, src, libd_wcslen(src) + 1);
}
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspcpy)(char32_t *__restrict buf,
                                   char32_t const *__restrict src) {
	return (char32_t *)libc_mempcpyl(buf, src, libc_wcslen(src) + 1);
}
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcspncpy)(char16_t *__restrict buf,
                                    char16_t const *__restrict src,
                                    size_t buflen) {
	size_t srclen = libd_wcsnlen(src, buflen);
	buf = (char16_t *)libc_mempcpyw(buf, src, srclen);
	buf = (char16_t *)libc_mempsetw(buf, (char16_t)'\0', buflen - srclen);
	return buf;
}
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcspncpy)(char32_t *__restrict buf,
                                    char32_t const *__restrict src,
                                    size_t buflen) {
	size_t srclen = libc_wcsnlen(src, buflen);
	buf = (char32_t *)libc_mempcpyl(buf, src, srclen);
	buf = (char32_t *)libc_mempsetl(buf, (char32_t)'\0', buflen - srclen);
	return buf;
}
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_INOUT(1) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_LEAF ATTR_INOUT(1) char32_t *
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
#include <hybrid/typecore.h>
/* >> wcsndup(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INS(1, 2) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsndup)(char16_t const *__restrict str,
                                   size_t max_chars) {
	size_t resultsize = libd_wcsnlen(str, max_chars) * sizeof(char16_t);
	char16_t *result = (char16_t *)libc_malloc(resultsize + sizeof(char16_t));
	if likely(result) {
		*(char16_t *)libc_mempcpy(result, str, resultsize) = '\0';
	}
	return result;
}
#include <hybrid/typecore.h>
/* >> wcsndup(3) */
INTERN ATTR_SECTION(".text.crt.wchar.heap.strdup") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INS(1, 2) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnchrnul)(char16_t const *__restrict haystack,
                                      char16_t needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (char16_t)*haystack != (char16_t)needle; ++haystack)
		;
	return (char16_t *)haystack;
}
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnchrnul)(char32_t const *__restrict haystack,
                                      char32_t needle,
                                      size_t maxlen) {
	for (; maxlen-- && *haystack && (char32_t)*haystack != (char32_t)needle; ++haystack)
		;
	return (char32_t *)haystack;
}
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)) char32_t *
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
#include <hybrid/typecore.h>
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBDCALL libd_wcsoff)(char16_t const *__restrict haystack,
                                  char16_t needle) {
	return (size_t)(libd_wcschrnul(haystack, needle) - haystack);
}
#include <hybrid/typecore.h>
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBKCALL libc_wcsoff)(char32_t const *__restrict haystack,
                                  char32_t needle) {
	return (size_t)(libc_wcschrnul(haystack, needle) - haystack);
}
#include <hybrid/typecore.h>
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBDCALL libd_wcsroff)(char16_t const *__restrict haystack,
                                   char16_t needle) {
	return (size_t)(libd_wcsrchrnul(haystack, needle) - haystack);
}
#include <hybrid/typecore.h>
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBKCALL libc_wcsroff)(char32_t const *__restrict haystack,
                                   char32_t needle) {
	return (size_t)(libc_wcsrchrnul(haystack, needle) - haystack);
}
#include <hybrid/typecore.h>
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnoff)(char16_t const *__restrict haystack,
                                   char16_t needle,
                                   size_t maxlen) {
	return (size_t)(libd_wcsnchrnul(haystack, needle, maxlen) - haystack);
}
#include <hybrid/typecore.h>
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnoff)(char32_t const *__restrict haystack,
                                   char32_t needle,
                                   size_t maxlen) {
	return (size_t)(libc_wcsnchrnul(haystack, needle, maxlen) - haystack);
}
#include <hybrid/typecore.h>
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnroff)(char16_t const *__restrict haystack,
                                    char16_t needle,
                                    size_t maxlen) {
	return (size_t)(libd_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}
#include <hybrid/typecore.h>
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnroff)(char32_t const *__restrict haystack,
                                    char32_t needle,
                                    size_t maxlen) {
	return (size_t)(libc_wcsnrchrnul(haystack, needle, maxlen) - haystack);
}
/* >> fuzzy_wcscmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscmp)(char16_t const *s1,
                                        char16_t const *s2) {
	return libc_fuzzy_memcmpw(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}
/* >> fuzzy_wcscmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscmp)(char32_t const *s1,
                                        char32_t const *s2) {
	return libc_fuzzy_memcmpl(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
/* >> fuzzy_wcsncmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncmp)(char16_t const *s1,
                                         size_t s1_maxlen,
                                         char16_t const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmpw(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}
/* >> fuzzy_wcsncmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncmp)(char32_t const *s1,
                                         size_t s1_maxlen,
                                         char32_t const *s2,
                                         size_t s2_maxlen) {
	return libc_fuzzy_memcmpl(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
#include <hybrid/typecore.h>
#include <parts/malloca.h>
/* >> fuzzy_wmemcasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
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
#include <hybrid/typecore.h>
#include <parts/malloca.h>
/* >> fuzzy_wmemcasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp)(char16_t const *s1,
                                            char16_t const *s2) {
	return libd_fuzzy_wmemcasecmp(s1, libd_wcslen(s1), s2, libd_wcslen(s2));
}
/* >> fuzzy_wcscasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp)(char32_t const *s1,
                                            char32_t const *s2) {
	return libc_fuzzy_wmemcasecmp(s1, libc_wcslen(s1), s2, libc_wcslen(s2));
}
/* >> fuzzy_wcsncasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp)(char16_t const *s1,
                                             size_t s1_maxlen,
                                             char16_t const *s2,
                                             size_t s2_maxlen) {
	return libd_fuzzy_wmemcasecmp(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen));
}
/* >> fuzzy_wcsncasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp)(char32_t const *s1,
                                             size_t s1_maxlen,
                                             char32_t const *s2,
                                             size_t s2_maxlen) {
	return libc_fuzzy_wmemcasecmp(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen));
}
/* >> wildwcscmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
				c1 = *++s1;
				if (c1 < '0' || c1 > '9')
					break;
				vala *= 10;
				vala += c1 - '0';
			}
			for (;;) {
				c2 = *++s2;
				if (c2 < '0' || c2 > '9')
					break;
				valb *= 10;
				valb += c2 - '0';
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
INTERN ATTR_SECTION(".text.crt.wchar.string.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
				c1 = *++s1;
				if (c1 < '0' || c1 > '9')
					break;
				vala *= 10;
				vala += c1 - '0';
			}
			for (;;) {
				c2 = *++s2;
				if (c2 < '0' || c2 > '9')
					break;
				valb *= 10;
				valb += c2 - '0';
			}

			/* Return difference between digits. */
			return (int)vala - (int)valb;
		}
		++s1;
		++s2;
	} while (c1 != '\0');
	return 0;
}
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcslstrip(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslstrip)(char16_t const *str) {
	/* NOTE: assert(!isspace('\0'));
	 * -> So we don't need special handling to stop on NUL! */



















	/* NOTE: No  need for special  handling for UTF-16 surrogates:
	 *       there are no unicode whitespace characters that would
	 *       need to be  encoded using surrogates  (so any  UTF-16
	 *       character that  might be  a space  is always  encoded
	 *       using a single word) */

	while (libd_iswspace((char16_t)*str))
		++str;

	return (char16_t *)str;
}
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcslstrip(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcslstrip)(char32_t const *str) {
	/* NOTE: assert(!isspace('\0'));
	 * -> So we don't need special handling to stop on NUL! */

























	while (libc_iswspace((char32_t)*str))
		++str;

	return (char32_t *)str;
}
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcsrstrip(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrstrip)(char16_t *str) {
	char16_t *endp = libd_wcsend(str);




















	/* NOTE: No  need for special  handling for UTF-16 surrogates:
	 *       there are no unicode whitespace characters that would
	 *       need to be  encoded using surrogates  (so any  UTF-16
	 *       character that  might be  a space  is always  encoded
	 *       using a single word) */

	while (endp > str && libd_iswspace((char16_t)endp[-1]))
		--endp;

	*endp = '\0'; /* Delete trailing space. */
	return str;
}
#include <libc/unicode.h>
#include <hybrid/typecore.h>
/* >> wcsrstrip(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrstrip)(char32_t *str) {
	char32_t *endp = libc_wcsend(str);


























	while (endp > str && libc_iswspace((char32_t)endp[-1]))
		--endp;

	*endp = '\0'; /* Delete trailing space. */
	return str;
}
/* >> wcsstrip(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsstrip)(char16_t *str) {
	str = libd_wcslstrip(str);
	str = libd_wcsrstrip(str);
	return str;
}
/* >> wcsstrip(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsstrip)(char32_t *str) {
	str = libc_wcslstrip(str);
	str = libc_wcsrstrip(str);
	return str;
}
#include <hybrid/typecore.h>
/* >> wmemcasecmp(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wmemcasecmp)(void const *s1,
                                       void const *s2,
                                       size_t num_chars) {
	char16_t const *p1 = (char16_t const *)s1;
	char16_t const *p2 = (char16_t const *)s2;
	char16_t v1, v2;
	v1 = 0;
	v2 = 0;
	while (num_chars--) {
		v1 = *p1++;
		v2 = *p2++;
		if (v1 != v2) {
			v1 = (char16_t)libd_towlower(v1);
			v2 = (char16_t)libd_towlower(v2);
			if (v1 != v2)
				break;
		}
	}
#if __SIZEOF_INT__ > 2
	return (int)v1 - (int)v2;
#else /* __SIZEOF_INT__ > 2 */
	if (v1 < v2)
		return -1;
	if (v1 > v2)
		return 1;
	return 0;
#endif /* __SIZEOF_INT__ <= 2 */
}
#include <hybrid/typecore.h>
/* >> wmemcasecmp(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wmemcasecmp)(void const *s1,
                                       void const *s2,
                                       size_t num_chars) {
	char32_t const *p1 = (char32_t const *)s1;
	char32_t const *p2 = (char32_t const *)s2;
	char32_t v1, v2;
	v1 = 0;
	v2 = 0;
	while (num_chars--) {
		v1 = *p1++;
		v2 = *p2++;
		if (v1 != v2) {
			v1 = (char32_t)libc_towlower(v1);
			v2 = (char32_t)libc_towlower(v2);
			if (v1 != v2)
				break;
		}
	}
#if __SIZEOF_INT__ > 4
	return (int)v1 - (int)v2;
#else /* __SIZEOF_INT__ > 4 */
	if (v1 < v2)
		return -1;
	if (v1 > v2)
		return 1;
	return 0;
#endif /* __SIZEOF_INT__ <= 4 */
}
/* >> wmemcasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wmemcasecmp_l)(void const *s1,
                                         void const *s2,
                                         size_t num_chars,
                                         locale_t locale) {
	(void)locale;
	return libd_wmemcasecmp(s1, s2, num_chars);
}
/* >> wmemcasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wmemcasecmp_l)(void const *s1,
                                         void const *s2,
                                         size_t num_chars,
                                         locale_t locale) {
	(void)locale;
	return libc_wmemcasecmp(s1, s2, num_chars);
}
/* >> wcsncoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncoll_l)(char16_t const *s1,
                                      char16_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libd_wcsncoll(s1, s2, maxlen);
}
/* >> wcsncoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncoll_l)(char32_t const *s1,
                                      char32_t const *s2,
                                      size_t maxlen,
                                      locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_wcsncoll(s1, s2, maxlen);
}
/* >> wcscasecoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBDCALL libd_wcscasecoll_l)(char16_t const *s1,
                                         char16_t const *s2,
                                         locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libd_wcscasecoll(s1, s2);
}
/* >> wcscasecoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBKCALL libc_wcscasecoll_l)(char32_t const *s1,
                                         char32_t const *s2,
                                         locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_wcscasecoll(s1, s2);
}
/* >> wcsncasecoll_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_wcsncasecoll_l)(char16_t const *s1,
                                          char16_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libd_wcsncasecoll(s1, s2, maxlen);
}
/* >> wcsncasecoll_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)) int
NOTHROW_NCX(LIBKCALL libc_wcsncasecoll_l)(char32_t const *s1,
                                          char32_t const *s2,
                                          size_t maxlen,
                                          locale_t locale) {
	/* XXX: Implement properly? */
	(void)locale;
	return libc_wcsncasecoll(s1, s2, maxlen);
}
/* >> wcslwr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr_l)(char16_t *__restrict str,
                                    locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower_l((char16_t)ch, locale);
	return str;
}
/* >> wcslwr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcslwr_l)(char32_t *__restrict str,
                                    locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l((char32_t)ch, locale);
	return str;
}
/* >> wcsupr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr_l)(char16_t *__restrict str,
                                    locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper_l((char16_t)ch, locale);
	return str;
}
/* >> wcsupr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsupr_l)(char32_t *__restrict str,
                                    locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l((char32_t)ch, locale);
	return str;
}
/* >> wcsnlwr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnlwr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower_l((char16_t)ch, locale);
	return str;
}
/* >> wcsnlwr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnlwr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l((char32_t)ch, locale);
	return str;
}
/* >> wcsnupr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnupr_l)(char16_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char16_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper_l((char16_t)ch, locale);
	return str;
}
/* >> wcsnupr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnupr_l)(char32_t *__restrict str,
                                     size_t maxlen,
                                     locale_t locale) {
	char32_t *iter, ch;
	for (iter = str; maxlen-- && (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l((char32_t)ch, locale);
	return str;
}
#include <hybrid/typecore.h>
/* >> wcscasestr_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcscasestr_l)(char16_t const *haystack,
                                        char16_t const *needle,
                                        locale_t locale) {
	size_t needle_len = libd_wcslen(needle);
	for (; *haystack; ++haystack) {
		if (libd_wmemcasecmp_l(haystack, needle, needle_len * sizeof(char16_t), locale) == 0)
			return (char16_t *)haystack;
	}
	return NULL;
}
#include <hybrid/typecore.h>
/* >> wcscasestr_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcscasestr_l)(char32_t const *haystack,
                                        char32_t const *needle,
                                        locale_t locale) {
	size_t needle_len = libc_wcslen(needle);
	for (; *haystack; ++haystack) {
		if (libc_wmemcasecmp_l(haystack, needle, needle_len * sizeof(char32_t), locale) == 0)
			return (char32_t *)haystack;
	}
	return NULL;
}
#include <hybrid/typecore.h>
#include <parts/malloca.h>
/* >> fuzzy_wmemcasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
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
#include <hybrid/typecore.h>
#include <parts/malloca.h>
/* >> fuzzy_wmemcasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcscasecmp_l)(char16_t const *s1,
                                              char16_t const *s2,
                                              locale_t locale) {
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcslen(s1), s2, libd_wcslen(s2), locale);
}
/* >> fuzzy_wcscasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcscasecmp_l)(char32_t const *s1,
                                              char32_t const *s2,
                                              locale_t locale) {
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcslen(s1), s2, libc_wcslen(s2), locale);
}
/* >> fuzzy_wcsncasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBDCALL libd_fuzzy_wcsncasecmp_l)(char16_t const *s1,
                                               size_t s1_maxlen,
                                               char16_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libd_fuzzy_wmemcasecmp_l(s1, libd_wcsnlen(s1, s1_maxlen), s2, libd_wcsnlen(s2, s2_maxlen), locale);
}
/* >> fuzzy_wcsncasecmp_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)) size_t
NOTHROW_NCX(LIBKCALL libc_fuzzy_wcsncasecmp_l)(char32_t const *s1,
                                               size_t s1_maxlen,
                                               char32_t const *s2,
                                               size_t s2_maxlen,
                                               locale_t locale) {
	return libc_fuzzy_wmemcasecmp_l(s1, libc_wcsnlen(s1, s1_maxlen), s2, libc_wcsnlen(s2, s2_maxlen), locale);
}
/* >> wildwcscasecmp_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
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
#include <hybrid/typecore.h>
/* >> wcslcat(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUTS(1, 3) NONNULL((1)) size_t
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
#include <hybrid/typecore.h>
/* >> wcslcat(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_IN(2) ATTR_INOUTS(1, 3) NONNULL((1)) size_t
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
#include <hybrid/typecore.h>
/* >> wcslcpy(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUTS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBDCALL libd_wcslcpy)(char16_t *__restrict dst,
                                   char16_t const *__restrict src,
                                   size_t bufsize) {
	size_t result = libd_wcslen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(dst, src, copy_size * sizeof(char16_t));
	dst[copy_size] = '\0';
	return result;
}
#include <hybrid/typecore.h>
/* >> wcslcpy(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") ATTR_LEAF ATTR_IN(2) ATTR_OUTS(1, 3) NONNULL((1)) size_t
NOTHROW_NCX(LIBKCALL libc_wcslcpy)(char32_t *__restrict dst,
                                   char32_t const *__restrict src,
                                   size_t bufsize) {
	size_t result = libc_wcslen(src);
	size_t copy_size = result < bufsize ? result : bufsize - 1;
	libc_memcpy(dst, src, copy_size * sizeof(char32_t));
	dst[copy_size] = '\0';
	return result;
}
/* >> wcsnset(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_INOUTS(1, 3) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsnset)(char16_t *__restrict str,
                                   char16_t ch,
                                   size_t maxlen) {
	char16_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}
/* >> wcsnset(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_INOUTS(1, 3) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsnset)(char32_t *__restrict str,
                                   char32_t ch,
                                   size_t maxlen) {
	char32_t *iter;
	for (iter = str; maxlen-- && *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
/* >> wcsrev(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsrev)(char16_t *__restrict str) {

	return (char16_t *)libc_memrevw(str, libd_wcslen(str));





}
/* >> wcsrev(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_RETNONNULL ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsrev)(char32_t *__restrict str) {



	return (char32_t *)libc_memrevl(str, libc_wcslen(str));



}
/* >> wcsset(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsset)(char16_t *__restrict str,
                                  int ch) {
	char16_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char16_t)ch;
	return str;
}
/* >> wcsset(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_LEAF ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsset)(char32_t *__restrict str,
                                  int ch) {
	char32_t *iter;
	for (iter = str; *iter; ++iter)
		*iter = (char32_t)ch;
	return str;
}
/* >> wcslwr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcslwr)(char16_t *__restrict str) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower((char16_t)ch);
	return str;
}
/* >> wcslwr(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcslwr)(char32_t *__restrict str) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower((char32_t)ch);
	return str;
}
/* >> wcsupr(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsupr)(char16_t *__restrict str) {
	char16_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper((char16_t)ch);
	return str;
}
/* >> wcsupr(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_wcsupr)(char32_t *__restrict str) {
	char32_t *iter, ch;
	for (iter = str; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper((char32_t)ch);
	return str;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$btowc,libd_btowc,ATTR_CONST WUNUSED,wint16_t,NOTHROW,LIBDCALL,(int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(btowc,libc_btowc,ATTR_CONST WUNUSED,wint32_t,NOTHROW,LIBKCALL,(int ch),(ch));
DEFINE_PUBLIC_ALIAS_P(DOS$wctob,libd_wctob,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t ch),(ch));
DEFINE_PUBLIC_ALIAS_P(wctob,libc_wctob,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t ch),(ch));
DEFINE_PUBLIC_ALIAS_P(DOS$__mbrtowc,libd_mbrtowc,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pwc,str,maxlen,mbs));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(mbrtoc16,libd_mbrtowc,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pwc,str,maxlen,mbs));
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(DOS$mbrtoc16,libd_mbrtowc,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pwc,str,maxlen,mbs));
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(DOS$mbrtowc,libd_mbrtowc,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pwc,str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(__mbrtowc,libc_mbrtowc,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pwc,str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(mbrtoc32,libc_mbrtowc,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pwc,str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(mbrtowc,libc_mbrtowc,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *pwc, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pwc,str,maxlen,mbs));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(c16rtomb,libd_wcrtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *__restrict str, char16_t wc, mbstate_t *mbs),(str,wc,mbs));
#endif /* __LIBCCALL_IS_LIBDCALL */
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(DOS$c16rtomb,libd_wcrtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *__restrict str, char16_t wc, mbstate_t *mbs),(str,wc,mbs));
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(DOS$__wcrtomb,libd_wcrtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *__restrict str, char16_t wc, mbstate_t *mbs),(str,wc,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$wcrtomb,libd_wcrtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *__restrict str, char16_t wc, mbstate_t *mbs),(str,wc,mbs));
DEFINE_PUBLIC_ALIAS_P(c32rtomb,libc_wcrtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char *__restrict str, char32_t wc, mbstate_t *mbs),(str,wc,mbs));
DEFINE_PUBLIC_ALIAS_P(__wcrtomb,libc_wcrtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char *__restrict str, char32_t wc, mbstate_t *mbs),(str,wc,mbs));
DEFINE_PUBLIC_ALIAS_P(wcrtomb,libc_wcrtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char *__restrict str, char32_t wc, mbstate_t *mbs),(str,wc,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$__mbrlen,libd_mbrlen,WUNUSED ATTR_INOUT_OPT(3) ATTR_IN_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char const *__restrict str, size_t maxlen, mbstate_t *mbs),(str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$mbrlen,libd_mbrlen,WUNUSED ATTR_INOUT_OPT(3) ATTR_IN_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char const *__restrict str, size_t maxlen, mbstate_t *mbs),(str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(__mbrlen,libc_mbrlen,WUNUSED ATTR_INOUT_OPT(3) ATTR_IN_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char const *__restrict str, size_t maxlen, mbstate_t *mbs),(str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(mbrlen,libc_mbrlen,WUNUSED ATTR_INOUT_OPT(3) ATTR_IN_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char const *__restrict str, size_t maxlen, mbstate_t *mbs),(str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$__mbsrtowcs,libd_mbsrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$mbsrtowcs,libd_mbsrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(__mbsrtowcs,libc_mbsrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(mbsrtowcs,libc_mbsrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcsrtombs,libd_wcsrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *dst, char16_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsrtombs,libd_wcsrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *dst, char16_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(__wcsrtombs,libc_wcsrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char *dst, char32_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(wcsrtombs,libc_wcsrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(4) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char *dst, char32_t const **__restrict psrc, size_t dstlen, mbstate_t *mbs),(dst,psrc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstol,libd_wcstol,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax,libd_wcstol,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstol,libc_wcstol,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoimax,libc_wcstol,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoul,libd_wcstoul,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax,libd_wcstoul,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstoul,libc_wcstoul,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoumax,libc_wcstoul,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(mbsinit,libc_mbsinit,ATTR_PURE WUNUSED ATTR_IN_OPT(1),int,NOTHROW_NCX,LIBCCALL,(mbstate_t const *mbs),(mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscpy,libd_wcscpy,ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src),(buf,src));
DEFINE_PUBLIC_ALIAS_P(wcscpy,libc_wcscpy,ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src),(buf,src));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscat,libd_wcscat,ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src),(buf,src));
DEFINE_PUBLIC_ALIAS_P(wcscat,libc_wcscat,ATTR_RETNONNULL ATTR_IN(2) ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src),(buf,src));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncat,libd_wcsncat,ATTR_RETNONNULL ATTR_INOUTS(1, 3) ATTR_INS(2, 3),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(wcsncat,libc_wcsncat,ATTR_RETNONNULL ATTR_INOUTS(1, 3) ATTR_INS(2, 3),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncpy,libd_wcsncpy,ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(wcsncpy,libc_wcsncpy,ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscmp,libd_wcscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(wcscmp,libc_wcscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncmp,libd_wcsncmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsncmp,libc_wcsncmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscoll,libd_wcscoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(wcscoll,libc_wcscoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsxfrm,libd_wcsxfrm,ATTR_INS(2, 3) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *dst, char16_t const *__restrict src, size_t buflen),(dst,src,buflen));
DEFINE_PUBLIC_ALIAS_P(wcsxfrm,libc_wcsxfrm,ATTR_INS(2, 3) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *dst, char32_t const *__restrict src, size_t buflen),(dst,src,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$_fgetwchar,libd_getwchar,,wint16_t,NOTHROW_CB_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$getwchar,libd_getwchar,,wint16_t,NOTHROW_CB_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getwchar,libc_getwchar,,wint32_t,NOTHROW_CB_NCX,LIBKCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$_fputwchar,libd_putwchar,,wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$putwchar,libd_putwchar,,wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(putwchar,libc_putwchar,,wint32_t,NOTHROW_CB_NCX,LIBKCALL,(char32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$fgetws,libd_fgetws,WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2),char16_t *,NOTHROW_CB_NCX,LIBDCALL,(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(fgetws,libc_fgetws,WUNUSED ATTR_INOUT(3) ATTR_OUTS(1, 2),char32_t *,NOTHROW_CB_NCX,LIBKCALL,(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fputws,libd_fputws,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict str, FILE *__restrict stream),(str,stream));
DEFINE_PUBLIC_ALIAS_P(fputws,libc_fputws,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(char32_t const *__restrict str, FILE *__restrict stream),(str,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsftime,libd_wcsftime,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C16FTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, struct tm const *__restrict tp),(buf,buflen,format,tp));
DEFINE_PUBLIC_ALIAS_P(wcsftime,libc_wcsftime,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C32FTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, struct tm const *__restrict tp),(buf,buflen,format,tp));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstok_s,libd_wcstok,ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *str, char16_t const *__restrict delim, char16_t **__restrict save_ptr),(str,delim,save_ptr));
DEFINE_PUBLIC_ALIAS_P(wcstok,libc_wcstok,ATTR_IN(2) ATTR_INOUT(3) ATTR_INOUT_OPT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *str, char32_t const *__restrict delim, char32_t **__restrict save_ptr),(str,delim,save_ptr));
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SLEN)
DEFINE_PUBLIC_ALIAS_P(DOS$wcslen,libd_wcslen,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str),(str));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SLEN)
DEFINE_PUBLIC_ALIAS_P(wcslen,libc_wcslen,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict str),(str));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SLEN */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$wcsspn,libd_wcsspn,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t const *accept),(haystack,accept));
DEFINE_PUBLIC_ALIAS_P(wcsspn,libc_wcsspn,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t const *accept),(haystack,accept));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscspn,libd_wcscspn,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t const *reject),(haystack,reject));
DEFINE_PUBLIC_ALIAS_P(wcscspn,libc_wcscspn,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t const *reject),(haystack,reject));
DEFINE_PUBLIC_ALIAS_P(DOS$wcschr,libd_wcschr,ATTR_PURE WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcschr,libc_wcschr,ATTR_PURE WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsrchr,libd_wcsrchr,ATTR_PURE WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcsrchr,libc_wcsrchr,ATTR_PURE WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$wcspbrk,libd_wcspbrk,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t const *accept),(haystack,accept));
DEFINE_PUBLIC_ALIAS_P(wcspbrk,libc_wcspbrk,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t const *accept),(haystack,accept));
DEFINE_PUBLIC_ALIAS_P(DOS$wcswcs,libd_wcsstr,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t const *needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsstr,libd_wcsstr,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t const *needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcswcs,libc_wcsstr,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t const *needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcsstr,libc_wcsstr,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t const *needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(fwide,libc_fwide,ATTR_INOUT(1),int,NOTHROW_NCX,LIBCCALL,(FILE *fp, int mode),(fp,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$_fwprintf_p,libd_fwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$fwprintf,libd_fwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(_fwprintf_p,libc_fwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(fwprintf,libc_fwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$_vfwprintf_p,libd_vfwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$vfwprintf,libd_vfwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(_vfwprintf_p,libc_vfwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vfwprintf,libc_vfwprintf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$_wprintf_p,libd_wprintf,ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char16_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$wprintf,libd_wprintf,ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char16_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(_wprintf_p,libc_wprintf,ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(char32_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(wprintf,libc_wprintf,ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(char32_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$_vwprintf_p,libd_vwprintf,ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$vwprintf,libd_vwprintf,ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(_vwprintf_p,libc_vwprintf,ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(char32_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(vwprintf,libc_vwprintf,ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(char32_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$fwscanf,libd_fwscanf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(fwscanf,libc_fwscanf,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$wscanf,libd_wscanf,ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char16_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(wscanf,libc_wscanf,ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(char32_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$swscanf,libd_swscanf,ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char16_t const *__restrict src, char16_t const *__restrict format, ...),(src,format,));
DEFINE_PUBLIC_ALIAS_P(swscanf,libc_swscanf,ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBKCALL,(char32_t const *__restrict src, char32_t const *__restrict format, ...),(src,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$_vswprintf_p,libd_vswprintf,ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, va_list args),(buf,buflen,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$vswprintf,libd_vswprintf,ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, va_list args),(buf,buflen,format,args));
DEFINE_PUBLIC_ALIAS_P(_vswprintf_p,libc_vswprintf,ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, va_list args),(buf,buflen,format,args));
DEFINE_PUBLIC_ALIAS_P(vswprintf,libc_vswprintf,ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 0) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, va_list args),(buf,buflen,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$_swprintf_p,libd_swprintf,ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, ...),(buf,buflen,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$swprintf,libd_swprintf,ATTR_IN(3) ATTR_LIBC_C16PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBDCALL,(char16_t *__restrict buf, size_t buflen, char16_t const *__restrict format, ...),(buf,buflen,format,));
DEFINE_PUBLIC_ALIAS_P(_swprintf_p,libc_swprintf,ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBKCALL,(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, ...),(buf,buflen,format,));
DEFINE_PUBLIC_ALIAS_P(swprintf,libc_swprintf,ATTR_IN(3) ATTR_LIBC_C32PRINTF(3, 4) ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,VLIBKCALL,(char32_t *__restrict buf, size_t buflen, char32_t const *__restrict format, ...),(buf,buflen,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstod,libd_wcstod,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(wcstod,libc_wcstod,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstof,libd_wcstof,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(wcstof,libc_wcstof,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstold,libd_wcstold,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(wcstold,libc_wcstold,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr),(nptr,endptr));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoll,libd_wcstoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoq,libd_wcstoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax,libd_wcstoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstoll,libc_wcstoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(wcstoq,libc_wcstoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoimax,libc_wcstoll,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoull,libd_wcstoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstouq,libd_wcstoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax,libd_wcstoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstoull,libc_wcstoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(wcstouq,libc_wcstoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoumax,libc_wcstoull,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(DOS$vfwscanf,libd_vfwscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vfwscanf,libc_vfwscanf,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$vwscanf,libd_vwscanf,WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(vwscanf,libc_vwscanf,WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(char32_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$vswscanf,libd_vswscanf,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C16SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict input, char16_t const *__restrict format, va_list args),(input,format,args));
DEFINE_PUBLIC_ALIAS_P(vswscanf,libc_vswscanf,WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_LIBC_C32SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict input, char32_t const *__restrict format, va_list args),(input,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsicmp,libd_wcscasecmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscasecmp,libd_wcscasecmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(wcscasecmp,libc_wcscasecmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsnicmp,libd_wcsncasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncasecmp,libd_wcsncasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsncasecmp,libc_wcsncasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsicmp_l,libd_wcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcscasecmp_l,libd_wcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscasecmp_l,libd_wcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(__wcscasecmp_l,libc_wcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(wcscasecmp_l,libc_wcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsnicmp_l,libd_wcsncasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcsncasecmp_l,libd_wcsncasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncasecmp_l,libd_wcsncasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(__wcsncasecmp_l,libc_wcsncasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(wcsncasecmp_l,libc_wcsncasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcscoll_l,libd_wcscoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcscoll_l,libd_wcscoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscoll_l,libd_wcscoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(__wcscoll_l,libc_wcscoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(wcscoll_l,libc_wcscoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsxfrm_l,libd_wcsxfrm_l,ATTR_INS(2, 3) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *dst, char16_t const *__restrict src, size_t buflen, locale_t locale),(dst,src,buflen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcsxfrm_l,libd_wcsxfrm_l,ATTR_INS(2, 3) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *dst, char16_t const *__restrict src, size_t buflen, locale_t locale),(dst,src,buflen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsxfrm_l,libd_wcsxfrm_l,ATTR_INS(2, 3) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *dst, char16_t const *__restrict src, size_t buflen, locale_t locale),(dst,src,buflen,locale));
DEFINE_PUBLIC_ALIAS_P(__wcsxfrm_l,libc_wcsxfrm_l,ATTR_INS(2, 3) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *dst, char32_t const *__restrict src, size_t buflen, locale_t locale),(dst,src,buflen,locale));
DEFINE_PUBLIC_ALIAS_P(wcsxfrm_l,libc_wcsxfrm_l,ATTR_INS(2, 3) ATTR_OUTS(1, 3),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *dst, char32_t const *__restrict src, size_t buflen, locale_t locale),(dst,src,buflen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcpcpy,libd_wcpcpy,ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char16_t const *__restrict src),(dst,src));
DEFINE_PUBLIC_ALIAS_P(DOS$wcpcpy,libd_wcpcpy,ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char16_t const *__restrict src),(dst,src));
DEFINE_PUBLIC_ALIAS_P(__wcpcpy,libc_wcpcpy,ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char32_t const *__restrict src),(dst,src));
DEFINE_PUBLIC_ALIAS_P(wcpcpy,libc_wcpcpy,ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char32_t const *__restrict src),(dst,src));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcpncpy,libd_wcpncpy,ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcpncpy,libd_wcpncpy,ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(__wcpncpy,libc_wcpncpy,ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(wcpncpy,libc_wcpncpy,ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$__mbsnrtowcs,libd_mbsnrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char const **__restrict psrc, size_t nmc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nmc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$mbsnrtowcs,libd_mbsnrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char const **__restrict psrc, size_t nmc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nmc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(__mbsnrtowcs,libc_mbsnrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char const **__restrict psrc, size_t nmc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nmc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(mbsnrtowcs,libc_mbsnrtowcs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char const **__restrict psrc, size_t nmc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nmc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcsnrtombs,libd_wcsnrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *dst, char16_t const **__restrict psrc, size_t nwc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nwc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnrtombs,libd_wcsnrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBDCALL,(char *dst, char16_t const **__restrict psrc, size_t nwc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nwc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(__wcsnrtombs,libc_wcsnrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char *dst, char32_t const **__restrict psrc, size_t nwc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nwc,dstlen,mbs));
DEFINE_PUBLIC_ALIAS_P(wcsnrtombs,libc_wcsnrtombs,ATTR_INOUT(2) ATTR_INOUT_OPT(5) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBKCALL,(char *dst, char32_t const **__restrict psrc, size_t nwc, size_t dstlen, mbstate_t *mbs),(dst,psrc,nwc,dstlen,mbs));
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SNLEN)
DEFINE_PUBLIC_ALIAS_P(DOS$__wcsncnt,libd_wcsnlen,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnlen,libd_wcsnlen,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str, size_t maxlen),(str,maxlen));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SNLEN */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SNLEN)
DEFINE_PUBLIC_ALIAS_P(wcsnlen,libc_wcsnlen,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict str, size_t maxlen),(str,maxlen));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SNLEN */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsdup,libd_wcsdup,ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict string),(string));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsdup,libd_wcsdup,ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict string),(string));
DEFINE_PUBLIC_ALIAS_P(wcsdup,libc_wcsdup,ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict string),(string));
DEFINE_PUBLIC_ALIAS_P(DOS$wcwidth,libd_wcwidth,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(char16_t ch),(ch));
DEFINE_PUBLIC_ALIAS_P(wcwidth,libc_wcwidth,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(char32_t ch),(ch));
DEFINE_PUBLIC_ALIAS_P(DOS$wcswidth,libd_wcswidth,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),__STDC_INT32_AS_SSIZE_T,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str, size_t num_chars),(str,num_chars));
DEFINE_PUBLIC_ALIAS_P(wcswidth,libc_wcswidth,ATTR_PURE WUNUSED ATTR_INS(1, 2) NONNULL((1)),__STDC_INT32_AS_SSIZE_T,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict str, size_t num_chars),(str,num_chars));
DEFINE_PUBLIC_ALIAS_P(DOS$wcschrnul,libd_wcschrnul,ATTR_PURE WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcschrnul,libc_wcschrnul,ATTR_PURE WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstol_l,libd_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcstol_l,libd_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax_l,libd_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoimax_l,libd_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstol_l,libd_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(__wcstol_l,libc_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoimax_l,libc_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstol_l,libc_wcstol_l,ATTR_IN(1) ATTR_OUT_OPT(2),long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoul_l,libd_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcstoul_l,libd_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax_l,libd_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoumax_l,libd_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoul_l,libd_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(__wcstoul_l,libc_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoumax_l,libc_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstoul_l,libc_wcstoul_l,ATTR_IN(1) ATTR_OUT_OPT(2),unsigned long,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoll_l,libd_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcstoll_l,libd_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax_l,libd_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoimax_l,libd_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoll_l,libd_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(__wcstoll_l,libc_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoimax_l,libc_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstoll_l,libc_wcstoll_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoull_l,libd_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcstoull_l,libd_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax_l,libd_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoumax_l,libd_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoull_l,libd_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(__wcstoull_l,libc_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
DEFINE_PUBLIC_ALIAS_P(wcstoumax_l,libc_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 && __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__ */
DEFINE_PUBLIC_ALIAS_P(wcstoull_l,libc_wcstoull_l,ATTR_IN(1) ATTR_OUT_OPT(2),__ULONGLONG,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstof_l,libd_wcstof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcstof_l,libd_wcstof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstof_l,libd_wcstof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(__wcstof_l,libc_wcstof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(wcstof_l,libc_wcstof_l,ATTR_IN(1) ATTR_OUT_OPT(2),float,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstod_l,libd_wcstod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcstod_l,libd_wcstod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstod_l,libd_wcstod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(__wcstod_l,libc_wcstod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(wcstod_l,libc_wcstod_l,ATTR_IN(1) ATTR_OUT_OPT(2),double,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstold_l,libd_wcstold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcstold_l,libd_wcstold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstold_l,libd_wcstold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(__wcstold_l,libc_wcstold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(wcstold_l,libc_wcstold_l,ATTR_IN(1) ATTR_OUT_OPT(2),__LONGDOUBLE,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, locale_t locale),(nptr,endptr,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$getwchar_unlocked,libd_getwchar_unlocked,,wint16_t,NOTHROW_CB_NCX,LIBDCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getwchar_unlocked,libc_getwchar_unlocked,,wint32_t,NOTHROW_CB_NCX,LIBKCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(DOS$putwchar_unlocked,libd_putwchar_unlocked,,wint16_t,NOTHROW_CB_NCX,LIBDCALL,(char16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(putwchar_unlocked,libc_putwchar_unlocked,,wint32_t,NOTHROW_CB_NCX,LIBKCALL,(char32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$_fgetws_nolock,libd_fgetws_unlocked,ATTR_INOUT(3) ATTR_OUTS(1, 2),char16_t *,NOTHROW_CB_NCX,LIBDCALL,(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fgetws_unlocked,libd_fgetws_unlocked,ATTR_INOUT(3) ATTR_OUTS(1, 2),char16_t *,NOTHROW_CB_NCX,LIBDCALL,(char16_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(fgetws_unlocked,libc_fgetws_unlocked,ATTR_INOUT(3) ATTR_OUTS(1, 2),char32_t *,NOTHROW_CB_NCX,LIBKCALL,(char32_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, FILE *__restrict stream),(buf,bufsize,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$_fputws_nolock,libd_fputws_unlocked,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict str, FILE *__restrict stream),(str,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$fputws_unlocked,libd_fputws_unlocked,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict str, FILE *__restrict stream),(str,stream));
DEFINE_PUBLIC_ALIAS_P(fputws_unlocked,libc_fputws_unlocked,ATTR_IN(1) ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(char32_t const *__restrict str, FILE *__restrict stream),(str,stream));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsftime_l,libd_wcsftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C16FTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, size_t maxsize, char16_t const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,maxsize,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__wcsftime_l,libd_wcsftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C16FTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, size_t maxsize, char16_t const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,maxsize,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsftime_l,libd_wcsftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C16FTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, size_t maxsize, char16_t const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,maxsize,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(__wcsftime_l,libc_wcsftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C32FTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, size_t maxsize, char32_t const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,maxsize,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(wcsftime_l,libc_wcsftime_l,ATTR_IN(3) ATTR_IN(4) ATTR_LIBC_C32FTIME(3, 0) ATTR_OUTS(1, 2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, size_t maxsize, char32_t const *__restrict format, struct tm const *__restrict tp, locale_t locale),(buf,maxsize,format,tp,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$fopen_wprinter,libd_fopen_wprinter,WUNUSED NONNULL((1)),FILE *,NOTHROW_NCX,LIBDCALL,(__pc16formatprinter printer, void *arg),(printer,arg));
DEFINE_PUBLIC_ALIAS_P(fopen_wprinter,libc_fopen_wprinter,WUNUSED NONNULL((1)),FILE *,NOTHROW_NCX,LIBKCALL,(__pc32formatprinter printer, void *arg),(printer,arg));
DEFINE_PUBLIC_ALIAS_P(DOS$vfwprintf_unlocked,libd_vfwprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vfwprintf_unlocked,libc_vfwprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$fwprintf_unlocked,libd_fwprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(fwprintf_unlocked,libc_fwprintf_unlocked,ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32PRINTF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$wprintf_unlocked,libd_wprintf_unlocked,ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char16_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(wprintf_unlocked,libc_wprintf_unlocked,ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(char32_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(DOS$vwprintf_unlocked,libd_vwprintf_unlocked,ATTR_IN(1) ATTR_LIBC_C16PRINTF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(vwprintf_unlocked,libc_vwprintf_unlocked,ATTR_IN(1) ATTR_LIBC_C32PRINTF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(char32_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$vfwscanf_unlocked,libd_vfwscanf_unlocked,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(vfwscanf_unlocked,libc_vfwscanf_unlocked,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, va_list args),(stream,format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$vwscanf_unlocked,libd_vwscanf_unlocked,WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBDCALL,(char16_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(vwscanf_unlocked,libc_vwscanf_unlocked,WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 0),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,LIBKCALL,(char32_t const *__restrict format, va_list args),(format,args));
DEFINE_PUBLIC_ALIAS_P(DOS$fwscanf_unlocked,libd_fwscanf_unlocked,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C16SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(FILE *__restrict stream, char16_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(fwscanf_unlocked,libc_fwscanf_unlocked,WUNUSED ATTR_IN(2) ATTR_INOUT(1) ATTR_LIBC_C32SCANF(2, 3),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(FILE *__restrict stream, char32_t const *__restrict format, ...),(stream,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$wscanf_unlocked,libd_wscanf_unlocked,WUNUSED ATTR_IN(1) ATTR_LIBC_C16SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBDCALL,(char16_t const *__restrict format, ...),(format,));
DEFINE_PUBLIC_ALIAS_P(wscanf_unlocked,libc_wscanf_unlocked,WUNUSED ATTR_IN(1) ATTR_LIBC_C32SCANF(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_CB_NCX,VLIBKCALL,(char32_t const *__restrict format, ...),(format,));
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SEND)
DEFINE_PUBLIC_ALIAS_P(DOS$wcsend,libd_wcsend,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str),(str));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SEND)
DEFINE_PUBLIC_ALIAS_P(wcsend,libc_wcsend,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict str),(str));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C16SNEND)
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnend,libd_wcsnend,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str, size_t maxlen),(str,maxlen));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C16SNEND */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_C32SNEND)
DEFINE_PUBLIC_ALIAS_P(wcsnend,libc_wcsnend,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 2) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict str, size_t maxlen),(str,maxlen));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_C32SNEND */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$wcsto32_r,libd_wcsto32_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),int32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(wcsto32_r,libc_wcsto32_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),int32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstou32_r,libd_wcstou32_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),uint32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(wcstou32_r,libc_wcstou32_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),uint32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax,libd_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(DOS$wcsto32,libd_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(wcstoimax,libc_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(wcsto32,libc_wcsto32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax,libd_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstou32,libd_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(wcstoumax,libc_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(wcstou32,libc_wcstou32,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsto64_r,libd_wcsto64_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(wcsto64_r,libc_wcsto64_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),int64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstou64_r,libd_wcstou64_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
DEFINE_PUBLIC_ALIAS_P(wcstou64_r,libc_wcstou64_r,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(4),uint64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, errno_t *error),(nptr,endptr,base,error));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax,libd_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoi64,libd_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsto64,libd_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(wcstoimax,libc_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(wcsto64,libc_wcsto64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax,libd_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoui64,libd_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
DEFINE_PUBLIC_ALIAS_P(DOS$wcstou64,libd_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(wcstoumax,libc_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(wcstou64,libc_wcstou64,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base),(nptr,endptr,base));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax_l,libd_wcsto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoimax_l,libd_wcsto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(DOS$wcsto32_l,libd_wcsto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(wcstoimax_l,libc_wcsto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(wcsto32_l,libc_wcsto32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax_l,libd_wcstou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoumax_l,libd_wcstou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstou32_l,libd_wcstou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 4
DEFINE_PUBLIC_ALIAS_P(wcstoumax_l,libc_wcstou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 4 */
DEFINE_PUBLIC_ALIAS_P(wcstou32_l,libc_wcstou32_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint32_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoi64_l,libd_wcsto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoimax_l,libd_wcsto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoimax_l,libd_wcsto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(DOS$wcsto64_l,libd_wcsto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(wcstoimax_l,libc_wcsto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(wcsto64_l,libc_wcsto64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),int64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoui64_l,libd_wcstou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(DOS$wcstoumax_l,libd_wcstou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcstoumax_l,libd_wcstou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(DOS$wcstou64_l,libd_wcstou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict nptr, char16_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#include <hybrid/typecore.h>
#if __SIZEOF_INTMAX_T__ == 8
DEFINE_PUBLIC_ALIAS_P(wcstoumax_l,libc_wcstou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
#endif /* __SIZEOF_INTMAX_T__ == 8 */
DEFINE_PUBLIC_ALIAS_P(wcstou64_l,libc_wcstou64_l,ATTR_LEAF ATTR_IN(1) ATTR_OUT_OPT(2),uint64_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict nptr, char32_t **endptr, __STDC_INT_AS_UINT_T base, locale_t locale),(nptr,endptr,base,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsncoll,libd_wcsncoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncoll,libd_wcsncoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsncoll,libc_wcsncoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsicoll,libd_wcscasecoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscasecoll,libd_wcscasecoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(wcscasecoll,libc_wcscasecoll,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsnicoll,libd_wcsncasecoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncasecoll,libd_wcsncasecoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsncasecoll,libc_wcsncasecoll,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen),(s1,s2,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnrev,libd_wcsnrev,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnrev,libc_wcsnrev,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnlwr,libd_wcsnlwr,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnlwr,libc_wcsnlwr,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnupr,libd_wcsnupr,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnupr,libc_wcsnupr,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, size_t maxlen),(str,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscasestr,libd_wcscasestr,ATTR_PURE WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t const *needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcscasestr,libc_wcscasestr,ATTR_PURE WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t const *needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$wcspcpy,libd_wcspcpy,ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src),(buf,src));
DEFINE_PUBLIC_ALIAS_P(wcspcpy,libc_wcspcpy,ATTR_LEAF ATTR_RETNONNULL ATTR_IN(2) ATTR_OUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src),(buf,src));
DEFINE_PUBLIC_ALIAS_P(DOS$wcspncpy,libd_wcspncpy,ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict buf, char16_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(wcspncpy,libc_wcspncpy,ATTR_LEAF ATTR_RETNONNULL ATTR_INS(2, 3) ATTR_OUTS(1, 3) NONNULL((1, 2)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict buf, char32_t const *__restrict src, size_t buflen),(buf,src,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnchr,libd_wcsnchr,ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnchr,libc_wcsnchr,ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnrchr,libd_wcsnrchr,ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnrchr,libc_wcsnrchr,ATTR_PURE WUNUSED ATTR_INS(1, 3) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcssep,libd_wcssep,ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t **__restrict stringp, char16_t const *__restrict delim),(stringp,delim));
DEFINE_PUBLIC_ALIAS_P(wcssep,libc_wcssep,ATTR_LEAF ATTR_IN(2) ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t **__restrict stringp, char32_t const *__restrict delim),(stringp,delim));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsfry,libd_wcsfry,ATTR_LEAF ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(wcsfry,libc_wcsfry,ATTR_LEAF ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsndup,libd_wcsndup,ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INS(1, 2),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str, size_t max_chars),(str,max_chars));
DEFINE_PUBLIC_ALIAS_P(wcsndup,libc_wcsndup,ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_INS(1, 2),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict str, size_t max_chars),(str,max_chars));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsrchrnul,libd_wcsrchrnul,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcsrchrnul,libc_wcsrchrnul,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnchrnul,libd_wcsnchrnul,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnchrnul,libc_wcsnchrnul,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnrchrnul,libd_wcsnrchrnul,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnrchrnul,libc_wcsnrchrnul,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsoff,libd_wcsoff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcsoff,libc_wcsoff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsroff,libd_wcsroff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(wcsroff,libc_wcsroff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle),(haystack,needle));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnoff,libd_wcsnoff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnoff,libc_wcsnoff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnroff,libd_wcsnroff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict haystack, char16_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnroff,libc_wcsnroff,ATTR_PURE WUNUSED ATTR_IN(1),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict haystack, char32_t needle, size_t maxlen),(haystack,needle,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wcscmp,libd_fuzzy_wcscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wcscmp,libc_fuzzy_wcscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wcsncmp,libd_fuzzy_wcsncmp,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen),(s1,s1_maxlen,s2,s2_maxlen));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wcsncmp,libc_fuzzy_wcsncmp,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen),(s1,s1_maxlen,s2,s2_maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wmemcasecmp,libd_fuzzy_wmemcasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes),(s1,s1_bytes,s2,s2_bytes));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wmemcasecmp,libc_fuzzy_wmemcasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes),(s1,s1_bytes,s2,s2_bytes));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wcscasecmp,libd_fuzzy_wcscasecmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wcscasecmp,libc_fuzzy_wcscasecmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wcsncasecmp,libd_fuzzy_wcsncasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen),(s1,s1_maxlen,s2,s2_maxlen));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wcsncasecmp,libc_fuzzy_wcsncasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen),(s1,s1_maxlen,s2,s2_maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wildwcscmp,libd_wildwcscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *pattern, char16_t const *string),(pattern,string));
DEFINE_PUBLIC_ALIAS_P(wildwcscmp,libc_wildwcscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *pattern, char32_t const *string),(pattern,string));
DEFINE_PUBLIC_ALIAS_P(DOS$wildwcscasecmp,libd_wildwcscasecmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *pattern, char16_t const *string),(pattern,string));
DEFINE_PUBLIC_ALIAS_P(wildwcscasecmp,libc_wildwcscasecmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *pattern, char32_t const *string),(pattern,string));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsverscmp,libd_wcsverscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(wcsverscmp,libc_wcsverscmp,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2),(s1,s2));
DEFINE_PUBLIC_ALIAS_P(DOS$wcslstrip,libd_wcslstrip,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *str),(str));
DEFINE_PUBLIC_ALIAS_P(wcslstrip,libc_wcslstrip,ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsrstrip,libd_wcsrstrip,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *str),(str));
DEFINE_PUBLIC_ALIAS_P(wcsrstrip,libc_wcsrstrip,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsstrip,libd_wcsstrip,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *str),(str));
DEFINE_PUBLIC_ALIAS_P(wcsstrip,libc_wcsstrip,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$wmemcasecmp,libd_wmemcasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(void const *s1, void const *s2, size_t num_chars),(s1,s2,num_chars));
DEFINE_PUBLIC_ALIAS_P(wmemcasecmp,libc_wmemcasecmp,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(void const *s1, void const *s2, size_t num_chars),(s1,s2,num_chars));
DEFINE_PUBLIC_ALIAS_P(DOS$wmemcasecmp_l,libd_wmemcasecmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(void const *s1, void const *s2, size_t num_chars, locale_t locale),(s1,s2,num_chars,locale));
DEFINE_PUBLIC_ALIAS_P(wmemcasecmp_l,libc_wmemcasecmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(void const *s1, void const *s2, size_t num_chars, locale_t locale),(s1,s2,num_chars,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsncoll_l,libd_wcsncoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncoll_l,libd_wcsncoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(wcsncoll_l,libc_wcsncoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsicoll_l,libd_wcscasecoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscasecoll_l,libd_wcscasecoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(wcscasecoll_l,libc_wcscasecoll_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsnicoll_l,libd_wcsncasecoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsncasecoll_l,libd_wcsncasecoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(wcsncasecoll_l,libc_wcsncasecoll_l,ATTR_PURE WUNUSED ATTR_INS(1, 3) ATTR_INS(2, 3) NONNULL((1, 2)),int,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, size_t maxlen, locale_t locale),(s1,s2,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcslwr_l,libd_wcslwr_l,ATTR_LEAF ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcslwr_l,libd_wcslwr_l,ATTR_LEAF ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(wcslwr_l,libc_wcslwr_l,ATTR_LEAF ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsupr_l,libd_wcsupr_l,ATTR_LEAF ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsupr_l,libd_wcsupr_l,ATTR_LEAF ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(wcsupr_l,libc_wcsupr_l,ATTR_LEAF ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, locale_t locale),(str,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnlwr_l,libd_wcsnlwr_l,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, size_t maxlen, locale_t locale),(str,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(wcsnlwr_l,libc_wcsnlwr_l,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, size_t maxlen, locale_t locale),(str,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnupr_l,libd_wcsnupr_l,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, size_t maxlen, locale_t locale),(str,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(wcsnupr_l,libc_wcsnupr_l,ATTR_LEAF ATTR_RETNONNULL ATTR_INOUTS(1, 2) NONNULL((1)),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, size_t maxlen, locale_t locale),(str,maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcscasestr_l,libd_wcscasestr_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t const *haystack, char16_t const *needle, locale_t locale),(haystack,needle,locale));
DEFINE_PUBLIC_ALIAS_P(wcscasestr_l,libc_wcscasestr_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t const *haystack, char32_t const *needle, locale_t locale),(haystack,needle,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wmemcasecmp_l,libd_fuzzy_wmemcasecmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, size_t s1_bytes, char16_t const *s2, size_t s2_bytes, locale_t locale),(s1,s1_bytes,s2,s2_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wmemcasecmp_l,libc_fuzzy_wmemcasecmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, size_t s1_bytes, char32_t const *s2, size_t s2_bytes, locale_t locale),(s1,s1_bytes,s2,s2_bytes,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wcscasecmp_l,libd_fuzzy_wcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, char16_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wcscasecmp_l,libc_fuzzy_wcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, char32_t const *s2, locale_t locale),(s1,s2,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$fuzzy_wcsncasecmp_l,libd_fuzzy_wcsncasecmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t const *s1, size_t s1_maxlen, char16_t const *s2, size_t s2_maxlen, locale_t locale),(s1,s1_maxlen,s2,s2_maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(fuzzy_wcsncasecmp_l,libc_fuzzy_wcsncasecmp_l,ATTR_PURE WUNUSED ATTR_INS(1, 2) ATTR_INS(3, 4) NONNULL((1, 3)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t const *s1, size_t s1_maxlen, char32_t const *s2, size_t s2_maxlen, locale_t locale),(s1,s1_maxlen,s2,s2_maxlen,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wildwcscasecmp_l,libd_wildwcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBDCALL,(char16_t const *pattern, char16_t const *string, locale_t locale),(pattern,string,locale));
DEFINE_PUBLIC_ALIAS_P(wildwcscasecmp_l,libc_wildwcscasecmp_l,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBKCALL,(char32_t const *pattern, char32_t const *string, locale_t locale),(pattern,string,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$wcslcat,libd_wcslcat,ATTR_LEAF ATTR_IN(2) ATTR_INOUTS(1, 3) NONNULL((1)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char16_t const *__restrict src, size_t bufsize),(dst,src,bufsize));
DEFINE_PUBLIC_ALIAS_P(wcslcat,libc_wcslcat,ATTR_LEAF ATTR_IN(2) ATTR_INOUTS(1, 3) NONNULL((1)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char32_t const *__restrict src, size_t bufsize),(dst,src,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$wcslcpy,libd_wcslcpy,ATTR_LEAF ATTR_IN(2) ATTR_OUTS(1, 3) NONNULL((1)),size_t,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict dst, char16_t const *__restrict src, size_t bufsize),(dst,src,bufsize));
DEFINE_PUBLIC_ALIAS_P(wcslcpy,libc_wcslcpy,ATTR_LEAF ATTR_IN(2) ATTR_OUTS(1, 3) NONNULL((1)),size_t,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict dst, char32_t const *__restrict src, size_t bufsize),(dst,src,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsnset,libd_wcsnset,ATTR_RETNONNULL ATTR_INOUTS(1, 3),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, char16_t ch, size_t maxlen),(str,ch,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsnset,libd_wcsnset,ATTR_RETNONNULL ATTR_INOUTS(1, 3),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, char16_t ch, size_t maxlen),(str,ch,maxlen));
DEFINE_PUBLIC_ALIAS_P(wcsnset,libc_wcsnset,ATTR_RETNONNULL ATTR_INOUTS(1, 3),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, char32_t ch, size_t maxlen),(str,ch,maxlen));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsrev,libd_wcsrev,ATTR_RETNONNULL ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsrev,libd_wcsrev,ATTR_RETNONNULL ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(wcsrev,libc_wcsrev,ATTR_RETNONNULL ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsset,libd_wcsset,ATTR_LEAF ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, int ch),(str,ch));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsset,libd_wcsset,ATTR_LEAF ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str, int ch),(str,ch));
DEFINE_PUBLIC_ALIAS_P(wcsset,libc_wcsset,ATTR_LEAF ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str, int ch),(str,ch));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcslwr,libd_wcslwr,ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$wcslwr,libd_wcslwr,ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(wcslwr,libc_wcslwr,ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$_wcsupr,libd_wcsupr,ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$wcsupr,libd_wcsupr,ATTR_INOUT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char16_t *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(wcsupr,libc_wcsupr,ATTR_INOUT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char32_t *__restrict str),(str));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_WCHAR_C */
