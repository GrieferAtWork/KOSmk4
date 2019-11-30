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
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _ATFILE_SOURCE 1

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
#include <sys/wait.h>      /* waitpid() */

#include <errno.h>   /* errno */
#include <fcntl.h>   /* AT_FDDRIVE_ROOT() */
#include <sched.h>   /* sched_yield() */
#include <signal.h>  /* signal() */
#include <stddef.h>  /* NULL */
#include <stdio.h>   /* dprintf() */
#include <string.h>  /* strerror() */
#include <termios.h> /* struct termios */
#include <unistd.h>  /* sync() */

#include <libansitty/ansitty.h>

DECL_BEGIN

PRIVATE char const *init_envp[] = {
	"PATH=/bin",
	"HOME=/",
	"TERM=xterm",
	NULL
};

/* Set the calling process as foreground process for /dev/console */
PRIVATE void console_set_fgproc(void) {
	pid_t me = 0; /* `0' is an alias for `getpid()' here. */
	Ioctl(STDIN_FILENO, TIOCSPGRP, &me);
}

/* Reset the termios of /dev/console to sane values */
PRIVATE void console_sane_ios(void) {
	struct termios ios;
	cfmakesane(&ios);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &ios);
}



int main(int argc, char *argv[], char *envp[]) {
	(void)argc;
	(void)argv;
	(void)envp;
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

	/* TODO: Make it so that the PS/2 driver checks for (and disables) USB
	 *       emulation, such that we only need to load the usb-hid drivers
	 *       when the ps2 keyboard files are missing from /dev
	 *       As it stands right now, PS/2 will still create device files,
	 *       even when the devices stem from USB emulation. */
	sysctl_insmod("usb-hid", NULL);

	/* Setup a couple of signals to-be ignored */
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);

	/* Construct /dev/console from the VGA display, and a PS/2 keyboard. */
	{
		fd_t i, console, display, keyboard;
		keyboard = open("/dev/usbkba", O_RDONLY | O_CLOEXEC, 0);
		if (keyboard < 0)
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
			pid_t me = 0; /* `0' is an alias for `getpid()' here. */
			Ioctl(console, TIOCSPGRP, &me);
		}

		/* Open the first 3 handles as copies of the console. */
		for (i = 0; i < 3; ++i) {
			if (console != i)
				Dup2(console, i);
		}
		if (console >= 3)
			close(console);
	}

	/* Construct the recommended symlinks for devfs.
	 * Don't do any error checking, since their absence
	 * shouldn't hinder minimal operability of the system. */
	symlink("/proc/self/fd", "/dev/fd");
	symlink("/proc/self/fd/0", "/dev/stdin");
	symlink("/proc/self/fd/1", "/dev/stdout");
	symlink("/proc/self/fd/2", "/dev/stderr");

	/* Setup dos drives. */
	{
		fd_t rfd = open("/", O_RDONLY | O_DIRECTORY);
		if (rfd >= 0) {
			dup2(rfd, AT_FDDRIVE_ROOT('C'));
			close(rfd);
		}
	}

	for (;;) {
		pid_t cpid;
		/* Do some cleanup on the console. */
		dprintf(STDOUT_FILENO,
		        ANSITTY_RESET_SEQUENCE /* Reset the TTY */
		        "\033[f" /* HVP(1,1): Place cursor at 0,0 */
		        "\033[J" /* ED(0):    Clear screen */);

		/* Don't directly exec() busybox.
		 * Instead, fork()+exec(), then keep on doing so
		 * whenever busybox dies (such as when the user presses
		 * CTRL+D do trigger an end-of-input event) */
		cpid = VFork();
		if (cpid == 0) {
			/* Become the foreground process of /dev/console */
			console_set_fgproc();
			execle("/bin/busybox", "bash", (char *)NULL, init_envp);
			execle("/bin/sh", "sh", (char *)NULL, init_envp);
			dprintf(STDOUT_FILENO, "Failed to launch shell: %s\n", strerror(errno));
			for (;;) {
				char buf[1];
				read(STDIN_FILENO, buf, sizeof(buf));
			}
		}

		/* Wait for the user-shell to die. */
		while (waitpid(cpid, NULL, 0) < 0)
			sched_yield();

		/* Kill anything which may have been left alive by the shell.
		 * Note that kill(-1, ...) will never kill a process with pid=1,
		 * meaning that we (the process with pid=1) won't get killed
		 * by this! */
		/* TODO: Send SIGQUIT and wait for a configurable timeout until all
		 *       processes except for our own have died. Only once the timeout
		 *       expires with different processes still alive should we send
		 *       SIGKILL. - That way, other processes still get a chance to
		 *       perform some cleanup (such as saving data to disk) before
		 *       really going away.
		 * NOTE: We can't use opendir("/proc") for this, since we mustn't rely
		 *       on a working procfs (see the procfs init above, which allows
		 *       for the insmod() and mount() to fail), meaning we need to use
		 *       a custom (probably sysctl()-based) function for checking how
		 *       many user-space threads are running on system */
		kill(-1, SIGKILL);

		/* Become the foreground process of /dev/console
		 * In theory this shouldn't be necessary, since the kill() before
		 * should have gotten rid of any process that could have been holding
		 * this foreground-process lock before, however just in case the kernel
		 * decides to make a SIGKILL-broadcast be performed asynchronously, in
		 * which case the old foreground process may still be alive when we
		 * clear the console above. - Note however that since we've installed
		 * a SIG_IGN handler for `SIGTTOU', we still wouldn't get suspended in
		 * such a scenario, but we'd still be unable to reset the tty... */
		console_set_fgproc();

		/* Reset the termios of /dev/console to sane values */
		console_sane_ios();
	}
}

DECL_END

#endif /* !GUARD_APPS_INIT_MAIN_C */
