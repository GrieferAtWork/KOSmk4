/* HASH CRC-32:0x537c8b52 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_htons_defined
#define __local_htons_defined 1
#include <__crt.h>
#include <hybrid/__byteswap.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(htons) __ATTR_CONST __UINT16_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(htons))(__UINT16_TYPE__ __hostword) {
	return (__UINT16_TYPE__)__hybrid_htobe32(__hostword);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_htons_defined
#define __local___localdep_htons_defined 1
#define __localdep_htons __LIBC_LOCAL_NAME(htons)
#endif /* !__local___localdep_htons_defined */
#endif /* !__local_htons_defined */
