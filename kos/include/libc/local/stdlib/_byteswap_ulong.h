/* HASH CRC-32:0x913c7d4f */
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
#ifndef __local__byteswap_ulong_defined
#define __local__byteswap_ulong_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <hybrid/__byteswap.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_byteswap_ulong) __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(_byteswap_ulong))(__UINT32_TYPE__ __val) {
	return __hybrid_bswap32(__val);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__byteswap_ulong_defined
#define __local___localdep__byteswap_ulong_defined
#define __localdep__byteswap_ulong __LIBC_LOCAL_NAME(_byteswap_ulong)
#endif /* !__local___localdep__byteswap_ulong_defined */
#endif /* !__local__byteswap_ulong_defined */
