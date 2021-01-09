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
#ifndef GUARD_LIBC_USER_SYS_IOCTL_C
#define GUARD_LIBC_USER_SYS_IOCTL_C 1

#include "../api.h"
#include "sys.ioctl.h"

#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/


/*[[[head:libc_ioctl,hash:CRC-32=0x7c152c2e]]]*/
/* Perform the I/O control operation specified by REQUEST on FD.
 * One argument may follow; its presence and type depend on REQUEST.
 * Return value depends on REQUEST. Usually -1 indicates error */
INTERN ATTR_SECTION(".text.crt.io.utility") __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(VLIBCCALL libc_ioctl)(fd_t fd,
                                  ulongptr_t request,
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

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xb0c64b0c]]]*/
DEFINE_PUBLIC_ALIAS(ioctl, libc_ioctl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_IOCTL_C */
