/* HASH CRC-32:0x3998de4e */
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
#ifndef __local_strfind_defined
#define __local_strfind_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strstr_defined
#define __local___localdep_strstr_defined
#if __has_builtin(__builtin_strstr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strstr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,__localdep_strstr,(char const *__haystack, char const *__needle),strstr,{ return __builtin_strstr(__haystack, __needle); })
#elif defined(__CRT_HAVE_strstr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,__localdep_strstr,(char const *__haystack, char const *__needle),strstr,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strstr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strstr __LIBC_LOCAL_NAME(strstr)
#endif /* !... */
#endif /* !__local___localdep_strstr_defined */
__LOCAL_LIBC(strfind) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strfind))(char const *__haystack, char const *__needle) {
	char const *__ptr = (__NAMESPACE_LOCAL_SYM __localdep_strstr)(__haystack, __needle);
	return __ptr ? (__STDC_INT_AS_SSIZE_T)(__ptr - __haystack) : -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strfind_defined
#define __local___localdep_strfind_defined
#define __localdep_strfind __LIBC_LOCAL_NAME(strfind)
#endif /* !__local___localdep_strfind_defined */
#endif /* !__local_strfind_defined */
