/* HASH CRC-32:0x16c160bc */
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
#include <kernel/compiler.h>

/* TODO: x86_64_printKernelSyscallWrapperCommon() */










/************************************************************************/
/* WRAPPERS: __x86_asm32_int80_...                                      */
/************************************************************************/
/* errno_t restart_syscall(void) */
.section .text.x86.asm32_syscall_int80.restart_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_restart_syscall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_restart_syscall)

/* void exit(syscall_ulong_t status) */
.section .text.x86.asm32_syscall_int80.exit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_exit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_exit)

/* pid_t fork(void) */
.section .text.x86.asm32_syscall_int80.fork
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fork)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fork)

/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.read
INTERN_WEAK_FUNCTION(__x86_asm32_int80_read)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_read)

/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.write
INTERN_WEAK_FUNCTION(__x86_asm32_int80_write)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_write)

/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_int80.open
INTERN_WEAK_FUNCTION(__x86_asm32_int80_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_open)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.x86.asm32_syscall_int80.close
INTERN_WEAK_FUNCTION(__x86_asm32_int80_close)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_close)

/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t waitpid(pid_t pid, int32_t *stat_loc, syscall_ulong_t options) */
.section .text.x86.asm32_syscall_int80.waitpid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_waitpid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_waitpid)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_int80.creat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_creat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_creat)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.x86.asm32_syscall_int80.link
INTERN_WEAK_FUNCTION(__x86_asm32_int80_link)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_link)

/* errno_t unlink(char const *filename) */
.section .text.x86.asm32_syscall_int80.unlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_unlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_unlink)

/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
.section .text.x86.asm32_syscall_int80.execve
INTERN_WEAK_FUNCTION(__x86_asm32_int80_execve)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_execve)

/* errno_t chdir(char const *path) */
.section .text.x86.asm32_syscall_int80.chdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_chdir)

/* time32_t time(time32_t *timer) */
.section .text.x86.asm32_syscall_int80.time
INTERN_WEAK_FUNCTION(__x86_asm32_int80_time)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_time)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_int80.mknod
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mknod)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mknod)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_int80.chmod
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chmod)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_chmod)

/* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_int80.lchown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lchown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lchown)

/* errno_t break(void) */
.section .text.x86.asm32_syscall_int80.break
INTERN_WEAK_FUNCTION(__x86_asm32_int80_break)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_break)

/* errno_t linux_oldstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_oldstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_oldstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_oldstat)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_int80.lseek
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lseek)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lseek)

/* pid_t getpid(void) */
.section .text.x86.asm32_syscall_int80.getpid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getpid)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
.section .text.x86.asm32_syscall_int80.mount
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mount)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mount)

/* errno_t umount(char const *special_file) */
.section .text.x86.asm32_syscall_int80.umount
INTERN_WEAK_FUNCTION(__x86_asm32_int80_umount)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_umount)

/* errno_t setuid(uint16_t uid) */
.section .text.x86.asm32_syscall_int80.setuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setuid)

/* uint16_t getuid(void) */
.section .text.x86.asm32_syscall_int80.getuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getuid)

/* errno_t stime(time32_t const *t) */
.section .text.x86.asm32_syscall_int80.stime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_stime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_stime)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.x86.asm32_syscall_int80.ptrace
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ptrace)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ptrace)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.x86.asm32_syscall_int80.alarm
INTERN_WEAK_FUNCTION(__x86_asm32_int80_alarm)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_alarm)

/* errno_t linux_oldfstat(fd_t fd, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_oldfstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_oldfstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_oldfstat)

/* errno_t pause(void) */
.section .text.x86.asm32_syscall_int80.pause
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pause)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pause)

/* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
.section .text.x86.asm32_syscall_int80.utime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_utime)

/* errno_t stty(void) */
.section .text.x86.asm32_syscall_int80.stty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_stty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_stty)

/* errno_t gtty(void) */
.section .text.x86.asm32_syscall_int80.gtty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gtty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_gtty)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.x86.asm32_syscall_int80.access
INTERN_WEAK_FUNCTION(__x86_asm32_int80_access)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_access)

/* errno_t nice(syscall_slong_t inc) */
.section .text.x86.asm32_syscall_int80.nice
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nice)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_nice)

/* errno_t ftime(struct timeb *tp) */
.section .text.x86.asm32_syscall_int80.ftime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ftime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ftime)

/* errno_t sync(void) */
.section .text.x86.asm32_syscall_int80.sync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sync)

/* @param: signo: One of `SIG*' */
/* errno_t kill(pid_t pid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_int80.kill
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kill)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kill)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.x86.asm32_syscall_int80.rename
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rename)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_int80.mkdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mkdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mkdir)

/* errno_t rmdir(char const *path) */
.section .text.x86.asm32_syscall_int80.rmdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rmdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rmdir)

/* fd_t dup(fd_t fd) */
.section .text.x86.asm32_syscall_int80.dup
INTERN_WEAK_FUNCTION(__x86_asm32_int80_dup)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_dup)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.x86.asm32_syscall_int80.pipe
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pipe)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pipe)

/* clock_t times(struct tms *buf) */
.section .text.x86.asm32_syscall_int80.times
INTERN_WEAK_FUNCTION(__x86_asm32_int80_times)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_times)

/* errno_t prof(void) */
.section .text.x86.asm32_syscall_int80.prof
INTERN_WEAK_FUNCTION(__x86_asm32_int80_prof)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_prof)

/* errno_t brk(void *addr) */
.section .text.x86.asm32_syscall_int80.brk
INTERN_WEAK_FUNCTION(__x86_asm32_int80_brk)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_brk)

/* errno_t setgid(uint16_t gid) */
.section .text.x86.asm32_syscall_int80.setgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setgid)

/* uint16_t getgid(void) */
.section .text.x86.asm32_syscall_int80.getgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getgid)

/* @param: signo: One of `SIG*' */
/* sighandler_t signal(syscall_ulong_t signo, sighandler_t handler) */
.section .text.x86.asm32_syscall_int80.signal
INTERN_WEAK_FUNCTION(__x86_asm32_int80_signal)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_signal)

/* uint16_t geteuid(void) */
.section .text.x86.asm32_syscall_int80.geteuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_geteuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_geteuid)

/* uint16_t getegid(void) */
.section .text.x86.asm32_syscall_int80.getegid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getegid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getegid)

/* errno_t acct(char const *filename) */
.section .text.x86.asm32_syscall_int80.acct
INTERN_WEAK_FUNCTION(__x86_asm32_int80_acct)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_acct)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.umount2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_umount2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_umount2)

/* errno_t lock(void) */
.section .text.x86.asm32_syscall_int80.lock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lock)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
.section .text.x86.asm32_syscall_int80.ioctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ioctl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
.section .text.x86.asm32_syscall_int80.fcntl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fcntl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fcntl)

/* errno_t mpx(void) */
.section .text.x86.asm32_syscall_int80.mpx
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mpx)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mpx)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.x86.asm32_syscall_int80.setpgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setpgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setpgid)

/* errno_t ulimit(void) */
.section .text.x86.asm32_syscall_int80.ulimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ulimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ulimit)

/* errno_t oldolduname(struct linux_oldolduname *name) */
.section .text.x86.asm32_syscall_int80.oldolduname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_oldolduname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_oldolduname)

/* mode_t umask(mode_t mode) */
.section .text.x86.asm32_syscall_int80.umask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_umask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_umask)

/* errno_t chroot(char const *path) */
.section .text.x86.asm32_syscall_int80.chroot
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chroot)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_chroot)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.x86.asm32_syscall_int80.ustat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ustat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ustat)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.x86.asm32_syscall_int80.dup2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_dup2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_dup2)

/* pid_t getppid(void) */
.section .text.x86.asm32_syscall_int80.getppid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getppid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getppid)

/* pid_t getpgrp(void) */
.section .text.x86.asm32_syscall_int80.getpgrp
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpgrp)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getpgrp)

/* pid_t setsid(void) */
.section .text.x86.asm32_syscall_int80.setsid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setsid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setsid)

/* @param: signo: One of `SIG*' */
/* errno_t sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact) */
.section .text.x86.asm32_syscall_int80.sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigaction)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sigaction)

/* syscall_ulong_t sgetmask(void) */
.section .text.x86.asm32_syscall_int80.sgetmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sgetmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sgetmask)

/* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
.section .text.x86.asm32_syscall_int80.ssetmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ssetmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ssetmask)

/* errno_t setreuid(uint16_t ruid, uint16_t euid) */
.section .text.x86.asm32_syscall_int80.setreuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setreuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setreuid)

/* errno_t setregid(uint16_t rgid, uint16_t egid) */
.section .text.x86.asm32_syscall_int80.setregid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setregid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setregid)

/* errno_t sigsuspend(struct __sigset_struct const *set) */
.section .text.x86.asm32_syscall_int80.sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigsuspend)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sigsuspend)

/* errno_t sigpending(struct __sigset_struct *set) */
.section .text.x86.asm32_syscall_int80.sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigpending)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sigpending)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_int80.sethostname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sethostname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sethostname)

/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.x86.asm32_syscall_int80.setrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setrlimit)

/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.x86.asm32_syscall_int80.getrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getrlimit)

/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
.section .text.x86.asm32_syscall_int80.getrusage
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getrusage)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getrusage)

/* errno_t gettimeofday(struct __timeval32 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_int80.gettimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gettimeofday)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_gettimeofday)

/* errno_t settimeofday(struct __timeval32 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_int80.settimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_int80_settimeofday)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_settimeofday)

/* errno_t getgroups(size_t size, uint16_t[] list) */
.section .text.x86.asm32_syscall_int80.getgroups
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgroups)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getgroups)

/* errno_t setgroups(size_t count, uint16_t const *groups) */
.section .text.x86.asm32_syscall_int80.setgroups
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgroups)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setgroups)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval32 *timeout) */
.section .text.x86.asm32_syscall_int80.select
INTERN_WEAK_FUNCTION(__x86_asm32_int80_select)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_select)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.x86.asm32_syscall_int80.symlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_symlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_symlink)

/* errno_t linux_oldlstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_oldlstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_oldlstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_oldlstat)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_int80.readlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_readlink)

/* errno_t uselib(char const *library) */
.section .text.x86.asm32_syscall_int80.uselib
INTERN_WEAK_FUNCTION(__x86_asm32_int80_uselib)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_uselib)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.x86.asm32_syscall_int80.swapon
INTERN_WEAK_FUNCTION(__x86_asm32_int80_swapon)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_swapon)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.x86.asm32_syscall_int80.reboot
INTERN_WEAK_FUNCTION(__x86_asm32_int80_reboot)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_reboot)

/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
/* errno_t readdir(fd_t fd, struct old_linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_int80.readdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_readdir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.x86.asm32_syscall_int80.mmap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mmap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mmap)

/* errno_t munmap(void *addr, size_t len) */
.section .text.x86.asm32_syscall_int80.munmap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_munmap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_munmap)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_int80.truncate
INTERN_WEAK_FUNCTION(__x86_asm32_int80_truncate)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_truncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_int80.ftruncate
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ftruncate)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ftruncate)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.x86.asm32_syscall_int80.fchmod
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchmod)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fchmod)

/* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_int80.fchown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fchown)

/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.x86.asm32_syscall_int80.getpriority
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpriority)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getpriority)

/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.x86.asm32_syscall_int80.setpriority
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setpriority)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setpriority)

/* errno_t profil(uint16_t *sample_buffer, size_t size, size_t offset, syscall_ulong_t scale) */
.section .text.x86.asm32_syscall_int80.profil
INTERN_WEAK_FUNCTION(__x86_asm32_int80_profil)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_profil)

/* errno_t statfs(char const *file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_int80.statfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_statfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_statfs)

/* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_int80.fstatfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fstatfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fstatfs)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.x86.asm32_syscall_int80.ioperm
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioperm)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ioperm)

/* errno_t socketcall(int call, unsigned long *args) */
.section .text.x86.asm32_syscall_int80.socketcall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_socketcall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_socketcall)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.x86.asm32_syscall_int80.syslog
INTERN_WEAK_FUNCTION(__x86_asm32_int80_syslog)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_syslog)

/* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
.section .text.x86.asm32_syscall_int80.setitimer
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setitimer)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setitimer)

/* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
.section .text.x86.asm32_syscall_int80.getitimer
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getitimer)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getitimer)

/* errno_t linux_stat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_stat32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_stat32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_stat32)

/* errno_t linux_lstat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_lstat32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_lstat32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_lstat32)

/* errno_t linux_fstat32(fd_t fd, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_fstat32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_fstat32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_fstat32)

/* errno_t olduname(struct linux_olduname *name) */
.section .text.x86.asm32_syscall_int80.olduname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_olduname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_olduname)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.x86.asm32_syscall_int80.iopl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_iopl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_iopl)

/* errno_t vhangup(void) */
.section .text.x86.asm32_syscall_int80.vhangup
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vhangup)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_vhangup)

/* errno_t idle(void) */
.section .text.x86.asm32_syscall_int80.idle
INTERN_WEAK_FUNCTION(__x86_asm32_int80_idle)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_idle)

/* errno_t vm86old(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.vm86old
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vm86old)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_vm86old)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
.section .text.x86.asm32_syscall_int80.wait4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_wait4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_wait4)

/* errno_t swapoff(char const *pathname) */
.section .text.x86.asm32_syscall_int80.swapoff
INTERN_WEAK_FUNCTION(__x86_asm32_int80_swapoff)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_swapoff)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.x86.asm32_syscall_int80.sysinfo
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sysinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sysinfo)

/* errno_t ipc(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.ipc
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ipc)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ipc)

/* errno_t fsync(fd_t fd) */
.section .text.x86.asm32_syscall_int80.fsync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fsync)

/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
/* void sigreturn(struct fpustate const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.x86.asm32_syscall_int80.sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigreturn)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sigreturn)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
.section .text.x86.asm32_syscall_int80.clone
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clone)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clone)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_int80.setdomainname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setdomainname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setdomainname)

/* errno_t uname(struct utsname *name) */
.section .text.x86.asm32_syscall_int80.uname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_uname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_uname)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.x86.asm32_syscall_int80.modify_ldt
INTERN_WEAK_FUNCTION(__x86_asm32_int80_modify_ldt)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_modify_ldt)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.adjtimex
INTERN_WEAK_FUNCTION(__x86_asm32_int80_adjtimex)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_adjtimex)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.x86.asm32_syscall_int80.mprotect
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mprotect)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset) */
.section .text.x86.asm32_syscall_int80.sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigprocmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sigprocmask)

/* errno_t create_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.create_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_create_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_create_module)

/* errno_t init_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.init_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_init_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_init_module)

/* errno_t delete_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.delete_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_delete_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_delete_module)

/* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_kernel_syms
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_kernel_syms)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_get_kernel_syms)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.quotactl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_quotactl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_quotactl)

/* pid_t getpgid(pid_t pid) */
.section .text.x86.asm32_syscall_int80.getpgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getpgid)

/* errno_t fchdir(fd_t fd) */
.section .text.x86.asm32_syscall_int80.fchdir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fchdir)

/* errno_t bdflush(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.bdflush
INTERN_WEAK_FUNCTION(__x86_asm32_int80_bdflush)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_bdflush)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.sysfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sysfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sysfs)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.personality
INTERN_WEAK_FUNCTION(__x86_asm32_int80_personality)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_personality)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.afs_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_afs_syscall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_afs_syscall)

/* errno_t setfsuid(uint16_t uid) */
.section .text.x86.asm32_syscall_int80.setfsuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setfsuid)

/* errno_t setfsgid(uint16_t gid) */
.section .text.x86.asm32_syscall_int80.setfsgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setfsgid)

/* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_int80._llseek
INTERN_WEAK_FUNCTION(__x86_asm32_int80__llseek)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80__llseek)

/* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_int80.getdents
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getdents)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getdents)

/* errno_t _newselect(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80._newselect
INTERN_WEAK_FUNCTION(__x86_asm32_int80__newselect)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80__newselect)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.x86.asm32_syscall_int80.flock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_flock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_flock)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.msync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_msync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_msync)

/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.x86.asm32_syscall_int80.readv
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readv)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_readv)

/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.x86.asm32_syscall_int80.writev
INTERN_WEAK_FUNCTION(__x86_asm32_int80_writev)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_writev)

/* pid_t getsid(pid_t pid) */
.section .text.x86.asm32_syscall_int80.getsid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getsid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getsid)

/* errno_t fdatasync(fd_t fd) */
.section .text.x86.asm32_syscall_int80.fdatasync
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fdatasync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fdatasync)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80._sysctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80__sysctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80__sysctl)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_int80.mlock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mlock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_int80.munlock
INTERN_WEAK_FUNCTION(__x86_asm32_int80_munlock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_munlock)

/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.mlockall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mlockall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mlockall)

/* errno_t munlockall(void) */
.section .text.x86.asm32_syscall_int80.munlockall
INTERN_WEAK_FUNCTION(__x86_asm32_int80_munlockall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_munlockall)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.x86.asm32_syscall_int80.sched_setparam
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setparam)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.x86.asm32_syscall_int80.sched_getparam
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getparam)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_getparam)

/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.x86.asm32_syscall_int80.sched_setscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setscheduler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.x86.asm32_syscall_int80.sched_getscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getscheduler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_getscheduler)

/* errno_t sched_yield(void) */
.section .text.x86.asm32_syscall_int80.sched_yield
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_yield)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_yield)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_int80.sched_get_priority_max
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_get_priority_max)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_int80.sched_get_priority_min
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_get_priority_min)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct __timespec32 *tms) */
.section .text.x86.asm32_syscall_int80.sched_rr_get_interval
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_rr_get_interval)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_rr_get_interval)

/* errno_t nanosleep(struct __timespec32 const *req, struct __timespec32 *rem) */
.section .text.x86.asm32_syscall_int80.nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nanosleep)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_nanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.x86.asm32_syscall_int80.mremap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mremap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mremap)

/* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
.section .text.x86.asm32_syscall_int80.setresuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setresuid)

/* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
.section .text.x86.asm32_syscall_int80.getresuid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getresuid)

/* errno_t vm86(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.vm86
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vm86)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_vm86)

/* errno_t query_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.query_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_query_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_query_module)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_int80.poll
INTERN_WEAK_FUNCTION(__x86_asm32_int80_poll)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_poll)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.nfsservctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nfsservctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_nfsservctl)

/* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
.section .text.x86.asm32_syscall_int80.setresgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setresgid)

/* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
.section .text.x86.asm32_syscall_int80.getresgid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getresgid)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.prctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_prctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_prctl)

/* void rt_sigreturn(struct fpustate const *restore_fpu, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.x86.asm32_syscall_int80.rt_sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigreturn)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigreturn)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigaction)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigprocmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigprocmask)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigpending)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec32 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigtimedwait
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigtimedwait)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.x86.asm32_syscall_int80.rt_sigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigqueueinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigqueueinfo)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigsuspend)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigsuspend)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.pread64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pread64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.pwrite64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwrite64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pwrite64)

/* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_int80.chown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_chown)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.x86.asm32_syscall_int80.getcwd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getcwd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getcwd)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.capget
INTERN_WEAK_FUNCTION(__x86_asm32_int80_capget)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_capget)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.capset
INTERN_WEAK_FUNCTION(__x86_asm32_int80_capset)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_capset)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
.section .text.x86.asm32_syscall_int80.sigaltstack
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sigaltstack)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sigaltstack)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
.section .text.x86.asm32_syscall_int80.sendfile
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendfile)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sendfile)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.getpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.putpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_putpmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_putpmsg)

/* pid_t vfork(void) */
.section .text.x86.asm32_syscall_int80.vfork
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vfork)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_vfork)

/* errno_t ugetrlimit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.ugetrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ugetrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ugetrlimit)

/* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
.section .text.x86.asm32_syscall_int80.mmap2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mmap2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mmap2)

/* errno_t truncate64(char const *filename, uint64_t length) */
.section .text.x86.asm32_syscall_int80.truncate64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_truncate64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_truncate64)

/* errno_t ftruncate64(fd_t fd, uint64_t length) */
.section .text.x86.asm32_syscall_int80.ftruncate64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ftruncate64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ftruncate64)

/* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_stat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_stat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_stat64)

/* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_lstat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_lstat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_lstat64)

/* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_int80.linux_fstat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_fstat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_fstat64)

/* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_int80.lchown32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lchown32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lchown32)

/* uint32_t getuid32(void) */
.section .text.x86.asm32_syscall_int80.getuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getuid32)

/* uint32_t getgid32(void) */
.section .text.x86.asm32_syscall_int80.getgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getgid32)

/* uint32_t geteuid32(void) */
.section .text.x86.asm32_syscall_int80.geteuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_geteuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_geteuid32)

/* uint32_t getegid32(void) */
.section .text.x86.asm32_syscall_int80.getegid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getegid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getegid32)

/* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
.section .text.x86.asm32_syscall_int80.setreuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setreuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setreuid32)

/* errno_t setregid32(uint32_t rgid, uint32_t egid) */
.section .text.x86.asm32_syscall_int80.setregid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setregid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setregid32)

/* errno_t getgroups32(size_t size, uint32_t[] list) */
.section .text.x86.asm32_syscall_int80.getgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getgroups32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getgroups32)

/* errno_t setgroups32(size_t count, uint32_t const *groups) */
.section .text.x86.asm32_syscall_int80.setgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgroups32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setgroups32)

/* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_int80.fchown32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchown32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fchown32)

/* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
.section .text.x86.asm32_syscall_int80.setresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setresuid32)

/* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
.section .text.x86.asm32_syscall_int80.getresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getresuid32)

/* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
.section .text.x86.asm32_syscall_int80.setresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setresgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setresgid32)

/* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
.section .text.x86.asm32_syscall_int80.getresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getresgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getresgid32)

/* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_int80.chown32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_chown32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_chown32)

/* errno_t setuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_int80.setuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setuid32)

/* errno_t setgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_int80.setgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setgid32)

/* errno_t setfsuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_int80.setfsuid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setfsuid32)

/* errno_t setfsgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_int80.setfsgid32
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setfsgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setfsgid32)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.pivot_root
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pivot_root)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pivot_root)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.x86.asm32_syscall_int80.mincore
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mincore)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.x86.asm32_syscall_int80.madvise
INTERN_WEAK_FUNCTION(__x86_asm32_int80_madvise)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_madvise)

/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
.section .text.x86.asm32_syscall_int80.getdents64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getdents64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getdents64)

/* syscall_slong_t fcntl64(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_int80.fcntl64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fcntl64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fcntl64)

/* pid_t gettid(void) */
.section .text.x86.asm32_syscall_int80.gettid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gettid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_gettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.x86.asm32_syscall_int80.readahead
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readahead)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_readahead)

/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.setxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setxattr)

/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.lsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lsetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lsetxattr)

/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.fsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.getxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.lgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lgetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_int80.fgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fgetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_int80.listxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_listxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_listxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_int80.llistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_llistxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_llistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_int80.flistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_flistxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_flistxattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_int80.removexattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_removexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_removexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_int80.lremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lremovexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lremovexattr)

/* errno_t fremovexattr(int fd, char const *name) */
.section .text.x86.asm32_syscall_int80.fremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fremovexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fremovexattr)

/* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_int80.tkill
INTERN_WEAK_FUNCTION(__x86_asm32_int80_tkill)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_tkill)

/* ssize_t sendfile64(fd_t out_fd, fd_t in_fd, uint64_t *offset, size_t count) */
.section .text.x86.asm32_syscall_int80.sendfile64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendfile64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sendfile64)

/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.x86.asm32_syscall_int80.futex
INTERN_WEAK_FUNCTION(__x86_asm32_int80_futex)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_futex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.x86.asm32_syscall_int80.sched_setaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setaffinity)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.x86.asm32_syscall_int80.sched_getaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getaffinity)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.set_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_thread_area)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_set_thread_area)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_thread_area)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_get_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_setup
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_setup)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_io_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_destroy
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_destroy)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_io_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_getevents
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_getevents)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_io_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_submit
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_submit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_io_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.io_cancel
INTERN_WEAK_FUNCTION(__x86_asm32_int80_io_cancel)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_io_cancel)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fadvise64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fadvise64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fadvise64)

/* void exit_group(syscall_ulong_t exit_code) */
.section .text.x86.asm32_syscall_int80.exit_group
INTERN_WEAK_FUNCTION(__x86_asm32_int80_exit_group)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_exit_group)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.lookup_dcookie
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lookup_dcookie)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lookup_dcookie)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.x86.asm32_syscall_int80.epoll_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_epoll_create)

/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.x86.asm32_syscall_int80.epoll_ctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_ctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_epoll_ctl)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_int80.epoll_wait
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_wait)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_epoll_wait)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.remap_file_pages
INTERN_WEAK_FUNCTION(__x86_asm32_int80_remap_file_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_remap_file_pages)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.x86.asm32_syscall_int80.set_tid_address
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_tid_address)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_set_tid_address)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.x86.asm32_syscall_int80.timer_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timer_create)

/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspec32 const *value, struct __itimerspec32 *ovalue) */
.section .text.x86.asm32_syscall_int80.timer_settime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timer_settime)

/* errno_t timer_gettime(timer_t timerid, struct __itimerspec32 *value) */
.section .text.x86.asm32_syscall_int80.timer_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.x86.asm32_syscall_int80.timer_getoverrun
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_getoverrun)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
.section .text.x86.asm32_syscall_int80.timer_delete
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_delete)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct __timespec32 const *tp) */
.section .text.x86.asm32_syscall_int80.clock_settime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct __timespec32 *tp) */
.section .text.x86.asm32_syscall_int80.clock_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct __timespec32 *res) */
.section .text.x86.asm32_syscall_int80.clock_getres
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_getres)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespec32 const *requested_time, struct __timespec32 *remaining) */
.section .text.x86.asm32_syscall_int80.clock_nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_nanosleep)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_nanosleep)

/* errno_t statfs64(char const *file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_int80.statfs64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_statfs64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_statfs64)

/* errno_t fstatfs64(fd_t file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_int80.fstatfs64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fstatfs64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fstatfs64)

/* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_int80.tgkill
INTERN_WEAK_FUNCTION(__x86_asm32_int80_tgkill)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_tgkill)

/* errno_t utimes(char const *filename, struct __timeval32 const[2] times) */
.section .text.x86.asm32_syscall_int80.utimes
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimes)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_utimes)

/* errno_t fadvise64_64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fadvise64_64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fadvise64_64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fadvise64_64)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.vserver
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vserver)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_vserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mbind
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mbind)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mbind)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_mempolicy)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_get_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.set_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_mempolicy)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_set_mempolicy)

/* errno_t mq_open(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mq_open
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mq_open)

/* errno_t mq_unlink(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mq_unlink
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_unlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mq_unlink)

/* errno_t mq_timedsend(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mq_timedsend
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_timedsend)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mq_timedsend)

/* errno_t mq_timedreceive(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mq_timedreceive
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_timedreceive)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mq_timedreceive)

/* errno_t mq_notify(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mq_notify
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_notify)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mq_notify)

/* errno_t mq_getsetattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mq_getsetattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mq_getsetattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.kexec_load
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kexec_load)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kexec_load)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
.section .text.x86.asm32_syscall_int80.waitid
INTERN_WEAK_FUNCTION(__x86_asm32_int80_waitid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_waitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.add_key
INTERN_WEAK_FUNCTION(__x86_asm32_int80_add_key)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_add_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.request_key
INTERN_WEAK_FUNCTION(__x86_asm32_int80_request_key)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_request_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.keyctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_keyctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_keyctl)

/* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
.section .text.x86.asm32_syscall_int80.ioprio_set
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioprio_set)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ioprio_set)

/* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
.section .text.x86.asm32_syscall_int80.ioprio_get
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioprio_get)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ioprio_get)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_init)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_inotify_init)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_add_watch
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_add_watch)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_inotify_add_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_rm_watch
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_rm_watch)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_inotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.migrate_pages
INTERN_WEAK_FUNCTION(__x86_asm32_int80_migrate_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_migrate_pages)

/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_int80.openat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_openat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_openat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_int80.mkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mkdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_int80.mknodat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mknodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fchownat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchownat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fchownat)

/* errno_t futimesat(fd_t dirfd, const char *filename, struct __timeval32 const[2] times) */
.section .text.x86.asm32_syscall_int80.futimesat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_futimesat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_futimesat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t linux_fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.linux_fstatat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linux_fstatat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linux_fstatat64)

/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.unlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_unlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_unlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.x86.asm32_syscall_int80.renameat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_renameat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_renameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.linkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_linkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_linkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.x86.asm32_syscall_int80.symlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_symlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_symlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_int80.readlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_readlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fchmodat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchmodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.faccessat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_faccessat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_faccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec32 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_int80.pselect6
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pselect6)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.ppoll
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ppoll)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ppoll)

/* param flags: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.unshare
INTERN_WEAK_FUNCTION(__x86_asm32_int80_unshare)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_unshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.set_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_robust_list)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_set_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.get_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_robust_list)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_get_robust_list)

/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.splice
INTERN_WEAK_FUNCTION(__x86_asm32_int80_splice)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_splice)

/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.sync_file_range
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sync_file_range)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sync_file_range)

/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.tee
INTERN_WEAK_FUNCTION(__x86_asm32_int80_tee)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_tee)

/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.vmsplice
INTERN_WEAK_FUNCTION(__x86_asm32_int80_vmsplice)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_vmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.move_pages
INTERN_WEAK_FUNCTION(__x86_asm32_int80_move_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_move_pages)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.x86.asm32_syscall_int80.getcpu
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getcpu)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getcpu)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.x86.asm32_syscall_int80.epoll_pwait
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_pwait)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_epoll_pwait)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespec32 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.utimensat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimensat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_utimensat)

/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.signalfd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_signalfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_signalfd)

/* Return file descriptor for new interval timer source */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.timerfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.x86.asm32_syscall_int80.eventfd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_eventfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_eventfd)

/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_int80.fallocate
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fallocate)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspec32 const *utmr, struct __itimerspec32 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_settime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t ufd, struct __itimerspec32 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timerfd_gettime)

/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.signalfd4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_signalfd4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_signalfd4)

/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.eventfd2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_eventfd2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_eventfd2)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.epoll_create1
INTERN_WEAK_FUNCTION(__x86_asm32_int80_epoll_create1)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.x86.asm32_syscall_int80.dup3
INTERN_WEAK_FUNCTION(__x86_asm32_int80_dup3)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_dup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.x86.asm32_syscall_int80.pipe2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pipe2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pipe2)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.inotify_init1
INTERN_WEAK_FUNCTION(__x86_asm32_int80_inotify_init1)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_inotify_init1)

/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.preadv
INTERN_WEAK_FUNCTION(__x86_asm32_int80_preadv)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_preadv)

/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_int80.pwritev
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwritev)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pwritev)

/* @param: signo: One of `SIG*' */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.x86.asm32_syscall_int80.rt_tgsigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_tgsigqueueinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.perf_event_open
INTERN_WEAK_FUNCTION(__x86_asm32_int80_perf_event_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_perf_event_open)

/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec32 *tmo) */
.section .text.x86.asm32_syscall_int80.recvmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvmmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_recvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fanotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fanotify_init)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.fanotify_mark
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fanotify_mark)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.x86.asm32_syscall_int80.prlimit64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_prlimit64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_prlimit64)

/* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.name_to_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_int80_name_to_handle_at)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_name_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.open_by_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_int80_open_by_handle_at)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_open_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.clock_adjtime
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_adjtime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_adjtime)

/* errno_t syncfs(fd_t fd) */
.section .text.x86.asm32_syscall_int80.syncfs
INTERN_WEAK_FUNCTION(__x86_asm32_int80_syncfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_syncfs)

/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.sendmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendmmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.x86.asm32_syscall_int80.setns
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setns)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setns)

/* ssize_t process_vm_readv(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.process_vm_readv
INTERN_WEAK_FUNCTION(__x86_asm32_int80_process_vm_readv)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_process_vm_readv)

/* ssize_t process_vm_writev(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.process_vm_writev
INTERN_WEAK_FUNCTION(__x86_asm32_int80_process_vm_writev)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_process_vm_writev)

/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.x86.asm32_syscall_int80.kcmp
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kcmp)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kcmp)

/* errno_t finit_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.finit_module
INTERN_WEAK_FUNCTION(__x86_asm32_int80_finit_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_finit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.sched_setattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_setattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.sched_getattr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_getattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_getattr)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.renameat2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_renameat2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_renameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.seccomp
INTERN_WEAK_FUNCTION(__x86_asm32_int80_seccomp)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_seccomp)

/* errno_t getrandom(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.getrandom
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getrandom)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getrandom)

/* errno_t memfd_create(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.memfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_int80_memfd_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_memfd_create)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.bpf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_bpf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_bpf)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.execveat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_execveat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_execveat)

/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.x86.asm32_syscall_int80.socket
INTERN_WEAK_FUNCTION(__x86_asm32_int80_socket)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_socket)

/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.x86.asm32_syscall_int80.socketpair
INTERN_WEAK_FUNCTION(__x86_asm32_int80_socketpair)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_socketpair)

/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_int80.bind
INTERN_WEAK_FUNCTION(__x86_asm32_int80_bind)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_bind)

/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_int80.connect
INTERN_WEAK_FUNCTION(__x86_asm32_int80_connect)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_connect)

/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.x86.asm32_syscall_int80.listen
INTERN_WEAK_FUNCTION(__x86_asm32_int80_listen)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_listen)

/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.accept4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_accept4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_accept4)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.x86.asm32_syscall_int80.getsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getsockopt)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.x86.asm32_syscall_int80.setsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setsockopt)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setsockopt)

/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_int80.getsockname
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getsockname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getsockname)

/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_int80.getpeername
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getpeername)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getpeername)

/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_int80.sendto
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendto)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sendto)

/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.sendmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sendmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sendmsg)

/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_int80.recvfrom
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvfrom)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_recvfrom)

/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_int80.recvmsg
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.x86.asm32_syscall_int80.shutdown
INTERN_WEAK_FUNCTION(__x86_asm32_int80_shutdown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_shutdown)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.userfaultfd
INTERN_WEAK_FUNCTION(__x86_asm32_int80_userfaultfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_userfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.membarrier
INTERN_WEAK_FUNCTION(__x86_asm32_int80_membarrier)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_membarrier)

/* errno_t mlock2(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_int80.mlock2
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mlock2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mlock2)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_int80.hop
INTERN_WEAK_FUNCTION(__x86_asm32_int80_hop)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_hop)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_int80.hopf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_hopf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_hopf)

/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.readf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_readf)

/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.writef
INTERN_WEAK_FUNCTION(__x86_asm32_int80_writef)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_writef)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
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
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
/* errno_t detach(pid_t pid) */
.section .text.x86.asm32_syscall_int80.detach
INTERN_WEAK_FUNCTION(__x86_asm32_int80_detach)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.x86.asm32_syscall_int80.getdrives
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getdrives)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.frealpath4
INTERN_WEAK_FUNCTION(__x86_asm32_int80_frealpath4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.frealpathat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_frealpathat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, void **arguments) */
.section .text.x86.asm32_syscall_int80.rpc_schedule
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rpc_schedule)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rpc_schedule)

/* syscall_slong_t sysctl(syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_int80.sysctl
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sysctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.x86.asm32_syscall_int80.openpty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_openpty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_openpty)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fchdirat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fchdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fchdirat)

/* time64_t time64(time64_t *timer) */
.section .text.x86.asm32_syscall_int80.time64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_time64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_time64)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
.section .text.x86.asm32_syscall_int80.set_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_exception_handler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
/* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
.section .text.x86.asm32_syscall_int80.get_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_int80_get_exception_handler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_get_exception_handler)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
/* errno_t set_library_listdef(struct library_listdef const *listdef) */
.section .text.x86.asm32_syscall_int80.set_library_listdef
INTERN_WEAK_FUNCTION(__x86_asm32_int80_set_library_listdef)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
.section .text.x86.asm32_syscall_int80.debugtrap
INTERN_WEAK_FUNCTION(__x86_asm32_int80_debugtrap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_debugtrap)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
.section .text.x86.asm32_syscall_int80.lfutex
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lfutex)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lfutex)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_int80.lseek64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lseek64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lseek64)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_int80.lfutexexpr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lfutexexpr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_int80.lfutexlockexpr
INTERN_WEAK_FUNCTION(__x86_asm32_int80_lfutexlockexpr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
.section .text.x86.asm32_syscall_int80.mktty
INTERN_WEAK_FUNCTION(__x86_asm32_int80_mktty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
/* errno_t raiseat(struct ucpustate const *state, struct __siginfo_struct const *si) */
.section .text.x86.asm32_syscall_int80.raiseat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_raiseat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, struct exception_data const *exception, syscall_ulong_t unwind_error) */
.section .text.x86.asm32_syscall_int80.coredump
INTERN_WEAK_FUNCTION(__x86_asm32_int80_coredump)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_coredump)

/* errno_t stime64(time64_t const *t) */
.section .text.x86.asm32_syscall_int80.stime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_stime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_stime64)

/* errno_t utime64(char const *filename, struct __utimbuf64 const *times) */
.section .text.x86.asm32_syscall_int80.utime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_utime64)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_int80.ioctlf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ioctlf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ioctlf)

/* uint64_t fsmode(uint64_t mode) */
.section .text.x86.asm32_syscall_int80.fsmode
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsmode)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fsmode)

/* errno_t gettimeofday64(struct __timeval64 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_int80.gettimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_gettimeofday64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_gettimeofday64)

/* errno_t settimeofday64(struct __timeval64 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_int80.settimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_settimeofday64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_settimeofday64)

/* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval64 *timeout) */
.section .text.x86.asm32_syscall_int80.select64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_select64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_select64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
.section .text.x86.asm32_syscall_int80.maplibrary
INTERN_WEAK_FUNCTION(__x86_asm32_int80_maplibrary)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_maplibrary)

/* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
.section .text.x86.asm32_syscall_int80.setitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_setitimer64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_setitimer64)

/* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
.section .text.x86.asm32_syscall_int80.getitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_getitimer64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_getitimer64)

/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.x86.asm32_syscall_int80.kreaddir
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kreaddir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kreaddir)

/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.readvf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_readvf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_readvf)

/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.writevf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_writevf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_writevf)

/* syscall_slong_t rpc_service(void) */
.section .text.x86.asm32_syscall_int80.rpc_service
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rpc_service)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rpc_service)

/* errno_t sched_rr_get_interval64(pid_t pid, struct __timespec64 *tms) */
.section .text.x86.asm32_syscall_int80.sched_rr_get_interval64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_sched_rr_get_interval64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_sched_rr_get_interval64)

/* errno_t nanosleep64(struct __timespec64 const *req, struct __timespec64 *rem) */
.section .text.x86.asm32_syscall_int80.nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_nanosleep64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_nanosleep64)

/* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec64 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.rt_sigtimedwait64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_rt_sigtimedwait64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_rt_sigtimedwait64)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.pread64f
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pread64f)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.pwrite64f
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwrite64f)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pwrite64f)

/* errno_t kstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_int80.kstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kstat)

/* errno_t klstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_int80.klstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_klstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_klstat)

/* errno_t kfstat(fd_t fd, struct stat *statbuf) */
.section .text.x86.asm32_syscall_int80.kfstat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kfstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kfstat)

/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.x86.asm32_syscall_int80.kreaddirf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kreaddirf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kreaddirf)

/* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct __itimerspec64 const *value, struct __itimerspec64 *ovalue) */
.section .text.x86.asm32_syscall_int80.timer_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_settime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timer_settime64)

/* errno_t timer_gettime64(timer_t timerid, struct __itimerspec64 *value) */
.section .text.x86.asm32_syscall_int80.timer_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timer_gettime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timer_gettime64)

/* errno_t clock_settime64(clockid_t clock_id, struct __timespec64 const *tp) */
.section .text.x86.asm32_syscall_int80.clock_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_settime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_settime64)

/* errno_t clock_gettime64(clockid_t clock_id, struct __timespec64 *tp) */
.section .text.x86.asm32_syscall_int80.clock_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_gettime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_gettime64)

/* errno_t clock_getres64(clockid_t clock_id, struct __timespec64 *res) */
.section .text.x86.asm32_syscall_int80.clock_getres64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_getres64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_getres64)

/* errno_t clock_nanosleep64(clockid_t clock_id, syscall_ulong_t flags, struct __timespec64 const *requested_time, struct __timespec64 *remaining) */
.section .text.x86.asm32_syscall_int80.clock_nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_clock_nanosleep64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_clock_nanosleep64)

/* errno_t utimes64(char const *filename, struct __timeval64 const[2] times) */
.section .text.x86.asm32_syscall_int80.utimes64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimes64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_utimes64)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fmkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fmkdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fmknodat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fmknodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
/* errno_t futimesat64(fd_t dirfd, const char *filename, struct __timeval64 const[2] times) */
.section .text.x86.asm32_syscall_int80.futimesat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_futimesat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_futimesat64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.kfstatat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_kfstatat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_kfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.frenameat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_frenameat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_frenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.fsymlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fsymlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE|AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.freadlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_int80_freadlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_freadlinkat)

/* ssize_t pselect6_64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec64 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_int80.pselect6_64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pselect6_64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pselect6_64)

/* ssize_t ppoll64(struct pollfd *fds, size_t nfds, struct __timespec64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_int80.ppoll64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_ppoll64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_ppoll64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat64(fd_t dirfd, char const *filename, struct __timespec64 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_int80.utimensat64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_utimensat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_utimensat64)

/* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
.section .text.x86.asm32_syscall_int80.fallocate64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_fallocate64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_fallocate64)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime64(fd_t ufd, syscall_ulong_t flags, struct __itimerspec64 const *utmr, struct __itimerspec64 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_settime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timerfd_settime64)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime64(fd_t ufd, struct __itimerspec64 *otmr) */
.section .text.x86.asm32_syscall_int80.timerfd_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_timerfd_gettime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_timerfd_gettime64)

/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.preadvf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_preadvf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_preadvf)

/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_int80.pwritevf
INTERN_WEAK_FUNCTION(__x86_asm32_int80_pwritevf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_pwritevf)

/* ssize_t recvmmsg64(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec64 *tmo) */
.section .text.x86.asm32_syscall_int80.recvmmsg64
INTERN_WEAK_FUNCTION(__x86_asm32_int80_recvmmsg64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_int80() */
END(__x86_asm32_int80_recvmmsg64)










/************************************************************************/
/* WRAPPERS: __x86_asm32_sysenter_...                                   */
/************************************************************************/
/* errno_t restart_syscall(void) */
.section .text.x86.asm32_syscall_sysenter.restart_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_restart_syscall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_restart_syscall)

/* void exit(syscall_ulong_t status) */
.section .text.x86.asm32_syscall_sysenter.exit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_exit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_exit)

/* pid_t fork(void) */
.section .text.x86.asm32_syscall_sysenter.fork
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fork)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fork)

/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.read
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_read)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_read)

/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.write
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_write)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_write)

/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.open
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_open)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.close
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_close)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_close)

/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t waitpid(pid_t pid, int32_t *stat_loc, syscall_ulong_t options) */
.section .text.x86.asm32_syscall_sysenter.waitpid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_waitpid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_waitpid)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.creat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_creat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_creat)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.x86.asm32_syscall_sysenter.link
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_link)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_link)

/* errno_t unlink(char const *filename) */
.section .text.x86.asm32_syscall_sysenter.unlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_unlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_unlink)

/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
.section .text.x86.asm32_syscall_sysenter.execve
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_execve)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_execve)

/* errno_t chdir(char const *path) */
.section .text.x86.asm32_syscall_sysenter.chdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_chdir)

/* time32_t time(time32_t *timer) */
.section .text.x86.asm32_syscall_sysenter.time
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_time)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_time)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_sysenter.mknod
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mknod)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mknod)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.chmod
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chmod)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_chmod)

/* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_sysenter.lchown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lchown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lchown)

/* errno_t break(void) */
.section .text.x86.asm32_syscall_sysenter.break
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_break)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_break)

/* errno_t linux_oldstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_oldstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_oldstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_oldstat)

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_sysenter.lseek
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lseek)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lseek)

/* pid_t getpid(void) */
.section .text.x86.asm32_syscall_sysenter.getpid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getpid)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
.section .text.x86.asm32_syscall_sysenter.mount
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mount)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mount)

/* errno_t umount(char const *special_file) */
.section .text.x86.asm32_syscall_sysenter.umount
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_umount)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_umount)

/* errno_t setuid(uint16_t uid) */
.section .text.x86.asm32_syscall_sysenter.setuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setuid)

/* uint16_t getuid(void) */
.section .text.x86.asm32_syscall_sysenter.getuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getuid)

/* errno_t stime(time32_t const *t) */
.section .text.x86.asm32_syscall_sysenter.stime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_stime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_stime)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.x86.asm32_syscall_sysenter.ptrace
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ptrace)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ptrace)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.x86.asm32_syscall_sysenter.alarm
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_alarm)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_alarm)

/* errno_t linux_oldfstat(fd_t fd, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_oldfstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_oldfstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_oldfstat)

/* errno_t pause(void) */
.section .text.x86.asm32_syscall_sysenter.pause
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pause)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pause)

/* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
.section .text.x86.asm32_syscall_sysenter.utime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_utime)

/* errno_t stty(void) */
.section .text.x86.asm32_syscall_sysenter.stty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_stty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_stty)

/* errno_t gtty(void) */
.section .text.x86.asm32_syscall_sysenter.gtty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gtty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_gtty)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.x86.asm32_syscall_sysenter.access
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_access)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_access)

/* errno_t nice(syscall_slong_t inc) */
.section .text.x86.asm32_syscall_sysenter.nice
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nice)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_nice)

/* errno_t ftime(struct timeb *tp) */
.section .text.x86.asm32_syscall_sysenter.ftime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ftime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ftime)

/* errno_t sync(void) */
.section .text.x86.asm32_syscall_sysenter.sync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sync)

/* @param: signo: One of `SIG*' */
/* errno_t kill(pid_t pid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_sysenter.kill
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kill)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kill)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.x86.asm32_syscall_sysenter.rename
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rename)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.mkdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mkdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mkdir)

/* errno_t rmdir(char const *path) */
.section .text.x86.asm32_syscall_sysenter.rmdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rmdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rmdir)

/* fd_t dup(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.dup
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_dup)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_dup)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.x86.asm32_syscall_sysenter.pipe
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pipe)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pipe)

/* clock_t times(struct tms *buf) */
.section .text.x86.asm32_syscall_sysenter.times
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_times)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_times)

/* errno_t prof(void) */
.section .text.x86.asm32_syscall_sysenter.prof
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_prof)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_prof)

/* errno_t brk(void *addr) */
.section .text.x86.asm32_syscall_sysenter.brk
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_brk)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_brk)

/* errno_t setgid(uint16_t gid) */
.section .text.x86.asm32_syscall_sysenter.setgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setgid)

/* uint16_t getgid(void) */
.section .text.x86.asm32_syscall_sysenter.getgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getgid)

/* @param: signo: One of `SIG*' */
/* sighandler_t signal(syscall_ulong_t signo, sighandler_t handler) */
.section .text.x86.asm32_syscall_sysenter.signal
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_signal)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_signal)

/* uint16_t geteuid(void) */
.section .text.x86.asm32_syscall_sysenter.geteuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_geteuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_geteuid)

/* uint16_t getegid(void) */
.section .text.x86.asm32_syscall_sysenter.getegid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getegid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getegid)

/* errno_t acct(char const *filename) */
.section .text.x86.asm32_syscall_sysenter.acct
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_acct)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_acct)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.umount2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_umount2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_umount2)

/* errno_t lock(void) */
.section .text.x86.asm32_syscall_sysenter.lock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lock)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
.section .text.x86.asm32_syscall_sysenter.ioctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ioctl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
.section .text.x86.asm32_syscall_sysenter.fcntl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fcntl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fcntl)

/* errno_t mpx(void) */
.section .text.x86.asm32_syscall_sysenter.mpx
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mpx)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mpx)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.x86.asm32_syscall_sysenter.setpgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setpgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setpgid)

/* errno_t ulimit(void) */
.section .text.x86.asm32_syscall_sysenter.ulimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ulimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ulimit)

/* errno_t oldolduname(struct linux_oldolduname *name) */
.section .text.x86.asm32_syscall_sysenter.oldolduname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_oldolduname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_oldolduname)

/* mode_t umask(mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.umask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_umask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_umask)

/* errno_t chroot(char const *path) */
.section .text.x86.asm32_syscall_sysenter.chroot
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chroot)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_chroot)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.x86.asm32_syscall_sysenter.ustat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ustat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ustat)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.x86.asm32_syscall_sysenter.dup2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_dup2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_dup2)

/* pid_t getppid(void) */
.section .text.x86.asm32_syscall_sysenter.getppid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getppid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getppid)

/* pid_t getpgrp(void) */
.section .text.x86.asm32_syscall_sysenter.getpgrp
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpgrp)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getpgrp)

/* pid_t setsid(void) */
.section .text.x86.asm32_syscall_sysenter.setsid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setsid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setsid)

/* @param: signo: One of `SIG*' */
/* errno_t sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact) */
.section .text.x86.asm32_syscall_sysenter.sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigaction)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sigaction)

/* syscall_ulong_t sgetmask(void) */
.section .text.x86.asm32_syscall_sysenter.sgetmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sgetmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sgetmask)

/* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
.section .text.x86.asm32_syscall_sysenter.ssetmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ssetmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ssetmask)

/* errno_t setreuid(uint16_t ruid, uint16_t euid) */
.section .text.x86.asm32_syscall_sysenter.setreuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setreuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setreuid)

/* errno_t setregid(uint16_t rgid, uint16_t egid) */
.section .text.x86.asm32_syscall_sysenter.setregid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setregid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setregid)

/* errno_t sigsuspend(struct __sigset_struct const *set) */
.section .text.x86.asm32_syscall_sysenter.sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigsuspend)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sigsuspend)

/* errno_t sigpending(struct __sigset_struct *set) */
.section .text.x86.asm32_syscall_sysenter.sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigpending)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sigpending)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_sysenter.sethostname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sethostname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sethostname)

/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.x86.asm32_syscall_sysenter.setrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setrlimit)

/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.x86.asm32_syscall_sysenter.getrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getrlimit)

/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
.section .text.x86.asm32_syscall_sysenter.getrusage
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getrusage)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getrusage)

/* errno_t gettimeofday(struct __timeval32 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_sysenter.gettimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gettimeofday)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_gettimeofday)

/* errno_t settimeofday(struct __timeval32 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_sysenter.settimeofday
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_settimeofday)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_settimeofday)

/* errno_t getgroups(size_t size, uint16_t[] list) */
.section .text.x86.asm32_syscall_sysenter.getgroups
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgroups)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getgroups)

/* errno_t setgroups(size_t count, uint16_t const *groups) */
.section .text.x86.asm32_syscall_sysenter.setgroups
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgroups)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setgroups)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval32 *timeout) */
.section .text.x86.asm32_syscall_sysenter.select
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_select)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_select)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.x86.asm32_syscall_sysenter.symlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_symlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_symlink)

/* errno_t linux_oldlstat(char const *filename, struct linux_oldstat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_oldlstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_oldlstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_oldlstat)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_sysenter.readlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_readlink)

/* errno_t uselib(char const *library) */
.section .text.x86.asm32_syscall_sysenter.uselib
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_uselib)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_uselib)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.x86.asm32_syscall_sysenter.swapon
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_swapon)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_swapon)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.x86.asm32_syscall_sysenter.reboot
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_reboot)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_reboot)

/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
/* errno_t readdir(fd_t fd, struct old_linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_sysenter.readdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_readdir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.x86.asm32_syscall_sysenter.mmap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mmap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mmap)

/* errno_t munmap(void *addr, size_t len) */
.section .text.x86.asm32_syscall_sysenter.munmap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_munmap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_munmap)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_sysenter.truncate
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_truncate)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_truncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_sysenter.ftruncate
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ftruncate)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ftruncate)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.fchmod
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchmod)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fchmod)

/* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_sysenter.fchown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fchown)

/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.x86.asm32_syscall_sysenter.getpriority
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpriority)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getpriority)

/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.x86.asm32_syscall_sysenter.setpriority
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setpriority)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setpriority)

/* errno_t profil(uint16_t *sample_buffer, size_t size, size_t offset, syscall_ulong_t scale) */
.section .text.x86.asm32_syscall_sysenter.profil
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_profil)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_profil)

/* errno_t statfs(char const *file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_sysenter.statfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_statfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_statfs)

/* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
.section .text.x86.asm32_syscall_sysenter.fstatfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fstatfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fstatfs)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.x86.asm32_syscall_sysenter.ioperm
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioperm)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ioperm)

/* errno_t socketcall(int call, unsigned long *args) */
.section .text.x86.asm32_syscall_sysenter.socketcall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_socketcall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_socketcall)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.x86.asm32_syscall_sysenter.syslog
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_syslog)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_syslog)

/* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
.section .text.x86.asm32_syscall_sysenter.setitimer
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setitimer)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setitimer)

/* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
.section .text.x86.asm32_syscall_sysenter.getitimer
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getitimer)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getitimer)

/* errno_t linux_stat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_stat32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_stat32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_stat32)

/* errno_t linux_lstat32(char const *filename, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_lstat32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_lstat32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_lstat32)

/* errno_t linux_fstat32(fd_t fd, struct linux_stat32 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_fstat32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_fstat32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_fstat32)

/* errno_t olduname(struct linux_olduname *name) */
.section .text.x86.asm32_syscall_sysenter.olduname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_olduname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_olduname)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.x86.asm32_syscall_sysenter.iopl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_iopl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_iopl)

/* errno_t vhangup(void) */
.section .text.x86.asm32_syscall_sysenter.vhangup
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vhangup)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_vhangup)

/* errno_t idle(void) */
.section .text.x86.asm32_syscall_sysenter.idle
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_idle)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_idle)

/* errno_t vm86old(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.vm86old
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vm86old)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_vm86old)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
.section .text.x86.asm32_syscall_sysenter.wait4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_wait4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_wait4)

/* errno_t swapoff(char const *pathname) */
.section .text.x86.asm32_syscall_sysenter.swapoff
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_swapoff)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_swapoff)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.x86.asm32_syscall_sysenter.sysinfo
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sysinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sysinfo)

/* errno_t ipc(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.ipc
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ipc)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ipc)

/* errno_t fsync(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.fsync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fsync)

/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
/* void sigreturn(struct fpustate const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.x86.asm32_syscall_sysenter.sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigreturn)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sigreturn)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
.section .text.x86.asm32_syscall_sysenter.clone
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clone)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clone)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.x86.asm32_syscall_sysenter.setdomainname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setdomainname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setdomainname)

/* errno_t uname(struct utsname *name) */
.section .text.x86.asm32_syscall_sysenter.uname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_uname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_uname)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.x86.asm32_syscall_sysenter.modify_ldt
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_modify_ldt)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_modify_ldt)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.adjtimex
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_adjtimex)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_adjtimex)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.x86.asm32_syscall_sysenter.mprotect
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mprotect)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset) */
.section .text.x86.asm32_syscall_sysenter.sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigprocmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sigprocmask)

/* errno_t create_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.create_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_create_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_create_module)

/* errno_t init_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.init_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_init_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_init_module)

/* errno_t delete_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.delete_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_delete_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_delete_module)

/* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_kernel_syms
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_kernel_syms)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_get_kernel_syms)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.quotactl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_quotactl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_quotactl)

/* pid_t getpgid(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.getpgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getpgid)

/* errno_t fchdir(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.fchdir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fchdir)

/* errno_t bdflush(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.bdflush
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_bdflush)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_bdflush)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.sysfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sysfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sysfs)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.personality
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_personality)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_personality)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.afs_syscall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_afs_syscall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_afs_syscall)

/* errno_t setfsuid(uint16_t uid) */
.section .text.x86.asm32_syscall_sysenter.setfsuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setfsuid)

/* errno_t setfsgid(uint16_t gid) */
.section .text.x86.asm32_syscall_sysenter.setfsgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setfsgid)

/* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_sysenter._llseek
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter__llseek)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter__llseek)

/* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
.section .text.x86.asm32_syscall_sysenter.getdents
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getdents)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getdents)

/* errno_t _newselect(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter._newselect
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter__newselect)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter__newselect)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.x86.asm32_syscall_sysenter.flock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_flock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_flock)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.msync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_msync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_msync)

/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.x86.asm32_syscall_sysenter.readv
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readv)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_readv)

/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.x86.asm32_syscall_sysenter.writev
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_writev)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_writev)

/* pid_t getsid(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.getsid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getsid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getsid)

/* errno_t fdatasync(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.fdatasync
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fdatasync)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fdatasync)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter._sysctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter__sysctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter__sysctl)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_sysenter.mlock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mlock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.x86.asm32_syscall_sysenter.munlock
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_munlock)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_munlock)

/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.mlockall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mlockall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mlockall)

/* errno_t munlockall(void) */
.section .text.x86.asm32_syscall_sysenter.munlockall
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_munlockall)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_munlockall)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.x86.asm32_syscall_sysenter.sched_setparam
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setparam)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.x86.asm32_syscall_sysenter.sched_getparam
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getparam)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_getparam)

/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.x86.asm32_syscall_sysenter.sched_setscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setscheduler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.sched_getscheduler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getscheduler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_getscheduler)

/* errno_t sched_yield(void) */
.section .text.x86.asm32_syscall_sysenter.sched_yield
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_yield)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_yield)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_sysenter.sched_get_priority_max
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_get_priority_max)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.x86.asm32_syscall_sysenter.sched_get_priority_min
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_get_priority_min)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct __timespec32 *tms) */
.section .text.x86.asm32_syscall_sysenter.sched_rr_get_interval
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_rr_get_interval)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_rr_get_interval)

/* errno_t nanosleep(struct __timespec32 const *req, struct __timespec32 *rem) */
.section .text.x86.asm32_syscall_sysenter.nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nanosleep)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_nanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.x86.asm32_syscall_sysenter.mremap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mremap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mremap)

/* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
.section .text.x86.asm32_syscall_sysenter.setresuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setresuid)

/* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
.section .text.x86.asm32_syscall_sysenter.getresuid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getresuid)

/* errno_t vm86(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.vm86
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vm86)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_vm86)

/* errno_t query_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.query_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_query_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_query_module)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_sysenter.poll
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_poll)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_poll)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.nfsservctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nfsservctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_nfsservctl)

/* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
.section .text.x86.asm32_syscall_sysenter.setresgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setresgid)

/* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
.section .text.x86.asm32_syscall_sysenter.getresgid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getresgid)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.prctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_prctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_prctl)

/* void rt_sigreturn(struct fpustate const *restore_fpu, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.x86.asm32_syscall_sysenter.rt_sigreturn
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigreturn)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigreturn)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigaction
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigaction)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigprocmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigprocmask)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigpending
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigpending)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec32 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigtimedwait
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigtimedwait)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.x86.asm32_syscall_sysenter.rt_sigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigqueueinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigqueueinfo)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigsuspend)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigsuspend)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.pread64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pread64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.pwrite64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwrite64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pwrite64)

/* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
.section .text.x86.asm32_syscall_sysenter.chown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_chown)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.x86.asm32_syscall_sysenter.getcwd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getcwd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getcwd)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.capget
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_capget)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_capget)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.capset
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_capset)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_capset)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
.section .text.x86.asm32_syscall_sysenter.sigaltstack
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sigaltstack)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sigaltstack)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
.section .text.x86.asm32_syscall_sysenter.sendfile
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendfile)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sendfile)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.getpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.putpmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_putpmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_putpmsg)

/* pid_t vfork(void) */
.section .text.x86.asm32_syscall_sysenter.vfork
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vfork)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_vfork)

/* errno_t ugetrlimit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.ugetrlimit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ugetrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ugetrlimit)

/* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
.section .text.x86.asm32_syscall_sysenter.mmap2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mmap2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mmap2)

/* errno_t truncate64(char const *filename, uint64_t length) */
.section .text.x86.asm32_syscall_sysenter.truncate64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_truncate64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_truncate64)

/* errno_t ftruncate64(fd_t fd, uint64_t length) */
.section .text.x86.asm32_syscall_sysenter.ftruncate64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ftruncate64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ftruncate64)

/* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_stat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_stat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_stat64)

/* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_lstat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_lstat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_lstat64)

/* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
.section .text.x86.asm32_syscall_sysenter.linux_fstat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_fstat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_fstat64)

/* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_sysenter.lchown32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lchown32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lchown32)

/* uint32_t getuid32(void) */
.section .text.x86.asm32_syscall_sysenter.getuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getuid32)

/* uint32_t getgid32(void) */
.section .text.x86.asm32_syscall_sysenter.getgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getgid32)

/* uint32_t geteuid32(void) */
.section .text.x86.asm32_syscall_sysenter.geteuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_geteuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_geteuid32)

/* uint32_t getegid32(void) */
.section .text.x86.asm32_syscall_sysenter.getegid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getegid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getegid32)

/* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
.section .text.x86.asm32_syscall_sysenter.setreuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setreuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setreuid32)

/* errno_t setregid32(uint32_t rgid, uint32_t egid) */
.section .text.x86.asm32_syscall_sysenter.setregid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setregid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setregid32)

/* errno_t getgroups32(size_t size, uint32_t[] list) */
.section .text.x86.asm32_syscall_sysenter.getgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getgroups32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getgroups32)

/* errno_t setgroups32(size_t count, uint32_t const *groups) */
.section .text.x86.asm32_syscall_sysenter.setgroups32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgroups32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setgroups32)

/* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_sysenter.fchown32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchown32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fchown32)

/* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
.section .text.x86.asm32_syscall_sysenter.setresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setresuid32)

/* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
.section .text.x86.asm32_syscall_sysenter.getresuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getresuid32)

/* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
.section .text.x86.asm32_syscall_sysenter.setresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setresgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setresgid32)

/* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
.section .text.x86.asm32_syscall_sysenter.getresgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getresgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getresgid32)

/* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
.section .text.x86.asm32_syscall_sysenter.chown32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_chown32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_chown32)

/* errno_t setuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_sysenter.setuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setuid32)

/* errno_t setgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_sysenter.setgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setgid32)

/* errno_t setfsuid32(uint32_t uid) */
.section .text.x86.asm32_syscall_sysenter.setfsuid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsuid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setfsuid32)

/* errno_t setfsgid32(uint32_t gid) */
.section .text.x86.asm32_syscall_sysenter.setfsgid32
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setfsgid32)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setfsgid32)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.pivot_root
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pivot_root)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pivot_root)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.x86.asm32_syscall_sysenter.mincore
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mincore)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.x86.asm32_syscall_sysenter.madvise
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_madvise)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_madvise)

/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
.section .text.x86.asm32_syscall_sysenter.getdents64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getdents64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getdents64)

/* syscall_slong_t fcntl64(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_sysenter.fcntl64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fcntl64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fcntl64)

/* pid_t gettid(void) */
.section .text.x86.asm32_syscall_sysenter.gettid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gettid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_gettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.x86.asm32_syscall_sysenter.readahead
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readahead)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_readahead)

/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.setxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setxattr)

/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.lsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lsetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lsetxattr)

/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.fsetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.getxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.lgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lgetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm32_syscall_sysenter.fgetxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fgetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_sysenter.listxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_listxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_listxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_sysenter.llistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_llistxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_llistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.x86.asm32_syscall_sysenter.flistxattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_flistxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_flistxattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_sysenter.removexattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_removexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_removexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.x86.asm32_syscall_sysenter.lremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lremovexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lremovexattr)

/* errno_t fremovexattr(int fd, char const *name) */
.section .text.x86.asm32_syscall_sysenter.fremovexattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fremovexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fremovexattr)

/* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_sysenter.tkill
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_tkill)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_tkill)

/* ssize_t sendfile64(fd_t out_fd, fd_t in_fd, uint64_t *offset, size_t count) */
.section .text.x86.asm32_syscall_sysenter.sendfile64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendfile64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sendfile64)

/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.x86.asm32_syscall_sysenter.futex
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_futex)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_futex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.x86.asm32_syscall_sysenter.sched_setaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setaffinity)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.x86.asm32_syscall_sysenter.sched_getaffinity
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getaffinity)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.set_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_thread_area)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_set_thread_area)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_thread_area
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_thread_area)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_get_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_setup
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_setup)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_io_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_destroy
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_destroy)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_io_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_getevents
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_getevents)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_io_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_submit
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_submit)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_io_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.io_cancel
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_io_cancel)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_io_cancel)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fadvise64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fadvise64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fadvise64)

/* void exit_group(syscall_ulong_t exit_code) */
.section .text.x86.asm32_syscall_sysenter.exit_group
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_exit_group)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_exit_group)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.lookup_dcookie
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lookup_dcookie)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lookup_dcookie)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.x86.asm32_syscall_sysenter.epoll_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_epoll_create)

/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.x86.asm32_syscall_sysenter.epoll_ctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_ctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_epoll_ctl)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.x86.asm32_syscall_sysenter.epoll_wait
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_wait)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_epoll_wait)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.remap_file_pages
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_remap_file_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_remap_file_pages)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.x86.asm32_syscall_sysenter.set_tid_address
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_tid_address)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_set_tid_address)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.x86.asm32_syscall_sysenter.timer_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timer_create)

/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspec32 const *value, struct __itimerspec32 *ovalue) */
.section .text.x86.asm32_syscall_sysenter.timer_settime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timer_settime)

/* errno_t timer_gettime(timer_t timerid, struct __itimerspec32 *value) */
.section .text.x86.asm32_syscall_sysenter.timer_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.x86.asm32_syscall_sysenter.timer_getoverrun
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_getoverrun)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
.section .text.x86.asm32_syscall_sysenter.timer_delete
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_delete)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct __timespec32 const *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_settime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct __timespec32 *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct __timespec32 *res) */
.section .text.x86.asm32_syscall_sysenter.clock_getres
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_getres)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespec32 const *requested_time, struct __timespec32 *remaining) */
.section .text.x86.asm32_syscall_sysenter.clock_nanosleep
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_nanosleep)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_nanosleep)

/* errno_t statfs64(char const *file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_sysenter.statfs64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_statfs64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_statfs64)

/* errno_t fstatfs64(fd_t file, struct statfs64 *buf) */
.section .text.x86.asm32_syscall_sysenter.fstatfs64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fstatfs64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fstatfs64)

/* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm32_syscall_sysenter.tgkill
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_tgkill)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_tgkill)

/* errno_t utimes(char const *filename, struct __timeval32 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.utimes
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimes)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_utimes)

/* errno_t fadvise64_64(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fadvise64_64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fadvise64_64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fadvise64_64)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.vserver
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vserver)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_vserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mbind
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mbind)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mbind)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_mempolicy)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_get_mempolicy)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.set_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_mempolicy)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_set_mempolicy)

/* errno_t mq_open(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mq_open
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mq_open)

/* errno_t mq_unlink(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mq_unlink
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_unlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mq_unlink)

/* errno_t mq_timedsend(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mq_timedsend
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_timedsend)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mq_timedsend)

/* errno_t mq_timedreceive(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mq_timedreceive
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_timedreceive)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mq_timedreceive)

/* errno_t mq_notify(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mq_notify
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_notify)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mq_notify)

/* errno_t mq_getsetattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mq_getsetattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mq_getsetattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.kexec_load
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kexec_load)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kexec_load)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
.section .text.x86.asm32_syscall_sysenter.waitid
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_waitid)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_waitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.add_key
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_add_key)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_add_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.request_key
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_request_key)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_request_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.keyctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_keyctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_keyctl)

/* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
.section .text.x86.asm32_syscall_sysenter.ioprio_set
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioprio_set)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ioprio_set)

/* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
.section .text.x86.asm32_syscall_sysenter.ioprio_get
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioprio_get)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ioprio_get)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_init)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_inotify_init)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_add_watch
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_add_watch)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_inotify_add_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_rm_watch
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_rm_watch)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_inotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.migrate_pages
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_migrate_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_migrate_pages)

/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.openat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_openat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_openat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.x86.asm32_syscall_sysenter.mkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mkdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm32_syscall_sysenter.mknodat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mknodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fchownat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchownat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fchownat)

/* errno_t futimesat(fd_t dirfd, const char *filename, struct __timeval32 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.futimesat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_futimesat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_futimesat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t linux_fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.linux_fstatat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linux_fstatat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linux_fstatat64)

/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.unlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_unlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_unlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.x86.asm32_syscall_sysenter.renameat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_renameat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_renameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.linkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_linkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_linkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.x86.asm32_syscall_sysenter.symlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_symlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_symlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.x86.asm32_syscall_sysenter.readlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_readlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fchmodat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchmodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.faccessat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_faccessat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_faccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec32 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_sysenter.pselect6
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pselect6)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.ppoll
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ppoll)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ppoll)

/* param flags: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.unshare
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_unshare)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_unshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.set_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_robust_list)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_set_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.get_robust_list
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_robust_list)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_get_robust_list)

/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.splice
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_splice)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_splice)

/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.sync_file_range
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sync_file_range)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sync_file_range)

/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.tee
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_tee)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_tee)

/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.vmsplice
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_vmsplice)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_vmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.move_pages
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_move_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_move_pages)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.x86.asm32_syscall_sysenter.getcpu
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getcpu)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getcpu)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.x86.asm32_syscall_sysenter.epoll_pwait
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_pwait)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_epoll_pwait)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespec32 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.utimensat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimensat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_utimensat)

/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.signalfd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_signalfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_signalfd)

/* Return file descriptor for new interval timer source */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.timerfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.x86.asm32_syscall_sysenter.eventfd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_eventfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_eventfd)

/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.x86.asm32_syscall_sysenter.fallocate
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fallocate)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspec32 const *utmr, struct __itimerspec32 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_settime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t ufd, struct __itimerspec32 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_gettime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timerfd_gettime)

/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.signalfd4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_signalfd4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_signalfd4)

/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.eventfd2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_eventfd2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_eventfd2)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.epoll_create1
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_epoll_create1)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.dup3
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_dup3)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_dup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.pipe2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pipe2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pipe2)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.inotify_init1
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_inotify_init1)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_inotify_init1)

/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.preadv
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_preadv)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_preadv)

/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm32_syscall_sysenter.pwritev
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwritev)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pwritev)

/* @param: signo: One of `SIG*' */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.x86.asm32_syscall_sysenter.rt_tgsigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_tgsigqueueinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.perf_event_open
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_perf_event_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_perf_event_open)

/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec32 *tmo) */
.section .text.x86.asm32_syscall_sysenter.recvmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvmmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_recvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fanotify_init
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fanotify_init)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.fanotify_mark
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fanotify_mark)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.x86.asm32_syscall_sysenter.prlimit64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_prlimit64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_prlimit64)

/* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.name_to_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_name_to_handle_at)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_name_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.open_by_handle_at
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_open_by_handle_at)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_open_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.clock_adjtime
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_adjtime)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_adjtime)

/* errno_t syncfs(fd_t fd) */
.section .text.x86.asm32_syscall_sysenter.syncfs
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_syncfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_syncfs)

/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.sendmmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendmmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.x86.asm32_syscall_sysenter.setns
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setns)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setns)

/* ssize_t process_vm_readv(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.process_vm_readv
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_process_vm_readv)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_process_vm_readv)

/* ssize_t process_vm_writev(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.process_vm_writev
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_process_vm_writev)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_process_vm_writev)

/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.x86.asm32_syscall_sysenter.kcmp
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kcmp)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kcmp)

/* errno_t finit_module(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.finit_module
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_finit_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_finit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.sched_setattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_setattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.sched_getattr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_getattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_getattr)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.renameat2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_renameat2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_renameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.seccomp
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_seccomp)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_seccomp)

/* errno_t getrandom(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.getrandom
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getrandom)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getrandom)

/* errno_t memfd_create(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.memfd_create
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_memfd_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_memfd_create)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.bpf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_bpf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_bpf)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.execveat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_execveat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_execveat)

/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.x86.asm32_syscall_sysenter.socket
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_socket)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_socket)

/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.x86.asm32_syscall_sysenter.socketpair
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_socketpair)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_socketpair)

/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_sysenter.bind
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_bind)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_bind)

/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_sysenter.connect
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_connect)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_connect)

/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.x86.asm32_syscall_sysenter.listen
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_listen)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_listen)

/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.accept4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_accept4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_accept4)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.x86.asm32_syscall_sysenter.getsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getsockopt)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.x86.asm32_syscall_sysenter.setsockopt
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setsockopt)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setsockopt)

/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_sysenter.getsockname
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getsockname)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getsockname)

/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_sysenter.getpeername
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getpeername)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getpeername)

/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm32_syscall_sysenter.sendto
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendto)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sendto)

/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.sendmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sendmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sendmsg)

/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm32_syscall_sysenter.recvfrom
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvfrom)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_recvfrom)

/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
.section .text.x86.asm32_syscall_sysenter.recvmsg
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.x86.asm32_syscall_sysenter.shutdown
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_shutdown)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_shutdown)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.userfaultfd
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_userfaultfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_userfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.membarrier
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_membarrier)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_membarrier)

/* errno_t mlock2(int TODO_PROTOTYPE) */
.section .text.x86.asm32_syscall_sysenter.mlock2
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mlock2)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mlock2)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_sysenter.hop
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_hop)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_hop)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_sysenter.hopf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_hopf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_hopf)

/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.readf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_readf)

/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.writef
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_writef)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_writef)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
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
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
/* errno_t detach(pid_t pid) */
.section .text.x86.asm32_syscall_sysenter.detach
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_detach)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.x86.asm32_syscall_sysenter.getdrives
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getdrives)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.frealpath4
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_frealpath4)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.frealpathat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_frealpathat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, void **arguments) */
.section .text.x86.asm32_syscall_sysenter.rpc_schedule
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rpc_schedule)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rpc_schedule)

/* syscall_slong_t sysctl(syscall_ulong_t command, void *arg) */
.section .text.x86.asm32_syscall_sysenter.sysctl
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sysctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.x86.asm32_syscall_sysenter.openpty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_openpty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_openpty)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fchdirat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fchdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fchdirat)

/* time64_t time64(time64_t *timer) */
.section .text.x86.asm32_syscall_sysenter.time64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_time64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_time64)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
.section .text.x86.asm32_syscall_sysenter.set_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_exception_handler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
/* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
.section .text.x86.asm32_syscall_sysenter.get_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_get_exception_handler)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_get_exception_handler)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
/* errno_t set_library_listdef(struct library_listdef const *listdef) */
.section .text.x86.asm32_syscall_sysenter.set_library_listdef
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_set_library_listdef)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
.section .text.x86.asm32_syscall_sysenter.debugtrap
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_debugtrap)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_debugtrap)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
.section .text.x86.asm32_syscall_sysenter.lfutex
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lfutex)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lfutex)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
.section .text.x86.asm32_syscall_sysenter.lseek64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lseek64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lseek64)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_sysenter.lfutexexpr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lfutexexpr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm32_syscall_sysenter.lfutexlockexpr
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_lfutexlockexpr)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
.section .text.x86.asm32_syscall_sysenter.mktty
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_mktty)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
/* errno_t raiseat(struct ucpustate const *state, struct __siginfo_struct const *si) */
.section .text.x86.asm32_syscall_sysenter.raiseat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_raiseat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, struct exception_data const *exception, syscall_ulong_t unwind_error) */
.section .text.x86.asm32_syscall_sysenter.coredump
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_coredump)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_coredump)

/* errno_t stime64(time64_t const *t) */
.section .text.x86.asm32_syscall_sysenter.stime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_stime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_stime64)

/* errno_t utime64(char const *filename, struct __utimbuf64 const *times) */
.section .text.x86.asm32_syscall_sysenter.utime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_utime64)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm32_syscall_sysenter.ioctlf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ioctlf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ioctlf)

/* uint64_t fsmode(uint64_t mode) */
.section .text.x86.asm32_syscall_sysenter.fsmode
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsmode)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fsmode)

/* errno_t gettimeofday64(struct __timeval64 *tv, struct timezone *tz) */
.section .text.x86.asm32_syscall_sysenter.gettimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_gettimeofday64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_gettimeofday64)

/* errno_t settimeofday64(struct __timeval64 const *tv, struct timezone const *tz) */
.section .text.x86.asm32_syscall_sysenter.settimeofday64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_settimeofday64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_settimeofday64)

/* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval64 *timeout) */
.section .text.x86.asm32_syscall_sysenter.select64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_select64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_select64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
.section .text.x86.asm32_syscall_sysenter.maplibrary
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_maplibrary)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_maplibrary)

/* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
.section .text.x86.asm32_syscall_sysenter.setitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_setitimer64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_setitimer64)

/* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
.section .text.x86.asm32_syscall_sysenter.getitimer64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_getitimer64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_getitimer64)

/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.x86.asm32_syscall_sysenter.kreaddir
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kreaddir)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kreaddir)

/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.readvf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_readvf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_readvf)

/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.writevf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_writevf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_writevf)

/* syscall_slong_t rpc_service(void) */
.section .text.x86.asm32_syscall_sysenter.rpc_service
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rpc_service)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rpc_service)

/* errno_t sched_rr_get_interval64(pid_t pid, struct __timespec64 *tms) */
.section .text.x86.asm32_syscall_sysenter.sched_rr_get_interval64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_sched_rr_get_interval64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_sched_rr_get_interval64)

/* errno_t nanosleep64(struct __timespec64 const *req, struct __timespec64 *rem) */
.section .text.x86.asm32_syscall_sysenter.nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_nanosleep64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_nanosleep64)

/* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec64 const *timeout, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.rt_sigtimedwait64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_rt_sigtimedwait64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_rt_sigtimedwait64)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.pread64f
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pread64f)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.pwrite64f
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwrite64f)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pwrite64f)

/* errno_t kstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.kstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kstat)

/* errno_t klstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.klstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_klstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_klstat)

/* errno_t kfstat(fd_t fd, struct stat *statbuf) */
.section .text.x86.asm32_syscall_sysenter.kfstat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kfstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kfstat)

/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.x86.asm32_syscall_sysenter.kreaddirf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kreaddirf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kreaddirf)

/* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct __itimerspec64 const *value, struct __itimerspec64 *ovalue) */
.section .text.x86.asm32_syscall_sysenter.timer_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_settime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timer_settime64)

/* errno_t timer_gettime64(timer_t timerid, struct __itimerspec64 *value) */
.section .text.x86.asm32_syscall_sysenter.timer_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timer_gettime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timer_gettime64)

/* errno_t clock_settime64(clockid_t clock_id, struct __timespec64 const *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_settime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_settime64)

/* errno_t clock_gettime64(clockid_t clock_id, struct __timespec64 *tp) */
.section .text.x86.asm32_syscall_sysenter.clock_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_gettime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_gettime64)

/* errno_t clock_getres64(clockid_t clock_id, struct __timespec64 *res) */
.section .text.x86.asm32_syscall_sysenter.clock_getres64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_getres64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_getres64)

/* errno_t clock_nanosleep64(clockid_t clock_id, syscall_ulong_t flags, struct __timespec64 const *requested_time, struct __timespec64 *remaining) */
.section .text.x86.asm32_syscall_sysenter.clock_nanosleep64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_clock_nanosleep64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_clock_nanosleep64)

/* errno_t utimes64(char const *filename, struct __timeval64 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.utimes64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimes64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_utimes64)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fmkdirat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fmkdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fmknodat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fmknodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
/* errno_t futimesat64(fd_t dirfd, const char *filename, struct __timeval64 const[2] times) */
.section .text.x86.asm32_syscall_sysenter.futimesat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_futimesat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_futimesat64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.kfstatat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_kfstatat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_kfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.frenameat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_frenameat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_frenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.fsymlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fsymlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE|AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.freadlinkat
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_freadlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_freadlinkat)

/* ssize_t pselect6_64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec64 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm32_syscall_sysenter.pselect6_64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pselect6_64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pselect6_64)

/* ssize_t ppoll64(struct pollfd *fds, size_t nfds, struct __timespec64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm32_syscall_sysenter.ppoll64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_ppoll64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_ppoll64)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat64(fd_t dirfd, char const *filename, struct __timespec64 const[2] times, atflag_t flags) */
.section .text.x86.asm32_syscall_sysenter.utimensat64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_utimensat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_utimensat64)

/* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
.section .text.x86.asm32_syscall_sysenter.fallocate64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_fallocate64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_fallocate64)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime64(fd_t ufd, syscall_ulong_t flags, struct __itimerspec64 const *utmr, struct __itimerspec64 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_settime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_settime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timerfd_settime64)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime64(fd_t ufd, struct __itimerspec64 *otmr) */
.section .text.x86.asm32_syscall_sysenter.timerfd_gettime64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_timerfd_gettime64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_timerfd_gettime64)

/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.preadvf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_preadvf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_preadvf)

/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm32_syscall_sysenter.pwritevf
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_pwritevf)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_pwritevf)

/* ssize_t recvmmsg64(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec64 *tmo) */
.section .text.x86.asm32_syscall_sysenter.recvmmsg64
INTERN_WEAK_FUNCTION(__x86_asm32_sysenter_recvmmsg64)
/* TODO: x86_64_printKernelSyscallWrapper_asm32_sysenter() */
END(__x86_asm32_sysenter_recvmmsg64)










/************************************************************************/
/* WRAPPERS: __x86_asm64_syscall_...                                    */
/************************************************************************/
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
.section .text.x86.asm64_syscall.read
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_read)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_read)

/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
.section .text.x86.asm64_syscall.write
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_write)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_write)

/* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm64_syscall.open
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_open)

/* Close a given file descriptor/handle `FD' */
/* errno_t close(fd_t fd) */
.section .text.x86.asm64_syscall.close
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_close)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_close)

/* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm64_syscall.linux_stat64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_linux_stat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_linux_stat64)

/* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
.section .text.x86.asm64_syscall.linux_fstat64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_linux_fstat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_linux_fstat64)

/* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
.section .text.x86.asm64_syscall.linux_lstat64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_linux_lstat64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_linux_lstat64)

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
.section .text.x86.asm64_syscall.poll
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_poll)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_poll)

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
.section .text.x86.asm64_syscall.lseek64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lseek64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lseek64)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
.section .text.x86.asm64_syscall.mmap
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mmap)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
.section .text.x86.asm64_syscall.mprotect
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mprotect)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mprotect)

/* errno_t munmap(void *addr, size_t len) */
.section .text.x86.asm64_syscall.munmap
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_munmap)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_munmap)

/* errno_t brk(void *addr) */
.section .text.x86.asm64_syscall.brk
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_brk)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_brk)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact, size_t sigsetsize) */
.section .text.x86.asm64_syscall.rt_sigaction
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_sigaction)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
.section .text.x86.asm64_syscall.rt_sigprocmask
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_sigprocmask)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_sigprocmask)

/* void rt_sigreturn(struct fpustate const *restore_fpu, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
.section .text.x86.asm64_syscall.rt_sigreturn
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_sigreturn)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_sigreturn)

/* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
.section .text.x86.asm64_syscall.ioctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ioctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ioctl)

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm64_syscall.pread64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pread64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pread64)

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
.section .text.x86.asm64_syscall.pwrite64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pwrite64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pwrite64)

/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.x86.asm64_syscall.readv
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_readv)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_readv)

/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
.section .text.x86.asm64_syscall.writev
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_writev)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_writev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
.section .text.x86.asm64_syscall.access
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_access)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_access)

/* errno_t pipe(fd_t[2] pipedes) */
.section .text.x86.asm64_syscall.pipe
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pipe)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pipe)

/* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval32 *timeout) */
.section .text.x86.asm64_syscall.select
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_select)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_select)

/* errno_t sched_yield(void) */
.section .text.x86.asm64_syscall.sched_yield
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_yield)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
.section .text.x86.asm64_syscall.mremap
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mremap)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mremap)

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.msync
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_msync)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_msync)

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
.section .text.x86.asm64_syscall.mincore
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mincore)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mincore)

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
.section .text.x86.asm64_syscall.madvise
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_madvise)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_madvise)

/* errno_t shmget(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.shmget
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_shmget)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_shmget)

/* errno_t shmat(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.shmat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_shmat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_shmat)

/* errno_t shmctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.shmctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_shmctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_shmctl)

/* fd_t dup(fd_t fd) */
.section .text.x86.asm64_syscall.dup
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_dup)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_dup)

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
.section .text.x86.asm64_syscall.dup2
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_dup2)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_dup2)

/* errno_t pause(void) */
.section .text.x86.asm64_syscall.pause
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pause)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pause)

/* errno_t nanosleep(struct __timespec32 const *req, struct __timespec32 *rem) */
.section .text.x86.asm64_syscall.nanosleep
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_nanosleep)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_nanosleep)

/* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
.section .text.x86.asm64_syscall.getitimer
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getitimer)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getitimer)

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
.section .text.x86.asm64_syscall.alarm
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_alarm)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_alarm)

/* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
.section .text.x86.asm64_syscall.setitimer
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setitimer)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setitimer)

/* pid_t getpid(void) */
.section .text.x86.asm64_syscall.getpid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getpid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getpid)

/* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
.section .text.x86.asm64_syscall.sendfile
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sendfile)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sendfile)

/* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
.section .text.x86.asm64_syscall.socket
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_socket)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_socket)

/* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm64_syscall.connect
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_connect)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_connect)

/* errno_t accept(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.accept
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_accept)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_accept)

/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
/* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm64_syscall.sendto
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sendto)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sendto)

/* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm64_syscall.recvfrom
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_recvfrom)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_recvfrom)

/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.sendmsg
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sendmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sendmsg)

/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.recvmsg
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_recvmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
.section .text.x86.asm64_syscall.shutdown
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_shutdown)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_shutdown)

/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
.section .text.x86.asm64_syscall.bind
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_bind)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_bind)

/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
.section .text.x86.asm64_syscall.listen
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_listen)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_listen)

/* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm64_syscall.getsockname
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getsockname)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getsockname)

/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
.section .text.x86.asm64_syscall.getpeername
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getpeername)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getpeername)

/* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
.section .text.x86.asm64_syscall.socketpair
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_socketpair)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_socketpair)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
.section .text.x86.asm64_syscall.setsockopt
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setsockopt)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
/* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
.section .text.x86.asm64_syscall.getsockopt
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getsockopt)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getsockopt)

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
.section .text.x86.asm64_syscall.clone
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_clone)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_clone)

/* pid_t fork(void) */
.section .text.x86.asm64_syscall.fork
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fork)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fork)

/* pid_t vfork(void) */
.section .text.x86.asm64_syscall.vfork
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_vfork)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_vfork)

/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
.section .text.x86.asm64_syscall.execve
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_execve)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_execve)

/* void exit(syscall_ulong_t status) */
.section .text.x86.asm64_syscall.exit
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_exit)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_exit)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
.section .text.x86.asm64_syscall.wait4
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_wait4)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_wait4)

/* @param: signo: One of `SIG*' */
/* errno_t kill(pid_t pid, syscall_ulong_t signo) */
.section .text.x86.asm64_syscall.kill
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kill)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kill)

/* errno_t uname(struct utsname *name) */
.section .text.x86.asm64_syscall.uname
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_uname)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_uname)

/* errno_t semget(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.semget
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_semget)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_semget)

/* errno_t semop(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.semop
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_semop)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_semop)

/* errno_t semctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.semctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_semctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_semctl)

/* errno_t shmdt(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.shmdt
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_shmdt)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_shmdt)

/* errno_t msgget(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.msgget
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_msgget)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_msgget)

/* errno_t msgsnd(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.msgsnd
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_msgsnd)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_msgsnd)

/* errno_t msgrcv(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.msgrcv
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_msgrcv)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_msgrcv)

/* errno_t msgctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.msgctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_msgctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_msgctl)

/* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
.section .text.x86.asm64_syscall.fcntl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fcntl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fcntl)

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
.section .text.x86.asm64_syscall.flock
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_flock)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_flock)

/* errno_t fsync(fd_t fd) */
.section .text.x86.asm64_syscall.fsync
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fsync)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fsync)

/* errno_t fdatasync(fd_t fd) */
.section .text.x86.asm64_syscall.fdatasync
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fdatasync)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fdatasync)

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
.section .text.x86.asm64_syscall.truncate
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_truncate)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_truncate)

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
.section .text.x86.asm64_syscall.ftruncate
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ftruncate)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ftruncate)

/* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
.section .text.x86.asm64_syscall.getdents
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getdents)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getdents)

/* ssize_t getcwd(char *buf, size_t size) */
.section .text.x86.asm64_syscall.getcwd
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getcwd)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getcwd)

/* errno_t chdir(char const *path) */
.section .text.x86.asm64_syscall.chdir
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_chdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_chdir)

/* errno_t fchdir(fd_t fd) */
.section .text.x86.asm64_syscall.fchdir
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fchdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fchdir)

/* errno_t rename(char const *oldname, char const *newname_or_path) */
.section .text.x86.asm64_syscall.rename
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rename)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rename)

/* errno_t mkdir(char const *pathname, mode_t mode) */
.section .text.x86.asm64_syscall.mkdir
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mkdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mkdir)

/* errno_t rmdir(char const *path) */
.section .text.x86.asm64_syscall.rmdir
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rmdir)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rmdir)

/* fd_t creat(char const *filename, mode_t mode) */
.section .text.x86.asm64_syscall.creat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_creat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_creat)

/* errno_t link(char const *existing_file, char const *link_file) */
.section .text.x86.asm64_syscall.link
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_link)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_link)

/* errno_t unlink(char const *filename) */
.section .text.x86.asm64_syscall.unlink
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_unlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_unlink)

/* errno_t symlink(char const *link_text, char const *target_path) */
.section .text.x86.asm64_syscall.symlink
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_symlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_symlink)

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
.section .text.x86.asm64_syscall.readlink
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_readlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_readlink)

/* errno_t chmod(char const *filename, mode_t mode) */
.section .text.x86.asm64_syscall.chmod
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_chmod)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_chmod)

/* errno_t fchmod(fd_t fd, mode_t mode) */
.section .text.x86.asm64_syscall.fchmod
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fchmod)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fchmod)

/* errno_t chown(char const *filename, uid_t owner, gid_t group) */
.section .text.x86.asm64_syscall.chown
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_chown)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_chown)

/* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
.section .text.x86.asm64_syscall.fchown
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fchown)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fchown)

/* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
.section .text.x86.asm64_syscall.lchown
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lchown)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lchown)

/* mode_t umask(mode_t mode) */
.section .text.x86.asm64_syscall.umask
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_umask)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_umask)

/* errno_t gettimeofday(struct __timeval32 *tv, struct timezone *tz) */
.section .text.x86.asm64_syscall.gettimeofday
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_gettimeofday)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_gettimeofday)

/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
.section .text.x86.asm64_syscall.getrlimit
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getrlimit)

/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
.section .text.x86.asm64_syscall.getrusage
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getrusage)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getrusage)

/* errno_t sysinfo(struct sysinfo *info) */
.section .text.x86.asm64_syscall.sysinfo
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sysinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sysinfo)

/* clock_t times(struct tms *buf) */
.section .text.x86.asm64_syscall.times
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_times)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_times)

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
.section .text.x86.asm64_syscall.ptrace
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ptrace)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ptrace)

/* uid_t getuid(void) */
.section .text.x86.asm64_syscall.getuid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getuid)

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
.section .text.x86.asm64_syscall.syslog
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_syslog)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_syslog)

/* gid_t getgid(void) */
.section .text.x86.asm64_syscall.getgid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getgid)

/* errno_t setuid(uid_t uid) */
.section .text.x86.asm64_syscall.setuid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setuid)

/* errno_t setgid(gid_t gid) */
.section .text.x86.asm64_syscall.setgid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setgid)

/* uid_t geteuid(void) */
.section .text.x86.asm64_syscall.geteuid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_geteuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_geteuid)

/* gid_t getegid(void) */
.section .text.x86.asm64_syscall.getegid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getegid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getegid)

/* errno_t setpgid(pid_t pid, pid_t pgid) */
.section .text.x86.asm64_syscall.setpgid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setpgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setpgid)

/* pid_t getppid(void) */
.section .text.x86.asm64_syscall.getppid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getppid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getppid)

/* pid_t getpgrp(void) */
.section .text.x86.asm64_syscall.getpgrp
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getpgrp)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getpgrp)

/* pid_t setsid(void) */
.section .text.x86.asm64_syscall.setsid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setsid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setsid)

/* errno_t setreuid(uid_t ruid, uid_t euid) */
.section .text.x86.asm64_syscall.setreuid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setreuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setreuid)

/* errno_t setregid(gid_t rgid, gid_t egid) */
.section .text.x86.asm64_syscall.setregid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setregid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setregid)

/* errno_t getgroups(size_t size, gid_t[] list) */
.section .text.x86.asm64_syscall.getgroups
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getgroups)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getgroups)

/* errno_t setgroups(size_t count, gid_t const *groups) */
.section .text.x86.asm64_syscall.setgroups
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setgroups)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setgroups)

/* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
.section .text.x86.asm64_syscall.setresuid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setresuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setresuid)

/* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
.section .text.x86.asm64_syscall.getresuid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getresuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getresuid)

/* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
.section .text.x86.asm64_syscall.setresgid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setresgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setresgid)

/* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
.section .text.x86.asm64_syscall.getresgid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getresgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getresgid)

/* pid_t getpgid(pid_t pid) */
.section .text.x86.asm64_syscall.getpgid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getpgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getpgid)

/* errno_t setfsuid(uid_t uid) */
.section .text.x86.asm64_syscall.setfsuid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setfsuid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setfsuid)

/* errno_t setfsgid(gid_t gid) */
.section .text.x86.asm64_syscall.setfsgid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setfsgid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setfsgid)

/* pid_t getsid(pid_t pid) */
.section .text.x86.asm64_syscall.getsid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getsid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getsid)

/* errno_t capget(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.capget
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_capget)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_capget)

/* errno_t capset(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.capset
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_capset)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_capset)

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
.section .text.x86.asm64_syscall.rt_sigpending
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_sigpending)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_sigpending)

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec32 const *timeout, size_t sigsetsize) */
.section .text.x86.asm64_syscall.rt_sigtimedwait
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_sigtimedwait)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
/* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.x86.asm64_syscall.rt_sigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_sigqueueinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_sigqueueinfo)

/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
.section .text.x86.asm64_syscall.rt_sigsuspend
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_sigsuspend)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_sigsuspend)

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
.section .text.x86.asm64_syscall.sigaltstack
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sigaltstack)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sigaltstack)

/* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
.section .text.x86.asm64_syscall.utime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_utime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_utime)

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm64_syscall.mknod
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mknod)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mknod)

/* errno_t uselib(char const *library) */
.section .text.x86.asm64_syscall.uselib
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_uselib)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_uselib)

/* errno_t personality(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.personality
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_personality)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_personality)

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
.section .text.x86.asm64_syscall.ustat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ustat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ustat)

/* errno_t statfs(char const *file, struct __statfs32 *buf) */
.section .text.x86.asm64_syscall.statfs
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_statfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_statfs)

/* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
.section .text.x86.asm64_syscall.fstatfs
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fstatfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fstatfs)

/* errno_t sysfs(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.sysfs
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sysfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sysfs)

/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
.section .text.x86.asm64_syscall.getpriority
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getpriority)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getpriority)

/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
.section .text.x86.asm64_syscall.setpriority
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setpriority)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setpriority)

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
.section .text.x86.asm64_syscall.sched_setparam
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_setparam)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_setparam)

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
.section .text.x86.asm64_syscall.sched_getparam
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_getparam)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_getparam)

/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
.section .text.x86.asm64_syscall.sched_setscheduler
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_setscheduler)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_setscheduler)

/* syscall_slong_t sched_getscheduler(pid_t pid) */
.section .text.x86.asm64_syscall.sched_getscheduler
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_getscheduler)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_getscheduler)

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
.section .text.x86.asm64_syscall.sched_get_priority_max
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_get_priority_max)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_get_priority_max)

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
.section .text.x86.asm64_syscall.sched_get_priority_min
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_get_priority_min)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_get_priority_min)

/* errno_t sched_rr_get_interval(pid_t pid, struct __timespec32 *tms) */
.section .text.x86.asm64_syscall.sched_rr_get_interval
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_rr_get_interval)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_rr_get_interval)

/* errno_t mlock(void const *addr, size_t len) */
.section .text.x86.asm64_syscall.mlock
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mlock)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mlock)

/* errno_t munlock(void const *addr, size_t len) */
.section .text.x86.asm64_syscall.munlock
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_munlock)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_munlock)

/* errno_t mlockall(syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.mlockall
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mlockall)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mlockall)

/* errno_t munlockall(void) */
.section .text.x86.asm64_syscall.munlockall
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_munlockall)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_munlockall)

/* errno_t vhangup(void) */
.section .text.x86.asm64_syscall.vhangup
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_vhangup)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_vhangup)

/* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
.section .text.x86.asm64_syscall.modify_ldt
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_modify_ldt)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_modify_ldt)

/* errno_t pivot_root(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.pivot_root
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pivot_root)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pivot_root)

/* errno_t _sysctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall._sysctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall__sysctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall__sysctl)

/* errno_t prctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.prctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_prctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_prctl)

/* errno_t arch_prctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.arch_prctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_arch_prctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_arch_prctl)

/* errno_t adjtimex(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.adjtimex
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_adjtimex)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_adjtimex)

/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
.section .text.x86.asm64_syscall.setrlimit
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setrlimit)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setrlimit)

/* errno_t chroot(char const *path) */
.section .text.x86.asm64_syscall.chroot
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_chroot)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_chroot)

/* errno_t sync(void) */
.section .text.x86.asm64_syscall.sync
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sync)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sync)

/* errno_t acct(char const *filename) */
.section .text.x86.asm64_syscall.acct
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_acct)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_acct)

/* errno_t settimeofday(struct __timeval32 const *tv, struct timezone const *tz) */
.section .text.x86.asm64_syscall.settimeofday
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_settimeofday)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_settimeofday)

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
.section .text.x86.asm64_syscall.mount
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mount)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mount)

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.umount2
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_umount2)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_umount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
.section .text.x86.asm64_syscall.swapon
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_swapon)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_swapon)

/* errno_t swapoff(char const *pathname) */
.section .text.x86.asm64_syscall.swapoff
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_swapoff)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_swapoff)

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
.section .text.x86.asm64_syscall.reboot
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_reboot)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_reboot)

/* errno_t sethostname(char const *name, size_t len) */
.section .text.x86.asm64_syscall.sethostname
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sethostname)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sethostname)

/* errno_t setdomainname(char const *name, size_t len) */
.section .text.x86.asm64_syscall.setdomainname
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setdomainname)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setdomainname)

/* errno_t iopl(syscall_ulong_t level) */
.section .text.x86.asm64_syscall.iopl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_iopl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_iopl)

/* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
.section .text.x86.asm64_syscall.ioperm
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ioperm)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ioperm)

/* errno_t create_module(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.create_module
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_create_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_create_module)

/* errno_t init_module(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.init_module
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_init_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_init_module)

/* errno_t delete_module(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.delete_module
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_delete_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_delete_module)

/* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.get_kernel_syms
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_get_kernel_syms)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_get_kernel_syms)

/* errno_t query_module(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.query_module
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_query_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_query_module)

/* errno_t quotactl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.quotactl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_quotactl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_quotactl)

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.nfsservctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_nfsservctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_nfsservctl)

/* errno_t getpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.getpmsg
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getpmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getpmsg)

/* errno_t putpmsg(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.putpmsg
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_putpmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_putpmsg)

/* errno_t afs_syscall(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.afs_syscall
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_afs_syscall)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_afs_syscall)

/* errno_t tuxcall(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.tuxcall
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_tuxcall)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_tuxcall)

/* errno_t security(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.security
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_security)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_security)

/* pid_t gettid(void) */
.section .text.x86.asm64_syscall.gettid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_gettid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_gettid)

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
.section .text.x86.asm64_syscall.readahead
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_readahead)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_readahead)

/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.setxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setxattr)

/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.lsetxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lsetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lsetxattr)

/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.fsetxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fsetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fsetxattr)

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm64_syscall.getxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getxattr)

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm64_syscall.lgetxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lgetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lgetxattr)

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
.section .text.x86.asm64_syscall.fgetxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fgetxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fgetxattr)

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm64_syscall.listxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_listxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_listxattr)

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
.section .text.x86.asm64_syscall.llistxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_llistxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_llistxattr)

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
.section .text.x86.asm64_syscall.flistxattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_flistxattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_flistxattr)

/* errno_t removexattr(char const *path, char const *name) */
.section .text.x86.asm64_syscall.removexattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_removexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_removexattr)

/* errno_t lremovexattr(char const *path, char const *name) */
.section .text.x86.asm64_syscall.lremovexattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lremovexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lremovexattr)

/* errno_t fremovexattr(int fd, char const *name) */
.section .text.x86.asm64_syscall.fremovexattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fremovexattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fremovexattr)

/* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm64_syscall.tkill
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_tkill)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_tkill)

/* time32_t time(time32_t *timer) */
.section .text.x86.asm64_syscall.time
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_time)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_time)

/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
.section .text.x86.asm64_syscall.futex
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_futex)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_futex)

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
.section .text.x86.asm64_syscall.sched_setaffinity
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_setaffinity)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_setaffinity)

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
.section .text.x86.asm64_syscall.sched_getaffinity
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_getaffinity)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_getaffinity)

/* errno_t set_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.set_thread_area
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_set_thread_area)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_set_thread_area)

/* errno_t io_setup(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.io_setup
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_io_setup)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_io_setup)

/* errno_t io_destroy(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.io_destroy
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_io_destroy)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_io_destroy)

/* errno_t io_getevents(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.io_getevents
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_io_getevents)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_io_getevents)

/* errno_t io_submit(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.io_submit
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_io_submit)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_io_submit)

/* errno_t io_cancel(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.io_cancel
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_io_cancel)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_io_cancel)

/* errno_t get_thread_area(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.get_thread_area
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_get_thread_area)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_get_thread_area)

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.lookup_dcookie
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lookup_dcookie)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lookup_dcookie)

/* fd_t epoll_create(syscall_ulong_t size) */
.section .text.x86.asm64_syscall.epoll_create
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_epoll_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_epoll_create)

/* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.x86.asm64_syscall.epoll_ctl_old
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_epoll_ctl_old)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_epoll_ctl_old)

/* errno_t epoll_wait_old(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.x86.asm64_syscall.epoll_wait_old
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_epoll_wait_old)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_epoll_wait_old)

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.remap_file_pages
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_remap_file_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_remap_file_pages)

/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
.section .text.x86.asm64_syscall.getdents64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getdents64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getdents64)

/* pid_t set_tid_address(pid_t *tidptr) */
.section .text.x86.asm64_syscall.set_tid_address
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_set_tid_address)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_set_tid_address)

/* errno_t restart_syscall(void) */
.section .text.x86.asm64_syscall.restart_syscall
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_restart_syscall)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_restart_syscall)

/* errno_t semtimedop(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.semtimedop
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_semtimedop)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_semtimedop)

/* errno_t fadvise64(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.fadvise64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fadvise64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fadvise64)

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
.section .text.x86.asm64_syscall.timer_create
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timer_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timer_create)

/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspec32 const *value, struct __itimerspec32 *ovalue) */
.section .text.x86.asm64_syscall.timer_settime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timer_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timer_settime)

/* errno_t timer_gettime(timer_t timerid, struct __itimerspec32 *value) */
.section .text.x86.asm64_syscall.timer_gettime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timer_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timer_gettime)

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
.section .text.x86.asm64_syscall.timer_getoverrun
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timer_getoverrun)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timer_getoverrun)

/* errno_t timer_delete(timer_t timerid) */
.section .text.x86.asm64_syscall.timer_delete
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timer_delete)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timer_delete)

/* errno_t clock_settime(clockid_t clock_id, struct __timespec32 const *tp) */
.section .text.x86.asm64_syscall.clock_settime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_clock_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_clock_settime)

/* errno_t clock_gettime(clockid_t clock_id, struct __timespec32 *tp) */
.section .text.x86.asm64_syscall.clock_gettime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_clock_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_clock_gettime)

/* errno_t clock_getres(clockid_t clock_id, struct __timespec32 *res) */
.section .text.x86.asm64_syscall.clock_getres
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_clock_getres)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_clock_getres)

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespec32 const *requested_time, struct __timespec32 *remaining) */
.section .text.x86.asm64_syscall.clock_nanosleep
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_clock_nanosleep)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_clock_nanosleep)

/* void exit_group(syscall_ulong_t exit_code) */
.section .text.x86.asm64_syscall.exit_group
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_exit_group)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_exit_group)

/* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
.section .text.x86.asm64_syscall.epoll_wait
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_epoll_wait)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_epoll_wait)

/* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
.section .text.x86.asm64_syscall.epoll_ctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_epoll_ctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_epoll_ctl)

/* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
.section .text.x86.asm64_syscall.tgkill
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_tgkill)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_tgkill)

/* errno_t utimes(char const *filename, struct __timeval32 const[2] times) */
.section .text.x86.asm64_syscall.utimes
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_utimes)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_utimes)

/* errno_t vserver(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.vserver
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_vserver)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_vserver)

/* errno_t mbind(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mbind
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mbind)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mbind)

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.set_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_set_mempolicy)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_set_mempolicy)

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.get_mempolicy
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_get_mempolicy)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_get_mempolicy)

/* errno_t mq_open(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mq_open
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mq_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mq_open)

/* errno_t mq_unlink(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mq_unlink
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mq_unlink)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mq_unlink)

/* errno_t mq_timedsend(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mq_timedsend
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mq_timedsend)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mq_timedsend)

/* errno_t mq_timedreceive(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mq_timedreceive
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mq_timedreceive)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mq_timedreceive)

/* errno_t mq_notify(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mq_notify
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mq_notify)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mq_notify)

/* errno_t mq_getsetattr(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mq_getsetattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mq_getsetattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mq_getsetattr)

/* errno_t kexec_load(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.kexec_load
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kexec_load)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kexec_load)

/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
.section .text.x86.asm64_syscall.waitid
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_waitid)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_waitid)

/* errno_t add_key(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.add_key
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_add_key)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_add_key)

/* errno_t request_key(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.request_key
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_request_key)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_request_key)

/* errno_t keyctl(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.keyctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_keyctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_keyctl)

/* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
.section .text.x86.asm64_syscall.ioprio_set
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ioprio_set)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ioprio_set)

/* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
.section .text.x86.asm64_syscall.ioprio_get
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ioprio_get)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ioprio_get)

/* errno_t inotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.inotify_init
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_inotify_init)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_inotify_init)

/* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.inotify_add_watch
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_inotify_add_watch)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_inotify_add_watch)

/* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.inotify_rm_watch
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_inotify_rm_watch)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_inotify_rm_watch)

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.migrate_pages
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_migrate_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_migrate_pages)

/* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
.section .text.x86.asm64_syscall.openat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_openat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_openat)

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
.section .text.x86.asm64_syscall.mkdirat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mkdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mkdirat)

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
.section .text.x86.asm64_syscall.mknodat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mknodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
.section .text.x86.asm64_syscall.fchownat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fchownat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fchownat)

/* errno_t futimesat(fd_t dirfd, const char *filename, struct __timeval32 const[2] times) */
.section .text.x86.asm64_syscall.futimesat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_futimesat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_futimesat)

/* errno_t linux_fstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
.section .text.x86.asm64_syscall.linux_fstatat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_linux_fstatat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_linux_fstatat)

/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
.section .text.x86.asm64_syscall.unlinkat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_unlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_unlinkat)

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
.section .text.x86.asm64_syscall.renameat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_renameat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_renameat)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm64_syscall.linkat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_linkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_linkat)

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
.section .text.x86.asm64_syscall.symlinkat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_symlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_symlinkat)

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
.section .text.x86.asm64_syscall.readlinkat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_readlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_readlinkat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
.section .text.x86.asm64_syscall.fchmodat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fchmodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
.section .text.x86.asm64_syscall.faccessat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_faccessat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_faccessat)

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec32 const *timeout, void const *sigmask_sigset_and_len) */
.section .text.x86.asm64_syscall.pselect6
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pselect6)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pselect6)

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm64_syscall.ppoll
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ppoll)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ppoll)

/* param flags: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.unshare
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_unshare)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_unshare)

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.set_robust_list
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_set_robust_list)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_set_robust_list)

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.get_robust_list
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_get_robust_list)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_get_robust_list)

/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.splice
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_splice)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_splice)

/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.tee
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_tee)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_tee)

/* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.sync_file_range
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sync_file_range)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sync_file_range)

/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.vmsplice
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_vmsplice)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_vmsplice)

/* errno_t move_pages(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.move_pages
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_move_pages)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_move_pages)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespec32 const[2] times, atflag_t flags) */
.section .text.x86.asm64_syscall.utimensat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_utimensat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_utimensat)

/* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
.section .text.x86.asm64_syscall.epoll_pwait
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_epoll_pwait)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_epoll_pwait)

/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
.section .text.x86.asm64_syscall.signalfd
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_signalfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_signalfd)

/* Return file descriptor for new interval timer source */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.timerfd_create
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timerfd_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timerfd_create)

/* fd_t eventfd(syscall_ulong_t initval) */
.section .text.x86.asm64_syscall.eventfd
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_eventfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_eventfd)

/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
.section .text.x86.asm64_syscall.fallocate
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fallocate)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
/* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspec32 const *utmr, struct __itimerspec32 *otmr) */
.section .text.x86.asm64_syscall.timerfd_settime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timerfd_settime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timerfd_settime)

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t ufd, struct __itimerspec32 *otmr) */
.section .text.x86.asm64_syscall.timerfd_gettime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_timerfd_gettime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_timerfd_gettime)

/* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.accept4
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_accept4)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_accept4)

/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.signalfd4
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_signalfd4)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_signalfd4)

/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.eventfd2
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_eventfd2)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_eventfd2)

/* fd_t epoll_create1(syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.epoll_create1
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_epoll_create1)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
.section .text.x86.asm64_syscall.dup3
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_dup3)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_dup3)

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
.section .text.x86.asm64_syscall.pipe2
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pipe2)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pipe2)

/* errno_t inotify_init1(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.inotify_init1
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_inotify_init1)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_inotify_init1)

/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm64_syscall.preadv
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_preadv)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_preadv)

/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
.section .text.x86.asm64_syscall.pwritev
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pwritev)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pwritev)

/* @param: signo: One of `SIG*' */
/* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
.section .text.x86.asm64_syscall.rt_tgsigqueueinfo
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rt_tgsigqueueinfo)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rt_tgsigqueueinfo)

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.perf_event_open
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_perf_event_open)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_perf_event_open)

/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec32 *tmo) */
.section .text.x86.asm64_syscall.recvmmsg
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_recvmmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_recvmmsg)

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.fanotify_init
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fanotify_init)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fanotify_init)

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.fanotify_mark
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fanotify_mark)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fanotify_mark)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
.section .text.x86.asm64_syscall.prlimit64
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_prlimit64)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_prlimit64)

/* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.name_to_handle_at
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_name_to_handle_at)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_name_to_handle_at)

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.open_by_handle_at
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_open_by_handle_at)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_open_by_handle_at)

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.clock_adjtime
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_clock_adjtime)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_clock_adjtime)

/* errno_t syncfs(fd_t fd) */
.section .text.x86.asm64_syscall.syncfs
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_syncfs)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_syncfs)

/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.sendmmsg
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sendmmsg)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sendmmsg)

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
.section .text.x86.asm64_syscall.setns
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_setns)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_setns)

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
.section .text.x86.asm64_syscall.getcpu
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getcpu)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getcpu)

/* ssize_t process_vm_readv(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.process_vm_readv
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_process_vm_readv)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_process_vm_readv)

/* ssize_t process_vm_writev(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.process_vm_writev
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_process_vm_writev)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_process_vm_writev)

/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
.section .text.x86.asm64_syscall.kcmp
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kcmp)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kcmp)

/* errno_t finit_module(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.finit_module
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_finit_module)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_finit_module)

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.sched_setattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_setattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_setattr)

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.sched_getattr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sched_getattr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sched_getattr)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
.section .text.x86.asm64_syscall.renameat2
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_renameat2)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_renameat2)

/* errno_t seccomp(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.seccomp
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_seccomp)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_seccomp)

/* errno_t getrandom(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.getrandom
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getrandom)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getrandom)

/* errno_t memfd_create(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.memfd_create
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_memfd_create)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_memfd_create)

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.kexec_file_load
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kexec_file_load)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kexec_file_load)

/* errno_t bpf(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.bpf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_bpf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_bpf)

/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
.section .text.x86.asm64_syscall.execveat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_execveat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_execveat)

/* errno_t userfaultfd(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.userfaultfd
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_userfaultfd)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_userfaultfd)

/* errno_t membarrier(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.membarrier
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_membarrier)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_membarrier)

/* errno_t mlock2(int TODO_PROTOTYPE) */
.section .text.x86.asm64_syscall.mlock2
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mlock2)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mlock2)

/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm64_syscall.readf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_readf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_readf)

/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
.section .text.x86.asm64_syscall.writef
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_writef)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_writef)

/* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
.section .text.x86.asm64_syscall.hop
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_hop)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_hop)

/* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm64_syscall.hopf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_hopf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_hopf)

/* errno_t kstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm64_syscall.kstat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kstat)

/* errno_t kfstat(fd_t fd, struct stat *statbuf) */
.section .text.x86.asm64_syscall.kfstat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kfstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kfstat)

/* errno_t klstat(char const *filename, struct stat *statbuf) */
.section .text.x86.asm64_syscall.klstat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_klstat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_klstat)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
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
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
/* errno_t detach(pid_t pid) */
.section .text.x86.asm64_syscall.detach
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_detach)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
.section .text.x86.asm64_syscall.getdrives
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_getdrives)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm64_syscall.frealpath4
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_frealpath4)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm64_syscall.frealpathat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_frealpathat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
/* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, void **arguments) */
.section .text.x86.asm64_syscall.rpc_schedule
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rpc_schedule)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rpc_schedule)

/* syscall_slong_t sysctl(syscall_ulong_t command, void *arg) */
.section .text.x86.asm64_syscall.sysctl
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_sysctl)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_sysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
.section .text.x86.asm64_syscall.openpty
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_openpty)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_openpty)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
/* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
.section .text.x86.asm64_syscall.set_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_set_exception_handler)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
/* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
.section .text.x86.asm64_syscall.get_exception_handler
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_get_exception_handler)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_get_exception_handler)

/* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
.section .text.x86.asm64_syscall.ioctlf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_ioctlf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_ioctlf)

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm64_syscall.pread64f
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pread64f)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pread64f)

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
.section .text.x86.asm64_syscall.pwrite64f
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pwrite64f)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pwrite64f)

/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm64_syscall.readvf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_readvf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_readvf)

/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
.section .text.x86.asm64_syscall.writevf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_writevf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_writevf)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
/* errno_t set_library_listdef(struct library_listdef const *listdef) */
.section .text.x86.asm64_syscall.set_library_listdef
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_set_library_listdef)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
/* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
.section .text.x86.asm64_syscall.debugtrap
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_debugtrap)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_debugtrap)

/* syscall_slong_t rpc_service(void) */
.section .text.x86.asm64_syscall.rpc_service
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_rpc_service)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_rpc_service)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
/* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
.section .text.x86.asm64_syscall.lfutex
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lfutex)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lfutex)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm64_syscall.lfutexexpr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lfutexexpr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
/* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr const *exprv, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
.section .text.x86.asm64_syscall.lfutexlockexpr
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_lfutexlockexpr)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
.section .text.x86.asm64_syscall.mktty
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_mktty)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
/* errno_t raiseat(struct ucpustate const *state, struct __siginfo_struct const *si) */
.section .text.x86.asm64_syscall.raiseat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_raiseat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, struct exception_data const *exception, syscall_ulong_t unwind_error) */
.section .text.x86.asm64_syscall.coredump
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_coredump)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_coredump)

/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
.section .text.x86.asm64_syscall.kreaddir
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kreaddir)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kreaddir)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
.section .text.x86.asm64_syscall.fchdirat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fchdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fchdirat)

/* uint64_t fsmode(uint64_t mode) */
.section .text.x86.asm64_syscall.fsmode
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fsmode)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fsmode)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
/* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
.section .text.x86.asm64_syscall.maplibrary
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_maplibrary)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_maplibrary)

/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
.section .text.x86.asm64_syscall.kreaddirf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kreaddirf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kreaddirf)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
.section .text.x86.asm64_syscall.fmkdirat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fmkdirat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fmkdirat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
.section .text.x86.asm64_syscall.fmknodat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fmknodat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fmknodat)

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
.section .text.x86.asm64_syscall.kfstatat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_kfstatat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_kfstatat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
.section .text.x86.asm64_syscall.frenameat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_frenameat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_frenameat)

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
.section .text.x86.asm64_syscall.fsymlinkat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_fsymlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_fsymlinkat)

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE|AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
.section .text.x86.asm64_syscall.freadlinkat
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_freadlinkat)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_freadlinkat)

/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm64_syscall.preadvf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_preadvf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_preadvf)

/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
.section .text.x86.asm64_syscall.pwritevf
INTERN_WEAK_FUNCTION(__x86_asm64_syscall_pwritevf)
/* TODO: x86_64_printKernelSyscallWrapper_asm64_syscall() */
END(__x86_asm64_syscall_pwritevf)

