/* HASH CRC-32:0xb4831498 */
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
#ifndef __local_strtof_l_defined
#define __local_strtof_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strtof from stdlib */
#ifndef __local___localdep_strtof_defined
#define __local___localdep_strtof_defined 1
#ifdef __CRT_HAVE_strtof
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,__localdep_strtof,(char const *__restrict __nptr, char **__endptr),strtof,(__nptr,__endptr))
#else /* __CRT_HAVE_strtof */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/strtof.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strtof __LIBC_LOCAL_NAME(strtof)
#endif /* !__CRT_HAVE_strtof */
#endif /* !__local___localdep_strtof_defined */
__LOCAL_LIBC(strtof_l) __ATTR_NONNULL((1)) float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtof_l))(char const *__restrict __nptr, char **__endptr, __locale_t __locale) {
	(void)__locale;
	return __localdep_strtof(__nptr, __endptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtof_l_defined
#define __local___localdep_strtof_l_defined 1
#define __localdep_strtof_l __LIBC_LOCAL_NAME(strtof_l)
#endif /* !__local___localdep_strtof_l_defined */
#endif /* !__local_strtof_l_defined */
