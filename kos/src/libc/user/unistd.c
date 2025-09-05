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
#ifndef GUARD_LIBC_USER_UNISTD_C
#define GUARD_LIBC_USER_UNISTD_C 1
#define _KOS_SOURCE 1
#define _ALL_LIMITS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/exec/idata.h>
#include <kos/fcntl.h>
#include <kos/ioctl/file.h> /* needed for pathconf() */
#include <kos/ioctl/tty.h>
#include <kos/sched/shared-lock.h>
#include <kos/sys/ioctl.h>
#include <kos/unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/stat.h>
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
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

#include "../libc/dl.h"
#include "../libc/globals.h"
#include "../libc/syscalls.h"
#include "../libc/tls.h"
#include "fcntl.h"
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"

DECL_BEGIN


/*[[[head:libd_execve,hash:CRC-32=0x5b7ea3c5]]]*/
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int
NOTHROW_RPC(LIBDCALL libd_execve)(char const *__restrict path,
                                  __TARGV,
                                  __TENVP)
/*[[[body:libd_execve]]]*/
{
	errno_t result;
	result = sys_execveat(AT_FDCWD, path,
	                      (char *const *)___argv,
	                      (char *const *)___envp,
	                      libd_AT_DOSPATH);
	return libc_seterrno_neg(result);
}
/*[[[end:libd_execve]]]*/

/*[[[head:libc_execve,hash:CRC-32=0xa7fb2025]]]*/
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int
NOTHROW_RPC(LIBCCALL libc_execve)(char const *__restrict path,
                                  __TARGV,
                                  __TENVP)
/*[[[body:libc_execve]]]*/
{
	errno_t result;
	result = sys_execve(path,
	                    (char *const *)___argv,
	                    (char *const *)___envp);
	return libc_seterrno_neg(result);
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

/*[[[head:libc_pipe,hash:CRC-32=0xe80f556b]]]*/
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.access") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_pipe)(fd_t pipedes[2])
/*[[[body:libc_pipe]]]*/
{
	errno_t error = sys_pipe(pipedes);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_pipe]]]*/

/*[[[head:libc_sleep,hash:CRC-32=0x17df3938]]]*/
/* >> sleep(3)
 * Sleep for up to `seconds' seconds
 * @return: 0 : Timeout expired
 * @return: * : You were interrupted, and this many seconds were still left on the timeout */
INTERN ATTR_SECTION(".text.crt.system.utility") unsigned int
NOTHROW_RPC(LIBCCALL libc_sleep)(unsigned int seconds)
/*[[[body:libc_sleep]]]*/
{
	struct timespec req, rem;
	req.tv_sec  = (time_t)seconds;
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

/*[[[head:libc_setpgid,hash:CRC-32=0x7634a5a6]]]*/
/* >> setpgid(2)
 * Change  the ID of  the process group  associated with `pid's process.
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

/*[[[head:libc_setsid,hash:CRC-32=0x4b32f42e]]]*/
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making  it its own session  leader.
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
	uid_t result = _sys_getuid();
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
	uid_t result = _sys_geteuid();
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
	gid_t result = _sys_getgid();
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
	gid_t result = _sys_getegid();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getegid]]]*/

/*[[[head:libc_getgroups,hash:CRC-32=0xb2fe69a0]]]*/
/* >> getgroups(2)
 * @return: * : [count == 0] The required number of groups
 * @return: * : [count != 0] The number of groups that were actually returned
 * @return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups */
INTERN ATTR_SECTION(".text.crt.sched.user") ATTR_OUTS(2, 1) int
NOTHROW_NCX(LIBCCALL libc_getgroups)(int size,
                                     gid_t list[])
/*[[[body:libc_getgroups]]]*/
{
	errno_t result;
	result = _sys_getgroups((size_t)size, list);
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
	errno_t result = _sys_setuid(uid);
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
	errno_t result = _sys_setgid(gid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setgid]]]*/

/*[[[head:libc_fork,hash:CRC-32=0x8a8f497a]]]*/
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
INTERN ATTR_SECTION(".text.crt.sched.access") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_fork)(void)
/*[[[body:libc_fork]]]*/
{
	pid_t result = sys_fork();
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
	errno_t result = sys_pause();
	return libc_seterrno_neg(result);
}
/*[[[end:libc_pause]]]*/

/*[[[head:libd_chown,hash:CRC-32=0x41fa4f3]]]*/
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_chown)(char const *file,
                                 uid_t owner,
                                 gid_t group)
/*[[[body:libd_chown]]]*/
{
	return libd_fchownat(AT_FDCWD, file, owner, group, 0);
}
/*[[[end:libd_chown]]]*/

/*[[[head:libc_chown,hash:CRC-32=0x98a7a187]]]*/
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_chown)(char const *file,
                                 uid_t owner,
                                 gid_t group)
/*[[[body:libc_chown]]]*/
{
	errno_t result;
	result = _sys_chown(file, owner, group);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chown]]]*/

/*[[[head:libc_setlogin,hash:CRC-32=0x24fdec8d]]]*/
/* >> setlogin(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_setlogin)(char const *name)
/*[[[body:libc_setlogin]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("setlogin(name: %q)", name); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_setlogin]]]*/

/*[[[head:libd_link,hash:CRC-32=0xd27b7554]]]*/
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_link)(char const *from,
                                char const *to)
/*[[[body:libd_link]]]*/
{
	return libd_linkat(AT_FDCWD, from, AT_FDCWD, to, 0);
}
/*[[[end:libd_link]]]*/

/*[[[head:libc_link,hash:CRC-32=0x82190e09]]]*/
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_link)(char const *from,
                                char const *to)
/*[[[body:libc_link]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_link)
	return libc_linkat(AT_FDCWD, from, AT_FDCWD, to, 0);
#else /* __OPTIMIZE_SIZE__ || !SYS_link */
	errno_t result = sys_link(from, to);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_link */
}
/*[[[end:libc_link]]]*/

/*[[[head:libc_read,hash:CRC-32=0x4e5abb25]]]*/
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
INTERN ATTR_SECTION(".text.crt.io.read") ATTR_FDREAD(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_read)(fd_t fd,
                                void *buf,
                                size_t bufsize)
/*[[[body:libc_read]]]*/
{
	ssize_t result = sys_read(fd, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_read]]]*/

/*[[[head:libc_write,hash:CRC-32=0xb7ecfe22]]]*/
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_FDWRITE(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_write)(fd_t fd,
                                 void const *buf,
                                 size_t bufsize)
/*[[[body:libc_write]]]*/
{
	ssize_t result = sys_write(fd, buf, bufsize);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_write]]]*/

/*[[[head:libc_dup,hash:CRC-32=0xf90f4300]]]*/
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED ATTR_FDARG(1) fd_t
NOTHROW_NCX(LIBCCALL libc_dup)(fd_t fd)
/*[[[body:libc_dup]]]*/
{
	fd_t result = sys_dup(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup]]]*/

/* Must clear `libd_dos_fsroot' in `DOS$chroot()' and `DOS$dup[2|3]()' with AT_FDROOT */
INTDEF ATTR_SECTION(".text.crt.dos.fs.environ") void
NOTHROW(CC libd_dos_fsroot_changed)(void);

/*[[[head:libd_dup2,hash:CRC-32=0xa755c5c8]]]*/
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") ATTR_FDARG(1) fd_t
NOTHROW_NCX(LIBDCALL libd_dup2)(fd_t oldfd,
                                fd_t newfd)
/*[[[body:libd_dup2]]]*/
{
	fd_t result;
	result = libc_dup2(oldfd, newfd);
	if (result == 0 && newfd == AT_FDROOT)
		libd_dos_fsroot_changed();
	return result;
}
/*[[[end:libd_dup2]]]*/

/*[[[head:libc_dup2,hash:CRC-32=0xc1091db2]]]*/
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
INTERN ATTR_SECTION(".text.crt.io.access") ATTR_FDARG(1) fd_t
NOTHROW_NCX(LIBCCALL libc_dup2)(fd_t oldfd,
                                fd_t newfd)
/*[[[body:libc_dup2]]]*/
{
	fd_t result = sys_dup2(oldfd, newfd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup2]]]*/

/*[[[head:libd_dup3,hash:CRC-32=0xe1b5a0c7]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") ATTR_FDARG(1) fd_t
NOTHROW_NCX(LIBDCALL libd_dup3)(fd_t oldfd,
                                fd_t newfd,
                                oflag_t flags)
/*[[[body:libd_dup3]]]*/
{
	fd_t result;
	result = libc_dup3(oldfd, newfd, flags);
	if (result == 0 && newfd == AT_FDROOT)
		libd_dos_fsroot_changed();
	return result;
}
/*[[[end:libd_dup3]]]*/

/*[[[head:libc_dup3,hash:CRC-32=0xdd6e4358]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") ATTR_FDARG(1) fd_t
NOTHROW_NCX(LIBCCALL libc_dup3)(fd_t oldfd,
                                fd_t newfd,
                                oflag_t flags)
/*[[[body:libc_dup3]]]*/
{
	fd_t result = sys_dup3(oldfd, newfd, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_dup3]]]*/

/*[[[head:libc_close,hash:CRC-32=0x9922557c]]]*/
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
INTERN ATTR_SECTION(".text.crt.io.access") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_close)(fd_t fd)
/*[[[body:libc_close]]]*/
{
	errno_t result = sys_close(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_close]]]*/

/*[[[head:libc_close_range,hash:CRC-32=0x62ca1277]]]*/
/* >> close_range(2)
 * Close all files handles `>= minfd && <= maxfd' (but see `flags')
 * @param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.bsd.io.access") int
NOTHROW_NCX(LIBCCALL libc_close_range)(unsigned int minfd,
                                       unsigned int maxfd,
                                       unsigned int flags)
/*[[[body:libc_close_range]]]*/
{
	errno_t result = sys_close_range(minfd, maxfd, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_close_range]]]*/

/*[[[head:libd_access,hash:CRC-32=0x33b8235a]]]*/
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type'
 * @return: 0 : Access would be granted
 * @return: -1: Access would be denied (s.a. `errno') */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_access)(char const *file,
                                  __STDC_INT_AS_UINT_T type)
/*[[[body:libd_access]]]*/
{
	return libd_faccessat(AT_FDCWD, file, type, 0);
}
/*[[[end:libd_access]]]*/

/*[[[head:libc_access,hash:CRC-32=0x2a318517]]]*/
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type'
 * @return: 0 : Access would be granted
 * @return: -1: Access would be denied (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_access)(char const *file,
                                  __STDC_INT_AS_UINT_T type)
/*[[[body:libc_access]]]*/
{
	errno_t result = sys_access(file, (syscall_ulong_t)(unsigned int)type);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_access]]]*/

/*[[[head:libd_chdir,hash:CRC-32=0x3d7d4bc5]]]*/
/* >> chdir(2)
 * Change the current working directory to `path' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.basic_property") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_chdir)(char const *path)
/*[[[body:libd_chdir]]]*/
{
	return libd_fchdirat(AT_FDCWD, path, 0);
}
/*[[[end:libd_chdir]]]*/

/*[[[head:libc_chdir,hash:CRC-32=0x1abdf77e]]]*/
/* >> chdir(2)
 * Change the current working directory to `path' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_chdir)(char const *path)
/*[[[body:libc_chdir]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_chdir)
	return libc_fchdirat(AT_FDCWD, path, 0);
#else /* __OPTIMIZE_SIZE__ || !SYS_chdir */
	errno_t result = sys_chdir(path);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_chdir */
}
/*[[[end:libc_chdir]]]*/

/*[[[head:libd_fchdirat,hash:CRC-32=0xc5eccf13]]]*/
/* >> fchdirat(2)
 * Change the current working directory to `dfd:path'
 * @param: flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_fchdirat)(fd_t dfd,
                                    char const *path,
                                    atflag_t flags)
/*[[[body:libd_fchdirat]]]*/
{
	return libc_fchdirat(dfd, path, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_fchdirat]]]*/

/*[[[head:libc_fchdirat,hash:CRC-32=0x92e95c55]]]*/
/* >> fchdirat(2)
 * Change the current working directory to `dfd:path'
 * @param: flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_fchdirat)(fd_t dfd,
                                    char const *path,
                                    atflag_t flags)
/*[[[body:libc_fchdirat]]]*/
{
	errno_t result = sys_fchdirat(dfd, path, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchdirat]]]*/

/*[[[head:libd_getcwd,hash:CRC-32=0x36e8e42]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.basic_property") ATTR_OUT_OPT(1) char *
NOTHROW_RPC(LIBDCALL libd_getcwd)(char *buf,
                                  size_t bufsize)
/*[[[body:libd_getcwd]]]*/
{
	return libd_frealpath(AT_FDCWD, buf, bufsize);
}
/*[[[end:libd_getcwd]]]*/

/*[[[head:libc_getcwd,hash:CRC-32=0x14908c60]]]*/
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_OUT_OPT(1) char *
NOTHROW_RPC(LIBCCALL libc_getcwd)(char *buf,
                                  size_t bufsize)
/*[[[body:libc_getcwd]]]*/
{
#ifdef __OPTIMIZE_SIZE__
	return libc_frealpath(AT_FDCWD, buf, bufsize);
#else /* __OPTIMIZE_SIZE__ */
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
		libc_seterrno_neg(result);
		return NULL;
	}
done:
	return buffer;
#endif /* !__OPTIMIZE_SIZE__ */
}
/*[[[end:libc_getcwd]]]*/

/*[[[head:libd_unlink,hash:CRC-32=0x10bf0d05]]]*/
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_unlink)(char const *file)
/*[[[body:libd_unlink]]]*/
{
	return libd_unlinkat(AT_FDCWD, file, 0);
}
/*[[[end:libd_unlink]]]*/

/*[[[head:libc_unlink,hash:CRC-32=0xf4c68783]]]*/
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_unlink)(char const *file)
/*[[[body:libc_unlink]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_unlink)
	return libc_unlinkat(AT_FDCWD, result, 0);
#else /* __OPTIMIZE_SIZE__ || !SYS_unlink */
	errno_t result = sys_unlink(file);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_unlink */
}
/*[[[end:libc_unlink]]]*/

/*[[[head:libd_rmdir,hash:CRC-32=0xbe8dd7eb]]]*/
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_rmdir)(char const *path)
/*[[[body:libd_rmdir]]]*/
{
	return libd_unlinkat(AT_FDCWD, path, AT_REMOVEDIR);
}
/*[[[end:libd_rmdir]]]*/

/*[[[head:libc_rmdir,hash:CRC-32=0xbe5758e]]]*/
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_rmdir)(char const *path)
/*[[[body:libc_rmdir]]]*/
{
#ifndef SYS_rmdir
	return libc_unlinkat(AT_FDCWD, path, AT_REMOVEDIR);
#else /* SYS_rmdir */
	errno_t result = sys_rmdir(path);
	return libc_seterrno_syserr(result);
#endif /* !SYS_rmdir */
}
/*[[[end:libc_rmdir]]]*/

/*[[[head:libd_euidaccess,hash:CRC-32=0x5523873]]]*/
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_euidaccess)(char const *file,
                                      __STDC_INT_AS_UINT_T type)
/*[[[body:libd_euidaccess]]]*/
{
	return libd_faccessat(AT_FDCWD, file, type, AT_EACCESS);
}
/*[[[end:libd_euidaccess]]]*/

/*[[[head:libc_euidaccess,hash:CRC-32=0x3c03b1e]]]*/
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_euidaccess)(char const *file,
                                      __STDC_INT_AS_UINT_T type)
/*[[[body:libc_euidaccess]]]*/
{
#ifdef __OPTIMIZE_SIZE__
	return libc_faccessat(AT_FDCWD, file, type, AT_EACCESS);
#else /* __OPTIMIZE_SIZE__ */
	errno_t result;
	result = sys_faccessat2(AT_FDCWD, file,
	                        (syscall_ulong_t)(unsigned int)type,
	                        AT_EACCESS);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ */
}
/*[[[end:libc_euidaccess]]]*/

/*[[[head:libd_faccessat,hash:CRC-32=0x63f6964]]]*/
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_faccessat)(fd_t dfd,
                                     char const *file,
                                     __STDC_INT_AS_UINT_T type,
                                     atflag_t flags)
/*[[[body:libd_faccessat]]]*/
{
	return libc_faccessat(dfd, file, type, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_faccessat]]]*/

/*[[[head:libc_faccessat,hash:CRC-32=0x1d7294b7]]]*/
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_faccessat)(fd_t dfd,
                                     char const *file,
                                     __STDC_INT_AS_UINT_T type,
                                     atflag_t flags)
/*[[[body:libc_faccessat]]]*/
{
	errno_t result;
	result = sys_faccessat2(dfd, file, (syscall_ulong_t)(unsigned int)type, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_faccessat]]]*/

/*[[[head:libd_fchownat,hash:CRC-32=0x49fb000b]]]*/
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_fchownat)(fd_t dfd,
                                    char const *file,
                                    uid_t owner,
                                    gid_t group,
                                    atflag_t flags)
/*[[[body:libd_fchownat]]]*/
{
	return libc_fchownat(dfd, file, owner, group, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_fchownat]]]*/

/*[[[head:libc_fchownat,hash:CRC-32=0x7b0894c4]]]*/
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_fchownat)(fd_t dfd,
                                    char const *file,
                                    uid_t owner,
                                    gid_t group,
                                    atflag_t flags)
/*[[[body:libc_fchownat]]]*/
{
	errno_t result;
	result = _sys_fchownat(dfd, file, owner, group, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchownat]]]*/

/*[[[head:libd_linkat,hash:CRC-32=0xd883884a]]]*/
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBDCALL libd_linkat)(fd_t fromfd,
                                  char const *from,
                                  fd_t tofd,
                                  char const *to,
                                  atflag_t flags)
/*[[[body:libd_linkat]]]*/
{
	return libc_linkat(fromfd, from, tofd, to, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_linkat]]]*/

/*[[[head:libc_linkat,hash:CRC-32=0xd6c22cc]]]*/
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) ATTR_IN(4) int
NOTHROW_RPC(LIBCCALL libc_linkat)(fd_t fromfd,
                                  char const *from,
                                  fd_t tofd,
                                  char const *to,
                                  atflag_t flags)
/*[[[body:libc_linkat]]]*/
{
	errno_t result = sys_linkat(fromfd, from, tofd, to, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_linkat]]]*/

/*[[[head:libd_symlinkat,hash:CRC-32=0x52f7c2ad]]]*/
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBDCALL libd_symlinkat)(char const *link_text,
                                     fd_t tofd,
                                     char const *target_path)
/*[[[body:libd_symlinkat]]]*/
{
	return libd_fsymlinkat(link_text, tofd, target_path, 0);
}
/*[[[end:libd_symlinkat]]]*/

/*[[[head:libc_symlinkat,hash:CRC-32=0x748dfd50]]]*/
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBCCALL libc_symlinkat)(char const *link_text,
                                     fd_t tofd,
                                     char const *target_path)
/*[[[body:libc_symlinkat]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_symlinkat)
	return libc_fsymlinkat(link_text, tofd, target_path, 0);
#else /* __OPTIMIZE_SIZE__ || !SYS_symlinkat */
	errno_t result = sys_symlinkat(link_text, tofd, target_path);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_symlinkat */
}
/*[[[end:libc_symlinkat]]]*/

/*[[[head:libd_readlinkat,hash:CRC-32=0x8d9f93ef]]]*/
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBDCALL libd_readlinkat)(fd_t dfd,
                                      char const *path,
                                      char *buf,
                                      size_t buflen)
/*[[[body:libd_readlinkat]]]*/
{
	return libd_freadlinkat(dfd, path, buf, buflen, 0);
}
/*[[[end:libd_readlinkat]]]*/

/*[[[head:libc_readlinkat,hash:CRC-32=0x5ef2ec18]]]*/
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBCCALL libc_readlinkat)(fd_t dfd,
                                      char const *path,
                                      char *buf,
                                      size_t buflen)
/*[[[body:libc_readlinkat]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_readlinkat)
	return libc_freadlinkat(dfd, path, buf, buflen, 0);
#else /* __OPTIMIZE_SIZE__ || !SYS_readlinkat */
	errno_t result = sys_readlinkat(dfd, path, buf, buflen);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_readlinkat */
}
/*[[[end:libc_readlinkat]]]*/

/*[[[head:libd_fsymlinkat,hash:CRC-32=0xcfd30ed4]]]*/
/* >> fsymlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path'
 * @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBDCALL libd_fsymlinkat)(char const *link_text,
                                      fd_t tofd,
                                      char const *target_path,
                                      atflag_t flags)
/*[[[body:libd_fsymlinkat]]]*/
{
	return libc_fsymlinkat(link_text, tofd, target_path, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_fsymlinkat]]]*/

/*[[[head:libc_fsymlinkat,hash:CRC-32=0x897d6751]]]*/
/* >> fsymlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path'
 * @param flags: Set of `0 | AT_DOSPATH' */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(1) ATTR_IN(3) int
NOTHROW_RPC(LIBCCALL libc_fsymlinkat)(char const *link_text,
                                      fd_t tofd,
                                      char const *target_path,
                                      atflag_t flags)
/*[[[body:libc_fsymlinkat]]]*/
{
	errno_t result = sys_fsymlinkat(link_text, tofd, target_path, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fsymlinkat]]]*/

/*[[[head:libd_freadlinkat,hash:CRC-32=0x54727f81]]]*/
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBDCALL libd_freadlinkat)(fd_t dfd,
                                       char const *path,
                                       char *buf,
                                       size_t buflen,
                                       atflag_t flags)
/*[[[body:libd_freadlinkat]]]*/
{
	return libc_freadlinkat(dfd, path, buf, buflen, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_freadlinkat]]]*/

/*[[[head:libc_freadlinkat,hash:CRC-32=0x91ec94b0]]]*/
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(2) ATTR_OUTS(3, 4) ssize_t
NOTHROW_RPC(LIBCCALL libc_freadlinkat)(fd_t dfd,
                                       char const *path,
                                       char *buf,
                                       size_t buflen,
                                       atflag_t flags)
/*[[[body:libc_freadlinkat]]]*/
{
	ssize_t result = sys_freadlinkat(dfd, path, buf, buflen, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_freadlinkat]]]*/

/*[[[head:libd_unlinkat,hash:CRC-32=0xb3846f97]]]*/
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_unlinkat)(fd_t dfd,
                                    char const *name,
                                    atflag_t flags)
/*[[[body:libd_unlinkat]]]*/
{
	return libc_unlinkat(dfd, name, flags | libd_AT_DOSPATH);
}
/*[[[end:libd_unlinkat]]]*/

/*[[[head:libc_unlinkat,hash:CRC-32=0x4529dd59]]]*/
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_unlinkat)(fd_t dfd,
                                    char const *name,
                                    atflag_t flags)
/*[[[body:libc_unlinkat]]]*/
{
	errno_t result = sys_unlinkat(dfd, name, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_unlinkat]]]*/

/*[[[head:libc_lseek,hash:CRC-32=0x1a9edecf]]]*/
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTERN ATTR_SECTION(".text.crt.io.seek") ATTR_FDARG(1) off_t
NOTHROW_NCX(LIBCCALL libc_lseek)(fd_t fd,
                                 off_t offset,
                                 __STDC_INT_AS_UINT_T whence)
/*[[[body:libc_lseek]]]*/
{
	off_t result;
#ifdef SYS_lseek
	result = sys_lseek(fd, (syscall_slong_t)offset, whence);
#else /* SYS_lseek */
	result = (off_t)sys_lseek64(fd, (int64_t)offset, whence);
#endif /* !SYS_lseek */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_lseek]]]*/

/*[[[head:libc_lseek64,hash:CRC-32=0xf8cdfe54]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lseek64, libc_lseek);
#else /* MAGIC:alias */
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTERN ATTR_SECTION(".text.crt.io.large.seek") ATTR_FDARG(1) off64_t
NOTHROW_NCX(LIBCCALL libc_lseek64)(fd_t fd,
                                   off64_t offset,
                                   __STDC_INT_AS_UINT_T whence)
/*[[[body:libc_lseek64]]]*/
{
#ifdef SYS_lseek64
	off64_t result = sys_lseek64(fd, (int64_t)offset, whence);
	return libc_seterrno_syserr(result);
#else /* SYS_lseek64 */
	uint64_t result;
	errno_t error;
	error = sys__llseek(fd, offset, &result, whence);
	if unlikely(E_ISERR(error))
		result = (uint64_t)(int64_t)libc_seterrno_neg(error);
	return result;
#endif /* !SYS_lseek64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_lseek64]]]*/

/*[[[head:libc_pread,hash:CRC-32=0x6fde6e74]]]*/
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTERN ATTR_SECTION(".text.crt.io.read") ATTR_FDREAD(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_pread)(fd_t fd,
                                 void *buf,
                                 size_t bufsize,
                                 __PIO_OFFSET offset)
/*[[[body:libc_pread]]]*/
{
	ssize_t result;
	result = sys_pread64(fd, buf, bufsize, (uint64_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pread]]]*/

/*[[[head:libc_pwrite,hash:CRC-32=0xb5c2d25e]]]*/
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_FDWRITE(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwrite)(fd_t fd,
                                  void const *buf,
                                  size_t bufsize,
                                  __PIO_OFFSET offset)
/*[[[body:libc_pwrite]]]*/
{
	ssize_t result = sys_pwrite64(fd, buf, bufsize, (uint64_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pwrite]]]*/

/*[[[head:libc_pread64,hash:CRC-32=0x90a75202]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pread64, libc_pread);
#else /* MAGIC:alias */
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTERN ATTR_SECTION(".text.crt.io.large.read") ATTR_FDREAD(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_pread64)(fd_t fd,
                                   void *buf,
                                   size_t bufsize,
                                   __PIO_OFFSET64 offset)
/*[[[body:libc_pread64]]]*/
{
	ssize_t result = sys_pread64(fd, buf, bufsize, (uint64_t)(__pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pread64]]]*/

/*[[[head:libc_pwrite64,hash:CRC-32=0xb9a4425c]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwrite64, libc_pwrite);
#else /* MAGIC:alias */
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTERN ATTR_SECTION(".text.crt.io.large.write") ATTR_FDWRITE(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwrite64)(fd_t fd,
                                    void const *buf,
                                    size_t bufsize,
                                    __PIO_OFFSET64 offset)
/*[[[body:libc_pwrite64]]]*/
{
	ssize_t result = sys_pwrite64(fd, buf, bufsize, (uint64_t)(__pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pwrite64]]]*/

/*[[[head:libc_pipe2,hash:CRC-32=0xa5fdc31b]]]*/
/* >> pipe2(2)
 * Construct a [reader,writer]-pair of pipes
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.access") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_pipe2)(fd_t pipedes[2],
                                 oflag_t flags)
/*[[[body:libc_pipe2]]]*/
{
	errno_t result = sys_pipe2(pipedes, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pipe2]]]*/

/*[[[head:libc_getresuid,hash:CRC-32=0x73a7c489]]]*/
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_getresuid)(uid_t *ruid,
                                     uid_t *euid,
                                     uid_t *suid)
/*[[[body:libc_getresuid]]]*/
{
	errno_t result;
	result = _sys_getresuid(ruid, euid, suid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getresuid]]]*/

/*[[[head:libc_getresgid,hash:CRC-32=0xaaab2582]]]*/
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_getresgid)(gid_t *rgid,
                                     gid_t *egid,
                                     gid_t *sgid)
/*[[[body:libc_getresgid]]]*/
{
	errno_t result;
	result = _sys_getresgid(rgid, egid, sgid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getresgid]]]*/

/*[[[head:libc_setresuid,hash:CRC-32=0x65bb757d]]]*/
/* >> setresuid(2)
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
	result = _sys_setresuid(ruid, euid, suid);
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
	result = _sys_setresgid(rgid, egid, sgid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setresgid]]]*/

/*[[[head:libc_fchown,hash:CRC-32=0x202cfe0c]]]*/
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_FDARG(1) int
NOTHROW_RPC(LIBCCALL libc_fchown)(fd_t fd,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libc_fchown]]]*/
{
	errno_t result;
	result = _sys_fchown(fd, owner, group);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchown]]]*/

/*[[[head:libc_fchdir,hash:CRC-32=0xe6cc7367]]]*/
/* >> fchdir(2)
 * Change the current working directory to `path' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_FDARG(1) int
NOTHROW_RPC(LIBCCALL libc_fchdir)(fd_t fd)
/*[[[body:libc_fchdir]]]*/
{
	errno_t result = sys_fchdir(fd);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fchdir]]]*/

/*[[[head:libc_getpgid,hash:CRC-32=0x73a5d73]]]*/
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getpgid)(pid_t pid)
/*[[[body:libc_getpgid]]]*/
{
	pid_t result = sys_getpgid(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getpgid]]]*/

/*[[[head:libc_getsid,hash:CRC-32=0x643d1819]]]*/
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTERN ATTR_SECTION(".text.crt.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_getsid)(pid_t pid)
/*[[[body:libc_getsid]]]*/
{
	pid_t result = sys_getsid(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_getsid]]]*/

/*[[[head:libd_lchown,hash:CRC-32=0x21dbeb8f]]]*/
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_lchown)(char const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libd_lchown]]]*/
{
	return libd_fchownat(AT_FDCWD, file, owner, group, AT_SYMLINK_NOFOLLOW);
}
/*[[[end:libd_lchown]]]*/

/*[[[head:libc_lchown,hash:CRC-32=0xe957ee3a]]]*/
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_lchown)(char const *file,
                                  uid_t owner,
                                  gid_t group)
/*[[[body:libc_lchown]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_lchown)
	return libc_fchownat(AT_FDCWD, file, owner, group, AT_SYMLINK_NOFOLLOW);
#else /* __OPTIMIZE_SIZE__ || !SYS_lchown */
	errno_t result;
	result = sys_lchown(file, (uint32_t)owner, (uint32_t)group);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_lchown */
}
/*[[[end:libc_lchown]]]*/

/*[[[head:libd_truncate,hash:CRC-32=0x2519c99]]]*/
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBDCALL libd_truncate)(char const *file,
                                    __PIO_OFFSET length)
/*[[[body:libd_truncate]]]*/
{
	int result;
	fd_t fd = libd_open(file, O_RDWR);
	if (fd < 0)
		return -1;
	result = libc_ftruncate(fd, length);
	(void)sys_close(fd);
	return result;
}
/*[[[end:libd_truncate]]]*/

/*[[[head:libc_truncate,hash:CRC-32=0x7d69cde1]]]*/
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_truncate)(char const *file,
                                    __PIO_OFFSET length)
/*[[[body:libc_truncate]]]*/
{
#ifndef SYS_truncate
	int result;
	fd_t fd = libc_open(file, O_RDWR);
	if (fd < 0)
		return -1;
	result = libc_ftruncate(fd, length);
	(void)sys_close(fd);
	return result;
#else /* !SYS_truncate */
	errno_t result = sys_truncate(file, (syscall_ulong_t)length);
	return libc_seterrno_syserr(result);
#endif /* SYS_truncate */
}
/*[[[end:libc_truncate]]]*/

/*[[[head:libd_truncate64,hash:CRC-32=0x617ef286]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libd_truncate64, libd_truncate);
#else /* MAGIC:alias */
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBDCALL libd_truncate64)(char const *file,
                                      __PIO_OFFSET64 length)
/*[[[body:libd_truncate64]]]*/
{
	int result;
	fd_t fd = libd_open(file, O_RDWR);
	if (fd < 0)
		return -1;
	result = libc_ftruncate64(fd, length);
	(void)sys_close(fd);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libd_truncate64]]]*/

/*[[[head:libc_truncate64,hash:CRC-32=0xa5b269de]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_truncate64, libc_truncate);
#else /* MAGIC:alias */
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_truncate64)(char const *file,
                                      __PIO_OFFSET64 length)
/*[[[body:libc_truncate64]]]*/
{
#ifndef SYS_truncate64
	int result;
	fd_t fd = libc_open(file, O_RDWR);
	if (fd < 0)
		return -1;
	result = libc_ftruncate64(fd, length);
	(void)sys_close(fd);
	return result;
#else /* !SYS_truncate64 */
	errno_t result = sys_truncate64(file, (uint64_t)(__pos64_t)length);
	return libc_seterrno_syserr(result);
#endif /* SYS_truncate64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_truncate64]]]*/

/*[[[head:libc_fexecve,hash:CRC-32=0x19d2b80f]]]*/
/* >> fexecve(2)
 * Replace the calling process with the application image referred
 * to by `execfd'  and execute it's  `main()' method, passing  the
 * given `argv', and setting `environ' to `envp'. */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_FDREAD(1) ATTR_IN(2) ATTR_IN(3) int
NOTHROW_RPC(LIBCCALL libc_fexecve)(fd_t execfd,
                                   __TARGV,
                                   __TENVP)
/*[[[body:libc_fexecve]]]*/
{
#if 0 && (defined(__OPTIMIZE_SIZE__) || !defined(SYS_fexecve)) /* TODO: Add as a kos-extension to <unistd.h> */
	return libc_execveat(execfd, "", ___argv, ___envp, AT_EMPTY_PATH);
#else /* __OPTIMIZE_SIZE__ || !SYS_fexecve */
	errno_t error;
	error = sys_fexecve(execfd,
	                    (char const *const *)___argv,
	                    (char const *const *)___envp);
	return libc_seterrno_neg(error);
#endif /* __OPTIMIZE_SIZE__ && SYS_fexecve */
}
/*[[[end:libc_fexecve]]]*/

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
	error = _sys_setreuid(ruid, euid);
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
	error = _sys_setregid(rgid, egid);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setregid]]]*/

/*[[[head:libd_symlink,hash:CRC-32=0xd8ddeed]]]*/
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_symlink)(char const *link_text,
                                   char const *target_path)
/*[[[body:libd_symlink]]]*/
{
	return libd_symlinkat(link_text, AT_FDCWD, target_path);
}
/*[[[end:libd_symlink]]]*/

/*[[[head:libc_symlink,hash:CRC-32=0xc7a789f2]]]*/
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_symlink)(char const *link_text,
                                   char const *target_path)
/*[[[body:libc_symlink]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_symlink)
	return libc_symlinkat(link_text, AT_FDCWD, target_path);
#else /* __OPTIMIZE_SIZE__ || !SYS_symlink */
	errno_t result = sys_symlink(link_text, target_path);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_symlink */
}
/*[[[end:libc_symlink]]]*/

/*[[[head:libd_readlink,hash:CRC-32=0x70dc90b3]]]*/
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBDCALL libd_readlink)(char const *path,
                                    char *buf,
                                    size_t buflen)
/*[[[body:libd_readlink]]]*/
{
	return libd_readlinkat(AT_FDCWD, path, buf, buflen);
}
/*[[[end:libd_readlink]]]*/

/*[[[head:libc_readlink,hash:CRC-32=0xdb5fe03d]]]*/
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_readlink)(char const *path,
                                    char *buf,
                                    size_t buflen)
/*[[[body:libc_readlink]]]*/
{
#if defined(__OPTIMIZE_SIZE__) || !defined(SYS_readlink)
	return libc_readlinkat(AT_FDCWD, path, buf, buflen);
#else /* __OPTIMIZE_SIZE__ || !SYS_readlink */
	ssize_t result = sys_readlink(path, buf, buflen);
	return libc_seterrno_syserr(result);
#endif /* !__OPTIMIZE_SIZE__ && SYS_readlink */
}
/*[[[end:libc_readlink]]]*/

/*[[[head:libc_sethostname,hash:CRC-32=0xcd816e29]]]*/
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_sethostname)(char const *name,
                                       size_t len)
/*[[[body:libc_sethostname]]]*/
{
	errno_t result = sys_sethostname(name, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sethostname]]]*/

/*[[[head:libc_setdomainname,hash:CRC-32=0x3a54e2c2]]]*/
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_setdomainname)(char const *name,
                                         size_t len)
/*[[[body:libc_setdomainname]]]*/
{
	errno_t result = sys_setdomainname(name, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setdomainname]]]*/

/*[[[head:libc_vhangup,hash:CRC-32=0x30a39db6]]]*/
/* >> vhangup(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_vhangup)(void)
/*[[[body:libc_vhangup]]]*/
{
	errno_t result = sys_vhangup();
	return libc_seterrno_syserr(result);
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
#if defined(SYS_profil) && 0
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



PRIVATE ATTR_SECTION(".bss.crt.database.shell")
FILE *usershells_file = NULL;
PRIVATE ATTR_SECTION(".rodata.crt.database.shell")
char const usershells_filename[] = _PATH_SHELLS;
PRIVATE ATTR_SECTION(".rodata.crt.database.shell")
char const usershells_defaultdata[] = "/bin/sh\n"
                                      "/bin/csh";


/*[[[head:libc_setusershell,hash:CRC-32=0xdab349fb]]]*/
/* >> setusershell(3) */
INTERN ATTR_SECTION(".text.crt.database.shell") void
NOTHROW_RPC(LIBCCALL libc_setusershell)(void)
/*[[[body:libc_setusershell]]]*/
{
	if (usershells_file) {
		rewind(usershells_file);
	} else {
		usershells_file = fopen(usershells_filename, "r");
		if (!usershells_file) {
			usershells_file = fmemopen((void *)usershells_defaultdata,
			                           sizeof(usershells_defaultdata),
			                           "r");
		}
	}
}
/*[[[end:libc_setusershell]]]*/

/*[[[head:libc_endusershell,hash:CRC-32=0xd5d53e38]]]*/
/* >> endusershell(3) */
INTERN ATTR_SECTION(".text.crt.database.shell") void
NOTHROW_NCX(LIBCCALL libc_endusershell)(void)
/*[[[body:libc_endusershell]]]*/
{
	if (usershells_file) {
		fclose(usershells_file);
		usershells_file = NULL;
	}
}
/*[[[end:libc_endusershell]]]*/

/*[[[head:libc_getusershell,hash:CRC-32=0x620a6b9c]]]*/
/* >> getusershell(3) */
INTERN ATTR_SECTION(".text.crt.database.shell") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_getusershell)(void)
/*[[[body:libc_getusershell]]]*/
{
	char *result;
	if (!usershells_file)
		libc_setusershell();
	/* Read the next non-empty line (hint: the buffer
	 * here  is  automatically free'd  by fclose(3)!) */
	while ((result = fgetln(usershells_file, NULL)) != NULL) {
		if (*result != '\0' && *result != '\n')
			break;
	}
	return result;
}
/*[[[end:libc_getusershell]]]*/

/*[[[head:libc_revoke,hash:CRC-32=0xde035669]]]*/
/* >> revoke(3) */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_revoke)(char const *file)
/*[[[body:libc_revoke]]]*/
/*AUTO*/{
	(void)file;
	CRT_UNIMPLEMENTEDF("revoke(file: %q)", file); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_revoke]]]*/

/*[[[head:libd_chroot,hash:CRC-32=0xcf9dc298]]]*/
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.utility") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_chroot)(char const *__restrict path)
/*[[[body:libd_chroot]]]*/
{
	int result;
	fd_t fd = libd_open(path, O_RDONLY | O_DIRECTORY);
	if (fd < 0)
		return -1;
	result = libd_fchroot(fd);
	(void)sys_close(fd);
#if 0 /* Already done for us by `libd_fchroot()' (which calls `libd_dup2()') */
	if (result == 0)
		libd_dos_fsroot_changed();
#endif
	return result;
}
/*[[[end:libd_chroot]]]*/

/*[[[head:libc_chroot,hash:CRC-32=0xad587a9b]]]*/
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTERN ATTR_SECTION(".text.crt.fs.utility") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_chroot)(char const *__restrict path)
/*[[[body:libc_chroot]]]*/
{
	errno_t result = sys_chroot(path);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_chroot]]]*/


/* `vfork' needs to be implemented in assembly! */
/*[[[skip:libc_vfork]]]*/

/* `syscall' needs to be implemented in assembly! */
/*[[[skip:libc_syscall]]]*/
/*[[[skip:libc_syscall64]]]*/

/*[[[head:libc_ftruncate,hash:CRC-32=0xa468f529]]]*/
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_FDWRITE(1) int
NOTHROW_NCX(LIBCCALL libc_ftruncate)(fd_t fd,
                                     __PIO_OFFSET length)
/*[[[body:libc_ftruncate]]]*/
{
	errno_t result = sys_ftruncate(fd, (syscall_ulong_t)length);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_ftruncate]]]*/

/*[[[head:libc_ftruncate64,hash:CRC-32=0x143f21e0]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_ftruncate64, libc_ftruncate);
#else /* MAGIC:alias */
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTERN ATTR_SECTION(".text.crt.io.large.write") ATTR_FDWRITE(1) int
NOTHROW_NCX(LIBCCALL libc_ftruncate64)(fd_t fd,
                                       __PIO_OFFSET64 length)
/*[[[body:libc_ftruncate64]]]*/
{
	errno_t result = sys_ftruncate64(fd, (uint64_t)(__pos64_t)length);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftruncate64]]]*/


/* Lock for `brk_curr' */
PRIVATE ATTR_SECTION(".bss.crt.heap.utility")
DEFINE_SHARED_LOCK(brk_lock);

/* [0..1][lock(brk_lock)] */
PRIVATE ATTR_SECTION(".bss.crt.heap.utility")
byte_t *brk_curr = NULL;

/* Helper macros for `struct kbddev::brk_lock' */
#define _brk_reap()      (void)0
#define brk_reap()       (void)0
#define brk_mustreap()   0
#define brk_tryacquire() shared_lock_tryacquire(&brk_lock)
#define brk_acquire()    shared_lock_acquire(&brk_lock)
#define _brk_release()   shared_lock_release(&brk_lock)
#define brk_release()    (shared_lock_release(&brk_lock), brk_reap())
#define brk_acquired()   shared_lock_acquired(&brk_lock)
#define brk_available()  shared_lock_available(&brk_lock)


/* For compatibility with old linux programs: the current program break address. */
DEFINE_PUBLIC_IDATA(___brk_addr, libc_brk_addr_cb, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(__curbrk, libc_brk_addr_cb, __SIZEOF_POINTER__);
INTERN ATTR_SECTION(".text.crt.compat.linux.heap") byte_t **LIBCCALL
libc_brk_addr_cb(void) {
	if (brk_curr == NULL)
		brk_curr = (byte_t *)dlsym(RTLD_DEFAULT, "_end");
	return &brk_curr;
}

PRIVATE ATTR_SECTION(".text.crt.heap.utility")
int LIBCCALL do_brk(void *addr) {
	size_t pagesize = getpagesize();
	byte_t *real_oldbrk, *real_newbrk;
	if ((real_oldbrk = brk_curr) == NULL) {
		/* Lookup the end address of the main executable
		 * NOTE: We do this lazily to prevent the necessity of a `R_386_GLOB_DAT' relocation */
		void *temp = dlsym(RTLD_DEFAULT, "_end");
		if unlikely(!temp && dlerror())
			goto err_perm;
		real_oldbrk = (byte_t *)CEIL_ALIGN((uintptr_t)temp, pagesize);
	} else {
		real_oldbrk = (byte_t *)CEIL_ALIGN((uintptr_t)real_oldbrk, pagesize);
	}
	real_newbrk = (byte_t *)CEIL_ALIGN((uintptr_t)addr, pagesize);
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


/*[[[head:libc_brk,hash:CRC-32=0x7ed249a9]]]*/
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTERN ATTR_SECTION(".text.crt.heap.utility") int
NOTHROW_NCX(LIBCCALL libc_brk)(void *addr)
/*[[[body:libc_brk]]]*/
{
	int result;
	brk_acquire();
	result = do_brk(addr);
	brk_release();
	return result;
}
/*[[[end:libc_brk]]]*/

/*[[[head:libc_sbrk,hash:CRC-32=0x6575aae]]]*/
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTERN ATTR_SECTION(".text.crt.heap.utility") void *
NOTHROW_NCX(LIBCCALL libc_sbrk)(intptr_t delta)
/*[[[body:libc_sbrk]]]*/
{
	byte_t *result;
	brk_acquire();
	if ((result = brk_curr) == NULL) {
		size_t pagesize;
		/* Lookup the end address of the main executable
		 * NOTE: We do this lazily to prevent the necessity of a relocation */
		void *temp = dlsym(RTLD_DEFAULT, "_end");
		if unlikely(!temp && dlerror())
			goto err_perm;
		pagesize = getpagesize();
		result   = (byte_t *)CEIL_ALIGN((uintptr_t)temp, pagesize);
	}
	if (do_brk(result + delta) != 0)
		result = (byte_t *)-1;
	brk_release();
	return result;
err_perm:
	brk_release();
	libc_seterrno(EPERM);
	return NULL;
}
/*[[[end:libc_sbrk]]]*/


#define PATHCONF_VARYING_LIMIT ((longptr_t)INTPTR_MIN)
PRIVATE ATTR_SECTION(".rodata.crt.fs.property") longptr_t const pc_constants[] = {
	[_PC_LINK_MAX]           = PATHCONF_VARYING_LIMIT,
	[_PC_MAX_CANON]          = PATHCONF_VARYING_LIMIT,
	[_PC_MAX_INPUT]          = PATHCONF_VARYING_LIMIT,
	[_PC_NAME_MAX]           = PATHCONF_VARYING_LIMIT,
	[_PC_PATH_MAX]           = -1 /*PATH_MAX*/, /* Unlimitedw */
	[_PC_PIPE_BUF]           = PIPE_BUF,
	[_PC_CHOWN_RESTRICTED]   = 1, /* All filesystems supported by KOS implement posix ownership rules. */
	[_PC_NO_TRUNC]           = 1, /* No, filenames are never silently truncated. */
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

PRIVATE ATTR_SECTION(".rodata.crt.fs.property")
uint32_t const pathconf_ioctl_codes[] = {
	[_PC_LINK_MAX]           = FILE_IOC_GETFSLINKMAX,
	[_PC_MAX_CANON]          = 0,
	[_PC_MAX_INPUT]          = 0,
	[_PC_NAME_MAX]           = FILE_IOC_GETFSNAMEMAX,
	[_PC_PATH_MAX]           = 0,
	[_PC_PIPE_BUF]           = 0,
	[_PC_CHOWN_RESTRICTED]   = 0,
	[_PC_NO_TRUNC]           = 0,
	[_PC_VDISABLE]           = 0,
	[_PC_SYNC_IO]            = 0,
	[_PC_ASYNC_IO]           = 0,
	[_PC_PRIO_IO]            = 0,
	[_PC_SOCK_MAXBUF]        = 0,
	[_PC_FILESIZEBITS]       = FILE_IOC_GETFSSIZBITS,
	[_PC_REC_INCR_XFER_SIZE] = FILE_IOC_GETFSXFERINC,
	[_PC_REC_MAX_XFER_SIZE]  = FILE_IOC_GETFSXFERMAX,
	[_PC_REC_MIN_XFER_SIZE]  = FILE_IOC_GETFSXFERMIN,
	[_PC_REC_XFER_ALIGN]     = FILE_IOC_GETFSXFERALN,
	[_PC_ALLOC_SIZE_MIN]     = FILE_IOC_GETFSXFERALN,
	[_PC_SYMLINK_MAX]        = FILE_IOC_GETFSSYMMAX,
	[_PC_2_SYMLINKS]         = FILE_IOC_GETFSSYMMAX,
};

/*[[[head:libc_fpathconf,hash:CRC-32=0xbf28e2dc]]]*/
/* >> fpathconf(3)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.fs.property") WUNUSED ATTR_FDARG(1) longptr_t
NOTHROW_RPC(LIBCCALL libc_fpathconf)(fd_t fd,
                                     __STDC_INT_AS_UINT_T name)
/*[[[body:libc_fpathconf]]]*/
{
	longptr_t result;
	if unlikely(name >= lengthof(pc_constants)) {
		result = libc_seterrno(EINVAL);
	} else if ((result = pc_constants[name]) == PATHCONF_VARYING_LIMIT) {
		/* Determine the value based on `fd' */
		switch (name) {

		case _PC_MAX_INPUT: {
			size_t value;
			result = ioctl(fd, TTY_IOC_IBUF_GETLIMIT, &value);
			if (result >= 0)
				result = (longptr_t)value;
		}	break;

		case _PC_MAX_CANON: {
			size_t value;
			result = ioctl(fd, TTY_IOC_CANON_GETLIMIT, &value);
			if (result >= 0)
				result = (longptr_t)value;
		}	break;

			/* Superblock attributes */
		case _PC_LINK_MAX:
		case _PC_NAME_MAX:
		case _PC_FILESIZEBITS:
		case _PC_REC_INCR_XFER_SIZE:
		case _PC_REC_MAX_XFER_SIZE:
		case _PC_REC_MIN_XFER_SIZE:
		case _PC_REC_XFER_ALIGN:
		case _PC_ALLOC_SIZE_MIN:
		case _PC_SYMLINK_MAX:
		case _PC_2_SYMLINKS: {
			alignas(alignof(uint64_t))
			byte_t buf[sizeof(uint64_t)];
			uint32_t cmd;
			cmd    = pathconf_ioctl_codes[name];
			result = ioctl(fd, cmd, buf);
			if (result >= 0) {
				if (name == _PC_2_SYMLINKS) {
					result = *(uint64_t const *)buf != 0;
				} else if (_IOC_SIZE(cmd) == 1) {
					result = *(uint8_t const *)buf;
				} else if (_IOC_SIZE(cmd) == 2) {
					result = *(uint16_t const *)buf;
				} else if (_IOC_SIZE(cmd) == 4) {
					result = *(uint32_t const *)buf;
				} else {
					assert(_IOC_SIZE(cmd) == 8);
					result = (longptr_t)*(uint64_t const *)buf;
				}
			}
		}	break;

		default:
			break;
		}
	}
	return result;
}
/*[[[end:libc_fpathconf]]]*/


PRIVATE ATTR_SECTION(".text.crt.fs.property") ATTR_IN(1) longptr_t
NOTHROW_RPC(LIBDCALL libc_do_pathconf)(char const *path,
                                       __STDC_INT_AS_UINT_T name,
                                       oflag_t path_oflags) {
	longptr_t result;
	/* Try not to open `path' if `name' is invalid, or has a constant value */
	if unlikely(name >= lengthof(pc_constants)) {
		result = libc_seterrno(EINVAL);
	} else if ((result = pc_constants[name]) == PATHCONF_VARYING_LIMIT) {
		fd_t fd;
		fd = open(path, path_oflags);
		if unlikely(fd < 0)
			return -1;
		result = libc_fpathconf(fd, name);
		(void)sys_close(fd);
	}
	return result;
}

INTERN ATTR_SECTION(".text.crt.except.fs.property") WUNUSED longptr_t LIBCCALL
libc_do_FPathConf(fd_t fd, __STDC_INT_AS_UINT_T name) THROWS(...) {
	longptr_t result;
	if unlikely(name >= lengthof(pc_constants)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_PATHCONF_NAME,
		      name);
	} else if ((result = pc_constants[name]) == PATHCONF_VARYING_LIMIT) {
		/* Determine the value based on `fd' */
		switch (name) {

		case _PC_MAX_INPUT: {
			size_t value;
			Ioctl(fd, TTY_IOC_IBUF_GETLIMIT, &value);
			result = (longptr_t)value;
		}	break;

		case _PC_MAX_CANON: {
			size_t value;
			Ioctl(fd, TTY_IOC_CANON_GETLIMIT, &value);
			result = (longptr_t)value;
		}	break;

			/* Superblock attributes */
		case _PC_LINK_MAX:
		case _PC_NAME_MAX:
		case _PC_FILESIZEBITS:
		case _PC_REC_INCR_XFER_SIZE:
		case _PC_REC_MAX_XFER_SIZE:
		case _PC_REC_MIN_XFER_SIZE:
		case _PC_REC_XFER_ALIGN:
		case _PC_ALLOC_SIZE_MIN:
		case _PC_SYMLINK_MAX:
		case _PC_2_SYMLINKS: {
			alignas(alignof(uint64_t))
			byte_t buf[sizeof(uint64_t)];
			uint32_t cmd;
			cmd    = pathconf_ioctl_codes[name];
			Ioctl(fd, cmd, buf);
			if (name == _PC_2_SYMLINKS) {
				result = *(uint64_t const *)buf != 0;
			} else if (_IOC_SIZE(cmd) == 1) {
				result = *(uint8_t const *)buf;
			} else if (_IOC_SIZE(cmd) == 2) {
				result = *(uint16_t const *)buf;
			} else if (_IOC_SIZE(cmd) == 4) {
				result = *(uint32_t const *)buf;
			} else {
				assert(_IOC_SIZE(cmd) == 8);
				result = (longptr_t)*(uint64_t const *)buf;
			}
		}	break;

		default:
			break;
		}
	}
	return result;
}

INTERN ATTR_SECTION(".text.crt.except.fs.property") ATTR_IN(1) longptr_t LIBDCALL
libc_do_PathConf(char const *path, __STDC_INT_AS_UINT_T name, oflag_t path_oflags) THROWS(...) {
	longptr_t result;
	/* Try not to open `path' if `name' is invalid, or has a constant value */
	if unlikely(name >= lengthof(pc_constants)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_PATHCONF_NAME,
		      name);
	} else if ((result = pc_constants[name]) == PATHCONF_VARYING_LIMIT) {
		fd_t fd;
		fd = Open(path, path_oflags);
		if unlikely(fd < 0)
			return -1;
		result = libc_do_FPathConf(fd, name);
		(void)sys_close(fd);
	}
	return result;
}

/*[[[head:libd_pathconf,hash:CRC-32=0x4fbe995d]]]*/
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(1) longptr_t
NOTHROW_RPC(LIBDCALL libd_pathconf)(char const *path,
                                    __STDC_INT_AS_UINT_T name)
/*[[[body:libd_pathconf]]]*/
{
	return libc_do_pathconf(path, name, O_RDONLY | libd_O_DOSPATH);
}
/*[[[end:libd_pathconf]]]*/

/*[[[head:libc_pathconf,hash:CRC-32=0x7e1d615e]]]*/
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(1) longptr_t
NOTHROW_RPC(LIBCCALL libc_pathconf)(char const *path,
                                    __STDC_INT_AS_UINT_T name)
/*[[[body:libc_pathconf]]]*/
{
	return libc_do_pathconf(path, name, O_RDONLY);
}
/*[[[end:libc_pathconf]]]*/

/*[[[head:libd_lpathconf,hash:CRC-32=0x931b871f]]]*/
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.property") ATTR_IN(1) longptr_t
NOTHROW_RPC(LIBDCALL libd_lpathconf)(char const *path,
                                     __STDC_INT_AS_UINT_T name)
/*[[[body:libd_lpathconf]]]*/
{
	return libc_do_pathconf(path, name, O_RDONLY | O_PATH | O_NOFOLLOW | libd_O_DOSPATH);
}
/*[[[end:libd_lpathconf]]]*/

/*[[[head:libc_lpathconf,hash:CRC-32=0x3468aa6]]]*/
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
INTERN ATTR_SECTION(".text.crt.fs.property") ATTR_IN(1) longptr_t
NOTHROW_RPC(LIBCCALL libc_lpathconf)(char const *path,
                                     __STDC_INT_AS_UINT_T name)
/*[[[body:libc_lpathconf]]]*/
{
	return libc_do_pathconf(path, name, O_RDONLY | O_PATH | O_NOFOLLOW);
}
/*[[[end:libc_lpathconf]]]*/




/* From "../libc/compat.c": */
INTDEF char const libc_gnu_libc_version_full[];
INTDEF char const libc_gnu_nptl_version_full[];


/*[[[head:libc_confstr,hash:CRC-32=0xa93baffc]]]*/
/* >> confstr(3)
 * Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_OUTS(2, 3) size_t
NOTHROW_NCX(LIBCCALL libc_confstr)(__STDC_INT_AS_UINT_T name,
                                   char *buf,
                                   size_t buflen)
/*[[[body:libc_confstr]]]*/
{
#define DEFINE_STRING(name, text) \
	PRIVATE ATTR_SECTION(".rodata.crt.system.configuration") char const name[] = text
	size_t result;
	DEFINE_STRING(empty_string, "");
	char const *result_string = empty_string;
	/* TODO: Use a packed string table + offset list to implement this function
	 *       Additionally, place a  dedicated symbol at  `_CS_GNU_LIBC_VERSION'
	 *       that can be used to implement `gnu_get_libc_version(3)'. */
	switch (name) {

	case _CS_PATH: {
		DEFINE_STRING(cs_path, _PATH_DEFPATH);
		result_string = cs_path;
	}	break;

	case _CS_GNU_LIBC_VERSION:
		result_string = libc_gnu_libc_version_full;
		break;

	case _CS_GNU_LIBPTHREAD_VERSION:
		result_string = libc_gnu_nptl_version_full;
		break;

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
				ppBeginIf(f"{v} <= INT32_MAX");
			} else if (v in SYSCONF_VALUES_LO_INT32) {
				need_undefined = true;
				ppBeginIf(f"{v} > INT32_MIN");
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
static_assert(lengthof(sysconf_table) <= _SC_COUNT);



/*[[[head:libc_sysconf,hash:CRC-32=0x66d53c48]]]*/
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.system.configuration") WUNUSED longptr_t
NOTHROW_RPC(LIBCCALL libc_sysconf)(__STDC_INT_AS_UINT_T name)
/*[[[body:libc_sysconf]]]*/
{
	longptr_t result;
	if (name < lengthof(sysconf_table)) {
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
		result = SYMLOOP_MAX; /* TODO: Kernel:`THIS_FS->fs_lnkmax' */
		break;

	default:
		result = libc_seterrno(EINVAL);
		break;
	}
	return result;
}
/*[[[end:libc_sysconf]]]*/

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

/*[[[head:libc_sync,hash:CRC-32=0x89d09d29]]]*/
/* >> sync(2)
 * Synchronize all disk  operations of  all mounted file  systems and  flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
INTERN ATTR_SECTION(".text.crt.fs.modify") void
NOTHROW_RPC(LIBCCALL libc_sync)(void)
/*[[[body:libc_sync]]]*/
{
	sys_sync();
}
/*[[[end:libc_sync]]]*/

/*[[[head:libc_syncfs,hash:CRC-32=0xa519daf2]]]*/
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_FDWRITE(1) int
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
#ifdef SYS_nice
	error = sys_nice(-inc);
	if unlikely(E_ISERR(error))
		goto err;
#else /* SYS_nice */
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
#endif /* !SYS_nice */
	return 20 - error;
err:
	return libc_seterrno_neg(error);
}
/*[[[end:libc_nice]]]*/

/*[[[head:libc_fsync,hash:CRC-32=0x62f85054]]]*/
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
INTERN ATTR_SECTION(".text.crt.io.sync") ATTR_FDWRITE(1) int
NOTHROW_RPC(LIBCCALL libc_fsync)(fd_t fd)
/*[[[body:libc_fsync]]]*/
{
	errno_t error = sys_fsync(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_fsync]]]*/

/*[[[head:libc_fdatasync,hash:CRC-32=0x7b31ad5a]]]*/
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
INTERN ATTR_SECTION(".text.crt.io.sync") ATTR_FDWRITE(1) int
NOTHROW_RPC(LIBCCALL libc_fdatasync)(fd_t fd)
/*[[[body:libc_fdatasync]]]*/
{
	errno_t error;
	error = sys_fdatasync(fd);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_fdatasync]]]*/

/*[[[head:libc_setmode,hash:CRC-32=0xdfbc8204]]]*/
/* >> setmode(3), getmode(3) */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_IN(1) void *
NOTHROW_NCX(LIBCCALL libc_setmode)(char const *mode_str)
/*[[[body:libc_setmode]]]*/
/*AUTO*/{
	(void)mode_str;
	CRT_UNIMPLEMENTEDF("setmode(mode_str: %q)", mode_str); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_setmode]]]*/

/*[[[head:libc_getmode,hash:CRC-32=0xc14dd2df]]]*/
/* >> setmode(3), getmode(3) */
INTERN ATTR_SECTION(".text.crt.bsd") WUNUSED ATTR_IN(1) mode_t
NOTHROW_NCX(LIBCCALL libc_getmode)(void const *bbox,
                                   mode_t mode)
/*[[[body:libc_getmode]]]*/
/*AUTO*/{
	(void)bbox;
	(void)mode;
	CRT_UNIMPLEMENTEDF("getmode(bbox: %p, mode: %" PRIxN(__SIZEOF_MODE_T__) ")", bbox, mode); /* TODO */
	return (mode_t)libc_seterrno(ENOSYS);
}
/*[[[end:libc_getmode]]]*/



/*[[[start:exports,hash:CRC-32=0xe606fc3e]]]*/
DEFINE_PUBLIC_ALIAS_P(DOS$_execve,libd_execve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char const *__restrict path, __TARGV, __TENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$__execve,libd_execve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char const *__restrict path, __TARGV, __TENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_execve,libd_execve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char const *__restrict path, __TARGV, __TENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$execve,libd_execve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char const *__restrict path, __TARGV, __TENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(__execve,libc_execve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBCCALL,(char const *__restrict path, __TARGV, __TENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(__libc_execve,libc_execve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBCCALL,(char const *__restrict path, __TARGV, __TENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(execve,libc_execve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBCCALL,(char const *__restrict path, __TARGV, __TENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(_getpid,libc_getpid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__getpid,libc_getpid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_getpid,libc_getpid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getpid,libc_getpid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__threadid,libc_gettid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P("?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ",libc_gettid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(pthread_getthreadid_np,libc_gettid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(gettid,libc_gettid,ATTR_CONST WUNUSED,pid_t,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__pipe,libc_pipe,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fd_t pipedes[2]),(pipedes));
DEFINE_PUBLIC_ALIAS_P(__libc_pipe,libc_pipe,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fd_t pipedes[2]),(pipedes));
DEFINE_PUBLIC_ALIAS_P(pipe,libc_pipe,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fd_t pipedes[2]),(pipedes));
DEFINE_PUBLIC_ALIAS_P(sleep,libc_sleep,,unsigned int,NOTHROW_RPC,LIBCCALL,(unsigned int seconds),(seconds));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_commit,libc_fsync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__fsync,libc_fsync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__libc_fsync,libc_fsync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(fsync,libc_fsync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__getppid,libc_getppid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_getppid,libc_getppid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getppid,libc_getppid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__getpgrp,libc_getpgrp,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_getpgrp,libc_getpgrp,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getpgrp,libc_getpgrp,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__setpgid,libc_setpgid,,int,NOTHROW_NCX,LIBCCALL,(pid_t pid, pid_t pgid),(pid,pgid));
DEFINE_PUBLIC_ALIAS_P(__libc_setpgid,libc_setpgid,,int,NOTHROW_NCX,LIBCCALL,(pid_t pid, pid_t pgid),(pid,pgid));
DEFINE_PUBLIC_ALIAS_P(setpgid,libc_setpgid,,int,NOTHROW_NCX,LIBCCALL,(pid_t pid, pid_t pgid),(pid,pgid));
DEFINE_PUBLIC_ALIAS_P(__setsid,libc_setsid,,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_setsid,libc_setsid,,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(setsid,libc_setsid,,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__getuid,libc_getuid,WUNUSED,uid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_getuid,libc_getuid,WUNUSED,uid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getuid,libc_getuid,WUNUSED,uid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__getgid,libc_getgid,WUNUSED,gid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_getgid,libc_getgid,WUNUSED,gid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getgid,libc_getgid,WUNUSED,gid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__geteuid,libc_geteuid,WUNUSED,uid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_geteuid,libc_geteuid,WUNUSED,uid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(geteuid,libc_geteuid,WUNUSED,uid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__getegid,libc_getegid,WUNUSED,gid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_getegid,libc_getegid,WUNUSED,gid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getegid,libc_getegid,WUNUSED,gid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__getgroups,libc_getgroups,ATTR_OUTS(2, 1),int,NOTHROW_NCX,LIBCCALL,(int size, gid_t list[]),(size,list));
DEFINE_PUBLIC_ALIAS_P(__libc_getgroups,libc_getgroups,ATTR_OUTS(2, 1),int,NOTHROW_NCX,LIBCCALL,(int size, gid_t list[]),(size,list));
DEFINE_PUBLIC_ALIAS_P(getgroups,libc_getgroups,ATTR_OUTS(2, 1),int,NOTHROW_NCX,LIBCCALL,(int size, gid_t list[]),(size,list));
DEFINE_PUBLIC_ALIAS_P(__setuid,libc_setuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(__libc_setuid,libc_setuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(setuid,libc_setuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(__setgid,libc_setgid,,int,NOTHROW_NCX,LIBCCALL,(gid_t gid),(gid));
DEFINE_PUBLIC_ALIAS_P(__libc_setgid,libc_setgid,,int,NOTHROW_NCX,LIBCCALL,(gid_t gid),(gid));
DEFINE_PUBLIC_ALIAS_P(setgid,libc_setgid,,int,NOTHROW_NCX,LIBCCALL,(gid_t gid),(gid));
DEFINE_PUBLIC_ALIAS_P(__fork,libc_fork,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_fork,libc_fork,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(fork,libc_fork,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__alarm,libc_alarm,,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int seconds),(seconds));
DEFINE_PUBLIC_ALIAS_P(__libc_alarm,libc_alarm,,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int seconds),(seconds));
DEFINE_PUBLIC_ALIAS_P(alarm,libc_alarm,,unsigned int,NOTHROW_NCX,LIBCCALL,(unsigned int seconds),(seconds));
DEFINE_PUBLIC_ALIAS_P(__pause,libc_pause,,int,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_pause,libc_pause,,int,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(pause,libc_pause,,int,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__fpathconf,libc_fpathconf,WUNUSED ATTR_FDARG(1),longptr_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T name),(fd,name));
DEFINE_PUBLIC_ALIAS_P(fpathconf,libc_fpathconf,WUNUSED ATTR_FDARG(1),longptr_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T name),(fd,name));
DEFINE_PUBLIC_ALIAS_P(DOS$__chown,libd_chown,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_chown,libd_chown,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(DOS$chown,libd_chown,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(__chown,libc_chown,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(__libc_chown,libc_chown,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(chown,libc_chown,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(DOS$__pathconf,libd_pathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBDCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(DOS$pathconf,libd_pathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBDCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(__pathconf,libc_pathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBCCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(pathconf,libc_pathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBCCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(DOS$__link,libd_link,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char const *from, char const *to),(from,to));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_link,libd_link,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char const *from, char const *to),(from,to));
DEFINE_PUBLIC_ALIAS_P(DOS$link,libd_link,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char const *from, char const *to),(from,to));
DEFINE_PUBLIC_ALIAS_P(__link,libc_link,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *from, char const *to),(from,to));
DEFINE_PUBLIC_ALIAS_P(__libc_link,libc_link,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *from, char const *to),(from,to));
DEFINE_PUBLIC_ALIAS_P(link,libc_link,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *from, char const *to),(from,to));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_read,libc_read,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize),(fd,buf,bufsize));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__read,libc_read,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize),(fd,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(__libc_read,libc_read,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize),(fd,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(read,libc_read,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize),(fd,buf,bufsize));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_write,libc_write,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize),(fd,buf,bufsize));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__write,libc_write,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize),(fd,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(__libc_write,libc_write,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize),(fd,buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(write,libc_write,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize),(fd,buf,bufsize));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_lseek,libc_lseek,ATTR_FDARG(1),off_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__lseek,libc_lseek,ATTR_FDARG(1),off_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(__libc_lseek,libc_lseek,ATTR_FDARG(1),off_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(lseek,libc_lseek,ATTR_FDARG(1),off_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(DOS$_dup2,libd_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBDCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
DEFINE_PUBLIC_ALIAS_P(DOS$__dup2,libd_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBDCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_dup2,libd_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBDCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
DEFINE_PUBLIC_ALIAS_P(DOS$dup2,libd_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBDCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_dup2,libc_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__dup2,libc_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
DEFINE_PUBLIC_ALIAS_P(__libc_dup2,libc_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
DEFINE_PUBLIC_ALIAS_P(dup2,libc_dup2,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t oldfd, fd_t newfd),(oldfd,newfd));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_dup,libc_dup,WUNUSED ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__dup,libc_dup,WUNUSED ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__libc_dup,libc_dup,WUNUSED ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(dup,libc_dup,WUNUSED ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_close,libc_close,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__close,libc_close,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__libc_close,libc_close,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__close_nocancel,libc_close,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(close,libc_close,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(DOS$_access,libd_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$__access,libd_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_access,libd_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$access,libd_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_access,libc_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__access,libc_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(__libc_access,libc_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(access,libc_access,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$_chdir,libd_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$__chdir,libd_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_chdir,libd_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$chdir_long,libd_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$chdir,libd_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(__chdir,libc_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(__libc_chdir,libc_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(chdir_long,libc_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(chdir,libc_chdir,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$_getcwd,libd_getcwd,ATTR_OUT_OPT(1),char *,NOTHROW_RPC,LIBDCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$__getcwd,libd_getcwd,ATTR_OUT_OPT(1),char *,NOTHROW_RPC,LIBDCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$getcwd,libd_getcwd,ATTR_OUT_OPT(1),char *,NOTHROW_RPC,LIBDCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(__getcwd,libc_getcwd,ATTR_OUT_OPT(1),char *,NOTHROW_RPC,LIBCCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(getcwd,libc_getcwd,ATTR_OUT_OPT(1),char *,NOTHROW_RPC,LIBCCALL,(char *buf, size_t bufsize),(buf,bufsize));
DEFINE_PUBLIC_ALIAS_P(DOS$_unlink,libd_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(DOS$__unlink,libd_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_unlink,libd_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(DOS$unlink,libd_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(__unlink,libc_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(__libc_unlink,libc_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(unlink,libc_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(DOS$_rmdir,libd_rmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$__rmdir,libd_rmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_rmdir,libd_rmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$rmdir,libd_rmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(__rmdir,libc_rmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(__libc_rmdir,libc_rmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(rmdir,libc_rmdir,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$eaccess,libd_euidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$__euidaccess,libd_euidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$euidaccess,libd_euidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(eaccess,libc_euidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(__euidaccess,libc_euidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(euidaccess,libc_euidaccess,WUNUSED ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, __STDC_INT_AS_UINT_T type),(file,type));
DEFINE_PUBLIC_ALIAS_P(DOS$faccessat,libd_faccessat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char const *file, __STDC_INT_AS_UINT_T type, atflag_t flags),(dfd,file,type,flags));
DEFINE_PUBLIC_ALIAS_P(faccessat,libc_faccessat,ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(fd_t dfd, char const *file, __STDC_INT_AS_UINT_T type, atflag_t flags),(dfd,file,type,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$fchownat,libd_fchownat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags),(dfd,file,owner,group,flags));
DEFINE_PUBLIC_ALIAS_P(fchownat,libc_fchownat,ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags),(dfd,file,owner,group,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$linkat,libd_linkat,ATTR_IN(2) ATTR_IN(4),int,NOTHROW_RPC,LIBDCALL,(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags),(fromfd,from,tofd,to,flags));
DEFINE_PUBLIC_ALIAS_P(linkat,libc_linkat,ATTR_IN(2) ATTR_IN(4),int,NOTHROW_RPC,LIBCCALL,(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags),(fromfd,from,tofd,to,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$symlinkat,libd_symlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char const *link_text, fd_t tofd, char const *target_path),(link_text,tofd,target_path));
DEFINE_PUBLIC_ALIAS_P(symlinkat,libc_symlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBCCALL,(char const *link_text, fd_t tofd, char const *target_path),(link_text,tofd,target_path));
DEFINE_PUBLIC_ALIAS_P(DOS$readlinkat,libd_readlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char const *path, char *buf, size_t buflen),(dfd,path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(readlinkat,libc_readlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t dfd, char const *path, char *buf, size_t buflen),(dfd,path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$unlinkat,libd_unlinkat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char const *name, atflag_t flags),(dfd,name,flags));
DEFINE_PUBLIC_ALIAS_P(unlinkat,libc_unlinkat,ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(fd_t dfd, char const *name, atflag_t flags),(dfd,name,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$fchdirat,libd_fchdirat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char const *path, atflag_t flags),(dfd,path,flags));
DEFINE_PUBLIC_ALIAS_P(fchdirat,libc_fchdirat,ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(fd_t dfd, char const *path, atflag_t flags),(dfd,path,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$fsymlinkat,libd_fsymlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags),(link_text,tofd,target_path,flags));
DEFINE_PUBLIC_ALIAS_P(fsymlinkat,libc_fsymlinkat,ATTR_IN(1) ATTR_IN(3),int,NOTHROW_RPC,LIBCCALL,(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags),(link_text,tofd,target_path,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$freadlinkat,libd_freadlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBDCALL,(fd_t dfd, char const *path, char *buf, size_t buflen, atflag_t flags),(dfd,path,buf,buflen,flags));
DEFINE_PUBLIC_ALIAS_P(freadlinkat,libc_freadlinkat,ATTR_IN(2) ATTR_OUTS(3, 4),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t dfd, char const *path, char *buf, size_t buflen, atflag_t flags),(dfd,path,buf,buflen,flags));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_lseeki64,libc_lseek64,ATTR_FDARG(1),off64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(llseek,libc_lseek64,ATTR_FDARG(1),off64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(__llseek,libc_lseek64,ATTR_FDARG(1),off64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(__libc_lseek64,libc_lseek64,ATTR_FDARG(1),off64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(__sys_llseek,libc_lseek64,ATTR_FDARG(1),off64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(lseek64,libc_lseek64,ATTR_FDARG(1),off64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence),(fd,offset,whence));
DEFINE_PUBLIC_ALIAS_P(__libc_pread,libc_pread,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(pread,libc_pread,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(__libc_pwrite,libc_pwrite,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(pwrite,libc_pwrite,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(__pread64,libc_pread64,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(__libc_pread64,libc_pread64,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(pread64,libc_pread64,ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(__pwrite64,libc_pwrite64,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(__libc_pwrite64,libc_pwrite64,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(pwrite64,libc_pwrite64,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(DOS$dup3,libd_dup3,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBDCALL,(fd_t oldfd, fd_t newfd, oflag_t flags),(oldfd,newfd,flags));
DEFINE_PUBLIC_ALIAS_P(dup3,libc_dup3,ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t oldfd, fd_t newfd, oflag_t flags),(oldfd,newfd,flags));
DEFINE_PUBLIC_ALIAS_P(pipe2,libc_pipe2,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fd_t pipedes[2], oflag_t flags),(pipedes,flags));
DEFINE_PUBLIC_ALIAS_P(syncfs,libc_syncfs,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(getresuid,libc_getresuid,ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3),int,NOTHROW_NCX,LIBCCALL,(uid_t *ruid, uid_t *euid, uid_t *suid),(ruid,euid,suid));
DEFINE_PUBLIC_ALIAS_P(getresgid,libc_getresgid,ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3),int,NOTHROW_NCX,LIBCCALL,(gid_t *rgid, gid_t *egid, gid_t *sgid),(rgid,egid,sgid));
DEFINE_PUBLIC_ALIAS_P(setresuid,libc_setresuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t ruid, uid_t euid, uid_t suid),(ruid,euid,suid));
DEFINE_PUBLIC_ALIAS_P(setresgid,libc_setresgid,,int,NOTHROW_NCX,LIBCCALL,(gid_t rgid, gid_t egid, gid_t sgid),(rgid,egid,sgid));
DEFINE_PUBLIC_ALIAS_P(__fchown,libc_fchown,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, uid_t owner, gid_t group),(fd,owner,group));
DEFINE_PUBLIC_ALIAS_P(__libc_fchown,libc_fchown,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, uid_t owner, gid_t group),(fd,owner,group));
DEFINE_PUBLIC_ALIAS_P(fchown,libc_fchown,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, uid_t owner, gid_t group),(fd,owner,group));
DEFINE_PUBLIC_ALIAS_P(__fchdir,libc_fchdir,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__libc_fchdir,libc_fchdir,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(fchdir,libc_fchdir,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__getpgid,libc_getpgid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(pid_t pid),(pid));
DEFINE_PUBLIC_ALIAS_P(__libc_getpgid,libc_getpgid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(pid_t pid),(pid));
DEFINE_PUBLIC_ALIAS_P(__bsd_getpgrp,libc_getpgid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(pid_t pid),(pid));
DEFINE_PUBLIC_ALIAS_P(getpgid,libc_getpgid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(pid_t pid),(pid));
DEFINE_PUBLIC_ALIAS_P(__getsid,libc_getsid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(pid_t pid),(pid));
DEFINE_PUBLIC_ALIAS_P(__libc_getsid,libc_getsid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(pid_t pid),(pid));
DEFINE_PUBLIC_ALIAS_P(getsid,libc_getsid,WUNUSED,pid_t,NOTHROW_NCX,LIBCCALL,(pid_t pid),(pid));
DEFINE_PUBLIC_ALIAS_P(DOS$__lchown,libd_lchown,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(DOS$lchown,libd_lchown,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(__lchown,libc_lchown,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(lchown,libc_lchown,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file, uid_t owner, gid_t group),(file,owner,group));
DEFINE_PUBLIC_ALIAS_P(DOS$__truncate,libd_truncate,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_truncate,libd_truncate,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(DOS$truncate,libd_truncate,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(__truncate,libc_truncate,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(__libc_truncate,libc_truncate,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(truncate,libc_truncate,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *file, __PIO_OFFSET length),(file,length));
DEFINE_PUBLIC_ALIAS_P(DOS$truncate64,libd_truncate64,ATTR_IN(1),int,NOTHROW_NCX,LIBDCALL,(char const *file, __PIO_OFFSET64 length),(file,length));
DEFINE_PUBLIC_ALIAS_P(truncate64,libc_truncate64,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *file, __PIO_OFFSET64 length),(file,length));
DEFINE_PUBLIC_ALIAS_P(fexecve,libc_fexecve,ATTR_FDREAD(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBCCALL,(fd_t execfd, __TARGV, __TENVP),(execfd,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(__nice,libc_nice,,int,NOTHROW_NCX,LIBCCALL,(int inc),(inc));
DEFINE_PUBLIC_ALIAS_P(__libc_nice,libc_nice,,int,NOTHROW_NCX,LIBCCALL,(int inc),(inc));
DEFINE_PUBLIC_ALIAS_P(nice,libc_nice,,int,NOTHROW_NCX,LIBCCALL,(int inc),(inc));
DEFINE_PUBLIC_ALIAS_P(confstr,libc_confstr,ATTR_OUTS(2, 3),size_t,NOTHROW_NCX,LIBCCALL,(__STDC_INT_AS_UINT_T name, char *buf, size_t buflen),(name,buf,buflen));
DEFINE_PUBLIC_ALIAS_P_VOID(__sync,libc_sync,,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(__libc_sync,libc_sync,,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(sync,libc_sync,,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__setreuid,libc_setreuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t ruid, uid_t euid),(ruid,euid));
DEFINE_PUBLIC_ALIAS_P(__libc_setreuid,libc_setreuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t ruid, uid_t euid),(ruid,euid));
DEFINE_PUBLIC_ALIAS_P(setreuid,libc_setreuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t ruid, uid_t euid),(ruid,euid));
DEFINE_PUBLIC_ALIAS_P(__setregid,libc_setregid,,int,NOTHROW_NCX,LIBCCALL,(gid_t rgid, gid_t egid),(rgid,egid));
DEFINE_PUBLIC_ALIAS_P(__libc_setregid,libc_setregid,,int,NOTHROW_NCX,LIBCCALL,(gid_t rgid, gid_t egid),(rgid,egid));
DEFINE_PUBLIC_ALIAS_P(setregid,libc_setregid,,int,NOTHROW_NCX,LIBCCALL,(gid_t rgid, gid_t egid),(rgid,egid));
DEFINE_PUBLIC_ALIAS_P(DOS$__symlink,libd_symlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char const *link_text, char const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_symlink,libd_symlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char const *link_text, char const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(DOS$symlink,libd_symlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char const *link_text, char const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(__symlink,libc_symlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *link_text, char const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(__libc_symlink,libc_symlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *link_text, char const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(symlink,libc_symlink,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(char const *link_text, char const *target_path),(link_text,target_path));
DEFINE_PUBLIC_ALIAS_P(DOS$__readlink,libd_readlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBDCALL,(char const *path, char *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_readlink,libd_readlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBDCALL,(char const *path, char *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(DOS$readlink,libd_readlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBDCALL,(char const *path, char *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(__readlink,libc_readlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(char const *path, char *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(__libc_readlink,libc_readlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(char const *path, char *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(readlink,libc_readlink,ATTR_IN(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(char const *path, char *buf, size_t buflen),(path,buf,buflen));
DEFINE_PUBLIC_ALIAS_P(setlogin,libc_setlogin,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(char const *name),(name));
DEFINE_PUBLIC_ALIAS_P(__sethostname,libc_sethostname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBCCALL,(char const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(__libc_sethostname,libc_sethostname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBCCALL,(char const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(sethostname,libc_sethostname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBCCALL,(char const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(__setdomainname,libc_setdomainname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBCCALL,(char const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(__libc_setdomainname,libc_setdomainname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBCCALL,(char const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(setdomainname,libc_setdomainname,ATTR_INS(1, 2),int,NOTHROW_NCX,LIBCCALL,(char const *name, size_t len),(name,len));
DEFINE_PUBLIC_ALIAS_P(__vhangup,libc_vhangup,,int,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__libc_vhangup,libc_vhangup,,int,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(vhangup,libc_vhangup,,int,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(profil,libc_profil,NONNULL((1)),int,NOTHROW_NCX,LIBCCALL,(uint16_t *sample_buffer, size_t size, size_t offset, unsigned int scale),(sample_buffer,size,offset,scale));
DEFINE_PUBLIC_ALIAS_P(getusershell,libc_getusershell,WUNUSED,char *,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(endusershell,libc_endusershell,,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P_VOID(setusershell,libc_setusershell,,NOTHROW_RPC,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(revoke,libc_revoke,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *file),(file));
DEFINE_PUBLIC_ALIAS_P(DOS$__chroot,libd_chroot,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *__restrict path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_chroot,libd_chroot,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *__restrict path),(path));
DEFINE_PUBLIC_ALIAS_P(DOS$chroot,libd_chroot,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *__restrict path),(path));
DEFINE_PUBLIC_ALIAS_P(__chroot,libc_chroot,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *__restrict path),(path));
DEFINE_PUBLIC_ALIAS_P(__libc_chroot,libc_chroot,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *__restrict path),(path));
DEFINE_PUBLIC_ALIAS_P(chroot,libc_chroot,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *__restrict path),(path));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_chsize,libc_ftruncate,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET length),(fd,length));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__ftruncate,libc_ftruncate,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET length),(fd,length));
DEFINE_PUBLIC_ALIAS_P(__libc_ftruncate,libc_ftruncate,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET length),(fd,length));
DEFINE_PUBLIC_ALIAS_P(chsize,libc_ftruncate,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET length),(fd,length));
DEFINE_PUBLIC_ALIAS_P(ftruncate,libc_ftruncate,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET length),(fd,length));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_chsize_s,libc_ftruncate64,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET64 length),(fd,length));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(ftruncate64,libc_ftruncate64,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET64 length),(fd,length));
DEFINE_PUBLIC_ALIAS_P(__brk,libc_brk,,int,NOTHROW_NCX,LIBCCALL,(void *addr),(addr));
DEFINE_PUBLIC_ALIAS_P(brk,libc_brk,,int,NOTHROW_NCX,LIBCCALL,(void *addr),(addr));
DEFINE_PUBLIC_ALIAS_P(__sbrk,libc_sbrk,,void *,NOTHROW_NCX,LIBCCALL,(intptr_t delta),(delta));
DEFINE_PUBLIC_ALIAS_P(sbrk,libc_sbrk,,void *,NOTHROW_NCX,LIBCCALL,(intptr_t delta),(delta));
DEFINE_PUBLIC_ALIAS_P(__fdatasync,libc_fdatasync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__libc_fdatasync,libc_fdatasync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(__libc_fsync,libc_fdatasync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(fdatasync,libc_fdatasync,ATTR_FDWRITE(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(setmode,libc_setmode,WUNUSED ATTR_IN(1),void *,NOTHROW_NCX,LIBCCALL,(char const *mode_str),(mode_str));
DEFINE_PUBLIC_ALIAS_P(getmode,libc_getmode,WUNUSED ATTR_IN(1),mode_t,NOTHROW_NCX,LIBCCALL,(void const *bbox, mode_t mode),(bbox,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$lpathconf,libd_lpathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBDCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(lpathconf,libc_lpathconf,ATTR_IN(1),longptr_t,NOTHROW_RPC,LIBCCALL,(char const *path, __STDC_INT_AS_UINT_T name),(path,name));
DEFINE_PUBLIC_ALIAS_P(__sysconf,libc_sysconf,WUNUSED,longptr_t,NOTHROW_RPC,LIBCCALL,(__STDC_INT_AS_UINT_T name),(name));
DEFINE_PUBLIC_ALIAS_P(sysconf,libc_sysconf,WUNUSED,longptr_t,NOTHROW_RPC,LIBCCALL,(__STDC_INT_AS_UINT_T name),(name));
DEFINE_PUBLIC_ALIAS_P(close_range,libc_close_range,,int,NOTHROW_NCX,LIBCCALL,(unsigned int minfd, unsigned int maxfd, unsigned int flags),(minfd,maxfd,flags));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UNISTD_C */
