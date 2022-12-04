/* HASH CRC-32:0x8a251a7a */
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
#define __NRAC_restart_syscall              0
#define __NRAC_exit                         1
#define __NRAC_fork                         0
#define __NRAC_read                         3
#define __NRAC_write                        3
#define __NRAC_open                         3
#define __NRAC_close                        1
#define __NRAC_waitpid                      3
#define __NRAC_creat                        2
#define __NRAC_link                         2
#define __NRAC_unlink                       1
#define __NRAC_execve                       3
#define __NRAC_chdir                        1
#define __NRAC_time                         1
#define __NRAC_mknod                        3
#define __NRAC_chmod                        2
#define __NRAC_lchown                       3
#define __NRAC_break                        0
#define __NRAC_oldstat                      2
#define __NRAC_lseek                        3
#define __NRAC_getpid                       0
#define __NRAC_mount                        5
#define __NRAC_umount                       1
#define __NRAC_setuid                       1
#define __NRAC_getuid                       0
#define __NRAC_stime                        1
#define __NRAC_ptrace                       4
#define __NRAC_alarm                        1
#define __NRAC_oldfstat                     2
#define __NRAC_pause                        0
#define __NRAC_utime                        2
#define __NRAC_stty                         0
#define __NRAC_gtty                         0
#define __NRAC_access                       2
#define __NRAC_nice                         1
#define __NRAC_ftime                        1
#define __NRAC_sync                         0
#define __NRAC_kill                         2
#define __NRAC_rename                       2
#define __NRAC_mkdir                        2
#define __NRAC_rmdir                        1
#define __NRAC_dup                          1
#define __NRAC_pipe                         1
#define __NRAC_times                        1
#define __NRAC_prof                         0
#define __NRAC_brk                          1
#define __NRAC_setgid                       1
#define __NRAC_getgid                       0
#define __NRAC_signal                       2
#define __NRAC_geteuid                      0
#define __NRAC_getegid                      0
#define __NRAC_acct                         1
#define __NRAC_umount2                      2
#define __NRAC_lock                         0
#define __NRAC_ioctl                        3
#define __NRAC_fcntl                        3
#define __NRAC_mpx                          0
#define __NRAC_setpgid                      2
#define __NRAC_ulimit                       0
#define __NRAC_oldolduname                  1
#define __NRAC_umask                        1
#define __NRAC_chroot                       1
#define __NRAC_ustat                        2
#define __NRAC_dup2                         2
#define __NRAC_getppid                      0
#define __NRAC_getpgrp                      0
#define __NRAC_setsid                       0
#define __NRAC_sigaction                    3
#define __NRAC_sgetmask                     0
#define __NRAC_ssetmask                     1
#define __NRAC_setreuid                     2
#define __NRAC_setregid                     2
#define __NRAC_sigsuspend                   1
#define __NRAC_sigpending                   1
#define __NRAC_sethostname                  2
#define __NRAC_setrlimit                    2
#define __NRAC_getrlimit                    2
#define __NRAC_getrusage                    2
#define __NRAC_gettimeofday                 2
#define __NRAC_settimeofday                 2
#define __NRAC_getgroups                    2
#define __NRAC_setgroups                    2
#define __NRAC_select                       1
#define __NRAC_symlink                      2
#define __NRAC_oldlstat                     2
#define __NRAC_readlink                     3
#define __NRAC_uselib                       1
#define __NRAC_swapon                       2
#define __NRAC_reboot                       1
#define __NRAC_readdir                      2
#define __NRAC_mmap                         6
#define __NRAC_munmap                       2
#define __NRAC_truncate                     2
#define __NRAC_ftruncate                    2
#define __NRAC_fchmod                       2
#define __NRAC_fchown                       3
#define __NRAC_getpriority                  2
#define __NRAC_setpriority                  3
#define __NRAC_profil                       0
#define __NRAC_statfs                       2
#define __NRAC_fstatfs                      2
#define __NRAC_ioperm                       3
#define __NRAC_socketcall                   2
#define __NRAC_syslog                       3
#define __NRAC_setitimer                    3
#define __NRAC_getitimer                    2
#define __NRAC_stat                         2
#define __NRAC_lstat                        2
#define __NRAC_fstat                        2
#define __NRAC_olduname                     1
#define __NRAC_iopl                         1
#define __NRAC_vhangup                      0
#define __NRAC_idle                         0
#define __NRAC_vm86old                      1
#define __NRAC_wait4                        4
#define __NRAC_swapoff                      1
#define __NRAC_sysinfo                      1
#define __NRAC_ipc                          1
#define __NRAC_fsync                        1
#define __NRAC_sigreturn                    0
#define __NRAC_clone                        5
#define __NRAC_setdomainname                2
#define __NRAC_uname                        1
#define __NRAC_modify_ldt                   3
#define __NRAC_adjtimex                     1
#define __NRAC_mprotect                     3
#define __NRAC_sigprocmask                  3
#define __NRAC_create_module                0
#define __NRAC_init_module                  3
#define __NRAC_delete_module                2
#define __NRAC_get_kernel_syms              0
#define __NRAC_quotactl                     1
#define __NRAC_getpgid                      1
#define __NRAC_fchdir                       1
#define __NRAC_bdflush                      1
#define __NRAC_sysfs                        1
#define __NRAC_personality                  1
#define __NRAC_afs_syscall                  0
#define __NRAC_setfsuid                     1
#define __NRAC_setfsgid                     1
#define __NRAC__llseek                      4
#define __NRAC_getdents                     3
#define __NRAC__newselect                   5
#define __NRAC_flock                        2
#define __NRAC_msync                        3
#define __NRAC_readv                        3
#define __NRAC_writev                       3
#define __NRAC_getsid                       1
#define __NRAC_fdatasync                    1
#define __NRAC__sysctl                      1
#define __NRAC_mlock                        2
#define __NRAC_munlock                      2
#define __NRAC_mlockall                     1
#define __NRAC_munlockall                   0
#define __NRAC_sched_setparam               2
#define __NRAC_sched_getparam               2
#define __NRAC_sched_setscheduler           3
#define __NRAC_sched_getscheduler           1
#define __NRAC_sched_yield                  0
#define __NRAC_sched_get_priority_max       1
#define __NRAC_sched_get_priority_min       1
#define __NRAC_sched_rr_get_interval        2
#define __NRAC_nanosleep                    2
#define __NRAC_mremap                       5
#define __NRAC_setresuid                    3
#define __NRAC_getresuid                    3
#define __NRAC_vm86                         1
#define __NRAC_query_module                 0
#define __NRAC_poll                         3
#define __NRAC_nfsservctl                   1
#define __NRAC_setresgid                    3
#define __NRAC_getresgid                    3
#define __NRAC_prctl                        5
#define __NRAC_rt_sigreturn                 0
#define __NRAC_rt_sigaction                 4
#define __NRAC_rt_sigprocmask               4
#define __NRAC_rt_sigpending                2
#define __NRAC_rt_sigtimedwait              4
#define __NRAC_rt_sigqueueinfo              3
#define __NRAC_rt_sigsuspend                2
#define __NRAC_pread64                      4
#define __NRAC_pwrite64                     4
#define __NRAC_chown                        3
#define __NRAC_getcwd                       2
#define __NRAC_capget                       1
#define __NRAC_capset                       1
#define __NRAC_sigaltstack                  2
#define __NRAC_sendfile                     4
#define __NRAC_getpmsg                      0
#define __NRAC_putpmsg                      0
#define __NRAC_vfork                        0
#define __NRAC_ugetrlimit                   1
#define __NRAC_mmap2                        6
#define __NRAC_truncate64                   2
#define __NRAC_ftruncate64                  2
#define __NRAC_stat64                       2
#define __NRAC_lstat64                      2
#define __NRAC_fstat64                      2
#define __NRAC_lchown32                     3
#define __NRAC_getuid32                     0
#define __NRAC_getgid32                     0
#define __NRAC_geteuid32                    0
#define __NRAC_getegid32                    0
#define __NRAC_setreuid32                   2
#define __NRAC_setregid32                   2
#define __NRAC_getgroups32                  2
#define __NRAC_setgroups32                  2
#define __NRAC_fchown32                     3
#define __NRAC_setresuid32                  3
#define __NRAC_getresuid32                  3
#define __NRAC_setresgid32                  3
#define __NRAC_getresgid32                  3
#define __NRAC_chown32                      3
#define __NRAC_setuid32                     1
#define __NRAC_setgid32                     1
#define __NRAC_setfsuid32                   1
#define __NRAC_setfsgid32                   1
#define __NRAC_pivot_root                   1
#define __NRAC_mincore                      3
#define __NRAC_madvise                      3
#define __NRAC_getdents64                   3
#define __NRAC_fcntl64                      3
#define __NRAC_gettid                       0
#define __NRAC_readahead                    3
#define __NRAC_setxattr                     5
#define __NRAC_lsetxattr                    5
#define __NRAC_fsetxattr                    5
#define __NRAC_getxattr                     4
#define __NRAC_lgetxattr                    4
#define __NRAC_fgetxattr                    4
#define __NRAC_listxattr                    3
#define __NRAC_llistxattr                   3
#define __NRAC_flistxattr                   3
#define __NRAC_removexattr                  2
#define __NRAC_lremovexattr                 2
#define __NRAC_fremovexattr                 2
#define __NRAC_tkill                        2
#define __NRAC_sendfile64                   4
#define __NRAC_futex                        6
#define __NRAC_sched_setaffinity            3
#define __NRAC_sched_getaffinity            3
#define __NRAC_set_thread_area              1
#define __NRAC_get_thread_area              1
#define __NRAC_io_setup                     1
#define __NRAC_io_destroy                   1
#define __NRAC_io_getevents                 1
#define __NRAC_io_submit                    1
#define __NRAC_io_cancel                    1
#define __NRAC_fadvise64                    1
#define __NRAC_exit_group                   1
#define __NRAC_lookup_dcookie               1
#define __NRAC_epoll_create                 1
#define __NRAC_epoll_ctl                    4
#define __NRAC_epoll_wait                   4
#define __NRAC_remap_file_pages             5
#define __NRAC_set_tid_address              1
#define __NRAC_timer_create                 3
#define __NRAC_timer_settime                4
#define __NRAC_timer_gettime                2
#define __NRAC_timer_getoverrun             1
#define __NRAC_timer_delete                 1
#define __NRAC_clock_settime                2
#define __NRAC_clock_gettime                2
#define __NRAC_clock_getres                 2
#define __NRAC_clock_nanosleep              4
#define __NRAC_statfs64                     2
#define __NRAC_fstatfs64                    2
#define __NRAC_tgkill                       3
#define __NRAC_utimes                       2
#define __NRAC_fadvise64_64                 1
#define __NRAC_vserver                      0
#define __NRAC_mbind                        1
#define __NRAC_get_mempolicy                1
#define __NRAC_set_mempolicy                1
#define __NRAC_mq_open                      3
#define __NRAC_mq_unlink                    1
#define __NRAC_mq_timedsend                 5
#define __NRAC_mq_timedreceive              5
#define __NRAC_mq_notify                    2
#define __NRAC_mq_getsetattr                3
#define __NRAC_kexec_load                   1
#define __NRAC_waitid                       5
#define __NRAC_add_key                      1
#define __NRAC_request_key                  1
#define __NRAC_keyctl                       1
#define __NRAC_ioprio_set                   3
#define __NRAC_ioprio_get                   2
#define __NRAC_inotify_init                 0
#define __NRAC_inotify_add_watch            3
#define __NRAC_inotify_rm_watch             2
#define __NRAC_migrate_pages                1
#define __NRAC_openat                       4
#define __NRAC_mkdirat                      3
#define __NRAC_mknodat                      4
#define __NRAC_fchownat                     5
#define __NRAC_futimesat                    3
#define __NRAC_fstatat64                    4
#define __NRAC_unlinkat                     3
#define __NRAC_renameat                     4
#define __NRAC_linkat                       5
#define __NRAC_symlinkat                    3
#define __NRAC_readlinkat                   4
#define __NRAC_fchmodat                     4
#define __NRAC_faccessat                    3
#define __NRAC_pselect6                     6
#define __NRAC_ppoll                        5
#define __NRAC_unshare                      1
#define __NRAC_set_robust_list              1
#define __NRAC_get_robust_list              1
#define __NRAC_splice                       6
#define __NRAC_sync_file_range              4
#define __NRAC_tee                          4
#define __NRAC_vmsplice                     4
#define __NRAC_move_pages                   1
#define __NRAC_getcpu                       3
#define __NRAC_epoll_pwait                  6
#define __NRAC_utimensat                    4
#define __NRAC_signalfd                     3
#define __NRAC_timerfd_create               2
#define __NRAC_eventfd                      1
#define __NRAC_fallocate                    4
#define __NRAC_timerfd_settime              4
#define __NRAC_timerfd_gettime              2
#define __NRAC_signalfd4                    4
#define __NRAC_eventfd2                     2
#define __NRAC_epoll_create1                1
#define __NRAC_dup3                         3
#define __NRAC_pipe2                        2
#define __NRAC_inotify_init1                1
#define __NRAC_preadv                       4
#define __NRAC_pwritev                      4
#define __NRAC_rt_tgsigqueueinfo            4
#define __NRAC_perf_event_open              1
#define __NRAC_recvmmsg                     5
#define __NRAC_fanotify_init                1
#define __NRAC_fanotify_mark                1
#define __NRAC_prlimit64                    4
#define __NRAC_name_to_handle_at            5
#define __NRAC_open_by_handle_at            3
#define __NRAC_clock_adjtime                1
#define __NRAC_syncfs                       1
#define __NRAC_sendmmsg                     4
#define __NRAC_setns                        2
#define __NRAC_process_vm_readv             6
#define __NRAC_process_vm_writev            6
#define __NRAC_kcmp                         5
#define __NRAC_finit_module                 3
#define __NRAC_sched_setattr                1
#define __NRAC_sched_getattr                1
#define __NRAC_renameat2                    5
#define __NRAC_seccomp                      1
#define __NRAC_getrandom                    3
#define __NRAC_memfd_create                 2
#define __NRAC_bpf                          1
#define __NRAC_execveat                     5
#define __NRAC_socket                       3
#define __NRAC_socketpair                   4
#define __NRAC_bind                         3
#define __NRAC_connect                      3
#define __NRAC_listen                       2
#define __NRAC_accept4                      4
#define __NRAC_getsockopt                   5
#define __NRAC_setsockopt                   5
#define __NRAC_getsockname                  3
#define __NRAC_getpeername                  3
#define __NRAC_sendto                       6
#define __NRAC_sendmsg                      3
#define __NRAC_recvfrom                     6
#define __NRAC_recvmsg                      3
#define __NRAC_shutdown                     2
#define __NRAC_userfaultfd                  1
#define __NRAC_membarrier                   1
#define __NRAC_mlock2                       3
#define __NRAC_copy_file_range              1
#define __NRAC_preadv2                      1
#define __NRAC_pwritev2                     1
#define __NRAC_pkey_mprotect                4
#define __NRAC_pkey_alloc                   2
#define __NRAC_pkey_free                    1
#define __NRAC_statx                        1
#define __NRAC_arch_prctl                   2
#define __NRAC_io_pgetevents                1
#define __NRAC_rseq                         1
#define __NRAC_semget                       1
#define __NRAC_semctl                       1
#define __NRAC_shmget                       3
#define __NRAC_shmctl                       3
#define __NRAC_shmat                        3
#define __NRAC_shmdt                        1
#define __NRAC_msgget                       1
#define __NRAC_msgsnd                       1
#define __NRAC_msgrcv                       1
#define __NRAC_msgctl                       1
#define __NRAC_clock_gettime64              2
#define __NRAC_clock_settime64              2
#define __NRAC_clock_adjtime64              1
#define __NRAC_clock_getres_time64          2
#define __NRAC_clock_nanosleep_time64       4
#define __NRAC_timer_gettime64              2
#define __NRAC_timer_settime64              4
#define __NRAC_timerfd_gettime64            2
#define __NRAC_timerfd_settime64            4
#define __NRAC_utimensat_time64             4
#define __NRAC_pselect6_time64              6
#define __NRAC_ppoll_time64                 5
#define __NRAC_io_pgetevents_time64         1
#define __NRAC_recvmmsg_time64              5
#define __NRAC_mq_timedsend_time64          5
#define __NRAC_mq_timedreceive_time64       5
#define __NRAC_semtimedop_time64            1
#define __NRAC_rt_sigtimedwait_time64       4
#define __NRAC_futex_time64                 6
#define __NRAC_sched_rr_get_interval_time64 2
#define __NRAC_pidfd_send_signal            4
#define __NRAC_io_uring_setup               1
#define __NRAC_io_uring_enter               1
#define __NRAC_io_uring_register            1
#define __NRAC_open_tree                    1
#define __NRAC_move_mount                   1
#define __NRAC_fsopen                       1
#define __NRAC_fsconfig                     1
#define __NRAC_fsmount                      1
#define __NRAC_fspick                       1
#define __NRAC_pidfd_open                   2
#define __NRAC_clone3                       2
#define __NRAC_close_range                  3
#define __NRAC_openat2                      1
#define __NRAC_pidfd_getfd                  3
#define __NRAC_faccessat2                   4
#define __NRAC_pwritevf                     5
#define __NRAC_preadvf                      5
#define __NRAC_fallocate64                  4
#define __NRAC_freadlinkat                  5
#define __NRAC_fsymlinkat                   4
#define __NRAC_kfstatat                     4
#define __NRAC_futimesat64                  3
#define __NRAC_fmknodat                     5
#define __NRAC_fmkdirat                     4
#define __NRAC_inotify_add_watch_at         5
#define __NRAC_waitid64                     5
#define __NRAC_utimes64                     2
#define __NRAC_set_userprocmask_address     1
#define __NRAC_lfutexexpr                   5
#define __NRAC_lfutex                       5
#define __NRAC_kreaddirf                    5
#define __NRAC_kreaddir                     4
#define __NRAC_kfstat                       2
#define __NRAC_klstat                       2
#define __NRAC_kstat                        2
#define __NRAC_pwrite64f                    5
#define __NRAC_pread64f                     5
#define __NRAC_ksigreturn                   6
#define __NRAC_nanosleep64                  2
#define __NRAC_rpc_serve_sysret             0
#define __NRAC_rpc_serve                    0
#define __NRAC_ksysctl                      2
#define __NRAC_writevf                      4
#define __NRAC_readvf                       4
#define __NRAC_select64                     5
#define __NRAC_wait4_64                     4
#define __NRAC_getitimer64                  2
#define __NRAC_setitimer64                  3
#define __NRAC_maplibrary                   5
#define __NRAC_settimeofday64               2
#define __NRAC_gettimeofday64               2
#define __NRAC_getrusage64                  2
#define __NRAC_fsmode                       1
#define __NRAC_ioctlf                       4
#define __NRAC_rtm_test                     0
#define __NRAC_rtm_abort                    1
#define __NRAC_rtm_end                      0
#define __NRAC_rtm_begin                    0
#define __NRAC_ftime64                      1
#define __NRAC_utime64                      2
#define __NRAC_stime64                      1
#define __NRAC_userviofd                    2
#define __NRAC_lseek64                      3
#define __NRAC_coredump                     6
#define __NRAC_debugtrap                    2
#define __NRAC_get_exception_handler        3
#define __NRAC_set_exception_handler        3
#define __NRAC_mktty                        4
#define __NRAC_time64                       1
#define __NRAC_fchdirat                     3
#define __NRAC_openpty                      5
#define __NRAC_rpc_schedule                 5
#define __NRAC_frealpathat                  5
#define __NRAC_detach                       1
#define __NRAC_frealpath4                   4
#define __NRAC_getdrives                    0
#define __NRAC_writef                       4
#define __NRAC_readf                        4
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT */


/************************************************************************/
/* SYSCALL RETURN TYPES                                                 */
/************************************************************************/
#ifdef __WANT_SYSCALL_RETURN_TYPES
#ifndef __NRFEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NRFEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NRRT_restart_syscall              (errno_t, __errno_t)
#define __NRRT_exit                         (void, void)
#define __NRRT_fork                         (pid_t, __pid_t)
#define __NRRT_read                         (ssize_t, __ssize_t)
#define __NRRT_write                        (ssize_t, __ssize_t)
#define __NRRT_open                         (fd_t, __fd_t)
#define __NRRT_close                        (errno_t, __errno_t)
#define __NRRT_waitpid                      (pid_t, __pid_t)
#define __NRRT_creat                        (fd_t, __fd_t)
#define __NRRT_link                         (errno_t, __errno_t)
#define __NRRT_unlink                       (errno_t, __errno_t)
#define __NRRT_execve                       (errno_t, __errno_t)
#define __NRRT_chdir                        (errno_t, __errno_t)
#define __NRRT_time                         (int32_t, __int32_t)
#define __NRRT_mknod                        (errno_t, __errno_t)
#define __NRRT_chmod                        (errno_t, __errno_t)
#define __NRRT_lchown                       (errno_t, __errno_t)
#define __NRRT_break                        (errno_t, __errno_t)
#define __NRRT_oldstat                      (errno_t, __errno_t)
#define __NRRT_lseek                        (syscall_slong_t, __syscall_slong_t)
#define __NRRT_getpid                       (pid_t, __pid_t)
#define __NRRT_mount                        (errno_t, __errno_t)
#define __NRRT_umount                       (errno_t, __errno_t)
#define __NRRT_setuid                       (errno_t, __errno_t)
#define __NRRT_getuid                       (uint16_t, __uint16_t)
#define __NRRT_stime                        (errno_t, __errno_t)
#define __NRRT_ptrace                       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_alarm                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRRT_oldfstat                     (errno_t, __errno_t)
#define __NRRT_pause                        (errno_t, __errno_t)
#define __NRRT_utime                        (errno_t, __errno_t)
#define __NRRT_stty                         (errno_t, __errno_t)
#define __NRRT_gtty                         (errno_t, __errno_t)
#define __NRRT_access                       (errno_t, __errno_t)
#define __NRRT_nice                         (errno_t, __errno_t)
#define __NRRT_ftime                        (errno_t, __errno_t)
#define __NRRT_sync                         (errno_t, __errno_t)
#define __NRRT_kill                         (errno_t, __errno_t)
#define __NRRT_rename                       (errno_t, __errno_t)
#define __NRRT_mkdir                        (errno_t, __errno_t)
#define __NRRT_rmdir                        (errno_t, __errno_t)
#define __NRRT_dup                          (fd_t, __fd_t)
#define __NRRT_pipe                         (errno_t, __errno_t)
#define __NRRT_times                        (clock_t, __clock_t)
#define __NRRT_prof                         (errno_t, __errno_t)
#define __NRRT_brk                          (errno_t, __errno_t)
#define __NRRT_setgid                       (errno_t, __errno_t)
#define __NRRT_getgid                       (uint16_t, __uint16_t)
#define __NRRT_signal                       (__sigactionx32_sa_handler_t, __sigactionx32_sa_handler_t)
#define __NRRT_geteuid                      (uint16_t, __uint16_t)
#define __NRRT_getegid                      (uint16_t, __uint16_t)
#define __NRRT_acct                         (errno_t, __errno_t)
#define __NRRT_umount2                      (errno_t, __errno_t)
#define __NRRT_lock                         (errno_t, __errno_t)
#define __NRRT_ioctl                        (syscall_slong_t, __syscall_slong_t)
#define __NRRT_fcntl                        (syscall_slong_t, __syscall_slong_t)
#define __NRRT_mpx                          (errno_t, __errno_t)
#define __NRRT_setpgid                      (errno_t, __errno_t)
#define __NRRT_ulimit                       (errno_t, __errno_t)
#define __NRRT_oldolduname                  (errno_t, __errno_t)
#define __NRRT_umask                        (mode_t, __mode_t)
#define __NRRT_chroot                       (errno_t, __errno_t)
#define __NRRT_ustat                        (errno_t, __errno_t)
#define __NRRT_dup2                         (fd_t, __fd_t)
#define __NRRT_getppid                      (pid_t, __pid_t)
#define __NRRT_getpgrp                      (pid_t, __pid_t)
#define __NRRT_setsid                       (pid_t, __pid_t)
#define __NRRT_sigaction                    (errno_t, __errno_t)
#define __NRRT_sgetmask                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRRT_ssetmask                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRRT_setreuid                     (errno_t, __errno_t)
#define __NRRT_setregid                     (errno_t, __errno_t)
#define __NRRT_sigsuspend                   (errno_t, __errno_t)
#define __NRRT_sigpending                   (errno_t, __errno_t)
#define __NRRT_sethostname                  (errno_t, __errno_t)
#define __NRRT_setrlimit                    (errno_t, __errno_t)
#define __NRRT_getrlimit                    (errno_t, __errno_t)
#define __NRRT_getrusage                    (errno_t, __errno_t)
#define __NRRT_gettimeofday                 (errno_t, __errno_t)
#define __NRRT_settimeofday                 (errno_t, __errno_t)
#define __NRRT_getgroups                    (ssize_t, __ssize_t)
#define __NRRT_setgroups                    (errno_t, __errno_t)
#define __NRRT_select                       (ssize_t, __ssize_t)
#define __NRRT_symlink                      (errno_t, __errno_t)
#define __NRRT_oldlstat                     (errno_t, __errno_t)
#define __NRRT_readlink                     (ssize_t, __ssize_t)
#define __NRRT_uselib                       (errno_t, __errno_t)
#define __NRRT_swapon                       (errno_t, __errno_t)
#define __NRRT_reboot                       (errno_t, __errno_t)
#define __NRRT_readdir                      (syscall_slong_t, __syscall_slong_t)
#define __NRRT_mmap                         (void *, void *)
#define __NRRT_munmap                       (errno_t, __errno_t)
#define __NRRT_truncate                     (errno_t, __errno_t)
#define __NRRT_ftruncate                    (errno_t, __errno_t)
#define __NRRT_fchmod                       (errno_t, __errno_t)
#define __NRRT_fchown                       (errno_t, __errno_t)
#define __NRRT_getpriority                  (syscall_slong_t, __syscall_slong_t)
#define __NRRT_setpriority                  (errno_t, __errno_t)
#define __NRRT_profil                       (errno_t, __errno_t)
#define __NRRT_statfs                       (errno_t, __errno_t)
#define __NRRT_fstatfs                      (errno_t, __errno_t)
#define __NRRT_ioperm                       (errno_t, __errno_t)
#define __NRRT_socketcall                   (__LONG32_TYPE__, __LONG32_TYPE__)
#define __NRRT_syslog                       (ssize_t, __ssize_t)
#define __NRRT_setitimer                    (errno_t, __errno_t)
#define __NRRT_getitimer                    (errno_t, __errno_t)
#define __NRRT_stat                         (errno_t, __errno_t)
#define __NRRT_lstat                        (errno_t, __errno_t)
#define __NRRT_fstat                        (errno_t, __errno_t)
#define __NRRT_olduname                     (errno_t, __errno_t)
#define __NRRT_iopl                         (errno_t, __errno_t)
#define __NRRT_vhangup                      (errno_t, __errno_t)
#define __NRRT_idle                         (errno_t, __errno_t)
#define __NRRT_vm86old                      (errno_t, __errno_t)
#define __NRRT_wait4                        (pid_t, __pid_t)
#define __NRRT_swapoff                      (errno_t, __errno_t)
#define __NRRT_sysinfo                      (errno_t, __errno_t)
#define __NRRT_ipc                          (errno_t, __errno_t)
#define __NRRT_fsync                        (errno_t, __errno_t)
#define __NRRT_sigreturn                    (void, void)
#define __NRRT_clone                        (pid_t, __pid_t)
#define __NRRT_setdomainname                (errno_t, __errno_t)
#define __NRRT_uname                        (errno_t, __errno_t)
#define __NRRT_modify_ldt                   (syscall_slong_t, __syscall_slong_t)
#define __NRRT_adjtimex                     (errno_t, __errno_t)
#define __NRRT_mprotect                     (errno_t, __errno_t)
#define __NRRT_sigprocmask                  (errno_t, __errno_t)
#define __NRRT_create_module                (errno_t, __errno_t)
#define __NRRT_init_module                  (errno_t, __errno_t)
#define __NRRT_delete_module                (errno_t, __errno_t)
#define __NRRT_get_kernel_syms              (errno_t, __errno_t)
#define __NRRT_quotactl                     (errno_t, __errno_t)
#define __NRRT_getpgid                      (pid_t, __pid_t)
#define __NRRT_fchdir                       (errno_t, __errno_t)
#define __NRRT_bdflush                      (errno_t, __errno_t)
#define __NRRT_sysfs                        (errno_t, __errno_t)
#define __NRRT_personality                  (errno_t, __errno_t)
#define __NRRT_afs_syscall                  (errno_t, __errno_t)
#define __NRRT_setfsuid                     (errno_t, __errno_t)
#define __NRRT_setfsgid                     (errno_t, __errno_t)
#define __NRRT__llseek                      (errno_t, __errno_t)
#define __NRRT_getdents                     (ssize_t, __ssize_t)
#define __NRRT__newselect                   (ssize_t, __ssize_t)
#define __NRRT_flock                        (errno_t, __errno_t)
#define __NRRT_msync                        (errno_t, __errno_t)
#define __NRRT_readv                        (ssize_t, __ssize_t)
#define __NRRT_writev                       (ssize_t, __ssize_t)
#define __NRRT_getsid                       (pid_t, __pid_t)
#define __NRRT_fdatasync                    (errno_t, __errno_t)
#define __NRRT__sysctl                      (errno_t, __errno_t)
#define __NRRT_mlock                        (errno_t, __errno_t)
#define __NRRT_munlock                      (errno_t, __errno_t)
#define __NRRT_mlockall                     (errno_t, __errno_t)
#define __NRRT_munlockall                   (errno_t, __errno_t)
#define __NRRT_sched_setparam               (errno_t, __errno_t)
#define __NRRT_sched_getparam               (errno_t, __errno_t)
#define __NRRT_sched_setscheduler           (errno_t, __errno_t)
#define __NRRT_sched_getscheduler           (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_yield                  (errno_t, __errno_t)
#define __NRRT_sched_get_priority_max       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_get_priority_min       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_rr_get_interval        (errno_t, __errno_t)
#define __NRRT_nanosleep                    (errno_t, __errno_t)
#define __NRRT_mremap                       (void *, void *)
#define __NRRT_setresuid                    (errno_t, __errno_t)
#define __NRRT_getresuid                    (errno_t, __errno_t)
#define __NRRT_vm86                         (errno_t, __errno_t)
#define __NRRT_query_module                 (errno_t, __errno_t)
#define __NRRT_poll                         (ssize_t, __ssize_t)
#define __NRRT_nfsservctl                   (errno_t, __errno_t)
#define __NRRT_setresgid                    (errno_t, __errno_t)
#define __NRRT_getresgid                    (errno_t, __errno_t)
#define __NRRT_prctl                        (syscall_slong_t, __syscall_slong_t)
#define __NRRT_rt_sigreturn                 (void, void)
#define __NRRT_rt_sigaction                 (errno_t, __errno_t)
#define __NRRT_rt_sigprocmask               (errno_t, __errno_t)
#define __NRRT_rt_sigpending                (errno_t, __errno_t)
#define __NRRT_rt_sigtimedwait              (syscall_slong_t, __syscall_slong_t)
#define __NRRT_rt_sigqueueinfo              (errno_t, __errno_t)
#define __NRRT_rt_sigsuspend                (errno_t, __errno_t)
#define __NRRT_pread64                      (ssize_t, __ssize_t)
#define __NRRT_pwrite64                     (ssize_t, __ssize_t)
#define __NRRT_chown                        (errno_t, __errno_t)
#define __NRRT_getcwd                       (ssize_t, __ssize_t)
#define __NRRT_capget                       (errno_t, __errno_t)
#define __NRRT_capset                       (errno_t, __errno_t)
#define __NRRT_sigaltstack                  (errno_t, __errno_t)
#define __NRRT_sendfile                     (ssize_t, __ssize_t)
#define __NRRT_getpmsg                      (errno_t, __errno_t)
#define __NRRT_putpmsg                      (errno_t, __errno_t)
#define __NRRT_vfork                        (pid_t, __pid_t)
#define __NRRT_ugetrlimit                   (errno_t, __errno_t)
#define __NRRT_mmap2                        (void *, void *)
#define __NRRT_truncate64                   (errno_t, __errno_t)
#define __NRRT_ftruncate64                  (errno_t, __errno_t)
#define __NRRT_stat64                       (errno_t, __errno_t)
#define __NRRT_lstat64                      (errno_t, __errno_t)
#define __NRRT_fstat64                      (errno_t, __errno_t)
#define __NRRT_lchown32                     (errno_t, __errno_t)
#define __NRRT_getuid32                     (uint32_t, __uint32_t)
#define __NRRT_getgid32                     (uint32_t, __uint32_t)
#define __NRRT_geteuid32                    (uint32_t, __uint32_t)
#define __NRRT_getegid32                    (uint32_t, __uint32_t)
#define __NRRT_setreuid32                   (errno_t, __errno_t)
#define __NRRT_setregid32                   (errno_t, __errno_t)
#define __NRRT_getgroups32                  (ssize_t, __ssize_t)
#define __NRRT_setgroups32                  (errno_t, __errno_t)
#define __NRRT_fchown32                     (errno_t, __errno_t)
#define __NRRT_setresuid32                  (errno_t, __errno_t)
#define __NRRT_getresuid32                  (errno_t, __errno_t)
#define __NRRT_setresgid32                  (errno_t, __errno_t)
#define __NRRT_getresgid32                  (errno_t, __errno_t)
#define __NRRT_chown32                      (errno_t, __errno_t)
#define __NRRT_setuid32                     (errno_t, __errno_t)
#define __NRRT_setgid32                     (errno_t, __errno_t)
#define __NRRT_setfsuid32                   (errno_t, __errno_t)
#define __NRRT_setfsgid32                   (errno_t, __errno_t)
#define __NRRT_pivot_root                   (errno_t, __errno_t)
#define __NRRT_mincore                      (errno_t, __errno_t)
#define __NRRT_madvise                      (errno_t, __errno_t)
#define __NRRT_getdents64                   (ssize_t, __ssize_t)
#define __NRRT_fcntl64                      (syscall_slong_t, __syscall_slong_t)
#define __NRRT_gettid                       (pid_t, __pid_t)
#define __NRRT_readahead                    (ssize_t, __ssize_t)
#define __NRRT_setxattr                     (errno_t, __errno_t)
#define __NRRT_lsetxattr                    (errno_t, __errno_t)
#define __NRRT_fsetxattr                    (errno_t, __errno_t)
#define __NRRT_getxattr                     (ssize_t, __ssize_t)
#define __NRRT_lgetxattr                    (ssize_t, __ssize_t)
#define __NRRT_fgetxattr                    (ssize_t, __ssize_t)
#define __NRRT_listxattr                    (ssize_t, __ssize_t)
#define __NRRT_llistxattr                   (ssize_t, __ssize_t)
#define __NRRT_flistxattr                   (ssize_t, __ssize_t)
#define __NRRT_removexattr                  (errno_t, __errno_t)
#define __NRRT_lremovexattr                 (errno_t, __errno_t)
#define __NRRT_fremovexattr                 (errno_t, __errno_t)
#define __NRRT_tkill                        (errno_t, __errno_t)
#define __NRRT_sendfile64                   (ssize_t, __ssize_t)
#define __NRRT_futex                        (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_setaffinity            (errno_t, __errno_t)
#define __NRRT_sched_getaffinity            (errno_t, __errno_t)
#define __NRRT_set_thread_area              (errno_t, __errno_t)
#define __NRRT_get_thread_area              (errno_t, __errno_t)
#define __NRRT_io_setup                     (errno_t, __errno_t)
#define __NRRT_io_destroy                   (errno_t, __errno_t)
#define __NRRT_io_getevents                 (errno_t, __errno_t)
#define __NRRT_io_submit                    (errno_t, __errno_t)
#define __NRRT_io_cancel                    (errno_t, __errno_t)
#define __NRRT_fadvise64                    (errno_t, __errno_t)
#define __NRRT_exit_group                   (void, void)
#define __NRRT_lookup_dcookie               (errno_t, __errno_t)
#define __NRRT_epoll_create                 (fd_t, __fd_t)
#define __NRRT_epoll_ctl                    (errno_t, __errno_t)
#define __NRRT_epoll_wait                   (ssize_t, __ssize_t)
#define __NRRT_remap_file_pages             (errno_t, __errno_t)
#define __NRRT_set_tid_address              (pid_t, __pid_t)
#define __NRRT_timer_create                 (errno_t, __errno_t)
#define __NRRT_timer_settime                (errno_t, __errno_t)
#define __NRRT_timer_gettime                (errno_t, __errno_t)
#define __NRRT_timer_getoverrun             (syscall_slong_t, __syscall_slong_t)
#define __NRRT_timer_delete                 (errno_t, __errno_t)
#define __NRRT_clock_settime                (errno_t, __errno_t)
#define __NRRT_clock_gettime                (errno_t, __errno_t)
#define __NRRT_clock_getres                 (errno_t, __errno_t)
#define __NRRT_clock_nanosleep              (errno_t, __errno_t)
#define __NRRT_statfs64                     (errno_t, __errno_t)
#define __NRRT_fstatfs64                    (errno_t, __errno_t)
#define __NRRT_tgkill                       (errno_t, __errno_t)
#define __NRRT_utimes                       (errno_t, __errno_t)
#define __NRRT_fadvise64_64                 (errno_t, __errno_t)
#define __NRRT_vserver                      (errno_t, __errno_t)
#define __NRRT_mbind                        (errno_t, __errno_t)
#define __NRRT_get_mempolicy                (errno_t, __errno_t)
#define __NRRT_set_mempolicy                (errno_t, __errno_t)
#define __NRRT_mq_open                      (fd_t, __fd_t)
#define __NRRT_mq_unlink                    (errno_t, __errno_t)
#define __NRRT_mq_timedsend                 (errno_t, __errno_t)
#define __NRRT_mq_timedreceive              (ssize_t, __ssize_t)
#define __NRRT_mq_notify                    (errno_t, __errno_t)
#define __NRRT_mq_getsetattr                (errno_t, __errno_t)
#define __NRRT_kexec_load                   (errno_t, __errno_t)
#define __NRRT_waitid                       (errno_t, __errno_t)
#define __NRRT_add_key                      (errno_t, __errno_t)
#define __NRRT_request_key                  (errno_t, __errno_t)
#define __NRRT_keyctl                       (errno_t, __errno_t)
#define __NRRT_ioprio_set                   (errno_t, __errno_t)
#define __NRRT_ioprio_get                   (syscall_slong_t, __syscall_slong_t)
#define __NRRT_inotify_init                 (fd_t, __fd_t)
#define __NRRT_inotify_add_watch            (int, int)
#define __NRRT_inotify_rm_watch             (errno_t, __errno_t)
#define __NRRT_migrate_pages                (errno_t, __errno_t)
#define __NRRT_openat                       (fd_t, __fd_t)
#define __NRRT_mkdirat                      (errno_t, __errno_t)
#define __NRRT_mknodat                      (errno_t, __errno_t)
#define __NRRT_fchownat                     (errno_t, __errno_t)
#define __NRRT_futimesat                    (errno_t, __errno_t)
#define __NRRT_fstatat64                    (errno_t, __errno_t)
#define __NRRT_unlinkat                     (errno_t, __errno_t)
#define __NRRT_renameat                     (errno_t, __errno_t)
#define __NRRT_linkat                       (errno_t, __errno_t)
#define __NRRT_symlinkat                    (errno_t, __errno_t)
#define __NRRT_readlinkat                   (ssize_t, __ssize_t)
#define __NRRT_fchmodat                     (errno_t, __errno_t)
#define __NRRT_faccessat                    (errno_t, __errno_t)
#define __NRRT_pselect6                     (ssize_t, __ssize_t)
#define __NRRT_ppoll                        (ssize_t, __ssize_t)
#define __NRRT_unshare                      (errno_t, __errno_t)
#define __NRRT_set_robust_list              (errno_t, __errno_t)
#define __NRRT_get_robust_list              (errno_t, __errno_t)
#define __NRRT_splice                       (ssize_t, __ssize_t)
#define __NRRT_sync_file_range              (errno_t, __errno_t)
#define __NRRT_tee                          (ssize_t, __ssize_t)
#define __NRRT_vmsplice                     (ssize_t, __ssize_t)
#define __NRRT_move_pages                   (errno_t, __errno_t)
#define __NRRT_getcpu                       (errno_t, __errno_t)
#define __NRRT_epoll_pwait                  (ssize_t, __ssize_t)
#define __NRRT_utimensat                    (errno_t, __errno_t)
#define __NRRT_signalfd                     (errno_t, __errno_t)
#define __NRRT_timerfd_create               (fd_t, __fd_t)
#define __NRRT_eventfd                      (fd_t, __fd_t)
#define __NRRT_fallocate                    (errno_t, __errno_t)
#define __NRRT_timerfd_settime              (errno_t, __errno_t)
#define __NRRT_timerfd_gettime              (errno_t, __errno_t)
#define __NRRT_signalfd4                    (errno_t, __errno_t)
#define __NRRT_eventfd2                     (fd_t, __fd_t)
#define __NRRT_epoll_create1                (fd_t, __fd_t)
#define __NRRT_dup3                         (fd_t, __fd_t)
#define __NRRT_pipe2                        (errno_t, __errno_t)
#define __NRRT_inotify_init1                (fd_t, __fd_t)
#define __NRRT_preadv                       (ssize_t, __ssize_t)
#define __NRRT_pwritev                      (ssize_t, __ssize_t)
#define __NRRT_rt_tgsigqueueinfo            (errno_t, __errno_t)
#define __NRRT_perf_event_open              (errno_t, __errno_t)
#define __NRRT_recvmmsg                     (ssize_t, __ssize_t)
#define __NRRT_fanotify_init                (errno_t, __errno_t)
#define __NRRT_fanotify_mark                (errno_t, __errno_t)
#define __NRRT_prlimit64                    (errno_t, __errno_t)
#define __NRRT_name_to_handle_at            (errno_t, __errno_t)
#define __NRRT_open_by_handle_at            (fd_t, __fd_t)
#define __NRRT_clock_adjtime                (errno_t, __errno_t)
#define __NRRT_syncfs                       (errno_t, __errno_t)
#define __NRRT_sendmmsg                     (ssize_t, __ssize_t)
#define __NRRT_setns                        (errno_t, __errno_t)
#define __NRRT_process_vm_readv             (ssize_t, __ssize_t)
#define __NRRT_process_vm_writev            (ssize_t, __ssize_t)
#define __NRRT_kcmp                         (syscall_slong_t, __syscall_slong_t)
#define __NRRT_finit_module                 (errno_t, __errno_t)
#define __NRRT_sched_setattr                (errno_t, __errno_t)
#define __NRRT_sched_getattr                (errno_t, __errno_t)
#define __NRRT_renameat2                    (errno_t, __errno_t)
#define __NRRT_seccomp                      (errno_t, __errno_t)
#define __NRRT_getrandom                    (ssize_t, __ssize_t)
#define __NRRT_memfd_create                 (fd_t, __fd_t)
#define __NRRT_bpf                          (errno_t, __errno_t)
#define __NRRT_execveat                     (errno_t, __errno_t)
#define __NRRT_socket                       (fd_t, __fd_t)
#define __NRRT_socketpair                   (errno_t, __errno_t)
#define __NRRT_bind                         (errno_t, __errno_t)
#define __NRRT_connect                      (errno_t, __errno_t)
#define __NRRT_listen                       (errno_t, __errno_t)
#define __NRRT_accept4                      (fd_t, __fd_t)
#define __NRRT_getsockopt                   (errno_t, __errno_t)
#define __NRRT_setsockopt                   (errno_t, __errno_t)
#define __NRRT_getsockname                  (errno_t, __errno_t)
#define __NRRT_getpeername                  (errno_t, __errno_t)
#define __NRRT_sendto                       (ssize_t, __ssize_t)
#define __NRRT_sendmsg                      (ssize_t, __ssize_t)
#define __NRRT_recvfrom                     (ssize_t, __ssize_t)
#define __NRRT_recvmsg                      (ssize_t, __ssize_t)
#define __NRRT_shutdown                     (errno_t, __errno_t)
#define __NRRT_userfaultfd                  (fd_t, __fd_t)
#define __NRRT_membarrier                   (errno_t, __errno_t)
#define __NRRT_mlock2                       (errno_t, __errno_t)
#define __NRRT_copy_file_range              (errno_t, __errno_t)
#define __NRRT_preadv2                      (errno_t, __errno_t)
#define __NRRT_pwritev2                     (errno_t, __errno_t)
#define __NRRT_pkey_mprotect                (errno_t, __errno_t)
#define __NRRT_pkey_alloc                   (syscall_slong_t, __syscall_slong_t)
#define __NRRT_pkey_free                    (errno_t, __errno_t)
#define __NRRT_statx                        (errno_t, __errno_t)
#define __NRRT_arch_prctl                   (syscall_slong_t, __syscall_slong_t)
#define __NRRT_io_pgetevents                (errno_t, __errno_t)
#define __NRRT_rseq                         (errno_t, __errno_t)
#define __NRRT_semget                       (errno_t, __errno_t)
#define __NRRT_semctl                       (errno_t, __errno_t)
#define __NRRT_shmget                       (errno_t, __errno_t)
#define __NRRT_shmctl                       (errno_t, __errno_t)
#define __NRRT_shmat                        (errno_t, __errno_t)
#define __NRRT_shmdt                        (errno_t, __errno_t)
#define __NRRT_msgget                       (errno_t, __errno_t)
#define __NRRT_msgsnd                       (errno_t, __errno_t)
#define __NRRT_msgrcv                       (errno_t, __errno_t)
#define __NRRT_msgctl                       (errno_t, __errno_t)
#define __NRRT_clock_gettime64              (errno_t, __errno_t)
#define __NRRT_clock_settime64              (errno_t, __errno_t)
#define __NRRT_clock_adjtime64              (errno_t, __errno_t)
#define __NRRT_clock_getres_time64          (errno_t, __errno_t)
#define __NRRT_clock_nanosleep_time64       (errno_t, __errno_t)
#define __NRRT_timer_gettime64              (errno_t, __errno_t)
#define __NRRT_timer_settime64              (errno_t, __errno_t)
#define __NRRT_timerfd_gettime64            (errno_t, __errno_t)
#define __NRRT_timerfd_settime64            (errno_t, __errno_t)
#define __NRRT_utimensat_time64             (errno_t, __errno_t)
#define __NRRT_pselect6_time64              (ssize_t, __ssize_t)
#define __NRRT_ppoll_time64                 (ssize_t, __ssize_t)
#define __NRRT_io_pgetevents_time64         (errno_t, __errno_t)
#define __NRRT_recvmmsg_time64              (ssize_t, __ssize_t)
#define __NRRT_mq_timedsend_time64          (errno_t, __errno_t)
#define __NRRT_mq_timedreceive_time64       (ssize_t, __ssize_t)
#define __NRRT_semtimedop_time64            (errno_t, __errno_t)
#define __NRRT_rt_sigtimedwait_time64       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_futex_time64                 (syscall_slong_t, __syscall_slong_t)
#define __NRRT_sched_rr_get_interval_time64 (errno_t, __errno_t)
#define __NRRT_pidfd_send_signal            (errno_t, __errno_t)
#define __NRRT_io_uring_setup               (errno_t, __errno_t)
#define __NRRT_io_uring_enter               (errno_t, __errno_t)
#define __NRRT_io_uring_register            (errno_t, __errno_t)
#define __NRRT_open_tree                    (errno_t, __errno_t)
#define __NRRT_move_mount                   (errno_t, __errno_t)
#define __NRRT_fsopen                       (errno_t, __errno_t)
#define __NRRT_fsconfig                     (errno_t, __errno_t)
#define __NRRT_fsmount                      (errno_t, __errno_t)
#define __NRRT_fspick                       (errno_t, __errno_t)
#define __NRRT_pidfd_open                   (fd_t, __fd_t)
#define __NRRT_clone3                       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_close_range                  (errno_t, __errno_t)
#define __NRRT_openat2                      (errno_t, __errno_t)
#define __NRRT_pidfd_getfd                  (fd_t, __fd_t)
#define __NRRT_faccessat2                   (errno_t, __errno_t)
#define __NRRT_pwritevf                     (ssize_t, __ssize_t)
#define __NRRT_preadvf                      (ssize_t, __ssize_t)
#define __NRRT_fallocate64                  (errno_t, __errno_t)
#define __NRRT_freadlinkat                  (ssize_t, __ssize_t)
#define __NRRT_fsymlinkat                   (errno_t, __errno_t)
#define __NRRT_kfstatat                     (errno_t, __errno_t)
#define __NRRT_futimesat64                  (errno_t, __errno_t)
#define __NRRT_fmknodat                     (errno_t, __errno_t)
#define __NRRT_fmkdirat                     (errno_t, __errno_t)
#define __NRRT_inotify_add_watch_at         (int, int)
#define __NRRT_waitid64                     (errno_t, __errno_t)
#define __NRRT_utimes64                     (errno_t, __errno_t)
#define __NRRT_set_userprocmask_address     (errno_t, __errno_t)
#define __NRRT_lfutexexpr                   (errno_t, __errno_t)
#define __NRRT_lfutex                       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_kreaddirf                    (ssize_t, __ssize_t)
#define __NRRT_kreaddir                     (ssize_t, __ssize_t)
#define __NRRT_kfstat                       (errno_t, __errno_t)
#define __NRRT_klstat                       (errno_t, __errno_t)
#define __NRRT_kstat                        (errno_t, __errno_t)
#define __NRRT_pwrite64f                    (ssize_t, __ssize_t)
#define __NRRT_pread64f                     (ssize_t, __ssize_t)
#define __NRRT_ksigreturn                   (void, void)
#define __NRRT_nanosleep64                  (errno_t, __errno_t)
#define __NRRT_rpc_serve_sysret             (errno_t, __errno_t)
#define __NRRT_rpc_serve                    (errno_t, __errno_t)
#define __NRRT_ksysctl                      (syscall_slong_t, __syscall_slong_t)
#define __NRRT_writevf                      (ssize_t, __ssize_t)
#define __NRRT_readvf                       (ssize_t, __ssize_t)
#define __NRRT_select64                     (ssize_t, __ssize_t)
#define __NRRT_wait4_64                     (pid_t, __pid_t)
#define __NRRT_getitimer64                  (errno_t, __errno_t)
#define __NRRT_setitimer64                  (errno_t, __errno_t)
#define __NRRT_maplibrary                   (void *, void *)
#define __NRRT_settimeofday64               (errno_t, __errno_t)
#define __NRRT_gettimeofday64               (errno_t, __errno_t)
#define __NRRT_getrusage64                  (errno_t, __errno_t)
#define __NRRT_fsmode                       (uint64_t, __uint64_t)
#define __NRRT_ioctlf                       (syscall_slong_t, __syscall_slong_t)
#define __NRRT_rtm_test                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRRT_rtm_abort                    (errno_t, __errno_t)
#define __NRRT_rtm_end                      (errno_t, __errno_t)
#define __NRRT_rtm_begin                    (rtm_status_t, __rtm_status_t)
#define __NRRT_ftime64                      (errno_t, __errno_t)
#define __NRRT_utime64                      (errno_t, __errno_t)
#define __NRRT_stime64                      (errno_t, __errno_t)
#define __NRRT_userviofd                    (fd_t, __fd_t)
#define __NRRT_lseek64                      (int64_t, __int64_t)
#define __NRRT_coredump                     (errno_t, __errno_t)
#define __NRRT_debugtrap                    (errno_t, __errno_t)
#define __NRRT_get_exception_handler        (errno_t, __errno_t)
#define __NRRT_set_exception_handler        (errno_t, __errno_t)
#define __NRRT_mktty                        (fd_t, __fd_t)
#define __NRRT_time64                       (int64_t, __int64_t)
#define __NRRT_fchdirat                     (errno_t, __errno_t)
#define __NRRT_openpty                      (errno_t, __errno_t)
#define __NRRT_rpc_schedule                 (errno_t, __errno_t)
#define __NRRT_frealpathat                  (ssize_t, __ssize_t)
#define __NRRT_detach                       (errno_t, __errno_t)
#define __NRRT_frealpath4                   (ssize_t, __ssize_t)
#define __NRRT_getdrives                    (syscall_slong_t, __syscall_slong_t)
#define __NRRT_writef                       (ssize_t, __ssize_t)
#define __NRRT_readf                        (ssize_t, __ssize_t)
#endif /* !__NRFEAT_DEFINED_SYSCALL_RETURN_TYPES */
#endif /* __WANT_SYSCALL_RETURN_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT TYPES                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_TYPES
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NRAT0_exit                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_read                         (fd_t, __fd_t)
#define __NRAT1_read                         (void *, void *)
#define __NRAT2_read                         (size_t, __size_t)
#define __NRAT0_write                        (fd_t, __fd_t)
#define __NRAT1_write                        (void const *, void const *)
#define __NRAT2_write                        (size_t, __size_t)
#define __NRAT0_open                         (char const *, char const *)
#define __NRAT1_open                         (oflag_t, __oflag_t)
#define __NRAT2_open                         (mode_t, __mode_t)
#define __NRAT0_close                        (fd_t, __fd_t)
#define __NRAT0_waitpid                      (pid_t, __pid_t)
#define __NRAT1_waitpid                      (int32_t *, __int32_t *)
#define __NRAT2_waitpid                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_creat                        (char const *, char const *)
#define __NRAT1_creat                        (mode_t, __mode_t)
#define __NRAT0_link                         (char const *, char const *)
#define __NRAT1_link                         (char const *, char const *)
#define __NRAT0_unlink                       (char const *, char const *)
#define __NRAT0_execve                       (char const *, char const *)
#define __NRAT1_execve                       (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NRAT2_execve                       (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NRAT0_chdir                        (char const *, char const *)
#define __NRAT0_time                         (int32_t *, __int32_t *)
#define __NRAT0_mknod                        (char const *, char const *)
#define __NRAT1_mknod                        (mode_t, __mode_t)
#define __NRAT2_mknod                        (dev_t, __dev_t)
#define __NRAT0_chmod                        (char const *, char const *)
#define __NRAT1_chmod                        (mode_t, __mode_t)
#define __NRAT0_lchown                       (char const *, char const *)
#define __NRAT1_lchown                       (uint16_t, __uint16_t)
#define __NRAT2_lchown                       (uint16_t, __uint16_t)
#define __NRAT0_oldstat                      (char const *, char const *)
#define __NRAT1_oldstat                      (struct linux_oldstat *, struct linux_oldstat *)
#define __NRAT0_lseek                        (fd_t, __fd_t)
#define __NRAT1_lseek                        (syscall_slong_t, __syscall_slong_t)
#define __NRAT2_lseek                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_mount                        (char const *, char const *)
#define __NRAT1_mount                        (char const *, char const *)
#define __NRAT2_mount                        (char const *, char const *)
#define __NRAT3_mount                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_mount                        (void const *, void const *)
#define __NRAT0_umount                       (char const *, char const *)
#define __NRAT0_setuid                       (uint16_t, __uint16_t)
#define __NRAT0_stime                        (time32_t const *, __time32_t const *)
#define __NRAT0_ptrace                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_ptrace                       (pid_t, __pid_t)
#define __NRAT2_ptrace                       (void *, void *)
#define __NRAT3_ptrace                       (void *, void *)
#define __NRAT0_alarm                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_oldfstat                     (fd_t, __fd_t)
#define __NRAT1_oldfstat                     (struct linux_oldstat *, struct linux_oldstat *)
#define __NRAT0_utime                        (char const *, char const *)
#define __NRAT1_utime                        (struct utimbufx32 const *, struct __utimbufx32 const *)
#define __NRAT0_access                       (char const *, char const *)
#define __NRAT1_access                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_nice                         (syscall_slong_t, __syscall_slong_t)
#define __NRAT0_ftime                        (struct timebx32 *, struct __timebx32 *)
#define __NRAT0_kill                         (pid_t, __pid_t)
#define __NRAT1_kill                         (signo_t, __signo_t)
#define __NRAT0_rename                       (char const *, char const *)
#define __NRAT1_rename                       (char const *, char const *)
#define __NRAT0_mkdir                        (char const *, char const *)
#define __NRAT1_mkdir                        (mode_t, __mode_t)
#define __NRAT0_rmdir                        (char const *, char const *)
#define __NRAT0_dup                          (fd_t, __fd_t)
#define __NRAT0_pipe                         (fd_t *, __fd_t *)
#define __NRAT0_times                        (struct tmsx32 *, struct __tmsx32 *)
#define __NRAT0_brk                          (void *, void *)
#define __NRAT0_setgid                       (uint16_t, __uint16_t)
#define __NRAT0_signal                       (signo_t, __signo_t)
#define __NRAT1_signal                       (__sigactionx32_sa_handler_t, __sigactionx32_sa_handler_t)
#define __NRAT0_acct                         (char const *, char const *)
#define __NRAT0_umount2                      (char const *, char const *)
#define __NRAT1_umount2                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_ioctl                        (fd_t, __fd_t)
#define __NRAT1_ioctl                        (ioctl_t, __ioctl_t)
#define __NRAT2_ioctl                        (void *, void *)
#define __NRAT0_fcntl                        (fd_t, __fd_t)
#define __NRAT1_fcntl                        (fcntl_t, __fcntl_t)
#define __NRAT2_fcntl                        (void *, void *)
#define __NRAT0_setpgid                      (pid_t, __pid_t)
#define __NRAT1_setpgid                      (pid_t, __pid_t)
#define __NRAT0_oldolduname                  (struct linux_oldolduname *, struct linux_oldolduname *)
#define __NRAT0_umask                        (mode_t, __mode_t)
#define __NRAT0_chroot                       (char const *, char const *)
#define __NRAT0_ustat                        (dev_t, __dev_t)
#define __NRAT1_ustat                        (struct ustat *, struct ustat *)
#define __NRAT0_dup2                         (fd_t, __fd_t)
#define __NRAT1_dup2                         (fd_t, __fd_t)
#define __NRAT0_sigaction                    (signo_t, __signo_t)
#define __NRAT1_sigaction                    (struct __old_kernel_sigactionx32 const *, struct __old_kernel_sigactionx32 const *)
#define __NRAT2_sigaction                    (struct __old_kernel_sigactionx32 *, struct __old_kernel_sigactionx32 *)
#define __NRAT0_ssetmask                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_setreuid                     (uint16_t, __uint16_t)
#define __NRAT1_setreuid                     (uint16_t, __uint16_t)
#define __NRAT0_setregid                     (uint16_t, __uint16_t)
#define __NRAT1_setregid                     (uint16_t, __uint16_t)
#define __NRAT0_sigsuspend                   (struct __old_sigset_struct const *, struct __old_sigset_struct const *)
#define __NRAT0_sigpending                   (struct __old_sigset_struct *, struct __old_sigset_struct *)
#define __NRAT0_sethostname                  (char const *, char const *)
#define __NRAT1_sethostname                  (size_t, __size_t)
#define __NRAT0_setrlimit                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_setrlimit                    (struct rlimitx32 const *, struct __rlimitx32 const *)
#define __NRAT0_getrlimit                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_getrlimit                    (struct rlimitx32 *, struct __rlimitx32 *)
#define __NRAT0_getrusage                    (syscall_slong_t, __syscall_slong_t)
#define __NRAT1_getrusage                    (struct rusagex32 *, struct __rusagex32 *)
#define __NRAT0_gettimeofday                 (struct timevalx32 *, struct __timevalx32 *)
#define __NRAT1_gettimeofday                 (struct timezone *, struct timezone *)
#define __NRAT0_settimeofday                 (struct timevalx32 const *, struct __timevalx32 const *)
#define __NRAT1_settimeofday                 (struct timezone const *, struct timezone const *)
#define __NRAT0_getgroups                    (size_t, __size_t)
#define __NRAT1_getgroups                    (uint16_t *, __uint16_t *)
#define __NRAT0_setgroups                    (size_t, __size_t)
#define __NRAT1_setgroups                    (uint16_t const *, __uint16_t const *)
#define __NRAT0_select                       (struct sel_arg_structx32 const *, struct sel_arg_structx32 const *)
#define __NRAT0_symlink                      (char const *, char const *)
#define __NRAT1_symlink                      (char const *, char const *)
#define __NRAT0_oldlstat                     (char const *, char const *)
#define __NRAT1_oldlstat                     (struct linux_oldstat *, struct linux_oldstat *)
#define __NRAT0_readlink                     (char const *, char const *)
#define __NRAT1_readlink                     (char *, char *)
#define __NRAT2_readlink                     (size_t, __size_t)
#define __NRAT0_uselib                       (char const *, char const *)
#define __NRAT0_swapon                       (char const *, char const *)
#define __NRAT1_swapon                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_reboot                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_readdir                      (fd_t, __fd_t)
#define __NRAT1_readdir                      (struct old_linux_direntx32 *, struct old_linux_direntx32 *)
#define __NRAT0_mmap                         (void *, void *)
#define __NRAT1_mmap                         (size_t, __size_t)
#define __NRAT2_mmap                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_mmap                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_mmap                         (fd_t, __fd_t)
#define __NRAT5_mmap                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_munmap                       (void *, void *)
#define __NRAT1_munmap                       (size_t, __size_t)
#define __NRAT0_truncate                     (char const *, char const *)
#define __NRAT1_truncate                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_ftruncate                    (fd_t, __fd_t)
#define __NRAT1_ftruncate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_fchmod                       (fd_t, __fd_t)
#define __NRAT1_fchmod                       (mode_t, __mode_t)
#define __NRAT0_fchown                       (fd_t, __fd_t)
#define __NRAT1_fchown                       (uint16_t, __uint16_t)
#define __NRAT2_fchown                       (uint16_t, __uint16_t)
#define __NRAT0_getpriority                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_getpriority                  (id_t, __id_t)
#define __NRAT0_setpriority                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_setpriority                  (id_t, __id_t)
#define __NRAT2_setpriority                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_statfs                       (char const *, char const *)
#define __NRAT1_statfs                       (struct statfsx32 *, struct __statfsx32 *)
#define __NRAT0_fstatfs                      (fd_t, __fd_t)
#define __NRAT1_fstatfs                      (struct statfsx32 *, struct __statfsx32 *)
#define __NRAT0_ioperm                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_ioperm                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_ioperm                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_socketcall                   (__ULONG32_TYPE__, __ULONG32_TYPE__)
#define __NRAT1_socketcall                   (__ULONG32_TYPE__ *, __ULONG32_TYPE__ *)
#define __NRAT0_syslog                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_syslog                       (char const *, char const *)
#define __NRAT2_syslog                       (size_t, __size_t)
#define __NRAT0_setitimer                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_setitimer                    (struct __itimervalx32 const *, struct __itimervalx32 const *)
#define __NRAT2_setitimer                    (struct __itimervalx32 *, struct __itimervalx32 *)
#define __NRAT0_getitimer                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_getitimer                    (struct __itimervalx32 *, struct __itimervalx32 *)
#define __NRAT0_stat                         (char const *, char const *)
#define __NRAT1_stat                         (struct linux_statx32 *, struct linux_statx32 *)
#define __NRAT0_lstat                        (char const *, char const *)
#define __NRAT1_lstat                        (struct linux_statx32 *, struct linux_statx32 *)
#define __NRAT0_fstat                        (fd_t, __fd_t)
#define __NRAT1_fstat                        (struct linux_statx32 *, struct linux_statx32 *)
#define __NRAT0_olduname                     (struct linux_olduname *, struct linux_olduname *)
#define __NRAT0_iopl                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_vm86old                      (int, int)
#define __NRAT0_wait4                        (pid_t, __pid_t)
#define __NRAT1_wait4                        (int32_t *, __int32_t *)
#define __NRAT2_wait4                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_wait4                        (struct rusagex32 *, struct __rusagex32 *)
#define __NRAT0_swapoff                      (char const *, char const *)
#define __NRAT0_sysinfo                      (struct __sysinfox32 *, struct __sysinfox32 *)
#define __NRAT0_ipc                          (int, int)
#define __NRAT0_fsync                        (fd_t, __fd_t)
#define __NRAT0_clone                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_clone                        (void *, void *)
#define __NRAT2_clone                        (pid_t *, __pid_t *)
#define __NRAT3_clone                        (uintptr_t, __uintptr_t)
#define __NRAT4_clone                        (pid_t *, __pid_t *)
#define __NRAT0_setdomainname                (char const *, char const *)
#define __NRAT1_setdomainname                (size_t, __size_t)
#define __NRAT0_uname                        (struct utsname *, struct utsname *)
#define __NRAT0_modify_ldt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_modify_ldt                   (void *, void *)
#define __NRAT2_modify_ldt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_adjtimex                     (struct timex *, struct timex *)
#define __NRAT0_mprotect                     (void *, void *)
#define __NRAT1_mprotect                     (size_t, __size_t)
#define __NRAT2_mprotect                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sigprocmask                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_sigprocmask                  (struct __old_sigset_struct const *, struct __old_sigset_struct const *)
#define __NRAT2_sigprocmask                  (struct __old_sigset_struct *, struct __old_sigset_struct *)
#define __NRAT0_init_module                  (void const *, void const *)
#define __NRAT1_init_module                  (size_t, __size_t)
#define __NRAT2_init_module                  (char const *, char const *)
#define __NRAT0_delete_module                (char const *, char const *)
#define __NRAT1_delete_module                (oflag_t, __oflag_t)
#define __NRAT0_quotactl                     (int, int)
#define __NRAT0_getpgid                      (pid_t, __pid_t)
#define __NRAT0_fchdir                       (fd_t, __fd_t)
#define __NRAT0_bdflush                      (int, int)
#define __NRAT0_sysfs                        (int, int)
#define __NRAT0_personality                  (int, int)
#define __NRAT0_setfsuid                     (uint16_t, __uint16_t)
#define __NRAT0_setfsgid                     (uint16_t, __uint16_t)
#define __NRAT0__llseek                      (fd_t, __fd_t)
#define __NRAT1__llseek                      (int64_t, __int64_t)
#define __NRAT2__llseek                      (uint64_t *, __uint64_t *)
#define __NRAT3__llseek                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_getdents                     (fd_t, __fd_t)
#define __NRAT1_getdents                     (struct linux_direntx32 *, struct linux_direntx32 *)
#define __NRAT2_getdents                     (size_t, __size_t)
#define __NRAT0__newselect                   (size_t, __size_t)
#define __NRAT1__newselect                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT2__newselect                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT3__newselect                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT4__newselect                   (struct timevalx32 *, struct __timevalx32 *)
#define __NRAT0_flock                        (fd_t, __fd_t)
#define __NRAT1_flock                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_msync                        (void *, void *)
#define __NRAT1_msync                        (size_t, __size_t)
#define __NRAT2_msync                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_readv                        (fd_t, __fd_t)
#define __NRAT1_readv                        (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_readv                        (size_t, __size_t)
#define __NRAT0_writev                       (fd_t, __fd_t)
#define __NRAT1_writev                       (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_writev                       (size_t, __size_t)
#define __NRAT0_getsid                       (pid_t, __pid_t)
#define __NRAT0_fdatasync                    (fd_t, __fd_t)
#define __NRAT0__sysctl                      (int, int)
#define __NRAT0_mlock                        (void const *, void const *)
#define __NRAT1_mlock                        (size_t, __size_t)
#define __NRAT0_munlock                      (void const *, void const *)
#define __NRAT1_munlock                      (size_t, __size_t)
#define __NRAT0_mlockall                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sched_setparam               (pid_t, __pid_t)
#define __NRAT1_sched_setparam               (struct sched_param const *, struct sched_param const *)
#define __NRAT0_sched_getparam               (pid_t, __pid_t)
#define __NRAT1_sched_getparam               (struct sched_param *, struct sched_param *)
#define __NRAT0_sched_setscheduler           (pid_t, __pid_t)
#define __NRAT1_sched_setscheduler           (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_sched_setscheduler           (struct sched_param const *, struct sched_param const *)
#define __NRAT0_sched_getscheduler           (pid_t, __pid_t)
#define __NRAT0_sched_get_priority_max       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sched_get_priority_min       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sched_rr_get_interval        (pid_t, __pid_t)
#define __NRAT1_sched_rr_get_interval        (struct timespecx32 *, struct __timespecx32 *)
#define __NRAT0_nanosleep                    (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT1_nanosleep                    (struct timespecx32 *, struct __timespecx32 *)
#define __NRAT0_mremap                       (void *, void *)
#define __NRAT1_mremap                       (size_t, __size_t)
#define __NRAT2_mremap                       (size_t, __size_t)
#define __NRAT3_mremap                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_mremap                       (void *, void *)
#define __NRAT0_setresuid                    (uint16_t, __uint16_t)
#define __NRAT1_setresuid                    (uint16_t, __uint16_t)
#define __NRAT2_setresuid                    (uint16_t, __uint16_t)
#define __NRAT0_getresuid                    (uint16_t *, __uint16_t *)
#define __NRAT1_getresuid                    (uint16_t *, __uint16_t *)
#define __NRAT2_getresuid                    (uint16_t *, __uint16_t *)
#define __NRAT0_vm86                         (int, int)
#define __NRAT0_poll                         (struct pollfd *, struct pollfd *)
#define __NRAT1_poll                         (size_t, __size_t)
#define __NRAT2_poll                         (syscall_slong_t, __syscall_slong_t)
#define __NRAT0_nfsservctl                   (int, int)
#define __NRAT0_setresgid                    (uint16_t, __uint16_t)
#define __NRAT1_setresgid                    (uint16_t, __uint16_t)
#define __NRAT2_setresgid                    (uint16_t, __uint16_t)
#define __NRAT0_getresgid                    (uint16_t *, __uint16_t *)
#define __NRAT1_getresgid                    (uint16_t *, __uint16_t *)
#define __NRAT2_getresgid                    (uint16_t *, __uint16_t *)
#define __NRAT0_prctl                        (unsigned int, unsigned int)
#define __NRAT1_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_rt_sigaction                 (signo_t, __signo_t)
#define __NRAT1_rt_sigaction                 (struct __kernel_sigactionx32 const *, struct __kernel_sigactionx32 const *)
#define __NRAT2_rt_sigaction                 (struct __kernel_sigactionx32 *, struct __kernel_sigactionx32 *)
#define __NRAT3_rt_sigaction                 (size_t, __size_t)
#define __NRAT0_rt_sigprocmask               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_rt_sigprocmask               (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT2_rt_sigprocmask               (struct __sigset_struct *, struct __sigset_struct *)
#define __NRAT3_rt_sigprocmask               (size_t, __size_t)
#define __NRAT0_rt_sigpending                (struct __sigset_struct *, struct __sigset_struct *)
#define __NRAT1_rt_sigpending                (size_t, __size_t)
#define __NRAT0_rt_sigtimedwait              (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT1_rt_sigtimedwait              (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NRAT2_rt_sigtimedwait              (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT3_rt_sigtimedwait              (size_t, __size_t)
#define __NRAT0_rt_sigqueueinfo              (pid_t, __pid_t)
#define __NRAT1_rt_sigqueueinfo              (signo_t, __signo_t)
#define __NRAT2_rt_sigqueueinfo              (struct __siginfox32_struct const *, struct __siginfox32_struct const *)
#define __NRAT0_rt_sigsuspend                (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT1_rt_sigsuspend                (size_t, __size_t)
#define __NRAT0_pread64                      (fd_t, __fd_t)
#define __NRAT1_pread64                      (void *, void *)
#define __NRAT2_pread64                      (size_t, __size_t)
#define __NRAT3_pread64                      (uint64_t, __uint64_t)
#define __NRAT0_pwrite64                     (fd_t, __fd_t)
#define __NRAT1_pwrite64                     (void const *, void const *)
#define __NRAT2_pwrite64                     (size_t, __size_t)
#define __NRAT3_pwrite64                     (uint64_t, __uint64_t)
#define __NRAT0_chown                        (char const *, char const *)
#define __NRAT1_chown                        (uint16_t, __uint16_t)
#define __NRAT2_chown                        (uint16_t, __uint16_t)
#define __NRAT0_getcwd                       (char *, char *)
#define __NRAT1_getcwd                       (size_t, __size_t)
#define __NRAT0_capget                       (int, int)
#define __NRAT0_capset                       (int, int)
#define __NRAT0_sigaltstack                  (struct __sigaltstackx32 const *, struct __sigaltstackx32 const *)
#define __NRAT1_sigaltstack                  (struct __sigaltstackx32 *, struct __sigaltstackx32 *)
#define __NRAT0_sendfile                     (fd_t, __fd_t)
#define __NRAT1_sendfile                     (fd_t, __fd_t)
#define __NRAT2_sendfile                     (__ULONG32_TYPE__ *, __ULONG32_TYPE__ *)
#define __NRAT3_sendfile                     (size_t, __size_t)
#define __NRAT0_ugetrlimit                   (int, int)
#define __NRAT0_mmap2                        (void *, void *)
#define __NRAT1_mmap2                        (size_t, __size_t)
#define __NRAT2_mmap2                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_mmap2                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_mmap2                        (fd_t, __fd_t)
#define __NRAT5_mmap2                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_truncate64                   (char const *, char const *)
#define __NRAT1_truncate64                   (uint64_t, __uint64_t)
#define __NRAT0_ftruncate64                  (fd_t, __fd_t)
#define __NRAT1_ftruncate64                  (uint64_t, __uint64_t)
#define __NRAT0_stat64                       (char const *, char const *)
#define __NRAT1_stat64                       (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NRAT0_lstat64                      (char const *, char const *)
#define __NRAT1_lstat64                      (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NRAT0_fstat64                      (fd_t, __fd_t)
#define __NRAT1_fstat64                      (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NRAT0_lchown32                     (char const *, char const *)
#define __NRAT1_lchown32                     (uint32_t, __uint32_t)
#define __NRAT2_lchown32                     (uint32_t, __uint32_t)
#define __NRAT0_setreuid32                   (uint32_t, __uint32_t)
#define __NRAT1_setreuid32                   (uint32_t, __uint32_t)
#define __NRAT0_setregid32                   (uint32_t, __uint32_t)
#define __NRAT1_setregid32                   (uint32_t, __uint32_t)
#define __NRAT0_getgroups32                  (size_t, __size_t)
#define __NRAT1_getgroups32                  (uint32_t *, __uint32_t *)
#define __NRAT0_setgroups32                  (size_t, __size_t)
#define __NRAT1_setgroups32                  (uint32_t const *, __uint32_t const *)
#define __NRAT0_fchown32                     (fd_t, __fd_t)
#define __NRAT1_fchown32                     (uint32_t, __uint32_t)
#define __NRAT2_fchown32                     (uint32_t, __uint32_t)
#define __NRAT0_setresuid32                  (uint32_t, __uint32_t)
#define __NRAT1_setresuid32                  (uint32_t, __uint32_t)
#define __NRAT2_setresuid32                  (uint32_t, __uint32_t)
#define __NRAT0_getresuid32                  (uint32_t *, __uint32_t *)
#define __NRAT1_getresuid32                  (uint32_t *, __uint32_t *)
#define __NRAT2_getresuid32                  (uint32_t *, __uint32_t *)
#define __NRAT0_setresgid32                  (uint32_t, __uint32_t)
#define __NRAT1_setresgid32                  (uint32_t, __uint32_t)
#define __NRAT2_setresgid32                  (uint32_t, __uint32_t)
#define __NRAT0_getresgid32                  (uint32_t *, __uint32_t *)
#define __NRAT1_getresgid32                  (uint32_t *, __uint32_t *)
#define __NRAT2_getresgid32                  (uint32_t *, __uint32_t *)
#define __NRAT0_chown32                      (char const *, char const *)
#define __NRAT1_chown32                      (uint32_t, __uint32_t)
#define __NRAT2_chown32                      (uint32_t, __uint32_t)
#define __NRAT0_setuid32                     (uint32_t, __uint32_t)
#define __NRAT0_setgid32                     (uint32_t, __uint32_t)
#define __NRAT0_setfsuid32                   (uint32_t, __uint32_t)
#define __NRAT0_setfsgid32                   (uint32_t, __uint32_t)
#define __NRAT0_pivot_root                   (int, int)
#define __NRAT0_mincore                      (void *, void *)
#define __NRAT1_mincore                      (size_t, __size_t)
#define __NRAT2_mincore                      (uint8_t *, __uint8_t *)
#define __NRAT0_madvise                      (void *, void *)
#define __NRAT1_madvise                      (size_t, __size_t)
#define __NRAT2_madvise                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_getdents64                   (fd_t, __fd_t)
#define __NRAT1_getdents64                   (struct linux_dirent64 *, struct linux_dirent64 *)
#define __NRAT2_getdents64                   (size_t, __size_t)
#define __NRAT0_fcntl64                      (fd_t, __fd_t)
#define __NRAT1_fcntl64                      (fcntl_t, __fcntl_t)
#define __NRAT2_fcntl64                      (void *, void *)
#define __NRAT0_readahead                    (fd_t, __fd_t)
#define __NRAT1_readahead                    (uint64_t, __uint64_t)
#define __NRAT2_readahead                    (size_t, __size_t)
#define __NRAT0_setxattr                     (char const *, char const *)
#define __NRAT1_setxattr                     (char const *, char const *)
#define __NRAT2_setxattr                     (void const *, void const *)
#define __NRAT3_setxattr                     (size_t, __size_t)
#define __NRAT4_setxattr                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_lsetxattr                    (char const *, char const *)
#define __NRAT1_lsetxattr                    (char const *, char const *)
#define __NRAT2_lsetxattr                    (void const *, void const *)
#define __NRAT3_lsetxattr                    (size_t, __size_t)
#define __NRAT4_lsetxattr                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_fsetxattr                    (fd_t, __fd_t)
#define __NRAT1_fsetxattr                    (char const *, char const *)
#define __NRAT2_fsetxattr                    (void const *, void const *)
#define __NRAT3_fsetxattr                    (size_t, __size_t)
#define __NRAT4_fsetxattr                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_getxattr                     (char const *, char const *)
#define __NRAT1_getxattr                     (char const *, char const *)
#define __NRAT2_getxattr                     (void *, void *)
#define __NRAT3_getxattr                     (size_t, __size_t)
#define __NRAT0_lgetxattr                    (char const *, char const *)
#define __NRAT1_lgetxattr                    (char const *, char const *)
#define __NRAT2_lgetxattr                    (void *, void *)
#define __NRAT3_lgetxattr                    (size_t, __size_t)
#define __NRAT0_fgetxattr                    (fd_t, __fd_t)
#define __NRAT1_fgetxattr                    (char const *, char const *)
#define __NRAT2_fgetxattr                    (void *, void *)
#define __NRAT3_fgetxattr                    (size_t, __size_t)
#define __NRAT0_listxattr                    (char const *, char const *)
#define __NRAT1_listxattr                    (char *, char *)
#define __NRAT2_listxattr                    (size_t, __size_t)
#define __NRAT0_llistxattr                   (char const *, char const *)
#define __NRAT1_llistxattr                   (char *, char *)
#define __NRAT2_llistxattr                   (size_t, __size_t)
#define __NRAT0_flistxattr                   (fd_t, __fd_t)
#define __NRAT1_flistxattr                   (char *, char *)
#define __NRAT2_flistxattr                   (size_t, __size_t)
#define __NRAT0_removexattr                  (char const *, char const *)
#define __NRAT1_removexattr                  (char const *, char const *)
#define __NRAT0_lremovexattr                 (char const *, char const *)
#define __NRAT1_lremovexattr                 (char const *, char const *)
#define __NRAT0_fremovexattr                 (fd_t, __fd_t)
#define __NRAT1_fremovexattr                 (char const *, char const *)
#define __NRAT0_tkill                        (pid_t, __pid_t)
#define __NRAT1_tkill                        (signo_t, __signo_t)
#define __NRAT0_sendfile64                   (fd_t, __fd_t)
#define __NRAT1_sendfile64                   (fd_t, __fd_t)
#define __NRAT2_sendfile64                   (__ULONG64_TYPE__ *, __ULONG64_TYPE__ *)
#define __NRAT3_sendfile64                   (size_t, __size_t)
#define __NRAT0_futex                        (uint32_t *, __uint32_t *)
#define __NRAT1_futex                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_futex                        (uint32_t, __uint32_t)
#define __NRAT3_futex                        (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT4_futex                        (uint32_t *, __uint32_t *)
#define __NRAT5_futex                        (uint32_t, __uint32_t)
#define __NRAT0_sched_setaffinity            (pid_t, __pid_t)
#define __NRAT1_sched_setaffinity            (size_t, __size_t)
#define __NRAT2_sched_setaffinity            (struct __cpu_set_struct const *, struct __cpu_set_struct const *)
#define __NRAT0_sched_getaffinity            (pid_t, __pid_t)
#define __NRAT1_sched_getaffinity            (size_t, __size_t)
#define __NRAT2_sched_getaffinity            (struct __cpu_set_struct *, struct __cpu_set_struct *)
#define __NRAT0_set_thread_area              (int, int)
#define __NRAT0_get_thread_area              (int, int)
#define __NRAT0_io_setup                     (int, int)
#define __NRAT0_io_destroy                   (int, int)
#define __NRAT0_io_getevents                 (int, int)
#define __NRAT0_io_submit                    (int, int)
#define __NRAT0_io_cancel                    (int, int)
#define __NRAT0_fadvise64                    (int, int)
#define __NRAT0_exit_group                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_lookup_dcookie               (int, int)
#define __NRAT0_epoll_create                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_epoll_ctl                    (fd_t, __fd_t)
#define __NRAT1_epoll_ctl                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_epoll_ctl                    (fd_t, __fd_t)
#define __NRAT3_epoll_ctl                    (struct epoll_event *, struct epoll_event *)
#define __NRAT0_epoll_wait                   (fd_t, __fd_t)
#define __NRAT1_epoll_wait                   (struct epoll_event *, struct epoll_event *)
#define __NRAT2_epoll_wait                   (size_t, __size_t)
#define __NRAT3_epoll_wait                   (syscall_slong_t, __syscall_slong_t)
#define __NRAT0_remap_file_pages             (void *, void *)
#define __NRAT1_remap_file_pages             (size_t, __size_t)
#define __NRAT2_remap_file_pages             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_remap_file_pages             (size_t, __size_t)
#define __NRAT4_remap_file_pages             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_set_tid_address              (pid_t *, __pid_t *)
#define __NRAT0_timer_create                 (clockid_t, __clockid_t)
#define __NRAT1_timer_create                 (struct sigevent *, struct sigevent *)
#define __NRAT2_timer_create                 (timer_t *, __timer_t *)
#define __NRAT0_timer_settime                (timer_t, __timer_t)
#define __NRAT1_timer_settime                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_timer_settime                (struct itimerspecx32 const *, struct __itimerspecx32 const *)
#define __NRAT3_timer_settime                (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NRAT0_timer_gettime                (timer_t, __timer_t)
#define __NRAT1_timer_gettime                (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NRAT0_timer_getoverrun             (timer_t, __timer_t)
#define __NRAT0_timer_delete                 (timer_t, __timer_t)
#define __NRAT0_clock_settime                (clockid_t, __clockid_t)
#define __NRAT1_clock_settime                (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT0_clock_gettime                (clockid_t, __clockid_t)
#define __NRAT1_clock_gettime                (struct timespecx32 *, struct __timespecx32 *)
#define __NRAT0_clock_getres                 (clockid_t, __clockid_t)
#define __NRAT1_clock_getres                 (struct timespecx32 *, struct __timespecx32 *)
#define __NRAT0_clock_nanosleep              (clockid_t, __clockid_t)
#define __NRAT1_clock_nanosleep              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_clock_nanosleep              (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT3_clock_nanosleep              (struct timespecx32 *, struct __timespecx32 *)
#define __NRAT0_statfs64                     (char const *, char const *)
#define __NRAT1_statfs64                     (struct statfsx32_64 *, struct __statfsx32_64 *)
#define __NRAT0_fstatfs64                    (fd_t, __fd_t)
#define __NRAT1_fstatfs64                    (struct statfsx32_64 *, struct __statfsx32_64 *)
#define __NRAT0_tgkill                       (pid_t, __pid_t)
#define __NRAT1_tgkill                       (pid_t, __pid_t)
#define __NRAT2_tgkill                       (signo_t, __signo_t)
#define __NRAT0_utimes                       (char const *, char const *)
#define __NRAT1_utimes                       (struct timevalx32 const *, struct __timevalx32 const *)
#define __NRAT0_fadvise64_64                 (int, int)
#define __NRAT0_mbind                        (int, int)
#define __NRAT0_get_mempolicy                (int, int)
#define __NRAT0_set_mempolicy                (int, int)
#define __NRAT0_mq_open                      (char const *, char const *)
#define __NRAT1_mq_open                      (oflag_t, __oflag_t)
#define __NRAT2_mq_open                      (mode_t, __mode_t)
#define __NRAT0_mq_unlink                    (char const *, char const *)
#define __NRAT0_mq_timedsend                 (fd_t, __fd_t)
#define __NRAT1_mq_timedsend                 (char const *, char const *)
#define __NRAT2_mq_timedsend                 (size_t, __size_t)
#define __NRAT3_mq_timedsend                 (uint32_t, __uint32_t)
#define __NRAT4_mq_timedsend                 (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT0_mq_timedreceive              (fd_t, __fd_t)
#define __NRAT1_mq_timedreceive              (char *, char *)
#define __NRAT2_mq_timedreceive              (size_t, __size_t)
#define __NRAT3_mq_timedreceive              (uint32_t *, __uint32_t *)
#define __NRAT4_mq_timedreceive              (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT0_mq_notify                    (fd_t, __fd_t)
#define __NRAT1_mq_notify                    (struct sigevent const *, struct sigevent const *)
#define __NRAT0_mq_getsetattr                (fd_t, __fd_t)
#define __NRAT1_mq_getsetattr                (struct mq_attr const *, struct mq_attr const *)
#define __NRAT2_mq_getsetattr                (struct mq_attr *, struct mq_attr *)
#define __NRAT0_kexec_load                   (int, int)
#define __NRAT0_waitid                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_waitid                       (id_t, __id_t)
#define __NRAT2_waitid                       (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NRAT3_waitid                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_waitid                       (struct rusagex32 *, struct __rusagex32 *)
#define __NRAT0_add_key                      (int, int)
#define __NRAT0_request_key                  (int, int)
#define __NRAT0_keyctl                       (int, int)
#define __NRAT0_ioprio_set                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_ioprio_set                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_ioprio_set                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_ioprio_get                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_ioprio_get                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_inotify_add_watch            (fd_t, __fd_t)
#define __NRAT1_inotify_add_watch            (char const *, char const *)
#define __NRAT2_inotify_add_watch            (uint32_t, __uint32_t)
#define __NRAT0_inotify_rm_watch             (fd_t, __fd_t)
#define __NRAT1_inotify_rm_watch             (int, int)
#define __NRAT0_migrate_pages                (int, int)
#define __NRAT0_openat                       (fd_t, __fd_t)
#define __NRAT1_openat                       (char const *, char const *)
#define __NRAT2_openat                       (oflag_t, __oflag_t)
#define __NRAT3_openat                       (mode_t, __mode_t)
#define __NRAT0_mkdirat                      (fd_t, __fd_t)
#define __NRAT1_mkdirat                      (char const *, char const *)
#define __NRAT2_mkdirat                      (mode_t, __mode_t)
#define __NRAT0_mknodat                      (fd_t, __fd_t)
#define __NRAT1_mknodat                      (char const *, char const *)
#define __NRAT2_mknodat                      (mode_t, __mode_t)
#define __NRAT3_mknodat                      (dev_t, __dev_t)
#define __NRAT0_fchownat                     (fd_t, __fd_t)
#define __NRAT1_fchownat                     (char const *, char const *)
#define __NRAT2_fchownat                     (uid_t, __uid_t)
#define __NRAT3_fchownat                     (gid_t, __gid_t)
#define __NRAT4_fchownat                     (atflag_t, __atflag_t)
#define __NRAT0_futimesat                    (fd_t, __fd_t)
#define __NRAT1_futimesat                    (char const *, char const *)
#define __NRAT2_futimesat                    (struct timevalx32 const *, struct __timevalx32 const *)
#define __NRAT0_fstatat64                    (fd_t, __fd_t)
#define __NRAT1_fstatat64                    (char const *, char const *)
#define __NRAT2_fstatat64                    (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NRAT3_fstatat64                    (atflag_t, __atflag_t)
#define __NRAT0_unlinkat                     (fd_t, __fd_t)
#define __NRAT1_unlinkat                     (char const *, char const *)
#define __NRAT2_unlinkat                     (atflag_t, __atflag_t)
#define __NRAT0_renameat                     (fd_t, __fd_t)
#define __NRAT1_renameat                     (char const *, char const *)
#define __NRAT2_renameat                     (fd_t, __fd_t)
#define __NRAT3_renameat                     (char const *, char const *)
#define __NRAT0_linkat                       (fd_t, __fd_t)
#define __NRAT1_linkat                       (char const *, char const *)
#define __NRAT2_linkat                       (fd_t, __fd_t)
#define __NRAT3_linkat                       (char const *, char const *)
#define __NRAT4_linkat                       (atflag_t, __atflag_t)
#define __NRAT0_symlinkat                    (char const *, char const *)
#define __NRAT1_symlinkat                    (fd_t, __fd_t)
#define __NRAT2_symlinkat                    (char const *, char const *)
#define __NRAT0_readlinkat                   (fd_t, __fd_t)
#define __NRAT1_readlinkat                   (char const *, char const *)
#define __NRAT2_readlinkat                   (char *, char *)
#define __NRAT3_readlinkat                   (size_t, __size_t)
#define __NRAT0_fchmodat                     (fd_t, __fd_t)
#define __NRAT1_fchmodat                     (char const *, char const *)
#define __NRAT2_fchmodat                     (mode_t, __mode_t)
#define __NRAT3_fchmodat                     (atflag_t, __atflag_t)
#define __NRAT0_faccessat                    (fd_t, __fd_t)
#define __NRAT1_faccessat                    (char const *, char const *)
#define __NRAT2_faccessat                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_pselect6                     (size_t, __size_t)
#define __NRAT1_pselect6                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT2_pselect6                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT3_pselect6                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT4_pselect6                     (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT5_pselect6                     (struct __sigset_with_sizex32 const *, struct __sigset_with_sizex32 const *)
#define __NRAT0_ppoll                        (struct pollfd *, struct pollfd *)
#define __NRAT1_ppoll                        (size_t, __size_t)
#define __NRAT2_ppoll                        (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT3_ppoll                        (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT4_ppoll                        (size_t, __size_t)
#define __NRAT0_unshare                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_set_robust_list              (int, int)
#define __NRAT0_get_robust_list              (int, int)
#define __NRAT0_splice                       (fd_t, __fd_t)
#define __NRAT1_splice                       (uint64_t *, __uint64_t *)
#define __NRAT2_splice                       (fd_t, __fd_t)
#define __NRAT3_splice                       (uint64_t *, __uint64_t *)
#define __NRAT4_splice                       (size_t, __size_t)
#define __NRAT5_splice                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sync_file_range              (fd_t, __fd_t)
#define __NRAT1_sync_file_range              (uint64_t, __uint64_t)
#define __NRAT2_sync_file_range              (uint64_t, __uint64_t)
#define __NRAT3_sync_file_range              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_tee                          (fd_t, __fd_t)
#define __NRAT1_tee                          (fd_t, __fd_t)
#define __NRAT2_tee                          (size_t, __size_t)
#define __NRAT3_tee                          (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_vmsplice                     (fd_t, __fd_t)
#define __NRAT1_vmsplice                     (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_vmsplice                     (size_t, __size_t)
#define __NRAT3_vmsplice                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_move_pages                   (int, int)
#define __NRAT0_getcpu                       (uint32_t *, __uint32_t *)
#define __NRAT1_getcpu                       (uint32_t *, __uint32_t *)
#define __NRAT2_getcpu                       (struct getcpu_cache *, struct getcpu_cache *)
#define __NRAT0_epoll_pwait                  (fd_t, __fd_t)
#define __NRAT1_epoll_pwait                  (struct epoll_event *, struct epoll_event *)
#define __NRAT2_epoll_pwait                  (size_t, __size_t)
#define __NRAT3_epoll_pwait                  (syscall_slong_t, __syscall_slong_t)
#define __NRAT4_epoll_pwait                  (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT5_epoll_pwait                  (size_t, __size_t)
#define __NRAT0_utimensat                    (fd_t, __fd_t)
#define __NRAT1_utimensat                    (char const *, char const *)
#define __NRAT2_utimensat                    (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT3_utimensat                    (atflag_t, __atflag_t)
#define __NRAT0_signalfd                     (fd_t, __fd_t)
#define __NRAT1_signalfd                     (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT2_signalfd                     (size_t, __size_t)
#define __NRAT0_timerfd_create               (clockid_t, __clockid_t)
#define __NRAT1_timerfd_create               (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_eventfd                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_fallocate                    (fd_t, __fd_t)
#define __NRAT1_fallocate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_fallocate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_fallocate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_timerfd_settime              (fd_t, __fd_t)
#define __NRAT1_timerfd_settime              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_timerfd_settime              (struct itimerspecx32 const *, struct __itimerspecx32 const *)
#define __NRAT3_timerfd_settime              (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NRAT0_timerfd_gettime              (fd_t, __fd_t)
#define __NRAT1_timerfd_gettime              (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NRAT0_signalfd4                    (fd_t, __fd_t)
#define __NRAT1_signalfd4                    (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT2_signalfd4                    (size_t, __size_t)
#define __NRAT3_signalfd4                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_eventfd2                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_eventfd2                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_epoll_create1                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_dup3                         (fd_t, __fd_t)
#define __NRAT1_dup3                         (fd_t, __fd_t)
#define __NRAT2_dup3                         (oflag_t, __oflag_t)
#define __NRAT0_pipe2                        (fd_t *, __fd_t *)
#define __NRAT1_pipe2                        (oflag_t, __oflag_t)
#define __NRAT0_inotify_init1                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_preadv                       (fd_t, __fd_t)
#define __NRAT1_preadv                       (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_preadv                       (size_t, __size_t)
#define __NRAT3_preadv                       (uint64_t, __uint64_t)
#define __NRAT0_pwritev                      (fd_t, __fd_t)
#define __NRAT1_pwritev                      (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_pwritev                      (size_t, __size_t)
#define __NRAT3_pwritev                      (uint64_t, __uint64_t)
#define __NRAT0_rt_tgsigqueueinfo            (pid_t, __pid_t)
#define __NRAT1_rt_tgsigqueueinfo            (pid_t, __pid_t)
#define __NRAT2_rt_tgsigqueueinfo            (signo_t, __signo_t)
#define __NRAT3_rt_tgsigqueueinfo            (struct __siginfox32_struct const *, struct __siginfox32_struct const *)
#define __NRAT0_perf_event_open              (int, int)
#define __NRAT0_recvmmsg                     (fd_t, __fd_t)
#define __NRAT1_recvmmsg                     (struct mmsghdrx32 *, struct __mmsghdrx32 *)
#define __NRAT2_recvmmsg                     (size_t, __size_t)
#define __NRAT3_recvmmsg                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_recvmmsg                     (struct timespecx32 const *, struct __timespecx32 const *)
#define __NRAT0_fanotify_init                (int, int)
#define __NRAT0_fanotify_mark                (int, int)
#define __NRAT0_prlimit64                    (pid_t, __pid_t)
#define __NRAT1_prlimit64                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_prlimit64                    (struct rlimitx32_64 const *, struct __rlimitx32_64 const *)
#define __NRAT3_prlimit64                    (struct rlimitx32_64 *, struct __rlimitx32_64 *)
#define __NRAT0_name_to_handle_at            (fd_t, __fd_t)
#define __NRAT1_name_to_handle_at            (char const *, char const *)
#define __NRAT2_name_to_handle_at            (struct file_handle *, struct file_handle *)
#define __NRAT3_name_to_handle_at            (int32_t *, __int32_t *)
#define __NRAT4_name_to_handle_at            (atflag_t, __atflag_t)
#define __NRAT0_open_by_handle_at            (fd_t, __fd_t)
#define __NRAT1_open_by_handle_at            (struct file_handle const *, struct file_handle const *)
#define __NRAT2_open_by_handle_at            (oflag_t, __oflag_t)
#define __NRAT0_clock_adjtime                (int, int)
#define __NRAT0_syncfs                       (fd_t, __fd_t)
#define __NRAT0_sendmmsg                     (fd_t, __fd_t)
#define __NRAT1_sendmmsg                     (struct mmsghdrx32 *, struct __mmsghdrx32 *)
#define __NRAT2_sendmmsg                     (size_t, __size_t)
#define __NRAT3_sendmmsg                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_setns                        (fd_t, __fd_t)
#define __NRAT1_setns                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_process_vm_readv             (pid_t, __pid_t)
#define __NRAT1_process_vm_readv             (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_process_vm_readv             (size_t, __size_t)
#define __NRAT3_process_vm_readv             (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT4_process_vm_readv             (size_t, __size_t)
#define __NRAT5_process_vm_readv             (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_process_vm_writev            (pid_t, __pid_t)
#define __NRAT1_process_vm_writev            (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_process_vm_writev            (size_t, __size_t)
#define __NRAT3_process_vm_writev            (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT4_process_vm_writev            (size_t, __size_t)
#define __NRAT5_process_vm_writev            (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_kcmp                         (pid_t, __pid_t)
#define __NRAT1_kcmp                         (pid_t, __pid_t)
#define __NRAT2_kcmp                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_kcmp                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_kcmp                         (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_finit_module                 (fd_t, __fd_t)
#define __NRAT1_finit_module                 (char const *, char const *)
#define __NRAT2_finit_module                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_sched_setattr                (int, int)
#define __NRAT0_sched_getattr                (int, int)
#define __NRAT0_renameat2                    (fd_t, __fd_t)
#define __NRAT1_renameat2                    (char const *, char const *)
#define __NRAT2_renameat2                    (fd_t, __fd_t)
#define __NRAT3_renameat2                    (char const *, char const *)
#define __NRAT4_renameat2                    (atflag_t, __atflag_t)
#define __NRAT0_seccomp                      (int, int)
#define __NRAT0_getrandom                    (void *, void *)
#define __NRAT1_getrandom                    (size_t, __size_t)
#define __NRAT2_getrandom                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_memfd_create                 (char const *, char const *)
#define __NRAT1_memfd_create                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_bpf                          (int, int)
#define __NRAT0_execveat                     (fd_t, __fd_t)
#define __NRAT1_execveat                     (char const *, char const *)
#define __NRAT2_execveat                     (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NRAT3_execveat                     (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NRAT4_execveat                     (atflag_t, __atflag_t)
#define __NRAT0_socket                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_socket                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_socket                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_socketpair                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_socketpair                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_socketpair                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_socketpair                   (fd_t *, __fd_t *)
#define __NRAT0_bind                         (fd_t, __fd_t)
#define __NRAT1_bind                         (struct sockaddr const *, struct sockaddr const *)
#define __NRAT2_bind                         (socklen_t, __socklen_t)
#define __NRAT0_connect                      (fd_t, __fd_t)
#define __NRAT1_connect                      (struct sockaddr const *, struct sockaddr const *)
#define __NRAT2_connect                      (socklen_t, __socklen_t)
#define __NRAT0_listen                       (fd_t, __fd_t)
#define __NRAT1_listen                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_accept4                      (fd_t, __fd_t)
#define __NRAT1_accept4                      (struct sockaddr *, struct sockaddr *)
#define __NRAT2_accept4                      (socklen_t *, __socklen_t *)
#define __NRAT3_accept4                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_getsockopt                   (fd_t, __fd_t)
#define __NRAT1_getsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_getsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_getsockopt                   (void *, void *)
#define __NRAT4_getsockopt                   (socklen_t *, __socklen_t *)
#define __NRAT0_setsockopt                   (fd_t, __fd_t)
#define __NRAT1_setsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_setsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_setsockopt                   (void const *, void const *)
#define __NRAT4_setsockopt                   (socklen_t, __socklen_t)
#define __NRAT0_getsockname                  (fd_t, __fd_t)
#define __NRAT1_getsockname                  (struct sockaddr *, struct sockaddr *)
#define __NRAT2_getsockname                  (socklen_t *, __socklen_t *)
#define __NRAT0_getpeername                  (fd_t, __fd_t)
#define __NRAT1_getpeername                  (struct sockaddr *, struct sockaddr *)
#define __NRAT2_getpeername                  (socklen_t *, __socklen_t *)
#define __NRAT0_sendto                       (fd_t, __fd_t)
#define __NRAT1_sendto                       (void const *, void const *)
#define __NRAT2_sendto                       (size_t, __size_t)
#define __NRAT3_sendto                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_sendto                       (struct sockaddr const *, struct sockaddr const *)
#define __NRAT5_sendto                       (socklen_t, __socklen_t)
#define __NRAT0_sendmsg                      (fd_t, __fd_t)
#define __NRAT1_sendmsg                      (struct msghdrx32 const *, struct __msghdrx32 const *)
#define __NRAT2_sendmsg                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_recvfrom                     (fd_t, __fd_t)
#define __NRAT1_recvfrom                     (void *, void *)
#define __NRAT2_recvfrom                     (size_t, __size_t)
#define __NRAT3_recvfrom                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_recvfrom                     (struct sockaddr *, struct sockaddr *)
#define __NRAT5_recvfrom                     (socklen_t *, __socklen_t *)
#define __NRAT0_recvmsg                      (fd_t, __fd_t)
#define __NRAT1_recvmsg                      (struct msghdrx32 *, struct __msghdrx32 *)
#define __NRAT2_recvmsg                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_shutdown                     (fd_t, __fd_t)
#define __NRAT1_shutdown                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_userfaultfd                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_membarrier                   (int, int)
#define __NRAT0_mlock2                       (void const *, void const *)
#define __NRAT1_mlock2                       (size_t, __size_t)
#define __NRAT2_mlock2                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_copy_file_range              (int, int)
#define __NRAT0_preadv2                      (int, int)
#define __NRAT0_pwritev2                     (int, int)
#define __NRAT0_pkey_mprotect                (void *, void *)
#define __NRAT1_pkey_mprotect                (size_t, __size_t)
#define __NRAT2_pkey_mprotect                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_pkey_mprotect                (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_pkey_alloc                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_pkey_alloc                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_pkey_free                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_statx                        (int, int)
#define __NRAT0_arch_prctl                   (unsigned int, unsigned int)
#define __NRAT1_arch_prctl                   (uint32_t *, __uint32_t *)
#define __NRAT0_io_pgetevents                (int, int)
#define __NRAT0_rseq                         (int, int)
#define __NRAT0_semget                       (int, int)
#define __NRAT0_semctl                       (int, int)
#define __NRAT0_shmget                       (key_t, __key_t)
#define __NRAT1_shmget                       (size_t, __size_t)
#define __NRAT2_shmget                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_shmctl                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_shmctl                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_shmctl                       (struct shmid_ds *, struct shmid_ds *)
#define __NRAT0_shmat                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_shmat                        (void const *, void const *)
#define __NRAT2_shmat                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_shmdt                        (void const *, void const *)
#define __NRAT0_msgget                       (int, int)
#define __NRAT0_msgsnd                       (int, int)
#define __NRAT0_msgrcv                       (int, int)
#define __NRAT0_msgctl                       (int, int)
#define __NRAT0_clock_gettime64              (clockid_t, __clockid_t)
#define __NRAT1_clock_gettime64              (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NRAT0_clock_settime64              (clockid_t, __clockid_t)
#define __NRAT1_clock_settime64              (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT0_clock_adjtime64              (int, int)
#define __NRAT0_clock_getres_time64          (clockid_t, __clockid_t)
#define __NRAT1_clock_getres_time64          (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NRAT0_clock_nanosleep_time64       (clockid_t, __clockid_t)
#define __NRAT1_clock_nanosleep_time64       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_clock_nanosleep_time64       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT3_clock_nanosleep_time64       (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NRAT0_timer_gettime64              (timer_t, __timer_t)
#define __NRAT1_timer_gettime64              (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NRAT0_timer_settime64              (timer_t, __timer_t)
#define __NRAT1_timer_settime64              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_timer_settime64              (struct itimerspecx32_64 const *, struct __itimerspecx32_64 const *)
#define __NRAT3_timer_settime64              (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NRAT0_timerfd_gettime64            (fd_t, __fd_t)
#define __NRAT1_timerfd_gettime64            (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NRAT0_timerfd_settime64            (fd_t, __fd_t)
#define __NRAT1_timerfd_settime64            (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_timerfd_settime64            (struct itimerspecx32_64 const *, struct __itimerspecx32_64 const *)
#define __NRAT3_timerfd_settime64            (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NRAT0_utimensat_time64             (fd_t, __fd_t)
#define __NRAT1_utimensat_time64             (char const *, char const *)
#define __NRAT2_utimensat_time64             (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT3_utimensat_time64             (atflag_t, __atflag_t)
#define __NRAT0_pselect6_time64              (size_t, __size_t)
#define __NRAT1_pselect6_time64              (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT2_pselect6_time64              (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT3_pselect6_time64              (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT4_pselect6_time64              (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT5_pselect6_time64              (struct __sigset_with_sizex32 const *, struct __sigset_with_sizex32 const *)
#define __NRAT0_ppoll_time64                 (struct pollfd *, struct pollfd *)
#define __NRAT1_ppoll_time64                 (size_t, __size_t)
#define __NRAT2_ppoll_time64                 (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT3_ppoll_time64                 (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT4_ppoll_time64                 (size_t, __size_t)
#define __NRAT0_io_pgetevents_time64         (int, int)
#define __NRAT0_recvmmsg_time64              (fd_t, __fd_t)
#define __NRAT1_recvmmsg_time64              (struct mmsghdrx32 *, struct __mmsghdrx32 *)
#define __NRAT2_recvmmsg_time64              (size_t, __size_t)
#define __NRAT3_recvmmsg_time64              (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_recvmmsg_time64              (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT0_mq_timedsend_time64          (fd_t, __fd_t)
#define __NRAT1_mq_timedsend_time64          (char const *, char const *)
#define __NRAT2_mq_timedsend_time64          (size_t, __size_t)
#define __NRAT3_mq_timedsend_time64          (uint32_t, __uint32_t)
#define __NRAT4_mq_timedsend_time64          (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT0_mq_timedreceive_time64       (fd_t, __fd_t)
#define __NRAT1_mq_timedreceive_time64       (char *, char *)
#define __NRAT2_mq_timedreceive_time64       (size_t, __size_t)
#define __NRAT3_mq_timedreceive_time64       (uint32_t *, __uint32_t *)
#define __NRAT4_mq_timedreceive_time64       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT0_semtimedop_time64            (int, int)
#define __NRAT0_rt_sigtimedwait_time64       (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NRAT1_rt_sigtimedwait_time64       (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NRAT2_rt_sigtimedwait_time64       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT3_rt_sigtimedwait_time64       (size_t, __size_t)
#define __NRAT0_futex_time64                 (uint32_t *, __uint32_t *)
#define __NRAT1_futex_time64                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_futex_time64                 (uint32_t, __uint32_t)
#define __NRAT3_futex_time64                 (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT4_futex_time64                 (uint32_t *, __uint32_t *)
#define __NRAT5_futex_time64                 (uint32_t, __uint32_t)
#define __NRAT0_sched_rr_get_interval_time64 (pid_t, __pid_t)
#define __NRAT1_sched_rr_get_interval_time64 (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NRAT0_pidfd_send_signal            (fd_t, __fd_t)
#define __NRAT1_pidfd_send_signal            (signo_t, __signo_t)
#define __NRAT2_pidfd_send_signal            (struct __siginfox32_struct const *, struct __siginfox32_struct const *)
#define __NRAT3_pidfd_send_signal            (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_io_uring_setup               (int, int)
#define __NRAT0_io_uring_enter               (int, int)
#define __NRAT0_io_uring_register            (int, int)
#define __NRAT0_open_tree                    (int, int)
#define __NRAT0_move_mount                   (int, int)
#define __NRAT0_fsopen                       (int, int)
#define __NRAT0_fsconfig                     (int, int)
#define __NRAT0_fsmount                      (int, int)
#define __NRAT0_fspick                       (int, int)
#define __NRAT0_pidfd_open                   (pid_t, __pid_t)
#define __NRAT1_pidfd_open                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_clone3                       (struct clone_args *, struct clone_args *)
#define __NRAT1_clone3                       (size_t, __size_t)
#define __NRAT0_close_range                  (unsigned int, unsigned int)
#define __NRAT1_close_range                  (unsigned int, unsigned int)
#define __NRAT2_close_range                  (unsigned int, unsigned int)
#define __NRAT0_openat2                      (int, int)
#define __NRAT0_pidfd_getfd                  (fd_t, __fd_t)
#define __NRAT1_pidfd_getfd                  (fd_t, __fd_t)
#define __NRAT2_pidfd_getfd                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_faccessat2                   (fd_t, __fd_t)
#define __NRAT1_faccessat2                   (char const *, char const *)
#define __NRAT2_faccessat2                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_faccessat2                   (atflag_t, __atflag_t)
#define __NRAT0_pwritevf                     (fd_t, __fd_t)
#define __NRAT1_pwritevf                     (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_pwritevf                     (size_t, __size_t)
#define __NRAT3_pwritevf                     (uint64_t, __uint64_t)
#define __NRAT4_pwritevf                     (iomode_t, __iomode_t)
#define __NRAT0_preadvf                      (fd_t, __fd_t)
#define __NRAT1_preadvf                      (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_preadvf                      (size_t, __size_t)
#define __NRAT3_preadvf                      (uint64_t, __uint64_t)
#define __NRAT4_preadvf                      (iomode_t, __iomode_t)
#define __NRAT0_fallocate64                  (fd_t, __fd_t)
#define __NRAT1_fallocate64                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_fallocate64                  (uint64_t, __uint64_t)
#define __NRAT3_fallocate64                  (uint64_t, __uint64_t)
#define __NRAT0_freadlinkat                  (fd_t, __fd_t)
#define __NRAT1_freadlinkat                  (char const *, char const *)
#define __NRAT2_freadlinkat                  (char *, char *)
#define __NRAT3_freadlinkat                  (size_t, __size_t)
#define __NRAT4_freadlinkat                  (atflag_t, __atflag_t)
#define __NRAT0_fsymlinkat                   (char const *, char const *)
#define __NRAT1_fsymlinkat                   (fd_t, __fd_t)
#define __NRAT2_fsymlinkat                   (char const *, char const *)
#define __NRAT3_fsymlinkat                   (atflag_t, __atflag_t)
#define __NRAT0_kfstatat                     (fd_t, __fd_t)
#define __NRAT1_kfstatat                     (char const *, char const *)
#define __NRAT2_kfstatat                     (struct __kos_stat *, struct __kos_stat *)
#define __NRAT3_kfstatat                     (atflag_t, __atflag_t)
#define __NRAT0_futimesat64                  (fd_t, __fd_t)
#define __NRAT1_futimesat64                  (char const *, char const *)
#define __NRAT2_futimesat64                  (struct timevalx32_64 const *, struct __timevalx32_64 const *)
#define __NRAT0_fmknodat                     (fd_t, __fd_t)
#define __NRAT1_fmknodat                     (char const *, char const *)
#define __NRAT2_fmknodat                     (mode_t, __mode_t)
#define __NRAT3_fmknodat                     (dev_t, __dev_t)
#define __NRAT4_fmknodat                     (atflag_t, __atflag_t)
#define __NRAT0_fmkdirat                     (fd_t, __fd_t)
#define __NRAT1_fmkdirat                     (char const *, char const *)
#define __NRAT2_fmkdirat                     (mode_t, __mode_t)
#define __NRAT3_fmkdirat                     (atflag_t, __atflag_t)
#define __NRAT0_inotify_add_watch_at         (fd_t, __fd_t)
#define __NRAT1_inotify_add_watch_at         (fd_t, __fd_t)
#define __NRAT2_inotify_add_watch_at         (char const *, char const *)
#define __NRAT3_inotify_add_watch_at         (atflag_t, __atflag_t)
#define __NRAT4_inotify_add_watch_at         (uint32_t, __uint32_t)
#define __NRAT0_waitid64                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_waitid64                     (id_t, __id_t)
#define __NRAT2_waitid64                     (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NRAT3_waitid64                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_waitid64                     (struct rusagex32_64 *, struct __rusagex32_64 *)
#define __NRAT0_utimes64                     (char const *, char const *)
#define __NRAT1_utimes64                     (struct timevalx32_64 const *, struct __timevalx32_64 const *)
#define __NRAT0_set_userprocmask_address     (struct userprocmask *, struct userprocmask *)
#define __NRAT0_lfutexexpr                   (uint32_t *, __uint32_t *)
#define __NRAT1_lfutexexpr                   (void *, void *)
#define __NRAT2_lfutexexpr                   (struct lfutexexprx32 const *, struct lfutexexprx32 const *)
#define __NRAT3_lfutexexpr                   (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT4_lfutexexpr                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_lfutex                       (uint32_t *, __uint32_t *)
#define __NRAT1_lfutex                       (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_lfutex                       (uint32_t, __uint32_t)
#define __NRAT3_lfutex                       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT4_lfutex                       (uint32_t, __uint32_t)
#define __NRAT0_kreaddirf                    (fd_t, __fd_t)
#define __NRAT1_kreaddirf                    (struct dirent *, struct dirent *)
#define __NRAT2_kreaddirf                    (size_t, __size_t)
#define __NRAT3_kreaddirf                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT4_kreaddirf                    (iomode_t, __iomode_t)
#define __NRAT0_kreaddir                     (fd_t, __fd_t)
#define __NRAT1_kreaddir                     (struct dirent *, struct dirent *)
#define __NRAT2_kreaddir                     (size_t, __size_t)
#define __NRAT3_kreaddir                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_kfstat                       (fd_t, __fd_t)
#define __NRAT1_kfstat                       (struct __kos_stat *, struct __kos_stat *)
#define __NRAT0_klstat                       (char const *, char const *)
#define __NRAT1_klstat                       (struct __kos_stat *, struct __kos_stat *)
#define __NRAT0_kstat                        (char const *, char const *)
#define __NRAT1_kstat                        (struct __kos_stat *, struct __kos_stat *)
#define __NRAT0_pwrite64f                    (fd_t, __fd_t)
#define __NRAT1_pwrite64f                    (void const *, void const *)
#define __NRAT2_pwrite64f                    (size_t, __size_t)
#define __NRAT3_pwrite64f                    (uint64_t, __uint64_t)
#define __NRAT4_pwrite64f                    (iomode_t, __iomode_t)
#define __NRAT0_pread64f                     (fd_t, __fd_t)
#define __NRAT1_pread64f                     (void *, void *)
#define __NRAT2_pread64f                     (size_t, __size_t)
#define __NRAT3_pread64f                     (uint64_t, __uint64_t)
#define __NRAT4_pread64f                     (iomode_t, __iomode_t)
#define __NRAT0_ksigreturn                   (struct fpustate32 const *, struct fpustate32 const *)
#define __NRAT1_ksigreturn                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_ksigreturn                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_ksigreturn                   (struct __sigset_with_sizex32 const *, struct __sigset_with_sizex32 const *)
#define __NRAT4_ksigreturn                   (struct rpc_syscall_info32 const *, struct rpc_syscall_info32 const *)
#define __NRAT5_ksigreturn                   (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NRAT0_nanosleep64                  (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NRAT1_nanosleep64                  (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NRAT0_ksysctl                      (ioctl_t, __ioctl_t)
#define __NRAT1_ksysctl                      (void *, void *)
#define __NRAT0_writevf                      (fd_t, __fd_t)
#define __NRAT1_writevf                      (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_writevf                      (size_t, __size_t)
#define __NRAT3_writevf                      (iomode_t, __iomode_t)
#define __NRAT0_readvf                       (fd_t, __fd_t)
#define __NRAT1_readvf                       (struct iovecx32 const *, struct __iovecx32 const *)
#define __NRAT2_readvf                       (size_t, __size_t)
#define __NRAT3_readvf                       (iomode_t, __iomode_t)
#define __NRAT0_select64                     (size_t, __size_t)
#define __NRAT1_select64                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT2_select64                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT3_select64                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NRAT4_select64                     (struct timevalx32_64 *, struct __timevalx32_64 *)
#define __NRAT0_wait4_64                     (pid_t, __pid_t)
#define __NRAT1_wait4_64                     (int32_t *, __int32_t *)
#define __NRAT2_wait4_64                     (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT3_wait4_64                     (struct rusagex32_64 *, struct __rusagex32_64 *)
#define __NRAT0_getitimer64                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_getitimer64                  (struct __itimervalx32_64 *, struct __itimervalx32_64 *)
#define __NRAT0_setitimer64                  (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_setitimer64                  (struct __itimervalx32_64 const *, struct __itimervalx32_64 const *)
#define __NRAT2_setitimer64                  (struct __itimervalx32_64 *, struct __itimervalx32_64 *)
#define __NRAT0_maplibrary                   (void *, void *)
#define __NRAT1_maplibrary                   (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_maplibrary                   (fd_t, __fd_t)
#define __NRAT3_maplibrary                   (struct elf32_phdr const *, struct elf32_phdr const *)
#define __NRAT4_maplibrary                   (size_t, __size_t)
#define __NRAT0_settimeofday64               (struct timevalx32_64 const *, struct __timevalx32_64 const *)
#define __NRAT1_settimeofday64               (struct timezone const *, struct timezone const *)
#define __NRAT0_gettimeofday64               (struct timevalx32_64 *, struct __timevalx32_64 *)
#define __NRAT1_gettimeofday64               (struct timezone *, struct timezone *)
#define __NRAT0_getrusage64                  (syscall_slong_t, __syscall_slong_t)
#define __NRAT1_getrusage64                  (struct rusagex32_64 *, struct __rusagex32_64 *)
#define __NRAT0_fsmode                       (uint64_t, __uint64_t)
#define __NRAT0_ioctlf                       (fd_t, __fd_t)
#define __NRAT1_ioctlf                       (ioctl_t, __ioctl_t)
#define __NRAT2_ioctlf                       (iomode_t, __iomode_t)
#define __NRAT3_ioctlf                       (void *, void *)
#define __NRAT0_rtm_abort                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_ftime64                      (struct timebx32_64 *, struct __timebx32_64 *)
#define __NRAT0_utime64                      (char const *, char const *)
#define __NRAT1_utime64                      (struct utimbufx32_64 const *, struct __utimbufx32_64 const *)
#define __NRAT0_stime64                      (time64_t const *, __time64_t const *)
#define __NRAT0_userviofd                    (size_t, __size_t)
#define __NRAT1_userviofd                    (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_lseek64                      (fd_t, __fd_t)
#define __NRAT1_lseek64                      (int64_t, __int64_t)
#define __NRAT2_lseek64                      (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_coredump                     (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NRAT1_coredump                     (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NRAT2_coredump                     (__HYBRID_PTR32(void const) const *, __HYBRID_PTR32(void const) const *)
#define __NRAT3_coredump                     (size_t, __size_t)
#define __NRAT4_coredump                     (union coredump_info32 const *, union coredump_info32 const *)
#define __NRAT5_coredump                     (unwind_errno_t, unwind_errno_t)
#define __NRAT0_debugtrap                    (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NRAT1_debugtrap                    (struct debugtrap_reason32 const *, struct debugtrap_reason32 const *)
#define __NRAT0_get_exception_handler        (__ULONG32_TYPE__ *, __ULONG32_TYPE__ *)
#define __NRAT1_get_exception_handler        (__except_handler32_t *, __except_handler32_t *)
#define __NRAT2_get_exception_handler        (__HYBRID_PTR32(void) *, __HYBRID_PTR32(void) *)
#define __NRAT0_set_exception_handler        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT1_set_exception_handler        (except_handler_t, __except_handler_t)
#define __NRAT2_set_exception_handler        (void *, void *)
#define __NRAT0_mktty                        (char const *, char const *)
#define __NRAT1_mktty                        (fd_t, __fd_t)
#define __NRAT2_mktty                        (fd_t, __fd_t)
#define __NRAT3_mktty                        (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT0_time64                       (int64_t *, __int64_t *)
#define __NRAT0_fchdirat                     (fd_t, __fd_t)
#define __NRAT1_fchdirat                     (char const *, char const *)
#define __NRAT2_fchdirat                     (atflag_t, __atflag_t)
#define __NRAT0_openpty                      (fd_t *, __fd_t *)
#define __NRAT1_openpty                      (fd_t *, __fd_t *)
#define __NRAT2_openpty                      (char *, char *)
#define __NRAT3_openpty                      (struct termios const *, struct termios const *)
#define __NRAT4_openpty                      (struct winsize const *, struct winsize const *)
#define __NRAT0_rpc_schedule                 (pid_t, __pid_t)
#define __NRAT1_rpc_schedule                 (syscall_ulong_t, __syscall_ulong_t)
#define __NRAT2_rpc_schedule                 (void const *, void const *)
#define __NRAT3_rpc_schedule                 (__HYBRID_PTR32(void const) const *, __HYBRID_PTR32(void const) const *)
#define __NRAT4_rpc_schedule                 (size_t, __size_t)
#define __NRAT0_frealpathat                  (fd_t, __fd_t)
#define __NRAT1_frealpathat                  (char const *, char const *)
#define __NRAT2_frealpathat                  (char *, char *)
#define __NRAT3_frealpathat                  (size_t, __size_t)
#define __NRAT4_frealpathat                  (atflag_t, __atflag_t)
#define __NRAT0_detach                       (pid_t, __pid_t)
#define __NRAT0_frealpath4                   (fd_t, __fd_t)
#define __NRAT1_frealpath4                   (char *, char *)
#define __NRAT2_frealpath4                   (size_t, __size_t)
#define __NRAT3_frealpath4                   (atflag_t, __atflag_t)
#define __NRAT0_writef                       (fd_t, __fd_t)
#define __NRAT1_writef                       (void const *, void const *)
#define __NRAT2_writef                       (size_t, __size_t)
#define __NRAT3_writef                       (iomode_t, __iomode_t)
#define __NRAT0_readf                        (fd_t, __fd_t)
#define __NRAT1_readf                        (void *, void *)
#define __NRAT2_readf                        (size_t, __size_t)
#define __NRAT3_readf                        (iomode_t, __iomode_t)
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_TYPES */
#endif /* __WANT_SYSCALL_ARGUMENT_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT LIST MAKING                                         */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_MAKER
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NRAM_restart_syscall(a, b, c, d, e, f)              /* nothing */
#define __NRAM_exit(a, b, c, d, e, f)                         (__syscall_ulong_t)a
#define __NRAM_fork(a, b, c, d, e, f)                         /* nothing */
#define __NRAM_read(a, b, c, d, e, f)                         (__fd_t)a, (void *)b, (__size_t)c
#define __NRAM_write(a, b, c, d, e, f)                        (__fd_t)a, (void const *)b, (__size_t)c
#define __NRAM_open(a, b, c, d, e, f)                         (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NRAM_close(a, b, c, d, e, f)                        (__fd_t)a
#define __NRAM_waitpid(a, b, c, d, e, f)                      (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c
#define __NRAM_creat(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b
#define __NRAM_link(a, b, c, d, e, f)                         (char const *)a, (char const *)b
#define __NRAM_unlink(a, b, c, d, e, f)                       (char const *)a
#define __NRAM_execve(a, b, c, d, e, f)                       (char const *)a, (__HYBRID_PTR32(char const) const *)b, (__HYBRID_PTR32(char const) const *)c
#define __NRAM_chdir(a, b, c, d, e, f)                        (char const *)a
#define __NRAM_time(a, b, c, d, e, f)                         (__int32_t *)a
#define __NRAM_mknod(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b, (__dev_t)c
#define __NRAM_chmod(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b
#define __NRAM_lchown(a, b, c, d, e, f)                       (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_break(a, b, c, d, e, f)                        /* nothing */
#define __NRAM_oldstat(a, b, c, d, e, f)                      (char const *)a, (struct linux_oldstat *)b
#define __NRAM_lseek(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_slong_t)b, (__syscall_ulong_t)c
#define __NRAM_getpid(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_mount(a, b, c, d, e, f)                        (char const *)a, (char const *)b, (char const *)c, (__syscall_ulong_t)d, (void const *)e
#define __NRAM_umount(a, b, c, d, e, f)                       (char const *)a
#define __NRAM_setuid(a, b, c, d, e, f)                       (__uint16_t)a
#define __NRAM_getuid(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_stime(a, b, c, d, e, f)                        (__time32_t const *)a
#define __NRAM_ptrace(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__pid_t)b, (void *)c, (void *)d
#define __NRAM_alarm(a, b, c, d, e, f)                        (__syscall_ulong_t)a
#define __NRAM_oldfstat(a, b, c, d, e, f)                     (__fd_t)a, (struct linux_oldstat *)b
#define __NRAM_pause(a, b, c, d, e, f)                        /* nothing */
#define __NRAM_utime(a, b, c, d, e, f)                        (char const *)a, (struct __utimbufx32 const *)b
#define __NRAM_stty(a, b, c, d, e, f)                         /* nothing */
#define __NRAM_gtty(a, b, c, d, e, f)                         /* nothing */
#define __NRAM_access(a, b, c, d, e, f)                       (char const *)a, (__syscall_ulong_t)b
#define __NRAM_nice(a, b, c, d, e, f)                         (__syscall_slong_t)a
#define __NRAM_ftime(a, b, c, d, e, f)                        (struct __timebx32 *)a
#define __NRAM_sync(a, b, c, d, e, f)                         /* nothing */
#define __NRAM_kill(a, b, c, d, e, f)                         (__pid_t)a, (__signo_t)b
#define __NRAM_rename(a, b, c, d, e, f)                       (char const *)a, (char const *)b
#define __NRAM_mkdir(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b
#define __NRAM_rmdir(a, b, c, d, e, f)                        (char const *)a
#define __NRAM_dup(a, b, c, d, e, f)                          (__fd_t)a
#define __NRAM_pipe(a, b, c, d, e, f)                         (__fd_t *)a
#define __NRAM_times(a, b, c, d, e, f)                        (struct __tmsx32 *)a
#define __NRAM_prof(a, b, c, d, e, f)                         /* nothing */
#define __NRAM_brk(a, b, c, d, e, f)                          (void *)a
#define __NRAM_setgid(a, b, c, d, e, f)                       (__uint16_t)a
#define __NRAM_getgid(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_signal(a, b, c, d, e, f)                       (__signo_t)a, (__sigactionx32_sa_handler_t)b
#define __NRAM_geteuid(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_getegid(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_acct(a, b, c, d, e, f)                         (char const *)a
#define __NRAM_umount2(a, b, c, d, e, f)                      (char const *)a, (__syscall_ulong_t)b
#define __NRAM_lock(a, b, c, d, e, f)                         /* nothing */
#define __NRAM_ioctl(a, b, c, d, e, f)                        (__fd_t)a, (__ioctl_t)b, (void *)c
#define __NRAM_fcntl(a, b, c, d, e, f)                        (__fd_t)a, (__fcntl_t)b, (void *)c
#define __NRAM_mpx(a, b, c, d, e, f)                          /* nothing */
#define __NRAM_setpgid(a, b, c, d, e, f)                      (__pid_t)a, (__pid_t)b
#define __NRAM_ulimit(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_oldolduname(a, b, c, d, e, f)                  (struct linux_oldolduname *)a
#define __NRAM_umask(a, b, c, d, e, f)                        (__mode_t)a
#define __NRAM_chroot(a, b, c, d, e, f)                       (char const *)a
#define __NRAM_ustat(a, b, c, d, e, f)                        (__dev_t)a, (struct ustat *)b
#define __NRAM_dup2(a, b, c, d, e, f)                         (__fd_t)a, (__fd_t)b
#define __NRAM_getppid(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_getpgrp(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_setsid(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_sigaction(a, b, c, d, e, f)                    (__signo_t)a, (struct __old_kernel_sigactionx32 const *)b, (struct __old_kernel_sigactionx32 *)c
#define __NRAM_sgetmask(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_ssetmask(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NRAM_setreuid(a, b, c, d, e, f)                     (__uint16_t)a, (__uint16_t)b
#define __NRAM_setregid(a, b, c, d, e, f)                     (__uint16_t)a, (__uint16_t)b
#define __NRAM_sigsuspend(a, b, c, d, e, f)                   (struct __old_sigset_struct const *)a
#define __NRAM_sigpending(a, b, c, d, e, f)                   (struct __old_sigset_struct *)a
#define __NRAM_sethostname(a, b, c, d, e, f)                  (char const *)a, (__size_t)b
#define __NRAM_setrlimit(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __rlimitx32 const *)b
#define __NRAM_getrlimit(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __rlimitx32 *)b
#define __NRAM_getrusage(a, b, c, d, e, f)                    (__syscall_slong_t)a, (struct __rusagex32 *)b
#define __NRAM_gettimeofday(a, b, c, d, e, f)                 (struct __timevalx32 *)a, (struct timezone *)b
#define __NRAM_settimeofday(a, b, c, d, e, f)                 (struct __timevalx32 const *)a, (struct timezone const *)b
#define __NRAM_getgroups(a, b, c, d, e, f)                    (__size_t)a, (__uint16_t *)b
#define __NRAM_setgroups(a, b, c, d, e, f)                    (__size_t)a, (__uint16_t const *)b
#define __NRAM_select(a, b, c, d, e, f)                       (struct sel_arg_structx32 const *)a
#define __NRAM_symlink(a, b, c, d, e, f)                      (char const *)a, (char const *)b
#define __NRAM_oldlstat(a, b, c, d, e, f)                     (char const *)a, (struct linux_oldstat *)b
#define __NRAM_readlink(a, b, c, d, e, f)                     (char const *)a, (char *)b, (__size_t)c
#define __NRAM_uselib(a, b, c, d, e, f)                       (char const *)a
#define __NRAM_swapon(a, b, c, d, e, f)                       (char const *)a, (__syscall_ulong_t)b
#define __NRAM_reboot(a, b, c, d, e, f)                       (__syscall_ulong_t)a
#define __NRAM_readdir(a, b, c, d, e, f)                      (__fd_t)a, (struct old_linux_direntx32 *)b
#define __NRAM_mmap(a, b, c, d, e, f)                         (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NRAM_munmap(a, b, c, d, e, f)                       (void *)a, (__size_t)b
#define __NRAM_truncate(a, b, c, d, e, f)                     (char const *)a, (__syscall_ulong_t)b
#define __NRAM_ftruncate(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_fchmod(a, b, c, d, e, f)                       (__fd_t)a, (__mode_t)b
#define __NRAM_fchown(a, b, c, d, e, f)                       (__fd_t)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getpriority(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__id_t)b
#define __NRAM_setpriority(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__id_t)b, (__syscall_ulong_t)c
#define __NRAM_profil(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_statfs(a, b, c, d, e, f)                       (char const *)a, (struct __statfsx32 *)b
#define __NRAM_fstatfs(a, b, c, d, e, f)                      (__fd_t)a, (struct __statfsx32 *)b
#define __NRAM_ioperm(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_socketcall(a, b, c, d, e, f)                   (__ULONG32_TYPE__)a, (__ULONG32_TYPE__ *)b
#define __NRAM_syslog(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (char const *)b, (__size_t)c
#define __NRAM_setitimer(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __itimervalx32 const *)b, (struct __itimervalx32 *)c
#define __NRAM_getitimer(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __itimervalx32 *)b
#define __NRAM_stat(a, b, c, d, e, f)                         (char const *)a, (struct linux_statx32 *)b
#define __NRAM_lstat(a, b, c, d, e, f)                        (char const *)a, (struct linux_statx32 *)b
#define __NRAM_fstat(a, b, c, d, e, f)                        (__fd_t)a, (struct linux_statx32 *)b
#define __NRAM_olduname(a, b, c, d, e, f)                     (struct linux_olduname *)a
#define __NRAM_iopl(a, b, c, d, e, f)                         (__syscall_ulong_t)a
#define __NRAM_vhangup(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_idle(a, b, c, d, e, f)                         /* nothing */
#define __NRAM_vm86old(a, b, c, d, e, f)                      (int)a
#define __NRAM_wait4(a, b, c, d, e, f)                        (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct __rusagex32 *)d
#define __NRAM_swapoff(a, b, c, d, e, f)                      (char const *)a
#define __NRAM_sysinfo(a, b, c, d, e, f)                      (struct __sysinfox32 *)a
#define __NRAM_ipc(a, b, c, d, e, f)                          (int)a
#define __NRAM_fsync(a, b, c, d, e, f)                        (__fd_t)a
#define __NRAM_sigreturn(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_clone(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (void *)b, (__pid_t *)c, (__uintptr_t)d, (__pid_t *)e
#define __NRAM_setdomainname(a, b, c, d, e, f)                (char const *)a, (__size_t)b
#define __NRAM_uname(a, b, c, d, e, f)                        (struct utsname *)a
#define __NRAM_modify_ldt(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (void *)b, (__syscall_ulong_t)c
#define __NRAM_adjtimex(a, b, c, d, e, f)                     (struct timex *)a
#define __NRAM_mprotect(a, b, c, d, e, f)                     (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_sigprocmask(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __old_sigset_struct const *)b, (struct __old_sigset_struct *)c
#define __NRAM_create_module(a, b, c, d, e, f)                /* nothing */
#define __NRAM_init_module(a, b, c, d, e, f)                  (void const *)a, (__size_t)b, (char const *)c
#define __NRAM_delete_module(a, b, c, d, e, f)                (char const *)a, (__oflag_t)b
#define __NRAM_get_kernel_syms(a, b, c, d, e, f)              /* nothing */
#define __NRAM_quotactl(a, b, c, d, e, f)                     (int)a
#define __NRAM_getpgid(a, b, c, d, e, f)                      (__pid_t)a
#define __NRAM_fchdir(a, b, c, d, e, f)                       (__fd_t)a
#define __NRAM_bdflush(a, b, c, d, e, f)                      (int)a
#define __NRAM_sysfs(a, b, c, d, e, f)                        (int)a
#define __NRAM_personality(a, b, c, d, e, f)                  (int)a
#define __NRAM_afs_syscall(a, b, c, d, e, f)                  /* nothing */
#define __NRAM_setfsuid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NRAM_setfsgid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NRAM__llseek(a, b, c, d, e, f)                      (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t *)d, (__syscall_ulong_t)e
#define __NRAM_getdents(a, b, c, d, e, f)                     (__fd_t)a, (struct linux_direntx32 *)b, (__size_t)c
#define __NRAM__newselect(a, b, c, d, e, f)                   (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timevalx32 *)e
#define __NRAM_flock(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_msync(a, b, c, d, e, f)                        (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_readv(a, b, c, d, e, f)                        (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c
#define __NRAM_writev(a, b, c, d, e, f)                       (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c
#define __NRAM_getsid(a, b, c, d, e, f)                       (__pid_t)a
#define __NRAM_fdatasync(a, b, c, d, e, f)                    (__fd_t)a
#define __NRAM__sysctl(a, b, c, d, e, f)                      (int)a
#define __NRAM_mlock(a, b, c, d, e, f)                        (void const *)a, (__size_t)b
#define __NRAM_munlock(a, b, c, d, e, f)                      (void const *)a, (__size_t)b
#define __NRAM_mlockall(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NRAM_munlockall(a, b, c, d, e, f)                   /* nothing */
#define __NRAM_sched_setparam(a, b, c, d, e, f)               (__pid_t)a, (struct sched_param const *)b
#define __NRAM_sched_getparam(a, b, c, d, e, f)               (__pid_t)a, (struct sched_param *)b
#define __NRAM_sched_setscheduler(a, b, c, d, e, f)           (__pid_t)a, (__syscall_ulong_t)b, (struct sched_param const *)c
#define __NRAM_sched_getscheduler(a, b, c, d, e, f)           (__pid_t)a
#define __NRAM_sched_yield(a, b, c, d, e, f)                  /* nothing */
#define __NRAM_sched_get_priority_max(a, b, c, d, e, f)       (__syscall_ulong_t)a
#define __NRAM_sched_get_priority_min(a, b, c, d, e, f)       (__syscall_ulong_t)a
#define __NRAM_sched_rr_get_interval(a, b, c, d, e, f)        (__pid_t)a, (struct __timespecx32 *)b
#define __NRAM_nanosleep(a, b, c, d, e, f)                    (struct __timespecx32 const *)a, (struct __timespecx32 *)b
#define __NRAM_mremap(a, b, c, d, e, f)                       (void *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d, (void *)e
#define __NRAM_setresuid(a, b, c, d, e, f)                    (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getresuid(a, b, c, d, e, f)                    (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NRAM_vm86(a, b, c, d, e, f)                         (int)a
#define __NRAM_query_module(a, b, c, d, e, f)                 /* nothing */
#define __NRAM_poll(a, b, c, d, e, f)                         (struct pollfd *)a, (__size_t)b, (__syscall_slong_t)c
#define __NRAM_nfsservctl(a, b, c, d, e, f)                   (int)a
#define __NRAM_setresgid(a, b, c, d, e, f)                    (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getresgid(a, b, c, d, e, f)                    (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NRAM_prctl(a, b, c, d, e, f)                        (unsigned int)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAM_rt_sigreturn(a, b, c, d, e, f)                 /* nothing */
#define __NRAM_rt_sigaction(a, b, c, d, e, f)                 (__signo_t)a, (struct __kernel_sigactionx32 const *)b, (struct __kernel_sigactionx32 *)c, (__size_t)d
#define __NRAM_rt_sigprocmask(a, b, c, d, e, f)               (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c, (__size_t)d
#define __NRAM_rt_sigpending(a, b, c, d, e, f)                (struct __sigset_struct *)a, (__size_t)b
#define __NRAM_rt_sigtimedwait(a, b, c, d, e, f)              (struct __sigset_struct const *)a, (struct __siginfox32_struct *)b, (struct __timespecx32 const *)c, (__size_t)d
#define __NRAM_rt_sigqueueinfo(a, b, c, d, e, f)              (__pid_t)a, (__signo_t)b, (struct __siginfox32_struct const *)c
#define __NRAM_rt_sigsuspend(a, b, c, d, e, f)                (struct __sigset_struct const *)a, (__size_t)b
#define __NRAM_pread64(a, b, c, d, e, f)                      (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_pwrite64(a, b, c, d, e, f)                     (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_chown(a, b, c, d, e, f)                        (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NRAM_getcwd(a, b, c, d, e, f)                       (char *)a, (__size_t)b
#define __NRAM_capget(a, b, c, d, e, f)                       (int)a
#define __NRAM_capset(a, b, c, d, e, f)                       (int)a
#define __NRAM_sigaltstack(a, b, c, d, e, f)                  (struct __sigaltstackx32 const *)a, (struct __sigaltstackx32 *)b
#define __NRAM_sendfile(a, b, c, d, e, f)                     (__fd_t)a, (__fd_t)b, (__ULONG32_TYPE__ *)c, (__size_t)d
#define __NRAM_getpmsg(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_putpmsg(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_vfork(a, b, c, d, e, f)                        /* nothing */
#define __NRAM_ugetrlimit(a, b, c, d, e, f)                   (int)a
#define __NRAM_mmap2(a, b, c, d, e, f)                        (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NRAM_truncate64(a, b, c, d, e, f)                   (char const *)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NRAM_ftruncate64(a, b, c, d, e, f)                  (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NRAM_stat64(a, b, c, d, e, f)                       (char const *)a, (struct linux_statx32_64 *)b
#define __NRAM_lstat64(a, b, c, d, e, f)                      (char const *)a, (struct linux_statx32_64 *)b
#define __NRAM_fstat64(a, b, c, d, e, f)                      (__fd_t)a, (struct linux_statx32_64 *)b
#define __NRAM_lchown32(a, b, c, d, e, f)                     (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_getuid32(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_getgid32(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_geteuid32(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_getegid32(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_setreuid32(a, b, c, d, e, f)                   (__uint32_t)a, (__uint32_t)b
#define __NRAM_setregid32(a, b, c, d, e, f)                   (__uint32_t)a, (__uint32_t)b
#define __NRAM_getgroups32(a, b, c, d, e, f)                  (__size_t)a, (__uint32_t *)b
#define __NRAM_setgroups32(a, b, c, d, e, f)                  (__size_t)a, (__uint32_t const *)b
#define __NRAM_fchown32(a, b, c, d, e, f)                     (__fd_t)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_setresuid32(a, b, c, d, e, f)                  (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_getresuid32(a, b, c, d, e, f)                  (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NRAM_setresgid32(a, b, c, d, e, f)                  (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_getresgid32(a, b, c, d, e, f)                  (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NRAM_chown32(a, b, c, d, e, f)                      (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NRAM_setuid32(a, b, c, d, e, f)                     (__uint32_t)a
#define __NRAM_setgid32(a, b, c, d, e, f)                     (__uint32_t)a
#define __NRAM_setfsuid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NRAM_setfsgid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NRAM_pivot_root(a, b, c, d, e, f)                   (int)a
#define __NRAM_mincore(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__uint8_t *)c
#define __NRAM_madvise(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_getdents64(a, b, c, d, e, f)                   (__fd_t)a, (struct linux_dirent64 *)b, (__size_t)c
#define __NRAM_fcntl64(a, b, c, d, e, f)                      (__fd_t)a, (__fcntl_t)b, (void *)c
#define __NRAM_gettid(a, b, c, d, e, f)                       /* nothing */
#define __NRAM_readahead(a, b, c, d, e, f)                    (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__size_t)d
#define __NRAM_setxattr(a, b, c, d, e, f)                     (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_lsetxattr(a, b, c, d, e, f)                    (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_fsetxattr(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_getxattr(a, b, c, d, e, f)                     (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_lgetxattr(a, b, c, d, e, f)                    (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_fgetxattr(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (void *)c, (__size_t)d
#define __NRAM_listxattr(a, b, c, d, e, f)                    (char const *)a, (char *)b, (__size_t)c
#define __NRAM_llistxattr(a, b, c, d, e, f)                   (char const *)a, (char *)b, (__size_t)c
#define __NRAM_flistxattr(a, b, c, d, e, f)                   (__fd_t)a, (char *)b, (__size_t)c
#define __NRAM_removexattr(a, b, c, d, e, f)                  (char const *)a, (char const *)b
#define __NRAM_lremovexattr(a, b, c, d, e, f)                 (char const *)a, (char const *)b
#define __NRAM_fremovexattr(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b
#define __NRAM_tkill(a, b, c, d, e, f)                        (__pid_t)a, (__signo_t)b
#define __NRAM_sendfile64(a, b, c, d, e, f)                   (__fd_t)a, (__fd_t)b, (__ULONG64_TYPE__ *)c, (__size_t)d
#define __NRAM_futex(a, b, c, d, e, f)                        (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespecx32 const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NRAM_sched_setaffinity(a, b, c, d, e, f)            (__pid_t)a, (__size_t)b, (struct __cpu_set_struct const *)c
#define __NRAM_sched_getaffinity(a, b, c, d, e, f)            (__pid_t)a, (__size_t)b, (struct __cpu_set_struct *)c
#define __NRAM_set_thread_area(a, b, c, d, e, f)              (int)a
#define __NRAM_get_thread_area(a, b, c, d, e, f)              (int)a
#define __NRAM_io_setup(a, b, c, d, e, f)                     (int)a
#define __NRAM_io_destroy(a, b, c, d, e, f)                   (int)a
#define __NRAM_io_getevents(a, b, c, d, e, f)                 (int)a
#define __NRAM_io_submit(a, b, c, d, e, f)                    (int)a
#define __NRAM_io_cancel(a, b, c, d, e, f)                    (int)a
#define __NRAM_fadvise64(a, b, c, d, e, f)                    (int)a
#define __NRAM_exit_group(a, b, c, d, e, f)                   (__syscall_ulong_t)a
#define __NRAM_lookup_dcookie(a, b, c, d, e, f)               (int)a
#define __NRAM_epoll_create(a, b, c, d, e, f)                 (__syscall_ulong_t)a
#define __NRAM_epoll_ctl(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b, (__fd_t)c, (struct epoll_event *)d
#define __NRAM_epoll_wait(a, b, c, d, e, f)                   (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d
#define __NRAM_remap_file_pages(a, b, c, d, e, f)             (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__size_t)d, (__syscall_ulong_t)e
#define __NRAM_set_tid_address(a, b, c, d, e, f)              (__pid_t *)a
#define __NRAM_timer_create(a, b, c, d, e, f)                 (__clockid_t)a, (struct sigevent *)b, (__timer_t *)c
#define __NRAM_timer_settime(a, b, c, d, e, f)                (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32 const *)c, (struct __itimerspecx32 *)d
#define __NRAM_timer_gettime(a, b, c, d, e, f)                (__timer_t)a, (struct __itimerspecx32 *)b
#define __NRAM_timer_getoverrun(a, b, c, d, e, f)             (__timer_t)a
#define __NRAM_timer_delete(a, b, c, d, e, f)                 (__timer_t)a
#define __NRAM_clock_settime(a, b, c, d, e, f)                (__clockid_t)a, (struct __timespecx32 const *)b
#define __NRAM_clock_gettime(a, b, c, d, e, f)                (__clockid_t)a, (struct __timespecx32 *)b
#define __NRAM_clock_getres(a, b, c, d, e, f)                 (__clockid_t)a, (struct __timespecx32 *)b
#define __NRAM_clock_nanosleep(a, b, c, d, e, f)              (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespecx32 const *)c, (struct __timespecx32 *)d
#define __NRAM_statfs64(a, b, c, d, e, f)                     (char const *)a, (struct __statfsx32_64 *)b
#define __NRAM_fstatfs64(a, b, c, d, e, f)                    (__fd_t)a, (struct __statfsx32_64 *)b
#define __NRAM_tgkill(a, b, c, d, e, f)                       (__pid_t)a, (__pid_t)b, (__signo_t)c
#define __NRAM_utimes(a, b, c, d, e, f)                       (char const *)a, (struct __timevalx32 const *)b
#define __NRAM_fadvise64_64(a, b, c, d, e, f)                 (int)a
#define __NRAM_vserver(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_mbind(a, b, c, d, e, f)                        (int)a
#define __NRAM_get_mempolicy(a, b, c, d, e, f)                (int)a
#define __NRAM_set_mempolicy(a, b, c, d, e, f)                (int)a
#define __NRAM_mq_open(a, b, c, d, e, f)                      (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NRAM_mq_unlink(a, b, c, d, e, f)                    (char const *)a
#define __NRAM_mq_timedsend(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__size_t)c, (__uint32_t)d, (struct __timespecx32 const *)e
#define __NRAM_mq_timedreceive(a, b, c, d, e, f)              (__fd_t)a, (char *)b, (__size_t)c, (__uint32_t *)d, (struct __timespecx32 const *)e
#define __NRAM_mq_notify(a, b, c, d, e, f)                    (__fd_t)a, (struct sigevent const *)b
#define __NRAM_mq_getsetattr(a, b, c, d, e, f)                (__fd_t)a, (struct mq_attr const *)b, (struct mq_attr *)c
#define __NRAM_kexec_load(a, b, c, d, e, f)                   (int)a
#define __NRAM_waitid(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__id_t)b, (struct __siginfox32_struct *)c, (__syscall_ulong_t)d, (struct __rusagex32 *)e
#define __NRAM_add_key(a, b, c, d, e, f)                      (int)a
#define __NRAM_request_key(a, b, c, d, e, f)                  (int)a
#define __NRAM_keyctl(a, b, c, d, e, f)                       (int)a
#define __NRAM_ioprio_set(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_ioprio_get(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAM_inotify_init(a, b, c, d, e, f)                 /* nothing */
#define __NRAM_inotify_add_watch(a, b, c, d, e, f)            (__fd_t)a, (char const *)b, (__uint32_t)c
#define __NRAM_inotify_rm_watch(a, b, c, d, e, f)             (__fd_t)a, (int)b
#define __NRAM_migrate_pages(a, b, c, d, e, f)                (int)a
#define __NRAM_openat(a, b, c, d, e, f)                       (__fd_t)a, (char const *)b, (__oflag_t)c, (__mode_t)d
#define __NRAM_mkdirat(a, b, c, d, e, f)                      (__fd_t)a, (char const *)b, (__mode_t)c
#define __NRAM_mknodat(a, b, c, d, e, f)                      (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d
#define __NRAM_fchownat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__uid_t)c, (__gid_t)d, (__atflag_t)e
#define __NRAM_futimesat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (struct __timevalx32 const *)c
#define __NRAM_fstatat64(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (struct linux_statx32_64 *)c, (__atflag_t)d
#define __NRAM_unlinkat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NRAM_renameat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d
#define __NRAM_linkat(a, b, c, d, e, f)                       (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NRAM_symlinkat(a, b, c, d, e, f)                    (char const *)a, (__fd_t)b, (char const *)c
#define __NRAM_readlinkat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (char *)c, (__size_t)d
#define __NRAM_fchmodat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NRAM_faccessat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NRAM_pselect6(a, b, c, d, e, f)                     (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespecx32 const *)e, (struct __sigset_with_sizex32 const *)f
#define __NRAM_ppoll(a, b, c, d, e, f)                        (struct pollfd *)a, (__size_t)b, (struct __timespecx32 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NRAM_unshare(a, b, c, d, e, f)                      (__syscall_ulong_t)a
#define __NRAM_set_robust_list(a, b, c, d, e, f)              (int)a
#define __NRAM_get_robust_list(a, b, c, d, e, f)              (int)a
#define __NRAM_splice(a, b, c, d, e, f)                       (__fd_t)a, (__uint64_t *)b, (__fd_t)c, (__uint64_t *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_sync_file_range(a, b, c, d, e, f)              (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__syscall_ulong_t)f
#define __NRAM_tee(a, b, c, d, e, f)                          (__fd_t)a, (__fd_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_vmsplice(a, b, c, d, e, f)                     (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_move_pages(a, b, c, d, e, f)                   (int)a
#define __NRAM_getcpu(a, b, c, d, e, f)                       (__uint32_t *)a, (__uint32_t *)b, (struct getcpu_cache *)c
#define __NRAM_epoll_pwait(a, b, c, d, e, f)                  (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d, (struct __sigset_struct const *)e, (__size_t)f
#define __NRAM_utimensat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (struct __timespecx32 const *)c, (__atflag_t)d
#define __NRAM_signalfd(a, b, c, d, e, f)                     (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c
#define __NRAM_timerfd_create(a, b, c, d, e, f)               (__clockid_t)a, (__syscall_ulong_t)b
#define __NRAM_eventfd(a, b, c, d, e, f)                      (__syscall_ulong_t)a
#define __NRAM_fallocate(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAM_timerfd_settime(a, b, c, d, e, f)              (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32 const *)c, (struct __itimerspecx32 *)d
#define __NRAM_timerfd_gettime(a, b, c, d, e, f)              (__fd_t)a, (struct __itimerspecx32 *)b
#define __NRAM_signalfd4(a, b, c, d, e, f)                    (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_eventfd2(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAM_epoll_create1(a, b, c, d, e, f)                (__syscall_ulong_t)a
#define __NRAM_dup3(a, b, c, d, e, f)                         (__fd_t)a, (__fd_t)b, (__oflag_t)c
#define __NRAM_pipe2(a, b, c, d, e, f)                        (__fd_t *)a, (__oflag_t)b
#define __NRAM_inotify_init1(a, b, c, d, e, f)                (__syscall_ulong_t)a
#define __NRAM_preadv(a, b, c, d, e, f)                       (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_pwritev(a, b, c, d, e, f)                      (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NRAM_rt_tgsigqueueinfo(a, b, c, d, e, f)            (__pid_t)a, (__pid_t)b, (__signo_t)c, (struct __siginfox32_struct const *)d
#define __NRAM_perf_event_open(a, b, c, d, e, f)              (int)a
#define __NRAM_recvmmsg(a, b, c, d, e, f)                     (__fd_t)a, (struct __mmsghdrx32 *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespecx32 const *)e
#define __NRAM_fanotify_init(a, b, c, d, e, f)                (int)a
#define __NRAM_fanotify_mark(a, b, c, d, e, f)                (int)a
#define __NRAM_prlimit64(a, b, c, d, e, f)                    (__pid_t)a, (__syscall_ulong_t)b, (struct __rlimitx32_64 const *)c, (struct __rlimitx32_64 *)d
#define __NRAM_name_to_handle_at(a, b, c, d, e, f)            (__fd_t)a, (char const *)b, (struct file_handle *)c, (__int32_t *)d, (__atflag_t)e
#define __NRAM_open_by_handle_at(a, b, c, d, e, f)            (__fd_t)a, (struct file_handle const *)b, (__oflag_t)c
#define __NRAM_clock_adjtime(a, b, c, d, e, f)                (int)a
#define __NRAM_syncfs(a, b, c, d, e, f)                       (__fd_t)a
#define __NRAM_sendmmsg(a, b, c, d, e, f)                     (__fd_t)a, (struct __mmsghdrx32 *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_setns(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_process_vm_readv(a, b, c, d, e, f)             (__pid_t)a, (struct __iovecx32 const *)b, (__size_t)c, (struct __iovecx32 const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_process_vm_writev(a, b, c, d, e, f)            (__pid_t)a, (struct __iovecx32 const *)b, (__size_t)c, (struct __iovecx32 const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NRAM_kcmp(a, b, c, d, e, f)                         (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAM_finit_module(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NRAM_sched_setattr(a, b, c, d, e, f)                (int)a
#define __NRAM_sched_getattr(a, b, c, d, e, f)                (int)a
#define __NRAM_renameat2(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NRAM_seccomp(a, b, c, d, e, f)                      (int)a
#define __NRAM_getrandom(a, b, c, d, e, f)                    (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_memfd_create(a, b, c, d, e, f)                 (char const *)a, (__syscall_ulong_t)b
#define __NRAM_bpf(a, b, c, d, e, f)                          (int)a
#define __NRAM_execveat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__HYBRID_PTR32(char const) const *)c, (__HYBRID_PTR32(char const) const *)d, (__atflag_t)e
#define __NRAM_socket(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAM_socketpair(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__fd_t *)d
#define __NRAM_bind(a, b, c, d, e, f)                         (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NRAM_connect(a, b, c, d, e, f)                      (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NRAM_listen(a, b, c, d, e, f)                       (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_accept4(a, b, c, d, e, f)                      (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c, (__syscall_ulong_t)d
#define __NRAM_getsockopt(a, b, c, d, e, f)                   (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void *)d, (__socklen_t *)e
#define __NRAM_setsockopt(a, b, c, d, e, f)                   (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void const *)d, (__socklen_t)e
#define __NRAM_getsockname(a, b, c, d, e, f)                  (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NRAM_getpeername(a, b, c, d, e, f)                  (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NRAM_sendto(a, b, c, d, e, f)                       (__fd_t)a, (void const *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr const *)e, (__socklen_t)f
#define __NRAM_sendmsg(a, b, c, d, e, f)                      (__fd_t)a, (struct __msghdrx32 const *)b, (__syscall_ulong_t)c
#define __NRAM_recvfrom(a, b, c, d, e, f)                     (__fd_t)a, (void *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr *)e, (__socklen_t *)f
#define __NRAM_recvmsg(a, b, c, d, e, f)                      (__fd_t)a, (struct __msghdrx32 *)b, (__syscall_ulong_t)c
#define __NRAM_shutdown(a, b, c, d, e, f)                     (__fd_t)a, (__syscall_ulong_t)b
#define __NRAM_userfaultfd(a, b, c, d, e, f)                  (__syscall_ulong_t)a
#define __NRAM_membarrier(a, b, c, d, e, f)                   (int)a
#define __NRAM_mlock2(a, b, c, d, e, f)                       (void const *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_copy_file_range(a, b, c, d, e, f)              (int)a
#define __NRAM_preadv2(a, b, c, d, e, f)                      (int)a
#define __NRAM_pwritev2(a, b, c, d, e, f)                     (int)a
#define __NRAM_pkey_mprotect(a, b, c, d, e, f)                (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAM_pkey_alloc(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAM_pkey_free(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NRAM_statx(a, b, c, d, e, f)                        (int)a
#define __NRAM_arch_prctl(a, b, c, d, e, f)                   (unsigned int)a, (__uint32_t *)b
#define __NRAM_io_pgetevents(a, b, c, d, e, f)                (int)a
#define __NRAM_rseq(a, b, c, d, e, f)                         (int)a
#define __NRAM_semget(a, b, c, d, e, f)                       (int)a
#define __NRAM_semctl(a, b, c, d, e, f)                       (int)a
#define __NRAM_shmget(a, b, c, d, e, f)                       (__key_t)a, (__size_t)b, (__syscall_ulong_t)c
#define __NRAM_shmctl(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (struct shmid_ds *)c
#define __NRAM_shmat(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (void const *)b, (__syscall_ulong_t)c
#define __NRAM_shmdt(a, b, c, d, e, f)                        (void const *)a
#define __NRAM_msgget(a, b, c, d, e, f)                       (int)a
#define __NRAM_msgsnd(a, b, c, d, e, f)                       (int)a
#define __NRAM_msgrcv(a, b, c, d, e, f)                       (int)a
#define __NRAM_msgctl(a, b, c, d, e, f)                       (int)a
#define __NRAM_clock_gettime64(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespecx32_64 *)b
#define __NRAM_clock_settime64(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespecx32_64 const *)b
#define __NRAM_clock_adjtime64(a, b, c, d, e, f)              (int)a
#define __NRAM_clock_getres_time64(a, b, c, d, e, f)          (__clockid_t)a, (struct __timespecx32_64 *)b
#define __NRAM_clock_nanosleep_time64(a, b, c, d, e, f)       (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespecx32_64 const *)c, (struct __timespecx32_64 *)d
#define __NRAM_timer_gettime64(a, b, c, d, e, f)              (__timer_t)a, (struct __itimerspecx32_64 *)b
#define __NRAM_timer_settime64(a, b, c, d, e, f)              (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32_64 const *)c, (struct __itimerspecx32_64 *)d
#define __NRAM_timerfd_gettime64(a, b, c, d, e, f)            (__fd_t)a, (struct __itimerspecx32_64 *)b
#define __NRAM_timerfd_settime64(a, b, c, d, e, f)            (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32_64 const *)c, (struct __itimerspecx32_64 *)d
#define __NRAM_utimensat_time64(a, b, c, d, e, f)             (__fd_t)a, (char const *)b, (struct __timespecx32_64 const *)c, (__atflag_t)d
#define __NRAM_pselect6_time64(a, b, c, d, e, f)              (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespecx32_64 const *)e, (struct __sigset_with_sizex32 const *)f
#define __NRAM_ppoll_time64(a, b, c, d, e, f)                 (struct pollfd *)a, (__size_t)b, (struct __timespecx32_64 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NRAM_io_pgetevents_time64(a, b, c, d, e, f)         (int)a
#define __NRAM_recvmmsg_time64(a, b, c, d, e, f)              (__fd_t)a, (struct __mmsghdrx32 *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespecx32_64 const *)e
#define __NRAM_mq_timedsend_time64(a, b, c, d, e, f)          (__fd_t)a, (char const *)b, (__size_t)c, (__uint32_t)d, (struct __timespecx32_64 const *)e
#define __NRAM_mq_timedreceive_time64(a, b, c, d, e, f)       (__fd_t)a, (char *)b, (__size_t)c, (__uint32_t *)d, (struct __timespecx32_64 const *)e
#define __NRAM_semtimedop_time64(a, b, c, d, e, f)            (int)a
#define __NRAM_rt_sigtimedwait_time64(a, b, c, d, e, f)       (struct __sigset_struct const *)a, (struct __siginfox32_struct *)b, (struct __timespecx32_64 const *)c, (__size_t)d
#define __NRAM_futex_time64(a, b, c, d, e, f)                 (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespecx32_64 const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NRAM_sched_rr_get_interval_time64(a, b, c, d, e, f) (__pid_t)a, (struct __timespecx32_64 *)b
#define __NRAM_pidfd_send_signal(a, b, c, d, e, f)            (__fd_t)a, (__signo_t)b, (struct __siginfox32_struct const *)c, (__syscall_ulong_t)d
#define __NRAM_io_uring_setup(a, b, c, d, e, f)               (int)a
#define __NRAM_io_uring_enter(a, b, c, d, e, f)               (int)a
#define __NRAM_io_uring_register(a, b, c, d, e, f)            (int)a
#define __NRAM_open_tree(a, b, c, d, e, f)                    (int)a
#define __NRAM_move_mount(a, b, c, d, e, f)                   (int)a
#define __NRAM_fsopen(a, b, c, d, e, f)                       (int)a
#define __NRAM_fsconfig(a, b, c, d, e, f)                     (int)a
#define __NRAM_fsmount(a, b, c, d, e, f)                      (int)a
#define __NRAM_fspick(a, b, c, d, e, f)                       (int)a
#define __NRAM_pidfd_open(a, b, c, d, e, f)                   (__pid_t)a, (__syscall_ulong_t)b
#define __NRAM_clone3(a, b, c, d, e, f)                       (struct clone_args *)a, (__size_t)b
#define __NRAM_close_range(a, b, c, d, e, f)                  (unsigned int)a, (unsigned int)b, (unsigned int)c
#define __NRAM_openat2(a, b, c, d, e, f)                      (int)a
#define __NRAM_pidfd_getfd(a, b, c, d, e, f)                  (__fd_t)a, (__fd_t)b, (__syscall_ulong_t)c
#define __NRAM_faccessat2(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__syscall_ulong_t)c, (__atflag_t)d
#define __NRAM_pwritevf(a, b, c, d, e, f)                     (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_preadvf(a, b, c, d, e, f)                      (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_fallocate64(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b, (__uint64_t)((__uint64_t)c | (__uint64_t)d << 32), (__uint64_t)((__uint64_t)e | (__uint64_t)f << 32)
#define __NRAM_freadlinkat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NRAM_fsymlinkat(a, b, c, d, e, f)                   (char const *)a, (__fd_t)b, (char const *)c, (__atflag_t)d
#define __NRAM_kfstatat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (struct __kos_stat *)c, (__atflag_t)d
#define __NRAM_futimesat64(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (struct __timevalx32_64 const *)c
#define __NRAM_fmknodat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d, (__atflag_t)e
#define __NRAM_fmkdirat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NRAM_inotify_add_watch_at(a, b, c, d, e, f)         (__fd_t)a, (__fd_t)b, (char const *)c, (__atflag_t)d, (__uint32_t)e
#define __NRAM_waitid64(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__id_t)b, (struct __siginfox32_struct *)c, (__syscall_ulong_t)d, (struct __rusagex32_64 *)e
#define __NRAM_utimes64(a, b, c, d, e, f)                     (char const *)a, (struct __timevalx32_64 const *)b
#define __NRAM_set_userprocmask_address(a, b, c, d, e, f)     (struct userprocmask *)a
#define __NRAM_lfutexexpr(a, b, c, d, e, f)                   (__uint32_t *)a, (void *)b, (struct lfutexexprx32 const *)c, (struct __timespecx32_64 const *)d, (__syscall_ulong_t)e
#define __NRAM_lfutex(a, b, c, d, e, f)                       (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespecx32_64 const *)d, (__uint32_t)e
#define __NRAM_kreaddirf(a, b, c, d, e, f)                    (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d, (__iomode_t)e
#define __NRAM_kreaddir(a, b, c, d, e, f)                     (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NRAM_kfstat(a, b, c, d, e, f)                       (__fd_t)a, (struct __kos_stat *)b
#define __NRAM_klstat(a, b, c, d, e, f)                       (char const *)a, (struct __kos_stat *)b
#define __NRAM_kstat(a, b, c, d, e, f)                        (char const *)a, (struct __kos_stat *)b
#define __NRAM_pwrite64f(a, b, c, d, e, f)                    (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_pread64f(a, b, c, d, e, f)                     (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NRAM_ksigreturn(a, b, c, d, e, f)                   (struct fpustate32 const *)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (struct __sigset_with_sizex32 const *)d, (struct rpc_syscall_info32 const *)e, (struct ucpustate32 const *)f
#define __NRAM_nanosleep64(a, b, c, d, e, f)                  (struct __timespecx32_64 const *)a, (struct __timespecx32_64 *)b
#define __NRAM_rpc_serve_sysret(a, b, c, d, e, f)             /* nothing */
#define __NRAM_rpc_serve(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_ksysctl(a, b, c, d, e, f)                      (__ioctl_t)a, (void *)b
#define __NRAM_writevf(a, b, c, d, e, f)                      (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__iomode_t)d
#define __NRAM_readvf(a, b, c, d, e, f)                       (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__iomode_t)d
#define __NRAM_select64(a, b, c, d, e, f)                     (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timevalx32_64 *)e
#define __NRAM_wait4_64(a, b, c, d, e, f)                     (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct __rusagex32_64 *)d
#define __NRAM_getitimer64(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimervalx32_64 *)b
#define __NRAM_setitimer64(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimervalx32_64 const *)b, (struct __itimervalx32_64 *)c
#define __NRAM_maplibrary(a, b, c, d, e, f)                   (void *)a, (__syscall_ulong_t)b, (__fd_t)c, (struct elf32_phdr const *)d, (__size_t)e
#define __NRAM_settimeofday64(a, b, c, d, e, f)               (struct __timevalx32_64 const *)a, (struct timezone const *)b
#define __NRAM_gettimeofday64(a, b, c, d, e, f)               (struct __timevalx32_64 *)a, (struct timezone *)b
#define __NRAM_getrusage64(a, b, c, d, e, f)                  (__syscall_slong_t)a, (struct __rusagex32_64 *)b
#define __NRAM_fsmode(a, b, c, d, e, f)                       (__uint64_t)((__uint64_t)a | (__uint64_t)b << 32)
#define __NRAM_ioctlf(a, b, c, d, e, f)                       (__fd_t)a, (__ioctl_t)b, (__iomode_t)c, (void *)d
#define __NRAM_rtm_test(a, b, c, d, e, f)                     /* nothing */
#define __NRAM_rtm_abort(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NRAM_rtm_end(a, b, c, d, e, f)                      /* nothing */
#define __NRAM_rtm_begin(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_ftime64(a, b, c, d, e, f)                      (struct __timebx32_64 *)a
#define __NRAM_utime64(a, b, c, d, e, f)                      (char const *)a, (struct __utimbufx32_64 const *)b
#define __NRAM_stime64(a, b, c, d, e, f)                      (__time64_t const *)a
#define __NRAM_userviofd(a, b, c, d, e, f)                    (__size_t)a, (__syscall_ulong_t)b
#define __NRAM_lseek64(a, b, c, d, e, f)                      (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__syscall_ulong_t)d
#define __NRAM_coredump(a, b, c, d, e, f)                     (struct ucpustate32 const *)a, (struct ucpustate32 const *)b, (__HYBRID_PTR32(void const) const *)c, (__size_t)d, (union coredump_info32 const *)e, (unwind_errno_t)f
#define __NRAM_debugtrap(a, b, c, d, e, f)                    (struct ucpustate32 const *)a, (struct debugtrap_reason32 const *)b
#define __NRAM_get_exception_handler(a, b, c, d, e, f)        (__ULONG32_TYPE__ *)a, (__except_handler32_t *)b, (__HYBRID_PTR32(void) *)c
#define __NRAM_set_exception_handler(a, b, c, d, e, f)        (__syscall_ulong_t)a, (__except_handler_t)b, (void *)c
#define __NRAM_mktty(a, b, c, d, e, f)                        (char const *)a, (__fd_t)b, (__fd_t)c, (__syscall_ulong_t)d
#define __NRAM_time64(a, b, c, d, e, f)                       (__int64_t *)a
#define __NRAM_fchdirat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NRAM_openpty(a, b, c, d, e, f)                      (__fd_t *)a, (__fd_t *)b, (char *)c, (struct termios const *)d, (struct winsize const *)e
#define __NRAM_rpc_schedule(a, b, c, d, e, f)                 (__pid_t)a, (__syscall_ulong_t)b, (void const *)c, (__HYBRID_PTR32(void const) const *)d, (__size_t)e
#define __NRAM_frealpathat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NRAM_detach(a, b, c, d, e, f)                       (__pid_t)a
#define __NRAM_frealpath4(a, b, c, d, e, f)                   (__fd_t)a, (char *)b, (__size_t)c, (__atflag_t)d
#define __NRAM_getdrives(a, b, c, d, e, f)                    /* nothing */
#define __NRAM_writef(a, b, c, d, e, f)                       (__fd_t)a, (void const *)b, (__size_t)c, (__iomode_t)d
#define __NRAM_readf(a, b, c, d, e, f)                        (__fd_t)a, (void *)b, (__size_t)c, (__iomode_t)d
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_MAKER */


/************************************************************************/
/* SYSCALL ARGUMENT LIST PACKING                                        */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NRAP_restart_syscall()                              /* nothing */
#define __NRAP_exit(a)                                        (__syscall_ulong_t)a
#define __NRAP_fork()                                         /* nothing */
#define __NRAP_read(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_write(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_open(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_close(a)                                       (__syscall_ulong_t)a
#define __NRAP_waitpid(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_creat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_link(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_unlink(a)                                      (__syscall_ulong_t)a
#define __NRAP_execve(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chdir(a)                                       (__syscall_ulong_t)a
#define __NRAP_time(a)                                        (__syscall_ulong_t)a
#define __NRAP_mknod(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chmod(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lchown(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_break()                                        /* nothing */
#define __NRAP_oldstat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lseek(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpid()                                       /* nothing */
#define __NRAP_mount(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_umount(a)                                      (__syscall_ulong_t)a
#define __NRAP_setuid(a)                                      (__syscall_ulong_t)a
#define __NRAP_getuid()                                       /* nothing */
#define __NRAP_stime(a)                                       (__syscall_ulong_t)a
#define __NRAP_ptrace(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_alarm(a)                                       (__syscall_ulong_t)a
#define __NRAP_oldfstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pause()                                        /* nothing */
#define __NRAP_utime(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_stty()                                         /* nothing */
#define __NRAP_gtty()                                         /* nothing */
#define __NRAP_access(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_nice(a)                                        (__syscall_ulong_t)a
#define __NRAP_ftime(a)                                       (__syscall_ulong_t)a
#define __NRAP_sync()                                         /* nothing */
#define __NRAP_kill(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rename(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mkdir(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rmdir(a)                                       (__syscall_ulong_t)a
#define __NRAP_dup(a)                                         (__syscall_ulong_t)a
#define __NRAP_pipe(a)                                        (__syscall_ulong_t)a
#define __NRAP_times(a)                                       (__syscall_ulong_t)a
#define __NRAP_prof()                                         /* nothing */
#define __NRAP_brk(a)                                         (__syscall_ulong_t)a
#define __NRAP_setgid(a)                                      (__syscall_ulong_t)a
#define __NRAP_getgid()                                       /* nothing */
#define __NRAP_signal(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_geteuid()                                      /* nothing */
#define __NRAP_getegid()                                      /* nothing */
#define __NRAP_acct(a)                                        (__syscall_ulong_t)a
#define __NRAP_umount2(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lock()                                         /* nothing */
#define __NRAP_ioctl(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_fcntl(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mpx()                                          /* nothing */
#define __NRAP_setpgid(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ulimit()                                       /* nothing */
#define __NRAP_oldolduname(a)                                 (__syscall_ulong_t)a
#define __NRAP_umask(a)                                       (__syscall_ulong_t)a
#define __NRAP_chroot(a)                                      (__syscall_ulong_t)a
#define __NRAP_ustat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_dup2(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getppid()                                      /* nothing */
#define __NRAP_getpgrp()                                      /* nothing */
#define __NRAP_setsid()                                       /* nothing */
#define __NRAP_sigaction(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sgetmask()                                     /* nothing */
#define __NRAP_ssetmask(a)                                    (__syscall_ulong_t)a
#define __NRAP_setreuid(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setregid(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sigsuspend(a)                                  (__syscall_ulong_t)a
#define __NRAP_sigpending(a)                                  (__syscall_ulong_t)a
#define __NRAP_sethostname(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setrlimit(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getrlimit(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getrusage(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_gettimeofday(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_settimeofday(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getgroups(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setgroups(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_select(a)                                      (__syscall_ulong_t)a
#define __NRAP_symlink(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_oldlstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_readlink(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_uselib(a)                                      (__syscall_ulong_t)a
#define __NRAP_swapon(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_reboot(a)                                      (__syscall_ulong_t)a
#define __NRAP_readdir(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mmap(a, b, c, d, e, f)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_munmap(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_truncate(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ftruncate(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fchmod(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fchown(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpriority(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setpriority(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_profil()                                       /* nothing */
#define __NRAP_statfs(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fstatfs(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_ioperm(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_socketcall(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_syslog(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setitimer(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getitimer(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_stat(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lstat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fstat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_olduname(a)                                    (__syscall_ulong_t)a
#define __NRAP_iopl(a)                                        (__syscall_ulong_t)a
#define __NRAP_vhangup()                                      /* nothing */
#define __NRAP_idle()                                         /* nothing */
#define __NRAP_vm86old(a)                                     (__syscall_ulong_t)a
#define __NRAP_wait4(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_swapoff(a)                                     (__syscall_ulong_t)a
#define __NRAP_sysinfo(a)                                     (__syscall_ulong_t)a
#define __NRAP_ipc(a)                                         (__syscall_ulong_t)a
#define __NRAP_fsync(a)                                       (__syscall_ulong_t)a
#define __NRAP_sigreturn()                                    /* nothing */
#define __NRAP_clone(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_setdomainname(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_uname(a)                                       (__syscall_ulong_t)a
#define __NRAP_modify_ldt(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_adjtimex(a)                                    (__syscall_ulong_t)a
#define __NRAP_mprotect(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sigprocmask(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_create_module()                                /* nothing */
#define __NRAP_init_module(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_delete_module(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_get_kernel_syms()                              /* nothing */
#define __NRAP_quotactl(a)                                    (__syscall_ulong_t)a
#define __NRAP_getpgid(a)                                     (__syscall_ulong_t)a
#define __NRAP_fchdir(a)                                      (__syscall_ulong_t)a
#define __NRAP_bdflush(a)                                     (__syscall_ulong_t)a
#define __NRAP_sysfs(a)                                       (__syscall_ulong_t)a
#define __NRAP_personality(a)                                 (__syscall_ulong_t)a
#define __NRAP_afs_syscall()                                  /* nothing */
#define __NRAP_setfsuid(a)                                    (__syscall_ulong_t)a
#define __NRAP_setfsgid(a)                                    (__syscall_ulong_t)a
#define __NRAP__llseek(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getdents(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP__newselect(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_flock(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_msync(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_readv(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_writev(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getsid(a)                                      (__syscall_ulong_t)a
#define __NRAP_fdatasync(a)                                   (__syscall_ulong_t)a
#define __NRAP__sysctl(a)                                     (__syscall_ulong_t)a
#define __NRAP_mlock(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_munlock(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mlockall(a)                                    (__syscall_ulong_t)a
#define __NRAP_munlockall()                                   /* nothing */
#define __NRAP_sched_setparam(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sched_getparam(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sched_setscheduler(a, b, c)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_getscheduler(a)                          (__syscall_ulong_t)a
#define __NRAP_sched_yield()                                  /* nothing */
#define __NRAP_sched_get_priority_max(a)                      (__syscall_ulong_t)a
#define __NRAP_sched_get_priority_min(a)                      (__syscall_ulong_t)a
#define __NRAP_sched_rr_get_interval(a, b)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_nanosleep(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mremap(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_setresuid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresuid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_vm86(a)                                        (__syscall_ulong_t)a
#define __NRAP_query_module()                                 /* nothing */
#define __NRAP_poll(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_nfsservctl(a)                                  (__syscall_ulong_t)a
#define __NRAP_setresgid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresgid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_prctl(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_rt_sigreturn()                                 /* nothing */
#define __NRAP_rt_sigaction(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigprocmask(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigpending(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rt_sigtimedwait(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rt_sigqueueinfo(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_rt_sigsuspend(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pread64(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_pwrite64(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_chown(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getcwd(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_capget(a)                                      (__syscall_ulong_t)a
#define __NRAP_capset(a)                                      (__syscall_ulong_t)a
#define __NRAP_sigaltstack(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sendfile(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getpmsg()                                      /* nothing */
#define __NRAP_putpmsg()                                      /* nothing */
#define __NRAP_vfork()                                        /* nothing */
#define __NRAP_ugetrlimit(a)                                  (__syscall_ulong_t)a
#define __NRAP_mmap2(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_truncate64(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NRAP_ftruncate64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NRAP_stat64(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lstat64(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fstat64(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lchown32(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getuid32()                                     /* nothing */
#define __NRAP_getgid32()                                     /* nothing */
#define __NRAP_geteuid32()                                    /* nothing */
#define __NRAP_getegid32()                                    /* nothing */
#define __NRAP_setreuid32(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setregid32(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getgroups32(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setgroups32(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fchown32(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setresuid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresuid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setresgid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getresgid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_chown32(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_setuid32(a)                                    (__syscall_ulong_t)a
#define __NRAP_setgid32(a)                                    (__syscall_ulong_t)a
#define __NRAP_setfsuid32(a)                                  (__syscall_ulong_t)a
#define __NRAP_setfsgid32(a)                                  (__syscall_ulong_t)a
#define __NRAP_pivot_root(a)                                  (__syscall_ulong_t)a
#define __NRAP_mincore(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_madvise(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getdents64(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_fcntl64(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_gettid()                                       /* nothing */
#define __NRAP_readahead(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NRAP_setxattr(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_lsetxattr(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fsetxattr(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_getxattr(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_lgetxattr(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fgetxattr(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_listxattr(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_llistxattr(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_flistxattr(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_removexattr(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lremovexattr(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fremovexattr(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_tkill(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_sendfile64(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_futex(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_sched_setaffinity(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_getaffinity(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_set_thread_area(a)                             (__syscall_ulong_t)a
#define __NRAP_get_thread_area(a)                             (__syscall_ulong_t)a
#define __NRAP_io_setup(a)                                    (__syscall_ulong_t)a
#define __NRAP_io_destroy(a)                                  (__syscall_ulong_t)a
#define __NRAP_io_getevents(a)                                (__syscall_ulong_t)a
#define __NRAP_io_submit(a)                                   (__syscall_ulong_t)a
#define __NRAP_io_cancel(a)                                   (__syscall_ulong_t)a
#define __NRAP_fadvise64(a)                                   (__syscall_ulong_t)a
#define __NRAP_exit_group(a)                                  (__syscall_ulong_t)a
#define __NRAP_lookup_dcookie(a)                              (__syscall_ulong_t)a
#define __NRAP_epoll_create(a)                                (__syscall_ulong_t)a
#define __NRAP_epoll_ctl(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_epoll_wait(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_remap_file_pages(a, b, c, d, e)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_set_tid_address(a)                             (__syscall_ulong_t)a
#define __NRAP_timer_create(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_timer_settime(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timer_gettime(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_timer_getoverrun(a)                            (__syscall_ulong_t)a
#define __NRAP_timer_delete(a)                                (__syscall_ulong_t)a
#define __NRAP_clock_settime(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_gettime(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_getres(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_nanosleep(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_statfs64(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fstatfs64(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_tgkill(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_utimes(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fadvise64_64(a)                                (__syscall_ulong_t)a
#define __NRAP_vserver()                                      /* nothing */
#define __NRAP_mbind(a)                                       (__syscall_ulong_t)a
#define __NRAP_get_mempolicy(a)                               (__syscall_ulong_t)a
#define __NRAP_set_mempolicy(a)                               (__syscall_ulong_t)a
#define __NRAP_mq_open(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mq_unlink(a)                                   (__syscall_ulong_t)a
#define __NRAP_mq_timedsend(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_mq_timedreceive(a, b, c, d, e)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_mq_notify(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_mq_getsetattr(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_kexec_load(a)                                  (__syscall_ulong_t)a
#define __NRAP_waitid(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_add_key(a)                                     (__syscall_ulong_t)a
#define __NRAP_request_key(a)                                 (__syscall_ulong_t)a
#define __NRAP_keyctl(a)                                      (__syscall_ulong_t)a
#define __NRAP_ioprio_set(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_ioprio_get(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_inotify_init()                                 /* nothing */
#define __NRAP_inotify_add_watch(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_inotify_rm_watch(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_migrate_pages(a)                               (__syscall_ulong_t)a
#define __NRAP_openat(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_mkdirat(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mknodat(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fchownat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_futimesat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_fstatat64(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_unlinkat(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_renameat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_linkat(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_symlinkat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_readlinkat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_fchmodat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_faccessat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_pselect6(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_ppoll(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_unshare(a)                                     (__syscall_ulong_t)a
#define __NRAP_set_robust_list(a)                             (__syscall_ulong_t)a
#define __NRAP_get_robust_list(a)                             (__syscall_ulong_t)a
#define __NRAP_splice(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_sync_file_range(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d
#define __NRAP_tee(a, b, c, d)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_vmsplice(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_move_pages(a)                                  (__syscall_ulong_t)a
#define __NRAP_getcpu(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_epoll_pwait(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_utimensat(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_signalfd(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_timerfd_create(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_eventfd(a)                                     (__syscall_ulong_t)a
#define __NRAP_fallocate(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_settime(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_gettime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_signalfd4(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_eventfd2(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_epoll_create1(a)                               (__syscall_ulong_t)a
#define __NRAP_dup3(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_pipe2(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_inotify_init1(a)                               (__syscall_ulong_t)a
#define __NRAP_preadv(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_pwritev(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_rt_tgsigqueueinfo(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_perf_event_open(a)                             (__syscall_ulong_t)a
#define __NRAP_recvmmsg(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fanotify_init(a)                               (__syscall_ulong_t)a
#define __NRAP_fanotify_mark(a)                               (__syscall_ulong_t)a
#define __NRAP_prlimit64(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_name_to_handle_at(a, b, c, d, e)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_open_by_handle_at(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_clock_adjtime(a)                               (__syscall_ulong_t)a
#define __NRAP_syncfs(a)                                      (__syscall_ulong_t)a
#define __NRAP_sendmmsg(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_setns(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_process_vm_readv(a, b, c, d, e, f)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_process_vm_writev(a, b, c, d, e, f)            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_kcmp(a, b, c, d, e)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_finit_module(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sched_setattr(a)                               (__syscall_ulong_t)a
#define __NRAP_sched_getattr(a)                               (__syscall_ulong_t)a
#define __NRAP_renameat2(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_seccomp(a)                                     (__syscall_ulong_t)a
#define __NRAP_getrandom(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_memfd_create(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_bpf(a)                                         (__syscall_ulong_t)a
#define __NRAP_execveat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_socket(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_socketpair(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_bind(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_connect(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_listen(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_accept4(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getsockopt(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_setsockopt(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_getsockname(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_getpeername(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_sendto(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_sendmsg(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_recvfrom(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_recvmsg(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shutdown(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_userfaultfd(a)                                 (__syscall_ulong_t)a
#define __NRAP_membarrier(a)                                  (__syscall_ulong_t)a
#define __NRAP_mlock2(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_copy_file_range(a)                             (__syscall_ulong_t)a
#define __NRAP_preadv2(a)                                     (__syscall_ulong_t)a
#define __NRAP_pwritev2(a)                                    (__syscall_ulong_t)a
#define __NRAP_pkey_mprotect(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pkey_alloc(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pkey_free(a)                                   (__syscall_ulong_t)a
#define __NRAP_statx(a)                                       (__syscall_ulong_t)a
#define __NRAP_arch_prctl(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_io_pgetevents(a)                               (__syscall_ulong_t)a
#define __NRAP_rseq(a)                                        (__syscall_ulong_t)a
#define __NRAP_semget(a)                                      (__syscall_ulong_t)a
#define __NRAP_semctl(a)                                      (__syscall_ulong_t)a
#define __NRAP_shmget(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shmctl(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shmat(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_shmdt(a)                                       (__syscall_ulong_t)a
#define __NRAP_msgget(a)                                      (__syscall_ulong_t)a
#define __NRAP_msgsnd(a)                                      (__syscall_ulong_t)a
#define __NRAP_msgrcv(a)                                      (__syscall_ulong_t)a
#define __NRAP_msgctl(a)                                      (__syscall_ulong_t)a
#define __NRAP_clock_gettime64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_settime64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_adjtime64(a)                             (__syscall_ulong_t)a
#define __NRAP_clock_getres_time64(a, b)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clock_nanosleep_time64(a, b, c, d)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timer_gettime64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_timer_settime64(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_timerfd_gettime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_timerfd_settime64(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_utimensat_time64(a, b, c, d)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pselect6_time64(a, b, c, d, e, f)              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_ppoll_time64(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_io_pgetevents_time64(a)                        (__syscall_ulong_t)a
#define __NRAP_recvmmsg_time64(a, b, c, d, e)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_mq_timedsend_time64(a, b, c, d, e)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_mq_timedreceive_time64(a, b, c, d, e)          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_semtimedop_time64(a)                           (__syscall_ulong_t)a
#define __NRAP_rt_sigtimedwait_time64(a, b, c, d)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_futex_time64(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_sched_rr_get_interval_time64(a, b)             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pidfd_send_signal(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_io_uring_setup(a)                              (__syscall_ulong_t)a
#define __NRAP_io_uring_enter(a)                              (__syscall_ulong_t)a
#define __NRAP_io_uring_register(a)                           (__syscall_ulong_t)a
#define __NRAP_open_tree(a)                                   (__syscall_ulong_t)a
#define __NRAP_move_mount(a)                                  (__syscall_ulong_t)a
#define __NRAP_fsopen(a)                                      (__syscall_ulong_t)a
#define __NRAP_fsconfig(a)                                    (__syscall_ulong_t)a
#define __NRAP_fsmount(a)                                     (__syscall_ulong_t)a
#define __NRAP_fspick(a)                                      (__syscall_ulong_t)a
#define __NRAP_pidfd_open(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_clone3(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_close_range(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_openat2(a)                                     (__syscall_ulong_t)a
#define __NRAP_pidfd_getfd(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_faccessat2(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_pwritevf(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_preadvf(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_fallocate64(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NRAP_freadlinkat(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fsymlinkat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_kfstatat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_futimesat64(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_fmknodat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_fmkdirat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_inotify_add_watch_at(a, b, c, d, e)            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_waitid64(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_utimes64(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_set_userprocmask_address(a)                    (__syscall_ulong_t)a
#define __NRAP_lfutexexpr(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_lfutex(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_kreaddirf(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_kreaddir(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_kfstat(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_klstat(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_kstat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_pwrite64f(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_pread64f(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NRAP_ksigreturn(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_nanosleep64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_rpc_serve_sysret()                             /* nothing */
#define __NRAP_rpc_serve()                                    /* nothing */
#define __NRAP_ksysctl(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_writevf(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_readvf(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_select64(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_wait4_64(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getitimer64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_setitimer64(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_maplibrary(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_settimeofday64(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_gettimeofday64(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_getrusage64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_fsmode(a)                                      (__syscall_ulong_t)a, (__syscall_ulong_t)((__uint64_t)a >> 32)
#define __NRAP_ioctlf(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_rtm_test()                                     /* nothing */
#define __NRAP_rtm_abort(a)                                   (__syscall_ulong_t)a
#define __NRAP_rtm_end()                                      /* nothing */
#define __NRAP_rtm_begin()                                    /* nothing */
#define __NRAP_ftime64(a)                                     (__syscall_ulong_t)a
#define __NRAP_utime64(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_stime64(a)                                     (__syscall_ulong_t)a
#define __NRAP_userviofd(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_lseek64(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NRAP_coredump(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NRAP_debugtrap(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NRAP_get_exception_handler(a, b, c)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_set_exception_handler(a, b, c)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_mktty(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_time64(a)                                      (__syscall_ulong_t)a
#define __NRAP_fchdirat(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NRAP_openpty(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_rpc_schedule(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_frealpathat(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NRAP_detach(a)                                      (__syscall_ulong_t)a
#define __NRAP_frealpath4(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_getdrives()                                    /* nothing */
#define __NRAP_writef(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NRAP_readf(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_PACKER */

