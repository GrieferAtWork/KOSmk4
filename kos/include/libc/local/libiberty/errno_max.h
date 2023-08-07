/* HASH CRC-32:0xef3c5ddc */
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
#ifndef __local_errno_max_defined
#define __local_errno_max_defined
#include <__crt.h>
#include <asm/os/errno.h>
#ifdef __ECOUNT
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(errno_max) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(errno_max))(void) {
	return __ECOUNT - 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_errno_max_defined
#define __local___localdep_errno_max_defined
#define __localdep_errno_max __LIBC_LOCAL_NAME(errno_max)
#endif /* !__local___localdep_errno_max_defined */
#else /* __ECOUNT */
#undef __local_errno_max_defined
#endif /* !__ECOUNT */
#endif /* !__local_errno_max_defined */
