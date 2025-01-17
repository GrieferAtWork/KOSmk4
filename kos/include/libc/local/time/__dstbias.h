/* HASH CRC-32:0x4261052 */
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
#ifndef __local___dstbias_defined
#define __local___dstbias_defined
#include <__crt.h>
#include <libc/template/dstbias.h>
#ifdef __LOCAL_dstbias
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__dstbias) __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED __LONG32_TYPE__ *
__NOTHROW(__LIBDCALL __LIBC_LOCAL_NAME(__dstbias))(void) {
	return &__LOCAL_dstbias;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___dstbias_defined
#define __local___localdep___dstbias_defined
#define __localdep___dstbias __LIBC_LOCAL_NAME(__dstbias)
#endif /* !__local___localdep___dstbias_defined */
#else /* __LOCAL_dstbias */
#undef __local___dstbias_defined
#endif /* !__LOCAL_dstbias */
#endif /* !__local___dstbias_defined */
