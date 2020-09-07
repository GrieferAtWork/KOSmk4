/* HASH CRC-32:0xb085bf3d */
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
#ifndef __local_cwait_defined
#define __local_cwait_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: waitpid from sys.wait */
#ifndef __local___localdep_waitpid_defined
#define __local___localdep_waitpid_defined 1
#ifdef __CRT_HAVE_waitpid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <features.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),waitpid,(__pid,__stat_loc,__options))
#elif defined(__CRT_HAVE___waitpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <features.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
/* >> waitpid(2)
 * Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),__waitpid,(__pid,__stat_loc,__options))
#else /* ... */
#undef __local___localdep_waitpid_defined
#endif /* !... */
#endif /* !__local___localdep_waitpid_defined */
__LOCAL_LIBC(cwait) __pid_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(cwait))(int *__tstat, __pid_t __pid, int __action) {
	/* This one's pretty simple, because it's literally just a waitpid() system call...
	 * (It even returns the same thing, that being the PID of the joined process...) */
	/* NOTE: Apparently, the `action' argument is completely ignored... */
	(void)__action;
	return __localdep_waitpid(__pid, __tstat, __WEXITED);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cwait_defined
#define __local___localdep_cwait_defined 1
#define __localdep_cwait __LIBC_LOCAL_NAME(cwait)
#endif /* !__local___localdep_cwait_defined */
#else /* __CRT_HAVE_waitpid || __CRT_HAVE___waitpid */
#undef __local_cwait_defined
#endif /* !__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid */
#endif /* !__local_cwait_defined */
