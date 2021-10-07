/* HASH CRC-32:0xfb09f246 */
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
#ifndef __local__error_check_no_nesting_defined
#define __local__error_check_no_nesting_defined
#include <__crt.h>
#include <kos/bits/fastexcept.h>
#if defined(__CRT_HAVE_error_active) || defined(__CRT_HAVE_error_code) || defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__error_badusage_no_nesting_defined
#define __local___localdep__error_badusage_no_nesting_defined
#ifdef __CRT_HAVE__error_badusage_no_nesting
__CREDIRECT_VOID(__ATTR_COLD __ATTR_NORETURN,__NOTHROW,__localdep__error_badusage_no_nesting,(void),_error_badusage_no_nesting,())
#else /* __CRT_HAVE__error_badusage_no_nesting */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/_error_badusage_no_nesting.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__error_badusage_no_nesting __LIBC_LOCAL_NAME(_error_badusage_no_nesting)
#endif /* !__CRT_HAVE__error_badusage_no_nesting */
#endif /* !__local___localdep__error_badusage_no_nesting_defined */
#ifndef __local___localdep_error_active_defined
#define __local___localdep_error_active_defined
#ifdef __CRT_HAVE_error_active
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED,__BOOL,__NOTHROW,__LIBKCALL,__localdep_error_active,(void),error_active,())
#elif (defined(__CRT_HAVE_error_code) || defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data)) && (defined(__arch_error_active) || defined(__CRT_HAVE_error_code) || defined(__arch_error_code) || defined(__CRT_HAVE_error_data) || defined(__arch_error_data))
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/error_active.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_error_active __LIBC_LOCAL_NAME(error_active)
#else /* ... */
#undef __local___localdep_error_active_defined
#endif /* !... */
#endif /* !__local___localdep_error_active_defined */
__LOCAL_LIBC(_error_check_no_nesting) void
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(_error_check_no_nesting))(void) {
#ifdef __arch_error_active
	if (__arch_error_active())
#else /* __arch_error_active */
	if ((__NAMESPACE_LOCAL_SYM __localdep_error_active)())
#endif /* !__arch_error_active */
	{
		(__NAMESPACE_LOCAL_SYM __localdep__error_badusage_no_nesting)();
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__error_check_no_nesting_defined
#define __local___localdep__error_check_no_nesting_defined
#define __localdep__error_check_no_nesting __LIBC_LOCAL_NAME(_error_check_no_nesting)
#endif /* !__local___localdep__error_check_no_nesting_defined */
#else /* __CRT_HAVE_error_active || __CRT_HAVE_error_code || __arch_error_code || __CRT_HAVE_error_data || __arch_error_data */
#undef __local__error_check_no_nesting_defined
#endif /* !__CRT_HAVE_error_active && !__CRT_HAVE_error_code && !__arch_error_code && !__CRT_HAVE_error_data && !__arch_error_data */
#endif /* !__local__error_check_no_nesting_defined */
