/* HASH CRC-32:0x6ac15fd2 */
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
#ifndef __local__wcsupr_s_l_defined
#define __local__wcsupr_s_l_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_towupper_l_defined
#define __local___localdep_towupper_l_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towupper_l) && defined(__CRT_HAVE_towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE__towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE___towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_towupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towupper_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__crt_towupper)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towupper(__ch); }
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towupper_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_towupper_l __LIBC_LOCAL_NAME(towupper_l)
#endif /* !... */
#endif /* !__local___localdep_towupper_l_defined */
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined
#ifdef __CRT_HAVE_wcsnlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !... */
#endif /* !__local___localdep_wcsnlen_defined */
__LOCAL_LIBC(_wcsupr_s_l) __ATTR_INOUT_OPT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wcsupr_s_l))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) {
	__WCHAR_TYPE__ *__iter, __ch;
	if (__buf == __NULLPTR)
		return 22;
	if ((__NAMESPACE_LOCAL_SYM __localdep_wcsnlen)(__buf, __buflen) >= __buflen)
		return 22;
	for (__iter = __buf; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = (__WCHAR_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_towupper_l)((__WCHAR_TYPE__)__ch, __locale);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wcsupr_s_l_defined
#define __local___localdep__wcsupr_s_l_defined
#define __localdep__wcsupr_s_l __LIBC_LOCAL_NAME(_wcsupr_s_l)
#endif /* !__local___localdep__wcsupr_s_l_defined */
#endif /* !__local__wcsupr_s_l_defined */
