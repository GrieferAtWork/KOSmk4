/* HASH CRC-32:0x1c8fac0b */
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
#ifndef __local_error_subclass_defined
#define __local_error_subclass_defined 1
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#if defined(__arch_error_subclass) || defined(__CRT_HAVE_error_code) || defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
#include <kos/bits/exception_data.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: error_code from kos.except */
#ifndef __local___localdep_error_code_defined
#define __local___localdep_error_code_defined 1
#ifdef __CRT_HAVE_error_code
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED,__error_code_t,__NOTHROW,__LIBKCALL,__localdep_error_code,(void),error_code,())
#elif defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/error_code.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_error_code __LIBC_LOCAL_NAME(error_code)
#else /* ... */
#undef __local___localdep_error_code_defined
#endif /* !... */
#endif /* !__local___localdep_error_code_defined */
__NAMESPACE_LOCAL_END
#include <kos/except/codes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(error_subclass) __ATTR_PURE __ATTR_WUNUSED __error_subclass_t
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(error_subclass))(void) {
#ifdef __arch_error_subclass
	return __arch_error_subclass();
#else /* __arch_error_subclass */
	return ERROR_SUBCLASS(__localdep_error_code());
#endif /* !__arch_error_subclass */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_error_subclass_defined
#define __local___localdep_error_subclass_defined 1
#define __localdep_error_subclass __LIBC_LOCAL_NAME(error_subclass)
#endif /* !__local___localdep_error_subclass_defined */
#else /* __arch_error_subclass || __CRT_HAVE_error_code || __arch_error_code || __CRT_HAVE_error_data || __arch_error_data */
#undef __local_error_subclass_defined
#endif /* !__arch_error_subclass && !__CRT_HAVE_error_code && !__arch_error_code && !__CRT_HAVE_error_data && !__arch_error_data */
#endif /* !__local_error_subclass_defined */
