/* HASH CRC-32:0xc1f94f71 */
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
#ifndef GUARD_LIBC_AUTO_PTY_C
#define GUARD_LIBC_AUTO_PTY_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/pty.h"
#include "../user/stdlib.h"
#include "../user/unistd.h"
#include "../user/utmp.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> forkpty(3)
 * A helper for combining `openpty(2)' with `fork(2)' and `login_tty(3)',
 * such  that  the newly  created PTY  is open  under all  std-handles in
 * the newly created child process.
 * Aside from this, this function returns the same as fork(2), that  is
 * it returns in  both the  parent and child  processes, returning  `0'
 * for the child, and the child's PID for the parent (or -1 in only the
 * parent if something went wrong) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_IN(3) ATTR_IN(4) ATTR_OUT(1) ATTR_OUT_OPT(2) pid_t
NOTHROW_NCX(LIBCCALL libc_forkpty)(fd_t *amaster,
                                   char *name,
                                   struct termios const *termp,
                                   struct winsize const *winp) {
	int error;
	fd_t master, slave;
	pid_t pid;
	error = libc_openpty(&master, &slave, name, termp, winp);
	if unlikely(error)
		return error;
	pid = libc_fork();
	if unlikely(pid == -1) {
		libc_close(master);
		goto done_slave;
	}
	if (pid == 0) {
		/* Child process. */
		libc_close(master);
		if (libc_login_tty(slave))
			libc__Exit(1);
		return 0;
	}
	/* Parent process. */
	*amaster = master;
done_slave:
	libc_close(slave);
	return pid;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(forkpty, libc_forkpty);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PTY_C */
