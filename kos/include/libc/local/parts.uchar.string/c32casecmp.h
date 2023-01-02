/* HASH CRC-32:0xfac69030 */
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
#ifndef __local_c32casecmp_defined
#define __local_c32casecmp_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tolower32_defined
#define __local___localdep_tolower32_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW,__LIBKCALL,__localdep_tolower32,(__WINT32_TYPE__ __wc),towlower,{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_CONST __ATTR_WUNUSED __WINT32_TYPE__ __NOTHROW(__LIBKCALL __localdep_tolower32)(__WINT32_TYPE__ __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW,__LIBKCALL,__localdep_tolower32,(__WINT32_TYPE__ __wc),towlower,{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW,__localdep_tolower32,(__WINT32_TYPE__ __wc),towlower,(__wc))
#elif defined(__CRT_HAVE_KOS$towlower)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,__WINT32_TYPE__,__NOTHROW,__localdep_tolower32,(__WINT32_TYPE__ __wc),towlower,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towlower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower32 __NAMESPACE_LOCAL_TYPEHAX(__WINT32_TYPE__(__LIBKCALL*)(__WINT32_TYPE__),__WINT32_TYPE__(__LIBKCALL&)(__WINT32_TYPE__),towlower)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/tolower32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower32 __LIBC_LOCAL_NAME(tolower32)
#endif /* !... */
#endif /* !__local___localdep_tolower32_defined */
__LOCAL_LIBC(c32casecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32casecmp))(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2) {
	__CHAR32_TYPE__ __c1, __c2;
	do {
		__c1 = *__s1++;
		__c2 = *__s2++;
		if (__c1 != __c2) {
			__c1 = (__CHAR32_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower32)((__CHAR32_TYPE__)__c1);
			__c2 = (__CHAR32_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower32)((__CHAR32_TYPE__)__c2);
			if (__c1 != __c2)
				return (int)((__CHAR32_TYPE__)__c1 - (__CHAR32_TYPE__)__c2);
		}
	} while (__c1 != '\0');
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32casecmp_defined
#define __local___localdep_c32casecmp_defined
#define __localdep_c32casecmp __LIBC_LOCAL_NAME(c32casecmp)
#endif /* !__local___localdep_c32casecmp_defined */
#endif /* !__local_c32casecmp_defined */
