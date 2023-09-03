/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_IOCTL_C
#define GUARD_LIBC_USER_SYS_IOCTL_C 1

#include "../api.h"
#include "sys.ioctl.h"

#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_ioctl,hash:CRC-32=0x660597ca]]]*/
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDARG(1) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(VLIBCCALL libc_ioctl)(fd_t fd,
                                  ioctl_t request,
                                  ...)
/*[[[body:libc_ioctl]]]*/
{
	ssize_t result;
	va_list args;
	va_start(args, request);
	result = sys_ioctl(fd,
	                   (syscall_ulong_t)request,
	                   va_arg(args, void *));
	va_end(args);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_ioctl]]]*/





/*[[[start:exports,hash:CRC-32=0xb0591502]]]*/
DEFINE_PUBLIC_ALIAS(__ioctl, libc_ioctl);
DEFINE_PUBLIC_ALIAS(__libc_ioctl, libc_ioctl);
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(__ioctl_time64, libc_ioctl);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
DEFINE_PUBLIC_ALIAS(ioctl, libc_ioctl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_IOCTL_C */
