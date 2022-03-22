/* HASH CRC-32:0xbb29a08a */
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
#ifndef __NR64FEAT_DEFINED_SYSCALL_ATTR_NORETURN
#define __NR64FEAT_DEFINED_SYSCALL_ATTR_NORETURN
#define __NR64FEAT_HAVE_ATTR_NORETURN
#define __NR64NT_exit
#define __NR64NT_exit_group
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ATTR_NORETURN */
#endif /* __WANT_SYSCALL_ATTR_NORETURN */


/************************************************************************/
/* SYSCALL ARGUMENT COUNT                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_COUNT
#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __NR64AC_read                     3
#define __NR64AC_write                    3
#define __NR64AC_open                     3
#define __NR64AC_close                    1
#define __NR64AC_stat                     2
#define __NR64AC_fstat                    2
#define __NR64AC_lstat                    2
#define __NR64AC_poll                     3
#define __NR64AC_lseek                    3
#define __NR64AC_mmap                     6
#define __NR64AC_mprotect                 3
#define __NR64AC_munmap                   2
#define __NR64AC_brk                      1
#define __NR64AC_rt_sigaction             4
#define __NR64AC_rt_sigprocmask           4
#define __NR64AC_rt_sigreturn             0
#define __NR64AC_ioctl                    3
#define __NR64AC_pread64                  4
#define __NR64AC_pwrite64                 4
#define __NR64AC_readv                    3
#define __NR64AC_writev                   3
#define __NR64AC_access                   2
#define __NR64AC_pipe                     1
#define __NR64AC_select                   5
#define __NR64AC_sched_yield              0
#define __NR64AC_mremap                   5
#define __NR64AC_msync                    3
#define __NR64AC_mincore                  3
#define __NR64AC_madvise                  3
#define __NR64AC_shmget                   3
#define __NR64AC_shmat                    3
#define __NR64AC_shmctl                   3
#define __NR64AC_dup                      1
#define __NR64AC_dup2                     2
#define __NR64AC_pause                    0
#define __NR64AC_nanosleep                2
#define __NR64AC_getitimer                2
#define __NR64AC_alarm                    1
#define __NR64AC_setitimer                3
#define __NR64AC_getpid                   0
#define __NR64AC_sendfile                 4
#define __NR64AC_socket                   3
#define __NR64AC_connect                  3
#define __NR64AC_accept                   3
#define __NR64AC_sendto                   6
#define __NR64AC_recvfrom                 6
#define __NR64AC_sendmsg                  3
#define __NR64AC_recvmsg                  3
#define __NR64AC_shutdown                 2
#define __NR64AC_bind                     3
#define __NR64AC_listen                   2
#define __NR64AC_getsockname              3
#define __NR64AC_getpeername              3
#define __NR64AC_socketpair               4
#define __NR64AC_setsockopt               5
#define __NR64AC_getsockopt               5
#define __NR64AC_clone                    5
#define __NR64AC_fork                     0
#define __NR64AC_vfork                    0
#define __NR64AC_execve                   3
#define __NR64AC_exit                     1
#define __NR64AC_wait4                    4
#define __NR64AC_kill                     2
#define __NR64AC_uname                    1
#define __NR64AC_semget                   1
#define __NR64AC_semop                    1
#define __NR64AC_semctl                   1
#define __NR64AC_shmdt                    1
#define __NR64AC_msgget                   1
#define __NR64AC_msgsnd                   1
#define __NR64AC_msgrcv                   1
#define __NR64AC_msgctl                   1
#define __NR64AC_fcntl                    3
#define __NR64AC_flock                    2
#define __NR64AC_fsync                    1
#define __NR64AC_fdatasync                1
#define __NR64AC_truncate                 2
#define __NR64AC_ftruncate                2
#define __NR64AC_getdents                 3
#define __NR64AC_getcwd                   2
#define __NR64AC_chdir                    1
#define __NR64AC_fchdir                   1
#define __NR64AC_rename                   2
#define __NR64AC_mkdir                    2
#define __NR64AC_rmdir                    1
#define __NR64AC_creat                    2
#define __NR64AC_link                     2
#define __NR64AC_unlink                   1
#define __NR64AC_symlink                  2
#define __NR64AC_readlink                 3
#define __NR64AC_chmod                    2
#define __NR64AC_fchmod                   2
#define __NR64AC_chown                    3
#define __NR64AC_fchown                   3
#define __NR64AC_lchown                   3
#define __NR64AC_umask                    1
#define __NR64AC_gettimeofday             2
#define __NR64AC_getrlimit                2
#define __NR64AC_getrusage                2
#define __NR64AC_sysinfo                  1
#define __NR64AC_times                    1
#define __NR64AC_ptrace                   4
#define __NR64AC_getuid                   0
#define __NR64AC_syslog                   3
#define __NR64AC_getgid                   0
#define __NR64AC_setuid                   1
#define __NR64AC_setgid                   1
#define __NR64AC_geteuid                  0
#define __NR64AC_getegid                  0
#define __NR64AC_setpgid                  2
#define __NR64AC_getppid                  0
#define __NR64AC_getpgrp                  0
#define __NR64AC_setsid                   0
#define __NR64AC_setreuid                 2
#define __NR64AC_setregid                 2
#define __NR64AC_getgroups                2
#define __NR64AC_setgroups                2
#define __NR64AC_setresuid                3
#define __NR64AC_getresuid                3
#define __NR64AC_setresgid                3
#define __NR64AC_getresgid                3
#define __NR64AC_getpgid                  1
#define __NR64AC_setfsuid                 1
#define __NR64AC_setfsgid                 1
#define __NR64AC_getsid                   1
#define __NR64AC_capget                   1
#define __NR64AC_capset                   1
#define __NR64AC_rt_sigpending            2
#define __NR64AC_rt_sigtimedwait          4
#define __NR64AC_rt_sigqueueinfo          3
#define __NR64AC_rt_sigsuspend            2
#define __NR64AC_sigaltstack              2
#define __NR64AC_utime                    2
#define __NR64AC_mknod                    3
#define __NR64AC_uselib                   1
#define __NR64AC_personality              1
#define __NR64AC_ustat                    2
#define __NR64AC_statfs                   2
#define __NR64AC_fstatfs                  2
#define __NR64AC_sysfs                    1
#define __NR64AC_getpriority              2
#define __NR64AC_setpriority              3
#define __NR64AC_sched_setparam           2
#define __NR64AC_sched_getparam           2
#define __NR64AC_sched_setscheduler       3
#define __NR64AC_sched_getscheduler       1
#define __NR64AC_sched_get_priority_max   1
#define __NR64AC_sched_get_priority_min   1
#define __NR64AC_sched_rr_get_interval    2
#define __NR64AC_mlock                    2
#define __NR64AC_munlock                  2
#define __NR64AC_mlockall                 1
#define __NR64AC_munlockall               0
#define __NR64AC_vhangup                  0
#define __NR64AC_modify_ldt               3
#define __NR64AC_pivot_root               1
#define __NR64AC__sysctl                  1
#define __NR64AC_prctl                    5
#define __NR64AC_arch_prctl               2
#define __NR64AC_adjtimex                 1
#define __NR64AC_setrlimit                2
#define __NR64AC_chroot                   1
#define __NR64AC_sync                     0
#define __NR64AC_acct                     1
#define __NR64AC_settimeofday             2
#define __NR64AC_mount                    5
#define __NR64AC_umount2                  2
#define __NR64AC_swapon                   2
#define __NR64AC_swapoff                  1
#define __NR64AC_reboot                   1
#define __NR64AC_sethostname              2
#define __NR64AC_setdomainname            2
#define __NR64AC_iopl                     1
#define __NR64AC_ioperm                   3
#define __NR64AC_create_module            0
#define __NR64AC_init_module              3
#define __NR64AC_delete_module            2
#define __NR64AC_get_kernel_syms          0
#define __NR64AC_query_module             0
#define __NR64AC_quotactl                 1
#define __NR64AC_nfsservctl               1
#define __NR64AC_getpmsg                  0
#define __NR64AC_putpmsg                  0
#define __NR64AC_afs_syscall              0
#define __NR64AC_tuxcall                  0
#define __NR64AC_security                 0
#define __NR64AC_gettid                   0
#define __NR64AC_readahead                3
#define __NR64AC_setxattr                 5
#define __NR64AC_lsetxattr                5
#define __NR64AC_fsetxattr                5
#define __NR64AC_getxattr                 4
#define __NR64AC_lgetxattr                4
#define __NR64AC_fgetxattr                4
#define __NR64AC_listxattr                3
#define __NR64AC_llistxattr               3
#define __NR64AC_flistxattr               3
#define __NR64AC_removexattr              2
#define __NR64AC_lremovexattr             2
#define __NR64AC_fremovexattr             2
#define __NR64AC_tkill                    2
#define __NR64AC_time                     1
#define __NR64AC_futex                    6
#define __NR64AC_sched_setaffinity        3
#define __NR64AC_sched_getaffinity        3
#define __NR64AC_set_thread_area          1
#define __NR64AC_io_setup                 1
#define __NR64AC_io_destroy               1
#define __NR64AC_io_getevents             1
#define __NR64AC_io_submit                1
#define __NR64AC_io_cancel                1
#define __NR64AC_get_thread_area          1
#define __NR64AC_lookup_dcookie           1
#define __NR64AC_epoll_create             1
#define __NR64AC_epoll_ctl_old            4
#define __NR64AC_epoll_wait_old           4
#define __NR64AC_remap_file_pages         5
#define __NR64AC_getdents64               3
#define __NR64AC_set_tid_address          1
#define __NR64AC_restart_syscall          0
#define __NR64AC_semtimedop               1
#define __NR64AC_fadvise64                1
#define __NR64AC_timer_create             3
#define __NR64AC_timer_settime            4
#define __NR64AC_timer_gettime            2
#define __NR64AC_timer_getoverrun         1
#define __NR64AC_timer_delete             1
#define __NR64AC_clock_settime            2
#define __NR64AC_clock_gettime            2
#define __NR64AC_clock_getres             2
#define __NR64AC_clock_nanosleep          4
#define __NR64AC_exit_group               1
#define __NR64AC_epoll_wait               4
#define __NR64AC_epoll_ctl                4
#define __NR64AC_tgkill                   3
#define __NR64AC_utimes                   2
#define __NR64AC_vserver                  0
#define __NR64AC_mbind                    1
#define __NR64AC_set_mempolicy            1
#define __NR64AC_get_mempolicy            1
#define __NR64AC_mq_open                  3
#define __NR64AC_mq_unlink                1
#define __NR64AC_mq_timedsend             5
#define __NR64AC_mq_timedreceive          5
#define __NR64AC_mq_notify                2
#define __NR64AC_mq_getsetattr            3
#define __NR64AC_kexec_load               1
#define __NR64AC_waitid                   5
#define __NR64AC_add_key                  1
#define __NR64AC_request_key              1
#define __NR64AC_keyctl                   1
#define __NR64AC_ioprio_set               3
#define __NR64AC_ioprio_get               2
#define __NR64AC_inotify_init             1
#define __NR64AC_inotify_add_watch        1
#define __NR64AC_inotify_rm_watch         1
#define __NR64AC_migrate_pages            1
#define __NR64AC_openat                   4
#define __NR64AC_mkdirat                  3
#define __NR64AC_mknodat                  4
#define __NR64AC_fchownat                 5
#define __NR64AC_futimesat                3
#define __NR64AC_newfstatat               4
#define __NR64AC_unlinkat                 3
#define __NR64AC_renameat                 4
#define __NR64AC_linkat                   5
#define __NR64AC_symlinkat                3
#define __NR64AC_readlinkat               4
#define __NR64AC_fchmodat                 4
#define __NR64AC_faccessat                3
#define __NR64AC_pselect6                 6
#define __NR64AC_ppoll                    5
#define __NR64AC_unshare                  1
#define __NR64AC_set_robust_list          1
#define __NR64AC_get_robust_list          1
#define __NR64AC_splice                   6
#define __NR64AC_tee                      4
#define __NR64AC_sync_file_range          4
#define __NR64AC_vmsplice                 4
#define __NR64AC_move_pages               1
#define __NR64AC_utimensat                4
#define __NR64AC_epoll_pwait              6
#define __NR64AC_signalfd                 3
#define __NR64AC_timerfd_create           2
#define __NR64AC_eventfd                  1
#define __NR64AC_fallocate                4
#define __NR64AC_timerfd_settime          4
#define __NR64AC_timerfd_gettime          2
#define __NR64AC_accept4                  4
#define __NR64AC_signalfd4                4
#define __NR64AC_eventfd2                 2
#define __NR64AC_epoll_create1            1
#define __NR64AC_dup3                     3
#define __NR64AC_pipe2                    2
#define __NR64AC_inotify_init1            1
#define __NR64AC_preadv                   4
#define __NR64AC_pwritev                  4
#define __NR64AC_rt_tgsigqueueinfo        4
#define __NR64AC_perf_event_open          1
#define __NR64AC_recvmmsg                 5
#define __NR64AC_fanotify_init            1
#define __NR64AC_fanotify_mark            1
#define __NR64AC_prlimit64                4
#define __NR64AC_name_to_handle_at        5
#define __NR64AC_open_by_handle_at        3
#define __NR64AC_clock_adjtime            1
#define __NR64AC_syncfs                   1
#define __NR64AC_sendmmsg                 4
#define __NR64AC_setns                    2
#define __NR64AC_getcpu                   3
#define __NR64AC_process_vm_readv         6
#define __NR64AC_process_vm_writev        6
#define __NR64AC_kcmp                     5
#define __NR64AC_finit_module             3
#define __NR64AC_sched_setattr            1
#define __NR64AC_sched_getattr            1
#define __NR64AC_renameat2                5
#define __NR64AC_seccomp                  1
#define __NR64AC_getrandom                3
#define __NR64AC_memfd_create             2
#define __NR64AC_kexec_file_load          1
#define __NR64AC_bpf                      1
#define __NR64AC_execveat                 5
#define __NR64AC_userfaultfd              1
#define __NR64AC_membarrier               1
#define __NR64AC_mlock2                   3
#define __NR64AC_copy_file_range          1
#define __NR64AC_preadv2                  1
#define __NR64AC_pwritev2                 1
#define __NR64AC_pkey_mprotect            4
#define __NR64AC_pkey_alloc               2
#define __NR64AC_pkey_free                1
#define __NR64AC_statx                    1
#define __NR64AC_io_pgetevents            1
#define __NR64AC_rseq                     1
#define __NR64AC_pidfd_send_signal        4
#define __NR64AC_io_uring_setup           1
#define __NR64AC_io_uring_enter           1
#define __NR64AC_io_uring_register        1
#define __NR64AC_open_tree                1
#define __NR64AC_move_mount               1
#define __NR64AC_fsopen                   1
#define __NR64AC_fsconfig                 1
#define __NR64AC_fsmount                  1
#define __NR64AC_fspick                   1
#define __NR64AC_pidfd_open               2
#define __NR64AC_clone3                   2
#define __NR64AC_close_range              3
#define __NR64AC_openat2                  1
#define __NR64AC_pidfd_getfd              3
#define __NR64AC_faccessat2               4
#define __NR64AC_pwritevf                 5
#define __NR64AC_preadvf                  5
#define __NR64AC_freadlinkat              5
#define __NR64AC_fsymlinkat               4
#define __NR64AC_kfstatat                 4
#define __NR64AC_fmknodat                 5
#define __NR64AC_fmkdirat                 4
#define __NR64AC_ksysctl                  2
#define __NR64AC_maplibrary               5
#define __NR64AC_fsmode                   1
#define __NR64AC_fchdirat                 3
#define __NR64AC_kreaddirf                5
#define __NR64AC_kreaddir                 4
#define __NR64AC_set_exception_handler    3
#define __NR64AC_get_exception_handler    3
#define __NR64AC_rpc_serve_sysret         0
#define __NR64AC_set_userprocmask_address 1
#define __NR64AC_rtm_test                 0
#define __NR64AC_rtm_abort                1
#define __NR64AC_rtm_end                  0
#define __NR64AC_rtm_begin                0
#define __NR64AC_userviofd                2
#define __NR64AC_coredump                 6
#define __NR64AC_mktty                    4
#define __NR64AC_lfutexexpr               5
#define __NR64AC_lfutex                   5
#define __NR64AC_rpc_serve                0
#define __NR64AC_debugtrap                2
#define __NR64AC_writevf                  4
#define __NR64AC_readvf                   4
#define __NR64AC_pwrite64f                5
#define __NR64AC_pread64f                 5
#define __NR64AC_ioctlf                   4
#define __NR64AC_ksigreturn               0
#define __NR64AC_openpty                  5
#define __NR64AC_rpc_schedule             5
#define __NR64AC_frealpathat              5
#define __NR64AC_frealpath4               4
#define __NR64AC_getdrives                0
#define __NR64AC_detach                   1
#define __NR64AC_readf                    4
#define __NR64AC_klstat                   2
#define __NR64AC_kfstat                   2
#define __NR64AC_kstat                    2
#define __NR64AC_writef                   4
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT */


/************************************************************************/
/* SYSCALL RETURN TYPES                                                 */
/************************************************************************/
#ifdef __WANT_SYSCALL_RETURN_TYPES
#ifndef __NR64FEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NR64FEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NR64RT_read                     (ssize_t, __ssize_t)
#define __NR64RT_write                    (ssize_t, __ssize_t)
#define __NR64RT_open                     (fd_t, __fd_t)
#define __NR64RT_close                    (errno_t, __errno_t)
#define __NR64RT_stat                     (errno_t, __errno_t)
#define __NR64RT_fstat                    (errno_t, __errno_t)
#define __NR64RT_lstat                    (errno_t, __errno_t)
#define __NR64RT_poll                     (ssize_t, __ssize_t)
#define __NR64RT_lseek                    (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_mmap                     (void *, void *)
#define __NR64RT_mprotect                 (errno_t, __errno_t)
#define __NR64RT_munmap                   (errno_t, __errno_t)
#define __NR64RT_brk                      (errno_t, __errno_t)
#define __NR64RT_rt_sigaction             (errno_t, __errno_t)
#define __NR64RT_rt_sigprocmask           (errno_t, __errno_t)
#define __NR64RT_rt_sigreturn             (void, void)
#define __NR64RT_ioctl                    (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_pread64                  (ssize_t, __ssize_t)
#define __NR64RT_pwrite64                 (ssize_t, __ssize_t)
#define __NR64RT_readv                    (ssize_t, __ssize_t)
#define __NR64RT_writev                   (ssize_t, __ssize_t)
#define __NR64RT_access                   (errno_t, __errno_t)
#define __NR64RT_pipe                     (errno_t, __errno_t)
#define __NR64RT_select                   (ssize_t, __ssize_t)
#define __NR64RT_sched_yield              (errno_t, __errno_t)
#define __NR64RT_mremap                   (void *, void *)
#define __NR64RT_msync                    (errno_t, __errno_t)
#define __NR64RT_mincore                  (errno_t, __errno_t)
#define __NR64RT_madvise                  (errno_t, __errno_t)
#define __NR64RT_shmget                   (errno_t, __errno_t)
#define __NR64RT_shmat                    (errno_t, __errno_t)
#define __NR64RT_shmctl                   (errno_t, __errno_t)
#define __NR64RT_dup                      (fd_t, __fd_t)
#define __NR64RT_dup2                     (fd_t, __fd_t)
#define __NR64RT_pause                    (errno_t, __errno_t)
#define __NR64RT_nanosleep                (errno_t, __errno_t)
#define __NR64RT_getitimer                (errno_t, __errno_t)
#define __NR64RT_alarm                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64RT_setitimer                (errno_t, __errno_t)
#define __NR64RT_getpid                   (pid_t, __pid_t)
#define __NR64RT_sendfile                 (ssize_t, __ssize_t)
#define __NR64RT_socket                   (fd_t, __fd_t)
#define __NR64RT_connect                  (errno_t, __errno_t)
#define __NR64RT_accept                   (fd_t, __fd_t)
#define __NR64RT_sendto                   (ssize_t, __ssize_t)
#define __NR64RT_recvfrom                 (ssize_t, __ssize_t)
#define __NR64RT_sendmsg                  (ssize_t, __ssize_t)
#define __NR64RT_recvmsg                  (ssize_t, __ssize_t)
#define __NR64RT_shutdown                 (errno_t, __errno_t)
#define __NR64RT_bind                     (errno_t, __errno_t)
#define __NR64RT_listen                   (errno_t, __errno_t)
#define __NR64RT_getsockname              (errno_t, __errno_t)
#define __NR64RT_getpeername              (errno_t, __errno_t)
#define __NR64RT_socketpair               (errno_t, __errno_t)
#define __NR64RT_setsockopt               (errno_t, __errno_t)
#define __NR64RT_getsockopt               (errno_t, __errno_t)
#define __NR64RT_clone                    (pid_t, __pid_t)
#define __NR64RT_fork                     (pid_t, __pid_t)
#define __NR64RT_vfork                    (pid_t, __pid_t)
#define __NR64RT_execve                   (errno_t, __errno_t)
#define __NR64RT_exit                     (void, void)
#define __NR64RT_wait4                    (pid_t, __pid_t)
#define __NR64RT_kill                     (errno_t, __errno_t)
#define __NR64RT_uname                    (errno_t, __errno_t)
#define __NR64RT_semget                   (errno_t, __errno_t)
#define __NR64RT_semop                    (errno_t, __errno_t)
#define __NR64RT_semctl                   (errno_t, __errno_t)
#define __NR64RT_shmdt                    (errno_t, __errno_t)
#define __NR64RT_msgget                   (errno_t, __errno_t)
#define __NR64RT_msgsnd                   (errno_t, __errno_t)
#define __NR64RT_msgrcv                   (errno_t, __errno_t)
#define __NR64RT_msgctl                   (errno_t, __errno_t)
#define __NR64RT_fcntl                    (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_flock                    (errno_t, __errno_t)
#define __NR64RT_fsync                    (errno_t, __errno_t)
#define __NR64RT_fdatasync                (errno_t, __errno_t)
#define __NR64RT_truncate                 (errno_t, __errno_t)
#define __NR64RT_ftruncate                (errno_t, __errno_t)
#define __NR64RT_getdents                 (ssize_t, __ssize_t)
#define __NR64RT_getcwd                   (ssize_t, __ssize_t)
#define __NR64RT_chdir                    (errno_t, __errno_t)
#define __NR64RT_fchdir                   (errno_t, __errno_t)
#define __NR64RT_rename                   (errno_t, __errno_t)
#define __NR64RT_mkdir                    (errno_t, __errno_t)
#define __NR64RT_rmdir                    (errno_t, __errno_t)
#define __NR64RT_creat                    (fd_t, __fd_t)
#define __NR64RT_link                     (errno_t, __errno_t)
#define __NR64RT_unlink                   (errno_t, __errno_t)
#define __NR64RT_symlink                  (errno_t, __errno_t)
#define __NR64RT_readlink                 (ssize_t, __ssize_t)
#define __NR64RT_chmod                    (errno_t, __errno_t)
#define __NR64RT_fchmod                   (errno_t, __errno_t)
#define __NR64RT_chown                    (errno_t, __errno_t)
#define __NR64RT_fchown                   (errno_t, __errno_t)
#define __NR64RT_lchown                   (errno_t, __errno_t)
#define __NR64RT_umask                    (mode_t, __mode_t)
#define __NR64RT_gettimeofday             (errno_t, __errno_t)
#define __NR64RT_getrlimit                (errno_t, __errno_t)
#define __NR64RT_getrusage                (errno_t, __errno_t)
#define __NR64RT_sysinfo                  (errno_t, __errno_t)
#define __NR64RT_times                    (clock_t, __clock_t)
#define __NR64RT_ptrace                   (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_getuid                   (uid_t, __uid_t)
#define __NR64RT_syslog                   (ssize_t, __ssize_t)
#define __NR64RT_getgid                   (gid_t, __gid_t)
#define __NR64RT_setuid                   (errno_t, __errno_t)
#define __NR64RT_setgid                   (errno_t, __errno_t)
#define __NR64RT_geteuid                  (uid_t, __uid_t)
#define __NR64RT_getegid                  (gid_t, __gid_t)
#define __NR64RT_setpgid                  (errno_t, __errno_t)
#define __NR64RT_getppid                  (pid_t, __pid_t)
#define __NR64RT_getpgrp                  (pid_t, __pid_t)
#define __NR64RT_setsid                   (pid_t, __pid_t)
#define __NR64RT_setreuid                 (errno_t, __errno_t)
#define __NR64RT_setregid                 (errno_t, __errno_t)
#define __NR64RT_getgroups                (ssize_t, __ssize_t)
#define __NR64RT_setgroups                (errno_t, __errno_t)
#define __NR64RT_setresuid                (errno_t, __errno_t)
#define __NR64RT_getresuid                (errno_t, __errno_t)
#define __NR64RT_setresgid                (errno_t, __errno_t)
#define __NR64RT_getresgid                (errno_t, __errno_t)
#define __NR64RT_getpgid                  (pid_t, __pid_t)
#define __NR64RT_setfsuid                 (errno_t, __errno_t)
#define __NR64RT_setfsgid                 (errno_t, __errno_t)
#define __NR64RT_getsid                   (pid_t, __pid_t)
#define __NR64RT_capget                   (errno_t, __errno_t)
#define __NR64RT_capset                   (errno_t, __errno_t)
#define __NR64RT_rt_sigpending            (errno_t, __errno_t)
#define __NR64RT_rt_sigtimedwait          (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_rt_sigqueueinfo          (errno_t, __errno_t)
#define __NR64RT_rt_sigsuspend            (errno_t, __errno_t)
#define __NR64RT_sigaltstack              (errno_t, __errno_t)
#define __NR64RT_utime                    (errno_t, __errno_t)
#define __NR64RT_mknod                    (errno_t, __errno_t)
#define __NR64RT_uselib                   (errno_t, __errno_t)
#define __NR64RT_personality              (errno_t, __errno_t)
#define __NR64RT_ustat                    (errno_t, __errno_t)
#define __NR64RT_statfs                   (errno_t, __errno_t)
#define __NR64RT_fstatfs                  (errno_t, __errno_t)
#define __NR64RT_sysfs                    (errno_t, __errno_t)
#define __NR64RT_getpriority              (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_setpriority              (errno_t, __errno_t)
#define __NR64RT_sched_setparam           (errno_t, __errno_t)
#define __NR64RT_sched_getparam           (errno_t, __errno_t)
#define __NR64RT_sched_setscheduler       (errno_t, __errno_t)
#define __NR64RT_sched_getscheduler       (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_sched_get_priority_max   (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_sched_get_priority_min   (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_sched_rr_get_interval    (errno_t, __errno_t)
#define __NR64RT_mlock                    (errno_t, __errno_t)
#define __NR64RT_munlock                  (errno_t, __errno_t)
#define __NR64RT_mlockall                 (errno_t, __errno_t)
#define __NR64RT_munlockall               (errno_t, __errno_t)
#define __NR64RT_vhangup                  (errno_t, __errno_t)
#define __NR64RT_modify_ldt               (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_pivot_root               (errno_t, __errno_t)
#define __NR64RT__sysctl                  (errno_t, __errno_t)
#define __NR64RT_prctl                    (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_arch_prctl               (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_adjtimex                 (errno_t, __errno_t)
#define __NR64RT_setrlimit                (errno_t, __errno_t)
#define __NR64RT_chroot                   (errno_t, __errno_t)
#define __NR64RT_sync                     (errno_t, __errno_t)
#define __NR64RT_acct                     (errno_t, __errno_t)
#define __NR64RT_settimeofday             (errno_t, __errno_t)
#define __NR64RT_mount                    (errno_t, __errno_t)
#define __NR64RT_umount2                  (errno_t, __errno_t)
#define __NR64RT_swapon                   (errno_t, __errno_t)
#define __NR64RT_swapoff                  (errno_t, __errno_t)
#define __NR64RT_reboot                   (errno_t, __errno_t)
#define __NR64RT_sethostname              (errno_t, __errno_t)
#define __NR64RT_setdomainname            (errno_t, __errno_t)
#define __NR64RT_iopl                     (errno_t, __errno_t)
#define __NR64RT_ioperm                   (errno_t, __errno_t)
#define __NR64RT_create_module            (errno_t, __errno_t)
#define __NR64RT_init_module              (errno_t, __errno_t)
#define __NR64RT_delete_module            (errno_t, __errno_t)
#define __NR64RT_get_kernel_syms          (errno_t, __errno_t)
#define __NR64RT_query_module             (errno_t, __errno_t)
#define __NR64RT_quotactl                 (errno_t, __errno_t)
#define __NR64RT_nfsservctl               (errno_t, __errno_t)
#define __NR64RT_getpmsg                  (errno_t, __errno_t)
#define __NR64RT_putpmsg                  (errno_t, __errno_t)
#define __NR64RT_afs_syscall              (errno_t, __errno_t)
#define __NR64RT_tuxcall                  (errno_t, __errno_t)
#define __NR64RT_security                 (errno_t, __errno_t)
#define __NR64RT_gettid                   (pid_t, __pid_t)
#define __NR64RT_readahead                (ssize_t, __ssize_t)
#define __NR64RT_setxattr                 (errno_t, __errno_t)
#define __NR64RT_lsetxattr                (errno_t, __errno_t)
#define __NR64RT_fsetxattr                (errno_t, __errno_t)
#define __NR64RT_getxattr                 (ssize_t, __ssize_t)
#define __NR64RT_lgetxattr                (ssize_t, __ssize_t)
#define __NR64RT_fgetxattr                (ssize_t, __ssize_t)
#define __NR64RT_listxattr                (ssize_t, __ssize_t)
#define __NR64RT_llistxattr               (ssize_t, __ssize_t)
#define __NR64RT_flistxattr               (ssize_t, __ssize_t)
#define __NR64RT_removexattr              (errno_t, __errno_t)
#define __NR64RT_lremovexattr             (errno_t, __errno_t)
#define __NR64RT_fremovexattr             (errno_t, __errno_t)
#define __NR64RT_tkill                    (errno_t, __errno_t)
#define __NR64RT_time                     (time32_t, __time32_t)
#define __NR64RT_futex                    (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_sched_setaffinity        (errno_t, __errno_t)
#define __NR64RT_sched_getaffinity        (errno_t, __errno_t)
#define __NR64RT_set_thread_area          (errno_t, __errno_t)
#define __NR64RT_io_setup                 (errno_t, __errno_t)
#define __NR64RT_io_destroy               (errno_t, __errno_t)
#define __NR64RT_io_getevents             (errno_t, __errno_t)
#define __NR64RT_io_submit                (errno_t, __errno_t)
#define __NR64RT_io_cancel                (errno_t, __errno_t)
#define __NR64RT_get_thread_area          (errno_t, __errno_t)
#define __NR64RT_lookup_dcookie           (errno_t, __errno_t)
#define __NR64RT_epoll_create             (fd_t, __fd_t)
#define __NR64RT_epoll_ctl_old            (errno_t, __errno_t)
#define __NR64RT_epoll_wait_old           (ssize_t, __ssize_t)
#define __NR64RT_remap_file_pages         (errno_t, __errno_t)
#define __NR64RT_getdents64               (ssize_t, __ssize_t)
#define __NR64RT_set_tid_address          (pid_t, __pid_t)
#define __NR64RT_restart_syscall          (errno_t, __errno_t)
#define __NR64RT_semtimedop               (errno_t, __errno_t)
#define __NR64RT_fadvise64                (errno_t, __errno_t)
#define __NR64RT_timer_create             (errno_t, __errno_t)
#define __NR64RT_timer_settime            (errno_t, __errno_t)
#define __NR64RT_timer_gettime            (errno_t, __errno_t)
#define __NR64RT_timer_getoverrun         (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_timer_delete             (errno_t, __errno_t)
#define __NR64RT_clock_settime            (errno_t, __errno_t)
#define __NR64RT_clock_gettime            (errno_t, __errno_t)
#define __NR64RT_clock_getres             (errno_t, __errno_t)
#define __NR64RT_clock_nanosleep          (errno_t, __errno_t)
#define __NR64RT_exit_group               (void, void)
#define __NR64RT_epoll_wait               (ssize_t, __ssize_t)
#define __NR64RT_epoll_ctl                (errno_t, __errno_t)
#define __NR64RT_tgkill                   (errno_t, __errno_t)
#define __NR64RT_utimes                   (errno_t, __errno_t)
#define __NR64RT_vserver                  (errno_t, __errno_t)
#define __NR64RT_mbind                    (errno_t, __errno_t)
#define __NR64RT_set_mempolicy            (errno_t, __errno_t)
#define __NR64RT_get_mempolicy            (errno_t, __errno_t)
#define __NR64RT_mq_open                  (fd_t, __fd_t)
#define __NR64RT_mq_unlink                (errno_t, __errno_t)
#define __NR64RT_mq_timedsend             (errno_t, __errno_t)
#define __NR64RT_mq_timedreceive          (ssize_t, __ssize_t)
#define __NR64RT_mq_notify                (errno_t, __errno_t)
#define __NR64RT_mq_getsetattr            (errno_t, __errno_t)
#define __NR64RT_kexec_load               (errno_t, __errno_t)
#define __NR64RT_waitid                   (errno_t, __errno_t)
#define __NR64RT_add_key                  (errno_t, __errno_t)
#define __NR64RT_request_key              (errno_t, __errno_t)
#define __NR64RT_keyctl                   (errno_t, __errno_t)
#define __NR64RT_ioprio_set               (errno_t, __errno_t)
#define __NR64RT_ioprio_get               (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_inotify_init             (errno_t, __errno_t)
#define __NR64RT_inotify_add_watch        (errno_t, __errno_t)
#define __NR64RT_inotify_rm_watch         (errno_t, __errno_t)
#define __NR64RT_migrate_pages            (errno_t, __errno_t)
#define __NR64RT_openat                   (fd_t, __fd_t)
#define __NR64RT_mkdirat                  (errno_t, __errno_t)
#define __NR64RT_mknodat                  (errno_t, __errno_t)
#define __NR64RT_fchownat                 (errno_t, __errno_t)
#define __NR64RT_futimesat                (errno_t, __errno_t)
#define __NR64RT_newfstatat               (errno_t, __errno_t)
#define __NR64RT_unlinkat                 (errno_t, __errno_t)
#define __NR64RT_renameat                 (errno_t, __errno_t)
#define __NR64RT_linkat                   (errno_t, __errno_t)
#define __NR64RT_symlinkat                (errno_t, __errno_t)
#define __NR64RT_readlinkat               (ssize_t, __ssize_t)
#define __NR64RT_fchmodat                 (errno_t, __errno_t)
#define __NR64RT_faccessat                (errno_t, __errno_t)
#define __NR64RT_pselect6                 (ssize_t, __ssize_t)
#define __NR64RT_ppoll                    (ssize_t, __ssize_t)
#define __NR64RT_unshare                  (errno_t, __errno_t)
#define __NR64RT_set_robust_list          (errno_t, __errno_t)
#define __NR64RT_get_robust_list          (errno_t, __errno_t)
#define __NR64RT_splice                   (ssize_t, __ssize_t)
#define __NR64RT_tee                      (ssize_t, __ssize_t)
#define __NR64RT_sync_file_range          (errno_t, __errno_t)
#define __NR64RT_vmsplice                 (ssize_t, __ssize_t)
#define __NR64RT_move_pages               (errno_t, __errno_t)
#define __NR64RT_utimensat                (errno_t, __errno_t)
#define __NR64RT_epoll_pwait              (ssize_t, __ssize_t)
#define __NR64RT_signalfd                 (errno_t, __errno_t)
#define __NR64RT_timerfd_create           (fd_t, __fd_t)
#define __NR64RT_eventfd                  (fd_t, __fd_t)
#define __NR64RT_fallocate                (errno_t, __errno_t)
#define __NR64RT_timerfd_settime          (errno_t, __errno_t)
#define __NR64RT_timerfd_gettime          (errno_t, __errno_t)
#define __NR64RT_accept4                  (fd_t, __fd_t)
#define __NR64RT_signalfd4                (errno_t, __errno_t)
#define __NR64RT_eventfd2                 (fd_t, __fd_t)
#define __NR64RT_epoll_create1            (fd_t, __fd_t)
#define __NR64RT_dup3                     (fd_t, __fd_t)
#define __NR64RT_pipe2                    (errno_t, __errno_t)
#define __NR64RT_inotify_init1            (errno_t, __errno_t)
#define __NR64RT_preadv                   (ssize_t, __ssize_t)
#define __NR64RT_pwritev                  (ssize_t, __ssize_t)
#define __NR64RT_rt_tgsigqueueinfo        (errno_t, __errno_t)
#define __NR64RT_perf_event_open          (errno_t, __errno_t)
#define __NR64RT_recvmmsg                 (ssize_t, __ssize_t)
#define __NR64RT_fanotify_init            (errno_t, __errno_t)
#define __NR64RT_fanotify_mark            (errno_t, __errno_t)
#define __NR64RT_prlimit64                (errno_t, __errno_t)
#define __NR64RT_name_to_handle_at        (errno_t, __errno_t)
#define __NR64RT_open_by_handle_at        (fd_t, __fd_t)
#define __NR64RT_clock_adjtime            (errno_t, __errno_t)
#define __NR64RT_syncfs                   (errno_t, __errno_t)
#define __NR64RT_sendmmsg                 (ssize_t, __ssize_t)
#define __NR64RT_setns                    (errno_t, __errno_t)
#define __NR64RT_getcpu                   (errno_t, __errno_t)
#define __NR64RT_process_vm_readv         (ssize_t, __ssize_t)
#define __NR64RT_process_vm_writev        (ssize_t, __ssize_t)
#define __NR64RT_kcmp                     (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_finit_module             (errno_t, __errno_t)
#define __NR64RT_sched_setattr            (errno_t, __errno_t)
#define __NR64RT_sched_getattr            (errno_t, __errno_t)
#define __NR64RT_renameat2                (errno_t, __errno_t)
#define __NR64RT_seccomp                  (errno_t, __errno_t)
#define __NR64RT_getrandom                (ssize_t, __ssize_t)
#define __NR64RT_memfd_create             (fd_t, __fd_t)
#define __NR64RT_kexec_file_load          (errno_t, __errno_t)
#define __NR64RT_bpf                      (errno_t, __errno_t)
#define __NR64RT_execveat                 (errno_t, __errno_t)
#define __NR64RT_userfaultfd              (fd_t, __fd_t)
#define __NR64RT_membarrier               (errno_t, __errno_t)
#define __NR64RT_mlock2                   (errno_t, __errno_t)
#define __NR64RT_copy_file_range          (errno_t, __errno_t)
#define __NR64RT_preadv2                  (errno_t, __errno_t)
#define __NR64RT_pwritev2                 (errno_t, __errno_t)
#define __NR64RT_pkey_mprotect            (errno_t, __errno_t)
#define __NR64RT_pkey_alloc               (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_pkey_free                (errno_t, __errno_t)
#define __NR64RT_statx                    (errno_t, __errno_t)
#define __NR64RT_io_pgetevents            (errno_t, __errno_t)
#define __NR64RT_rseq                     (errno_t, __errno_t)
#define __NR64RT_pidfd_send_signal        (errno_t, __errno_t)
#define __NR64RT_io_uring_setup           (errno_t, __errno_t)
#define __NR64RT_io_uring_enter           (errno_t, __errno_t)
#define __NR64RT_io_uring_register        (errno_t, __errno_t)
#define __NR64RT_open_tree                (errno_t, __errno_t)
#define __NR64RT_move_mount               (errno_t, __errno_t)
#define __NR64RT_fsopen                   (errno_t, __errno_t)
#define __NR64RT_fsconfig                 (errno_t, __errno_t)
#define __NR64RT_fsmount                  (errno_t, __errno_t)
#define __NR64RT_fspick                   (errno_t, __errno_t)
#define __NR64RT_pidfd_open               (fd_t, __fd_t)
#define __NR64RT_clone3                   (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_close_range              (errno_t, __errno_t)
#define __NR64RT_openat2                  (errno_t, __errno_t)
#define __NR64RT_pidfd_getfd              (fd_t, __fd_t)
#define __NR64RT_faccessat2               (errno_t, __errno_t)
#define __NR64RT_pwritevf                 (ssize_t, __ssize_t)
#define __NR64RT_preadvf                  (ssize_t, __ssize_t)
#define __NR64RT_freadlinkat              (ssize_t, __ssize_t)
#define __NR64RT_fsymlinkat               (errno_t, __errno_t)
#define __NR64RT_kfstatat                 (errno_t, __errno_t)
#define __NR64RT_fmknodat                 (errno_t, __errno_t)
#define __NR64RT_fmkdirat                 (errno_t, __errno_t)
#define __NR64RT_ksysctl                  (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_maplibrary               (void *, void *)
#define __NR64RT_fsmode                   (uint64_t, __uint64_t)
#define __NR64RT_fchdirat                 (errno_t, __errno_t)
#define __NR64RT_kreaddirf                (ssize_t, __ssize_t)
#define __NR64RT_kreaddir                 (ssize_t, __ssize_t)
#define __NR64RT_set_exception_handler    (errno_t, __errno_t)
#define __NR64RT_get_exception_handler    (errno_t, __errno_t)
#define __NR64RT_rpc_serve_sysret         (errno_t, __errno_t)
#define __NR64RT_set_userprocmask_address (errno_t, __errno_t)
#define __NR64RT_rtm_test                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64RT_rtm_abort                (errno_t, __errno_t)
#define __NR64RT_rtm_end                  (errno_t, __errno_t)
#define __NR64RT_rtm_begin                (rtm_status_t, __rtm_status_t)
#define __NR64RT_userviofd                (fd_t, __fd_t)
#define __NR64RT_coredump                 (errno_t, __errno_t)
#define __NR64RT_mktty                    (fd_t, __fd_t)
#define __NR64RT_lfutexexpr               (errno_t, __errno_t)
#define __NR64RT_lfutex                   (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_rpc_serve                (errno_t, __errno_t)
#define __NR64RT_debugtrap                (errno_t, __errno_t)
#define __NR64RT_writevf                  (ssize_t, __ssize_t)
#define __NR64RT_readvf                   (ssize_t, __ssize_t)
#define __NR64RT_pwrite64f                (ssize_t, __ssize_t)
#define __NR64RT_pread64f                 (ssize_t, __ssize_t)
#define __NR64RT_ioctlf                   (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_ksigreturn               (void, void)
#define __NR64RT_openpty                  (errno_t, __errno_t)
#define __NR64RT_rpc_schedule             (errno_t, __errno_t)
#define __NR64RT_frealpathat              (ssize_t, __ssize_t)
#define __NR64RT_frealpath4               (ssize_t, __ssize_t)
#define __NR64RT_getdrives                (syscall_slong_t, __syscall_slong_t)
#define __NR64RT_detach                   (errno_t, __errno_t)
#define __NR64RT_readf                    (ssize_t, __ssize_t)
#define __NR64RT_klstat                   (errno_t, __errno_t)
#define __NR64RT_kfstat                   (errno_t, __errno_t)
#define __NR64RT_kstat                    (errno_t, __errno_t)
#define __NR64RT_writef                   (ssize_t, __ssize_t)
#endif /* !__NR64FEAT_DEFINED_SYSCALL_RETURN_TYPES */
#endif /* __WANT_SYSCALL_RETURN_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT TYPES                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_TYPES
#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NR64AT0_read                     (fd_t, __fd_t)
#define __NR64AT1_read                     (void *, void *)
#define __NR64AT2_read                     (size_t, __size_t)
#define __NR64AT0_write                    (fd_t, __fd_t)
#define __NR64AT1_write                    (void const *, void const *)
#define __NR64AT2_write                    (size_t, __size_t)
#define __NR64AT0_open                     (char const *, char const *)
#define __NR64AT1_open                     (oflag_t, __oflag_t)
#define __NR64AT2_open                     (mode_t, __mode_t)
#define __NR64AT0_close                    (fd_t, __fd_t)
#define __NR64AT0_stat                     (char const *, char const *)
#define __NR64AT1_stat                     (struct linux_statx64 *, struct linux_statx64 *)
#define __NR64AT0_fstat                    (fd_t, __fd_t)
#define __NR64AT1_fstat                    (struct linux_statx64 *, struct linux_statx64 *)
#define __NR64AT0_lstat                    (char const *, char const *)
#define __NR64AT1_lstat                    (struct linux_statx64 *, struct linux_statx64 *)
#define __NR64AT0_poll                     (struct pollfd *, struct pollfd *)
#define __NR64AT1_poll                     (size_t, __size_t)
#define __NR64AT2_poll                     (syscall_slong_t, __syscall_slong_t)
#define __NR64AT0_lseek                    (fd_t, __fd_t)
#define __NR64AT1_lseek                    (syscall_slong_t, __syscall_slong_t)
#define __NR64AT2_lseek                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_mmap                     (void *, void *)
#define __NR64AT1_mmap                     (size_t, __size_t)
#define __NR64AT2_mmap                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_mmap                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_mmap                     (fd_t, __fd_t)
#define __NR64AT5_mmap                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_mprotect                 (void *, void *)
#define __NR64AT1_mprotect                 (size_t, __size_t)
#define __NR64AT2_mprotect                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_munmap                   (void *, void *)
#define __NR64AT1_munmap                   (size_t, __size_t)
#define __NR64AT0_brk                      (void *, void *)
#define __NR64AT0_rt_sigaction             (signo_t, __signo_t)
#define __NR64AT1_rt_sigaction             (struct __kernel_sigactionx64 const *, struct __kernel_sigactionx64 const *)
#define __NR64AT2_rt_sigaction             (struct __kernel_sigactionx64 *, struct __kernel_sigactionx64 *)
#define __NR64AT3_rt_sigaction             (size_t, __size_t)
#define __NR64AT0_rt_sigprocmask           (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_rt_sigprocmask           (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR64AT2_rt_sigprocmask           (struct __sigset_struct *, struct __sigset_struct *)
#define __NR64AT3_rt_sigprocmask           (size_t, __size_t)
#define __NR64AT0_ioctl                    (fd_t, __fd_t)
#define __NR64AT1_ioctl                    (ioctl_t, __ioctl_t)
#define __NR64AT2_ioctl                    (void *, void *)
#define __NR64AT0_pread64                  (fd_t, __fd_t)
#define __NR64AT1_pread64                  (void *, void *)
#define __NR64AT2_pread64                  (size_t, __size_t)
#define __NR64AT3_pread64                  (uint64_t, __uint64_t)
#define __NR64AT0_pwrite64                 (fd_t, __fd_t)
#define __NR64AT1_pwrite64                 (void const *, void const *)
#define __NR64AT2_pwrite64                 (size_t, __size_t)
#define __NR64AT3_pwrite64                 (uint64_t, __uint64_t)
#define __NR64AT0_readv                    (fd_t, __fd_t)
#define __NR64AT1_readv                    (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_readv                    (size_t, __size_t)
#define __NR64AT0_writev                   (fd_t, __fd_t)
#define __NR64AT1_writev                   (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_writev                   (size_t, __size_t)
#define __NR64AT0_access                   (char const *, char const *)
#define __NR64AT1_access                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_pipe                     (fd_t *, __fd_t *)
#define __NR64AT0_select                   (size_t, __size_t)
#define __NR64AT1_select                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR64AT2_select                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR64AT3_select                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR64AT4_select                   (struct timevalx64 *, struct __timevalx64 *)
#define __NR64AT0_mremap                   (void *, void *)
#define __NR64AT1_mremap                   (size_t, __size_t)
#define __NR64AT2_mremap                   (size_t, __size_t)
#define __NR64AT3_mremap                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_mremap                   (void *, void *)
#define __NR64AT0_msync                    (void *, void *)
#define __NR64AT1_msync                    (size_t, __size_t)
#define __NR64AT2_msync                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_mincore                  (void *, void *)
#define __NR64AT1_mincore                  (size_t, __size_t)
#define __NR64AT2_mincore                  (uint8_t *, __uint8_t *)
#define __NR64AT0_madvise                  (void *, void *)
#define __NR64AT1_madvise                  (size_t, __size_t)
#define __NR64AT2_madvise                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_shmget                   (key_t, __key_t)
#define __NR64AT1_shmget                   (size_t, __size_t)
#define __NR64AT2_shmget                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_shmat                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_shmat                    (void const *, void const *)
#define __NR64AT2_shmat                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_shmctl                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_shmctl                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_shmctl                   (struct shmid_ds *, struct shmid_ds *)
#define __NR64AT0_dup                      (fd_t, __fd_t)
#define __NR64AT0_dup2                     (fd_t, __fd_t)
#define __NR64AT1_dup2                     (fd_t, __fd_t)
#define __NR64AT0_nanosleep                (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT1_nanosleep                (struct timespecx64 *, struct __timespecx64 *)
#define __NR64AT0_getitimer                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_getitimer                (struct __itimervalx64 *, struct __itimervalx64 *)
#define __NR64AT0_alarm                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_setitimer                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_setitimer                (struct __itimervalx64 const *, struct __itimervalx64 const *)
#define __NR64AT2_setitimer                (struct __itimervalx64 *, struct __itimervalx64 *)
#define __NR64AT0_sendfile                 (fd_t, __fd_t)
#define __NR64AT1_sendfile                 (fd_t, __fd_t)
#define __NR64AT2_sendfile                 (syscall_ulong_t *, __syscall_ulong_t *)
#define __NR64AT3_sendfile                 (size_t, __size_t)
#define __NR64AT0_socket                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_socket                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_socket                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_connect                  (fd_t, __fd_t)
#define __NR64AT1_connect                  (struct sockaddr const *, struct sockaddr const *)
#define __NR64AT2_connect                  (socklen_t, __socklen_t)
#define __NR64AT0_accept                   (fd_t, __fd_t)
#define __NR64AT1_accept                   (struct sockaddr *, struct sockaddr *)
#define __NR64AT2_accept                   (socklen_t *, __socklen_t *)
#define __NR64AT0_sendto                   (fd_t, __fd_t)
#define __NR64AT1_sendto                   (void const *, void const *)
#define __NR64AT2_sendto                   (size_t, __size_t)
#define __NR64AT3_sendto                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_sendto                   (struct sockaddr const *, struct sockaddr const *)
#define __NR64AT5_sendto                   (socklen_t, __socklen_t)
#define __NR64AT0_recvfrom                 (fd_t, __fd_t)
#define __NR64AT1_recvfrom                 (void *, void *)
#define __NR64AT2_recvfrom                 (size_t, __size_t)
#define __NR64AT3_recvfrom                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_recvfrom                 (struct sockaddr *, struct sockaddr *)
#define __NR64AT5_recvfrom                 (socklen_t *, __socklen_t *)
#define __NR64AT0_sendmsg                  (fd_t, __fd_t)
#define __NR64AT1_sendmsg                  (struct msghdrx64 const *, struct __msghdrx64 const *)
#define __NR64AT2_sendmsg                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_recvmsg                  (fd_t, __fd_t)
#define __NR64AT1_recvmsg                  (struct msghdrx64 *, struct __msghdrx64 *)
#define __NR64AT2_recvmsg                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_shutdown                 (fd_t, __fd_t)
#define __NR64AT1_shutdown                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_bind                     (fd_t, __fd_t)
#define __NR64AT1_bind                     (struct sockaddr const *, struct sockaddr const *)
#define __NR64AT2_bind                     (socklen_t, __socklen_t)
#define __NR64AT0_listen                   (fd_t, __fd_t)
#define __NR64AT1_listen                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_getsockname              (fd_t, __fd_t)
#define __NR64AT1_getsockname              (struct sockaddr *, struct sockaddr *)
#define __NR64AT2_getsockname              (socklen_t *, __socklen_t *)
#define __NR64AT0_getpeername              (fd_t, __fd_t)
#define __NR64AT1_getpeername              (struct sockaddr *, struct sockaddr *)
#define __NR64AT2_getpeername              (socklen_t *, __socklen_t *)
#define __NR64AT0_socketpair               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_socketpair               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_socketpair               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_socketpair               (fd_t *, __fd_t *)
#define __NR64AT0_setsockopt               (fd_t, __fd_t)
#define __NR64AT1_setsockopt               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_setsockopt               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_setsockopt               (void const *, void const *)
#define __NR64AT4_setsockopt               (socklen_t, __socklen_t)
#define __NR64AT0_getsockopt               (fd_t, __fd_t)
#define __NR64AT1_getsockopt               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_getsockopt               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_getsockopt               (void *, void *)
#define __NR64AT4_getsockopt               (socklen_t *, __socklen_t *)
#define __NR64AT0_clone                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_clone                    (void *, void *)
#define __NR64AT2_clone                    (pid_t *, __pid_t *)
#define __NR64AT3_clone                    (pid_t *, __pid_t *)
#define __NR64AT4_clone                    (uintptr_t, __uintptr_t)
#define __NR64AT0_execve                   (char const *, char const *)
#define __NR64AT1_execve                   (__HYBRID_PTR64(char const) const *, __HYBRID_PTR64(char const) const *)
#define __NR64AT2_execve                   (__HYBRID_PTR64(char const) const *, __HYBRID_PTR64(char const) const *)
#define __NR64AT0_exit                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_wait4                    (pid_t, __pid_t)
#define __NR64AT1_wait4                    (int32_t *, __int32_t *)
#define __NR64AT2_wait4                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_wait4                    (struct rusagex64 *, struct __rusagex64 *)
#define __NR64AT0_kill                     (pid_t, __pid_t)
#define __NR64AT1_kill                     (signo_t, __signo_t)
#define __NR64AT0_uname                    (struct utsname *, struct utsname *)
#define __NR64AT0_semget                   (int, int)
#define __NR64AT0_semop                    (int, int)
#define __NR64AT0_semctl                   (int, int)
#define __NR64AT0_shmdt                    (void const *, void const *)
#define __NR64AT0_msgget                   (int, int)
#define __NR64AT0_msgsnd                   (int, int)
#define __NR64AT0_msgrcv                   (int, int)
#define __NR64AT0_msgctl                   (int, int)
#define __NR64AT0_fcntl                    (fd_t, __fd_t)
#define __NR64AT1_fcntl                    (fcntl_t, __fcntl_t)
#define __NR64AT2_fcntl                    (void *, void *)
#define __NR64AT0_flock                    (fd_t, __fd_t)
#define __NR64AT1_flock                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_fsync                    (fd_t, __fd_t)
#define __NR64AT0_fdatasync                (fd_t, __fd_t)
#define __NR64AT0_truncate                 (char const *, char const *)
#define __NR64AT1_truncate                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_ftruncate                (fd_t, __fd_t)
#define __NR64AT1_ftruncate                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_getdents                 (fd_t, __fd_t)
#define __NR64AT1_getdents                 (struct linux_direntx64 *, struct linux_direntx64 *)
#define __NR64AT2_getdents                 (size_t, __size_t)
#define __NR64AT0_getcwd                   (char *, char *)
#define __NR64AT1_getcwd                   (size_t, __size_t)
#define __NR64AT0_chdir                    (char const *, char const *)
#define __NR64AT0_fchdir                   (fd_t, __fd_t)
#define __NR64AT0_rename                   (char const *, char const *)
#define __NR64AT1_rename                   (char const *, char const *)
#define __NR64AT0_mkdir                    (char const *, char const *)
#define __NR64AT1_mkdir                    (mode_t, __mode_t)
#define __NR64AT0_rmdir                    (char const *, char const *)
#define __NR64AT0_creat                    (char const *, char const *)
#define __NR64AT1_creat                    (mode_t, __mode_t)
#define __NR64AT0_link                     (char const *, char const *)
#define __NR64AT1_link                     (char const *, char const *)
#define __NR64AT0_unlink                   (char const *, char const *)
#define __NR64AT0_symlink                  (char const *, char const *)
#define __NR64AT1_symlink                  (char const *, char const *)
#define __NR64AT0_readlink                 (char const *, char const *)
#define __NR64AT1_readlink                 (char *, char *)
#define __NR64AT2_readlink                 (size_t, __size_t)
#define __NR64AT0_chmod                    (char const *, char const *)
#define __NR64AT1_chmod                    (mode_t, __mode_t)
#define __NR64AT0_fchmod                   (fd_t, __fd_t)
#define __NR64AT1_fchmod                   (mode_t, __mode_t)
#define __NR64AT0_chown                    (char const *, char const *)
#define __NR64AT1_chown                    (uid_t, __uid_t)
#define __NR64AT2_chown                    (gid_t, __gid_t)
#define __NR64AT0_fchown                   (fd_t, __fd_t)
#define __NR64AT1_fchown                   (uid_t, __uid_t)
#define __NR64AT2_fchown                   (gid_t, __gid_t)
#define __NR64AT0_lchown                   (char const *, char const *)
#define __NR64AT1_lchown                   (uid_t, __uid_t)
#define __NR64AT2_lchown                   (gid_t, __gid_t)
#define __NR64AT0_umask                    (mode_t, __mode_t)
#define __NR64AT0_gettimeofday             (struct timevalx64 *, struct __timevalx64 *)
#define __NR64AT1_gettimeofday             (struct timezone *, struct timezone *)
#define __NR64AT0_getrlimit                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_getrlimit                (struct rlimitx64 *, struct __rlimitx64 *)
#define __NR64AT0_getrusage                (syscall_slong_t, __syscall_slong_t)
#define __NR64AT1_getrusage                (struct rusagex64 *, struct __rusagex64 *)
#define __NR64AT0_sysinfo                  (struct __sysinfox64 *, struct __sysinfox64 *)
#define __NR64AT0_times                    (struct tmsx64 *, struct __tmsx64 *)
#define __NR64AT0_ptrace                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_ptrace                   (pid_t, __pid_t)
#define __NR64AT2_ptrace                   (void *, void *)
#define __NR64AT3_ptrace                   (void *, void *)
#define __NR64AT0_syslog                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_syslog                   (char const *, char const *)
#define __NR64AT2_syslog                   (size_t, __size_t)
#define __NR64AT0_setuid                   (uid_t, __uid_t)
#define __NR64AT0_setgid                   (gid_t, __gid_t)
#define __NR64AT0_setpgid                  (pid_t, __pid_t)
#define __NR64AT1_setpgid                  (pid_t, __pid_t)
#define __NR64AT0_setreuid                 (uid_t, __uid_t)
#define __NR64AT1_setreuid                 (uid_t, __uid_t)
#define __NR64AT0_setregid                 (gid_t, __gid_t)
#define __NR64AT1_setregid                 (gid_t, __gid_t)
#define __NR64AT0_getgroups                (size_t, __size_t)
#define __NR64AT1_getgroups                (gid_t *, __gid_t *)
#define __NR64AT0_setgroups                (size_t, __size_t)
#define __NR64AT1_setgroups                (gid_t const *, __gid_t const *)
#define __NR64AT0_setresuid                (uid_t, __uid_t)
#define __NR64AT1_setresuid                (uid_t, __uid_t)
#define __NR64AT2_setresuid                (uid_t, __uid_t)
#define __NR64AT0_getresuid                (uid_t *, __uid_t *)
#define __NR64AT1_getresuid                (uid_t *, __uid_t *)
#define __NR64AT2_getresuid                (uid_t *, __uid_t *)
#define __NR64AT0_setresgid                (gid_t, __gid_t)
#define __NR64AT1_setresgid                (gid_t, __gid_t)
#define __NR64AT2_setresgid                (gid_t, __gid_t)
#define __NR64AT0_getresgid                (gid_t *, __gid_t *)
#define __NR64AT1_getresgid                (gid_t *, __gid_t *)
#define __NR64AT2_getresgid                (gid_t *, __gid_t *)
#define __NR64AT0_getpgid                  (pid_t, __pid_t)
#define __NR64AT0_setfsuid                 (uid_t, __uid_t)
#define __NR64AT0_setfsgid                 (gid_t, __gid_t)
#define __NR64AT0_getsid                   (pid_t, __pid_t)
#define __NR64AT0_capget                   (int, int)
#define __NR64AT0_capset                   (int, int)
#define __NR64AT0_rt_sigpending            (struct __sigset_struct *, struct __sigset_struct *)
#define __NR64AT1_rt_sigpending            (size_t, __size_t)
#define __NR64AT0_rt_sigtimedwait          (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR64AT1_rt_sigtimedwait          (struct __siginfox64_struct *, struct __siginfox64_struct *)
#define __NR64AT2_rt_sigtimedwait          (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT3_rt_sigtimedwait          (size_t, __size_t)
#define __NR64AT0_rt_sigqueueinfo          (pid_t, __pid_t)
#define __NR64AT1_rt_sigqueueinfo          (signo_t, __signo_t)
#define __NR64AT2_rt_sigqueueinfo          (struct __siginfox64_struct const *, struct __siginfox64_struct const *)
#define __NR64AT0_rt_sigsuspend            (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR64AT1_rt_sigsuspend            (size_t, __size_t)
#define __NR64AT0_sigaltstack              (struct __sigaltstackx64 const *, struct __sigaltstackx64 const *)
#define __NR64AT1_sigaltstack              (struct __sigaltstackx64 *, struct __sigaltstackx64 *)
#define __NR64AT0_utime                    (char const *, char const *)
#define __NR64AT1_utime                    (struct utimbufx64 const *, struct __utimbufx64 const *)
#define __NR64AT0_mknod                    (char const *, char const *)
#define __NR64AT1_mknod                    (mode_t, __mode_t)
#define __NR64AT2_mknod                    (dev_t, __dev_t)
#define __NR64AT0_uselib                   (char const *, char const *)
#define __NR64AT0_personality              (int, int)
#define __NR64AT0_ustat                    (dev_t, __dev_t)
#define __NR64AT1_ustat                    (struct ustat *, struct ustat *)
#define __NR64AT0_statfs                   (char const *, char const *)
#define __NR64AT1_statfs                   (struct __statfsx64 *, struct __statfsx64 *)
#define __NR64AT0_fstatfs                  (fd_t, __fd_t)
#define __NR64AT1_fstatfs                  (struct __statfsx64 *, struct __statfsx64 *)
#define __NR64AT0_sysfs                    (int, int)
#define __NR64AT0_getpriority              (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_getpriority              (id_t, __id_t)
#define __NR64AT0_setpriority              (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_setpriority              (id_t, __id_t)
#define __NR64AT2_setpriority              (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_sched_setparam           (pid_t, __pid_t)
#define __NR64AT1_sched_setparam           (struct sched_param const *, struct sched_param const *)
#define __NR64AT0_sched_getparam           (pid_t, __pid_t)
#define __NR64AT1_sched_getparam           (struct sched_param *, struct sched_param *)
#define __NR64AT0_sched_setscheduler       (pid_t, __pid_t)
#define __NR64AT1_sched_setscheduler       (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_sched_setscheduler       (struct sched_param const *, struct sched_param const *)
#define __NR64AT0_sched_getscheduler       (pid_t, __pid_t)
#define __NR64AT0_sched_get_priority_max   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_sched_get_priority_min   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_sched_rr_get_interval    (pid_t, __pid_t)
#define __NR64AT1_sched_rr_get_interval    (struct timespecx64 *, struct __timespecx64 *)
#define __NR64AT0_mlock                    (void const *, void const *)
#define __NR64AT1_mlock                    (size_t, __size_t)
#define __NR64AT0_munlock                  (void const *, void const *)
#define __NR64AT1_munlock                  (size_t, __size_t)
#define __NR64AT0_mlockall                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_modify_ldt               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_modify_ldt               (void *, void *)
#define __NR64AT2_modify_ldt               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_pivot_root               (int, int)
#define __NR64AT0__sysctl                  (int, int)
#define __NR64AT0_prctl                    (unsigned int, unsigned int)
#define __NR64AT1_prctl                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_prctl                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_prctl                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_prctl                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_arch_prctl               (unsigned int, unsigned int)
#define __NR64AT1_arch_prctl               (uint64_t *, __uint64_t *)
#define __NR64AT0_adjtimex                 (struct timex *, struct timex *)
#define __NR64AT0_setrlimit                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_setrlimit                (struct rlimitx64 const *, struct __rlimitx64 const *)
#define __NR64AT0_chroot                   (char const *, char const *)
#define __NR64AT0_acct                     (char const *, char const *)
#define __NR64AT0_settimeofday             (struct timevalx64 const *, struct __timevalx64 const *)
#define __NR64AT1_settimeofday             (struct timezone const *, struct timezone const *)
#define __NR64AT0_mount                    (char const *, char const *)
#define __NR64AT1_mount                    (char const *, char const *)
#define __NR64AT2_mount                    (char const *, char const *)
#define __NR64AT3_mount                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_mount                    (void const *, void const *)
#define __NR64AT0_umount2                  (char const *, char const *)
#define __NR64AT1_umount2                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_swapon                   (char const *, char const *)
#define __NR64AT1_swapon                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_swapoff                  (char const *, char const *)
#define __NR64AT0_reboot                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_sethostname              (char const *, char const *)
#define __NR64AT1_sethostname              (size_t, __size_t)
#define __NR64AT0_setdomainname            (char const *, char const *)
#define __NR64AT1_setdomainname            (size_t, __size_t)
#define __NR64AT0_iopl                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_ioperm                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_ioperm                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_ioperm                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_init_module              (void const *, void const *)
#define __NR64AT1_init_module              (size_t, __size_t)
#define __NR64AT2_init_module              (char const *, char const *)
#define __NR64AT0_delete_module            (char const *, char const *)
#define __NR64AT1_delete_module            (oflag_t, __oflag_t)
#define __NR64AT0_quotactl                 (int, int)
#define __NR64AT0_nfsservctl               (int, int)
#define __NR64AT0_readahead                (fd_t, __fd_t)
#define __NR64AT1_readahead                (uint64_t, __uint64_t)
#define __NR64AT2_readahead                (size_t, __size_t)
#define __NR64AT0_setxattr                 (char const *, char const *)
#define __NR64AT1_setxattr                 (char const *, char const *)
#define __NR64AT2_setxattr                 (void const *, void const *)
#define __NR64AT3_setxattr                 (size_t, __size_t)
#define __NR64AT4_setxattr                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_lsetxattr                (char const *, char const *)
#define __NR64AT1_lsetxattr                (char const *, char const *)
#define __NR64AT2_lsetxattr                (void const *, void const *)
#define __NR64AT3_lsetxattr                (size_t, __size_t)
#define __NR64AT4_lsetxattr                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_fsetxattr                (fd_t, __fd_t)
#define __NR64AT1_fsetxattr                (char const *, char const *)
#define __NR64AT2_fsetxattr                (void const *, void const *)
#define __NR64AT3_fsetxattr                (size_t, __size_t)
#define __NR64AT4_fsetxattr                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_getxattr                 (char const *, char const *)
#define __NR64AT1_getxattr                 (char const *, char const *)
#define __NR64AT2_getxattr                 (void *, void *)
#define __NR64AT3_getxattr                 (size_t, __size_t)
#define __NR64AT0_lgetxattr                (char const *, char const *)
#define __NR64AT1_lgetxattr                (char const *, char const *)
#define __NR64AT2_lgetxattr                (void *, void *)
#define __NR64AT3_lgetxattr                (size_t, __size_t)
#define __NR64AT0_fgetxattr                (fd_t, __fd_t)
#define __NR64AT1_fgetxattr                (char const *, char const *)
#define __NR64AT2_fgetxattr                (void *, void *)
#define __NR64AT3_fgetxattr                (size_t, __size_t)
#define __NR64AT0_listxattr                (char const *, char const *)
#define __NR64AT1_listxattr                (char *, char *)
#define __NR64AT2_listxattr                (size_t, __size_t)
#define __NR64AT0_llistxattr               (char const *, char const *)
#define __NR64AT1_llistxattr               (char *, char *)
#define __NR64AT2_llistxattr               (size_t, __size_t)
#define __NR64AT0_flistxattr               (fd_t, __fd_t)
#define __NR64AT1_flistxattr               (char *, char *)
#define __NR64AT2_flistxattr               (size_t, __size_t)
#define __NR64AT0_removexattr              (char const *, char const *)
#define __NR64AT1_removexattr              (char const *, char const *)
#define __NR64AT0_lremovexattr             (char const *, char const *)
#define __NR64AT1_lremovexattr             (char const *, char const *)
#define __NR64AT0_fremovexattr             (fd_t, __fd_t)
#define __NR64AT1_fremovexattr             (char const *, char const *)
#define __NR64AT0_tkill                    (pid_t, __pid_t)
#define __NR64AT1_tkill                    (signo_t, __signo_t)
#define __NR64AT0_time                     (time32_t *, __time32_t *)
#define __NR64AT0_futex                    (uint32_t *, __uint32_t *)
#define __NR64AT1_futex                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_futex                    (uint32_t, __uint32_t)
#define __NR64AT3_futex                    (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT4_futex                    (uint32_t *, __uint32_t *)
#define __NR64AT5_futex                    (uint32_t, __uint32_t)
#define __NR64AT0_sched_setaffinity        (pid_t, __pid_t)
#define __NR64AT1_sched_setaffinity        (size_t, __size_t)
#define __NR64AT2_sched_setaffinity        (struct __cpu_set_struct const *, struct __cpu_set_struct const *)
#define __NR64AT0_sched_getaffinity        (pid_t, __pid_t)
#define __NR64AT1_sched_getaffinity        (size_t, __size_t)
#define __NR64AT2_sched_getaffinity        (struct __cpu_set_struct *, struct __cpu_set_struct *)
#define __NR64AT0_set_thread_area          (int, int)
#define __NR64AT0_io_setup                 (int, int)
#define __NR64AT0_io_destroy               (int, int)
#define __NR64AT0_io_getevents             (int, int)
#define __NR64AT0_io_submit                (int, int)
#define __NR64AT0_io_cancel                (int, int)
#define __NR64AT0_get_thread_area          (int, int)
#define __NR64AT0_lookup_dcookie           (int, int)
#define __NR64AT0_epoll_create             (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_epoll_ctl_old            (fd_t, __fd_t)
#define __NR64AT1_epoll_ctl_old            (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_epoll_ctl_old            (fd_t, __fd_t)
#define __NR64AT3_epoll_ctl_old            (struct epoll_event *, struct epoll_event *)
#define __NR64AT0_epoll_wait_old           (fd_t, __fd_t)
#define __NR64AT1_epoll_wait_old           (struct epoll_event *, struct epoll_event *)
#define __NR64AT2_epoll_wait_old           (size_t, __size_t)
#define __NR64AT3_epoll_wait_old           (syscall_slong_t, __syscall_slong_t)
#define __NR64AT0_remap_file_pages         (void *, void *)
#define __NR64AT1_remap_file_pages         (size_t, __size_t)
#define __NR64AT2_remap_file_pages         (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_remap_file_pages         (size_t, __size_t)
#define __NR64AT4_remap_file_pages         (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_getdents64               (fd_t, __fd_t)
#define __NR64AT1_getdents64               (struct linux_dirent64 *, struct linux_dirent64 *)
#define __NR64AT2_getdents64               (size_t, __size_t)
#define __NR64AT0_set_tid_address          (pid_t *, __pid_t *)
#define __NR64AT0_semtimedop               (int, int)
#define __NR64AT0_fadvise64                (int, int)
#define __NR64AT0_timer_create             (clockid_t, __clockid_t)
#define __NR64AT1_timer_create             (struct sigevent *, struct sigevent *)
#define __NR64AT2_timer_create             (timer_t *, __timer_t *)
#define __NR64AT0_timer_settime            (timer_t, __timer_t)
#define __NR64AT1_timer_settime            (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_timer_settime            (struct itimerspecx64 const *, struct __itimerspecx64 const *)
#define __NR64AT3_timer_settime            (struct itimerspecx64 *, struct __itimerspecx64 *)
#define __NR64AT0_timer_gettime            (timer_t, __timer_t)
#define __NR64AT1_timer_gettime            (struct itimerspecx64 *, struct __itimerspecx64 *)
#define __NR64AT0_timer_getoverrun         (timer_t, __timer_t)
#define __NR64AT0_timer_delete             (timer_t, __timer_t)
#define __NR64AT0_clock_settime            (clockid_t, __clockid_t)
#define __NR64AT1_clock_settime            (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT0_clock_gettime            (clockid_t, __clockid_t)
#define __NR64AT1_clock_gettime            (struct timespecx64 *, struct __timespecx64 *)
#define __NR64AT0_clock_getres             (clockid_t, __clockid_t)
#define __NR64AT1_clock_getres             (struct timespecx64 *, struct __timespecx64 *)
#define __NR64AT0_clock_nanosleep          (clockid_t, __clockid_t)
#define __NR64AT1_clock_nanosleep          (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_clock_nanosleep          (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT3_clock_nanosleep          (struct timespecx64 *, struct __timespecx64 *)
#define __NR64AT0_exit_group               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_epoll_wait               (fd_t, __fd_t)
#define __NR64AT1_epoll_wait               (struct epoll_event *, struct epoll_event *)
#define __NR64AT2_epoll_wait               (size_t, __size_t)
#define __NR64AT3_epoll_wait               (syscall_slong_t, __syscall_slong_t)
#define __NR64AT0_epoll_ctl                (fd_t, __fd_t)
#define __NR64AT1_epoll_ctl                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_epoll_ctl                (fd_t, __fd_t)
#define __NR64AT3_epoll_ctl                (struct epoll_event *, struct epoll_event *)
#define __NR64AT0_tgkill                   (pid_t, __pid_t)
#define __NR64AT1_tgkill                   (pid_t, __pid_t)
#define __NR64AT2_tgkill                   (signo_t, __signo_t)
#define __NR64AT0_utimes                   (char const *, char const *)
#define __NR64AT1_utimes                   (struct timevalx64 const *, struct __timevalx64 const *)
#define __NR64AT0_mbind                    (int, int)
#define __NR64AT0_set_mempolicy            (int, int)
#define __NR64AT0_get_mempolicy            (int, int)
#define __NR64AT0_mq_open                  (char const *, char const *)
#define __NR64AT1_mq_open                  (oflag_t, __oflag_t)
#define __NR64AT2_mq_open                  (mode_t, __mode_t)
#define __NR64AT0_mq_unlink                (char const *, char const *)
#define __NR64AT0_mq_timedsend             (fd_t, __fd_t)
#define __NR64AT1_mq_timedsend             (char const *, char const *)
#define __NR64AT2_mq_timedsend             (size_t, __size_t)
#define __NR64AT3_mq_timedsend             (uint32_t, __uint32_t)
#define __NR64AT4_mq_timedsend             (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT0_mq_timedreceive          (fd_t, __fd_t)
#define __NR64AT1_mq_timedreceive          (char *, char *)
#define __NR64AT2_mq_timedreceive          (size_t, __size_t)
#define __NR64AT3_mq_timedreceive          (uint32_t *, __uint32_t *)
#define __NR64AT4_mq_timedreceive          (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT0_mq_notify                (fd_t, __fd_t)
#define __NR64AT1_mq_notify                (struct sigevent const *, struct sigevent const *)
#define __NR64AT0_mq_getsetattr            (fd_t, __fd_t)
#define __NR64AT1_mq_getsetattr            (struct mq_attr const *, struct mq_attr const *)
#define __NR64AT2_mq_getsetattr            (struct mq_attr *, struct mq_attr *)
#define __NR64AT0_kexec_load               (int, int)
#define __NR64AT0_waitid                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_waitid                   (id_t, __id_t)
#define __NR64AT2_waitid                   (struct __siginfox64_struct *, struct __siginfox64_struct *)
#define __NR64AT3_waitid                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_waitid                   (struct rusagex64 *, struct __rusagex64 *)
#define __NR64AT0_add_key                  (int, int)
#define __NR64AT0_request_key              (int, int)
#define __NR64AT0_keyctl                   (int, int)
#define __NR64AT0_ioprio_set               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_ioprio_set               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_ioprio_set               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_ioprio_get               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_ioprio_get               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_inotify_init             (int, int)
#define __NR64AT0_inotify_add_watch        (int, int)
#define __NR64AT0_inotify_rm_watch         (int, int)
#define __NR64AT0_migrate_pages            (int, int)
#define __NR64AT0_openat                   (fd_t, __fd_t)
#define __NR64AT1_openat                   (char const *, char const *)
#define __NR64AT2_openat                   (oflag_t, __oflag_t)
#define __NR64AT3_openat                   (mode_t, __mode_t)
#define __NR64AT0_mkdirat                  (fd_t, __fd_t)
#define __NR64AT1_mkdirat                  (char const *, char const *)
#define __NR64AT2_mkdirat                  (mode_t, __mode_t)
#define __NR64AT0_mknodat                  (fd_t, __fd_t)
#define __NR64AT1_mknodat                  (char const *, char const *)
#define __NR64AT2_mknodat                  (mode_t, __mode_t)
#define __NR64AT3_mknodat                  (dev_t, __dev_t)
#define __NR64AT0_fchownat                 (fd_t, __fd_t)
#define __NR64AT1_fchownat                 (char const *, char const *)
#define __NR64AT2_fchownat                 (uid_t, __uid_t)
#define __NR64AT3_fchownat                 (gid_t, __gid_t)
#define __NR64AT4_fchownat                 (atflag_t, __atflag_t)
#define __NR64AT0_futimesat                (fd_t, __fd_t)
#define __NR64AT1_futimesat                (char const *, char const *)
#define __NR64AT2_futimesat                (struct timevalx64 const *, struct __timevalx64 const *)
#define __NR64AT0_newfstatat               (fd_t, __fd_t)
#define __NR64AT1_newfstatat               (char const *, char const *)
#define __NR64AT2_newfstatat               (struct linux64_stat32 *, struct linux64_stat32 *)
#define __NR64AT3_newfstatat               (atflag_t, __atflag_t)
#define __NR64AT0_unlinkat                 (fd_t, __fd_t)
#define __NR64AT1_unlinkat                 (char const *, char const *)
#define __NR64AT2_unlinkat                 (atflag_t, __atflag_t)
#define __NR64AT0_renameat                 (fd_t, __fd_t)
#define __NR64AT1_renameat                 (char const *, char const *)
#define __NR64AT2_renameat                 (fd_t, __fd_t)
#define __NR64AT3_renameat                 (char const *, char const *)
#define __NR64AT0_linkat                   (fd_t, __fd_t)
#define __NR64AT1_linkat                   (char const *, char const *)
#define __NR64AT2_linkat                   (fd_t, __fd_t)
#define __NR64AT3_linkat                   (char const *, char const *)
#define __NR64AT4_linkat                   (atflag_t, __atflag_t)
#define __NR64AT0_symlinkat                (char const *, char const *)
#define __NR64AT1_symlinkat                (fd_t, __fd_t)
#define __NR64AT2_symlinkat                (char const *, char const *)
#define __NR64AT0_readlinkat               (fd_t, __fd_t)
#define __NR64AT1_readlinkat               (char const *, char const *)
#define __NR64AT2_readlinkat               (char *, char *)
#define __NR64AT3_readlinkat               (size_t, __size_t)
#define __NR64AT0_fchmodat                 (fd_t, __fd_t)
#define __NR64AT1_fchmodat                 (char const *, char const *)
#define __NR64AT2_fchmodat                 (mode_t, __mode_t)
#define __NR64AT3_fchmodat                 (atflag_t, __atflag_t)
#define __NR64AT0_faccessat                (fd_t, __fd_t)
#define __NR64AT1_faccessat                (char const *, char const *)
#define __NR64AT2_faccessat                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_pselect6                 (size_t, __size_t)
#define __NR64AT1_pselect6                 (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR64AT2_pselect6                 (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR64AT3_pselect6                 (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR64AT4_pselect6                 (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT5_pselect6                 (struct __sigset_with_sizex64 const *, struct __sigset_with_sizex64 const *)
#define __NR64AT0_ppoll                    (struct pollfd *, struct pollfd *)
#define __NR64AT1_ppoll                    (size_t, __size_t)
#define __NR64AT2_ppoll                    (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT3_ppoll                    (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR64AT4_ppoll                    (size_t, __size_t)
#define __NR64AT0_unshare                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_set_robust_list          (int, int)
#define __NR64AT0_get_robust_list          (int, int)
#define __NR64AT0_splice                   (fd_t, __fd_t)
#define __NR64AT1_splice                   (uint64_t *, __uint64_t *)
#define __NR64AT2_splice                   (fd_t, __fd_t)
#define __NR64AT3_splice                   (uint64_t *, __uint64_t *)
#define __NR64AT4_splice                   (size_t, __size_t)
#define __NR64AT5_splice                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_tee                      (fd_t, __fd_t)
#define __NR64AT1_tee                      (fd_t, __fd_t)
#define __NR64AT2_tee                      (size_t, __size_t)
#define __NR64AT3_tee                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_sync_file_range          (fd_t, __fd_t)
#define __NR64AT1_sync_file_range          (uint64_t, __uint64_t)
#define __NR64AT2_sync_file_range          (uint64_t, __uint64_t)
#define __NR64AT3_sync_file_range          (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_vmsplice                 (fd_t, __fd_t)
#define __NR64AT1_vmsplice                 (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_vmsplice                 (size_t, __size_t)
#define __NR64AT3_vmsplice                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_move_pages               (int, int)
#define __NR64AT0_utimensat                (fd_t, __fd_t)
#define __NR64AT1_utimensat                (char const *, char const *)
#define __NR64AT2_utimensat                (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT3_utimensat                (atflag_t, __atflag_t)
#define __NR64AT0_epoll_pwait              (fd_t, __fd_t)
#define __NR64AT1_epoll_pwait              (struct epoll_event *, struct epoll_event *)
#define __NR64AT2_epoll_pwait              (size_t, __size_t)
#define __NR64AT3_epoll_pwait              (syscall_slong_t, __syscall_slong_t)
#define __NR64AT4_epoll_pwait              (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR64AT5_epoll_pwait              (size_t, __size_t)
#define __NR64AT0_signalfd                 (fd_t, __fd_t)
#define __NR64AT1_signalfd                 (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR64AT2_signalfd                 (size_t, __size_t)
#define __NR64AT0_timerfd_create           (clockid_t, __clockid_t)
#define __NR64AT1_timerfd_create           (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_eventfd                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_fallocate                (fd_t, __fd_t)
#define __NR64AT1_fallocate                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_fallocate                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_fallocate                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_timerfd_settime          (fd_t, __fd_t)
#define __NR64AT1_timerfd_settime          (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_timerfd_settime          (struct itimerspecx64 const *, struct __itimerspecx64 const *)
#define __NR64AT3_timerfd_settime          (struct itimerspecx64 *, struct __itimerspecx64 *)
#define __NR64AT0_timerfd_gettime          (fd_t, __fd_t)
#define __NR64AT1_timerfd_gettime          (struct itimerspecx64 *, struct __itimerspecx64 *)
#define __NR64AT0_accept4                  (fd_t, __fd_t)
#define __NR64AT1_accept4                  (struct sockaddr *, struct sockaddr *)
#define __NR64AT2_accept4                  (socklen_t *, __socklen_t *)
#define __NR64AT3_accept4                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_signalfd4                (fd_t, __fd_t)
#define __NR64AT1_signalfd4                (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR64AT2_signalfd4                (size_t, __size_t)
#define __NR64AT3_signalfd4                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_eventfd2                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_eventfd2                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_epoll_create1            (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_dup3                     (fd_t, __fd_t)
#define __NR64AT1_dup3                     (fd_t, __fd_t)
#define __NR64AT2_dup3                     (oflag_t, __oflag_t)
#define __NR64AT0_pipe2                    (fd_t *, __fd_t *)
#define __NR64AT1_pipe2                    (oflag_t, __oflag_t)
#define __NR64AT0_inotify_init1            (int, int)
#define __NR64AT0_preadv                   (fd_t, __fd_t)
#define __NR64AT1_preadv                   (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_preadv                   (size_t, __size_t)
#define __NR64AT3_preadv                   (uint64_t, __uint64_t)
#define __NR64AT0_pwritev                  (fd_t, __fd_t)
#define __NR64AT1_pwritev                  (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_pwritev                  (size_t, __size_t)
#define __NR64AT3_pwritev                  (uint64_t, __uint64_t)
#define __NR64AT0_rt_tgsigqueueinfo        (pid_t, __pid_t)
#define __NR64AT1_rt_tgsigqueueinfo        (pid_t, __pid_t)
#define __NR64AT2_rt_tgsigqueueinfo        (signo_t, __signo_t)
#define __NR64AT3_rt_tgsigqueueinfo        (struct __siginfox64_struct const *, struct __siginfox64_struct const *)
#define __NR64AT0_perf_event_open          (int, int)
#define __NR64AT0_recvmmsg                 (fd_t, __fd_t)
#define __NR64AT1_recvmmsg                 (struct mmsghdrx64 *, struct __mmsghdrx64 *)
#define __NR64AT2_recvmmsg                 (size_t, __size_t)
#define __NR64AT3_recvmmsg                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_recvmmsg                 (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT0_fanotify_init            (int, int)
#define __NR64AT0_fanotify_mark            (int, int)
#define __NR64AT0_prlimit64                (pid_t, __pid_t)
#define __NR64AT1_prlimit64                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_prlimit64                (struct rlimitx64 const *, struct __rlimitx64 const *)
#define __NR64AT3_prlimit64                (struct rlimitx64 *, struct __rlimitx64 *)
#define __NR64AT0_name_to_handle_at        (fd_t, __fd_t)
#define __NR64AT1_name_to_handle_at        (char const *, char const *)
#define __NR64AT2_name_to_handle_at        (struct file_handle *, struct file_handle *)
#define __NR64AT3_name_to_handle_at        (int32_t *, __int32_t *)
#define __NR64AT4_name_to_handle_at        (atflag_t, __atflag_t)
#define __NR64AT0_open_by_handle_at        (fd_t, __fd_t)
#define __NR64AT1_open_by_handle_at        (struct file_handle const *, struct file_handle const *)
#define __NR64AT2_open_by_handle_at        (oflag_t, __oflag_t)
#define __NR64AT0_clock_adjtime            (int, int)
#define __NR64AT0_syncfs                   (fd_t, __fd_t)
#define __NR64AT0_sendmmsg                 (fd_t, __fd_t)
#define __NR64AT1_sendmmsg                 (struct mmsghdrx64 *, struct __mmsghdrx64 *)
#define __NR64AT2_sendmmsg                 (size_t, __size_t)
#define __NR64AT3_sendmmsg                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_setns                    (fd_t, __fd_t)
#define __NR64AT1_setns                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_getcpu                   (uint32_t *, __uint32_t *)
#define __NR64AT1_getcpu                   (uint32_t *, __uint32_t *)
#define __NR64AT2_getcpu                   (struct getcpu_cache *, struct getcpu_cache *)
#define __NR64AT0_process_vm_readv         (pid_t, __pid_t)
#define __NR64AT1_process_vm_readv         (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_process_vm_readv         (size_t, __size_t)
#define __NR64AT3_process_vm_readv         (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT4_process_vm_readv         (size_t, __size_t)
#define __NR64AT5_process_vm_readv         (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_process_vm_writev        (pid_t, __pid_t)
#define __NR64AT1_process_vm_writev        (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_process_vm_writev        (size_t, __size_t)
#define __NR64AT3_process_vm_writev        (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT4_process_vm_writev        (size_t, __size_t)
#define __NR64AT5_process_vm_writev        (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_kcmp                     (pid_t, __pid_t)
#define __NR64AT1_kcmp                     (pid_t, __pid_t)
#define __NR64AT2_kcmp                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_kcmp                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_kcmp                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_finit_module             (fd_t, __fd_t)
#define __NR64AT1_finit_module             (char const *, char const *)
#define __NR64AT2_finit_module             (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_sched_setattr            (int, int)
#define __NR64AT0_sched_getattr            (int, int)
#define __NR64AT0_renameat2                (fd_t, __fd_t)
#define __NR64AT1_renameat2                (char const *, char const *)
#define __NR64AT2_renameat2                (fd_t, __fd_t)
#define __NR64AT3_renameat2                (char const *, char const *)
#define __NR64AT4_renameat2                (atflag_t, __atflag_t)
#define __NR64AT0_seccomp                  (int, int)
#define __NR64AT0_getrandom                (void *, void *)
#define __NR64AT1_getrandom                (size_t, __size_t)
#define __NR64AT2_getrandom                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_memfd_create             (char const *, char const *)
#define __NR64AT1_memfd_create             (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_kexec_file_load          (int, int)
#define __NR64AT0_bpf                      (int, int)
#define __NR64AT0_execveat                 (fd_t, __fd_t)
#define __NR64AT1_execveat                 (char const *, char const *)
#define __NR64AT2_execveat                 (__HYBRID_PTR64(char const) const *, __HYBRID_PTR64(char const) const *)
#define __NR64AT3_execveat                 (__HYBRID_PTR64(char const) const *, __HYBRID_PTR64(char const) const *)
#define __NR64AT4_execveat                 (atflag_t, __atflag_t)
#define __NR64AT0_userfaultfd              (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_membarrier               (int, int)
#define __NR64AT0_mlock2                   (void const *, void const *)
#define __NR64AT1_mlock2                   (size_t, __size_t)
#define __NR64AT2_mlock2                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_copy_file_range          (int, int)
#define __NR64AT0_preadv2                  (int, int)
#define __NR64AT0_pwritev2                 (int, int)
#define __NR64AT0_pkey_mprotect            (void *, void *)
#define __NR64AT1_pkey_mprotect            (size_t, __size_t)
#define __NR64AT2_pkey_mprotect            (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_pkey_mprotect            (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_pkey_alloc               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_pkey_alloc               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_pkey_free                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_statx                    (int, int)
#define __NR64AT0_io_pgetevents            (int, int)
#define __NR64AT0_rseq                     (int, int)
#define __NR64AT0_pidfd_send_signal        (fd_t, __fd_t)
#define __NR64AT1_pidfd_send_signal        (signo_t, __signo_t)
#define __NR64AT2_pidfd_send_signal        (struct __siginfox64_struct const *, struct __siginfox64_struct const *)
#define __NR64AT3_pidfd_send_signal        (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_io_uring_setup           (int, int)
#define __NR64AT0_io_uring_enter           (int, int)
#define __NR64AT0_io_uring_register        (int, int)
#define __NR64AT0_open_tree                (int, int)
#define __NR64AT0_move_mount               (int, int)
#define __NR64AT0_fsopen                   (int, int)
#define __NR64AT0_fsconfig                 (int, int)
#define __NR64AT0_fsmount                  (int, int)
#define __NR64AT0_fspick                   (int, int)
#define __NR64AT0_pidfd_open               (pid_t, __pid_t)
#define __NR64AT1_pidfd_open               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_clone3                   (struct clone_args *, struct clone_args *)
#define __NR64AT1_clone3                   (size_t, __size_t)
#define __NR64AT0_close_range              (unsigned int, unsigned int)
#define __NR64AT1_close_range              (unsigned int, unsigned int)
#define __NR64AT2_close_range              (unsigned int, unsigned int)
#define __NR64AT0_openat2                  (int, int)
#define __NR64AT0_pidfd_getfd              (fd_t, __fd_t)
#define __NR64AT1_pidfd_getfd              (fd_t, __fd_t)
#define __NR64AT2_pidfd_getfd              (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_faccessat2               (fd_t, __fd_t)
#define __NR64AT1_faccessat2               (char const *, char const *)
#define __NR64AT2_faccessat2               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT3_faccessat2               (atflag_t, __atflag_t)
#define __NR64AT0_pwritevf                 (fd_t, __fd_t)
#define __NR64AT1_pwritevf                 (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_pwritevf                 (size_t, __size_t)
#define __NR64AT3_pwritevf                 (uint64_t, __uint64_t)
#define __NR64AT4_pwritevf                 (iomode_t, __iomode_t)
#define __NR64AT0_preadvf                  (fd_t, __fd_t)
#define __NR64AT1_preadvf                  (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_preadvf                  (size_t, __size_t)
#define __NR64AT3_preadvf                  (uint64_t, __uint64_t)
#define __NR64AT4_preadvf                  (iomode_t, __iomode_t)
#define __NR64AT0_freadlinkat              (fd_t, __fd_t)
#define __NR64AT1_freadlinkat              (char const *, char const *)
#define __NR64AT2_freadlinkat              (char *, char *)
#define __NR64AT3_freadlinkat              (size_t, __size_t)
#define __NR64AT4_freadlinkat              (atflag_t, __atflag_t)
#define __NR64AT0_fsymlinkat               (char const *, char const *)
#define __NR64AT1_fsymlinkat               (fd_t, __fd_t)
#define __NR64AT2_fsymlinkat               (char const *, char const *)
#define __NR64AT3_fsymlinkat               (atflag_t, __atflag_t)
#define __NR64AT0_kfstatat                 (fd_t, __fd_t)
#define __NR64AT1_kfstatat                 (char const *, char const *)
#define __NR64AT2_kfstatat                 (struct __kos_stat *, struct __kos_stat *)
#define __NR64AT3_kfstatat                 (atflag_t, __atflag_t)
#define __NR64AT0_fmknodat                 (fd_t, __fd_t)
#define __NR64AT1_fmknodat                 (char const *, char const *)
#define __NR64AT2_fmknodat                 (mode_t, __mode_t)
#define __NR64AT3_fmknodat                 (dev_t, __dev_t)
#define __NR64AT4_fmknodat                 (atflag_t, __atflag_t)
#define __NR64AT0_fmkdirat                 (fd_t, __fd_t)
#define __NR64AT1_fmkdirat                 (char const *, char const *)
#define __NR64AT2_fmkdirat                 (mode_t, __mode_t)
#define __NR64AT3_fmkdirat                 (atflag_t, __atflag_t)
#define __NR64AT0_ksysctl                  (ioctl_t, __ioctl_t)
#define __NR64AT1_ksysctl                  (void *, void *)
#define __NR64AT0_maplibrary               (void *, void *)
#define __NR64AT1_maplibrary               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_maplibrary               (fd_t, __fd_t)
#define __NR64AT3_maplibrary               (struct elf64_phdr const *, struct elf64_phdr const *)
#define __NR64AT4_maplibrary               (size_t, __size_t)
#define __NR64AT0_fsmode                   (uint64_t, __uint64_t)
#define __NR64AT0_fchdirat                 (fd_t, __fd_t)
#define __NR64AT1_fchdirat                 (char const *, char const *)
#define __NR64AT2_fchdirat                 (atflag_t, __atflag_t)
#define __NR64AT0_kreaddirf                (fd_t, __fd_t)
#define __NR64AT1_kreaddirf                (struct dirent *, struct dirent *)
#define __NR64AT2_kreaddirf                (size_t, __size_t)
#define __NR64AT3_kreaddirf                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT4_kreaddirf                (iomode_t, __iomode_t)
#define __NR64AT0_kreaddir                 (fd_t, __fd_t)
#define __NR64AT1_kreaddir                 (struct dirent *, struct dirent *)
#define __NR64AT2_kreaddir                 (size_t, __size_t)
#define __NR64AT3_kreaddir                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_set_exception_handler    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT1_set_exception_handler    (except_handler_t, __except_handler_t)
#define __NR64AT2_set_exception_handler    (void *, void *)
#define __NR64AT0_get_exception_handler    (__ULONG64_TYPE__ *, __ULONG64_TYPE__ *)
#define __NR64AT1_get_exception_handler    (__except_handler64_t *, __except_handler64_t *)
#define __NR64AT2_get_exception_handler    (__HYBRID_PTR64(void) *, __HYBRID_PTR64(void) *)
#define __NR64AT0_set_userprocmask_address (struct userprocmask *, struct userprocmask *)
#define __NR64AT0_rtm_abort                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_userviofd                (size_t, __size_t)
#define __NR64AT1_userviofd                (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_coredump                 (struct ucpustate64 const *, struct ucpustate64 const *)
#define __NR64AT1_coredump                 (struct ucpustate64 const *, struct ucpustate64 const *)
#define __NR64AT2_coredump                 (__HYBRID_PTR64(void const) const *, __HYBRID_PTR64(void const) const *)
#define __NR64AT3_coredump                 (size_t, __size_t)
#define __NR64AT4_coredump                 (union coredump_info64 const *, union coredump_info64 const *)
#define __NR64AT5_coredump                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_mktty                    (char const *, char const *)
#define __NR64AT1_mktty                    (fd_t, __fd_t)
#define __NR64AT2_mktty                    (fd_t, __fd_t)
#define __NR64AT3_mktty                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_lfutexexpr               (uint64_t *, __uint64_t *)
#define __NR64AT1_lfutexexpr               (void *, void *)
#define __NR64AT2_lfutexexpr               (struct lfutexexprx64 const *, struct lfutexexprx64 const *)
#define __NR64AT3_lfutexexpr               (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT4_lfutexexpr               (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT0_lfutex                   (uint64_t *, __uint64_t *)
#define __NR64AT1_lfutex                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_lfutex                   (uint64_t, __uint64_t)
#define __NR64AT3_lfutex                   (struct timespecx64 const *, struct __timespecx64 const *)
#define __NR64AT4_lfutex                   (uint64_t, __uint64_t)
#define __NR64AT0_debugtrap                (struct ucpustate64 const *, struct ucpustate64 const *)
#define __NR64AT1_debugtrap                (struct debugtrap_reason64 const *, struct debugtrap_reason64 const *)
#define __NR64AT0_writevf                  (fd_t, __fd_t)
#define __NR64AT1_writevf                  (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_writevf                  (size_t, __size_t)
#define __NR64AT3_writevf                  (iomode_t, __iomode_t)
#define __NR64AT0_readvf                   (fd_t, __fd_t)
#define __NR64AT1_readvf                   (struct iovecx64 const *, struct __iovecx64 const *)
#define __NR64AT2_readvf                   (size_t, __size_t)
#define __NR64AT3_readvf                   (iomode_t, __iomode_t)
#define __NR64AT0_pwrite64f                (fd_t, __fd_t)
#define __NR64AT1_pwrite64f                (void const *, void const *)
#define __NR64AT2_pwrite64f                (size_t, __size_t)
#define __NR64AT3_pwrite64f                (uint64_t, __uint64_t)
#define __NR64AT4_pwrite64f                (iomode_t, __iomode_t)
#define __NR64AT0_pread64f                 (fd_t, __fd_t)
#define __NR64AT1_pread64f                 (void *, void *)
#define __NR64AT2_pread64f                 (size_t, __size_t)
#define __NR64AT3_pread64f                 (uint64_t, __uint64_t)
#define __NR64AT4_pread64f                 (iomode_t, __iomode_t)
#define __NR64AT0_ioctlf                   (fd_t, __fd_t)
#define __NR64AT1_ioctlf                   (ioctl_t, __ioctl_t)
#define __NR64AT2_ioctlf                   (iomode_t, __iomode_t)
#define __NR64AT3_ioctlf                   (void *, void *)
#define __NR64AT0_openpty                  (fd_t *, __fd_t *)
#define __NR64AT1_openpty                  (fd_t *, __fd_t *)
#define __NR64AT2_openpty                  (char *, char *)
#define __NR64AT3_openpty                  (struct termios const *, struct termios const *)
#define __NR64AT4_openpty                  (struct winsize const *, struct winsize const *)
#define __NR64AT0_rpc_schedule             (pid_t, __pid_t)
#define __NR64AT1_rpc_schedule             (syscall_ulong_t, __syscall_ulong_t)
#define __NR64AT2_rpc_schedule             (void const *, void const *)
#define __NR64AT3_rpc_schedule             (__HYBRID_PTR64(void const) const *, __HYBRID_PTR64(void const) const *)
#define __NR64AT4_rpc_schedule             (size_t, __size_t)
#define __NR64AT0_frealpathat              (fd_t, __fd_t)
#define __NR64AT1_frealpathat              (char const *, char const *)
#define __NR64AT2_frealpathat              (char *, char *)
#define __NR64AT3_frealpathat              (size_t, __size_t)
#define __NR64AT4_frealpathat              (atflag_t, __atflag_t)
#define __NR64AT0_frealpath4               (fd_t, __fd_t)
#define __NR64AT1_frealpath4               (char *, char *)
#define __NR64AT2_frealpath4               (size_t, __size_t)
#define __NR64AT3_frealpath4               (atflag_t, __atflag_t)
#define __NR64AT0_detach                   (pid_t, __pid_t)
#define __NR64AT0_readf                    (fd_t, __fd_t)
#define __NR64AT1_readf                    (void *, void *)
#define __NR64AT2_readf                    (size_t, __size_t)
#define __NR64AT3_readf                    (iomode_t, __iomode_t)
#define __NR64AT0_klstat                   (char const *, char const *)
#define __NR64AT1_klstat                   (struct __kos_stat *, struct __kos_stat *)
#define __NR64AT0_kfstat                   (fd_t, __fd_t)
#define __NR64AT1_kfstat                   (struct __kos_stat *, struct __kos_stat *)
#define __NR64AT0_kstat                    (char const *, char const *)
#define __NR64AT1_kstat                    (struct __kos_stat *, struct __kos_stat *)
#define __NR64AT0_writef                   (fd_t, __fd_t)
#define __NR64AT1_writef                   (void const *, void const *)
#define __NR64AT2_writef                   (size_t, __size_t)
#define __NR64AT3_writef                   (iomode_t, __iomode_t)
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES */
#endif /* __WANT_SYSCALL_ARGUMENT_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT LIST MAKING                                         */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_MAKER
#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NR64AM_read(a, b, c, d, e, f)                     (__fd_t)a, (void *)b, (__size_t)c
#define __NR64AM_write(a, b, c, d, e, f)                    (__fd_t)a, (void const *)b, (__size_t)c
#define __NR64AM_open(a, b, c, d, e, f)                     (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NR64AM_close(a, b, c, d, e, f)                    (__fd_t)a
#define __NR64AM_stat(a, b, c, d, e, f)                     (char const *)a, (struct linux_statx64 *)b
#define __NR64AM_fstat(a, b, c, d, e, f)                    (__fd_t)a, (struct linux_statx64 *)b
#define __NR64AM_lstat(a, b, c, d, e, f)                    (char const *)a, (struct linux_statx64 *)b
#define __NR64AM_poll(a, b, c, d, e, f)                     (struct pollfd *)a, (__size_t)b, (__syscall_slong_t)c
#define __NR64AM_lseek(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_slong_t)b, (__syscall_ulong_t)c
#define __NR64AM_mmap(a, b, c, d, e, f)                     (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NR64AM_mprotect(a, b, c, d, e, f)                 (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR64AM_munmap(a, b, c, d, e, f)                   (void *)a, (__size_t)b
#define __NR64AM_brk(a, b, c, d, e, f)                      (void *)a
#define __NR64AM_rt_sigaction(a, b, c, d, e, f)             (__signo_t)a, (struct __kernel_sigactionx64 const *)b, (struct __kernel_sigactionx64 *)c, (__size_t)d
#define __NR64AM_rt_sigprocmask(a, b, c, d, e, f)           (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c, (__size_t)d
#define __NR64AM_rt_sigreturn(a, b, c, d, e, f)             /* nothing */
#define __NR64AM_ioctl(a, b, c, d, e, f)                    (__fd_t)a, (__ioctl_t)b, (void *)c
#define __NR64AM_pread64(a, b, c, d, e, f)                  (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)d
#define __NR64AM_pwrite64(a, b, c, d, e, f)                 (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)d
#define __NR64AM_readv(a, b, c, d, e, f)                    (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c
#define __NR64AM_writev(a, b, c, d, e, f)                   (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c
#define __NR64AM_access(a, b, c, d, e, f)                   (char const *)a, (__syscall_ulong_t)b
#define __NR64AM_pipe(a, b, c, d, e, f)                     (__fd_t *)a
#define __NR64AM_select(a, b, c, d, e, f)                   (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timevalx64 *)e
#define __NR64AM_sched_yield(a, b, c, d, e, f)              /* nothing */
#define __NR64AM_mremap(a, b, c, d, e, f)                   (void *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d, (void *)e
#define __NR64AM_msync(a, b, c, d, e, f)                    (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR64AM_mincore(a, b, c, d, e, f)                  (void *)a, (__size_t)b, (__uint8_t *)c
#define __NR64AM_madvise(a, b, c, d, e, f)                  (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR64AM_shmget(a, b, c, d, e, f)                   (__key_t)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR64AM_shmat(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (void const *)b, (__syscall_ulong_t)c
#define __NR64AM_shmctl(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (struct shmid_ds *)c
#define __NR64AM_dup(a, b, c, d, e, f)                      (__fd_t)a
#define __NR64AM_dup2(a, b, c, d, e, f)                     (__fd_t)a, (__fd_t)b
#define __NR64AM_pause(a, b, c, d, e, f)                    /* nothing */
#define __NR64AM_nanosleep(a, b, c, d, e, f)                (struct __timespecx64 const *)a, (struct __timespecx64 *)b
#define __NR64AM_getitimer(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __itimervalx64 *)b
#define __NR64AM_alarm(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NR64AM_setitimer(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __itimervalx64 const *)b, (struct __itimervalx64 *)c
#define __NR64AM_getpid(a, b, c, d, e, f)                   /* nothing */
#define __NR64AM_sendfile(a, b, c, d, e, f)                 (__fd_t)a, (__fd_t)b, (__syscall_ulong_t *)c, (__size_t)d
#define __NR64AM_socket(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AM_connect(a, b, c, d, e, f)                  (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NR64AM_accept(a, b, c, d, e, f)                   (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NR64AM_sendto(a, b, c, d, e, f)                   (__fd_t)a, (void const *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr const *)e, (__socklen_t)f
#define __NR64AM_recvfrom(a, b, c, d, e, f)                 (__fd_t)a, (void *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr *)e, (__socklen_t *)f
#define __NR64AM_sendmsg(a, b, c, d, e, f)                  (__fd_t)a, (struct __msghdrx64 const *)b, (__syscall_ulong_t)c
#define __NR64AM_recvmsg(a, b, c, d, e, f)                  (__fd_t)a, (struct __msghdrx64 *)b, (__syscall_ulong_t)c
#define __NR64AM_shutdown(a, b, c, d, e, f)                 (__fd_t)a, (__syscall_ulong_t)b
#define __NR64AM_bind(a, b, c, d, e, f)                     (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NR64AM_listen(a, b, c, d, e, f)                   (__fd_t)a, (__syscall_ulong_t)b
#define __NR64AM_getsockname(a, b, c, d, e, f)              (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NR64AM_getpeername(a, b, c, d, e, f)              (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NR64AM_socketpair(a, b, c, d, e, f)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__fd_t *)d
#define __NR64AM_setsockopt(a, b, c, d, e, f)               (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void const *)d, (__socklen_t)e
#define __NR64AM_getsockopt(a, b, c, d, e, f)               (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void *)d, (__socklen_t *)e
#define __NR64AM_clone(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (void *)b, (__pid_t *)c, (__pid_t *)d, (__uintptr_t)e
#define __NR64AM_fork(a, b, c, d, e, f)                     /* nothing */
#define __NR64AM_vfork(a, b, c, d, e, f)                    /* nothing */
#define __NR64AM_execve(a, b, c, d, e, f)                   (char const *)a, (__HYBRID_PTR64(char const) const *)b, (__HYBRID_PTR64(char const) const *)c
#define __NR64AM_exit(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NR64AM_wait4(a, b, c, d, e, f)                    (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct __rusagex64 *)d
#define __NR64AM_kill(a, b, c, d, e, f)                     (__pid_t)a, (__signo_t)b
#define __NR64AM_uname(a, b, c, d, e, f)                    (struct utsname *)a
#define __NR64AM_semget(a, b, c, d, e, f)                   (int)a
#define __NR64AM_semop(a, b, c, d, e, f)                    (int)a
#define __NR64AM_semctl(a, b, c, d, e, f)                   (int)a
#define __NR64AM_shmdt(a, b, c, d, e, f)                    (void const *)a
#define __NR64AM_msgget(a, b, c, d, e, f)                   (int)a
#define __NR64AM_msgsnd(a, b, c, d, e, f)                   (int)a
#define __NR64AM_msgrcv(a, b, c, d, e, f)                   (int)a
#define __NR64AM_msgctl(a, b, c, d, e, f)                   (int)a
#define __NR64AM_fcntl(a, b, c, d, e, f)                    (__fd_t)a, (__fcntl_t)b, (void *)c
#define __NR64AM_flock(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b
#define __NR64AM_fsync(a, b, c, d, e, f)                    (__fd_t)a
#define __NR64AM_fdatasync(a, b, c, d, e, f)                (__fd_t)a
#define __NR64AM_truncate(a, b, c, d, e, f)                 (char const *)a, (__syscall_ulong_t)b
#define __NR64AM_ftruncate(a, b, c, d, e, f)                (__fd_t)a, (__syscall_ulong_t)b
#define __NR64AM_getdents(a, b, c, d, e, f)                 (__fd_t)a, (struct linux_direntx64 *)b, (__size_t)c
#define __NR64AM_getcwd(a, b, c, d, e, f)                   (char *)a, (__size_t)b
#define __NR64AM_chdir(a, b, c, d, e, f)                    (char const *)a
#define __NR64AM_fchdir(a, b, c, d, e, f)                   (__fd_t)a
#define __NR64AM_rename(a, b, c, d, e, f)                   (char const *)a, (char const *)b
#define __NR64AM_mkdir(a, b, c, d, e, f)                    (char const *)a, (__mode_t)b
#define __NR64AM_rmdir(a, b, c, d, e, f)                    (char const *)a
#define __NR64AM_creat(a, b, c, d, e, f)                    (char const *)a, (__mode_t)b
#define __NR64AM_link(a, b, c, d, e, f)                     (char const *)a, (char const *)b
#define __NR64AM_unlink(a, b, c, d, e, f)                   (char const *)a
#define __NR64AM_symlink(a, b, c, d, e, f)                  (char const *)a, (char const *)b
#define __NR64AM_readlink(a, b, c, d, e, f)                 (char const *)a, (char *)b, (__size_t)c
#define __NR64AM_chmod(a, b, c, d, e, f)                    (char const *)a, (__mode_t)b
#define __NR64AM_fchmod(a, b, c, d, e, f)                   (__fd_t)a, (__mode_t)b
#define __NR64AM_chown(a, b, c, d, e, f)                    (char const *)a, (__uid_t)b, (__gid_t)c
#define __NR64AM_fchown(a, b, c, d, e, f)                   (__fd_t)a, (__uid_t)b, (__gid_t)c
#define __NR64AM_lchown(a, b, c, d, e, f)                   (char const *)a, (__uid_t)b, (__gid_t)c
#define __NR64AM_umask(a, b, c, d, e, f)                    (__mode_t)a
#define __NR64AM_gettimeofday(a, b, c, d, e, f)             (struct __timevalx64 *)a, (struct timezone *)b
#define __NR64AM_getrlimit(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __rlimitx64 *)b
#define __NR64AM_getrusage(a, b, c, d, e, f)                (__syscall_slong_t)a, (struct __rusagex64 *)b
#define __NR64AM_sysinfo(a, b, c, d, e, f)                  (struct __sysinfox64 *)a
#define __NR64AM_times(a, b, c, d, e, f)                    (struct __tmsx64 *)a
#define __NR64AM_ptrace(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__pid_t)b, (void *)c, (void *)d
#define __NR64AM_getuid(a, b, c, d, e, f)                   /* nothing */
#define __NR64AM_syslog(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (char const *)b, (__size_t)c
#define __NR64AM_getgid(a, b, c, d, e, f)                   /* nothing */
#define __NR64AM_setuid(a, b, c, d, e, f)                   (__uid_t)a
#define __NR64AM_setgid(a, b, c, d, e, f)                   (__gid_t)a
#define __NR64AM_geteuid(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_getegid(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_setpgid(a, b, c, d, e, f)                  (__pid_t)a, (__pid_t)b
#define __NR64AM_getppid(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_getpgrp(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_setsid(a, b, c, d, e, f)                   /* nothing */
#define __NR64AM_setreuid(a, b, c, d, e, f)                 (__uid_t)a, (__uid_t)b
#define __NR64AM_setregid(a, b, c, d, e, f)                 (__gid_t)a, (__gid_t)b
#define __NR64AM_getgroups(a, b, c, d, e, f)                (__size_t)a, (__gid_t *)b
#define __NR64AM_setgroups(a, b, c, d, e, f)                (__size_t)a, (__gid_t const *)b
#define __NR64AM_setresuid(a, b, c, d, e, f)                (__uid_t)a, (__uid_t)b, (__uid_t)c
#define __NR64AM_getresuid(a, b, c, d, e, f)                (__uid_t *)a, (__uid_t *)b, (__uid_t *)c
#define __NR64AM_setresgid(a, b, c, d, e, f)                (__gid_t)a, (__gid_t)b, (__gid_t)c
#define __NR64AM_getresgid(a, b, c, d, e, f)                (__gid_t *)a, (__gid_t *)b, (__gid_t *)c
#define __NR64AM_getpgid(a, b, c, d, e, f)                  (__pid_t)a
#define __NR64AM_setfsuid(a, b, c, d, e, f)                 (__uid_t)a
#define __NR64AM_setfsgid(a, b, c, d, e, f)                 (__gid_t)a
#define __NR64AM_getsid(a, b, c, d, e, f)                   (__pid_t)a
#define __NR64AM_capget(a, b, c, d, e, f)                   (int)a
#define __NR64AM_capset(a, b, c, d, e, f)                   (int)a
#define __NR64AM_rt_sigpending(a, b, c, d, e, f)            (struct __sigset_struct *)a, (__size_t)b
#define __NR64AM_rt_sigtimedwait(a, b, c, d, e, f)          (struct __sigset_struct const *)a, (struct __siginfox64_struct *)b, (struct __timespecx64 const *)c, (__size_t)d
#define __NR64AM_rt_sigqueueinfo(a, b, c, d, e, f)          (__pid_t)a, (__signo_t)b, (struct __siginfox64_struct const *)c
#define __NR64AM_rt_sigsuspend(a, b, c, d, e, f)            (struct __sigset_struct const *)a, (__size_t)b
#define __NR64AM_sigaltstack(a, b, c, d, e, f)              (struct __sigaltstackx64 const *)a, (struct __sigaltstackx64 *)b
#define __NR64AM_utime(a, b, c, d, e, f)                    (char const *)a, (struct __utimbufx64 const *)b
#define __NR64AM_mknod(a, b, c, d, e, f)                    (char const *)a, (__mode_t)b, (__dev_t)c
#define __NR64AM_uselib(a, b, c, d, e, f)                   (char const *)a
#define __NR64AM_personality(a, b, c, d, e, f)              (int)a
#define __NR64AM_ustat(a, b, c, d, e, f)                    (__dev_t)a, (struct ustat *)b
#define __NR64AM_statfs(a, b, c, d, e, f)                   (char const *)a, (struct __statfsx64 *)b
#define __NR64AM_fstatfs(a, b, c, d, e, f)                  (__fd_t)a, (struct __statfsx64 *)b
#define __NR64AM_sysfs(a, b, c, d, e, f)                    (int)a
#define __NR64AM_getpriority(a, b, c, d, e, f)              (__syscall_ulong_t)a, (__id_t)b
#define __NR64AM_setpriority(a, b, c, d, e, f)              (__syscall_ulong_t)a, (__id_t)b, (__syscall_ulong_t)c
#define __NR64AM_sched_setparam(a, b, c, d, e, f)           (__pid_t)a, (struct sched_param const *)b
#define __NR64AM_sched_getparam(a, b, c, d, e, f)           (__pid_t)a, (struct sched_param *)b
#define __NR64AM_sched_setscheduler(a, b, c, d, e, f)       (__pid_t)a, (__syscall_ulong_t)b, (struct sched_param const *)c
#define __NR64AM_sched_getscheduler(a, b, c, d, e, f)       (__pid_t)a
#define __NR64AM_sched_get_priority_max(a, b, c, d, e, f)   (__syscall_ulong_t)a
#define __NR64AM_sched_get_priority_min(a, b, c, d, e, f)   (__syscall_ulong_t)a
#define __NR64AM_sched_rr_get_interval(a, b, c, d, e, f)    (__pid_t)a, (struct __timespecx64 *)b
#define __NR64AM_mlock(a, b, c, d, e, f)                    (void const *)a, (__size_t)b
#define __NR64AM_munlock(a, b, c, d, e, f)                  (void const *)a, (__size_t)b
#define __NR64AM_mlockall(a, b, c, d, e, f)                 (__syscall_ulong_t)a
#define __NR64AM_munlockall(a, b, c, d, e, f)               /* nothing */
#define __NR64AM_vhangup(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_modify_ldt(a, b, c, d, e, f)               (__syscall_ulong_t)a, (void *)b, (__syscall_ulong_t)c
#define __NR64AM_pivot_root(a, b, c, d, e, f)               (int)a
#define __NR64AM__sysctl(a, b, c, d, e, f)                  (int)a
#define __NR64AM_prctl(a, b, c, d, e, f)                    (unsigned int)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AM_arch_prctl(a, b, c, d, e, f)               (unsigned int)a, (__uint64_t *)b
#define __NR64AM_adjtimex(a, b, c, d, e, f)                 (struct timex *)a
#define __NR64AM_setrlimit(a, b, c, d, e, f)                (__syscall_ulong_t)a, (struct __rlimitx64 const *)b
#define __NR64AM_chroot(a, b, c, d, e, f)                   (char const *)a
#define __NR64AM_sync(a, b, c, d, e, f)                     /* nothing */
#define __NR64AM_acct(a, b, c, d, e, f)                     (char const *)a
#define __NR64AM_settimeofday(a, b, c, d, e, f)             (struct __timevalx64 const *)a, (struct timezone const *)b
#define __NR64AM_mount(a, b, c, d, e, f)                    (char const *)a, (char const *)b, (char const *)c, (__syscall_ulong_t)d, (void const *)e
#define __NR64AM_umount2(a, b, c, d, e, f)                  (char const *)a, (__syscall_ulong_t)b
#define __NR64AM_swapon(a, b, c, d, e, f)                   (char const *)a, (__syscall_ulong_t)b
#define __NR64AM_swapoff(a, b, c, d, e, f)                  (char const *)a
#define __NR64AM_reboot(a, b, c, d, e, f)                   (__syscall_ulong_t)a
#define __NR64AM_sethostname(a, b, c, d, e, f)              (char const *)a, (__size_t)b
#define __NR64AM_setdomainname(a, b, c, d, e, f)            (char const *)a, (__size_t)b
#define __NR64AM_iopl(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NR64AM_ioperm(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AM_create_module(a, b, c, d, e, f)            /* nothing */
#define __NR64AM_init_module(a, b, c, d, e, f)              (void const *)a, (__size_t)b, (char const *)c
#define __NR64AM_delete_module(a, b, c, d, e, f)            (char const *)a, (__oflag_t)b
#define __NR64AM_get_kernel_syms(a, b, c, d, e, f)          /* nothing */
#define __NR64AM_query_module(a, b, c, d, e, f)             /* nothing */
#define __NR64AM_quotactl(a, b, c, d, e, f)                 (int)a
#define __NR64AM_nfsservctl(a, b, c, d, e, f)               (int)a
#define __NR64AM_getpmsg(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_putpmsg(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_afs_syscall(a, b, c, d, e, f)              /* nothing */
#define __NR64AM_tuxcall(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_security(a, b, c, d, e, f)                 /* nothing */
#define __NR64AM_gettid(a, b, c, d, e, f)                   /* nothing */
#define __NR64AM_readahead(a, b, c, d, e, f)                (__fd_t)a, (__uint64_t)b, (__size_t)c
#define __NR64AM_setxattr(a, b, c, d, e, f)                 (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR64AM_lsetxattr(a, b, c, d, e, f)                (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR64AM_fsetxattr(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR64AM_getxattr(a, b, c, d, e, f)                 (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NR64AM_lgetxattr(a, b, c, d, e, f)                (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NR64AM_fgetxattr(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (void *)c, (__size_t)d
#define __NR64AM_listxattr(a, b, c, d, e, f)                (char const *)a, (char *)b, (__size_t)c
#define __NR64AM_llistxattr(a, b, c, d, e, f)               (char const *)a, (char *)b, (__size_t)c
#define __NR64AM_flistxattr(a, b, c, d, e, f)               (__fd_t)a, (char *)b, (__size_t)c
#define __NR64AM_removexattr(a, b, c, d, e, f)              (char const *)a, (char const *)b
#define __NR64AM_lremovexattr(a, b, c, d, e, f)             (char const *)a, (char const *)b
#define __NR64AM_fremovexattr(a, b, c, d, e, f)             (__fd_t)a, (char const *)b
#define __NR64AM_tkill(a, b, c, d, e, f)                    (__pid_t)a, (__signo_t)b
#define __NR64AM_time(a, b, c, d, e, f)                     (__time32_t *)a
#define __NR64AM_futex(a, b, c, d, e, f)                    (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespecx64 const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NR64AM_sched_setaffinity(a, b, c, d, e, f)        (__pid_t)a, (__size_t)b, (struct __cpu_set_struct const *)c
#define __NR64AM_sched_getaffinity(a, b, c, d, e, f)        (__pid_t)a, (__size_t)b, (struct __cpu_set_struct *)c
#define __NR64AM_set_thread_area(a, b, c, d, e, f)          (int)a
#define __NR64AM_io_setup(a, b, c, d, e, f)                 (int)a
#define __NR64AM_io_destroy(a, b, c, d, e, f)               (int)a
#define __NR64AM_io_getevents(a, b, c, d, e, f)             (int)a
#define __NR64AM_io_submit(a, b, c, d, e, f)                (int)a
#define __NR64AM_io_cancel(a, b, c, d, e, f)                (int)a
#define __NR64AM_get_thread_area(a, b, c, d, e, f)          (int)a
#define __NR64AM_lookup_dcookie(a, b, c, d, e, f)           (int)a
#define __NR64AM_epoll_create(a, b, c, d, e, f)             (__syscall_ulong_t)a
#define __NR64AM_epoll_ctl_old(a, b, c, d, e, f)            (__fd_t)a, (__syscall_ulong_t)b, (__fd_t)c, (struct epoll_event *)d
#define __NR64AM_epoll_wait_old(a, b, c, d, e, f)           (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d
#define __NR64AM_remap_file_pages(a, b, c, d, e, f)         (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR64AM_getdents64(a, b, c, d, e, f)               (__fd_t)a, (struct linux_dirent64 *)b, (__size_t)c
#define __NR64AM_set_tid_address(a, b, c, d, e, f)          (__pid_t *)a
#define __NR64AM_restart_syscall(a, b, c, d, e, f)          /* nothing */
#define __NR64AM_semtimedop(a, b, c, d, e, f)               (int)a
#define __NR64AM_fadvise64(a, b, c, d, e, f)                (int)a
#define __NR64AM_timer_create(a, b, c, d, e, f)             (__clockid_t)a, (struct sigevent *)b, (__timer_t *)c
#define __NR64AM_timer_settime(a, b, c, d, e, f)            (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspecx64 const *)c, (struct __itimerspecx64 *)d
#define __NR64AM_timer_gettime(a, b, c, d, e, f)            (__timer_t)a, (struct __itimerspecx64 *)b
#define __NR64AM_timer_getoverrun(a, b, c, d, e, f)         (__timer_t)a
#define __NR64AM_timer_delete(a, b, c, d, e, f)             (__timer_t)a
#define __NR64AM_clock_settime(a, b, c, d, e, f)            (__clockid_t)a, (struct __timespecx64 const *)b
#define __NR64AM_clock_gettime(a, b, c, d, e, f)            (__clockid_t)a, (struct __timespecx64 *)b
#define __NR64AM_clock_getres(a, b, c, d, e, f)             (__clockid_t)a, (struct __timespecx64 *)b
#define __NR64AM_clock_nanosleep(a, b, c, d, e, f)          (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespecx64 const *)c, (struct __timespecx64 *)d
#define __NR64AM_exit_group(a, b, c, d, e, f)               (__syscall_ulong_t)a
#define __NR64AM_epoll_wait(a, b, c, d, e, f)               (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d
#define __NR64AM_epoll_ctl(a, b, c, d, e, f)                (__fd_t)a, (__syscall_ulong_t)b, (__fd_t)c, (struct epoll_event *)d
#define __NR64AM_tgkill(a, b, c, d, e, f)                   (__pid_t)a, (__pid_t)b, (__signo_t)c
#define __NR64AM_utimes(a, b, c, d, e, f)                   (char const *)a, (struct __timevalx64 const *)b
#define __NR64AM_vserver(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_mbind(a, b, c, d, e, f)                    (int)a
#define __NR64AM_set_mempolicy(a, b, c, d, e, f)            (int)a
#define __NR64AM_get_mempolicy(a, b, c, d, e, f)            (int)a
#define __NR64AM_mq_open(a, b, c, d, e, f)                  (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NR64AM_mq_unlink(a, b, c, d, e, f)                (char const *)a
#define __NR64AM_mq_timedsend(a, b, c, d, e, f)             (__fd_t)a, (char const *)b, (__size_t)c, (__uint32_t)d, (struct __timespecx64 const *)e
#define __NR64AM_mq_timedreceive(a, b, c, d, e, f)          (__fd_t)a, (char *)b, (__size_t)c, (__uint32_t *)d, (struct __timespecx64 const *)e
#define __NR64AM_mq_notify(a, b, c, d, e, f)                (__fd_t)a, (struct sigevent const *)b
#define __NR64AM_mq_getsetattr(a, b, c, d, e, f)            (__fd_t)a, (struct mq_attr const *)b, (struct mq_attr *)c
#define __NR64AM_kexec_load(a, b, c, d, e, f)               (int)a
#define __NR64AM_waitid(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__id_t)b, (struct __siginfox64_struct *)c, (__syscall_ulong_t)d, (struct __rusagex64 *)e
#define __NR64AM_add_key(a, b, c, d, e, f)                  (int)a
#define __NR64AM_request_key(a, b, c, d, e, f)              (int)a
#define __NR64AM_keyctl(a, b, c, d, e, f)                   (int)a
#define __NR64AM_ioprio_set(a, b, c, d, e, f)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AM_ioprio_get(a, b, c, d, e, f)               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AM_inotify_init(a, b, c, d, e, f)             (int)a
#define __NR64AM_inotify_add_watch(a, b, c, d, e, f)        (int)a
#define __NR64AM_inotify_rm_watch(a, b, c, d, e, f)         (int)a
#define __NR64AM_migrate_pages(a, b, c, d, e, f)            (int)a
#define __NR64AM_openat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__oflag_t)c, (__mode_t)d
#define __NR64AM_mkdirat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__mode_t)c
#define __NR64AM_mknodat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d
#define __NR64AM_fchownat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__uid_t)c, (__gid_t)d, (__atflag_t)e
#define __NR64AM_futimesat(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (struct __timevalx64 const *)c
#define __NR64AM_newfstatat(a, b, c, d, e, f)               (__fd_t)a, (char const *)b, (struct linux64_stat32 *)c, (__atflag_t)d
#define __NR64AM_unlinkat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NR64AM_renameat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d
#define __NR64AM_linkat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NR64AM_symlinkat(a, b, c, d, e, f)                (char const *)a, (__fd_t)b, (char const *)c
#define __NR64AM_readlinkat(a, b, c, d, e, f)               (__fd_t)a, (char const *)b, (char *)c, (__size_t)d
#define __NR64AM_fchmodat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NR64AM_faccessat(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NR64AM_pselect6(a, b, c, d, e, f)                 (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespecx64 const *)e, (struct __sigset_with_sizex64 const *)f
#define __NR64AM_ppoll(a, b, c, d, e, f)                    (struct pollfd *)a, (__size_t)b, (struct __timespecx64 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NR64AM_unshare(a, b, c, d, e, f)                  (__syscall_ulong_t)a
#define __NR64AM_set_robust_list(a, b, c, d, e, f)          (int)a
#define __NR64AM_get_robust_list(a, b, c, d, e, f)          (int)a
#define __NR64AM_splice(a, b, c, d, e, f)                   (__fd_t)a, (__uint64_t *)b, (__fd_t)c, (__uint64_t *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR64AM_tee(a, b, c, d, e, f)                      (__fd_t)a, (__fd_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR64AM_sync_file_range(a, b, c, d, e, f)          (__fd_t)a, (__uint64_t)b, (__uint64_t)c, (__syscall_ulong_t)d
#define __NR64AM_vmsplice(a, b, c, d, e, f)                 (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR64AM_move_pages(a, b, c, d, e, f)               (int)a
#define __NR64AM_utimensat(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (struct __timespecx64 const *)c, (__atflag_t)d
#define __NR64AM_epoll_pwait(a, b, c, d, e, f)              (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d, (struct __sigset_struct const *)e, (__size_t)f
#define __NR64AM_signalfd(a, b, c, d, e, f)                 (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c
#define __NR64AM_timerfd_create(a, b, c, d, e, f)           (__clockid_t)a, (__syscall_ulong_t)b
#define __NR64AM_eventfd(a, b, c, d, e, f)                  (__syscall_ulong_t)a
#define __NR64AM_fallocate(a, b, c, d, e, f)                (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AM_timerfd_settime(a, b, c, d, e, f)          (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspecx64 const *)c, (struct __itimerspecx64 *)d
#define __NR64AM_timerfd_gettime(a, b, c, d, e, f)          (__fd_t)a, (struct __itimerspecx64 *)b
#define __NR64AM_accept4(a, b, c, d, e, f)                  (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c, (__syscall_ulong_t)d
#define __NR64AM_signalfd4(a, b, c, d, e, f)                (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR64AM_eventfd2(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AM_epoll_create1(a, b, c, d, e, f)            (__syscall_ulong_t)a
#define __NR64AM_dup3(a, b, c, d, e, f)                     (__fd_t)a, (__fd_t)b, (__oflag_t)c
#define __NR64AM_pipe2(a, b, c, d, e, f)                    (__fd_t *)a, (__oflag_t)b
#define __NR64AM_inotify_init1(a, b, c, d, e, f)            (int)a
#define __NR64AM_preadv(a, b, c, d, e, f)                   (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c, (__uint64_t)d
#define __NR64AM_pwritev(a, b, c, d, e, f)                  (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c, (__uint64_t)d
#define __NR64AM_rt_tgsigqueueinfo(a, b, c, d, e, f)        (__pid_t)a, (__pid_t)b, (__signo_t)c, (struct __siginfox64_struct const *)d
#define __NR64AM_perf_event_open(a, b, c, d, e, f)          (int)a
#define __NR64AM_recvmmsg(a, b, c, d, e, f)                 (__fd_t)a, (struct __mmsghdrx64 *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespecx64 const *)e
#define __NR64AM_fanotify_init(a, b, c, d, e, f)            (int)a
#define __NR64AM_fanotify_mark(a, b, c, d, e, f)            (int)a
#define __NR64AM_prlimit64(a, b, c, d, e, f)                (__pid_t)a, (__syscall_ulong_t)b, (struct __rlimitx64 const *)c, (struct __rlimitx64 *)d
#define __NR64AM_name_to_handle_at(a, b, c, d, e, f)        (__fd_t)a, (char const *)b, (struct file_handle *)c, (__int32_t *)d, (__atflag_t)e
#define __NR64AM_open_by_handle_at(a, b, c, d, e, f)        (__fd_t)a, (struct file_handle const *)b, (__oflag_t)c
#define __NR64AM_clock_adjtime(a, b, c, d, e, f)            (int)a
#define __NR64AM_syncfs(a, b, c, d, e, f)                   (__fd_t)a
#define __NR64AM_sendmmsg(a, b, c, d, e, f)                 (__fd_t)a, (struct __mmsghdrx64 *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR64AM_setns(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b
#define __NR64AM_getcpu(a, b, c, d, e, f)                   (__uint32_t *)a, (__uint32_t *)b, (struct getcpu_cache *)c
#define __NR64AM_process_vm_readv(a, b, c, d, e, f)         (__pid_t)a, (struct __iovecx64 const *)b, (__size_t)c, (struct __iovecx64 const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR64AM_process_vm_writev(a, b, c, d, e, f)        (__pid_t)a, (struct __iovecx64 const *)b, (__size_t)c, (struct __iovecx64 const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR64AM_kcmp(a, b, c, d, e, f)                     (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AM_finit_module(a, b, c, d, e, f)             (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NR64AM_sched_setattr(a, b, c, d, e, f)            (int)a
#define __NR64AM_sched_getattr(a, b, c, d, e, f)            (int)a
#define __NR64AM_renameat2(a, b, c, d, e, f)                (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NR64AM_seccomp(a, b, c, d, e, f)                  (int)a
#define __NR64AM_getrandom(a, b, c, d, e, f)                (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR64AM_memfd_create(a, b, c, d, e, f)             (char const *)a, (__syscall_ulong_t)b
#define __NR64AM_kexec_file_load(a, b, c, d, e, f)          (int)a
#define __NR64AM_bpf(a, b, c, d, e, f)                      (int)a
#define __NR64AM_execveat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__HYBRID_PTR64(char const) const *)c, (__HYBRID_PTR64(char const) const *)d, (__atflag_t)e
#define __NR64AM_userfaultfd(a, b, c, d, e, f)              (__syscall_ulong_t)a
#define __NR64AM_membarrier(a, b, c, d, e, f)               (int)a
#define __NR64AM_mlock2(a, b, c, d, e, f)                   (void const *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR64AM_copy_file_range(a, b, c, d, e, f)          (int)a
#define __NR64AM_preadv2(a, b, c, d, e, f)                  (int)a
#define __NR64AM_pwritev2(a, b, c, d, e, f)                 (int)a
#define __NR64AM_pkey_mprotect(a, b, c, d, e, f)            (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AM_pkey_alloc(a, b, c, d, e, f)               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AM_pkey_free(a, b, c, d, e, f)                (__syscall_ulong_t)a
#define __NR64AM_statx(a, b, c, d, e, f)                    (int)a
#define __NR64AM_io_pgetevents(a, b, c, d, e, f)            (int)a
#define __NR64AM_rseq(a, b, c, d, e, f)                     (int)a
#define __NR64AM_pidfd_send_signal(a, b, c, d, e, f)        (__fd_t)a, (__signo_t)b, (struct __siginfox64_struct const *)c, (__syscall_ulong_t)d
#define __NR64AM_io_uring_setup(a, b, c, d, e, f)           (int)a
#define __NR64AM_io_uring_enter(a, b, c, d, e, f)           (int)a
#define __NR64AM_io_uring_register(a, b, c, d, e, f)        (int)a
#define __NR64AM_open_tree(a, b, c, d, e, f)                (int)a
#define __NR64AM_move_mount(a, b, c, d, e, f)               (int)a
#define __NR64AM_fsopen(a, b, c, d, e, f)                   (int)a
#define __NR64AM_fsconfig(a, b, c, d, e, f)                 (int)a
#define __NR64AM_fsmount(a, b, c, d, e, f)                  (int)a
#define __NR64AM_fspick(a, b, c, d, e, f)                   (int)a
#define __NR64AM_pidfd_open(a, b, c, d, e, f)               (__pid_t)a, (__syscall_ulong_t)b
#define __NR64AM_clone3(a, b, c, d, e, f)                   (struct clone_args *)a, (__size_t)b
#define __NR64AM_close_range(a, b, c, d, e, f)              (unsigned int)a, (unsigned int)b, (unsigned int)c
#define __NR64AM_openat2(a, b, c, d, e, f)                  (int)a
#define __NR64AM_pidfd_getfd(a, b, c, d, e, f)              (__fd_t)a, (__fd_t)b, (__syscall_ulong_t)c
#define __NR64AM_faccessat2(a, b, c, d, e, f)               (__fd_t)a, (char const *)b, (__syscall_ulong_t)c, (__atflag_t)d
#define __NR64AM_pwritevf(a, b, c, d, e, f)                 (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c, (__uint64_t)d, (__iomode_t)e
#define __NR64AM_preadvf(a, b, c, d, e, f)                  (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c, (__uint64_t)d, (__iomode_t)e
#define __NR64AM_freadlinkat(a, b, c, d, e, f)              (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NR64AM_fsymlinkat(a, b, c, d, e, f)               (char const *)a, (__fd_t)b, (char const *)c, (__atflag_t)d
#define __NR64AM_kfstatat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (struct __kos_stat *)c, (__atflag_t)d
#define __NR64AM_fmknodat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d, (__atflag_t)e
#define __NR64AM_fmkdirat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NR64AM_ksysctl(a, b, c, d, e, f)                  (__ioctl_t)a, (void *)b
#define __NR64AM_maplibrary(a, b, c, d, e, f)               (void *)a, (__syscall_ulong_t)b, (__fd_t)c, (struct elf64_phdr const *)d, (__size_t)e
#define __NR64AM_fsmode(a, b, c, d, e, f)                   (__uint64_t)a
#define __NR64AM_fchdirat(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NR64AM_kreaddirf(a, b, c, d, e, f)                (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d, (__iomode_t)e
#define __NR64AM_kreaddir(a, b, c, d, e, f)                 (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR64AM_set_exception_handler(a, b, c, d, e, f)    (__syscall_ulong_t)a, (__except_handler_t)b, (void *)c
#define __NR64AM_get_exception_handler(a, b, c, d, e, f)    (__ULONG64_TYPE__ *)a, (__except_handler64_t *)b, (__HYBRID_PTR64(void) *)c
#define __NR64AM_rpc_serve_sysret(a, b, c, d, e, f)         /* nothing */
#define __NR64AM_set_userprocmask_address(a, b, c, d, e, f) (struct userprocmask *)a
#define __NR64AM_rtm_test(a, b, c, d, e, f)                 /* nothing */
#define __NR64AM_rtm_abort(a, b, c, d, e, f)                (__syscall_ulong_t)a
#define __NR64AM_rtm_end(a, b, c, d, e, f)                  /* nothing */
#define __NR64AM_rtm_begin(a, b, c, d, e, f)                /* nothing */
#define __NR64AM_userviofd(a, b, c, d, e, f)                (__size_t)a, (__syscall_ulong_t)b
#define __NR64AM_coredump(a, b, c, d, e, f)                 (struct ucpustate64 const *)a, (struct ucpustate64 const *)b, (__HYBRID_PTR64(void const) const *)c, (__size_t)d, (union coredump_info64 const *)e, (__syscall_ulong_t)f
#define __NR64AM_mktty(a, b, c, d, e, f)                    (char const *)a, (__fd_t)b, (__fd_t)c, (__syscall_ulong_t)d
#define __NR64AM_lfutexexpr(a, b, c, d, e, f)               (__uint64_t *)a, (void *)b, (struct lfutexexprx64 const *)c, (struct __timespecx64 const *)d, (__syscall_ulong_t)e
#define __NR64AM_lfutex(a, b, c, d, e, f)                   (__uint64_t *)a, (__syscall_ulong_t)b, (__uint64_t)c, (struct __timespecx64 const *)d, (__uint64_t)e
#define __NR64AM_rpc_serve(a, b, c, d, e, f)                /* nothing */
#define __NR64AM_debugtrap(a, b, c, d, e, f)                (struct ucpustate64 const *)a, (struct debugtrap_reason64 const *)b
#define __NR64AM_writevf(a, b, c, d, e, f)                  (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c, (__iomode_t)d
#define __NR64AM_readvf(a, b, c, d, e, f)                   (__fd_t)a, (struct __iovecx64 const *)b, (__size_t)c, (__iomode_t)d
#define __NR64AM_pwrite64f(a, b, c, d, e, f)                (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)d, (__iomode_t)e
#define __NR64AM_pread64f(a, b, c, d, e, f)                 (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)d, (__iomode_t)e
#define __NR64AM_ioctlf(a, b, c, d, e, f)                   (__fd_t)a, (__ioctl_t)b, (__iomode_t)c, (void *)d
#define __NR64AM_ksigreturn(a, b, c, d, e, f)               /* nothing */
#define __NR64AM_openpty(a, b, c, d, e, f)                  (__fd_t *)a, (__fd_t *)b, (char *)c, (struct termios const *)d, (struct winsize const *)e
#define __NR64AM_rpc_schedule(a, b, c, d, e, f)             (__pid_t)a, (__syscall_ulong_t)b, (void const *)c, (__HYBRID_PTR64(void const) const *)d, (__size_t)e
#define __NR64AM_frealpathat(a, b, c, d, e, f)              (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NR64AM_frealpath4(a, b, c, d, e, f)               (__fd_t)a, (char *)b, (__size_t)c, (__atflag_t)d
#define __NR64AM_getdrives(a, b, c, d, e, f)                /* nothing */
#define __NR64AM_detach(a, b, c, d, e, f)                   (__pid_t)a
#define __NR64AM_readf(a, b, c, d, e, f)                    (__fd_t)a, (void *)b, (__size_t)c, (__iomode_t)d
#define __NR64AM_klstat(a, b, c, d, e, f)                   (char const *)a, (struct __kos_stat *)b
#define __NR64AM_kfstat(a, b, c, d, e, f)                   (__fd_t)a, (struct __kos_stat *)b
#define __NR64AM_kstat(a, b, c, d, e, f)                    (char const *)a, (struct __kos_stat *)b
#define __NR64AM_writef(a, b, c, d, e, f)                   (__fd_t)a, (void const *)b, (__size_t)c, (__iomode_t)d
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_MAKER */


/************************************************************************/
/* SYSCALL ARGUMENT LIST PACKING                                        */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NR64AP_read(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_write(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_open(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_close(a)                                   (__syscall_ulong_t)a
#define __NR64AP_stat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_fstat(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_lstat(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_poll(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_lseek(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_mmap(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_mprotect(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_munmap(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_brk(a)                                     (__syscall_ulong_t)a
#define __NR64AP_rt_sigaction(a, b, c, d)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_rt_sigprocmask(a, b, c, d)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_rt_sigreturn()                             /* nothing */
#define __NR64AP_ioctl(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_pread64(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_pwrite64(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_readv(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_writev(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_access(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_pipe(a)                                    (__syscall_ulong_t)a
#define __NR64AP_select(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_sched_yield()                              /* nothing */
#define __NR64AP_mremap(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_msync(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_mincore(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_madvise(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_shmget(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_shmat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_shmctl(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_dup(a)                                     (__syscall_ulong_t)a
#define __NR64AP_dup2(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_pause()                                    /* nothing */
#define __NR64AP_nanosleep(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getitimer(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_alarm(a)                                   (__syscall_ulong_t)a
#define __NR64AP_setitimer(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_getpid()                                   /* nothing */
#define __NR64AP_sendfile(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_socket(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_connect(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_accept(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_sendto(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_recvfrom(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_sendmsg(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_recvmsg(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_shutdown(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_bind(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_listen(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getsockname(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_getpeername(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_socketpair(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_setsockopt(a, b, c, d, e)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_getsockopt(a, b, c, d, e)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_clone(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_fork()                                     /* nothing */
#define __NR64AP_vfork()                                    /* nothing */
#define __NR64AP_execve(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_exit(a)                                    (__syscall_ulong_t)a
#define __NR64AP_wait4(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_kill(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_uname(a)                                   (__syscall_ulong_t)a
#define __NR64AP_semget(a)                                  (__syscall_ulong_t)a
#define __NR64AP_semop(a)                                   (__syscall_ulong_t)a
#define __NR64AP_semctl(a)                                  (__syscall_ulong_t)a
#define __NR64AP_shmdt(a)                                   (__syscall_ulong_t)a
#define __NR64AP_msgget(a)                                  (__syscall_ulong_t)a
#define __NR64AP_msgsnd(a)                                  (__syscall_ulong_t)a
#define __NR64AP_msgrcv(a)                                  (__syscall_ulong_t)a
#define __NR64AP_msgctl(a)                                  (__syscall_ulong_t)a
#define __NR64AP_fcntl(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_flock(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_fsync(a)                                   (__syscall_ulong_t)a
#define __NR64AP_fdatasync(a)                               (__syscall_ulong_t)a
#define __NR64AP_truncate(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_ftruncate(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getdents(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_getcwd(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_chdir(a)                                   (__syscall_ulong_t)a
#define __NR64AP_fchdir(a)                                  (__syscall_ulong_t)a
#define __NR64AP_rename(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_mkdir(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_rmdir(a)                                   (__syscall_ulong_t)a
#define __NR64AP_creat(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_link(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_unlink(a)                                  (__syscall_ulong_t)a
#define __NR64AP_symlink(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_readlink(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_chmod(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_fchmod(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_chown(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_fchown(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_lchown(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_umask(a)                                   (__syscall_ulong_t)a
#define __NR64AP_gettimeofday(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getrlimit(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getrusage(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_sysinfo(a)                                 (__syscall_ulong_t)a
#define __NR64AP_times(a)                                   (__syscall_ulong_t)a
#define __NR64AP_ptrace(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_getuid()                                   /* nothing */
#define __NR64AP_syslog(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_getgid()                                   /* nothing */
#define __NR64AP_setuid(a)                                  (__syscall_ulong_t)a
#define __NR64AP_setgid(a)                                  (__syscall_ulong_t)a
#define __NR64AP_geteuid()                                  /* nothing */
#define __NR64AP_getegid()                                  /* nothing */
#define __NR64AP_setpgid(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getppid()                                  /* nothing */
#define __NR64AP_getpgrp()                                  /* nothing */
#define __NR64AP_setsid()                                   /* nothing */
#define __NR64AP_setreuid(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_setregid(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getgroups(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_setgroups(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_setresuid(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_getresuid(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_setresgid(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_getresgid(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_getpgid(a)                                 (__syscall_ulong_t)a
#define __NR64AP_setfsuid(a)                                (__syscall_ulong_t)a
#define __NR64AP_setfsgid(a)                                (__syscall_ulong_t)a
#define __NR64AP_getsid(a)                                  (__syscall_ulong_t)a
#define __NR64AP_capget(a)                                  (__syscall_ulong_t)a
#define __NR64AP_capset(a)                                  (__syscall_ulong_t)a
#define __NR64AP_rt_sigpending(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_rt_sigtimedwait(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_rt_sigqueueinfo(a, b, c)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_rt_sigsuspend(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_sigaltstack(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_utime(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_mknod(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_uselib(a)                                  (__syscall_ulong_t)a
#define __NR64AP_personality(a)                             (__syscall_ulong_t)a
#define __NR64AP_ustat(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_statfs(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_fstatfs(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_sysfs(a)                                   (__syscall_ulong_t)a
#define __NR64AP_getpriority(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_setpriority(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_sched_setparam(a, b)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_sched_getparam(a, b)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_sched_setscheduler(a, b, c)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_sched_getscheduler(a)                      (__syscall_ulong_t)a
#define __NR64AP_sched_get_priority_max(a)                  (__syscall_ulong_t)a
#define __NR64AP_sched_get_priority_min(a)                  (__syscall_ulong_t)a
#define __NR64AP_sched_rr_get_interval(a, b)                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_mlock(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_munlock(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_mlockall(a)                                (__syscall_ulong_t)a
#define __NR64AP_munlockall()                               /* nothing */
#define __NR64AP_vhangup()                                  /* nothing */
#define __NR64AP_modify_ldt(a, b, c)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_pivot_root(a)                              (__syscall_ulong_t)a
#define __NR64AP__sysctl(a)                                 (__syscall_ulong_t)a
#define __NR64AP_prctl(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_arch_prctl(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_adjtimex(a)                                (__syscall_ulong_t)a
#define __NR64AP_setrlimit(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_chroot(a)                                  (__syscall_ulong_t)a
#define __NR64AP_sync()                                     /* nothing */
#define __NR64AP_acct(a)                                    (__syscall_ulong_t)a
#define __NR64AP_settimeofday(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_mount(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_umount2(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_swapon(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_swapoff(a)                                 (__syscall_ulong_t)a
#define __NR64AP_reboot(a)                                  (__syscall_ulong_t)a
#define __NR64AP_sethostname(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_setdomainname(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_iopl(a)                                    (__syscall_ulong_t)a
#define __NR64AP_ioperm(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_create_module()                            /* nothing */
#define __NR64AP_init_module(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_delete_module(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_get_kernel_syms()                          /* nothing */
#define __NR64AP_query_module()                             /* nothing */
#define __NR64AP_quotactl(a)                                (__syscall_ulong_t)a
#define __NR64AP_nfsservctl(a)                              (__syscall_ulong_t)a
#define __NR64AP_getpmsg()                                  /* nothing */
#define __NR64AP_putpmsg()                                  /* nothing */
#define __NR64AP_afs_syscall()                              /* nothing */
#define __NR64AP_tuxcall()                                  /* nothing */
#define __NR64AP_security()                                 /* nothing */
#define __NR64AP_gettid()                                   /* nothing */
#define __NR64AP_readahead(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_setxattr(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_lsetxattr(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_fsetxattr(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_getxattr(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_lgetxattr(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_fgetxattr(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_listxattr(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_llistxattr(a, b, c)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_flistxattr(a, b, c)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_removexattr(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_lremovexattr(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_fremovexattr(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_tkill(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_time(a)                                    (__syscall_ulong_t)a
#define __NR64AP_futex(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_sched_setaffinity(a, b, c)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_sched_getaffinity(a, b, c)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_set_thread_area(a)                         (__syscall_ulong_t)a
#define __NR64AP_io_setup(a)                                (__syscall_ulong_t)a
#define __NR64AP_io_destroy(a)                              (__syscall_ulong_t)a
#define __NR64AP_io_getevents(a)                            (__syscall_ulong_t)a
#define __NR64AP_io_submit(a)                               (__syscall_ulong_t)a
#define __NR64AP_io_cancel(a)                               (__syscall_ulong_t)a
#define __NR64AP_get_thread_area(a)                         (__syscall_ulong_t)a
#define __NR64AP_lookup_dcookie(a)                          (__syscall_ulong_t)a
#define __NR64AP_epoll_create(a)                            (__syscall_ulong_t)a
#define __NR64AP_epoll_ctl_old(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_epoll_wait_old(a, b, c, d)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_remap_file_pages(a, b, c, d, e)            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_getdents64(a, b, c)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_set_tid_address(a)                         (__syscall_ulong_t)a
#define __NR64AP_restart_syscall()                          /* nothing */
#define __NR64AP_semtimedop(a)                              (__syscall_ulong_t)a
#define __NR64AP_fadvise64(a)                               (__syscall_ulong_t)a
#define __NR64AP_timer_create(a, b, c)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_timer_settime(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_timer_gettime(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_timer_getoverrun(a)                        (__syscall_ulong_t)a
#define __NR64AP_timer_delete(a)                            (__syscall_ulong_t)a
#define __NR64AP_clock_settime(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_clock_gettime(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_clock_getres(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_clock_nanosleep(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_exit_group(a)                              (__syscall_ulong_t)a
#define __NR64AP_epoll_wait(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_epoll_ctl(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_tgkill(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_utimes(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_vserver()                                  /* nothing */
#define __NR64AP_mbind(a)                                   (__syscall_ulong_t)a
#define __NR64AP_set_mempolicy(a)                           (__syscall_ulong_t)a
#define __NR64AP_get_mempolicy(a)                           (__syscall_ulong_t)a
#define __NR64AP_mq_open(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_mq_unlink(a)                               (__syscall_ulong_t)a
#define __NR64AP_mq_timedsend(a, b, c, d, e)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_mq_timedreceive(a, b, c, d, e)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_mq_notify(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_mq_getsetattr(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_kexec_load(a)                              (__syscall_ulong_t)a
#define __NR64AP_waitid(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_add_key(a)                                 (__syscall_ulong_t)a
#define __NR64AP_request_key(a)                             (__syscall_ulong_t)a
#define __NR64AP_keyctl(a)                                  (__syscall_ulong_t)a
#define __NR64AP_ioprio_set(a, b, c)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_ioprio_get(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_inotify_init(a)                            (__syscall_ulong_t)a
#define __NR64AP_inotify_add_watch(a)                       (__syscall_ulong_t)a
#define __NR64AP_inotify_rm_watch(a)                        (__syscall_ulong_t)a
#define __NR64AP_migrate_pages(a)                           (__syscall_ulong_t)a
#define __NR64AP_openat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_mkdirat(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_mknodat(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_fchownat(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_futimesat(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_newfstatat(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_unlinkat(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_renameat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_linkat(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_symlinkat(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_readlinkat(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_fchmodat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_faccessat(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_pselect6(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_ppoll(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_unshare(a)                                 (__syscall_ulong_t)a
#define __NR64AP_set_robust_list(a)                         (__syscall_ulong_t)a
#define __NR64AP_get_robust_list(a)                         (__syscall_ulong_t)a
#define __NR64AP_splice(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_tee(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_sync_file_range(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_vmsplice(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_move_pages(a)                              (__syscall_ulong_t)a
#define __NR64AP_utimensat(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_epoll_pwait(a, b, c, d, e, f)              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_signalfd(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_timerfd_create(a, b)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_eventfd(a)                                 (__syscall_ulong_t)a
#define __NR64AP_fallocate(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_timerfd_settime(a, b, c, d)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_timerfd_gettime(a, b)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_accept4(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_signalfd4(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_eventfd2(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_epoll_create1(a)                           (__syscall_ulong_t)a
#define __NR64AP_dup3(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_pipe2(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_inotify_init1(a)                           (__syscall_ulong_t)a
#define __NR64AP_preadv(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_pwritev(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_rt_tgsigqueueinfo(a, b, c, d)              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_perf_event_open(a)                         (__syscall_ulong_t)a
#define __NR64AP_recvmmsg(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_fanotify_init(a)                           (__syscall_ulong_t)a
#define __NR64AP_fanotify_mark(a)                           (__syscall_ulong_t)a
#define __NR64AP_prlimit64(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_name_to_handle_at(a, b, c, d, e)           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_open_by_handle_at(a, b, c)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_clock_adjtime(a)                           (__syscall_ulong_t)a
#define __NR64AP_syncfs(a)                                  (__syscall_ulong_t)a
#define __NR64AP_sendmmsg(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_setns(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_getcpu(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_process_vm_readv(a, b, c, d, e, f)         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_process_vm_writev(a, b, c, d, e, f)        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_kcmp(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_finit_module(a, b, c)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_sched_setattr(a)                           (__syscall_ulong_t)a
#define __NR64AP_sched_getattr(a)                           (__syscall_ulong_t)a
#define __NR64AP_renameat2(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_seccomp(a)                                 (__syscall_ulong_t)a
#define __NR64AP_getrandom(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_memfd_create(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_kexec_file_load(a)                         (__syscall_ulong_t)a
#define __NR64AP_bpf(a)                                     (__syscall_ulong_t)a
#define __NR64AP_execveat(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_userfaultfd(a)                             (__syscall_ulong_t)a
#define __NR64AP_membarrier(a)                              (__syscall_ulong_t)a
#define __NR64AP_mlock2(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_copy_file_range(a)                         (__syscall_ulong_t)a
#define __NR64AP_preadv2(a)                                 (__syscall_ulong_t)a
#define __NR64AP_pwritev2(a)                                (__syscall_ulong_t)a
#define __NR64AP_pkey_mprotect(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_pkey_alloc(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_pkey_free(a)                               (__syscall_ulong_t)a
#define __NR64AP_statx(a)                                   (__syscall_ulong_t)a
#define __NR64AP_io_pgetevents(a)                           (__syscall_ulong_t)a
#define __NR64AP_rseq(a)                                    (__syscall_ulong_t)a
#define __NR64AP_pidfd_send_signal(a, b, c, d)              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_io_uring_setup(a)                          (__syscall_ulong_t)a
#define __NR64AP_io_uring_enter(a)                          (__syscall_ulong_t)a
#define __NR64AP_io_uring_register(a)                       (__syscall_ulong_t)a
#define __NR64AP_open_tree(a)                               (__syscall_ulong_t)a
#define __NR64AP_move_mount(a)                              (__syscall_ulong_t)a
#define __NR64AP_fsopen(a)                                  (__syscall_ulong_t)a
#define __NR64AP_fsconfig(a)                                (__syscall_ulong_t)a
#define __NR64AP_fsmount(a)                                 (__syscall_ulong_t)a
#define __NR64AP_fspick(a)                                  (__syscall_ulong_t)a
#define __NR64AP_pidfd_open(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_clone3(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_close_range(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_openat2(a)                                 (__syscall_ulong_t)a
#define __NR64AP_pidfd_getfd(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_faccessat2(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_pwritevf(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_preadvf(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_freadlinkat(a, b, c, d, e)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_fsymlinkat(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_kfstatat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_fmknodat(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_fmkdirat(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_ksysctl(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_maplibrary(a, b, c, d, e)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_fsmode(a)                                  (__syscall_ulong_t)a
#define __NR64AP_fchdirat(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_kreaddirf(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_kreaddir(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_set_exception_handler(a, b, c)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_get_exception_handler(a, b, c)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR64AP_rpc_serve_sysret()                         /* nothing */
#define __NR64AP_set_userprocmask_address(a)                (__syscall_ulong_t)a
#define __NR64AP_rtm_test()                                 /* nothing */
#define __NR64AP_rtm_abort(a)                               (__syscall_ulong_t)a
#define __NR64AP_rtm_end()                                  /* nothing */
#define __NR64AP_rtm_begin()                                /* nothing */
#define __NR64AP_userviofd(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_coredump(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR64AP_mktty(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_lfutexexpr(a, b, c, d, e)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_lfutex(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_rpc_serve()                                /* nothing */
#define __NR64AP_debugtrap(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_writevf(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_readvf(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_pwrite64f(a, b, c, d, e)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_pread64f(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_ioctlf(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_ksigreturn()                               /* nothing */
#define __NR64AP_openpty(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_rpc_schedule(a, b, c, d, e)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_frealpathat(a, b, c, d, e)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR64AP_frealpath4(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_getdrives()                                /* nothing */
#define __NR64AP_detach(a)                                  (__syscall_ulong_t)a
#define __NR64AP_readf(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR64AP_klstat(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_kfstat(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_kstat(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR64AP_writef(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_PACKER */

