/* HASH CRC-32:0x76131899 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_syslog_defined
#define __local_syslog_defined
#include <__crt.h>
#if defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vsyslog_defined
#define __local___localdep_vsyslog_defined
#ifdef __CRT_HAVE_vsyslog
__CREDIRECT_VOID(__ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 0),__NOTHROW_RPC,__localdep_vsyslog,(__STDC_INT_AS_UINT_T __level, char const *__format, __builtin_va_list __args),vsyslog,(__level,__format,__args))
#elif defined(__CRT_HAVE_syslog_printer)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.syslog/vsyslog.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsyslog __LIBC_LOCAL_NAME(vsyslog)
#else /* ... */
#undef __local___localdep_vsyslog_defined
#endif /* !... */
#endif /* !__local___localdep_vsyslog_defined */
__LOCAL_LIBC(syslog) __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) void
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(syslog))(__STDC_INT_AS_UINT_T __level, char const *__format, ...) {
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	(__NAMESPACE_LOCAL_SYM __localdep_vsyslog)(__level, __format, __args);
	__builtin_va_end(__args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_syslog_defined
#define __local___localdep_syslog_defined
#define __localdep_syslog __LIBC_LOCAL_NAME(syslog)
#endif /* !__local___localdep_syslog_defined */
#else /* __CRT_HAVE_vsyslog || __CRT_HAVE_syslog_printer */
#undef __local_syslog_defined
#endif /* !__CRT_HAVE_vsyslog && !__CRT_HAVE_syslog_printer */
#endif /* !__local_syslog_defined */
