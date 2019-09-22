/* HASH CRC-32:0x74c38d65 */
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

#define __NR_exit                       1          /* void exit(syscall_ulong_t status) */
#define __NR_fork                       2          /* pid_t fork(void) */
#define __NR_read                       3          /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
#define __NR_write                      4          /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
#define __NR_open                       5          /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `FD' */
#define __NR_close                      6          /* errno_t close(fd_t fd) */
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR_waitpid                    7          /* pid_t waitpid(pid_t pid, int32_t *stat_loc, syscall_ulong_t options) */
#define __NR_creat                      8          /* fd_t creat(char const *filename, mode_t mode) */
#define __NR_link                       9          /* errno_t link(char const *existing_file, char const *link_file) */
#define __NR_unlink                     10         /* errno_t unlink(char const *filename) */
#define __NR_execve                     11         /* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
#define __NR_chdir                      12         /* errno_t chdir(char const *path) */
#define __NR_time                       13         /* time32_t time(time32_t *timer) */
#define __NR_mknod                      14         /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define __NR_chmod                      15         /* errno_t chmod(char const *filename, mode_t mode) */
#define __NR_lchown                     16         /* errno_t lchown(char const *filename, uint16_t owner, uint16_t group) */
#define __NR_linux_oldstat              18         /* errno_t linux_oldstat(char const *filename, struct linux_oldstat *statbuf) */
#define __NR_lseek                      19         /* int32_t lseek(fd_t fd, int32_t offset, syscall_ulong_t whence) */
#define __NR_getpid                     20         /* pid_t getpid(void) */
#define __NR_mount                      21         /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
#define __NR_umount                     22         /* errno_t umount(char const *special_file) */
#define __NR_setuid                     23         /* errno_t setuid(uint16_t uid) */
#define __NR_getuid                     24         /* uint16_t getuid(void) */
#define __NR_stime                      25         /* errno_t stime(time32_t const *t) */
#define __NR_ptrace                     26         /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
#define __NR_alarm                      27         /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
#define __NR_linux_oldfstat             28         /* errno_t linux_oldfstat(fd_t fd, struct linux_oldstat *statbuf) */
#define __NR_pause                      29         /* errno_t pause(void) */
#define __NR_utime                      30         /* errno_t utime(char const *filename, struct __utimbuf32 const *times) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define __NR_access                     33         /* errno_t access(char const *filename, syscall_ulong_t type) */
#define __NR_nice                       34         /* errno_t nice(syscall_slong_t inc) */
#define __NR_ftime                      35         /* errno_t ftime(struct timeb *tp) */
#define __NR_sync                       36         /* errno_t sync(void) */
/* @param: signo: One of `SIG*' */
#define __NR_kill                       37         /* errno_t kill(pid_t pid, syscall_ulong_t signo) */
#define __NR_rename                     38         /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define __NR_mkdir                      39         /* errno_t mkdir(char const *pathname, mode_t mode) */
#define __NR_rmdir                      40         /* errno_t rmdir(char const *path) */
#define __NR_dup                        41         /* fd_t dup(fd_t fd) */
#define __NR_pipe                       42         /* errno_t pipe([2]fd_t *pipedes) */
#define __NR_times                      43         /* clock_t times(struct tms *buf) */
#define __NR_brk                        45         /* errno_t brk(void *addr) */
#define __NR_setgid                     46         /* errno_t setgid(uint16_t gid) */
#define __NR_getgid                     47         /* uint16_t getgid(void) */
/* @param: signo: One of `SIG*' */
#define __NR_signal                     48         /* sighandler_t signal(syscall_ulong_t signo, sighandler_t handler) */
#define __NR_geteuid                    49         /* uint16_t geteuid(void) */
#define __NR_getegid                    50         /* uint16_t getegid(void) */
#define __NR_acct                       51         /* errno_t acct(char const *filename) */
#define __NR_umount2                    52         /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
#define __NR_ioctl                      54         /* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
#define __NR_fcntl                      55         /* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
#define __NR_setpgid                    57         /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define __NR_oldolduname                59         /* errno_t oldolduname(struct linux_oldolduname *name) */
#define __NR_umask                      60         /* mode_t umask(mode_t mode) */
#define __NR_chroot                     61         /* errno_t chroot(char const *path) */
#define __NR_ustat                      62         /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
#define __NR_dup2                       63         /* fd_t dup2(fd_t oldfd, fd_t newfd) */
#define __NR_getppid                    64         /* pid_t getppid(void) */
#define __NR_getpgrp                    65         /* pid_t getpgrp(void) */
#define __NR_setsid                     66         /* pid_t setsid(void) */
/* @param: signo: One of `SIG*' */
#define __NR_sigaction                  67         /* errno_t sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact) */
#define __NR_sgetmask                   68         /* syscall_ulong_t sgetmask(void) */
#define __NR_ssetmask                   69         /* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
#define __NR_setreuid                   70         /* errno_t setreuid(uint16_t ruid, uint16_t euid) */
#define __NR_setregid                   71         /* errno_t setregid(uint16_t rgid, uint16_t egid) */
#define __NR_sigsuspend                 72         /* errno_t sigsuspend(struct __sigset_struct const *set) */
#define __NR_sigpending                 73         /* errno_t sigpending(struct __sigset_struct *set) */
#define __NR_sethostname                74         /* errno_t sethostname(char const *name, size_t len) */
#define __NR_setrlimit                  75         /* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
#define __NR_getrlimit                  76         /* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
#define __NR_getrusage                  77         /* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
#define __NR_gettimeofday               78         /* errno_t gettimeofday(struct __timeval32 *tv, struct timezone *tz) */
#define __NR_settimeofday               79         /* errno_t settimeofday(struct __timeval32 const *tv, struct timezone const *tz) */
#define __NR_getgroups                  80         /* errno_t getgroups(size_t size, []uint16_t *list) */
#define __NR_setgroups                  81         /* errno_t setgroups(size_t count, uint16_t const *groups) */
#define __NR_select                     82         /* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval32 *timeout) */
#define __NR_symlink                    83         /* errno_t symlink(char const *link_text, char const *target_path) */
#define __NR_linux_oldlstat             84         /* errno_t linux_oldlstat(char const *filename, struct linux_oldstat *statbuf) */
#define __NR_readlink                   85         /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define __NR_swapon                     87         /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
#define __NR_reboot                     88         /* errno_t reboot(syscall_ulong_t how) */
/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
#define __NR_readdir                    89         /* errno_t readdir(fd_t fd, struct old_linux_dirent *dirp, size_t count) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
#define __NR_mmap                       90         /* void * mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
#define __NR_munmap                     91         /* errno_t munmap(void *addr, size_t len) */
#define __NR_truncate                   92         /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define __NR_ftruncate                  93         /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
#define __NR_fchmod                     94         /* errno_t fchmod(fd_t fd, mode_t mode) */
#define __NR_fchown                     95         /* errno_t fchown(fd_t fd, uint16_t owner, uint16_t group) */
#define __NR_getpriority                96         /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
#define __NR_setpriority                97         /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
#define __NR_profil                     98         /* errno_t profil(uint16_t *sample_buffer, size_t size, size_t offset, syscall_ulong_t scale) */
#define __NR_statfs                     99         /* errno_t statfs(char const *file, struct __statfs32 *buf) */
#define __NR_fstatfs                    100        /* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
#define __NR_ioperm                     101        /* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
#define __NR_socketcall                 102        /* errno_t socketcall(int call, unsigned long *args) */
#define __NR_syslog                     103        /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
#define __NR_setitimer                  104        /* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
#define __NR_getitimer                  105        /* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
#define __NR_linux_stat32               106        /* errno_t linux_stat32(char const *filename, struct linux_stat32 *statbuf) */
#define __NR_linux_lstat32              107        /* errno_t linux_lstat32(char const *filename, struct linux_stat32 *statbuf) */
#define __NR_linux_fstat32              108        /* errno_t linux_fstat32(fd_t fd, struct linux_stat32 *statbuf) */
#define __NR_olduname                   109        /* errno_t olduname(struct linux_olduname *name) */
#define __NR_iopl                       110        /* errno_t iopl(syscall_ulong_t level) */
#define __NR_vhangup                    111        /* errno_t vhangup(void) */
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR_wait4                      114        /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
#define __NR_swapoff                    115        /* errno_t swapoff(char const *pathname) */
#define __NR_sysinfo                    116        /* errno_t sysinfo(struct sysinfo *info) */
#define __NR_fsync                      118        /* errno_t fsync(fd_t fd) */
/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
#define __NR_sigreturn                  119        /* void sigreturn(struct fpustate const *restore_fpu, syscall_ulong_t unused1, syscall_ulong_t unused2, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
#define __NR_clone                      120        /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
#define __NR_setdomainname              121        /* errno_t setdomainname(char const *name, size_t len) */
#define __NR_uname                      122        /* errno_t uname(struct utsname *name) */
#define __NR_modify_ldt                 123        /* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
#define __NR_mprotect                   125        /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR_sigprocmask                126        /* errno_t sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset) */
#define __NR_getpgid                    132        /* pid_t getpgid(pid_t pid) */
#define __NR_fchdir                     133        /* errno_t fchdir(fd_t fd) */
#define __NR_setfsuid                   138        /* errno_t setfsuid(uint16_t uid) */
#define __NR_setfsgid                   139        /* errno_t setfsgid(uint16_t gid) */
#define __NR__llseek                    140        /* errno_t _llseek(fd_t fd, int64_t offset, uint64_t *result, syscall_ulong_t whence) */
#define __NR_getdents                   141        /* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
#define __NR_flock                      143        /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
#define __NR_msync                      144        /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
#define __NR_readv                      145        /* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
#define __NR_writev                     146        /* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
#define __NR_getsid                     147        /* pid_t getsid(pid_t pid) */
#define __NR_fdatasync                  148        /* errno_t fdatasync(fd_t fd) */
#define __NR_mlock                      150        /* errno_t mlock(void const *addr, size_t len) */
#define __NR_munlock                    151        /* errno_t munlock(void const *addr, size_t len) */
#define __NR_mlockall                   152        /* errno_t mlockall(syscall_ulong_t flags) */
#define __NR_munlockall                 153        /* errno_t munlockall(void) */
#define __NR_sched_setparam             154        /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
#define __NR_sched_getparam             155        /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
#define __NR_sched_setscheduler         156        /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define __NR_sched_getscheduler         157        /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define __NR_sched_yield                158        /* errno_t sched_yield(void) */
#define __NR_sched_get_priority_max     159        /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define __NR_sched_get_priority_min     160        /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define __NR_sched_rr_get_interval      161        /* errno_t sched_rr_get_interval(pid_t pid, struct __timespec32 *tms) */
#define __NR_nanosleep                  162        /* errno_t nanosleep(struct __timespec32 const *req, struct __timespec32 *rem) */
/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
#define __NR_mremap                     163        /* void * mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define __NR_setresuid                  164        /* errno_t setresuid(uint16_t ruid, uint16_t euid, uint16_t suid) */
#define __NR_getresuid                  165        /* errno_t getresuid(uint16_t *ruid, uint16_t *euid, uint16_t *suid) */
#define __NR_poll                       168        /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
#define __NR_setresgid                  170        /* errno_t setresgid(uint16_t rgid, uint16_t egid, uint16_t sgid) */
#define __NR_getresgid                  171        /* errno_t getresgid(uint16_t *rgid, uint16_t *egid, uint16_t *sgid) */
/* @param: signo: One of `SIG*' */
#define __NR_rt_sigaction               174        /* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction const *act, struct sigaction *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR_rt_sigprocmask             175        /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
#define __NR_rt_sigpending              176        /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define __NR_rt_sigtimedwait            177        /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec32 const *timeout, size_t sigsetsize) */
/* @param: signo: One of `SIG*' */
#define __NR_rt_sigqueueinfo            178        /* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
#define __NR_rt_sigsuspend              179        /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define __NR_pread64                    180        /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define __NR_pwrite64                   181        /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
#define __NR_chown                      182        /* errno_t chown(char const *filename, uint16_t owner, uint16_t group) */
#define __NR_getcwd                     183        /* ssize_t getcwd(char *buf, size_t size) */
#define __NR_sigaltstack                186        /* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
#define __NR_sendfile                   187        /* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
#define __NR_vfork                      190        /* pid_t vfork(void) */
#define __NR_mmap2                      192        /* void * mmap2(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t pgoffset) */
#define __NR_truncate64                 193        /* errno_t truncate64(char const *filename, uint64_t length) */
#define __NR_ftruncate64                194        /* errno_t ftruncate64(fd_t fd, uint64_t length) */
#define __NR_linux_stat64               195        /* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
#define __NR_linux_lstat64              196        /* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
#define __NR_linux_fstat64              197        /* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
#define __NR_lchown32                   198        /* errno_t lchown32(char const *filename, uint32_t owner, uint32_t group) */
#define __NR_getuid32                   199        /* uint32_t getuid32(void) */
#define __NR_getgid32                   200        /* uint32_t getgid32(void) */
#define __NR_geteuid32                  201        /* uint32_t geteuid32(void) */
#define __NR_getegid32                  202        /* uint32_t getegid32(void) */
#define __NR_setreuid32                 203        /* errno_t setreuid32(uint32_t ruid, uint32_t euid) */
#define __NR_setregid32                 204        /* errno_t setregid32(uint32_t rgid, uint32_t egid) */
#define __NR_getgroups32                205        /* errno_t getgroups32(size_t size, []uint32_t *list) */
#define __NR_setgroups32                206        /* errno_t setgroups32(size_t count, uint32_t const *groups) */
#define __NR_fchown32                   207        /* errno_t fchown32(fd_t fd, uint32_t owner, uint32_t group) */
#define __NR_setresuid32                208        /* errno_t setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) */
#define __NR_getresuid32                209        /* errno_t getresuid32(uint32_t *ruid, uint32_t *euid, uint32_t *suid) */
#define __NR_setresgid32                210        /* errno_t setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) */
#define __NR_getresgid32                211        /* errno_t getresgid32(uint32_t *rgid, uint32_t *egid, uint32_t *sgid) */
#define __NR_chown32                    212        /* errno_t chown32(char const *filename, uint32_t owner, uint32_t group) */
#define __NR_setuid32                   213        /* errno_t setuid32(uint32_t uid) */
#define __NR_setgid32                   214        /* errno_t setgid32(uint32_t gid) */
#define __NR_setfsuid32                 215        /* errno_t setfsuid32(uint32_t uid) */
#define __NR_setfsgid32                 216        /* errno_t setfsgid32(uint32_t gid) */
#define __NR_mincore                    218        /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define __NR_madvise                    219        /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
#define __NR_getdents64                 220        /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
#define __NR_fcntl64                    221        /* syscall_slong_t fcntl64(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR_gettid                     224        /* pid_t gettid(void) */
#define __NR_readahead                  225        /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
#define __NR_setxattr                   226        /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR_lsetxattr                  227        /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR_fsetxattr                  228        /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR_getxattr                   229        /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR_lgetxattr                  230        /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR_fgetxattr                  231        /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define __NR_listxattr                  232        /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR_llistxattr                 233        /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR_flistxattr                 234        /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define __NR_removexattr                235        /* errno_t removexattr(char const *path, char const *name) */
#define __NR_lremovexattr               236        /* errno_t lremovexattr(char const *path, char const *name) */
#define __NR_fremovexattr               237        /* errno_t fremovexattr(int fd, char const *name) */
/* @param: signo: One of `SIG*' */
#define __NR_tkill                      238        /* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
#define __NR_sendfile64                 239        /* ssize_t sendfile64(fd_t out_fd, fd_t in_fd, uint64_t *offset, size_t count) */
#define __NR_futex                      240        /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespec32 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define __NR_sched_setaffinity          241        /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define __NR_sched_getaffinity          242        /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define __NR_exit_group                 252        /* void exit_group(syscall_ulong_t exit_code) */
#define __NR_epoll_create               254        /* fd_t epoll_create(syscall_ulong_t size) */
#define __NR_epoll_ctl                  255        /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
#define __NR_epoll_wait                 256        /* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
#define __NR_remap_file_pages           257        /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
#define __NR_set_tid_address            258        /* pid_t set_tid_address(pid_t *tidptr) */
#define __NR_timer_create               259        /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
#define __NR_timer_settime              260        /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspec32 const *value, struct __itimerspec32 *ovalue) */
#define __NR_timer_gettime              261        /* errno_t timer_gettime(timer_t timerid, struct __itimerspec32 *value) */
#define __NR_timer_getoverrun           262        /* syscall_slong_t timer_getoverrun(timer_t timerid) */
#define __NR_timer_delete               263        /* errno_t timer_delete(timer_t timerid) */
#define __NR_clock_settime              264        /* errno_t clock_settime(clockid_t clock_id, struct __timespec32 const *tp) */
#define __NR_clock_gettime              265        /* errno_t clock_gettime(clockid_t clock_id, struct __timespec32 *tp) */
#define __NR_clock_getres               266        /* errno_t clock_getres(clockid_t clock_id, struct __timespec32 *res) */
#define __NR_clock_nanosleep            267        /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespec32 const *requested_time, struct __timespec32 *remaining) */
#define __NR_statfs64                   268        /* errno_t statfs64(char const *file, struct statfs64 *buf) */
#define __NR_fstatfs64                  269        /* errno_t fstatfs64(fd_t file, struct statfs64 *buf) */
/* @param: signo: One of `SIG*' */
#define __NR_tgkill                     270        /* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
#define __NR_utimes                     271        /* errno_t utimes(char const *filename, [2]struct __timeval32 const *times) */
/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
#define __NR_waitid                     284        /* errno_t waitid(idtype_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
#define __NR_ioprio_set                 289        /* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
#define __NR_ioprio_get                 290        /* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
#define __NR_openat                     295        /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
#define __NR_mkdirat                    296        /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
#define __NR_mknodat                    297        /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR_fchownat                   298        /* errno_t fchownat(fd_t dirfd, char const *filename, uint32_t owner, uint32_t group, atflag_t flags) */
#define __NR_futimesat                  299        /* errno_t futimesat(fd_t dirfd, const char *filename, [2]struct __timeval32 const *times) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR_linux_fstatat64            300        /* errno_t linux_fstatat64(fd_t dirfd, char const *filename, struct linux_stat64 *statbuf, atflag_t flags) */
/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
#define __NR_unlinkat                   301        /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define __NR_renameat                   302        /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
#define __NR_linkat                     303        /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define __NR_symlinkat                  304        /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
#define __NR_readlinkat                 305        /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR_fchmodat                   306        /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
#define __NR_faccessat                  307        /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
#define __NR_pselect6                   308        /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec32 const *timeout, void const *sigmask_sigset_and_len) */
#define __NR_ppoll                      309        /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespec32 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* param flags: Set of `CLONE_*' */
#define __NR_unshare                    310        /* errno_t unshare(syscall_ulong_t flags) */
#define __NR_splice                     313        /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
#define __NR_sync_file_range            314        /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
#define __NR_tee                        315        /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
#define __NR_vmsplice                   316        /* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
#define __NR_getcpu                     318        /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
#define __NR_epoll_pwait                319        /* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#define __NR_utimensat                  320        /* errno_t utimensat(fd_t dirfd, char const *filename, [2-3]struct __timespec32 const *times, atflag_t flags) */
/* Return file descriptor for new interval timer source */
#define __NR_timerfd_create             322        /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
#define __NR_eventfd                    323        /* errno_t eventfd(syscall_ulong_t initval) */
#define __NR_fallocate                  324        /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, uint32_t offset, uint32_t length) */
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
#define __NR_timerfd_settime            325        /* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspec32 const *utmr, struct __itimerspec32 *otmr) */
/* Return the next expiration time of UFD */
#define __NR_timerfd_gettime            326        /* errno_t timerfd_gettime(fd_t ufd, struct __itimerspec32 *otmr) */
#define __NR_eventfd2                   328        /* errno_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
#define __NR_epoll_create1              329        /* fd_t epoll_create1(syscall_ulong_t flags) */
/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
#define __NR_dup3                       330        /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
#define __NR_pipe2                      331        /* errno_t pipe2([2]fd_t *pipedes, oflag_t flags) */
#define __NR_preadv                     333        /* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
#define __NR_pwritev                    334        /* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
/* @param: signo: One of `SIG*' */
#define __NR_rt_tgsigqueueinfo          335        /* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo_struct const *uinfo) */
#define __NR_recvmmsg                   337        /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec32 *tmo) */
/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
#define __NR_prlimit64                  340        /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
#define __NR_name_to_handle_at          341        /* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
#define __NR_open_by_handle_at          342        /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
#define __NR_syncfs                     344        /* errno_t syncfs(fd_t fd) */
#define __NR_sendmmsg                   345        /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
#define __NR_setns                      346        /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
#define __NR_process_vm_readv           347        /* ssize_t process_vm_readv(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
#define __NR_process_vm_writev          348        /* ssize_t process_vm_writev(pid_t pid, struct iovec const *lvec, size_t liovcnt, struct iovec const *rvec, size_t riovcnt, syscall_ulong_t flags) */
#define __NR_kcmp                       349        /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
#define __NR_renameat2                  353        /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR_execveat                   358        /* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
#define __NR_socket                     359        /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
#define __NR_socketpair                 360        /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, [2]fd_t *fds) */
#define __NR_bind                       361        /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR_connect                    362        /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR_listen                     363        /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
#define __NR_accept4                    364        /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define __NR_getsockopt                 365        /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define __NR_setsockopt                 366        /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
#define __NR_getsockname                367        /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
#define __NR_getpeername                368        /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
#define __NR_sendto                     369        /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR_sendmsg                    370        /* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
#define __NR_recvfrom                   371        /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
#define __NR_recvmsg                    372        /* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
#define __NR_shutdown                   373        /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
#define __NR_hop                        0x80000001 /* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR_hopf                       0x80000002 /* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define __NR_readf                      0x80000003 /* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
#define __NR_writef                     0x80000004 /* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
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
#define __NR_detach                     0x80000005 /* errno_t detach(pid_t pid) */
/* Returns a bitset of all of the currently mounted dos-drives */
#define __NR_getdrives                  0x80000006 /* syscall_slong_t getdrives(void) */
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define __NR_frealpath4                 0x80000007 /* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define __NR_frealpathat                0x80000008 /* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
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
#define __NR_rpc_schedule               0x80000009 /* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, void **arguments) */
#define __NR_sysctl                     0x8000000a /* syscall_slong_t sysctl(syscall_ulong_t command, void *arg) */
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
#define __NR_openpty                    0x8000000b /* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR_fchdirat                   0x8000000c /* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
#define __NR_time64                     0x8000000d /* time64_t time64(time64_t *timer) */
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
#define __NR_set_exception_handler      0x8000000e /* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
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
#define __NR_get_exception_handler      0x8000000f /* errno_t get_exception_handler(syscall_ulong_t *pmode, except_handler_t *phandler, void **phandler_sp) */
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
#define __NR_set_library_listdef        0x80000010 /* errno_t set_library_listdef(struct library_listdef const *listdef) */
/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: trapno:   One of `SIG*' (e.g. `SIGTRAP')
 * @param: regs:     When non-NULL, additional trap register data
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
#define __NR_debugtrap                  0x80000011 /* errno_t debugtrap(struct ucpustate const *state, syscall_ulong_t trapno, struct debug_trap_register const *regs) */
#define __NR_lfutex                     0x80000012 /* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
#define __NR_lseek64                    0x80000013 /* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
#define __NR_lfutexlock                 0x80000014 /* syscall_slong_t lfutexlock(uintptr_t *ulockaddr, uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct __timespec64 const *timeout, uintptr_t val2) */
#define __NR_lfutexexpr                 0x80000015 /* errno_t lfutexexpr(uintptr_t *uaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
#define __NR_lfutexlockexpr             0x80000016 /* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct __timespec64 const *timeout, syscall_ulong_t timeout_flags) */
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
#define __NR_mktty                      0x80000017 /* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
#define __NR_raiseat                    0x80000018 /* errno_t raiseat(struct ucpustate const *state, struct __siginfo_struct const *si) */
#define __NR_stime64                    0x80000019 /* errno_t stime64(time64_t const *t) */
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
#define __NR_coredump                   0x8000001a /* errno_t coredump(struct ucpustate const *curr_state, struct ucpustate const *orig_state, void const *const *traceback_vector, size_t traceback_length, struct exception_data const *exception, syscall_ulong_t unwind_error) */
#define __NR_utime64                    0x8000001e /* errno_t utime64(char const *filename, struct utimbuf64 const *times) */
#define __NR_ioctlf                     0x80000036 /* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define __NR_fsmode                     0x8000003c /* uint64_t fsmode(uint64_t mode) */
#define __NR_gettimeofday64             0x8000004e /* errno_t gettimeofday64(struct __timeval64 *tv, struct timezone *tz) */
#define __NR_settimeofday64             0x8000004f /* errno_t settimeofday64(struct __timeval64 const *tv, struct timezone const *tz) */
#define __NR_select64                   0x80000052 /* ssize_t select64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timeval64 *timeout) */
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
#define __NR_maplibrary                 0x80000056 /* void * maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, void *hdrv, size_t hdrc) */
#define __NR_setitimer64                0x80000068 /* errno_t setitimer64(syscall_ulong_t which, struct __itimerval64 const *newval, struct __itimerval64 *oldval) */
#define __NR_getitimer64                0x80000069 /* errno_t getitimer64(syscall_ulong_t which, struct __itimerval64 *curr_value) */
#define __NR_kreaddir                   0x8000008d /* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
#define __NR_readvf                     0x80000091 /* ssize_t readvf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
#define __NR_writevf                    0x80000092 /* ssize_t writevf(fd_t fd, struct iovec const *iovec, size_t count, iomode_t mode) */
#define __NR_rpc_service                0x8000009e /* syscall_slong_t rpc_service(void) */
#define __NR_sched_rr_get_interval64    0x800000a1 /* errno_t sched_rr_get_interval64(pid_t pid, struct __timespec64 *tms) */
#define __NR_nanosleep64                0x800000a2 /* errno_t nanosleep64(struct __timespec64 const *req, struct __timespec64 *rem) */
#define __NR_rt_sigtimedwait64          0x800000b1 /* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set, struct __siginfo_struct *info, struct __timespec64 const *timeout, size_t sigsetsize) */
#define __NR_pread64f                   0x800000b4 /* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR_pwrite64f                  0x800000b5 /* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR_kstat                      0x800000c3 /* errno_t kstat(char const *filename, struct stat *statbuf) */
#define __NR_klstat                     0x800000c4 /* errno_t klstat(char const *filename, struct stat *statbuf) */
#define __NR_kfstat                     0x800000c5 /* errno_t kfstat(fd_t fd, struct stat *statbuf) */
#define __NR_kreaddirf                  0x800000dc /* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
#define __NR_timer_settime64            0x80000104 /* errno_t timer_settime64(timer_t timerid, syscall_ulong_t flags, struct __itimerspec64 const *value, struct __itimerspec64 *ovalue) */
#define __NR_timer_gettime64            0x80000105 /* errno_t timer_gettime64(timer_t timerid, struct __itimerspec64 *value) */
#define __NR_clock_settime64            0x80000108 /* errno_t clock_settime64(clockid_t clock_id, struct __timespec64 const *tp) */
#define __NR_clock_gettime64            0x80000109 /* errno_t clock_gettime64(clockid_t clock_id, struct __timespec64 *tp) */
#define __NR_clock_getres64             0x8000010a /* errno_t clock_getres64(clockid_t clock_id, struct __timespec64 *res) */
#define __NR_clock_nanosleep64          0x8000010b /* errno_t clock_nanosleep64(clockid_t clock_id, syscall_ulong_t flags, struct __timespec64 const *requested_time, struct __timespec64 *remaining) */
#define __NR_utimes64                   0x8000010f /* errno_t utimes64(char const *filename, [2]struct __timeval64 const *times) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR_fmkdirat                   0x80000128 /* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR_fmknodat                   0x80000129 /* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#define __NR_futimesat64                0x8000012b /* errno_t futimesat64(fd_t dirfd, const char *filename, [2-3]struct __timeval64 const *times) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
#define __NR_kfstatat                   0x8000012c /* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR_frenameat                  0x8000012e /* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
/* @param: flags: Set of `0|AT_DOSPATH' */
#define __NR_fsymlinkat                 0x80000130 /* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
#define __NR_freadlinkat                0x80000131 /* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
#define __NR_pselect6_64                0x80000134 /* ssize_t pselect6_64(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespec64 const *timeout, void const *sigmask_sigset_and_len) */
#define __NR_ppoll64                    0x80000135 /* ssize_t ppoll64(struct pollfd *fds, size_t nfds, struct __timespec64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
#define __NR_utimensat64                0x80000140 /* errno_t utimensat64(fd_t dirfd, char const *filename, [2-3]struct __timespec64 const *times, atflag_t flags) */
#define __NR_fallocate64                0x80000144 /* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
#define __NR_timerfd_settime64          0x80000145 /* errno_t timerfd_settime64(fd_t ufd, syscall_ulong_t flags, struct __itimerspec64 const *utmr, struct __itimerspec64 *otmr) */
/* Return the next expiration time of UFD */
#define __NR_timerfd_gettime64          0x80000146 /* errno_t timerfd_gettime64(fd_t ufd, struct __itimerspec64 *otmr) */
#define __NR_preadvf                    0x8000014d /* ssize_t preadvf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
#define __NR_pwritevf                   0x8000014e /* ssize_t pwritevf(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset, iomode_t mode) */
#define __NR_recvmmsg64                 0x80000151 /* ssize_t recvmmsg64(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespec64 *tmo) */

#define __NR_syscall_min   1
#define __NR_syscall_max   373
#define __NR_exsyscall_min 0x80000001
#define __NR_exsyscall_max 0x80000151

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
#define __NRRM_exit                       2
#define __NRRM_fork                       2
#define __NRRM_read                       0
#define __NRRM_write                      0
#define __NRRM_open                       0
#define __NRRM_close                      2
#define __NRRM_waitpid                    1
#define __NRRM_creat                      0
#define __NRRM_link                       0
#define __NRRM_unlink                     0
#define __NRRM_execve                     0
#define __NRRM_chdir                      0
#define __NRRM_time                       0
#define __NRRM_mknod                      0
#define __NRRM_chmod                      0
#define __NRRM_lchown                     0
#define __NRRM_linux_oldstat              0
#define __NRRM_lseek                      0
#define __NRRM_getpid                     2
#define __NRRM_mount                      0
#define __NRRM_umount                     0
#define __NRRM_setuid                     2
#define __NRRM_getuid                     2
#define __NRRM_stime                      0
#define __NRRM_ptrace                     0
#define __NRRM_alarm                      0
#define __NRRM_linux_oldfstat             0
#define __NRRM_pause                      1
#define __NRRM_utime                      0
#define __NRRM_access                     0
#define __NRRM_nice                       0
#define __NRRM_ftime                      0
#define __NRRM_sync                       0
#define __NRRM_kill                       0
#define __NRRM_rename                     0
#define __NRRM_mkdir                      0
#define __NRRM_rmdir                      0
#define __NRRM_dup                        0
#define __NRRM_pipe                       0
#define __NRRM_times                      0
#define __NRRM_brk                        0
#define __NRRM_setgid                     2
#define __NRRM_getgid                     2
#define __NRRM_signal                     0
#define __NRRM_geteuid                    2
#define __NRRM_getegid                    2
#define __NRRM_acct                       0
#define __NRRM_umount2                    2
#define __NRRM_ioctl                      0
#define __NRRM_fcntl                      0
#define __NRRM_setpgid                    2
#define __NRRM_oldolduname                0
#define __NRRM_umask                      2
#define __NRRM_chroot                     0
#define __NRRM_ustat                      0
#define __NRRM_dup2                       0
#define __NRRM_getppid                    2
#define __NRRM_getpgrp                    2
#define __NRRM_setsid                     2
#define __NRRM_sigaction                  0
#define __NRRM_sgetmask                   0
#define __NRRM_ssetmask                   0
#define __NRRM_setreuid                   2
#define __NRRM_setregid                   2
#define __NRRM_sigsuspend                 1
#define __NRRM_sigpending                 0
#define __NRRM_sethostname                0
#define __NRRM_setrlimit                  0
#define __NRRM_getrlimit                  0
#define __NRRM_getrusage                  0
#define __NRRM_gettimeofday               0
#define __NRRM_settimeofday               0
#define __NRRM_getgroups                  0
#define __NRRM_setgroups                  0
#define __NRRM_select                     1
#define __NRRM_symlink                    0
#define __NRRM_linux_oldlstat             0
#define __NRRM_readlink                   0
#define __NRRM_swapon                     0
#define __NRRM_reboot                     0
#define __NRRM_readdir                    0
#define __NRRM_mmap                       0
#define __NRRM_munmap                     2
#define __NRRM_truncate                   0
#define __NRRM_ftruncate                  0
#define __NRRM_fchmod                     0
#define __NRRM_fchown                     0
#define __NRRM_getpriority                0
#define __NRRM_setpriority                0
#define __NRRM_profil                     0
#define __NRRM_statfs                     0
#define __NRRM_fstatfs                    0
#define __NRRM_ioperm                     0
#define __NRRM_socketcall                 0
#define __NRRM_syslog                     2
#define __NRRM_setitimer                  0
#define __NRRM_getitimer                  0
#define __NRRM_linux_stat32               0
#define __NRRM_linux_lstat32              0
#define __NRRM_linux_fstat32              0
#define __NRRM_olduname                   0
#define __NRRM_iopl                       0
#define __NRRM_vhangup                    0
#define __NRRM_wait4                      1
#define __NRRM_swapoff                    0
#define __NRRM_sysinfo                    0
#define __NRRM_fsync                      0
#define __NRRM_sigreturn                  2
#define __NRRM_clone                      0
#define __NRRM_setdomainname              0
#define __NRRM_uname                      0
#define __NRRM_modify_ldt                 0
#define __NRRM_mprotect                   2
#define __NRRM_sigprocmask                0
#define __NRRM_getpgid                    2
#define __NRRM_fchdir                     0
#define __NRRM_setfsuid                   2
#define __NRRM_setfsgid                   2
#define __NRRM__llseek                    0
#define __NRRM_getdents                   0
#define __NRRM_flock                      0
#define __NRRM_msync                      0
#define __NRRM_readv                      0
#define __NRRM_writev                     0
#define __NRRM_getsid                     2
#define __NRRM_fdatasync                  0
#define __NRRM_mlock                      0
#define __NRRM_munlock                    0
#define __NRRM_mlockall                   0
#define __NRRM_munlockall                 0
#define __NRRM_sched_setparam             0
#define __NRRM_sched_getparam             0
#define __NRRM_sched_setscheduler         0
#define __NRRM_sched_getscheduler         0
#define __NRRM_sched_yield                1
#define __NRRM_sched_get_priority_max     0
#define __NRRM_sched_get_priority_min     0
#define __NRRM_sched_rr_get_interval      0
#define __NRRM_nanosleep                  1
#define __NRRM_mremap                     0
#define __NRRM_setresuid                  2
#define __NRRM_getresuid                  2
#define __NRRM_poll                       1
#define __NRRM_setresgid                  2
#define __NRRM_getresgid                  2
#define __NRRM_rt_sigaction               0
#define __NRRM_rt_sigprocmask             0
#define __NRRM_rt_sigpending              0
#define __NRRM_rt_sigtimedwait            1
#define __NRRM_rt_sigqueueinfo            0
#define __NRRM_rt_sigsuspend              0
#define __NRRM_pread64                    0
#define __NRRM_pwrite64                   0
#define __NRRM_chown                      0
#define __NRRM_getcwd                     0
#define __NRRM_sigaltstack                0
#define __NRRM_sendfile                   1
#define __NRRM_vfork                      0
#define __NRRM_mmap2                      0
#define __NRRM_truncate64                 0
#define __NRRM_ftruncate64                0
#define __NRRM_linux_stat64               0
#define __NRRM_linux_lstat64              0
#define __NRRM_linux_fstat64              0
#define __NRRM_lchown32                   0
#define __NRRM_getuid32                   2
#define __NRRM_getgid32                   2
#define __NRRM_geteuid32                  2
#define __NRRM_getegid32                  2
#define __NRRM_setreuid32                 2
#define __NRRM_setregid32                 2
#define __NRRM_getgroups32                2
#define __NRRM_setgroups32                2
#define __NRRM_fchown32                   0
#define __NRRM_setresuid32                2
#define __NRRM_getresuid32                2
#define __NRRM_setresgid32                2
#define __NRRM_getresgid32                2
#define __NRRM_chown32                    0
#define __NRRM_setuid32                   2
#define __NRRM_setgid32                   2
#define __NRRM_setfsuid32                 2
#define __NRRM_setfsgid32                 2
#define __NRRM_mincore                    0
#define __NRRM_madvise                    0
#define __NRRM_getdents64                 0
#define __NRRM_fcntl64                    0
#define __NRRM_gettid                     2
#define __NRRM_readahead                  0
#define __NRRM_setxattr                   0
#define __NRRM_lsetxattr                  0
#define __NRRM_fsetxattr                  0
#define __NRRM_getxattr                   0
#define __NRRM_lgetxattr                  0
#define __NRRM_fgetxattr                  0
#define __NRRM_listxattr                  0
#define __NRRM_llistxattr                 0
#define __NRRM_flistxattr                 0
#define __NRRM_removexattr                0
#define __NRRM_lremovexattr               0
#define __NRRM_fremovexattr               0
#define __NRRM_tkill                      0
#define __NRRM_sendfile64                 0
#define __NRRM_futex                      0
#define __NRRM_sched_setaffinity          0
#define __NRRM_sched_getaffinity          0
#define __NRRM_exit_group                 2
#define __NRRM_epoll_create               0
#define __NRRM_epoll_ctl                  0
#define __NRRM_epoll_wait                 1
#define __NRRM_remap_file_pages           0
#define __NRRM_set_tid_address            0
#define __NRRM_timer_create               0
#define __NRRM_timer_settime              0
#define __NRRM_timer_gettime              0
#define __NRRM_timer_getoverrun           0
#define __NRRM_timer_delete               0
#define __NRRM_clock_settime              0
#define __NRRM_clock_gettime              0
#define __NRRM_clock_getres               0
#define __NRRM_clock_nanosleep            1
#define __NRRM_statfs64                   0
#define __NRRM_fstatfs64                  0
#define __NRRM_tgkill                     0
#define __NRRM_utimes                     0
#define __NRRM_waitid                     1
#define __NRRM_ioprio_set                 0
#define __NRRM_ioprio_get                 0
#define __NRRM_openat                     0
#define __NRRM_mkdirat                    0
#define __NRRM_mknodat                    0
#define __NRRM_fchownat                   0
#define __NRRM_futimesat                  0
#define __NRRM_linux_fstatat64            0
#define __NRRM_unlinkat                   0
#define __NRRM_renameat                   0
#define __NRRM_linkat                     0
#define __NRRM_symlinkat                  0
#define __NRRM_readlinkat                 0
#define __NRRM_fchmodat                   0
#define __NRRM_faccessat                  0
#define __NRRM_pselect6                   1
#define __NRRM_ppoll                      1
#define __NRRM_unshare                    0
#define __NRRM_splice                     0
#define __NRRM_sync_file_range            0
#define __NRRM_tee                        0
#define __NRRM_vmsplice                   0
#define __NRRM_getcpu                     0
#define __NRRM_epoll_pwait                1
#define __NRRM_utimensat                  0
#define __NRRM_timerfd_create             0
#define __NRRM_eventfd                    0
#define __NRRM_fallocate                  0
#define __NRRM_timerfd_settime            0
#define __NRRM_timerfd_gettime            0
#define __NRRM_eventfd2                   0
#define __NRRM_epoll_create1              0
#define __NRRM_dup3                       0
#define __NRRM_pipe2                      0
#define __NRRM_preadv                     0
#define __NRRM_pwritev                    0
#define __NRRM_rt_tgsigqueueinfo          0
#define __NRRM_recvmmsg                   1
#define __NRRM_prlimit64                  0
#define __NRRM_name_to_handle_at          0
#define __NRRM_open_by_handle_at          0
#define __NRRM_syncfs                     0
#define __NRRM_sendmmsg                   1
#define __NRRM_setns                      0
#define __NRRM_process_vm_readv           0
#define __NRRM_process_vm_writev          0
#define __NRRM_kcmp                       0
#define __NRRM_renameat2                  0
#define __NRRM_execveat                   0
#define __NRRM_socket                     0
#define __NRRM_socketpair                 0
#define __NRRM_bind                       0
#define __NRRM_connect                    1
#define __NRRM_listen                     0
#define __NRRM_accept4                    1
#define __NRRM_getsockopt                 0
#define __NRRM_setsockopt                 1
#define __NRRM_getsockname                0
#define __NRRM_getpeername                0
#define __NRRM_sendto                     1
#define __NRRM_sendmsg                    1
#define __NRRM_recvfrom                   1
#define __NRRM_recvmsg                    1
#define __NRRM_shutdown                   0
#define __NRRM_hop                        0
#define __NRRM_hopf                       0
#define __NRRM_readf                      0
#define __NRRM_writef                     0
#define __NRRM_detach                     2
#define __NRRM_getdrives                  2
#define __NRRM_frealpath4                 0
#define __NRRM_frealpathat                0
#define __NRRM_rpc_schedule               0
#define __NRRM_sysctl                     0
#define __NRRM_openpty                    0
#define __NRRM_fchdirat                   0
#define __NRRM_time64                     0
#define __NRRM_set_exception_handler      2
#define __NRRM_get_exception_handler      2
#define __NRRM_set_library_listdef        2
#define __NRRM_debugtrap                  0
#define __NRRM_lfutex                     1
#define __NRRM_lseek64                    0
#define __NRRM_lfutexlock                 1
#define __NRRM_lfutexexpr                 1
#define __NRRM_lfutexlockexpr             1
#define __NRRM_mktty                      0
#define __NRRM_raiseat                    2
#define __NRRM_stime64                    0
#define __NRRM_coredump                   2
#define __NRRM_utime64                    0
#define __NRRM_ioctlf                     0
#define __NRRM_fsmode                     2
#define __NRRM_gettimeofday64             0
#define __NRRM_settimeofday64             0
#define __NRRM_select64                   1
#define __NRRM_maplibrary                 0
#define __NRRM_setitimer64                0
#define __NRRM_getitimer64                0
#define __NRRM_kreaddir                   0
#define __NRRM_readvf                     0
#define __NRRM_writevf                    0
#define __NRRM_rpc_service                1
#define __NRRM_sched_rr_get_interval64    0
#define __NRRM_nanosleep64                1
#define __NRRM_rt_sigtimedwait64          1
#define __NRRM_pread64f                   0
#define __NRRM_pwrite64f                  0
#define __NRRM_kstat                      0
#define __NRRM_klstat                     0
#define __NRRM_kfstat                     0
#define __NRRM_kreaddirf                  0
#define __NRRM_timer_settime64            0
#define __NRRM_timer_gettime64            0
#define __NRRM_clock_settime64            0
#define __NRRM_clock_gettime64            0
#define __NRRM_clock_getres64             0
#define __NRRM_clock_nanosleep64          1
#define __NRRM_utimes64                   0
#define __NRRM_fmkdirat                   0
#define __NRRM_fmknodat                   0
#define __NRRM_futimesat64                0
#define __NRRM_kfstatat                   0
#define __NRRM_frenameat                  0
#define __NRRM_fsymlinkat                 0
#define __NRRM_freadlinkat                0
#define __NRRM_pselect6_64                1
#define __NRRM_ppoll64                    1
#define __NRRM_utimensat64                0
#define __NRRM_fallocate64                0
#define __NRRM_timerfd_settime64          0
#define __NRRM_timerfd_gettime64          0
#define __NRRM_preadvf                    0
#define __NRRM_pwritevf                   0
#define __NRRM_recvmmsg64                 1
#endif /* __WANT_SYSCALL_RESTART_MODES */

#ifdef __WANT_SYSCALL_CANCELLATION_POINTS
#define __NRCP_exit                       0
#define __NRCP_fork                       0
#define __NRCP_read                       1
#define __NRCP_write                      1
#define __NRCP_open                       1
#define __NRCP_close                      0
#define __NRCP_waitpid                    1
#define __NRCP_creat                      1
#define __NRCP_link                       1
#define __NRCP_unlink                     1
#define __NRCP_execve                     1
#define __NRCP_chdir                      1
#define __NRCP_time                       0
#define __NRCP_mknod                      1
#define __NRCP_chmod                      1
#define __NRCP_lchown                     1
#define __NRCP_linux_oldstat              1
#define __NRCP_lseek                      1
#define __NRCP_getpid                     0
#define __NRCP_mount                      1
#define __NRCP_umount                     1
#define __NRCP_setuid                     0
#define __NRCP_getuid                     0
#define __NRCP_stime                      0
#define __NRCP_ptrace                     0
#define __NRCP_alarm                      0
#define __NRCP_linux_oldfstat             1
#define __NRCP_pause                      1
#define __NRCP_utime                      1
#define __NRCP_access                     1
#define __NRCP_nice                       0
#define __NRCP_ftime                      0
#define __NRCP_sync                       1
#define __NRCP_kill                       0
#define __NRCP_rename                     1
#define __NRCP_mkdir                      1
#define __NRCP_rmdir                      0
#define __NRCP_dup                        0
#define __NRCP_pipe                       0
#define __NRCP_times                      0
#define __NRCP_brk                        0
#define __NRCP_setgid                     0
#define __NRCP_getgid                     0
#define __NRCP_signal                     0
#define __NRCP_geteuid                    0
#define __NRCP_getegid                    0
#define __NRCP_acct                       0
#define __NRCP_umount2                    1
#define __NRCP_ioctl                      1
#define __NRCP_fcntl                      1
#define __NRCP_setpgid                    0
#define __NRCP_oldolduname                0
#define __NRCP_umask                      0
#define __NRCP_chroot                     0
#define __NRCP_ustat                      0
#define __NRCP_dup2                       0
#define __NRCP_getppid                    0
#define __NRCP_getpgrp                    0
#define __NRCP_setsid                     0
#define __NRCP_sigaction                  0
#define __NRCP_sgetmask                   0
#define __NRCP_ssetmask                   0
#define __NRCP_setreuid                   0
#define __NRCP_setregid                   0
#define __NRCP_sigsuspend                 1
#define __NRCP_sigpending                 0
#define __NRCP_sethostname                0
#define __NRCP_setrlimit                  0
#define __NRCP_getrlimit                  0
#define __NRCP_getrusage                  0
#define __NRCP_gettimeofday               0
#define __NRCP_settimeofday               0
#define __NRCP_getgroups                  0
#define __NRCP_setgroups                  0
#define __NRCP_select                     1
#define __NRCP_symlink                    1
#define __NRCP_linux_oldlstat             1
#define __NRCP_readlink                   1
#define __NRCP_swapon                     0
#define __NRCP_reboot                     0
#define __NRCP_readdir                    0
#define __NRCP_mmap                       0
#define __NRCP_munmap                     0
#define __NRCP_truncate                   0
#define __NRCP_ftruncate                  0
#define __NRCP_fchmod                     1
#define __NRCP_fchown                     1
#define __NRCP_getpriority                0
#define __NRCP_setpriority                0
#define __NRCP_profil                     0
#define __NRCP_statfs                     0
#define __NRCP_fstatfs                    0
#define __NRCP_ioperm                     0
#define __NRCP_socketcall                 0
#define __NRCP_syslog                     1
#define __NRCP_setitimer                  0
#define __NRCP_getitimer                  0
#define __NRCP_linux_stat32               1
#define __NRCP_linux_lstat32              1
#define __NRCP_linux_fstat32              1
#define __NRCP_olduname                   0
#define __NRCP_iopl                       0
#define __NRCP_vhangup                    0
#define __NRCP_wait4                      1
#define __NRCP_swapoff                    0
#define __NRCP_sysinfo                    1
#define __NRCP_fsync                      1
#define __NRCP_sigreturn                  0
#define __NRCP_clone                      0
#define __NRCP_setdomainname              0
#define __NRCP_uname                      0
#define __NRCP_modify_ldt                 0
#define __NRCP_mprotect                   0
#define __NRCP_sigprocmask                0
#define __NRCP_getpgid                    0
#define __NRCP_fchdir                     1
#define __NRCP_setfsuid                   0
#define __NRCP_setfsgid                   0
#define __NRCP__llseek                    1
#define __NRCP_getdents                   1
#define __NRCP_flock                      1
#define __NRCP_msync                      1
#define __NRCP_readv                      1
#define __NRCP_writev                     1
#define __NRCP_getsid                     0
#define __NRCP_fdatasync                  1
#define __NRCP_mlock                      0
#define __NRCP_munlock                    0
#define __NRCP_mlockall                   0
#define __NRCP_munlockall                 0
#define __NRCP_sched_setparam             0
#define __NRCP_sched_getparam             0
#define __NRCP_sched_setscheduler         0
#define __NRCP_sched_getscheduler         0
#define __NRCP_sched_yield                0
#define __NRCP_sched_get_priority_max     0
#define __NRCP_sched_get_priority_min     0
#define __NRCP_sched_rr_get_interval      0
#define __NRCP_nanosleep                  1
#define __NRCP_mremap                     0
#define __NRCP_setresuid                  0
#define __NRCP_getresuid                  0
#define __NRCP_poll                       1
#define __NRCP_setresgid                  0
#define __NRCP_getresgid                  0
#define __NRCP_rt_sigaction               0
#define __NRCP_rt_sigprocmask             0
#define __NRCP_rt_sigpending              0
#define __NRCP_rt_sigtimedwait            1
#define __NRCP_rt_sigqueueinfo            0
#define __NRCP_rt_sigsuspend              0
#define __NRCP_pread64                    1
#define __NRCP_pwrite64                   1
#define __NRCP_chown                      1
#define __NRCP_getcwd                     1
#define __NRCP_sigaltstack                0
#define __NRCP_sendfile                   1
#define __NRCP_vfork                      0
#define __NRCP_mmap2                      0
#define __NRCP_truncate64                 0
#define __NRCP_ftruncate64                0
#define __NRCP_linux_stat64               1
#define __NRCP_linux_lstat64              1
#define __NRCP_linux_fstat64              1
#define __NRCP_lchown32                   1
#define __NRCP_getuid32                   0
#define __NRCP_getgid32                   0
#define __NRCP_geteuid32                  0
#define __NRCP_getegid32                  0
#define __NRCP_setreuid32                 0
#define __NRCP_setregid32                 0
#define __NRCP_getgroups32                0
#define __NRCP_setgroups32                0
#define __NRCP_fchown32                   1
#define __NRCP_setresuid32                0
#define __NRCP_getresuid32                0
#define __NRCP_setresgid32                0
#define __NRCP_getresgid32                0
#define __NRCP_chown32                    1
#define __NRCP_setuid32                   0
#define __NRCP_setgid32                   0
#define __NRCP_setfsuid32                 0
#define __NRCP_setfsgid32                 0
#define __NRCP_mincore                    0
#define __NRCP_madvise                    0
#define __NRCP_getdents64                 1
#define __NRCP_fcntl64                    1
#define __NRCP_gettid                     0
#define __NRCP_readahead                  0
#define __NRCP_setxattr                   1
#define __NRCP_lsetxattr                  1
#define __NRCP_fsetxattr                  1
#define __NRCP_getxattr                   1
#define __NRCP_lgetxattr                  1
#define __NRCP_fgetxattr                  1
#define __NRCP_listxattr                  1
#define __NRCP_llistxattr                 1
#define __NRCP_flistxattr                 1
#define __NRCP_removexattr                1
#define __NRCP_lremovexattr               1
#define __NRCP_fremovexattr               1
#define __NRCP_tkill                      0
#define __NRCP_sendfile64                 0
#define __NRCP_futex                      1
#define __NRCP_sched_setaffinity          0
#define __NRCP_sched_getaffinity          0
#define __NRCP_exit_group                 0
#define __NRCP_epoll_create               0
#define __NRCP_epoll_ctl                  0
#define __NRCP_epoll_wait                 1
#define __NRCP_remap_file_pages           0
#define __NRCP_set_tid_address            0
#define __NRCP_timer_create               0
#define __NRCP_timer_settime              0
#define __NRCP_timer_gettime              0
#define __NRCP_timer_getoverrun           0
#define __NRCP_timer_delete               0
#define __NRCP_clock_settime              0
#define __NRCP_clock_gettime              0
#define __NRCP_clock_getres               0
#define __NRCP_clock_nanosleep            1
#define __NRCP_statfs64                   0
#define __NRCP_fstatfs64                  0
#define __NRCP_tgkill                     0
#define __NRCP_utimes                     1
#define __NRCP_waitid                     1
#define __NRCP_ioprio_set                 0
#define __NRCP_ioprio_get                 0
#define __NRCP_openat                     1
#define __NRCP_mkdirat                    1
#define __NRCP_mknodat                    1
#define __NRCP_fchownat                   1
#define __NRCP_futimesat                  1
#define __NRCP_linux_fstatat64            1
#define __NRCP_unlinkat                   1
#define __NRCP_renameat                   1
#define __NRCP_linkat                     1
#define __NRCP_symlinkat                  1
#define __NRCP_readlinkat                 1
#define __NRCP_fchmodat                   1
#define __NRCP_faccessat                  1
#define __NRCP_pselect6                   1
#define __NRCP_ppoll                      1
#define __NRCP_unshare                    0
#define __NRCP_splice                     1
#define __NRCP_sync_file_range            1
#define __NRCP_tee                        1
#define __NRCP_vmsplice                   1
#define __NRCP_getcpu                     0
#define __NRCP_epoll_pwait                1
#define __NRCP_utimensat                  1
#define __NRCP_timerfd_create             0
#define __NRCP_eventfd                    0
#define __NRCP_fallocate                  0
#define __NRCP_timerfd_settime            0
#define __NRCP_timerfd_gettime            0
#define __NRCP_eventfd2                   0
#define __NRCP_epoll_create1              0
#define __NRCP_dup3                       0
#define __NRCP_pipe2                      0
#define __NRCP_preadv                     1
#define __NRCP_pwritev                    1
#define __NRCP_rt_tgsigqueueinfo          0
#define __NRCP_recvmmsg                   1
#define __NRCP_prlimit64                  0
#define __NRCP_name_to_handle_at          1
#define __NRCP_open_by_handle_at          1
#define __NRCP_syncfs                     1
#define __NRCP_sendmmsg                   1
#define __NRCP_setns                      0
#define __NRCP_process_vm_readv           0
#define __NRCP_process_vm_writev          0
#define __NRCP_kcmp                       0
#define __NRCP_renameat2                  1
#define __NRCP_execveat                   1
#define __NRCP_socket                     0
#define __NRCP_socketpair                 0
#define __NRCP_bind                       0
#define __NRCP_connect                    1
#define __NRCP_listen                     0
#define __NRCP_accept4                    1
#define __NRCP_getsockopt                 0
#define __NRCP_setsockopt                 0
#define __NRCP_getsockname                0
#define __NRCP_getpeername                0
#define __NRCP_sendto                     1
#define __NRCP_sendmsg                    1
#define __NRCP_recvfrom                   1
#define __NRCP_recvmsg                    1
#define __NRCP_shutdown                   0
#define __NRCP_hop                        1
#define __NRCP_hopf                       1
#define __NRCP_readf                      1
#define __NRCP_writef                     1
#define __NRCP_detach                     0
#define __NRCP_getdrives                  0
#define __NRCP_frealpath4                 1
#define __NRCP_frealpathat                1
#define __NRCP_rpc_schedule               0
#define __NRCP_sysctl                     1
#define __NRCP_openpty                    0
#define __NRCP_fchdirat                   1
#define __NRCP_time64                     0
#define __NRCP_set_exception_handler      0
#define __NRCP_get_exception_handler      0
#define __NRCP_set_library_listdef        0
#define __NRCP_debugtrap                  0
#define __NRCP_lfutex                     1
#define __NRCP_lseek64                    1
#define __NRCP_lfutexlock                 1
#define __NRCP_lfutexexpr                 1
#define __NRCP_lfutexlockexpr             1
#define __NRCP_mktty                      0
#define __NRCP_raiseat                    0
#define __NRCP_stime64                    0
#define __NRCP_coredump                   0
#define __NRCP_utime64                    1
#define __NRCP_ioctlf                     1
#define __NRCP_fsmode                     0
#define __NRCP_gettimeofday64             0
#define __NRCP_settimeofday64             0
#define __NRCP_select64                   1
#define __NRCP_maplibrary                 0
#define __NRCP_setitimer64                0
#define __NRCP_getitimer64                0
#define __NRCP_kreaddir                   1
#define __NRCP_readvf                     1
#define __NRCP_writevf                    1
#define __NRCP_rpc_service                1
#define __NRCP_sched_rr_get_interval64    0
#define __NRCP_nanosleep64                1
#define __NRCP_rt_sigtimedwait64          1
#define __NRCP_pread64f                   1
#define __NRCP_pwrite64f                  1
#define __NRCP_kstat                      1
#define __NRCP_klstat                     1
#define __NRCP_kfstat                     1
#define __NRCP_kreaddirf                  1
#define __NRCP_timer_settime64            0
#define __NRCP_timer_gettime64            0
#define __NRCP_clock_settime64            0
#define __NRCP_clock_gettime64            0
#define __NRCP_clock_getres64             0
#define __NRCP_clock_nanosleep64          1
#define __NRCP_utimes64                   1
#define __NRCP_fmkdirat                   1
#define __NRCP_fmknodat                   1
#define __NRCP_futimesat64                1
#define __NRCP_kfstatat                   1
#define __NRCP_frenameat                  1
#define __NRCP_fsymlinkat                 1
#define __NRCP_freadlinkat                1
#define __NRCP_pselect6_64                1
#define __NRCP_ppoll64                    1
#define __NRCP_utimensat64                1
#define __NRCP_fallocate64                0
#define __NRCP_timerfd_settime64          0
#define __NRCP_timerfd_gettime64          0
#define __NRCP_preadvf                    1
#define __NRCP_pwritevf                   1
#define __NRCP_recvmmsg64                 1
#endif /* __WANT_SYSCALL_CANCELLATION_POINTS */

#ifdef __WANT_SYSCALL_RETURN_TYPES
#define __NRRT_exit                       void
#define __NRRT_fork                       pid_t
#define __NRRT_read                       ssize_t
#define __NRRT_write                      ssize_t
#define __NRRT_open                       fd_t
#define __NRRT_close                      errno_t
#define __NRRT_waitpid                    pid_t
#define __NRRT_creat                      fd_t
#define __NRRT_link                       errno_t
#define __NRRT_unlink                     errno_t
#define __NRRT_execve                     errno_t
#define __NRRT_chdir                      errno_t
#define __NRRT_time                       time32_t
#define __NRRT_mknod                      errno_t
#define __NRRT_chmod                      errno_t
#define __NRRT_lchown                     errno_t
#define __NRRT_linux_oldstat              errno_t
#define __NRRT_lseek                      int32_t
#define __NRRT_getpid                     pid_t
#define __NRRT_mount                      errno_t
#define __NRRT_umount                     errno_t
#define __NRRT_setuid                     errno_t
#define __NRRT_getuid                     uint16_t
#define __NRRT_stime                      errno_t
#define __NRRT_ptrace                     syscall_slong_t
#define __NRRT_alarm                      syscall_ulong_t
#define __NRRT_linux_oldfstat             errno_t
#define __NRRT_pause                      errno_t
#define __NRRT_utime                      errno_t
#define __NRRT_access                     errno_t
#define __NRRT_nice                       errno_t
#define __NRRT_ftime                      errno_t
#define __NRRT_sync                       errno_t
#define __NRRT_kill                       errno_t
#define __NRRT_rename                     errno_t
#define __NRRT_mkdir                      errno_t
#define __NRRT_rmdir                      errno_t
#define __NRRT_dup                        fd_t
#define __NRRT_pipe                       errno_t
#define __NRRT_times                      clock_t
#define __NRRT_brk                        errno_t
#define __NRRT_setgid                     errno_t
#define __NRRT_getgid                     uint16_t
#define __NRRT_signal                     sighandler_t
#define __NRRT_geteuid                    uint16_t
#define __NRRT_getegid                    uint16_t
#define __NRRT_acct                       errno_t
#define __NRRT_umount2                    errno_t
#define __NRRT_ioctl                      syscall_slong_t
#define __NRRT_fcntl                      syscall_slong_t
#define __NRRT_setpgid                    errno_t
#define __NRRT_oldolduname                errno_t
#define __NRRT_umask                      mode_t
#define __NRRT_chroot                     errno_t
#define __NRRT_ustat                      errno_t
#define __NRRT_dup2                       fd_t
#define __NRRT_getppid                    pid_t
#define __NRRT_getpgrp                    pid_t
#define __NRRT_setsid                     pid_t
#define __NRRT_sigaction                  errno_t
#define __NRRT_sgetmask                   syscall_ulong_t
#define __NRRT_ssetmask                   syscall_ulong_t
#define __NRRT_setreuid                   errno_t
#define __NRRT_setregid                   errno_t
#define __NRRT_sigsuspend                 errno_t
#define __NRRT_sigpending                 errno_t
#define __NRRT_sethostname                errno_t
#define __NRRT_setrlimit                  errno_t
#define __NRRT_getrlimit                  errno_t
#define __NRRT_getrusage                  errno_t
#define __NRRT_gettimeofday               errno_t
#define __NRRT_settimeofday               errno_t
#define __NRRT_getgroups                  errno_t
#define __NRRT_setgroups                  errno_t
#define __NRRT_select                     ssize_t
#define __NRRT_symlink                    errno_t
#define __NRRT_linux_oldlstat             errno_t
#define __NRRT_readlink                   ssize_t
#define __NRRT_swapon                     errno_t
#define __NRRT_reboot                     errno_t
#define __NRRT_readdir                    errno_t
#define __NRRT_mmap                       void *
#define __NRRT_munmap                     errno_t
#define __NRRT_truncate                   errno_t
#define __NRRT_ftruncate                  errno_t
#define __NRRT_fchmod                     errno_t
#define __NRRT_fchown                     errno_t
#define __NRRT_getpriority                syscall_slong_t
#define __NRRT_setpriority                errno_t
#define __NRRT_profil                     errno_t
#define __NRRT_statfs                     errno_t
#define __NRRT_fstatfs                    errno_t
#define __NRRT_ioperm                     errno_t
#define __NRRT_socketcall                 errno_t
#define __NRRT_syslog                     ssize_t
#define __NRRT_setitimer                  errno_t
#define __NRRT_getitimer                  errno_t
#define __NRRT_linux_stat32               errno_t
#define __NRRT_linux_lstat32              errno_t
#define __NRRT_linux_fstat32              errno_t
#define __NRRT_olduname                   errno_t
#define __NRRT_iopl                       errno_t
#define __NRRT_vhangup                    errno_t
#define __NRRT_wait4                      pid_t
#define __NRRT_swapoff                    errno_t
#define __NRRT_sysinfo                    errno_t
#define __NRRT_fsync                      errno_t
#define __NRRT_sigreturn                  void
#define __NRRT_clone                      pid_t
#define __NRRT_setdomainname              errno_t
#define __NRRT_uname                      errno_t
#define __NRRT_modify_ldt                 syscall_slong_t
#define __NRRT_mprotect                   errno_t
#define __NRRT_sigprocmask                errno_t
#define __NRRT_getpgid                    pid_t
#define __NRRT_fchdir                     errno_t
#define __NRRT_setfsuid                   errno_t
#define __NRRT_setfsgid                   errno_t
#define __NRRT__llseek                    errno_t
#define __NRRT_getdents                   ssize_t
#define __NRRT_flock                      errno_t
#define __NRRT_msync                      errno_t
#define __NRRT_readv                      ssize_t
#define __NRRT_writev                     ssize_t
#define __NRRT_getsid                     pid_t
#define __NRRT_fdatasync                  errno_t
#define __NRRT_mlock                      errno_t
#define __NRRT_munlock                    errno_t
#define __NRRT_mlockall                   errno_t
#define __NRRT_munlockall                 errno_t
#define __NRRT_sched_setparam             errno_t
#define __NRRT_sched_getparam             errno_t
#define __NRRT_sched_setscheduler         errno_t
#define __NRRT_sched_getscheduler         syscall_slong_t
#define __NRRT_sched_yield                errno_t
#define __NRRT_sched_get_priority_max     syscall_slong_t
#define __NRRT_sched_get_priority_min     syscall_slong_t
#define __NRRT_sched_rr_get_interval      errno_t
#define __NRRT_nanosleep                  errno_t
#define __NRRT_mremap                     void *
#define __NRRT_setresuid                  errno_t
#define __NRRT_getresuid                  errno_t
#define __NRRT_poll                       ssize_t
#define __NRRT_setresgid                  errno_t
#define __NRRT_getresgid                  errno_t
#define __NRRT_rt_sigaction               errno_t
#define __NRRT_rt_sigprocmask             errno_t
#define __NRRT_rt_sigpending              errno_t
#define __NRRT_rt_sigtimedwait            syscall_slong_t
#define __NRRT_rt_sigqueueinfo            errno_t
#define __NRRT_rt_sigsuspend              errno_t
#define __NRRT_pread64                    ssize_t
#define __NRRT_pwrite64                   ssize_t
#define __NRRT_chown                      errno_t
#define __NRRT_getcwd                     ssize_t
#define __NRRT_sigaltstack                errno_t
#define __NRRT_sendfile                   ssize_t
#define __NRRT_vfork                      pid_t
#define __NRRT_mmap2                      void *
#define __NRRT_truncate64                 errno_t
#define __NRRT_ftruncate64                errno_t
#define __NRRT_linux_stat64               errno_t
#define __NRRT_linux_lstat64              errno_t
#define __NRRT_linux_fstat64              errno_t
#define __NRRT_lchown32                   errno_t
#define __NRRT_getuid32                   uint32_t
#define __NRRT_getgid32                   uint32_t
#define __NRRT_geteuid32                  uint32_t
#define __NRRT_getegid32                  uint32_t
#define __NRRT_setreuid32                 errno_t
#define __NRRT_setregid32                 errno_t
#define __NRRT_getgroups32                errno_t
#define __NRRT_setgroups32                errno_t
#define __NRRT_fchown32                   errno_t
#define __NRRT_setresuid32                errno_t
#define __NRRT_getresuid32                errno_t
#define __NRRT_setresgid32                errno_t
#define __NRRT_getresgid32                errno_t
#define __NRRT_chown32                    errno_t
#define __NRRT_setuid32                   errno_t
#define __NRRT_setgid32                   errno_t
#define __NRRT_setfsuid32                 errno_t
#define __NRRT_setfsgid32                 errno_t
#define __NRRT_mincore                    errno_t
#define __NRRT_madvise                    errno_t
#define __NRRT_getdents64                 ssize_t
#define __NRRT_fcntl64                    syscall_slong_t
#define __NRRT_gettid                     pid_t
#define __NRRT_readahead                  ssize_t
#define __NRRT_setxattr                   errno_t
#define __NRRT_lsetxattr                  errno_t
#define __NRRT_fsetxattr                  errno_t
#define __NRRT_getxattr                   ssize_t
#define __NRRT_lgetxattr                  ssize_t
#define __NRRT_fgetxattr                  ssize_t
#define __NRRT_listxattr                  ssize_t
#define __NRRT_llistxattr                 ssize_t
#define __NRRT_flistxattr                 ssize_t
#define __NRRT_removexattr                errno_t
#define __NRRT_lremovexattr               errno_t
#define __NRRT_fremovexattr               errno_t
#define __NRRT_tkill                      errno_t
#define __NRRT_sendfile64                 ssize_t
#define __NRRT_futex                      syscall_slong_t
#define __NRRT_sched_setaffinity          errno_t
#define __NRRT_sched_getaffinity          errno_t
#define __NRRT_exit_group                 void
#define __NRRT_epoll_create               fd_t
#define __NRRT_epoll_ctl                  errno_t
#define __NRRT_epoll_wait                 errno_t
#define __NRRT_remap_file_pages           errno_t
#define __NRRT_set_tid_address            pid_t
#define __NRRT_timer_create               errno_t
#define __NRRT_timer_settime              errno_t
#define __NRRT_timer_gettime              errno_t
#define __NRRT_timer_getoverrun           syscall_slong_t
#define __NRRT_timer_delete               errno_t
#define __NRRT_clock_settime              errno_t
#define __NRRT_clock_gettime              errno_t
#define __NRRT_clock_getres               errno_t
#define __NRRT_clock_nanosleep            errno_t
#define __NRRT_statfs64                   errno_t
#define __NRRT_fstatfs64                  errno_t
#define __NRRT_tgkill                     errno_t
#define __NRRT_utimes                     errno_t
#define __NRRT_waitid                     errno_t
#define __NRRT_ioprio_set                 errno_t
#define __NRRT_ioprio_get                 errno_t
#define __NRRT_openat                     fd_t
#define __NRRT_mkdirat                    errno_t
#define __NRRT_mknodat                    errno_t
#define __NRRT_fchownat                   errno_t
#define __NRRT_futimesat                  errno_t
#define __NRRT_linux_fstatat64            errno_t
#define __NRRT_unlinkat                   errno_t
#define __NRRT_renameat                   errno_t
#define __NRRT_linkat                     errno_t
#define __NRRT_symlinkat                  errno_t
#define __NRRT_readlinkat                 ssize_t
#define __NRRT_fchmodat                   errno_t
#define __NRRT_faccessat                  errno_t
#define __NRRT_pselect6                   ssize_t
#define __NRRT_ppoll                      ssize_t
#define __NRRT_unshare                    errno_t
#define __NRRT_splice                     ssize_t
#define __NRRT_sync_file_range            errno_t
#define __NRRT_tee                        ssize_t
#define __NRRT_vmsplice                   ssize_t
#define __NRRT_getcpu                     errno_t
#define __NRRT_epoll_pwait                errno_t
#define __NRRT_utimensat                  errno_t
#define __NRRT_timerfd_create             fd_t
#define __NRRT_eventfd                    errno_t
#define __NRRT_fallocate                  errno_t
#define __NRRT_timerfd_settime            errno_t
#define __NRRT_timerfd_gettime            errno_t
#define __NRRT_eventfd2                   errno_t
#define __NRRT_epoll_create1              fd_t
#define __NRRT_dup3                       fd_t
#define __NRRT_pipe2                      errno_t
#define __NRRT_preadv                     ssize_t
#define __NRRT_pwritev                    ssize_t
#define __NRRT_rt_tgsigqueueinfo          errno_t
#define __NRRT_recvmmsg                   ssize_t
#define __NRRT_prlimit64                  errno_t
#define __NRRT_name_to_handle_at          errno_t
#define __NRRT_open_by_handle_at          fd_t
#define __NRRT_syncfs                     errno_t
#define __NRRT_sendmmsg                   ssize_t
#define __NRRT_setns                      errno_t
#define __NRRT_process_vm_readv           ssize_t
#define __NRRT_process_vm_writev          ssize_t
#define __NRRT_kcmp                       syscall_slong_t
#define __NRRT_renameat2                  errno_t
#define __NRRT_execveat                   errno_t
#define __NRRT_socket                     fd_t
#define __NRRT_socketpair                 errno_t
#define __NRRT_bind                       errno_t
#define __NRRT_connect                    errno_t
#define __NRRT_listen                     errno_t
#define __NRRT_accept4                    fd_t
#define __NRRT_getsockopt                 errno_t
#define __NRRT_setsockopt                 errno_t
#define __NRRT_getsockname                errno_t
#define __NRRT_getpeername                errno_t
#define __NRRT_sendto                     ssize_t
#define __NRRT_sendmsg                    ssize_t
#define __NRRT_recvfrom                   ssize_t
#define __NRRT_recvmsg                    ssize_t
#define __NRRT_shutdown                   errno_t
#define __NRRT_hop                        syscall_slong_t
#define __NRRT_hopf                       syscall_slong_t
#define __NRRT_readf                      ssize_t
#define __NRRT_writef                     ssize_t
#define __NRRT_detach                     errno_t
#define __NRRT_getdrives                  syscall_slong_t
#define __NRRT_frealpath4                 ssize_t
#define __NRRT_frealpathat                ssize_t
#define __NRRT_rpc_schedule               syscall_slong_t
#define __NRRT_sysctl                     syscall_slong_t
#define __NRRT_openpty                    errno_t
#define __NRRT_fchdirat                   errno_t
#define __NRRT_time64                     time64_t
#define __NRRT_set_exception_handler      errno_t
#define __NRRT_get_exception_handler      errno_t
#define __NRRT_set_library_listdef        errno_t
#define __NRRT_debugtrap                  errno_t
#define __NRRT_lfutex                     syscall_slong_t
#define __NRRT_lseek64                    int64_t
#define __NRRT_lfutexlock                 syscall_slong_t
#define __NRRT_lfutexexpr                 errno_t
#define __NRRT_lfutexlockexpr             errno_t
#define __NRRT_mktty                      fd_t
#define __NRRT_raiseat                    errno_t
#define __NRRT_stime64                    errno_t
#define __NRRT_coredump                   errno_t
#define __NRRT_utime64                    errno_t
#define __NRRT_ioctlf                     syscall_slong_t
#define __NRRT_fsmode                     uint64_t
#define __NRRT_gettimeofday64             errno_t
#define __NRRT_settimeofday64             errno_t
#define __NRRT_select64                   ssize_t
#define __NRRT_maplibrary                 void *
#define __NRRT_setitimer64                errno_t
#define __NRRT_getitimer64                errno_t
#define __NRRT_kreaddir                   ssize_t
#define __NRRT_readvf                     ssize_t
#define __NRRT_writevf                    ssize_t
#define __NRRT_rpc_service                syscall_slong_t
#define __NRRT_sched_rr_get_interval64    errno_t
#define __NRRT_nanosleep64                errno_t
#define __NRRT_rt_sigtimedwait64          syscall_slong_t
#define __NRRT_pread64f                   ssize_t
#define __NRRT_pwrite64f                  ssize_t
#define __NRRT_kstat                      errno_t
#define __NRRT_klstat                     errno_t
#define __NRRT_kfstat                     errno_t
#define __NRRT_kreaddirf                  ssize_t
#define __NRRT_timer_settime64            errno_t
#define __NRRT_timer_gettime64            errno_t
#define __NRRT_clock_settime64            errno_t
#define __NRRT_clock_gettime64            errno_t
#define __NRRT_clock_getres64             errno_t
#define __NRRT_clock_nanosleep64          errno_t
#define __NRRT_utimes64                   errno_t
#define __NRRT_fmkdirat                   errno_t
#define __NRRT_fmknodat                   errno_t
#define __NRRT_futimesat64                errno_t
#define __NRRT_kfstatat                   errno_t
#define __NRRT_frenameat                  errno_t
#define __NRRT_fsymlinkat                 errno_t
#define __NRRT_freadlinkat                ssize_t
#define __NRRT_pselect6_64                ssize_t
#define __NRRT_ppoll64                    ssize_t
#define __NRRT_utimensat64                errno_t
#define __NRRT_fallocate64                errno_t
#define __NRRT_timerfd_settime64          errno_t
#define __NRRT_timerfd_gettime64          errno_t
#define __NRRT_preadvf                    ssize_t
#define __NRRT_pwritevf                   ssize_t
#define __NRRT_recvmmsg64                 ssize_t
#endif /* __WANT_SYSCALL_RETURN_TYPES */

#ifdef __WANT_SYSCALL_ARGUMENT_TYPES
#define __NRAT0_exit                       syscall_ulong_t
#define __NRAT0_read                       fd_t
#define __NRAT1_read                       void *
#define __NRAT2_read                       size_t
#define __NRAT0_write                      fd_t
#define __NRAT1_write                      void const *
#define __NRAT2_write                      size_t
#define __NRAT0_open                       char const *
#define __NRAT1_open                       oflag_t
#define __NRAT2_open                       mode_t
#define __NRAT0_close                      fd_t
#define __NRAT0_waitpid                    pid_t
#define __NRAT1_waitpid                    int32_t *
#define __NRAT2_waitpid                    syscall_ulong_t
#define __NRAT0_creat                      char const *
#define __NRAT1_creat                      mode_t
#define __NRAT0_link                       char const *
#define __NRAT1_link                       char const *
#define __NRAT0_unlink                     char const *
#define __NRAT0_execve                     char const *
#define __NRAT1_execve                     char const *const *
#define __NRAT2_execve                     char const *const *
#define __NRAT0_chdir                      char const *
#define __NRAT0_time                       time32_t *
#define __NRAT0_mknod                      char const *
#define __NRAT1_mknod                      mode_t
#define __NRAT2_mknod                      dev_t
#define __NRAT0_chmod                      char const *
#define __NRAT1_chmod                      mode_t
#define __NRAT0_lchown                     char const *
#define __NRAT1_lchown                     uint16_t
#define __NRAT2_lchown                     uint16_t
#define __NRAT0_linux_oldstat              char const *
#define __NRAT1_linux_oldstat              struct linux_oldstat *
#define __NRAT0_lseek                      fd_t
#define __NRAT1_lseek                      int32_t
#define __NRAT2_lseek                      syscall_ulong_t
#define __NRAT0_mount                      char const *
#define __NRAT1_mount                      char const *
#define __NRAT2_mount                      char const *
#define __NRAT3_mount                      syscall_ulong_t
#define __NRAT4_mount                      void const *
#define __NRAT0_umount                     char const *
#define __NRAT0_setuid                     uint16_t
#define __NRAT0_stime                      time32_t const *
#define __NRAT0_ptrace                     syscall_ulong_t
#define __NRAT1_ptrace                     pid_t
#define __NRAT2_ptrace                     void *
#define __NRAT3_ptrace                     void *
#define __NRAT0_alarm                      syscall_ulong_t
#define __NRAT0_linux_oldfstat             fd_t
#define __NRAT1_linux_oldfstat             struct linux_oldstat *
#define __NRAT0_utime                      char const *
#define __NRAT1_utime                      struct __utimbuf32 const *
#define __NRAT0_access                     char const *
#define __NRAT1_access                     syscall_ulong_t
#define __NRAT0_nice                       syscall_slong_t
#define __NRAT0_ftime                      struct timeb *
#define __NRAT0_kill                       pid_t
#define __NRAT1_kill                       syscall_ulong_t
#define __NRAT0_rename                     char const *
#define __NRAT1_rename                     char const *
#define __NRAT0_mkdir                      char const *
#define __NRAT1_mkdir                      mode_t
#define __NRAT0_rmdir                      char const *
#define __NRAT0_dup                        fd_t
#define __NRAT0_pipe                       /*[2]*/fd_t *
#define __NRAT0_times                      struct tms *
#define __NRAT0_brk                        void *
#define __NRAT0_setgid                     uint16_t
#define __NRAT0_signal                     syscall_ulong_t
#define __NRAT1_signal                     sighandler_t
#define __NRAT0_acct                       char const *
#define __NRAT0_umount2                    char const *
#define __NRAT1_umount2                    syscall_ulong_t
#define __NRAT0_ioctl                      fd_t
#define __NRAT1_ioctl                      syscall_ulong_t
#define __NRAT2_ioctl                      void *
#define __NRAT0_fcntl                      fd_t
#define __NRAT1_fcntl                      syscall_ulong_t
#define __NRAT2_fcntl                      void *
#define __NRAT0_setpgid                    pid_t
#define __NRAT1_setpgid                    pid_t
#define __NRAT0_oldolduname                struct linux_oldolduname *
#define __NRAT0_umask                      mode_t
#define __NRAT0_chroot                     char const *
#define __NRAT0_ustat                      dev_t
#define __NRAT1_ustat                      struct ustat *
#define __NRAT0_dup2                       fd_t
#define __NRAT1_dup2                       fd_t
#define __NRAT0_sigaction                  syscall_ulong_t
#define __NRAT1_sigaction                  struct sigaction const *
#define __NRAT2_sigaction                  struct sigaction *
#define __NRAT0_ssetmask                   syscall_ulong_t
#define __NRAT0_setreuid                   uint16_t
#define __NRAT1_setreuid                   uint16_t
#define __NRAT0_setregid                   uint16_t
#define __NRAT1_setregid                   uint16_t
#define __NRAT0_sigsuspend                 struct __sigset_struct const *
#define __NRAT0_sigpending                 struct __sigset_struct *
#define __NRAT0_sethostname                char const *
#define __NRAT1_sethostname                size_t
#define __NRAT0_setrlimit                  syscall_ulong_t
#define __NRAT1_setrlimit                  struct rlimit const *
#define __NRAT0_getrlimit                  syscall_ulong_t
#define __NRAT1_getrlimit                  struct rlimit *
#define __NRAT0_getrusage                  syscall_slong_t
#define __NRAT1_getrusage                  struct rusage *
#define __NRAT0_gettimeofday               struct __timeval32 *
#define __NRAT1_gettimeofday               struct timezone *
#define __NRAT0_settimeofday               struct __timeval32 const *
#define __NRAT1_settimeofday               struct timezone const *
#define __NRAT0_getgroups                  size_t
#define __NRAT1_getgroups                  /*[]*/uint16_t *
#define __NRAT0_setgroups                  size_t
#define __NRAT1_setgroups                  uint16_t const *
#define __NRAT0_select                     size_t
#define __NRAT1_select                     struct __fd_set_struct *
#define __NRAT2_select                     struct __fd_set_struct *
#define __NRAT3_select                     struct __fd_set_struct *
#define __NRAT4_select                     struct __timeval32 *
#define __NRAT0_symlink                    char const *
#define __NRAT1_symlink                    char const *
#define __NRAT0_linux_oldlstat             char const *
#define __NRAT1_linux_oldlstat             struct linux_oldstat *
#define __NRAT0_readlink                   char const *
#define __NRAT1_readlink                   char *
#define __NRAT2_readlink                   size_t
#define __NRAT0_swapon                     char const *
#define __NRAT1_swapon                     syscall_ulong_t
#define __NRAT0_reboot                     syscall_ulong_t
#define __NRAT0_readdir                    fd_t
#define __NRAT1_readdir                    struct old_linux_dirent *
#define __NRAT2_readdir                    size_t
#define __NRAT0_mmap                       void *
#define __NRAT1_mmap                       size_t
#define __NRAT2_mmap                       syscall_ulong_t
#define __NRAT3_mmap                       syscall_ulong_t
#define __NRAT4_mmap                       fd_t
#define __NRAT5_mmap                       syscall_ulong_t
#define __NRAT0_munmap                     void *
#define __NRAT1_munmap                     size_t
#define __NRAT0_truncate                   char const *
#define __NRAT1_truncate                   syscall_ulong_t
#define __NRAT0_ftruncate                  fd_t
#define __NRAT1_ftruncate                  syscall_ulong_t
#define __NRAT0_fchmod                     fd_t
#define __NRAT1_fchmod                     mode_t
#define __NRAT0_fchown                     fd_t
#define __NRAT1_fchown                     uint16_t
#define __NRAT2_fchown                     uint16_t
#define __NRAT0_getpriority                syscall_ulong_t
#define __NRAT1_getpriority                id_t
#define __NRAT0_setpriority                syscall_ulong_t
#define __NRAT1_setpriority                id_t
#define __NRAT2_setpriority                syscall_ulong_t
#define __NRAT0_profil                     uint16_t *
#define __NRAT1_profil                     size_t
#define __NRAT2_profil                     size_t
#define __NRAT3_profil                     syscall_ulong_t
#define __NRAT0_statfs                     char const *
#define __NRAT1_statfs                     struct __statfs32 *
#define __NRAT0_fstatfs                    fd_t
#define __NRAT1_fstatfs                    struct __statfs32 *
#define __NRAT0_ioperm                     syscall_ulong_t
#define __NRAT1_ioperm                     syscall_ulong_t
#define __NRAT2_ioperm                     syscall_ulong_t
#define __NRAT0_socketcall                 int
#define __NRAT1_socketcall                 unsigned long *
#define __NRAT0_syslog                     syscall_ulong_t
#define __NRAT1_syslog                     char const *
#define __NRAT2_syslog                     size_t
#define __NRAT0_setitimer                  syscall_ulong_t
#define __NRAT1_setitimer                  struct __itimerval32 const *
#define __NRAT2_setitimer                  struct __itimerval32 *
#define __NRAT0_getitimer                  syscall_ulong_t
#define __NRAT1_getitimer                  struct __itimerval32 *
#define __NRAT0_linux_stat32               char const *
#define __NRAT1_linux_stat32               struct linux_stat32 *
#define __NRAT0_linux_lstat32              char const *
#define __NRAT1_linux_lstat32              struct linux_stat32 *
#define __NRAT0_linux_fstat32              fd_t
#define __NRAT1_linux_fstat32              struct linux_stat32 *
#define __NRAT0_olduname                   struct linux_olduname *
#define __NRAT0_iopl                       syscall_ulong_t
#define __NRAT0_wait4                      pid_t
#define __NRAT1_wait4                      int32_t *
#define __NRAT2_wait4                      syscall_ulong_t
#define __NRAT3_wait4                      struct rusage *
#define __NRAT0_swapoff                    char const *
#define __NRAT0_sysinfo                    struct sysinfo *
#define __NRAT0_fsync                      fd_t
#define __NRAT0_sigreturn                  struct fpustate const *
#define __NRAT1_sigreturn                  syscall_ulong_t
#define __NRAT2_sigreturn                  syscall_ulong_t
#define __NRAT3_sigreturn                  struct __sigset_struct const *
#define __NRAT4_sigreturn                  struct rpc_syscall_info *
#define __NRAT5_sigreturn                  struct ucpustate const *
#define __NRAT0_clone                      syscall_ulong_t
#define __NRAT1_clone                      void *
#define __NRAT2_clone                      pid_t *
#define __NRAT3_clone                      uintptr_t
#define __NRAT4_clone                      pid_t *
#define __NRAT0_setdomainname              char const *
#define __NRAT1_setdomainname              size_t
#define __NRAT0_uname                      struct utsname *
#define __NRAT0_modify_ldt                 syscall_ulong_t
#define __NRAT1_modify_ldt                 void *
#define __NRAT2_modify_ldt                 syscall_ulong_t
#define __NRAT0_mprotect                   void *
#define __NRAT1_mprotect                   size_t
#define __NRAT2_mprotect                   syscall_ulong_t
#define __NRAT0_sigprocmask                syscall_ulong_t
#define __NRAT1_sigprocmask                struct __sigset_struct const *
#define __NRAT2_sigprocmask                struct __sigset_struct *
#define __NRAT0_getpgid                    pid_t
#define __NRAT0_fchdir                     fd_t
#define __NRAT0_setfsuid                   uint16_t
#define __NRAT0_setfsgid                   uint16_t
#define __NRAT0__llseek                    fd_t
#define __NRAT1__llseek                    int64_t
#define __NRAT2__llseek                    uint64_t *
#define __NRAT3__llseek                    syscall_ulong_t
#define __NRAT0_getdents                   fd_t
#define __NRAT1_getdents                   struct linux_dirent *
#define __NRAT2_getdents                   size_t
#define __NRAT0_flock                      fd_t
#define __NRAT1_flock                      syscall_ulong_t
#define __NRAT0_msync                      void *
#define __NRAT1_msync                      size_t
#define __NRAT2_msync                      syscall_ulong_t
#define __NRAT0_readv                      fd_t
#define __NRAT1_readv                      struct iovec const *
#define __NRAT2_readv                      size_t
#define __NRAT0_writev                     fd_t
#define __NRAT1_writev                     struct iovec const *
#define __NRAT2_writev                     size_t
#define __NRAT0_getsid                     pid_t
#define __NRAT0_fdatasync                  fd_t
#define __NRAT0_mlock                      void const *
#define __NRAT1_mlock                      size_t
#define __NRAT0_munlock                    void const *
#define __NRAT1_munlock                    size_t
#define __NRAT0_mlockall                   syscall_ulong_t
#define __NRAT0_sched_setparam             pid_t
#define __NRAT1_sched_setparam             struct sched_param const *
#define __NRAT0_sched_getparam             pid_t
#define __NRAT1_sched_getparam             struct sched_param *
#define __NRAT0_sched_setscheduler         pid_t
#define __NRAT1_sched_setscheduler         syscall_ulong_t
#define __NRAT2_sched_setscheduler         struct sched_param const *
#define __NRAT0_sched_getscheduler         pid_t
#define __NRAT0_sched_get_priority_max     syscall_ulong_t
#define __NRAT0_sched_get_priority_min     syscall_ulong_t
#define __NRAT0_sched_rr_get_interval      pid_t
#define __NRAT1_sched_rr_get_interval      struct __timespec32 *
#define __NRAT0_nanosleep                  struct __timespec32 const *
#define __NRAT1_nanosleep                  struct __timespec32 *
#define __NRAT0_mremap                     void *
#define __NRAT1_mremap                     size_t
#define __NRAT2_mremap                     size_t
#define __NRAT3_mremap                     syscall_ulong_t
#define __NRAT4_mremap                     void *
#define __NRAT0_setresuid                  uint16_t
#define __NRAT1_setresuid                  uint16_t
#define __NRAT2_setresuid                  uint16_t
#define __NRAT0_getresuid                  uint16_t *
#define __NRAT1_getresuid                  uint16_t *
#define __NRAT2_getresuid                  uint16_t *
#define __NRAT0_poll                       struct pollfd *
#define __NRAT1_poll                       size_t
#define __NRAT2_poll                       syscall_slong_t
#define __NRAT0_setresgid                  uint16_t
#define __NRAT1_setresgid                  uint16_t
#define __NRAT2_setresgid                  uint16_t
#define __NRAT0_getresgid                  uint16_t *
#define __NRAT1_getresgid                  uint16_t *
#define __NRAT2_getresgid                  uint16_t *
#define __NRAT0_rt_sigaction               syscall_ulong_t
#define __NRAT1_rt_sigaction               struct sigaction const *
#define __NRAT2_rt_sigaction               struct sigaction *
#define __NRAT3_rt_sigaction               size_t
#define __NRAT0_rt_sigprocmask             syscall_ulong_t
#define __NRAT1_rt_sigprocmask             struct __sigset_struct const *
#define __NRAT2_rt_sigprocmask             struct __sigset_struct *
#define __NRAT3_rt_sigprocmask             size_t
#define __NRAT0_rt_sigpending              struct __sigset_struct *
#define __NRAT1_rt_sigpending              size_t
#define __NRAT0_rt_sigtimedwait            struct __sigset_struct const *
#define __NRAT1_rt_sigtimedwait            struct __siginfo_struct *
#define __NRAT2_rt_sigtimedwait            struct __timespec32 const *
#define __NRAT3_rt_sigtimedwait            size_t
#define __NRAT0_rt_sigqueueinfo            pid_t
#define __NRAT1_rt_sigqueueinfo            syscall_ulong_t
#define __NRAT2_rt_sigqueueinfo            struct __siginfo_struct const *
#define __NRAT0_rt_sigsuspend              struct __sigset_struct const *
#define __NRAT1_rt_sigsuspend              size_t
#define __NRAT0_pread64                    fd_t
#define __NRAT1_pread64                    void *
#define __NRAT2_pread64                    size_t
#define __NRAT3_pread64                    uint64_t
#define __NRAT0_pwrite64                   fd_t
#define __NRAT1_pwrite64                   void const *
#define __NRAT2_pwrite64                   size_t
#define __NRAT3_pwrite64                   uint64_t
#define __NRAT0_chown                      char const *
#define __NRAT1_chown                      uint16_t
#define __NRAT2_chown                      uint16_t
#define __NRAT0_getcwd                     char *
#define __NRAT1_getcwd                     size_t
#define __NRAT0_sigaltstack                struct sigaltstack const *
#define __NRAT1_sigaltstack                struct sigaltstack *
#define __NRAT0_sendfile                   fd_t
#define __NRAT1_sendfile                   fd_t
#define __NRAT2_sendfile                   syscall_ulong_t *
#define __NRAT3_sendfile                   size_t
#define __NRAT0_mmap2                      void *
#define __NRAT1_mmap2                      size_t
#define __NRAT2_mmap2                      syscall_ulong_t
#define __NRAT3_mmap2                      syscall_ulong_t
#define __NRAT4_mmap2                      fd_t
#define __NRAT5_mmap2                      syscall_ulong_t
#define __NRAT0_truncate64                 char const *
#define __NRAT1_truncate64                 uint64_t
#define __NRAT0_ftruncate64                fd_t
#define __NRAT1_ftruncate64                uint64_t
#define __NRAT0_linux_stat64               char const *
#define __NRAT1_linux_stat64               struct linux_stat64 *
#define __NRAT0_linux_lstat64              char const *
#define __NRAT1_linux_lstat64              struct linux_stat64 *
#define __NRAT0_linux_fstat64              fd_t
#define __NRAT1_linux_fstat64              struct linux_stat64 *
#define __NRAT0_lchown32                   char const *
#define __NRAT1_lchown32                   uint32_t
#define __NRAT2_lchown32                   uint32_t
#define __NRAT0_setreuid32                 uint32_t
#define __NRAT1_setreuid32                 uint32_t
#define __NRAT0_setregid32                 uint32_t
#define __NRAT1_setregid32                 uint32_t
#define __NRAT0_getgroups32                size_t
#define __NRAT1_getgroups32                /*[]*/uint32_t *
#define __NRAT0_setgroups32                size_t
#define __NRAT1_setgroups32                uint32_t const *
#define __NRAT0_fchown32                   fd_t
#define __NRAT1_fchown32                   uint32_t
#define __NRAT2_fchown32                   uint32_t
#define __NRAT0_setresuid32                uint32_t
#define __NRAT1_setresuid32                uint32_t
#define __NRAT2_setresuid32                uint32_t
#define __NRAT0_getresuid32                uint32_t *
#define __NRAT1_getresuid32                uint32_t *
#define __NRAT2_getresuid32                uint32_t *
#define __NRAT0_setresgid32                uint32_t
#define __NRAT1_setresgid32                uint32_t
#define __NRAT2_setresgid32                uint32_t
#define __NRAT0_getresgid32                uint32_t *
#define __NRAT1_getresgid32                uint32_t *
#define __NRAT2_getresgid32                uint32_t *
#define __NRAT0_chown32                    char const *
#define __NRAT1_chown32                    uint32_t
#define __NRAT2_chown32                    uint32_t
#define __NRAT0_setuid32                   uint32_t
#define __NRAT0_setgid32                   uint32_t
#define __NRAT0_setfsuid32                 uint32_t
#define __NRAT0_setfsgid32                 uint32_t
#define __NRAT0_mincore                    void *
#define __NRAT1_mincore                    size_t
#define __NRAT2_mincore                    uint8_t *
#define __NRAT0_madvise                    void *
#define __NRAT1_madvise                    size_t
#define __NRAT2_madvise                    syscall_ulong_t
#define __NRAT0_getdents64                 fd_t
#define __NRAT1_getdents64                 struct linux_dirent64 *
#define __NRAT2_getdents64                 size_t
#define __NRAT0_fcntl64                    fd_t
#define __NRAT1_fcntl64                    syscall_ulong_t
#define __NRAT2_fcntl64                    void *
#define __NRAT0_readahead                  fd_t
#define __NRAT1_readahead                  uint64_t
#define __NRAT2_readahead                  size_t
#define __NRAT0_setxattr                   char const *
#define __NRAT1_setxattr                   char const *
#define __NRAT2_setxattr                   void const *
#define __NRAT3_setxattr                   size_t
#define __NRAT4_setxattr                   syscall_ulong_t
#define __NRAT0_lsetxattr                  char const *
#define __NRAT1_lsetxattr                  char const *
#define __NRAT2_lsetxattr                  void const *
#define __NRAT3_lsetxattr                  size_t
#define __NRAT4_lsetxattr                  syscall_ulong_t
#define __NRAT0_fsetxattr                  fd_t
#define __NRAT1_fsetxattr                  char const *
#define __NRAT2_fsetxattr                  void const *
#define __NRAT3_fsetxattr                  size_t
#define __NRAT4_fsetxattr                  syscall_ulong_t
#define __NRAT0_getxattr                   char const *
#define __NRAT1_getxattr                   char const *
#define __NRAT2_getxattr                   void *
#define __NRAT3_getxattr                   size_t
#define __NRAT0_lgetxattr                  char const *
#define __NRAT1_lgetxattr                  char const *
#define __NRAT2_lgetxattr                  void *
#define __NRAT3_lgetxattr                  size_t
#define __NRAT0_fgetxattr                  fd_t
#define __NRAT1_fgetxattr                  char const *
#define __NRAT2_fgetxattr                  void *
#define __NRAT3_fgetxattr                  size_t
#define __NRAT0_listxattr                  char const *
#define __NRAT1_listxattr                  char *
#define __NRAT2_listxattr                  size_t
#define __NRAT0_llistxattr                 char const *
#define __NRAT1_llistxattr                 char *
#define __NRAT2_llistxattr                 size_t
#define __NRAT0_flistxattr                 fd_t
#define __NRAT1_flistxattr                 char *
#define __NRAT2_flistxattr                 size_t
#define __NRAT0_removexattr                char const *
#define __NRAT1_removexattr                char const *
#define __NRAT0_lremovexattr               char const *
#define __NRAT1_lremovexattr               char const *
#define __NRAT0_fremovexattr               int
#define __NRAT1_fremovexattr               char const *
#define __NRAT0_tkill                      pid_t
#define __NRAT1_tkill                      syscall_ulong_t
#define __NRAT0_sendfile64                 fd_t
#define __NRAT1_sendfile64                 fd_t
#define __NRAT2_sendfile64                 uint64_t *
#define __NRAT3_sendfile64                 size_t
#define __NRAT0_futex                      uint32_t *
#define __NRAT1_futex                      syscall_ulong_t
#define __NRAT2_futex                      uint32_t
#define __NRAT3_futex                      struct __timespec32 const *
#define __NRAT4_futex                      uint32_t *
#define __NRAT5_futex                      uint32_t
#define __NRAT0_sched_setaffinity          pid_t
#define __NRAT1_sched_setaffinity          size_t
#define __NRAT2_sched_setaffinity          struct __cpu_set_struct const *
#define __NRAT0_sched_getaffinity          pid_t
#define __NRAT1_sched_getaffinity          size_t
#define __NRAT2_sched_getaffinity          struct __cpu_set_struct *
#define __NRAT0_exit_group                 syscall_ulong_t
#define __NRAT0_epoll_create               syscall_ulong_t
#define __NRAT0_epoll_ctl                  fd_t
#define __NRAT1_epoll_ctl                  syscall_ulong_t
#define __NRAT2_epoll_ctl                  fd_t
#define __NRAT3_epoll_ctl                  struct epoll_event *
#define __NRAT0_epoll_wait                 fd_t
#define __NRAT1_epoll_wait                 struct epoll_event *
#define __NRAT2_epoll_wait                 syscall_ulong_t
#define __NRAT3_epoll_wait                 syscall_slong_t
#define __NRAT0_remap_file_pages           void *
#define __NRAT1_remap_file_pages           size_t
#define __NRAT2_remap_file_pages           syscall_ulong_t
#define __NRAT3_remap_file_pages           size_t
#define __NRAT4_remap_file_pages           syscall_ulong_t
#define __NRAT0_set_tid_address            pid_t *
#define __NRAT0_timer_create               clockid_t
#define __NRAT1_timer_create               struct sigevent *
#define __NRAT2_timer_create               timer_t *
#define __NRAT0_timer_settime              timer_t
#define __NRAT1_timer_settime              syscall_ulong_t
#define __NRAT2_timer_settime              struct __itimerspec32 const *
#define __NRAT3_timer_settime              struct __itimerspec32 *
#define __NRAT0_timer_gettime              timer_t
#define __NRAT1_timer_gettime              struct __itimerspec32 *
#define __NRAT0_timer_getoverrun           timer_t
#define __NRAT0_timer_delete               timer_t
#define __NRAT0_clock_settime              clockid_t
#define __NRAT1_clock_settime              struct __timespec32 const *
#define __NRAT0_clock_gettime              clockid_t
#define __NRAT1_clock_gettime              struct __timespec32 *
#define __NRAT0_clock_getres               clockid_t
#define __NRAT1_clock_getres               struct __timespec32 *
#define __NRAT0_clock_nanosleep            clockid_t
#define __NRAT1_clock_nanosleep            syscall_ulong_t
#define __NRAT2_clock_nanosleep            struct __timespec32 const *
#define __NRAT3_clock_nanosleep            struct __timespec32 *
#define __NRAT0_statfs64                   char const *
#define __NRAT1_statfs64                   struct statfs64 *
#define __NRAT0_fstatfs64                  fd_t
#define __NRAT1_fstatfs64                  struct statfs64 *
#define __NRAT0_tgkill                     pid_t
#define __NRAT1_tgkill                     pid_t
#define __NRAT2_tgkill                     syscall_ulong_t
#define __NRAT0_utimes                     char const *
#define __NRAT1_utimes                     /*[2]*/struct __timeval32 const *
#define __NRAT0_waitid                     idtype_t
#define __NRAT1_waitid                     id_t
#define __NRAT2_waitid                     struct __siginfo_struct *
#define __NRAT3_waitid                     syscall_ulong_t
#define __NRAT4_waitid                     struct rusage *
#define __NRAT0_ioprio_set                 syscall_ulong_t
#define __NRAT1_ioprio_set                 syscall_ulong_t
#define __NRAT2_ioprio_set                 syscall_ulong_t
#define __NRAT0_ioprio_get                 syscall_ulong_t
#define __NRAT1_ioprio_get                 syscall_ulong_t
#define __NRAT0_openat                     fd_t
#define __NRAT1_openat                     char const *
#define __NRAT2_openat                     oflag_t
#define __NRAT3_openat                     mode_t
#define __NRAT0_mkdirat                    fd_t
#define __NRAT1_mkdirat                    char const *
#define __NRAT2_mkdirat                    mode_t
#define __NRAT0_mknodat                    fd_t
#define __NRAT1_mknodat                    char const *
#define __NRAT2_mknodat                    mode_t
#define __NRAT3_mknodat                    dev_t
#define __NRAT0_fchownat                   fd_t
#define __NRAT1_fchownat                   char const *
#define __NRAT2_fchownat                   uint32_t
#define __NRAT3_fchownat                   uint32_t
#define __NRAT4_fchownat                   atflag_t
#define __NRAT0_futimesat                  fd_t
#define __NRAT1_futimesat                  const char *
#define __NRAT2_futimesat                  /*[2]*/struct __timeval32 const *
#define __NRAT0_linux_fstatat64            fd_t
#define __NRAT1_linux_fstatat64            char const *
#define __NRAT2_linux_fstatat64            struct linux_stat64 *
#define __NRAT3_linux_fstatat64            atflag_t
#define __NRAT0_unlinkat                   fd_t
#define __NRAT1_unlinkat                   char const *
#define __NRAT2_unlinkat                   atflag_t
#define __NRAT0_renameat                   fd_t
#define __NRAT1_renameat                   char const *
#define __NRAT2_renameat                   fd_t
#define __NRAT3_renameat                   char const *
#define __NRAT0_linkat                     fd_t
#define __NRAT1_linkat                     char const *
#define __NRAT2_linkat                     fd_t
#define __NRAT3_linkat                     char const *
#define __NRAT4_linkat                     atflag_t
#define __NRAT0_symlinkat                  char const *
#define __NRAT1_symlinkat                  fd_t
#define __NRAT2_symlinkat                  char const *
#define __NRAT0_readlinkat                 fd_t
#define __NRAT1_readlinkat                 char const *
#define __NRAT2_readlinkat                 char *
#define __NRAT3_readlinkat                 size_t
#define __NRAT0_fchmodat                   fd_t
#define __NRAT1_fchmodat                   char const *
#define __NRAT2_fchmodat                   mode_t
#define __NRAT3_fchmodat                   atflag_t
#define __NRAT0_faccessat                  fd_t
#define __NRAT1_faccessat                  char const *
#define __NRAT2_faccessat                  syscall_ulong_t
#define __NRAT3_faccessat                  atflag_t
#define __NRAT0_pselect6                   size_t
#define __NRAT1_pselect6                   struct __fd_set_struct *
#define __NRAT2_pselect6                   struct __fd_set_struct *
#define __NRAT3_pselect6                   struct __fd_set_struct *
#define __NRAT4_pselect6                   struct __timespec32 const *
#define __NRAT5_pselect6                   void const *
#define __NRAT0_ppoll                      struct pollfd *
#define __NRAT1_ppoll                      size_t
#define __NRAT2_ppoll                      struct __timespec32 const *
#define __NRAT3_ppoll                      struct __sigset_struct const *
#define __NRAT4_ppoll                      size_t
#define __NRAT0_unshare                    syscall_ulong_t
#define __NRAT0_splice                     fd_t
#define __NRAT1_splice                     uint64_t *
#define __NRAT2_splice                     fd_t
#define __NRAT3_splice                     uint64_t *
#define __NRAT4_splice                     size_t
#define __NRAT5_splice                     syscall_ulong_t
#define __NRAT0_sync_file_range            fd_t
#define __NRAT1_sync_file_range            uint64_t
#define __NRAT2_sync_file_range            uint64_t
#define __NRAT3_sync_file_range            syscall_ulong_t
#define __NRAT0_tee                        fd_t
#define __NRAT1_tee                        fd_t
#define __NRAT2_tee                        size_t
#define __NRAT3_tee                        syscall_ulong_t
#define __NRAT0_vmsplice                   fd_t
#define __NRAT1_vmsplice                   struct iovec const *
#define __NRAT2_vmsplice                   size_t
#define __NRAT3_vmsplice                   syscall_ulong_t
#define __NRAT0_getcpu                     uint32_t *
#define __NRAT1_getcpu                     uint32_t *
#define __NRAT2_getcpu                     struct getcpu_cache *
#define __NRAT0_epoll_pwait                fd_t
#define __NRAT1_epoll_pwait                struct epoll_event *
#define __NRAT2_epoll_pwait                syscall_ulong_t
#define __NRAT3_epoll_pwait                syscall_slong_t
#define __NRAT4_epoll_pwait                struct __sigset_struct const *
#define __NRAT0_utimensat                  fd_t
#define __NRAT1_utimensat                  char const *
#define __NRAT2_utimensat                  /*[2-3]*/struct __timespec32 const *
#define __NRAT3_utimensat                  atflag_t
#define __NRAT0_timerfd_create             clockid_t
#define __NRAT1_timerfd_create             syscall_ulong_t
#define __NRAT0_eventfd                    syscall_ulong_t
#define __NRAT0_fallocate                  fd_t
#define __NRAT1_fallocate                  syscall_ulong_t
#define __NRAT2_fallocate                  uint32_t
#define __NRAT3_fallocate                  uint32_t
#define __NRAT0_timerfd_settime            fd_t
#define __NRAT1_timerfd_settime            syscall_ulong_t
#define __NRAT2_timerfd_settime            struct __itimerspec32 const *
#define __NRAT3_timerfd_settime            struct __itimerspec32 *
#define __NRAT0_timerfd_gettime            fd_t
#define __NRAT1_timerfd_gettime            struct __itimerspec32 *
#define __NRAT0_eventfd2                   syscall_ulong_t
#define __NRAT1_eventfd2                   syscall_ulong_t
#define __NRAT0_epoll_create1              syscall_ulong_t
#define __NRAT0_dup3                       fd_t
#define __NRAT1_dup3                       fd_t
#define __NRAT2_dup3                       oflag_t
#define __NRAT0_pipe2                      /*[2]*/fd_t *
#define __NRAT1_pipe2                      oflag_t
#define __NRAT0_preadv                     fd_t
#define __NRAT1_preadv                     struct iovec const *
#define __NRAT2_preadv                     size_t
#define __NRAT3_preadv                     uint64_t
#define __NRAT0_pwritev                    fd_t
#define __NRAT1_pwritev                    struct iovec const *
#define __NRAT2_pwritev                    size_t
#define __NRAT3_pwritev                    uint64_t
#define __NRAT0_rt_tgsigqueueinfo          pid_t
#define __NRAT1_rt_tgsigqueueinfo          pid_t
#define __NRAT2_rt_tgsigqueueinfo          syscall_ulong_t
#define __NRAT3_rt_tgsigqueueinfo          struct __siginfo_struct const *
#define __NRAT0_recvmmsg                   fd_t
#define __NRAT1_recvmmsg                   struct mmsghdr *
#define __NRAT2_recvmmsg                   size_t
#define __NRAT3_recvmmsg                   syscall_ulong_t
#define __NRAT4_recvmmsg                   struct __timespec32 *
#define __NRAT0_prlimit64                  pid_t
#define __NRAT1_prlimit64                  syscall_ulong_t
#define __NRAT2_prlimit64                  struct rlimit64 const *
#define __NRAT3_prlimit64                  struct rlimit64 *
#define __NRAT0_name_to_handle_at          fd_t
#define __NRAT1_name_to_handle_at          char const *
#define __NRAT2_name_to_handle_at          struct file_handle *
#define __NRAT3_name_to_handle_at          int32_t *
#define __NRAT4_name_to_handle_at          syscall_ulong_t
#define __NRAT0_open_by_handle_at          fd_t
#define __NRAT1_open_by_handle_at          struct file_handle *
#define __NRAT2_open_by_handle_at          syscall_ulong_t
#define __NRAT0_syncfs                     fd_t
#define __NRAT0_sendmmsg                   fd_t
#define __NRAT1_sendmmsg                   struct mmsghdr *
#define __NRAT2_sendmmsg                   size_t
#define __NRAT3_sendmmsg                   syscall_ulong_t
#define __NRAT0_setns                      fd_t
#define __NRAT1_setns                      syscall_ulong_t
#define __NRAT0_process_vm_readv           pid_t
#define __NRAT1_process_vm_readv           struct iovec const *
#define __NRAT2_process_vm_readv           size_t
#define __NRAT3_process_vm_readv           struct iovec const *
#define __NRAT4_process_vm_readv           size_t
#define __NRAT5_process_vm_readv           syscall_ulong_t
#define __NRAT0_process_vm_writev          pid_t
#define __NRAT1_process_vm_writev          struct iovec const *
#define __NRAT2_process_vm_writev          size_t
#define __NRAT3_process_vm_writev          struct iovec const *
#define __NRAT4_process_vm_writev          size_t
#define __NRAT5_process_vm_writev          syscall_ulong_t
#define __NRAT0_kcmp                       pid_t
#define __NRAT1_kcmp                       pid_t
#define __NRAT2_kcmp                       syscall_ulong_t
#define __NRAT3_kcmp                       syscall_ulong_t
#define __NRAT4_kcmp                       syscall_ulong_t
#define __NRAT0_renameat2                  fd_t
#define __NRAT1_renameat2                  char const *
#define __NRAT2_renameat2                  fd_t
#define __NRAT3_renameat2                  char const *
#define __NRAT4_renameat2                  syscall_ulong_t
#define __NRAT0_execveat                   fd_t
#define __NRAT1_execveat                   char const *
#define __NRAT2_execveat                   char const *const *
#define __NRAT3_execveat                   char const *const *
#define __NRAT4_execveat                   atflag_t
#define __NRAT0_socket                     syscall_ulong_t
#define __NRAT1_socket                     syscall_ulong_t
#define __NRAT2_socket                     syscall_ulong_t
#define __NRAT0_socketpair                 syscall_ulong_t
#define __NRAT1_socketpair                 syscall_ulong_t
#define __NRAT2_socketpair                 syscall_ulong_t
#define __NRAT3_socketpair                 /*[2]*/fd_t *
#define __NRAT0_bind                       fd_t
#define __NRAT1_bind                       struct sockaddr const *
#define __NRAT2_bind                       socklen_t
#define __NRAT0_connect                    fd_t
#define __NRAT1_connect                    struct sockaddr const *
#define __NRAT2_connect                    socklen_t
#define __NRAT0_listen                     fd_t
#define __NRAT1_listen                     syscall_ulong_t
#define __NRAT0_accept4                    fd_t
#define __NRAT1_accept4                    struct sockaddr *
#define __NRAT2_accept4                    socklen_t *
#define __NRAT3_accept4                    syscall_ulong_t
#define __NRAT0_getsockopt                 fd_t
#define __NRAT1_getsockopt                 syscall_ulong_t
#define __NRAT2_getsockopt                 syscall_ulong_t
#define __NRAT3_getsockopt                 void *
#define __NRAT4_getsockopt                 socklen_t *
#define __NRAT0_setsockopt                 fd_t
#define __NRAT1_setsockopt                 syscall_ulong_t
#define __NRAT2_setsockopt                 syscall_ulong_t
#define __NRAT3_setsockopt                 void const *
#define __NRAT4_setsockopt                 socklen_t
#define __NRAT0_getsockname                fd_t
#define __NRAT1_getsockname                struct sockaddr *
#define __NRAT2_getsockname                socklen_t *
#define __NRAT0_getpeername                fd_t
#define __NRAT1_getpeername                struct sockaddr *
#define __NRAT2_getpeername                socklen_t *
#define __NRAT0_sendto                     fd_t
#define __NRAT1_sendto                     void const *
#define __NRAT2_sendto                     size_t
#define __NRAT3_sendto                     syscall_ulong_t
#define __NRAT4_sendto                     struct sockaddr const *
#define __NRAT5_sendto                     socklen_t
#define __NRAT0_sendmsg                    fd_t
#define __NRAT1_sendmsg                    struct msghdr const *
#define __NRAT2_sendmsg                    syscall_ulong_t
#define __NRAT0_recvfrom                   fd_t
#define __NRAT1_recvfrom                   void *
#define __NRAT2_recvfrom                   size_t
#define __NRAT3_recvfrom                   syscall_ulong_t
#define __NRAT4_recvfrom                   struct sockaddr *
#define __NRAT5_recvfrom                   socklen_t *
#define __NRAT0_recvmsg                    fd_t
#define __NRAT1_recvmsg                    struct msghdr *
#define __NRAT2_recvmsg                    syscall_ulong_t
#define __NRAT0_shutdown                   fd_t
#define __NRAT1_shutdown                   syscall_ulong_t
#define __NRAT0_hop                        fd_t
#define __NRAT1_hop                        syscall_ulong_t
#define __NRAT2_hop                        void *
#define __NRAT0_hopf                       fd_t
#define __NRAT1_hopf                       syscall_ulong_t
#define __NRAT2_hopf                       iomode_t
#define __NRAT3_hopf                       void *
#define __NRAT0_readf                      fd_t
#define __NRAT1_readf                      void *
#define __NRAT2_readf                      size_t
#define __NRAT3_readf                      iomode_t
#define __NRAT0_writef                     fd_t
#define __NRAT1_writef                     void const *
#define __NRAT2_writef                     size_t
#define __NRAT3_writef                     iomode_t
#define __NRAT0_detach                     pid_t
#define __NRAT0_frealpath4                 fd_t
#define __NRAT1_frealpath4                 char *
#define __NRAT2_frealpath4                 size_t
#define __NRAT3_frealpath4                 atflag_t
#define __NRAT0_frealpathat                fd_t
#define __NRAT1_frealpathat                char const *
#define __NRAT2_frealpathat                char *
#define __NRAT3_frealpathat                size_t
#define __NRAT4_frealpathat                atflag_t
#define __NRAT0_rpc_schedule               pid_t
#define __NRAT1_rpc_schedule               syscall_ulong_t
#define __NRAT2_rpc_schedule               uint8_t const *
#define __NRAT3_rpc_schedule               void **
#define __NRAT0_sysctl                     syscall_ulong_t
#define __NRAT1_sysctl                     void *
#define __NRAT0_openpty                    fd_t *
#define __NRAT1_openpty                    fd_t *
#define __NRAT2_openpty                    char *
#define __NRAT3_openpty                    struct termios const *
#define __NRAT4_openpty                    struct winsize const *
#define __NRAT0_fchdirat                   fd_t
#define __NRAT1_fchdirat                   char const *
#define __NRAT2_fchdirat                   atflag_t
#define __NRAT0_time64                     time64_t *
#define __NRAT0_set_exception_handler      syscall_ulong_t
#define __NRAT1_set_exception_handler      except_handler_t
#define __NRAT2_set_exception_handler      void *
#define __NRAT0_get_exception_handler      syscall_ulong_t *
#define __NRAT1_get_exception_handler      except_handler_t *
#define __NRAT2_get_exception_handler      void **
#define __NRAT0_set_library_listdef        struct library_listdef const *
#define __NRAT0_debugtrap                  struct ucpustate const *
#define __NRAT1_debugtrap                  syscall_ulong_t
#define __NRAT2_debugtrap                  struct debug_trap_register const *
#define __NRAT0_lfutex                     uintptr_t *
#define __NRAT1_lfutex                     syscall_ulong_t
#define __NRAT2_lfutex                     uintptr_t
#define __NRAT3_lfutex                     struct __timespec64 const *
#define __NRAT4_lfutex                     uintptr_t
#define __NRAT0_lseek64                    fd_t
#define __NRAT1_lseek64                    int64_t
#define __NRAT2_lseek64                    syscall_ulong_t
#define __NRAT0_lfutexlock                 uintptr_t *
#define __NRAT1_lfutexlock                 uintptr_t *
#define __NRAT2_lfutexlock                 syscall_ulong_t
#define __NRAT3_lfutexlock                 uintptr_t
#define __NRAT4_lfutexlock                 struct __timespec64 const *
#define __NRAT5_lfutexlock                 uintptr_t
#define __NRAT0_lfutexexpr                 uintptr_t *
#define __NRAT1_lfutexexpr                 void *
#define __NRAT2_lfutexexpr                 struct lfutexexpr const *
#define __NRAT3_lfutexexpr                 size_t
#define __NRAT4_lfutexexpr                 struct __timespec64 const *
#define __NRAT5_lfutexexpr                 syscall_ulong_t
#define __NRAT0_lfutexlockexpr             uintptr_t *
#define __NRAT1_lfutexlockexpr             void *
#define __NRAT2_lfutexlockexpr             struct lfutexexpr const *
#define __NRAT3_lfutexlockexpr             size_t
#define __NRAT4_lfutexlockexpr             struct __timespec64 const *
#define __NRAT5_lfutexlockexpr             syscall_ulong_t
#define __NRAT0_mktty                      fd_t
#define __NRAT1_mktty                      fd_t
#define __NRAT2_mktty                      char const *
#define __NRAT3_mktty                      syscall_ulong_t
#define __NRAT0_raiseat                    struct ucpustate const *
#define __NRAT1_raiseat                    struct __siginfo_struct const *
#define __NRAT0_stime64                    time64_t const *
#define __NRAT0_coredump                   struct ucpustate const *
#define __NRAT1_coredump                   struct ucpustate const *
#define __NRAT2_coredump                   void const *const *
#define __NRAT3_coredump                   size_t
#define __NRAT4_coredump                   struct exception_data const *
#define __NRAT5_coredump                   syscall_ulong_t
#define __NRAT0_utime64                    char const *
#define __NRAT1_utime64                    struct utimbuf64 const *
#define __NRAT0_ioctlf                     fd_t
#define __NRAT1_ioctlf                     syscall_ulong_t
#define __NRAT2_ioctlf                     iomode_t
#define __NRAT3_ioctlf                     void *
#define __NRAT0_fsmode                     uint64_t
#define __NRAT0_gettimeofday64             struct __timeval64 *
#define __NRAT1_gettimeofday64             struct timezone *
#define __NRAT0_settimeofday64             struct __timeval64 const *
#define __NRAT1_settimeofday64             struct timezone const *
#define __NRAT0_select64                   size_t
#define __NRAT1_select64                   struct __fd_set_struct *
#define __NRAT2_select64                   struct __fd_set_struct *
#define __NRAT3_select64                   struct __fd_set_struct *
#define __NRAT4_select64                   struct __timeval64 *
#define __NRAT0_maplibrary                 void *
#define __NRAT1_maplibrary                 syscall_ulong_t
#define __NRAT2_maplibrary                 fd_t
#define __NRAT3_maplibrary                 void *
#define __NRAT4_maplibrary                 size_t
#define __NRAT0_setitimer64                syscall_ulong_t
#define __NRAT1_setitimer64                struct __itimerval64 const *
#define __NRAT2_setitimer64                struct __itimerval64 *
#define __NRAT0_getitimer64                syscall_ulong_t
#define __NRAT1_getitimer64                struct __itimerval64 *
#define __NRAT0_kreaddir                   fd_t
#define __NRAT1_kreaddir                   struct dirent *
#define __NRAT2_kreaddir                   size_t
#define __NRAT3_kreaddir                   syscall_ulong_t
#define __NRAT0_readvf                     fd_t
#define __NRAT1_readvf                     struct iovec const *
#define __NRAT2_readvf                     size_t
#define __NRAT3_readvf                     iomode_t
#define __NRAT0_writevf                    fd_t
#define __NRAT1_writevf                    struct iovec const *
#define __NRAT2_writevf                    size_t
#define __NRAT3_writevf                    iomode_t
#define __NRAT0_sched_rr_get_interval64    pid_t
#define __NRAT1_sched_rr_get_interval64    struct __timespec64 *
#define __NRAT0_nanosleep64                struct __timespec64 const *
#define __NRAT1_nanosleep64                struct __timespec64 *
#define __NRAT0_rt_sigtimedwait64          struct __sigset_struct const *
#define __NRAT1_rt_sigtimedwait64          struct __siginfo_struct *
#define __NRAT2_rt_sigtimedwait64          struct __timespec64 const *
#define __NRAT3_rt_sigtimedwait64          size_t
#define __NRAT0_pread64f                   fd_t
#define __NRAT1_pread64f                   void *
#define __NRAT2_pread64f                   size_t
#define __NRAT3_pread64f                   uint64_t
#define __NRAT4_pread64f                   iomode_t
#define __NRAT0_pwrite64f                  fd_t
#define __NRAT1_pwrite64f                  void const *
#define __NRAT2_pwrite64f                  size_t
#define __NRAT3_pwrite64f                  uint64_t
#define __NRAT4_pwrite64f                  iomode_t
#define __NRAT0_kstat                      char const *
#define __NRAT1_kstat                      struct stat *
#define __NRAT0_klstat                     char const *
#define __NRAT1_klstat                     struct stat *
#define __NRAT0_kfstat                     fd_t
#define __NRAT1_kfstat                     struct stat *
#define __NRAT0_kreaddirf                  fd_t
#define __NRAT1_kreaddirf                  struct dirent *
#define __NRAT2_kreaddirf                  size_t
#define __NRAT3_kreaddirf                  syscall_ulong_t
#define __NRAT4_kreaddirf                  iomode_t
#define __NRAT0_timer_settime64            timer_t
#define __NRAT1_timer_settime64            syscall_ulong_t
#define __NRAT2_timer_settime64            struct __itimerspec64 const *
#define __NRAT3_timer_settime64            struct __itimerspec64 *
#define __NRAT0_timer_gettime64            timer_t
#define __NRAT1_timer_gettime64            struct __itimerspec64 *
#define __NRAT0_clock_settime64            clockid_t
#define __NRAT1_clock_settime64            struct __timespec64 const *
#define __NRAT0_clock_gettime64            clockid_t
#define __NRAT1_clock_gettime64            struct __timespec64 *
#define __NRAT0_clock_getres64             clockid_t
#define __NRAT1_clock_getres64             struct __timespec64 *
#define __NRAT0_clock_nanosleep64          clockid_t
#define __NRAT1_clock_nanosleep64          syscall_ulong_t
#define __NRAT2_clock_nanosleep64          struct __timespec64 const *
#define __NRAT3_clock_nanosleep64          struct __timespec64 *
#define __NRAT0_utimes64                   char const *
#define __NRAT1_utimes64                   /*[2]*/struct __timeval64 const *
#define __NRAT0_fmkdirat                   fd_t
#define __NRAT1_fmkdirat                   char const *
#define __NRAT2_fmkdirat                   mode_t
#define __NRAT3_fmkdirat                   atflag_t
#define __NRAT0_fmknodat                   fd_t
#define __NRAT1_fmknodat                   char const *
#define __NRAT2_fmknodat                   mode_t
#define __NRAT3_fmknodat                   dev_t
#define __NRAT4_fmknodat                   atflag_t
#define __NRAT0_futimesat64                fd_t
#define __NRAT1_futimesat64                const char *
#define __NRAT2_futimesat64                /*[2-3]*/struct __timeval64 const *
#define __NRAT0_kfstatat                   fd_t
#define __NRAT1_kfstatat                   char const *
#define __NRAT2_kfstatat                   struct stat *
#define __NRAT3_kfstatat                   atflag_t
#define __NRAT0_frenameat                  fd_t
#define __NRAT1_frenameat                  char const *
#define __NRAT2_frenameat                  fd_t
#define __NRAT3_frenameat                  char const *
#define __NRAT4_frenameat                  atflag_t
#define __NRAT0_fsymlinkat                 char const *
#define __NRAT1_fsymlinkat                 fd_t
#define __NRAT2_fsymlinkat                 char const *
#define __NRAT3_fsymlinkat                 atflag_t
#define __NRAT0_freadlinkat                fd_t
#define __NRAT1_freadlinkat                char const *
#define __NRAT2_freadlinkat                char *
#define __NRAT3_freadlinkat                size_t
#define __NRAT4_freadlinkat                atflag_t
#define __NRAT0_pselect6_64                size_t
#define __NRAT1_pselect6_64                struct __fd_set_struct *
#define __NRAT2_pselect6_64                struct __fd_set_struct *
#define __NRAT3_pselect6_64                struct __fd_set_struct *
#define __NRAT4_pselect6_64                struct __timespec64 const *
#define __NRAT5_pselect6_64                void const *
#define __NRAT0_ppoll64                    struct pollfd *
#define __NRAT1_ppoll64                    size_t
#define __NRAT2_ppoll64                    struct __timespec64 const *
#define __NRAT3_ppoll64                    struct __sigset_struct const *
#define __NRAT4_ppoll64                    size_t
#define __NRAT0_utimensat64                fd_t
#define __NRAT1_utimensat64                char const *
#define __NRAT2_utimensat64                /*[2-3]*/struct __timespec64 const *
#define __NRAT3_utimensat64                atflag_t
#define __NRAT0_fallocate64                fd_t
#define __NRAT1_fallocate64                syscall_ulong_t
#define __NRAT2_fallocate64                uint64_t
#define __NRAT3_fallocate64                uint64_t
#define __NRAT0_timerfd_settime64          fd_t
#define __NRAT1_timerfd_settime64          syscall_ulong_t
#define __NRAT2_timerfd_settime64          struct __itimerspec64 const *
#define __NRAT3_timerfd_settime64          struct __itimerspec64 *
#define __NRAT0_timerfd_gettime64          fd_t
#define __NRAT1_timerfd_gettime64          struct __itimerspec64 *
#define __NRAT0_preadvf                    fd_t
#define __NRAT1_preadvf                    struct iovec const *
#define __NRAT2_preadvf                    size_t
#define __NRAT3_preadvf                    uint64_t
#define __NRAT4_preadvf                    iomode_t
#define __NRAT0_pwritevf                   fd_t
#define __NRAT1_pwritevf                   struct iovec const *
#define __NRAT2_pwritevf                   size_t
#define __NRAT3_pwritevf                   uint64_t
#define __NRAT4_pwritevf                   iomode_t
#define __NRAT0_recvmmsg64                 fd_t
#define __NRAT1_recvmmsg64                 struct mmsghdr *
#define __NRAT2_recvmmsg64                 size_t
#define __NRAT3_recvmmsg64                 syscall_ulong_t
#define __NRAT4_recvmmsg64                 struct __timespec64 *
#endif /* __WANT_SYSCALL_ARGUMENT_TYPES */

#ifdef __WANT_SYSCALL_ARGUMENT_NAMES
#define __NRAN0_exit                       "status"
#define __NRAN0_read                       "fd"
#define __NRAN1_read                       "buf"
#define __NRAN2_read                       "bufsize"
#define __NRAN0_write                      "fd"
#define __NRAN1_write                      "buf"
#define __NRAN2_write                      "bufsize"
#define __NRAN0_open                       "filename"
#define __NRAN1_open                       "oflags"
#define __NRAN2_open                       "mode"
#define __NRAN0_close                      "fd"
#define __NRAN0_waitpid                    "pid"
#define __NRAN1_waitpid                    "stat_loc"
#define __NRAN2_waitpid                    "options"
#define __NRAN0_creat                      "filename"
#define __NRAN1_creat                      "mode"
#define __NRAN0_link                       "existing_file"
#define __NRAN1_link                       "link_file"
#define __NRAN0_unlink                     "filename"
#define __NRAN0_execve                     "path"
#define __NRAN1_execve                     "argv"
#define __NRAN2_execve                     "envp"
#define __NRAN0_chdir                      "path"
#define __NRAN0_time                       "timer"
#define __NRAN0_mknod                      "nodename"
#define __NRAN1_mknod                      "mode"
#define __NRAN2_mknod                      "dev"
#define __NRAN0_chmod                      "filename"
#define __NRAN1_chmod                      "mode"
#define __NRAN0_lchown                     "filename"
#define __NRAN1_lchown                     "owner"
#define __NRAN2_lchown                     "group"
#define __NRAN0_linux_oldstat              "filename"
#define __NRAN1_linux_oldstat              "statbuf"
#define __NRAN0_lseek                      "fd"
#define __NRAN1_lseek                      "offset"
#define __NRAN2_lseek                      "whence"
#define __NRAN0_mount                      "special_file"
#define __NRAN1_mount                      "dir"
#define __NRAN2_mount                      "fstype"
#define __NRAN3_mount                      "rwflag"
#define __NRAN4_mount                      "data"
#define __NRAN0_umount                     "special_file"
#define __NRAN0_setuid                     "uid"
#define __NRAN0_stime                      "t"
#define __NRAN0_ptrace                     "request"
#define __NRAN1_ptrace                     "pid"
#define __NRAN2_ptrace                     "addr"
#define __NRAN3_ptrace                     "data"
#define __NRAN0_alarm                      "seconds"
#define __NRAN0_linux_oldfstat             "fd"
#define __NRAN1_linux_oldfstat             "statbuf"
#define __NRAN0_utime                      "filename"
#define __NRAN1_utime                      "times"
#define __NRAN0_access                     "filename"
#define __NRAN1_access                     "type"
#define __NRAN0_nice                       "inc"
#define __NRAN0_ftime                      "tp"
#define __NRAN0_kill                       "pid"
#define __NRAN1_kill                       "signo"
#define __NRAN0_rename                     "oldname"
#define __NRAN1_rename                     "newname_or_path"
#define __NRAN0_mkdir                      "pathname"
#define __NRAN1_mkdir                      "mode"
#define __NRAN0_rmdir                      "path"
#define __NRAN0_dup                        "fd"
#define __NRAN0_pipe                       "pipedes"
#define __NRAN0_times                      "buf"
#define __NRAN0_brk                        "addr"
#define __NRAN0_setgid                     "gid"
#define __NRAN0_signal                     "signo"
#define __NRAN1_signal                     "handler"
#define __NRAN0_acct                       "filename"
#define __NRAN0_umount2                    "special_file"
#define __NRAN1_umount2                    "flags"
#define __NRAN0_ioctl                      "fd"
#define __NRAN1_ioctl                      "request"
#define __NRAN2_ioctl                      "arg"
#define __NRAN0_fcntl                      "fd"
#define __NRAN1_fcntl                      "cmd"
#define __NRAN2_fcntl                      "arg"
#define __NRAN0_setpgid                    "pid"
#define __NRAN1_setpgid                    "pgid"
#define __NRAN0_oldolduname                "name"
#define __NRAN0_umask                      "mode"
#define __NRAN0_chroot                     "path"
#define __NRAN0_ustat                      "dev"
#define __NRAN1_ustat                      "ubuf"
#define __NRAN0_dup2                       "oldfd"
#define __NRAN1_dup2                       "newfd"
#define __NRAN0_sigaction                  "signo"
#define __NRAN1_sigaction                  "act"
#define __NRAN2_sigaction                  "oact"
#define __NRAN0_ssetmask                   "sigmask"
#define __NRAN0_setreuid                   "ruid"
#define __NRAN1_setreuid                   "euid"
#define __NRAN0_setregid                   "rgid"
#define __NRAN1_setregid                   "egid"
#define __NRAN0_sigsuspend                 "set"
#define __NRAN0_sigpending                 "set"
#define __NRAN0_sethostname                "name"
#define __NRAN1_sethostname                "len"
#define __NRAN0_setrlimit                  "resource"
#define __NRAN1_setrlimit                  "rlimits"
#define __NRAN0_getrlimit                  "resource"
#define __NRAN1_getrlimit                  "rlimits"
#define __NRAN0_getrusage                  "who"
#define __NRAN1_getrusage                  "usage"
#define __NRAN0_gettimeofday               "tv"
#define __NRAN1_gettimeofday               "tz"
#define __NRAN0_settimeofday               "tv"
#define __NRAN1_settimeofday               "tz"
#define __NRAN0_getgroups                  "size"
#define __NRAN1_getgroups                  "list"
#define __NRAN0_setgroups                  "count"
#define __NRAN1_setgroups                  "groups"
#define __NRAN0_select                     "nfds"
#define __NRAN1_select                     "readfds"
#define __NRAN2_select                     "writefds"
#define __NRAN3_select                     "exceptfds"
#define __NRAN4_select                     "timeout"
#define __NRAN0_symlink                    "link_text"
#define __NRAN1_symlink                    "target_path"
#define __NRAN0_linux_oldlstat             "filename"
#define __NRAN1_linux_oldlstat             "statbuf"
#define __NRAN0_readlink                   "path"
#define __NRAN1_readlink                   "buf"
#define __NRAN2_readlink                   "buflen"
#define __NRAN0_swapon                     "pathname"
#define __NRAN1_swapon                     "swapflags"
#define __NRAN0_reboot                     "how"
#define __NRAN0_readdir                    "fd"
#define __NRAN1_readdir                    "dirp"
#define __NRAN2_readdir                    "count"
#define __NRAN0_mmap                       "addr"
#define __NRAN1_mmap                       "len"
#define __NRAN2_mmap                       "prot"
#define __NRAN3_mmap                       "flags"
#define __NRAN4_mmap                       "fd"
#define __NRAN5_mmap                       "offset"
#define __NRAN0_munmap                     "addr"
#define __NRAN1_munmap                     "len"
#define __NRAN0_truncate                   "filename"
#define __NRAN1_truncate                   "length"
#define __NRAN0_ftruncate                  "fd"
#define __NRAN1_ftruncate                  "length"
#define __NRAN0_fchmod                     "fd"
#define __NRAN1_fchmod                     "mode"
#define __NRAN0_fchown                     "fd"
#define __NRAN1_fchown                     "owner"
#define __NRAN2_fchown                     "group"
#define __NRAN0_getpriority                "which"
#define __NRAN1_getpriority                "who"
#define __NRAN0_setpriority                "which"
#define __NRAN1_setpriority                "who"
#define __NRAN2_setpriority                "value"
#define __NRAN0_profil                     "sample_buffer"
#define __NRAN1_profil                     "size"
#define __NRAN2_profil                     "offset"
#define __NRAN3_profil                     "scale"
#define __NRAN0_statfs                     "file"
#define __NRAN1_statfs                     "buf"
#define __NRAN0_fstatfs                    "file"
#define __NRAN1_fstatfs                    "buf"
#define __NRAN0_ioperm                     "from"
#define __NRAN1_ioperm                     "num"
#define __NRAN2_ioperm                     "turn_on"
#define __NRAN0_socketcall                 "call"
#define __NRAN1_socketcall                 "args"
#define __NRAN0_syslog                     "level"
#define __NRAN1_syslog                     "str"
#define __NRAN2_syslog                     "len"
#define __NRAN0_setitimer                  "which"
#define __NRAN1_setitimer                  "newval"
#define __NRAN2_setitimer                  "oldval"
#define __NRAN0_getitimer                  "which"
#define __NRAN1_getitimer                  "curr_value"
#define __NRAN0_linux_stat32               "filename"
#define __NRAN1_linux_stat32               "statbuf"
#define __NRAN0_linux_lstat32              "filename"
#define __NRAN1_linux_lstat32              "statbuf"
#define __NRAN0_linux_fstat32              "fd"
#define __NRAN1_linux_fstat32              "statbuf"
#define __NRAN0_olduname                   "name"
#define __NRAN0_iopl                       "level"
#define __NRAN0_wait4                      "pid"
#define __NRAN1_wait4                      "stat_loc"
#define __NRAN2_wait4                      "options"
#define __NRAN3_wait4                      "usage"
#define __NRAN0_swapoff                    "pathname"
#define __NRAN0_sysinfo                    "info"
#define __NRAN0_fsync                      "fd"
#define __NRAN0_sigreturn                  "restore_fpu"
#define __NRAN1_sigreturn                  "unused1"
#define __NRAN2_sigreturn                  "unused2"
#define __NRAN3_sigreturn                  "restore_sigmask"
#define __NRAN4_sigreturn                  "sc_info"
#define __NRAN5_sigreturn                  "restore_cpu"
#define __NRAN0_clone                      "flags"
#define __NRAN1_clone                      "child_stack"
#define __NRAN2_clone                      "ptid"
#define __NRAN3_clone                      "newtls"
#define __NRAN4_clone                      "ctid"
#define __NRAN0_setdomainname              "name"
#define __NRAN1_setdomainname              "len"
#define __NRAN0_uname                      "name"
#define __NRAN0_modify_ldt                 "func"
#define __NRAN1_modify_ldt                 "ptr"
#define __NRAN2_modify_ldt                 "bytecount"
#define __NRAN0_mprotect                   "addr"
#define __NRAN1_mprotect                   "len"
#define __NRAN2_mprotect                   "prot"
#define __NRAN0_sigprocmask                "how"
#define __NRAN1_sigprocmask                "set"
#define __NRAN2_sigprocmask                "oset"
#define __NRAN0_getpgid                    "pid"
#define __NRAN0_fchdir                     "fd"
#define __NRAN0_setfsuid                   "uid"
#define __NRAN0_setfsgid                   "gid"
#define __NRAN0__llseek                    "fd"
#define __NRAN1__llseek                    "offset"
#define __NRAN2__llseek                    "result"
#define __NRAN3__llseek                    "whence"
#define __NRAN0_getdents                   "fd"
#define __NRAN1_getdents                   "dirp"
#define __NRAN2_getdents                   "count"
#define __NRAN0_flock                      "fd"
#define __NRAN1_flock                      "operation"
#define __NRAN0_msync                      "addr"
#define __NRAN1_msync                      "len"
#define __NRAN2_msync                      "flags"
#define __NRAN0_readv                      "fd"
#define __NRAN1_readv                      "iovec"
#define __NRAN2_readv                      "count"
#define __NRAN0_writev                     "fd"
#define __NRAN1_writev                     "iovec"
#define __NRAN2_writev                     "count"
#define __NRAN0_getsid                     "pid"
#define __NRAN0_fdatasync                  "fd"
#define __NRAN0_mlock                      "addr"
#define __NRAN1_mlock                      "len"
#define __NRAN0_munlock                    "addr"
#define __NRAN1_munlock                    "len"
#define __NRAN0_mlockall                   "flags"
#define __NRAN0_sched_setparam             "pid"
#define __NRAN1_sched_setparam             "param"
#define __NRAN0_sched_getparam             "pid"
#define __NRAN1_sched_getparam             "param"
#define __NRAN0_sched_setscheduler         "pid"
#define __NRAN1_sched_setscheduler         "policy"
#define __NRAN2_sched_setscheduler         "param"
#define __NRAN0_sched_getscheduler         "pid"
#define __NRAN0_sched_get_priority_max     "algorithm"
#define __NRAN0_sched_get_priority_min     "algorithm"
#define __NRAN0_sched_rr_get_interval      "pid"
#define __NRAN1_sched_rr_get_interval      "tms"
#define __NRAN0_nanosleep                  "req"
#define __NRAN1_nanosleep                  "rem"
#define __NRAN0_mremap                     "addr"
#define __NRAN1_mremap                     "old_len"
#define __NRAN2_mremap                     "new_len"
#define __NRAN3_mremap                     "flags"
#define __NRAN4_mremap                     "new_address"
#define __NRAN0_setresuid                  "ruid"
#define __NRAN1_setresuid                  "euid"
#define __NRAN2_setresuid                  "suid"
#define __NRAN0_getresuid                  "ruid"
#define __NRAN1_getresuid                  "euid"
#define __NRAN2_getresuid                  "suid"
#define __NRAN0_poll                       "fds"
#define __NRAN1_poll                       "nfds"
#define __NRAN2_poll                       "timeout"
#define __NRAN0_setresgid                  "rgid"
#define __NRAN1_setresgid                  "egid"
#define __NRAN2_setresgid                  "sgid"
#define __NRAN0_getresgid                  "rgid"
#define __NRAN1_getresgid                  "egid"
#define __NRAN2_getresgid                  "sgid"
#define __NRAN0_rt_sigaction               "signo"
#define __NRAN1_rt_sigaction               "act"
#define __NRAN2_rt_sigaction               "oact"
#define __NRAN3_rt_sigaction               "sigsetsize"
#define __NRAN0_rt_sigprocmask             "how"
#define __NRAN1_rt_sigprocmask             "set"
#define __NRAN2_rt_sigprocmask             "oset"
#define __NRAN3_rt_sigprocmask             "sigsetsize"
#define __NRAN0_rt_sigpending              "set"
#define __NRAN1_rt_sigpending              "sigsetsize"
#define __NRAN0_rt_sigtimedwait            "set"
#define __NRAN1_rt_sigtimedwait            "info"
#define __NRAN2_rt_sigtimedwait            "timeout"
#define __NRAN3_rt_sigtimedwait            "sigsetsize"
#define __NRAN0_rt_sigqueueinfo            "tgid"
#define __NRAN1_rt_sigqueueinfo            "signo"
#define __NRAN2_rt_sigqueueinfo            "uinfo"
#define __NRAN0_rt_sigsuspend              "set"
#define __NRAN1_rt_sigsuspend              "sigsetsize"
#define __NRAN0_pread64                    "fd"
#define __NRAN1_pread64                    "buf"
#define __NRAN2_pread64                    "bufsize"
#define __NRAN3_pread64                    "offset"
#define __NRAN0_pwrite64                   "fd"
#define __NRAN1_pwrite64                   "buf"
#define __NRAN2_pwrite64                   "bufsize"
#define __NRAN3_pwrite64                   "offset"
#define __NRAN0_chown                      "filename"
#define __NRAN1_chown                      "owner"
#define __NRAN2_chown                      "group"
#define __NRAN0_getcwd                     "buf"
#define __NRAN1_getcwd                     "size"
#define __NRAN0_sigaltstack                "ss"
#define __NRAN1_sigaltstack                "oss"
#define __NRAN0_sendfile                   "out_fd"
#define __NRAN1_sendfile                   "in_fd"
#define __NRAN2_sendfile                   "offset"
#define __NRAN3_sendfile                   "count"
#define __NRAN0_mmap2                      "addr"
#define __NRAN1_mmap2                      "len"
#define __NRAN2_mmap2                      "prot"
#define __NRAN3_mmap2                      "flags"
#define __NRAN4_mmap2                      "fd"
#define __NRAN5_mmap2                      "pgoffset"
#define __NRAN0_truncate64                 "filename"
#define __NRAN1_truncate64                 "length"
#define __NRAN0_ftruncate64                "fd"
#define __NRAN1_ftruncate64                "length"
#define __NRAN0_linux_stat64               "filename"
#define __NRAN1_linux_stat64               "statbuf"
#define __NRAN0_linux_lstat64              "filename"
#define __NRAN1_linux_lstat64              "statbuf"
#define __NRAN0_linux_fstat64              "fd"
#define __NRAN1_linux_fstat64              "statbuf"
#define __NRAN0_lchown32                   "filename"
#define __NRAN1_lchown32                   "owner"
#define __NRAN2_lchown32                   "group"
#define __NRAN0_setreuid32                 "ruid"
#define __NRAN1_setreuid32                 "euid"
#define __NRAN0_setregid32                 "rgid"
#define __NRAN1_setregid32                 "egid"
#define __NRAN0_getgroups32                "size"
#define __NRAN1_getgroups32                "list"
#define __NRAN0_setgroups32                "count"
#define __NRAN1_setgroups32                "groups"
#define __NRAN0_fchown32                   "fd"
#define __NRAN1_fchown32                   "owner"
#define __NRAN2_fchown32                   "group"
#define __NRAN0_setresuid32                "ruid"
#define __NRAN1_setresuid32                "euid"
#define __NRAN2_setresuid32                "suid"
#define __NRAN0_getresuid32                "ruid"
#define __NRAN1_getresuid32                "euid"
#define __NRAN2_getresuid32                "suid"
#define __NRAN0_setresgid32                "rgid"
#define __NRAN1_setresgid32                "egid"
#define __NRAN2_setresgid32                "sgid"
#define __NRAN0_getresgid32                "rgid"
#define __NRAN1_getresgid32                "egid"
#define __NRAN2_getresgid32                "sgid"
#define __NRAN0_chown32                    "filename"
#define __NRAN1_chown32                    "owner"
#define __NRAN2_chown32                    "group"
#define __NRAN0_setuid32                   "uid"
#define __NRAN0_setgid32                   "gid"
#define __NRAN0_setfsuid32                 "uid"
#define __NRAN0_setfsgid32                 "gid"
#define __NRAN0_mincore                    "start"
#define __NRAN1_mincore                    "len"
#define __NRAN2_mincore                    "vec"
#define __NRAN0_madvise                    "addr"
#define __NRAN1_madvise                    "len"
#define __NRAN2_madvise                    "advice"
#define __NRAN0_getdents64                 "fd"
#define __NRAN1_getdents64                 "dirp"
#define __NRAN2_getdents64                 "count"
#define __NRAN0_fcntl64                    "fd"
#define __NRAN1_fcntl64                    "command"
#define __NRAN2_fcntl64                    "arg"
#define __NRAN0_readahead                  "fd"
#define __NRAN1_readahead                  "offset"
#define __NRAN2_readahead                  "count"
#define __NRAN0_setxattr                   "path"
#define __NRAN1_setxattr                   "name"
#define __NRAN2_setxattr                   "buf"
#define __NRAN3_setxattr                   "bufsize"
#define __NRAN4_setxattr                   "flags"
#define __NRAN0_lsetxattr                  "path"
#define __NRAN1_lsetxattr                  "name"
#define __NRAN2_lsetxattr                  "buf"
#define __NRAN3_lsetxattr                  "bufsize"
#define __NRAN4_lsetxattr                  "flags"
#define __NRAN0_fsetxattr                  "fd"
#define __NRAN1_fsetxattr                  "name"
#define __NRAN2_fsetxattr                  "buf"
#define __NRAN3_fsetxattr                  "bufsize"
#define __NRAN4_fsetxattr                  "flags"
#define __NRAN0_getxattr                   "path"
#define __NRAN1_getxattr                   "name"
#define __NRAN2_getxattr                   "buf"
#define __NRAN3_getxattr                   "bufsize"
#define __NRAN0_lgetxattr                  "path"
#define __NRAN1_lgetxattr                  "name"
#define __NRAN2_lgetxattr                  "buf"
#define __NRAN3_lgetxattr                  "bufsize"
#define __NRAN0_fgetxattr                  "fd"
#define __NRAN1_fgetxattr                  "name"
#define __NRAN2_fgetxattr                  "buf"
#define __NRAN3_fgetxattr                  "bufsize"
#define __NRAN0_listxattr                  "path"
#define __NRAN1_listxattr                  "listbuf"
#define __NRAN2_listxattr                  "listbufsize"
#define __NRAN0_llistxattr                 "path"
#define __NRAN1_llistxattr                 "listbuf"
#define __NRAN2_llistxattr                 "listbufsize"
#define __NRAN0_flistxattr                 "fd"
#define __NRAN1_flistxattr                 "listbuf"
#define __NRAN2_flistxattr                 "listbufsize"
#define __NRAN0_removexattr                "path"
#define __NRAN1_removexattr                "name"
#define __NRAN0_lremovexattr               "path"
#define __NRAN1_lremovexattr               "name"
#define __NRAN0_fremovexattr               "fd"
#define __NRAN1_fremovexattr               "name"
#define __NRAN0_tkill                      "tid"
#define __NRAN1_tkill                      "signo"
#define __NRAN0_sendfile64                 "out_fd"
#define __NRAN1_sendfile64                 "in_fd"
#define __NRAN2_sendfile64                 "offset"
#define __NRAN3_sendfile64                 "count"
#define __NRAN0_futex                      "uaddr"
#define __NRAN1_futex                      "futex_op"
#define __NRAN2_futex                      "val"
#define __NRAN3_futex                      "timeout_or_val2"
#define __NRAN4_futex                      "uaddr2"
#define __NRAN5_futex                      "val3"
#define __NRAN0_sched_setaffinity          "pid"
#define __NRAN1_sched_setaffinity          "cpusetsize"
#define __NRAN2_sched_setaffinity          "cpuset"
#define __NRAN0_sched_getaffinity          "pid"
#define __NRAN1_sched_getaffinity          "cpusetsize"
#define __NRAN2_sched_getaffinity          "cpuset"
#define __NRAN0_exit_group                 "exit_code"
#define __NRAN0_epoll_create               "size"
#define __NRAN0_epoll_ctl                  "epfd"
#define __NRAN1_epoll_ctl                  "op"
#define __NRAN2_epoll_ctl                  "fd"
#define __NRAN3_epoll_ctl                  "event"
#define __NRAN0_epoll_wait                 "epfd"
#define __NRAN1_epoll_wait                 "events"
#define __NRAN2_epoll_wait                 "maxevents"
#define __NRAN3_epoll_wait                 "timeout"
#define __NRAN0_remap_file_pages           "start"
#define __NRAN1_remap_file_pages           "size"
#define __NRAN2_remap_file_pages           "prot"
#define __NRAN3_remap_file_pages           "pgoff"
#define __NRAN4_remap_file_pages           "flags"
#define __NRAN0_set_tid_address            "tidptr"
#define __NRAN0_timer_create               "clock_id"
#define __NRAN1_timer_create               "evp"
#define __NRAN2_timer_create               "timerid"
#define __NRAN0_timer_settime              "timerid"
#define __NRAN1_timer_settime              "flags"
#define __NRAN2_timer_settime              "value"
#define __NRAN3_timer_settime              "ovalue"
#define __NRAN0_timer_gettime              "timerid"
#define __NRAN1_timer_gettime              "value"
#define __NRAN0_timer_getoverrun           "timerid"
#define __NRAN0_timer_delete               "timerid"
#define __NRAN0_clock_settime              "clock_id"
#define __NRAN1_clock_settime              "tp"
#define __NRAN0_clock_gettime              "clock_id"
#define __NRAN1_clock_gettime              "tp"
#define __NRAN0_clock_getres               "clock_id"
#define __NRAN1_clock_getres               "res"
#define __NRAN0_clock_nanosleep            "clock_id"
#define __NRAN1_clock_nanosleep            "flags"
#define __NRAN2_clock_nanosleep            "requested_time"
#define __NRAN3_clock_nanosleep            "remaining"
#define __NRAN0_statfs64                   "file"
#define __NRAN1_statfs64                   "buf"
#define __NRAN0_fstatfs64                  "file"
#define __NRAN1_fstatfs64                  "buf"
#define __NRAN0_tgkill                     "tgid"
#define __NRAN1_tgkill                     "tid"
#define __NRAN2_tgkill                     "signo"
#define __NRAN0_utimes                     "filename"
#define __NRAN1_utimes                     "times"
#define __NRAN0_waitid                     "idtype"
#define __NRAN1_waitid                     "id"
#define __NRAN2_waitid                     "infop"
#define __NRAN3_waitid                     "options"
#define __NRAN4_waitid                     "ru"
#define __NRAN0_ioprio_set                 "which"
#define __NRAN1_ioprio_set                 "who"
#define __NRAN2_ioprio_set                 "ioprio"
#define __NRAN0_ioprio_get                 "which"
#define __NRAN1_ioprio_get                 "who"
#define __NRAN0_openat                     "dirfd"
#define __NRAN1_openat                     "filename"
#define __NRAN2_openat                     "oflags"
#define __NRAN3_openat                     "mode"
#define __NRAN0_mkdirat                    "dirfd"
#define __NRAN1_mkdirat                    "pathname"
#define __NRAN2_mkdirat                    "mode"
#define __NRAN0_mknodat                    "dirfd"
#define __NRAN1_mknodat                    "nodename"
#define __NRAN2_mknodat                    "mode"
#define __NRAN3_mknodat                    "dev"
#define __NRAN0_fchownat                   "dirfd"
#define __NRAN1_fchownat                   "filename"
#define __NRAN2_fchownat                   "owner"
#define __NRAN3_fchownat                   "group"
#define __NRAN4_fchownat                   "flags"
#define __NRAN0_futimesat                  "dirfd"
#define __NRAN1_futimesat                  "filename"
#define __NRAN2_futimesat                  "times"
#define __NRAN0_linux_fstatat64            "dirfd"
#define __NRAN1_linux_fstatat64            "filename"
#define __NRAN2_linux_fstatat64            "statbuf"
#define __NRAN3_linux_fstatat64            "flags"
#define __NRAN0_unlinkat                   "dirfd"
#define __NRAN1_unlinkat                   "name"
#define __NRAN2_unlinkat                   "flags"
#define __NRAN0_renameat                   "oldfd"
#define __NRAN1_renameat                   "oldname"
#define __NRAN2_renameat                   "newfd"
#define __NRAN3_renameat                   "newname_or_path"
#define __NRAN0_linkat                     "fromfd"
#define __NRAN1_linkat                     "existing_file"
#define __NRAN2_linkat                     "tofd"
#define __NRAN3_linkat                     "target_path"
#define __NRAN4_linkat                     "flags"
#define __NRAN0_symlinkat                  "link_text"
#define __NRAN1_symlinkat                  "tofd"
#define __NRAN2_symlinkat                  "target_path"
#define __NRAN0_readlinkat                 "dirfd"
#define __NRAN1_readlinkat                 "path"
#define __NRAN2_readlinkat                 "buf"
#define __NRAN3_readlinkat                 "buflen"
#define __NRAN0_fchmodat                   "dirfd"
#define __NRAN1_fchmodat                   "filename"
#define __NRAN2_fchmodat                   "mode"
#define __NRAN3_fchmodat                   "flags"
#define __NRAN0_faccessat                  "dirfd"
#define __NRAN1_faccessat                  "filename"
#define __NRAN2_faccessat                  "type"
#define __NRAN3_faccessat                  "flags"
#define __NRAN0_pselect6                   "nfds"
#define __NRAN1_pselect6                   "readfds"
#define __NRAN2_pselect6                   "writefds"
#define __NRAN3_pselect6                   "exceptfds"
#define __NRAN4_pselect6                   "timeout"
#define __NRAN5_pselect6                   "sigmask_sigset_and_len"
#define __NRAN0_ppoll                      "fds"
#define __NRAN1_ppoll                      "nfds"
#define __NRAN2_ppoll                      "timeout_ts"
#define __NRAN3_ppoll                      "sigmask"
#define __NRAN4_ppoll                      "sigsetsize"
#define __NRAN0_unshare                    "flags"
#define __NRAN0_splice                     "fdin"
#define __NRAN1_splice                     "offin"
#define __NRAN2_splice                     "fdout"
#define __NRAN3_splice                     "offout"
#define __NRAN4_splice                     "length"
#define __NRAN5_splice                     "flags"
#define __NRAN0_sync_file_range            "fd"
#define __NRAN1_sync_file_range            "offset"
#define __NRAN2_sync_file_range            "count"
#define __NRAN3_sync_file_range            "flags"
#define __NRAN0_tee                        "fdin"
#define __NRAN1_tee                        "fdout"
#define __NRAN2_tee                        "length"
#define __NRAN3_tee                        "flags"
#define __NRAN0_vmsplice                   "fdout"
#define __NRAN1_vmsplice                   "iov"
#define __NRAN2_vmsplice                   "count"
#define __NRAN3_vmsplice                   "flags"
#define __NRAN0_getcpu                     "cpu"
#define __NRAN1_getcpu                     "node"
#define __NRAN2_getcpu                     "tcache"
#define __NRAN0_epoll_pwait                "epfd"
#define __NRAN1_epoll_pwait                "events"
#define __NRAN2_epoll_pwait                "maxevents"
#define __NRAN3_epoll_pwait                "timeout"
#define __NRAN4_epoll_pwait                "ss"
#define __NRAN0_utimensat                  "dirfd"
#define __NRAN1_utimensat                  "filename"
#define __NRAN2_utimensat                  "times"
#define __NRAN3_utimensat                  "flags"
#define __NRAN0_timerfd_create             "clock_id"
#define __NRAN1_timerfd_create             "flags"
#define __NRAN0_eventfd                    "initval"
#define __NRAN0_fallocate                  "fd"
#define __NRAN1_fallocate                  "mode"
#define __NRAN2_fallocate                  "offset"
#define __NRAN3_fallocate                  "length"
#define __NRAN0_timerfd_settime            "ufd"
#define __NRAN1_timerfd_settime            "flags"
#define __NRAN2_timerfd_settime            "utmr"
#define __NRAN3_timerfd_settime            "otmr"
#define __NRAN0_timerfd_gettime            "ufd"
#define __NRAN1_timerfd_gettime            "otmr"
#define __NRAN0_eventfd2                   "initval"
#define __NRAN1_eventfd2                   "flags"
#define __NRAN0_epoll_create1              "flags"
#define __NRAN0_dup3                       "oldfd"
#define __NRAN1_dup3                       "newfd"
#define __NRAN2_dup3                       "flags"
#define __NRAN0_pipe2                      "pipedes"
#define __NRAN1_pipe2                      "flags"
#define __NRAN0_preadv                     "fd"
#define __NRAN1_preadv                     "iovec"
#define __NRAN2_preadv                     "count"
#define __NRAN3_preadv                     "offset"
#define __NRAN0_pwritev                    "fd"
#define __NRAN1_pwritev                    "iovec"
#define __NRAN2_pwritev                    "count"
#define __NRAN3_pwritev                    "offset"
#define __NRAN0_rt_tgsigqueueinfo          "tgid"
#define __NRAN1_rt_tgsigqueueinfo          "tid"
#define __NRAN2_rt_tgsigqueueinfo          "signo"
#define __NRAN3_rt_tgsigqueueinfo          "uinfo"
#define __NRAN0_recvmmsg                   "sockfd"
#define __NRAN1_recvmmsg                   "vmessages"
#define __NRAN2_recvmmsg                   "vlen"
#define __NRAN3_recvmmsg                   "flags"
#define __NRAN4_recvmmsg                   "tmo"
#define __NRAN0_prlimit64                  "pid"
#define __NRAN1_prlimit64                  "resource"
#define __NRAN2_prlimit64                  "new_limit"
#define __NRAN3_prlimit64                  "old_limit"
#define __NRAN0_name_to_handle_at          "dirfd"
#define __NRAN1_name_to_handle_at          "name"
#define __NRAN2_name_to_handle_at          "handle"
#define __NRAN3_name_to_handle_at          "mnt_id"
#define __NRAN4_name_to_handle_at          "flags"
#define __NRAN0_open_by_handle_at          "mountdirfd"
#define __NRAN1_open_by_handle_at          "handle"
#define __NRAN2_open_by_handle_at          "flags"
#define __NRAN0_syncfs                     "fd"
#define __NRAN0_sendmmsg                   "sockfd"
#define __NRAN1_sendmmsg                   "vmessages"
#define __NRAN2_sendmmsg                   "vlen"
#define __NRAN3_sendmmsg                   "flags"
#define __NRAN0_setns                      "fd"
#define __NRAN1_setns                      "nstype"
#define __NRAN0_process_vm_readv           "pid"
#define __NRAN1_process_vm_readv           "lvec"
#define __NRAN2_process_vm_readv           "liovcnt"
#define __NRAN3_process_vm_readv           "rvec"
#define __NRAN4_process_vm_readv           "riovcnt"
#define __NRAN5_process_vm_readv           "flags"
#define __NRAN0_process_vm_writev          "pid"
#define __NRAN1_process_vm_writev          "lvec"
#define __NRAN2_process_vm_writev          "liovcnt"
#define __NRAN3_process_vm_writev          "rvec"
#define __NRAN4_process_vm_writev          "riovcnt"
#define __NRAN5_process_vm_writev          "flags"
#define __NRAN0_kcmp                       "pid1"
#define __NRAN1_kcmp                       "pid2"
#define __NRAN2_kcmp                       "type"
#define __NRAN3_kcmp                       "idx1"
#define __NRAN4_kcmp                       "idx2"
#define __NRAN0_renameat2                  "olddirfd"
#define __NRAN1_renameat2                  "oldpath"
#define __NRAN2_renameat2                  "newdirfd"
#define __NRAN3_renameat2                  "newpath"
#define __NRAN4_renameat2                  "flags"
#define __NRAN0_execveat                   "dirfd"
#define __NRAN1_execveat                   "pathname"
#define __NRAN2_execveat                   "argv"
#define __NRAN3_execveat                   "envp"
#define __NRAN4_execveat                   "flags"
#define __NRAN0_socket                     "domain"
#define __NRAN1_socket                     "type"
#define __NRAN2_socket                     "protocol"
#define __NRAN0_socketpair                 "domain"
#define __NRAN1_socketpair                 "type"
#define __NRAN2_socketpair                 "protocol"
#define __NRAN3_socketpair                 "fds"
#define __NRAN0_bind                       "sockfd"
#define __NRAN1_bind                       "addr"
#define __NRAN2_bind                       "addr_len"
#define __NRAN0_connect                    "sockfd"
#define __NRAN1_connect                    "addr"
#define __NRAN2_connect                    "addr_len"
#define __NRAN0_listen                     "sockfd"
#define __NRAN1_listen                     "max_backlog"
#define __NRAN0_accept4                    "sockfd"
#define __NRAN1_accept4                    "addr"
#define __NRAN2_accept4                    "addr_len"
#define __NRAN3_accept4                    "flags"
#define __NRAN0_getsockopt                 "sockfd"
#define __NRAN1_getsockopt                 "level"
#define __NRAN2_getsockopt                 "optname"
#define __NRAN3_getsockopt                 "optval"
#define __NRAN4_getsockopt                 "optlen"
#define __NRAN0_setsockopt                 "sockfd"
#define __NRAN1_setsockopt                 "level"
#define __NRAN2_setsockopt                 "optname"
#define __NRAN3_setsockopt                 "optval"
#define __NRAN4_setsockopt                 "optlen"
#define __NRAN0_getsockname                "sockfd"
#define __NRAN1_getsockname                "addr"
#define __NRAN2_getsockname                "addr_len"
#define __NRAN0_getpeername                "sockfd"
#define __NRAN1_getpeername                "addr"
#define __NRAN2_getpeername                "addr_len"
#define __NRAN0_sendto                     "sockfd"
#define __NRAN1_sendto                     "buf"
#define __NRAN2_sendto                     "bufsize"
#define __NRAN3_sendto                     "flags"
#define __NRAN4_sendto                     "addr"
#define __NRAN5_sendto                     "addr_len"
#define __NRAN0_sendmsg                    "sockfd"
#define __NRAN1_sendmsg                    "message"
#define __NRAN2_sendmsg                    "flags"
#define __NRAN0_recvfrom                   "sockfd"
#define __NRAN1_recvfrom                   "buf"
#define __NRAN2_recvfrom                   "bufsize"
#define __NRAN3_recvfrom                   "flags"
#define __NRAN4_recvfrom                   "addr"
#define __NRAN5_recvfrom                   "addr_len"
#define __NRAN0_recvmsg                    "sockfd"
#define __NRAN1_recvmsg                    "message"
#define __NRAN2_recvmsg                    "flags"
#define __NRAN0_shutdown                   "sockfd"
#define __NRAN1_shutdown                   "how"
#define __NRAN0_hop                        "fd"
#define __NRAN1_hop                        "command"
#define __NRAN2_hop                        "arg"
#define __NRAN0_hopf                       "fd"
#define __NRAN1_hopf                       "command"
#define __NRAN2_hopf                       "mode"
#define __NRAN3_hopf                       "arg"
#define __NRAN0_readf                      "fd"
#define __NRAN1_readf                      "buf"
#define __NRAN2_readf                      "bufsize"
#define __NRAN3_readf                      "mode"
#define __NRAN0_writef                     "fd"
#define __NRAN1_writef                     "buf"
#define __NRAN2_writef                     "bufsize"
#define __NRAN3_writef                     "mode"
#define __NRAN0_detach                     "pid"
#define __NRAN0_frealpath4                 "fd"
#define __NRAN1_frealpath4                 "buf"
#define __NRAN2_frealpath4                 "buflen"
#define __NRAN3_frealpath4                 "flags"
#define __NRAN0_frealpathat                "dirfd"
#define __NRAN1_frealpathat                "filename"
#define __NRAN2_frealpathat                "buf"
#define __NRAN3_frealpathat                "buflen"
#define __NRAN4_frealpathat                "flags"
#define __NRAN0_rpc_schedule               "target"
#define __NRAN1_rpc_schedule               "flags"
#define __NRAN2_rpc_schedule               "program"
#define __NRAN3_rpc_schedule               "arguments"
#define __NRAN0_sysctl                     "command"
#define __NRAN1_sysctl                     "arg"
#define __NRAN0_openpty                    "amaster"
#define __NRAN1_openpty                    "aslave"
#define __NRAN2_openpty                    "name"
#define __NRAN3_openpty                    "termp"
#define __NRAN4_openpty                    "winp"
#define __NRAN0_fchdirat                   "dirfd"
#define __NRAN1_fchdirat                   "path"
#define __NRAN2_fchdirat                   "flags"
#define __NRAN0_time64                     "timer"
#define __NRAN0_set_exception_handler      "mode"
#define __NRAN1_set_exception_handler      "handler"
#define __NRAN2_set_exception_handler      "handler_sp"
#define __NRAN0_get_exception_handler      "pmode"
#define __NRAN1_get_exception_handler      "phandler"
#define __NRAN2_get_exception_handler      "phandler_sp"
#define __NRAN0_set_library_listdef        "listdef"
#define __NRAN0_debugtrap                  "state"
#define __NRAN1_debugtrap                  "trapno"
#define __NRAN2_debugtrap                  "regs"
#define __NRAN0_lfutex                     "uaddr"
#define __NRAN1_lfutex                     "futex_op"
#define __NRAN2_lfutex                     "val"
#define __NRAN3_lfutex                     "timeout"
#define __NRAN4_lfutex                     "val2"
#define __NRAN0_lseek64                    "fd"
#define __NRAN1_lseek64                    "offset"
#define __NRAN2_lseek64                    "whence"
#define __NRAN0_lfutexlock                 "ulockaddr"
#define __NRAN1_lfutexlock                 "uaddr"
#define __NRAN2_lfutexlock                 "futex_op"
#define __NRAN3_lfutexlock                 "val"
#define __NRAN4_lfutexlock                 "timeout"
#define __NRAN5_lfutexlock                 "val2"
#define __NRAN0_lfutexexpr                 "uaddr"
#define __NRAN1_lfutexexpr                 "base"
#define __NRAN2_lfutexexpr                 "exprv"
#define __NRAN3_lfutexexpr                 "exprc"
#define __NRAN4_lfutexexpr                 "timeout"
#define __NRAN5_lfutexexpr                 "timeout_flags"
#define __NRAN0_lfutexlockexpr             "ulockaddr"
#define __NRAN1_lfutexlockexpr             "base"
#define __NRAN2_lfutexlockexpr             "exprv"
#define __NRAN3_lfutexlockexpr             "exprc"
#define __NRAN4_lfutexlockexpr             "timeout"
#define __NRAN5_lfutexlockexpr             "timeout_flags"
#define __NRAN0_mktty                      "keyboard"
#define __NRAN1_mktty                      "display"
#define __NRAN2_mktty                      "name"
#define __NRAN3_mktty                      "rsvd"
#define __NRAN0_raiseat                    "state"
#define __NRAN1_raiseat                    "si"
#define __NRAN0_stime64                    "t"
#define __NRAN0_coredump                   "curr_state"
#define __NRAN1_coredump                   "orig_state"
#define __NRAN2_coredump                   "traceback_vector"
#define __NRAN3_coredump                   "traceback_length"
#define __NRAN4_coredump                   "exception"
#define __NRAN5_coredump                   "unwind_error"
#define __NRAN0_utime64                    "filename"
#define __NRAN1_utime64                    "times"
#define __NRAN0_ioctlf                     "fd"
#define __NRAN1_ioctlf                     "command"
#define __NRAN2_ioctlf                     "mode"
#define __NRAN3_ioctlf                     "arg"
#define __NRAN0_fsmode                     "mode"
#define __NRAN0_gettimeofday64             "tv"
#define __NRAN1_gettimeofday64             "tz"
#define __NRAN0_settimeofday64             "tv"
#define __NRAN1_settimeofday64             "tz"
#define __NRAN0_select64                   "nfds"
#define __NRAN1_select64                   "readfds"
#define __NRAN2_select64                   "writefds"
#define __NRAN3_select64                   "exceptfds"
#define __NRAN4_select64                   "timeout"
#define __NRAN0_maplibrary                 "addr"
#define __NRAN1_maplibrary                 "flags"
#define __NRAN2_maplibrary                 "fd"
#define __NRAN3_maplibrary                 "hdrv"
#define __NRAN4_maplibrary                 "hdrc"
#define __NRAN0_setitimer64                "which"
#define __NRAN1_setitimer64                "newval"
#define __NRAN2_setitimer64                "oldval"
#define __NRAN0_getitimer64                "which"
#define __NRAN1_getitimer64                "curr_value"
#define __NRAN0_kreaddir                   "fd"
#define __NRAN1_kreaddir                   "buf"
#define __NRAN2_kreaddir                   "bufsize"
#define __NRAN3_kreaddir                   "mode"
#define __NRAN0_readvf                     "fd"
#define __NRAN1_readvf                     "iovec"
#define __NRAN2_readvf                     "count"
#define __NRAN3_readvf                     "mode"
#define __NRAN0_writevf                    "fd"
#define __NRAN1_writevf                    "iovec"
#define __NRAN2_writevf                    "count"
#define __NRAN3_writevf                    "mode"
#define __NRAN0_sched_rr_get_interval64    "pid"
#define __NRAN1_sched_rr_get_interval64    "tms"
#define __NRAN0_nanosleep64                "req"
#define __NRAN1_nanosleep64                "rem"
#define __NRAN0_rt_sigtimedwait64          "set"
#define __NRAN1_rt_sigtimedwait64          "info"
#define __NRAN2_rt_sigtimedwait64          "timeout"
#define __NRAN3_rt_sigtimedwait64          "sigsetsize"
#define __NRAN0_pread64f                   "fd"
#define __NRAN1_pread64f                   "buf"
#define __NRAN2_pread64f                   "bufsize"
#define __NRAN3_pread64f                   "offset"
#define __NRAN4_pread64f                   "mode"
#define __NRAN0_pwrite64f                  "fd"
#define __NRAN1_pwrite64f                  "buf"
#define __NRAN2_pwrite64f                  "bufsize"
#define __NRAN3_pwrite64f                  "offset"
#define __NRAN4_pwrite64f                  "mode"
#define __NRAN0_kstat                      "filename"
#define __NRAN1_kstat                      "statbuf"
#define __NRAN0_klstat                     "filename"
#define __NRAN1_klstat                     "statbuf"
#define __NRAN0_kfstat                     "fd"
#define __NRAN1_kfstat                     "statbuf"
#define __NRAN0_kreaddirf                  "fd"
#define __NRAN1_kreaddirf                  "buf"
#define __NRAN2_kreaddirf                  "bufsize"
#define __NRAN3_kreaddirf                  "mode"
#define __NRAN4_kreaddirf                  "iomode"
#define __NRAN0_timer_settime64            "timerid"
#define __NRAN1_timer_settime64            "flags"
#define __NRAN2_timer_settime64            "value"
#define __NRAN3_timer_settime64            "ovalue"
#define __NRAN0_timer_gettime64            "timerid"
#define __NRAN1_timer_gettime64            "value"
#define __NRAN0_clock_settime64            "clock_id"
#define __NRAN1_clock_settime64            "tp"
#define __NRAN0_clock_gettime64            "clock_id"
#define __NRAN1_clock_gettime64            "tp"
#define __NRAN0_clock_getres64             "clock_id"
#define __NRAN1_clock_getres64             "res"
#define __NRAN0_clock_nanosleep64          "clock_id"
#define __NRAN1_clock_nanosleep64          "flags"
#define __NRAN2_clock_nanosleep64          "requested_time"
#define __NRAN3_clock_nanosleep64          "remaining"
#define __NRAN0_utimes64                   "filename"
#define __NRAN1_utimes64                   "times"
#define __NRAN0_fmkdirat                   "dirfd"
#define __NRAN1_fmkdirat                   "pathname"
#define __NRAN2_fmkdirat                   "mode"
#define __NRAN3_fmkdirat                   "flags"
#define __NRAN0_fmknodat                   "dirfd"
#define __NRAN1_fmknodat                   "nodename"
#define __NRAN2_fmknodat                   "mode"
#define __NRAN3_fmknodat                   "dev"
#define __NRAN4_fmknodat                   "flags"
#define __NRAN0_futimesat64                "dirfd"
#define __NRAN1_futimesat64                "filename"
#define __NRAN2_futimesat64                "times"
#define __NRAN0_kfstatat                   "dirfd"
#define __NRAN1_kfstatat                   "filename"
#define __NRAN2_kfstatat                   "statbuf"
#define __NRAN3_kfstatat                   "flags"
#define __NRAN0_frenameat                  "oldfd"
#define __NRAN1_frenameat                  "oldname"
#define __NRAN2_frenameat                  "newfd"
#define __NRAN3_frenameat                  "newname_or_path"
#define __NRAN4_frenameat                  "flags"
#define __NRAN0_fsymlinkat                 "link_text"
#define __NRAN1_fsymlinkat                 "tofd"
#define __NRAN2_fsymlinkat                 "target_path"
#define __NRAN3_fsymlinkat                 "flags"
#define __NRAN0_freadlinkat                "dirfd"
#define __NRAN1_freadlinkat                "path"
#define __NRAN2_freadlinkat                "buf"
#define __NRAN3_freadlinkat                "buflen"
#define __NRAN4_freadlinkat                "flags"
#define __NRAN0_pselect6_64                "nfds"
#define __NRAN1_pselect6_64                "readfds"
#define __NRAN2_pselect6_64                "writefds"
#define __NRAN3_pselect6_64                "exceptfds"
#define __NRAN4_pselect6_64                "timeout"
#define __NRAN5_pselect6_64                "sigmask_sigset_and_len"
#define __NRAN0_ppoll64                    "fds"
#define __NRAN1_ppoll64                    "nfds"
#define __NRAN2_ppoll64                    "timeout_ts"
#define __NRAN3_ppoll64                    "sigmask"
#define __NRAN4_ppoll64                    "sigsetsize"
#define __NRAN0_utimensat64                "dirfd"
#define __NRAN1_utimensat64                "filename"
#define __NRAN2_utimensat64                "times"
#define __NRAN3_utimensat64                "flags"
#define __NRAN0_fallocate64                "fd"
#define __NRAN1_fallocate64                "mode"
#define __NRAN2_fallocate64                "offset"
#define __NRAN3_fallocate64                "length"
#define __NRAN0_timerfd_settime64          "ufd"
#define __NRAN1_timerfd_settime64          "flags"
#define __NRAN2_timerfd_settime64          "utmr"
#define __NRAN3_timerfd_settime64          "otmr"
#define __NRAN0_timerfd_gettime64          "ufd"
#define __NRAN1_timerfd_gettime64          "otmr"
#define __NRAN0_preadvf                    "fd"
#define __NRAN1_preadvf                    "iovec"
#define __NRAN2_preadvf                    "count"
#define __NRAN3_preadvf                    "offset"
#define __NRAN4_preadvf                    "mode"
#define __NRAN0_pwritevf                   "fd"
#define __NRAN1_pwritevf                   "iovec"
#define __NRAN2_pwritevf                   "count"
#define __NRAN3_pwritevf                   "offset"
#define __NRAN4_pwritevf                   "mode"
#define __NRAN0_recvmmsg64                 "sockfd"
#define __NRAN1_recvmmsg64                 "vmessages"
#define __NRAN2_recvmmsg64                 "vlen"
#define __NRAN3_recvmmsg64                 "flags"
#define __NRAN4_recvmmsg64                 "tmo"
#endif /* __WANT_SYSCALL_ARGUMENT_NAMES */

#ifdef __WANT_SYSCALL_ARGUMENT_FORMAT
#define __NRATRF0_exit                       "%Iu"
#define __NRATRA0_exit(status)               ,(uintptr_t)(status)
#define __NRATRF0_read                       "%d"
#define __NRATRA0_read(fd, buf, bufsize)     ,(int)(fd)
#define __NRATRF1_read                       "%p"
#define __NRATRA1_read(fd, buf, bufsize)     ,buf
#define __NRATRF2_read                       "%Iu"
#define __NRATRA2_read(fd, buf, bufsize)     ,bufsize
#define __NRATRF0_write                      "%d"
#define __NRATRA0_write(fd, buf, bufsize)    ,(int)(fd)
#define __NRATRF1_write                      "%p"
#define __NRATRA1_write(fd, buf, bufsize)    ,buf
#define __NRATRF2_write                      "%Iu"
#define __NRATRA2_write(fd, buf, bufsize)    ,bufsize
#define __NRATRF0_open                       "%q"
#define __NRATRA0_open(filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_open                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA1_open(filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
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
#define __NRATRF2_open                       "%#Io"
#define __NRATRA2_open(filename, oflags, mode) ,(uintptr_t)(mode)
#define __NRATRF0_close                      "%d"
#define __NRATRA0_close(fd)                  ,(int)(fd)
#define __NRATRF0_waitpid                    "%Id"
#define __NRATRA0_waitpid(pid, stat_loc, options) ,(intptr_t)(pid)
#define __NRATRF1_waitpid                    "%p"
#define __NRATRA1_waitpid(pid, stat_loc, options) ,stat_loc
#define __NRATRF2_waitpid                    "%#Ix=%s%s%s%s%s%s%s"
#define __NRATRA2_waitpid(pid, stat_loc, options) ,(uintptr_t)(options),(options) & WNOHANG ? "WNOHANG" : "" \
                                                  ,((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "",(options) & WUNTRACED ? "WUNTRACED" : "" \
                                                  ,((options) & WCONTINUED) && ((options) & (WNOHANG|WUNTRACED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                  ,((options) & WNOWAIT) && ((options) & (WNOHANG|WUNTRACED|WCONTINUED)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF0_creat                      "%q"
#define __NRATRA0_creat(filename, mode)      ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_creat                      "%#Io"
#define __NRATRA1_creat(filename, mode)      ,(uintptr_t)(mode)
#define __NRATRF0_link                       "%q"
#define __NRATRA0_link(existing_file, link_file) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NRATRF1_link                       "%q"
#define __NRATRA1_link(existing_file, link_file) ,(validate_readable_opt(link_file,1),link_file)
#define __NRATRF0_unlink                     "%q"
#define __NRATRA0_unlink(filename)           ,(validate_readable_opt(filename,1),filename)
#define __NRATRF0_execve                     "%q"
#define __NRATRA0_execve(path, argv, envp)   ,(validate_readable_opt(path,1),path)
#define __NRATRF1_execve                     "%p"
#define __NRATRA1_execve(path, argv, envp)   ,argv
#define __NRATRF2_execve                     "%p"
#define __NRATRA2_execve(path, argv, envp)   ,envp
#define __NRATRF0_chdir                      "%q"
#define __NRATRA0_chdir(path)                ,(validate_readable_opt(path,1),path)
#define __NRATRF0_time                       "%p"
#define __NRATRA0_time(timer)                ,timer
#define __NRATRF0_mknod                      "%q"
#define __NRATRA0_mknod(nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NRATRF1_mknod                      "%#Io"
#define __NRATRA1_mknod(nodename, mode, dev) ,(uintptr_t)(mode)
#define __NRATRF2_mknod                      "%.2x:%.2x"
#define __NRATRA2_mknod(nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF0_chmod                      "%q"
#define __NRATRA0_chmod(filename, mode)      ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_chmod                      "%#Io"
#define __NRATRA1_chmod(filename, mode)      ,(uintptr_t)(mode)
#define __NRATRF0_lchown                     "%q"
#define __NRATRA0_lchown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_lchown                     "%I16u"
#define __NRATRA1_lchown(filename, owner, group) ,owner
#define __NRATRF2_lchown                     "%I16u"
#define __NRATRA2_lchown(filename, owner, group) ,group
#define __NRATRF0_linux_oldstat              "%q"
#define __NRATRA0_linux_oldstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_oldstat              "%p"
#define __NRATRA1_linux_oldstat(filename, statbuf) ,statbuf
#define __NRATRF0_lseek                      "%d"
#define __NRATRA0_lseek(fd, offset, whence)  ,(int)(fd)
#define __NRATRF1_lseek                      "%I32d"
#define __NRATRA1_lseek(fd, offset, whence)  ,offset
#define __NRATRF2_lseek                      "%#Ix=%s"
#define __NRATRA2_lseek(fd, offset, whence)  ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NRATRF0_mount                      "%q"
#define __NRATRA0_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(special_file,1),special_file)
#define __NRATRF1_mount                      "%q"
#define __NRATRA1_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(dir,1),dir)
#define __NRATRF2_mount                      "%q"
#define __NRATRA2_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(fstype,1),fstype)
#define __NRATRF3_mount                      "%#Ix"
#define __NRATRA3_mount(special_file, dir, fstype, rwflag, data) ,(uintptr_t)(rwflag)
#define __NRATRF4_mount                      "%p"
#define __NRATRA4_mount(special_file, dir, fstype, rwflag, data) ,data
#define __NRATRF0_umount                     "%q"
#define __NRATRA0_umount(special_file)       ,(validate_readable_opt(special_file,1),special_file)
#define __NRATRF0_setuid                     "%I16u"
#define __NRATRA0_setuid(uid)                ,uid
#define __NRATRF0_stime                      "%p"
#define __NRATRA0_stime(t)                   ,t
#define __NRATRF0_ptrace                     "%#Ix"
#define __NRATRA0_ptrace(request, pid, addr, data) ,(uintptr_t)(request)
#define __NRATRF1_ptrace                     "%Id"
#define __NRATRA1_ptrace(request, pid, addr, data) ,(intptr_t)(pid)
#define __NRATRF2_ptrace                     "%p"
#define __NRATRA2_ptrace(request, pid, addr, data) ,addr
#define __NRATRF3_ptrace                     "%p"
#define __NRATRA3_ptrace(request, pid, addr, data) ,data
#define __NRATRF0_alarm                      "%#Ix"
#define __NRATRA0_alarm(seconds)             ,(uintptr_t)(seconds)
#define __NRATRF0_linux_oldfstat             "%d"
#define __NRATRA0_linux_oldfstat(fd, statbuf) ,(int)(fd)
#define __NRATRF1_linux_oldfstat             "%p"
#define __NRATRA1_linux_oldfstat(fd, statbuf) ,statbuf
#define __NRATRF0_utime                      "%q"
#define __NRATRA0_utime(filename, times)     ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_utime                      "%p"
#define __NRATRA1_utime(filename, times)     ,times
#define __NRATRF0_access                     "%q"
#define __NRATRA0_access(filename, type)     ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_access                     "%#Ix=%s%s%s%s%s"
#define __NRATRA1_access(filename, type)     ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                             ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                             ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NRATRF0_nice                       "%Id"
#define __NRATRA0_nice(inc)                  ,(intptr_t)(inc)
#define __NRATRF0_ftime                      "%p"
#define __NRATRA0_ftime(tp)                  ,tp
#define __NRATRF0_kill                       "%Id"
#define __NRATRA0_kill(pid, signo)           ,(intptr_t)(pid)
#define __NRATRF1_kill                       "%#Ix"
#define __NRATRA1_kill(pid, signo)           ,(uintptr_t)(signo)
#define __NRATRF0_rename                     "%q"
#define __NRATRA0_rename(oldname, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NRATRF1_rename                     "%q"
#define __NRATRA1_rename(oldname, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NRATRF0_mkdir                      "%q"
#define __NRATRA0_mkdir(pathname, mode)      ,(validate_readable_opt(pathname,1),pathname)
#define __NRATRF1_mkdir                      "%#Io"
#define __NRATRA1_mkdir(pathname, mode)      ,(uintptr_t)(mode)
#define __NRATRF0_rmdir                      "%q"
#define __NRATRA0_rmdir(path)                ,(validate_readable_opt(path,1),path)
#define __NRATRF0_dup                        "%d"
#define __NRATRA0_dup(fd)                    ,(int)(fd)
#define __NRATRF0_pipe                       "%p"
#define __NRATRA0_pipe(pipedes)              ,pipedes
#define __NRATRF0_times                      "%p"
#define __NRATRA0_times(buf)                 ,buf
#define __NRATRF0_brk                        "%p"
#define __NRATRA0_brk(addr)                  ,addr
#define __NRATRF0_setgid                     "%I16u"
#define __NRATRA0_setgid(gid)                ,gid
#define __NRATRF0_signal                     "%#Ix"
#define __NRATRA0_signal(signo, handler)     ,(uintptr_t)(signo)
#define __NRATRF1_signal                     "%p"
#define __NRATRA1_signal(signo, handler)     ,handler
#define __NRATRF0_acct                       "%q"
#define __NRATRA0_acct(filename)             ,(validate_readable_opt(filename,1),filename)
#define __NRATRF0_umount2                    "%q"
#define __NRATRA0_umount2(special_file, flags) ,(validate_readable_opt(special_file,1),special_file)
#define __NRATRF1_umount2                    "%#Ix"
#define __NRATRA1_umount2(special_file, flags) ,(uintptr_t)(flags)
#define __NRATRF0_ioctl                      "%d"
#define __NRATRA0_ioctl(fd, request, arg)    ,(int)(fd)
#define __NRATRF1_ioctl                      "%#Ix"
#define __NRATRA1_ioctl(fd, request, arg)    ,(uintptr_t)(request)
#define __NRATRF2_ioctl                      "%p"
#define __NRATRA2_ioctl(fd, request, arg)    ,arg
#define __NRATRF0_fcntl                      "%d"
#define __NRATRA0_fcntl(fd, cmd, arg)        ,(int)(fd)
#define __NRATRF1_fcntl                      "%#Ix"
#define __NRATRA1_fcntl(fd, cmd, arg)        ,(uintptr_t)(cmd)
#define __NRATRF2_fcntl                      "%p"
#define __NRATRA2_fcntl(fd, cmd, arg)        ,arg
#define __NRATRF0_setpgid                    "%Id"
#define __NRATRA0_setpgid(pid, pgid)         ,(intptr_t)(pid)
#define __NRATRF1_setpgid                    "%Id"
#define __NRATRA1_setpgid(pid, pgid)         ,(intptr_t)(pgid)
#define __NRATRF0_oldolduname                "%p"
#define __NRATRA0_oldolduname(name)          ,name
#define __NRATRF0_umask                      "%#Io"
#define __NRATRA0_umask(mode)                ,(uintptr_t)(mode)
#define __NRATRF0_chroot                     "%q"
#define __NRATRA0_chroot(path)               ,(validate_readable_opt(path,1),path)
#define __NRATRF0_ustat                      "%.2x:%.2x"
#define __NRATRA0_ustat(dev, ubuf)           ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF1_ustat                      "%p"
#define __NRATRA1_ustat(dev, ubuf)           ,ubuf
#define __NRATRF0_dup2                       "%d"
#define __NRATRA0_dup2(oldfd, newfd)         ,(int)(oldfd)
#define __NRATRF1_dup2                       "%d"
#define __NRATRA1_dup2(oldfd, newfd)         ,(int)(newfd)
#define __NRATRF0_sigaction                  "%#Ix"
#define __NRATRA0_sigaction(signo, act, oact) ,(uintptr_t)(signo)
#define __NRATRF1_sigaction                  "%p"
#define __NRATRA1_sigaction(signo, act, oact) ,act
#define __NRATRF2_sigaction                  "%p"
#define __NRATRA2_sigaction(signo, act, oact) ,oact
#define __NRATRF0_ssetmask                   "%#Ix"
#define __NRATRA0_ssetmask(sigmask)          ,(uintptr_t)(sigmask)
#define __NRATRF0_setreuid                   "%I16u"
#define __NRATRA0_setreuid(ruid, euid)       ,ruid
#define __NRATRF1_setreuid                   "%I16u"
#define __NRATRA1_setreuid(ruid, euid)       ,euid
#define __NRATRF0_setregid                   "%I16u"
#define __NRATRA0_setregid(rgid, egid)       ,rgid
#define __NRATRF1_setregid                   "%I16u"
#define __NRATRA1_setregid(rgid, egid)       ,egid
#define __NRATRF0_sigsuspend                 "%p"
#define __NRATRA0_sigsuspend(set)            ,set
#define __NRATRF0_sigpending                 "%p"
#define __NRATRA0_sigpending(set)            ,set
#define __NRATRF0_sethostname                "%q"
#define __NRATRA0_sethostname(name, len)     ,(validate_readable_opt(name,1),name)
#define __NRATRF1_sethostname                "%Iu"
#define __NRATRA1_sethostname(name, len)     ,len
#define __NRATRF0_setrlimit                  "%#Ix"
#define __NRATRA0_setrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NRATRF1_setrlimit                  "%p"
#define __NRATRA1_setrlimit(resource, rlimits) ,rlimits
#define __NRATRF0_getrlimit                  "%#Ix"
#define __NRATRA0_getrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NRATRF1_getrlimit                  "%p"
#define __NRATRA1_getrlimit(resource, rlimits) ,rlimits
#define __NRATRF0_getrusage                  "%Id"
#define __NRATRA0_getrusage(who, usage)      ,(intptr_t)(who)
#define __NRATRF1_getrusage                  "%p"
#define __NRATRA1_getrusage(who, usage)      ,usage
#define __NRATRF0_gettimeofday               "%p"
#define __NRATRA0_gettimeofday(tv, tz)       ,tv
#define __NRATRF1_gettimeofday               "%p"
#define __NRATRA1_gettimeofday(tv, tz)       ,tz
#define __NRATRF0_settimeofday               "%p"
#define __NRATRA0_settimeofday(tv, tz)       ,tv
#define __NRATRF1_settimeofday               "%p"
#define __NRATRA1_settimeofday(tv, tz)       ,tz
#define __NRATRF0_getgroups                  "%Iu"
#define __NRATRA0_getgroups(size, list)      ,size
#define __NRATRF1_getgroups                  "%p"
#define __NRATRA1_getgroups(size, list)      ,list
#define __NRATRF0_setgroups                  "%Iu"
#define __NRATRA0_setgroups(count, groups)   ,count
#define __NRATRF1_setgroups                  "%p"
#define __NRATRA1_setgroups(count, groups)   ,groups
#define __NRATRF0_select                     "%Iu"
#define __NRATRA0_select(nfds, readfds, writefds, exceptfds, timeout) ,nfds
#define __NRATRF1_select                     "%p"
#define __NRATRA1_select(nfds, readfds, writefds, exceptfds, timeout) ,readfds
#define __NRATRF2_select                     "%p"
#define __NRATRA2_select(nfds, readfds, writefds, exceptfds, timeout) ,writefds
#define __NRATRF3_select                     "%p"
#define __NRATRA3_select(nfds, readfds, writefds, exceptfds, timeout) ,exceptfds
#define __NRATRF4_select                     "%p"
#define __NRATRA4_select(nfds, readfds, writefds, exceptfds, timeout) ,timeout
#define __NRATRF0_symlink                    "%q"
#define __NRATRA0_symlink(link_text, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NRATRF1_symlink                    "%q"
#define __NRATRA1_symlink(link_text, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NRATRF0_linux_oldlstat             "%q"
#define __NRATRA0_linux_oldlstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_oldlstat             "%p"
#define __NRATRA1_linux_oldlstat(filename, statbuf) ,statbuf
#define __NRATRF0_readlink                   "%q"
#define __NRATRA0_readlink(path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NRATRF1_readlink                   "%p"
#define __NRATRA1_readlink(path, buf, buflen) ,buf
#define __NRATRF2_readlink                   "%Iu"
#define __NRATRA2_readlink(path, buf, buflen) ,buflen
#define __NRATRF0_swapon                     "%q"
#define __NRATRA0_swapon(pathname, swapflags) ,(validate_readable_opt(pathname,1),pathname)
#define __NRATRF1_swapon                     "%#Ix=%s%s%s"
#define __NRATRA1_swapon(pathname, swapflags) ,(uintptr_t)(swapflags),(swapflags) & SWAP_FLAG_PREFER ? "SWAP_FLAG_PREFER" : "" \
                                              ,((swapflags) & SWAP_FLAG_DISCARD) && ((swapflags) & (SWAP_FLAG_PREFER)) ? "|" : "",(swapflags) & SWAP_FLAG_DISCARD ? "SWAP_FLAG_DISCARD" : ""
#define __NRATRF0_reboot                     "%#Ix"
#define __NRATRA0_reboot(how)                ,(uintptr_t)(how)
#define __NRATRF0_readdir                    "%d"
#define __NRATRA0_readdir(fd, dirp, count)   ,(int)(fd)
#define __NRATRF1_readdir                    "%p"
#define __NRATRA1_readdir(fd, dirp, count)   ,dirp
#define __NRATRF2_readdir                    "%Iu"
#define __NRATRA2_readdir(fd, dirp, count)   ,count
#define __NRATRF0_mmap                       "%p"
#define __NRATRA0_mmap(addr, len, prot, flags, fd, offset) ,addr
#define __NRATRF1_mmap                       "%Iu"
#define __NRATRA1_mmap(addr, len, prot, flags, fd, offset) ,len
#define __NRATRF2_mmap                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                                           ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                                           ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                                           ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : "" \
                                                           ,((prot) & PROT_LOOSE) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM)) ? "|" : "",(prot) & PROT_LOOSE ? "PROT_LOOSE" : "" \
                                                           ,((prot) & PROT_SHARED) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE)) ? "|" : "",(prot) & PROT_SHARED ? "PROT_SHARED" : ""
#define __NRATRF3_mmap                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(flags),(flags) & MAP_SHARED ? "MAP_SHARED" : (flags) ? "" : "MAP_AUTOMATIC" \
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
#define __NRATRF4_mmap                       "%d"
#define __NRATRA4_mmap(addr, len, prot, flags, fd, offset) ,(int)(fd)
#define __NRATRF5_mmap                       "%#Ix"
#define __NRATRA5_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(offset)
#define __NRATRF0_munmap                     "%p"
#define __NRATRA0_munmap(addr, len)          ,addr
#define __NRATRF1_munmap                     "%Iu"
#define __NRATRA1_munmap(addr, len)          ,len
#define __NRATRF0_truncate                   "%q"
#define __NRATRA0_truncate(filename, length) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_truncate                   "%#Ix"
#define __NRATRA1_truncate(filename, length) ,(uintptr_t)(length)
#define __NRATRF0_ftruncate                  "%d"
#define __NRATRA0_ftruncate(fd, length)      ,(int)(fd)
#define __NRATRF1_ftruncate                  "%#Ix"
#define __NRATRA1_ftruncate(fd, length)      ,(uintptr_t)(length)
#define __NRATRF0_fchmod                     "%d"
#define __NRATRA0_fchmod(fd, mode)           ,(int)(fd)
#define __NRATRF1_fchmod                     "%#Io"
#define __NRATRA1_fchmod(fd, mode)           ,(uintptr_t)(mode)
#define __NRATRF0_fchown                     "%d"
#define __NRATRA0_fchown(fd, owner, group)   ,(int)(fd)
#define __NRATRF1_fchown                     "%I16u"
#define __NRATRA1_fchown(fd, owner, group)   ,owner
#define __NRATRF2_fchown                     "%I16u"
#define __NRATRA2_fchown(fd, owner, group)   ,group
#define __NRATRF0_getpriority                "%#Ix"
#define __NRATRA0_getpriority(which, who)    ,(uintptr_t)(which)
#define __NRATRF1_getpriority                "%Iu"
#define __NRATRA1_getpriority(which, who)    ,(uintptr_t)(who)
#define __NRATRF0_setpriority                "%#Ix"
#define __NRATRA0_setpriority(which, who, value) ,(uintptr_t)(which)
#define __NRATRF1_setpriority                "%Iu"
#define __NRATRA1_setpriority(which, who, value) ,(uintptr_t)(who)
#define __NRATRF2_setpriority                "%#Ix"
#define __NRATRA2_setpriority(which, who, value) ,(uintptr_t)(value)
#define __NRATRF0_profil                     "%p"
#define __NRATRA0_profil(sample_buffer, size, offset, scale) ,sample_buffer
#define __NRATRF1_profil                     "%Iu"
#define __NRATRA1_profil(sample_buffer, size, offset, scale) ,size
#define __NRATRF2_profil                     "%Iu"
#define __NRATRA2_profil(sample_buffer, size, offset, scale) ,offset
#define __NRATRF3_profil                     "%#Ix"
#define __NRATRA3_profil(sample_buffer, size, offset, scale) ,(uintptr_t)(scale)
#define __NRATRF0_statfs                     "%q"
#define __NRATRA0_statfs(file, buf)          ,(validate_readable_opt(file,1),file)
#define __NRATRF1_statfs                     "%p"
#define __NRATRA1_statfs(file, buf)          ,buf
#define __NRATRF0_fstatfs                    "%d"
#define __NRATRA0_fstatfs(file, buf)         ,(int)(file)
#define __NRATRF1_fstatfs                    "%p"
#define __NRATRA1_fstatfs(file, buf)         ,buf
#define __NRATRF0_ioperm                     "%#Ix"
#define __NRATRA0_ioperm(from, num, turn_on) ,(uintptr_t)(from)
#define __NRATRF1_ioperm                     "%#Ix"
#define __NRATRA1_ioperm(from, num, turn_on) ,(uintptr_t)(num)
#define __NRATRF2_ioperm                     "%#Ix"
#define __NRATRA2_ioperm(from, num, turn_on) ,(uintptr_t)(turn_on)
#define __NRATRF0_socketcall                 "?"
#define __NRATRA0_socketcall(call, args)     /* nothing */
#define __NRATRF1_socketcall                 "%p"
#define __NRATRA1_socketcall(call, args)     ,args
#define __NRATRF0_syslog                     "%Iu"
#define __NRATRA0_syslog(level, str, len)    ,(uintptr_t)(level)
#define __NRATRF1_syslog                     "%$q"
#define __NRATRA1_syslog(level, str, len)    ,len,(validate_readable(str,len),str)
#define __NRATRF2_syslog                     "%Iu"
#define __NRATRA2_syslog(level, str, len)    ,len
#define __NRATRF0_setitimer                  "%#Ix"
#define __NRATRA0_setitimer(which, newval, oldval) ,(uintptr_t)(which)
#define __NRATRF1_setitimer                  "%p"
#define __NRATRA1_setitimer(which, newval, oldval) ,newval
#define __NRATRF2_setitimer                  "%p"
#define __NRATRA2_setitimer(which, newval, oldval) ,oldval
#define __NRATRF0_getitimer                  "%#Ix"
#define __NRATRA0_getitimer(which, curr_value) ,(uintptr_t)(which)
#define __NRATRF1_getitimer                  "%p"
#define __NRATRA1_getitimer(which, curr_value) ,curr_value
#define __NRATRF0_linux_stat32               "%q"
#define __NRATRA0_linux_stat32(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_stat32               "%p"
#define __NRATRA1_linux_stat32(filename, statbuf) ,statbuf
#define __NRATRF0_linux_lstat32              "%q"
#define __NRATRA0_linux_lstat32(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_lstat32              "%p"
#define __NRATRA1_linux_lstat32(filename, statbuf) ,statbuf
#define __NRATRF0_linux_fstat32              "%d"
#define __NRATRA0_linux_fstat32(fd, statbuf) ,(int)(fd)
#define __NRATRF1_linux_fstat32              "%p"
#define __NRATRA1_linux_fstat32(fd, statbuf) ,statbuf
#define __NRATRF0_olduname                   "%p"
#define __NRATRA0_olduname(name)             ,name
#define __NRATRF0_iopl                       "%#Ix"
#define __NRATRA0_iopl(level)                ,(uintptr_t)(level)
#define __NRATRF0_wait4                      "%Id"
#define __NRATRA0_wait4(pid, stat_loc, options, usage) ,(intptr_t)(pid)
#define __NRATRF1_wait4                      "%p"
#define __NRATRA1_wait4(pid, stat_loc, options, usage) ,stat_loc
#define __NRATRF2_wait4                      "%#Ix=%s%s%s%s%s%s%s"
#define __NRATRA2_wait4(pid, stat_loc, options, usage) ,(uintptr_t)(options),(options) & WNOHANG ? "WNOHANG" : "" \
                                                       ,((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "",(options) & WUNTRACED ? "WUNTRACED" : "" \
                                                       ,((options) & WCONTINUED) && ((options) & (WNOHANG|WUNTRACED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                       ,((options) & WNOWAIT) && ((options) & (WNOHANG|WUNTRACED|WCONTINUED)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF3_wait4                      "%p"
#define __NRATRA3_wait4(pid, stat_loc, options, usage) ,usage
#define __NRATRF0_swapoff                    "%q"
#define __NRATRA0_swapoff(pathname)          ,(validate_readable_opt(pathname,1),pathname)
#define __NRATRF0_sysinfo                    "%p"
#define __NRATRA0_sysinfo(info)              ,info
#define __NRATRF0_fsync                      "%d"
#define __NRATRA0_fsync(fd)                  ,(int)(fd)
#define __NRATRF0_sigreturn                  "%p"
#define __NRATRA0_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_fpu
#define __NRATRF1_sigreturn                  "%#Ix"
#define __NRATRA1_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,(uintptr_t)(unused1)
#define __NRATRF2_sigreturn                  "%#Ix"
#define __NRATRA2_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,(uintptr_t)(unused2)
#define __NRATRF3_sigreturn                  "%p"
#define __NRATRA3_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_sigmask
#define __NRATRF4_sigreturn                  "%p"
#define __NRATRA4_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,sc_info
#define __NRATRF5_sigreturn                  "%p"
#define __NRATRA5_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_cpu
#define __NRATRF0_clone                      "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA0_clone(flags, child_stack, ptid, newtls, ctid) ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
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
#define __NRATRF1_clone                      "%p"
#define __NRATRA1_clone(flags, child_stack, ptid, newtls, ctid) ,child_stack
#define __NRATRF2_clone                      "%p"
#define __NRATRA2_clone(flags, child_stack, ptid, newtls, ctid) ,ptid
#define __NRATRF3_clone                      "%p"
#define __NRATRA3_clone(flags, child_stack, ptid, newtls, ctid) ,newtls
#define __NRATRF4_clone                      "%p"
#define __NRATRA4_clone(flags, child_stack, ptid, newtls, ctid) ,ctid
#define __NRATRF0_setdomainname              "%q"
#define __NRATRA0_setdomainname(name, len)   ,(validate_readable_opt(name,1),name)
#define __NRATRF1_setdomainname              "%Iu"
#define __NRATRA1_setdomainname(name, len)   ,len
#define __NRATRF0_uname                      "%p"
#define __NRATRA0_uname(name)                ,name
#define __NRATRF0_modify_ldt                 "%#Ix"
#define __NRATRA0_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(func)
#define __NRATRF1_modify_ldt                 "%p"
#define __NRATRA1_modify_ldt(func, ptr, bytecount) ,ptr
#define __NRATRF2_modify_ldt                 "%#Ix"
#define __NRATRA2_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(bytecount)
#define __NRATRF0_mprotect                   "%p"
#define __NRATRA0_mprotect(addr, len, prot)  ,addr
#define __NRATRF1_mprotect                   "%Iu"
#define __NRATRA1_mprotect(addr, len, prot)  ,len
#define __NRATRF2_mprotect                   "%#Ix=%s%s%s%s%s%s%s"
#define __NRATRA2_mprotect(addr, len, prot)  ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                             ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                             ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                             ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : ""
#define __NRATRF0_sigprocmask                "%#Ix"
#define __NRATRA0_sigprocmask(how, set, oset) ,(uintptr_t)(how)
#define __NRATRF1_sigprocmask                "%p"
#define __NRATRA1_sigprocmask(how, set, oset) ,set
#define __NRATRF2_sigprocmask                "%p"
#define __NRATRA2_sigprocmask(how, set, oset) ,oset
#define __NRATRF0_getpgid                    "%Id"
#define __NRATRA0_getpgid(pid)               ,(intptr_t)(pid)
#define __NRATRF0_fchdir                     "%d"
#define __NRATRA0_fchdir(fd)                 ,(int)(fd)
#define __NRATRF0_setfsuid                   "%I16u"
#define __NRATRA0_setfsuid(uid)              ,uid
#define __NRATRF0_setfsgid                   "%I16u"
#define __NRATRA0_setfsgid(gid)              ,gid
#define __NRATRF0__llseek                    "%d"
#define __NRATRA0__llseek(fd, offset, result, whence) ,(int)(fd)
#define __NRATRF1__llseek                    "%I64d"
#define __NRATRA1__llseek(fd, offset, result, whence) ,offset
#define __NRATRF2__llseek                    "%p"
#define __NRATRA2__llseek(fd, offset, result, whence) ,result
#define __NRATRF3__llseek                    "%#Ix=%s"
#define __NRATRA3__llseek(fd, offset, result, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NRATRF0_getdents                   "%d"
#define __NRATRA0_getdents(fd, dirp, count)  ,(int)(fd)
#define __NRATRF1_getdents                   "%p"
#define __NRATRA1_getdents(fd, dirp, count)  ,dirp
#define __NRATRF2_getdents                   "%Iu"
#define __NRATRA2_getdents(fd, dirp, count)  ,count
#define __NRATRF0_flock                      "%d"
#define __NRATRA0_flock(fd, operation)       ,(int)(fd)
#define __NRATRF1_flock                      "%#Ix"
#define __NRATRA1_flock(fd, operation)       ,(uintptr_t)(operation)
#define __NRATRF0_msync                      "%p"
#define __NRATRA0_msync(addr, len, flags)    ,addr
#define __NRATRF1_msync                      "%Iu"
#define __NRATRA1_msync(addr, len, flags)    ,len
#define __NRATRF2_msync                      "%#Ix"
#define __NRATRA2_msync(addr, len, flags)    ,(uintptr_t)(flags)
#define __NRATRF0_readv                      "%d"
#define __NRATRA0_readv(fd, iovec, count)    ,(int)(fd)
#define __NRATRF1_readv                      "%p"
#define __NRATRA1_readv(fd, iovec, count)    ,iovec
#define __NRATRF2_readv                      "%Iu"
#define __NRATRA2_readv(fd, iovec, count)    ,count
#define __NRATRF0_writev                     "%d"
#define __NRATRA0_writev(fd, iovec, count)   ,(int)(fd)
#define __NRATRF1_writev                     "%p"
#define __NRATRA1_writev(fd, iovec, count)   ,iovec
#define __NRATRF2_writev                     "%Iu"
#define __NRATRA2_writev(fd, iovec, count)   ,count
#define __NRATRF0_getsid                     "%Id"
#define __NRATRA0_getsid(pid)                ,(intptr_t)(pid)
#define __NRATRF0_fdatasync                  "%d"
#define __NRATRA0_fdatasync(fd)              ,(int)(fd)
#define __NRATRF0_mlock                      "%p"
#define __NRATRA0_mlock(addr, len)           ,addr
#define __NRATRF1_mlock                      "%Iu"
#define __NRATRA1_mlock(addr, len)           ,len
#define __NRATRF0_munlock                    "%p"
#define __NRATRA0_munlock(addr, len)         ,addr
#define __NRATRF1_munlock                    "%Iu"
#define __NRATRA1_munlock(addr, len)         ,len
#define __NRATRF0_mlockall                   "%#Ix"
#define __NRATRA0_mlockall(flags)            ,(uintptr_t)(flags)
#define __NRATRF0_sched_setparam             "%Id"
#define __NRATRA0_sched_setparam(pid, param) ,(intptr_t)(pid)
#define __NRATRF1_sched_setparam             "%p"
#define __NRATRA1_sched_setparam(pid, param) ,param
#define __NRATRF0_sched_getparam             "%Id"
#define __NRATRA0_sched_getparam(pid, param) ,(intptr_t)(pid)
#define __NRATRF1_sched_getparam             "%p"
#define __NRATRA1_sched_getparam(pid, param) ,param
#define __NRATRF0_sched_setscheduler         "%Id"
#define __NRATRA0_sched_setscheduler(pid, policy, param) ,(intptr_t)(pid)
#define __NRATRF1_sched_setscheduler         "%#Ix"
#define __NRATRA1_sched_setscheduler(pid, policy, param) ,(uintptr_t)(policy)
#define __NRATRF2_sched_setscheduler         "%p"
#define __NRATRA2_sched_setscheduler(pid, policy, param) ,param
#define __NRATRF0_sched_getscheduler         "%Id"
#define __NRATRA0_sched_getscheduler(pid)    ,(intptr_t)(pid)
#define __NRATRF0_sched_get_priority_max     "%#Ix"
#define __NRATRA0_sched_get_priority_max(algorithm) ,(uintptr_t)(algorithm)
#define __NRATRF0_sched_get_priority_min     "%#Ix"
#define __NRATRA0_sched_get_priority_min(algorithm) ,(uintptr_t)(algorithm)
#define __NRATRF0_sched_rr_get_interval      "%Id"
#define __NRATRA0_sched_rr_get_interval(pid, tms) ,(intptr_t)(pid)
#define __NRATRF1_sched_rr_get_interval      "%p"
#define __NRATRA1_sched_rr_get_interval(pid, tms) ,tms
#define __NRATRF0_nanosleep                  "%p"
#define __NRATRA0_nanosleep(req, rem)        ,req
#define __NRATRF1_nanosleep                  "%p"
#define __NRATRA1_nanosleep(req, rem)        ,rem
#define __NRATRF0_mremap                     "%p"
#define __NRATRA0_mremap(addr, old_len, new_len, flags, new_address) ,addr
#define __NRATRF1_mremap                     "%Iu"
#define __NRATRA1_mremap(addr, old_len, new_len, flags, new_address) ,old_len
#define __NRATRF2_mremap                     "%Iu"
#define __NRATRA2_mremap(addr, old_len, new_len, flags, new_address) ,new_len
#define __NRATRF3_mremap                     "%#Ix=%s%s%s"
#define __NRATRA3_mremap(addr, old_len, new_len, flags, new_address) ,(uintptr_t)(flags),(flags) & MREMAP_MAYMOVE ? "MREMAP_MAYMOVE" : "" \
                                                                     ,((flags) & MREMAP_FIXED) && ((flags) & (MREMAP_MAYMOVE)) ? "|" : "",(flags) & MREMAP_FIXED ? "MREMAP_FIXED" : ""
#define __NRATRF4_mremap                     "%p"
#define __NRATRA4_mremap(addr, old_len, new_len, flags, new_address) ,new_address
#define __NRATRF0_setresuid                  "%I16u"
#define __NRATRA0_setresuid(ruid, euid, suid) ,ruid
#define __NRATRF1_setresuid                  "%I16u"
#define __NRATRA1_setresuid(ruid, euid, suid) ,euid
#define __NRATRF2_setresuid                  "%I16u"
#define __NRATRA2_setresuid(ruid, euid, suid) ,suid
#define __NRATRF0_getresuid                  "%p"
#define __NRATRA0_getresuid(ruid, euid, suid) ,ruid
#define __NRATRF1_getresuid                  "%p"
#define __NRATRA1_getresuid(ruid, euid, suid) ,euid
#define __NRATRF2_getresuid                  "%p"
#define __NRATRA2_getresuid(ruid, euid, suid) ,suid
#define __NRATRF0_poll                       "%p"
#define __NRATRA0_poll(fds, nfds, timeout)   ,fds
#define __NRATRF1_poll                       "%Iu"
#define __NRATRA1_poll(fds, nfds, timeout)   ,nfds
#define __NRATRF2_poll                       "%Id"
#define __NRATRA2_poll(fds, nfds, timeout)   ,(intptr_t)(timeout)
#define __NRATRF0_setresgid                  "%I16u"
#define __NRATRA0_setresgid(rgid, egid, sgid) ,rgid
#define __NRATRF1_setresgid                  "%I16u"
#define __NRATRA1_setresgid(rgid, egid, sgid) ,egid
#define __NRATRF2_setresgid                  "%I16u"
#define __NRATRA2_setresgid(rgid, egid, sgid) ,sgid
#define __NRATRF0_getresgid                  "%p"
#define __NRATRA0_getresgid(rgid, egid, sgid) ,rgid
#define __NRATRF1_getresgid                  "%p"
#define __NRATRA1_getresgid(rgid, egid, sgid) ,egid
#define __NRATRF2_getresgid                  "%p"
#define __NRATRA2_getresgid(rgid, egid, sgid) ,sgid
#define __NRATRF0_rt_sigaction               "%#Ix"
#define __NRATRA0_rt_sigaction(signo, act, oact, sigsetsize) ,(uintptr_t)(signo)
#define __NRATRF1_rt_sigaction               "%p"
#define __NRATRA1_rt_sigaction(signo, act, oact, sigsetsize) ,act
#define __NRATRF2_rt_sigaction               "%p"
#define __NRATRA2_rt_sigaction(signo, act, oact, sigsetsize) ,oact
#define __NRATRF3_rt_sigaction               "%Iu"
#define __NRATRA3_rt_sigaction(signo, act, oact, sigsetsize) ,sigsetsize
#define __NRATRF0_rt_sigprocmask             "%#Ix"
#define __NRATRA0_rt_sigprocmask(how, set, oset, sigsetsize) ,(uintptr_t)(how)
#define __NRATRF1_rt_sigprocmask             "%p"
#define __NRATRA1_rt_sigprocmask(how, set, oset, sigsetsize) ,set
#define __NRATRF2_rt_sigprocmask             "%p"
#define __NRATRA2_rt_sigprocmask(how, set, oset, sigsetsize) ,oset
#define __NRATRF3_rt_sigprocmask             "%Iu"
#define __NRATRA3_rt_sigprocmask(how, set, oset, sigsetsize) ,sigsetsize
#define __NRATRF0_rt_sigpending              "%p"
#define __NRATRA0_rt_sigpending(set, sigsetsize) ,set
#define __NRATRF1_rt_sigpending              "%Iu"
#define __NRATRA1_rt_sigpending(set, sigsetsize) ,sigsetsize
#define __NRATRF0_rt_sigtimedwait            "%p"
#define __NRATRA0_rt_sigtimedwait(set, info, timeout, sigsetsize) ,set
#define __NRATRF1_rt_sigtimedwait            "%p"
#define __NRATRA1_rt_sigtimedwait(set, info, timeout, sigsetsize) ,info
#define __NRATRF2_rt_sigtimedwait            "%p"
#define __NRATRA2_rt_sigtimedwait(set, info, timeout, sigsetsize) ,timeout
#define __NRATRF3_rt_sigtimedwait            "%Iu"
#define __NRATRA3_rt_sigtimedwait(set, info, timeout, sigsetsize) ,sigsetsize
#define __NRATRF0_rt_sigqueueinfo            "%Id"
#define __NRATRA0_rt_sigqueueinfo(tgid, signo, uinfo) ,(intptr_t)(tgid)
#define __NRATRF1_rt_sigqueueinfo            "%#Ix"
#define __NRATRA1_rt_sigqueueinfo(tgid, signo, uinfo) ,(uintptr_t)(signo)
#define __NRATRF2_rt_sigqueueinfo            "%p"
#define __NRATRA2_rt_sigqueueinfo(tgid, signo, uinfo) ,uinfo
#define __NRATRF0_rt_sigsuspend              "%p"
#define __NRATRA0_rt_sigsuspend(set, sigsetsize) ,set
#define __NRATRF1_rt_sigsuspend              "%Iu"
#define __NRATRA1_rt_sigsuspend(set, sigsetsize) ,sigsetsize
#define __NRATRF0_pread64                    "%d"
#define __NRATRA0_pread64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NRATRF1_pread64                    "%p"
#define __NRATRA1_pread64(fd, buf, bufsize, offset) ,buf
#define __NRATRF2_pread64                    "%Iu"
#define __NRATRA2_pread64(fd, buf, bufsize, offset) ,bufsize
#define __NRATRF3_pread64                    "%I64u"
#define __NRATRA3_pread64(fd, buf, bufsize, offset) ,offset
#define __NRATRF0_pwrite64                   "%d"
#define __NRATRA0_pwrite64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NRATRF1_pwrite64                   "%p"
#define __NRATRA1_pwrite64(fd, buf, bufsize, offset) ,buf
#define __NRATRF2_pwrite64                   "%Iu"
#define __NRATRA2_pwrite64(fd, buf, bufsize, offset) ,bufsize
#define __NRATRF3_pwrite64                   "%I64u"
#define __NRATRA3_pwrite64(fd, buf, bufsize, offset) ,offset
#define __NRATRF0_chown                      "%q"
#define __NRATRA0_chown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_chown                      "%I16u"
#define __NRATRA1_chown(filename, owner, group) ,owner
#define __NRATRF2_chown                      "%I16u"
#define __NRATRA2_chown(filename, owner, group) ,group
#define __NRATRF0_getcwd                     "%p"
#define __NRATRA0_getcwd(buf, size)          ,buf
#define __NRATRF1_getcwd                     "%Iu"
#define __NRATRA1_getcwd(buf, size)          ,size
#define __NRATRF0_sigaltstack                "%p"
#define __NRATRA0_sigaltstack(ss, oss)       ,ss
#define __NRATRF1_sigaltstack                "%p"
#define __NRATRA1_sigaltstack(ss, oss)       ,oss
#define __NRATRF0_sendfile                   "%d"
#define __NRATRA0_sendfile(out_fd, in_fd, offset, count) ,(int)(out_fd)
#define __NRATRF1_sendfile                   "%d"
#define __NRATRA1_sendfile(out_fd, in_fd, offset, count) ,(int)(in_fd)
#define __NRATRF2_sendfile                   "%p"
#define __NRATRA2_sendfile(out_fd, in_fd, offset, count) ,offset
#define __NRATRF3_sendfile                   "%Iu"
#define __NRATRA3_sendfile(out_fd, in_fd, offset, count) ,count
#define __NRATRF0_mmap2                      "%p"
#define __NRATRA0_mmap2(addr, len, prot, flags, fd, pgoffset) ,addr
#define __NRATRF1_mmap2                      "%Iu"
#define __NRATRA1_mmap2(addr, len, prot, flags, fd, pgoffset) ,len
#define __NRATRF2_mmap2                      "%#Ix"
#define __NRATRA2_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(prot)
#define __NRATRF3_mmap2                      "%#Ix"
#define __NRATRA3_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(flags)
#define __NRATRF4_mmap2                      "%d"
#define __NRATRA4_mmap2(addr, len, prot, flags, fd, pgoffset) ,(int)(fd)
#define __NRATRF5_mmap2                      "%#Ix"
#define __NRATRA5_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(pgoffset)
#define __NRATRF0_truncate64                 "%q"
#define __NRATRA0_truncate64(filename, length) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_truncate64                 "%I64u"
#define __NRATRA1_truncate64(filename, length) ,length
#define __NRATRF0_ftruncate64                "%d"
#define __NRATRA0_ftruncate64(fd, length)    ,(int)(fd)
#define __NRATRF1_ftruncate64                "%I64u"
#define __NRATRA1_ftruncate64(fd, length)    ,length
#define __NRATRF0_linux_stat64               "%q"
#define __NRATRA0_linux_stat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_stat64               "%p"
#define __NRATRA1_linux_stat64(filename, statbuf) ,statbuf
#define __NRATRF0_linux_lstat64              "%q"
#define __NRATRA0_linux_lstat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_lstat64              "%p"
#define __NRATRA1_linux_lstat64(filename, statbuf) ,statbuf
#define __NRATRF0_linux_fstat64              "%d"
#define __NRATRA0_linux_fstat64(fd, statbuf) ,(int)(fd)
#define __NRATRF1_linux_fstat64              "%p"
#define __NRATRA1_linux_fstat64(fd, statbuf) ,statbuf
#define __NRATRF0_lchown32                   "%q"
#define __NRATRA0_lchown32(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_lchown32                   "%I32u"
#define __NRATRA1_lchown32(filename, owner, group) ,owner
#define __NRATRF2_lchown32                   "%I32u"
#define __NRATRA2_lchown32(filename, owner, group) ,group
#define __NRATRF0_setreuid32                 "%I32u"
#define __NRATRA0_setreuid32(ruid, euid)     ,ruid
#define __NRATRF1_setreuid32                 "%I32u"
#define __NRATRA1_setreuid32(ruid, euid)     ,euid
#define __NRATRF0_setregid32                 "%I32u"
#define __NRATRA0_setregid32(rgid, egid)     ,rgid
#define __NRATRF1_setregid32                 "%I32u"
#define __NRATRA1_setregid32(rgid, egid)     ,egid
#define __NRATRF0_getgroups32                "%Iu"
#define __NRATRA0_getgroups32(size, list)    ,size
#define __NRATRF1_getgroups32                "%p"
#define __NRATRA1_getgroups32(size, list)    ,list
#define __NRATRF0_setgroups32                "%Iu"
#define __NRATRA0_setgroups32(count, groups) ,count
#define __NRATRF1_setgroups32                "%p"
#define __NRATRA1_setgroups32(count, groups) ,groups
#define __NRATRF0_fchown32                   "%d"
#define __NRATRA0_fchown32(fd, owner, group) ,(int)(fd)
#define __NRATRF1_fchown32                   "%I32u"
#define __NRATRA1_fchown32(fd, owner, group) ,owner
#define __NRATRF2_fchown32                   "%I32u"
#define __NRATRA2_fchown32(fd, owner, group) ,group
#define __NRATRF0_setresuid32                "%I32u"
#define __NRATRA0_setresuid32(ruid, euid, suid) ,ruid
#define __NRATRF1_setresuid32                "%I32u"
#define __NRATRA1_setresuid32(ruid, euid, suid) ,euid
#define __NRATRF2_setresuid32                "%I32u"
#define __NRATRA2_setresuid32(ruid, euid, suid) ,suid
#define __NRATRF0_getresuid32                "%p"
#define __NRATRA0_getresuid32(ruid, euid, suid) ,ruid
#define __NRATRF1_getresuid32                "%p"
#define __NRATRA1_getresuid32(ruid, euid, suid) ,euid
#define __NRATRF2_getresuid32                "%p"
#define __NRATRA2_getresuid32(ruid, euid, suid) ,suid
#define __NRATRF0_setresgid32                "%I32u"
#define __NRATRA0_setresgid32(rgid, egid, sgid) ,rgid
#define __NRATRF1_setresgid32                "%I32u"
#define __NRATRA1_setresgid32(rgid, egid, sgid) ,egid
#define __NRATRF2_setresgid32                "%I32u"
#define __NRATRA2_setresgid32(rgid, egid, sgid) ,sgid
#define __NRATRF0_getresgid32                "%p"
#define __NRATRA0_getresgid32(rgid, egid, sgid) ,rgid
#define __NRATRF1_getresgid32                "%p"
#define __NRATRA1_getresgid32(rgid, egid, sgid) ,egid
#define __NRATRF2_getresgid32                "%p"
#define __NRATRA2_getresgid32(rgid, egid, sgid) ,sgid
#define __NRATRF0_chown32                    "%q"
#define __NRATRA0_chown32(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_chown32                    "%I32u"
#define __NRATRA1_chown32(filename, owner, group) ,owner
#define __NRATRF2_chown32                    "%I32u"
#define __NRATRA2_chown32(filename, owner, group) ,group
#define __NRATRF0_setuid32                   "%I32u"
#define __NRATRA0_setuid32(uid)              ,uid
#define __NRATRF0_setgid32                   "%I32u"
#define __NRATRA0_setgid32(gid)              ,gid
#define __NRATRF0_setfsuid32                 "%I32u"
#define __NRATRA0_setfsuid32(uid)            ,uid
#define __NRATRF0_setfsgid32                 "%I32u"
#define __NRATRA0_setfsgid32(gid)            ,gid
#define __NRATRF0_mincore                    "%p"
#define __NRATRA0_mincore(start, len, vec)   ,start
#define __NRATRF1_mincore                    "%Iu"
#define __NRATRA1_mincore(start, len, vec)   ,len
#define __NRATRF2_mincore                    "%p"
#define __NRATRA2_mincore(start, len, vec)   ,vec
#define __NRATRF0_madvise                    "%p"
#define __NRATRA0_madvise(addr, len, advice) ,addr
#define __NRATRF1_madvise                    "%Iu"
#define __NRATRA1_madvise(addr, len, advice) ,len
#define __NRATRF2_madvise                    "%#Ix"
#define __NRATRA2_madvise(addr, len, advice) ,(uintptr_t)(advice)
#define __NRATRF0_getdents64                 "%d"
#define __NRATRA0_getdents64(fd, dirp, count) ,(int)(fd)
#define __NRATRF1_getdents64                 "%p"
#define __NRATRA1_getdents64(fd, dirp, count) ,dirp
#define __NRATRF2_getdents64                 "%Iu"
#define __NRATRA2_getdents64(fd, dirp, count) ,count
#define __NRATRF0_fcntl64                    "%d"
#define __NRATRA0_fcntl64(fd, command, arg)  ,(int)(fd)
#define __NRATRF1_fcntl64                    "%#Ix"
#define __NRATRA1_fcntl64(fd, command, arg)  ,(uintptr_t)(command)
#define __NRATRF2_fcntl64                    "%p"
#define __NRATRA2_fcntl64(fd, command, arg)  ,arg
#define __NRATRF0_readahead                  "%d"
#define __NRATRA0_readahead(fd, offset, count) ,(int)(fd)
#define __NRATRF1_readahead                  "%I64u"
#define __NRATRA1_readahead(fd, offset, count) ,offset
#define __NRATRF2_readahead                  "%Iu"
#define __NRATRA2_readahead(fd, offset, count) ,count
#define __NRATRF0_setxattr                   "%q"
#define __NRATRA0_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NRATRF1_setxattr                   "%q"
#define __NRATRA1_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_setxattr                   "%p"
#define __NRATRA2_setxattr(path, name, buf, bufsize, flags) ,buf
#define __NRATRF3_setxattr                   "%Iu"
#define __NRATRA3_setxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NRATRF4_setxattr                   "%#Ix"
#define __NRATRA4_setxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NRATRF0_lsetxattr                  "%q"
#define __NRATRA0_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NRATRF1_lsetxattr                  "%q"
#define __NRATRA1_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_lsetxattr                  "%p"
#define __NRATRA2_lsetxattr(path, name, buf, bufsize, flags) ,buf
#define __NRATRF3_lsetxattr                  "%Iu"
#define __NRATRA3_lsetxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NRATRF4_lsetxattr                  "%#Ix"
#define __NRATRA4_lsetxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NRATRF0_fsetxattr                  "%d"
#define __NRATRA0_fsetxattr(fd, name, buf, bufsize, flags) ,(int)(fd)
#define __NRATRF1_fsetxattr                  "%q"
#define __NRATRA1_fsetxattr(fd, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_fsetxattr                  "%p"
#define __NRATRA2_fsetxattr(fd, name, buf, bufsize, flags) ,buf
#define __NRATRF3_fsetxattr                  "%Iu"
#define __NRATRA3_fsetxattr(fd, name, buf, bufsize, flags) ,bufsize
#define __NRATRF4_fsetxattr                  "%#Ix"
#define __NRATRA4_fsetxattr(fd, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NRATRF0_getxattr                   "%q"
#define __NRATRA0_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NRATRF1_getxattr                   "%q"
#define __NRATRA1_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_getxattr                   "%p"
#define __NRATRA2_getxattr(path, name, buf, bufsize) ,buf
#define __NRATRF3_getxattr                   "%Iu"
#define __NRATRA3_getxattr(path, name, buf, bufsize) ,bufsize
#define __NRATRF0_lgetxattr                  "%q"
#define __NRATRA0_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NRATRF1_lgetxattr                  "%q"
#define __NRATRA1_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_lgetxattr                  "%p"
#define __NRATRA2_lgetxattr(path, name, buf, bufsize) ,buf
#define __NRATRF3_lgetxattr                  "%Iu"
#define __NRATRA3_lgetxattr(path, name, buf, bufsize) ,bufsize
#define __NRATRF0_fgetxattr                  "%d"
#define __NRATRA0_fgetxattr(fd, name, buf, bufsize) ,(int)(fd)
#define __NRATRF1_fgetxattr                  "%q"
#define __NRATRA1_fgetxattr(fd, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_fgetxattr                  "%p"
#define __NRATRA2_fgetxattr(fd, name, buf, bufsize) ,buf
#define __NRATRF3_fgetxattr                  "%Iu"
#define __NRATRA3_fgetxattr(fd, name, buf, bufsize) ,bufsize
#define __NRATRF0_listxattr                  "%q"
#define __NRATRA0_listxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NRATRF1_listxattr                  "%p"
#define __NRATRA1_listxattr(path, listbuf, listbufsize) ,listbuf
#define __NRATRF2_listxattr                  "%Iu"
#define __NRATRA2_listxattr(path, listbuf, listbufsize) ,listbufsize
#define __NRATRF0_llistxattr                 "%q"
#define __NRATRA0_llistxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NRATRF1_llistxattr                 "%p"
#define __NRATRA1_llistxattr(path, listbuf, listbufsize) ,listbuf
#define __NRATRF2_llistxattr                 "%Iu"
#define __NRATRA2_llistxattr(path, listbuf, listbufsize) ,listbufsize
#define __NRATRF0_flistxattr                 "%d"
#define __NRATRA0_flistxattr(fd, listbuf, listbufsize) ,(int)(fd)
#define __NRATRF1_flistxattr                 "%p"
#define __NRATRA1_flistxattr(fd, listbuf, listbufsize) ,listbuf
#define __NRATRF2_flistxattr                 "%Iu"
#define __NRATRA2_flistxattr(fd, listbuf, listbufsize) ,listbufsize
#define __NRATRF0_removexattr                "%q"
#define __NRATRA0_removexattr(path, name)    ,(validate_readable_opt(path,1),path)
#define __NRATRF1_removexattr                "%q"
#define __NRATRA1_removexattr(path, name)    ,(validate_readable_opt(name,1),name)
#define __NRATRF0_lremovexattr               "%q"
#define __NRATRA0_lremovexattr(path, name)   ,(validate_readable_opt(path,1),path)
#define __NRATRF1_lremovexattr               "%q"
#define __NRATRA1_lremovexattr(path, name)   ,(validate_readable_opt(name,1),name)
#define __NRATRF0_fremovexattr               "?"
#define __NRATRA0_fremovexattr(fd, name)     /* nothing */
#define __NRATRF1_fremovexattr               "%q"
#define __NRATRA1_fremovexattr(fd, name)     ,(validate_readable_opt(name,1),name)
#define __NRATRF0_tkill                      "%Id"
#define __NRATRA0_tkill(tid, signo)          ,(intptr_t)(tid)
#define __NRATRF1_tkill                      "%#Ix"
#define __NRATRA1_tkill(tid, signo)          ,(uintptr_t)(signo)
#define __NRATRF0_sendfile64                 "%d"
#define __NRATRA0_sendfile64(out_fd, in_fd, offset, count) ,(int)(out_fd)
#define __NRATRF1_sendfile64                 "%d"
#define __NRATRA1_sendfile64(out_fd, in_fd, offset, count) ,(int)(in_fd)
#define __NRATRF2_sendfile64                 "%p"
#define __NRATRA2_sendfile64(out_fd, in_fd, offset, count) ,offset
#define __NRATRF3_sendfile64                 "%Iu"
#define __NRATRA3_sendfile64(out_fd, in_fd, offset, count) ,count
#define __NRATRF0_futex                      "%p"
#define __NRATRA0_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr
#define __NRATRF1_futex                      "%#Ix"
#define __NRATRA1_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,(uintptr_t)(futex_op)
#define __NRATRF2_futex                      "%I32u"
#define __NRATRA2_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val
#define __NRATRF3_futex                      "%p"
#define __NRATRA3_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,timeout_or_val2
#define __NRATRF4_futex                      "%p"
#define __NRATRA4_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr2
#define __NRATRF5_futex                      "%I32u"
#define __NRATRA5_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val3
#define __NRATRF0_sched_setaffinity          "%Id"
#define __NRATRA0_sched_setaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NRATRF1_sched_setaffinity          "%Iu"
#define __NRATRA1_sched_setaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NRATRF2_sched_setaffinity          "%p"
#define __NRATRA2_sched_setaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NRATRF0_sched_getaffinity          "%Id"
#define __NRATRA0_sched_getaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NRATRF1_sched_getaffinity          "%Iu"
#define __NRATRA1_sched_getaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NRATRF2_sched_getaffinity          "%p"
#define __NRATRA2_sched_getaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NRATRF0_exit_group                 "%Iu"
#define __NRATRA0_exit_group(exit_code)      ,(uintptr_t)(exit_code)
#define __NRATRF0_epoll_create               "%#Ix"
#define __NRATRA0_epoll_create(size)         ,(uintptr_t)(size)
#define __NRATRF0_epoll_ctl                  "%d"
#define __NRATRA0_epoll_ctl(epfd, op, fd, event) ,(int)(epfd)
#define __NRATRF1_epoll_ctl                  "%#Ix=%s"
#define __NRATRA1_epoll_ctl(epfd, op, fd, event) ,(op),(op) == EPOLL_CTL_ADD ? "EPOLL_CTL_ADD" : (op) == EPOLL_CTL_DEL ? "EPOLL_CTL_DEL" : (op) == EPOLL_CTL_MOD ? "EPOLL_CTL_MOD" : "?"
#define __NRATRF2_epoll_ctl                  "%d"
#define __NRATRA2_epoll_ctl(epfd, op, fd, event) ,(int)(fd)
#define __NRATRF3_epoll_ctl                  "%p"
#define __NRATRA3_epoll_ctl(epfd, op, fd, event) ,event
#define __NRATRF0_epoll_wait                 "%d"
#define __NRATRA0_epoll_wait(epfd, events, maxevents, timeout) ,(int)(epfd)
#define __NRATRF1_epoll_wait                 "%p"
#define __NRATRA1_epoll_wait(epfd, events, maxevents, timeout) ,events
#define __NRATRF2_epoll_wait                 "%#Ix"
#define __NRATRA2_epoll_wait(epfd, events, maxevents, timeout) ,(uintptr_t)(maxevents)
#define __NRATRF3_epoll_wait                 "%Id"
#define __NRATRA3_epoll_wait(epfd, events, maxevents, timeout) ,(intptr_t)(timeout)
#define __NRATRF0_remap_file_pages           "%p"
#define __NRATRA0_remap_file_pages(start, size, prot, pgoff, flags) ,start
#define __NRATRF1_remap_file_pages           "%Iu"
#define __NRATRA1_remap_file_pages(start, size, prot, pgoff, flags) ,size
#define __NRATRF2_remap_file_pages           "%#Ix"
#define __NRATRA2_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(prot)
#define __NRATRF3_remap_file_pages           "%Iu"
#define __NRATRA3_remap_file_pages(start, size, prot, pgoff, flags) ,pgoff
#define __NRATRF4_remap_file_pages           "%#Ix"
#define __NRATRA4_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(flags)
#define __NRATRF0_set_tid_address            "%p"
#define __NRATRA0_set_tid_address(tidptr)    ,tidptr
#define __NRATRF0_timer_create               "?"
#define __NRATRA0_timer_create(clock_id, evp, timerid) /* nothing */
#define __NRATRF1_timer_create               "%p"
#define __NRATRA1_timer_create(clock_id, evp, timerid) ,evp
#define __NRATRF2_timer_create               "%p"
#define __NRATRA2_timer_create(clock_id, evp, timerid) ,timerid
#define __NRATRF0_timer_settime              "?"
#define __NRATRA0_timer_settime(timerid, flags, value, ovalue) /* nothing */
#define __NRATRF1_timer_settime              "%#Ix"
#define __NRATRA1_timer_settime(timerid, flags, value, ovalue) ,(uintptr_t)(flags)
#define __NRATRF2_timer_settime              "%p"
#define __NRATRA2_timer_settime(timerid, flags, value, ovalue) ,value
#define __NRATRF3_timer_settime              "%p"
#define __NRATRA3_timer_settime(timerid, flags, value, ovalue) ,ovalue
#define __NRATRF0_timer_gettime              "?"
#define __NRATRA0_timer_gettime(timerid, value) /* nothing */
#define __NRATRF1_timer_gettime              "%p"
#define __NRATRA1_timer_gettime(timerid, value) ,value
#define __NRATRF0_timer_getoverrun           "?"
#define __NRATRA0_timer_getoverrun(timerid)  /* nothing */
#define __NRATRF0_timer_delete               "?"
#define __NRATRA0_timer_delete(timerid)      /* nothing */
#define __NRATRF0_clock_settime              "?"
#define __NRATRA0_clock_settime(clock_id, tp) /* nothing */
#define __NRATRF1_clock_settime              "%p"
#define __NRATRA1_clock_settime(clock_id, tp) ,tp
#define __NRATRF0_clock_gettime              "?"
#define __NRATRA0_clock_gettime(clock_id, tp) /* nothing */
#define __NRATRF1_clock_gettime              "%p"
#define __NRATRA1_clock_gettime(clock_id, tp) ,tp
#define __NRATRF0_clock_getres               "?"
#define __NRATRA0_clock_getres(clock_id, res) /* nothing */
#define __NRATRF1_clock_getres               "%p"
#define __NRATRA1_clock_getres(clock_id, res) ,res
#define __NRATRF0_clock_nanosleep            "?"
#define __NRATRA0_clock_nanosleep(clock_id, flags, requested_time, remaining) /* nothing */
#define __NRATRF1_clock_nanosleep            "%#Ix"
#define __NRATRA1_clock_nanosleep(clock_id, flags, requested_time, remaining) ,(uintptr_t)(flags)
#define __NRATRF2_clock_nanosleep            "%p"
#define __NRATRA2_clock_nanosleep(clock_id, flags, requested_time, remaining) ,requested_time
#define __NRATRF3_clock_nanosleep            "%p"
#define __NRATRA3_clock_nanosleep(clock_id, flags, requested_time, remaining) ,remaining
#define __NRATRF0_statfs64                   "%q"
#define __NRATRA0_statfs64(file, buf)        ,(validate_readable_opt(file,1),file)
#define __NRATRF1_statfs64                   "%p"
#define __NRATRA1_statfs64(file, buf)        ,buf
#define __NRATRF0_fstatfs64                  "%d"
#define __NRATRA0_fstatfs64(file, buf)       ,(int)(file)
#define __NRATRF1_fstatfs64                  "%p"
#define __NRATRA1_fstatfs64(file, buf)       ,buf
#define __NRATRF0_tgkill                     "%Id"
#define __NRATRA0_tgkill(tgid, tid, signo)   ,(intptr_t)(tgid)
#define __NRATRF1_tgkill                     "%Id"
#define __NRATRA1_tgkill(tgid, tid, signo)   ,(intptr_t)(tid)
#define __NRATRF2_tgkill                     "%#Ix"
#define __NRATRA2_tgkill(tgid, tid, signo)   ,(uintptr_t)(signo)
#define __NRATRF0_utimes                     "%q"
#define __NRATRA0_utimes(filename, times)    ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_utimes                     "%p"
#define __NRATRA1_utimes(filename, times)    ,times
#define __NRATRF0_waitid                     "%#Ix=%s"
#define __NRATRA0_waitid(idtype, id, infop, options, ru) ,(idtype),(idtype) == P_ALL ? "P_ALL" : (idtype) == P_PID ? "P_PID" : (idtype) == P_PGID ? "P_PGID" : "?"
#define __NRATRF1_waitid                     "%Iu"
#define __NRATRA1_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(id)
#define __NRATRF2_waitid                     "%p"
#define __NRATRA2_waitid(idtype, id, infop, options, ru) ,infop
#define __NRATRF3_waitid                     "%#Ix=%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(options),(options) & WEXITED ? "WEXITED" : "" \
                                                         ,((options) & WSTOPPED) && ((options) & (WEXITED)) ? "|" : "",(options) & WSTOPPED ? "WSTOPPED" : "" \
                                                         ,((options) & WCONTINUED) && ((options) & (WEXITED|WSTOPPED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                         ,((options) & WNOHANG) && ((options) & (WEXITED|WSTOPPED|WCONTINUED)) ? "|" : "",(options) & WNOHANG ? "WNOHANG" : "" \
                                                         ,((options) & WNOWAIT) && ((options) & (WEXITED|WSTOPPED|WCONTINUED|WNOHANG)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF4_waitid                     "%p"
#define __NRATRA4_waitid(idtype, id, infop, options, ru) ,ru
#define __NRATRF0_ioprio_set                 "%#Ix"
#define __NRATRA0_ioprio_set(which, who, ioprio) ,(uintptr_t)(which)
#define __NRATRF1_ioprio_set                 "%#Ix"
#define __NRATRA1_ioprio_set(which, who, ioprio) ,(uintptr_t)(who)
#define __NRATRF2_ioprio_set                 "%#Ix"
#define __NRATRA2_ioprio_set(which, who, ioprio) ,(uintptr_t)(ioprio)
#define __NRATRF0_ioprio_get                 "%#Ix"
#define __NRATRA0_ioprio_get(which, who)     ,(uintptr_t)(which)
#define __NRATRF1_ioprio_get                 "%#Ix"
#define __NRATRA1_ioprio_get(which, who)     ,(uintptr_t)(who)
#define __NRATRF0_openat                     "%d"
#define __NRATRA0_openat(dirfd, filename, oflags, mode) ,(int)(dirfd)
#define __NRATRF1_openat                     "%q"
#define __NRATRA1_openat(dirfd, filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_openat                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
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
#define __NRATRF3_openat                     "%#Io"
#define __NRATRA3_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(mode)
#define __NRATRF0_mkdirat                    "%d"
#define __NRATRA0_mkdirat(dirfd, pathname, mode) ,(int)(dirfd)
#define __NRATRF1_mkdirat                    "%q"
#define __NRATRA1_mkdirat(dirfd, pathname, mode) ,(validate_readable_opt(pathname,1),pathname)
#define __NRATRF2_mkdirat                    "%#Io"
#define __NRATRA2_mkdirat(dirfd, pathname, mode) ,(uintptr_t)(mode)
#define __NRATRF0_mknodat                    "%d"
#define __NRATRA0_mknodat(dirfd, nodename, mode, dev) ,(int)(dirfd)
#define __NRATRF1_mknodat                    "%q"
#define __NRATRA1_mknodat(dirfd, nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NRATRF2_mknodat                    "%#Io"
#define __NRATRA2_mknodat(dirfd, nodename, mode, dev) ,(uintptr_t)(mode)
#define __NRATRF3_mknodat                    "%.2x:%.2x"
#define __NRATRA3_mknodat(dirfd, nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF0_fchownat                   "%d"
#define __NRATRA0_fchownat(dirfd, filename, owner, group, flags) ,(int)(dirfd)
#define __NRATRF1_fchownat                   "%q"
#define __NRATRA1_fchownat(dirfd, filename, owner, group, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_fchownat                   "%I32u"
#define __NRATRA2_fchownat(dirfd, filename, owner, group, flags) ,owner
#define __NRATRF3_fchownat                   "%I32u"
#define __NRATRA3_fchownat(dirfd, filename, owner, group, flags) ,group
#define __NRATRF4_fchownat                   "%#Ix=%s%s%s"
#define __NRATRA4_fchownat(dirfd, filename, owner, group, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_futimesat                  "%d"
#define __NRATRA0_futimesat(dirfd, filename, times) ,(int)(dirfd)
#define __NRATRF1_futimesat                  "%p"
#define __NRATRA1_futimesat(dirfd, filename, times) ,filename
#define __NRATRF2_futimesat                  "%p"
#define __NRATRA2_futimesat(dirfd, filename, times) ,times
#define __NRATRF0_linux_fstatat64            "%d"
#define __NRATRA0_linux_fstatat64(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NRATRF1_linux_fstatat64            "%q"
#define __NRATRA1_linux_fstatat64(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_linux_fstatat64            "%p"
#define __NRATRA2_linux_fstatat64(dirfd, filename, statbuf, flags) ,statbuf
#define __NRATRF3_linux_fstatat64            "%#Ix=%s%s%s"
#define __NRATRA3_linux_fstatat64(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_unlinkat                   "%d"
#define __NRATRA0_unlinkat(dirfd, name, flags) ,(int)(dirfd)
#define __NRATRF1_unlinkat                   "%q"
#define __NRATRA1_unlinkat(dirfd, name, flags) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_unlinkat                   "%#Ix=%s%s%s%s%s"
#define __NRATRA2_unlinkat(dirfd, name, flags) ,(uintptr_t)(flags),(flags) & AT_REMOVEDIR ? "AT_REMOVEDIR" : "" \
                                               ,((flags) & AT_REMOVEREG) && ((flags) & (AT_REMOVEDIR)) ? "|" : "",(flags) & AT_REMOVEREG ? "AT_REMOVEREG" : "" \
                                               ,((flags) & AT_DOSPATH) && ((flags) & (AT_REMOVEDIR|AT_REMOVEREG)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_renameat                   "%d"
#define __NRATRA0_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(oldfd)
#define __NRATRF1_renameat                   "%q"
#define __NRATRA1_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NRATRF2_renameat                   "%d"
#define __NRATRA2_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(newfd)
#define __NRATRF3_renameat                   "%q"
#define __NRATRA3_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NRATRF0_linkat                     "%d"
#define __NRATRA0_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(fromfd)
#define __NRATRF1_linkat                     "%q"
#define __NRATRA1_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NRATRF2_linkat                     "%d"
#define __NRATRA2_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(tofd)
#define __NRATRF3_linkat                     "%q"
#define __NRATRA3_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NRATRF4_linkat                     "%#Ix=%s%s%s%s%s"
#define __NRATRA4_linkat(fromfd, existing_file, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                          ,((flags) & AT_SYMLINK_FOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_FOLLOW ? "AT_SYMLINK_FOLLOW" : "" \
                                                                          ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_FOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_symlinkat                  "%q"
#define __NRATRA0_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NRATRF1_symlinkat                  "%d"
#define __NRATRA1_symlinkat(link_text, tofd, target_path) ,(int)(tofd)
#define __NRATRF2_symlinkat                  "%q"
#define __NRATRA2_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NRATRF0_readlinkat                 "%d"
#define __NRATRA0_readlinkat(dirfd, path, buf, buflen) ,(int)(dirfd)
#define __NRATRF1_readlinkat                 "%q"
#define __NRATRA1_readlinkat(dirfd, path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NRATRF2_readlinkat                 "%p"
#define __NRATRA2_readlinkat(dirfd, path, buf, buflen) ,buf
#define __NRATRF3_readlinkat                 "%Iu"
#define __NRATRA3_readlinkat(dirfd, path, buf, buflen) ,buflen
#define __NRATRF0_fchmodat                   "%d"
#define __NRATRA0_fchmodat(dirfd, filename, mode, flags) ,(int)(dirfd)
#define __NRATRF1_fchmodat                   "%q"
#define __NRATRA1_fchmodat(dirfd, filename, mode, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_fchmodat                   "%#Io"
#define __NRATRA2_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(mode)
#define __NRATRF3_fchmodat                   "%#Ix=%s%s%s"
#define __NRATRA3_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                         ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_faccessat                  "%d"
#define __NRATRA0_faccessat(dirfd, filename, type, flags) ,(int)(dirfd)
#define __NRATRF1_faccessat                  "%q"
#define __NRATRA1_faccessat(dirfd, filename, type, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_faccessat                  "%#Ix=%s%s%s%s%s"
#define __NRATRA2_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                                          ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                                          ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NRATRF3_faccessat                  "%#Ix=%s%s%s%s%s"
#define __NRATRA3_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                          ,((flags) & AT_EACCESS) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_EACCESS ? "AT_EACCESS" : "" \
                                                          ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_EACCESS)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_pselect6                   "%Iu"
#define __NRATRA0_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,nfds
#define __NRATRF1_pselect6                   "%p"
#define __NRATRA1_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,readfds
#define __NRATRF2_pselect6                   "%p"
#define __NRATRA2_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,writefds
#define __NRATRF3_pselect6                   "%p"
#define __NRATRA3_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,exceptfds
#define __NRATRF4_pselect6                   "%p"
#define __NRATRA4_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,timeout
#define __NRATRF5_pselect6                   "%p"
#define __NRATRA5_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,sigmask_sigset_and_len
#define __NRATRF0_ppoll                      "%p"
#define __NRATRA0_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,fds
#define __NRATRF1_ppoll                      "%Iu"
#define __NRATRA1_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,nfds
#define __NRATRF2_ppoll                      "%p"
#define __NRATRA2_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,timeout_ts
#define __NRATRF3_ppoll                      "%p"
#define __NRATRA3_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigmask
#define __NRATRF4_ppoll                      "%Iu"
#define __NRATRA4_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigsetsize
#define __NRATRF0_unshare                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA0_unshare(flags)             ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
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
#define __NRATRF0_splice                     "%d"
#define __NRATRA0_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdin)
#define __NRATRF1_splice                     "%p"
#define __NRATRA1_splice(fdin, offin, fdout, offout, length, flags) ,offin
#define __NRATRF2_splice                     "%d"
#define __NRATRA2_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdout)
#define __NRATRF3_splice                     "%p"
#define __NRATRA3_splice(fdin, offin, fdout, offout, length, flags) ,offout
#define __NRATRF4_splice                     "%Iu"
#define __NRATRA4_splice(fdin, offin, fdout, offout, length, flags) ,length
#define __NRATRF5_splice                     "%#Ix"
#define __NRATRA5_splice(fdin, offin, fdout, offout, length, flags) ,(uintptr_t)(flags)
#define __NRATRF0_sync_file_range            "%d"
#define __NRATRA0_sync_file_range(fd, offset, count, flags) ,(int)(fd)
#define __NRATRF1_sync_file_range            "%I64u"
#define __NRATRA1_sync_file_range(fd, offset, count, flags) ,offset
#define __NRATRF2_sync_file_range            "%I64u"
#define __NRATRA2_sync_file_range(fd, offset, count, flags) ,count
#define __NRATRF3_sync_file_range            "%#Ix"
#define __NRATRA3_sync_file_range(fd, offset, count, flags) ,(uintptr_t)(flags)
#define __NRATRF0_tee                        "%d"
#define __NRATRA0_tee(fdin, fdout, length, flags) ,(int)(fdin)
#define __NRATRF1_tee                        "%d"
#define __NRATRA1_tee(fdin, fdout, length, flags) ,(int)(fdout)
#define __NRATRF2_tee                        "%Iu"
#define __NRATRA2_tee(fdin, fdout, length, flags) ,length
#define __NRATRF3_tee                        "%#Ix"
#define __NRATRA3_tee(fdin, fdout, length, flags) ,(uintptr_t)(flags)
#define __NRATRF0_vmsplice                   "%d"
#define __NRATRA0_vmsplice(fdout, iov, count, flags) ,(int)(fdout)
#define __NRATRF1_vmsplice                   "%p"
#define __NRATRA1_vmsplice(fdout, iov, count, flags) ,iov
#define __NRATRF2_vmsplice                   "%Iu"
#define __NRATRA2_vmsplice(fdout, iov, count, flags) ,count
#define __NRATRF3_vmsplice                   "%#Ix"
#define __NRATRA3_vmsplice(fdout, iov, count, flags) ,(uintptr_t)(flags)
#define __NRATRF0_getcpu                     "%p"
#define __NRATRA0_getcpu(cpu, node, tcache)  ,cpu
#define __NRATRF1_getcpu                     "%p"
#define __NRATRA1_getcpu(cpu, node, tcache)  ,node
#define __NRATRF2_getcpu                     "%p"
#define __NRATRA2_getcpu(cpu, node, tcache)  ,tcache
#define __NRATRF0_epoll_pwait                "%d"
#define __NRATRA0_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(int)(epfd)
#define __NRATRF1_epoll_pwait                "%p"
#define __NRATRA1_epoll_pwait(epfd, events, maxevents, timeout, ss) ,events
#define __NRATRF2_epoll_pwait                "%#Ix"
#define __NRATRA2_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(uintptr_t)(maxevents)
#define __NRATRF3_epoll_pwait                "%Id"
#define __NRATRA3_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(intptr_t)(timeout)
#define __NRATRF4_epoll_pwait                "%p"
#define __NRATRA4_epoll_pwait(epfd, events, maxevents, timeout, ss) ,ss
#define __NRATRF0_utimensat                  "%d"
#define __NRATRA0_utimensat(dirfd, filename, times, flags) ,(int)(dirfd)
#define __NRATRF1_utimensat                  "%q"
#define __NRATRA1_utimensat(dirfd, filename, times, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_utimensat                  "%p"
#define __NRATRA2_utimensat(dirfd, filename, times, flags) ,times
#define __NRATRF3_utimensat                  "%#Ix=%s%s%s%s%s"
#define __NRATRA3_utimensat(dirfd, filename, times, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                           ,((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                           ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_timerfd_create             "?"
#define __NRATRA0_timerfd_create(clock_id, flags) /* nothing */
#define __NRATRF1_timerfd_create             "%#Ix"
#define __NRATRA1_timerfd_create(clock_id, flags) ,(uintptr_t)(flags)
#define __NRATRF0_eventfd                    "%#Ix"
#define __NRATRA0_eventfd(initval)           ,(uintptr_t)(initval)
#define __NRATRF0_fallocate                  "%d"
#define __NRATRA0_fallocate(fd, mode, offset, length) ,(int)(fd)
#define __NRATRF1_fallocate                  "%#Ix"
#define __NRATRA1_fallocate(fd, mode, offset, length) ,(uintptr_t)(mode)
#define __NRATRF2_fallocate                  "%I32u"
#define __NRATRA2_fallocate(fd, mode, offset, length) ,offset
#define __NRATRF3_fallocate                  "%I32u"
#define __NRATRA3_fallocate(fd, mode, offset, length) ,length
#define __NRATRF0_timerfd_settime            "%d"
#define __NRATRA0_timerfd_settime(ufd, flags, utmr, otmr) ,(int)(ufd)
#define __NRATRF1_timerfd_settime            "%#Ix"
#define __NRATRA1_timerfd_settime(ufd, flags, utmr, otmr) ,(uintptr_t)(flags)
#define __NRATRF2_timerfd_settime            "%p"
#define __NRATRA2_timerfd_settime(ufd, flags, utmr, otmr) ,utmr
#define __NRATRF3_timerfd_settime            "%p"
#define __NRATRA3_timerfd_settime(ufd, flags, utmr, otmr) ,otmr
#define __NRATRF0_timerfd_gettime            "%d"
#define __NRATRA0_timerfd_gettime(ufd, otmr) ,(int)(ufd)
#define __NRATRF1_timerfd_gettime            "%p"
#define __NRATRA1_timerfd_gettime(ufd, otmr) ,otmr
#define __NRATRF0_eventfd2                   "%#Ix"
#define __NRATRA0_eventfd2(initval, flags)   ,(uintptr_t)(initval)
#define __NRATRF1_eventfd2                   "%#Ix=%s%s%s%s%s"
#define __NRATRA1_eventfd2(initval, flags)   ,(uintptr_t)(flags),(flags) & EFD_SEMAPHORE ? "EFD_SEMAPHORE" : "" \
                                             ,((flags) & EFD_NONBLOCK) && ((flags) & (EFD_SEMAPHORE)) ? "|" : "",(flags) & EFD_NONBLOCK ? "EFD_NONBLOCK" : "" \
                                             ,((flags) & EFD_CLOEXEC) && ((flags) & (EFD_SEMAPHORE|EFD_NONBLOCK)) ? "|" : "",(flags) & EFD_CLOEXEC ? "EFD_CLOEXEC" : ""
#define __NRATRF0_epoll_create1              "%#Ix"
#define __NRATRA0_epoll_create1(flags)       ,(uintptr_t)(flags)
#define __NRATRF0_dup3                       "%d"
#define __NRATRA0_dup3(oldfd, newfd, flags)  ,(int)(oldfd)
#define __NRATRF1_dup3                       "%d"
#define __NRATRA1_dup3(oldfd, newfd, flags)  ,(int)(newfd)
#define __NRATRF2_dup3                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_dup3(oldfd, newfd, flags)  ,(uintptr_t)(flags),(flags) & O_WRONLY ? "O_WRONLY" : (flags) ? "" : "O_RDONLY" \
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
#define __NRATRF0_pipe2                      "%p"
#define __NRATRA0_pipe2(pipedes, flags)      ,pipedes
#define __NRATRF1_pipe2                      "%#Ix=%s%s%s%s%s%s%s"
#define __NRATRA1_pipe2(pipedes, flags)      ,(uintptr_t)(flags),(flags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                             ,((flags) & O_CLOFORK) && ((flags) & (O_CLOEXEC)) ? "|" : "",(flags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                             ,((flags) & O_NONBLOCK) && ((flags) & (O_CLOEXEC|O_CLOFORK)) ? "|" : "",(flags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                             ,((flags) & O_DIRECT) && ((flags) & (O_CLOEXEC|O_CLOFORK|O_NONBLOCK)) ? "|" : "",(flags) & O_DIRECT ? "O_DIRECT" : ""
#define __NRATRF0_preadv                     "%d"
#define __NRATRA0_preadv(fd, iovec, count, offset) ,(int)(fd)
#define __NRATRF1_preadv                     "%p"
#define __NRATRA1_preadv(fd, iovec, count, offset) ,iovec
#define __NRATRF2_preadv                     "%Iu"
#define __NRATRA2_preadv(fd, iovec, count, offset) ,count
#define __NRATRF3_preadv                     "%I64u"
#define __NRATRA3_preadv(fd, iovec, count, offset) ,offset
#define __NRATRF0_pwritev                    "%d"
#define __NRATRA0_pwritev(fd, iovec, count, offset) ,(int)(fd)
#define __NRATRF1_pwritev                    "%p"
#define __NRATRA1_pwritev(fd, iovec, count, offset) ,iovec
#define __NRATRF2_pwritev                    "%Iu"
#define __NRATRA2_pwritev(fd, iovec, count, offset) ,count
#define __NRATRF3_pwritev                    "%I64u"
#define __NRATRA3_pwritev(fd, iovec, count, offset) ,offset
#define __NRATRF0_rt_tgsigqueueinfo          "%Id"
#define __NRATRA0_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tgid)
#define __NRATRF1_rt_tgsigqueueinfo          "%Id"
#define __NRATRA1_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tid)
#define __NRATRF2_rt_tgsigqueueinfo          "%#Ix"
#define __NRATRA2_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(uintptr_t)(signo)
#define __NRATRF3_rt_tgsigqueueinfo          "%p"
#define __NRATRA3_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,uinfo
#define __NRATRF0_recvmmsg                   "%d"
#define __NRATRA0_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(int)(sockfd)
#define __NRATRF1_recvmmsg                   "%p"
#define __NRATRA1_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vmessages
#define __NRATRF2_recvmmsg                   "%Iu"
#define __NRATRA2_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vlen
#define __NRATRF3_recvmmsg                   "%#Ix"
#define __NRATRA3_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(uintptr_t)(flags)
#define __NRATRF4_recvmmsg                   "%p"
#define __NRATRA4_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,tmo
#define __NRATRF0_prlimit64                  "%Id"
#define __NRATRA0_prlimit64(pid, resource, new_limit, old_limit) ,(intptr_t)(pid)
#define __NRATRF1_prlimit64                  "%#Ix"
#define __NRATRA1_prlimit64(pid, resource, new_limit, old_limit) ,(uintptr_t)(resource)
#define __NRATRF2_prlimit64                  "%p"
#define __NRATRA2_prlimit64(pid, resource, new_limit, old_limit) ,new_limit
#define __NRATRF3_prlimit64                  "%p"
#define __NRATRA3_prlimit64(pid, resource, new_limit, old_limit) ,old_limit
#define __NRATRF0_name_to_handle_at          "%d"
#define __NRATRA0_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(int)(dirfd)
#define __NRATRF1_name_to_handle_at          "%q"
#define __NRATRA1_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(validate_readable_opt(name,1),name)
#define __NRATRF2_name_to_handle_at          "%p"
#define __NRATRA2_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,handle
#define __NRATRF3_name_to_handle_at          "%p"
#define __NRATRA3_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,mnt_id
#define __NRATRF4_name_to_handle_at          "%#Ix"
#define __NRATRA4_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(uintptr_t)(flags)
#define __NRATRF0_open_by_handle_at          "%d"
#define __NRATRA0_open_by_handle_at(mountdirfd, handle, flags) ,(int)(mountdirfd)
#define __NRATRF1_open_by_handle_at          "%p"
#define __NRATRA1_open_by_handle_at(mountdirfd, handle, flags) ,handle
#define __NRATRF2_open_by_handle_at          "%#Ix"
#define __NRATRA2_open_by_handle_at(mountdirfd, handle, flags) ,(uintptr_t)(flags)
#define __NRATRF0_syncfs                     "%d"
#define __NRATRA0_syncfs(fd)                 ,(int)(fd)
#define __NRATRF0_sendmmsg                   "%d"
#define __NRATRA0_sendmmsg(sockfd, vmessages, vlen, flags) ,(int)(sockfd)
#define __NRATRF1_sendmmsg                   "%p"
#define __NRATRA1_sendmmsg(sockfd, vmessages, vlen, flags) ,vmessages
#define __NRATRF2_sendmmsg                   "%Iu"
#define __NRATRA2_sendmmsg(sockfd, vmessages, vlen, flags) ,vlen
#define __NRATRF3_sendmmsg                   "%#Ix"
#define __NRATRA3_sendmmsg(sockfd, vmessages, vlen, flags) ,(uintptr_t)(flags)
#define __NRATRF0_setns                      "%d"
#define __NRATRA0_setns(fd, nstype)          ,(int)(fd)
#define __NRATRF1_setns                      "%#Ix"
#define __NRATRA1_setns(fd, nstype)          ,(uintptr_t)(nstype)
#define __NRATRF0_process_vm_readv           "%Id"
#define __NRATRA0_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NRATRF1_process_vm_readv           "%p"
#define __NRATRA1_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NRATRF2_process_vm_readv           "%Iu"
#define __NRATRA2_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NRATRF3_process_vm_readv           "%p"
#define __NRATRA3_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NRATRF4_process_vm_readv           "%Iu"
#define __NRATRA4_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NRATRF5_process_vm_readv           "%#Ix"
#define __NRATRA5_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NRATRF0_process_vm_writev          "%Id"
#define __NRATRA0_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NRATRF1_process_vm_writev          "%p"
#define __NRATRA1_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NRATRF2_process_vm_writev          "%Iu"
#define __NRATRA2_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NRATRF3_process_vm_writev          "%p"
#define __NRATRA3_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NRATRF4_process_vm_writev          "%Iu"
#define __NRATRA4_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NRATRF5_process_vm_writev          "%#Ix"
#define __NRATRA5_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NRATRF0_kcmp                       "%Id"
#define __NRATRA0_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid1)
#define __NRATRF1_kcmp                       "%Id"
#define __NRATRA1_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid2)
#define __NRATRF2_kcmp                       "%#Ix"
#define __NRATRA2_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(type)
#define __NRATRF3_kcmp                       "%#Ix"
#define __NRATRA3_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx1)
#define __NRATRF4_kcmp                       "%#Ix"
#define __NRATRA4_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx2)
#define __NRATRF0_renameat2                  "%d"
#define __NRATRA0_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(olddirfd)
#define __NRATRF1_renameat2                  "%q"
#define __NRATRA1_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(oldpath,1),oldpath)
#define __NRATRF2_renameat2                  "%d"
#define __NRATRA2_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(newdirfd)
#define __NRATRF3_renameat2                  "%q"
#define __NRATRA3_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(newpath,1),newpath)
#define __NRATRF4_renameat2                  "%#Ix"
#define __NRATRA4_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(uintptr_t)(flags)
#define __NRATRF0_execveat                   "%d"
#define __NRATRA0_execveat(dirfd, pathname, argv, envp, flags) ,(int)(dirfd)
#define __NRATRF1_execveat                   "%q"
#define __NRATRA1_execveat(dirfd, pathname, argv, envp, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NRATRF2_execveat                   "%p"
#define __NRATRA2_execveat(dirfd, pathname, argv, envp, flags) ,argv
#define __NRATRF3_execveat                   "%p"
#define __NRATRA3_execveat(dirfd, pathname, argv, envp, flags) ,envp
#define __NRATRF4_execveat                   "%#Ix=%s%s%s%s%s"
#define __NRATRA4_execveat(dirfd, pathname, argv, envp, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                               ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                               ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_socket                     "%#Ix"
#define __NRATRA0_socket(domain, type, protocol) ,(uintptr_t)(domain)
#define __NRATRF1_socket                     "%#Ix"
#define __NRATRA1_socket(domain, type, protocol) ,(uintptr_t)(type)
#define __NRATRF2_socket                     "%#Ix"
#define __NRATRA2_socket(domain, type, protocol) ,(uintptr_t)(protocol)
#define __NRATRF0_socketpair                 "%#Ix"
#define __NRATRA0_socketpair(domain, type, protocol, fds) ,(uintptr_t)(domain)
#define __NRATRF1_socketpair                 "%#Ix"
#define __NRATRA1_socketpair(domain, type, protocol, fds) ,(uintptr_t)(type)
#define __NRATRF2_socketpair                 "%#Ix"
#define __NRATRA2_socketpair(domain, type, protocol, fds) ,(uintptr_t)(protocol)
#define __NRATRF3_socketpair                 "%p"
#define __NRATRA3_socketpair(domain, type, protocol, fds) ,fds
#define __NRATRF0_bind                       "%d"
#define __NRATRA0_bind(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NRATRF1_bind                       "%p"
#define __NRATRA1_bind(sockfd, addr, addr_len) ,addr
#define __NRATRF2_bind                       "%Iu"
#define __NRATRA2_bind(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NRATRF0_connect                    "%d"
#define __NRATRA0_connect(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NRATRF1_connect                    "%p"
#define __NRATRA1_connect(sockfd, addr, addr_len) ,addr
#define __NRATRF2_connect                    "%Iu"
#define __NRATRA2_connect(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NRATRF0_listen                     "%d"
#define __NRATRA0_listen(sockfd, max_backlog) ,(int)(sockfd)
#define __NRATRF1_listen                     "%#Ix"
#define __NRATRA1_listen(sockfd, max_backlog) ,(uintptr_t)(max_backlog)
#define __NRATRF0_accept4                    "%d"
#define __NRATRA0_accept4(sockfd, addr, addr_len, flags) ,(int)(sockfd)
#define __NRATRF1_accept4                    "%p"
#define __NRATRA1_accept4(sockfd, addr, addr_len, flags) ,addr
#define __NRATRF2_accept4                    "%p"
#define __NRATRA2_accept4(sockfd, addr, addr_len, flags) ,addr_len
#define __NRATRF3_accept4                    "%#Ix=%s%s%s%s%s"
#define __NRATRA3_accept4(sockfd, addr, addr_len, flags) ,(uintptr_t)(flags),(flags) & SOCK_NONBLOCK ? "SOCK_NONBLOCK" : "" \
                                                         ,((flags) & SOCK_CLOEXEC) && ((flags) & (SOCK_NONBLOCK)) ? "|" : "",(flags) & SOCK_CLOEXEC ? "SOCK_CLOEXEC" : "" \
                                                         ,((flags) & SOCK_CLOFORK) && ((flags) & (SOCK_NONBLOCK|SOCK_CLOEXEC)) ? "|" : "",(flags) & SOCK_CLOFORK ? "SOCK_CLOFORK" : ""
#define __NRATRF0_getsockopt                 "%d"
#define __NRATRA0_getsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NRATRF1_getsockopt                 "%#Ix=%s"
#define __NRATRA1_getsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NRATRF2_getsockopt                 "%#Ix"
#define __NRATRA2_getsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NRATRF3_getsockopt                 "%p"
#define __NRATRA3_getsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NRATRF4_getsockopt                 "%p"
#define __NRATRA4_getsockopt(sockfd, level, optname, optval, optlen) ,optlen
#define __NRATRF0_setsockopt                 "%d"
#define __NRATRA0_setsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NRATRF1_setsockopt                 "%#Ix=%s"
#define __NRATRA1_setsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NRATRF2_setsockopt                 "%#Ix"
#define __NRATRA2_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NRATRF3_setsockopt                 "%p"
#define __NRATRA3_setsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NRATRF4_setsockopt                 "%Iu"
#define __NRATRA4_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optlen)
#define __NRATRF0_getsockname                "%d"
#define __NRATRA0_getsockname(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NRATRF1_getsockname                "%p"
#define __NRATRA1_getsockname(sockfd, addr, addr_len) ,addr
#define __NRATRF2_getsockname                "%p"
#define __NRATRA2_getsockname(sockfd, addr, addr_len) ,addr_len
#define __NRATRF0_getpeername                "%d"
#define __NRATRA0_getpeername(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NRATRF1_getpeername                "%p"
#define __NRATRA1_getpeername(sockfd, addr, addr_len) ,addr
#define __NRATRF2_getpeername                "%p"
#define __NRATRA2_getpeername(sockfd, addr, addr_len) ,addr_len
#define __NRATRF0_sendto                     "%d"
#define __NRATRA0_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NRATRF1_sendto                     "%p"
#define __NRATRA1_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NRATRF2_sendto                     "%Iu"
#define __NRATRA2_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NRATRF3_sendto                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                                      ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                                      ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                      ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                                      ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                                      ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                                      ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NRATRF4_sendto                     "%p"
#define __NRATRA4_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NRATRF5_sendto                     "%Iu"
#define __NRATRA5_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NRATRF0_sendmsg                    "%d"
#define __NRATRA0_sendmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NRATRF1_sendmsg                    "%p"
#define __NRATRA1_sendmsg(sockfd, message, flags) ,message
#define __NRATRF2_sendmsg                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_sendmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                  ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                  ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                  ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                  ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                  ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                  ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NRATRF0_recvfrom                   "%d"
#define __NRATRA0_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NRATRF1_recvfrom                   "%p"
#define __NRATRA1_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NRATRF2_recvfrom                   "%Iu"
#define __NRATRA2_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NRATRF3_recvfrom                   "%#Ix=%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                        ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                                        ,((flags) & MSG_OOB) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                                        ,((flags) & MSG_PEEK) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                                        ,((flags) & MSG_TRUNC) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                                        ,((flags) & MSG_WAITALL) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NRATRF4_recvfrom                   "%p"
#define __NRATRA4_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NRATRF5_recvfrom                   "%p"
#define __NRATRA5_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr_len
#define __NRATRF0_recvmsg                    "%d"
#define __NRATRA0_recvmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NRATRF1_recvmsg                    "%p"
#define __NRATRA1_recvmsg(sockfd, message, flags) ,message
#define __NRATRF2_recvmsg                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_recvmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CMSG_CLOEXEC ? "MSG_CMSG_CLOEXEC" : "" \
                                                  ,((flags) & MSG_CMSG_CLOFORK) && ((flags) & (MSG_CMSG_CLOEXEC)) ? "|" : "",(flags) & MSG_CMSG_CLOFORK ? "MSG_CMSG_CLOFORK" : "" \
                                                  ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                  ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                  ,((flags) & MSG_OOB) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                  ,((flags) & MSG_PEEK) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                  ,((flags) & MSG_TRUNC) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                  ,((flags) & MSG_WAITALL) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NRATRF0_shutdown                   "%d"
#define __NRATRA0_shutdown(sockfd, how)      ,(int)(sockfd)
#define __NRATRF1_shutdown                   "%#Ix=%s"
#define __NRATRA1_shutdown(sockfd, how)      ,(how),(how) == SHUT_RD ? "SHUT_RD" : (how) == SHUT_WR ? "SHUT_WR" : (how) == SHUT_RDWR ? "SHUT_RDWR" : "?"
#define __NRATRF0_hop                        "%d"
#define __NRATRA0_hop(fd, command, arg)      ,(int)(fd)
#define __NRATRF1_hop                        "%#Ix"
#define __NRATRA1_hop(fd, command, arg)      ,(uintptr_t)(command)
#define __NRATRF2_hop                        "%p"
#define __NRATRA2_hop(fd, command, arg)      ,arg
#define __NRATRF0_hopf                       "%d"
#define __NRATRA0_hopf(fd, command, mode, arg) ,(int)(fd)
#define __NRATRF1_hopf                       "%#Ix"
#define __NRATRA1_hopf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NRATRF2_hopf                       "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_hopf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                               ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                               ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                               ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                               ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                               ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                               ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                               ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                               ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF3_hopf                       "%p"
#define __NRATRA3_hopf(fd, command, mode, arg) ,arg
#define __NRATRF0_readf                      "%d"
#define __NRATRA0_readf(fd, buf, bufsize, mode) ,(int)(fd)
#define __NRATRF1_readf                      "%p"
#define __NRATRA1_readf(fd, buf, bufsize, mode) ,buf
#define __NRATRF2_readf                      "%Iu"
#define __NRATRA2_readf(fd, buf, bufsize, mode) ,bufsize
#define __NRATRF3_readf                      "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_readf(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_writef                     "%d"
#define __NRATRA0_writef(fd, buf, bufsize, mode) ,(int)(fd)
#define __NRATRF1_writef                     "%p"
#define __NRATRA1_writef(fd, buf, bufsize, mode) ,buf
#define __NRATRF2_writef                     "%Iu"
#define __NRATRA2_writef(fd, buf, bufsize, mode) ,bufsize
#define __NRATRF3_writef                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_writef(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_detach                     "%Id"
#define __NRATRA0_detach(pid)                ,(intptr_t)(pid)
#define __NRATRF0_frealpath4                 "%d"
#define __NRATRA0_frealpath4(fd, buf, buflen, flags) ,(int)(fd)
#define __NRATRF1_frealpath4                 "%p"
#define __NRATRA1_frealpath4(fd, buf, buflen, flags) ,buf
#define __NRATRF2_frealpath4                 "%Iu"
#define __NRATRA2_frealpath4(fd, buf, buflen, flags) ,buflen
#define __NRATRF3_frealpath4                 "%#Ix=%s%s%s%s%s"
#define __NRATRA3_frealpath4(fd, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                     ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                     ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_frealpathat                "%d"
#define __NRATRA0_frealpathat(dirfd, filename, buf, buflen, flags) ,(int)(dirfd)
#define __NRATRF1_frealpathat                "%q"
#define __NRATRA1_frealpathat(dirfd, filename, buf, buflen, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_frealpathat                "%p"
#define __NRATRA2_frealpathat(dirfd, filename, buf, buflen, flags) ,buf
#define __NRATRF3_frealpathat                "%Iu"
#define __NRATRA3_frealpathat(dirfd, filename, buf, buflen, flags) ,buflen
#define __NRATRF4_frealpathat                "%#Ix=%s%s%s%s%s%s%s"
#define __NRATRA4_frealpathat(dirfd, filename, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                                   ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                   ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_rpc_schedule               "%Id"
#define __NRATRA0_rpc_schedule(target, flags, program, arguments) ,(intptr_t)(target)
#define __NRATRF1_rpc_schedule               "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA1_rpc_schedule(target, flags, program, arguments) ,(uintptr_t)(flags),(flags) & RPC_SCHEDULE_ASYNC ? "RPC_SCHEDULE_ASYNC" : (flags) ? "" : "RPC_SCHEDULE_SYNC" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_NONSYSCALL) && ((flags) & (RPC_SCHEDULE_ASYNC)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NONSYSCALL ? "RPC_SCHEDULE_FLAG_NONSYSCALL" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_WAITFORSTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITFORSTART ? "RPC_SCHEDULE_FLAG_WAITFORSTART" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX ? "RPC_SCHEDULE_FLAG_STATUSFUTEX" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_SYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_SYSRESTART ? "RPC_SCHEDULE_FLAG_SYSRESTART" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART ? "RPC_SCHEDULE_FLAG_NOSYSRESTART" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_WAITSMPACK) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITSMPACK ? "RPC_SCHEDULE_FLAG_WAITSMPACK" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_DONTWAKE) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_DONTWAKE ? "RPC_SCHEDULE_FLAG_DONTWAKE" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_HIGHPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_HIGHPRIO ? "RPC_SCHEDULE_FLAG_HIGHPRIO" : "" \
                                                                  ,((flags) & RPC_SCHEDULE_FLAG_LOWPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE|RPC_SCHEDULE_FLAG_HIGHPRIO)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_LOWPRIO ? "RPC_SCHEDULE_FLAG_LOWPRIO" : ""
#define __NRATRF2_rpc_schedule               "%p"
#define __NRATRA2_rpc_schedule(target, flags, program, arguments) ,program
#define __NRATRF3_rpc_schedule               "%p"
#define __NRATRA3_rpc_schedule(target, flags, program, arguments) ,arguments
#define __NRATRF0_sysctl                     "%#Ix"
#define __NRATRA0_sysctl(command, arg)       ,(uintptr_t)(command)
#define __NRATRF1_sysctl                     "%p"
#define __NRATRA1_sysctl(command, arg)       ,arg
#define __NRATRF0_openpty                    "%p"
#define __NRATRA0_openpty(amaster, aslave, name, termp, winp) ,amaster
#define __NRATRF1_openpty                    "%p"
#define __NRATRA1_openpty(amaster, aslave, name, termp, winp) ,aslave
#define __NRATRF2_openpty                    "%p"
#define __NRATRA2_openpty(amaster, aslave, name, termp, winp) ,name
#define __NRATRF3_openpty                    "%p"
#define __NRATRA3_openpty(amaster, aslave, name, termp, winp) ,termp
#define __NRATRF4_openpty                    "%p"
#define __NRATRA4_openpty(amaster, aslave, name, termp, winp) ,winp
#define __NRATRF0_fchdirat                   "%d"
#define __NRATRA0_fchdirat(dirfd, path, flags) ,(int)(dirfd)
#define __NRATRF1_fchdirat                   "%q"
#define __NRATRA1_fchdirat(dirfd, path, flags) ,(validate_readable_opt(path,1),path)
#define __NRATRF2_fchdirat                   "%#Ix=%s"
#define __NRATRA2_fchdirat(dirfd, path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_time64                     "%p"
#define __NRATRA0_time64(timer)              ,timer
#define __NRATRF0_set_exception_handler      "%#Ix"
#define __NRATRA0_set_exception_handler(mode, handler, handler_sp) ,(uintptr_t)(mode)
#define __NRATRF1_set_exception_handler      "%p"
#define __NRATRA1_set_exception_handler(mode, handler, handler_sp) ,handler
#define __NRATRF2_set_exception_handler      "%p"
#define __NRATRA2_set_exception_handler(mode, handler, handler_sp) ,handler_sp
#define __NRATRF0_get_exception_handler      "%p"
#define __NRATRA0_get_exception_handler(pmode, phandler, phandler_sp) ,pmode
#define __NRATRF1_get_exception_handler      "%p"
#define __NRATRA1_get_exception_handler(pmode, phandler, phandler_sp) ,phandler
#define __NRATRF2_get_exception_handler      "%p"
#define __NRATRA2_get_exception_handler(pmode, phandler, phandler_sp) ,phandler_sp
#define __NRATRF0_set_library_listdef        "%p"
#define __NRATRA0_set_library_listdef(listdef) ,listdef
#define __NRATRF0_debugtrap                  "%p"
#define __NRATRA0_debugtrap(state, trapno, regs) ,state
#define __NRATRF1_debugtrap                  "%#Ix"
#define __NRATRA1_debugtrap(state, trapno, regs) ,(uintptr_t)(trapno)
#define __NRATRF2_debugtrap                  "%p"
#define __NRATRA2_debugtrap(state, trapno, regs) ,regs
#define __NRATRF0_lfutex                     "%p"
#define __NRATRA0_lfutex(uaddr, futex_op, val, timeout, val2) ,uaddr
#define __NRATRF1_lfutex                     "%#Ix"
#define __NRATRA1_lfutex(uaddr, futex_op, val, timeout, val2) ,(uintptr_t)(futex_op)
#define __NRATRF2_lfutex                     "%p"
#define __NRATRA2_lfutex(uaddr, futex_op, val, timeout, val2) ,val
#define __NRATRF3_lfutex                     "%p"
#define __NRATRA3_lfutex(uaddr, futex_op, val, timeout, val2) ,timeout
#define __NRATRF4_lfutex                     "%p"
#define __NRATRA4_lfutex(uaddr, futex_op, val, timeout, val2) ,val2
#define __NRATRF0_lseek64                    "%d"
#define __NRATRA0_lseek64(fd, offset, whence) ,(int)(fd)
#define __NRATRF1_lseek64                    "%I64d"
#define __NRATRA1_lseek64(fd, offset, whence) ,offset
#define __NRATRF2_lseek64                    "%#Ix=%s"
#define __NRATRA2_lseek64(fd, offset, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NRATRF0_lfutexlock                 "%p"
#define __NRATRA0_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,ulockaddr
#define __NRATRF1_lfutexlock                 "%p"
#define __NRATRA1_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,uaddr
#define __NRATRF2_lfutexlock                 "%#Ix"
#define __NRATRA2_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,(uintptr_t)(futex_op)
#define __NRATRF3_lfutexlock                 "%p"
#define __NRATRA3_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,val
#define __NRATRF4_lfutexlock                 "%p"
#define __NRATRA4_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,timeout
#define __NRATRF5_lfutexlock                 "%p"
#define __NRATRA5_lfutexlock(ulockaddr, uaddr, futex_op, val, timeout, val2) ,val2
#define __NRATRF0_lfutexexpr                 "%p"
#define __NRATRA0_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,uaddr
#define __NRATRF1_lfutexexpr                 "%p"
#define __NRATRA1_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,base
#define __NRATRF2_lfutexexpr                 "%p"
#define __NRATRA2_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,exprv
#define __NRATRF3_lfutexexpr                 "%Iu"
#define __NRATRA3_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,exprc
#define __NRATRF4_lfutexexpr                 "%p"
#define __NRATRA4_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,timeout
#define __NRATRF5_lfutexexpr                 "%#Ix"
#define __NRATRA5_lfutexexpr(uaddr, base, exprv, exprc, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NRATRF0_lfutexlockexpr             "%p"
#define __NRATRA0_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,ulockaddr
#define __NRATRF1_lfutexlockexpr             "%p"
#define __NRATRA1_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,base
#define __NRATRF2_lfutexlockexpr             "%p"
#define __NRATRA2_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,exprv
#define __NRATRF3_lfutexlockexpr             "%Iu"
#define __NRATRA3_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,exprc
#define __NRATRF4_lfutexlockexpr             "%p"
#define __NRATRA4_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,timeout
#define __NRATRF5_lfutexlockexpr             "%#Ix"
#define __NRATRA5_lfutexlockexpr(ulockaddr, base, exprv, exprc, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NRATRF0_mktty                      "%d"
#define __NRATRA0_mktty(keyboard, display, name, rsvd) ,(int)(keyboard)
#define __NRATRF1_mktty                      "%d"
#define __NRATRA1_mktty(keyboard, display, name, rsvd) ,(int)(display)
#define __NRATRF2_mktty                      "%q"
#define __NRATRA2_mktty(keyboard, display, name, rsvd) ,(validate_readable_opt(name,1),name)
#define __NRATRF3_mktty                      "%#Ix"
#define __NRATRA3_mktty(keyboard, display, name, rsvd) ,(uintptr_t)(rsvd)
#define __NRATRF0_raiseat                    "%p"
#define __NRATRA0_raiseat(state, si)         ,state
#define __NRATRF1_raiseat                    "%p"
#define __NRATRA1_raiseat(state, si)         ,si
#define __NRATRF0_stime64                    "%p"
#define __NRATRA0_stime64(t)                 ,t
#define __NRATRF0_coredump                   "%p"
#define __NRATRA0_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,curr_state
#define __NRATRF1_coredump                   "%p"
#define __NRATRA1_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,orig_state
#define __NRATRF2_coredump                   "%p"
#define __NRATRA2_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_vector
#define __NRATRF3_coredump                   "%Iu"
#define __NRATRA3_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_length
#define __NRATRF4_coredump                   "%p"
#define __NRATRA4_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,exception
#define __NRATRF5_coredump                   "%#Ix"
#define __NRATRA5_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,(uintptr_t)(unwind_error)
#define __NRATRF0_utime64                    "%q"
#define __NRATRA0_utime64(filename, times)   ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_utime64                    "%p"
#define __NRATRA1_utime64(filename, times)   ,times
#define __NRATRF0_ioctlf                     "%d"
#define __NRATRA0_ioctlf(fd, command, mode, arg) ,(int)(fd)
#define __NRATRF1_ioctlf                     "%#Ix"
#define __NRATRA1_ioctlf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NRATRF2_ioctlf                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_ioctlf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF3_ioctlf                     "%p"
#define __NRATRA3_ioctlf(fd, command, mode, arg) ,arg
#define __NRATRF0_fsmode                     "%I64u"
#define __NRATRA0_fsmode(mode)               ,mode
#define __NRATRF0_gettimeofday64             "%p"
#define __NRATRA0_gettimeofday64(tv, tz)     ,tv
#define __NRATRF1_gettimeofday64             "%p"
#define __NRATRA1_gettimeofday64(tv, tz)     ,tz
#define __NRATRF0_settimeofday64             "%p"
#define __NRATRA0_settimeofday64(tv, tz)     ,tv
#define __NRATRF1_settimeofday64             "%p"
#define __NRATRA1_settimeofday64(tv, tz)     ,tz
#define __NRATRF0_select64                   "%Iu"
#define __NRATRA0_select64(nfds, readfds, writefds, exceptfds, timeout) ,nfds
#define __NRATRF1_select64                   "%p"
#define __NRATRA1_select64(nfds, readfds, writefds, exceptfds, timeout) ,readfds
#define __NRATRF2_select64                   "%p"
#define __NRATRA2_select64(nfds, readfds, writefds, exceptfds, timeout) ,writefds
#define __NRATRF3_select64                   "%p"
#define __NRATRA3_select64(nfds, readfds, writefds, exceptfds, timeout) ,exceptfds
#define __NRATRF4_select64                   "%p"
#define __NRATRA4_select64(nfds, readfds, writefds, exceptfds, timeout) ,timeout
#define __NRATRF0_maplibrary                 "%p"
#define __NRATRA0_maplibrary(addr, flags, fd, hdrv, hdrc) ,addr
#define __NRATRF1_maplibrary                 "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA1_maplibrary(addr, flags, fd, hdrv, hdrc) ,(uintptr_t)(flags),(flags) & MAP_FIXED ? "MAP_FIXED" : "" \
                                                          ,((flags) & MAP_LOCKED) && ((flags) & (MAP_FIXED)) ? "|" : "",(flags) & MAP_LOCKED ? "MAP_LOCKED" : "" \
                                                          ,((flags) & MAP_NONBLOCK) && ((flags) & (MAP_FIXED|MAP_LOCKED)) ? "|" : "",(flags) & MAP_NONBLOCK ? "MAP_NONBLOCK" : "" \
                                                          ,((flags) & MAP_NORESERVE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK)) ? "|" : "",(flags) & MAP_NORESERVE ? "MAP_NORESERVE" : "" \
                                                          ,((flags) & MAP_POPULATE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE)) ? "|" : "",(flags) & MAP_POPULATE ? "MAP_POPULATE" : "" \
                                                          ,((flags) & MAP_SYNC) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE)) ? "|" : "",(flags) & MAP_SYNC ? "MAP_SYNC" : "" \
                                                          ,((flags) & MAP_DONT_MAP) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC)) ? "|" : "",(flags) & MAP_DONT_MAP ? "MAP_DONT_MAP" : "" \
                                                          ,((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP)) ? "|" : "",(flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : ""
#define __NRATRF2_maplibrary                 "%d"
#define __NRATRA2_maplibrary(addr, flags, fd, hdrv, hdrc) ,(int)(fd)
#define __NRATRF3_maplibrary                 "%p"
#define __NRATRA3_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrv
#define __NRATRF4_maplibrary                 "%Iu"
#define __NRATRA4_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrc
#define __NRATRF0_setitimer64                "%#Ix"
#define __NRATRA0_setitimer64(which, newval, oldval) ,(uintptr_t)(which)
#define __NRATRF1_setitimer64                "%p"
#define __NRATRA1_setitimer64(which, newval, oldval) ,newval
#define __NRATRF2_setitimer64                "%p"
#define __NRATRA2_setitimer64(which, newval, oldval) ,oldval
#define __NRATRF0_getitimer64                "%#Ix"
#define __NRATRA0_getitimer64(which, curr_value) ,(uintptr_t)(which)
#define __NRATRF1_getitimer64                "%p"
#define __NRATRA1_getitimer64(which, curr_value) ,curr_value
#define __NRATRF0_kreaddir                   "%d"
#define __NRATRA0_kreaddir(fd, buf, bufsize, mode) ,(int)(fd)
#define __NRATRF1_kreaddir                   "%p"
#define __NRATRA1_kreaddir(fd, buf, bufsize, mode) ,buf
#define __NRATRF2_kreaddir                   "%Iu"
#define __NRATRA2_kreaddir(fd, buf, bufsize, mode) ,bufsize
#define __NRATRF3_kreaddir                   "%#Ix=%s%s%s%s%s%s%s"
#define __NRATRA3_kreaddir(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                   ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                   ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                   ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NRATRF0_readvf                     "%d"
#define __NRATRA0_readvf(fd, iovec, count, mode) ,(int)(fd)
#define __NRATRF1_readvf                     "%p"
#define __NRATRA1_readvf(fd, iovec, count, mode) ,iovec
#define __NRATRF2_readvf                     "%Iu"
#define __NRATRA2_readvf(fd, iovec, count, mode) ,count
#define __NRATRF3_readvf                     "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_readvf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_writevf                    "%d"
#define __NRATRA0_writevf(fd, iovec, count, mode) ,(int)(fd)
#define __NRATRF1_writevf                    "%p"
#define __NRATRA1_writevf(fd, iovec, count, mode) ,iovec
#define __NRATRF2_writevf                    "%Iu"
#define __NRATRA2_writevf(fd, iovec, count, mode) ,count
#define __NRATRF3_writevf                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_writevf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                  ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                  ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                  ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                  ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                  ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                  ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                  ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                  ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_sched_rr_get_interval64    "%Id"
#define __NRATRA0_sched_rr_get_interval64(pid, tms) ,(intptr_t)(pid)
#define __NRATRF1_sched_rr_get_interval64    "%p"
#define __NRATRA1_sched_rr_get_interval64(pid, tms) ,tms
#define __NRATRF0_nanosleep64                "%p"
#define __NRATRA0_nanosleep64(req, rem)      ,req
#define __NRATRF1_nanosleep64                "%p"
#define __NRATRA1_nanosleep64(req, rem)      ,rem
#define __NRATRF0_rt_sigtimedwait64          "%p"
#define __NRATRA0_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,set
#define __NRATRF1_rt_sigtimedwait64          "%p"
#define __NRATRA1_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,info
#define __NRATRF2_rt_sigtimedwait64          "%p"
#define __NRATRA2_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,timeout
#define __NRATRF3_rt_sigtimedwait64          "%Iu"
#define __NRATRA3_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,sigsetsize
#define __NRATRF0_pread64f                   "%d"
#define __NRATRA0_pread64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NRATRF1_pread64f                   "%p"
#define __NRATRA1_pread64f(fd, buf, bufsize, offset, mode) ,buf
#define __NRATRF2_pread64f                   "%Iu"
#define __NRATRA2_pread64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NRATRF3_pread64f                   "%I64u"
#define __NRATRA3_pread64f(fd, buf, bufsize, offset, mode) ,offset
#define __NRATRF4_pread64f                   "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_pread64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                           ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                           ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                           ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                           ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                           ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                           ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                           ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                           ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_pwrite64f                  "%d"
#define __NRATRA0_pwrite64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NRATRF1_pwrite64f                  "%p"
#define __NRATRA1_pwrite64f(fd, buf, bufsize, offset, mode) ,buf
#define __NRATRF2_pwrite64f                  "%Iu"
#define __NRATRA2_pwrite64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NRATRF3_pwrite64f                  "%I64u"
#define __NRATRA3_pwrite64f(fd, buf, bufsize, offset, mode) ,offset
#define __NRATRF4_pwrite64f                  "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_pwrite64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                            ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                            ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                            ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                            ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                            ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                            ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                            ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                            ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_kstat                      "%q"
#define __NRATRA0_kstat(filename, statbuf)   ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_kstat                      "%p"
#define __NRATRA1_kstat(filename, statbuf)   ,statbuf
#define __NRATRF0_klstat                     "%q"
#define __NRATRA0_klstat(filename, statbuf)  ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_klstat                     "%p"
#define __NRATRA1_klstat(filename, statbuf)  ,statbuf
#define __NRATRF0_kfstat                     "%d"
#define __NRATRA0_kfstat(fd, statbuf)        ,(int)(fd)
#define __NRATRF1_kfstat                     "%p"
#define __NRATRA1_kfstat(fd, statbuf)        ,statbuf
#define __NRATRF0_kreaddirf                  "%d"
#define __NRATRA0_kreaddirf(fd, buf, bufsize, mode, iomode) ,(int)(fd)
#define __NRATRF1_kreaddirf                  "%p"
#define __NRATRA1_kreaddirf(fd, buf, bufsize, mode, iomode) ,buf
#define __NRATRF2_kreaddirf                  "%Iu"
#define __NRATRA2_kreaddirf(fd, buf, bufsize, mode, iomode) ,bufsize
#define __NRATRF3_kreaddirf                  "%#Ix=%s%s%s%s%s%s%s"
#define __NRATRA3_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                            ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                            ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                            ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NRATRF4_kreaddirf                  "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(iomode),(iomode) & IO_WRONLY ? "IO_WRONLY" : (iomode) ? "" : "IO_RDONLY" \
                                                            ,((iomode) & IO_RDWR) && ((iomode) & (IO_WRONLY)) ? "|" : "",(iomode) & IO_RDWR ? "IO_RDWR" : "" \
                                                            ,((iomode) & IO_CLOEXEC) && ((iomode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(iomode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                            ,((iomode) & IO_CLOFORK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(iomode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                            ,((iomode) & IO_APPEND) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(iomode) & IO_APPEND ? "IO_APPEND" : "" \
                                                            ,((iomode) & IO_NONBLOCK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(iomode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                            ,((iomode) & IO_SYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(iomode) & IO_SYNC ? "IO_SYNC" : "" \
                                                            ,((iomode) & IO_ASYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(iomode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                            ,((iomode) & IO_DIRECT) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(iomode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_timer_settime64            "?"
#define __NRATRA0_timer_settime64(timerid, flags, value, ovalue) /* nothing */
#define __NRATRF1_timer_settime64            "%#Ix"
#define __NRATRA1_timer_settime64(timerid, flags, value, ovalue) ,(uintptr_t)(flags)
#define __NRATRF2_timer_settime64            "%p"
#define __NRATRA2_timer_settime64(timerid, flags, value, ovalue) ,value
#define __NRATRF3_timer_settime64            "%p"
#define __NRATRA3_timer_settime64(timerid, flags, value, ovalue) ,ovalue
#define __NRATRF0_timer_gettime64            "?"
#define __NRATRA0_timer_gettime64(timerid, value) /* nothing */
#define __NRATRF1_timer_gettime64            "%p"
#define __NRATRA1_timer_gettime64(timerid, value) ,value
#define __NRATRF0_clock_settime64            "?"
#define __NRATRA0_clock_settime64(clock_id, tp) /* nothing */
#define __NRATRF1_clock_settime64            "%p"
#define __NRATRA1_clock_settime64(clock_id, tp) ,tp
#define __NRATRF0_clock_gettime64            "?"
#define __NRATRA0_clock_gettime64(clock_id, tp) /* nothing */
#define __NRATRF1_clock_gettime64            "%p"
#define __NRATRA1_clock_gettime64(clock_id, tp) ,tp
#define __NRATRF0_clock_getres64             "?"
#define __NRATRA0_clock_getres64(clock_id, res) /* nothing */
#define __NRATRF1_clock_getres64             "%p"
#define __NRATRA1_clock_getres64(clock_id, res) ,res
#define __NRATRF0_clock_nanosleep64          "?"
#define __NRATRA0_clock_nanosleep64(clock_id, flags, requested_time, remaining) /* nothing */
#define __NRATRF1_clock_nanosleep64          "%#Ix"
#define __NRATRA1_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,(uintptr_t)(flags)
#define __NRATRF2_clock_nanosleep64          "%p"
#define __NRATRA2_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,requested_time
#define __NRATRF3_clock_nanosleep64          "%p"
#define __NRATRA3_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,remaining
#define __NRATRF0_utimes64                   "%q"
#define __NRATRA0_utimes64(filename, times)  ,(validate_readable_opt(filename,1),filename)
#define __NRATRF1_utimes64                   "%p"
#define __NRATRA1_utimes64(filename, times)  ,times
#define __NRATRF0_fmkdirat                   "%d"
#define __NRATRA0_fmkdirat(dirfd, pathname, mode, flags) ,(int)(dirfd)
#define __NRATRF1_fmkdirat                   "%q"
#define __NRATRA1_fmkdirat(dirfd, pathname, mode, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NRATRF2_fmkdirat                   "%#Io"
#define __NRATRA2_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(mode)
#define __NRATRF3_fmkdirat                   "%#Ix=%s"
#define __NRATRA3_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_fmknodat                   "%d"
#define __NRATRA0_fmknodat(dirfd, nodename, mode, dev, flags) ,(int)(dirfd)
#define __NRATRF1_fmknodat                   "%q"
#define __NRATRA1_fmknodat(dirfd, nodename, mode, dev, flags) ,(validate_readable_opt(nodename,1),nodename)
#define __NRATRF2_fmknodat                   "%#Io"
#define __NRATRA2_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(mode)
#define __NRATRF3_fmknodat                   "%.2x:%.2x"
#define __NRATRA3_fmknodat(dirfd, nodename, mode, dev, flags) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF4_fmknodat                   "%#Ix=%s"
#define __NRATRA4_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_futimesat64                "%d"
#define __NRATRA0_futimesat64(dirfd, filename, times) ,(int)(dirfd)
#define __NRATRF1_futimesat64                "%p"
#define __NRATRA1_futimesat64(dirfd, filename, times) ,filename
#define __NRATRF2_futimesat64                "%p"
#define __NRATRA2_futimesat64(dirfd, filename, times) ,times
#define __NRATRF0_kfstatat                   "%d"
#define __NRATRA0_kfstatat(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NRATRF1_kfstatat                   "%q"
#define __NRATRA1_kfstatat(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_kfstatat                   "%p"
#define __NRATRA2_kfstatat(dirfd, filename, statbuf, flags) ,statbuf
#define __NRATRF3_kfstatat                   "%#Ix=%s%s%s"
#define __NRATRA3_kfstatat(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                            ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_frenameat                  "%d"
#define __NRATRA0_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(oldfd)
#define __NRATRF1_frenameat                  "%q"
#define __NRATRA1_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(oldname,1),oldname)
#define __NRATRF2_frenameat                  "%d"
#define __NRATRA2_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(newfd)
#define __NRATRF3_frenameat                  "%q"
#define __NRATRA3_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NRATRF4_frenameat                  "%#Ix=%s"
#define __NRATRA4_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_fsymlinkat                 "%q"
#define __NRATRA0_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(link_text,1),link_text)
#define __NRATRF1_fsymlinkat                 "%d"
#define __NRATRA1_fsymlinkat(link_text, tofd, target_path, flags) ,(int)(tofd)
#define __NRATRF2_fsymlinkat                 "%q"
#define __NRATRA2_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NRATRF3_fsymlinkat                 "%#Ix=%s"
#define __NRATRA3_fsymlinkat(link_text, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_freadlinkat                "%d"
#define __NRATRA0_freadlinkat(dirfd, path, buf, buflen, flags) ,(int)(dirfd)
#define __NRATRF1_freadlinkat                "%q"
#define __NRATRA1_freadlinkat(dirfd, path, buf, buflen, flags) ,(validate_readable_opt(path,1),path)
#define __NRATRF2_freadlinkat                "%p"
#define __NRATRA2_freadlinkat(dirfd, path, buf, buflen, flags) ,buf
#define __NRATRF3_freadlinkat                "%Iu"
#define __NRATRA3_freadlinkat(dirfd, path, buf, buflen, flags) ,buflen
#define __NRATRF4_freadlinkat                "%#Ix=%s%s%s"
#define __NRATRA4_freadlinkat(dirfd, path, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                               ,((flags) & AT_DOSPATH) && ((flags) & (AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_pselect6_64                "%Iu"
#define __NRATRA0_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,nfds
#define __NRATRF1_pselect6_64                "%p"
#define __NRATRA1_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,readfds
#define __NRATRF2_pselect6_64                "%p"
#define __NRATRA2_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,writefds
#define __NRATRF3_pselect6_64                "%p"
#define __NRATRA3_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,exceptfds
#define __NRATRF4_pselect6_64                "%p"
#define __NRATRA4_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,timeout
#define __NRATRF5_pselect6_64                "%p"
#define __NRATRA5_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,sigmask_sigset_and_len
#define __NRATRF0_ppoll64                    "%p"
#define __NRATRA0_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,fds
#define __NRATRF1_ppoll64                    "%Iu"
#define __NRATRA1_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,nfds
#define __NRATRF2_ppoll64                    "%p"
#define __NRATRA2_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,timeout_ts
#define __NRATRF3_ppoll64                    "%p"
#define __NRATRA3_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigmask
#define __NRATRF4_ppoll64                    "%Iu"
#define __NRATRA4_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigsetsize
#define __NRATRF0_utimensat64                "%d"
#define __NRATRA0_utimensat64(dirfd, filename, times, flags) ,(int)(dirfd)
#define __NRATRF1_utimensat64                "%q"
#define __NRATRA1_utimensat64(dirfd, filename, times, flags) ,(validate_readable_opt(filename,1),filename)
#define __NRATRF2_utimensat64                "%p"
#define __NRATRA2_utimensat64(dirfd, filename, times, flags) ,times
#define __NRATRF3_utimensat64                "%#Ix=%s%s%s%s%s"
#define __NRATRA3_utimensat64(dirfd, filename, times, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                             ,((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                             ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_fallocate64                "%d"
#define __NRATRA0_fallocate64(fd, mode, offset, length) ,(int)(fd)
#define __NRATRF1_fallocate64                "%#Ix"
#define __NRATRA1_fallocate64(fd, mode, offset, length) ,(uintptr_t)(mode)
#define __NRATRF2_fallocate64                "%I64u"
#define __NRATRA2_fallocate64(fd, mode, offset, length) ,offset
#define __NRATRF3_fallocate64                "%I64u"
#define __NRATRA3_fallocate64(fd, mode, offset, length) ,length
#define __NRATRF0_timerfd_settime64          "%d"
#define __NRATRA0_timerfd_settime64(ufd, flags, utmr, otmr) ,(int)(ufd)
#define __NRATRF1_timerfd_settime64          "%#Ix"
#define __NRATRA1_timerfd_settime64(ufd, flags, utmr, otmr) ,(uintptr_t)(flags)
#define __NRATRF2_timerfd_settime64          "%p"
#define __NRATRA2_timerfd_settime64(ufd, flags, utmr, otmr) ,utmr
#define __NRATRF3_timerfd_settime64          "%p"
#define __NRATRA3_timerfd_settime64(ufd, flags, utmr, otmr) ,otmr
#define __NRATRF0_timerfd_gettime64          "%d"
#define __NRATRA0_timerfd_gettime64(ufd, otmr) ,(int)(ufd)
#define __NRATRF1_timerfd_gettime64          "%p"
#define __NRATRA1_timerfd_gettime64(ufd, otmr) ,otmr
#define __NRATRF0_preadvf                    "%d"
#define __NRATRA0_preadvf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NRATRF1_preadvf                    "%p"
#define __NRATRA1_preadvf(fd, iovec, count, offset, mode) ,iovec
#define __NRATRF2_preadvf                    "%Iu"
#define __NRATRA2_preadvf(fd, iovec, count, offset, mode) ,count
#define __NRATRF3_preadvf                    "%I64u"
#define __NRATRA3_preadvf(fd, iovec, count, offset, mode) ,offset
#define __NRATRF4_preadvf                    "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_preadvf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                          ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                          ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                          ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                          ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                          ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                          ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                          ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                          ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_pwritevf                   "%d"
#define __NRATRA0_pwritevf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NRATRF1_pwritevf                   "%p"
#define __NRATRA1_pwritevf(fd, iovec, count, offset, mode) ,iovec
#define __NRATRF2_pwritevf                   "%Iu"
#define __NRATRA2_pwritevf(fd, iovec, count, offset, mode) ,count
#define __NRATRF3_pwritevf                   "%I64u"
#define __NRATRA3_pwritevf(fd, iovec, count, offset, mode) ,offset
#define __NRATRF4_pwritevf                   "%#Ix=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_pwritevf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                           ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                           ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                           ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                           ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                           ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                           ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                           ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                           ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_recvmmsg64                 "%d"
#define __NRATRA0_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,(int)(sockfd)
#define __NRATRF1_recvmmsg64                 "%p"
#define __NRATRA1_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,vmessages
#define __NRATRF2_recvmmsg64                 "%Iu"
#define __NRATRA2_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,vlen
#define __NRATRF3_recvmmsg64                 "%#Ix"
#define __NRATRA3_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,(uintptr_t)(flags)
#define __NRATRF4_recvmmsg64                 "%p"
#define __NRATRA4_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,tmo
#endif /* __WANT_SYSCALL_ARGUMENT_FORMAT */

#ifdef __WANT_SYSCALL_ARGUMENT_COUNT
#define __NRAC_exit                       1
#define __NRAC_fork                       0
#define __NRAC_read                       3
#define __NRAC_write                      3
#define __NRAC_open                       3
#define __NRAC_close                      1
#define __NRAC_waitpid                    3
#define __NRAC_creat                      2
#define __NRAC_link                       2
#define __NRAC_unlink                     1
#define __NRAC_execve                     3
#define __NRAC_chdir                      1
#define __NRAC_time                       1
#define __NRAC_mknod                      3
#define __NRAC_chmod                      2
#define __NRAC_lchown                     3
#define __NRAC_linux_oldstat              2
#define __NRAC_lseek                      3
#define __NRAC_getpid                     0
#define __NRAC_mount                      5
#define __NRAC_umount                     1
#define __NRAC_setuid                     1
#define __NRAC_getuid                     0
#define __NRAC_stime                      1
#define __NRAC_ptrace                     4
#define __NRAC_alarm                      1
#define __NRAC_linux_oldfstat             2
#define __NRAC_pause                      0
#define __NRAC_utime                      2
#define __NRAC_access                     2
#define __NRAC_nice                       1
#define __NRAC_ftime                      1
#define __NRAC_sync                       0
#define __NRAC_kill                       2
#define __NRAC_rename                     2
#define __NRAC_mkdir                      2
#define __NRAC_rmdir                      1
#define __NRAC_dup                        1
#define __NRAC_pipe                       1
#define __NRAC_times                      1
#define __NRAC_brk                        1
#define __NRAC_setgid                     1
#define __NRAC_getgid                     0
#define __NRAC_signal                     2
#define __NRAC_geteuid                    0
#define __NRAC_getegid                    0
#define __NRAC_acct                       1
#define __NRAC_umount2                    2
#define __NRAC_ioctl                      3
#define __NRAC_fcntl                      3
#define __NRAC_setpgid                    2
#define __NRAC_oldolduname                1
#define __NRAC_umask                      1
#define __NRAC_chroot                     1
#define __NRAC_ustat                      2
#define __NRAC_dup2                       2
#define __NRAC_getppid                    0
#define __NRAC_getpgrp                    0
#define __NRAC_setsid                     0
#define __NRAC_sigaction                  3
#define __NRAC_sgetmask                   0
#define __NRAC_ssetmask                   1
#define __NRAC_setreuid                   2
#define __NRAC_setregid                   2
#define __NRAC_sigsuspend                 1
#define __NRAC_sigpending                 1
#define __NRAC_sethostname                2
#define __NRAC_setrlimit                  2
#define __NRAC_getrlimit                  2
#define __NRAC_getrusage                  2
#define __NRAC_gettimeofday               2
#define __NRAC_settimeofday               2
#define __NRAC_getgroups                  2
#define __NRAC_setgroups                  2
#define __NRAC_select                     5
#define __NRAC_symlink                    2
#define __NRAC_linux_oldlstat             2
#define __NRAC_readlink                   3
#define __NRAC_swapon                     2
#define __NRAC_reboot                     1
#define __NRAC_readdir                    3
#define __NRAC_mmap                       6
#define __NRAC_munmap                     2
#define __NRAC_truncate                   2
#define __NRAC_ftruncate                  2
#define __NRAC_fchmod                     2
#define __NRAC_fchown                     3
#define __NRAC_getpriority                2
#define __NRAC_setpriority                3
#define __NRAC_profil                     4
#define __NRAC_statfs                     2
#define __NRAC_fstatfs                    2
#define __NRAC_ioperm                     3
#define __NRAC_socketcall                 2
#define __NRAC_syslog                     3
#define __NRAC_setitimer                  3
#define __NRAC_getitimer                  2
#define __NRAC_linux_stat32               2
#define __NRAC_linux_lstat32              2
#define __NRAC_linux_fstat32              2
#define __NRAC_olduname                   1
#define __NRAC_iopl                       1
#define __NRAC_vhangup                    0
#define __NRAC_wait4                      4
#define __NRAC_swapoff                    1
#define __NRAC_sysinfo                    1
#define __NRAC_fsync                      1
#define __NRAC_sigreturn                  6
#define __NRAC_clone                      5
#define __NRAC_setdomainname              2
#define __NRAC_uname                      1
#define __NRAC_modify_ldt                 3
#define __NRAC_mprotect                   3
#define __NRAC_sigprocmask                3
#define __NRAC_getpgid                    1
#define __NRAC_fchdir                     1
#define __NRAC_setfsuid                   1
#define __NRAC_setfsgid                   1
#define __NRAC__llseek                    4
#define __NRAC_getdents                   3
#define __NRAC_flock                      2
#define __NRAC_msync                      3
#define __NRAC_readv                      3
#define __NRAC_writev                     3
#define __NRAC_getsid                     1
#define __NRAC_fdatasync                  1
#define __NRAC_mlock                      2
#define __NRAC_munlock                    2
#define __NRAC_mlockall                   1
#define __NRAC_munlockall                 0
#define __NRAC_sched_setparam             2
#define __NRAC_sched_getparam             2
#define __NRAC_sched_setscheduler         3
#define __NRAC_sched_getscheduler         1
#define __NRAC_sched_yield                0
#define __NRAC_sched_get_priority_max     1
#define __NRAC_sched_get_priority_min     1
#define __NRAC_sched_rr_get_interval      2
#define __NRAC_nanosleep                  2
#define __NRAC_mremap                     5
#define __NRAC_setresuid                  3
#define __NRAC_getresuid                  3
#define __NRAC_poll                       3
#define __NRAC_setresgid                  3
#define __NRAC_getresgid                  3
#define __NRAC_rt_sigaction               4
#define __NRAC_rt_sigprocmask             4
#define __NRAC_rt_sigpending              2
#define __NRAC_rt_sigtimedwait            4
#define __NRAC_rt_sigqueueinfo            3
#define __NRAC_rt_sigsuspend              2
#define __NRAC_pread64                    4
#define __NRAC_pwrite64                   4
#define __NRAC_chown                      3
#define __NRAC_getcwd                     2
#define __NRAC_sigaltstack                2
#define __NRAC_sendfile                   4
#define __NRAC_vfork                      0
#define __NRAC_mmap2                      6
#define __NRAC_truncate64                 2
#define __NRAC_ftruncate64                2
#define __NRAC_linux_stat64               2
#define __NRAC_linux_lstat64              2
#define __NRAC_linux_fstat64              2
#define __NRAC_lchown32                   3
#define __NRAC_getuid32                   0
#define __NRAC_getgid32                   0
#define __NRAC_geteuid32                  0
#define __NRAC_getegid32                  0
#define __NRAC_setreuid32                 2
#define __NRAC_setregid32                 2
#define __NRAC_getgroups32                2
#define __NRAC_setgroups32                2
#define __NRAC_fchown32                   3
#define __NRAC_setresuid32                3
#define __NRAC_getresuid32                3
#define __NRAC_setresgid32                3
#define __NRAC_getresgid32                3
#define __NRAC_chown32                    3
#define __NRAC_setuid32                   1
#define __NRAC_setgid32                   1
#define __NRAC_setfsuid32                 1
#define __NRAC_setfsgid32                 1
#define __NRAC_mincore                    3
#define __NRAC_madvise                    3
#define __NRAC_getdents64                 3
#define __NRAC_fcntl64                    3
#define __NRAC_gettid                     0
#define __NRAC_readahead                  3
#define __NRAC_setxattr                   5
#define __NRAC_lsetxattr                  5
#define __NRAC_fsetxattr                  5
#define __NRAC_getxattr                   4
#define __NRAC_lgetxattr                  4
#define __NRAC_fgetxattr                  4
#define __NRAC_listxattr                  3
#define __NRAC_llistxattr                 3
#define __NRAC_flistxattr                 3
#define __NRAC_removexattr                2
#define __NRAC_lremovexattr               2
#define __NRAC_fremovexattr               2
#define __NRAC_tkill                      2
#define __NRAC_sendfile64                 4
#define __NRAC_futex                      6
#define __NRAC_sched_setaffinity          3
#define __NRAC_sched_getaffinity          3
#define __NRAC_exit_group                 1
#define __NRAC_epoll_create               1
#define __NRAC_epoll_ctl                  4
#define __NRAC_epoll_wait                 4
#define __NRAC_remap_file_pages           5
#define __NRAC_set_tid_address            1
#define __NRAC_timer_create               3
#define __NRAC_timer_settime              4
#define __NRAC_timer_gettime              2
#define __NRAC_timer_getoverrun           1
#define __NRAC_timer_delete               1
#define __NRAC_clock_settime              2
#define __NRAC_clock_gettime              2
#define __NRAC_clock_getres               2
#define __NRAC_clock_nanosleep            4
#define __NRAC_statfs64                   2
#define __NRAC_fstatfs64                  2
#define __NRAC_tgkill                     3
#define __NRAC_utimes                     2
#define __NRAC_waitid                     5
#define __NRAC_ioprio_set                 3
#define __NRAC_ioprio_get                 2
#define __NRAC_openat                     4
#define __NRAC_mkdirat                    3
#define __NRAC_mknodat                    4
#define __NRAC_fchownat                   5
#define __NRAC_futimesat                  3
#define __NRAC_linux_fstatat64            4
#define __NRAC_unlinkat                   3
#define __NRAC_renameat                   4
#define __NRAC_linkat                     5
#define __NRAC_symlinkat                  3
#define __NRAC_readlinkat                 4
#define __NRAC_fchmodat                   4
#define __NRAC_faccessat                  4
#define __NRAC_pselect6                   6
#define __NRAC_ppoll                      5
#define __NRAC_unshare                    1
#define __NRAC_splice                     6
#define __NRAC_sync_file_range            4
#define __NRAC_tee                        4
#define __NRAC_vmsplice                   4
#define __NRAC_getcpu                     3
#define __NRAC_epoll_pwait                5
#define __NRAC_utimensat                  4
#define __NRAC_timerfd_create             2
#define __NRAC_eventfd                    1
#define __NRAC_fallocate                  4
#define __NRAC_timerfd_settime            4
#define __NRAC_timerfd_gettime            2
#define __NRAC_eventfd2                   2
#define __NRAC_epoll_create1              1
#define __NRAC_dup3                       3
#define __NRAC_pipe2                      2
#define __NRAC_preadv                     4
#define __NRAC_pwritev                    4
#define __NRAC_rt_tgsigqueueinfo          4
#define __NRAC_recvmmsg                   5
#define __NRAC_prlimit64                  4
#define __NRAC_name_to_handle_at          5
#define __NRAC_open_by_handle_at          3
#define __NRAC_syncfs                     1
#define __NRAC_sendmmsg                   4
#define __NRAC_setns                      2
#define __NRAC_process_vm_readv           6
#define __NRAC_process_vm_writev          6
#define __NRAC_kcmp                       5
#define __NRAC_renameat2                  5
#define __NRAC_execveat                   5
#define __NRAC_socket                     3
#define __NRAC_socketpair                 4
#define __NRAC_bind                       3
#define __NRAC_connect                    3
#define __NRAC_listen                     2
#define __NRAC_accept4                    4
#define __NRAC_getsockopt                 5
#define __NRAC_setsockopt                 5
#define __NRAC_getsockname                3
#define __NRAC_getpeername                3
#define __NRAC_sendto                     6
#define __NRAC_sendmsg                    3
#define __NRAC_recvfrom                   6
#define __NRAC_recvmsg                    3
#define __NRAC_shutdown                   2
#define __NRAC_hop                        3
#define __NRAC_hopf                       4
#define __NRAC_readf                      4
#define __NRAC_writef                     4
#define __NRAC_detach                     1
#define __NRAC_getdrives                  0
#define __NRAC_frealpath4                 4
#define __NRAC_frealpathat                5
#define __NRAC_rpc_schedule               4
#define __NRAC_sysctl                     2
#define __NRAC_openpty                    5
#define __NRAC_fchdirat                   3
#define __NRAC_time64                     1
#define __NRAC_set_exception_handler      3
#define __NRAC_get_exception_handler      3
#define __NRAC_set_library_listdef        1
#define __NRAC_debugtrap                  3
#define __NRAC_lfutex                     5
#define __NRAC_lseek64                    3
#define __NRAC_lfutexlock                 6
#define __NRAC_lfutexexpr                 6
#define __NRAC_lfutexlockexpr             6
#define __NRAC_mktty                      4
#define __NRAC_raiseat                    2
#define __NRAC_stime64                    1
#define __NRAC_coredump                   6
#define __NRAC_utime64                    2
#define __NRAC_ioctlf                     4
#define __NRAC_fsmode                     1
#define __NRAC_gettimeofday64             2
#define __NRAC_settimeofday64             2
#define __NRAC_select64                   5
#define __NRAC_maplibrary                 5
#define __NRAC_setitimer64                3
#define __NRAC_getitimer64                2
#define __NRAC_kreaddir                   4
#define __NRAC_readvf                     4
#define __NRAC_writevf                    4
#define __NRAC_rpc_service                0
#define __NRAC_sched_rr_get_interval64    2
#define __NRAC_nanosleep64                2
#define __NRAC_rt_sigtimedwait64          4
#define __NRAC_pread64f                   5
#define __NRAC_pwrite64f                  5
#define __NRAC_kstat                      2
#define __NRAC_klstat                     2
#define __NRAC_kfstat                     2
#define __NRAC_kreaddirf                  5
#define __NRAC_timer_settime64            4
#define __NRAC_timer_gettime64            2
#define __NRAC_clock_settime64            2
#define __NRAC_clock_gettime64            2
#define __NRAC_clock_getres64             2
#define __NRAC_clock_nanosleep64          4
#define __NRAC_utimes64                   2
#define __NRAC_fmkdirat                   4
#define __NRAC_fmknodat                   5
#define __NRAC_futimesat64                3
#define __NRAC_kfstatat                   4
#define __NRAC_frenameat                  5
#define __NRAC_fsymlinkat                 4
#define __NRAC_freadlinkat                5
#define __NRAC_pselect6_64                6
#define __NRAC_ppoll64                    5
#define __NRAC_utimensat64                4
#define __NRAC_fallocate64                4
#define __NRAC_timerfd_settime64          4
#define __NRAC_timerfd_gettime64          2
#define __NRAC_preadvf                    5
#define __NRAC_pwritevf                   5
#define __NRAC_recvmmsg64                 5
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT */

#ifdef __WANT_SYSCALL_ARGUMENT_LIST_MAKER
#define __NRAM_exit(a, b, c, d, e, f)                       (__syscall_ulong_t)a
#define __NRAM_fork(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_read(a, b, c, d, e, f)                       (__fd_t)a, (void *)b, (__size_t)c
#define __NRAM_write(a, b, c, d, e, f)                      (__fd_t)a, (void const *)b, (__size_t)c
#define __NRAM_open(a, b, c, d, e, f)                       (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NRAM_close(a, b, c, d, e, f)                      (__fd_t)a
#define __NRAM_waitpid(a, b, c, d, e, f)                    (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c
#define __NRAM_creat(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b
#define __NRAM_link(a, b, c, d, e, f)                       (char const *)a, (char const *)b
#define __NRAM_unlink(a, b, c, d, e, f)                     (char const *)a
#define __NRAM_execve(a, b, c, d, e, f)                     (char const *)a, (char const *const *)b, (char const *const *)c
#define __NRAM_chdir(a, b, c, d, e, f)                      (char const *)a
#define __NRAM_time(a, b, c, d, e, f)                       (__time32_t *)a
#define __NRAM_mknod(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b, (__dev_t)c
#define __NRAM_chmod(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b
#define __NRAM_lchown(a, b, c, d, e, f)                     (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_linux_oldstat(a, b, c, d, e, f)              (char const *)a, (struct linux_oldstat *)b
#define __NRAM_lseek(a, b, c, d, e, f)                      (__fd_t)a, (__int32_t)b, (__syscall_ulong_t)c
#define __NRAM_getpid(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_mount(a, b, c, d, e, f)                      (char const *)a, (char const *)b, (char const *)c, (__syscall_ulong_t)d, (void const *)e
#define __NRAM_umount(a, b, c, d, e, f)                     (char const *)a
#define __NRAM_setuid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NRAM_getuid(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_stime(a, b, c, d, e, f)                      (__time32_t const *)a
#define __NRAM_ptrace(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__pid_t)b, (void *)c, (void *)d
#define __NRAM_alarm(a, b, c, d, e, f)                      (__syscall_ulong_t)a
#define __NRAM_linux_oldfstat(a, b, c, d, e, f)             (__fd_t)a, (struct linux_oldstat *)b
#define __NRAM_pause(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_utime(a, b, c, d, e, f)                      (char const *)a, (struct __utimbuf32 const *)b
#define __NRAM_access(a, b, c, d, e, f)                     (char const *)a, (__syscall_ulong_t)b
#define __NRAM_nice(a, b, c, d, e, f)                       (__syscall_slong_t)a
#define __NRAM_ftime(a, b, c, d, e, f)                      (struct timeb *)a
#define __NRAM_sync(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_kill(a, b, c, d, e, f)                       (__pid_t)a, (__syscall_ulong_t)b
#define __NRAM_rename(a, b, c, d, e, f)                     (char const *)a, (char const *)b
#define __NRAM_mkdir(a, b, c, d, e, f)                      (char const *)a, (__mode_t)b
#define __NRAM_rmdir(a, b, c, d, e, f)                      (char const *)a
#define __NRAM_dup(a, b, c, d, e, f)                        (__fd_t)a
#define __NRAM_pipe(a, b, c, d, e, f)                       (/*[2]*/__fd_t *)a
#define __NRAM_times(a, b, c, d, e, f)                      (struct tms *)a
#define __NRAM_brk(a, b, c, d, e, f)                        (void *)a
#define __NRAM_setgid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NRAM_getgid(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_signal(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__sighandler_t)b
#define __NRAM_geteuid(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_getegid(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_acct(a, b, c, d, e, f)                       (char const *)a
#define __NRAM_umount2(a, b, c, d, e, f)                    (char const *)a, (__syscall_ulong_t)b
#define __NRAM_ioctl(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NRAM_fcntl(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NRAM_setpgid(a, b, c, d, e, f)                    (__pid_t)a, (__pid_t)b
#define __NRAM_oldolduname(a, b, c, d, e, f)                (struct linux_oldolduname *)a
#define __NRAM_umask(a, b, c, d, e, f)                      (__mode_t)a
#define __NRAM_chroot(a, b, c, d, e, f)                     (char const *)a
#define __NRAM_ustat(a, b, c, d, e, f)                      (__dev_t)a, (struct ustat *)b
#define __NRAM_dup2(a, b, c, d, e, f)                       (__fd_t)a, (__fd_t)b
#define __NRAM_getppid(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_getpgrp(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_setsid(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_sigaction(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct sigaction const *)b, (struct sigaction *)c
#define __NRAM_sgetmask(a, b, c, d, e, f)                   /* nothing */
#define __NRAM_ssetmask(a, b, c, d, e, f)                   (__syscall_ulong_t)a
#define __NRAM_setreuid(a, b, c, d, e, f)                   (__uint16_t)a, (__uint16_t)b
#define __NRAM_setregid(a, b, c, d, e, f)                   (__uint16_t)a, (__uint16_t)b
#define __NRAM_sigsuspend(a, b, c, d, e, f)                 (struct __sigset_struct const *)a
#define __NRAM_sigpending(a, b, c, d, e, f)                 (struct __sigset_struct *)a
#define __NRAM_sethostname(a, b, c, d, e, f)                (char const *)a, (__size_t)b
#define __NRAM_setrlimit(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct rlimit const *)b
#define __NRAM_getrlimit(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct rlimit *)b
#define __NRAM_getrusage(a, b, c, d, e, f)                  (__syscall_slong_t)a, (struct rusage *)b
#define __NRAM_gettimeofday(a, b, c, d, e, f)               (struct __timeval32 *)a, (struct timezone *)b
#define __NRAM_settimeofday(a, b, c, d, e, f)               (struct __timeval32 const *)a, (struct timezone const *)b
#define __NRAM_getgroups(a, b, c, d, e, f)                  (__size_t)a, (/*[]*/__uint16_t *)b
#define __NRAM_setgroups(a, b, c, d, e, f)                  (__size_t)a, (__uint16_t const *)b
#define __NRAM_select(a, b, c, d, e, f)                     (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timeval32 *)e
#define __NRAM_symlink(a, b, c, d, e, f)                    (char const *)a, (char const *)b
#define __NRAM_linux_oldlstat(a, b, c, d, e, f)             (char const *)a, (struct linux_oldstat *)b
#define __NRAM_readlink(a, b, c, d, e, f)                   (char const *)a, (char *)b, (__size_t)c
#define __NRAM_swapon(a, b, c, d, e, f)                     (char const *)a, (__syscall_ulong_t)b
#define __NRAM_reboot(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NRAM_readdir(a, b, c, d, e, f)                    (__fd_t)a, (struct old_linux_dirent *)b, (__size_t)c
#define __NRAM_mmap(a, b, c, d, e, f)                       (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NRAM_munmap(a, b, c, d, e, f)                     (void *)a, (__size_t)b
#define __NRAM_truncate(a, b, c, d, e, f)                   (char const *)a, (__syscall_ulong_t)b
#define __NRAM_ftruncate(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_fchmod(a, b, c, d, e, f)                     (__fd_t)a, (__mode_t)b
#define __NRAM_fchown(a, b, c, d, e, f)                     (__fd_t)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getpriority(a, b, c, d, e, f)                (__syscall_ulong_t)a, (__id_t)b
#define __NRAM_setpriority(a, b, c, d, e, f)                (__syscall_ulong_t)a, (__id_t)b, (__syscall_ulong_t)c
#define __NRAM_profil(a, b, c, d, e, f)                     (__uint16_t *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_statfs(a, b, c, d, e, f)                     (char const *)a, (struct __statfs32 *)b
#define __NRAM_fstatfs(a, b, c, d, e, f)                    (__fd_t)a, (struct __statfs32 *)b
#define __NRAM_ioperm(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_socketcall(a, b, c, d, e, f)                 (int)a, (unsigned long *)b
#define __NRAM_syslog(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (char const *)b, (__size_t)c
#define __NRAM_setitimer(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimerval32 const *)b, (struct __itimerval32 *)c
#define __NRAM_getitimer(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimerval32 *)b
#define __NRAM_linux_stat32(a, b, c, d, e, f)               (char const *)a, (struct linux_stat32 *)b
#define __NRAM_linux_lstat32(a, b, c, d, e, f)              (char const *)a, (struct linux_stat32 *)b
#define __NRAM_linux_fstat32(a, b, c, d, e, f)              (__fd_t)a, (struct linux_stat32 *)b
#define __NRAM_olduname(a, b, c, d, e, f)                   (struct linux_olduname *)a
#define __NRAM_iopl(a, b, c, d, e, f)                       (__syscall_ulong_t)a
#define __NRAM_vhangup(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_wait4(a, b, c, d, e, f)                      (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct rusage *)d
#define __NRAM_swapoff(a, b, c, d, e, f)                    (char const *)a
#define __NRAM_sysinfo(a, b, c, d, e, f)                    (struct sysinfo *)a
#define __NRAM_fsync(a, b, c, d, e, f)                      (__fd_t)a
#define __NRAM_sigreturn(a, b, c, d, e, f)                  (struct fpustate const *)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (struct __sigset_struct const *)d, (struct rpc_syscall_info *)e, (struct ucpustate const *)f
#define __NRAM_clone(a, b, c, d, e, f)                      (__syscall_ulong_t)a, (void *)b, (__pid_t *)c, (__uintptr_t)d, (__pid_t *)e
#define __NRAM_setdomainname(a, b, c, d, e, f)              (char const *)a, (__size_t)b
#define __NRAM_uname(a, b, c, d, e, f)                      (struct utsname *)a
#define __NRAM_modify_ldt(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (void *)b, (__syscall_ulong_t)c
#define __NRAM_mprotect(a, b, c, d, e, f)                   (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_sigprocmask(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c
#define __NRAM_getpgid(a, b, c, d, e, f)                    (__pid_t)a
#define __NRAM_fchdir(a, b, c, d, e, f)                     (__fd_t)a
#define __NRAM_setfsuid(a, b, c, d, e, f)                   (__uint16_t)a
#define __NRAM_setfsgid(a, b, c, d, e, f)                   (__uint16_t)a
#define __NRAM__llseek(a, b, c, d, e, f)                    (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t *)d, (__syscall_ulong_t)e
#define __NRAM_getdents(a, b, c, d, e, f)                   (__fd_t)a, (struct linux_dirent *)b, (__size_t)c
#define __NRAM_flock(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_msync(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_readv(a, b, c, d, e, f)                      (__fd_t)a, (struct iovec const *)b, (__size_t)c
#define __NRAM_writev(a, b, c, d, e, f)                     (__fd_t)a, (struct iovec const *)b, (__size_t)c
#define __NRAM_getsid(a, b, c, d, e, f)                     (__pid_t)a
#define __NRAM_fdatasync(a, b, c, d, e, f)                  (__fd_t)a
#define __NRAM_mlock(a, b, c, d, e, f)                      (void const *)a, (__size_t)b
#define __NRAM_munlock(a, b, c, d, e, f)                    (void const *)a, (__size_t)b
#define __NRAM_mlockall(a, b, c, d, e, f)                   (__syscall_ulong_t)a
#define __NRAM_munlockall(a, b, c, d, e, f)                 /* nothing */
#define __NRAM_sched_setparam(a, b, c, d, e, f)             (__pid_t)a, (struct sched_param const *)b
#define __NRAM_sched_getparam(a, b, c, d, e, f)             (__pid_t)a, (struct sched_param *)b
#define __NRAM_sched_setscheduler(a, b, c, d, e, f)         (__pid_t)a, (__syscall_ulong_t)b, (struct sched_param const *)c
#define __NRAM_sched_getscheduler(a, b, c, d, e, f)         (__pid_t)a
#define __NRAM_sched_yield(a, b, c, d, e, f)                /* nothing */
#define __NRAM_sched_get_priority_max(a, b, c, d, e, f)     (__syscall_ulong_t)a
#define __NRAM_sched_get_priority_min(a, b, c, d, e, f)     (__syscall_ulong_t)a
#define __NRAM_sched_rr_get_interval(a, b, c, d, e, f)      (__pid_t)a, (struct __timespec32 *)b
#define __NRAM_nanosleep(a, b, c, d, e, f)                  (struct __timespec32 const *)a, (struct __timespec32 *)b
#define __NRAM_mremap(a, b, c, d, e, f)                     (void *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d, (void *)e
#define __NRAM_setresuid(a, b, c, d, e, f)                  (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getresuid(a, b, c, d, e, f)                  (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NRAM_poll(a, b, c, d, e, f)                       (struct pollfd *)a, (__size_t)b, (__syscall_slong_t)c
#define __NRAM_setresgid(a, b, c, d, e, f)                  (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getresgid(a, b, c, d, e, f)                  (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NRAM_rt_sigaction(a, b, c, d, e, f)               (__syscall_ulong_t)a, (struct sigaction const *)b, (struct sigaction *)c, (__size_t)d
#define __NRAM_rt_sigprocmask(a, b, c, d, e, f)             (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c, (__size_t)d
#define __NRAM_rt_sigpending(a, b, c, d, e, f)              (struct __sigset_struct *)a, (__size_t)b
#define __NRAM_rt_sigtimedwait(a, b, c, d, e, f)            (struct __sigset_struct const *)a, (struct __siginfo_struct *)b, (struct __timespec32 const *)c, (__size_t)d
#define __NRAM_rt_sigqueueinfo(a, b, c, d, e, f)            (__pid_t)a, (__syscall_ulong_t)b, (struct __siginfo_struct const *)c
#define __NRAM_rt_sigsuspend(a, b, c, d, e, f)              (struct __sigset_struct const *)a, (__size_t)b
#define __NRAM_pread64(a, b, c, d, e, f)                    (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_pwrite64(a, b, c, d, e, f)                   (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_chown(a, b, c, d, e, f)                      (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getcwd(a, b, c, d, e, f)                     (char *)a, (__size_t)b
#define __NRAM_sigaltstack(a, b, c, d, e, f)                (struct sigaltstack const *)a, (struct sigaltstack *)b
#define __NRAM_sendfile(a, b, c, d, e, f)                   (__fd_t)a, (__fd_t)b, (__syscall_ulong_t *)c, (__size_t)d
#define __NRAM_vfork(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_mmap2(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NRAM_truncate64(a, b, c, d, e, f)                 (char const *)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NRAM_ftruncate64(a, b, c, d, e, f)                (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NRAM_linux_stat64(a, b, c, d, e, f)               (char const *)a, (struct linux_stat64 *)b
#define __NRAM_linux_lstat64(a, b, c, d, e, f)              (char const *)a, (struct linux_stat64 *)b
#define __NRAM_linux_fstat64(a, b, c, d, e, f)              (__fd_t)a, (struct linux_stat64 *)b
#define __NRAM_lchown32(a, b, c, d, e, f)                   (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_getuid32(a, b, c, d, e, f)                   /* nothing */
#define __NRAM_getgid32(a, b, c, d, e, f)                   /* nothing */
#define __NRAM_geteuid32(a, b, c, d, e, f)                  /* nothing */
#define __NRAM_getegid32(a, b, c, d, e, f)                  /* nothing */
#define __NRAM_setreuid32(a, b, c, d, e, f)                 (__uint32_t)a, (__uint32_t)b
#define __NRAM_setregid32(a, b, c, d, e, f)                 (__uint32_t)a, (__uint32_t)b
#define __NRAM_getgroups32(a, b, c, d, e, f)                (__size_t)a, (/*[]*/__uint32_t *)b
#define __NRAM_setgroups32(a, b, c, d, e, f)                (__size_t)a, (__uint32_t const *)b
#define __NRAM_fchown32(a, b, c, d, e, f)                   (__fd_t)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_setresuid32(a, b, c, d, e, f)                (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_getresuid32(a, b, c, d, e, f)                (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NRAM_setresgid32(a, b, c, d, e, f)                (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_getresgid32(a, b, c, d, e, f)                (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NRAM_chown32(a, b, c, d, e, f)                    (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_setuid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NRAM_setgid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NRAM_setfsuid32(a, b, c, d, e, f)                 (__uint32_t)a
#define __NRAM_setfsgid32(a, b, c, d, e, f)                 (__uint32_t)a
#define __NRAM_mincore(a, b, c, d, e, f)                    (void *)a, (__size_t)b, (__uint8_t *)c
#define __NRAM_madvise(a, b, c, d, e, f)                    (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_getdents64(a, b, c, d, e, f)                 (__fd_t)a, (struct linux_dirent64 *)b, (__size_t)c
#define __NRAM_fcntl64(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NRAM_gettid(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_readahead(a, b, c, d, e, f)                  (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__size_t)d
#define __NRAM_setxattr(a, b, c, d, e, f)                   (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_lsetxattr(a, b, c, d, e, f)                  (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_fsetxattr(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_getxattr(a, b, c, d, e, f)                   (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_lgetxattr(a, b, c, d, e, f)                  (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_fgetxattr(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_listxattr(a, b, c, d, e, f)                  (char const *)a, (char *)b, (__size_t)c
#define __NRAM_llistxattr(a, b, c, d, e, f)                 (char const *)a, (char *)b, (__size_t)c
#define __NRAM_flistxattr(a, b, c, d, e, f)                 (__fd_t)a, (char *)b, (__size_t)c
#define __NRAM_removexattr(a, b, c, d, e, f)                (char const *)a, (char const *)b
#define __NRAM_lremovexattr(a, b, c, d, e, f)               (char const *)a, (char const *)b
#define __NRAM_fremovexattr(a, b, c, d, e, f)               (int)a, (char const *)b
#define __NRAM_tkill(a, b, c, d, e, f)                      (__pid_t)a, (__syscall_ulong_t)b
#define __NRAM_sendfile64(a, b, c, d, e, f)                 (__fd_t)a, (__fd_t)b, (__uint64_t *)c, (__size_t)d
#define __NRAM_futex(a, b, c, d, e, f)                      (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespec32 const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NRAM_sched_setaffinity(a, b, c, d, e, f)          (__pid_t)a, (__size_t)b, (struct __cpu_set_struct const *)c
#define __NRAM_sched_getaffinity(a, b, c, d, e, f)          (__pid_t)a, (__size_t)b, (struct __cpu_set_struct *)c
#define __NRAM_exit_group(a, b, c, d, e, f)                 (__syscall_ulong_t)a
#define __NRAM_epoll_create(a, b, c, d, e, f)               (__syscall_ulong_t)a
#define __NRAM_epoll_ctl(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b, (__fd_t)c, (struct epoll_event *)d
#define __NRAM_epoll_wait(a, b, c, d, e, f)                 (__fd_t)a, (struct epoll_event *)b, (__syscall_ulong_t)c, (__syscall_slong_t)d
#define __NRAM_remap_file_pages(a, b, c, d, e, f)           (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_set_tid_address(a, b, c, d, e, f)            (__pid_t *)a
#define __NRAM_timer_create(a, b, c, d, e, f)               (__clockid_t)a, (struct sigevent *)b, (__timer_t *)c
#define __NRAM_timer_settime(a, b, c, d, e, f)              (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspec32 const *)c, (struct __itimerspec32 *)d
#define __NRAM_timer_gettime(a, b, c, d, e, f)              (__timer_t)a, (struct __itimerspec32 *)b
#define __NRAM_timer_getoverrun(a, b, c, d, e, f)           (__timer_t)a
#define __NRAM_timer_delete(a, b, c, d, e, f)               (__timer_t)a
#define __NRAM_clock_settime(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespec32 const *)b
#define __NRAM_clock_gettime(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespec32 *)b
#define __NRAM_clock_getres(a, b, c, d, e, f)               (__clockid_t)a, (struct __timespec32 *)b
#define __NRAM_clock_nanosleep(a, b, c, d, e, f)            (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespec32 const *)c, (struct __timespec32 *)d
#define __NRAM_statfs64(a, b, c, d, e, f)                   (char const *)a, (struct statfs64 *)b
#define __NRAM_fstatfs64(a, b, c, d, e, f)                  (__fd_t)a, (struct statfs64 *)b
#define __NRAM_tgkill(a, b, c, d, e, f)                     (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c
#define __NRAM_utimes(a, b, c, d, e, f)                     (char const *)a, (/*[2]*/struct __timeval32 const *)b
#define __NRAM_waitid(a, b, c, d, e, f)                     (__idtype_t)a, (__id_t)b, (struct __siginfo_struct *)c, (__syscall_ulong_t)d, (struct rusage *)e
#define __NRAM_ioprio_set(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_ioprio_get(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAM_openat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__oflag_t)c, (__mode_t)d
#define __NRAM_mkdirat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__mode_t)c
#define __NRAM_mknodat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d
#define __NRAM_fchownat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__uint32_t)c, (__uint32_t)d, (__atflag_t)e
#define __NRAM_futimesat(a, b, c, d, e, f)                  (__fd_t)a, (const char *)b, (/*[2]*/struct __timeval32 const *)c
#define __NRAM_linux_fstatat64(a, b, c, d, e, f)            (__fd_t)a, (char const *)b, (struct linux_stat64 *)c, (__atflag_t)d
#define __NRAM_unlinkat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NRAM_renameat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d
#define __NRAM_linkat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NRAM_symlinkat(a, b, c, d, e, f)                  (char const *)a, (__fd_t)b, (char const *)c
#define __NRAM_readlinkat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (char *)c, (__size_t)d
#define __NRAM_fchmodat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NRAM_faccessat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__syscall_ulong_t)c, (__atflag_t)d
#define __NRAM_pselect6(a, b, c, d, e, f)                   (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespec32 const *)e, (void const *)f
#define __NRAM_ppoll(a, b, c, d, e, f)                      (struct pollfd *)a, (__size_t)b, (struct __timespec32 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NRAM_unshare(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NRAM_splice(a, b, c, d, e, f)                     (__fd_t)a, (__uint64_t *)b, (__fd_t)c, (__uint64_t *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_sync_file_range(a, b, c, d, e, f)            (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__syscall_ulong_t)f
#define __NRAM_tee(a, b, c, d, e, f)                        (__fd_t)a, (__fd_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_vmsplice(a, b, c, d, e, f)                   (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_getcpu(a, b, c, d, e, f)                     (__uint32_t *)a, (__uint32_t *)b, (struct getcpu_cache *)c
#define __NRAM_epoll_pwait(a, b, c, d, e, f)                (__fd_t)a, (struct epoll_event *)b, (__syscall_ulong_t)c, (__syscall_slong_t)d, (struct __sigset_struct const *)e
#define __NRAM_utimensat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (/*[2-3]*/struct __timespec32 const *)c, (__atflag_t)d
#define __NRAM_timerfd_create(a, b, c, d, e, f)             (__clockid_t)a, (__syscall_ulong_t)b
#define __NRAM_eventfd(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NRAM_fallocate(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b, (__uint32_t)c, (__uint32_t)d
#define __NRAM_timerfd_settime(a, b, c, d, e, f)            (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspec32 const *)c, (struct __itimerspec32 *)d
#define __NRAM_timerfd_gettime(a, b, c, d, e, f)            (__fd_t)a, (struct __itimerspec32 *)b
#define __NRAM_eventfd2(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAM_epoll_create1(a, b, c, d, e, f)              (__syscall_ulong_t)a
#define __NRAM_dup3(a, b, c, d, e, f)                       (__fd_t)a, (__fd_t)b, (__oflag_t)c
#define __NRAM_pipe2(a, b, c, d, e, f)                      (/*[2]*/__fd_t *)a, (__oflag_t)b
#define __NRAM_preadv(a, b, c, d, e, f)                     (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_pwritev(a, b, c, d, e, f)                    (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_rt_tgsigqueueinfo(a, b, c, d, e, f)          (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (struct __siginfo_struct const *)d
#define __NRAM_recvmmsg(a, b, c, d, e, f)                   (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespec32 *)e
#define __NRAM_prlimit64(a, b, c, d, e, f)                  (__pid_t)a, (__syscall_ulong_t)b, (struct rlimit64 const *)c, (struct rlimit64 *)d
#define __NRAM_name_to_handle_at(a, b, c, d, e, f)          (__fd_t)a, (char const *)b, (struct file_handle *)c, (__int32_t *)d, (__syscall_ulong_t)e
#define __NRAM_open_by_handle_at(a, b, c, d, e, f)          (__fd_t)a, (struct file_handle *)b, (__syscall_ulong_t)c
#define __NRAM_syncfs(a, b, c, d, e, f)                     (__fd_t)a
#define __NRAM_sendmmsg(a, b, c, d, e, f)                   (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_setns(a, b, c, d, e, f)                      (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_process_vm_readv(a, b, c, d, e, f)           (__pid_t)a, (struct iovec const *)b, (__size_t)c, (struct iovec const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_process_vm_writev(a, b, c, d, e, f)          (__pid_t)a, (struct iovec const *)b, (__size_t)c, (struct iovec const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_kcmp(a, b, c, d, e, f)                       (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAM_renameat2(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__syscall_ulong_t)e
#define __NRAM_execveat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (char const *const *)c, (char const *const *)d, (__atflag_t)e
#define __NRAM_socket(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_socketpair(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (/*[2]*/__fd_t *)d
#define __NRAM_bind(a, b, c, d, e, f)                       (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NRAM_connect(a, b, c, d, e, f)                    (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NRAM_listen(a, b, c, d, e, f)                     (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_accept4(a, b, c, d, e, f)                    (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c, (__syscall_ulong_t)d
#define __NRAM_getsockopt(a, b, c, d, e, f)                 (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void *)d, (__socklen_t *)e
#define __NRAM_setsockopt(a, b, c, d, e, f)                 (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void const *)d, (__socklen_t)e
#define __NRAM_getsockname(a, b, c, d, e, f)                (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NRAM_getpeername(a, b, c, d, e, f)                (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NRAM_sendto(a, b, c, d, e, f)                     (__fd_t)a, (void const *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr const *)e, (__socklen_t)f
#define __NRAM_sendmsg(a, b, c, d, e, f)                    (__fd_t)a, (struct msghdr const *)b, (__syscall_ulong_t)c
#define __NRAM_recvfrom(a, b, c, d, e, f)                   (__fd_t)a, (void *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr *)e, (__socklen_t *)f
#define __NRAM_recvmsg(a, b, c, d, e, f)                    (__fd_t)a, (struct msghdr *)b, (__syscall_ulong_t)c
#define __NRAM_shutdown(a, b, c, d, e, f)                   (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_hop(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_ulong_t)b, (void *)c
#define __NRAM_hopf(a, b, c, d, e, f)                       (__fd_t)a, (__syscall_ulong_t)b, (__iomode_t)c, (void *)d
#define __NRAM_readf(a, b, c, d, e, f)                      (__fd_t)a, (void *)b, (__size_t)c, (__iomode_t)d
#define __NRAM_writef(a, b, c, d, e, f)                     (__fd_t)a, (void const *)b, (__size_t)c, (__iomode_t)d
#define __NRAM_detach(a, b, c, d, e, f)                     (__pid_t)a
#define __NRAM_getdrives(a, b, c, d, e, f)                  /* nothing */
#define __NRAM_frealpath4(a, b, c, d, e, f)                 (__fd_t)a, (char *)b, (__size_t)c, (__atflag_t)d
#define __NRAM_frealpathat(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NRAM_rpc_schedule(a, b, c, d, e, f)               (__pid_t)a, (__syscall_ulong_t)b, (__uint8_t const *)c, (void **)d
#define __NRAM_sysctl(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (void *)b
#define __NRAM_openpty(a, b, c, d, e, f)                    (__fd_t *)a, (__fd_t *)b, (char *)c, (struct termios const *)d, (struct winsize const *)e
#define __NRAM_fchdirat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NRAM_time64(a, b, c, d, e, f)                     (__time64_t *)a
#define __NRAM_set_exception_handler(a, b, c, d, e, f)      (__syscall_ulong_t)a, (__except_handler_t)b, (void *)c
#define __NRAM_get_exception_handler(a, b, c, d, e, f)      (__syscall_ulong_t *)a, (__except_handler_t *)b, (void **)c
#define __NRAM_set_library_listdef(a, b, c, d, e, f)        (struct library_listdef const *)a
#define __NRAM_debugtrap(a, b, c, d, e, f)                  (struct ucpustate const *)a, (__syscall_ulong_t)b, (struct debug_trap_register const *)c
#define __NRAM_lfutex(a, b, c, d, e, f)                     (__uintptr_t *)a, (__syscall_ulong_t)b, (__uintptr_t)c, (struct __timespec64 const *)d, (__uintptr_t)e
#define __NRAM_lseek64(a, b, c, d, e, f)                    (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__syscall_ulong_t)d
#define __NRAM_lfutexlock(a, b, c, d, e, f)                 (__uintptr_t *)a, (__uintptr_t *)b, (__syscall_ulong_t)c, (__uintptr_t)d, (struct __timespec64 const *)e, (__uintptr_t)f
#define __NRAM_lfutexexpr(a, b, c, d, e, f)                 (__uintptr_t *)a, (void *)b, (struct lfutexexpr const *)c, (__size_t)d, (struct __timespec64 const *)e, (__syscall_ulong_t)f
#define __NRAM_lfutexlockexpr(a, b, c, d, e, f)             (__uintptr_t *)a, (void *)b, (struct lfutexexpr const *)c, (__size_t)d, (struct __timespec64 const *)e, (__syscall_ulong_t)f
#define __NRAM_mktty(a, b, c, d, e, f)                      (__fd_t)a, (__fd_t)b, (char const *)c, (__syscall_ulong_t)d
#define __NRAM_raiseat(a, b, c, d, e, f)                    (struct ucpustate const *)a, (struct __siginfo_struct const *)b
#define __NRAM_stime64(a, b, c, d, e, f)                    (__time64_t const *)a
#define __NRAM_coredump(a, b, c, d, e, f)                   (struct ucpustate const *)a, (struct ucpustate const *)b, (void const *const *)c, (__size_t)d, (struct exception_data const *)e, (__syscall_ulong_t)f
#define __NRAM_utime64(a, b, c, d, e, f)                    (char const *)a, (struct utimbuf64 const *)b
#define __NRAM_ioctlf(a, b, c, d, e, f)                     (__fd_t)a, (__syscall_ulong_t)b, (__iomode_t)c, (void *)d
#define __NRAM_fsmode(a, b, c, d, e, f)                     (__uint64_t)((__uint64_t)a | (__uint64_t)b << 32)
#define __NRAM_gettimeofday64(a, b, c, d, e, f)             (struct __timeval64 *)a, (struct timezone *)b
#define __NRAM_settimeofday64(a, b, c, d, e, f)             (struct __timeval64 const *)a, (struct timezone const *)b
#define __NRAM_select64(a, b, c, d, e, f)                   (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timeval64 *)e
#define __NRAM_maplibrary(a, b, c, d, e, f)                 (void *)a, (__syscall_ulong_t)b, (__fd_t)c, (void *)d, (__size_t)e
#define __NRAM_setitimer64(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __itimerval64 const *)b, (struct __itimerval64 *)c
#define __NRAM_getitimer64(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __itimerval64 *)b
#define __NRAM_kreaddir(a, b, c, d, e, f)                   (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_readvf(a, b, c, d, e, f)                     (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__iomode_t)d
#define __NRAM_writevf(a, b, c, d, e, f)                    (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__iomode_t)d
#define __NRAM_rpc_service(a, b, c, d, e, f)                /* nothing */
#define __NRAM_sched_rr_get_interval64(a, b, c, d, e, f)    (__pid_t)a, (struct __timespec64 *)b
#define __NRAM_nanosleep64(a, b, c, d, e, f)                (struct __timespec64 const *)a, (struct __timespec64 *)b
#define __NRAM_rt_sigtimedwait64(a, b, c, d, e, f)          (struct __sigset_struct const *)a, (struct __siginfo_struct *)b, (struct __timespec64 const *)c, (__size_t)d
#define __NRAM_pread64f(a, b, c, d, e, f)                   (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_pwrite64f(a, b, c, d, e, f)                  (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_kstat(a, b, c, d, e, f)                      (char const *)a, (struct stat *)b
#define __NRAM_klstat(a, b, c, d, e, f)                     (char const *)a, (struct stat *)b
#define __NRAM_kfstat(a, b, c, d, e, f)                     (__fd_t)a, (struct stat *)b
#define __NRAM_kreaddirf(a, b, c, d, e, f)                  (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d, (__iomode_t)e
#define __NRAM_timer_settime64(a, b, c, d, e, f)            (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspec64 const *)c, (struct __itimerspec64 *)d
#define __NRAM_timer_gettime64(a, b, c, d, e, f)            (__timer_t)a, (struct __itimerspec64 *)b
#define __NRAM_clock_settime64(a, b, c, d, e, f)            (__clockid_t)a, (struct __timespec64 const *)b
#define __NRAM_clock_gettime64(a, b, c, d, e, f)            (__clockid_t)a, (struct __timespec64 *)b
#define __NRAM_clock_getres64(a, b, c, d, e, f)             (__clockid_t)a, (struct __timespec64 *)b
#define __NRAM_clock_nanosleep64(a, b, c, d, e, f)          (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespec64 const *)c, (struct __timespec64 *)d
#define __NRAM_utimes64(a, b, c, d, e, f)                   (char const *)a, (/*[2]*/struct __timeval64 const *)b
#define __NRAM_fmkdirat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NRAM_fmknodat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d, (__atflag_t)e
#define __NRAM_futimesat64(a, b, c, d, e, f)                (__fd_t)a, (const char *)b, (/*[2-3]*/struct __timeval64 const *)c
#define __NRAM_kfstatat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (struct stat *)c, (__atflag_t)d
#define __NRAM_frenameat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NRAM_fsymlinkat(a, b, c, d, e, f)                 (char const *)a, (__fd_t)b, (char const *)c, (__atflag_t)d
#define __NRAM_freadlinkat(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NRAM_pselect6_64(a, b, c, d, e, f)                (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespec64 const *)e, (void const *)f
#define __NRAM_ppoll64(a, b, c, d, e, f)                    (struct pollfd *)a, (__size_t)b, (struct __timespec64 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NRAM_utimensat64(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (/*[2-3]*/struct __timespec64 const *)c, (__atflag_t)d
#define __NRAM_fallocate64(a, b, c, d, e, f)                (__fd_t)a, (__syscall_ulong_t)b, (__uint64_t)((__uint64_t)c | (__uint64_t)d << 32), (__uint64_t)((__uint64_t)e | (__uint64_t)f << 32)
#define __NRAM_timerfd_settime64(a, b, c, d, e, f)          (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspec64 const *)c, (struct __itimerspec64 *)d
#define __NRAM_timerfd_gettime64(a, b, c, d, e, f)          (__fd_t)a, (struct __itimerspec64 *)b
#define __NRAM_preadvf(a, b, c, d, e, f)                    (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_pwritevf(a, b, c, d, e, f)                   (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_recvmmsg64(a, b, c, d, e, f)                 (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespec64 *)e
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_MAKER */

#ifdef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#define __NRAP_exit(a)                                      (__syscall_ulong_t)a
#define __NRAP_fork()                                         /* nothing */
#define __NRAP_read(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_write(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_open(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_close(a)                                     (__syscall_ulong_t)a
#define __NRAP_waitpid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_creat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_link(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_unlink(a)                                    (__syscall_ulong_t)a
#define __NRAP_execve(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chdir(a)                                     (__syscall_ulong_t)a
#define __NRAP_time(a)                                      (__syscall_ulong_t)a
#define __NRAP_mknod(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chmod(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lchown(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_linux_oldstat(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lseek(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpid()                                       /* nothing */
#define __NRAP_mount(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_umount(a)                                    (__syscall_ulong_t)a
#define __NRAP_setuid(a)                                    (__syscall_ulong_t)a
#define __NRAP_getuid()                                       /* nothing */
#define __NRAP_stime(a)                                     (__syscall_ulong_t)a
#define __NRAP_ptrace(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_alarm(a)                                     (__syscall_ulong_t)a
#define __NRAP_linux_oldfstat(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pause()                                        /* nothing */
#define __NRAP_utime(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_access(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_nice(a)                                      (__syscall_ulong_t)a
#define __NRAP_ftime(a)                                     (__syscall_ulong_t)a
#define __NRAP_sync()                                         /* nothing */
#define __NRAP_kill(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rename(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mkdir(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rmdir(a)                                     (__syscall_ulong_t)a
#define __NRAP_dup(a)                                       (__syscall_ulong_t)a
#define __NRAP_pipe(a)                                      (__syscall_ulong_t)a
#define __NRAP_times(a)                                     (__syscall_ulong_t)a
#define __NRAP_brk(a)                                       (__syscall_ulong_t)a
#define __NRAP_setgid(a)                                    (__syscall_ulong_t)a
#define __NRAP_getgid()                                       /* nothing */
#define __NRAP_signal(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_geteuid()                                      /* nothing */
#define __NRAP_getegid()                                      /* nothing */
#define __NRAP_acct(a)                                      (__syscall_ulong_t)a
#define __NRAP_umount2(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ioctl(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_fcntl(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setpgid(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_oldolduname(a)                               (__syscall_ulong_t)a
#define __NRAP_umask(a)                                     (__syscall_ulong_t)a
#define __NRAP_chroot(a)                                    (__syscall_ulong_t)a
#define __NRAP_ustat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_dup2(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getppid()                                      /* nothing */
#define __NRAP_getpgrp()                                      /* nothing */
#define __NRAP_setsid()                                       /* nothing */
#define __NRAP_sigaction(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sgetmask()                                     /* nothing */
#define __NRAP_ssetmask(a)                                  (__syscall_ulong_t)a
#define __NRAP_setreuid(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setregid(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sigsuspend(a)                                (__syscall_ulong_t)a
#define __NRAP_sigpending(a)                                (__syscall_ulong_t)a
#define __NRAP_sethostname(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setrlimit(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getrlimit(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getrusage(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_gettimeofday(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_settimeofday(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getgroups(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setgroups(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_select(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_symlink(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_linux_oldlstat(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_readlink(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_swapon(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_reboot(a)                                    (__syscall_ulong_t)a
#define __NRAP_readdir(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mmap(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_munmap(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_truncate(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ftruncate(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fchmod(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fchown(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpriority(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setpriority(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_profil(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_statfs(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fstatfs(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ioperm(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_socketcall(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_syslog(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setitimer(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getitimer(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_linux_stat32(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_linux_lstat32(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_linux_fstat32(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_olduname(a)                                  (__syscall_ulong_t)a
#define __NRAP_iopl(a)                                      (__syscall_ulong_t)a
#define __NRAP_vhangup()                                      /* nothing */
#define __NRAP_wait4(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_swapoff(a)                                   (__syscall_ulong_t)a
#define __NRAP_sysinfo(a)                                   (__syscall_ulong_t)a
#define __NRAP_fsync(a)                                     (__syscall_ulong_t)a
#define __NRAP_sigreturn(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_clone(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_setdomainname(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_uname(a)                                     (__syscall_ulong_t)a
#define __NRAP_modify_ldt(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mprotect(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sigprocmask(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpgid(a)                                   (__syscall_ulong_t)a
#define __NRAP_fchdir(a)                                    (__syscall_ulong_t)a
#define __NRAP_setfsuid(a)                                  (__syscall_ulong_t)a
#define __NRAP_setfsgid(a)                                  (__syscall_ulong_t)a
#define __NRAP__llseek(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getdents(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_flock(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_msync(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_readv(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_writev(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getsid(a)                                    (__syscall_ulong_t)a
#define __NRAP_fdatasync(a)                                 (__syscall_ulong_t)a
#define __NRAP_mlock(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_munlock(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mlockall(a)                                  (__syscall_ulong_t)a
#define __NRAP_munlockall()                                   /* nothing */
#define __NRAP_sched_setparam(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sched_getparam(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sched_setscheduler(a, b, c)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_getscheduler(a)                        (__syscall_ulong_t)a
#define __NRAP_sched_yield()                                  /* nothing */
#define __NRAP_sched_get_priority_max(a)                    (__syscall_ulong_t)a
#define __NRAP_sched_get_priority_min(a)                    (__syscall_ulong_t)a
#define __NRAP_sched_rr_get_interval(a, b)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_nanosleep(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mremap(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_setresuid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresuid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_poll(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setresgid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresgid(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_rt_sigaction(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigprocmask(a, b, c, d)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigpending(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rt_sigtimedwait(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigqueueinfo(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_rt_sigsuspend(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pread64(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_pwrite64(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_chown(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getcwd(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sigaltstack(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sendfile(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_vfork()                                        /* nothing */
#define __NRAP_mmap2(a, b, c, d, e, f)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_truncate64(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NRAP_ftruncate64(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NRAP_linux_stat64(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_linux_lstat64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_linux_fstat64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lchown32(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getuid32()                                     /* nothing */
#define __NRAP_getgid32()                                     /* nothing */
#define __NRAP_geteuid32()                                    /* nothing */
#define __NRAP_getegid32()                                    /* nothing */
#define __NRAP_setreuid32(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setregid32(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getgroups32(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setgroups32(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fchown32(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setresuid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresuid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setresgid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresgid32(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chown32(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setuid32(a)                                  (__syscall_ulong_t)a
#define __NRAP_setgid32(a)                                  (__syscall_ulong_t)a
#define __NRAP_setfsuid32(a)                                (__syscall_ulong_t)a
#define __NRAP_setfsgid32(a)                                (__syscall_ulong_t)a
#define __NRAP_mincore(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_madvise(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getdents64(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_fcntl64(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_gettid()                                       /* nothing */
#define __NRAP_readahead(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NRAP_setxattr(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_lsetxattr(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fsetxattr(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_getxattr(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_lgetxattr(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fgetxattr(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_listxattr(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_llistxattr(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_flistxattr(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_removexattr(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lremovexattr(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fremovexattr(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_tkill(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sendfile64(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_futex(a, b, c, d, e, f)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_sched_setaffinity(a, b, c)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_getaffinity(a, b, c)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_exit_group(a)                                (__syscall_ulong_t)a
#define __NRAP_epoll_create(a)                              (__syscall_ulong_t)a
#define __NRAP_epoll_ctl(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_epoll_wait(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_remap_file_pages(a, b, c, d, e)              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_set_tid_address(a)                           (__syscall_ulong_t)a
#define __NRAP_timer_create(a, b, c)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_timer_settime(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timer_gettime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_timer_getoverrun(a)                          (__syscall_ulong_t)a
#define __NRAP_timer_delete(a)                              (__syscall_ulong_t)a
#define __NRAP_clock_settime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_gettime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_getres(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_nanosleep(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_statfs64(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fstatfs64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_tgkill(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_utimes(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_waitid(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_ioprio_set(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_ioprio_get(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_openat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_mkdirat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mknodat(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fchownat(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_futimesat(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_linux_fstatat64(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_unlinkat(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_renameat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_linkat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_symlinkat(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_readlinkat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fchmodat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_faccessat(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pselect6(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_ppoll(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_unshare(a)                                   (__syscall_ulong_t)a
#define __NRAP_splice(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_sync_file_range(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d
#define __NRAP_tee(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_vmsplice(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getcpu(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_epoll_pwait(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_utimensat(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_create(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_eventfd(a)                                   (__syscall_ulong_t)a
#define __NRAP_fallocate(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_settime(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_gettime(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_eventfd2(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_epoll_create1(a)                             (__syscall_ulong_t)a
#define __NRAP_dup3(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_pipe2(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_preadv(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_pwritev(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_rt_tgsigqueueinfo(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_recvmmsg(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_prlimit64(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_name_to_handle_at(a, b, c, d, e)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_open_by_handle_at(a, b, c)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_syncfs(a)                                    (__syscall_ulong_t)a
#define __NRAP_sendmmsg(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_setns(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_process_vm_readv(a, b, c, d, e, f)           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_process_vm_writev(a, b, c, d, e, f)          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_kcmp(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_renameat2(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_execveat(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_socket(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_socketpair(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_bind(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_connect(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_listen(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_accept4(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getsockopt(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_setsockopt(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_getsockname(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpeername(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sendto(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_sendmsg(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_recvfrom(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_recvmsg(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shutdown(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_hop(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_hopf(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_readf(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_writef(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_detach(a)                                    (__syscall_ulong_t)a
#define __NRAP_getdrives()                                    /* nothing */
#define __NRAP_frealpath4(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_frealpathat(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_rpc_schedule(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_sysctl(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_openpty(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fchdirat(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_time64(a)                                    (__syscall_ulong_t)a
#define __NRAP_set_exception_handler(a, b, c)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_get_exception_handler(a, b, c)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_set_library_listdef(a)                       (__syscall_ulong_t)a
#define __NRAP_debugtrap(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_lfutex(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_lseek64(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NRAP_lfutexlock(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_lfutexexpr(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_lfutexlockexpr(a, b, c, d, e, f)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_mktty(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_raiseat(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_stime64(a)                                   (__syscall_ulong_t)a
#define __NRAP_coredump(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_utime64(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ioctlf(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fsmode(a)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)((__uint64_t)a >> 32)
#define __NRAP_gettimeofday64(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_settimeofday64(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_select64(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_maplibrary(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_setitimer64(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getitimer64(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_kreaddir(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_readvf(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_writevf(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rpc_service()                                  /* nothing */
#define __NRAP_sched_rr_get_interval64(a, b)                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_nanosleep64(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rt_sigtimedwait64(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pread64f(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_pwrite64f(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_kstat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_klstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_kfstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_kreaddirf(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_timer_settime64(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timer_gettime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_settime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_gettime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_getres64(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_nanosleep64(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_utimes64(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fmkdirat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fmknodat(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_futimesat64(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_kfstatat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_frenameat(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fsymlinkat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_freadlinkat(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_pselect6_64(a, b, c, d, e, f)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_ppoll64(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_utimensat64(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fallocate64(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_timerfd_settime64(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_gettime64(a, b)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_preadvf(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_pwritevf(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_recvmmsg64(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_PACKER */

#ifdef __WANT_SYSCALL_ATTR_NORETURN
#define __NRNT_exit                       1
#define __NRNT_exit_group                 1
#endif /* __WANT_SYSCALL_ATTR_NORETURN */

#ifdef __WANT_SYSCALL_DOUBLE_WIDE_RETURN_386
#define __NRDW386_time64                     1
#define __NRDW386_lseek64                    1
#define __NRDW386_fsmode                     1
#endif /* __WANT_SYSCALL_DOUBLE_WIDE_RETURN_386 */

#ifdef __WANT_SYSCALL_ARGUMENT_COUNT_386
#define __NRAC386_exit                       1
#define __NRAC386_fork                       0
#define __NRAC386_read                       3
#define __NRAC386_write                      3
#define __NRAC386_open                       3
#define __NRAC386_close                      1
#define __NRAC386_waitpid                    3
#define __NRAC386_creat                      2
#define __NRAC386_link                       2
#define __NRAC386_unlink                     1
#define __NRAC386_execve                     3
#define __NRAC386_chdir                      1
#define __NRAC386_time                       1
#define __NRAC386_mknod                      3
#define __NRAC386_chmod                      2
#define __NRAC386_lchown                     3
#define __NRAC386_linux_oldstat              2
#define __NRAC386_lseek                      3
#define __NRAC386_getpid                     0
#define __NRAC386_mount                      5
#define __NRAC386_umount                     1
#define __NRAC386_setuid                     1
#define __NRAC386_getuid                     0
#define __NRAC386_stime                      1
#define __NRAC386_ptrace                     4
#define __NRAC386_alarm                      1
#define __NRAC386_linux_oldfstat             2
#define __NRAC386_pause                      0
#define __NRAC386_utime                      2
#define __NRAC386_access                     2
#define __NRAC386_nice                       1
#define __NRAC386_ftime                      1
#define __NRAC386_sync                       0
#define __NRAC386_kill                       2
#define __NRAC386_rename                     2
#define __NRAC386_mkdir                      2
#define __NRAC386_rmdir                      1
#define __NRAC386_dup                        1
#define __NRAC386_pipe                       1
#define __NRAC386_times                      1
#define __NRAC386_brk                        1
#define __NRAC386_setgid                     1
#define __NRAC386_getgid                     0
#define __NRAC386_signal                     2
#define __NRAC386_geteuid                    0
#define __NRAC386_getegid                    0
#define __NRAC386_acct                       1
#define __NRAC386_umount2                    2
#define __NRAC386_ioctl                      3
#define __NRAC386_fcntl                      3
#define __NRAC386_setpgid                    2
#define __NRAC386_oldolduname                1
#define __NRAC386_umask                      1
#define __NRAC386_chroot                     1
#define __NRAC386_ustat                      2
#define __NRAC386_dup2                       2
#define __NRAC386_getppid                    0
#define __NRAC386_getpgrp                    0
#define __NRAC386_setsid                     0
#define __NRAC386_sigaction                  3
#define __NRAC386_sgetmask                   0
#define __NRAC386_ssetmask                   1
#define __NRAC386_setreuid                   2
#define __NRAC386_setregid                   2
#define __NRAC386_sigsuspend                 1
#define __NRAC386_sigpending                 1
#define __NRAC386_sethostname                2
#define __NRAC386_setrlimit                  2
#define __NRAC386_getrlimit                  2
#define __NRAC386_getrusage                  2
#define __NRAC386_gettimeofday               2
#define __NRAC386_settimeofday               2
#define __NRAC386_getgroups                  2
#define __NRAC386_setgroups                  2
#define __NRAC386_select                     5
#define __NRAC386_symlink                    2
#define __NRAC386_linux_oldlstat             2
#define __NRAC386_readlink                   3
#define __NRAC386_swapon                     2
#define __NRAC386_reboot                     1
#define __NRAC386_readdir                    3
#define __NRAC386_mmap                       6
#define __NRAC386_munmap                     2
#define __NRAC386_truncate                   2
#define __NRAC386_ftruncate                  2
#define __NRAC386_fchmod                     2
#define __NRAC386_fchown                     3
#define __NRAC386_getpriority                2
#define __NRAC386_setpriority                3
#define __NRAC386_profil                     4
#define __NRAC386_statfs                     2
#define __NRAC386_fstatfs                    2
#define __NRAC386_ioperm                     3
#define __NRAC386_socketcall                 2
#define __NRAC386_syslog                     3
#define __NRAC386_setitimer                  3
#define __NRAC386_getitimer                  2
#define __NRAC386_linux_stat32               2
#define __NRAC386_linux_lstat32              2
#define __NRAC386_linux_fstat32              2
#define __NRAC386_olduname                   1
#define __NRAC386_iopl                       1
#define __NRAC386_vhangup                    0
#define __NRAC386_wait4                      4
#define __NRAC386_swapoff                    1
#define __NRAC386_sysinfo                    1
#define __NRAC386_fsync                      1
#define __NRAC386_sigreturn                  6
#define __NRAC386_clone                      5
#define __NRAC386_setdomainname              2
#define __NRAC386_uname                      1
#define __NRAC386_modify_ldt                 3
#define __NRAC386_mprotect                   3
#define __NRAC386_sigprocmask                3
#define __NRAC386_getpgid                    1
#define __NRAC386_fchdir                     1
#define __NRAC386_setfsuid                   1
#define __NRAC386_setfsgid                   1
#define __NRAC386__llseek                    5
#define __NRAC386_getdents                   3
#define __NRAC386_flock                      2
#define __NRAC386_msync                      3
#define __NRAC386_readv                      3
#define __NRAC386_writev                     3
#define __NRAC386_getsid                     1
#define __NRAC386_fdatasync                  1
#define __NRAC386_mlock                      2
#define __NRAC386_munlock                    2
#define __NRAC386_mlockall                   1
#define __NRAC386_munlockall                 0
#define __NRAC386_sched_setparam             2
#define __NRAC386_sched_getparam             2
#define __NRAC386_sched_setscheduler         3
#define __NRAC386_sched_getscheduler         1
#define __NRAC386_sched_yield                0
#define __NRAC386_sched_get_priority_max     1
#define __NRAC386_sched_get_priority_min     1
#define __NRAC386_sched_rr_get_interval      2
#define __NRAC386_nanosleep                  2
#define __NRAC386_mremap                     5
#define __NRAC386_setresuid                  3
#define __NRAC386_getresuid                  3
#define __NRAC386_poll                       3
#define __NRAC386_setresgid                  3
#define __NRAC386_getresgid                  3
#define __NRAC386_rt_sigaction               4
#define __NRAC386_rt_sigprocmask             4
#define __NRAC386_rt_sigpending              2
#define __NRAC386_rt_sigtimedwait            4
#define __NRAC386_rt_sigqueueinfo            3
#define __NRAC386_rt_sigsuspend              2
#define __NRAC386_pread64                    5
#define __NRAC386_pwrite64                   5
#define __NRAC386_chown                      3
#define __NRAC386_getcwd                     2
#define __NRAC386_sigaltstack                2
#define __NRAC386_sendfile                   4
#define __NRAC386_vfork                      0
#define __NRAC386_mmap2                      6
#define __NRAC386_truncate64                 3
#define __NRAC386_ftruncate64                3
#define __NRAC386_linux_stat64               2
#define __NRAC386_linux_lstat64              2
#define __NRAC386_linux_fstat64              2
#define __NRAC386_lchown32                   3
#define __NRAC386_getuid32                   0
#define __NRAC386_getgid32                   0
#define __NRAC386_geteuid32                  0
#define __NRAC386_getegid32                  0
#define __NRAC386_setreuid32                 2
#define __NRAC386_setregid32                 2
#define __NRAC386_getgroups32                2
#define __NRAC386_setgroups32                2
#define __NRAC386_fchown32                   3
#define __NRAC386_setresuid32                3
#define __NRAC386_getresuid32                3
#define __NRAC386_setresgid32                3
#define __NRAC386_getresgid32                3
#define __NRAC386_chown32                    3
#define __NRAC386_setuid32                   1
#define __NRAC386_setgid32                   1
#define __NRAC386_setfsuid32                 1
#define __NRAC386_setfsgid32                 1
#define __NRAC386_mincore                    3
#define __NRAC386_madvise                    3
#define __NRAC386_getdents64                 3
#define __NRAC386_fcntl64                    3
#define __NRAC386_gettid                     0
#define __NRAC386_readahead                  4
#define __NRAC386_setxattr                   5
#define __NRAC386_lsetxattr                  5
#define __NRAC386_fsetxattr                  5
#define __NRAC386_getxattr                   4
#define __NRAC386_lgetxattr                  4
#define __NRAC386_fgetxattr                  4
#define __NRAC386_listxattr                  3
#define __NRAC386_llistxattr                 3
#define __NRAC386_flistxattr                 3
#define __NRAC386_removexattr                2
#define __NRAC386_lremovexattr               2
#define __NRAC386_fremovexattr               2
#define __NRAC386_tkill                      2
#define __NRAC386_sendfile64                 4
#define __NRAC386_futex                      6
#define __NRAC386_sched_setaffinity          3
#define __NRAC386_sched_getaffinity          3
#define __NRAC386_exit_group                 1
#define __NRAC386_epoll_create               1
#define __NRAC386_epoll_ctl                  4
#define __NRAC386_epoll_wait                 4
#define __NRAC386_remap_file_pages           5
#define __NRAC386_set_tid_address            1
#define __NRAC386_timer_create               3
#define __NRAC386_timer_settime              4
#define __NRAC386_timer_gettime              2
#define __NRAC386_timer_getoverrun           1
#define __NRAC386_timer_delete               1
#define __NRAC386_clock_settime              2
#define __NRAC386_clock_gettime              2
#define __NRAC386_clock_getres               2
#define __NRAC386_clock_nanosleep            4
#define __NRAC386_statfs64                   2
#define __NRAC386_fstatfs64                  2
#define __NRAC386_tgkill                     3
#define __NRAC386_utimes                     2
#define __NRAC386_waitid                     5
#define __NRAC386_ioprio_set                 3
#define __NRAC386_ioprio_get                 2
#define __NRAC386_openat                     4
#define __NRAC386_mkdirat                    3
#define __NRAC386_mknodat                    4
#define __NRAC386_fchownat                   5
#define __NRAC386_futimesat                  3
#define __NRAC386_linux_fstatat64            4
#define __NRAC386_unlinkat                   3
#define __NRAC386_renameat                   4
#define __NRAC386_linkat                     5
#define __NRAC386_symlinkat                  3
#define __NRAC386_readlinkat                 4
#define __NRAC386_fchmodat                   4
#define __NRAC386_faccessat                  4
#define __NRAC386_pselect6                   6
#define __NRAC386_ppoll                      5
#define __NRAC386_unshare                    1
#define __NRAC386_splice                     6
#define __NRAC386_sync_file_range            6
#define __NRAC386_tee                        4
#define __NRAC386_vmsplice                   4
#define __NRAC386_getcpu                     3
#define __NRAC386_epoll_pwait                5
#define __NRAC386_utimensat                  4
#define __NRAC386_timerfd_create             2
#define __NRAC386_eventfd                    1
#define __NRAC386_fallocate                  4
#define __NRAC386_timerfd_settime            4
#define __NRAC386_timerfd_gettime            2
#define __NRAC386_eventfd2                   2
#define __NRAC386_epoll_create1              1
#define __NRAC386_dup3                       3
#define __NRAC386_pipe2                      2
#define __NRAC386_preadv                     5
#define __NRAC386_pwritev                    5
#define __NRAC386_rt_tgsigqueueinfo          4
#define __NRAC386_recvmmsg                   5
#define __NRAC386_prlimit64                  4
#define __NRAC386_name_to_handle_at          5
#define __NRAC386_open_by_handle_at          3
#define __NRAC386_syncfs                     1
#define __NRAC386_sendmmsg                   4
#define __NRAC386_setns                      2
#define __NRAC386_process_vm_readv           6
#define __NRAC386_process_vm_writev          6
#define __NRAC386_kcmp                       5
#define __NRAC386_renameat2                  5
#define __NRAC386_execveat                   5
#define __NRAC386_socket                     3
#define __NRAC386_socketpair                 4
#define __NRAC386_bind                       3
#define __NRAC386_connect                    3
#define __NRAC386_listen                     2
#define __NRAC386_accept4                    4
#define __NRAC386_getsockopt                 5
#define __NRAC386_setsockopt                 5
#define __NRAC386_getsockname                3
#define __NRAC386_getpeername                3
#define __NRAC386_sendto                     6
#define __NRAC386_sendmsg                    3
#define __NRAC386_recvfrom                   6
#define __NRAC386_recvmsg                    3
#define __NRAC386_shutdown                   2
#define __NRAC386_hop                        3
#define __NRAC386_hopf                       4
#define __NRAC386_readf                      4
#define __NRAC386_writef                     4
#define __NRAC386_detach                     1
#define __NRAC386_getdrives                  0
#define __NRAC386_frealpath4                 4
#define __NRAC386_frealpathat                5
#define __NRAC386_rpc_schedule               4
#define __NRAC386_sysctl                     2
#define __NRAC386_openpty                    5
#define __NRAC386_fchdirat                   3
#define __NRAC386_time64                     1
#define __NRAC386_set_exception_handler      3
#define __NRAC386_get_exception_handler      3
#define __NRAC386_set_library_listdef        1
#define __NRAC386_debugtrap                  3
#define __NRAC386_lfutex                     5
#define __NRAC386_lseek64                    4
#define __NRAC386_lfutexlock                 6
#define __NRAC386_lfutexexpr                 6
#define __NRAC386_lfutexlockexpr             6
#define __NRAC386_mktty                      4
#define __NRAC386_raiseat                    2
#define __NRAC386_stime64                    1
#define __NRAC386_coredump                   6
#define __NRAC386_utime64                    2
#define __NRAC386_ioctlf                     4
#define __NRAC386_fsmode                     2
#define __NRAC386_gettimeofday64             2
#define __NRAC386_settimeofday64             2
#define __NRAC386_select64                   5
#define __NRAC386_maplibrary                 5
#define __NRAC386_setitimer64                3
#define __NRAC386_getitimer64                2
#define __NRAC386_kreaddir                   4
#define __NRAC386_readvf                     4
#define __NRAC386_writevf                    4
#define __NRAC386_rpc_service                0
#define __NRAC386_sched_rr_get_interval64    2
#define __NRAC386_nanosleep64                2
#define __NRAC386_rt_sigtimedwait64          4
#define __NRAC386_pread64f                   6
#define __NRAC386_pwrite64f                  6
#define __NRAC386_kstat                      2
#define __NRAC386_klstat                     2
#define __NRAC386_kfstat                     2
#define __NRAC386_kreaddirf                  5
#define __NRAC386_timer_settime64            4
#define __NRAC386_timer_gettime64            2
#define __NRAC386_clock_settime64            2
#define __NRAC386_clock_gettime64            2
#define __NRAC386_clock_getres64             2
#define __NRAC386_clock_nanosleep64          4
#define __NRAC386_utimes64                   2
#define __NRAC386_fmkdirat                   4
#define __NRAC386_fmknodat                   5
#define __NRAC386_futimesat64                3
#define __NRAC386_kfstatat                   4
#define __NRAC386_frenameat                  5
#define __NRAC386_fsymlinkat                 4
#define __NRAC386_freadlinkat                5
#define __NRAC386_pselect6_64                6
#define __NRAC386_ppoll64                    5
#define __NRAC386_utimensat64                4
#define __NRAC386_fallocate64                6
#define __NRAC386_timerfd_settime64          4
#define __NRAC386_timerfd_gettime64          2
#define __NRAC386_preadvf                    6
#define __NRAC386_pwritevf                   6
#define __NRAC386_recvmmsg64                 5
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT_386 */

