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
#ifndef GUARD_LIBC_USER_SYS_EVENTFD_C
#define GUARD_LIBC_USER_SYS_EVENTFD_C 1

#include "../api.h"
#include "sys.eventfd.h"
#include "unistd.h"

#include <parts/errno.h>
#include <kos/syscalls.h>


DECL_BEGIN

/*[[[start:implementation]]]*/

/*[[[head:eventfd,hash:CRC-32=0x317b29e1]]]*/
/* Return file descriptor for generic event channel. Set initial value to COUNT */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.sched.eventfd.eventfd") fd_t
NOTHROW_NCX(LIBCCALL libc_eventfd)(unsigned int count,
                                   int flags)
/*[[[body:eventfd]]]*/
{
	fd_t result;
	result = sys_eventfd2((syscall_ulong_t)count,
	                      (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:eventfd]]]*/

/*[[[head:eventfd_read,hash:CRC-32=0xcb08c7c7]]]*/
/* Read event counter and possibly wait for events */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.eventfd.eventfd_read") int
NOTHROW_RPC(LIBCCALL libc_eventfd_read)(fd_t fd,
                                        eventfd_t *value)
/*[[[body:eventfd_read]]]*/
/*AUTO*/{
	ssize_t error;
	error = libc_read(fd, value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
#ifdef __EINVAL
	if (error >= 0)
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
	return -1;
}
/*[[[end:eventfd_read]]]*/

/*[[[head:eventfd_write,hash:CRC-32=0xbce4c292]]]*/
/* Increment event counter */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.eventfd.eventfd_write") int
NOTHROW_RPC(LIBCCALL libc_eventfd_write)(fd_t fd,
                                         eventfd_t value)
/*[[[body:eventfd_write]]]*/
/*AUTO*/{
	ssize_t error;
	error = libc_write(fd, &value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
#ifdef __EINVAL
	if (error >= 0)
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
	return -1;
}
/*[[[end:eventfd_write]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x35c0103a]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(eventfd, libc_eventfd);
DEFINE_PUBLIC_WEAK_ALIAS(eventfd_read, libc_eventfd_read);
DEFINE_PUBLIC_WEAK_ALIAS(eventfd_write, libc_eventfd_write);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_EVENTFD_C */
