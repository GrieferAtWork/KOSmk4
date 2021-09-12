/* HASH CRC-32:0x2a28b46a */
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
#ifndef __local_isuctype16_l_defined
#define __local_isuctype16_l_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$iswctype) || (defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$is_wctype) || (defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$__iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <hybrid/typecore.h>
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isuctype16_defined
#define __local___localdep_isuctype16_defined 1
#if defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isuctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$iswctype)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isuctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isuctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$is_wctype)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isuctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isuctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$__iswctype)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isuctype16,(__WINT16_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswctype.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isuctype16 (*(int(__LIBDCALL *)(__WINT16_TYPE__, __wctype_t))&__LIBC_LOCAL_NAME(iswctype))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/isuctype16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isuctype16 __LIBC_LOCAL_NAME(isuctype16)
#else /* ... */
#undef __local___localdep_isuctype16_defined
#endif /* !... */
#endif /* !__local___localdep_isuctype16_defined */
__LOCAL_LIBC(isuctype16_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(isuctype16_l))(__WINT16_TYPE__ __wc, __wctype_t __type, __locale_t __locale) {
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_isuctype16(__wc, __type);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isuctype16_l_defined
#define __local___localdep_isuctype16_l_defined 1
#define __localdep_isuctype16_l __LIBC_LOCAL_NAME(isuctype16_l)
#endif /* !__local___localdep_isuctype16_l_defined */
#else /* (__CRT_HAVE_iswctype && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$iswctype || (__CRT_HAVE_is_wctype && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$is_wctype || (__CRT_HAVE___iswctype && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$__iswctype || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#undef __local_isuctype16_l_defined
#endif /* (!__CRT_HAVE_iswctype || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$iswctype && (!__CRT_HAVE_is_wctype || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$is_wctype && (!__CRT_HAVE___iswctype || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$__iswctype && (!__CRT_KOS || !__CRT_HAVE___unicode_descriptor) */
#endif /* !__local_isuctype16_l_defined */
