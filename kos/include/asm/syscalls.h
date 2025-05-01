/* HASH CRC-32:0xbb14ddeb */
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

/************************************************************************/
/* SYSCALL IDS                                                          */
/************************************************************************/
#ifndef __NR_io_setup
#define __NR_io_setup               0x0   /* errno_t io_setup(int TODO_PROTOTYPE) */
#define __NR_io_destroy             0x1   /* errno_t io_destroy(int TODO_PROTOTYPE) */
#define __NR_io_submit              0x2   /* errno_t io_submit(int TODO_PROTOTYPE) */
#define __NR_io_cancel              0x3   /* errno_t io_cancel(int TODO_PROTOTYPE) */
#define __NR_io_getevents           0x4   /* errno_t io_getevents(int TODO_PROTOTYPE) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR_setxattr               0x5   /* errno_t setxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR_lsetxattr              0x6   /* errno_t lsetxattr(char const *path, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
/* @param: flags: One of `0', `XATTR_CREATE' or `XATTR_REPLACE' */
#define __NR_fsetxattr              0x7   /* errno_t fsetxattr(fd_t fd, char const *name, void const *buf, size_t bufsize, syscall_ulong_t flags) */
#define __NR_getxattr               0x8   /* ssize_t getxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR_lgetxattr              0x9   /* ssize_t lgetxattr(char const *path, char const *name, void *buf, size_t bufsize) */
#define __NR_fgetxattr              0xa   /* ssize_t fgetxattr(fd_t fd, char const *name, void *buf, size_t bufsize) */
#define __NR_listxattr              0xb   /* ssize_t listxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR_llistxattr             0xc   /* ssize_t llistxattr(char const *path, char *listbuf, size_t listbufsize) */
#define __NR_flistxattr             0xd   /* ssize_t flistxattr(fd_t fd, char *listbuf, size_t listbufsize) */
#define __NR_removexattr            0xe   /* errno_t removexattr(char const *path, char const *name) */
#define __NR_lremovexattr           0xf   /* errno_t lremovexattr(char const *path, char const *name) */
#define __NR_fremovexattr           0x10  /* errno_t fremovexattr(fd_t fd, char const *name) */
#define __NR_getcwd                 0x11  /* ssize_t getcwd(char *buf, size_t size) */
#define __NR_lookup_dcookie         0x12  /* errno_t lookup_dcookie(int TODO_PROTOTYPE) */
/* @param: flags: Set of `EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC | EFD_CLOFORK' */
#define __NR_eventfd2               0x13  /* fd_t eventfd2(syscall_ulong_t initval, syscall_ulong_t flags) */
/* >> epoll_create1(2)
 * Create  a new epoll control descriptor which can be used for
 * monitoring of pollable events happening in registered files.
 * @param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
 * @return: * :   The newly created epoll control descriptor.
 * @throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...] */
#define __NR_epoll_create1          0x14  /* fd_t epoll_create1(syscall_ulong_t flags) */
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
#define __NR_epoll_ctl              0x15  /* errno_t epoll_ctl(fd_t epfd, syscall_ulong_t op, fd_t fd, struct epoll_event *info) */
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
#define __NR_epoll_pwait            0x16  /* ssize_t epoll_pwait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout, struct __sigset_struct const *ss, size_t sigsetsize) */
#define __NR_dup                    0x17  /* fd_t dup(fd_t fd) */
/* @param: flags:  Set of `O_CLOEXEC | O_CLOFORK' */
#define __NR_dup3                   0x18  /* fd_t dup3(fd_t oldfd, fd_t newfd, oflag_t flags) */
/* @param: flags: Set of `IN_NONBLOCK | IN_CLOEXEC | IN_CLOFORK' */
#define __NR_inotify_init1          0x1a  /* fd_t inotify_init1(syscall_ulong_t flags) */
/* @param: mask: Set of `IN_ALL_EVENTS | ...' */
#define __NR_inotify_add_watch      0x1b  /* int inotify_add_watch(fd_t notify_fd, char const *pathname, uint32_t mask) */
/* @param: wd: Watch fd (as returned by `inotify_add_watch{_at}') */
#define __NR_inotify_rm_watch       0x1c  /* errno_t inotify_rm_watch(fd_t notify_fd, int wd) */
#define __NR_ioctl                  0x1d  /* syscall_slong_t ioctl(fd_t fd, ioctl_t command, void *arg) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define __NR_ioprio_set             0x1e  /* errno_t ioprio_set(syscall_ulong_t who, syscall_ulong_t id, syscall_ulong_t ioprio) */
/* NOTE: Linux calls `who' `which', and `id' `who' (refactored to prevent confusion)
 * @param: who: One of `IOPRIO_WHO_PROCESS', `IOPRIO_WHO_PGRP' or `IOPRIO_WHO_USER' */
#define __NR_ioprio_get             0x1f  /* syscall_slong_t ioprio_get(syscall_ulong_t who, syscall_ulong_t id) */
#define __NR_flock                  0x20  /* errno_t flock(fd_t fd, syscall_ulong_t operation) */
#define __NR_mknodat                0x21  /* errno_t mknodat(fd_t dirfd, char const *nodename, mode_t mode, dev_t dev) */
#define __NR_mkdirat                0x22  /* errno_t mkdirat(fd_t dirfd, char const *pathname, mode_t mode) */
/* @param: flags: Set of `0 | AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH' */
#define __NR_unlinkat               0x23  /* errno_t unlinkat(fd_t dirfd, char const *name, atflag_t flags) */
#define __NR_symlinkat              0x24  /* errno_t symlinkat(char const *link_text, fd_t tofd, char const *target_path) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define __NR_linkat                 0x25  /* errno_t linkat(fd_t fromfd, char const *existing_file, fd_t tofd, char const *target_path, atflag_t flags) */
#define __NR_renameat               0x26  /* errno_t renameat(fd_t oldfd, char const *oldname, fd_t newfd, char const *newname_or_path) */
#define __NR_umount2                0x27  /* errno_t umount2(char const *special_file, syscall_ulong_t flags) */
#define __NR_mount                  0x28  /* errno_t mount(char const *special_file, char const *dir, char const *fstype, syscall_ulong_t mountflags, void const *data) */
#define __NR_pivot_root             0x29  /* errno_t pivot_root(int TODO_PROTOTYPE) */
#define __NR_nfsservctl             0x2a  /* errno_t nfsservctl(int TODO_PROTOTYPE) */
/* @param: mode: Set of `0 | FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE' */
#define __NR_fallocate              0x2f  /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, syscall_ulong_t offset, syscall_ulong_t length) */
/* @param: type: Set of `R_OK | W_OK | X_OK' or `F_OK' */
#define __NR_faccessat              0x30  /* errno_t faccessat(fd_t dirfd, char const *filename, syscall_ulong_t type) */
#define __NR_chdir                  0x31  /* errno_t chdir(char const *path) */
#define __NR_fchdir                 0x32  /* errno_t fchdir(fd_t fd) */
#define __NR_chroot                 0x33  /* errno_t chroot(char const *path) */
#define __NR_fchmod                 0x34  /* errno_t fchmod(fd_t fd, mode_t mode) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_fchmodat               0x35  /* errno_t fchmodat(fd_t dirfd, char const *filename, mode_t mode, atflag_t flags) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_fchownat               0x36  /* errno_t fchownat(fd_t dirfd, char const *filename, uid_t owner, gid_t group, atflag_t flags) */
#define __NR_fchown                 0x37  /* errno_t fchown(fd_t fd, uid_t owner, gid_t group) */
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
#define __NR_openat                 0x38  /* fd_t openat(fd_t dirfd, char const *filename, oflag_t oflags, mode_t mode) */
/* Close a given file descriptor/handle `fd' */
#define __NR_close                  0x39  /* errno_t close(fd_t fd) */
#define __NR_vhangup                0x3a  /* errno_t vhangup(void) */
#define __NR_pipe2                  0x3b  /* errno_t pipe2(fd_t[2] pipedes, oflag_t flags) */
#define __NR_quotactl               0x3c  /* errno_t quotactl(int TODO_PROTOTYPE) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define __NR_getdents64             0x3d  /* ssize_t getdents64(fd_t fd, struct linux_dirent64 *buf, size_t buflen) */
/* Read up to `bufsize' bytes from `fd' into `buf'
 * When  `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw `E_WOULDBLOCK' if no
 * data was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
#define __NR_read                   0x3f  /* ssize_t read(fd_t fd, void *buf, size_t bufsize) */
/* Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data as
 * possible at the time the call was made, and throw `E_WOULDBLOCK' if
 * no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
#define __NR_write                  0x40  /* ssize_t write(fd_t fd, void const *buf, size_t bufsize) */
/* Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at  the time  the call  was made,  and throw  `E_WOULDBLOCK'
 * no data was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
#define __NR_readv                  0x41  /* ssize_t readv(fd_t fd, struct iovec const *iovec, size_t count) */
/* Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When  `fd' has the  `O_NONBLOCK' flag set, only  write as much data
 * as possible at the time the call was made, and throw `E_WOULDBLOCK'
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
#define __NR_writev                 0x42  /* ssize_t writev(fd_t fd, struct iovec const *iovec, size_t count) */
#define __NR_pread64                0x43  /* ssize_t pread64(fd_t fd, void *buf, size_t bufsize, uint64_t offset) */
#define __NR_pwrite64               0x44  /* ssize_t pwrite64(fd_t fd, void const *buf, size_t bufsize, uint64_t offset) */
/* Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
#define __NR_preadv                 0x45  /* ssize_t preadv(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
/* Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
#define __NR_pwritev                0x46  /* ssize_t pwritev(fd_t fd, struct iovec const *iovec, size_t count, uint64_t offset) */
#define __NR_pselect6               0x48  /* ssize_t pselect6(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timespec const *timeout, struct sigset_with_size const *sigmask_sigset_with_size) */
#define __NR_ppoll                  0x49  /* ssize_t ppoll(struct pollfd *fds, size_t nfds, struct timespec const *timeout_ts, struct __sigset_struct const *sigmask, size_t sigsetsize) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process.
 * @param: flags: Set of `0 | SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK' */
#define __NR_signalfd4              0x4a  /* errno_t signalfd4(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR_vmsplice               0x4b  /* ssize_t vmsplice(fd_t fdout, struct iovec const *iov, size_t count, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR_splice                 0x4c  /* ssize_t splice(fd_t fdin, uint64_t *offin, fd_t fdout, uint64_t *offout, size_t length, syscall_ulong_t flags) */
/* @param: flags: Set of `SPLICE_F_MOVE | SPLICE_F_NONBLOCK | SPLICE_F_MORE | SPLICE_F_GIFT' */
#define __NR_tee                    0x4d  /* ssize_t tee(fd_t fdin, fd_t fdout, size_t length, syscall_ulong_t flags) */
#define __NR_readlinkat             0x4e  /* ssize_t readlinkat(fd_t dirfd, char const *path, char *buf, size_t buflen) */
#define __NR_sync                   0x51  /* errno_t sync(void) */
/* Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
#define __NR_fsync                  0x52  /* errno_t fsync(fd_t fd) */
/* Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
#define __NR_fdatasync              0x53  /* errno_t fdatasync(fd_t fd) */
/* @param: flags: Set of `SYNC_FILE_RANGE_WAIT_BEFORE | SYNC_FILE_RANGE_WRITE | SYNC_FILE_RANGE_WAIT_AFTER' */
#define __NR_sync_file_range        0x54  /* errno_t sync_file_range(fd_t fd, uint64_t offset, uint64_t count, syscall_ulong_t flags) */
/* Return file descriptor for new interval timer source
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
#define __NR_timerfd_create         0x55  /* fd_t timerfd_create(clockid_t clock_id, syscall_ulong_t flags) */
/* Set next expiration time of interval timer source `timerfd' to `utmr'.
 * If `flags'  has the  `TFD_TIMER_ABSTIME' flag  set the  timeout  value
 * is absolute. Optionally return the old expiration time in `otmr'
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
#define __NR_timerfd_settime        0x56  /* errno_t timerfd_settime(fd_t timerfd, syscall_ulong_t flags, struct itimerspec const *utmr, struct itimerspec *otmr) */
/* Return the next expiration time of UFD */
#define __NR_timerfd_gettime        0x57  /* errno_t timerfd_gettime(fd_t timerfd, struct itimerspec *otmr) */
/* @param: flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
#define __NR_utimensat              0x58  /* errno_t utimensat(fd_t dirfd, char const *filename, struct timespec const[2] times, atflag_t flags) */
#define __NR_acct                   0x59  /* errno_t acct(char const *filename) */
#define __NR_capget                 0x5a  /* errno_t capget(int TODO_PROTOTYPE) */
#define __NR_capset                 0x5b  /* errno_t capset(int TODO_PROTOTYPE) */
#define __NR_personality            0x5c  /* errno_t personality(int TODO_PROTOTYPE) */
/* Terminate the calling thread (_NOT_ process!)
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define __NR_exit                   0x5d  /* void exit(syscall_ulong_t exit_code) */
/* Terminate the calling process
 * @param: exit_code: Thread exit code (as returned by `wait(2)') */
#define __NR_exit_group             0x5e  /* void exit_group(syscall_ulong_t exit_code) */
/* @param: idtype:  One of `P_ALL', `P_PID', `P_PGID'
 * @param: options: At least one of `WEXITED', `WSTOPPED', `WCONTINUED', optionally or'd with `WNOHANG | WNOWAIT' */
#define __NR_waitid                 0x5f  /* errno_t waitid(syscall_ulong_t idtype, id_t id, struct __siginfo_struct *infop, syscall_ulong_t options, struct rusage *ru) */
#define __NR_set_tid_address        0x60  /* pid_t set_tid_address(pid_t *tidptr) */
/* param: what: Set of `CLONE_*' */
#define __NR_unshare                0x61  /* errno_t unshare(syscall_ulong_t what) */
/* @param: futex_op: One of `FUTEX_*' from <linux/futex.h> */
#define __NR_futex                  0x62  /* syscall_slong_t futex(uint32_t *uaddr, syscall_ulong_t futex_op, uint32_t val, struct timespec const *timeout_or_val2, uint32_t *uaddr2, uint32_t val3) */
#define __NR_set_robust_list        0x63  /* errno_t set_robust_list(int TODO_PROTOTYPE) */
#define __NR_get_robust_list        0x64  /* errno_t get_robust_list(int TODO_PROTOTYPE) */
#define __NR_nanosleep              0x65  /* errno_t nanosleep(struct timespec const *req, struct timespec *rem) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR_getitimer              0x66  /* errno_t getitimer(syscall_ulong_t which, struct itimerval *curr_value) */
/* @param: which: One of `ITIMER_REAL', `ITIMER_VIRTUAL' or `ITIMER_PROF' */
#define __NR_setitimer              0x67  /* errno_t setitimer(syscall_ulong_t which, struct itimerval const *newval, struct itimerval *oldval) */
#define __NR_kexec_load             0x68  /* errno_t kexec_load(int TODO_PROTOTYPE) */
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_BLOB'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
#define __NR_init_module            0x69  /* errno_t init_module(void const *module_image, size_t len, char const *uargs) */
/* Try to unload a driver, given its `name'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_DELMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * @param: name:  The name of the driver
 * @param: flags: Set of `O_NONBLOCK | O_TRUNC', where:
 *                - O_NONBLOCK: s.a. `KSYSCTL_DRIVER_DELMOD_FNONBLOCK'
 *                - O_TRUNC:    s.a. `KSYSCTL_DRIVER_DELMOD_FFORCE' */
#define __NR_delete_module          0x6a  /* errno_t delete_module(char const *name, oflag_t flags) */
#define __NR_timer_create           0x6b  /* errno_t timer_create(clockid_t clock_id, struct sigevent *evp, timer_t *timerid) */
#define __NR_timer_gettime          0x6c  /* errno_t timer_gettime(timer_t timerid, struct itimerspec *value) */
#define __NR_timer_getoverrun       0x6d  /* syscall_slong_t timer_getoverrun(timer_t timerid) */
/* @param: flags: Set of `0 | TIMER_ABSTIME' */
#define __NR_timer_settime          0x6e  /* errno_t timer_settime(timer_t timerid, syscall_ulong_t flags, struct itimerspec const *value, struct itimerspec *ovalue) */
#define __NR_timer_delete           0x6f  /* errno_t timer_delete(timer_t timerid) */
#define __NR_clock_settime          0x70  /* errno_t clock_settime(clockid_t clock_id, struct timespec const *tp) */
#define __NR_clock_gettime          0x71  /* errno_t clock_gettime(clockid_t clock_id, struct timespec *tp) */
#define __NR_clock_getres           0x72  /* errno_t clock_getres(clockid_t clock_id, struct timespec *res) */
/* >> clock_nanosleep(2), clock_nanosleep64(2)
 * High-resolution sleep with the specified clock
 * @param: clock_id: One of `CLOCK_REALTIME, CLOCK_TAI, CLOCK_MONOTONIC, CLOCK_BOOTTIME, CLOCK_PROCESS_CPUTIME_ID'
 *                   Other clock IDs cannot be used with this system call!
 * @param: flags:    Set of `0 | TIMER_ABSTIME' */
#define __NR_clock_nanosleep        0x73  /* errno_t clock_nanosleep(clockid_t clock_id, syscall_ulong_t flags, struct timespec const *requested_time, struct timespec *remaining) */
#define __NR_syslog                 0x74  /* ssize_t syslog(syscall_ulong_t level, char const *str, size_t len) */
#define __NR_ptrace                 0x75  /* syscall_slong_t ptrace(syscall_ulong_t request, pid_t pid, void *addr, void *data) */
#define __NR_sched_setparam         0x76  /* errno_t sched_setparam(pid_t pid, struct sched_param const *param) */
/* @param: policy: One of `SCHED_OTHER', `SCHED_FIFO', `SCHED_RR', `SCHED_BATCH',
 *                 `SCHED_IDLE',  optionally   or'd  with   `SCHED_RESET_ON_FORK' */
#define __NR_sched_setscheduler     0x77  /* errno_t sched_setscheduler(pid_t pid, syscall_ulong_t policy, struct sched_param const *param) */
#define __NR_sched_getscheduler     0x78  /* syscall_slong_t sched_getscheduler(pid_t pid) */
#define __NR_sched_getparam         0x79  /* errno_t sched_getparam(pid_t pid, struct sched_param *param) */
#define __NR_sched_setaffinity      0x7a  /* errno_t sched_setaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct const *cpuset) */
#define __NR_sched_getaffinity      0x7b  /* errno_t sched_getaffinity(pid_t pid, size_t cpusetsize, struct __cpu_set_struct *cpuset) */
#define __NR_sched_yield            0x7c  /* errno_t sched_yield(void) */
#define __NR_sched_get_priority_max 0x7d  /* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
#define __NR_sched_get_priority_min 0x7e  /* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
#define __NR_sched_rr_get_interval  0x7f  /* errno_t sched_rr_get_interval(pid_t pid, struct timespec *ts) */
#define __NR_restart_syscall        0x80  /* errno_t restart_syscall(void) */
#define __NR_kill                   0x81  /* errno_t kill(pid_t pid, signo_t signo) */
#define __NR_tkill                  0x82  /* errno_t tkill(pid_t tid, signo_t signo) */
#define __NR_tgkill                 0x83  /* errno_t tgkill(pid_t pid, pid_t tid, signo_t signo) */
#define __NR_sigaltstack            0x84  /* errno_t sigaltstack(struct sigaltstack const *ss, struct sigaltstack *oss) */
/* >> sigsuspend(2), rt_sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
#define __NR_rt_sigsuspend          0x85  /* errno_t rt_sigsuspend(struct __sigset_struct const *set, size_t sigsetsize) */
#define __NR_rt_sigaction           0x86  /* errno_t rt_sigaction(signo_t signo, struct __kernel_sigaction const *act, struct __kernel_sigaction *oact, size_t sigsetsize) */
/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
#define __NR_rt_sigprocmask         0x87  /* errno_t rt_sigprocmask(syscall_ulong_t how, struct __sigset_struct const *set, struct __sigset_struct *oset, size_t sigsetsize) */
#define __NR_rt_sigpending          0x88  /* errno_t rt_sigpending(struct __sigset_struct *set, size_t sigsetsize) */
#define __NR_rt_sigtimedwait        0x89  /* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set, struct __siginfo_struct *info, struct timespec const *timeout, size_t sigsetsize) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define __NR_rt_sigqueueinfo        0x8a  /* errno_t rt_sigqueueinfo(pid_t pid, signo_t usigno, struct __siginfo_struct const *uinfo) */
#define __NR_rt_sigreturn           0x8b  /* void rt_sigreturn(void) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define __NR_setpriority            0x8c  /* errno_t setpriority(syscall_ulong_t which, id_t who, syscall_ulong_t value) */
/* @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER' */
#define __NR_getpriority            0x8d  /* syscall_slong_t getpriority(syscall_ulong_t which, id_t who) */
/* @param: how: One of the `RB_*' constants from <sys/reboot.h> */
#define __NR_reboot                 0x8e  /* errno_t reboot(syscall_ulong_t how) */
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR_setregid               0x8f  /* errno_t setregid(gid_t rgid, gid_t egid) */
/* >> setgid(2)
 * Set the GID of the calling thread (this is the so-called ~real~ GID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR_setgid                 0x90  /* errno_t setgid(gid_t gid) */
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR_setreuid               0x91  /* errno_t setreuid(uid_t ruid, uid_t euid) */
/* >> setuid(2)
 * Set the UID of the calling thread (this is the so-called ~real~ UID)
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR_setuid                 0x92  /* errno_t setuid(uid_t uid) */
/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR_setresuid              0x93  /* errno_t setresuid(uid_t ruid, uid_t euid, uid_t suid) */
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success */
#define __NR_getresuid              0x94  /* errno_t getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) */
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR_setresgid              0x95  /* errno_t setresgid(gid_t rgid, gid_t egid, gid_t sgid) */
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success */
#define __NR_getresgid              0x96  /* errno_t getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) */
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETUID: [...] */
#define __NR_setfsuid               0x97  /* errno_t setfsuid(uid_t uid) */
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @throw: E_INSUFFICIENT_RIGHTS:CAP_SETGID: [...] */
#define __NR_setfsgid               0x98  /* errno_t setfsgid(gid_t gid) */
#define __NR_times                  0x99  /* clock_t times(struct tms *buf) */
#define __NR_setpgid                0x9a  /* errno_t setpgid(pid_t pid, pid_t pgid) */
#define __NR_getpgid                0x9b  /* pid_t getpgid(pid_t pid) */
#define __NR_getsid                 0x9c  /* pid_t getsid(pid_t pid) */
#define __NR_setsid                 0x9d  /* pid_t setsid(void) */
/* @return: * :     [count == 0] The required number of groups
 * @return: * :     [count != 0] The number of groups that were actually returned
 * @throw: -EINVAL: [count != 0] There are more than `count' groups (NOTE: No exception is thrown for this case!) */
#define __NR_getgroups              0x9e  /* ssize_t getgroups(size_t count, gid_t[] list) */
#define __NR_setgroups              0x9f  /* errno_t setgroups(size_t count, gid_t const *groups) */
#define __NR_uname                  0xa0  /* errno_t uname(struct utsname *name) */
#define __NR_sethostname            0xa1  /* errno_t sethostname(char const *name, size_t len) */
#define __NR_setdomainname          0xa2  /* errno_t setdomainname(char const *name, size_t len) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR_getrlimit              0xa3  /* errno_t getrlimit(syscall_ulong_t resource, struct rlimit *rlimits) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR_setrlimit              0xa4  /* errno_t setrlimit(syscall_ulong_t resource, struct rlimit const *rlimits) */
/* @param: who: One of `RUSAGE_SELF', `RUSAGE_CHILDREN' or `RUSAGE_THREAD' */
#define __NR_getrusage              0xa5  /* errno_t getrusage(syscall_slong_t who, struct rusage *usage) */
#define __NR_umask                  0xa6  /* mode_t umask(mode_t mode) */
/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... : Up  to 4 additional arguments (dependent on `command')
 *               Note that some control codes  require you to pass  `0'
 *               for  all seemingly "unused" arguments. In these cases,
 *               the documentation for that command includes the number
 *               of unused, but required trailing 0s in its comment.
 * @return: * :  Return value depends on `command' */
#define __NR_prctl                  0xa7  /* syscall_slong_t prctl(unsigned int command, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5) */
#define __NR_getcpu                 0xa8  /* errno_t getcpu(uint32_t *cpu, uint32_t *node, struct getcpu_cache *tcache) */
#define __NR_gettimeofday           0xa9  /* errno_t gettimeofday(struct timeval *tv, struct timezone *tz) */
#define __NR_settimeofday           0xaa  /* errno_t settimeofday(struct timeval const *tv, struct timezone const *tz) */
#define __NR_adjtimex               0xab  /* errno_t adjtimex(struct timex *ntx) */
#define __NR_getpid                 0xac  /* pid_t getpid(void) */
#define __NR_getppid                0xad  /* pid_t getppid(void) */
/* >> getuid(2)
 * @return: * : The UID of the calling thread (this is the so-called ~real~ UID) */
#define __NR_getuid                 0xae  /* uid_t getuid(void) */
/* >> geteuid(2)
 * @return: * : The   effective  UID  of  the  calling  thread.
 *              This is the one used for most permission checks */
#define __NR_geteuid                0xaf  /* uid_t geteuid(void) */
/* >> getgid(2)
 * @return: * : The GID of the calling thread (this is the so-called ~real~ GID) */
#define __NR_getgid                 0xb0  /* gid_t getgid(void) */
/* >> getegid(2)
 * @return: * : The   effective  GID  of  the  calling  thread.
 *              This is the one used for most permission checks */
#define __NR_getegid                0xb1  /* gid_t getegid(void) */
#define __NR_gettid                 0xb2  /* pid_t gettid(void) */
#define __NR_sysinfo                0xb3  /* errno_t sysinfo(struct sysinfo *info) */
#define __NR_mq_open                0xb4  /* fd_t mq_open(char const *name, oflag_t oflags, mode_t mode) */
#define __NR_mq_unlink              0xb5  /* errno_t mq_unlink(char const *name) */
#define __NR_mq_timedsend           0xb6  /* errno_t mq_timedsend(fd_t mqdes, char const *msg_ptr, size_t msg_len, uint32_t msg_prio, struct timespec const *abs_timeout) */
#define __NR_mq_timedreceive        0xb7  /* ssize_t mq_timedreceive(fd_t mqdes, char *msg_ptr, size_t msg_len, uint32_t *pmsg_prio, struct timespec const *abs_timeout) */
#define __NR_mq_notify              0xb8  /* errno_t mq_notify(fd_t mqdes, struct sigevent const *notification) */
#define __NR_mq_getsetattr          0xb9  /* errno_t mq_getsetattr(fd_t mqdes, struct mq_attr const *newattr, struct mq_attr *oldattr) */
#define __NR_msgget                 0xba  /* errno_t msgget(int TODO_PROTOTYPE) */
#define __NR_msgctl                 0xbb  /* errno_t msgctl(int TODO_PROTOTYPE) */
#define __NR_msgrcv                 0xbc  /* errno_t msgrcv(int TODO_PROTOTYPE) */
#define __NR_msgsnd                 0xbd  /* errno_t msgsnd(int TODO_PROTOTYPE) */
#define __NR_semget                 0xbe  /* errno_t semget(int TODO_PROTOTYPE) */
#define __NR_semctl                 0xbf  /* errno_t semctl(int TODO_PROTOTYPE) */
#define __NR_semtimedop             0xc0  /* errno_t semtimedop(int TODO_PROTOTYPE) */
#define __NR_semop                  0xc1  /* errno_t semop(int TODO_PROTOTYPE) */
#define __NR_shmget                 0xc2  /* errno_t shmget(key_t key, size_t size, syscall_ulong_t shmflg) */
#define __NR_shmctl                 0xc3  /* errno_t shmctl(syscall_ulong_t shmid, syscall_ulong_t cmd, struct shmid_ds *buf) */
#define __NR_shmat                  0xc4  /* errno_t shmat(syscall_ulong_t shmid, void const *shmaddr, syscall_ulong_t shmflg) */
#define __NR_shmdt                  0xc5  /* errno_t shmdt(void const *shmaddr) */
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
#define __NR_socket                 0xc6  /* fd_t socket(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol) */
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
#define __NR_socketpair             0xc7  /* errno_t socketpair(syscall_ulong_t domain, syscall_ulong_t type, syscall_ulong_t protocol, fd_t[2] fds) */
/* Bind the given socket `sockfd' to the specified local address.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_BIND_WRONG_ADDRESS_FAMILY
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_BIND_ALREADY_BOUND
 * @throw: E_NET_ADDRESS_NOT_AVAILABLE
 * @throw: E_BUFFER_TOO_SMALL   (`addr_len' is incorrect)
 * @return: 0 : Success */
#define __NR_bind                   0xc8  /* errno_t bind(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
/* Begin to listen for incoming client (aka. peer) connection requests.
 * @param: max_backlog: The max number of clients  pending to be accept(2)-ed,  before
 *                      the kernel will refuse to enqueue additional clients, and will
 *                      instead automatically refuse  any further  requests until  the
 *                      less than `max_backlog' clients are still pending.
 * @throw: E_NET_ADDRESS_IN_USE:E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN
 * @throw: E_INVALID_HANDLE_NET_OPERATION:E_NET_OPERATION_LISTEN
 * @return: 0 : Success */
#define __NR_listen                 0xc9  /* errno_t listen(fd_t sockfd, syscall_ulong_t max_backlog) */
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
#define __NR_accept                 0xca  /* fd_t accept(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
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
#define __NR_connect                0xcb  /* errno_t connect(fd_t sockfd, struct sockaddr const *addr, socklen_t addr_len) */
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
#define __NR_getsockname            0xcc  /* errno_t getsockname(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
/* Lookup the peer (remote) address of `sockfd' and store it in `*addr...+=*addr_len'
 * @param: addr:     [out] Buffer where to store the sock address.
 * @param: addr_len: [in]  The amount of available memory starting at `addr'
 *                   [out] The amount of required memory for the address.
 *                         This may be more than was given, in which case
 *                         the  address was truncated and may be invalid.
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_GETPEERNAME_NOT_CONNECTED
 * @return: 0 : Success */
#define __NR_getpeername            0xcd  /* errno_t getpeername(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len) */
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
#define __NR_sendto                 0xce  /* ssize_t sendto(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr const *addr, socklen_t addr_len) */
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
#define __NR_recvfrom               0xcf  /* ssize_t recvfrom(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags, struct sockaddr *addr, socklen_t *addr_len) */
/* Set the value of the named socket option `level:optname' from what is given in `optval'
 * @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level'
 * @param: optval:  Buffer for where to write the value of the socket option.
 * @param: optlen:  The amount of available memory starting at `optval'
 * @throw: E_INVALID_ARGUMENT_SOCKET_OPT:E_INVALID_ARGUMENT_CONTEXT_SETSOCKOPT
 * @throw: E_BUFFER_TOO_SMALL  (The specified `optlen' is invalid for the given option)
 * @return: 0 : Success */
#define __NR_setsockopt             0xd0  /* errno_t setsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void const *optval, socklen_t optlen) */
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
#define __NR_getsockopt             0xd1  /* errno_t getsockopt(fd_t sockfd, syscall_ulong_t level, syscall_ulong_t optname, void *optval, socklen_t *optlen) */
/* Disallow further reception of data (causing `recv(2)' to return `0' as soon
 * as  all currently queued  data has been  read), and/or further transmission
 * of data (causing `send(2)' to throw an `E_NET_SHUTDOWN' exception)
 * @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SHUTDOWN_NOT_CONNECTED
 * @return: 0 : Success */
#define __NR_shutdown               0xd2  /* errno_t shutdown(fd_t sockfd, syscall_ulong_t how) */
/* Same as `send(2)' and `sendto(2)', but also allows for sending ancillary
 * data as well as  for data buffers  to be represented  by an IOV  vector.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as for `send(2)' and `sendto(2)'
 * @return: * : [<= bufsize] The actual # of send payload bytes */
#define __NR_sendmsg                0xd3  /* ssize_t sendmsg(fd_t sockfd, struct msghdr const *message, syscall_ulong_t msg_flags) */
/* Same as `recv(2)' and `recvfrom(2)', but also allows for receiving ancillary
 * data as  well as  for  data buffers  to be  represented  by an  IOV  vector.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC  |  MSG_WAITALL'
 * @throw: ... Same as for `recv(2)' and `recvfrom(2)'
 * @return: * : [<= bufsize] The actual # of received payload bytes */
#define __NR_recvmsg                0xd4  /* ssize_t recvmsg(fd_t sockfd, struct msghdr *message, syscall_ulong_t msg_flags) */
#define __NR_readahead              0xd5  /* ssize_t readahead(fd_t fd, uint64_t offset, size_t count) */
#define __NR_brk                    0xd6  /* errno_t brk(void *addr) */
#define __NR_munmap                 0xd7  /* errno_t munmap(void *addr, size_t len) */
/* @param: flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
#define __NR_mremap                 0xd8  /* void *mremap(void *addr, size_t old_len, size_t new_len, syscall_ulong_t flags, void *new_address) */
#define __NR_add_key                0xd9  /* errno_t add_key(int TODO_PROTOTYPE) */
#define __NR_request_key            0xda  /* errno_t request_key(int TODO_PROTOTYPE) */
#define __NR_keyctl                 0xdb  /* errno_t keyctl(int TODO_PROTOTYPE) */
#define __NR_clone                  0xdc  /* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, uintptr_t newtls, pid_t *ctid) */
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
#define __NR_execve                 0xdd  /* errno_t execve(char const *path, char const *const *argv, char const *const *envp) */
/* @param: swapflags: Set of `SWAP_FLAG_*' */
#define __NR_swapon                 0xe0  /* errno_t swapon(char const *pathname, syscall_ulong_t swapflags) */
#define __NR_swapoff                0xe1  /* errno_t swapoff(char const *pathname) */
/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED' */
#define __NR_mprotect               0xe2  /* errno_t mprotect(void *addr, size_t len, syscall_ulong_t prot) */
#define __NR_msync                  0xe3  /* errno_t msync(void *addr, size_t len, syscall_ulong_t flags) */
#define __NR_mlock                  0xe4  /* errno_t mlock(void const *addr, size_t len) */
#define __NR_munlock                0xe5  /* errno_t munlock(void const *addr, size_t len) */
/* @param: flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
#define __NR_mlockall               0xe6  /* errno_t mlockall(syscall_ulong_t flags) */
#define __NR_munlockall             0xe7  /* errno_t munlockall(void) */
#define __NR_mincore                0xe8  /* errno_t mincore(void *start, size_t len, uint8_t *vec) */
#define __NR_madvise                0xe9  /* errno_t madvise(void *addr, size_t len, syscall_ulong_t advice) */
#define __NR_remap_file_pages       0xea  /* errno_t remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
#define __NR_mbind                  0xeb  /* errno_t mbind(int TODO_PROTOTYPE) */
#define __NR_get_mempolicy          0xec  /* errno_t get_mempolicy(int TODO_PROTOTYPE) */
#define __NR_set_mempolicy          0xed  /* errno_t set_mempolicy(int TODO_PROTOTYPE) */
#define __NR_migrate_pages          0xee  /* errno_t migrate_pages(int TODO_PROTOTYPE) */
#define __NR_move_pages             0xef  /* errno_t move_pages(int TODO_PROTOTYPE) */
/* @param: usigno: The signal that should be sent
 * @param: uinfo:  [0..1] Additional signal information
 * @throw: E_INVALID_ARGUMENT_UNEXPECTED_COMMAND:E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO: [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO:              [...]
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE:  [...]
 * @throw: E_ILLEGAL_OPERATION:                                                            [...] */
#define __NR_rt_tgsigqueueinfo      0xf0  /* errno_t rt_tgsigqueueinfo(pid_t pid, pid_t tid, signo_t usigno, struct __siginfo_struct const *uinfo) */
#define __NR_perf_event_open        0xf1  /* errno_t perf_event_open(int TODO_PROTOTYPE) */
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
#define __NR_accept4                0xf2  /* fd_t accept4(fd_t sockfd, struct sockaddr *addr, socklen_t *addr_len, syscall_ulong_t sock_flags) */
/* Same as `recvmsg(2)', but may be used to receive many
 * messages  (datagrams)  with  a  single  system  call.
 * @param: msg_flags: Set of `MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK |
 *                            MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK  |  MSG_TRUNC |  MSG_WAITALL |
 *                            MSG_WAITFORONE'
 * @throw: Error (s.a. `recvmsg(2)')
 * @return: * : The # of datagrams successfully received. */
#define __NR_recvmmsg               0xf3  /* ssize_t recvmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags, struct timespec const *tmo) */
/* Same as `waitpid(pid, STAT_LOC, OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
#define __NR_wait4                  0x104 /* pid_t wait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
/* @param: resource: One of `RLIMIT_*' from <sys/resource.h> */
#define __NR_prlimit64              0x105 /* errno_t prlimit64(pid_t pid, syscall_ulong_t resource, struct rlimit64 const *new_limit, struct rlimit64 *old_limit) */
#define __NR_fanotify_init          0x106 /* errno_t fanotify_init(int TODO_PROTOTYPE) */
#define __NR_fanotify_mark          0x107 /* errno_t fanotify_mark(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH' */
#define __NR_name_to_handle_at      0x108 /* errno_t name_to_handle_at(fd_t dirfd, char const *filename, struct file_handle *handle, int32_t *mnt_id, atflag_t flags) */
#define __NR_open_by_handle_at      0x109 /* fd_t open_by_handle_at(fd_t mountdirfd, struct file_handle const *handle, oflag_t flags) */
#define __NR_clock_adjtime          0x10a /* errno_t clock_adjtime(int TODO_PROTOTYPE) */
#define __NR_syncfs                 0x10b /* errno_t syncfs(fd_t fd) */
#define __NR_setns                  0x10c /* errno_t setns(fd_t fd, syscall_ulong_t nstype) */
/* Same as `sendmsg(2)', but may be used to send many
 * messages (datagrams)  with a  single system  call.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: ... Same as `sendmsg(2)'
 * @return: * : The # of datagrams successfully sent. */
#define __NR_sendmmsg               0x10d /* ssize_t sendmmsg(fd_t sockfd, struct mmsghdr *vmessages, size_t vlen, syscall_ulong_t msg_flags) */
/* Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
#define __NR_process_vm_readv       0x10e /* ssize_t process_vm_readv(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
#define __NR_process_vm_writev      0x10f /* ssize_t process_vm_writev(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags) */
/* @param: type: One of  `KCMP_FILE',  `KCMP_FILES',  `KCMP_FS',  `KCMP_IO',
 *               `KCMP_SIGHAND', `KCMP_SYSVSEM', `KCMP_VM', `KCMP_EPOLL_TFD' */
#define __NR_kcmp                   0x110 /* syscall_slong_t kcmp(pid_t pid1, pid_t pid2, syscall_ulong_t type, syscall_ulong_t idx1, syscall_ulong_t idx2) */
/* Load a  kernel  driver  from an  ELF  image  `module_image...+=len'
 * This system call exists for linux compatibility, and is implemented
 * as an alias for  `KSYSCTL_DRIVER_INSMOD:KSYSCTL_DRIVER_FORMAT_FILE'
 * 
 * Note however that that is where linux compatibility ends. Since the
 * linux kernel does not implement any semblance of a stable ABI,  you
 * have to realize that on KOS, this system call can only load drivers
 * specifically built to run within the KOS kernel!
 * @param: uargs: The driver commandline */
#define __NR_finit_module           0x111 /* errno_t finit_module(fd_t fd, char const *uargs, syscall_ulong_t flags) */
#define __NR_sched_setattr          0x112 /* errno_t sched_setattr(int TODO_PROTOTYPE) */
#define __NR_sched_getattr          0x113 /* errno_t sched_getattr(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE | AT_RENAME_WHITEOUT | AT_RENAME_MOVETODIR | AT_DOSPATH' */
#define __NR_renameat2              0x114 /* errno_t renameat2(fd_t olddirfd, char const *oldpath, fd_t newdirfd, char const *newpath, atflag_t flags) */
#define __NR_seccomp                0x115 /* errno_t seccomp(int TODO_PROTOTYPE) */
/* @param: flags: Set of `0 | GRND_RANDOM | GRND_NONBLOCK' */
#define __NR_getrandom              0x116 /* ssize_t getrandom(void *buf, size_t num_bytes, syscall_ulong_t flags) */
/* @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
#define __NR_memfd_create           0x117 /* fd_t memfd_create(char const *name, syscall_ulong_t flags) */
#define __NR_bpf                    0x118 /* errno_t bpf(int TODO_PROTOTYPE) */
/* Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
 * @param: flags: Set of `0 | AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
#define __NR_execveat               0x119 /* errno_t execveat(fd_t dirfd, char const *pathname, char const *const *argv, char const *const *envp, atflag_t flags) */
#define __NR_userfaultfd            0x11a /* fd_t userfaultfd(syscall_ulong_t flags) */
#define __NR_membarrier             0x11b /* errno_t membarrier(int TODO_PROTOTYPE) */
#define __NR_mlock2                 0x11c /* errno_t mlock2(void const *addr, size_t length, syscall_ulong_t flags) */
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
#define __NR_open                   0x400 /* fd_t open(char const *filename, oflag_t oflags, mode_t mode) */
#define __NR_link                   0x401 /* errno_t link(char const *existing_file, char const *link_file) */
#define __NR_unlink                 0x402 /* errno_t unlink(char const *filename) */
#define __NR_mknod                  0x403 /* errno_t mknod(char const *nodename, mode_t mode, dev_t dev) */
#define __NR_chmod                  0x404 /* errno_t chmod(char const *filename, mode_t mode) */
#define __NR_chown                  0x405 /* errno_t chown(char const *filename, uid_t owner, gid_t group) */
#define __NR_mkdir                  0x406 /* errno_t mkdir(char const *pathname, mode_t mode) */
#define __NR_rmdir                  0x407 /* errno_t rmdir(char const *path) */
#define __NR_lchown                 0x408 /* errno_t lchown(char const *filename, uid_t owner, gid_t group) */
/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
#define __NR_access                 0x409 /* errno_t access(char const *filename, syscall_ulong_t type) */
#define __NR_rename                 0x40a /* errno_t rename(char const *oldname, char const *newname_or_path) */
#define __NR_readlink               0x40b /* ssize_t readlink(char const *path, char *buf, size_t buflen) */
#define __NR_symlink                0x40c /* errno_t symlink(char const *link_text, char const *target_path) */
/* @param: times:    When NULL, set the current time
 * @param: times[0]: New access time
 * @param: times[1]: New last-modified time */
#define __NR_utimes                 0x40d /* errno_t utimes(char const *filename, struct timeval const[2] times) */
#define __NR_pipe                   0x410 /* errno_t pipe(fd_t[2] pipedes) */
#define __NR_dup2                   0x411 /* fd_t dup2(fd_t oldfd, fd_t newfd) */
/* >> epoll_create(2)
 * Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
 * @return: * : The newly created epoll control descriptor.
 * @return: -1: Error (s.a. `errno') */
#define __NR_epoll_create           0x412 /* fd_t epoll_create(syscall_ulong_t size) */
#define __NR_inotify_init           0x413 /* fd_t inotify_init(void) */
#define __NR_eventfd                0x414 /* fd_t eventfd(syscall_ulong_t initval) */
/* Create a poll(2)-able file descriptor which can be used to wait for the
 * delivery of signals masked by `sigmask' to the waiting  thread/process. */
#define __NR_signalfd               0x415 /* errno_t signalfd(fd_t fd, struct __sigset_struct const *sigmask, size_t sigmasksize) */
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
#define __NR_sendfile               0x416 /* ssize_t sendfile(fd_t outfd, fd_t infd, syscall_ulong_t *pin_offset, size_t num_bytes) */
#define __NR_ftruncate              0x417 /* errno_t ftruncate(fd_t fd, syscall_ulong_t length) */
#define __NR_truncate               0x418 /* errno_t truncate(char const *filename, syscall_ulong_t length) */
#define __NR_stat                   0x419 /* errno_t stat(char const *filename, struct linux_stat *statbuf) */
#define __NR_lstat                  0x41a /* errno_t lstat(char const *filename, struct linux_stat *statbuf) */
#define __NR_fstat                  0x41b /* errno_t fstat(fd_t fd, struct linux_stat *statbuf) */
#define __NR_fcntl                  0x41c /* syscall_slong_t fcntl(fd_t fd, fcntl_t command, void *arg) */
#define __NR_fadvise64              0x41d /* errno_t fadvise64(int TODO_PROTOTYPE) */
#define __NR_newfstatat             0x41e /* errno_t newfstatat(fd_t dirfd, char const *filename, struct linux64_stat32 *statbuf, atflag_t flags) */
#define __NR_fstatfs                0x41f /* errno_t fstatfs(fd_t file, struct statfs *buf) */
#define __NR_statfs                 0x420 /* errno_t statfs(char const *file, struct statfs *buf) */
#define __NR_lseek                  0x421 /* syscall_slong_t lseek(fd_t fd, syscall_slong_t offset, syscall_ulong_t whence) */
/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param: flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with  a  set of  `MAP_ANONYMOUS  | MAP_FIXED  |  MAP_GROWSDOWN |  MAP_LOCKED |
 *               MAP_NONBLOCK  |  MAP_NORESERVE  |  MAP_POPULATE  |  MAP_STACK  |  MAP_SYNC   |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE | MAP_OFFSET64_POINTER' */
#define __NR_mmap                   0x422 /* void *mmap(void *addr, size_t len, syscall_ulong_t prot, syscall_ulong_t flags, fd_t fd, syscall_ulong_t offset) */
#define __NR_alarm                  0x423 /* syscall_ulong_t alarm(syscall_ulong_t seconds) */
#define __NR_getpgrp                0x424 /* pid_t getpgrp(void) */
/* Same as `select(0, NULL, NULL, NULL, NULL)' */
#define __NR_pause                  0x425 /* errno_t pause(void) */
#define __NR_time                   0x426 /* time32_t time(time32_t *timer) */
/* @param: times: When NULL, set the current time */
#define __NR_utime                  0x427 /* errno_t utime(char const *filename, struct utimbuf const *times) */
#define __NR_creat                  0x428 /* fd_t creat(char const *filename, mode_t mode) */
/* @return: * : The actual number of read entries
 * @return: 0 : End-of-directory */
#define __NR_getdents               0x429 /* ssize_t getdents(fd_t fd, struct linux_dirent *buf, size_t buflen) */
#define __NR_futimesat              0x42a /* errno_t futimesat(fd_t dirfd, char const *filename, struct timeval const[2] times) */
#define __NR_select                 0x42b /* ssize_t select(size_t nfds, struct __fd_set_struct *readfds, struct __fd_set_struct *writefds, struct __fd_set_struct *exceptfds, struct timeval *timeout) */
#define __NR_poll                   0x42c /* ssize_t poll(struct pollfd *fds, size_t nfds, syscall_slong_t timeout) */
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
#define __NR_epoll_wait             0x42d /* ssize_t epoll_wait(fd_t epfd, struct epoll_event *events, size_t maxevents, syscall_slong_t timeout) */
#define __NR_ustat                  0x42e /* errno_t ustat(dev_t dev, struct ustat *ubuf) */
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
#define __NR_vfork                  0x42f /* pid_t vfork(void) */
/* @param: options: Set of `WNOHANG | WUNTRACED | WCONTINUED' */
#define __NR_oldwait4               0x430 /* pid_t oldwait4(pid_t pid, int32_t *stat_loc, syscall_ulong_t options, struct rusage *usage) */
/* Receive data over the given socket `sockfd', and store the contents within the given buffer.
 * @param: msg_flags: Set of `MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB |
 *                            MSG_PEEK | MSG_TRUNC | MSG_WAITALL'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_RECV_NOT_CONNECTED
 * @throw: E_NET_CONNECTION_REFUSED
 * @return: * : [<= bufsize] The actual # of received bytes */
#define __NR_recv                   0x431 /* ssize_t recv(fd_t sockfd, void *buf, size_t bufsize, syscall_ulong_t msg_flags) */
/* Send the contents of a given buffer over the given socket `sockfd'.
 * @param: msg_flags: Set of `MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT |
 *                            MSG_EOR | MSG_MORE | MSG_NOSIGNAL | MSG_OOB'
 * @throw: E_ILLEGAL_BECAUSE_NOT_READY:E_ILLEGAL_OPERATION_CONTEXT_SOCKET_SEND_NOT_CONNECTED
 * @throw: E_NET_MESSAGE_TOO_LONG
 * @throw: E_NET_CONNECTION_RESET
 * @throw: E_NET_SHUTDOWN
 * @return: * : [<= bufsize] The actual # of send bytes */
#define __NR_send                   0x432 /* ssize_t send(fd_t sockfd, void const *buf, size_t bufsize, syscall_ulong_t msg_flags) */
#define __NR_bdflush                0x433 /* errno_t bdflush(int TODO_PROTOTYPE) */
#define __NR_umount                 0x434 /* errno_t umount(char const *special_file) */
#define __NR_uselib                 0x435 /* errno_t uselib(char const *library) */
#define __NR__sysctl                0x436 /* errno_t _sysctl(int TODO_PROTOTYPE) */
/* Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
#define __NR_fork                   0x437 /* pid_t fork(void) */


/************************************************************************/
/* SYSCALL LIMITS                                                       */
/************************************************************************/
#define __NRFEAT_SYSCALL_TABLE_COUNT 1
#define __NRFEAT_SYSCALL_TABLE_FOREACH(callback) \
	callback(0) 
#define __NR_syscall0_min 0x0
#define __NR_syscall0_max 0x437
#define __NR_syscall0_cnt 0x438
#endif /* !__NR_io_setup */


/************************************************************************/
/* SYSCALL RESTART MODES                                                */
/************************************************************************/
#ifdef __WANT_SYSCALL_RESTART_MODES
#ifndef __NRFEAT_DEFINED_SYSCALL_RESTART_MODES
#define __NRFEAT_DEFINED_SYSCALL_RESTART_MODES
/* Restart modes:
 * 0 (auto):
 *   - Restart only if `SA_RESTART' / `RPC_SYSRESTART_F_AUTO' is set
 * 1 (dont):
 *   - Never restart; always return -EINTR or propagate E_INTERRUPT
 * 2 (must):
 *   - Always restart, after return from a signal handler
 * Interaction with `SA_RESTART' / `RPC_SYSRESTART_F_AUTO':
 *  - auto + ~SA_RESTART: No
 *  - auto + SA_RESTART:  Yes
 *  - dont + ~SA_RESTART: No
 *  - dont + SA_RESTART:  No
 *  - must + ~SA_RESTART: Yes
 *  - must + SA_RESTART:  Yes
 */
#define __NRRM_io_setup               0
#define __NRRM_io_destroy             0
#define __NRRM_io_submit              0
#define __NRRM_io_cancel              0
#define __NRRM_io_getevents           1
#define __NRRM_setxattr               0
#define __NRRM_lsetxattr              0
#define __NRRM_fsetxattr              0
#define __NRRM_getxattr               0
#define __NRRM_lgetxattr              0
#define __NRRM_fgetxattr              0
#define __NRRM_listxattr              0
#define __NRRM_llistxattr             0
#define __NRRM_flistxattr             0
#define __NRRM_removexattr            0
#define __NRRM_lremovexattr           0
#define __NRRM_fremovexattr           0
#define __NRRM_getcwd                 0
#define __NRRM_lookup_dcookie         0
#define __NRRM_eventfd2               0
#define __NRRM_epoll_create1          0
#define __NRRM_epoll_ctl              0
#define __NRRM_epoll_pwait            1
#define __NRRM_dup                    0
#define __NRRM_dup3                   0
#define __NRRM_inotify_init1          0
#define __NRRM_inotify_add_watch      0
#define __NRRM_inotify_rm_watch       0
#define __NRRM_ioctl                  0
#define __NRRM_ioprio_set             0
#define __NRRM_ioprio_get             0
#define __NRRM_flock                  0
#define __NRRM_mknodat                0
#define __NRRM_mkdirat                0
#define __NRRM_unlinkat               0
#define __NRRM_symlinkat              0
#define __NRRM_linkat                 0
#define __NRRM_renameat               0
#define __NRRM_umount2                2
#define __NRRM_mount                  0
#define __NRRM_pivot_root             0
#define __NRRM_nfsservctl             0
#define __NRRM_fallocate              0
#define __NRRM_faccessat              0
#define __NRRM_chdir                  0
#define __NRRM_fchdir                 0
#define __NRRM_chroot                 0
#define __NRRM_fchmod                 0
#define __NRRM_fchmodat               0
#define __NRRM_fchownat               0
#define __NRRM_fchown                 0
#define __NRRM_openat                 0
#define __NRRM_close                  2
#define __NRRM_vhangup                0
#define __NRRM_pipe2                  0
#define __NRRM_quotactl               0
#define __NRRM_getdents64             0
#define __NRRM_read                   0
#define __NRRM_write                  0
#define __NRRM_readv                  0
#define __NRRM_writev                 0
#define __NRRM_pread64                0
#define __NRRM_pwrite64               0
#define __NRRM_preadv                 0
#define __NRRM_pwritev                0
#define __NRRM_pselect6               1
#define __NRRM_ppoll                  1
#define __NRRM_signalfd4              0
#define __NRRM_vmsplice               0
#define __NRRM_splice                 0
#define __NRRM_tee                    0
#define __NRRM_readlinkat             0
#define __NRRM_sync                   0
#define __NRRM_fsync                  0
#define __NRRM_fdatasync              0
#define __NRRM_sync_file_range        0
#define __NRRM_timerfd_create         0
#define __NRRM_timerfd_settime        0
#define __NRRM_timerfd_gettime        0
#define __NRRM_utimensat              0
#define __NRRM_acct                   0
#define __NRRM_capget                 0
#define __NRRM_capset                 0
#define __NRRM_personality            0
#define __NRRM_exit                   2
#define __NRRM_exit_group             2
#define __NRRM_waitid                 1
#define __NRRM_set_tid_address        2
#define __NRRM_unshare                0
#define __NRRM_futex                  0
#define __NRRM_set_robust_list        0
#define __NRRM_get_robust_list        0
#define __NRRM_nanosleep              1
#define __NRRM_getitimer              0
#define __NRRM_setitimer              0
#define __NRRM_kexec_load             0
#define __NRRM_init_module            0
#define __NRRM_delete_module          0
#define __NRRM_timer_create           0
#define __NRRM_timer_gettime          0
#define __NRRM_timer_getoverrun       0
#define __NRRM_timer_settime          0
#define __NRRM_timer_delete           0
#define __NRRM_clock_settime          0
#define __NRRM_clock_gettime          0
#define __NRRM_clock_getres           0
#define __NRRM_clock_nanosleep        1
#define __NRRM_syslog                 2
#define __NRRM_ptrace                 0
#define __NRRM_sched_setparam         0
#define __NRRM_sched_setscheduler     0
#define __NRRM_sched_getscheduler     0
#define __NRRM_sched_getparam         0
#define __NRRM_sched_setaffinity      0
#define __NRRM_sched_getaffinity      0
#define __NRRM_sched_yield            1
#define __NRRM_sched_get_priority_max 0
#define __NRRM_sched_get_priority_min 0
#define __NRRM_sched_rr_get_interval  0
#define __NRRM_restart_syscall        0
#define __NRRM_kill                   0
#define __NRRM_tkill                  0
#define __NRRM_tgkill                 0
#define __NRRM_sigaltstack            0
#define __NRRM_rt_sigsuspend          1
#define __NRRM_rt_sigaction           0
#define __NRRM_rt_sigprocmask         0
#define __NRRM_rt_sigpending          0
#define __NRRM_rt_sigtimedwait        1
#define __NRRM_rt_sigqueueinfo        0
#define __NRRM_rt_sigreturn           2
#define __NRRM_setpriority            0
#define __NRRM_getpriority            0
#define __NRRM_reboot                 0
#define __NRRM_setregid               2
#define __NRRM_setgid                 2
#define __NRRM_setreuid               2
#define __NRRM_setuid                 2
#define __NRRM_setresuid              2
#define __NRRM_getresuid              2
#define __NRRM_setresgid              2
#define __NRRM_getresgid              2
#define __NRRM_setfsuid               2
#define __NRRM_setfsgid               2
#define __NRRM_times                  0
#define __NRRM_setpgid                2
#define __NRRM_getpgid                2
#define __NRRM_getsid                 2
#define __NRRM_setsid                 2
#define __NRRM_getgroups              2
#define __NRRM_setgroups              2
#define __NRRM_uname                  0
#define __NRRM_sethostname            0
#define __NRRM_setdomainname          0
#define __NRRM_getrlimit              0
#define __NRRM_setrlimit              0
#define __NRRM_getrusage              0
#define __NRRM_umask                  2
#define __NRRM_prctl                  0
#define __NRRM_getcpu                 0
#define __NRRM_gettimeofday           0
#define __NRRM_settimeofday           0
#define __NRRM_adjtimex               0
#define __NRRM_getpid                 2
#define __NRRM_getppid                2
#define __NRRM_getuid                 2
#define __NRRM_geteuid                2
#define __NRRM_getgid                 2
#define __NRRM_getegid                2
#define __NRRM_gettid                 2
#define __NRRM_sysinfo                0
#define __NRRM_mq_open                0
#define __NRRM_mq_unlink              0
#define __NRRM_mq_timedsend           0
#define __NRRM_mq_timedreceive        0
#define __NRRM_mq_notify              0
#define __NRRM_mq_getsetattr          0
#define __NRRM_msgget                 0
#define __NRRM_msgctl                 0
#define __NRRM_msgrcv                 1
#define __NRRM_msgsnd                 1
#define __NRRM_semget                 0
#define __NRRM_semctl                 0
#define __NRRM_semtimedop             1
#define __NRRM_semop                  1
#define __NRRM_shmget                 0
#define __NRRM_shmctl                 0
#define __NRRM_shmat                  0
#define __NRRM_shmdt                  0
#define __NRRM_socket                 0
#define __NRRM_socketpair             0
#define __NRRM_bind                   0
#define __NRRM_listen                 0
#define __NRRM_accept                 1
#define __NRRM_connect                1
#define __NRRM_getsockname            0
#define __NRRM_getpeername            0
#define __NRRM_sendto                 1
#define __NRRM_recvfrom               1
#define __NRRM_setsockopt             1
#define __NRRM_getsockopt             0
#define __NRRM_shutdown               0
#define __NRRM_sendmsg                1
#define __NRRM_recvmsg                1
#define __NRRM_readahead              0
#define __NRRM_brk                    0
#define __NRRM_munmap                 2
#define __NRRM_mremap                 0
#define __NRRM_add_key                0
#define __NRRM_request_key            0
#define __NRRM_keyctl                 0
#define __NRRM_clone                  0
#define __NRRM_execve                 2
#define __NRRM_swapon                 0
#define __NRRM_swapoff                0
#define __NRRM_mprotect               2
#define __NRRM_msync                  0
#define __NRRM_mlock                  0
#define __NRRM_munlock                0
#define __NRRM_mlockall               0
#define __NRRM_munlockall             0
#define __NRRM_mincore                0
#define __NRRM_madvise                0
#define __NRRM_remap_file_pages       0
#define __NRRM_mbind                  0
#define __NRRM_get_mempolicy          0
#define __NRRM_set_mempolicy          0
#define __NRRM_migrate_pages          0
#define __NRRM_move_pages             0
#define __NRRM_rt_tgsigqueueinfo      0
#define __NRRM_perf_event_open        0
#define __NRRM_accept4                1
#define __NRRM_recvmmsg               1
#define __NRRM_wait4                  1
#define __NRRM_prlimit64              0
#define __NRRM_fanotify_init          0
#define __NRRM_fanotify_mark          0
#define __NRRM_name_to_handle_at      0
#define __NRRM_open_by_handle_at      0
#define __NRRM_clock_adjtime          0
#define __NRRM_syncfs                 0
#define __NRRM_setns                  0
#define __NRRM_sendmmsg               1
#define __NRRM_process_vm_readv       0
#define __NRRM_process_vm_writev      0
#define __NRRM_kcmp                   0
#define __NRRM_finit_module           0
#define __NRRM_sched_setattr          0
#define __NRRM_sched_getattr          0
#define __NRRM_renameat2              0
#define __NRRM_seccomp                0
#define __NRRM_getrandom              0
#define __NRRM_memfd_create           0
#define __NRRM_bpf                    0
#define __NRRM_execveat               2
#define __NRRM_userfaultfd            0
#define __NRRM_membarrier             0
#define __NRRM_mlock2                 0
#define __NRRM_open                   0
#define __NRRM_link                   0
#define __NRRM_unlink                 0
#define __NRRM_mknod                  0
#define __NRRM_chmod                  0
#define __NRRM_chown                  0
#define __NRRM_mkdir                  0
#define __NRRM_rmdir                  0
#define __NRRM_lchown                 0
#define __NRRM_access                 0
#define __NRRM_rename                 0
#define __NRRM_readlink               0
#define __NRRM_symlink                0
#define __NRRM_utimes                 0
#define __NRRM_pipe                   0
#define __NRRM_dup2                   0
#define __NRRM_epoll_create           0
#define __NRRM_inotify_init           0
#define __NRRM_eventfd                0
#define __NRRM_signalfd               0
#define __NRRM_sendfile               1
#define __NRRM_ftruncate              0
#define __NRRM_truncate               0
#define __NRRM_stat                   0
#define __NRRM_lstat                  0
#define __NRRM_fstat                  0
#define __NRRM_fcntl                  0
#define __NRRM_fadvise64              0
#define __NRRM_newfstatat             0
#define __NRRM_fstatfs                0
#define __NRRM_statfs                 0
#define __NRRM_lseek                  0
#define __NRRM_mmap                   0
#define __NRRM_alarm                  0
#define __NRRM_getpgrp                2
#define __NRRM_pause                  1
#define __NRRM_time                   0
#define __NRRM_utime                  0
#define __NRRM_creat                  0
#define __NRRM_getdents               0
#define __NRRM_futimesat              0
#define __NRRM_select                 1
#define __NRRM_poll                   1
#define __NRRM_epoll_wait             1
#define __NRRM_ustat                  0
#define __NRRM_vfork                  2
#define __NRRM_oldwait4               1
#define __NRRM_recv                   1
#define __NRRM_send                   1
#define __NRRM_bdflush                0
#define __NRRM_umount                 0
#define __NRRM_uselib                 0
#define __NRRM__sysctl                0
#define __NRRM_fork                   2
#endif /* !__NRFEAT_DEFINED_SYSCALL_RESTART_MODES */
#endif /* __WANT_SYSCALL_RESTART_MODES */


/************************************************************************/
/* SYSCALL CANCELLATION POINTS                                          */
/************************************************************************/
#ifdef __WANT_SYSCALL_CANCELLATION_POINTS
#ifndef __NRFEAT_DEFINED_SYSCALL_CANCELLATION_POINTS
#define __NRFEAT_DEFINED_SYSCALL_CANCELLATION_POINTS
#define __NRFEAT_HAVE_CANCELLATION_POINTS
#define __NRCP_setxattr
#define __NRCP_lsetxattr
#define __NRCP_fsetxattr
#define __NRCP_getxattr
#define __NRCP_lgetxattr
#define __NRCP_fgetxattr
#define __NRCP_listxattr
#define __NRCP_llistxattr
#define __NRCP_flistxattr
#define __NRCP_removexattr
#define __NRCP_lremovexattr
#define __NRCP_fremovexattr
#define __NRCP_getcwd
#define __NRCP_epoll_pwait
#define __NRCP_ioctl
#define __NRCP_flock
#define __NRCP_mknodat
#define __NRCP_mkdirat
#define __NRCP_unlinkat
#define __NRCP_symlinkat
#define __NRCP_linkat
#define __NRCP_renameat
#define __NRCP_umount2
#define __NRCP_mount
#define __NRCP_faccessat
#define __NRCP_chdir
#define __NRCP_fchdir
#define __NRCP_fchmod
#define __NRCP_fchmodat
#define __NRCP_fchownat
#define __NRCP_fchown
#define __NRCP_openat
#define __NRCP_getdents64
#define __NRCP_read
#define __NRCP_write
#define __NRCP_readv
#define __NRCP_writev
#define __NRCP_pread64
#define __NRCP_pwrite64
#define __NRCP_preadv
#define __NRCP_pwritev
#define __NRCP_pselect6
#define __NRCP_ppoll
#define __NRCP_vmsplice
#define __NRCP_splice
#define __NRCP_tee
#define __NRCP_readlinkat
#define __NRCP_sync
#define __NRCP_fsync
#define __NRCP_fdatasync
#define __NRCP_sync_file_range
#define __NRCP_utimensat
#define __NRCP_waitid
#define __NRCP_futex
#define __NRCP_nanosleep
#define __NRCP_clock_nanosleep
#define __NRCP_rt_sigsuspend
#define __NRCP_rt_sigtimedwait
#define __NRCP_sysinfo
#define __NRCP_mq_timedsend
#define __NRCP_mq_timedreceive
#define __NRCP_msgrcv
#define __NRCP_msgsnd
#define __NRCP_accept
#define __NRCP_connect
#define __NRCP_sendto
#define __NRCP_recvfrom
#define __NRCP_sendmsg
#define __NRCP_recvmsg
#define __NRCP_execve
#define __NRCP_msync
#define __NRCP_accept4
#define __NRCP_recvmmsg
#define __NRCP_wait4
#define __NRCP_name_to_handle_at
#define __NRCP_open_by_handle_at
#define __NRCP_syncfs
#define __NRCP_sendmmsg
#define __NRCP_renameat2
#define __NRCP_execveat
#define __NRCP_open
#define __NRCP_link
#define __NRCP_unlink
#define __NRCP_mknod
#define __NRCP_chmod
#define __NRCP_chown
#define __NRCP_mkdir
#define __NRCP_lchown
#define __NRCP_access
#define __NRCP_rename
#define __NRCP_readlink
#define __NRCP_symlink
#define __NRCP_utimes
#define __NRCP_sendfile
#define __NRCP_stat
#define __NRCP_lstat
#define __NRCP_fstat
#define __NRCP_fcntl
#define __NRCP_newfstatat
#define __NRCP_lseek
#define __NRCP_pause
#define __NRCP_utime
#define __NRCP_creat
#define __NRCP_getdents
#define __NRCP_futimesat
#define __NRCP_select
#define __NRCP_poll
#define __NRCP_epoll_wait
#define __NRCP_oldwait4
#define __NRCP_recv
#define __NRCP_send
#define __NRCP_umount
#endif /* !__NRFEAT_DEFINED_SYSCALL_CANCELLATION_POINTS */
#endif /* __WANT_SYSCALL_CANCELLATION_POINTS */


/************************************************************************/
/* SYSCALL REGISTER COUNT                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_REGISTER_COUNT
#ifndef __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NRFEAT_SYSCALL_REGISTER_MAX_COUNT none
#define __NRFEAT_SYSCALL_REGISTER_BITS none
#define __NRRC_io_setup               1
#define __NRRC_io_destroy             1
#define __NRRC_io_submit              1
#define __NRRC_io_cancel              1
#define __NRRC_io_getevents           1
#define __NRRC_setxattr               5
#define __NRRC_lsetxattr              5
#define __NRRC_fsetxattr              5
#define __NRRC_getxattr               4
#define __NRRC_lgetxattr              4
#define __NRRC_fgetxattr              4
#define __NRRC_listxattr              3
#define __NRRC_llistxattr             3
#define __NRRC_flistxattr             3
#define __NRRC_removexattr            2
#define __NRRC_lremovexattr           2
#define __NRRC_fremovexattr           2
#define __NRRC_getcwd                 2
#define __NRRC_lookup_dcookie         1
#define __NRRC_eventfd2               2
#define __NRRC_epoll_create1          1
#define __NRRC_epoll_ctl              4
#define __NRRC_epoll_pwait            6
#define __NRRC_dup                    1
#define __NRRC_dup3                   3
#define __NRRC_inotify_init1          1
#define __NRRC_inotify_add_watch      3
#define __NRRC_inotify_rm_watch       2
#define __NRRC_ioctl                  3
#define __NRRC_ioprio_set             3
#define __NRRC_ioprio_get             2
#define __NRRC_flock                  2
#define __NRRC_mknodat                4
#define __NRRC_mkdirat                3
#define __NRRC_unlinkat               3
#define __NRRC_symlinkat              3
#define __NRRC_linkat                 5
#define __NRRC_renameat               4
#define __NRRC_umount2                2
#define __NRRC_mount                  5
#define __NRRC_pivot_root             1
#define __NRRC_nfsservctl             1
#define __NRRC_fallocate              4
#define __NRRC_faccessat              3
#define __NRRC_chdir                  1
#define __NRRC_fchdir                 1
#define __NRRC_chroot                 1
#define __NRRC_fchmod                 2
#define __NRRC_fchmodat               4
#define __NRRC_fchownat               5
#define __NRRC_fchown                 3
#define __NRRC_openat                 4
#define __NRRC_close                  1
#define __NRRC_vhangup                0
#define __NRRC_pipe2                  2
#define __NRRC_quotactl               1
#define __NRRC_getdents64             3
#define __NRRC_read                   3
#define __NRRC_write                  3
#define __NRRC_readv                  3
#define __NRRC_writev                 3
#define __NRRC_pread64                5 /* __NRAC_pread64 + 1 */
#define __NRRC_pwrite64               5 /* __NRAC_pwrite64 + 1 */
#define __NRRC_preadv                 5 /* __NRAC_preadv + 1 */
#define __NRRC_pwritev                5 /* __NRAC_pwritev + 1 */
#define __NRRC_pselect6               6
#define __NRRC_ppoll                  5
#define __NRRC_signalfd4              4
#define __NRRC_vmsplice               4
#define __NRRC_splice                 6
#define __NRRC_tee                    4
#define __NRRC_readlinkat             4
#define __NRRC_sync                   0
#define __NRRC_fsync                  1
#define __NRRC_fdatasync              1
#define __NRRC_sync_file_range        6 /* __NRAC_sync_file_range + 2 */
#define __NRRC_timerfd_create         2
#define __NRRC_timerfd_settime        4
#define __NRRC_timerfd_gettime        2
#define __NRRC_utimensat              4
#define __NRRC_acct                   1
#define __NRRC_capget                 1
#define __NRRC_capset                 1
#define __NRRC_personality            1
#define __NRRC_exit                   1
#define __NRRC_exit_group             1
#define __NRRC_waitid                 5
#define __NRRC_set_tid_address        1
#define __NRRC_unshare                1
#define __NRRC_futex                  6
#define __NRRC_set_robust_list        1
#define __NRRC_get_robust_list        1
#define __NRRC_nanosleep              2
#define __NRRC_getitimer              2
#define __NRRC_setitimer              3
#define __NRRC_kexec_load             1
#define __NRRC_init_module            3
#define __NRRC_delete_module          2
#define __NRRC_timer_create           3
#define __NRRC_timer_gettime          2
#define __NRRC_timer_getoverrun       1
#define __NRRC_timer_settime          4
#define __NRRC_timer_delete           1
#define __NRRC_clock_settime          2
#define __NRRC_clock_gettime          2
#define __NRRC_clock_getres           2
#define __NRRC_clock_nanosleep        4
#define __NRRC_syslog                 3
#define __NRRC_ptrace                 4
#define __NRRC_sched_setparam         2
#define __NRRC_sched_setscheduler     3
#define __NRRC_sched_getscheduler     1
#define __NRRC_sched_getparam         2
#define __NRRC_sched_setaffinity      3
#define __NRRC_sched_getaffinity      3
#define __NRRC_sched_yield            0
#define __NRRC_sched_get_priority_max 1
#define __NRRC_sched_get_priority_min 1
#define __NRRC_sched_rr_get_interval  2
#define __NRRC_restart_syscall        0
#define __NRRC_kill                   2
#define __NRRC_tkill                  2
#define __NRRC_tgkill                 3
#define __NRRC_sigaltstack            2
#define __NRRC_rt_sigsuspend          2
#define __NRRC_rt_sigaction           4
#define __NRRC_rt_sigprocmask         4
#define __NRRC_rt_sigpending          2
#define __NRRC_rt_sigtimedwait        4
#define __NRRC_rt_sigqueueinfo        3
#define __NRRC_rt_sigreturn           0
#define __NRRC_setpriority            3
#define __NRRC_getpriority            2
#define __NRRC_reboot                 1
#define __NRRC_setregid               2
#define __NRRC_setgid                 1
#define __NRRC_setreuid               2
#define __NRRC_setuid                 1
#define __NRRC_setresuid              3
#define __NRRC_getresuid              3
#define __NRRC_setresgid              3
#define __NRRC_getresgid              3
#define __NRRC_setfsuid               1
#define __NRRC_setfsgid               1
#define __NRRC_times                  1
#define __NRRC_setpgid                2
#define __NRRC_getpgid                1
#define __NRRC_getsid                 1
#define __NRRC_setsid                 0
#define __NRRC_getgroups              2
#define __NRRC_setgroups              2
#define __NRRC_uname                  1
#define __NRRC_sethostname            2
#define __NRRC_setdomainname          2
#define __NRRC_getrlimit              2
#define __NRRC_setrlimit              2
#define __NRRC_getrusage              2
#define __NRRC_umask                  1
#define __NRRC_prctl                  5
#define __NRRC_getcpu                 3
#define __NRRC_gettimeofday           2
#define __NRRC_settimeofday           2
#define __NRRC_adjtimex               1
#define __NRRC_getpid                 0
#define __NRRC_getppid                0
#define __NRRC_getuid                 0
#define __NRRC_geteuid                0
#define __NRRC_getgid                 0
#define __NRRC_getegid                0
#define __NRRC_gettid                 0
#define __NRRC_sysinfo                1
#define __NRRC_mq_open                3
#define __NRRC_mq_unlink              1
#define __NRRC_mq_timedsend           5
#define __NRRC_mq_timedreceive        5
#define __NRRC_mq_notify              2
#define __NRRC_mq_getsetattr          3
#define __NRRC_msgget                 1
#define __NRRC_msgctl                 1
#define __NRRC_msgrcv                 1
#define __NRRC_msgsnd                 1
#define __NRRC_semget                 1
#define __NRRC_semctl                 1
#define __NRRC_semtimedop             1
#define __NRRC_semop                  1
#define __NRRC_shmget                 3
#define __NRRC_shmctl                 3
#define __NRRC_shmat                  3
#define __NRRC_shmdt                  1
#define __NRRC_socket                 3
#define __NRRC_socketpair             4
#define __NRRC_bind                   3
#define __NRRC_listen                 2
#define __NRRC_accept                 3
#define __NRRC_connect                3
#define __NRRC_getsockname            3
#define __NRRC_getpeername            3
#define __NRRC_sendto                 6
#define __NRRC_recvfrom               6
#define __NRRC_setsockopt             5
#define __NRRC_getsockopt             5
#define __NRRC_shutdown               2
#define __NRRC_sendmsg                3
#define __NRRC_recvmsg                3
#define __NRRC_readahead              4 /* __NRAC_readahead + 1 */
#define __NRRC_brk                    1
#define __NRRC_munmap                 2
#define __NRRC_mremap                 5
#define __NRRC_add_key                1
#define __NRRC_request_key            1
#define __NRRC_keyctl                 1
#define __NRRC_clone                  5
#define __NRRC_execve                 3
#define __NRRC_swapon                 2
#define __NRRC_swapoff                1
#define __NRRC_mprotect               3
#define __NRRC_msync                  3
#define __NRRC_mlock                  2
#define __NRRC_munlock                2
#define __NRRC_mlockall               1
#define __NRRC_munlockall             0
#define __NRRC_mincore                3
#define __NRRC_madvise                3
#define __NRRC_remap_file_pages       5
#define __NRRC_mbind                  1
#define __NRRC_get_mempolicy          1
#define __NRRC_set_mempolicy          1
#define __NRRC_migrate_pages          1
#define __NRRC_move_pages             1
#define __NRRC_rt_tgsigqueueinfo      4
#define __NRRC_perf_event_open        1
#define __NRRC_accept4                4
#define __NRRC_recvmmsg               5
#define __NRRC_wait4                  4
#define __NRRC_prlimit64              4
#define __NRRC_fanotify_init          1
#define __NRRC_fanotify_mark          1
#define __NRRC_name_to_handle_at      5
#define __NRRC_open_by_handle_at      3
#define __NRRC_clock_adjtime          1
#define __NRRC_syncfs                 1
#define __NRRC_setns                  2
#define __NRRC_sendmmsg               4
#define __NRRC_process_vm_readv       6
#define __NRRC_process_vm_writev      6
#define __NRRC_kcmp                   5
#define __NRRC_finit_module           3
#define __NRRC_sched_setattr          1
#define __NRRC_sched_getattr          1
#define __NRRC_renameat2              5
#define __NRRC_seccomp                1
#define __NRRC_getrandom              3
#define __NRRC_memfd_create           2
#define __NRRC_bpf                    1
#define __NRRC_execveat               5
#define __NRRC_userfaultfd            1
#define __NRRC_membarrier             1
#define __NRRC_mlock2                 3
#define __NRRC_open                   3
#define __NRRC_link                   2
#define __NRRC_unlink                 1
#define __NRRC_mknod                  3
#define __NRRC_chmod                  2
#define __NRRC_chown                  3
#define __NRRC_mkdir                  2
#define __NRRC_rmdir                  1
#define __NRRC_lchown                 3
#define __NRRC_access                 2
#define __NRRC_rename                 2
#define __NRRC_readlink               3
#define __NRRC_symlink                2
#define __NRRC_utimes                 2
#define __NRRC_pipe                   1
#define __NRRC_dup2                   2
#define __NRRC_epoll_create           1
#define __NRRC_inotify_init           0
#define __NRRC_eventfd                1
#define __NRRC_signalfd               3
#define __NRRC_sendfile               4
#define __NRRC_ftruncate              2
#define __NRRC_truncate               2
#define __NRRC_stat                   2
#define __NRRC_lstat                  2
#define __NRRC_fstat                  2
#define __NRRC_fcntl                  3
#define __NRRC_fadvise64              1
#define __NRRC_newfstatat             4
#define __NRRC_fstatfs                2
#define __NRRC_statfs                 2
#define __NRRC_lseek                  3
#define __NRRC_mmap                   6
#define __NRRC_alarm                  1
#define __NRRC_getpgrp                0
#define __NRRC_pause                  0
#define __NRRC_time                   1
#define __NRRC_utime                  2
#define __NRRC_creat                  2
#define __NRRC_getdents               3
#define __NRRC_futimesat              3
#define __NRRC_select                 5
#define __NRRC_poll                   3
#define __NRRC_epoll_wait             4
#define __NRRC_ustat                  2
#define __NRRC_vfork                  0
#define __NRRC_oldwait4               4
#define __NRRC_recv                   4
#define __NRRC_send                   4
#define __NRRC_bdflush                1
#define __NRRC_umount                 1
#define __NRRC_uselib                 1
#define __NRRC__sysctl                1
#define __NRRC_fork                   0
#endif /* !__NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT */
#endif /* __WANT_SYSCALL_REGISTER_COUNT */


/************************************************************************/
/* SYSCALL DOUBLE WIDE RETURN VALUE                                     */
/************************************************************************/
#ifdef __WANT_SYSCALL_DOUBLE_WIDE_RETURN
#ifndef __NRFEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN
#define __NRFEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN
#endif /* !__NRFEAT_DEFINED_SYSCALL_DOUBLE_WIDE_RETURN */
#endif /* __WANT_SYSCALL_DOUBLE_WIDE_RETURN */


