/* HASH CRC-32:0x8a30a4e3 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_cimagl_defined
#define __local_cimagl_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cimagl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(cimagl))(long double _Complex __z) {
	union {
		long double _Complex __x;
		__LONGDOUBLE __parts[2];
	} __v;
	__v.__x = __z;
	return __v.__parts[1];
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cimagl_defined
#define __local___localdep_cimagl_defined
#define __localdep_cimagl __LIBC_LOCAL_NAME(cimagl)
#endif /* !__local___localdep_cimagl_defined */
#endif /* !__local_cimagl_defined */
