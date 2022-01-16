/* HASH CRC-32:0xac1a060e */
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
#ifndef __local_error_info_defined
#define __local_error_info_defined
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#ifdef __arch_error_info
struct exception_info;
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(error_info) __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_info *
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(error_info))(void) {
	return __arch_error_info();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_error_info_defined
#define __local___localdep_error_info_defined
#define __localdep_error_info __LIBC_LOCAL_NAME(error_info)
#endif /* !__local___localdep_error_info_defined */
#else /* __arch_error_info */
#undef __local_error_info_defined
#endif /* !__arch_error_info */
#endif /* !__local_error_info_defined */
