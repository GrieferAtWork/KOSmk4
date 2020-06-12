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
#ifndef GUARD_LIBC_USER_SYS_EVENTFD_C
#define GUARD_LIBC_USER_SYS_EVENTFD_C 1

#include "../api.h"
#include "sys.eventfd.h"
#include "unistd.h"

#include <parts/errno.h>
#include <kos/syscalls.h>


DECL_BEGIN

/*[[[start:implementation]]]*/

/*[[[head:libc_eventfd,hash:CRC-32=0xd8b0888d]]]*/
/* Return file descriptor for generic event channel. Set initial value to COUNT */
INTERN ATTR_SECTION(".text.crt.sched.eventfd") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_eventfd)(__STDC_UINT_AS_SIZE_T count,
                                   __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_eventfd]]]*/
{
	fd_t result;
	result = sys_eventfd2((syscall_ulong_t)count,
	                      (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_eventfd]]]*/

/*[[[head:libc_eventfd_read,hash:CRC-32=0xc626fdce]]]*/
/* Read event counter and possibly wait for events */
INTERN ATTR_SECTION(".text.crt.sched.eventfd") int
NOTHROW_RPC(LIBCCALL libc_eventfd_read)(fd_t fd,
                                        eventfd_t *value)
/*[[[body:libc_eventfd_read]]]*/
/*AUTO*/{
	ssize_t error;
	error = read(fd, value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
#ifdef EINVAL
	if (error >= 0)
		__libc_seterrno(EINVAL);
#endif /* EINVAL */
	return -1;
}
/*[[[end:libc_eventfd_read]]]*/

/*[[[head:libc_eventfd_write,hash:CRC-32=0x4590dd0c]]]*/
/* Increment event counter */
INTERN ATTR_SECTION(".text.crt.sched.eventfd") int
NOTHROW_RPC(LIBCCALL libc_eventfd_write)(fd_t fd,
                                         eventfd_t value)
/*[[[body:libc_eventfd_write]]]*/
/*AUTO*/{
	ssize_t error;
	error = write(fd, &value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
#ifdef EINVAL
	if (error >= 0)
		__libc_seterrno(EINVAL);
#endif /* EINVAL */
	return -1;
}
/*[[[end:libc_eventfd_write]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4fd87928]]]*/
DEFINE_PUBLIC_ALIAS(eventfd, libc_eventfd);
DEFINE_PUBLIC_ALIAS(eventfd_read, libc_eventfd_read);
DEFINE_PUBLIC_ALIAS(eventfd_write, libc_eventfd_write);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_EVENTFD_C */
