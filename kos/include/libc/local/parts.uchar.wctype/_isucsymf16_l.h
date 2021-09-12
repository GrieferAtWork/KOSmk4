/* HASH CRC-32:0xa857f4c0 */
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
#ifndef __local__isucsymf16_l_defined
#define __local__isucsymf16_l_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___isucsymf16_defined
#define __local___localdep___isucsymf16_defined 1
#if defined(__CRT_HAVE___iswcsymf) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep___isucsymf16,(__WINT16_TYPE__ __wc),__iswcsymf,(__wc))
#elif defined(__CRT_HAVE_DOS$__iswcsymf)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep___isucsymf16,(__WINT16_TYPE__ __wc),__iswcsymf,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/__iswcsymf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___isucsymf16 (*(int(__LIBDCALL *)(__WINT16_TYPE__))&__LIBC_LOCAL_NAME(__iswcsymf))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/__isucsymf16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___isucsymf16 __LIBC_LOCAL_NAME(__isucsymf16)
#endif /* !... */
#endif /* !__local___localdep___isucsymf16_defined */
#ifndef __local___localdep_isualpha16_l_defined
#define __local___localdep_isualpha16_l_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswalpha_l) && defined(__CRT_HAVE_iswalpha_l) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_EIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE___iswalpha_l) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_EIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__LIBDCALL,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && __SIZEOF_WCHAR_T__ == 2
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBDCALL __localdep_isualpha16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_iswalpha_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalpha_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$iswalpha_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalpha_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_iswalpha_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalpha_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__iswalpha_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isualpha16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswalpha_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isualpha16_l (*(int(__LIBDCALL *)(__WINT16_TYPE__, __locale_t))&__LIBC_LOCAL_NAME(iswalpha_l))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/isualpha16_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isualpha16_l __LIBC_LOCAL_NAME(isualpha16_l)
#endif /* !... */
#endif /* !__local___localdep_isualpha16_l_defined */
__LOCAL_LIBC(_isucsymf16_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_isucsymf16_l))(__WINT16_TYPE__ __wc, __locale_t __locale) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep___isucsymf16(__wc);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return __localdep_isualpha16_l(__wc, __locale) || __wc == '_' || __wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__isucsymf16_l_defined
#define __local___localdep__isucsymf16_l_defined 1
#define __localdep__isucsymf16_l __LIBC_LOCAL_NAME(_isucsymf16_l)
#endif /* !__local___localdep__isucsymf16_l_defined */
#endif /* !__local__isucsymf16_l_defined */
