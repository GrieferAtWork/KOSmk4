/* HASH CRC-32:0xb44c8c61 */
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
#ifndef __local__ldpcomp_defined
#define __local__ldpcomp_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE__dpcomp
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__dpcomp_defined
#define __local___localdep__dpcomp_defined 1
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__dpcomp,(double __x, double __y),_dpcomp,(__x,__y))
#endif /* !__local___localdep__dpcomp_defined */
__LOCAL_LIBC(_ldpcomp) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ldpcomp))(__LONGDOUBLE __x, __LONGDOUBLE __y) {
	return __localdep__dpcomp((double)__x, (double)__y);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__ldpcomp_defined
#define __local___localdep__ldpcomp_defined 1
#define __localdep__ldpcomp __LIBC_LOCAL_NAME(_ldpcomp)
#endif /* !__local___localdep__ldpcomp_defined */
#else /* __CRT_HAVE__dpcomp */
#undef __local__ldpcomp_defined
#endif /* !__CRT_HAVE__dpcomp */
#endif /* !__local__ldpcomp_defined */
