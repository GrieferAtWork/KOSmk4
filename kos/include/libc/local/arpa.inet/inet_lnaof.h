/* HASH CRC-32:0xdfc597a */
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
#ifndef __local_inet_lnaof_defined
#define __local_inet_lnaof_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <netinet/bits/in.h>
#include <netinet/in.h>
#include <hybrid/__byteswap.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(inet_lnaof) __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_lnaof))(struct in_addr __inaddr) {
	__UINT32_TYPE__ __addr = __hybrid_betoh32(__inaddr.s_addr);
	if (IN_CLASSA(__addr)) {
		return __addr & IN_CLASSA_HOST;
	} else if (IN_CLASSB(__addr)) {
		return __addr & IN_CLASSB_HOST;
	} else {
		return __addr & IN_CLASSC_HOST;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_inet_lnaof_defined
#define __local___localdep_inet_lnaof_defined
#define __localdep_inet_lnaof __LIBC_LOCAL_NAME(inet_lnaof)
#endif /* !__local___localdep_inet_lnaof_defined */
#endif /* !__local_inet_lnaof_defined */
