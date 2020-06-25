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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_EPOLL_C
#define GUARD_LIBC_USER_SYS_EPOLL_C 1

#include "../api.h"
#include "sys.epoll.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_epoll_create,hash:CRC-32=0xd315b7af]]]*/
/* Creates an epoll instance.  Returns an fd for the new instance.
 * The "size" parameter is a hint specifying the number of file
 * descriptors to be associated with the new instance. The fd
 * returned by epoll_create() should be closed with close() */
INTERN ATTR_SECTION(".text.crt.io.poll") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_epoll_create)(__STDC_INT_AS_SIZE_T size)
/*[[[body:libc_epoll_create]]]*/
{
	fd_t result;
	result = sys_epoll_create((syscall_ulong_t)size);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_create]]]*/

/*[[[head:libc_epoll_create1,hash:CRC-32=0x482bd0b0]]]*/
/* Same as epoll_create but with an FLAGS parameter.
 * The unused SIZE parameter has been dropped
 * @param: flags: Set of `EPOLL_*' */
INTERN ATTR_SECTION(".text.crt.io.poll") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_epoll_create1)(__STDC_INT_AS_UINT_T flags)
/*[[[body:libc_epoll_create1]]]*/
{
	fd_t result;
	result = sys_epoll_create1((syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_create1]]]*/

/*[[[head:libc_epoll_ctl,hash:CRC-32=0x42d08fd0]]]*/
/* Manipulate an epoll instance "epfd". Returns 0 in case of success,
 * -1 in case of error (the "errno" variable will contain the
 * specific error code) The "op" parameter is one of the EPOLL_CTL_*
 * constants defined above. The "fd" parameter is the target of the
 * operation. The "event" parameter describes which events the caller
 * is interested in and any associated user data */
INTERN ATTR_SECTION(".text.crt.io.poll") int
NOTHROW_NCX(LIBCCALL libc_epoll_ctl)(fd_t epfd,
                                     __epoll_ctl_t op,
                                     fd_t fd,
                                     struct epoll_event *event)
/*[[[body:libc_epoll_ctl]]]*/
{
	fd_t result;
	result = sys_epoll_ctl(epfd, (syscall_ulong_t)op, fd, event);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_ctl]]]*/

/*[[[head:libc_epoll_wait,hash:CRC-32=0xc0d04753]]]*/
/* Wait for events on an epoll instance "epfd". Returns the number of
 * triggered events returned in "events" buffer. Or -1 in case of
 * error with the "errno" variable set to the specific error code. The
 * "events" parameter is a buffer that will contain triggered
 * events. The "maxevents" is the maximum number of events to be
 * returned (usually size of "events"). The "timeout" parameter
 * specifies the maximum wait time in milliseconds (-1 == infinite). */
INTERN ATTR_SECTION(".text.crt.io.poll") int
NOTHROW_RPC(LIBCCALL libc_epoll_wait)(fd_t epfd,
                                      struct epoll_event *events,
                                      __STDC_INT_AS_SIZE_T maxevents,
                                      int timeout)
/*[[[body:libc_epoll_wait]]]*/
{
	fd_t result;
	result = sys_epoll_wait(epfd,
	                        events,
	                        (syscall_ulong_t)maxevents,
	                        (syscall_slong_t)timeout);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_wait]]]*/

/*[[[head:libc_epoll_pwait,hash:CRC-32=0xb11db1c6]]]*/
/* Same as epoll_wait, but the thread's signal mask is temporarily
 * and atomically replaced with the one provided as parameter */
INTERN ATTR_SECTION(".text.crt.io.poll") int
NOTHROW_RPC(LIBCCALL libc_epoll_pwait)(fd_t epfd,
                                       struct epoll_event *events,
                                       __STDC_INT_AS_SIZE_T maxevents,
                                       int timeout,
                                       sigset_t const *ss)
/*[[[body:libc_epoll_pwait]]]*/
{
	fd_t result;
	result = sys_epoll_pwait(epfd,
	                         events,
	                         (syscall_ulong_t)maxevents,
	                         (syscall_slong_t)timeout,
	                         ss);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_epoll_pwait]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x69a39cda]]]*/
DEFINE_PUBLIC_ALIAS(epoll_create, libc_epoll_create);
DEFINE_PUBLIC_ALIAS(epoll_create1, libc_epoll_create1);
DEFINE_PUBLIC_ALIAS(epoll_ctl, libc_epoll_ctl);
DEFINE_PUBLIC_ALIAS(epoll_wait, libc_epoll_wait);
DEFINE_PUBLIC_ALIAS(epoll_pwait, libc_epoll_pwait);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_EPOLL_C */
