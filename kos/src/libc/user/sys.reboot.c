/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_REBOOT_C
#define GUARD_LIBC_USER_SYS_REBOOT_C 1

#include "../api.h"
/**/

#include "../libc/syscalls.h"
#include "sys.reboot.h"

DECL_BEGIN

/*[[[head:libc_reboot,hash:CRC-32=0x7a5a0c26]]]*/
/* Reboot or halt the system
 * @param: howto: One of the `RB_*' constants above */
INTERN ATTR_SECTION(".text.crt.system.reboot") int
NOTHROW_NCX(LIBCCALL libc_reboot)(__STDC_INT_AS_UINT_T howto)
/*[[[body:libc_reboot]]]*/
{
	errno_t error;
	error = sys_reboot((syscall_ulong_t)(unsigned int)howto);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_reboot]]]*/





/*[[[start:exports,hash:CRC-32=0x160a2a8c]]]*/
DEFINE_PUBLIC_ALIAS(__reboot, libc_reboot);
DEFINE_PUBLIC_ALIAS(__libc_reboot, libc_reboot);
DEFINE_PUBLIC_ALIAS(reboot, libc_reboot);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_REBOOT_C */
