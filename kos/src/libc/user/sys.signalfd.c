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
#ifndef GUARD_LIBC_USER_SYS_SIGNALFD_C
#define GUARD_LIBC_USER_SYS_SIGNALFD_C 1

#include "../api.h"
/**/

#include "../libc/syscalls.h"
#include "sys.signalfd.h"

DECL_BEGIN

/*[[[head:libc_signalfd,hash:CRC-32=0x41eb2a02]]]*/
/* >> signalfd(2)
 * Create or update a poll(2)-able file descriptor which can be used to
 * wait for the delivery of signals masked by `sigmask' to the  waiting
 * thread/process.
 * @param: fd:    When `-1', create a new signalfd object; Otherwise,
 *                the FD number of  the signalfd object who's  signal
 *                mask should be updated to `sigmask'.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK'
 *                Meaningless,  but  still  validated  when  `fd != -1' */
INTERN ATTR_SECTION(".text.crt.sched.signalfd") WUNUSED ATTR_IN(2) fd_t
NOTHROW_NCX(LIBCCALL libc_signalfd)(fd_t fd,
                                    sigset_t const *sigmask,
                                    __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_signalfd]]]*/
{
	fd_t result;
	result = sys_signalfd4(fd, sigmask, sizeof(sigset_t),
	                       (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_signalfd]]]*/


/*[[[start:exports,hash:CRC-32=0x2ecaa63]]]*/
DEFINE_PUBLIC_ALIAS_P(signalfd,libc_signalfd,WUNUSED ATTR_IN(2),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, sigset_t const *sigmask, __STDC_INT_AS_UINT_T flags),(fd,sigmask,flags));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SIGNALFD_C */
