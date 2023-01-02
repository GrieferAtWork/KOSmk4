/* HASH CRC-32:0xc818d06c */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__atodbl_defined
#define __local__atodbl_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtod_defined
#define __local___localdep_strtod_defined
#ifdef __CRT_HAVE_strtod
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,__localdep_strtod,(char const *__restrict __nptr, char **__endptr),strtod,(__nptr,__endptr))
#else /* __CRT_HAVE_strtod */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_strtold) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,__localdep_strtod,(char const *__restrict __nptr, char **__endptr),strtold,(__nptr,__endptr))
#else /* __CRT_HAVE_strtold && __ARCH_LONG_DOUBLE_IS_DOUBLE */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtod.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtod __LIBC_LOCAL_NAME(strtod)
#endif /* !__CRT_HAVE_strtold || !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#endif /* !__CRT_HAVE_strtod */
#endif /* !__local___localdep_strtod_defined */
__LOCAL_LIBC(_atodbl) __ATTR_IN(2) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atodbl))(double *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) {
	*__result = (__NAMESPACE_LOCAL_SYM __localdep_strtod)(__nptr, __NULLPTR);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__atodbl_defined
#define __local___localdep__atodbl_defined
#define __localdep__atodbl __LIBC_LOCAL_NAME(_atodbl)
#endif /* !__local___localdep__atodbl_defined */
#endif /* !__local__atodbl_defined */
