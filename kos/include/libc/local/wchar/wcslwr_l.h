/* HASH CRC-32:0xffd49161 */
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
#ifndef __local_wcslwr_l_defined
#define __local_wcslwr_l_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_towlower_l_defined
#define __local___localdep_towlower_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towlower_l) && defined(__CRT_HAVE_towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE__towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE___towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_towlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__crt_towlower)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towlower(__ch); }
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towlower_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_towlower_l __LIBC_LOCAL_NAME(towlower_l)
#endif /* !... */
#endif /* !__local___localdep_towlower_l_defined */
__LOCAL_LIBC(wcslwr_l) __ATTR_LEAF __ATTR_ACCESS_RW(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcslwr_l))(__WCHAR_TYPE__ *__restrict __str, __locale_t __locale) {
	__WCHAR_TYPE__ *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__WCHAR_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_towlower_l)((__WCHAR_TYPE__)__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcslwr_l_defined
#define __local___localdep_wcslwr_l_defined
#define __localdep_wcslwr_l __LIBC_LOCAL_NAME(wcslwr_l)
#endif /* !__local___localdep_wcslwr_l_defined */
#endif /* !__local_wcslwr_l_defined */
