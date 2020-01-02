/* HASH CRC-32:0x90ec626d */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_syslog_defined
#if defined(__CRT_HAVE_syslog_printer) || defined(__CRT_HAVE_vsyslog)
#define __local_syslog_defined 1
/* Dependency: "vsyslog" from "sys.syslog" */
#ifndef ____localdep_vsyslog_defined
#define ____localdep_vsyslog_defined 1
#ifdef __CRT_HAVE_vsyslog
__CREDIRECT_VOID(__ATTR_NONNULL((2)) __ATTR_LIBC_PRINTF(2,0),__NOTHROW_RPC,__localdep_vsyslog,(int __level, char const *__format, __builtin_va_list __args),vsyslog,(__level,__format,__args))
#elif defined(__CRT_HAVE_syslog_printer)
#include <local/sys.syslog/vsyslog.h>
#define __localdep_vsyslog (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vsyslog))
#else /* CUSTOM: vsyslog */
#undef ____localdep_vsyslog_defined
#endif /* vsyslog... */
#endif /* !____localdep_vsyslog_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(syslog) __ATTR_NONNULL((2)) __ATTR_LIBC_PRINTF(2,3) void
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(syslog))(int __level,
                                                     char const *__format,
                                                     ...) {
#line 144 "kos/src/libc/magic/sys.syslog.c"
	__builtin_va_list __args;
	__builtin_va_start(__args,__format);
	__localdep_vsyslog(__level,__format,__args);
	__builtin_va_end(__args);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_syslog_printer || __CRT_HAVE_vsyslog */
#endif /* !__local_syslog_defined */
