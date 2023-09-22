/* HASH CRC-32:0x19d840a9 */
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
#ifndef __local__initterm_e_defined
#define __local__initterm_e_defined
#include <__crt.h>
#include <bits/crt/dos/corecrt_startup.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_syslog_defined
#define __local___localdep_syslog_defined
#ifdef __CRT_HAVE_syslog
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) void __NOTHROW_RPC(__VLIBCCALL __localdep_syslog)(__STDC_INT_AS_UINT_T __level, char const *__format, ...) __CASMNAME("syslog");
#elif defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.syslog/syslog.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_syslog __LIBC_LOCAL_NAME(syslog)
#else /* ... */
#undef __local___localdep_syslog_defined
#endif /* !... */
#endif /* !__local___localdep_syslog_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/syslog.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_initterm_e) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_initterm_e))(_onexit_t *__start, _onexit_t *__end) {
	int __result = 0;
	for (; __start < __end; ++__start) {
		if (!*__start)
			continue;
#if defined(__CRT_HAVE_syslog) || defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer)
		(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog)(__LOG_DEBUG, "[libd] _initterm_e: call %p\n", *__start);
#endif /* __CRT_HAVE_syslog || __CRT_HAVE_vsyslog || __CRT_HAVE_syslog_printer */
		__result = (**__start)();
		if (__result != 0) {
#if defined(__CRT_HAVE_syslog) || defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer)
			(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog)(__LOG_DEBUG, "[libd] _initterm_e: call %p failed -> %d\n", *__start, __result);
#endif /* __CRT_HAVE_syslog || __CRT_HAVE_vsyslog || __CRT_HAVE_syslog_printer */
			break;
		}
	}
#if defined(__CRT_HAVE_syslog) || defined(__CRT_HAVE_vsyslog) || defined(__CRT_HAVE_syslog_printer)
	(void)(__NAMESPACE_LOCAL_SYM __localdep_syslog)(__LOG_DEBUG, "[libd] _initterm_e: done\n");
#endif /* __CRT_HAVE_syslog || __CRT_HAVE_vsyslog || __CRT_HAVE_syslog_printer */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__initterm_e_defined
#define __local___localdep__initterm_e_defined
#define __localdep__initterm_e __LIBC_LOCAL_NAME(_initterm_e)
#endif /* !__local___localdep__initterm_e_defined */
#endif /* !__local__initterm_e_defined */
