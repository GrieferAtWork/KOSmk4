/* HASH CRC-32:0x3fbb0cd2 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcrtomb_defined
#define __local_wcrtomb_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unicode_writeutf8_defined
#define __local___localdep_unicode_writeutf8_defined
#ifdef __CRT_HAVE_unicode_writeutf8
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_unicode_writeutf8,(char *__restrict __dst, __CHAR32_TYPE__ __ch),unicode_writeutf8,(__dst,__ch))
#else /* __CRT_HAVE_unicode_writeutf8 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_writeutf8.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_writeutf8 __LIBC_LOCAL_NAME(unicode_writeutf8)
#endif /* !__CRT_HAVE_unicode_writeutf8 */
#endif /* !__local___localdep_unicode_writeutf8_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcrtomb) __ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcrtomb))(char *__restrict __str, __WCHAR_TYPE__ __wc, struct __mbstate *__mbs) {
	char *__endptr;
	__SIZE_TYPE__ __result;
#if __SIZEOF_WCHAR_T__ == 2
	/* unicode_c16toc8() */
	if (!__mbs) {



		/* For whatever reason, libc4/5 exported this `wcrtomb_ps' as `_mb_shift' */
		static struct __mbstate __wcrtomb_ps = __MBSTATE_INIT;
		__mbs = &__wcrtomb_ps;

	}
	if (!__str) {
		__mbstate_init(__mbs);
		return 1;
	}
	if ((__mbs->__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		/* Complete surrogate */
		__CHAR32_TYPE__ __ch32;
		if __unlikely(!((__UINT16_TYPE__)__wc >= 0xdc00 &&
		              (__UINT16_TYPE__)__wc <= 0xdfff)) {
			/* Expected low surrogate */
#ifdef __EILSEQ
			(void)__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
			return (__SIZE_TYPE__)-1;
		}
		__ch32 = ((__mbs->__mb_word & 0x000003ff) << 10) +
		       0x10000 + ((__UINT16_TYPE__)__wc - 0xdc00);
		__mbs->__mb_word = __MBSTATE_TYPE_EMPTY;
		__endptr = (__NAMESPACE_LOCAL_SYM __localdep_unicode_writeutf8)(__str, __ch32);
	} else if ((__UINT16_TYPE__)__wc >= 0xd800 &&
	           (__UINT16_TYPE__)__wc <= 0xdbff) {
		__mbs->__mb_word = __MBSTATE_TYPE_UTF16_LO | ((__UINT16_TYPE__)__wc - 0xd800);
		return 0;
	} else {
		__endptr = (__NAMESPACE_LOCAL_SYM __localdep_unicode_writeutf8)(__str, (__CHAR32_TYPE__)(__UINT32_TYPE__)(__UINT16_TYPE__)__wc);
	}
#else /* __SIZEOF_WCHAR_T__ == 2 */
	/* unicode_c32toc8() */
	(void)__mbs;
	if (!__str)
		return 1;
	__endptr = (__NAMESPACE_LOCAL_SYM __localdep_unicode_writeutf8)(__str, (__CHAR32_TYPE__)__wc);
#endif /* __SIZEOF_WCHAR_T__ != 2 */
	__result = (__SIZE_TYPE__)(__endptr - __str);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcrtomb_defined
#define __local___localdep_wcrtomb_defined
#define __localdep_wcrtomb __LIBC_LOCAL_NAME(wcrtomb)
#endif /* !__local___localdep_wcrtomb_defined */
#endif /* !__local_wcrtomb_defined */
