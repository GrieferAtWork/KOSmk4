/* HASH CRC-32:0xcb0fc7a2 */
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
#ifndef __local_cfgetispeed_defined
#define __local_cfgetispeed_defined
#include <__crt.h>
#include <bits/os/termios.h>
#include <bits/types.h>
#include <asm/os/termios.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cfgetispeed) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cfgetispeed))(struct termios const *__restrict __termios_p) {
#if defined(__IBAUD0) && defined(__CBAUD)
	return (__termios_p->c_iflag & __IBAUD0) ? 0 : (__termios_p->c_cflag & __CBAUD);
#elif defined(_HAVE_STRUCT_TERMIOS_C_ISPEED)
	return __termios_p->c_ispeed;
#else /* ... */
	(void)__termios_p;
	__COMPILER_IMPURE();
	return 0;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cfgetispeed_defined
#define __local___localdep_cfgetispeed_defined
#define __localdep_cfgetispeed __LIBC_LOCAL_NAME(cfgetispeed)
#endif /* !__local___localdep_cfgetispeed_defined */
#endif /* !__local_cfgetispeed_defined */
