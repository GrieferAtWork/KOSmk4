/* HASH CRC-32:0x76213097 */
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
#ifndef __local_cfsetispeed_defined
#define __local_cfsetispeed_defined
#include <__crt.h>
#include <bits/os/termios.h>
#include <bits/types.h>
#include <asm/os/termios.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cfsetispeed) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfsetispeed))(struct termios *__restrict __termios_p, __UINT32_TYPE__ __speed) {
#if defined(__IBAUD0) && defined(__CBAUD)
	if __unlikely(__speed & ~__CBAUD) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	if (__speed == 0) {
		__termios_p->c_iflag |= __IBAUD0;
	} else {
		__termios_p->c_iflag &= ~__IBAUD0;
		__termios_p->c_cflag &= ~__CBAUD;
		__termios_p->c_cflag |= __speed;
	}
#elif defined(__CBAUD) && defined(__IBSHIFT)
	__UINT32_TYPE__ __used_speed;
	if __unlikely(__speed & ~__CBAUD) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	__used_speed = __speed;
	if (__speed == 0)
		__used_speed = __termios_p->c_cflag & __CBAUD;
	__termios_p->c_cflag &= ~(__CBAUD << __IBSHIFT);
	__termios_p->c_cflag |= __used_speed << __IBSHIFT;
#endif /* ... */

	/* If present, store in the dedicated ispeed field. */
#ifdef _HAVE_STRUCT_TERMIOS_C_ISPEED
	__termios_p->c_ispeed = __speed;
#endif /* _HAVE_STRUCT_TERMIOS_C_ISPEED */
	(void)__termios_p;
	(void)__speed;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cfsetispeed_defined
#define __local___localdep_cfsetispeed_defined
#define __localdep_cfsetispeed __LIBC_LOCAL_NAME(cfsetispeed)
#endif /* !__local___localdep_cfsetispeed_defined */
#endif /* !__local_cfsetispeed_defined */
