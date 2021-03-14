/* HASH CRC-32:0xc2a26878 */
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
#ifndef __local_strtonum_defined
#define __local_strtonum_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtoi from inttypes */
#ifndef __local___localdep_strtoi_defined
#define __local___localdep_strtoi_defined 1
#ifdef __CRT_HAVE_strtoi
__NAMESPACE_LOCAL_END
#include <features.h>
#include <bits/types.h>
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
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INTMAX_TYPE__,__NOTHROW_NCX,__localdep_strtoi,(char const *__restrict __nptr, char **__restrict __endptr, __STDC_INT_AS_UINT_T __base, __INTMAX_TYPE__ __lo, __INTMAX_TYPE__ __hi, __errno_t *__rstatus),strtoi,(__nptr,__endptr,__base,__lo,__hi,__rstatus))
#else /* __CRT_HAVE_strtoi */
__NAMESPACE_LOCAL_END
#include <libc/local/inttypes/strtoi.h>
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
#define __localdep_strtoi __LIBC_LOCAL_NAME(strtoi)
#endif /* !__CRT_HAVE_strtoi */
#endif /* !__local___localdep_strtoi_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strtonum(3)
 * Similar to `strtoi()' with `base=10', but return human-
 * readable error messages in `*p_errstr' on error (alongside
 * `return==0') (or `NULL' on success).
 * The following messages are defined:
 *   - "too large": Numeric value is too great (`ERANGE' && greater than `hi')
 *   - "too small": Numeric value is too small (`ERANGE' && less than `lo')
 *   - "invalid":   Any other error (`ENOTSUP' or `ECANCELED')
 * @return: 0 : [*p_errstr != NULL] Error
 * @return: 0 : [*p_errstr == NULL] Success
 * @return: * : [*p_errstr == NULL] Success */
__LOCAL_LIBC(strtonum) __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtonum))(char const *__nptr, __LONGLONG __lo, __LONGLONG __hi, char const **__p_errstr) {
	__errno_t __error;
	__LONGLONG __result;
	__result = (__LONGLONG)__localdep_strtoi(__nptr, __NULLPTR, 10, __lo, __hi, &__error);
	if (__error == 0) {
		if (__p_errstr)
			*__p_errstr = __NULLPTR;
		return __result;
	}
	if (__p_errstr) {
		*__p_errstr = "invalid";
#ifdef __ERANGE
		if (__error == __ERANGE) {
			*__p_errstr = "too large";
			if (__result == __lo)
				*__p_errstr = "too small";
		}
#endif /* __ERANGE */
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtonum_defined
#define __local___localdep_strtonum_defined 1
#define __localdep_strtonum __LIBC_LOCAL_NAME(strtonum)
#endif /* !__local___localdep_strtonum_defined */
#endif /* !__local_strtonum_defined */
