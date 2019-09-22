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
#ifndef GUARD_LIBC_USER_PTY_C
#define GUARD_LIBC_USER_PTY_C 1

#include "pty.h"

#include <kos/syscalls.h>

#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>

#include "../api.h"

DECL_BEGIN

/*[[[start:implementation]]]*/

/*[[[head:openpty,hash:CRC-32=0xa48d70d7]]]*/
/* Create pseudo tty master slave pair with NAME and set terminal
 * attributes according to TERMP and WINP and return handles for
 * both ends in AMASTER and ASLAVE */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.openpty") int
NOTHROW_NCX(LIBCCALL libc_openpty)(fd_t *amaster,
                                   fd_t *aslave,
                                   char *name,
                                   struct termios const *termp,
                                   struct winsize const *winp)
/*[[[body:openpty]]]*/
{
	errno_t result;
	result = sys_openpty(amaster,
	                     aslave,
	                     name,
	                     termp,
	                     winp);
	return libc_seterrno_syserr(result);
}
/*[[[end:openpty]]]*/

/*[[[head:forkpty,hash:CRC-32=0x1448b4e5]]]*/
/* Create child process and establish the slave pseudo
 * terminal as the child's controlling terminal */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.forkpty") pid_t
NOTHROW_NCX(LIBCCALL libc_forkpty)(fd_t *amaster,
                                   char *name,
                                   struct termios const *termp,
                                   struct winsize const *winp)
/*[[[body:forkpty]]]*/
{
	int error, master, slave;
	pid_t pid;
	error = openpty(&master, &slave, name, termp, winp);
	if unlikely(error)
		return error;
	pid = fork();
	if unlikely(pid < 0) {
		close(master);
		close(slave);
		return -1;
	}
	if (pid == 0) {
		/* Child process. */
		close(master);
		if (login_tty(slave))
			_Exit(1);
		return 0;
	}
	/* Parent process. */
	*amaster = master;
	close(slave);
	return pid;
}
/*[[[end:forkpty]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x396159a5]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(openpty, libc_openpty);
DEFINE_PUBLIC_WEAK_ALIAS(forkpty, libc_forkpty);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PTY_C */
