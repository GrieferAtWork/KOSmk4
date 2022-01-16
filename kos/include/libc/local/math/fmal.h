/* HASH CRC-32:0x679dc64f */
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
#ifndef __local_fmal_defined
#define __local_fmal_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fmal) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fmal))(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z) {
	/* TODO: ieee754-specific function */
	return (__x * __y) + __z;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fmal_defined
#define __local___localdep_fmal_defined
#define __localdep_fmal __LIBC_LOCAL_NAME(fmal)
#endif /* !__local___localdep_fmal_defined */
#endif /* !__local_fmal_defined */
