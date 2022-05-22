/* HASH CRC-32:0xe28b4045 */
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
#ifndef __local_strtoull_l_defined
#define __local_strtoull_l_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtoull_defined
#define __local___localdep_strtoull_defined
#ifdef __CRT_HAVE_strtoull
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtouq)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtouq,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_strtou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2),__ULONGLONG,__NOTHROW_NCX,__localdep_strtoull,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoumax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoull __NAMESPACE_LOCAL_TYPEHAX(__ULONGLONG(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__ULONGLONG(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strtou64)
#elif __SIZEOF_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoull __NAMESPACE_LOCAL_TYPEHAX(__ULONGLONG(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__ULONGLONG(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strtou32)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtoull.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoull __LIBC_LOCAL_NAME(strtoull)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_strtoull_defined */
__LOCAL_LIBC(strtoull_l) __ATTR_ACCESS_RO(1) __ATTR_ACCESS_WR_OPT(2) __ULONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoull_l))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_strtoull)(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoull_l_defined
#define __local___localdep_strtoull_l_defined
#define __localdep_strtoull_l __LIBC_LOCAL_NAME(strtoull_l)
#endif /* !__local___localdep_strtoull_l_defined */
#endif /* !__local_strtoull_l_defined */
