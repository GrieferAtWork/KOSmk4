/* HASH CRC-32:0x7d282b56 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__ismbbalnum_l_defined
#define __local__ismbbalnum_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbbkalnum_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbbkalnum_l_defined
#define __local___localdep__ismbbkalnum_l_defined
#ifdef __CRT_HAVE__ismbbkalnum_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbbkalnum_l,(unsigned int __ch, __locale_t __locale),_ismbbkalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbbkalnum_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbbkalnum_l __LIBC_LOCAL_NAME(_ismbbkalnum_l)
#else /* ... */
#undef __local___localdep__ismbbkalnum_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbbkalnum_l_defined */
#ifndef __local___localdep_isalnum_l_defined
#define __local___localdep_isalnum_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isalnum_l) && defined(__CRT_HAVE_isalnum_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum_l,(int __ch, __locale_t __locale),isalnum_l,{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l) && defined(__CRT_HAVE__isalnum_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum_l,(int __ch, __locale_t __locale),_isalnum_l,{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l) && defined(__CRT_HAVE___isalnum_l)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum_l,(int __ch, __locale_t __locale),__isalnum_l,{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l)
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __localdep_isalnum_l)(int __ch, __locale_t __locale) { return __crt_isalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum_l,(int __ch, __locale_t __locale),isalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum_l,(int __ch, __locale_t __locale),_isalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isalnum_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum_l,(int __ch, __locale_t __locale),__isalnum_l,(__ch,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isalnum_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isalnum_l __LIBC_LOCAL_NAME(isalnum_l)
#endif /* !... */
#endif /* !__local___localdep_isalnum_l_defined */
__LOCAL_LIBC(_ismbbalnum_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ismbbalnum_l))(unsigned int __ch, __locale_t __locale) {
	return (__NAMESPACE_LOCAL_SYM __localdep_isalnum_l)(__ch, __locale) || (__NAMESPACE_LOCAL_SYM __localdep__ismbbkalnum_l)(__ch, __locale);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ismbbalnum_l_defined
#define __local___localdep__ismbbalnum_l_defined
#define __localdep__ismbbalnum_l __LIBC_LOCAL_NAME(_ismbbalnum_l)
#endif /* !__local___localdep__ismbbalnum_l_defined */
#else /* __CRT_HAVE__ismbbkalnum_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__ismbbalnum_l_defined
#endif /* !__CRT_HAVE__ismbbkalnum_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__ismbbalnum_l_defined */
