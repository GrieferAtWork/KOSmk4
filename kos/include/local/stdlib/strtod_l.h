/* HASH CRC-32:0xa8b8d760 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strtod_l_defined
#define __local_strtod_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtod from stdlib */
#ifndef __local___localdep_strtod_defined
#define __local___localdep_strtod_defined 1
#ifdef __CRT_HAVE_strtod
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_strtod,(char const *__restrict __nptr, char **__endptr),strtod,(__nptr,__endptr))
#elif defined(__CRT_HAVE_strtold) && (__SIZEOF_LONG_DOUBLE__ == __SIZEOF_DOUBLE__)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,__localdep_strtod,(char const *__restrict __nptr, char **__endptr),strtold,(__nptr,__endptr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/stdlib/strtod.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtod __LIBC_LOCAL_NAME(strtod)
#endif /* !... */
#endif /* !__local___localdep_strtod_defined */
__LOCAL_LIBC(strtod_l) __ATTR_NONNULL((1)) double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtod_l))(char const *__restrict __nptr, char **__endptr, __locale_t __locale) {
	(void)__locale;
	return __localdep_strtod(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtod_l_defined
#define __local___localdep_strtod_l_defined 1
#define __localdep_strtod_l __LIBC_LOCAL_NAME(strtod_l)
#endif /* !__local___localdep_strtod_l_defined */
#endif /* !__local_strtod_l_defined */
