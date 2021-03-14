/* HASH CRC-32:0xe86a2d0 */
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
#ifndef __local_strtoull_r_defined
#define __local_strtoull_r_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtou32_r from stdlib */
#ifndef __local___localdep_strtou32_r_defined
#define __local___localdep_strtou32_r_defined 1
#ifdef __CRT_HAVE_strtou32_r
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou32_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou32_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32_r.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
#define __localdep_strtou32_r __LIBC_LOCAL_NAME(strtou32_r)
#endif /* !__CRT_HAVE_strtou32_r */
#endif /* !__local___localdep_strtou32_r_defined */
/* Dependency: strtou64_r from stdlib */
#ifndef __local___localdep_strtou64_r_defined
#define __local___localdep_strtou64_r_defined 1
#ifdef __CRT_HAVE_strtou64_r
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou64_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou64_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou64_r.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
#define __localdep_strtou64_r __LIBC_LOCAL_NAME(strtou64_r)
#endif /* !__CRT_HAVE_strtou64_r */
#endif /* !__local___localdep_strtou64_r_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <hybrid/limitcode.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtoull_r) __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoull_r))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) {
#if __SIZEOF_LONG_LONG__ >= 8
	return (__ULONGLONG)__localdep_strtou64_r(__nptr, __endptr, __base, __error);
#elif __SIZEOF_LONG_LONG__ >= 4
	return (__ULONGLONG)__localdep_strtou32_r(__nptr, __endptr, __base, __error);
#else /* ... */
	__UINT32_TYPE__ __result = __localdep_strtou32_r(__nptr, __endptr, __base, __error);
	if (__result > __ULONG_LONG_MAX__) {
		if (__error) {
#ifdef __ERANGE
			*__error = __ERANGE;
#else /* __ERANGE */
			*__error = 1;
#endif /* !__ERANGE */
		}
		__result = __ULONG_LONG_MAX__;
	}
	return (__ULONGLONG)__result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoull_r_defined
#define __local___localdep_strtoull_r_defined 1
#define __localdep_strtoull_r __LIBC_LOCAL_NAME(strtoull_r)
#endif /* !__local___localdep_strtoull_r_defined */
#endif /* !__local_strtoull_r_defined */
