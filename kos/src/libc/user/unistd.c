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
#ifndef GUARD_LIBC_USER_UNISTD_C
#define GUARD_LIBC_USER_UNISTD_C 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/pagesize.h>
#include <kos/hop/mfile.h> /* Needed for fpathconf() */
#include <kos/ioctl/tty.h>
#include <kos/syscalls.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/utsname.h>

#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <limits.h>
#include <paths.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

#include "../libc/capture-varargs.h"
#include "../libc/dl.h"
#include "../libc/globals.h"
#include "../libc/tls.h"
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"

#ifdef __ARCH_PAGESIZE
#define OS_PAGESIZE __ARCH_PAGESIZE
#else /* __ARCH_PAGESIZE */
#define OS_PAGESIZE getpagesize()
#endif /* !__ARCH_PAGESIZE */

DECL_BEGIN

INTERN ATTR_SECTION(".bss.crt.fs.environ.lock")
struct atomic_rwlock libc_environ_lock = ATOMIC_RWLOCK_INIT;

DEFINE_PUBLIC_ALIAS(__p__environ, libc_p_environ);
INTERN WUNUSED ATTR_CONST ATTR_RETNONNULL
ATTR_SECTION(".text.crt.dos.fs.environ.__p__environ") char ***
NOTHROW(LIBCCALL libc_p_environ)(void) {
	return &environ;
}




/*[[[head:libc_execve,hash:CRC-32=0xae5637c3]]]*/
/* >> execve(2)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_execve)(char const *__restrict path,
                                  __TARGV,
                                  __TENVP)
/*[[[body:libc_execve]]]*/
{
	errno_t result;
	result = sys_execve(path,
	                    (char *const *)___argv,
	                    (char *const *)___envp);
	return (int)libc_seterrno(-result);
}
/*[[[end:libc_execve]]]*/

/*[[[head:libc_getpid,hash:CRC-32=0xf750987b]]]*/
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
INTERN ATTR_SECTION(".text.crt.sched.process") ATTR_CONST WUNUSED pid_t
NOTHROW(LIBCCALL libc_getpid)(void)
/*[[[body:libc_getpid]]]*/
{
	pid_t result = sys_getpid();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getpid]]]*/

/*[[[head:libc_pipe,hash:CRC-32=0x68f6b91f]]]*/
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTERN ATTR_SECTION(".text.crt.io.access") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pipe)(fd_t pipedes[2])
/*[[[body:libc_pipe]]]*/
{
	errno_t error;
	error = sys_pipe(pipedes);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_pipe]]]*/

/*[[[head:libc_sleep,hash:CRC-32=0x56bdadfa]]]*/
/* >> sleep(3)
 * Sleep for up to `seconds' seconds */
INTERN ATTR_SECTION(".text.crt.system.utility") unsigned int
NOTHROW_RPC(LIBCCALL libc_sleep)(unsigned int seconds)
/*[[[body:libc_sleep]]]*/
{
	struct timespec req, rem;
	req.tv_sec  = seconds;
	req.tv_nsec = 0;
	rem.tv_sec  = 0;
	sys_nanosleep(&req, &rem);
	return rem.tv_sec;
}
/*[[[end:libc_sleep]]]*/

/*[[[head:libc_getppid,hash:CRC-32=0xffba2bcf]]]*/
/* >> getppid(2)
 * Return the PID of the calling process's parent.
 * (That is the TID of the leader of the parent of the calling thread's leader)
 * THIS_THREAD->LEADER->PARENT->LEADER->PID */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getppid)(void)
/*[[[body:libc_getppid]]]*/
{
	pid_t result = sys_getppid();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getppid]]]*/

/*[[[head:libc_getpgrp,hash:CRC-32=0xfcc72f04]]]*/
/* >> getpgrp(2)
 * Return the ID of the calling process's process group.
 * (That is the TID of the leader of the process group of the calling thread's leader)
 * THIS_THREAD->LEADER->GROUP_LEADER->PID */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getpgrp)(void)
/*[[[body:libc_getpgrp]]]*/
{
	pid_t result = sys_getpgid(0);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getpgrp]]]*/

/*[[[head:libc_setpgid,hash:CRC-32=0x5c9bcdc1]]]*/
/* >> setpgid(2)
 * Change the ID of the process group associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
INTERN ATTR_SECTION(".text.crt.sched.process") int
NOTHROW_NCX(LIBCCALL libc_setpgid)(pid_t pid,
                                   pid_t pgid)
/*[[[body:libc_setpgid]]]*/
{
	errno_t result = sys_setpgid(pid, pgid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setpgid]]]*/

/*[[[head:libc_setsid,hash:CRC-32=0x23cae8a2]]]*/
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making it its own session leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
INTERN ATTR_SECTION(".text.crt.sched.process") pid_t
NOTHROW_NCX(LIBCCALL libc_setsid)(void)
/*[[[body:libc_setsid]]]*/
{
	pid_t result = sys_setsid();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setsid]]]*/

/*[[[head:libc_getuid,hash:CRC-32=0xf6d31881]]]*/
/* >> getuid(2)
 * Return the real user ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED uid_t
NOTHROW_NCX(LIBCCALL libc_getuid)(void)
/*[[[body:libc_getuid]]]*/
{
#ifdef SYS_getuid32
	uint32_t result = sys_getuid32();
#else /* SYS_getuid32 */
	uid_t result = sys_getuid();
#endif /* !SYS_getuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getuid]]]*/

/*[[[head:libc_geteuid,hash:CRC-32=0x4fa2ab2b]]]*/
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED uid_t
NOTHROW_NCX(LIBCCALL libc_geteuid)(void)
/*[[[body:libc_geteuid]]]*/
{
#ifdef SYS_geteuid32
	uint32_t result = sys_geteuid32();
#else /* SYS_geteuid32 */
	uid_t result = sys_geteuid();
#endif /* !SYS_geteuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_geteuid]]]*/

/*[[[head:libc_getgid,hash:CRC-32=0x144895db]]]*/
/* >> getgid(2)
 * Return the real group ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED gid_t
NOTHROW_NCX(LIBCCALL libc_getgid)(void)
/*[[[body:libc_getgid]]]*/
{
#ifdef SYS_getgid32
	uint32_t result = sys_getgid32();
#else /* SYS_getgid32 */
	gid_t result = sys_getgid();
#endif /* !SYS_getgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getgid]]]*/

/*[[[head:libc_getegid,hash:CRC-32=0x4df40388]]]*/
/* >> getegid(2)
 * Return the effective group ID of the calling process */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED gid_t
NOTHROW_NCX(LIBCCALL libc_getegid)(void)
/*[[[body:libc_getegid]]]*/
{
#ifdef SYS_getegid32
	uint32_t result = sys_getegid32();
#else /* SYS_getegid32 */
	gid_t result = sys_getegid();
#endif /* !SYS_getegid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getegid]]]*/

/*[[[head:libc_getgroups,hash:CRC-32=0x1550b567]]]*/
/* >> getgroups(2)
 * @return: * : [count == 0] The required number of groups
 * @return: * : [count != 0] The number of groups that were actually returned
 * @return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_getgroups)(int size,
                                     gid_t list[])
/*[[[body:libc_getgroups]]]*/
{
	errno_t result;
#if defined(SYS_setgroups32) && __SIZEOF_GID_T__ == 4
	result = sys_getgroups32((size_t)size, (uint32_t *)list);
#else /* SYS_setgroups32 && __SIZEOF_GID_T__ == 4 */
	result = sys_getgroups((size_t)size, (uint32_t *)list);
#endif /* !SYS_setgroups32 || __SIZEOF_GID_T__ != 4 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getgroups]]]*/

/*[[[head:libc_setuid,hash:CRC-32=0x36baefd7]]]*/
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setuid)(uid_t uid)
/*[[[body:libc_setuid]]]*/
{
	errno_t result;
#ifdef SYS_setuid32
	result = sys_setuid32((uint32_t)uid);
#else /* SYS_setuid32 */
	result = sys_setuid(uid);
#endif /* !SYS_setuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setuid]]]*/

/*[[[head:libc_setgid,hash:CRC-32=0xd63f5aff]]]*/
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setgid)(gid_t gid)
/*[[[body:libc_setgid]]]*/
{
	errno_t result;
#ifdef SYS_setgid32
	result = sys_setgid32((uint32_t)gid);
#else /* SYS_setgid32 */
	result = sys_setgid(gid);
#endif /* !SYS_setgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setgid]]]*/

/*[[[head:libc_fork,hash:CRC-32=0x2f1aa539]]]*/
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
INTERN ATTR_SECTION(".text.crt.sched.access") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_fork)(void)
/*[[[body:libc_fork]]]*/
{
	pid_t result;
	result = sys_fork();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fork]]]*/

/*[[[head:libc_alarm,hash:CRC-32=0x38df66e8]]]*/
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass `0' for `seconds' to disable a previously scheduled alarm */
INTERN ATTR_SECTION(".text.crt.system.utility") unsigned int
NOTHROW_NCX(LIBCCALL libc_alarm)(unsigned int seconds)
/*[[[body:libc_alarm]]]*/
{
	syscall_ulong_t result;
	result = sys_alarm(seconds);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_alarm]]]*/

/*[[[head:libc_pause,hash:CRC-32=0x69734833]]]*/
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_pause)(void)
/*[[[body:libc_pause]]]*/
{
	errno_t result;
	result = sys_pause();
	return (int)libc_seterrno(-result);
}
/*[[[end:libc_pause]]]*/

PRIVATE ATTR_SECTION(".bss.crt.io.tty.ttyname_buffer") char ttyname_buffer[32];

/*[[[head:libc_ttyname,hash:CRC-32=0x276e3f5]]]*/
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_ttyname)(fd_t fd)
/*[[[body:libc_ttyname]]]*/
{
	if unlikely(libc_ttyname_r(fd, ttyname_buffer, sizeof(ttyname_buffer)))
		return NULL;
	return ttyname_buffer;
}
/*[[[end:libc_ttyname]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.io.tty.devpath") char const devpath[] = "/dev";

/*[[[head:libc_ttyname_r,hash:CRC-32=0x47a8f874]]]*/
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_ttyname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen)
/*[[[body:libc_ttyname_r]]]*/
{
	if unlikely(!libc_isatty(fd)) {
		libc_seterrno(ENOTTY);
		return ENOTTY;
	}
	/* Simply try to realpath() the given `fd' */
	{
		ssize_t reqlen;
		reqlen = sys_frealpath4(fd, buf, buflen, AT_READLINK_REQSIZE);
		if unlikely(E_ISERR(reqlen))
			goto fallback; /* Shouldn't happen... */
		/* Check if the buffer was large enough */
		if unlikely((size_t)reqlen > buflen) {
			libc_seterrno(ERANGE);
			return ERANGE;
		}
		/* Found it! */
		return 0;
	}
	/* Fallback: Search `/dev' for the proper file */
fallback:
	{
		struct stat64 st;
		struct dirent *d;
		DIR *dirstream;
		int safe;
		dev_t rdev;
		ino_t ino;
		if unlikely(buflen < (COMPILER_STRLEN(devpath) + 1) * sizeof(char)) {
			libc_seterrno(ERANGE);
			return ERANGE;
		}
		if unlikely(fstat64(fd, &st) < 0)
			return libc_geterrno();
		if ((dirstream = opendir(devpath)) == NULL)
			return libc_geterrno();
		memcpy(buf, devpath, COMPILER_STRLEN(devpath), sizeof(char));
		buf[COMPILER_STRLEN(devpath)] = '/';
		buflen -= (COMPILER_STRLEN(devpath) + 1) * sizeof(char);
		safe = libc_geterrno();
		rdev = st.st_dev;
		ino  = st.st_ino;
		while ((d = readdir(dirstream)) != NULL) {
			size_t needed;
			/* We need a character device. */
			if (d->d_type != DT_CHR)
				continue;
			if (d->d_ino != ino)
				continue;
#if 0 /* These are symlinks (DT_LNK), so we've already skipped them ;) */
			{
				PRIVATE ATTR_SECTION(".rodata.crt.io.tty.str_stdin")  char const str_stdin[] = "stdin";
				PRIVATE ATTR_SECTION(".rodata.crt.io.tty.str_stdout") char const str_stdout[] = "stdout";
				PRIVATE ATTR_SECTION(".rodata.crt.io.tty.str_stderr") char const str_stderr[] = "stderr";
				/* Ignore the /dev/std(in|out|err) aliases */
				if (strcmp(d->d_name, str_stdin) == 0)
					continue;
				if (strcmp(d->d_name, str_stdout) == 0)
					continue;
				if (strcmp(d->d_name, str_stderr) == 0)
					continue;
			}
#endif
			needed = _D_EXACT_NAMLEN(d);
			if (needed >= buflen) {
				closedir(dirstream);
				libc_seterrno(ERANGE);
				return ERANGE;
			}
			memcpy(&buf[sizeof(devpath)],
			       d->d_name,
			       needed + 1,
			       sizeof(char));
			if (stat64(buf, &st) != 0)
				continue;
			if (st.st_rdev != rdev)
				continue;
			if unlikely(st.st_ino != ino)
				continue;
			if unlikely(!S_ISCHR(st.st_mode))
				continue;
			/* Found it! */
			closedir(dirstream);
			libc_seterrno(safe);
			return 0;
		}
		closedir(dirstream);
		libc_seterrno(safe);
	}
	return ENOTTY;
}
/*[[[end:libc_ttyname_r]]]*/

/*[[[head:libc_tcgetpgrp,hash:CRC-32=0x92b5b83e]]]*/
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_tcgetpgrp)(fd_t fd)
/*[[[body:libc_tcgetpgrp]]]*/
{
	pid_t result;
	if (ioctl(fd, TIOCGPGRP, &result) < 0)
		result = -1;
	return result;
}
/*[[[end:libc_tcgetpgrp]]]*/

/*[[[head:libc_tcsetpgrp,hash:CRC-32=0xfc6f4045]]]*/
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcsetpgrp)(fd_t fd,
                                     pid_t pgrp_id)
/*[[[body:libc_tcsetpgrp]]]*/
{
	return ioctl(fd, TIOCSPGRP, &pgrp_id) < 0 ? -1 : 0;
}
/*[[[end:libc_tcsetpgrp]]]*/



/*[[[head:libc_setlogin,hash:CRC-32=0x6accf5bf]]]*/
/* >> setlogin(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_setlogin)(char const *name)
/*[[[body:libc_setlogin]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("setlogin(%q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setlogin]]]*/

/*[[[head:libc_chown,hash:CRC-32=0xd604eb29]]]*/
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chown)(char const *file,
                                 uid_t owner,
                                 gid_t group)
/*[[[body:libc_chown]]]*/
{
	errno_t result;
#ifdef __NR_chown32
	result = sys_chown32(file, (uint32_t)owner, (uint32_t)group);
#else /* __NR_chown32 */
	result = sys_chown(file, (uint32_t)owner, (uint32_t)group);
#endif /* !__NR_chown32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chown]]]*/

/*[[[head:libc_link,hash:CRC-32=0xf1911c10]]]*/
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_link)(char const *from,
                                char const *to)
/*[[[body:libc_link]]]*/
{
	errno_t result;
	result = sys_link(from, to);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_link]]]*/

/*[[[head:libc_read,hash:CRC-32=0x760af5fb]]]*/
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_read)(fd_t fd,
                                void *buf,
                                size_t bufsize)
/*[[[body:libc_read]]]*/
{
	ssize_t result;
	result = sys_read(fd, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_read]]]*/

/*[[[head:libc_write,hash:CRC-32=0x77a5c27]]]*/
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_write)(fd_t fd,
                                 void const *buf,
                                 size_t bufsize)
/*[[[body:libc_write]]]*/
{
	ssize_t result;
	result = sys_write(fd, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_write]]]*/

/*[[[head:libc_lseek,hash:CRC-32=0xf5643ece]]]*/
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTERN ATTR_SECTION(".text.crt.io.seek") off_t
NOTHROW_NCX(LIBCCALL libc_lseek)(fd_t fd,
                                 off_t offset,
                                 __STDC_INT_AS_UINT_T whence)
/*[[[body:libc_lseek]]]*/
{
	off_t result;
#ifdef __NR_lseek
	result = sys_lseek(fd, (int32_t)offset, whence);
#else /* __NR_lseek */
	result = sys_lseek64(fd, (int64_t)offset, whence);
#endif /* !__NR_lseek */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lseek]]]*/

/*[[[head:libc_dup2,hash:CRC-32=0x7ac90214]]]*/
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
INTERN ATTR_SECTION(".text.crt.io.access") fd_t
NOTHROW_NCX(LIBCCALL libc_dup2)(fd_t oldfd,
                                fd_t newfd)
/*[[[body:libc_dup2]]]*/
{
	fd_t result;
	result = sys_dup2(oldfd, newfd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup2]]]*/

/*[[[head:libc_dup,hash:CRC-32=0x9db26688]]]*/
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_dup)(fd_t fd)
/*[[[body:libc_dup]]]*/
{
	fd_t result;
	result = sys_dup(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup]]]*/

/*[[[head:libc_close,hash:CRC-32=0x30df5919]]]*/
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
INTERN ATTR_SECTION(".text.crt.io.access") int
NOTHROW_NCX(LIBCCALL libc_close)(fd_t fd)
/*[[[body:libc_close]]]*/
{
	errno_t result;
	result = sys_close(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_close]]]*/

/*[[[head:libc_access,hash:CRC-32=0x262b886e]]]*/
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_access)(char const *file,
                                  __STDC_INT_AS_UINT_T type)
/*[[[body:libc_access]]]*/
{
	errno_t result;
	result = sys_access(file, (syscall_ulong_t)(unsigned int)type);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_access]]]*/

/*[[[head:libc_chdir,hash:CRC-32=0xae25299f]]]*/
/* >> chdir(2)
 * Change the current working directory to `path' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chdir)(char const *path)
/*[[[body:libc_chdir]]]*/
{
	errno_t result;
	result = sys_chdir(path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chdir]]]*/

/*[[[head:libc_getcwd,hash:CRC-32=0xf7aeb2ae]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") char *
NOTHROW_RPC(LIBCCALL libc_getcwd)(char *buf,
                                  size_t bufsize)
/*[[[body:libc_getcwd]]]*/
{
	ssize_t result;
	char *buffer = buf;
	if (!buf) {
		if (!bufsize) {
			/* Automatically allocate + determine buffer size. */
			bufsize = PATH_MAX;
			buffer  = (char *)malloc(bufsize);
			if unlikely(!buffer)
				bufsize = 0;
			for (;;) {
				result = sys_frealpath4(AT_FDCWD,
				                        buffer,
				                        bufsize,
				                        AT_READLINK_REQSIZE);
				if unlikely(E_ISERR(result))
					goto err_buffer_result_errno;
				if likely((size_t)result <= bufsize)
					break;
				/* Allocate the required amount of memory. */
				buf = (char *)realloc(buffer, (size_t)result);
				if unlikely(!buf) {
					free(buffer);
					return NULL;
				}
				bufsize = (size_t)result;
				buffer  = buf;
			}
			if ((size_t)result != bufsize) {
				buf = (char *)realloc(buffer, (size_t)result);
				if likely(buf)
					buffer = buf;
			}
			return buffer;
		}
		buffer = (char *)malloc(bufsize);
		if unlikely(!buffer)
			goto done;
	}
	result = sys_getcwd(buffer,
	                    bufsize);
	if (E_ISERR(result)) {
		if (!buf) {
err_buffer_result_errno:
			free(buffer);
		}
		libc_seterrno(-result);
		return NULL;
	}
done:
	return buffer;
}
/*[[[end:libc_getcwd]]]*/

/*[[[head:libc_unlink,hash:CRC-32=0xf2a3ec93]]]*/
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_unlink)(char const *file)
/*[[[body:libc_unlink]]]*/
{
	errno_t result;
#ifdef __NR_unlink
	result = sys_unlink(file);
#else /* __NR_unlink */
	result = sys_unlinkat(AT_FDCWD, file, 0);
#endif /* !__NR_unlink */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_unlink]]]*/

/*[[[head:libc_rmdir,hash:CRC-32=0x51e1f733]]]*/
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_rmdir)(char const *path)
/*[[[body:libc_rmdir]]]*/
{
	errno_t result;
#ifdef __NR_rmdir
	result = sys_rmdir(path);
#else /* __NR_rmdir */
	result = sys_unlinkat(AT_FDCWD, path, AT_REMOVEDIR);
#endif /* !__NR_rmdir */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_rmdir]]]*/

/*[[[head:libc_euidaccess,hash:CRC-32=0x10962284]]]*/
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_euidaccess)(char const *file,
                                      __STDC_INT_AS_UINT_T type)
/*[[[body:libc_euidaccess]]]*/
{
	errno_t result;
	result = sys_faccessat(AT_FDCWD,
	                       file,
	                       (syscall_ulong_t)(unsigned int)type,
	                       AT_EACCESS);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_euidaccess]]]*/

/*[[[head:libc_faccessat,hash:CRC-32=0xd99c78b0]]]*/
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_faccessat)(fd_t dfd,
                                     char const *file,
                                     __STDC_INT_AS_UINT_T type,
                                     atflag_t flags)
/*[[[body:libc_faccessat]]]*/
{
	errno_t result;
	result = sys_faccessat(dfd,
	                       file,
	                       (syscall_ulong_t)(unsigned int)type,
	                       flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_faccessat]]]*/

/*[[[head:libc_fchownat,hash:CRC-32=0xfdb7221f]]]*/
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_fchownat)(fd_t dfd,
                                    char const *file,
                                    uid_t owner,
                                    gid_t group,
                                    atflag_t flags)
/*[[[body:libc_fchownat]]]*/
{
	errno_t result;
	result = sys_fchownat(dfd,
	                      file,
	                      (uint32_t)owner,
	                      (uint32_t)group,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchownat]]]*/

/*[[[head:libc_linkat,hash:CRC-32=0xc42322fe]]]*/
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2, 4)) int
NOTHROW_RPC(LIBCCALL libc_linkat)(fd_t fromfd,
                                  char const *from,
                                  fd_t tofd,
                                  char const *to,
                                  atflag_t flags)
/*[[[body:libc_linkat]]]*/
{
	errno_t result;
	result = sys_linkat(fromfd,
	                    from,
	                    tofd,
	                    to,
	                    flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_linkat]]]*/

/*[[[head:libc_symlinkat,hash:CRC-32=0x5689b9b5]]]*/
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `link_text' as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1, 3)) int
NOTHROW_RPC(LIBCCALL libc_symlinkat)(char const *link_text,
                                     fd_t tofd,
                                     char const *target_path)
/*[[[body:libc_symlinkat]]]*/
{
	errno_t result;
	result = sys_symlinkat(link_text,
	                       tofd,
	                       target_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_symlinkat]]]*/

/*[[[head:libc_readlinkat,hash:CRC-32=0x3ba8f438]]]*/
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBCCALL libc_readlinkat)(fd_t dfd,
                                      char const *path,
                                      char *buf,
                                      size_t buflen)
/*[[[body:libc_readlinkat]]]*/
{
	errno_t result;
	result = sys_readlinkat(dfd,
	                        path,
	                        buf,
	                        buflen);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_readlinkat]]]*/

/*[[[head:libc_unlinkat,hash:CRC-32=0xbd33e56e]]]*/
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_unlinkat)(fd_t dfd,
                                    char const *name,
                                    atflag_t flags)
/*[[[body:libc_unlinkat]]]*/
{
	errno_t result;
	result = sys_unlinkat(dfd,
	                      name,
	                      flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_unlinkat]]]*/

/*[[[head:libc_lseek64,hash:CRC-32=0x94399d16]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lseek64, libc_lseek);
#else /* MAGIC:alias */
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTERN ATTR_SECTION(".text.crt.io.large.seek") off64_t
NOTHROW_NCX(LIBCCALL libc_lseek64)(fd_t fd,
                                   off64_t offset,
                                   __STDC_INT_AS_UINT_T whence)
/*[[[body:libc_lseek64]]]*/
{
	off64_t result;
	result = sys_lseek64(fd,
	                     offset,
	                     whence);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_lseek64]]]*/

/*[[[head:libc_pread,hash:CRC-32=0x91b7bc1d]]]*/
/* >> pread(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pread)(fd_t fd,
                                 void *buf,
                                 size_t bufsize,
                                 __PIO_OFFSET offset)
/*[[[body:libc_pread]]]*/
{
	ssize_t result;
	result = sys_pread64(fd,
	                     buf,
	                     bufsize,
	                     (uint64_t)(uint32_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pread]]]*/

/*[[[head:libc_pwrite,hash:CRC-32=0x70ec361c]]]*/
/* >> pwrite(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwrite)(fd_t fd,
                                  void const *buf,
                                  size_t bufsize,
                                  __PIO_OFFSET offset)
/*[[[body:libc_pwrite]]]*/
{
	ssize_t result;
	result = sys_pwrite64(fd,
	                      buf,
	                      bufsize,
	                      (uint64_t)(uint32_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pwrite]]]*/

/*[[[head:libc_pread64,hash:CRC-32=0xa822560a]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pread64, libc_pread);
#else /* MAGIC:alias */
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.io.large.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pread64)(fd_t fd,
                                   void *buf,
                                   size_t bufsize,
                                   __PIO_OFFSET64 offset)
/*[[[body:libc_pread64]]]*/
{
	ssize_t result;
	result = sys_pread64(fd,
	                     buf,
	                     bufsize,
	                     (uint64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pread64]]]*/

/*[[[head:libc_pwrite64,hash:CRC-32=0xbd5df9c6]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwrite64, libc_pwrite);
#else /* MAGIC:alias */
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.io.large.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwrite64)(fd_t fd,
                                    void const *buf,
                                    size_t bufsize,
                                    __PIO_OFFSET64 offset)
/*[[[body:libc_pwrite64]]]*/
{
	ssize_t result;
	result = sys_pwrite64(fd,
	                      buf,
	                      bufsize,
	                      (uint64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pwrite64]]]*/

/*[[[head:libc_pipe2,hash:CRC-32=0x9bb86b5]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_pipe2)(fd_t pipedes[2],
                                 oflag_t flags)
/*[[[body:libc_pipe2]]]*/
{
	errno_t result;
	result = sys_pipe2(pipedes,
	                   flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pipe2]]]*/

/*[[[head:libc_dup3,hash:CRC-32=0x88bdc54a]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") fd_t
NOTHROW_NCX(LIBCCALL libc_dup3)(fd_t oldfd,
                                fd_t newfd,
                                oflag_t flags)
/*[[[body:libc_dup3]]]*/
{
	fd_t result;
	result = sys_dup3(oldfd,
	                  newfd,
	                  flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup3]]]*/

/*[[[head:libc_get_current_dir_name,hash:CRC-32=0x4c0969ed]]]*/
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_MALLOC WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_get_current_dir_name)(void)
/*[[[body:libc_get_current_dir_name]]]*/
{
	return getcwd(NULL, 0);
}
/*[[[end:libc_get_current_dir_name]]]*/


PRIVATE ATTR_NOINLINE int LIBCCALL
group_member_impl(gid_t gid, unsigned int bufsize) {
	int n; unsigned int i;
	gid_t *groups;
	groups = (gid_t *)alloca(bufsize * sizeof(*groups));
	n = getgroups((int)bufsize, groups);
	if unlikely(n < 0)
		return n;
	for (i = 0; i < (unsigned int)n; ++i) {
		if (groups[i] == gid)
			return 1;
	}
	return 0;
}

/*[[[head:libc_group_member,hash:CRC-32=0x8c8ecfec]]]*/
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_group_member)(gid_t gid)
/*[[[body:libc_group_member]]]*/
{
	int result;
#if !defined(NGROUPS_MAX) || NGROUPS_MAX > 32
	unsigned int size = 32;
#else /* !NGROUPS_MAX || NGROUPS_MAX > 32 */
	unsigned int size = NGROUPS_MAX;
#endif /* NGROUPS_MAX && NGROUPS_MAX <= 32 */
	while ((result = group_member_impl(gid, size)) < 0 &&
	       libc_geterrno() == EINVAL)
		size *= 2;
	return result;
}
/*[[[end:libc_group_member]]]*/

/*[[[head:libc_getresuid,hash:CRC-32=0x5ba5736d]]]*/
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_getresuid)(uid_t *ruid,
                                     uid_t *euid,
                                     uid_t *suid)
/*[[[body:libc_getresuid]]]*/
{
	errno_t result;
#ifdef SYS_getresuid32
	result = sys_getresuid32((uint32_t *)ruid,
	                         (uint32_t *)euid,
	                         (uint32_t *)suid);
#else /* SYS_getresuid32 */
	result = sys_getresuid(ruid, euid, suid);
#endif /* !SYS_getresuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getresuid]]]*/

/*[[[head:libc_getresgid,hash:CRC-32=0xa6a58713]]]*/
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_getresgid)(gid_t *rgid,
                                     gid_t *egid,
                                     gid_t *sgid)
/*[[[body:libc_getresgid]]]*/
{
	errno_t result;
#ifdef SYS_getresgid32
	result = sys_getresgid32((uint32_t *)rgid,
	                         (uint32_t *)egid,
	                         (uint32_t *)sgid);
#else /* SYS_getresgid32 */
	result = sys_getresgid(rgid, egid, sgid);
#endif /* !SYS_getresgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getresgid]]]*/

/*[[[head:libc_setresuid,hash:CRC-32=0x3482425f]]]*/
/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setresuid)(uid_t ruid,
                                     uid_t euid,
                                     uid_t suid)
/*[[[body:libc_setresuid]]]*/
{
	errno_t result;
#ifdef SYS_setresuid32
	result = sys_setresuid32((uint32_t)ruid,
	                         (uint32_t)euid,
	                         (uint32_t)suid);
#else /* SYS_setresuid32 */
	result = sys_setresuid(ruid, euid, suid);
#endif /* !SYS_setresuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setresuid]]]*/

/*[[[head:libc_setresgid,hash:CRC-32=0xddb24490]]]*/
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setresgid)(gid_t rgid,
                                     gid_t egid,
                                     gid_t sgid)
/*[[[body:libc_setresgid]]]*/
{
	errno_t result;
#ifdef SYS_setresgid32
	result = sys_setresgid32((uint32_t)rgid,
	                         (uint32_t)egid,
	                         (uint32_t)sgid);
#else /* SYS_setresgid32 */
	result = sys_setresgid(rgid, egid, sgid);
#endif /* !SYS_setresgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setresgid]]]*/

/*[[[head:libc_usleep,hash:CRC-32=0xe9ff7436]]]*/
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_usleep)(useconds_t useconds)
/*[[[body:libc_usleep]]]*/
{
	struct timespec ts;
	ts.tv_sec  = (time_t)(useconds / USEC_PER_SEC);
	ts.tv_nsec = (syscall_ulong_t)(useconds % USEC_PER_SEC) * NSEC_PER_USEC;
	return nanosleep(&ts, NULL);
}
/*[[[end:libc_usleep]]]*/

/*[[[head:libc_getwd,hash:CRC-32=0x411bae1b]]]*/
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_DEPRECATED("Use getcwd()") NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_getwd)(char *buf)
/*[[[body:libc_getwd]]]*/
{
	return getcwd(buf, (size_t)-1);
}
/*[[[end:libc_getwd]]]*/

/*[[[head:libc_ualarm,hash:CRC-32=0x3b758142]]]*/
INTERN ATTR_SECTION(".text.crt.system.utility") useconds_t
NOTHROW_NCX(LIBCCALL libc_ualarm)(useconds_t value,
                                  useconds_t interval)
/*[[[body:libc_ualarm]]]*/
{
	struct itimerval timer, otimer;
	timer.it_value.tv_sec     = value / 1000000;
	timer.it_value.tv_usec    = value % 1000000;
	timer.it_interval.tv_sec  = interval / 1000000;
	timer.it_interval.tv_usec = interval % 1000000;
	if (setitimer(ITIMER_REAL, &timer, &otimer) < 0)
		goto err;
	return (otimer.it_value.tv_sec * 1000000) +
	       (otimer.it_value.tv_usec);
err:
	return (useconds_t)-1;
}
/*[[[end:libc_ualarm]]]*/

/*[[[head:libc_fchown,hash:CRC-32=0x91a498d1]]]*/
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
INTERN ATTR_SECTION(".text.crt.fs.modify") int
NOTHROW_RPC(LIBCCALL libc_fchown)(fd_t fd,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libc_fchown]]]*/
{
	errno_t result;
#ifdef __NR_fchown32
	result = sys_fchown32(fd,
	                      (uint32_t)owner,
	                      (uint32_t)group);
#else /* __NR_fchown32 */
	result = sys_fchown(fd,
	                    (uint32_t)owner,
	                    (uint32_t)group);
#endif /* !__NR_fchown32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchown]]]*/

/*[[[head:libc_fchdir,hash:CRC-32=0x47010fa5]]]*/
/* >> chdir(2)
 * Change the current working directory to `path' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") int
NOTHROW_RPC(LIBCCALL libc_fchdir)(fd_t fd)
/*[[[body:libc_fchdir]]]*/
{
	errno_t result;
	result = sys_fchdir(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchdir]]]*/

/*[[[head:libc_getpgid,hash:CRC-32=0x5ffda70]]]*/
/* >> getpgid(2)
 * Return the ID of the process group associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getpgid)(pid_t pid)
/*[[[body:libc_getpgid]]]*/
{
	pid_t result;
	result = sys_getpgid(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getpgid]]]*/

/*[[[head:libc_getsid,hash:CRC-32=0xe542b6c7]]]*/
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getsid)(pid_t pid)
/*[[[body:libc_getsid]]]*/
{
	pid_t result;
	result = sys_getsid(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getsid]]]*/

/*[[[head:libc_lchown,hash:CRC-32=0x65b469a0]]]*/
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if that file is a symbolic link */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_lchown)(char const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libc_lchown]]]*/
{
	errno_t result;
#ifdef __NR_lchown32
	result = sys_lchown32(file,
	                      (uint32_t)owner,
	                      (uint32_t)group);
#else /* __NR_lchown32 */
	result = sys_lchown(file,
	                    (uint32_t)owner,
	                    (uint32_t)group);
#endif /* !__NR_lchown32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lchown]]]*/

/*[[[head:libc_truncate,hash:CRC-32=0x7c24ef0]]]*/
/* >> truncate(2)
 * Truncate the given file `file' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_truncate)(char const *file,
                                    __PIO_OFFSET length)
/*[[[body:libc_truncate]]]*/
{
	errno_t result;
	result = sys_truncate(file,
	                      (uint32_t)length);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_truncate]]]*/

/*[[[head:libc_truncate64,hash:CRC-32=0x7bf49012]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_truncate64, libc_truncate);
#else /* MAGIC:alias */
/* >> truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_truncate64)(char const *file,
                                      __PIO_OFFSET64 length)
/*[[[body:libc_truncate64]]]*/
{
	errno_t result;
	result = sys_truncate64(file,
	                        (uint64_t)length);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_truncate64]]]*/

/*[[[head:libc_fexecve,hash:CRC-32=0xac08f77f]]]*/
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `fd' and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((2, 3)) int
NOTHROW_RPC(LIBCCALL libc_fexecve)(fd_t fd,
                                   __TARGV,
                                   __TENVP)
/*[[[body:libc_fexecve]]]*/
{
	errno_t error;
	error = sys_execveat(fd,
	                     "",
	                     (char const *const *)___argv,
	                     (char const *const *)___envp,
	                     AT_EMPTY_PATH);
	return (int)libc_seterrno(-error);
}
/*[[[end:libc_fexecve]]]*/

/*[[[head:libc_setpgrp,hash:CRC-32=0xeef27930]]]*/
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTERN ATTR_SECTION(".text.crt.sched.process") int
NOTHROW_NCX(LIBCCALL libc_setpgrp)(void)
/*[[[body:libc_setpgrp]]]*/
{
	errno_t error;
	error = sys_setpgid(0, 0);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setpgrp]]]*/

/*[[[head:libc_setreuid,hash:CRC-32=0xb1ea64ca]]]*/
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setreuid)(uid_t ruid,
                                    uid_t euid)
/*[[[body:libc_setreuid]]]*/
{
	errno_t error;
#ifdef SYS_setreuid32
	error = sys_setreuid32((uint32_t)ruid,
	                       (uint32_t)euid);
#else /* SYS_setreuid32 */
	error = sys_setreuid(ruid, euid);
#endif /* !SYS_setreuid32 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setreuid]]]*/

/*[[[head:libc_setregid,hash:CRC-32=0xd668752]]]*/
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setregid)(gid_t rgid,
                                    gid_t egid)
/*[[[body:libc_setregid]]]*/
{
	errno_t error;
#ifdef SYS_setregid32
	error = sys_setregid32((uint32_t)rgid,
	                       (uint32_t)egid);
#else /* SYS_setregid32 */
	error = sys_setregid(rgid, egid);
#endif /* !SYS_setregid32 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setregid]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.system.configuration.hostid_pathname") char const hostid_pathname[] = "/etc";
PRIVATE ATTR_SECTION(".rodata.crt.system.configuration.hostid_filename") char const hostid_filename[] = "/etc/hostid";

/*[[[head:libc_gethostid,hash:CRC-32=0xd6c89d9b]]]*/
/* >> gethostid(3) */
INTERN ATTR_SECTION(".text.crt.system.configuration") WUNUSED longptr_t
NOTHROW_NCX(LIBCCALL libc_gethostid)(void)
/*[[[body:libc_gethostid]]]*/
{
	fd_t fd;
	uint32_t id32;
	fd = sys_open(hostid_filename, O_RDONLY, 0);
	if (fd >= 0) {
		ssize_t count;
		count = readall(fd, &id32, 4);
		sys_close(fd);
		if (count == 4)
			return (long int)(unsigned long int)id32;
	}
	/* XXX: Glibc also tries to use the host's IP address here... */
	return 0;
}
/*[[[end:libc_gethostid]]]*/

/*[[[head:libc_sethostid,hash:CRC-32=0xb3db0ff1]]]*/
/* >> sethostid(3) */
INTERN ATTR_SECTION(".text.crt.system.configuration") int
NOTHROW_NCX(LIBCCALL libc_sethostid)(longptr_t id)
/*[[[body:libc_sethostid]]]*/
{
	fd_t fd;
	ssize_t count;
	uint32_t id32;
#if __SIZEOF_LONG__ > 4
	if (id & ~UINT32_C(0xffffffff))
		return libc_seterrno(EOVERFLOW);
#endif /* __SIZEOF_LONG__ > 4 */
	fd = sys_open(hostid_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0) {
		if (fd == -ENOTDIR) {
			/* Check if /etc was already created. */
			fd = sys_mkdir(hostid_pathname, 0755);
			if (fd == -EOK || fd == -EEXIST) {
				fd = sys_open(hostid_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (fd >= 0)
					goto got_fd;
			}
		}
		return libc_seterrno_syserr(fd);
	}
got_fd:
	id32  = (uint32_t)(unsigned long int)id;
	count = writeall(fd, &id32, 4);
	sys_close(fd);
	if (count <= 0) {
		if (!count)
			libc_seterrno(ENOSPC); /* ??? */
		return -1;
	}
	return 0;
}
/*[[[end:libc_sethostid]]]*/

/*[[[head:libc_seteuid,hash:CRC-32=0x14fcb70c]]]*/
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_seteuid)(uid_t euid)
/*[[[body:libc_seteuid]]]*/
{
	errno_t error;
#ifdef SYS_getresuid32
	uint32_t ruid;
	error = sys_getresuid32(&ruid, NULL, NULL);
#else /* SYS_getresuid32 */
	uid_t ruid;
	error = sys_getresuid(&ruid, NULL, NULL);
#endif /* !SYS_getresuid32 */
	if (E_ISOK(error)) {
#ifdef SYS_setreuid32
		error = sys_setreuid32(ruid, (uint32_t)euid);
#else /* SYS_setreuid32 */
		error = sys_setreuid(ruid, euid);
#endif /* !SYS_setreuid32 */
	}
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_seteuid]]]*/

/*[[[head:libc_setegid,hash:CRC-32=0x5114f16d]]]*/
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setegid)(gid_t egid)
/*[[[body:libc_setegid]]]*/
{
	errno_t error;
#ifdef SYS_getresgid32
	uint32_t rgid;
	error = sys_getresgid32(&rgid, NULL, NULL);
#else /* SYS_getresgid32 */
	gid_t rgid;
	error = sys_getresgid(&rgid, NULL, NULL);
#endif /* !SYS_getresgid32 */
	if (E_ISOK(error)) {
#ifdef SYS_setregid32
		error = sys_setregid32(rgid, (uint32_t)egid);
#else /* SYS_setregid32 */
		error = sys_setregid(rgid, egid);
#endif /* !SYS_setregid32 */
	}
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setegid]]]*/

/*[[[head:libc_ttyslot,hash:CRC-32=0xed7869b6]]]*/
/* >> ttyslot(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_ttyslot)(void)
/*[[[body:libc_ttyslot]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("ttyslot"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ttyslot]]]*/

/*[[[head:libc_symlink,hash:CRC-32=0x386d6ca5]]]*/
/* >> symlink(3)
 * Create a new symbolic link loaded with `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_symlink)(char const *link_text,
                                   char const *target_path)
/*[[[body:libc_symlink]]]*/
{
	errno_t result;
	result = sys_symlink(link_text, target_path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_symlink]]]*/

/*[[[head:libc_readlink,hash:CRC-32=0xb933789e]]]*/
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((1, 2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_readlink)(char const *path,
                                    char *buf,
                                    size_t buflen)
/*[[[body:libc_readlink]]]*/
{
	ssize_t result;
	result = sys_readlink(path, buf, buflen);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_readlink]]]*/

/*[[[head:libc_gethostname,hash:CRC-32=0xd7e1249d]]]*/
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_gethostname)(char *name,
                                       size_t buflen)
/*[[[body:libc_gethostname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if (result == 0) {
		size_t len = strnlen(uts.nodename, _UTSNAME_NODENAME_LENGTH);
		if (buflen <= len) {
			/* EINVAL For getdomainname() under libc: name is NULL or name is longer than len bytes. */
			return (int)libc_seterrno(EINVAL);
		}
		memcpy(name, uts.nodename, len, sizeof(char));
		name[len] = '\0';
	}
	return result;
}
/*[[[end:libc_gethostname]]]*/

/*[[[head:libc_sethostname,hash:CRC-32=0x60798dac]]]*/
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sethostname)(char const *name,
                                       size_t len)
/*[[[body:libc_sethostname]]]*/
{
	errno_t result;
	result = sys_sethostname(name, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sethostname]]]*/

/*[[[head:libc_getdomainname,hash:CRC-32=0x973a241a]]]*/
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_getdomainname)(char *name,
                                         size_t buflen)
/*[[[body:libc_getdomainname]]]*/
{
	struct utsname uts;
	int result = uname(&uts);
	if (result == 0) {
		size_t len = strnlen(uts.domainname, _UTSNAME_DOMAIN_LENGTH);
		if (buflen <= len) {
			/* EINVAL For getdomainname() under libc: name is NULL or name is longer than len bytes. */
			return (int)libc_seterrno(EINVAL);
		}
		memcpy(name, uts.domainname, len, sizeof(char));
		name[len] = '\0';
	}
	return result;
}
/*[[[end:libc_getdomainname]]]*/

/*[[[head:libc_setdomainname,hash:CRC-32=0xde26f8ae]]]*/
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN ATTR_SECTION(".text.crt.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_setdomainname)(char const *name,
                                         size_t len)
/*[[[body:libc_setdomainname]]]*/
{
	errno_t result;
	result = sys_setdomainname(name, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setdomainname]]]*/

/*[[[head:libc_vhangup,hash:CRC-32=0x30a39db6]]]*/
/* >> vhangup(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_vhangup)(void)
/*[[[body:libc_vhangup]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("vhangup"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_vhangup]]]*/

/*[[[head:libc_profil,hash:CRC-32=0x48b90317]]]*/
/* >> profil(3) */
INTERN ATTR_SECTION(".text.crt.system.utility") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_profil)(uint16_t *sample_buffer,
                                  size_t size,
                                  size_t offset,
                                  unsigned int scale)
/*[[[body:libc_profil]]]*/
{
#ifdef SYS_profil
	errno_t result;
	result = sys_profil((uint16_t *)sample_buffer,
	                    size,
	                    offset,
	                    (syscall_ulong_t)scale);
	return libc_seterrno_syserr(result);
#else /* SYS_profil */
	(void)sample_buffer;
	(void)size;
	(void)offset;
	(void)scale;
	return libc_seterrno(ENOSYS);
#endif /* !SYS_profil */
}
/*[[[end:libc_profil]]]*/

/*[[[head:libc_getusershell,hash:CRC-32=0x620a6b9c]]]*/
/* >> getusershell(3) */
INTERN ATTR_SECTION(".text.crt.database.shell") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_getusershell)(void)
/*[[[body:libc_getusershell]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getusershell"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getusershell]]]*/

/*[[[head:libc_endusershell,hash:CRC-32=0xd5d53e38]]]*/
/* >> endusershell(3) */
INTERN ATTR_SECTION(".text.crt.database.shell") void
NOTHROW_NCX(LIBCCALL libc_endusershell)(void)
/*[[[body:libc_endusershell]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endusershell"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endusershell]]]*/

/*[[[head:libc_setusershell,hash:CRC-32=0xdab349fb]]]*/
/* >> setusershell(3) */
INTERN ATTR_SECTION(".text.crt.database.shell") void
NOTHROW_RPC(LIBCCALL libc_setusershell)(void)
/*[[[body:libc_setusershell]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setusershell"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setusershell]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.system.utility.root") char const root[] = "/";
PRIVATE ATTR_SECTION(".rodata.crt.system.utility.dev_null") char const dev_null[] = "/dev/null";

/*[[[head:libc_daemon,hash:CRC-32=0xbc774599]]]*/
/* >> daemon(3) */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_daemon)(__STDC_INT_AS_UINT_T nochdir,
                                  __STDC_INT_AS_UINT_T noclose)
/*[[[body:libc_daemon]]]*/
{
	pid_t cpid;
	cpid = fork();
	if (cpid < 0)
		return -1;
	if (cpid != 0)
		_Exit(0); /* The parent process dies. */
	if (setsid() < 0)
		return -1;
	if (!nochdir)
		chdir(root);
	if (!noclose) {
		fd_t i, nul = open(dev_null, O_RDWR);
		if (nul < 0)
			return -1;
		/* NOTE: Glibc does an additional check to ensure that `nul'  really
		 *       is a character-device with the  correct dev_t. We could  do
		 *       that as well, however I'd consider a system where /dev/null
		 *       isn't actually /dev/null to  already be broken... (and  the
		 *       check only adds unnecessary overhead if you ask me) */
		for (i = 0; i < 3; ++i) {
			if (nul != i)
				sys_dup2(nul, i);
		}
		if (nul >= 3)
			sys_close(nul);
	}
	return 0;
}
/*[[[end:libc_daemon]]]*/

/*[[[head:libc_revoke,hash:CRC-32=0x96b7f405]]]*/
/* >> revoke(3) */
INTERN ATTR_SECTION(".text.crt.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_revoke)(char const *file)
/*[[[body:libc_revoke]]]*/
/*AUTO*/{
	(void)file;
	CRT_UNIMPLEMENTEDF("revoke(%q)", file); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_revoke]]]*/

/* `vfork' needs to be implemented in assembly! */
/*[[[skip:libc_vfork]]]*/

/* `syscall' needs to be implemented in assembly! */
/*[[[skip:libc_syscall]]]*/
/*[[[skip:libc_syscall64]]]*/

/*[[[head:libc_chroot,hash:CRC-32=0xc5ab98aa]]]*/
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTERN ATTR_SECTION(".text.crt.fs.utility") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_chroot)(char const *__restrict path)
/*[[[body:libc_chroot]]]*/
{
	errno_t result;
	result = sys_chroot(path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chroot]]]*/


/*[[[head:libc_ftruncate,hash:CRC-32=0xcd4e0d6b]]]*/
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.io.write") int
NOTHROW_NCX(LIBCCALL libc_ftruncate)(fd_t fd,
                                     __PIO_OFFSET length)
/*[[[body:libc_ftruncate]]]*/
{
	errno_t result;
	result = sys_ftruncate(fd, (uint32_t)length);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_ftruncate]]]*/

/*[[[head:libc_ftruncate64,hash:CRC-32=0x4d1db1cd]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_ftruncate64, libc_ftruncate);
#else /* MAGIC:alias */
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.io.large.write") int
NOTHROW_NCX(LIBCCALL libc_ftruncate64)(fd_t fd,
                                       __PIO_OFFSET64 length)
/*[[[body:libc_ftruncate64]]]*/
{
	errno_t result;
	result = sys_ftruncate64(fd, (uint64_t)length);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftruncate64]]]*/


PRIVATE byte_t *brk_curr = NULL;
PRIVATE struct atomic_lock brk_lock = ATOMIC_LOCK_INIT;

PRIVATE int LIBCCALL do_brk(void *addr) {
	byte_t *real_oldbrk, *real_newbrk;
	if ((real_oldbrk = brk_curr) == NULL) {
		/* Lookup the end address of the main executable
		 * NOTE: We do this lazily to prevent the necessity of a `R_386_GLOB_DAT' relocation */
		void *temp = dlsym(RTLD_DEFAULT, "_end");
		if unlikely(!temp && dlerror())
			goto err_perm;
		real_oldbrk = (byte_t *)CEIL_ALIGN((uintptr_t)temp, OS_PAGESIZE);
	} else {
		real_oldbrk = (byte_t *)CEIL_ALIGN((uintptr_t)real_oldbrk, OS_PAGESIZE);
	}
	real_newbrk = (byte_t *)CEIL_ALIGN((uintptr_t)addr, OS_PAGESIZE);
	if (real_newbrk < real_oldbrk) {
		/* Release memory */
		if unlikely(munmap(real_newbrk, real_oldbrk - real_newbrk) == -1)
			goto err;
	} else if (real_newbrk > real_oldbrk) {
		void *map_result;
		/* Allocate more memory */
		map_result = mmap(real_oldbrk,
		                  real_newbrk - real_oldbrk,
		                  PROT_READ | PROT_WRITE,
		                  MAP_FIXED | MAP_ANONYMOUS,
		                  -1,
		                  0);
		if unlikely(map_result == MAP_FAILED)
			goto err;
		assertf(map_result == real_oldbrk,
		        "%p != %p",
		        map_result,
		        real_oldbrk);
	}
	brk_curr = (byte_t *)addr;
	return 0;
err_perm:
	libc_seterrno(EPERM);
err:
	return -1;
}


/*[[[head:libc_brk,hash:CRC-32=0xcf35a87e]]]*/
/* >> brk(2), sbrk(2)
 * Change the program break, allowing for a rudimentary implementation of a heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTERN ATTR_SECTION(".text.crt.heap.utility") int
NOTHROW_NCX(LIBCCALL libc_brk)(void *addr)
/*[[[body:libc_brk]]]*/
{
	int result;
	atomic_lock_acquire(&brk_lock);
	result = do_brk(addr);
	atomic_lock_release(&brk_lock);
	return result;
}
/*[[[end:libc_brk]]]*/

/*[[[head:libc_sbrk,hash:CRC-32=0x89be8296]]]*/
/* >> brk(2), sbrk(2)
 * Change the program break, allowing for a rudimentary implementation of a heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTERN ATTR_SECTION(".text.crt.heap.utility") void *
NOTHROW_NCX(LIBCCALL libc_sbrk)(intptr_t delta)
/*[[[body:libc_sbrk]]]*/
{
	byte_t *result;
	atomic_lock_acquire(&brk_lock);
	if ((result = brk_curr) == NULL) {
		/* Lookup the end address of the main executable
		 * NOTE: We do this lazily to prevent the necessity of a relocation */
		void *temp = dlsym(RTLD_DEFAULT, "_end");
		if unlikely(!temp && dlerror())
			goto err_perm;
		result = (byte_t *)CEIL_ALIGN((uintptr_t)temp, OS_PAGESIZE);
	}
	if (do_brk(result + delta) != 0)
		result = (byte_t *)-1;
	atomic_lock_release(&brk_lock);
	return result;
err_perm:
	atomic_lock_release(&brk_lock);
	libc_seterrno(EPERM);
	return NULL;
}
/*[[[end:libc_sbrk]]]*/


#define PATHCONF_VARYING_LIMIT INTPTR_MIN
PRIVATE ATTR_SECTION(".rodata.crt.fs.property") longptr_t const pc_constants[] = {
	[_PC_LINK_MAX]           = PATHCONF_VARYING_LIMIT,
	[_PC_MAX_CANON]          = PATHCONF_VARYING_LIMIT,
	[_PC_MAX_INPUT]          = PATHCONF_VARYING_LIMIT,
	[_PC_NAME_MAX]           = PATHCONF_VARYING_LIMIT,
	[_PC_PATH_MAX]           = PATH_MAX,
	[_PC_PIPE_BUF]           = PIPE_BUF,
	[_PC_CHOWN_RESTRICTED]   = _POSIX_CHOWN_RESTRICTED,
	[_PC_NO_TRUNC]           = _POSIX_NO_TRUNC,
	[_PC_VDISABLE]           = 1, /* All   KOS  terminals  support  disabling  control  characters.  All
	                               * related functionality is implemented in `/kos/src/libterm/termio.c' */
#ifdef _POSIX_SYNC_IO
	[_PC_SYNC_IO]            = _POSIX_SYNC_IO,
#else /* _POSIX_SYNC_IO */
	[_PC_SYNC_IO]            = -1,
#endif /* !_POSIX_SYNC_IO */
#ifdef _POSIX_ASYNC_IO
	[_PC_ASYNC_IO]           = _POSIX_ASYNC_IO,
#else /* _POSIX_ASYNC_IO */
	[_PC_ASYNC_IO]           = -1,
#endif /* !_POSIX_ASYNC_IO */
#ifdef _POSIX_PRIO_IO
	[_PC_PRIO_IO]            = _POSIX_PRIO_IO,
#else /* _POSIX_PRIO_IO */
	[_PC_PRIO_IO]            = -1,
#endif /* !_POSIX_PRIO_IO */
	[_PC_SOCK_MAXBUF]        = -1,
	[_PC_FILESIZEBITS]       = PATHCONF_VARYING_LIMIT,
	[_PC_REC_INCR_XFER_SIZE] = PATHCONF_VARYING_LIMIT,
	[_PC_REC_MAX_XFER_SIZE]  = PATHCONF_VARYING_LIMIT,
	[_PC_REC_MIN_XFER_SIZE]  = PATHCONF_VARYING_LIMIT,
	[_PC_REC_XFER_ALIGN]     = PATHCONF_VARYING_LIMIT,
	[_PC_ALLOC_SIZE_MIN]     = PATHCONF_VARYING_LIMIT,
	[_PC_SYMLINK_MAX]        = PATHCONF_VARYING_LIMIT,
	[_PC_2_SYMLINKS]         = PATHCONF_VARYING_LIMIT,
	/* What about `_PC_TIMESTAMP_RESOLUTION'? */
	// XXX: _PC_ACL_ENABLED
	// XXX: _PC_MIN_HOLE_SIZE
	// XXX: _PC_REFLINK_ENABLED
	// XXX: _PC_XATTR_ENABLED
	// XXX: _PC_SATTR_ENABLED
	// XXX: _PC_XATTR_EXISTS
	// XXX: _PC_SATTR_EXISTS
	// XXX: _PC_ACCESS_FILTERING
};


#if __SIZEOF_POINTER__ <= 4
#define FIELD32_OFFSET(offset) (u8)(offset)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define FIELD64_OFFSET(offset) (u8)(offset)
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define FIELD64_OFFSET(offset) (u8)(offset) + 4
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#else /* __SIZEOF_POINTER__ <= 4 */
#define FIELD32_OFFSET(offset) 0x80 | (u8)(offset)
#define FIELD64_OFFSET(offset) (u8)(offset)
#endif /* __SIZEOF_POINTER__ > 4 */
#define FIELD_UNDEFINED UINT8_MAX

PRIVATE ATTR_SECTION(".rodata.crt.fs.property") u8 const pc_superblock_features_offset[] = {
	[_PC_LINK_MAX]           = FIELD64_OFFSET(offsetof(struct hop_superblock_features, sbf_link_max)),
	[_PC_MAX_CANON]          = FIELD_UNDEFINED,
	[_PC_MAX_INPUT]          = FIELD_UNDEFINED,
	[_PC_NAME_MAX]           = FIELD64_OFFSET(offsetof(struct hop_superblock_features, sbf_name_max)),
	[_PC_PATH_MAX]           = FIELD_UNDEFINED,
	[_PC_PIPE_BUF]           = FIELD_UNDEFINED,
	[_PC_CHOWN_RESTRICTED]   = FIELD_UNDEFINED,
	[_PC_NO_TRUNC]           = FIELD_UNDEFINED,
	[_PC_VDISABLE]           = FIELD_UNDEFINED,
	[_PC_SYNC_IO]            = FIELD_UNDEFINED,
	[_PC_ASYNC_IO]           = FIELD_UNDEFINED,
	[_PC_PRIO_IO]            = FIELD_UNDEFINED,
	[_PC_SOCK_MAXBUF]        = FIELD_UNDEFINED,
	[_PC_FILESIZEBITS]       = FIELD_UNDEFINED, /* Custom! */
	[_PC_REC_INCR_XFER_SIZE] = FIELD32_OFFSET(offsetof(struct hop_superblock_features, sbf_rec_incr_xfer_size)),
	[_PC_REC_MAX_XFER_SIZE]  = FIELD32_OFFSET(offsetof(struct hop_superblock_features, sbf_rec_max_xfer_size)),
	[_PC_REC_MIN_XFER_SIZE]  = FIELD32_OFFSET(offsetof(struct hop_superblock_features, sbf_rec_min_xfer_size)),
	[_PC_REC_XFER_ALIGN]     = FIELD32_OFFSET(offsetof(struct hop_superblock_features, sbf_rec_xfer_align)),
	[_PC_ALLOC_SIZE_MIN]     = FIELD32_OFFSET(offsetof(struct hop_superblock_features, sbf_rec_xfer_align)),
	[_PC_SYMLINK_MAX]        = FIELD64_OFFSET(offsetof(struct hop_superblock_features, sbf_symlink_max)),
	[_PC_2_SYMLINKS]         = FIELD_UNDEFINED, /* Custom! */
};

/*[[[head:libc_fpathconf,hash:CRC-32=0x53714ecc]]]*/
/* >> fpathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED longptr_t
NOTHROW_RPC(LIBCCALL libc_fpathconf)(fd_t fd,
                                     __STDC_INT_AS_UINT_T name)
/*[[[body:libc_fpathconf]]]*/
{
	longptr_t result;
	STATIC_ASSERT(COMPILER_LENOF(pc_superblock_features_offset) >=
	              COMPILER_LENOF(pc_constants));
	if unlikely(name >= COMPILER_LENOF(pc_constants)) {
		result = libc_seterrno(EINVAL);
	} else if ((result = pc_constants[name]) == PATHCONF_VARYING_LIMIT) {
		/* Determine the value based on `fd' */
		switch (name) {

		case _PC_MAX_INPUT: {
			size_t value;
			result = ioctl(fd, TTYIO_IBUF_GETLIMIT, &value);
			if (result >= 0)
				result = (longptr_t)value;
		}	break;

		case _PC_MAX_CANON: {
			size_t value;
			result = ioctl(fd, TTYIO_CANON_GETLIMIT, &value);
			if (result >= 0)
				result = (longptr_t)value;
		}	break;

		default: {
			struct hop_superblock_features feat;
			/* Default case: Derive path information from superblock features. */
			feat.sbf_struct_size = sizeof(feat);
			result = hop(fd, HOP_SUPERBLOCK_FEATURES, &feat);
			if (result >= 0) {
				u8 offset;
				offset = pc_superblock_features_offset[name];
				if (offset != FIELD_UNDEFINED) {
#if __SIZEOF_POINTER__ <= 4
					result = (longptr_t)(*(u32 const *)((byte_t const *)&feat + offset));
#else /* __SIZEOF_POINTER__ <= 4 */
					void const *field_addr;
					field_addr = (byte_t const *)&feat + (offset & 0x7f);
					if (offset & 0x80) {
						/* 32-bit field. */
						result = (longptr_t)(*(u32 const *)field_addr);
					} else {
						/* 64-bit field. */
						result = (longptr_t)(*(u64 const *)field_addr);
					}
#endif /* __SIZEOF_POINTER__ > 4 */
				} else {
					/* Custom field. */
					if (name == _PC_FILESIZEBITS) {
						result = feat.sbf_filesizebits; /* 8-bit field */
					} else if (name == _PC_2_SYMLINKS) {
						result = feat.sbf_features & HOP_SUPERBLOCK_FEAT_SYMLINKS ? 1 : 0; /* 1-bit field */
					} else {
						/* Shouldn't get here... */
						result = PATHCONF_VARYING_LIMIT;
					}
				}
			}
		}	break;
		}
	}
	return result;
}
/*[[[end:libc_fpathconf]]]*/

/*[[[head:libc_pathconf,hash:CRC-32=0x87341e12]]]*/
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((1)) longptr_t
NOTHROW_RPC(LIBCCALL libc_pathconf)(char const *path,
                                    __STDC_INT_AS_UINT_T name)
/*[[[body:libc_pathconf]]]*/
{
	longptr_t result;
#ifndef __OPTIMIZE_SIZE__
	/* Try not to open `path' if `name' is invalid, or has a constant value */
	if unlikely(name >= COMPILER_LENOF(pc_constants)) {
		result = libc_seterrno(EINVAL);
	} else if ((result = pc_constants[name]) == PATHCONF_VARYING_LIMIT)
#endif /* !__OPTIMIZE_SIZE__ */
	{
		fd_t fd;
		fd = open(path, O_RDONLY);
		if unlikely(fd < 0)
			return -1;
		result = libc_fpathconf(fd, name);
		sys_close(fd);
	}
	return result;
}
/*[[[end:libc_pathconf]]]*/



/*[[[head:libc_confstr,hash:CRC-32=0x6f69d415]]]*/
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTERN ATTR_SECTION(".text.crt.system.configuration") size_t
NOTHROW_NCX(LIBCCALL libc_confstr)(__STDC_INT_AS_UINT_T name,
                                   char *buf,
                                   size_t buflen)
/*[[[body:libc_confstr]]]*/
{
#define DEFINE_STRING(name, text) \
	PRIVATE ATTR_SECTION(".rodata.crt.system.configuration.confstr_" #name) char const name[] = text
	size_t result;
	DEFINE_STRING(empty_string, "");
	char const *result_string = empty_string;
	switch (name) {

	case _CS_PATH: {
		DEFINE_STRING(cs_path, _PATH_DEFPATH);
		result_string = cs_path;
	}	break;

	case _CS_GNU_LIBC_VERSION:
	case _CS_GNU_LIBPTHREAD_VERSION:
	case _CS_V6_WIDTH_RESTRICTED_ENVS:
	case _CS_V5_WIDTH_RESTRICTED_ENVS:
	case _CS_V7_WIDTH_RESTRICTED_ENVS:
	case _CS_XBS5_ILP32_OFF32_CFLAGS:
	case _CS_XBS5_ILP32_OFF32_LDFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_CFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_LDFLAGS:
	case _CS_XBS5_LP64_OFF64_CFLAGS:
	case _CS_XBS5_LP64_OFF64_LDFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_CFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_LDFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_CFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_LDFLAGS:
	case _CS_POSIX_V7_ILP32_OFF32_CFLAGS:
	case _CS_POSIX_V7_ILP32_OFF32_LDFLAGS:
	case _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS:
	case _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS:
	case _CS_POSIX_V7_LP64_OFF64_CFLAGS:
	case _CS_POSIX_V7_LP64_OFF64_LDFLAGS:
		/* TODO? */
		break;

	case _CS_LFS_CFLAGS:
	case _CS_LFS_LINTFLAGS: {
		DEFINE_STRING(define_LFS, "-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64");
		result_string = define_LFS;
	}	break;

	case _CS_LFS64_CFLAGS:
	case _CS_LFS64_LINTFLAGS: {
		DEFINE_STRING(define_LFS64, "-D_LARGEFILE64_SOURCE");
		result_string = define_LFS64;
	}	break;

	case _CS_LFS_LDFLAGS:
	case _CS_LFS_LIBS:
	case _CS_LFS64_LDFLAGS:
	case _CS_LFS64_LIBS:
	case _CS_XBS5_ILP32_OFF32_LIBS:
	case _CS_XBS5_ILP32_OFF32_LINTFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_LIBS:
	case _CS_XBS5_ILP32_OFFBIG_LINTFLAGS:
	case _CS_XBS5_LP64_OFF64_LIBS:
	case _CS_XBS5_LP64_OFF64_LINTFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_CFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_LDFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_LIBS:
	case _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V6_ILP32_OFF32_LIBS:
	case _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LIBS:
	case _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V6_LP64_OFF64_LIBS:
	case _CS_POSIX_V6_LP64_OFF64_LINTFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LIBS:
	case _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V7_ILP32_OFF32_LIBS:
	case _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS:
	case _CS_POSIX_V7_ILP32_OFFBIG_LIBS:
	case _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS:
	case _CS_POSIX_V7_LP64_OFF64_LIBS:
	case _CS_POSIX_V7_LP64_OFF64_LINTFLAGS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_LIBS:
	case _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS:
		break;

	case _CS_V6_ENV:
	case _CS_V7_ENV: {
		DEFINE_STRING(cs_v67_env, "POSIXLY_CORRECT=1");
		result_string = cs_v67_env;
	}	break;

	default:
		libc_seterrno(EINVAL);
		return 0;
	}
	result = strlen(result_string) + 1;
	if (buflen && buf) {
		if (buflen >= result) {
			memcpy(buf, result_string, result, sizeof(char));
		} else {
			memcpy(buf, result_string, buflen - 1, sizeof(char));
			buf[buflen - 1] = '\0';
		}
	}
	return result;
}
/*[[[end:libc_confstr]]]*/



#define SYSCONF_ENTRY_UNDEFINED INT32_MIN
#define SYSCONF_ENTRY_UNLIMITED (-1)

/* List of sysconf values that may have values > INT32_MAX */
#define SYSCONF_VALUES_HI_INT32             \
	{ "CHAR_MAX", "INT_MAX", "SSIZE_MAX",   \
	  "SCHAR_MAX", "SHRT_MAX", "UCHAR_MAX", \
	  "UINT_MAX", "ULONG_MAX", "USHRT_MAX" }

/* List of sysconf values that may have values <= INT32_MIN */
#define SYSCONF_VALUES_LO_INT32 \
	{ "CHAR_MIN", "INT_MIN", "SCHAR_MIN", "SHRT_MIN" }


PRIVATE ATTR_SECTION(".rodata.crt.system.configuration")
s32 const sysconf_table[] = {
/*[[[deemon
import * from deemon;
@@Mapping from @(SC_ID: (name, values))
local sc_values: {int: (string, string)} = Dict();
for (local l: File.open("../../../include/asm/crt/confname.h")) {
	l = l.strip();
	local name, idval, values;
	try {
		name, idval, values = l.scanf("#define _SC_%[^ ] %[^/]/" "* [== %[^\\]]")...;
	} catch (...) {
		continue;
	}
	if (name == "COUNT")
		continue;
	name = "_SC_" + name;
	try {
		idval = idval.strip();
		if (!idval.isnumeric()) {
			for (local i, nameAndValue: sc_values) {
				local name2, none = nameAndValue...;
				if (name2 in idval)
					idval = idval.replace(name2, str(i));
			}
			idval = exec(idval);
		} else {
			idval = int(idval);
		}
	} catch (...) {
		continue;
	}
	if (idval !in sc_values)
		sc_values[idval] = (name, values.strip());
}
local idCount = (sc_values.keys > ...) + 1;
local maxIdLen = #str(idCount - 1);
for (local id: [:idCount]) {
	local name, values = sc_values.get(id)...;
	if (name is none)
		name = str(id);
	if (values is none)
		values = "SYSCONF_ENTRY_UNDEFINED";
	local prefix = "\t/" "* [{}] = *" "/ ".format({ str(id).rjust(maxIdLen) });
	local suffix = ", /" "* {} *" "/".format({ name });
	local endifComment = Cell();
	function ppBeginIfDef(macroName) {
		if (!endifComment) {
			print("#ifdef ", macroName);
			endifComment.value = macroName;
		} else {
			print("#elif defined(", macroName, ")");
			endifComment.value = "...";
		}
	}
	function ppBeginIf(expr) {
		if (!endifComment) {
			print("#if ", expr);
			endifComment.value = expr;
		} else {
			print("#elif ", expr);
			endifComment.value = "...";
		}
	}
	function ppElse() {
		local com = endifComment.value;
		print("#else /" "* ", com, " *" "/");
		if ("<" in com) {
			com = com.replace("<", ">=").replace(">==", ">");
		} else if (">" in com) {
			com = com.replace(">", "<=").replace("<==", "<");
		} else {
			com = "!" + com;
		}
		endifComment.value = com;
	}
	function ppEndif() {
		print("#endif /" "* ", endifComment.value, " *" "/");
		del endifComment.value;
	}
	values = List(values.split(","));
	local nvalues = #values;
	for (local i: [:nvalues]) {
		local v = values[i].strip();
		if (v.startswith("defined(") && v.endswith(")")) {
			v = v[8:-1].strip();
			ppBeginIfDef(v);
			print(prefix, "1", suffix);
			ppElse();
			print(prefix, "SYSCONF_ENTRY_UNLIMITED", suffix);
			ppEndif();
			break;
		} else if (v in ["custom", "SYSCONF_ENTRY_UNDEFINED"]) {
			if (endifComment)
				ppElse();
			print(prefix, "SYSCONF_ENTRY_UNDEFINED", suffix);
			break;
		} else if (v == "unlimited") {
			if (endifComment)
				ppElse();
			print(prefix, "SYSCONF_ENTRY_UNLIMITED", suffix);
			break;
		} else {
			local need_undefined = false;
			if (v in SYSCONF_VALUES_HI_INT32) {
				need_undefined = true;
				ppBeginIf("{} <= INT32_MAX".format({ v }));
			} else if (v in SYSCONF_VALUES_LO_INT32) {
				need_undefined = true;
				ppBeginIf("{} > INT32_MIN".format({ v }));
			} else if (i != nvalues - 1) {
				ppBeginIfDef(v);
			} else if (endifComment) {
				ppElse();
			}
			print(prefix, v, suffix);
			if (need_undefined) {
				ppElse();
				print(prefix, "SYSCONF_ENTRY_UNDEFINED", suffix);
				ppEndif();
				break;
			}
		}
	}
	if (endifComment)
		ppEndif();
}
]]]*/
	/* [  0] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_ARG_MAX */
	/* [  1] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_CHILD_MAX */
	/* [  2] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_CLK_TCK */
	/* [  3] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NGROUPS_MAX */
	/* [  4] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_OPEN_MAX */
	/* [  5] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_STREAM_MAX */
	/* [  6] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TZNAME_MAX */
	/* [  7] = */ _POSIX_JOB_CONTROL, /* _SC_JOB_CONTROL */
	/* [  8] = */ _POSIX_SAVED_IDS, /* _SC_SAVED_IDS */
	/* [  9] = */ _POSIX_REALTIME_SIGNALS, /* _SC_REALTIME_SIGNALS */
	/* [ 10] = */ _POSIX_PRIORITY_SCHEDULING, /* _SC_PRIORITY_SCHEDULING */
	/* [ 11] = */ _POSIX_TIMERS, /* _SC_TIMERS */
	/* [ 12] = */ _POSIX_ASYNCHRONOUS_IO, /* _SC_ASYNCHRONOUS_IO */
	/* [ 13] = */ _POSIX_PRIORITIZED_IO, /* _SC_PRIORITIZED_IO */
	/* [ 14] = */ _POSIX_SYNCHRONIZED_IO, /* _SC_SYNCHRONIZED_IO */
	/* [ 15] = */ _POSIX_FSYNC, /* _SC_FSYNC */
	/* [ 16] = */ _POSIX_MAPPED_FILES, /* _SC_MAPPED_FILES */
	/* [ 17] = */ _POSIX_MEMLOCK, /* _SC_MEMLOCK */
	/* [ 18] = */ _POSIX_MEMLOCK_RANGE, /* _SC_MEMLOCK_RANGE */
	/* [ 19] = */ _POSIX_MEMORY_PROTECTION, /* _SC_MEMORY_PROTECTION */
	/* [ 20] = */ _POSIX_MESSAGE_PASSING, /* _SC_MESSAGE_PASSING */
	/* [ 21] = */ _POSIX_SEMAPHORES, /* _SC_SEMAPHORES */
	/* [ 22] = */ _POSIX_SHARED_MEMORY_OBJECTS, /* _SC_SHARED_MEMORY_OBJECTS */
	/* [ 23] = */ _POSIX_AIO_LISTIO_MAX, /* _SC_AIO_LISTIO_MAX */
	/* [ 24] = */ _POSIX_AIO_MAX, /* _SC_AIO_MAX */
	/* [ 25] = */ AIO_PRIO_DELTA_MAX, /* _SC_AIO_PRIO_DELTA_MAX */
#ifdef DELAYTIMER_MAX
	/* [ 26] = */ DELAYTIMER_MAX, /* _SC_DELAYTIMER_MAX */
#else /* DELAYTIMER_MAX */
	/* [ 26] = */ _POSIX_DELAYTIMER_MAX, /* _SC_DELAYTIMER_MAX */
#endif /* !DELAYTIMER_MAX */
	/* [ 27] = */ _POSIX_MQ_OPEN_MAX, /* _SC_MQ_OPEN_MAX */
#ifdef MQ_PRIO_MAX
	/* [ 28] = */ MQ_PRIO_MAX, /* _SC_MQ_PRIO_MAX */
#else /* MQ_PRIO_MAX */
	/* [ 28] = */ _POSIX_MQ_PRIO_MAX, /* _SC_MQ_PRIO_MAX */
#endif /* !MQ_PRIO_MAX */
	/* [ 29] = */ _POSIX_VERSION, /* _SC_VERSION */
	/* [ 30] = */ __ARCH_PAGESIZE, /* _SC_PAGESIZE */
#ifdef RTSIG_MAX
	/* [ 31] = */ RTSIG_MAX, /* _SC_RTSIG_MAX */
#else /* RTSIG_MAX */
	/* [ 31] = */ _POSIX_RTSIG_MAX, /* _SC_RTSIG_MAX */
#endif /* !RTSIG_MAX */
	/* [ 32] = */ _POSIX_SEM_NSEMS_MAX, /* _SC_SEM_NSEMS_MAX */
#ifdef SEM_VALUE_MAX
	/* [ 33] = */ SEM_VALUE_MAX, /* _SC_SEM_VALUE_MAX */
#else /* SEM_VALUE_MAX */
	/* [ 33] = */ _POSIX_SEM_VALUE_MAX, /* _SC_SEM_VALUE_MAX */
#endif /* !SEM_VALUE_MAX */
	/* [ 34] = */ _POSIX_SIGQUEUE_MAX, /* _SC_SIGQUEUE_MAX */
	/* [ 35] = */ _POSIX_TIMER_MAX, /* _SC_TIMER_MAX */
#ifdef BC_BASE_MAX
	/* [ 36] = */ BC_BASE_MAX, /* _SC_BC_BASE_MAX */
#else /* BC_BASE_MAX */
	/* [ 36] = */ _POSIX2_BC_BASE_MAX, /* _SC_BC_BASE_MAX */
#endif /* !BC_BASE_MAX */
#ifdef BC_DIM_MAX
	/* [ 37] = */ BC_DIM_MAX, /* _SC_BC_DIM_MAX */
#else /* BC_DIM_MAX */
	/* [ 37] = */ _POSIX2_BC_DIM_MAX, /* _SC_BC_DIM_MAX */
#endif /* !BC_DIM_MAX */
#ifdef BC_SCALE_MAX
	/* [ 38] = */ BC_SCALE_MAX, /* _SC_BC_SCALE_MAX */
#else /* BC_SCALE_MAX */
	/* [ 38] = */ _POSIX2_BC_SCALE_MAX, /* _SC_BC_SCALE_MAX */
#endif /* !BC_SCALE_MAX */
#ifdef BC_STRING_MAX
	/* [ 39] = */ BC_STRING_MAX, /* _SC_BC_STRING_MAX */
#else /* BC_STRING_MAX */
	/* [ 39] = */ _POSIX2_BC_STRING_MAX, /* _SC_BC_STRING_MAX */
#endif /* !BC_STRING_MAX */
#ifdef COLL_WEIGHTS_MAX
	/* [ 40] = */ COLL_WEIGHTS_MAX, /* _SC_COLL_WEIGHTS_MAX */
#else /* COLL_WEIGHTS_MAX */
	/* [ 40] = */ _POSIX2_COLL_WEIGHTS_MAX, /* _SC_COLL_WEIGHTS_MAX */
#endif /* !COLL_WEIGHTS_MAX */
	/* [ 41] = */ SYSCONF_ENTRY_UNDEFINED, /* 41 */
#ifdef EXPR_NEST_MAX
	/* [ 42] = */ EXPR_NEST_MAX, /* _SC_EXPR_NEST_MAX */
#else /* EXPR_NEST_MAX */
	/* [ 42] = */ _POSIX2_EXPR_NEST_MAX, /* _SC_EXPR_NEST_MAX */
#endif /* !EXPR_NEST_MAX */
#ifdef LINE_MAX
	/* [ 43] = */ LINE_MAX, /* _SC_LINE_MAX */
#else /* LINE_MAX */
	/* [ 43] = */ _POSIX2_LINE_MAX, /* _SC_LINE_MAX */
#endif /* !LINE_MAX */
#ifdef RE_DUP_MAX
	/* [ 44] = */ RE_DUP_MAX, /* _SC_RE_DUP_MAX */
#else /* RE_DUP_MAX */
	/* [ 44] = */ _POSIX_RE_DUP_MAX, /* _SC_RE_DUP_MAX */
#endif /* !RE_DUP_MAX */
#ifdef CHARCLASS_NAME_MAX
	/* [ 45] = */ CHARCLASS_NAME_MAX, /* _SC_CHARCLASS_NAME_MAX */
#else /* CHARCLASS_NAME_MAX */
	/* [ 45] = */ _POSIX2_CHARCLASS_NAME_MAX, /* _SC_CHARCLASS_NAME_MAX */
#endif /* !CHARCLASS_NAME_MAX */
	/* [ 46] = */ _POSIX2_VERSION, /* _SC_2_VERSION */
#ifdef _POSIX2_C_BIND
	/* [ 47] = */ _POSIX2_C_BIND, /* _SC_2_C_BIND */
#else /* _POSIX2_C_BIND */
	/* [ 47] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_C_BIND */
#endif /* !_POSIX2_C_BIND */
#ifdef _SC_2_C_DEV
	/* [ 48] = */ _SC_2_C_DEV, /* _SC_2_C_DEV */
#else /* _SC_2_C_DEV */
	/* [ 48] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_C_DEV */
#endif /* !_SC_2_C_DEV */
#ifdef _POSIX2_FORT_DEV
	/* [ 49] = */ _POSIX2_FORT_DEV, /* _SC_2_FORT_DEV */
#else /* _POSIX2_FORT_DEV */
	/* [ 49] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_FORT_DEV */
#endif /* !_POSIX2_FORT_DEV */
#ifdef _POSIX2_FORT_RUN
	/* [ 50] = */ _POSIX2_FORT_RUN, /* _SC_2_FORT_RUN */
#else /* _POSIX2_FORT_RUN */
	/* [ 50] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_FORT_RUN */
#endif /* !_POSIX2_FORT_RUN */
#ifdef _POSIX2_SW_DEV
	/* [ 51] = */ _POSIX2_SW_DEV, /* _SC_2_SW_DEV */
#else /* _POSIX2_SW_DEV */
	/* [ 51] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_SW_DEV */
#endif /* !_POSIX2_SW_DEV */
#ifdef _POSIX2_LOCALEDEF
	/* [ 52] = */ _POSIX2_LOCALEDEF, /* _SC_2_LOCALEDEF */
#else /* _POSIX2_LOCALEDEF */
	/* [ 52] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_LOCALEDEF */
#endif /* !_POSIX2_LOCALEDEF */
#ifdef _POSIX_PII
	/* [ 53] = */ 1, /* _SC_PII */
#else /* _POSIX_PII */
	/* [ 53] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII */
#endif /* !_POSIX_PII */
#ifdef _POSIX_PII_XTI
	/* [ 54] = */ 1, /* _SC_PII_XTI */
#else /* _POSIX_PII_XTI */
	/* [ 54] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_XTI */
#endif /* !_POSIX_PII_XTI */
#ifdef _POSIX_PII_SOCKET
	/* [ 55] = */ 1, /* _SC_PII_SOCKET */
#else /* _POSIX_PII_SOCKET */
	/* [ 55] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_SOCKET */
#endif /* !_POSIX_PII_SOCKET */
#ifdef _POSIX_PII_INTERNET
	/* [ 56] = */ 1, /* _SC_PII_INTERNET */
#else /* _POSIX_PII_INTERNET */
	/* [ 56] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_INTERNET */
#endif /* !_POSIX_PII_INTERNET */
#ifdef _POSIX_PII_OSI
	/* [ 57] = */ 1, /* _SC_PII_OSI */
#else /* _POSIX_PII_OSI */
	/* [ 57] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_OSI */
#endif /* !_POSIX_PII_OSI */
#ifdef _POSIX_POLL
	/* [ 58] = */ 1, /* _SC_POLL */
#else /* _POSIX_POLL */
	/* [ 58] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_POLL */
#endif /* !_POSIX_POLL */
#ifdef _POSIX_SELECT
	/* [ 59] = */ 1, /* _SC_SELECT */
#else /* _POSIX_SELECT */
	/* [ 59] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SELECT */
#endif /* !_POSIX_SELECT */
	/* [ 60] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_UIO_MAXIOV */
#ifdef _POSIX_PII_INTERNET_STREAM
	/* [ 61] = */ 1, /* _SC_PII_INTERNET_STREAM */
#else /* _POSIX_PII_INTERNET_STREAM */
	/* [ 61] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_INTERNET_STREAM */
#endif /* !_POSIX_PII_INTERNET_STREAM */
#ifdef _POSIX_PII_INTERNET_DGRAM
	/* [ 62] = */ 1, /* _SC_PII_INTERNET_DGRAM */
#else /* _POSIX_PII_INTERNET_DGRAM */
	/* [ 62] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_INTERNET_DGRAM */
#endif /* !_POSIX_PII_INTERNET_DGRAM */
#ifdef _POSIX_PII_OSI_COTS
	/* [ 63] = */ 1, /* _SC_PII_OSI_COTS */
#else /* _POSIX_PII_OSI_COTS */
	/* [ 63] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_OSI_COTS */
#endif /* !_POSIX_PII_OSI_COTS */
#ifdef _POSIX_PII_OSI_CLTS
	/* [ 64] = */ 1, /* _SC_PII_OSI_CLTS */
#else /* _POSIX_PII_OSI_CLTS */
	/* [ 64] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_OSI_CLTS */
#endif /* !_POSIX_PII_OSI_CLTS */
#ifdef _POSIX_PII_OSI_M
	/* [ 65] = */ 1, /* _SC_PII_OSI_M */
#else /* _POSIX_PII_OSI_M */
	/* [ 65] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PII_OSI_M */
#endif /* !_POSIX_PII_OSI_M */
	/* [ 66] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_T_IOV_MAX */
	/* [ 67] = */ _POSIX_THREADS, /* _SC_THREADS */
	/* [ 68] = */ _POSIX_THREAD_SAFE_FUNCTIONS, /* _SC_THREAD_SAFE_FUNCTIONS */
	/* [ 69] = */ NSS_BUFLEN_GROUP, /* _SC_GETGR_R_SIZE_MAX */
	/* [ 70] = */ NSS_BUFLEN_PASSWD, /* _SC_GETPW_R_SIZE_MAX */
	/* [ 71] = */ LOGIN_NAME_MAX, /* _SC_LOGIN_NAME_MAX */
	/* [ 72] = */ TTY_NAME_MAX, /* _SC_TTY_NAME_MAX */
	/* [ 73] = */ _POSIX_THREAD_DESTRUCTOR_ITERATIONS, /* _SC_THREAD_DESTRUCTOR_ITERATIONS */
	/* [ 74] = */ _POSIX_THREAD_KEYS_MAX, /* _SC_THREAD_KEYS_MAX */
	/* [ 75] = */ PTHREAD_STACK_MIN, /* _SC_THREAD_STACK_MIN */
	/* [ 76] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_THREAD_THREADS_MAX */
	/* [ 77] = */ _POSIX_THREAD_ATTR_STACKADDR, /* _SC_THREAD_ATTR_STACKADDR */
	/* [ 78] = */ _POSIX_THREAD_ATTR_STACKSIZE, /* _SC_THREAD_ATTR_STACKSIZE */
	/* [ 79] = */ _POSIX_THREAD_PRIORITY_SCHEDULING, /* _SC_THREAD_PRIORITY_SCHEDULING */
	/* [ 80] = */ _POSIX_THREAD_PRIO_INHERIT, /* _SC_THREAD_PRIO_INHERIT */
	/* [ 81] = */ _POSIX_THREAD_PRIO_PROTECT, /* _SC_THREAD_PRIO_PROTECT */
	/* [ 82] = */ _POSIX_THREAD_PROCESS_SHARED, /* _SC_THREAD_PROCESS_SHARED */
	/* [ 83] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_NPROCESSORS_CONF */
	/* [ 84] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_NPROCESSORS_ONLN */
	/* [ 85] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_PHYS_PAGES */
	/* [ 86] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_AVPHYS_PAGES */
	/* [ 87] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_ATEXIT_MAX */
	/* [ 88] = */ BUFSIZ, /* _SC_PASS_MAX */
	/* [ 89] = */ _XOPEN_VERSION, /* _SC_XOPEN_VERSION */
	/* [ 90] = */ _XOPEN_XCU_VERSION, /* _SC_XOPEN_XCU_VERSION */
	/* [ 91] = */ _XOPEN_UNIX, /* _SC_XOPEN_UNIX */
	/* [ 92] = */ _XOPEN_CRYPT, /* _SC_XOPEN_CRYPT */
	/* [ 93] = */ _XOPEN_ENH_I18N, /* _SC_XOPEN_ENH_I18N */
	/* [ 94] = */ _XOPEN_SHM, /* _SC_XOPEN_SHM */
	/* [ 95] = */ _POSIX2_CHAR_TERM, /* _SC_2_CHAR_TERM */
	/* [ 96] = */ _POSIX2_C_VERSION, /* _SC_2_C_VERSION */
#ifdef _POSIX2_UPE
	/* [ 97] = */ _POSIX2_UPE, /* _SC_2_UPE */
#else /* _POSIX2_UPE */
	/* [ 97] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_UPE */
#endif /* !_POSIX2_UPE */
	/* [ 98] = */ _XOPEN_XPG2, /* _SC_XOPEN_XPG2 */
	/* [ 99] = */ _XOPEN_XPG3, /* _SC_XOPEN_XPG3 */
	/* [100] = */ _XOPEN_XPG4, /* _SC_XOPEN_XPG4 */
	/* [101] = */ CHAR_BIT, /* _SC_CHAR_BIT */
#if CHAR_MAX <= INT32_MAX
	/* [102] = */ CHAR_MAX, /* _SC_CHAR_MAX */
#else /* CHAR_MAX <= INT32_MAX */
	/* [102] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_CHAR_MAX */
#endif /* CHAR_MAX > INT32_MAX */
#if CHAR_MIN > INT32_MIN
	/* [103] = */ CHAR_MIN, /* _SC_CHAR_MIN */
#else /* CHAR_MIN > INT32_MIN */
	/* [103] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_CHAR_MIN */
#endif /* CHAR_MIN <= INT32_MIN */
#if INT_MAX <= INT32_MAX
	/* [104] = */ INT_MAX, /* _SC_INT_MAX */
#else /* INT_MAX <= INT32_MAX */
	/* [104] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_INT_MAX */
#endif /* INT_MAX > INT32_MAX */
#if INT_MIN > INT32_MIN
	/* [105] = */ INT_MIN, /* _SC_INT_MIN */
#else /* INT_MIN > INT32_MIN */
	/* [105] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_INT_MIN */
#endif /* INT_MIN <= INT32_MIN */
	/* [106] = */ LONG_BIT, /* _SC_LONG_BIT */
	/* [107] = */ WORD_BIT, /* _SC_WORD_BIT */
	/* [108] = */ MB_LEN_MAX, /* _SC_MB_LEN_MAX */
	/* [109] = */ NZERO, /* _SC_NZERO */
#if SSIZE_MAX <= INT32_MAX
	/* [110] = */ SSIZE_MAX, /* _SC_SSIZE_MAX */
#else /* SSIZE_MAX <= INT32_MAX */
	/* [110] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_SSIZE_MAX */
#endif /* SSIZE_MAX > INT32_MAX */
#if SCHAR_MAX <= INT32_MAX
	/* [111] = */ SCHAR_MAX, /* _SC_SCHAR_MAX */
#else /* SCHAR_MAX <= INT32_MAX */
	/* [111] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_SCHAR_MAX */
#endif /* SCHAR_MAX > INT32_MAX */
#if SCHAR_MIN > INT32_MIN
	/* [112] = */ SCHAR_MIN, /* _SC_SCHAR_MIN */
#else /* SCHAR_MIN > INT32_MIN */
	/* [112] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_SCHAR_MIN */
#endif /* SCHAR_MIN <= INT32_MIN */
#if SHRT_MAX <= INT32_MAX
	/* [113] = */ SHRT_MAX, /* _SC_SHRT_MAX */
#else /* SHRT_MAX <= INT32_MAX */
	/* [113] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_SHRT_MAX */
#endif /* SHRT_MAX > INT32_MAX */
#if SHRT_MIN > INT32_MIN
	/* [114] = */ SHRT_MIN, /* _SC_SHRT_MIN */
#else /* SHRT_MIN > INT32_MIN */
	/* [114] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_SHRT_MIN */
#endif /* SHRT_MIN <= INT32_MIN */
#if UCHAR_MAX <= INT32_MAX
	/* [115] = */ UCHAR_MAX, /* _SC_UCHAR_MAX */
#else /* UCHAR_MAX <= INT32_MAX */
	/* [115] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_UCHAR_MAX */
#endif /* UCHAR_MAX > INT32_MAX */
#if UINT_MAX <= INT32_MAX
	/* [116] = */ UINT_MAX, /* _SC_UINT_MAX */
#else /* UINT_MAX <= INT32_MAX */
	/* [116] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_UINT_MAX */
#endif /* UINT_MAX > INT32_MAX */
#if ULONG_MAX <= INT32_MAX
	/* [117] = */ ULONG_MAX, /* _SC_ULONG_MAX */
#else /* ULONG_MAX <= INT32_MAX */
	/* [117] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_ULONG_MAX */
#endif /* ULONG_MAX > INT32_MAX */
#if USHRT_MAX <= INT32_MAX
	/* [118] = */ USHRT_MAX, /* _SC_USHRT_MAX */
#else /* USHRT_MAX <= INT32_MAX */
	/* [118] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_USHRT_MAX */
#endif /* USHRT_MAX > INT32_MAX */
#ifdef NL_ARGMAX
	/* [119] = */ NL_ARGMAX, /* _SC_NL_ARGMAX */
#else /* NL_ARGMAX */
	/* [119] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NL_ARGMAX */
#endif /* !NL_ARGMAX */
#ifdef NL_LANGMAX
	/* [120] = */ NL_LANGMAX, /* _SC_NL_LANGMAX */
#else /* NL_LANGMAX */
	/* [120] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NL_LANGMAX */
#endif /* !NL_LANGMAX */
#ifdef NL_MSGMAX
	/* [121] = */ NL_MSGMAX, /* _SC_NL_MSGMAX */
#else /* NL_MSGMAX */
	/* [121] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NL_MSGMAX */
#endif /* !NL_MSGMAX */
#ifdef NL_NMAX
	/* [122] = */ NL_NMAX, /* _SC_NL_NMAX */
#else /* NL_NMAX */
	/* [122] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NL_NMAX */
#endif /* !NL_NMAX */
#ifdef NL_SETMAX
	/* [123] = */ NL_SETMAX, /* _SC_NL_SETMAX */
#else /* NL_SETMAX */
	/* [123] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NL_SETMAX */
#endif /* !NL_SETMAX */
#ifdef NL_TEXTMAX
	/* [124] = */ NL_TEXTMAX, /* _SC_NL_TEXTMAX */
#else /* NL_TEXTMAX */
	/* [124] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NL_TEXTMAX */
#endif /* !NL_TEXTMAX */
	/* [125] = */ SYSCONF_ENTRY_UNDEFINED, /* 125 */
	/* [126] = */ SYSCONF_ENTRY_UNDEFINED, /* 126 */
	/* [127] = */ SYSCONF_ENTRY_UNDEFINED, /* 127 */
	/* [128] = */ SYSCONF_ENTRY_UNDEFINED, /* 128 */
	/* [129] = */ _XOPEN_LEGACY, /* _SC_XOPEN_LEGACY */
#ifdef _XOPEN_REALTIME
	/* [130] = */ _XOPEN_REALTIME, /* _SC_XOPEN_REALTIME */
#else /* _XOPEN_REALTIME */
	/* [130] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_XOPEN_REALTIME */
#endif /* !_XOPEN_REALTIME */
#ifdef _XOPEN_REALTIME_THREADS
	/* [131] = */ _XOPEN_REALTIME_THREADS, /* _SC_XOPEN_REALTIME_THREADS */
#else /* _XOPEN_REALTIME_THREADS */
	/* [131] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_XOPEN_REALTIME_THREADS */
#endif /* !_XOPEN_REALTIME_THREADS */
	/* [132] = */ _POSIX_ADVISORY_INFO, /* _SC_ADVISORY_INFO */
	/* [133] = */ _POSIX_BARRIERS, /* _SC_BARRIERS */
#ifdef _POSIX_BASE
	/* [134] = */ _POSIX_BASE, /* _SC_BASE */
#else /* _POSIX_BASE */
	/* [134] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_BASE */
#endif /* !_POSIX_BASE */
#ifdef _POSIX_C_LANG_SUPPORT
	/* [135] = */ _POSIX_C_LANG_SUPPORT, /* _SC_C_LANG_SUPPORT */
#else /* _POSIX_C_LANG_SUPPORT */
	/* [135] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_C_LANG_SUPPORT */
#endif /* !_POSIX_C_LANG_SUPPORT */
#ifdef _POSIX_C_LANG_SUPPORT_R
	/* [136] = */ _POSIX_C_LANG_SUPPORT_R, /* _SC_C_LANG_SUPPORT_R */
#else /* _POSIX_C_LANG_SUPPORT_R */
	/* [136] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_C_LANG_SUPPORT_R */
#endif /* !_POSIX_C_LANG_SUPPORT_R */
#ifdef _POSIX_CLOCK_SELECTION
	/* [137] = */ _POSIX_CLOCK_SELECTION, /* _SC_CLOCK_SELECTION */
#else /* _POSIX_CLOCK_SELECTION */
	/* [137] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_CLOCK_SELECTION */
#endif /* !_POSIX_CLOCK_SELECTION */
#ifdef _POSIX_CPUTIME
	/* [138] = */ _POSIX_CPUTIME, /* _SC_CPUTIME */
#else /* _POSIX_CPUTIME */
	/* [138] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_CPUTIME */
#endif /* !_POSIX_CPUTIME */
#ifdef _POSIX_THREAD_CPUTIME
	/* [139] = */ _POSIX_THREAD_CPUTIME, /* _SC_THREAD_CPUTIME */
#else /* _POSIX_THREAD_CPUTIME */
	/* [139] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_THREAD_CPUTIME */
#endif /* !_POSIX_THREAD_CPUTIME */
#ifdef _POSIX_DEVICE_IO
	/* [140] = */ _POSIX_DEVICE_IO, /* _SC_DEVICE_IO */
#else /* _POSIX_DEVICE_IO */
	/* [140] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_DEVICE_IO */
#endif /* !_POSIX_DEVICE_IO */
#ifdef _POSIX_DEVICE_SPECIFIC
	/* [141] = */ _POSIX_DEVICE_SPECIFIC, /* _SC_DEVICE_SPECIFIC */
#else /* _POSIX_DEVICE_SPECIFIC */
	/* [141] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_DEVICE_SPECIFIC */
#endif /* !_POSIX_DEVICE_SPECIFIC */
#ifdef _POSIX_DEVICE_SPECIFIC_R
	/* [142] = */ _POSIX_DEVICE_SPECIFIC_R, /* _SC_DEVICE_SPECIFIC_R */
#else /* _POSIX_DEVICE_SPECIFIC_R */
	/* [142] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_DEVICE_SPECIFIC_R */
#endif /* !_POSIX_DEVICE_SPECIFIC_R */
#ifdef _POSIX_FD_MGMT
	/* [143] = */ _POSIX_FD_MGMT, /* _SC_FD_MGMT */
#else /* _POSIX_FD_MGMT */
	/* [143] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_FD_MGMT */
#endif /* !_POSIX_FD_MGMT */
#ifdef _POSIX_FIFO
	/* [144] = */ _POSIX_FIFO, /* _SC_FIFO */
#else /* _POSIX_FIFO */
	/* [144] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_FIFO */
#endif /* !_POSIX_FIFO */
#ifdef _POSIX_PIPE
	/* [145] = */ _POSIX_PIPE, /* _SC_PIPE */
#else /* _POSIX_PIPE */
	/* [145] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_PIPE */
#endif /* !_POSIX_PIPE */
#ifdef _POSIX_FILE_ATTRIBUTES
	/* [146] = */ _POSIX_FILE_ATTRIBUTES, /* _SC_FILE_ATTRIBUTES */
#else /* _POSIX_FILE_ATTRIBUTES */
	/* [146] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_FILE_ATTRIBUTES */
#endif /* !_POSIX_FILE_ATTRIBUTES */
#ifdef _POSIX_FILE_LOCKING
	/* [147] = */ _POSIX_FILE_LOCKING, /* _SC_FILE_LOCKING */
#else /* _POSIX_FILE_LOCKING */
	/* [147] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_FILE_LOCKING */
#endif /* !_POSIX_FILE_LOCKING */
#ifdef _POSIX_FILE_SYSTEM
	/* [148] = */ _POSIX_FILE_SYSTEM, /* _SC_FILE_SYSTEM */
#else /* _POSIX_FILE_SYSTEM */
	/* [148] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_FILE_SYSTEM */
#endif /* !_POSIX_FILE_SYSTEM */
#ifdef _POSIX_MONOTONIC_CLOCK
	/* [149] = */ _POSIX_MONOTONIC_CLOCK, /* _SC_MONOTONIC_CLOCK */
#else /* _POSIX_MONOTONIC_CLOCK */
	/* [149] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_MONOTONIC_CLOCK */
#endif /* !_POSIX_MONOTONIC_CLOCK */
#ifdef _POSIX_MULTI_PROCESS
	/* [150] = */ _POSIX_MULTI_PROCESS, /* _SC_MULTI_PROCESS */
#else /* _POSIX_MULTI_PROCESS */
	/* [150] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_MULTI_PROCESS */
#endif /* !_POSIX_MULTI_PROCESS */
#ifdef _POSIX_SINGLE_PROCESS
	/* [151] = */ _POSIX_SINGLE_PROCESS, /* _SC_SINGLE_PROCESS */
#else /* _POSIX_SINGLE_PROCESS */
	/* [151] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SINGLE_PROCESS */
#endif /* !_POSIX_SINGLE_PROCESS */
#ifdef _POSIX_NETWORKING
	/* [152] = */ _POSIX_NETWORKING, /* _SC_NETWORKING */
#else /* _POSIX_NETWORKING */
	/* [152] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_NETWORKING */
#endif /* !_POSIX_NETWORKING */
#ifdef _POSIX_READER_WRITER_LOCKS
	/* [153] = */ _POSIX_READER_WRITER_LOCKS, /* _SC_READER_WRITER_LOCKS */
#else /* _POSIX_READER_WRITER_LOCKS */
	/* [153] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_READER_WRITER_LOCKS */
#endif /* !_POSIX_READER_WRITER_LOCKS */
#ifdef _POSIX_SPIN_LOCKS
	/* [154] = */ _POSIX_SPIN_LOCKS, /* _SC_SPIN_LOCKS */
#else /* _POSIX_SPIN_LOCKS */
	/* [154] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SPIN_LOCKS */
#endif /* !_POSIX_SPIN_LOCKS */
#ifdef _POSIX_REGEXP
	/* [155] = */ _POSIX_REGEXP, /* _SC_REGEXP */
#else /* _POSIX_REGEXP */
	/* [155] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_REGEXP */
#endif /* !_POSIX_REGEXP */
	/* [156] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_REGEX_VERSION */
#ifdef _POSIX_SHELL
	/* [157] = */ _POSIX_SHELL, /* _SC_SHELL */
#else /* _POSIX_SHELL */
	/* [157] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SHELL */
#endif /* !_POSIX_SHELL */
#ifdef _POSIX_SIGNALS
	/* [158] = */ _POSIX_SIGNALS, /* _SC_SIGNALS */
#else /* _POSIX_SIGNALS */
	/* [158] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SIGNALS */
#endif /* !_POSIX_SIGNALS */
#ifdef _POSIX_SPAWN
	/* [159] = */ _POSIX_SPAWN, /* _SC_SPAWN */
#else /* _POSIX_SPAWN */
	/* [159] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SPAWN */
#endif /* !_POSIX_SPAWN */
#ifdef _POSIX_SPORADIC_SERVER
	/* [160] = */ _POSIX_SPORADIC_SERVER, /* _SC_SPORADIC_SERVER */
#else /* _POSIX_SPORADIC_SERVER */
	/* [160] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SPORADIC_SERVER */
#endif /* !_POSIX_SPORADIC_SERVER */
#ifdef _POSIX_THREAD_SPORADIC_SERVER
	/* [161] = */ _POSIX_THREAD_SPORADIC_SERVER, /* _SC_THREAD_SPORADIC_SERVER */
#else /* _POSIX_THREAD_SPORADIC_SERVER */
	/* [161] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_THREAD_SPORADIC_SERVER */
#endif /* !_POSIX_THREAD_SPORADIC_SERVER */
#ifdef _POSIX_SYSTEM_DATABASE
	/* [162] = */ _POSIX_SYSTEM_DATABASE, /* _SC_SYSTEM_DATABASE */
#else /* _POSIX_SYSTEM_DATABASE */
	/* [162] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SYSTEM_DATABASE */
#endif /* !_POSIX_SYSTEM_DATABASE */
#ifdef _POSIX_SYSTEM_DATABASE_R
	/* [163] = */ _POSIX_SYSTEM_DATABASE_R, /* _SC_SYSTEM_DATABASE_R */
#else /* _POSIX_SYSTEM_DATABASE_R */
	/* [163] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SYSTEM_DATABASE_R */
#endif /* !_POSIX_SYSTEM_DATABASE_R */
#ifdef _POSIX_TIMEOUTS
	/* [164] = */ _POSIX_TIMEOUTS, /* _SC_TIMEOUTS */
#else /* _POSIX_TIMEOUTS */
	/* [164] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TIMEOUTS */
#endif /* !_POSIX_TIMEOUTS */
#ifdef _POSIX_TYPED_MEMORY_OBJECTS
	/* [165] = */ _POSIX_TYPED_MEMORY_OBJECTS, /* _SC_TYPED_MEMORY_OBJECTS */
#else /* _POSIX_TYPED_MEMORY_OBJECTS */
	/* [165] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TYPED_MEMORY_OBJECTS */
#endif /* !_POSIX_TYPED_MEMORY_OBJECTS */
#ifdef _POSIX_USER_GROUPS
	/* [166] = */ _POSIX_USER_GROUPS, /* _SC_USER_GROUPS */
#else /* _POSIX_USER_GROUPS */
	/* [166] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_USER_GROUPS */
#endif /* !_POSIX_USER_GROUPS */
#ifdef _POSIX_USER_GROUPS_R
	/* [167] = */ _POSIX_USER_GROUPS_R, /* _SC_USER_GROUPS_R */
#else /* _POSIX_USER_GROUPS_R */
	/* [167] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_USER_GROUPS_R */
#endif /* !_POSIX_USER_GROUPS_R */
#ifdef _POSIX2_PBS
	/* [168] = */ _POSIX2_PBS, /* _SC_2_PBS */
#else /* _POSIX2_PBS */
	/* [168] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_PBS */
#endif /* !_POSIX2_PBS */
#ifdef _POSIX2_PBS_ACCOUNTING
	/* [169] = */ _POSIX2_PBS_ACCOUNTING, /* _SC_2_PBS_ACCOUNTING */
#else /* _POSIX2_PBS_ACCOUNTING */
	/* [169] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_PBS_ACCOUNTING */
#endif /* !_POSIX2_PBS_ACCOUNTING */
#ifdef _POSIX2_PBS_LOCATE
	/* [170] = */ _POSIX2_PBS_LOCATE, /* _SC_2_PBS_LOCATE */
#else /* _POSIX2_PBS_LOCATE */
	/* [170] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_PBS_LOCATE */
#endif /* !_POSIX2_PBS_LOCATE */
#ifdef _POSIX2_PBS_MESSAGE
	/* [171] = */ _POSIX2_PBS_MESSAGE, /* _SC_2_PBS_MESSAGE */
#else /* _POSIX2_PBS_MESSAGE */
	/* [171] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_PBS_MESSAGE */
#endif /* !_POSIX2_PBS_MESSAGE */
#ifdef _POSIX2_PBS_TRACK
	/* [172] = */ _POSIX2_PBS_TRACK, /* _SC_2_PBS_TRACK */
#else /* _POSIX2_PBS_TRACK */
	/* [172] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_PBS_TRACK */
#endif /* !_POSIX2_PBS_TRACK */
	/* [173] = */ SYSCONF_ENTRY_UNDEFINED, /* _SC_SYMLOOP_MAX */
	/* [174] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_STREAMS */
#ifdef _POSIX2_PBS_CHECKPOINT
	/* [175] = */ _POSIX2_PBS_CHECKPOINT, /* _SC_2_PBS_CHECKPOINT */
#else /* _POSIX2_PBS_CHECKPOINT */
	/* [175] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_2_PBS_CHECKPOINT */
#endif /* !_POSIX2_PBS_CHECKPOINT */
	/* [176] = */ SYSCONF_ENTRY_UNDEFINED, /* 176 */
	/* [177] = */ SYSCONF_ENTRY_UNDEFINED, /* 177 */
	/* [178] = */ SYSCONF_ENTRY_UNDEFINED, /* 178 */
	/* [179] = */ SYSCONF_ENTRY_UNDEFINED, /* 179 */
#ifdef HOST_NAME_MAX
	/* [180] = */ HOST_NAME_MAX, /* _SC_HOST_NAME_MAX */
#else /* HOST_NAME_MAX */
	/* [180] = */ _POSIX_HOST_NAME_MAX, /* _SC_HOST_NAME_MAX */
#endif /* !HOST_NAME_MAX */
#ifdef _POSIX_TRACE
	/* [181] = */ _POSIX_TRACE, /* _SC_TRACE */
#else /* _POSIX_TRACE */
	/* [181] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TRACE */
#endif /* !_POSIX_TRACE */
	/* [182] = */ _POSIX_TRACE_EVENT_FILTER, /* _SC_TRACE_EVENT_FILTER */
	/* [183] = */ _POSIX_TRACE_INHERIT, /* _SC_TRACE_INHERIT */
	/* [184] = */ _POSIX_TRACE_LOG, /* _SC_TRACE_LOG */
	/* [185] = */ 0, /* _SC_LEVEL1_ICACHE_SIZE */
	/* [186] = */ 0, /* _SC_LEVEL1_ICACHE_ASSOC */
	/* [187] = */ 0, /* _SC_LEVEL1_ICACHE_LINESIZE */
	/* [188] = */ 0, /* _SC_LEVEL1_DCACHE_SIZE */
	/* [189] = */ 0, /* _SC_LEVEL1_DCACHE_ASSOC */
	/* [190] = */ 0, /* _SC_LEVEL1_DCACHE_LINESIZE */
	/* [191] = */ 0, /* _SC_LEVEL2_CACHE_SIZE */
	/* [192] = */ 0, /* _SC_LEVEL2_CACHE_ASSOC */
	/* [193] = */ 0, /* _SC_LEVEL2_CACHE_LINESIZE */
	/* [194] = */ 0, /* _SC_LEVEL3_CACHE_SIZE */
	/* [195] = */ 0, /* _SC_LEVEL3_CACHE_ASSOC */
	/* [196] = */ 0, /* _SC_LEVEL3_CACHE_LINESIZE */
	/* [197] = */ 0, /* _SC_LEVEL4_CACHE_SIZE */
	/* [198] = */ 0, /* _SC_LEVEL4_CACHE_ASSOC */
	/* [199] = */ 0, /* _SC_LEVEL4_CACHE_LINESIZE */
	/* [200] = */ SYSCONF_ENTRY_UNDEFINED, /* 200 */
	/* [201] = */ SYSCONF_ENTRY_UNDEFINED, /* 201 */
	/* [202] = */ SYSCONF_ENTRY_UNDEFINED, /* 202 */
	/* [203] = */ SYSCONF_ENTRY_UNDEFINED, /* 203 */
	/* [204] = */ SYSCONF_ENTRY_UNDEFINED, /* 204 */
	/* [205] = */ SYSCONF_ENTRY_UNDEFINED, /* 205 */
	/* [206] = */ SYSCONF_ENTRY_UNDEFINED, /* 206 */
	/* [207] = */ SYSCONF_ENTRY_UNDEFINED, /* 207 */
	/* [208] = */ SYSCONF_ENTRY_UNDEFINED, /* 208 */
	/* [209] = */ SYSCONF_ENTRY_UNDEFINED, /* 209 */
	/* [210] = */ SYSCONF_ENTRY_UNDEFINED, /* 210 */
	/* [211] = */ SYSCONF_ENTRY_UNDEFINED, /* 211 */
	/* [212] = */ SYSCONF_ENTRY_UNDEFINED, /* 212 */
	/* [213] = */ SYSCONF_ENTRY_UNDEFINED, /* 213 */
	/* [214] = */ SYSCONF_ENTRY_UNDEFINED, /* 214 */
	/* [215] = */ SYSCONF_ENTRY_UNDEFINED, /* 215 */
	/* [216] = */ SYSCONF_ENTRY_UNDEFINED, /* 216 */
	/* [217] = */ SYSCONF_ENTRY_UNDEFINED, /* 217 */
	/* [218] = */ SYSCONF_ENTRY_UNDEFINED, /* 218 */
	/* [219] = */ SYSCONF_ENTRY_UNDEFINED, /* 219 */
	/* [220] = */ SYSCONF_ENTRY_UNDEFINED, /* 220 */
	/* [221] = */ SYSCONF_ENTRY_UNDEFINED, /* 221 */
	/* [222] = */ SYSCONF_ENTRY_UNDEFINED, /* 222 */
	/* [223] = */ SYSCONF_ENTRY_UNDEFINED, /* 223 */
	/* [224] = */ SYSCONF_ENTRY_UNDEFINED, /* 224 */
	/* [225] = */ SYSCONF_ENTRY_UNDEFINED, /* 225 */
	/* [226] = */ SYSCONF_ENTRY_UNDEFINED, /* 226 */
	/* [227] = */ SYSCONF_ENTRY_UNDEFINED, /* 227 */
	/* [228] = */ SYSCONF_ENTRY_UNDEFINED, /* 228 */
	/* [229] = */ SYSCONF_ENTRY_UNDEFINED, /* 229 */
	/* [230] = */ SYSCONF_ENTRY_UNDEFINED, /* 230 */
	/* [231] = */ SYSCONF_ENTRY_UNDEFINED, /* 231 */
	/* [232] = */ SYSCONF_ENTRY_UNDEFINED, /* 232 */
	/* [233] = */ SYSCONF_ENTRY_UNDEFINED, /* 233 */
	/* [234] = */ SYSCONF_ENTRY_UNDEFINED, /* 234 */
#ifdef _POSIX_IPV6
	/* [235] = */ _POSIX_IPV6, /* _SC_IPV6 */
#else /* _POSIX_IPV6 */
	/* [235] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_IPV6 */
#endif /* !_POSIX_IPV6 */
#ifdef _POSIX_RAW_SOCKETS
	/* [236] = */ _POSIX_RAW_SOCKETS, /* _SC_RAW_SOCKETS */
#else /* _POSIX_RAW_SOCKETS */
	/* [236] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_RAW_SOCKETS */
#endif /* !_POSIX_RAW_SOCKETS */
	/* [237] = */ SYSCONF_ENTRY_UNDEFINED, /* 237 */
	/* [238] = */ SYSCONF_ENTRY_UNDEFINED, /* 238 */
	/* [239] = */ SYSCONF_ENTRY_UNDEFINED, /* 239 */
	/* [240] = */ SYSCONF_ENTRY_UNDEFINED, /* 240 */
#ifdef _POSIX_SS_REPL_MAX
	/* [241] = */ _POSIX_SS_REPL_MAX, /* _SC_SS_REPL_MAX */
#else /* _POSIX_SS_REPL_MAX */
	/* [241] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_SS_REPL_MAX */
#endif /* !_POSIX_SS_REPL_MAX */
	/* [242] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TRACE_EVENT_NAME_MAX */
	/* [243] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TRACE_NAME_MAX */
	/* [244] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TRACE_SYS_MAX */
	/* [245] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_TRACE_USER_EVENT_MAX */
	/* [246] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_XOPEN_STREAMS */
#ifdef _POSIX_THREAD_ROBUST_PRIO_INHERIT
	/* [247] = */ _POSIX_THREAD_ROBUST_PRIO_INHERIT, /* _SC_THREAD_ROBUST_PRIO_INHERIT */
#else /* _POSIX_THREAD_ROBUST_PRIO_INHERIT */
	/* [247] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_THREAD_ROBUST_PRIO_INHERIT */
#endif /* !_POSIX_THREAD_ROBUST_PRIO_INHERIT */
#ifdef _POSIX_THREAD_ROBUST_PRIO_PROTECT
	/* [248] = */ _POSIX_THREAD_ROBUST_PRIO_PROTECT, /* _SC_THREAD_ROBUST_PRIO_PROTECT */
#else /* _POSIX_THREAD_ROBUST_PRIO_PROTECT */
	/* [248] = */ SYSCONF_ENTRY_UNLIMITED, /* _SC_THREAD_ROBUST_PRIO_PROTECT */
#endif /* !_POSIX_THREAD_ROBUST_PRIO_PROTECT */
/*[[[end]]]*/
};
STATIC_ASSERT(COMPILER_LENOF(sysconf_table) <= _SC_COUNT);



/*[[[head:libc_sysconf,hash:CRC-32=0x4e89c8f0]]]*/
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.system.configuration") WUNUSED longptr_t
NOTHROW_RPC(LIBCCALL libc_sysconf)(__STDC_INT_AS_UINT_T name)
/*[[[body:libc_sysconf]]]*/
{
	longptr_t result;
	if (name < COMPILER_LENOF(sysconf_table)) {
		result = sysconf_table[name];
		if (result != SYSCONF_ENTRY_UNDEFINED)
			return result;
	}
	switch (name) {

	/* Special  handling to deal with names where the actual config value
	 * overlaps  with the `SYSCONF_ENTRY_UNDEFINED' marker. Note that for
	 * this purpose, `SYSCONF_ENTRY_UNDEFINED' has a value of `INT32_MIN' */

/*[[[deemon
for (local name: SYSCONF_VALUES_LO_INT32) {
	print("#if ", name, " == INT32_MIN");
	print("#define NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP");
	print("	case _SC_", name, ":");
	print("#endif /" "* ", name, " == INT32_MIN *" "/");
}
]]]*/
#if CHAR_MIN == INT32_MIN
#define NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP
	case _SC_CHAR_MIN:
#endif /* CHAR_MIN == INT32_MIN */
#if INT_MIN == INT32_MIN
#define NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP
	case _SC_INT_MIN:
#endif /* INT_MIN == INT32_MIN */
#if SCHAR_MIN == INT32_MIN
#define NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP
	case _SC_SCHAR_MIN:
#endif /* SCHAR_MIN == INT32_MIN */
#if SHRT_MIN == INT32_MIN
#define NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP
	case _SC_SHRT_MIN:
#endif /* SHRT_MIN == INT32_MIN */
/*[[[end]]]*/
#ifdef NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP
#undef NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP
		result = INT32_MIN;
		break;
#endif /* NEED_SYSCONF_INT32_MIN_CONFVAL_OVERLAP */


	/* Special  handling for conf values outside of the
	 * 32-bit range required by the config table above. */
/*[[[deemon
for (local name: SYSCONF_VALUES_HI_INT32) {
	print("#if ", name, " > INT32_MAX");
	print("	case _SC_", name, ":");
	print("		result = (longptr_t)", name, ";");
	print("		break;");
	print("#endif /" "* ", name, " > INT32_MAX *" "/");
}

for (local name: SYSCONF_VALUES_LO_INT32) {
	print("#if ", name, " < INT32_MIN");
	print("	case _SC_", name, ":");
	print("		result = (longptr_t)", name, ";");
	print("		break;");
	print("#endif /" "* ", name, " < INT32_MIN *" "/");
}
]]]*/
#if CHAR_MAX > INT32_MAX
	case _SC_CHAR_MAX:
		result = (longptr_t)CHAR_MAX;
		break;
#endif /* CHAR_MAX > INT32_MAX */
#if INT_MAX > INT32_MAX
	case _SC_INT_MAX:
		result = (longptr_t)INT_MAX;
		break;
#endif /* INT_MAX > INT32_MAX */
#if SSIZE_MAX > INT32_MAX
	case _SC_SSIZE_MAX:
		result = (longptr_t)SSIZE_MAX;
		break;
#endif /* SSIZE_MAX > INT32_MAX */
#if SCHAR_MAX > INT32_MAX
	case _SC_SCHAR_MAX:
		result = (longptr_t)SCHAR_MAX;
		break;
#endif /* SCHAR_MAX > INT32_MAX */
#if SHRT_MAX > INT32_MAX
	case _SC_SHRT_MAX:
		result = (longptr_t)SHRT_MAX;
		break;
#endif /* SHRT_MAX > INT32_MAX */
#if UCHAR_MAX > INT32_MAX
	case _SC_UCHAR_MAX:
		result = (longptr_t)UCHAR_MAX;
		break;
#endif /* UCHAR_MAX > INT32_MAX */
#if UINT_MAX > INT32_MAX
	case _SC_UINT_MAX:
		result = (longptr_t)UINT_MAX;
		break;
#endif /* UINT_MAX > INT32_MAX */
#if ULONG_MAX > INT32_MAX
	case _SC_ULONG_MAX:
		result = (longptr_t)ULONG_MAX;
		break;
#endif /* ULONG_MAX > INT32_MAX */
#if USHRT_MAX > INT32_MAX
	case _SC_USHRT_MAX:
		result = (longptr_t)USHRT_MAX;
		break;
#endif /* USHRT_MAX > INT32_MAX */
#if CHAR_MIN < INT32_MIN
	case _SC_CHAR_MIN:
		result = (longptr_t)CHAR_MIN;
		break;
#endif /* CHAR_MIN < INT32_MIN */
#if INT_MIN < INT32_MIN
	case _SC_INT_MIN:
		result = (longptr_t)INT_MIN;
		break;
#endif /* INT_MIN < INT32_MIN */
#if SCHAR_MIN < INT32_MIN
	case _SC_SCHAR_MIN:
		result = (longptr_t)SCHAR_MIN;
		break;
#endif /* SCHAR_MIN < INT32_MIN */
#if SHRT_MIN < INT32_MIN
	case _SC_SHRT_MIN:
		result = (longptr_t)SHRT_MIN;
		break;
#endif /* SHRT_MIN < INT32_MIN */
/*[[[end]]]*/

	case _SC_CLK_TCK:
		result = CLK_TCK; /* TODO */
		break;

	case _SC_NPROCESSORS_CONF:
		result = get_nprocs_conf();
		break;

	case _SC_NPROCESSORS_ONLN:
		result = get_nprocs();
		break;

	case _SC_PHYS_PAGES:
		result = get_phys_pages();
		break;

	case _SC_AVPHYS_PAGES:
		result = get_avphys_pages();
		break;

	case _SC_SYMLOOP_MAX:
		result = SYMLOOP_MAX; /* TODO: Kernel:`THIS_FS->f_lnkmax' */
		break;

	default:
		result = libc_seterrno(EINVAL);
		break;
	}
	return result;
}
/*[[[end:libc_sysconf]]]*/

/*[[[head:libc_freadlinkat,hash:CRC-32=0xbfc3ac49]]]*/
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.fs.property") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBCCALL libc_freadlinkat)(fd_t dfd,
                                       char const *path,
                                       char *buf,
                                       size_t buflen,
                                       atflag_t flags)
/*[[[body:libc_freadlinkat]]]*/
{
	ssize_t result;
	result = sys_freadlinkat(dfd, path, buf, buflen, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_freadlinkat]]]*/

/*[[[head:libc_readall,hash:CRC-32=0x1811c1fc]]]*/
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_readall)(fd_t fd,
                                   void *buf,
                                   size_t bufsize)
/*[[[body:libc_readall]]]*/
{
	ssize_t result, temp;
	result = read(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = read(fd,
			            (byte_t *)buf + (size_t)result,
			            bufsize - (size_t)result);
			if (temp <= 0) {
				errno_t old_error = libc_geterrno();
				/* Try to un-read data that had already been loaded. */
				libc_lseek64(fd, -(off64_t)(pos64_t)result, SEEK_CUR);
				libc_seterrno(old_error);
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
/*[[[end:libc_readall]]]*/

/*[[[head:libc_writeall,hash:CRC-32=0xa9ae1bd1]]]*/
/* >> writeall(3)
 * Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_writeall)(fd_t fd,
                                    void const *buf,
                                    size_t bufsize)
/*[[[body:libc_writeall]]]*/
{
	ssize_t result, temp;
	result = write(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = write(fd,
			            (byte_t *)buf + (size_t)result,
			            bufsize - (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
/*[[[end:libc_writeall]]]*/

/*[[[head:libc_preadall,hash:CRC-32=0x208b5ffc]]]*/
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadall)(fd_t fd,
                                    void *buf,
                                    size_t bufsize,
                                    __PIO_OFFSET offset)
/*[[[body:libc_preadall]]]*/
{
	ssize_t result, temp;
	result = pread(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = pread(fd,
			             (byte_t *)buf + (size_t)result,
			             bufsize - (size_t)result,
			             offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
/*[[[end:libc_preadall]]]*/

/*[[[head:libc_preadall64,hash:CRC-32=0x65d5e44c]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_preadall64, libc_preadall);
#else /* MAGIC:alias */
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.io.large.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadall64)(fd_t fd,
                                      void *buf,
                                      size_t bufsize,
                                      __PIO_OFFSET64 offset)
/*[[[body:libc_preadall64]]]*/
{
	ssize_t result, temp;
	result = pread64(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = pread64(fd,
			               (byte_t *)buf + (size_t)result,
			               bufsize - (size_t)result,
			               offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_preadall64]]]*/

/*[[[head:libc_pwriteall,hash:CRC-32=0x61cf24d8]]]*/
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwriteall)(fd_t fd,
                                     void const *buf,
                                     size_t bufsize,
                                     __PIO_OFFSET offset)
/*[[[body:libc_pwriteall]]]*/
{
	ssize_t result, temp;
	result = pwrite(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = pwrite(fd,
			              (byte_t *)buf + (size_t)result,
			              bufsize - (size_t)result,
			              offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
/*[[[end:libc_pwriteall]]]*/

/*[[[head:libc_pwriteall64,hash:CRC-32=0x4aa10dd8]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwriteall64, libc_pwriteall);
#else /* MAGIC:alias */
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.io.large.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwriteall64)(fd_t fd,
                                       void *buf,
                                       size_t bufsize,
                                       __PIO_OFFSET64 offset)
/*[[[body:libc_pwriteall64]]]*/
{
	ssize_t result, temp;
	result = pwrite64(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = pwrite64(fd,
			                (byte_t *)buf + (size_t)result,
			                bufsize - (size_t)result,
			                offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pwriteall64]]]*/

/*[[[head:libc_gettid,hash:CRC-32=0x530df3fd]]]*/
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
INTERN ATTR_SECTION(".text.crt.sched.thread") ATTR_CONST WUNUSED pid_t
NOTHROW(LIBCCALL libc_gettid)(void)
/*[[[body:libc_gettid]]]*/
{
	struct pthread *me;
	/* Use pthread_self(), since that one will already
	 * do all of the  lazy TID initialization for  us! */
	me = libc_pthread_self();
	return _pthread_tid(me);
}
/*[[[end:libc_gettid]]]*/

/*[[[head:libc_sync,hash:CRC-32=0x1431d596]]]*/
/* >> sync(2)
 * Synchronize all disk operations of all mounted file systems and flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
INTERN ATTR_SECTION(".text.crt.fs.modify") void
NOTHROW_RPC(LIBCCALL libc_sync)(void)
/*[[[body:libc_sync]]]*/
{
	sys_sync();
}
/*[[[end:libc_sync]]]*/

/*[[[head:libc_syncfs,hash:CRC-32=0x95a3c051]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") int
NOTHROW_RPC(LIBCCALL libc_syncfs)(fd_t fd)
/*[[[body:libc_syncfs]]]*/
{
	errno_t error;
	error = sys_syncfs(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_syncfs]]]*/

/*[[[head:libc_nice,hash:CRC-32=0x314a2f67]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_nice)(int inc)
/*[[[body:libc_nice]]]*/
{
	syscall_slong_t error;
#ifdef __sys_nice_defined
	error = sys_nice(-inc);
	if unlikely(E_ISERR(error))
		goto err;
#else /* __sys_Xnice_defined */
	error = sys_getpriority(PRIO_PROCESS, 0);
	if unlikely(E_ISERR(error))
		goto err;
	error = (20 - error);
	error += inc;
	error = sys_setpriority(PRIO_PROCESS, 0, (syscall_ulong_t)(20 - error));
	if unlikely(E_ISERR(error))
		goto err;
	error = sys_getpriority(PRIO_PROCESS, 0);
	if unlikely(E_ISERR(error))
		goto err;
#endif /* !__sys_Xnice_defined */
	return 20 - error;
err:
	return libc_seterrno(-error);
}
/*[[[end:libc_nice]]]*/

/*[[[head:libc_fsync,hash:CRC-32=0x9bcfb5e6]]]*/
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTERN ATTR_SECTION(".text.crt.io.sync") int
NOTHROW_RPC(LIBCCALL libc_fsync)(fd_t fd)
/*[[[body:libc_fsync]]]*/
{
	errno_t error;
	error = sys_fsync(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_fsync]]]*/

/*[[[head:libc_fdatasync,hash:CRC-32=0xcadd0612]]]*/
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTERN ATTR_SECTION(".text.crt.io.sync") int
NOTHROW_RPC(LIBCCALL libc_fdatasync)(fd_t fd)
/*[[[body:libc_fdatasync]]]*/
{
	errno_t error;
	error = sys_fdatasync(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_fdatasync]]]*/

/*[[[head:libc_setmode,hash:CRC-32=0x5440ef72]]]*/
/* >> setmode(3), getmode(3) */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc_setmode)(char const *mode_str)
/*[[[body:libc_setmode]]]*/
/*AUTO*/{
	(void)mode_str;
	CRT_UNIMPLEMENTEDF("setmode(%q)", mode_str); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_setmode]]]*/

/*[[[head:libc_getmode,hash:CRC-32=0xd63cf099]]]*/
/* >> setmode(3), getmode(3) */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED NONNULL((1)) mode_t
NOTHROW_NCX(LIBCCALL libc_getmode)(void const *bbox,
                                   mode_t mode)
/*[[[body:libc_getmode]]]*/
/*AUTO*/{
	(void)bbox;
	(void)mode;
	CRT_UNIMPLEMENTEDF("getmode(%p, %" PRIxN(__SIZEOF_MODE_T__) ")", bbox, mode); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getmode]]]*/

/*[[[head:libc_ctermid_r,hash:CRC-32=0x4e77dd5c]]]*/
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
INTERN ATTR_SECTION(".text.crt.io.tty") char *
NOTHROW_NCX(LIBCCALL libc_ctermid_r)(char *s)
/*[[[body:libc_ctermid_r]]]*/
/*AUTO*/{
	return s ? ctermid(s) : NULL;
}
/*[[[end:libc_ctermid_r]]]*/






/*[[[start:exports,hash:CRC-32=0xc1427a34]]]*/
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execve, libc_execve);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execve, libc_execve);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_getpid, libc_getpid);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__getpid, libc_getpid);
DEFINE_PUBLIC_ALIAS(getpid, libc_getpid);
DEFINE_PUBLIC_ALIAS(gettid, libc_gettid);
DEFINE_PUBLIC_ALIAS(__pipe, libc_pipe);
DEFINE_PUBLIC_ALIAS(pipe, libc_pipe);
DEFINE_PUBLIC_ALIAS(sleep, libc_sleep);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_commit, libc_fsync);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(fsync, libc_fsync);
DEFINE_PUBLIC_ALIAS(getppid, libc_getppid);
DEFINE_PUBLIC_ALIAS(getpgrp, libc_getpgrp);
DEFINE_PUBLIC_ALIAS(__setpgid, libc_setpgid);
DEFINE_PUBLIC_ALIAS(setpgid, libc_setpgid);
DEFINE_PUBLIC_ALIAS(setsid, libc_setsid);
DEFINE_PUBLIC_ALIAS(getuid, libc_getuid);
DEFINE_PUBLIC_ALIAS(geteuid, libc_geteuid);
DEFINE_PUBLIC_ALIAS(getgid, libc_getgid);
DEFINE_PUBLIC_ALIAS(getegid, libc_getegid);
DEFINE_PUBLIC_ALIAS(getgroups, libc_getgroups);
DEFINE_PUBLIC_ALIAS(setuid, libc_setuid);
DEFINE_PUBLIC_ALIAS(setgid, libc_setgid);
DEFINE_PUBLIC_ALIAS(__fork, libc_fork);
DEFINE_PUBLIC_ALIAS(fork, libc_fork);
DEFINE_PUBLIC_ALIAS(alarm, libc_alarm);
DEFINE_PUBLIC_ALIAS(pause, libc_pause);
DEFINE_PUBLIC_ALIAS(fpathconf, libc_fpathconf);
DEFINE_PUBLIC_ALIAS(ttyname, libc_ttyname);
DEFINE_PUBLIC_ALIAS(ttyname_r, libc_ttyname_r);
DEFINE_PUBLIC_ALIAS(tcgetpgrp, libc_tcgetpgrp);
DEFINE_PUBLIC_ALIAS(tcsetpgrp, libc_tcsetpgrp);
DEFINE_PUBLIC_ALIAS(chown, libc_chown);
DEFINE_PUBLIC_ALIAS(pathconf, libc_pathconf);
DEFINE_PUBLIC_ALIAS(link, libc_link);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_read, libc_read);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__read, libc_read);
DEFINE_PUBLIC_ALIAS(read, libc_read);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_write, libc_write);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__write, libc_write);
DEFINE_PUBLIC_ALIAS(write, libc_write);
DEFINE_PUBLIC_ALIAS(readall, libc_readall);
DEFINE_PUBLIC_ALIAS(writeall, libc_writeall);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_lseek, libc_lseek);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__lseek, libc_lseek);
DEFINE_PUBLIC_ALIAS(lseek, libc_lseek);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_dup2, libc_dup2);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__dup2, libc_dup2);
DEFINE_PUBLIC_ALIAS(dup2, libc_dup2);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_dup, libc_dup);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(dup, libc_dup);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_close, libc_close);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__close, libc_close);
DEFINE_PUBLIC_ALIAS(close, libc_close);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_access, libc_access);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(access, libc_access);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_chdir, libc_chdir);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(chdir, libc_chdir);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_getcwd, libc_getcwd);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(getcwd, libc_getcwd);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_unlink, libc_unlink);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(unlink, libc_unlink);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_rmdir, libc_rmdir);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(rmdir, libc_rmdir);
DEFINE_PUBLIC_ALIAS(eaccess, libc_euidaccess);
DEFINE_PUBLIC_ALIAS(euidaccess, libc_euidaccess);
DEFINE_PUBLIC_ALIAS(faccessat, libc_faccessat);
DEFINE_PUBLIC_ALIAS(fchownat, libc_fchownat);
DEFINE_PUBLIC_ALIAS(linkat, libc_linkat);
DEFINE_PUBLIC_ALIAS(symlinkat, libc_symlinkat);
DEFINE_PUBLIC_ALIAS(readlinkat, libc_readlinkat);
DEFINE_PUBLIC_ALIAS(freadlinkat, libc_freadlinkat);
DEFINE_PUBLIC_ALIAS(unlinkat, libc_unlinkat);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_lseeki64, libc_lseek64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(lseek64, libc_lseek64);
DEFINE_PUBLIC_ALIAS(pread, libc_pread);
DEFINE_PUBLIC_ALIAS(pwrite, libc_pwrite);
DEFINE_PUBLIC_ALIAS(preadall, libc_preadall);
DEFINE_PUBLIC_ALIAS(pwriteall, libc_pwriteall);
DEFINE_PUBLIC_ALIAS(__pread64, libc_pread64);
DEFINE_PUBLIC_ALIAS(pread64, libc_pread64);
DEFINE_PUBLIC_ALIAS(__pwrite64, libc_pwrite64);
DEFINE_PUBLIC_ALIAS(pwrite64, libc_pwrite64);
DEFINE_PUBLIC_ALIAS(preadall64, libc_preadall64);
DEFINE_PUBLIC_ALIAS(pwriteall64, libc_pwriteall64);
DEFINE_PUBLIC_ALIAS(dup3, libc_dup3);
DEFINE_PUBLIC_ALIAS(pipe2, libc_pipe2);
DEFINE_PUBLIC_ALIAS(get_current_dir_name, libc_get_current_dir_name);
DEFINE_PUBLIC_ALIAS(syncfs, libc_syncfs);
DEFINE_PUBLIC_ALIAS(group_member, libc_group_member);
DEFINE_PUBLIC_ALIAS(getresuid, libc_getresuid);
DEFINE_PUBLIC_ALIAS(getresgid, libc_getresgid);
DEFINE_PUBLIC_ALIAS(setresuid, libc_setresuid);
DEFINE_PUBLIC_ALIAS(setresgid, libc_setresgid);
DEFINE_PUBLIC_ALIAS(usleep, libc_usleep);
DEFINE_PUBLIC_ALIAS(getwd, libc_getwd);
DEFINE_PUBLIC_ALIAS(ualarm, libc_ualarm);
DEFINE_PUBLIC_ALIAS(fchown, libc_fchown);
DEFINE_PUBLIC_ALIAS(fchdir, libc_fchdir);
DEFINE_PUBLIC_ALIAS(__getpgid, libc_getpgid);
DEFINE_PUBLIC_ALIAS(getpgid, libc_getpgid);
DEFINE_PUBLIC_ALIAS(getsid, libc_getsid);
DEFINE_PUBLIC_ALIAS(lchown, libc_lchown);
DEFINE_PUBLIC_ALIAS(truncate, libc_truncate);
DEFINE_PUBLIC_ALIAS(truncate64, libc_truncate64);
DEFINE_PUBLIC_ALIAS(fexecve, libc_fexecve);
DEFINE_PUBLIC_ALIAS(nice, libc_nice);
DEFINE_PUBLIC_ALIAS(confstr, libc_confstr);
DEFINE_PUBLIC_ALIAS(sync, libc_sync);
DEFINE_PUBLIC_ALIAS(setpgrp, libc_setpgrp);
DEFINE_PUBLIC_ALIAS(setreuid, libc_setreuid);
DEFINE_PUBLIC_ALIAS(setregid, libc_setregid);
DEFINE_PUBLIC_ALIAS(gethostid, libc_gethostid);
DEFINE_PUBLIC_ALIAS(seteuid, libc_seteuid);
DEFINE_PUBLIC_ALIAS(setegid, libc_setegid);
DEFINE_PUBLIC_ALIAS(ttyslot, libc_ttyslot);
DEFINE_PUBLIC_ALIAS(symlink, libc_symlink);
DEFINE_PUBLIC_ALIAS(readlink, libc_readlink);
DEFINE_PUBLIC_ALIAS(gethostname, libc_gethostname);
DEFINE_PUBLIC_ALIAS(setlogin, libc_setlogin);
DEFINE_PUBLIC_ALIAS(sethostname, libc_sethostname);
DEFINE_PUBLIC_ALIAS(sethostid, libc_sethostid);
DEFINE_PUBLIC_ALIAS(getdomainname, libc_getdomainname);
DEFINE_PUBLIC_ALIAS(setdomainname, libc_setdomainname);
DEFINE_PUBLIC_ALIAS(vhangup, libc_vhangup);
DEFINE_PUBLIC_ALIAS(profil, libc_profil);
DEFINE_PUBLIC_ALIAS(getusershell, libc_getusershell);
DEFINE_PUBLIC_ALIAS(endusershell, libc_endusershell);
DEFINE_PUBLIC_ALIAS(setusershell, libc_setusershell);
DEFINE_PUBLIC_ALIAS(daemon, libc_daemon);
DEFINE_PUBLIC_ALIAS(revoke, libc_revoke);
DEFINE_PUBLIC_ALIAS(chroot, libc_chroot);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_chsize, libc_ftruncate);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(chsize, libc_ftruncate);
DEFINE_PUBLIC_ALIAS(ftruncate, libc_ftruncate);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_chsize_s, libc_ftruncate64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(ftruncate64, libc_ftruncate64);
DEFINE_PUBLIC_ALIAS(brk, libc_brk);
DEFINE_PUBLIC_ALIAS(__sbrk, libc_sbrk);
DEFINE_PUBLIC_ALIAS(sbrk, libc_sbrk);
DEFINE_PUBLIC_ALIAS(fdatasync, libc_fdatasync);
DEFINE_PUBLIC_ALIAS(setmode, libc_setmode);
DEFINE_PUBLIC_ALIAS(getmode, libc_getmode);
DEFINE_PUBLIC_ALIAS(ctermid_r, libc_ctermid_r);
DEFINE_PUBLIC_ALIAS(__sysconf, libc_sysconf);
DEFINE_PUBLIC_ALIAS(sysconf, libc_sysconf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UNISTD_C */
