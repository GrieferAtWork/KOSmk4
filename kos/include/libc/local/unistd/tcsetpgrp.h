/* HASH CRC-32:0x5aa145ec */
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
#ifndef __local_tcsetpgrp_defined
#define __local_tcsetpgrp_defined
#include <__crt.h>
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCSPGRP)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(tcsetpgrp) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tcsetpgrp))(__fd_t __fd, __pid_t __pgrp_id) {
	return (__NAMESPACE_LOCAL_SYM __localdep_ioctl)(__fd, __TIOCSPGRP, &__pgrp_id) < 0 ? -1 : 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tcsetpgrp_defined
#define __local___localdep_tcsetpgrp_defined
#define __localdep_tcsetpgrp __LIBC_LOCAL_NAME(tcsetpgrp)
#endif /* !__local___localdep_tcsetpgrp_defined */
#else /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCSPGRP */
#undef __local_tcsetpgrp_defined
#endif /* (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TIOCSPGRP */
#endif /* !__local_tcsetpgrp_defined */
