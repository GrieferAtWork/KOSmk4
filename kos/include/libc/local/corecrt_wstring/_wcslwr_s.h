/* HASH CRC-32:0xa63c01e8 */
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
#ifndef __local__wcslwr_s_defined
#define __local__wcslwr_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_towlower_defined
#define __local___localdep_towlower_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towlower,(__WINT_TYPE__ __wc),towlower,{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_CONST __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW(__LIBCCALL __localdep_towlower)(__WINT_TYPE__ __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towlower,(__WINT_TYPE__ __wc),towlower,{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW,__localdep_towlower,(__WINT_TYPE__ __wc),towlower,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towlower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_towlower __LIBC_LOCAL_NAME(towlower)
#endif /* !... */
#endif /* !__local___localdep_towlower_defined */
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined
#ifdef __CRT_HAVE_wcsnlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !... */
#endif /* !__local___localdep_wcsnlen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wcslwr_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wcslwr_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen) {
	__WCHAR_TYPE__ *__iter, __ch;
	if (__buf == __NULLPTR)
		return 22;
	if ((__NAMESPACE_LOCAL_SYM __localdep_wcsnlen)(__buf, __buflen) >= __buflen)
		return 22;
	for (__iter = __buf; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__WCHAR_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_towlower)((__WCHAR_TYPE__)__ch);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wcslwr_s_defined
#define __local___localdep__wcslwr_s_defined
#define __localdep__wcslwr_s __LIBC_LOCAL_NAME(_wcslwr_s)
#endif /* !__local___localdep__wcslwr_s_defined */
#endif /* !__local__wcslwr_s_defined */
