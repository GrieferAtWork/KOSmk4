/* HASH CRC-32:0xe7cf2c7 */
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
#ifndef __local__atoldbl_l_defined
#define __local__atoldbl_l_defined 1
/* Dependency: "strtold_l" from "stdlib" */
#ifndef ____localdep_strtold_l_defined
#define ____localdep_strtold_l_defined 1
#ifdef __CRT_HAVE_strtold_l
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtold_l)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE_strtod_l) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_NONNULL((1)),long double,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtod_l,(__nptr,__endptr,__locale))
#else /* LIBC: strtold_l */
#include <local/stdlib/strtold_l.h>
#define __localdep_strtold_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtold_l))
#endif /* strtold_l... */
#endif /* !____localdep_strtold_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_atoldbl_l) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atoldbl_l))(long double *__restrict __result,
                                                        char __KOS_FIXED_CONST *__restrict __nptr,
                                                        __locale_t __locale) {
#line 2729 "kos/src/libc/magic/stdlib.c"
	*__result = __localdep_strtold_l(__nptr, __NULLPTR, __locale);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__atoldbl_l_defined */
