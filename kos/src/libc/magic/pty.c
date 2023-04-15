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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/pty.h) */
/* (#) Portability: GNU C Library (/login/pty.h) */
/* (#) Portability: GNU Hurd      (/usr/include/pty.h) */
/* (#) Portability: diet libc     (/include/pty.h) */
/* (#) Portability: libc6         (/include/pty.h) */
/* (#) Portability: mintlib       (/include/pty.h) */
/* (#) Portability: musl libc     (/include/pty.h) */
/* (#) Portability: uClibc        (/include/pty.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[default:section(".text.crt{|.dos}.io.tty")]

%[define_decl_include("<bits/os/termio.h>": ["struct winsize", "struct termio"])]
%[define_decl_include("<bits/os/termios.h>": ["struct termios"])]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/ioctl.h>
)]%{

}%[insert:prefix(
#include <termios.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

struct termios;
struct winsize;

}

@@>> openpty(2)
@@Create  a  new  ptty (psuedo  tty),  storing the  handles  for the
@@master/slave adapters in  `*amaster' and `*aslave'.  Additionally,
@@the caller  may specific  the  initial terminal  settings  `termp'
@@and  window size  `winp', as well  as a location  where the kernel
@@should store the  filename of  the PTY master  socket (as  already
@@returned in `*amaster'). Note that the max length of this filename
@@is implementation defined, with no way for the use to specify  how
@@much space is available in the passed buffer. As such, a  portable
@@application can only ever pass `NULL' for this value.
@@
@@On KOS, the value written to `name' is the absolute filename of
@@the master-device in the `/dev' filesystem, which usually means
@@that the written filename is something like `/dev/ptyp0'.
@@
@@NOTE: On KOS, this function is a system call, though in other
@@      operating system it is often implemented via `open(2)',
@@      possibly combined with `ioctl(2)'.
[[guard]]
[[decl_include("<bits/types.h>", "<bits/os/termios.h>", "<bits/os/termio.h>")]]
int openpty([[out]] $fd_t *amaster,
            [[out]] $fd_t *aslave,
            [[out_opt]] char *name,
            [[in_opt]] struct termios const *termp,
            [[in_opt]] struct winsize const *winp);

@@>> forkpty(3)
@@A helper for combining `openpty(2)' with `fork(2)' and `login_tty(3)',
@@such  that  the newly  created PTY  is open  under all  std-handles in
@@the newly created child process.
@@Aside from this, this function returns the same as fork(2), that  is
@@it returns in  both the  parent and child  processes, returning  `0'
@@for the child, and the child's PID for the parent (or -1 in only the
@@parent if something went wrong)
[[guard]]
[[decl_include("<bits/types.h>", "<bits/os/termios.h>", "<bits/os/termio.h>")]]
[[requires_function(openpty, fork, close, login_tty, _Exit)]]
$pid_t forkpty([[out]] $fd_t *amaster,
               [[out_opt]] char *name,
               [[in]] struct termios const *termp,
               [[in]] struct winsize const *winp) {
	int error;
	fd_t master, slave;
	pid_t pid;
	error = openpty(&master, &slave, name, termp, winp);
	if unlikely(error)
		return error;
	pid = fork();
	if unlikely(pid == -1) {
		close(master);
		goto done_slave;
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
done_slave:
	close(slave);
	return pid;
}

%{

__SYSDECL_END
#endif /* __CC__ */

}
