/* HASH CRC-32:0xc5e0a657 */
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
#ifndef __local_toctrans16_l_defined
#define __local_toctrans16_l_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$towctrans) || (defined(__CRT_HAVE___towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$__towctrans) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <hybrid/typecore.h>
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_toctrans16_defined
#define __local___localdep_toctrans16_defined
#if defined(__CRT_HAVE_towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_toctrans16,(__WINT16_TYPE__ __wc, __wctrans_t __desc),towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$towctrans)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_toctrans16,(__WINT16_TYPE__ __wc, __wctrans_t __desc),towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE___towctrans) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_toctrans16,(__WINT16_TYPE__ __wc, __wctrans_t __desc),__towctrans,(__wc,__desc))
#elif defined(__CRT_HAVE_DOS$__towctrans)
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_toctrans16,(__WINT16_TYPE__ __wc, __wctrans_t __desc),__towctrans,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towctrans.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toctrans16 __NAMESPACE_LOCAL_TYPEHAX(__WINT16_TYPE__(__LIBDCALL*)(__WINT16_TYPE__,__wctrans_t),__WINT16_TYPE__(__LIBDCALL&)(__WINT16_TYPE__,__wctrans_t),towctrans)
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/toctrans16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toctrans16 __LIBC_LOCAL_NAME(toctrans16)
#else /* ... */
#undef __local___localdep_toctrans16_defined
#endif /* !... */
#endif /* !__local___localdep_toctrans16_defined */
__LOCAL_LIBC(toctrans16_l) __ATTR_WUNUSED __WINT16_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(toctrans16_l))(__WINT16_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale) {
	__COMPILER_IMPURE();
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_toctrans16)(__wc, __desc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_toctrans16_l_defined
#define __local___localdep_toctrans16_l_defined
#define __localdep_toctrans16_l __LIBC_LOCAL_NAME(toctrans16_l)
#endif /* !__local___localdep_toctrans16_l_defined */
#else /* (__CRT_HAVE_towctrans && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$towctrans || (__CRT_HAVE___towctrans && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$__towctrans || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#undef __local_toctrans16_l_defined
#endif /* (!__CRT_HAVE_towctrans || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$towctrans && (!__CRT_HAVE___towctrans || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$__towctrans && (!__CRT_KOS || !__CRT_HAVE___unicode_descriptor) */
#endif /* !__local_toctrans16_l_defined */
