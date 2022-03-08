/* HASH CRC-32:0xd22791c1 */
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
#ifndef __local_ns_get32_defined
#define __local_ns_get32_defined
#include <__crt.h>
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ns_get32) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ns_get32))(unsigned char const *__srcptr) {
	return __hybrid_unaligned_getbe32(__srcptr);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ns_get32_defined
#define __local___localdep_ns_get32_defined
#define __localdep_ns_get32 __LIBC_LOCAL_NAME(ns_get32)
#endif /* !__local___localdep_ns_get32_defined */
#endif /* !__local_ns_get32_defined */
