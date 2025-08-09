/* HASH CRC-32:0x734ea309 */
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
#ifndef GUARD_KERNEL_CORE_ARCH_ARM_SYSCALL_WRAPPERS_S
#define GUARD_KERNEL_CORE_ARCH_ARM_SYSCALL_WRAPPERS_S 1

#include <kernel/compiler.h>

/* TODO: arm_printKernelSyscallWrapperCommon() */










/* errno_t restart_syscall(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 0) */

/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit(syscall_ulong_t exit_code) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 1) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 2) */

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 3) */

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 4) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 5) */

/* Close a given file descriptor/handle `fd' */
/* errno_t close(fd_t fd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 6) */

/* fd_t creat(char const *filename, mode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8) */

/* errno_t link(char const *existing_file, char const *link_file) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 9) */

/* errno_t unlink(char const *filename) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 10) */

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
/* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 11) */

/* errno_t chdir(char const *path) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 12) */

/* time32_t time(time32_t *timer) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 13) */

/* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 14) */

/* errno_t chmod(char const *filename, mode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 15) */

/* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 16) */

/* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 19) */

/* pid_t getpid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 20) */

/* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 21) */

/* errno_t umount(char const *special_file) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 22) */

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid(uint16_t uid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 23) */

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uint16_t getuid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 24) */

/* errno_t stime(time32_t const *t) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 25) */

/* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 26) */

/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 27) */

/* Same as `select(0, NULL, NULL, NULL, NULL)' */
/* errno_t pause(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 29) */

/* @param: times: When NULL, set the current time */
/* errno_t utime(char const *filename, struct utimbuf32 const *times) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 30) */

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
/* errno_t access(char const *filename, syscall_ulong_t type) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 33) */

/* errno_t nice(syscall_slong_t inc) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 34) */

/* errno_t sync(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 36) */

/* errno_t kill(pid_t pid, signo_t signo) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 37) */

/* errno_t rename(char const *oldname, char const *newname_or_path) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 38) */

/* errno_t mkdir(char const *pathname, mode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 39) */

/* errno_t rmdir(char const *path) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 40) */

/* fd_t dup(fd_t fd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 41) */

/* errno_t pipe(fd_t[2] pipedes) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 42) */

/* clock_t times(struct tms *buf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 43) */

/* errno_t brk(void *addr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 45) */

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid(uint16_t gid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 46) */

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* uint16_t getgid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 47) */

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint16_t geteuid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 49) */

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint16_t getegid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 50) */

/* errno_t acct(char const *filename) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 51) */

/* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 52) */

/* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 54) */

/* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 55) */

/* errno_t setpgid(pid_t pid, pid_t pgid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 57) */

/* mode_t umask(mode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 60) */

/* errno_t chroot(char const *path) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 61) */

/* errno_t ustat(dev_t dev, struct ustat *ubuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 62) */

/* fd_t dup2(fd_t oldfd, fd_t newfd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 63) */

/* pid_t getppid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 64) */

/* pid_t getpgrp(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 65) */

/* pid_t setsid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 66) */

/* errno_t sigaction(signo_t signo, struct __old_kernel_sigaction const *act, struct __old_kernel_sigaction *oact) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 67) */

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid(uint16_t ruid, uint16_t euid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 70) */

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid(uint16_t rgid, uint16_t egid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 71) */

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t sigsuspend(struct __old_sigset_struct const *set) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 72) */

/* errno_t sigpending(struct __old_sigset_struct *set) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 73) */

/* errno_t sethostname(char const *name, size_t len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 74) */

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t setrlimit(syscall_ulong_t resource, struct rlimit32 const *rlimits) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 75) */

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t getrlimit(syscall_ulong_t resource, struct rlimit32 *rlimits) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 76) */

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 77) */

/* errno_t gettimeofday(struct timeval32 *tv, struct timezone *tz) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 78) */

/* errno_t settimeofday(struct timeval32 const *tv, struct timezone const *tz) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 79) */

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups(size_t count, uint16_t[] list) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 80) */

/* errno_t setgroups(size_t count, uint16_t const *groups) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 81) */

/* ssize_t select(struct sel_arg_struct const *arg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 82) */

/* errno_t symlink(char const *link_text, char const *target_path) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 83) */

/* ssize_t readlink(char const *path, char *buf, size_t buflen) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 85) */

/* errno_t uselib(char const *library) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 86) */

/* @param: swapflags: Set of `SWAP_FLAG_*' */
/* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 87) */

/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
/* errno_t reboot(syscall_ulong_t how) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 88) */

/* Read exactly one directory entry from `fd'
 * Note that the linux version of this system call has one additional argument `count'.
 * However, within the  linux kernel implementation,  that argument is  unconditionally
 * ignored,  and the system call will _always_ read exactly 1 directory entry from `fd'
 * @return: 1 : Read on directory entry
 * @return: 0 : End-of-directory */
/* syscall_slong_t readdir(fd_t fd, struct old_linux_dirent *buf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 89) */

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
/* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 90) */

/* errno_t munmap(void *addr, size_t len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 91) */

/* errno_t truncate(char const *filename, syscall_ulong_t length) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 92) */

/* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 93) */

/* errno_t fchmod(fd_t fd, mode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 94) */

/* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 95) */

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 96) */

/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
/* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 97) */

/* errno_t statfs(char const *file, struct statfs32 *buf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 99) */

/* errno_t fstatfs(fd_t file, struct statfs32 *buf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 100) */

/* syscall_slong_t socketcall(syscall_ulong_t call, syscall_ulong_t *args) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 102) */

/* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 103) */

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer(syscall_ulong_t which, struct itimerval const *newval, struct itimerval *oldval) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 104) */

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer(syscall_ulong_t which, struct itimerval *curr_value) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 105) */

/* errno_t stat(char const *filename, struct linux_stat *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 106) */

/* errno_t lstat(char const *filename, struct linux_stat *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 107) */

/* errno_t fstat(fd_t fd, struct linux_stat *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 108) */

/* errno_t vhangup(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 111) */

/* Syscall to call a syscall */
/* errno_t syscall(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 113) */

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage32 *usage) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 114) */

/* errno_t swapoff(char const *pathname) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 115) */

/* errno_t sysinfo(struct sysinfo *info) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 116) */

/* errno_t ipc(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 117) */

/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
/* errno_t fsync(fd_t fd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 118) */

/* void sigreturn(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 119) */

/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 120) */

/* errno_t setdomainname(char const *name, size_t len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 121) */

/* errno_t uname(struct utsname *name) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 122) */

/* errno_t adjtimex(struct timex32 *ntx) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 124) */

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
/* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 125) */

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t sigprocmask(syscall_ulong_t how, struct __old_sigset_struct const *set, struct __old_sigset_struct *oset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 126) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 128) */

/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
/* errno_t delete_module(char const *name, oflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 129) */

/* errno_t quotactl(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 131) */

/* pid_t getpgid(pid_t pid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 132) */

/* errno_t fchdir(fd_t fd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 133) */

/* errno_t bdflush(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 134) */

/* errno_t sysfs(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 135) */

/* errno_t personality(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 136) */

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid(uint16_t uid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 138) */

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid(uint16_t gid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 139) */

/* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 140) */

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents(fd_t fd, struct linux_dirent *buf, size_t buflen) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 141) */

/* ssize_t _newselect(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval32 *timeout) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 142) */

/* errno_t flock(fd_t fd, syscall_ulong_t operation) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 143) */

/* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 144) */

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 145) */

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 146) */

/* pid_t getsid(pid_t pid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 147) */

/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
/* errno_t fdatasync(fd_t fd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 148) */

/* errno_t _sysctl(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 149) */

/* errno_t mlock(void const *addr, size_t len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 150) */

/* errno_t munlock(void const *addr, size_t len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 151) */

/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
/* errno_t mlockall(syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 152) */

/* errno_t munlockall(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 153) */

/* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 154) */

/* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 155) */

/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
/* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 156) */

/* syscall_slong_t sched_getscheduler(pid_t pid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 157) */

/* errno_t sched_yield(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 158) */

/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 159) */

/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 160) */

/* errno_t sched_rr_get_interval(pid_t pid, struct timespec32 *ts) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 161) */

/* errno_t nanosleep(struct timespec32 const *req, struct timespec32 *rem) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 162) */

/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
/* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 163) */

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 164) */

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 165) */

/* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 168) */

/* errno_t nfsservctl(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 169) */

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 170) */

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 171) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 172) */

/* void rt_sigreturn(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 173) */

/* errno_t rt_sigaction(signo_t signo, struct __kernel_sigaction const *act, struct __kernel_sigaction *oact, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 174) */

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
/* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 175) */

/* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 176) */

/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec32 const *timeout, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 177) */

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfo_struct const *uinfo) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 178) */

/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
/* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 179) */

/* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 180) */

/* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 181) */

/* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 182) */

/* ssize_t getcwd(char *buf, size_t size) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 183) */

/* errno_t capget(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 184) */

/* errno_t capset(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 185) */

/* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 186) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 187) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 190) */

/* errno_t ugetrlimit(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 191) */

/* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 192) */

/* errno_t truncate64(char const *filename, uint64_t length) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 193) */

/* errno_t ftruncate64(fd_t fd, uint64_t length) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 194) */

/* errno_t stat64(char const *filename, struct linux_stat64 *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 195) */

/* errno_t lstat64(char const *filename, struct linux_stat64 *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 196) */

/* errno_t fstat64(fd_t fd, struct linux_stat64 *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 197) */

/* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 198) */

/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
/* uint32_t getuid32(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 199) */

/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
/* uint32_t getgid32(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 200) */

/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint32_t geteuid32(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 201) */

/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
/* uint32_t getegid32(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 202) */

/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 203) */

/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setregid32(uint32_t rgid, uint32_t egid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 204) */

/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
/* ssize_t getgroups32(size_t count, uint32_t[] list) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 205) */

/* errno_t setgroups32(size_t count, uint32_t const *groups) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 206) */

/* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 207) */

/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 208) */

/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 209) */

/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 210) */

/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
/* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 211) */

/* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 212) */

/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setuid32(uint32_t uid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 213) */

/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setgid32(uint32_t gid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 214) */

/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
/* errno_t setfsuid32(uint32_t uid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 215) */

/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
/* errno_t setfsgid32(uint32_t gid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 216) */

/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
/* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 217) */

/* errno_t pivot_root(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 218) */

/* errno_t mincore(void *start, size_t len, uint8_t *vec) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 219) */

/* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 220) */

/* syscall_slong_t fcntl64(fd_t fd, fcntl_t command, void *arg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 221) */

/* pid_t gettid(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 224) */

/* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 225) */

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 226) */

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 227) */

/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
/* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 228) */

/* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 229) */

/* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 230) */

/* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 231) */

/* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 232) */

/* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 233) */

/* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 234) */

/* errno_t removexattr(char const *path, char const *name) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 235) */

/* errno_t lremovexattr(char const *path, char const *name) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 236) */

/* errno_t fremovexattr(fd_t fd, char const *name) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 237) */

/* errno_t tkill(pid_t tid, signo_t signo) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 238) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 239) */

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 240) */

/* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 241) */

/* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 242) */

/* errno_t io_setup(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 243) */

/* errno_t io_destroy(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 244) */

/* errno_t io_getevents(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 245) */

/* errno_t io_submit(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 246) */

/* errno_t io_cancel(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 247) */

/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
/* void exit_group(syscall_ulong_t exit_code) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 248) */

/* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 249) */

/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
/* fd_t epoll_create(syscall_ulong_t size) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 250) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 251) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 252) */

/* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 253) */

/* pid_t set_tid_address(pid_t *tidptr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 256) */

/* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 257) */

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspec32 const *value, struct itimerspec32 *ovalue) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 258) */

/* errno_t timer_gettime(timer_t timerid, struct itimerspec32 *value) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 259) */

/* syscall_slong_t timer_getoverrun(timer_t timerid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 260) */

/* errno_t timer_delete(timer_t timerid) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 261) */

/* errno_t clock_settime(clockid_t clock_id, struct timespec32 const *tp) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 262) */

/* errno_t clock_gettime(clockid_t clock_id, struct timespec32 *tp) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 263) */

/* errno_t clock_getres(clockid_t clock_id, struct timespec32 *res) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 264) */

/* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespec32 const *requested_time, struct timespec32 *remaining) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 265) */

/* errno_t statfs64(char const *file, struct statfs64 *buf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 266) */

/* errno_t fstatfs64(fd_t file, struct statfs64 *buf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 267) */

/* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 268) */

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes(char const *filename, struct timeval32 const[2] times) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 269) */

/* errno_t arm_fadvise64_64(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 270) */

/* errno_t pciconfig_iobase(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 271) */

/* errno_t pciconfig_read(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 272) */

/* errno_t pciconfig_write(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 273) */

/* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 274) */

/* errno_t mq_unlink(char const *name) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 275) */

/* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec32 const *abs_timeout) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 276) */

/* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec32 const *abs_timeout) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 277) */

/* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 278) */

/* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 279) */

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage32 *ru) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 280) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 281) */

/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
/* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 282) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 283) */

/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
/* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 284) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 285) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 286) */

/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 287) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 288) */

/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @return: * : [<= bufsize] The actual # of send bytes */
/* ssize_t send(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 289) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 290) */

/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @return: * : [<= bufsize] The actual # of received bytes */
/* ssize_t recv(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 291) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 292) */

/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
/* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 293) */

/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
/* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 294) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 295) */

/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
/* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t msg_flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 296) */

/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
/* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t msg_flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 297) */

/* errno_t semop(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 298) */

/* errno_t semget(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 299) */

/* errno_t semctl(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 300) */

/* errno_t msgsnd(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 301) */

/* errno_t msgrcv(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 302) */

/* errno_t msgget(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 303) */

/* errno_t msgctl(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 304) */

/* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 305) */

/* errno_t shmdt(void const *shmaddr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 306) */

/* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 307) */

/* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 308) */

/* errno_t add_key(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 309) */

/* errno_t request_key(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 310) */

/* errno_t keyctl(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 311) */

/* errno_t semtimedop(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 312) */

/* errno_t vserve(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 313) */

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 314) */

/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
/* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 315) */

/* fd_t inotify_init(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 316) */

/* @param: mask: Set of `IN_ALL_EVENTS | ...' */
/* int inotify_add_watch(fd_t notify_fd, char const *pathname, uint32_t mask) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 317) */

/* @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
/* errno_t inotify_rm_watch(fd_t notify_fd, int wd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 318) */

/* errno_t mbind(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 319) */

/* errno_t get_mempolicy(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 320) */

/* errno_t set_mempolicy(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 321) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 322) */

/* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 323) */

/* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 324) */

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 325) */

/* errno_t futimesat(fd_t dirfd, char const *filename, struct timeval32 const[2] times) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 326) */

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 327) */

/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
/* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 328) */

/* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 329) */

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 330) */

/* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 331) */

/* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 332) */

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 333) */

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
/* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 334) */

/* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec32 const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 335) */

/* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 336) */

/* param: what: Set of `CLONE_*' */
/* errno_t unshare(syscall_ulong_t what) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 337) */

/* errno_t set_robust_list(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 338) */

/* errno_t get_robust_list(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 339) */

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 340) */

/* errno_t sync_file_range2(fd_t fd, syscall_ulong_t flags, uint64_t offset, uint64_t count) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 341) */

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 342) */

/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
/* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 343) */

/* errno_t move_pages(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 344) */

/* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 345) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 346) */

/* errno_t kexec_load(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 347) */

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat(fd_t dirfd, char const *filename, struct timespec32 const[2] times, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 348) */

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
/* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 349) */

/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
/* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 350) */

/* fd_t eventfd(syscall_ulong_t initval) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 351) */

/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
/* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 352) */

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspec32 const *utmr, struct itimerspec32 *otmr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 353) */

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime(fd_t timerfd, struct itimerspec32 *otmr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 354) */

/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
/* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 355) */

/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
/* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 356) */

/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
/* fd_t epoll_create1(syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 357) */

/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
/* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 358) */

/* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 359) */

/* @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
/* fd_t inotify_init1(syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 360) */

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 361) */

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 362) */

/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
/* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfo_struct const *uinfo) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 363) */

/* errno_t perf_event_open(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 364) */

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec32 const *tmo) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 365) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 366) */

/* errno_t fanotify_init(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 367) */

/* errno_t fanotify_mark(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 368) */

/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
/* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 369) */

/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
/* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 370) */

/* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 371) */

/* errno_t clock_adjtime(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 372) */

/* errno_t syncfs(fd_t fd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 373) */

/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
/* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 374) */

/* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 375) */

/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
/* ssize_t process_vm_readv(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 376) */

/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
/* ssize_t process_vm_writev(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 377) */

/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
/* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 378) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 379) */

/* errno_t sched_setattr(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 380) */

/* errno_t sched_getattr(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 381) */

/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
/* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 382) */

/* errno_t seccomp(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 383) */

/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
/* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 384) */

/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
/* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 385) */

/* errno_t bpf(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 386) */

/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 387) */

/* fd_t userfaultfd(syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 388) */

/* errno_t membarrier(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 389) */

/* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 390) */

/* errno_t copy_file_range(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 391) */

/* errno_t preadv2(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 392) */

/* errno_t pwritev2(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 393) */

/* errno_t pkey_mprotect(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t pkey) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 394) */

/* syscall_slong_t pkey_alloc(syscall_ulong_t flags, syscall_ulong_t access_rights) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 395) */

/* errno_t pkey_free(syscall_ulong_t key) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 396) */

/* errno_t statx(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 397) */

/* errno_t rseq(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 398) */

/* errno_t io_pgetevents(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 399) */

/* errno_t migrate_pages(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 400) */

/* errno_t kexec_file_load(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 401) */

/* errno_t clock_gettime64(clockid_t clock_id, struct timespec64 *tp) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 403) */

/* errno_t clock_settime64(clockid_t clock_id, struct timespec64 const *tp) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 404) */

/* errno_t clock_adjtime64(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 405) */

/* errno_t clock_getres_time64(clockid_t clock_id, struct timespec64 *res) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 406) */

/* errno_t clock_nanosleep_time64(clockid_t clock_id, syscall_ulong_t flags, struct timespec64 const *requested_time, struct timespec64 *remaining) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 407) */

/* errno_t timer_gettime64(timer_t timerid, struct itimerspec64 *value) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 408) */

/* @param: flags: Set of `0 | TIMER_ABSTIME' */
/* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct itimerspec64 const *value, struct itimerspec64 *ovalue) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 409) */

/* Return the next expiration time of UFD */
/* errno_t timerfd_gettime64(fd_t timerfd, struct itimerspec64 *otmr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 410) */

/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
/* errno_t timerfd_settime64(fd_t timerfd, syscall_ulong_t flags, struct itimerspec64 const *utmr, struct itimerspec64 *otmr) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 411) */

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
/* errno_t utimensat_time64(fd_t dirfd, char const *filename, struct timespec64 const[2] times, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 412) */

/* ssize_t pselect6_time64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec64 const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 413) */

/* ssize_t ppoll_time64(struct pollfd *fds, size_t nfds, struct timespec64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 414) */

/* errno_t io_pgetevents_time64(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 416) */

/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
/* ssize_t recvmmsg_time64(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec64 const *tmo) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 417) */

/* errno_t mq_timedsend_time64(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec64 const *abs_timeout) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 418) */

/* ssize_t mq_timedreceive_time64(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec64 const *abs_timeout) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 419) */

/* errno_t semtimedop_time64(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 420) */

/* syscall_slong_t rt_sigtimedwait_time64(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec64 const *timeout, size_t sigsetsize) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 421) */

/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
/* syscall_slong_t futex_time64(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 422) */

/* errno_t sched_rr_get_interval_time64(pid_t pid, struct timespec64 *ts) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 423) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 424) */

/* errno_t io_uring_setup(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 425) */

/* errno_t io_uring_enter(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 426) */

/* errno_t io_uring_register(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 427) */

/* errno_t open_tree(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 428) */

/* errno_t move_mount(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 429) */

/* errno_t fsopen(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 430) */

/* errno_t fsconfig(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 431) */

/* errno_t fsmount(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 432) */

/* errno_t fspick(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 433) */

/* Return a `HANDLE_TYPE_PIDFD' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not  allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
/* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 434) */

/* syscall_slong_t clone3(struct clone_args *cl_args, size_t size) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 435) */

/* @param: flags: Set of `CLOSE_RANGE_*' from <linux/close_range.h> */
/* errno_t close_range(unsigned int minfd, unsigned int maxfd, unsigned int flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 436) */

/* errno_t openat2(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 437) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 438) */

/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
/* errno_t faccessat2(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 439) */

/* errno_t process_madvise(int TODO_PROTOTYPE) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 440) */

/* Trigger a breakpoint */
/* void breakpoint(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 983041) */

/* Flush instruction cache */
/* errno_t cacheflush(void const *start, void const *end, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 983042) */

/* Clear CPSR.T=0x10 */
/* void usr26(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 983043) */

/* Set CPSR.T=0x10 */
/* void usr32(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 983044) */

/* Set calling thread's TLS pointer */
/* errno_t set_tls(void const *tlsval) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 983045) */

/* Get calling thread's TLS pointer */
/* void *get_tls(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 983046) */

/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
/* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323075) */

/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
/* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323076) */

/* Returns a bitset of all of the currently mounted dos-drives */
/* syscall_slong_t getdrives(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323077) */

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323078) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323079) */

/* Returns  the  absolute   filesystem  path  for   the  specified   file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is  dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the   required   buffer   size,   rather   than   the   used    size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323080) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323081) */

/* Create a new pseudo-terminal driver and store handles to both the
 * master  and slave ends  of the connection  in the given pointers. */
/* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323083) */

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323084) */

/* time64_t time64(time64_t *timer) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323085) */

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The  newly created  device automatically gets  assigned an arbitrary  device number, before
 * being made available under a file `/dev/${name}'  (or rather: as ${name} within the  devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
/* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323086) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323087) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323088) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323089) */

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
/* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, union coredump_info const *reason, unwind_errno_t unwind_error) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323090) */

/* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323091) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323092) */

/* errno_t stime64(time64_t const *t) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323097) */

/* @param: times: When NULL, set the current time */
/* errno_t utime64(char const *filename, struct utimbuf64 const *times) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323102) */

/* errno_t ftime64(struct timeb64 *tp) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323107) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323120) */

/* End a transaction
 * If  the  transaction was  successful,  return normally  (by  returning `-EOK').
 * If    the   transaction   failed,   `sys_rtm_begin()'   returns   `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
/* errno_t rtm_end(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323121) */

/* Abort the current transaction  by having `sys_rtm_begin()' return  with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise,  this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
/* errno_t rtm_abort(syscall_ulong_t code) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323122) */

/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
/* syscall_ulong_t rtm_test(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323123) */

/* syscall_slong_t ioctlf(fd_t fd, ioctl_t command, iomode_t mode, void *arg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323126) */

/* uint64_t fsmode(uint64_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323132) */

/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
/* errno_t getrusage64(syscall_slong_t who, struct rusage64 *tv) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323149) */

/* errno_t gettimeofday64(struct timeval64 *tv, struct timezone *tz) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323150) */

/* errno_t settimeofday64(struct timeval64 const *tv, struct timezone const *tz) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323151) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323158) */

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323176) */

/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
/* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323177) */

/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
/* pid_t wait4_64(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage64 *usage) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323186) */

/* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval64 *timeout) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323214) */

/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
/* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323217) */

/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
/* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323218) */

/* syscall_slong_t ksysctl(ioctl_t command, void *arg) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323221) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323230) */

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
 * a no-op (semantically speaking, it does nothing). But when enabled,
 * it  is really only usable in conjunction with the userprocmask. The
 * exact usage can be seen in `chkuserprocmask(3)'.
 * 
 * @return: 0 : Always, unconditionally returned. */
/* errno_t rpc_serve_sysret(void) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323231) */

/* errno_t nanosleep64(struct timespec64 const *req, struct timespec64 *rem) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323234) */

/* void ksigreturn(struct ucpustate const *restore_cpu, struct fpustate const *restore_fpu, struct sigset_with_size const *restore_sigmask, struct rpc_syscall_info const *restart_sc_info) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323245) */

/* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323252) */

/* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323253) */

/* errno_t kstat(char const *filename, struct __kos_stat *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323267) */

/* errno_t klstat(char const *filename, struct __kos_stat *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323268) */

/* errno_t kfstat(fd_t fd, struct __kos_stat *statbuf) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323269) */

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323289) */

/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally     or'd     with     any     of     `READDIR_SKIPREL | READDIR_WANTEOF' */
/* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323290) */

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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323312) */

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
/* errno_t lfutexexpr(uintptr_t *futexaddr, void *base, struct lfutexexpr const *expr, struct timespec64 const *timeout, syscall_ulong_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323313) */

/* >> set_userprocmask_address(2)
 * Register the address of  the calling thread's userprocmask  controller.
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
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323328) */

/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
/* errno_t utimes64(char const *filename, struct timeval64 const[2] times) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323341) */

/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
/* errno_t waitid64(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage64 *ru) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323352) */

/* @param: atflags: Set of `AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @param: mask:    Set of `IN_ALL_EVENTS | ...' */
/* int inotify_add_watch_at(fd_t notify_fd, fd_t dirfd, char const *pathname, atflag_t atflags, uint32_t mask) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323389) */

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323395) */

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323396) */

/* errno_t futimesat64(fd_t dirfd, char const *filename, struct timeval64 const[2] times) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323398) */

/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
/* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *statbuf, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323399) */

/* @param: flags: Set of `0 | AT_DOSPATH' */
/* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323403) */

/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
/* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323404) */

/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
/* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323405) */

/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
/* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323406) */

/* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
/* TODO: arm_printKernelSyscallWrapper_TODO(sysno: 8323424) */


#endif /* !GUARD_KERNEL_CORE_ARCH_ARM_SYSCALL_WRAPPERS_S */
