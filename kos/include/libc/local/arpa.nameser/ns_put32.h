/* HASH CRC-32:0x8b123e9d */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ns_put32_defined
#define __local_ns_put32_defined
#include <__crt.h>
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ns_put32) __ATTR_OUT(2) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ns_put32))(unsigned long __val, unsigned char *__destptr) {
	__hybrid_unaligned_setbe32(__destptr, __val);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ns_put32_defined
#define __local___localdep_ns_put32_defined
#define __localdep_ns_put32 __LIBC_LOCAL_NAME(ns_put32)
#endif /* !__local___localdep_ns_put32_defined */
#endif /* !__local_ns_put32_defined */
