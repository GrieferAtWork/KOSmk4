/* HASH CRC-32:0x60d72d3a */
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
#ifndef __local_strtoi_defined
#define __local_strtoi_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtoimax_r_defined
#define __local___localdep_strtoimax_r_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_strto64_r) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_strto32_r) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax_r __NAMESPACE_LOCAL_TYPEHAX(__INTMAX_TYPE__(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T,__errno_t *),__INTMAX_TYPE__(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T,__errno_t *),strto64_r)
#elif __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto32_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax_r __NAMESPACE_LOCAL_TYPEHAX(__INTMAX_TYPE__(__LIBCCALL*)(char const *__restrict,char **,__STDC_INT_AS_UINT_T,__errno_t *),__INTMAX_TYPE__(__LIBCCALL&)(char const *__restrict,char **,__STDC_INT_AS_UINT_T,__errno_t *),strto32_r)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/inttypes/strtoimax_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax_r __LIBC_LOCAL_NAME(strtoimax_r)
#endif /* !... */
#endif /* !__local___localdep_strtoimax_r_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtoi) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(6) __INTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoi))(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __INTMAX_TYPE__ __lo, __INTMAX_TYPE__ __hi, __errno_t *__rstatus) {
	char *__used_endptr;
	__INTMAX_TYPE__ __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_strtoimax_r)(__nptr, &__used_endptr, __base, __rstatus);
	if (__endptr)
		*__endptr = __used_endptr;
	if (__rstatus && *__rstatus == 0) {
		if (*__used_endptr != '\0') {
#ifdef __ENOTSUP
			*__rstatus = __ENOTSUP;
#elif defined(__EINVAL)
			*__rstatus = __EINVAL;
#else /* ... */
			*__rstatus = 1;
#endif /* !... */
		} else if (__result < __lo) {
#ifdef __ERANGE
			*__rstatus = __ERANGE;
#else /* __ERANGE */
			*__rstatus = 1;
#endif /* !__ERANGE */
			__result = __lo;
		} else if (__result > __hi) {
#ifdef __ERANGE
			*__rstatus = __ERANGE;
#else /* __ERANGE */
			*__rstatus = 1;
#endif /* !__ERANGE */
			__result = __hi;
		} else {
			*__rstatus = 0;
		}
	} else {
		if (__result < __lo) {
			__result = __lo;
		} else if (__result > __hi) {
			__result = __hi;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoi_defined
#define __local___localdep_strtoi_defined
#define __localdep_strtoi __LIBC_LOCAL_NAME(strtoi)
#endif /* !__local___localdep_strtoi_defined */
#endif /* !__local_strtoi_defined */
