/* HASH 0x5d5e9661 */
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
#ifndef __local__atoi64_defined
#define __local__atoi64_defined 1
/* Dependency: "strto64" from "stdlib" */
#ifndef ____localdep_strto64_defined
#define ____localdep_strto64_defined 1
#if defined(__CRT_HAVE_strto64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64,(char const *__restrict __nptr, char **__endptr, int __base),strtoimax,(__nptr,__endptr,__base))
#else /* LIBC: strto64 */
#include <local/stdlib/strto64.h>
#define __localdep_strto64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64))
#endif /* strto64... */
#endif /* !____localdep_strto64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_atoi64) __ATTR_PURE __ATTR_NONNULL((1)) __ATTR_WUNUSED __INT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atoi64))(char const *__restrict __nptr) {
#line 2013 "kos/src/libc/magic/stdlib.c"
	return __localdep_strto64(__nptr, __NULLPTR, 10);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__atoi64_defined */
