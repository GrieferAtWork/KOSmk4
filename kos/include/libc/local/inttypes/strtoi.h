/* HASH CRC-32:0xab062fbf */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strtoi_defined
#define __local_strtoi_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtoimax from inttypes */
#ifndef __local___localdep_strtoimax_defined
#define __local___localdep_strtoimax_defined 1
#ifdef __CRT_HAVE_strtoimax
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoimax,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtol) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoll) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strtoq) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strtoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto64) && __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__strtoi64) && __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),_strtoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_strto32) && __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoimax,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base),strto32,(__nptr,__endptr,__base))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax (*(__INTMAX_TYPE__(__LIBCCALL *)(char const *__restrict, char **, __STDC_INT_AS_UINT_T))&__LIBC_LOCAL_NAME(strto64))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax (*(__INTMAX_TYPE__(__LIBCCALL *)(char const *__restrict, char **, __STDC_INT_AS_UINT_T))&__LIBC_LOCAL_NAME(strto32))
#else /* __SIZEOF_INTMAX_T__ == 4 */
__NAMESPACE_LOCAL_END
#include <libc/local/inttypes/strtoimax.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoimax __LIBC_LOCAL_NAME(strtoimax)
#endif /* __SIZEOF_INTMAX_T__ != 4 */
#endif /* !... */
#endif /* !__local___localdep_strtoimax_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strtoi(3), strtou(3), strtoi_l(3), strtou_l(3)
 * Safely convert `nptr' to an integer which is then returned.
 * If no integer could be read, set `*rstatus' (if non-`NULL') to `ECANCELED'
 * If non-`NULL', `*endptr' is made to point past the read integer, and if
 * it points to a non-'\0'-character, `*rstatus' (if non-`NULL') to `ENOTSUP'
 * Also make sure that the returned integer lies within the
 * bounds of `[lo,hi]' (inclusively). If it does not, clamp it
 * to those bounds and set `*rstatus' (if non-`NULL') to `ERANGE'
 * @param: lo, hi:  Lo/Hi-bounds for the to-be returned integer.
 * @param: rstatus: When non-`NULL', set to a conversion error (if any) */
__LOCAL_LIBC(strtoi) __ATTR_LEAF __ATTR_NONNULL((1)) __INTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoi))(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __INTMAX_TYPE__ __lo, __INTMAX_TYPE__ __hi, __errno_t *__rstatus) {
	char *__used_endptr;
	__INTMAX_TYPE__ __result;
	__result = __localdep_strtoimax(__nptr, &__used_endptr, __base);
	if (__endptr)
		*__endptr = __used_endptr;
	if (__rstatus) {
		if (__used_endptr == __nptr) {
#ifdef __ECANCELED
			*__rstatus = __ECANCELED;
#else /* __ECANCELED */
			*__rstatus = 1;
#endif /* !__ECANCELED */
		} else if (*__used_endptr != '\0') {
#ifdef __ENOTSUP
			*__rstatus = __ENOTSUP;
#else /* __ENOTSUP */
			*__rstatus = 1;
#endif /* !__ENOTSUP */
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
#define __local___localdep_strtoi_defined 1
#define __localdep_strtoi __LIBC_LOCAL_NAME(strtoi)
#endif /* !__local___localdep_strtoi_defined */
#endif /* !__local_strtoi_defined */
