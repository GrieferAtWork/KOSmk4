/* HASH CRC-32:0xb96bc535 */
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
#ifndef __local_memfrob_defined
#define __local_memfrob_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memfrob(3)
 * Xor every byte in `buf...+=num_bytes' with decimal `42' (yeah...)
 * Always re-return the given `buf' */
__LOCAL_LIBC(memfrob) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memfrob))(void *__buf, __SIZE_TYPE__ __num_bytes) {
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__buf;
	while (__num_bytes--)
		*__iter++ ^= 42; /* -_-   yeah... */
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memfrob_defined
#define __local___localdep_memfrob_defined 1
#define __localdep_memfrob __LIBC_LOCAL_NAME(memfrob)
#endif /* !__local___localdep_memfrob_defined */
#endif /* !__local_memfrob_defined */
