/* HASH CRC-32:0x9f9aaec9 */
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
#ifndef __local_strtou_l_defined
#define __local_strtou_l_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtoumax_l from inttypes */
#ifndef __local___localdep_strtoumax_l_defined
#define __local___localdep_strtoumax_l_defined 1
#ifdef __CRT_HAVE_strtoumax_l
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoumax_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoul_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___strtoull_l) && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__strtoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou64_l) && __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__strtoui64_l) && __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_strtoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_strtou32_l) && __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoumax_l,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),strtou32_l,(__nptr,__endptr,__base,__locale))
#elif __SIZEOF_INTMAX_T__ == 8
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou64_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoumax_l (*(__UINTMAX_TYPE__(__LIBCCALL *)(char const *__restrict, char **, __STDC_INT_AS_UINT_T, __locale_t))&__LIBC_LOCAL_NAME(strtou64_l))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if __SIZEOF_INTMAX_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoumax_l (*(__UINTMAX_TYPE__(__LIBCCALL *)(char const *__restrict, char **, __STDC_INT_AS_UINT_T, __locale_t))&__LIBC_LOCAL_NAME(strtou32_l))
#else /* __SIZEOF_INTMAX_T__ == 4 */
__NAMESPACE_LOCAL_END
#include <libc/local/inttypes/strtoumax_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtoumax_l __LIBC_LOCAL_NAME(strtoumax_l)
#endif /* __SIZEOF_INTMAX_T__ != 4 */
#endif /* !... */
#endif /* !__local___localdep_strtoumax_l_defined */
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
__LOCAL_LIBC(strtou_l) __ATTR_LEAF __ATTR_NONNULL((1)) __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtou_l))(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __UINTMAX_TYPE__ __lo, __UINTMAX_TYPE__ __hi, __errno_t *__rstatus, __locale_t __locale) {
	char *__used_endptr;
	__UINTMAX_TYPE__ __result;
	__result = __localdep_strtoumax_l(__nptr, &__used_endptr, __base, __locale);
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
#ifndef __local___localdep_strtou_l_defined
#define __local___localdep_strtou_l_defined 1
#define __localdep_strtou_l __LIBC_LOCAL_NAME(strtou_l)
#endif /* !__local___localdep_strtou_l_defined */
#endif /* !__local_strtou_l_defined */
