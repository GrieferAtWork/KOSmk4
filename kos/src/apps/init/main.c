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
#ifndef GUARD_APPS_INIT_MAIN_C
#define GUARD_APPS_INIT_MAIN_C 1

#include <hybrid/compiler.h>

#include <kos/fcntl.h>     /* Open() */
#include <kos/sys/ioctl.h> /* Ioctl() */
#include <kos/sys/stat.h>  /* Mkdir() */
#include <kos/syscalls.h>  /* sys_Xmktty() */
#include <kos/sysctl.h>    /* sysctl() */
#include <kos/types.h>     /* fd_t */
#include <kos/unistd.h>    /* Dup2() */
#include <sys/mount.h>     /* mount() */
#include <sys/syslog.h>    /* syslog() */

#include <errno.h>  /* errno */
#include <stddef.h> /* NULL */
#include <stdio.h>  /* dprintf() */
#include <string.h> /* strerror() */
#include <unistd.h> /* sync() */

DECL_BEGIN

PRIVATE char const *init_envp[] = {
	"TERM=xterm",
	NULL
};



int main(int argc, char *argv[], char *envp[]) {
	syslog(LOG_NOTICE, "[init] Init started\n");

	/* Mount the /dev filesystem. */
	if (mount(NULL, "/dev", "devfs", 0, NULL) < 0) {
		if (errno == ENOENT) {
			Mkdir("/dev", 0755);
			sync();
			if (mount(NULL, "/dev", "devfs", 0, NULL) >= 0)
				goto done_devfs;
		}
		syslog(LOG_ERR, "[init] Failed to mount devfs: %s\n",
		       strerror(errno));
	}
done_devfs:

	/* Mount the /proc filesystem (but do this optionally). */
	if (sysctl_insmod("procfs", NULL) >= 0) {
		if (mount(NULL, "/proc", "procfs", 0, NULL) < 0) {
			if (errno == ENOENT) {
				mkdir("/proc", 0755);
				sync();
				if (mount(NULL, "/proc", "procfs", 0, NULL) >= 0)
					goto done_procfs;
			}
			syslog(LOG_ERR, "[init] Failed to mount procfs: %s\n",
			       strerror(errno));
			sysctl_delmod("procfs");
		}
	}
done_procfs:

	/* Make sure there aren't any memory leaks. */
	Sysctl(SYSCTL_SYSTEM_MEMORY_DUMP_LEAKS);

	/* Load some additional drivers that we need for the I/O console. */
	SysctlInsmod("ps2", NULL); /* Keyboard */
	SysctlInsmod("vga", NULL); /* Display */

	/* Construct /dev/console from the VGA display, and a PS/2 keyboard. */
	{
		fd_t i, console, display, keyboard;
		keyboard = open("/dev/ps2kbd1", O_RDONLY | O_CLOEXEC, 0);
		if (keyboard < 0)
			keyboard = Open("/dev/ps2kbd2", O_RDONLY | O_CLOEXEC, 0);
		display = Open("/dev/vga", O_WRONLY | O_CLOEXEC, 0);
		console = sys_Xmktty(keyboard, display, "console", 0);
		close(keyboard);
		close(display);
		Symlink("console", "/dev/tty0");

		/* Set /dev/console as the controlling TTY of the our process. */
		Ioctl(console, TIOCSCTTY, NULL);

		{
			/* Set our process as the foreground process
			 * group controlled by /dev/console. */
			pid_t me = getpid();
			Ioctl(console, TIOCSPGRP, &me);
		}

		/* Open the first 3 handles as copies of the console. */
		for (i = 0; i < 3; ++i) {
			if (console != i)
				Dup2(console, i);
		}
		if (console > 3)
			close(console);
	}

	dprintf(STDOUT_FILENO,
	        "\033[J" /* ED(0):    Clear screen */
	        "\033[f" /* HVP(1,1): Place cursor at 0,0 */);

	execle("/bin/busybox", "bash", (char *)NULL, init_envp);
	Execle("/bin/sh", "sh", (char *)NULL, init_envp);

	/* TODO: `__CORRECT_ISO_CPP_MATH_H_PROTO' interferes with libstdc++'s autoconf detection... */
	/* TODO: libstdc++ doesn't detect `HAVE_ISWBLANK' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_LINK' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_LINUX_FUTEX' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_POLL' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_READLINK' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_SETENV' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_STDALIGN_H' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_STDBOOL_H' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_STRERROR_L' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_STRUCT_DIRENT_D_TYPE' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_STRXFRM_L' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_SYMLINK' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_SYS_RESOURCE_H' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_S_IFREG' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_TRUNCATE' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_VFWSCANF' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_VSWSCANF' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_VWSCANF' properly */
	/* TODO: libstdc++ doesn't detect `HAVE_WCSTOF' properly */
	/* TODO: libstdc++ doesn't detect `HAVE__WFOPEN' properly */
	/* TODO: libstdc++ doesn't detect `USE_FCHMOD' properly */
	/* TODO: libstdc++ doesn't detect `USE_FCHMODAT' properly */
	/* TODO: libstdc++ doesn't detect `USE_LFS' properly */
	/* TODO: libstdc++ doesn't detect `USE_LSTAT' properly */
	/* TODO: libstdc++ doesn't detect `USE_NANOSLEEP' properly */
	/* TODO: libstdc++ doesn't detect `USE_REALPATH' properly */
	/* TODO: libstdc++ doesn't detect `USE_SCHED_YIELD' properly */
	/* TODO: libstdc++ doesn't detect `USE_ST_MTIM' properly */
	/* TODO: libstdc++ doesn't detect `USE_UTIME' properly */
	/* TODO: libstdc++ doesn't detect `USE_UTIMENSAT' properly */
	/* TODO: libstdc++ doesn't detect `machine/endian.h' */
	/* TODO: Add support for `HAVE___CXA_THREAD_ATEXIT' */
	/* TODO: Add system header <sys/machine.h> */
	/* TODO: Add system header <sys/sdt.h> */
	/* TODO: Add system header <fenv.h> */
	/* TODO: Add system header <fp.h> */
	/* TODO: Add system header <libintl.h> */
	/* TODO: Add system header <nan.h> */
	/* TODO: Add system header <ftw.h> */
}

DECL_END

#endif /* !GUARD_APPS_INIT_MAIN_C */
