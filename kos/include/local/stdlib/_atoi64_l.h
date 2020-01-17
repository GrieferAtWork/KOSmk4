/* HASH CRC-32:0xa91e574d */
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
#ifndef __local__atoi64_l_defined
#define __local__atoi64_l_defined 1
/* Dependency: "strto64_l" from "stdlib" */
#ifndef ____localdep_strto64_l_defined
#define ____localdep_strto64_l_defined 1
#ifdef __CRT_HAVE_strto64_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoi64_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtol_l) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),__strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoll_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoll_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),__strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoimax_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoimax_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoimax_l) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),__strtoimax_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strto64_l */
#include <local/stdlib/strto64_l.h>
#define __localdep_strto64_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strto64_l))
#endif /* strto64_l... */
#endif /* !____localdep_strto64_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_atoi64_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atoi64_l))(char const *__restrict __nptr,
                                                       __locale_t __locale) {
#line 2392 "kos/src/libc/magic/stdlib.c"
	return __localdep_strto64_l(__nptr, __NULLPTR, 10, __locale);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__atoi64_l_defined */
