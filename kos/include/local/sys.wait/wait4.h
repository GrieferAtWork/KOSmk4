/* HASH CRC-32:0x666b0330 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wait4_defined
#if defined(__CRT_HAVE_wait4) || defined(__CRT_HAVE_wait4_64)
#define __local_wait4_defined 1
#include <bits/rusage-struct.h>
struct rusage;
/* Dependency: "wait4_32" from "sys.wait" */
#ifndef ____localdep_wait4_32_defined
#define ____localdep_wait4_32_defined 1
#ifdef __CRT_HAVE_wait4
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_wait4_32,(__pid_t __pid, __WAIT_STATUS __stat_loc, int __options, struct __rusage32 *__usage),wait4,(__pid,__stat_loc,__options,__usage))
#else /* LIBC: wait4 */
#undef ____localdep_wait4_32_defined
#endif /* wait4_32... */
#endif /* !____localdep_wait4_32_defined */

/* Dependency: "wait4_64" from "sys.wait" */
#ifndef ____localdep_wait4_64_defined
#define ____localdep_wait4_64_defined 1
#ifdef __CRT_HAVE_wait4_64
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, int __options, struct __rusage64 *__usage),wait4_64,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_wait4_64,(__pid_t __pid, __WAIT_STATUS __stat_loc, int __options, struct __rusage64 *__usage),wait4,(__pid,__stat_loc,__options,__usage))
#elif defined(__CRT_HAVE_wait4)
#include <local/sys.wait/wait4_64.h>
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __localdep_wait4_64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wait4_64))
#else /* CUSTOM: wait4_64 */
#undef ____localdep_wait4_64_defined
#endif /* wait4_64... */
#endif /* !____localdep_wait4_64_defined */

__NAMESPACE_LOCAL_BEGIN
#include <bits/rusage-struct.h>

#include <bits/rusage-convert.h>
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__LOCAL_LIBC(wait4) __pid_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wait4))(__pid_t __pid,
                                                   __WAIT_STATUS __stat_loc,
                                                   int __options,
                                                   struct rusage *__usage) {
#line 191 "kos/src/libc/magic/sys.wait.c"
	__pid_t __result;
#ifdef __CRT_HAVE_wait4
	struct __rusage32 __ru32;
	__result = __localdep_wait4_32(__pid, __stat_loc, __options, __usage ? &__ru32 : __NULLPTR);
	if (__result >= 0 && __usage)
		rusage32_to_rusage(&__ru32, __usage);
#else /* __CRT_HAVE_wait4 */
	struct __rusage64 __ru64;
	__result = __localdep_wait4_64(__pid, __stat_loc, __options, __usage ? &__ru64 : __NULLPTR);
	if (__result >= 0 && __usage)
		rusage64_to_rusage(&__ru64, __usage);
#endif /* !__CRT_HAVE_wait4 */
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_wait4 || __CRT_HAVE_wait4_64 */
#endif /* !__local_wait4_defined */
