/* HASH CRC-32:0xb402d13a */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_SYSCALLS_S
#define GUARD_LIBC_LIBC_ARCH_ARM_SYSCALLS_S 1

#include <hybrid/compiler.h>

.section .text.crt.syscalls
/* TODO: arm_printLibcSyscallWrapperPrefix() */

/* errno_t restart_syscall(void) */
INTERN_FUNCTION(libc_sys_restart_syscall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 0, enableExcept: false) */
	b .
END(libc_sys_restart_syscall)
DEFINE_PUBLIC_ALIAS(sys_restart_syscall, libc_sys_restart_syscall)

/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_exit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 1, enableExcept: false) */
	b .
END(libc_sys_exit)
DEFINE_PUBLIC_ALIAS(sys_exit, libc_sys_exit)

/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
/* pid_t fork(void) */
INTERN_FUNCTION(libc_sys_fork)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 2, enableExcept: false) */
	b .
END(libc_sys_fork)
DEFINE_PUBLIC_ALIAS(sys_fork, libc_sys_fork)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_read)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 3, enableExcept: false) */
	b .
END(libc_sys_read)
DEFINE_PUBLIC_ALIAS(sys_read, libc_sys_read)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_write)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 4, enableExcept: false) */
	b .
END(libc_sys_write)
DEFINE_PUBLIC_ALIAS(sys_write, libc_sys_write)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_open)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 5, enableExcept: false) */
	b .
END(libc_sys_open)
DEFINE_PUBLIC_ALIAS(sys_open, libc_sys_open)

/* Close a given file descriptor/handle `fd' */
/* errno_t close(fd_t fd) */
INTERN_FUNCTION(libc_sys_close)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 6, enableExcept: false) */
	b .
END(libc_sys_close)
DEFINE_PUBLIC_ALIAS(sys_close, libc_sys_close)

/* fd_t creat(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_creat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8, enableExcept: false) */
	b .
END(libc_sys_creat)
DEFINE_PUBLIC_ALIAS(sys_creat, libc_sys_creat)

/* errno_t link(char const *existing_file, char const *link_file) */
INTERN_FUNCTION(libc_sys_link)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 9, enableExcept: false) */
	b .
END(libc_sys_link)
DEFINE_PUBLIC_ALIAS(sys_link, libc_sys_link)

/* errno_t unlink(char const *filename) */
INTERN_FUNCTION(libc_sys_unlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 10, enableExcept: false) */
	b .
END(libc_sys_unlink)
DEFINE_PUBLIC_ALIAS(sys_unlink, libc_sys_unlink)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
INTERN_FUNCTION(libc_sys_execve)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 11, enableExcept: false) */
	b .
END(libc_sys_execve)
DEFINE_PUBLIC_ALIAS(sys_execve, libc_sys_execve)

/* errno_t chdir(char const *path) */
INTERN_FUNCTION(libc_sys_chdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 12, enableExcept: false) */
	b .
END(libc_sys_chdir)
DEFINE_PUBLIC_ALIAS(sys_chdir, libc_sys_chdir)

/* time32_t time(time32_t *timer) */
INTERN_FUNCTION(libc_sys_time)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 13, enableExcept: false) */
	b .
END(libc_sys_time)
DEFINE_PUBLIC_ALIAS(sys_time, libc_sys_time)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_mknod)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 14, enableExcept: false) */
	b .
END(libc_sys_mknod)
DEFINE_PUBLIC_ALIAS(sys_mknod, libc_sys_mknod)

/* errno_t chmod(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_chmod)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 15, enableExcept: false) */
	b .
END(libc_sys_chmod)
DEFINE_PUBLIC_ALIAS(sys_chmod, libc_sys_chmod)

/* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
INTERN_FUNCTION(libc_sys_lchown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 16, enableExcept: false) */
	b .
END(libc_sys_lchown)
DEFINE_PUBLIC_ALIAS(sys_lchown, libc_sys_lchown)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_lseek)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 19, enableExcept: false) */
	b .
END(libc_sys_lseek)
DEFINE_PUBLIC_ALIAS(sys_lseek, libc_sys_lseek)

/* pid_t getpid(void) */
INTERN_FUNCTION(libc_sys_getpid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 20, enableExcept: false) */
	b .
END(libc_sys_getpid)
DEFINE_PUBLIC_ALIAS(sys_getpid, libc_sys_getpid)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
INTERN_FUNCTION(libc_sys_mount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 21, enableExcept: false) */
	b .
END(libc_sys_mount)
DEFINE_PUBLIC_ALIAS(sys_mount, libc_sys_mount)

/* errno_t umount(char const *special_file) */
INTERN_FUNCTION(libc_sys_umount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 22, enableExcept: false) */
	b .
END(libc_sys_umount)
DEFINE_PUBLIC_ALIAS(sys_umount, libc_sys_umount)

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid(uint16_t uid) */
INTERN_FUNCTION(libc_sys_setuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 23, enableExcept: false) */
	b .
END(libc_sys_setuid)
DEFINE_PUBLIC_ALIAS(sys_setuid, libc_sys_setuid)

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uint16_t getuid(void) */
INTERN_FUNCTION(libc_sys_getuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 24, enableExcept: false) */
	b .
END(libc_sys_getuid)
DEFINE_PUBLIC_ALIAS(sys_getuid, libc_sys_getuid)

/* errno_t stime(time32_t const *t) */
INTERN_FUNCTION(libc_sys_stime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 25, enableExcept: false) */
	b .
END(libc_sys_stime)
DEFINE_PUBLIC_ALIAS(sys_stime, libc_sys_stime)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
INTERN_FUNCTION(libc_sys_ptrace)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 26, enableExcept: false) */
	b .
END(libc_sys_ptrace)
DEFINE_PUBLIC_ALIAS(sys_ptrace, libc_sys_ptrace)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
INTERN_FUNCTION(libc_sys_alarm)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 27, enableExcept: false) */
	b .
END(libc_sys_alarm)
DEFINE_PUBLIC_ALIAS(sys_alarm, libc_sys_alarm)

/* Same as `select(0, NULL, NULL, NULL, NULL)' */
/* errno_t pause(void) */
INTERN_FUNCTION(libc_sys_pause)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 29, enableExcept: false) */
	b .
END(libc_sys_pause)
DEFINE_PUBLIC_ALIAS(sys_pause, libc_sys_pause)

/* @param: times: When NULL, set the current time */
/* errno_t utime(char const *filename, struct utimbuf32 const *times) */
INTERN_FUNCTION(libc_sys_utime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 30, enableExcept: false) */
	b .
END(libc_sys_utime)
DEFINE_PUBLIC_ALIAS(sys_utime, libc_sys_utime)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_access)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 33, enableExcept: false) */
	b .
END(libc_sys_access)
DEFINE_PUBLIC_ALIAS(sys_access, libc_sys_access)

/* errno_t nice(syscall_slong_t inc) */
INTERN_FUNCTION(libc_sys_nice)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 34, enableExcept: false) */
	b .
END(libc_sys_nice)
DEFINE_PUBLIC_ALIAS(sys_nice, libc_sys_nice)

/* errno_t sync(void) */
INTERN_FUNCTION(libc_sys_sync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 36, enableExcept: false) */
	b .
END(libc_sys_sync)
DEFINE_PUBLIC_ALIAS(sys_sync, libc_sys_sync)

/* errno_t kill(pid_t pid, signo_t signo) */
INTERN_FUNCTION(libc_sys_kill)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 37, enableExcept: false) */
	b .
END(libc_sys_kill)
DEFINE_PUBLIC_ALIAS(sys_kill, libc_sys_kill)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_rename)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 38, enableExcept: false) */
	b .
END(libc_sys_rename)
DEFINE_PUBLIC_ALIAS(sys_rename, libc_sys_rename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_mkdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 39, enableExcept: false) */
	b .
END(libc_sys_mkdir)
DEFINE_PUBLIC_ALIAS(sys_mkdir, libc_sys_mkdir)

/* errno_t rmdir(char const *path) */
INTERN_FUNCTION(libc_sys_rmdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 40, enableExcept: false) */
	b .
END(libc_sys_rmdir)
DEFINE_PUBLIC_ALIAS(sys_rmdir, libc_sys_rmdir)

/* fd_t dup(fd_t fd) */
INTERN_FUNCTION(libc_sys_dup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 41, enableExcept: false) */
	b .
END(libc_sys_dup)
DEFINE_PUBLIC_ALIAS(sys_dup, libc_sys_dup)

/* errno_t pipe(fd_t[2] pipedes) */
INTERN_FUNCTION(libc_sys_pipe)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 42, enableExcept: false) */
	b .
END(libc_sys_pipe)
DEFINE_PUBLIC_ALIAS(sys_pipe, libc_sys_pipe)

/* clock_t times(struct tms *buf) */
INTERN_FUNCTION(libc_sys_times)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 43, enableExcept: false) */
	b .
END(libc_sys_times)
DEFINE_PUBLIC_ALIAS(sys_times, libc_sys_times)

/* errno_t brk(void *addr) */
INTERN_FUNCTION(libc_sys_brk)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 45, enableExcept: false) */
	b .
END(libc_sys_brk)
DEFINE_PUBLIC_ALIAS(sys_brk, libc_sys_brk)

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid(uint16_t gid) */
INTERN_FUNCTION(libc_sys_setgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 46, enableExcept: false) */
	b .
END(libc_sys_setgid)
DEFINE_PUBLIC_ALIAS(sys_setgid, libc_sys_setgid)

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* uint16_t getgid(void) */
INTERN_FUNCTION(libc_sys_getgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 47, enableExcept: false) */
	b .
END(libc_sys_getgid)
DEFINE_PUBLIC_ALIAS(sys_getgid, libc_sys_getgid)

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint16_t geteuid(void) */
INTERN_FUNCTION(libc_sys_geteuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 49, enableExcept: false) */
	b .
END(libc_sys_geteuid)
DEFINE_PUBLIC_ALIAS(sys_geteuid, libc_sys_geteuid)

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint16_t getegid(void) */
INTERN_FUNCTION(libc_sys_getegid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 50, enableExcept: false) */
	b .
END(libc_sys_getegid)
DEFINE_PUBLIC_ALIAS(sys_getegid, libc_sys_getegid)

/* errno_t acct(char const *filename) */
INTERN_FUNCTION(libc_sys_acct)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 51, enableExcept: false) */
	b .
END(libc_sys_acct)
DEFINE_PUBLIC_ALIAS(sys_acct, libc_sys_acct)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_umount2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 52, enableExcept: false) */
	b .
END(libc_sys_umount2)
DEFINE_PUBLIC_ALIAS(sys_umount2, libc_sys_umount2)

/* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_ioctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 54, enableExcept: false) */
	b .
END(libc_sys_ioctl)
DEFINE_PUBLIC_ALIAS(sys_ioctl, libc_sys_ioctl)

/* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_fcntl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 55, enableExcept: false) */
	b .
END(libc_sys_fcntl)
DEFINE_PUBLIC_ALIAS(sys_fcntl, libc_sys_fcntl)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
INTERN_FUNCTION(libc_sys_setpgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 57, enableExcept: false) */
	b .
END(libc_sys_setpgid)
DEFINE_PUBLIC_ALIAS(sys_setpgid, libc_sys_setpgid)

/* mode_t umask(mode_t mode) */
INTERN_FUNCTION(libc_sys_umask)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 60, enableExcept: false) */
	b .
END(libc_sys_umask)
DEFINE_PUBLIC_ALIAS(sys_umask, libc_sys_umask)

/* errno_t chroot(char const *path) */
INTERN_FUNCTION(libc_sys_chroot)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 61, enableExcept: false) */
	b .
END(libc_sys_chroot)
DEFINE_PUBLIC_ALIAS(sys_chroot, libc_sys_chroot)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
INTERN_FUNCTION(libc_sys_ustat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 62, enableExcept: false) */
	b .
END(libc_sys_ustat)
DEFINE_PUBLIC_ALIAS(sys_ustat, libc_sys_ustat)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
INTERN_FUNCTION(libc_sys_dup2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 63, enableExcept: false) */
	b .
END(libc_sys_dup2)
DEFINE_PUBLIC_ALIAS(sys_dup2, libc_sys_dup2)

/* pid_t getppid(void) */
INTERN_FUNCTION(libc_sys_getppid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 64, enableExcept: false) */
	b .
END(libc_sys_getppid)
DEFINE_PUBLIC_ALIAS(sys_getppid, libc_sys_getppid)

/* pid_t getpgrp(void) */
INTERN_FUNCTION(libc_sys_getpgrp)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 65, enableExcept: false) */
	b .
END(libc_sys_getpgrp)
DEFINE_PUBLIC_ALIAS(sys_getpgrp, libc_sys_getpgrp)

/* pid_t setsid(void) */
INTERN_FUNCTION(libc_sys_setsid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 66, enableExcept: false) */
	b .
END(libc_sys_setsid)
DEFINE_PUBLIC_ALIAS(sys_setsid, libc_sys_setsid)

/* errno_t sigaction(signo_t signo, struct __old_kernel_sigaction const *act, struct __old_kernel_sigaction *oact) */
INTERN_FUNCTION(libc_sys_sigaction)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 67, enableExcept: false) */
	b .
END(libc_sys_sigaction)
DEFINE_PUBLIC_ALIAS(sys_sigaction, libc_sys_sigaction)

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid(uint16_t ruid, uint16_t euid) */
INTERN_FUNCTION(libc_sys_setreuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 70, enableExcept: false) */
	b .
END(libc_sys_setreuid)
DEFINE_PUBLIC_ALIAS(sys_setreuid, libc_sys_setreuid)

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid(uint16_t rgid, uint16_t egid) */
INTERN_FUNCTION(libc_sys_setregid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 71, enableExcept: false) */
	b .
END(libc_sys_setregid)
DEFINE_PUBLIC_ALIAS(sys_setregid, libc_sys_setregid)

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t sigsuspend(struct __old_sigset_struct const *set) */
INTERN_FUNCTION(libc_sys_sigsuspend)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 72, enableExcept: false) */
	b .
END(libc_sys_sigsuspend)
DEFINE_PUBLIC_ALIAS(sys_sigsuspend, libc_sys_sigsuspend)

/* errno_t sigpending(struct __old_sigset_struct *set) */
INTERN_FUNCTION(libc_sys_sigpending)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 73, enableExcept: false) */
	b .
END(libc_sys_sigpending)
DEFINE_PUBLIC_ALIAS(sys_sigpending, libc_sys_sigpending)

/* errno_t sethostname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_sethostname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 74, enableExcept: false) */
	b .
END(libc_sys_sethostname)
DEFINE_PUBLIC_ALIAS(sys_sethostname, libc_sys_sethostname)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
INTERN_FUNCTION(libc_sys_setrlimit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 75, enableExcept: false) */
	b .
END(libc_sys_setrlimit)
DEFINE_PUBLIC_ALIAS(sys_setrlimit, libc_sys_setrlimit)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
INTERN_FUNCTION(libc_sys_getrlimit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 76, enableExcept: false) */
	b .
END(libc_sys_getrlimit)
DEFINE_PUBLIC_ALIAS(sys_getrlimit, libc_sys_getrlimit)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
INTERN_FUNCTION(libc_sys_getrusage)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 77, enableExcept: false) */
	b .
END(libc_sys_getrusage)
DEFINE_PUBLIC_ALIAS(sys_getrusage, libc_sys_getrusage)

/* errno_t gettimeofday(struct timeval *tv, struct timezone *tz) */
INTERN_FUNCTION(libc_sys_gettimeofday)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 78, enableExcept: false) */
	b .
END(libc_sys_gettimeofday)
DEFINE_PUBLIC_ALIAS(sys_gettimeofday, libc_sys_gettimeofday)

/* errno_t settimeofday(struct timeval const *tv, struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_settimeofday)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 79, enableExcept: false) */
	b .
END(libc_sys_settimeofday)
DEFINE_PUBLIC_ALIAS(sys_settimeofday, libc_sys_settimeofday)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups(size_t count, uint16_t[] list) */
INTERN_FUNCTION(libc_sys_getgroups)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 80, enableExcept: false) */
	b .
END(libc_sys_getgroups)
DEFINE_PUBLIC_ALIAS(sys_getgroups, libc_sys_getgroups)

/* errno_t setgroups(size_t count, uint16_t const *groups) */
INTERN_FUNCTION(libc_sys_setgroups)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 81, enableExcept: false) */
	b .
END(libc_sys_setgroups)
DEFINE_PUBLIC_ALIAS(sys_setgroups, libc_sys_setgroups)

/* ssize_t select(struct sel_arg_struct const *arg) */
INTERN_FUNCTION(libc_sys_select)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 82, enableExcept: false) */
	b .
END(libc_sys_select)
DEFINE_PUBLIC_ALIAS(sys_select, libc_sys_select)

/* errno_t symlink(char const *link_text, char const *target_path) */
INTERN_FUNCTION(libc_sys_symlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 83, enableExcept: false) */
	b .
END(libc_sys_symlink)
DEFINE_PUBLIC_ALIAS(sys_symlink, libc_sys_symlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_readlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 85, enableExcept: false) */
	b .
END(libc_sys_readlink)
DEFINE_PUBLIC_ALIAS(sys_readlink, libc_sys_readlink)

/* errno_t uselib(char const *library) */
INTERN_FUNCTION(libc_sys_uselib)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 86, enableExcept: false) */
	b .
END(libc_sys_uselib)
DEFINE_PUBLIC_ALIAS(sys_uselib, libc_sys_uselib)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
INTERN_FUNCTION(libc_sys_swapon)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 87, enableExcept: false) */
	b .
END(libc_sys_swapon)
DEFINE_PUBLIC_ALIAS(sys_swapon, libc_sys_swapon)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_reboot)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 88, enableExcept: false) */
	b .
END(libc_sys_reboot)
DEFINE_PUBLIC_ALIAS(sys_reboot, libc_sys_reboot)

/* Read exactly one directory entry from `fd'
 * Note that the linux version of this system call has one additional argument `count'.
 * However, within the  linux kernel implementation,  that argument is  unconditionally
 * ignored,  and the system call will _always_ read exactly 1 directory entry from `fd'
 * @return: 1 : Read on directory entry
 * @return: 0 : End-of-directory */
/* syscall_slong_t readdir(fd_t fd, struct old_linux_dirent *buf) */
INTERN_FUNCTION(libc_sys_readdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 89, enableExcept: false) */
	b .
END(libc_sys_readdir)
DEFINE_PUBLIC_ALIAS(sys_readdir, libc_sys_readdir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
INTERN_FUNCTION(libc_sys_mmap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 90, enableExcept: false) */
	b .
END(libc_sys_mmap)
DEFINE_PUBLIC_ALIAS(sys_mmap, libc_sys_mmap)

/* errno_t munmap(void *addr, size_t len) */
INTERN_FUNCTION(libc_sys_munmap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 91, enableExcept: false) */
	b .
END(libc_sys_munmap)
DEFINE_PUBLIC_ALIAS(sys_munmap, libc_sys_munmap)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_truncate)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 92, enableExcept: false) */
	b .
END(libc_sys_truncate)
DEFINE_PUBLIC_ALIAS(sys_truncate, libc_sys_truncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_ftruncate)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 93, enableExcept: false) */
	b .
END(libc_sys_ftruncate)
DEFINE_PUBLIC_ALIAS(sys_ftruncate, libc_sys_ftruncate)

/* errno_t fchmod(fd_t fd, mode_t mode) */
INTERN_FUNCTION(libc_sys_fchmod)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 94, enableExcept: false) */
	b .
END(libc_sys_fchmod)
DEFINE_PUBLIC_ALIAS(sys_fchmod, libc_sys_fchmod)

/* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
INTERN_FUNCTION(libc_sys_fchown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 95, enableExcept: false) */
	b .
END(libc_sys_fchown)
DEFINE_PUBLIC_ALIAS(sys_fchown, libc_sys_fchown)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
INTERN_FUNCTION(libc_sys_getpriority)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 96, enableExcept: false) */
	b .
END(libc_sys_getpriority)
DEFINE_PUBLIC_ALIAS(sys_getpriority, libc_sys_getpriority)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
INTERN_FUNCTION(libc_sys_setpriority)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 97, enableExcept: false) */
	b .
END(libc_sys_setpriority)
DEFINE_PUBLIC_ALIAS(sys_setpriority, libc_sys_setpriority)

/* errno_t statfs(char const *file, struct statfs *buf) */
INTERN_FUNCTION(libc_sys_statfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 99, enableExcept: false) */
	b .
END(libc_sys_statfs)
DEFINE_PUBLIC_ALIAS(sys_statfs, libc_sys_statfs)

/* errno_t fstatfs(fd_t file, struct statfs *buf) */
INTERN_FUNCTION(libc_sys_fstatfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 100, enableExcept: false) */
	b .
END(libc_sys_fstatfs)
DEFINE_PUBLIC_ALIAS(sys_fstatfs, libc_sys_fstatfs)

/* syscall_slong_t socketcall(syscall_ulong_t call, syscall_ulong_t *args) */
INTERN_FUNCTION(libc_sys_socketcall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 102, enableExcept: false) */
	b .
END(libc_sys_socketcall)
DEFINE_PUBLIC_ALIAS(sys_socketcall, libc_sys_socketcall)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
INTERN_FUNCTION(libc_sys_syslog)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 103, enableExcept: false) */
	b .
END(libc_sys_syslog)
DEFINE_PUBLIC_ALIAS(sys_syslog, libc_sys_syslog)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer(syscall_ulong_t which, struct itimerval const *newval, struct itimerval *oldval) */
INTERN_FUNCTION(libc_sys_setitimer)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 104, enableExcept: false) */
	b .
END(libc_sys_setitimer)
DEFINE_PUBLIC_ALIAS(sys_setitimer, libc_sys_setitimer)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer(syscall_ulong_t which, struct itimerval *curr_value) */
INTERN_FUNCTION(libc_sys_getitimer)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 105, enableExcept: false) */
	b .
END(libc_sys_getitimer)
DEFINE_PUBLIC_ALIAS(sys_getitimer, libc_sys_getitimer)

/* errno_t stat(char const *filename, struct linux_stat *statbuf) */
INTERN_FUNCTION(libc_sys_stat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 106, enableExcept: false) */
	b .
END(libc_sys_stat)
DEFINE_PUBLIC_ALIAS(sys_stat, libc_sys_stat)

/* errno_t lstat(char const *filename, struct linux_stat *statbuf) */
INTERN_FUNCTION(libc_sys_lstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 107, enableExcept: false) */
	b .
END(libc_sys_lstat)
DEFINE_PUBLIC_ALIAS(sys_lstat, libc_sys_lstat)

/* errno_t fstat(fd_t fd, struct linux_stat *statbuf) */
INTERN_FUNCTION(libc_sys_fstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 108, enableExcept: false) */
	b .
END(libc_sys_fstat)
DEFINE_PUBLIC_ALIAS(sys_fstat, libc_sys_fstat)

/* errno_t vhangup(void) */
INTERN_FUNCTION(libc_sys_vhangup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 111, enableExcept: false) */
	b .
END(libc_sys_vhangup)
DEFINE_PUBLIC_ALIAS(sys_vhangup, libc_sys_vhangup)

/* Syscall to call a syscall */
/* errno_t syscall(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_syscall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 113, enableExcept: false) */
	b .
END(libc_sys_syscall)
DEFINE_PUBLIC_ALIAS(sys_syscall, libc_sys_syscall)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
INTERN_FUNCTION(libc_sys_wait4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 114, enableExcept: false) */
	b .
END(libc_sys_wait4)
DEFINE_PUBLIC_ALIAS(sys_wait4, libc_sys_wait4)

/* errno_t swapoff(char const *pathname) */
INTERN_FUNCTION(libc_sys_swapoff)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 115, enableExcept: false) */
	b .
END(libc_sys_swapoff)
DEFINE_PUBLIC_ALIAS(sys_swapoff, libc_sys_swapoff)

/* errno_t sysinfo(struct sysinfo *info) */
INTERN_FUNCTION(libc_sys_sysinfo)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 116, enableExcept: false) */
	b .
END(libc_sys_sysinfo)
DEFINE_PUBLIC_ALIAS(sys_sysinfo, libc_sys_sysinfo)

/* errno_t ipc(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_ipc)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 117, enableExcept: false) */
	b .
END(libc_sys_ipc)
DEFINE_PUBLIC_ALIAS(sys_ipc, libc_sys_ipc)

/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
/* errno_t fsync(fd_t fd) */
INTERN_FUNCTION(libc_sys_fsync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 118, enableExcept: false) */
	b .
END(libc_sys_fsync)
DEFINE_PUBLIC_ALIAS(sys_fsync, libc_sys_fsync)

/* void sigreturn(void) */
INTERN_FUNCTION(libc_sys_sigreturn)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 119, enableExcept: false) */
	b .
END(libc_sys_sigreturn)
DEFINE_PUBLIC_ALIAS(sys_sigreturn, libc_sys_sigreturn)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
INTERN_FUNCTION(libc_sys_clone)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 120, enableExcept: false) */
	b .
END(libc_sys_clone)
DEFINE_PUBLIC_ALIAS(sys_clone, libc_sys_clone)

/* errno_t setdomainname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_setdomainname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 121, enableExcept: false) */
	b .
END(libc_sys_setdomainname)
DEFINE_PUBLIC_ALIAS(sys_setdomainname, libc_sys_setdomainname)

/* errno_t uname(struct utsname *name) */
INTERN_FUNCTION(libc_sys_uname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 122, enableExcept: false) */
	b .
END(libc_sys_uname)
DEFINE_PUBLIC_ALIAS(sys_uname, libc_sys_uname)

/* errno_t adjtimex(struct timex32 *ntx) */
INTERN_FUNCTION(libc_sys_adjtimex)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 124, enableExcept: false) */
	b .
END(libc_sys_adjtimex)
DEFINE_PUBLIC_ALIAS(sys_adjtimex, libc_sys_adjtimex)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
INTERN_FUNCTION(libc_sys_mprotect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 125, enableExcept: false) */
	b .
END(libc_sys_mprotect)
DEFINE_PUBLIC_ALIAS(sys_mprotect, libc_sys_mprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t sigprocmask(syscall_ulong_t how, struct __old_sigset_struct const *set, struct __old_sigset_struct *oset) */
INTERN_FUNCTION(libc_sys_sigprocmask)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 126, enableExcept: false) */
	b .
END(libc_sys_sigprocmask)
DEFINE_PUBLIC_ALIAS(sys_sigprocmask, libc_sys_sigprocmask)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
INTERN_FUNCTION(libc_sys_init_module)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 128, enableExcept: false) */
	b .
END(libc_sys_init_module)
DEFINE_PUBLIC_ALIAS(sys_init_module, libc_sys_init_module)

/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
/* errno_t delete_module(char const *name, oflag_t flags) */
INTERN_FUNCTION(libc_sys_delete_module)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 129, enableExcept: false) */
	b .
END(libc_sys_delete_module)
DEFINE_PUBLIC_ALIAS(sys_delete_module, libc_sys_delete_module)

/* errno_t quotactl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_quotactl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 131, enableExcept: false) */
	b .
END(libc_sys_quotactl)
DEFINE_PUBLIC_ALIAS(sys_quotactl, libc_sys_quotactl)

/* pid_t getpgid(pid_t pid) */
INTERN_FUNCTION(libc_sys_getpgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 132, enableExcept: false) */
	b .
END(libc_sys_getpgid)
DEFINE_PUBLIC_ALIAS(sys_getpgid, libc_sys_getpgid)

/* errno_t fchdir(fd_t fd) */
INTERN_FUNCTION(libc_sys_fchdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 133, enableExcept: false) */
	b .
END(libc_sys_fchdir)
DEFINE_PUBLIC_ALIAS(sys_fchdir, libc_sys_fchdir)

/* errno_t bdflush(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_bdflush)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 134, enableExcept: false) */
	b .
END(libc_sys_bdflush)
DEFINE_PUBLIC_ALIAS(sys_bdflush, libc_sys_bdflush)

/* errno_t sysfs(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_sysfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 135, enableExcept: false) */
	b .
END(libc_sys_sysfs)
DEFINE_PUBLIC_ALIAS(sys_sysfs, libc_sys_sysfs)

/* errno_t personality(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_personality)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 136, enableExcept: false) */
	b .
END(libc_sys_personality)
DEFINE_PUBLIC_ALIAS(sys_personality, libc_sys_personality)

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid(uint16_t uid) */
INTERN_FUNCTION(libc_sys_setfsuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 138, enableExcept: false) */
	b .
END(libc_sys_setfsuid)
DEFINE_PUBLIC_ALIAS(sys_setfsuid, libc_sys_setfsuid)

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid(uint16_t gid) */
INTERN_FUNCTION(libc_sys_setfsgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 139, enableExcept: false) */
	b .
END(libc_sys_setfsgid)
DEFINE_PUBLIC_ALIAS(sys_setfsgid, libc_sys_setfsgid)

/* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys__llseek)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 140, enableExcept: false) */
	b .
END(libc_sys__llseek)
DEFINE_PUBLIC_ALIAS(sys__llseek, libc_sys__llseek)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents(fd_t fd, struct linux_dirent *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_getdents)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 141, enableExcept: false) */
	b .
END(libc_sys_getdents)
DEFINE_PUBLIC_ALIAS(sys_getdents, libc_sys_getdents)

/* ssize_t _newselect(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval32 *timeout) */
INTERN_FUNCTION(libc_sys__newselect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 142, enableExcept: false) */
	b .
END(libc_sys__newselect)
DEFINE_PUBLIC_ALIAS(sys__newselect, libc_sys__newselect)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
INTERN_FUNCTION(libc_sys_flock)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 143, enableExcept: false) */
	b .
END(libc_sys_flock)
DEFINE_PUBLIC_ALIAS(sys_flock, libc_sys_flock)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_msync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 144, enableExcept: false) */
	b .
END(libc_sys_msync)
DEFINE_PUBLIC_ALIAS(sys_msync, libc_sys_msync)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_readv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 145, enableExcept: false) */
	b .
END(libc_sys_readv)
DEFINE_PUBLIC_ALIAS(sys_readv, libc_sys_readv)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_writev)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 146, enableExcept: false) */
	b .
END(libc_sys_writev)
DEFINE_PUBLIC_ALIAS(sys_writev, libc_sys_writev)

/* pid_t getsid(pid_t pid) */
INTERN_FUNCTION(libc_sys_getsid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 147, enableExcept: false) */
	b .
END(libc_sys_getsid)
DEFINE_PUBLIC_ALIAS(sys_getsid, libc_sys_getsid)

/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
/* errno_t fdatasync(fd_t fd) */
INTERN_FUNCTION(libc_sys_fdatasync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 148, enableExcept: false) */
	b .
END(libc_sys_fdatasync)
DEFINE_PUBLIC_ALIAS(sys_fdatasync, libc_sys_fdatasync)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys__sysctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 149, enableExcept: false) */
	b .
END(libc_sys__sysctl)
DEFINE_PUBLIC_ALIAS(sys__sysctl, libc_sys__sysctl)

/* errno_t mlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_mlock)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 150, enableExcept: false) */
	b .
END(libc_sys_mlock)
DEFINE_PUBLIC_ALIAS(sys_mlock, libc_sys_mlock)

/* errno_t munlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_munlock)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 151, enableExcept: false) */
	b .
END(libc_sys_munlock)
DEFINE_PUBLIC_ALIAS(sys_munlock, libc_sys_munlock)

/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
/* errno_t mlockall(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_mlockall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 152, enableExcept: false) */
	b .
END(libc_sys_mlockall)
DEFINE_PUBLIC_ALIAS(sys_mlockall, libc_sys_mlockall)

/* errno_t munlockall(void) */
INTERN_FUNCTION(libc_sys_munlockall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 153, enableExcept: false) */
	b .
END(libc_sys_munlockall)
DEFINE_PUBLIC_ALIAS(sys_munlockall, libc_sys_munlockall)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_sched_setparam)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 154, enableExcept: false) */
	b .
END(libc_sys_sched_setparam)
DEFINE_PUBLIC_ALIAS(sys_sched_setparam, libc_sys_sched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
INTERN_FUNCTION(libc_sys_sched_getparam)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 155, enableExcept: false) */
	b .
END(libc_sys_sched_getparam)
DEFINE_PUBLIC_ALIAS(sys_sched_getparam, libc_sys_sched_getparam)

/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_sched_setscheduler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 156, enableExcept: false) */
	b .
END(libc_sys_sched_setscheduler)
DEFINE_PUBLIC_ALIAS(sys_sched_setscheduler, libc_sys_sched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
INTERN_FUNCTION(libc_sys_sched_getscheduler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 157, enableExcept: false) */
	b .
END(libc_sys_sched_getscheduler)
DEFINE_PUBLIC_ALIAS(sys_sched_getscheduler, libc_sys_sched_getscheduler)

/* errno_t sched_yield(void) */
INTERN_FUNCTION(libc_sys_sched_yield)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 158, enableExcept: false) */
	b .
END(libc_sys_sched_yield)
DEFINE_PUBLIC_ALIAS(sys_sched_yield, libc_sys_sched_yield)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_sched_get_priority_max)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 159, enableExcept: false) */
	b .
END(libc_sys_sched_get_priority_max)
DEFINE_PUBLIC_ALIAS(sys_sched_get_priority_max, libc_sys_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_sched_get_priority_min)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 160, enableExcept: false) */
	b .
END(libc_sys_sched_get_priority_min)
DEFINE_PUBLIC_ALIAS(sys_sched_get_priority_min, libc_sys_sched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct timespec32 *ts) */
INTERN_FUNCTION(libc_sys_sched_rr_get_interval)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 161, enableExcept: false) */
	b .
END(libc_sys_sched_rr_get_interval)
DEFINE_PUBLIC_ALIAS(sys_sched_rr_get_interval, libc_sys_sched_rr_get_interval)

/* errno_t nanosleep(struct timespec32 const *req, struct timespec32 *rem) */
INTERN_FUNCTION(libc_sys_nanosleep)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 162, enableExcept: false) */
	b .
END(libc_sys_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_nanosleep, libc_sys_nanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
INTERN_FUNCTION(libc_sys_mremap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 163, enableExcept: false) */
	b .
END(libc_sys_mremap)
DEFINE_PUBLIC_ALIAS(sys_mremap, libc_sys_mremap)

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
INTERN_FUNCTION(libc_sys_setresuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 164, enableExcept: false) */
	b .
END(libc_sys_setresuid)
DEFINE_PUBLIC_ALIAS(sys_setresuid, libc_sys_setresuid)

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
INTERN_FUNCTION(libc_sys_getresuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 165, enableExcept: false) */
	b .
END(libc_sys_getresuid)
DEFINE_PUBLIC_ALIAS(sys_getresuid, libc_sys_getresuid)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_poll)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 168, enableExcept: false) */
	b .
END(libc_sys_poll)
DEFINE_PUBLIC_ALIAS(sys_poll, libc_sys_poll)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_nfsservctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 169, enableExcept: false) */
	b .
END(libc_sys_nfsservctl)
DEFINE_PUBLIC_ALIAS(sys_nfsservctl, libc_sys_nfsservctl)

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
INTERN_FUNCTION(libc_sys_setresgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 170, enableExcept: false) */
	b .
END(libc_sys_setresgid)
DEFINE_PUBLIC_ALIAS(sys_setresgid, libc_sys_setresgid)

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
INTERN_FUNCTION(libc_sys_getresgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 171, enableExcept: false) */
	b .
END(libc_sys_getresgid)
DEFINE_PUBLIC_ALIAS(sys_getresgid, libc_sys_getresgid)

/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
/* syscall_slong_t prctl(unsigned int command, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5) */
INTERN_FUNCTION(libc_sys_prctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 172, enableExcept: false) */
	b .
END(libc_sys_prctl)
DEFINE_PUBLIC_ALIAS(sys_prctl, libc_sys_prctl)

/* void rt_sigreturn(void) */
INTERN_FUNCTION(libc_sys_rt_sigreturn)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 173, enableExcept: false) */
	b .
END(libc_sys_rt_sigreturn)
DEFINE_PUBLIC_ALIAS(sys_rt_sigreturn, libc_sys_rt_sigreturn)

/* errno_t rt_sigaction(signo_t signo, struct __kernel_sigaction const *act, struct __kernel_sigaction *oact, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigaction)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 174, enableExcept: false) */
	b .
END(libc_sys_rt_sigaction)
DEFINE_PUBLIC_ALIAS(sys_rt_sigaction, libc_sys_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigprocmask)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 175, enableExcept: false) */
	b .
END(libc_sys_rt_sigprocmask)
DEFINE_PUBLIC_ALIAS(sys_rt_sigprocmask, libc_sys_rt_sigprocmask)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigpending)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 176, enableExcept: false) */
	b .
END(libc_sys_rt_sigpending)
DEFINE_PUBLIC_ALIAS(sys_rt_sigpending, libc_sys_rt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec32 const *timeout, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigtimedwait)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 177, enableExcept: false) */
	b .
END(libc_sys_rt_sigtimedwait)
DEFINE_PUBLIC_ALIAS(sys_rt_sigtimedwait, libc_sys_rt_sigtimedwait)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_rt_sigqueueinfo)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 178, enableExcept: false) */
	b .
END(libc_sys_rt_sigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_rt_sigqueueinfo, libc_sys_rt_sigqueueinfo)

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigsuspend)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 179, enableExcept: false) */
	b .
END(libc_sys_rt_sigsuspend)
DEFINE_PUBLIC_ALIAS(sys_rt_sigsuspend, libc_sys_rt_sigsuspend)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_pread64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 180, enableExcept: false) */
	b .
END(libc_sys_pread64)
DEFINE_PUBLIC_ALIAS(sys_pread64, libc_sys_pread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_pwrite64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 181, enableExcept: false) */
	b .
END(libc_sys_pwrite64)
DEFINE_PUBLIC_ALIAS(sys_pwrite64, libc_sys_pwrite64)

/* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
INTERN_FUNCTION(libc_sys_chown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 182, enableExcept: false) */
	b .
END(libc_sys_chown)
DEFINE_PUBLIC_ALIAS(sys_chown, libc_sys_chown)

/* ssize_t getcwd(char *buf, size_t size) */
INTERN_FUNCTION(libc_sys_getcwd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 183, enableExcept: false) */
	b .
END(libc_sys_getcwd)
DEFINE_PUBLIC_ALIAS(sys_getcwd, libc_sys_getcwd)

/* errno_t capget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_capget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 184, enableExcept: false) */
	b .
END(libc_sys_capget)
DEFINE_PUBLIC_ALIAS(sys_capget, libc_sys_capget)

/* errno_t capset(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_capset)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 185, enableExcept: false) */
	b .
END(libc_sys_capset)
DEFINE_PUBLIC_ALIAS(sys_capset, libc_sys_capset)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
INTERN_FUNCTION(libc_sys_sigaltstack)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 186, enableExcept: false) */
	b .
END(libc_sys_sigaltstack)
DEFINE_PUBLIC_ALIAS(sys_sigaltstack, libc_sys_sigaltstack)

/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
/* ssize_t sendfile(fd_t outfd, fd_t infd, syscall_ulong_t *pin_offset, size_t num_bytes) */
INTERN_FUNCTION(libc_sys_sendfile)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 187, enableExcept: false) */
	b .
END(libc_sys_sendfile)
DEFINE_PUBLIC_ALIAS(sys_sendfile, libc_sys_sendfile)

/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will  only be resumed in case  the
 *                     new  program image could  be loaded successfully. Otherwise,
 *                     the call  to  `execve(2)'  returns normally  in  the  child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
/* pid_t vfork(void) */
INTERN_FUNCTION(libc_sys_vfork)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 190, enableExcept: false) */
	b .
END(libc_sys_vfork)
DEFINE_PUBLIC_ALIAS(sys_vfork, libc_sys_vfork)

/* errno_t ugetrlimit(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_ugetrlimit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 191, enableExcept: false) */
	b .
END(libc_sys_ugetrlimit)
DEFINE_PUBLIC_ALIAS(sys_ugetrlimit, libc_sys_ugetrlimit)

/* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
INTERN_FUNCTION(libc_sys_mmap2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 192, enableExcept: false) */
	b .
END(libc_sys_mmap2)
DEFINE_PUBLIC_ALIAS(sys_mmap2, libc_sys_mmap2)

/* errno_t truncate64(char const *filename, uint64_t length) */
INTERN_FUNCTION(libc_sys_truncate64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 193, enableExcept: false) */
	b .
END(libc_sys_truncate64)
DEFINE_PUBLIC_ALIAS(sys_truncate64, libc_sys_truncate64)

/* errno_t ftruncate64(fd_t fd, uint64_t length) */
INTERN_FUNCTION(libc_sys_ftruncate64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 194, enableExcept: false) */
	b .
END(libc_sys_ftruncate64)
DEFINE_PUBLIC_ALIAS(sys_ftruncate64, libc_sys_ftruncate64)

/* errno_t stat64(char const *filename, struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_stat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 195, enableExcept: false) */
	b .
END(libc_sys_stat64)
DEFINE_PUBLIC_ALIAS(sys_stat64, libc_sys_stat64)

/* errno_t lstat64(char const *filename, struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_lstat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 196, enableExcept: false) */
	b .
END(libc_sys_lstat64)
DEFINE_PUBLIC_ALIAS(sys_lstat64, libc_sys_lstat64)

/* errno_t fstat64(fd_t fd, struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_fstat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 197, enableExcept: false) */
	b .
END(libc_sys_fstat64)
DEFINE_PUBLIC_ALIAS(sys_fstat64, libc_sys_fstat64)

/* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
INTERN_FUNCTION(libc_sys_lchown32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 198, enableExcept: false) */
	b .
END(libc_sys_lchown32)
DEFINE_PUBLIC_ALIAS(sys_lchown32, libc_sys_lchown32)

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uint32_t getuid32(void) */
INTERN_FUNCTION(libc_sys_getuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 199, enableExcept: false) */
	b .
END(libc_sys_getuid32)
DEFINE_PUBLIC_ALIAS(sys_getuid32, libc_sys_getuid32)

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* uint32_t getgid32(void) */
INTERN_FUNCTION(libc_sys_getgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 200, enableExcept: false) */
	b .
END(libc_sys_getgid32)
DEFINE_PUBLIC_ALIAS(sys_getgid32, libc_sys_getgid32)

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint32_t geteuid32(void) */
INTERN_FUNCTION(libc_sys_geteuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 201, enableExcept: false) */
	b .
END(libc_sys_geteuid32)
DEFINE_PUBLIC_ALIAS(sys_geteuid32, libc_sys_geteuid32)

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint32_t getegid32(void) */
INTERN_FUNCTION(libc_sys_getegid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 202, enableExcept: false) */
	b .
END(libc_sys_getegid32)
DEFINE_PUBLIC_ALIAS(sys_getegid32, libc_sys_getegid32)

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
INTERN_FUNCTION(libc_sys_setreuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 203, enableExcept: false) */
	b .
END(libc_sys_setreuid32)
DEFINE_PUBLIC_ALIAS(sys_setreuid32, libc_sys_setreuid32)

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid32(uint32_t rgid, uint32_t egid) */
INTERN_FUNCTION(libc_sys_setregid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 204, enableExcept: false) */
	b .
END(libc_sys_setregid32)
DEFINE_PUBLIC_ALIAS(sys_setregid32, libc_sys_setregid32)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups32(size_t count, uint32_t[] list) */
INTERN_FUNCTION(libc_sys_getgroups32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 205, enableExcept: false) */
	b .
END(libc_sys_getgroups32)
DEFINE_PUBLIC_ALIAS(sys_getgroups32, libc_sys_getgroups32)

/* errno_t setgroups32(size_t count, uint32_t const *groups) */
INTERN_FUNCTION(libc_sys_setgroups32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 206, enableExcept: false) */
	b .
END(libc_sys_setgroups32)
DEFINE_PUBLIC_ALIAS(sys_setgroups32, libc_sys_setgroups32)

/* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
INTERN_FUNCTION(libc_sys_fchown32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 207, enableExcept: false) */
	b .
END(libc_sys_fchown32)
DEFINE_PUBLIC_ALIAS(sys_fchown32, libc_sys_fchown32)

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
INTERN_FUNCTION(libc_sys_setresuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 208, enableExcept: false) */
	b .
END(libc_sys_setresuid32)
DEFINE_PUBLIC_ALIAS(sys_setresuid32, libc_sys_setresuid32)

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
INTERN_FUNCTION(libc_sys_getresuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 209, enableExcept: false) */
	b .
END(libc_sys_getresuid32)
DEFINE_PUBLIC_ALIAS(sys_getresuid32, libc_sys_getresuid32)

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
INTERN_FUNCTION(libc_sys_setresgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 210, enableExcept: false) */
	b .
END(libc_sys_setresgid32)
DEFINE_PUBLIC_ALIAS(sys_setresgid32, libc_sys_setresgid32)

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
INTERN_FUNCTION(libc_sys_getresgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 211, enableExcept: false) */
	b .
END(libc_sys_getresgid32)
DEFINE_PUBLIC_ALIAS(sys_getresgid32, libc_sys_getresgid32)

/* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
INTERN_FUNCTION(libc_sys_chown32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 212, enableExcept: false) */
	b .
END(libc_sys_chown32)
DEFINE_PUBLIC_ALIAS(sys_chown32, libc_sys_chown32)

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_setuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 213, enableExcept: false) */
	b .
END(libc_sys_setuid32)
DEFINE_PUBLIC_ALIAS(sys_setuid32, libc_sys_setuid32)

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_setgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 214, enableExcept: false) */
	b .
END(libc_sys_setgid32)
DEFINE_PUBLIC_ALIAS(sys_setgid32, libc_sys_setgid32)

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_setfsuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 215, enableExcept: false) */
	b .
END(libc_sys_setfsuid32)
DEFINE_PUBLIC_ALIAS(sys_setfsuid32, libc_sys_setfsuid32)

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_setfsgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 216, enableExcept: false) */
	b .
END(libc_sys_setfsgid32)
DEFINE_PUBLIC_ALIAS(sys_setfsgid32, libc_sys_setfsgid32)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_getdents64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 217, enableExcept: false) */
	b .
END(libc_sys_getdents64)
DEFINE_PUBLIC_ALIAS(sys_getdents64, libc_sys_getdents64)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_pivot_root)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 218, enableExcept: false) */
	b .
END(libc_sys_pivot_root)
DEFINE_PUBLIC_ALIAS(sys_pivot_root, libc_sys_pivot_root)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
INTERN_FUNCTION(libc_sys_mincore)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 219, enableExcept: false) */
	b .
END(libc_sys_mincore)
DEFINE_PUBLIC_ALIAS(sys_mincore, libc_sys_mincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
INTERN_FUNCTION(libc_sys_madvise)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 220, enableExcept: false) */
	b .
END(libc_sys_madvise)
DEFINE_PUBLIC_ALIAS(sys_madvise, libc_sys_madvise)

/* syscall_slong_t fcntl64(fd_t fd, fcntl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_fcntl64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 221, enableExcept: false) */
	b .
END(libc_sys_fcntl64)
DEFINE_PUBLIC_ALIAS(sys_fcntl64, libc_sys_fcntl64)

/* pid_t gettid(void) */
INTERN_FUNCTION(libc_sys_gettid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 224, enableExcept: false) */
	b .
END(libc_sys_gettid)
DEFINE_PUBLIC_ALIAS(sys_gettid, libc_sys_gettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
INTERN_FUNCTION(libc_sys_readahead)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 225, enableExcept: false) */
	b .
END(libc_sys_readahead)
DEFINE_PUBLIC_ALIAS(sys_readahead, libc_sys_readahead)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_setxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 226, enableExcept: false) */
	b .
END(libc_sys_setxattr)
DEFINE_PUBLIC_ALIAS(sys_setxattr, libc_sys_setxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_lsetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 227, enableExcept: false) */
	b .
END(libc_sys_lsetxattr)
DEFINE_PUBLIC_ALIAS(sys_lsetxattr, libc_sys_lsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_fsetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 228, enableExcept: false) */
	b .
END(libc_sys_fsetxattr)
DEFINE_PUBLIC_ALIAS(sys_fsetxattr, libc_sys_fsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_getxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 229, enableExcept: false) */
	b .
END(libc_sys_getxattr)
DEFINE_PUBLIC_ALIAS(sys_getxattr, libc_sys_getxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_lgetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 230, enableExcept: false) */
	b .
END(libc_sys_lgetxattr)
DEFINE_PUBLIC_ALIAS(sys_lgetxattr, libc_sys_lgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_fgetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 231, enableExcept: false) */
	b .
END(libc_sys_fgetxattr)
DEFINE_PUBLIC_ALIAS(sys_fgetxattr, libc_sys_fgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_listxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 232, enableExcept: false) */
	b .
END(libc_sys_listxattr)
DEFINE_PUBLIC_ALIAS(sys_listxattr, libc_sys_listxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_llistxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 233, enableExcept: false) */
	b .
END(libc_sys_llistxattr)
DEFINE_PUBLIC_ALIAS(sys_llistxattr, libc_sys_llistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_flistxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 234, enableExcept: false) */
	b .
END(libc_sys_flistxattr)
DEFINE_PUBLIC_ALIAS(sys_flistxattr, libc_sys_flistxattr)

/* errno_t removexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_removexattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 235, enableExcept: false) */
	b .
END(libc_sys_removexattr)
DEFINE_PUBLIC_ALIAS(sys_removexattr, libc_sys_removexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_lremovexattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 236, enableExcept: false) */
	b .
END(libc_sys_lremovexattr)
DEFINE_PUBLIC_ALIAS(sys_lremovexattr, libc_sys_lremovexattr)

/* errno_t fremovexattr(fd_t fd, char const *name) */
INTERN_FUNCTION(libc_sys_fremovexattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 237, enableExcept: false) */
	b .
END(libc_sys_fremovexattr)
DEFINE_PUBLIC_ALIAS(sys_fremovexattr, libc_sys_fremovexattr)

/* errno_t tkill(pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_tkill)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 238, enableExcept: false) */
	b .
END(libc_sys_tkill)
DEFINE_PUBLIC_ALIAS(sys_tkill, libc_sys_tkill)

/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
/* ssize_t sendfile64(fd_t outfd, fd_t infd, __ULONG64_TYPE__ *pin_offset, size_t num_bytes) */
INTERN_FUNCTION(libc_sys_sendfile64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 239, enableExcept: false) */
	b .
END(libc_sys_sendfile64)
DEFINE_PUBLIC_ALIAS(sys_sendfile64, libc_sys_sendfile64)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
INTERN_FUNCTION(libc_sys_futex)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 240, enableExcept: false) */
	b .
END(libc_sys_futex)
DEFINE_PUBLIC_ALIAS(sys_futex, libc_sys_futex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
INTERN_FUNCTION(libc_sys_sched_setaffinity)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 241, enableExcept: false) */
	b .
END(libc_sys_sched_setaffinity)
DEFINE_PUBLIC_ALIAS(sys_sched_setaffinity, libc_sys_sched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
INTERN_FUNCTION(libc_sys_sched_getaffinity)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 242, enableExcept: false) */
	b .
END(libc_sys_sched_getaffinity)
DEFINE_PUBLIC_ALIAS(sys_sched_getaffinity, libc_sys_sched_getaffinity)

/* errno_t io_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_setup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 243, enableExcept: false) */
	b .
END(libc_sys_io_setup)
DEFINE_PUBLIC_ALIAS(sys_io_setup, libc_sys_io_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_destroy)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 244, enableExcept: false) */
	b .
END(libc_sys_io_destroy)
DEFINE_PUBLIC_ALIAS(sys_io_destroy, libc_sys_io_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_getevents)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 245, enableExcept: false) */
	b .
END(libc_sys_io_getevents)
DEFINE_PUBLIC_ALIAS(sys_io_getevents, libc_sys_io_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_submit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 246, enableExcept: false) */
	b .
END(libc_sys_io_submit)
DEFINE_PUBLIC_ALIAS(sys_io_submit, libc_sys_io_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_cancel)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 247, enableExcept: false) */
	b .
END(libc_sys_io_cancel)
DEFINE_PUBLIC_ALIAS(sys_io_cancel, libc_sys_io_cancel)

/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit_group(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_exit_group)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 248, enableExcept: false) */
	b .
END(libc_sys_exit_group)
DEFINE_PUBLIC_ALIAS(sys_exit_group, libc_sys_exit_group)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_lookup_dcookie)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 249, enableExcept: false) */
	b .
END(libc_sys_lookup_dcookie)
DEFINE_PUBLIC_ALIAS(sys_lookup_dcookie, libc_sys_lookup_dcookie)

/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
/* fd_t epoll_create(syscall_ulong_t size) */
INTERN_FUNCTION(libc_sys_epoll_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 250, enableExcept: false) */
	b .
END(libc_sys_epoll_create)
DEFINE_PUBLIC_ALIAS(sys_epoll_create, libc_sys_epoll_create)

/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
INTERN_FUNCTION(libc_sys_epoll_ctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 251, enableExcept: false) */
	b .
END(libc_sys_epoll_ctl)
DEFINE_PUBLIC_ALIAS(sys_epoll_ctl, libc_sys_epoll_ctl)

/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_wait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_epoll_wait)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 252, enableExcept: false) */
	b .
END(libc_sys_epoll_wait)
DEFINE_PUBLIC_ALIAS(sys_epoll_wait, libc_sys_epoll_wait)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_remap_file_pages)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 253, enableExcept: false) */
	b .
END(libc_sys_remap_file_pages)
DEFINE_PUBLIC_ALIAS(sys_remap_file_pages, libc_sys_remap_file_pages)

/* pid_t set_tid_address(pid_t *tidptr) */
INTERN_FUNCTION(libc_sys_set_tid_address)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 256, enableExcept: false) */
	b .
END(libc_sys_set_tid_address)
DEFINE_PUBLIC_ALIAS(sys_set_tid_address, libc_sys_set_tid_address)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
INTERN_FUNCTION(libc_sys_timer_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 257, enableExcept: false) */
	b .
END(libc_sys_timer_create)
DEFINE_PUBLIC_ALIAS(sys_timer_create, libc_sys_timer_create)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspec32 const *value, struct itimerspec32 *ovalue) */
INTERN_FUNCTION(libc_sys_timer_settime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 258, enableExcept: false) */
	b .
END(libc_sys_timer_settime)
DEFINE_PUBLIC_ALIAS(sys_timer_settime, libc_sys_timer_settime)

/* errno_t timer_gettime(timer_t timerid, struct itimerspec32 *value) */
INTERN_FUNCTION(libc_sys_timer_gettime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 259, enableExcept: false) */
	b .
END(libc_sys_timer_gettime)
DEFINE_PUBLIC_ALIAS(sys_timer_gettime, libc_sys_timer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
INTERN_FUNCTION(libc_sys_timer_getoverrun)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 260, enableExcept: false) */
	b .
END(libc_sys_timer_getoverrun)
DEFINE_PUBLIC_ALIAS(sys_timer_getoverrun, libc_sys_timer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
INTERN_FUNCTION(libc_sys_timer_delete)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 261, enableExcept: false) */
	b .
END(libc_sys_timer_delete)
DEFINE_PUBLIC_ALIAS(sys_timer_delete, libc_sys_timer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct timespec32 const *tp) */
INTERN_FUNCTION(libc_sys_clock_settime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 262, enableExcept: false) */
	b .
END(libc_sys_clock_settime)
DEFINE_PUBLIC_ALIAS(sys_clock_settime, libc_sys_clock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct timespec32 *tp) */
INTERN_FUNCTION(libc_sys_clock_gettime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 263, enableExcept: false) */
	b .
END(libc_sys_clock_gettime)
DEFINE_PUBLIC_ALIAS(sys_clock_gettime, libc_sys_clock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct timespec32 *res) */
INTERN_FUNCTION(libc_sys_clock_getres)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 264, enableExcept: false) */
	b .
END(libc_sys_clock_getres)
DEFINE_PUBLIC_ALIAS(sys_clock_getres, libc_sys_clock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespec32 const *requested_time, struct timespec32 *remaining) */
INTERN_FUNCTION(libc_sys_clock_nanosleep)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 265, enableExcept: false) */
	b .
END(libc_sys_clock_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_clock_nanosleep, libc_sys_clock_nanosleep)

/* errno_t statfs64(char const *file, struct __statfs64 *buf) */
INTERN_FUNCTION(libc_sys_statfs64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 266, enableExcept: false) */
	b .
END(libc_sys_statfs64)
DEFINE_PUBLIC_ALIAS(sys_statfs64, libc_sys_statfs64)

/* errno_t fstatfs64(fd_t file, struct __statfs64 *buf) */
INTERN_FUNCTION(libc_sys_fstatfs64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 267, enableExcept: false) */
	b .
END(libc_sys_fstatfs64)
DEFINE_PUBLIC_ALIAS(sys_fstatfs64, libc_sys_fstatfs64)

/* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_tgkill)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 268, enableExcept: false) */
	b .
END(libc_sys_tgkill)
DEFINE_PUBLIC_ALIAS(sys_tgkill, libc_sys_tgkill)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes(char const *filename, struct timeval32 const[2] times) */
INTERN_FUNCTION(libc_sys_utimes)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 269, enableExcept: false) */
	b .
END(libc_sys_utimes)
DEFINE_PUBLIC_ALIAS(sys_utimes, libc_sys_utimes)

/* errno_t arm_fadvise64_64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_arm_fadvise64_64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 270, enableExcept: false) */
	b .
END(libc_sys_arm_fadvise64_64)
DEFINE_PUBLIC_ALIAS(sys_arm_fadvise64_64, libc_sys_arm_fadvise64_64)

/* errno_t pciconfig_iobase(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_pciconfig_iobase)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 271, enableExcept: false) */
	b .
END(libc_sys_pciconfig_iobase)
DEFINE_PUBLIC_ALIAS(sys_pciconfig_iobase, libc_sys_pciconfig_iobase)

/* errno_t pciconfig_read(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_pciconfig_read)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 272, enableExcept: false) */
	b .
END(libc_sys_pciconfig_read)
DEFINE_PUBLIC_ALIAS(sys_pciconfig_read, libc_sys_pciconfig_read)

/* errno_t pciconfig_write(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_pciconfig_write)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 273, enableExcept: false) */
	b .
END(libc_sys_pciconfig_write)
DEFINE_PUBLIC_ALIAS(sys_pciconfig_write, libc_sys_pciconfig_write)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_mq_open)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 274, enableExcept: false) */
	b .
END(libc_sys_mq_open)
DEFINE_PUBLIC_ALIAS(sys_mq_open, libc_sys_mq_open)

/* errno_t mq_unlink(char const *name) */
INTERN_FUNCTION(libc_sys_mq_unlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 275, enableExcept: false) */
	b .
END(libc_sys_mq_unlink)
DEFINE_PUBLIC_ALIAS(sys_mq_unlink, libc_sys_mq_unlink)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec32 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_mq_timedsend)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 276, enableExcept: false) */
	b .
END(libc_sys_mq_timedsend)
DEFINE_PUBLIC_ALIAS(sys_mq_timedsend, libc_sys_mq_timedsend)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec32 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_mq_timedreceive)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 277, enableExcept: false) */
	b .
END(libc_sys_mq_timedreceive)
DEFINE_PUBLIC_ALIAS(sys_mq_timedreceive, libc_sys_mq_timedreceive)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
INTERN_FUNCTION(libc_sys_mq_notify)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 278, enableExcept: false) */
	b .
END(libc_sys_mq_notify)
DEFINE_PUBLIC_ALIAS(sys_mq_notify, libc_sys_mq_notify)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
INTERN_FUNCTION(libc_sys_mq_getsetattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 279, enableExcept: false) */
	b .
END(libc_sys_mq_getsetattr)
DEFINE_PUBLIC_ALIAS(sys_mq_getsetattr, libc_sys_mq_getsetattr)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
INTERN_FUNCTION(libc_sys_waitid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 280, enableExcept: false) */
	b .
END(libc_sys_waitid)
DEFINE_PUBLIC_ALIAS(sys_waitid, libc_sys_waitid)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
INTERN_FUNCTION(libc_sys_socket)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 281, enableExcept: false) */
	b .
END(libc_sys_socket)
DEFINE_PUBLIC_ALIAS(sys_socket, libc_sys_socket)

/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_bind)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 282, enableExcept: false) */
	b .
END(libc_sys_bind)
DEFINE_PUBLIC_ALIAS(sys_bind, libc_sys_bind)

/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_connect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 283, enableExcept: false) */
	b .
END(libc_sys_connect)
DEFINE_PUBLIC_ALIAS(sys_connect, libc_sys_connect)

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
INTERN_FUNCTION(libc_sys_listen)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 284, enableExcept: false) */
	b .
END(libc_sys_listen)
DEFINE_PUBLIC_ALIAS(sys_listen, libc_sys_listen)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_accept)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 285, enableExcept: false) */
	b .
END(libc_sys_accept)
DEFINE_PUBLIC_ALIAS(sys_accept, libc_sys_accept)

/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success */
/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_getsockname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 286, enableExcept: false) */
	b .
END(libc_sys_getsockname)
DEFINE_PUBLIC_ALIAS(sys_getsockname, libc_sys_getsockname)

/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_getpeername)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 287, enableExcept: false) */
	b .
END(libc_sys_getpeername)
DEFINE_PUBLIC_ALIAS(sys_getpeername, libc_sys_getpeername)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
INTERN_FUNCTION(libc_sys_socketpair)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 288, enableExcept: false) */
	b .
END(libc_sys_socketpair)
DEFINE_PUBLIC_ALIAS(sys_socketpair, libc_sys_socketpair)

/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t send(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_send)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 289, enableExcept: false) */
	b .
END(libc_sys_send)
DEFINE_PUBLIC_ALIAS(sys_send, libc_sys_send)

/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_sendto)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 290, enableExcept: false) */
	b .
END(libc_sys_sendto)
DEFINE_PUBLIC_ALIAS(sys_sendto, libc_sys_sendto)

/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recv(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_recv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 291, enableExcept: false) */
	b .
END(libc_sys_recv)
DEFINE_PUBLIC_ALIAS(sys_recv, libc_sys_recv)

/* Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_recvfrom)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 292, enableExcept: false) */
	b .
END(libc_sys_recvfrom)
DEFINE_PUBLIC_ALIAS(sys_recvfrom, libc_sys_recvfrom)

/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_shutdown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 293, enableExcept: false) */
	b .
END(libc_sys_shutdown)
DEFINE_PUBLIC_ALIAS(sys_shutdown, libc_sys_shutdown)

/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
INTERN_FUNCTION(libc_sys_setsockopt)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 294, enableExcept: false) */
	b .
END(libc_sys_setsockopt)
DEFINE_PUBLIC_ALIAS(sys_setsockopt, libc_sys_setsockopt)

/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
INTERN_FUNCTION(libc_sys_getsockopt)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 295, enableExcept: false) */
	b .
END(libc_sys_getsockopt)
DEFINE_PUBLIC_ALIAS(sys_getsockopt, libc_sys_getsockopt)

/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_sendmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 296, enableExcept: false) */
	b .
END(libc_sys_sendmsg)
DEFINE_PUBLIC_ALIAS(sys_sendmsg, libc_sys_sendmsg)

/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_recvmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 297, enableExcept: false) */
	b .
END(libc_sys_recvmsg)
DEFINE_PUBLIC_ALIAS(sys_recvmsg, libc_sys_recvmsg)

/* errno_t semop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semop)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 298, enableExcept: false) */
	b .
END(libc_sys_semop)
DEFINE_PUBLIC_ALIAS(sys_semop, libc_sys_semop)

/* errno_t semget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 299, enableExcept: false) */
	b .
END(libc_sys_semget)
DEFINE_PUBLIC_ALIAS(sys_semget, libc_sys_semget)

/* errno_t semctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 300, enableExcept: false) */
	b .
END(libc_sys_semctl)
DEFINE_PUBLIC_ALIAS(sys_semctl, libc_sys_semctl)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgsnd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 301, enableExcept: false) */
	b .
END(libc_sys_msgsnd)
DEFINE_PUBLIC_ALIAS(sys_msgsnd, libc_sys_msgsnd)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgrcv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 302, enableExcept: false) */
	b .
END(libc_sys_msgrcv)
DEFINE_PUBLIC_ALIAS(sys_msgrcv, libc_sys_msgrcv)

/* errno_t msgget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 303, enableExcept: false) */
	b .
END(libc_sys_msgget)
DEFINE_PUBLIC_ALIAS(sys_msgget, libc_sys_msgget)

/* errno_t msgctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_msgctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 304, enableExcept: false) */
	b .
END(libc_sys_msgctl)
DEFINE_PUBLIC_ALIAS(sys_msgctl, libc_sys_msgctl)

/* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_shmat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 305, enableExcept: false) */
	b .
END(libc_sys_shmat)
DEFINE_PUBLIC_ALIAS(sys_shmat, libc_sys_shmat)

/* errno_t shmdt(void const *shmaddr) */
INTERN_FUNCTION(libc_sys_shmdt)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 306, enableExcept: false) */
	b .
END(libc_sys_shmdt)
DEFINE_PUBLIC_ALIAS(sys_shmdt, libc_sys_shmdt)

/* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_shmget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 307, enableExcept: false) */
	b .
END(libc_sys_shmget)
DEFINE_PUBLIC_ALIAS(sys_shmget, libc_sys_shmget)

/* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
INTERN_FUNCTION(libc_sys_shmctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 308, enableExcept: false) */
	b .
END(libc_sys_shmctl)
DEFINE_PUBLIC_ALIAS(sys_shmctl, libc_sys_shmctl)

/* errno_t add_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_add_key)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 309, enableExcept: false) */
	b .
END(libc_sys_add_key)
DEFINE_PUBLIC_ALIAS(sys_add_key, libc_sys_add_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_request_key)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 310, enableExcept: false) */
	b .
END(libc_sys_request_key)
DEFINE_PUBLIC_ALIAS(sys_request_key, libc_sys_request_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_keyctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 311, enableExcept: false) */
	b .
END(libc_sys_keyctl)
DEFINE_PUBLIC_ALIAS(sys_keyctl, libc_sys_keyctl)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semtimedop)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 312, enableExcept: false) */
	b .
END(libc_sys_semtimedop)
DEFINE_PUBLIC_ALIAS(sys_semtimedop, libc_sys_semtimedop)

/* errno_t vserve(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_vserve)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 313, enableExcept: false) */
	b .
END(libc_sys_vserve)
DEFINE_PUBLIC_ALIAS(sys_vserve, libc_sys_vserve)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
INTERN_FUNCTION(libc_sys_ioprio_set)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 314, enableExcept: false) */
	b .
END(libc_sys_ioprio_set)
DEFINE_PUBLIC_ALIAS(sys_ioprio_set, libc_sys_ioprio_set)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
INTERN_FUNCTION(libc_sys_ioprio_get)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 315, enableExcept: false) */
	b .
END(libc_sys_ioprio_get)
DEFINE_PUBLIC_ALIAS(sys_ioprio_get, libc_sys_ioprio_get)

/* fd_t inotify_init(void) */
INTERN_FUNCTION(libc_sys_inotify_init)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 316, enableExcept: false) */
	b .
END(libc_sys_inotify_init)
DEFINE_PUBLIC_ALIAS(sys_inotify_init, libc_sys_inotify_init)

/* @param: mask: Set of `IN_ALL_EVENTS | ...' */
/* int inotify_add_watch(fd_t notify_fd, char const *pathname, uint32_t mask) */
INTERN_FUNCTION(libc_sys_inotify_add_watch)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 317, enableExcept: false) */
	b .
END(libc_sys_inotify_add_watch)
DEFINE_PUBLIC_ALIAS(sys_inotify_add_watch, libc_sys_inotify_add_watch)

/* @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
/* errno_t inotify_rm_watch(fd_t notify_fd, int wd) */
INTERN_FUNCTION(libc_sys_inotify_rm_watch)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 318, enableExcept: false) */
	b .
END(libc_sys_inotify_rm_watch)
DEFINE_PUBLIC_ALIAS(sys_inotify_rm_watch, libc_sys_inotify_rm_watch)

/* errno_t mbind(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_mbind)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 319, enableExcept: false) */
	b .
END(libc_sys_mbind)
DEFINE_PUBLIC_ALIAS(sys_mbind, libc_sys_mbind)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_get_mempolicy)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 320, enableExcept: false) */
	b .
END(libc_sys_get_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_get_mempolicy, libc_sys_get_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_set_mempolicy)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 321, enableExcept: false) */
	b .
END(libc_sys_set_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_set_mempolicy, libc_sys_set_mempolicy)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_openat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 322, enableExcept: false) */
	b .
END(libc_sys_openat)
DEFINE_PUBLIC_ALIAS(sys_openat, libc_sys_openat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_mkdirat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 323, enableExcept: false) */
	b .
END(libc_sys_mkdirat)
DEFINE_PUBLIC_ALIAS(sys_mkdirat, libc_sys_mkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_mknodat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 324, enableExcept: false) */
	b .
END(libc_sys_mknodat)
DEFINE_PUBLIC_ALIAS(sys_mknodat, libc_sys_mknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchownat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 325, enableExcept: false) */
	b .
END(libc_sys_fchownat)
DEFINE_PUBLIC_ALIAS(sys_fchownat, libc_sys_fchownat)

/* errno_t futimesat(fd_t dirfd, char const *filename, struct timeval32 const[2] times) */
INTERN_FUNCTION(libc_sys_futimesat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 326, enableExcept: false) */
	b .
END(libc_sys_futimesat)
DEFINE_PUBLIC_ALIAS(sys_futimesat, libc_sys_futimesat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fstatat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 327, enableExcept: false) */
	b .
END(libc_sys_fstatat64)
DEFINE_PUBLIC_ALIAS(sys_fstatat64, libc_sys_fstatat64)

/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
INTERN_FUNCTION(libc_sys_unlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 328, enableExcept: false) */
	b .
END(libc_sys_unlinkat)
DEFINE_PUBLIC_ALIAS(sys_unlinkat, libc_sys_unlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_renameat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 329, enableExcept: false) */
	b .
END(libc_sys_renameat)
DEFINE_PUBLIC_ALIAS(sys_renameat, libc_sys_renameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_linkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 330, enableExcept: false) */
	b .
END(libc_sys_linkat)
DEFINE_PUBLIC_ALIAS(sys_linkat, libc_sys_linkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
INTERN_FUNCTION(libc_sys_symlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 331, enableExcept: false) */
	b .
END(libc_sys_symlinkat)
DEFINE_PUBLIC_ALIAS(sys_symlinkat, libc_sys_symlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_readlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 332, enableExcept: false) */
	b .
END(libc_sys_readlinkat)
DEFINE_PUBLIC_ALIAS(sys_readlinkat, libc_sys_readlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchmodat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 333, enableExcept: false) */
	b .
END(libc_sys_fchmodat)
DEFINE_PUBLIC_ALIAS(sys_fchmodat, libc_sys_fchmodat)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_faccessat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 334, enableExcept: false) */
	b .
END(libc_sys_faccessat)
DEFINE_PUBLIC_ALIAS(sys_faccessat, libc_sys_faccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec32 const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
INTERN_FUNCTION(libc_sys_pselect6)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 335, enableExcept: false) */
	b .
END(libc_sys_pselect6)
DEFINE_PUBLIC_ALIAS(sys_pselect6, libc_sys_pselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_ppoll)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 336, enableExcept: false) */
	b .
END(libc_sys_ppoll)
DEFINE_PUBLIC_ALIAS(sys_ppoll, libc_sys_ppoll)

/* param: what: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t what) */
INTERN_FUNCTION(libc_sys_unshare)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 337, enableExcept: false) */
	b .
END(libc_sys_unshare)
DEFINE_PUBLIC_ALIAS(sys_unshare, libc_sys_unshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_set_robust_list)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 338, enableExcept: false) */
	b .
END(libc_sys_set_robust_list)
DEFINE_PUBLIC_ALIAS(sys_set_robust_list, libc_sys_set_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_get_robust_list)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 339, enableExcept: false) */
	b .
END(libc_sys_get_robust_list)
DEFINE_PUBLIC_ALIAS(sys_get_robust_list, libc_sys_get_robust_list)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_splice)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 340, enableExcept: false) */
	b .
END(libc_sys_splice)
DEFINE_PUBLIC_ALIAS(sys_splice, libc_sys_splice)

/* errno_t arm_sync_file_range(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_arm_sync_file_range)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 341, enableExcept: false) */
	b .
END(libc_sys_arm_sync_file_range)
DEFINE_PUBLIC_ALIAS(sys_arm_sync_file_range, libc_sys_arm_sync_file_range)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_tee)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 342, enableExcept: false) */
	b .
END(libc_sys_tee)
DEFINE_PUBLIC_ALIAS(sys_tee, libc_sys_tee)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_vmsplice)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 343, enableExcept: false) */
	b .
END(libc_sys_vmsplice)
DEFINE_PUBLIC_ALIAS(sys_vmsplice, libc_sys_vmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_move_pages)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 344, enableExcept: false) */
	b .
END(libc_sys_move_pages)
DEFINE_PUBLIC_ALIAS(sys_move_pages, libc_sys_move_pages)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
INTERN_FUNCTION(libc_sys_getcpu)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 345, enableExcept: false) */
	b .
END(libc_sys_getcpu)
DEFINE_PUBLIC_ALIAS(sys_getcpu, libc_sys_getcpu)

/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_pwait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_epoll_pwait)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 346, enableExcept: false) */
	b .
END(libc_sys_epoll_pwait)
DEFINE_PUBLIC_ALIAS(sys_epoll_pwait, libc_sys_epoll_pwait)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_kexec_load)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 347, enableExcept: false) */
	b .
END(libc_sys_kexec_load)
DEFINE_PUBLIC_ALIAS(sys_kexec_load, libc_sys_kexec_load)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct timespec32 const[2] times, atflag_t flags) */
INTERN_FUNCTION(libc_sys_utimensat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 348, enableExcept: false) */
	b .
END(libc_sys_utimensat)
DEFINE_PUBLIC_ALIAS(sys_utimensat, libc_sys_utimensat)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
INTERN_FUNCTION(libc_sys_signalfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 349, enableExcept: false) */
	b .
END(libc_sys_signalfd)
DEFINE_PUBLIC_ALIAS(sys_signalfd, libc_sys_signalfd)

/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_timerfd_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 350, enableExcept: false) */
	b .
END(libc_sys_timerfd_create)
DEFINE_PUBLIC_ALIAS(sys_timerfd_create, libc_sys_timerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
INTERN_FUNCTION(libc_sys_eventfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 351, enableExcept: false) */
	b .
END(libc_sys_eventfd)
DEFINE_PUBLIC_ALIAS(sys_eventfd, libc_sys_eventfd)

/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_fallocate)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 352, enableExcept: false) */
	b .
END(libc_sys_fallocate)
DEFINE_PUBLIC_ALIAS(sys_fallocate, libc_sys_fallocate)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspec32 const *utmr, struct itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_settime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 353, enableExcept: false) */
	b .
END(libc_sys_timerfd_settime)
DEFINE_PUBLIC_ALIAS(sys_timerfd_settime, libc_sys_timerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t timerfd, struct itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_gettime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 354, enableExcept: false) */
	b .
END(libc_sys_timerfd_gettime)
DEFINE_PUBLIC_ALIAS(sys_timerfd_gettime, libc_sys_timerfd_gettime)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_signalfd4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 355, enableExcept: false) */
	b .
END(libc_sys_signalfd4)
DEFINE_PUBLIC_ALIAS(sys_signalfd4, libc_sys_signalfd4)

/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_eventfd2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 356, enableExcept: false) */
	b .
END(libc_sys_eventfd2)
DEFINE_PUBLIC_ALIAS(sys_eventfd2, libc_sys_eventfd2)

/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
/* fd_t epoll_create1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_epoll_create1)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 357, enableExcept: false) */
	b .
END(libc_sys_epoll_create1)
DEFINE_PUBLIC_ALIAS(sys_epoll_create1, libc_sys_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
INTERN_FUNCTION(libc_sys_dup3)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 358, enableExcept: false) */
	b .
END(libc_sys_dup3)
DEFINE_PUBLIC_ALIAS(sys_dup3, libc_sys_dup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
INTERN_FUNCTION(libc_sys_pipe2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 359, enableExcept: false) */
	b .
END(libc_sys_pipe2)
DEFINE_PUBLIC_ALIAS(sys_pipe2, libc_sys_pipe2)

/* @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
/* fd_t inotify_init1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_inotify_init1)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 360, enableExcept: false) */
	b .
END(libc_sys_inotify_init1)
DEFINE_PUBLIC_ALIAS(sys_inotify_init1, libc_sys_inotify_init1)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_preadv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 361, enableExcept: false) */
	b .
END(libc_sys_preadv)
DEFINE_PUBLIC_ALIAS(sys_preadv, libc_sys_preadv)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_pwritev)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 362, enableExcept: false) */
	b .
END(libc_sys_pwritev)
DEFINE_PUBLIC_ALIAS(sys_pwritev, libc_sys_pwritev)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_rt_tgsigqueueinfo)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 363, enableExcept: false) */
	b .
END(libc_sys_rt_tgsigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_rt_tgsigqueueinfo, libc_sys_rt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_perf_event_open)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 364, enableExcept: false) */
	b .
END(libc_sys_perf_event_open)
DEFINE_PUBLIC_ALIAS(sys_perf_event_open, libc_sys_perf_event_open)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr32 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec32 const *tmo) */
INTERN_FUNCTION(libc_sys_recvmmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 365, enableExcept: false) */
	b .
END(libc_sys_recvmmsg)
DEFINE_PUBLIC_ALIAS(sys_recvmmsg, libc_sys_recvmmsg)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
INTERN_FUNCTION(libc_sys_accept4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 366, enableExcept: false) */
	b .
END(libc_sys_accept4)
DEFINE_PUBLIC_ALIAS(sys_accept4, libc_sys_accept4)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fanotify_init)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 367, enableExcept: false) */
	b .
END(libc_sys_fanotify_init)
DEFINE_PUBLIC_ALIAS(sys_fanotify_init, libc_sys_fanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fanotify_mark)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 368, enableExcept: false) */
	b .
END(libc_sys_fanotify_mark)
DEFINE_PUBLIC_ALIAS(sys_fanotify_mark, libc_sys_fanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
INTERN_FUNCTION(libc_sys_prlimit64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 369, enableExcept: false) */
	b .
END(libc_sys_prlimit64)
DEFINE_PUBLIC_ALIAS(sys_prlimit64, libc_sys_prlimit64)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
INTERN_FUNCTION(libc_sys_name_to_handle_at)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 370, enableExcept: false) */
	b .
END(libc_sys_name_to_handle_at)
DEFINE_PUBLIC_ALIAS(sys_name_to_handle_at, libc_sys_name_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
INTERN_FUNCTION(libc_sys_open_by_handle_at)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 371, enableExcept: false) */
	b .
END(libc_sys_open_by_handle_at)
DEFINE_PUBLIC_ALIAS(sys_open_by_handle_at, libc_sys_open_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_clock_adjtime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 372, enableExcept: false) */
	b .
END(libc_sys_clock_adjtime)
DEFINE_PUBLIC_ALIAS(sys_clock_adjtime, libc_sys_clock_adjtime)

/* errno_t syncfs(fd_t fd) */
INTERN_FUNCTION(libc_sys_syncfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 373, enableExcept: false) */
	b .
END(libc_sys_syncfs)
DEFINE_PUBLIC_ALIAS(sys_syncfs, libc_sys_syncfs)

/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_sendmmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 374, enableExcept: false) */
	b .
END(libc_sys_sendmmsg)
DEFINE_PUBLIC_ALIAS(sys_sendmmsg, libc_sys_sendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
INTERN_FUNCTION(libc_sys_setns)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 375, enableExcept: false) */
	b .
END(libc_sys_setns)
DEFINE_PUBLIC_ALIAS(sys_setns, libc_sys_setns)

/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
/* ssize_t process_vm_readv(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_process_vm_readv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 376, enableExcept: false) */
	b .
END(libc_sys_process_vm_readv)
DEFINE_PUBLIC_ALIAS(sys_process_vm_readv, libc_sys_process_vm_readv)

/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
/* ssize_t process_vm_writev(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_process_vm_writev)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 377, enableExcept: false) */
	b .
END(libc_sys_process_vm_writev)
DEFINE_PUBLIC_ALIAS(sys_process_vm_writev, libc_sys_process_vm_writev)

/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
INTERN_FUNCTION(libc_sys_kcmp)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 378, enableExcept: false) */
	b .
END(libc_sys_kcmp)
DEFINE_PUBLIC_ALIAS(sys_kcmp, libc_sys_kcmp)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_finit_module)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 379, enableExcept: false) */
	b .
END(libc_sys_finit_module)
DEFINE_PUBLIC_ALIAS(sys_finit_module, libc_sys_finit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_sched_setattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 380, enableExcept: false) */
	b .
END(libc_sys_sched_setattr)
DEFINE_PUBLIC_ALIAS(sys_sched_setattr, libc_sys_sched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_sched_getattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 381, enableExcept: false) */
	b .
END(libc_sys_sched_getattr)
DEFINE_PUBLIC_ALIAS(sys_sched_getattr, libc_sys_sched_getattr)

/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
INTERN_FUNCTION(libc_sys_renameat2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 382, enableExcept: false) */
	b .
END(libc_sys_renameat2)
DEFINE_PUBLIC_ALIAS(sys_renameat2, libc_sys_renameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_seccomp)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 383, enableExcept: false) */
	b .
END(libc_sys_seccomp)
DEFINE_PUBLIC_ALIAS(sys_seccomp, libc_sys_seccomp)

/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
/* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_getrandom)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 384, enableExcept: false) */
	b .
END(libc_sys_getrandom)
DEFINE_PUBLIC_ALIAS(sys_getrandom, libc_sys_getrandom)

/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
/* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_memfd_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 385, enableExcept: false) */
	b .
END(libc_sys_memfd_create)
DEFINE_PUBLIC_ALIAS(sys_memfd_create, libc_sys_memfd_create)

/* errno_t bpf(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_bpf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 386, enableExcept: false) */
	b .
END(libc_sys_bpf)
DEFINE_PUBLIC_ALIAS(sys_bpf, libc_sys_bpf)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
INTERN_FUNCTION(libc_sys_execveat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 387, enableExcept: false) */
	b .
END(libc_sys_execveat)
DEFINE_PUBLIC_ALIAS(sys_execveat, libc_sys_execveat)

/* fd_t userfaultfd(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_userfaultfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 388, enableExcept: false) */
	b .
END(libc_sys_userfaultfd)
DEFINE_PUBLIC_ALIAS(sys_userfaultfd, libc_sys_userfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_membarrier)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 389, enableExcept: false) */
	b .
END(libc_sys_membarrier)
DEFINE_PUBLIC_ALIAS(sys_membarrier, libc_sys_membarrier)

/* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_mlock2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 390, enableExcept: false) */
	b .
END(libc_sys_mlock2)
DEFINE_PUBLIC_ALIAS(sys_mlock2, libc_sys_mlock2)

/* errno_t copy_file_range(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_copy_file_range)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 391, enableExcept: false) */
	b .
END(libc_sys_copy_file_range)
DEFINE_PUBLIC_ALIAS(sys_copy_file_range, libc_sys_copy_file_range)

/* errno_t preadv2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_preadv2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 392, enableExcept: false) */
	b .
END(libc_sys_preadv2)
DEFINE_PUBLIC_ALIAS(sys_preadv2, libc_sys_preadv2)

/* errno_t pwritev2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_pwritev2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 393, enableExcept: false) */
	b .
END(libc_sys_pwritev2)
DEFINE_PUBLIC_ALIAS(sys_pwritev2, libc_sys_pwritev2)

/* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
INTERN_FUNCTION(libc_sys_pkey_mprotect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 394, enableExcept: false) */
	b .
END(libc_sys_pkey_mprotect)
DEFINE_PUBLIC_ALIAS(sys_pkey_mprotect, libc_sys_pkey_mprotect)

/* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
INTERN_FUNCTION(libc_sys_pkey_alloc)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 395, enableExcept: false) */
	b .
END(libc_sys_pkey_alloc)
DEFINE_PUBLIC_ALIAS(sys_pkey_alloc, libc_sys_pkey_alloc)

/* errno_t pkey_free(syscall_ulong_t key) */
INTERN_FUNCTION(libc_sys_pkey_free)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 396, enableExcept: false) */
	b .
END(libc_sys_pkey_free)
DEFINE_PUBLIC_ALIAS(sys_pkey_free, libc_sys_pkey_free)

/* errno_t statx(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_statx)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 397, enableExcept: false) */
	b .
END(libc_sys_statx)
DEFINE_PUBLIC_ALIAS(sys_statx, libc_sys_statx)

/* errno_t rseq(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_rseq)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 398, enableExcept: false) */
	b .
END(libc_sys_rseq)
DEFINE_PUBLIC_ALIAS(sys_rseq, libc_sys_rseq)

/* errno_t io_pgetevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_pgetevents)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 399, enableExcept: false) */
	b .
END(libc_sys_io_pgetevents)
DEFINE_PUBLIC_ALIAS(sys_io_pgetevents, libc_sys_io_pgetevents)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_migrate_pages)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 400, enableExcept: false) */
	b .
END(libc_sys_migrate_pages)
DEFINE_PUBLIC_ALIAS(sys_migrate_pages, libc_sys_migrate_pages)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_kexec_file_load)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 401, enableExcept: false) */
	b .
END(libc_sys_kexec_file_load)
DEFINE_PUBLIC_ALIAS(sys_kexec_file_load, libc_sys_kexec_file_load)

/* errno_t clock_gettime64(clockid_t clock_id, struct timespec64 *tp) */
INTERN_FUNCTION(libc_sys_clock_gettime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 403, enableExcept: false) */
	b .
END(libc_sys_clock_gettime64)
DEFINE_PUBLIC_ALIAS(sys_clock_gettime64, libc_sys_clock_gettime64)

/* errno_t clock_settime64(clockid_t clock_id, struct timespec64 const *tp) */
INTERN_FUNCTION(libc_sys_clock_settime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 404, enableExcept: false) */
	b .
END(libc_sys_clock_settime64)
DEFINE_PUBLIC_ALIAS(sys_clock_settime64, libc_sys_clock_settime64)

/* errno_t clock_adjtime64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_clock_adjtime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 405, enableExcept: false) */
	b .
END(libc_sys_clock_adjtime64)
DEFINE_PUBLIC_ALIAS(sys_clock_adjtime64, libc_sys_clock_adjtime64)

/* errno_t clock_getres_time64(clockid_t clock_id, struct timespec64 *res) */
INTERN_FUNCTION(libc_sys_clock_getres_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 406, enableExcept: false) */
	b .
END(libc_sys_clock_getres_time64)
DEFINE_PUBLIC_ALIAS(sys_clock_getres_time64, libc_sys_clock_getres_time64)

/* errno_t clock_nanosleep_time64(clockid_t clock_id, syscall_ulong_t flags, struct timespec64 const *requested_time, struct timespec64 *remaining) */
INTERN_FUNCTION(libc_sys_clock_nanosleep_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 407, enableExcept: false) */
	b .
END(libc_sys_clock_nanosleep_time64)
DEFINE_PUBLIC_ALIAS(sys_clock_nanosleep_time64, libc_sys_clock_nanosleep_time64)

/* errno_t timer_gettime64(timer_t timerid, struct itimerspec64 *value) */
INTERN_FUNCTION(libc_sys_timer_gettime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 408, enableExcept: false) */
	b .
END(libc_sys_timer_gettime64)
DEFINE_PUBLIC_ALIAS(sys_timer_gettime64, libc_sys_timer_gettime64)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct itimerspec64 const *value, struct itimerspec64 *ovalue) */
INTERN_FUNCTION(libc_sys_timer_settime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 409, enableExcept: false) */
	b .
END(libc_sys_timer_settime64)
DEFINE_PUBLIC_ALIAS(sys_timer_settime64, libc_sys_timer_settime64)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime64(fd_t timerfd, struct itimerspec64 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_gettime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 410, enableExcept: false) */
	b .
END(libc_sys_timerfd_gettime64)
DEFINE_PUBLIC_ALIAS(sys_timerfd_gettime64, libc_sys_timerfd_gettime64)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime64(fd_t timerfd, syscall_ulong_t flags, struct itimerspec64 const *utmr, struct itimerspec64 *otmr) */
INTERN_FUNCTION(libc_sys_timerfd_settime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 411, enableExcept: false) */
	b .
END(libc_sys_timerfd_settime64)
DEFINE_PUBLIC_ALIAS(sys_timerfd_settime64, libc_sys_timerfd_settime64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat_time64(fd_t dirfd, char const *filename, struct timespec64 const[2] times, atflag_t flags) */
INTERN_FUNCTION(libc_sys_utimensat_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 412, enableExcept: false) */
	b .
END(libc_sys_utimensat_time64)
DEFINE_PUBLIC_ALIAS(sys_utimensat_time64, libc_sys_utimensat_time64)

/* ssize_t pselect6_time64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec64 const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
INTERN_FUNCTION(libc_sys_pselect6_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 413, enableExcept: false) */
	b .
END(libc_sys_pselect6_time64)
DEFINE_PUBLIC_ALIAS(sys_pselect6_time64, libc_sys_pselect6_time64)

/* ssize_t ppoll_time64(struct pollfd *fds, size_t nfds, struct timespec64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_ppoll_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 414, enableExcept: false) */
	b .
END(libc_sys_ppoll_time64)
DEFINE_PUBLIC_ALIAS(sys_ppoll_time64, libc_sys_ppoll_time64)

/* errno_t io_pgetevents_time64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_pgetevents_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 416, enableExcept: false) */
	b .
END(libc_sys_io_pgetevents_time64)
DEFINE_PUBLIC_ALIAS(sys_io_pgetevents_time64, libc_sys_io_pgetevents_time64)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg_time64(fd_t sockfd, struct mmsghdr64 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec64 const *tmo) */
INTERN_FUNCTION(libc_sys_recvmmsg_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 417, enableExcept: false) */
	b .
END(libc_sys_recvmmsg_time64)
DEFINE_PUBLIC_ALIAS(sys_recvmmsg_time64, libc_sys_recvmmsg_time64)

/* errno_t mq_timedsend_time64(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_mq_timedsend_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 418, enableExcept: false) */
	b .
END(libc_sys_mq_timedsend_time64)
DEFINE_PUBLIC_ALIAS(sys_mq_timedsend_time64, libc_sys_mq_timedsend_time64)

/* ssize_t mq_timedreceive_time64(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_mq_timedreceive_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 419, enableExcept: false) */
	b .
END(libc_sys_mq_timedreceive_time64)
DEFINE_PUBLIC_ALIAS(sys_mq_timedreceive_time64, libc_sys_mq_timedreceive_time64)

/* errno_t semtimedop_time64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_semtimedop_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 420, enableExcept: false) */
	b .
END(libc_sys_semtimedop_time64)
DEFINE_PUBLIC_ALIAS(sys_semtimedop_time64, libc_sys_semtimedop_time64)

/* syscall_slong_t rt_sigtimedwait_time64(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec64 const *timeout, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_rt_sigtimedwait_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 421, enableExcept: false) */
	b .
END(libc_sys_rt_sigtimedwait_time64)
DEFINE_PUBLIC_ALIAS(sys_rt_sigtimedwait_time64, libc_sys_rt_sigtimedwait_time64)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex_time64(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
INTERN_FUNCTION(libc_sys_futex_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 422, enableExcept: false) */
	b .
END(libc_sys_futex_time64)
DEFINE_PUBLIC_ALIAS(sys_futex_time64, libc_sys_futex_time64)

/* errno_t sched_rr_get_interval_time64(pid_t pid, struct timespec64 *ts) */
INTERN_FUNCTION(libc_sys_sched_rr_get_interval_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 423, enableExcept: false) */
	b .
END(libc_sys_sched_rr_get_interval_time64)
DEFINE_PUBLIC_ALIAS(sys_sched_rr_get_interval_time64, libc_sys_sched_rr_get_interval_time64)

/* Send a signal to the process of a given pidfd
 * @param: pidfd:  A `HANDLE_TYPE_PIDFD'-handle
 * @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @param: flags:  Must always be `0' (for now)
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO:    [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:                 [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:     [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfo_struct const *uinfo, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_pidfd_send_signal)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 424, enableExcept: false) */
	b .
END(libc_sys_pidfd_send_signal)
DEFINE_PUBLIC_ALIAS(sys_pidfd_send_signal, libc_sys_pidfd_send_signal)

/* errno_t io_uring_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_uring_setup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 425, enableExcept: false) */
	b .
END(libc_sys_io_uring_setup)
DEFINE_PUBLIC_ALIAS(sys_io_uring_setup, libc_sys_io_uring_setup)

/* errno_t io_uring_enter(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_uring_enter)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 426, enableExcept: false) */
	b .
END(libc_sys_io_uring_enter)
DEFINE_PUBLIC_ALIAS(sys_io_uring_enter, libc_sys_io_uring_enter)

/* errno_t io_uring_register(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_io_uring_register)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 427, enableExcept: false) */
	b .
END(libc_sys_io_uring_register)
DEFINE_PUBLIC_ALIAS(sys_io_uring_register, libc_sys_io_uring_register)

/* errno_t open_tree(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_open_tree)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 428, enableExcept: false) */
	b .
END(libc_sys_open_tree)
DEFINE_PUBLIC_ALIAS(sys_open_tree, libc_sys_open_tree)

/* errno_t move_mount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_move_mount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 429, enableExcept: false) */
	b .
END(libc_sys_move_mount)
DEFINE_PUBLIC_ALIAS(sys_move_mount, libc_sys_move_mount)

/* errno_t fsopen(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fsopen)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 430, enableExcept: false) */
	b .
END(libc_sys_fsopen)
DEFINE_PUBLIC_ALIAS(sys_fsopen, libc_sys_fsopen)

/* errno_t fsconfig(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fsconfig)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 431, enableExcept: false) */
	b .
END(libc_sys_fsconfig)
DEFINE_PUBLIC_ALIAS(sys_fsconfig, libc_sys_fsconfig)

/* errno_t fsmount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fsmount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 432, enableExcept: false) */
	b .
END(libc_sys_fsmount)
DEFINE_PUBLIC_ALIAS(sys_fsmount, libc_sys_fsmount)

/* errno_t fspick(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_fspick)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 433, enableExcept: false) */
	b .
END(libc_sys_fspick)
DEFINE_PUBLIC_ALIAS(sys_fspick, libc_sys_fspick)

/* Return a `HANDLE_TYPE_PIDFD' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not  allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
/* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_pidfd_open)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 434, enableExcept: false) */
	b .
END(libc_sys_pidfd_open)
DEFINE_PUBLIC_ALIAS(sys_pidfd_open, libc_sys_pidfd_open)

/* syscall_slong_t clone3(struct clone_args *cl_args, size_t size) */
INTERN_FUNCTION(libc_sys_clone3)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 435, enableExcept: false) */
	b .
END(libc_sys_clone3)
DEFINE_PUBLIC_ALIAS(sys_clone3, libc_sys_clone3)

/* @param: flags: Set of `CLOSE_RANGE_*' from <linux/close_range.h> */
/* errno_t close_range(unsigned int minfd, unsigned int maxfd, unsigned int flags) */
INTERN_FUNCTION(libc_sys_close_range)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 436, enableExcept: false) */
	b .
END(libc_sys_close_range)
DEFINE_PUBLIC_ALIAS(sys_close_range, libc_sys_close_range)

/* errno_t openat2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_openat2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 437, enableExcept: false) */
	b .
END(libc_sys_openat2)
DEFINE_PUBLIC_ALIAS(sys_openat2, libc_sys_openat2)

/* Duplicate the  handle  of  a  foreign  process into  a  handle  for  the  caller.
 * This system call duplicates the functionality of `open("/proc/[pid]/fd/[fdno]")',
 * which may also be used to duplicate file handles from another process.
 * @param: pidfd: A `HANDLE_TYPE_PIDFD'-handle
 * @param: fd:    The FD-number of the handle to clone
 * @param: flags: Must always be `0' (for now)
 * @return: * :   The duplicated handle number
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                            [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_pidfd_getfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 438, enableExcept: false) */
	b .
END(libc_sys_pidfd_getfd)
DEFINE_PUBLIC_ALIAS(sys_pidfd_getfd, libc_sys_pidfd_getfd)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat2(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
INTERN_FUNCTION(libc_sys_faccessat2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 439, enableExcept: false) */
	b .
END(libc_sys_faccessat2)
DEFINE_PUBLIC_ALIAS(sys_faccessat2, libc_sys_faccessat2)

/* errno_t process_madvise(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_process_madvise)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 440, enableExcept: false) */
	b .
END(libc_sys_process_madvise)
DEFINE_PUBLIC_ALIAS(sys_process_madvise, libc_sys_process_madvise)

/* Trigger a breakpoint */
/* void breakpoint(void) */
INTERN_FUNCTION(libc_sys_breakpoint)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983041, enableExcept: false) */
	b .
END(libc_sys_breakpoint)
DEFINE_PUBLIC_ALIAS(sys_breakpoint, libc_sys_breakpoint)

/* Flush instruction cache */
/* errno_t cacheflush(void const *start, void const *end, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_cacheflush)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983042, enableExcept: false) */
	b .
END(libc_sys_cacheflush)
DEFINE_PUBLIC_ALIAS(sys_cacheflush, libc_sys_cacheflush)

/* Clear CPSR.T=0x10 */
/* void usr26(void) */
INTERN_FUNCTION(libc_sys_usr26)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983043, enableExcept: false) */
	b .
END(libc_sys_usr26)
DEFINE_PUBLIC_ALIAS(sys_usr26, libc_sys_usr26)

/* Set CPSR.T=0x10 */
/* void usr32(void) */
INTERN_FUNCTION(libc_sys_usr32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983044, enableExcept: false) */
	b .
END(libc_sys_usr32)
DEFINE_PUBLIC_ALIAS(sys_usr32, libc_sys_usr32)

/* Set calling thread's TLS pointer */
/* errno_t set_tls(void const *tlsval) */
INTERN_FUNCTION(libc_sys_set_tls)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983045, enableExcept: false) */
	b .
END(libc_sys_set_tls)
DEFINE_PUBLIC_ALIAS(sys_set_tls, libc_sys_set_tls)

/* Get calling thread's TLS pointer */
/* void *get_tls(void) */
INTERN_FUNCTION(libc_sys_get_tls)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983046, enableExcept: false) */
	b .
END(libc_sys_get_tls)
DEFINE_PUBLIC_ALIAS(sys_get_tls, libc_sys_get_tls)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_readf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323075, enableExcept: false) */
	b .
END(libc_sys_readf)
DEFINE_PUBLIC_ALIAS(sys_readf, libc_sys_readf)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_writef)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323076, enableExcept: false) */
	b .
END(libc_sys_writef)
DEFINE_PUBLIC_ALIAS(sys_writef, libc_sys_writef)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
INTERN_FUNCTION(libc_sys_getdrives)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323077, enableExcept: false) */
	b .
END(libc_sys_getdrives)
DEFINE_PUBLIC_ALIAS(sys_getdrives, libc_sys_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_frealpath4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323078, enableExcept: false) */
	b .
END(libc_sys_frealpath4)
DEFINE_PUBLIC_ALIAS(sys_frealpath4, libc_sys_frealpath4)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the  thread from turning into  a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling  thread from  the set of  running children  within
 *     its own process.  Note however  that when this  is done  by the  main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the  calling   process   the   same  way   a   double-fork   would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads  of the calling process,  essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * The given `pid' must be:
 *   - A thread without the caller's process
 *   - A child process of the caller's process
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had  already
 *       be called.
 * @return: -ECHILD:         `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED: No such  thread/process exists,  or  the thread  isn't  isn't
 *                           a thread in your process, or a child process of your process. */
/* errno_t detach(pid_t pid) */
INTERN_FUNCTION(libc_sys_detach)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323079, enableExcept: false) */
	b .
END(libc_sys_detach)
DEFINE_PUBLIC_ALIAS(sys_detach, libc_sys_detach)

/* Returns  the  absolute   filesystem  path  for   the  specified   file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is  dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_frealpathat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323080, enableExcept: false) */
	b .
END(libc_sys_frealpathat)
DEFINE_PUBLIC_ALIAS(sys_frealpathat, libc_sys_frealpathat)

/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread terminate before the  conditions for the RPC  to be served are  ever
 * met. Note that these  conditions depend on the  given `mode'. Note that  on
 * multi-arch  platforms (such as  x86), the register numbers,  as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 * 
 * NOTE: Only a cancellation point when `RPC_JOIN_WAITFOR' is used!
 * 
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of `RPC_PRIORITY_*',  optionally or'd  with
 *                          one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                          one of `RPC_JOIN_*'
 * @param: program:         The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:          RPC program parameters (for `RPC_OP_push_param')
 * @param: max_param_count: The max # of `params' used by `program'
 * 
 * @return: 0 :                Success
 * @throws: E_SEGFAULT:        Faulty pointers were given
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
 *                             The given `mode' is invalid.
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
 *                             The RPC program  contains illegal  instructions.
 *                             In this case, modifications made by instructions
 *                             encountered before the illegal one(s) will still
 *                             have  happened, meaning that the target thread's
 *                             state may have become inconsistent.
 * @throws: E_PROCESS_EXITED:  The target thread has already terminated, or
 *                             doesn't exist. Note  though that unless  the
 *                             thread  is  part  of your  own  process, are
 *                             still many reasons  outside of your  control
 *                             for why it  may terminate immediately  after
 *                             the RPC program finished. */
/* errno_t rpc_schedule(pid_t target_tid, syscall_ulong_t mode, void const *program, void const *const *params, size_t max_param_count) */
INTERN_FUNCTION(libc_sys_rpc_schedule)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323081, enableExcept: false) */
	b .
END(libc_sys_rpc_schedule)
DEFINE_PUBLIC_ALIAS(sys_rpc_schedule, libc_sys_rpc_schedule)

/* Create a new pseudo-terminal driver and store handles to both the
 * master  and slave ends  of the connection  in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
INTERN_FUNCTION(libc_sys_openpty)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323083, enableExcept: false) */
	b .
END(libc_sys_openpty)
DEFINE_PUBLIC_ALIAS(sys_openpty, libc_sys_openpty)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fchdirat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323084, enableExcept: false) */
	b .
END(libc_sys_fchdirat)
DEFINE_PUBLIC_ALIAS(sys_fchdirat, libc_sys_fchdirat)

/* time64_t time64(time64_t *timer) */
INTERN_FUNCTION(libc_sys_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323085, enableExcept: false) */
	b .
END(libc_sys_time64)
DEFINE_PUBLIC_ALIAS(sys_time64, libc_sys_time64)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The  newly created  device automatically gets  assigned an arbitrary  device number, before
 * being made available under a file `/dev/${name}'  (or rather: as ${name} within the  devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
INTERN_FUNCTION(libc_sys_mktty)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323086, enableExcept: false) */
	b .
END(libc_sys_mktty)
DEFINE_PUBLIC_ALIAS(sys_mktty, libc_sys_mktty)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   - Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND, NULL, NULL)'
 *   - Set mode #4 (as done by libc): `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND |
 *                                                           EXCEPT_HANDLER_FLAG_SETHANDLER,
 *                                                           &except_handler4, NULL)'
 * @param: mode:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: handler:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: handler_sp: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given `mode' is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
INTERN_FUNCTION(libc_sys_set_exception_handler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323087, enableExcept: false) */
	b .
END(libc_sys_set_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_set_exception_handler, libc_sys_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: pmode:       When non-`NULL', store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: phandler:    When   non-`NULL',   store  the   address   of  the   user-space   exception  handler.
 *                      Note that when no handler has been set (`!(*pmode & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: phandler_sp: When non-`NULL', store the starting address of the user-space exception handler stack.
 *                      Note that  when no  stack has  been set  (`!(*pmode & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-`NULL' and faulty */
/* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
INTERN_FUNCTION(libc_sys_get_exception_handler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323088, enableExcept: false) */
	b .
END(libc_sys_get_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_get_exception_handler, libc_sys_get_exception_handler)

/* Trigger a debugger trap `trapno', optionally extended with  `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to  the
 * given  `state', though given the purpose of this system call being
 * to inform a connected debugger  of some breakable event,  allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
INTERN_FUNCTION(libc_sys_debugtrap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323089, enableExcept: false) */
	b .
END(libc_sys_debugtrap)
DEFINE_PUBLIC_ALIAS(sys_debugtrap, libc_sys_debugtrap)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The  state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `reason' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When   `curr_state'   is   also   `NULL',   then   the   current   CPU   state   is   used   instead.
 * @param: traceback_vector: (potentially  incomplete)   vector  of   additional  program   pointers  that   were
 *                           traversed   when   the  stack   was   walked  from   `orig_state'   to  `curr_state'
 *                           Note that earlier  entries within this  vector are further  up the call-stack,  with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it  can  be  assumed  that  the  traceback is  complete  and  contains  all  traversed  instruction locations.
 *                           In   this   case,  a   traceback  displayed   to   a  human   should  not   include   the  text   location  at
 *                           `traceback_vector[traceback_length-1]',    since    that    location    would    also    be    printed    when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: reason:           The reason that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           For certain `unwind_error' values, this can also  point to other things, but is  always
 *                           allowed to be `NULL' to indicate default/stub values.
 * @param: unwind_error:     The  unwind  error that  caused the  coredump,  or `UNWIND_SUCCESS'  if unwinding
 *                           was  never  actually  performed,  and   `reason'  is  actually  a   `siginfo_t *'
 *                           Ignored when `reason == NULL', in which case `UNWIND_SUCCESS' is assumed instead. */
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, union coredump_info const *reason, syscall_ulong_t unwind_error) */
INTERN_FUNCTION(libc_sys_coredump)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323090, enableExcept: false) */
	b .
END(libc_sys_coredump)
DEFINE_PUBLIC_ALIAS(sys_coredump, libc_sys_coredump)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_lseek64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323091, enableExcept: false) */
	b .
END(libc_sys_lseek64)
DEFINE_PUBLIC_ALIAS(sys_lseek64, libc_sys_lseek64)

/* Construct   a   user-vio-fd  object   supporting  mmap(2),   with  actual
 * memory  accesses  being dispatched  by  adding them  as  pending requests
 * to an internal  queue that  should be read(2)  from by  a worker  thread,
 * which should then service those requests before responding by write(2)ing
 * the results of the operation back to the same fd.
 * HINT: The format of the structures that are read(2) and
 *       write(2)en can be found in `<libvio/userviofd.h>'
 * NOTE: Don't use this system call directly. Use `vio_create(3)'
 *       from `<libvio/vio.h>' instead.
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This  size may be  altered at a  later point in time
 *                       through use of `ftruncate(return)'
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK | O_NONBLOCK' */
/* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_userviofd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323092, enableExcept: false) */
	b .
END(libc_sys_userviofd)
DEFINE_PUBLIC_ALIAS(sys_userviofd, libc_sys_userviofd)

/* errno_t stime64(time64_t const *t) */
INTERN_FUNCTION(libc_sys_stime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323097, enableExcept: false) */
	b .
END(libc_sys_stime64)
DEFINE_PUBLIC_ALIAS(sys_stime64, libc_sys_stime64)

/* @param: times: When NULL, set the current time */
/* errno_t utime64(char const *filename, struct utimbuf64 const *times) */
INTERN_FUNCTION(libc_sys_utime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323102, enableExcept: false) */
	b .
END(libc_sys_utime64)
DEFINE_PUBLIC_ALIAS(sys_utime64, libc_sys_utime64)

/* errno_t ftime64(struct timeb64 *tp) */
INTERN_FUNCTION(libc_sys_ftime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323107, enableExcept: false) */
	b .
END(libc_sys_ftime64)
DEFINE_PUBLIC_ALIAS(sys_ftime64, libc_sys_ftime64)

/* Begin  an  RTM operation.  Note that  if  the arch-specific  RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM  operation is in progress,  only a very small  hand
 * full  of system calls are allowed to  be used. Attempting to use arbitrary
 * system calls will most likely  result in an `RTM_ABORT_FAILED' error,  and
 * attempting to access too much system memory in general will result in this
 * function returning  with  `RTM_ABORT_CAPACITY',  rather  than  succeeding.
 * The following is  a list  of system calls  which are  whitelisted for  use
 * during a transaction:
 *   - sys_rtm_begin:  Nested RTM operation
 *   - sys_rtm_end:    End an RTM operation
 *   - sys_rtm_abort:  Abort an RTM operation
 *   - sys_rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the RTM driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
/* rtm_status_t rtm_begin(void) */
INTERN_FUNCTION(libc_sys_rtm_begin)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323120, enableExcept: false) */
	b .
END(libc_sys_rtm_begin)
DEFINE_PUBLIC_ALIAS(sys_rtm_begin, libc_sys_rtm_begin)

/* End a transaction
 * If  the  transaction was  successful,  return normally  (by  returning `-EOK').
 * If    the   transaction   failed,   `sys_rtm_begin()'   returns   `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
/* errno_t rtm_end(void) */
INTERN_FUNCTION(libc_sys_rtm_end)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323121, enableExcept: false) */
	b .
END(libc_sys_rtm_end)
DEFINE_PUBLIC_ALIAS(sys_rtm_end, libc_sys_rtm_end)

/* Abort the current transaction  by having `sys_rtm_begin()' return  with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise,  this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
/* errno_t rtm_abort(syscall_ulong_t code) */
INTERN_FUNCTION(libc_sys_rtm_abort)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323122, enableExcept: false) */
	b .
END(libc_sys_rtm_abort)
DEFINE_PUBLIC_ALIAS(sys_rtm_abort, libc_sys_rtm_abort)

/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
/* syscall_ulong_t rtm_test(void) */
INTERN_FUNCTION(libc_sys_rtm_test)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323123, enableExcept: false) */
	b .
END(libc_sys_rtm_test)
DEFINE_PUBLIC_ALIAS(sys_rtm_test, libc_sys_rtm_test)

/* syscall_slong_t ioctlf(fd_t fd, ioctl_t command, iomode_t mode, void *arg) */
INTERN_FUNCTION(libc_sys_ioctlf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323126, enableExcept: false) */
	b .
END(libc_sys_ioctlf)
DEFINE_PUBLIC_ALIAS(sys_ioctlf, libc_sys_ioctlf)

/* uint64_t fsmode(uint64_t mode) */
INTERN_FUNCTION(libc_sys_fsmode)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323132, enableExcept: false) */
	b .
END(libc_sys_fsmode)
DEFINE_PUBLIC_ALIAS(sys_fsmode, libc_sys_fsmode)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage64(syscall_slong_t who, struct rusage64 *tv) */
INTERN_FUNCTION(libc_sys_getrusage64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323149, enableExcept: false) */
	b .
END(libc_sys_getrusage64)
DEFINE_PUBLIC_ALIAS(sys_getrusage64, libc_sys_getrusage64)

/* errno_t gettimeofday64(struct timeval64 *tv, struct timezone *tz) */
INTERN_FUNCTION(libc_sys_gettimeofday64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323150, enableExcept: false) */
	b .
END(libc_sys_gettimeofday64)
DEFINE_PUBLIC_ALIAS(sys_gettimeofday64, libc_sys_gettimeofday64)

/* errno_t settimeofday64(struct timeval64 const *tv, struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_settimeofday64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323151, enableExcept: false) */
	b .
END(libc_sys_settimeofday64)
DEFINE_PUBLIC_ALIAS(sys_settimeofday64, libc_sys_settimeofday64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN |
 *                MAP_GROWSUP  |  MAP_LOCKED  |  MAP_NORESERVE  |
 *                MAP_POPULATE  |  MAP_NONBLOCK   |  MAP_SYNC   |
 *                MAP_FIXED_NOREPLACE | MAP_NOASLR'
 * @param: fd:    A handle for the library file being mapped (must be mmap(2)-able)
 * @param: hdrv:  Pointer  to  a vector  of `Elf32_Phdr'  or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf32_phdr const *hdrv, size_t hdrc) */
INTERN_FUNCTION(libc_sys_maplibrary)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323158, enableExcept: false) */
	b .
END(libc_sys_maplibrary)
DEFINE_PUBLIC_ALIAS(sys_maplibrary, libc_sys_maplibrary)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
INTERN_FUNCTION(libc_sys_setitimer64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323176, enableExcept: false) */
	b .
END(libc_sys_setitimer64)
DEFINE_PUBLIC_ALIAS(sys_setitimer64, libc_sys_setitimer64)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
INTERN_FUNCTION(libc_sys_getitimer64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323177, enableExcept: false) */
	b .
END(libc_sys_getitimer64)
DEFINE_PUBLIC_ALIAS(sys_getitimer64, libc_sys_getitimer64)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4_64(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage64 *usage) */
INTERN_FUNCTION(libc_sys_wait4_64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323186, enableExcept: false) */
	b .
END(libc_sys_wait4_64)
DEFINE_PUBLIC_ALIAS(sys_wait4_64, libc_sys_wait4_64)

/* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval64 *timeout) */
INTERN_FUNCTION(libc_sys_select64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323214, enableExcept: false) */
	b .
END(libc_sys_select64)
DEFINE_PUBLIC_ALIAS(sys_select64, libc_sys_select64)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_readvf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323217, enableExcept: false) */
	b .
END(libc_sys_readvf)
DEFINE_PUBLIC_ALIAS(sys_readvf, libc_sys_readvf)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_writevf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323218, enableExcept: false) */
	b .
END(libc_sys_writevf)
DEFINE_PUBLIC_ALIAS(sys_writevf, libc_sys_writevf)

/* syscall_slong_t ksysctl(ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_ksysctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323221, enableExcept: false) */
	b .
END(libc_sys_ksysctl)
DEFINE_PUBLIC_ALIAS(sys_ksysctl, libc_sys_ksysctl)

/* >> rpc_serve(2)
 * Check for pending signals and RPCs. This is a wrapper around the
 * kernel `task_serve()' function, which is always invoked before a
 * thread begins waiting for a blocking operation. All system calls
 * marked as cancellation  points probably  call `task_serve()'  at
 * some point.
 * Note that unlike (say) `pause(2)', this function doesn't  block,
 * and may be used to implement `pthread_testcancel(3)' (should KOS
 * RPCs be used to facility pthread cancellation points, as done by
 * KOS's builtin libc)
 * @return: 0:      Nothing was handled.
 * @return: -EINTR: RPCs (or posix signals) were handled. */
/* errno_t rpc_serve(void) */
INTERN_FUNCTION(libc_sys_rpc_serve)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323230, enableExcept: false) */
	b .
END(libc_sys_rpc_serve)
DEFINE_PUBLIC_ALIAS(sys_rpc_serve, libc_sys_rpc_serve)

/* >> rpc_serve_sysret(2)
 * Very similar to `rpc_serve(2)', but with the addition that this one
 * will only serve RPCs that can be handled in `RPC_REASONCTX_SYSRET',
 * aka. `RPC_REASONCTX_ASYNC' contexts. Additionally, this system call
 * ignores the state of the  internal `TASK_FRPC' flag, and should  be
 * invoked  when  the calling  thread  makes use  of  the userprocmask
 * mechanism, and the  signal mask became  less restrictive while  the
 * `USERPROCMASK_FLAG_HASPENDING' flag was set.
 * 
 * When userprocmask is disabled, this system call is pretty much just
 * a no-op (semnatically speaking, it does nothing). But when enabled,
 * it is really only usable  in conjuction with the userprocmask.  The
 * exact usage can be seen in `chkuserprocmask(3)'.
 * 
 * @return: 0 : Always, unconditionally returned. */
/* errno_t rpc_serve_sysret(void) */
INTERN_FUNCTION(libc_sys_rpc_serve_sysret)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323231, enableExcept: false) */
	b .
END(libc_sys_rpc_serve_sysret)
DEFINE_PUBLIC_ALIAS(sys_rpc_serve_sysret, libc_sys_rpc_serve_sysret)

/* errno_t nanosleep64(struct timespec64 const *req, struct timespec64 *rem) */
INTERN_FUNCTION(libc_sys_nanosleep64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323234, enableExcept: false) */
	b .
END(libc_sys_nanosleep64)
DEFINE_PUBLIC_ALIAS(sys_nanosleep64, libc_sys_nanosleep64)

/* void ksigreturn(struct ucpustate const *restore_cpu, struct fpustate const *restore_fpu, struct sigset_with_size const *restore_sigmask, struct rpc_syscall_info const *restart_sc_info) */
INTERN_FUNCTION(libc_sys_ksigreturn)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323245, enableExcept: false) */
	b .
END(libc_sys_ksigreturn)
DEFINE_PUBLIC_ALIAS(sys_ksigreturn, libc_sys_ksigreturn)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_pread64f)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323252, enableExcept: false) */
	b .
END(libc_sys_pread64f)
DEFINE_PUBLIC_ALIAS(sys_pread64f, libc_sys_pread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_pwrite64f)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323253, enableExcept: false) */
	b .
END(libc_sys_pwrite64f)
DEFINE_PUBLIC_ALIAS(sys_pwrite64f, libc_sys_pwrite64f)

/* errno_t kstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_kstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323267, enableExcept: false) */
	b .
END(libc_sys_kstat)
DEFINE_PUBLIC_ALIAS(sys_kstat, libc_sys_kstat)

/* errno_t klstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_klstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323268, enableExcept: false) */
	b .
END(libc_sys_klstat)
DEFINE_PUBLIC_ALIAS(sys_klstat, libc_sys_klstat)

/* errno_t kfstat(fd_t fd, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_kfstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323269, enableExcept: false) */
	b .
END(libc_sys_kfstat)
DEFINE_PUBLIC_ALIAS(sys_kfstat, libc_sys_kfstat)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
INTERN_FUNCTION(libc_sys_kreaddir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323289, enableExcept: false) */
	b .
END(libc_sys_kreaddir)
DEFINE_PUBLIC_ALIAS(sys_kreaddir, libc_sys_kreaddir)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
INTERN_FUNCTION(libc_sys_kreaddirf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323290, enableExcept: false) */
	b .
END(libc_sys_kreaddirf)
DEFINE_PUBLIC_ALIAS(sys_kreaddirf, libc_sys_kreaddirf)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:                (lfutex_t *uaddr, LFUTEX_WAKE, size_t count)
 *    - LFUTEX_WAKEMASK:            (lfutex_t *uaddr, LFUTEX_WAKEMASK, size_t count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_WHILE:          (lfutex_t *uaddr, LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:          (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_UNTIL_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_ABOVE_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_BELOW_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct timespec64 const *timeout, uintptr_t val2) */
INTERN_FUNCTION(libc_sys_lfutex)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323312, enableExcept: false) */
	b .
END(libc_sys_lfutex)
DEFINE_PUBLIC_ALIAS(sys_lfutex, libc_sys_lfutex)

/* >> lfutexexpr(2)
 * The lfutexexpr(2) system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: futexaddr: The futex on which to wait
 * @param: base:      Base pointer added to the `fe_offset' fields of given expressions
 * @param: expr:      Vector of expressions for which to check, terminated by `LFUTEX_EXPREND'
 * @param: timeout:   Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 *                    When `LFUTEX_FDBIT'  is  set,  this argument  must  be  `NULL'.
 * @param: flags:     Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*' or `LFUTEX_FDBIT'
 * @return: * : The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *              to see their  possible return  values, which are  always `0'  when they  would
 *              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 *              When `LFUTEX_FDBIT' is set, the return value is an `fd_t' for a futex fd that
 *              can be used to poll for the specified `exprv'. Note that in this case `exprv'
 *              is limited to `LFUTEXFD_DEFAULT_MAXEXPR' (`/proc/kos/futexfd-maxexpr')
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(uintptr_t *futexaddr, void *base, struct lfutexexpr const *expr, struct timespec const *timeout, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_lfutexexpr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323313, enableExcept: false) */
	b .
END(libc_sys_lfutexexpr)
DEFINE_PUBLIC_ALIAS(sys_lfutexexpr, libc_sys_lfutexexpr)

/* Register the address of  the calling thread's userprocmask  controller.
 * This also  initializes `*ctl->pm_sigmask'  and `ctl->pm_pending',  such
 * that `*ctl->pm_sigmask' is filled with the current kernel-level  signal
 * mask, as would be returned by `sigprocmask(2)', while `ctl->pm_pending'
 * is filled in with the equivalent of `sigpending(2)'
 * Additionally,  the address  of `&ctl->pm_mytid'  is stored  as an override
 * for `set_tid_address(2)', and the kernel may read from `*ctl->pm_sigmask',
 * and write to `ctl->pm_pending' (using  atomic-or for the later) from  this
 * point forth.
 * NOTE: Before calling this function, the caller must:
 *       >> bzero(ctl, sizeof(struct userprocmask));
 *       >> ctl->pm_sigsize = sizeof(sigset_t);
 *       >> ctl->pm_sigmask = &initial_sigmask;
 *       Where the initial bzero() is needed to initialize potential
 *       additional,   arch-specific   fields    to   all    zeroes.
 * NOTE: This system call will then initialize:
 *       >> ctl->pm_mytid = gettid();
 *       >> sigprocmask(0, NULL, ctl->pm_sigmask);
 *       >> sigpending(&ctl->pm_pending);
 * NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
 *       before this is done, the kernel will copy the  `pm_sigmask'
 *       of the previously set  controller into its internal  signal
 *       mask. (i.e. the one used outside of userprocmask-mode)
 * Note though  that  `pm_sigmask'  is ignored  for  `SIGKILL'  and  `SIGSTOP'
 * Note also  that  this  function replaces  `set_tid_address(2)',  such  that
 * it negates a  prior call  to said  function, while  a future  call to  said
 * function will once again disable userprocmask, same as passing `NULL' would */
/* errno_t set_userprocmask_address(struct userprocmask *ctl) */
INTERN_FUNCTION(libc_sys_set_userprocmask_address)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323328, enableExcept: false) */
	b .
END(libc_sys_set_userprocmask_address)
DEFINE_PUBLIC_ALIAS(sys_set_userprocmask_address, libc_sys_set_userprocmask_address)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes64(char const *filename, struct timeval64 const[2] times) */
INTERN_FUNCTION(libc_sys_utimes64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323341, enableExcept: false) */
	b .
END(libc_sys_utimes64)
DEFINE_PUBLIC_ALIAS(sys_utimes64, libc_sys_utimes64)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid64(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage64 *ru) */
INTERN_FUNCTION(libc_sys_waitid64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323352, enableExcept: false) */
	b .
END(libc_sys_waitid64)
DEFINE_PUBLIC_ALIAS(sys_waitid64, libc_sys_waitid64)

/* @param: atflags: Set of `AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @param: mask:    Set of `IN_ALL_EVENTS | ...' */
/* int inotify_add_watch_at(fd_t notify_fd, fd_t dirfd, char const *pathname, atflag_t atflags, uint32_t mask) */
INTERN_FUNCTION(libc_sys_inotify_add_watch_at)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323389, enableExcept: false) */
	b .
END(libc_sys_inotify_add_watch_at)
DEFINE_PUBLIC_ALIAS(sys_inotify_add_watch_at, libc_sys_inotify_add_watch_at)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fmkdirat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323395, enableExcept: false) */
	b .
END(libc_sys_fmkdirat)
DEFINE_PUBLIC_ALIAS(sys_fmkdirat, libc_sys_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fmknodat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323396, enableExcept: false) */
	b .
END(libc_sys_fmknodat)
DEFINE_PUBLIC_ALIAS(sys_fmknodat, libc_sys_fmknodat)

/* errno_t futimesat64(fd_t dirfd, char const *filename, struct timeval64 const[2] times) */
INTERN_FUNCTION(libc_sys_futimesat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323398, enableExcept: false) */
	b .
END(libc_sys_futimesat64)
DEFINE_PUBLIC_ALIAS(sys_futimesat64, libc_sys_futimesat64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_kfstatat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323399, enableExcept: false) */
	b .
END(libc_sys_kfstatat)
DEFINE_PUBLIC_ALIAS(sys_kfstatat, libc_sys_kfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_fsymlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323403, enableExcept: false) */
	b .
END(libc_sys_fsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_fsymlinkat, libc_sys_fsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_freadlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323404, enableExcept: false) */
	b .
END(libc_sys_freadlinkat)
DEFINE_PUBLIC_ALIAS(sys_freadlinkat, libc_sys_freadlinkat)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_preadvf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323405, enableExcept: false) */
	b .
END(libc_sys_preadvf)
DEFINE_PUBLIC_ALIAS(sys_preadvf, libc_sys_preadvf)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_pwritevf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323406, enableExcept: false) */
	b .
END(libc_sys_pwritevf)
DEFINE_PUBLIC_ALIAS(sys_pwritevf, libc_sys_pwritevf)

/* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
INTERN_FUNCTION(libc_sys_fallocate64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323424, enableExcept: false) */
	b .
END(libc_sys_fallocate64)
DEFINE_PUBLIC_ALIAS(sys_fallocate64, libc_sys_fallocate64)

/* errno_t restart_syscall(void) */
INTERN_FUNCTION(libc_sys_Xrestart_syscall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 0, enableExcept: true) */
	b .
END(libc_sys_Xrestart_syscall)
DEFINE_PUBLIC_ALIAS(sys_Xrestart_syscall, libc_sys_Xrestart_syscall)

/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_Xexit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 1, enableExcept: true) */
	b .
END(libc_sys_Xexit)
DEFINE_PUBLIC_ALIAS(sys_Xexit, libc_sys_Xexit)

/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
/* pid_t fork(void) */
INTERN_FUNCTION(libc_sys_Xfork)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 2, enableExcept: true) */
	b .
END(libc_sys_Xfork)
DEFINE_PUBLIC_ALIAS(sys_Xfork, libc_sys_Xfork)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xread)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 3, enableExcept: true) */
	b .
END(libc_sys_Xread)
DEFINE_PUBLIC_ALIAS(sys_Xread, libc_sys_Xread)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xwrite)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 4, enableExcept: true) */
	b .
END(libc_sys_Xwrite)
DEFINE_PUBLIC_ALIAS(sys_Xwrite, libc_sys_Xwrite)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xopen)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 5, enableExcept: true) */
	b .
END(libc_sys_Xopen)
DEFINE_PUBLIC_ALIAS(sys_Xopen, libc_sys_Xopen)

/* Close a given file descriptor/handle `fd' */
/* errno_t close(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xclose)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 6, enableExcept: true) */
	b .
END(libc_sys_Xclose)
DEFINE_PUBLIC_ALIAS(sys_Xclose, libc_sys_Xclose)

/* fd_t creat(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xcreat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8, enableExcept: true) */
	b .
END(libc_sys_Xcreat)
DEFINE_PUBLIC_ALIAS(sys_Xcreat, libc_sys_Xcreat)

/* errno_t link(char const *existing_file, char const *link_file) */
INTERN_FUNCTION(libc_sys_Xlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 9, enableExcept: true) */
	b .
END(libc_sys_Xlink)
DEFINE_PUBLIC_ALIAS(sys_Xlink, libc_sys_Xlink)

/* errno_t unlink(char const *filename) */
INTERN_FUNCTION(libc_sys_Xunlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 10, enableExcept: true) */
	b .
END(libc_sys_Xunlink)
DEFINE_PUBLIC_ALIAS(sys_Xunlink, libc_sys_Xunlink)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
INTERN_FUNCTION(libc_sys_Xexecve)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 11, enableExcept: true) */
	b .
END(libc_sys_Xexecve)
DEFINE_PUBLIC_ALIAS(sys_Xexecve, libc_sys_Xexecve)

/* errno_t chdir(char const *path) */
INTERN_FUNCTION(libc_sys_Xchdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 12, enableExcept: true) */
	b .
END(libc_sys_Xchdir)
DEFINE_PUBLIC_ALIAS(sys_Xchdir, libc_sys_Xchdir)

/* time32_t time(time32_t *timer) */
INTERN_FUNCTION(libc_sys_Xtime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 13, enableExcept: true) */
	b .
END(libc_sys_Xtime)
DEFINE_PUBLIC_ALIAS(sys_Xtime, libc_sys_Xtime)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_Xmknod)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 14, enableExcept: true) */
	b .
END(libc_sys_Xmknod)
DEFINE_PUBLIC_ALIAS(sys_Xmknod, libc_sys_Xmknod)

/* errno_t chmod(char const *filename, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xchmod)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 15, enableExcept: true) */
	b .
END(libc_sys_Xchmod)
DEFINE_PUBLIC_ALIAS(sys_Xchmod, libc_sys_Xchmod)

/* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
INTERN_FUNCTION(libc_sys_Xlchown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 16, enableExcept: true) */
	b .
END(libc_sys_Xlchown)
DEFINE_PUBLIC_ALIAS(sys_Xlchown, libc_sys_Xlchown)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_Xlseek)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 19, enableExcept: true) */
	b .
END(libc_sys_Xlseek)
DEFINE_PUBLIC_ALIAS(sys_Xlseek, libc_sys_Xlseek)

/* pid_t getpid(void) */
INTERN_FUNCTION(libc_sys_Xgetpid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 20, enableExcept: true) */
	b .
END(libc_sys_Xgetpid)
DEFINE_PUBLIC_ALIAS(sys_Xgetpid, libc_sys_Xgetpid)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
INTERN_FUNCTION(libc_sys_Xmount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 21, enableExcept: true) */
	b .
END(libc_sys_Xmount)
DEFINE_PUBLIC_ALIAS(sys_Xmount, libc_sys_Xmount)

/* errno_t umount(char const *special_file) */
INTERN_FUNCTION(libc_sys_Xumount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 22, enableExcept: true) */
	b .
END(libc_sys_Xumount)
DEFINE_PUBLIC_ALIAS(sys_Xumount, libc_sys_Xumount)

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid(uint16_t uid) */
INTERN_FUNCTION(libc_sys_Xsetuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 23, enableExcept: true) */
	b .
END(libc_sys_Xsetuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetuid, libc_sys_Xsetuid)

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uint16_t getuid(void) */
INTERN_FUNCTION(libc_sys_Xgetuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 24, enableExcept: true) */
	b .
END(libc_sys_Xgetuid)
DEFINE_PUBLIC_ALIAS(sys_Xgetuid, libc_sys_Xgetuid)

/* errno_t stime(time32_t const *t) */
INTERN_FUNCTION(libc_sys_Xstime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 25, enableExcept: true) */
	b .
END(libc_sys_Xstime)
DEFINE_PUBLIC_ALIAS(sys_Xstime, libc_sys_Xstime)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
INTERN_FUNCTION(libc_sys_Xptrace)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 26, enableExcept: true) */
	b .
END(libc_sys_Xptrace)
DEFINE_PUBLIC_ALIAS(sys_Xptrace, libc_sys_Xptrace)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
INTERN_FUNCTION(libc_sys_Xalarm)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 27, enableExcept: true) */
	b .
END(libc_sys_Xalarm)
DEFINE_PUBLIC_ALIAS(sys_Xalarm, libc_sys_Xalarm)

/* Same as `select(0, NULL, NULL, NULL, NULL)' */
/* errno_t pause(void) */
INTERN_FUNCTION(libc_sys_Xpause)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 29, enableExcept: true) */
	b .
END(libc_sys_Xpause)
DEFINE_PUBLIC_ALIAS(sys_Xpause, libc_sys_Xpause)

/* @param: times: When NULL, set the current time */
/* errno_t utime(char const *filename, struct utimbuf32 const *times) */
INTERN_FUNCTION(libc_sys_Xutime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 30, enableExcept: true) */
	b .
END(libc_sys_Xutime)
DEFINE_PUBLIC_ALIAS(sys_Xutime, libc_sys_Xutime)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_Xaccess)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 33, enableExcept: true) */
	b .
END(libc_sys_Xaccess)
DEFINE_PUBLIC_ALIAS(sys_Xaccess, libc_sys_Xaccess)

/* errno_t nice(syscall_slong_t inc) */
INTERN_FUNCTION(libc_sys_Xnice)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 34, enableExcept: true) */
	b .
END(libc_sys_Xnice)
DEFINE_PUBLIC_ALIAS(sys_Xnice, libc_sys_Xnice)

/* errno_t sync(void) */
INTERN_FUNCTION(libc_sys_Xsync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 36, enableExcept: true) */
	b .
END(libc_sys_Xsync)
DEFINE_PUBLIC_ALIAS(sys_Xsync, libc_sys_Xsync)

/* errno_t kill(pid_t pid, signo_t signo) */
INTERN_FUNCTION(libc_sys_Xkill)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 37, enableExcept: true) */
	b .
END(libc_sys_Xkill)
DEFINE_PUBLIC_ALIAS(sys_Xkill, libc_sys_Xkill)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_Xrename)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 38, enableExcept: true) */
	b .
END(libc_sys_Xrename)
DEFINE_PUBLIC_ALIAS(sys_Xrename, libc_sys_Xrename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmkdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 39, enableExcept: true) */
	b .
END(libc_sys_Xmkdir)
DEFINE_PUBLIC_ALIAS(sys_Xmkdir, libc_sys_Xmkdir)

/* errno_t rmdir(char const *path) */
INTERN_FUNCTION(libc_sys_Xrmdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 40, enableExcept: true) */
	b .
END(libc_sys_Xrmdir)
DEFINE_PUBLIC_ALIAS(sys_Xrmdir, libc_sys_Xrmdir)

/* fd_t dup(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xdup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 41, enableExcept: true) */
	b .
END(libc_sys_Xdup)
DEFINE_PUBLIC_ALIAS(sys_Xdup, libc_sys_Xdup)

/* errno_t pipe(fd_t[2] pipedes) */
INTERN_FUNCTION(libc_sys_Xpipe)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 42, enableExcept: true) */
	b .
END(libc_sys_Xpipe)
DEFINE_PUBLIC_ALIAS(sys_Xpipe, libc_sys_Xpipe)

/* clock_t times(struct tms *buf) */
INTERN_FUNCTION(libc_sys_Xtimes)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 43, enableExcept: true) */
	b .
END(libc_sys_Xtimes)
DEFINE_PUBLIC_ALIAS(sys_Xtimes, libc_sys_Xtimes)

/* errno_t brk(void *addr) */
INTERN_FUNCTION(libc_sys_Xbrk)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 45, enableExcept: true) */
	b .
END(libc_sys_Xbrk)
DEFINE_PUBLIC_ALIAS(sys_Xbrk, libc_sys_Xbrk)

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid(uint16_t gid) */
INTERN_FUNCTION(libc_sys_Xsetgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 46, enableExcept: true) */
	b .
END(libc_sys_Xsetgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetgid, libc_sys_Xsetgid)

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* uint16_t getgid(void) */
INTERN_FUNCTION(libc_sys_Xgetgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 47, enableExcept: true) */
	b .
END(libc_sys_Xgetgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetgid, libc_sys_Xgetgid)

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint16_t geteuid(void) */
INTERN_FUNCTION(libc_sys_Xgeteuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 49, enableExcept: true) */
	b .
END(libc_sys_Xgeteuid)
DEFINE_PUBLIC_ALIAS(sys_Xgeteuid, libc_sys_Xgeteuid)

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint16_t getegid(void) */
INTERN_FUNCTION(libc_sys_Xgetegid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 50, enableExcept: true) */
	b .
END(libc_sys_Xgetegid)
DEFINE_PUBLIC_ALIAS(sys_Xgetegid, libc_sys_Xgetegid)

/* errno_t acct(char const *filename) */
INTERN_FUNCTION(libc_sys_Xacct)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 51, enableExcept: true) */
	b .
END(libc_sys_Xacct)
DEFINE_PUBLIC_ALIAS(sys_Xacct, libc_sys_Xacct)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xumount2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 52, enableExcept: true) */
	b .
END(libc_sys_Xumount2)
DEFINE_PUBLIC_ALIAS(sys_Xumount2, libc_sys_Xumount2)

/* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_Xioctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 54, enableExcept: true) */
	b .
END(libc_sys_Xioctl)
DEFINE_PUBLIC_ALIAS(sys_Xioctl, libc_sys_Xioctl)

/* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_Xfcntl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 55, enableExcept: true) */
	b .
END(libc_sys_Xfcntl)
DEFINE_PUBLIC_ALIAS(sys_Xfcntl, libc_sys_Xfcntl)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
INTERN_FUNCTION(libc_sys_Xsetpgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 57, enableExcept: true) */
	b .
END(libc_sys_Xsetpgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetpgid, libc_sys_Xsetpgid)

/* mode_t umask(mode_t mode) */
INTERN_FUNCTION(libc_sys_Xumask)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 60, enableExcept: true) */
	b .
END(libc_sys_Xumask)
DEFINE_PUBLIC_ALIAS(sys_Xumask, libc_sys_Xumask)

/* errno_t chroot(char const *path) */
INTERN_FUNCTION(libc_sys_Xchroot)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 61, enableExcept: true) */
	b .
END(libc_sys_Xchroot)
DEFINE_PUBLIC_ALIAS(sys_Xchroot, libc_sys_Xchroot)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
INTERN_FUNCTION(libc_sys_Xustat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 62, enableExcept: true) */
	b .
END(libc_sys_Xustat)
DEFINE_PUBLIC_ALIAS(sys_Xustat, libc_sys_Xustat)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
INTERN_FUNCTION(libc_sys_Xdup2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 63, enableExcept: true) */
	b .
END(libc_sys_Xdup2)
DEFINE_PUBLIC_ALIAS(sys_Xdup2, libc_sys_Xdup2)

/* pid_t getppid(void) */
INTERN_FUNCTION(libc_sys_Xgetppid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 64, enableExcept: true) */
	b .
END(libc_sys_Xgetppid)
DEFINE_PUBLIC_ALIAS(sys_Xgetppid, libc_sys_Xgetppid)

/* pid_t getpgrp(void) */
INTERN_FUNCTION(libc_sys_Xgetpgrp)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 65, enableExcept: true) */
	b .
END(libc_sys_Xgetpgrp)
DEFINE_PUBLIC_ALIAS(sys_Xgetpgrp, libc_sys_Xgetpgrp)

/* pid_t setsid(void) */
INTERN_FUNCTION(libc_sys_Xsetsid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 66, enableExcept: true) */
	b .
END(libc_sys_Xsetsid)
DEFINE_PUBLIC_ALIAS(sys_Xsetsid, libc_sys_Xsetsid)

/* errno_t sigaction(signo_t signo, struct __old_kernel_sigaction const *act, struct __old_kernel_sigaction *oact) */
INTERN_FUNCTION(libc_sys_Xsigaction)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 67, enableExcept: true) */
	b .
END(libc_sys_Xsigaction)
DEFINE_PUBLIC_ALIAS(sys_Xsigaction, libc_sys_Xsigaction)

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid(uint16_t ruid, uint16_t euid) */
INTERN_FUNCTION(libc_sys_Xsetreuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 70, enableExcept: true) */
	b .
END(libc_sys_Xsetreuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetreuid, libc_sys_Xsetreuid)

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid(uint16_t rgid, uint16_t egid) */
INTERN_FUNCTION(libc_sys_Xsetregid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 71, enableExcept: true) */
	b .
END(libc_sys_Xsetregid)
DEFINE_PUBLIC_ALIAS(sys_Xsetregid, libc_sys_Xsetregid)

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t sigsuspend(struct __old_sigset_struct const *set) */
INTERN_FUNCTION(libc_sys_Xsigsuspend)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 72, enableExcept: true) */
	b .
END(libc_sys_Xsigsuspend)
DEFINE_PUBLIC_ALIAS(sys_Xsigsuspend, libc_sys_Xsigsuspend)

/* errno_t sigpending(struct __old_sigset_struct *set) */
INTERN_FUNCTION(libc_sys_Xsigpending)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 73, enableExcept: true) */
	b .
END(libc_sys_Xsigpending)
DEFINE_PUBLIC_ALIAS(sys_Xsigpending, libc_sys_Xsigpending)

/* errno_t sethostname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_Xsethostname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 74, enableExcept: true) */
	b .
END(libc_sys_Xsethostname)
DEFINE_PUBLIC_ALIAS(sys_Xsethostname, libc_sys_Xsethostname)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
INTERN_FUNCTION(libc_sys_Xsetrlimit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 75, enableExcept: true) */
	b .
END(libc_sys_Xsetrlimit)
DEFINE_PUBLIC_ALIAS(sys_Xsetrlimit, libc_sys_Xsetrlimit)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
INTERN_FUNCTION(libc_sys_Xgetrlimit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 76, enableExcept: true) */
	b .
END(libc_sys_Xgetrlimit)
DEFINE_PUBLIC_ALIAS(sys_Xgetrlimit, libc_sys_Xgetrlimit)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
INTERN_FUNCTION(libc_sys_Xgetrusage)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 77, enableExcept: true) */
	b .
END(libc_sys_Xgetrusage)
DEFINE_PUBLIC_ALIAS(sys_Xgetrusage, libc_sys_Xgetrusage)

/* errno_t gettimeofday(struct timeval *tv, struct timezone *tz) */
INTERN_FUNCTION(libc_sys_Xgettimeofday)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 78, enableExcept: true) */
	b .
END(libc_sys_Xgettimeofday)
DEFINE_PUBLIC_ALIAS(sys_Xgettimeofday, libc_sys_Xgettimeofday)

/* errno_t settimeofday(struct timeval const *tv, struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_Xsettimeofday)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 79, enableExcept: true) */
	b .
END(libc_sys_Xsettimeofday)
DEFINE_PUBLIC_ALIAS(sys_Xsettimeofday, libc_sys_Xsettimeofday)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups(size_t count, uint16_t[] list) */
INTERN_FUNCTION(libc_sys_Xgetgroups)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 80, enableExcept: true) */
	b .
END(libc_sys_Xgetgroups)
DEFINE_PUBLIC_ALIAS(sys_Xgetgroups, libc_sys_Xgetgroups)

/* errno_t setgroups(size_t count, uint16_t const *groups) */
INTERN_FUNCTION(libc_sys_Xsetgroups)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 81, enableExcept: true) */
	b .
END(libc_sys_Xsetgroups)
DEFINE_PUBLIC_ALIAS(sys_Xsetgroups, libc_sys_Xsetgroups)

/* ssize_t select(struct sel_arg_struct const *arg) */
INTERN_FUNCTION(libc_sys_Xselect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 82, enableExcept: true) */
	b .
END(libc_sys_Xselect)
DEFINE_PUBLIC_ALIAS(sys_Xselect, libc_sys_Xselect)

/* errno_t symlink(char const *link_text, char const *target_path) */
INTERN_FUNCTION(libc_sys_Xsymlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 83, enableExcept: true) */
	b .
END(libc_sys_Xsymlink)
DEFINE_PUBLIC_ALIAS(sys_Xsymlink, libc_sys_Xsymlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xreadlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 85, enableExcept: true) */
	b .
END(libc_sys_Xreadlink)
DEFINE_PUBLIC_ALIAS(sys_Xreadlink, libc_sys_Xreadlink)

/* errno_t uselib(char const *library) */
INTERN_FUNCTION(libc_sys_Xuselib)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 86, enableExcept: true) */
	b .
END(libc_sys_Xuselib)
DEFINE_PUBLIC_ALIAS(sys_Xuselib, libc_sys_Xuselib)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
INTERN_FUNCTION(libc_sys_Xswapon)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 87, enableExcept: true) */
	b .
END(libc_sys_Xswapon)
DEFINE_PUBLIC_ALIAS(sys_Xswapon, libc_sys_Xswapon)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_Xreboot)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 88, enableExcept: true) */
	b .
END(libc_sys_Xreboot)
DEFINE_PUBLIC_ALIAS(sys_Xreboot, libc_sys_Xreboot)

/* Read exactly one directory entry from `fd'
 * Note that the linux version of this system call has one additional argument `count'.
 * However, within the  linux kernel implementation,  that argument is  unconditionally
 * ignored,  and the system call will _always_ read exactly 1 directory entry from `fd'
 * @return: 1 : Read on directory entry
 * @return: 0 : End-of-directory */
/* syscall_slong_t readdir(fd_t fd, struct old_linux_dirent *buf) */
INTERN_FUNCTION(libc_sys_Xreaddir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 89, enableExcept: true) */
	b .
END(libc_sys_Xreaddir)
DEFINE_PUBLIC_ALIAS(sys_Xreaddir, libc_sys_Xreaddir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
INTERN_FUNCTION(libc_sys_Xmmap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 90, enableExcept: true) */
	b .
END(libc_sys_Xmmap)
DEFINE_PUBLIC_ALIAS(sys_Xmmap, libc_sys_Xmmap)

/* errno_t munmap(void *addr, size_t len) */
INTERN_FUNCTION(libc_sys_Xmunmap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 91, enableExcept: true) */
	b .
END(libc_sys_Xmunmap)
DEFINE_PUBLIC_ALIAS(sys_Xmunmap, libc_sys_Xmunmap)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xtruncate)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 92, enableExcept: true) */
	b .
END(libc_sys_Xtruncate)
DEFINE_PUBLIC_ALIAS(sys_Xtruncate, libc_sys_Xtruncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xftruncate)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 93, enableExcept: true) */
	b .
END(libc_sys_Xftruncate)
DEFINE_PUBLIC_ALIAS(sys_Xftruncate, libc_sys_Xftruncate)

/* errno_t fchmod(fd_t fd, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xfchmod)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 94, enableExcept: true) */
	b .
END(libc_sys_Xfchmod)
DEFINE_PUBLIC_ALIAS(sys_Xfchmod, libc_sys_Xfchmod)

/* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
INTERN_FUNCTION(libc_sys_Xfchown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 95, enableExcept: true) */
	b .
END(libc_sys_Xfchown)
DEFINE_PUBLIC_ALIAS(sys_Xfchown, libc_sys_Xfchown)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
INTERN_FUNCTION(libc_sys_Xgetpriority)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 96, enableExcept: true) */
	b .
END(libc_sys_Xgetpriority)
DEFINE_PUBLIC_ALIAS(sys_Xgetpriority, libc_sys_Xgetpriority)

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
INTERN_FUNCTION(libc_sys_Xsetpriority)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 97, enableExcept: true) */
	b .
END(libc_sys_Xsetpriority)
DEFINE_PUBLIC_ALIAS(sys_Xsetpriority, libc_sys_Xsetpriority)

/* errno_t statfs(char const *file, struct statfs *buf) */
INTERN_FUNCTION(libc_sys_Xstatfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 99, enableExcept: true) */
	b .
END(libc_sys_Xstatfs)
DEFINE_PUBLIC_ALIAS(sys_Xstatfs, libc_sys_Xstatfs)

/* errno_t fstatfs(fd_t file, struct statfs *buf) */
INTERN_FUNCTION(libc_sys_Xfstatfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 100, enableExcept: true) */
	b .
END(libc_sys_Xfstatfs)
DEFINE_PUBLIC_ALIAS(sys_Xfstatfs, libc_sys_Xfstatfs)

/* syscall_slong_t socketcall(syscall_ulong_t call, syscall_ulong_t *args) */
INTERN_FUNCTION(libc_sys_Xsocketcall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 102, enableExcept: true) */
	b .
END(libc_sys_Xsocketcall)
DEFINE_PUBLIC_ALIAS(sys_Xsocketcall, libc_sys_Xsocketcall)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
INTERN_FUNCTION(libc_sys_Xsyslog)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 103, enableExcept: true) */
	b .
END(libc_sys_Xsyslog)
DEFINE_PUBLIC_ALIAS(sys_Xsyslog, libc_sys_Xsyslog)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer(syscall_ulong_t which, struct itimerval const *newval, struct itimerval *oldval) */
INTERN_FUNCTION(libc_sys_Xsetitimer)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 104, enableExcept: true) */
	b .
END(libc_sys_Xsetitimer)
DEFINE_PUBLIC_ALIAS(sys_Xsetitimer, libc_sys_Xsetitimer)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer(syscall_ulong_t which, struct itimerval *curr_value) */
INTERN_FUNCTION(libc_sys_Xgetitimer)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 105, enableExcept: true) */
	b .
END(libc_sys_Xgetitimer)
DEFINE_PUBLIC_ALIAS(sys_Xgetitimer, libc_sys_Xgetitimer)

/* errno_t stat(char const *filename, struct linux_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 106, enableExcept: true) */
	b .
END(libc_sys_Xstat)
DEFINE_PUBLIC_ALIAS(sys_Xstat, libc_sys_Xstat)

/* errno_t lstat(char const *filename, struct linux_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xlstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 107, enableExcept: true) */
	b .
END(libc_sys_Xlstat)
DEFINE_PUBLIC_ALIAS(sys_Xlstat, libc_sys_Xlstat)

/* errno_t fstat(fd_t fd, struct linux_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xfstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 108, enableExcept: true) */
	b .
END(libc_sys_Xfstat)
DEFINE_PUBLIC_ALIAS(sys_Xfstat, libc_sys_Xfstat)

/* errno_t vhangup(void) */
INTERN_FUNCTION(libc_sys_Xvhangup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 111, enableExcept: true) */
	b .
END(libc_sys_Xvhangup)
DEFINE_PUBLIC_ALIAS(sys_Xvhangup, libc_sys_Xvhangup)

/* Syscall to call a syscall */
/* errno_t syscall(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsyscall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 113, enableExcept: true) */
	b .
END(libc_sys_Xsyscall)
DEFINE_PUBLIC_ALIAS(sys_Xsyscall, libc_sys_Xsyscall)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
INTERN_FUNCTION(libc_sys_Xwait4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 114, enableExcept: true) */
	b .
END(libc_sys_Xwait4)
DEFINE_PUBLIC_ALIAS(sys_Xwait4, libc_sys_Xwait4)

/* errno_t swapoff(char const *pathname) */
INTERN_FUNCTION(libc_sys_Xswapoff)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 115, enableExcept: true) */
	b .
END(libc_sys_Xswapoff)
DEFINE_PUBLIC_ALIAS(sys_Xswapoff, libc_sys_Xswapoff)

/* errno_t sysinfo(struct sysinfo *info) */
INTERN_FUNCTION(libc_sys_Xsysinfo)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 116, enableExcept: true) */
	b .
END(libc_sys_Xsysinfo)
DEFINE_PUBLIC_ALIAS(sys_Xsysinfo, libc_sys_Xsysinfo)

/* errno_t ipc(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xipc)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 117, enableExcept: true) */
	b .
END(libc_sys_Xipc)
DEFINE_PUBLIC_ALIAS(sys_Xipc, libc_sys_Xipc)

/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
/* errno_t fsync(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfsync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 118, enableExcept: true) */
	b .
END(libc_sys_Xfsync)
DEFINE_PUBLIC_ALIAS(sys_Xfsync, libc_sys_Xfsync)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
INTERN_FUNCTION(libc_sys_Xclone)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 120, enableExcept: true) */
	b .
END(libc_sys_Xclone)
DEFINE_PUBLIC_ALIAS(sys_Xclone, libc_sys_Xclone)

/* errno_t setdomainname(char const *name, size_t len) */
INTERN_FUNCTION(libc_sys_Xsetdomainname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 121, enableExcept: true) */
	b .
END(libc_sys_Xsetdomainname)
DEFINE_PUBLIC_ALIAS(sys_Xsetdomainname, libc_sys_Xsetdomainname)

/* errno_t uname(struct utsname *name) */
INTERN_FUNCTION(libc_sys_Xuname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 122, enableExcept: true) */
	b .
END(libc_sys_Xuname)
DEFINE_PUBLIC_ALIAS(sys_Xuname, libc_sys_Xuname)

/* errno_t adjtimex(struct timex32 *ntx) */
INTERN_FUNCTION(libc_sys_Xadjtimex)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 124, enableExcept: true) */
	b .
END(libc_sys_Xadjtimex)
DEFINE_PUBLIC_ALIAS(sys_Xadjtimex, libc_sys_Xadjtimex)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
INTERN_FUNCTION(libc_sys_Xmprotect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 125, enableExcept: true) */
	b .
END(libc_sys_Xmprotect)
DEFINE_PUBLIC_ALIAS(sys_Xmprotect, libc_sys_Xmprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t sigprocmask(syscall_ulong_t how, struct __old_sigset_struct const *set, struct __old_sigset_struct *oset) */
INTERN_FUNCTION(libc_sys_Xsigprocmask)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 126, enableExcept: true) */
	b .
END(libc_sys_Xsigprocmask)
DEFINE_PUBLIC_ALIAS(sys_Xsigprocmask, libc_sys_Xsigprocmask)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
INTERN_FUNCTION(libc_sys_Xinit_module)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 128, enableExcept: true) */
	b .
END(libc_sys_Xinit_module)
DEFINE_PUBLIC_ALIAS(sys_Xinit_module, libc_sys_Xinit_module)

/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
/* errno_t delete_module(char const *name, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xdelete_module)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 129, enableExcept: true) */
	b .
END(libc_sys_Xdelete_module)
DEFINE_PUBLIC_ALIAS(sys_Xdelete_module, libc_sys_Xdelete_module)

/* errno_t quotactl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xquotactl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 131, enableExcept: true) */
	b .
END(libc_sys_Xquotactl)
DEFINE_PUBLIC_ALIAS(sys_Xquotactl, libc_sys_Xquotactl)

/* pid_t getpgid(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xgetpgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 132, enableExcept: true) */
	b .
END(libc_sys_Xgetpgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetpgid, libc_sys_Xgetpgid)

/* errno_t fchdir(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfchdir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 133, enableExcept: true) */
	b .
END(libc_sys_Xfchdir)
DEFINE_PUBLIC_ALIAS(sys_Xfchdir, libc_sys_Xfchdir)

/* errno_t bdflush(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xbdflush)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 134, enableExcept: true) */
	b .
END(libc_sys_Xbdflush)
DEFINE_PUBLIC_ALIAS(sys_Xbdflush, libc_sys_Xbdflush)

/* errno_t sysfs(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsysfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 135, enableExcept: true) */
	b .
END(libc_sys_Xsysfs)
DEFINE_PUBLIC_ALIAS(sys_Xsysfs, libc_sys_Xsysfs)

/* errno_t personality(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpersonality)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 136, enableExcept: true) */
	b .
END(libc_sys_Xpersonality)
DEFINE_PUBLIC_ALIAS(sys_Xpersonality, libc_sys_Xpersonality)

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid(uint16_t uid) */
INTERN_FUNCTION(libc_sys_Xsetfsuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 138, enableExcept: true) */
	b .
END(libc_sys_Xsetfsuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsuid, libc_sys_Xsetfsuid)

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid(uint16_t gid) */
INTERN_FUNCTION(libc_sys_Xsetfsgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 139, enableExcept: true) */
	b .
END(libc_sys_Xsetfsgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsgid, libc_sys_Xsetfsgid)

/* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_X_llseek)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 140, enableExcept: true) */
	b .
END(libc_sys_X_llseek)
DEFINE_PUBLIC_ALIAS(sys_X_llseek, libc_sys_X_llseek)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents(fd_t fd, struct linux_dirent *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xgetdents)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 141, enableExcept: true) */
	b .
END(libc_sys_Xgetdents)
DEFINE_PUBLIC_ALIAS(sys_Xgetdents, libc_sys_Xgetdents)

/* ssize_t _newselect(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval32 *timeout) */
INTERN_FUNCTION(libc_sys_X_newselect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 142, enableExcept: true) */
	b .
END(libc_sys_X_newselect)
DEFINE_PUBLIC_ALIAS(sys_X_newselect, libc_sys_X_newselect)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
INTERN_FUNCTION(libc_sys_Xflock)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 143, enableExcept: true) */
	b .
END(libc_sys_Xflock)
DEFINE_PUBLIC_ALIAS(sys_Xflock, libc_sys_Xflock)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmsync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 144, enableExcept: true) */
	b .
END(libc_sys_Xmsync)
DEFINE_PUBLIC_ALIAS(sys_Xmsync, libc_sys_Xmsync)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_Xreadv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 145, enableExcept: true) */
	b .
END(libc_sys_Xreadv)
DEFINE_PUBLIC_ALIAS(sys_Xreadv, libc_sys_Xreadv)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
INTERN_FUNCTION(libc_sys_Xwritev)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 146, enableExcept: true) */
	b .
END(libc_sys_Xwritev)
DEFINE_PUBLIC_ALIAS(sys_Xwritev, libc_sys_Xwritev)

/* pid_t getsid(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xgetsid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 147, enableExcept: true) */
	b .
END(libc_sys_Xgetsid)
DEFINE_PUBLIC_ALIAS(sys_Xgetsid, libc_sys_Xgetsid)

/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
/* errno_t fdatasync(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xfdatasync)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 148, enableExcept: true) */
	b .
END(libc_sys_Xfdatasync)
DEFINE_PUBLIC_ALIAS(sys_Xfdatasync, libc_sys_Xfdatasync)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_X_sysctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 149, enableExcept: true) */
	b .
END(libc_sys_X_sysctl)
DEFINE_PUBLIC_ALIAS(sys_X_sysctl, libc_sys_X_sysctl)

/* errno_t mlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_Xmlock)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 150, enableExcept: true) */
	b .
END(libc_sys_Xmlock)
DEFINE_PUBLIC_ALIAS(sys_Xmlock, libc_sys_Xmlock)

/* errno_t munlock(void const *addr, size_t len) */
INTERN_FUNCTION(libc_sys_Xmunlock)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 151, enableExcept: true) */
	b .
END(libc_sys_Xmunlock)
DEFINE_PUBLIC_ALIAS(sys_Xmunlock, libc_sys_Xmunlock)

/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
/* errno_t mlockall(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmlockall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 152, enableExcept: true) */
	b .
END(libc_sys_Xmlockall)
DEFINE_PUBLIC_ALIAS(sys_Xmlockall, libc_sys_Xmlockall)

/* errno_t munlockall(void) */
INTERN_FUNCTION(libc_sys_Xmunlockall)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 153, enableExcept: true) */
	b .
END(libc_sys_Xmunlockall)
DEFINE_PUBLIC_ALIAS(sys_Xmunlockall, libc_sys_Xmunlockall)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_Xsched_setparam)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 154, enableExcept: true) */
	b .
END(libc_sys_Xsched_setparam)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setparam, libc_sys_Xsched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
INTERN_FUNCTION(libc_sys_Xsched_getparam)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 155, enableExcept: true) */
	b .
END(libc_sys_Xsched_getparam)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getparam, libc_sys_Xsched_getparam)

/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
INTERN_FUNCTION(libc_sys_Xsched_setscheduler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 156, enableExcept: true) */
	b .
END(libc_sys_Xsched_setscheduler)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setscheduler, libc_sys_Xsched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xsched_getscheduler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 157, enableExcept: true) */
	b .
END(libc_sys_Xsched_getscheduler)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getscheduler, libc_sys_Xsched_getscheduler)

/* errno_t sched_yield(void) */
INTERN_FUNCTION(libc_sys_Xsched_yield)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 158, enableExcept: true) */
	b .
END(libc_sys_Xsched_yield)
DEFINE_PUBLIC_ALIAS(sys_Xsched_yield, libc_sys_Xsched_yield)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_Xsched_get_priority_max)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 159, enableExcept: true) */
	b .
END(libc_sys_Xsched_get_priority_max)
DEFINE_PUBLIC_ALIAS(sys_Xsched_get_priority_max, libc_sys_Xsched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
INTERN_FUNCTION(libc_sys_Xsched_get_priority_min)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 160, enableExcept: true) */
	b .
END(libc_sys_Xsched_get_priority_min)
DEFINE_PUBLIC_ALIAS(sys_Xsched_get_priority_min, libc_sys_Xsched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct timespec32 *ts) */
INTERN_FUNCTION(libc_sys_Xsched_rr_get_interval)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 161, enableExcept: true) */
	b .
END(libc_sys_Xsched_rr_get_interval)
DEFINE_PUBLIC_ALIAS(sys_Xsched_rr_get_interval, libc_sys_Xsched_rr_get_interval)

/* errno_t nanosleep(struct timespec32 const *req, struct timespec32 *rem) */
INTERN_FUNCTION(libc_sys_Xnanosleep)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 162, enableExcept: true) */
	b .
END(libc_sys_Xnanosleep)
DEFINE_PUBLIC_ALIAS(sys_Xnanosleep, libc_sys_Xnanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
INTERN_FUNCTION(libc_sys_Xmremap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 163, enableExcept: true) */
	b .
END(libc_sys_Xmremap)
DEFINE_PUBLIC_ALIAS(sys_Xmremap, libc_sys_Xmremap)

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
INTERN_FUNCTION(libc_sys_Xsetresuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 164, enableExcept: true) */
	b .
END(libc_sys_Xsetresuid)
DEFINE_PUBLIC_ALIAS(sys_Xsetresuid, libc_sys_Xsetresuid)

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
INTERN_FUNCTION(libc_sys_Xgetresuid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 165, enableExcept: true) */
	b .
END(libc_sys_Xgetresuid)
DEFINE_PUBLIC_ALIAS(sys_Xgetresuid, libc_sys_Xgetresuid)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xpoll)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 168, enableExcept: true) */
	b .
END(libc_sys_Xpoll)
DEFINE_PUBLIC_ALIAS(sys_Xpoll, libc_sys_Xpoll)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xnfsservctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 169, enableExcept: true) */
	b .
END(libc_sys_Xnfsservctl)
DEFINE_PUBLIC_ALIAS(sys_Xnfsservctl, libc_sys_Xnfsservctl)

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
INTERN_FUNCTION(libc_sys_Xsetresgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 170, enableExcept: true) */
	b .
END(libc_sys_Xsetresgid)
DEFINE_PUBLIC_ALIAS(sys_Xsetresgid, libc_sys_Xsetresgid)

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
INTERN_FUNCTION(libc_sys_Xgetresgid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 171, enableExcept: true) */
	b .
END(libc_sys_Xgetresgid)
DEFINE_PUBLIC_ALIAS(sys_Xgetresgid, libc_sys_Xgetresgid)

/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
/* syscall_slong_t prctl(unsigned int command, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5) */
INTERN_FUNCTION(libc_sys_Xprctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 172, enableExcept: true) */
	b .
END(libc_sys_Xprctl)
DEFINE_PUBLIC_ALIAS(sys_Xprctl, libc_sys_Xprctl)

/* errno_t rt_sigaction(signo_t signo, struct __kernel_sigaction const *act, struct __kernel_sigaction *oact, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigaction)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 174, enableExcept: true) */
	b .
END(libc_sys_Xrt_sigaction)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigaction, libc_sys_Xrt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigprocmask)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 175, enableExcept: true) */
	b .
END(libc_sys_Xrt_sigprocmask)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigprocmask, libc_sys_Xrt_sigprocmask)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigpending)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 176, enableExcept: true) */
	b .
END(libc_sys_Xrt_sigpending)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigpending, libc_sys_Xrt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec32 const *timeout, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigtimedwait)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 177, enableExcept: true) */
	b .
END(libc_sys_Xrt_sigtimedwait)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigtimedwait, libc_sys_Xrt_sigtimedwait)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_Xrt_sigqueueinfo)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 178, enableExcept: true) */
	b .
END(libc_sys_Xrt_sigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigqueueinfo, libc_sys_Xrt_sigqueueinfo)

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigsuspend)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 179, enableExcept: true) */
	b .
END(libc_sys_Xrt_sigsuspend)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigsuspend, libc_sys_Xrt_sigsuspend)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpread64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 180, enableExcept: true) */
	b .
END(libc_sys_Xpread64)
DEFINE_PUBLIC_ALIAS(sys_Xpread64, libc_sys_Xpread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpwrite64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 181, enableExcept: true) */
	b .
END(libc_sys_Xpwrite64)
DEFINE_PUBLIC_ALIAS(sys_Xpwrite64, libc_sys_Xpwrite64)

/* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
INTERN_FUNCTION(libc_sys_Xchown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 182, enableExcept: true) */
	b .
END(libc_sys_Xchown)
DEFINE_PUBLIC_ALIAS(sys_Xchown, libc_sys_Xchown)

/* ssize_t getcwd(char *buf, size_t size) */
INTERN_FUNCTION(libc_sys_Xgetcwd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 183, enableExcept: true) */
	b .
END(libc_sys_Xgetcwd)
DEFINE_PUBLIC_ALIAS(sys_Xgetcwd, libc_sys_Xgetcwd)

/* errno_t capget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xcapget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 184, enableExcept: true) */
	b .
END(libc_sys_Xcapget)
DEFINE_PUBLIC_ALIAS(sys_Xcapget, libc_sys_Xcapget)

/* errno_t capset(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xcapset)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 185, enableExcept: true) */
	b .
END(libc_sys_Xcapset)
DEFINE_PUBLIC_ALIAS(sys_Xcapset, libc_sys_Xcapset)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
INTERN_FUNCTION(libc_sys_Xsigaltstack)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 186, enableExcept: true) */
	b .
END(libc_sys_Xsigaltstack)
DEFINE_PUBLIC_ALIAS(sys_Xsigaltstack, libc_sys_Xsigaltstack)

/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
/* ssize_t sendfile(fd_t outfd, fd_t infd, syscall_ulong_t *pin_offset, size_t num_bytes) */
INTERN_FUNCTION(libc_sys_Xsendfile)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 187, enableExcept: true) */
	b .
END(libc_sys_Xsendfile)
DEFINE_PUBLIC_ALIAS(sys_Xsendfile, libc_sys_Xsendfile)

/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will  only be resumed in case  the
 *                     new  program image could  be loaded successfully. Otherwise,
 *                     the call  to  `execve(2)'  returns normally  in  the  child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
/* pid_t vfork(void) */
INTERN_FUNCTION(libc_sys_Xvfork)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 190, enableExcept: true) */
	b .
END(libc_sys_Xvfork)
DEFINE_PUBLIC_ALIAS(sys_Xvfork, libc_sys_Xvfork)

/* errno_t ugetrlimit(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xugetrlimit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 191, enableExcept: true) */
	b .
END(libc_sys_Xugetrlimit)
DEFINE_PUBLIC_ALIAS(sys_Xugetrlimit, libc_sys_Xugetrlimit)

/* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
INTERN_FUNCTION(libc_sys_Xmmap2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 192, enableExcept: true) */
	b .
END(libc_sys_Xmmap2)
DEFINE_PUBLIC_ALIAS(sys_Xmmap2, libc_sys_Xmmap2)

/* errno_t truncate64(char const *filename, uint64_t length) */
INTERN_FUNCTION(libc_sys_Xtruncate64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 193, enableExcept: true) */
	b .
END(libc_sys_Xtruncate64)
DEFINE_PUBLIC_ALIAS(sys_Xtruncate64, libc_sys_Xtruncate64)

/* errno_t ftruncate64(fd_t fd, uint64_t length) */
INTERN_FUNCTION(libc_sys_Xftruncate64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 194, enableExcept: true) */
	b .
END(libc_sys_Xftruncate64)
DEFINE_PUBLIC_ALIAS(sys_Xftruncate64, libc_sys_Xftruncate64)

/* errno_t stat64(char const *filename, struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xstat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 195, enableExcept: true) */
	b .
END(libc_sys_Xstat64)
DEFINE_PUBLIC_ALIAS(sys_Xstat64, libc_sys_Xstat64)

/* errno_t lstat64(char const *filename, struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xlstat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 196, enableExcept: true) */
	b .
END(libc_sys_Xlstat64)
DEFINE_PUBLIC_ALIAS(sys_Xlstat64, libc_sys_Xlstat64)

/* errno_t fstat64(fd_t fd, struct linux_stat64 *statbuf) */
INTERN_FUNCTION(libc_sys_Xfstat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 197, enableExcept: true) */
	b .
END(libc_sys_Xfstat64)
DEFINE_PUBLIC_ALIAS(sys_Xfstat64, libc_sys_Xfstat64)

/* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
INTERN_FUNCTION(libc_sys_Xlchown32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 198, enableExcept: true) */
	b .
END(libc_sys_Xlchown32)
DEFINE_PUBLIC_ALIAS(sys_Xlchown32, libc_sys_Xlchown32)

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uint32_t getuid32(void) */
INTERN_FUNCTION(libc_sys_Xgetuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 199, enableExcept: true) */
	b .
END(libc_sys_Xgetuid32)
DEFINE_PUBLIC_ALIAS(sys_Xgetuid32, libc_sys_Xgetuid32)

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* uint32_t getgid32(void) */
INTERN_FUNCTION(libc_sys_Xgetgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 200, enableExcept: true) */
	b .
END(libc_sys_Xgetgid32)
DEFINE_PUBLIC_ALIAS(sys_Xgetgid32, libc_sys_Xgetgid32)

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint32_t geteuid32(void) */
INTERN_FUNCTION(libc_sys_Xgeteuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 201, enableExcept: true) */
	b .
END(libc_sys_Xgeteuid32)
DEFINE_PUBLIC_ALIAS(sys_Xgeteuid32, libc_sys_Xgeteuid32)

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint32_t getegid32(void) */
INTERN_FUNCTION(libc_sys_Xgetegid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 202, enableExcept: true) */
	b .
END(libc_sys_Xgetegid32)
DEFINE_PUBLIC_ALIAS(sys_Xgetegid32, libc_sys_Xgetegid32)

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
INTERN_FUNCTION(libc_sys_Xsetreuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 203, enableExcept: true) */
	b .
END(libc_sys_Xsetreuid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetreuid32, libc_sys_Xsetreuid32)

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid32(uint32_t rgid, uint32_t egid) */
INTERN_FUNCTION(libc_sys_Xsetregid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 204, enableExcept: true) */
	b .
END(libc_sys_Xsetregid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetregid32, libc_sys_Xsetregid32)

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups32(size_t count, uint32_t[] list) */
INTERN_FUNCTION(libc_sys_Xgetgroups32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 205, enableExcept: true) */
	b .
END(libc_sys_Xgetgroups32)
DEFINE_PUBLIC_ALIAS(sys_Xgetgroups32, libc_sys_Xgetgroups32)

/* errno_t setgroups32(size_t count, uint32_t const *groups) */
INTERN_FUNCTION(libc_sys_Xsetgroups32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 206, enableExcept: true) */
	b .
END(libc_sys_Xsetgroups32)
DEFINE_PUBLIC_ALIAS(sys_Xsetgroups32, libc_sys_Xsetgroups32)

/* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
INTERN_FUNCTION(libc_sys_Xfchown32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 207, enableExcept: true) */
	b .
END(libc_sys_Xfchown32)
DEFINE_PUBLIC_ALIAS(sys_Xfchown32, libc_sys_Xfchown32)

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
INTERN_FUNCTION(libc_sys_Xsetresuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 208, enableExcept: true) */
	b .
END(libc_sys_Xsetresuid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetresuid32, libc_sys_Xsetresuid32)

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
INTERN_FUNCTION(libc_sys_Xgetresuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 209, enableExcept: true) */
	b .
END(libc_sys_Xgetresuid32)
DEFINE_PUBLIC_ALIAS(sys_Xgetresuid32, libc_sys_Xgetresuid32)

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
INTERN_FUNCTION(libc_sys_Xsetresgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 210, enableExcept: true) */
	b .
END(libc_sys_Xsetresgid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetresgid32, libc_sys_Xsetresgid32)

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
INTERN_FUNCTION(libc_sys_Xgetresgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 211, enableExcept: true) */
	b .
END(libc_sys_Xgetresgid32)
DEFINE_PUBLIC_ALIAS(sys_Xgetresgid32, libc_sys_Xgetresgid32)

/* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
INTERN_FUNCTION(libc_sys_Xchown32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 212, enableExcept: true) */
	b .
END(libc_sys_Xchown32)
DEFINE_PUBLIC_ALIAS(sys_Xchown32, libc_sys_Xchown32)

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_Xsetuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 213, enableExcept: true) */
	b .
END(libc_sys_Xsetuid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetuid32, libc_sys_Xsetuid32)

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_Xsetgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 214, enableExcept: true) */
	b .
END(libc_sys_Xsetgid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetgid32, libc_sys_Xsetgid32)

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid32(uint32_t uid) */
INTERN_FUNCTION(libc_sys_Xsetfsuid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 215, enableExcept: true) */
	b .
END(libc_sys_Xsetfsuid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsuid32, libc_sys_Xsetfsuid32)

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid32(uint32_t gid) */
INTERN_FUNCTION(libc_sys_Xsetfsgid32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 216, enableExcept: true) */
	b .
END(libc_sys_Xsetfsgid32)
DEFINE_PUBLIC_ALIAS(sys_Xsetfsgid32, libc_sys_Xsetfsgid32)

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xgetdents64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 217, enableExcept: true) */
	b .
END(libc_sys_Xgetdents64)
DEFINE_PUBLIC_ALIAS(sys_Xgetdents64, libc_sys_Xgetdents64)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpivot_root)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 218, enableExcept: true) */
	b .
END(libc_sys_Xpivot_root)
DEFINE_PUBLIC_ALIAS(sys_Xpivot_root, libc_sys_Xpivot_root)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
INTERN_FUNCTION(libc_sys_Xmincore)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 219, enableExcept: true) */
	b .
END(libc_sys_Xmincore)
DEFINE_PUBLIC_ALIAS(sys_Xmincore, libc_sys_Xmincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
INTERN_FUNCTION(libc_sys_Xmadvise)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 220, enableExcept: true) */
	b .
END(libc_sys_Xmadvise)
DEFINE_PUBLIC_ALIAS(sys_Xmadvise, libc_sys_Xmadvise)

/* syscall_slong_t fcntl64(fd_t fd, fcntl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_Xfcntl64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 221, enableExcept: true) */
	b .
END(libc_sys_Xfcntl64)
DEFINE_PUBLIC_ALIAS(sys_Xfcntl64, libc_sys_Xfcntl64)

/* pid_t gettid(void) */
INTERN_FUNCTION(libc_sys_Xgettid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 224, enableExcept: true) */
	b .
END(libc_sys_Xgettid)
DEFINE_PUBLIC_ALIAS(sys_Xgettid, libc_sys_Xgettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
INTERN_FUNCTION(libc_sys_Xreadahead)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 225, enableExcept: true) */
	b .
END(libc_sys_Xreadahead)
DEFINE_PUBLIC_ALIAS(sys_Xreadahead, libc_sys_Xreadahead)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 226, enableExcept: true) */
	b .
END(libc_sys_Xsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xsetxattr, libc_sys_Xsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xlsetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 227, enableExcept: true) */
	b .
END(libc_sys_Xlsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlsetxattr, libc_sys_Xlsetxattr)

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xfsetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 228, enableExcept: true) */
	b .
END(libc_sys_Xfsetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xfsetxattr, libc_sys_Xfsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xgetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 229, enableExcept: true) */
	b .
END(libc_sys_Xgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xgetxattr, libc_sys_Xgetxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xlgetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 230, enableExcept: true) */
	b .
END(libc_sys_Xlgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlgetxattr, libc_sys_Xlgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
INTERN_FUNCTION(libc_sys_Xfgetxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 231, enableExcept: true) */
	b .
END(libc_sys_Xfgetxattr)
DEFINE_PUBLIC_ALIAS(sys_Xfgetxattr, libc_sys_Xfgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xlistxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 232, enableExcept: true) */
	b .
END(libc_sys_Xlistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xlistxattr, libc_sys_Xlistxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xllistxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 233, enableExcept: true) */
	b .
END(libc_sys_Xllistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xllistxattr, libc_sys_Xllistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
INTERN_FUNCTION(libc_sys_Xflistxattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 234, enableExcept: true) */
	b .
END(libc_sys_Xflistxattr)
DEFINE_PUBLIC_ALIAS(sys_Xflistxattr, libc_sys_Xflistxattr)

/* errno_t removexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_Xremovexattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 235, enableExcept: true) */
	b .
END(libc_sys_Xremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xremovexattr, libc_sys_Xremovexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
INTERN_FUNCTION(libc_sys_Xlremovexattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 236, enableExcept: true) */
	b .
END(libc_sys_Xlremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xlremovexattr, libc_sys_Xlremovexattr)

/* errno_t fremovexattr(fd_t fd, char const *name) */
INTERN_FUNCTION(libc_sys_Xfremovexattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 237, enableExcept: true) */
	b .
END(libc_sys_Xfremovexattr)
DEFINE_PUBLIC_ALIAS(sys_Xfremovexattr, libc_sys_Xfremovexattr)

/* errno_t tkill(pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_Xtkill)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 238, enableExcept: true) */
	b .
END(libc_sys_Xtkill)
DEFINE_PUBLIC_ALIAS(sys_Xtkill, libc_sys_Xtkill)

/* Read up to `num_bytes' from `infd', and write that data to `outfd'
 * Files must be opened with the relevant access permissions (same as
 * would be enforced by `read(2)' and `write(2)')
 * When `pin_offset != NULL', the pointed-to location is used to track
 * the read-position in `infd'. Note that in the event that writing to
 * this address faults, data may  have still been written to  `outfd',
 * so be sure to have this point to writable memory.
 * @param: outfd:      Output file descriptor
 * @param: infd:       Input file descriptor
 * @param: pin_offset: If non-NULL, position from which to start reading,
 *                     and updated to reflect  how much could be  copied.
 * @param: num_bytes:  The max number of bytes to transfer
 * @return: * :        The actual number of bytes transferred */
/* ssize_t sendfile64(fd_t outfd, fd_t infd, __ULONG64_TYPE__ *pin_offset, size_t num_bytes) */
INTERN_FUNCTION(libc_sys_Xsendfile64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 239, enableExcept: true) */
	b .
END(libc_sys_Xsendfile64)
DEFINE_PUBLIC_ALIAS(sys_Xsendfile64, libc_sys_Xsendfile64)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
INTERN_FUNCTION(libc_sys_Xfutex)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 240, enableExcept: true) */
	b .
END(libc_sys_Xfutex)
DEFINE_PUBLIC_ALIAS(sys_Xfutex, libc_sys_Xfutex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
INTERN_FUNCTION(libc_sys_Xsched_setaffinity)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 241, enableExcept: true) */
	b .
END(libc_sys_Xsched_setaffinity)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setaffinity, libc_sys_Xsched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
INTERN_FUNCTION(libc_sys_Xsched_getaffinity)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 242, enableExcept: true) */
	b .
END(libc_sys_Xsched_getaffinity)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getaffinity, libc_sys_Xsched_getaffinity)

/* errno_t io_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_setup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 243, enableExcept: true) */
	b .
END(libc_sys_Xio_setup)
DEFINE_PUBLIC_ALIAS(sys_Xio_setup, libc_sys_Xio_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_destroy)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 244, enableExcept: true) */
	b .
END(libc_sys_Xio_destroy)
DEFINE_PUBLIC_ALIAS(sys_Xio_destroy, libc_sys_Xio_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_getevents)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 245, enableExcept: true) */
	b .
END(libc_sys_Xio_getevents)
DEFINE_PUBLIC_ALIAS(sys_Xio_getevents, libc_sys_Xio_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_submit)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 246, enableExcept: true) */
	b .
END(libc_sys_Xio_submit)
DEFINE_PUBLIC_ALIAS(sys_Xio_submit, libc_sys_Xio_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_cancel)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 247, enableExcept: true) */
	b .
END(libc_sys_Xio_cancel)
DEFINE_PUBLIC_ALIAS(sys_Xio_cancel, libc_sys_Xio_cancel)

/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit_group(syscall_ulong_t exit_code) */
INTERN_FUNCTION(libc_sys_Xexit_group)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 248, enableExcept: true) */
	b .
END(libc_sys_Xexit_group)
DEFINE_PUBLIC_ALIAS(sys_Xexit_group, libc_sys_Xexit_group)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xlookup_dcookie)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 249, enableExcept: true) */
	b .
END(libc_sys_Xlookup_dcookie)
DEFINE_PUBLIC_ALIAS(sys_Xlookup_dcookie, libc_sys_Xlookup_dcookie)

/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
/* fd_t epoll_create(syscall_ulong_t size) */
INTERN_FUNCTION(libc_sys_Xepoll_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 250, enableExcept: true) */
	b .
END(libc_sys_Xepoll_create)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_create, libc_sys_Xepoll_create)

/* >> epoll_ctl(2)
 * Manipulate a given  epoll controller  `epfd', as previously  returned by  `epoll_create1(2)'
 * in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
 * the file descriptors being monitored
 * @param: op:       One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
 * @param: fd:       The file descriptor to add/remove/modify
 * @param: info:     The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
 * @return: 0 :      Success
 * @return: -EEXIST: [op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
 * @return: -ENOENT: [op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
 * @throw: E_ILLEGAL_REFERENCE_LOOP: The  given  `fd'  is  another  epoll  that either
 *                                   forms a loop with `epfd', or has too many nested.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...] */
/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
INTERN_FUNCTION(libc_sys_Xepoll_ctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 251, enableExcept: true) */
	b .
END(libc_sys_Xepoll_ctl)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_ctl, libc_sys_Xepoll_ctl)

/* >> epoll_wait(2)
 * Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_wait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
INTERN_FUNCTION(libc_sys_Xepoll_wait)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 252, enableExcept: true) */
	b .
END(libc_sys_Xepoll_wait)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_wait, libc_sys_Xepoll_wait)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xremap_file_pages)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 253, enableExcept: true) */
	b .
END(libc_sys_Xremap_file_pages)
DEFINE_PUBLIC_ALIAS(sys_Xremap_file_pages, libc_sys_Xremap_file_pages)

/* pid_t set_tid_address(pid_t *tidptr) */
INTERN_FUNCTION(libc_sys_Xset_tid_address)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 256, enableExcept: true) */
	b .
END(libc_sys_Xset_tid_address)
DEFINE_PUBLIC_ALIAS(sys_Xset_tid_address, libc_sys_Xset_tid_address)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 257, enableExcept: true) */
	b .
END(libc_sys_Xtimer_create)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_create, libc_sys_Xtimer_create)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspec32 const *value, struct itimerspec32 *ovalue) */
INTERN_FUNCTION(libc_sys_Xtimer_settime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 258, enableExcept: true) */
	b .
END(libc_sys_Xtimer_settime)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_settime, libc_sys_Xtimer_settime)

/* errno_t timer_gettime(timer_t timerid, struct itimerspec32 *value) */
INTERN_FUNCTION(libc_sys_Xtimer_gettime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 259, enableExcept: true) */
	b .
END(libc_sys_Xtimer_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_gettime, libc_sys_Xtimer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_getoverrun)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 260, enableExcept: true) */
	b .
END(libc_sys_Xtimer_getoverrun)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_getoverrun, libc_sys_Xtimer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
INTERN_FUNCTION(libc_sys_Xtimer_delete)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 261, enableExcept: true) */
	b .
END(libc_sys_Xtimer_delete)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_delete, libc_sys_Xtimer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct timespec32 const *tp) */
INTERN_FUNCTION(libc_sys_Xclock_settime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 262, enableExcept: true) */
	b .
END(libc_sys_Xclock_settime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_settime, libc_sys_Xclock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct timespec32 *tp) */
INTERN_FUNCTION(libc_sys_Xclock_gettime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 263, enableExcept: true) */
	b .
END(libc_sys_Xclock_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_gettime, libc_sys_Xclock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct timespec32 *res) */
INTERN_FUNCTION(libc_sys_Xclock_getres)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 264, enableExcept: true) */
	b .
END(libc_sys_Xclock_getres)
DEFINE_PUBLIC_ALIAS(sys_Xclock_getres, libc_sys_Xclock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespec32 const *requested_time, struct timespec32 *remaining) */
INTERN_FUNCTION(libc_sys_Xclock_nanosleep)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 265, enableExcept: true) */
	b .
END(libc_sys_Xclock_nanosleep)
DEFINE_PUBLIC_ALIAS(sys_Xclock_nanosleep, libc_sys_Xclock_nanosleep)

/* errno_t statfs64(char const *file, struct __statfs64 *buf) */
INTERN_FUNCTION(libc_sys_Xstatfs64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 266, enableExcept: true) */
	b .
END(libc_sys_Xstatfs64)
DEFINE_PUBLIC_ALIAS(sys_Xstatfs64, libc_sys_Xstatfs64)

/* errno_t fstatfs64(fd_t file, struct __statfs64 *buf) */
INTERN_FUNCTION(libc_sys_Xfstatfs64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 267, enableExcept: true) */
	b .
END(libc_sys_Xfstatfs64)
DEFINE_PUBLIC_ALIAS(sys_Xfstatfs64, libc_sys_Xfstatfs64)

/* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
INTERN_FUNCTION(libc_sys_Xtgkill)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 268, enableExcept: true) */
	b .
END(libc_sys_Xtgkill)
DEFINE_PUBLIC_ALIAS(sys_Xtgkill, libc_sys_Xtgkill)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes(char const *filename, struct timeval32 const[2] times) */
INTERN_FUNCTION(libc_sys_Xutimes)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 269, enableExcept: true) */
	b .
END(libc_sys_Xutimes)
DEFINE_PUBLIC_ALIAS(sys_Xutimes, libc_sys_Xutimes)

/* errno_t arm_fadvise64_64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xarm_fadvise64_64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 270, enableExcept: true) */
	b .
END(libc_sys_Xarm_fadvise64_64)
DEFINE_PUBLIC_ALIAS(sys_Xarm_fadvise64_64, libc_sys_Xarm_fadvise64_64)

/* errno_t pciconfig_iobase(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpciconfig_iobase)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 271, enableExcept: true) */
	b .
END(libc_sys_Xpciconfig_iobase)
DEFINE_PUBLIC_ALIAS(sys_Xpciconfig_iobase, libc_sys_Xpciconfig_iobase)

/* errno_t pciconfig_read(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpciconfig_read)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 272, enableExcept: true) */
	b .
END(libc_sys_Xpciconfig_read)
DEFINE_PUBLIC_ALIAS(sys_Xpciconfig_read, libc_sys_Xpciconfig_read)

/* errno_t pciconfig_write(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpciconfig_write)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 273, enableExcept: true) */
	b .
END(libc_sys_Xpciconfig_write)
DEFINE_PUBLIC_ALIAS(sys_Xpciconfig_write, libc_sys_Xpciconfig_write)

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmq_open)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 274, enableExcept: true) */
	b .
END(libc_sys_Xmq_open)
DEFINE_PUBLIC_ALIAS(sys_Xmq_open, libc_sys_Xmq_open)

/* errno_t mq_unlink(char const *name) */
INTERN_FUNCTION(libc_sys_Xmq_unlink)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 275, enableExcept: true) */
	b .
END(libc_sys_Xmq_unlink)
DEFINE_PUBLIC_ALIAS(sys_Xmq_unlink, libc_sys_Xmq_unlink)

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec32 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_Xmq_timedsend)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 276, enableExcept: true) */
	b .
END(libc_sys_Xmq_timedsend)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedsend, libc_sys_Xmq_timedsend)

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec32 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_Xmq_timedreceive)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 277, enableExcept: true) */
	b .
END(libc_sys_Xmq_timedreceive)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedreceive, libc_sys_Xmq_timedreceive)

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
INTERN_FUNCTION(libc_sys_Xmq_notify)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 278, enableExcept: true) */
	b .
END(libc_sys_Xmq_notify)
DEFINE_PUBLIC_ALIAS(sys_Xmq_notify, libc_sys_Xmq_notify)

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
INTERN_FUNCTION(libc_sys_Xmq_getsetattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 279, enableExcept: true) */
	b .
END(libc_sys_Xmq_getsetattr)
DEFINE_PUBLIC_ALIAS(sys_Xmq_getsetattr, libc_sys_Xmq_getsetattr)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
INTERN_FUNCTION(libc_sys_Xwaitid)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 280, enableExcept: true) */
	b .
END(libc_sys_Xwaitid)
DEFINE_PUBLIC_ALIAS(sys_Xwaitid, libc_sys_Xwaitid)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
INTERN_FUNCTION(libc_sys_Xsocket)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 281, enableExcept: true) */
	b .
END(libc_sys_Xsocket)
DEFINE_PUBLIC_ALIAS(sys_Xsocket, libc_sys_Xsocket)

/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xbind)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 282, enableExcept: true) */
	b .
END(libc_sys_Xbind)
DEFINE_PUBLIC_ALIAS(sys_Xbind, libc_sys_Xbind)

/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that  will implicitly be  used as destination  by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xconnect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 283, enableExcept: true) */
	b .
END(libc_sys_Xconnect)
DEFINE_PUBLIC_ALIAS(sys_Xconnect, libc_sys_Xconnect)

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
INTERN_FUNCTION(libc_sys_Xlisten)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 284, enableExcept: true) */
	b .
END(libc_sys_Xlisten)
DEFINE_PUBLIC_ALIAS(sys_Xlisten, libc_sys_Xlisten)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] Don't fill in the client's peer address
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The  amount  of required  memory for  the address.
 *                           This  may be  more than  was given,  in which case
 *                           the  address  was  truncated and  may  be invalid.
 *                           If this happens,  the caller  can still  determine
 *                           the correct address through use of `getpeername()'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xaccept)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 285, enableExcept: true) */
	b .
END(libc_sys_Xaccept)
DEFINE_PUBLIC_ALIAS(sys_Xaccept, libc_sys_Xaccept)

/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This  is usually the  same address as was  previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly  undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * return: 0 : Success */
/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xgetsockname)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 286, enableExcept: true) */
	b .
END(libc_sys_Xgetsockname)
DEFINE_PUBLIC_ALIAS(sys_Xgetsockname, libc_sys_Xgetsockname)

/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xgetpeername)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 287, enableExcept: true) */
	b .
END(libc_sys_Xgetpeername)
DEFINE_PUBLIC_ALIAS(sys_Xgetpeername, libc_sys_Xgetpeername)

/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument.  for  example,  `AF_INET' takes  one  of  `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
INTERN_FUNCTION(libc_sys_Xsocketpair)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 288, enableExcept: true) */
	b .
END(libc_sys_Xsocketpair)
DEFINE_PUBLIC_ALIAS(sys_Xsocketpair, libc_sys_Xsocketpair)

/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t send(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xsend)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 289, enableExcept: true) */
	b .
END(libc_sys_Xsend)
DEFINE_PUBLIC_ALIAS(sys_Xsend, libc_sys_Xsend)

/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for            `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
INTERN_FUNCTION(libc_sys_Xsendto)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 290, enableExcept: true) */
	b .
END(libc_sys_Xsendto)
DEFINE_PUBLIC_ALIAS(sys_Xsendto, libc_sys_Xsendto)

/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recv(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xrecv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 291, enableExcept: true) */
	b .
END(libc_sys_Xrecv)
DEFINE_PUBLIC_ALIAS(sys_Xrecv, libc_sys_Xrecv)

/* Receive data over this socket, and store the contents within the given buffer.
 * @param: buf:       Buffer to-be filled with up to `bufsize' bytes of received data
 * @param: bufsize:   Max # of bytes to receive
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @param: addr:      Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:  [NULL] behave as an alias for `recv(sockfd, buf, bufsize, msg_flags)'
 *                    [in]   The amount of available memory starting at `addr'
 *                    [out]  The amount of required memory for the address.
 *                           This may be more than was given, in which case
 *                           the address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
INTERN_FUNCTION(libc_sys_Xrecvfrom)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 292, enableExcept: true) */
	b .
END(libc_sys_Xrecvfrom)
DEFINE_PUBLIC_ALIAS(sys_Xrecvfrom, libc_sys_Xrecvfrom)

/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
INTERN_FUNCTION(libc_sys_Xshutdown)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 293, enableExcept: true) */
	b .
END(libc_sys_Xshutdown)
DEFINE_PUBLIC_ALIAS(sys_Xshutdown, libc_sys_Xshutdown)

/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
INTERN_FUNCTION(libc_sys_Xsetsockopt)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 294, enableExcept: true) */
	b .
END(libc_sys_Xsetsockopt)
DEFINE_PUBLIC_ALIAS(sys_Xsetsockopt, libc_sys_Xsetsockopt)

/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the  contents  of   `optval'  are   undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
INTERN_FUNCTION(libc_sys_Xgetsockopt)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 295, enableExcept: true) */
	b .
END(libc_sys_Xgetsockopt)
DEFINE_PUBLIC_ALIAS(sys_Xgetsockopt, libc_sys_Xgetsockopt)

/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xsendmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 296, enableExcept: true) */
	b .
END(libc_sys_Xsendmsg)
DEFINE_PUBLIC_ALIAS(sys_Xsendmsg, libc_sys_Xsendmsg)

/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xrecvmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 297, enableExcept: true) */
	b .
END(libc_sys_Xrecvmsg)
DEFINE_PUBLIC_ALIAS(sys_Xrecvmsg, libc_sys_Xrecvmsg)

/* errno_t semop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemop)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 298, enableExcept: true) */
	b .
END(libc_sys_Xsemop)
DEFINE_PUBLIC_ALIAS(sys_Xsemop, libc_sys_Xsemop)

/* errno_t semget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 299, enableExcept: true) */
	b .
END(libc_sys_Xsemget)
DEFINE_PUBLIC_ALIAS(sys_Xsemget, libc_sys_Xsemget)

/* errno_t semctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 300, enableExcept: true) */
	b .
END(libc_sys_Xsemctl)
DEFINE_PUBLIC_ALIAS(sys_Xsemctl, libc_sys_Xsemctl)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgsnd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 301, enableExcept: true) */
	b .
END(libc_sys_Xmsgsnd)
DEFINE_PUBLIC_ALIAS(sys_Xmsgsnd, libc_sys_Xmsgsnd)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgrcv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 302, enableExcept: true) */
	b .
END(libc_sys_Xmsgrcv)
DEFINE_PUBLIC_ALIAS(sys_Xmsgrcv, libc_sys_Xmsgrcv)

/* errno_t msgget(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 303, enableExcept: true) */
	b .
END(libc_sys_Xmsgget)
DEFINE_PUBLIC_ALIAS(sys_Xmsgget, libc_sys_Xmsgget)

/* errno_t msgctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmsgctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 304, enableExcept: true) */
	b .
END(libc_sys_Xmsgctl)
DEFINE_PUBLIC_ALIAS(sys_Xmsgctl, libc_sys_Xmsgctl)

/* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_Xshmat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 305, enableExcept: true) */
	b .
END(libc_sys_Xshmat)
DEFINE_PUBLIC_ALIAS(sys_Xshmat, libc_sys_Xshmat)

/* errno_t shmdt(void const *shmaddr) */
INTERN_FUNCTION(libc_sys_Xshmdt)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 306, enableExcept: true) */
	b .
END(libc_sys_Xshmdt)
DEFINE_PUBLIC_ALIAS(sys_Xshmdt, libc_sys_Xshmdt)

/* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
INTERN_FUNCTION(libc_sys_Xshmget)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 307, enableExcept: true) */
	b .
END(libc_sys_Xshmget)
DEFINE_PUBLIC_ALIAS(sys_Xshmget, libc_sys_Xshmget)

/* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
INTERN_FUNCTION(libc_sys_Xshmctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 308, enableExcept: true) */
	b .
END(libc_sys_Xshmctl)
DEFINE_PUBLIC_ALIAS(sys_Xshmctl, libc_sys_Xshmctl)

/* errno_t add_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xadd_key)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 309, enableExcept: true) */
	b .
END(libc_sys_Xadd_key)
DEFINE_PUBLIC_ALIAS(sys_Xadd_key, libc_sys_Xadd_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xrequest_key)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 310, enableExcept: true) */
	b .
END(libc_sys_Xrequest_key)
DEFINE_PUBLIC_ALIAS(sys_Xrequest_key, libc_sys_Xrequest_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xkeyctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 311, enableExcept: true) */
	b .
END(libc_sys_Xkeyctl)
DEFINE_PUBLIC_ALIAS(sys_Xkeyctl, libc_sys_Xkeyctl)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemtimedop)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 312, enableExcept: true) */
	b .
END(libc_sys_Xsemtimedop)
DEFINE_PUBLIC_ALIAS(sys_Xsemtimedop, libc_sys_Xsemtimedop)

/* errno_t vserve(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xvserve)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 313, enableExcept: true) */
	b .
END(libc_sys_Xvserve)
DEFINE_PUBLIC_ALIAS(sys_Xvserve, libc_sys_Xvserve)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
INTERN_FUNCTION(libc_sys_Xioprio_set)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 314, enableExcept: true) */
	b .
END(libc_sys_Xioprio_set)
DEFINE_PUBLIC_ALIAS(sys_Xioprio_set, libc_sys_Xioprio_set)

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
INTERN_FUNCTION(libc_sys_Xioprio_get)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 315, enableExcept: true) */
	b .
END(libc_sys_Xioprio_get)
DEFINE_PUBLIC_ALIAS(sys_Xioprio_get, libc_sys_Xioprio_get)

/* fd_t inotify_init(void) */
INTERN_FUNCTION(libc_sys_Xinotify_init)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 316, enableExcept: true) */
	b .
END(libc_sys_Xinotify_init)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_init, libc_sys_Xinotify_init)

/* @param: mask: Set of `IN_ALL_EVENTS | ...' */
/* int inotify_add_watch(fd_t notify_fd, char const *pathname, uint32_t mask) */
INTERN_FUNCTION(libc_sys_Xinotify_add_watch)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 317, enableExcept: true) */
	b .
END(libc_sys_Xinotify_add_watch)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_add_watch, libc_sys_Xinotify_add_watch)

/* @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
/* errno_t inotify_rm_watch(fd_t notify_fd, int wd) */
INTERN_FUNCTION(libc_sys_Xinotify_rm_watch)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 318, enableExcept: true) */
	b .
END(libc_sys_Xinotify_rm_watch)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_rm_watch, libc_sys_Xinotify_rm_watch)

/* errno_t mbind(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmbind)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 319, enableExcept: true) */
	b .
END(libc_sys_Xmbind)
DEFINE_PUBLIC_ALIAS(sys_Xmbind, libc_sys_Xmbind)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xget_mempolicy)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 320, enableExcept: true) */
	b .
END(libc_sys_Xget_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_Xget_mempolicy, libc_sys_Xget_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xset_mempolicy)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 321, enableExcept: true) */
	b .
END(libc_sys_Xset_mempolicy)
DEFINE_PUBLIC_ALIAS(sys_Xset_mempolicy, libc_sys_Xset_mempolicy)

/* Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xopenat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 322, enableExcept: true) */
	b .
END(libc_sys_Xopenat)
DEFINE_PUBLIC_ALIAS(sys_Xopenat, libc_sys_Xopenat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
INTERN_FUNCTION(libc_sys_Xmkdirat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 323, enableExcept: true) */
	b .
END(libc_sys_Xmkdirat)
DEFINE_PUBLIC_ALIAS(sys_Xmkdirat, libc_sys_Xmkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
INTERN_FUNCTION(libc_sys_Xmknodat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 324, enableExcept: true) */
	b .
END(libc_sys_Xmknodat)
DEFINE_PUBLIC_ALIAS(sys_Xmknodat, libc_sys_Xmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchownat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 325, enableExcept: true) */
	b .
END(libc_sys_Xfchownat)
DEFINE_PUBLIC_ALIAS(sys_Xfchownat, libc_sys_Xfchownat)

/* errno_t futimesat(fd_t dirfd, char const *filename, struct timeval32 const[2] times) */
INTERN_FUNCTION(libc_sys_Xfutimesat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 326, enableExcept: true) */
	b .
END(libc_sys_Xfutimesat)
DEFINE_PUBLIC_ALIAS(sys_Xfutimesat, libc_sys_Xfutimesat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfstatat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 327, enableExcept: true) */
	b .
END(libc_sys_Xfstatat64)
DEFINE_PUBLIC_ALIAS(sys_Xfstatat64, libc_sys_Xfstatat64)

/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xunlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 328, enableExcept: true) */
	b .
END(libc_sys_Xunlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xunlinkat, libc_sys_Xunlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
INTERN_FUNCTION(libc_sys_Xrenameat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 329, enableExcept: true) */
	b .
END(libc_sys_Xrenameat)
DEFINE_PUBLIC_ALIAS(sys_Xrenameat, libc_sys_Xrenameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 330, enableExcept: true) */
	b .
END(libc_sys_Xlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xlinkat, libc_sys_Xlinkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
INTERN_FUNCTION(libc_sys_Xsymlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 331, enableExcept: true) */
	b .
END(libc_sys_Xsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xsymlinkat, libc_sys_Xsymlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
INTERN_FUNCTION(libc_sys_Xreadlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 332, enableExcept: true) */
	b .
END(libc_sys_Xreadlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xreadlinkat, libc_sys_Xreadlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchmodat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 333, enableExcept: true) */
	b .
END(libc_sys_Xfchmodat)
DEFINE_PUBLIC_ALIAS(sys_Xfchmodat, libc_sys_Xfchmodat)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
INTERN_FUNCTION(libc_sys_Xfaccessat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 334, enableExcept: true) */
	b .
END(libc_sys_Xfaccessat)
DEFINE_PUBLIC_ALIAS(sys_Xfaccessat, libc_sys_Xfaccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec32 const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
INTERN_FUNCTION(libc_sys_Xpselect6)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 335, enableExcept: true) */
	b .
END(libc_sys_Xpselect6)
DEFINE_PUBLIC_ALIAS(sys_Xpselect6, libc_sys_Xpselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xppoll)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 336, enableExcept: true) */
	b .
END(libc_sys_Xppoll)
DEFINE_PUBLIC_ALIAS(sys_Xppoll, libc_sys_Xppoll)

/* param: what: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t what) */
INTERN_FUNCTION(libc_sys_Xunshare)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 337, enableExcept: true) */
	b .
END(libc_sys_Xunshare)
DEFINE_PUBLIC_ALIAS(sys_Xunshare, libc_sys_Xunshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xset_robust_list)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 338, enableExcept: true) */
	b .
END(libc_sys_Xset_robust_list)
DEFINE_PUBLIC_ALIAS(sys_Xset_robust_list, libc_sys_Xset_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xget_robust_list)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 339, enableExcept: true) */
	b .
END(libc_sys_Xget_robust_list)
DEFINE_PUBLIC_ALIAS(sys_Xget_robust_list, libc_sys_Xget_robust_list)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsplice)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 340, enableExcept: true) */
	b .
END(libc_sys_Xsplice)
DEFINE_PUBLIC_ALIAS(sys_Xsplice, libc_sys_Xsplice)

/* errno_t arm_sync_file_range(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xarm_sync_file_range)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 341, enableExcept: true) */
	b .
END(libc_sys_Xarm_sync_file_range)
DEFINE_PUBLIC_ALIAS(sys_Xarm_sync_file_range, libc_sys_Xarm_sync_file_range)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xtee)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 342, enableExcept: true) */
	b .
END(libc_sys_Xtee)
DEFINE_PUBLIC_ALIAS(sys_Xtee, libc_sys_Xtee)

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xvmsplice)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 343, enableExcept: true) */
	b .
END(libc_sys_Xvmsplice)
DEFINE_PUBLIC_ALIAS(sys_Xvmsplice, libc_sys_Xvmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmove_pages)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 344, enableExcept: true) */
	b .
END(libc_sys_Xmove_pages)
DEFINE_PUBLIC_ALIAS(sys_Xmove_pages, libc_sys_Xmove_pages)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
INTERN_FUNCTION(libc_sys_Xgetcpu)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 345, enableExcept: true) */
	b .
END(libc_sys_Xgetcpu)
DEFINE_PUBLIC_ALIAS(sys_Xgetcpu, libc_sys_Xgetcpu)

/* >> epoll_pwait(2)
 * Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
 * waiting.  Wait until at least one of the conditions monitored by `epfd' to be met.
 * @param: epfd:      The epoll controller on which to wait.
 * @param: events:    A buffer where the kernel can store information on the
 *                    events that actually took place.
 * @param: maxevents: The # of events that can be stored in `events' (must be >= 1)
 * @param: timeout:   The max amount of time (in milliseconds) before  returning
 *                    in the case where no event occurred in the mean time. When
 *                    set to `-1', wait indefinitely
 * @param: ss:        The signal mask to apply while waiting for an event to happen.
 * @return: >= 1:     The # of events that happened (written to the first `return'
 *                    items of `events')
 * @return: 0:        No events happened before `timeout' expired.
 * @return: -1:       Error (s.a. `errno') */
/* ssize_t epoll_pwait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xepoll_pwait)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 346, enableExcept: true) */
	b .
END(libc_sys_Xepoll_pwait)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_pwait, libc_sys_Xepoll_pwait)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xkexec_load)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 347, enableExcept: true) */
	b .
END(libc_sys_Xkexec_load)
DEFINE_PUBLIC_ALIAS(sys_Xkexec_load, libc_sys_Xkexec_load)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct timespec32 const[2] times, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xutimensat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 348, enableExcept: true) */
	b .
END(libc_sys_Xutimensat)
DEFINE_PUBLIC_ALIAS(sys_Xutimensat, libc_sys_Xutimensat)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
INTERN_FUNCTION(libc_sys_Xsignalfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 349, enableExcept: true) */
	b .
END(libc_sys_Xsignalfd)
DEFINE_PUBLIC_ALIAS(sys_Xsignalfd, libc_sys_Xsignalfd)

/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xtimerfd_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 350, enableExcept: true) */
	b .
END(libc_sys_Xtimerfd_create)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_create, libc_sys_Xtimerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
INTERN_FUNCTION(libc_sys_Xeventfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 351, enableExcept: true) */
	b .
END(libc_sys_Xeventfd)
DEFINE_PUBLIC_ALIAS(sys_Xeventfd, libc_sys_Xeventfd)

/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
INTERN_FUNCTION(libc_sys_Xfallocate)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 352, enableExcept: true) */
	b .
END(libc_sys_Xfallocate)
DEFINE_PUBLIC_ALIAS(sys_Xfallocate, libc_sys_Xfallocate)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspec32 const *utmr, struct itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_settime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 353, enableExcept: true) */
	b .
END(libc_sys_Xtimerfd_settime)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_settime, libc_sys_Xtimerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t timerfd, struct itimerspec32 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_gettime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 354, enableExcept: true) */
	b .
END(libc_sys_Xtimerfd_gettime)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_gettime, libc_sys_Xtimerfd_gettime)

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xsignalfd4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 355, enableExcept: true) */
	b .
END(libc_sys_Xsignalfd4)
DEFINE_PUBLIC_ALIAS(sys_Xsignalfd4, libc_sys_Xsignalfd4)

/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xeventfd2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 356, enableExcept: true) */
	b .
END(libc_sys_Xeventfd2)
DEFINE_PUBLIC_ALIAS(sys_Xeventfd2, libc_sys_Xeventfd2)

/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
/* fd_t epoll_create1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xepoll_create1)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 357, enableExcept: true) */
	b .
END(libc_sys_Xepoll_create1)
DEFINE_PUBLIC_ALIAS(sys_Xepoll_create1, libc_sys_Xepoll_create1)

/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xdup3)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 358, enableExcept: true) */
	b .
END(libc_sys_Xdup3)
DEFINE_PUBLIC_ALIAS(sys_Xdup3, libc_sys_Xdup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xpipe2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 359, enableExcept: true) */
	b .
END(libc_sys_Xpipe2)
DEFINE_PUBLIC_ALIAS(sys_Xpipe2, libc_sys_Xpipe2)

/* @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
/* fd_t inotify_init1(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xinotify_init1)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 360, enableExcept: true) */
	b .
END(libc_sys_Xinotify_init1)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_init1, libc_sys_Xinotify_init1)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpreadv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 361, enableExcept: true) */
	b .
END(libc_sys_Xpreadv)
DEFINE_PUBLIC_ALIAS(sys_Xpreadv, libc_sys_Xpreadv)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
INTERN_FUNCTION(libc_sys_Xpwritev)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 362, enableExcept: true) */
	b .
END(libc_sys_Xpwritev)
DEFINE_PUBLIC_ALIAS(sys_Xpwritev, libc_sys_Xpwritev)

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfo_struct const *uinfo) */
INTERN_FUNCTION(libc_sys_Xrt_tgsigqueueinfo)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 363, enableExcept: true) */
	b .
END(libc_sys_Xrt_tgsigqueueinfo)
DEFINE_PUBLIC_ALIAS(sys_Xrt_tgsigqueueinfo, libc_sys_Xrt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xperf_event_open)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 364, enableExcept: true) */
	b .
END(libc_sys_Xperf_event_open)
DEFINE_PUBLIC_ALIAS(sys_Xperf_event_open, libc_sys_Xperf_event_open)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr32 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec32 const *tmo) */
INTERN_FUNCTION(libc_sys_Xrecvmmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 365, enableExcept: true) */
	b .
END(libc_sys_Xrecvmmsg)
DEFINE_PUBLIC_ALIAS(sys_Xrecvmmsg, libc_sys_Xrecvmmsg)

/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The  amount  of required  memory for  the address.
 *                            This  may be  more than  was given,  in which case
 *                            the  address  was  truncated and  may  be invalid.
 *                            If this happens,  the caller  can still  determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_ACCEPT_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
INTERN_FUNCTION(libc_sys_Xaccept4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 366, enableExcept: true) */
	b .
END(libc_sys_Xaccept4)
DEFINE_PUBLIC_ALIAS(sys_Xaccept4, libc_sys_Xaccept4)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfanotify_init)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 367, enableExcept: true) */
	b .
END(libc_sys_Xfanotify_init)
DEFINE_PUBLIC_ALIAS(sys_Xfanotify_init, libc_sys_Xfanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfanotify_mark)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 368, enableExcept: true) */
	b .
END(libc_sys_Xfanotify_mark)
DEFINE_PUBLIC_ALIAS(sys_Xfanotify_mark, libc_sys_Xfanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
INTERN_FUNCTION(libc_sys_Xprlimit64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 369, enableExcept: true) */
	b .
END(libc_sys_Xprlimit64)
DEFINE_PUBLIC_ALIAS(sys_Xprlimit64, libc_sys_Xprlimit64)

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xname_to_handle_at)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 370, enableExcept: true) */
	b .
END(libc_sys_Xname_to_handle_at)
DEFINE_PUBLIC_ALIAS(sys_Xname_to_handle_at, libc_sys_Xname_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
INTERN_FUNCTION(libc_sys_Xopen_by_handle_at)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 371, enableExcept: true) */
	b .
END(libc_sys_Xopen_by_handle_at)
DEFINE_PUBLIC_ALIAS(sys_Xopen_by_handle_at, libc_sys_Xopen_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xclock_adjtime)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 372, enableExcept: true) */
	b .
END(libc_sys_Xclock_adjtime)
DEFINE_PUBLIC_ALIAS(sys_Xclock_adjtime, libc_sys_Xclock_adjtime)

/* errno_t syncfs(fd_t fd) */
INTERN_FUNCTION(libc_sys_Xsyncfs)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 373, enableExcept: true) */
	b .
END(libc_sys_Xsyncfs)
DEFINE_PUBLIC_ALIAS(sys_Xsyncfs, libc_sys_Xsyncfs)

/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
INTERN_FUNCTION(libc_sys_Xsendmmsg)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 374, enableExcept: true) */
	b .
END(libc_sys_Xsendmmsg)
DEFINE_PUBLIC_ALIAS(sys_Xsendmmsg, libc_sys_Xsendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
INTERN_FUNCTION(libc_sys_Xsetns)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 375, enableExcept: true) */
	b .
END(libc_sys_Xsetns)
DEFINE_PUBLIC_ALIAS(sys_Xsetns, libc_sys_Xsetns)

/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
/* ssize_t process_vm_readv(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xprocess_vm_readv)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 376, enableExcept: true) */
	b .
END(libc_sys_Xprocess_vm_readv)
DEFINE_PUBLIC_ALIAS(sys_Xprocess_vm_readv, libc_sys_Xprocess_vm_readv)

/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
/* ssize_t process_vm_writev(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xprocess_vm_writev)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 377, enableExcept: true) */
	b .
END(libc_sys_Xprocess_vm_writev)
DEFINE_PUBLIC_ALIAS(sys_Xprocess_vm_writev, libc_sys_Xprocess_vm_writev)

/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
INTERN_FUNCTION(libc_sys_Xkcmp)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 378, enableExcept: true) */
	b .
END(libc_sys_Xkcmp)
DEFINE_PUBLIC_ALIAS(sys_Xkcmp, libc_sys_Xkcmp)

/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
/* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xfinit_module)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 379, enableExcept: true) */
	b .
END(libc_sys_Xfinit_module)
DEFINE_PUBLIC_ALIAS(sys_Xfinit_module, libc_sys_Xfinit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsched_setattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 380, enableExcept: true) */
	b .
END(libc_sys_Xsched_setattr)
DEFINE_PUBLIC_ALIAS(sys_Xsched_setattr, libc_sys_Xsched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsched_getattr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 381, enableExcept: true) */
	b .
END(libc_sys_Xsched_getattr)
DEFINE_PUBLIC_ALIAS(sys_Xsched_getattr, libc_sys_Xsched_getattr)

/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xrenameat2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 382, enableExcept: true) */
	b .
END(libc_sys_Xrenameat2)
DEFINE_PUBLIC_ALIAS(sys_Xrenameat2, libc_sys_Xrenameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xseccomp)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 383, enableExcept: true) */
	b .
END(libc_sys_Xseccomp)
DEFINE_PUBLIC_ALIAS(sys_Xseccomp, libc_sys_Xseccomp)

/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
/* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xgetrandom)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 384, enableExcept: true) */
	b .
END(libc_sys_Xgetrandom)
DEFINE_PUBLIC_ALIAS(sys_Xgetrandom, libc_sys_Xgetrandom)

/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
/* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmemfd_create)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 385, enableExcept: true) */
	b .
END(libc_sys_Xmemfd_create)
DEFINE_PUBLIC_ALIAS(sys_Xmemfd_create, libc_sys_Xmemfd_create)

/* errno_t bpf(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xbpf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 386, enableExcept: true) */
	b .
END(libc_sys_Xbpf)
DEFINE_PUBLIC_ALIAS(sys_Xbpf, libc_sys_Xbpf)

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xexecveat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 387, enableExcept: true) */
	b .
END(libc_sys_Xexecveat)
DEFINE_PUBLIC_ALIAS(sys_Xexecveat, libc_sys_Xexecveat)

/* fd_t userfaultfd(syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xuserfaultfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 388, enableExcept: true) */
	b .
END(libc_sys_Xuserfaultfd)
DEFINE_PUBLIC_ALIAS(sys_Xuserfaultfd, libc_sys_Xuserfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmembarrier)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 389, enableExcept: true) */
	b .
END(libc_sys_Xmembarrier)
DEFINE_PUBLIC_ALIAS(sys_Xmembarrier, libc_sys_Xmembarrier)

/* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xmlock2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 390, enableExcept: true) */
	b .
END(libc_sys_Xmlock2)
DEFINE_PUBLIC_ALIAS(sys_Xmlock2, libc_sys_Xmlock2)

/* errno_t copy_file_range(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xcopy_file_range)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 391, enableExcept: true) */
	b .
END(libc_sys_Xcopy_file_range)
DEFINE_PUBLIC_ALIAS(sys_Xcopy_file_range, libc_sys_Xcopy_file_range)

/* errno_t preadv2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpreadv2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 392, enableExcept: true) */
	b .
END(libc_sys_Xpreadv2)
DEFINE_PUBLIC_ALIAS(sys_Xpreadv2, libc_sys_Xpreadv2)

/* errno_t pwritev2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xpwritev2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 393, enableExcept: true) */
	b .
END(libc_sys_Xpwritev2)
DEFINE_PUBLIC_ALIAS(sys_Xpwritev2, libc_sys_Xpwritev2)

/* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
INTERN_FUNCTION(libc_sys_Xpkey_mprotect)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 394, enableExcept: true) */
	b .
END(libc_sys_Xpkey_mprotect)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_mprotect, libc_sys_Xpkey_mprotect)

/* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
INTERN_FUNCTION(libc_sys_Xpkey_alloc)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 395, enableExcept: true) */
	b .
END(libc_sys_Xpkey_alloc)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_alloc, libc_sys_Xpkey_alloc)

/* errno_t pkey_free(syscall_ulong_t key) */
INTERN_FUNCTION(libc_sys_Xpkey_free)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 396, enableExcept: true) */
	b .
END(libc_sys_Xpkey_free)
DEFINE_PUBLIC_ALIAS(sys_Xpkey_free, libc_sys_Xpkey_free)

/* errno_t statx(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xstatx)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 397, enableExcept: true) */
	b .
END(libc_sys_Xstatx)
DEFINE_PUBLIC_ALIAS(sys_Xstatx, libc_sys_Xstatx)

/* errno_t rseq(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xrseq)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 398, enableExcept: true) */
	b .
END(libc_sys_Xrseq)
DEFINE_PUBLIC_ALIAS(sys_Xrseq, libc_sys_Xrseq)

/* errno_t io_pgetevents(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_pgetevents)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 399, enableExcept: true) */
	b .
END(libc_sys_Xio_pgetevents)
DEFINE_PUBLIC_ALIAS(sys_Xio_pgetevents, libc_sys_Xio_pgetevents)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmigrate_pages)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 400, enableExcept: true) */
	b .
END(libc_sys_Xmigrate_pages)
DEFINE_PUBLIC_ALIAS(sys_Xmigrate_pages, libc_sys_Xmigrate_pages)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xkexec_file_load)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 401, enableExcept: true) */
	b .
END(libc_sys_Xkexec_file_load)
DEFINE_PUBLIC_ALIAS(sys_Xkexec_file_load, libc_sys_Xkexec_file_load)

/* errno_t clock_gettime64(clockid_t clock_id, struct timespec64 *tp) */
INTERN_FUNCTION(libc_sys_Xclock_gettime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 403, enableExcept: true) */
	b .
END(libc_sys_Xclock_gettime64)
DEFINE_PUBLIC_ALIAS(sys_Xclock_gettime64, libc_sys_Xclock_gettime64)

/* errno_t clock_settime64(clockid_t clock_id, struct timespec64 const *tp) */
INTERN_FUNCTION(libc_sys_Xclock_settime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 404, enableExcept: true) */
	b .
END(libc_sys_Xclock_settime64)
DEFINE_PUBLIC_ALIAS(sys_Xclock_settime64, libc_sys_Xclock_settime64)

/* errno_t clock_adjtime64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xclock_adjtime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 405, enableExcept: true) */
	b .
END(libc_sys_Xclock_adjtime64)
DEFINE_PUBLIC_ALIAS(sys_Xclock_adjtime64, libc_sys_Xclock_adjtime64)

/* errno_t clock_getres_time64(clockid_t clock_id, struct timespec64 *res) */
INTERN_FUNCTION(libc_sys_Xclock_getres_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 406, enableExcept: true) */
	b .
END(libc_sys_Xclock_getres_time64)
DEFINE_PUBLIC_ALIAS(sys_Xclock_getres_time64, libc_sys_Xclock_getres_time64)

/* errno_t clock_nanosleep_time64(clockid_t clock_id, syscall_ulong_t flags, struct timespec64 const *requested_time, struct timespec64 *remaining) */
INTERN_FUNCTION(libc_sys_Xclock_nanosleep_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 407, enableExcept: true) */
	b .
END(libc_sys_Xclock_nanosleep_time64)
DEFINE_PUBLIC_ALIAS(sys_Xclock_nanosleep_time64, libc_sys_Xclock_nanosleep_time64)

/* errno_t timer_gettime64(timer_t timerid, struct itimerspec64 *value) */
INTERN_FUNCTION(libc_sys_Xtimer_gettime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 408, enableExcept: true) */
	b .
END(libc_sys_Xtimer_gettime64)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_gettime64, libc_sys_Xtimer_gettime64)

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct itimerspec64 const *value, struct itimerspec64 *ovalue) */
INTERN_FUNCTION(libc_sys_Xtimer_settime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 409, enableExcept: true) */
	b .
END(libc_sys_Xtimer_settime64)
DEFINE_PUBLIC_ALIAS(sys_Xtimer_settime64, libc_sys_Xtimer_settime64)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime64(fd_t timerfd, struct itimerspec64 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_gettime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 410, enableExcept: true) */
	b .
END(libc_sys_Xtimerfd_gettime64)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_gettime64, libc_sys_Xtimerfd_gettime64)

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime64(fd_t timerfd, syscall_ulong_t flags, struct itimerspec64 const *utmr, struct itimerspec64 *otmr) */
INTERN_FUNCTION(libc_sys_Xtimerfd_settime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 411, enableExcept: true) */
	b .
END(libc_sys_Xtimerfd_settime64)
DEFINE_PUBLIC_ALIAS(sys_Xtimerfd_settime64, libc_sys_Xtimerfd_settime64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat_time64(fd_t dirfd, char const *filename, struct timespec64 const[2] times, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xutimensat_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 412, enableExcept: true) */
	b .
END(libc_sys_Xutimensat_time64)
DEFINE_PUBLIC_ALIAS(sys_Xutimensat_time64, libc_sys_Xutimensat_time64)

/* ssize_t pselect6_time64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec64 const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
INTERN_FUNCTION(libc_sys_Xpselect6_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 413, enableExcept: true) */
	b .
END(libc_sys_Xpselect6_time64)
DEFINE_PUBLIC_ALIAS(sys_Xpselect6_time64, libc_sys_Xpselect6_time64)

/* ssize_t ppoll_time64(struct pollfd *fds, size_t nfds, struct timespec64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xppoll_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 414, enableExcept: true) */
	b .
END(libc_sys_Xppoll_time64)
DEFINE_PUBLIC_ALIAS(sys_Xppoll_time64, libc_sys_Xppoll_time64)

/* errno_t io_pgetevents_time64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_pgetevents_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 416, enableExcept: true) */
	b .
END(libc_sys_Xio_pgetevents_time64)
DEFINE_PUBLIC_ALIAS(sys_Xio_pgetevents_time64, libc_sys_Xio_pgetevents_time64)

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg_time64(fd_t sockfd, struct mmsghdr64 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec64 const *tmo) */
INTERN_FUNCTION(libc_sys_Xrecvmmsg_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 417, enableExcept: true) */
	b .
END(libc_sys_Xrecvmmsg_time64)
DEFINE_PUBLIC_ALIAS(sys_Xrecvmmsg_time64, libc_sys_Xrecvmmsg_time64)

/* errno_t mq_timedsend_time64(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_Xmq_timedsend_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 418, enableExcept: true) */
	b .
END(libc_sys_Xmq_timedsend_time64)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedsend_time64, libc_sys_Xmq_timedsend_time64)

/* ssize_t mq_timedreceive_time64(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec64 const *abs_timeout) */
INTERN_FUNCTION(libc_sys_Xmq_timedreceive_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 419, enableExcept: true) */
	b .
END(libc_sys_Xmq_timedreceive_time64)
DEFINE_PUBLIC_ALIAS(sys_Xmq_timedreceive_time64, libc_sys_Xmq_timedreceive_time64)

/* errno_t semtimedop_time64(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xsemtimedop_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 420, enableExcept: true) */
	b .
END(libc_sys_Xsemtimedop_time64)
DEFINE_PUBLIC_ALIAS(sys_Xsemtimedop_time64, libc_sys_Xsemtimedop_time64)

/* syscall_slong_t rt_sigtimedwait_time64(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec64 const *timeout, size_t sigsetsize) */
INTERN_FUNCTION(libc_sys_Xrt_sigtimedwait_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 421, enableExcept: true) */
	b .
END(libc_sys_Xrt_sigtimedwait_time64)
DEFINE_PUBLIC_ALIAS(sys_Xrt_sigtimedwait_time64, libc_sys_Xrt_sigtimedwait_time64)

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex_time64(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
INTERN_FUNCTION(libc_sys_Xfutex_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 422, enableExcept: true) */
	b .
END(libc_sys_Xfutex_time64)
DEFINE_PUBLIC_ALIAS(sys_Xfutex_time64, libc_sys_Xfutex_time64)

/* errno_t sched_rr_get_interval_time64(pid_t pid, struct timespec64 *ts) */
INTERN_FUNCTION(libc_sys_Xsched_rr_get_interval_time64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 423, enableExcept: true) */
	b .
END(libc_sys_Xsched_rr_get_interval_time64)
DEFINE_PUBLIC_ALIAS(sys_Xsched_rr_get_interval_time64, libc_sys_Xsched_rr_get_interval_time64)

/* Send a signal to the process of a given pidfd
 * @param: pidfd:  A `HANDLE_TYPE_PIDFD'-handle
 * @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @param: flags:  Must always be `0' (for now)
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO:    [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:                 [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:     [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfo_struct const *uinfo, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xpidfd_send_signal)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 424, enableExcept: true) */
	b .
END(libc_sys_Xpidfd_send_signal)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_send_signal, libc_sys_Xpidfd_send_signal)

/* errno_t io_uring_setup(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_uring_setup)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 425, enableExcept: true) */
	b .
END(libc_sys_Xio_uring_setup)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_setup, libc_sys_Xio_uring_setup)

/* errno_t io_uring_enter(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_uring_enter)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 426, enableExcept: true) */
	b .
END(libc_sys_Xio_uring_enter)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_enter, libc_sys_Xio_uring_enter)

/* errno_t io_uring_register(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xio_uring_register)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 427, enableExcept: true) */
	b .
END(libc_sys_Xio_uring_register)
DEFINE_PUBLIC_ALIAS(sys_Xio_uring_register, libc_sys_Xio_uring_register)

/* errno_t open_tree(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xopen_tree)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 428, enableExcept: true) */
	b .
END(libc_sys_Xopen_tree)
DEFINE_PUBLIC_ALIAS(sys_Xopen_tree, libc_sys_Xopen_tree)

/* errno_t move_mount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xmove_mount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 429, enableExcept: true) */
	b .
END(libc_sys_Xmove_mount)
DEFINE_PUBLIC_ALIAS(sys_Xmove_mount, libc_sys_Xmove_mount)

/* errno_t fsopen(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfsopen)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 430, enableExcept: true) */
	b .
END(libc_sys_Xfsopen)
DEFINE_PUBLIC_ALIAS(sys_Xfsopen, libc_sys_Xfsopen)

/* errno_t fsconfig(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfsconfig)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 431, enableExcept: true) */
	b .
END(libc_sys_Xfsconfig)
DEFINE_PUBLIC_ALIAS(sys_Xfsconfig, libc_sys_Xfsconfig)

/* errno_t fsmount(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfsmount)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 432, enableExcept: true) */
	b .
END(libc_sys_Xfsmount)
DEFINE_PUBLIC_ALIAS(sys_Xfsmount, libc_sys_Xfsmount)

/* errno_t fspick(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xfspick)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 433, enableExcept: true) */
	b .
END(libc_sys_Xfspick)
DEFINE_PUBLIC_ALIAS(sys_Xfspick, libc_sys_Xfspick)

/* Return a `HANDLE_TYPE_PIDFD' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not  allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
/* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xpidfd_open)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 434, enableExcept: true) */
	b .
END(libc_sys_Xpidfd_open)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_open, libc_sys_Xpidfd_open)

/* syscall_slong_t clone3(struct clone_args *cl_args, size_t size) */
INTERN_FUNCTION(libc_sys_Xclone3)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 435, enableExcept: true) */
	b .
END(libc_sys_Xclone3)
DEFINE_PUBLIC_ALIAS(sys_Xclone3, libc_sys_Xclone3)

/* @param: flags: Set of `CLOSE_RANGE_*' from <linux/close_range.h> */
/* errno_t close_range(unsigned int minfd, unsigned int maxfd, unsigned int flags) */
INTERN_FUNCTION(libc_sys_Xclose_range)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 436, enableExcept: true) */
	b .
END(libc_sys_Xclose_range)
DEFINE_PUBLIC_ALIAS(sys_Xclose_range, libc_sys_Xclose_range)

/* errno_t openat2(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xopenat2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 437, enableExcept: true) */
	b .
END(libc_sys_Xopenat2)
DEFINE_PUBLIC_ALIAS(sys_Xopenat2, libc_sys_Xopenat2)

/* Duplicate the  handle  of  a  foreign  process into  a  handle  for  the  caller.
 * This system call duplicates the functionality of `open("/proc/[pid]/fd/[fdno]")',
 * which may also be used to duplicate file handles from another process.
 * @param: pidfd: A `HANDLE_TYPE_PIDFD'-handle
 * @param: fd:    The FD-number of the handle to clone
 * @param: flags: Must always be `0' (for now)
 * @return: * :   The duplicated handle number
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                            [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
/* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xpidfd_getfd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 438, enableExcept: true) */
	b .
END(libc_sys_Xpidfd_getfd)
DEFINE_PUBLIC_ALIAS(sys_Xpidfd_getfd, libc_sys_Xpidfd_getfd)

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat2(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfaccessat2)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 439, enableExcept: true) */
	b .
END(libc_sys_Xfaccessat2)
DEFINE_PUBLIC_ALIAS(sys_Xfaccessat2, libc_sys_Xfaccessat2)

/* errno_t process_madvise(int TODO_PROTOTYPE) */
INTERN_FUNCTION(libc_sys_Xprocess_madvise)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 440, enableExcept: true) */
	b .
END(libc_sys_Xprocess_madvise)
DEFINE_PUBLIC_ALIAS(sys_Xprocess_madvise, libc_sys_Xprocess_madvise)

/* Trigger a breakpoint */
/* void breakpoint(void) */
INTERN_FUNCTION(libc_sys_Xbreakpoint)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983041, enableExcept: true) */
	b .
END(libc_sys_Xbreakpoint)
DEFINE_PUBLIC_ALIAS(sys_Xbreakpoint, libc_sys_Xbreakpoint)

/* Flush instruction cache */
/* errno_t cacheflush(void const *start, void const *end, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xcacheflush)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983042, enableExcept: true) */
	b .
END(libc_sys_Xcacheflush)
DEFINE_PUBLIC_ALIAS(sys_Xcacheflush, libc_sys_Xcacheflush)

/* Clear CPSR.T=0x10 */
/* void usr26(void) */
INTERN_FUNCTION(libc_sys_Xusr26)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983043, enableExcept: true) */
	b .
END(libc_sys_Xusr26)
DEFINE_PUBLIC_ALIAS(sys_Xusr26, libc_sys_Xusr26)

/* Set CPSR.T=0x10 */
/* void usr32(void) */
INTERN_FUNCTION(libc_sys_Xusr32)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983044, enableExcept: true) */
	b .
END(libc_sys_Xusr32)
DEFINE_PUBLIC_ALIAS(sys_Xusr32, libc_sys_Xusr32)

/* Set calling thread's TLS pointer */
/* errno_t set_tls(void const *tlsval) */
INTERN_FUNCTION(libc_sys_Xset_tls)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983045, enableExcept: true) */
	b .
END(libc_sys_Xset_tls)
DEFINE_PUBLIC_ALIAS(sys_Xset_tls, libc_sys_Xset_tls)

/* Get calling thread's TLS pointer */
/* void *get_tls(void) */
INTERN_FUNCTION(libc_sys_Xget_tls)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 983046, enableExcept: true) */
	b .
END(libc_sys_Xget_tls)
DEFINE_PUBLIC_ALIAS(sys_Xget_tls, libc_sys_Xget_tls)

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xreadf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323075, enableExcept: true) */
	b .
END(libc_sys_Xreadf)
DEFINE_PUBLIC_ALIAS(sys_Xreadf, libc_sys_Xreadf)

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xwritef)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323076, enableExcept: true) */
	b .
END(libc_sys_Xwritef)
DEFINE_PUBLIC_ALIAS(sys_Xwritef, libc_sys_Xwritef)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
INTERN_FUNCTION(libc_sys_Xgetdrives)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323077, enableExcept: true) */
	b .
END(libc_sys_Xgetdrives)
DEFINE_PUBLIC_ALIAS(sys_Xgetdrives, libc_sys_Xgetdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfrealpath4)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323078, enableExcept: true) */
	b .
END(libc_sys_Xfrealpath4)
DEFINE_PUBLIC_ALIAS(sys_Xfrealpath4, libc_sys_Xfrealpath4)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the  thread from turning into  a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling  thread from  the set of  running children  within
 *     its own process.  Note however  that when this  is done  by the  main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the  calling   process   the   same  way   a   double-fork   would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads  of the calling process,  essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * The given `pid' must be:
 *   - A thread without the caller's process
 *   - A child process of the caller's process
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had  already
 *       be called.
 * @return: -ECHILD:         `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED: No such  thread/process exists,  or  the thread  isn't  isn't
 *                           a thread in your process, or a child process of your process. */
/* errno_t detach(pid_t pid) */
INTERN_FUNCTION(libc_sys_Xdetach)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323079, enableExcept: true) */
	b .
END(libc_sys_Xdetach)
DEFINE_PUBLIC_ALIAS(sys_Xdetach, libc_sys_Xdetach)

/* Returns  the  absolute   filesystem  path  for   the  specified   file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is  dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfrealpathat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323080, enableExcept: true) */
	b .
END(libc_sys_Xfrealpathat)
DEFINE_PUBLIC_ALIAS(sys_Xfrealpathat, libc_sys_Xfrealpathat)

/* >> rpc_schedule(2)
 * Schedule an RPC program to-be executed by some other thread. This  function
 * cannot guaranty that  the RPC  program is  always executed,  as the  target
 * thread terminate before the  conditions for the RPC  to be served are  ever
 * met. Note that these  conditions depend on the  given `mode'. Note that  on
 * multi-arch  platforms (such as  x86), the register numbers,  as well as the
 * address size used by `program' depend on the execution mode of `target_tid'
 * 
 * NOTE: Only a cancellation point when `RPC_JOIN_WAITFOR' is used!
 * 
 * @param: target_tid:      The TID of the targeted thread
 * @param: mode:            One of `RPC_SYNCMODE_*',  optionally or'd  with
 *                          one of `RPC_SYSRESTART_*', optionally or'd with
 *                          one of `RPC_PRIORITY_*',  optionally or'd  with
 *                          one of  `RPC_DOMAIN_*',  optionally  or'd  with
 *                          one of `RPC_JOIN_*'
 * @param: program:         The RPC program to execute (sequences of `RPC_OP_*')
 * @param: params:          RPC program parameters (for `RPC_OP_push_param')
 * @param: max_param_count: The max # of `params' used by `program'
 * 
 * @return: 0 :                Success
 * @throws: E_SEGFAULT:        Faulty pointers were given
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE:
 *                             The given `mode' is invalid.
 * @throws: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION:
 *                             The RPC program  contains illegal  instructions.
 *                             In this case, modifications made by instructions
 *                             encountered before the illegal one(s) will still
 *                             have  happened, meaning that the target thread's
 *                             state may have become inconsistent.
 * @throws: E_PROCESS_EXITED:  The target thread has already terminated, or
 *                             doesn't exist. Note  though that unless  the
 *                             thread  is  part  of your  own  process, are
 *                             still many reasons  outside of your  control
 *                             for why it  may terminate immediately  after
 *                             the RPC program finished. */
/* errno_t rpc_schedule(pid_t target_tid, syscall_ulong_t mode, void const *program, void const *const *params, size_t max_param_count) */
INTERN_FUNCTION(libc_sys_Xrpc_schedule)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323081, enableExcept: true) */
	b .
END(libc_sys_Xrpc_schedule)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_schedule, libc_sys_Xrpc_schedule)

/* Create a new pseudo-terminal driver and store handles to both the
 * master  and slave ends  of the connection  in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
INTERN_FUNCTION(libc_sys_Xopenpty)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323083, enableExcept: true) */
	b .
END(libc_sys_Xopenpty)
DEFINE_PUBLIC_ALIAS(sys_Xopenpty, libc_sys_Xopenpty)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfchdirat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323084, enableExcept: true) */
	b .
END(libc_sys_Xfchdirat)
DEFINE_PUBLIC_ALIAS(sys_Xfchdirat, libc_sys_Xfchdirat)

/* time64_t time64(time64_t *timer) */
INTERN_FUNCTION(libc_sys_Xtime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323085, enableExcept: true) */
	b .
END(libc_sys_Xtime64)
DEFINE_PUBLIC_ALIAS(sys_Xtime64, libc_sys_Xtime64)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The  newly created  device automatically gets  assigned an arbitrary  device number, before
 * being made available under a file `/dev/${name}'  (or rather: as ${name} within the  devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
INTERN_FUNCTION(libc_sys_Xmktty)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323086, enableExcept: true) */
	b .
END(libc_sys_Xmktty)
DEFINE_PUBLIC_ALIAS(sys_Xmktty, libc_sys_Xmktty)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   - Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND, NULL, NULL)'
 *   - Set mode #4 (as done by libc): `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND |
 *                                                           EXCEPT_HANDLER_FLAG_SETHANDLER,
 *                                                           &except_handler4, NULL)'
 * @param: mode:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: handler:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: handler_sp: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given `mode' is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
INTERN_FUNCTION(libc_sys_Xset_exception_handler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323087, enableExcept: true) */
	b .
END(libc_sys_Xset_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_Xset_exception_handler, libc_sys_Xset_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: pmode:       When non-`NULL', store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: phandler:    When   non-`NULL',   store  the   address   of  the   user-space   exception  handler.
 *                      Note that when no handler has been set (`!(*pmode & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: phandler_sp: When non-`NULL', store the starting address of the user-space exception handler stack.
 *                      Note that  when no  stack has  been set  (`!(*pmode & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-`NULL' and faulty */
/* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
INTERN_FUNCTION(libc_sys_Xget_exception_handler)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323088, enableExcept: true) */
	b .
END(libc_sys_Xget_exception_handler)
DEFINE_PUBLIC_ALIAS(sys_Xget_exception_handler, libc_sys_Xget_exception_handler)

/* Trigger a debugger trap `trapno', optionally extended with  `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to  the
 * given  `state', though given the purpose of this system call being
 * to inform a connected debugger  of some breakable event,  allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
INTERN_FUNCTION(libc_sys_Xdebugtrap)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323089, enableExcept: true) */
	b .
END(libc_sys_Xdebugtrap)
DEFINE_PUBLIC_ALIAS(sys_Xdebugtrap, libc_sys_Xdebugtrap)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The  state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `reason' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When   `curr_state'   is   also   `NULL',   then   the   current   CPU   state   is   used   instead.
 * @param: traceback_vector: (potentially  incomplete)   vector  of   additional  program   pointers  that   were
 *                           traversed   when   the  stack   was   walked  from   `orig_state'   to  `curr_state'
 *                           Note that earlier  entries within this  vector are further  up the call-stack,  with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it  can  be  assumed  that  the  traceback is  complete  and  contains  all  traversed  instruction locations.
 *                           In   this   case,  a   traceback  displayed   to   a  human   should  not   include   the  text   location  at
 *                           `traceback_vector[traceback_length-1]',    since    that    location    would    also    be    printed    when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: reason:           The reason that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           For certain `unwind_error' values, this can also  point to other things, but is  always
 *                           allowed to be `NULL' to indicate default/stub values.
 * @param: unwind_error:     The  unwind  error that  caused the  coredump,  or `UNWIND_SUCCESS'  if unwinding
 *                           was  never  actually  performed,  and   `reason'  is  actually  a   `siginfo_t *'
 *                           Ignored when `reason == NULL', in which case `UNWIND_SUCCESS' is assumed instead. */
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, union coredump_info const *reason, syscall_ulong_t unwind_error) */
INTERN_FUNCTION(libc_sys_Xcoredump)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323090, enableExcept: true) */
	b .
END(libc_sys_Xcoredump)
DEFINE_PUBLIC_ALIAS(sys_Xcoredump, libc_sys_Xcoredump)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
INTERN_FUNCTION(libc_sys_Xlseek64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323091, enableExcept: true) */
	b .
END(libc_sys_Xlseek64)
DEFINE_PUBLIC_ALIAS(sys_Xlseek64, libc_sys_Xlseek64)

/* Construct   a   user-vio-fd  object   supporting  mmap(2),   with  actual
 * memory  accesses  being dispatched  by  adding them  as  pending requests
 * to an internal  queue that  should be read(2)  from by  a worker  thread,
 * which should then service those requests before responding by write(2)ing
 * the results of the operation back to the same fd.
 * HINT: The format of the structures that are read(2) and
 *       write(2)en can be found in `<libvio/userviofd.h>'
 * NOTE: Don't use this system call directly. Use `vio_create(3)'
 *       from `<libvio/vio.h>' instead.
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This  size may be  altered at a  later point in time
 *                       through use of `ftruncate(return)'
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK | O_NONBLOCK' */
/* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xuserviofd)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323092, enableExcept: true) */
	b .
END(libc_sys_Xuserviofd)
DEFINE_PUBLIC_ALIAS(sys_Xuserviofd, libc_sys_Xuserviofd)

/* errno_t stime64(time64_t const *t) */
INTERN_FUNCTION(libc_sys_Xstime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323097, enableExcept: true) */
	b .
END(libc_sys_Xstime64)
DEFINE_PUBLIC_ALIAS(sys_Xstime64, libc_sys_Xstime64)

/* @param: times: When NULL, set the current time */
/* errno_t utime64(char const *filename, struct utimbuf64 const *times) */
INTERN_FUNCTION(libc_sys_Xutime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323102, enableExcept: true) */
	b .
END(libc_sys_Xutime64)
DEFINE_PUBLIC_ALIAS(sys_Xutime64, libc_sys_Xutime64)

/* errno_t ftime64(struct timeb64 *tp) */
INTERN_FUNCTION(libc_sys_Xftime64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323107, enableExcept: true) */
	b .
END(libc_sys_Xftime64)
DEFINE_PUBLIC_ALIAS(sys_Xftime64, libc_sys_Xftime64)

/* Begin  an  RTM operation.  Note that  if  the arch-specific  RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM  operation is in progress,  only a very small  hand
 * full  of system calls are allowed to  be used. Attempting to use arbitrary
 * system calls will most likely  result in an `RTM_ABORT_FAILED' error,  and
 * attempting to access too much system memory in general will result in this
 * function returning  with  `RTM_ABORT_CAPACITY',  rather  than  succeeding.
 * The following is  a list  of system calls  which are  whitelisted for  use
 * during a transaction:
 *   - sys_rtm_begin:  Nested RTM operation
 *   - sys_rtm_end:    End an RTM operation
 *   - sys_rtm_abort:  Abort an RTM operation
 *   - sys_rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the RTM driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
/* rtm_status_t rtm_begin(void) */
INTERN_FUNCTION(libc_sys_Xrtm_begin)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323120, enableExcept: true) */
	b .
END(libc_sys_Xrtm_begin)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_begin, libc_sys_Xrtm_begin)

/* End a transaction
 * If  the  transaction was  successful,  return normally  (by  returning `-EOK').
 * If    the   transaction   failed,   `sys_rtm_begin()'   returns   `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
/* errno_t rtm_end(void) */
INTERN_FUNCTION(libc_sys_Xrtm_end)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323121, enableExcept: true) */
	b .
END(libc_sys_Xrtm_end)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_end, libc_sys_Xrtm_end)

/* Abort the current transaction  by having `sys_rtm_begin()' return  with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise,  this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
/* errno_t rtm_abort(syscall_ulong_t code) */
INTERN_FUNCTION(libc_sys_Xrtm_abort)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323122, enableExcept: true) */
	b .
END(libc_sys_Xrtm_abort)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_abort, libc_sys_Xrtm_abort)

/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
/* syscall_ulong_t rtm_test(void) */
INTERN_FUNCTION(libc_sys_Xrtm_test)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323123, enableExcept: true) */
	b .
END(libc_sys_Xrtm_test)
DEFINE_PUBLIC_ALIAS(sys_Xrtm_test, libc_sys_Xrtm_test)

/* syscall_slong_t ioctlf(fd_t fd, ioctl_t command, iomode_t mode, void *arg) */
INTERN_FUNCTION(libc_sys_Xioctlf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323126, enableExcept: true) */
	b .
END(libc_sys_Xioctlf)
DEFINE_PUBLIC_ALIAS(sys_Xioctlf, libc_sys_Xioctlf)

/* uint64_t fsmode(uint64_t mode) */
INTERN_FUNCTION(libc_sys_Xfsmode)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323132, enableExcept: true) */
	b .
END(libc_sys_Xfsmode)
DEFINE_PUBLIC_ALIAS(sys_Xfsmode, libc_sys_Xfsmode)

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage64(syscall_slong_t who, struct rusage64 *tv) */
INTERN_FUNCTION(libc_sys_Xgetrusage64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323149, enableExcept: true) */
	b .
END(libc_sys_Xgetrusage64)
DEFINE_PUBLIC_ALIAS(sys_Xgetrusage64, libc_sys_Xgetrusage64)

/* errno_t gettimeofday64(struct timeval64 *tv, struct timezone *tz) */
INTERN_FUNCTION(libc_sys_Xgettimeofday64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323150, enableExcept: true) */
	b .
END(libc_sys_Xgettimeofday64)
DEFINE_PUBLIC_ALIAS(sys_Xgettimeofday64, libc_sys_Xgettimeofday64)

/* errno_t settimeofday64(struct timeval64 const *tv, struct timezone const *tz) */
INTERN_FUNCTION(libc_sys_Xsettimeofday64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323151, enableExcept: true) */
	b .
END(libc_sys_Xsettimeofday64)
DEFINE_PUBLIC_ALIAS(sys_Xsettimeofday64, libc_sys_Xsettimeofday64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN |
 *                MAP_GROWSUP  |  MAP_LOCKED  |  MAP_NORESERVE  |
 *                MAP_POPULATE  |  MAP_NONBLOCK   |  MAP_SYNC   |
 *                MAP_FIXED_NOREPLACE | MAP_NOASLR'
 * @param: fd:    A handle for the library file being mapped (must be mmap(2)-able)
 * @param: hdrv:  Pointer  to  a vector  of `Elf32_Phdr'  or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf32_phdr const *hdrv, size_t hdrc) */
INTERN_FUNCTION(libc_sys_Xmaplibrary)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323158, enableExcept: true) */
	b .
END(libc_sys_Xmaplibrary)
DEFINE_PUBLIC_ALIAS(sys_Xmaplibrary, libc_sys_Xmaplibrary)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
INTERN_FUNCTION(libc_sys_Xsetitimer64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323176, enableExcept: true) */
	b .
END(libc_sys_Xsetitimer64)
DEFINE_PUBLIC_ALIAS(sys_Xsetitimer64, libc_sys_Xsetitimer64)

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
INTERN_FUNCTION(libc_sys_Xgetitimer64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323177, enableExcept: true) */
	b .
END(libc_sys_Xgetitimer64)
DEFINE_PUBLIC_ALIAS(sys_Xgetitimer64, libc_sys_Xgetitimer64)

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4_64(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage64 *usage) */
INTERN_FUNCTION(libc_sys_Xwait4_64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323186, enableExcept: true) */
	b .
END(libc_sys_Xwait4_64)
DEFINE_PUBLIC_ALIAS(sys_Xwait4_64, libc_sys_Xwait4_64)

/* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval64 *timeout) */
INTERN_FUNCTION(libc_sys_Xselect64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323214, enableExcept: true) */
	b .
END(libc_sys_Xselect64)
DEFINE_PUBLIC_ALIAS(sys_Xselect64, libc_sys_Xselect64)

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xreadvf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323217, enableExcept: true) */
	b .
END(libc_sys_Xreadvf)
DEFINE_PUBLIC_ALIAS(sys_Xreadvf, libc_sys_Xreadvf)

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xwritevf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323218, enableExcept: true) */
	b .
END(libc_sys_Xwritevf)
DEFINE_PUBLIC_ALIAS(sys_Xwritevf, libc_sys_Xwritevf)

/* syscall_slong_t ksysctl(ioctl_t command, void *arg) */
INTERN_FUNCTION(libc_sys_Xksysctl)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323221, enableExcept: true) */
	b .
END(libc_sys_Xksysctl)
DEFINE_PUBLIC_ALIAS(sys_Xksysctl, libc_sys_Xksysctl)

/* >> rpc_serve(2)
 * Check for pending signals and RPCs. This is a wrapper around the
 * kernel `task_serve()' function, which is always invoked before a
 * thread begins waiting for a blocking operation. All system calls
 * marked as cancellation  points probably  call `task_serve()'  at
 * some point.
 * Note that unlike (say) `pause(2)', this function doesn't  block,
 * and may be used to implement `pthread_testcancel(3)' (should KOS
 * RPCs be used to facility pthread cancellation points, as done by
 * KOS's builtin libc)
 * @return: 0:      Nothing was handled.
 * @return: -EINTR: RPCs (or posix signals) were handled. */
/* errno_t rpc_serve(void) */
INTERN_FUNCTION(libc_sys_Xrpc_serve)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323230, enableExcept: true) */
	b .
END(libc_sys_Xrpc_serve)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_serve, libc_sys_Xrpc_serve)

/* >> rpc_serve_sysret(2)
 * Very similar to `rpc_serve(2)', but with the addition that this one
 * will only serve RPCs that can be handled in `RPC_REASONCTX_SYSRET',
 * aka. `RPC_REASONCTX_ASYNC' contexts. Additionally, this system call
 * ignores the state of the  internal `TASK_FRPC' flag, and should  be
 * invoked  when  the calling  thread  makes use  of  the userprocmask
 * mechanism, and the  signal mask became  less restrictive while  the
 * `USERPROCMASK_FLAG_HASPENDING' flag was set.
 * 
 * When userprocmask is disabled, this system call is pretty much just
 * a no-op (semnatically speaking, it does nothing). But when enabled,
 * it is really only usable  in conjuction with the userprocmask.  The
 * exact usage can be seen in `chkuserprocmask(3)'.
 * 
 * @return: 0 : Always, unconditionally returned. */
/* errno_t rpc_serve_sysret(void) */
INTERN_FUNCTION(libc_sys_Xrpc_serve_sysret)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323231, enableExcept: true) */
	b .
END(libc_sys_Xrpc_serve_sysret)
DEFINE_PUBLIC_ALIAS(sys_Xrpc_serve_sysret, libc_sys_Xrpc_serve_sysret)

/* errno_t nanosleep64(struct timespec64 const *req, struct timespec64 *rem) */
INTERN_FUNCTION(libc_sys_Xnanosleep64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323234, enableExcept: true) */
	b .
END(libc_sys_Xnanosleep64)
DEFINE_PUBLIC_ALIAS(sys_Xnanosleep64, libc_sys_Xnanosleep64)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpread64f)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323252, enableExcept: true) */
	b .
END(libc_sys_Xpread64f)
DEFINE_PUBLIC_ALIAS(sys_Xpread64f, libc_sys_Xpread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpwrite64f)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323253, enableExcept: true) */
	b .
END(libc_sys_Xpwrite64f)
DEFINE_PUBLIC_ALIAS(sys_Xpwrite64f, libc_sys_Xpwrite64f)

/* errno_t kstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xkstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323267, enableExcept: true) */
	b .
END(libc_sys_Xkstat)
DEFINE_PUBLIC_ALIAS(sys_Xkstat, libc_sys_Xkstat)

/* errno_t klstat(char const *filename, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xklstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323268, enableExcept: true) */
	b .
END(libc_sys_Xklstat)
DEFINE_PUBLIC_ALIAS(sys_Xklstat, libc_sys_Xklstat)

/* errno_t kfstat(fd_t fd, struct __kos_stat *statbuf) */
INTERN_FUNCTION(libc_sys_Xkfstat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323269, enableExcept: true) */
	b .
END(libc_sys_Xkfstat)
DEFINE_PUBLIC_ALIAS(sys_Xkfstat, libc_sys_Xkfstat)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
INTERN_FUNCTION(libc_sys_Xkreaddir)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323289, enableExcept: true) */
	b .
END(libc_sys_Xkreaddir)
DEFINE_PUBLIC_ALIAS(sys_Xkreaddir, libc_sys_Xkreaddir)

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
INTERN_FUNCTION(libc_sys_Xkreaddirf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323290, enableExcept: true) */
	b .
END(libc_sys_Xkreaddirf)
DEFINE_PUBLIC_ALIAS(sys_Xkreaddirf, libc_sys_Xkreaddirf)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:                (lfutex_t *uaddr, LFUTEX_WAKE, size_t count)
 *    - LFUTEX_WAKEMASK:            (lfutex_t *uaddr, LFUTEX_WAKEMASK, size_t count, lfutex_t mask_and, lfutex_t mask_or)
 *    - LFUTEX_WAIT_WHILE:          (lfutex_t *uaddr, LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:          (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
 *    - LFUTEX_WAIT_WHILE_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_UNTIL_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_ABOVE_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 *    - LFUTEX_WAIT_WHILE_BELOW_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct timespec64 const *timeout, uintptr_t val2) */
INTERN_FUNCTION(libc_sys_Xlfutex)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323312, enableExcept: true) */
	b .
END(libc_sys_Xlfutex)
DEFINE_PUBLIC_ALIAS(sys_Xlfutex, libc_sys_Xlfutex)

/* >> lfutexexpr(2)
 * The lfutexexpr(2) system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread.
 * @param: futexaddr: The futex on which to wait
 * @param: base:      Base pointer added to the `fe_offset' fields of given expressions
 * @param: expr:      Vector of expressions for which to check, terminated by `LFUTEX_EXPREND'
 * @param: timeout:   Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 *                    When `LFUTEX_FDBIT'  is  set,  this argument  must  be  `NULL'.
 * @param: flags:     Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*' or `LFUTEX_FDBIT'
 * @return: * : The first  non-zero  return value  from  executing  all of  the  given  `expr'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
 *              to see their  possible return  values, which are  always `0'  when they  would
 *              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 *              When `LFUTEX_FDBIT' is set, the return value is an `fd_t' for a futex fd that
 *              can be used to poll for the specified `exprv'. Note that in this case `exprv'
 *              is limited to `LFUTEXFD_DEFAULT_MAXEXPR' (`/proc/kos/futexfd-maxexpr')
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(uintptr_t *futexaddr, void *base, struct lfutexexpr const *expr, struct timespec const *timeout, syscall_ulong_t flags) */
INTERN_FUNCTION(libc_sys_Xlfutexexpr)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323313, enableExcept: true) */
	b .
END(libc_sys_Xlfutexexpr)
DEFINE_PUBLIC_ALIAS(sys_Xlfutexexpr, libc_sys_Xlfutexexpr)

/* Register the address of  the calling thread's userprocmask  controller.
 * This also  initializes `*ctl->pm_sigmask'  and `ctl->pm_pending',  such
 * that `*ctl->pm_sigmask' is filled with the current kernel-level  signal
 * mask, as would be returned by `sigprocmask(2)', while `ctl->pm_pending'
 * is filled in with the equivalent of `sigpending(2)'
 * Additionally,  the address  of `&ctl->pm_mytid'  is stored  as an override
 * for `set_tid_address(2)', and the kernel may read from `*ctl->pm_sigmask',
 * and write to `ctl->pm_pending' (using  atomic-or for the later) from  this
 * point forth.
 * NOTE: Before calling this function, the caller must:
 *       >> bzero(ctl, sizeof(struct userprocmask));
 *       >> ctl->pm_sigsize = sizeof(sigset_t);
 *       >> ctl->pm_sigmask = &initial_sigmask;
 *       Where the initial bzero() is needed to initialize potential
 *       additional,   arch-specific   fields    to   all    zeroes.
 * NOTE: This system call will then initialize:
 *       >> ctl->pm_mytid = gettid();
 *       >> sigprocmask(0, NULL, ctl->pm_sigmask);
 *       >> sigpending(&ctl->pm_pending);
 * NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
 *       before this is done, the kernel will copy the  `pm_sigmask'
 *       of the previously set  controller into its internal  signal
 *       mask. (i.e. the one used outside of userprocmask-mode)
 * Note though  that  `pm_sigmask'  is ignored  for  `SIGKILL'  and  `SIGSTOP'
 * Note also  that  this  function replaces  `set_tid_address(2)',  such  that
 * it negates a  prior call  to said  function, while  a future  call to  said
 * function will once again disable userprocmask, same as passing `NULL' would */
/* errno_t set_userprocmask_address(struct userprocmask *ctl) */
INTERN_FUNCTION(libc_sys_Xset_userprocmask_address)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323328, enableExcept: true) */
	b .
END(libc_sys_Xset_userprocmask_address)
DEFINE_PUBLIC_ALIAS(sys_Xset_userprocmask_address, libc_sys_Xset_userprocmask_address)

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes64(char const *filename, struct timeval64 const[2] times) */
INTERN_FUNCTION(libc_sys_Xutimes64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323341, enableExcept: true) */
	b .
END(libc_sys_Xutimes64)
DEFINE_PUBLIC_ALIAS(sys_Xutimes64, libc_sys_Xutimes64)

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid64(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage64 *ru) */
INTERN_FUNCTION(libc_sys_Xwaitid64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323352, enableExcept: true) */
	b .
END(libc_sys_Xwaitid64)
DEFINE_PUBLIC_ALIAS(sys_Xwaitid64, libc_sys_Xwaitid64)

/* @param: atflags: Set of `AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @param: mask:    Set of `IN_ALL_EVENTS | ...' */
/* int inotify_add_watch_at(fd_t notify_fd, fd_t dirfd, char const *pathname, atflag_t atflags, uint32_t mask) */
INTERN_FUNCTION(libc_sys_Xinotify_add_watch_at)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323389, enableExcept: true) */
	b .
END(libc_sys_Xinotify_add_watch_at)
DEFINE_PUBLIC_ALIAS(sys_Xinotify_add_watch_at, libc_sys_Xinotify_add_watch_at)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfmkdirat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323395, enableExcept: true) */
	b .
END(libc_sys_Xfmkdirat)
DEFINE_PUBLIC_ALIAS(sys_Xfmkdirat, libc_sys_Xfmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfmknodat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323396, enableExcept: true) */
	b .
END(libc_sys_Xfmknodat)
DEFINE_PUBLIC_ALIAS(sys_Xfmknodat, libc_sys_Xfmknodat)

/* errno_t futimesat64(fd_t dirfd, char const *filename, struct timeval64 const[2] times) */
INTERN_FUNCTION(libc_sys_Xfutimesat64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323398, enableExcept: true) */
	b .
END(libc_sys_Xfutimesat64)
DEFINE_PUBLIC_ALIAS(sys_Xfutimesat64, libc_sys_Xfutimesat64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *statbuf, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xkfstatat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323399, enableExcept: true) */
	b .
END(libc_sys_Xkfstatat)
DEFINE_PUBLIC_ALIAS(sys_Xkfstatat, libc_sys_Xkfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfsymlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323403, enableExcept: true) */
	b .
END(libc_sys_Xfsymlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xfsymlinkat, libc_sys_Xfsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
INTERN_FUNCTION(libc_sys_Xfreadlinkat)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323404, enableExcept: true) */
	b .
END(libc_sys_Xfreadlinkat)
DEFINE_PUBLIC_ALIAS(sys_Xfreadlinkat, libc_sys_Xfreadlinkat)

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpreadvf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323405, enableExcept: true) */
	b .
END(libc_sys_Xpreadvf)
DEFINE_PUBLIC_ALIAS(sys_Xpreadvf, libc_sys_Xpreadvf)

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
INTERN_FUNCTION(libc_sys_Xpwritevf)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323406, enableExcept: true) */
	b .
END(libc_sys_Xpwritevf)
DEFINE_PUBLIC_ALIAS(sys_Xpwritevf, libc_sys_Xpwritevf)

/* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
INTERN_FUNCTION(libc_sys_Xfallocate64)
	/* TODO: arm_printLibcSyscallWrapper(sysno: 8323424, enableExcept: true) */
	b .
END(libc_sys_Xfallocate64)
DEFINE_PUBLIC_ALIAS(sys_Xfallocate64, libc_sys_Xfallocate64)


/* TODO: arm_printLibcSyscallWrapperSuffix() */

/* Include the system call amendment in order to alias
 * some exception-enabled functions onto system calls. */
#include "../../syscalls-ammend.S.inl"

#endif /* GUARD_LIBC_LIBC_ARCH_ARM_SYSCALLS_S */
