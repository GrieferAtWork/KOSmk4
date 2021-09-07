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
#ifndef GUARD_LIBC_USER_KOS_HOP_API_C
#define GUARD_LIBC_USER_KOS_HOP_API_C 1

#include "../api.h"
/**/

#include "kos.hop.api.h"
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_hop,hash:CRC-32=0xadf62b1e]]]*/
/* Perform a handle operation specified by `cmd'
 * @param: cmd: One of `HOP_<type>_<command>' */
INTERN ATTR_SECTION(".text.crt.kos.syscalls") syscall_slong_t
NOTHROW_NCX(VLIBCCALL libc_hop)(fd_t fd,
                                syscall_ulong_t cmd,
                                ...)
/*[[[body:libc_hop]]]*/
{
	syscall_slong_t result;
	va_list args;
	va_start(args, cmd);
	result = sys_hop(fd, cmd, va_arg(args, void *));
	va_end(args);
	if (E_ISERR(result))
		result = libc_seterrno((errno_t)-result);
	return result;
}
/*[[[end:libc_hop]]]*/

/*[[[head:libc_hopf,hash:CRC-32=0xd730ae8e]]]*/
/* Perform a handle operation specified by `cmd'
 * @param: cmd: One of `HOP_<type>_<command>' */
INTERN ATTR_SECTION(".text.crt.kos.syscalls") syscall_slong_t
NOTHROW_NCX(VLIBCCALL libc_hopf)(fd_t fd,
                                 syscall_ulong_t cmd,
                                 iomode_t mode,
                                 ...)
/*[[[body:libc_hopf]]]*/
{
	syscall_slong_t result;
	va_list args;
	va_start(args, mode);
	result = sys_hopf(fd, cmd, mode, va_arg(args, void *));
	va_end(args);
	if (E_ISERR(result))
		result = libc_seterrno((errno_t)-result);
	return result;
}
/*[[[end:libc_hopf]]]*/


/* These are provided as syscall amendments */
/*[[[skip:libc_Hop]]]*/
/*[[[skip:libc_Hopf]]]*/



/*[[[start:exports,hash:CRC-32=0xc71fbf47]]]*/
DEFINE_PUBLIC_ALIAS(hop, libc_hop);
DEFINE_PUBLIC_ALIAS(hopf, libc_hopf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_HOP_API_C */
