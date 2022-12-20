/* HASH CRC-32:0x9d260a64 */
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
#ifndef __local_strsuftollx_defined
#define __local_strsuftollx_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtoll_defined
#define __local___localdep_strtoll_defined
#ifdef __CRT_HAVE_strtoll
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE___strtoq)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),__strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,__localdep_strtoll,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif __SIZEOF_LONG_LONG__ == 8
__NAMESPACE_LOCAL_END
#include <features.h>
#include <libc/local/stdlib/strto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoll __NAMESPACE_LOCAL_TYPEHAX(__LONGLONG(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__LONGLONG(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strto64)
#elif __SIZEOF_LONG_LONG__ == 4
__NAMESPACE_LOCAL_END
#include <features.h>
#include <libc/local/stdlib/strto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoll __NAMESPACE_LOCAL_TYPEHAX(__LONGLONG(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),__LONGLONG(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T),strto32)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtoll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoll __LIBC_LOCAL_NAME(strtoll)
#endif /* !... */
#endif /* !__local___localdep_strtoll_defined */
__LOCAL_LIBC(strsuftollx) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsuftollx))(char const *__desc, char const *__val, __LONGLONG __lo, __LONGLONG __hi, char *__errbuf, __SIZE_TYPE__ __errbuflen) {
	/* TODO */
	(void)__desc;
	(void)__lo;
	(void)__hi;
	if (__errbuflen)
		*__errbuf = 0;
	return (__NAMESPACE_LOCAL_SYM __localdep_strtoll)(__val, __NULLPTR, 10);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strsuftollx_defined
#define __local___localdep_strsuftollx_defined
#define __localdep_strsuftollx __LIBC_LOCAL_NAME(strsuftollx)
#endif /* !__local___localdep_strsuftollx_defined */
#endif /* !__local_strsuftollx_defined */
