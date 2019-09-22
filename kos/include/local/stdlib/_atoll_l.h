/* HASH CRC-32:0x4b164513 */
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
#ifndef __local__atoll_l_defined
#define __local__atoll_l_defined 1
/* Dependency: "strtoll_l" from "stdlib" */
#ifndef ____localdep_strtoll_l_defined
#define ____localdep_strtoll_l_defined 1
#if defined(__CRT_HAVE_strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoq_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtoq_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),_strtol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto64_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strto32_l) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll_l,(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale),strto32_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: strtoll_l */
#include <local/stdlib/strtoll_l.h>
#define __localdep_strtoll_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strtoll_l))
#endif /* strtoll_l... */
#endif /* !____localdep_strtoll_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_atoll_l) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atoll_l))(char const *__restrict __nptr,
                                                      __locale_t __locale) {
#line 1703 "kos/src/libc/magic/stdlib.c"
	return __localdep_strtoll_l(__nptr, __NULLPTR, 10, __locale);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__atoll_l_defined */
