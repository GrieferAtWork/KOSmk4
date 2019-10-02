/* HASH CRC-32:0xdc18590d */
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

#define __NR32_exit                       1          /* void exit(syscall_ulong_t status) */
#define __NR32_fork                       2          /* pid_t fork(void) */
#define __NR32_read                       3          /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
#define __NR32_write                      4          /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
#define __NR32_open                       5          /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `FD' */
#define __NR32_close                      6          /* errno_t close(fd_t fd) */
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR32_waitpid                    7          /* pid_t waitpid(pid_t pid, int32_t *stat_loc, syscall_ulong_t options) */
#define __NR32_creat                      8          /* fd_t creat(char const *filename, mode_t mode) */
#define __NR32_link                       9          /* errno_t link(char const *existing_file, char const *link_file) */
#define __NR32_unlink                     10         /* errno_t unlink(char const *filename) */
#define __NR32_execve                     11         /* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
#define __NR32_chdir                      12         /* errno_t chdir(char const *path) */
#define __NR32_time                       13         /* time32_t time(time32_t *timer) */
#define __NR32_mknod                      14         /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define __NR32_chmod                      15         /* errno_t chmod(char const *filename, mode_t mode) */
#define __NR32_lchown                     16         /* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
#define __NR32_linux_oldstat              18         /* errno_t linux_oldstat(char const *filename, struct linux_oldstat *statbuf) */
#define __NR32_lseek                      19         /* int32_t lseek(fd_t fd, int32_t offset, syscall_ulong_t whence) */
#define __NR32_getpid                     20         /* pid_t getpid(void) */
#define __NR32_mount                      21         /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
#define __NR32_umount                     22         /* errno_t umount(char const *special_file) */
#define __NR32_setuid                     23         /* errno_t setuid(uint16_t uid) */
#define __NR32_getuid                     24         /* uint16_t getuid(void) */
#define __NR32_stime                      25         /* errno_t stime(time32_t const *t) */
#define __NR32_ptrace                     26         /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
#define __NR32_alarm                      27         /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
#define __NR32_linux_oldfstat             28         /* errno_t linux_oldfstat(fd_t fd, struct linux_oldstat *statbuf) */
#define __NR32_pause                      29         /* errno_t pause(void) */
#define __NR32_utime                      30         /* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define __NR32_access                     33         /* errno_t access(char const *filename, syscall_ulong_t type) */
#define __NR32_nice                       34         /* errno_t nice(syscall_slong_t inc) */
#define __NR32_ftime                      35         /* errno_t ftime(struct timeb *tp) */
#define __NR32_sync                       36         /* errno_t sync(void) */
/* @param: signo: One of `SIG*' */
#define __NR32_kill                       37         /* errno_t kill(pid_t pid, syscall_ulong_t signo) */
#define __NR32_rename                     38         /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define __NR32_mkdir                      39         /* errno_t mkdir(char const *pathname, mode_t mode) */
#define __NR32_rmdir                      40         /* errno_t rmdir(char const *path) */
#define __NR32_dup                        41         /* fd_t dup(fd_t fd) */
#define __NR32_pipe                       42         /* errno_t pipe([2]fd_t *pipedes) */
#define __NR32_times                      43         /* clock_t times(struct tms *buf) */
#define __NR32_brk                        45         /* errno_t brk(void *addr) */
#define __NR32_setgid                     46         /* errno_t setgid(uint16_t gid) */
#define __NR32_getgid                     47         /* uint16_t getgid(void) */
/* @param: signo: One of `SIG*' */
#define __NR32_signal                     48         /* sighandler_t signal(syscall_ulong_t signo, sighandler_t handler) */
#define __NR32_geteuid                    49         /* uint16_t geteuid(void) */
#define __NR32_getegid                    50         /* uint16_t getegid(void) */
#define __NR32_acct                       51         /* errno_t acct(char const *filename) */
#define __NR32_umount2                    52         /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
#define __NR32_ioctl                      54         /* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
#define __NR32_fcntl                      55         /* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
#define __NR32_setpgid                    57         /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define __NR32_oldolduname                59         /* errno_t oldolduname(struct linux_oldolduname *name) */
#define __NR32_umask                      60         /* mode_t umask(mode_t mode) */
#define __NR32_chroot                     61         /* errno_t chroot(char const *path) */
#define __NR32_ustat                      62         /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
#define __NR32_dup2                       63         /* fd_t dup2(fd_t oldfd, fd_t newfd) */
#define __NR32_getppid                    64         /* pid_t getppid(void) */
#define __NR32_getpgrp                    65         /* pid_t getpgrp(void) */
#define __NR32_setsid                     66         /* pid_t setsid(void) */
/* @param: signo: One of `SIG*' */
#define __NR32_sigaction                  67         /* errno_t sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact) */
#define __NR32_sgetmask                   68         /* syscall_ulong_t sgetmask(void) */
#define __NR32_ssetmask                   69         /* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
#define __NR32_setreuid                   70         /* errno_t setreuid(uint16_t ruid, uint16_t euid) */
#define __NR32_setregid                   71         /* errno_t setregid(uint16_t rgid, uint16_t egid) */
#define __NR32_sigsuspend                 72         /* errno_t sigsuspend(struct __sigset_struct const *set) */
#define __NR32_sigpending                 73         /* errno_t sigpending(struct __sigset_struct *set) */
#define __NR32_sethostname                74         /* errno_t sethostname(char const *name, size_t len) */
#define __NR32_setrlimit                  75         /* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
#define __NR32_getrlimit                  76         /* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
#define __NR32_getrusage                  77         /* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
#define __NR32_gettimeofday               78         /* errno_t gettimeofday(struct __timeval32 *tv, struct timezone *tz) */
#define __NR32_settimeofday               79         /* errno_t settimeofday(struct __timeval32 const *tv, struct timezone const *tz) */
#define __NR32_getgroups                  80         /* errno_t getgroups(size_t size, []uint16_t *list) */
#define __NR32_setgroups                  81         /* errno_t setgroups(size_t count, uint16_t const *groups) */
#define __NR32_select                     82         /* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval32 *timeout) */
#define __NR32_symlink                    83         /* errno_t symlink(char const *link_text, char const *target_path) */
#define __NR32_linux_oldlstat             84         /* errno_t linux_oldlstat(char const *filename, struct linux_oldstat *statbuf) */
#define __NR32_readlink                   85         /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define __NR32_swapon                     87         /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
#define __NR32_reboot                     88         /* errno_t reboot(syscall_ulong_t how) */
/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
#define __NR32_readdir                    89         /* errno_t readdir(fd_t fd, struct old_linux_dirent *dirp, size_t count) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
#define __NR32_mmap                       90         /* void * mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
#define __NR32_munmap                     91         /* errno_t munmap(void *addr, size_t len) */
#define __NR32_truncate                   92         /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define __NR32_ftruncate                  93         /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
#define __NR32_fchmod                     94         /* errno_t fchmod(fd_t fd, mode_t mode) */
#define __NR32_fchown                     95         /* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
#define __NR32_getpriority                96         /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
#define __NR32_setpriority                97         /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
#define __NR32_profil                     98         /* errno_t profil(uint16_t *sample_buffer, size_t size, size_t offset, syscall_ulong_t scale) */
#define __NR32_statfs                     99         /* errno_t statfs(char const *file, struct __statfs32 *buf) */
#define __NR32_fstatfs                    100        /* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
#define __NR32_ioperm                     101        /* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
#define __NR32_socketcall                 102        /* errno_t socketcall(int call, unsigned long *args) */
#define __NR32_syslog                     103        /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
#define __NR32_setitimer                  104        /* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
#define __NR32_getitimer                  105        /* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
#define __NR32_linux_stat32               106        /* errno_t linux_stat32(char const *filename, struct linux_stat32 *statbuf) */
#define __NR32_linux_lstat32              107        /* errno_t linux_lstat32(char const *filename, struct linux_stat32 *statbuf) */
#define __NR32_linux_fstat32              108        /* errno_t linux_fstat32(fd_t fd, struct linux_stat32 *statbuf) */
#define __NR32_olduname                   109        /* errno_t olduname(struct linux_olduname *name) */
#define __NR32_iopl                       110        /* errno_t iopl(syscall_ulong_t level) */
#define __NR32_vhangup                    111        /* errno_t vhangup(void) */
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR32_wait4                      114        /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
#define __NR32_swapoff                    115        /* errno_t swapoff(char const *pathname) */
#define __NR32_sysinfo                    116        /* errno_t sysinfo(struct sysinfo *info) */
#define __NR32_fsync                      118        /* errno_t fsync(fd_t fd) */
/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
#define __NR32_sigreturn                  119        /* void sigreturn(struct fpustate const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
#define __NR32_clone                      120        /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
#define __NR32_setdomainname              121        /* errno_t setdomainname(char const *name, size_t len) */
#define __NR32_uname                      122        /* errno_t uname(struct utsname *name) */
#define __NR32_modify_ldt                 123        /* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
#define __NR32_mprotect                   125        /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR32_sigprocmask                126        /* errno_t sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset) */
#define __NR32_getpgid                    132        /* pid_t getpgid(pid_t pid) */
#define __NR32_fchdir                     133        /* errno_t fchdir(fd_t fd) */
#define __NR32_setfsuid                   138        /* errno_t setfsuid(uint16_t uid) */
#define __NR32_setfsgid                   139        /* errno_t setfsgid(uint16_t gid) */
#define __NR32__llseek                    140        /* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
#define __NR32_getdents                   141        /* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
#define __NR32_flock                      143        /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
#define __NR32_msync                      144        /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
#define __NR32_readv                      145        /* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
#define __NR32_writev                     146        /* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
#define __NR32_getsid                     147        /* pid_t getsid(pid_t pid) */
#define __NR32_fdatasync                  148        /* errno_t fdatasync(fd_t fd) */
#define __NR32_mlock                      150        /* errno_t mlock(void const *addr, size_t len) */
#define __NR32_munlock                    151        /* errno_t munlock(void const *addr, size_t len) */
#define __NR32_mlockall                   152        /* errno_t mlockall(syscall_ulong_t flags) */
#define __NR32_munlockall                 153        /* errno_t munlockall(void) */
#define __NR32_sched_setparam             154        /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
#define __NR32_sched_getparam             155        /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
#define __NR32_sched_setscheduler         156        /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define __NR32_sched_getscheduler         157        /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define __NR32_sched_yield                158        /* errno_t sched_yield(void) */
#define __NR32_sched_get_priority_max     159        /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define __NR32_sched_get_priority_min     160        /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define __NR32_sched_rr_get_interval      161        /* errno_t sched_rr_get_interval(pid_t pid, struct __timespec32 *tms) */
#define __NR32_nanosleep                  162        /* errno_t nanosleep(struct __timespec32 const *req, struct __timespec32 *rem) */
/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
#define __NR32_mremap                     163        /* void * mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define __NR32_setresuid                  164        /* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
#define __NR32_getresuid                  165        /* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
#define __NR32_poll                       168        /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
#define __NR32_setresgid                  170        /* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
#define __NR32_getresgid                  171        /* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
/* @param: signo: One of `SIG*' */
#define __NR32_rt_sigaction               174        /* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR32_rt_sigprocmask             175        /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
#define __NR32_rt_sigpending              176        /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define __NR32_rt_sigtimedwait            177        /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec32 const *timeout, size_t sigsetsize) */
/* @param: signo: One of `SIG*' */
#define __NR32_rt_sigqueueinfo            178        /* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
#define __NR32_rt_sigsuspend              179        /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define __NR32_pread64                    180        /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define __NR32_pwrite64                   181        /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
#define __NR32_chown                      182        /* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
#define __NR32_getcwd                     183        /* ssize_t getcwd(char *buf, size_t size) */
#define __NR32_sigaltstack                186        /* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
#define __NR32_sendfile                   187        /* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
#define __NR32_vfork                      190        /* pid_t vfork(void) */
#define __NR32_mmap2                      192        /* void * mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
#define __NR32_truncate64                 193        /* errno_t truncate64(char const *filename, uint64_t length) */
#define __NR32_ftruncate64                194        /* errno_t ftruncate64(fd_t fd, uint64_t length) */
#define __NR32_linux_stat64               195        /* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
#define __NR32_linux_lstat64              196        /* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
#define __NR32_linux_fstat64              197        /* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
#define __NR32_lchown32                   198        /* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
#define __NR32_getuid32                   199        /* uint32_t getuid32(void) */
#define __NR32_getgid32                   200        /* uint32_t getgid32(void) */
#define __NR32_geteuid32                  201        /* uint32_t geteuid32(void) */
#define __NR32_getegid32                  202        /* uint32_t getegid32(void) */
#define __NR32_setreuid32                 203        /* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
#define __NR32_setregid32                 204        /* errno_t setregid32(uint32_t rgid, uint32_t egid) */
#define __NR32_getgroups32                205        /* errno_t getgroups32(size_t size, []uint32_t *list) */
#define __NR32_setgroups32                206        /* errno_t setgroups32(size_t count, uint32_t const *groups) */
#define __NR32_fchown32                   207        /* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
#define __NR32_setresuid32                208        /* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
#define __NR32_getresuid32                209        /* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
#define __NR32_setresgid32                210        /* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
#define __NR32_getresgid32                211        /* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
#define __NR32_chown32                    212        /* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
#define __NR32_setuid32                   213        /* errno_t setuid32(uint32_t uid) */
#define __NR32_setgid32                   214        /* errno_t setgid32(uint32_t gid) */
#define __NR32_setfsuid32                 215        /* errno_t setfsuid32(uint32_t uid) */
#define __NR32_setfsgid32                 216        /* errno_t setfsgid32(uint32_t gid) */
#define __NR32_mincore                    218        /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define __NR32_madvise                    219        /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
#define __NR32_getdents64                 220        /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
#define __NR32_fcntl64                    221        /* syscall_slong_t fcntl64(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR32_gettid                     224        /* pid_t gettid(void) */
#define __NR32_readahead                  225        /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
#define __NR32_setxattr                   226        /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR32_lsetxattr                  227        /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR32_fsetxattr                  228        /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR32_getxattr                   229        /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR32_lgetxattr                  230        /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR32_fgetxattr                  231        /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define __NR32_listxattr                  232        /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR32_llistxattr                 233        /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR32_flistxattr                 234        /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define __NR32_removexattr                235        /* errno_t removexattr(char const *path, char const *name) */
#define __NR32_lremovexattr               236        /* errno_t lremovexattr(char const *path, char const *name) */
#define __NR32_fremovexattr               237        /* errno_t fremovexattr(int fd, char const *name) */
/* @param: signo: One of `SIG*' */
#define __NR32_tkill                      238        /* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
#define __NR32_sendfile64                 239        /* ssize_t sendfile64(fd_t out_fd, fd_t in_fd, uint64_t *offset, size_t count) */
#define __NR32_futex                      240        /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define __NR32_sched_setaffinity          241        /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define __NR32_sched_getaffinity          242        /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define __NR32_exit_group                 252        /* void exit_group(syscall_ulong_t exit_code) */
#define __NR32_epoll_create               254        /* fd_t epoll_create(syscall_ulong_t size) */
#define __NR32_epoll_ctl                  255        /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
#define __NR32_epoll_wait                 256        /* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
#define __NR32_remap_file_pages           257        /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
#define __NR32_set_tid_address            258        /* pid_t set_tid_address(pid_t *tidptr) */
#define __NR32_timer_create               259        /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
#define __NR32_timer_settime              260        /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspec32 const *value, struct __itimerspec32 *ovalue) */
#define __NR32_timer_gettime              261        /* errno_t timer_gettime(timer_t timerid, struct __itimerspec32 *value) */
#define __NR32_timer_getoverrun           262        /* syscall_slong_t timer_getoverrun(timer_t timerid) */
#define __NR32_timer_delete               263        /* errno_t timer_delete(timer_t timerid) */
#define __NR32_clock_settime              264        /* errno_t clock_settime(clockid_t clock_id, struct __timespec32 const *tp) */
#define __NR32_clock_gettime              265        /* errno_t clock_gettime(clockid_t clock_id, struct __timespec32 *tp) */
#define __NR32_clock_getres               266        /* errno_t clock_getres(clockid_t clock_id, struct __timespec32 *res) */
#define __NR32_clock_nanosleep            267        /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespec32 const *requested_time, struct __timespec32 *remaining) */
#define __NR32_statfs64                   268        /* errno_t statfs64(char const *file, struct statfs64 *buf) */
#define __NR32_fstatfs64                  269        /* errno_t fstatfs64(fd_t file, struct statfs64 *buf) */
/* @param: signo: One of `SIG*' */
#define __NR32_tgkill                     270        /* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
#define __NR32_utimes                     271        /* errno_t utimes(char const *filename, [2]struct __timeval32 const *times) */
/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
#define __NR32_waitid                     284        /* errno_t waitid(idtype_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
#define __NR32_ioprio_set                 289        /* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
#define __NR32_ioprio_get                 290        /* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
#define __NR32_openat                     295        /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
#define __NR32_mkdirat                    296        /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
#define __NR32_mknodat                    297        /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR32_fchownat                   298        /* errno_t fchownat(fd_t dirfd, char const *filename, uint32_t owner, uint32_t group, atflag_t flags) */
#define __NR32_futimesat                  299        /* errno_t futimesat(fd_t dirfd, const char *filename, [2]struct __timeval32 const *times) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR32_linux_fstatat64            300        /* errno_t linux_fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
#define __NR32_unlinkat                   301        /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define __NR32_renameat                   302        /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
#define __NR32_linkat                     303        /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define __NR32_symlinkat                  304        /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
#define __NR32_readlinkat                 305        /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR32_fchmodat                   306        /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
#define __NR32_faccessat                  307        /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
#define __NR32_pselect6                   308        /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec32 const *timeout, void const *sigmask_sigset_and_len) */
#define __NR32_ppoll                      309        /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* param flags: Set of `CLONE_*' */
#define __NR32_unshare                    310        /* errno_t unshare(syscall_ulong_t flags) */
#define __NR32_splice                     313        /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
#define __NR32_sync_file_range            314        /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
#define __NR32_tee                        315        /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
#define __NR32_vmsplice                   316        /* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
#define __NR32_getcpu                     318        /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
#define __NR32_epoll_pwait                319        /* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#define __NR32_utimensat                  320        /* errno_t utimensat(fd_t dirfd, char const *filename, [2-3]struct __timespec32 const *times, atflag_t flags) */
#define __NR32_signalfd                   321        /* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* Return file descriptor for new interval timer source */
#define __NR32_timerfd_create             322        /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
#define __NR32_eventfd                    323        /* fd_t eventfd(syscall_ulong_t initval) */
#define __NR32_fallocate                  324        /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, uint32_t offset, uint32_t length) */
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
#define __NR32_timerfd_settime            325        /* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspec32 const *utmr, struct __itimerspec32 *otmr) */
/* Return the next expiration time of UFD */
#define __NR32_timerfd_gettime            326        /* errno_t timerfd_gettime(fd_t ufd, struct __itimerspec32 *otmr) */
#define __NR32_signalfd4                  327        /* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
#define __NR32_eventfd2                   328        /* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
#define __NR32_epoll_create1              329        /* fd_t epoll_create1(syscall_ulong_t flags) */
/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
#define __NR32_dup3                       330        /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
#define __NR32_pipe2                      331        /* errno_t pipe2([2]fd_t *pipedes, oflag_t flags) */
#define __NR32_preadv                     333        /* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
#define __NR32_pwritev                    334        /* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
/* @param: signo: One of `SIG*' */
#define __NR32_rt_tgsigqueueinfo          335        /* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
#define __NR32_recvmmsg                   337        /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec32 *tmo) */
/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
#define __NR32_prlimit64                  340        /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
#define __NR32_name_to_handle_at          341        /* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
#define __NR32_open_by_handle_at          342        /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
#define __NR32_syncfs                     344        /* errno_t syncfs(fd_t fd) */
#define __NR32_sendmmsg                   345        /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
#define __NR32_setns                      346        /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
#define __NR32_process_vm_readv           347        /* ssize_t process_vm_readv(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
#define __NR32_process_vm_writev          348        /* ssize_t process_vm_writev(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
#define __NR32_kcmp                       349        /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
#define __NR32_renameat2                  353        /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR32_execveat                   358        /* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
#define __NR32_socket                     359        /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
#define __NR32_socketpair                 360        /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, [2]fd_t *fds) */
#define __NR32_bind                       361        /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR32_connect                    362        /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR32_listen                     363        /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
#define __NR32_accept4                    364        /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define __NR32_getsockopt                 365        /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define __NR32_setsockopt                 366        /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
#define __NR32_getsockname                367        /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
#define __NR32_getpeername                368        /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
#define __NR32_sendto                     369        /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR32_sendmsg                    370        /* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
#define __NR32_recvfrom                   371        /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
#define __NR32_recvmsg                    372        /* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
#define __NR32_shutdown                   373        /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
#define __NR32_hop                        0x80000001 /* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR32_hopf                       0x80000002 /* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define __NR32_readf                      0x80000003 /* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
#define __NR32_writef                     0x80000004 /* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
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
#define __NR32_detach                     0x80000005 /* errno_t detach(pid_t pid) */
/* Returns a bitset of all of the currently mounted dos-drives */
#define __NR32_getdrives                  0x80000006 /* syscall_slong_t getdrives(void) */
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define __NR32_frealpath4                 0x80000007 /* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define __NR32_frealpathat                0x80000008 /* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
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
#define __NR32_rpc_schedule               0x80000009 /* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, void **arguments) */
#define __NR32_sysctl                     0x8000000a /* syscall_slong_t sysctl(syscall_ulong_t command, void *arg) */
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
#define __NR32_openpty                    0x8000000b /* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR32_fchdirat                   0x8000000c /* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
#define __NR32_time64                     0x8000000d /* time64_t time64(time64_t *timer) */
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
#define __NR32_set_exception_handler      0x8000000e /* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
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
#define __NR32_get_exception_handler      0x8000000f /* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
#define __NR32_set_library_listdef        0x80000010 /* errno_t set_library_listdef(struct library_listdef const *listdef) */
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
#define __NR32_debugtrap                  0x80000011 /* errno_t debugtrap(struct ucpustate const *state, struct debugtrap_reason const *reason) */
#define __NR32_lfutex                     0x80000012 /* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
#define __NR32_lseek64                    0x80000013 /* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
#define __NR32_lfutexlock                 0x80000014 /* syscall_slong_t lfutexlock(uintptr_t *ulockaddr, uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
#define __NR32_lfutexexpr                 0x80000015 /* errno_t lfutexexpr(uintptr_t *uaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
#define __NR32_lfutexlockexpr             0x80000016 /* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
#define __NR32_mktty                      0x80000017 /* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
#define __NR32_raiseat                    0x80000018 /* errno_t raiseat(struct ucpustate const *state, struct __siginfo_struct const *si) */
#define __NR32_stime64                    0x80000019 /* errno_t stime64(time64_t const *t) */
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
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == UCPUSTATE_PC(*curr_state)',
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
#define __NR32_coredump                   0x8000001a /* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, struct exception_data const *exception, syscall_ulong_t unwind_error) */
#define __NR32_utime64                    0x8000001e /* errno_t utime64(char const *filename, struct utimbuf64 const *times) */
#define __NR32_ioctlf                     0x80000036 /* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define __NR32_fsmode                     0x8000003c /* uint64_t fsmode(uint64_t mode) */
#define __NR32_gettimeofday64             0x8000004e /* errno_t gettimeofday64(struct __timeval64 *tv, struct timezone *tz) */
#define __NR32_settimeofday64             0x8000004f /* errno_t settimeofday64(struct __timeval64 const *tv, struct timezone const *tz) */
#define __NR32_select64                   0x80000052 /* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval64 *timeout) */
/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *              (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *              (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
#define __NR32_maplibrary                 0x80000056 /* void * maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
#define __NR32_setitimer64                0x80000068 /* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
#define __NR32_getitimer64                0x80000069 /* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
#define __NR32_kreaddir                   0x8000008d /* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
#define __NR32_readvf                     0x80000091 /* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
#define __NR32_writevf                    0x80000092 /* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
#define __NR32_rpc_service                0x8000009e /* syscall_slong_t rpc_service(void) */
#define __NR32_sched_rr_get_interval64    0x800000a1 /* errno_t sched_rr_get_interval64(pid_t pid, struct __timespec64 *tms) */
#define __NR32_nanosleep64                0x800000a2 /* errno_t nanosleep64(struct __timespec64 const *req, struct __timespec64 *rem) */
#define __NR32_rt_sigtimedwait64          0x800000b1 /* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec64 const *timeout, size_t sigsetsize) */
#define __NR32_pread64f                   0x800000b4 /* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR32_pwrite64f                  0x800000b5 /* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR32_kstat                      0x800000c3 /* errno_t kstat(char const *filename, struct stat *statbuf) */
#define __NR32_klstat                     0x800000c4 /* errno_t klstat(char const *filename, struct stat *statbuf) */
#define __NR32_kfstat                     0x800000c5 /* errno_t kfstat(fd_t fd, struct stat *statbuf) */
#define __NR32_kreaddirf                  0x800000dc /* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
#define __NR32_timer_settime64            0x80000104 /* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct __itimerspec64 const *value, struct __itimerspec64 *ovalue) */
#define __NR32_timer_gettime64            0x80000105 /* errno_t timer_gettime64(timer_t timerid, struct __itimerspec64 *value) */
#define __NR32_clock_settime64            0x80000108 /* errno_t clock_settime64(clockid_t clock_id, struct __timespec64 const *tp) */
#define __NR32_clock_gettime64            0x80000109 /* errno_t clock_gettime64(clockid_t clock_id, struct __timespec64 *tp) */
#define __NR32_clock_getres64             0x8000010a /* errno_t clock_getres64(clockid_t clock_id, struct __timespec64 *res) */
#define __NR32_clock_nanosleep64          0x8000010b /* errno_t clock_nanosleep64(clockid_t clock_id, syscall_ulong_t flags, struct __timespec64 const *requested_time, struct __timespec64 *remaining) */
#define __NR32_utimes64                   0x8000010f /* errno_t utimes64(char const *filename, [2]struct __timeval64 const *times) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR32_fmkdirat                   0x80000128 /* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR32_fmknodat                   0x80000129 /* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#define __NR32_futimesat64                0x8000012b /* errno_t futimesat64(fd_t dirfd, const char *filename, [2-3]struct __timeval64 const *times) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR32_kfstatat                   0x8000012c /* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR32_frenameat                  0x8000012e /* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR32_fsymlinkat                 0x80000130 /* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define __NR32_freadlinkat                0x80000131 /* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
#define __NR32_pselect6_64                0x80000134 /* ssize_t pselect6_64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec64 const *timeout, void const *sigmask_sigset_and_len) */
#define __NR32_ppoll64                    0x80000135 /* ssize_t ppoll64(struct pollfd *fds, size_t nfds, struct __timespec64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#define __NR32_utimensat64                0x80000140 /* errno_t utimensat64(fd_t dirfd, char const *filename, [2-3]struct __timespec64 const *times, atflag_t flags) */
#define __NR32_fallocate64                0x80000144 /* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
#define __NR32_timerfd_settime64          0x80000145 /* errno_t timerfd_settime64(fd_t ufd, syscall_ulong_t flags, struct __itimerspec64 const *utmr, struct __itimerspec64 *otmr) */
/* Return the next expiration time of UFD */
#define __NR32_timerfd_gettime64          0x80000146 /* errno_t timerfd_gettime64(fd_t ufd, struct __itimerspec64 *otmr) */
#define __NR32_preadvf                    0x8000014d /* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
#define __NR32_pwritevf                   0x8000014e /* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
#define __NR32_recvmmsg64                 0x80000151 /* ssize_t recvmmsg64(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec64 *tmo) */

#define __NR32_syscall_min   1
#define __NR32_syscall_max   373
#define __NR32_exsyscall_min 0x80000001
#define __NR32_exsyscall_max 0x80000151

#ifdef __WANT_SYSCALL_RESTART_MODES
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
#define __NR32RM_exit                       2
#define __NR32RM_fork                       2
#define __NR32RM_read                       0
#define __NR32RM_write                      0
#define __NR32RM_open                       0
#define __NR32RM_close                      2
#define __NR32RM_waitpid                    1
#define __NR32RM_creat                      0
#define __NR32RM_link                       0
#define __NR32RM_unlink                     0
#define __NR32RM_execve                     0
#define __NR32RM_chdir                      0
#define __NR32RM_time                       0
#define __NR32RM_mknod                      0
#define __NR32RM_chmod                      0
#define __NR32RM_lchown                     0
#define __NR32RM_linux_oldstat              0
#define __NR32RM_lseek                      0
#define __NR32RM_getpid                     2
#define __NR32RM_mount                      0
#define __NR32RM_umount                     0
#define __NR32RM_setuid                     2
#define __NR32RM_getuid                     2
#define __NR32RM_stime                      0
#define __NR32RM_ptrace                     0
#define __NR32RM_alarm                      0
#define __NR32RM_linux_oldfstat             0
#define __NR32RM_pause                      1
#define __NR32RM_utime                      0
#define __NR32RM_access                     0
#define __NR32RM_nice                       0
#define __NR32RM_ftime                      0
#define __NR32RM_sync                       0
#define __NR32RM_kill                       0
#define __NR32RM_rename                     0
#define __NR32RM_mkdir                      0
#define __NR32RM_rmdir                      0
#define __NR32RM_dup                        0
#define __NR32RM_pipe                       0
#define __NR32RM_times                      0
#define __NR32RM_brk                        0
#define __NR32RM_setgid                     2
#define __NR32RM_getgid                     2
#define __NR32RM_signal                     0
#define __NR32RM_geteuid                    2
#define __NR32RM_getegid                    2
#define __NR32RM_acct                       0
#define __NR32RM_umount2                    2
#define __NR32RM_ioctl                      0
#define __NR32RM_fcntl                      0
#define __NR32RM_setpgid                    2
#define __NR32RM_oldolduname                0
#define __NR32RM_umask                      2
#define __NR32RM_chroot                     0
#define __NR32RM_ustat                      0
#define __NR32RM_dup2                       0
#define __NR32RM_getppid                    2
#define __NR32RM_getpgrp                    2
#define __NR32RM_setsid                     2
#define __NR32RM_sigaction                  0
#define __NR32RM_sgetmask                   0
#define __NR32RM_ssetmask                   0
#define __NR32RM_setreuid                   2
#define __NR32RM_setregid                   2
#define __NR32RM_sigsuspend                 1
#define __NR32RM_sigpending                 0
#define __NR32RM_sethostname                0
#define __NR32RM_setrlimit                  0
#define __NR32RM_getrlimit                  0
#define __NR32RM_getrusage                  0
#define __NR32RM_gettimeofday               0
#define __NR32RM_settimeofday               0
#define __NR32RM_getgroups                  0
#define __NR32RM_setgroups                  0
#define __NR32RM_select                     1
#define __NR32RM_symlink                    0
#define __NR32RM_linux_oldlstat             0
#define __NR32RM_readlink                   0
#define __NR32RM_swapon                     0
#define __NR32RM_reboot                     0
#define __NR32RM_readdir                    0
#define __NR32RM_mmap                       0
#define __NR32RM_munmap                     2
#define __NR32RM_truncate                   0
#define __NR32RM_ftruncate                  0
#define __NR32RM_fchmod                     0
#define __NR32RM_fchown                     0
#define __NR32RM_getpriority                0
#define __NR32RM_setpriority                0
#define __NR32RM_profil                     0
#define __NR32RM_statfs                     0
#define __NR32RM_fstatfs                    0
#define __NR32RM_ioperm                     0
#define __NR32RM_socketcall                 0
#define __NR32RM_syslog                     2
#define __NR32RM_setitimer                  0
#define __NR32RM_getitimer                  0
#define __NR32RM_linux_stat32               0
#define __NR32RM_linux_lstat32              0
#define __NR32RM_linux_fstat32              0
#define __NR32RM_olduname                   0
#define __NR32RM_iopl                       0
#define __NR32RM_vhangup                    0
#define __NR32RM_wait4                      1
#define __NR32RM_swapoff                    0
#define __NR32RM_sysinfo                    0
#define __NR32RM_fsync                      0
#define __NR32RM_sigreturn                  2
#define __NR32RM_clone                      0
#define __NR32RM_setdomainname              0
#define __NR32RM_uname                      0
#define __NR32RM_modify_ldt                 0
#define __NR32RM_mprotect                   2
#define __NR32RM_sigprocmask                0
#define __NR32RM_getpgid                    2
#define __NR32RM_fchdir                     0
#define __NR32RM_setfsuid                   2
#define __NR32RM_setfsgid                   2
#define __NR32RM__llseek                    0
#define __NR32RM_getdents                   0
#define __NR32RM_flock                      0
#define __NR32RM_msync                      0
#define __NR32RM_readv                      0
#define __NR32RM_writev                     0
#define __NR32RM_getsid                     2
#define __NR32RM_fdatasync                  0
#define __NR32RM_mlock                      0
#define __NR32RM_munlock                    0
#define __NR32RM_mlockall                   0
#define __NR32RM_munlockall                 0
#define __NR32RM_sched_setparam             0
#define __NR32RM_sched_getparam             0
#define __NR32RM_sched_setscheduler         0
#define __NR32RM_sched_getscheduler         0
#define __NR32RM_sched_yield                1
#define __NR32RM_sched_get_priority_max     0
#define __NR32RM_sched_get_priority_min     0
#define __NR32RM_sched_rr_get_interval      0
#define __NR32RM_nanosleep                  1
#define __NR32RM_mremap                     0
#define __NR32RM_setresuid                  2
#define __NR32RM_getresuid                  2
#define __NR32RM_poll                       1
#define __NR32RM_setresgid                  2
#define __NR32RM_getresgid                  2
#define __NR32RM_rt_sigaction               0
#define __NR32RM_rt_sigprocmask             0
#define __NR32RM_rt_sigpending              0
#define __NR32RM_rt_sigtimedwait            1
#define __NR32RM_rt_sigqueueinfo            0
#define __NR32RM_rt_sigsuspend              0
#define __NR32RM_pread64                    0
#define __NR32RM_pwrite64                   0
#define __NR32RM_chown                      0
#define __NR32RM_getcwd                     0
#define __NR32RM_sigaltstack                0
#define __NR32RM_sendfile                   1
#define __NR32RM_vfork                      0
#define __NR32RM_mmap2                      0
#define __NR32RM_truncate64                 0
#define __NR32RM_ftruncate64                0
#define __NR32RM_linux_stat64               0
#define __NR32RM_linux_lstat64              0
#define __NR32RM_linux_fstat64              0
#define __NR32RM_lchown32                   0
#define __NR32RM_getuid32                   2
#define __NR32RM_getgid32                   2
#define __NR32RM_geteuid32                  2
#define __NR32RM_getegid32                  2
#define __NR32RM_setreuid32                 2
#define __NR32RM_setregid32                 2
#define __NR32RM_getgroups32                2
#define __NR32RM_setgroups32                2
#define __NR32RM_fchown32                   0
#define __NR32RM_setresuid32                2
#define __NR32RM_getresuid32                2
#define __NR32RM_setresgid32                2
#define __NR32RM_getresgid32                2
#define __NR32RM_chown32                    0
#define __NR32RM_setuid32                   2
#define __NR32RM_setgid32                   2
#define __NR32RM_setfsuid32                 2
#define __NR32RM_setfsgid32                 2
#define __NR32RM_mincore                    0
#define __NR32RM_madvise                    0
#define __NR32RM_getdents64                 0
#define __NR32RM_fcntl64                    0
#define __NR32RM_gettid                     2
#define __NR32RM_readahead                  0
#define __NR32RM_setxattr                   0
#define __NR32RM_lsetxattr                  0
#define __NR32RM_fsetxattr                  0
#define __NR32RM_getxattr                   0
#define __NR32RM_lgetxattr                  0
#define __NR32RM_fgetxattr                  0
#define __NR32RM_listxattr                  0
#define __NR32RM_llistxattr                 0
#define __NR32RM_flistxattr                 0
#define __NR32RM_removexattr                0
#define __NR32RM_lremovexattr               0
#define __NR32RM_fremovexattr               0
#define __NR32RM_tkill                      0
#define __NR32RM_sendfile64                 0
#define __NR32RM_futex                      0
#define __NR32RM_sched_setaffinity          0
#define __NR32RM_sched_getaffinity          0
#define __NR32RM_exit_group                 2
#define __NR32RM_epoll_create               0
#define __NR32RM_epoll_ctl                  0
#define __NR32RM_epoll_wait                 1
#define __NR32RM_remap_file_pages           0
#define __NR32RM_set_tid_address            0
#define __NR32RM_timer_create               0
#define __NR32RM_timer_settime              0
#define __NR32RM_timer_gettime              0
#define __NR32RM_timer_getoverrun           0
#define __NR32RM_timer_delete               0
#define __NR32RM_clock_settime              0
#define __NR32RM_clock_gettime              0
#define __NR32RM_clock_getres               0
#define __NR32RM_clock_nanosleep            1
#define __NR32RM_statfs64                   0
#define __NR32RM_fstatfs64                  0
#define __NR32RM_tgkill                     0
#define __NR32RM_utimes                     0
#define __NR32RM_waitid                     1
#define __NR32RM_ioprio_set                 0
#define __NR32RM_ioprio_get                 0
#define __NR32RM_openat                     0
#define __NR32RM_mkdirat                    0
#define __NR32RM_mknodat                    0
#define __NR32RM_fchownat                   0
#define __NR32RM_futimesat                  0
#define __NR32RM_linux_fstatat64            0
#define __NR32RM_unlinkat                   0
#define __NR32RM_renameat                   0
#define __NR32RM_linkat                     0
#define __NR32RM_symlinkat                  0
#define __NR32RM_readlinkat                 0
#define __NR32RM_fchmodat                   0
#define __NR32RM_faccessat                  0
#define __NR32RM_pselect6                   1
#define __NR32RM_ppoll                      1
#define __NR32RM_unshare                    0
#define __NR32RM_splice                     0
#define __NR32RM_sync_file_range            0
#define __NR32RM_tee                        0
#define __NR32RM_vmsplice                   0
#define __NR32RM_getcpu                     0
#define __NR32RM_epoll_pwait                1
#define __NR32RM_utimensat                  0
#define __NR32RM_signalfd                   0
#define __NR32RM_timerfd_create             0
#define __NR32RM_eventfd                    0
#define __NR32RM_fallocate                  0
#define __NR32RM_timerfd_settime            0
#define __NR32RM_timerfd_gettime            0
#define __NR32RM_signalfd4                  0
#define __NR32RM_eventfd2                   0
#define __NR32RM_epoll_create1              0
#define __NR32RM_dup3                       0
#define __NR32RM_pipe2                      0
#define __NR32RM_preadv                     0
#define __NR32RM_pwritev                    0
#define __NR32RM_rt_tgsigqueueinfo          0
#define __NR32RM_recvmmsg                   1
#define __NR32RM_prlimit64                  0
#define __NR32RM_name_to_handle_at          0
#define __NR32RM_open_by_handle_at          0
#define __NR32RM_syncfs                     0
#define __NR32RM_sendmmsg                   1
#define __NR32RM_setns                      0
#define __NR32RM_process_vm_readv           0
#define __NR32RM_process_vm_writev          0
#define __NR32RM_kcmp                       0
#define __NR32RM_renameat2                  0
#define __NR32RM_execveat                   0
#define __NR32RM_socket                     0
#define __NR32RM_socketpair                 0
#define __NR32RM_bind                       0
#define __NR32RM_connect                    1
#define __NR32RM_listen                     0
#define __NR32RM_accept4                    1
#define __NR32RM_getsockopt                 0
#define __NR32RM_setsockopt                 1
#define __NR32RM_getsockname                0
#define __NR32RM_getpeername                0
#define __NR32RM_sendto                     1
#define __NR32RM_sendmsg                    1
#define __NR32RM_recvfrom                   1
#define __NR32RM_recvmsg                    1
#define __NR32RM_shutdown                   0
#define __NR32RM_hop                        0
#define __NR32RM_hopf                       0
#define __NR32RM_readf                      0
#define __NR32RM_writef                     0
#define __NR32RM_detach                     2
#define __NR32RM_getdrives                  2
#define __NR32RM_frealpath4                 0
#define __NR32RM_frealpathat                0
#define __NR32RM_rpc_schedule               0
#define __NR32RM_sysctl                     0
#define __NR32RM_openpty                    0
#define __NR32RM_fchdirat                   0
#define __NR32RM_time64                     0
#define __NR32RM_set_exception_handler      2
#define __NR32RM_get_exception_handler      2
#define __NR32RM_set_library_listdef        2
#define __NR32RM_debugtrap                  0
#define __NR32RM_lfutex                     1
#define __NR32RM_lseek64                    0
#define __NR32RM_lfutexlock                 1
#define __NR32RM_lfutexexpr                 1
#define __NR32RM_lfutexlockexpr             1
#define __NR32RM_mktty                      0
#define __NR32RM_raiseat                    2
#define __NR32RM_stime64                    0
#define __NR32RM_coredump                   2
#define __NR32RM_utime64                    0
#define __NR32RM_ioctlf                     0
#define __NR32RM_fsmode                     2
#define __NR32RM_gettimeofday64             0
#define __NR32RM_settimeofday64             0
#define __NR32RM_select64                   1
#define __NR32RM_maplibrary                 0
#define __NR32RM_setitimer64                0
#define __NR32RM_getitimer64                0
#define __NR32RM_kreaddir                   0
#define __NR32RM_readvf                     0
#define __NR32RM_writevf                    0
#define __NR32RM_rpc_service                1
#define __NR32RM_sched_rr_get_interval64    0
#define __NR32RM_nanosleep64                1
#define __NR32RM_rt_sigtimedwait64          1
#define __NR32RM_pread64f                   0
#define __NR32RM_pwrite64f                  0
#define __NR32RM_kstat                      0
#define __NR32RM_klstat                     0
#define __NR32RM_kfstat                     0
#define __NR32RM_kreaddirf                  0
#define __NR32RM_timer_settime64            0
#define __NR32RM_timer_gettime64            0
#define __NR32RM_clock_settime64            0
#define __NR32RM_clock_gettime64            0
#define __NR32RM_clock_getres64             0
#define __NR32RM_clock_nanosleep64          1
#define __NR32RM_utimes64                   0
#define __NR32RM_fmkdirat                   0
#define __NR32RM_fmknodat                   0
#define __NR32RM_futimesat64                0
#define __NR32RM_kfstatat                   0
#define __NR32RM_frenameat                  0
#define __NR32RM_fsymlinkat                 0
#define __NR32RM_freadlinkat                0
#define __NR32RM_pselect6_64                1
#define __NR32RM_ppoll64                    1
#define __NR32RM_utimensat64                0
#define __NR32RM_fallocate64                0
#define __NR32RM_timerfd_settime64          0
#define __NR32RM_timerfd_gettime64          0
#define __NR32RM_preadvf                    0
#define __NR32RM_pwritevf                   0
#define __NR32RM_recvmmsg64                 1
#endif /* __WANT_SYSCALL_RESTART_MODES */

#ifdef __WANT_SYSCALL_CANCELLATION_POINTS
#define __NR32CP_exit                       0
#define __NR32CP_fork                       0
#define __NR32CP_read                       1
#define __NR32CP_write                      1
#define __NR32CP_open                       1
#define __NR32CP_close                      0
#define __NR32CP_waitpid                    1
#define __NR32CP_creat                      1
#define __NR32CP_link                       1
#define __NR32CP_unlink                     1
#define __NR32CP_execve                     1
#define __NR32CP_chdir                      1
#define __NR32CP_time                       0
#define __NR32CP_mknod                      1
#define __NR32CP_chmod                      1
#define __NR32CP_lchown                     1
#define __NR32CP_linux_oldstat              1
#define __NR32CP_lseek                      1
#define __NR32CP_getpid                     0
#define __NR32CP_mount                      1
#define __NR32CP_umount                     1
#define __NR32CP_setuid                     0
#define __NR32CP_getuid                     0
#define __NR32CP_stime                      0
#define __NR32CP_ptrace                     0
#define __NR32CP_alarm                      0
#define __NR32CP_linux_oldfstat             1
#define __NR32CP_pause                      1
#define __NR32CP_utime                      1
#define __NR32CP_access                     1
#define __NR32CP_nice                       0
#define __NR32CP_ftime                      0
#define __NR32CP_sync                       1
#define __NR32CP_kill                       0
#define __NR32CP_rename                     1
#define __NR32CP_mkdir                      1
#define __NR32CP_rmdir                      0
#define __NR32CP_dup                        0
#define __NR32CP_pipe                       0
#define __NR32CP_times                      0
#define __NR32CP_brk                        0
#define __NR32CP_setgid                     0
#define __NR32CP_getgid                     0
#define __NR32CP_signal                     0
#define __NR32CP_geteuid                    0
#define __NR32CP_getegid                    0
#define __NR32CP_acct                       0
#define __NR32CP_umount2                    1
#define __NR32CP_ioctl                      1
#define __NR32CP_fcntl                      1
#define __NR32CP_setpgid                    0
#define __NR32CP_oldolduname                0
#define __NR32CP_umask                      0
#define __NR32CP_chroot                     0
#define __NR32CP_ustat                      0
#define __NR32CP_dup2                       0
#define __NR32CP_getppid                    0
#define __NR32CP_getpgrp                    0
#define __NR32CP_setsid                     0
#define __NR32CP_sigaction                  0
#define __NR32CP_sgetmask                   0
#define __NR32CP_ssetmask                   0
#define __NR32CP_setreuid                   0
#define __NR32CP_setregid                   0
#define __NR32CP_sigsuspend                 1
#define __NR32CP_sigpending                 0
#define __NR32CP_sethostname                0
#define __NR32CP_setrlimit                  0
#define __NR32CP_getrlimit                  0
#define __NR32CP_getrusage                  0
#define __NR32CP_gettimeofday               0
#define __NR32CP_settimeofday               0
#define __NR32CP_getgroups                  0
#define __NR32CP_setgroups                  0
#define __NR32CP_select                     1
#define __NR32CP_symlink                    1
#define __NR32CP_linux_oldlstat             1
#define __NR32CP_readlink                   1
#define __NR32CP_swapon                     0
#define __NR32CP_reboot                     0
#define __NR32CP_readdir                    0
#define __NR32CP_mmap                       0
#define __NR32CP_munmap                     0
#define __NR32CP_truncate                   0
#define __NR32CP_ftruncate                  0
#define __NR32CP_fchmod                     1
#define __NR32CP_fchown                     1
#define __NR32CP_getpriority                0
#define __NR32CP_setpriority                0
#define __NR32CP_profil                     0
#define __NR32CP_statfs                     0
#define __NR32CP_fstatfs                    0
#define __NR32CP_ioperm                     0
#define __NR32CP_socketcall                 0
#define __NR32CP_syslog                     1
#define __NR32CP_setitimer                  0
#define __NR32CP_getitimer                  0
#define __NR32CP_linux_stat32               1
#define __NR32CP_linux_lstat32              1
#define __NR32CP_linux_fstat32              1
#define __NR32CP_olduname                   0
#define __NR32CP_iopl                       0
#define __NR32CP_vhangup                    0
#define __NR32CP_wait4                      1
#define __NR32CP_swapoff                    0
#define __NR32CP_sysinfo                    1
#define __NR32CP_fsync                      1
#define __NR32CP_sigreturn                  0
#define __NR32CP_clone                      0
#define __NR32CP_setdomainname              0
#define __NR32CP_uname                      0
#define __NR32CP_modify_ldt                 0
#define __NR32CP_mprotect                   0
#define __NR32CP_sigprocmask                0
#define __NR32CP_getpgid                    0
#define __NR32CP_fchdir                     1
#define __NR32CP_setfsuid                   0
#define __NR32CP_setfsgid                   0
#define __NR32CP__llseek                    1
#define __NR32CP_getdents                   1
#define __NR32CP_flock                      1
#define __NR32CP_msync                      1
#define __NR32CP_readv                      1
#define __NR32CP_writev                     1
#define __NR32CP_getsid                     0
#define __NR32CP_fdatasync                  1
#define __NR32CP_mlock                      0
#define __NR32CP_munlock                    0
#define __NR32CP_mlockall                   0
#define __NR32CP_munlockall                 0
#define __NR32CP_sched_setparam             0
#define __NR32CP_sched_getparam             0
#define __NR32CP_sched_setscheduler         0
#define __NR32CP_sched_getscheduler         0
#define __NR32CP_sched_yield                0
#define __NR32CP_sched_get_priority_max     0
#define __NR32CP_sched_get_priority_min     0
#define __NR32CP_sched_rr_get_interval      0
#define __NR32CP_nanosleep                  1
#define __NR32CP_mremap                     0
#define __NR32CP_setresuid                  0
#define __NR32CP_getresuid                  0
#define __NR32CP_poll                       1
#define __NR32CP_setresgid                  0
#define __NR32CP_getresgid                  0
#define __NR32CP_rt_sigaction               0
#define __NR32CP_rt_sigprocmask             0
#define __NR32CP_rt_sigpending              0
#define __NR32CP_rt_sigtimedwait            1
#define __NR32CP_rt_sigqueueinfo            0
#define __NR32CP_rt_sigsuspend              0
#define __NR32CP_pread64                    1
#define __NR32CP_pwrite64                   1
#define __NR32CP_chown                      1
#define __NR32CP_getcwd                     1
#define __NR32CP_sigaltstack                0
#define __NR32CP_sendfile                   1
#define __NR32CP_vfork                      0
#define __NR32CP_mmap2                      0
#define __NR32CP_truncate64                 0
#define __NR32CP_ftruncate64                0
#define __NR32CP_linux_stat64               1
#define __NR32CP_linux_lstat64              1
#define __NR32CP_linux_fstat64              1
#define __NR32CP_lchown32                   1
#define __NR32CP_getuid32                   0
#define __NR32CP_getgid32                   0
#define __NR32CP_geteuid32                  0
#define __NR32CP_getegid32                  0
#define __NR32CP_setreuid32                 0
#define __NR32CP_setregid32                 0
#define __NR32CP_getgroups32                0
#define __NR32CP_setgroups32                0
#define __NR32CP_fchown32                   1
#define __NR32CP_setresuid32                0
#define __NR32CP_getresuid32                0
#define __NR32CP_setresgid32                0
#define __NR32CP_getresgid32                0
#define __NR32CP_chown32                    1
#define __NR32CP_setuid32                   0
#define __NR32CP_setgid32                   0
#define __NR32CP_setfsuid32                 0
#define __NR32CP_setfsgid32                 0
#define __NR32CP_mincore                    0
#define __NR32CP_madvise                    0
#define __NR32CP_getdents64                 1
#define __NR32CP_fcntl64                    1
#define __NR32CP_gettid                     0
#define __NR32CP_readahead                  0
#define __NR32CP_setxattr                   1
#define __NR32CP_lsetxattr                  1
#define __NR32CP_fsetxattr                  1
#define __NR32CP_getxattr                   1
#define __NR32CP_lgetxattr                  1
#define __NR32CP_fgetxattr                  1
#define __NR32CP_listxattr                  1
#define __NR32CP_llistxattr                 1
#define __NR32CP_flistxattr                 1
#define __NR32CP_removexattr                1
#define __NR32CP_lremovexattr               1
#define __NR32CP_fremovexattr               1
#define __NR32CP_tkill                      0
#define __NR32CP_sendfile64                 0
#define __NR32CP_futex                      1
#define __NR32CP_sched_setaffinity          0
#define __NR32CP_sched_getaffinity          0
#define __NR32CP_exit_group                 0
#define __NR32CP_epoll_create               0
#define __NR32CP_epoll_ctl                  0
#define __NR32CP_epoll_wait                 1
#define __NR32CP_remap_file_pages           0
#define __NR32CP_set_tid_address            0
#define __NR32CP_timer_create               0
#define __NR32CP_timer_settime              0
#define __NR32CP_timer_gettime              0
#define __NR32CP_timer_getoverrun           0
#define __NR32CP_timer_delete               0
#define __NR32CP_clock_settime              0
#define __NR32CP_clock_gettime              0
#define __NR32CP_clock_getres               0
#define __NR32CP_clock_nanosleep            1
#define __NR32CP_statfs64                   0
#define __NR32CP_fstatfs64                  0
#define __NR32CP_tgkill                     0
#define __NR32CP_utimes                     1
#define __NR32CP_waitid                     1
#define __NR32CP_ioprio_set                 0
#define __NR32CP_ioprio_get                 0
#define __NR32CP_openat                     1
#define __NR32CP_mkdirat                    1
#define __NR32CP_mknodat                    1
#define __NR32CP_fchownat                   1
#define __NR32CP_futimesat                  1
#define __NR32CP_linux_fstatat64            1
#define __NR32CP_unlinkat                   1
#define __NR32CP_renameat                   1
#define __NR32CP_linkat                     1
#define __NR32CP_symlinkat                  1
#define __NR32CP_readlinkat                 1
#define __NR32CP_fchmodat                   1
#define __NR32CP_faccessat                  1
#define __NR32CP_pselect6                   1
#define __NR32CP_ppoll                      1
#define __NR32CP_unshare                    0
#define __NR32CP_splice                     1
#define __NR32CP_sync_file_range            1
#define __NR32CP_tee                        1
#define __NR32CP_vmsplice                   1
#define __NR32CP_getcpu                     0
#define __NR32CP_epoll_pwait                1
#define __NR32CP_utimensat                  1
#define __NR32CP_signalfd                   0
#define __NR32CP_timerfd_create             0
#define __NR32CP_eventfd                    0
#define __NR32CP_fallocate                  0
#define __NR32CP_timerfd_settime            0
#define __NR32CP_timerfd_gettime            0
#define __NR32CP_signalfd4                  0
#define __NR32CP_eventfd2                   0
#define __NR32CP_epoll_create1              0
#define __NR32CP_dup3                       0
#define __NR32CP_pipe2                      0
#define __NR32CP_preadv                     1
#define __NR32CP_pwritev                    1
#define __NR32CP_rt_tgsigqueueinfo          0
#define __NR32CP_recvmmsg                   1
#define __NR32CP_prlimit64                  0
#define __NR32CP_name_to_handle_at          1
#define __NR32CP_open_by_handle_at          1
#define __NR32CP_syncfs                     1
#define __NR32CP_sendmmsg                   1
#define __NR32CP_setns                      0
#define __NR32CP_process_vm_readv           0
#define __NR32CP_process_vm_writev          0
#define __NR32CP_kcmp                       0
#define __NR32CP_renameat2                  1
#define __NR32CP_execveat                   1
#define __NR32CP_socket                     0
#define __NR32CP_socketpair                 0
#define __NR32CP_bind                       0
#define __NR32CP_connect                    1
#define __NR32CP_listen                     0
#define __NR32CP_accept4                    1
#define __NR32CP_getsockopt                 0
#define __NR32CP_setsockopt                 0
#define __NR32CP_getsockname                0
#define __NR32CP_getpeername                0
#define __NR32CP_sendto                     1
#define __NR32CP_sendmsg                    1
#define __NR32CP_recvfrom                   1
#define __NR32CP_recvmsg                    1
#define __NR32CP_shutdown                   0
#define __NR32CP_hop                        1
#define __NR32CP_hopf                       1
#define __NR32CP_readf                      1
#define __NR32CP_writef                     1
#define __NR32CP_detach                     0
#define __NR32CP_getdrives                  0
#define __NR32CP_frealpath4                 1
#define __NR32CP_frealpathat                1
#define __NR32CP_rpc_schedule               0
#define __NR32CP_sysctl                     1
#define __NR32CP_openpty                    0
#define __NR32CP_fchdirat                   1
#define __NR32CP_time64                     0
#define __NR32CP_set_exception_handler      0
#define __NR32CP_get_exception_handler      0
#define __NR32CP_set_library_listdef        0
#define __NR32CP_debugtrap                  0
#define __NR32CP_lfutex                     1
#define __NR32CP_lseek64                    1
#define __NR32CP_lfutexlock                 1
#define __NR32CP_lfutexexpr                 1
#define __NR32CP_lfutexlockexpr             1
#define __NR32CP_mktty                      0
#define __NR32CP_raiseat                    0
#define __NR32CP_stime64                    0
#define __NR32CP_coredump                   0
#define __NR32CP_utime64                    1
#define __NR32CP_ioctlf                     1
#define __NR32CP_fsmode                     0
#define __NR32CP_gettimeofday64             0
#define __NR32CP_settimeofday64             0
#define __NR32CP_select64                   1
#define __NR32CP_maplibrary                 0
#define __NR32CP_setitimer64                0
#define __NR32CP_getitimer64                0
#define __NR32CP_kreaddir                   1
#define __NR32CP_readvf                     1
#define __NR32CP_writevf                    1
#define __NR32CP_rpc_service                1
#define __NR32CP_sched_rr_get_interval64    0
#define __NR32CP_nanosleep64                1
#define __NR32CP_rt_sigtimedwait64          1
#define __NR32CP_pread64f                   1
#define __NR32CP_pwrite64f                  1
#define __NR32CP_kstat                      1
#define __NR32CP_klstat                     1
#define __NR32CP_kfstat                     1
#define __NR32CP_kreaddirf                  1
#define __NR32CP_timer_settime64            0
#define __NR32CP_timer_gettime64            0
#define __NR32CP_clock_settime64            0
#define __NR32CP_clock_gettime64            0
#define __NR32CP_clock_getres64             0
#define __NR32CP_clock_nanosleep64          1
#define __NR32CP_utimes64                   1
#define __NR32CP_fmkdirat                   1
#define __NR32CP_fmknodat                   1
#define __NR32CP_futimesat64                1
#define __NR32CP_kfstatat                   1
#define __NR32CP_frenameat                  1
#define __NR32CP_fsymlinkat                 1
#define __NR32CP_freadlinkat                1
#define __NR32CP_pselect6_64                1
#define __NR32CP_ppoll64                    1
#define __NR32CP_utimensat64                1
#define __NR32CP_fallocate64                0
#define __NR32CP_timerfd_settime64          0
#define __NR32CP_timerfd_gettime64          0
#define __NR32CP_preadvf                    1
#define __NR32CP_pwritevf                   1
#define __NR32CP_recvmmsg64                 1
#endif /* __WANT_SYSCALL_CANCELLATION_POINTS */

#ifdef __WANT_SYSCALL_RETURN_TYPES
#define __NR32RT_exit                       void
#define __NR32RT_fork                       pid_t
#define __NR32RT_read                       ssize_t
#define __NR32RT_write                      ssize_t
#define __NR32RT_open                       fd_t
#define __NR32RT_close                      errno_t
#define __NR32RT_waitpid                    pid_t
#define __NR32RT_creat                      fd_t
#define __NR32RT_link                       errno_t
#define __NR32RT_unlink                     errno_t
#define __NR32RT_execve                     errno_t
#define __NR32RT_chdir                      errno_t
#define __NR32RT_time                       time32_t
#define __NR32RT_mknod                      errno_t
#define __NR32RT_chmod                      errno_t
#define __NR32RT_lchown                     errno_t
#define __NR32RT_linux_oldstat              errno_t
#define __NR32RT_lseek                      int32_t
#define __NR32RT_getpid                     pid_t
#define __NR32RT_mount                      errno_t
#define __NR32RT_umount                     errno_t
#define __NR32RT_setuid                     errno_t
#define __NR32RT_getuid                     uint16_t
#define __NR32RT_stime                      errno_t
#define __NR32RT_ptrace                     syscall_slong_t
#define __NR32RT_alarm                      syscall_ulong_t
#define __NR32RT_linux_oldfstat             errno_t
#define __NR32RT_pause                      errno_t
#define __NR32RT_utime                      errno_t
#define __NR32RT_access                     errno_t
#define __NR32RT_nice                       errno_t
#define __NR32RT_ftime                      errno_t
#define __NR32RT_sync                       errno_t
#define __NR32RT_kill                       errno_t
#define __NR32RT_rename                     errno_t
#define __NR32RT_mkdir                      errno_t
#define __NR32RT_rmdir                      errno_t
#define __NR32RT_dup                        fd_t
#define __NR32RT_pipe                       errno_t
#define __NR32RT_times                      clock_t
#define __NR32RT_brk                        errno_t
#define __NR32RT_setgid                     errno_t
#define __NR32RT_getgid                     uint16_t
#define __NR32RT_signal                     sighandler_t
#define __NR32RT_geteuid                    uint16_t
#define __NR32RT_getegid                    uint16_t
#define __NR32RT_acct                       errno_t
#define __NR32RT_umount2                    errno_t
#define __NR32RT_ioctl                      syscall_slong_t
#define __NR32RT_fcntl                      syscall_slong_t
#define __NR32RT_setpgid                    errno_t
#define __NR32RT_oldolduname                errno_t
#define __NR32RT_umask                      mode_t
#define __NR32RT_chroot                     errno_t
#define __NR32RT_ustat                      errno_t
#define __NR32RT_dup2                       fd_t
#define __NR32RT_getppid                    pid_t
#define __NR32RT_getpgrp                    pid_t
#define __NR32RT_setsid                     pid_t
#define __NR32RT_sigaction                  errno_t
#define __NR32RT_sgetmask                   syscall_ulong_t
#define __NR32RT_ssetmask                   syscall_ulong_t
#define __NR32RT_setreuid                   errno_t
#define __NR32RT_setregid                   errno_t
#define __NR32RT_sigsuspend                 errno_t
#define __NR32RT_sigpending                 errno_t
#define __NR32RT_sethostname                errno_t
#define __NR32RT_setrlimit                  errno_t
#define __NR32RT_getrlimit                  errno_t
#define __NR32RT_getrusage                  errno_t
#define __NR32RT_gettimeofday               errno_t
#define __NR32RT_settimeofday               errno_t
#define __NR32RT_getgroups                  errno_t
#define __NR32RT_setgroups                  errno_t
#define __NR32RT_select                     ssize_t
#define __NR32RT_symlink                    errno_t
#define __NR32RT_linux_oldlstat             errno_t
#define __NR32RT_readlink                   ssize_t
#define __NR32RT_swapon                     errno_t
#define __NR32RT_reboot                     errno_t
#define __NR32RT_readdir                    errno_t
#define __NR32RT_mmap                       void *
#define __NR32RT_munmap                     errno_t
#define __NR32RT_truncate                   errno_t
#define __NR32RT_ftruncate                  errno_t
#define __NR32RT_fchmod                     errno_t
#define __NR32RT_fchown                     errno_t
#define __NR32RT_getpriority                syscall_slong_t
#define __NR32RT_setpriority                errno_t
#define __NR32RT_profil                     errno_t
#define __NR32RT_statfs                     errno_t
#define __NR32RT_fstatfs                    errno_t
#define __NR32RT_ioperm                     errno_t
#define __NR32RT_socketcall                 errno_t
#define __NR32RT_syslog                     ssize_t
#define __NR32RT_setitimer                  errno_t
#define __NR32RT_getitimer                  errno_t
#define __NR32RT_linux_stat32               errno_t
#define __NR32RT_linux_lstat32              errno_t
#define __NR32RT_linux_fstat32              errno_t
#define __NR32RT_olduname                   errno_t
#define __NR32RT_iopl                       errno_t
#define __NR32RT_vhangup                    errno_t
#define __NR32RT_wait4                      pid_t
#define __NR32RT_swapoff                    errno_t
#define __NR32RT_sysinfo                    errno_t
#define __NR32RT_fsync                      errno_t
#define __NR32RT_sigreturn                  void
#define __NR32RT_clone                      pid_t
#define __NR32RT_setdomainname              errno_t
#define __NR32RT_uname                      errno_t
#define __NR32RT_modify_ldt                 syscall_slong_t
#define __NR32RT_mprotect                   errno_t
#define __NR32RT_sigprocmask                errno_t
#define __NR32RT_getpgid                    pid_t
#define __NR32RT_fchdir                     errno_t
#define __NR32RT_setfsuid                   errno_t
#define __NR32RT_setfsgid                   errno_t
#define __NR32RT__llseek                    errno_t
#define __NR32RT_getdents                   ssize_t
#define __NR32RT_flock                      errno_t
#define __NR32RT_msync                      errno_t
#define __NR32RT_readv                      ssize_t
#define __NR32RT_writev                     ssize_t
#define __NR32RT_getsid                     pid_t
#define __NR32RT_fdatasync                  errno_t
#define __NR32RT_mlock                      errno_t
#define __NR32RT_munlock                    errno_t
#define __NR32RT_mlockall                   errno_t
#define __NR32RT_munlockall                 errno_t
#define __NR32RT_sched_setparam             errno_t
#define __NR32RT_sched_getparam             errno_t
#define __NR32RT_sched_setscheduler         errno_t
#define __NR32RT_sched_getscheduler         syscall_slong_t
#define __NR32RT_sched_yield                errno_t
#define __NR32RT_sched_get_priority_max     syscall_slong_t
#define __NR32RT_sched_get_priority_min     syscall_slong_t
#define __NR32RT_sched_rr_get_interval      errno_t
#define __NR32RT_nanosleep                  errno_t
#define __NR32RT_mremap                     void *
#define __NR32RT_setresuid                  errno_t
#define __NR32RT_getresuid                  errno_t
#define __NR32RT_poll                       ssize_t
#define __NR32RT_setresgid                  errno_t
#define __NR32RT_getresgid                  errno_t
#define __NR32RT_rt_sigaction               errno_t
#define __NR32RT_rt_sigprocmask             errno_t
#define __NR32RT_rt_sigpending              errno_t
#define __NR32RT_rt_sigtimedwait            syscall_slong_t
#define __NR32RT_rt_sigqueueinfo            errno_t
#define __NR32RT_rt_sigsuspend              errno_t
#define __NR32RT_pread64                    ssize_t
#define __NR32RT_pwrite64                   ssize_t
#define __NR32RT_chown                      errno_t
#define __NR32RT_getcwd                     ssize_t
#define __NR32RT_sigaltstack                errno_t
#define __NR32RT_sendfile                   ssize_t
#define __NR32RT_vfork                      pid_t
#define __NR32RT_mmap2                      void *
#define __NR32RT_truncate64                 errno_t
#define __NR32RT_ftruncate64                errno_t
#define __NR32RT_linux_stat64               errno_t
#define __NR32RT_linux_lstat64              errno_t
#define __NR32RT_linux_fstat64              errno_t
#define __NR32RT_lchown32                   errno_t
#define __NR32RT_getuid32                   uint32_t
#define __NR32RT_getgid32                   uint32_t
#define __NR32RT_geteuid32                  uint32_t
#define __NR32RT_getegid32                  uint32_t
#define __NR32RT_setreuid32                 errno_t
#define __NR32RT_setregid32                 errno_t
#define __NR32RT_getgroups32                errno_t
#define __NR32RT_setgroups32                errno_t
#define __NR32RT_fchown32                   errno_t
#define __NR32RT_setresuid32                errno_t
#define __NR32RT_getresuid32                errno_t
#define __NR32RT_setresgid32                errno_t
#define __NR32RT_getresgid32                errno_t
#define __NR32RT_chown32                    errno_t
#define __NR32RT_setuid32                   errno_t
#define __NR32RT_setgid32                   errno_t
#define __NR32RT_setfsuid32                 errno_t
#define __NR32RT_setfsgid32                 errno_t
#define __NR32RT_mincore                    errno_t
#define __NR32RT_madvise                    errno_t
#define __NR32RT_getdents64                 ssize_t
#define __NR32RT_fcntl64                    syscall_slong_t
#define __NR32RT_gettid                     pid_t
#define __NR32RT_readahead                  ssize_t
#define __NR32RT_setxattr                   errno_t
#define __NR32RT_lsetxattr                  errno_t
#define __NR32RT_fsetxattr                  errno_t
#define __NR32RT_getxattr                   ssize_t
#define __NR32RT_lgetxattr                  ssize_t
#define __NR32RT_fgetxattr                  ssize_t
#define __NR32RT_listxattr                  ssize_t
#define __NR32RT_llistxattr                 ssize_t
#define __NR32RT_flistxattr                 ssize_t
#define __NR32RT_removexattr                errno_t
#define __NR32RT_lremovexattr               errno_t
#define __NR32RT_fremovexattr               errno_t
#define __NR32RT_tkill                      errno_t
#define __NR32RT_sendfile64                 ssize_t
#define __NR32RT_futex                      syscall_slong_t
#define __NR32RT_sched_setaffinity          errno_t
#define __NR32RT_sched_getaffinity          errno_t
#define __NR32RT_exit_group                 void
#define __NR32RT_epoll_create               fd_t
#define __NR32RT_epoll_ctl                  errno_t
#define __NR32RT_epoll_wait                 errno_t
#define __NR32RT_remap_file_pages           errno_t
#define __NR32RT_set_tid_address            pid_t
#define __NR32RT_timer_create               errno_t
#define __NR32RT_timer_settime              errno_t
#define __NR32RT_timer_gettime              errno_t
#define __NR32RT_timer_getoverrun           syscall_slong_t
#define __NR32RT_timer_delete               errno_t
#define __NR32RT_clock_settime              errno_t
#define __NR32RT_clock_gettime              errno_t
#define __NR32RT_clock_getres               errno_t
#define __NR32RT_clock_nanosleep            errno_t
#define __NR32RT_statfs64                   errno_t
#define __NR32RT_fstatfs64                  errno_t
#define __NR32RT_tgkill                     errno_t
#define __NR32RT_utimes                     errno_t
#define __NR32RT_waitid                     errno_t
#define __NR32RT_ioprio_set                 errno_t
#define __NR32RT_ioprio_get                 errno_t
#define __NR32RT_openat                     fd_t
#define __NR32RT_mkdirat                    errno_t
#define __NR32RT_mknodat                    errno_t
#define __NR32RT_fchownat                   errno_t
#define __NR32RT_futimesat                  errno_t
#define __NR32RT_linux_fstatat64            errno_t
#define __NR32RT_unlinkat                   errno_t
#define __NR32RT_renameat                   errno_t
#define __NR32RT_linkat                     errno_t
#define __NR32RT_symlinkat                  errno_t
#define __NR32RT_readlinkat                 ssize_t
#define __NR32RT_fchmodat                   errno_t
#define __NR32RT_faccessat                  errno_t
#define __NR32RT_pselect6                   ssize_t
#define __NR32RT_ppoll                      ssize_t
#define __NR32RT_unshare                    errno_t
#define __NR32RT_splice                     ssize_t
#define __NR32RT_sync_file_range            errno_t
#define __NR32RT_tee                        ssize_t
#define __NR32RT_vmsplice                   ssize_t
#define __NR32RT_getcpu                     errno_t
#define __NR32RT_epoll_pwait                errno_t
#define __NR32RT_utimensat                  errno_t
#define __NR32RT_signalfd                   errno_t
#define __NR32RT_timerfd_create             fd_t
#define __NR32RT_eventfd                    fd_t
#define __NR32RT_fallocate                  errno_t
#define __NR32RT_timerfd_settime            errno_t
#define __NR32RT_timerfd_gettime            errno_t
#define __NR32RT_signalfd4                  errno_t
#define __NR32RT_eventfd2                   fd_t
#define __NR32RT_epoll_create1              fd_t
#define __NR32RT_dup3                       fd_t
#define __NR32RT_pipe2                      errno_t
#define __NR32RT_preadv                     ssize_t
#define __NR32RT_pwritev                    ssize_t
#define __NR32RT_rt_tgsigqueueinfo          errno_t
#define __NR32RT_recvmmsg                   ssize_t
#define __NR32RT_prlimit64                  errno_t
#define __NR32RT_name_to_handle_at          errno_t
#define __NR32RT_open_by_handle_at          fd_t
#define __NR32RT_syncfs                     errno_t
#define __NR32RT_sendmmsg                   ssize_t
#define __NR32RT_setns                      errno_t
#define __NR32RT_process_vm_readv           ssize_t
#define __NR32RT_process_vm_writev          ssize_t
#define __NR32RT_kcmp                       syscall_slong_t
#define __NR32RT_renameat2                  errno_t
#define __NR32RT_execveat                   errno_t
#define __NR32RT_socket                     fd_t
#define __NR32RT_socketpair                 errno_t
#define __NR32RT_bind                       errno_t
#define __NR32RT_connect                    errno_t
#define __NR32RT_listen                     errno_t
#define __NR32RT_accept4                    fd_t
#define __NR32RT_getsockopt                 errno_t
#define __NR32RT_setsockopt                 errno_t
#define __NR32RT_getsockname                errno_t
#define __NR32RT_getpeername                errno_t
#define __NR32RT_sendto                     ssize_t
#define __NR32RT_sendmsg                    ssize_t
#define __NR32RT_recvfrom                   ssize_t
#define __NR32RT_recvmsg                    ssize_t
#define __NR32RT_shutdown                   errno_t
#define __NR32RT_hop                        syscall_slong_t
#define __NR32RT_hopf                       syscall_slong_t
#define __NR32RT_readf                      ssize_t
#define __NR32RT_writef                     ssize_t
#define __NR32RT_detach                     errno_t
#define __NR32RT_getdrives                  syscall_slong_t
#define __NR32RT_frealpath4                 ssize_t
#define __NR32RT_frealpathat                ssize_t
#define __NR32RT_rpc_schedule               syscall_slong_t
#define __NR32RT_sysctl                     syscall_slong_t
#define __NR32RT_openpty                    errno_t
#define __NR32RT_fchdirat                   errno_t
#define __NR32RT_time64                     time64_t
#define __NR32RT_set_exception_handler      errno_t
#define __NR32RT_get_exception_handler      errno_t
#define __NR32RT_set_library_listdef        errno_t
#define __NR32RT_debugtrap                  errno_t
#define __NR32RT_lfutex                     syscall_slong_t
#define __NR32RT_lseek64                    int64_t
#define __NR32RT_lfutexlock                 syscall_slong_t
#define __NR32RT_lfutexexpr                 errno_t
#define __NR32RT_lfutexlockexpr             errno_t
#define __NR32RT_mktty                      fd_t
#define __NR32RT_raiseat                    errno_t
#define __NR32RT_stime64                    errno_t
#define __NR32RT_coredump                   errno_t
#define __NR32RT_utime64                    errno_t
#define __NR32RT_ioctlf                     syscall_slong_t
#define __NR32RT_fsmode                     uint64_t
#define __NR32RT_gettimeofday64             errno_t
#define __NR32RT_settimeofday64             errno_t
#define __NR32RT_select64                   ssize_t
#define __NR32RT_maplibrary                 void *
#define __NR32RT_setitimer64                errno_t
#define __NR32RT_getitimer64                errno_t
#define __NR32RT_kreaddir                   ssize_t
#define __NR32RT_readvf                     ssize_t
#define __NR32RT_writevf                    ssize_t
#define __NR32RT_rpc_service                syscall_slong_t
#define __NR32RT_sched_rr_get_interval64    errno_t
#define __NR32RT_nanosleep64                errno_t
#define __NR32RT_rt_sigtimedwait64          syscall_slong_t
#define __NR32RT_pread64f                   ssize_t
#define __NR32RT_pwrite64f                  ssize_t
#define __NR32RT_kstat                      errno_t
#define __NR32RT_klstat                     errno_t
#define __NR32RT_kfstat                     errno_t
#define __NR32RT_kreaddirf                  ssize_t
#define __NR32RT_timer_settime64            errno_t
#define __NR32RT_timer_gettime64            errno_t
#define __NR32RT_clock_settime64            errno_t
#define __NR32RT_clock_gettime64            errno_t
#define __NR32RT_clock_getres64             errno_t
#define __NR32RT_clock_nanosleep64          errno_t
#define __NR32RT_utimes64                   errno_t
#define __NR32RT_fmkdirat                   errno_t
#define __NR32RT_fmknodat                   errno_t
#define __NR32RT_futimesat64                errno_t
#define __NR32RT_kfstatat                   errno_t
#define __NR32RT_frenameat                  errno_t
#define __NR32RT_fsymlinkat                 errno_t
#define __NR32RT_freadlinkat                ssize_t
#define __NR32RT_pselect6_64                ssize_t
#define __NR32RT_ppoll64                    ssize_t
#define __NR32RT_utimensat64                errno_t
#define __NR32RT_fallocate64                errno_t
#define __NR32RT_timerfd_settime64          errno_t
#define __NR32RT_timerfd_gettime64          errno_t
#define __NR32RT_preadvf                    ssize_t
#define __NR32RT_pwritevf                   ssize_t
#define __NR32RT_recvmmsg64                 ssize_t
#endif /* __WANT_SYSCALL_RETURN_TYPES */

#ifdef __WANT_SYSCALL_ARGUMENT_TYPES
#define __NR32AT0_exit                       syscall_ulong_t
#define __NR32AT0_read                       fd_t
#define __NR32AT1_read                       void *
#define __NR32AT2_read                       size_t
#define __NR32AT0_write                      fd_t
#define __NR32AT1_write                      void const *
#define __NR32AT2_write                      size_t
#define __NR32AT0_open                       char const *
#define __NR32AT1_open                       oflag_t
#define __NR32AT2_open                       mode_t
#define __NR32AT0_close                      fd_t
#define __NR32AT0_waitpid                    pid_t
#define __NR32AT1_waitpid                    int32_t *
#define __NR32AT2_waitpid                    syscall_ulong_t
#define __NR32AT0_creat                      char const *
#define __NR32AT1_creat                      mode_t
#define __NR32AT0_link                       char const *
#define __NR32AT1_link                       char const *
#define __NR32AT0_unlink                     char const *
#define __NR32AT0_execve                     char const *
#define __NR32AT1_execve                     char const *const *
#define __NR32AT2_execve                     char const *const *
#define __NR32AT0_chdir                      char const *
#define __NR32AT0_time                       time32_t *
#define __NR32AT0_mknod                      char const *
#define __NR32AT1_mknod                      mode_t
#define __NR32AT2_mknod                      dev_t
#define __NR32AT0_chmod                      char const *
#define __NR32AT1_chmod                      mode_t
#define __NR32AT0_lchown                     char const *
#define __NR32AT1_lchown                     uint16_t
#define __NR32AT2_lchown                     uint16_t
#define __NR32AT0_linux_oldstat              char const *
#define __NR32AT1_linux_oldstat              struct linux_oldstat *
#define __NR32AT0_lseek                      fd_t
#define __NR32AT1_lseek                      int32_t
#define __NR32AT2_lseek                      syscall_ulong_t
#define __NR32AT0_mount                      char const *
#define __NR32AT1_mount                      char const *
#define __NR32AT2_mount                      char const *
#define __NR32AT3_mount                      syscall_ulong_t
#define __NR32AT4_mount                      void const *
#define __NR32AT0_umount                     char const *
#define __NR32AT0_setuid                     uint16_t
#define __NR32AT0_stime                      time32_t const *
#define __NR32AT0_ptrace                     syscall_ulong_t
#define __NR32AT1_ptrace                     pid_t
#define __NR32AT2_ptrace                     void *
#define __NR32AT3_ptrace                     void *
#define __NR32AT0_alarm                      syscall_ulong_t
#define __NR32AT0_linux_oldfstat             fd_t
#define __NR32AT1_linux_oldfstat             struct linux_oldstat *
#define __NR32AT0_utime                      char const *
#define __NR32AT1_utime                      struct __utimbuf32 const *
#define __NR32AT0_access                     char const *
#define __NR32AT1_access                     syscall_ulong_t
#define __NR32AT0_nice                       syscall_slong_t
#define __NR32AT0_ftime                      struct timeb *
#define __NR32AT0_kill                       pid_t
#define __NR32AT1_kill                       syscall_ulong_t
#define __NR32AT0_rename                     char const *
#define __NR32AT1_rename                     char const *
#define __NR32AT0_mkdir                      char const *
#define __NR32AT1_mkdir                      mode_t
#define __NR32AT0_rmdir                      char const *
#define __NR32AT0_dup                        fd_t
#define __NR32AT0_pipe                       /*[2]*/fd_t *
#define __NR32AT0_times                      struct tms *
#define __NR32AT0_brk                        void *
#define __NR32AT0_setgid                     uint16_t
#define __NR32AT0_signal                     syscall_ulong_t
#define __NR32AT1_signal                     sighandler_t
#define __NR32AT0_acct                       char const *
#define __NR32AT0_umount2                    char const *
#define __NR32AT1_umount2                    syscall_ulong_t
#define __NR32AT0_ioctl                      fd_t
#define __NR32AT1_ioctl                      syscall_ulong_t
#define __NR32AT2_ioctl                      void *
#define __NR32AT0_fcntl                      fd_t
#define __NR32AT1_fcntl                      syscall_ulong_t
#define __NR32AT2_fcntl                      void *
#define __NR32AT0_setpgid                    pid_t
#define __NR32AT1_setpgid                    pid_t
#define __NR32AT0_oldolduname                struct linux_oldolduname *
#define __NR32AT0_umask                      mode_t
#define __NR32AT0_chroot                     char const *
#define __NR32AT0_ustat                      dev_t
#define __NR32AT1_ustat                      struct ustat *
#define __NR32AT0_dup2                       fd_t
#define __NR32AT1_dup2                       fd_t
#define __NR32AT0_sigaction                  syscall_ulong_t
#define __NR32AT1_sigaction                  struct sigaction const *
#define __NR32AT2_sigaction                  struct sigaction *
#define __NR32AT0_ssetmask                   syscall_ulong_t
#define __NR32AT0_setreuid                   uint16_t
#define __NR32AT1_setreuid                   uint16_t
#define __NR32AT0_setregid                   uint16_t
#define __NR32AT1_setregid                   uint16_t
#define __NR32AT0_sigsuspend                 struct __sigset_struct const *
#define __NR32AT0_sigpending                 struct __sigset_struct *
#define __NR32AT0_sethostname                char const *
#define __NR32AT1_sethostname                size_t
#define __NR32AT0_setrlimit                  syscall_ulong_t
#define __NR32AT1_setrlimit                  struct rlimit const *
#define __NR32AT0_getrlimit                  syscall_ulong_t
#define __NR32AT1_getrlimit                  struct rlimit *
#define __NR32AT0_getrusage                  syscall_slong_t
#define __NR32AT1_getrusage                  struct rusage *
#define __NR32AT0_gettimeofday               struct __timeval32 *
#define __NR32AT1_gettimeofday               struct timezone *
#define __NR32AT0_settimeofday               struct __timeval32 const *
#define __NR32AT1_settimeofday               struct timezone const *
#define __NR32AT0_getgroups                  size_t
#define __NR32AT1_getgroups                  /*[]*/uint16_t *
#define __NR32AT0_setgroups                  size_t
#define __NR32AT1_setgroups                  uint16_t const *
#define __NR32AT0_select                     size_t
#define __NR32AT1_select                     struct __fd_set_struct *
#define __NR32AT2_select                     struct __fd_set_struct *
#define __NR32AT3_select                     struct __fd_set_struct *
#define __NR32AT4_select                     struct __timeval32 *
#define __NR32AT0_symlink                    char const *
#define __NR32AT1_symlink                    char const *
#define __NR32AT0_linux_oldlstat             char const *
#define __NR32AT1_linux_oldlstat             struct linux_oldstat *
#define __NR32AT0_readlink                   char const *
#define __NR32AT1_readlink                   char *
#define __NR32AT2_readlink                   size_t
#define __NR32AT0_swapon                     char const *
#define __NR32AT1_swapon                     syscall_ulong_t
#define __NR32AT0_reboot                     syscall_ulong_t
#define __NR32AT0_readdir                    fd_t
#define __NR32AT1_readdir                    struct old_linux_dirent *
#define __NR32AT2_readdir                    size_t
#define __NR32AT0_mmap                       void *
#define __NR32AT1_mmap                       size_t
#define __NR32AT2_mmap                       syscall_ulong_t
#define __NR32AT3_mmap                       syscall_ulong_t
#define __NR32AT4_mmap                       fd_t
#define __NR32AT5_mmap                       syscall_ulong_t
#define __NR32AT0_munmap                     void *
#define __NR32AT1_munmap                     size_t
#define __NR32AT0_truncate                   char const *
#define __NR32AT1_truncate                   syscall_ulong_t
#define __NR32AT0_ftruncate                  fd_t
#define __NR32AT1_ftruncate                  syscall_ulong_t
#define __NR32AT0_fchmod                     fd_t
#define __NR32AT1_fchmod                     mode_t
#define __NR32AT0_fchown                     fd_t
#define __NR32AT1_fchown                     uint16_t
#define __NR32AT2_fchown                     uint16_t
#define __NR32AT0_getpriority                syscall_ulong_t
#define __NR32AT1_getpriority                id_t
#define __NR32AT0_setpriority                syscall_ulong_t
#define __NR32AT1_setpriority                id_t
#define __NR32AT2_setpriority                syscall_ulong_t
#define __NR32AT0_profil                     uint16_t *
#define __NR32AT1_profil                     size_t
#define __NR32AT2_profil                     size_t
#define __NR32AT3_profil                     syscall_ulong_t
#define __NR32AT0_statfs                     char const *
#define __NR32AT1_statfs                     struct __statfs32 *
#define __NR32AT0_fstatfs                    fd_t
#define __NR32AT1_fstatfs                    struct __statfs32 *
#define __NR32AT0_ioperm                     syscall_ulong_t
#define __NR32AT1_ioperm                     syscall_ulong_t
#define __NR32AT2_ioperm                     syscall_ulong_t
#define __NR32AT0_socketcall                 int
#define __NR32AT1_socketcall                 unsigned long *
#define __NR32AT0_syslog                     syscall_ulong_t
#define __NR32AT1_syslog                     char const *
#define __NR32AT2_syslog                     size_t
#define __NR32AT0_setitimer                  syscall_ulong_t
#define __NR32AT1_setitimer                  struct __itimerval32 const *
#define __NR32AT2_setitimer                  struct __itimerval32 *
#define __NR32AT0_getitimer                  syscall_ulong_t
#define __NR32AT1_getitimer                  struct __itimerval32 *
#define __NR32AT0_linux_stat32               char const *
#define __NR32AT1_linux_stat32               struct linux_stat32 *
#define __NR32AT0_linux_lstat32              char const *
#define __NR32AT1_linux_lstat32              struct linux_stat32 *
#define __NR32AT0_linux_fstat32              fd_t
#define __NR32AT1_linux_fstat32              struct linux_stat32 *
#define __NR32AT0_olduname                   struct linux_olduname *
#define __NR32AT0_iopl                       syscall_ulong_t
#define __NR32AT0_wait4                      pid_t
#define __NR32AT1_wait4                      int32_t *
#define __NR32AT2_wait4                      syscall_ulong_t
#define __NR32AT3_wait4                      struct rusage *
#define __NR32AT0_swapoff                    char const *
#define __NR32AT0_sysinfo                    struct sysinfo *
#define __NR32AT0_fsync                      fd_t
#define __NR32AT0_sigreturn                  struct fpustate const *
#define __NR32AT1_sigreturn                  syscall_ulong_t
#define __NR32AT2_sigreturn                  syscall_ulong_t
#define __NR32AT3_sigreturn                  struct __sigset_struct const *
#define __NR32AT4_sigreturn                  struct rpc_syscall_info *
#define __NR32AT5_sigreturn                  struct ucpustate const *
#define __NR32AT0_clone                      syscall_ulong_t
#define __NR32AT1_clone                      void *
#define __NR32AT2_clone                      pid_t *
#define __NR32AT3_clone                      uintptr_t
#define __NR32AT4_clone                      pid_t *
#define __NR32AT0_setdomainname              char const *
#define __NR32AT1_setdomainname              size_t
#define __NR32AT0_uname                      struct utsname *
#define __NR32AT0_modify_ldt                 syscall_ulong_t
#define __NR32AT1_modify_ldt                 void *
#define __NR32AT2_modify_ldt                 syscall_ulong_t
#define __NR32AT0_mprotect                   void *
#define __NR32AT1_mprotect                   size_t
#define __NR32AT2_mprotect                   syscall_ulong_t
#define __NR32AT0_sigprocmask                syscall_ulong_t
#define __NR32AT1_sigprocmask                struct __sigset_struct const *
#define __NR32AT2_sigprocmask                struct __sigset_struct *
#define __NR32AT0_getpgid                    pid_t
#define __NR32AT0_fchdir                     fd_t
#define __NR32AT0_setfsuid                   uint16_t
#define __NR32AT0_setfsgid                   uint16_t
#define __NR32AT0__llseek                    fd_t
#define __NR32AT1__llseek                    int64_t
#define __NR32AT2__llseek                    uint64_t *
#define __NR32AT3__llseek                    syscall_ulong_t
#define __NR32AT0_getdents                   fd_t
#define __NR32AT1_getdents                   struct linux_dirent *
#define __NR32AT2_getdents                   size_t
#define __NR32AT0_flock                      fd_t
#define __NR32AT1_flock                      syscall_ulong_t
#define __NR32AT0_msync                      void *
#define __NR32AT1_msync                      size_t
#define __NR32AT2_msync                      syscall_ulong_t
#define __NR32AT0_readv                      fd_t
#define __NR32AT1_readv                      struct iovec const *
#define __NR32AT2_readv                      size_t
#define __NR32AT0_writev                     fd_t
#define __NR32AT1_writev                     struct iovec const *
#define __NR32AT2_writev                     size_t
#define __NR32AT0_getsid                     pid_t
#define __NR32AT0_fdatasync                  fd_t
#define __NR32AT0_mlock                      void const *
#define __NR32AT1_mlock                      size_t
#define __NR32AT0_munlock                    void const *
#define __NR32AT1_munlock                    size_t
#define __NR32AT0_mlockall                   syscall_ulong_t
#define __NR32AT0_sched_setparam             pid_t
#define __NR32AT1_sched_setparam             struct sched_param const *
#define __NR32AT0_sched_getparam             pid_t
#define __NR32AT1_sched_getparam             struct sched_param *
#define __NR32AT0_sched_setscheduler         pid_t
#define __NR32AT1_sched_setscheduler         syscall_ulong_t
#define __NR32AT2_sched_setscheduler         struct sched_param const *
#define __NR32AT0_sched_getscheduler         pid_t
#define __NR32AT0_sched_get_priority_max     syscall_ulong_t
#define __NR32AT0_sched_get_priority_min     syscall_ulong_t
#define __NR32AT0_sched_rr_get_interval      pid_t
#define __NR32AT1_sched_rr_get_interval      struct __timespec32 *
#define __NR32AT0_nanosleep                  struct __timespec32 const *
#define __NR32AT1_nanosleep                  struct __timespec32 *
#define __NR32AT0_mremap                     void *
#define __NR32AT1_mremap                     size_t
#define __NR32AT2_mremap                     size_t
#define __NR32AT3_mremap                     syscall_ulong_t
#define __NR32AT4_mremap                     void *
#define __NR32AT0_setresuid                  uint16_t
#define __NR32AT1_setresuid                  uint16_t
#define __NR32AT2_setresuid                  uint16_t
#define __NR32AT0_getresuid                  uint16_t *
#define __NR32AT1_getresuid                  uint16_t *
#define __NR32AT2_getresuid                  uint16_t *
#define __NR32AT0_poll                       struct pollfd *
#define __NR32AT1_poll                       size_t
#define __NR32AT2_poll                       syscall_slong_t
#define __NR32AT0_setresgid                  uint16_t
#define __NR32AT1_setresgid                  uint16_t
#define __NR32AT2_setresgid                  uint16_t
#define __NR32AT0_getresgid                  uint16_t *
#define __NR32AT1_getresgid                  uint16_t *
#define __NR32AT2_getresgid                  uint16_t *
#define __NR32AT0_rt_sigaction               syscall_ulong_t
#define __NR32AT1_rt_sigaction               struct sigaction const *
#define __NR32AT2_rt_sigaction               struct sigaction *
#define __NR32AT3_rt_sigaction               size_t
#define __NR32AT0_rt_sigprocmask             syscall_ulong_t
#define __NR32AT1_rt_sigprocmask             struct __sigset_struct const *
#define __NR32AT2_rt_sigprocmask             struct __sigset_struct *
#define __NR32AT3_rt_sigprocmask             size_t
#define __NR32AT0_rt_sigpending              struct __sigset_struct *
#define __NR32AT1_rt_sigpending              size_t
#define __NR32AT0_rt_sigtimedwait            struct __sigset_struct const *
#define __NR32AT1_rt_sigtimedwait            struct __siginfo_struct *
#define __NR32AT2_rt_sigtimedwait            struct __timespec32 const *
#define __NR32AT3_rt_sigtimedwait            size_t
#define __NR32AT0_rt_sigqueueinfo            pid_t
#define __NR32AT1_rt_sigqueueinfo            syscall_ulong_t
#define __NR32AT2_rt_sigqueueinfo            struct __siginfo_struct const *
#define __NR32AT0_rt_sigsuspend              struct __sigset_struct const *
#define __NR32AT1_rt_sigsuspend              size_t
#define __NR32AT0_pread64                    fd_t
#define __NR32AT1_pread64                    void *
#define __NR32AT2_pread64                    size_t
#define __NR32AT3_pread64                    uint64_t
#define __NR32AT0_pwrite64                   fd_t
#define __NR32AT1_pwrite64                   void const *
#define __NR32AT2_pwrite64                   size_t
#define __NR32AT3_pwrite64                   uint64_t
#define __NR32AT0_chown                      char const *
#define __NR32AT1_chown                      uint16_t
#define __NR32AT2_chown                      uint16_t
#define __NR32AT0_getcwd                     char *
#define __NR32AT1_getcwd                     size_t
#define __NR32AT0_sigaltstack                struct sigaltstack const *
#define __NR32AT1_sigaltstack                struct sigaltstack *
#define __NR32AT0_sendfile                   fd_t
#define __NR32AT1_sendfile                   fd_t
#define __NR32AT2_sendfile                   syscall_ulong_t *
#define __NR32AT3_sendfile                   size_t
#define __NR32AT0_mmap2                      void *
#define __NR32AT1_mmap2                      size_t
#define __NR32AT2_mmap2                      syscall_ulong_t
#define __NR32AT3_mmap2                      syscall_ulong_t
#define __NR32AT4_mmap2                      fd_t
#define __NR32AT5_mmap2                      syscall_ulong_t
#define __NR32AT0_truncate64                 char const *
#define __NR32AT1_truncate64                 uint64_t
#define __NR32AT0_ftruncate64                fd_t
#define __NR32AT1_ftruncate64                uint64_t
#define __NR32AT0_linux_stat64               char const *
#define __NR32AT1_linux_stat64               struct linux_stat64 *
#define __NR32AT0_linux_lstat64              char const *
#define __NR32AT1_linux_lstat64              struct linux_stat64 *
#define __NR32AT0_linux_fstat64              fd_t
#define __NR32AT1_linux_fstat64              struct linux_stat64 *
#define __NR32AT0_lchown32                   char const *
#define __NR32AT1_lchown32                   uint32_t
#define __NR32AT2_lchown32                   uint32_t
#define __NR32AT0_setreuid32                 uint32_t
#define __NR32AT1_setreuid32                 uint32_t
#define __NR32AT0_setregid32                 uint32_t
#define __NR32AT1_setregid32                 uint32_t
#define __NR32AT0_getgroups32                size_t
#define __NR32AT1_getgroups32                /*[]*/uint32_t *
#define __NR32AT0_setgroups32                size_t
#define __NR32AT1_setgroups32                uint32_t const *
#define __NR32AT0_fchown32                   fd_t
#define __NR32AT1_fchown32                   uint32_t
#define __NR32AT2_fchown32                   uint32_t
#define __NR32AT0_setresuid32                uint32_t
#define __NR32AT1_setresuid32                uint32_t
#define __NR32AT2_setresuid32                uint32_t
#define __NR32AT0_getresuid32                uint32_t *
#define __NR32AT1_getresuid32                uint32_t *
#define __NR32AT2_getresuid32                uint32_t *
#define __NR32AT0_setresgid32                uint32_t
#define __NR32AT1_setresgid32                uint32_t
#define __NR32AT2_setresgid32                uint32_t
#define __NR32AT0_getresgid32                uint32_t *
#define __NR32AT1_getresgid32                uint32_t *
#define __NR32AT2_getresgid32                uint32_t *
#define __NR32AT0_chown32                    char const *
#define __NR32AT1_chown32                    uint32_t
#define __NR32AT2_chown32                    uint32_t
#define __NR32AT0_setuid32                   uint32_t
#define __NR32AT0_setgid32                   uint32_t
#define __NR32AT0_setfsuid32                 uint32_t
#define __NR32AT0_setfsgid32                 uint32_t
#define __NR32AT0_mincore                    void *
#define __NR32AT1_mincore                    size_t
#define __NR32AT2_mincore                    uint8_t *
#define __NR32AT0_madvise                    void *
#define __NR32AT1_madvise                    size_t
#define __NR32AT2_madvise                    syscall_ulong_t
#define __NR32AT0_getdents64                 fd_t
#define __NR32AT1_getdents64                 struct linux_dirent64 *
#define __NR32AT2_getdents64                 size_t
#define __NR32AT0_fcntl64                    fd_t
#define __NR32AT1_fcntl64                    syscall_ulong_t
#define __NR32AT2_fcntl64                    void *
#define __NR32AT0_readahead                  fd_t
#define __NR32AT1_readahead                  uint64_t
#define __NR32AT2_readahead                  size_t
#define __NR32AT0_setxattr                   char const *
#define __NR32AT1_setxattr                   char const *
#define __NR32AT2_setxattr                   void const *
#define __NR32AT3_setxattr                   size_t
#define __NR32AT4_setxattr                   syscall_ulong_t
#define __NR32AT0_lsetxattr                  char const *
#define __NR32AT1_lsetxattr                  char const *
#define __NR32AT2_lsetxattr                  void const *
#define __NR32AT3_lsetxattr                  size_t
#define __NR32AT4_lsetxattr                  syscall_ulong_t
#define __NR32AT0_fsetxattr                  fd_t
#define __NR32AT1_fsetxattr                  char const *
#define __NR32AT2_fsetxattr                  void const *
#define __NR32AT3_fsetxattr                  size_t
#define __NR32AT4_fsetxattr                  syscall_ulong_t
#define __NR32AT0_getxattr                   char const *
#define __NR32AT1_getxattr                   char const *
#define __NR32AT2_getxattr                   void *
#define __NR32AT3_getxattr                   size_t
#define __NR32AT0_lgetxattr                  char const *
#define __NR32AT1_lgetxattr                  char const *
#define __NR32AT2_lgetxattr                  void *
#define __NR32AT3_lgetxattr                  size_t
#define __NR32AT0_fgetxattr                  fd_t
#define __NR32AT1_fgetxattr                  char const *
#define __NR32AT2_fgetxattr                  void *
#define __NR32AT3_fgetxattr                  size_t
#define __NR32AT0_listxattr                  char const *
#define __NR32AT1_listxattr                  char *
#define __NR32AT2_listxattr                  size_t
#define __NR32AT0_llistxattr                 char const *
#define __NR32AT1_llistxattr                 char *
#define __NR32AT2_llistxattr                 size_t
#define __NR32AT0_flistxattr                 fd_t
#define __NR32AT1_flistxattr                 char *
#define __NR32AT2_flistxattr                 size_t
#define __NR32AT0_removexattr                char const *
#define __NR32AT1_removexattr                char const *
#define __NR32AT0_lremovexattr               char const *
#define __NR32AT1_lremovexattr               char const *
#define __NR32AT0_fremovexattr               int
#define __NR32AT1_fremovexattr               char const *
#define __NR32AT0_tkill                      pid_t
#define __NR32AT1_tkill                      syscall_ulong_t
#define __NR32AT0_sendfile64                 fd_t
#define __NR32AT1_sendfile64                 fd_t
#define __NR32AT2_sendfile64                 uint64_t *
#define __NR32AT3_sendfile64                 size_t
#define __NR32AT0_futex                      uint32_t *
#define __NR32AT1_futex                      syscall_ulong_t
#define __NR32AT2_futex                      uint32_t
#define __NR32AT3_futex                      struct __timespec32 const *
#define __NR32AT4_futex                      uint32_t *
#define __NR32AT5_futex                      uint32_t
#define __NR32AT0_sched_setaffinity          pid_t
#define __NR32AT1_sched_setaffinity          size_t
#define __NR32AT2_sched_setaffinity          struct __cpu_set_struct const *
#define __NR32AT0_sched_getaffinity          pid_t
#define __NR32AT1_sched_getaffinity          size_t
#define __NR32AT2_sched_getaffinity          struct __cpu_set_struct *
#define __NR32AT0_exit_group                 syscall_ulong_t
#define __NR32AT0_epoll_create               syscall_ulong_t
#define __NR32AT0_epoll_ctl                  fd_t
#define __NR32AT1_epoll_ctl                  syscall_ulong_t
#define __NR32AT2_epoll_ctl                  fd_t
#define __NR32AT3_epoll_ctl                  struct epoll_event *
#define __NR32AT0_epoll_wait                 fd_t
#define __NR32AT1_epoll_wait                 struct epoll_event *
#define __NR32AT2_epoll_wait                 syscall_ulong_t
#define __NR32AT3_epoll_wait                 syscall_slong_t
#define __NR32AT0_remap_file_pages           void *
#define __NR32AT1_remap_file_pages           size_t
#define __NR32AT2_remap_file_pages           syscall_ulong_t
#define __NR32AT3_remap_file_pages           size_t
#define __NR32AT4_remap_file_pages           syscall_ulong_t
#define __NR32AT0_set_tid_address            pid_t *
#define __NR32AT0_timer_create               clockid_t
#define __NR32AT1_timer_create               struct sigevent *
#define __NR32AT2_timer_create               timer_t *
#define __NR32AT0_timer_settime              timer_t
#define __NR32AT1_timer_settime              syscall_ulong_t
#define __NR32AT2_timer_settime              struct __itimerspec32 const *
#define __NR32AT3_timer_settime              struct __itimerspec32 *
#define __NR32AT0_timer_gettime              timer_t
#define __NR32AT1_timer_gettime              struct __itimerspec32 *
#define __NR32AT0_timer_getoverrun           timer_t
#define __NR32AT0_timer_delete               timer_t
#define __NR32AT0_clock_settime              clockid_t
#define __NR32AT1_clock_settime              struct __timespec32 const *
#define __NR32AT0_clock_gettime              clockid_t
#define __NR32AT1_clock_gettime              struct __timespec32 *
#define __NR32AT0_clock_getres               clockid_t
#define __NR32AT1_clock_getres               struct __timespec32 *
#define __NR32AT0_clock_nanosleep            clockid_t
#define __NR32AT1_clock_nanosleep            syscall_ulong_t
#define __NR32AT2_clock_nanosleep            struct __timespec32 const *
#define __NR32AT3_clock_nanosleep            struct __timespec32 *
#define __NR32AT0_statfs64                   char const *
#define __NR32AT1_statfs64                   struct statfs64 *
#define __NR32AT0_fstatfs64                  fd_t
#define __NR32AT1_fstatfs64                  struct statfs64 *
#define __NR32AT0_tgkill                     pid_t
#define __NR32AT1_tgkill                     pid_t
#define __NR32AT2_tgkill                     syscall_ulong_t
#define __NR32AT0_utimes                     char const *
#define __NR32AT1_utimes                     /*[2]*/struct __timeval32 const *
#define __NR32AT0_waitid                     idtype_t
#define __NR32AT1_waitid                     id_t
#define __NR32AT2_waitid                     struct __siginfo_struct *
#define __NR32AT3_waitid                     syscall_ulong_t
#define __NR32AT4_waitid                     struct rusage *
#define __NR32AT0_ioprio_set                 syscall_ulong_t
#define __NR32AT1_ioprio_set                 syscall_ulong_t
#define __NR32AT2_ioprio_set                 syscall_ulong_t
#define __NR32AT0_ioprio_get                 syscall_ulong_t
#define __NR32AT1_ioprio_get                 syscall_ulong_t
#define __NR32AT0_openat                     fd_t
#define __NR32AT1_openat                     char const *
#define __NR32AT2_openat                     oflag_t
#define __NR32AT3_openat                     mode_t
#define __NR32AT0_mkdirat                    fd_t
#define __NR32AT1_mkdirat                    char const *
#define __NR32AT2_mkdirat                    mode_t
#define __NR32AT0_mknodat                    fd_t
#define __NR32AT1_mknodat                    char const *
#define __NR32AT2_mknodat                    mode_t
#define __NR32AT3_mknodat                    dev_t
#define __NR32AT0_fchownat                   fd_t
#define __NR32AT1_fchownat                   char const *
#define __NR32AT2_fchownat                   uint32_t
#define __NR32AT3_fchownat                   uint32_t
#define __NR32AT4_fchownat                   atflag_t
#define __NR32AT0_futimesat                  fd_t
#define __NR32AT1_futimesat                  const char *
#define __NR32AT2_futimesat                  /*[2]*/struct __timeval32 const *
#define __NR32AT0_linux_fstatat64            fd_t
#define __NR32AT1_linux_fstatat64            char const *
#define __NR32AT2_linux_fstatat64            struct linux_stat64 *
#define __NR32AT3_linux_fstatat64            atflag_t
#define __NR32AT0_unlinkat                   fd_t
#define __NR32AT1_unlinkat                   char const *
#define __NR32AT2_unlinkat                   atflag_t
#define __NR32AT0_renameat                   fd_t
#define __NR32AT1_renameat                   char const *
#define __NR32AT2_renameat                   fd_t
#define __NR32AT3_renameat                   char const *
#define __NR32AT0_linkat                     fd_t
#define __NR32AT1_linkat                     char const *
#define __NR32AT2_linkat                     fd_t
#define __NR32AT3_linkat                     char const *
#define __NR32AT4_linkat                     atflag_t
#define __NR32AT0_symlinkat                  char const *
#define __NR32AT1_symlinkat                  fd_t
#define __NR32AT2_symlinkat                  char const *
#define __NR32AT0_readlinkat                 fd_t
#define __NR32AT1_readlinkat                 char const *
#define __NR32AT2_readlinkat                 char *
#define __NR32AT3_readlinkat                 size_t
#define __NR32AT0_fchmodat                   fd_t
#define __NR32AT1_fchmodat                   char const *
#define __NR32AT2_fchmodat                   mode_t
#define __NR32AT3_fchmodat                   atflag_t
#define __NR32AT0_faccessat                  fd_t
#define __NR32AT1_faccessat                  char const *
#define __NR32AT2_faccessat                  syscall_ulong_t
#define __NR32AT3_faccessat                  atflag_t
#define __NR32AT0_pselect6                   size_t
#define __NR32AT1_pselect6                   struct __fd_set_struct *
#define __NR32AT2_pselect6                   struct __fd_set_struct *
#define __NR32AT3_pselect6                   struct __fd_set_struct *
#define __NR32AT4_pselect6                   struct __timespec32 const *
#define __NR32AT5_pselect6                   void const *
#define __NR32AT0_ppoll                      struct pollfd *
#define __NR32AT1_ppoll                      size_t
#define __NR32AT2_ppoll                      struct __timespec32 const *
#define __NR32AT3_ppoll                      struct __sigset_struct const *
#define __NR32AT4_ppoll                      size_t
#define __NR32AT0_unshare                    syscall_ulong_t
#define __NR32AT0_splice                     fd_t
#define __NR32AT1_splice                     uint64_t *
#define __NR32AT2_splice                     fd_t
#define __NR32AT3_splice                     uint64_t *
#define __NR32AT4_splice                     size_t
#define __NR32AT5_splice                     syscall_ulong_t
#define __NR32AT0_sync_file_range            fd_t
#define __NR32AT1_sync_file_range            uint64_t
#define __NR32AT2_sync_file_range            uint64_t
#define __NR32AT3_sync_file_range            syscall_ulong_t
#define __NR32AT0_tee                        fd_t
#define __NR32AT1_tee                        fd_t
#define __NR32AT2_tee                        size_t
#define __NR32AT3_tee                        syscall_ulong_t
#define __NR32AT0_vmsplice                   fd_t
#define __NR32AT1_vmsplice                   struct iovec const *
#define __NR32AT2_vmsplice                   size_t
#define __NR32AT3_vmsplice                   syscall_ulong_t
#define __NR32AT0_getcpu                     uint32_t *
#define __NR32AT1_getcpu                     uint32_t *
#define __NR32AT2_getcpu                     struct getcpu_cache *
#define __NR32AT0_epoll_pwait                fd_t
#define __NR32AT1_epoll_pwait                struct epoll_event *
#define __NR32AT2_epoll_pwait                syscall_ulong_t
#define __NR32AT3_epoll_pwait                syscall_slong_t
#define __NR32AT4_epoll_pwait                struct __sigset_struct const *
#define __NR32AT0_utimensat                  fd_t
#define __NR32AT1_utimensat                  char const *
#define __NR32AT2_utimensat                  /*[2-3]*/struct __timespec32 const *
#define __NR32AT3_utimensat                  atflag_t
#define __NR32AT0_signalfd                   fd_t
#define __NR32AT1_signalfd                   struct __sigset_struct const *
#define __NR32AT2_signalfd                   size_t
#define __NR32AT0_timerfd_create             clockid_t
#define __NR32AT1_timerfd_create             syscall_ulong_t
#define __NR32AT0_eventfd                    syscall_ulong_t
#define __NR32AT0_fallocate                  fd_t
#define __NR32AT1_fallocate                  syscall_ulong_t
#define __NR32AT2_fallocate                  uint32_t
#define __NR32AT3_fallocate                  uint32_t
#define __NR32AT0_timerfd_settime            fd_t
#define __NR32AT1_timerfd_settime            syscall_ulong_t
#define __NR32AT2_timerfd_settime            struct __itimerspec32 const *
#define __NR32AT3_timerfd_settime            struct __itimerspec32 *
#define __NR32AT0_timerfd_gettime            fd_t
#define __NR32AT1_timerfd_gettime            struct __itimerspec32 *
#define __NR32AT0_signalfd4                  fd_t
#define __NR32AT1_signalfd4                  struct __sigset_struct const *
#define __NR32AT2_signalfd4                  size_t
#define __NR32AT3_signalfd4                  syscall_ulong_t
#define __NR32AT0_eventfd2                   syscall_ulong_t
#define __NR32AT1_eventfd2                   syscall_ulong_t
#define __NR32AT0_epoll_create1              syscall_ulong_t
#define __NR32AT0_dup3                       fd_t
#define __NR32AT1_dup3                       fd_t
#define __NR32AT2_dup3                       oflag_t
#define __NR32AT0_pipe2                      /*[2]*/fd_t *
#define __NR32AT1_pipe2                      oflag_t
#define __NR32AT0_preadv                     fd_t
#define __NR32AT1_preadv                     struct iovec const *
#define __NR32AT2_preadv                     size_t
#define __NR32AT3_preadv                     uint64_t
#define __NR32AT0_pwritev                    fd_t
#define __NR32AT1_pwritev                    struct iovec const *
#define __NR32AT2_pwritev                    size_t
#define __NR32AT3_pwritev                    uint64_t
#define __NR32AT0_rt_tgsigqueueinfo          pid_t
#define __NR32AT1_rt_tgsigqueueinfo          pid_t
#define __NR32AT2_rt_tgsigqueueinfo          syscall_ulong_t
#define __NR32AT3_rt_tgsigqueueinfo          struct __siginfo_struct const *
#define __NR32AT0_recvmmsg                   fd_t
#define __NR32AT1_recvmmsg                   struct mmsghdr *
#define __NR32AT2_recvmmsg                   size_t
#define __NR32AT3_recvmmsg                   syscall_ulong_t
#define __NR32AT4_recvmmsg                   struct __timespec32 *
#define __NR32AT0_prlimit64                  pid_t
#define __NR32AT1_prlimit64                  syscall_ulong_t
#define __NR32AT2_prlimit64                  struct rlimit64 const *
#define __NR32AT3_prlimit64                  struct rlimit64 *
#define __NR32AT0_name_to_handle_at          fd_t
#define __NR32AT1_name_to_handle_at          char const *
#define __NR32AT2_name_to_handle_at          struct file_handle *
#define __NR32AT3_name_to_handle_at          int32_t *
#define __NR32AT4_name_to_handle_at          syscall_ulong_t
#define __NR32AT0_open_by_handle_at          fd_t
#define __NR32AT1_open_by_handle_at          struct file_handle *
#define __NR32AT2_open_by_handle_at          syscall_ulong_t
#define __NR32AT0_syncfs                     fd_t
#define __NR32AT0_sendmmsg                   fd_t
#define __NR32AT1_sendmmsg                   struct mmsghdr *
#define __NR32AT2_sendmmsg                   size_t
#define __NR32AT3_sendmmsg                   syscall_ulong_t
#define __NR32AT0_setns                      fd_t
#define __NR32AT1_setns                      syscall_ulong_t
#define __NR32AT0_process_vm_readv           pid_t
#define __NR32AT1_process_vm_readv           struct iovec const *
#define __NR32AT2_process_vm_readv           size_t
#define __NR32AT3_process_vm_readv           struct iovec const *
#define __NR32AT4_process_vm_readv           size_t
#define __NR32AT5_process_vm_readv           syscall_ulong_t
#define __NR32AT0_process_vm_writev          pid_t
#define __NR32AT1_process_vm_writev          struct iovec const *
#define __NR32AT2_process_vm_writev          size_t
#define __NR32AT3_process_vm_writev          struct iovec const *
#define __NR32AT4_process_vm_writev          size_t
#define __NR32AT5_process_vm_writev          syscall_ulong_t
#define __NR32AT0_kcmp                       pid_t
#define __NR32AT1_kcmp                       pid_t
#define __NR32AT2_kcmp                       syscall_ulong_t
#define __NR32AT3_kcmp                       syscall_ulong_t
#define __NR32AT4_kcmp                       syscall_ulong_t
#define __NR32AT0_renameat2                  fd_t
#define __NR32AT1_renameat2                  char const *
#define __NR32AT2_renameat2                  fd_t
#define __NR32AT3_renameat2                  char const *
#define __NR32AT4_renameat2                  syscall_ulong_t
#define __NR32AT0_execveat                   fd_t
#define __NR32AT1_execveat                   char const *
#define __NR32AT2_execveat                   char const *const *
#define __NR32AT3_execveat                   char const *const *
#define __NR32AT4_execveat                   atflag_t
#define __NR32AT0_socket                     syscall_ulong_t
#define __NR32AT1_socket                     syscall_ulong_t
#define __NR32AT2_socket                     syscall_ulong_t
#define __NR32AT0_socketpair                 syscall_ulong_t
#define __NR32AT1_socketpair                 syscall_ulong_t
#define __NR32AT2_socketpair                 syscall_ulong_t
#define __NR32AT3_socketpair                 /*[2]*/fd_t *
#define __NR32AT0_bind                       fd_t
#define __NR32AT1_bind                       struct sockaddr const *
#define __NR32AT2_bind                       socklen_t
#define __NR32AT0_connect                    fd_t
#define __NR32AT1_connect                    struct sockaddr const *
#define __NR32AT2_connect                    socklen_t
#define __NR32AT0_listen                     fd_t
#define __NR32AT1_listen                     syscall_ulong_t
#define __NR32AT0_accept4                    fd_t
#define __NR32AT1_accept4                    struct sockaddr *
#define __NR32AT2_accept4                    socklen_t *
#define __NR32AT3_accept4                    syscall_ulong_t
#define __NR32AT0_getsockopt                 fd_t
#define __NR32AT1_getsockopt                 syscall_ulong_t
#define __NR32AT2_getsockopt                 syscall_ulong_t
#define __NR32AT3_getsockopt                 void *
#define __NR32AT4_getsockopt                 socklen_t *
#define __NR32AT0_setsockopt                 fd_t
#define __NR32AT1_setsockopt                 syscall_ulong_t
#define __NR32AT2_setsockopt                 syscall_ulong_t
#define __NR32AT3_setsockopt                 void const *
#define __NR32AT4_setsockopt                 socklen_t
#define __NR32AT0_getsockname                fd_t
#define __NR32AT1_getsockname                struct sockaddr *
#define __NR32AT2_getsockname                socklen_t *
#define __NR32AT0_getpeername                fd_t
#define __NR32AT1_getpeername                struct sockaddr *
#define __NR32AT2_getpeername                socklen_t *
#define __NR32AT0_sendto                     fd_t
#define __NR32AT1_sendto                     void const *
#define __NR32AT2_sendto                     size_t
#define __NR32AT3_sendto                     syscall_ulong_t
#define __NR32AT4_sendto                     struct sockaddr const *
#define __NR32AT5_sendto                     socklen_t
#define __NR32AT0_sendmsg                    fd_t
#define __NR32AT1_sendmsg                    struct msghdr const *
#define __NR32AT2_sendmsg                    syscall_ulong_t
#define __NR32AT0_recvfrom                   fd_t
#define __NR32AT1_recvfrom                   void *
#define __NR32AT2_recvfrom                   size_t
#define __NR32AT3_recvfrom                   syscall_ulong_t
#define __NR32AT4_recvfrom                   struct sockaddr *
#define __NR32AT5_recvfrom                   socklen_t *
#define __NR32AT0_recvmsg                    fd_t
#define __NR32AT1_recvmsg                    struct msghdr *
#define __NR32AT2_recvmsg                    syscall_ulong_t
#define __NR32AT0_shutdown                   fd_t
#define __NR32AT1_shutdown                   syscall_ulong_t
#define __NR32AT0_hop                        fd_t
#define __NR32AT1_hop                        syscall_ulong_t
#define __NR32AT2_hop                        void *
#define __NR32AT0_hopf                       fd_t
#define __NR32AT1_hopf                       syscall_ulong_t
#define __NR32AT2_hopf                       iomode_t
#define __NR32AT3_hopf                       void *
#define __NR32AT0_readf                      fd_t
#define __NR32AT1_readf                      void *
#define __NR32AT2_readf                      size_t
#define __NR32AT3_readf                      iomode_t
#define __NR32AT0_writef                     fd_t
#define __NR32AT1_writef                     void const *
#define __NR32AT2_writef                     size_t
#define __NR32AT3_writef                     iomode_t
#define __NR32AT0_detach                     pid_t
#define __NR32AT0_frealpath4                 fd_t
#define __NR32AT1_frealpath4                 char *
#define __NR32AT2_frealpath4                 size_t
#define __NR32AT3_frealpath4                 atflag_t
#define __NR32AT0_frealpathat                fd_t
#define __NR32AT1_frealpathat                char const *
#define __NR32AT2_frealpathat                char *
#define __NR32AT3_frealpathat                size_t
#define __NR32AT4_frealpathat                atflag_t
#define __NR32AT0_rpc_schedule               pid_t
#define __NR32AT1_rpc_schedule               syscall_ulong_t
#define __NR32AT2_rpc_schedule               uint8_t const *
#define __NR32AT3_rpc_schedule               void **
#define __NR32AT0_sysctl                     syscall_ulong_t
#define __NR32AT1_sysctl                     void *
#define __NR32AT0_openpty                    fd_t *
#define __NR32AT1_openpty                    fd_t *
#define __NR32AT2_openpty                    char *
#define __NR32AT3_openpty                    struct termios const *
#define __NR32AT4_openpty                    struct winsize const *
#define __NR32AT0_fchdirat                   fd_t
#define __NR32AT1_fchdirat                   char const *
#define __NR32AT2_fchdirat                   atflag_t
#define __NR32AT0_time64                     time64_t *
#define __NR32AT0_set_exception_handler      syscall_ulong_t
#define __NR32AT1_set_exception_handler      except_handler_t
#define __NR32AT2_set_exception_handler      void *
#define __NR32AT0_get_exception_handler      syscall_ulong_t *
#define __NR32AT1_get_exception_handler      except_handler_t *
#define __NR32AT2_get_exception_handler      void **
#define __NR32AT0_set_library_listdef        struct library_listdef const *
#define __NR32AT0_debugtrap                  struct ucpustate const *
#define __NR32AT1_debugtrap                  struct debugtrap_reason const *
#define __NR32AT0_lfutex                     uintptr_t *
#define __NR32AT1_lfutex                     syscall_ulong_t
#define __NR32AT2_lfutex                     uintptr_t
#define __NR32AT3_lfutex                     struct __timespec64 const *
#define __NR32AT4_lfutex                     uintptr_t
#define __NR32AT0_lseek64                    fd_t
#define __NR32AT1_lseek64                    int64_t
#define __NR32AT2_lseek64                    syscall_ulong_t
#define __NR32AT0_lfutexlock                 uintptr_t *
#define __NR32AT1_lfutexlock                 uintptr_t *
#define __NR32AT2_lfutexlock                 syscall_ulong_t
#define __NR32AT3_lfutexlock                 uintptr_t
#define __NR32AT4_lfutexlock                 struct __timespec64 const *
#define __NR32AT5_lfutexlock                 uintptr_t
#define __NR32AT0_lfutexexpr                 uintptr_t *
#define __NR32AT1_lfutexexpr                 void *
#define __NR32AT2_lfutexexpr                 struct lfutexexpr const *
#define __NR32AT3_lfutexexpr                 size_t
#define __NR32AT4_lfutexexpr                 struct __timespec64 const *
#define __NR32AT5_lfutexexpr                 syscall_ulong_t
#define __NR32AT0_lfutexlockexpr             uintptr_t *
#define __NR32AT1_lfutexlockexpr             void *
#define __NR32AT2_lfutexlockexpr             struct lfutexexpr const *
#define __NR32AT3_lfutexlockexpr             size_t
#define __NR32AT4_lfutexlockexpr             struct __timespec64 const *
#define __NR32AT5_lfutexlockexpr             syscall_ulong_t
#define __NR32AT0_mktty                      fd_t
#define __NR32AT1_mktty                      fd_t
#define __NR32AT2_mktty                      char const *
#define __NR32AT3_mktty                      syscall_ulong_t
#define __NR32AT0_raiseat                    struct ucpustate const *
#define __NR32AT1_raiseat                    struct __siginfo_struct const *
#define __NR32AT0_stime64                    time64_t const *
#define __NR32AT0_coredump                   struct ucpustate const *
#define __NR32AT1_coredump                   struct ucpustate const *
#define __NR32AT2_coredump                   void const *const *
#define __NR32AT3_coredump                   size_t
#define __NR32AT4_coredump                   struct exception_data const *
#define __NR32AT5_coredump                   syscall_ulong_t
#define __NR32AT0_utime64                    char const *
#define __NR32AT1_utime64                    struct utimbuf64 const *
#define __NR32AT0_ioctlf                     fd_t
#define __NR32AT1_ioctlf                     syscall_ulong_t
#define __NR32AT2_ioctlf                     iomode_t
#define __NR32AT3_ioctlf                     void *
#define __NR32AT0_fsmode                     uint64_t
#define __NR32AT0_gettimeofday64             struct __timeval64 *
#define __NR32AT1_gettimeofday64             struct timezone *
#define __NR32AT0_settimeofday64             struct __timeval64 const *
#define __NR32AT1_settimeofday64             struct timezone const *
#define __NR32AT0_select64                   size_t
#define __NR32AT1_select64                   struct __fd_set_struct *
#define __NR32AT2_select64                   struct __fd_set_struct *
#define __NR32AT3_select64                   struct __fd_set_struct *
#define __NR32AT4_select64                   struct __timeval64 *
#define __NR32AT0_maplibrary                 void *
#define __NR32AT1_maplibrary                 syscall_ulong_t
#define __NR32AT2_maplibrary                 fd_t
#define __NR32AT3_maplibrary                 void *
#define __NR32AT4_maplibrary                 size_t
#define __NR32AT0_setitimer64                syscall_ulong_t
#define __NR32AT1_setitimer64                struct __itimerval64 const *
#define __NR32AT2_setitimer64                struct __itimerval64 *
#define __NR32AT0_getitimer64                syscall_ulong_t
#define __NR32AT1_getitimer64                struct __itimerval64 *
#define __NR32AT0_kreaddir                   fd_t
#define __NR32AT1_kreaddir                   struct dirent *
#define __NR32AT2_kreaddir                   size_t
#define __NR32AT3_kreaddir                   syscall_ulong_t
#define __NR32AT0_readvf                     fd_t
#define __NR32AT1_readvf                     struct iovec const *
#define __NR32AT2_readvf                     size_t
#define __NR32AT3_readvf                     iomode_t
#define __NR32AT0_writevf                    fd_t
#define __NR32AT1_writevf                    struct iovec const *
#define __NR32AT2_writevf                    size_t
#define __NR32AT3_writevf                    iomode_t
#define __NR32AT0_sched_rr_get_interval64    pid_t
#define __NR32AT1_sched_rr_get_interval64    struct __timespec64 *
#define __NR32AT0_nanosleep64                struct __timespec64 const *
#define __NR32AT1_nanosleep64                struct __timespec64 *
#define __NR32AT0_rt_sigtimedwait64          struct __sigset_struct const *
#define __NR32AT1_rt_sigtimedwait64          struct __siginfo_struct *
#define __NR32AT2_rt_sigtimedwait64          struct __timespec64 const *
#define __NR32AT3_rt_sigtimedwait64          size_t
#define __NR32AT0_pread64f                   fd_t
#define __NR32AT1_pread64f                   void *
#define __NR32AT2_pread64f                   size_t
#define __NR32AT3_pread64f                   uint64_t
#define __NR32AT4_pread64f                   iomode_t
#define __NR32AT0_pwrite64f                  fd_t
#define __NR32AT1_pwrite64f                  void const *
#define __NR32AT2_pwrite64f                  size_t
#define __NR32AT3_pwrite64f                  uint64_t
#define __NR32AT4_pwrite64f                  iomode_t
#define __NR32AT0_kstat                      char const *
#define __NR32AT1_kstat                      struct stat *
#define __NR32AT0_klstat                     char const *
#define __NR32AT1_klstat                     struct stat *
#define __NR32AT0_kfstat                     fd_t
#define __NR32AT1_kfstat                     struct stat *
#define __NR32AT0_kreaddirf                  fd_t
#define __NR32AT1_kreaddirf                  struct dirent *
#define __NR32AT2_kreaddirf                  size_t
#define __NR32AT3_kreaddirf                  syscall_ulong_t
#define __NR32AT4_kreaddirf                  iomode_t
#define __NR32AT0_timer_settime64            timer_t
#define __NR32AT1_timer_settime64            syscall_ulong_t
#define __NR32AT2_timer_settime64            struct __itimerspec64 const *
#define __NR32AT3_timer_settime64            struct __itimerspec64 *
#define __NR32AT0_timer_gettime64            timer_t
#define __NR32AT1_timer_gettime64            struct __itimerspec64 *
#define __NR32AT0_clock_settime64            clockid_t
#define __NR32AT1_clock_settime64            struct __timespec64 const *
#define __NR32AT0_clock_gettime64            clockid_t
#define __NR32AT1_clock_gettime64            struct __timespec64 *
#define __NR32AT0_clock_getres64             clockid_t
#define __NR32AT1_clock_getres64             struct __timespec64 *
#define __NR32AT0_clock_nanosleep64          clockid_t
#define __NR32AT1_clock_nanosleep64          syscall_ulong_t
#define __NR32AT2_clock_nanosleep64          struct __timespec64 const *
#define __NR32AT3_clock_nanosleep64          struct __timespec64 *
#define __NR32AT0_utimes64                   char const *
#define __NR32AT1_utimes64                   /*[2]*/struct __timeval64 const *
#define __NR32AT0_fmkdirat                   fd_t
#define __NR32AT1_fmkdirat                   char const *
#define __NR32AT2_fmkdirat                   mode_t
#define __NR32AT3_fmkdirat                   atflag_t
#define __NR32AT0_fmknodat                   fd_t
#define __NR32AT1_fmknodat                   char const *
#define __NR32AT2_fmknodat                   mode_t
#define __NR32AT3_fmknodat                   dev_t
#define __NR32AT4_fmknodat                   atflag_t
#define __NR32AT0_futimesat64                fd_t
#define __NR32AT1_futimesat64                const char *
#define __NR32AT2_futimesat64                /*[2-3]*/struct __timeval64 const *
#define __NR32AT0_kfstatat                   fd_t
#define __NR32AT1_kfstatat                   char const *
#define __NR32AT2_kfstatat                   struct stat *
#define __NR32AT3_kfstatat                   atflag_t
#define __NR32AT0_frenameat                  fd_t
#define __NR32AT1_frenameat                  char const *
#define __NR32AT2_frenameat                  fd_t
#define __NR32AT3_frenameat                  char const *
#define __NR32AT4_frenameat                  atflag_t
#define __NR32AT0_fsymlinkat                 char const *
#define __NR32AT1_fsymlinkat                 fd_t
#define __NR32AT2_fsymlinkat                 char const *
#define __NR32AT3_fsymlinkat                 atflag_t
#define __NR32AT0_freadlinkat                fd_t
#define __NR32AT1_freadlinkat                char const *
#define __NR32AT2_freadlinkat                char *
#define __NR32AT3_freadlinkat                size_t
#define __NR32AT4_freadlinkat                atflag_t
#define __NR32AT0_pselect6_64                size_t
#define __NR32AT1_pselect6_64                struct __fd_set_struct *
#define __NR32AT2_pselect6_64                struct __fd_set_struct *
#define __NR32AT3_pselect6_64                struct __fd_set_struct *
#define __NR32AT4_pselect6_64                struct __timespec64 const *
#define __NR32AT5_pselect6_64                void const *
#define __NR32AT0_ppoll64                    struct pollfd *
#define __NR32AT1_ppoll64                    size_t
#define __NR32AT2_ppoll64                    struct __timespec64 const *
#define __NR32AT3_ppoll64                    struct __sigset_struct const *
#define __NR32AT4_ppoll64                    size_t
#define __NR32AT0_utimensat64                fd_t
#define __NR32AT1_utimensat64                char const *
#define __NR32AT2_utimensat64                /*[2-3]*/struct __timespec64 const *
#define __NR32AT3_utimensat64                atflag_t
#define __NR32AT0_fallocate64                fd_t
#define __NR32AT1_fallocate64                syscall_ulong_t
#define __NR32AT2_fallocate64                uint64_t
#define __NR32AT3_fallocate64                uint64_t
#define __NR32AT0_timerfd_settime64          fd_t
#define __NR32AT1_timerfd_settime64          syscall_ulong_t
#define __NR32AT2_timerfd_settime64          struct __itimerspec64 const *
#define __NR32AT3_timerfd_settime64          struct __itimerspec64 *
#define __NR32AT0_timerfd_gettime64          fd_t
#define __NR32AT1_timerfd_gettime64          struct __itimerspec64 *
#define __NR32AT0_preadvf                    fd_t
#define __NR32AT1_preadvf                    struct iovec const *
#define __NR32AT2_preadvf                    size_t
#define __NR32AT3_preadvf                    uint64_t
#define __NR32AT4_preadvf                    iomode_t
#define __NR32AT0_pwritevf                   fd_t
#define __NR32AT1_pwritevf                   struct iovec const *
#define __NR32AT2_pwritevf                   size_t
#define __NR32AT3_pwritevf                   uint64_t
#define __NR32AT4_pwritevf                   iomode_t
#define __NR32AT0_recvmmsg64                 fd_t
#define __NR32AT1_recvmmsg64                 struct mmsghdr *
#define __NR32AT2_recvmmsg64                 size_t
#define __NR32AT3_recvmmsg64                 syscall_ulong_t
#define __NR32AT4_recvmmsg64                 struct __timespec64 *
#endif /* __WANT_SYSCALL_ARGUMENT_TYPES */

#ifdef __WANT_SYSCALL_ARGUMENT_NAMES
#define __NR32AN0_exit                       "status"
#define __NR32AN0_read                       "fd"
#define __NR32AN1_read                       "buf"
#define __NR32AN2_read                       "bufsize"
#define __NR32AN0_write                      "fd"
#define __NR32AN1_write                      "buf"
#define __NR32AN2_write                      "bufsize"
#define __NR32AN0_open                       "filename"
#define __NR32AN1_open                       "oflags"
#define __NR32AN2_open                       "mode"
#define __NR32AN0_close                      "fd"
#define __NR32AN0_waitpid                    "pid"
#define __NR32AN1_waitpid                    "stat_loc"
#define __NR32AN2_waitpid                    "options"
#define __NR32AN0_creat                      "filename"
#define __NR32AN1_creat                      "mode"
#define __NR32AN0_link                       "existing_file"
#define __NR32AN1_link                       "link_file"
#define __NR32AN0_unlink                     "filename"
#define __NR32AN0_execve                     "path"
#define __NR32AN1_execve                     "argv"
#define __NR32AN2_execve                     "envp"
#define __NR32AN0_chdir                      "path"
#define __NR32AN0_time                       "timer"
#define __NR32AN0_mknod                      "nodename"
#define __NR32AN1_mknod                      "mode"
#define __NR32AN2_mknod                      "dev"
#define __NR32AN0_chmod                      "filename"
#define __NR32AN1_chmod                      "mode"
#define __NR32AN0_lchown                     "filename"
#define __NR32AN1_lchown                     "owner"
#define __NR32AN2_lchown                     "group"
#define __NR32AN0_linux_oldstat              "filename"
#define __NR32AN1_linux_oldstat              "statbuf"
#define __NR32AN0_lseek                      "fd"
#define __NR32AN1_lseek                      "offset"
#define __NR32AN2_lseek                      "whence"
#define __NR32AN0_mount                      "special_file"
#define __NR32AN1_mount                      "dir"
#define __NR32AN2_mount                      "fstype"
#define __NR32AN3_mount                      "rwflag"
#define __NR32AN4_mount                      "data"
#define __NR32AN0_umount                     "special_file"
#define __NR32AN0_setuid                     "uid"
#define __NR32AN0_stime                      "t"
#define __NR32AN0_ptrace                     "request"
#define __NR32AN1_ptrace                     "pid"
#define __NR32AN2_ptrace                     "addr"
#define __NR32AN3_ptrace                     "data"
#define __NR32AN0_alarm                      "seconds"
#define __NR32AN0_linux_oldfstat             "fd"
#define __NR32AN1_linux_oldfstat             "statbuf"
#define __NR32AN0_utime                      "filename"
#define __NR32AN1_utime                      "times"
#define __NR32AN0_access                     "filename"
#define __NR32AN1_access                     "type"
#define __NR32AN0_nice                       "inc"
#define __NR32AN0_ftime                      "tp"
#define __NR32AN0_kill                       "pid"
#define __NR32AN1_kill                       "signo"
#define __NR32AN0_rename                     "oldname"
#define __NR32AN1_rename                     "newname_or_path"
#define __NR32AN0_mkdir                      "pathname"
#define __NR32AN1_mkdir                      "mode"
#define __NR32AN0_rmdir                      "path"
#define __NR32AN0_dup                        "fd"
#define __NR32AN0_pipe                       "pipedes"
#define __NR32AN0_times                      "buf"
#define __NR32AN0_brk                        "addr"
#define __NR32AN0_setgid                     "gid"
#define __NR32AN0_signal                     "signo"
#define __NR32AN1_signal                     "handler"
#define __NR32AN0_acct                       "filename"
#define __NR32AN0_umount2                    "special_file"
#define __NR32AN1_umount2                    "flags"
#define __NR32AN0_ioctl                      "fd"
#define __NR32AN1_ioctl                      "request"
#define __NR32AN2_ioctl                      "arg"
#define __NR32AN0_fcntl                      "fd"
#define __NR32AN1_fcntl                      "cmd"
#define __NR32AN2_fcntl                      "arg"
#define __NR32AN0_setpgid                    "pid"
#define __NR32AN1_setpgid                    "pgid"
#define __NR32AN0_oldolduname                "name"
#define __NR32AN0_umask                      "mode"
#define __NR32AN0_chroot                     "path"
#define __NR32AN0_ustat                      "dev"
#define __NR32AN1_ustat                      "ubuf"
#define __NR32AN0_dup2                       "oldfd"
#define __NR32AN1_dup2                       "newfd"
#define __NR32AN0_sigaction                  "signo"
#define __NR32AN1_sigaction                  "act"
#define __NR32AN2_sigaction                  "oact"
#define __NR32AN0_ssetmask                   "sigmask"
#define __NR32AN0_setreuid                   "ruid"
#define __NR32AN1_setreuid                   "euid"
#define __NR32AN0_setregid                   "rgid"
#define __NR32AN1_setregid                   "egid"
#define __NR32AN0_sigsuspend                 "set"
#define __NR32AN0_sigpending                 "set"
#define __NR32AN0_sethostname                "name"
#define __NR32AN1_sethostname                "len"
#define __NR32AN0_setrlimit                  "resource"
#define __NR32AN1_setrlimit                  "rlimits"
#define __NR32AN0_getrlimit                  "resource"
#define __NR32AN1_getrlimit                  "rlimits"
#define __NR32AN0_getrusage                  "who"
#define __NR32AN1_getrusage                  "usage"
#define __NR32AN0_gettimeofday               "tv"
#define __NR32AN1_gettimeofday               "tz"
#define __NR32AN0_settimeofday               "tv"
#define __NR32AN1_settimeofday               "tz"
#define __NR32AN0_getgroups                  "size"
#define __NR32AN1_getgroups                  "list"
#define __NR32AN0_setgroups                  "count"
#define __NR32AN1_setgroups                  "groups"
#define __NR32AN0_select                     "nfds"
#define __NR32AN1_select                     "readfds"
#define __NR32AN2_select                     "writefds"
#define __NR32AN3_select                     "exceptfds"
#define __NR32AN4_select                     "timeout"
#define __NR32AN0_symlink                    "link_text"
#define __NR32AN1_symlink                    "target_path"
#define __NR32AN0_linux_oldlstat             "filename"
#define __NR32AN1_linux_oldlstat             "statbuf"
#define __NR32AN0_readlink                   "path"
#define __NR32AN1_readlink                   "buf"
#define __NR32AN2_readlink                   "buflen"
#define __NR32AN0_swapon                     "pathname"
#define __NR32AN1_swapon                     "swapflags"
#define __NR32AN0_reboot                     "how"
#define __NR32AN0_readdir                    "fd"
#define __NR32AN1_readdir                    "dirp"
#define __NR32AN2_readdir                    "count"
#define __NR32AN0_mmap                       "addr"
#define __NR32AN1_mmap                       "len"
#define __NR32AN2_mmap                       "prot"
#define __NR32AN3_mmap                       "flags"
#define __NR32AN4_mmap                       "fd"
#define __NR32AN5_mmap                       "offset"
#define __NR32AN0_munmap                     "addr"
#define __NR32AN1_munmap                     "len"
#define __NR32AN0_truncate                   "filename"
#define __NR32AN1_truncate                   "length"
#define __NR32AN0_ftruncate                  "fd"
#define __NR32AN1_ftruncate                  "length"
#define __NR32AN0_fchmod                     "fd"
#define __NR32AN1_fchmod                     "mode"
#define __NR32AN0_fchown                     "fd"
#define __NR32AN1_fchown                     "owner"
#define __NR32AN2_fchown                     "group"
#define __NR32AN0_getpriority                "which"
#define __NR32AN1_getpriority                "who"
#define __NR32AN0_setpriority                "which"
#define __NR32AN1_setpriority                "who"
#define __NR32AN2_setpriority                "value"
#define __NR32AN0_profil                     "sample_buffer"
#define __NR32AN1_profil                     "size"
#define __NR32AN2_profil                     "offset"
#define __NR32AN3_profil                     "scale"
#define __NR32AN0_statfs                     "file"
#define __NR32AN1_statfs                     "buf"
#define __NR32AN0_fstatfs                    "file"
#define __NR32AN1_fstatfs                    "buf"
#define __NR32AN0_ioperm                     "from"
#define __NR32AN1_ioperm                     "num"
#define __NR32AN2_ioperm                     "turn_on"
#define __NR32AN0_socketcall                 "call"
#define __NR32AN1_socketcall                 "args"
#define __NR32AN0_syslog                     "level"
#define __NR32AN1_syslog                     "str"
#define __NR32AN2_syslog                     "len"
#define __NR32AN0_setitimer                  "which"
#define __NR32AN1_setitimer                  "newval"
#define __NR32AN2_setitimer                  "oldval"
#define __NR32AN0_getitimer                  "which"
#define __NR32AN1_getitimer                  "curr_value"
#define __NR32AN0_linux_stat32               "filename"
#define __NR32AN1_linux_stat32               "statbuf"
#define __NR32AN0_linux_lstat32              "filename"
#define __NR32AN1_linux_lstat32              "statbuf"
#define __NR32AN0_linux_fstat32              "fd"
#define __NR32AN1_linux_fstat32              "statbuf"
#define __NR32AN0_olduname                   "name"
#define __NR32AN0_iopl                       "level"
#define __NR32AN0_wait4                      "pid"
#define __NR32AN1_wait4                      "stat_loc"
#define __NR32AN2_wait4                      "options"
#define __NR32AN3_wait4                      "usage"
#define __NR32AN0_swapoff                    "pathname"
#define __NR32AN0_sysinfo                    "info"
#define __NR32AN0_fsync                      "fd"
#define __NR32AN0_sigreturn                  "restore_fpu"
#define __NR32AN1_sigreturn                  "unused1"
#define __NR32AN2_sigreturn                  "unused2"
#define __NR32AN3_sigreturn                  "restore_sigmask"
#define __NR32AN4_sigreturn                  "sc_info"
#define __NR32AN5_sigreturn                  "restore_cpu"
#define __NR32AN0_clone                      "flags"
#define __NR32AN1_clone                      "child_stack"
#define __NR32AN2_clone                      "ptid"
#define __NR32AN3_clone                      "newtls"
#define __NR32AN4_clone                      "ctid"
#define __NR32AN0_setdomainname              "name"
#define __NR32AN1_setdomainname              "len"
#define __NR32AN0_uname                      "name"
#define __NR32AN0_modify_ldt                 "func"
#define __NR32AN1_modify_ldt                 "ptr"
#define __NR32AN2_modify_ldt                 "bytecount"
#define __NR32AN0_mprotect                   "addr"
#define __NR32AN1_mprotect                   "len"
#define __NR32AN2_mprotect                   "prot"
#define __NR32AN0_sigprocmask                "how"
#define __NR32AN1_sigprocmask                "set"
#define __NR32AN2_sigprocmask                "oset"
#define __NR32AN0_getpgid                    "pid"
#define __NR32AN0_fchdir                     "fd"
#define __NR32AN0_setfsuid                   "uid"
#define __NR32AN0_setfsgid                   "gid"
#define __NR32AN0__llseek                    "fd"
#define __NR32AN1__llseek                    "offset"
#define __NR32AN2__llseek                    "result"
#define __NR32AN3__llseek                    "whence"
#define __NR32AN0_getdents                   "fd"
#define __NR32AN1_getdents                   "dirp"
#define __NR32AN2_getdents                   "count"
#define __NR32AN0_flock                      "fd"
#define __NR32AN1_flock                      "operation"
#define __NR32AN0_msync                      "addr"
#define __NR32AN1_msync                      "len"
#define __NR32AN2_msync                      "flags"
#define __NR32AN0_readv                      "fd"
#define __NR32AN1_readv                      "iovec"
#define __NR32AN2_readv                      "count"
#define __NR32AN0_writev                     "fd"
#define __NR32AN1_writev                     "iovec"
#define __NR32AN2_writev                     "count"
#define __NR32AN0_getsid                     "pid"
#define __NR32AN0_fdatasync                  "fd"
#define __NR32AN0_mlock                      "addr"
#define __NR32AN1_mlock                      "len"
#define __NR32AN0_munlock                    "addr"
#define __NR32AN1_munlock                    "len"
#define __NR32AN0_mlockall                   "flags"
#define __NR32AN0_sched_setparam             "pid"
#define __NR32AN1_sched_setparam             "param"
#define __NR32AN0_sched_getparam             "pid"
#define __NR32AN1_sched_getparam             "param"
#define __NR32AN0_sched_setscheduler         "pid"
#define __NR32AN1_sched_setscheduler         "policy"
#define __NR32AN2_sched_setscheduler         "param"
#define __NR32AN0_sched_getscheduler         "pid"
#define __NR32AN0_sched_get_priority_max     "algorithm"
#define __NR32AN0_sched_get_priority_min     "algorithm"
#define __NR32AN0_sched_rr_get_interval      "pid"
#define __NR32AN1_sched_rr_get_interval      "tms"
#define __NR32AN0_nanosleep                  "req"
#define __NR32AN1_nanosleep                  "rem"
#define __NR32AN0_mremap                     "addr"
#define __NR32AN1_mremap                     "old_len"
#define __NR32AN2_mremap                     "new_len"
#define __NR32AN3_mremap                     "flags"
#define __NR32AN4_mremap                     "new_address"
#define __NR32AN0_setresuid                  "ruid"
#define __NR32AN1_setresuid                  "euid"
#define __NR32AN2_setresuid                  "suid"
#define __NR32AN0_getresuid                  "ruid"
#define __NR32AN1_getresuid                  "euid"
#define __NR32AN2_getresuid                  "suid"
#define __NR32AN0_poll                       "fds"
#define __NR32AN1_poll                       "nfds"
#define __NR32AN2_poll                       "timeout"
#define __NR32AN0_setresgid                  "rgid"
#define __NR32AN1_setresgid                  "egid"
#define __NR32AN2_setresgid                  "sgid"
#define __NR32AN0_getresgid                  "rgid"
#define __NR32AN1_getresgid                  "egid"
#define __NR32AN2_getresgid                  "sgid"
#define __NR32AN0_rt_sigaction               "signo"
#define __NR32AN1_rt_sigaction               "act"
#define __NR32AN2_rt_sigaction               "oact"
#define __NR32AN3_rt_sigaction               "sigsetsize"
#define __NR32AN0_rt_sigprocmask             "how"
#define __NR32AN1_rt_sigprocmask             "set"
#define __NR32AN2_rt_sigprocmask             "oset"
#define __NR32AN3_rt_sigprocmask             "sigsetsize"
#define __NR32AN0_rt_sigpending              "set"
#define __NR32AN1_rt_sigpending              "sigsetsize"
#define __NR32AN0_rt_sigtimedwait            "set"
#define __NR32AN1_rt_sigtimedwait            "info"
#define __NR32AN2_rt_sigtimedwait            "timeout"
#define __NR32AN3_rt_sigtimedwait            "sigsetsize"
#define __NR32AN0_rt_sigqueueinfo            "tgid"
#define __NR32AN1_rt_sigqueueinfo            "signo"
#define __NR32AN2_rt_sigqueueinfo            "uinfo"
#define __NR32AN0_rt_sigsuspend              "set"
#define __NR32AN1_rt_sigsuspend              "sigsetsize"
#define __NR32AN0_pread64                    "fd"
#define __NR32AN1_pread64                    "buf"
#define __NR32AN2_pread64                    "bufsize"
#define __NR32AN3_pread64                    "offset"
#define __NR32AN0_pwrite64                   "fd"
#define __NR32AN1_pwrite64                   "buf"
#define __NR32AN2_pwrite64                   "bufsize"
#define __NR32AN3_pwrite64                   "offset"
#define __NR32AN0_chown                      "filename"
#define __NR32AN1_chown                      "owner"
#define __NR32AN2_chown                      "group"
#define __NR32AN0_getcwd                     "buf"
#define __NR32AN1_getcwd                     "size"
#define __NR32AN0_sigaltstack                "ss"
#define __NR32AN1_sigaltstack                "oss"
#define __NR32AN0_sendfile                   "out_fd"
#define __NR32AN1_sendfile                   "in_fd"
#define __NR32AN2_sendfile                   "offset"
#define __NR32AN3_sendfile                   "count"
#define __NR32AN0_mmap2                      "addr"
#define __NR32AN1_mmap2                      "len"
#define __NR32AN2_mmap2                      "prot"
#define __NR32AN3_mmap2                      "flags"
#define __NR32AN4_mmap2                      "fd"
#define __NR32AN5_mmap2                      "pgoffset"
#define __NR32AN0_truncate64                 "filename"
#define __NR32AN1_truncate64                 "length"
#define __NR32AN0_ftruncate64                "fd"
#define __NR32AN1_ftruncate64                "length"
#define __NR32AN0_linux_stat64               "filename"
#define __NR32AN1_linux_stat64               "statbuf"
#define __NR32AN0_linux_lstat64              "filename"
#define __NR32AN1_linux_lstat64              "statbuf"
#define __NR32AN0_linux_fstat64              "fd"
#define __NR32AN1_linux_fstat64              "statbuf"
#define __NR32AN0_lchown32                   "filename"
#define __NR32AN1_lchown32                   "owner"
#define __NR32AN2_lchown32                   "group"
#define __NR32AN0_setreuid32                 "ruid"
#define __NR32AN1_setreuid32                 "euid"
#define __NR32AN0_setregid32                 "rgid"
#define __NR32AN1_setregid32                 "egid"
#define __NR32AN0_getgroups32                "size"
#define __NR32AN1_getgroups32                "list"
#define __NR32AN0_setgroups32                "count"
#define __NR32AN1_setgroups32                "groups"
#define __NR32AN0_fchown32                   "fd"
#define __NR32AN1_fchown32                   "owner"
#define __NR32AN2_fchown32                   "group"
#define __NR32AN0_setresuid32                "ruid"
#define __NR32AN1_setresuid32                "euid"
#define __NR32AN2_setresuid32                "suid"
#define __NR32AN0_getresuid32                "ruid"
#define __NR32AN1_getresuid32                "euid"
#define __NR32AN2_getresuid32                "suid"
#define __NR32AN0_setresgid32                "rgid"
#define __NR32AN1_setresgid32                "egid"
#define __NR32AN2_setresgid32                "sgid"
#define __NR32AN0_getresgid32                "rgid"
#define __NR32AN1_getresgid32                "egid"
#define __NR32AN2_getresgid32                "sgid"
#define __NR32AN0_chown32                    "filename"
#define __NR32AN1_chown32                    "owner"
#define __NR32AN2_chown32                    "group"
#define __NR32AN0_setuid32                   "uid"
#define __NR32AN0_setgid32                   "gid"
#define __NR32AN0_setfsuid32                 "uid"
#define __NR32AN0_setfsgid32                 "gid"
#define __NR32AN0_mincore                    "start"
#define __NR32AN1_mincore                    "len"
#define __NR32AN2_mincore                    "vec"
#define __NR32AN0_madvise                    "addr"
#define __NR32AN1_madvise                    "len"
#define __NR32AN2_madvise                    "advice"
#define __NR32AN0_getdents64                 "fd"
#define __NR32AN1_getdents64                 "dirp"
#define __NR32AN2_getdents64                 "count"
#define __NR32AN0_fcntl64                    "fd"
#define __NR32AN1_fcntl64                    "command"
#define __NR32AN2_fcntl64                    "arg"
#define __NR32AN0_readahead                  "fd"
#define __NR32AN1_readahead                  "offset"
#define __NR32AN2_readahead                  "count"
#define __NR32AN0_setxattr                   "path"
#define __NR32AN1_setxattr                   "name"
#define __NR32AN2_setxattr                   "buf"
#define __NR32AN3_setxattr                   "bufsize"
#define __NR32AN4_setxattr                   "flags"
#define __NR32AN0_lsetxattr                  "path"
#define __NR32AN1_lsetxattr                  "name"
#define __NR32AN2_lsetxattr                  "buf"
#define __NR32AN3_lsetxattr                  "bufsize"
#define __NR32AN4_lsetxattr                  "flags"
#define __NR32AN0_fsetxattr                  "fd"
#define __NR32AN1_fsetxattr                  "name"
#define __NR32AN2_fsetxattr                  "buf"
#define __NR32AN3_fsetxattr                  "bufsize"
#define __NR32AN4_fsetxattr                  "flags"
#define __NR32AN0_getxattr                   "path"
#define __NR32AN1_getxattr                   "name"
#define __NR32AN2_getxattr                   "buf"
#define __NR32AN3_getxattr                   "bufsize"
#define __NR32AN0_lgetxattr                  "path"
#define __NR32AN1_lgetxattr                  "name"
#define __NR32AN2_lgetxattr                  "buf"
#define __NR32AN3_lgetxattr                  "bufsize"
#define __NR32AN0_fgetxattr                  "fd"
#define __NR32AN1_fgetxattr                  "name"
#define __NR32AN2_fgetxattr                  "buf"
#define __NR32AN3_fgetxattr                  "bufsize"
#define __NR32AN0_listxattr                  "path"
#define __NR32AN1_listxattr                  "listbuf"
#define __NR32AN2_listxattr                  "listbufsize"
#define __NR32AN0_llistxattr                 "path"
#define __NR32AN1_llistxattr                 "listbuf"
#define __NR32AN2_llistxattr                 "listbufsize"
#define __NR32AN0_flistxattr                 "fd"
#define __NR32AN1_flistxattr                 "listbuf"
#define __NR32AN2_flistxattr                 "listbufsize"
#define __NR32AN0_removexattr                "path"
#define __NR32AN1_removexattr                "name"
#define __NR32AN0_lremovexattr               "path"
#define __NR32AN1_lremovexattr               "name"
#define __NR32AN0_fremovexattr               "fd"
#define __NR32AN1_fremovexattr               "name"
#define __NR32AN0_tkill                      "tid"
#define __NR32AN1_tkill                      "signo"
#define __NR32AN0_sendfile64                 "out_fd"
#define __NR32AN1_sendfile64                 "in_fd"
#define __NR32AN2_sendfile64                 "offset"
#define __NR32AN3_sendfile64                 "count"
#define __NR32AN0_futex                      "uaddr"
#define __NR32AN1_futex                      "futex_op"
#define __NR32AN2_futex                      "val"
#define __NR32AN3_futex                      "timeout_or_val2"
#define __NR32AN4_futex                      "uaddr2"
#define __NR32AN5_futex                      "val3"
#define __NR32AN0_sched_setaffinity          "pid"
#define __NR32AN1_sched_setaffinity          "cpusetsize"
#define __NR32AN2_sched_setaffinity          "cpuset"
#define __NR32AN0_sched_getaffinity          "pid"
#define __NR32AN1_sched_getaffinity          "cpusetsize"
#define __NR32AN2_sched_getaffinity          "cpuset"
#define __NR32AN0_exit_group                 "exit_code"
#define __NR32AN0_epoll_create               "size"
#define __NR32AN0_epoll_ctl                  "epfd"
#define __NR32AN1_epoll_ctl                  "op"
#define __NR32AN2_epoll_ctl                  "fd"
#define __NR32AN3_epoll_ctl                  "event"
#define __NR32AN0_epoll_wait                 "epfd"
#define __NR32AN1_epoll_wait                 "events"
#define __NR32AN2_epoll_wait                 "maxevents"
#define __NR32AN3_epoll_wait                 "timeout"
#define __NR32AN0_remap_file_pages           "start"
#define __NR32AN1_remap_file_pages           "size"
#define __NR32AN2_remap_file_pages           "prot"
#define __NR32AN3_remap_file_pages           "pgoff"
#define __NR32AN4_remap_file_pages           "flags"
#define __NR32AN0_set_tid_address            "tidptr"
#define __NR32AN0_timer_create               "clock_id"
#define __NR32AN1_timer_create               "evp"
#define __NR32AN2_timer_create               "timerid"
#define __NR32AN0_timer_settime              "timerid"
#define __NR32AN1_timer_settime              "flags"
#define __NR32AN2_timer_settime              "value"
#define __NR32AN3_timer_settime              "ovalue"
#define __NR32AN0_timer_gettime              "timerid"
#define __NR32AN1_timer_gettime              "value"
#define __NR32AN0_timer_getoverrun           "timerid"
#define __NR32AN0_timer_delete               "timerid"
#define __NR32AN0_clock_settime              "clock_id"
#define __NR32AN1_clock_settime              "tp"
#define __NR32AN0_clock_gettime              "clock_id"
#define __NR32AN1_clock_gettime              "tp"
#define __NR32AN0_clock_getres               "clock_id"
#define __NR32AN1_clock_getres               "res"
#define __NR32AN0_clock_nanosleep            "clock_id"
#define __NR32AN1_clock_nanosleep            "flags"
#define __NR32AN2_clock_nanosleep            "requested_time"
#define __NR32AN3_clock_nanosleep            "remaining"
#define __NR32AN0_statfs64                   "file"
#define __NR32AN1_statfs64                   "buf"
#define __NR32AN0_fstatfs64                  "file"
#define __NR32AN1_fstatfs64                  "buf"
#define __NR32AN0_tgkill                     "tgid"
#define __NR32AN1_tgkill                     "tid"
#define __NR32AN2_tgkill                     "signo"
#define __NR32AN0_utimes                     "filename"
#define __NR32AN1_utimes                     "times"
#define __NR32AN0_waitid                     "idtype"
#define __NR32AN1_waitid                     "id"
#define __NR32AN2_waitid                     "infop"
#define __NR32AN3_waitid                     "options"
#define __NR32AN4_waitid                     "ru"
#define __NR32AN0_ioprio_set                 "which"
#define __NR32AN1_ioprio_set                 "who"
#define __NR32AN2_ioprio_set                 "ioprio"
#define __NR32AN0_ioprio_get                 "which"
#define __NR32AN1_ioprio_get                 "who"
#define __NR32AN0_openat                     "dirfd"
#define __NR32AN1_openat                     "filename"
#define __NR32AN2_openat                     "oflags"
#define __NR32AN3_openat                     "mode"
#define __NR32AN0_mkdirat                    "dirfd"
#define __NR32AN1_mkdirat                    "pathname"
#define __NR32AN2_mkdirat                    "mode"
#define __NR32AN0_mknodat                    "dirfd"
#define __NR32AN1_mknodat                    "nodename"
#define __NR32AN2_mknodat                    "mode"
#define __NR32AN3_mknodat                    "dev"
#define __NR32AN0_fchownat                   "dirfd"
#define __NR32AN1_fchownat                   "filename"
#define __NR32AN2_fchownat                   "owner"
#define __NR32AN3_fchownat                   "group"
#define __NR32AN4_fchownat                   "flags"
#define __NR32AN0_futimesat                  "dirfd"
#define __NR32AN1_futimesat                  "filename"
#define __NR32AN2_futimesat                  "times"
#define __NR32AN0_linux_fstatat64            "dirfd"
#define __NR32AN1_linux_fstatat64            "filename"
#define __NR32AN2_linux_fstatat64            "statbuf"
#define __NR32AN3_linux_fstatat64            "flags"
#define __NR32AN0_unlinkat                   "dirfd"
#define __NR32AN1_unlinkat                   "name"
#define __NR32AN2_unlinkat                   "flags"
#define __NR32AN0_renameat                   "oldfd"
#define __NR32AN1_renameat                   "oldname"
#define __NR32AN2_renameat                   "newfd"
#define __NR32AN3_renameat                   "newname_or_path"
#define __NR32AN0_linkat                     "fromfd"
#define __NR32AN1_linkat                     "existing_file"
#define __NR32AN2_linkat                     "tofd"
#define __NR32AN3_linkat                     "target_path"
#define __NR32AN4_linkat                     "flags"
#define __NR32AN0_symlinkat                  "link_text"
#define __NR32AN1_symlinkat                  "tofd"
#define __NR32AN2_symlinkat                  "target_path"
#define __NR32AN0_readlinkat                 "dirfd"
#define __NR32AN1_readlinkat                 "path"
#define __NR32AN2_readlinkat                 "buf"
#define __NR32AN3_readlinkat                 "buflen"
#define __NR32AN0_fchmodat                   "dirfd"
#define __NR32AN1_fchmodat                   "filename"
#define __NR32AN2_fchmodat                   "mode"
#define __NR32AN3_fchmodat                   "flags"
#define __NR32AN0_faccessat                  "dirfd"
#define __NR32AN1_faccessat                  "filename"
#define __NR32AN2_faccessat                  "type"
#define __NR32AN3_faccessat                  "flags"
#define __NR32AN0_pselect6                   "nfds"
#define __NR32AN1_pselect6                   "readfds"
#define __NR32AN2_pselect6                   "writefds"
#define __NR32AN3_pselect6                   "exceptfds"
#define __NR32AN4_pselect6                   "timeout"
#define __NR32AN5_pselect6                   "sigmask_sigset_and_len"
#define __NR32AN0_ppoll                      "fds"
#define __NR32AN1_ppoll                      "nfds"
#define __NR32AN2_ppoll                      "timeout_ts"
#define __NR32AN3_ppoll                      "sigmask"
#define __NR32AN4_ppoll                      "sigsetsize"
#define __NR32AN0_unshare                    "flags"
#define __NR32AN0_splice                     "fdin"
#define __NR32AN1_splice                     "offin"
#define __NR32AN2_splice                     "fdout"
#define __NR32AN3_splice                     "offout"
#define __NR32AN4_splice                     "length"
#define __NR32AN5_splice                     "flags"
#define __NR32AN0_sync_file_range            "fd"
#define __NR32AN1_sync_file_range            "offset"
#define __NR32AN2_sync_file_range            "count"
#define __NR32AN3_sync_file_range            "flags"
#define __NR32AN0_tee                        "fdin"
#define __NR32AN1_tee                        "fdout"
#define __NR32AN2_tee                        "length"
#define __NR32AN3_tee                        "flags"
#define __NR32AN0_vmsplice                   "fdout"
#define __NR32AN1_vmsplice                   "iov"
#define __NR32AN2_vmsplice                   "count"
#define __NR32AN3_vmsplice                   "flags"
#define __NR32AN0_getcpu                     "cpu"
#define __NR32AN1_getcpu                     "node"
#define __NR32AN2_getcpu                     "tcache"
#define __NR32AN0_epoll_pwait                "epfd"
#define __NR32AN1_epoll_pwait                "events"
#define __NR32AN2_epoll_pwait                "maxevents"
#define __NR32AN3_epoll_pwait                "timeout"
#define __NR32AN4_epoll_pwait                "ss"
#define __NR32AN0_utimensat                  "dirfd"
#define __NR32AN1_utimensat                  "filename"
#define __NR32AN2_utimensat                  "times"
#define __NR32AN3_utimensat                  "flags"
#define __NR32AN0_signalfd                   "fd"
#define __NR32AN1_signalfd                   "sigmask"
#define __NR32AN2_signalfd                   "sigsetsize"
#define __NR32AN0_timerfd_create             "clock_id"
#define __NR32AN1_timerfd_create             "flags"
#define __NR32AN0_eventfd                    "initval"
#define __NR32AN0_fallocate                  "fd"
#define __NR32AN1_fallocate                  "mode"
#define __NR32AN2_fallocate                  "offset"
#define __NR32AN3_fallocate                  "length"
#define __NR32AN0_timerfd_settime            "ufd"
#define __NR32AN1_timerfd_settime            "flags"
#define __NR32AN2_timerfd_settime            "utmr"
#define __NR32AN3_timerfd_settime            "otmr"
#define __NR32AN0_timerfd_gettime            "ufd"
#define __NR32AN1_timerfd_gettime            "otmr"
#define __NR32AN0_signalfd4                  "fd"
#define __NR32AN1_signalfd4                  "sigmask"
#define __NR32AN2_signalfd4                  "sigsetsize"
#define __NR32AN3_signalfd4                  "flags"
#define __NR32AN0_eventfd2                   "initval"
#define __NR32AN1_eventfd2                   "flags"
#define __NR32AN0_epoll_create1              "flags"
#define __NR32AN0_dup3                       "oldfd"
#define __NR32AN1_dup3                       "newfd"
#define __NR32AN2_dup3                       "flags"
#define __NR32AN0_pipe2                      "pipedes"
#define __NR32AN1_pipe2                      "flags"
#define __NR32AN0_preadv                     "fd"
#define __NR32AN1_preadv                     "iovec"
#define __NR32AN2_preadv                     "count"
#define __NR32AN3_preadv                     "offset"
#define __NR32AN0_pwritev                    "fd"
#define __NR32AN1_pwritev                    "iovec"
#define __NR32AN2_pwritev                    "count"
#define __NR32AN3_pwritev                    "offset"
#define __NR32AN0_rt_tgsigqueueinfo          "tgid"
#define __NR32AN1_rt_tgsigqueueinfo          "tid"
#define __NR32AN2_rt_tgsigqueueinfo          "signo"
#define __NR32AN3_rt_tgsigqueueinfo          "uinfo"
#define __NR32AN0_recvmmsg                   "sockfd"
#define __NR32AN1_recvmmsg                   "vmessages"
#define __NR32AN2_recvmmsg                   "vlen"
#define __NR32AN3_recvmmsg                   "flags"
#define __NR32AN4_recvmmsg                   "tmo"
#define __NR32AN0_prlimit64                  "pid"
#define __NR32AN1_prlimit64                  "resource"
#define __NR32AN2_prlimit64                  "new_limit"
#define __NR32AN3_prlimit64                  "old_limit"
#define __NR32AN0_name_to_handle_at          "dirfd"
#define __NR32AN1_name_to_handle_at          "name"
#define __NR32AN2_name_to_handle_at          "handle"
#define __NR32AN3_name_to_handle_at          "mnt_id"
#define __NR32AN4_name_to_handle_at          "flags"
#define __NR32AN0_open_by_handle_at          "mountdirfd"
#define __NR32AN1_open_by_handle_at          "handle"
#define __NR32AN2_open_by_handle_at          "flags"
#define __NR32AN0_syncfs                     "fd"
#define __NR32AN0_sendmmsg                   "sockfd"
#define __NR32AN1_sendmmsg                   "vmessages"
#define __NR32AN2_sendmmsg                   "vlen"
#define __NR32AN3_sendmmsg                   "flags"
#define __NR32AN0_setns                      "fd"
#define __NR32AN1_setns                      "nstype"
#define __NR32AN0_process_vm_readv           "pid"
#define __NR32AN1_process_vm_readv           "lvec"
#define __NR32AN2_process_vm_readv           "liovcnt"
#define __NR32AN3_process_vm_readv           "rvec"
#define __NR32AN4_process_vm_readv           "riovcnt"
#define __NR32AN5_process_vm_readv           "flags"
#define __NR32AN0_process_vm_writev          "pid"
#define __NR32AN1_process_vm_writev          "lvec"
#define __NR32AN2_process_vm_writev          "liovcnt"
#define __NR32AN3_process_vm_writev          "rvec"
#define __NR32AN4_process_vm_writev          "riovcnt"
#define __NR32AN5_process_vm_writev          "flags"
#define __NR32AN0_kcmp                       "pid1"
#define __NR32AN1_kcmp                       "pid2"
#define __NR32AN2_kcmp                       "type"
#define __NR32AN3_kcmp                       "idx1"
#define __NR32AN4_kcmp                       "idx2"
#define __NR32AN0_renameat2                  "olddirfd"
#define __NR32AN1_renameat2                  "oldpath"
#define __NR32AN2_renameat2                  "newdirfd"
#define __NR32AN3_renameat2                  "newpath"
#define __NR32AN4_renameat2                  "flags"
#define __NR32AN0_execveat                   "dirfd"
#define __NR32AN1_execveat                   "pathname"
#define __NR32AN2_execveat                   "argv"
#define __NR32AN3_execveat                   "envp"
#define __NR32AN4_execveat                   "flags"
#define __NR32AN0_socket                     "domain"
#define __NR32AN1_socket                     "type"
#define __NR32AN2_socket                     "protocol"
#define __NR32AN0_socketpair                 "domain"
#define __NR32AN1_socketpair                 "type"
#define __NR32AN2_socketpair                 "protocol"
#define __NR32AN3_socketpair                 "fds"
#define __NR32AN0_bind                       "sockfd"
#define __NR32AN1_bind                       "addr"
#define __NR32AN2_bind                       "addr_len"
#define __NR32AN0_connect                    "sockfd"
#define __NR32AN1_connect                    "addr"
#define __NR32AN2_connect                    "addr_len"
#define __NR32AN0_listen                     "sockfd"
#define __NR32AN1_listen                     "max_backlog"
#define __NR32AN0_accept4                    "sockfd"
#define __NR32AN1_accept4                    "addr"
#define __NR32AN2_accept4                    "addr_len"
#define __NR32AN3_accept4                    "flags"
#define __NR32AN0_getsockopt                 "sockfd"
#define __NR32AN1_getsockopt                 "level"
#define __NR32AN2_getsockopt                 "optname"
#define __NR32AN3_getsockopt                 "optval"
#define __NR32AN4_getsockopt                 "optlen"
#define __NR32AN0_setsockopt                 "sockfd"
#define __NR32AN1_setsockopt                 "level"
#define __NR32AN2_setsockopt                 "optname"
#define __NR32AN3_setsockopt                 "optval"
#define __NR32AN4_setsockopt                 "optlen"
#define __NR32AN0_getsockname                "sockfd"
#define __NR32AN1_getsockname                "addr"
#define __NR32AN2_getsockname                "addr_len"
#define __NR32AN0_getpeername                "sockfd"
#define __NR32AN1_getpeername                "addr"
#define __NR32AN2_getpeername                "addr_len"
#define __NR32AN0_sendto                     "sockfd"
#define __NR32AN1_sendto                     "buf"
#define __NR32AN2_sendto                     "bufsize"
#define __NR32AN3_sendto                     "flags"
#define __NR32AN4_sendto                     "addr"
#define __NR32AN5_sendto                     "addr_len"
#define __NR32AN0_sendmsg                    "sockfd"
#define __NR32AN1_sendmsg                    "message"
#define __NR32AN2_sendmsg                    "flags"
#define __NR32AN0_recvfrom                   "sockfd"
#define __NR32AN1_recvfrom                   "buf"
#define __NR32AN2_recvfrom                   "bufsize"
#define __NR32AN3_recvfrom                   "flags"
#define __NR32AN4_recvfrom                   "addr"
#define __NR32AN5_recvfrom                   "addr_len"
#define __NR32AN0_recvmsg                    "sockfd"
#define __NR32AN1_recvmsg                    "message"
#define __NR32AN2_recvmsg                    "flags"
#define __NR32AN0_shutdown                   "sockfd"
#define __NR32AN1_shutdown                   "how"
#define __NR32AN0_hop                        "fd"
#define __NR32AN1_hop                        "command"
#define __NR32AN2_hop                        "arg"
#define __NR32AN0_hopf                       "fd"
#define __NR32AN1_hopf                       "command"
#define __NR32AN2_hopf                       "mode"
#define __NR32AN3_hopf                       "arg"
#define __NR32AN0_readf                      "fd"
#define __NR32AN1_readf                      "buf"
#define __NR32AN2_readf                      "bufsize"
#define __NR32AN3_readf                      "mode"
#define __NR32AN0_writef                     "fd"
#define __NR32AN1_writef                     "buf"
#define __NR32AN2_writef                     "bufsize"
#define __NR32AN3_writef                     "mode"
#define __NR32AN0_detach                     "pid"
#define __NR32AN0_frealpath4                 "fd"
#define __NR32AN1_frealpath4                 "buf"
#define __NR32AN2_frealpath4                 "buflen"
#define __NR32AN3_frealpath4                 "flags"
#define __NR32AN0_frealpathat                "dirfd"
#define __NR32AN1_frealpathat                "filename"
#define __NR32AN2_frealpathat                "buf"
#define __NR32AN3_frealpathat                "buflen"
#define __NR32AN4_frealpathat                "flags"
#define __NR32AN0_rpc_schedule               "target"
#define __NR32AN1_rpc_schedule               "flags"
#define __NR32AN2_rpc_schedule               "program"
#define __NR32AN3_rpc_schedule               "arguments"
#define __NR32AN0_sysctl                     "command"
#define __NR32AN1_sysctl                     "arg"
#define __NR32AN0_openpty                    "amaster"
#define __NR32AN1_openpty                    "aslave"
#define __NR32AN2_openpty                    "name"
#define __NR32AN3_openpty                    "termp"
#define __NR32AN4_openpty                    "winp"
#define __NR32AN0_fchdirat                   "dirfd"
#define __NR32AN1_fchdirat                   "path"
#define __NR32AN2_fchdirat                   "flags"
#define __NR32AN0_time64                     "timer"
#define __NR32AN0_set_exception_handler      "mode"
#define __NR32AN1_set_exception_handler      "handler"
#define __NR32AN2_set_exception_handler      "handler_sp"
#define __NR32AN0_get_exception_handler      "pmode"
#define __NR32AN1_get_exception_handler      "phandler"
#define __NR32AN2_get_exception_handler      "phandler_sp"
#define __NR32AN0_set_library_listdef        "listdef"
#define __NR32AN0_debugtrap                  "state"
#define __NR32AN1_debugtrap                  "reason"
#define __NR32AN0_lfutex                     "uaddr"
#define __NR32AN1_lfutex                     "futex_op"
#define __NR32AN2_lfutex                     "val"
#define __NR32AN3_lfutex                     "timeout"
#define __NR32AN4_lfutex                     "val2"
#define __NR32AN0_lseek64                    "fd"
#define __NR32AN1_lseek64                    "offset"
#define __NR32AN2_lseek64                    "whence"
#define __NR32AN0_lfutexlock                 "ulockaddr"
#define __NR32AN1_lfutexlock                 "uaddr"
#define __NR32AN2_lfutexlock                 "futex_op"
#define __NR32AN3_lfutexlock                 "val"
#define __NR32AN4_lfutexlock                 "timeout"
#define __NR32AN5_lfutexlock                 "val2"
#define __NR32AN0_lfutexexpr                 "uaddr"
#define __NR32AN1_lfutexexpr                 "base"
#define __NR32AN2_lfutexexpr                 "exprv"
#define __NR32AN3_lfutexexpr                 "exprc"
#define __NR32AN4_lfutexexpr                 "timeout"
#define __NR32AN5_lfutexexpr                 "timeout_flags"
#define __NR32AN0_lfutexlockexpr             "ulockaddr"
#define __NR32AN1_lfutexlockexpr             "base"
#define __NR32AN2_lfutexlockexpr             "exprv"
#define __NR32AN3_lfutexlockexpr             "exprc"
#define __NR32AN4_lfutexlockexpr             "timeout"
#define __NR32AN5_lfutexlockexpr             "timeout_flags"
#define __NR32AN0_mktty                      "keyboard"
#define __NR32AN1_mktty                      "display"
#define __NR32AN2_mktty                      "name"
#define __NR32AN3_mktty                      "rsvd"
#define __NR32AN0_raiseat                    "state"
#define __NR32AN1_raiseat                    "si"
#define __NR32AN0_stime64                    "t"
#define __NR32AN0_coredump                   "curr_state"
#define __NR32AN1_coredump                   "orig_state"
#define __NR32AN2_coredump                   "traceback_vector"
#define __NR32AN3_coredump                   "traceback_length"
#define __NR32AN4_coredump                   "exception"
#define __NR32AN5_coredump                   "unwind_error"
#define __NR32AN0_utime64                    "filename"
#define __NR32AN1_utime64                    "times"
#define __NR32AN0_ioctlf                     "fd"
#define __NR32AN1_ioctlf                     "command"
#define __NR32AN2_ioctlf                     "mode"
#define __NR32AN3_ioctlf                     "arg"
#define __NR32AN0_fsmode                     "mode"
#define __NR32AN0_gettimeofday64             "tv"
#define __NR32AN1_gettimeofday64             "tz"
#define __NR32AN0_settimeofday64             "tv"
#define __NR32AN1_settimeofday64             "tz"
#define __NR32AN0_select64                   "nfds"
#define __NR32AN1_select64                   "readfds"
#define __NR32AN2_select64                   "writefds"
#define __NR32AN3_select64                   "exceptfds"
#define __NR32AN4_select64                   "timeout"
#define __NR32AN0_maplibrary                 "addr"
#define __NR32AN1_maplibrary                 "flags"
#define __NR32AN2_maplibrary                 "fd"
#define __NR32AN3_maplibrary                 "hdrv"
#define __NR32AN4_maplibrary                 "hdrc"
#define __NR32AN0_setitimer64                "which"
#define __NR32AN1_setitimer64                "newval"
#define __NR32AN2_setitimer64                "oldval"
#define __NR32AN0_getitimer64                "which"
#define __NR32AN1_getitimer64                "curr_value"
#define __NR32AN0_kreaddir                   "fd"
#define __NR32AN1_kreaddir                   "buf"
#define __NR32AN2_kreaddir                   "bufsize"
#define __NR32AN3_kreaddir                   "mode"
#define __NR32AN0_readvf                     "fd"
#define __NR32AN1_readvf                     "iovec"
#define __NR32AN2_readvf                     "count"
#define __NR32AN3_readvf                     "mode"
#define __NR32AN0_writevf                    "fd"
#define __NR32AN1_writevf                    "iovec"
#define __NR32AN2_writevf                    "count"
#define __NR32AN3_writevf                    "mode"
#define __NR32AN0_sched_rr_get_interval64    "pid"
#define __NR32AN1_sched_rr_get_interval64    "tms"
#define __NR32AN0_nanosleep64                "req"
#define __NR32AN1_nanosleep64                "rem"
#define __NR32AN0_rt_sigtimedwait64          "set"
#define __NR32AN1_rt_sigtimedwait64          "info"
#define __NR32AN2_rt_sigtimedwait64          "timeout"
#define __NR32AN3_rt_sigtimedwait64          "sigsetsize"
#define __NR32AN0_pread64f                   "fd"
#define __NR32AN1_pread64f                   "buf"
#define __NR32AN2_pread64f                   "bufsize"
#define __NR32AN3_pread64f                   "offset"
#define __NR32AN4_pread64f                   "mode"
#define __NR32AN0_pwrite64f                  "fd"
#define __NR32AN1_pwrite64f                  "buf"
#define __NR32AN2_pwrite64f                  "bufsize"
#define __NR32AN3_pwrite64f                  "offset"
#define __NR32AN4_pwrite64f                  "mode"
#define __NR32AN0_kstat                      "filename"
#define __NR32AN1_kstat                      "statbuf"
#define __NR32AN0_klstat                     "filename"
#define __NR32AN1_klstat                     "statbuf"
#define __NR32AN0_kfstat                     "fd"
#define __NR32AN1_kfstat                     "statbuf"
#define __NR32AN0_kreaddirf                  "fd"
#define __NR32AN1_kreaddirf                  "buf"
#define __NR32AN2_kreaddirf                  "bufsize"
#define __NR32AN3_kreaddirf                  "mode"
#define __NR32AN4_kreaddirf                  "iomode"
#define __NR32AN0_timer_settime64            "timerid"
#define __NR32AN1_timer_settime64            "flags"
#define __NR32AN2_timer_settime64            "value"
#define __NR32AN3_timer_settime64            "ovalue"
#define __NR32AN0_timer_gettime64            "timerid"
#define __NR32AN1_timer_gettime64            "value"
#define __NR32AN0_clock_settime64            "clock_id"
#define __NR32AN1_clock_settime64            "tp"
#define __NR32AN0_clock_gettime64            "clock_id"
#define __NR32AN1_clock_gettime64            "tp"
#define __NR32AN0_clock_getres64             "clock_id"
#define __NR32AN1_clock_getres64             "res"
#define __NR32AN0_clock_nanosleep64          "clock_id"
#define __NR32AN1_clock_nanosleep64          "flags"
#define __NR32AN2_clock_nanosleep64          "requested_time"
#define __NR32AN3_clock_nanosleep64          "remaining"
#define __NR32AN0_utimes64                   "filename"
#define __NR32AN1_utimes64                   "times"
#define __NR32AN0_fmkdirat                   "dirfd"
#define __NR32AN1_fmkdirat                   "pathname"
#define __NR32AN2_fmkdirat                   "mode"
#define __NR32AN3_fmkdirat                   "flags"
#define __NR32AN0_fmknodat                   "dirfd"
#define __NR32AN1_fmknodat                   "nodename"
#define __NR32AN2_fmknodat                   "mode"
#define __NR32AN3_fmknodat                   "dev"
#define __NR32AN4_fmknodat                   "flags"
#define __NR32AN0_futimesat64                "dirfd"
#define __NR32AN1_futimesat64                "filename"
#define __NR32AN2_futimesat64                "times"
#define __NR32AN0_kfstatat                   "dirfd"
#define __NR32AN1_kfstatat                   "filename"
#define __NR32AN2_kfstatat                   "statbuf"
#define __NR32AN3_kfstatat                   "flags"
#define __NR32AN0_frenameat                  "oldfd"
#define __NR32AN1_frenameat                  "oldname"
#define __NR32AN2_frenameat                  "newfd"
#define __NR32AN3_frenameat                  "newname_or_path"
#define __NR32AN4_frenameat                  "flags"
#define __NR32AN0_fsymlinkat                 "link_text"
#define __NR32AN1_fsymlinkat                 "tofd"
#define __NR32AN2_fsymlinkat                 "target_path"
#define __NR32AN3_fsymlinkat                 "flags"
#define __NR32AN0_freadlinkat                "dirfd"
#define __NR32AN1_freadlinkat                "path"
#define __NR32AN2_freadlinkat                "buf"
#define __NR32AN3_freadlinkat                "buflen"
#define __NR32AN4_freadlinkat                "flags"
#define __NR32AN0_pselect6_64                "nfds"
#define __NR32AN1_pselect6_64                "readfds"
#define __NR32AN2_pselect6_64                "writefds"
#define __NR32AN3_pselect6_64                "exceptfds"
#define __NR32AN4_pselect6_64                "timeout"
#define __NR32AN5_pselect6_64                "sigmask_sigset_and_len"
#define __NR32AN0_ppoll64                    "fds"
#define __NR32AN1_ppoll64                    "nfds"
#define __NR32AN2_ppoll64                    "timeout_ts"
#define __NR32AN3_ppoll64                    "sigmask"
#define __NR32AN4_ppoll64                    "sigsetsize"
#define __NR32AN0_utimensat64                "dirfd"
#define __NR32AN1_utimensat64                "filename"
#define __NR32AN2_utimensat64                "times"
#define __NR32AN3_utimensat64                "flags"
#define __NR32AN0_fallocate64                "fd"
#define __NR32AN1_fallocate64                "mode"
#define __NR32AN2_fallocate64                "offset"
#define __NR32AN3_fallocate64                "length"
#define __NR32AN0_timerfd_settime64          "ufd"
#define __NR32AN1_timerfd_settime64          "flags"
#define __NR32AN2_timerfd_settime64          "utmr"
#define __NR32AN3_timerfd_settime64          "otmr"
#define __NR32AN0_timerfd_gettime64          "ufd"
#define __NR32AN1_timerfd_gettime64          "otmr"
#define __NR32AN0_preadvf                    "fd"
#define __NR32AN1_preadvf                    "iovec"
#define __NR32AN2_preadvf                    "count"
#define __NR32AN3_preadvf                    "offset"
#define __NR32AN4_preadvf                    "mode"
#define __NR32AN0_pwritevf                   "fd"
#define __NR32AN1_pwritevf                   "iovec"
#define __NR32AN2_pwritevf                   "count"
#define __NR32AN3_pwritevf                   "offset"
#define __NR32AN4_pwritevf                   "mode"
#define __NR32AN0_recvmmsg64                 "sockfd"
#define __NR32AN1_recvmmsg64                 "vmessages"
#define __NR32AN2_recvmmsg64                 "vlen"
#define __NR32AN3_recvmmsg64                 "flags"
#define __NR32AN4_recvmmsg64                 "tmo"
#endif /* __WANT_SYSCALL_ARGUMENT_NAMES */

#ifdef __WANT_SYSCALL_ARGUMENT_FORMAT
#define __NR32ATRF0_exit                       "%Iu"
#define __NR32ATRA0_exit(status)               ,(uintptr_t)(status)
#define __NR32ATRF0_read                       "%d"
#define __NR32ATRA0_read(fd, buf, bufsize)     ,(int)(fd)
#define __NR32ATRF1_read                       "%p"
#define __NR32ATRA1_read(fd, buf, bufsize)     ,buf
#define __NR32ATRF2_read                       "%Iu"
#define __NR32ATRA2_read(fd, buf, bufsize)     ,bufsize
#define __NR32ATRF0_write                      "%d"
#define __NR32ATRA0_write(fd, buf, bufsize)    ,(int)(fd)
#define __NR32ATRF1_write                      "%p"
#define __NR32ATRA1_write(fd, buf, bufsize)    ,buf
#define __NR32ATRF2_write                      "%Iu"
#define __NR32ATRA2_write(fd, buf, bufsize)    ,bufsize
#define __NR32ATRF0_open                       "%q"
#define __NR32ATRA0_open(filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_open                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA1_open(filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
                                                 ,((oflags) & O_RDWR) && ((oflags) & (O_WRONLY)) ? "|" : "",(oflags) & O_RDWR ? "O_RDWR" : "" \
                                                 ,((oflags) & O_CREAT) && ((oflags) & (O_WRONLY|O_RDWR)) ? "|" : "",(oflags) & O_CREAT ? "O_CREAT" : "" \
                                                 ,((oflags) & O_EXCL) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT)) ? "|" : "",(oflags) & O_EXCL ? "O_EXCL" : "" \
                                                 ,((oflags) & O_NOCTTY) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL)) ? "|" : "",(oflags) & O_NOCTTY ? "O_NOCTTY" : "" \
                                                 ,((oflags) & O_TRUNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY)) ? "|" : "",(oflags) & O_TRUNC ? "O_TRUNC" : "" \
                                                 ,((oflags) & O_APPEND) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC)) ? "|" : "",(oflags) & O_APPEND ? "O_APPEND" : "" \
                                                 ,((oflags) & O_NONBLOCK) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND)) ? "|" : "",(oflags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                                 ,((oflags) & O_SYNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK)) ? "|" : "",(oflags) & O_SYNC ? "O_SYNC" : "" \
                                                 ,((oflags) & O_DSYNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC)) ? "|" : "",(oflags) & O_DSYNC ? "O_DSYNC" : "" \
                                                 ,((oflags) & O_ASYNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC)) ? "|" : "",(oflags) & O_ASYNC ? "O_ASYNC" : "" \
                                                 ,((oflags) & O_DIRECT) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC)) ? "|" : "",(oflags) & O_DIRECT ? "O_DIRECT" : "" \
                                                 ,((oflags) & O_LARGEFILE) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT)) ? "|" : "",(oflags) & O_LARGEFILE ? "O_LARGEFILE" : "" \
                                                 ,((oflags) & O_DIRECTORY) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE)) ? "|" : "",(oflags) & O_DIRECTORY ? "O_DIRECTORY" : "" \
                                                 ,((oflags) & O_NOFOLLOW) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY)) ? "|" : "",(oflags) & O_NOFOLLOW ? "O_NOFOLLOW" : "" \
                                                 ,((oflags) & O_NOATIME) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW)) ? "|" : "",(oflags) & O_NOATIME ? "O_NOATIME" : "" \
                                                 ,((oflags) & O_CLOEXEC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME)) ? "|" : "",(oflags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                                 ,((oflags) & O_CLOFORK) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC)) ? "|" : "",(oflags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                                 ,((oflags) & O_PATH) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK)) ? "|" : "",(oflags) & O_PATH ? "O_PATH" : "" \
                                                 ,((oflags) & 0x0400000) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH)) ? "|" : "",(oflags) & 0x0400000 ? "O_TMPFILE" : "" \
                                                 ,((oflags) & O_SYMLINK) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH|0x0400000)) ? "|" : "",(oflags) & O_SYMLINK ? "O_SYMLINK" : "" \
                                                 ,((oflags) & O_DOSPATH) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH|0x0400000|O_SYMLINK)) ? "|" : "",(oflags) & O_DOSPATH ? "O_DOSPATH" : ""
#define __NR32ATRF2_open                       "%#Io"
#define __NR32ATRA2_open(filename, oflags, mode) ,(uintptr_t)(mode)
#define __NR32ATRF0_close                      "%d"
#define __NR32ATRA0_close(fd)                  ,(int)(fd)
#define __NR32ATRF0_waitpid                    "%Id"
#define __NR32ATRA0_waitpid(pid, stat_loc, options) ,(intptr_t)(pid)
#define __NR32ATRF1_waitpid                    "%p"
#define __NR32ATRA1_waitpid(pid, stat_loc, options) ,stat_loc
#define __NR32ATRF2_waitpid                    "%#Ix=%s%s%s%s%s%s%s"
#define __NR32ATRA2_waitpid(pid, stat_loc, options) ,(uintptr_t)(options),(options) & WNOHANG ? "WNOHANG" : "" \
                                                    ,((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "",(options) & WUNTRACED ? "WUNTRACED" : "" \
                                                    ,((options) & WCONTINUED) && ((options) & (WNOHANG|WUNTRACED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                    ,((options) & WNOWAIT) && ((options) & (WNOHANG|WUNTRACED|WCONTINUED)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR32ATRF0_creat                      "%q"
#define __NR32ATRA0_creat(filename, mode)      ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_creat                      "%#Io"
#define __NR32ATRA1_creat(filename, mode)      ,(uintptr_t)(mode)
#define __NR32ATRF0_link                       "%q"
#define __NR32ATRA0_link(existing_file, link_file) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NR32ATRF1_link                       "%q"
#define __NR32ATRA1_link(existing_file, link_file) ,(validate_readable_opt(link_file,1),link_file)
#define __NR32ATRF0_unlink                     "%q"
#define __NR32ATRA0_unlink(filename)           ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF0_execve                     "%q"
#define __NR32ATRA0_execve(path, argv, envp)   ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_execve                     "%p"
#define __NR32ATRA1_execve(path, argv, envp)   ,argv
#define __NR32ATRF2_execve                     "%p"
#define __NR32ATRA2_execve(path, argv, envp)   ,envp
#define __NR32ATRF0_chdir                      "%q"
#define __NR32ATRA0_chdir(path)                ,(validate_readable_opt(path,1),path)
#define __NR32ATRF0_time                       "%p"
#define __NR32ATRA0_time(timer)                ,timer
#define __NR32ATRF0_mknod                      "%q"
#define __NR32ATRA0_mknod(nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NR32ATRF1_mknod                      "%#Io"
#define __NR32ATRA1_mknod(nodename, mode, dev) ,(uintptr_t)(mode)
#define __NR32ATRF2_mknod                      "%.2x:%.2x"
#define __NR32ATRA2_mknod(nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF0_chmod                      "%q"
#define __NR32ATRA0_chmod(filename, mode)      ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_chmod                      "%#Io"
#define __NR32ATRA1_chmod(filename, mode)      ,(uintptr_t)(mode)
#define __NR32ATRF0_lchown                     "%q"
#define __NR32ATRA0_lchown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_lchown                     "%I16u"
#define __NR32ATRA1_lchown(filename, owner, group) ,owner
#define __NR32ATRF2_lchown                     "%I16u"
#define __NR32ATRA2_lchown(filename, owner, group) ,group
#define __NR32ATRF0_linux_oldstat              "%q"
#define __NR32ATRA0_linux_oldstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_oldstat              "%p"
#define __NR32ATRA1_linux_oldstat(filename, statbuf) ,statbuf
#define __NR32ATRF0_lseek                      "%d"
#define __NR32ATRA0_lseek(fd, offset, whence)  ,(int)(fd)
#define __NR32ATRF1_lseek                      "%I32d"
#define __NR32ATRA1_lseek(fd, offset, whence)  ,offset
#define __NR32ATRF2_lseek                      "%#Ix=%s"
#define __NR32ATRA2_lseek(fd, offset, whence)  ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NR32ATRF0_mount                      "%q"
#define __NR32ATRA0_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(special_file,1),special_file)
#define __NR32ATRF1_mount                      "%q"
#define __NR32ATRA1_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(dir,1),dir)
#define __NR32ATRF2_mount                      "%q"
#define __NR32ATRA2_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(fstype,1),fstype)
#define __NR32ATRF3_mount                      "%#Ix"
#define __NR32ATRA3_mount(special_file, dir, fstype, rwflag, data) ,(uintptr_t)(rwflag)
#define __NR32ATRF4_mount                      "%p"
#define __NR32ATRA4_mount(special_file, dir, fstype, rwflag, data) ,data
#define __NR32ATRF0_umount                     "%q"
#define __NR32ATRA0_umount(special_file)       ,(validate_readable_opt(special_file,1),special_file)
#define __NR32ATRF0_setuid                     "%I16u"
#define __NR32ATRA0_setuid(uid)                ,uid
#define __NR32ATRF0_stime                      "%p"
#define __NR32ATRA0_stime(t)                   ,t
#define __NR32ATRF0_ptrace                     "%#Ix"
#define __NR32ATRA0_ptrace(request, pid, addr, data) ,(uintptr_t)(request)
#define __NR32ATRF1_ptrace                     "%Id"
#define __NR32ATRA1_ptrace(request, pid, addr, data) ,(intptr_t)(pid)
#define __NR32ATRF2_ptrace                     "%p"
#define __NR32ATRA2_ptrace(request, pid, addr, data) ,addr
#define __NR32ATRF3_ptrace                     "%p"
#define __NR32ATRA3_ptrace(request, pid, addr, data) ,data
#define __NR32ATRF0_alarm                      "%#Ix"
#define __NR32ATRA0_alarm(seconds)             ,(uintptr_t)(seconds)
#define __NR32ATRF0_linux_oldfstat             "%d"
#define __NR32ATRA0_linux_oldfstat(fd, statbuf) ,(int)(fd)
#define __NR32ATRF1_linux_oldfstat             "%p"
#define __NR32ATRA1_linux_oldfstat(fd, statbuf) ,statbuf
#define __NR32ATRF0_utime                      "%q"
#define __NR32ATRA0_utime(filename, times)     ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utime                      "%p"
#define __NR32ATRA1_utime(filename, times)     ,times
#define __NR32ATRF0_access                     "%q"
#define __NR32ATRA0_access(filename, type)     ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_access                     "%#Ix=%s%s%s%s%s"
#define __NR32ATRA1_access(filename, type)     ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                               ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                               ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NR32ATRF0_nice                       "%Id"
#define __NR32ATRA0_nice(inc)                  ,(intptr_t)(inc)
#define __NR32ATRF0_ftime                      "%p"
#define __NR32ATRA0_ftime(tp)                  ,tp
#define __NR32ATRF0_kill                       "%Id"
#define __NR32ATRA0_kill(pid, signo)           ,(intptr_t)(pid)
#define __NR32ATRF1_kill                       "%#Ix"
#define __NR32ATRA1_kill(pid, signo)           ,(uintptr_t)(signo)
#define __NR32ATRF0_rename                     "%q"
#define __NR32ATRA0_rename(oldname, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NR32ATRF1_rename                     "%q"
#define __NR32ATRA1_rename(oldname, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR32ATRF0_mkdir                      "%q"
#define __NR32ATRA0_mkdir(pathname, mode)      ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF1_mkdir                      "%#Io"
#define __NR32ATRA1_mkdir(pathname, mode)      ,(uintptr_t)(mode)
#define __NR32ATRF0_rmdir                      "%q"
#define __NR32ATRA0_rmdir(path)                ,(validate_readable_opt(path,1),path)
#define __NR32ATRF0_dup                        "%d"
#define __NR32ATRA0_dup(fd)                    ,(int)(fd)
#define __NR32ATRF0_pipe                       "%p"
#define __NR32ATRA0_pipe(pipedes)              ,pipedes
#define __NR32ATRF0_times                      "%p"
#define __NR32ATRA0_times(buf)                 ,buf
#define __NR32ATRF0_brk                        "%p"
#define __NR32ATRA0_brk(addr)                  ,addr
#define __NR32ATRF0_setgid                     "%I16u"
#define __NR32ATRA0_setgid(gid)                ,gid
#define __NR32ATRF0_signal                     "%#Ix"
#define __NR32ATRA0_signal(signo, handler)     ,(uintptr_t)(signo)
#define __NR32ATRF1_signal                     "%p"
#define __NR32ATRA1_signal(signo, handler)     ,handler
#define __NR32ATRF0_acct                       "%q"
#define __NR32ATRA0_acct(filename)             ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF0_umount2                    "%q"
#define __NR32ATRA0_umount2(special_file, flags) ,(validate_readable_opt(special_file,1),special_file)
#define __NR32ATRF1_umount2                    "%#Ix"
#define __NR32ATRA1_umount2(special_file, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_ioctl                      "%d"
#define __NR32ATRA0_ioctl(fd, request, arg)    ,(int)(fd)
#define __NR32ATRF1_ioctl                      "%#Ix"
#define __NR32ATRA1_ioctl(fd, request, arg)    ,(uintptr_t)(request)
#define __NR32ATRF2_ioctl                      "%p"
#define __NR32ATRA2_ioctl(fd, request, arg)    ,arg
#define __NR32ATRF0_fcntl                      "%d"
#define __NR32ATRA0_fcntl(fd, cmd, arg)        ,(int)(fd)
#define __NR32ATRF1_fcntl                      "%#Ix"
#define __NR32ATRA1_fcntl(fd, cmd, arg)        ,(uintptr_t)(cmd)
#define __NR32ATRF2_fcntl                      "%p"
#define __NR32ATRA2_fcntl(fd, cmd, arg)        ,arg
#define __NR32ATRF0_setpgid                    "%Id"
#define __NR32ATRA0_setpgid(pid, pgid)         ,(intptr_t)(pid)
#define __NR32ATRF1_setpgid                    "%Id"
#define __NR32ATRA1_setpgid(pid, pgid)         ,(intptr_t)(pgid)
#define __NR32ATRF0_oldolduname                "%p"
#define __NR32ATRA0_oldolduname(name)          ,name
#define __NR32ATRF0_umask                      "%#Io"
#define __NR32ATRA0_umask(mode)                ,(uintptr_t)(mode)
#define __NR32ATRF0_chroot                     "%q"
#define __NR32ATRA0_chroot(path)               ,(validate_readable_opt(path,1),path)
#define __NR32ATRF0_ustat                      "%.2x:%.2x"
#define __NR32ATRA0_ustat(dev, ubuf)           ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF1_ustat                      "%p"
#define __NR32ATRA1_ustat(dev, ubuf)           ,ubuf
#define __NR32ATRF0_dup2                       "%d"
#define __NR32ATRA0_dup2(oldfd, newfd)         ,(int)(oldfd)
#define __NR32ATRF1_dup2                       "%d"
#define __NR32ATRA1_dup2(oldfd, newfd)         ,(int)(newfd)
#define __NR32ATRF0_sigaction                  "%#Ix"
#define __NR32ATRA0_sigaction(signo, act, oact) ,(uintptr_t)(signo)
#define __NR32ATRF1_sigaction                  "%p"
#define __NR32ATRA1_sigaction(signo, act, oact) ,act
#define __NR32ATRF2_sigaction                  "%p"
#define __NR32ATRA2_sigaction(signo, act, oact) ,oact
#define __NR32ATRF0_ssetmask                   "%#Ix"
#define __NR32ATRA0_ssetmask(sigmask)          ,(uintptr_t)(sigmask)
#define __NR32ATRF0_setreuid                   "%I16u"
#define __NR32ATRA0_setreuid(ruid, euid)       ,ruid
#define __NR32ATRF1_setreuid                   "%I16u"
#define __NR32ATRA1_setreuid(ruid, euid)       ,euid
#define __NR32ATRF0_setregid                   "%I16u"
#define __NR32ATRA0_setregid(rgid, egid)       ,rgid
#define __NR32ATRF1_setregid                   "%I16u"
#define __NR32ATRA1_setregid(rgid, egid)       ,egid
#define __NR32ATRF0_sigsuspend                 "%p"
#define __NR32ATRA0_sigsuspend(set)            ,set
#define __NR32ATRF0_sigpending                 "%p"
#define __NR32ATRA0_sigpending(set)            ,set
#define __NR32ATRF0_sethostname                "%q"
#define __NR32ATRA0_sethostname(name, len)     ,(validate_readable_opt(name,1),name)
#define __NR32ATRF1_sethostname                "%Iu"
#define __NR32ATRA1_sethostname(name, len)     ,len
#define __NR32ATRF0_setrlimit                  "%#Ix"
#define __NR32ATRA0_setrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NR32ATRF1_setrlimit                  "%p"
#define __NR32ATRA1_setrlimit(resource, rlimits) ,rlimits
#define __NR32ATRF0_getrlimit                  "%#Ix"
#define __NR32ATRA0_getrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NR32ATRF1_getrlimit                  "%p"
#define __NR32ATRA1_getrlimit(resource, rlimits) ,rlimits
#define __NR32ATRF0_getrusage                  "%Id"
#define __NR32ATRA0_getrusage(who, usage)      ,(intptr_t)(who)
#define __NR32ATRF1_getrusage                  "%p"
#define __NR32ATRA1_getrusage(who, usage)      ,usage
#define __NR32ATRF0_gettimeofday               "%p"
#define __NR32ATRA0_gettimeofday(tv, tz)       ,tv
#define __NR32ATRF1_gettimeofday               "%p"
#define __NR32ATRA1_gettimeofday(tv, tz)       ,tz
#define __NR32ATRF0_settimeofday               "%p"
#define __NR32ATRA0_settimeofday(tv, tz)       ,tv
#define __NR32ATRF1_settimeofday               "%p"
#define __NR32ATRA1_settimeofday(tv, tz)       ,tz
#define __NR32ATRF0_getgroups                  "%Iu"
#define __NR32ATRA0_getgroups(size, list)      ,size
#define __NR32ATRF1_getgroups                  "%p"
#define __NR32ATRA1_getgroups(size, list)      ,list
#define __NR32ATRF0_setgroups                  "%Iu"
#define __NR32ATRA0_setgroups(count, groups)   ,count
#define __NR32ATRF1_setgroups                  "%p"
#define __NR32ATRA1_setgroups(count, groups)   ,groups
#define __NR32ATRF0_select                     "%Iu"
#define __NR32ATRA0_select(nfds, readfds, writefds, exceptfds, timeout) ,nfds
#define __NR32ATRF1_select                     "%p"
#define __NR32ATRA1_select(nfds, readfds, writefds, exceptfds, timeout) ,readfds
#define __NR32ATRF2_select                     "%p"
#define __NR32ATRA2_select(nfds, readfds, writefds, exceptfds, timeout) ,writefds
#define __NR32ATRF3_select                     "%p"
#define __NR32ATRA3_select(nfds, readfds, writefds, exceptfds, timeout) ,exceptfds
#define __NR32ATRF4_select                     "%p"
#define __NR32ATRA4_select(nfds, readfds, writefds, exceptfds, timeout) ,timeout
#define __NR32ATRF0_symlink                    "%q"
#define __NR32ATRA0_symlink(link_text, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NR32ATRF1_symlink                    "%q"
#define __NR32ATRA1_symlink(link_text, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF0_linux_oldlstat             "%q"
#define __NR32ATRA0_linux_oldlstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_oldlstat             "%p"
#define __NR32ATRA1_linux_oldlstat(filename, statbuf) ,statbuf
#define __NR32ATRF0_readlink                   "%q"
#define __NR32ATRA0_readlink(path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_readlink                   "%p"
#define __NR32ATRA1_readlink(path, buf, buflen) ,buf
#define __NR32ATRF2_readlink                   "%Iu"
#define __NR32ATRA2_readlink(path, buf, buflen) ,buflen
#define __NR32ATRF0_swapon                     "%q"
#define __NR32ATRA0_swapon(pathname, swapflags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF1_swapon                     "%#Ix=%s%s%s"
#define __NR32ATRA1_swapon(pathname, swapflags) ,(uintptr_t)(swapflags),(swapflags) & SWAP_FLAG_PREFER ? "SWAP_FLAG_PREFER" : "" \
                                                ,((swapflags) & SWAP_FLAG_DISCARD) && ((swapflags) & (SWAP_FLAG_PREFER)) ? "|" : "",(swapflags) & SWAP_FLAG_DISCARD ? "SWAP_FLAG_DISCARD" : ""
#define __NR32ATRF0_reboot                     "%#Ix"
#define __NR32ATRA0_reboot(how)                ,(uintptr_t)(how)
#define __NR32ATRF0_readdir                    "%d"
#define __NR32ATRA0_readdir(fd, dirp, count)   ,(int)(fd)
#define __NR32ATRF1_readdir                    "%p"
#define __NR32ATRA1_readdir(fd, dirp, count)   ,dirp
#define __NR32ATRF2_readdir                    "%Iu"
#define __NR32ATRA2_readdir(fd, dirp, count)   ,count
#define __NR32ATRF0_mmap                       "%p"
#define __NR32ATRA0_mmap(addr, len, prot, flags, fd, offset) ,addr
#define __NR32ATRF1_mmap                       "%Iu"
#define __NR32ATRA1_mmap(addr, len, prot, flags, fd, offset) ,len
#define __NR32ATRF2_mmap                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                                             ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                                             ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                                             ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : "" \
                                                             ,((prot) & PROT_LOOSE) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM)) ? "|" : "",(prot) & PROT_LOOSE ? "PROT_LOOSE" : "" \
                                                             ,((prot) & PROT_SHARED) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE)) ? "|" : "",(prot) & PROT_SHARED ? "PROT_SHARED" : ""
#define __NR32ATRF3_mmap                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(flags),(flags) & MAP_SHARED ? "MAP_SHARED" : (flags) ? "" : "MAP_AUTOMATIC" \
                                                             ,((flags) & MAP_PRIVATE) && ((flags) & (MAP_SHARED)) ? "|" : "",(flags) & MAP_PRIVATE ? "MAP_PRIVATE" : "" \
                                                             ,((flags) & MAP_FIXED) && ((flags) & (MAP_SHARED|MAP_PRIVATE)) ? "|" : "",(flags) & MAP_FIXED ? "MAP_FIXED" : "" \
                                                             ,((flags) & MAP_ANON) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED)) ? "|" : "",(flags) & MAP_ANON ? "MAP_ANON" : "" \
                                                             ,((flags) & MAP_32BIT) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON)) ? "|" : "",(flags) & MAP_32BIT ? "MAP_32BIT" : "" \
                                                             ,((flags) & MAP_GROWSDOWN) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT)) ? "|" : "",(flags) & MAP_GROWSDOWN ? "MAP_GROWSDOWN" : "" \
                                                             ,((flags) & MAP_GROWSUP) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN)) ? "|" : "",(flags) & MAP_GROWSUP ? "MAP_GROWSUP" : "" \
                                                             ,((flags) & MAP_LOCKED) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP)) ? "|" : "",(flags) & MAP_LOCKED ? "MAP_LOCKED" : "" \
                                                             ,((flags) & MAP_NORESERVE) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED)) ? "|" : "",(flags) & MAP_NORESERVE ? "MAP_NORESERVE" : "" \
                                                             ,((flags) & MAP_POPULATE) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE)) ? "|" : "",(flags) & MAP_POPULATE ? "MAP_POPULATE" : "" \
                                                             ,((flags) & MAP_NONBLOCK) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE)) ? "|" : "",(flags) & MAP_NONBLOCK ? "MAP_NONBLOCK" : "" \
                                                             ,((flags) & MAP_STACK) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK)) ? "|" : "",(flags) & MAP_STACK ? "MAP_STACK" : "" \
                                                             ,((flags) & MAP_UNINITIALIZED) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK|MAP_STACK)) ? "|" : "",(flags) & MAP_UNINITIALIZED ? "MAP_UNINITIALIZED" : "" \
                                                             ,((flags) & MAP_DONT_MAP) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK|MAP_STACK|MAP_UNINITIALIZED)) ? "|" : "",(flags) & MAP_DONT_MAP ? "MAP_DONT_MAP" : "" \
                                                             ,((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK|MAP_STACK|MAP_UNINITIALIZED|MAP_DONT_MAP)) ? "|" : "",(flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : "" \
                                                             ,((flags) & MAP_OFFSET64_POINTER) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK|MAP_STACK|MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE)) ? "|" : "",(flags) & MAP_OFFSET64_POINTER ? "MAP_OFFSET64_POINTER" : ""
#define __NR32ATRF4_mmap                       "%d"
#define __NR32ATRA4_mmap(addr, len, prot, flags, fd, offset) ,(int)(fd)
#define __NR32ATRF5_mmap                       "%#Ix"
#define __NR32ATRA5_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(offset)
#define __NR32ATRF0_munmap                     "%p"
#define __NR32ATRA0_munmap(addr, len)          ,addr
#define __NR32ATRF1_munmap                     "%Iu"
#define __NR32ATRA1_munmap(addr, len)          ,len
#define __NR32ATRF0_truncate                   "%q"
#define __NR32ATRA0_truncate(filename, length) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_truncate                   "%#Ix"
#define __NR32ATRA1_truncate(filename, length) ,(uintptr_t)(length)
#define __NR32ATRF0_ftruncate                  "%d"
#define __NR32ATRA0_ftruncate(fd, length)      ,(int)(fd)
#define __NR32ATRF1_ftruncate                  "%#Ix"
#define __NR32ATRA1_ftruncate(fd, length)      ,(uintptr_t)(length)
#define __NR32ATRF0_fchmod                     "%d"
#define __NR32ATRA0_fchmod(fd, mode)           ,(int)(fd)
#define __NR32ATRF1_fchmod                     "%#Io"
#define __NR32ATRA1_fchmod(fd, mode)           ,(uintptr_t)(mode)
#define __NR32ATRF0_fchown                     "%d"
#define __NR32ATRA0_fchown(fd, owner, group)   ,(int)(fd)
#define __NR32ATRF1_fchown                     "%I16u"
#define __NR32ATRA1_fchown(fd, owner, group)   ,owner
#define __NR32ATRF2_fchown                     "%I16u"
#define __NR32ATRA2_fchown(fd, owner, group)   ,group
#define __NR32ATRF0_getpriority                "%#Ix"
#define __NR32ATRA0_getpriority(which, who)    ,(uintptr_t)(which)
#define __NR32ATRF1_getpriority                "%Iu"
#define __NR32ATRA1_getpriority(which, who)    ,(uintptr_t)(who)
#define __NR32ATRF0_setpriority                "%#Ix"
#define __NR32ATRA0_setpriority(which, who, value) ,(uintptr_t)(which)
#define __NR32ATRF1_setpriority                "%Iu"
#define __NR32ATRA1_setpriority(which, who, value) ,(uintptr_t)(who)
#define __NR32ATRF2_setpriority                "%#Ix"
#define __NR32ATRA2_setpriority(which, who, value) ,(uintptr_t)(value)
#define __NR32ATRF0_profil                     "%p"
#define __NR32ATRA0_profil(sample_buffer, size, offset, scale) ,sample_buffer
#define __NR32ATRF1_profil                     "%Iu"
#define __NR32ATRA1_profil(sample_buffer, size, offset, scale) ,size
#define __NR32ATRF2_profil                     "%Iu"
#define __NR32ATRA2_profil(sample_buffer, size, offset, scale) ,offset
#define __NR32ATRF3_profil                     "%#Ix"
#define __NR32ATRA3_profil(sample_buffer, size, offset, scale) ,(uintptr_t)(scale)
#define __NR32ATRF0_statfs                     "%q"
#define __NR32ATRA0_statfs(file, buf)          ,(validate_readable_opt(file,1),file)
#define __NR32ATRF1_statfs                     "%p"
#define __NR32ATRA1_statfs(file, buf)          ,buf
#define __NR32ATRF0_fstatfs                    "%d"
#define __NR32ATRA0_fstatfs(file, buf)         ,(int)(file)
#define __NR32ATRF1_fstatfs                    "%p"
#define __NR32ATRA1_fstatfs(file, buf)         ,buf
#define __NR32ATRF0_ioperm                     "%#Ix"
#define __NR32ATRA0_ioperm(from, num, turn_on) ,(uintptr_t)(from)
#define __NR32ATRF1_ioperm                     "%#Ix"
#define __NR32ATRA1_ioperm(from, num, turn_on) ,(uintptr_t)(num)
#define __NR32ATRF2_ioperm                     "%#Ix"
#define __NR32ATRA2_ioperm(from, num, turn_on) ,(uintptr_t)(turn_on)
#define __NR32ATRF0_socketcall                 "?"
#define __NR32ATRA0_socketcall(call, args)     /* nothing */
#define __NR32ATRF1_socketcall                 "%p"
#define __NR32ATRA1_socketcall(call, args)     ,args
#define __NR32ATRF0_syslog                     "%Iu"
#define __NR32ATRA0_syslog(level, str, len)    ,(uintptr_t)(level)
#define __NR32ATRF1_syslog                     "%$q"
#define __NR32ATRA1_syslog(level, str, len)    ,len,(validate_readable(str,len),str)
#define __NR32ATRF2_syslog                     "%Iu"
#define __NR32ATRA2_syslog(level, str, len)    ,len
#define __NR32ATRF0_setitimer                  "%#Ix"
#define __NR32ATRA0_setitimer(which, newval, oldval) ,(uintptr_t)(which)
#define __NR32ATRF1_setitimer                  "%p"
#define __NR32ATRA1_setitimer(which, newval, oldval) ,newval
#define __NR32ATRF2_setitimer                  "%p"
#define __NR32ATRA2_setitimer(which, newval, oldval) ,oldval
#define __NR32ATRF0_getitimer                  "%#Ix"
#define __NR32ATRA0_getitimer(which, curr_value) ,(uintptr_t)(which)
#define __NR32ATRF1_getitimer                  "%p"
#define __NR32ATRA1_getitimer(which, curr_value) ,curr_value
#define __NR32ATRF0_linux_stat32               "%q"
#define __NR32ATRA0_linux_stat32(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_stat32               "%p"
#define __NR32ATRA1_linux_stat32(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_lstat32              "%q"
#define __NR32ATRA0_linux_lstat32(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_lstat32              "%p"
#define __NR32ATRA1_linux_lstat32(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_fstat32              "%d"
#define __NR32ATRA0_linux_fstat32(fd, statbuf) ,(int)(fd)
#define __NR32ATRF1_linux_fstat32              "%p"
#define __NR32ATRA1_linux_fstat32(fd, statbuf) ,statbuf
#define __NR32ATRF0_olduname                   "%p"
#define __NR32ATRA0_olduname(name)             ,name
#define __NR32ATRF0_iopl                       "%#Ix"
#define __NR32ATRA0_iopl(level)                ,(uintptr_t)(level)
#define __NR32ATRF0_wait4                      "%Id"
#define __NR32ATRA0_wait4(pid, stat_loc, options, usage) ,(intptr_t)(pid)
#define __NR32ATRF1_wait4                      "%p"
#define __NR32ATRA1_wait4(pid, stat_loc, options, usage) ,stat_loc
#define __NR32ATRF2_wait4                      "%#Ix=%s%s%s%s%s%s%s"
#define __NR32ATRA2_wait4(pid, stat_loc, options, usage) ,(uintptr_t)(options),(options) & WNOHANG ? "WNOHANG" : "" \
                                                         ,((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "",(options) & WUNTRACED ? "WUNTRACED" : "" \
                                                         ,((options) & WCONTINUED) && ((options) & (WNOHANG|WUNTRACED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                         ,((options) & WNOWAIT) && ((options) & (WNOHANG|WUNTRACED|WCONTINUED)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR32ATRF3_wait4                      "%p"
#define __NR32ATRA3_wait4(pid, stat_loc, options, usage) ,usage
#define __NR32ATRF0_swapoff                    "%q"
#define __NR32ATRA0_swapoff(pathname)          ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF0_sysinfo                    "%p"
#define __NR32ATRA0_sysinfo(info)              ,info
#define __NR32ATRF0_fsync                      "%d"
#define __NR32ATRA0_fsync(fd)                  ,(int)(fd)
#define __NR32ATRF0_sigreturn                  "%p"
#define __NR32ATRA0_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_fpu
#define __NR32ATRF1_sigreturn                  "%#Ix"
#define __NR32ATRA1_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,(uintptr_t)(unused1)
#define __NR32ATRF2_sigreturn                  "%#Ix"
#define __NR32ATRA2_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,(uintptr_t)(unused2)
#define __NR32ATRF3_sigreturn                  "%p"
#define __NR32ATRA3_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_sigmask
#define __NR32ATRF4_sigreturn                  "%p"
#define __NR32ATRA4_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,sc_info
#define __NR32ATRF5_sigreturn                  "%p"
#define __NR32ATRA5_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_cpu
#define __NR32ATRF0_clone                      "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA0_clone(flags, child_stack, ptid, newtls, ctid) ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
                                                                  ,((flags) & CLONE_FS) && ((flags) & (CLONE_VM)) ? "|" : "",(flags) & CLONE_FS ? "CLONE_FS" : "" \
                                                                  ,((flags) & CLONE_FILES) && ((flags) & (CLONE_VM|CLONE_FS)) ? "|" : "",(flags) & CLONE_FILES ? "CLONE_FILES" : "" \
                                                                  ,((flags) & CLONE_SIGHAND) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES)) ? "|" : "",(flags) & CLONE_SIGHAND ? "CLONE_SIGHAND" : "" \
                                                                  ,((flags) & CLONE_PTRACE) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND)) ? "|" : "",(flags) & CLONE_PTRACE ? "CLONE_PTRACE" : "" \
                                                                  ,((flags) & CLONE_VFORK) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE)) ? "|" : "",(flags) & CLONE_VFORK ? "CLONE_VFORK" : "" \
                                                                  ,((flags) & CLONE_PARENT) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK)) ? "|" : "",(flags) & CLONE_PARENT ? "CLONE_PARENT" : "" \
                                                                  ,((flags) & CLONE_THREAD) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT)) ? "|" : "",(flags) & CLONE_THREAD ? "CLONE_THREAD" : "" \
                                                                  ,((flags) & CLONE_NEWNS) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD)) ? "|" : "",(flags) & CLONE_NEWNS ? "CLONE_NEWNS" : "" \
                                                                  ,((flags) & CLONE_SYSVSEM) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS)) ? "|" : "",(flags) & CLONE_SYSVSEM ? "CLONE_SYSVSEM" : "" \
                                                                  ,((flags) & CLONE_SETTLS) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM)) ? "|" : "",(flags) & CLONE_SETTLS ? "CLONE_SETTLS" : "" \
                                                                  ,((flags) & CLONE_PARENT_SETTID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS)) ? "|" : "",(flags) & CLONE_PARENT_SETTID ? "CLONE_PARENT_SETTID" : "" \
                                                                  ,((flags) & CLONE_CHILD_CLEARTID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID)) ? "|" : "",(flags) & CLONE_CHILD_CLEARTID ? "CLONE_CHILD_CLEARTID" : "" \
                                                                  ,((flags) & CLONE_DETACHED) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID)) ? "|" : "",(flags) & CLONE_DETACHED ? "CLONE_DETACHED" : "" \
                                                                  ,((flags) & CLONE_UNTRACED) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED)) ? "|" : "",(flags) & CLONE_UNTRACED ? "CLONE_UNTRACED" : "" \
                                                                  ,((flags) & CLONE_CHILD_SETTID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED)) ? "|" : "",(flags) & CLONE_CHILD_SETTID ? "CLONE_CHILD_SETTID" : "" \
                                                                  ,((flags) & CLONE_NEWUTS) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID)) ? "|" : "",(flags) & CLONE_NEWUTS ? "CLONE_NEWUTS" : "" \
                                                                  ,((flags) & CLONE_NEWIPC) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS)) ? "|" : "",(flags) & CLONE_NEWIPC ? "CLONE_NEWIPC" : "" \
                                                                  ,((flags) & CLONE_NEWUSER) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC)) ? "|" : "",(flags) & CLONE_NEWUSER ? "CLONE_NEWUSER" : "" \
                                                                  ,((flags) & CLONE_NEWPID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC|CLONE_NEWUSER)) ? "|" : "",(flags) & CLONE_NEWPID ? "CLONE_NEWPID" : "" \
                                                                  ,((flags) & CLONE_NEWNET) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC|CLONE_NEWUSER|CLONE_NEWPID)) ? "|" : "",(flags) & CLONE_NEWNET ? "CLONE_NEWNET" : "" \
                                                                  ,((flags) & CLONE_IO) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC|CLONE_NEWUSER|CLONE_NEWPID|CLONE_NEWNET)) ? "|" : "",(flags) & CLONE_IO ? "CLONE_IO" : ""
#define __NR32ATRF1_clone                      "%p"
#define __NR32ATRA1_clone(flags, child_stack, ptid, newtls, ctid) ,child_stack
#define __NR32ATRF2_clone                      "%p"
#define __NR32ATRA2_clone(flags, child_stack, ptid, newtls, ctid) ,ptid
#define __NR32ATRF3_clone                      "%p"
#define __NR32ATRA3_clone(flags, child_stack, ptid, newtls, ctid) ,newtls
#define __NR32ATRF4_clone                      "%p"
#define __NR32ATRA4_clone(flags, child_stack, ptid, newtls, ctid) ,ctid
#define __NR32ATRF0_setdomainname              "%q"
#define __NR32ATRA0_setdomainname(name, len)   ,(validate_readable_opt(name,1),name)
#define __NR32ATRF1_setdomainname              "%Iu"
#define __NR32ATRA1_setdomainname(name, len)   ,len
#define __NR32ATRF0_uname                      "%p"
#define __NR32ATRA0_uname(name)                ,name
#define __NR32ATRF0_modify_ldt                 "%#Ix"
#define __NR32ATRA0_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(func)
#define __NR32ATRF1_modify_ldt                 "%p"
#define __NR32ATRA1_modify_ldt(func, ptr, bytecount) ,ptr
#define __NR32ATRF2_modify_ldt                 "%#Ix"
#define __NR32ATRA2_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(bytecount)
#define __NR32ATRF0_mprotect                   "%p"
#define __NR32ATRA0_mprotect(addr, len, prot)  ,addr
#define __NR32ATRF1_mprotect                   "%Iu"
#define __NR32ATRA1_mprotect(addr, len, prot)  ,len
#define __NR32ATRF2_mprotect                   "%#Ix=%s%s%s%s%s%s%s"
#define __NR32ATRA2_mprotect(addr, len, prot)  ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                               ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                               ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                               ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : ""
#define __NR32ATRF0_sigprocmask                "%#Ix"
#define __NR32ATRA0_sigprocmask(how, set, oset) ,(uintptr_t)(how)
#define __NR32ATRF1_sigprocmask                "%p"
#define __NR32ATRA1_sigprocmask(how, set, oset) ,set
#define __NR32ATRF2_sigprocmask                "%p"
#define __NR32ATRA2_sigprocmask(how, set, oset) ,oset
#define __NR32ATRF0_getpgid                    "%Id"
#define __NR32ATRA0_getpgid(pid)               ,(intptr_t)(pid)
#define __NR32ATRF0_fchdir                     "%d"
#define __NR32ATRA0_fchdir(fd)                 ,(int)(fd)
#define __NR32ATRF0_setfsuid                   "%I16u"
#define __NR32ATRA0_setfsuid(uid)              ,uid
#define __NR32ATRF0_setfsgid                   "%I16u"
#define __NR32ATRA0_setfsgid(gid)              ,gid
#define __NR32ATRF0__llseek                    "%d"
#define __NR32ATRA0__llseek(fd, offset, result, whence) ,(int)(fd)
#define __NR32ATRF1__llseek                    "%I64d"
#define __NR32ATRA1__llseek(fd, offset, result, whence) ,offset
#define __NR32ATRF2__llseek                    "%p"
#define __NR32ATRA2__llseek(fd, offset, result, whence) ,result
#define __NR32ATRF3__llseek                    "%#Ix=%s"
#define __NR32ATRA3__llseek(fd, offset, result, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NR32ATRF0_getdents                   "%d"
#define __NR32ATRA0_getdents(fd, dirp, count)  ,(int)(fd)
#define __NR32ATRF1_getdents                   "%p"
#define __NR32ATRA1_getdents(fd, dirp, count)  ,dirp
#define __NR32ATRF2_getdents                   "%Iu"
#define __NR32ATRA2_getdents(fd, dirp, count)  ,count
#define __NR32ATRF0_flock                      "%d"
#define __NR32ATRA0_flock(fd, operation)       ,(int)(fd)
#define __NR32ATRF1_flock                      "%#Ix"
#define __NR32ATRA1_flock(fd, operation)       ,(uintptr_t)(operation)
#define __NR32ATRF0_msync                      "%p"
#define __NR32ATRA0_msync(addr, len, flags)    ,addr
#define __NR32ATRF1_msync                      "%Iu"
#define __NR32ATRA1_msync(addr, len, flags)    ,len
#define __NR32ATRF2_msync                      "%#Ix"
#define __NR32ATRA2_msync(addr, len, flags)    ,(uintptr_t)(flags)
#define __NR32ATRF0_readv                      "%d"
#define __NR32ATRA0_readv(fd, iovec, count)    ,(int)(fd)
#define __NR32ATRF1_readv                      "%p"
#define __NR32ATRA1_readv(fd, iovec, count)    ,iovec
#define __NR32ATRF2_readv                      "%Iu"
#define __NR32ATRA2_readv(fd, iovec, count)    ,count
#define __NR32ATRF0_writev                     "%d"
#define __NR32ATRA0_writev(fd, iovec, count)   ,(int)(fd)
#define __NR32ATRF1_writev                     "%p"
#define __NR32ATRA1_writev(fd, iovec, count)   ,iovec
#define __NR32ATRF2_writev                     "%Iu"
#define __NR32ATRA2_writev(fd, iovec, count)   ,count
#define __NR32ATRF0_getsid                     "%Id"
#define __NR32ATRA0_getsid(pid)                ,(intptr_t)(pid)
#define __NR32ATRF0_fdatasync                  "%d"
#define __NR32ATRA0_fdatasync(fd)              ,(int)(fd)
#define __NR32ATRF0_mlock                      "%p"
#define __NR32ATRA0_mlock(addr, len)           ,addr
#define __NR32ATRF1_mlock                      "%Iu"
#define __NR32ATRA1_mlock(addr, len)           ,len
#define __NR32ATRF0_munlock                    "%p"
#define __NR32ATRA0_munlock(addr, len)         ,addr
#define __NR32ATRF1_munlock                    "%Iu"
#define __NR32ATRA1_munlock(addr, len)         ,len
#define __NR32ATRF0_mlockall                   "%#Ix"
#define __NR32ATRA0_mlockall(flags)            ,(uintptr_t)(flags)
#define __NR32ATRF0_sched_setparam             "%Id"
#define __NR32ATRA0_sched_setparam(pid, param) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_setparam             "%p"
#define __NR32ATRA1_sched_setparam(pid, param) ,param
#define __NR32ATRF0_sched_getparam             "%Id"
#define __NR32ATRA0_sched_getparam(pid, param) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_getparam             "%p"
#define __NR32ATRA1_sched_getparam(pid, param) ,param
#define __NR32ATRF0_sched_setscheduler         "%Id"
#define __NR32ATRA0_sched_setscheduler(pid, policy, param) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_setscheduler         "%#Ix"
#define __NR32ATRA1_sched_setscheduler(pid, policy, param) ,(uintptr_t)(policy)
#define __NR32ATRF2_sched_setscheduler         "%p"
#define __NR32ATRA2_sched_setscheduler(pid, policy, param) ,param
#define __NR32ATRF0_sched_getscheduler         "%Id"
#define __NR32ATRA0_sched_getscheduler(pid)    ,(intptr_t)(pid)
#define __NR32ATRF0_sched_get_priority_max     "%#Ix"
#define __NR32ATRA0_sched_get_priority_max(algorithm) ,(uintptr_t)(algorithm)
#define __NR32ATRF0_sched_get_priority_min     "%#Ix"
#define __NR32ATRA0_sched_get_priority_min(algorithm) ,(uintptr_t)(algorithm)
#define __NR32ATRF0_sched_rr_get_interval      "%Id"
#define __NR32ATRA0_sched_rr_get_interval(pid, tms) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_rr_get_interval      "%p"
#define __NR32ATRA1_sched_rr_get_interval(pid, tms) ,tms
#define __NR32ATRF0_nanosleep                  "%p"
#define __NR32ATRA0_nanosleep(req, rem)        ,req
#define __NR32ATRF1_nanosleep                  "%p"
#define __NR32ATRA1_nanosleep(req, rem)        ,rem
#define __NR32ATRF0_mremap                     "%p"
#define __NR32ATRA0_mremap(addr, old_len, new_len, flags, new_address) ,addr
#define __NR32ATRF1_mremap                     "%Iu"
#define __NR32ATRA1_mremap(addr, old_len, new_len, flags, new_address) ,old_len
#define __NR32ATRF2_mremap                     "%Iu"
#define __NR32ATRA2_mremap(addr, old_len, new_len, flags, new_address) ,new_len
#define __NR32ATRF3_mremap                     "%#Ix=%s%s%s"
#define __NR32ATRA3_mremap(addr, old_len, new_len, flags, new_address) ,(uintptr_t)(flags),(flags) & MREMAP_MAYMOVE ? "MREMAP_MAYMOVE" : "" \
                                                                       ,((flags) & MREMAP_FIXED) && ((flags) & (MREMAP_MAYMOVE)) ? "|" : "",(flags) & MREMAP_FIXED ? "MREMAP_FIXED" : ""
#define __NR32ATRF4_mremap                     "%p"
#define __NR32ATRA4_mremap(addr, old_len, new_len, flags, new_address) ,new_address
#define __NR32ATRF0_setresuid                  "%I16u"
#define __NR32ATRA0_setresuid(ruid, euid, suid) ,ruid
#define __NR32ATRF1_setresuid                  "%I16u"
#define __NR32ATRA1_setresuid(ruid, euid, suid) ,euid
#define __NR32ATRF2_setresuid                  "%I16u"
#define __NR32ATRA2_setresuid(ruid, euid, suid) ,suid
#define __NR32ATRF0_getresuid                  "%p"
#define __NR32ATRA0_getresuid(ruid, euid, suid) ,ruid
#define __NR32ATRF1_getresuid                  "%p"
#define __NR32ATRA1_getresuid(ruid, euid, suid) ,euid
#define __NR32ATRF2_getresuid                  "%p"
#define __NR32ATRA2_getresuid(ruid, euid, suid) ,suid
#define __NR32ATRF0_poll                       "%p"
#define __NR32ATRA0_poll(fds, nfds, timeout)   ,fds
#define __NR32ATRF1_poll                       "%Iu"
#define __NR32ATRA1_poll(fds, nfds, timeout)   ,nfds
#define __NR32ATRF2_poll                       "%Id"
#define __NR32ATRA2_poll(fds, nfds, timeout)   ,(intptr_t)(timeout)
#define __NR32ATRF0_setresgid                  "%I16u"
#define __NR32ATRA0_setresgid(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_setresgid                  "%I16u"
#define __NR32ATRA1_setresgid(rgid, egid, sgid) ,egid
#define __NR32ATRF2_setresgid                  "%I16u"
#define __NR32ATRA2_setresgid(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_getresgid                  "%p"
#define __NR32ATRA0_getresgid(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_getresgid                  "%p"
#define __NR32ATRA1_getresgid(rgid, egid, sgid) ,egid
#define __NR32ATRF2_getresgid                  "%p"
#define __NR32ATRA2_getresgid(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_rt_sigaction               "%#Ix"
#define __NR32ATRA0_rt_sigaction(signo, act, oact, sigsetsize) ,(uintptr_t)(signo)
#define __NR32ATRF1_rt_sigaction               "%p"
#define __NR32ATRA1_rt_sigaction(signo, act, oact, sigsetsize) ,act
#define __NR32ATRF2_rt_sigaction               "%p"
#define __NR32ATRA2_rt_sigaction(signo, act, oact, sigsetsize) ,oact
#define __NR32ATRF3_rt_sigaction               "%Iu"
#define __NR32ATRA3_rt_sigaction(signo, act, oact, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigprocmask             "%#Ix"
#define __NR32ATRA0_rt_sigprocmask(how, set, oset, sigsetsize) ,(uintptr_t)(how)
#define __NR32ATRF1_rt_sigprocmask             "%p"
#define __NR32ATRA1_rt_sigprocmask(how, set, oset, sigsetsize) ,set
#define __NR32ATRF2_rt_sigprocmask             "%p"
#define __NR32ATRA2_rt_sigprocmask(how, set, oset, sigsetsize) ,oset
#define __NR32ATRF3_rt_sigprocmask             "%Iu"
#define __NR32ATRA3_rt_sigprocmask(how, set, oset, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigpending              "%p"
#define __NR32ATRA0_rt_sigpending(set, sigsetsize) ,set
#define __NR32ATRF1_rt_sigpending              "%Iu"
#define __NR32ATRA1_rt_sigpending(set, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigtimedwait            "%p"
#define __NR32ATRA0_rt_sigtimedwait(set, info, timeout, sigsetsize) ,set
#define __NR32ATRF1_rt_sigtimedwait            "%p"
#define __NR32ATRA1_rt_sigtimedwait(set, info, timeout, sigsetsize) ,info
#define __NR32ATRF2_rt_sigtimedwait            "%p"
#define __NR32ATRA2_rt_sigtimedwait(set, info, timeout, sigsetsize) ,timeout
#define __NR32ATRF3_rt_sigtimedwait            "%Iu"
#define __NR32ATRA3_rt_sigtimedwait(set, info, timeout, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigqueueinfo            "%Id"
#define __NR32ATRA0_rt_sigqueueinfo(tgid, signo, uinfo) ,(intptr_t)(tgid)
#define __NR32ATRF1_rt_sigqueueinfo            "%#Ix"
#define __NR32ATRA1_rt_sigqueueinfo(tgid, signo, uinfo) ,(uintptr_t)(signo)
#define __NR32ATRF2_rt_sigqueueinfo            "%p"
#define __NR32ATRA2_rt_sigqueueinfo(tgid, signo, uinfo) ,uinfo
#define __NR32ATRF0_rt_sigsuspend              "%p"
#define __NR32ATRA0_rt_sigsuspend(set, sigsetsize) ,set
#define __NR32ATRF1_rt_sigsuspend              "%Iu"
#define __NR32ATRA1_rt_sigsuspend(set, sigsetsize) ,sigsetsize
#define __NR32ATRF0_pread64                    "%d"
#define __NR32ATRA0_pread64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NR32ATRF1_pread64                    "%p"
#define __NR32ATRA1_pread64(fd, buf, bufsize, offset) ,buf
#define __NR32ATRF2_pread64                    "%Iu"
#define __NR32ATRA2_pread64(fd, buf, bufsize, offset) ,bufsize
#define __NR32ATRF3_pread64                    "%I64u"
#define __NR32ATRA3_pread64(fd, buf, bufsize, offset) ,offset
#define __NR32ATRF0_pwrite64                   "%d"
#define __NR32ATRA0_pwrite64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NR32ATRF1_pwrite64                   "%p"
#define __NR32ATRA1_pwrite64(fd, buf, bufsize, offset) ,buf
#define __NR32ATRF2_pwrite64                   "%Iu"
#define __NR32ATRA2_pwrite64(fd, buf, bufsize, offset) ,bufsize
#define __NR32ATRF3_pwrite64                   "%I64u"
#define __NR32ATRA3_pwrite64(fd, buf, bufsize, offset) ,offset
#define __NR32ATRF0_chown                      "%q"
#define __NR32ATRA0_chown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_chown                      "%I16u"
#define __NR32ATRA1_chown(filename, owner, group) ,owner
#define __NR32ATRF2_chown                      "%I16u"
#define __NR32ATRA2_chown(filename, owner, group) ,group
#define __NR32ATRF0_getcwd                     "%p"
#define __NR32ATRA0_getcwd(buf, size)          ,buf
#define __NR32ATRF1_getcwd                     "%Iu"
#define __NR32ATRA1_getcwd(buf, size)          ,size
#define __NR32ATRF0_sigaltstack                "%p"
#define __NR32ATRA0_sigaltstack(ss, oss)       ,ss
#define __NR32ATRF1_sigaltstack                "%p"
#define __NR32ATRA1_sigaltstack(ss, oss)       ,oss
#define __NR32ATRF0_sendfile                   "%d"
#define __NR32ATRA0_sendfile(out_fd, in_fd, offset, count) ,(int)(out_fd)
#define __NR32ATRF1_sendfile                   "%d"
#define __NR32ATRA1_sendfile(out_fd, in_fd, offset, count) ,(int)(in_fd)
#define __NR32ATRF2_sendfile                   "%p"
#define __NR32ATRA2_sendfile(out_fd, in_fd, offset, count) ,offset
#define __NR32ATRF3_sendfile                   "%Iu"
#define __NR32ATRA3_sendfile(out_fd, in_fd, offset, count) ,count
#define __NR32ATRF0_mmap2                      "%p"
#define __NR32ATRA0_mmap2(addr, len, prot, flags, fd, pgoffset) ,addr
#define __NR32ATRF1_mmap2                      "%Iu"
#define __NR32ATRA1_mmap2(addr, len, prot, flags, fd, pgoffset) ,len
#define __NR32ATRF2_mmap2                      "%#Ix"
#define __NR32ATRA2_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(prot)
#define __NR32ATRF3_mmap2                      "%#Ix"
#define __NR32ATRA3_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(flags)
#define __NR32ATRF4_mmap2                      "%d"
#define __NR32ATRA4_mmap2(addr, len, prot, flags, fd, pgoffset) ,(int)(fd)
#define __NR32ATRF5_mmap2                      "%#Ix"
#define __NR32ATRA5_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(pgoffset)
#define __NR32ATRF0_truncate64                 "%q"
#define __NR32ATRA0_truncate64(filename, length) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_truncate64                 "%I64u"
#define __NR32ATRA1_truncate64(filename, length) ,length
#define __NR32ATRF0_ftruncate64                "%d"
#define __NR32ATRA0_ftruncate64(fd, length)    ,(int)(fd)
#define __NR32ATRF1_ftruncate64                "%I64u"
#define __NR32ATRA1_ftruncate64(fd, length)    ,length
#define __NR32ATRF0_linux_stat64               "%q"
#define __NR32ATRA0_linux_stat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_stat64               "%p"
#define __NR32ATRA1_linux_stat64(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_lstat64              "%q"
#define __NR32ATRA0_linux_lstat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_lstat64              "%p"
#define __NR32ATRA1_linux_lstat64(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_fstat64              "%d"
#define __NR32ATRA0_linux_fstat64(fd, statbuf) ,(int)(fd)
#define __NR32ATRF1_linux_fstat64              "%p"
#define __NR32ATRA1_linux_fstat64(fd, statbuf) ,statbuf
#define __NR32ATRF0_lchown32                   "%q"
#define __NR32ATRA0_lchown32(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_lchown32                   "%I32u"
#define __NR32ATRA1_lchown32(filename, owner, group) ,owner
#define __NR32ATRF2_lchown32                   "%I32u"
#define __NR32ATRA2_lchown32(filename, owner, group) ,group
#define __NR32ATRF0_setreuid32                 "%I32u"
#define __NR32ATRA0_setreuid32(ruid, euid)     ,ruid
#define __NR32ATRF1_setreuid32                 "%I32u"
#define __NR32ATRA1_setreuid32(ruid, euid)     ,euid
#define __NR32ATRF0_setregid32                 "%I32u"
#define __NR32ATRA0_setregid32(rgid, egid)     ,rgid
#define __NR32ATRF1_setregid32                 "%I32u"
#define __NR32ATRA1_setregid32(rgid, egid)     ,egid
#define __NR32ATRF0_getgroups32                "%Iu"
#define __NR32ATRA0_getgroups32(size, list)    ,size
#define __NR32ATRF1_getgroups32                "%p"
#define __NR32ATRA1_getgroups32(size, list)    ,list
#define __NR32ATRF0_setgroups32                "%Iu"
#define __NR32ATRA0_setgroups32(count, groups) ,count
#define __NR32ATRF1_setgroups32                "%p"
#define __NR32ATRA1_setgroups32(count, groups) ,groups
#define __NR32ATRF0_fchown32                   "%d"
#define __NR32ATRA0_fchown32(fd, owner, group) ,(int)(fd)
#define __NR32ATRF1_fchown32                   "%I32u"
#define __NR32ATRA1_fchown32(fd, owner, group) ,owner
#define __NR32ATRF2_fchown32                   "%I32u"
#define __NR32ATRA2_fchown32(fd, owner, group) ,group
#define __NR32ATRF0_setresuid32                "%I32u"
#define __NR32ATRA0_setresuid32(ruid, euid, suid) ,ruid
#define __NR32ATRF1_setresuid32                "%I32u"
#define __NR32ATRA1_setresuid32(ruid, euid, suid) ,euid
#define __NR32ATRF2_setresuid32                "%I32u"
#define __NR32ATRA2_setresuid32(ruid, euid, suid) ,suid
#define __NR32ATRF0_getresuid32                "%p"
#define __NR32ATRA0_getresuid32(ruid, euid, suid) ,ruid
#define __NR32ATRF1_getresuid32                "%p"
#define __NR32ATRA1_getresuid32(ruid, euid, suid) ,euid
#define __NR32ATRF2_getresuid32                "%p"
#define __NR32ATRA2_getresuid32(ruid, euid, suid) ,suid
#define __NR32ATRF0_setresgid32                "%I32u"
#define __NR32ATRA0_setresgid32(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_setresgid32                "%I32u"
#define __NR32ATRA1_setresgid32(rgid, egid, sgid) ,egid
#define __NR32ATRF2_setresgid32                "%I32u"
#define __NR32ATRA2_setresgid32(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_getresgid32                "%p"
#define __NR32ATRA0_getresgid32(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_getresgid32                "%p"
#define __NR32ATRA1_getresgid32(rgid, egid, sgid) ,egid
#define __NR32ATRF2_getresgid32                "%p"
#define __NR32ATRA2_getresgid32(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_chown32                    "%q"
#define __NR32ATRA0_chown32(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_chown32                    "%I32u"
#define __NR32ATRA1_chown32(filename, owner, group) ,owner
#define __NR32ATRF2_chown32                    "%I32u"
#define __NR32ATRA2_chown32(filename, owner, group) ,group
#define __NR32ATRF0_setuid32                   "%I32u"
#define __NR32ATRA0_setuid32(uid)              ,uid
#define __NR32ATRF0_setgid32                   "%I32u"
#define __NR32ATRA0_setgid32(gid)              ,gid
#define __NR32ATRF0_setfsuid32                 "%I32u"
#define __NR32ATRA0_setfsuid32(uid)            ,uid
#define __NR32ATRF0_setfsgid32                 "%I32u"
#define __NR32ATRA0_setfsgid32(gid)            ,gid
#define __NR32ATRF0_mincore                    "%p"
#define __NR32ATRA0_mincore(start, len, vec)   ,start
#define __NR32ATRF1_mincore                    "%Iu"
#define __NR32ATRA1_mincore(start, len, vec)   ,len
#define __NR32ATRF2_mincore                    "%p"
#define __NR32ATRA2_mincore(start, len, vec)   ,vec
#define __NR32ATRF0_madvise                    "%p"
#define __NR32ATRA0_madvise(addr, len, advice) ,addr
#define __NR32ATRF1_madvise                    "%Iu"
#define __NR32ATRA1_madvise(addr, len, advice) ,len
#define __NR32ATRF2_madvise                    "%#Ix"
#define __NR32ATRA2_madvise(addr, len, advice) ,(uintptr_t)(advice)
#define __NR32ATRF0_getdents64                 "%d"
#define __NR32ATRA0_getdents64(fd, dirp, count) ,(int)(fd)
#define __NR32ATRF1_getdents64                 "%p"
#define __NR32ATRA1_getdents64(fd, dirp, count) ,dirp
#define __NR32ATRF2_getdents64                 "%Iu"
#define __NR32ATRA2_getdents64(fd, dirp, count) ,count
#define __NR32ATRF0_fcntl64                    "%d"
#define __NR32ATRA0_fcntl64(fd, command, arg)  ,(int)(fd)
#define __NR32ATRF1_fcntl64                    "%#Ix"
#define __NR32ATRA1_fcntl64(fd, command, arg)  ,(uintptr_t)(command)
#define __NR32ATRF2_fcntl64                    "%p"
#define __NR32ATRA2_fcntl64(fd, command, arg)  ,arg
#define __NR32ATRF0_readahead                  "%d"
#define __NR32ATRA0_readahead(fd, offset, count) ,(int)(fd)
#define __NR32ATRF1_readahead                  "%I64u"
#define __NR32ATRA1_readahead(fd, offset, count) ,offset
#define __NR32ATRF2_readahead                  "%Iu"
#define __NR32ATRA2_readahead(fd, offset, count) ,count
#define __NR32ATRF0_setxattr                   "%q"
#define __NR32ATRA0_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_setxattr                   "%q"
#define __NR32ATRA1_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_setxattr                   "%p"
#define __NR32ATRA2_setxattr(path, name, buf, bufsize, flags) ,buf
#define __NR32ATRF3_setxattr                   "%Iu"
#define __NR32ATRA3_setxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NR32ATRF4_setxattr                   "%#Ix"
#define __NR32ATRA4_setxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_lsetxattr                  "%q"
#define __NR32ATRA0_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_lsetxattr                  "%q"
#define __NR32ATRA1_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_lsetxattr                  "%p"
#define __NR32ATRA2_lsetxattr(path, name, buf, bufsize, flags) ,buf
#define __NR32ATRF3_lsetxattr                  "%Iu"
#define __NR32ATRA3_lsetxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NR32ATRF4_lsetxattr                  "%#Ix"
#define __NR32ATRA4_lsetxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_fsetxattr                  "%d"
#define __NR32ATRA0_fsetxattr(fd, name, buf, bufsize, flags) ,(int)(fd)
#define __NR32ATRF1_fsetxattr                  "%q"
#define __NR32ATRA1_fsetxattr(fd, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_fsetxattr                  "%p"
#define __NR32ATRA2_fsetxattr(fd, name, buf, bufsize, flags) ,buf
#define __NR32ATRF3_fsetxattr                  "%Iu"
#define __NR32ATRA3_fsetxattr(fd, name, buf, bufsize, flags) ,bufsize
#define __NR32ATRF4_fsetxattr                  "%#Ix"
#define __NR32ATRA4_fsetxattr(fd, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_getxattr                   "%q"
#define __NR32ATRA0_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_getxattr                   "%q"
#define __NR32ATRA1_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_getxattr                   "%p"
#define __NR32ATRA2_getxattr(path, name, buf, bufsize) ,buf
#define __NR32ATRF3_getxattr                   "%Iu"
#define __NR32ATRA3_getxattr(path, name, buf, bufsize) ,bufsize
#define __NR32ATRF0_lgetxattr                  "%q"
#define __NR32ATRA0_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_lgetxattr                  "%q"
#define __NR32ATRA1_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_lgetxattr                  "%p"
#define __NR32ATRA2_lgetxattr(path, name, buf, bufsize) ,buf
#define __NR32ATRF3_lgetxattr                  "%Iu"
#define __NR32ATRA3_lgetxattr(path, name, buf, bufsize) ,bufsize
#define __NR32ATRF0_fgetxattr                  "%d"
#define __NR32ATRA0_fgetxattr(fd, name, buf, bufsize) ,(int)(fd)
#define __NR32ATRF1_fgetxattr                  "%q"
#define __NR32ATRA1_fgetxattr(fd, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_fgetxattr                  "%p"
#define __NR32ATRA2_fgetxattr(fd, name, buf, bufsize) ,buf
#define __NR32ATRF3_fgetxattr                  "%Iu"
#define __NR32ATRA3_fgetxattr(fd, name, buf, bufsize) ,bufsize
#define __NR32ATRF0_listxattr                  "%q"
#define __NR32ATRA0_listxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_listxattr                  "%p"
#define __NR32ATRA1_listxattr(path, listbuf, listbufsize) ,listbuf
#define __NR32ATRF2_listxattr                  "%Iu"
#define __NR32ATRA2_listxattr(path, listbuf, listbufsize) ,listbufsize
#define __NR32ATRF0_llistxattr                 "%q"
#define __NR32ATRA0_llistxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_llistxattr                 "%p"
#define __NR32ATRA1_llistxattr(path, listbuf, listbufsize) ,listbuf
#define __NR32ATRF2_llistxattr                 "%Iu"
#define __NR32ATRA2_llistxattr(path, listbuf, listbufsize) ,listbufsize
#define __NR32ATRF0_flistxattr                 "%d"
#define __NR32ATRA0_flistxattr(fd, listbuf, listbufsize) ,(int)(fd)
#define __NR32ATRF1_flistxattr                 "%p"
#define __NR32ATRA1_flistxattr(fd, listbuf, listbufsize) ,listbuf
#define __NR32ATRF2_flistxattr                 "%Iu"
#define __NR32ATRA2_flistxattr(fd, listbuf, listbufsize) ,listbufsize
#define __NR32ATRF0_removexattr                "%q"
#define __NR32ATRA0_removexattr(path, name)    ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_removexattr                "%q"
#define __NR32ATRA1_removexattr(path, name)    ,(validate_readable_opt(name,1),name)
#define __NR32ATRF0_lremovexattr               "%q"
#define __NR32ATRA0_lremovexattr(path, name)   ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_lremovexattr               "%q"
#define __NR32ATRA1_lremovexattr(path, name)   ,(validate_readable_opt(name,1),name)
#define __NR32ATRF0_fremovexattr               "?"
#define __NR32ATRA0_fremovexattr(fd, name)     /* nothing */
#define __NR32ATRF1_fremovexattr               "%q"
#define __NR32ATRA1_fremovexattr(fd, name)     ,(validate_readable_opt(name,1),name)
#define __NR32ATRF0_tkill                      "%Id"
#define __NR32ATRA0_tkill(tid, signo)          ,(intptr_t)(tid)
#define __NR32ATRF1_tkill                      "%#Ix"
#define __NR32ATRA1_tkill(tid, signo)          ,(uintptr_t)(signo)
#define __NR32ATRF0_sendfile64                 "%d"
#define __NR32ATRA0_sendfile64(out_fd, in_fd, offset, count) ,(int)(out_fd)
#define __NR32ATRF1_sendfile64                 "%d"
#define __NR32ATRA1_sendfile64(out_fd, in_fd, offset, count) ,(int)(in_fd)
#define __NR32ATRF2_sendfile64                 "%p"
#define __NR32ATRA2_sendfile64(out_fd, in_fd, offset, count) ,offset
#define __NR32ATRF3_sendfile64                 "%Iu"
#define __NR32ATRA3_sendfile64(out_fd, in_fd, offset, count) ,count
#define __NR32ATRF0_futex                      "%p"
#define __NR32ATRA0_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr
#define __NR32ATRF1_futex                      "%#Ix"
#define __NR32ATRA1_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,(uintptr_t)(futex_op)
#define __NR32ATRF2_futex                      "%I32u"
#define __NR32ATRA2_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val
#define __NR32ATRF3_futex                      "%p"
#define __NR32ATRA3_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,timeout_or_val2
#define __NR32ATRF4_futex                      "%p"
#define __NR32ATRA4_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr2
#define __NR32ATRF5_futex                      "%I32u"
#define __NR32ATRA5_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val3
#define __NR32ATRF0_sched_setaffinity          "%Id"
#define __NR32ATRA0_sched_setaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_setaffinity          "%Iu"
#define __NR32ATRA1_sched_setaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NR32ATRF2_sched_setaffinity          "%p"
#define __NR32ATRA2_sched_setaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NR32ATRF0_sched_getaffinity          "%Id"
#define __NR32ATRA0_sched_getaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_getaffinity          "%Iu"
#define __NR32ATRA1_sched_getaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NR32ATRF2_sched_getaffinity          "%p"
#define __NR32ATRA2_sched_getaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NR32ATRF0_exit_group                 "%Iu"
#define __NR32ATRA0_exit_group(exit_code)      ,(uintptr_t)(exit_code)
#define __NR32ATRF0_epoll_create               "%#Ix"
#define __NR32ATRA0_epoll_create(size)         ,(uintptr_t)(size)
#define __NR32ATRF0_epoll_ctl                  "%d"
#define __NR32ATRA0_epoll_ctl(epfd, op, fd, event) ,(int)(epfd)
#define __NR32ATRF1_epoll_ctl                  "%#Ix=%s"
#define __NR32ATRA1_epoll_ctl(epfd, op, fd, event) ,(op),(op) == EPOLL_CTL_ADD ? "EPOLL_CTL_ADD" : (op) == EPOLL_CTL_DEL ? "EPOLL_CTL_DEL" : (op) == EPOLL_CTL_MOD ? "EPOLL_CTL_MOD" : "?"
#define __NR32ATRF2_epoll_ctl                  "%d"
#define __NR32ATRA2_epoll_ctl(epfd, op, fd, event) ,(int)(fd)
#define __NR32ATRF3_epoll_ctl                  "%p"
#define __NR32ATRA3_epoll_ctl(epfd, op, fd, event) ,event
#define __NR32ATRF0_epoll_wait                 "%d"
#define __NR32ATRA0_epoll_wait(epfd, events, maxevents, timeout) ,(int)(epfd)
#define __NR32ATRF1_epoll_wait                 "%p"
#define __NR32ATRA1_epoll_wait(epfd, events, maxevents, timeout) ,events
#define __NR32ATRF2_epoll_wait                 "%#Ix"
#define __NR32ATRA2_epoll_wait(epfd, events, maxevents, timeout) ,(uintptr_t)(maxevents)
#define __NR32ATRF3_epoll_wait                 "%Id"
#define __NR32ATRA3_epoll_wait(epfd, events, maxevents, timeout) ,(intptr_t)(timeout)
#define __NR32ATRF0_remap_file_pages           "%p"
#define __NR32ATRA0_remap_file_pages(start, size, prot, pgoff, flags) ,start
#define __NR32ATRF1_remap_file_pages           "%Iu"
#define __NR32ATRA1_remap_file_pages(start, size, prot, pgoff, flags) ,size
#define __NR32ATRF2_remap_file_pages           "%#Ix"
#define __NR32ATRA2_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(prot)
#define __NR32ATRF3_remap_file_pages           "%Iu"
#define __NR32ATRA3_remap_file_pages(start, size, prot, pgoff, flags) ,pgoff
#define __NR32ATRF4_remap_file_pages           "%#Ix"
#define __NR32ATRA4_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_set_tid_address            "%p"
#define __NR32ATRA0_set_tid_address(tidptr)    ,tidptr
#define __NR32ATRF0_timer_create               "?"
#define __NR32ATRA0_timer_create(clock_id, evp, timerid) /* nothing */
#define __NR32ATRF1_timer_create               "%p"
#define __NR32ATRA1_timer_create(clock_id, evp, timerid) ,evp
#define __NR32ATRF2_timer_create               "%p"
#define __NR32ATRA2_timer_create(clock_id, evp, timerid) ,timerid
#define __NR32ATRF0_timer_settime              "?"
#define __NR32ATRA0_timer_settime(timerid, flags, value, ovalue) /* nothing */
#define __NR32ATRF1_timer_settime              "%#Ix"
#define __NR32ATRA1_timer_settime(timerid, flags, value, ovalue) ,(uintptr_t)(flags)
#define __NR32ATRF2_timer_settime              "%p"
#define __NR32ATRA2_timer_settime(timerid, flags, value, ovalue) ,value
#define __NR32ATRF3_timer_settime              "%p"
#define __NR32ATRA3_timer_settime(timerid, flags, value, ovalue) ,ovalue
#define __NR32ATRF0_timer_gettime              "?"
#define __NR32ATRA0_timer_gettime(timerid, value) /* nothing */
#define __NR32ATRF1_timer_gettime              "%p"
#define __NR32ATRA1_timer_gettime(timerid, value) ,value
#define __NR32ATRF0_timer_getoverrun           "?"
#define __NR32ATRA0_timer_getoverrun(timerid)  /* nothing */
#define __NR32ATRF0_timer_delete               "?"
#define __NR32ATRA0_timer_delete(timerid)      /* nothing */
#define __NR32ATRF0_clock_settime              "?"
#define __NR32ATRA0_clock_settime(clock_id, tp) /* nothing */
#define __NR32ATRF1_clock_settime              "%p"
#define __NR32ATRA1_clock_settime(clock_id, tp) ,tp
#define __NR32ATRF0_clock_gettime              "?"
#define __NR32ATRA0_clock_gettime(clock_id, tp) /* nothing */
#define __NR32ATRF1_clock_gettime              "%p"
#define __NR32ATRA1_clock_gettime(clock_id, tp) ,tp
#define __NR32ATRF0_clock_getres               "?"
#define __NR32ATRA0_clock_getres(clock_id, res) /* nothing */
#define __NR32ATRF1_clock_getres               "%p"
#define __NR32ATRA1_clock_getres(clock_id, res) ,res
#define __NR32ATRF0_clock_nanosleep            "?"
#define __NR32ATRA0_clock_nanosleep(clock_id, flags, requested_time, remaining) /* nothing */
#define __NR32ATRF1_clock_nanosleep            "%#Ix"
#define __NR32ATRA1_clock_nanosleep(clock_id, flags, requested_time, remaining) ,(uintptr_t)(flags)
#define __NR32ATRF2_clock_nanosleep            "%p"
#define __NR32ATRA2_clock_nanosleep(clock_id, flags, requested_time, remaining) ,requested_time
#define __NR32ATRF3_clock_nanosleep            "%p"
#define __NR32ATRA3_clock_nanosleep(clock_id, flags, requested_time, remaining) ,remaining
#define __NR32ATRF0_statfs64                   "%q"
#define __NR32ATRA0_statfs64(file, buf)        ,(validate_readable_opt(file,1),file)
#define __NR32ATRF1_statfs64                   "%p"
#define __NR32ATRA1_statfs64(file, buf)        ,buf
#define __NR32ATRF0_fstatfs64                  "%d"
#define __NR32ATRA0_fstatfs64(file, buf)       ,(int)(file)
#define __NR32ATRF1_fstatfs64                  "%p"
#define __NR32ATRA1_fstatfs64(file, buf)       ,buf
#define __NR32ATRF0_tgkill                     "%Id"
#define __NR32ATRA0_tgkill(tgid, tid, signo)   ,(intptr_t)(tgid)
#define __NR32ATRF1_tgkill                     "%Id"
#define __NR32ATRA1_tgkill(tgid, tid, signo)   ,(intptr_t)(tid)
#define __NR32ATRF2_tgkill                     "%#Ix"
#define __NR32ATRA2_tgkill(tgid, tid, signo)   ,(uintptr_t)(signo)
#define __NR32ATRF0_utimes                     "%q"
#define __NR32ATRA0_utimes(filename, times)    ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utimes                     "%p"
#define __NR32ATRA1_utimes(filename, times)    ,times
#define __NR32ATRF0_waitid                     "%#Ix=%s"
#define __NR32ATRA0_waitid(idtype, id, infop, options, ru) ,(idtype),(idtype) == P_ALL ? "P_ALL" : (idtype) == P_PID ? "P_PID" : (idtype) == P_PGID ? "P_PGID" : "?"
#define __NR32ATRF1_waitid                     "%Iu"
#define __NR32ATRA1_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(id)
#define __NR32ATRF2_waitid                     "%p"
#define __NR32ATRA2_waitid(idtype, id, infop, options, ru) ,infop
#define __NR32ATRF3_waitid                     "%#Ix=%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(options),(options) & WEXITED ? "WEXITED" : "" \
                                                           ,((options) & WSTOPPED) && ((options) & (WEXITED)) ? "|" : "",(options) & WSTOPPED ? "WSTOPPED" : "" \
                                                           ,((options) & WCONTINUED) && ((options) & (WEXITED|WSTOPPED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                           ,((options) & WNOHANG) && ((options) & (WEXITED|WSTOPPED|WCONTINUED)) ? "|" : "",(options) & WNOHANG ? "WNOHANG" : "" \
                                                           ,((options) & WNOWAIT) && ((options) & (WEXITED|WSTOPPED|WCONTINUED|WNOHANG)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR32ATRF4_waitid                     "%p"
#define __NR32ATRA4_waitid(idtype, id, infop, options, ru) ,ru
#define __NR32ATRF0_ioprio_set                 "%#Ix"
#define __NR32ATRA0_ioprio_set(which, who, ioprio) ,(uintptr_t)(which)
#define __NR32ATRF1_ioprio_set                 "%#Ix"
#define __NR32ATRA1_ioprio_set(which, who, ioprio) ,(uintptr_t)(who)
#define __NR32ATRF2_ioprio_set                 "%#Ix"
#define __NR32ATRA2_ioprio_set(which, who, ioprio) ,(uintptr_t)(ioprio)
#define __NR32ATRF0_ioprio_get                 "%#Ix"
#define __NR32ATRA0_ioprio_get(which, who)     ,(uintptr_t)(which)
#define __NR32ATRF1_ioprio_get                 "%#Ix"
#define __NR32ATRA1_ioprio_get(which, who)     ,(uintptr_t)(who)
#define __NR32ATRF0_openat                     "%d"
#define __NR32ATRA0_openat(dirfd, filename, oflags, mode) ,(int)(dirfd)
#define __NR32ATRF1_openat                     "%q"
#define __NR32ATRA1_openat(dirfd, filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_openat                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
                                                          ,((oflags) & O_RDWR) && ((oflags) & (O_WRONLY)) ? "|" : "",(oflags) & O_RDWR ? "O_RDWR" : "" \
                                                          ,((oflags) & O_CREAT) && ((oflags) & (O_WRONLY|O_RDWR)) ? "|" : "",(oflags) & O_CREAT ? "O_CREAT" : "" \
                                                          ,((oflags) & O_EXCL) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT)) ? "|" : "",(oflags) & O_EXCL ? "O_EXCL" : "" \
                                                          ,((oflags) & O_NOCTTY) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL)) ? "|" : "",(oflags) & O_NOCTTY ? "O_NOCTTY" : "" \
                                                          ,((oflags) & O_TRUNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY)) ? "|" : "",(oflags) & O_TRUNC ? "O_TRUNC" : "" \
                                                          ,((oflags) & O_APPEND) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC)) ? "|" : "",(oflags) & O_APPEND ? "O_APPEND" : "" \
                                                          ,((oflags) & O_NONBLOCK) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND)) ? "|" : "",(oflags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                                          ,((oflags) & O_SYNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK)) ? "|" : "",(oflags) & O_SYNC ? "O_SYNC" : "" \
                                                          ,((oflags) & O_DSYNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC)) ? "|" : "",(oflags) & O_DSYNC ? "O_DSYNC" : "" \
                                                          ,((oflags) & O_ASYNC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC)) ? "|" : "",(oflags) & O_ASYNC ? "O_ASYNC" : "" \
                                                          ,((oflags) & O_DIRECT) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC)) ? "|" : "",(oflags) & O_DIRECT ? "O_DIRECT" : "" \
                                                          ,((oflags) & O_LARGEFILE) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT)) ? "|" : "",(oflags) & O_LARGEFILE ? "O_LARGEFILE" : "" \
                                                          ,((oflags) & O_DIRECTORY) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE)) ? "|" : "",(oflags) & O_DIRECTORY ? "O_DIRECTORY" : "" \
                                                          ,((oflags) & O_NOFOLLOW) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY)) ? "|" : "",(oflags) & O_NOFOLLOW ? "O_NOFOLLOW" : "" \
                                                          ,((oflags) & O_NOATIME) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW)) ? "|" : "",(oflags) & O_NOATIME ? "O_NOATIME" : "" \
                                                          ,((oflags) & O_CLOEXEC) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME)) ? "|" : "",(oflags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                                          ,((oflags) & O_CLOFORK) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC)) ? "|" : "",(oflags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                                          ,((oflags) & O_PATH) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK)) ? "|" : "",(oflags) & O_PATH ? "O_PATH" : "" \
                                                          ,((oflags) & 0x0400000) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH)) ? "|" : "",(oflags) & 0x0400000 ? "O_TMPFILE" : "" \
                                                          ,((oflags) & O_SYMLINK) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH|0x0400000)) ? "|" : "",(oflags) & O_SYMLINK ? "O_SYMLINK" : "" \
                                                          ,((oflags) & O_DOSPATH) && ((oflags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH|0x0400000|O_SYMLINK)) ? "|" : "",(oflags) & O_DOSPATH ? "O_DOSPATH" : ""
#define __NR32ATRF3_openat                     "%#Io"
#define __NR32ATRA3_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(mode)
#define __NR32ATRF0_mkdirat                    "%d"
#define __NR32ATRA0_mkdirat(dirfd, pathname, mode) ,(int)(dirfd)
#define __NR32ATRF1_mkdirat                    "%q"
#define __NR32ATRA1_mkdirat(dirfd, pathname, mode) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF2_mkdirat                    "%#Io"
#define __NR32ATRA2_mkdirat(dirfd, pathname, mode) ,(uintptr_t)(mode)
#define __NR32ATRF0_mknodat                    "%d"
#define __NR32ATRA0_mknodat(dirfd, nodename, mode, dev) ,(int)(dirfd)
#define __NR32ATRF1_mknodat                    "%q"
#define __NR32ATRA1_mknodat(dirfd, nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NR32ATRF2_mknodat                    "%#Io"
#define __NR32ATRA2_mknodat(dirfd, nodename, mode, dev) ,(uintptr_t)(mode)
#define __NR32ATRF3_mknodat                    "%.2x:%.2x"
#define __NR32ATRA3_mknodat(dirfd, nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF0_fchownat                   "%d"
#define __NR32ATRA0_fchownat(dirfd, filename, owner, group, flags) ,(int)(dirfd)
#define __NR32ATRF1_fchownat                   "%q"
#define __NR32ATRA1_fchownat(dirfd, filename, owner, group, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_fchownat                   "%I32u"
#define __NR32ATRA2_fchownat(dirfd, filename, owner, group, flags) ,owner
#define __NR32ATRF3_fchownat                   "%I32u"
#define __NR32ATRA3_fchownat(dirfd, filename, owner, group, flags) ,group
#define __NR32ATRF4_fchownat                   "%#Ix=%s%s%s"
#define __NR32ATRA4_fchownat(dirfd, filename, owner, group, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_futimesat                  "%d"
#define __NR32ATRA0_futimesat(dirfd, filename, times) ,(int)(dirfd)
#define __NR32ATRF1_futimesat                  "%p"
#define __NR32ATRA1_futimesat(dirfd, filename, times) ,filename
#define __NR32ATRF2_futimesat                  "%p"
#define __NR32ATRA2_futimesat(dirfd, filename, times) ,times
#define __NR32ATRF0_linux_fstatat64            "%d"
#define __NR32ATRA0_linux_fstatat64(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NR32ATRF1_linux_fstatat64            "%q"
#define __NR32ATRA1_linux_fstatat64(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_linux_fstatat64            "%p"
#define __NR32ATRA2_linux_fstatat64(dirfd, filename, statbuf, flags) ,statbuf
#define __NR32ATRF3_linux_fstatat64            "%#Ix=%s%s%s"
#define __NR32ATRA3_linux_fstatat64(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                     ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_unlinkat                   "%d"
#define __NR32ATRA0_unlinkat(dirfd, name, flags) ,(int)(dirfd)
#define __NR32ATRF1_unlinkat                   "%q"
#define __NR32ATRA1_unlinkat(dirfd, name, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_unlinkat                   "%#Ix=%s%s%s%s%s"
#define __NR32ATRA2_unlinkat(dirfd, name, flags) ,(uintptr_t)(flags),(flags) & AT_REMOVEDIR ? "AT_REMOVEDIR" : "" \
                                                 ,((flags) & AT_REMOVEREG) && ((flags) & (AT_REMOVEDIR)) ? "|" : "",(flags) & AT_REMOVEREG ? "AT_REMOVEREG" : "" \
                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_REMOVEDIR|AT_REMOVEREG)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_renameat                   "%d"
#define __NR32ATRA0_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(oldfd)
#define __NR32ATRF1_renameat                   "%q"
#define __NR32ATRA1_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NR32ATRF2_renameat                   "%d"
#define __NR32ATRA2_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(newfd)
#define __NR32ATRF3_renameat                   "%q"
#define __NR32ATRA3_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR32ATRF0_linkat                     "%d"
#define __NR32ATRA0_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(fromfd)
#define __NR32ATRF1_linkat                     "%q"
#define __NR32ATRA1_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NR32ATRF2_linkat                     "%d"
#define __NR32ATRA2_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(tofd)
#define __NR32ATRF3_linkat                     "%q"
#define __NR32ATRA3_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF4_linkat                     "%#Ix=%s%s%s%s%s"
#define __NR32ATRA4_linkat(fromfd, existing_file, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                            ,((flags) & AT_SYMLINK_FOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_FOLLOW ? "AT_SYMLINK_FOLLOW" : "" \
                                                                            ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_FOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_symlinkat                  "%q"
#define __NR32ATRA0_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NR32ATRF1_symlinkat                  "%d"
#define __NR32ATRA1_symlinkat(link_text, tofd, target_path) ,(int)(tofd)
#define __NR32ATRF2_symlinkat                  "%q"
#define __NR32ATRA2_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF0_readlinkat                 "%d"
#define __NR32ATRA0_readlinkat(dirfd, path, buf, buflen) ,(int)(dirfd)
#define __NR32ATRF1_readlinkat                 "%q"
#define __NR32ATRA1_readlinkat(dirfd, path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF2_readlinkat                 "%p"
#define __NR32ATRA2_readlinkat(dirfd, path, buf, buflen) ,buf
#define __NR32ATRF3_readlinkat                 "%Iu"
#define __NR32ATRA3_readlinkat(dirfd, path, buf, buflen) ,buflen
#define __NR32ATRF0_fchmodat                   "%d"
#define __NR32ATRA0_fchmodat(dirfd, filename, mode, flags) ,(int)(dirfd)
#define __NR32ATRF1_fchmodat                   "%q"
#define __NR32ATRA1_fchmodat(dirfd, filename, mode, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_fchmodat                   "%#Io"
#define __NR32ATRA2_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(mode)
#define __NR32ATRF3_fchmodat                   "%#Ix=%s%s%s"
#define __NR32ATRA3_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                           ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_faccessat                  "%d"
#define __NR32ATRA0_faccessat(dirfd, filename, type, flags) ,(int)(dirfd)
#define __NR32ATRF1_faccessat                  "%q"
#define __NR32ATRA1_faccessat(dirfd, filename, type, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_faccessat                  "%#Ix=%s%s%s%s%s"
#define __NR32ATRA2_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                                            ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                                            ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NR32ATRF3_faccessat                  "%#Ix=%s%s%s%s%s"
#define __NR32ATRA3_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                            ,((flags) & AT_EACCESS) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_EACCESS ? "AT_EACCESS" : "" \
                                                            ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_EACCESS)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_pselect6                   "%Iu"
#define __NR32ATRA0_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,nfds
#define __NR32ATRF1_pselect6                   "%p"
#define __NR32ATRA1_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,readfds
#define __NR32ATRF2_pselect6                   "%p"
#define __NR32ATRA2_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,writefds
#define __NR32ATRF3_pselect6                   "%p"
#define __NR32ATRA3_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,exceptfds
#define __NR32ATRF4_pselect6                   "%p"
#define __NR32ATRA4_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,timeout
#define __NR32ATRF5_pselect6                   "%p"
#define __NR32ATRA5_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,sigmask_sigset_and_len
#define __NR32ATRF0_ppoll                      "%p"
#define __NR32ATRA0_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,fds
#define __NR32ATRF1_ppoll                      "%Iu"
#define __NR32ATRA1_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,nfds
#define __NR32ATRF2_ppoll                      "%p"
#define __NR32ATRA2_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,timeout_ts
#define __NR32ATRF3_ppoll                      "%p"
#define __NR32ATRA3_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigmask
#define __NR32ATRF4_ppoll                      "%Iu"
#define __NR32ATRA4_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigsetsize
#define __NR32ATRF0_unshare                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA0_unshare(flags)             ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
                                               ,((flags) & CLONE_FS) && ((flags) & (CLONE_VM)) ? "|" : "",(flags) & CLONE_FS ? "CLONE_FS" : "" \
                                               ,((flags) & CLONE_FILES) && ((flags) & (CLONE_VM|CLONE_FS)) ? "|" : "",(flags) & CLONE_FILES ? "CLONE_FILES" : "" \
                                               ,((flags) & CLONE_SIGHAND) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES)) ? "|" : "",(flags) & CLONE_SIGHAND ? "CLONE_SIGHAND" : "" \
                                               ,((flags) & CLONE_PTRACE) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND)) ? "|" : "",(flags) & CLONE_PTRACE ? "CLONE_PTRACE" : "" \
                                               ,((flags) & CLONE_VFORK) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE)) ? "|" : "",(flags) & CLONE_VFORK ? "CLONE_VFORK" : "" \
                                               ,((flags) & CLONE_PARENT) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK)) ? "|" : "",(flags) & CLONE_PARENT ? "CLONE_PARENT" : "" \
                                               ,((flags) & CLONE_THREAD) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT)) ? "|" : "",(flags) & CLONE_THREAD ? "CLONE_THREAD" : "" \
                                               ,((flags) & CLONE_NEWNS) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD)) ? "|" : "",(flags) & CLONE_NEWNS ? "CLONE_NEWNS" : "" \
                                               ,((flags) & CLONE_SYSVSEM) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS)) ? "|" : "",(flags) & CLONE_SYSVSEM ? "CLONE_SYSVSEM" : "" \
                                               ,((flags) & CLONE_SETTLS) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM)) ? "|" : "",(flags) & CLONE_SETTLS ? "CLONE_SETTLS" : "" \
                                               ,((flags) & CLONE_PARENT_SETTID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS)) ? "|" : "",(flags) & CLONE_PARENT_SETTID ? "CLONE_PARENT_SETTID" : "" \
                                               ,((flags) & CLONE_CHILD_CLEARTID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID)) ? "|" : "",(flags) & CLONE_CHILD_CLEARTID ? "CLONE_CHILD_CLEARTID" : "" \
                                               ,((flags) & CLONE_DETACHED) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID)) ? "|" : "",(flags) & CLONE_DETACHED ? "CLONE_DETACHED" : "" \
                                               ,((flags) & CLONE_UNTRACED) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED)) ? "|" : "",(flags) & CLONE_UNTRACED ? "CLONE_UNTRACED" : "" \
                                               ,((flags) & CLONE_CHILD_SETTID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED)) ? "|" : "",(flags) & CLONE_CHILD_SETTID ? "CLONE_CHILD_SETTID" : "" \
                                               ,((flags) & CLONE_NEWUTS) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID)) ? "|" : "",(flags) & CLONE_NEWUTS ? "CLONE_NEWUTS" : "" \
                                               ,((flags) & CLONE_NEWIPC) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS)) ? "|" : "",(flags) & CLONE_NEWIPC ? "CLONE_NEWIPC" : "" \
                                               ,((flags) & CLONE_NEWUSER) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC)) ? "|" : "",(flags) & CLONE_NEWUSER ? "CLONE_NEWUSER" : "" \
                                               ,((flags) & CLONE_NEWPID) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC|CLONE_NEWUSER)) ? "|" : "",(flags) & CLONE_NEWPID ? "CLONE_NEWPID" : "" \
                                               ,((flags) & CLONE_NEWNET) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC|CLONE_NEWUSER|CLONE_NEWPID)) ? "|" : "",(flags) & CLONE_NEWNET ? "CLONE_NEWNET" : "" \
                                               ,((flags) & CLONE_IO) && ((flags) & (CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PTRACE|CLONE_VFORK|CLONE_PARENT|CLONE_THREAD|CLONE_NEWNS|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID|CLONE_DETACHED|CLONE_UNTRACED|CLONE_CHILD_SETTID|CLONE_NEWUTS|CLONE_NEWIPC|CLONE_NEWUSER|CLONE_NEWPID|CLONE_NEWNET)) ? "|" : "",(flags) & CLONE_IO ? "CLONE_IO" : ""
#define __NR32ATRF0_splice                     "%d"
#define __NR32ATRA0_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdin)
#define __NR32ATRF1_splice                     "%p"
#define __NR32ATRA1_splice(fdin, offin, fdout, offout, length, flags) ,offin
#define __NR32ATRF2_splice                     "%d"
#define __NR32ATRA2_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdout)
#define __NR32ATRF3_splice                     "%p"
#define __NR32ATRA3_splice(fdin, offin, fdout, offout, length, flags) ,offout
#define __NR32ATRF4_splice                     "%Iu"
#define __NR32ATRA4_splice(fdin, offin, fdout, offout, length, flags) ,length
#define __NR32ATRF5_splice                     "%#Ix"
#define __NR32ATRA5_splice(fdin, offin, fdout, offout, length, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_sync_file_range            "%d"
#define __NR32ATRA0_sync_file_range(fd, offset, count, flags) ,(int)(fd)
#define __NR32ATRF1_sync_file_range            "%I64u"
#define __NR32ATRA1_sync_file_range(fd, offset, count, flags) ,offset
#define __NR32ATRF2_sync_file_range            "%I64u"
#define __NR32ATRA2_sync_file_range(fd, offset, count, flags) ,count
#define __NR32ATRF3_sync_file_range            "%#Ix"
#define __NR32ATRA3_sync_file_range(fd, offset, count, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_tee                        "%d"
#define __NR32ATRA0_tee(fdin, fdout, length, flags) ,(int)(fdin)
#define __NR32ATRF1_tee                        "%d"
#define __NR32ATRA1_tee(fdin, fdout, length, flags) ,(int)(fdout)
#define __NR32ATRF2_tee                        "%Iu"
#define __NR32ATRA2_tee(fdin, fdout, length, flags) ,length
#define __NR32ATRF3_tee                        "%#Ix"
#define __NR32ATRA3_tee(fdin, fdout, length, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_vmsplice                   "%d"
#define __NR32ATRA0_vmsplice(fdout, iov, count, flags) ,(int)(fdout)
#define __NR32ATRF1_vmsplice                   "%p"
#define __NR32ATRA1_vmsplice(fdout, iov, count, flags) ,iov
#define __NR32ATRF2_vmsplice                   "%Iu"
#define __NR32ATRA2_vmsplice(fdout, iov, count, flags) ,count
#define __NR32ATRF3_vmsplice                   "%#Ix"
#define __NR32ATRA3_vmsplice(fdout, iov, count, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_getcpu                     "%p"
#define __NR32ATRA0_getcpu(cpu, node, tcache)  ,cpu
#define __NR32ATRF1_getcpu                     "%p"
#define __NR32ATRA1_getcpu(cpu, node, tcache)  ,node
#define __NR32ATRF2_getcpu                     "%p"
#define __NR32ATRA2_getcpu(cpu, node, tcache)  ,tcache
#define __NR32ATRF0_epoll_pwait                "%d"
#define __NR32ATRA0_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(int)(epfd)
#define __NR32ATRF1_epoll_pwait                "%p"
#define __NR32ATRA1_epoll_pwait(epfd, events, maxevents, timeout, ss) ,events
#define __NR32ATRF2_epoll_pwait                "%#Ix"
#define __NR32ATRA2_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(uintptr_t)(maxevents)
#define __NR32ATRF3_epoll_pwait                "%Id"
#define __NR32ATRA3_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(intptr_t)(timeout)
#define __NR32ATRF4_epoll_pwait                "%p"
#define __NR32ATRA4_epoll_pwait(epfd, events, maxevents, timeout, ss) ,ss
#define __NR32ATRF0_utimensat                  "%d"
#define __NR32ATRA0_utimensat(dirfd, filename, times, flags) ,(int)(dirfd)
#define __NR32ATRF1_utimensat                  "%q"
#define __NR32ATRA1_utimensat(dirfd, filename, times, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_utimensat                  "%p"
#define __NR32ATRA2_utimensat(dirfd, filename, times, flags) ,times
#define __NR32ATRF3_utimensat                  "%#Ix=%s%s%s%s%s"
#define __NR32ATRA3_utimensat(dirfd, filename, times, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                             ,((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                             ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_signalfd                   "%d"
#define __NR32ATRA0_signalfd(fd, sigmask, sigsetsize) ,(int)(fd)
#define __NR32ATRF1_signalfd                   "%p"
#define __NR32ATRA1_signalfd(fd, sigmask, sigsetsize) ,sigmask
#define __NR32ATRF2_signalfd                   "%Iu"
#define __NR32ATRA2_signalfd(fd, sigmask, sigsetsize) ,sigsetsize
#define __NR32ATRF0_timerfd_create             "?"
#define __NR32ATRA0_timerfd_create(clock_id, flags) /* nothing */
#define __NR32ATRF1_timerfd_create             "%#Ix"
#define __NR32ATRA1_timerfd_create(clock_id, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_eventfd                    "%#Ix"
#define __NR32ATRA0_eventfd(initval)           ,(uintptr_t)(initval)
#define __NR32ATRF0_fallocate                  "%d"
#define __NR32ATRA0_fallocate(fd, mode, offset, length) ,(int)(fd)
#define __NR32ATRF1_fallocate                  "%#Ix"
#define __NR32ATRA1_fallocate(fd, mode, offset, length) ,(uintptr_t)(mode)
#define __NR32ATRF2_fallocate                  "%I32u"
#define __NR32ATRA2_fallocate(fd, mode, offset, length) ,offset
#define __NR32ATRF3_fallocate                  "%I32u"
#define __NR32ATRA3_fallocate(fd, mode, offset, length) ,length
#define __NR32ATRF0_timerfd_settime            "%d"
#define __NR32ATRA0_timerfd_settime(ufd, flags, utmr, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_settime            "%#Ix"
#define __NR32ATRA1_timerfd_settime(ufd, flags, utmr, otmr) ,(uintptr_t)(flags)
#define __NR32ATRF2_timerfd_settime            "%p"
#define __NR32ATRA2_timerfd_settime(ufd, flags, utmr, otmr) ,utmr
#define __NR32ATRF3_timerfd_settime            "%p"
#define __NR32ATRA3_timerfd_settime(ufd, flags, utmr, otmr) ,otmr
#define __NR32ATRF0_timerfd_gettime            "%d"
#define __NR32ATRA0_timerfd_gettime(ufd, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_gettime            "%p"
#define __NR32ATRA1_timerfd_gettime(ufd, otmr) ,otmr
#define __NR32ATRF0_signalfd4                  "%d"
#define __NR32ATRA0_signalfd4(fd, sigmask, sigsetsize, flags) ,(int)(fd)
#define __NR32ATRF1_signalfd4                  "%p"
#define __NR32ATRA1_signalfd4(fd, sigmask, sigsetsize, flags) ,sigmask
#define __NR32ATRF2_signalfd4                  "%Iu"
#define __NR32ATRA2_signalfd4(fd, sigmask, sigsetsize, flags) ,sigsetsize
#define __NR32ATRF3_signalfd4                  "%#Ix=%s%s%s"
#define __NR32ATRA3_signalfd4(fd, sigmask, sigsetsize, flags) ,(uintptr_t)(flags),(flags) & SFD_NONBLOCK ? "SFD_NONBLOCK" : "" \
                                                              ,((flags) & SFD_CLOEXEC) && ((flags) & (SFD_NONBLOCK)) ? "|" : "",(flags) & SFD_CLOEXEC ? "SFD_CLOEXEC" : ""
#define __NR32ATRF0_eventfd2                   "%#Ix"
#define __NR32ATRA0_eventfd2(initval, flags)   ,(uintptr_t)(initval)
#define __NR32ATRF1_eventfd2                   "%#Ix=%s%s%s%s%s"
#define __NR32ATRA1_eventfd2(initval, flags)   ,(uintptr_t)(flags),(flags) & EFD_SEMAPHORE ? "EFD_SEMAPHORE" : "" \
                                               ,((flags) & EFD_NONBLOCK) && ((flags) & (EFD_SEMAPHORE)) ? "|" : "",(flags) & EFD_NONBLOCK ? "EFD_NONBLOCK" : "" \
                                               ,((flags) & EFD_CLOEXEC) && ((flags) & (EFD_SEMAPHORE|EFD_NONBLOCK)) ? "|" : "",(flags) & EFD_CLOEXEC ? "EFD_CLOEXEC" : ""
#define __NR32ATRF0_epoll_create1              "%#Ix"
#define __NR32ATRA0_epoll_create1(flags)       ,(uintptr_t)(flags)
#define __NR32ATRF0_dup3                       "%d"
#define __NR32ATRA0_dup3(oldfd, newfd, flags)  ,(int)(oldfd)
#define __NR32ATRF1_dup3                       "%d"
#define __NR32ATRA1_dup3(oldfd, newfd, flags)  ,(int)(newfd)
#define __NR32ATRF2_dup3                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_dup3(oldfd, newfd, flags)  ,(uintptr_t)(flags),(flags) & O_WRONLY ? "O_WRONLY" : (flags) ? "" : "O_RDONLY" \
                                               ,((flags) & O_RDWR) && ((flags) & (O_WRONLY)) ? "|" : "",(flags) & O_RDWR ? "O_RDWR" : "" \
                                               ,((flags) & O_CREAT) && ((flags) & (O_WRONLY|O_RDWR)) ? "|" : "",(flags) & O_CREAT ? "O_CREAT" : "" \
                                               ,((flags) & O_EXCL) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT)) ? "|" : "",(flags) & O_EXCL ? "O_EXCL" : "" \
                                               ,((flags) & O_NOCTTY) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL)) ? "|" : "",(flags) & O_NOCTTY ? "O_NOCTTY" : "" \
                                               ,((flags) & O_TRUNC) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY)) ? "|" : "",(flags) & O_TRUNC ? "O_TRUNC" : "" \
                                               ,((flags) & O_APPEND) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC)) ? "|" : "",(flags) & O_APPEND ? "O_APPEND" : "" \
                                               ,((flags) & O_NONBLOCK) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND)) ? "|" : "",(flags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                               ,((flags) & O_SYNC) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK)) ? "|" : "",(flags) & O_SYNC ? "O_SYNC" : "" \
                                               ,((flags) & O_DSYNC) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC)) ? "|" : "",(flags) & O_DSYNC ? "O_DSYNC" : "" \
                                               ,((flags) & O_ASYNC) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC)) ? "|" : "",(flags) & O_ASYNC ? "O_ASYNC" : "" \
                                               ,((flags) & O_DIRECT) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC)) ? "|" : "",(flags) & O_DIRECT ? "O_DIRECT" : "" \
                                               ,((flags) & O_LARGEFILE) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT)) ? "|" : "",(flags) & O_LARGEFILE ? "O_LARGEFILE" : "" \
                                               ,((flags) & O_DIRECTORY) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE)) ? "|" : "",(flags) & O_DIRECTORY ? "O_DIRECTORY" : "" \
                                               ,((flags) & O_NOFOLLOW) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY)) ? "|" : "",(flags) & O_NOFOLLOW ? "O_NOFOLLOW" : "" \
                                               ,((flags) & O_NOATIME) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW)) ? "|" : "",(flags) & O_NOATIME ? "O_NOATIME" : "" \
                                               ,((flags) & O_CLOEXEC) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME)) ? "|" : "",(flags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                               ,((flags) & O_CLOFORK) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC)) ? "|" : "",(flags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                               ,((flags) & O_PATH) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK)) ? "|" : "",(flags) & O_PATH ? "O_PATH" : "" \
                                               ,((flags) & 0x0400000) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH)) ? "|" : "",(flags) & 0x0400000 ? "O_TMPFILE" : "" \
                                               ,((flags) & O_SYMLINK) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH|0x0400000)) ? "|" : "",(flags) & O_SYMLINK ? "O_SYMLINK" : "" \
                                               ,((flags) & O_DOSPATH) && ((flags) & (O_WRONLY|O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_TRUNC|O_APPEND|O_NONBLOCK|O_SYNC|O_DSYNC|O_ASYNC|O_DIRECT|O_LARGEFILE|O_DIRECTORY|O_NOFOLLOW|O_NOATIME|O_CLOEXEC|O_CLOFORK|O_PATH|0x0400000|O_SYMLINK)) ? "|" : "",(flags) & O_DOSPATH ? "O_DOSPATH" : ""
#define __NR32ATRF0_pipe2                      "%p"
#define __NR32ATRA0_pipe2(pipedes, flags)      ,pipedes
#define __NR32ATRF1_pipe2                      "%#Ix=%s%s%s%s%s%s%s"
#define __NR32ATRA1_pipe2(pipedes, flags)      ,(uintptr_t)(flags),(flags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                               ,((flags) & O_CLOFORK) && ((flags) & (O_CLOEXEC)) ? "|" : "",(flags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                               ,((flags) & O_NONBLOCK) && ((flags) & (O_CLOEXEC|O_CLOFORK)) ? "|" : "",(flags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                               ,((flags) & O_DIRECT) && ((flags) & (O_CLOEXEC|O_CLOFORK|O_NONBLOCK)) ? "|" : "",(flags) & O_DIRECT ? "O_DIRECT" : ""
#define __NR32ATRF0_preadv                     "%d"
#define __NR32ATRA0_preadv(fd, iovec, count, offset) ,(int)(fd)
#define __NR32ATRF1_preadv                     "%p"
#define __NR32ATRA1_preadv(fd, iovec, count, offset) ,iovec
#define __NR32ATRF2_preadv                     "%Iu"
#define __NR32ATRA2_preadv(fd, iovec, count, offset) ,count
#define __NR32ATRF3_preadv                     "%I64u"
#define __NR32ATRA3_preadv(fd, iovec, count, offset) ,offset
#define __NR32ATRF0_pwritev                    "%d"
#define __NR32ATRA0_pwritev(fd, iovec, count, offset) ,(int)(fd)
#define __NR32ATRF1_pwritev                    "%p"
#define __NR32ATRA1_pwritev(fd, iovec, count, offset) ,iovec
#define __NR32ATRF2_pwritev                    "%Iu"
#define __NR32ATRA2_pwritev(fd, iovec, count, offset) ,count
#define __NR32ATRF3_pwritev                    "%I64u"
#define __NR32ATRA3_pwritev(fd, iovec, count, offset) ,offset
#define __NR32ATRF0_rt_tgsigqueueinfo          "%Id"
#define __NR32ATRA0_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tgid)
#define __NR32ATRF1_rt_tgsigqueueinfo          "%Id"
#define __NR32ATRA1_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tid)
#define __NR32ATRF2_rt_tgsigqueueinfo          "%#Ix"
#define __NR32ATRA2_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(uintptr_t)(signo)
#define __NR32ATRF3_rt_tgsigqueueinfo          "%p"
#define __NR32ATRA3_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,uinfo
#define __NR32ATRF0_recvmmsg                   "%d"
#define __NR32ATRA0_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(int)(sockfd)
#define __NR32ATRF1_recvmmsg                   "%p"
#define __NR32ATRA1_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vmessages
#define __NR32ATRF2_recvmmsg                   "%Iu"
#define __NR32ATRA2_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vlen
#define __NR32ATRF3_recvmmsg                   "%#Ix"
#define __NR32ATRA3_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(uintptr_t)(flags)
#define __NR32ATRF4_recvmmsg                   "%p"
#define __NR32ATRA4_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,tmo
#define __NR32ATRF0_prlimit64                  "%Id"
#define __NR32ATRA0_prlimit64(pid, resource, new_limit, old_limit) ,(intptr_t)(pid)
#define __NR32ATRF1_prlimit64                  "%#Ix"
#define __NR32ATRA1_prlimit64(pid, resource, new_limit, old_limit) ,(uintptr_t)(resource)
#define __NR32ATRF2_prlimit64                  "%p"
#define __NR32ATRA2_prlimit64(pid, resource, new_limit, old_limit) ,new_limit
#define __NR32ATRF3_prlimit64                  "%p"
#define __NR32ATRA3_prlimit64(pid, resource, new_limit, old_limit) ,old_limit
#define __NR32ATRF0_name_to_handle_at          "%d"
#define __NR32ATRA0_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(int)(dirfd)
#define __NR32ATRF1_name_to_handle_at          "%q"
#define __NR32ATRA1_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_name_to_handle_at          "%p"
#define __NR32ATRA2_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,handle
#define __NR32ATRF3_name_to_handle_at          "%p"
#define __NR32ATRA3_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,mnt_id
#define __NR32ATRF4_name_to_handle_at          "%#Ix"
#define __NR32ATRA4_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_open_by_handle_at          "%d"
#define __NR32ATRA0_open_by_handle_at(mountdirfd, handle, flags) ,(int)(mountdirfd)
#define __NR32ATRF1_open_by_handle_at          "%p"
#define __NR32ATRA1_open_by_handle_at(mountdirfd, handle, flags) ,handle
#define __NR32ATRF2_open_by_handle_at          "%#Ix"
#define __NR32ATRA2_open_by_handle_at(mountdirfd, handle, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_syncfs                     "%d"
#define __NR32ATRA0_syncfs(fd)                 ,(int)(fd)
#define __NR32ATRF0_sendmmsg                   "%d"
#define __NR32ATRA0_sendmmsg(sockfd, vmessages, vlen, flags) ,(int)(sockfd)
#define __NR32ATRF1_sendmmsg                   "%p"
#define __NR32ATRA1_sendmmsg(sockfd, vmessages, vlen, flags) ,vmessages
#define __NR32ATRF2_sendmmsg                   "%Iu"
#define __NR32ATRA2_sendmmsg(sockfd, vmessages, vlen, flags) ,vlen
#define __NR32ATRF3_sendmmsg                   "%#Ix"
#define __NR32ATRA3_sendmmsg(sockfd, vmessages, vlen, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_setns                      "%d"
#define __NR32ATRA0_setns(fd, nstype)          ,(int)(fd)
#define __NR32ATRF1_setns                      "%#Ix"
#define __NR32ATRA1_setns(fd, nstype)          ,(uintptr_t)(nstype)
#define __NR32ATRF0_process_vm_readv           "%Id"
#define __NR32ATRA0_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NR32ATRF1_process_vm_readv           "%p"
#define __NR32ATRA1_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NR32ATRF2_process_vm_readv           "%Iu"
#define __NR32ATRA2_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NR32ATRF3_process_vm_readv           "%p"
#define __NR32ATRA3_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NR32ATRF4_process_vm_readv           "%Iu"
#define __NR32ATRA4_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NR32ATRF5_process_vm_readv           "%#Ix"
#define __NR32ATRA5_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_process_vm_writev          "%Id"
#define __NR32ATRA0_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NR32ATRF1_process_vm_writev          "%p"
#define __NR32ATRA1_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NR32ATRF2_process_vm_writev          "%Iu"
#define __NR32ATRA2_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NR32ATRF3_process_vm_writev          "%p"
#define __NR32ATRA3_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NR32ATRF4_process_vm_writev          "%Iu"
#define __NR32ATRA4_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NR32ATRF5_process_vm_writev          "%#Ix"
#define __NR32ATRA5_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_kcmp                       "%Id"
#define __NR32ATRA0_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid1)
#define __NR32ATRF1_kcmp                       "%Id"
#define __NR32ATRA1_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid2)
#define __NR32ATRF2_kcmp                       "%#Ix"
#define __NR32ATRA2_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(type)
#define __NR32ATRF3_kcmp                       "%#Ix"
#define __NR32ATRA3_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx1)
#define __NR32ATRF4_kcmp                       "%#Ix"
#define __NR32ATRA4_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx2)
#define __NR32ATRF0_renameat2                  "%d"
#define __NR32ATRA0_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(olddirfd)
#define __NR32ATRF1_renameat2                  "%q"
#define __NR32ATRA1_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(oldpath,1),oldpath)
#define __NR32ATRF2_renameat2                  "%d"
#define __NR32ATRA2_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(newdirfd)
#define __NR32ATRF3_renameat2                  "%q"
#define __NR32ATRA3_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(newpath,1),newpath)
#define __NR32ATRF4_renameat2                  "%#Ix"
#define __NR32ATRA4_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_execveat                   "%d"
#define __NR32ATRA0_execveat(dirfd, pathname, argv, envp, flags) ,(int)(dirfd)
#define __NR32ATRF1_execveat                   "%q"
#define __NR32ATRA1_execveat(dirfd, pathname, argv, envp, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF2_execveat                   "%p"
#define __NR32ATRA2_execveat(dirfd, pathname, argv, envp, flags) ,argv
#define __NR32ATRF3_execveat                   "%p"
#define __NR32ATRA3_execveat(dirfd, pathname, argv, envp, flags) ,envp
#define __NR32ATRF4_execveat                   "%#Ix=%s%s%s%s%s"
#define __NR32ATRA4_execveat(dirfd, pathname, argv, envp, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                 ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_socket                     "%#Ix"
#define __NR32ATRA0_socket(domain, type, protocol) ,(uintptr_t)(domain)
#define __NR32ATRF1_socket                     "%#Ix"
#define __NR32ATRA1_socket(domain, type, protocol) ,(uintptr_t)(type)
#define __NR32ATRF2_socket                     "%#Ix"
#define __NR32ATRA2_socket(domain, type, protocol) ,(uintptr_t)(protocol)
#define __NR32ATRF0_socketpair                 "%#Ix"
#define __NR32ATRA0_socketpair(domain, type, protocol, fds) ,(uintptr_t)(domain)
#define __NR32ATRF1_socketpair                 "%#Ix"
#define __NR32ATRA1_socketpair(domain, type, protocol, fds) ,(uintptr_t)(type)
#define __NR32ATRF2_socketpair                 "%#Ix"
#define __NR32ATRA2_socketpair(domain, type, protocol, fds) ,(uintptr_t)(protocol)
#define __NR32ATRF3_socketpair                 "%p"
#define __NR32ATRA3_socketpair(domain, type, protocol, fds) ,fds
#define __NR32ATRF0_bind                       "%d"
#define __NR32ATRA0_bind(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_bind                       "%p"
#define __NR32ATRA1_bind(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_bind                       "%Iu"
#define __NR32ATRA2_bind(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR32ATRF0_connect                    "%d"
#define __NR32ATRA0_connect(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_connect                    "%p"
#define __NR32ATRA1_connect(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_connect                    "%Iu"
#define __NR32ATRA2_connect(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR32ATRF0_listen                     "%d"
#define __NR32ATRA0_listen(sockfd, max_backlog) ,(int)(sockfd)
#define __NR32ATRF1_listen                     "%#Ix"
#define __NR32ATRA1_listen(sockfd, max_backlog) ,(uintptr_t)(max_backlog)
#define __NR32ATRF0_accept4                    "%d"
#define __NR32ATRA0_accept4(sockfd, addr, addr_len, flags) ,(int)(sockfd)
#define __NR32ATRF1_accept4                    "%p"
#define __NR32ATRA1_accept4(sockfd, addr, addr_len, flags) ,addr
#define __NR32ATRF2_accept4                    "%p"
#define __NR32ATRA2_accept4(sockfd, addr, addr_len, flags) ,addr_len
#define __NR32ATRF3_accept4                    "%#Ix=%s%s%s%s%s"
#define __NR32ATRA3_accept4(sockfd, addr, addr_len, flags) ,(uintptr_t)(flags),(flags) & SOCK_NONBLOCK ? "SOCK_NONBLOCK" : "" \
                                                           ,((flags) & SOCK_CLOEXEC) && ((flags) & (SOCK_NONBLOCK)) ? "|" : "",(flags) & SOCK_CLOEXEC ? "SOCK_CLOEXEC" : "" \
                                                           ,((flags) & SOCK_CLOFORK) && ((flags) & (SOCK_NONBLOCK|SOCK_CLOEXEC)) ? "|" : "",(flags) & SOCK_CLOFORK ? "SOCK_CLOFORK" : ""
#define __NR32ATRF0_getsockopt                 "%d"
#define __NR32ATRA0_getsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NR32ATRF1_getsockopt                 "%#Ix=%s"
#define __NR32ATRA1_getsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NR32ATRF2_getsockopt                 "%#Ix"
#define __NR32ATRA2_getsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NR32ATRF3_getsockopt                 "%p"
#define __NR32ATRA3_getsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NR32ATRF4_getsockopt                 "%p"
#define __NR32ATRA4_getsockopt(sockfd, level, optname, optval, optlen) ,optlen
#define __NR32ATRF0_setsockopt                 "%d"
#define __NR32ATRA0_setsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NR32ATRF1_setsockopt                 "%#Ix=%s"
#define __NR32ATRA1_setsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NR32ATRF2_setsockopt                 "%#Ix"
#define __NR32ATRA2_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NR32ATRF3_setsockopt                 "%p"
#define __NR32ATRA3_setsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NR32ATRF4_setsockopt                 "%Iu"
#define __NR32ATRA4_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optlen)
#define __NR32ATRF0_getsockname                "%d"
#define __NR32ATRA0_getsockname(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_getsockname                "%p"
#define __NR32ATRA1_getsockname(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_getsockname                "%p"
#define __NR32ATRA2_getsockname(sockfd, addr, addr_len) ,addr_len
#define __NR32ATRF0_getpeername                "%d"
#define __NR32ATRA0_getpeername(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_getpeername                "%p"
#define __NR32ATRA1_getpeername(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_getpeername                "%p"
#define __NR32ATRA2_getpeername(sockfd, addr, addr_len) ,addr_len
#define __NR32ATRF0_sendto                     "%d"
#define __NR32ATRA0_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_sendto                     "%p"
#define __NR32ATRA1_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NR32ATRF2_sendto                     "%Iu"
#define __NR32ATRA2_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NR32ATRF3_sendto                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                                        ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                                        ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                        ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                                        ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                                        ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                                        ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NR32ATRF4_sendto                     "%p"
#define __NR32ATRA4_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NR32ATRF5_sendto                     "%Iu"
#define __NR32ATRA5_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR32ATRF0_sendmsg                    "%d"
#define __NR32ATRA0_sendmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NR32ATRF1_sendmsg                    "%p"
#define __NR32ATRA1_sendmsg(sockfd, message, flags) ,message
#define __NR32ATRF2_sendmsg                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_sendmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                    ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                    ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                    ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                    ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                    ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                    ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NR32ATRF0_recvfrom                   "%d"
#define __NR32ATRA0_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_recvfrom                   "%p"
#define __NR32ATRA1_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NR32ATRF2_recvfrom                   "%Iu"
#define __NR32ATRA2_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NR32ATRF3_recvfrom                   "%#Ix=%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                          ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                                          ,((flags) & MSG_OOB) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                                          ,((flags) & MSG_PEEK) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                                          ,((flags) & MSG_TRUNC) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                                          ,((flags) & MSG_WAITALL) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NR32ATRF4_recvfrom                   "%p"
#define __NR32ATRA4_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NR32ATRF5_recvfrom                   "%p"
#define __NR32ATRA5_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr_len
#define __NR32ATRF0_recvmsg                    "%d"
#define __NR32ATRA0_recvmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NR32ATRF1_recvmsg                    "%p"
#define __NR32ATRA1_recvmsg(sockfd, message, flags) ,message
#define __NR32ATRF2_recvmsg                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_recvmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CMSG_CLOEXEC ? "MSG_CMSG_CLOEXEC" : "" \
                                                    ,((flags) & MSG_CMSG_CLOFORK) && ((flags) & (MSG_CMSG_CLOEXEC)) ? "|" : "",(flags) & MSG_CMSG_CLOFORK ? "MSG_CMSG_CLOFORK" : "" \
                                                    ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                    ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                    ,((flags) & MSG_OOB) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                    ,((flags) & MSG_PEEK) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                    ,((flags) & MSG_TRUNC) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                    ,((flags) & MSG_WAITALL) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NR32ATRF0_shutdown                   "%d"
#define __NR32ATRA0_shutdown(sockfd, how)      ,(int)(sockfd)
#define __NR32ATRF1_shutdown                   "%#Ix=%s"
#define __NR32ATRA1_shutdown(sockfd, how)      ,(how),(how) == SHUT_RD ? "SHUT_RD" : (how) == SHUT_WR ? "SHUT_WR" : (how) == SHUT_RDWR ? "SHUT_RDWR" : "?"
#define __NR32ATRF0_hop                        "%d"
#define __NR32ATRA0_hop(fd, command, arg)      ,(int)(fd)
#define __NR32ATRF1_hop                        "%#Ix"
#define __NR32ATRA1_hop(fd, command, arg)      ,(uintptr_t)(command)
#define __NR32ATRF2_hop                        "%p"
#define __NR32ATRA2_hop(fd, command, arg)      ,arg
#define __NR32ATRF0_hopf                       "%d"
#define __NR32ATRA0_hopf(fd, command, mode, arg) ,(int)(fd)
#define __NR32ATRF1_hopf                       "%#Ix"
#define __NR32ATRA1_hopf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NR32ATRF2_hopf                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_hopf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF3_hopf                       "%p"
#define __NR32ATRA3_hopf(fd, command, mode, arg) ,arg
#define __NR32ATRF0_readf                      "%d"
#define __NR32ATRA0_readf(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR32ATRF1_readf                      "%p"
#define __NR32ATRA1_readf(fd, buf, bufsize, mode) ,buf
#define __NR32ATRF2_readf                      "%Iu"
#define __NR32ATRA2_readf(fd, buf, bufsize, mode) ,bufsize
#define __NR32ATRF3_readf                      "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_readf(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                  ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                  ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                  ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                  ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                  ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                  ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                  ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                  ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_writef                     "%d"
#define __NR32ATRA0_writef(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR32ATRF1_writef                     "%p"
#define __NR32ATRA1_writef(fd, buf, bufsize, mode) ,buf
#define __NR32ATRF2_writef                     "%Iu"
#define __NR32ATRA2_writef(fd, buf, bufsize, mode) ,bufsize
#define __NR32ATRF3_writef                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_writef(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_detach                     "%Id"
#define __NR32ATRA0_detach(pid)                ,(intptr_t)(pid)
#define __NR32ATRF0_frealpath4                 "%d"
#define __NR32ATRA0_frealpath4(fd, buf, buflen, flags) ,(int)(fd)
#define __NR32ATRF1_frealpath4                 "%p"
#define __NR32ATRA1_frealpath4(fd, buf, buflen, flags) ,buf
#define __NR32ATRF2_frealpath4                 "%Iu"
#define __NR32ATRA2_frealpath4(fd, buf, buflen, flags) ,buflen
#define __NR32ATRF3_frealpath4                 "%#Ix=%s%s%s%s%s"
#define __NR32ATRA3_frealpath4(fd, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                       ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                       ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_frealpathat                "%d"
#define __NR32ATRA0_frealpathat(dirfd, filename, buf, buflen, flags) ,(int)(dirfd)
#define __NR32ATRF1_frealpathat                "%q"
#define __NR32ATRA1_frealpathat(dirfd, filename, buf, buflen, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_frealpathat                "%p"
#define __NR32ATRA2_frealpathat(dirfd, filename, buf, buflen, flags) ,buf
#define __NR32ATRF3_frealpathat                "%Iu"
#define __NR32ATRA3_frealpathat(dirfd, filename, buf, buflen, flags) ,buflen
#define __NR32ATRF4_frealpathat                "%#Ix=%s%s%s%s%s%s%s"
#define __NR32ATRA4_frealpathat(dirfd, filename, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                                     ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                     ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                     ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_rpc_schedule               "%Id"
#define __NR32ATRA0_rpc_schedule(target, flags, program, arguments) ,(intptr_t)(target)
#define __NR32ATRF1_rpc_schedule               "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA1_rpc_schedule(target, flags, program, arguments) ,(uintptr_t)(flags),(flags) & RPC_SCHEDULE_ASYNC ? "RPC_SCHEDULE_ASYNC" : (flags) ? "" : "RPC_SCHEDULE_SYNC" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_NONSYSCALL) && ((flags) & (RPC_SCHEDULE_ASYNC)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NONSYSCALL ? "RPC_SCHEDULE_FLAG_NONSYSCALL" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_WAITFORSTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITFORSTART ? "RPC_SCHEDULE_FLAG_WAITFORSTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX ? "RPC_SCHEDULE_FLAG_STATUSFUTEX" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_SYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_SYSRESTART ? "RPC_SCHEDULE_FLAG_SYSRESTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART ? "RPC_SCHEDULE_FLAG_NOSYSRESTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_WAITSMPACK) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITSMPACK ? "RPC_SCHEDULE_FLAG_WAITSMPACK" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_DONTWAKE) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_DONTWAKE ? "RPC_SCHEDULE_FLAG_DONTWAKE" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_HIGHPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_HIGHPRIO ? "RPC_SCHEDULE_FLAG_HIGHPRIO" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_LOWPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE|RPC_SCHEDULE_FLAG_HIGHPRIO)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_LOWPRIO ? "RPC_SCHEDULE_FLAG_LOWPRIO" : ""
#define __NR32ATRF2_rpc_schedule               "%p"
#define __NR32ATRA2_rpc_schedule(target, flags, program, arguments) ,program
#define __NR32ATRF3_rpc_schedule               "%p"
#define __NR32ATRA3_rpc_schedule(target, flags, program, arguments) ,arguments
#define __NR32ATRF0_sysctl                     "%#Ix"
#define __NR32ATRA0_sysctl(command, arg)       ,(uintptr_t)(command)
#define __NR32ATRF1_sysctl                     "%p"
#define __NR32ATRA1_sysctl(command, arg)       ,arg
#define __NR32ATRF0_openpty                    "%p"
#define __NR32ATRA0_openpty(amaster, aslave, name, termp, winp) ,amaster
#define __NR32ATRF1_openpty                    "%p"
#define __NR32ATRA1_openpty(amaster, aslave, name, termp, winp) ,aslave
#define __NR32ATRF2_openpty                    "%p"
#define __NR32ATRA2_openpty(amaster, aslave, name, termp, winp) ,name
#define __NR32ATRF3_openpty                    "%p"
#define __NR32ATRA3_openpty(amaster, aslave, name, termp, winp) ,termp
#define __NR32ATRF4_openpty                    "%p"
#define __NR32ATRA4_openpty(amaster, aslave, name, termp, winp) ,winp
#define __NR32ATRF0_fchdirat                   "%d"
#define __NR32ATRA0_fchdirat(dirfd, path, flags) ,(int)(dirfd)
#define __NR32ATRF1_fchdirat                   "%q"
#define __NR32ATRA1_fchdirat(dirfd, path, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF2_fchdirat                   "%#Ix=%s"
#define __NR32ATRA2_fchdirat(dirfd, path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_time64                     "%p"
#define __NR32ATRA0_time64(timer)              ,timer
#define __NR32ATRF0_set_exception_handler      "%#Ix"
#define __NR32ATRA0_set_exception_handler(mode, handler, handler_sp) ,(uintptr_t)(mode)
#define __NR32ATRF1_set_exception_handler      "%p"
#define __NR32ATRA1_set_exception_handler(mode, handler, handler_sp) ,handler
#define __NR32ATRF2_set_exception_handler      "%p"
#define __NR32ATRA2_set_exception_handler(mode, handler, handler_sp) ,handler_sp
#define __NR32ATRF0_get_exception_handler      "%p"
#define __NR32ATRA0_get_exception_handler(pmode, phandler, phandler_sp) ,pmode
#define __NR32ATRF1_get_exception_handler      "%p"
#define __NR32ATRA1_get_exception_handler(pmode, phandler, phandler_sp) ,phandler
#define __NR32ATRF2_get_exception_handler      "%p"
#define __NR32ATRA2_get_exception_handler(pmode, phandler, phandler_sp) ,phandler_sp
#define __NR32ATRF0_set_library_listdef        "%p"
#define __NR32ATRA0_set_library_listdef(listdef) ,listdef
#define __NR32ATRF0_debugtrap                  "%p"
#define __NR32ATRA0_debugtrap(state, reason)   ,state
#define __NR32ATRF1_debugtrap                  "%p"
#define __NR32ATRA1_debugtrap(state, reason)   ,reason
#define __NR32ATRF0_lfutex                     "%p"
#define __NR32ATRA0_lfutex(uaddr, futex_op, val, timeout, val2) ,uaddr
#define __NR32ATRF1_lfutex                     "%#Ix"
#define __NR32ATRA1_lfutex(uaddr, futex_op, val, timeout, val2) ,(uintptr_t)(futex_op)
#define __NR32ATRF2_lfutex                     "%p"
#define __NR32ATRA2_lfutex(uaddr, futex_op, val, timeout, val2) ,val
#define __NR32ATRF3_lfutex                     "%p"
#define __NR32ATRA3_lfutex(uaddr, futex_op, val, timeout, val2) ,timeout
#define __NR32ATRF4_lfutex                     "%p"
#define __NR32ATRA4_lfutex(uaddr, futex_op, val, timeout, val2) ,val2
#define __NR32ATRF0_lseek64                    "%d"
#define __NR32ATRA0_lseek64(fd, offset, whence) ,(int)(fd)
#define __NR32ATRF1_lseek64                    "%I64d"
#define __NR32ATRA1_lseek64(fd, offset, whence) ,offset
#define __NR32ATRF2_lseek64                    "%#Ix=%s"
#define __NR32ATRA2_lseek64(fd, offset, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NR32ATRF0_lfutexlock                 "%p"
#define __NR32ATRA0_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,ulockaddr
#define __NR32ATRF1_lfutexlock                 "%p"
#define __NR32ATRA1_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,uaddr
#define __NR32ATRF2_lfutexlock                 "%#Ix"
#define __NR32ATRA2_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,(uintptr_t)(futex_op)
#define __NR32ATRF3_lfutexlock                 "%p"
#define __NR32ATRA3_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,val
#define __NR32ATRF4_lfutexlock                 "%p"
#define __NR32ATRA4_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,timeout
#define __NR32ATRF5_lfutexlock                 "%p"
#define __NR32ATRA5_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,val2
#define __NR32ATRF0_lfutexexpr                 "%p"
#define __NR32ATRA0_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,uaddr
#define __NR32ATRF1_lfutexexpr                 "%p"
#define __NR32ATRA1_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,base
#define __NR32ATRF2_lfutexexpr                 "%p"
#define __NR32ATRA2_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,exprv
#define __NR32ATRF3_lfutexexpr                 "%Iu"
#define __NR32ATRA3_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,exprc
#define __NR32ATRF4_lfutexexpr                 "%p"
#define __NR32ATRA4_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,timeout
#define __NR32ATRF5_lfutexexpr                 "%#Ix"
#define __NR32ATRA5_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NR32ATRF0_lfutexlockexpr             "%p"
#define __NR32ATRA0_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,ulockaddr
#define __NR32ATRF1_lfutexlockexpr             "%p"
#define __NR32ATRA1_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,base
#define __NR32ATRF2_lfutexlockexpr             "%p"
#define __NR32ATRA2_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,exprv
#define __NR32ATRF3_lfutexlockexpr             "%Iu"
#define __NR32ATRA3_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,exprc
#define __NR32ATRF4_lfutexlockexpr             "%p"
#define __NR32ATRA4_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,timeout
#define __NR32ATRF5_lfutexlockexpr             "%#Ix"
#define __NR32ATRA5_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NR32ATRF0_mktty                      "%d"
#define __NR32ATRA0_mktty(keyboard, display, name, rsvd) ,(int)(keyboard)
#define __NR32ATRF1_mktty                      "%d"
#define __NR32ATRA1_mktty(keyboard, display, name, rsvd) ,(int)(display)
#define __NR32ATRF2_mktty                      "%q"
#define __NR32ATRA2_mktty(keyboard, display, name, rsvd) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF3_mktty                      "%#Ix"
#define __NR32ATRA3_mktty(keyboard, display, name, rsvd) ,(uintptr_t)(rsvd)
#define __NR32ATRF0_raiseat                    "%p"
#define __NR32ATRA0_raiseat(state, si)         ,state
#define __NR32ATRF1_raiseat                    "%p"
#define __NR32ATRA1_raiseat(state, si)         ,si
#define __NR32ATRF0_stime64                    "%p"
#define __NR32ATRA0_stime64(t)                 ,t
#define __NR32ATRF0_coredump                   "%p"
#define __NR32ATRA0_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,curr_state
#define __NR32ATRF1_coredump                   "%p"
#define __NR32ATRA1_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,orig_state
#define __NR32ATRF2_coredump                   "%p"
#define __NR32ATRA2_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_vector
#define __NR32ATRF3_coredump                   "%Iu"
#define __NR32ATRA3_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_length
#define __NR32ATRF4_coredump                   "%p"
#define __NR32ATRA4_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,exception
#define __NR32ATRF5_coredump                   "%#Ix"
#define __NR32ATRA5_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,(uintptr_t)(unwind_error)
#define __NR32ATRF0_utime64                    "%q"
#define __NR32ATRA0_utime64(filename, times)   ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utime64                    "%p"
#define __NR32ATRA1_utime64(filename, times)   ,times
#define __NR32ATRF0_ioctlf                     "%d"
#define __NR32ATRA0_ioctlf(fd, command, mode, arg) ,(int)(fd)
#define __NR32ATRF1_ioctlf                     "%#Ix"
#define __NR32ATRA1_ioctlf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NR32ATRF2_ioctlf                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_ioctlf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF3_ioctlf                     "%p"
#define __NR32ATRA3_ioctlf(fd, command, mode, arg) ,arg
#define __NR32ATRF0_fsmode                     "%I64u"
#define __NR32ATRA0_fsmode(mode)               ,mode
#define __NR32ATRF0_gettimeofday64             "%p"
#define __NR32ATRA0_gettimeofday64(tv, tz)     ,tv
#define __NR32ATRF1_gettimeofday64             "%p"
#define __NR32ATRA1_gettimeofday64(tv, tz)     ,tz
#define __NR32ATRF0_settimeofday64             "%p"
#define __NR32ATRA0_settimeofday64(tv, tz)     ,tv
#define __NR32ATRF1_settimeofday64             "%p"
#define __NR32ATRA1_settimeofday64(tv, tz)     ,tz
#define __NR32ATRF0_select64                   "%Iu"
#define __NR32ATRA0_select64(nfds, readfds, writefds, exceptfds, timeout) ,nfds
#define __NR32ATRF1_select64                   "%p"
#define __NR32ATRA1_select64(nfds, readfds, writefds, exceptfds, timeout) ,readfds
#define __NR32ATRF2_select64                   "%p"
#define __NR32ATRA2_select64(nfds, readfds, writefds, exceptfds, timeout) ,writefds
#define __NR32ATRF3_select64                   "%p"
#define __NR32ATRA3_select64(nfds, readfds, writefds, exceptfds, timeout) ,exceptfds
#define __NR32ATRF4_select64                   "%p"
#define __NR32ATRA4_select64(nfds, readfds, writefds, exceptfds, timeout) ,timeout
#define __NR32ATRF0_maplibrary                 "%p"
#define __NR32ATRA0_maplibrary(addr, flags, fd, hdrv, hdrc) ,addr
#define __NR32ATRF1_maplibrary                 "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA1_maplibrary(addr, flags, fd, hdrv, hdrc) ,(uintptr_t)(flags),(flags) & MAP_FIXED ? "MAP_FIXED" : "" \
                                                            ,((flags) & MAP_LOCKED) && ((flags) & (MAP_FIXED)) ? "|" : "",(flags) & MAP_LOCKED ? "MAP_LOCKED" : "" \
                                                            ,((flags) & MAP_NONBLOCK) && ((flags) & (MAP_FIXED|MAP_LOCKED)) ? "|" : "",(flags) & MAP_NONBLOCK ? "MAP_NONBLOCK" : "" \
                                                            ,((flags) & MAP_NORESERVE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK)) ? "|" : "",(flags) & MAP_NORESERVE ? "MAP_NORESERVE" : "" \
                                                            ,((flags) & MAP_POPULATE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE)) ? "|" : "",(flags) & MAP_POPULATE ? "MAP_POPULATE" : "" \
                                                            ,((flags) & MAP_SYNC) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE)) ? "|" : "",(flags) & MAP_SYNC ? "MAP_SYNC" : "" \
                                                            ,((flags) & MAP_DONT_MAP) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC)) ? "|" : "",(flags) & MAP_DONT_MAP ? "MAP_DONT_MAP" : "" \
                                                            ,((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP)) ? "|" : "",(flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : ""
#define __NR32ATRF2_maplibrary                 "%d"
#define __NR32ATRA2_maplibrary(addr, flags, fd, hdrv, hdrc) ,(int)(fd)
#define __NR32ATRF3_maplibrary                 "%p"
#define __NR32ATRA3_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrv
#define __NR32ATRF4_maplibrary                 "%Iu"
#define __NR32ATRA4_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrc
#define __NR32ATRF0_setitimer64                "%#Ix"
#define __NR32ATRA0_setitimer64(which, newval, oldval) ,(uintptr_t)(which)
#define __NR32ATRF1_setitimer64                "%p"
#define __NR32ATRA1_setitimer64(which, newval, oldval) ,newval
#define __NR32ATRF2_setitimer64                "%p"
#define __NR32ATRA2_setitimer64(which, newval, oldval) ,oldval
#define __NR32ATRF0_getitimer64                "%#Ix"
#define __NR32ATRA0_getitimer64(which, curr_value) ,(uintptr_t)(which)
#define __NR32ATRF1_getitimer64                "%p"
#define __NR32ATRA1_getitimer64(which, curr_value) ,curr_value
#define __NR32ATRF0_kreaddir                   "%d"
#define __NR32ATRA0_kreaddir(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR32ATRF1_kreaddir                   "%p"
#define __NR32ATRA1_kreaddir(fd, buf, bufsize, mode) ,buf
#define __NR32ATRF2_kreaddir                   "%Iu"
#define __NR32ATRA2_kreaddir(fd, buf, bufsize, mode) ,bufsize
#define __NR32ATRF3_kreaddir                   "%#Ix=%s%s%s%s%s%s%s"
#define __NR32ATRA3_kreaddir(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                     ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                     ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                     ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NR32ATRF0_readvf                     "%d"
#define __NR32ATRA0_readvf(fd, iovec, count, mode) ,(int)(fd)
#define __NR32ATRF1_readvf                     "%p"
#define __NR32ATRA1_readvf(fd, iovec, count, mode) ,iovec
#define __NR32ATRF2_readvf                     "%Iu"
#define __NR32ATRA2_readvf(fd, iovec, count, mode) ,count
#define __NR32ATRF3_readvf                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_readvf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_writevf                    "%d"
#define __NR32ATRA0_writevf(fd, iovec, count, mode) ,(int)(fd)
#define __NR32ATRF1_writevf                    "%p"
#define __NR32ATRA1_writevf(fd, iovec, count, mode) ,iovec
#define __NR32ATRF2_writevf                    "%Iu"
#define __NR32ATRA2_writevf(fd, iovec, count, mode) ,count
#define __NR32ATRF3_writevf                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_writevf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                    ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                    ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                    ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                    ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                    ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                    ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                    ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                    ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_sched_rr_get_interval64    "%Id"
#define __NR32ATRA0_sched_rr_get_interval64(pid, tms) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_rr_get_interval64    "%p"
#define __NR32ATRA1_sched_rr_get_interval64(pid, tms) ,tms
#define __NR32ATRF0_nanosleep64                "%p"
#define __NR32ATRA0_nanosleep64(req, rem)      ,req
#define __NR32ATRF1_nanosleep64                "%p"
#define __NR32ATRA1_nanosleep64(req, rem)      ,rem
#define __NR32ATRF0_rt_sigtimedwait64          "%p"
#define __NR32ATRA0_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,set
#define __NR32ATRF1_rt_sigtimedwait64          "%p"
#define __NR32ATRA1_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,info
#define __NR32ATRF2_rt_sigtimedwait64          "%p"
#define __NR32ATRA2_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,timeout
#define __NR32ATRF3_rt_sigtimedwait64          "%Iu"
#define __NR32ATRA3_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,sigsetsize
#define __NR32ATRF0_pread64f                   "%d"
#define __NR32ATRA0_pread64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NR32ATRF1_pread64f                   "%p"
#define __NR32ATRA1_pread64f(fd, buf, bufsize, offset, mode) ,buf
#define __NR32ATRF2_pread64f                   "%Iu"
#define __NR32ATRA2_pread64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NR32ATRF3_pread64f                   "%I64u"
#define __NR32ATRA3_pread64f(fd, buf, bufsize, offset, mode) ,offset
#define __NR32ATRF4_pread64f                   "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_pread64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                             ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                             ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                             ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                             ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                             ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                             ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                             ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                             ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_pwrite64f                  "%d"
#define __NR32ATRA0_pwrite64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NR32ATRF1_pwrite64f                  "%p"
#define __NR32ATRA1_pwrite64f(fd, buf, bufsize, offset, mode) ,buf
#define __NR32ATRF2_pwrite64f                  "%Iu"
#define __NR32ATRA2_pwrite64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NR32ATRF3_pwrite64f                  "%I64u"
#define __NR32ATRA3_pwrite64f(fd, buf, bufsize, offset, mode) ,offset
#define __NR32ATRF4_pwrite64f                  "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_pwrite64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                              ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                              ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                              ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                              ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                              ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                              ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                              ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                              ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_kstat                      "%q"
#define __NR32ATRA0_kstat(filename, statbuf)   ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_kstat                      "%p"
#define __NR32ATRA1_kstat(filename, statbuf)   ,statbuf
#define __NR32ATRF0_klstat                     "%q"
#define __NR32ATRA0_klstat(filename, statbuf)  ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_klstat                     "%p"
#define __NR32ATRA1_klstat(filename, statbuf)  ,statbuf
#define __NR32ATRF0_kfstat                     "%d"
#define __NR32ATRA0_kfstat(fd, statbuf)        ,(int)(fd)
#define __NR32ATRF1_kfstat                     "%p"
#define __NR32ATRA1_kfstat(fd, statbuf)        ,statbuf
#define __NR32ATRF0_kreaddirf                  "%d"
#define __NR32ATRA0_kreaddirf(fd, buf, bufsize, mode, iomode) ,(int)(fd)
#define __NR32ATRF1_kreaddirf                  "%p"
#define __NR32ATRA1_kreaddirf(fd, buf, bufsize, mode, iomode) ,buf
#define __NR32ATRF2_kreaddirf                  "%Iu"
#define __NR32ATRA2_kreaddirf(fd, buf, bufsize, mode, iomode) ,bufsize
#define __NR32ATRF3_kreaddirf                  "%#Ix=%s%s%s%s%s%s%s"
#define __NR32ATRA3_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                              ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                              ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                              ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NR32ATRF4_kreaddirf                  "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(iomode),(iomode) & IO_WRONLY ? "IO_WRONLY" : (iomode) ? "" : "IO_RDONLY" \
                                                              ,((iomode) & IO_RDWR) && ((iomode) & (IO_WRONLY)) ? "|" : "",(iomode) & IO_RDWR ? "IO_RDWR" : "" \
                                                              ,((iomode) & IO_CLOEXEC) && ((iomode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(iomode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                              ,((iomode) & IO_CLOFORK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(iomode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                              ,((iomode) & IO_APPEND) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(iomode) & IO_APPEND ? "IO_APPEND" : "" \
                                                              ,((iomode) & IO_NONBLOCK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(iomode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                              ,((iomode) & IO_SYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(iomode) & IO_SYNC ? "IO_SYNC" : "" \
                                                              ,((iomode) & IO_ASYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(iomode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                              ,((iomode) & IO_DIRECT) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(iomode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_timer_settime64            "?"
#define __NR32ATRA0_timer_settime64(timerid, flags, value, ovalue) /* nothing */
#define __NR32ATRF1_timer_settime64            "%#Ix"
#define __NR32ATRA1_timer_settime64(timerid, flags, value, ovalue) ,(uintptr_t)(flags)
#define __NR32ATRF2_timer_settime64            "%p"
#define __NR32ATRA2_timer_settime64(timerid, flags, value, ovalue) ,value
#define __NR32ATRF3_timer_settime64            "%p"
#define __NR32ATRA3_timer_settime64(timerid, flags, value, ovalue) ,ovalue
#define __NR32ATRF0_timer_gettime64            "?"
#define __NR32ATRA0_timer_gettime64(timerid, value) /* nothing */
#define __NR32ATRF1_timer_gettime64            "%p"
#define __NR32ATRA1_timer_gettime64(timerid, value) ,value
#define __NR32ATRF0_clock_settime64            "?"
#define __NR32ATRA0_clock_settime64(clock_id, tp) /* nothing */
#define __NR32ATRF1_clock_settime64            "%p"
#define __NR32ATRA1_clock_settime64(clock_id, tp) ,tp
#define __NR32ATRF0_clock_gettime64            "?"
#define __NR32ATRA0_clock_gettime64(clock_id, tp) /* nothing */
#define __NR32ATRF1_clock_gettime64            "%p"
#define __NR32ATRA1_clock_gettime64(clock_id, tp) ,tp
#define __NR32ATRF0_clock_getres64             "?"
#define __NR32ATRA0_clock_getres64(clock_id, res) /* nothing */
#define __NR32ATRF1_clock_getres64             "%p"
#define __NR32ATRA1_clock_getres64(clock_id, res) ,res
#define __NR32ATRF0_clock_nanosleep64          "?"
#define __NR32ATRA0_clock_nanosleep64(clock_id, flags, requested_time, remaining) /* nothing */
#define __NR32ATRF1_clock_nanosleep64          "%#Ix"
#define __NR32ATRA1_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,(uintptr_t)(flags)
#define __NR32ATRF2_clock_nanosleep64          "%p"
#define __NR32ATRA2_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,requested_time
#define __NR32ATRF3_clock_nanosleep64          "%p"
#define __NR32ATRA3_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,remaining
#define __NR32ATRF0_utimes64                   "%q"
#define __NR32ATRA0_utimes64(filename, times)  ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utimes64                   "%p"
#define __NR32ATRA1_utimes64(filename, times)  ,times
#define __NR32ATRF0_fmkdirat                   "%d"
#define __NR32ATRA0_fmkdirat(dirfd, pathname, mode, flags) ,(int)(dirfd)
#define __NR32ATRF1_fmkdirat                   "%q"
#define __NR32ATRA1_fmkdirat(dirfd, pathname, mode, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF2_fmkdirat                   "%#Io"
#define __NR32ATRA2_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(mode)
#define __NR32ATRF3_fmkdirat                   "%#Ix=%s"
#define __NR32ATRA3_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_fmknodat                   "%d"
#define __NR32ATRA0_fmknodat(dirfd, nodename, mode, dev, flags) ,(int)(dirfd)
#define __NR32ATRF1_fmknodat                   "%q"
#define __NR32ATRA1_fmknodat(dirfd, nodename, mode, dev, flags) ,(validate_readable_opt(nodename,1),nodename)
#define __NR32ATRF2_fmknodat                   "%#Io"
#define __NR32ATRA2_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(mode)
#define __NR32ATRF3_fmknodat                   "%.2x:%.2x"
#define __NR32ATRA3_fmknodat(dirfd, nodename, mode, dev, flags) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF4_fmknodat                   "%#Ix=%s"
#define __NR32ATRA4_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_futimesat64                "%d"
#define __NR32ATRA0_futimesat64(dirfd, filename, times) ,(int)(dirfd)
#define __NR32ATRF1_futimesat64                "%p"
#define __NR32ATRA1_futimesat64(dirfd, filename, times) ,filename
#define __NR32ATRF2_futimesat64                "%p"
#define __NR32ATRA2_futimesat64(dirfd, filename, times) ,times
#define __NR32ATRF0_kfstatat                   "%d"
#define __NR32ATRA0_kfstatat(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NR32ATRF1_kfstatat                   "%q"
#define __NR32ATRA1_kfstatat(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_kfstatat                   "%p"
#define __NR32ATRA2_kfstatat(dirfd, filename, statbuf, flags) ,statbuf
#define __NR32ATRF3_kfstatat                   "%#Ix=%s%s%s"
#define __NR32ATRA3_kfstatat(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                              ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_frenameat                  "%d"
#define __NR32ATRA0_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(oldfd)
#define __NR32ATRF1_frenameat                  "%q"
#define __NR32ATRA1_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(oldname,1),oldname)
#define __NR32ATRF2_frenameat                  "%d"
#define __NR32ATRA2_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(newfd)
#define __NR32ATRF3_frenameat                  "%q"
#define __NR32ATRA3_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR32ATRF4_frenameat                  "%#Ix=%s"
#define __NR32ATRA4_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_fsymlinkat                 "%q"
#define __NR32ATRA0_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(link_text,1),link_text)
#define __NR32ATRF1_fsymlinkat                 "%d"
#define __NR32ATRA1_fsymlinkat(link_text, tofd, target_path, flags) ,(int)(tofd)
#define __NR32ATRF2_fsymlinkat                 "%q"
#define __NR32ATRA2_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF3_fsymlinkat                 "%#Ix=%s"
#define __NR32ATRA3_fsymlinkat(link_text, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_freadlinkat                "%d"
#define __NR32ATRA0_freadlinkat(dirfd, path, buf, buflen, flags) ,(int)(dirfd)
#define __NR32ATRF1_freadlinkat                "%q"
#define __NR32ATRA1_freadlinkat(dirfd, path, buf, buflen, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF2_freadlinkat                "%p"
#define __NR32ATRA2_freadlinkat(dirfd, path, buf, buflen, flags) ,buf
#define __NR32ATRF3_freadlinkat                "%Iu"
#define __NR32ATRA3_freadlinkat(dirfd, path, buf, buflen, flags) ,buflen
#define __NR32ATRF4_freadlinkat                "%#Ix=%s%s%s"
#define __NR32ATRA4_freadlinkat(dirfd, path, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_pselect6_64                "%Iu"
#define __NR32ATRA0_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,nfds
#define __NR32ATRF1_pselect6_64                "%p"
#define __NR32ATRA1_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,readfds
#define __NR32ATRF2_pselect6_64                "%p"
#define __NR32ATRA2_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,writefds
#define __NR32ATRF3_pselect6_64                "%p"
#define __NR32ATRA3_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,exceptfds
#define __NR32ATRF4_pselect6_64                "%p"
#define __NR32ATRA4_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,timeout
#define __NR32ATRF5_pselect6_64                "%p"
#define __NR32ATRA5_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,sigmask_sigset_and_len
#define __NR32ATRF0_ppoll64                    "%p"
#define __NR32ATRA0_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,fds
#define __NR32ATRF1_ppoll64                    "%Iu"
#define __NR32ATRA1_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,nfds
#define __NR32ATRF2_ppoll64                    "%p"
#define __NR32ATRA2_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,timeout_ts
#define __NR32ATRF3_ppoll64                    "%p"
#define __NR32ATRA3_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigmask
#define __NR32ATRF4_ppoll64                    "%Iu"
#define __NR32ATRA4_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigsetsize
#define __NR32ATRF0_utimensat64                "%d"
#define __NR32ATRA0_utimensat64(dirfd, filename, times, flags) ,(int)(dirfd)
#define __NR32ATRF1_utimensat64                "%q"
#define __NR32ATRA1_utimensat64(dirfd, filename, times, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_utimensat64                "%p"
#define __NR32ATRA2_utimensat64(dirfd, filename, times, flags) ,times
#define __NR32ATRF3_utimensat64                "%#Ix=%s%s%s%s%s"
#define __NR32ATRA3_utimensat64(dirfd, filename, times, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                               ,((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                               ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_fallocate64                "%d"
#define __NR32ATRA0_fallocate64(fd, mode, offset, length) ,(int)(fd)
#define __NR32ATRF1_fallocate64                "%#Ix"
#define __NR32ATRA1_fallocate64(fd, mode, offset, length) ,(uintptr_t)(mode)
#define __NR32ATRF2_fallocate64                "%I64u"
#define __NR32ATRA2_fallocate64(fd, mode, offset, length) ,offset
#define __NR32ATRF3_fallocate64                "%I64u"
#define __NR32ATRA3_fallocate64(fd, mode, offset, length) ,length
#define __NR32ATRF0_timerfd_settime64          "%d"
#define __NR32ATRA0_timerfd_settime64(ufd, flags, utmr, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_settime64          "%#Ix"
#define __NR32ATRA1_timerfd_settime64(ufd, flags, utmr, otmr) ,(uintptr_t)(flags)
#define __NR32ATRF2_timerfd_settime64          "%p"
#define __NR32ATRA2_timerfd_settime64(ufd, flags, utmr, otmr) ,utmr
#define __NR32ATRF3_timerfd_settime64          "%p"
#define __NR32ATRA3_timerfd_settime64(ufd, flags, utmr, otmr) ,otmr
#define __NR32ATRF0_timerfd_gettime64          "%d"
#define __NR32ATRA0_timerfd_gettime64(ufd, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_gettime64          "%p"
#define __NR32ATRA1_timerfd_gettime64(ufd, otmr) ,otmr
#define __NR32ATRF0_preadvf                    "%d"
#define __NR32ATRA0_preadvf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NR32ATRF1_preadvf                    "%p"
#define __NR32ATRA1_preadvf(fd, iovec, count, offset, mode) ,iovec
#define __NR32ATRF2_preadvf                    "%Iu"
#define __NR32ATRA2_preadvf(fd, iovec, count, offset, mode) ,count
#define __NR32ATRF3_preadvf                    "%I64u"
#define __NR32ATRA3_preadvf(fd, iovec, count, offset, mode) ,offset
#define __NR32ATRF4_preadvf                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_preadvf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                            ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                            ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                            ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                            ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                            ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                            ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                            ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                            ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_pwritevf                   "%d"
#define __NR32ATRA0_pwritevf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NR32ATRF1_pwritevf                   "%p"
#define __NR32ATRA1_pwritevf(fd, iovec, count, offset, mode) ,iovec
#define __NR32ATRF2_pwritevf                   "%Iu"
#define __NR32ATRA2_pwritevf(fd, iovec, count, offset, mode) ,count
#define __NR32ATRF3_pwritevf                   "%I64u"
#define __NR32ATRA3_pwritevf(fd, iovec, count, offset, mode) ,offset
#define __NR32ATRF4_pwritevf                   "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_pwritevf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                             ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                             ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                             ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                             ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                             ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                             ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                             ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                             ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_recvmmsg64                 "%d"
#define __NR32ATRA0_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,(int)(sockfd)
#define __NR32ATRF1_recvmmsg64                 "%p"
#define __NR32ATRA1_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,vmessages
#define __NR32ATRF2_recvmmsg64                 "%Iu"
#define __NR32ATRA2_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,vlen
#define __NR32ATRF3_recvmmsg64                 "%#Ix"
#define __NR32ATRA3_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,(uintptr_t)(flags)
#define __NR32ATRF4_recvmmsg64                 "%p"
#define __NR32ATRA4_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,tmo
#endif /* __WANT_SYSCALL_ARGUMENT_FORMAT */

#ifdef __WANT_SYSCALL_ARGUMENT_COUNT
#define __NR32AC_exit                       1
#define __NR32AC_fork                       0
#define __NR32AC_read                       3
#define __NR32AC_write                      3
#define __NR32AC_open                       3
#define __NR32AC_close                      1
#define __NR32AC_waitpid                    3
#define __NR32AC_creat                      2
#define __NR32AC_link                       2
#define __NR32AC_unlink                     1
#define __NR32AC_execve                     3
#define __NR32AC_chdir                      1
#define __NR32AC_time                       1
#define __NR32AC_mknod                      3
#define __NR32AC_chmod                      2
#define __NR32AC_lchown                     3
#define __NR32AC_linux_oldstat              2
#define __NR32AC_lseek                      3
#define __NR32AC_getpid                     0
#define __NR32AC_mount                      5
#define __NR32AC_umount                     1
#define __NR32AC_setuid                     1
#define __NR32AC_getuid                     0
#define __NR32AC_stime                      1
#define __NR32AC_ptrace                     4
#define __NR32AC_alarm                      1
#define __NR32AC_linux_oldfstat             2
#define __NR32AC_pause                      0
#define __NR32AC_utime                      2
#define __NR32AC_access                     2
#define __NR32AC_nice                       1
#define __NR32AC_ftime                      1
#define __NR32AC_sync                       0
#define __NR32AC_kill                       2
#define __NR32AC_rename                     2
#define __NR32AC_mkdir                      2
#define __NR32AC_rmdir                      1
#define __NR32AC_dup                        1
#define __NR32AC_pipe                       1
#define __NR32AC_times                      1
#define __NR32AC_brk                        1
#define __NR32AC_setgid                     1
#define __NR32AC_getgid                     0
#define __NR32AC_signal                     2
#define __NR32AC_geteuid                    0
#define __NR32AC_getegid                    0
#define __NR32AC_acct                       1
#define __NR32AC_umount2                    2
#define __NR32AC_ioctl                      3
#define __NR32AC_fcntl                      3
#define __NR32AC_setpgid                    2
#define __NR32AC_oldolduname                1
#define __NR32AC_umask                      1
#define __NR32AC_chroot                     1
#define __NR32AC_ustat                      2
#define __NR32AC_dup2                       2
#define __NR32AC_getppid                    0
#define __NR32AC_getpgrp                    0
#define __NR32AC_setsid                     0
#define __NR32AC_sigaction                  3
#define __NR32AC_sgetmask                   0
#define __NR32AC_ssetmask                   1
#define __NR32AC_setreuid                   2
#define __NR32AC_setregid                   2
#define __NR32AC_sigsuspend                 1
#define __NR32AC_sigpending                 1
#define __NR32AC_sethostname                2
#define __NR32AC_setrlimit                  2
#define __NR32AC_getrlimit                  2
#define __NR32AC_getrusage                  2
#define __NR32AC_gettimeofday               2
#define __NR32AC_settimeofday               2
#define __NR32AC_getgroups                  2
#define __NR32AC_setgroups                  2
#define __NR32AC_select                     5
#define __NR32AC_symlink                    2
#define __NR32AC_linux_oldlstat             2
#define __NR32AC_readlink                   3
#define __NR32AC_swapon                     2
#define __NR32AC_reboot                     1
#define __NR32AC_readdir                    3
#define __NR32AC_mmap                       6
#define __NR32AC_munmap                     2
#define __NR32AC_truncate                   2
#define __NR32AC_ftruncate                  2
#define __NR32AC_fchmod                     2
#define __NR32AC_fchown                     3
#define __NR32AC_getpriority                2
#define __NR32AC_setpriority                3
#define __NR32AC_profil                     4
#define __NR32AC_statfs                     2
#define __NR32AC_fstatfs                    2
#define __NR32AC_ioperm                     3
#define __NR32AC_socketcall                 2
#define __NR32AC_syslog                     3
#define __NR32AC_setitimer                  3
#define __NR32AC_getitimer                  2
#define __NR32AC_linux_stat32               2
#define __NR32AC_linux_lstat32              2
#define __NR32AC_linux_fstat32              2
#define __NR32AC_olduname                   1
#define __NR32AC_iopl                       1
#define __NR32AC_vhangup                    0
#define __NR32AC_wait4                      4
#define __NR32AC_swapoff                    1
#define __NR32AC_sysinfo                    1
#define __NR32AC_fsync                      1
#define __NR32AC_sigreturn                  6
#define __NR32AC_clone                      5
#define __NR32AC_setdomainname              2
#define __NR32AC_uname                      1
#define __NR32AC_modify_ldt                 3
#define __NR32AC_mprotect                   3
#define __NR32AC_sigprocmask                3
#define __NR32AC_getpgid                    1
#define __NR32AC_fchdir                     1
#define __NR32AC_setfsuid                   1
#define __NR32AC_setfsgid                   1
#define __NR32AC__llseek                    4
#define __NR32AC_getdents                   3
#define __NR32AC_flock                      2
#define __NR32AC_msync                      3
#define __NR32AC_readv                      3
#define __NR32AC_writev                     3
#define __NR32AC_getsid                     1
#define __NR32AC_fdatasync                  1
#define __NR32AC_mlock                      2
#define __NR32AC_munlock                    2
#define __NR32AC_mlockall                   1
#define __NR32AC_munlockall                 0
#define __NR32AC_sched_setparam             2
#define __NR32AC_sched_getparam             2
#define __NR32AC_sched_setscheduler         3
#define __NR32AC_sched_getscheduler         1
#define __NR32AC_sched_yield                0
#define __NR32AC_sched_get_priority_max     1
#define __NR32AC_sched_get_priority_min     1
#define __NR32AC_sched_rr_get_interval      2
#define __NR32AC_nanosleep                  2
#define __NR32AC_mremap                     5
#define __NR32AC_setresuid                  3
#define __NR32AC_getresuid                  3
#define __NR32AC_poll                       3
#define __NR32AC_setresgid                  3
#define __NR32AC_getresgid                  3
#define __NR32AC_rt_sigaction               4
#define __NR32AC_rt_sigprocmask             4
#define __NR32AC_rt_sigpending              2
#define __NR32AC_rt_sigtimedwait            4
#define __NR32AC_rt_sigqueueinfo            3
#define __NR32AC_rt_sigsuspend              2
#define __NR32AC_pread64                    4
#define __NR32AC_pwrite64                   4
#define __NR32AC_chown                      3
#define __NR32AC_getcwd                     2
#define __NR32AC_sigaltstack                2
#define __NR32AC_sendfile                   4
#define __NR32AC_vfork                      0
#define __NR32AC_mmap2                      6
#define __NR32AC_truncate64                 2
#define __NR32AC_ftruncate64                2
#define __NR32AC_linux_stat64               2
#define __NR32AC_linux_lstat64              2
#define __NR32AC_linux_fstat64              2
#define __NR32AC_lchown32                   3
#define __NR32AC_getuid32                   0
#define __NR32AC_getgid32                   0
#define __NR32AC_geteuid32                  0
#define __NR32AC_getegid32                  0
#define __NR32AC_setreuid32                 2
#define __NR32AC_setregid32                 2
#define __NR32AC_getgroups32                2
#define __NR32AC_setgroups32                2
#define __NR32AC_fchown32                   3
#define __NR32AC_setresuid32                3
#define __NR32AC_getresuid32                3
#define __NR32AC_setresgid32                3
#define __NR32AC_getresgid32                3
#define __NR32AC_chown32                    3
#define __NR32AC_setuid32                   1
#define __NR32AC_setgid32                   1
#define __NR32AC_setfsuid32                 1
#define __NR32AC_setfsgid32                 1
#define __NR32AC_mincore                    3
#define __NR32AC_madvise                    3
#define __NR32AC_getdents64                 3
#define __NR32AC_fcntl64                    3
#define __NR32AC_gettid                     0
#define __NR32AC_readahead                  3
#define __NR32AC_setxattr                   5
#define __NR32AC_lsetxattr                  5
#define __NR32AC_fsetxattr                  5
#define __NR32AC_getxattr                   4
#define __NR32AC_lgetxattr                  4
#define __NR32AC_fgetxattr                  4
#define __NR32AC_listxattr                  3
#define __NR32AC_llistxattr                 3
#define __NR32AC_flistxattr                 3
#define __NR32AC_removexattr                2
#define __NR32AC_lremovexattr               2
#define __NR32AC_fremovexattr               2
#define __NR32AC_tkill                      2
#define __NR32AC_sendfile64                 4
#define __NR32AC_futex                      6
#define __NR32AC_sched_setaffinity          3
#define __NR32AC_sched_getaffinity          3
#define __NR32AC_exit_group                 1
#define __NR32AC_epoll_create               1
#define __NR32AC_epoll_ctl                  4
#define __NR32AC_epoll_wait                 4
#define __NR32AC_remap_file_pages           5
#define __NR32AC_set_tid_address            1
#define __NR32AC_timer_create               3
#define __NR32AC_timer_settime              4
#define __NR32AC_timer_gettime              2
#define __NR32AC_timer_getoverrun           1
#define __NR32AC_timer_delete               1
#define __NR32AC_clock_settime              2
#define __NR32AC_clock_gettime              2
#define __NR32AC_clock_getres               2
#define __NR32AC_clock_nanosleep            4
#define __NR32AC_statfs64                   2
#define __NR32AC_fstatfs64                  2
#define __NR32AC_tgkill                     3
#define __NR32AC_utimes                     2
#define __NR32AC_waitid                     5
#define __NR32AC_ioprio_set                 3
#define __NR32AC_ioprio_get                 2
#define __NR32AC_openat                     4
#define __NR32AC_mkdirat                    3
#define __NR32AC_mknodat                    4
#define __NR32AC_fchownat                   5
#define __NR32AC_futimesat                  3
#define __NR32AC_linux_fstatat64            4
#define __NR32AC_unlinkat                   3
#define __NR32AC_renameat                   4
#define __NR32AC_linkat                     5
#define __NR32AC_symlinkat                  3
#define __NR32AC_readlinkat                 4
#define __NR32AC_fchmodat                   4
#define __NR32AC_faccessat                  4
#define __NR32AC_pselect6                   6
#define __NR32AC_ppoll                      5
#define __NR32AC_unshare                    1
#define __NR32AC_splice                     6
#define __NR32AC_sync_file_range            4
#define __NR32AC_tee                        4
#define __NR32AC_vmsplice                   4
#define __NR32AC_getcpu                     3
#define __NR32AC_epoll_pwait                5
#define __NR32AC_utimensat                  4
#define __NR32AC_signalfd                   3
#define __NR32AC_timerfd_create             2
#define __NR32AC_eventfd                    1
#define __NR32AC_fallocate                  4
#define __NR32AC_timerfd_settime            4
#define __NR32AC_timerfd_gettime            2
#define __NR32AC_signalfd4                  4
#define __NR32AC_eventfd2                   2
#define __NR32AC_epoll_create1              1
#define __NR32AC_dup3                       3
#define __NR32AC_pipe2                      2
#define __NR32AC_preadv                     4
#define __NR32AC_pwritev                    4
#define __NR32AC_rt_tgsigqueueinfo          4
#define __NR32AC_recvmmsg                   5
#define __NR32AC_prlimit64                  4
#define __NR32AC_name_to_handle_at          5
#define __NR32AC_open_by_handle_at          3
#define __NR32AC_syncfs                     1
#define __NR32AC_sendmmsg                   4
#define __NR32AC_setns                      2
#define __NR32AC_process_vm_readv           6
#define __NR32AC_process_vm_writev          6
#define __NR32AC_kcmp                       5
#define __NR32AC_renameat2                  5
#define __NR32AC_execveat                   5
#define __NR32AC_socket                     3
#define __NR32AC_socketpair                 4
#define __NR32AC_bind                       3
#define __NR32AC_connect                    3
#define __NR32AC_listen                     2
#define __NR32AC_accept4                    4
#define __NR32AC_getsockopt                 5
#define __NR32AC_setsockopt                 5
#define __NR32AC_getsockname                3
#define __NR32AC_getpeername                3
#define __NR32AC_sendto                     6
#define __NR32AC_sendmsg                    3
#define __NR32AC_recvfrom                   6
#define __NR32AC_recvmsg                    3
#define __NR32AC_shutdown                   2
#define __NR32AC_hop                        3
#define __NR32AC_hopf                       4
#define __NR32AC_readf                      4
#define __NR32AC_writef                     4
#define __NR32AC_detach                     1
#define __NR32AC_getdrives                  0
#define __NR32AC_frealpath4                 4
#define __NR32AC_frealpathat                5
#define __NR32AC_rpc_schedule               4
#define __NR32AC_sysctl                     2
#define __NR32AC_openpty                    5
#define __NR32AC_fchdirat                   3
#define __NR32AC_time64                     1
#define __NR32AC_set_exception_handler      3
#define __NR32AC_get_exception_handler      3
#define __NR32AC_set_library_listdef        1
#define __NR32AC_debugtrap                  2
#define __NR32AC_lfutex                     5
#define __NR32AC_lseek64                    3
#define __NR32AC_lfutexlock                 6
#define __NR32AC_lfutexexpr                 6
#define __NR32AC_lfutexlockexpr             6
#define __NR32AC_mktty                      4
#define __NR32AC_raiseat                    2
#define __NR32AC_stime64                    1
#define __NR32AC_coredump                   6
#define __NR32AC_utime64                    2
#define __NR32AC_ioctlf                     4
#define __NR32AC_fsmode                     1
#define __NR32AC_gettimeofday64             2
#define __NR32AC_settimeofday64             2
#define __NR32AC_select64                   5
#define __NR32AC_maplibrary                 5
#define __NR32AC_setitimer64                3
#define __NR32AC_getitimer64                2
#define __NR32AC_kreaddir                   4
#define __NR32AC_readvf                     4
#define __NR32AC_writevf                    4
#define __NR32AC_rpc_service                0
#define __NR32AC_sched_rr_get_interval64    2
#define __NR32AC_nanosleep64                2
#define __NR32AC_rt_sigtimedwait64          4
#define __NR32AC_pread64f                   5
#define __NR32AC_pwrite64f                  5
#define __NR32AC_kstat                      2
#define __NR32AC_klstat                     2
#define __NR32AC_kfstat                     2
#define __NR32AC_kreaddirf                  5
#define __NR32AC_timer_settime64            4
#define __NR32AC_timer_gettime64            2
#define __NR32AC_clock_settime64            2
#define __NR32AC_clock_gettime64            2
#define __NR32AC_clock_getres64             2
#define __NR32AC_clock_nanosleep64          4
#define __NR32AC_utimes64                   2
#define __NR32AC_fmkdirat                   4
#define __NR32AC_fmknodat                   5
#define __NR32AC_futimesat64                3
#define __NR32AC_kfstatat                   4
#define __NR32AC_frenameat                  5
#define __NR32AC_fsymlinkat                 4
#define __NR32AC_freadlinkat                5
#define __NR32AC_pselect6_64                6
#define __NR32AC_ppoll64                    5
#define __NR32AC_utimensat64                4
#define __NR32AC_fallocate64                4
#define __NR32AC_timerfd_settime64          4
#define __NR32AC_timerfd_gettime64          2
#define __NR32AC_preadvf                    5
#define __NR32AC_pwritevf                   5
#define __NR32AC_recvmmsg64                 5
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT */

#ifdef __WANT_SYSCALL_ARGUMENT_LIST_MAKER
#define __NR32AM_exit(a, b, c, d, e, f)                       (__syscall_ulong_t)a
#define __NR32AM_fork(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_read(a, b, c, d, e, f)                       (__fd_t)a, (void *)b, (__size_t)c
#define __NR32AM_write(a, b, c, d, e, f)                      (__fd_t)a, (void const *)b, (__size_t)c
#define __NR32AM_open(a, b, c, d, e, f)                       (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NR32AM_close(a, b, c, d, e, f)                      (__fd_t)a
#define __NR32AM_waitpid(a, b, c, d, e, f)                    (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c
#define __NR32AM_creat(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b
#define __NR32AM_link(a, b, c, d, e, f)                       (char const *)a, (char const *)b
#define __NR32AM_unlink(a, b, c, d, e, f)                     (char const *)a
#define __NR32AM_execve(a, b, c, d, e, f)                     (char const *)a, (char const *const *)b, (char const *const *)c
#define __NR32AM_chdir(a, b, c, d, e, f)                      (char const *)a
#define __NR32AM_time(a, b, c, d, e, f)                       (__time32_t *)a
#define __NR32AM_mknod(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b, (__dev_t)c
#define __NR32AM_chmod(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b
#define __NR32AM_lchown(a, b, c, d, e, f)                     (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_linux_oldstat(a, b, c, d, e, f)              (char const *)a, (struct linux_oldstat *)b
#define __NR32AM_lseek(a, b, c, d, e, f)                      (__fd_t)a, (__int32_t)b, (__syscall_ulong_t)c
#define __NR32AM_getpid(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_mount(a, b, c, d, e, f)                      (char const *)a, (char const *)b, (char const *)c, (__syscall_ulong_t)d, (void const *)e
#define __NR32AM_umount(a, b, c, d, e, f)                     (char const *)a
#define __NR32AM_setuid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NR32AM_getuid(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_stime(a, b, c, d, e, f)                      (__time32_t const *)a
#define __NR32AM_ptrace(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__pid_t)b, (void *)c, (void *)d
#define __NR32AM_alarm(a, b, c, d, e, f)                      (__syscall_ulong_t)a
#define __NR32AM_linux_oldfstat(a, b, c, d, e, f)             (__fd_t)a, (struct linux_oldstat *)b
#define __NR32AM_pause(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_utime(a, b, c, d, e, f)                      (char const *)a, (struct __utimbuf32 const *)b
#define __NR32AM_access(a, b, c, d, e, f)                     (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_nice(a, b, c, d, e, f)                       (__syscall_slong_t)a
#define __NR32AM_ftime(a, b, c, d, e, f)                      (struct timeb *)a
#define __NR32AM_sync(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_kill(a, b, c, d, e, f)                       (__pid_t)a, (__syscall_ulong_t)b
#define __NR32AM_rename(a, b, c, d, e, f)                     (char const *)a, (char const *)b
#define __NR32AM_mkdir(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b
#define __NR32AM_rmdir(a, b, c, d, e, f)                      (char const *)a
#define __NR32AM_dup(a, b, c, d, e, f)                        (__fd_t)a
#define __NR32AM_pipe(a, b, c, d, e, f)                       (/*[2]*/__fd_t *)a
#define __NR32AM_times(a, b, c, d, e, f)                      (struct tms *)a
#define __NR32AM_brk(a, b, c, d, e, f)                        (void *)a
#define __NR32AM_setgid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NR32AM_getgid(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_signal(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__sighandler_t)b
#define __NR32AM_geteuid(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_getegid(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_acct(a, b, c, d, e, f)                       (char const *)a
#define __NR32AM_umount2(a, b, c, d, e, f)                    (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_ioctl(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NR32AM_fcntl(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NR32AM_setpgid(a, b, c, d, e, f)                    (__pid_t)a, (__pid_t)b
#define __NR32AM_oldolduname(a, b, c, d, e, f)                (struct linux_oldolduname *)a
#define __NR32AM_umask(a, b, c, d, e, f)                      (__mode_t)a
#define __NR32AM_chroot(a, b, c, d, e, f)                     (char const *)a
#define __NR32AM_ustat(a, b, c, d, e, f)                      (__dev_t)a, (struct ustat *)b
#define __NR32AM_dup2(a, b, c, d, e, f)                       (__fd_t)a, (__fd_t)b
#define __NR32AM_getppid(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_getpgrp(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_setsid(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_sigaction(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct sigaction const *)b, (struct sigaction *)c
#define __NR32AM_sgetmask(a, b, c, d, e, f)                   /* nothing */
#define __NR32AM_ssetmask(a, b, c, d, e, f)                   (__syscall_ulong_t)a
#define __NR32AM_setreuid(a, b, c, d, e, f)                   (__uint16_t)a, (__uint16_t)b
#define __NR32AM_setregid(a, b, c, d, e, f)                   (__uint16_t)a, (__uint16_t)b
#define __NR32AM_sigsuspend(a, b, c, d, e, f)                 (struct __sigset_struct const *)a
#define __NR32AM_sigpending(a, b, c, d, e, f)                 (struct __sigset_struct *)a
#define __NR32AM_sethostname(a, b, c, d, e, f)                (char const *)a, (__size_t)b
#define __NR32AM_setrlimit(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct rlimit const *)b
#define __NR32AM_getrlimit(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct rlimit *)b
#define __NR32AM_getrusage(a, b, c, d, e, f)                  (__syscall_slong_t)a, (struct rusage *)b
#define __NR32AM_gettimeofday(a, b, c, d, e, f)               (struct __timeval32 *)a, (struct timezone *)b
#define __NR32AM_settimeofday(a, b, c, d, e, f)               (struct __timeval32 const *)a, (struct timezone const *)b
#define __NR32AM_getgroups(a, b, c, d, e, f)                  (__size_t)a, (/*[]*/__uint16_t *)b
#define __NR32AM_setgroups(a, b, c, d, e, f)                  (__size_t)a, (__uint16_t const *)b
#define __NR32AM_select(a, b, c, d, e, f)                     (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timeval32 *)e
#define __NR32AM_symlink(a, b, c, d, e, f)                    (char const *)a, (char const *)b
#define __NR32AM_linux_oldlstat(a, b, c, d, e, f)             (char const *)a, (struct linux_oldstat *)b
#define __NR32AM_readlink(a, b, c, d, e, f)                   (char const *)a, (char *)b, (__size_t)c
#define __NR32AM_swapon(a, b, c, d, e, f)                     (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_reboot(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NR32AM_readdir(a, b, c, d, e, f)                    (__fd_t)a, (struct old_linux_dirent *)b, (__size_t)c
#define __NR32AM_mmap(a, b, c, d, e, f)                       (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NR32AM_munmap(a, b, c, d, e, f)                     (void *)a, (__size_t)b
#define __NR32AM_truncate(a, b, c, d, e, f)                   (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_ftruncate(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_fchmod(a, b, c, d, e, f)                     (__fd_t)a, (__mode_t)b
#define __NR32AM_fchown(a, b, c, d, e, f)                     (__fd_t)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getpriority(a, b, c, d, e, f)                (__syscall_ulong_t)a, (__id_t)b
#define __NR32AM_setpriority(a, b, c, d, e, f)                (__syscall_ulong_t)a, (__id_t)b, (__syscall_ulong_t)c
#define __NR32AM_profil(a, b, c, d, e, f)                     (__uint16_t *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_statfs(a, b, c, d, e, f)                     (char const *)a, (struct __statfs32 *)b
#define __NR32AM_fstatfs(a, b, c, d, e, f)                    (__fd_t)a, (struct __statfs32 *)b
#define __NR32AM_ioperm(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AM_socketcall(a, b, c, d, e, f)                 (int)a, (unsigned long *)b
#define __NR32AM_syslog(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (char const *)b, (__size_t)c
#define __NR32AM_setitimer(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimerval32 const *)b, (struct __itimerval32 *)c
#define __NR32AM_getitimer(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimerval32 *)b
#define __NR32AM_linux_stat32(a, b, c, d, e, f)               (char const *)a, (struct linux_stat32 *)b
#define __NR32AM_linux_lstat32(a, b, c, d, e, f)              (char const *)a, (struct linux_stat32 *)b
#define __NR32AM_linux_fstat32(a, b, c, d, e, f)              (__fd_t)a, (struct linux_stat32 *)b
#define __NR32AM_olduname(a, b, c, d, e, f)                   (struct linux_olduname *)a
#define __NR32AM_iopl(a, b, c, d, e, f)                       (__syscall_ulong_t)a
#define __NR32AM_vhangup(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_wait4(a, b, c, d, e, f)                      (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct rusage *)d
#define __NR32AM_swapoff(a, b, c, d, e, f)                    (char const *)a
#define __NR32AM_sysinfo(a, b, c, d, e, f)                    (struct sysinfo *)a
#define __NR32AM_fsync(a, b, c, d, e, f)                      (__fd_t)a
#define __NR32AM_sigreturn(a, b, c, d, e, f)                  (struct fpustate const *)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (struct __sigset_struct const *)d, (struct rpc_syscall_info *)e, (struct ucpustate const *)f
#define __NR32AM_clone(a, b, c, d, e, f)                      (__syscall_ulong_t)a, (void *)b, (__pid_t *)c, (__uintptr_t)d, (__pid_t *)e
#define __NR32AM_setdomainname(a, b, c, d, e, f)              (char const *)a, (__size_t)b
#define __NR32AM_uname(a, b, c, d, e, f)                      (struct utsname *)a
#define __NR32AM_modify_ldt(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (void *)b, (__syscall_ulong_t)c
#define __NR32AM_mprotect(a, b, c, d, e, f)                   (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_sigprocmask(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c
#define __NR32AM_getpgid(a, b, c, d, e, f)                    (__pid_t)a
#define __NR32AM_fchdir(a, b, c, d, e, f)                     (__fd_t)a
#define __NR32AM_setfsuid(a, b, c, d, e, f)                   (__uint16_t)a
#define __NR32AM_setfsgid(a, b, c, d, e, f)                   (__uint16_t)a
#define __NR32AM__llseek(a, b, c, d, e, f)                    (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t *)d, (__syscall_ulong_t)e
#define __NR32AM_getdents(a, b, c, d, e, f)                   (__fd_t)a, (struct linux_dirent *)b, (__size_t)c
#define __NR32AM_flock(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_msync(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_readv(a, b, c, d, e, f)                      (__fd_t)a, (struct iovec const *)b, (__size_t)c
#define __NR32AM_writev(a, b, c, d, e, f)                     (__fd_t)a, (struct iovec const *)b, (__size_t)c
#define __NR32AM_getsid(a, b, c, d, e, f)                     (__pid_t)a
#define __NR32AM_fdatasync(a, b, c, d, e, f)                  (__fd_t)a
#define __NR32AM_mlock(a, b, c, d, e, f)                      (void const *)a, (__size_t)b
#define __NR32AM_munlock(a, b, c, d, e, f)                    (void const *)a, (__size_t)b
#define __NR32AM_mlockall(a, b, c, d, e, f)                   (__syscall_ulong_t)a
#define __NR32AM_munlockall(a, b, c, d, e, f)                 /* nothing */
#define __NR32AM_sched_setparam(a, b, c, d, e, f)             (__pid_t)a, (struct sched_param const *)b
#define __NR32AM_sched_getparam(a, b, c, d, e, f)             (__pid_t)a, (struct sched_param *)b
#define __NR32AM_sched_setscheduler(a, b, c, d, e, f)         (__pid_t)a, (__syscall_ulong_t)b, (struct sched_param const *)c
#define __NR32AM_sched_getscheduler(a, b, c, d, e, f)         (__pid_t)a
#define __NR32AM_sched_yield(a, b, c, d, e, f)                /* nothing */
#define __NR32AM_sched_get_priority_max(a, b, c, d, e, f)     (__syscall_ulong_t)a
#define __NR32AM_sched_get_priority_min(a, b, c, d, e, f)     (__syscall_ulong_t)a
#define __NR32AM_sched_rr_get_interval(a, b, c, d, e, f)      (__pid_t)a, (struct __timespec32 *)b
#define __NR32AM_nanosleep(a, b, c, d, e, f)                  (struct __timespec32 const *)a, (struct __timespec32 *)b
#define __NR32AM_mremap(a, b, c, d, e, f)                     (void *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d, (void *)e
#define __NR32AM_setresuid(a, b, c, d, e, f)                  (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getresuid(a, b, c, d, e, f)                  (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NR32AM_poll(a, b, c, d, e, f)                       (struct pollfd *)a, (__size_t)b, (__syscall_slong_t)c
#define __NR32AM_setresgid(a, b, c, d, e, f)                  (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getresgid(a, b, c, d, e, f)                  (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NR32AM_rt_sigaction(a, b, c, d, e, f)               (__syscall_ulong_t)a, (struct sigaction const *)b, (struct sigaction *)c, (__size_t)d
#define __NR32AM_rt_sigprocmask(a, b, c, d, e, f)             (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c, (__size_t)d
#define __NR32AM_rt_sigpending(a, b, c, d, e, f)              (struct __sigset_struct *)a, (__size_t)b
#define __NR32AM_rt_sigtimedwait(a, b, c, d, e, f)            (struct __sigset_struct const *)a, (struct __siginfo_struct *)b, (struct __timespec32 const *)c, (__size_t)d
#define __NR32AM_rt_sigqueueinfo(a, b, c, d, e, f)            (__pid_t)a, (__syscall_ulong_t)b, (struct __siginfo_struct const *)c
#define __NR32AM_rt_sigsuspend(a, b, c, d, e, f)              (struct __sigset_struct const *)a, (__size_t)b
#define __NR32AM_pread64(a, b, c, d, e, f)                    (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_pwrite64(a, b, c, d, e, f)                   (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_chown(a, b, c, d, e, f)                      (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getcwd(a, b, c, d, e, f)                     (char *)a, (__size_t)b
#define __NR32AM_sigaltstack(a, b, c, d, e, f)                (struct sigaltstack const *)a, (struct sigaltstack *)b
#define __NR32AM_sendfile(a, b, c, d, e, f)                   (__fd_t)a, (__fd_t)b, (__syscall_ulong_t *)c, (__size_t)d
#define __NR32AM_vfork(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_mmap2(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NR32AM_truncate64(a, b, c, d, e, f)                 (char const *)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NR32AM_ftruncate64(a, b, c, d, e, f)                (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NR32AM_linux_stat64(a, b, c, d, e, f)               (char const *)a, (struct linux_stat64 *)b
#define __NR32AM_linux_lstat64(a, b, c, d, e, f)              (char const *)a, (struct linux_stat64 *)b
#define __NR32AM_linux_fstat64(a, b, c, d, e, f)              (__fd_t)a, (struct linux_stat64 *)b
#define __NR32AM_lchown32(a, b, c, d, e, f)                   (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_getuid32(a, b, c, d, e, f)                   /* nothing */
#define __NR32AM_getgid32(a, b, c, d, e, f)                   /* nothing */
#define __NR32AM_geteuid32(a, b, c, d, e, f)                  /* nothing */
#define __NR32AM_getegid32(a, b, c, d, e, f)                  /* nothing */
#define __NR32AM_setreuid32(a, b, c, d, e, f)                 (__uint32_t)a, (__uint32_t)b
#define __NR32AM_setregid32(a, b, c, d, e, f)                 (__uint32_t)a, (__uint32_t)b
#define __NR32AM_getgroups32(a, b, c, d, e, f)                (__size_t)a, (/*[]*/__uint32_t *)b
#define __NR32AM_setgroups32(a, b, c, d, e, f)                (__size_t)a, (__uint32_t const *)b
#define __NR32AM_fchown32(a, b, c, d, e, f)                   (__fd_t)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_setresuid32(a, b, c, d, e, f)                (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_getresuid32(a, b, c, d, e, f)                (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NR32AM_setresgid32(a, b, c, d, e, f)                (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_getresgid32(a, b, c, d, e, f)                (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NR32AM_chown32(a, b, c, d, e, f)                    (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_setuid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NR32AM_setgid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NR32AM_setfsuid32(a, b, c, d, e, f)                 (__uint32_t)a
#define __NR32AM_setfsgid32(a, b, c, d, e, f)                 (__uint32_t)a
#define __NR32AM_mincore(a, b, c, d, e, f)                    (void *)a, (__size_t)b, (__uint8_t *)c
#define __NR32AM_madvise(a, b, c, d, e, f)                    (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_getdents64(a, b, c, d, e, f)                 (__fd_t)a, (struct linux_dirent64 *)b, (__size_t)c
#define __NR32AM_fcntl64(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NR32AM_gettid(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_readahead(a, b, c, d, e, f)                  (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__size_t)d
#define __NR32AM_setxattr(a, b, c, d, e, f)                   (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_lsetxattr(a, b, c, d, e, f)                  (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_fsetxattr(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_getxattr(a, b, c, d, e, f)                   (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NR32AM_lgetxattr(a, b, c, d, e, f)                  (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NR32AM_fgetxattr(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (void *)c, (__size_t)d
#define __NR32AM_listxattr(a, b, c, d, e, f)                  (char const *)a, (char *)b, (__size_t)c
#define __NR32AM_llistxattr(a, b, c, d, e, f)                 (char const *)a, (char *)b, (__size_t)c
#define __NR32AM_flistxattr(a, b, c, d, e, f)                 (__fd_t)a, (char *)b, (__size_t)c
#define __NR32AM_removexattr(a, b, c, d, e, f)                (char const *)a, (char const *)b
#define __NR32AM_lremovexattr(a, b, c, d, e, f)               (char const *)a, (char const *)b
#define __NR32AM_fremovexattr(a, b, c, d, e, f)               (int)a, (char const *)b
#define __NR32AM_tkill(a, b, c, d, e, f)                      (__pid_t)a, (__syscall_ulong_t)b
#define __NR32AM_sendfile64(a, b, c, d, e, f)                 (__fd_t)a, (__fd_t)b, (__uint64_t *)c, (__size_t)d
#define __NR32AM_futex(a, b, c, d, e, f)                      (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespec32 const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NR32AM_sched_setaffinity(a, b, c, d, e, f)          (__pid_t)a, (__size_t)b, (struct __cpu_set_struct const *)c
#define __NR32AM_sched_getaffinity(a, b, c, d, e, f)          (__pid_t)a, (__size_t)b, (struct __cpu_set_struct *)c
#define __NR32AM_exit_group(a, b, c, d, e, f)                 (__syscall_ulong_t)a
#define __NR32AM_epoll_create(a, b, c, d, e, f)               (__syscall_ulong_t)a
#define __NR32AM_epoll_ctl(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b, (__fd_t)c, (struct epoll_event *)d
#define __NR32AM_epoll_wait(a, b, c, d, e, f)                 (__fd_t)a, (struct epoll_event *)b, (__syscall_ulong_t)c, (__syscall_slong_t)d
#define __NR32AM_remap_file_pages(a, b, c, d, e, f)           (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_set_tid_address(a, b, c, d, e, f)            (__pid_t *)a
#define __NR32AM_timer_create(a, b, c, d, e, f)               (__clockid_t)a, (struct sigevent *)b, (__timer_t *)c
#define __NR32AM_timer_settime(a, b, c, d, e, f)              (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspec32 const *)c, (struct __itimerspec32 *)d
#define __NR32AM_timer_gettime(a, b, c, d, e, f)              (__timer_t)a, (struct __itimerspec32 *)b
#define __NR32AM_timer_getoverrun(a, b, c, d, e, f)           (__timer_t)a
#define __NR32AM_timer_delete(a, b, c, d, e, f)               (__timer_t)a
#define __NR32AM_clock_settime(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespec32 const *)b
#define __NR32AM_clock_gettime(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespec32 *)b
#define __NR32AM_clock_getres(a, b, c, d, e, f)               (__clockid_t)a, (struct __timespec32 *)b
#define __NR32AM_clock_nanosleep(a, b, c, d, e, f)            (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespec32 const *)c, (struct __timespec32 *)d
#define __NR32AM_statfs64(a, b, c, d, e, f)                   (char const *)a, (struct statfs64 *)b
#define __NR32AM_fstatfs64(a, b, c, d, e, f)                  (__fd_t)a, (struct statfs64 *)b
#define __NR32AM_tgkill(a, b, c, d, e, f)                     (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c
#define __NR32AM_utimes(a, b, c, d, e, f)                     (char const *)a, (/*[2]*/struct __timeval32 const *)b
#define __NR32AM_waitid(a, b, c, d, e, f)                     (__idtype_t)a, (__id_t)b, (struct __siginfo_struct *)c, (__syscall_ulong_t)d, (struct rusage *)e
#define __NR32AM_ioprio_set(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AM_ioprio_get(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AM_openat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__oflag_t)c, (__mode_t)d
#define __NR32AM_mkdirat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__mode_t)c
#define __NR32AM_mknodat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d
#define __NR32AM_fchownat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__uint32_t)c, (__uint32_t)d, (__atflag_t)e
#define __NR32AM_futimesat(a, b, c, d, e, f)                  (__fd_t)a, (const char *)b, (/*[2]*/struct __timeval32 const *)c
#define __NR32AM_linux_fstatat64(a, b, c, d, e, f)            (__fd_t)a, (char const *)b, (struct linux_stat64 *)c, (__atflag_t)d
#define __NR32AM_unlinkat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NR32AM_renameat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d
#define __NR32AM_linkat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NR32AM_symlinkat(a, b, c, d, e, f)                  (char const *)a, (__fd_t)b, (char const *)c
#define __NR32AM_readlinkat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (char *)c, (__size_t)d
#define __NR32AM_fchmodat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NR32AM_faccessat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__syscall_ulong_t)c, (__atflag_t)d
#define __NR32AM_pselect6(a, b, c, d, e, f)                   (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespec32 const *)e, (void const *)f
#define __NR32AM_ppoll(a, b, c, d, e, f)                      (struct pollfd *)a, (__size_t)b, (struct __timespec32 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NR32AM_unshare(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NR32AM_splice(a, b, c, d, e, f)                     (__fd_t)a, (__uint64_t *)b, (__fd_t)c, (__uint64_t *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR32AM_sync_file_range(a, b, c, d, e, f)            (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__syscall_ulong_t)f
#define __NR32AM_tee(a, b, c, d, e, f)                        (__fd_t)a, (__fd_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_vmsplice(a, b, c, d, e, f)                   (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_getcpu(a, b, c, d, e, f)                     (__uint32_t *)a, (__uint32_t *)b, (struct getcpu_cache *)c
#define __NR32AM_epoll_pwait(a, b, c, d, e, f)                (__fd_t)a, (struct epoll_event *)b, (__syscall_ulong_t)c, (__syscall_slong_t)d, (struct __sigset_struct const *)e
#define __NR32AM_utimensat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (/*[2-3]*/struct __timespec32 const *)c, (__atflag_t)d
#define __NR32AM_signalfd(a, b, c, d, e, f)                   (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c
#define __NR32AM_timerfd_create(a, b, c, d, e, f)             (__clockid_t)a, (__syscall_ulong_t)b
#define __NR32AM_eventfd(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NR32AM_fallocate(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b, (__uint32_t)c, (__uint32_t)d
#define __NR32AM_timerfd_settime(a, b, c, d, e, f)            (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspec32 const *)c, (struct __itimerspec32 *)d
#define __NR32AM_timerfd_gettime(a, b, c, d, e, f)            (__fd_t)a, (struct __itimerspec32 *)b
#define __NR32AM_signalfd4(a, b, c, d, e, f)                  (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_eventfd2(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AM_epoll_create1(a, b, c, d, e, f)              (__syscall_ulong_t)a
#define __NR32AM_dup3(a, b, c, d, e, f)                       (__fd_t)a, (__fd_t)b, (__oflag_t)c
#define __NR32AM_pipe2(a, b, c, d, e, f)                      (/*[2]*/__fd_t *)a, (__oflag_t)b
#define __NR32AM_preadv(a, b, c, d, e, f)                     (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_pwritev(a, b, c, d, e, f)                    (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_rt_tgsigqueueinfo(a, b, c, d, e, f)          (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (struct __siginfo_struct const *)d
#define __NR32AM_recvmmsg(a, b, c, d, e, f)                   (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespec32 *)e
#define __NR32AM_prlimit64(a, b, c, d, e, f)                  (__pid_t)a, (__syscall_ulong_t)b, (struct rlimit64 const *)c, (struct rlimit64 *)d
#define __NR32AM_name_to_handle_at(a, b, c, d, e, f)          (__fd_t)a, (char const *)b, (struct file_handle *)c, (__int32_t *)d, (__syscall_ulong_t)e
#define __NR32AM_open_by_handle_at(a, b, c, d, e, f)          (__fd_t)a, (struct file_handle *)b, (__syscall_ulong_t)c
#define __NR32AM_syncfs(a, b, c, d, e, f)                     (__fd_t)a
#define __NR32AM_sendmmsg(a, b, c, d, e, f)                   (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_setns(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_process_vm_readv(a, b, c, d, e, f)           (__pid_t)a, (struct iovec const *)b, (__size_t)c, (struct iovec const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR32AM_process_vm_writev(a, b, c, d, e, f)          (__pid_t)a, (struct iovec const *)b, (__size_t)c, (struct iovec const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR32AM_kcmp(a, b, c, d, e, f)                       (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AM_renameat2(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__syscall_ulong_t)e
#define __NR32AM_execveat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (char const *const *)c, (char const *const *)d, (__atflag_t)e
#define __NR32AM_socket(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AM_socketpair(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (/*[2]*/__fd_t *)d
#define __NR32AM_bind(a, b, c, d, e, f)                       (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NR32AM_connect(a, b, c, d, e, f)                    (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NR32AM_listen(a, b, c, d, e, f)                     (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_accept4(a, b, c, d, e, f)                    (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c, (__syscall_ulong_t)d
#define __NR32AM_getsockopt(a, b, c, d, e, f)                 (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void *)d, (__socklen_t *)e
#define __NR32AM_setsockopt(a, b, c, d, e, f)                 (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void const *)d, (__socklen_t)e
#define __NR32AM_getsockname(a, b, c, d, e, f)                (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NR32AM_getpeername(a, b, c, d, e, f)                (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NR32AM_sendto(a, b, c, d, e, f)                     (__fd_t)a, (void const *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr const *)e, (__socklen_t)f
#define __NR32AM_sendmsg(a, b, c, d, e, f)                    (__fd_t)a, (struct msghdr const *)b, (__syscall_ulong_t)c
#define __NR32AM_recvfrom(a, b, c, d, e, f)                   (__fd_t)a, (void *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr *)e, (__socklen_t *)f
#define __NR32AM_recvmsg(a, b, c, d, e, f)                    (__fd_t)a, (struct msghdr *)b, (__syscall_ulong_t)c
#define __NR32AM_shutdown(a, b, c, d, e, f)                   (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_hop(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NR32AM_hopf(a, b, c, d, e, f)                       (__fd_t)a, (__syscall_ulong_t)b, (__iomode_t)c, (void *)d
#define __NR32AM_readf(a, b, c, d, e, f)                      (__fd_t)a, (void *)b, (__size_t)c, (__iomode_t)d
#define __NR32AM_writef(a, b, c, d, e, f)                     (__fd_t)a, (void const *)b, (__size_t)c, (__iomode_t)d
#define __NR32AM_detach(a, b, c, d, e, f)                     (__pid_t)a
#define __NR32AM_getdrives(a, b, c, d, e, f)                  /* nothing */
#define __NR32AM_frealpath4(a, b, c, d, e, f)                 (__fd_t)a, (char *)b, (__size_t)c, (__atflag_t)d
#define __NR32AM_frealpathat(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NR32AM_rpc_schedule(a, b, c, d, e, f)               (__pid_t)a, (__syscall_ulong_t)b, (__uint8_t const *)c, (void **)d
#define __NR32AM_sysctl(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (void *)b
#define __NR32AM_openpty(a, b, c, d, e, f)                    (__fd_t *)a, (__fd_t *)b, (char *)c, (struct termios const *)d, (struct winsize const *)e
#define __NR32AM_fchdirat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NR32AM_time64(a, b, c, d, e, f)                     (__time64_t *)a
#define __NR32AM_set_exception_handler(a, b, c, d, e, f)      (__syscall_ulong_t)a, (__except_handler_t)b, (void *)c
#define __NR32AM_get_exception_handler(a, b, c, d, e, f)      (__syscall_ulong_t *)a, (__except_handler_t *)b, (void **)c
#define __NR32AM_set_library_listdef(a, b, c, d, e, f)        (struct library_listdef const *)a
#define __NR32AM_debugtrap(a, b, c, d, e, f)                  (struct ucpustate const *)a, (struct debugtrap_reason const *)b
#define __NR32AM_lfutex(a, b, c, d, e, f)                     (__uintptr_t *)a, (__syscall_ulong_t)b, (__uintptr_t)c, (struct __timespec64 const *)d, (__uintptr_t)e
#define __NR32AM_lseek64(a, b, c, d, e, f)                    (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__syscall_ulong_t)d
#define __NR32AM_lfutexlock(a, b, c, d, e, f)                 (__uintptr_t *)a, (__uintptr_t *)b, (__syscall_ulong_t)c, (__uintptr_t)d, (struct __timespec64 const *)e, (__uintptr_t)f
#define __NR32AM_lfutexexpr(a, b, c, d, e, f)                 (__uintptr_t *)a, (void *)b, (struct lfutexexpr const *)c, (__size_t)d, (struct __timespec64 const *)e, (__syscall_ulong_t)f
#define __NR32AM_lfutexlockexpr(a, b, c, d, e, f)             (__uintptr_t *)a, (void *)b, (struct lfutexexpr const *)c, (__size_t)d, (struct __timespec64 const *)e, (__syscall_ulong_t)f
#define __NR32AM_mktty(a, b, c, d, e, f)                      (__fd_t)a, (__fd_t)b, (char const *)c, (__syscall_ulong_t)d
#define __NR32AM_raiseat(a, b, c, d, e, f)                    (struct ucpustate const *)a, (struct __siginfo_struct const *)b
#define __NR32AM_stime64(a, b, c, d, e, f)                    (__time64_t const *)a
#define __NR32AM_coredump(a, b, c, d, e, f)                   (struct ucpustate const *)a, (struct ucpustate const *)b, (void const *const *)c, (__size_t)d, (struct exception_data const *)e, (__syscall_ulong_t)f
#define __NR32AM_utime64(a, b, c, d, e, f)                    (char const *)a, (struct utimbuf64 const *)b
#define __NR32AM_ioctlf(a, b, c, d, e, f)                     (__fd_t)a, (__syscall_ulong_t)b, (__iomode_t)c, (void *)d
#define __NR32AM_fsmode(a, b, c, d, e, f)                     (__uint64_t)((__uint64_t)a | (__uint64_t)b << 32)
#define __NR32AM_gettimeofday64(a, b, c, d, e, f)             (struct __timeval64 *)a, (struct timezone *)b
#define __NR32AM_settimeofday64(a, b, c, d, e, f)             (struct __timeval64 const *)a, (struct timezone const *)b
#define __NR32AM_select64(a, b, c, d, e, f)                   (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timeval64 *)e
#define __NR32AM_maplibrary(a, b, c, d, e, f)                 (void *)a, (__syscall_ulong_t)b, (__fd_t)c, (void *)d, (__size_t)e
#define __NR32AM_setitimer64(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __itimerval64 const *)b, (struct __itimerval64 *)c
#define __NR32AM_getitimer64(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __itimerval64 *)b
#define __NR32AM_kreaddir(a, b, c, d, e, f)                   (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_readvf(a, b, c, d, e, f)                     (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__iomode_t)d
#define __NR32AM_writevf(a, b, c, d, e, f)                    (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__iomode_t)d
#define __NR32AM_rpc_service(a, b, c, d, e, f)                /* nothing */
#define __NR32AM_sched_rr_get_interval64(a, b, c, d, e, f)    (__pid_t)a, (struct __timespec64 *)b
#define __NR32AM_nanosleep64(a, b, c, d, e, f)                (struct __timespec64 const *)a, (struct __timespec64 *)b
#define __NR32AM_rt_sigtimedwait64(a, b, c, d, e, f)          (struct __sigset_struct const *)a, (struct __siginfo_struct *)b, (struct __timespec64 const *)c, (__size_t)d
#define __NR32AM_pread64f(a, b, c, d, e, f)                   (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_pwrite64f(a, b, c, d, e, f)                  (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_kstat(a, b, c, d, e, f)                      (char const *)a, (struct stat *)b
#define __NR32AM_klstat(a, b, c, d, e, f)                     (char const *)a, (struct stat *)b
#define __NR32AM_kfstat(a, b, c, d, e, f)                     (__fd_t)a, (struct stat *)b
#define __NR32AM_kreaddirf(a, b, c, d, e, f)                  (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d, (__iomode_t)e
#define __NR32AM_timer_settime64(a, b, c, d, e, f)            (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspec64 const *)c, (struct __itimerspec64 *)d
#define __NR32AM_timer_gettime64(a, b, c, d, e, f)            (__timer_t)a, (struct __itimerspec64 *)b
#define __NR32AM_clock_settime64(a, b, c, d, e, f)            (__clockid_t)a, (struct __timespec64 const *)b
#define __NR32AM_clock_gettime64(a, b, c, d, e, f)            (__clockid_t)a, (struct __timespec64 *)b
#define __NR32AM_clock_getres64(a, b, c, d, e, f)             (__clockid_t)a, (struct __timespec64 *)b
#define __NR32AM_clock_nanosleep64(a, b, c, d, e, f)          (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespec64 const *)c, (struct __timespec64 *)d
#define __NR32AM_utimes64(a, b, c, d, e, f)                   (char const *)a, (/*[2]*/struct __timeval64 const *)b
#define __NR32AM_fmkdirat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NR32AM_fmknodat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d, (__atflag_t)e
#define __NR32AM_futimesat64(a, b, c, d, e, f)                (__fd_t)a, (const char *)b, (/*[2-3]*/struct __timeval64 const *)c
#define __NR32AM_kfstatat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (struct stat *)c, (__atflag_t)d
#define __NR32AM_frenameat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NR32AM_fsymlinkat(a, b, c, d, e, f)                 (char const *)a, (__fd_t)b, (char const *)c, (__atflag_t)d
#define __NR32AM_freadlinkat(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NR32AM_pselect6_64(a, b, c, d, e, f)                (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespec64 const *)e, (void const *)f
#define __NR32AM_ppoll64(a, b, c, d, e, f)                    (struct pollfd *)a, (__size_t)b, (struct __timespec64 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NR32AM_utimensat64(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (/*[2-3]*/struct __timespec64 const *)c, (__atflag_t)d
#define __NR32AM_fallocate64(a, b, c, d, e, f)                (__fd_t)a, (__syscall_ulong_t)b, (__uint64_t)((__uint64_t)c | (__uint64_t)d << 32), (__uint64_t)((__uint64_t)e | (__uint64_t)f << 32)
#define __NR32AM_timerfd_settime64(a, b, c, d, e, f)          (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspec64 const *)c, (struct __itimerspec64 *)d
#define __NR32AM_timerfd_gettime64(a, b, c, d, e, f)          (__fd_t)a, (struct __itimerspec64 *)b
#define __NR32AM_preadvf(a, b, c, d, e, f)                    (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_pwritevf(a, b, c, d, e, f)                   (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_recvmmsg64(a, b, c, d, e, f)                 (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespec64 *)e
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_MAKER */

#ifdef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#define __NR32AP_exit(a)                                      (__syscall_ulong_t)a
#define __NR32AP_fork()                                         /* nothing */
#define __NR32AP_read(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_write(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_open(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_close(a)                                     (__syscall_ulong_t)a
#define __NR32AP_waitpid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_creat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_link(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_unlink(a)                                    (__syscall_ulong_t)a
#define __NR32AP_execve(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_chdir(a)                                     (__syscall_ulong_t)a
#define __NR32AP_time(a)                                      (__syscall_ulong_t)a
#define __NR32AP_mknod(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_chmod(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lchown(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_linux_oldstat(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lseek(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getpid()                                       /* nothing */
#define __NR32AP_mount(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_umount(a)                                    (__syscall_ulong_t)a
#define __NR32AP_setuid(a)                                    (__syscall_ulong_t)a
#define __NR32AP_getuid()                                       /* nothing */
#define __NR32AP_stime(a)                                     (__syscall_ulong_t)a
#define __NR32AP_ptrace(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_alarm(a)                                     (__syscall_ulong_t)a
#define __NR32AP_linux_oldfstat(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_pause()                                        /* nothing */
#define __NR32AP_utime(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_access(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_nice(a)                                      (__syscall_ulong_t)a
#define __NR32AP_ftime(a)                                     (__syscall_ulong_t)a
#define __NR32AP_sync()                                         /* nothing */
#define __NR32AP_kill(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rename(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mkdir(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rmdir(a)                                     (__syscall_ulong_t)a
#define __NR32AP_dup(a)                                       (__syscall_ulong_t)a
#define __NR32AP_pipe(a)                                      (__syscall_ulong_t)a
#define __NR32AP_times(a)                                     (__syscall_ulong_t)a
#define __NR32AP_brk(a)                                       (__syscall_ulong_t)a
#define __NR32AP_setgid(a)                                    (__syscall_ulong_t)a
#define __NR32AP_getgid()                                       /* nothing */
#define __NR32AP_signal(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_geteuid()                                      /* nothing */
#define __NR32AP_getegid()                                      /* nothing */
#define __NR32AP_acct(a)                                      (__syscall_ulong_t)a
#define __NR32AP_umount2(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_ioctl(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_fcntl(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setpgid(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_oldolduname(a)                               (__syscall_ulong_t)a
#define __NR32AP_umask(a)                                     (__syscall_ulong_t)a
#define __NR32AP_chroot(a)                                    (__syscall_ulong_t)a
#define __NR32AP_ustat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_dup2(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getppid()                                      /* nothing */
#define __NR32AP_getpgrp()                                      /* nothing */
#define __NR32AP_setsid()                                       /* nothing */
#define __NR32AP_sigaction(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sgetmask()                                     /* nothing */
#define __NR32AP_ssetmask(a)                                  (__syscall_ulong_t)a
#define __NR32AP_setreuid(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setregid(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sigsuspend(a)                                (__syscall_ulong_t)a
#define __NR32AP_sigpending(a)                                (__syscall_ulong_t)a
#define __NR32AP_sethostname(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setrlimit(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getrlimit(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getrusage(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_gettimeofday(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_settimeofday(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getgroups(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setgroups(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_select(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_symlink(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_linux_oldlstat(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_readlink(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_swapon(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_reboot(a)                                    (__syscall_ulong_t)a
#define __NR32AP_readdir(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_mmap(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_munmap(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_truncate(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_ftruncate(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fchmod(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fchown(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getpriority(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setpriority(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_profil(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_statfs(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fstatfs(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_ioperm(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_socketcall(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_syslog(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setitimer(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getitimer(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_linux_stat32(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_linux_lstat32(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_linux_fstat32(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_olduname(a)                                  (__syscall_ulong_t)a
#define __NR32AP_iopl(a)                                      (__syscall_ulong_t)a
#define __NR32AP_vhangup()                                      /* nothing */
#define __NR32AP_wait4(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_swapoff(a)                                   (__syscall_ulong_t)a
#define __NR32AP_sysinfo(a)                                   (__syscall_ulong_t)a
#define __NR32AP_fsync(a)                                     (__syscall_ulong_t)a
#define __NR32AP_sigreturn(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_clone(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_setdomainname(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_uname(a)                                     (__syscall_ulong_t)a
#define __NR32AP_modify_ldt(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_mprotect(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sigprocmask(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getpgid(a)                                   (__syscall_ulong_t)a
#define __NR32AP_fchdir(a)                                    (__syscall_ulong_t)a
#define __NR32AP_setfsuid(a)                                  (__syscall_ulong_t)a
#define __NR32AP_setfsgid(a)                                  (__syscall_ulong_t)a
#define __NR32AP__llseek(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getdents(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_flock(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_msync(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_readv(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_writev(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getsid(a)                                    (__syscall_ulong_t)a
#define __NR32AP_fdatasync(a)                                 (__syscall_ulong_t)a
#define __NR32AP_mlock(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_munlock(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mlockall(a)                                  (__syscall_ulong_t)a
#define __NR32AP_munlockall()                                   /* nothing */
#define __NR32AP_sched_setparam(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sched_getparam(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sched_setscheduler(a, b, c)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sched_getscheduler(a)                        (__syscall_ulong_t)a
#define __NR32AP_sched_yield()                                  /* nothing */
#define __NR32AP_sched_get_priority_max(a)                    (__syscall_ulong_t)a
#define __NR32AP_sched_get_priority_min(a)                    (__syscall_ulong_t)a
#define __NR32AP_sched_rr_get_interval(a, b)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_nanosleep(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mremap(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_setresuid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresuid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_poll(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setresgid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresgid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_rt_sigaction(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rt_sigprocmask(a, b, c, d)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rt_sigpending(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rt_sigtimedwait(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rt_sigqueueinfo(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_rt_sigsuspend(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_pread64(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_pwrite64(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_chown(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getcwd(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sigaltstack(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sendfile(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_vfork()                                        /* nothing */
#define __NR32AP_mmap2(a, b, c, d, e, f)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_truncate64(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NR32AP_ftruncate64(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NR32AP_linux_stat64(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_linux_lstat64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_linux_fstat64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lchown32(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getuid32()                                     /* nothing */
#define __NR32AP_getgid32()                                     /* nothing */
#define __NR32AP_geteuid32()                                    /* nothing */
#define __NR32AP_getegid32()                                    /* nothing */
#define __NR32AP_setreuid32(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setregid32(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getgroups32(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setgroups32(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fchown32(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setresuid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresuid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setresgid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresgid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_chown32(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setuid32(a)                                  (__syscall_ulong_t)a
#define __NR32AP_setgid32(a)                                  (__syscall_ulong_t)a
#define __NR32AP_setfsuid32(a)                                (__syscall_ulong_t)a
#define __NR32AP_setfsgid32(a)                                (__syscall_ulong_t)a
#define __NR32AP_mincore(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_madvise(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getdents64(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_fcntl64(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_gettid()                                       /* nothing */
#define __NR32AP_readahead(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NR32AP_setxattr(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_lsetxattr(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_fsetxattr(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_getxattr(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_lgetxattr(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fgetxattr(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_listxattr(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_llistxattr(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_flistxattr(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_removexattr(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lremovexattr(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fremovexattr(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_tkill(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sendfile64(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_futex(a, b, c, d, e, f)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_sched_setaffinity(a, b, c)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sched_getaffinity(a, b, c)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_exit_group(a)                                (__syscall_ulong_t)a
#define __NR32AP_epoll_create(a)                              (__syscall_ulong_t)a
#define __NR32AP_epoll_ctl(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_epoll_wait(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_remap_file_pages(a, b, c, d, e)              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_set_tid_address(a)                           (__syscall_ulong_t)a
#define __NR32AP_timer_create(a, b, c)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_timer_settime(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timer_gettime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_timer_getoverrun(a)                          (__syscall_ulong_t)a
#define __NR32AP_timer_delete(a)                              (__syscall_ulong_t)a
#define __NR32AP_clock_settime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_gettime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_getres(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_nanosleep(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_statfs64(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fstatfs64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_tgkill(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_utimes(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_waitid(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_ioprio_set(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_ioprio_get(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_openat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_mkdirat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_mknodat(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fchownat(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_futimesat(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_linux_fstatat64(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_unlinkat(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_renameat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_linkat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_symlinkat(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_readlinkat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fchmodat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_faccessat(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_pselect6(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_ppoll(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_unshare(a)                                   (__syscall_ulong_t)a
#define __NR32AP_splice(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_sync_file_range(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d
#define __NR32AP_tee(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_vmsplice(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getcpu(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_epoll_pwait(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_utimensat(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_signalfd(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_timerfd_create(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_eventfd(a)                                   (__syscall_ulong_t)a
#define __NR32AP_fallocate(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timerfd_settime(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timerfd_gettime(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_signalfd4(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_eventfd2(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_epoll_create1(a)                             (__syscall_ulong_t)a
#define __NR32AP_dup3(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_pipe2(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_preadv(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_pwritev(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_rt_tgsigqueueinfo(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_recvmmsg(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_prlimit64(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_name_to_handle_at(a, b, c, d, e)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_open_by_handle_at(a, b, c)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_syncfs(a)                                    (__syscall_ulong_t)a
#define __NR32AP_sendmmsg(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_setns(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_process_vm_readv(a, b, c, d, e, f)           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_process_vm_writev(a, b, c, d, e, f)          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_kcmp(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_renameat2(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_execveat(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_socket(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_socketpair(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_bind(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_connect(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_listen(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_accept4(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getsockopt(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_setsockopt(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_getsockname(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getpeername(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sendto(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_sendmsg(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_recvfrom(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_recvmsg(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_shutdown(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_hop(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_hopf(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_readf(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_writef(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_detach(a)                                    (__syscall_ulong_t)a
#define __NR32AP_getdrives()                                    /* nothing */
#define __NR32AP_frealpath4(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_frealpathat(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_rpc_schedule(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_sysctl(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_openpty(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_fchdirat(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_time64(a)                                    (__syscall_ulong_t)a
#define __NR32AP_set_exception_handler(a, b, c)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_get_exception_handler(a, b, c)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_set_library_listdef(a)                       (__syscall_ulong_t)a
#define __NR32AP_debugtrap(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lfutex(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_lseek64(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NR32AP_lfutexlock(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_lfutexexpr(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_lfutexlockexpr(a, b, c, d, e, f)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_mktty(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_raiseat(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_stime64(a)                                   (__syscall_ulong_t)a
#define __NR32AP_coredump(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_utime64(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_ioctlf(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fsmode(a)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)((__uint64_t)a >> 32)
#define __NR32AP_gettimeofday64(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_settimeofday64(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_select64(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_maplibrary(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_setitimer64(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getitimer64(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_kreaddir(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_readvf(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_writevf(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rpc_service()                                  /* nothing */
#define __NR32AP_sched_rr_get_interval64(a, b)                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_nanosleep64(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rt_sigtimedwait64(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_pread64f(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_pwrite64f(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_kstat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_klstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_kfstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_kreaddirf(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_timer_settime64(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timer_gettime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_settime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_gettime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_getres64(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_nanosleep64(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_utimes64(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fmkdirat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fmknodat(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_futimesat64(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_kfstatat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_frenameat(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_fsymlinkat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_freadlinkat(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_pselect6_64(a, b, c, d, e, f)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_ppoll64(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_utimensat64(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fallocate64(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_timerfd_settime64(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timerfd_gettime64(a, b)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_preadvf(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_pwritevf(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_recvmmsg64(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_PACKER */

#ifdef __WANT_SYSCALL_ATTR_NORETURN
#define __NR32NT_exit                       1
#define __NR32NT_exit_group                 1
#endif /* __WANT_SYSCALL_ATTR_NORETURN */

#ifdef __WANT_SYSCALL_DOUBLE_WIDE_RETURN_386
#define __NR32DW386_time64                     1
#define __NR32DW386_lseek64                    1
#define __NR32DW386_fsmode                     1
#endif /* __WANT_SYSCALL_DOUBLE_WIDE_RETURN_386 */

#ifdef __WANT_SYSCALL_ARGUMENT_COUNT_386
#define __NR32AC386_exit                       1
#define __NR32AC386_fork                       0
#define __NR32AC386_read                       3
#define __NR32AC386_write                      3
#define __NR32AC386_open                       3
#define __NR32AC386_close                      1
#define __NR32AC386_waitpid                    3
#define __NR32AC386_creat                      2
#define __NR32AC386_link                       2
#define __NR32AC386_unlink                     1
#define __NR32AC386_execve                     3
#define __NR32AC386_chdir                      1
#define __NR32AC386_time                       1
#define __NR32AC386_mknod                      3
#define __NR32AC386_chmod                      2
#define __NR32AC386_lchown                     3
#define __NR32AC386_linux_oldstat              2
#define __NR32AC386_lseek                      3
#define __NR32AC386_getpid                     0
#define __NR32AC386_mount                      5
#define __NR32AC386_umount                     1
#define __NR32AC386_setuid                     1
#define __NR32AC386_getuid                     0
#define __NR32AC386_stime                      1
#define __NR32AC386_ptrace                     4
#define __NR32AC386_alarm                      1
#define __NR32AC386_linux_oldfstat             2
#define __NR32AC386_pause                      0
#define __NR32AC386_utime                      2
#define __NR32AC386_access                     2
#define __NR32AC386_nice                       1
#define __NR32AC386_ftime                      1
#define __NR32AC386_sync                       0
#define __NR32AC386_kill                       2
#define __NR32AC386_rename                     2
#define __NR32AC386_mkdir                      2
#define __NR32AC386_rmdir                      1
#define __NR32AC386_dup                        1
#define __NR32AC386_pipe                       1
#define __NR32AC386_times                      1
#define __NR32AC386_brk                        1
#define __NR32AC386_setgid                     1
#define __NR32AC386_getgid                     0
#define __NR32AC386_signal                     2
#define __NR32AC386_geteuid                    0
#define __NR32AC386_getegid                    0
#define __NR32AC386_acct                       1
#define __NR32AC386_umount2                    2
#define __NR32AC386_ioctl                      3
#define __NR32AC386_fcntl                      3
#define __NR32AC386_setpgid                    2
#define __NR32AC386_oldolduname                1
#define __NR32AC386_umask                      1
#define __NR32AC386_chroot                     1
#define __NR32AC386_ustat                      2
#define __NR32AC386_dup2                       2
#define __NR32AC386_getppid                    0
#define __NR32AC386_getpgrp                    0
#define __NR32AC386_setsid                     0
#define __NR32AC386_sigaction                  3
#define __NR32AC386_sgetmask                   0
#define __NR32AC386_ssetmask                   1
#define __NR32AC386_setreuid                   2
#define __NR32AC386_setregid                   2
#define __NR32AC386_sigsuspend                 1
#define __NR32AC386_sigpending                 1
#define __NR32AC386_sethostname                2
#define __NR32AC386_setrlimit                  2
#define __NR32AC386_getrlimit                  2
#define __NR32AC386_getrusage                  2
#define __NR32AC386_gettimeofday               2
#define __NR32AC386_settimeofday               2
#define __NR32AC386_getgroups                  2
#define __NR32AC386_setgroups                  2
#define __NR32AC386_select                     5
#define __NR32AC386_symlink                    2
#define __NR32AC386_linux_oldlstat             2
#define __NR32AC386_readlink                   3
#define __NR32AC386_swapon                     2
#define __NR32AC386_reboot                     1
#define __NR32AC386_readdir                    3
#define __NR32AC386_mmap                       6
#define __NR32AC386_munmap                     2
#define __NR32AC386_truncate                   2
#define __NR32AC386_ftruncate                  2
#define __NR32AC386_fchmod                     2
#define __NR32AC386_fchown                     3
#define __NR32AC386_getpriority                2
#define __NR32AC386_setpriority                3
#define __NR32AC386_profil                     4
#define __NR32AC386_statfs                     2
#define __NR32AC386_fstatfs                    2
#define __NR32AC386_ioperm                     3
#define __NR32AC386_socketcall                 2
#define __NR32AC386_syslog                     3
#define __NR32AC386_setitimer                  3
#define __NR32AC386_getitimer                  2
#define __NR32AC386_linux_stat32               2
#define __NR32AC386_linux_lstat32              2
#define __NR32AC386_linux_fstat32              2
#define __NR32AC386_olduname                   1
#define __NR32AC386_iopl                       1
#define __NR32AC386_vhangup                    0
#define __NR32AC386_wait4                      4
#define __NR32AC386_swapoff                    1
#define __NR32AC386_sysinfo                    1
#define __NR32AC386_fsync                      1
#define __NR32AC386_sigreturn                  6
#define __NR32AC386_clone                      5
#define __NR32AC386_setdomainname              2
#define __NR32AC386_uname                      1
#define __NR32AC386_modify_ldt                 3
#define __NR32AC386_mprotect                   3
#define __NR32AC386_sigprocmask                3
#define __NR32AC386_getpgid                    1
#define __NR32AC386_fchdir                     1
#define __NR32AC386_setfsuid                   1
#define __NR32AC386_setfsgid                   1
#define __NR32AC386__llseek                    5
#define __NR32AC386_getdents                   3
#define __NR32AC386_flock                      2
#define __NR32AC386_msync                      3
#define __NR32AC386_readv                      3
#define __NR32AC386_writev                     3
#define __NR32AC386_getsid                     1
#define __NR32AC386_fdatasync                  1
#define __NR32AC386_mlock                      2
#define __NR32AC386_munlock                    2
#define __NR32AC386_mlockall                   1
#define __NR32AC386_munlockall                 0
#define __NR32AC386_sched_setparam             2
#define __NR32AC386_sched_getparam             2
#define __NR32AC386_sched_setscheduler         3
#define __NR32AC386_sched_getscheduler         1
#define __NR32AC386_sched_yield                0
#define __NR32AC386_sched_get_priority_max     1
#define __NR32AC386_sched_get_priority_min     1
#define __NR32AC386_sched_rr_get_interval      2
#define __NR32AC386_nanosleep                  2
#define __NR32AC386_mremap                     5
#define __NR32AC386_setresuid                  3
#define __NR32AC386_getresuid                  3
#define __NR32AC386_poll                       3
#define __NR32AC386_setresgid                  3
#define __NR32AC386_getresgid                  3
#define __NR32AC386_rt_sigaction               4
#define __NR32AC386_rt_sigprocmask             4
#define __NR32AC386_rt_sigpending              2
#define __NR32AC386_rt_sigtimedwait            4
#define __NR32AC386_rt_sigqueueinfo            3
#define __NR32AC386_rt_sigsuspend              2
#define __NR32AC386_pread64                    5
#define __NR32AC386_pwrite64                   5
#define __NR32AC386_chown                      3
#define __NR32AC386_getcwd                     2
#define __NR32AC386_sigaltstack                2
#define __NR32AC386_sendfile                   4
#define __NR32AC386_vfork                      0
#define __NR32AC386_mmap2                      6
#define __NR32AC386_truncate64                 3
#define __NR32AC386_ftruncate64                3
#define __NR32AC386_linux_stat64               2
#define __NR32AC386_linux_lstat64              2
#define __NR32AC386_linux_fstat64              2
#define __NR32AC386_lchown32                   3
#define __NR32AC386_getuid32                   0
#define __NR32AC386_getgid32                   0
#define __NR32AC386_geteuid32                  0
#define __NR32AC386_getegid32                  0
#define __NR32AC386_setreuid32                 2
#define __NR32AC386_setregid32                 2
#define __NR32AC386_getgroups32                2
#define __NR32AC386_setgroups32                2
#define __NR32AC386_fchown32                   3
#define __NR32AC386_setresuid32                3
#define __NR32AC386_getresuid32                3
#define __NR32AC386_setresgid32                3
#define __NR32AC386_getresgid32                3
#define __NR32AC386_chown32                    3
#define __NR32AC386_setuid32                   1
#define __NR32AC386_setgid32                   1
#define __NR32AC386_setfsuid32                 1
#define __NR32AC386_setfsgid32                 1
#define __NR32AC386_mincore                    3
#define __NR32AC386_madvise                    3
#define __NR32AC386_getdents64                 3
#define __NR32AC386_fcntl64                    3
#define __NR32AC386_gettid                     0
#define __NR32AC386_readahead                  4
#define __NR32AC386_setxattr                   5
#define __NR32AC386_lsetxattr                  5
#define __NR32AC386_fsetxattr                  5
#define __NR32AC386_getxattr                   4
#define __NR32AC386_lgetxattr                  4
#define __NR32AC386_fgetxattr                  4
#define __NR32AC386_listxattr                  3
#define __NR32AC386_llistxattr                 3
#define __NR32AC386_flistxattr                 3
#define __NR32AC386_removexattr                2
#define __NR32AC386_lremovexattr               2
#define __NR32AC386_fremovexattr               2
#define __NR32AC386_tkill                      2
#define __NR32AC386_sendfile64                 4
#define __NR32AC386_futex                      6
#define __NR32AC386_sched_setaffinity          3
#define __NR32AC386_sched_getaffinity          3
#define __NR32AC386_exit_group                 1
#define __NR32AC386_epoll_create               1
#define __NR32AC386_epoll_ctl                  4
#define __NR32AC386_epoll_wait                 4
#define __NR32AC386_remap_file_pages           5
#define __NR32AC386_set_tid_address            1
#define __NR32AC386_timer_create               3
#define __NR32AC386_timer_settime              4
#define __NR32AC386_timer_gettime              2
#define __NR32AC386_timer_getoverrun           1
#define __NR32AC386_timer_delete               1
#define __NR32AC386_clock_settime              2
#define __NR32AC386_clock_gettime              2
#define __NR32AC386_clock_getres               2
#define __NR32AC386_clock_nanosleep            4
#define __NR32AC386_statfs64                   2
#define __NR32AC386_fstatfs64                  2
#define __NR32AC386_tgkill                     3
#define __NR32AC386_utimes                     2
#define __NR32AC386_waitid                     5
#define __NR32AC386_ioprio_set                 3
#define __NR32AC386_ioprio_get                 2
#define __NR32AC386_openat                     4
#define __NR32AC386_mkdirat                    3
#define __NR32AC386_mknodat                    4
#define __NR32AC386_fchownat                   5
#define __NR32AC386_futimesat                  3
#define __NR32AC386_linux_fstatat64            4
#define __NR32AC386_unlinkat                   3
#define __NR32AC386_renameat                   4
#define __NR32AC386_linkat                     5
#define __NR32AC386_symlinkat                  3
#define __NR32AC386_readlinkat                 4
#define __NR32AC386_fchmodat                   4
#define __NR32AC386_faccessat                  4
#define __NR32AC386_pselect6                   6
#define __NR32AC386_ppoll                      5
#define __NR32AC386_unshare                    1
#define __NR32AC386_splice                     6
#define __NR32AC386_sync_file_range            6
#define __NR32AC386_tee                        4
#define __NR32AC386_vmsplice                   4
#define __NR32AC386_getcpu                     3
#define __NR32AC386_epoll_pwait                5
#define __NR32AC386_utimensat                  4
#define __NR32AC386_signalfd                   3
#define __NR32AC386_timerfd_create             2
#define __NR32AC386_eventfd                    1
#define __NR32AC386_fallocate                  4
#define __NR32AC386_timerfd_settime            4
#define __NR32AC386_timerfd_gettime            2
#define __NR32AC386_signalfd4                  4
#define __NR32AC386_eventfd2                   2
#define __NR32AC386_epoll_create1              1
#define __NR32AC386_dup3                       3
#define __NR32AC386_pipe2                      2
#define __NR32AC386_preadv                     5
#define __NR32AC386_pwritev                    5
#define __NR32AC386_rt_tgsigqueueinfo          4
#define __NR32AC386_recvmmsg                   5
#define __NR32AC386_prlimit64                  4
#define __NR32AC386_name_to_handle_at          5
#define __NR32AC386_open_by_handle_at          3
#define __NR32AC386_syncfs                     1
#define __NR32AC386_sendmmsg                   4
#define __NR32AC386_setns                      2
#define __NR32AC386_process_vm_readv           6
#define __NR32AC386_process_vm_writev          6
#define __NR32AC386_kcmp                       5
#define __NR32AC386_renameat2                  5
#define __NR32AC386_execveat                   5
#define __NR32AC386_socket                     3
#define __NR32AC386_socketpair                 4
#define __NR32AC386_bind                       3
#define __NR32AC386_connect                    3
#define __NR32AC386_listen                     2
#define __NR32AC386_accept4                    4
#define __NR32AC386_getsockopt                 5
#define __NR32AC386_setsockopt                 5
#define __NR32AC386_getsockname                3
#define __NR32AC386_getpeername                3
#define __NR32AC386_sendto                     6
#define __NR32AC386_sendmsg                    3
#define __NR32AC386_recvfrom                   6
#define __NR32AC386_recvmsg                    3
#define __NR32AC386_shutdown                   2
#define __NR32AC386_hop                        3
#define __NR32AC386_hopf                       4
#define __NR32AC386_readf                      4
#define __NR32AC386_writef                     4
#define __NR32AC386_detach                     1
#define __NR32AC386_getdrives                  0
#define __NR32AC386_frealpath4                 4
#define __NR32AC386_frealpathat                5
#define __NR32AC386_rpc_schedule               4
#define __NR32AC386_sysctl                     2
#define __NR32AC386_openpty                    5
#define __NR32AC386_fchdirat                   3
#define __NR32AC386_time64                     1
#define __NR32AC386_set_exception_handler      3
#define __NR32AC386_get_exception_handler      3
#define __NR32AC386_set_library_listdef        1
#define __NR32AC386_debugtrap                  2
#define __NR32AC386_lfutex                     5
#define __NR32AC386_lseek64                    4
#define __NR32AC386_lfutexlock                 6
#define __NR32AC386_lfutexexpr                 6
#define __NR32AC386_lfutexlockexpr             6
#define __NR32AC386_mktty                      4
#define __NR32AC386_raiseat                    2
#define __NR32AC386_stime64                    1
#define __NR32AC386_coredump                   6
#define __NR32AC386_utime64                    2
#define __NR32AC386_ioctlf                     4
#define __NR32AC386_fsmode                     2
#define __NR32AC386_gettimeofday64             2
#define __NR32AC386_settimeofday64             2
#define __NR32AC386_select64                   5
#define __NR32AC386_maplibrary                 5
#define __NR32AC386_setitimer64                3
#define __NR32AC386_getitimer64                2
#define __NR32AC386_kreaddir                   4
#define __NR32AC386_readvf                     4
#define __NR32AC386_writevf                    4
#define __NR32AC386_rpc_service                0
#define __NR32AC386_sched_rr_get_interval64    2
#define __NR32AC386_nanosleep64                2
#define __NR32AC386_rt_sigtimedwait64          4
#define __NR32AC386_pread64f                   6
#define __NR32AC386_pwrite64f                  6
#define __NR32AC386_kstat                      2
#define __NR32AC386_klstat                     2
#define __NR32AC386_kfstat                     2
#define __NR32AC386_kreaddirf                  5
#define __NR32AC386_timer_settime64            4
#define __NR32AC386_timer_gettime64            2
#define __NR32AC386_clock_settime64            2
#define __NR32AC386_clock_gettime64            2
#define __NR32AC386_clock_getres64             2
#define __NR32AC386_clock_nanosleep64          4
#define __NR32AC386_utimes64                   2
#define __NR32AC386_fmkdirat                   4
#define __NR32AC386_fmknodat                   5
#define __NR32AC386_futimesat64                3
#define __NR32AC386_kfstatat                   4
#define __NR32AC386_frenameat                  5
#define __NR32AC386_fsymlinkat                 4
#define __NR32AC386_freadlinkat                5
#define __NR32AC386_pselect6_64                6
#define __NR32AC386_ppoll64                    5
#define __NR32AC386_utimensat64                4
#define __NR32AC386_fallocate64                6
#define __NR32AC386_timerfd_settime64          4
#define __NR32AC386_timerfd_gettime64          2
#define __NR32AC386_preadvf                    6
#define __NR32AC386_pwritevf                   6
#define __NR32AC386_recvmmsg64                 5
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT_386 */

