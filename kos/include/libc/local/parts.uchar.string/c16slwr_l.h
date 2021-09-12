/* HASH CRC-32:0xc4f10081 */
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
#ifndef __local_c16slwr_l_defined
#define __local_c16slwr_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_toulower16_l_defined
#define __local___localdep_toulower16_l_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towlower_l) && defined(__CRT_HAVE_towlower_l) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_EIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE___towlower_l) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_EIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__LIBDCALL,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW_NCX(__LIBDCALL __localdep_toulower16_l)(__WINT16_TYPE__ __ch, __locale_t __locale) { return __crt_towlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$_towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towlower_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE_DOS$__towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW_NCX,__localdep_toulower16_l,(__WINT16_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towlower_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toulower16_l (*(__WINT16_TYPE__(__LIBDCALL *)(__WINT16_TYPE__, __locale_t))&__LIBC_LOCAL_NAME(towlower_l))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/toulower16_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toulower16_l __LIBC_LOCAL_NAME(toulower16_l)
#endif /* !... */
#endif /* !__local___localdep_toulower16_l_defined */
__LOCAL_LIBC(c16slwr_l) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16slwr_l))(__CHAR16_TYPE__ *__restrict __str, __locale_t __locale) {
	__CHAR16_TYPE__ *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = __localdep_toulower16_l(__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16slwr_l_defined
#define __local___localdep_c16slwr_l_defined 1
#define __localdep_c16slwr_l __LIBC_LOCAL_NAME(c16slwr_l)
#endif /* !__local___localdep_c16slwr_l_defined */
#endif /* !__local_c16slwr_l_defined */
