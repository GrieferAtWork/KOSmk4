/* HASH CRC-32:0x8c1d8920 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_tcsetsid_defined
#define __local_tcsetsid_defined
#include <__crt.h>
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCSCTTY)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getsid_defined
#define __local___localdep_getsid_defined
#ifdef __CRT_HAVE_getsid
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_getsid,(__pid_t __pid),getsid,(__pid))
#elif defined(__CRT_HAVE___getsid)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_getsid,(__pid_t __pid),__getsid,(__pid))
#elif defined(__CRT_HAVE___libc_getsid)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_getsid,(__pid_t __pid),__libc_getsid,(__pid))
#else /* ... */
#undef __local___localdep_getsid_defined
#endif /* !... */
#endif /* !__local___localdep_getsid_defined */
#ifndef __local___localdep_ioctl_defined
#define __local___localdep_ioctl_defined
#ifdef __CRT_HAVE_ioctl
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___ioctl)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#else /* ... */
#undef __local___localdep_ioctl_defined
#endif /* !... */
#endif /* !__local___localdep_ioctl_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tcsetsid) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tcsetsid))(__fd_t __fd, __pid_t __pid) {
	int __result;
	if __unlikely(__pid != (__NAMESPACE_LOCAL_SYM __localdep_getsid)(0)) {
#ifdef __EINVAL
		__result = __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		__result = __libc_seterrno(1);
#endif /* !__EINVAL */
	} else {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__fd, __TIOCSCTTY, __NULLPTR);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tcsetsid_defined
#define __local___localdep_tcsetsid_defined
#define __localdep_tcsetsid __LIBC_LOCAL_NAME(tcsetsid)
#endif /* !__local___localdep_tcsetsid_defined */
#else /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCSCTTY */
#undef __local_tcsetsid_defined
#endif /* (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TIOCSCTTY */
#endif /* !__local_tcsetsid_defined */
