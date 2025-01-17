/* HASH CRC-32:0x22936e6d */
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
#ifndef __local_strcasestr_defined
#define __local_strcasestr_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcasecmp_defined
#define __local___localdep_memcasecmp_defined
#ifdef __CRT_HAVE_memcasecmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memicmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memicmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE__memicmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),_memicmp,(__s1,__s2,__num_chars))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcasecmp __LIBC_LOCAL_NAME(memcasecmp)
#endif /* !... */
#endif /* !__local___localdep_memcasecmp_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strcasestr) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcasestr))(char const *__haystack, char const *__needle) {
	__SIZE_TYPE__ __needle_len = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__needle);
	for (; *__haystack; ++__haystack) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_memcasecmp)(__haystack, __needle, __needle_len * sizeof(char)) == 0)
			return (char *)__haystack;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strcasestr_defined
#define __local___localdep_strcasestr_defined
#define __localdep_strcasestr __LIBC_LOCAL_NAME(strcasestr)
#endif /* !__local___localdep_strcasestr_defined */
#endif /* !__local_strcasestr_defined */
