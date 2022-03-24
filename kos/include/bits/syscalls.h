/* HASH CRC-32:0x8de4e5b8 */
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

#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H 1

#ifndef __NR_io_setup
#include "../asm/syscalls.h"
#endif /* !__NR_io_setup */

#define SYS_io_setup               __NR_io_setup               /* errno_t io_setup(int TODO_PROTOTYPE) */
#define SYS_io_destroy             __NR_io_destroy             /* errno_t io_destroy(int TODO_PROTOTYPE) */
#define SYS_io_submit              __NR_io_submit              /* errno_t io_submit(int TODO_PROTOTYPE) */
#define SYS_io_cancel              __NR_io_cancel              /* errno_t io_cancel(int TODO_PROTOTYPE) */
#define SYS_io_getevents           __NR_io_getevents           /* errno_t io_getevents(int TODO_PROTOTYPE) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define SYS_setxattr               __NR_setxattr               /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define SYS_lsetxattr              __NR_lsetxattr              /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define SYS_fsetxattr              __NR_fsetxattr              /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define SYS_getxattr               __NR_getxattr               /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define SYS_lgetxattr              __NR_lgetxattr              /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define SYS_fgetxattr              __NR_fgetxattr              /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define SYS_listxattr              __NR_listxattr              /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define SYS_llistxattr             __NR_llistxattr             /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define SYS_flistxattr             __NR_flistxattr             /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define SYS_removexattr            __NR_removexattr            /* errno_t removexattr(char const *path, char const *name) */
#define SYS_lremovexattr           __NR_lremovexattr           /* errno_t lremovexattr(char const *path, char const *name) */
#define SYS_fremovexattr           __NR_fremovexattr           /* errno_t fremovexattr(fd_t fd, char const *name) */
#define SYS_getcwd                 __NR_getcwd                 /* ssize_t getcwd(char *buf, size_t size) */
#define SYS_lookup_dcookie         __NR_lookup_dcookie         /* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
#define SYS_eventfd2               __NR_eventfd2               /* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
#define SYS_epoll_create1          __NR_epoll_create1          /* fd_t epoll_create1(syscall_ulong_t flags) */
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
#define SYS_epoll_ctl              __NR_epoll_ctl              /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
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
#define SYS_epoll_pwait            __NR_epoll_pwait            /* ssize_t epoll_pwait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss, size_t sigsetsize) */
#define SYS_dup                    __NR_dup                    /* fd_t dup(fd_t fd) */
/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
#define SYS_dup3                   __NR_dup3                   /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
#define SYS_inotify_init1          __NR_inotify_init1          /* errno_t inotify_init1(int TODO_PROTOTYPE) */
#define SYS_inotify_add_watch      __NR_inotify_add_watch      /* errno_t inotify_add_watch(int TODO_PROTOTYPE) */
#define SYS_inotify_rm_watch       __NR_inotify_rm_watch       /* errno_t inotify_rm_watch(int TODO_PROTOTYPE) */
#define SYS_ioctl                  __NR_ioctl                  /* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define SYS_ioprio_set             __NR_ioprio_set             /* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define SYS_ioprio_get             __NR_ioprio_get             /* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
#define SYS_flock                  __NR_flock                  /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
#define SYS_mknodat                __NR_mknodat                /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
#define SYS_mkdirat                __NR_mkdirat                /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
#define SYS_unlinkat               __NR_unlinkat               /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define SYS_symlinkat              __NR_symlinkat              /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define SYS_linkat                 __NR_linkat                 /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define SYS_renameat               __NR_renameat               /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
#define SYS_umount2                __NR_umount2                /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
#define SYS_mount                  __NR_mount                  /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
#define SYS_pivot_root             __NR_pivot_root             /* errno_t pivot_root(int TODO_PROTOTYPE) */
#define SYS_nfsservctl             __NR_nfsservctl             /* errno_t nfsservctl(int TODO_PROTOTYPE) */
/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
#define SYS_fallocate              __NR_fallocate              /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
#define SYS_faccessat              __NR_faccessat              /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
#define SYS_chdir                  __NR_chdir                  /* errno_t chdir(char const *path) */
#define SYS_fchdir                 __NR_fchdir                 /* errno_t fchdir(fd_t fd) */
#define SYS_chroot                 __NR_chroot                 /* errno_t chroot(char const *path) */
#define SYS_fchmod                 __NR_fchmod                 /* errno_t fchmod(fd_t fd, mode_t mode) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_fchmodat               __NR_fchmodat               /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_fchownat               __NR_fchownat               /* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
#define SYS_fchown                 __NR_fchown                 /* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
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
#define SYS_openat                 __NR_openat                 /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `fd' */
#define SYS_close                  __NR_close                  /* errno_t close(fd_t fd) */
#define SYS_vhangup                __NR_vhangup                /* errno_t vhangup(void) */
#define SYS_pipe2                  __NR_pipe2                  /* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
#define SYS_quotactl               __NR_quotactl               /* errno_t quotactl(int TODO_PROTOTYPE) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define SYS_getdents64             __NR_getdents64             /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
#define SYS_read                   __NR_read                   /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
#define SYS_write                  __NR_write                  /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
#define SYS_readv                  __NR_readv                  /* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
#define SYS_writev                 __NR_writev                 /* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
#define SYS_pread64                __NR_pread64                /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define SYS_pwrite64               __NR_pwrite64               /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
#define SYS_preadv                 __NR_preadv                 /* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
#define SYS_pwritev                __NR_pwritev                /* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
#define SYS_pselect6               __NR_pselect6               /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
#define SYS_ppoll                  __NR_ppoll                  /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespec const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
#define SYS_signalfd4              __NR_signalfd4              /* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define SYS_vmsplice               __NR_vmsplice               /* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define SYS_splice                 __NR_splice                 /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define SYS_tee                    __NR_tee                    /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
#define SYS_readlinkat             __NR_readlinkat             /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
#define SYS_sync                   __NR_sync                   /* errno_t sync(void) */
/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
#define SYS_fsync                  __NR_fsync                  /* errno_t fsync(fd_t fd) */
/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
#define SYS_fdatasync              __NR_fdatasync              /* errno_t fdatasync(fd_t fd) */
/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
#define SYS_sync_file_range        __NR_sync_file_range        /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
#define SYS_timerfd_create         __NR_timerfd_create         /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
#define SYS_timerfd_settime        __NR_timerfd_settime        /* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspec const *utmr, struct itimerspec *otmr) */
/* Return the next expiration time of UFD */
#define SYS_timerfd_gettime        __NR_timerfd_gettime        /* errno_t timerfd_gettime(fd_t timerfd, struct itimerspec *otmr) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
#define SYS_utimensat              __NR_utimensat              /* errno_t utimensat(fd_t dirfd, char const *filename, struct timespec const[2] times, atflag_t flags) */
#define SYS_acct                   __NR_acct                   /* errno_t acct(char const *filename) */
#define SYS_capget                 __NR_capget                 /* errno_t capget(int TODO_PROTOTYPE) */
#define SYS_capset                 __NR_capset                 /* errno_t capset(int TODO_PROTOTYPE) */
#define SYS_personality            __NR_personality            /* errno_t personality(int TODO_PROTOTYPE) */
/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define SYS_exit                   __NR_exit                   /* void exit(syscall_ulong_t exit_code) */
/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define SYS_exit_group             __NR_exit_group             /* void exit_group(syscall_ulong_t exit_code) */
/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
#define SYS_waitid                 __NR_waitid                 /* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
#define SYS_set_tid_address        __NR_set_tid_address        /* pid_t set_tid_address(pid_t *tidptr) */
/* param: what: Set of `CLONE_*' */
#define SYS_unshare                __NR_unshare                /* errno_t unshare(syscall_ulong_t what) */
/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
#define SYS_futex                  __NR_futex                  /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define SYS_set_robust_list        __NR_set_robust_list        /* errno_t set_robust_list(int TODO_PROTOTYPE) */
#define SYS_get_robust_list        __NR_get_robust_list        /* errno_t get_robust_list(int TODO_PROTOTYPE) */
#define SYS_nanosleep              __NR_nanosleep              /* errno_t nanosleep(struct timespec const *req, struct timespec *rem) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define SYS_getitimer              __NR_getitimer              /* errno_t getitimer(syscall_ulong_t which, struct itimerval *curr_value) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define SYS_setitimer              __NR_setitimer              /* errno_t setitimer(syscall_ulong_t which, struct itimerval const *newval, struct itimerval *oldval) */
#define SYS_kexec_load             __NR_kexec_load             /* errno_t kexec_load(int TODO_PROTOTYPE) */
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
#define SYS_init_module            __NR_init_module            /* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
#define SYS_delete_module          __NR_delete_module          /* errno_t delete_module(char const *name, oflag_t flags) */
#define SYS_timer_create           __NR_timer_create           /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
#define SYS_timer_gettime          __NR_timer_gettime          /* errno_t timer_gettime(timer_t timerid, struct itimerspec *value) */
#define SYS_timer_getoverrun       __NR_timer_getoverrun       /* syscall_slong_t timer_getoverrun(timer_t timerid) */
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
#define SYS_timer_settime          __NR_timer_settime          /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspec const *value, struct itimerspec *ovalue) */
#define SYS_timer_delete           __NR_timer_delete           /* errno_t timer_delete(timer_t timerid) */
#define SYS_clock_settime          __NR_clock_settime          /* errno_t clock_settime(clockid_t clock_id, struct timespec const *tp) */
#define SYS_clock_gettime          __NR_clock_gettime          /* errno_t clock_gettime(clockid_t clock_id, struct timespec *tp) */
#define SYS_clock_getres           __NR_clock_getres           /* errno_t clock_getres(clockid_t clock_id, struct timespec *res) */
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
#define SYS_clock_nanosleep        __NR_clock_nanosleep        /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespec const *requested_time, struct timespec *remaining) */
#define SYS_syslog                 __NR_syslog                 /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
#define SYS_ptrace                 __NR_ptrace                 /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
#define SYS_sched_setparam         __NR_sched_setparam         /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
#define SYS_sched_setscheduler     __NR_sched_setscheduler     /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define SYS_sched_getscheduler     __NR_sched_getscheduler     /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define SYS_sched_getparam         __NR_sched_getparam         /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
#define SYS_sched_setaffinity      __NR_sched_setaffinity      /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define SYS_sched_getaffinity      __NR_sched_getaffinity      /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define SYS_sched_yield            __NR_sched_yield            /* errno_t sched_yield(void) */
#define SYS_sched_get_priority_max __NR_sched_get_priority_max /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define SYS_sched_get_priority_min __NR_sched_get_priority_min /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define SYS_sched_rr_get_interval  __NR_sched_rr_get_interval  /* errno_t sched_rr_get_interval(pid_t pid, struct timespec *ts) */
#define SYS_restart_syscall        __NR_restart_syscall        /* errno_t restart_syscall(void) */
#define SYS_kill                   __NR_kill                   /* errno_t kill(pid_t pid, signo_t signo) */
#define SYS_tkill                  __NR_tkill                  /* errno_t tkill(pid_t tid, signo_t signo) */
#define SYS_tgkill                 __NR_tgkill                 /* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
#define SYS_sigaltstack            __NR_sigaltstack            /* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
#define SYS_rt_sigsuspend          __NR_rt_sigsuspend          /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define SYS_rt_sigaction           __NR_rt_sigaction           /* errno_t rt_sigaction(signo_t signo, struct __kernel_sigaction const *act, struct __kernel_sigaction *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define SYS_rt_sigprocmask         __NR_rt_sigprocmask         /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
#define SYS_rt_sigpending          __NR_rt_sigpending          /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define SYS_rt_sigtimedwait        __NR_rt_sigtimedwait        /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec const *timeout, size_t sigsetsize) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define SYS_rt_sigqueueinfo        __NR_rt_sigqueueinfo        /* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfo_struct const *uinfo) */
#define SYS_rt_sigreturn           __NR_rt_sigreturn           /* void rt_sigreturn(void) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define SYS_setpriority            __NR_setpriority            /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define SYS_getpriority            __NR_getpriority            /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
#define SYS_reboot                 __NR_reboot                 /* errno_t reboot(syscall_ulong_t how) */
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define SYS_setregid               __NR_setregid               /* errno_t setregid(gid_t rgid, gid_t egid) */
/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define SYS_setgid                 __NR_setgid                 /* errno_t setgid(gid_t gid) */
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define SYS_setreuid               __NR_setreuid               /* errno_t setreuid(uid_t ruid, uid_t euid) */
/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define SYS_setuid                 __NR_setuid                 /* errno_t setuid(uid_t uid) */
/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define SYS_setresuid              __NR_setresuid              /* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
#define SYS_getresuid              __NR_getresuid              /* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define SYS_setresgid              __NR_setresgid              /* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
#define SYS_getresgid              __NR_getresgid              /* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define SYS_setfsuid               __NR_setfsuid               /* errno_t setfsuid(uid_t uid) */
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define SYS_setfsgid               __NR_setfsgid               /* errno_t setfsgid(gid_t gid) */
#define SYS_times                  __NR_times                  /* clock_t times(struct tms *buf) */
#define SYS_setpgid                __NR_setpgid                /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define SYS_getpgid                __NR_getpgid                /* pid_t getpgid(pid_t pid) */
#define SYS_getsid                 __NR_getsid                 /* pid_t getsid(pid_t pid) */
#define SYS_setsid                 __NR_setsid                 /* pid_t setsid(void) */
/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
#define SYS_getgroups              __NR_getgroups              /* ssize_t getgroups(size_t count, gid_t[] list) */
#define SYS_setgroups              __NR_setgroups              /* errno_t setgroups(size_t count, gid_t const *groups) */
#define SYS_uname                  __NR_uname                  /* errno_t uname(struct utsname *name) */
#define SYS_sethostname            __NR_sethostname            /* errno_t sethostname(char const *name, size_t len) */
#define SYS_setdomainname          __NR_setdomainname          /* errno_t setdomainname(char const *name, size_t len) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define SYS_getrlimit              __NR_getrlimit              /* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define SYS_setrlimit              __NR_setrlimit              /* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
#define SYS_getrusage              __NR_getrusage              /* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
#define SYS_umask                  __NR_umask                  /* mode_t umask(mode_t mode) */
/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
#define SYS_prctl                  __NR_prctl                  /* syscall_slong_t prctl(unsigned int command, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5) */
#define SYS_getcpu                 __NR_getcpu                 /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
#define SYS_gettimeofday           __NR_gettimeofday           /* errno_t gettimeofday(struct timeval *tv, struct timezone *tz) */
#define SYS_settimeofday           __NR_settimeofday           /* errno_t settimeofday(struct timeval const *tv, struct timezone const *tz) */
#define SYS_adjtimex               __NR_adjtimex               /* errno_t adjtimex(struct timex *ntx) */
#define SYS_getpid                 __NR_getpid                 /* pid_t getpid(void) */
#define SYS_getppid                __NR_getppid                /* pid_t getppid(void) */
/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
#define SYS_getuid                 __NR_getuid                 /* uid_t getuid(void) */
/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
#define SYS_geteuid                __NR_geteuid                /* uid_t geteuid(void) */
/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
#define SYS_getgid                 __NR_getgid                 /* gid_t getgid(void) */
/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
#define SYS_getegid                __NR_getegid                /* gid_t getegid(void) */
#define SYS_gettid                 __NR_gettid                 /* pid_t gettid(void) */
#define SYS_sysinfo                __NR_sysinfo                /* errno_t sysinfo(struct sysinfo *info) */
#define SYS_mq_open                __NR_mq_open                /* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
#define SYS_mq_unlink              __NR_mq_unlink              /* errno_t mq_unlink(char const *name) */
#define SYS_mq_timedsend           __NR_mq_timedsend           /* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec const *abs_timeout) */
#define SYS_mq_timedreceive        __NR_mq_timedreceive        /* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec const *abs_timeout) */
#define SYS_mq_notify              __NR_mq_notify              /* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
#define SYS_mq_getsetattr          __NR_mq_getsetattr          /* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
#define SYS_msgget                 __NR_msgget                 /* errno_t msgget(int TODO_PROTOTYPE) */
#define SYS_msgctl                 __NR_msgctl                 /* errno_t msgctl(int TODO_PROTOTYPE) */
#define SYS_msgrcv                 __NR_msgrcv                 /* errno_t msgrcv(int TODO_PROTOTYPE) */
#define SYS_msgsnd                 __NR_msgsnd                 /* errno_t msgsnd(int TODO_PROTOTYPE) */
#define SYS_semget                 __NR_semget                 /* errno_t semget(int TODO_PROTOTYPE) */
#define SYS_semctl                 __NR_semctl                 /* errno_t semctl(int TODO_PROTOTYPE) */
#define SYS_semtimedop             __NR_semtimedop             /* errno_t semtimedop(int TODO_PROTOTYPE) */
#define SYS_semop                  __NR_semop                  /* errno_t semop(int TODO_PROTOTYPE) */
#define SYS_shmget                 __NR_shmget                 /* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
#define SYS_shmctl                 __NR_shmctl                 /* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
#define SYS_shmat                  __NR_shmat                  /* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
#define SYS_shmdt                  __NR_shmdt                  /* errno_t shmdt(void const *shmaddr) */
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
#define SYS_socket                 __NR_socket                 /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
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
#define SYS_socketpair             __NR_socketpair             /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
#define SYS_bind                   __NR_bind                   /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
#define SYS_listen                 __NR_listen                 /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
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
#define SYS_accept                 __NR_accept                 /* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
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
#define SYS_connect                __NR_connect                /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
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
#define SYS_getsockname            __NR_getsockname            /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
#define SYS_getpeername            __NR_getpeername            /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
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
#define SYS_sendto                 __NR_sendto                 /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
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
#define SYS_recvfrom               __NR_recvfrom               /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
#define SYS_setsockopt             __NR_setsockopt             /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
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
#define SYS_getsockopt             __NR_getsockopt             /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
#define SYS_shutdown               __NR_shutdown               /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
#define SYS_sendmsg                __NR_sendmsg                /* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t msg_flags) */
/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
#define SYS_recvmsg                __NR_recvmsg                /* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t msg_flags) */
#define SYS_readahead              __NR_readahead              /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
#define SYS_brk                    __NR_brk                    /* errno_t brk(void *addr) */
#define SYS_munmap                 __NR_munmap                 /* errno_t munmap(void *addr, size_t len) */
/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
#define SYS_mremap                 __NR_mremap                 /* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define SYS_add_key                __NR_add_key                /* errno_t add_key(int TODO_PROTOTYPE) */
#define SYS_request_key            __NR_request_key            /* errno_t request_key(int TODO_PROTOTYPE) */
#define SYS_keyctl                 __NR_keyctl                 /* errno_t keyctl(int TODO_PROTOTYPE) */
#define SYS_clone                  __NR_clone                  /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
#define SYS_execve                 __NR_execve                 /* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define SYS_swapon                 __NR_swapon                 /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
#define SYS_swapoff                __NR_swapoff                /* errno_t swapoff(char const *pathname) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
#define SYS_mprotect               __NR_mprotect               /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
#define SYS_msync                  __NR_msync                  /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
#define SYS_mlock                  __NR_mlock                  /* errno_t mlock(void const *addr, size_t len) */
#define SYS_munlock                __NR_munlock                /* errno_t munlock(void const *addr, size_t len) */
/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
#define SYS_mlockall               __NR_mlockall               /* errno_t mlockall(syscall_ulong_t flags) */
#define SYS_munlockall             __NR_munlockall             /* errno_t munlockall(void) */
#define SYS_mincore                __NR_mincore                /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define SYS_madvise                __NR_madvise                /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
#define SYS_remap_file_pages       __NR_remap_file_pages       /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
#define SYS_mbind                  __NR_mbind                  /* errno_t mbind(int TODO_PROTOTYPE) */
#define SYS_get_mempolicy          __NR_get_mempolicy          /* errno_t get_mempolicy(int TODO_PROTOTYPE) */
#define SYS_set_mempolicy          __NR_set_mempolicy          /* errno_t set_mempolicy(int TODO_PROTOTYPE) */
#define SYS_migrate_pages          __NR_migrate_pages          /* errno_t migrate_pages(int TODO_PROTOTYPE) */
#define SYS_move_pages             __NR_move_pages             /* errno_t move_pages(int TODO_PROTOTYPE) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define SYS_rt_tgsigqueueinfo      __NR_rt_tgsigqueueinfo      /* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfo_struct const *uinfo) */
#define SYS_perf_event_open        __NR_perf_event_open        /* errno_t perf_event_open(int TODO_PROTOTYPE) */
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
#define SYS_accept4                __NR_accept4                /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
#define SYS_recvmmsg               __NR_recvmmsg               /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec const *tmo) */
/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define SYS_wait4                  __NR_wait4                  /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define SYS_prlimit64              __NR_prlimit64              /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
#define SYS_fanotify_init          __NR_fanotify_init          /* errno_t fanotify_init(int TODO_PROTOTYPE) */
#define SYS_fanotify_mark          __NR_fanotify_mark          /* errno_t fanotify_mark(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define SYS_name_to_handle_at      __NR_name_to_handle_at      /* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
#define SYS_open_by_handle_at      __NR_open_by_handle_at      /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
#define SYS_clock_adjtime          __NR_clock_adjtime          /* errno_t clock_adjtime(int TODO_PROTOTYPE) */
#define SYS_syncfs                 __NR_syncfs                 /* errno_t syncfs(fd_t fd) */
#define SYS_setns                  __NR_setns                  /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
#define SYS_sendmmsg               __NR_sendmmsg               /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
#define SYS_process_vm_readv       __NR_process_vm_readv       /* ssize_t process_vm_readv(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
#define SYS_process_vm_writev      __NR_process_vm_writev      /* ssize_t process_vm_writev(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
#define SYS_kcmp                   __NR_kcmp                   /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
#define SYS_finit_module           __NR_finit_module           /* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
#define SYS_sched_setattr          __NR_sched_setattr          /* errno_t sched_setattr(int TODO_PROTOTYPE) */
#define SYS_sched_getattr          __NR_sched_getattr          /* errno_t sched_getattr(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
#define SYS_renameat2              __NR_renameat2              /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
#define SYS_seccomp                __NR_seccomp                /* errno_t seccomp(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
#define SYS_getrandom              __NR_getrandom              /* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
#define SYS_memfd_create           __NR_memfd_create           /* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
#define SYS_bpf                    __NR_bpf                    /* errno_t bpf(int TODO_PROTOTYPE) */
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define SYS_execveat               __NR_execveat               /* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
#define SYS_userfaultfd            __NR_userfaultfd            /* fd_t userfaultfd(syscall_ulong_t flags) */
#define SYS_membarrier             __NR_membarrier             /* errno_t membarrier(int TODO_PROTOTYPE) */
#define SYS_mlock2                 __NR_mlock2                 /* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
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
#define SYS_open                   __NR_open                   /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
#define SYS_link                   __NR_link                   /* errno_t link(char const *existing_file, char const *link_file) */
#define SYS_unlink                 __NR_unlink                 /* errno_t unlink(char const *filename) */
#define SYS_mknod                  __NR_mknod                  /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define SYS_chmod                  __NR_chmod                  /* errno_t chmod(char const *filename, mode_t mode) */
#define SYS_chown                  __NR_chown                  /* errno_t chown(char const *filename, uid_t owner, gid_t group) */
#define SYS_mkdir                  __NR_mkdir                  /* errno_t mkdir(char const *pathname, mode_t mode) */
#define SYS_rmdir                  __NR_rmdir                  /* errno_t rmdir(char const *path) */
#define SYS_lchown                 __NR_lchown                 /* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define SYS_access                 __NR_access                 /* errno_t access(char const *filename, syscall_ulong_t type) */
#define SYS_rename                 __NR_rename                 /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define SYS_readlink               __NR_readlink               /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
#define SYS_symlink                __NR_symlink                /* errno_t symlink(char const *link_text, char const *target_path) */
/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
#define SYS_utimes                 __NR_utimes                 /* errno_t utimes(char const *filename, struct timeval const[2] times) */
#define SYS_pipe                   __NR_pipe                   /* errno_t pipe(fd_t[2] pipedes) */
#define SYS_dup2                   __NR_dup2                   /* fd_t dup2(fd_t oldfd, fd_t newfd) */
/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
#define SYS_epoll_create           __NR_epoll_create           /* fd_t epoll_create(syscall_ulong_t size) */
#define SYS_inotify_init           __NR_inotify_init           /* errno_t inotify_init(int TODO_PROTOTYPE) */
#define SYS_eventfd                __NR_eventfd                /* fd_t eventfd(syscall_ulong_t initval) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
#define SYS_signalfd               __NR_signalfd               /* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
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
#define SYS_sendfile               __NR_sendfile               /* ssize_t sendfile(fd_t outfd, fd_t infd, syscall_ulong_t *pin_offset, size_t num_bytes) */
#define SYS_ftruncate              __NR_ftruncate              /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
#define SYS_truncate               __NR_truncate               /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define SYS_stat                   __NR_stat                   /* errno_t stat(char const *filename, struct linux_stat *statbuf) */
#define SYS_lstat                  __NR_lstat                  /* errno_t lstat(char const *filename, struct linux_stat *statbuf) */
#define SYS_fstat                  __NR_fstat                  /* errno_t fstat(fd_t fd, struct linux_stat *statbuf) */
#define SYS_fcntl                  __NR_fcntl                  /* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
#define SYS_fadvise64              __NR_fadvise64              /* errno_t fadvise64(int TODO_PROTOTYPE) */
#define SYS_newfstatat             __NR_newfstatat             /* errno_t newfstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
#define SYS_fstatfs                __NR_fstatfs                /* errno_t fstatfs(fd_t file, struct statfs *buf) */
#define SYS_statfs                 __NR_statfs                 /* errno_t statfs(char const *file, struct statfs *buf) */
#define SYS_lseek                  __NR_lseek                  /* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
#define SYS_mmap                   __NR_mmap                   /* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
#define SYS_alarm                  __NR_alarm                  /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
#define SYS_getpgrp                __NR_getpgrp                /* pid_t getpgrp(void) */
/* Same as `select(0, NULL, NULL, NULL, NULL)' */
#define SYS_pause                  __NR_pause                  /* errno_t pause(void) */
#define SYS_time                   __NR_time                   /* time32_t time(time32_t *timer) */
/* @param: times: When NULL, set the current time */
#define SYS_utime                  __NR_utime                  /* errno_t utime(char const *filename, struct utimbuf const *times) */
#define SYS_creat                  __NR_creat                  /* fd_t creat(char const *filename, mode_t mode) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define SYS_getdents               __NR_getdents               /* ssize_t getdents(fd_t fd, struct linux_dirent *buf, size_t buflen) */
#define SYS_futimesat              __NR_futimesat              /* errno_t futimesat(fd_t dirfd, char const *filename, struct timeval const[2] times) */
#define SYS_select                 __NR_select                 /* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval *timeout) */
#define SYS_poll                   __NR_poll                   /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
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
#define SYS_epoll_wait             __NR_epoll_wait             /* ssize_t epoll_wait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
#define SYS_ustat                  __NR_ustat                  /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
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
#define SYS_vfork                  __NR_vfork                  /* pid_t vfork(void) */
/* @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' */
#define SYS_oldwait4               __NR_oldwait4               /* pid_t oldwait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @return: * : [<= bufsize] The actual # of received bytes */
#define SYS_recv                   __NR_recv                   /* ssize_t recv(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags) */
/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @return: * : [<= bufsize] The actual # of send bytes */
#define SYS_send                   __NR_send                   /* ssize_t send(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags) */
#define SYS_bdflush                __NR_bdflush                /* errno_t bdflush(int TODO_PROTOTYPE) */
#define SYS_umount                 __NR_umount                 /* errno_t umount(char const *special_file) */
#define SYS_uselib                 __NR_uselib                 /* errno_t uselib(char const *library) */
#define SYS__sysctl                __NR__sysctl                /* errno_t _sysctl(int TODO_PROTOTYPE) */
/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
#define SYS_fork                   __NR_fork                   /* pid_t fork(void) */

#endif /* !_BITS_SYSCALLS_H */
