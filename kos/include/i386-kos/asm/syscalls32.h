/* HASH CRC-32:0xe69b8456 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

/************************************************************************/
/* SYSCALL IDS                                                          */
/************************************************************************/
#ifndef __NR_restart_syscall
#define __NR_restart_syscall              0x0                    /* errno_t restart_syscall(void) */
/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define __NR_exit                         0x1                    /* void exit(syscall_ulong_t exit_code) */
/* Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
#define __NR_fork                         0x2                    /* pid_t fork(void) */
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
#define __NR_read                         0x3                    /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
#define __NR_write                        0x4                    /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
/* Open a new file handle to the file specified by `FILENAME'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_DATABLOCK:              For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
#define __NR_open                         0x5                    /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `FD' */
#define __NR_close                        0x6                    /* errno_t close(fd_t fd) */
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR_waitpid                      0x7                    /* pid_t waitpid(pid_t pid, int32_t *stat_loc, syscall_ulong_t options) */
#define __NR_creat                        0x8                    /* fd_t creat(char const *filename, mode_t mode) */
#define __NR_link                         0x9                    /* errno_t link(char const *existing_file, char const *link_file) */
#define __NR_unlink                       0xa                    /* errno_t unlink(char const *filename) */
/* Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
#define __NR_execve                       0xb                    /* errno_t execve(char const *path, __HYBRID_PTR32(char const) const *argv, __HYBRID_PTR32(char const) const *envp) */
#define __NR_chdir                        0xc                    /* errno_t chdir(char const *path) */
#define __NR_time                         0xd                    /* int32_t time(int32_t *timer) */
#define __NR_mknod                        0xe                    /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define __NR_chmod                        0xf                    /* errno_t chmod(char const *filename, mode_t mode) */
#define __NR_lchown                       0x10                   /* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
#define __NR_break                        0x11                   /* errno_t break(void) */
#define __NR_oldstat                      0x12                   /* errno_t oldstat(char const *filename, struct linux_oldstat *statbuf) */
#define __NR_lseek                        0x13                   /* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
#define __NR_getpid                       0x14                   /* pid_t getpid(void) */
#define __NR_mount                        0x15                   /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
#define __NR_umount                       0x16                   /* errno_t umount(char const *special_file) */
#define __NR_setuid                       0x17                   /* errno_t setuid(uint16_t uid) */
#define __NR_getuid                       0x18                   /* uint16_t getuid(void) */
#define __NR_stime                        0x19                   /* errno_t stime(time32_t const *t) */
#define __NR_ptrace                       0x1a                   /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
#define __NR_alarm                        0x1b                   /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
#define __NR_oldfstat                     0x1c                   /* errno_t oldfstat(fd_t fd, struct linux_oldstat *statbuf) */
/* Same as `select(0, NULL, NULL, NULL, NULL)' */
#define __NR_pause                        0x1d                   /* errno_t pause(void) */
#define __NR_utime                        0x1e                   /* errno_t utime(char const *filename, struct utimbufx32 const *times) */
#define __NR_stty                         0x1f                   /* errno_t stty(void) */
#define __NR_gtty                         0x20                   /* errno_t gtty(void) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define __NR_access                       0x21                   /* errno_t access(char const *filename, syscall_ulong_t type) */
#define __NR_nice                         0x22                   /* errno_t nice(syscall_slong_t inc) */
#define __NR_ftime                        0x23                   /* errno_t ftime(struct timebx32 *tp) */
#define __NR_sync                         0x24                   /* errno_t sync(void) */
#define __NR_kill                         0x25                   /* errno_t kill(pid_t pid, signo_t signo) */
#define __NR_rename                       0x26                   /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define __NR_mkdir                        0x27                   /* errno_t mkdir(char const *pathname, mode_t mode) */
#define __NR_rmdir                        0x28                   /* errno_t rmdir(char const *path) */
#define __NR_dup                          0x29                   /* fd_t dup(fd_t fd) */
#define __NR_pipe                         0x2a                   /* errno_t pipe(fd_t[2] pipedes) */
#define __NR_times                        0x2b                   /* clock_t times(struct tms *buf) */
#define __NR_prof                         0x2c                   /* errno_t prof(void) */
#define __NR_brk                          0x2d                   /* errno_t brk(void *addr) */
#define __NR_setgid                       0x2e                   /* errno_t setgid(uint16_t gid) */
#define __NR_getgid                       0x2f                   /* uint16_t getgid(void) */
#define __NR_signal                       0x30                   /* sighandler_t signal(signo_t signo, sighandler_t handler) */
#define __NR_geteuid                      0x31                   /* uint16_t geteuid(void) */
#define __NR_getegid                      0x32                   /* uint16_t getegid(void) */
#define __NR_acct                         0x33                   /* errno_t acct(char const *filename) */
#define __NR_umount2                      0x34                   /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
#define __NR_lock                         0x35                   /* errno_t lock(void) */
#define __NR_ioctl                        0x36                   /* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR_fcntl                        0x37                   /* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR_mpx                          0x38                   /* errno_t mpx(void) */
#define __NR_setpgid                      0x39                   /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define __NR_ulimit                       0x3a                   /* errno_t ulimit(void) */
#define __NR_oldolduname                  0x3b                   /* errno_t oldolduname(struct linux_oldolduname *name) */
#define __NR_umask                        0x3c                   /* mode_t umask(mode_t mode) */
#define __NR_chroot                       0x3d                   /* errno_t chroot(char const *path) */
#define __NR_ustat                        0x3e                   /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
#define __NR_dup2                         0x3f                   /* fd_t dup2(fd_t oldfd, fd_t newfd) */
#define __NR_getppid                      0x40                   /* pid_t getppid(void) */
#define __NR_getpgrp                      0x41                   /* pid_t getpgrp(void) */
#define __NR_setsid                       0x42                   /* pid_t setsid(void) */
#define __NR_sigaction                    0x43                   /* errno_t sigaction(signo_t signo, struct __sigactionx32 const *act, struct __sigactionx32 *oact) */
#define __NR_sgetmask                     0x44                   /* syscall_ulong_t sgetmask(void) */
#define __NR_ssetmask                     0x45                   /* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
#define __NR_setreuid                     0x46                   /* errno_t setreuid(uint16_t ruid, uint16_t euid) */
#define __NR_setregid                     0x47                   /* errno_t setregid(uint16_t rgid, uint16_t egid) */
#define __NR_sigsuspend                   0x48                   /* errno_t sigsuspend(struct __sigset_struct const *set) */
#define __NR_sigpending                   0x49                   /* errno_t sigpending(struct __sigset_struct *set) */
#define __NR_sethostname                  0x4a                   /* errno_t sethostname(char const *name, size_t len) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR_setrlimit                    0x4b                   /* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR_getrlimit                    0x4c                   /* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
#define __NR_getrusage                    0x4d                   /* errno_t getrusage(syscall_slong_t who, struct rusagex32 *tv) */
#define __NR_gettimeofday                 0x4e                   /* errno_t gettimeofday(struct timevalx32 *tv, struct timezone *tz) */
#define __NR_settimeofday                 0x4f                   /* errno_t settimeofday(struct timevalx32 const *tv, struct timezone const *tz) */
/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
#define __NR_getgroups                    0x50                   /* ssize_t getgroups(size_t count, uint16_t[] list) */
#define __NR_setgroups                    0x51                   /* errno_t setgroups(size_t count, uint16_t const *groups) */
#define __NR_select                       0x52                   /* ssize_t select(struct sel_arg_structx32 const *arg) */
#define __NR_symlink                      0x53                   /* errno_t symlink(char const *link_text, char const *target_path) */
#define __NR_oldlstat                     0x54                   /* errno_t oldlstat(char const *filename, struct linux_oldstat *statbuf) */
#define __NR_readlink                     0x55                   /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
#define __NR_uselib                       0x56                   /* errno_t uselib(char const *library) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define __NR_swapon                       0x57                   /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
#define __NR_reboot                       0x58                   /* errno_t reboot(syscall_ulong_t how) */
/* Read exactly one directory entry from `fd'
 * Note that the linux version of this system call has one additional argument `count'.
 * However, within the linux kernel implementation, that argument is unconditionally
 * ignored, and the system call will _always_ read exactly 1 directory entry from `fd'
 * @return: 1 : Read on directory entry
 * @return: 0 : End-of-directory */
#define __NR_readdir                      0x59                   /* syscall_slong_t readdir(fd_t fd, struct old_linux_direntx32 *buf) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
#define __NR_mmap                         0x5a                   /* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
#define __NR_munmap                       0x5b                   /* errno_t munmap(void *addr, size_t len) */
#define __NR_truncate                     0x5c                   /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define __NR_ftruncate                    0x5d                   /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
#define __NR_fchmod                       0x5e                   /* errno_t fchmod(fd_t fd, mode_t mode) */
#define __NR_fchown                       0x5f                   /* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define __NR_getpriority                  0x60                   /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define __NR_setpriority                  0x61                   /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
#define __NR_profil                       0x62                   /* errno_t profil(uint16_t *sample_buffer, size_t size, size_t offset, syscall_ulong_t scale) */
#define __NR_statfs                       0x63                   /* errno_t statfs(char const *file, struct __statfsx32 *buf) */
#define __NR_fstatfs                      0x64                   /* errno_t fstatfs(fd_t file, struct __statfsx32 *buf) */
#define __NR_ioperm                       0x65                   /* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
#define __NR_socketcall                   0x66                   /* errno_t socketcall(syscall_ulong_t call, syscall_ulong_t *args) */
#define __NR_syslog                       0x67                   /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR_setitimer                    0x68                   /* errno_t setitimer(syscall_ulong_t which, struct __itimervalx32 const *newval, struct __itimervalx32 *oldval) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR_getitimer                    0x69                   /* errno_t getitimer(syscall_ulong_t which, struct __itimervalx32 *curr_value) */
#define __NR_stat                         0x6a                   /* errno_t stat(char const *filename, struct linux_statx32 *statbuf) */
#define __NR_lstat                        0x6b                   /* errno_t lstat(char const *filename, struct linux_statx32 *statbuf) */
#define __NR_fstat                        0x6c                   /* errno_t fstat(fd_t fd, struct linux_statx32 *statbuf) */
#define __NR_olduname                     0x6d                   /* errno_t olduname(struct linux_olduname *name) */
#define __NR_iopl                         0x6e                   /* errno_t iopl(syscall_ulong_t level) */
#define __NR_vhangup                      0x6f                   /* errno_t vhangup(void) */
#define __NR_idle                         0x70                   /* errno_t idle(void) */
#define __NR_vm86old                      0x71                   /* errno_t vm86old(int TODO_PROTOTYPE) */
/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR_wait4                        0x72                   /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusagex32 *usage) */
#define __NR_swapoff                      0x73                   /* errno_t swapoff(char const *pathname) */
#define __NR_sysinfo                      0x74                   /* errno_t sysinfo(struct sysinfo *info) */
#define __NR_ipc                          0x75                   /* errno_t ipc(int TODO_PROTOTYPE) */
/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
#define __NR_fsync                        0x76                   /* errno_t fsync(fd_t fd) */
/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
#define __NR_sigreturn                    0x77                   /* void sigreturn(struct fpustate32 const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info32 const *sc_info, struct ucpustate32 const *restore_cpu) */
#define __NR_clone                        0x78                   /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
#define __NR_setdomainname                0x79                   /* errno_t setdomainname(char const *name, size_t len) */
#define __NR_uname                        0x7a                   /* errno_t uname(struct utsname *name) */
#define __NR_modify_ldt                   0x7b                   /* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
#define __NR_adjtimex                     0x7c                   /* errno_t adjtimex(int TODO_PROTOTYPE) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED' */
#define __NR_mprotect                     0x7d                   /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR_sigprocmask                  0x7e                   /* errno_t sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset) */
#define __NR_create_module                0x7f                   /* errno_t create_module(int TODO_PROTOTYPE) */
#define __NR_init_module                  0x80                   /* errno_t init_module(int TODO_PROTOTYPE) */
#define __NR_delete_module                0x81                   /* errno_t delete_module(int TODO_PROTOTYPE) */
#define __NR_get_kernel_syms              0x82                   /* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
#define __NR_quotactl                     0x83                   /* errno_t quotactl(int TODO_PROTOTYPE) */
#define __NR_getpgid                      0x84                   /* pid_t getpgid(pid_t pid) */
#define __NR_fchdir                       0x85                   /* errno_t fchdir(fd_t fd) */
#define __NR_bdflush                      0x86                   /* errno_t bdflush(int TODO_PROTOTYPE) */
#define __NR_sysfs                        0x87                   /* errno_t sysfs(int TODO_PROTOTYPE) */
#define __NR_personality                  0x88                   /* errno_t personality(int TODO_PROTOTYPE) */
#define __NR_afs_syscall                  0x89                   /* errno_t afs_syscall(int TODO_PROTOTYPE) */
#define __NR_setfsuid                     0x8a                   /* errno_t setfsuid(uint16_t uid) */
#define __NR_setfsgid                     0x8b                   /* errno_t setfsgid(uint16_t gid) */
#define __NR__llseek                      0x8c                   /* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define __NR_getdents                     0x8d                   /* ssize_t getdents(fd_t fd, struct linux_direntx32 *buf, size_t buflen) */
#define __NR__newselect                   0x8e                   /* ssize_t _newselect(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timevalx32 *timeout) */
#define __NR_flock                        0x8f                   /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
#define __NR_msync                        0x90                   /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read data into `count' seperate buffers, though still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
#define __NR_readv                        0x91                   /* ssize_t readv(fd_t fd, struct iovecx32 const *iovec, size_t count) */
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write data from `count' seperate buffers, though still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
#define __NR_writev                       0x92                   /* ssize_t writev(fd_t fd, struct iovecx32 const *iovec, size_t count) */
#define __NR_getsid                       0x93                   /* pid_t getsid(pid_t pid) */
/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
#define __NR_fdatasync                    0x94                   /* errno_t fdatasync(fd_t fd) */
#define __NR__sysctl                      0x95                   /* errno_t _sysctl(int TODO_PROTOTYPE) */
#define __NR_mlock                        0x96                   /* errno_t mlock(void const *addr, size_t len) */
#define __NR_munlock                      0x97                   /* errno_t munlock(void const *addr, size_t len) */
/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
#define __NR_mlockall                     0x98                   /* errno_t mlockall(syscall_ulong_t flags) */
#define __NR_munlockall                   0x99                   /* errno_t munlockall(void) */
#define __NR_sched_setparam               0x9a                   /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
#define __NR_sched_getparam               0x9b                   /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE', optionally or'd with `SCHED_RESET_ON_FORK' */
#define __NR_sched_setscheduler           0x9c                   /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define __NR_sched_getscheduler           0x9d                   /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define __NR_sched_yield                  0x9e                   /* errno_t sched_yield(void) */
#define __NR_sched_get_priority_max       0x9f                   /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define __NR_sched_get_priority_min       0xa0                   /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define __NR_sched_rr_get_interval        0xa1                   /* errno_t sched_rr_get_interval(pid_t pid, struct timespecx32 *tms) */
#define __NR_nanosleep                    0xa2                   /* errno_t nanosleep(struct timespecx32 const *req, struct timespecx32 *rem) */
/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
#define __NR_mremap                       0xa3                   /* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define __NR_setresuid                    0xa4                   /* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
#define __NR_getresuid                    0xa5                   /* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
#define __NR_vm86                         0xa6                   /* errno_t vm86(int TODO_PROTOTYPE) */
#define __NR_query_module                 0xa7                   /* errno_t query_module(int TODO_PROTOTYPE) */
#define __NR_poll                         0xa8                   /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
#define __NR_nfsservctl                   0xa9                   /* errno_t nfsservctl(int TODO_PROTOTYPE) */
#define __NR_setresgid                    0xaa                   /* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
#define __NR_getresgid                    0xab                   /* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
#define __NR_prctl                        0xac                   /* errno_t prctl(int TODO_PROTOTYPE) */
/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
#define __NR_rt_sigreturn                 0xad                   /* void rt_sigreturn(struct fpustate32 const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info32 const *sc_info, struct ucpustate32 const *restore_cpu) */
#define __NR_rt_sigaction                 0xae                   /* errno_t rt_sigaction(signo_t signo, struct sigactionx32 const *act, struct sigactionx32 *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR_rt_sigprocmask               0xaf                   /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
#define __NR_rt_sigpending                0xb0                   /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define __NR_rt_sigtimedwait              0xb1                   /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfox32_struct *info, struct timespecx32 const *timeout, size_t sigsetsize) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:            [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define __NR_rt_sigqueueinfo              0xb2                   /* errno_t rt_sigqueueinfo(pid_t tgid, signo_t usigno, struct __siginfox32_struct const *uinfo) */
#define __NR_rt_sigsuspend                0xb3                   /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define __NR_pread64                      0xb4                   /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define __NR_pwrite64                     0xb5                   /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
#define __NR_chown                        0xb6                   /* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
#define __NR_getcwd                       0xb7                   /* ssize_t getcwd(char *buf, size_t size) */
#define __NR_capget                       0xb8                   /* errno_t capget(int TODO_PROTOTYPE) */
#define __NR_capset                       0xb9                   /* errno_t capset(int TODO_PROTOTYPE) */
#define __NR_sigaltstack                  0xba                   /* errno_t sigaltstack(struct __sigaltstackx32 const *ss, struct __sigaltstackx32 *oss) */
#define __NR_sendfile                     0xbb                   /* ssize_t sendfile(fd_t out_fd, fd_t in_fd, __ULONG32_TYPE__ *pin_offset, size_t num_bytes) */
#define __NR_getpmsg                      0xbc                   /* errno_t getpmsg(int TODO_PROTOTYPE) */
#define __NR_putpmsg                      0xbd                   /* errno_t putpmsg(int TODO_PROTOTYPE) */
/* Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the parent process remaining suspended until the
 * child process invokes one of the following system calls:
 *   - `exit(2)'       Terminate the child process
 *   - `exit_group(2)' Terminate the child process
 *   - `execve(2)'     Create a new VM that is populated with the specified process
 *                     image. The parent process will only be resumed in case the
 *                     new program image could be loaded successfully. Otherwise,
 *                     the call to `execve(2)' returns normally in the child.
 *                     Other functions from the exec()-family behave the same
 * 
 * Care must be taken when using this system call, since you have to make sure that
 * the child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in the parent process. The same also goes for heap
 * functions, but generally speaking: you really shouldn't do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3), which
 * is something that KOS intentionally doesn't do, since I feel like doing so only
 * adds unnecessary bloat to code that doesn't rely on this)
 * 
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which case the parent process will not actually get suspended until the child
 * process performs any of the actions above. */
#define __NR_vfork                        0xbe                   /* pid_t vfork(void) */
#define __NR_ugetrlimit                   0xbf                   /* errno_t ugetrlimit(int TODO_PROTOTYPE) */
#define __NR_mmap2                        0xc0                   /* void *mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
#define __NR_truncate64                   0xc1                   /* errno_t truncate64(char const *filename, uint64_t length) */
#define __NR_ftruncate64                  0xc2                   /* errno_t ftruncate64(fd_t fd, uint64_t length) */
#define __NR_stat64                       0xc3                   /* errno_t stat64(char const *filename, struct linux_statx32_64 *statbuf) */
#define __NR_lstat64                      0xc4                   /* errno_t lstat64(char const *filename, struct linux_statx32_64 *statbuf) */
#define __NR_fstat64                      0xc5                   /* errno_t fstat64(fd_t fd, struct linux_statx32_64 *statbuf) */
#define __NR_lchown32                     0xc6                   /* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
#define __NR_getuid32                     0xc7                   /* uint32_t getuid32(void) */
#define __NR_getgid32                     0xc8                   /* uint32_t getgid32(void) */
#define __NR_geteuid32                    0xc9                   /* uint32_t geteuid32(void) */
#define __NR_getegid32                    0xca                   /* uint32_t getegid32(void) */
#define __NR_setreuid32                   0xcb                   /* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
#define __NR_setregid32                   0xcc                   /* errno_t setregid32(uint32_t rgid, uint32_t egid) */
/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
#define __NR_getgroups32                  0xcd                   /* ssize_t getgroups32(size_t count, uint32_t[] list) */
#define __NR_setgroups32                  0xce                   /* errno_t setgroups32(size_t count, uint32_t const *groups) */
#define __NR_fchown32                     0xcf                   /* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
#define __NR_setresuid32                  0xd0                   /* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
#define __NR_getresuid32                  0xd1                   /* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
#define __NR_setresgid32                  0xd2                   /* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
#define __NR_getresgid32                  0xd3                   /* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
#define __NR_chown32                      0xd4                   /* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
#define __NR_setuid32                     0xd5                   /* errno_t setuid32(uint32_t uid) */
#define __NR_setgid32                     0xd6                   /* errno_t setgid32(uint32_t gid) */
#define __NR_setfsuid32                   0xd7                   /* errno_t setfsuid32(uint32_t uid) */
#define __NR_setfsgid32                   0xd8                   /* errno_t setfsgid32(uint32_t gid) */
#define __NR_pivot_root                   0xd9                   /* errno_t pivot_root(int TODO_PROTOTYPE) */
#define __NR_mincore                      0xda                   /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define __NR_madvise                      0xdb                   /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define __NR_getdents64                   0xdc                   /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
#define __NR_fcntl64                      0xdd                   /* syscall_slong_t fcntl64(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR_gettid                       0xe0                   /* pid_t gettid(void) */
#define __NR_readahead                    0xe1                   /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR_setxattr                     0xe2                   /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR_lsetxattr                    0xe3                   /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR_fsetxattr                    0xe4                   /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR_getxattr                     0xe5                   /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR_lgetxattr                    0xe6                   /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR_fgetxattr                    0xe7                   /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define __NR_listxattr                    0xe8                   /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR_llistxattr                   0xe9                   /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR_flistxattr                   0xea                   /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define __NR_removexattr                  0xeb                   /* errno_t removexattr(char const *path, char const *name) */
#define __NR_lremovexattr                 0xec                   /* errno_t lremovexattr(char const *path, char const *name) */
#define __NR_fremovexattr                 0xed                   /* errno_t fremovexattr(fd_t fd, char const *name) */
#define __NR_tkill                        0xee                   /* errno_t tkill(pid_t tid, signo_t signo) */
#define __NR_sendfile64                   0xef                   /* ssize_t sendfile64(fd_t out_fd, fd_t in_fd, __ULONG64_TYPE__ *pin_offset, size_t num_bytes) */
/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
#define __NR_futex                        0xf0                   /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define __NR_sched_setaffinity            0xf1                   /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define __NR_sched_getaffinity            0xf2                   /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define __NR_set_thread_area              0xf3                   /* errno_t set_thread_area(int TODO_PROTOTYPE) */
#define __NR_get_thread_area              0xf4                   /* errno_t get_thread_area(int TODO_PROTOTYPE) */
#define __NR_io_setup                     0xf5                   /* errno_t io_setup(int TODO_PROTOTYPE) */
#define __NR_io_destroy                   0xf6                   /* errno_t io_destroy(int TODO_PROTOTYPE) */
#define __NR_io_getevents                 0xf7                   /* errno_t io_getevents(int TODO_PROTOTYPE) */
#define __NR_io_submit                    0xf8                   /* errno_t io_submit(int TODO_PROTOTYPE) */
#define __NR_io_cancel                    0xf9                   /* errno_t io_cancel(int TODO_PROTOTYPE) */
#define __NR_fadvise64                    0xfa                   /* errno_t fadvise64(int TODO_PROTOTYPE) */
/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define __NR_exit_group                   0xfc                   /* void exit_group(syscall_ulong_t exit_code) */
#define __NR_lookup_dcookie               0xfd                   /* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
#define __NR_epoll_create                 0xfe                   /* fd_t epoll_create(syscall_ulong_t size) */
/* @param: op: One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL', `EPOLL_CTL_MOD' */
#define __NR_epoll_ctl                    0xff                   /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
#define __NR_epoll_wait                   0x100                  /* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
#define __NR_remap_file_pages             0x101                  /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
#define __NR_set_tid_address              0x102                  /* pid_t set_tid_address(pid_t *tidptr) */
#define __NR_timer_create                 0x103                  /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
#define __NR_timer_settime                0x104                  /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspecx32 const *value, struct itimerspecx32 *ovalue) */
#define __NR_timer_gettime                0x105                  /* errno_t timer_gettime(timer_t timerid, struct itimerspecx32 *value) */
#define __NR_timer_getoverrun             0x106                  /* syscall_slong_t timer_getoverrun(timer_t timerid) */
#define __NR_timer_delete                 0x107                  /* errno_t timer_delete(timer_t timerid) */
#define __NR_clock_settime                0x108                  /* errno_t clock_settime(clockid_t clock_id, struct timespecx32 const *tp) */
#define __NR_clock_gettime                0x109                  /* errno_t clock_gettime(clockid_t clock_id, struct timespecx32 *tp) */
#define __NR_clock_getres                 0x10a                  /* errno_t clock_getres(clockid_t clock_id, struct timespecx32 *res) */
#define __NR_clock_nanosleep              0x10b                  /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespecx32 const *requested_time, struct timespecx32 *remaining) */
#define __NR_statfs64                     0x10c                  /* errno_t statfs64(char const *file, struct __statfsx32_64 *buf) */
#define __NR_fstatfs64                    0x10d                  /* errno_t fstatfs64(fd_t file, struct __statfsx32_64 *buf) */
#define __NR_tgkill                       0x10e                  /* errno_t tgkill(pid_t tgid, pid_t tid, signo_t signo) */
#define __NR_utimes                       0x10f                  /* errno_t utimes(char const *filename, struct timevalx32 const[2] times) */
#define __NR_fadvise64_64                 0x110                  /* errno_t fadvise64_64(int TODO_PROTOTYPE) */
#define __NR_vserver                      0x111                  /* errno_t vserver(int TODO_PROTOTYPE) */
#define __NR_mbind                        0x112                  /* errno_t mbind(int TODO_PROTOTYPE) */
#define __NR_get_mempolicy                0x113                  /* errno_t get_mempolicy(int TODO_PROTOTYPE) */
#define __NR_set_mempolicy                0x114                  /* errno_t set_mempolicy(int TODO_PROTOTYPE) */
#define __NR_mq_open                      0x115                  /* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
#define __NR_mq_unlink                    0x116                  /* errno_t mq_unlink(char const *name) */
#define __NR_mq_timedsend                 0x117                  /* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespecx32 const *abs_timeout) */
#define __NR_mq_timedreceive              0x118                  /* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespecx32 const *abs_timeout) */
#define __NR_mq_notify                    0x119                  /* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
#define __NR_mq_getsetattr                0x11a                  /* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
#define __NR_kexec_load                   0x11b                  /* errno_t kexec_load(int TODO_PROTOTYPE) */
/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED',
 *                  optionally or'd with `WNOHANG | WNOWAIT' */
#define __NR_waitid                       0x11c                  /* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfox32_struct *infop, syscall_ulong_t options, struct rusagex32 *ru) */
#define __NR_add_key                      0x11e                  /* errno_t add_key(int TODO_PROTOTYPE) */
#define __NR_request_key                  0x11f                  /* errno_t request_key(int TODO_PROTOTYPE) */
#define __NR_keyctl                       0x120                  /* errno_t keyctl(int TODO_PROTOTYPE) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define __NR_ioprio_set                   0x121                  /* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define __NR_ioprio_get                   0x122                  /* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
#define __NR_inotify_init                 0x123                  /* errno_t inotify_init(int TODO_PROTOTYPE) */
#define __NR_inotify_add_watch            0x124                  /* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
#define __NR_inotify_rm_watch             0x125                  /* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
#define __NR_migrate_pages                0x126                  /* errno_t migrate_pages(int TODO_PROTOTYPE) */
/* Open a new file handle to the file specified by `FILENAME'
 * When `oflags & O_CREAT', then `mode' specifies the initial
 * file access permissions with which the file should be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:                   When `O_PATH' was given
 *   - HANDLE_TYPE_BLOCKDEVICE:            For `S_IFBLK' files
 *   - HANDLE_TYPE_CHARACTERDEVICE:        For `S_IFCHR' files (in this case, `O_NOCTTY' gains meaning)
 *   - HANDLE_TYPE_FIFO_USER:              For `S_IFIFO' files
 *   - HANDLE_TYPE_DATABLOCK:              For `S_IFLNK' files (only when `O_SYMLINK' was given)
 *   - HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: For `S_IFDIR' files from special one-shot directories
 *   - HANDLE_TYPE_FILE:                   For `S_IFREG' and `S_IFDIR' (~normal~) files
 *   - *:                                  Certain filesystem names can literally return anything, such
 *                                         as `/proc/self/fd/1234', which is more like `dup(1234)' */
#define __NR_openat                       0x127                  /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
#define __NR_mkdirat                      0x128                  /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
#define __NR_mknodat                      0x129                  /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_fchownat                     0x12a                  /* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
#define __NR_futimesat                    0x12b                  /* errno_t futimesat(fd_t dirfd, char const *filename, struct timevalx32 const[2] times) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_fstatat64                    0x12c                  /* errno_t fstatat64(fd_t dirfd, char const *filename, struct linux_statx32_64 *statbuf, atflag_t flags) */
/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
#define __NR_unlinkat                     0x12d                  /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define __NR_renameat                     0x12e                  /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define __NR_linkat                       0x12f                  /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define __NR_symlinkat                    0x130                  /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
#define __NR_readlinkat                   0x131                  /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_fchmodat                     0x132                  /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH' */
#define __NR_faccessat                    0x133                  /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
#define __NR_pselect6                     0x134                  /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespecx32 const *timeout, void const *sigmask_sigset_and_len) */
#define __NR_ppoll                        0x135                  /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespecx32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* param flags: Set of `CLONE_*' */
#define __NR_unshare                      0x136                  /* errno_t unshare(syscall_ulong_t flags) */
#define __NR_set_robust_list              0x137                  /* errno_t set_robust_list(int TODO_PROTOTYPE) */
#define __NR_get_robust_list              0x138                  /* errno_t get_robust_list(int TODO_PROTOTYPE) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR_splice                       0x139                  /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
#define __NR_sync_file_range              0x13a                  /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR_tee                          0x13b                  /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR_vmsplice                     0x13c                  /* ssize_t vmsplice(fd_t fdout, struct iovecx32 const *iov, size_t count, syscall_ulong_t flags) */
#define __NR_move_pages                   0x13d                  /* errno_t move_pages(int TODO_PROTOTYPE) */
#define __NR_getcpu                       0x13e                  /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
#define __NR_epoll_pwait                  0x13f                  /* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
#define __NR_utimensat                    0x140                  /* errno_t utimensat(fd_t dirfd, char const *filename, struct timespecx32 const[2] times, atflag_t flags) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `SIGMASK' to the waiting thread/process. */
#define __NR_signalfd                     0x141                  /* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
#define __NR_timerfd_create               0x142                  /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
#define __NR_eventfd                      0x143                  /* fd_t eventfd(syscall_ulong_t initval) */
/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
#define __NR_fallocate                    0x144                  /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags' has the `TFD_TIMER_ABSTIME' flag set the timeout value
 * is absolute. Optionally return the old expiration time in `otmr''
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
#define __NR_timerfd_settime              0x145                  /* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspecx32 const *utmr, struct itimerspecx32 *otmr) */
/* Return the next expiration time of UFD */
#define __NR_timerfd_gettime              0x146                  /* errno_t timerfd_gettime(fd_t timerfd, struct itimerspecx32 *otmr) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `SIGMASK' to the waiting thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
#define __NR_signalfd4                    0x147                  /* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC' */
#define __NR_eventfd2                     0x148                  /* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
#define __NR_epoll_create1                0x149                  /* fd_t epoll_create1(syscall_ulong_t flags) */
/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
#define __NR_dup3                         0x14a                  /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
#define __NR_pipe2                        0x14b                  /* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
#define __NR_inotify_init1                0x14c                  /* errno_t inotify_init1(int TODO_PROTOTYPE) */
/* Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
#define __NR_preadv                       0x14d                  /* ssize_t preadv(fd_t fd, struct iovecx32 const *iovec, size_t count, uint64_t offset) */
/* Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
#define __NR_pwritev                      0x14e                  /* ssize_t pwritev(fd_t fd, struct iovecx32 const *iovec, size_t count, uint64_t offset) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:            [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define __NR_rt_tgsigqueueinfo            0x14f                  /* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, signo_t usigno, struct __siginfox32_struct const *uinfo) */
#define __NR_perf_event_open              0x150                  /* errno_t perf_event_open(int TODO_PROTOTYPE) */
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
#define __NR_recvmmsg                     0x151                  /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdrx32 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespecx32 const *tmo) */
#define __NR_fanotify_init                0x152                  /* errno_t fanotify_init(int TODO_PROTOTYPE) */
#define __NR_fanotify_mark                0x153                  /* errno_t fanotify_mark(int TODO_PROTOTYPE) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR_prlimit64                    0x154                  /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define __NR_name_to_handle_at            0x155                  /* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
#define __NR_open_by_handle_at            0x156                  /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
#define __NR_clock_adjtime                0x157                  /* errno_t clock_adjtime(int TODO_PROTOTYPE) */
#define __NR_syncfs                       0x158                  /* errno_t syncfs(fd_t fd) */
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
#define __NR_sendmmsg                     0x159                  /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdrx32 *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
#define __NR_setns                        0x15a                  /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
#define __NR_process_vm_readv             0x15b                  /* ssize_t process_vm_readv(pid_t pid, struct iovecx32 const *local_iov, size_t liovcnt, struct iovecx32 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
#define __NR_process_vm_writev            0x15c                  /* ssize_t process_vm_writev(pid_t pid, struct iovecx32 const *local_iov, size_t liovcnt, struct iovecx32 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* @param: type: One of `KCMP_FILE', `KCMP_FILES', `KCMP_FS', `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
#define __NR_kcmp                         0x15d                  /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
#define __NR_finit_module                 0x15e                  /* errno_t finit_module(int TODO_PROTOTYPE) */
#define __NR_sched_setattr                0x15f                  /* errno_t sched_setattr(int TODO_PROTOTYPE) */
#define __NR_sched_getattr                0x160                  /* errno_t sched_getattr(int TODO_PROTOTYPE) */
/* @param: flags: Set of `RENAME_EXCHANGE | RENAME_NOREPLACE | RENAME_WHITEOUT' */
#define __NR_renameat2                    0x161                  /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
#define __NR_seccomp                      0x162                  /* errno_t seccomp(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
#define __NR_getrandom                    0x163                  /* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
/* @param: flags: Set of `MFD_CLOEXEC | MFD_ALLOW_SEALING' */
#define __NR_memfd_create                 0x164                  /* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
#define __NR_bpf                          0x165                  /* errno_t bpf(int TODO_PROTOTYPE) */
/* Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_execveat                     0x166                  /* errno_t execveat(fd_t dirfd, char const *pathname, __HYBRID_PTR32(char const) const *argv, __HYBRID_PTR32(char const) const *envp, atflag_t flags) */
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
#define __NR_socket                       0x167                  /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
/* Create a new socket for the given domain/type/protocol triple.
 * @param: domain:   Socket address domain/family (one of `AF_*' from `<sys/socket.h>')
 * @param: type:     Socket type (one of `SOCK_*' from `<sys/socket.h>')
 *                   May optionally be or'd with `SOCK_CLOEXEC | SOCK_CLOFORK | SOCK_NONBLOCK'
 * @param: protocol: Socket protocol (`0' for automatic). Available socket protocols mainly
 *                   depend on the selected `domain', and may be further specialized by the
 *                   `type' argument. for example, `AF_INET' takes one of `IPPROTO_*'
 *                   >> socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 *                   Also note that protocol IDs can be enumerated by `getprotoent(3)' from `<netdb.h>'
 * @return: * : A file descriptor for the newly created socket. */
#define __NR_socketpair                   0x168                  /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
#define __NR_bind                         0x169                  /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
/* Connect to the specified address.
 * If the given `sockfd' isn't connection-oriented, this will set the address
 * that will implicitly be used as destination by `send(2)' and `write(2)'
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_BUFFER_TOO_SMALL   (addr_len is incorrect)
 * @return: 0 : Success */
#define __NR_connect                      0x16a                  /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients pending to be accept(2)-ed, before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse any further requests until the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
#define __NR_listen                       0x16b                  /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
/* Accept incoming client (aka. peer) connection requests.
 * @param: addr:       Peer address of the sender (or `NULL' when `addr_len' is `NULL')
 * @param: addr_len:   [NULL] Don't fill in the client's peer address
 *                     [in]   The amount of available memory starting at `addr'
 *                     [out]  The amount of required memory for the address.
 *                            This may be more than was given, in which case
 *                            the address was truncated and may be invalid.
 *                            If this happens, the caller can still determine
 *                            the correct address through use of `getpeername()'
 * @param: sock_flags: Set of `SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SOCKET_NOT_LISTENING
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_ACCEPT
 * @throw: E_NET_CONNECTION_ABORT
 * @return: * : A file descriptor for the newly accept(2)-ed connection */
#define __NR_accept4                      0x16c                  /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
/* Get the value of the named socket option `level:optname' and store it in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  [in]  The amount of available memory starting at `optval'
 *                  [out] The amount of required memory for the option value.
 *                        This may be more than was given, in which case
 *                        the contents of `optval' are undefined.
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_GETSOCKOPT
 * @return: 0 : Success */
#define __NR_getsockopt                   0x16d                  /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
#define __NR_setsockopt                   0x16e                  /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
/* Determine the local address (aka. name) for the given socket `sockfd'.
 * This is usually the same address as was previously set by `bind(2)'
 * NOTE: Before the socket has actually be bound or connected, the exact
 *       address that is returned by this function is weakly undefined.
 *       e.g.: For AF_INET, sin_addr=0.0.0.0, sin_port=0 is returned.
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * return: 0 : Success */
#define __NR_getsockname                  0x16f                  /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the address was truncated and may be invalid.
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
#define __NR_getpeername                  0x170                  /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* Send the contents of a given buffer over this socket to the specified address
 * @param: buf:       Buffer of data to send (with a length of `bufsize' bytes)
 * @param: bufsize:   Size of `buf' (in bytes)
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @param: addr:      Address where to send data (or NULL when `addr_len' is 0)
 * @param: addr_len:  Size of `addr', or `0' to have this behave as an alias
 *                    for `send(sockfd, buf, bufsize, msg_flags)'
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SENDTO_WRONG_ADDRESS_FAMILY
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @throw: E_BUFFER_TOO_SMALL  (`addr_len' is incorrect)
 * @return: * : [<= bufsize] The actual # of send bytes */
#define __NR_sendto                       0x171                  /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
#define __NR_sendmsg                      0x172                  /* ssize_t sendmsg(fd_t sockfd, struct msghdrx32 const *message, syscall_ulong_t msg_flags) */
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
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @throw: E_WOULDBLOCK (`MSG_DONTWAIT' was given, and the operation would have blocked)
 * @return: * : [<= bufsize] The actual # of received bytes */
#define __NR_recvfrom                     0x173                  /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as well as for data buffers to be represented by an IOV vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
#define __NR_recvmsg                      0x174                  /* ssize_t recvmsg(fd_t sockfd, struct msghdrx32 *message, syscall_ulong_t msg_flags) */
/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as all currently queued data has been read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
#define __NR_shutdown                     0x175                  /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
#define __NR_userfaultfd                  0x176                  /* errno_t userfaultfd(int TODO_PROTOTYPE) */
#define __NR_membarrier                   0x177                  /* errno_t membarrier(int TODO_PROTOTYPE) */
#define __NR_mlock2                       0x178                  /* errno_t mlock2(int TODO_PROTOTYPE) */
#define __NR_copy_file_range              0x179                  /* errno_t copy_file_range(int TODO_PROTOTYPE) */
#define __NR_preadv2                      0x17a                  /* errno_t preadv2(int TODO_PROTOTYPE) */
#define __NR_pwritev2                     0x17b                  /* errno_t pwritev2(int TODO_PROTOTYPE) */
#define __NR_pkey_mprotect                0x17c                  /* errno_t pkey_mprotect(int TODO_PROTOTYPE) */
#define __NR_pkey_alloc                   0x17d                  /* errno_t pkey_alloc(int TODO_PROTOTYPE) */
#define __NR_pkey_free                    0x17e                  /* errno_t pkey_free(int TODO_PROTOTYPE) */
#define __NR_statx                        0x17f                  /* errno_t statx(int TODO_PROTOTYPE) */
#define __NR_arch_prctl                   0x180                  /* errno_t arch_prctl(int TODO_PROTOTYPE) */
#define __NR_io_pgetevents                0x181                  /* errno_t io_pgetevents(int TODO_PROTOTYPE) */
#define __NR_rseq                         0x182                  /* errno_t rseq(int TODO_PROTOTYPE) */
#define __NR_semget                       0x189                  /* errno_t semget(int TODO_PROTOTYPE) */
#define __NR_semctl                       0x18a                  /* errno_t semctl(int TODO_PROTOTYPE) */
#define __NR_shmget                       0x18b                  /* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
#define __NR_shmctl                       0x18c                  /* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
#define __NR_shmat                        0x18d                  /* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
#define __NR_shmdt                        0x18e                  /* errno_t shmdt(void const *shmaddr) */
#define __NR_msgget                       0x18f                  /* errno_t msgget(int TODO_PROTOTYPE) */
#define __NR_msgsnd                       0x190                  /* errno_t msgsnd(int TODO_PROTOTYPE) */
#define __NR_msgrcv                       0x191                  /* errno_t msgrcv(int TODO_PROTOTYPE) */
#define __NR_msgctl                       0x192                  /* errno_t msgctl(int TODO_PROTOTYPE) */
#define __NR_clock_gettime64              0x193                  /* errno_t clock_gettime64(clockid_t clock_id, struct timespecx32_64 *tp) */
#define __NR_clock_settime64              0x194                  /* errno_t clock_settime64(clockid_t clock_id, struct timespecx32_64 const *tp) */
#define __NR_clock_adjtime64              0x195                  /* errno_t clock_adjtime64(int TODO_PROTOTYPE) */
#define __NR_clock_getres_time64          0x196                  /* errno_t clock_getres_time64(clockid_t clock_id, struct timespecx32_64 *res) */
#define __NR_clock_nanosleep_time64       0x197                  /* errno_t clock_nanosleep_time64(clockid_t clock_id, syscall_ulong_t flags, struct timespecx32_64 const *requested_time, struct timespecx32_64 *remaining) */
#define __NR_timer_gettime64              0x198                  /* errno_t timer_gettime64(timer_t timerid, struct itimerspecx32_64 *value) */
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
#define __NR_timer_settime64              0x199                  /* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct itimerspecx32_64 const *value, struct itimerspecx32_64 *ovalue) */
/* Return the next expiration time of UFD */
#define __NR_timerfd_gettime64            0x19a                  /* errno_t timerfd_gettime64(fd_t timerfd, struct itimerspecx32_64 *otmr) */
/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags' has the `TFD_TIMER_ABSTIME' flag set the timeout value
 * is absolute. Optionally return the old expiration time in `otmr''
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
#define __NR_timerfd_settime64            0x19b                  /* errno_t timerfd_settime64(fd_t timerfd, syscall_ulong_t flags, struct itimerspecx32_64 const *utmr, struct itimerspecx32_64 *otmr) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
#define __NR_utimensat_time64             0x19c                  /* errno_t utimensat_time64(fd_t dirfd, char const *filename, struct timespecx32_64 const[2] times, atflag_t flags) */
#define __NR_pselect6_time64              0x19d                  /* ssize_t pselect6_time64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespecx32_64 const *timeout, void const *sigmask_sigset_and_len) */
#define __NR_ppoll_time64                 0x19e                  /* ssize_t ppoll_time64(struct pollfd *fds, size_t nfds, struct timespecx32_64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
#define __NR_io_pgetevents_time64         0x1a0                  /* errno_t io_pgetevents_time64(int TODO_PROTOTYPE) */
/* Same as `recvmsg(2)', but may be used to receive many
 * messages (datagrams) with a single system call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
#define __NR_recvmmsg_time64              0x1a1                  /* ssize_t recvmmsg_time64(fd_t sockfd, struct mmsghdrx32 *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespecx32_64 const *tmo) */
#define __NR_mq_timedsend_time64          0x1a2                  /* errno_t mq_timedsend_time64(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespecx32_64 const *abs_timeout) */
#define __NR_mq_timedreceive_time64       0x1a3                  /* ssize_t mq_timedreceive_time64(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespecx32_64 const *abs_timeout) */
#define __NR_semtimedop_time64            0x1a4                  /* errno_t semtimedop_time64(int TODO_PROTOTYPE) */
#define __NR_rt_sigtimedwait_time64       0x1a5                  /* syscall_slong_t rt_sigtimedwait_time64(struct __sigset_struct const *set, struct __siginfox32_struct *info, struct timespecx32_64 const *timeout, size_t sigsetsize) */
/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
#define __NR_futex_time64                 0x1a6                  /* syscall_slong_t futex_time64(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx32_64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define __NR_sched_rr_get_interval_time64 0x1a7                  /* errno_t sched_rr_get_interval_time64(pid_t pid, struct timespecx32_64 *tms) */
/* Send a signal to the process of a given pidfd
 * @param: pidfd:  A `HANDLE_TYPE_TASK'-handle
 * @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @param: flags:  Must always be `0' (for now)
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO:    [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO:               [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:     [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
#define __NR_pidfd_send_signal            0x1a8                  /* errno_t pidfd_send_signal(fd_t pidfd, signo_t usigno, struct __siginfox32_struct const *uinfo, syscall_ulong_t flags) */
#define __NR_io_uring_setup               0x1a9                  /* errno_t io_uring_setup(int TODO_PROTOTYPE) */
#define __NR_io_uring_enter               0x1aa                  /* errno_t io_uring_enter(int TODO_PROTOTYPE) */
#define __NR_io_uring_register            0x1ab                  /* errno_t io_uring_register(int TODO_PROTOTYPE) */
#define __NR_open_tree                    0x1ac                  /* errno_t open_tree(int TODO_PROTOTYPE) */
#define __NR_move_mount                   0x1ad                  /* errno_t move_mount(int TODO_PROTOTYPE) */
#define __NR_fsopen                       0x1ae                  /* errno_t fsopen(int TODO_PROTOTYPE) */
#define __NR_fsconfig                     0x1af                  /* errno_t fsconfig(int TODO_PROTOTYPE) */
#define __NR_fsmount                      0x1b0                  /* errno_t fsmount(int TODO_PROTOTYPE) */
#define __NR_fspick                       0x1b1                  /* errno_t fspick(int TODO_PROTOTYPE) */
/* Return a `HANDLE_TYPE_TASK' handle for the given `pid'
 * This system call exists for compatibility with linux, which does not allow
 * this call to succeed when `pid' isn't a process leader (i.e. main() thread)
 * @param: flags: Must always be `0' (for now)
 * @return: * :   A handle for the process `pid'
 * @throw: E_PROCESS_EXITED:                                                                 [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_STATE:E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER:    [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                           [...] */
#define __NR_pidfd_open                   0x1b2                  /* fd_t pidfd_open(pid_t pid, syscall_ulong_t flags) */
#define __NR_clone3                       0x1b3                  /* errno_t clone3(int TODO_PROTOTYPE) */
#define __NR_close_range                  0x1b4                  /* errno_t close_range(int TODO_PROTOTYPE) */
#define __NR_openat2                      0x1b5                  /* errno_t openat2(int TODO_PROTOTYPE) */
/* Duplicate the handle of a foreign process into a handle for the caller.
 * This system call duplicates the functionality of `open("/proc/[pid]/fd/[fdno]")',
 * which may also be used to duplicate file handles from another process.
 * @param: pidfd: A `HANDLE_TYPE_TASK'-handle
 * @param: fd:    The FD-number of the handle to clone
 * @param: flags: Must always be `0' (for now)
 * @return: * :   The duplicated handle number
 * @throw: E_PROCESS_EXITED:                                                                  [...]
 * @throw: E_INVALID_ARGUMENT_RESERVED_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS: [...]
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS:                                            [...]
 * @throw: E_INVALID_HANDLE_FILE:                                                             [...]
 * @throw: E_ILLEGAL_OPERATION:                                                               [...] */
#define __NR_pidfd_getfd                  0x1b6                  /* fd_t pidfd_getfd(fd_t pidfd, fd_t foreign_fd, syscall_ulong_t flags) */
#define __NR_faccessat2                   0x1b7                  /* errno_t faccessat2(int TODO_PROTOTYPE) */
/* Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
#define __NR_pwritevf                     __UINT32_C(0xfffffeb2) /* ssize_t pwritevf(fd_t fd, struct iovecx32 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
/* Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
#define __NR_preadvf                      __UINT32_C(0xfffffeb3) /* ssize_t preadvf(fd_t fd, struct iovecx32 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
#define __NR_fallocate64                  __UINT32_C(0xfffffebc) /* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR_freadlinkat                  __UINT32_C(0xfffffecf) /* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR_fsymlinkat                   __UINT32_C(0xfffffed0) /* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR_frenameat                    __UINT32_C(0xfffffed2) /* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_kfstatat                     __UINT32_C(0xfffffed4) /* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_statx32 *statbuf, atflag_t flags) */
#define __NR_futimesat64                  __UINT32_C(0xfffffed5) /* errno_t futimesat64(fd_t dirfd, char const *filename, struct timevalx32_64 const[2] times) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR_fmknodat                     __UINT32_C(0xfffffed7) /* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR_fmkdirat                     __UINT32_C(0xfffffed8) /* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED',
 *                  optionally or'd with `WNOHANG | WNOWAIT' */
#define __NR_waitid64                     __UINT32_C(0xfffffee4) /* errno_t waitid64(syscall_ulong_t idtype, id_t id, struct __siginfox32_struct *infop, syscall_ulong_t options, struct rusagex32_64 *ru) */
#define __NR_utimes64                     __UINT32_C(0xfffffef1) /* errno_t utimes64(char const *filename, struct timevalx32_64 const[2] times) */
/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally or'd with any of `READDIR_SKIPREL | READDIR_WANTEOF' */
#define __NR_kreaddirf                    __UINT32_C(0xffffff24) /* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
#define __NR_kfstat                       __UINT32_C(0xffffff3b) /* errno_t kfstat(fd_t fd, struct __kos_statx32 *statbuf) */
#define __NR_klstat                       __UINT32_C(0xffffff3c) /* errno_t klstat(char const *filename, struct __kos_statx32 *statbuf) */
#define __NR_kstat                        __UINT32_C(0xffffff3d) /* errno_t kstat(char const *filename, struct __kos_statx32 *statbuf) */
#define __NR_pwrite64f                    __UINT32_C(0xffffff4b) /* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR_pread64f                     __UINT32_C(0xffffff4c) /* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR_nanosleep64                  __UINT32_C(0xffffff5e) /* errno_t nanosleep64(struct timespecx32_64 const *req, struct timespecx32_64 *rem) */
#define __NR_rpc_service                  __UINT32_C(0xffffff62) /* syscall_slong_t rpc_service(void) */
#define __NR_ksysctl                      __UINT32_C(0xffffff6b) /* syscall_slong_t ksysctl(syscall_ulong_t command, void *arg) */
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write data from `count' seperate buffers, though still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
#define __NR_writevf                      __UINT32_C(0xffffff6e) /* ssize_t writevf(fd_t fd, struct iovecx32 const *iovec, size_t count, iomode_t mode) */
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read data into `count' seperate buffers, though still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
#define __NR_readvf                       __UINT32_C(0xffffff6f) /* ssize_t readvf(fd_t fd, struct iovecx32 const *iovec, size_t count, iomode_t mode) */
/* @param: mode: One of `READDIR_DEFAULT', `READDIR_CONTINUE', `READDIR_PEEK' or `READDIR_MULTIPLE',
 *               optionally or'd with any of `READDIR_SKIPREL | READDIR_WANTEOF' */
#define __NR_kreaddir                     __UINT32_C(0xffffff73) /* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR_wait4_64                     __UINT32_C(0xffffff8e) /* pid_t wait4_64(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusagex32_64 *usage) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR_getitimer64                  __UINT32_C(0xffffff97) /* errno_t getitimer64(syscall_ulong_t which, struct __itimervalx32_64 *curr_value) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR_setitimer64                  __UINT32_C(0xffffff98) /* errno_t setitimer64(syscall_ulong_t which, struct __itimervalx32_64 const *newval, struct __itimervalx32_64 *oldval) */
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
#define __NR_maplibrary                   __UINT32_C(0xffffffaa) /* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf32_phdr const *hdrv, size_t hdrc) */
#define __NR_select64                     __UINT32_C(0xffffffae) /* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timevalx32_64 *timeout) */
#define __NR_settimeofday64               __UINT32_C(0xffffffb1) /* errno_t settimeofday64(struct timevalx32_64 const *tv, struct timezone const *tz) */
#define __NR_gettimeofday64               __UINT32_C(0xffffffb2) /* errno_t gettimeofday64(struct timevalx32_64 *tv, struct timezone *tz) */
/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
#define __NR_getrusage64                  __UINT32_C(0xffffffb3) /* errno_t getrusage64(syscall_slong_t who, struct rusagex32_64 *tv) */
#define __NR_fsmode                       __UINT32_C(0xffffffc4) /* uint64_t fsmode(uint64_t mode) */
#define __NR_ioctlf                       __UINT32_C(0xffffffca) /* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
#define __NR_rtm_test                     __UINT32_C(0xffffffcd) /* syscall_ulong_t rtm_test(void) */
/* Abort the current transaction by having `sys_rtm_begin()' return with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op and return `-EOK'.
 * Otherwise, this system call does not return normally, but returns from
 * the original `sys_rtm_begin()' */
#define __NR_rtm_abort                    __UINT32_C(0xffffffce) /* errno_t rtm_abort(syscall_ulong_t code) */
/* End a transaction
 * If the transaction was successful, return normally (by returning `-EOK').
 * If the transaction failed, `sys_rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
#define __NR_rtm_end                      __UINT32_C(0xffffffcf) /* errno_t rtm_end(void) */
/* Begin an RTM operation. Note that if the arch-specific RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls will most likely result in an `RTM_ABORT_FAILED' error, and
 * attempting to access too much system memory in general will result in this
 * function returning with `RTM_ABORT_CAPACITY', rather than succeeding.
 * The following is a list of system calls which are whitelisted for use
 * during a transaction:
 *   - sys_rtm_begin:  Nested RTM operation
 *   - sys_rtm_end:    End an RTM operation
 *   - sys_rtm_abort:  Abort an RTM operation
 *   - sys_rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the RTM driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
#define __NR_rtm_begin                    __UINT32_C(0xffffffd0) /* rtm_status_t rtm_begin(void) */
#define __NR_ftime64                      __UINT32_C(0xffffffdd) /* errno_t ftime64(struct timebx32_64 *tp) */
#define __NR_utime64                      __UINT32_C(0xffffffe2) /* errno_t utime64(char const *filename, struct utimbufx32_64 const *times) */
/* Construct a user-vio-fd object supporting mmap(2), with actual
 * memory accesses being dispatched by adding them as pending requests
 * to an internal queue that should be read(2) from by a worker thread,
 * which should then service those requests before responding by write(2)ing
 * the results of the operation back to the same fd.
 * HINT: The format of the structures that are read(2) and
 *       write(2)en can be found in `<libvio/userviofd.h>'
 * NOTE: Don't use this system call directly. Use `vio_create(3)'
 *       from `<libvio/vio.h>' instead.
 * @param: initial_size: The initial mmap(2)able size of the returned handle.
 *                       This size may be altered at a later point in time
 *                       through use of `ftruncate(return)'
 * @param: flags:        Set of `0 | O_CLOEXEC | O_CLOFORK | O_NONBLOCK' */
#define __NR_userviofd                    __UINT32_C(0xffffffe5) /* fd_t userviofd(size_t initial_size, syscall_ulong_t flags) */
#define __NR_stime64                      __UINT32_C(0xffffffe7) /* errno_t stime64(time64_t const *t) */
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
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_SUCCESS' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
#define __NR_coredump                     __UINT32_C(0xffffffe8) /* errno_t coredump(struct ucpustate32 const *curr_state, struct ucpustate32 const *orig_state, __HYBRID_PTR32(void) const *traceback_vector, size_t traceback_length, struct __exception_data32 const *exception, syscall_ulong_t unwind_error) */
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it. */
#define __NR_raiseat                      __UINT32_C(0xffffffe9) /* errno_t raiseat(struct ucpustate32 const *state, struct __siginfox32_struct const *si) */
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
#define __NR_mktty                        __UINT32_C(0xffffffea) /* fd_t mktty(char const *name, fd_t keyboard, fd_t display, syscall_ulong_t rsvd) */
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
#define __NR_lfutexlockexpr               __UINT32_C(0xffffffeb) /* errno_t lfutexlockexpr(uint32_t *ulockaddr, void *base, size_t exprc, struct lfutexexprx32 const *exprv, struct timespecx32_64 const *timeout, syscall_ulong_t timeout_flags) */
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
#define __NR_lfutexexpr                   __UINT32_C(0xffffffec) /* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexprx32 const *exprv, struct timespecx32_64 const *timeout, syscall_ulong_t timeout_flags) */
#define __NR_lseek64                      __UINT32_C(0xffffffed) /* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
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
#define __NR_lfutex                       __UINT32_C(0xffffffee) /* syscall_slong_t lfutex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespecx32_64 const *timeout, uint32_t val2) */
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
#define __NR_debugtrap                    __UINT32_C(0xffffffef) /* errno_t debugtrap(struct ucpustate32 const *state, struct debugtrap_reason32 const *reason) */
/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    When non-NULL, store the address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: When non-NULL, store the starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
#define __NR_get_exception_handler        __UINT32_C(0xfffffff1) /* errno_t get_exception_handler(__ULONG32_TYPE__ *pmode, __except_handler32_t *phandler, __HYBRID_PTR32(void) *phandler_sp) */
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND, NULL, NULL)'
 *   Set mode #4 (as done by libc): `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND |
 *                                                         EXCEPT_HANDLER_FLAG_SETHANDLER,
 *                                                         &except_handler4, NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
#define __NR_set_exception_handler        __UINT32_C(0xfffffff2) /* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
#define __NR_time64                       __UINT32_C(0xfffffff3) /* int64_t time64(int64_t *timer) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR_fchdirat                     __UINT32_C(0xfffffff4) /* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
/* Create a new pseudo-terminal driver and store handles to both the
 * master and slave ends of the connection in the given pointers. */
#define __NR_openpty                      __UINT32_C(0xfffffff5) /* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
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
#define __NR_rpc_schedule                 __UINT32_C(0xfffffff7) /* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, __HYBRID_PTR32(void) *arguments) */
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR_frealpathat                  __UINT32_C(0xfffffff8) /* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR_frealpath4                   __UINT32_C(0xfffffff9) /* ssize_t frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags) */
/* Returns a bitset of all of the currently mounted dos-drives */
#define __NR_getdrives                    __UINT32_C(0xfffffffa) /* syscall_slong_t getdrives(void) */
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
 *                      or had you assigned as its parent.
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
 * NOTE: If a thread is created using clone() with `CLONE_DETACHED' set,
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
#define __NR_detach                       __UINT32_C(0xfffffffb) /* errno_t detach(pid_t pid) */
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
#define __NR_writef                       __UINT32_C(0xfffffffc) /* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
#define __NR_readf                        __UINT32_C(0xfffffffd) /* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
#define __NR_hopf                         __UINT32_C(0xfffffffe) /* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define __NR_hop                          __UINT32_C(0xffffffff) /* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */


/************************************************************************/
/* SYSCALL LIMITS                                                       */
/************************************************************************/
#define __NRFEAT_SYSCALL_TABLE_COUNT 2
#define __NRFEAT_SYSCALL_TABLE_FOREACH(callback) \
	callback(0)                                  \
	callback(1) 
#define __NR_syscall0_min 0x0
#define __NR_syscall0_max 0x1b7
#define __NR_syscall0_cnt 0x1b8
#define __NR_syscall1_min __UINT32_C(0xfffffeb2)
#define __NR_syscall1_max __UINT32_C(0xffffffff)
#define __NR_syscall1_cnt 0x14e
#endif /* !__NR_restart_syscall */


/************************************************************************/
/* SYSCALL RESTART MODES                                                */
/************************************************************************/
#ifdef __WANT_SYSCALL_RESTART_MODES
#ifndef __NRFEAT_DEFINED_SYSCALL_RESTART_MODES
#define __NRFEAT_DEFINED_SYSCALL_RESTART_MODES 1
/* Restart modes:
 * 0 (auto):
 *   - Always restart after an `E_INTERRUPT_USER_RPC'
 *   - Restart from sigreturn() if the signal handler had the `SA_RESTART' flag set
 * 1 (dont):
 *   - Never restart. - Always propagate `E_INTERRUPT_USER_RPC'
 *   - The only case when the system call should still be restarted,
 *     is when an RPC with `RPC_SCHEDULE_FLAG_SYSRESTART' was used
 * 2 (must):
 *   - Always restart, even from `sigreturn()' when the
 *     handler didn't have the `SA_RESTART' flag set
 *   - The only case when the system call shouldn't be restarted,
 *     is when an RPC with `RPC_SCHEDULE_FLAG_NOSYSRESTART' was used
 * Interaction with `SA_RESTART':
 *  - auto + ~SA_RESTART:      No
 *  - auto + SA_RESTART:       Yes
 *  - dont + ~SA_RESTART:      No
 *  - dont + SA_RESTART:       No
 *  - must + ~SA_RESTART:      Yes
 *  - must + SA_RESTART:       Yes
 * Interaction with RPC flags:
 *  - auto + <no flags>:                     Yes
 *  - auto + RPC_SCHEDULE_FLAG_SYSRESTART:   Yes
 *  - auto + RPC_SCHEDULE_FLAG_NOSYSRESTART: No
 *  - dont + <no flags>:                     No
 *  - dont + RPC_SCHEDULE_FLAG_SYSRESTART:   Yes
 *  - dont + RPC_SCHEDULE_FLAG_NOSYSRESTART: No
 *  - must + <no flags>:                     Yes
 *  - must + RPC_SCHEDULE_FLAG_SYSRESTART:   Yes
 *  - must + RPC_SCHEDULE_FLAG_NOSYSRESTART: No
 */
#define __NRRM_restart_syscall              0
#define __NRRM_exit                         2
#define __NRRM_fork                         2
#define __NRRM_read                         0
#define __NRRM_write                        0
#define __NRRM_open                         0
#define __NRRM_close                        2
#define __NRRM_waitpid                      1
#define __NRRM_creat                        0
#define __NRRM_link                         0
#define __NRRM_unlink                       0
#define __NRRM_execve                       0
#define __NRRM_chdir                        0
#define __NRRM_time                         0
#define __NRRM_mknod                        0
#define __NRRM_chmod                        0
#define __NRRM_lchown                       0
#define __NRRM_break                        0
#define __NRRM_oldstat                      0
#define __NRRM_lseek                        0
#define __NRRM_getpid                       2
#define __NRRM_mount                        0
#define __NRRM_umount                       0
#define __NRRM_setuid                       2
#define __NRRM_getuid                       2
#define __NRRM_stime                        0
#define __NRRM_ptrace                       0
#define __NRRM_alarm                        0
#define __NRRM_oldfstat                     0
#define __NRRM_pause                        1
#define __NRRM_utime                        0
#define __NRRM_stty                         0
#define __NRRM_gtty                         0
#define __NRRM_access                       0
#define __NRRM_nice                         0
#define __NRRM_ftime                        0
#define __NRRM_sync                         0
#define __NRRM_kill                         0
#define __NRRM_rename                       0
#define __NRRM_mkdir                        0
#define __NRRM_rmdir                        0
#define __NRRM_dup                          0
#define __NRRM_pipe                         0
#define __NRRM_times                        0
#define __NRRM_prof                         0
#define __NRRM_brk                          0
#define __NRRM_setgid                       2
#define __NRRM_getgid                       2
#define __NRRM_signal                       0
#define __NRRM_geteuid                      2
#define __NRRM_getegid                      2
#define __NRRM_acct                         0
#define __NRRM_umount2                      2
#define __NRRM_lock                         0
#define __NRRM_ioctl                        0
#define __NRRM_fcntl                        0
#define __NRRM_mpx                          0
#define __NRRM_setpgid                      2
#define __NRRM_ulimit                       0
#define __NRRM_oldolduname                  0
#define __NRRM_umask                        2
#define __NRRM_chroot                       0
#define __NRRM_ustat                        0
#define __NRRM_dup2                         0
#define __NRRM_getppid                      2
#define __NRRM_getpgrp                      2
#define __NRRM_setsid                       2
#define __NRRM_sigaction                    0
#define __NRRM_sgetmask                     0
#define __NRRM_ssetmask                     0
#define __NRRM_setreuid                     2
#define __NRRM_setregid                     2
#define __NRRM_sigsuspend                   1
#define __NRRM_sigpending                   0
#define __NRRM_sethostname                  0
#define __NRRM_setrlimit                    0
#define __NRRM_getrlimit                    0
#define __NRRM_getrusage                    0
#define __NRRM_gettimeofday                 0
#define __NRRM_settimeofday                 0
#define __NRRM_getgroups                    2
#define __NRRM_setgroups                    2
#define __NRRM_select                       1
#define __NRRM_symlink                      0
#define __NRRM_oldlstat                     0
#define __NRRM_readlink                     0
#define __NRRM_uselib                       0
#define __NRRM_swapon                       0
#define __NRRM_reboot                       0
#define __NRRM_readdir                      0
#define __NRRM_mmap                         0
#define __NRRM_munmap                       2
#define __NRRM_truncate                     0
#define __NRRM_ftruncate                    0
#define __NRRM_fchmod                       0
#define __NRRM_fchown                       0
#define __NRRM_getpriority                  0
#define __NRRM_setpriority                  0
#define __NRRM_profil                       0
#define __NRRM_statfs                       0
#define __NRRM_fstatfs                      0
#define __NRRM_ioperm                       0
#define __NRRM_socketcall                   0
#define __NRRM_syslog                       2
#define __NRRM_setitimer                    0
#define __NRRM_getitimer                    0
#define __NRRM_stat                         0
#define __NRRM_lstat                        0
#define __NRRM_fstat                        0
#define __NRRM_olduname                     0
#define __NRRM_iopl                         0
#define __NRRM_vhangup                      0
#define __NRRM_idle                         0
#define __NRRM_vm86old                      0
#define __NRRM_wait4                        1
#define __NRRM_swapoff                      0
#define __NRRM_sysinfo                      0
#define __NRRM_ipc                          0
#define __NRRM_fsync                        0
#define __NRRM_sigreturn                    2
#define __NRRM_clone                        0
#define __NRRM_setdomainname                0
#define __NRRM_uname                        0
#define __NRRM_modify_ldt                   0
#define __NRRM_adjtimex                     0
#define __NRRM_mprotect                     2
#define __NRRM_sigprocmask                  0
#define __NRRM_create_module                0
#define __NRRM_init_module                  0
#define __NRRM_delete_module                0
#define __NRRM_get_kernel_syms              0
#define __NRRM_quotactl                     0
#define __NRRM_getpgid                      2
#define __NRRM_fchdir                       0
#define __NRRM_bdflush                      0
#define __NRRM_sysfs                        0
#define __NRRM_personality                  0
#define __NRRM_afs_syscall                  0
#define __NRRM_setfsuid                     2
#define __NRRM_setfsgid                     2
#define __NRRM__llseek                      0
#define __NRRM_getdents                     0
#define __NRRM__newselect                   1
#define __NRRM_flock                        0
#define __NRRM_msync                        0
#define __NRRM_readv                        0
#define __NRRM_writev                       0
#define __NRRM_getsid                       2
#define __NRRM_fdatasync                    0
#define __NRRM__sysctl                      0
#define __NRRM_mlock                        0
#define __NRRM_munlock                      0
#define __NRRM_mlockall                     0
#define __NRRM_munlockall                   0
#define __NRRM_sched_setparam               0
#define __NRRM_sched_getparam               0
#define __NRRM_sched_setscheduler           0
#define __NRRM_sched_getscheduler           0
#define __NRRM_sched_yield                  1
#define __NRRM_sched_get_priority_max       0
#define __NRRM_sched_get_priority_min       0
#define __NRRM_sched_rr_get_interval        0
#define __NRRM_nanosleep                    1
#define __NRRM_mremap                       0
#define __NRRM_setresuid                    2
#define __NRRM_getresuid                    2
#define __NRRM_vm86                         0
#define __NRRM_query_module                 0
#define __NRRM_poll                         1
#define __NRRM_nfsservctl                   0
#define __NRRM_setresgid                    2
#define __NRRM_getresgid                    2
#define __NRRM_prctl                        0
#define __NRRM_rt_sigreturn                 2
#define __NRRM_rt_sigaction                 0
#define __NRRM_rt_sigprocmask               0
#define __NRRM_rt_sigpending                0
#define __NRRM_rt_sigtimedwait              1
#define __NRRM_rt_sigqueueinfo              0
#define __NRRM_rt_sigsuspend                1
#define __NRRM_pread64                      0
#define __NRRM_pwrite64                     0
#define __NRRM_chown                        0
#define __NRRM_getcwd                       0
#define __NRRM_capget                       0
#define __NRRM_capset                       0
#define __NRRM_sigaltstack                  0
#define __NRRM_sendfile                     1
#define __NRRM_getpmsg                      0
#define __NRRM_putpmsg                      0
#define __NRRM_vfork                        2
#define __NRRM_ugetrlimit                   0
#define __NRRM_mmap2                        0
#define __NRRM_truncate64                   0
#define __NRRM_ftruncate64                  0
#define __NRRM_stat64                       0
#define __NRRM_lstat64                      0
#define __NRRM_fstat64                      0
#define __NRRM_lchown32                     0
#define __NRRM_getuid32                     2
#define __NRRM_getgid32                     2
#define __NRRM_geteuid32                    2
#define __NRRM_getegid32                    2
#define __NRRM_setreuid32                   2
#define __NRRM_setregid32                   2
#define __NRRM_getgroups32                  2
#define __NRRM_setgroups32                  2
#define __NRRM_fchown32                     0
#define __NRRM_setresuid32                  2
#define __NRRM_getresuid32                  2
#define __NRRM_setresgid32                  2
#define __NRRM_getresgid32                  2
#define __NRRM_chown32                      0
#define __NRRM_setuid32                     2
#define __NRRM_setgid32                     2
#define __NRRM_setfsuid32                   2
#define __NRRM_setfsgid32                   2
#define __NRRM_pivot_root                   0
#define __NRRM_mincore                      0
#define __NRRM_madvise                      0
#define __NRRM_getdents64                   0
#define __NRRM_fcntl64                      0
#define __NRRM_gettid                       2
#define __NRRM_readahead                    0
#define __NRRM_setxattr                     0
#define __NRRM_lsetxattr                    0
#define __NRRM_fsetxattr                    0
#define __NRRM_getxattr                     0
#define __NRRM_lgetxattr                    0
#define __NRRM_fgetxattr                    0
#define __NRRM_listxattr                    0
#define __NRRM_llistxattr                   0
#define __NRRM_flistxattr                   0
#define __NRRM_removexattr                  0
#define __NRRM_lremovexattr                 0
#define __NRRM_fremovexattr                 0
#define __NRRM_tkill                        0
#define __NRRM_sendfile64                   1
#define __NRRM_futex                        0
#define __NRRM_sched_setaffinity            0
#define __NRRM_sched_getaffinity            0
#define __NRRM_set_thread_area              0
#define __NRRM_get_thread_area              0
#define __NRRM_io_setup                     0
#define __NRRM_io_destroy                   0
#define __NRRM_io_getevents                 1
#define __NRRM_io_submit                    0
#define __NRRM_io_cancel                    0
#define __NRRM_fadvise64                    0
#define __NRRM_exit_group                   2
#define __NRRM_lookup_dcookie               0
#define __NRRM_epoll_create                 0
#define __NRRM_epoll_ctl                    0
#define __NRRM_epoll_wait                   1
#define __NRRM_remap_file_pages             0
#define __NRRM_set_tid_address              2
#define __NRRM_timer_create                 0
#define __NRRM_timer_settime                0
#define __NRRM_timer_gettime                0
#define __NRRM_timer_getoverrun             0
#define __NRRM_timer_delete                 0
#define __NRRM_clock_settime                0
#define __NRRM_clock_gettime                0
#define __NRRM_clock_getres                 0
#define __NRRM_clock_nanosleep              1
#define __NRRM_statfs64                     0
#define __NRRM_fstatfs64                    0
#define __NRRM_tgkill                       0
#define __NRRM_utimes                       0
#define __NRRM_fadvise64_64                 0
#define __NRRM_vserver                      0
#define __NRRM_mbind                        0
#define __NRRM_get_mempolicy                0
#define __NRRM_set_mempolicy                0
#define __NRRM_mq_open                      0
#define __NRRM_mq_unlink                    0
#define __NRRM_mq_timedsend                 0
#define __NRRM_mq_timedreceive              0
#define __NRRM_mq_notify                    0
#define __NRRM_mq_getsetattr                0
#define __NRRM_kexec_load                   0
#define __NRRM_waitid                       1
#define __NRRM_add_key                      0
#define __NRRM_request_key                  0
#define __NRRM_keyctl                       0
#define __NRRM_ioprio_set                   0
#define __NRRM_ioprio_get                   0
#define __NRRM_inotify_init                 0
#define __NRRM_inotify_add_watch            0
#define __NRRM_inotify_rm_watch             0
#define __NRRM_migrate_pages                0
#define __NRRM_openat                       0
#define __NRRM_mkdirat                      0
#define __NRRM_mknodat                      0
#define __NRRM_fchownat                     0
#define __NRRM_futimesat                    0
#define __NRRM_fstatat64                    0
#define __NRRM_unlinkat                     0
#define __NRRM_renameat                     0
#define __NRRM_linkat                       0
#define __NRRM_symlinkat                    0
#define __NRRM_readlinkat                   0
#define __NRRM_fchmodat                     0
#define __NRRM_faccessat                    0
#define __NRRM_pselect6                     1
#define __NRRM_ppoll                        1
#define __NRRM_unshare                      0
#define __NRRM_set_robust_list              0
#define __NRRM_get_robust_list              0
#define __NRRM_splice                       0
#define __NRRM_sync_file_range              0
#define __NRRM_tee                          0
#define __NRRM_vmsplice                     0
#define __NRRM_move_pages                   0
#define __NRRM_getcpu                       0
#define __NRRM_epoll_pwait                  1
#define __NRRM_utimensat                    0
#define __NRRM_signalfd                     0
#define __NRRM_timerfd_create               0
#define __NRRM_eventfd                      0
#define __NRRM_fallocate                    0
#define __NRRM_timerfd_settime              0
#define __NRRM_timerfd_gettime              0
#define __NRRM_signalfd4                    0
#define __NRRM_eventfd2                     0
#define __NRRM_epoll_create1                0
#define __NRRM_dup3                         0
#define __NRRM_pipe2                        0
#define __NRRM_inotify_init1                0
#define __NRRM_preadv                       0
#define __NRRM_pwritev                      0
#define __NRRM_rt_tgsigqueueinfo            0
#define __NRRM_perf_event_open              0
#define __NRRM_recvmmsg                     1
#define __NRRM_fanotify_init                0
#define __NRRM_fanotify_mark                0
#define __NRRM_prlimit64                    0
#define __NRRM_name_to_handle_at            0
#define __NRRM_open_by_handle_at            0
#define __NRRM_clock_adjtime                0
#define __NRRM_syncfs                       0
#define __NRRM_sendmmsg                     1
#define __NRRM_setns                        0
#define __NRRM_process_vm_readv             0
#define __NRRM_process_vm_writev            0
#define __NRRM_kcmp                         0
#define __NRRM_finit_module                 0
#define __NRRM_sched_setattr                0
#define __NRRM_sched_getattr                0
#define __NRRM_renameat2                    0
#define __NRRM_seccomp                      0
#define __NRRM_getrandom                    0
#define __NRRM_memfd_create                 0
#define __NRRM_bpf                          0
#define __NRRM_execveat                     0
#define __NRRM_socket                       0
#define __NRRM_socketpair                   0
#define __NRRM_bind                         0
#define __NRRM_connect                      1
#define __NRRM_listen                       0
#define __NRRM_accept4                      1
#define __NRRM_getsockopt                   0
#define __NRRM_setsockopt                   1
#define __NRRM_getsockname                  0
#define __NRRM_getpeername                  0
#define __NRRM_sendto                       1
#define __NRRM_sendmsg                      1
#define __NRRM_recvfrom                     1
#define __NRRM_recvmsg                      1
#define __NRRM_shutdown                     0
#define __NRRM_userfaultfd                  0
#define __NRRM_membarrier                   0
#define __NRRM_mlock2                       0
#define __NRRM_copy_file_range              0
#define __NRRM_preadv2                      0
#define __NRRM_pwritev2                     0
#define __NRRM_pkey_mprotect                0
#define __NRRM_pkey_alloc                   0
#define __NRRM_pkey_free                    0
#define __NRRM_statx                        0
#define __NRRM_arch_prctl                   0
#define __NRRM_io_pgetevents                1
#define __NRRM_rseq                         0
#define __NRRM_semget                       0
#define __NRRM_semctl                       0
#define __NRRM_shmget                       0
#define __NRRM_shmctl                       0
#define __NRRM_shmat                        0
#define __NRRM_shmdt                        0
#define __NRRM_msgget                       0
#define __NRRM_msgsnd                       1
#define __NRRM_msgrcv                       1
#define __NRRM_msgctl                       0
#define __NRRM_clock_gettime64              0
#define __NRRM_clock_settime64              0
#define __NRRM_clock_adjtime64              0
#define __NRRM_clock_getres_time64          0
#define __NRRM_clock_nanosleep_time64       1
#define __NRRM_timer_gettime64              0
#define __NRRM_timer_settime64              0
#define __NRRM_timerfd_gettime64            0
#define __NRRM_timerfd_settime64            0
#define __NRRM_utimensat_time64             0
#define __NRRM_pselect6_time64              1
#define __NRRM_ppoll_time64                 1
#define __NRRM_io_pgetevents_time64         1
#define __NRRM_recvmmsg_time64              1
#define __NRRM_mq_timedsend_time64          0
#define __NRRM_mq_timedreceive_time64       0
#define __NRRM_semtimedop_time64            1
#define __NRRM_rt_sigtimedwait_time64       1
#define __NRRM_futex_time64                 0
#define __NRRM_sched_rr_get_interval_time64 0
#define __NRRM_pidfd_send_signal            0
#define __NRRM_io_uring_setup               0
#define __NRRM_io_uring_enter               0
#define __NRRM_io_uring_register            0
#define __NRRM_open_tree                    0
#define __NRRM_move_mount                   0
#define __NRRM_fsopen                       0
#define __NRRM_fsconfig                     0
#define __NRRM_fsmount                      0
#define __NRRM_fspick                       0
#define __NRRM_pidfd_open                   0
#define __NRRM_clone3                       0
#define __NRRM_close_range                  0
#define __NRRM_openat2                      0
#define __NRRM_pidfd_getfd                  0
#define __NRRM_faccessat2                   0
#define __NRRM_pwritevf                     0
#define __NRRM_preadvf                      0
#define __NRRM_fallocate64                  0
#define __NRRM_freadlinkat                  0
#define __NRRM_fsymlinkat                   0
#define __NRRM_frenameat                    0
#define __NRRM_kfstatat                     0
#define __NRRM_futimesat64                  0
#define __NRRM_fmknodat                     0
#define __NRRM_fmkdirat                     0
#define __NRRM_waitid64                     1
#define __NRRM_utimes64                     0
#define __NRRM_kreaddirf                    0
#define __NRRM_kfstat                       0
#define __NRRM_klstat                       0
#define __NRRM_kstat                        0
#define __NRRM_pwrite64f                    0
#define __NRRM_pread64f                     0
#define __NRRM_nanosleep64                  1
#define __NRRM_rpc_service                  1
#define __NRRM_ksysctl                      0
#define __NRRM_writevf                      0
#define __NRRM_readvf                       0
#define __NRRM_kreaddir                     0
#define __NRRM_wait4_64                     1
#define __NRRM_getitimer64                  0
#define __NRRM_setitimer64                  0
#define __NRRM_maplibrary                   0
#define __NRRM_select64                     1
#define __NRRM_settimeofday64               0
#define __NRRM_gettimeofday64               0
#define __NRRM_getrusage64                  0
#define __NRRM_fsmode                       2
#define __NRRM_ioctlf                       0
#define __NRRM_rtm_test                     0
#define __NRRM_rtm_abort                    0
#define __NRRM_rtm_end                      0
#define __NRRM_rtm_begin                    0
#define __NRRM_ftime64                      0
#define __NRRM_utime64                      0
#define __NRRM_userviofd                    0
#define __NRRM_stime64                      0
#define __NRRM_coredump                     2
#define __NRRM_raiseat                      2
#define __NRRM_mktty                        0
#define __NRRM_lfutexlockexpr               1
#define __NRRM_lfutexexpr                   1
#define __NRRM_lseek64                      0
#define __NRRM_lfutex                       1
#define __NRRM_debugtrap                    0
#define __NRRM_get_exception_handler        2
#define __NRRM_set_exception_handler        2
#define __NRRM_time64                       0
#define __NRRM_fchdirat                     0
#define __NRRM_openpty                      0
#define __NRRM_rpc_schedule                 0
#define __NRRM_frealpathat                  0
#define __NRRM_frealpath4                   0
#define __NRRM_getdrives                    2
#define __NRRM_detach                       2
#define __NRRM_writef                       0
#define __NRRM_readf                        0
#define __NRRM_hopf                         0
#define __NRRM_hop                          0
#endif /* !__NRFEAT_DEFINED_SYSCALL_RESTART_MODES */
#endif /* __WANT_SYSCALL_RESTART_MODES */


/************************************************************************/
/* SYSCALL CANCELLATION POINTS                                          */
/************************************************************************/
#ifdef __WANT_SYSCALL_CANCELLATION_POINTS
#ifndef __NRFEAT_DEFINED_SYSCALL_CANCELLATION_POINTS
#define __NRFEAT_DEFINED_SYSCALL_CANCELLATION_POINTS 1
#define __NRFEAT_HAVE_CANCELLATION_POINTS 1
#define __NRCP_read                         1
#define __NRCP_write                        1
#define __NRCP_open                         1
#define __NRCP_waitpid                      1
#define __NRCP_creat                        1
#define __NRCP_link                         1
#define __NRCP_unlink                       1
#define __NRCP_execve                       1
#define __NRCP_chdir                        1
#define __NRCP_mknod                        1
#define __NRCP_chmod                        1
#define __NRCP_lchown                       1
#define __NRCP_oldstat                      1
#define __NRCP_lseek                        1
#define __NRCP_mount                        1
#define __NRCP_umount                       1
#define __NRCP_oldfstat                     1
#define __NRCP_pause                        1
#define __NRCP_utime                        1
#define __NRCP_access                       1
#define __NRCP_sync                         1
#define __NRCP_rename                       1
#define __NRCP_mkdir                        1
#define __NRCP_umount2                      1
#define __NRCP_ioctl                        1
#define __NRCP_fcntl                        1
#define __NRCP_sigsuspend                   1
#define __NRCP_select                       1
#define __NRCP_symlink                      1
#define __NRCP_oldlstat                     1
#define __NRCP_readlink                     1
#define __NRCP_readdir                      1
#define __NRCP_fchmod                       1
#define __NRCP_fchown                       1
#define __NRCP_syslog                       1
#define __NRCP_stat                         1
#define __NRCP_lstat                        1
#define __NRCP_fstat                        1
#define __NRCP_wait4                        1
#define __NRCP_sysinfo                      1
#define __NRCP_fsync                        1
#define __NRCP_fchdir                       1
#define __NRCP__llseek                      1
#define __NRCP_getdents                     1
#define __NRCP__newselect                   1
#define __NRCP_flock                        1
#define __NRCP_msync                        1
#define __NRCP_readv                        1
#define __NRCP_writev                       1
#define __NRCP_fdatasync                    1
#define __NRCP_nanosleep                    1
#define __NRCP_poll                         1
#define __NRCP_rt_sigtimedwait              1
#define __NRCP_rt_sigsuspend                1
#define __NRCP_pread64                      1
#define __NRCP_pwrite64                     1
#define __NRCP_chown                        1
#define __NRCP_getcwd                       1
#define __NRCP_sendfile                     1
#define __NRCP_getpmsg                      1
#define __NRCP_putpmsg                      1
#define __NRCP_stat64                       1
#define __NRCP_lstat64                      1
#define __NRCP_fstat64                      1
#define __NRCP_lchown32                     1
#define __NRCP_fchown32                     1
#define __NRCP_chown32                      1
#define __NRCP_getdents64                   1
#define __NRCP_fcntl64                      1
#define __NRCP_setxattr                     1
#define __NRCP_lsetxattr                    1
#define __NRCP_fsetxattr                    1
#define __NRCP_getxattr                     1
#define __NRCP_lgetxattr                    1
#define __NRCP_fgetxattr                    1
#define __NRCP_listxattr                    1
#define __NRCP_llistxattr                   1
#define __NRCP_flistxattr                   1
#define __NRCP_removexattr                  1
#define __NRCP_lremovexattr                 1
#define __NRCP_fremovexattr                 1
#define __NRCP_sendfile64                   1
#define __NRCP_futex                        1
#define __NRCP_epoll_wait                   1
#define __NRCP_clock_nanosleep              1
#define __NRCP_utimes                       1
#define __NRCP_mq_timedsend                 1
#define __NRCP_mq_timedreceive              1
#define __NRCP_waitid                       1
#define __NRCP_openat                       1
#define __NRCP_mkdirat                      1
#define __NRCP_mknodat                      1
#define __NRCP_fchownat                     1
#define __NRCP_futimesat                    1
#define __NRCP_fstatat64                    1
#define __NRCP_unlinkat                     1
#define __NRCP_renameat                     1
#define __NRCP_linkat                       1
#define __NRCP_symlinkat                    1
#define __NRCP_readlinkat                   1
#define __NRCP_fchmodat                     1
#define __NRCP_faccessat                    1
#define __NRCP_pselect6                     1
#define __NRCP_ppoll                        1
#define __NRCP_splice                       1
#define __NRCP_sync_file_range              1
#define __NRCP_tee                          1
#define __NRCP_vmsplice                     1
#define __NRCP_epoll_pwait                  1
#define __NRCP_utimensat                    1
#define __NRCP_preadv                       1
#define __NRCP_pwritev                      1
#define __NRCP_recvmmsg                     1
#define __NRCP_name_to_handle_at            1
#define __NRCP_open_by_handle_at            1
#define __NRCP_syncfs                       1
#define __NRCP_sendmmsg                     1
#define __NRCP_renameat2                    1
#define __NRCP_execveat                     1
#define __NRCP_connect                      1
#define __NRCP_accept4                      1
#define __NRCP_sendto                       1
#define __NRCP_sendmsg                      1
#define __NRCP_recvfrom                     1
#define __NRCP_recvmsg                      1
#define __NRCP_msgsnd                       1
#define __NRCP_msgrcv                       1
#define __NRCP_clock_nanosleep_time64       1
#define __NRCP_utimensat_time64             1
#define __NRCP_pselect6_time64              1
#define __NRCP_ppoll_time64                 1
#define __NRCP_recvmmsg_time64              1
#define __NRCP_mq_timedsend_time64          1
#define __NRCP_mq_timedreceive_time64       1
#define __NRCP_rt_sigtimedwait_time64       1
#define __NRCP_futex_time64                 1
#define __NRCP_pwritevf                     1
#define __NRCP_preadvf                      1
#define __NRCP_freadlinkat                  1
#define __NRCP_fsymlinkat                   1
#define __NRCP_frenameat                    1
#define __NRCP_kfstatat                     1
#define __NRCP_futimesat64                  1
#define __NRCP_fmknodat                     1
#define __NRCP_fmkdirat                     1
#define __NRCP_waitid64                     1
#define __NRCP_utimes64                     1
#define __NRCP_kreaddirf                    1
#define __NRCP_kfstat                       1
#define __NRCP_klstat                       1
#define __NRCP_kstat                        1
#define __NRCP_pwrite64f                    1
#define __NRCP_pread64f                     1
#define __NRCP_nanosleep64                  1
#define __NRCP_rpc_service                  1
#define __NRCP_ksysctl                      1
#define __NRCP_writevf                      1
#define __NRCP_readvf                       1
#define __NRCP_kreaddir                     1
#define __NRCP_wait4_64                     1
#define __NRCP_select64                     1
#define __NRCP_ioctlf                       1
#define __NRCP_utime64                      1
#define __NRCP_lfutexlockexpr               1
#define __NRCP_lfutexexpr                   1
#define __NRCP_lseek64                      1
#define __NRCP_lfutex                       1
#define __NRCP_fchdirat                     1
#define __NRCP_frealpathat                  1
#define __NRCP_frealpath4                   1
#define __NRCP_writef                       1
#define __NRCP_readf                        1
#define __NRCP_hopf                         1
#define __NRCP_hop                          1
#endif /* !__NRFEAT_DEFINED_SYSCALL_CANCELLATION_POINTS */
#endif /* __WANT_SYSCALL_CANCELLATION_POINTS */


/************************************************************************/
/* SYSCALL REGISTER COUNT                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_REGISTER_COUNT
#ifndef __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT 1
#define __NRFEAT_SYSCALL_REGISTER_MAX_COUNT 6
#define __NRFEAT_SYSCALL_REGISTER_BITS 32
#define __NRRC_restart_syscall              0
#define __NRRC_exit                         1
#define __NRRC_fork                         0
#define __NRRC_read                         3
#define __NRRC_write                        3
#define __NRRC_open                         3
#define __NRRC_close                        1
#define __NRRC_waitpid                      3
#define __NRRC_creat                        2
#define __NRRC_link                         2
#define __NRRC_unlink                       1
#define __NRRC_execve                       3
#define __NRRC_chdir                        1
#define __NRRC_time                         1
#define __NRRC_mknod                        3
#define __NRRC_chmod                        2
#define __NRRC_lchown                       3
#define __NRRC_break                        0
#define __NRRC_oldstat                      2
#define __NRRC_lseek                        3
#define __NRRC_getpid                       0
#define __NRRC_mount                        5
#define __NRRC_umount                       1
#define __NRRC_setuid                       1
#define __NRRC_getuid                       0
#define __NRRC_stime                        1
#define __NRRC_ptrace                       4
#define __NRRC_alarm                        1
#define __NRRC_oldfstat                     2
#define __NRRC_pause                        0
#define __NRRC_utime                        2
#define __NRRC_stty                         0
#define __NRRC_gtty                         0
#define __NRRC_access                       2
#define __NRRC_nice                         1
#define __NRRC_ftime                        1
#define __NRRC_sync                         0
#define __NRRC_kill                         2
#define __NRRC_rename                       2
#define __NRRC_mkdir                        2
#define __NRRC_rmdir                        1
#define __NRRC_dup                          1
#define __NRRC_pipe                         1
#define __NRRC_times                        1
#define __NRRC_prof                         0
#define __NRRC_brk                          1
#define __NRRC_setgid                       1
#define __NRRC_getgid                       0
#define __NRRC_signal                       2
#define __NRRC_geteuid                      0
#define __NRRC_getegid                      0
#define __NRRC_acct                         1
#define __NRRC_umount2                      2
#define __NRRC_lock                         0
#define __NRRC_ioctl                        3
#define __NRRC_fcntl                        3
#define __NRRC_mpx                          0
#define __NRRC_setpgid                      2
#define __NRRC_ulimit                       0
#define __NRRC_oldolduname                  1
#define __NRRC_umask                        1
#define __NRRC_chroot                       1
#define __NRRC_ustat                        2
#define __NRRC_dup2                         2
#define __NRRC_getppid                      0
#define __NRRC_getpgrp                      0
#define __NRRC_setsid                       0
#define __NRRC_sigaction                    3
#define __NRRC_sgetmask                     0
#define __NRRC_ssetmask                     1
#define __NRRC_setreuid                     2
#define __NRRC_setregid                     2
#define __NRRC_sigsuspend                   1
#define __NRRC_sigpending                   1
#define __NRRC_sethostname                  2
#define __NRRC_setrlimit                    2
#define __NRRC_getrlimit                    2
#define __NRRC_getrusage                    2
#define __NRRC_gettimeofday                 2
#define __NRRC_settimeofday                 2
#define __NRRC_getgroups                    2
#define __NRRC_setgroups                    2
#define __NRRC_select                       1
#define __NRRC_symlink                      2
#define __NRRC_oldlstat                     2
#define __NRRC_readlink                     3
#define __NRRC_uselib                       1
#define __NRRC_swapon                       2
#define __NRRC_reboot                       1
#define __NRRC_readdir                      2
#define __NRRC_mmap                         6
#define __NRRC_munmap                       2
#define __NRRC_truncate                     2
#define __NRRC_ftruncate                    2
#define __NRRC_fchmod                       2
#define __NRRC_fchown                       3
#define __NRRC_getpriority                  2
#define __NRRC_setpriority                  3
#define __NRRC_profil                       4
#define __NRRC_statfs                       2
#define __NRRC_fstatfs                      2
#define __NRRC_ioperm                       3
#define __NRRC_socketcall                   2
#define __NRRC_syslog                       3
#define __NRRC_setitimer                    3
#define __NRRC_getitimer                    2
#define __NRRC_stat                         2
#define __NRRC_lstat                        2
#define __NRRC_fstat                        2
#define __NRRC_olduname                     1
#define __NRRC_iopl                         1
#define __NRRC_vhangup                      0
#define __NRRC_idle                         0
#define __NRRC_vm86old                      1
#define __NRRC_wait4                        4
#define __NRRC_swapoff                      1
#define __NRRC_sysinfo                      1
#define __NRRC_ipc                          1
#define __NRRC_fsync                        1
#define __NRRC_sigreturn                    6
#define __NRRC_clone                        5
#define __NRRC_setdomainname                2
#define __NRRC_uname                        1
#define __NRRC_modify_ldt                   3
#define __NRRC_adjtimex                     1
#define __NRRC_mprotect                     3
#define __NRRC_sigprocmask                  3
#define __NRRC_create_module                1
#define __NRRC_init_module                  1
#define __NRRC_delete_module                1
#define __NRRC_get_kernel_syms              1
#define __NRRC_quotactl                     1
#define __NRRC_getpgid                      1
#define __NRRC_fchdir                       1
#define __NRRC_bdflush                      1
#define __NRRC_sysfs                        1
#define __NRRC_personality                  1
#define __NRRC_afs_syscall                  1
#define __NRRC_setfsuid                     1
#define __NRRC_setfsgid                     1
#define __NRRC__llseek                      5 /* __NRAC__llseek + 1 */
#define __NRRC_getdents                     3
#define __NRRC__newselect                   5
#define __NRRC_flock                        2
#define __NRRC_msync                        3
#define __NRRC_readv                        3
#define __NRRC_writev                       3
#define __NRRC_getsid                       1
#define __NRRC_fdatasync                    1
#define __NRRC__sysctl                      1
#define __NRRC_mlock                        2
#define __NRRC_munlock                      2
#define __NRRC_mlockall                     1
#define __NRRC_munlockall                   0
#define __NRRC_sched_setparam               2
#define __NRRC_sched_getparam               2
#define __NRRC_sched_setscheduler           3
#define __NRRC_sched_getscheduler           1
#define __NRRC_sched_yield                  0
#define __NRRC_sched_get_priority_max       1
#define __NRRC_sched_get_priority_min       1
#define __NRRC_sched_rr_get_interval        2
#define __NRRC_nanosleep                    2
#define __NRRC_mremap                       5
#define __NRRC_setresuid                    3
#define __NRRC_getresuid                    3
#define __NRRC_vm86                         1
#define __NRRC_query_module                 1
#define __NRRC_poll                         3
#define __NRRC_nfsservctl                   1
#define __NRRC_setresgid                    3
#define __NRRC_getresgid                    3
#define __NRRC_prctl                        1
#define __NRRC_rt_sigreturn                 6
#define __NRRC_rt_sigaction                 4
#define __NRRC_rt_sigprocmask               4
#define __NRRC_rt_sigpending                2
#define __NRRC_rt_sigtimedwait              4
#define __NRRC_rt_sigqueueinfo              3
#define __NRRC_rt_sigsuspend                2
#define __NRRC_pread64                      5 /* __NRAC_pread64 + 1 */
#define __NRRC_pwrite64                     5 /* __NRAC_pwrite64 + 1 */
#define __NRRC_chown                        3
#define __NRRC_getcwd                       2
#define __NRRC_capget                       1
#define __NRRC_capset                       1
#define __NRRC_sigaltstack                  2
#define __NRRC_sendfile                     4
#define __NRRC_getpmsg                      1
#define __NRRC_putpmsg                      1
#define __NRRC_vfork                        0
#define __NRRC_ugetrlimit                   1
#define __NRRC_mmap2                        6
#define __NRRC_truncate64                   3 /* __NRAC_truncate64 + 1 */
#define __NRRC_ftruncate64                  3 /* __NRAC_ftruncate64 + 1 */
#define __NRRC_stat64                       2
#define __NRRC_lstat64                      2
#define __NRRC_fstat64                      2
#define __NRRC_lchown32                     3
#define __NRRC_getuid32                     0
#define __NRRC_getgid32                     0
#define __NRRC_geteuid32                    0
#define __NRRC_getegid32                    0
#define __NRRC_setreuid32                   2
#define __NRRC_setregid32                   2
#define __NRRC_getgroups32                  2
#define __NRRC_setgroups32                  2
#define __NRRC_fchown32                     3
#define __NRRC_setresuid32                  3
#define __NRRC_getresuid32                  3
#define __NRRC_setresgid32                  3
#define __NRRC_getresgid32                  3
#define __NRRC_chown32                      3
#define __NRRC_setuid32                     1
#define __NRRC_setgid32                     1
#define __NRRC_setfsuid32                   1
#define __NRRC_setfsgid32                   1
#define __NRRC_pivot_root                   1
#define __NRRC_mincore                      3
#define __NRRC_madvise                      3
#define __NRRC_getdents64                   3
#define __NRRC_fcntl64                      3
#define __NRRC_gettid                       0
#define __NRRC_readahead                    4 /* __NRAC_readahead + 1 */
#define __NRRC_setxattr                     5
#define __NRRC_lsetxattr                    5
#define __NRRC_fsetxattr                    5
#define __NRRC_getxattr                     4
#define __NRRC_lgetxattr                    4
#define __NRRC_fgetxattr                    4
#define __NRRC_listxattr                    3
#define __NRRC_llistxattr                   3
#define __NRRC_flistxattr                   3
#define __NRRC_removexattr                  2
#define __NRRC_lremovexattr                 2
#define __NRRC_fremovexattr                 2
#define __NRRC_tkill                        2
#define __NRRC_sendfile64                   4
#define __NRRC_futex                        6
#define __NRRC_sched_setaffinity            3
#define __NRRC_sched_getaffinity            3
#define __NRRC_set_thread_area              1
#define __NRRC_get_thread_area              1
#define __NRRC_io_setup                     1
#define __NRRC_io_destroy                   1
#define __NRRC_io_getevents                 1
#define __NRRC_io_submit                    1
#define __NRRC_io_cancel                    1
#define __NRRC_fadvise64                    1
#define __NRRC_exit_group                   1
#define __NRRC_lookup_dcookie               1
#define __NRRC_epoll_create                 1
#define __NRRC_epoll_ctl                    4
#define __NRRC_epoll_wait                   4
#define __NRRC_remap_file_pages             5
#define __NRRC_set_tid_address              1
#define __NRRC_timer_create                 3
#define __NRRC_timer_settime                4
#define __NRRC_timer_gettime                2
#define __NRRC_timer_getoverrun             1
#define __NRRC_timer_delete                 1
#define __NRRC_clock_settime                2
#define __NRRC_clock_gettime                2
#define __NRRC_clock_getres                 2
#define __NRRC_clock_nanosleep              4
#define __NRRC_statfs64                     2
#define __NRRC_fstatfs64                    2
#define __NRRC_tgkill                       3
#define __NRRC_utimes                       2
#define __NRRC_fadvise64_64                 1
#define __NRRC_vserver                      1
#define __NRRC_mbind                        1
#define __NRRC_get_mempolicy                1
#define __NRRC_set_mempolicy                1
#define __NRRC_mq_open                      3
#define __NRRC_mq_unlink                    1
#define __NRRC_mq_timedsend                 5
#define __NRRC_mq_timedreceive              5
#define __NRRC_mq_notify                    2
#define __NRRC_mq_getsetattr                3
#define __NRRC_kexec_load                   1
#define __NRRC_waitid                       5
#define __NRRC_add_key                      1
#define __NRRC_request_key                  1
#define __NRRC_keyctl                       1
#define __NRRC_ioprio_set                   3
#define __NRRC_ioprio_get                   2
#define __NRRC_inotify_init                 1
#define __NRRC_inotify_add_watch            1
#define __NRRC_inotify_rm_watch             1
#define __NRRC_migrate_pages                1
#define __NRRC_openat                       4
#define __NRRC_mkdirat                      3
#define __NRRC_mknodat                      4
#define __NRRC_fchownat                     5
#define __NRRC_futimesat                    3
#define __NRRC_fstatat64                    4
#define __NRRC_unlinkat                     3
#define __NRRC_renameat                     4
#define __NRRC_linkat                       5
#define __NRRC_symlinkat                    3
#define __NRRC_readlinkat                   4
#define __NRRC_fchmodat                     4
#define __NRRC_faccessat                    4
#define __NRRC_pselect6                     6
#define __NRRC_ppoll                        5
#define __NRRC_unshare                      1
#define __NRRC_set_robust_list              1
#define __NRRC_get_robust_list              1
#define __NRRC_splice                       6
#define __NRRC_sync_file_range              6 /* __NRAC_sync_file_range + 2 */
#define __NRRC_tee                          4
#define __NRRC_vmsplice                     4
#define __NRRC_move_pages                   1
#define __NRRC_getcpu                       3
#define __NRRC_epoll_pwait                  5
#define __NRRC_utimensat                    4
#define __NRRC_signalfd                     3
#define __NRRC_timerfd_create               2
#define __NRRC_eventfd                      1
#define __NRRC_fallocate                    4
#define __NRRC_timerfd_settime              4
#define __NRRC_timerfd_gettime              2
#define __NRRC_signalfd4                    4
#define __NRRC_eventfd2                     2
#define __NRRC_epoll_create1                1
#define __NRRC_dup3                         3
#define __NRRC_pipe2                        2
#define __NRRC_inotify_init1                1
#define __NRRC_preadv                       5 /* __NRAC_preadv + 1 */
#define __NRRC_pwritev                      5 /* __NRAC_pwritev + 1 */
#define __NRRC_rt_tgsigqueueinfo            4
#define __NRRC_perf_event_open              1
#define __NRRC_recvmmsg                     5
#define __NRRC_fanotify_init                1
#define __NRRC_fanotify_mark                1
#define __NRRC_prlimit64                    4
#define __NRRC_name_to_handle_at            5
#define __NRRC_open_by_handle_at            3
#define __NRRC_clock_adjtime                1
#define __NRRC_syncfs                       1
#define __NRRC_sendmmsg                     4
#define __NRRC_setns                        2
#define __NRRC_process_vm_readv             6
#define __NRRC_process_vm_writev            6
#define __NRRC_kcmp                         5
#define __NRRC_finit_module                 1
#define __NRRC_sched_setattr                1
#define __NRRC_sched_getattr                1
#define __NRRC_renameat2                    5
#define __NRRC_seccomp                      1
#define __NRRC_getrandom                    3
#define __NRRC_memfd_create                 2
#define __NRRC_bpf                          1
#define __NRRC_execveat                     5
#define __NRRC_socket                       3
#define __NRRC_socketpair                   4
#define __NRRC_bind                         3
#define __NRRC_connect                      3
#define __NRRC_listen                       2
#define __NRRC_accept4                      4
#define __NRRC_getsockopt                   5
#define __NRRC_setsockopt                   5
#define __NRRC_getsockname                  3
#define __NRRC_getpeername                  3
#define __NRRC_sendto                       6
#define __NRRC_sendmsg                      3
#define __NRRC_recvfrom                     6
#define __NRRC_recvmsg                      3
#define __NRRC_shutdown                     2
#define __NRRC_userfaultfd                  1
#define __NRRC_membarrier                   1
#define __NRRC_mlock2                       1
#define __NRRC_copy_file_range              1
#define __NRRC_preadv2                      1
#define __NRRC_pwritev2                     1
#define __NRRC_pkey_mprotect                1
#define __NRRC_pkey_alloc                   1
#define __NRRC_pkey_free                    1
#define __NRRC_statx                        1
#define __NRRC_arch_prctl                   1
#define __NRRC_io_pgetevents                1
#define __NRRC_rseq                         1
#define __NRRC_semget                       1
#define __NRRC_semctl                       1
#define __NRRC_shmget                       3
#define __NRRC_shmctl                       3
#define __NRRC_shmat                        3
#define __NRRC_shmdt                        1
#define __NRRC_msgget                       1
#define __NRRC_msgsnd                       1
#define __NRRC_msgrcv                       1
#define __NRRC_msgctl                       1
#define __NRRC_clock_gettime64              2
#define __NRRC_clock_settime64              2
#define __NRRC_clock_adjtime64              1
#define __NRRC_clock_getres_time64          2
#define __NRRC_clock_nanosleep_time64       4
#define __NRRC_timer_gettime64              2
#define __NRRC_timer_settime64              4
#define __NRRC_timerfd_gettime64            2
#define __NRRC_timerfd_settime64            4
#define __NRRC_utimensat_time64             4
#define __NRRC_pselect6_time64              6
#define __NRRC_ppoll_time64                 5
#define __NRRC_io_pgetevents_time64         1
#define __NRRC_recvmmsg_time64              5
#define __NRRC_mq_timedsend_time64          5
#define __NRRC_mq_timedreceive_time64       5
#define __NRRC_semtimedop_time64            1
#define __NRRC_rt_sigtimedwait_time64       4
#define __NRRC_futex_time64                 6
#define __NRRC_sched_rr_get_interval_time64 2
#define __NRRC_pidfd_send_signal            4
#define __NRRC_io_uring_setup               1
#define __NRRC_io_uring_enter               1
#define __NRRC_io_uring_register            1
#define __NRRC_open_tree                    1
#define __NRRC_move_mount                   1
#define __NRRC_fsopen                       1
#define __NRRC_fsconfig                     1
#define __NRRC_fsmount                      1
#define __NRRC_fspick                       1
#define __NRRC_pidfd_open                   2
#define __NRRC_clone3                       1
#define __NRRC_close_range                  1
#define __NRRC_openat2                      1
#define __NRRC_pidfd_getfd                  3
#define __NRRC_faccessat2                   1
#define __NRRC_pwritevf                     6 /* __NRAC_pwritevf + 1 */
#define __NRRC_preadvf                      6 /* __NRAC_preadvf + 1 */
#define __NRRC_fallocate64                  6 /* __NRAC_fallocate64 + 2 */
#define __NRRC_freadlinkat                  5
#define __NRRC_fsymlinkat                   4
#define __NRRC_frenameat                    5
#define __NRRC_kfstatat                     4
#define __NRRC_futimesat64                  3
#define __NRRC_fmknodat                     5
#define __NRRC_fmkdirat                     4
#define __NRRC_waitid64                     5
#define __NRRC_utimes64                     2
#define __NRRC_kreaddirf                    5
#define __NRRC_kfstat                       2
#define __NRRC_klstat                       2
#define __NRRC_kstat                        2
#define __NRRC_pwrite64f                    6 /* __NRAC_pwrite64f + 1 */
#define __NRRC_pread64f                     6 /* __NRAC_pread64f + 1 */
#define __NRRC_nanosleep64                  2
#define __NRRC_rpc_service                  0
#define __NRRC_ksysctl                      2
#define __NRRC_writevf                      4
#define __NRRC_readvf                       4
#define __NRRC_kreaddir                     4
#define __NRRC_wait4_64                     4
#define __NRRC_getitimer64                  2
#define __NRRC_setitimer64                  3
#define __NRRC_maplibrary                   5
#define __NRRC_select64                     5
#define __NRRC_settimeofday64               2
#define __NRRC_gettimeofday64               2
#define __NRRC_getrusage64                  2
#define __NRRC_fsmode                       2 /* __NRAC_fsmode + 1 */
#define __NRRC_ioctlf                       4
#define __NRRC_rtm_test                     0
#define __NRRC_rtm_abort                    1
#define __NRRC_rtm_end                      0
#define __NRRC_rtm_begin                    0
#define __NRRC_ftime64                      1
#define __NRRC_utime64                      2
#define __NRRC_userviofd                    2
#define __NRRC_stime64                      1
#define __NRRC_coredump                     6
#define __NRRC_raiseat                      2
#define __NRRC_mktty                        4
#define __NRRC_lfutexlockexpr               6
#define __NRRC_lfutexexpr                   5
#define __NRRC_lseek64                      4 /* __NRAC_lseek64 + 1 */
#define __NRRC_lfutex                       5
#define __NRRC_debugtrap                    2
#define __NRRC_get_exception_handler        3
#define __NRRC_set_exception_handler        3
#define __NRRC_time64                       1
#define __NRRC_fchdirat                     3
#define __NRRC_openpty                      5
#define __NRRC_rpc_schedule                 4
#define __NRRC_frealpathat                  5
#define __NRRC_frealpath4                   4
#define __NRRC_getdrives                    0
#define __NRRC_detach                       1
#define __NRRC_writef                       4
#define __NRRC_readf                        4
#define __NRRC_hopf                         4
#define __NRRC_hop                          3
#endif /* !__NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT */
#endif /* __WANT_SYSCALL_REGISTER_COUNT */


/************************************************************************/
/* SYSCALL DOUBLE WIDE RETURN VALUE                                     */
/************************************************************************/
#ifdef __WANT_SYSCALL_DOUBLE_WIDE_RETURN
#ifndef __NRFEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN
#define __NRFEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN 1
#define __NRFEAT_HAVE_DOUBLE_WIDE 1
#define __NRDW_fsmode                       1
#define __NRDW_lseek64                      1
#define __NRDW_time64                       1
#endif /* !__NRFEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN */
#endif /* __WANT_SYSCALL_DOUBLE_WIDE_RETURN */


