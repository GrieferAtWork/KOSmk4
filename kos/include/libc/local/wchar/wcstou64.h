/* HASH CRC-32:0xa86d8a3d */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcstou64_defined
#define __local_wcstou64_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstou64_r_defined
#define __local___localdep_wcstou64_r_defined
#ifdef __CRT_HAVE_wcstou64_r
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,__localdep_wcstou64_r,(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcstou64_r */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstou64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstou64_r __LIBC_LOCAL_NAME(wcstou64_r)
#endif /* !__CRT_HAVE_wcstou64_r */
#endif /* !__local___localdep_wcstou64_r_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcstou64) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstou64))(__WCHAR_TYPE__ const *__restrict __nptr, __WCHAR_TYPE__ **__endptr, __STDC_INT_AS_UINT_T __base) {
#if defined(__libc_geterrno) && defined(__ERANGE)
	__UINT64_TYPE__ __result;
	__errno_t __error;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_wcstou64_r)(__nptr, __endptr, __base, &__error);
	if (__error == __ERANGE)
		(void)__libc_seterrno(__ERANGE);
	return __result;
#else /* __libc_geterrno && __ERANGE */
	return (__NAMESPACE_LOCAL_SYM __localdep_wcstou64_r)(__nptr, __endptr, __base, __NULLPTR);
#endif /* !__libc_geterrno || !__ERANGE */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcstou64_defined
#define __local___localdep_wcstou64_defined
#define __localdep_wcstou64 __LIBC_LOCAL_NAME(wcstou64)
#endif /* !__local___localdep_wcstou64_defined */
#endif /* !__local_wcstou64_defined */
