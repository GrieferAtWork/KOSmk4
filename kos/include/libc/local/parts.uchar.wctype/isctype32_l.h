/* HASH CRC-32:0x4b99a4b6 */
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
#ifndef __local_isctype32_l_defined
#define __local_isctype32_l_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$iswctype) || (defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$is_wctype) || (defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$__iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <hybrid/typecore.h>
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isctype32_defined
#define __local___localdep_isctype32_defined
#if defined(__CRT_HAVE_iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$iswctype)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$is_wctype)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_KOS$__iswctype)
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isctype32,(__WINT32_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswctype.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isctype32 __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(__WINT32_TYPE__,__wctype_t),int(__LIBKCALL&)(__WINT32_TYPE__,__wctype_t),iswctype)
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/isctype32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isctype32 __LIBC_LOCAL_NAME(isctype32)
#else /* ... */
#undef __local___localdep_isctype32_defined
#endif /* !... */
#endif /* !__local___localdep_isctype32_defined */
__LOCAL_LIBC(isctype32_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(isctype32_l))(__WINT32_TYPE__ __wc, __wctype_t __type, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_isctype32)(__wc, __type);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isctype32_l_defined
#define __local___localdep_isctype32_l_defined
#define __localdep_isctype32_l __LIBC_LOCAL_NAME(isctype32_l)
#endif /* !__local___localdep_isctype32_l_defined */
#else /* (__CRT_HAVE_iswctype && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$iswctype || (__CRT_HAVE_is_wctype && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$is_wctype || (__CRT_HAVE___iswctype && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$__iswctype || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#undef __local_isctype32_l_defined
#endif /* (!__CRT_HAVE_iswctype || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$iswctype && (!__CRT_HAVE_is_wctype || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$is_wctype && (!__CRT_HAVE___iswctype || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$__iswctype && (!__CRT_KOS || !__CRT_HAVE___unicode_descriptor) */
#endif /* !__local_isctype32_l_defined */
