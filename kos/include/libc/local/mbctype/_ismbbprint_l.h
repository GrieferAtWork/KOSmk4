/* HASH CRC-32:0x8bb73c2b */
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
#ifndef __local__ismbbprint_l_defined
#define __local__ismbbprint_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbbkana_l) || defined(__CRT_HAVE__ismbbkprint_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbbkprint_l_defined
#define __local___localdep__ismbbkprint_l_defined
#ifdef __CRT_HAVE__ismbbkana_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbbkprint_l,(unsigned int __ch, __locale_t __locale),_ismbbkana_l,(__ch,__locale))
#elif defined(__CRT_HAVE__ismbbkprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbbkprint_l,(unsigned int __ch, __locale_t __locale),_ismbbkprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbbkana_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbbkprint_l __LIBC_LOCAL_NAME(_ismbbkana_l)
#else /* ... */
#undef __local___localdep__ismbbkprint_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbbkprint_l_defined */
#ifndef __local___localdep_isprint_l_defined
#define __local___localdep_isprint_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isprint_l) && defined(__CRT_HAVE_isprint_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isprint_l,(int __ch, __locale_t __locale),isprint_l,{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l) && defined(__CRT_HAVE__isprint_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isprint_l,(int __ch, __locale_t __locale),_isprint_l,{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l) && defined(__CRT_HAVE___isprint_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isprint_l,(int __ch, __locale_t __locale),__isprint_l,{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l)
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __localdep_isprint_l)(int __ch, __locale_t __locale) { return __crt_isprint_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isprint_l,(int __ch, __locale_t __locale),isprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isprint_l,(int __ch, __locale_t __locale),_isprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isprint_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isprint_l,(int __ch, __locale_t __locale),__isprint_l,(__ch,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isprint_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isprint_l __LIBC_LOCAL_NAME(isprint_l)
#endif /* !... */
#endif /* !__local___localdep_isprint_l_defined */
__LOCAL_LIBC(_ismbbprint_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ismbbprint_l))(unsigned int __ch, __locale_t __locale) {
	return (__NAMESPACE_LOCAL_SYM __localdep_isprint_l)(__ch, __locale) || (__NAMESPACE_LOCAL_SYM __localdep__ismbbkprint_l)(__ch, __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ismbbprint_l_defined
#define __local___localdep__ismbbprint_l_defined
#define __localdep__ismbbprint_l __LIBC_LOCAL_NAME(_ismbbprint_l)
#endif /* !__local___localdep__ismbbprint_l_defined */
#else /* __CRT_HAVE__ismbbkana_l || __CRT_HAVE__ismbbkprint_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__ismbbprint_l_defined
#endif /* !__CRT_HAVE__ismbbkana_l && !__CRT_HAVE__ismbbkprint_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__ismbbprint_l_defined */
