/* HASH CRC-32:0xe3f2a315 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SYS_EVENTFD_C
#define GUARD_LIBC_AUTO_SYS_EVENTFD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.eventfd.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
/* >> eventfd_read(3)
 * Read the event counter, and (if not `O_NONBLOCK'), wait for an event to happen */
INTERN ATTR_SECTION(".text.crt.sched.eventfd") int
NOTHROW_RPC(LIBCCALL libc_eventfd_read)(fd_t fd,
                                        eventfd_t *value) {
	ssize_t error;
	error = libc_read(fd, value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;

	if (error >= 0)
		(void)libc_seterrno(EINVAL);

	return -1;
}
#include <libc/errno.h>
/* >> eventfd_write(3)
 * Increment the event counter */
INTERN ATTR_SECTION(".text.crt.sched.eventfd") int
NOTHROW_RPC(LIBCCALL libc_eventfd_write)(fd_t fd,
                                         eventfd_t value) {
	ssize_t error;
	error = libc_write(fd, &value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;

	if (error >= 0)
		(void)libc_seterrno(EINVAL);

	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(eventfd_read, libc_eventfd_read);
DEFINE_PUBLIC_ALIAS(eventfd_write, libc_eventfd_write);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_EVENTFD_C */
