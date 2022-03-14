/* HASH CRC-32:0x5079a301 */
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
#ifndef __local__mbbtype_l_defined
#define __local__mbbtype_l_defined
#include <__crt.h>
#if (defined(__CRT_HAVE__ismbbtrail_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)) && (defined(__CRT_HAVE__ismbbprint_l) || defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype))
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep__ismbbprint_l_defined
#define __local___localdep__ismbbprint_l_defined
#ifdef __CRT_HAVE__ismbbprint_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbbprint_l,(unsigned int __ch, __locale_t __locale),_ismbbprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbbprint_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbbprint_l __LIBC_LOCAL_NAME(_ismbbprint_l)
#else /* ... */
#undef __local___localdep__ismbbprint_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbbprint_l_defined */
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
__LOCAL_LIBC(_mbbtype_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbbtype_l))(unsigned char __ch, int __ctype, __locale_t __locale) {
	if (__ctype == 1)
		return (__NAMESPACE_LOCAL_SYM __localdep__ismbbtrail_l)(__ch, __locale) ? 2 : (-1);
	if ((__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__ch, __locale))
		return 1;
	if ((__NAMESPACE_LOCAL_SYM __localdep__ismbbprint_l)(__ch, __locale))
		return 0;
	return (-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbbtype_l_defined
#define __local___localdep__mbbtype_l_defined
#define __localdep__mbbtype_l __LIBC_LOCAL_NAME(_mbbtype_l)
#endif /* !__local___localdep__mbbtype_l_defined */
#else /* (__CRT_HAVE__ismbbtrail_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) && (__CRT_HAVE__ismbbprint_l || __CRT_HAVE__ismbbkana_l || __CRT_HAVE__ismbbkprint_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype) */
#undef __local__mbbtype_l_defined
#endif /* (!__CRT_HAVE__ismbbtrail_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) || (!__CRT_HAVE__ismbbprint_l && !__CRT_HAVE__ismbbkana_l && !__CRT_HAVE__ismbbkprint_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype) */
#endif /* !__local__mbbtype_l_defined */
