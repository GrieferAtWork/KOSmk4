/* HASH CRC-32:0x27707cd3 */
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
#ifndef __local_isatty_defined
#define __local_isatty_defined 1
#include <__crt.h>
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_tcgetattr) || (defined(__CRT_HAVE_ioctl) && defined(__TCGETA))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ioctl from sys.ioctl */
#if !defined(__local___localdep_ioctl_defined) && defined(__CRT_HAVE_ioctl)
#define __local___localdep_ioctl_defined 1
__NAMESPACE_LOCAL_END
#include <features.h>
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
#endif /* !__local___localdep_ioctl_defined && __CRT_HAVE_ioctl */
/* Dependency: tcgetattr from termios */
#ifndef __local___localdep_tcgetattr_defined
#define __local___localdep_tcgetattr_defined 1
#ifdef __CRT_HAVE_tcgetattr
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* >> tcgetattr(3)
 * Get terminal attributes */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,__localdep_tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),tcgetattr,(__fd,__termios_p))
#elif defined(__CRT_HAVE_ioctl) && defined(__TCGETA)
__NAMESPACE_LOCAL_END
#include <libc/local/termios/tcgetattr.h>
__NAMESPACE_LOCAL_BEGIN
/* >> tcgetattr(3)
 * Get terminal attributes */
#define __localdep_tcgetattr __LIBC_LOCAL_NAME(tcgetattr)
#else /* ... */
#undef __local___localdep_tcgetattr_defined
#endif /* !... */
#endif /* !__local___localdep_tcgetattr_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__LOCAL_LIBC(isatty) __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(isatty))(__fd_t __fd) {
	struct termios __ios;
#if defined(__CRT_HAVE_ioctl) && defined(__TCGETA)
	return __localdep_ioctl(__fd, __TCGETA, &__ios) < 0 ? 0 : 1;
#else /* __CRT_HAVE_ioctl && __TCGETA */
	return __localdep_tcgetattr(__fd, &__ios) != 0 ? 0 : 1;
#endif /* !__CRT_HAVE_ioctl || !__TCGETA */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_isatty_defined
#define __local___localdep_isatty_defined 1
#define __localdep_isatty __LIBC_LOCAL_NAME(isatty)
#endif /* !__local___localdep_isatty_defined */
#else /* __CRT_HAVE_tcgetattr || (__CRT_HAVE_ioctl && __TCGETA) */
#undef __local_isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && (!__CRT_HAVE_ioctl || !__TCGETA) */
#endif /* !__local_isatty_defined */
