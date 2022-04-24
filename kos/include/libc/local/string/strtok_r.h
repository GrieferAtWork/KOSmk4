/* HASH CRC-32:0x3deaa1da */
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
#ifndef __local_strtok_r_defined
#define __local_strtok_r_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strcspn_defined
#define __local___localdep_strcspn_defined
#if __has_builtin(__builtin_strcspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcspn)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strcspn,(char const *__haystack, char const *__reject),strcspn,{ return __builtin_strcspn(__haystack, __reject); })
#elif defined(__CRT_HAVE_strcspn)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strcspn,(char const *__haystack, char const *__reject),strcspn,(__haystack,__reject))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcspn __LIBC_LOCAL_NAME(strcspn)
#endif /* !... */
#endif /* !__local___localdep_strcspn_defined */
#ifndef __local___localdep_strspn_defined
#define __local___localdep_strspn_defined
#if __has_builtin(__builtin_strspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strspn)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strspn,(char const *__haystack, char const *__accept),strspn,{ return __builtin_strspn(__haystack, __accept); })
#elif defined(__CRT_HAVE_strspn)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strspn,(char const *__haystack, char const *__accept),strspn,(__haystack,__accept))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strspn __LIBC_LOCAL_NAME(strspn)
#endif /* !... */
#endif /* !__local___localdep_strspn_defined */
__LOCAL_LIBC(strtok_r) __ATTR_LEAF __ATTR_NONNULL((2, 3)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtok_r))(char *__str, char const *__delim, char **__restrict __save_ptr) {
	char *__end;
	if (!__str)
		__str = *__save_ptr;
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__str += (__NAMESPACE_LOCAL_SYM __localdep_strspn)(__str, __delim);
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__end = __str + (__NAMESPACE_LOCAL_SYM __localdep_strcspn)(__str, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __str;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtok_r_defined
#define __local___localdep_strtok_r_defined
#define __localdep_strtok_r __LIBC_LOCAL_NAME(strtok_r)
#endif /* !__local___localdep_strtok_r_defined */
#endif /* !__local_strtok_r_defined */
