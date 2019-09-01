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
#ifndef GUARD_LIBC_USER_SYS_POLL_C
#define GUARD_LIBC_USER_SYS_POLL_C 1

#include "../api.h"
#include "sys.poll.h"

#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:poll,hash:0x187fffc4]]]*/
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.poll") int
NOTHROW_RPC(LIBCCALL libc_poll)(struct pollfd *fds,
                                nfds_t nfds,
                                int timeout)
/*[[[body:poll]]]*/
{
	struct timespec64 tms;
	if (timeout < 0)
		return ppoll64(fds, nfds, NULL, NULL);
	tms.tv_sec  = (unsigned int)timeout / 1000;
	tms.tv_nsec = ((unsigned int)timeout % 1000) * (__NSECS_PER_SEC / 1000);
	return ppoll64(fds, nfds, &tms, NULL);
}
/*[[[end:poll]]]*/

/*[[[head:ppoll,hash:0x78ae9b1a]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.ppoll") int
NOTHROW_RPC(LIBCCALL libc_ppoll)(struct pollfd *fds,
                                 nfds_t nfds,
                                 struct timespec const *timeout,
                                 sigset_t const *ss)
/*[[[body:ppoll]]]*/
{
	syscall_slong_t result;
	result = sys_ppoll(fds, (size_t)nfds, timeout, ss, sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
/*[[[end:ppoll]]]*/

/*[[[head:ppoll64,hash:0x53e1c346]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ppoll64, libc_ppoll);
#else
INTERN NONNULL((1)) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.poll.ppoll64") int
NOTHROW_RPC(LIBCCALL libc_ppoll64)(struct pollfd *fds,
                                   nfds_t nfds,
                                   struct timespec64 const *timeout,
                                   sigset_t const *ss)
/*[[[body:ppoll64]]]*/
{
	syscall_slong_t result;
	result = sys_ppoll64(fds, (size_t)nfds, timeout, ss, sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:ppoll64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x36090ba7]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(poll, libc_poll);
DEFINE_PUBLIC_WEAK_ALIAS(ppoll, libc_ppoll);
DEFINE_PUBLIC_WEAK_ALIAS(ppoll64, libc_ppoll64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_POLL_C */
