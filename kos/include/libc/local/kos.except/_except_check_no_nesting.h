/* HASH CRC-32:0x50f3fa60 */
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
#ifndef __local__except_check_no_nesting_defined
#define __local__except_check_no_nesting_defined
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#if defined(__CRT_HAVE_except_active) || defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__except_badusage_no_nesting_defined
#define __local___localdep__except_badusage_no_nesting_defined
#ifdef __CRT_HAVE__except_badusage_no_nesting
__CREDIRECT_VOID(__ATTR_COLD __ATTR_NORETURN,__NOTHROW,__localdep__except_badusage_no_nesting,(void),_except_badusage_no_nesting,())
#else /* __CRT_HAVE__except_badusage_no_nesting */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/_except_badusage_no_nesting.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__except_badusage_no_nesting __LIBC_LOCAL_NAME(_except_badusage_no_nesting)
#endif /* !__CRT_HAVE__except_badusage_no_nesting */
#endif /* !__local___localdep__except_badusage_no_nesting_defined */
#ifndef __local___localdep_except_active_defined
#define __local___localdep_except_active_defined
#ifdef __CRT_HAVE_except_active
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED,__BOOL,__NOTHROW,__LIBKCALL,__localdep_except_active,(void),except_active,())
#elif (defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data)) && (defined(__arch_except_active) || defined(__CRT_HAVE_except_code) || defined(__arch_except_code) || defined(__CRT_HAVE_except_data) || defined(__arch_except_data))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/except_active.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_except_active __LIBC_LOCAL_NAME(except_active)
#else /* ... */
#undef __local___localdep_except_active_defined
#endif /* !... */
#endif /* !__local___localdep_except_active_defined */
__LOCAL_LIBC(_except_check_no_nesting) void
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(_except_check_no_nesting))(void) {
#ifdef __arch_except_active
	if (__arch_except_active())
#else /* __arch_except_active */
	if ((__NAMESPACE_LOCAL_SYM __localdep_except_active)())
#endif /* !__arch_except_active */
	{
		(__NAMESPACE_LOCAL_SYM __localdep__except_badusage_no_nesting)();
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__except_check_no_nesting_defined
#define __local___localdep__except_check_no_nesting_defined
#define __localdep__except_check_no_nesting __LIBC_LOCAL_NAME(_except_check_no_nesting)
#endif /* !__local___localdep__except_check_no_nesting_defined */
#else /* __CRT_HAVE_except_active || __CRT_HAVE_except_code || __arch_except_code || __CRT_HAVE_except_data || __arch_except_data */
#undef __local__except_check_no_nesting_defined
#endif /* !__CRT_HAVE_except_active && !__CRT_HAVE_except_code && !__arch_except_code && !__CRT_HAVE_except_data && !__arch_except_data */
#endif /* !__local__except_check_no_nesting_defined */
