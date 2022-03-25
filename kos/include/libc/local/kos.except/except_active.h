/* HASH CRC-32:0x7fa48663 */
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
#ifndef __local_except_active_defined
#define __local_except_active_defined
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#if defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_except_code_defined
#define __local___localdep_except_code_defined
#ifdef __CRT_HAVE_except_code
__NAMESPACE_LOCAL_END
#include <kos/bits/exception_data.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED,__except_code_t,__NOTHROW,__LIBKCALL,__localdep_except_code,(void),except_code,())
#elif defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/except_code.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_except_code __LIBC_LOCAL_NAME(except_code)
#else /* ... */
#undef __local___localdep_except_code_defined
#endif /* !... */
#endif /* !__local___localdep_except_code_defined */
__NAMESPACE_LOCAL_END
#include <kos/except/codes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(except_active) __ATTR_PURE __ATTR_WUNUSED __BOOL
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(except_active))(void) {
#ifdef __arch_except_active
	return __arch_except_active();
#else /* __arch_except_active */
	return (__NAMESPACE_LOCAL_SYM __localdep_except_code)() != E_OK;
#endif /* !__arch_except_active */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_except_active_defined
#define __local___localdep_except_active_defined
#define __localdep_except_active __LIBC_LOCAL_NAME(except_active)
#endif /* !__local___localdep_except_active_defined */
#else /* __CRT_HAVE_except_code || __arch_except_code || __CRT_HAVE_except_data || __arch_except_data */
#undef __local_except_active_defined
#endif /* !__CRT_HAVE_except_code && !__arch_except_code && !__CRT_HAVE_except_data && !__arch_except_data */
#endif /* !__local_except_active_defined */
