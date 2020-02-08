/* HASH CRC-32:0x8f362925 */
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

#ifndef _I386_KOS_BITS_SYSCALLS64_H
#define _I386_KOS_BITS_SYSCALLS64_H 1

#ifndef __NR_read
#include "../asm/syscalls64.h"
#endif /* !__NR_read */

#define SYS_read                   __NR_read                   /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
#define SYS_write                  __NR_write                  /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
#define SYS_open                   __NR_open                   /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `FD' */
#define SYS_close                  __NR_close                  /* errno_t close(fd_t fd) */
#define SYS_linux_stat             __NR_linux_stat             /* errno_t linux_stat(char const *filename, struct linux_statx64 *statbuf) */
#define SYS_linux_fstat            __NR_linux_fstat            /* errno_t linux_fstat(fd_t fd, struct linux_statx64 *statbuf) */
#define SYS_linux_lstat            __NR_linux_lstat            /* errno_t linux_lstat(char const *filename, struct linux_statx64 *statbuf) */
#define SYS_poll                   __NR_poll                   /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
#define SYS_lseek                  __NR_lseek                  /* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
#define SYS_mmap                   __NR_mmap                   /* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
#define SYS_mprotect               __NR_mprotect               /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
#define SYS_munmap                 __NR_munmap                 /* errno_t munmap(void *addr, size_t len) */
#define SYS_brk                    __NR_brk                    /* errno_t brk(void *addr) */
#define SYS_rt_sigaction           __NR_rt_sigaction           /* errno_t rt_sigaction(syscall_ulong_t signo, struct sigaction64 const *act, struct sigaction64 *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define SYS_rt_sigprocmask         __NR_rt_sigprocmask         /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
/* Restore the given CPU/FPU context descriptors, as well as signal mask
 * before resuming execution by either invoking another system call `sc_info',
 * which will then return to `restore_cpu', or by directly returning there.
 * Arguments:
 *  - %rbp: [1..1] struct ucpustate64 const *restore_cpu;
 *  - %rbx: [0..1] struct fpustate64 const *restore_fpu;
 *  - %r12: [0..1] sigset_t const *restore_sigmask;
 *  - %r13: [0..1] struct rpc_syscall_info64 const *sc_info;
 * This system call uses a custom calling convention because registers passed
 * must not get clobbered during execution of a normal C function. On i386
 * this doesn't require a custom calling convention since enough registers
 * exist that are preserved by a C function, but are still used by at least
 * one system call invocation method. However on x86_64, no such registers
 * exist, requiring the use of a custom protocol. */
#define SYS_rt_sigreturn           __NR_rt_sigreturn           /* void rt_sigreturn(void) */
#define SYS_ioctl                  __NR_ioctl                  /* syscall_slong_t ioctl(fd_t fd, syscall_ulong_t request, void *arg) */
#define SYS_pread64                __NR_pread64                /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define SYS_pwrite64               __NR_pwrite64               /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
#define SYS_readv                  __NR_readv                  /* ssize_t readv(fd_t fd, struct iovec64 const *iovec, size_t count) */
#define SYS_writev                 __NR_writev                 /* ssize_t writev(fd_t fd, struct iovec64 const *iovec, size_t count) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define SYS_access                 __NR_access                 /* errno_t access(char const *filename, syscall_ulong_t type) */
#define SYS_pipe                   __NR_pipe                   /* errno_t pipe(fd_t[2] pipedes) */
#define SYS_select                 __NR_select                 /* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timevalx64 *timeout) */
#define SYS_sched_yield            __NR_sched_yield            /* errno_t sched_yield(void) */
/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
#define SYS_mremap                 __NR_mremap                 /* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define SYS_msync                  __NR_msync                  /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
#define SYS_mincore                __NR_mincore                /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define SYS_madvise                __NR_madvise                /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
#define SYS_shmget                 __NR_shmget                 /* errno_t shmget(int TODO_PROTOTYPE) */
#define SYS_shmat                  __NR_shmat                  /* errno_t shmat(int TODO_PROTOTYPE) */
#define SYS_shmctl                 __NR_shmctl                 /* errno_t shmctl(int TODO_PROTOTYPE) */
#define SYS_dup                    __NR_dup                    /* fd_t dup(fd_t fd) */
#define SYS_dup2                   __NR_dup2                   /* fd_t dup2(fd_t oldfd, fd_t newfd) */
#define SYS_pause                  __NR_pause                  /* errno_t pause(void) */
#define SYS_nanosleep              __NR_nanosleep              /* errno_t nanosleep(struct __timespecx64 const *req, struct __timespecx64 *rem) */
#define SYS_getitimer              __NR_getitimer              /* errno_t getitimer(syscall_ulong_t which, struct __itimervalx64 *curr_value) */
#define SYS_alarm                  __NR_alarm                  /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
#define SYS_setitimer              __NR_setitimer              /* errno_t setitimer(syscall_ulong_t which, struct __itimervalx64 const *newval, struct __itimervalx64 *oldval) */
#define SYS_getpid                 __NR_getpid                 /* pid_t getpid(void) */
#define SYS_sendfile               __NR_sendfile               /* ssize_t sendfile(fd_t out_fd, fd_t in_fd, syscall_ulong_t *pin_offset, size_t num_bytes) */
#define SYS_socket                 __NR_socket                 /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
#define SYS_connect                __NR_connect                /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define SYS_accept                 __NR_accept                 /* errno_t accept(int TODO_PROTOTYPE) */
/* param flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB' */
#define SYS_sendto                 __NR_sendto                 /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr const *addr, socklen_t addr_len) */
#define SYS_recvfrom               __NR_recvfrom               /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t flags, struct sockaddr *addr, socklen_t *addr_len) */
#define SYS_sendmsg                __NR_sendmsg                /* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t flags) */
#define SYS_recvmsg                __NR_recvmsg                /* ssize_t recvmsg(fd_t sockfd, struct msghdr64 *message, syscall_ulong_t flags) */
/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
#define SYS_shutdown               __NR_shutdown               /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
#define SYS_bind                   __NR_bind                   /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
#define SYS_listen                 __NR_listen                 /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
#define SYS_getsockname            __NR_getsockname            /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
#define SYS_getpeername            __NR_getpeername            /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
#define SYS_socketpair             __NR_socketpair             /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define SYS_setsockopt             __NR_setsockopt             /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
#define SYS_getsockopt             __NR_getsockopt             /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
#define SYS_clone                  __NR_clone                  /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
#define SYS_fork                   __NR_fork                   /* pid_t fork(void) */
#define SYS_vfork                  __NR_vfork                  /* pid_t vfork(void) */
#define SYS_execve                 __NR_execve                 /* errno_t execve(char const *path, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp) */
#define SYS_exit                   __NR_exit                   /* void exit(syscall_ulong_t status) */
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define SYS_wait4                  __NR_wait4                  /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct __rusagex64 *usage) */
/* @param: signo: One of `SIG*' */
#define SYS_kill                   __NR_kill                   /* errno_t kill(pid_t pid, syscall_ulong_t signo) */
#define SYS_uname                  __NR_uname                  /* errno_t uname(struct utsname *name) */
#define SYS_semget                 __NR_semget                 /* errno_t semget(int TODO_PROTOTYPE) */
#define SYS_semop                  __NR_semop                  /* errno_t semop(int TODO_PROTOTYPE) */
#define SYS_semctl                 __NR_semctl                 /* errno_t semctl(int TODO_PROTOTYPE) */
#define SYS_shmdt                  __NR_shmdt                  /* errno_t shmdt(int TODO_PROTOTYPE) */
#define SYS_msgget                 __NR_msgget                 /* errno_t msgget(int TODO_PROTOTYPE) */
#define SYS_msgsnd                 __NR_msgsnd                 /* errno_t msgsnd(int TODO_PROTOTYPE) */
#define SYS_msgrcv                 __NR_msgrcv                 /* errno_t msgrcv(int TODO_PROTOTYPE) */
#define SYS_msgctl                 __NR_msgctl                 /* errno_t msgctl(int TODO_PROTOTYPE) */
#define SYS_fcntl                  __NR_fcntl                  /* syscall_slong_t fcntl(fd_t fd, syscall_ulong_t cmd, void *arg) */
#define SYS_flock                  __NR_flock                  /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
#define SYS_fsync                  __NR_fsync                  /* errno_t fsync(fd_t fd) */
#define SYS_fdatasync              __NR_fdatasync              /* errno_t fdatasync(fd_t fd) */
#define SYS_truncate               __NR_truncate               /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define SYS_ftruncate              __NR_ftruncate              /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
#define SYS_getdents               __NR_getdents               /* ssize_t getdents(fd_t fd, struct linux_dirent *dirp, size_t count) */
#define SYS_getcwd                 __NR_getcwd                 /* ssize_t getcwd(char *buf, size_t size) */
#define SYS_chdir                  __NR_chdir                  /* errno_t chdir(char const *path) */
#define SYS_fchdir                 __NR_fchdir                 /* errno_t fchdir(fd_t fd) */
#define SYS_rename                 __NR_rename                 /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define SYS_mkdir                  __NR_mkdir                  /* errno_t mkdir(char const *pathname, mode_t mode) */
#define SYS_rmdir                  __NR_rmdir                  /* errno_t rmdir(char const *path) */
#define SYS_creat                  __NR_creat                  /* fd_t creat(char const *filename, mode_t mode) */
#define SYS_link                   __NR_link                   /* errno_t link(char const *existing_file, char const *link_file) */
#define SYS_unlink                 __NR_unlink                 /* errno_t unlink(char const *filename) */
#define SYS_symlink                __NR_symlink                /* errno_t symlink(char const *link_text, char const *target_path) */
#define SYS_readlink               __NR_readlink               /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
#define SYS_chmod                  __NR_chmod                  /* errno_t chmod(char const *filename, mode_t mode) */
#define SYS_fchmod                 __NR_fchmod                 /* errno_t fchmod(fd_t fd, mode_t mode) */
#define SYS_chown                  __NR_chown                  /* errno_t chown(char const *filename, uid_t owner, gid_t group) */
#define SYS_fchown                 __NR_fchown                 /* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
#define SYS_lchown                 __NR_lchown                 /* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
#define SYS_umask                  __NR_umask                  /* mode_t umask(mode_t mode) */
#define SYS_gettimeofday           __NR_gettimeofday           /* errno_t gettimeofday(struct __timevalx64 *tv, struct timezone *tz) */
#define SYS_getrlimit              __NR_getrlimit              /* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
#define SYS_getrusage              __NR_getrusage              /* errno_t getrusage(syscall_slong_t who, struct __rusagex64 *tv) */
#define SYS_sysinfo                __NR_sysinfo                /* errno_t sysinfo(struct sysinfo *info) */
#define SYS_times                  __NR_times                  /* clock_t times(struct tms *buf) */
#define SYS_ptrace                 __NR_ptrace                 /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
#define SYS_getuid                 __NR_getuid                 /* uid_t getuid(void) */
#define SYS_syslog                 __NR_syslog                 /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
#define SYS_getgid                 __NR_getgid                 /* gid_t getgid(void) */
#define SYS_setuid                 __NR_setuid                 /* errno_t setuid(uid_t uid) */
#define SYS_setgid                 __NR_setgid                 /* errno_t setgid(gid_t gid) */
#define SYS_geteuid                __NR_geteuid                /* uid_t geteuid(void) */
#define SYS_getegid                __NR_getegid                /* gid_t getegid(void) */
#define SYS_setpgid                __NR_setpgid                /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define SYS_getppid                __NR_getppid                /* pid_t getppid(void) */
#define SYS_getpgrp                __NR_getpgrp                /* pid_t getpgrp(void) */
#define SYS_setsid                 __NR_setsid                 /* pid_t setsid(void) */
#define SYS_setreuid               __NR_setreuid               /* errno_t setreuid(uid_t ruid, uid_t euid) */
#define SYS_setregid               __NR_setregid               /* errno_t setregid(gid_t rgid, gid_t egid) */
#define SYS_getgroups              __NR_getgroups              /* errno_t getgroups(size_t size, gid_t[] list) */
#define SYS_setgroups              __NR_setgroups              /* errno_t setgroups(size_t count, gid_t const *groups) */
#define SYS_setresuid              __NR_setresuid              /* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
#define SYS_getresuid              __NR_getresuid              /* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
#define SYS_setresgid              __NR_setresgid              /* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
#define SYS_getresgid              __NR_getresgid              /* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
#define SYS_getpgid                __NR_getpgid                /* pid_t getpgid(pid_t pid) */
#define SYS_setfsuid               __NR_setfsuid               /* errno_t setfsuid(uid_t uid) */
#define SYS_setfsgid               __NR_setfsgid               /* errno_t setfsgid(gid_t gid) */
#define SYS_getsid                 __NR_getsid                 /* pid_t getsid(pid_t pid) */
#define SYS_capget                 __NR_capget                 /* errno_t capget(int TODO_PROTOTYPE) */
#define SYS_capset                 __NR_capset                 /* errno_t capset(int TODO_PROTOTYPE) */
#define SYS_rt_sigpending          __NR_rt_sigpending          /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define SYS_rt_sigtimedwait        __NR_rt_sigtimedwait        /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo64_struct *info, struct __timespecx64 const *timeout, size_t sigsetsize) */
/* @param: signo: One of `SIG*' */
#define SYS_rt_sigqueueinfo        __NR_rt_sigqueueinfo        /* errno_t rt_sigqueueinfo(pid_t tgid, syscall_ulong_t signo, struct __siginfo64_struct const *uinfo) */
#define SYS_rt_sigsuspend          __NR_rt_sigsuspend          /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define SYS_sigaltstack            __NR_sigaltstack            /* errno_t sigaltstack(struct sigaltstack64 const *ss, struct sigaltstack64 *oss) */
#define SYS_utime                  __NR_utime                  /* errno_t utime(char const *filename, struct utimbuf const *times) */
#define SYS_mknod                  __NR_mknod                  /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define SYS_uselib                 __NR_uselib                 /* errno_t uselib(char const *library) */
#define SYS_personality            __NR_personality            /* errno_t personality(int TODO_PROTOTYPE) */
#define SYS_ustat                  __NR_ustat                  /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
#define SYS_statfs                 __NR_statfs                 /* errno_t statfs(char const *file, struct __statfsx64 *buf) */
#define SYS_fstatfs                __NR_fstatfs                /* errno_t fstatfs(fd_t file, struct __statfsx64 *buf) */
#define SYS_sysfs                  __NR_sysfs                  /* errno_t sysfs(int TODO_PROTOTYPE) */
#define SYS_getpriority            __NR_getpriority            /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
#define SYS_setpriority            __NR_setpriority            /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
#define SYS_sched_setparam         __NR_sched_setparam         /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
#define SYS_sched_getparam         __NR_sched_getparam         /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
#define SYS_sched_setscheduler     __NR_sched_setscheduler     /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define SYS_sched_getscheduler     __NR_sched_getscheduler     /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define SYS_sched_get_priority_max __NR_sched_get_priority_max /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define SYS_sched_get_priority_min __NR_sched_get_priority_min /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define SYS_sched_rr_get_interval  __NR_sched_rr_get_interval  /* errno_t sched_rr_get_interval(pid_t pid, struct __timespecx64 *tms) */
#define SYS_mlock                  __NR_mlock                  /* errno_t mlock(void const *addr, size_t len) */
#define SYS_munlock                __NR_munlock                /* errno_t munlock(void const *addr, size_t len) */
#define SYS_mlockall               __NR_mlockall               /* errno_t mlockall(syscall_ulong_t flags) */
#define SYS_munlockall             __NR_munlockall             /* errno_t munlockall(void) */
#define SYS_vhangup                __NR_vhangup                /* errno_t vhangup(void) */
#define SYS_modify_ldt             __NR_modify_ldt             /* syscall_slong_t modify_ldt(syscall_ulong_t func, void *ptr, syscall_ulong_t bytecount) */
#define SYS_pivot_root             __NR_pivot_root             /* errno_t pivot_root(int TODO_PROTOTYPE) */
#define SYS__sysctl                __NR__sysctl                /* errno_t _sysctl(int TODO_PROTOTYPE) */
#define SYS_prctl                  __NR_prctl                  /* errno_t prctl(int TODO_PROTOTYPE) */
#define SYS_arch_prctl             __NR_arch_prctl             /* errno_t arch_prctl(int TODO_PROTOTYPE) */
#define SYS_adjtimex               __NR_adjtimex               /* errno_t adjtimex(int TODO_PROTOTYPE) */
#define SYS_setrlimit              __NR_setrlimit              /* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
#define SYS_chroot                 __NR_chroot                 /* errno_t chroot(char const *path) */
#define SYS_sync                   __NR_sync                   /* errno_t sync(void) */
#define SYS_acct                   __NR_acct                   /* errno_t acct(char const *filename) */
#define SYS_settimeofday           __NR_settimeofday           /* errno_t settimeofday(struct __timevalx64 const *tv, struct timezone const *tz) */
#define SYS_mount                  __NR_mount                  /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t rwflag, void const *data) */
#define SYS_umount2                __NR_umount2                /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define SYS_swapon                 __NR_swapon                 /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
#define SYS_swapoff                __NR_swapoff                /* errno_t swapoff(char const *pathname) */
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
#define SYS_reboot                 __NR_reboot                 /* errno_t reboot(syscall_ulong_t how) */
#define SYS_sethostname            __NR_sethostname            /* errno_t sethostname(char const *name, size_t len) */
#define SYS_setdomainname          __NR_setdomainname          /* errno_t setdomainname(char const *name, size_t len) */
#define SYS_iopl                   __NR_iopl                   /* errno_t iopl(syscall_ulong_t level) */
#define SYS_ioperm                 __NR_ioperm                 /* errno_t ioperm(syscall_ulong_t from, syscall_ulong_t num, syscall_ulong_t turn_on) */
#define SYS_create_module          __NR_create_module          /* errno_t create_module(int TODO_PROTOTYPE) */
#define SYS_init_module            __NR_init_module            /* errno_t init_module(int TODO_PROTOTYPE) */
#define SYS_delete_module          __NR_delete_module          /* errno_t delete_module(int TODO_PROTOTYPE) */
#define SYS_get_kernel_syms        __NR_get_kernel_syms        /* errno_t get_kernel_syms(int TODO_PROTOTYPE) */
#define SYS_query_module           __NR_query_module           /* errno_t query_module(int TODO_PROTOTYPE) */
#define SYS_quotactl               __NR_quotactl               /* errno_t quotactl(int TODO_PROTOTYPE) */
#define SYS_nfsservctl             __NR_nfsservctl             /* errno_t nfsservctl(int TODO_PROTOTYPE) */
#define SYS_getpmsg                __NR_getpmsg                /* errno_t getpmsg(int TODO_PROTOTYPE) */
#define SYS_putpmsg                __NR_putpmsg                /* errno_t putpmsg(int TODO_PROTOTYPE) */
#define SYS_afs_syscall            __NR_afs_syscall            /* errno_t afs_syscall(int TODO_PROTOTYPE) */
#define SYS_tuxcall                __NR_tuxcall                /* errno_t tuxcall(int TODO_PROTOTYPE) */
#define SYS_security               __NR_security               /* errno_t security(int TODO_PROTOTYPE) */
#define SYS_gettid                 __NR_gettid                 /* pid_t gettid(void) */
#define SYS_readahead              __NR_readahead              /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
#define SYS_setxattr               __NR_setxattr               /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define SYS_lsetxattr              __NR_lsetxattr              /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define SYS_fsetxattr              __NR_fsetxattr              /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define SYS_getxattr               __NR_getxattr               /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define SYS_lgetxattr              __NR_lgetxattr              /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define SYS_fgetxattr              __NR_fgetxattr              /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define SYS_listxattr              __NR_listxattr              /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define SYS_llistxattr             __NR_llistxattr             /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define SYS_flistxattr             __NR_flistxattr             /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define SYS_removexattr            __NR_removexattr            /* errno_t removexattr(char const *path, char const *name) */
#define SYS_lremovexattr           __NR_lremovexattr           /* errno_t lremovexattr(char const *path, char const *name) */
#define SYS_fremovexattr           __NR_fremovexattr           /* errno_t fremovexattr(int fd, char const *name) */
#define SYS_tkill                  __NR_tkill                  /* errno_t tkill(pid_t tid, syscall_ulong_t signo) */
#define SYS_time                   __NR_time                   /* time32_t time(time32_t *timer) */
#define SYS_futex                  __NR_futex                  /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct __timespecx64 const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define SYS_sched_setaffinity      __NR_sched_setaffinity      /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define SYS_sched_getaffinity      __NR_sched_getaffinity      /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define SYS_set_thread_area        __NR_set_thread_area        /* errno_t set_thread_area(int TODO_PROTOTYPE) */
#define SYS_io_setup               __NR_io_setup               /* errno_t io_setup(int TODO_PROTOTYPE) */
#define SYS_io_destroy             __NR_io_destroy             /* errno_t io_destroy(int TODO_PROTOTYPE) */
#define SYS_io_getevents           __NR_io_getevents           /* errno_t io_getevents(int TODO_PROTOTYPE) */
#define SYS_io_submit              __NR_io_submit              /* errno_t io_submit(int TODO_PROTOTYPE) */
#define SYS_io_cancel              __NR_io_cancel              /* errno_t io_cancel(int TODO_PROTOTYPE) */
#define SYS_get_thread_area        __NR_get_thread_area        /* errno_t get_thread_area(int TODO_PROTOTYPE) */
#define SYS_lookup_dcookie         __NR_lookup_dcookie         /* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
#define SYS_epoll_create           __NR_epoll_create           /* fd_t epoll_create(syscall_ulong_t size) */
#define SYS_epoll_ctl_old          __NR_epoll_ctl_old          /* errno_t epoll_ctl_old(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
#define SYS_epoll_wait_old         __NR_epoll_wait_old         /* errno_t epoll_wait_old(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
#define SYS_remap_file_pages       __NR_remap_file_pages       /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
#define SYS_getdents64             __NR_getdents64             /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *dirp, size_t count) */
#define SYS_set_tid_address        __NR_set_tid_address        /* pid_t set_tid_address(pid_t *tidptr) */
#define SYS_restart_syscall        __NR_restart_syscall        /* errno_t restart_syscall(void) */
#define SYS_semtimedop             __NR_semtimedop             /* errno_t semtimedop(int TODO_PROTOTYPE) */
#define SYS_fadvise64              __NR_fadvise64              /* errno_t fadvise64(int TODO_PROTOTYPE) */
#define SYS_timer_create           __NR_timer_create           /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
#define SYS_timer_settime          __NR_timer_settime          /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct __itimerspecx64 const *value, struct __itimerspecx64 *ovalue) */
#define SYS_timer_gettime          __NR_timer_gettime          /* errno_t timer_gettime(timer_t timerid, struct __itimerspecx64 *value) */
#define SYS_timer_getoverrun       __NR_timer_getoverrun       /* syscall_slong_t timer_getoverrun(timer_t timerid) */
#define SYS_timer_delete           __NR_timer_delete           /* errno_t timer_delete(timer_t timerid) */
#define SYS_clock_settime          __NR_clock_settime          /* errno_t clock_settime(clockid_t clock_id, struct __timespecx64 const *tp) */
#define SYS_clock_gettime          __NR_clock_gettime          /* errno_t clock_gettime(clockid_t clock_id, struct __timespecx64 *tp) */
#define SYS_clock_getres           __NR_clock_getres           /* errno_t clock_getres(clockid_t clock_id, struct __timespecx64 *res) */
#define SYS_clock_nanosleep        __NR_clock_nanosleep        /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct __timespecx64 const *requested_time, struct __timespecx64 *remaining) */
#define SYS_exit_group             __NR_exit_group             /* void exit_group(syscall_ulong_t exit_code) */
#define SYS_epoll_wait             __NR_epoll_wait             /* errno_t epoll_wait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout) */
#define SYS_epoll_ctl              __NR_epoll_ctl              /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *event) */
#define SYS_tgkill                 __NR_tgkill                 /* errno_t tgkill(pid_t tgid, pid_t tid, syscall_ulong_t signo) */
#define SYS_utimes                 __NR_utimes                 /* errno_t utimes(char const *filename, struct __timevalx64 const[2] times) */
#define SYS_vserver                __NR_vserver                /* errno_t vserver(int TODO_PROTOTYPE) */
#define SYS_mbind                  __NR_mbind                  /* errno_t mbind(int TODO_PROTOTYPE) */
#define SYS_set_mempolicy          __NR_set_mempolicy          /* errno_t set_mempolicy(int TODO_PROTOTYPE) */
#define SYS_get_mempolicy          __NR_get_mempolicy          /* errno_t get_mempolicy(int TODO_PROTOTYPE) */
#define SYS_mq_open                __NR_mq_open                /* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
#define SYS_mq_unlink              __NR_mq_unlink              /* errno_t mq_unlink(char const *name) */
#define SYS_mq_timedsend           __NR_mq_timedsend           /* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct __timespecx64 const *abs_timeout) */
#define SYS_mq_timedreceive        __NR_mq_timedreceive        /* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct __timespecx64 const *abs_timeout) */
#define SYS_mq_notify              __NR_mq_notify              /* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
#define SYS_mq_getsetattr          __NR_mq_getsetattr          /* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
#define SYS_kexec_load             __NR_kexec_load             /* errno_t kexec_load(int TODO_PROTOTYPE) */
/* @param: options: At least one of `WEXITED | WSTOPPED | WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
#define SYS_waitid                 __NR_waitid                 /* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo64_struct *infop, syscall_ulong_t options, struct __rusagex64 *ru) */
#define SYS_add_key                __NR_add_key                /* errno_t add_key(int TODO_PROTOTYPE) */
#define SYS_request_key            __NR_request_key            /* errno_t request_key(int TODO_PROTOTYPE) */
#define SYS_keyctl                 __NR_keyctl                 /* errno_t keyctl(int TODO_PROTOTYPE) */
#define SYS_ioprio_set             __NR_ioprio_set             /* errno_t ioprio_set(syscall_ulong_t which, syscall_ulong_t who, syscall_ulong_t ioprio) */
#define SYS_ioprio_get             __NR_ioprio_get             /* errno_t ioprio_get(syscall_ulong_t which, syscall_ulong_t who) */
#define SYS_inotify_init           __NR_inotify_init           /* errno_t inotify_init(int TODO_PROTOTYPE) */
#define SYS_inotify_add_watch      __NR_inotify_add_watch      /* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
#define SYS_inotify_rm_watch       __NR_inotify_rm_watch       /* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
#define SYS_migrate_pages          __NR_migrate_pages          /* errno_t migrate_pages(int TODO_PROTOTYPE) */
#define SYS_openat                 __NR_openat                 /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
#define SYS_mkdirat                __NR_mkdirat                /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
#define SYS_mknodat                __NR_mknodat                /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_fchownat               __NR_fchownat               /* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
#define SYS_futimesat              __NR_futimesat              /* errno_t futimesat(fd_t dirfd, const char *filename, struct __timevalx64 const[2] times) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_linux_fstatat          __NR_linux_fstatat          /* errno_t linux_fstatat(fd_t dirfd, char const *filename, struct linux_statx64 *statbuf, atflag_t flags) */
/* @param: flags: Set of `0 | AT_REMOVEDIR|AT_REMOVEREG | AT_DOSPATH' */
#define SYS_unlinkat               __NR_unlinkat               /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define SYS_renameat               __NR_renameat               /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define SYS_linkat                 __NR_linkat                 /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define SYS_symlinkat              __NR_symlinkat              /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
#define SYS_readlinkat             __NR_readlinkat             /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_fchmodat               __NR_fchmodat               /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW|AT_EACCESS | AT_DOSPATH' */
#define SYS_faccessat              __NR_faccessat              /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type, atflag_t flags) */
#define SYS_pselect6               __NR_pselect6               /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct __timespecx64 const *timeout, void const *sigmask_sigset_and_len) */
#define SYS_ppoll                  __NR_ppoll                  /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct __timespecx64 const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* param flags: Set of `CLONE_*' */
#define SYS_unshare                __NR_unshare                /* errno_t unshare(syscall_ulong_t flags) */
#define SYS_set_robust_list        __NR_set_robust_list        /* errno_t set_robust_list(int TODO_PROTOTYPE) */
#define SYS_get_robust_list        __NR_get_robust_list        /* errno_t get_robust_list(int TODO_PROTOTYPE) */
#define SYS_splice                 __NR_splice                 /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
#define SYS_tee                    __NR_tee                    /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
#define SYS_sync_file_range        __NR_sync_file_range        /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
#define SYS_vmsplice               __NR_vmsplice               /* ssize_t vmsplice(fd_t fdout, struct iovec64 const *iov, size_t count, syscall_ulong_t flags) */
#define SYS_move_pages             __NR_move_pages             /* errno_t move_pages(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH' */
#define SYS_utimensat              __NR_utimensat              /* errno_t utimensat(fd_t dirfd, char const *filename, struct __timespecx64 const[2] times, atflag_t flags) */
#define SYS_epoll_pwait            __NR_epoll_pwait            /* errno_t epoll_pwait(fd_t epfd, struct epoll_event *events, syscall_ulong_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss) */
#define SYS_signalfd               __NR_signalfd               /* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* Return file descriptor for new interval timer source */
#define SYS_timerfd_create         __NR_timerfd_create         /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
#define SYS_eventfd                __NR_eventfd                /* fd_t eventfd(syscall_ulong_t initval) */
#define SYS_fallocate              __NR_fallocate              /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
#define SYS_timerfd_settime        __NR_timerfd_settime        /* errno_t timerfd_settime(fd_t ufd, syscall_ulong_t flags, struct __itimerspecx64 const *utmr, struct __itimerspecx64 *otmr) */
/* Return the next expiration time of UFD */
#define SYS_timerfd_gettime        __NR_timerfd_gettime        /* errno_t timerfd_gettime(fd_t ufd, struct __itimerspecx64 *otmr) */
#define SYS_accept4                __NR_accept4                /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t flags) */
#define SYS_signalfd4              __NR_signalfd4              /* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigsetsize, syscall_ulong_t flags) */
#define SYS_eventfd2               __NR_eventfd2               /* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
#define SYS_epoll_create1          __NR_epoll_create1          /* fd_t epoll_create1(syscall_ulong_t flags) */
/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
#define SYS_dup3                   __NR_dup3                   /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
#define SYS_pipe2                  __NR_pipe2                  /* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
#define SYS_inotify_init1          __NR_inotify_init1          /* errno_t inotify_init1(int TODO_PROTOTYPE) */
#define SYS_preadv                 __NR_preadv                 /* ssize_t preadv(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset) */
#define SYS_pwritev                __NR_pwritev                /* ssize_t pwritev(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset) */
/* @param: signo: One of `SIG*' */
#define SYS_rt_tgsigqueueinfo      __NR_rt_tgsigqueueinfo      /* errno_t rt_tgsigqueueinfo(pid_t tgid, pid_t tid, syscall_ulong_t signo, struct __siginfo64_struct const *uinfo) */
#define SYS_perf_event_open        __NR_perf_event_open        /* errno_t perf_event_open(int TODO_PROTOTYPE) */
#define SYS_recvmmsg               __NR_recvmmsg               /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags, struct __timespecx64 *tmo) */
#define SYS_fanotify_init          __NR_fanotify_init          /* errno_t fanotify_init(int TODO_PROTOTYPE) */
#define SYS_fanotify_mark          __NR_fanotify_mark          /* errno_t fanotify_mark(int TODO_PROTOTYPE) */
/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
#define SYS_prlimit64              __NR_prlimit64              /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
#define SYS_name_to_handle_at      __NR_name_to_handle_at      /* errno_t name_to_handle_at(fd_t dirfd, char const *name, struct file_handle *handle, int32_t *mnt_id, syscall_ulong_t flags) */
#define SYS_open_by_handle_at      __NR_open_by_handle_at      /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle *handle, syscall_ulong_t flags) */
#define SYS_clock_adjtime          __NR_clock_adjtime          /* errno_t clock_adjtime(int TODO_PROTOTYPE) */
#define SYS_syncfs                 __NR_syncfs                 /* errno_t syncfs(fd_t fd) */
#define SYS_sendmmsg               __NR_sendmmsg               /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t flags) */
#define SYS_setns                  __NR_setns                  /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
#define SYS_getcpu                 __NR_getcpu                 /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
#define SYS_process_vm_readv       __NR_process_vm_readv       /* ssize_t process_vm_readv(pid_t pid, struct iovec64 const *local_iov, size_t liovcnt, struct iovec64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
#define SYS_process_vm_writev      __NR_process_vm_writev      /* ssize_t process_vm_writev(pid_t pid, struct iovec64 const *local_iov, size_t liovcnt, struct iovec64 const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
#define SYS_kcmp                   __NR_kcmp                   /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
#define SYS_finit_module           __NR_finit_module           /* errno_t finit_module(int TODO_PROTOTYPE) */
#define SYS_sched_setattr          __NR_sched_setattr          /* errno_t sched_setattr(int TODO_PROTOTYPE) */
#define SYS_sched_getattr          __NR_sched_getattr          /* errno_t sched_getattr(int TODO_PROTOTYPE) */
/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
#define SYS_renameat2              __NR_renameat2              /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, syscall_ulong_t flags) */
#define SYS_seccomp                __NR_seccomp                /* errno_t seccomp(int TODO_PROTOTYPE) */
#define SYS_getrandom              __NR_getrandom              /* errno_t getrandom(int TODO_PROTOTYPE) */
#define SYS_memfd_create           __NR_memfd_create           /* errno_t memfd_create(int TODO_PROTOTYPE) */
#define SYS_kexec_file_load        __NR_kexec_file_load        /* errno_t kexec_file_load(int TODO_PROTOTYPE) */
#define SYS_bpf                    __NR_bpf                    /* errno_t bpf(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_execveat               __NR_execveat               /* errno_t execveat(fd_t dirfd, char const *pathname, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp, atflag_t flags) */
#define SYS_userfaultfd            __NR_userfaultfd            /* errno_t userfaultfd(int TODO_PROTOTYPE) */
#define SYS_membarrier             __NR_membarrier             /* errno_t membarrier(int TODO_PROTOTYPE) */
#define SYS_mlock2                 __NR_mlock2                 /* errno_t mlock2(int TODO_PROTOTYPE) */
#define SYS_pwritevf               __NR_pwritevf               /* ssize_t pwritevf(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
#define SYS_preadvf                __NR_preadvf                /* ssize_t preadvf(fd_t fd, struct iovec64 const *iovec, size_t count, uint64_t offset, iomode_t mode) */
/* @param: flags: Set of `0 | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define SYS_freadlinkat            __NR_freadlinkat            /* ssize_t freadlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define SYS_fsymlinkat             __NR_fsymlinkat             /* errno_t fsymlinkat(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define SYS_frenameat              __NR_frenameat              /* errno_t frenameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path, atflag_t flags) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_kfstatat               __NR_kfstatat               /* errno_t kfstatat(fd_t dirfd, char const *filename, struct __kos_statx64 *statbuf, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define SYS_fmknodat               __NR_fmknodat               /* errno_t fmknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev, atflag_t flags) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define SYS_fmkdirat               __NR_fmkdirat               /* errno_t fmkdirat(fd_t dirfd, char const *pathname, mode_t mode, atflag_t flags) */
#define SYS_ksysctl                __NR_ksysctl                /* syscall_slong_t ksysctl(syscall_ulong_t command, void *arg) */
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
#define SYS_maplibrary             __NR_maplibrary             /* void *maplibrary(void *addr, syscall_ulong_t flags, fd_t fd, struct elf64_phdr *hdrv, size_t hdrc) */
#define SYS_fsmode                 __NR_fsmode                 /* uint64_t fsmode(uint64_t mode) */
/* @param: flags: Set of `0 | AT_DOSPATH' */
#define SYS_fchdirat               __NR_fchdirat               /* errno_t fchdirat(fd_t dirfd, char const *path, atflag_t flags) */
#define SYS_kreaddirf              __NR_kreaddirf              /* ssize_t kreaddirf(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode, iomode_t iomode) */
#define SYS_kreaddir               __NR_kreaddir               /* ssize_t kreaddir(fd_t fd, struct dirent *buf, size_t bufsize, syscall_ulong_t mode) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_process_spawnveat      __NR_process_spawnveat      /* errno_t process_spawnveat(fd_t dirfd, char const *pathname, __HYBRID_PTR64(char const) const *argv, __HYBRID_PTR64(char const) const *envp, atflag_t flags, struct spawn_actionsx64 const *actions) */
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
#define SYS_coredump               __NR_coredump               /* errno_t coredump(struct ucpustate64 const *curr_state, struct ucpustate64 const *orig_state, __HYBRID_PTR64(void) const *traceback_vector, size_t traceback_length, struct exception_data64 const *exception, syscall_ulong_t unwind_error) */
/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
#define SYS_raiseat                __NR_raiseat                /* errno_t raiseat(struct ucpustate64 const *state, struct __siginfo64_struct const *si) */
/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
#define SYS_mktty                  __NR_mktty                  /* fd_t mktty(fd_t keyboard, fd_t display, char const *name, syscall_ulong_t rsvd) */
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
#define SYS_lfutexlockexpr         __NR_lfutexlockexpr         /* errno_t lfutexlockexpr(uint64_t *ulockaddr, void *base, size_t exprc, struct lfutexexprx64 const *exprv, struct __timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
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
#define SYS_lfutexexpr             __NR_lfutexexpr             /* errno_t lfutexexpr(void *base, size_t exprc, struct lfutexexprx64 const *exprv, struct __timespecx64 const *timeout, syscall_ulong_t timeout_flags) */
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
#define SYS_lfutex                 __NR_lfutex                 /* syscall_slong_t lfutex(uint64_t *uaddr, syscall_ulong_t futex_op, uint64_t val, struct __timespecx64 const *timeout, uint64_t val2) */
#define SYS_rpc_service            __NR_rpc_service            /* syscall_slong_t rpc_service(void) */
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
#define SYS_debugtrap              __NR_debugtrap              /* errno_t debugtrap(struct ucpustate64 const *state, struct debugtrap_reason64 const *reason) */
/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
#define SYS_set_library_listdef    __NR_set_library_listdef    /* errno_t set_library_listdef(struct library_listdef64 const *listdef) */
#define SYS_writevf                __NR_writevf                /* ssize_t writevf(fd_t fd, struct iovec64 const *iovec, size_t count, iomode_t mode) */
#define SYS_readvf                 __NR_readvf                 /* ssize_t readvf(fd_t fd, struct iovec64 const *iovec, size_t count, iomode_t mode) */
#define SYS_pwrite64f              __NR_pwrite64f              /* ssize_t pwrite64f(fd_t fd, void const *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define SYS_pread64f               __NR_pread64f               /* ssize_t pread64f(fd_t fd, void *buf, size_t bufsize, uint64_t offset, iomode_t mode) */
#define SYS_ioctlf                 __NR_ioctlf                 /* syscall_slong_t ioctlf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
#define SYS_set_exception_handler  __NR_set_exception_handler  /* errno_t set_exception_handler(syscall_ulong_t mode, except_handler_t handler, void *handler_sp) */
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
#define SYS_get_exception_handler  __NR_get_exception_handler  /* errno_t get_exception_handler(__ULONG64_TYPE__ *pmode, __except_handler64_t *phandler, __HYBRID_PTR64(void) *phandler_sp) */
/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
#define SYS_openpty                __NR_openpty                /* errno_t openpty(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp) */
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
#define SYS_rpc_schedule           __NR_rpc_schedule           /* syscall_slong_t rpc_schedule(pid_t target, syscall_ulong_t flags, uint8_t const *program, __HYBRID_PTR64(void) *arguments) */
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define SYS_frealpathat            __NR_frealpathat            /* ssize_t frealpathat(fd_t dirfd, char const *filename, char *buf, size_t buflen, atflag_t flags) */
/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0 | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH' */
#define SYS_frealpath4             __NR_frealpath4             /* ssize_t frealpath4(fd_t fd, char *buf, size_t buflen, atflag_t flags) */
/* Returns a bitset of all of the currently mounted dos-drives */
#define SYS_getdrives              __NR_getdrives              /* syscall_slong_t getdrives(void) */
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
#define SYS_detach                 __NR_detach                 /* errno_t detach(pid_t pid) */
#define SYS_readf                  __NR_readf                  /* ssize_t readf(fd_t fd, void *buf, size_t bufsize, iomode_t mode) */
#define SYS_klstat                 __NR_klstat                 /* errno_t klstat(char const *filename, struct __kos_statx64 *statbuf) */
#define SYS_kfstat                 __NR_kfstat                 /* errno_t kfstat(fd_t fd, struct __kos_statx64 *statbuf) */
#define SYS_kstat                  __NR_kstat                  /* errno_t kstat(char const *filename, struct __kos_statx64 *statbuf) */
#define SYS_hopf                   __NR_hopf                   /* syscall_slong_t hopf(fd_t fd, syscall_ulong_t command, iomode_t mode, void *arg) */
#define SYS_hop                    __NR_hop                    /* syscall_slong_t hop(fd_t fd, syscall_ulong_t command, void *arg) */
#define SYS_writef                 __NR_writef                 /* ssize_t writef(fd_t fd, void const *buf, size_t bufsize, iomode_t mode) */

#endif /* !_I386_KOS_BITS_SYSCALLS64_H */
