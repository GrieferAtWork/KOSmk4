/* HASH CRC-32:0xc7fc7b1c */
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
#ifndef __local_creal_defined
#define __local_creal_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(creal) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(creal))(double _Complex __z) {
	union {
		double _Complex __x;
		double __parts[2];
	} __v;
	__v.__x = __z;
	return __v.__parts[0];
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_creal_defined
#define __local___localdep_creal_defined
#define __localdep_creal __LIBC_LOCAL_NAME(creal)
#endif /* !__local___localdep_creal_defined */
#endif /* !__local_creal_defined */
