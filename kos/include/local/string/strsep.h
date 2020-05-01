/* HASH CRC-32:0xea2f3024 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strsep_defined
#define __local_strsep_defined 1
#include <__crt.h>
/* Dependency: "strchr" from "string" */
#ifndef ____localdep_strchr_defined
#define ____localdep_strchr_defined 1
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#else /* LIBC: strchr */
#include <local/string/strchr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strchr))
#endif /* strchr... */
#endif /* !____localdep_strchr_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strsep) __ATTR_LEAF __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsep))(char **__restrict __stringp,
                                                    char const *__restrict __delim) {
#line 850 "kos/src/libc/magic/string.c"
	char *__result, *__iter;
	if (!__stringp || (__result = *__stringp) == __NULLPTR || !*__result)
		return __NULLPTR;
	for (__iter = __result; *__iter && !__localdep_strchr(__delim, *__iter); ++__iter)
		;
	if (*__iter)
		*__iter++ = '\0';
	*__stringp = __iter;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strsep_defined */
