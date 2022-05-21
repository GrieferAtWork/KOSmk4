/* HASH CRC-32:0x1ad9c0d0 */
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
#ifndef __local_bufsplit_defined
#define __local_bufsplit_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_RO(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
#ifndef __local___localdep_strpbrk_defined
#define __local___localdep_strpbrk_defined
#if __has_builtin(__builtin_strpbrk) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strpbrk)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),char *,__NOTHROW_NCX,__localdep_strpbrk,(char const *__haystack, char const *__accept),strpbrk,{ return __builtin_strpbrk(__haystack, __accept); })
#elif defined(__CRT_HAVE_strpbrk)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),char *,__NOTHROW_NCX,__localdep_strpbrk,(char const *__haystack, char const *__accept),strpbrk,(__haystack,__accept))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strpbrk.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strpbrk __LIBC_LOCAL_NAME(strpbrk)
#endif /* !... */
#endif /* !__local___localdep_strpbrk_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(bufsplit) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bufsplit))(char *__string, __SIZE_TYPE__ __result_c, char **__result_v) {
	__SIZE_TYPE__ __count;
	char const *__splitchar;
	static char const __default_splitchar[] = "\t\n";
#ifdef __pic__
	static char const *__saved_splitchar = __NULLPTR;
	if (__saved_splitchar == __NULLPTR)
		__saved_splitchar = __default_splitchar;
#else /* __pic__ */
	static char const *__saved_splitchar = __default_splitchar;
#endif /* !__pic__ */
	if __unlikely(!__string)
		return 0;
	if (__result_c == 0 && __result_v == 0) {
		__saved_splitchar = (char const *)__string;
		return 1;
	} else {
		if __unlikely((__result_c != 0 && __result_v == 0) ||
		            (__result_c == 0 && __result_v != 0))
			return 0;
	}
	__splitchar = __saved_splitchar;
	for (__count = 0; __count < __result_c; ) {
		__result_v[__count++] = __string;
		/* Find end of field. */
		__string = (__NAMESPACE_LOCAL_SYM __localdep_strpbrk)(__string, __splitchar);
		if (!__string)
			break;
		/* Split field. */
		*__string++ = '\0';
		if (*__string == '\0') {
			/* Special case: end-of-string after field separator
			 * --> no more fields. */
			break;
		}
	}
	/* All remaining fields become the empty string that exists at
	 * the end of the last  (preceding) field. There is always  at
	 * least one field at the start of the string. */
	if (__count < __result_c) {
		__SIZE_TYPE__ __i;
		__string = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result_v[__count - 1]);
		for (__i = __count; __i < __result_c; __i++)
			__result_v[__i] = __string;
	}
	return __count;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_bufsplit_defined
#define __local___localdep_bufsplit_defined
#define __localdep_bufsplit __LIBC_LOCAL_NAME(bufsplit)
#endif /* !__local___localdep_bufsplit_defined */
#endif /* !__local_bufsplit_defined */
