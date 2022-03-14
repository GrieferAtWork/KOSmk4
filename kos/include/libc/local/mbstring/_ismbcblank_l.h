/* HASH CRC-32:0xb8ca7db3 */
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
#ifndef __local__ismbcblank_l_defined
#define __local__ismbcblank_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbbblank_l_defined
#define __local___localdep__ismbbblank_l_defined
#ifdef __CRT_HAVE__ismbbblank_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbbblank_l,(unsigned int __ch, __locale_t __locale),_ismbbblank_l,(__ch,__locale))
#else /* __CRT_HAVE__ismbbblank_l */
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbbblank_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbbblank_l __LIBC_LOCAL_NAME(_ismbbblank_l)
#endif /* !__CRT_HAVE__ismbbblank_l */
#endif /* !__local___localdep__ismbbblank_l_defined */
#if !defined(__local___localdep__mbctouni_l_defined) && defined(__CRT_HAVE__mbctouni_l)
#define __local___localdep__mbctouni_l_defined
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__CHAR32_TYPE__,__NOTHROW_NCX,__localdep__mbctouni_l,(unsigned int __ch, __locale_t __locale),_mbctouni_l,(__ch,__locale))
#endif /* !__local___localdep__mbctouni_l_defined && __CRT_HAVE__mbctouni_l */
__NAMESPACE_LOCAL_END
#include <libc/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_ismbcblank_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ismbcblank_l))(unsigned int __ch, __locale_t __locale) {
#if defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE___unicode_descriptor)
	__CHAR32_TYPE__ __uni = (__NAMESPACE_LOCAL_SYM __localdep__mbctouni_l)(__ch, __locale);
	return __libc_unicode_isblank(__uni);
#else /* __CRT_HAVE__mbctouni_l && __CRT_HAVE___unicode_descriptor */
	if (__ch <= 0xff)
		return (__NAMESPACE_LOCAL_SYM __localdep__ismbbblank_l)(__ch, __locale);
	return 0;
#endif /* !__CRT_HAVE__mbctouni_l || !__CRT_HAVE___unicode_descriptor */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ismbcblank_l_defined
#define __local___localdep__ismbcblank_l_defined
#define __localdep__ismbcblank_l __LIBC_LOCAL_NAME(_ismbcblank_l)
#endif /* !__local___localdep__ismbcblank_l_defined */
#endif /* !__local__ismbcblank_l_defined */
