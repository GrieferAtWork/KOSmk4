/* HASH CRC-32:0x4a8f1fdb */
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
#ifndef __local_strtrns_defined
#define __local_strtrns_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtrns) __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3) __ATTR_OUT(4) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtrns))(char const *__string, char const *__find_map, char const *__repl_map, char *__result) {
	char *__dst = __result;
	for (;;) {
		char __ch = *__string++;
		char const *__pos;
		if (!__ch)
			break;
		__pos = (__NAMESPACE_LOCAL_SYM __localdep_strchr)(__find_map, __ch);
		if (__pos != __NULLPTR)
			__ch = __repl_map[(__SIZE_TYPE__)(__pos - __find_map)];
		*__dst++ = __ch;
	}
	*__dst++ = '\0';
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtrns_defined
#define __local___localdep_strtrns_defined
#define __localdep_strtrns __LIBC_LOCAL_NAME(strtrns)
#endif /* !__local___localdep_strtrns_defined */
#endif /* !__local_strtrns_defined */
