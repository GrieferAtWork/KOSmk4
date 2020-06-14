/* HASH CRC-32:0x311e159a */
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
#ifndef __local_uchar_c32rtomb_defined
#define __local_uchar_c32rtomb_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: unicode_writeutf8 from unicode */
#ifndef __local___localdep_unicode_writeutf8_defined
#define __local___localdep_unicode_writeutf8_defined 1
#ifdef __CRT_HAVE_unicode_writeutf8
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_unicode_writeutf8,(char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf8 */
__NAMESPACE_LOCAL_END
#include <local/unicode/unicode_writeutf8.h>
__NAMESPACE_LOCAL_BEGIN
/* Write a given Unicode character `ch' to `dst' and return a pointer to its end location.
 * This function will write at most `UNICODE_UTF8_CURLEN' bytes to `dst' */
#define __localdep_unicode_writeutf8 __LIBC_LOCAL_NAME(unicode_writeutf8)
#endif /* !__CRT_HAVE_unicode_writeutf8 */
#endif /* !__local___localdep_unicode_writeutf8_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(uchar_c32rtomb) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(uchar_c32rtomb))(char *__restrict __str, __CHAR32_TYPE__ __wc, __mbstate_t *__mbs) {
	char *__endptr;
	__SIZE_TYPE__ __result;
#if 4 == 2
	/* unicode_c16toc8() */
	if (!__mbs) {
		static __mbstate_t __wcrtomb_ps = __MBSTATE_INIT;
		__mbs = &__wcrtomb_ps;
	}
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
#ifdef EILSEQ
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
#else /* 4 == 2 */
	/* unicode_c32toc8() */
	(void)__mbs;
	if (!__str)
		return 1;
	__endptr = __localdep_unicode_writeutf8(__str, (__CHAR32_TYPE__)__wc);
#endif /* !(4 == 2) */
	__result = (__SIZE_TYPE__)(__endptr - __str);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_uchar_c32rtomb_defined
#define __local___localdep_uchar_c32rtomb_defined 1
#define __localdep_uchar_c32rtomb __LIBC_LOCAL_NAME(uchar_c32rtomb)
#endif /* !__local___localdep_uchar_c32rtomb_defined */
#endif /* !__local_uchar_c32rtomb_defined */
