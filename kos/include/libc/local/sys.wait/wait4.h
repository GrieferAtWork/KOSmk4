/* HASH CRC-32:0xf40488d2 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wait4_defined
#define __local_wait4_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_wait4_64) || defined(__CRT_HAVE___wait4_time64) || defined(__CRT_HAVE_wait4) || defined(__CRT_HAVE___wait4) || defined(__CRT_HAVE___libc_wait4)
struct rusage;
#include <features.h>
#include <bits/os/rusage.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wait4_32_defined
#define __local___localdep_wait4_32_defined
#ifdef __CRT_HAVE_wait4
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,__localdep_wait4_32,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage32 *__usage),wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait4)
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,__localdep_wait4_32,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage32 *__usage),__wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___libc_wait4)
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_RPC,__localdep_wait4_32,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage32 *__usage),__libc_wait4,(__pid,__stat_loc,__options,__usage))
#else /* ... */
#undef __local___localdep_wait4_32_defined
#endif /* !... */
#endif /* !__local___localdep_wait4_32_defined */
#ifndef __local___localdep_wait4_64_defined
#define __local___localdep_wait4_64_defined
#if defined(__CRT_HAVE_wait4) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
struct __rusage64;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,__localdep_wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage64 *__usage),wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait4) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
struct __rusage64;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,__localdep_wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage64 *__usage),__wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___libc_wait4) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
struct __rusage64;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,__localdep_wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage64 *__usage),__libc_wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4_64)
__NAMESPACE_LOCAL_END
struct __rusage64;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,__localdep_wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage64 *__usage),wait4_64,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE___wait4_time64)
__NAMESPACE_LOCAL_END
struct __rusage64;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(4),__pid_t,__NOTHROW_NCX,__localdep_wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct __rusage64 *__usage),__wait4_time64,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4) || defined(__CRT_HAVE___wait4) || defined(__CRT_HAVE___libc_wait4)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.wait/wait4_64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wait4_64 __LIBC_LOCAL_NAME(wait4_64)
#else /* ... */
#undef __local___localdep_wait4_64_defined
#endif /* !... */
#endif /* !__local___localdep_wait4_64_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/rusage-convert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wait4) __ATTR_OUT_OPT(4) __pid_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wait4))(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options, struct rusage *__usage) {
	__pid_t __result;
#if defined(__CRT_HAVE_wait4) || defined(__CRT_HAVE___wait4) || defined(__CRT_HAVE___libc_wait4)
	struct __rusage32 __ru32;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_wait4_32)(__pid, __stat_loc, __options, __usage ? &__ru32 : __NULLPTR);
	if (__result >= 0 && __usage)
		rusage32_to_rusage(&__ru32, __usage);
#else /* __CRT_HAVE_wait4 || __CRT_HAVE___wait4 || __CRT_HAVE___libc_wait4 */
	struct __rusage64 __ru64;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_wait4_64)(__pid, __stat_loc, __options, __usage ? &__ru64 : __NULLPTR);
	if (__result >= 0 && __usage)
		rusage64_to_rusage(&__ru64, __usage);
#endif /* !__CRT_HAVE_wait4 && !__CRT_HAVE___wait4 && !__CRT_HAVE___libc_wait4 */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wait4_defined
#define __local___localdep_wait4_defined
#define __localdep_wait4 __LIBC_LOCAL_NAME(wait4)
#endif /* !__local___localdep_wait4_defined */
#else /* __CRT_HAVE_wait4_64 || __CRT_HAVE___wait4_time64 || __CRT_HAVE_wait4 || __CRT_HAVE___wait4 || __CRT_HAVE___libc_wait4 */
#undef __local_wait4_defined
#endif /* !__CRT_HAVE_wait4_64 && !__CRT_HAVE___wait4_time64 && !__CRT_HAVE_wait4 && !__CRT_HAVE___wait4 && !__CRT_HAVE___libc_wait4 */
#endif /* !__local_wait4_defined */
