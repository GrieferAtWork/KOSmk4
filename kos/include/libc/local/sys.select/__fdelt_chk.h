/* HASH CRC-32:0x9ec83001 */
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
#ifndef __local___fdelt_chk_defined
#define __local___fdelt_chk_defined
#include <__crt.h>
#include <bits/types.h>
#include <asm/os/fd_set.h>
#include <bits/os/fd_set.h>
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__fdelt_chk) __ATTR_CONST __ATTR_WUNUSED __LONGPTR_TYPE__
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__fdelt_chk))(__LONGPTR_TYPE__ __fd) {
	__hybrid_assertf(__fd >= 0 && __fd < __FD_SETSIZE,
	                 "fd %ld cannot be used with `fd_set'",
	                 (long int)__fd);
	return __fd / __NFDBITS;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___fdelt_chk_defined
#define __local___localdep___fdelt_chk_defined
#define __localdep___fdelt_chk __LIBC_LOCAL_NAME(__fdelt_chk)
#endif /* !__local___localdep___fdelt_chk_defined */
#endif /* !__local___fdelt_chk_defined */
