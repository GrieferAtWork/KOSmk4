/* HASH CRC-32:0x358602e5 */
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

/************************************************************************/
/* SYSCALL IDS                                                          */
/************************************************************************/
#ifndef __NR64_read
#define __NR64_read                   0x0                            /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
#define __NR64_write                  0x1                            /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
#define __NR64_open                   0x2                            /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `FD' */
#define __NR64_close                  0x3                            /* errno_t close(fd_t fd) */
#define __NR64_linux_stat64           0x4                            /* errno_t linux_stat64(char const *filename, struct linux_stat64 *statbuf) */
#define __NR64_linux_fstat64          0x5                            /* errno_t linux_fstat64(fd_t fd, struct linux_stat64 *statbuf) */
#define __NR64_linux_lstat64          0x6                            /* errno_t linux_lstat64(char const *filename, struct linux_stat64 *statbuf) */
#define __NR64_poll                   0x7                            /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
#define __NR64_lseek64                0x8                            /* int64_t lseek64(fd_t fd, int64_t offset, syscall_ulong_t whence) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
#define __NR64_mmap                   0x9                            /* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
#define __NR64_mprotect               0xa                            /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
#define __NR64_munmap                 0xb                            /* errno_t munmap(void *addr, size_t len) */
#define __NR64_brk                    0xc                            /* errno_t brk(void *addr) */
#define __NR64_rt_sigaction           0xd                            /* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction64 const *act, struct sigaction64 *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR64_rt_sigprocmask         0xe                            /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
#define __NR64_rt_sigreturn           0xf                            /* void rt_sigreturn(struct fpustate const *restore_fpu, struct __sigset_struct const *restore_sigmask, struct rpc_syscall_info *sc_info, struct ucpustate const *restore_cpu) */
#define __NR64_ioctl                  0x10                           /* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
#define __NR64_pread64                0x11                           /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define __NR64_pwrite64               0x12                           /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
#define __NR64_readv                  0x13                           /* ssize_t readv(fd_t fd, struct iovec64 const *iovec, size_t count) */
#define __NR64_writev                 0x14                           /* ssize_t writev(fd_t fd, struct iovec64 const *iovec, size_t count) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define __NR64_access                 0x15                           /* errno_t access(char const *filename, syscall_ulong_t type) */
#define __NR64_pipe                   0x16                           /* errno_t pipe(fd_t[2] pipedes) */
#define __NR64_select                 0x17                           /* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timevalx64 *timeout) */
#define __NR64_sched_yield            0x18                           /* errno_t sched_yield(void) */
/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
#define __NR64_mremap                 0x19                           /* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define __NR64_msync                  0x1a                           /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
#define __NR64_mincore                0x1b                           /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define __NR64_madvise                0x1c                           /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
#define __NR64_shmget                 0x1d                           /* errno_t shmget(int TODO_PROTOTYPE) */
#define __NR64_shmat                  0x1e                           /* errno_t shmat(int TODO_PROTOTYPE) */
#define __NR64_shmctl                 0x1f                           /* errno_t shmctl(int TODO_PROTOTYPE) */
#define __NR64_dup                    0x20                           /* fd_t dup(fd_t fd) */
#define __NR64_dup2                   0x21                           /* fd_t dup2(fd_t oldfd, fd_t newfd) */
#define __NR64_pause                  0x22                           /* errno_t pause(void) */
#define __NR64_nanosleep              0x23                           /* errno_t nanosleep(struct __timespecx64 const *req, struct __timespecx64 *rem) */
#define __NR64_getitimer              0x24                           /* errno_t getitimer(syscall_ulong_t which, struct __itimerval32 *curr_value) */
#define __NR64_alarm                  0x25                           /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
#define __NR64_setitimer              0x26                           /* errno_t setitimer(syscall_ulong_t which, struct __itimerval32 const *newval, struct __itimerval32 *oldval) */
#define __NR64_getpid                 0x27                           /* pid_t getpid(void) */
#define __NR64_sendfile               0x28                           /* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *offset, size_t count) */
#define __NR64_socket                 0x29                           /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
#define __NR64_connect                0x2a                           /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR64_accept                 0x2b                           /* errno_t accept(int TODO_PROTOTYPE) */
/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
#define __NR64_sendto                 0x2c                           /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR64_recvfrom               0x2d                           /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
#define __NR64_sendmsg                0x2e                           /* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
#define __NR64_recvmsg                0x2f                           /* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t flags) */
/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
#define __NR64_shutdown               0x30                           /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
#define __NR64_bind                   0x31                           /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define __NR64_listen                 0x32                           /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
#define __NR64_getsockname            0x33                           /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
#define __NR64_getpeername            0x34                           /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
#define __NR64_socketpair             0x35                           /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define __NR64_setsockopt             0x36                           /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define __NR64_getsockopt             0x37                           /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
#define __NR64_clone                  0x38                           /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
#define __NR64_fork                   0x39                           /* pid_t fork(void) */
#define __NR64_vfork                  0x3a                           /* pid_t vfork(void) */
#define __NR64_execve                 0x3b                           /* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
#define __NR64_exit                   0x3c                           /* void exit(syscall_ulong_t status) */
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR64_wait4                  0x3d                           /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct __rusagex64 *usage) */
/* @param: signo: One of `SIG*' */
#define __NR64_kill                   0x3e                           /* errno_t kill(pid_t pid, syscall_ulong_t signo) */
#define __NR64_uname                  0x3f                           /* errno_t uname(struct utsname *name) */
#define __NR64_semget                 0x40                           /* errno_t semget(int TODO_PROTOTYPE) */
#define __NR64_semop                  0x41                           /* errno_t semop(int TODO_PROTOTYPE) */
#define __NR64_semctl                 0x42                           /* errno_t semctl(int TODO_PROTOTYPE) */
#define __NR64_shmdt                  0x43                           /* errno_t shmdt(int TODO_PROTOTYPE) */
#define __NR64_msgget                 0x44                           /* errno_t msgget(int TODO_PROTOTYPE) */
#define __NR64_msgsnd                 0x45                           /* errno_t msgsnd(int TODO_PROTOTYPE) */
#define __NR64_msgrcv                 0x46                           /* errno_t msgrcv(int TODO_PROTOTYPE) */
#define __NR64_msgctl                 0x47                           /* errno_t msgctl(int TODO_PROTOTYPE) */
#define __NR64_fcntl                  0x48                           /* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
#define __NR64_flock                  0x49                           /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
#define __NR64_fsync                  0x4a                           /* errno_t fsync(fd_t fd) */
#define __NR64_fdatasync              0x4b                           /* errno_t fdatasync(fd_t fd) */
#define __NR64_truncate               0x4c                           /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define __NR64_ftruncate              0x4d                           /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
#define __NR64_getdents               0x4e                           /* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
#define __NR64_getcwd                 0x4f                           /* ssize_t getcwd(char *buf, size_t size) */
#define __NR64_chdir                  0x50                           /* errno_t chdir(char const *path) */
#define __NR64_fchdir                 0x51                           /* errno_t fchdir(fd_t fd) */
#define __NR64_rename                 0x52                           /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define __NR64_mkdir                  0x53                           /* errno_t mkdir(char const *pathname, mode_t mode) */
#define __NR64_rmdir                  0x54                           /* errno_t rmdir(char const *path) */
#define __NR64_creat                  0x55                           /* fd_t creat(char const *filename, mode_t mode) */
#define __NR64_link                   0x56                           /* errno_t link(char const *existing_file, char const *link_file) */
#define __NR64_unlink                 0x57                           /* errno_t unlink(char const *filename) */
#define __NR64_symlink                0x58                           /* errno_t symlink(char const *link_text, char const *target_path) */
#define __NR64_readlink               0x59                           /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
#define __NR64_chmod                  0x5a                           /* errno_t chmod(char const *filename, mode_t mode) */
#define __NR64_fchmod                 0x5b                           /* errno_t fchmod(fd_t fd, mode_t mode) */
#define __NR64_chown                  0x5c                           /* errno_t chown(char const *filename, uid_t owner, gid_t group) */
#define __NR64_fchown                 0x5d                           /* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
#define __NR64_lchown                 0x5e                           /* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
#define __NR64_umask                  0x5f                           /* mode_t umask(mode_t mode) */
#define __NR64_gettimeofday           0x60                           /* errno_t gettimeofday(struct __timevalx64 *tv, struct timezone *tz) */
#define __NR64_getrlimit              0x61                           /* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
#define __NR64_getrusage              0x62                           /* errno_t getrusage(syscall_slong_t who, struct __rusagex64 *tv) */
#define __NR64_sysinfo                0x63                           /* errno_t sysinfo(struct sysinfo *info) */
#define __NR64_times                  0x64                           /* clock_t times(struct tms *buf) */
#define __NR64_ptrace                 0x65                           /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
#define __NR64_getuid                 0x66                           /* uid_t getuid(void) */
#define __NR64_syslog                 0x67                           /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
#define __NR64_getgid                 0x68                           /* gid_t getgid(void) */
#define __NR64_setuid                 0x69                           /* errno_t setuid(uid_t uid) */
#define __NR64_setgid                 0x6a                           /* errno_t setgid(gid_t gid) */
#define __NR64_geteuid                0x6b                           /* uid_t geteuid(void) */
#define __NR64_getegid                0x6c                           /* gid_t getegid(void) */
#define __NR64_setpgid                0x6d                           /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define __NR64_getppid                0x6e                           /* pid_t getppid(void) */
#define __NR64_getpgrp                0x6f                           /* pid_t getpgrp(void) */
#define __NR64_setsid                 0x70                           /* pid_t setsid(void) */
#define __NR64_setreuid               0x71                           /* errno_t setreuid(uid_t ruid, uid_t euid) */
#define __NR64_setregid               0x72                           /* errno_t setregid(gid_t rgid, gid_t egid) */
#define __NR64_getgroups              0x73                           /* errno_t getgroups(size_t size, gid_t[] list) */
#define __NR64_setgroups              0x74                           /* errno_t setgroups(size_t count, gid_t const *groups) */
#define __NR64_setresuid              0x75                           /* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
#define __NR64_getresuid              0x76                           /* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
#define __NR64_setresgid              0x77                           /* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
#define __NR64_getresgid              0x78                           /* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
#define __NR64_getpgid                0x79                           /* pid_t getpgid(pid_t pid) */
#define __NR64_setfsuid               0x7a                           /* errno_t setfsuid(uid_t uid) */
#define __NR64_setfsgid               0x7b                           /* errno_t setfsgid(gid_t gid) */
#define __NR64_getsid                 0x7c                           /* pid_t getsid(pid_t pid) */
#define __NR64_capget                 0x7d                           /* errno_t capget(int TODO_PROTOTYPE) */
#define __NR64_capset                 0x7e                           /* errno_t capset(int TODO_PROTOTYPE) */
#define __NR64_rt_sigpending          0x7f                           /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define __NR64_rt_sigtimedwait        0x80                           /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo64_struct *info, struct __timespecx64 const *timeout, size_t sigsetsize) */
/* @param: signo: One of `SIG*' */
#define __NR64_rt_sigqueueinfo        0x81                           /* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo64_struct const *uinfo) */
#define __NR64_rt_sigsuspend          0x82                           /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define __NR64_sigaltstack            0x83                           /* errno_t sigaltstack(struct sigaltstack64 const *ss, struct sigaltstack64 *oss) */
#define __NR64_utime                  0x84                           /* errno_t utime(char const *filename, struct utimbuf const *times) */
#define __NR64_mknod                  0x85                           /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define __NR64_uselib                 0x86                           /* errno_t uselib(char const *library) */
#define __NR64_personality            0x87                           /* errno_t personality(int TODO_PROTOTYPE) */
#define __NR64_ustat                  0x88                           /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
#define __NR64_statfs                 0x89                           /* errno_t statfs(char const *file, struct __statfs32 *buf) */
#define __NR64_fstatfs                0x8a                           /* errno_t fstatfs(fd_t file, struct __statfs32 *buf) */
#define __NR64_sysfs                  0x8b                           /* errno_t sysfs(int TODO_PROTOTYPE) */
#define __NR64_getpriority            0x8c                           /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
#define __NR64_setpriority            0x8d                           /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
#define __NR64_sched_setparam         0x8e                           /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
#define __NR64_sched_getparam         0x8f                           /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
#define __NR64_sched_setscheduler     0x90                           /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define __NR64_sched_getscheduler     0x91                           /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define __NR64_sched_get_priority_max 0x92                           /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define __NR64_sched_get_priority_min 0x93                           /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define __NR64_sched_rr_get_interval  0x94                           /* errno_t sched_rr_get_interval(pid_t pid, struct __timespecx64 *tms) */
#define __NR64_mlock                  0x95                           /* errno_t mlock(void const *addr, size_t len) */
#define __NR64_munlock                0x96                           /* errno_t munlock(void const *addr, size_t len) */
#define __NR64_mlockall               0x97                           /* errno_t mlockall(syscall_ulong_t flags) */
#define __NR64_munlockall             0x98                           /* errno_t munlockall(void) */
#define __NR64_vhangup                0x99                           /* errno_t vhangup(void) */
#define __NR64_modify_ldt             0x9a                           /* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
#define __NR64_pivot_root             0x9b                           /* errno_t pivot_root(int TODO_PROTOTYPE) */
#define __NR64__sysctl                0x9c                           /* errno_t _sysctl(int TODO_PROTOTYPE) */
#define __NR64_prctl                  0x9d                           /* errno_t prctl(int TODO_PROTOTYPE) */
#define __NR64_arch_prctl             0x9e                           /* errno_t arch_prctl(int TODO_PROTOTYPE) */
#define __NR64_adjtimex               0x9f                           /* errno_t adjtimex(int TODO_PROTOTYPE) */
#define __NR64_setrlimit              0xa0                           /* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
#define __NR64_chroot                 0xa1                           /* errno_t chroot(char const *path) */
#define __NR64_sync                   0xa2                           /* errno_t sync(void) */
#define __NR64_acct                   0xa3                           /* errno_t acct(char const *filename) */
#define __NR64_settimeofday           0xa4                           /* errno_t settimeofday(struct __timevalx64 const *tv, struct timezone const *tz) */
#define __NR64_mount                  0xa5                           /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
#define __NR64_umount2                0xa6                           /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define __NR64_swapon                 0xa7                           /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
#define __NR64_swapoff                0xa8                           /* errno_t swapoff(char const *pathname) */
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
#define __NR64_reboot                 0xa9                           /* errno_t reboot(syscall_ulong_t how) */
#define __NR64_sethostname            0xaa                           /* errno_t sethostname(char const *name, size_t len) */
#define __NR64_setdomainname          0xab                           /* errno_t setdomainname(char const *name, size_t len) */
#define __NR64_iopl                   0xac                           /* errno_t iopl(syscall_ulong_t level) */
#define __NR64_ioperm                 0xad                           /* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
#define __NR64_create_module          0xae                           /* errno_t create_module(int TODO_PROTOTYPE) */
#define __NR64_init_module            0xaf                           /* errno_t init_module(int TODO_PROTOTYPE) */
#define __NR64_delete_module          0xb0                           /* errno_t delete_module(int TODO_PROTOTYPE) */
#define __NR64_get_kernel_syms        0xb1                           /* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
#define __NR64_query_module           0xb2                           /* errno_t query_module(int TODO_PROTOTYPE) */
#define __NR64_quotactl               0xb3                           /* errno_t quotactl(int TODO_PROTOTYPE) */
#define __NR64_nfsservctl             0xb4                           /* errno_t nfsservctl(int TODO_PROTOTYPE) */
#define __NR64_getpmsg                0xb5                           /* errno_t getpmsg(int TODO_PROTOTYPE) */
#define __NR64_putpmsg                0xb6                           /* errno_t putpmsg(int TODO_PROTOTYPE) */
#define __NR64_afs_syscall            0xb7                           /* errno_t afs_syscall(int TODO_PROTOTYPE) */
#define __NR64_tuxcall                0xb8                           /* errno_t tuxcall(int TODO_PROTOTYPE) */
#define __NR64_security               0xb9                           /* errno_t security(int TODO_PROTOTYPE) */
#define __NR64_gettid                 0xba                           /* pid_t gettid(void) */
#define __NR64_readahead              0xbb                           /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
#define __NR64_setxattr               0xbc                           /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR64_lsetxattr              0xbd                           /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR64_fsetxattr              0xbe                           /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR64_getxattr               0xbf                           /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR64_lgetxattr              0xc0                           /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR64_fgetxattr              0xc1                           /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define __NR64_listxattr              0xc2                           /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR64_llistxattr             0xc3                           /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR64_flistxattr             0xc4                           /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define __NR64_removexattr            0xc5                           /* errno_t removexattr(char const *path, char const *name) */
#define __NR64_lremovexattr           0xc6                           /* errno_t lremovexattr(char const *path, char const *name) */
#define __NR64_fremovexattr           0xc7                           /* errno_t fremovexattr(int fd, char const *name) */
#define __NR64_tkill                  0xc8                           /* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
#define __NR64_time                   0xc9                           /* time32_t time(time32_t *timer) */
#define __NR64_futex                  0xca                           /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespecx64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define __NR64_sched_setaffinity      0xcb                           /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define __NR64_sched_getaffinity      0xcc                           /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define __NR64_set_thread_area        0xcd                           /* errno_t set_thread_area(int TODO_PROTOTYPE) */
#define __NR64_io_setup               0xce                           /* errno_t io_setup(int TODO_PROTOTYPE) */
#define __NR64_io_destroy             0xcf                           /* errno_t io_destroy(int TODO_PROTOTYPE) */
#define __NR64_io_getevents           0xd0                           /* errno_t io_getevents(int TODO_PROTOTYPE) */
#define __NR64_io_submit              0xd1                           /* errno_t io_submit(int TODO_PROTOTYPE) */
#define __NR64_io_cancel              0xd2                           /* errno_t io_cancel(int TODO_PROTOTYPE) */
#define __NR64_get_thread_area        0xd3                           /* errno_t get_thread_area(int TODO_PROTOTYPE) */
#define __NR64_lookup_dcookie         0xd4                           /* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
#define __NR64_epoll_create           0xd5                           /* fd_t epoll_create(syscall_ulong_t size) */
#define __NR64_epoll_ctl_old          0xd6                           /* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
#define __NR64_epoll_wait_old         0xd7                           /* errno_t epoll_wait_old(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
#define __NR64_remap_file_pages       0xd8                           /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
#define __NR64_getdents64             0xd9                           /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
#define __NR64_set_tid_address        0xda                           /* pid_t set_tid_address(pid_t *tidptr) */
#define __NR64_restart_syscall        0xdb                           /* errno_t restart_syscall(void) */
#define __NR64_semtimedop             0xdc                           /* errno_t semtimedop(int TODO_PROTOTYPE) */
#define __NR64_fadvise64              0xdd                           /* errno_t fadvise64(int TODO_PROTOTYPE) */
#define __NR64_timer_create           0xde                           /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
#define __NR64_timer_settime          0xdf                           /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspecx64 const *value, struct __itimerspecx64 *ovalue) */
#define __NR64_timer_gettime          0xe0                           /* errno_t timer_gettime(timer_t timerid, struct __itimerspecx64 *value) */
#define __NR64_timer_getoverrun       0xe1                           /* syscall_slong_t timer_getoverrun(timer_t timerid) */
#define __NR64_timer_delete           0xe2                           /* errno_t timer_delete(timer_t timerid) */
#define __NR64_clock_settime          0xe3                           /* errno_t clock_settime(clockid_t clock_id, struct __timespecx64 const *tp) */
#define __NR64_clock_gettime          0xe4                           /* errno_t clock_gettime(clockid_t clock_id, struct __timespecx64 *tp) */
#define __NR64_clock_getres           0xe5                           /* errno_t clock_getres(clockid_t clock_id, struct __timespecx64 *res) */
#define __NR64_clock_nanosleep        0xe6                           /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespecx64 const *requested_time, struct __timespecx64 *remaining) */
#define __NR64_exit_group             0xe7                           /* void exit_group(syscall_ulong_t exit_code) */
#define __NR64_epoll_wait             0xe8                           /* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
#define __NR64_epoll_ctl              0xe9                           /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
#define __NR64_tgkill                 0xea                           /* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
#define __NR64_utimes                 0xeb                           /* errno_t utimes(char const *filename, struct __timevalx64 const[2] times) */
#define __NR64_vserver                0xec                           /* errno_t vserver(int TODO_PROTOTYPE) */
#define __NR64_mbind                  0xed                           /* errno_t mbind(int TODO_PROTOTYPE) */
#define __NR64_set_mempolicy          0xee                           /* errno_t set_mempolicy(int TODO_PROTOTYPE) */
#define __NR64_get_mempolicy          0xef                           /* errno_t get_mempolicy(int TODO_PROTOTYPE) */
#define __NR64_mq_open                0xf0                           /* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
#define __NR64_mq_unlink              0xf1                           /* errno_t mq_unlink(char const *name) */
#define __NR64_mq_timedsend           0xf2                           /* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct __timespecx64 const *abs_timeout) */
#define __NR64_mq_timedreceive        0xf3                           /* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct __timespecx64 const *abs_timeout) */
#define __NR64_mq_notify              0xf4                           /* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
#define __NR64_mq_getsetattr          0xf5                           /* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
#define __NR64_kexec_load             0xf6                           /* errno_t kexec_load(int TODO_PROTOTYPE) */
/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
#define __NR64_waitid                 0xf7                           /* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo64_struct *infop, syscall_ulong_t options, struct __rusagex64 *ru) */
#define __NR64_add_key                0xf8                           /* errno_t add_key(int TODO_PROTOTYPE) */
#define __NR64_request_key            0xf9                           /* errno_t request_key(int TODO_PROTOTYPE) */
#define __NR64_keyctl                 0xfa                           /* errno_t keyctl(int TODO_PROTOTYPE) */
#define __NR64_ioprio_set             0xfb                           /* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
#define __NR64_ioprio_get             0xfc                           /* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
#define __NR64_inotify_init           0xfd                           /* errno_t inotify_init(int TODO_PROTOTYPE) */
#define __NR64_inotify_add_watch      0xfe                           /* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
#define __NR64_inotify_rm_watch       0xff                           /* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
#define __NR64_migrate_pages          0x100                          /* errno_t migrate_pages(int TODO_PROTOTYPE) */
#define __NR64_openat                 0x101                          /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
#define __NR64_mkdirat                0x102                          /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
#define __NR64_mknodat                0x103                          /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_fchownat               0x104                          /* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
#define __NR64_futimesat              0x105                          /* errno_t futimesat(fd_t dirfd, const char *filename, struct __timevalx64 const[2] times) */
#define __NR64_linux_fstatat          0x106                          /* errno_t linux_fstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG | AT_DOSPATH' */
#define __NR64_unlinkat               0x107                          /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define __NR64_renameat               0x108                          /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define __NR64_linkat                 0x109                          /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define __NR64_symlinkat              0x10a                          /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
#define __NR64_readlinkat             0x10b                          /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_fchmodat               0x10c                          /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS | AT_DOSPATH' */
#define __NR64_faccessat              0x10d                          /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
#define __NR64_pselect6               0x10e                          /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespecx64 const *timeout, void const *sigmask_sigset_and_len) */
#define __NR64_ppoll                  0x10f                          /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespecx64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* param flags: Set of `CLONE_*' */
#define __NR64_unshare                0x110                          /* errno_t unshare(syscall_ulong_t flags) */
#define __NR64_set_robust_list        0x111                          /* errno_t set_robust_list(int TODO_PROTOTYPE) */
#define __NR64_get_robust_list        0x112                          /* errno_t get_robust_list(int TODO_PROTOTYPE) */
#define __NR64_splice                 0x113                          /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
#define __NR64_tee                    0x114                          /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
#define __NR64_sync_file_range        0x115                          /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
#define __NR64_vmsplice               0x116                          /* ssize_t vmsplice(fd_t fdout, struct iovec64 const *iov, size_t count, syscall_ulong_t flags) */
#define __NR64_move_pages             0x117                          /* errno_t move_pages(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
#define __NR64_utimensat              0x118                          /* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespecx64 const[2] times, atflag_t flags) */
#define __NR64_epoll_pwait            0x119                          /* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
#define __NR64_signalfd               0x11a                          /* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* Return file descriptor for new interval timer source */
#define __NR64_timerfd_create         0x11b                          /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
#define __NR64_eventfd                0x11c                          /* fd_t eventfd(syscall_ulong_t initval) */
#define __NR64_fallocate              0x11d                          /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
#define __NR64_timerfd_settime        0x11e                          /* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspecx64 const *utmr, struct __itimerspecx64 *otmr) */
/* Return the next expiration time of UFD */
#define __NR64_timerfd_gettime        0x11f                          /* errno_t timerfd_gettime(fd_t ufd, struct __itimerspecx64 *otmr) */
#define __NR64_accept4                0x120                          /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
#define __NR64_signalfd4              0x121                          /* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
#define __NR64_eventfd2               0x122                          /* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
#define __NR64_epoll_create1          0x123                          /* fd_t epoll_create1(syscall_ulong_t flags) */
/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
#define __NR64_dup3                   0x124                          /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
#define __NR64_pipe2                  0x125                          /* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
#define __NR64_inotify_init1          0x126                          /* errno_t inotify_init1(int TODO_PROTOTYPE) */
#define __NR64_preadv                 0x127                          /* ssize_t preadv(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset) */
#define __NR64_pwritev                0x128                          /* ssize_t pwritev(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset) */
/* @param: signo: One of `SIG*' */
#define __NR64_rt_tgsigqueueinfo      0x129                          /* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo64_struct const *uinfo) */
#define __NR64_perf_event_open        0x12a                          /* errno_t perf_event_open(int TODO_PROTOTYPE) */
#define __NR64_recvmmsg               0x12b                          /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespecx64 *tmo) */
#define __NR64_fanotify_init          0x12c                          /* errno_t fanotify_init(int TODO_PROTOTYPE) */
#define __NR64_fanotify_mark          0x12d                          /* errno_t fanotify_mark(int TODO_PROTOTYPE) */
/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
#define __NR64_prlimit64              0x12e                          /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
#define __NR64_name_to_handle_at      0x12f                          /* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
#define __NR64_open_by_handle_at      0x130                          /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
#define __NR64_clock_adjtime          0x131                          /* errno_t clock_adjtime(int TODO_PROTOTYPE) */
#define __NR64_syncfs                 0x132                          /* errno_t syncfs(fd_t fd) */
#define __NR64_sendmmsg               0x133                          /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
#define __NR64_setns                  0x134                          /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
#define __NR64_getcpu                 0x135                          /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
#define __NR64_process_vm_readv       0x136                          /* ssize_t process_vm_readv(pid_t pid, struct iovec64 const *lvec, size_t liovcnt, struct iovec64 const *rvec, size_t riovcnt, syscall_ulong_t flags) */
#define __NR64_process_vm_writev      0x137                          /* ssize_t process_vm_writev(pid_t pid, struct iovec64 const *lvec, size_t liovcnt, struct iovec64 const *rvec, size_t riovcnt, syscall_ulong_t flags) */
#define __NR64_kcmp                   0x138                          /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
#define __NR64_finit_module           0x139                          /* errno_t finit_module(int TODO_PROTOTYPE) */
#define __NR64_sched_setattr          0x13a                          /* errno_t sched_setattr(int TODO_PROTOTYPE) */
#define __NR64_sched_getattr          0x13b                          /* errno_t sched_getattr(int TODO_PROTOTYPE) */
/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
#define __NR64_renameat2              0x13c                          /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
#define __NR64_seccomp                0x13d                          /* errno_t seccomp(int TODO_PROTOTYPE) */
#define __NR64_getrandom              0x13e                          /* errno_t getrandom(int TODO_PROTOTYPE) */
#define __NR64_memfd_create           0x13f                          /* errno_t memfd_create(int TODO_PROTOTYPE) */
#define __NR64_kexec_file_load        0x140                          /* errno_t kexec_file_load(int TODO_PROTOTYPE) */
#define __NR64_bpf                    0x141                          /* errno_t bpf(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_execveat               0x142                          /* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
#define __NR64_userfaultfd            0x143                          /* errno_t userfaultfd(int TODO_PROTOTYPE) */
#define __NR64_membarrier             0x144                          /* errno_t membarrier(int TODO_PROTOTYPE) */
#define __NR64_mlock2                 0x145                          /* errno_t mlock2(int TODO_PROTOTYPE) */
#define __NR64_readf                  __UINT64_C(0xffffffff80000000) /* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
#define __NR64_writef                 __UINT64_C(0xffffffff80000001) /* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */
#define __NR64_hop                    __UINT64_C(0xffffffff80000002) /* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
#define __NR64_hopf                   __UINT64_C(0xffffffff80000003) /* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define __NR64_kstat                  __UINT64_C(0xffffffff80000004) /* errno_t kstat(char const *filename, struct stat *statbuf) */
#define __NR64_kfstat                 __UINT64_C(0xffffffff80000005) /* errno_t kfstat(fd_t fd, struct stat *statbuf) */
#define __NR64_klstat                 __UINT64_C(0xffffffff80000006) /* errno_t klstat(char const *filename, struct stat *statbuf) */
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
#define __NR64_detach                 __UINT64_C(0xffffffff80000007) /* errno_t detach(pid_t pid) */
/* Returns a bitset of all of the currently mounted dos-drives */
#define __NR64_getdrives              __UINT64_C(0xffffffff80000008) /* syscall_slong_t getdrives(void) */
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR64_frealpath4             __UINT64_C(0xffffffff80000009) /* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR64_frealpathat            __UINT64_C(0xffffffff8000000a) /* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
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
#define __NR64_rpc_schedule           __UINT64_C(0xffffffff8000000b) /* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, __HYBRID_PTR64(void) *arguments) */
#define __NR64_ksysctl                __UINT64_C(0xffffffff8000000c) /* syscall_slong_t ksysctl(syscall_ulong_t command, void *arg) */
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
#define __NR64_openpty                __UINT64_C(0xffffffff8000000d) /* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
#define __NR64_set_exception_handler  __UINT64_C(0xffffffff8000000e) /* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
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
#define __NR64_get_exception_handler  __UINT64_C(0xffffffff8000000f) /* errno_t get_exception_handler(__ULONG64_TYPE__ *pmode, __except_handler64_t *phandler, __HYBRID_PTR64(void) *phandler_sp) */
#define __NR64_ioctlf                 __UINT64_C(0xffffffff80000010) /* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define __NR64_pread64f               __UINT64_C(0xffffffff80000011) /* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR64_pwrite64f              __UINT64_C(0xffffffff80000012) /* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define __NR64_readvf                 __UINT64_C(0xffffffff80000013) /* ssize_t readvf(fd_t fd, struct iovec64 const *iovec, size_t count, iomode_t mode) */
#define __NR64_writevf                __UINT64_C(0xffffffff80000014) /* ssize_t writevf(fd_t fd, struct iovec64 const *iovec, size_t count, iomode_t mode) */
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
#define __NR64_set_library_listdef    __UINT64_C(0xffffffff80000015) /* errno_t set_library_listdef(struct library_listdef64 const *listdef) */
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
#define __NR64_debugtrap              __UINT64_C(0xffffffff80000016) /* errno_t debugtrap(struct ucpustate64 const *state, struct debugtrap_reason64 const *reason) */
#define __NR64_rpc_service            __UINT64_C(0xffffffff80000018) /* syscall_slong_t rpc_service(void) */
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
#define __NR64_lfutex                 __UINT64_C(0xffffffff80000019) /* syscall_slong_t lfutex(uint64_t *uaddr, syscall_ulong_t futex_op, uint64_t val, struct __timespecx64 const *timeout, uint64_t val2) */
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
#define __NR64_lfutexexpr             __UINT64_C(0xffffffff8000001a) /* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexpr64 const *exprv, struct __timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
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
#define __NR64_lfutexlockexpr         __UINT64_C(0xffffffff8000001b) /* errno_t lfutexlockexpr(uint64_t *ulockaddr, void *base, size_t exprc, struct lfutexexpr64 const *exprv, struct __timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
#define __NR64_mktty                  __UINT64_C(0xffffffff8000001c) /* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
#define __NR64_raiseat                __UINT64_C(0xffffffff8000001d) /* errno_t raiseat(struct ucpustate64 const *state, struct __siginfo64_struct const *si) */
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
#define __NR64_coredump               __UINT64_C(0xffffffff8000001e) /* errno_t coredump(struct ucpustate64 const *curr_state, struct ucpustate64 const *orig_state, __HYBRID_PTR64(void) const *traceback_vector, size_t traceback_length, struct exception_data64 const *exception, syscall_ulong_t unwind_error) */
#define __NR64_kreaddir               __UINT64_C(0xffffffff8000004e) /* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fchdirat               __UINT64_C(0xffffffff80000050) /* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
#define __NR64_fsmode                 __UINT64_C(0xffffffff8000005f) /* uint64_t fsmode(uint64_t mode) */
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
#define __NR64_maplibrary             __UINT64_C(0xffffffff80000086) /* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf64_phdr *hdrv, size_t hdrc) */
#define __NR64_kreaddirf              __UINT64_C(0xffffffff800000d9) /* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fmkdirat               __UINT64_C(0xffffffff80000102) /* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fmknodat               __UINT64_C(0xffffffff80000103) /* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR64_kfstatat               __UINT64_C(0xffffffff80000106) /* errno_t kfstatat(fd_t dirfd, char const *filename, struct stat *statbuf, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_frenameat              __UINT64_C(0xffffffff80000108) /* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define __NR64_fsymlinkat             __UINT64_C(0xffffffff8000010a) /* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define __NR64_freadlinkat            __UINT64_C(0xffffffff8000010b) /* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
#define __NR64_preadvf                __UINT64_C(0xffffffff80000127) /* ssize_t preadvf(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
#define __NR64_pwritevf               __UINT64_C(0xffffffff80000128) /* ssize_t pwritevf(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */


/************************************************************************/
/* SYSCALL LIMITS                                                       */
/************************************************************************/
#define __NR64FEAT_SYSCALL_TABLE_COUNT 2
#define __NR64FEAT_SYSCALL_TABLE_FOREACH(callback) \
	callback(0)                                    \
	callback(1) 
#define __NR64_syscall0_min 0x0
#define __NR64_syscall0_max 0x145
#define __NR64_syscall0_cnt 0x146
#define __NR64_syscall1_min __UINT64_C(0xffffffff80000000)
#define __NR64_syscall1_max __UINT64_C(0xffffffff80000128)
#define __NR64_syscall1_cnt 0x129
#endif /* !__NR64_read */


/************************************************************************/
/* SYSCALL RESTART MODES                                                */
/************************************************************************/
#ifdef __WANT_SYSCALL_RESTART_MODES
#ifndef __NR64FEAT_DEFINED_SYSCALL_RESTART_MODES
#define __NR64FEAT_DEFINED_SYSCALL_RESTART_MODES 1
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
#define __NR64RM_read                   0
#define __NR64RM_write                  0
#define __NR64RM_open                   0
#define __NR64RM_close                  2
#define __NR64RM_linux_stat64           0
#define __NR64RM_linux_fstat64          0
#define __NR64RM_linux_lstat64          0
#define __NR64RM_poll                   1
#define __NR64RM_lseek64                0
#define __NR64RM_mmap                   0
#define __NR64RM_mprotect               2
#define __NR64RM_munmap                 2
#define __NR64RM_brk                    0
#define __NR64RM_rt_sigaction           0
#define __NR64RM_rt_sigprocmask         0
#define __NR64RM_rt_sigreturn           2
#define __NR64RM_ioctl                  0
#define __NR64RM_pread64                0
#define __NR64RM_pwrite64               0
#define __NR64RM_readv                  0
#define __NR64RM_writev                 0
#define __NR64RM_access                 0
#define __NR64RM_pipe                   0
#define __NR64RM_select                 1
#define __NR64RM_sched_yield            1
#define __NR64RM_mremap                 0
#define __NR64RM_msync                  0
#define __NR64RM_mincore                0
#define __NR64RM_madvise                0
#define __NR64RM_shmget                 0
#define __NR64RM_shmat                  0
#define __NR64RM_shmctl                 0
#define __NR64RM_dup                    0
#define __NR64RM_dup2                   0
#define __NR64RM_pause                  1
#define __NR64RM_nanosleep              1
#define __NR64RM_getitimer              0
#define __NR64RM_alarm                  0
#define __NR64RM_setitimer              0
#define __NR64RM_getpid                 2
#define __NR64RM_sendfile               1
#define __NR64RM_socket                 0
#define __NR64RM_connect                1
#define __NR64RM_accept                 1
#define __NR64RM_sendto                 1
#define __NR64RM_recvfrom               1
#define __NR64RM_sendmsg                1
#define __NR64RM_recvmsg                1
#define __NR64RM_shutdown               0
#define __NR64RM_bind                   0
#define __NR64RM_listen                 0
#define __NR64RM_getsockname            0
#define __NR64RM_getpeername            0
#define __NR64RM_socketpair             0
#define __NR64RM_setsockopt             1
#define __NR64RM_getsockopt             0
#define __NR64RM_clone                  0
#define __NR64RM_fork                   2
#define __NR64RM_vfork                  0
#define __NR64RM_execve                 0
#define __NR64RM_exit                   2
#define __NR64RM_wait4                  1
#define __NR64RM_kill                   0
#define __NR64RM_uname                  0
#define __NR64RM_semget                 0
#define __NR64RM_semop                  1
#define __NR64RM_semctl                 0
#define __NR64RM_shmdt                  0
#define __NR64RM_msgget                 0
#define __NR64RM_msgsnd                 1
#define __NR64RM_msgrcv                 1
#define __NR64RM_msgctl                 0
#define __NR64RM_fcntl                  0
#define __NR64RM_flock                  0
#define __NR64RM_fsync                  0
#define __NR64RM_fdatasync              0
#define __NR64RM_truncate               0
#define __NR64RM_ftruncate              0
#define __NR64RM_getdents               0
#define __NR64RM_getcwd                 0
#define __NR64RM_chdir                  0
#define __NR64RM_fchdir                 0
#define __NR64RM_rename                 0
#define __NR64RM_mkdir                  0
#define __NR64RM_rmdir                  0
#define __NR64RM_creat                  0
#define __NR64RM_link                   0
#define __NR64RM_unlink                 0
#define __NR64RM_symlink                0
#define __NR64RM_readlink               0
#define __NR64RM_chmod                  0
#define __NR64RM_fchmod                 0
#define __NR64RM_chown                  0
#define __NR64RM_fchown                 0
#define __NR64RM_lchown                 0
#define __NR64RM_umask                  2
#define __NR64RM_gettimeofday           0
#define __NR64RM_getrlimit              0
#define __NR64RM_getrusage              0
#define __NR64RM_sysinfo                0
#define __NR64RM_times                  0
#define __NR64RM_ptrace                 0
#define __NR64RM_getuid                 2
#define __NR64RM_syslog                 2
#define __NR64RM_getgid                 2
#define __NR64RM_setuid                 2
#define __NR64RM_setgid                 2
#define __NR64RM_geteuid                2
#define __NR64RM_getegid                2
#define __NR64RM_setpgid                2
#define __NR64RM_getppid                2
#define __NR64RM_getpgrp                2
#define __NR64RM_setsid                 2
#define __NR64RM_setreuid               2
#define __NR64RM_setregid               2
#define __NR64RM_getgroups              2
#define __NR64RM_setgroups              2
#define __NR64RM_setresuid              2
#define __NR64RM_getresuid              2
#define __NR64RM_setresgid              2
#define __NR64RM_getresgid              2
#define __NR64RM_getpgid                2
#define __NR64RM_setfsuid               2
#define __NR64RM_setfsgid               2
#define __NR64RM_getsid                 2
#define __NR64RM_capget                 0
#define __NR64RM_capset                 0
#define __NR64RM_rt_sigpending          0
#define __NR64RM_rt_sigtimedwait        1
#define __NR64RM_rt_sigqueueinfo        0
#define __NR64RM_rt_sigsuspend          0
#define __NR64RM_sigaltstack            0
#define __NR64RM_utime                  0
#define __NR64RM_mknod                  0
#define __NR64RM_uselib                 0
#define __NR64RM_personality            0
#define __NR64RM_ustat                  0
#define __NR64RM_statfs                 0
#define __NR64RM_fstatfs                0
#define __NR64RM_sysfs                  0
#define __NR64RM_getpriority            0
#define __NR64RM_setpriority            0
#define __NR64RM_sched_setparam         0
#define __NR64RM_sched_getparam         0
#define __NR64RM_sched_setscheduler     0
#define __NR64RM_sched_getscheduler     0
#define __NR64RM_sched_get_priority_max 0
#define __NR64RM_sched_get_priority_min 0
#define __NR64RM_sched_rr_get_interval  0
#define __NR64RM_mlock                  0
#define __NR64RM_munlock                0
#define __NR64RM_mlockall               0
#define __NR64RM_munlockall             0
#define __NR64RM_vhangup                0
#define __NR64RM_modify_ldt             0
#define __NR64RM_pivot_root             0
#define __NR64RM__sysctl                0
#define __NR64RM_prctl                  0
#define __NR64RM_arch_prctl             0
#define __NR64RM_adjtimex               0
#define __NR64RM_setrlimit              0
#define __NR64RM_chroot                 0
#define __NR64RM_sync                   0
#define __NR64RM_acct                   0
#define __NR64RM_settimeofday           0
#define __NR64RM_mount                  0
#define __NR64RM_umount2                2
#define __NR64RM_swapon                 0
#define __NR64RM_swapoff                0
#define __NR64RM_reboot                 0
#define __NR64RM_sethostname            0
#define __NR64RM_setdomainname          0
#define __NR64RM_iopl                   0
#define __NR64RM_ioperm                 0
#define __NR64RM_create_module          0
#define __NR64RM_init_module            0
#define __NR64RM_delete_module          0
#define __NR64RM_get_kernel_syms        0
#define __NR64RM_query_module           0
#define __NR64RM_quotactl               0
#define __NR64RM_nfsservctl             0
#define __NR64RM_getpmsg                0
#define __NR64RM_putpmsg                0
#define __NR64RM_afs_syscall            0
#define __NR64RM_tuxcall                0
#define __NR64RM_security               0
#define __NR64RM_gettid                 2
#define __NR64RM_readahead              0
#define __NR64RM_setxattr               0
#define __NR64RM_lsetxattr              0
#define __NR64RM_fsetxattr              0
#define __NR64RM_getxattr               0
#define __NR64RM_lgetxattr              0
#define __NR64RM_fgetxattr              0
#define __NR64RM_listxattr              0
#define __NR64RM_llistxattr             0
#define __NR64RM_flistxattr             0
#define __NR64RM_removexattr            0
#define __NR64RM_lremovexattr           0
#define __NR64RM_fremovexattr           0
#define __NR64RM_tkill                  0
#define __NR64RM_time                   0
#define __NR64RM_futex                  0
#define __NR64RM_sched_setaffinity      0
#define __NR64RM_sched_getaffinity      0
#define __NR64RM_set_thread_area        0
#define __NR64RM_io_setup               0
#define __NR64RM_io_destroy             0
#define __NR64RM_io_getevents           1
#define __NR64RM_io_submit              0
#define __NR64RM_io_cancel              0
#define __NR64RM_get_thread_area        0
#define __NR64RM_lookup_dcookie         0
#define __NR64RM_epoll_create           0
#define __NR64RM_epoll_ctl_old          0
#define __NR64RM_epoll_wait_old         1
#define __NR64RM_remap_file_pages       0
#define __NR64RM_getdents64             0
#define __NR64RM_set_tid_address        0
#define __NR64RM_restart_syscall        0
#define __NR64RM_semtimedop             1
#define __NR64RM_fadvise64              0
#define __NR64RM_timer_create           0
#define __NR64RM_timer_settime          0
#define __NR64RM_timer_gettime          0
#define __NR64RM_timer_getoverrun       0
#define __NR64RM_timer_delete           0
#define __NR64RM_clock_settime          0
#define __NR64RM_clock_gettime          0
#define __NR64RM_clock_getres           0
#define __NR64RM_clock_nanosleep        1
#define __NR64RM_exit_group             2
#define __NR64RM_epoll_wait             1
#define __NR64RM_epoll_ctl              0
#define __NR64RM_tgkill                 0
#define __NR64RM_utimes                 0
#define __NR64RM_vserver                0
#define __NR64RM_mbind                  0
#define __NR64RM_set_mempolicy          0
#define __NR64RM_get_mempolicy          0
#define __NR64RM_mq_open                0
#define __NR64RM_mq_unlink              0
#define __NR64RM_mq_timedsend           0
#define __NR64RM_mq_timedreceive        0
#define __NR64RM_mq_notify              0
#define __NR64RM_mq_getsetattr          0
#define __NR64RM_kexec_load             0
#define __NR64RM_waitid                 1
#define __NR64RM_add_key                0
#define __NR64RM_request_key            0
#define __NR64RM_keyctl                 0
#define __NR64RM_ioprio_set             0
#define __NR64RM_ioprio_get             0
#define __NR64RM_inotify_init           0
#define __NR64RM_inotify_add_watch      0
#define __NR64RM_inotify_rm_watch       0
#define __NR64RM_migrate_pages          0
#define __NR64RM_openat                 0
#define __NR64RM_mkdirat                0
#define __NR64RM_mknodat                0
#define __NR64RM_fchownat               0
#define __NR64RM_futimesat              0
#define __NR64RM_linux_fstatat          0
#define __NR64RM_unlinkat               0
#define __NR64RM_renameat               0
#define __NR64RM_linkat                 0
#define __NR64RM_symlinkat              0
#define __NR64RM_readlinkat             0
#define __NR64RM_fchmodat               0
#define __NR64RM_faccessat              0
#define __NR64RM_pselect6               1
#define __NR64RM_ppoll                  1
#define __NR64RM_unshare                0
#define __NR64RM_set_robust_list        0
#define __NR64RM_get_robust_list        0
#define __NR64RM_splice                 0
#define __NR64RM_tee                    0
#define __NR64RM_sync_file_range        0
#define __NR64RM_vmsplice               0
#define __NR64RM_move_pages             0
#define __NR64RM_utimensat              0
#define __NR64RM_epoll_pwait            1
#define __NR64RM_signalfd               0
#define __NR64RM_timerfd_create         0
#define __NR64RM_eventfd                0
#define __NR64RM_fallocate              0
#define __NR64RM_timerfd_settime        0
#define __NR64RM_timerfd_gettime        0
#define __NR64RM_accept4                1
#define __NR64RM_signalfd4              0
#define __NR64RM_eventfd2               0
#define __NR64RM_epoll_create1          0
#define __NR64RM_dup3                   0
#define __NR64RM_pipe2                  0
#define __NR64RM_inotify_init1          0
#define __NR64RM_preadv                 0
#define __NR64RM_pwritev                0
#define __NR64RM_rt_tgsigqueueinfo      0
#define __NR64RM_perf_event_open        0
#define __NR64RM_recvmmsg               1
#define __NR64RM_fanotify_init          0
#define __NR64RM_fanotify_mark          0
#define __NR64RM_prlimit64              0
#define __NR64RM_name_to_handle_at      0
#define __NR64RM_open_by_handle_at      0
#define __NR64RM_clock_adjtime          0
#define __NR64RM_syncfs                 0
#define __NR64RM_sendmmsg               1
#define __NR64RM_setns                  0
#define __NR64RM_getcpu                 0
#define __NR64RM_process_vm_readv       0
#define __NR64RM_process_vm_writev      0
#define __NR64RM_kcmp                   0
#define __NR64RM_finit_module           0
#define __NR64RM_sched_setattr          0
#define __NR64RM_sched_getattr          0
#define __NR64RM_renameat2              0
#define __NR64RM_seccomp                0
#define __NR64RM_getrandom              0
#define __NR64RM_memfd_create           0
#define __NR64RM_kexec_file_load        0
#define __NR64RM_bpf                    0
#define __NR64RM_execveat               0
#define __NR64RM_userfaultfd            0
#define __NR64RM_membarrier             0
#define __NR64RM_mlock2                 0
#define __NR64RM_readf                  0
#define __NR64RM_writef                 0
#define __NR64RM_hop                    0
#define __NR64RM_hopf                   0
#define __NR64RM_kstat                  0
#define __NR64RM_kfstat                 0
#define __NR64RM_klstat                 0
#define __NR64RM_detach                 2
#define __NR64RM_getdrives              2
#define __NR64RM_frealpath4             0
#define __NR64RM_frealpathat            0
#define __NR64RM_rpc_schedule           0
#define __NR64RM_ksysctl                0
#define __NR64RM_openpty                0
#define __NR64RM_set_exception_handler  2
#define __NR64RM_get_exception_handler  2
#define __NR64RM_ioctlf                 0
#define __NR64RM_pread64f               0
#define __NR64RM_pwrite64f              0
#define __NR64RM_readvf                 0
#define __NR64RM_writevf                0
#define __NR64RM_set_library_listdef    2
#define __NR64RM_debugtrap              0
#define __NR64RM_rpc_service            1
#define __NR64RM_lfutex                 1
#define __NR64RM_lfutexexpr             1
#define __NR64RM_lfutexlockexpr         1
#define __NR64RM_mktty                  0
#define __NR64RM_raiseat                2
#define __NR64RM_coredump               2
#define __NR64RM_kreaddir               0
#define __NR64RM_fchdirat               0
#define __NR64RM_fsmode                 2
#define __NR64RM_maplibrary             0
#define __NR64RM_kreaddirf              0
#define __NR64RM_fmkdirat               0
#define __NR64RM_fmknodat               0
#define __NR64RM_kfstatat               0
#define __NR64RM_frenameat              0
#define __NR64RM_fsymlinkat             0
#define __NR64RM_freadlinkat            0
#define __NR64RM_preadvf                0
#define __NR64RM_pwritevf               0
#endif /* !__NR64FEAT_DEFINED_SYSCALL_RESTART_MODES */
#endif /* __WANT_SYSCALL_RESTART_MODES */


/************************************************************************/
/* SYSCALL CANCELLATION POINTS                                          */
/************************************************************************/
#ifdef __WANT_SYSCALL_CANCELLATION_POINTS
#ifndef __NR64FEAT_DEFINED_SYSCALL_CANCELLATION_POINTS
#define __NR64FEAT_DEFINED_SYSCALL_CANCELLATION_POINTS 1
#define __NR64FEAT_HAVE_CANCELLATION_POINTS 1
#define __NR64CP_read                   1
#define __NR64CP_write                  1
#define __NR64CP_open                   1
#define __NR64CP_linux_stat64           1
#define __NR64CP_linux_fstat64          1
#define __NR64CP_linux_lstat64          1
#define __NR64CP_poll                   1
#define __NR64CP_lseek64                1
#define __NR64CP_ioctl                  1
#define __NR64CP_pread64                1
#define __NR64CP_pwrite64               1
#define __NR64CP_readv                  1
#define __NR64CP_writev                 1
#define __NR64CP_access                 1
#define __NR64CP_select                 1
#define __NR64CP_msync                  1
#define __NR64CP_pause                  1
#define __NR64CP_nanosleep              1
#define __NR64CP_sendfile               1
#define __NR64CP_connect                1
#define __NR64CP_accept                 1
#define __NR64CP_sendto                 1
#define __NR64CP_recvfrom               1
#define __NR64CP_sendmsg                1
#define __NR64CP_recvmsg                1
#define __NR64CP_execve                 1
#define __NR64CP_wait4                  1
#define __NR64CP_msgsnd                 1
#define __NR64CP_msgrcv                 1
#define __NR64CP_fcntl                  1
#define __NR64CP_flock                  1
#define __NR64CP_fsync                  1
#define __NR64CP_fdatasync              1
#define __NR64CP_getdents               1
#define __NR64CP_getcwd                 1
#define __NR64CP_chdir                  1
#define __NR64CP_fchdir                 1
#define __NR64CP_rename                 1
#define __NR64CP_mkdir                  1
#define __NR64CP_creat                  1
#define __NR64CP_link                   1
#define __NR64CP_unlink                 1
#define __NR64CP_symlink                1
#define __NR64CP_readlink               1
#define __NR64CP_chmod                  1
#define __NR64CP_fchmod                 1
#define __NR64CP_chown                  1
#define __NR64CP_fchown                 1
#define __NR64CP_lchown                 1
#define __NR64CP_sysinfo                1
#define __NR64CP_syslog                 1
#define __NR64CP_rt_sigtimedwait        1
#define __NR64CP_utime                  1
#define __NR64CP_mknod                  1
#define __NR64CP_sync                   1
#define __NR64CP_mount                  1
#define __NR64CP_umount2                1
#define __NR64CP_getpmsg                1
#define __NR64CP_putpmsg                1
#define __NR64CP_setxattr               1
#define __NR64CP_lsetxattr              1
#define __NR64CP_fsetxattr              1
#define __NR64CP_getxattr               1
#define __NR64CP_lgetxattr              1
#define __NR64CP_fgetxattr              1
#define __NR64CP_listxattr              1
#define __NR64CP_llistxattr             1
#define __NR64CP_flistxattr             1
#define __NR64CP_removexattr            1
#define __NR64CP_lremovexattr           1
#define __NR64CP_fremovexattr           1
#define __NR64CP_futex                  1
#define __NR64CP_epoll_wait_old         1
#define __NR64CP_getdents64             1
#define __NR64CP_clock_nanosleep        1
#define __NR64CP_epoll_wait             1
#define __NR64CP_utimes                 1
#define __NR64CP_mq_timedsend           1
#define __NR64CP_mq_timedreceive        1
#define __NR64CP_waitid                 1
#define __NR64CP_openat                 1
#define __NR64CP_mkdirat                1
#define __NR64CP_mknodat                1
#define __NR64CP_fchownat               1
#define __NR64CP_futimesat              1
#define __NR64CP_linux_fstatat          1
#define __NR64CP_unlinkat               1
#define __NR64CP_renameat               1
#define __NR64CP_linkat                 1
#define __NR64CP_symlinkat              1
#define __NR64CP_readlinkat             1
#define __NR64CP_fchmodat               1
#define __NR64CP_faccessat              1
#define __NR64CP_pselect6               1
#define __NR64CP_ppoll                  1
#define __NR64CP_splice                 1
#define __NR64CP_tee                    1
#define __NR64CP_sync_file_range        1
#define __NR64CP_vmsplice               1
#define __NR64CP_utimensat              1
#define __NR64CP_epoll_pwait            1
#define __NR64CP_accept4                1
#define __NR64CP_preadv                 1
#define __NR64CP_pwritev                1
#define __NR64CP_recvmmsg               1
#define __NR64CP_name_to_handle_at      1
#define __NR64CP_open_by_handle_at      1
#define __NR64CP_syncfs                 1
#define __NR64CP_sendmmsg               1
#define __NR64CP_renameat2              1
#define __NR64CP_execveat               1
#define __NR64CP_readf                  1
#define __NR64CP_writef                 1
#define __NR64CP_hop                    1
#define __NR64CP_hopf                   1
#define __NR64CP_kstat                  1
#define __NR64CP_kfstat                 1
#define __NR64CP_klstat                 1
#define __NR64CP_frealpath4             1
#define __NR64CP_frealpathat            1
#define __NR64CP_ksysctl                1
#define __NR64CP_ioctlf                 1
#define __NR64CP_pread64f               1
#define __NR64CP_pwrite64f              1
#define __NR64CP_readvf                 1
#define __NR64CP_writevf                1
#define __NR64CP_rpc_service            1
#define __NR64CP_lfutex                 1
#define __NR64CP_lfutexexpr             1
#define __NR64CP_lfutexlockexpr         1
#define __NR64CP_kreaddir               1
#define __NR64CP_fchdirat               1
#define __NR64CP_kreaddirf              1
#define __NR64CP_fmkdirat               1
#define __NR64CP_fmknodat               1
#define __NR64CP_kfstatat               1
#define __NR64CP_frenameat              1
#define __NR64CP_fsymlinkat             1
#define __NR64CP_freadlinkat            1
#define __NR64CP_preadvf                1
#define __NR64CP_pwritevf               1
#endif /* !__NR64FEAT_DEFINED_SYSCALL_CANCELLATION_POINTS */
#endif /* __WANT_SYSCALL_CANCELLATION_POINTS */


/************************************************************************/
/* SYSCALL REGISTER COUNT                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_REGISTER_COUNT
#ifndef __NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT 1
#define __NR64FEAT_SYSCALL_REGISTER_MAX_COUNT 6
#define __NR64FEAT_SYSCALL_REGISTER_BITS 64
#define __NR64RC_read                   3
#define __NR64RC_write                  3
#define __NR64RC_open                   3
#define __NR64RC_close                  1
#define __NR64RC_linux_stat64           2
#define __NR64RC_linux_fstat64          2
#define __NR64RC_linux_lstat64          2
#define __NR64RC_poll                   3
#define __NR64RC_lseek64                3
#define __NR64RC_mmap                   6
#define __NR64RC_mprotect               3
#define __NR64RC_munmap                 2
#define __NR64RC_brk                    1
#define __NR64RC_rt_sigaction           4
#define __NR64RC_rt_sigprocmask         4
#define __NR64RC_rt_sigreturn           4
#define __NR64RC_ioctl                  3
#define __NR64RC_pread64                4
#define __NR64RC_pwrite64               4
#define __NR64RC_readv                  3
#define __NR64RC_writev                 3
#define __NR64RC_access                 2
#define __NR64RC_pipe                   1
#define __NR64RC_select                 5
#define __NR64RC_sched_yield            0
#define __NR64RC_mremap                 5
#define __NR64RC_msync                  3
#define __NR64RC_mincore                3
#define __NR64RC_madvise                3
#define __NR64RC_shmget                 1
#define __NR64RC_shmat                  1
#define __NR64RC_shmctl                 1
#define __NR64RC_dup                    1
#define __NR64RC_dup2                   2
#define __NR64RC_pause                  0
#define __NR64RC_nanosleep              2
#define __NR64RC_getitimer              2
#define __NR64RC_alarm                  1
#define __NR64RC_setitimer              3
#define __NR64RC_getpid                 0
#define __NR64RC_sendfile               4
#define __NR64RC_socket                 3
#define __NR64RC_connect                3
#define __NR64RC_accept                 1
#define __NR64RC_sendto                 6
#define __NR64RC_recvfrom               6
#define __NR64RC_sendmsg                3
#define __NR64RC_recvmsg                3
#define __NR64RC_shutdown               2
#define __NR64RC_bind                   3
#define __NR64RC_listen                 2
#define __NR64RC_getsockname            3
#define __NR64RC_getpeername            3
#define __NR64RC_socketpair             4
#define __NR64RC_setsockopt             5
#define __NR64RC_getsockopt             5
#define __NR64RC_clone                  5
#define __NR64RC_fork                   0
#define __NR64RC_vfork                  0
#define __NR64RC_execve                 3
#define __NR64RC_exit                   1
#define __NR64RC_wait4                  4
#define __NR64RC_kill                   2
#define __NR64RC_uname                  1
#define __NR64RC_semget                 1
#define __NR64RC_semop                  1
#define __NR64RC_semctl                 1
#define __NR64RC_shmdt                  1
#define __NR64RC_msgget                 1
#define __NR64RC_msgsnd                 1
#define __NR64RC_msgrcv                 1
#define __NR64RC_msgctl                 1
#define __NR64RC_fcntl                  3
#define __NR64RC_flock                  2
#define __NR64RC_fsync                  1
#define __NR64RC_fdatasync              1
#define __NR64RC_truncate               2
#define __NR64RC_ftruncate              2
#define __NR64RC_getdents               3
#define __NR64RC_getcwd                 2
#define __NR64RC_chdir                  1
#define __NR64RC_fchdir                 1
#define __NR64RC_rename                 2
#define __NR64RC_mkdir                  2
#define __NR64RC_rmdir                  1
#define __NR64RC_creat                  2
#define __NR64RC_link                   2
#define __NR64RC_unlink                 1
#define __NR64RC_symlink                2
#define __NR64RC_readlink               3
#define __NR64RC_chmod                  2
#define __NR64RC_fchmod                 2
#define __NR64RC_chown                  3
#define __NR64RC_fchown                 3
#define __NR64RC_lchown                 3
#define __NR64RC_umask                  1
#define __NR64RC_gettimeofday           2
#define __NR64RC_getrlimit              2
#define __NR64RC_getrusage              2
#define __NR64RC_sysinfo                1
#define __NR64RC_times                  1
#define __NR64RC_ptrace                 4
#define __NR64RC_getuid                 0
#define __NR64RC_syslog                 3
#define __NR64RC_getgid                 0
#define __NR64RC_setuid                 1
#define __NR64RC_setgid                 1
#define __NR64RC_geteuid                0
#define __NR64RC_getegid                0
#define __NR64RC_setpgid                2
#define __NR64RC_getppid                0
#define __NR64RC_getpgrp                0
#define __NR64RC_setsid                 0
#define __NR64RC_setreuid               2
#define __NR64RC_setregid               2
#define __NR64RC_getgroups              2
#define __NR64RC_setgroups              2
#define __NR64RC_setresuid              3
#define __NR64RC_getresuid              3
#define __NR64RC_setresgid              3
#define __NR64RC_getresgid              3
#define __NR64RC_getpgid                1
#define __NR64RC_setfsuid               1
#define __NR64RC_setfsgid               1
#define __NR64RC_getsid                 1
#define __NR64RC_capget                 1
#define __NR64RC_capset                 1
#define __NR64RC_rt_sigpending          2
#define __NR64RC_rt_sigtimedwait        4
#define __NR64RC_rt_sigqueueinfo        3
#define __NR64RC_rt_sigsuspend          2
#define __NR64RC_sigaltstack            2
#define __NR64RC_utime                  2
#define __NR64RC_mknod                  3
#define __NR64RC_uselib                 1
#define __NR64RC_personality            1
#define __NR64RC_ustat                  2
#define __NR64RC_statfs                 2
#define __NR64RC_fstatfs                2
#define __NR64RC_sysfs                  1
#define __NR64RC_getpriority            2
#define __NR64RC_setpriority            3
#define __NR64RC_sched_setparam         2
#define __NR64RC_sched_getparam         2
#define __NR64RC_sched_setscheduler     3
#define __NR64RC_sched_getscheduler     1
#define __NR64RC_sched_get_priority_max 1
#define __NR64RC_sched_get_priority_min 1
#define __NR64RC_sched_rr_get_interval  2
#define __NR64RC_mlock                  2
#define __NR64RC_munlock                2
#define __NR64RC_mlockall               1
#define __NR64RC_munlockall             0
#define __NR64RC_vhangup                0
#define __NR64RC_modify_ldt             3
#define __NR64RC_pivot_root             1
#define __NR64RC__sysctl                1
#define __NR64RC_prctl                  1
#define __NR64RC_arch_prctl             1
#define __NR64RC_adjtimex               1
#define __NR64RC_setrlimit              2
#define __NR64RC_chroot                 1
#define __NR64RC_sync                   0
#define __NR64RC_acct                   1
#define __NR64RC_settimeofday           2
#define __NR64RC_mount                  5
#define __NR64RC_umount2                2
#define __NR64RC_swapon                 2
#define __NR64RC_swapoff                1
#define __NR64RC_reboot                 1
#define __NR64RC_sethostname            2
#define __NR64RC_setdomainname          2
#define __NR64RC_iopl                   1
#define __NR64RC_ioperm                 3
#define __NR64RC_create_module          1
#define __NR64RC_init_module            1
#define __NR64RC_delete_module          1
#define __NR64RC_get_kernel_syms        1
#define __NR64RC_query_module           1
#define __NR64RC_quotactl               1
#define __NR64RC_nfsservctl             1
#define __NR64RC_getpmsg                1
#define __NR64RC_putpmsg                1
#define __NR64RC_afs_syscall            1
#define __NR64RC_tuxcall                1
#define __NR64RC_security               1
#define __NR64RC_gettid                 0
#define __NR64RC_readahead              3
#define __NR64RC_setxattr               5
#define __NR64RC_lsetxattr              5
#define __NR64RC_fsetxattr              5
#define __NR64RC_getxattr               4
#define __NR64RC_lgetxattr              4
#define __NR64RC_fgetxattr              4
#define __NR64RC_listxattr              3
#define __NR64RC_llistxattr             3
#define __NR64RC_flistxattr             3
#define __NR64RC_removexattr            2
#define __NR64RC_lremovexattr           2
#define __NR64RC_fremovexattr           2
#define __NR64RC_tkill                  2
#define __NR64RC_time                   1
#define __NR64RC_futex                  6
#define __NR64RC_sched_setaffinity      3
#define __NR64RC_sched_getaffinity      3
#define __NR64RC_set_thread_area        1
#define __NR64RC_io_setup               1
#define __NR64RC_io_destroy             1
#define __NR64RC_io_getevents           1
#define __NR64RC_io_submit              1
#define __NR64RC_io_cancel              1
#define __NR64RC_get_thread_area        1
#define __NR64RC_lookup_dcookie         1
#define __NR64RC_epoll_create           1
#define __NR64RC_epoll_ctl_old          4
#define __NR64RC_epoll_wait_old         4
#define __NR64RC_remap_file_pages       5
#define __NR64RC_getdents64             3
#define __NR64RC_set_tid_address        1
#define __NR64RC_restart_syscall        0
#define __NR64RC_semtimedop             1
#define __NR64RC_fadvise64              1
#define __NR64RC_timer_create           3
#define __NR64RC_timer_settime          4
#define __NR64RC_timer_gettime          2
#define __NR64RC_timer_getoverrun       1
#define __NR64RC_timer_delete           1
#define __NR64RC_clock_settime          2
#define __NR64RC_clock_gettime          2
#define __NR64RC_clock_getres           2
#define __NR64RC_clock_nanosleep        4
#define __NR64RC_exit_group             1
#define __NR64RC_epoll_wait             4
#define __NR64RC_epoll_ctl              4
#define __NR64RC_tgkill                 3
#define __NR64RC_utimes                 2
#define __NR64RC_vserver                1
#define __NR64RC_mbind                  1
#define __NR64RC_set_mempolicy          1
#define __NR64RC_get_mempolicy          1
#define __NR64RC_mq_open                3
#define __NR64RC_mq_unlink              1
#define __NR64RC_mq_timedsend           5
#define __NR64RC_mq_timedreceive        5
#define __NR64RC_mq_notify              2
#define __NR64RC_mq_getsetattr          3
#define __NR64RC_kexec_load             1
#define __NR64RC_waitid                 5
#define __NR64RC_add_key                1
#define __NR64RC_request_key            1
#define __NR64RC_keyctl                 1
#define __NR64RC_ioprio_set             3
#define __NR64RC_ioprio_get             2
#define __NR64RC_inotify_init           1
#define __NR64RC_inotify_add_watch      1
#define __NR64RC_inotify_rm_watch       1
#define __NR64RC_migrate_pages          1
#define __NR64RC_openat                 4
#define __NR64RC_mkdirat                3
#define __NR64RC_mknodat                4
#define __NR64RC_fchownat               5
#define __NR64RC_futimesat              3
#define __NR64RC_linux_fstatat          4
#define __NR64RC_unlinkat               3
#define __NR64RC_renameat               4
#define __NR64RC_linkat                 5
#define __NR64RC_symlinkat              3
#define __NR64RC_readlinkat             4
#define __NR64RC_fchmodat               4
#define __NR64RC_faccessat              4
#define __NR64RC_pselect6               6
#define __NR64RC_ppoll                  5
#define __NR64RC_unshare                1
#define __NR64RC_set_robust_list        1
#define __NR64RC_get_robust_list        1
#define __NR64RC_splice                 6
#define __NR64RC_tee                    4
#define __NR64RC_sync_file_range        4
#define __NR64RC_vmsplice               4
#define __NR64RC_move_pages             1
#define __NR64RC_utimensat              4
#define __NR64RC_epoll_pwait            5
#define __NR64RC_signalfd               3
#define __NR64RC_timerfd_create         2
#define __NR64RC_eventfd                1
#define __NR64RC_fallocate              4
#define __NR64RC_timerfd_settime        4
#define __NR64RC_timerfd_gettime        2
#define __NR64RC_accept4                4
#define __NR64RC_signalfd4              4
#define __NR64RC_eventfd2               2
#define __NR64RC_epoll_create1          1
#define __NR64RC_dup3                   3
#define __NR64RC_pipe2                  2
#define __NR64RC_inotify_init1          1
#define __NR64RC_preadv                 4
#define __NR64RC_pwritev                4
#define __NR64RC_rt_tgsigqueueinfo      4
#define __NR64RC_perf_event_open        1
#define __NR64RC_recvmmsg               5
#define __NR64RC_fanotify_init          1
#define __NR64RC_fanotify_mark          1
#define __NR64RC_prlimit64              4
#define __NR64RC_name_to_handle_at      5
#define __NR64RC_open_by_handle_at      3
#define __NR64RC_clock_adjtime          1
#define __NR64RC_syncfs                 1
#define __NR64RC_sendmmsg               4
#define __NR64RC_setns                  2
#define __NR64RC_getcpu                 3
#define __NR64RC_process_vm_readv       6
#define __NR64RC_process_vm_writev      6
#define __NR64RC_kcmp                   5
#define __NR64RC_finit_module           1
#define __NR64RC_sched_setattr          1
#define __NR64RC_sched_getattr          1
#define __NR64RC_renameat2              5
#define __NR64RC_seccomp                1
#define __NR64RC_getrandom              1
#define __NR64RC_memfd_create           1
#define __NR64RC_kexec_file_load        1
#define __NR64RC_bpf                    1
#define __NR64RC_execveat               5
#define __NR64RC_userfaultfd            1
#define __NR64RC_membarrier             1
#define __NR64RC_mlock2                 1
#define __NR64RC_readf                  4
#define __NR64RC_writef                 4
#define __NR64RC_hop                    3
#define __NR64RC_hopf                   4
#define __NR64RC_kstat                  2
#define __NR64RC_kfstat                 2
#define __NR64RC_klstat                 2
#define __NR64RC_detach                 1
#define __NR64RC_getdrives              0
#define __NR64RC_frealpath4             4
#define __NR64RC_frealpathat            5
#define __NR64RC_rpc_schedule           4
#define __NR64RC_ksysctl                2
#define __NR64RC_openpty                5
#define __NR64RC_set_exception_handler  3
#define __NR64RC_get_exception_handler  3
#define __NR64RC_ioctlf                 4
#define __NR64RC_pread64f               5
#define __NR64RC_pwrite64f              5
#define __NR64RC_readvf                 4
#define __NR64RC_writevf                4
#define __NR64RC_set_library_listdef    1
#define __NR64RC_debugtrap              2
#define __NR64RC_rpc_service            0
#define __NR64RC_lfutex                 5
#define __NR64RC_lfutexexpr             5
#define __NR64RC_lfutexlockexpr         6
#define __NR64RC_mktty                  4
#define __NR64RC_raiseat                2
#define __NR64RC_coredump               6
#define __NR64RC_kreaddir               4
#define __NR64RC_fchdirat               3
#define __NR64RC_fsmode                 1
#define __NR64RC_maplibrary             5
#define __NR64RC_kreaddirf              5
#define __NR64RC_fmkdirat               4
#define __NR64RC_fmknodat               5
#define __NR64RC_kfstatat               4
#define __NR64RC_frenameat              5
#define __NR64RC_fsymlinkat             4
#define __NR64RC_freadlinkat            5
#define __NR64RC_preadvf                5
#define __NR64RC_pwritevf               5
#endif /* !__NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT */
#endif /* __WANT_SYSCALL_REGISTER_COUNT */


/************************************************************************/
/* SYSCALL DOUBLE WIDE RETURN VALUE                                     */
/************************************************************************/
#ifdef __WANT_SYSCALL_DOUBLE_WIDE_RETURN
#ifndef __NR64FEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN
#define __NR64FEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN 1
#endif /* !__NR64FEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN */
#endif /* __WANT_SYSCALL_DOUBLE_WIDE_RETURN */


