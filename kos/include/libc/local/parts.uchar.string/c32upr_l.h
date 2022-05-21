/* HASH CRC-32:0x9bf9f604 */
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
#ifndef __local_c32upr_l_defined
#define __local_c32upr_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_toupper32_l_defined
#define __local___localdep_toupper32_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towupper_l) && defined(__CRT_HAVE_towupper_l) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE__towupper_l) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE___towupper_l) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__LIBKCALL,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL __localdep_toupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { return __crt_towupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$_towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towupper_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE_KOS$__towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW_NCX,__localdep_toupper32_l,(__WINT32_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__crt_towupper) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW_NCX(__LIBKCALL __localdep_toupper32_l)(__WINT32_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towupper(__ch); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towupper_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper32_l __NAMESPACE_LOCAL_TYPEHAX(__WINT32_TYPE__(__LIBKCALL*)(__WINT32_TYPE__,__locale_t),__WINT32_TYPE__(__LIBKCALL&)(__WINT32_TYPE__,__locale_t),towupper_l)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/toupper32_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_toupper32_l __LIBC_LOCAL_NAME(toupper32_l)
#endif /* !... */
#endif /* !__local___localdep_toupper32_l_defined */
__LOCAL_LIBC(c32upr_l) __ATTR_LEAF __ATTR_ACCESS_RW(1) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32upr_l))(__CHAR32_TYPE__ *__restrict __str, __locale_t __locale) {
	__CHAR32_TYPE__ *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__CHAR32_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_toupper32_l)((__CHAR32_TYPE__)__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32upr_l_defined
#define __local___localdep_c32upr_l_defined
#define __localdep_c32upr_l __LIBC_LOCAL_NAME(c32upr_l)
#endif /* !__local___localdep_c32upr_l_defined */
#endif /* !__local_c32upr_l_defined */
