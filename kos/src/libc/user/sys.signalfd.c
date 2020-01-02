/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_LIBC_USER_SYS_SIGNALFD_C
#define GUARD_LIBC_USER_SYS_SIGNALFD_C 1

#include "../api.h"
#include "sys.signalfd.h"

#include <kos/syscalls.h>

DECL_BEGIN

/*[[[start:implementation]]]*/

/*[[[head:signalfd,hash:CRC-32=0x71241a1b]]]*/
/* Request notification for delivery of signals in MASK to be performed using descriptor FD */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signalfd.signalfd") fd_t
NOTHROW_NCX(LIBCCALL libc_signalfd)(fd_t fd,
                                    sigset_t const *mask,
                                    int flags)
/*[[[body:signalfd]]]*/
{
	fd_t result;
	result = sys_signalfd4(fd, mask, sizeof(sigset_t),
	                       (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:signalfd]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x17d058d5]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(signalfd, libc_signalfd);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SIGNALFD_C */
