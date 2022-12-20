/* HASH CRC-32:0x2ea2850e */
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
#ifndef __local_strtoll_l_defined
#define __local_strtoll_l_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtoll_defined
#define __local___localdep_strtoll_defined
#ifdef __CRT_HAVE_strtoll
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_strto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoll __NAMESPACE_LOCAL_TYPEHAX(__LONGLONG(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__LONGLONG(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strto64)
#elif __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoll __NAMESPACE_LOCAL_TYPEHAX(__LONGLONG(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__LONGLONG(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strto32)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoll __LIBC_LOCAL_NAME(strtoll)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_strtoll_defined */
__LOCAL_LIBC(strtoll_l) __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoll_l))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_strtoll)(__nptr, __endptr, __base);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoll_l_defined
#define __local___localdep_strtoll_l_defined
#define __localdep_strtoll_l __LIBC_LOCAL_NAME(strtoll_l)
#endif /* !__local___localdep_strtoll_l_defined */
#endif /* !__local_strtoll_l_defined */
