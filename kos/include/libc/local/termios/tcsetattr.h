/* HASH CRC-32:0xa6f7ac5f */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_tcsetattr_defined
#define __local_tcsetattr_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_ioctl
#include <features.h>
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ioctl from sys.ioctl */
#ifndef __local___localdep_ioctl_defined
#define __local___localdep_ioctl_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> ioctl(2)
 * Perform the I/O control operation specified by `request' on `fd'.
 * Many I/O control operations except an additional argument, though
 * this argument's type and meaning depends on `REQUEST'. If used, it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_ioctl,(__fd_t __fd, __ULONGPTR_TYPE__ __request),ioctl,(__fd,__request),__request,1,(void *))
#endif /* !__local___localdep_ioctl_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/tty.h>
#include <asm/os/termios.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
__LOCAL_LIBC(tcsetattr) __ATTR_NONNULL((3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tcsetattr))(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p) {
	int __cmd;
	switch (__optional_actions) {

#if defined(__TCSANOW) && defined(__TCSETA)
	case __TCSANOW:
		__cmd = __TCSETA;
		break;
#endif /* __TCSANOW && __TCSETA */

#if defined(__TCSADRAIN) && defined(__TCSETAW)
	case __TCSADRAIN:
		__cmd = __TCSETAW;
		break;
#endif /* __TCSADRAIN && __TCSETAW */

#if defined(__TCSAFLUSH) && defined(__TCSETAF)
	case __TCSAFLUSH:
		__cmd = __TCSETAF;
		break;
#endif /* __TCSAFLUSH && __TCSETAF */

	default:
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	return (int)__localdep_ioctl(__fd, __cmd, __termios_p);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tcsetattr_defined
#define __local___localdep_tcsetattr_defined 1
#define __localdep_tcsetattr __LIBC_LOCAL_NAME(tcsetattr)
#endif /* !__local___localdep_tcsetattr_defined */
#else /* __CRT_HAVE_ioctl */
#undef __local_tcsetattr_defined
#endif /* !__CRT_HAVE_ioctl */
#endif /* !__local_tcsetattr_defined */
