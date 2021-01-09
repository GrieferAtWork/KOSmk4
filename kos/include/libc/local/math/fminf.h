/* HASH CRC-32:0x5580ff1d */
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
#ifndef __local_fminf_defined
#define __local_fminf_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Return minimum numeric value from X and Y */
__LOCAL_LIBC(fminf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fminf))(float __x, float __y) {
	/* TODO: ieee754-specific function */
	return __x < __y ? __x : __y;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fminf_defined
#define __local___localdep_fminf_defined 1
#define __localdep_fminf __LIBC_LOCAL_NAME(fminf)
#endif /* !__local___localdep_fminf_defined */
#endif /* !__local_fminf_defined */
