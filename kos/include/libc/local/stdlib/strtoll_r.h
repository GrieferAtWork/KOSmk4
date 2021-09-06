/* HASH CRC-32:0xac402014 */
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
#ifndef __local_strtoll_r_defined
#define __local_strtoll_r_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strto32_r_defined
#define __local___localdep_strto32_r_defined 1
#ifdef __CRT_HAVE_strto32_r
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_strto32_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto32_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strto32_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto32_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strto32_r __LIBC_LOCAL_NAME(strto32_r)
#endif /* !__CRT_HAVE_strto32_r */
#endif /* !__local___localdep_strto32_r_defined */
#ifndef __local___localdep_strto64_r_defined
#define __local___localdep_strto64_r_defined 1
#ifdef __CRT_HAVE_strto64_r
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_strto64_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strto64_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strto64_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strto64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strto64_r __LIBC_LOCAL_NAME(strto64_r)
#endif /* !__CRT_HAVE_strto64_r */
#endif /* !__local___localdep_strto64_r_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <hybrid/limitcore.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtoll_r) __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoll_r))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) {
#if __SIZEOF_LONG_LONG__ >= 8
	return (__LONGLONG)__localdep_strto64_r(__nptr, __endptr, __base, __error);
#elif __SIZEOF_LONG_LONG__ >= 4
	return (__LONGLONG)__localdep_strto32_r(__nptr, __endptr, __base, __error);
#else /* ... */
	__INT32_TYPE__ __result = __localdep_strto32_r(__nptr, __endptr, __base, __error);
	if (__result > __LONG_LONG_MAX__) {
		if (__error) {
#ifdef __ERANGE
			*__error = __ERANGE;
#else /* __ERANGE */
			*__error = 1;
#endif /* !__ERANGE */
		}
		__result = __LONG_LONG_MAX__;
	} else if (__result < __LONG_LONG_MIN__) {
		if (__error) {
#ifdef __ERANGE
			*__error = __ERANGE;
#else /* __ERANGE */
			*__error = 1;
#endif /* !__ERANGE */
		}
		__result = __LONG_LONG_MIN__;
	}
	return (__LONGLONG)__result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoll_r_defined
#define __local___localdep_strtoll_r_defined 1
#define __localdep_strtoll_r __LIBC_LOCAL_NAME(strtoll_r)
#endif /* !__local___localdep_strtoll_r_defined */
#endif /* !__local_strtoll_r_defined */
