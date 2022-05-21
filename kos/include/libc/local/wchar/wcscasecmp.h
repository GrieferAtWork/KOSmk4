/* HASH CRC-32:0x3084d7f7 */
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
#ifndef __local_wcscasecmp_defined
#define __local_wcscasecmp_defined
#include <__crt.h>
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
__LOCAL_LIBC(wcscasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscasecmp))(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2) {
	__WCHAR_TYPE__ __c1, __c2;
	do {
		__c1 = *__s1++;
		__c2 = *__s2++;
		if (__c1 != __c2) {
			__c1 = (__WCHAR_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_towlower)((__WCHAR_TYPE__)__c1);
			__c2 = (__WCHAR_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_towlower)((__WCHAR_TYPE__)__c2);
			if (__c1 != __c2)
				return (int)((__WCHAR_TYPE__)__c1 - (__WCHAR_TYPE__)__c2);
		}
	} while (__c1 != '\0');
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcscasecmp_defined
#define __local___localdep_wcscasecmp_defined
#define __localdep_wcscasecmp __LIBC_LOCAL_NAME(wcscasecmp)
#endif /* !__local___localdep_wcscasecmp_defined */
#endif /* !__local_wcscasecmp_defined */
