/* HASH CRC-32:0xa6f8c632 */
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
#ifndef __local_cfsetspeed_defined
#define __local_cfsetspeed_defined
#include <__crt.h>
#include <bits/os/termios.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cfsetispeed_defined
#define __local___localdep_cfsetispeed_defined
#ifdef __CRT_HAVE_cfsetispeed
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_cfsetispeed,(struct termios *__restrict __termios_p, __UINT32_TYPE__ __speed),cfsetispeed,(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetispeed */
__NAMESPACE_LOCAL_END
#include <libc/local/termios/cfsetispeed.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cfsetispeed __LIBC_LOCAL_NAME(cfsetispeed)
#endif /* !__CRT_HAVE_cfsetispeed */
#endif /* !__local___localdep_cfsetispeed_defined */
#ifndef __local___localdep_cfsetospeed_defined
#define __local___localdep_cfsetospeed_defined
#ifdef __CRT_HAVE_cfsetospeed
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_cfsetospeed,(struct termios *__restrict __termios_p, __UINT32_TYPE__ __speed),cfsetospeed,(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetospeed */
__NAMESPACE_LOCAL_END
#include <libc/local/termios/cfsetospeed.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cfsetospeed __LIBC_LOCAL_NAME(cfsetospeed)
#endif /* !__CRT_HAVE_cfsetospeed */
#endif /* !__local___localdep_cfsetospeed_defined */
__LOCAL_LIBC(cfsetspeed) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfsetspeed))(struct termios *__restrict __termios_p, __UINT32_TYPE__ __speed) {
	return (__NAMESPACE_LOCAL_SYM __localdep_cfsetispeed)(__termios_p, __speed) |
	       (__NAMESPACE_LOCAL_SYM __localdep_cfsetospeed)(__termios_p, __speed);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cfsetspeed_defined
#define __local___localdep_cfsetspeed_defined
#define __localdep_cfsetspeed __LIBC_LOCAL_NAME(cfsetspeed)
#endif /* !__local___localdep_cfsetspeed_defined */
#endif /* !__local_cfsetspeed_defined */
