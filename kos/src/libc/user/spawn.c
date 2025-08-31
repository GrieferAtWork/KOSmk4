/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SPAWN_C
#define GUARD_LIBC_USER_SPAWN_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>
#include <sys/wait.h>

#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "spawn.h"

DECL_BEGIN

/*[[[head:libc_pidfd_spawn_impl,hash:CRC-32=0xceef6ea0]]]*/
INTERN ATTR_SECTION(".text.crt.fs.exec.posix_spawn") ATTR_IN(6) ATTR_IN(7) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pidfd_spawn_impl)(fd_t *__restrict pidfd,
                                            unsigned int exec_type,
                                            void *exec_arg,
                                            posix_spawn_file_actions_t const *file_actions,
                                            posix_spawnattr_t const *attrp,
                                            __TARGV,
                                            __TENVP)
/*[[[body:libc_pidfd_spawn_impl]]]*/
{
	int status;
	errno_t result, error, old_errno;
	pid_t child;
	struct clone_args cargs;
	old_errno = libc_geterrno();
	(void)libc_seterrno(0);

	/* This is the magic right here: do a VFORK+PIDFD clone(2) system call. */
	bzero(&cargs, sizeof(cargs));
	cargs.ca_flags       = CLONE_VM | CLONE_VFORK | CLONE_PIDFD;
	cargs.ca_exit_signal = SIGCHLD;
	cargs.ca_pidfd       = pidfd;
	child = sys_clone3(&cargs, sizeof(cargs));
	if (child == 0)
		goto do_exec;
	if (E_ISERR(child)) {
		/* The vfork() itself failed. */
		(void)libc_seterrno(old_errno);
		return -child;
	}

	/* Check if something within the child failed after vfork(). */
	result = libc_geterrno();
	if (result != 0)
		goto err_join_zombie_child;

	/* Restore the old errno */
	(void)libc_seterrno(old_errno);
	return result;
err_join_zombie_child:
	/* Unless the child was already spawned as detached,
	 * we still have to re-join  it, or else it will  be
	 * left dangling as a zombie process! */
	if (waitpid(child, &status, 0) < 0) {
		if (libc_geterrno() == EINTR)
			goto err_join_zombie_child;
	}
	/* Must close the (already-opened) PIDfd file descriptor. Even though
	 * we *did* manage to  spawn a new process,  the exec part that  came
	 * after failed, meaning we can't let our caller inherit the FD. */
	(void)close(*pidfd);
	(void)libc_seterrno(old_errno);
	return result;
do_exec:
	error = libc_posix_spawn_child(exec_type, exec_arg, file_actions, attrp, ___argv, ___envp);
	if (error != 0) {
		/* If the exec fails, it will have modified `errno' to indicate this fact.
		 * And since we're sharing VMs with  our parent process, the error  reason
		 * will have already  been written  back to  our parent's  VM, so  there's
		 * actually nothing left for us to do, but to simply exit! */
		libc_seterrno(error);
	}
	_Exit(127);
}
/*[[[end:libc_pidfd_spawn_impl]]]*/

/*[[[start:exports,hash:CRC-32=0x0]]]*/
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SPAWN_C */
