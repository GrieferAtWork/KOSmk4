/* HASH CRC-32:0x87633646 */
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
#ifndef __local_strtoumax_r_defined
#define __local_strtoumax_r_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtou32_r_defined
#define __local___localdep_strtou32_r_defined
#ifdef __CRT_HAVE_strtou32_r
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT32_TYPE__,__NOTHROW_NCX,__localdep_strtou32_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou32_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou32_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou32_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou32_r __LIBC_LOCAL_NAME(strtou32_r)
#endif /* !__CRT_HAVE_strtou32_r */
#endif /* !__local___localdep_strtou32_r_defined */
#ifndef __local___localdep_strtou64_r_defined
#define __local___localdep_strtou64_r_defined
#ifdef __CRT_HAVE_strtou64_r
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_strtou64_r,(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),strtou64_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_strtou64_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtou64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtou64_r __LIBC_LOCAL_NAME(strtou64_r)
#endif /* !__CRT_HAVE_strtou64_r */
#endif /* !__local___localdep_strtou64_r_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <hybrid/limitcore.h>
#include <asm/os/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtoumax_r) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtoumax_r))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) {
#if __SIZEOF_INTMAX_T__ >= 8
	return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_strtou64_r)(__nptr, __endptr, __base, __error);
#elif __SIZEOF_INTMAX_T__ >= 4
	return (__UINTMAX_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_strtou32_r)(__nptr, __endptr, __base, __error);
#else /* ... */
	__UINT32_TYPE__ __result = (__NAMESPACE_LOCAL_SYM __localdep_strtou32_r)(__nptr, __endptr, __base, __error);
	if (__result > __UINTMAX_MAX__) {
		if (__error) {
#ifdef __ERANGE
			*__error = __ERANGE;
#else /* __ERANGE */
			*__error = 1;
#endif /* !__ERANGE */
		}
		__result = __UINTMAX_MAX__;
	}
	return (__UINTMAX_TYPE__)__result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtoumax_r_defined
#define __local___localdep_strtoumax_r_defined
#define __localdep_strtoumax_r __LIBC_LOCAL_NAME(strtoumax_r)
#endif /* !__local___localdep_strtoumax_r_defined */
#endif /* !__local_strtoumax_r_defined */
