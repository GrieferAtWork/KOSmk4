/* HASH CRC-32:0xcca2c610 */
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
#ifndef __local_tcgetattr_defined
#define __local_tcgetattr_defined 1
#include <__crt.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_ioctl) && defined(__TCGETA)
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
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
/* >> tcgetattr(3)
 * Get terminal attributes */
__LOCAL_LIBC(tcgetattr) __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tcgetattr))(__fd_t __fd, struct termios *__restrict __termios_p) {
	return (int)__localdep_ioctl(__fd, __TCGETA, __termios_p);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tcgetattr_defined
#define __local___localdep_tcgetattr_defined 1
#define __localdep_tcgetattr __LIBC_LOCAL_NAME(tcgetattr)
#endif /* !__local___localdep_tcgetattr_defined */
#else /* __CRT_HAVE_ioctl && __TCGETA */
#undef __local_tcgetattr_defined
#endif /* !__CRT_HAVE_ioctl || !__TCGETA */
#endif /* !__local_tcgetattr_defined */
