/* HASH CRC-32:0xdbfe5d9a */
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
#ifndef __local_iswsymstrt_defined
#define __local_iswsymstrt_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep___unicode_descriptor_defined) && defined(__CRT_HAVE___unicode_descriptor)
#define __local___localdep___unicode_descriptor_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_RETNONNULL,struct __unitraits const *,__NOTHROW,__localdep___unicode_descriptor,(__CHAR32_TYPE__ __ch),__unicode_descriptor,(__ch))
#endif /* !__local___localdep___unicode_descriptor_defined && __CRT_HAVE___unicode_descriptor */
#ifndef __local___localdep_iswalpha_defined
#define __local___localdep_iswalpha_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswalpha) && defined(__CRT_HAVE_iswalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswalpha,(__WINT_TYPE__ __wc),iswalpha,{ return __crt_iswalpha(__wc); })
#elif defined(__crt_iswalpha)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_iswalpha)(__WINT_TYPE__ __wc) { return __crt_iswalpha(__wc); }
#elif __has_builtin(__builtin_iswalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalpha)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswalpha,(__WINT_TYPE__ __wc),iswalpha,{ return __builtin_iswalpha(__wc); })
#elif defined(__CRT_HAVE_iswalpha)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswalpha,(__WINT_TYPE__ __wc),iswalpha,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswalpha.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswalpha __LIBC_LOCAL_NAME(iswalpha)
#endif /* !... */
#endif /* !__local___localdep_iswalpha_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/unicode.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswsymstrt) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswsymstrt))(__WINT_TYPE__ __wc) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	struct __unitraits const *__traits = (__NAMESPACE_LOCAL_SYM __localdep___unicode_descriptor)(__wc);
	return (int)(__traits->__ut_flags & __UNICODE_ISSYMSTRT);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return (__NAMESPACE_LOCAL_SYM __localdep_iswalpha)(__wc) || __wc == '_' || __wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_iswsymstrt_defined
#define __local___localdep_iswsymstrt_defined
#define __localdep_iswsymstrt __LIBC_LOCAL_NAME(iswsymstrt)
#endif /* !__local___localdep_iswsymstrt_defined */
#endif /* !__local_iswsymstrt_defined */
