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
#ifndef GUARD_APPS_INIT_MAIN_C
#define GUARD_APPS_INIT_MAIN_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _ATFILE_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/config/toolchain.h>
#include <kos/fcntl.h> /* Open() */
#include <kos/io.h>
#include <kos/ioctl/svga.h>
#include <kos/ksysctl.h>   /* ksysctl_insmod() */
#include <kos/sys/ioctl.h> /* Ioctl() */
#include <kos/sys/stat.h>  /* MkDir() */
#include <kos/syscalls.h>  /* sys_Xmktty() */
#include <kos/types.h>     /* fd_t */
#include <kos/unistd.h>    /* Dup2() */
#include <sys/mount.h>     /* mount() */
#include <sys/syslog.h>    /* syslog() */
#include <sys/wait.h>      /* waitpid() */

#include <errno.h>   /* errno */
#include <fcntl.h>   /* AT_FDDRIVE_ROOT() */
#include <paths.h>   /* _PATH_DEFPATH */
#include <sched.h>   /* sched_yield() */
#include <signal.h>  /* signal() */
#include <stddef.h>  /* NULL */
#include <stdio.h>   /* dprintf() */
#include <string.h>  /* strerror() */
#include <termios.h> /* struct termios */
#include <unistd.h>  /* sync() */

#include <libansitty/ansitty.h>
#include <libansitty/ctl.h>


DECL_BEGIN

PRIVATE char const *init_envp[] = {
	"HOME=/",
	"PATH=" _PATH_STDPATH, /* NOLINT */
	"PWD=/",
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



/* User-space entry point for /bin/init
 * NOTE: This program is  running as PID=1  (i.e. boottask), which  carries
 *       the `TASK_FCRITICAL' flag, meaning that if this program ever dies,
 *       then the kernel will (intentionally) PANIC! */
int main(int argc, char *argv[], char *envp[]) {
	volatile int have_fortune;

	(void)argc;
	(void)argv;
	(void)envp;
	syslog(LOG_NOTICE, "[init] Init started\n");

	/* Try to load the debugger extensions drivers. */
	ksysctl_insmod("dbx", NULL);

	/* Enable system call tracing by loading the sctrace driver. */
	ksysctl_insmod("sctrace", NULL);

	/* Mount the /dev filesystem. */
	if (mount(NULL, "/dev", "devfs", 0, NULL) < 0) {
		if (errno == ENOENT) {
			MkDir("/dev", 0755);
			sync();
			if (mount(NULL, "/dev", "devfs", 0, NULL) >= 0)
				goto done_devfs;
		}
		syslog(LOG_ERR, "[init] Failed to mount devfs: %m\n");
	}
done_devfs:

	/* Mount the /proc filesystem (but do this optionally). */
	if (ksysctl_insmod("procfs", NULL) >= 0) {
		if (mount(NULL, "/proc", "procfs", 0, NULL) < 0) {
			if (errno == ENOENT) {
				mkdir("/proc", 0755);
				sync();
				if (mount(NULL, "/proc", "procfs", 0, NULL) >= 0)
					goto done_procfs;
			}
			syslog(LOG_ERR, "[init] Failed to mount procfs: %m\n");
			ksysctl_delmod("procfs");
		}
	}
done_procfs:

	/* Also mount a ramfs filesystem under /tmp */
	if (mount(NULL, "/tmp", "ramfs", 0, NULL) < 0) {
		if (errno == ENOENT) {
			mkdir("/tmp", 0755);
			sync();
			if (mount(NULL, "/tmp", "ramfs", 0, NULL) >= 0)
				goto done_tmpfs;
		}
		syslog(LOG_ERR, "[init] Failed to mount ramfs: %m\n");
	}
done_tmpfs:


	/* Load some additional drivers that we need for the I/O console. */
	KSysctlInsmod("ps2", NULL);  /* Keyboard */
	KSysctlInsmod("svga", NULL); /* Display */

	/* TODO: Make it so that the PS/2 driver checks for (and disables) USB
	 *       emulation, such that we only need to load the usb-hid drivers
	 *       when  the   ps2  keyboard   files  are   missing  from   /dev
	 *       As  it stands right now, PS/2 will still create device files,
	 *       even when the devices stem from USB emulation. */
//	ksysctl_insmod("usb", NULL);

	/* Setup a couple of signals to-be ignored */
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);

	/* Construct /dev/console from the VGA display, and a keyboard. */
	{
		struct svga_maketty tty;
		fd_t i, console, display, keyboard;
		keyboard = open("/dev/usbkba", O_RDONLY | O_CLOEXEC);
		if (keyboard < 0)
			keyboard = open("/dev/ps2kbd1", O_RDONLY | O_CLOEXEC);
		if (keyboard < 0)
			keyboard = Open("/dev/ps2kbd2", O_RDONLY | O_CLOEXEC);
		display = Open("/dev/svga", O_WRONLY | O_CLOEXEC);

		/* Construct ansitty device /dev/svga1 */
		bzero(&tty, sizeof(tty));
#if OPENFD_MODE_AUTO != 0 /* When `0', will have already been done by bzero() */
		tty.smt_res.of_mode = OPENFD_MODE_AUTO;
#endif /* OPENFD_MODE_AUTO != 0 */
		tty.smt_res.of_flags = IO_CLOEXEC;
		Ioctl(display, SVGA_IOC_GETDEFMODE, &tty.smt_mode);
		tty.smt_name = "svga1";
		Ioctl(display, SVGA_IOC_MAKETTY, &tty);
		close(display);
		display = tty.smt_res.of_hint;
		Ioctl(display, SVGA_IOC_ACTIVATE);

		console = sys_Xmktty("console", keyboard, display, 0);
		close(keyboard);
		close(display);
		Symlink("console", "/dev/tty0");

		/* Set /dev/console as the controlling TTY of the our process. */
		Ioctl(console, TIOCSCTTY, NULL);

		{
			/* Set our process as the foreground process
			 * group    controlled    by   /dev/console. */
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

	/* Construct  the  recommended  symlinks  for   devfs.
	 * Don't do any  error checking,  since their  absence
	 * shouldn't hinder minimal operability of the system. */
	symlink("/proc/self/fd", "/dev/fd");
	symlink("/proc/self/fd/0", "/dev/stdin");
	symlink("/proc/self/fd/1", "/dev/stdout");
	symlink("/proc/self/fd/2", "/dev/stderr");

	/* Setup dos drives. */
	{
		fd_t rfd = open("/", O_RDONLY | O_DIRECTORY); /* NOLINT */
		if (rfd >= 0) {
			dup2(rfd, AT_FDDRIVE_ROOT('C'));
			close(rfd);
		}
	}

#if 0
	{
		pid_t cpid;
		int stat;
		int i;
		for (i = 0; i < 8; ++i) {
			cpid = VFork();
			if (cpid == 0) {
				console_set_fgproc();
				signal(SIGHUP, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				signal(SIGTTIN, SIG_DFL);
				signal(SIGTTOU, SIG_DFL);
				execle("/bin/system-test32", "system-test32", (char *)NULL, init_envp);
			}
			/* Wait for the system-test to finish. */
			while (waitpid(cpid, &stat, 0) < 0)
				sched_yield();
			if (!WIFEXITED(stat) || WEXITSTATUS(stat) != 0) {
				syslog(LOG_ERR, "system-test exited with %u\n",
					   WEXITSTATUS(stat));
				for (;;)
					pause();
			}
		}
		ksysctl(0xcccc0001); /* reboot (requires `CONFIG_HAVE_KERNEL_HACKY_REBOOT') */
		for (;;)
			pause();
	}
#endif

	/* Just for fun :P */
	have_fortune = access("/usr/bin/fortune", X_OK);

	for (;;) {
		pid_t cpid;
		/* Do some cleanup on the console. */
		dprintf(STDOUT_FILENO,
		        AC_CAN    /* Cancel any in-progress escape sequence */
		        AC_CUP0   /* Place cursor at 0,0 */
		        AC_RIS    /* Reset all terminal settings (except for cursor position and screen contents) */
		        AC_ED("") /* Clear screen */
		        "");

		/* If you've got bsdgames installed, I'll tell you your fortune */
		if ((have_fortune == 0) && (VFork() == 0)) {
			signal(SIGHUP, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);
			execle("/usr/bin/fortune", "fortune", (char *)NULL, init_envp);
			have_fortune = -1; /* VFork() means we share VM, so this writes to parent process! */
			_Exit(127);
		}

		/* Don't directly exec() busybox.
		 * Instead, fork()+exec(),  then keep  on doing  so
		 * whenever  busybox  dies (such  as when  the user
		 * presses CTRL+D do trigger an end-of-input event) */
		cpid = VFork();
		if (cpid == 0) {
			/* Become the foreground process of /dev/console */
			console_set_fgproc();

			/* Restore default signal dispositions */
			signal(SIGHUP, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			signal(SIGTTOU, SIG_DFL);

			/* Try stuff from `/etc/shells' */
			{
				char *shell;
				setusershell();
				while ((shell = getusershell()) != NULL) {
					execle(shell, strrchrnul(shell, '/') + 1,
					       (char *)NULL, init_envp);
				}
			}

			/* Try some fallback paths. */
			execle("/bin/sh", "sh", (char *)NULL, init_envp);
			execle("/bin/csh", "csh", (char *)NULL, init_envp);
			execle("/bin/bash", "bash", (char *)NULL, init_envp);
			execle("/bin/busybox", "bash", (char *)NULL, init_envp);

			/* Display an error if we were unable to launch a shell. */
			dprintf(STDOUT_FILENO, "Failed to launch shell: %m\n");
			if (errno == ENOENT) {
				dprintf(STDOUT_FILENO,
				        "Did you remember to install:\n"
				        "\t" AC_WHITE("bash kos/misc/make_utility.sh " KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_ARCH " busybox") "\n");
			}
			for (;;) {
				char buf[1];
				read(STDIN_FILENO, buf, sizeof(buf));
			}
		}

		/* Wait for the user-shell  to die, as well  as
		 * reap processes that got re-parented onto us. */
		for (;;) {
			pid_t wpid;
			union wait st;
			wpid = wait(&st);
			if (wpid < 0) {
				if (errno != EINTR) {
					syslog(LOG_ERR, "init: wait(2) failed with %s\n",
					       strerrorname_np(errno));
				}
				sched_yield();
				continue;
			}
			if (wpid == cpid)
				break; /* Shell died. -- Try to spawn a new one. */
			syslog(LOG_INFO, "init: reaped detached process %d [status:%#.4x]\n",
			       wpid, st.w_status);
		}

		/* Kill  anything which may  have been left  alive by the shell.
		 * Note that kill(-1, ...) will never kill a process with pid=1,
		 * meaning  that we (the process with pid=1) won't get killed by
		 * this! */
		/* TODO: Send SIGTERM and  wait for a  configurable timeout until  all
		 *       processes except for our own have died. Only once the timeout
		 *       expires with different processes  still alive should we  send
		 *       SIGKILL.  - That way,  other processes still  get a chance to
		 *       perform  some cleanup  (such as  saving data  to disk) before
		 *       really going away.
		 * NOTE: We can't use opendir("/proc") for this, since we mustn't rely
		 *       on  a working procfs (see the procfs init above, which allows
		 *       for the insmod() and mount() to fail), meaning we need to use
		 *       a  custom (probably sysctl()-based) function for checking how
		 *       many user-space threads are running on the system */
		kill(-1, SIGKILL);

		/* Become the foreground process of /dev/console
		 * In theory  this shouldn't  be necessary,  since the  kill()  before
		 * should have gotten rid of any process that could have been  holding
		 * the foreground-process lock before, however just in case the kernel
		 * decides to have a SIGKILL-broadcast be performed asynchronously, in
		 * which  case the old  foreground process may still  be alive when we
		 * clear the console above, we go the safe route and always become the
		 * foreground process  once  again.  - Note  however  that  since  we'
		 * installed a SIG_IGN  handler for `SIGTTOU',  we still wouldn't  get
		 * suspended in such a scenario, but we'd also be unable to reset  the
		 * tty... */
		console_set_fgproc();

		/* Reset the termios of /dev/console to sane values */
		console_sane_ios();
	}
}

DECL_END

#endif /* !GUARD_APPS_INIT_MAIN_C */
