/* HASH CRC-32:0x3ef04ce5 */
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
#ifndef __local__mbcjmstojis_l_defined
#define __local__mbcjmstojis_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__getmbcp) && (defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__ismbbtrail_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__getmbcp_l_defined
#define __local___localdep__getmbcp_l_defined
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_getmbcp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__getmbcp_l __LIBC_LOCAL_NAME(_getmbcp_l)
#endif /* !__local___localdep__getmbcp_l_defined */
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
#ifdef __CRT_HAVE__ismbblead_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbblead_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbblead_l __LIBC_LOCAL_NAME(_ismbblead_l)
#else /* ... */
#undef __local___localdep__ismbblead_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbblead_l_defined */
#ifndef __local___localdep__ismbbtrail_l_defined
#define __local___localdep__ismbbtrail_l_defined
#ifdef __CRT_HAVE__ismbbtrail_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbbtrail_l,(unsigned int __ch, __locale_t __locale),_ismbbtrail_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbbtrail_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbbtrail_l __LIBC_LOCAL_NAME(_ismbbtrail_l)
#else /* ... */
#undef __local___localdep__ismbbtrail_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbbtrail_l_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbcjmstojis_l) __ATTR_PURE __ATTR_WUNUSED unsigned int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbcjmstojis_l))(unsigned int __ch, __locale_t __locale) {
	unsigned char __c1, __c2;
	/* Extrapolated from reverse engineering. */
	if ((__NAMESPACE_LOCAL_SYM __localdep__getmbcp_l)(__locale) != 932)
		return __ch;
	__c1 = __ch & 0xff;
	__c2 = (__ch >> 8) & 0xff;
	if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__c1, __locale) && (__NAMESPACE_LOCAL_SYM __localdep__ismbbtrail_l)(__c2, __locale)) {
		__c2 -= __c2 < 0xa0 ? 0x81 : 0xc1;
		if (__c1 < 0x9f) {
			__ch = (__c2 * 0x200) + 0x2100;
			__ch |= __c1 - (__c1 < 0x7f ? 0x1f : 0x20);
		} else {
			__ch = (__c2 * 0x200) + 0x2200;
			__ch |= __c1 - 0x7e;
		}
		if ((__ch > 0x2120 && __ch < 0x7e7f) &&
		    ((__ch & 0xff) > 0x20) &&
		    ((__ch & 0xff) < 0x7f))
			return __ch;
	}
#ifdef __EILSEQ
	__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbcjmstojis_l_defined
#define __local___localdep__mbcjmstojis_l_defined
#define __localdep__mbcjmstojis_l __LIBC_LOCAL_NAME(_mbcjmstojis_l)
#endif /* !__local___localdep__mbcjmstojis_l_defined */
#else /* __CRT_HAVE__getmbcp && (__CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__ismbbtrail_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) */
#undef __local__mbcjmstojis_l_defined
#endif /* !__CRT_HAVE__getmbcp || (!__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__ismbbtrail_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) */
#endif /* !__local__mbcjmstojis_l_defined */
