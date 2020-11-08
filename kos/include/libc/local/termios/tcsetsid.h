/* HASH CRC-32:0x292988e8 */
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
#ifndef __local_tcsetsid_defined
#define __local_tcsetsid_defined 1
#include <__crt.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_ioctl) && defined(__TIOCSCTTY)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getsid from unistd */
#if !defined(__local___localdep_getsid_defined) && defined(__CRT_HAVE_getsid)
#define __local___localdep_getsid_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_getsid,(__pid_t __pid),getsid,(__pid))
#endif /* !__local___localdep_getsid_defined && __CRT_HAVE_getsid */
/* Dependency: ioctl from sys.ioctl */
#ifndef __local___localdep_ioctl_defined
#define __local___localdep_ioctl_defined 1
__NAMESPACE_LOCAL_END
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Perform the I/O control operation specified by REQUEST on FD.
 * One argument may follow; its presence and type depend on REQUEST.
 * Return value depends on REQUEST. Usually -1 indicates error */
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ULONGPTR_TYPE__ __request),ioctl,(__fd,__request),__request,1,(void *))
#endif /* !__local___localdep_ioctl_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tcsetsid) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tcsetsid))(__fd_t __fd, __pid_t __pid) {
	int __result;
	if __unlikely(__pid != __localdep_getsid(0)) {
#ifdef __EINVAL
		__result = __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		__result = __libc_seterrno(1);
#endif /* !__EINVAL */
	} else {
		__result = __localdep_ioctl(__fd, __TIOCSCTTY, __NULLPTR);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tcsetsid_defined
#define __local___localdep_tcsetsid_defined 1
#define __localdep_tcsetsid __LIBC_LOCAL_NAME(tcsetsid)
#endif /* !__local___localdep_tcsetsid_defined */
#else /* __CRT_HAVE_ioctl && __TIOCSCTTY */
#undef __local_tcsetsid_defined
#endif /* !__CRT_HAVE_ioctl || !__TIOCSCTTY */
#endif /* !__local_tcsetsid_defined */
