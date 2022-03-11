/* HASH CRC-32:0x9d93ffce */
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
#ifndef __local_canonicalizel_defined
#define __local_canonicalizel_defined
#include <__crt.h>
#ifdef __CRT_HAVE_canonicalize
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_canonicalize_defined
#define __local___localdep_canonicalize_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_canonicalize,(double *__cx, double const *__x),canonicalize,(__cx,__x))
#endif /* !__local___localdep_canonicalize_defined */
__LOCAL_LIBC(canonicalizel) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(canonicalizel))(__LONGDOUBLE *__cx, __LONGDOUBLE const *__x) {
	return (__NAMESPACE_LOCAL_SYM __localdep_canonicalize)((double *)__cx, (double const *)__x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_canonicalizel_defined
#define __local___localdep_canonicalizel_defined
#define __localdep_canonicalizel __LIBC_LOCAL_NAME(canonicalizel)
#endif /* !__local___localdep_canonicalizel_defined */
#else /* __CRT_HAVE_canonicalize */
#undef __local_canonicalizel_defined
#endif /* !__CRT_HAVE_canonicalize */
#endif /* !__local_canonicalizel_defined */
