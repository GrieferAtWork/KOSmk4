/* HASH CRC-32:0xbebbe060 */
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
#ifndef __local_fmaxmagf_defined
#define __local_fmaxmagf_defined
#include <__crt.h>
#ifdef __CRT_HAVE_fmaxmag
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fmaxmag_defined
#define __local___localdep_fmaxmag_defined
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW_NCX,__localdep_fmaxmag,(double __x, double __y),fmaxmag,(__x,__y))
#endif /* !__local___localdep_fmaxmag_defined */
__LOCAL_LIBC(fmaxmagf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fmaxmagf))(float __x, float __y) {
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_fmaxmag)((double)__x, (double)__y);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmaxmagf_defined
#define __local___localdep_fmaxmagf_defined
#define __localdep_fmaxmagf __LIBC_LOCAL_NAME(fmaxmagf)
#endif /* !__local___localdep_fmaxmagf_defined */
#else /* __CRT_HAVE_fmaxmag */
#undef __local_fmaxmagf_defined
#endif /* !__CRT_HAVE_fmaxmag */
#endif /* !__local_fmaxmagf_defined */