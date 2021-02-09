/* HASH CRC-32:0x8dfb18ba */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_UTMP_C
#define GUARD_LIBC_AUTO_UTMP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/utmp.h"
#include "../user/sys.ioctl.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/tty.h>
#include <asm/os/stdio.h>
/* >> login_tty(3)
 * Set the given `fd' as the controlling terminal, stdin,
 * stdout, and stderr. Afterwards, `fd' is closed.
 * @return: 0 : Success
 * @return: * : Error */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_RPC_KOS(LIBCCALL libc_login_tty)(fd_t fd) {
	if unlikely(libc_setsid() < 0)
		goto err;
	if unlikely(libc_ioctl(fd, __TIOCSCTTY, 1) < 0)
		goto err;
#if STDIN_FILENO <= 2 && STDOUT_FILENO <= 2 && STDERR_FILENO <= 2
	{
		fd_t i;
		for (i = 0; i <= 2; ++i) {
			if likely(fd != i) {
				if unlikely(libc_dup2(fd, i))
					goto err;
			}
		}
	}
	if likely(fd >= 3)
		libc_close(fd);
#else /* STDIN_FILENO <= 2 && STDOUT_FILENO <= 2 && STDERR_FILENO <= 2 */
	if (likely(fd != STDIN_FILENO) && unlikely(libc_dup2(fd, STDIN_FILENO)))
		goto err;
	if (likely(fd != STDOUT_FILENO) && unlikely(libc_dup2(fd, STDOUT_FILENO)))
		goto err;
	if (likely(fd != STDERR_FILENO) && unlikely(libc_dup2(fd, STDERR_FILENO)))
		goto err;
	if likely(fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		libc_close(fd);
#endif /* STDIN_FILENO > 2 || STDOUT_FILENO > 2 || STDERR_FILENO > 2 */
	return 0;
err:
	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(login_tty, libc_login_tty);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UTMP_C */
