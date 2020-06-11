/* HASH CRC-32:0x6434beea */
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
#ifndef __local_c32rtomb_defined
#define __local_c32rtomb_defined 1
#include <__crt.h>
#include <bits/mbstate.h>
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
__LOCAL_LIBC(c32rtomb) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32rtomb))(char *__restrict __s, __CHAR32_TYPE__ __c32, __mbstate_t *__restrict __mbs) {
	if (!__s) {
		if (__mbs)
			__mbs->__word = __MBSTATE_TYPE_EMPTY;
		return 1;
	}
	if __unlikely((__c32 > 0x10ffff) ||
	            (__mbs && (__mbs->__word & __MBSTATE_TYPE_MASK) != __MBSTATE_TYPE_EMPTY)) {
#ifdef EILSEQ
		__libc_seterrno(__EILSEQ);
#endif /* EILSEQ */
		return (__SIZE_TYPE__)-1;
	}
	/* Write a utf-8 sequence */
	return (__SIZE_TYPE__)(__localdep_unicode_writeutf8(__s, __c32) - __s);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32rtomb_defined
#define __local___localdep_c32rtomb_defined 1
#define __localdep_c32rtomb __LIBC_LOCAL_NAME(c32rtomb)
#endif /* !__local___localdep_c32rtomb_defined */
#endif /* !__local_c32rtomb_defined */
