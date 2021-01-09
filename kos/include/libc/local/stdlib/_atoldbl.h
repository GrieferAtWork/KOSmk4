/* HASH CRC-32:0x447b2e2c */
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
#ifndef __local__atoldbl_defined
#define __local__atoldbl_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtold from stdlib */
#ifndef __local___localdep_strtold_defined
#define __local___localdep_strtold_defined 1
#ifdef __CRT_HAVE_strtold
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold,(char const *__restrict __nptr, char **__endptr),strtold,(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtod) && __SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold,(char const *__restrict __nptr, char **__endptr),strtod,(__nptr,__endptr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtold.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtold __LIBC_LOCAL_NAME(strtold)
#endif /* !... */
#endif /* !__local___localdep_strtold_defined */
__LOCAL_LIBC(_atoldbl) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atoldbl))(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr) {
	*__result = __localdep_strtold(__nptr, __NULLPTR);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__atoldbl_defined
#define __local___localdep__atoldbl_defined 1
#define __localdep__atoldbl __LIBC_LOCAL_NAME(_atoldbl)
#endif /* !__local___localdep__atoldbl_defined */
#endif /* !__local__atoldbl_defined */
