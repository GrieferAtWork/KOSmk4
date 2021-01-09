/* HASH CRC-32:0x54322a4c */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_error_data_defined
#define __local_error_data_defined 1
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#ifdef __arch_error_data
struct exception_data;
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(error_data) __ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED struct exception_data *
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(error_data))(void) {
	return __arch_error_data();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_error_data_defined
#define __local___localdep_error_data_defined 1
#define __localdep_error_data __LIBC_LOCAL_NAME(error_data)
#endif /* !__local___localdep_error_data_defined */
#else /* __arch_error_data */
#undef __local_error_data_defined
#endif /* !__arch_error_data */
#endif /* !__local_error_data_defined */
