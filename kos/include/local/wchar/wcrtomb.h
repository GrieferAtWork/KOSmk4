/* HASH CRC-32:0xd3c523ad */
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
#ifndef __local_wcrtomb_defined
#define __local_wcrtomb_defined 1
#include <__crt.h>
#include <parts/errno.h>
/* Dependency: "unicode_writeutf8" from "unicode" */
#ifndef ____localdep_unicode_writeutf8_defined
#define ____localdep_unicode_writeutf8_defined 1
#ifdef __CRT_HAVE_unicode_writeutf8
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_unicode_writeutf8,(/*utf-8*/ char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* LIBC: unicode_writeutf8 */
#include <local/unicode/unicode_writeutf8.h>
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __localdep_unicode_writeutf8 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_writeutf8))
#endif /* unicode_writeutf8... */
#endif /* !____localdep_unicode_writeutf8_defined */

__NAMESPACE_LOCAL_BEGIN
#if __SIZEOF_WCHAR_T__ == 2
#ifndef ____local_wcrtomb_ps_defined
#define ____local_wcrtomb_ps_defined 1
__LOCAL_LIBC_DATA(__wcrtomb_ps) __mbstate_t __wcrtomb_ps = __MBSTATE_INIT;
#endif /* !____local_wcrtomb_ps_defined */
#endif /* __SIZEOF_WCHAR_T__ == 2 */
__LOCAL_LIBC(wcrtomb) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcrtomb))(char *__restrict __str,
                                                     __WCHAR_TYPE__ __wc,
                                                     __mbstate_t *__mbs) {
#line 255 "kos/src/libc/magic/wchar.c"
	char *__endptr;
	__SIZE_TYPE__ __result;
#if __SIZEOF_WCHAR_T__ == 2
	/* unicode_c16toc8() */
	if (!__mbs)
		__mbs = &__wcrtomb_ps;
	if (!__str) {
		__mbs->__word = 0;
		return 1;
	}
	if ((__mbs->__word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		/* Complete surrogate */
		__CHAR32_TYPE__ __ch32;
		if __unlikely(!((__UINT16_TYPE__)__wc >= 0xdc00 &&
		              (__UINT16_TYPE__)__wc <= 0xdfff)) {
			/* Expected low surrogate */
#ifdef __EILSEQ
			__libc_seterrno(__EILSEQ);
#endif /* EILSEQ */
			return (__SIZE_TYPE__)-1;
		}
		__ch32 = ((__mbs->__word & 0x000003ff) << 10) +
		       0x10000 + ((__UINT16_TYPE__)__wc - 0xdc00);
		__mbs->__word = 0;
		__endptr = __localdep_unicode_writeutf8(__str, __ch32);
	} else if ((__UINT16_TYPE__)__wc >= 0xd800 &&
	           (__UINT16_TYPE__)__wc <= 0xdbff) {
		__mbs->__word = __MBSTATE_TYPE_UTF16_LO | ((__UINT16_TYPE__)__wc - 0xd800);
		return 0;
	} else {
		__endptr = __localdep_unicode_writeutf8(__str, (__CHAR32_TYPE__)(__UINT32_TYPE__)(__UINT16_TYPE__)__wc);
	}
#else /* __SIZEOF_WCHAR_T__ == 2 */
	/* unicode_c32toc8() */
	(void)__mbs;
	if (!__str)
		return 1;
	__endptr = __localdep_unicode_writeutf8(__str, (__CHAR32_TYPE__)__wc);
#endif /* __SIZEOF_WCHAR_T__ != 2 */
	__result = (__SIZE_TYPE__)(__endptr - __str);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcrtomb_defined */
