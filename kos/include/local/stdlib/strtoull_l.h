/* HASH CRC-32:0xd72f9f9a */
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
#ifndef __local_strtoull_l_defined
#define __local_strtoull_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtoull from stdlib */
#ifndef __local___localdep_strtoull_defined
#define __local___localdep_strtoull_defined 1
#ifdef __strtoull_defined
__NAMESPACE_GLB_USING(strtoull)
#define __localdep_strtoull strtoull
#elif defined(__std_strtoull_defined)
__NAMESPACE_STD_USING(strtoull)
#define __localdep_strtoull strtoull
#elif defined(__CRT_HAVE_strtoull)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, int __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, int __base),strtoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdlib/strtoull.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoull __LIBC_LOCAL_NAME(strtoull)
#endif /* !... */
#endif /* !__local___localdep_strtoull_defined */
__LOCAL_LIBC(strtoull_l) __ATTR_NONNULL((1)) __ULONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoull_l))(char const *__restrict __nptr, char **__endptr, int __base, __locale_t __locale) {
	(void)__locale;
	return __localdep_strtoull(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoull_l_defined
#define __local___localdep_strtoull_l_defined 1
#define __localdep_strtoull_l __LIBC_LOCAL_NAME(strtoull_l)
#endif /* !__local___localdep_strtoull_l_defined */
#endif /* !__local_strtoull_l_defined */
