/* HASH CRC-32:0xa72e5dbd */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strtok_r_defined
#define __local_strtok_r_defined 1
/* Dependency: "strspn" from "string" */
#ifndef ____localdep_strspn_defined
#define ____localdep_strspn_defined 1
#if __has_builtin(__builtin_strspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strspn)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_strspn)(char const *__haystack, char const *__accept) { return __builtin_strspn(__haystack, __accept); }
#elif defined(__CRT_HAVE_strspn)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strspn,(char const *__haystack, char const *__accept),strspn,(__haystack,__accept))
#else /* LIBC: strspn */
#include <local/string/strspn.h>
#define __localdep_strspn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strspn))
#endif /* strspn... */
#endif /* !____localdep_strspn_defined */

/* Dependency: "strcspn" from "string" */
#ifndef ____localdep_strcspn_defined
#define ____localdep_strcspn_defined 1
#if __has_builtin(__builtin_strcspn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcspn)
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_strcspn)(char const *__haystack, char const *__reject) { return __builtin_strcspn(__haystack, __reject); }
#elif defined(__CRT_HAVE_strcspn)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strcspn,(char const *__haystack, char const *__reject),strcspn,(__haystack,__reject))
#else /* LIBC: strcspn */
#include <local/string/strcspn.h>
#define __localdep_strcspn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcspn))
#endif /* strcspn... */
#endif /* !____localdep_strcspn_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtok_r) __ATTR_LEAF __ATTR_LEAF __ATTR_NONNULL((2, 3)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtok_r))(char *__string,
                                                      char const *__delim,
                                                      char **__restrict __save_ptr) {
#line 548 "kos/src/libc/magic/string.c"
	char *__end;
	if (!__string)
		__string = *__save_ptr;
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__string += __localdep_strspn(__string, __delim);
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__end = __string + __localdep_strcspn(__string, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __string;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __string;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strtok_r_defined */
