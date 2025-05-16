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
#include <sys/ioctl.h>     /* TIOCSPGRP */
#include <sys/mount.h>     /* mount() */
#include <sys/stat.h>      /* mkdir */
#include <sys/syslog.h>    /* syslog() */
#include <sys/types.h>     /* pid_t */
#include <sys/wait.h>      /* waitpid() */

#include <errno.h>   /* errno */
#include <fcntl.h>   /* AT_FDDRIVE_ROOT() */
#include <paths.h>   /* _PATH_DEFPATH */
#include <sched.h>   /* sched_yield() */
#include <signal.h>  /* signal() */
#include <stddef.h>  /* NULL */
#include <stdio.h>   /* dprintf() */
#include <stdlib.h>  /* _Exit() */
#include <string.h>  /* strerror() */
#include <termios.h> /* struct termios */
#include <unistd.h>  /* sync() */

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
	(void)Ioctl(STDIN_FILENO, TIOCSPGRP, &me);
}

/* Reset the termios of /dev/console to sane values */
PRIVATE void console_sane_ios(void) {
	struct termios ios;
	cfmakesane(&ios);
	(void)tcsetattr(STDIN_FILENO, TCSADRAIN, &ios);
}



/* User-space entry point for /bin/init
 * NOTE: This program is  running as PID=1  (i.e. boottask), which  carries
 *       the `TASK_FCRITICAL' flag, meaning that if this program ever dies,
 *       then the kernel will (intentionally) PANIC! */
int main(int argc, char *argv[], char *envp[]) {
	/* "volatile" so guarantied shared with VFork() child process */
	volatile int have_fortune;

	(void)argc;
	(void)argv;
	(void)envp;
	syslog(LOG_NOTICE, "[init] Init started\n");

	/* Try to load the debugger extensions drivers. */
	(void)ksysctl_insmod("dbx", NULL);

	/* Enable system call tracing by loading the sctrace driver. */
	(void)ksysctl_insmod("sctrace", NULL);

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
				(void)mkdir("/proc", 0755);
				sync();
				if (mount(NULL, "/proc", "procfs", 0, NULL) >= 0)
					goto done_procfs;
			}
			syslog(LOG_ERR, "[init] Failed to mount procfs: %m\n");
			(void)ksysctl_delmod("procfs");
		}
	}
done_procfs:

	/* Also mount a ramfs filesystem under /tmp */
	if (mount(NULL, "/tmp", "ramfs", 0, NULL) < 0) {
		if (errno == ENOENT) {
			(void)mkdir("/tmp", 0755);
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
	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGTTIN, SIG_IGN);
	(void)signal(SIGTTOU, SIG_IGN);

	/* Construct /dev/console from an SVGA-based TTY, and some keyboard. */
	{
		struct svga_maketty tty;
		fd_t i, console, svga1, svga, keyboard;

		/* Find a keyboard to use */
		keyboard = open("/dev/usbkba", O_RDONLY | O_CLOEXEC);
		if (keyboard < 0)
			keyboard = open("/dev/ps2kbd1", O_RDONLY | O_CLOEXEC);
		if (keyboard < 0)
			keyboard = Open("/dev/ps2kbd2", O_RDONLY | O_CLOEXEC);

		/* Gain access to the SVGA controller driver */
		svga = Open("/dev/svga", O_WRONLY | O_CLOEXEC);

		/* Construct an SVGA ansitty device "/dev/svga1" */
		bzero(&tty, sizeof(tty));
#if OPENFD_MODE_AUTO != 0 /* When `0', will have already been done by bzero() */
		tty.smt_res.of_mode = OPENFD_MODE_AUTO;
#endif /* OPENFD_MODE_AUTO != 0 */
		tty.smt_res.of_flags = IO_CLOEXEC;

		/* Ask  SVGA about its  default video mode (which  will be the preferred
		 * video mode specified via the kernel commandline, or some other means) */
		(void)Ioctl(svga, SVGA_IOC_GETDEFMODE, &tty.smt_mode);

		/* Actually create a new SVGA TTY and name it "/dev/svga1" */
		tty.smt_name = "svga1";
		(void)Ioctl(svga, SVGA_IOC_MAKETTY, &tty);
		(void)close(svga);

		/* Active the newly created TTY, making it claim ownership of the physical screen */
		svga1 = tty.smt_res.of_hint;
		(void)Ioctl(svga1, SVGA_IOC_ACTIVATE);

		/* Create a proper system TTY by combining our ANSI/SVGA TTY with the keyboard
		 * from earlier. The result then  becomes "console" (i.e.: the default  system
		 * console) */
		console = sys_Xmktty("console", keyboard, svga1, 0);
		(void)close(keyboard);
		(void)close(svga1);

		/* Link "console" as an alias for "/dev/tty0" (the first TTY) */
		Symlink("console", "/dev/tty0");

		/* Set /dev/console as the controlling TTY of the our process (/bin/init). */
		(void)Ioctl(console, TIOCSCTTY, NULL);

		{
			/* Set our process as the foreground process
			 * group   controlled   by   `/dev/console'. */
			pid_t me = 0; /* `0' is an alias for `getpid()' here. */
			(void)Ioctl(console, TIOCSPGRP, &me);
		}

		/* Open the first 3 handles as copies of the console. */
		for (i = 0; i < 3; ++i) {
			if (console != i)
				(void)Dup2(console, i);
		}
		if (console >= 3)
			(void)close(console);
	}

	/* Construct  the  recommended  symlinks  for   devfs.
	 * Don't do any  error checking,  since their  absence
	 * shouldn't hinder minimal operability of the system. */
	(void)symlink("/proc/self/fd", "/dev/fd");
	(void)symlink("/proc/self/fd/0", "/dev/stdin");
	(void)symlink("/proc/self/fd/1", "/dev/stdout");
	(void)symlink("/proc/self/fd/2", "/dev/stderr");

	/* Setup dos drives. */
	{
		fd_t rfd = open("/", O_RDONLY | O_DIRECTORY); /* NOLINT */
		if (rfd >= 0) {
			(void)dup2(rfd, AT_FDDRIVE_ROOT('C'));
			(void)close(rfd);
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
				(void)signal(SIGHUP, SIG_DFL);
				(void)signal(SIGINT, SIG_DFL);
				(void)signal(SIGTTIN, SIG_DFL);
				(void)signal(SIGTTOU, SIG_DFL);
				(void)execle("/bin/system-test32", "system-test32", (char *)NULL, init_envp);
			}
			/* Wait for the system-test to finish. */
			while (waitpid(cpid, &stat, 0) < 0)
				(void)sched_yield();
			if (!WIFEXITED(stat) || WEXITSTATUS(stat) != 0) {
				syslog(LOG_ERR, "system-test exited with %u\n",
					   WEXITSTATUS(stat));
				for (;;)
					(void)pause();
			}
		}
		ksysctl(0xcccc0001); /* reboot (requires `CONFIG_HAVE_KERNEL_HACKY_REBOOT') */
		for (;;)
			(void)pause();
	}
#endif

	/* Just for fun :P */
	have_fortune = access("/usr/bin/fortune", X_OK);

	for (;;) {
		pid_t cpid;
		/* Do some cleanup on the console. */
		(void)dprintf(STDOUT_FILENO,
		              ""
		              AC_CAN /* Cancel any in-progress escape sequence */
		              AC_CUP0   /* Place cursor at 0,0 */
		              AC_RIS    /* Reset all terminal settings (except for cursor position and screen contents) */
		              AC_ED("") /* Clear screen */
		              "");

		/* If you've got bsdgames installed, I'll tell you your fortune */
		if ((have_fortune == 0) && (VFork() == 0)) {
			(void)signal(SIGHUP, SIG_DFL);
			(void)signal(SIGINT, SIG_DFL);
			(void)signal(SIGTTIN, SIG_DFL);
			(void)signal(SIGTTOU, SIG_DFL);
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
			(void)signal(SIGHUP, SIG_DFL);
			(void)signal(SIGINT, SIG_DFL);
			(void)signal(SIGTTIN, SIG_DFL);
			(void)signal(SIGTTOU, SIG_DFL);

			/* Try stuff from `/etc/shells' */
			{
				char *shell;
				setusershell();
				while ((shell = getusershell()) != NULL) {
					(void)execle(shell, strrchrnul(shell, '/') + 1,
					             (char *)NULL, init_envp);
				}
			}

			/* Try some fallback paths. */
			(void)execle("/bin/sh", "sh", (char *)NULL, init_envp);
			(void)execle("/bin/csh", "csh", (char *)NULL, init_envp);
			(void)execle("/bin/bash", "bash", (char *)NULL, init_envp);
			(void)execle("/bin/busybox", "bash", (char *)NULL, init_envp);

			/* Display an error if we were unable to launch a shell. */
			(void)dprintf(STDOUT_FILENO, "Failed to launch shell: %m\n");
			if (errno == ENOENT) {
				(void)dprintf(STDOUT_FILENO,
				              "Did you remember to install:\n"
				              "\t" AC_WHITE("bash kos/misc/make_utility.sh " KOS_BUILD_CONFIG_TOOLCHAIN_BUILD_ARCH " busybox") "\n");
			}
			for (;;) {
				char buf[1];
				(void)read(STDIN_FILENO, buf, sizeof(buf));
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
				(void)sched_yield();
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
		(void)kill(-1, SIGKILL);

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
