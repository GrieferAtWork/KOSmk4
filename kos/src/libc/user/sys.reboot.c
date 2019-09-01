/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_REBOOT_C
#define GUARD_LIBC_USER_SYS_REBOOT_C 1

#include "../api.h"
#include "sys.reboot.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:reboot,hash:0xcceb6c97]]]*/
/* Reboot or halt the system
 * @param: howto: One of the `RB_*' constants above */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.reboot.reboot") int
NOTHROW_NCX(LIBCCALL libc_reboot)(int howto)
/*[[[body:reboot]]]*/
{
	errno_t error;
	error = sys_reboot((syscall_ulong_t)(unsigned int)howto);
	return libc_seterrno_syserr(error);
}
/*[[[end:reboot]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x7409680f]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(reboot, libc_reboot);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_REBOOT_C */
