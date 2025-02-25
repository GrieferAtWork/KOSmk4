/* HASH CRC-32:0xeb1c8c19 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_cfsetospeed_defined
#define __local_cfsetospeed_defined
#include <__crt.h>
#include <bits/os/termios.h>
#include <bits/types.h>
#include <asm/os/termios.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cfsetospeed) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfsetospeed))(struct termios *__restrict __termios_p, __UINT32_TYPE__ __speed) {
#ifdef __CBAUD
	if __unlikely(__speed & ~__CBAUD) {
#ifdef __EINVAL
		return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
		return __libc_seterrno(1);
#endif /* !__EINVAL */
	}
	__termios_p->c_cflag &= ~__CBAUD;
	__termios_p->c_cflag |= __speed;
#endif /* __CBAUD */

	/* If present, store in the dedicated ospeed field. */
#ifdef _HAVE_STRUCT_TERMIOS_C_OSPEED
	__termios_p->c_ospeed = __speed;
#endif /* _HAVE_STRUCT_TERMIOS_C_OSPEED */
	(void)__termios_p;
	(void)__speed;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cfsetospeed_defined
#define __local___localdep_cfsetospeed_defined
#define __localdep_cfsetospeed __LIBC_LOCAL_NAME(cfsetospeed)
#endif /* !__local___localdep_cfsetospeed_defined */
#endif /* !__local_cfsetospeed_defined */
