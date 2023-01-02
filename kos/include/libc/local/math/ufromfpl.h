/* HASH CRC-32:0x656bd571 */
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
#ifndef __local_ufromfpl_defined
#define __local_ufromfpl_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ufromfp
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ufromfp_defined
#define __local___localdep_ufromfp_defined
__CREDIRECT(__ATTR_WUNUSED,__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_ufromfp,(double __x, int __round, unsigned int __width),ufromfp,(__x,__round,__width))
#endif /* !__local___localdep_ufromfp_defined */
__LOCAL_LIBC(ufromfpl) __ATTR_WUNUSED __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ufromfpl))(__LONGDOUBLE __x, int __roundl, unsigned int __width) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ufromfp)((double)__x, __roundl, __width);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ufromfpl_defined
#define __local___localdep_ufromfpl_defined
#define __localdep_ufromfpl __LIBC_LOCAL_NAME(ufromfpl)
#endif /* !__local___localdep_ufromfpl_defined */
#else /* __CRT_HAVE_ufromfp */
#undef __local_ufromfpl_defined
#endif /* !__CRT_HAVE_ufromfp */
#endif /* !__local_ufromfpl_defined */
