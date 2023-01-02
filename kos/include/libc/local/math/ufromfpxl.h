/* HASH CRC-32:0xb425d0aa */
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
#ifndef __local_ufromfpxl_defined
#define __local_ufromfpxl_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ufromfpx
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ufromfpx_defined
#define __local___localdep_ufromfpx_defined
__CREDIRECT(__ATTR_WUNUSED,__UINTMAX_TYPE__,__NOTHROW_NCX,__localdep_ufromfpx,(double __x, int __round, unsigned int __width),ufromfpx,(__x,__round,__width))
#endif /* !__local___localdep_ufromfpx_defined */
__LOCAL_LIBC(ufromfpxl) __ATTR_WUNUSED __UINTMAX_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ufromfpxl))(__LONGDOUBLE __x, int __roundl, unsigned int __width) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ufromfpx)((double)__x, __roundl, __width);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ufromfpxl_defined
#define __local___localdep_ufromfpxl_defined
#define __localdep_ufromfpxl __LIBC_LOCAL_NAME(ufromfpxl)
#endif /* !__local___localdep_ufromfpxl_defined */
#else /* __CRT_HAVE_ufromfpx */
#undef __local_ufromfpxl_defined
#endif /* !__CRT_HAVE_ufromfpx */
#endif /* !__local_ufromfpxl_defined */
