/* HASH CRC-32:0xa5d48551 */
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
#ifndef __local__ismbcdigit_l_defined
#define __local__ismbcdigit_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep__mbctouni_l_defined) && defined(__CRT_HAVE__mbctouni_l)
#define __local___localdep__mbctouni_l_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__CHAR32_TYPE__,__NOTHROW_NCX,__localdep__mbctouni_l,(unsigned int __ch, __locale_t __locale),_mbctouni_l,(__ch,__locale))
#endif /* !__local___localdep__mbctouni_l_defined && __CRT_HAVE__mbctouni_l */
#ifndef __local___localdep_isdigit_l_defined
#define __local___localdep_isdigit_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isdigit_l) && defined(__CRT_HAVE_isdigit_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isdigit_l,(int __ch, __locale_t __locale),isdigit_l,{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l) && defined(__CRT_HAVE__isdigit_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isdigit_l,(int __ch, __locale_t __locale),_isdigit_l,{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l) && defined(__CRT_HAVE___isdigit_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isdigit_l,(int __ch, __locale_t __locale),__isdigit_l,{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l)
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __localdep_isdigit_l)(int __ch, __locale_t __locale) { return __crt_isdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isdigit_l,(int __ch, __locale_t __locale),isdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isdigit_l,(int __ch, __locale_t __locale),_isdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isdigit_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isdigit_l,(int __ch, __locale_t __locale),__isdigit_l,(__ch,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isdigit_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isdigit_l __LIBC_LOCAL_NAME(isdigit_l)
#endif /* !... */
#endif /* !__local___localdep_isdigit_l_defined */
__NAMESPACE_LOCAL_END
#include <libc/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_ismbcdigit_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ismbcdigit_l))(unsigned int __ch, __locale_t __locale) {
#if defined(__CRT_HAVE__mbctouni_l) && defined(__CRT_HAVE___unicode_descriptor)
	__CHAR32_TYPE__ __uni = (__NAMESPACE_LOCAL_SYM __localdep__mbctouni_l)(__ch, __locale);
	return __libc_unicode_isdigit(__uni);
#else /* __CRT_HAVE__mbctouni_l && __CRT_HAVE___unicode_descriptor */
	if (__ch <= 0xff)
		return (__NAMESPACE_LOCAL_SYM __localdep_isdigit_l)(__ch, __locale);
	return 0;
#endif /* !__CRT_HAVE__mbctouni_l || !__CRT_HAVE___unicode_descriptor */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ismbcdigit_l_defined
#define __local___localdep__ismbcdigit_l_defined
#define __localdep__ismbcdigit_l __LIBC_LOCAL_NAME(_ismbcdigit_l)
#endif /* !__local___localdep__ismbcdigit_l_defined */
#endif /* !__local__ismbcdigit_l_defined */
