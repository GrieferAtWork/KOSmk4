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
#ifndef GUARD_LIBC_USER_SYS_POLL_C
#define GUARD_LIBC_USER_SYS_POLL_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <syscall.h>

#include "sys.poll.h"

DECL_BEGIN

/*[[[head:libc_poll,hash:CRC-32=0xf14d20a0]]]*/
/* @param timeout: Timeout in milliseconds (or negative for infinity) */
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_INOUTS(1, 2) int
NOTHROW_RPC(LIBCCALL libc_poll)(struct pollfd *fds,
                                nfds_t nfds,
                                int timeout)
/*[[[body:libc_poll]]]*/
{
	struct timespec64 tms;
	if (timeout < 0)
		return ppoll64(fds, nfds, NULL, NULL);
	tms.tv_sec  = (unsigned int)timeout / 1000;
	tms.tv_nsec = ((unsigned int)timeout % 1000) * (__NSEC_PER_SEC / 1000);
	return ppoll64(fds, nfds, &tms, NULL);
}
/*[[[end:libc_poll]]]*/

/*[[[head:libc_ppoll,hash:CRC-32=0x8e1b724b]]]*/
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) int
NOTHROW_RPC(LIBCCALL libc_ppoll)(struct pollfd *fds,
                                 nfds_t nfds,
                                 struct timespec const *timeout,
                                 sigset_t const *ss)
/*[[[body:libc_ppoll]]]*/
{
	syscall_slong_t result;
	result = sys_ppoll(fds, (size_t)nfds, timeout, ss, sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_ppoll]]]*/

/*[[[head:libc_ppoll64,hash:CRC-32=0xb5d237ba]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ppoll64, libc_ppoll);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.poll") ATTR_INOUTS(1, 2) ATTR_IN_OPT(3) ATTR_IN_OPT(4) int
NOTHROW_RPC(LIBCCALL libc_ppoll64)(struct pollfd *fds,
                                   nfds_t nfds,
                                   struct timespec64 const *timeout,
                                   sigset_t const *ss)
/*[[[body:libc_ppoll64]]]*/
{
	syscall_slong_t result;
#ifdef SYS_ppoll64
	result = sys_ppoll64(fds, (size_t)nfds, timeout, ss, sizeof(sigset_t));
#elif defined(SYS_ppoll_time64)
	result = sys_ppoll_time64(fds, (size_t)nfds, timeout, ss, sizeof(sigset_t));
#else /* ... */
#error "No way to implement `ppoll64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_ppoll64]]]*/





/*[[[start:exports,hash:CRC-32=0xc439b09b]]]*/
DEFINE_PUBLIC_ALIAS(__poll, libc_poll);
DEFINE_PUBLIC_ALIAS(poll, libc_poll);
DEFINE_PUBLIC_ALIAS(ppoll, libc_ppoll);
DEFINE_PUBLIC_ALIAS(ppoll64, libc_ppoll64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_POLL_C */
