/* HASH CRC-32:0x954f01c9 */
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
#ifndef __local_c16rtomb_defined
#define __local_c16rtomb_defined 1
#include <__crt.h>
#include <parts/errno.h>

#include <bits/mbstate.h>
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
__LOCAL_LIBC_DATA(__c16rtomb_mbs) __mbstate_t __c16rtomb_mbs = __MBSTATE_INIT;
__LOCAL_LIBC(c16rtomb) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16rtomb))(char *__restrict __s,
                                                      __CHAR16_TYPE__ __c16,
                                                      __mbstate_t *__restrict __mbs) {
#line 152 "kos/src/libc/magic/uchar.c"
	__CHAR32_TYPE__ __ch32;
	if (!__s) {
		if (__mbs)
			__mbs->__word = __MBSTATE_TYPE_EMPTY;
		return 1;
	}
	if (!__mbs)
		__mbs = &__c16rtomb_mbs;
	switch (__mbs->__word & __MBSTATE_TYPE_MASK) {

	case __MBSTATE_TYPE_EMPTY:
		if (__c16 >= 0xd800 && __c16 <= 0xdbff) {
			/* High surrogate (set the MBS to accept a low surrogate as the next character) */
			__mbs->__word = __MBSTATE_TYPE_UTF16_LO | ((__c16 - 0xd800) & 0x3ff);
			return 0;
		}
		__ch32 = (__CHAR32_TYPE__)__c16;
		break;

	case __MBSTATE_TYPE_UTF16_LO:
		/* c16 should be a low surrogate */
		if __unlikely(!(__c16 >= 0xdc00 && __c16 <= 0xdfff))
			goto __error_ilseq;
		__ch32 = ((__mbs->__word & 0x000003ff) << 10) + 0x10000 + (__c16 - 0xdc00);
		__mbs->__word = __MBSTATE_TYPE_EMPTY;
		break;

	default:
__error_ilseq:
#ifdef __EILSEQ
		__libc_seterrno(__EILSEQ);
#endif /* EILSEQ */
		return (__SIZE_TYPE__)-1;
	}
	/* Write a utf-8 sequence */
	return (__SIZE_TYPE__)(__localdep_unicode_writeutf8(__s, __ch32) - __s);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16rtomb_defined */
