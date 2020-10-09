/* HASH CRC-32:0x4eddc852 */
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
#ifndef __local_killpg_defined
#define __local_killpg_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_kill
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: kill from signal */
#ifndef __local___localdep_kill_defined
#define __local___localdep_kill_defined 1
/* >> kill(2)
 * Raise a signal `signo' within the process(es) specified by `pid':
 *   - pid > 0:   Deliver `signo' to a process who's PID matches `pid'.
 *   - pid == 0:  Deliver `signo' to every process within the caller's process group.
 *   - pid == -1: Deliver `signo' to every process the caller has permission to send
 *                signals to, with the exception of a process with pid=1 (i.e. `/bin/init')
 *   - pid < -1:  Deliver `signo' to every process within the process group `-pid'
 * @param: signo: The signal number to deliver. When set to `0', no signal is delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_kill,(__pid_t __pid, __signo_t __signo),kill,(__pid,__signo))
#endif /* !__local___localdep_kill_defined */
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
 * @return: -1:   [errno=ESRCH]  No process group is identified by `pgrp' */
__LOCAL_LIBC(killpg) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(killpg))(__pid_t __pgrp, __signo_t __signo) {
	return __localdep_kill(-__pgrp, __signo);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_killpg_defined
#define __local___localdep_killpg_defined 1
#define __localdep_killpg __LIBC_LOCAL_NAME(killpg)
#endif /* !__local___localdep_killpg_defined */
#else /* __CRT_HAVE_kill */
#undef __local_killpg_defined
#endif /* !__CRT_HAVE_kill */
#endif /* !__local_killpg_defined */
