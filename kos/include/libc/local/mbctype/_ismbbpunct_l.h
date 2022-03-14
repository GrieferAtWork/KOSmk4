/* HASH CRC-32:0x61c43ae4 */
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
#ifndef __local__ismbbpunct_l_defined
#define __local__ismbbpunct_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbbkpunct_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbbkpunct_l_defined
#define __local___localdep__ismbbkpunct_l_defined
#ifdef __CRT_HAVE__ismbbkpunct_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbbkpunct_l,(unsigned int __ch, __locale_t __locale),_ismbbkpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbbkpunct_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbbkpunct_l __LIBC_LOCAL_NAME(_ismbbkpunct_l)
#else /* ... */
#undef __local___localdep__ismbbkpunct_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbbkpunct_l_defined */
#ifndef __local___localdep_ispunct_l_defined
#define __local___localdep_ispunct_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_ispunct_l) && defined(__CRT_HAVE_ispunct_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_ispunct_l,(int __ch, __locale_t __locale),ispunct_l,{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l) && defined(__CRT_HAVE__ispunct_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_ispunct_l,(int __ch, __locale_t __locale),_ispunct_l,{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l) && defined(__CRT_HAVE___ispunct_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_ispunct_l,(int __ch, __locale_t __locale),__ispunct_l,{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l)
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __localdep_ispunct_l)(int __ch, __locale_t __locale) { return __crt_ispunct_l(__ch, __locale); }
#elif defined(__CRT_HAVE_ispunct_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_ispunct_l,(int __ch, __locale_t __locale),ispunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE__ispunct_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_ispunct_l,(int __ch, __locale_t __locale),_ispunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE___ispunct_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_ispunct_l,(int __ch, __locale_t __locale),__ispunct_l,(__ch,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/ispunct_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ispunct_l __LIBC_LOCAL_NAME(ispunct_l)
#endif /* !... */
#endif /* !__local___localdep_ispunct_l_defined */
__LOCAL_LIBC(_ismbbpunct_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ismbbpunct_l))(unsigned int __ch, __locale_t __locale) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ispunct_l)(__ch, __locale) || (__NAMESPACE_LOCAL_SYM __localdep__ismbbkpunct_l)(__ch, __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ismbbpunct_l_defined
#define __local___localdep__ismbbpunct_l_defined
#define __localdep__ismbbpunct_l __LIBC_LOCAL_NAME(_ismbbpunct_l)
#endif /* !__local___localdep__ismbbpunct_l_defined */
#else /* __CRT_HAVE__ismbbkpunct_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__ismbbpunct_l_defined
#endif /* !__CRT_HAVE__ismbbkpunct_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__ismbbpunct_l_defined */
