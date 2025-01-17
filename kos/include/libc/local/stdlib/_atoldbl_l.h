/* HASH CRC-32:0xa80b2386 */
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
#ifndef __local__atoldbl_l_defined
#define __local__atoldbl_l_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strtold_l_defined
#define __local___localdep_strtold_l_defined
#ifdef __CRT_HAVE_strtold_l
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtold_l)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtold_l)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtold_l,(__nptr,__endptr,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_strtod_l) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__strtod_l) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),_strtod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___strtod_l) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,__localdep_strtold_l,(char const *__restrict __nptr, char **__endptr, __locale_t __locale),__strtod_l,(__nptr,__endptr,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtold_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtold_l __LIBC_LOCAL_NAME(strtold_l)
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_strtold_l_defined */
__LOCAL_LIBC(_atoldbl_l) __ATTR_IN(2) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_atoldbl_l))(__LONGDOUBLE *__restrict __result, char __KOS_FIXED_CONST *__restrict __nptr, __locale_t __locale) {
	*__result = (__NAMESPACE_LOCAL_SYM __localdep_strtold_l)(__nptr, __NULLPTR, __locale);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__atoldbl_l_defined
#define __local___localdep__atoldbl_l_defined
#define __localdep__atoldbl_l __LIBC_LOCAL_NAME(_atoldbl_l)
#endif /* !__local___localdep__atoldbl_l_defined */
#endif /* !__local__atoldbl_l_defined */
