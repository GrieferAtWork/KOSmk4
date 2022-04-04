/* HASH CRC-32:0xeefe23d1 */
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

/************************************************************************/
/* SYSCALL NORETURN ATTRIBUTE                                           */
/************************************************************************/
#ifdef __WANT_SYSCALL_ATTR_NORETURN
#ifndef __NRFEAT_DEFINED_SYSCALL_ATTR_NORETURN
#define __NRFEAT_DEFINED_SYSCALL_ATTR_NORETURN
#define __NRFEAT_HAVE_ATTR_NORETURN
#define __NRNT_exit
#define __NRNT_exit_group
#endif /* !__NRFEAT_DEFINED_SYSCALL_ATTR_NORETURN */
#endif /* __WANT_SYSCALL_ATTR_NORETURN */


/************************************************************************/
/* SYSCALL ARGUMENT COUNT                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_COUNT
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __NRAC_io_setup               1
#define __NRAC_io_destroy             1
#define __NRAC_io_submit              1
#define __NRAC_io_cancel              1
#define __NRAC_io_getevents           1
#define __NRAC_setxattr               5
#define __NRAC_lsetxattr              5
#define __NRAC_fsetxattr              5
#define __NRAC_getxattr               4
#define __NRAC_lgetxattr              4
#define __NRAC_fgetxattr              4
#define __NRAC_listxattr              3
#define __NRAC_llistxattr             3
#define __NRAC_flistxattr             3
#define __NRAC_removexattr            2
#define __NRAC_lremovexattr           2
#define __NRAC_fremovexattr           2
#define __NRAC_getcwd                 2
#define __NRAC_lookup_dcookie         1
#define __NRAC_eventfd2               2
#define __NRAC_epoll_create1          1
#define __NRAC_epoll_ctl              4
#define __NRAC_epoll_pwait            6
#define __NRAC_dup                    1
#define __NRAC_dup3                   3
#define __NRAC_inotify_init1          1
#define __NRAC_inotify_add_watch      3
#define __NRAC_inotify_rm_watch       2
#define __NRAC_ioctl                  3
#define __NRAC_ioprio_set             3
#define __NRAC_ioprio_get             2
#define __NRAC_flock                  2
#define __NRAC_mknodat                4
#define __NRAC_mkdirat                3
#define __NRAC_unlinkat               3
#define __NRAC_symlinkat              3
#define __NRAC_linkat                 5
#define __NRAC_renameat               4
#define __NRAC_umount2                2
#define __NRAC_mount                  5
#define __NRAC_pivot_root             1
#define __NRAC_nfsservctl             1
#define __NRAC_fallocate              4
#define __NRAC_faccessat              3
#define __NRAC_chdir                  1
#define __NRAC_fchdir                 1
#define __NRAC_chroot                 1
#define __NRAC_fchmod                 2
#define __NRAC_fchmodat               4
#define __NRAC_fchownat               5
#define __NRAC_fchown                 3
#define __NRAC_openat                 4
#define __NRAC_close                  1
#define __NRAC_vhangup                0
#define __NRAC_pipe2                  2
#define __NRAC_quotactl               1
#define __NRAC_getdents64             3
#define __NRAC_read                   3
#define __NRAC_write                  3
#define __NRAC_readv                  3
#define __NRAC_writev                 3
#define __NRAC_pread64                4
#define __NRAC_pwrite64               4
#define __NRAC_preadv                 4
#define __NRAC_pwritev                4
#define __NRAC_pselect6               6
#define __NRAC_ppoll                  5
#define __NRAC_signalfd4              4
#define __NRAC_vmsplice               4
#define __NRAC_splice                 6
#define __NRAC_tee                    4
#define __NRAC_readlinkat             4
#define __NRAC_sync                   0
#define __NRAC_fsync                  1
#define __NRAC_fdatasync              1
#define __NRAC_sync_file_range        4
#define __NRAC_timerfd_create         2
#define __NRAC_timerfd_settime        4
#define __NRAC_timerfd_gettime        2
#define __NRAC_utimensat              4
#define __NRAC_acct                   1
#define __NRAC_capget                 1
#define __NRAC_capset                 1
#define __NRAC_personality            1
#define __NRAC_exit                   1
#define __NRAC_exit_group             1
#define __NRAC_waitid                 5
#define __NRAC_set_tid_address        1
#define __NRAC_unshare                1
#define __NRAC_futex                  6
#define __NRAC_set_robust_list        1
#define __NRAC_get_robust_list        1
#define __NRAC_nanosleep              2
#define __NRAC_getitimer              2
#define __NRAC_setitimer              3
#define __NRAC_kexec_load             1
#define __NRAC_init_module            3
#define __NRAC_delete_module          2
#define __NRAC_timer_create           3
#define __NRAC_timer_gettime          2
#define __NRAC_timer_getoverrun       1
#define __NRAC_timer_settime          4
#define __NRAC_timer_delete           1
#define __NRAC_clock_settime          2
#define __NRAC_clock_gettime          2
#define __NRAC_clock_getres           2
#define __NRAC_clock_nanosleep        4
#define __NRAC_syslog                 3
#define __NRAC_ptrace                 4
#define __NRAC_sched_setparam         2
#define __NRAC_sched_setscheduler     3
#define __NRAC_sched_getscheduler     1
#define __NRAC_sched_getparam         2
#define __NRAC_sched_setaffinity      3
#define __NRAC_sched_getaffinity      3
#define __NRAC_sched_yield            0
#define __NRAC_sched_get_priority_max 1
#define __NRAC_sched_get_priority_min 1
#define __NRAC_sched_rr_get_interval  2
#define __NRAC_restart_syscall        0
#define __NRAC_kill                   2
#define __NRAC_tkill                  2
#define __NRAC_tgkill                 3
#define __NRAC_sigaltstack            2
#define __NRAC_rt_sigsuspend          2
#define __NRAC_rt_sigaction           4
#define __NRAC_rt_sigprocmask         4
#define __NRAC_rt_sigpending          2
#define __NRAC_rt_sigtimedwait        4
#define __NRAC_rt_sigqueueinfo        3
#define __NRAC_rt_sigreturn           0
#define __NRAC_setpriority            3
#define __NRAC_getpriority            2
#define __NRAC_reboot                 1
#define __NRAC_setregid               2
#define __NRAC_setgid                 1
#define __NRAC_setreuid               2
#define __NRAC_setuid                 1
#define __NRAC_setresuid              3
#define __NRAC_getresuid              3
#define __NRAC_setresgid              3
#define __NRAC_getresgid              3
#define __NRAC_setfsuid               1
#define __NRAC_setfsgid               1
#define __NRAC_times                  1
#define __NRAC_setpgid                2
#define __NRAC_getpgid                1
#define __NRAC_getsid                 1
#define __NRAC_setsid                 0
#define __NRAC_getgroups              2
#define __NRAC_setgroups              2
#define __NRAC_uname                  1
#define __NRAC_sethostname            2
#define __NRAC_setdomainname          2
#define __NRAC_getrlimit              2
#define __NRAC_setrlimit              2
#define __NRAC_getrusage              2
#define __NRAC_umask                  1
#define __NRAC_prctl                  5
#define __NRAC_getcpu                 3
#define __NRAC_gettimeofday           2
#define __NRAC_settimeofday           2
#define __NRAC_adjtimex               1
#define __NRAC_getpid                 0
#define __NRAC_getppid                0
#define __NRAC_getuid                 0
#define __NRAC_geteuid                0
#define __NRAC_getgid                 0
#define __NRAC_getegid                0
#define __NRAC_gettid                 0
#define __NRAC_sysinfo                1
#define __NRAC_mq_open                3
#define __NRAC_mq_unlink              1
#define __NRAC_mq_timedsend           5
#define __NRAC_mq_timedreceive        5
#define __NRAC_mq_notify              2
#define __NRAC_mq_getsetattr          3
#define __NRAC_msgget                 1
#define __NRAC_msgctl                 1
#define __NRAC_msgrcv                 1
#define __NRAC_msgsnd                 1
#define __NRAC_semget                 1
#define __NRAC_semctl                 1
#define __NRAC_semtimedop             1
#define __NRAC_semop                  1
#define __NRAC_shmget                 3
#define __NRAC_shmctl                 3
#define __NRAC_shmat                  3
#define __NRAC_shmdt                  1
#define __NRAC_socket                 3
#define __NRAC_socketpair             4
#define __NRAC_bind                   3
#define __NRAC_listen                 2
#define __NRAC_accept                 3
#define __NRAC_connect                3
#define __NRAC_getsockname            3
#define __NRAC_getpeername            3
#define __NRAC_sendto                 6
#define __NRAC_recvfrom               6
#define __NRAC_setsockopt             5
#define __NRAC_getsockopt             5
#define __NRAC_shutdown               2
#define __NRAC_sendmsg                3
#define __NRAC_recvmsg                3
#define __NRAC_readahead              3
#define __NRAC_brk                    1
#define __NRAC_munmap                 2
#define __NRAC_mremap                 5
#define __NRAC_add_key                1
#define __NRAC_request_key            1
#define __NRAC_keyctl                 1
#define __NRAC_clone                  5
#define __NRAC_execve                 3
#define __NRAC_swapon                 2
#define __NRAC_swapoff                1
#define __NRAC_mprotect               3
#define __NRAC_msync                  3
#define __NRAC_mlock                  2
#define __NRAC_munlock                2
#define __NRAC_mlockall               1
#define __NRAC_munlockall             0
#define __NRAC_mincore                3
#define __NRAC_madvise                3
#define __NRAC_remap_file_pages       5
#define __NRAC_mbind                  1
#define __NRAC_get_mempolicy          1
#define __NRAC_set_mempolicy          1
#define __NRAC_migrate_pages          1
#define __NRAC_move_pages             1
#define __NRAC_rt_tgsigqueueinfo      4
#define __NRAC_perf_event_open        1
#define __NRAC_accept4                4
#define __NRAC_recvmmsg               5
#define __NRAC_wait4                  4
#define __NRAC_prlimit64              4
#define __NRAC_fanotify_init          1
#define __NRAC_fanotify_mark          1
#define __NRAC_name_to_handle_at      5
#define __NRAC_open_by_handle_at      3
#define __NRAC_clock_adjtime          1
#define __NRAC_syncfs                 1
#define __NRAC_setns                  2
#define __NRAC_sendmmsg               4
#define __NRAC_process_vm_readv       6
#define __NRAC_process_vm_writev      6
#define __NRAC_kcmp                   5
#define __NRAC_finit_module           3
#define __NRAC_sched_setattr          1
#define __NRAC_sched_getattr          1
#define __NRAC_renameat2              5
#define __NRAC_seccomp                1
#define __NRAC_getrandom              3
#define __NRAC_memfd_create           2
#define __NRAC_bpf                    1
#define __NRAC_execveat               5
#define __NRAC_userfaultfd            1
#define __NRAC_membarrier             1
#define __NRAC_mlock2                 3
#define __NRAC_open                   3
#define __NRAC_link                   2
#define __NRAC_unlink                 1
#define __NRAC_mknod                  3
#define __NRAC_chmod                  2
#define __NRAC_chown                  3
#define __NRAC_mkdir                  2
#define __NRAC_rmdir                  1
#define __NRAC_lchown                 3
#define __NRAC_access                 2
#define __NRAC_rename                 2
#define __NRAC_readlink               3
#define __NRAC_symlink                2
#define __NRAC_utimes                 2
#define __NRAC_pipe                   1
#define __NRAC_dup2                   2
#define __NRAC_epoll_create           1
#define __NRAC_inotify_init           0
#define __NRAC_eventfd                1
#define __NRAC_signalfd               3
#define __NRAC_sendfile               4
#define __NRAC_ftruncate              2
#define __NRAC_truncate               2
#define __NRAC_stat                   2
#define __NRAC_lstat                  2
#define __NRAC_fstat                  2
#define __NRAC_fcntl                  3
#define __NRAC_fadvise64              1
#define __NRAC_newfstatat             4
#define __NRAC_fstatfs                2
#define __NRAC_statfs                 2
#define __NRAC_lseek                  3
#define __NRAC_mmap                   6
#define __NRAC_alarm                  1
#define __NRAC_getpgrp                0
#define __NRAC_pause                  0
#define __NRAC_time                   1
#define __NRAC_utime                  2
#define __NRAC_creat                  2
#define __NRAC_getdents               3
#define __NRAC_futimesat              3
#define __NRAC_select                 5
#define __NRAC_poll                   3
#define __NRAC_epoll_wait             4
#define __NRAC_ustat                  2
#define __NRAC_vfork                  0
#define __NRAC_oldwait4               4
#define __NRAC_recv                   4
#define __NRAC_send                   4
#define __NRAC_bdflush                1
#define __NRAC_umount                 1
#define __NRAC_uselib                 1
#define __NRAC__sysctl                1
#define __NRAC_fork                   0
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT */


/************************************************************************/
/* SYSCALL RETURN TYPES                                                 */
/************************************************************************/
#ifdef __WANT_SYSCALL_RETURN_TYPES
#ifndef __NRFEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NRFEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NRRT_io_setup               (errno_t, __errno_t)
#define __NRRT_io_destroy             (errno_t, __errno_t)
#define __NRRT_io_submit              (errno_t, __errno_t)
#define __NRRT_io_cancel              (errno_t, __errno_t)
#define __NRRT_io_getevents           (errno_t, __errno_t)
#define __NRRT_setxattr               (errno_t, __errno_t)
#define __NRRT_lsetxattr              (errno_t, __errno_t)
#define __NRRT_fsetxattr              (errno_t, __errno_t)
#define __NRRT_getxattr               (ssize_t, __ssize_t)
#define __NRRT_lgetxattr              (ssize_t, __ssize_t)
#define __NRRT_fgetxattr              (ssize_t, __ssize_t)
#define __NRRT_listxattr              (ssize_t, __ssize_t)
#define __NRRT_llistxattr             (ssize_t, __ssize_t)
#define __NRRT_flistxattr             (ssize_t, __ssize_t)
#define __NRRT_removexattr            (errno_t, __errno_t)
#define __NRRT_lremovexattr           (errno_t, __errno_t)
#define __NRRT_fremovexattr           (errno_t, __errno_t)
#define __NRRT_getcwd                 (ssize_t, __ssize_t)
#define __NRRT_lookup_dcookie         (errno_t, __errno_t)
#define __NRRT_eventfd2               (fd_t, __fd_t)
#define __NRRT_epoll_create1          (fd_t, __fd_t)
#define __NRRT_epoll_ctl              (errno_t, __errno_t)
#define __NRRT_epoll_pwait            (ssize_t, __ssize_t)
#define __NRRT_dup                    (fd_t, __fd_t)
#define __NRRT_dup3                   (fd_t, __fd_t)
#define __NRRT_inotify_init1          (fd_t, __fd_t)
#define __NRRT_inotify_add_watch      (int, int)
#define __NRRT_inotify_rm_watch       (errno_t, __errno_t)
#define __NRRT_ioctl                  (syscall_slong_t, __syscall_slong_t)
#define __NRRT_ioprio_set             (errno_t, __errno_t)
#define __NRRT_ioprio_get             (syscall_slong_t, __syscall_slong_t)
#define __NRRT_flock                  (errno_t, __errno_t)
#define __NRRT_mknodat                (errno_t, __errno_t)
#define __NRRT_mkdirat                (errno_t, __errno_t)
#define __NRRT_unlinkat               (errno_t, __errno_t)
#define __NRRT_symlinkat              (errno_t, __errno_t)
#define __NRRT_linkat                 (errno_t, __errno_t)
#define __NRRT_renameat               (errno_t, __errno_t)
#define __NRRT_umount2                (errno_t, __errno_t)
#define __NRRT_mount                  (errno_t, __errno_t)
#define __NRRT_pivot_root             (errno_t, __errno_t)
#define __NRRT_nfsservctl             (errno_t, __errno_t)
#define __NRRT_fallocate              (errno_t, __errno_t)
#define __NRRT_faccessat              (errno_t, __errno_t)
#define __NRRT_chdir                  (errno_t, __errno_t)
#define __NRRT_fchdir                 (errno_t, __errno_t)
#define __NRRT_chroot                 (errno_t, __errno_t)
#define __NRRT_fchmod                 (errno_t, __errno_t)
#define __NRRT_fchmodat               (errno_t, __errno_t)
#define __NRRT_fchownat               (errno_t, __errno_t)
#define __NRRT_fchown                 (errno_t, __errno_t)
#define __NRRT_openat                 (fd_t, __fd_t)
#define __NRRT_close                  (errno_t, __errno_t)
#define __NRRT_vhangup                (errno_t, __errno_t)
#define __NRRT_pipe2                  (errno_t, __errno_t)
#define __NRRT_quotactl               (errno_t, __errno_t)
#define __NRRT_getdents64             (ssize_t, __ssize_t)
#define __NRRT_read                   (ssize_t, __ssize_t)
#define __NRRT_write                  (ssize_t, __ssize_t)
#define __NRRT_readv                  (ssize_t, __ssize_t)
#define __NRRT_writev                 (ssize_t, __ssize_t)
#define __NRRT_pread64                (ssize_t, __ssize_t)
#define __NRRT_pwrite64               (ssize_t, __ssize_t)
#define __NRRT_preadv                 (ssize_t, __ssize_t)
#define __NRRT_pwritev                (ssize_t, __ssize_t)
#define __NRRT_pselect6               (ssize_t, __ssize_t)
#define __NRRT_ppoll                  (ssize_t, __ssize_t)
#define __NRRT_signalfd4              (errno_t, __errno_t)
#define __NRRT_vmsplice               (ssize_t, __ssize_t)
#define __NRRT_splice                 (ssize_t, __ssize_t)
#define __NRRT_tee                    (ssize_t, __ssize_t)
#define __NRRT_readlinkat             (ssize_t, __ssize_t)
#define __NRRT_sync                   (errno_t, __errno_t)
#define __NRRT_fsync                  (errno_t, __errno_t)
#define __NRRT_fdatasync              (errno_t, __errno_t)
#define __NRRT_sync_file_range        (errno_t, __errno_t)
#define __NRRT_timerfd_create         (fd_t, __fd_t)
#define __NRRT_timerfd_settime        (errno_t, __errno_t)
#define __NRRT_timerfd_gettime        (errno_t, __errno_t)
#define __NRRT_utimensat              (errno_t, __errno_t)
#define __NRRT_acct                   (errno_t, __errno_t)
#define __NRRT_capget                 (errno_t, __errno_t)
#define __NRRT_capset                 (errno_t, __errno_t)
#define __NRRT_personality            (errno_t, __errno_t)
#define __NRRT_exit                   (void, void)
#define __NRRT_exit_group             (void, void)
#define __NRRT_waitid                 (errno_t, __errno_t)
#define __NRRT_set_tid_address        (pid_t, __pid_t)
#define __NRRT_unshare                (errno_t, __errno_t)
#define __NRRT_futex                  (syscall_slong_t, __syscall_slong_t)
#define __NRRT_set_robust_list        (errno_t, __errno_t)
#define __NRRT_get_robust_list        (errno_t, __errno_t)
#define __NRRT_nanosleep              (errno_t, __errno_t)
#define __NRRT_getitimer              (errno_t, __errno_t)
#define __NRRT_setitimer              (errno_t, __errno_t)
#define __NRRT_kexec_load             (errno_t, __errno_t)
#define __NRRT_init_module            (errno_t, __errno_t)
#define __NRRT_delete_module          (errno_t, __errno_t)
#define __NRRT_timer_create           (errno_t, __errno_t)
#define __NRRT_timer_gettime          (errno_t, __errno_t)
#define __NRRT_timer_getoverrun       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_timer_settime          (errno_t, __errno_t)
#define __NRRT_timer_delete           (errno_t, __errno_t)
#define __NRRT_clock_settime          (errno_t, __errno_t)
#define __NRRT_clock_gettime          (errno_t, __errno_t)
#define __NRRT_clock_getres           (errno_t, __errno_t)
#define __NRRT_clock_nanosleep        (errno_t, __errno_t)
#define __NRRT_syslog                 (ssize_t, __ssize_t)
#define __NRRT_ptrace                 (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_setparam         (errno_t, __errno_t)
#define __NRRT_sched_setscheduler     (errno_t, __errno_t)
#define __NRRT_sched_getscheduler     (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_getparam         (errno_t, __errno_t)
#define __NRRT_sched_setaffinity      (errno_t, __errno_t)
#define __NRRT_sched_getaffinity      (errno_t, __errno_t)
#define __NRRT_sched_yield            (errno_t, __errno_t)
#define __NRRT_sched_get_priority_max (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_get_priority_min (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_rr_get_interval  (errno_t, __errno_t)
#define __NRRT_restart_syscall        (errno_t, __errno_t)
#define __NRRT_kill                   (errno_t, __errno_t)
#define __NRRT_tkill                  (errno_t, __errno_t)
#define __NRRT_tgkill                 (errno_t, __errno_t)
#define __NRRT_sigaltstack            (errno_t, __errno_t)
#define __NRRT_rt_sigsuspend          (errno_t, __errno_t)
#define __NRRT_rt_sigaction           (errno_t, __errno_t)
#define __NRRT_rt_sigprocmask         (errno_t, __errno_t)
#define __NRRT_rt_sigpending          (errno_t, __errno_t)
#define __NRRT_rt_sigtimedwait        (syscall_slong_t, __syscall_slong_t)
#define __NRRT_rt_sigqueueinfo        (errno_t, __errno_t)
#define __NRRT_rt_sigreturn           (void, void)
#define __NRRT_setpriority            (errno_t, __errno_t)
#define __NRRT_getpriority            (syscall_slong_t, __syscall_slong_t)
#define __NRRT_reboot                 (errno_t, __errno_t)
#define __NRRT_setregid               (errno_t, __errno_t)
#define __NRRT_setgid                 (errno_t, __errno_t)
#define __NRRT_setreuid               (errno_t, __errno_t)
#define __NRRT_setuid                 (errno_t, __errno_t)
#define __NRRT_setresuid              (errno_t, __errno_t)
#define __NRRT_getresuid              (errno_t, __errno_t)
#define __NRRT_setresgid              (errno_t, __errno_t)
#define __NRRT_getresgid              (errno_t, __errno_t)
#define __NRRT_setfsuid               (errno_t, __errno_t)
#define __NRRT_setfsgid               (errno_t, __errno_t)
#define __NRRT_times                  (clock_t, __clock_t)
#define __NRRT_setpgid                (errno_t, __errno_t)
#define __NRRT_getpgid                (pid_t, __pid_t)
#define __NRRT_getsid                 (pid_t, __pid_t)
#define __NRRT_setsid                 (pid_t, __pid_t)
#define __NRRT_getgroups              (ssize_t, __ssize_t)
#define __NRRT_setgroups              (errno_t, __errno_t)
#define __NRRT_uname                  (errno_t, __errno_t)
#define __NRRT_sethostname            (errno_t, __errno_t)
#define __NRRT_setdomainname          (errno_t, __errno_t)
#define __NRRT_getrlimit              (errno_t, __errno_t)
#define __NRRT_setrlimit              (errno_t, __errno_t)
#define __NRRT_getrusage              (errno_t, __errno_t)
#define __NRRT_umask                  (mode_t, __mode_t)
#define __NRRT_prctl                  (syscall_slong_t, __syscall_slong_t)
#define __NRRT_getcpu                 (errno_t, __errno_t)
#define __NRRT_gettimeofday           (errno_t, __errno_t)
#define __NRRT_settimeofday           (errno_t, __errno_t)
#define __NRRT_adjtimex               (errno_t, __errno_t)
#define __NRRT_getpid                 (pid_t, __pid_t)
#define __NRRT_getppid                (pid_t, __pid_t)
#define __NRRT_getuid                 (uid_t, __uid_t)
#define __NRRT_geteuid                (uid_t, __uid_t)
#define __NRRT_getgid                 (gid_t, __gid_t)
#define __NRRT_getegid                (gid_t, __gid_t)
#define __NRRT_gettid                 (pid_t, __pid_t)
#define __NRRT_sysinfo                (errno_t, __errno_t)
#define __NRRT_mq_open                (fd_t, __fd_t)
#define __NRRT_mq_unlink              (errno_t, __errno_t)
#define __NRRT_mq_timedsend           (errno_t, __errno_t)
#define __NRRT_mq_timedreceive        (ssize_t, __ssize_t)
#define __NRRT_mq_notify              (errno_t, __errno_t)
#define __NRRT_mq_getsetattr          (errno_t, __errno_t)
#define __NRRT_msgget                 (errno_t, __errno_t)
#define __NRRT_msgctl                 (errno_t, __errno_t)
#define __NRRT_msgrcv                 (errno_t, __errno_t)
#define __NRRT_msgsnd                 (errno_t, __errno_t)
#define __NRRT_semget                 (errno_t, __errno_t)
#define __NRRT_semctl                 (errno_t, __errno_t)
#define __NRRT_semtimedop             (errno_t, __errno_t)
#define __NRRT_semop                  (errno_t, __errno_t)
#define __NRRT_shmget                 (errno_t, __errno_t)
#define __NRRT_shmctl                 (errno_t, __errno_t)
#define __NRRT_shmat                  (errno_t, __errno_t)
#define __NRRT_shmdt                  (errno_t, __errno_t)
#define __NRRT_socket                 (fd_t, __fd_t)
#define __NRRT_socketpair             (errno_t, __errno_t)
#define __NRRT_bind                   (errno_t, __errno_t)
#define __NRRT_listen                 (errno_t, __errno_t)
#define __NRRT_accept                 (fd_t, __fd_t)
#define __NRRT_connect                (errno_t, __errno_t)
#define __NRRT_getsockname            (errno_t, __errno_t)
#define __NRRT_getpeername            (errno_t, __errno_t)
#define __NRRT_sendto                 (ssize_t, __ssize_t)
#define __NRRT_recvfrom               (ssize_t, __ssize_t)
#define __NRRT_setsockopt             (errno_t, __errno_t)
#define __NRRT_getsockopt             (errno_t, __errno_t)
#define __NRRT_shutdown               (errno_t, __errno_t)
#define __NRRT_sendmsg                (ssize_t, __ssize_t)
#define __NRRT_recvmsg                (ssize_t, __ssize_t)
#define __NRRT_readahead              (ssize_t, __ssize_t)
#define __NRRT_brk                    (errno_t, __errno_t)
#define __NRRT_munmap                 (errno_t, __errno_t)
#define __NRRT_mremap                 (void *, void *)
#define __NRRT_add_key                (errno_t, __errno_t)
#define __NRRT_request_key            (errno_t, __errno_t)
#define __NRRT_keyctl                 (errno_t, __errno_t)
#define __NRRT_clone                  (pid_t, __pid_t)
#define __NRRT_execve                 (errno_t, __errno_t)
#define __NRRT_swapon                 (errno_t, __errno_t)
#define __NRRT_swapoff                (errno_t, __errno_t)
#define __NRRT_mprotect               (errno_t, __errno_t)
#define __NRRT_msync                  (errno_t, __errno_t)
#define __NRRT_mlock                  (errno_t, __errno_t)
#define __NRRT_munlock                (errno_t, __errno_t)
#define __NRRT_mlockall               (errno_t, __errno_t)
#define __NRRT_munlockall             (errno_t, __errno_t)
#define __NRRT_mincore                (errno_t, __errno_t)
#define __NRRT_madvise                (errno_t, __errno_t)
#define __NRRT_remap_file_pages       (errno_t, __errno_t)
#define __NRRT_mbind                  (errno_t, __errno_t)
#define __NRRT_get_mempolicy          (errno_t, __errno_t)
#define __NRRT_set_mempolicy          (errno_t, __errno_t)
#define __NRRT_migrate_pages          (errno_t, __errno_t)
#define __NRRT_move_pages             (errno_t, __errno_t)
#define __NRRT_rt_tgsigqueueinfo      (errno_t, __errno_t)
#define __NRRT_perf_event_open        (errno_t, __errno_t)
#define __NRRT_accept4                (fd_t, __fd_t)
#define __NRRT_recvmmsg               (ssize_t, __ssize_t)
#define __NRRT_wait4                  (pid_t, __pid_t)
#define __NRRT_prlimit64              (errno_t, __errno_t)
#define __NRRT_fanotify_init          (errno_t, __errno_t)
#define __NRRT_fanotify_mark          (errno_t, __errno_t)
#define __NRRT_name_to_handle_at      (errno_t, __errno_t)
#define __NRRT_open_by_handle_at      (fd_t, __fd_t)
#define __NRRT_clock_adjtime          (errno_t, __errno_t)
#define __NRRT_syncfs                 (errno_t, __errno_t)
#define __NRRT_setns                  (errno_t, __errno_t)
#define __NRRT_sendmmsg               (ssize_t, __ssize_t)
#define __NRRT_process_vm_readv       (ssize_t, __ssize_t)
#define __NRRT_process_vm_writev      (ssize_t, __ssize_t)
#define __NRRT_kcmp                   (syscall_slong_t, __syscall_slong_t)
#define __NRRT_finit_module           (errno_t, __errno_t)
#define __NRRT_sched_setattr          (errno_t, __errno_t)
#define __NRRT_sched_getattr          (errno_t, __errno_t)
#define __NRRT_renameat2              (errno_t, __errno_t)
#define __NRRT_seccomp                (errno_t, __errno_t)
#define __NRRT_getrandom              (ssize_t, __ssize_t)
#define __NRRT_memfd_create           (fd_t, __fd_t)
#define __NRRT_bpf                    (errno_t, __errno_t)
#define __NRRT_execveat               (errno_t, __errno_t)
#define __NRRT_userfaultfd            (fd_t, __fd_t)
#define __NRRT_membarrier             (errno_t, __errno_t)
#define __NRRT_mlock2                 (errno_t, __errno_t)
#define __NRRT_open                   (fd_t, __fd_t)
#define __NRRT_link                   (errno_t, __errno_t)
#define __NRRT_unlink                 (errno_t, __errno_t)
#define __NRRT_mknod                  (errno_t, __errno_t)
#define __NRRT_chmod                  (errno_t, __errno_t)
#define __NRRT_chown                  (errno_t, __errno_t)
#define __NRRT_mkdir                  (errno_t, __errno_t)
#define __NRRT_rmdir                  (errno_t, __errno_t)
#define __NRRT_lchown                 (errno_t, __errno_t)
#define __NRRT_access                 (errno_t, __errno_t)
#define __NRRT_rename                 (errno_t, __errno_t)
#define __NRRT_readlink               (ssize_t, __ssize_t)
#define __NRRT_symlink                (errno_t, __errno_t)
#define __NRRT_utimes                 (errno_t, __errno_t)
#define __NRRT_pipe                   (errno_t, __errno_t)
#define __NRRT_dup2                   (fd_t, __fd_t)
#define __NRRT_epoll_create           (fd_t, __fd_t)
#define __NRRT_inotify_init           (fd_t, __fd_t)
#define __NRRT_eventfd                (fd_t, __fd_t)
#define __NRRT_signalfd               (errno_t, __errno_t)
#define __NRRT_sendfile               (ssize_t, __ssize_t)
#define __NRRT_ftruncate              (errno_t, __errno_t)
#define __NRRT_truncate               (errno_t, __errno_t)
#define __NRRT_stat                   (errno_t, __errno_t)
#define __NRRT_lstat                  (errno_t, __errno_t)
#define __NRRT_fstat                  (errno_t, __errno_t)
#define __NRRT_fcntl                  (syscall_slong_t, __syscall_slong_t)
#define __NRRT_fadvise64              (errno_t, __errno_t)
#define __NRRT_newfstatat             (errno_t, __errno_t)
#define __NRRT_fstatfs                (errno_t, __errno_t)
#define __NRRT_statfs                 (errno_t, __errno_t)
#define __NRRT_lseek                  (syscall_slong_t, __syscall_slong_t)
#define __NRRT_mmap                   (void *, void *)
#define __NRRT_alarm                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRRT_getpgrp                (pid_t, __pid_t)
#define __NRRT_pause                  (errno_t, __errno_t)
#define __NRRT_time                   (time32_t, __time32_t)
#define __NRRT_utime                  (errno_t, __errno_t)
#define __NRRT_creat                  (fd_t, __fd_t)
#define __NRRT_getdents               (ssize_t, __ssize_t)
#define __NRRT_futimesat              (errno_t, __errno_t)
#define __NRRT_select                 (ssize_t, __ssize_t)
#define __NRRT_poll                   (ssize_t, __ssize_t)
#define __NRRT_epoll_wait             (ssize_t, __ssize_t)
#define __NRRT_ustat                  (errno_t, __errno_t)
#define __NRRT_vfork                  (pid_t, __pid_t)
#define __NRRT_oldwait4               (pid_t, __pid_t)
#define __NRRT_recv                   (ssize_t, __ssize_t)
#define __NRRT_send                   (ssize_t, __ssize_t)
#define __NRRT_bdflush                (errno_t, __errno_t)
#define __NRRT_umount                 (errno_t, __errno_t)
#define __NRRT_uselib                 (errno_t, __errno_t)
#define __NRRT__sysctl                (errno_t, __errno_t)
#define __NRRT_fork                   (pid_t, __pid_t)
#endif /* !__NRFEAT_DEFINED_SYSCALL_RETURN_TYPES */
#endif /* __WANT_SYSCALL_RETURN_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT TYPES                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_TYPES
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NRAT0_io_setup               (int, int)
#define __NRAT0_io_destroy             (int, int)
#define __NRAT0_io_submit              (int, int)
#define __NRAT0_io_cancel              (int, int)
#define __NRAT0_io_getevents           (int, int)
#define __NRAT0_setxattr               (char const *, char const *)
#define __NRAT1_setxattr               (char const *, char const *)
#define __NRAT2_setxattr               (void const *, void const *)
#define __NRAT3_setxattr               (size_t, __size_t)
#define __NRAT4_setxattr               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_lsetxattr              (char const *, char const *)
#define __NRAT1_lsetxattr              (char const *, char const *)
#define __NRAT2_lsetxattr              (void const *, void const *)
#define __NRAT3_lsetxattr              (size_t, __size_t)
#define __NRAT4_lsetxattr              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_fsetxattr              (fd_t, __fd_t)
#define __NRAT1_fsetxattr              (char const *, char const *)
#define __NRAT2_fsetxattr              (void const *, void const *)
#define __NRAT3_fsetxattr              (size_t, __size_t)
#define __NRAT4_fsetxattr              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_getxattr               (char const *, char const *)
#define __NRAT1_getxattr               (char const *, char const *)
#define __NRAT2_getxattr               (void *, void *)
#define __NRAT3_getxattr               (size_t, __size_t)
#define __NRAT0_lgetxattr              (char const *, char const *)
#define __NRAT1_lgetxattr              (char const *, char const *)
#define __NRAT2_lgetxattr              (void *, void *)
#define __NRAT3_lgetxattr              (size_t, __size_t)
#define __NRAT0_fgetxattr              (fd_t, __fd_t)
#define __NRAT1_fgetxattr              (char const *, char const *)
#define __NRAT2_fgetxattr              (void *, void *)
#define __NRAT3_fgetxattr              (size_t, __size_t)
#define __NRAT0_listxattr              (char const *, char const *)
#define __NRAT1_listxattr              (char *, char *)
#define __NRAT2_listxattr              (size_t, __size_t)
#define __NRAT0_llistxattr             (char const *, char const *)
#define __NRAT1_llistxattr             (char *, char *)
#define __NRAT2_llistxattr             (size_t, __size_t)
#define __NRAT0_flistxattr             (fd_t, __fd_t)
#define __NRAT1_flistxattr             (char *, char *)
#define __NRAT2_flistxattr             (size_t, __size_t)
#define __NRAT0_removexattr            (char const *, char const *)
#define __NRAT1_removexattr            (char const *, char const *)
#define __NRAT0_lremovexattr           (char const *, char const *)
#define __NRAT1_lremovexattr           (char const *, char const *)
#define __NRAT0_fremovexattr           (fd_t, __fd_t)
#define __NRAT1_fremovexattr           (char const *, char const *)
#define __NRAT0_getcwd                 (char *, char *)
#define __NRAT1_getcwd                 (size_t, __size_t)
#define __NRAT0_lookup_dcookie         (int, int)
#define __NRAT0_eventfd2               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_eventfd2               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_epoll_create1          (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_epoll_ctl              (fd_t, __fd_t)
#define __NRAT1_epoll_ctl              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_epoll_ctl              (fd_t, __fd_t)
#define __NRAT3_epoll_ctl              (struct epoll_event *, struct epoll_event *)
#define __NRAT0_epoll_pwait            (fd_t, __fd_t)
#define __NRAT1_epoll_pwait            (struct epoll_event *, struct epoll_event *)
#define __NRAT2_epoll_pwait            (size_t, __size_t)
#define __NRAT3_epoll_pwait            (syscall_slong_t, __syscall_slong_t)
#define __NRAT4_epoll_pwait            (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT5_epoll_pwait            (size_t, __size_t)
#define __NRAT0_dup                    (fd_t, __fd_t)
#define __NRAT0_dup3                   (fd_t, __fd_t)
#define __NRAT1_dup3                   (fd_t, __fd_t)
#define __NRAT2_dup3                   (oflag_t, __oflag_t)
#define __NRAT0_inotify_init1          (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_inotify_add_watch      (fd_t, __fd_t)
#define __NRAT1_inotify_add_watch      (char const *, char const *)
#define __NRAT2_inotify_add_watch      (uint32_t, __uint32_t)
#define __NRAT0_inotify_rm_watch       (fd_t, __fd_t)
#define __NRAT1_inotify_rm_watch       (int, int)
#define __NRAT0_ioctl                  (fd_t, __fd_t)
#define __NRAT1_ioctl                  (ioctl_t, __ioctl_t)
#define __NRAT2_ioctl                  (void *, void *)
#define __NRAT0_ioprio_set             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_ioprio_set             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_ioprio_set             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_ioprio_get             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_ioprio_get             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_flock                  (fd_t, __fd_t)
#define __NRAT1_flock                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_mknodat                (fd_t, __fd_t)
#define __NRAT1_mknodat                (char const *, char const *)
#define __NRAT2_mknodat                (mode_t, __mode_t)
#define __NRAT3_mknodat                (dev_t, __dev_t)
#define __NRAT0_mkdirat                (fd_t, __fd_t)
#define __NRAT1_mkdirat                (char const *, char const *)
#define __NRAT2_mkdirat                (mode_t, __mode_t)
#define __NRAT0_unlinkat               (fd_t, __fd_t)
#define __NRAT1_unlinkat               (char const *, char const *)
#define __NRAT2_unlinkat               (atflag_t, __atflag_t)
#define __NRAT0_symlinkat              (char const *, char const *)
#define __NRAT1_symlinkat              (fd_t, __fd_t)
#define __NRAT2_symlinkat              (char const *, char const *)
#define __NRAT0_linkat                 (fd_t, __fd_t)
#define __NRAT1_linkat                 (char const *, char const *)
#define __NRAT2_linkat                 (fd_t, __fd_t)
#define __NRAT3_linkat                 (char const *, char const *)
#define __NRAT4_linkat                 (atflag_t, __atflag_t)
#define __NRAT0_renameat               (fd_t, __fd_t)
#define __NRAT1_renameat               (char const *, char const *)
#define __NRAT2_renameat               (fd_t, __fd_t)
#define __NRAT3_renameat               (char const *, char const *)
#define __NRAT0_umount2                (char const *, char const *)
#define __NRAT1_umount2                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_mount                  (char const *, char const *)
#define __NRAT1_mount                  (char const *, char const *)
#define __NRAT2_mount                  (char const *, char const *)
#define __NRAT3_mount                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_mount                  (void const *, void const *)
#define __NRAT0_pivot_root             (int, int)
#define __NRAT0_nfsservctl             (int, int)
#define __NRAT0_fallocate              (fd_t, __fd_t)
#define __NRAT1_fallocate              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_fallocate              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_fallocate              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_faccessat              (fd_t, __fd_t)
#define __NRAT1_faccessat              (char const *, char const *)
#define __NRAT2_faccessat              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_chdir                  (char const *, char const *)
#define __NRAT0_fchdir                 (fd_t, __fd_t)
#define __NRAT0_chroot                 (char const *, char const *)
#define __NRAT0_fchmod                 (fd_t, __fd_t)
#define __NRAT1_fchmod                 (mode_t, __mode_t)
#define __NRAT0_fchmodat               (fd_t, __fd_t)
#define __NRAT1_fchmodat               (char const *, char const *)
#define __NRAT2_fchmodat               (mode_t, __mode_t)
#define __NRAT3_fchmodat               (atflag_t, __atflag_t)
#define __NRAT0_fchownat               (fd_t, __fd_t)
#define __NRAT1_fchownat               (char const *, char const *)
#define __NRAT2_fchownat               (uid_t, __uid_t)
#define __NRAT3_fchownat               (gid_t, __gid_t)
#define __NRAT4_fchownat               (atflag_t, __atflag_t)
#define __NRAT0_fchown                 (fd_t, __fd_t)
#define __NRAT1_fchown                 (uid_t, __uid_t)
#define __NRAT2_fchown                 (gid_t, __gid_t)
#define __NRAT0_openat                 (fd_t, __fd_t)
#define __NRAT1_openat                 (char const *, char const *)
#define __NRAT2_openat                 (oflag_t, __oflag_t)
#define __NRAT3_openat                 (mode_t, __mode_t)
#define __NRAT0_close                  (fd_t, __fd_t)
#define __NRAT0_pipe2                  (fd_t *, __fd_t *)
#define __NRAT1_pipe2                  (oflag_t, __oflag_t)
#define __NRAT0_quotactl               (int, int)
#define __NRAT0_getdents64             (fd_t, __fd_t)
#define __NRAT1_getdents64             (struct linux_dirent64 *, struct linux_dirent64 *)
#define __NRAT2_getdents64             (size_t, __size_t)
#define __NRAT0_read                   (fd_t, __fd_t)
#define __NRAT1_read                   (void *, void *)
#define __NRAT2_read                   (size_t, __size_t)
#define __NRAT0_write                  (fd_t, __fd_t)
#define __NRAT1_write                  (void const *, void const *)
#define __NRAT2_write                  (size_t, __size_t)
#define __NRAT0_readv                  (fd_t, __fd_t)
#define __NRAT1_readv                  (struct iovec const *, struct iovec const *)
#define __NRAT2_readv                  (size_t, __size_t)
#define __NRAT0_writev                 (fd_t, __fd_t)
#define __NRAT1_writev                 (struct iovec const *, struct iovec const *)
#define __NRAT2_writev                 (size_t, __size_t)
#define __NRAT0_pread64                (fd_t, __fd_t)
#define __NRAT1_pread64                (void *, void *)
#define __NRAT2_pread64                (size_t, __size_t)
#define __NRAT3_pread64                (uint64_t, __uint64_t)
#define __NRAT0_pwrite64               (fd_t, __fd_t)
#define __NRAT1_pwrite64               (void const *, void const *)
#define __NRAT2_pwrite64               (size_t, __size_t)
#define __NRAT3_pwrite64               (uint64_t, __uint64_t)
#define __NRAT0_preadv                 (fd_t, __fd_t)
#define __NRAT1_preadv                 (struct iovec const *, struct iovec const *)
#define __NRAT2_preadv                 (size_t, __size_t)
#define __NRAT3_preadv                 (uint64_t, __uint64_t)
#define __NRAT0_pwritev                (fd_t, __fd_t)
#define __NRAT1_pwritev                (struct iovec const *, struct iovec const *)
#define __NRAT2_pwritev                (size_t, __size_t)
#define __NRAT3_pwritev                (uint64_t, __uint64_t)
#define __NRAT0_pselect6               (size_t, __size_t)
#define __NRAT1_pselect6               (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT2_pselect6               (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT3_pselect6               (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT4_pselect6               (struct timespec const *, struct timespec const *)
#define __NRAT5_pselect6               (struct sigset_with_size const *, struct sigset_with_size const *)
#define __NRAT0_ppoll                  (struct pollfd *, struct pollfd *)
#define __NRAT1_ppoll                  (size_t, __size_t)
#define __NRAT2_ppoll                  (struct timespec const *, struct timespec const *)
#define __NRAT3_ppoll                  (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT4_ppoll                  (size_t, __size_t)
#define __NRAT0_signalfd4              (fd_t, __fd_t)
#define __NRAT1_signalfd4              (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT2_signalfd4              (size_t, __size_t)
#define __NRAT3_signalfd4              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_vmsplice               (fd_t, __fd_t)
#define __NRAT1_vmsplice               (struct iovec const *, struct iovec const *)
#define __NRAT2_vmsplice               (size_t, __size_t)
#define __NRAT3_vmsplice               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_splice                 (fd_t, __fd_t)
#define __NRAT1_splice                 (uint64_t *, __uint64_t *)
#define __NRAT2_splice                 (fd_t, __fd_t)
#define __NRAT3_splice                 (uint64_t *, __uint64_t *)
#define __NRAT4_splice                 (size_t, __size_t)
#define __NRAT5_splice                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_tee                    (fd_t, __fd_t)
#define __NRAT1_tee                    (fd_t, __fd_t)
#define __NRAT2_tee                    (size_t, __size_t)
#define __NRAT3_tee                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_readlinkat             (fd_t, __fd_t)
#define __NRAT1_readlinkat             (char const *, char const *)
#define __NRAT2_readlinkat             (char *, char *)
#define __NRAT3_readlinkat             (size_t, __size_t)
#define __NRAT0_fsync                  (fd_t, __fd_t)
#define __NRAT0_fdatasync              (fd_t, __fd_t)
#define __NRAT0_sync_file_range        (fd_t, __fd_t)
#define __NRAT1_sync_file_range        (uint64_t, __uint64_t)
#define __NRAT2_sync_file_range        (uint64_t, __uint64_t)
#define __NRAT3_sync_file_range        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_timerfd_create         (clockid_t, __clockid_t)
#define __NRAT1_timerfd_create         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_timerfd_settime        (fd_t, __fd_t)
#define __NRAT1_timerfd_settime        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_timerfd_settime        (struct itimerspec const *, struct itimerspec const *)
#define __NRAT3_timerfd_settime        (struct itimerspec *, struct itimerspec *)
#define __NRAT0_timerfd_gettime        (fd_t, __fd_t)
#define __NRAT1_timerfd_gettime        (struct itimerspec *, struct itimerspec *)
#define __NRAT0_utimensat              (fd_t, __fd_t)
#define __NRAT1_utimensat              (char const *, char const *)
#define __NRAT2_utimensat              (struct timespec const *, struct timespec const *)
#define __NRAT3_utimensat              (atflag_t, __atflag_t)
#define __NRAT0_acct                   (char const *, char const *)
#define __NRAT0_capget                 (int, int)
#define __NRAT0_capset                 (int, int)
#define __NRAT0_personality            (int, int)
#define __NRAT0_exit                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_exit_group             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_waitid                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_waitid                 (id_t, __id_t)
#define __NRAT2_waitid                 (struct __siginfo_struct *, struct __siginfo_struct *)
#define __NRAT3_waitid                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_waitid                 (struct rusage *, struct rusage *)
#define __NRAT0_set_tid_address        (pid_t *, __pid_t *)
#define __NRAT0_unshare                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_futex                  (uint32_t *, __uint32_t *)
#define __NRAT1_futex                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_futex                  (uint32_t, __uint32_t)
#define __NRAT3_futex                  (struct timespec const *, struct timespec const *)
#define __NRAT4_futex                  (uint32_t *, __uint32_t *)
#define __NRAT5_futex                  (uint32_t, __uint32_t)
#define __NRAT0_set_robust_list        (int, int)
#define __NRAT0_get_robust_list        (int, int)
#define __NRAT0_nanosleep              (struct timespec const *, struct timespec const *)
#define __NRAT1_nanosleep              (struct timespec *, struct timespec *)
#define __NRAT0_getitimer              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_getitimer              (struct itimerval *, struct itimerval *)
#define __NRAT0_setitimer              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_setitimer              (struct itimerval const *, struct itimerval const *)
#define __NRAT2_setitimer              (struct itimerval *, struct itimerval *)
#define __NRAT0_kexec_load             (int, int)
#define __NRAT0_init_module            (void const *, void const *)
#define __NRAT1_init_module            (size_t, __size_t)
#define __NRAT2_init_module            (char const *, char const *)
#define __NRAT0_delete_module          (char const *, char const *)
#define __NRAT1_delete_module          (oflag_t, __oflag_t)
#define __NRAT0_timer_create           (clockid_t, __clockid_t)
#define __NRAT1_timer_create           (struct sigevent *, struct sigevent *)
#define __NRAT2_timer_create           (timer_t *, __timer_t *)
#define __NRAT0_timer_gettime          (timer_t, __timer_t)
#define __NRAT1_timer_gettime          (struct itimerspec *, struct itimerspec *)
#define __NRAT0_timer_getoverrun       (timer_t, __timer_t)
#define __NRAT0_timer_settime          (timer_t, __timer_t)
#define __NRAT1_timer_settime          (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_timer_settime          (struct itimerspec const *, struct itimerspec const *)
#define __NRAT3_timer_settime          (struct itimerspec *, struct itimerspec *)
#define __NRAT0_timer_delete           (timer_t, __timer_t)
#define __NRAT0_clock_settime          (clockid_t, __clockid_t)
#define __NRAT1_clock_settime          (struct timespec const *, struct timespec const *)
#define __NRAT0_clock_gettime          (clockid_t, __clockid_t)
#define __NRAT1_clock_gettime          (struct timespec *, struct timespec *)
#define __NRAT0_clock_getres           (clockid_t, __clockid_t)
#define __NRAT1_clock_getres           (struct timespec *, struct timespec *)
#define __NRAT0_clock_nanosleep        (clockid_t, __clockid_t)
#define __NRAT1_clock_nanosleep        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_clock_nanosleep        (struct timespec const *, struct timespec const *)
#define __NRAT3_clock_nanosleep        (struct timespec *, struct timespec *)
#define __NRAT0_syslog                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_syslog                 (char const *, char const *)
#define __NRAT2_syslog                 (size_t, __size_t)
#define __NRAT0_ptrace                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_ptrace                 (pid_t, __pid_t)
#define __NRAT2_ptrace                 (void *, void *)
#define __NRAT3_ptrace                 (void *, void *)
#define __NRAT0_sched_setparam         (pid_t, __pid_t)
#define __NRAT1_sched_setparam         (struct sched_param const *, struct sched_param const *)
#define __NRAT0_sched_setscheduler     (pid_t, __pid_t)
#define __NRAT1_sched_setscheduler     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_sched_setscheduler     (struct sched_param const *, struct sched_param const *)
#define __NRAT0_sched_getscheduler     (pid_t, __pid_t)
#define __NRAT0_sched_getparam         (pid_t, __pid_t)
#define __NRAT1_sched_getparam         (struct sched_param *, struct sched_param *)
#define __NRAT0_sched_setaffinity      (pid_t, __pid_t)
#define __NRAT1_sched_setaffinity      (size_t, __size_t)
#define __NRAT2_sched_setaffinity      (struct __cpu_set_struct const *, struct __cpu_set_struct const *)
#define __NRAT0_sched_getaffinity      (pid_t, __pid_t)
#define __NRAT1_sched_getaffinity      (size_t, __size_t)
#define __NRAT2_sched_getaffinity      (struct __cpu_set_struct *, struct __cpu_set_struct *)
#define __NRAT0_sched_get_priority_max (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sched_get_priority_min (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sched_rr_get_interval  (pid_t, __pid_t)
#define __NRAT1_sched_rr_get_interval  (struct timespec *, struct timespec *)
#define __NRAT0_kill                   (pid_t, __pid_t)
#define __NRAT1_kill                   (signo_t, __signo_t)
#define __NRAT0_tkill                  (pid_t, __pid_t)
#define __NRAT1_tkill                  (signo_t, __signo_t)
#define __NRAT0_tgkill                 (pid_t, __pid_t)
#define __NRAT1_tgkill                 (pid_t, __pid_t)
#define __NRAT2_tgkill                 (signo_t, __signo_t)
#define __NRAT0_sigaltstack            (struct sigaltstack const *, struct sigaltstack const *)
#define __NRAT1_sigaltstack            (struct sigaltstack *, struct sigaltstack *)
#define __NRAT0_rt_sigsuspend          (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT1_rt_sigsuspend          (size_t, __size_t)
#define __NRAT0_rt_sigaction           (signo_t, __signo_t)
#define __NRAT1_rt_sigaction           (struct __kernel_sigaction const *, struct __kernel_sigaction const *)
#define __NRAT2_rt_sigaction           (struct __kernel_sigaction *, struct __kernel_sigaction *)
#define __NRAT3_rt_sigaction           (size_t, __size_t)
#define __NRAT0_rt_sigprocmask         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_rt_sigprocmask         (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT2_rt_sigprocmask         (struct __sigset_struct *, struct __sigset_struct *)
#define __NRAT3_rt_sigprocmask         (size_t, __size_t)
#define __NRAT0_rt_sigpending          (struct __sigset_struct *, struct __sigset_struct *)
#define __NRAT1_rt_sigpending          (size_t, __size_t)
#define __NRAT0_rt_sigtimedwait        (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT1_rt_sigtimedwait        (struct __siginfo_struct *, struct __siginfo_struct *)
#define __NRAT2_rt_sigtimedwait        (struct timespec const *, struct timespec const *)
#define __NRAT3_rt_sigtimedwait        (size_t, __size_t)
#define __NRAT0_rt_sigqueueinfo        (pid_t, __pid_t)
#define __NRAT1_rt_sigqueueinfo        (signo_t, __signo_t)
#define __NRAT2_rt_sigqueueinfo        (struct __siginfo_struct const *, struct __siginfo_struct const *)
#define __NRAT0_setpriority            (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_setpriority            (id_t, __id_t)
#define __NRAT2_setpriority            (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_getpriority            (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_getpriority            (id_t, __id_t)
#define __NRAT0_reboot                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_setregid               (gid_t, __gid_t)
#define __NRAT1_setregid               (gid_t, __gid_t)
#define __NRAT0_setgid                 (gid_t, __gid_t)
#define __NRAT0_setreuid               (uid_t, __uid_t)
#define __NRAT1_setreuid               (uid_t, __uid_t)
#define __NRAT0_setuid                 (uid_t, __uid_t)
#define __NRAT0_setresuid              (uid_t, __uid_t)
#define __NRAT1_setresuid              (uid_t, __uid_t)
#define __NRAT2_setresuid              (uid_t, __uid_t)
#define __NRAT0_getresuid              (uid_t *, __uid_t *)
#define __NRAT1_getresuid              (uid_t *, __uid_t *)
#define __NRAT2_getresuid              (uid_t *, __uid_t *)
#define __NRAT0_setresgid              (gid_t, __gid_t)
#define __NRAT1_setresgid              (gid_t, __gid_t)
#define __NRAT2_setresgid              (gid_t, __gid_t)
#define __NRAT0_getresgid              (gid_t *, __gid_t *)
#define __NRAT1_getresgid              (gid_t *, __gid_t *)
#define __NRAT2_getresgid              (gid_t *, __gid_t *)
#define __NRAT0_setfsuid               (uid_t, __uid_t)
#define __NRAT0_setfsgid               (gid_t, __gid_t)
#define __NRAT0_times                  (struct tms *, struct tms *)
#define __NRAT0_setpgid                (pid_t, __pid_t)
#define __NRAT1_setpgid                (pid_t, __pid_t)
#define __NRAT0_getpgid                (pid_t, __pid_t)
#define __NRAT0_getsid                 (pid_t, __pid_t)
#define __NRAT0_getgroups              (size_t, __size_t)
#define __NRAT1_getgroups              (gid_t *, __gid_t *)
#define __NRAT0_setgroups              (size_t, __size_t)
#define __NRAT1_setgroups              (gid_t const *, __gid_t const *)
#define __NRAT0_uname                  (struct utsname *, struct utsname *)
#define __NRAT0_sethostname            (char const *, char const *)
#define __NRAT1_sethostname            (size_t, __size_t)
#define __NRAT0_setdomainname          (char const *, char const *)
#define __NRAT1_setdomainname          (size_t, __size_t)
#define __NRAT0_getrlimit              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_getrlimit              (struct rlimit *, struct rlimit *)
#define __NRAT0_setrlimit              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_setrlimit              (struct rlimit const *, struct rlimit const *)
#define __NRAT0_getrusage              (syscall_slong_t, __syscall_slong_t)
#define __NRAT1_getrusage              (struct rusage *, struct rusage *)
#define __NRAT0_umask                  (mode_t, __mode_t)
#define __NRAT0_prctl                  (unsigned int, unsigned int)
#define __NRAT1_prctl                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_prctl                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_prctl                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_prctl                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_getcpu                 (uint32_t *, __uint32_t *)
#define __NRAT1_getcpu                 (uint32_t *, __uint32_t *)
#define __NRAT2_getcpu                 (struct getcpu_cache *, struct getcpu_cache *)
#define __NRAT0_gettimeofday           (struct timeval *, struct timeval *)
#define __NRAT1_gettimeofday           (struct timezone *, struct timezone *)
#define __NRAT0_settimeofday           (struct timeval const *, struct timeval const *)
#define __NRAT1_settimeofday           (struct timezone const *, struct timezone const *)
#define __NRAT0_adjtimex               (struct timex *, struct timex *)
#define __NRAT0_sysinfo                (struct sysinfo *, struct sysinfo *)
#define __NRAT0_mq_open                (char const *, char const *)
#define __NRAT1_mq_open                (oflag_t, __oflag_t)
#define __NRAT2_mq_open                (mode_t, __mode_t)
#define __NRAT0_mq_unlink              (char const *, char const *)
#define __NRAT0_mq_timedsend           (fd_t, __fd_t)
#define __NRAT1_mq_timedsend           (char const *, char const *)
#define __NRAT2_mq_timedsend           (size_t, __size_t)
#define __NRAT3_mq_timedsend           (uint32_t, __uint32_t)
#define __NRAT4_mq_timedsend           (struct timespec const *, struct timespec const *)
#define __NRAT0_mq_timedreceive        (fd_t, __fd_t)
#define __NRAT1_mq_timedreceive        (char *, char *)
#define __NRAT2_mq_timedreceive        (size_t, __size_t)
#define __NRAT3_mq_timedreceive        (uint32_t *, __uint32_t *)
#define __NRAT4_mq_timedreceive        (struct timespec const *, struct timespec const *)
#define __NRAT0_mq_notify              (fd_t, __fd_t)
#define __NRAT1_mq_notify              (struct sigevent const *, struct sigevent const *)
#define __NRAT0_mq_getsetattr          (fd_t, __fd_t)
#define __NRAT1_mq_getsetattr          (struct mq_attr const *, struct mq_attr const *)
#define __NRAT2_mq_getsetattr          (struct mq_attr *, struct mq_attr *)
#define __NRAT0_msgget                 (int, int)
#define __NRAT0_msgctl                 (int, int)
#define __NRAT0_msgrcv                 (int, int)
#define __NRAT0_msgsnd                 (int, int)
#define __NRAT0_semget                 (int, int)
#define __NRAT0_semctl                 (int, int)
#define __NRAT0_semtimedop             (int, int)
#define __NRAT0_semop                  (int, int)
#define __NRAT0_shmget                 (key_t, __key_t)
#define __NRAT1_shmget                 (size_t, __size_t)
#define __NRAT2_shmget                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_shmctl                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_shmctl                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_shmctl                 (struct shmid_ds *, struct shmid_ds *)
#define __NRAT0_shmat                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_shmat                  (void const *, void const *)
#define __NRAT2_shmat                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_shmdt                  (void const *, void const *)
#define __NRAT0_socket                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_socket                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_socket                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_socketpair             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_socketpair             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_socketpair             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_socketpair             (fd_t *, __fd_t *)
#define __NRAT0_bind                   (fd_t, __fd_t)
#define __NRAT1_bind                   (struct sockaddr const *, struct sockaddr const *)
#define __NRAT2_bind                   (socklen_t, __socklen_t)
#define __NRAT0_listen                 (fd_t, __fd_t)
#define __NRAT1_listen                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_accept                 (fd_t, __fd_t)
#define __NRAT1_accept                 (struct sockaddr *, struct sockaddr *)
#define __NRAT2_accept                 (socklen_t *, __socklen_t *)
#define __NRAT0_connect                (fd_t, __fd_t)
#define __NRAT1_connect                (struct sockaddr const *, struct sockaddr const *)
#define __NRAT2_connect                (socklen_t, __socklen_t)
#define __NRAT0_getsockname            (fd_t, __fd_t)
#define __NRAT1_getsockname            (struct sockaddr *, struct sockaddr *)
#define __NRAT2_getsockname            (socklen_t *, __socklen_t *)
#define __NRAT0_getpeername            (fd_t, __fd_t)
#define __NRAT1_getpeername            (struct sockaddr *, struct sockaddr *)
#define __NRAT2_getpeername            (socklen_t *, __socklen_t *)
#define __NRAT0_sendto                 (fd_t, __fd_t)
#define __NRAT1_sendto                 (void const *, void const *)
#define __NRAT2_sendto                 (size_t, __size_t)
#define __NRAT3_sendto                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_sendto                 (struct sockaddr const *, struct sockaddr const *)
#define __NRAT5_sendto                 (socklen_t, __socklen_t)
#define __NRAT0_recvfrom               (fd_t, __fd_t)
#define __NRAT1_recvfrom               (void *, void *)
#define __NRAT2_recvfrom               (size_t, __size_t)
#define __NRAT3_recvfrom               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_recvfrom               (struct sockaddr *, struct sockaddr *)
#define __NRAT5_recvfrom               (socklen_t *, __socklen_t *)
#define __NRAT0_setsockopt             (fd_t, __fd_t)
#define __NRAT1_setsockopt             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_setsockopt             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_setsockopt             (void const *, void const *)
#define __NRAT4_setsockopt             (socklen_t, __socklen_t)
#define __NRAT0_getsockopt             (fd_t, __fd_t)
#define __NRAT1_getsockopt             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_getsockopt             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_getsockopt             (void *, void *)
#define __NRAT4_getsockopt             (socklen_t *, __socklen_t *)
#define __NRAT0_shutdown               (fd_t, __fd_t)
#define __NRAT1_shutdown               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sendmsg                (fd_t, __fd_t)
#define __NRAT1_sendmsg                (struct msghdr const *, struct msghdr const *)
#define __NRAT2_sendmsg                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_recvmsg                (fd_t, __fd_t)
#define __NRAT1_recvmsg                (struct msghdr *, struct msghdr *)
#define __NRAT2_recvmsg                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_readahead              (fd_t, __fd_t)
#define __NRAT1_readahead              (uint64_t, __uint64_t)
#define __NRAT2_readahead              (size_t, __size_t)
#define __NRAT0_brk                    (void *, void *)
#define __NRAT0_munmap                 (void *, void *)
#define __NRAT1_munmap                 (size_t, __size_t)
#define __NRAT0_mremap                 (void *, void *)
#define __NRAT1_mremap                 (size_t, __size_t)
#define __NRAT2_mremap                 (size_t, __size_t)
#define __NRAT3_mremap                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_mremap                 (void *, void *)
#define __NRAT0_add_key                (int, int)
#define __NRAT0_request_key            (int, int)
#define __NRAT0_keyctl                 (int, int)
#define __NRAT0_clone                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_clone                  (void *, void *)
#define __NRAT2_clone                  (pid_t *, __pid_t *)
#define __NRAT3_clone                  (uintptr_t, __uintptr_t)
#define __NRAT4_clone                  (pid_t *, __pid_t *)
#define __NRAT0_execve                 (char const *, char const *)
#define __NRAT1_execve                 (char const *const *, char const *const *)
#define __NRAT2_execve                 (char const *const *, char const *const *)
#define __NRAT0_swapon                 (char const *, char const *)
#define __NRAT1_swapon                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_swapoff                (char const *, char const *)
#define __NRAT0_mprotect               (void *, void *)
#define __NRAT1_mprotect               (size_t, __size_t)
#define __NRAT2_mprotect               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_msync                  (void *, void *)
#define __NRAT1_msync                  (size_t, __size_t)
#define __NRAT2_msync                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_mlock                  (void const *, void const *)
#define __NRAT1_mlock                  (size_t, __size_t)
#define __NRAT0_munlock                (void const *, void const *)
#define __NRAT1_munlock                (size_t, __size_t)
#define __NRAT0_mlockall               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_mincore                (void *, void *)
#define __NRAT1_mincore                (size_t, __size_t)
#define __NRAT2_mincore                (uint8_t *, __uint8_t *)
#define __NRAT0_madvise                (void *, void *)
#define __NRAT1_madvise                (size_t, __size_t)
#define __NRAT2_madvise                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_remap_file_pages       (void *, void *)
#define __NRAT1_remap_file_pages       (size_t, __size_t)
#define __NRAT2_remap_file_pages       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_remap_file_pages       (size_t, __size_t)
#define __NRAT4_remap_file_pages       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_mbind                  (int, int)
#define __NRAT0_get_mempolicy          (int, int)
#define __NRAT0_set_mempolicy          (int, int)
#define __NRAT0_migrate_pages          (int, int)
#define __NRAT0_move_pages             (int, int)
#define __NRAT0_rt_tgsigqueueinfo      (pid_t, __pid_t)
#define __NRAT1_rt_tgsigqueueinfo      (pid_t, __pid_t)
#define __NRAT2_rt_tgsigqueueinfo      (signo_t, __signo_t)
#define __NRAT3_rt_tgsigqueueinfo      (struct __siginfo_struct const *, struct __siginfo_struct const *)
#define __NRAT0_perf_event_open        (int, int)
#define __NRAT0_accept4                (fd_t, __fd_t)
#define __NRAT1_accept4                (struct sockaddr *, struct sockaddr *)
#define __NRAT2_accept4                (socklen_t *, __socklen_t *)
#define __NRAT3_accept4                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_recvmmsg               (fd_t, __fd_t)
#define __NRAT1_recvmmsg               (struct mmsghdr *, struct mmsghdr *)
#define __NRAT2_recvmmsg               (size_t, __size_t)
#define __NRAT3_recvmmsg               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_recvmmsg               (struct timespec const *, struct timespec const *)
#define __NRAT0_wait4                  (pid_t, __pid_t)
#define __NRAT1_wait4                  (int32_t *, __int32_t *)
#define __NRAT2_wait4                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_wait4                  (struct rusage *, struct rusage *)
#define __NRAT0_prlimit64              (pid_t, __pid_t)
#define __NRAT1_prlimit64              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_prlimit64              (struct rlimit64 const *, struct __rlimit64 const *)
#define __NRAT3_prlimit64              (struct rlimit64 *, struct __rlimit64 *)
#define __NRAT0_fanotify_init          (int, int)
#define __NRAT0_fanotify_mark          (int, int)
#define __NRAT0_name_to_handle_at      (fd_t, __fd_t)
#define __NRAT1_name_to_handle_at      (char const *, char const *)
#define __NRAT2_name_to_handle_at      (struct file_handle *, struct file_handle *)
#define __NRAT3_name_to_handle_at      (int32_t *, __int32_t *)
#define __NRAT4_name_to_handle_at      (atflag_t, __atflag_t)
#define __NRAT0_open_by_handle_at      (fd_t, __fd_t)
#define __NRAT1_open_by_handle_at      (struct file_handle const *, struct file_handle const *)
#define __NRAT2_open_by_handle_at      (oflag_t, __oflag_t)
#define __NRAT0_clock_adjtime          (int, int)
#define __NRAT0_syncfs                 (fd_t, __fd_t)
#define __NRAT0_setns                  (fd_t, __fd_t)
#define __NRAT1_setns                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sendmmsg               (fd_t, __fd_t)
#define __NRAT1_sendmmsg               (struct mmsghdr *, struct mmsghdr *)
#define __NRAT2_sendmmsg               (size_t, __size_t)
#define __NRAT3_sendmmsg               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_process_vm_readv       (pid_t, __pid_t)
#define __NRAT1_process_vm_readv       (struct iovec const *, struct iovec const *)
#define __NRAT2_process_vm_readv       (size_t, __size_t)
#define __NRAT3_process_vm_readv       (struct iovec const *, struct iovec const *)
#define __NRAT4_process_vm_readv       (size_t, __size_t)
#define __NRAT5_process_vm_readv       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_process_vm_writev      (pid_t, __pid_t)
#define __NRAT1_process_vm_writev      (struct iovec const *, struct iovec const *)
#define __NRAT2_process_vm_writev      (size_t, __size_t)
#define __NRAT3_process_vm_writev      (struct iovec const *, struct iovec const *)
#define __NRAT4_process_vm_writev      (size_t, __size_t)
#define __NRAT5_process_vm_writev      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_kcmp                   (pid_t, __pid_t)
#define __NRAT1_kcmp                   (pid_t, __pid_t)
#define __NRAT2_kcmp                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_kcmp                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_kcmp                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_finit_module           (fd_t, __fd_t)
#define __NRAT1_finit_module           (char const *, char const *)
#define __NRAT2_finit_module           (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sched_setattr          (int, int)
#define __NRAT0_sched_getattr          (int, int)
#define __NRAT0_renameat2              (fd_t, __fd_t)
#define __NRAT1_renameat2              (char const *, char const *)
#define __NRAT2_renameat2              (fd_t, __fd_t)
#define __NRAT3_renameat2              (char const *, char const *)
#define __NRAT4_renameat2              (atflag_t, __atflag_t)
#define __NRAT0_seccomp                (int, int)
#define __NRAT0_getrandom              (void *, void *)
#define __NRAT1_getrandom              (size_t, __size_t)
#define __NRAT2_getrandom              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_memfd_create           (char const *, char const *)
#define __NRAT1_memfd_create           (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_bpf                    (int, int)
#define __NRAT0_execveat               (fd_t, __fd_t)
#define __NRAT1_execveat               (char const *, char const *)
#define __NRAT2_execveat               (char const *const *, char const *const *)
#define __NRAT3_execveat               (char const *const *, char const *const *)
#define __NRAT4_execveat               (atflag_t, __atflag_t)
#define __NRAT0_userfaultfd            (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_membarrier             (int, int)
#define __NRAT0_mlock2                 (void const *, void const *)
#define __NRAT1_mlock2                 (size_t, __size_t)
#define __NRAT2_mlock2                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_open                   (char const *, char const *)
#define __NRAT1_open                   (oflag_t, __oflag_t)
#define __NRAT2_open                   (mode_t, __mode_t)
#define __NRAT0_link                   (char const *, char const *)
#define __NRAT1_link                   (char const *, char const *)
#define __NRAT0_unlink                 (char const *, char const *)
#define __NRAT0_mknod                  (char const *, char const *)
#define __NRAT1_mknod                  (mode_t, __mode_t)
#define __NRAT2_mknod                  (dev_t, __dev_t)
#define __NRAT0_chmod                  (char const *, char const *)
#define __NRAT1_chmod                  (mode_t, __mode_t)
#define __NRAT0_chown                  (char const *, char const *)
#define __NRAT1_chown                  (uid_t, __uid_t)
#define __NRAT2_chown                  (gid_t, __gid_t)
#define __NRAT0_mkdir                  (char const *, char const *)
#define __NRAT1_mkdir                  (mode_t, __mode_t)
#define __NRAT0_rmdir                  (char const *, char const *)
#define __NRAT0_lchown                 (char const *, char const *)
#define __NRAT1_lchown                 (uid_t, __uid_t)
#define __NRAT2_lchown                 (gid_t, __gid_t)
#define __NRAT0_access                 (char const *, char const *)
#define __NRAT1_access                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_rename                 (char const *, char const *)
#define __NRAT1_rename                 (char const *, char const *)
#define __NRAT0_readlink               (char const *, char const *)
#define __NRAT1_readlink               (char *, char *)
#define __NRAT2_readlink               (size_t, __size_t)
#define __NRAT0_symlink                (char const *, char const *)
#define __NRAT1_symlink                (char const *, char const *)
#define __NRAT0_utimes                 (char const *, char const *)
#define __NRAT1_utimes                 (struct timeval const *, struct timeval const *)
#define __NRAT0_pipe                   (fd_t *, __fd_t *)
#define __NRAT0_dup2                   (fd_t, __fd_t)
#define __NRAT1_dup2                   (fd_t, __fd_t)
#define __NRAT0_epoll_create           (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_eventfd                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_signalfd               (fd_t, __fd_t)
#define __NRAT1_signalfd               (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT2_signalfd               (size_t, __size_t)
#define __NRAT0_sendfile               (fd_t, __fd_t)
#define __NRAT1_sendfile               (fd_t, __fd_t)
#define __NRAT2_sendfile               (syscall_ulong_t *, __syscall_ulong_t *)
#define __NRAT3_sendfile               (size_t, __size_t)
#define __NRAT0_ftruncate              (fd_t, __fd_t)
#define __NRAT1_ftruncate              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_truncate               (char const *, char const *)
#define __NRAT1_truncate               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_stat                   (char const *, char const *)
#define __NRAT1_stat                   (struct linux_stat *, struct linux_stat *)
#define __NRAT0_lstat                  (char const *, char const *)
#define __NRAT1_lstat                  (struct linux_stat *, struct linux_stat *)
#define __NRAT0_fstat                  (fd_t, __fd_t)
#define __NRAT1_fstat                  (struct linux_stat *, struct linux_stat *)
#define __NRAT0_fcntl                  (fd_t, __fd_t)
#define __NRAT1_fcntl                  (fcntl_t, __fcntl_t)
#define __NRAT2_fcntl                  (void *, void *)
#define __NRAT0_fadvise64              (int, int)
#define __NRAT0_newfstatat             (fd_t, __fd_t)
#define __NRAT1_newfstatat             (char const *, char const *)
#define __NRAT2_newfstatat             (struct linux64_stat32 *, struct linux64_stat32 *)
#define __NRAT3_newfstatat             (atflag_t, __atflag_t)
#define __NRAT0_fstatfs                (fd_t, __fd_t)
#define __NRAT1_fstatfs                (struct statfs *, struct statfs *)
#define __NRAT0_statfs                 (char const *, char const *)
#define __NRAT1_statfs                 (struct statfs *, struct statfs *)
#define __NRAT0_lseek                  (fd_t, __fd_t)
#define __NRAT1_lseek                  (syscall_slong_t, __syscall_slong_t)
#define __NRAT2_lseek                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_mmap                   (void *, void *)
#define __NRAT1_mmap                   (size_t, __size_t)
#define __NRAT2_mmap                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_mmap                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_mmap                   (fd_t, __fd_t)
#define __NRAT5_mmap                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_alarm                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_time                   (time32_t *, __time32_t *)
#define __NRAT0_utime                  (char const *, char const *)
#define __NRAT1_utime                  (struct utimbuf const *, struct utimbuf const *)
#define __NRAT0_creat                  (char const *, char const *)
#define __NRAT1_creat                  (mode_t, __mode_t)
#define __NRAT0_getdents               (fd_t, __fd_t)
#define __NRAT1_getdents               (struct linux_dirent *, struct linux_dirent *)
#define __NRAT2_getdents               (size_t, __size_t)
#define __NRAT0_futimesat              (fd_t, __fd_t)
#define __NRAT1_futimesat              (char const *, char const *)
#define __NRAT2_futimesat              (struct timeval const *, struct timeval const *)
#define __NRAT0_select                 (size_t, __size_t)
#define __NRAT1_select                 (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT2_select                 (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT3_select                 (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT4_select                 (struct timeval *, struct timeval *)
#define __NRAT0_poll                   (struct pollfd *, struct pollfd *)
#define __NRAT1_poll                   (size_t, __size_t)
#define __NRAT2_poll                   (syscall_slong_t, __syscall_slong_t)
#define __NRAT0_epoll_wait             (fd_t, __fd_t)
#define __NRAT1_epoll_wait             (struct epoll_event *, struct epoll_event *)
#define __NRAT2_epoll_wait             (size_t, __size_t)
#define __NRAT3_epoll_wait             (syscall_slong_t, __syscall_slong_t)
#define __NRAT0_ustat                  (dev_t, __dev_t)
#define __NRAT1_ustat                  (struct ustat *, struct ustat *)
#define __NRAT0_oldwait4               (pid_t, __pid_t)
#define __NRAT1_oldwait4               (int32_t *, __int32_t *)
#define __NRAT2_oldwait4               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_oldwait4               (struct rusage *, struct rusage *)
#define __NRAT0_recv                   (fd_t, __fd_t)
#define __NRAT1_recv                   (void *, void *)
#define __NRAT2_recv                   (size_t, __size_t)
#define __NRAT3_recv                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_send                   (fd_t, __fd_t)
#define __NRAT1_send                   (void const *, void const *)
#define __NRAT2_send                   (size_t, __size_t)
#define __NRAT3_send                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_bdflush                (int, int)
#define __NRAT0_umount                 (char const *, char const *)
#define __NRAT0_uselib                 (char const *, char const *)
#define __NRAT0__sysctl                (int, int)
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_TYPES */
#endif /* __WANT_SYSCALL_ARGUMENT_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT LIST MAKING                                         */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_MAKER
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NRAM_io_setup(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (int)a
#define __NRAM_io_destroy(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (int)a
#define __NRAM_io_submit(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (int)a
#define __NRAM_io_cancel(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (int)a
#define __NRAM_io_getevents(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (int)a
#define __NRAM_setxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_lsetxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_fsetxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_getxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_lgetxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_fgetxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_listxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (char const *)a, (char *)b, (__size_t)c
#define __NRAM_llistxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (char const *)a, (char *)b, (__size_t)c
#define __NRAM_flistxattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__fd_t)a, (char *)b, (__size_t)c
#define __NRAM_removexattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (char const *)a, (char const *)b
#define __NRAM_lremovexattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (char const *)a, (char const *)b
#define __NRAM_fremovexattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__fd_t)a, (char const *)b
#define __NRAM_getcwd(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char *)a, (__size_t)b
#define __NRAM_lookup_dcookie(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)         (int)a
#define __NRAM_eventfd2(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAM_epoll_create1(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (__syscall_ulong_t)a
#define __NRAM_epoll_ctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (__syscall_ulong_t)b, (__fd_t)c, (struct epoll_event *)d
#define __NRAM_epoll_pwait(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d, (struct __sigset_struct const *)e, (__size_t)f
#define __NRAM_dup(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                    (__fd_t)a
#define __NRAM_dup3(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__fd_t)a, (__fd_t)b, (__oflag_t)c
#define __NRAM_inotify_init1(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (__syscall_ulong_t)a
#define __NRAM_inotify_add_watch(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)      (__fd_t)a, (char const *)b, (__uint32_t)c
#define __NRAM_inotify_rm_watch(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)       (__fd_t)a, (int)b
#define __NRAM_ioctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (__ioctl_t)b, (void *)c
#define __NRAM_ioprio_set(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_ioprio_get(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAM_flock(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_mknodat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d
#define __NRAM_mkdirat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (char const *)b, (__mode_t)c
#define __NRAM_unlinkat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NRAM_symlinkat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (char const *)a, (__fd_t)b, (char const *)c
#define __NRAM_linkat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NRAM_renameat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d
#define __NRAM_umount2(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (char const *)a, (__syscall_ulong_t)b
#define __NRAM_mount(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (char const *)b, (char const *)c, (__syscall_ulong_t)d, (void const *)e
#define __NRAM_pivot_root(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (int)a
#define __NRAM_nfsservctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (int)a
#define __NRAM_fallocate(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAM_faccessat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NRAM_chdir(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a
#define __NRAM_fchdir(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a
#define __NRAM_chroot(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a
#define __NRAM_fchmod(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (__mode_t)b
#define __NRAM_fchmodat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NRAM_fchownat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (char const *)b, (__uid_t)c, (__gid_t)d, (__atflag_t)e
#define __NRAM_fchown(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (__uid_t)b, (__gid_t)c
#define __NRAM_openat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (char const *)b, (__oflag_t)c, (__mode_t)d
#define __NRAM_close(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a
#define __NRAM_vhangup(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                /* nothing */
#define __NRAM_pipe2(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t *)a, (__oflag_t)b
#define __NRAM_quotactl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (int)a
#define __NRAM_getdents64(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__fd_t)a, (struct linux_dirent64 *)b, (__size_t)c
#define __NRAM_read(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__fd_t)a, (void *)b, (__size_t)c
#define __NRAM_write(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (void const *)b, (__size_t)c
#define __NRAM_readv(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (struct iovec const *)b, (__size_t)c
#define __NRAM_writev(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (struct iovec const *)b, (__size_t)c
#define __NRAM_pread64(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)d
#define __NRAM_pwrite64(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)d
#define __NRAM_preadv(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)d
#define __NRAM_pwritev(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__uint64_t)d
#define __NRAM_pselect6(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct timespec const *)e, (struct sigset_with_size const *)f
#define __NRAM_ppoll(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (struct pollfd *)a, (__size_t)b, (struct timespec const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NRAM_signalfd4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_vmsplice(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (struct iovec const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_splice(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (__uint64_t *)b, (__fd_t)c, (__uint64_t *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_tee(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                    (__fd_t)a, (__fd_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_readlinkat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__fd_t)a, (char const *)b, (char *)c, (__size_t)d
#define __NRAM_sync(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   /* nothing */
#define __NRAM_fsync(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a
#define __NRAM_fdatasync(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a
#define __NRAM_sync_file_range(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (__fd_t)a, (__uint64_t)b, (__uint64_t)c, (__syscall_ulong_t)d
#define __NRAM_timerfd_create(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)         (__clockid_t)a, (__syscall_ulong_t)b
#define __NRAM_timerfd_settime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (__fd_t)a, (__syscall_ulong_t)b, (struct itimerspec const *)c, (struct itimerspec *)d
#define __NRAM_timerfd_gettime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (__fd_t)a, (struct itimerspec *)b
#define __NRAM_utimensat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (char const *)b, (struct timespec const *)c, (__atflag_t)d
#define __NRAM_acct(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (char const *)a
#define __NRAM_capget(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_capset(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_personality(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (int)a
#define __NRAM_exit(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__syscall_ulong_t)a
#define __NRAM_exit_group(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__syscall_ulong_t)a
#define __NRAM_waitid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__syscall_ulong_t)a, (__id_t)b, (struct __siginfo_struct *)c, (__syscall_ulong_t)d, (struct rusage *)e
#define __NRAM_set_tid_address(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (__pid_t *)a
#define __NRAM_unshare(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__syscall_ulong_t)a
#define __NRAM_futex(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct timespec const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NRAM_set_robust_list(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (int)a
#define __NRAM_get_robust_list(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (int)a
#define __NRAM_nanosleep(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (struct timespec const *)a, (struct timespec *)b
#define __NRAM_getitimer(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__syscall_ulong_t)a, (struct itimerval *)b
#define __NRAM_setitimer(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__syscall_ulong_t)a, (struct itimerval const *)b, (struct itimerval *)c
#define __NRAM_kexec_load(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (int)a
#define __NRAM_init_module(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (void const *)a, (__size_t)b, (char const *)c
#define __NRAM_delete_module(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (char const *)a, (__oflag_t)b
#define __NRAM_timer_create(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__clockid_t)a, (struct sigevent *)b, (__timer_t *)c
#define __NRAM_timer_gettime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (__timer_t)a, (struct itimerspec *)b
#define __NRAM_timer_getoverrun(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)       (__timer_t)a
#define __NRAM_timer_settime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (__timer_t)a, (__syscall_ulong_t)b, (struct itimerspec const *)c, (struct itimerspec *)d
#define __NRAM_timer_delete(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__timer_t)a
#define __NRAM_clock_settime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (__clockid_t)a, (struct timespec const *)b
#define __NRAM_clock_gettime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (__clockid_t)a, (struct timespec *)b
#define __NRAM_clock_getres(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__clockid_t)a, (struct timespec *)b
#define __NRAM_clock_nanosleep(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (__clockid_t)a, (__syscall_ulong_t)b, (struct timespec const *)c, (struct timespec *)d
#define __NRAM_syslog(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__syscall_ulong_t)a, (char const *)b, (__size_t)c
#define __NRAM_ptrace(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__syscall_ulong_t)a, (__pid_t)b, (void *)c, (void *)d
#define __NRAM_sched_setparam(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)         (__pid_t)a, (struct sched_param const *)b
#define __NRAM_sched_setscheduler(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)     (__pid_t)a, (__syscall_ulong_t)b, (struct sched_param const *)c
#define __NRAM_sched_getscheduler(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)     (__pid_t)a
#define __NRAM_sched_getparam(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)         (__pid_t)a, (struct sched_param *)b
#define __NRAM_sched_setaffinity(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)      (__pid_t)a, (__size_t)b, (struct __cpu_set_struct const *)c
#define __NRAM_sched_getaffinity(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)      (__pid_t)a, (__size_t)b, (struct __cpu_set_struct *)c
#define __NRAM_sched_yield(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            /* nothing */
#define __NRAM_sched_get_priority_max(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z) (__syscall_ulong_t)a
#define __NRAM_sched_get_priority_min(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z) (__syscall_ulong_t)a
#define __NRAM_sched_rr_get_interval(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)  (__pid_t)a, (struct timespec *)b
#define __NRAM_restart_syscall(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        /* nothing */
#define __NRAM_kill(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__pid_t)a, (__signo_t)b
#define __NRAM_tkill(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__pid_t)a, (__signo_t)b
#define __NRAM_tgkill(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__pid_t)a, (__pid_t)b, (__signo_t)c
#define __NRAM_sigaltstack(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (struct sigaltstack const *)a, (struct sigaltstack *)b
#define __NRAM_rt_sigsuspend(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (struct __sigset_struct const *)a, (__size_t)b
#define __NRAM_rt_sigaction(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__signo_t)a, (struct __kernel_sigaction const *)b, (struct __kernel_sigaction *)c, (__size_t)d
#define __NRAM_rt_sigprocmask(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)         (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c, (__size_t)d
#define __NRAM_rt_sigpending(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (struct __sigset_struct *)a, (__size_t)b
#define __NRAM_rt_sigtimedwait(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (struct __sigset_struct const *)a, (struct __siginfo_struct *)b, (struct timespec const *)c, (__size_t)d
#define __NRAM_rt_sigqueueinfo(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (__pid_t)a, (__signo_t)b, (struct __siginfo_struct const *)c
#define __NRAM_rt_sigreturn(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           /* nothing */
#define __NRAM_setpriority(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (__syscall_ulong_t)a, (__id_t)b, (__syscall_ulong_t)c
#define __NRAM_getpriority(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (__syscall_ulong_t)a, (__id_t)b
#define __NRAM_reboot(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__syscall_ulong_t)a
#define __NRAM_setregid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__gid_t)a, (__gid_t)b
#define __NRAM_setgid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__gid_t)a
#define __NRAM_setreuid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__uid_t)a, (__uid_t)b
#define __NRAM_setuid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__uid_t)a
#define __NRAM_setresuid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__uid_t)a, (__uid_t)b, (__uid_t)c
#define __NRAM_getresuid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__uid_t *)a, (__uid_t *)b, (__uid_t *)c
#define __NRAM_setresgid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__gid_t)a, (__gid_t)b, (__gid_t)c
#define __NRAM_getresgid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__gid_t *)a, (__gid_t *)b, (__gid_t *)c
#define __NRAM_setfsuid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__uid_t)a
#define __NRAM_setfsgid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__gid_t)a
#define __NRAM_times(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (struct tms *)a
#define __NRAM_setpgid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__pid_t)a, (__pid_t)b
#define __NRAM_getpgid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__pid_t)a
#define __NRAM_getsid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__pid_t)a
#define __NRAM_setsid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 /* nothing */
#define __NRAM_getgroups(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__size_t)a, (__gid_t *)b
#define __NRAM_setgroups(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__size_t)a, (__gid_t const *)b
#define __NRAM_uname(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (struct utsname *)a
#define __NRAM_sethostname(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (char const *)a, (__size_t)b
#define __NRAM_setdomainname(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (char const *)a, (__size_t)b
#define __NRAM_getrlimit(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__syscall_ulong_t)a, (struct rlimit *)b
#define __NRAM_setrlimit(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__syscall_ulong_t)a, (struct rlimit const *)b
#define __NRAM_getrusage(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__syscall_slong_t)a, (struct rusage *)b
#define __NRAM_umask(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__mode_t)a
#define __NRAM_prctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (unsigned int)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAM_getcpu(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__uint32_t *)a, (__uint32_t *)b, (struct getcpu_cache *)c
#define __NRAM_gettimeofday(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (struct timeval *)a, (struct timezone *)b
#define __NRAM_settimeofday(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (struct timeval const *)a, (struct timezone const *)b
#define __NRAM_adjtimex(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (struct timex *)a
#define __NRAM_getpid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 /* nothing */
#define __NRAM_getppid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                /* nothing */
#define __NRAM_getuid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 /* nothing */
#define __NRAM_geteuid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                /* nothing */
#define __NRAM_getgid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 /* nothing */
#define __NRAM_getegid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                /* nothing */
#define __NRAM_gettid(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 /* nothing */
#define __NRAM_sysinfo(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (struct sysinfo *)a
#define __NRAM_mq_open(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NRAM_mq_unlink(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (char const *)a
#define __NRAM_mq_timedsend(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__fd_t)a, (char const *)b, (__size_t)c, (__uint32_t)d, (struct timespec const *)e
#define __NRAM_mq_timedreceive(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (__fd_t)a, (char *)b, (__size_t)c, (__uint32_t *)d, (struct timespec const *)e
#define __NRAM_mq_notify(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (struct sigevent const *)b
#define __NRAM_mq_getsetattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (__fd_t)a, (struct mq_attr const *)b, (struct mq_attr *)c
#define __NRAM_msgget(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_msgctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_msgrcv(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_msgsnd(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_semget(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_semctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_semtimedop(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (int)a
#define __NRAM_semop(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (int)a
#define __NRAM_shmget(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__key_t)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_shmctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (struct shmid_ds *)c
#define __NRAM_shmat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__syscall_ulong_t)a, (void const *)b, (__syscall_ulong_t)c
#define __NRAM_shmdt(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (void const *)a
#define __NRAM_socket(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_socketpair(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__fd_t *)d
#define __NRAM_bind(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NRAM_listen(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_accept(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NRAM_connect(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NRAM_getsockname(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NRAM_getpeername(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NRAM_sendto(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a, (void const *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr const *)e, (__socklen_t)f
#define __NRAM_recvfrom(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (void *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr *)e, (__socklen_t *)f
#define __NRAM_setsockopt(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void const *)d, (__socklen_t)e
#define __NRAM_getsockopt(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void *)d, (__socklen_t *)e
#define __NRAM_shutdown(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_sendmsg(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (struct msghdr const *)b, (__syscall_ulong_t)c
#define __NRAM_recvmsg(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (struct msghdr *)b, (__syscall_ulong_t)c
#define __NRAM_readahead(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (__uint64_t)b, (__size_t)c
#define __NRAM_brk(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                    (void *)a
#define __NRAM_munmap(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (void *)a, (__size_t)b
#define __NRAM_mremap(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (void *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d, (void *)e
#define __NRAM_add_key(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (int)a
#define __NRAM_request_key(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (int)a
#define __NRAM_keyctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (int)a
#define __NRAM_clone(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__syscall_ulong_t)a, (void *)b, (__pid_t *)c, (__uintptr_t)d, (__pid_t *)e
#define __NRAM_execve(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a, (char const *const *)b, (char const *const *)c
#define __NRAM_swapon(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a, (__syscall_ulong_t)b
#define __NRAM_swapoff(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (char const *)a
#define __NRAM_mprotect(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_msync(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_mlock(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (void const *)a, (__size_t)b
#define __NRAM_munlock(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (void const *)a, (__size_t)b
#define __NRAM_mlockall(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__syscall_ulong_t)a
#define __NRAM_munlockall(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             /* nothing */
#define __NRAM_mincore(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (void *)a, (__size_t)b, (__uint8_t *)c
#define __NRAM_madvise(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_remap_file_pages(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)       (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_mbind(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (int)a
#define __NRAM_get_mempolicy(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_set_mempolicy(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_migrate_pages(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_move_pages(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (int)a
#define __NRAM_rt_tgsigqueueinfo(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)      (__pid_t)a, (__pid_t)b, (__signo_t)c, (struct __siginfo_struct const *)d
#define __NRAM_perf_event_open(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)        (int)a
#define __NRAM_accept4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c, (__syscall_ulong_t)d
#define __NRAM_recvmmsg(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d, (struct timespec const *)e
#define __NRAM_wait4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct rusage *)d
#define __NRAM_prlimit64(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__pid_t)a, (__syscall_ulong_t)b, (struct __rlimit64 const *)c, (struct __rlimit64 *)d
#define __NRAM_fanotify_init(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_fanotify_mark(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_name_to_handle_at(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)      (__fd_t)a, (char const *)b, (struct file_handle *)c, (__int32_t *)d, (__atflag_t)e
#define __NRAM_open_by_handle_at(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)      (__fd_t)a, (struct file_handle const *)b, (__oflag_t)c
#define __NRAM_clock_adjtime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_syncfs(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__fd_t)a
#define __NRAM_setns(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_sendmmsg(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (struct mmsghdr *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_process_vm_readv(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)       (__pid_t)a, (struct iovec const *)b, (__size_t)c, (struct iovec const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_process_vm_writev(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)      (__pid_t)a, (struct iovec const *)b, (__size_t)c, (struct iovec const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_kcmp(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAM_finit_module(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NRAM_sched_setattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_sched_getattr(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)          (int)a
#define __NRAM_renameat2(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NRAM_seccomp(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (int)a
#define __NRAM_getrandom(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_memfd_create(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (char const *)a, (__syscall_ulong_t)b
#define __NRAM_bpf(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                    (int)a
#define __NRAM_execveat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (char const *)b, (char const *const *)c, (char const *const *)d, (__atflag_t)e
#define __NRAM_userfaultfd(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)            (__syscall_ulong_t)a
#define __NRAM_membarrier(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (int)a
#define __NRAM_mlock2(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (void const *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_open(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NRAM_link(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (char const *)a, (char const *)b
#define __NRAM_unlink(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a
#define __NRAM_mknod(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (__mode_t)b, (__dev_t)c
#define __NRAM_chmod(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (__mode_t)b
#define __NRAM_chown(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (__uid_t)b, (__gid_t)c
#define __NRAM_mkdir(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (__mode_t)b
#define __NRAM_rmdir(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a
#define __NRAM_lchown(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a, (__uid_t)b, (__gid_t)c
#define __NRAM_access(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a, (__syscall_ulong_t)b
#define __NRAM_rename(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a, (char const *)b
#define __NRAM_readlink(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (char const *)a, (char *)b, (__size_t)c
#define __NRAM_symlink(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (char const *)a, (char const *)b
#define __NRAM_utimes(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a, (struct timeval const *)b
#define __NRAM_pipe(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__fd_t *)a
#define __NRAM_dup2(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__fd_t)a, (__fd_t)b
#define __NRAM_epoll_create(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           (__syscall_ulong_t)a
#define __NRAM_inotify_init(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)           /* nothing */
#define __NRAM_eventfd(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__syscall_ulong_t)a
#define __NRAM_signalfd(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c
#define __NRAM_sendfile(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (__fd_t)b, (__syscall_ulong_t *)c, (__size_t)d
#define __NRAM_ftruncate(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_truncate(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (char const *)a, (__syscall_ulong_t)b
#define __NRAM_stat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (char const *)a, (struct linux_stat *)b
#define __NRAM_lstat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (struct linux_stat *)b
#define __NRAM_fstat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (struct linux_stat *)b
#define __NRAM_fcntl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (__fcntl_t)b, (void *)c
#define __NRAM_fadvise64(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (int)a
#define __NRAM_newfstatat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__fd_t)a, (char const *)b, (struct linux64_stat32 *)c, (__atflag_t)d
#define __NRAM_fstatfs(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (__fd_t)a, (struct statfs *)b
#define __NRAM_statfs(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a, (struct statfs *)b
#define __NRAM_lseek(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__fd_t)a, (__syscall_slong_t)b, (__syscall_ulong_t)c
#define __NRAM_mmap(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NRAM_alarm(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__syscall_ulong_t)a
#define __NRAM_getpgrp(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                /* nothing */
#define __NRAM_pause(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  /* nothing */
#define __NRAM_time(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__time32_t *)a
#define __NRAM_utime(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (struct utimbuf const *)b
#define __NRAM_creat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (char const *)a, (__mode_t)b
#define __NRAM_getdents(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__fd_t)a, (struct linux_dirent *)b, (__size_t)c
#define __NRAM_futimesat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)              (__fd_t)a, (char const *)b, (struct timeval const *)c
#define __NRAM_select(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct timeval *)e
#define __NRAM_poll(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (struct pollfd *)a, (__size_t)b, (__syscall_slong_t)c
#define __NRAM_epoll_wait(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)             (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d
#define __NRAM_ustat(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  (__dev_t)a, (struct ustat *)b
#define __NRAM_vfork(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                  /* nothing */
#define __NRAM_oldwait4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)               (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct rusage *)d
#define __NRAM_recv(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__fd_t)a, (void *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_send(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   (__fd_t)a, (void const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_bdflush(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (int)a
#define __NRAM_umount(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a
#define __NRAM_uselib(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                 (char const *)a
#define __NRAM__sysctl(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                (int)a
#define __NRAM_fork(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)                   /* nothing */
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_MAKER */


/************************************************************************/
/* SYSCALL ARGUMENT LIST PACKING                                        */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NRAP_io_setup(a)                                                                                          (__syscall_ulong_t)a
#define __NRAP_io_destroy(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_io_submit(a)                                                                                         (__syscall_ulong_t)a
#define __NRAP_io_cancel(a)                                                                                         (__syscall_ulong_t)a
#define __NRAP_io_getevents(a)                                                                                      (__syscall_ulong_t)a
#define __NRAP_setxattr(a, b, c, d, e)                                                                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_lsetxattr(a, b, c, d, e)                                                                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fsetxattr(a, b, c, d, e)                                                                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_getxattr(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_lgetxattr(a, b, c, d)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fgetxattr(a, b, c, d)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_listxattr(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_llistxattr(a, b, c)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_flistxattr(a, b, c)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_removexattr(a, b)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lremovexattr(a, b)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fremovexattr(a, b)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getcwd(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lookup_dcookie(a)                                                                                    (__syscall_ulong_t)a
#define __NRAP_eventfd2(a, b)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_epoll_create1(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_epoll_ctl(a, b, c, d)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_epoll_pwait(a, b, c, d, e, f)                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_dup(a)                                                                                               (__syscall_ulong_t)a
#define __NRAP_dup3(a, b, c)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_inotify_init1(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_inotify_add_watch(a, b, c)                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_inotify_rm_watch(a, b)                                                                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ioctl(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_ioprio_set(a, b, c)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_ioprio_get(a, b)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_flock(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mknodat(a, b, c, d)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_mkdirat(a, b, c)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_unlinkat(a, b, c)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_symlinkat(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_linkat(a, b, c, d, e)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_renameat(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_umount2(a, b)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mount(a, b, c, d, e)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_pivot_root(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_nfsservctl(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_fallocate(a, b, c, d)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_faccessat(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chdir(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_fchdir(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_chroot(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_fchmod(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fchmodat(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fchownat(a, b, c, d, e)                                                                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fchown(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_openat(a, b, c, d)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_close(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_vhangup()                                                                                            /* nothing */
#define __NRAP_pipe2(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_quotactl(a)                                                                                          (__syscall_ulong_t)a
#define __NRAP_getdents64(a, b, c)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_read(a, b, c)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_write(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_readv(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_writev(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_pread64(a, b, c, d)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pwrite64(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_preadv(a, b, c, d)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pwritev(a, b, c, d)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pselect6(a, b, c, d, e, f)                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_ppoll(a, b, c, d, e)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_signalfd4(a, b, c, d)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_vmsplice(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_splice(a, b, c, d, e, f)                                                                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_tee(a, b, c, d)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_readlinkat(a, b, c, d)                                                                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_sync()                                                                                               /* nothing */
#define __NRAP_fsync(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_fdatasync(a)                                                                                         (__syscall_ulong_t)a
#define __NRAP_sync_file_range(a, b, c, d)                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_create(a, b)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_timerfd_settime(a, b, c, d)                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_gettime(a, b)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_utimensat(a, b, c, d)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_acct(a)                                                                                              (__syscall_ulong_t)a
#define __NRAP_capget(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_capset(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_personality(a)                                                                                       (__syscall_ulong_t)a
#define __NRAP_exit(a)                                                                                              (__syscall_ulong_t)a
#define __NRAP_exit_group(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_waitid(a, b, c, d, e)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_set_tid_address(a)                                                                                   (__syscall_ulong_t)a
#define __NRAP_unshare(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_futex(a, b, c, d, e, f)                                                                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_set_robust_list(a)                                                                                   (__syscall_ulong_t)a
#define __NRAP_get_robust_list(a)                                                                                   (__syscall_ulong_t)a
#define __NRAP_nanosleep(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getitimer(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setitimer(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_kexec_load(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_init_module(a, b, c)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_delete_module(a, b)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_timer_create(a, b, c)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_timer_gettime(a, b)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_timer_getoverrun(a)                                                                                  (__syscall_ulong_t)a
#define __NRAP_timer_settime(a, b, c, d)                                                                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timer_delete(a)                                                                                      (__syscall_ulong_t)a
#define __NRAP_clock_settime(a, b)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_gettime(a, b)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_getres(a, b)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_nanosleep(a, b, c, d)                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_syslog(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_ptrace(a, b, c, d)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_sched_setparam(a, b)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sched_setscheduler(a, b, c)                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_getscheduler(a)                                                                                (__syscall_ulong_t)a
#define __NRAP_sched_getparam(a, b)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sched_setaffinity(a, b, c)                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_getaffinity(a, b, c)                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_yield()                                                                                        /* nothing */
#define __NRAP_sched_get_priority_max(a)                                                                            (__syscall_ulong_t)a
#define __NRAP_sched_get_priority_min(a)                                                                            (__syscall_ulong_t)a
#define __NRAP_sched_rr_get_interval(a, b)                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_restart_syscall()                                                                                    /* nothing */
#define __NRAP_kill(a, b)                                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_tkill(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_tgkill(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sigaltstack(a, b)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rt_sigsuspend(a, b)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rt_sigaction(a, b, c, d)                                                                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigprocmask(a, b, c, d)                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigpending(a, b)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rt_sigtimedwait(a, b, c, d)                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigqueueinfo(a, b, c)                                                                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_rt_sigreturn()                                                                                       /* nothing */
#define __NRAP_setpriority(a, b, c)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpriority(a, b)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_reboot(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_setregid(a, b)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setgid(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_setreuid(a, b)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setuid(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_setresuid(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresuid(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setresgid(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresgid(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setfsuid(a)                                                                                          (__syscall_ulong_t)a
#define __NRAP_setfsgid(a)                                                                                          (__syscall_ulong_t)a
#define __NRAP_times(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_setpgid(a, b)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getpgid(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_getsid(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_setsid()                                                                                             /* nothing */
#define __NRAP_getgroups(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setgroups(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_uname(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_sethostname(a, b)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setdomainname(a, b)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getrlimit(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setrlimit(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getrusage(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_umask(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_prctl(a, b, c, d, e)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_getcpu(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_gettimeofday(a, b)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_settimeofday(a, b)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_adjtimex(a)                                                                                          (__syscall_ulong_t)a
#define __NRAP_getpid()                                                                                             /* nothing */
#define __NRAP_getppid()                                                                                            /* nothing */
#define __NRAP_getuid()                                                                                             /* nothing */
#define __NRAP_geteuid()                                                                                            /* nothing */
#define __NRAP_getgid()                                                                                             /* nothing */
#define __NRAP_getegid()                                                                                            /* nothing */
#define __NRAP_gettid()                                                                                             /* nothing */
#define __NRAP_sysinfo(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_mq_open(a, b, c)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mq_unlink(a)                                                                                         (__syscall_ulong_t)a
#define __NRAP_mq_timedsend(a, b, c, d, e)                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_mq_timedreceive(a, b, c, d, e)                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_mq_notify(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mq_getsetattr(a, b, c)                                                                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_msgget(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_msgctl(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_msgrcv(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_msgsnd(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_semget(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_semctl(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_semtimedop(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_semop(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_shmget(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shmctl(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shmat(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shmdt(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_socket(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_socketpair(a, b, c, d)                                                                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_bind(a, b, c)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_listen(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_accept(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_connect(a, b, c)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getsockname(a, b, c)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpeername(a, b, c)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sendto(a, b, c, d, e, f)                                                                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_recvfrom(a, b, c, d, e, f)                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_setsockopt(a, b, c, d, e)                                                                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_getsockopt(a, b, c, d, e)                                                                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_shutdown(a, b)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sendmsg(a, b, c)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_recvmsg(a, b, c)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_readahead(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_brk(a)                                                                                               (__syscall_ulong_t)a
#define __NRAP_munmap(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mremap(a, b, c, d, e)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_add_key(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_request_key(a)                                                                                       (__syscall_ulong_t)a
#define __NRAP_keyctl(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_clone(a, b, c, d, e)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_execve(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_swapon(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_swapoff(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_mprotect(a, b, c)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_msync(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mlock(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_munlock(a, b)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mlockall(a)                                                                                          (__syscall_ulong_t)a
#define __NRAP_munlockall()                                                                                         /* nothing */
#define __NRAP_mincore(a, b, c)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_madvise(a, b, c)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_remap_file_pages(a, b, c, d, e)                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_mbind(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_get_mempolicy(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_set_mempolicy(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_migrate_pages(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_move_pages(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_rt_tgsigqueueinfo(a, b, c, d)                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_perf_event_open(a)                                                                                   (__syscall_ulong_t)a
#define __NRAP_accept4(a, b, c, d)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_recvmmsg(a, b, c, d, e)                                                                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_wait4(a, b, c, d)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_prlimit64(a, b, c, d)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fanotify_init(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_fanotify_mark(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_name_to_handle_at(a, b, c, d, e)                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_open_by_handle_at(a, b, c)                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_clock_adjtime(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_syncfs(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_setns(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sendmmsg(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_process_vm_readv(a, b, c, d, e, f)                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_process_vm_writev(a, b, c, d, e, f)                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_kcmp(a, b, c, d, e)                                                                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_finit_module(a, b, c)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_setattr(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_sched_getattr(a)                                                                                     (__syscall_ulong_t)a
#define __NRAP_renameat2(a, b, c, d, e)                                                                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_seccomp(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_getrandom(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_memfd_create(a, b)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_bpf(a)                                                                                               (__syscall_ulong_t)a
#define __NRAP_execveat(a, b, c, d, e)                                                                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_userfaultfd(a)                                                                                       (__syscall_ulong_t)a
#define __NRAP_membarrier(a)                                                                                        (__syscall_ulong_t)a
#define __NRAP_mlock2(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_open(a, b, c)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_link(a, b)                                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_unlink(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_mknod(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chmod(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_chown(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mkdir(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rmdir(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_lchown(a, b, c)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_access(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rename(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_readlink(a, b, c)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_symlink(a, b)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_utimes(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pipe(a)                                                                                              (__syscall_ulong_t)a
#define __NRAP_dup2(a, b)                                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_epoll_create(a)                                                                                      (__syscall_ulong_t)a
#define __NRAP_inotify_init()                                                                                       /* nothing */
#define __NRAP_eventfd(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_signalfd(a, b, c)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sendfile(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_ftruncate(a, b)                                                                                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_truncate(a, b)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_stat(a, b)                                                                                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lstat(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fstat(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fcntl(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_fadvise64(a)                                                                                         (__syscall_ulong_t)a
#define __NRAP_newfstatat(a, b, c, d)                                                                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fstatfs(a, b)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_statfs(a, b)                                                                                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lseek(a, b, c)                                                                                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mmap(a, b, c, d, e, f)                                                                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_alarm(a)                                                                                             (__syscall_ulong_t)a
#define __NRAP_getpgrp()                                                                                            /* nothing */
#define __NRAP_pause()                                                                                              /* nothing */
#define __NRAP_time(a)                                                                                              (__syscall_ulong_t)a
#define __NRAP_utime(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_creat(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getdents(a, b, c)                                                                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_futimesat(a, b, c)                                                                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_select(a, b, c, d, e)                                                                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_poll(a, b, c)                                                                                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_epoll_wait(a, b, c, d)                                                                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_ustat(a, b)                                                                                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_vfork()                                                                                              /* nothing */
#define __NRAP_oldwait4(a, b, c, d)                                                                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_recv(a, b, c, d)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_send(a, b, c, d)                                                                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_bdflush(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_umount(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP_uselib(a)                                                                                            (__syscall_ulong_t)a
#define __NRAP__sysctl(a)                                                                                           (__syscall_ulong_t)a
#define __NRAP_fork()                                                                                               /* nothing */
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_PACKER */

