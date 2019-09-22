/* HASH CRC-32:0x4fc1b833 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ntohl_defined
#define __local_ntohl_defined 1
#include <hybrid/__byteswap.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ntohl) __ATTR_CONST __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ntohl))(__UINT32_TYPE__ __netlong) {
#line 290 "kos/src/libc/magic/netinet.in.c"
	return (__UINT32_TYPE__)__hybrid_beswap32(__netlong);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ntohl_defined */
