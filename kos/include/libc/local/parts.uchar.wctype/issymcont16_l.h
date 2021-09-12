/* HASH CRC-32:0x69a35ae4 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_issymcont16_l_defined
#define __local_issymcont16_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isalnum16_l_defined
#define __local___localdep_isalnum16_l_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswalnum_l) && defined(__CRT_HAVE_iswalnum_l) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_EIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE___iswalnum_l) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_EIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && __SIZEOF_WCHAR_T__ == 2
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL __localdep_isalnum16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalnum_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswalnum_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalnum_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswalnum_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalnum_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswalnum_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isalnum16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswalnum_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isalnum16_l __NAMESPACE_LOCAL_TYPEHAX(int(__LIBDCALL*)(__WINT16_TYPE__,__locale_t),int(__LIBDCALL&)(__WINT16_TYPE__,__locale_t),iswalnum_l)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/isalnum16_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isalnum16_l __LIBC_LOCAL_NAME(isalnum16_l)
#endif /* !... */
#endif /* !__local___localdep_isalnum16_l_defined */
__LOCAL_LIBC(issymcont16_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(issymcont16_l))(__WINT16_TYPE__ __wc, __locale_t __locale) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	(void)__locale;
	__COMPILER_IMPURE();
	return __iswcsym(__wc);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return __NAMESPACE_LOCAL_SYM __localdep_isalnum16_l(__wc, __locale) || __wc == '_' || __wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_issymcont16_l_defined
#define __local___localdep_issymcont16_l_defined 1
#define __localdep_issymcont16_l __LIBC_LOCAL_NAME(issymcont16_l)
#endif /* !__local___localdep_issymcont16_l_defined */
#endif /* !__local_issymcont16_l_defined */
