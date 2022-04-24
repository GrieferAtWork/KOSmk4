/* HASH CRC-32:0xfb12133e */
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
#ifndef __local_c16stol_r_defined
#define __local_c16stol_r_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16sto32_r_defined
#define __local___localdep_c16sto32_r_defined
#if defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c16sto32_r,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto32_r)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,__localdep_c16sto32_r,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsto32_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto32_r __NAMESPACE_LOCAL_TYPEHAX(__INT32_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T,__errno_t *),__INT32_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T,__errno_t *),wcsto32_r)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c16sto32_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto32_r __LIBC_LOCAL_NAME(c16sto32_r)
#endif /* !... */
#endif /* !__local___localdep_c16sto32_r_defined */
#ifndef __local___localdep_c16sto64_r_defined
#define __local___localdep_c16sto64_r_defined
#if defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c16sto64_r,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_DOS$wcsto64_r)
__CREDIRECT_DOS(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,__localdep_c16sto64_r,(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsto64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto64_r __NAMESPACE_LOCAL_TYPEHAX(__INT64_TYPE__(__LIBDCALL*)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T,__errno_t *),__INT64_TYPE__(__LIBDCALL&)(__CHAR16_TYPE__ const *__restrict,__CHAR16_TYPE__ **,__STDC_INT_AS_UINT_T,__errno_t *),wcsto64_r)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.stdlib/c16sto64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16sto64_r __LIBC_LOCAL_NAME(c16sto64_r)
#endif /* !... */
#endif /* !__local___localdep_c16sto64_r_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <hybrid/limitcore.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16stol_r) __ATTR_LEAF __ATTR_NONNULL((1)) long
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16stol_r))(__CHAR16_TYPE__ const *__restrict __nptr, __CHAR16_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) {
#if __SIZEOF_LONG__ >= 8
	return (long)(__NAMESPACE_LOCAL_SYM __localdep_c16sto64_r)(__nptr, __endptr, __base, __error);
#elif __SIZEOF_LONG__ >= 4
	return (long)(__NAMESPACE_LOCAL_SYM __localdep_c16sto32_r)(__nptr, __endptr, __base, __error);
#else /* ... */
	__INT32_TYPE__ __result = (__NAMESPACE_LOCAL_SYM __localdep_c16sto32_r)(__nptr, __endptr, __base, __error);
	if (__result > __LONG_MAX__) {
		if (__error) {
#ifdef __ERANGE
			*__error = __ERANGE;
#else /* __ERANGE */
			*__error = 1;
#endif /* !__ERANGE */
		}
		__result = __LONG_MAX__;
	} else if (__result < __LONG_MIN__) {
		if (__error) {
#ifdef __ERANGE
			*__error = __ERANGE;
#else /* __ERANGE */
			*__error = 1;
#endif /* !__ERANGE */
		}
		__result = __LONG_MIN__;
	}
	return (long)__result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16stol_r_defined
#define __local___localdep_c16stol_r_defined
#define __localdep_c16stol_r __LIBC_LOCAL_NAME(c16stol_r)
#endif /* !__local___localdep_c16stol_r_defined */
#endif /* !__local_c16stol_r_defined */
