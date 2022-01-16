/* HASH CRC-32:0x7e34f43c */
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
#ifndef __local_error_code_defined
#define __local_error_code_defined
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#if defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
#include <kos/bits/exception_data.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_error_data_defined
#define __local___localdep_error_data_defined
#ifdef __CRT_HAVE_error_data
__NAMESPACE_LOCAL_END
struct exception_data;
__NAMESPACE_LOCAL_BEGIN
__COMPILER_REDIRECT(__LIBC,__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,struct exception_data *,__NOTHROW,__LIBKCALL,__localdep_error_data,(void),error_data,())
#elif defined(__arch_error_data)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/error_data.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_error_data __LIBC_LOCAL_NAME(error_data)
#else /* ... */
#undef __local___localdep_error_data_defined
#endif /* !... */
#endif /* !__local___localdep_error_data_defined */
__LOCAL_LIBC(error_code) __ATTR_PURE __ATTR_WUNUSED __error_code_t
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(error_code))(void) {
#ifdef __arch_error_code
	return __arch_error_code();
#else /* __arch_error_code */
	return (__NAMESPACE_LOCAL_SYM __localdep_error_data)()->e_code;
#endif /* !__arch_error_code */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_error_code_defined
#define __local___localdep_error_code_defined
#define __localdep_error_code __LIBC_LOCAL_NAME(error_code)
#endif /* !__local___localdep_error_code_defined */
#else /* __arch_error_code || __CRT_HAVE_error_data || __arch_error_data */
#undef __local_error_code_defined
#endif /* !__arch_error_code && !__CRT_HAVE_error_data && !__arch_error_data */
#endif /* !__local_error_code_defined */
